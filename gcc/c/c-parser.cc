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

#அந்தர்பாவ "config.h"
#define INCLUDE_STRING
#அந்தர்பாவ "system.h"
#அந்தர்பாவ "coretypes.h"
#அந்தர்பாவ "target.h"
#அந்தர்பாவ "function.h"
#அந்தர்பாவ "c-tree.h"
#அந்தர்பாவ "timevar.h"
#அந்தர்பாவ "stringpool.h"
#அந்தர்பாவ "cgraph.h"
#அந்தர்பாவ "attribs.h"
#அந்தர்பாவ "stor-layout.h"
#அந்தர்பாவ "varasm.h"
#அந்தர்பாவ "trans-mem.h"
#அந்தர்பாவ "c-family/c-pragma.h"
#அந்தர்பாவ "c-lang.h"
#அந்தர்பாவ "c-family/c-objc.h"
#அந்தர்பாவ "plugin.h"
#அந்தர்பாவ "omp-general.h"
#அந்தர்பாவ "omp-offload.h"
#அந்தர்பாவ "builtins.h"
#அந்தர்பாவ "gomp-constants.h"
#அந்தர்பாவ "c-family/c-indentation.h"
#அந்தர்பாவ "gimple-expr.h"
#அந்தர்பாவ "context.h"
#அந்தர்பாவ "gcc-rich-location.h"
#அந்தர்பாவ "c-parser.h"
#அந்தர்பாவ "gimple-parser.h"
#அந்தர்பாவ "read-rtl-function.h"
#அந்தர்பாவ "run-rtl-passes.h"
#அந்தர்பாவ "intl.h"
#அந்தர்பாவ "c-family/name-hint.h"
#அந்தர்பாவ "tree-iterator.h"
#அந்தர்பாவ "tree-pretty-print.h"
#அந்தர்பாவ "memmodel.h"
#அந்தர்பாவ "c-family/known-headers.h"
#அந்தர்பாவ "bitmap.h"
#அந்தர்பாவ "analyzer/analyzer-language.h"
#அந்தர்பாவ "toplev.h"
#அந்தர்பாவ "asan.h"
#அந்தர்பாவ "c-family/c-ubsan.h"
#அந்தர்பாவ "gcc-urlifier.h"

/* We need to walk over decls with incomplete struct/union/enum types
   after parsing the whole translation unit.
   In finish_decl(), if the decl is static, has incomplete
   struct/union/enum type, it is appended to incomplete_record_decls.
   In c_parser_translation_unit(), we iterate over incomplete_record_decls
   and report error if any of the decls are still incomplete.  */

vec<மரம்> incomplete_record_decls;

வெறுமை
set_c_கோவை_source_range (c_கோவை *கோவை,
			 location_t start, location_t finish)
{
  கோவை->src_range.m_start = start;
  கோவை->src_range.m_finish = finish;
  எனில் (கோவை->மதிப்பு)
    set_source_range (கோவை->மதிப்பு, start, finish);
}

வெறுமை
set_c_கோவை_source_range (c_கோவை *கோவை,
			 source_range src_range)
{
  கோவை->src_range = src_range;
  எனில் (கோவை->மதிப்பு)
    set_source_range (கோவை->மதிப்பு, src_range);
}


/* Initialization routine for this file.  */

வெறுமை
c_parse_init (வெறுமை)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  unsigned முழு i;
  மரம் id;
  முழு mask = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  mask |= D_CXXONLY;
  எனில் (!flag_isoc99)
    mask |= D_C99;
  எனில் (!flag_isoc23)
    mask |= D_C23;
  எனில் (flag_no_asm)
    {
      mask |= D_ASM | D_EXT;
      எனில் (!flag_isoc99)
	mask |= D_EXT89;
      எனில் (!flag_isoc23)
	mask |= D_EXT11;
    }
  எனில் (!c_dialect_objc ())
    mask |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<மரம்> ((முழு) RID_MAX);
  க்கு (i = 0; i < இலக்கம்_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      எனில் (c_common_reswords[i].disable & mask)
	{
	  எனில் (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].word);
	      C_SET_RID_CODE (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_WORD (id) = 1;
	    }
	  தொடர்;
	}

      id = get_identifier (c_common_reswords[i].word);
      C_SET_RID_CODE (id, c_common_reswords[i].rid);
      C_IS_RESERVED_WORD (id) = 1;
      ridpointers [(முழு) c_common_reswords[i].rid] = id;
    }

  க்கு (i = 0; i < இலக்கம்_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      எழுத்து name[50];
      sprintf (name, "__int%d", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;

      sprintf (name, "__int%d__", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;
    }

  எனில் (flag_openmp)
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
கட்டமைப்பு GTY(()) c_parser {
  /* The look-ahead tokens.  */
  c_token * GTY((skip)) tokens;
  /* Buffer for look-ahead tokens.  */
  c_token tokens_buf[4];
  /* How many look-ahead tokens are available (0 - 4, or
     more if parsing from pre-lexed tokens).  */
  unsigned முழு tokens_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_tokens;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  unsigned முழு raw_tokens_used;
  /* True if a syntax error is being recovered from; false otherwise.
     c_parser_error sets this flag.  It should clear this flag when
     enough tokens have been consumed to recover from the error.  */
  தருக்க error : 1;
  /* True if we're processing a pragma, and shouldn't automatically
     consume CPP_PRAGMA_EOL.  */
  தருக்க in_pragma : 1;
  /* True if we're parsing the outermost block of an if statement.  */
  தருக்க in_if_block : 1;
  /* True if we want to lex a translated, joined string (for an
     initial #pragma pch_preprocess).  Otherwise the parser is
     responsible for concatenating strings and translating to the
     execution character set as needed.  */
  தருக்க lex_joined_string : 1;
  /* True if, when the parser is concatenating string literals, it
     should translate them to the execution character set (false
     inside attributes).  */
  தருக்க translate_strings_p : 1;

  /* Objective-C specific parser/lexer information.  */

  /* True if we are in a context where the Objective-C "PQ" keywords
     are considered keywords.  */
  தருக்க objc_pq_context : 1;
  /* True if we are parsing a (potential) Objective-C foreach
     statement.  This is set to true after we parsed 'for (' and while
     we wait for 'in' or ';' to decide if it's a standard C for loop or an
     Objective-C foreach loop.  */
  தருக்க objc_could_be_foreach_context : 1;
  /* The following flag is needed to contextualize Objective-C lexical
     analysis.  In some cases (e.g., 'int NSObject;'), it is
     undesirable to bind an identifier to an Objective-C class, even
     if a class with that name exists.  */
  தருக்க objc_need_raw_identifier : 1;
  /* Nonzero if we're processing a __transaction statement.  The value
     is 1 | TM_STMT_ATTR_*.  */
  unsigned முழு in_transaction : 4;
  /* True if we are in a context where the Objective-C "Property attribute"
     keywords are valid.  */
  தருக்க objc_property_attr_context : 1;

  /* Whether we have just seen/constructed a string-literal.  Set when
     returning a string-literal from c_parser_string_literal.  Reset
     in consume_token.  Useful when we get a parse error and see an
     unknown token, which could have been a string-literal constant
     macro.  */
  தருக்க seen_string_literal : 1;

  /* TRUE if omp::directive, omp::decl or omp::sequence attributes may not
     appear.  */
  தருக்க omp_attrs_forbidden_p : 1;

  /* Location of the last consumed token.  */
  location_t last_token_location;

  /* Holds state for parsing collapsed OMP_FOR loops.  Managed by
     c_parser_omp_for_loop.  */
  கட்டமைப்பு omp_for_parse_data * GTY((skip)) omp_for_parse_state;

  /* If we're in the context of OpenMP directives written as C23
     attributes turned into pragma, the tokens field is temporarily
     redirected.  This holds data needed to restore state afterwards.
     It's NULL otherwise.  */
  கட்டமைப்பு omp_attribute_pragma_state *in_omp_attribute_pragma;

  /* Set for omp::decl attribute parsing to the decl to which it
     appertains.  */
  மரம் in_omp_decl_attribute;

  /* Non-null only when parsing the body of an OpenMP metadirective.
     Managed by c_parser_omp_metadirective.  */
  கட்டமைப்பு omp_metadirective_parse_data * GTY((skip))
    omp_metadirective_state;
};

/* Holds data needed to restore the token stream to its previous state
   after parsing an OpenMP attribute-syntax pragma.  */
கட்டமைப்பு GTY(()) omp_attribute_pragma_state
{
  vec<c_token, va_gc> *token_vec;
  c_token * GTY((skip)) save_tokens;
  unsigned முழு save_tokens_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
கட்டமைப்பு GTY(()) omp_begin_declare_variant_map_entry {
  மரம் variant;		/* The variant decl.  */
  மரம் id;		/* Name of base function.  */
  மரம் ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_entry, va_gc> *omp_begin_declare_variant_map;

நிலையான மரம் omp_start_variant_function (c_declarator *, மரம்);
நிலையான வெறுமை omp_finish_variant_function (மரம், மரம், மரம்);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_tokens_buf (c_parser *parser, unsigned n)
{
  திரும்பு &parser->tokens_buf[n];
}

/* Return the error state of PARSER.  */

தருக்க
c_parser_error (c_parser *parser)
{
  திரும்பு parser->error;
}

/* Set the error state of PARSER to ERR.  */

வெறுமை
c_parser_set_error (c_parser *parser, தருக்க err)
{
  parser->error = err;
}


/* The actual parser and external interface.  ??? Does this need to be
   garbage-collected?  */

நிலையான GTY (()) c_parser *the_parser;

/* Read in and lex a single token, storing it in *TOKEN.  If RAW,
   context-sensitive postprocessing of the token is not done.  */

நிலையான வெறுமை
c_lex_one_token (c_parser *parser, c_token *token, தருக்க raw = பொய்)
{
  timevar_தள்ளு (TV_LEX);

  எனில் (raw || vec_safe_length (parser->raw_tokens) == 0)
    {
      token->type = c_lex_with_flags (&token->மதிப்பு, &token->location,
				      &token->flags,
				      (parser->lex_joined_string
				       ? 0 : C_LEX_STRING_NO_JOIN));
      token->id_kind = C_ID_NONE;
      token->keyword = RID_MAX;
      token->pragma_kind = PRAGMA_NONE;
    }
  இல்லையெனில்
    {
      /* Use a token previously lexed as a raw look-ahead token, and
	 complete the processing on it.  */
      *token = (*parser->raw_tokens)[parser->raw_tokens_used];
      ++parser->raw_tokens_used;
      எனில் (parser->raw_tokens_used == vec_safe_length (parser->raw_tokens))
	{
	  vec_free (parser->raw_tokens);
	  parser->raw_tokens_used = 0;
	}
    }

  எனில் (raw)
    செல் out;

  தேர்வு (token->type)
    {
    நிலை CPP_NAME:
      {
	மரம் decl;

	தருக்க objc_force_identifier = parser->objc_need_raw_identifier;
	எனில் (c_dialect_objc ())
	  parser->objc_need_raw_identifier = பொய்;

	எனில் (C_IS_RESERVED_WORD (token->மதிப்பு))
	  {
	    எண்ணிக்கை rid rid_code = C_RID_CODE (token->மதிப்பு);

	    எனில் (rid_code == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->மதிப்பு);
	      }
	    இல்லையெனில் எனில் (rid_code >= RID_FIRST_ADDR_SPACE
		     && rid_code <= RID_LAST_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_code - RID_FIRST_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_kind = C_ID_ADDRSPACE;
		token->keyword = rid_code;
		நிறுத்து;
	      }
	    இல்லையெனில் எனில் (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		எனில் (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    நிறுத்து;
		  }
		இல்லையெனில் எனில் (parser->objc_could_be_foreach_context
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
		    நிறுத்து;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    இல்லையெனில் எனில் (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		எனில் (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    நிறுத்து;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    இல்லையெனில் எனில் (c_dialect_objc ()
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
	    இல்லையெனில்
	      {
		token->type = CPP_KEYWORD;
		token->keyword = rid_code;
		நிறுத்து;
	      }
	  }

	decl = lookup_name (token->மதிப்பு);
	எனில் (decl)
	  {
	    எனில் (மரம்_CODE (decl) == TYPE_DECL)
	      {
		token->id_kind = C_ID_TYPENAME;
		நிறுத்து;
	      }
	  }
	இல்லையெனில் எனில் (c_dialect_objc ())
	  {
	    மரம் objc_interface_decl = objc_is_class_name (token->மதிப்பு);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    எனில் (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->மதிப்பு = objc_interface_decl;
		token->id_kind = C_ID_CLASSNAME;
		நிறுத்து;
	      }
	  }
        token->id_kind = C_ID_ID;
      }
      நிறுத்து;
    நிலை CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      தேர்வு (C_RID_CODE (token->மதிப்பு))
	{
	  /* Replace 'class' with '@class', 'private' with '@private',
	     etc.  This prevents confusion with the C++ keyword
	     'class', and makes the tokens consistent with other
	     Objective-C 'AT' keywords.  For example '@class' is
	     reported as RID_AT_CLASS which is consistent with
	     '@synchronized', which is reported as
	     RID_AT_SYNCHRONIZED.
	  */
	நிலை RID_CLASS:     token->keyword = RID_AT_CLASS; நிறுத்து;
	நிலை RID_PRIVATE:   token->keyword = RID_AT_PRIVATE; நிறுத்து;
	நிலை RID_PROTECTED: token->keyword = RID_AT_PROTECTED; நிறுத்து;
	நிலை RID_PUBLIC:    token->keyword = RID_AT_PUBLIC; நிறுத்து;
	நிலை RID_THROW:     token->keyword = RID_AT_THROW; நிறுத்து;
	நிலை RID_TRY:       token->keyword = RID_AT_TRY; நிறுத்து;
	நிலை RID_CATCH:     token->keyword = RID_AT_CATCH; நிறுத்து;
	நிலை RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; நிறுத்து;
	இயல்பு:            token->keyword = C_RID_CODE (token->மதிப்பு);
	}
      நிறுத்து;
    நிலை CPP_COLON:
    நிலை CPP_COMMA:
    நிலை CPP_CLOSE_PAREN:
    நிலை CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      எனில் (c_dialect_objc ())
	parser->objc_need_raw_identifier = பொய்;
      நிறுத்து;
    நிலை CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_kind = (எண்ணிக்கை pragma_kind) மரம்_INT_CST_கீழ் (token->மதிப்பு);
      token->மதிப்பு = வெற்று;
      நிறுத்து;
    இயல்பு:
      நிறுத்து;
    }
 out:
  timevar_எடு (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  எனில் (parser->tokens_avail == 0)
    {
      c_lex_one_token (parser, &parser->tokens[0]);
      parser->tokens_avail = 1;
    }
  திரும்பு &parser->tokens[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  எனில் (parser->tokens_avail >= 2)
    திரும்பு &parser->tokens[1];
  gcc_assert (parser->tokens_avail == 1);
  gcc_assert (parser->tokens[0].type != CPP_EOF);
  gcc_assert (parser->tokens[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->tokens[1]);
  parser->tokens_avail = 2;
  திரும்பு &parser->tokens[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, unsigned முழு n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  எனில் (parser->tokens_avail >= n)
    திரும்பு &parser->tokens[n - 1];
  gcc_assert (parser->tokens_avail == n - 1);
  c_lex_one_token (parser, &parser->tokens[n - 1]);
  parser->tokens_avail = n;
  திரும்பு &parser->tokens[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, unsigned முழு n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  எனில் (parser->tokens_avail >= n)
    திரும்பு &parser->tokens[n - 1];
  unsigned முழு raw_len = vec_safe_length (parser->raw_tokens);
  unsigned முழு raw_avail
    = parser->tokens_avail + raw_len - parser->raw_tokens_used;
  gcc_assert (raw_avail >= n - 1);
  எனில் (raw_avail >= n)
    திரும்பு &(*parser->raw_tokens)[parser->raw_tokens_used
				  + n - 1 - parser->tokens_avail];
  vec_safe_reserve (parser->raw_tokens, 1);
  parser->raw_tokens->quick_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_tokens)[raw_len], உண்மை);
  திரும்பு &(*parser->raw_tokens)[raw_len];
}

தருக்க
c_keyword_starts_typename (எண்ணிக்கை rid keyword)
{
  தேர்வு (keyword)
    {
    நிலை RID_UNSIGNED:
    நிலை RID_LONG:
    நிலை RID_SHORT:
    நிலை RID_SIGNED:
    நிலை RID_COMPLEX:
    நிலை RID_INT:
    நிலை RID_CHAR:
    நிலை RID_FLOAT:
    நிலை RID_DOUBLE:
    நிலை RID_VOID:
    நிலை RID_DFLOAT32:
    நிலை RID_DFLOAT64:
    நிலை RID_DFLOAT128:
    நிலை RID_DFLOAT64X:
    CASE_RID_FLOATN_NX:
    நிலை RID_BOOL:
    நிலை RID_BITINT:
    நிலை RID_ENUM:
    நிலை RID_STRUCT:
    நிலை RID_UNION:
    நிலை RID_TYPEOF:
    நிலை RID_TYPEOF_UNQUAL:
    நிலை RID_CONST:
    நிலை RID_ATOMIC:
    நிலை RID_VOLATILE:
    நிலை RID_RESTRICT:
    நிலை RID_ATTRIBUTE:
    நிலை RID_FRACT:
    நிலை RID_ACCUM:
    நிலை RID_SAT:
    நிலை RID_AUTO_TYPE:
    நிலை RID_ALIGNAS:
      திரும்பு உண்மை;
    இயல்பு:
      எனில் (keyword >= RID_FIRST_INT_N
	  && keyword < RID_FIRST_INT_N + இலக்கம்_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_FIRST_INT_N])
	திரும்பு உண்மை;
      திரும்பு பொய்;
    }
}

/* Return true if TOKEN can start a type name,
   false otherwise.  */
தருக்க
c_token_starts_typename (c_token *token)
{
  தேர்வு (token->type)
    {
    நிலை CPP_NAME:
      தேர்வு (token->id_kind)
	{
	நிலை C_ID_ID:
	  திரும்பு பொய்;
	நிலை C_ID_ADDRSPACE:
	  திரும்பு உண்மை;
	நிலை C_ID_TYPENAME:
	  திரும்பு உண்மை;
	நிலை C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  திரும்பு உண்மை;
	இயல்பு:
	  gcc_unreachable ();
	}
    நிலை CPP_KEYWORD:
      திரும்பு c_keyword_starts_typename (token->keyword);
    நிலை CPP_LESS:
      எனில் (c_dialect_objc ())
	திரும்பு உண்மை;
      திரும்பு பொய்;
    இயல்பு:
      திரும்பு பொய்;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

நிலையான உள்வரி தருக்க
c_parser_next_tokens_start_typename (c_parser *parser, எண்ணிக்கை c_lookahead_kind la,
				     unsigned முழு n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  எனில் (c_token_starts_typename (token))
    திரும்பு உண்மை;

  /* Try a bit harder to detect an unknown typename.  */
  எனில் (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_kind == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->மதிப்பு))
    திரும்பு உண்மை;

  திரும்பு பொய்;
}

/* Return true if TOKEN, after an open parenthesis, can start a
   compound literal (either a storage class specifier allowed in that
   context, or a type name), false otherwise.  */
நிலையான தருக்க
c_token_starts_compound_literal (c_token *token)
{
  தேர்வு (token->type)
    {
    நிலை CPP_KEYWORD:
      தேர்வு (token->keyword)
	{
	நிலை RID_CONSTEXPR:
	நிலை RID_REGISTER:
	நிலை RID_STATIC:
	நிலை RID_THREAD:
	  திரும்பு உண்மை;
	இயல்பு:
	  நிறுத்து;
	}
      /* Fall through.  */
    இயல்பு:
      திரும்பு c_token_starts_typename (token);
    }
}

/* Return true if TOKEN is a type qualifier, false otherwise.  */
நிலையான தருக்க
c_token_is_qualifier (c_token *token)
{
  தேர்வு (token->type)
    {
    நிலை CPP_NAME:
      தேர்வு (token->id_kind)
	{
	நிலை C_ID_ADDRSPACE:
	  திரும்பு உண்மை;
	இயல்பு:
	  திரும்பு பொய்;
	}
    நிலை CPP_KEYWORD:
      தேர்வு (token->keyword)
	{
	நிலை RID_CONST:
	நிலை RID_VOLATILE:
	நிலை RID_RESTRICT:
	நிலை RID_ATTRIBUTE:
	நிலை RID_ATOMIC:
	  திரும்பு உண்மை;
	இயல்பு:
	  திரும்பு பொய்;
	}
    நிலை CPP_LESS:
      திரும்பு பொய்;
    இயல்பு:
      gcc_unreachable ();
    }
}

/* Return true if the next token from PARSER is a type qualifier,
   false otherwise.  */
நிலையான உள்வரி தருக்க
c_parser_next_token_is_qualifier (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  திரும்பு c_token_is_qualifier (token);
}

/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes), false otherwise.  */
நிலையான தருக்க
c_token_starts_declspecs (c_token *token)
{
  தேர்வு (token->type)
    {
    நிலை CPP_NAME:
      தேர்வு (token->id_kind)
	{
	நிலை C_ID_ID:
	  திரும்பு பொய்;
	நிலை C_ID_ADDRSPACE:
	  திரும்பு உண்மை;
	நிலை C_ID_TYPENAME:
	  திரும்பு உண்மை;
	நிலை C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  திரும்பு உண்மை;
	இயல்பு:
	  gcc_unreachable ();
	}
    நிலை CPP_KEYWORD:
      தேர்வு (token->keyword)
	{
	நிலை RID_STATIC:
	நிலை RID_EXTERN:
	நிலை RID_REGISTER:
	நிலை RID_TYPEDEF:
	நிலை RID_INLINE:
	நிலை RID_NORETURN:
	நிலை RID_AUTO:
	நிலை RID_THREAD:
	நிலை RID_UNSIGNED:
	நிலை RID_LONG:
	நிலை RID_SHORT:
	நிலை RID_SIGNED:
	நிலை RID_COMPLEX:
	நிலை RID_INT:
	நிலை RID_CHAR:
	நிலை RID_FLOAT:
	நிலை RID_DOUBLE:
	நிலை RID_VOID:
	நிலை RID_DFLOAT32:
	நிலை RID_DFLOAT64:
	நிலை RID_DFLOAT128:
	நிலை RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	நிலை RID_BOOL:
	நிலை RID_BITINT:
	நிலை RID_ENUM:
	நிலை RID_STRUCT:
	நிலை RID_UNION:
	நிலை RID_TYPEOF:
	நிலை RID_TYPEOF_UNQUAL:
	நிலை RID_CONST:
	நிலை RID_VOLATILE:
	நிலை RID_RESTRICT:
	நிலை RID_ATTRIBUTE:
	நிலை RID_FRACT:
	நிலை RID_ACCUM:
	நிலை RID_SAT:
	நிலை RID_ALIGNAS:
	நிலை RID_ATOMIC:
	நிலை RID_AUTO_TYPE:
	நிலை RID_CONSTEXPR:
	  திரும்பு உண்மை;
	இயல்பு:
	  எனில் (token->keyword >= RID_FIRST_INT_N
	      && token->keyword < RID_FIRST_INT_N + இலக்கம்_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_FIRST_INT_N])
	    திரும்பு உண்மை;
	  திரும்பு பொய்;
	}
    நிலை CPP_LESS:
      எனில் (c_dialect_objc ())
	திரும்பு உண்மை;
      திரும்பு பொய்;
    இயல்பு:
      திரும்பு பொய்;
    }
}


/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes) or a static assertion, false
   otherwise.  */
நிலையான தருக்க
c_token_starts_declaration (c_token *token)
{
  எனில் (c_token_starts_declspecs (token)
      || token->keyword == RID_STATIC_ASSERT)
    திரும்பு உண்மை;
  இல்லையெனில்
    திரும்பு பொய்;
}

/* Return true if the next token from PARSER can start declaration
   specifiers (not including standard attributes), false
   otherwise.  */
தருக்க
c_parser_next_token_starts_declspecs (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);

  /* In Objective-C, a classname normally starts a declspecs unless it
     is immediately followed by a dot.  In that case, it is the
     Objective-C 2.0 "dot-syntax" for class objects, ie, calls the
     setter/getter on the class.  c_token_starts_declspecs() can't
     differentiate between the two cases because it only checks the
     current token, so we have a special check here.  */
  எனில் (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    திரும்பு பொய்;

  திரும்பு c_token_starts_declspecs (token);
}

நிலையான தருக்க c_parser_check_balanced_raw_token_sequence (c_parser *,
							unsigned முழு *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
தருக்க
c_parser_next_tokens_start_declaration (c_parser *parser, unsigned முழு n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  எனில் (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_DOT)
    திரும்பு பொய்;

  /* Labels do not start declarations.  */
  எனில் (token->type == CPP_NAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_COLON)
    திரும்பு பொய்;

  /* A static assertion is only a declaration if followed by a semicolon;
     otherwise, it may be an expression in C2Y.  */
  எனில் (token->keyword == RID_STATIC_ASSERT
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_PAREN)
    {
      n += 2;
      எனில் (!c_parser_check_balanced_raw_token_sequence (parser, &n)
	  || c_parser_peek_nth_token_raw (parser, n)->type != CPP_CLOSE_PAREN)
	/* Invalid static assertion syntax; treat as a declaration and report a
	   syntax error there.  */
	திரும்பு உண்மை;
      திரும்பு c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  எனில் (c_token_starts_declaration (token))
    திரும்பு உண்மை;

  எனில் (c_parser_next_tokens_start_typename (parser, cla_nonabstract_decl, n))
    திரும்பு உண்மை;

  திரும்பு பொய்;
}

/* Consume the next token from PARSER.  */

வெறுமை
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
  எனில் (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  இல்லையெனில் எனில் (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      எனில் (parser->tokens_avail >= 3)
        {
          parser->tokens[1] = parser->tokens[2];
          எனில் (parser->tokens_avail >= 4)
            parser->tokens[2] = parser->tokens[3];
        }
    }
  parser->tokens_avail--;
  parser->seen_string_literal = பொய்;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

நிலையான வெறுமை
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->in_pragma);
  gcc_assert (parser->tokens_avail >= 1);
  gcc_assert (parser->tokens[0].type == CPP_PRAGMA);
  எனில் (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  இல்லையெனில் எனில் (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      எனில் (parser->tokens_avail >= 3)
	parser->tokens[1] = parser->tokens[2];
    }
  parser->tokens_avail--;
  parser->in_pragma = உண்மை;
}

/* Update the global input_location from TOKEN.  */
நிலையான உள்வரி வெறுமை
c_parser_set_source_position_from_token (c_token *token)
{
  எனில் (token->type != CPP_EOF)
    {
      உள்ளீடு_location = token->location;
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

நிலையான தருக்க
c_parser_peek_conflict_marker (c_parser *parser, எண்ணிக்கை cpp_ttype tok1_kind,
			       location_t *out_loc)
{
  c_token *token2 = c_parser_peek_2nd_token (parser);
  எனில் (token2->type != tok1_kind)
    திரும்பு பொய்;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  எனில் (token3->type != tok1_kind)
    திரும்பு பொய்;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  எனில் (token4->type != conflict_marker_get_final_tok_kind (tok1_kind))
    திரும்பு பொய்;

  /* It must be at the start of the line.  */
  location_t start_loc = c_parser_peek_token (parser)->location;
  எனில் (LOCATION_COLUMN (start_loc) != 1)
    திரும்பு பொய்;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t finish_loc = get_finish (token4->location);
  *out_loc = make_location (start_loc, start_loc, finish_loc);

  திரும்பு உண்மை;
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

நிலையான தருக்க
c_parser_error_richloc (c_parser *parser, மாறிலி எழுத்து *gmsgid,
			rich_location *richloc)
{
  c_token *token = c_parser_peek_token (parser);
  எனில் (parser->error)
    திரும்பு பொய்;
  parser->error = உண்மை;
  எனில் (!gmsgid)
    திரும்பு பொய்;

  /* If this is actually a conflict marker, report it as such.  */
  எனில் (token->type == CPP_LSHIFT
      || token->type == CPP_RSHIFT
      || token->type == CPP_EQ_EQ)
    {
      location_t loc;
      எனில் (c_parser_peek_conflict_marker (parser, token->type, &loc))
	{
	  error_at (loc, "version control conflict marker in file");
	  திரும்பு உண்மை;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_group d;
  name_hint h;
  எனில் (parser->seen_string_literal && token->type == CPP_NAME)
    {
      மரம் name = token->மதிப்பு;
      மாறிலி எழுத்து *token_name = IDENTIFIER_POINTER (name);
      மாறிலி எழுத்து *header_hint
	= get_c_stdlib_header_for_string_macro_name (token_name);
      எனில் (header_hint != வெற்று)
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
		 token->மதிப்பு, /*flags=*/0, richloc);
  திரும்பு உண்மை;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

தருக்க
c_parser_error (c_parser *parser, மாறிலி எழுத்து *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_set_source_position_from_token (token);
  rich_location richloc (வரி_table, உள்ளீடு_location);
  திரும்பு c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

template <typename traits_t>
வகுப்பு token_pair
{
 பொது:
  /* token_pair's ctor.  */
  token_pair () : m_open_loc (UNKNOWN_LOCATION) {}

  /* If the next token is the opening symbol for this pair, consume it and
     return true.
     Otherwise, issue an error and return false.
     In either case, record the location of the opening token.  */

  தருக்க require_open (c_parser *parser)
  {
    c_token *token = c_parser_peek_token (parser);
    எனில் (token)
      m_open_loc = token->location;

    திரும்பு c_parser_require (parser, traits_t::open_token_type,
			     traits_t::open_gmsgid);
  }

  /* Consume the next token from PARSER, recording its location as
     that of the opening token within the pair.  */

  வெறுமை consume_open (c_parser *parser)
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

  தருக்க require_close (c_parser *parser) மாறிலி
  {
    திரும்பு c_parser_require (parser, traits_t::close_token_type,
			     traits_t::close_gmsgid, m_open_loc);
  }

  /* Like token_pair::require_close, except that tokens will be skipped
     until the desired token is found.  An error message is still produced
     if the next token is not as expected.  */

  வெறுமை skip_until_found_close (c_parser *parser) மாறிலி
  {
    c_parser_skip_until_found (parser, traits_t::close_token_type,
			       traits_t::close_gmsgid, m_open_loc);
  }

 தனிப்பட்ட:
  location_t m_open_loc;
};

/* Traits for token_pair<T> for tracking matching pairs of parentheses.  */

கட்டமைப்பு matching_paren_traits
{
  நிலையான மாறிலி எண்ணிக்கை cpp_ttype open_token_type = CPP_OPEN_PAREN;
  நிலையான மாறிலி எழுத்து * மாறிலி open_gmsgid;
  நிலையான மாறிலி எண்ணிக்கை cpp_ttype close_token_type = CPP_CLOSE_PAREN;
  நிலையான மாறிலி எழுத்து * மாறிலி close_gmsgid;
};

மாறிலி எழுத்து * மாறிலி matching_paren_traits::open_gmsgid = "expected %<(%>";
மாறிலி எழுத்து * மாறிலி matching_paren_traits::close_gmsgid = "expected %<)%>";

/* "matching_parens" is a token_pair<T> class for tracking matching
   pairs of parentheses.  */

வகைவரை token_pair<matching_paren_traits> matching_parens;

/* Traits for token_pair<T> for tracking matching pairs of braces.  */

கட்டமைப்பு matching_brace_traits
{
  நிலையான மாறிலி எண்ணிக்கை cpp_ttype open_token_type = CPP_OPEN_BRACE;
  நிலையான மாறிலி எழுத்து * மாறிலி open_gmsgid;
  நிலையான மாறிலி எண்ணிக்கை cpp_ttype close_token_type = CPP_CLOSE_BRACE;
  நிலையான மாறிலி எழுத்து * மாறிலி close_gmsgid;
};

மாறிலி எழுத்து * மாறிலி matching_brace_traits::open_gmsgid = "expected %<{%>";
மாறிலி எழுத்து * மாறிலி matching_brace_traits::close_gmsgid = "expected %<}%>";

/* "matching_braces" is a token_pair<T> class for tracking matching
   pairs of braces.  */

வகைவரை token_pair<matching_brace_traits> matching_braces;

/* Get a description of the matching symbol to TYPE e.g. "(" for
   CPP_CLOSE_PAREN.  */

நிலையான மாறிலி எழுத்து *
get_matching_குறியீடு (எண்ணிக்கை cpp_ttype type)
{
  தேர்வு (type)
    {
    இயல்பு:
      gcc_unreachable ();
    நிலை CPP_CLOSE_PAREN:
      திரும்பு "(";
    நிலை CPP_CLOSE_BRACE:
      திரும்பு "{";
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

தருக்க
c_parser_require (c_parser *parser,
		  எண்ணிக்கை cpp_ttype type,
		  மாறிலி எழுத்து *msgid,
		  location_t matching_location,
		  தருக்க type_is_unique)
{
  எனில் (c_parser_next_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      திரும்பு உண்மை;
    }
  இல்லையெனில்
    {
      location_t next_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (next_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      எனில் (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->last_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      தருக்க added_matching_location = பொய்;
      எனில் (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.add_location_if_nearby (*global_dc, matching_location);

      எனில் (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	எனில் (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_குறியீடு (type));

      திரும்பு பொய்;
    }
}

/* If the next token is the indicated keyword, consume it.  Otherwise,
   issue the error MSGID.  Returns true if found, false otherwise.  */

நிலையான தருக்க
c_parser_require_keyword (c_parser *parser,
			  எண்ணிக்கை rid keyword,
			  மாறிலி எழுத்து *msgid)
{
  எனில் (c_parser_next_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      திரும்பு உண்மை;
    }
  இல்லையெனில்
    {
      c_parser_error (parser, msgid);
      திரும்பு பொய்;
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

வெறுமை
c_parser_skip_until_found (c_parser *parser,
			   எண்ணிக்கை cpp_ttype type,
			   மாறிலி எழுத்து *msgid,
			   location_t matching_location)
{
  unsigned nesting_depth = 0;

  எனில் (c_parser_require (parser, type, msgid, matching_location))
    {
      எனில் (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->in_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  எனில் (token->type == CPP_EOF)
	    {
	      parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	      parser->tokens_avail
		= parser->in_omp_attribute_pragma->save_tokens_avail;
	      parser->in_omp_attribute_pragma = வெற்று;
	    }
	}
      திரும்பு;
    }

  /* Skip tokens until the desired token is found.  */
  போது (உண்மை)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      எனில் (token->type == type && !nesting_depth)
	{
	  c_parser_consume_token (parser);
	  எனில் (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->in_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      எனில் (token->type == CPP_EOF)
		{
		  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
		  parser->tokens_avail
		    = parser->in_omp_attribute_pragma->save_tokens_avail;
		  parser->in_omp_attribute_pragma = வெற்று;
		}
	    }
	  நிறுத்து;
	}

      /* If we've run out of tokens, stop.  */
      எனில் (token->type == CPP_EOF)
	திரும்பு;
      எனில் (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	திரும்பு;
      எனில் (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      இல்லையெனில் எனில் (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  எனில் (nesting_depth-- == 0)
	    நிறுத்து;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = பொய்;
}

/* Skip tokens until the end of a parameter is found, but do not
   consume the comma, semicolon or closing delimiter.  */

நிலையான வெறுமை
c_parser_skip_to_end_of_parameter (c_parser *parser)
{
  unsigned nesting_depth = 0;

  போது (உண்மை)
    {
      c_token *token = c_parser_peek_token (parser);
      எனில் ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_depth)
	நிறுத்து;
      /* If we've run out of tokens, stop.  */
      எனில் (token->type == CPP_EOF)
	திரும்பு;
      எனில் (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	திரும்பு;
      எனில் (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      இல்லையெனில் எனில் (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  எனில் (nesting_depth-- == 0)
	    நிறுத்து;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = பொய்;
}

/* Skip tokens until a non-nested closing curly brace is the next
   token, or there are no more tokens. Return true in the first case,
   false otherwise.  */

நிலையான தருக்க
c_parser_skip_to_closing_brace (c_parser *parser)
{
  unsigned nesting_depth = 0;

  போது (உண்மை)
    {
      c_token *token = c_parser_peek_token (parser);

      தேர்வு (token->type)
	{
	நிலை CPP_PRAGMA_EOL:
	  எனில் (!parser->in_pragma)
	    நிறுத்து;
	  /* FALLTHRU */
	நிலை CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  திரும்பு பொய்;

	நிலை CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  எனில் (nesting_depth-- == 0)
	    திரும்பு உண்மை;
	  நிறுத்து;

	நிலை CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  நிறுத்து;

	இயல்பு:
	  நிறுத்து;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Expect to be at the end of the pragma directive and consume an
   end of line marker.  */

நிலையான வெறுமை
c_parser_skip_to_pragma_eol (c_parser *parser, தருக்க error_if_not_eol = உண்மை)
{
  gcc_assert (parser->in_pragma);
  parser->in_pragma = பொய்;

  எனில் (error_if_not_eol && c_parser_peek_token (parser)->type != CPP_PRAGMA_EOL)
    c_parser_error (parser, "expected end of line");

  cpp_ttype token_type;
  செய்
    {
      c_token *token = c_parser_peek_token (parser);
      token_type = token->type;
      எனில் (token_type == CPP_EOF)
	நிறுத்து;
      c_parser_consume_token (parser);
    }
  போது (token_type != CPP_PRAGMA_EOL);

  எனில் (parser->in_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      எனில் (token->type == CPP_EOF)
	{
	  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	  parser->tokens_avail
	    = parser->in_omp_attribute_pragma->save_tokens_avail;
	  parser->in_omp_attribute_pragma = வெற்று;
	}
    }

  parser->error = பொய்;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
நிலையான வெறுமை
c_parser_skip_to_pragma_omp_end_declare_variant (c_parser *parser)
{
  க்கு (முழு depth = 0; depth >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      தேர்வு (token->type)
	{
	நிலை CPP_PRAGMA_EOL:
	  எனில் (!parser->in_pragma)
	    நிறுத்து;
	  /* FALLTHRU */
	நிலை CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  திரும்பு;

	நிலை CPP_PRAGMA:
	  எனில் ((token->pragma_kind == PRAGMA_OMP_BEGIN
	       || token->pragma_kind == PRAGMA_OMP_END)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      மரம் id1 = c_parser_peek_nth_token (parser, 2)->மதிப்பு;
	      மரம் id2 = c_parser_peek_nth_token (parser, 3)->மதிப்பு;
	      எனில் (strcmp (IDENTIFIER_POINTER (id1), "declare") == 0
		  && strcmp (IDENTIFIER_POINTER (id2), "variant") == 0)
		{
		  எனில் (token->pragma_kind == PRAGMA_OMP_BEGIN)
		    depth++;
		  இல்லையெனில்
		    depth--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, பொய்);
	  தொடர்;

	இயல்பு:
	  நிறுத்து;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Skip tokens until we have consumed an entire block, or until we
   have consumed a non-nested ';'.  */

நிலையான வெறுமை
c_parser_skip_to_end_of_block_or_statement (c_parser *parser,
					    தருக்க metadirective_p = பொய்)
{
  unsigned nesting_depth = 0;
  முழு bracket_depth = 0;
  தருக்க save_error = parser->error;

  போது (உண்மை)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      தேர்வு (token->type)
	{
	நிலை CPP_EOF:
	  திரும்பு;

	நிலை CPP_PRAGMA_EOL:
	  எனில் (parser->in_pragma)
	    திரும்பு;
	  நிறுத்து;

	நிலை CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  எனில் (!nesting_depth && (!metadirective_p || bracket_depth <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      செல் finished;
	    }
	  நிறுத்து;

	நிலை CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  எனில் ((nesting_depth == 0 || --nesting_depth == 0)
	      && (!metadirective_p || bracket_depth <= 0))
	    {
	      c_parser_consume_token (parser);
	      செல் finished;
	    }
	  நிறுத்து;

	நிலை CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  நிறுத்து;

	நிலை CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  எனில் (metadirective_p && nesting_depth == 0)
	    ++bracket_depth;
	  நிறுத்து;

	நிலை CPP_CLOSE_PAREN:
	  எனில் (metadirective_p && nesting_depth == 0)
	    --bracket_depth;
	  நிறுத்து;

	நிலை CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, பொய்);
	  parser->error = save_error;
	  தொடர்;

	இயல்பு:
	  நிறுத்து;
	}

      c_parser_consume_token (parser);
    }

 finished:
  parser->error = பொய்;
}

/* CPP's options (initialized by c-opts.cc).  */
வெளி cpp_options *cpp_opts;

/* Save the warning flags which are controlled by __extension__.  */

நிலையான உள்வரி முழு
disable_extension_diagnostics (வெறுமை)
{
  முழு ret = (pedantic
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
  திரும்பு ret;
}

/* Restore the warning flags which are controlled by __extension__.
   FLAGS is the return value from disable_extension_diagnostics.  */

நிலையான உள்வரி வெறுமை
restore_extension_diagnostics (முழு flags)
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
கட்டமைப்பு oacc_routine_data {
  தருக்க error_seen; /* Set if error has been reported.  */
  தருக்க fndecl_seen; /* Set if one fn decl/definition has been seen already.  */
  மரம் clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
நிலையான மரம் objc_foreach_break_label, objc_foreach_continue_label;

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
கட்டமைப்பு omp_for_parse_data {
  எண்ணிக்கை மரம்_code code;
  மரம் declv, condv, incrv, initv;
  மரம் pre_body;
  மரம் bindings;
  முழு மொத்தம்;	/* Expected nesting depth.  */
  முழு depth;	/* Current nesting depth.  */
  location_t for_loc;
  தருக்க ordered : 1;
  தருக்க inscan : 1;
  தருக்க want_nested_loop : 1;
  தருக்க in_intervening_code : 1;
  தருக்க saw_intervening_code: 1;
  தருக்க perfect_nesting_fail : 1;
  தருக்க fail : 1;
};

கட்டமைப்பு attr_state
{
  /* True if we parsed a musttail attribute for return.  */
  தருக்க musttail_p;

  வெறுமை reset () { musttail_p = பொய்; }
};

நிலையான தருக்க c_parser_nth_token_starts_std_attributes (c_parser *,
						      unsigned முழு);
நிலையான மரம் c_parser_std_attribute_specifier_sequence (c_parser *);
நிலையான வெறுமை c_parser_external_declaration (c_parser *);
நிலையான வெறுமை c_parser_asm_definition (c_parser *);
நிலையான மரம் c_parser_declaration_or_fndef (c_parser *, தருக்க, தருக்க, தருக்க,
					   தருக்க, தருக்க, தருக்க, மரம் * = வெற்று,
					   vec<c_token> * = வெற்று,
					   தருக்க have_attrs = பொய்,
					   மரம் attrs = வெற்று,
					   கட்டமைப்பு oacc_routine_data * = வெற்று,
					   தருக்க * = வெற்று);
நிலையான தருக்க c_parser_handle_statement_omp_attributes (c_parser *, மரம் &,
						      தருக்க *);
நிலையான வெறுமை c_parser_static_assert_declaration_no_semi (c_parser *);
நிலையான வெறுமை c_parser_static_assert_declaration (c_parser *);
நிலையான கட்டமைப்பு c_typespec c_parser_enum_specifier (c_parser *);
நிலையான கட்டமைப்பு c_typespec c_parser_struct_or_union_specifier (c_parser *);
நிலையான மரம் c_parser_struct_declaration (c_parser *, மரம் *);
நிலையான கட்டமைப்பு c_typespec c_parser_typeof_specifier (c_parser *);
நிலையான மரம் c_parser_alignas_specifier (c_parser *);
நிலையான கட்டமைப்பு c_declarator *c_parser_direct_declarator (c_parser *, தருக்க,
							c_dtr_syn, தருக்க *);
நிலையான கட்டமைப்பு c_declarator *c_parser_direct_declarator_inner (c_parser *,
							      தருக்க,
							      கட்டமைப்பு c_declarator *);
நிலையான கட்டமைப்பு c_arg_info *c_parser_parms_declarator (c_parser *, தருக்க, மரம்,
						     தருக்க);
நிலையான கட்டமைப்பு c_arg_info *c_parser_parms_list_declarator (c_parser *, மரம்,
							  மரம், தருக்க);
நிலையான கட்டமைப்பு c_parm *c_parser_parameter_declaration (c_parser *, மரம், தருக்க);
நிலையான மரம் c_parser_asm_string_literal (c_parser *);
நிலையான மரம் c_parser_simple_asm_கோவை (c_parser *);
நிலையான மரம் c_parser_gnu_attributes (c_parser *);
நிலையான கட்டமைப்பு c_கோவை c_parser_initializer (c_parser *, மரம்);
நிலையான கட்டமைப்பு c_கோவை c_parser_braced_init (c_parser *, மரம், தருக்க,
					   கட்டமைப்பு obstack *, தருக்க);
நிலையான வெறுமை c_parser_initelt (c_parser *, கட்டமைப்பு obstack *);
நிலையான வெறுமை c_parser_initval (c_parser *, கட்டமைப்பு c_கோவை *,
			      கட்டமைப்பு obstack *);
நிலையான மரம் c_parser_compound_statement (c_parser *, location_t * = வெற்று);
நிலையான location_t c_parser_compound_statement_nostart (c_parser *);
நிலையான வெறுமை c_parser_label (c_parser *, மரம்);
நிலையான வெறுமை c_parser_statement (c_parser *, தருக்க *, location_t * = வெற்று);
நிலையான வெறுமை c_parser_statement_after_labels (c_parser *, தருக்க *, மரம்,
					     vec<மரம்> * = வெற்று,
					     attr_state = {});
நிலையான மரம் c_parser_c99_block_statement (c_parser *, தருக்க *,
					  location_t * = வெற்று);
நிலையான வெறுமை c_parser_if_statement (c_parser *, தருக்க *, vec<மரம்> *);
நிலையான வெறுமை c_parser_switch_statement (c_parser *, தருக்க *, மரம்);
நிலையான வெறுமை c_parser_while_statement (c_parser *, தருக்க, unsigned short, தருக்க,
				      தருக்க *, மரம்);
நிலையான வெறுமை c_parser_do_statement (c_parser *, தருக்க, unsigned short, தருக்க,
				   மரம்);
நிலையான வெறுமை c_parser_for_statement (c_parser *, தருக்க, unsigned short, தருக்க,
				    தருக்க *, மரம்);
நிலையான மரம் c_parser_asm_statement (c_parser *);
நிலையான மரம் c_parser_asm_operands (c_parser *);
நிலையான மரம் c_parser_asm_goto_operands (c_parser *);
நிலையான மரம் c_parser_asm_clobbers (c_parser *);
நிலையான கட்டமைப்பு c_கோவை c_parser_கோவை_no_commas (c_parser *, கட்டமைப்பு c_கோவை *,
					      மரம் = NULL_மரம்);
நிலையான கட்டமைப்பு c_கோவை c_parser_conditional_expression (c_parser *,
						      கட்டமைப்பு c_கோவை *, மரம்);
நிலையான கட்டமைப்பு c_கோவை c_parser_இருமம்_expression (c_parser *, கட்டமைப்பு c_கோவை *,
						 மரம்);
நிலையான கட்டமைப்பு c_கோவை c_parser_cast_expression (c_parser *, கட்டமைப்பு c_கோவை *);
நிலையான கட்டமைப்பு c_கோவை c_parser_unary_expression (c_parser *);
நிலையான கட்டமைப்பு c_கோவை c_parser_sizeof_or_countof_expression (c_parser *,
							    எண்ணிக்கை rid);
நிலையான கட்டமைப்பு c_கோவை c_parser_alignof_expression (c_parser *);
நிலையான கட்டமைப்பு c_கோவை c_parser_maxof_or_minof_expression (c_parser *, எண்ணிக்கை rid);
நிலையான கட்டமைப்பு c_கோவை c_parser_postfix_expression (c_parser *);
நிலையான கட்டமைப்பு c_கோவை c_parser_postfix_expression_after_paren_type (c_parser *,
								   கட்டமைப்பு c_declspecs *,
								   கட்டமைப்பு c_type_name *,
								   location_t);
நிலையான கட்டமைப்பு c_கோவை c_parser_postfix_expression_after_primary (c_parser *,
								location_t loc,
								கட்டமைப்பு c_கோவை);
நிலையான மரம் c_parser_transaction (c_parser *, எண்ணிக்கை rid);
நிலையான கட்டமைப்பு c_கோவை c_parser_transaction_expression (c_parser *, எண்ணிக்கை rid);
நிலையான மரம் c_parser_transaction_cancel (c_parser *);
நிலையான கட்டமைப்பு c_கோவை c_parser_expression (c_parser *);
நிலையான கட்டமைப்பு c_கோவை c_parser_expression_conv (c_parser *);
நிலையான vec<மரம், va_gc> *c_parser_கோவை_list (c_parser *, தருக்க, தருக்க,
					     vec<மரம், va_gc> **, location_t *,
					     மரம் *, vec<location_t> *,
					     unsigned முழு * = வெற்று);
நிலையான கட்டமைப்பு c_கோவை c_parser_has_attribute_expression (c_parser *);

நிலையான வெறுமை c_parser_oacc_declare (c_parser *);
நிலையான வெறுமை c_parser_oacc_enter_exit_data (c_parser *, தருக்க);
நிலையான வெறுமை c_parser_oacc_update (c_parser *);
நிலையான வெறுமை c_parser_omp_construct (c_parser *, தருக்க *);
நிலையான வெறுமை c_parser_omp_groupprivate (c_parser *);
நிலையான வெறுமை c_parser_omp_threadprivate (c_parser *);
நிலையான வெறுமை c_parser_omp_barrier (c_parser *);
நிலையான வெறுமை c_parser_omp_depobj (c_parser *);
நிலையான வெறுமை c_parser_omp_flush (c_parser *);
நிலையான தருக்க c_parser_omp_next_tokens_can_be_canon_loop (c_parser *,
							எண்ணிக்கை மரம்_code, தருக்க);
நிலையான மரம் c_parser_omp_loop_nest (c_parser *, தருக்க *);
நிலையான மரம் c_parser_omp_for_loop (location_t, c_parser *, எண்ணிக்கை மரம்_code,
				   மரம், மரம் *, தருக்க *);
நிலையான வெறுமை c_parser_omp_taskwait (c_parser *);
நிலையான வெறுமை c_parser_omp_taskyield (c_parser *);
நிலையான வெறுமை c_parser_omp_cancel (c_parser *);
நிலையான வெறுமை c_parser_omp_nothing (c_parser *);
நிலையான வெறுமை c_parser_omp_metadirective (c_parser *, தருக்க *);

எண்ணிக்கை pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
நிலையான தருக்க c_parser_pragma (c_parser *, எண்ணிக்கை pragma_context, தருக்க *, மரம்);
நிலையான தருக்க c_parser_omp_cancellation_point (c_parser *, எண்ணிக்கை pragma_context);
நிலையான தருக்க c_parser_omp_target (c_parser *, எண்ணிக்கை pragma_context, தருக்க *);
நிலையான வெறுமை c_parser_omp_begin (c_parser *);
நிலையான வெறுமை c_parser_omp_end (c_parser *);
நிலையான தருக்க c_parser_omp_declare (c_parser *, எண்ணிக்கை pragma_context);
நிலையான வெறுமை c_parser_omp_requires (c_parser *);
நிலையான தருக்க c_parser_omp_error (c_parser *, எண்ணிக்கை pragma_context);
நிலையான வெறுமை c_parser_omp_assumption_clauses (c_parser *, தருக்க);
நிலையான வெறுமை c_parser_omp_allocate (c_parser *);
நிலையான வெறுமை c_parser_omp_assumes (c_parser *);
நிலையான தருக்க c_parser_omp_ordered (c_parser *, எண்ணிக்கை pragma_context, தருக்க *);
நிலையான மரம் c_parser_omp_dispatch (location_t, c_parser *);
நிலையான வெறுமை c_parser_omp_interop (c_parser *);
நிலையான வெறுமை c_parser_oacc_routine (c_parser *, எண்ணிக்கை pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
நிலையான வெறுமை c_parser_objc_class_definition (c_parser *, மரம்);
நிலையான வெறுமை c_parser_objc_class_instance_variables (c_parser *);
நிலையான வெறுமை c_parser_objc_class_declaration (c_parser *);
நிலையான வெறுமை c_parser_objc_alias_declaration (c_parser *);
நிலையான வெறுமை c_parser_objc_protocol_definition (c_parser *, மரம்);
நிலையான தருக்க c_parser_objc_method_type (c_parser *);
நிலையான வெறுமை c_parser_objc_method_definition (c_parser *);
நிலையான வெறுமை c_parser_objc_methodprotolist (c_parser *);
நிலையான வெறுமை c_parser_objc_methodproto (c_parser *);
நிலையான மரம் c_parser_objc_method_decl (c_parser *, தருக்க, மரம் *, மரம் *);
நிலையான மரம் c_parser_objc_type_name (c_parser *);
நிலையான மரம் c_parser_objc_protocol_refs (c_parser *);
நிலையான வெறுமை c_parser_objc_try_catch_finally_statement (c_parser *);
நிலையான வெறுமை c_parser_objc_synchronized_statement (c_parser *);
நிலையான மரம் c_parser_objc_selector (c_parser *);
நிலையான மரம் c_parser_objc_selector_arg (c_parser *);
நிலையான மரம் c_parser_objc_receiver (c_parser *);
நிலையான மரம் c_parser_objc_message_args (c_parser *);
நிலையான மரம் c_parser_objc_keywordexpr (c_parser *);
நிலையான வெறுமை c_parser_objc_at_property_declaration (c_parser *);
நிலையான வெறுமை c_parser_objc_at_synthesize_declaration (c_parser *);
நிலையான வெறுமை c_parser_objc_at_dynamic_declaration (c_parser *);
நிலையான தருக்க c_parser_objc_diagnose_bad_element_prefix
  (c_parser *, கட்டமைப்பு c_declspecs *);
நிலையான location_t c_parser_parse_rtl_body (c_parser *, எழுத்து *);
நிலையான மரம் c_parser_handle_musttail (c_parser *, மரம், attr_state &);

#எனில் ENABLE_ANALYZER

நாமாகாஶ ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

வகுப்பு c_translation_unit : பொது translation_unit
{
பொது:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  மரம் lookup_constant_by_id (மரம் id) மாறிலி final override
  {
    /* Consider decls.  */
    எனில் (மரம் decl = lookup_name (id))
      எனில் (மரம்_CODE (decl) == CONST_DECL)
	எனில் (மரம் மதிப்பு = DECL_INITIAL (decl))
	  எனில் (மரம்_CODE (மதிப்பு) == INTEGER_CST)
	    திரும்பு மதிப்பு;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    எனில் (cpp_macro_p (hashnode))
      எனில் (மரம் மதிப்பு = consider_macro (hashnode->மதிப்பு.macro))
	திரும்பு மதிப்பு;

    திரும்பு NULL_மரம்;
  }

  மரம்
  lookup_type_by_id (மரம் id) மாறிலி final override
  {
    எனில் (மரம் type_decl = lookup_name (id))
	எனில் (மரம்_CODE (type_decl) == TYPE_DECL)
	  {
	    மரம் record_type = மரம்_TYPE (type_decl);
	    எனில் (மரம்_CODE (record_type) == RECORD_TYPE)
	      திரும்பு record_type;
	  }

    திரும்பு NULL_மரம்;
  }

  மரம்
  lookup_global_var_by_id (மரம் id) மாறிலி final override
  {
    எனில் (மரம் var_decl = lookup_name (id))
      எனில் (மரம்_CODE (var_decl) == VAR_DECL)
				திரும்பு var_decl;

    திரும்பு NULL_மரம்;
  }

தனிப்பட்ட:
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
  மரம் consider_macro (cpp_macro *macro, முழு depth = 0) மாறிலி
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (depth >= 0);

    எனில் (macro->paramc > 0)
      திரும்பு NULL_மரம்;
    எனில் (macro->kind != cmk_macro)
      திரும்பு NULL_மரம்;
    எனில் (macro->மொத்தம் != 1)
      திரும்பு NULL_மரம்;
    மாறிலி cpp_token &tok = macro->exp.tokens[0];
    எனில் (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	எனில் (depth >= param_analyzer_max_macro_alias_depth)
	  திரும்பு NULL_மரம்;

	cpp_hashnode *alias = tok.val.முனை.முனை;
	எனில் (cpp_macro_p (alias))
	  திரும்பு consider_macro (alias->மதிப்பு.macro, depth + 1);

	/* Not a simple alias.  */
	திரும்பு NULL_மரம்;
      }
    இல்லையெனில் எனில் (tok.type != CPP_எண்)
      திரும்பு NULL_மரம்;

    cpp_reader *old_parse_in = parse_in;
    parse_in = cpp_create_reader (CLK_GNUC89, வெற்று, வரி_table);

    pretty_printer pp;
    pp_string (&pp, (மாறிலி எழுத்து *) tok.val.str.text);
    pp_newline (&pp);
    cpp_தள்ளு_buffer (parse_in,
		     (மாறிலி unsigned எழுத்து *) pp_formatted_text (&pp),
		     strlen (pp_formatted_text (&pp)),
		     0);

    மரம் மதிப்பு;
    location_t loc;
    unsigned எழுத்து cpp_flags;
    c_lex_with_flags (&மதிப்பு, &loc, &cpp_flags, 0);

    cpp_destroy (parse_in);
    parse_in = old_parse_in;

    எனில் (மதிப்பு && மரம்_CODE (மதிப்பு) == INTEGER_CST)
      திரும்பு மதிப்பு;

    திரும்பு NULL_மரம்;
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

நிலையான வெறுமை
c_parser_translation_unit (c_parser *parser)
{
  எனில் (c_parser_next_token_is (parser, CPP_EOF))
    {
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C forbids an empty translation unit");
    }
  இல்லையெனில்
    {
      வெறுமை *obstack_position = obstack_alloc (&parser_obstack, 0);
      mark_valid_location_for_stdc_pragma (பொய்);
      செய்
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      போது (c_parser_next_token_is_not (parser, CPP_EOF));
    }

  unsigned முழு i;
  மரம் decl;
  FOR_EACH_VEC_ELT (incomplete_record_decls, i, decl)
    எனில் (DECL_SIZE (decl) == NULL_மரம் && மரம்_TYPE (decl) != error_mark_முனை)
      error ("storage size of %q+D isn%'t known", decl);

  எனில் (vec_safe_length (current_omp_declare_target_attribute))
    {
      c_omp_declare_target_attr
	a = current_omp_declare_target_attribute->எடு ();
      எனில் (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_safe_truncate (current_omp_declare_target_attribute, 0);
    }
  எனில் (vec_safe_length (current_omp_begin_assumes))
    {
      எனில் (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_safe_truncate (current_omp_begin_assumes, 0);
    }
  எனில் (vec_safe_length (current_omp_declare_variant_attribute))
    {
      எனில் (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_safe_truncate (current_omp_declare_variant_attribute, 0);
    }
  எனில் (vec_safe_length (omp_begin_declare_variant_map))
    {
      unsigned முழு i;
      omp_begin_declare_variant_map_entry *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_finish_variant_function (e->variant, e->id, e->ctx);
      vec_safe_truncate (omp_begin_declare_variant_map, 0);
    }

#எனில் ENABLE_ANALYZER
  எனில் (flag_analyzer)
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

நிலையான வெறுமை
c_parser_external_declaration (c_parser *parser)
{
  முழு ext;
  தேர்வு (c_parser_peek_token (parser)->type)
    {
    நிலை CPP_KEYWORD:
      தேர்வு (c_parser_peek_token (parser)->keyword)
	{
	நிலை RID_EXTENSION:
	  ext = disable_extension_diagnostics ();
	  c_parser_consume_token (parser);
	  c_parser_external_declaration (parser);
	  restore_extension_diagnostics (ext);
	  நிறுத்து;
	நிலை RID_ASM:
	  c_parser_asm_definition (parser);
	  நிறுத்து;
	நிலை RID_AT_INTERFACE:
	நிலை RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_definition (parser, NULL_மரம்);
	  நிறுத்து;
	நிலை RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  நிறுத்து;
	நிலை RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  நிறுத்து;
	நிலை RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_protocol_definition (parser, NULL_மரம்);
	  நிறுத்து;
	நிலை RID_AT_PROPERTY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_property_declaration (parser);
	  நிறுத்து;
	நிலை RID_AT_SYNTHESIZE:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_synthesize_declaration (parser);
	  நிறுத்து;
	நிலை RID_AT_DYNAMIC:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_dynamic_declaration (parser);
	  நிறுத்து;
	நிலை RID_AT_END:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_finish_implementation ();
	  நிறுத்து;
	இயல்பு:
	  செல் decl_or_fndef;
	}
      நிறுத்து;
    நிலை CPP_SEMICOLON:
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      நிறுத்து;
    நிலை CPP_PRAGMA:
      mark_valid_location_for_stdc_pragma (உண்மை);
      c_parser_pragma (parser, pragma_external, வெற்று, NULL_மரம்);
      mark_valid_location_for_stdc_pragma (பொய்);
      நிறுத்து;
    நிலை CPP_PLUS:
    நிலை CPP_MINUS:
      எனில் (c_dialect_objc ())
	{
	  c_parser_objc_method_definition (parser);
	  நிறுத்து;
	}
      /* Else fall through, and yield a syntax error trying to parse
	 as a declaration or function definition.  */
      /* FALLTHRU */
    இயல்பு:
    decl_or_fndef:
      /* A declaration or a function definition (or, in Objective-C,
	 an @interface or @protocol with prefix attributes).  We can
	 only tell which after parsing the declaration specifiers, if
	 any, and the first declarator.  */
      c_parser_declaration_or_fndef (parser, உண்மை, உண்மை, உண்மை, பொய், உண்மை,
				     பொய்);
      நிறுத்து;
    }
}

நிலையான வெறுமை c_parser_handle_directive_omp_attributes (மரம் &, vec<c_token> *&,
						      vec<c_token> *);
நிலையான வெறுமை c_finish_omp_declare_simd (c_parser *, மரம், மரம், vec<c_token> *);
நிலையான வெறுமை c_finish_oacc_routine (கட்டமைப்பு oacc_routine_data *, மரம், தருக்க);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

நிலையான வெறுமை
add_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  எனில் (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    திரும்பு;

  மரம் stmt = build0 (DEBUG_BEGIN_STMT, void_type_முனை);
  SET_கோவை_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

நிலையான மரம்
handle_assume_attribute (location_t here, மரம் attrs, தருக்க nested)
{
  எனில் (nested)
    க்கு (மரம் attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", மரம்_CHAIN (attr)))
      {
	மரம் args = மரம்_மதிப்பு (attr);
	முழு nargs = list_length (args);
	எனில் (nargs != 1)
	  {
	    error_at (here, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (here, "expected %i, found %i", 1, nargs);
	  }
	இல்லையெனில்
	  {
	    மரம் arg = மரம்_மதிப்பு (args);
	    arg = c_objc_common_truthvalue_conversion (here, arg);
	    arg = c_fully_fold (arg, பொய், வெற்று);
	    எனில் (arg != error_mark_முனை)
	      {
		மரம் fn = build_call_கோவை_internal_loc (here, IFN_ASSUME,
							void_type_முனை, 1,
							arg);
		add_stmt (fn);
	      }
	  }
      }
  இல்லையெனில்
    pedwarn (here, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  திரும்பு remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

நிலையான வெறுமை
c_parser_maybe_reclassify_token (c_parser *parser)
{
  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      எனில் (token->id_kind == C_ID_ID || token->id_kind == C_ID_TYPENAME)
	{
	  மரம் decl = lookup_name (token->மதிப்பு);

	  token->id_kind = C_ID_ID;
	  எனில் (decl)
	    {
	      எனில் (மரம்_CODE (decl) == TYPE_DECL)
		token->id_kind = C_ID_TYPENAME;
	    }
	  இல்லையெனில் எனில் (c_dialect_objc ())
	    {
	      மரம் objc_interface_decl = objc_is_class_name (token->மதிப்பு);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      எனில் (objc_interface_decl)
		{
		  token->மதிப்பு = objc_interface_decl;
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

நிலையான மரம்
c_parser_declaration_or_fndef (c_parser *parser, தருக்க fndef_ok,
			       தருக்க static_assert_ok, தருக்க empty_ok,
			       தருக்க nested, தருக்க start_attr_ok,
			       தருக்க simple_ok,
			       மரம் *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       தருக்க have_attrs /* = false */,
			       மரம் attrs /* = NULL_TREE */,
			       கட்டமைப்பு oacc_routine_data *oacc_routine_data
			       /* = NULL */,
			       தருக்க *fallthru_attr_p /* = NULL */)
{
  கட்டமைப்பு c_declspecs *specs;
  மரம் prefix_attrs;
  மரம் all_prefix_attrs;
  தருக்க diagnosed_no_specs = பொய்;
  location_t here = c_parser_peek_token (parser)->location;
  மரம் result = NULL_மரம்;

  add_debug_begin_stmt (c_parser_peek_token (parser)->location);

  எனில் (static_assert_ok
      && c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      திரும்பு result;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  எனில் (have_attrs)
    {
      declspecs_add_attrs (here, specs, attrs);
      specs->non_std_attrs_seen_p = பொய்;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  எனில் (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_kind == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->மதிப்பு)))
    {
      மரம் name = c_parser_peek_token (parser)->மதிப்பு;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (here);
      எனில் (tag_exists_p (RECORD_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.add_fixit_செருகு_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      இல்லையெனில் எனில் (tag_exists_p (UNION_TYPE, name))
	{
	  richloc.add_fixit_செருகு_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      இல்லையெனில் எனில் (tag_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.add_fixit_செருகு_before ("enum ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<enum%> keyword to refer to the type",
		    name);
	}
      இல்லையெனில்
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (name, FUZZY_LOOKUP_TYPENAME,
					      here);
	  எனில் (மாறிலி எழுத்து *suggestion = hint.suggestion ())
	    {
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			name, suggestion);
	    }
	  இல்லையெனில்
	    error_at (here, "unknown type name %qE", name);
	}

      /* Parse declspecs normally to get a correct pointer type, but avoid
         a further "fails to be a type name" error.  Refuse nested functions
         since it is not how the user likely wants us to recover.  */
      c_parser_peek_token (parser)->type = CPP_KEYWORD;
      c_parser_peek_token (parser)->keyword = RID_VOID;
      c_parser_peek_token (parser)->மதிப்பு = error_mark_முனை;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  எனில் (c_parser_nth_token_starts_std_attributes (parser, 1))
    have_attrs = உண்மை;

  c_parser_declspecs (parser, specs, உண்மை, உண்மை, start_attr_ok,
		      உண்மை, உண்மை, start_attr_ok, உண்மை, cla_nonabstract_decl);
  எனில் (parser->error)
    {
      c_parser_skip_to_end_of_block_or_statement (parser);
      திரும்பு result;
    }
  எனில் (nested && !specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_end_of_block_or_statement (parser);
      திரும்பு result;
    }

  finish_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  எனில் (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_உச்சி_anonymous_type (specs->type);

  தருக்க gnu_auto_type_p = specs->typespec_word == cts_auto_type;
  தருக்க std_auto_type_p = specs->c23_auto_p;
  தருக்க any_auto_type_p = gnu_auto_type_p || std_auto_type_p;
  gcc_assert (!(gnu_auto_type_p && std_auto_type_p));
  மாறிலி எழுத்து *auto_type_keyword = gnu_auto_type_p ? "__auto_type" : "auto";
  எனில் (specs->constexpr_p)
    {
      /* An underspecified declaration may not declare tags or members
	 or structures or unions; it is undefined behavior to declare
	 the members of an enumeration.  Where the structure, union or
	 enumeration type is declared within an initializer, this is
	 diagnosed elsewhere.  Diagnose here the case of declaring
	 such a type in the type specifiers of a constexpr
	 declaration.  */
      தேர்வு (specs->typespec_kind)
	{
	நிலை ctsk_tagfirstref:
	நிலை ctsk_tagfirstref_attrs:
	  error_at (here, "%qT declared in underspecified object declaration",
		    specs->type);
	  நிறுத்து;

	நிலை ctsk_tagdef:
	  error_at (here, "%qT defined in underspecified object declaration",
		    specs->type);
	  நிறுத்து;

	இயல்பு:
	  நிறுத்து;
	}
    }

  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      தருக்க handled_assume = பொய்;
      எனில் (specs->attrs
	  && !nested
	  && specs->typespec_kind == ctsk_none
	  && c_parser_handle_statement_omp_attributes (parser, specs->attrs,
						       வெற்று))
	{
	  எனில் (specs->attrs)
	    c_warn_unused_attributes (specs->attrs);
	  போது (parser->in_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_next_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, வெற்று, NULL_மரம்);
	    }
	  c_parser_consume_token (parser);
	  திரும்பு result;
	}
      எனில் (specs->typespec_kind == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = உண்மை;
	  specs->attrs
	    = handle_assume_attribute (here, specs->attrs, nested);
	}
      எனில் (any_auto_type_p)
	error_at (here, "%qs in empty declaration", auto_type_keyword);
      இல்லையெனில் எனில் (specs->typespec_kind == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  எனில் (fallthru_attr_p != வெற்று)
	    *fallthru_attr_p = உண்மை;
	  எனில் (nested)
	    {
	      மரம் fn = build_call_கோவை_internal_loc (here, IFN_FALLTHROUGH,
						      void_type_முனை, 0);
	      add_stmt (fn);
	    }
	  இல்லையெனில்
	    pedwarn (here, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      இல்லையெனில் எனில் (empty_ok
	       && !(have_attrs && specs->non_std_attrs_seen_p)
	       && !handled_assume)
	shadow_tag (specs);
      இல்லையெனில்
	{
	  shadow_tag_warned (specs, 1);
	  எனில் (!handled_assume)
	    pedwarn (here, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      எனில் (specs->கோவை)
	add_stmt (fold_convert (void_type_முனை, specs->கோவை));
      c_parser_consume_token (parser);
      எனில் (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, NULL_மரம், பொய்);
      திரும்பு result;
    }
  இல்லையெனில் எனில் (specs->typespec_kind == ctsk_none
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
      எனில் (astate.musttail_p)
	{
	  எனில் (specs->attrs)
	    {
	      auto_urlify_attributes sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, வெற்று, NULL_மரம், வெற்று,
					   astate);
	  திரும்பு result;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  எனில் (empty_ok
      && specs->typespec_kind == ctsk_tagdef
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = பொய்;
      shadow_tag_warned (specs, 1);
      திரும்பு result;
    }
  இல்லையெனில் எனில் (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      தேர்வு (c_parser_peek_token (parser)->type)
	{
	  நிலை CPP_PLUS:
	  நிலை CPP_MINUS:
	    எனில் (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      திரும்பு result;
	    எனில் (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_மரம்;
	      }
	    எனில் (fndef_ok)
	      c_parser_objc_method_definition (parser);
	    இல்லையெனில்
	      c_parser_objc_methodproto (parser);
	    திரும்பு result;
	    நிறுத்து;
	  இயல்பு:
	    நிறுத்து;
	}
      /* This is where we parse 'attributes @interface ...',
	 'attributes @implementation ...', 'attributes @protocol ...'
	 (where attributes could be, for example, __attribute__
	 ((deprecated)).
      */
      தேர்வு (c_parser_peek_token (parser)->keyword)
	{
	நிலை RID_AT_INTERFACE:
	  {
	    எனில் (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      திரும்பு result;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    திரும்பு result;
	  }
	  நிறுத்து;
	நிலை RID_AT_IMPLEMENTATION:
	  {
	    எனில் (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      திரும்பு result;
	    எனில் (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_மரம்;
	      }
	    c_parser_objc_class_definition (parser, NULL_மரம்);
	    திரும்பு result;
	  }
	  நிறுத்து;
	நிலை RID_AT_PROTOCOL:
	  {
	    எனில் (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      திரும்பு result;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    திரும்பு result;
	  }
	  நிறுத்து;
	நிலை RID_AT_ALIAS:
	நிலை RID_AT_CLASS:
	நிலை RID_AT_END:
	நிலை RID_AT_PROPERTY:
	  எனில் (specs->attrs)
	    {
	      c_parser_error (parser, "unexpected attribute");
	      specs->attrs = வெற்று;
	    }
	  நிறுத்து;
	இயல்பு:
	  நிறுத்து;
	}
    }
  இல்லையெனில் எனில் (attribute_fallthrough_p (specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  இல்லையெனில் எனில் (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_attributes (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_மரம்;
  தருக்க more_than_one_decl = பொய்;
  போது (உண்மை)
    {
      கட்டமைப்பு c_declarator *declarator;
      தருக்க dummy = பொய்;
      timevar_id_t tv;
      மரம் fnbody = NULL_மரம்;
      மரம் underspec_name = NULL_மரம்;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_kind != ctsk_none,
					C_DTR_NORMAL, &dummy);
      எனில் (declarator == வெற்று)
	{
	  எனில் (omp_declare_simd_clauses)
	    c_finish_omp_declare_simd (parser, NULL_மரம், NULL_மரம்,
				       omp_declare_simd_clauses);
	  எனில் (oacc_routine_data)
	    c_finish_oacc_routine (oacc_routine_data, NULL_மரம், பொய்);
	  /* This check is here purely to improve the diagnostic.  */
	  எனில் (!simple_ok)
	    c_parser_skip_to_end_of_block_or_statement (parser);
	  திரும்பு result;
	}
      எனில் (flag_openmp || flag_openmp_simd)
	{
	  கட்டமைப்பு c_declarator *d = declarator;
	  போது (d->kind != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = வெற்று;
	  c_parser_handle_directive_omp_attributes (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      எனில் (gnu_auto_type_p && declarator->kind != cdk_id)
	{
	  error_at (here,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  திரும்பு result;
	}
      எனில் (std_auto_type_p)
	{
	  கட்டமைப்பு c_declarator *d = declarator;
	  போது (d->kind == cdk_attrs)
	    d = d->declarator;
	  எனில் (d->kind != cdk_id)
	    {
	      error_at (here,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      திரும்பு result;
	    }
	  underspec_name = d->u.id.id;
	}
      இல்லையெனில் எனில் (specs->constexpr_p)
	{
	  கட்டமைப்பு c_declarator *d = declarator;
	  போது (d->kind != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      எனில் (c_parser_next_token_is (parser, CPP_EQ)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is_keyword (parser, RID_ASM)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_next_token_is_keyword (parser, RID_IN))
	{
	  மரம் asm_name = NULL_மரம்;
	  மரம் postfix_attrs = NULL_மரம்;
	  எனில் (!diagnosed_no_specs && !specs->declspecs_seen_p)
	    {
	      diagnosed_no_specs = உண்மை;
	      pedwarn (here, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = பொய்;
	  எனில் (c_parser_next_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_கோவை (parser);
	  எனில் (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_attributes (parser);
	      எனில் (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (here, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  திரும்பு result;
		}
	    }
	  எனில் (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      மரம் d;
	      கட்டமைப்பு c_கோவை init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      எனில் (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (வரி_table, init_loc);
		  unsigned முழு underspec_state = 0;
		  எனில் (std_auto_type_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  start_init (NULL_மரம், asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  எனில் (nested && !empty_ok)
		    flag_sanitize = 0;
		  init = c_parser_கோவை_no_commas (parser, வெற்று);
		  எனில் (std_auto_type_p)
		    finish_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  எனில் (gnu_auto_type_p
		      && மரம்_CODE (init.மதிப்பு) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (மரம்_OPERAND (init.மதிப்பு, 1)))
		    error_at (here,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_to_rvalue (init_loc, init, உண்மை, உண்மை,
						   உண்மை);
		  மரம் init_type = மரம்_TYPE (init.மதிப்பு);
		  தருக்க vm_type = c_type_variably_modified_p (init_type);
		  எனில் (vm_type)
		    init.மதிப்பு = save_கோவை (init.மதிப்பு);
		  finish_init ();
		  specs->typespec_kind = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = உண்மை;
		  specs->type = init_type;
		  எனில் (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_attributes (specs->type,
						  specs->postfix_attrs);
		      decl_attributes (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_மரம்;
		    }
		  எனில் (vm_type)
		    {
		      தருக்க maybe_const = உண்மை;
		      மரம் type_கோவை = c_fully_fold (init.மதிப்பு, பொய்,
						     &maybe_const);
		      specs->கோவை_const_operands &= maybe_const;
		      எனில் (specs->கோவை)
			specs->கோவை = build2 (COMPOUND_கோவை,
					      மரம்_TYPE (type_கோவை),
					      specs->கோவை, type_கோவை);
		      இல்லையெனில்
			specs->கோவை = type_கோவை;
		    }
		  d = start_decl (declarator, specs, உண்மை,
				  chainon (postfix_attrs, all_prefix_attrs));
		  எனில் (!d)
		    d = error_mark_முனை;
		  எனில் (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_மரம்,
					       omp_declare_simd_clauses);
		  எனில் (!omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_மரம்,
					       &omp_dsimd_idattr_clauses);
		}
	      இல்லையெனில்
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (வரி_table, init_loc);
		  unsigned முழு underspec_state = 0;
		  எனில் (specs->constexpr_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  d = start_decl (declarator, specs, உண்மை,
				  chainon (postfix_attrs,
					   all_prefix_attrs),
				  !specs->constexpr_p);
		  எனில் (!d)
		    d = error_mark_முனை;
		  எனில் (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_மரம்,
					       omp_declare_simd_clauses);
		  எனில் (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_மரம்,
					       &omp_dsimd_idattr_clauses);
		  start_init (d, asm_name,
			      மரம்_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  எனில் (மரம்_CODE (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  எனில் (specs->constexpr_p)
		    {
		      finish_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      எனில் (omp_declare_simd_clauses)
			c_finish_omp_declare_simd (parser, d, NULL_மரம்,
						   omp_declare_simd_clauses);
		  எனில் (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_மரம்,
					       &omp_dsimd_idattr_clauses);
		    }
		  finish_init ();
		}
	      எனில் (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, பொய்);
	      எனில் (d != error_mark_முனை)
		{
		  maybe_warn_string_init (init_loc, மரம்_TYPE (d), init);
		  finish_decl (d, init_loc, init.மதிப்பு,
			       init.original_type, asm_name);
		  result = d;
		}
	    }
	  இல்லையெனில்
	    {
	      எனில் (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  திரும்பு result;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      மரம் attrs = chainon (postfix_attrs, all_prefix_attrs);
	      மரம் d = start_decl (declarator, specs, பொய், attrs, உண்மை,
				   &lastloc);
	      எனில் (d && மரம்_CODE (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  மாறிலி கட்டமைப்பு c_declarator *decl = declarator;
		  மாறிலி கட்டமைப்பு c_declarator *last_non_id_attrs = வெற்று;

		  போது (decl)
		    தேர்வு (decl->kind)
		      {
		      நிலை cdk_array:
		      நிலை cdk_function:
		      நிலை cdk_pointer:
			last_non_id_attrs = decl;
			decl = decl->declarator;
			நிறுத்து;

		      நிலை cdk_attrs:
			decl = decl->declarator;
			நிறுத்து;

		      நிலை cdk_id:
			decl = 0;
			நிறுத்து;

		      இயல்பு:
			gcc_unreachable ();
		      }

		  /* If it exists and is cdk_function declaration whose
		     arguments have not been set yet, use its arguments.  */
		  எனில் (last_non_id_attrs
		      && last_non_id_attrs->kind == cdk_function)
		    {
		      மரம் parms = last_non_id_attrs->u.arg_info->parms;
		      எனில் (DECL_ARGUMENTS (d) == NULL_மரம்
			  && DECL_INITIAL (d) == NULL_மரம்)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      எனில் (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_empty ())
		{
		  மரம் parms = NULL_மரம்;
		  எனில் (d && மரம்_CODE (d) == FUNCTION_DECL)
		    {
		      கட்டமைப்பு c_declarator *ce = declarator;
		      போது (ce != வெற்று)
			எனில் (ce->kind == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    நிறுத்து;
			  }
			இல்லையெனில்
			  ce = ce->declarator;
		    }
		  எனில் (parms)
		    temp_store_parm_decls (d, parms);
		  எனில் (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  எனில் (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  எனில் (parms)
		    temp_எடு_parm_decls ();
		}
	      எனில் (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, பொய்);
	      எனில் (d)
		finish_decl (d, UNKNOWN_LOCATION, NULL_மரம்,
			     NULL_மரம், asm_name);

	      எனில் (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  எனில் (d)
		    *objc_foreach_object_declaration = d;
		  இல்லையெனில்
		    *objc_foreach_object_declaration = error_mark_முனை;
		}
	    }
	  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      more_than_one_decl = உண்மை;
	      எனில் (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  திரும்பு result;
		}
	      c_parser_consume_token (parser);
	      எனில் (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
		all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					    prefix_attrs);
	      இல்லையெனில்
		all_prefix_attrs = prefix_attrs;
	      தொடர்;
	    }
	  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      எனில் (!simple_ok)
		c_parser_consume_token (parser);
	      திரும்பு result;
	    }
	  இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      திரும்பு result;
	    }
	  இல்லையெனில்
	    {
	      எனில் (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      இல்லையெனில் எனில் (more_than_one_decl)
		error_at (here, "declaration in condition can only declare "
			  "a single object");
	      திரும்பு result;
	    }
	}
      இல்லையெனில் எனில் (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (here,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  திரும்பு result;
	}
      இல்லையெனில் எனில் (!fndef_ok)
	{
	  எனில் (simple_ok && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  இல்லையெனில்
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	    }
	  திரும்பு result;
	}
      /* Function definition (nested or otherwise).  */
      எனில் (nested)
	{
	  pedwarn (here, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_தள்ளு_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      மரம் dv_base = NULL_மரம்;
      மரம் dv_ctx = NULL_மரம்;
      எனில் (!vec_safe_is_empty (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->last ();
	  dv_ctx = copy_list (a.selector);
	  dv_base = omp_start_variant_function (declarator, dv_ctx);
	}

      எனில் (!start_function (specs, declarator, all_prefix_attrs))
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
	  எனில் (c_parser_next_token_starts_declspecs (parser))
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
	      parser->error = பொய்;
	    }
	  இல்லையெனில்
	    {
	      /* This can appear in many cases looking nothing like a
		 function definition, so we don't give a more specific
		 error suggesting there was one.  */
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			      "or %<__attribute__%>");
	    }
	  எனில் (nested)
	    c_எடு_function_context ();
	  நிறுத்து;
	}

      எனில் (DECL_DECLARED_INLINE_P (current_function_decl))
        tv = TV_PARSE_INLINE;
      இல்லையெனில்
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
      முழு save_debug_nonbind_markers_p = debug_nonbind_markers_p;
      debug_nonbind_markers_p = 0;
      c_parser_maybe_reclassify_token (parser);
      போது (c_parser_next_token_is_not (parser, CPP_EOF)
	     && c_parser_next_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, பொய், பொய், பொய்,
				       உண்மை, பொய், பொய்);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      எனில் (omp_declare_simd_clauses)
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_மரம்,
				   omp_declare_simd_clauses);
      எனில் (!omp_dsimd_idattr_clauses.is_empty ())
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_மரம்,
				   &omp_dsimd_idattr_clauses);
      எனில் (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, current_function_decl, உண்மை);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_start_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      எனில் (dv_base && current_function_decl != error_mark_முனை)
	{
	  omp_begin_declare_variant_map_entry e
	    = { current_function_decl, dv_base, dv_ctx };
	  vec_safe_தள்ளு (omp_begin_declare_variant_map, e);
	}

      /* If the definition was marked with __RTL, use the RTL parser now,
	 consuming the function body.  */
      எனில் (specs->declspec_il == cdil_rtl)
	{
	  endloc = c_parser_parse_rtl_body (parser, specs->gimple_or_rtl_pass);

	  /* Normally, store_parm_decls sets next_is_function_body,
	     anticipating a function body.  We need a push_scope/pop_scope
	     pair to flush out this state, or subsequent function parsing
	     will go wrong.  */
	  தள்ளு_scope ();
	  எடு_scope ();

	  finish_function (endloc);
	  திரும்பு result;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      இல்லையெனில் எனில் (specs->declspec_il != cdil_none)
	{
	  தருக்க saved = in_late_இருமம்_op;
	  in_late_இருமம்_op = உண்மை;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->entry_bb_மொத்தம்);
	  in_late_இருமம்_op = saved;
	}
      இல்லையெனில்
	fnbody = c_parser_compound_statement (parser, &endloc);
      மரம் fndecl = current_function_decl;
      எனில் (nested && specs->declspec_il == cdil_none)
	{
	  மரம் decl = current_function_decl;
	  /* Mark nested functions as needing static-chain initially.
	     lower_nested_functions will recompute it but the
	     DECL_STATIC_CHAIN flag is also used before that happens,
	     by initializer_constant_valid_p.  See gcc.dg/nested-fn-2.c.  */
	  DECL_STATIC_CHAIN (decl) = 1;
	  add_stmt (fnbody);
	  finish_function (endloc);
	  c_எடு_function_context ();
	  add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_கோவை, decl));
	}
      இல்லையெனில் எனில் (nested)
	{
	  எனில் (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  இல்லையெனில்
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  finish_function (endloc);
	  c_எடு_function_context ();
	}
      இல்லையெனில்
	{
	  எனில் (fnbody)
	    add_stmt (fnbody);
	  finish_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      எனில் (specs->declspec_il != cdil_none)
	DECL_SAVED_மரம் (fndecl) = NULL_மரம்;

      நிறுத்து;
    }

  திரும்பு result;
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

நிலையான வெறுமை
c_parser_asm_definition (c_parser *parser)
{
  location_t asm_loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  மரம் asm_str = NULL_மரம்;
  மரம் outputs = NULL_மரம், inputs = NULL_மரம்;
  எனில் (!parens.require_open (parser))
    செல் done;
  asm_str = c_parser_asm_string_literal (parser);
  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      செல் done;
    }
  க்கு (முழு section = 0; section < 2; ++section)
    {
      எனில் (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  எனில் (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
	      asm_str = NULL_மரம்;
	      செல் done;
	    }
	  c_parser_consume_token (parser);
	}
      இல்லையெனில் எனில் (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, பொய்))
	செல் error_close_paren;
      எனில் (!c_parser_next_token_is (parser, CPP_COLON)
	  && !c_parser_next_token_is (parser, CPP_SCOPE)
	  && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  எனில் (section)
	    inputs = c_parser_asm_operands (parser);
	  இல்லையெனில்
	    outputs = c_parser_asm_operands (parser);
	}
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	நிறுத்து;
    }

  எனில் (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
      asm_str = NULL_மரம்;
    }

  எனில் (asm_str)
    asm_str = build_asm_கோவை (asm_loc, asm_str, outputs, inputs,
			      NULL_மரம், NULL_மரம், பொய், பொய்);
done:
  எனில் (asm_str)
    symtab->finalize_toplevel_asm (asm_str);
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse a static assertion (C11 6.7.10).

   static_assert-declaration:
     static_assert-declaration-no-semi ;
*/

நிலையான வெறுமை
c_parser_static_assert_declaration (c_parser *parser)
{
  c_parser_static_assert_declaration_no_semi (parser);
  எனில் (parser->error
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

நிலையான வெறுமை
c_parser_static_assert_declaration_no_semi (c_parser *parser)
{
  location_t assert_loc, மதிப்பு_loc;
  மரம் மதிப்பு;
  மரம் string = NULL_மரம்;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT));
  மரம் spelling = c_parser_peek_token (parser)->மதிப்பு;
  assert_loc = c_parser_peek_token (parser)->location;
  எனில் (flag_isoc99)
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  இல்லையெனில்
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  c_parser_consume_token (parser);
  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு;
  location_t மதிப்பு_tok_loc = c_parser_peek_token (parser)->location;
  மதிப்பு = convert_lvalue_to_rvalue (மதிப்பு_tok_loc,
				    c_parser_கோவை_no_commas (parser, வெற்று),
				    உண்மை, உண்மை).மதிப்பு;
  மதிப்பு_loc = கோவை_LOC_OR_LOC (மதிப்பு, மதிப்பு_tok_loc);
  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      தேர்வு (c_parser_peek_token (parser)->type)
	{
	நிலை CPP_STRING:
	நிலை CPP_STRING16:
	நிலை CPP_STRING32:
	நிலை CPP_WSTRING:
	நிலை CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, பொய், உண்மை).மதிப்பு;
	  நிறுத்து;
	இயல்பு:
	  c_parser_error (parser, "expected string literal");
	  திரும்பு;
	}
    }
  இல்லையெனில் எனில் (flag_isoc11)
    /* If pedantic for pre-C11, the use of _Static_assert itself will
       have been diagnosed, so do not also diagnose the use of this
       new C23 feature of _Static_assert.  */
    pedwarn_c11 (assert_loc, OPT_Wpedantic,
		 "ISO C11 does not support omitting the string in "
		 "%qE", spelling);
  parens.require_close (parser);

  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (மதிப்பு)))
    {
      error_at (மதிப்பு_loc, "expression in static assertion is not an integer");
      திரும்பு;
    }
  எனில் (மரம்_CODE (மதிப்பு) != INTEGER_CST)
    {
      மதிப்பு = c_fully_fold (மதிப்பு, பொய், வெற்று);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (மதிப்பு);
      எனில் (மரம்_CODE (மதிப்பு) == INTEGER_CST)
	pedwarn (மதிப்பு_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  எனில் (மரம்_CODE (மதிப்பு) != INTEGER_CST)
    {
      error_at (மதிப்பு_loc, "expression in static assertion is not constant");
      திரும்பு;
    }
  constant_expression_warning (மதிப்பு);
  எனில் (integer_zerop (மதிப்பு))
    {
      எனில் (string)
	error_at (assert_loc, "static assertion failed: %E", string);
      இல்லையெனில்
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

வெறுமை
c_parser_declspecs (c_parser *parser, கட்டமைப்பு c_declspecs *specs,
		    தருக்க scspec_ok, தருக்க typespec_ok, தருக்க start_attr_ok,
		    தருக்க alignspec_ok, தருக்க auto_type_ok,
		    தருக்க start_std_attr_ok, தருக்க end_std_attr_ok,
		    எண்ணிக்கை c_lookahead_kind la)
{
  தருக்க attrs_ok = start_attr_ok;
  தருக்க seen_type = specs->typespec_kind != ctsk_none;

  எனில் (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  எனில் (start_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_seen_p);
      location_t loc = c_parser_peek_token (parser)->location;
      மரம் attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_add_attrs (loc, specs, attrs);
      specs->non_std_attrs_seen_p = பொய்;
    }

  போது (c_parser_next_token_is (parser, CPP_NAME)
	 || c_parser_next_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_next_token_is (parser, CPP_LESS)))
    {
      கட்டமைப்பு c_typespec t;
      மரம் attrs;
      மரம் align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      எனில் ((!typespec_ok || specs->typespec_kind == ctsk_tagdef)
	  && c_parser_next_tokens_start_typename (parser, la)
	  && !c_parser_next_token_is_qualifier (parser)
	  && !c_parser_next_token_is_keyword (parser, RID_ALIGNAS))
	நிறுத்து;

      எனில் (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  மரம் மதிப்பு = name_token->மதிப்பு;
	  c_id_kind kind = name_token->id_kind;

	  எனில் (kind == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_FIRST_ADDR_SPACE;
	      declspecs_add_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = உண்மை;
	      தொடர்;
	    }

	  gcc_assert (!c_parser_next_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  எனில் (seen_type || !c_parser_next_tokens_start_typename (parser, la))
	    நிறுத்து;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  seen_type = உண்மை;
	  attrs_ok = உண்மை;
	  எனில் (kind == C_ID_ID)
	    {
	      auto_diagnostic_group d;
	      name_hint hint = lookup_name_fuzzy (மதிப்பு, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      எனில் (மாறிலி எழுத்து *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.add_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    மதிப்பு, suggestion);
		}
	      இல்லையெனில்
		error_at (loc, "unknown type name %qE", மதிப்பு);
	      t.kind = ctsk_typedef;
	      t.spec = error_mark_முனை;
	    }
	  இல்லையெனில் எனில் (kind == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_next_token_is_not (parser, CPP_LESS)))
	    {
	      t.kind = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (மதிப்பு);
	    }
	  இல்லையெனில்
	    {
	      மரம் proto = NULL_மரம்;
	      gcc_assert (c_dialect_objc ());
	      t.kind = ctsk_objc;
	      எனில் (c_parser_next_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (மதிப்பு, proto);
	    }
	  t.கோவை = NULL_மரம்;
	  t.கோவை_const_operands = உண்மை;
	  t.has_enum_type_specifier = பொய்;
	  declspecs_add_type (name_token->location, specs, t);
	  தொடர்;
	}
      எனில் (c_parser_next_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  மரம் proto;
	  gcc_assert (c_dialect_objc ());
	  எனில் (!typespec_ok || seen_type)
	    நிறுத்து;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.kind = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_மரம், proto);
	  t.கோவை = NULL_மரம்;
	  t.கோவை_const_operands = உண்மை;
	  t.has_enum_type_specifier = பொய்;
	  declspecs_add_type (loc, specs, t);
	  தொடர்;
	}
      gcc_assert (c_parser_next_token_is (parser, CPP_KEYWORD));
      தேர்வு (c_parser_peek_token (parser)->keyword)
	{
	நிலை RID_STATIC:
	நிலை RID_EXTERN:
	நிலை RID_REGISTER:
	நிலை RID_TYPEDEF:
	நிலை RID_INLINE:
	நிலை RID_NORETURN:
	நிலை RID_AUTO:
	நிலை RID_THREAD:
	நிலை RID_CONSTEXPR:
	  எனில் (!scspec_ok)
	    செல் out;
	  attrs_ok = உண்மை;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_add_scspec (loc, specs,
				c_parser_peek_token (parser)->மதிப்பு);
	  c_parser_consume_token (parser);
	  நிறுத்து;
	நிலை RID_AUTO_TYPE:
	  எனில் (!auto_type_ok)
	    செல் out;
	  /* Fall through.  */
	நிலை RID_UNSIGNED:
	நிலை RID_LONG:
	நிலை RID_SHORT:
	நிலை RID_SIGNED:
	நிலை RID_COMPLEX:
	நிலை RID_INT:
	நிலை RID_CHAR:
	நிலை RID_FLOAT:
	நிலை RID_DOUBLE:
	நிலை RID_VOID:
	நிலை RID_DFLOAT32:
	நிலை RID_DFLOAT64:
	நிலை RID_DFLOAT128:
	நிலை RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	நிலை RID_BOOL:
	நிலை RID_FRACT:
	நிலை RID_ACCUM:
	நிலை RID_SAT:
	நிலை RID_INT_N_0:
	நிலை RID_INT_N_1:
	நிலை RID_INT_N_2:
	நிலை RID_INT_N_3:
	  எனில் (!typespec_ok)
	    செல் out;
	  attrs_ok = உண்மை;
	  seen_type = உண்மை;
	  எனில் (c_dialect_objc ())
	    parser->objc_need_raw_identifier = உண்மை;
	  t.kind = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->மதிப்பு;
	  t.கோவை = NULL_மரம்;
	  t.கோவை_const_operands = உண்மை;
	  t.has_enum_type_specifier = பொய்;
	  declspecs_add_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  நிறுத்து;
	நிலை RID_ENUM:
	  எனில் (!typespec_ok)
	    செல் out;
	  attrs_ok = உண்மை;
	  seen_type = உண்மை;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  நிறுத்து;
	நிலை RID_STRUCT:
	நிலை RID_UNION:
	  எனில் (!typespec_ok)
	    செல் out;
	  attrs_ok = உண்மை;
	  seen_type = உண்மை;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  நிறுத்து;
	நிலை RID_TYPEOF:
	நிலை RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  எனில் (!typespec_ok || seen_type)
	    செல் out;
	  attrs_ok = உண்மை;
	  seen_type = உண்மை;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_add_type (loc, specs, t);
	  நிறுத்து;
	நிலை RID_BITINT:
	  எனில் (!typespec_ok)
	    செல் out;
	  இல்லையெனில்
	    {
	      attrs_ok = உண்மை;
	      seen_type = உண்மை;
	      t.kind = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->மதிப்பு;
	      t.கோவை = error_mark_முனை;
	      t.கோவை_const_operands = உண்மை;
	      t.has_enum_type_specifier = பொய்;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      எனில் (parens.require_open (parser))
		{
		  c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
		  t.கோவை = convert_lvalue_to_rvalue (loc, கோவை, உண்மை,
						     உண்மை).மதிப்பு;
		  parens.skip_until_found_close (parser);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  நிறுத்து;
	நிலை RID_ATOMIC:
	  /* C parser handling of Objective-C constructs needs
	     checking for correct lvalue-to-rvalue conversions, and
	     the code in build_modify_expr handling various
	     Objective-C cases, and that in build_unary_op handling
	     Objective-C cases for increment / decrement, also needs
	     updating; uses of TYPE_MAIN_VARIANT in objc_compare_types
	     and objc_types_are_equivalent may also need updates.  */
	  எனில் (c_dialect_objc ())
	    sorry ("%<_Atomic%> in Objective-C");
	  எனில் (flag_isoc99)
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C99 does not support the %<_Atomic%> qualifier");
	  இல்லையெனில்
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C90 does not support the %<_Atomic%> qualifier");
	  attrs_ok = உண்மை;
	  மரம் மதிப்பு;
	  மதிப்பு = c_parser_peek_token (parser)->மதிப்பு;
	  c_parser_consume_token (parser);
	  எனில் (typespec_ok && c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      seen_type = உண்மை;
	      c_parser_consume_token (parser);
	      கட்டமைப்பு c_type_name *type = c_parser_type_name (parser);
	      t.kind = ctsk_typeof;
	      t.spec = error_mark_முனை;
	      t.கோவை = NULL_மரம்;
	      t.கோவை_const_operands = உண்மை;
	      t.has_enum_type_specifier = பொய்;
	      எனில் (type != வெற்று)
		t.spec = groktypename (type, &t.கோவை,
				       &t.கோவை_const_operands);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      எனில் (t.spec != error_mark_முனை)
		{
		  எனில் (மரம்_CODE (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  இல்லையெனில் எனில் (மரம்_CODE (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  இல்லையெனில் எனில் (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  இல்லையெனில்
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  இல்லையெனில்
	    declspecs_add_qual (loc, specs, மதிப்பு);
	  நிறுத்து;
	நிலை RID_CONST:
	நிலை RID_VOLATILE:
	நிலை RID_RESTRICT:
	  attrs_ok = உண்மை;
	  declspecs_add_qual (loc, specs, c_parser_peek_token (parser)->மதிப்பு);
	  c_parser_consume_token (parser);
	  நிறுத்து;
	நிலை RID_ATTRIBUTE:
	  எனில் (!attrs_ok)
	    செல் out;
	  attrs = c_parser_gnu_attributes (parser);
	  declspecs_add_attrs (loc, specs, attrs);
	  நிறுத்து;
	நிலை RID_ALIGNAS:
	  எனில் (!alignspec_ok)
	    செல் out;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_add_alignas (loc, specs, align);
	  நிறுத்து;
	நிலை RID_GIMPLE:
	  எனில் (! flag_gimple)
	    error_at (loc, "%<__GIMPLE%> only valid with %<-fgimple%>");
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_gimple;
	  specs->locations[cdw_gimple] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  நிறுத்து;
	நிலை RID_RTL:
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_rtl;
	  specs->locations[cdw_rtl] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  நிறுத்து;
	இயல்பு:
	  செல் out;
	}
    }
 out:
  எனில் (end_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    specs->postfix_attrs = c_parser_std_attribute_specifier_sequence (parser);
}

/* Complain about a non-CPP_NAME within an enumerator list.  */

நிலையான வெறுமை
report_bad_enum_name (c_parser *parser)
{
  எனில் (!parser->error)
    {
      c_token *token = c_parser_peek_token (parser);
      தேர்வு (token->type)
	{
	இயல்பு:
	  நிறுத்து;
	நிலை CPP_CLOSE_BRACE:
	  /* Give a nicer error for "enum {}".  */
	  error_at (token->location,
		    "empty enum is invalid");
	  parser->error = உண்மை;
	  திரும்பு;
	நிலை CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  எனில் (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_group d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_POINTER (token->மதிப்பு));
	      add_note_about_new_keyword (token->location,
					  token->மதிப்பு);
	      parser->error = உண்மை;
	      திரும்பு;
	    }
	  நிறுத்து;
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

நிலையான கட்டமைப்பு c_typespec
c_parser_enum_specifier (c_parser *parser)
{
  கட்டமைப்பு c_typespec ret;
  தருக்க have_std_attrs;
  தருக்க potential_nesting_p = பொய்;
  மரம் std_attrs = NULL_மரம்;
  மரம் attrs;
  மரம் ident = NULL_மரம்;
  மரம் fixed_underlying_type = NULL_மரம்;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  எனில் (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));
  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->மதிப்பு;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  எனில் (c_parser_next_token_is (parser, CPP_COLON)
      /* Distinguish an enum-type-specifier from a bit-field
	 declaration of the form "enum e : constant-expression;".  */
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      pedwarn_c11 (enum_loc, OPT_Wpedantic,
		   "ISO C does not support specifying %<enum%> underlying "
		   "types before C23");
      எனில் (ident)
	{
	  /* The tag is in scope during the enum-type-specifier (which
	     may refer to the tag inside typeof).  */
	  ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, உண்மை);
	  எனில் (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_மரம் == TYPE_மதிப்புகள் (ret.spec);
	}
      இல்லையெனில்
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_மரம்;
	  ret.kind = ctsk_tagdef;
	  ret.கோவை = NULL_மரம்;
	  ret.கோவை_const_operands = உண்மை;
	  ret.has_enum_type_specifier = உண்மை;
	}
      c_parser_consume_token (parser);
      கட்டமைப்பு c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, பொய், உண்மை, பொய், பொய், பொய்,
			  பொய், உண்மை, cla_prefer_id);
      finish_declspecs (specs);
      எனில் (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      இல்லையெனில் எனில் (மரம்_CODE (specs->type) != INTEGER_TYPE
	       && மரம்_CODE (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || மரம்_CODE (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_முனை;
	}
      இல்லையெனில் எனில் (specs->restrict_p)
	error_at (enum_loc, "invalid use of %<restrict%>");
      fixed_underlying_type = TYPE_MAIN_VARIANT (specs->type);
      எனில் (ident)
	{
	  /* The type specified must be consistent with any previously
	     specified underlying type.  If this is a newly declared
	     type, it is now a complete type.  */
	  எனில் (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
	      && ENUM_UNDERLYING_TYPE (ret.spec) == NULL_மரம்)
	    {
	      TYPE_MIN_மதிப்பு (ret.spec) =
		TYPE_MIN_மதிப்பு (fixed_underlying_type);
	      TYPE_MAX_மதிப்பு (ret.spec) =
		TYPE_MAX_மதிப்பு (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      SET_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_SIZE (ret.spec) = NULL_மரம்;
	      TYPE_PRECISION (ret.spec) =
		TYPE_PRECISION (fixed_underlying_type);
	      ENUM_UNDERLYING_TYPE (ret.spec) = fixed_underlying_type;
	      layout_type (ret.spec);
	    }
	  இல்லையெனில் எனில் (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
		   && !comptypes (fixed_underlying_type,
				  ENUM_UNDERLYING_TYPE (ret.spec)))
	    {
	      error_at (enum_loc, "%<enum%> underlying type incompatible with "
			"previous declaration");
	      fixed_underlying_type = ENUM_UNDERLYING_TYPE (ret.spec);
	    }
	}
    }
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      கட்டமைப்பு c_enum_contents the_enum;
      மரம் type;
      மரம் postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      மரம் மதிப்புகள்;
      timevar_தள்ளு (TV_PARSE_ENUM);
      type = start_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      மதிப்புகள் = NULL_மரம்;
      c_parser_consume_token (parser);
      போது (உண்மை)
	{
	  மரம் enum_id;
	  மரம் enum_மதிப்பு;
	  மரம் enum_decl;
	  தருக்க seen_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, மதிப்பு_loc;
	  எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, வெற்று);
	      மதிப்புகள் = error_mark_முனை;
	      நிறுத்து;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->மதிப்பு;
	  /* Set the location in case we create a decl now.  */
	  c_parser_set_source_position_from_token (token);
	  decl_loc = மதிப்பு_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  மரம் std_attrs = NULL_மரம்;
	  எனில் (c_parser_nth_token_starts_std_attributes (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  மரம் enum_attrs = chainon (std_attrs,
				     c_parser_gnu_attributes (parser));
	  எனில் (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      மதிப்பு_loc = c_parser_peek_token (parser)->location;
	      enum_மதிப்பு = convert_lvalue_to_rvalue (மதிப்பு_loc,
						     (c_parser_கோவை_no_commas
						      (parser, வெற்று)),
						     உண்மை, உண்மை).மதிப்பு;
	    }
	  இல்லையெனில்
	    enum_மதிப்பு = NULL_மரம்;
	  enum_decl = build_enumerator (decl_loc, மதிப்பு_loc,
					&the_enum, enum_id, enum_மதிப்பு);
	  எனில் (enum_attrs)
	    decl_attributes (&மரம்_PURPOSE (enum_decl), enum_attrs, 0);
	  மரம்_CHAIN (enum_decl) = மதிப்புகள்;
	  மதிப்புகள் = enum_decl;
	  seen_comma = பொய்;
	  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      seen_comma = உண்மை;
	      c_parser_consume_token (parser);
	    }
	  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      எனில் (seen_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      நிறுத்து;
	    }
	  எனில் (!seen_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, வெற்று);
	      மதிப்புகள் = error_mark_முனை;
	      நிறுத்து;
	    }
	}
      postfix_attrs = c_parser_gnu_attributes (parser);
      ret.spec = finish_enum (type, nreverse (மதிப்புகள்),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.kind = ctsk_tagdef;
      ret.கோவை = NULL_மரம்;
      ret.கோவை_const_operands = உண்மை;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_மரம்;
      timevar_எடு (TV_PARSE_ENUM);
      திரும்பு ret;
    }
  இல்லையெனில் எனில் (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_முனை;
      ret.kind = ctsk_tagref;
      ret.கோவை = NULL_மரம்;
      ret.கோவை_const_operands = உண்மை;
      ret.has_enum_type_specifier = பொய்;
      திரும்பு ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  எனில் (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  எனில் (fixed_underlying_type == NULL_மரம்)
    {
      ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
			     std_attrs, பொய்);
      /* In ISO C, enumerated types without a fixed underlying type
	 can be referred to only if already defined.  */
      எனில் (pedantic && !COMPLETE_TYPE_P (ret.spec))
	{
	  gcc_assert (ident);
	  pedwarn (enum_loc, OPT_Wpedantic,
		   "ISO C forbids forward references to %<enum%> types");
	}
    }
  திரும்பு ret;
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

நிலையான கட்டமைப்பு c_typespec
c_parser_struct_or_union_specifier (c_parser *parser)
{
  கட்டமைப்பு c_typespec ret;
  தருக்க have_std_attrs;
  மரம் std_attrs = NULL_மரம்;
  மரம் attrs;
  மரம் ident = NULL_மரம்;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  எண்ணிக்கை மரம்_code code;
  தேர்வு (c_parser_peek_token (parser)->keyword)
    {
    நிலை RID_STRUCT:
      code = RECORD_TYPE;
      நிறுத்து;
    நிலை RID_UNION:
      code = UNION_TYPE;
      நிறுத்து;
    இயல்பு:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  எனில் (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->மதிப்பு;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      வகுப்பு c_struct_parse_info *struct_info;
      மரம் type = start_struct (struct_loc, code, ident, &struct_info);
      மரம் postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      மரம் contents;
      மரம் கோவை = வெற்று;
      timevar_தள்ளு (TV_PARSE_STRUCT);
      contents = NULL_மரம்;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      எனில் (c_parser_next_token_is_keyword (parser, RID_AT_DEFS))
	{
	  மரம் name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  எனில் (!parens.require_open (parser))
	    செல் end_at_defs;
	  எனில் (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->மதிப்பு;
	      c_parser_consume_token (parser);
	    }
	  இல்லையெனில்
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
	      செல் end_at_defs;
	    }
	  parens.skip_until_found_close (parser);
	  contents = nreverse (objc_get_class_ivars (name));
	}
    end_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      போது (உண்மை)
	{
	  மரம் decls;
	  /* Parse any stray semicolon.  */
	  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      location_t semicolon_loc
		= c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (semicolon_loc);
	      richloc.add_fixit_remove ();
	      pedwarn (&richloc, OPT_Wpedantic,
		       "extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      தொடர்;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      நிறுத்து;
	    }
	  /* Accept #pragmas at struct scope.  */
	  எனில் (c_parser_next_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, வெற்று, NULL_மரம்);
	      தொடர்;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &கோவை);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  இல்லையெனில்
	    {
	      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      இல்லையெனில் எனில் (parser->error
		       || !c_parser_next_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, வெற்று);
		  நிறுத்து;
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
				struct_info, &கோவை);
      ret.kind = ctsk_tagdef;
      ret.கோவை = கோவை;
      ret.கோவை_const_operands = உண்மை;
      ret.has_enum_type_specifier = பொய்;
      timevar_எடு (TV_PARSE_STRUCT);
      திரும்பு ret;
    }
  இல்லையெனில் எனில் (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_முனை;
      ret.kind = ctsk_tagref;
      ret.கோவை = NULL_மரம்;
      ret.கோவை_const_operands = உண்மை;
      ret.has_enum_type_specifier = பொய்;
      திரும்பு ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  எனில் (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_tag (ident_loc, code, ident, have_std_attrs, std_attrs,
			 பொய்);
  திரும்பு ret;
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

நிலையான மரம்
c_parser_struct_declaration (c_parser *parser, மரம் *கோவை)
{
  கட்டமைப்பு c_declspecs *specs;
  மரம் prefix_attrs;
  மரம் all_prefix_attrs;
  மரம் decls;
  location_t decl_loc;
  எனில் (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      முழு ext;
      மரம் decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, கோவை);
      restore_extension_diagnostics (ext);
      திரும்பு decl;
    }
  எனில் (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      திரும்பு NULL_மரம்;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, பொய், உண்மை, உண்மை,
		      உண்மை, பொய், உண்மை, உண்மை, cla_nonabstract_decl);
  எனில் (parser->error)
    திரும்பு NULL_மரம்;
  எனில் (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      திரும்பு NULL_மரம்;
    }
  finish_declspecs (specs);
  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      மரம் ret;
      எனில் (specs->typespec_kind == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_tag_warned (specs, pedantic);
	  ret = NULL_மரம்;
	}
      இல்லையெனில்
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  மரம் attrs = வெற்று;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_மரம்), specs,
			   NULL_மரம், &attrs, கோவை);
	  எனில் (ret)
	    decl_attributes (&ret, attrs, 0);
	}
      திரும்பு ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  எனில் (specs->typespec_kind == ctsk_tagdef
      && மரம்_CODE (specs->type) != ENUMERAL_TYPE
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = பொய்;
      திரும்பு NULL_மரம்;
    }

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_மரம்;
  decls = NULL_மரம்;
  போது (உண்மை)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      கட்டமைப்பு c_declarator *declarator;
      தருக்க dummy = பொய்;
      எனில் (c_parser_next_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_மரம்);
      இல்லையெனில்
	declarator = c_parser_declarator (parser,
					  specs->typespec_kind != ctsk_none,
					  C_DTR_NORMAL, &dummy);
      எனில் (declarator == வெற்று)
	{
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  நிறுத்து;
	}
      எனில் (c_parser_next_token_is (parser, CPP_COLON)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  மரம் postfix_attrs = NULL_மரம்;
	  மரம் width = NULL_மரம்;
	  மரம் d;
	  எனில் (c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      width = convert_lvalue_to_rvalue (loc,
						(c_parser_கோவை_no_commas
						 (parser, வெற்று)),
						உண்மை, உண்மை).மதிப்பு;
	    }
	  எனில் (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_attributes (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, width, &all_prefix_attrs, கோவை);
	  decl_attributes (&d, chainon (postfix_attrs,
					all_prefix_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  எனில் (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					prefix_attrs);
	  இல்லையெனில்
	    all_prefix_attrs = prefix_attrs;
	  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON)
		   || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      /* Semicolon consumed in caller.  */
	      நிறுத்து;
	    }
	  இல்லையெனில்
	    {
	      c_parser_error (parser, "expected %<,%>, %<;%> or %<}%>");
	      நிறுத்து;
	    }
	}
      இல்லையெனில்
	{
	  c_parser_error (parser,
			  "expected %<:%>, %<,%>, %<;%>, %<}%> or "
			  "%<__attribute__%>");
	  நிறுத்து;
	}
    }
  திரும்பு decls;
}

/* Parse a typeof specifier (a GNU extension adopted in C23).

   typeof-specifier:
     typeof ( expression )
     typeof ( type-name )
     typeof_unqual ( expression )
     typeof_unqual ( type-name )
*/

நிலையான கட்டமைப்பு c_typespec
c_parser_typeof_specifier (c_parser *parser)
{
  தருக்க is_unqual;
  தருக்க is_std;
  கட்டமைப்பு c_typespec ret;
  ret.kind = ctsk_typeof;
  ret.spec = error_mark_முனை;
  ret.கோவை = NULL_மரம்;
  ret.கோவை_const_operands = உண்மை;
  ret.has_enum_type_specifier = பொய்;
  எனில் (c_parser_next_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = பொய்;
      மரம் spelling = c_parser_peek_token (parser)->மதிப்பு;
      is_std = (flag_isoc23
		&& strcmp (IDENTIFIER_POINTER (spelling), "typeof") == 0);
    }
  இல்லையெனில்
    {
      gcc_assert (c_parser_next_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = உண்மை;
      மரம் spelling = c_parser_peek_token (parser)->மதிப்பு;
      is_std = strcmp (IDENTIFIER_POINTER (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_typeof++;
  matching_parens parens;
  எனில் (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      திரும்பு ret;
    }
  எனில் (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      கட்டமைப்பு c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      எனில் (type != வெற்று)
	{
	  ret.spec = groktypename (type, &ret.கோவை, &ret.கோவை_const_operands);
	  எடு_maybe_used (c_type_variably_modified_p (ret.spec));
	}
    }
  இல்லையெனில்
    {
      தருக்க was_vm;
      location_t here = c_parser_peek_token (parser)->location;
      கட்டமைப்பு c_கோவை கோவை = c_parser_expression (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      எனில் (மரம்_CODE (கோவை.மதிப்பு) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (மரம்_OPERAND (கோவை.மதிப்பு, 1)))
	error_at (here, "%<typeof%> applied to a bit-field");
      mark_exp_read (கோவை.மதிப்பு);
      ret.spec = மரம்_TYPE (கோவை.மதிப்பு);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      எனில் (was_vm)
	ret.கோவை = c_fully_fold (கோவை.மதிப்பு, பொய், &ret.கோவை_const_operands);
      எடு_maybe_used (was_vm);
    }
  parens.skip_until_found_close (parser);
  எனில் (ret.spec != error_mark_முனை)
    {
      எனில் (is_unqual)
	{
	  தருக்க is_array = மரம்_CODE (ret.spec) == ARRAY_TYPE;
	  முழு quals = TYPE_QUALS (strip_array_types (ret.spec));
	  எனில் ((is_array ? quals & ~TYPE_QUAL_ATOMIC : quals)
	      != TYPE_UNQUALIFIED)
	    {
	      ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	      எனில் (quals & TYPE_QUAL_ATOMIC && is_array)
		ret.spec = c_build_qualified_type (ret.spec,
						   TYPE_QUAL_ATOMIC);
	    }
	}
      எனில் (is_std)
	{
	  /* In ISO C terms, _Noreturn is not part of the type of
	     expressions such as &abort, but in GCC it is represented
	     internally as a type qualifier.  */
	  எனில் (மரம்_CODE (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  இல்லையெனில் எனில் (FUNCTION_POINTER_TYPE_P (ret.spec)
		   && TYPE_QUALS (மரம்_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_pointer_type (TYPE_MAIN_VARIANT (மரம்_TYPE (ret.spec)));
	}
    }
  திரும்பு ret;
}

/* Parse an alignment-specifier.

   C11 6.7.5:

   alignment-specifier:
     _Alignas ( type-name )
     _Alignas ( constant-expression )
*/

நிலையான மரம்
c_parser_alignas_specifier (c_parser * parser)
{
  மரம் ret = error_mark_முனை;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNAS));
  மரம் spelling = c_parser_peek_token (parser)->மதிப்பு;
  c_parser_consume_token (parser);
  எனில் (flag_isoc99)
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  இல்லையெனில்
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு ret;
  எனில் (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      கட்டமைப்பு c_type_name *type = c_parser_type_name (parser);
      எனில் (type != வெற்று)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, வெற்று, வெற்று),
					பொய், உண்மை, 1);
    }
  இல்லையெனில்
    ret = convert_lvalue_to_rvalue (loc,
				    c_parser_கோவை_no_commas (parser, வெற்று),
				    உண்மை, உண்மை).மதிப்பு;
  parens.skip_until_found_close (parser);
  திரும்பு ret;
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

கட்டமைப்பு c_declarator *
c_parser_declarator (c_parser *parser, தருக்க type_seen_p, c_dtr_syn kind,
		     தருக்க *seen_id)
{
  /* Parse any initial pointer part.  */
  எனில் (c_parser_next_token_is (parser, CPP_MULT))
    {
      கட்டமைப்பு c_declspecs *quals_attrs = build_null_declspecs ();
      கட்டமைப்பு c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, பொய், பொய், உண்மை,
			  பொய், பொய், உண்மை, பொய், cla_prefer_id);
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      எனில் (inner == வெற்று)
	திரும்பு வெற்று;
      இல்லையெனில்
	திரும்பு make_pointer_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  திரும்பு c_parser_direct_declarator (parser, type_seen_p, kind, seen_id);
}

/* Parse a direct declarator or direct abstract declarator; arguments
   as c_parser_declarator.  */

நிலையான கட்டமைப்பு c_declarator *
c_parser_direct_declarator (c_parser *parser, தருக்க type_seen_p, c_dtr_syn kind,
			    தருக்க *seen_id)
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

  எனில் (kind != C_DTR_ABSTRACT
      && c_parser_next_token_is (parser, CPP_NAME)
      && ((type_seen_p
	   && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_kind == C_ID_ID))
    {
      கட்டமைப்பு c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->மதிப்பு);
      *seen_id = உண்மை;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      எனில் (c_parser_nth_token_starts_std_attributes (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      திரும்பு c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  எனில் (kind != C_DTR_NORMAL
      && c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      கட்டமைப்பு c_declarator *inner = build_id_declarator (NULL_மரம்);
      inner->id_loc = c_parser_peek_token (parser)->location;
      திரும்பு c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      மரம் attrs;
      கட்டமைப்பு c_declarator *inner;
      c_parser_consume_token (parser);
      தருக்க have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      எனில் (kind != C_DTR_NORMAL
	  && (c_parser_next_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_attributes (parser, 1)
		      || c_parser_next_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  கட்டமைப்பு c_arg_info *args
	    = c_parser_parms_declarator (parser, kind == C_DTR_NORMAL,
					 attrs, have_gnu_attrs);
	  எனில் (args == வெற்று)
	    திரும்பு வெற்று;
	  இல்லையெனில்
	    {
	      inner = build_id_declarator (NULL_மரம்);
	      எனில் (!(args->types
		    && args->types != error_mark_முனை
		    && மரம்_CODE (மரம்_மதிப்பு (args->types)) == IDENTIFIER_முனை)
		  && c_parser_nth_token_starts_std_attributes (parser, 1))
		{
		  மரம் std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  எனில் (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (args, inner);
	      திரும்பு c_parser_direct_declarator_inner (parser, *seen_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      எனில் (inner != வெற்று && attrs != வெற்று)
	inner = build_attrs_declarator (attrs, inner);
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  எனில் (inner == வெற்று)
	    திரும்பு வெற்று;
	  இல்லையெனில்
	    திரும்பு c_parser_direct_declarator_inner (parser, *seen_id, inner);
	}
      இல்லையெனில்
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  திரும்பு வெற்று;
	}
    }
  இல்லையெனில்
    {
      எனில் (kind == C_DTR_NORMAL)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  திரும்பு வெற்று;
	}
      இல்லையெனில்
	திரும்பு build_id_declarator (NULL_மரம்);
    }
}

/* Parse part of a direct declarator or direct abstract declarator,
   given that some (in INNER) has already been parsed; ID_PRESENT is
   true if an identifier is present, false for an abstract
   declarator.  */

நிலையான கட்டமைப்பு c_declarator *
c_parser_direct_declarator_inner (c_parser *parser, தருக்க id_present,
				  கட்டமைப்பு c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      கட்டமைப்பு c_declarator *declarator;
      கட்டமைப்பு c_declspecs *quals_attrs = build_null_declspecs ();
      கட்டமைப்பு c_கோவை dimen;
      dimen.மதிப்பு = NULL_மரம்;
      dimen.original_code = ERROR_MARK;
      dimen.original_type = NULL_மரம்;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, பொய், பொய், உண்மை,
			  பொய், பொய், பொய், பொய், cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      எனில் (c_parser_next_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  எனில் (!quals_attrs->declspecs_seen_p)
	    c_parser_declspecs (parser, quals_attrs, பொய், பொய், உண்மை,
				பொய், பொய், பொய், பொய், cla_prefer_id);
	}
      எனில் (!quals_attrs->declspecs_seen_p)
	quals_attrs = வெற்று;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      மாறிலி தருக்க static_seen = (static_loc != UNKNOWN_LOCATION);
      தருக்க star_seen = பொய்;
      எனில் (c_parser_next_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_SQUARE)
	{
	  star_seen = உண்மை;
	  c_parser_consume_token (parser);
	}
      இல்லையெனில் எனில் (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	dimen = c_parser_கோவை_no_commas (parser, வெற்று);

      எனில் (static_seen)
	{
	  எனில் (star_seen)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      star_seen = பொய்;
	      dimen.மதிப்பு = error_mark_முனை;
	    }
	  இல்லையெனில் எனில் (!dimen.மதிப்பு)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	c_parser_consume_token (parser);
      இல்லையெனில்
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  திரும்பு வெற்று;
	}
      எனில் (dimen.மதிப்பு)
	dimen = convert_lvalue_to_rvalue (brace_loc, dimen, உண்மை, உண்மை);
      declarator = build_array_declarator (brace_loc, dimen.மதிப்பு, quals_attrs,
					   static_seen, star_seen);
      எனில் (declarator == வெற்று)
	திரும்பு வெற்று;
      எனில் (c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  மரம் std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  எனில் (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = set_array_declarator_inner (declarator, inner);
      திரும்பு c_parser_direct_declarator_inner (parser, id_present, inner);
    }
  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      மரம் attrs;
      கட்டமைப்பு c_arg_info *args;
      c_parser_consume_token (parser);
      தருக்க have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      args = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      எனில் (args == வெற்று)
	திரும்பு வெற்று;
      இல்லையெனில்
	{
	  எனில் (!(args->types
		&& args->types != error_mark_முனை
		&& மரம்_CODE (மரம்_மதிப்பு (args->types)) == IDENTIFIER_முனை)
	      && c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      மரம் std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      எனில் (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (args, inner);
	  திரும்பு c_parser_direct_declarator_inner (parser, id_present, inner);
	}
    }
  திரும்பு inner;
}

/* Parse a parameter list or identifier list, including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list.  ID_LIST_OK is true if an identifier list
   is acceptable; such a list must not have attributes at the start.
   HAVE_GNU_ATTRS says whether any gnu-attributes (including empty
   attributes) were present (in which case standard attributes cannot
   occur).  */

நிலையான கட்டமைப்பு c_arg_info *
c_parser_parms_declarator (c_parser *parser, தருக்க id_list_ok, மரம் attrs,
			   தருக்க have_gnu_attrs)
{
  தள்ளு_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  எனில் (id_list_ok
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
      மரம் list = NULL_மரம், *nextp = &list;
      போது (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  *nextp = build_மரம்_list (NULL_மரம்,
				    c_parser_peek_token (parser)->மதிப்பு);
	  nextp = & மரம்_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  எனில் (c_parser_next_token_is_not (parser, CPP_COMMA))
	    நிறுத்து;
	  c_parser_consume_token (parser);
	  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      நிறுத்து;
	    }
	}
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  கட்டமைப்பு c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  எடு_scope ();
	  திரும்பு ret;
	}
      இல்லையெனில்
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  எடு_scope ();
	  திரும்பு வெற்று;
	}
    }
  இல்லையெனில்
    {
      கட்டமைப்பு c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, வெற்று, have_gnu_attrs);
      எடு_scope ();
      திரும்பு ret;
    }
}

/* Parse a parameter list (possibly empty), including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list; if HAVE_GNU_ATTRS, there were some such
   attributes (possibly empty, in which case ATTRS is NULL_TREE),
   which means standard attributes cannot start the list.  EXPR is
   NULL or an expression that needs to be evaluated for the side
   effects of array size expressions in the parameters.  */

நிலையான கட்டமைப்பு c_arg_info *
c_parser_parms_list_declarator (c_parser *parser, மரம் attrs, மரம் கோவை,
				தருக்க have_gnu_attrs)
{
  தருக்க bad_parm = பொய்;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      கட்டமைப்பு c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      திரும்பு ret;
    }
  எனில் (c_parser_next_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      கட்டமைப்பு c_arg_info *ret = build_arg_info ();

      ret->types = NULL_மரம்;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_args_stdarg_p = உண்மை;
	  c_parser_consume_token (parser);
	  திரும்பு ret;
	}
      இல்லையெனில்
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  திரும்பு வெற்று;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  போது (உண்மை)
    {
      /* Parse a parameter.  */
      கட்டமைப்பு c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_மரம்;
      have_gnu_attrs = பொய்;
      எனில் (parm == வெற்று)
	bad_parm = உண்மை;
      இல்லையெனில்
	தள்ளு_parm_decl (parm, &கோவை);
      எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  மரம் new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  தருக்க new_have_gnu_attrs
	    = c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_attributes (parser);
	  திரும்பு c_parser_parms_list_declarator (parser, new_attrs, கோவை,
						 new_have_gnu_attrs);
	}
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  எனில் (bad_parm)
	    திரும்பு வெற்று;
	  இல்லையெனில்
	    திரும்பு get_parm_info (பொய், கோவை);
	}
      எனில் (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, பொய்))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
	  திரும்பு வெற்று;
	}
      எனில் (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      எனில் (bad_parm)
		திரும்பு வெற்று;
	      இல்லையெனில்
		திரும்பு get_parm_info (உண்மை, கோவை);
	    }
	  இல்லையெனில்
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      திரும்பு வெற்று;
	    }
	}
    }
}

/* Parse a parameter declaration.  ATTRS are the gnu-attributes at the
   start of the declaration if it is the first parameter;
   HAVE_GNU_ATTRS is true if there were any gnu-attributes there (even
   empty) there.  */

நிலையான கட்டமைப்பு c_parm *
c_parser_parameter_declaration (c_parser *parser, மரம் attrs,
				தருக்க have_gnu_attrs)
{
  கட்டமைப்பு c_declspecs *specs;
  கட்டமைப்பு c_declarator *declarator;
  மரம் prefix_attrs;
  மரம் postfix_attrs = NULL_மரம்;
  தருக்க dummy = பொய்;

  /* Accept #pragmas between parameter declarations.  */
  போது (c_parser_next_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, வெற்று, NULL_மரம்);

  எனில் (!c_parser_next_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      எனில் (parser->error)
	திரும்பு வெற்று;
      c_parser_set_source_position_from_token (token);
      எனில் (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (token->மதிப்பு,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  எனில் (மாறிலி எழுத்து *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->மதிப்பு, suggestion);
	    }
	  இல்லையெனில்
	    error_at (token->location, "unknown type name %qE", token->மதிப்பு);
	  parser->error = உண்மை;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      இல்லையெனில்
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_to_end_of_parameter (parser);
      திரும்பு வெற்று;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  எனில் (attrs)
    {
      declspecs_add_attrs (உள்ளீடு_location, specs, attrs);
      attrs = NULL_மரம்;
    }
  c_parser_declspecs (parser, specs, உண்மை, உண்மை, உண்மை, உண்மை, பொய்,
		      !have_gnu_attrs, உண்மை, cla_nonabstract_decl);
  finish_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  எனில் (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_உச்சி_anonymous_type (specs->type);

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  specs->attrs = NULL_மரம்;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_PARM, &dummy);
  எனில் (declarator == வெற்று)
    {
      c_parser_skip_until_found (parser, CPP_COMMA, வெற்று);
      திரும்பு வெற்று;
    }
  எனில் (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
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
  போது (id_declarator && id_declarator->kind != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : start_loc);
  location_t param_loc = make_location (caret_loc, start_loc, end_loc);

  திரும்பு build_c_parm (specs, chainon (postfix_attrs, prefix_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

நிலையான மரம்
c_parser_asm_string_literal (c_parser *parser)
{
  மரம் str;
  முழு save_flag = warn_overlength_strings;
  warn_overlength_strings = 0;
  str = c_parser_string_literal (parser, பொய், பொய்).மதிப்பு;
  warn_overlength_strings = save_flag;
  திரும்பு str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

நிலையான மரம்
c_parser_simple_asm_கோவை (c_parser *parser)
{
  மரம் str;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு NULL_மரம்;
  str = c_parser_asm_string_literal (parser);
  எனில் (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
      திரும்பு NULL_மரம்;
    }
  திரும்பு str;
}

நிலையான மரம்
c_parser_gnu_attribute_any_word (c_parser *parser)
{
  மரம் attr_name = NULL_மரம்;

  எனில் (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      /* ??? See comment above about what keywords are accepted here.  */
      தருக்க ok;
      தேர்வு (c_parser_peek_token (parser)->keyword)
	{
	நிலை RID_STATIC:
	நிலை RID_UNSIGNED:
	நிலை RID_LONG:
	நிலை RID_CONST:
	நிலை RID_EXTERN:
	நிலை RID_REGISTER:
	நிலை RID_TYPEDEF:
	நிலை RID_SHORT:
	நிலை RID_INLINE:
	நிலை RID_NORETURN:
	நிலை RID_VOLATILE:
	நிலை RID_SIGNED:
	நிலை RID_AUTO:
	நிலை RID_RESTRICT:
	நிலை RID_COMPLEX:
	நிலை RID_THREAD:
	நிலை RID_INT:
	நிலை RID_CHAR:
	நிலை RID_FLOAT:
	நிலை RID_DOUBLE:
	நிலை RID_VOID:
	நிலை RID_DFLOAT32:
	நிலை RID_DFLOAT64:
	நிலை RID_DFLOAT128:
	நிலை RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	நிலை RID_BOOL:
	நிலை RID_BITINT:
	நிலை RID_FRACT:
	நிலை RID_ACCUM:
	நிலை RID_SAT:
	நிலை RID_TRANSACTION_ATOMIC:
	நிலை RID_TRANSACTION_CANCEL:
	நிலை RID_ATOMIC:
	நிலை RID_AUTO_TYPE:
	நிலை RID_CONSTEXPR:
	நிலை RID_INT_N_0:
	நிலை RID_INT_N_1:
	நிலை RID_INT_N_2:
	நிலை RID_INT_N_3:
	  ok = உண்மை;
	  நிறுத்து;
	இயல்பு:
	  ok = பொய்;
	  நிறுத்து;
	}
      எனில் (!ok)
	திரும்பு NULL_மரம்;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(முழு) c_parser_peek_token (parser)->keyword];
    }
  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->மதிப்பு;

  திரும்பு attr_name;
}

/* Parse attribute arguments.  This is a common form of syntax
   covering all currently valid GNU and standard attributes.

   gnu-attribute-arguments:
     identifier
     identifier , nonempty-expr-list
     expr-list

   where the "identifier" must not be declared as a type.  ??? Why not
   allow identifiers declared as types to start the arguments?  */

நிலையான மரம்
c_parser_attribute_arguments (c_parser *parser, தருக்க takes_identifier,
			      தருக்க require_string, தருக்க assume_attr,
			      தருக்க allow_empty_args)
{
  vec<மரம், va_gc> *கோவை_list;
  மரம் attr_args;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  எனில் (c_parser_next_token_is (parser, CPP_NAME)
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
      மரம் arg1 = c_parser_peek_token (parser)->மதிப்பு;
      c_parser_consume_token (parser);
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	attr_args = build_மரம்_list (NULL_மரம், arg1);
      இல்லையெனில்
	{
	  மரம் மரம்_list;
	  c_parser_consume_token (parser);
	  கோவை_list = c_parser_கோவை_list (parser, பொய், உண்மை,
					  வெற்று, வெற்று, வெற்று, வெற்று);
	  மரம்_list = build_மரம்_list_vec (கோவை_list);
	  attr_args = மரம்_cons (NULL_மரம், arg1, மரம்_list);
	  release_மரம்_vector (கோவை_list);
	}
    }
  இல்லையெனில்
    {
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  எனில் (!allow_empty_args)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_args = NULL_மரம்;
	}
      இல்லையெனில் எனில் (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  மரம் string = c_parser_string_literal (parser, பொய், உண்மை).மதிப்பு;
	  attr_args = build_மரம்_list (NULL_மரம், string);
	}
      இல்லையெனில் எனில் (assume_attr)
	{
	  மரம் cond
	    = c_parser_conditional_expression (parser, வெற்று, NULL_மரம்).மதிப்பு;
	  எனில் (!c_parser_next_token_is (parser, CPP_COMMA))
	    attr_args = build_மரம்_list (NULL_மரம், cond);
	  இல்லையெனில்
	    {
	      மரம் மரம்_list;
	      c_parser_consume_token (parser);
	      கோவை_list = c_parser_கோவை_list (parser, பொய், உண்மை,
					      வெற்று, வெற்று, வெற்று, வெற்று);
	      மரம்_list = build_மரம்_list_vec (கோவை_list);
	      attr_args = மரம்_cons (NULL_மரம், cond, மரம்_list);
	      release_மரம்_vector (கோவை_list);
	    }
	}
      இல்லையெனில்
	{
	  கோவை_list = c_parser_கோவை_list (parser, பொய், உண்மை,
					  வெற்று, வெற்று, வெற்று, வெற்று);
	  attr_args = build_மரம்_list_vec (கோவை_list);
	  release_மரம்_vector (கோவை_list);
	}
    }
  திரும்பு attr_args;
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

நிலையான மரம்
c_parser_gnu_attribute (c_parser *parser, மரம் attrs,
			தருக்க expect_comma = பொய், தருக்க empty_ok = உண்மை)
{
  தருக்க comma_first = c_parser_next_token_is (parser, CPP_COMMA);
  எனில் (!comma_first
      && !c_parser_next_token_is (parser, CPP_NAME)
      && !c_parser_next_token_is (parser, CPP_KEYWORD))
    திரும்பு NULL_மரம்;

  போது (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      எனில் (!empty_ok)
	திரும்பு attrs;
    }

  மரம் attr_name = c_parser_gnu_attribute_any_word (parser);
  எனில் (attr_name == NULL_மரம்)
    திரும்பு NULL_மரம்;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  மரம் attr;
  எனில் (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      எனில் (expect_comma && !comma_first)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  திரும்பு error_mark_முனை;
	}
      attr = build_மரம்_list (attr_name, NULL_மரம்);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      திரும்பு attrs;
    }
  c_parser_consume_token (parser);

  மரம் attr_args
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    பொய்,
				    is_attribute_p ("assume", attr_name),
				    உண்மை);

  attr = build_மரம்_list (attr_name, attr_args);
  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  இல்லையெனில்
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      திரும்பு error_mark_முனை;
    }

  எனில் (expect_comma && !comma_first)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      திரும்பு error_mark_முனை;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  திரும்பு attrs;
}

நிலையான மரம்
c_parser_gnu_attributes (c_parser *parser)
{
  மரம் attrs = NULL_மரம்;
  போது (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      தருக்க save_translate_strings_p = parser->translate_strings_p;
      parser->translate_strings_p = பொய்;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      எனில் (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  திரும்பு attrs;
	}
      எனில் (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
	  திரும்பு attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      க்கு (தருக்க expect_comma = பொய்; ; expect_comma = உண்மை)
	{
	  /* Parse a single attribute.  */
	  மரம் attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  எனில் (attr == error_mark_முனை)
	    திரும்பு attrs;
	  எனில் (!attr)
	    நிறுத்து;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      இல்லையெனில்
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  திரும்பு attrs;
	}
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      இல்லையெனில்
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  திரும்பு attrs;
	}
      parser->translate_strings_p = save_translate_strings_p;
    }

  திரும்பு attrs;
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

நிலையான வெறுமை
c_parser_balanced_token_sequence (c_parser *parser)
{
  போது (உண்மை)
    {
      c_token *token = c_parser_peek_token (parser);
      தேர்வு (token->type)
	{
	நிலை CPP_OPEN_BRACE:
	  {
	    matching_braces braces;
	    braces.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    braces.require_close (parser);
	    நிறுத்து;
	  }

	நிலை CPP_OPEN_PAREN:
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    parens.require_close (parser);
	    நிறுத்து;
	  }

	நிலை CPP_OPEN_SQUARE:
	  c_parser_consume_token (parser);
	  c_parser_balanced_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
	  நிறுத்து;

	நிலை CPP_CLOSE_BRACE:
	நிலை CPP_CLOSE_PAREN:
	நிலை CPP_CLOSE_SQUARE:
	நிலை CPP_EOF:
	  திரும்பு;

	நிலை CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, பொய்);
	  நிறுத்து;

	இயல்பு:
	  c_parser_consume_token (parser);
	  நிறுத்து;
	}
    }
}

/* Parse arguments of omp::directive or omp::decl attribute.

   directive-name ,[opt] clause-list[opt]

   For directive just remember the tokens in a vector for subsequent
   parsing.  */

நிலையான வெறுமை
c_parser_omp_directive_args (c_parser *parser, மரம் attribute, தருக்க decl_p)
{
  unsigned முழு n = 1;
  c_token *first = c_parser_peek_token (parser);
  எனில் (!c_parser_check_balanced_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_balanced_token_sequence (parser);
      மரம்_மதிப்பு (attribute) = NULL_மரம்;
      திரும்பு;
    }
  எனில் (n == 1)
    {
      error_at (first->location, "expected OpenMP directive name");
      மரம்_மதிப்பு (attribute) = NULL_மரம்;
      திரும்பு;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  க்கு (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->quick_தள்ளு (*tok);
      c_parser_consume_token (parser);
    }
  மரம் arg = make_முனை (C_TOKEN_VEC);
  C_TOKEN_VEC_TOKENS (arg) = v;
  எனில் (decl_p)
    மரம்_PUBLIC (arg) = 1;
  மரம்_மதிப்பு (attribute) = மரம்_cons (NULL_மரம், arg, மரம்_மதிப்பு (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

நிலையான வெறுமை
c_parser_omp_sequence_args (c_parser *parser, மரம் attribute)
{
  செய்
    {
      c_token *token = c_parser_peek_token (parser);
      எனில் (token->type == CPP_NAME
	  && strcmp (IDENTIFIER_POINTER (token->மதிப்பு), "omp") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_SCOPE)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  token = c_parser_peek_token (parser);
	}
      தருக்க directive = பொய்;
      மாறிலி எழுத்து *p;
      எனில் (token->type != CPP_NAME)
	p = "";
      இல்லையெனில்
	p = IDENTIFIER_POINTER (token->மதிப்பு);
      எனில் (strcmp (p, "directive") == 0)
	directive = உண்மை;
      இல்லையெனில் எனில் (strcmp (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  unsigned nesting_depth = 0;

	  போது (உண்மை)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      எனில் ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_depth)
		நிறுத்து;
	      /* If we've run out of tokens, stop.  */
	      எனில் (token->type == CPP_EOF)
		நிறுத்து;
	      எனில் (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
		நிறுத்து;
	      எனில் (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_SQUARE)
		++nesting_depth;
	      இல்லையெனில் எனில் (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_SQUARE)
		{
		  எனில் (nesting_depth-- == 0)
		    நிறுத்து;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  எனில் (c_parser_next_token_is_not (parser, CPP_COMMA))
	    நிறுத்து;
	  c_parser_consume_token (parser);
	  தொடர்;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      எனில் (parens.require_open (parser))
	{
	  எனில் (directive)
	    c_parser_omp_directive_args (parser, attribute, பொய்);
	  இல்லையெனில்
	    c_parser_omp_sequence_args (parser, attribute);
	  parens.skip_until_found_close (parser);
	  எனில் (c_parser_next_token_is_not (parser, CPP_COMMA))
	    நிறுத்து;
	  c_parser_consume_token (parser);
	}
      இல்லையெனில் எனில் (c_parser_next_token_is_not (parser, CPP_COMMA))
	நிறுத்து;
      இல்லையெனில்
	c_parser_consume_token (parser);
    }
  போது (1);
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

நிலையான மரம்
c_parser_std_attribute (c_parser *parser, தருக்க for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  மரம் ns, name, attribute;

  /* Parse the attribute-token.  */
  எனில் (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      திரும்பு error_mark_முனை;
    }
  name = canonicalize_attr_name (token->மதிப்பு);
  c_parser_consume_token (parser);
  எனில் (c_parser_next_token_is (parser, CPP_SCOPE)
      || (c_parser_next_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      எனில் (c_parser_next_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      எனில் (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  திரும்பு error_mark_முனை;
	}
      name = canonicalize_attr_name (token->மதிப்பு);
      c_parser_consume_token (parser);
    }
  இல்லையெனில்
    ns = NULL_மரம்;
  attribute = build_மரம்_list (build_மரம்_list (ns, name), NULL_மரம்);

  /* Parse the arguments, if any.  */
  மாறிலி attribute_spec *as = lookup_attribute_spec (மரம்_PURPOSE (attribute));
  எனில் (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      எனில் ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  திரும்பு error_mark_முனை;
	}
      செல் out;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    எனில் ((as && as->max_length == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_found_close (parser);
	திரும்பு error_mark_முனை;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    எனில் (as && !attribute_ignored_p (as))
      {
	தருக்க takes_identifier
	  = (ns != NULL_மரம்
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	தருக்க require_string
	  = (ns == NULL_மரம்
	     && (strcmp (IDENTIFIER_POINTER (name), "deprecated") == 0
		 || strcmp (IDENTIFIER_POINTER (name), "nodiscard") == 0));
	தருக்க assume_attr
	  = (ns != NULL_மரம்
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && strcmp (IDENTIFIER_POINTER (name), "assume") == 0);
	மரம்_மதிப்பு (attribute)
	  = c_parser_attribute_arguments (parser, takes_identifier,
					  require_string, assume_attr, பொய்);
      }
    இல்லையெனில்
      {
	எனில் ((flag_openmp || flag_openmp_simd)
	    && ns
	    && is_attribute_p ("omp", ns))
	  {
	    எனில் (is_attribute_p ("directive", name))
	      {
		c_parser_omp_directive_args (parser, attribute, பொய்);
		parens.skip_until_found_close (parser);
		திரும்பு attribute;
	      }
	    இல்லையெனில் எனில் (is_attribute_p ("decl", name))
	      {
		மரம்_மதிப்பு (மரம்_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_args (parser, attribute, உண்மை);
		parens.skip_until_found_close (parser);
		திரும்பு attribute;
	      }
	    இல்லையெனில் எனில் (is_attribute_p ("sequence", name))
	      {
		மரம்_மதிப்பு (மரம்_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_args (parser, attribute);
		parens.skip_until_found_close (parser);
		மரம்_மதிப்பு (attribute) = nreverse (மரம்_மதிப்பு (attribute));
		திரும்பு attribute;
	      }
	  }
	c_parser_balanced_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 out:
  எனில் (ns == NULL_மரம் && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (உள்ளீடு_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      திரும்பு error_mark_முனை;
    }
  திரும்பு attribute;
}

நிலையான மரம்
c_parser_std_attribute_list (c_parser *parser, தருக்க for_tm)
{
  மரம் attributes = NULL_மரம்;
  போது (உண்மை)
    {
      c_token *token = c_parser_peek_token (parser);
      எனில் (token->type == CPP_CLOSE_SQUARE)
	நிறுத்து;
      எனில் (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  தொடர்;
	}
      மரம் attribute = c_parser_std_attribute (parser, for_tm);
      எனில் (attribute != error_mark_முனை)
	{
	  மரம்_CHAIN (attribute) = attributes;
	  attributes = attribute;
	}
      எனில் (c_parser_next_token_is_not (parser, CPP_COMMA))
	நிறுத்து;
    }
  திரும்பு attributes;
}

நிலையான மரம்
c_parser_std_attribute_specifier (c_parser *parser, தருக்க for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  எனில் (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    திரும்பு NULL_மரம்;
  எனில் (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
      திரும்பு NULL_மரம்;
    }
  மரம் attributes;
  எனில் (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      auto ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      attributes = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  இல்லையெனில்
    {
      எனில் (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      attributes = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  திரும்பு nreverse (attributes);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

நிலையான தருக்க
c_parser_check_balanced_raw_token_sequence (c_parser *parser, unsigned முழு *n)
{
  போது (உண்மை)
    {
      c_token *token = c_parser_peek_nth_token_raw (parser, *n);
      தேர்வு (token->type)
	{
	நிலை CPP_OPEN_BRACE:
	  {
	    ++*n;
	    எனில் (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		எனில் (token->type == CPP_CLOSE_BRACE)
		  ++*n;
		இல்லையெனில்
		  திரும்பு பொய்;
	      }
	    இல்லையெனில்
	      திரும்பு பொய்;
	    நிறுத்து;
	  }

	நிலை CPP_OPEN_PAREN:
	  {
	    ++*n;
	    எனில் (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		எனில் (token->type == CPP_CLOSE_PAREN)
		  ++*n;
		இல்லையெனில்
		  திரும்பு பொய்;
	      }
	    இல்லையெனில்
	      திரும்பு பொய்;
	    நிறுத்து;
	  }

	நிலை CPP_OPEN_SQUARE:
	  {
	    ++*n;
	    எனில் (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		எனில் (token->type == CPP_CLOSE_SQUARE)
		  ++*n;
		இல்லையெனில்
		  திரும்பு பொய்;
	      }
	    இல்லையெனில்
	      திரும்பு பொய்;
	    நிறுத்து;
	  }

	நிலை CPP_CLOSE_BRACE:
	நிலை CPP_CLOSE_PAREN:
	நிலை CPP_CLOSE_SQUARE:
	நிலை CPP_EOF:
	  திரும்பு உண்மை;

	இயல்பு:
	  ++*n;
	  நிறுத்து;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

நிலையான தருக்க
c_parser_nth_token_starts_std_attributes (c_parser *parser, unsigned முழு n)
{
  எனில் (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_SQUARE
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_SQUARE))
    திரும்பு பொய்;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  எனில் (!c_dialect_objc ())
    திரும்பு உண்மை;
  n += 2;
  எனில் (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    திரும்பு பொய்;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  எனில் (token->type != CPP_CLOSE_SQUARE)
    திரும்பு பொய்;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  திரும்பு token->type == CPP_CLOSE_SQUARE;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

நிலையான size_t
c_parser_skip_std_attribute_spec_seq (c_parser *parser, size_t n)
{
  size_t orig_n = n;
  போது (உண்மை)
    {
      எனில் (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_SQUARE
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_SQUARE))
	{
	  unsigned முழு m = n + 2;
	  எனில் (!c_parser_check_balanced_raw_token_sequence (parser, &m))
	    திரும்பு orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  எனில் (token->type != CPP_CLOSE_SQUARE)
	    திரும்பு orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  எனில் (token->type != CPP_CLOSE_SQUARE)
	    திரும்பு orig_n;
	  n = m + 2;
	}
      இல்லையெனில்
	நிறுத்து;
    }
  திரும்பு n;
}

நிலையான மரம்
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  மரம் attributes = NULL_மரம்;
  செய்
    {
      மரம் attrs = c_parser_std_attribute_specifier (parser, பொய்);
      attributes = chainon (attributes, attrs);
    }
  போது (c_parser_nth_token_starts_std_attributes (parser, 1));
  திரும்பு attributes;
}

/* Parse a type name (C90 6.5.5, C99 6.7.6, C11 6.7.7).  ALIGNAS_OK
   says whether alignment specifiers are OK (only in cases that might
   be the type name of a compound literal).

   type-name:
     specifier-qualifier-list abstract-declarator[opt]
*/

கட்டமைப்பு c_type_name *
c_parser_type_name (c_parser *parser, தருக்க alignas_ok)
{
  கட்டமைப்பு c_declspecs *specs = build_null_declspecs ();
  கட்டமைப்பு c_declarator *declarator;
  கட்டமைப்பு c_type_name *ret;
  தருக்க dummy = பொய்;
  c_parser_declspecs (parser, specs, பொய், உண்மை, உண்மை, alignas_ok, பொய்,
		      பொய், உண்மை, cla_prefer_type);
  எனில் (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      திரும்பு வெற்று;
    }
  எனில் (specs->type != error_mark_முனை)
    {
      pending_xref_error ();
      finish_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      எனில் (specs->typespec_kind == ctsk_tagdef)
	verify_counted_by_for_உச்சி_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_ABSTRACT, &dummy);
  எனில் (declarator == வெற்று)
    திரும்பு வெற்று;
  ret = XOBNEW (&parser_obstack, கட்டமைப்பு c_type_name);
  ret->specs = specs;
  ret->declarator = declarator;
  திரும்பு ret;
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

நிலையான கட்டமைப்பு c_கோவை
c_parser_initializer (c_parser *parser, மரம் decl)
{
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    திரும்பு c_parser_braced_init (parser, NULL_மரம், பொய், வெற்று,
				 decl != error_mark_முனை
				 && C_DECL_VARIABLE_SIZE (decl));
  இல்லையெனில்
    {
      கட்டமைப்பு c_கோவை ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_கோவை_no_commas (parser, வெற்று);
      எனில் (decl != error_mark_முனை && C_DECL_VARIABLE_SIZE (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.set_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      எனில் (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !மரம்_STATIC (decl)
	  && ret.மதிப்பு == decl
	  && !warning_enabled_at (DECL_SOURCE_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      எனில் (மரம்_CODE (ret.மதிப்பு) != STRING_CST
	  && (மரம்_CODE (ret.மதிப்பு) != COMPOUND_LITERAL_கோவை
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_கோவை_DECL
					    (ret.மதிப்பு))))
	ret = convert_lvalue_to_rvalue (loc, ret, உண்மை, உண்மை, உண்மை);
      திரும்பு ret;
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

நிலையான கட்டமைப்பு c_கோவை
c_parser_braced_init (c_parser *parser, மரம் type, தருக்க nested_p,
		      கட்டமைப்பு obstack *outer_obstack, தருக்க varsize_p)
{
  கட்டமைப்பு c_கோவை ret;
  கட்டமைப்பு obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  தருக்க save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = பொய்;
  தருக்க zero_init_padding_bits = பொய்;
  matching_braces braces;
  braces.consume_open (parser);
  எனில் (nested_p)
    {
      finish_implicit_inits (brace_loc, outer_obstack);
      தள்ளு_init_level (brace_loc, 0, &braced_init_obstack);
    }
  இல்லையெனில்
    really_start_incremental_init (type);
  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      எனில் (flag_isoc23)
	zero_init_padding_bits = உண்மை;
    }
  இல்லையெனில்
    {
      எனில் (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      போது (உண்மை)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  எனில் (parser->error)
	    நிறுத்து;
	  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      last_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      போது (c_parser_next_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_கோவை embed_val;
		  embed_val.மதிப்பு = embed->மதிப்பு;
		  embed_val.original_code = RAW_DATA_CST;
		  embed_val.original_type = integer_type_முனை;
		  set_c_கோவை_source_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, பொய்,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_next_token_is (parser,
							       CPP_COMMA));
		  last_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  இல்லையெனில்
	    நிறுத்து;
	  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    நிறுத்து;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *next_tok = c_parser_peek_token (parser);
  எனில் (next_tok->type != CPP_CLOSE_BRACE)
    {
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = வெற்று;
      braces.skip_until_found_close (parser);
      எடு_init_level (brace_loc, 0, &braced_init_obstack, last_init_list_comma);
      obstack_free (&braced_init_obstack, வெற்று);
      திரும்பு ret;
    }
  location_t close_loc = next_tok->location;
  c_parser_consume_token (parser);
  ret = எடு_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  எனில் (zero_init_padding_bits
      && ret.மதிப்பு
      && மரம்_CODE (ret.மதிப்பு) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_BITS (ret.மதிப்பு) = 1;
  obstack_free (&braced_init_obstack, வெற்று);
  set_c_கோவை_source_range (&ret, brace_loc, close_loc);
  திரும்பு ret;
}

/* Parse a nested initializer, including designators.  */

நிலையான வெறுமை
c_parser_initelt (c_parser *parser, கட்டமைப்பு obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  எனில் (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      set_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->மதிப்பு,
		      c_parser_peek_token (parser)->location,
		      braced_init_obstack);
      /* Use the colon as the error location.  */
      pedwarn (c_parser_peek_2nd_token (parser)->location, OPT_Wpedantic,
	       "obsolete use of designated initializer with %<:%>");
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  இல்லையெனில்
    {
      /* des_seen is 0 if there have been no designators, 1 if there
	 has been a single array designator and 2 otherwise.  */
      முழு des_seen = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      போது (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
	     || c_parser_next_token_is (parser, CPP_DOT))
	{
	  முழு des_prev = des_seen;
	  எனில் (!des_seen)
	    des_loc = c_parser_peek_token (parser)->location;
	  எனில் (des_seen < 2)
	    des_seen++;
	  எனில் (c_parser_next_token_is (parser, CPP_DOT))
	    {
	      des_seen = 2;
	      c_parser_consume_token (parser);
	      எனில் (c_parser_next_token_is (parser, CPP_NAME))
		{
		  set_init_label (des_loc, c_parser_peek_token (parser)->மதிப்பு,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      இல்லையெனில்
		{
		  கட்டமைப்பு c_கோவை init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = வெற்று;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_found (parser, CPP_COMMA, வெற்று);
		  process_init_element (உள்ளீடு_location, init, பொய்,
					braced_init_obstack);
		  திரும்பு;
		}
	    }
	  இல்லையெனில்
	    {
	      கட்டமைப்பு c_கோவை first_கோவை;
	      மரம் first, second;
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
	      எனில் (des_prev == 1 && c_dialect_objc ())
		{
		  des_seen = des_prev;
		  நிறுத்து;
		}
	      எனில் (des_prev == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  மரம் rec, args;
		  கட்டமைப்பு c_கோவை mexpr;
		  c_parser_consume_token (parser);
		  எனில் (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_kind
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_kind
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      மரம் id = c_parser_peek_token (parser)->மதிப்பு;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      செல் parse_message_args;
		    }
		  array_index_loc = c_parser_peek_token (parser)->location;
		  first_கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
		  mark_exp_read (first_கோவை.மதிப்பு);
		  எனில் (c_parser_next_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    செல் array_desig_after_first;
		  first = first_கோவை.மதிப்பு;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = first;
		  போது (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      கட்டமைப்பு c_கோவை next;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      next = c_parser_கோவை_no_commas (parser, வெற்று);
		      next = convert_lvalue_to_rvalue (exp_loc, next,
						       உண்மை, உண்மை);
		      rec = build_compound_கோவை (comma_loc, rec, next.மதிப்பு);
		    }
		parse_message_args:
		  /* Now parse the objc-message-args.  */
		  args = c_parser_objc_message_args (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					     "expected %<]%>");
		  mexpr.மதிப்பு
		    = objc_build_message_கோவை (rec, args);
		  mexpr.original_code = ERROR_MARK;
		  mexpr.original_type = வெற்று;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  திரும்பு;
		}
	      c_parser_consume_token (parser);
	      array_index_loc = c_parser_peek_token (parser)->location;
	      first_கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	      mark_exp_read (first_கோவை.மதிப்பு);
	    array_desig_after_first:
	      first_கோவை = convert_lvalue_to_rvalue (array_index_loc,
						     first_கோவை,
						     உண்மை, உண்மை);
	      first = first_கோவை.மதிப்பு;
	      எனில் (c_parser_next_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  second = convert_lvalue_to_rvalue (ellipsis_loc,
						     (c_parser_கோவை_no_commas
						      (parser, வெற்று)),
						     உண்மை, உண்மை).மதிப்பு;
		  mark_exp_read (second);
		}
	      இல்லையெனில்
		second = NULL_மரம்;
	      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		{
		  c_parser_consume_token (parser);
		  set_init_index (array_index_loc, first, second,
				  braced_init_obstack);
		  எனில் (second)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      இல்லையெனில்
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					   "expected %<]%>");
	    }
	}
      எனில் (des_seen >= 1)
	{
	  எனில் (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  இல்லையெனில்
	    {
	      எனில் (des_seen == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      இல்லையெனில்
		{
		  கட்டமைப்பு c_கோவை init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = வெற்று;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_found (parser, CPP_COMMA, வெற்று);
		  process_init_element (உள்ளீடு_location, init, பொய்,
					braced_init_obstack);
		  திரும்பு;
		}
	    }
	}
    }
  c_parser_initval (parser, வெற்று, braced_init_obstack);
}

/* Parse a nested initializer; as c_parser_initializer but parses
   initializers within braced lists, after any designators have been
   applied.  If AFTER is not NULL then it is an Objective-C message
   expression which is the primary-expression starting the
   initializer.  */

நிலையான வெறுமை
c_parser_initval (c_parser *parser, கட்டமைப்பு c_கோவை *after,
		  கட்டமைப்பு obstack * braced_init_obstack)
{
  கட்டமைப்பு c_கோவை init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  எனில் (c_parser_next_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_மரம், உண்மை,
				 braced_init_obstack, பொய்);
  இல்லையெனில்
    {
      init = c_parser_கோவை_no_commas (parser, after);
      எனில் (init.மதிப்பு != NULL_மரம்
	  && மரம்_CODE (init.மதிப்பு) != STRING_CST
	  && (மரம்_CODE (init.மதிப்பு) != COMPOUND_LITERAL_கோவை
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_கோவை_DECL
					    (init.மதிப்பு))))
	init = convert_lvalue_to_rvalue (loc, init, உண்மை, உண்மை, உண்மை);
    }
  மரம் val = init.மதிப்பு;
  process_init_element (loc, init, பொய், braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  நிலையான unsigned vals_to_ignore;
  எனில் (vals_to_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_to_ignore;
  இல்லையெனில் எனில் (val
	   && மரம்_CODE (val) == INTEGER_CST
	   && மரம்_TYPE (val) == integer_type_முனை
	   && c_parser_next_token_is (parser, CPP_COMMA))
    எனில் (unsigned முழு len = c_maybe_optimize_large_byte_initializer ())
      {
	எழுத்து buf1[64];
	unsigned முழு i;
	gcc_checking_assert (len >= 64);
	location_t last_loc = UNKNOWN_LOCATION;
	க்கு (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    எனில் (tok->type != CPP_COMMA)
	      நிறுத்து;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    எனில் (tok->type != CPP_எண்
		|| மரம்_CODE (tok->மதிப்பு) != INTEGER_CST
		|| மரம்_TYPE (tok->மதிப்பு) != integer_type_முனை
		|| wi::neg_p (wi::to_wide (tok->மதிப்பு))
		|| wi::to_widest (tok->மதிப்பு) > UCHAR_MAX)
	      நிறுத்து;
	    buf1[i] = (எழுத்து) மரம்_to_uhwi (tok->மதிப்பு);
	    எனில் (i == 0)
	      loc = tok->location;
	    last_loc = tok->location;
	  }
	எனில் (i < 64)
	  {
	    vals_to_ignore = i;
	    திரும்பு;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	எனில் (tok->type == CPP_CLOSE_BRACE && len != INT_MAX)
	  len = i;
	இல்லையெனில் எனில் (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_எண்))
	  {
	    vals_to_ignore = i;
	    திரும்பு;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	unsigned முழு max_len = 131072 - offsetof (கட்டமைப்பு மரம்_string, str) - 1;
	unsigned முழு orig_len = len;
	unsigned முழு off = 0, last = 0;
	எனில் (!wi::neg_p (wi::to_wide (val)) && wi::to_widest (val) <= UCHAR_MAX)
	  off = 1;
	len = MIN (len, max_len - off);
	எழுத்து *buf2 = XNEWVEC (எழுத்து, len + off);
	எனில் (off)
	  buf2[0] = (எழுத்து) மரம்_to_uhwi (val);
	memcpy (buf2 + off, buf1, i);
	க்கு (unsigned முழு j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	க்கு (; i < len; ++i)
	  {
	    எனில் (!c_parser_next_token_is (parser, CPP_COMMA))
	      நிறுத்து;
	    tok = c_parser_peek_2nd_token (parser);
	    எனில் (tok->type != CPP_எண்
		|| மரம்_CODE (tok->மதிப்பு) != INTEGER_CST
		|| மரம்_TYPE (tok->மதிப்பு) != integer_type_முனை
		|| wi::neg_p (wi::to_wide (tok->மதிப்பு))
		|| wi::to_widest (tok->மதிப்பு) > UCHAR_MAX)
	      நிறுத்து;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    எனில் (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      நிறுத்து;
	    buf2[i + off] = (எழுத்து) மரம்_to_uhwi (tok->மதிப்பு);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    எனில் (orig_len == INT_MAX
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_எண்)))
	      {
		last = 1;
		நிறுத்து;
	      }
	    last_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_முனை (RAW_DATA_CST);
	மரம்_TYPE (val) = integer_type_முனை;
	RAW_DATA_LENGTH (val) = i;
	மரம் owner = build_string (i + off + last, buf2);
	XDELETEVEC (buf2);
	மரம்_TYPE (owner) = build_array_type_nelts (unsigned_char_type_முனை,
						    i + off + last);
	RAW_DATA_OWNER (val) = owner;
	RAW_DATA_POINTER (val) = மரம்_STRING_POINTER (owner) + off;
	init.மதிப்பு = val;
	set_c_கோவை_source_range (&init, loc, last_loc);
	init.original_code = RAW_DATA_CST;
	init.original_type = integer_type_முனை;
	init.m_decimal = 0;
	process_init_element (loc, init, பொய், braced_init_obstack);
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

நிலையான மரம்
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  மரம் stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  எனில் (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (உண்மை);
      c_end_compound_stmt (brace_loc, stmt, உண்மை);
      திரும்பு error_mark_முனை;
    }
  stmt = c_begin_compound_stmt (உண்மை);
  location_t end_loc = c_parser_compound_statement_nostart (parser);
  எனில் (endlocp)
    *endlocp = end_loc;

  திரும்பு c_end_compound_stmt (brace_loc, stmt, உண்மை);
}

/* Diagnose errors related to imperfectly nested loops in an OMP
   loop construct.  This function is called when such code is seen.
   Only issue one such diagnostic no matter how much invalid
   intervening code there is in the loop.
   FIXME: maybe the location associated with the diagnostic should
   be the current parser token instead of the location of the outer loop
   nest.  */

நிலையான வெறுமை
check_omp_intervening_code (c_parser *parser)
{
  கட்டமைப்பு omp_for_parse_data *omp_for_parse_state = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);

  எனில் (!omp_for_parse_state->in_intervening_code)
    திரும்பு;
  omp_for_parse_state->saw_intervening_code = உண்மை;

  /* Only diagnose errors related to perfect nesting once.  */
  எனில் (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      எனில் (omp_for_parse_state->code == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = உண்மை;
	}
      இல்லையெனில் எனில் (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = உண்மை;
	}
      இல்லையெனில் எனில் (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = உண்மை;
	}
      இல்லையெனில் எனில் (omp_for_parse_state->code == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = உண்மை;
	}
      எனில் (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->fail = உண்மை;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
நிலையான வெறுமை
add_structured_block_stmt (மரம் sl)
{
  எனில் (மரம்_CODE (sl) != STATEMENT_LIST
      || !tsi_end_p (tsi_start (sl)))
    add_stmt (build1 (OMP_STRUCTURED_BLOCK, void_type_முனை, sl));
}

கட்டமைப்பு c_omp_attribute_data
{
  vec<c_token, va_gc> *tokens;
  மாறிலி c_omp_directive *dir;
  c_omp_directive_kind kind;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

நிலையான தருக்க
c_parser_handle_statement_omp_attributes (c_parser *parser, மரம் &attrs,
					  தருக்க *have_std_attrs)
{
  எனில் (!flag_openmp && !flag_openmp_simd)
    திரும்பு பொய்;

  auto_vec<c_omp_attribute_data, 16> vd;
  முழு cnt = 0;
  முழு tokens = 0;
  தருக்க bad = பொய்;
  க்கு (மரம் *pa = &attrs; *pa; )
    எனில் (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	க்கு (மரம் a = மரம்_மதிப்பு (*pa); a; a = மரம்_CHAIN (a))
	  {
	    மரம் d = மரம்_மதிப்பு (a);
	    gcc_assert (மரம்_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    எனில் (parser->omp_attrs_forbidden_p)
	      {
		error_at (first->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = பொய்;
		bad = உண்மை;
	      }
	    இல்லையெனில் எனில் (மரம்_PUBLIC (d))
	      {
		error_at (first->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		bad = உண்மை;
	      }
	    மாறிலி எழுத்து *directive[3] = {};
	    க்கு (முழு i = 0; i < 3; i++)
	      {
		மரம் id = NULL_மரம்;
		எனில் (first + i == last)
		  நிறுத்து;
		எனில் (first[i].type == CPP_NAME)
		  id = first[i].மதிப்பு;
		இல்லையெனில் எனில் (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(முழு) first[i].keyword];
		இல்லையெனில்
		  நிறுத்து;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    மாறிலி c_omp_directive *dir = வெற்று;
	    எனில் (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    எனில் (dir == வெற்று)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  மரம்_PUBLIC (d) ? "omp::decl" : "omp::directive");
		தொடர்;
	      }
	    c_omp_directive_kind kind = dir->kind;
	    எனில் (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		எனில் (directive[1]
		    && (strcmp (directive[1], "depend") == 0
			|| strcmp (directive[1], "doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
		இல்லையெனில் எனில் (first + 2 < last
			 && first[1].type == CPP_COMMA
			 && first[2].type == CPP_NAME
			 && (strcmp (IDENTIFIER_POINTER (first[2].மதிப்பு),
				     "depend") == 0
			     || strcmp (IDENTIFIER_POINTER (first[2].மதிப்பு),
					"doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
	      }
	    இல்லையெனில் எனில் (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		முழு paren_depth = 0;
		க்கு (முழு i = 1; first + i < last; i++)
		  எனில் (first[i].type == CPP_OPEN_PAREN)
		    paren_depth++;
		  இல்லையெனில் எனில் (first[i].type == CPP_CLOSE_PAREN)
		    paren_depth--;
		  இல்லையெனில் எனில் (paren_depth == 0
			   && first + i + 2 < last
			   && first[i].type == CPP_NAME
			   && first[i + 1].type == CPP_OPEN_PAREN
			   && first[i + 2].type == CPP_NAME
			   && !strcmp (IDENTIFIER_POINTER (first[i].மதிப்பு),
				       "at")
			   && !strcmp (IDENTIFIER_POINTER (first[i
								 + 2].மதிப்பு),
				       "execution"))
		    {
		      kind = C_OMP_DIR_STANDALONE;
		      நிறுத்து;
		    }
	      }
	    c_omp_attribute_data v = { toks, dir, kind };
	    vd.safe_தள்ளு (v);
	    எனில் (flag_openmp || dir->simd)
	      tokens += (last - first) + 1;
	  }
	c_omp_attribute_data v = {};
	vd.safe_தள்ளு (v);
	*pa = மரம்_CHAIN (*pa);
      }
    இல்லையெனில்
      pa = &மரம்_CHAIN (*pa);

  எனில் (bad)
    {
    fail:
      எனில் (have_std_attrs && attrs == வெற்று)
	*have_std_attrs = பொய்;
      திரும்பு பொய்;
    }

  unsigned முழு i;
  c_omp_attribute_data *v;
  c_omp_attribute_data *construct_seen = nullptr;
  c_omp_attribute_data *standalone_seen = nullptr;
  c_omp_attribute_data *prev_standalone_seen = nullptr;
  FOR_EACH_VEC_ELT (vd, i, v)
    எனில் (v->tokens)
      {
	எனில் (v->kind == C_OMP_DIR_CONSTRUCT && !construct_seen)
	  construct_seen = v;
	இல்லையெனில் எனில் (v->kind == C_OMP_DIR_STANDALONE && !standalone_seen)
	  standalone_seen = v;
      }
    இல்லையெனில்
      {
	எனில் (standalone_seen && !prev_standalone_seen)
	  {
	    prev_standalone_seen = standalone_seen;
	    standalone_seen = nullptr;
	  }
      }

  எனில் (cnt > 1 && construct_seen)
    {
      error_at ((*construct_seen->tokens)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      செல் fail;
    }
  எனில் (cnt > 1 && standalone_seen && prev_standalone_seen)
    {
      error_at ((*standalone_seen->tokens)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      செல் fail;
    }

  எனில் (prev_standalone_seen)
    standalone_seen = prev_standalone_seen;
  எனில் (standalone_seen
      && !c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_seen->tokens->address ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      செல் fail;
    }
  எனில் (cnt && c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      எண்ணிக்கை pragma_kind kind = token->pragma_kind;
      எனில் (kind >= PRAGMA_OMP__START_ && kind <= PRAGMA_OMP__LAST_)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  செல் fail;
	}
    }

  எனில் (!tokens)
    திரும்பு பொய்;

  unsigned முழு tokens_avail = parser->tokens_avail;

  tokens++;
  vec<c_token, va_gc> *toks = வெற்று;
  vec_safe_reserve (toks, tokens, உண்மை);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      எனில் (!v->tokens)
	தொடர்;
      எனில் (!flag_openmp && !v->dir->simd)
	தொடர்;
      c_token *first = v->tokens->address ();
      c_token *last = first + v->tokens->length ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_kind = pragma_kind (v->dir->id);
      tok.location = first->location;
      toks->quick_தள்ளு (tok);
      போது (++first < last)
	toks->quick_தள்ளு (*first);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = last[-1].location;
      toks->quick_தள்ளு (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->last ().location;
  toks->quick_தள்ளு (tok);

  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = tokens;
  திரும்பு உண்மை;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

நிலையான வெறுமை
c_parser_handle_directive_omp_attributes (மரம் &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  எனில் (!flag_openmp && !flag_openmp_simd)
    திரும்பு;

  க்கு (மரம் *pa = &attrs; *pa; )
    எனில் (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	முழு cnt = 0;
	க்கு (மரம் *pa2 = &மரம்_மதிப்பு (*pa); *pa2; )
	  {
	    மரம் a = *pa2;
	    மரம் d = மரம்_மதிப்பு (a);
	    gcc_assert (மரம்_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    மாறிலி எழுத்து *directive[3] = {};
	    க்கு (முழு i = 0; i < 3; i++)
	      {
		மரம் id = NULL_மரம்;
		எனில் (first + i == last)
		  நிறுத்து;
		எனில் (first[i].type == CPP_NAME)
		  id = first[i].மதிப்பு;
		இல்லையெனில் எனில் (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(முழு) first[i].keyword];
		இல்லையெனில்
		  நிறுத்து;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    மாறிலி c_omp_directive *dir = வெற்று;
	    எனில் (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    எனில் (dir == வெற்று)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  மரம்_PUBLIC (d) ? "omp::decl" : "omp::directive");
		*pa2 = மரம்_CHAIN (a);
	      }
	    இல்லையெனில் எனில் (dir->id == PRAGMA_OMP_DECLARE
		     && (strcmp (directive[1], "simd") == 0
			 || strcmp (directive[1], "variant") == 0))
	      {
		எனில் (pragma_clauses)
		  {
		    error_at (first->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    க்கு (pa = &attrs; *pa; )
		      எனில் (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = மரம்_CHAIN (*pa);
		      இல்லையெனில்
			pa = &மரம்_CHAIN (*pa);
		    திரும்பு;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->length ()
				       + toks->length () + 2);
		க்கு (++first; first < last; ++first)
		  attr_clauses->quick_தள்ளு (*first);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = last[-1].location;
		attr_clauses->quick_தள்ளு (tok);
		*pa2 = மரம்_CHAIN (a);
	      }
	    இல்லையெனில்
	      pa2 = &மரம்_CHAIN (a);
	  }
	எனில் (cnt && மரம்_மதிப்பு (*pa) == NULL_மரம்)
	  *pa = மரம்_CHAIN (*pa);
	இல்லையெனில்
	  pa = &மரம்_CHAIN (*pa);
      }
    இல்லையெனில்
      pa = &மரம்_CHAIN (*pa);
  எனில் (attr_clauses->length ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->last ().location;
      attr_clauses->quick_தள்ளு (tok);
      attr_clauses->quick_தள்ளு (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

நிலையான மரம்
c_parser_handle_musttail (c_parser *parser, மரம் std_attrs, attr_state &attr)
{
  எனில் (c_parser_next_token_is_keyword (parser, RID_RETURN))
    {
      எனில் (மரம் a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  க்கு (; a; a = lookup_attribute ("gnu", "musttail", மரம்_CHAIN (a)))
	    எனில் (மரம்_மதிப்பு (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = உண்மை;
	}
      எனில் (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = உண்மை;
	}
    }
  திரும்பு std_attrs;
}

/* Return a statement before optional series of LABEL_EXPR/CASE_LABEL_EXPRs.
   Instead of collecting vectors of labels before each stmt just in case
   the statement would be iteration or switch statement for named loops,
   we just remember last emitted statement and let the iteration/switch
   statement search backwards in cur_stmt_list until that stmt for loop
   names if any.  */

நிலையான மரம்
get_before_labels ()
{
  எனில் (!building_stmt_list_p ())
    திரும்பு NULL_மரம்;
  மரம்_stmt_iterator tsi = tsi_last (cur_stmt_list);
  எனில் (tsi_end_p (tsi))
    திரும்பு NULL_மரம்;
  திரும்பு tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

நிலையான location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  தருக்க last_stmt = பொய்;
  தருக்க last_label = பொய்;
  தருக்க save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  கட்டமைப்பு omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  தருக்க in_omp_loop_block
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : பொய்;
  மரம் sl = NULL_மரம்;
  attr_state astate = {};

  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      add_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      திரும்பு endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  எனில் (in_omp_loop_block)
    sl = தள்ளு_stmt_list ();

  mark_valid_location_for_stdc_pragma (உண்மை);
  எனில் (c_parser_next_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (பொய்);
      எனில் (in_omp_loop_block)
	check_omp_intervening_code (parser);
      போது (c_parser_next_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  போது (உண்மை)
	    {
	      மரம் label;
	      எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  நிறுத்து;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->மதிப்பு);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      add_stmt (build_stmt (label_loc, DECL_கோவை, label));
	      c_parser_consume_token (parser);
	      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      இல்லையெனில்
		நிறுத்து;
	    }
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      திரும்பு endloc;
    }
  மரம் before_labels = get_before_labels ();
  போது (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_point_location_if_in_system_header (loc);

      தருக்க want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : பொய்);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      எனில் (in_omp_loop_block && !last_label)
	{
	  மரம்_code code = omp_for_parse_state->code;
	  எனில் (want_nested_loop
	      && c_parser_omp_next_tokens_can_be_canon_loop (parser, code,
							     பொய்))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      add_structured_block_stmt (எடு_stmt_list (sl));
	      omp_for_parse_state->depth++;
	      add_stmt (c_parser_omp_loop_nest (parser, வெற்று));
	      omp_for_parse_state->depth--;
	      sl = தள்ளு_stmt_list ();
	      parser->error = பொய்;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      தொடர்;
	    }
	  இல்லையெனில் எனில் (want_nested_loop
		   && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      மரம் pre_sl = எடு_stmt_list (sl);
	      மரம் nested_sl = தள்ளு_stmt_list ();
	      mark_valid_location_for_stdc_pragma (பொய்);
	      c_parser_statement_after_labels (parser, வெற்று, NULL_மரம்);
	      nested_sl = எடு_stmt_list (nested_sl);
	      எனில் (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_code (parser);
		  sl = தள்ளு_stmt_list ();
		  add_stmt (pre_sl);
		  add_stmt (nested_sl);
		}
	      இல்லையெனில்
		{
		  /* It contains the nested loop.  */
		  add_structured_block_stmt (pre_sl);
		  add_stmt (nested_sl);
		  sl = தள்ளு_stmt_list ();
		}
	      parser->error = பொய்;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      தொடர்;
	    }
	  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      /* Prior to implementing the OpenMP 5.1 syntax for canonical
		 loop form, GCC used to accept an empty statements that
		 would now be flagged as intervening code.  Continue to
		 do that, as an extension.  */
	      /* FIXME:  Maybe issue a warning or something here?  */
	      c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
	      தொடர்;
	    }
	}

      /* Standard attributes may start a label, statement or declaration.  */
      தருக்க have_std_attrs
	= c_parser_nth_token_starts_std_attributes (parser, 1);
      மரம் std_attrs = NULL_மரம்;
      எனில் (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      எனில் (c_parser_next_token_is_keyword (parser, RID_CASE)
	  || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  எனில் (c_parser_next_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  இல்லையெனில்
	    label_loc = c_parser_peek_token (parser)->location;
	  last_label = உண்மை;
	  last_stmt = பொய்;
	  mark_valid_location_for_stdc_pragma (பொய்);
	  எனில் (in_omp_loop_block)
	    check_omp_intervening_code (parser);
	  c_parser_label (parser, std_attrs);
	}
      இல்லையெனில் எனில் (c_parser_next_tokens_start_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_attributes
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_next_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = உண்மை)))
	{
	  எனில் (last_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  எனில் (in_omp_loop_block)
	    {
	      check_omp_intervening_code (parser);
	      omp_for_parse_state->want_nested_loop = பொய்;
	    }
	  mark_valid_location_for_stdc_pragma (பொய்);
	  தருக்க fallthru_attr_p = பொய்;
	  c_parser_declaration_or_fndef (parser, உண்மை, !have_std_attrs,
					 உண்மை, உண்மை, உண்மை, பொய், வெற்று,
					 வெற்று, have_std_attrs, std_attrs,
					 வெற்று, &fallthru_attr_p);

	  எனில் (in_omp_loop_block)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  எனில் (last_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  last_stmt = fallthru_attr_p;
	  last_label = பொய்;
	  before_labels = get_before_labels ();
	}
      இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  If standard attributes have already
	     been seen, it must start a statement, not a declaration,
	     but standard attributes starting a declaration may appear
	     after __extension__.  */
	  போது (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  எனில் (!have_std_attrs
	      && (c_parser_next_tokens_start_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_attributes (parser, 2)))
	    {
	      முழு ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      last_label = பொய்;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      எனில் (in_omp_loop_block)
		{
		  check_omp_intervening_code (parser);
		  omp_for_parse_state->want_nested_loop = பொய்;
		}
	      mark_valid_location_for_stdc_pragma (பொய்);
	      c_parser_declaration_or_fndef (parser, உண்மை, உண்மை, உண்மை, உண்மை,
					     உண்மை, பொய்);
	      எனில் (in_omp_loop_block)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      எனில் (last_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      last_stmt = பொய்;
	      before_labels = get_before_labels ();
	    }
	  இல்லையெனில்
	    செல் statement;
	}
      இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  எனில் (have_std_attrs && !parser->in_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  இல்லையெனில் எனில் (std_attrs)
	    c_warn_unused_attributes (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  எனில் (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = பொய்;
	  எனில் (c_parser_pragma (parser,
			       last_label ? pragma_stmt : pragma_compound,
			       வெற்று, before_labels))
	    {
	      last_label = பொய்;
	      last_stmt = உண்மை;
	      எனில் (omp_for_parse_state)
		check_omp_intervening_code (parser);
	    }
	  எனில் (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  திரும்பு c_parser_peek_token (parser)->location;
	}
      இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_ELSE))
        {
          எனில் (parser->in_if_block)
            {
	      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	      error_at (loc, "expected %<}%> before %<else%>");
	      திரும்பு c_parser_peek_token (parser)->location;
            }
          இல்லையெனில்
            {
              error_at (loc, "%<else%> without a previous %<if%>");
              c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
              தொடர்;
            }
        }
      இல்லையெனில்
	{
	statement:
	  c_warn_unused_attributes (std_attrs);
	  last_label = பொய்;
	  last_stmt = உண்மை;
	  mark_valid_location_for_stdc_pragma (பொய்);
	  எனில் (!omp_for_parse_state)
	    c_parser_statement_after_labels (parser, வெற்று, before_labels,
					     வெற்று, astate);
	  இல்லையெனில்
	    {
	      /* In canonical loop nest form, nested loops can only appear
		 directly, or in a directly nested compound statement.  We
		 already took care of those cases above, so now we have
		 something else.  This statement and everything inside
		 it must be intervening code.  */
	      omp_for_parse_state->want_nested_loop = பொய்;
	      check_omp_intervening_code (parser);
	      c_parser_statement_after_labels (parser, வெற்று, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = பொய்;
      astate.reset ();
    }
  எனில் (last_label)
    pedwarn_c11 (label_loc, OPT_Wfree_labels,
		 "label at end of compound statement");
  location_t endloc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  /* Restore the value we started with.  */
  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);

  /* Package leftover intervening code, or the whole contents of the
     compound statement if we were looking for a nested loop in an OMP_FOR
     construct and didn't find one.  */
  எனில் (sl)
    {
      sl = எடு_stmt_list (sl);
      எனில் (omp_for_parse_state->want_nested_loop)
	add_stmt (sl);
      இல்லையெனில்
	add_structured_block_stmt (sl);
    }
  திரும்பு endloc;
}

/* Parse all consecutive labels, possibly preceded by standard
   attributes.  In this context, a statement is required, not a
   declaration, so attributes must be followed by a statement that is
   not just a semicolon.  Returns an attr_state.  */

நிலையான attr_state
c_parser_all_labels (c_parser *parser)
{
  attr_state attr = {};
  தருக்க have_std_attrs;
  மரம் std_attrs = வெற்று;
  எனில் ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  போது (c_parser_next_token_is_keyword (parser, RID_CASE)
	 || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = வெற்று;
      எனில் ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  எனில் (std_attrs
      && (!c_parser_handle_statement_omp_attributes (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      எனில் (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_unused_attributes (std_attrs);
    }
  இல்லையெனில் எனில் (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  திரும்பு attr;
}


/* Information used while parsing an OpenMP metadirective.  */
கட்டமைப்பு omp_metadirective_parse_data {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<மரம்> * GTY((skip)) body_labels;
  unsigned முழு region_இலக்கம்;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
நிலையான மரம்
mangle_metadirective_region_label (c_parser *parser, மரம் name)
{
  எனில் (parser->omp_metadirective_state->body_labels->contains (name))
    {
      மாறிலி எழுத்து *old_name = IDENTIFIER_POINTER (name);
      எழுத்து *new_name = (எழுத்து *) XALLOCAVEC (எழுத்து, strlen (old_name) + 32);
      sprintf (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_இலக்கம்);
      திரும்பு get_identifier (new_name);
    }
  திரும்பு name;
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
நிலையான வெறுமை
c_parser_label (c_parser *parser, மரம் std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  மரம் label = NULL_மரம்;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  தருக்க fallthrough_p = c_parser_peek_token (parser)->flags & PREV_FALLTHROUGH;

  எனில் (c_parser_next_token_is_keyword (parser, RID_CASE))
    {
      மரம் exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_to_rvalue (loc1,
				       c_parser_கோவை_no_commas (parser, வெற்று),
				       உண்மை, உண்மை).மதிப்பு;
      எனில் (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_மரம், std_attrs);
	}
      இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_to_rvalue (loc1,
					   c_parser_கோவை_no_commas (parser,
								    வெற்று),
					   உண்மை, உண்மை).மதிப்பு;
	  எனில் (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      இல்லையெனில்
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      எனில் (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_மரம், NULL_மரம், std_attrs);
    }
  இல்லையெனில்
    {
      மரம் name = c_parser_peek_token (parser)->மதிப்பு;
      மரம் tlab;
      மரம் attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_attributes (parser);
      எனில் (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      எனில் (tlab)
	{
	  decl_attributes (&tlab, attrs, 0);
	  decl_attributes (&tlab, std_attrs, 0);
	  label = add_stmt (build_stmt (loc1, LABEL_கோவை, tlab));
	}
      எனில் (attrs
	  && c_parser_next_tokens_start_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  எனில் (label)
    {
      எனில் (மரம்_CODE (label) == LABEL_கோவை)
	FALLTHROUGH_LABEL_P (LABEL_கோவை_LABEL (label)) = fallthrough_p;
      இல்லையெனில்
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

நிலையான வெறுமை
c_parser_statement (c_parser *parser, தருக்க *if_p, location_t *loc_after_labels)
{
  மரம் before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  எனில் (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = பொய்;
  c_parser_statement_after_labels (parser, if_p, before_labels, வெற்று, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

நிலையான மரம்
c_parser_bc_name (c_parser *parser, தருக்க is_break)
{
  எனில் (!c_parser_next_token_is (parser, CPP_NAME))
    திரும்பு NULL_மரம்;

  c_token *tok = c_parser_peek_token (parser);
  மரம் label = c_finish_bc_name (tok->location, tok->மதிப்பு, is_break);
  c_parser_consume_token (parser);
  திரும்பு label;
}

/* Parse a statement, other than a labeled statement.  CHAIN is a vector
   of if-else-if conditions.  All labels and standard attributes have
   been parsed in the caller.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  ASTATE is an earlier parsed attribute state.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

நிலையான வெறுமை
c_parser_statement_after_labels (c_parser *parser, தருக்க *if_p,
				 மரம் before_labels,
				 vec<மரம்> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  மரம் stmt = NULL_மரம்;
  தருக்க in_if_block = parser->in_if_block;
  parser->in_if_block = பொய்;
  எனில் (if_p != வெற்று)
    *if_p = பொய்;

  எனில் (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    add_debug_begin_stmt (loc);

 restart:
  தேர்வு (c_parser_peek_token (parser)->type)
    {
    நிலை CPP_OPEN_BRACE:
      add_stmt (c_parser_compound_statement (parser));
      நிறுத்து;
    நிலை CPP_KEYWORD:
      தேர்வு (c_parser_peek_token (parser)->keyword)
	{
	நிலை RID_IF:
	  c_parser_if_statement (parser, if_p, chain);
	  நிறுத்து;
	நிலை RID_SWITCH:
	  c_parser_switch_statement (parser, if_p, before_labels);
	  நிறுத்து;
	நிலை RID_WHILE:
	  c_parser_while_statement (parser, பொய், 0, பொய், if_p, before_labels);
	  நிறுத்து;
	நிலை RID_DO:
	  c_parser_do_statement (parser, பொய், 0, பொய், before_labels);
	  நிறுத்து;
	நிலை RID_FOR:
	  c_parser_for_statement (parser, பொய், 0, பொய், if_p, before_labels);
	  நிறுத்து;
	நிலை RID_GOTO:
	  c_parser_consume_token (parser);
	  எனில் (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      மரம் name = c_parser_peek_token (parser)->மதிப்பு;
	      எனில் (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_finish_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_MULT))
	    {
	      கட்டமைப்பு c_கோவை val;

	      c_parser_consume_token (parser);
	      val = c_parser_expression (parser);
	      val = convert_lvalue_to_rvalue (loc, val, பொய், உண்மை);
	      stmt = c_finish_goto_ptr (loc, val);
	    }
	  இல்லையெனில்
	    c_parser_error (parser, "expected identifier or %<*%>");
	  செல் expect_semicolon;
	நிலை RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_continue_label, பொய்,
				   c_parser_bc_name (parser, பொய்));
	  செல் expect_semicolon;
	நிலை RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_break_label, உண்மை,
				   c_parser_bc_name (parser, உண்மை));
	  செல் expect_semicolon;
	நிலை RID_RETURN:
	  c_parser_consume_token (parser);
	  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_finish_return (loc, NULL_மரம், NULL_மரம்,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  இல்லையெனில்
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      கட்டமைப்பு c_கோவை கோவை = c_parser_expression_conv (parser);
	      mark_exp_read (கோவை.மதிப்பு);
	      stmt = c_finish_return (கோவை_LOC_OR_LOC (கோவை.மதிப்பு, xloc),
				      கோவை.மதிப்பு, கோவை.original_type,
				      astate.musttail_p);
	      செல் expect_semicolon;
	    }
	  நிறுத்து;
	நிலை RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  நிறுத்து;
	நிலை RID_TRANSACTION_ATOMIC:
	நிலை RID_TRANSACTION_RELAXED:
	  stmt = c_parser_transaction (parser,
	      c_parser_peek_token (parser)->keyword);
	  நிறுத்து;
	நிலை RID_TRANSACTION_CANCEL:
	  stmt = c_parser_transaction_cancel (parser);
	  செல் expect_semicolon;
	நிலை RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_மரம்);
	      c_parser_consume_token (parser);
	    }
	  இல்லையெனில்
	    {
	      கட்டமைப்பு c_கோவை கோவை = c_parser_expression (parser);
	      கோவை = convert_lvalue_to_rvalue (loc, கோவை, பொய், பொய்);
	      கோவை.மதிப்பு = c_fully_fold (கோவை.மதிப்பு, பொய், வெற்று);
	      stmt = objc_build_throw_stmt (loc, கோவை.மதிப்பு);
	      செல் expect_semicolon;
	    }
	  நிறுத்து;
	நிலை RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_finally_statement (parser);
	  நிறுத்து;
	நிலை RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  நிறுத்து;
	நிலை RID_ATTRIBUTE:
	  {
	    /* Allow '__attribute__((fallthrough));' or
	       '__attribute__((assume(cond)));' or
	       '__attribute__((musttail))) return'.  */
	    மரம் attrs = c_parser_gnu_attributes (parser);
	    தருக்க has_assume = lookup_attribute ("assume", attrs);
	    எனில் (has_assume)
	      {
		எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, உண்மை);
		இல்லையெனில்
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<assume%> attribute not followed by %<;%>");
		    has_assume = பொய்;
		  }
	      }
	    gcc_assert (!astate.musttail_p);
	    attrs = c_parser_handle_musttail (parser, attrs, astate);
	    எனில் (astate.musttail_p)
	      {
		எனில் (attrs)
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		செல் restart;
	      }
	    எனில் (attribute_fallthrough_p (attrs))
	      {
		எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  {
		    மரம் fn = build_call_கோவை_internal_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_முனை, 0);
		    add_stmt (fn);
		    /* Eat the ';'.  */
		    c_parser_consume_token (parser);
		  }
		இல்லையெனில்
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<fallthrough%> attribute not followed "
				"by %<;%>");
		  }
	      }
	    இல்லையெனில் எனில் (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    இல்லையெனில் எனில் (attrs != NULL_மரம்)
	      {
		auto_urlify_attributes sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    நிறுத்து;
	  }
	இயல்பு:
	  செல் கோவை_stmt;
	}
      நிறுத்து;
    நிலை CPP_SEMICOLON:
      c_parser_consume_token (parser);
      நிறுத்து;
    நிலை CPP_CLOSE_PAREN:
    நிலை CPP_CLOSE_SQUARE:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      நிறுத்து;
    நிலை CPP_PRAGMA:
      எனில் (!c_parser_pragma (parser, pragma_stmt, if_p, before_labels))
        செல் restart;
      நிறுத்து;
    இயல்பு:
    கோவை_stmt:
      stmt = c_finish_கோவை_stmt (loc, c_parser_expression_conv (parser).மதிப்பு);
    expect_semicolon:
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      நிறுத்து;
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
  எனில் (கோவை_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_set_கோவை_location (stmt, loc);

  parser->in_if_block = in_if_block;
}

/* Parse the condition from an if, do, while or for statements.  */

நிலையான மரம்
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  மரம் cond;
  cond = c_parser_expression_conv (parser).மதிப்பு;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, பொய், வெற்று);
  எனில் (warn_sequence_point)
    verify_sequence_points (cond);
  திரும்பு cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

நிலையான மரம்
c_parser_paren_condition (c_parser *parser)
{
  மரம் cond;
  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு error_mark_முனை;
  cond = c_parser_condition (parser);
  parens.skip_until_found_close (parser);
  திரும்பு cond;
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

நிலையான c_கோவை
c_parser_selection_header (c_parser *parser, தருக்க switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_கோவை கோவை;
  தருக்க parse_கோவை = உண்மை;
  மரம் std_attrs;
  தருக்க have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  எனில் (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  இல்லையெனில்
    std_attrs = NULL_மரம்;
  எனில் (c_parser_next_tokens_start_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      கோவை.மதிப்பு
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/பொய்,
					 /*static_assert_ok=*/பொய்,
					 /*empty_ok=*/பொய்,
					 /*nested=*/உண்மை,
					 /*start_attr_ok=*/உண்மை,
					 /*simple_ok=*/உண்மை,
					 /*objc_foreach_object_decl=*/nullptr,
					 /*omp_declare_simd_clauses=*/nullptr,
					 have_std_attrs,
					 std_attrs);
      எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      இல்லையெனில்
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  எனில் (!கோவை.மதிப்பு)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      கோவை.original_type = error_mark_முனை;
	      கோவை.set_error ();
	      திரும்பு கோவை;
	    }
	  parse_கோவை = பொய்;
	}
      எனில் (கோவை.மதிப்பு)
	{
	  கோவை.original_type = மரம்_TYPE (கோவை.மதிப்பு);
	  கோவை = convert_lvalue_to_rvalue (loc, கோவை, /*convert_p=*/உண்மை,
					   /*read_p=*/உண்மை);
	}
    }
  இல்லையெனில் எனில் (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      கோவை.original_type = error_mark_முனை;
      கோவை.set_error ();
      திரும்பு கோவை;
    }

  எனில் (parse_கோவை)
    கோவை = c_parser_expression_conv (parser);
  எனில் (!switch_p)
    {
      கோவை.மதிப்பு = c_objc_common_truthvalue_conversion (loc, கோவை.மதிப்பு);
      கோவை.மதிப்பு = c_fully_fold (கோவை.மதிப்பு, பொய், வெற்று);
      எனில் (warn_sequence_point)
	verify_sequence_points (கோவை.மதிப்பு);
    }
  திரும்பு கோவை;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

நிலையான மரம்
c_parser_paren_selection_header (c_parser *parser)
{
  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு error_mark_முனை;
  மரம் cond = c_parser_selection_header (parser, /*switch_p=*/பொய்).மதிப்பு;
  parens.skip_until_found_close (parser);
  திரும்பு cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

நிலையான மரம்
c_parser_c99_block_statement (c_parser *parser, தருக்க *if_p,
			      location_t *loc_after_labels)
{
  மரம் block = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  திரும்பு c_end_compound_stmt (loc, block, flag_isoc99);
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

நிலையான மரம்
c_parser_if_body (c_parser *parser, தருக்க *if_p,
		  மாறிலி token_indent_info &if_tinfo)
{
  மரம் block = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  மரம் before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
      எனில் (!c_parser_next_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    add_stmt (c_parser_compound_statement (parser));
  இல்லையெனில்
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, வெற்று, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, next_tinfo);
  எனில் (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    if_tinfo.location, RID_IF);

  திரும்பு c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

நிலையான மரம்
c_parser_else_body (c_parser *parser, மாறிலி token_indent_info &else_tinfo,
		    vec<மரம்> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  மரம் block = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  மரம் before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      warning_at (loc,
		  OPT_Wempty_body,
	         "suggest braces around empty body in an %<else%> statement");
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
    }
  இல்லையெனில்
    {
      எனில் (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, வெற்று, before_labels, chain, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, next_tinfo);
  எனில் (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  திரும்பு c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse an if statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   if-statement:
     if ( selection-header ) statement
     if ( selection-header ) statement else statement

   CHAIN is a vector of if-else-if conditions.
   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

நிலையான வெறுமை
c_parser_if_statement (c_parser *parser, தருக்க *if_p, vec<மரம்> *chain)
{
  மரம் block;
  location_t loc;
  மரம் cond;
  தருக்க nested_if = பொய்;
  மரம் first_body, second_body;
  தருக்க in_if_block;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_IF));
  token_indent_info if_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_selection_header (parser);
  in_if_block = parser->in_if_block;
  parser->in_if_block = உண்மை;
  first_body = c_parser_if_body (parser, &nested_if, if_tinfo);
  parser->in_if_block = in_if_block;

  எனில் (warn_duplicated_cond)
    warn_duplicated_cond_add_or_warn (கோவை_LOCATION (cond), cond, &chain);

  எனில் (c_parser_next_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      எனில் (warn_duplicated_cond)
	{
	  எனில் (c_parser_next_token_is_keyword (parser, RID_IF)
	      && chain == வெற்று)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = புதிய vec<மரம்> ();
	      எனில் (!CONSTANT_CLASS_P (cond) && !மரம்_SIDE_EFFECTS (cond))
		chain->safe_தள்ளு (cond);
	    }
	  இல்லையெனில் எனில் (!c_parser_next_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      second_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      எனில் (if_p != வெற்று)
	*if_p = உண்மை;
    }
  இல்லையெனில்
    {
      second_body = NULL_மரம்;

      /* Diagnose an ambiguous else if if-then-else is nested inside
	 if-then.  */
      எனில் (nested_if)
	warning_at (loc, OPT_Wdangling_else,
		    "suggest explicit braces to avoid ambiguous %<else%>");

      எனில் (warn_duplicated_cond)
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

நிலையான வெறுமை
c_parser_switch_statement (c_parser *parser, தருக்க *if_p, மரம் before_labels)
{
  கட்டமைப்பு c_கோவை ce;
  மரம் block, கோவை, body;
  unsigned எழுத்து save_in_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  மரம் switch_name;
  முழு இலக்கம்_names = c_get_loop_names (before_labels, உண்மை, &switch_name);
  block = c_begin_compound_stmt (flag_isoc99);
  தருக்க explicit_cast_p = பொய்;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = உண்மை;
      ce = c_parser_selection_header (parser, /*switch_p=*/உண்மை);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_to_rvalue (switch_cond_loc, ce, உண்மை, உண்மை);
      கோவை = ce.மதிப்பு;
      /* ??? expr has no valid location?  */
      parens.skip_until_found_close (parser);
    }
  இல்லையெனில்
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      கோவை = error_mark_முனை;
      ce.original_type = error_mark_முனை;
    }
  மரம் stmt
    = c_start_switch (switch_loc, switch_cond_loc, கோவை, explicit_cast_p,
		      switch_name);
  save_in_statement = in_statement;
  in_statement |= IN_SWITCH_STMT;
  எனில் (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  இல்லையெனில்
    in_statement &= ~IN_NAMED_STMT;
  location_t loc_after_labels;
  தருக்க open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  location_t next_loc = c_parser_peek_token (parser)->location;
  எனில் (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, next_loc, switch_loc,
				    RID_SWITCH);
  c_finish_switch (body, ce.original_type);
  in_statement = save_in_statement;
  எனில் (இலக்கம்_names)
    {
      எனில் (!C_DECL_LOOP_SWITCH_NAME_USED (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_மரம்;
      இல்லையெனில்
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_names (இலக்கம்_names);
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

நிலையான வெறுமை
c_parser_while_statement (c_parser *parser, தருக்க ivdep, unsigned short unroll,
			  தருக்க novector, தருக்க *if_p, மரம் before_labels)
{
  மரம் block, cond, body;
  unsigned எழுத்து save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  மரம் loop_name;
  முழு இலக்கம்_names = c_get_loop_names (before_labels, பொய், &loop_name);

  எனில் (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = உண்மை;
    }

  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  எனில் (ivdep && cond != error_mark_முனை)
    cond = build3 (ANNOTATE_கோவை, மரம்_TYPE (cond), cond,
		   build_int_cst (integer_type_முனை,
				  annot_கோவை_ivdep_kind),
		   integer_zero_முனை);
  எனில் (unroll && cond != error_mark_முனை)
    cond = build3 (ANNOTATE_கோவை, மரம்_TYPE (cond), cond,
		   build_int_cst (integer_type_முனை,
				  annot_கோவை_unroll_kind),
		   build_int_cst (integer_type_முனை, unroll));
  எனில் (novector && cond != error_mark_முனை)
    cond = build3 (ANNOTATE_கோவை, மரம்_TYPE (cond), cond,
		   build_int_cst (integer_type_முனை,
				  annot_கோவை_no_vector_kind),
		   integer_zero_முனை);
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  எனில் (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  தருக்க open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  எனில் (loop_name && !C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
    loop_name = NULL_மரம்;
  add_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_மரம்,
			NULL_மரம்));
  add_stmt (c_end_compound_stmt (loc, block, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  எனில் (இலக்கம்_names)
    c_release_loop_names (இலக்கம்_names);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, next_tinfo);

  எனில் (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    while_tinfo.location, RID_WHILE);

  in_statement = save_in_statement;
}

/* Parse a do statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   do-statement:
     do statement while ( expression ) ;

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

நிலையான வெறுமை
c_parser_do_statement (c_parser *parser, தருக்க ivdep, unsigned short unroll,
		       தருக்க novector, மரம் before_labels)
{
  மரம் block, cond, body;
  unsigned எழுத்து save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_DO));
  மரம் loop_name;
  முழு இலக்கம்_names = c_get_loop_names (before_labels, பொய், &loop_name);

  எனில் (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = உண்மை;
    }

  c_parser_consume_token (parser);
  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  எனில் (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  body = c_parser_c99_block_statement (parser, வெற்று);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  in_statement = save_in_statement;
  எனில் (இலக்கம்_names)
    {
      எனில் (!C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
	loop_name = NULL_மரம்;
      c_release_loop_names (இலக்கம்_names);
    }
  cond = c_parser_paren_condition (parser);
  எனில் (ivdep && cond != error_mark_முனை)
    cond = build3 (ANNOTATE_கோவை, மரம்_TYPE (cond), cond,
		   build_int_cst (integer_type_முனை,
				  annot_கோவை_ivdep_kind),
		   integer_zero_முனை);
  எனில் (unroll && cond != error_mark_முனை)
    cond = build3 (ANNOTATE_கோவை, மரம்_TYPE (cond), cond,
		   build_int_cst (integer_type_முனை,
				  annot_கோவை_unroll_kind),
 		   build_int_cst (integer_type_முனை, unroll));
  எனில் (novector && cond != error_mark_முனை)
    cond = build3 (ANNOTATE_கோவை, மரம்_TYPE (cond), cond,
		   build_int_cst (integer_type_முனை,
				  annot_கோவை_no_vector_kind),
		   integer_zero_முனை);
  எனில் (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
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

நிலையான வெறுமை
c_parser_for_statement (c_parser *parser, தருக்க ivdep, unsigned short unroll,
			தருக்க novector, தருக்க *if_p, மரம் before_labels)
{
  மரம் block, cond, incr, body;
  unsigned எழுத்து save_in_statement;
  மரம் save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  மரம் object_expression;
  /* Silence the bogus uninitialized warning.  */
  மரம் collection_expression = வெற்று;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  தருக்க is_foreach_statement = பொய்;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  மரம் loop_name;
  முழு இலக்கம்_names = c_get_loop_names (before_labels, பொய், &loop_name);

  எனில் (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = உண்மை;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  block = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_முனை;
  incr = error_mark_முனை;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_expression = error_mark_முனை;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = பொய்;
	  c_parser_consume_token (parser);
	  c_finish_கோவை_stmt (loc, NULL_மரம்);
	}
      இல்லையெனில் எனில் (c_parser_next_tokens_start_declaration (parser)
	       || c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, உண்மை, உண்மை, உண்மை, உண்மை, உண்மை,
					 பொய், &object_expression);
	  parser->objc_could_be_foreach_context = பொய்;

	  எனில் (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = உண்மை;
	      எனில் (check_for_loop_decls (for_loc, உண்மை) == NULL_மரம்)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  இல்லையெனில்
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  போது (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  எனில் (c_parser_next_tokens_start_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_attributes (parser, 2))
	    {
	      முழு ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, உண்மை, உண்மை, உண்மை, உண்மை,
					     உண்மை, பொய், &object_expression);
	      parser->objc_could_be_foreach_context = பொய்;

	      restore_extension_diagnostics (ext);
	      எனில் (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = உண்மை;
		  எனில் (check_for_loop_decls (for_loc, உண்மை) == NULL_மரம்)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      இல்லையெனில்
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  இல்லையெனில்
	    செல் init_கோவை;
	}
      இல்லையெனில்
	{
	init_கோவை:
	  {
	    கட்டமைப்பு c_கோவை ce;
	    மரம் init_expression;
	    ce = c_parser_expression (parser);
	    init_expression = ce.மதிப்பு;
	    parser->objc_could_be_foreach_context = பொய்;
	    எனில் (c_parser_next_token_is_keyword (parser, RID_IN))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = உண்மை;
		எனில் (! lvalue_p (init_expression))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_expression
		  = c_fully_fold (init_expression, பொய், வெற்று);
	      }
	    இல்லையெனில்
	      {
		ce = convert_lvalue_to_rvalue (loc, ce, உண்மை, பொய்);
		init_expression = ce.மதிப்பு;
		c_finish_கோவை_stmt (loc, init_expression);
		c_parser_skip_until_found (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      எனில் (!is_foreach_statement)
	{
	  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      எனில் (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_முனை;
		}
	      இல்லையெனில் எனில் (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_முனை;
		}
	      இல்லையெனில்
		{
		  c_parser_consume_token (parser);
		  cond = NULL_மரம்;
		}
	    }
	  இல்லையெனில்
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_found (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  எனில் (ivdep && cond != error_mark_முனை)
	    cond = build3 (ANNOTATE_கோவை, மரம்_TYPE (cond), cond,
			   build_int_cst (integer_type_முனை,
					  annot_கோவை_ivdep_kind),
			   integer_zero_முனை);
	  எனில் (unroll && cond != error_mark_முனை)
	    cond = build3 (ANNOTATE_கோவை, மரம்_TYPE (cond), cond,
 			   build_int_cst (integer_type_முனை,
					  annot_கோவை_unroll_kind),
			   build_int_cst (integer_type_முனை, unroll));
	  எனில் (novector && cond && cond != error_mark_முனை)
	    cond = build3 (ANNOTATE_கோவை, மரம்_TYPE (cond), cond,
			   build_int_cst (integer_type_முனை,
					  annot_கோவை_no_vector_kind),
			   integer_zero_முனை);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  எனில் (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_expression = error_mark_முனை;
	    }
	  இல்லையெனில்
	    incr = c_process_கோவை_stmt (loc, NULL_மரம்);
	}
      இல்லையெனில்
	{
	  எனில் (is_foreach_statement)
	    collection_expression
	      = c_fully_fold (c_parser_expression (parser).மதிப்பு, பொய், வெற்று);
	  இல்லையெனில்
	    {
	      கட்டமைப்பு c_கோவை ce = c_parser_expression (parser);
	      ce = convert_lvalue_to_rvalue (loc, ce, உண்மை, பொய்);
	      incr = c_process_கோவை_stmt (loc, ce.மதிப்பு);
	    }
	}
      parens.skip_until_found_close (parser);
    }
  save_in_statement = in_statement;
  எனில் (is_foreach_statement)
    {
      in_statement = IN_OBJC_FOREACH;
      save_objc_foreach_break_label = objc_foreach_break_label;
      save_objc_foreach_continue_label = objc_foreach_continue_label;
      objc_foreach_break_label = create_artificial_label (loc);
      objc_foreach_continue_label = create_artificial_label (loc);
      எனில் (loop_name)
	{
	  gcc_checking_assert (!DECL_CHAIN (loop_name)
			       && !DECL_CHAIN (objc_foreach_break_label));
	  C_DECL_SWITCH_NAME (loop_name) = 1;
	  DECL_CHAIN (loop_name) = objc_foreach_break_label;
	  DECL_CHAIN (objc_foreach_break_label) = objc_foreach_continue_label;
	}
    }
  இல்லையெனில்
    in_statement = IN_ITERATION_STMT;
  எனில் (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  தருக்க open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);

  எனில் (loop_name && is_foreach_statement)
    {
      gcc_checking_assert (DECL_CHAIN (loop_name) == objc_foreach_break_label
			   && (DECL_CHAIN (objc_foreach_break_label)
			       == objc_foreach_continue_label));
      C_DECL_SWITCH_NAME (loop_name) = 0;
      DECL_CHAIN (loop_name) = NULL_மரம்;
      DECL_CHAIN (objc_foreach_break_label) = NULL_மரம்;
    }

  எனில் (is_foreach_statement)
    objc_finish_foreach_loop (for_loc, object_expression,
			      collection_expression, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  இல்லையெனில்
    add_stmt (build_stmt (for_loc, FOR_STMT, NULL_மரம், cond, incr,
			  body, NULL_மரம்,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_USED (loop_name)
			  ? loop_name : NULL_மரம், NULL_மரம், NULL_மரம்));
  add_stmt (c_end_compound_stmt (for_loc, block,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, next_tinfo);

  எனில் (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    for_tinfo.location, RID_FOR);

  in_statement = save_in_statement;
  எனில் (இலக்கம்_names)
    c_release_loop_names (இலக்கம்_names);
  எனில் (is_foreach_statement)
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

நிலையான மரம்
c_parser_asm_statement (c_parser *parser)
{
  மரம் str, outputs, inputs, clobbers, labels, ret;
  தருக்க simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  முழு section, nsections;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);

  /* Handle the asm-qualifier-list.  */
  location_t volatile_loc = UNKNOWN_LOCATION;
  location_t inline_loc = UNKNOWN_LOCATION;
  location_t goto_loc = UNKNOWN_LOCATION;
  க்கு (;;)
    {
      c_token *token = c_parser_peek_token (parser);
      location_t loc = token->location;
      தேர்வு (token->keyword)
	{
	நிலை RID_VOLATILE:
	  எனில் (volatile_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->மதிப்பு);
	      inform (volatile_loc, "first seen here");
	    }
	  இல்லையெனில்
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  தொடர்;

	நிலை RID_INLINE:
	  எனில் (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->மதிப்பு);
	      inform (inline_loc, "first seen here");
	    }
	  இல்லையெனில்
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  தொடர்;

	நிலை RID_GOTO:
	  எனில் (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->மதிப்பு);
	      inform (goto_loc, "first seen here");
	    }
	  இல்லையெனில்
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  தொடர்;

	நிலை RID_CONST:
	நிலை RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->மதிப்பு);
	  c_parser_consume_token (parser);
	  தொடர்;

	இயல்பு:
	  நிறுத்து;
	}
      நிறுத்து;
    }

  தருக்க is_volatile = (volatile_loc != UNKNOWN_LOCATION);
  தருக்க is_inline = (inline_loc != UNKNOWN_LOCATION);
  தருக்க is_goto = (goto_loc != UNKNOWN_LOCATION);

  ret = வெற்று;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    செல் error;

  str = c_parser_asm_string_literal (parser);
  எனில் (str == NULL_மரம்)
    செல் error_close_paren;

  simple = உண்மை;
  outputs = NULL_மரம்;
  inputs = NULL_மரம்;
  clobbers = NULL_மரம்;
  labels = NULL_மரம்;

  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    செல் done_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  க்கு (section = 0; section < nsections; ++section)
    {
      எனில் (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  எனில் (section == nsections)
	    {
	      c_parser_error (parser, "expected %<)%>");
	      செல் error_close_paren;
	    }
	  c_parser_consume_token (parser);
	}
      இல்லையெனில் எனில் (!c_parser_require (parser, CPP_COLON,
				  is_goto
				  ? G_("expected %<:%>")
				  : G_("expected %<:%> or %<)%>"),
				  UNKNOWN_LOCATION, is_goto))
	செல் error_close_paren;

      /* Once past any colon, we're no longer a simple asm.  */
      simple = பொய்;

      எனில் ((!c_parser_next_token_is (parser, CPP_COLON)
	   && !c_parser_next_token_is (parser, CPP_SCOPE)
	   && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	  || section == 3)
	தேர்வு (section)
	  {
	  நிலை 0:
	    outputs = c_parser_asm_operands (parser);
	    நிறுத்து;
	  நிலை 1:
	    inputs = c_parser_asm_operands (parser);
	    நிறுத்து;
	  நிலை 2:
	    clobbers = c_parser_asm_clobbers (parser);
	    நிறுத்து;
	  நிலை 3:
	    labels = c_parser_asm_goto_operands (parser);
	    நிறுத்து;
	  இயல்பு:
	    gcc_unreachable ();
	  }

      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	செல் done_asm;
    }

 done_asm:
  எனில் (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
      செல் error;
    }

  எனில் (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_to_end_of_block_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_கோவை (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  திரும்பு ret;

 error_close_paren:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
  செல் error;
}

/* Parse asm operands, a GNU extension.

   asm-operands:
     asm-operand
     asm-operands , asm-operand

   asm-operand:
     asm-string-literal ( expression )
     [ identifier ] asm-string-literal ( expression )
*/

நிலையான மரம்
c_parser_asm_operands (c_parser *parser)
{
  மரம் list = NULL_மரம்;
  போது (உண்மை)
    {
      மரம் name, str;
      கட்டமைப்பு c_கோவை கோவை;
      எனில் (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
	{
	  c_parser_consume_token (parser);
	  எனில் (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      மரம் id = c_parser_peek_token (parser)->மதிப்பு;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_LENGTH (id),
				   IDENTIFIER_POINTER (id));
	    }
	  இல்லையெனில்
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, வெற்று);
	      திரும்பு NULL_மரம்;
	    }
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	}
      இல்லையெனில்
	name = NULL_மரம்;
      str = c_parser_asm_string_literal (parser);
      எனில் (str == NULL_மரம்)
	திரும்பு NULL_மரம்;
      matching_parens parens;
      எனில் (!parens.require_open (parser))
	திரும்பு NULL_மரம்;
      கோவை = c_parser_expression (parser);
      mark_exp_read (கோவை.மதிப்பு);
      எனில் (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
	  திரும்பு NULL_மரம்;
	}
      list = chainon (list, build_மரம்_list (build_மரம்_list (name, str),
					     கோவை.மதிப்பு));
      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      இல்லையெனில்
	நிறுத்து;
    }
  திரும்பு list;
}

/* Parse asm clobbers, a GNU extension.

   asm-clobbers:
     asm-string-literal
     asm-clobbers , asm-string-literal
*/

நிலையான மரம்
c_parser_asm_clobbers (c_parser *parser)
{
  மரம் list = NULL_மரம்;
  போது (உண்மை)
    {
      மரம் str = c_parser_asm_string_literal (parser);
      எனில் (str)
	list = மரம்_cons (NULL_மரம், str, list);
      இல்லையெனில்
	திரும்பு NULL_மரம்;
      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      இல்லையெனில்
	நிறுத்து;
    }
  திரும்பு list;
}

/* Parse asm goto labels, a GNU extension.

   asm-goto-operands:
     identifier
     asm-goto-operands , identifier
*/

நிலையான மரம்
c_parser_asm_goto_operands (c_parser *parser)
{
  மரம் list = NULL_மரம்;
  போது (உண்மை)
    {
      மரம் name, label;

      எனில் (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->மதிப்பு;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  மரம்_USED (label) = 1;
	}
      இல்லையெனில்
	{
	  c_parser_error (parser, "expected identifier");
	  திரும்பு NULL_மரம்;
	}

      name = build_string (IDENTIFIER_LENGTH (name),
			   IDENTIFIER_POINTER (name));
      list = மரம்_cons (name, label, list);
      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      இல்லையெனில்
	திரும்பு nreverse (list);
    }
}

/* Parse a possibly concatenated sequence of string literals.
   TRANSLATE says whether to translate them to the execution character
   set; WIDE_OK says whether any kind of prefixed string literal is
   permitted in this context.  This code is based on that in
   lex_string.  */

கட்டமைப்பு c_கோவை
c_parser_string_literal (c_parser *parser, தருக்க translate, தருக்க wide_ok)
{
  கட்டமைப்பு c_கோவை ret;
  size_t மொத்தம்;
  கட்டமைப்பு obstack str_ob;
  கட்டமைப்பு obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, last_tok_loc;
  எண்ணிக்கை cpp_ttype type;
  மரம் மதிப்பு, string_மரம்;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  last_tok_loc = linemap_resolve_location (வரி_table, loc,
					   LRK_MACRO_DEFINITION_LOCATION,
					   வெற்று);
  type = tok->type;
  தேர்வு (type)
    {
    நிலை CPP_STRING:
    நிலை CPP_WSTRING:
    நிலை CPP_STRING16:
    நிலை CPP_STRING32:
    நிலை CPP_UTF8STRING:
      string_மரம் = tok->மதிப்பு;
      நிறுத்து;

    இயல்பு:
      c_parser_error (parser, "expected string literal");
      ret.set_error ();
      ret.மதிப்பு = NULL_மரம்;
      ret.original_code = ERROR_MARK;
      ret.original_type = NULL_மரம்;
      திரும்பு ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  தேர்வு (c_parser_peek_2nd_token (parser)->type)
    {
    இயல்பு:
      c_parser_consume_token (parser);
      str.text = (மாறிலி unsigned எழுத்து *) மரம்_STRING_POINTER (string_மரம்);
      str.len = மரம்_STRING_LENGTH (string_மரம்);
      மொத்தம் = 1;
      strs = &str;
      நிறுத்து;

    நிலை CPP_STRING:
    நிலை CPP_WSTRING:
    நிலை CPP_STRING16:
    நிலை CPP_STRING32:
    நிலை CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      மொத்தம் = 0;
      செய்
	{
	  c_parser_consume_token (parser);
	  மொத்தம்++;
	  str.text = (மாறிலி unsigned எழுத்து *) மரம்_STRING_POINTER (string_மரம்);
	  str.len = மரம்_STRING_LENGTH (string_மரம்);
	  எனில் (type != tok->type)
	    {
	      எனில் (type == CPP_STRING)
		type = tok->type;
	      இல்லையெனில் எனில் (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, அளவு (cpp_string));
	  obstack_grow (&loc_ob, &last_tok_loc, அளவு (location_t));
	  tok = c_parser_peek_token (parser);
	  string_மரம் = tok->மதிப்பு;
	  last_tok_loc
	    = linemap_resolve_location (வரி_table, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, வெற்று);
	}
      போது (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_finish (&str_ob);
    }

  எனில் (மொத்தம் > 1 && !in_system_header_at (உள்ளீடு_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  எனில் ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_in, strs, மொத்தம், &istr, type)))
    {
      மதிப்பு = build_string (istr.len, (மாறிலி எழுத்து *) istr.text);
      விடுவி (const_cast<unsigned எழுத்து *> (istr.text));
      எனில் (மொத்தம் > 1)
	{
	  location_t *locs = (location_t *) obstack_finish (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->record_string_concatenation (மொத்தம், locs);
	}
    }
  இல்லையெனில்
    {
      எனில் (type != CPP_STRING && !wide_ok)
	{
	  error_at (loc, "a wide string is invalid in this context");
	  type = CPP_STRING;
	}
      /* Callers cannot generally handle error_mark_node in this
	 context, so return the empty string instead.  An error has
	 been issued, either above or from cpp_interpret_string.  */
      தேர்வு (type)
	{
	இயல்பு:
	நிலை CPP_STRING:
	நிலை CPP_UTF8STRING:
	  எனில் (type == CPP_UTF8STRING && flag_char8_t)
	    {
	      மதிப்பு = build_string (TYPE_PRECISION (char8_type_முனை)
				    / TYPE_PRECISION (char_type_முனை),
				    "");  /* char8_t is 8 bits */
	    }
	  இல்லையெனில்
	    மதிப்பு = build_string (1, "");
	  நிறுத்து;
	நிலை CPP_STRING16:
	  மதிப்பு = build_string (TYPE_PRECISION (char16_type_முனை)
				/ TYPE_PRECISION (char_type_முனை),
				"\0");  /* char16_t is 16 bits */
	  நிறுத்து;
	நிலை CPP_STRING32:
	  மதிப்பு = build_string (TYPE_PRECISION (char32_type_முனை)
				/ TYPE_PRECISION (char_type_முனை),
				"\0\0\0");  /* char32_t is 32 bits */
	  நிறுத்து;
	நிலை CPP_WSTRING:
	  மதிப்பு = build_string (TYPE_PRECISION (wchar_type_முனை)
				/ TYPE_PRECISION (char_type_முனை),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  நிறுத்து;
        }
    }

  தேர்வு (type)
    {
    இயல்பு:
    நிலை CPP_STRING:
      மரம்_TYPE (மதிப்பு) = char_array_type_முனை;
      நிறுத்து;
    நிலை CPP_UTF8STRING:
      எனில் (flag_char8_t)
	மரம்_TYPE (மதிப்பு) = char8_array_type_முனை;
      இல்லையெனில்
	மரம்_TYPE (மதிப்பு) = char_array_type_முனை;
      நிறுத்து;
    நிலை CPP_STRING16:
      மரம்_TYPE (மதிப்பு) = char16_array_type_முனை;
      நிறுத்து;
    நிலை CPP_STRING32:
      மரம்_TYPE (மதிப்பு) = char32_array_type_முனை;
      நிறுத்து;
    நிலை CPP_WSTRING:
      மரம்_TYPE (மதிப்பு) = wchar_array_type_முனை;
    }
  மதிப்பு = fix_string_type (மதிப்பு);

  எனில் (மொத்தம் > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.மதிப்பு = மதிப்பு;
  ret.original_code = STRING_CST;
  ret.original_type = NULL_மரம்;
  set_c_கோவை_source_range (&ret, get_range_from_loc (வரி_table, loc));
  ret.m_decimal = 0;
  parser->seen_string_literal = உண்மை;
  திரும்பு ret;
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

நிலையான கட்டமைப்பு c_கோவை
c_parser_கோவை_no_commas (c_parser *parser, கட்டமைப்பு c_கோவை *after,
			 மரம் omp_atomic_lhs)
{
  கட்டமைப்பு c_கோவை lhs, rhs, ret;
  எண்ணிக்கை மரம்_code code;
  location_t op_location, exp_location;
  தருக்க save_in_omp_for = c_in_omp_for;
  c_in_omp_for = பொய்;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_expression (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  தேர்வு (c_parser_peek_token (parser)->type)
    {
    நிலை CPP_EQ:
      code = NOP_கோவை;
      நிறுத்து;
    நிலை CPP_MULT_EQ:
      code = MULT_கோவை;
      நிறுத்து;
    நிலை CPP_DIV_EQ:
      code = TRUNC_DIV_கோவை;
      நிறுத்து;
    நிலை CPP_MOD_EQ:
      code = TRUNC_MOD_கோவை;
      நிறுத்து;
    நிலை CPP_PLUS_EQ:
      code = PLUS_கோவை;
      நிறுத்து;
    நிலை CPP_MINUS_EQ:
      code = MINUS_கோவை;
      நிறுத்து;
    நிலை CPP_LSHIFT_EQ:
      code = LSHIFT_கோவை;
      நிறுத்து;
    நிலை CPP_RSHIFT_EQ:
      code = RSHIFT_கோவை;
      நிறுத்து;
    நிலை CPP_AND_EQ:
      code = BIT_AND_கோவை;
      நிறுத்து;
    நிலை CPP_XOR_EQ:
      code = BIT_XOR_கோவை;
      நிறுத்து;
    நிலை CPP_OR_EQ:
      code = BIT_IOR_கோவை;
      நிறுத்து;
    இயல்பு:
      c_in_omp_for = save_in_omp_for;
      திரும்பு lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_கோவை_no_commas (parser, வெற்று);
  rhs = convert_lvalue_to_rvalue (exp_location, rhs, உண்மை, உண்மை);

  ret.மதிப்பு = build_modify_கோவை (op_location, lhs.மதிப்பு, lhs.original_type,
				 code, exp_location, rhs.மதிப்பு,
				 rhs.original_type);
  ret.m_decimal = 0;
  set_c_கோவை_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  எனில் (code == NOP_கோவை)
    ret.original_code = MODIFY_கோவை;
  இல்லையெனில்
    {
      suppress_warning (ret.மதிப்பு, OPT_Wparentheses);
      ret.original_code = ERROR_MARK;
    }
  ret.original_type = வெற்று;
  c_in_omp_for = save_in_omp_for;
  திரும்பு ret;
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

நிலையான கட்டமைப்பு c_கோவை
c_parser_conditional_expression (c_parser *parser, கட்டமைப்பு c_கோவை *after,
				 மரம் omp_atomic_lhs)
{
  கட்டமைப்பு c_கோவை cond, exp1, exp2, ret;
  location_t start, cond_loc, colon_loc;
  தருக்க save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_இருமம்_expression (parser, after, omp_atomic_lhs);

  எனில் (c_parser_next_token_is_not (parser, CPP_QUERY))
    திரும்பு cond;
  c_omp_array_section_p = பொய்;
  எனில் (cond.மதிப்பு != error_mark_முனை)
    start = cond.get_start ();
  இல்லையெனில்
    start = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_to_rvalue (cond_loc, cond, உண்மை, உண்மை);
  c_parser_consume_token (parser);
  எனில் (c_parser_next_token_is (parser, CPP_COLON))
    {
      மரம் eptype = NULL_மரம்;

      location_t நடு_loc = c_parser_peek_token (parser)->location;
      pedwarn (நடு_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      எனில் (மரம்_CODE (cond.மதிப்பு) == EXCESS_PRECISION_கோவை)
	{
	  eptype = மரம்_TYPE (cond.மதிப்பு);
	  cond.மதிப்பு = மரம்_OPERAND (cond.மதிப்பு, 0);
	}
      மரம் e = cond.மதிப்பு;
      போது (மரம்_CODE (e) == COMPOUND_கோவை)
	e = மரம்_OPERAND (e, 1);
      warn_for_omitted_condop (நடு_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.மதிப்பு = save_கோவை (default_conversion (cond.மதிப்பு));
      எனில் (eptype)
	exp1.மதிப்பு = build1 (EXCESS_PRECISION_கோவை, eptype, exp1.மதிப்பு);
      exp1.original_type = வெற்று;
      exp1.src_range = cond.src_range;
      cond.மதிப்பு = c_objc_common_truthvalue_conversion (cond_loc, exp1.மதிப்பு);
      c_inhibit_evaluation_warnings += cond.மதிப்பு == truthvalue_true_முனை;
    }
  இல்லையெனில்
    {
      cond.மதிப்பு
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.மதிப்பு));
      c_inhibit_evaluation_warnings += cond.மதிப்பு == truthvalue_false_முனை;
      exp1 = c_parser_expression_conv (parser);
      mark_exp_read (exp1.மதிப்பு);
      c_inhibit_evaluation_warnings +=
	((cond.மதிப்பு == truthvalue_true_முனை)
	 - (cond.மதிப்பு == truthvalue_false_முனை));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.மதிப்பு == truthvalue_true_முனை;
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = வெற்று;
      c_omp_array_section_p = save_c_omp_array_section_p;
      திரும்பு ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_expression (parser, வெற்று, NULL_மரம்);
    exp2 = convert_lvalue_to_rvalue (exp2_loc, exp2, உண்மை, உண்மை);
  }
  c_inhibit_evaluation_warnings -= cond.மதிப்பு == truthvalue_true_முனை;
  location_t loc1 = make_location (exp1.get_start (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_start (), exp2.src_range);
  எனில் (UNLIKELY (omp_atomic_lhs != வெற்று)
      && (மரம்_CODE (cond.மதிப்பு) == GT_கோவை
	  || மரம்_CODE (cond.மதிப்பு) == LT_கோவை
	  || மரம்_CODE (cond.மதிப்பு) == EQ_கோவை)
      && c_மரம்_equal (exp2.மதிப்பு, omp_atomic_lhs)
      && (c_மரம்_equal (மரம்_OPERAND (cond.மதிப்பு, 0), omp_atomic_lhs)
	  || c_மரம்_equal (மரம்_OPERAND (cond.மதிப்பு, 1), omp_atomic_lhs)))
    ret.மதிப்பு = build3_loc (colon_loc, COND_கோவை, மரம்_TYPE (omp_atomic_lhs),
			    cond.மதிப்பு, exp1.மதிப்பு, exp2.மதிப்பு);
  இல்லையெனில்
    ret.மதிப்பு
      = build_conditional_கோவை (colon_loc, cond.மதிப்பு,
				cond.original_code == C_MAYBE_CONST_கோவை,
				exp1.மதிப்பு, exp1.original_type, loc1,
				exp2.மதிப்பு, exp2.original_type, loc2);
  ret.original_code = ERROR_MARK;
  எனில் (exp1.மதிப்பு == error_mark_முனை || exp2.மதிப்பு == error_mark_முனை)
    ret.original_type = வெற்று;
  இல்லையெனில்
    {
      மரம் t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : மரம்_TYPE (exp1.மதிப்பு);
      t2 = exp2.original_type ? exp2.original_type : மரம்_TYPE (exp2.மதிப்பு);
      ret.original_type = ((t1 != error_mark_முனை
			    && t2 != error_mark_முனை
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : வெற்று);
    }
  set_c_கோவை_source_range (&ret, start, exp2.get_finish ());
  ret.m_decimal = 0;
  c_omp_array_section_p = save_c_omp_array_section_p;
  திரும்பு ret;
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

நிலையான கட்டமைப்பு c_கோவை
c_parser_இருமம்_expression (c_parser *parser, கட்டமைப்பு c_கோவை *after,
			    மரம் omp_atomic_lhs)
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

  கட்டமைப்பு {
    /* The expression at this stack level.  */
    கட்டமைப்பு c_கோவை கோவை;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    எண்ணிக்கை c_parser_prec prec;
    /* The operation on its left.  */
    எண்ணிக்கை மரம்_code op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    மரம் sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    மரம் orig_கோவை;
  } அடுக்கு[இலக்கம்_PRECS];
  முழு sp;
  /* Location of the binary operator.  */
  location_t இருமம்_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#define எடு_2								      \
  செய் {									      \
    தேர்வு (அடுக்கு[sp].op)						      \
      {									      \
      நிலை TRUTH_ANDIF_கோவை:						      \
	c_inhibit_evaluation_warnings -= (அடுக்கு[sp - 1].கோவை.மதிப்பு	      \
					  == truthvalue_false_முனை);	      \
	நிறுத்து;								      \
      நிலை TRUTH_ORIF_கோவை:						      \
	c_inhibit_evaluation_warnings -= (அடுக்கு[sp - 1].கோவை.மதிப்பு	      \
					  == truthvalue_true_முனை);	      \
	நிறுத்து;								      \
      நிலை TRUNC_DIV_கோவை:						      \
	எனில் ((அடுக்கு[sp - 1].கோவை.original_code == SIZEOF_கோவை		      \
	     || அடுக்கு[sp - 1].கோவை.original_code == PAREN_SIZEOF_கோவை)	      \
	    && (அடுக்கு[sp].கோவை.original_code == SIZEOF_கோவை		      \
		|| அடுக்கு[sp].கோவை.original_code == PAREN_SIZEOF_கோவை))	      \
	  {								      \
	    மரம் type0 = அடுக்கு[sp - 1].sizeof_arg;			      \
	    மரம் type1 = அடுக்கு[sp].sizeof_arg;				      \
	    மரம் first_arg = type0;					      \
	    எனில் (!TYPE_P (type0))					      \
	      type0 = மரம்_TYPE (type0);				      \
	    எனில் (!TYPE_P (type1))					      \
	      type1 = மரம்_TYPE (type1);				      \
	    எனில் (POINTER_TYPE_P (type0)					      \
		&& comptypes (மரம்_TYPE (type0), type1)			      \
		&& !(மரம்_CODE (first_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (first_arg)			      \
		     && warn_sizeof_array_argument))			      \
	      {								      \
		auto_diagnostic_group d;				      \
		எனில் (warning_at (அடுக்கு[sp].loc, OPT_Wsizeof_pointer_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  எனில் (DECL_P (first_arg))				      \
		    inform (DECL_SOURCE_LOCATION (first_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    இல்லையெனில் எனில் (மரம்_CODE (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (மரம்_TYPE (type0)))  \
		     && அடுக்கு[sp].கோவை.original_code != PAREN_SIZEOF_கோவை)    \
	      maybe_warn_sizeof_array_div (அடுக்கு[sp].loc, first_arg, type0,   \
					   அடுக்கு[sp].sizeof_arg, type1);      \
	  }								      \
	நிறுத்து;								      \
      இயல்பு:								      \
	நிறுத்து;								      \
      }									      \
    அடுக்கு[sp - 1].கோவை							      \
      = convert_lvalue_to_rvalue (அடுக்கு[sp - 1].loc,			      \
				  அடுக்கு[sp - 1].கோவை, உண்மை, உண்மை);	      \
    அடுக்கு[sp].கோவை							      \
      = convert_lvalue_to_rvalue (அடுக்கு[sp].loc,			      \
				  அடுக்கு[sp].கோவை, உண்மை, உண்மை);		      \
    எனில் (UNLIKELY (omp_atomic_lhs != NULL_மரம்) && sp == 1		      \
	&& ((c_parser_next_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << அடுக்கு[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_SHIFT)		      \
		     | (1 << PREC_ADD) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_next_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_முனை			      \
		     && c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (அடுக்கு[sp].prec == PREC_REL || அடுக்கு[sp].prec == PREC_EQ)))\
	&& அடுக்கு[sp].op != TRUNC_MOD_கோவை				      \
	&& அடுக்கு[sp].op != GE_கோவை					      \
	&& அடுக்கு[sp].op != LE_கோவை					      \
	&& அடுக்கு[sp].op != NE_கோவை					      \
	&& அடுக்கு[0].கோவை.மதிப்பு != error_mark_முனை			      \
	&& அடுக்கு[1].கோவை.மதிப்பு != error_mark_முனை			      \
	&& (omp_atomic_lhs == void_list_முனை				      \
	    || c_மரம்_equal (அடுக்கு[0].கோவை.மதிப்பு, omp_atomic_lhs)	      \
	    || c_மரம்_equal (அடுக்கு[1].கோவை.மதிப்பு, omp_atomic_lhs)	      \
	    || (அடுக்கு[sp].op == EQ_கோவை					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	மரம் t = make_முனை (அடுக்கு[1].op);				      \
	மரம்_TYPE (t) = மரம்_TYPE (அடுக்கு[0].கோவை.மதிப்பு);		      \
	மரம்_OPERAND (t, 0) = அடுக்கு[0].கோவை.மதிப்பு;			      \
	மரம்_OPERAND (t, 1) = அடுக்கு[1].கோவை.மதிப்பு;			      \
	அடுக்கு[0].கோவை.மதிப்பு = t;					      \
	அடுக்கு[0].கோவை.m_decimal = 0;					      \
      }									      \
    இல்லையெனில்								      \
      அடுக்கு[sp - 1].கோவை = parser_build_இருமம்_op (அடுக்கு[sp].loc,	      \
						   அடுக்கு[sp].op,	      \
						   அடுக்கு[sp - 1].கோவை,	      \
						   அடுக்கு[sp].கோவை,	      \
						   அடுக்கு[sp - 1].orig_கோவை);  \
    அடுக்கு[sp - 1].orig_கோவை = NULL_மரம்;				      \
    sp--;								      \
  } போது (0)
  gcc_assert (!after || c_dialect_objc ());
  அடுக்கு[0].loc = c_parser_peek_token (parser)->location;
  அடுக்கு[0].கோவை = c_parser_cast_expression (parser, after);
  அடுக்கு[0].prec = PREC_NONE;
  அடுக்கு[0].sizeof_arg = c_last_sizeof_arg;
  அடுக்கு[0].orig_கோவை = NULL_மரம்;
  sp = 0;
  போது (உண்மை)
    {
      எண்ணிக்கை c_parser_prec oprec;
      எண்ணிக்கை மரம்_code ocode;
      source_range src_range;
      எனில் (parser->error)
	செல் out;
      தேர்வு (c_parser_peek_token (parser)->type)
	{
	நிலை CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_கோவை;
	  நிறுத்து;
	நிலை CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_கோவை;
	  நிறுத்து;
	நிலை CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_கோவை;
	  நிறுத்து;
	நிலை CPP_PLUS:
	  oprec = PREC_ADD;
	  ocode = PLUS_கோவை;
	  நிறுத்து;
	நிலை CPP_MINUS:
	  oprec = PREC_ADD;
	  ocode = MINUS_கோவை;
	  நிறுத்து;
	நிலை CPP_LSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = LSHIFT_கோவை;
	  நிறுத்து;
	நிலை CPP_RSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = RSHIFT_கோவை;
	  நிறுத்து;
	நிலை CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_கோவை;
	  நிறுத்து;
	நிலை CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_கோவை;
	  நிறுத்து;
	நிலை CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_கோவை;
	  நிறுத்து;
	நிலை CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_கோவை;
	  நிறுத்து;
	நிலை CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_கோவை;
	  நிறுத்து;
	நிலை CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_கோவை;
	  நிறுத்து;
	நிலை CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = BIT_AND_கோவை;
	  நிறுத்து;
	நிலை CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = BIT_XOR_கோவை;
	  நிறுத்து;
	நிலை CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = BIT_IOR_கோவை;
	  நிறுத்து;
	நிலை CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_கோவை;
	  நிறுத்து;
	நிலை CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_கோவை;
	  நிறுத்து;
	இயல்பு:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  செல் out;
	}
      இருமம்_loc = c_parser_peek_token (parser)->location;
      போது (oprec <= அடுக்கு[sp].prec)
	எடு_2;
      c_parser_consume_token (parser);
      தேர்வு (ocode)
	{
	நிலை TRUTH_ANDIF_கோவை:
	  src_range = அடுக்கு[sp].கோவை.src_range;
	  அடுக்கு[sp].கோவை
	    = convert_lvalue_to_rvalue (அடுக்கு[sp].loc,
					அடுக்கு[sp].கோவை, உண்மை, உண்மை);
	  அடுக்கு[sp].orig_கோவை = அடுக்கு[sp].கோவை.மதிப்பு;
	  அடுக்கு[sp].கோவை.மதிப்பு = c_objc_common_truthvalue_conversion
	    (அடுக்கு[sp].loc, default_conversion (அடுக்கு[sp].கோவை.மதிப்பு));
	  c_inhibit_evaluation_warnings += (அடுக்கு[sp].கோவை.மதிப்பு
					    == truthvalue_false_முனை);
	  set_c_கோவை_source_range (&அடுக்கு[sp].கோவை, src_range);
	  நிறுத்து;
	நிலை TRUTH_ORIF_கோவை:
	  src_range = அடுக்கு[sp].கோவை.src_range;
	  அடுக்கு[sp].கோவை
	    = convert_lvalue_to_rvalue (அடுக்கு[sp].loc,
					அடுக்கு[sp].கோவை, உண்மை, உண்மை);
	  அடுக்கு[sp].orig_கோவை = அடுக்கு[sp].கோவை.மதிப்பு;
	  அடுக்கு[sp].கோவை.மதிப்பு = c_objc_common_truthvalue_conversion
	    (அடுக்கு[sp].loc, default_conversion (அடுக்கு[sp].கோவை.மதிப்பு));
	  c_inhibit_evaluation_warnings += (அடுக்கு[sp].கோவை.மதிப்பு
					    == truthvalue_true_முனை);
	  set_c_கோவை_source_range (&அடுக்கு[sp].கோவை, src_range);
	  நிறுத்து;
	இயல்பு:
	  நிறுத்து;
	}
      sp++;
      அடுக்கு[sp].loc = இருமம்_loc;
      அடுக்கு[sp].கோவை = c_parser_cast_expression (parser, வெற்று);
      அடுக்கு[sp].prec = oprec;
      அடுக்கு[sp].op = ocode;
      அடுக்கு[sp].sizeof_arg = c_last_sizeof_arg;
      அடுக்கு[sp].orig_கோவை = NULL_மரம்;
    }
 out:
  போது (sp > 0)
    எடு_2;
  திரும்பு அடுக்கு[0].கோவை;
#undef எடு_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

நிலையான கட்டமைப்பு c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  தருக்க seen_scspec = பொய்;
  கட்டமைப்பு c_declspecs *specs = build_null_declspecs ();
  போது (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      தேர்வு (c_parser_peek_token (parser)->keyword)
	{
	நிலை RID_CONSTEXPR:
	நிலை RID_REGISTER:
	நிலை RID_STATIC:
	நிலை RID_THREAD:
	  seen_scspec = உண்மை;
	  declspecs_add_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->மதிப்பு);
	  c_parser_consume_token (parser);
	  நிறுத்து;
	இயல்பு:
	  செல் out;
	}
    }
 out:
  திரும்பு seen_scspec ? specs : வெற்று;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

நிலையான கட்டமைப்பு c_கோவை
c_parser_cast_expression (c_parser *parser, கட்டமைப்பு c_கோவை *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  எனில் (after)
    திரும்பு c_parser_postfix_expression_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      கட்டமைப்பு c_declspecs *scspecs;
      கட்டமைப்பு c_type_name *type_name;
      கட்டமைப்பு c_கோவை ret;
      கட்டமைப்பு c_கோவை கோவை;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, உண்மை);
      parens.skip_until_found_close (parser);
      எனில் (type_name == வெற்று)
	{
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = வெற்று;
	  திரும்பு ret;
	}

      /* Save casted types in the function's used types hash table.  */
      used_types_செருகு (type_name->specs->type);

      எனில் (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	திரும்பு c_parser_postfix_expression_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      எனில் (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      எனில் (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t கோவை_loc = c_parser_peek_token (parser)->location;
	கோவை = c_parser_cast_expression (parser, வெற்று);
	கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, உண்மை, உண்மை);
      }
      ret.மதிப்பு = c_cast_கோவை (cast_loc, type_name, கோவை.மதிப்பு);
      எனில் (ret.மதிப்பு && கோவை.மதிப்பு)
	set_c_கோவை_source_range (&ret, cast_loc, கோவை.get_finish ());
      ret.original_code = ERROR_MARK;
      ret.original_type = வெற்று;
      ret.m_decimal = 0;
      திரும்பு ret;
    }
  இல்லையெனில்
    திரும்பு c_parser_unary_expression (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

நிலையான வெறுமை
mark_exp_read_cond (மரம் exp)
{
  எனில் ((VAR_P (exp) || மரம்_CODE (exp) == PARM_DECL)
      && (VAR_P (exp) ? warn_unused_but_set_variable
		      : warn_unused_but_set_parameter) > 1)
    திரும்பு;

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

நிலையான கட்டமைப்பு c_கோவை
c_parser_unary_expression (c_parser *parser)
{
  முழு ext;
  கட்டமைப்பு c_கோவை ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t exp_loc;
  location_t finish;
  ret.original_code = ERROR_MARK;
  ret.original_type = வெற்று;
  தேர்வு (c_parser_peek_token (parser)->type)
    {
    நிலை CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, வெற்று);
      mark_exp_read_cond (op.மதிப்பு);
      op = default_function_array_conversion (exp_loc, op);
      திரும்பு parser_build_unary_op (op_loc, PREINCREMENT_கோவை, op);
    நிலை CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, வெற்று);
      mark_exp_read_cond (op.மதிப்பு);
      op = default_function_array_conversion (exp_loc, op);
      திரும்பு parser_build_unary_op (op_loc, PREDECREMENT_கோவை, op);
    நிலை CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, வெற்று);
      mark_exp_read (op.மதிப்பு);
      திரும்பு parser_build_unary_op (op_loc, ADDR_கோவை, op);
    நிலை CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_expression (parser, வெற்று);
	finish = op.get_finish ();
	op = convert_lvalue_to_rvalue (exp_loc, op, உண்மை, உண்மை);
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.மதிப்பு = build_indirect_ref (combined_loc, op.மதிப்பு, RO_UNARY_STAR);
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ret.m_decimal = 0;
	திரும்பு ret;
      }
    நிலை CPP_PLUS:
      எனில் (!c_dialect_objc () && !in_system_header_at (உள்ளீடு_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, வெற்று);
      op = convert_lvalue_to_rvalue (exp_loc, op, உண்மை, உண்மை);
      திரும்பு parser_build_unary_op (op_loc, CONVERT_கோவை, op);
    நிலை CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, வெற்று);
      op = convert_lvalue_to_rvalue (exp_loc, op, உண்மை, உண்மை);
      திரும்பு parser_build_unary_op (op_loc, NEGATE_கோவை, op);
    நிலை CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, வெற்று);
      op = convert_lvalue_to_rvalue (exp_loc, op, உண்மை, உண்மை);
      திரும்பு parser_build_unary_op (op_loc, BIT_NOT_கோவை, op);
    நிலை CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, வெற்று);
      op = convert_lvalue_to_rvalue (exp_loc, op, உண்மை, உண்மை);
      திரும்பு parser_build_unary_op (op_loc, TRUTH_NOT_கோவை, op);
    நிலை CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      எனில் (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ret.மதிப்பு = finish_label_address_கோவை
	    (c_parser_peek_token (parser)->மதிப்பு, op_loc);
	  set_c_கோவை_source_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_finish ());
	  c_parser_consume_token (parser);
	}
      இல்லையெனில்
	{
	  c_parser_error (parser, "expected identifier");
	  ret.set_error ();
	}
      திரும்பு ret;
    நிலை CPP_KEYWORD:
      {
	எண்ணிக்கை rid rid = c_parser_peek_token (parser)->keyword;
	தேர்வு (rid)
	  {
	  நிலை RID_COUNTOF:
	  நிலை RID_SIZEOF:
	    திரும்பு c_parser_sizeof_or_countof_expression (parser, rid);
	  நிலை RID_ALIGNOF:
	    திரும்பு c_parser_alignof_expression (parser);
	  நிலை RID_MAXOF:
	  நிலை RID_MINOF:
	    திரும்பு c_parser_maxof_or_minof_expression (parser, rid);
	  நிலை RID_BUILTIN_HAS_ATTRIBUTE:
	    திரும்பு c_parser_has_attribute_expression (parser);
	  நிலை RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_expression (parser, வெற்று);
	    restore_extension_diagnostics (ext);
	    திரும்பு ret;
	  நிலை RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, வெற்று);
	    op = default_function_array_conversion (exp_loc, op);
	    திரும்பு parser_build_unary_op (op_loc, REALPART_கோவை, op);
	  நிலை RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, வெற்று);
	    op = default_function_array_conversion (exp_loc, op);
	    திரும்பு parser_build_unary_op (op_loc, IMAGPART_கோவை, op);
	  நிலை RID_TRANSACTION_ATOMIC:
	  நிலை RID_TRANSACTION_RELAXED:
	    திரும்பு c_parser_transaction_expression (parser, rid);
	  நிலை RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.மதிப்பு = void_முனை;
	    set_c_கோவை_source_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    திரும்பு ret;
	  இயல்பு:
	    திரும்பு c_parser_postfix_expression (parser);
	  }
      }
    இயல்பு:
      திரும்பு c_parser_postfix_expression (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

நிலையான கட்டமைப்பு c_கோவை
c_parser_sizeof_or_countof_expression (c_parser *parser, எண்ணிக்கை rid rid)
{
  மாறிலி எழுத்து *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  கட்டமைப்பு c_கோவை கோவை;
  கட்டமைப்பு c_கோவை result;
  location_t கோவை_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  எனில் (rid == RID_COUNTOF)
    pedwarn_c23 (start, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  எனில் (rid == RID_COUNTOF)
    in_countof++;
  இல்லையெனில்
    in_sizeof++;
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      கட்டமைப்பு c_declspecs *scspecs;
      கட்டமைப்பு c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      கோவை_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, உண்மை);
      parens.skip_until_found_close (parser);
      finish = parser->tokens_buf[0].location;
      எனில் (type_name == வெற்று)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  கோவை.set_error ();
	  செல் Xof_கோவை;
	}
      எனில் (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  கோவை = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       கோவை_loc);
	  finish = கோவை.get_finish ();
	  செல் Xof_கோவை;
	}
      /* sizeof ( type-name ).  */
      எனில் (scspecs)
	error_at (கோவை_loc, "storage class specifier in %qs", op_name);
      எனில் (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      எனில் (rid == RID_COUNTOF)
	{
	  in_countof--;
	  result = c_கோவை_countof_type (கோவை_loc, type_name);
	}
      இல்லையெனில்
	{
	  in_sizeof--;
	  result = c_கோவை_sizeof_type (கோவை_loc, type_name);
	}
    }
  இல்லையெனில்
    {
      கோவை_loc = c_parser_peek_token (parser)->location;
      கோவை = c_parser_unary_expression (parser);
      finish = கோவை.get_finish ();
    Xof_கோவை:
      c_inhibit_evaluation_warnings--;
      எனில் (rid == RID_COUNTOF)
	in_countof--;
      இல்லையெனில்
	in_sizeof--;
      mark_exp_read (கோவை.மதிப்பு);
      எனில் (மரம்_CODE (கோவை.மதிப்பு) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (மரம்_OPERAND (கோவை.மதிப்பு, 1)))
	error_at (கோவை_loc, "%qs applied to a bit-field", op_name);
      எனில் (rid == RID_COUNTOF)
	result = c_கோவை_countof_கோவை (கோவை_loc, கோவை);
      இல்லையெனில்
	result = c_கோவை_sizeof_கோவை (கோவை_loc, கோவை);
    }
  எனில் (finish == UNKNOWN_LOCATION)
    finish = start;
  set_c_கோவை_source_range (&result, start, finish);
  திரும்பு result;
}

/* Parse an alignof expression.  */

நிலையான கட்டமைப்பு c_கோவை
c_parser_alignof_expression (c_parser *parser)
{
  கட்டமைப்பு c_கோவை கோவை;
  location_t start_loc = c_parser_peek_token (parser)->location;
  location_t end_loc;
  மரம் alignof_spelling = c_parser_peek_token (parser)->மதிப்பு;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNOF));
  தருக்க is_c11_alignof = (strcmp (IDENTIFIER_POINTER (alignof_spelling),
				"_Alignof") == 0
			 || strcmp (IDENTIFIER_POINTER (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  எனில் (is_c11_alignof)
    {
      எனில் (flag_isoc99)
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      இல்லையெனில்
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_alignof++;
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      கட்டமைப்பு c_declspecs *scspecs;
      கட்டமைப்பு c_type_name *type_name;
      கட்டமைப்பு c_கோவை ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, உண்மை);
      end_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
      எனில் (type_name == வெற்று)
	{
	  கட்டமைப்பு c_கோவை ret;
	  c_inhibit_evaluation_warnings--;
	  in_alignof--;
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = வெற்று;
	  திரும்பு ret;
	}
      எனில் (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  கோவை = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  செல் alignof_கோவை;
	}
      /* alignof ( type-name ).  */
      எனில் (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      எனில் (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      ret.மதிப்பு = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       வெற்று, வெற்று),
					    பொய், is_c11_alignof, 1);
      ret.original_code = ERROR_MARK;
      ret.original_type = வெற்று;
      set_c_கோவை_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      திரும்பு ret;
    }
  இல்லையெனில்
    {
      கட்டமைப்பு c_கோவை ret;
      கோவை = c_parser_unary_expression (parser);
      end_loc = கோவை.src_range.m_finish;
    alignof_கோவை:
      mark_exp_read (கோவை.மதிப்பு);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      எனில் (is_c11_alignof)
	pedwarn (start_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.மதிப்பு = c_alignof_கோவை (start_loc, கோவை.மதிப்பு);
      ret.original_code = ERROR_MARK;
      ret.original_type = வெற்று;
      set_c_கோவை_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      திரும்பு ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

நிலையான கட்டமைப்பு c_கோவை
c_parser_maxof_or_minof_expression (c_parser *parser, எண்ணிக்கை rid rid)
{
  மாறிலி எழுத்து *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  கட்டமைப்பு c_கோவை result;
  location_t கோவை_loc;
  கட்டமைப்பு c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  pedwarn (start, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  எனில் (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      செல் fail;
    }
  parens.consume_open (parser);
  கோவை_loc = c_parser_peek_token (parser)->location;
  எனில் (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (கோவை_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_found_close (parser);
      செல் fail;
    }
  type_name = c_parser_type_name (parser, உண்மை);
  எனில் (type_name == வெற்று)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_found_close (parser);
      செல் fail;
    }
  parens.skip_until_found_close (parser);
  finish = parser->tokens_buf[0].location;
  எனில் (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  எனில் (rid == RID_MAXOF)
    result = c_கோவை_maxof_type (கோவை_loc, type_name);
  இல்லையெனில்
    result = c_கோவை_minof_type (கோவை_loc, type_name);
  set_c_கோவை_source_range (&result, start, finish);
  திரும்பு result;
fail:
  c_inhibit_evaluation_warnings--;
  result.set_error ();
  result.original_code = ERROR_MARK;
  result.original_type = வெற்று;
  திரும்பு result;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

நிலையான கட்டமைப்பு c_கோவை
c_parser_has_attribute_expression (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t start = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;

      கட்டமைப்பு c_கோவை result;
      result.set_error ();
      result.original_code = ERROR_MARK;
      result.original_type = வெற்று;
      திரும்பு result;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  in_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  மரம் oper = NULL_மரம்;
  எனில் (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      கட்டமைப்பு c_type_name *tname = c_parser_type_name (parser);
      in_typeof--;
      எனில் (tname)
	{
	  oper = groktypename (tname, வெற்று, வெற்று);
	  எடு_maybe_used (c_type_variably_modified_p (oper));
	}
    }
  இல்லையெனில்
    {
      கட்டமைப்பு c_கோவை cexpr = c_parser_கோவை_no_commas (parser, வெற்று);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      எனில் (cexpr.மதிப்பு != error_mark_முனை)
	{
	  mark_exp_read (cexpr.மதிப்பு);
	  oper = cexpr.மதிப்பு;
	  மரம் etype = மரம்_TYPE (oper);
	  தருக்க was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  எனில் (was_vm)
	    oper = c_fully_fold (oper, பொய், வெற்று);
	  எடு_maybe_used (was_vm);
	}
    }

  கட்டமைப்பு c_கோவை result;
  result.original_code = ERROR_MARK;
  result.original_type = வெற்று;

  எனில் (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      result.set_error ();
      திரும்பு result;
    }

  தருக்க save_translate_strings_p = parser->translate_strings_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  மரம் attr = c_parser_gnu_attribute (parser, NULL_மரம், பொய், பொய்);

  parser->translate_strings_p = save_translate_strings_p;

  location_t finish = c_parser_peek_token (parser)->location;
  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  இல்லையெனில்
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);

      result.set_error ();
      திரும்பு result;
    }

  எனில் (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      result.set_error ();
      திரும்பு result;
    }

  result.original_code = INTEGER_CST;
  result.original_type = boolean_type_முனை;

  எனில் (has_attribute (atloc, oper, attr, default_conversion))
    result.மதிப்பு = boolean_true_முனை;
  இல்லையெனில்
    result.மதிப்பு =  boolean_false_முனை;

  set_c_கோவை_source_range (&result, start, finish);
  result.m_decimal = 0;
  திரும்பு result;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
நிலையான தருக்க
c_parser_get_builtin_args (c_parser *parser, மாறிலி எழுத்து *bname,
			   vec<c_கோவை_t, va_gc> **ret_cexpr_list,
			   தருக்க choose_கோவை_p,
			   location_t *out_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_கோவை_t, va_gc> *cexpr_list;
  c_கோவை_t கோவை;
  தருக்க saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = வெற்று;
  எனில் (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      திரும்பு பொய்;
    }

  c_parser_consume_token (parser);

  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      *out_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      திரும்பு உண்மை;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= choose_கோவை_p;
  கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_safe_தள்ளு (cexpr_list, கோவை);
  போது (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      எனில் (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  மரம் மதிப்பு = embed->மதிப்பு;
	  கோவை.original_code = INTEGER_CST;
	  கோவை.original_type = integer_type_முனை;
	  கோவை.மதிப்பு = NULL_மரம்;
	  set_c_கோவை_source_range (&கோவை, embed->get_range ());
	  கோவை.m_decimal = 0;
	  க்கு (unsigned முழு i = 0; i < (unsigned) RAW_DATA_LENGTH (மதிப்பு); i++)
	    {
	      கோவை.மதிப்பு = build_int_cst (integer_type_முனை,
					  RAW_DATA_UCHAR_ELT (மதிப்பு, i));
	      vec_safe_தள்ளு (cexpr_list, கோவை);
	    }
	  c_parser_consume_token (parser);
	  தொடர்;
	}
      கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      vec_safe_தள்ளு (cexpr_list, கோவை);
    }

  *out_close_paren_loc = c_parser_peek_token (parser)->location;
  எனில் (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    திரும்பு பொய்;

  *ret_cexpr_list = cexpr_list;
  திரும்பு உண்மை;
}

/* This represents a single generic-association.  */

கட்டமைப்பு c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  மரம் type;
  /* The association's expression.  */
  கட்டமைப்பு c_கோவை expression;
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

நிலையான கட்டமைப்பு c_கோவை
c_parser_generic_selection (c_parser *parser)
{
  கட்டமைப்பு c_கோவை selector, error_கோவை;
  மரம் selector_type;
  கட்டமைப்பு c_generic_association matched_assoc;
  முழு match_found = -1;
  location_t generic_loc, selector_loc;

  error_கோவை.original_code = ERROR_MARK;
  error_கோவை.original_type = வெற்று;
  error_கோவை.set_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_மரம்;
  matched_assoc.expression = error_கோவை;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_GENERIC));
  generic_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  எனில் (flag_isoc99)
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C99 does not support %<_Generic%>");
  இல்லையெனில்
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C90 does not support %<_Generic%>");

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு error_கோவை;

  selector_loc = c_parser_peek_token (parser)->location;
  எனில் (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      c_inhibit_evaluation_warnings++;
      pedwarn_c23 (selector_loc, OPT_Wpedantic,
		   "ISO C does not support use of type name as %<_Generic%> "
		   "controlling operand before C2Y");
      கட்டமைப்பு c_type_name *type = c_parser_type_name (parser);
      எனில் (type)
	selector_type = groktypename (type, வெற்று, வெற்று);
      c_inhibit_evaluation_warnings--;
      எனில் (!type)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
	  திரும்பு error_கோவை;
	}
    }
  இல்லையெனில்
    {
      c_inhibit_evaluation_warnings++;
      in_generic++;
      selector = c_parser_கோவை_no_commas (parser, வெற்று);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      in_generic--;
      எடு_maybe_used (!flag_isoc23);

      எனில் (selector.மதிப்பு == error_mark_முனை)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
	  திரும்பு selector;
	}
      mark_exp_read (selector.மதிப்பு);
      selector_type = மரம்_TYPE (selector.மதிப்பு);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      எனில் (மரம்_CODE (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      எனில் (FUNCTION_POINTER_TYPE_P (selector_type)
	  && TYPE_QUALS (மரம்_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_pointer_type (TYPE_MAIN_VARIANT (மரம்_TYPE (selector_type)));
    }

  எனில் (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
      திரும்பு error_கோவை;
    }

  auto_vec<c_generic_association> associations;
  கட்டமைப்பு maybe_used_decl *maybe_used_default = வெற்று;
  போது (1)
    {
      கட்டமைப்பு c_generic_association assoc, *iter;
      unsigned முழு ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      எனில் (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_மரம்;
	}
      இல்லையெனில்
	{
	  கட்டமைப்பு c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  எனில் (type_name == வெற்று)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
	      திரும்பு error_கோவை;
	    }
	  assoc.type = grokgenassoc (type_name);
	  எனில் (assoc.type == error_mark_முனை)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
	      திரும்பு error_கோவை;
	    }

	  எனில் (மரம்_CODE (assoc.type) == FUNCTION_TYPE)
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "function type before C2Y");
	  இல்லையெனில் எனில் (!COMPLETE_TYPE_P (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "incomplete type before C2Y");

	  எனில் (c_type_variably_modified_p (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "variably-modified type before C2Y");
	}

      எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
	  திரும்பு error_கோவை;
	}

      தருக்க match = assoc.type == NULL_மரம்
		   || comptypes (assoc.type, selector_type);

      எனில் (!match || matched_assoc.type != NULL_மரம்)
	c_inhibit_evaluation_warnings++;
      in_generic++;

      assoc.expression = c_parser_கோவை_no_commas (parser, வெற்று);

      எனில் (!match || matched_assoc.type != NULL_மரம்)
	c_inhibit_evaluation_warnings--;
      in_generic--;
      எனில் (!match)
	எடு_maybe_used (!flag_isoc23);
      இல்லையெனில் எனில் (assoc.type == NULL_மரம்)
	maybe_used_default = save_maybe_used ();
      இல்லையெனில்
	எடு_maybe_used (உண்மை);

      எனில் (assoc.expression.மதிப்பு == error_mark_முனை)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
	  திரும்பு error_கோவை;
	}

      க்கு (ix = 0; associations.iterate (ix, &iter); ++ix)
	{
	  எனில் (assoc.type == NULL_மரம்)
	    {
	      எனில் (iter->type == NULL_மரம்)
		{
		  error_at (assoc.type_location,
			    "duplicate %<default%> case in %<_Generic%>");
		  inform (iter->type_location, "original %<default%> is here");
		}
	    }
	  இல்லையெனில் எனில் (iter->type != NULL_மரம்)
	    {
	      எனில் (comptypes (assoc.type, iter->type))
		{
		  error_at (assoc.type_location,
			    "%<_Generic%> specifies two compatible types");
		  inform (iter->type_location, "compatible type is here");
		}
	    }
	}

      எனில் (assoc.type == NULL_மரம்)
	{
	  எனில் (match_found < 0)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	}
      இல்லையெனில் எனில் (match)
	{
	  எனில் (match_found < 0 || matched_assoc.type == NULL_மரம்)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	  இல்லையெனில்
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.safe_தள்ளு (assoc);

      எனில் (c_parser_peek_token (parser)->type != CPP_COMMA)
	நிறுத்து;
      c_parser_consume_token (parser);
    }

  எனில் (match_found >= 0 && matched_assoc.type == NULL_மரம்)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_used (maybe_used_default);
      எடு_maybe_used (உண்மை);
    }
  இல்லையெனில் எனில் (maybe_used_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_used (maybe_used_default);
      எடு_maybe_used (!flag_isoc23);
    }

  unsigned முழு ix;
  கட்டமைப்பு c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    எனில் (ix != (unsigned) match_found)
      mark_exp_read (iter->expression.மதிப்பு);

  எனில் (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
      திரும்பு error_கோவை;
    }

  எனில் (match_found < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      திரும்பு error_கோவை;
    }

  திரும்பு matched_assoc.expression;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

நிலையான unsigned முழு
check_tgmath_function (c_கோவை *கோவை, unsigned முழு pos)
{
  மரம் type = மரம்_TYPE (கோவை->மதிப்பு);
  எனில் (!FUNCTION_POINTER_TYPE_P (type))
    {
      error_at (கோவை->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      திரும்பு 0;
    }
  type = மரம்_TYPE (type);
  எனில் (!prototype_p (type))
    {
      error_at (கோவை->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      திரும்பு 0;
    }
  எனில் (stdarg_p (type))
    {
      error_at (கோவை->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      திரும்பு 0;
    }
  unsigned முழு nargs = 0;
  function_args_iterator iter;
  மரம் t;
  FOREACH_FUNCTION_ARGS (type, t, iter)
    {
      எனில் (t == void_type_முனை)
	நிறுத்து;
      nargs++;
    }
  எனில் (nargs == 0)
    {
      error_at (கோவை->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      திரும்பு 0;
    }
  திரும்பு nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
எண்ணிக்கை tgmath_parm_kind
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

நிலையான கட்டமைப்பு c_கோவை
c_parser_predefined_identifier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  தேர்வு (c_parser_peek_token (parser)->keyword)
    {
    நிலை RID_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__FUNCTION__");
      நிறுத்து;
    நிலை RID_PRETTY_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__PRETTY_FUNCTION__");
      நிறுத்து;
    நிலை RID_C99_FUNCTION_NAME:
      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support "
		   "%<__func__%> predefined identifier");
      நிறுத்து;
    இயல்பு:
      gcc_unreachable ();
    }

  கட்டமைப்பு c_கோவை கோவை;
  கோவை.original_code = ERROR_MARK;
  கோவை.original_type = வெற்று;
  கோவை.மதிப்பு = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->மதிப்பு);
  set_c_கோவை_source_range (&கோவை, loc, loc);
  கோவை.m_decimal = 0;
  c_parser_consume_token (parser);
  திரும்பு கோவை;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

நிலையான தருக்க
has_counted_by_object (மரம் ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  எனில் ((மரம்_CODE (ref) == INDIRECT_REF
       && is_access_with_size_p (மரம்_OPERAND (ref, 0)))
      || is_access_with_size_p (ref))
    திரும்பு உண்மை;
  திரும்பு பொய்;
}

/* Get the reference to the counted-by object associated with the REF.  */

நிலையான மரம்
get_counted_by_ref (மரம் ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  எனில் (மரம்_CODE (ref) == INDIRECT_REF
      && is_access_with_size_p (மரம்_OPERAND (ref, 0)))
    திரும்பு CALL_கோவை_ARG (மரம்_OPERAND (ref, 0), 1);
  இல்லையெனில் எனில் (is_access_with_size_p (ref))
    திரும்பு CALL_கோவை_ARG (ref, 1);

  திரும்பு NULL_மரம்;
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

நிலையான கட்டமைப்பு c_கோவை
c_parser_postfix_expression (c_parser *parser)
{
  கட்டமைப்பு c_கோவை கோவை, e1;
  கட்டமைப்பு c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  கோவை.original_code = ERROR_MARK;
  கோவை.original_type = வெற்று;
  கோவை.m_decimal = 0;
  தேர்வு (c_parser_peek_token (parser)->type)
    {
    நிலை CPP_எண்:
      கோவை.மதிப்பு = c_parser_peek_token (parser)->மதிப்பு;
      set_c_கோவை_source_range (&கோவை, tok_range);
      loc = c_parser_peek_token (parser)->location;
      கோவை.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      எனில் (மரம்_CODE (கோவை.மதிப்பு) == FIXED_CST
	  && !targetm.fixed_point_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  கோவை.set_error ();
	}
      நிறுத்து;
    நிலை CPP_CHAR:
    நிலை CPP_CHAR16:
    நிலை CPP_CHAR32:
    நிலை CPP_UTF8CHAR:
    நிலை CPP_WCHAR:
      கோவை.மதிப்பு = c_parser_peek_token (parser)->மதிப்பு;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      கோவை.original_type = char_type_முனை;
      set_c_கோவை_source_range (&கோவை, tok_range);
      c_parser_consume_token (parser);
      நிறுத்து;
    நிலை CPP_STRING:
    நிலை CPP_STRING16:
    நிலை CPP_STRING32:
    நிலை CPP_WSTRING:
    நிலை CPP_UTF8STRING:
      கோவை = c_parser_string_literal (parser, parser->translate_strings_p,
				      உண்மை);
      நிறுத்து;
    நிலை CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      கோவை.மதிப்பு
	= objc_build_string_object (c_parser_peek_token (parser)->மதிப்பு);
      set_c_கோவை_source_range (&கோவை, tok_range);
      c_parser_consume_token (parser);
      நிறுத்து;
    நிலை CPP_NAME:
      தேர்வு (c_parser_peek_token (parser)->id_kind)
	{
	நிலை C_ID_ID:
	  {
	    மரம் id = c_parser_peek_token (parser)->மதிப்பு;
	    c_parser_consume_token (parser);
	    கோவை.மதிப்பு = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &கோவை.original_type);
	    set_c_கோவை_source_range (&கோவை, tok_range);
	    நிறுத்து;
	  }
	நிலை C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    மரம் class_name = c_parser_peek_token (parser)->மதிப்பு;
	    மரம் component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    எனில் (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		கோவை.set_error ();
		நிறுத்து;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->மதிப்பு;
	    location_t end_loc = component_tok->get_finish ();
	    c_parser_consume_token (parser);
	    கோவை.மதிப்பு = objc_build_class_component_ref (class_name,
							 component);
	    set_c_கோவை_source_range (&கோவை, loc, end_loc);
	    நிறுத்து;
	  }
	இயல்பு:
	  c_parser_error (parser, "expected expression");
	  கோவை.set_error ();
	  நிறுத்து;
	}
      நிறுத்து;
    நிலை CPP_OPEN_PAREN:
      /* A parenthesized expression, statement expression or compound
	 literal.  */
      எனில் (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_BRACE)
	{
	  /* A statement expression.  */
	  மரம் stmt;
	  location_t brace_loc;
	  தருக்க save_c_omp_array_section_p = c_omp_array_section_p;
	  c_parser_consume_token (parser);
	  brace_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* If we've not yet started the current function's statement list,
	     or we're in the parameter scope of an old-style function
	     declaration, statement expressions are not allowed.  */
	  எனில் (!building_stmt_list_p () || old_style_parameter_scope ())
	    {
	      error_at (loc, "braced-group within expression allowed "
			"only inside a function");
	      parser->error = உண்மை;
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, வெற்று);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
	      கோவை.set_error ();
	      நிறுத்து;
	    }
	  c_omp_array_section_p = பொய்;
	  stmt = c_begin_stmt_கோவை ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  கோவை.மதிப்பு = c_finish_stmt_கோவை (brace_loc, stmt);
	  set_c_கோவை_source_range (&கோவை, loc, close_loc);
	  mark_exp_read (கோவை.மதிப்பு);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      இல்லையெனில்
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  கோவை = c_parser_expression (parser);
	  எனில் (மரம்_CODE (கோவை.மதிப்பு) == MODIFY_கோவை)
	    suppress_warning (கோவை.மதிப்பு, OPT_Wparentheses);
	  எனில் (கோவை.original_code != C_MAYBE_CONST_கோவை
	      && கோவை.original_code != SIZEOF_கோவை)
	    கோவை.original_code = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  எனில் (கோவை.original_code == SIZEOF_கோவை)
	    கோவை.original_code = PAREN_SIZEOF_கோவை;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  set_c_கோவை_source_range (&கோவை, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      நிறுத்து;
    நிலை CPP_KEYWORD:
      தேர்வு (c_parser_peek_token (parser)->keyword)
	{
	நிலை RID_FUNCTION_NAME:
	நிலை RID_PRETTY_FUNCTION_NAME:
	நிலை RID_C99_FUNCTION_NAME:
	  கோவை = c_parser_predefined_identifier (parser);
	  நிறுத்து;
	நிலை RID_VA_ARG:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    எனில் (!parens.require_open (parser))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    e1 = c_parser_கோவை_no_commas (parser, வெற்று);
	    mark_exp_read (e1.மதிப்பு);
	    e1.மதிப்பு = c_fully_fold (e1.மதிப்பு, பொய், வெற்று);
	    எனில் (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    எனில் (t1 == வெற்று)
	      {
		கோவை.set_error ();
	      }
	    இல்லையெனில்
	      {
		மரம் type_கோவை = NULL_மரம்;
		மரம் type = groktypename (t1, &type_கோவை, வெற்று);
		கோவை.மதிப்பு = c_build_va_arg (start_loc, e1.மதிப்பு, loc,
					     type, type_கோவை);
		set_c_கோவை_source_range (&கோவை, start_loc, end_loc);
	      }
	  }
	  நிறுத்து;
	நிலை RID_C23_VA_START:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    எனில் (!parens.require_open (parser))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    e1 = c_parser_கோவை_no_commas (parser, வெற்று);
	    e1 = convert_lvalue_to_rvalue (e1.get_location (), e1, உண்மை, உண்மை);
	    எனில் (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		எனில் (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
		    கோவை.set_error ();
		    நிறுத்து;
		  }
		எனில் (c_parser_next_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_kind == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    மரம் name = c_parser_peek_token (parser)->மதிப்பு;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    மரம் decl = lookup_name (name);
		    மரம் last_parm
		      = மரம்_last (DECL_ARGUMENTS (current_function_decl));
		    எனில் (!last_parm || decl != last_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    இல்லையெனில் எனில் (DECL_REGISTER (decl))
		      warning_at (nloc, OPT_Wvarargs,
				  "undefined behavior when second parameter "
				  "of %<va_start%> is declared with "
				  "%<register%> storage");
		    c_parser_consume_token (parser);
		  }
		இல்லையெனில்
		  {
		    unsigned nesting_depth = 0;
		    location_t sloc = c_parser_peek_token (parser)->location;
		    location_t eloc = sloc;

		    /* For va_start (ap,) the ) comes from stdarg.h.
		       Use location of , in that case, otherwise without
		       -Wsystem-headers nothing is reported.  After all,
		       the problematic token is the comma in that case.  */
		    எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    போது (உண்மை)
		      {
			c_token *token = c_parser_peek_token (parser);
			எனில் (token->type == CPP_CLOSE_PAREN && !nesting_depth)
			  நிறுத்து;

			எனில் (token->type == CPP_EOF)
			  நிறுத்து;
			எனில் (token->type == CPP_OPEN_PAREN)
			  ++nesting_depth;
			இல்லையெனில் எனில் (token->type == CPP_CLOSE_PAREN)
			  --nesting_depth;
			eloc = token->location;
			c_parser_consume_token (parser);
		      }
		    எனில் (sloc != eloc)
		      sloc = make_location (sloc, sloc, eloc);
		    warning_at (sloc, OPT_Wvarargs,
				"%<va_start%> macro used with additional "
				"arguments other than identifier of the "
				"last named argument");
		  }
	      }
	    parens.skip_until_found_close (parser);
	    மரம் fndecl = builtin_decl_explicit (BUILT_IN_VA_START);
	    vec<மரம், va_gc> *params;
	    vec_alloc (params, 2);
	    params->quick_தள்ளு (e1.மதிப்பு);
	    params->quick_தள்ளு (integer_zero_முனை);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.quick_தள்ளு (e1.get_location ());
	    arg_loc.quick_தள்ளு (UNKNOWN_LOCATION);
	    கோவை.மதிப்பு = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, வெற்று);
	    set_c_கோவை_source_range (&கோவை, loc,
				     parser->tokens_buf[0].get_finish ());
	    கோவை.m_decimal = 0;
	    கோவை.original_code = ERROR_MARK;
	    கோவை.original_type = வெற்று;
	    release_மரம்_vector (params);
	    நிறுத்து;
	  }
	நிலை RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    எனில் (!parens.require_open (parser))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    t1 = c_parser_type_name (parser);
	    எனில் (t1 == வெற்று)
	      parser->error = உண்மை;
	    எனில் (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    எனில் (parser->error)
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    மரம் type = groktypename (t1, வெற்று, வெற்று);
	    மரம் offsetof_ref;
	    எனில் (type == error_mark_முனை)
	      offsetof_ref = error_mark_முனை;
	    இல்லையெனில்
	      {
		offsetof_ref = build1 (INDIRECT_REF, type, null_pointer_முனை);
		SET_கோவை_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    எனில் (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->மதிப்பு,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		போது (c_parser_next_token_is (parser, CPP_DOT)
		       || c_parser_next_token_is (parser,
						  CPP_OPEN_SQUARE)
		       || c_parser_next_token_is (parser,
						  CPP_DEREF))
		  {
		    எனில் (c_parser_next_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_முனை);
			செல் do_dot;
		      }
		    இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			எனில் (c_parser_next_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    நிறுத்து;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->மதிப்பு,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    இல்லையெனில்
		      {
			கட்டமைப்பு c_கோவை ce;
			மரம் idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_expression (parser);
			ce = convert_lvalue_to_rvalue (loc, ce, பொய், பொய்);
			idx = ce.மதிப்பு;
			idx = c_fully_fold (idx, பொய், வெற்று);
			c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
						   "expected %<]%>");
			offsetof_ref = build_array_ref (loc, offsetof_ref, idx);
		      }
		  }
	      }
	    இல்லையெனில்
	      c_parser_error (parser, "expected identifier");
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    கோவை.மதிப்பு = fold_offsetof (offsetof_ref);
	    set_c_கோவை_source_range (&கோவை, loc, end_loc);
	  }
	  நிறுத்து;
	நிலை RID_CHOOSE_கோவை:
	  {
	    vec<c_கோவை_t, va_gc> *cexpr_list;
	    c_கோவை_t *e1_p, *e2_p, *e3_p;
	    மரம் c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    எனில் (!c_parser_get_builtin_args (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, உண்மை,
					    &close_paren_loc))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }

	    எனில் (vec_safe_length (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		கோவை.set_error ();
		நிறுத்து;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->மதிப்பு;
	    mark_exp_read (e2_p->மதிப்பு);
	    mark_exp_read (e3_p->மதிப்பு);
	    எனில் (மரம்_CODE (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (மரம்_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_expression_warning (c);
	    கோவை = integer_zerop (c) ? *e3_p : *e2_p;
	    set_c_கோவை_source_range (&கோவை, loc, close_paren_loc);
	    நிறுத்து;
	  }
	நிலை RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    எனில் (!parens.require_open (parser))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    t1 = c_parser_type_name (parser);
	    எனில் (t1 == வெற்று)
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    t2 = c_parser_type_name (parser);
	    எனில் (t2 == வெற்று)
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    மரம் e1, e2;
	    e1 = groktypename (t1, வெற்று, வெற்று);
	    e2 = groktypename (t2, வெற்று, வெற்று);
	    எனில் (e1 == error_mark_முனை || e2 == error_mark_முனை)
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    கோவை.மதிப்பு
	      = comptypes (e1, e2) ? integer_one_முனை : integer_zero_முனை;
	    set_c_கோவை_source_range (&கோவை, loc, close_paren_loc);
	  }
	  நிறுத்து;
	நிலை RID_BUILTIN_TGMATH:
	  {
	    vec<c_கோவை_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    எனில் (!c_parser_get_builtin_args (parser,
					    "__builtin_tgmath",
					    &cexpr_list, பொய்,
					    &close_paren_loc))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }

	    எனில் (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		கோவை.set_error ();
		நிறுத்து;
	      }

	    unsigned முழு i;
	    c_கோவை_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, உண்மை, உண்மை);
	    unsigned முழு nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    எனில் (nargs == 0)
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (vec_safe_length (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		கோவை.set_error ();
		நிறுத்து;
	      }
	    unsigned முழு இலக்கம்_functions = vec_safe_length (cexpr_list) - nargs;
	    எனில் (இலக்கம்_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		கோவை.set_error ();
		நிறுத்து;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    க்கு (unsigned முழு j = 1; j < இலக்கம்_functions; j++)
	      {
		unsigned முழு this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		எனில் (this_nargs == 0)
		  {
		    கோவை.set_error ();
		    செல் out;
		  }
		எனில் (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    கோவை.set_error ();
		    செல் out;
		  }
	      }

	    /* The functions all have the same number of arguments.
	       Determine whether arguments and return types vary in
	       ways permitted for <tgmath.h> functions.  */
	    /* The first entry in each of these vectors is for the
	       return type, subsequent entries for parameter
	       types.  */
	    auto_vec<எண்ணிக்கை tgmath_parm_kind> parm_kind (nargs + 1);
	    auto_vec<மரம்> parm_first (nargs + 1);
	    auto_vec<தருக்க> parm_complex (nargs + 1);
	    auto_vec<தருக்க> parm_varies (nargs + 1);
	    மரம் first_type = மரம்_TYPE (மரம்_TYPE ((*cexpr_list)[0].மதிப்பு));
	    மரம் first_ret = TYPE_MAIN_VARIANT (மரம்_TYPE (first_type));
	    parm_first.quick_தள்ளு (first_ret);
	    parm_complex.quick_தள்ளு (மரம்_CODE (first_ret) == COMPLEX_TYPE);
	    parm_varies.quick_தள்ளு (பொய்);
	    function_args_iterator iter;
	    மரம் t;
	    unsigned முழு argpos;
	    FOREACH_FUNCTION_ARGS (first_type, t, iter)
	      {
		எனில் (t == void_type_முனை)
		  நிறுத்து;
		parm_first.quick_தள்ளு (TYPE_MAIN_VARIANT (t));
		parm_complex.quick_தள்ளு (மரம்_CODE (t) == COMPLEX_TYPE);
		parm_varies.quick_தள்ளு (பொய்);
	      }
	    க்கு (unsigned முழு j = 1; j < இலக்கம்_functions; j++)
	      {
		மரம் type = மரம்_TYPE (மரம்_TYPE ((*cexpr_list)[j].மதிப்பு));
		மரம் ret = TYPE_MAIN_VARIANT (மரம்_TYPE (type));
		எனில் (ret != parm_first[0])
		  {
		    parm_varies[0] = உண்மை;
		    எனில் (!SCALAR_FLOAT_TYPE_P (parm_first[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_first[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			கோவை.set_error ();
			செல் out;
		      }
		    எனில் (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			கோவை.set_error ();
			செல் out;
		      }
		  }
		எனில் (மரம்_CODE (ret) == COMPLEX_TYPE)
		  parm_complex[0] = உண்மை;
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    எனில் (t == void_type_முனை)
		      நிறுத்து;
		    t = TYPE_MAIN_VARIANT (t);
		    எனில் (t != parm_first[argpos])
		      {
			parm_varies[argpos] = உண்மை;
			எனில் (!SCALAR_FLOAT_TYPE_P (parm_first[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_first[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    கோவை.set_error ();
			    செல் out;
			  }
			எனில் (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    கோவை.set_error ();
			    செல் out;
			  }
		      }
		    எனில் (மரம்_CODE (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = உண்மை;
		    argpos++;
		  }
	      }
	    எண்ணிக்கை tgmath_parm_kind max_variation = tgmath_fixed;
	    க்கு (unsigned முழு j = 0; j <= nargs; j++)
	      {
		எண்ணிக்கை tgmath_parm_kind this_kind;
		எனில் (parm_varies[j])
		  {
		    எனில் (parm_complex[j])
		      max_variation = this_kind = tgmath_complex;
		    இல்லையெனில்
		      {
			this_kind = tgmath_real;
			எனில் (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		இல்லையெனில்
		  this_kind = tgmath_fixed;
		parm_kind.quick_தள்ளு (this_kind);
	      }
	    எனில் (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		கோவை.set_error ();
		நிறுத்து;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    unsigned முழு tgarg = 0;
	    க்கு (unsigned முழு j = 1; j <= nargs; j++)
	      எனில் (parm_kind[j] == max_variation)
		{
		  tgarg = j;
		  நிறுத்து;
		}
	    எனில் (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		கோவை.set_error ();
		நிறுத்து;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<மரம்> tg_type (இலக்கம்_functions);
	    க்கு (unsigned முழு j = 0; j < இலக்கம்_functions; j++)
	      {
		மரம் type = மரம்_TYPE (மரம்_TYPE ((*cexpr_list)[j].மதிப்பு));
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    எனில் (argpos == tgarg)
		      {
			tg_type.quick_தள்ளு (TYPE_MAIN_VARIANT (t));
			நிறுத்து;
		      }
		    argpos++;
		  }
	      }

	    /* Verify that the corresponding types are different for
	       all the listed functions.  Also determine whether all
	       the types are complex, whether all the types are
	       standard or binary, and whether all the types are
	       decimal.  */
	    தருக்க all_complex = உண்மை;
	    தருக்க all_இருமம் = உண்மை;
	    தருக்க all_decimal = உண்மை;
	    hash_set<மரம்> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		எனில் (மரம்_CODE (t) == COMPLEX_TYPE)
		  all_decimal = பொய்;
		இல்லையெனில்
		  {
		    all_complex = பொய்;
		    எனில் (DECIMAL_FLOAT_TYPE_P (t))
		      all_இருமம் = பொய்;
		    இல்லையெனில்
		      all_decimal = பொய்;
		  }
		எனில் (tg_types.add (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    கோவை.set_error ();
		    செல் out;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    க்கு (unsigned முழு j = 0; j < இலக்கம்_functions; j++)
	      {
		மரம் exp_type = tg_type[j];
		மரம் exp_real_type = exp_type;
		எனில் (மரம்_CODE (exp_type) == COMPLEX_TYPE)
		  exp_real_type = மரம்_TYPE (exp_type);
		மரம் type = மரம்_TYPE (மரம்_TYPE ((*cexpr_list)[j].மதிப்பு));
		மரம் ret = TYPE_MAIN_VARIANT (மரம்_TYPE (type));
		எனில் ((parm_kind[0] == tgmath_complex && ret != exp_type)
		    || (parm_kind[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    கோவை.set_error ();
		    செல் out;
		  }
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    எனில் (t == void_type_முனை)
		      நிறுத்து;
		    t = TYPE_MAIN_VARIANT (t);
		    எனில் ((parm_kind[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_kind[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			கோவை.set_error ();
			செல் out;
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
	    தருக்க arg_complex = all_complex;
	    தருக்க arg_இருமம் = all_இருமம்;
	    தருக்க arg_int_decimal = all_decimal;
	    தருக்க arg_int_floatnx = பொய்;
	    தருக்க arg_int_decimalx = பொய்;
	    க்கு (unsigned முழு j = 1; j <= nargs; j++)
	      {
		எனில் (parm_kind[j] == tgmath_fixed)
		  தொடர்;
		c_கோவை_t *ce = &(*cexpr_list)[இலக்கம்_functions + j - 1];
		மரம் type = மரம்_TYPE (ce->மதிப்பு);
		எனில் (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && மரம்_CODE (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    கோவை.set_error ();
		    செல் out;
		  }
		எனில் (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = உண்மை;
		    எனில் (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			கோவை.set_error ();
			செல் out;
		      }
		    இல்லையெனில் எனில் (all_இருமம்)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			கோவை.set_error ();
			செல் out;
		      }
		    இல்லையெனில் எனில் (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			கோவை.set_error ();
			செல் out;
		      }
		    இல்லையெனில் எனில் (arg_இருமம்)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			கோவை.set_error ();
			செல் out;
		      }
		  }
		இல்லையெனில் எனில் (மரம்_CODE (type) == COMPLEX_TYPE)
		  {
		    arg_complex = உண்மை;
		    எனில் (COMPLEX_FLOAT_TYPE_P (type))
		      arg_இருமம் = உண்மை;
		    எனில் (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			கோவை.set_error ();
			செல் out;
		      }
		    இல்லையெனில் எனில் (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			கோவை.set_error ();
			செல் out;
		      }
		  }
		இல்லையெனில் எனில் (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_இருமம் = உண்மை;
		    எனில் (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			கோவை.set_error ();
			செல் out;
		      }
		    இல்லையெனில் எனில் (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			கோவை.set_error ();
			செல் out;
		      }
		  }
		மரம் rtype = TYPE_MAIN_VARIANT (type);
		எனில் (மரம்_CODE (rtype) == COMPLEX_TYPE)
		  rtype = மரம்_TYPE (rtype);
		எனில் (SCALAR_FLOAT_TYPE_P (rtype))
		  க்கு (unsigned முழு j = 0; j < இலக்கம்_FLOATNX_TYPES; j++)
		    எனில் (rtype == FLOATNX_TYPE_முனை (j))
		      {
			arg_int_floatnx = உண்மை;
			நிறுத்து;
		      }
		எனில் (rtype == dfloat64x_type_முனை)
		  arg_int_decimalx = உண்மை;
	      }
	    மரம் arg_real = NULL_மரம்;
	    க்கு (unsigned முழு j = 1; j <= nargs; j++)
	      {
		எனில் (parm_kind[j] == tgmath_fixed)
		  தொடர்;
		c_கோவை_t *ce = &(*cexpr_list)[இலக்கம்_functions + j - 1];
		மரம் type = TYPE_MAIN_VARIANT (மரம்_TYPE (ce->மதிப்பு));
		எனில் (மரம்_CODE (type) == COMPLEX_TYPE)
		  type = மரம்_TYPE (type);
		எனில் (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_முனை
			  : arg_int_floatnx
			  ? float32x_type_முனை
			  : arg_int_decimal
			  ? dfloat64_type_முனை
			  : double_type_முனை);
		எனில் (arg_real == NULL_மரம்)
		  arg_real = type;
		இல்லையெனில்
		  arg_real = common_type (arg_real, type);
		எனில் (arg_real == error_mark_முனை)
		  {
		    கோவை.set_error ();
		    செல் out;
		  }
	      }
	    மரம் arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_கோவை_t *fn = வெற்று;
	    க்கு (unsigned முழு j = 0; j < இலக்கம்_functions; j++)
	      {
		எனில் (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    நிறுத்து;
		  }
	      }
	    எனில் (fn == வெற்று
		&& parm_kind[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_first[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		க்கு (unsigned முழு j = 0; j < இலக்கம்_functions; j++)
		  {
		    எனில் (arg_complex
			!= (மரம்_CODE (tg_type[j]) == COMPLEX_TYPE))
		      தொடர்;
		    மரம் real_tg_type = (arg_complex
					 ? மரம்_TYPE (tg_type[j])
					 : tg_type[j]);
		    எனில் (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      தொடர்;
		    scalar_float_mode arg_mode
		      = SCALAR_FLOAT_TYPE_MODE (arg_real);
		    scalar_float_mode tg_mode
		      = SCALAR_FLOAT_TYPE_MODE (real_tg_type);
		    மாறிலி real_format *arg_fmt = REAL_MODE_FORMAT (arg_mode);
		    மாறிலி real_format *tg_fmt = REAL_MODE_FORMAT (tg_mode);
		    எனில் (arg_fmt->b == tg_fmt->b
			&& arg_fmt->p <= tg_fmt->p
			&& arg_fmt->emax <= tg_fmt->emax
			&& (arg_fmt->emin - arg_fmt->p
			    >= tg_fmt->emin - tg_fmt->p))
		      {
			fn = &(*cexpr_list)[j];
			நிறுத்து;
		      }
		  }
	      }
	    எனில் (fn == வெற்று)
	      {
		error_at (loc, "no matching function for type-generic call");
		கோவை.set_error ();
		நிறுத்து;
	      }

	    /* Construct a call to FN.  */
	    vec<மரம், va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<மரம், va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    க்கு (unsigned முழு j = 0; j < nargs; j++)
	      {
		c_கோவை_t *ce = &(*cexpr_list)[இலக்கம்_functions + j];
		args->quick_தள்ளு (ce->மதிப்பு);
		arg_loc.quick_தள்ளு (ce->get_location ());
		origtypes->quick_தள்ளு (ce->original_type);
	      }
	    கோவை.மதிப்பு = c_build_function_call_vec (loc, arg_loc, fn->மதிப்பு,
						    args, origtypes);
	    set_c_கோவை_source_range (&கோவை, loc, close_paren_loc);
	    நிறுத்து;
	  }
	நிலை RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_கோவை_t, va_gc> *cexpr_list;
	    c_கோவை_t *e2_p;
	    மரம் chain_மதிப்பு;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    எனில் (!c_parser_get_builtin_args (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, பொய்,
					    &close_paren_loc))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		கோவை.set_error ();
		நிறுத்து;
	      }

	    கோவை = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, உண்மை, உண்மை);
	    chain_மதிப்பு = e2_p->மதிப்பு;
	    mark_exp_read (chain_மதிப்பு);

	    எனில் (மரம்_CODE (கோவை.மதிப்பு) != CALL_கோவை)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    இல்லையெனில் எனில் (மரம்_CODE (மரம்_TYPE (chain_மதிப்பு)) != POINTER_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    இல்லையெனில்
	      CALL_கோவை_STATIC_CHAIN (கோவை.மதிப்பு) = chain_மதிப்பு;
	    set_c_கோவை_source_range (&கோவை, loc, close_paren_loc);
	    நிறுத்து;
	  }
	நிலை RID_BUILTIN_COMPLEX:
	  {
	    vec<c_கோவை_t, va_gc> *cexpr_list;
	    c_கோவை_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    எனில் (!c_parser_get_builtin_args (parser,
					    "__builtin_complex",
					    &cexpr_list, பொய்,
					    &close_paren_loc))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }

	    எனில் (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		கோவை.set_error ();
		நிறுத்து;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_to_rvalue (loc, *e1_p, உண்மை, உண்மை);
	    எனில் (மரம்_CODE (e1_p->மதிப்பு) == EXCESS_PRECISION_கோவை)
	      e1_p->மதிப்பு = convert (மரம்_TYPE (e1_p->மதிப்பு),
				     மரம்_OPERAND (e1_p->மதிப்பு, 0));
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, உண்மை, உண்மை);
	    எனில் (மரம்_CODE (e2_p->மதிப்பு) == EXCESS_PRECISION_கோவை)
	      e2_p->மதிப்பு = convert (மரம்_TYPE (e2_p->மதிப்பு),
				     மரம்_OPERAND (e2_p->மதிப்பு, 0));
	    எனில் (!SCALAR_FLOAT_TYPE_P (மரம்_TYPE (e1_p->மதிப்பு))
		|| DECIMAL_FLOAT_TYPE_P (மரம்_TYPE (e1_p->மதிப்பு))
		|| !SCALAR_FLOAT_TYPE_P (மரம்_TYPE (e2_p->மதிப்பு))
		|| DECIMAL_FLOAT_TYPE_P (மரம்_TYPE (e2_p->மதிப்பு)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (TYPE_MAIN_VARIANT (மரம்_TYPE (e1_p->மதிப்பு))
		!= TYPE_MAIN_VARIANT (மரம்_TYPE (e2_p->மதிப்பு)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		கோவை.set_error ();
		நிறுத்து;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    கோவை.மதிப்பு = build2_loc (loc, COMPLEX_கோவை,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (மரம்_TYPE (e1_p->மதிப்பு))),
				     e1_p->மதிப்பு, e2_p->மதிப்பு);
	    set_c_கோவை_source_range (&கோவை, loc, close_paren_loc);
	    நிறுத்து;
	  }
	நிலை RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_கோவை_t, va_gc> *cexpr_list;
	    c_கோவை_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    எனில் (!c_parser_get_builtin_args (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, பொய்,
					    &close_paren_loc))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		கோவை.set_error ();
		நிறுத்து;
	      }

	    e_p = &(*cexpr_list)[0];
	    மரம் ref = e_p->மதிப்பு;

	    எனில் (மரம்_CODE (மரம்_TYPE (ref)) != ARRAY_TYPE
		 && மரம்_CODE (மரம்_TYPE (ref)) != POINTER_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		கோவை.set_error ();
		நிறுத்து;
	      }

	    எனில் (மரம்_CODE (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		கோவை.set_error ();
		நிறுத்து;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    எனில் (மரம்_CODE (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    எனில் (has_counted_by_object (ref))
	      கோவை.மதிப்பு = get_counted_by_ref (ref);
	    இல்லையெனில்
	      கோவை.மதிப்பு = null_pointer_முனை;

	    set_c_கோவை_source_range (&கோவை, loc, close_paren_loc);
	    நிறுத்து;
	  }
	நிலை RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_கோவை_t, va_gc> *cexpr_list;
	    unsigned முழு i;
	    c_கோவை_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    எனில் (!c_parser_get_builtin_args (parser,
					    "__builtin_shuffle",
					    &cexpr_list, பொய்,
					    &close_paren_loc))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, உண்மை, உண்மை);

	    எனில் (vec_safe_length (cexpr_list) == 2)
	      கோவை.மதிப்பு = c_build_vec_perm_கோவை (loc, (*cexpr_list)[0].மதிப்பு,
						  NULL_மரம்,
						  (*cexpr_list)[1].மதிப்பு);

	    இல்லையெனில் எனில் (vec_safe_length (cexpr_list) == 3)
	      கோவை.மதிப்பு = c_build_vec_perm_கோவை (loc, (*cexpr_list)[0].மதிப்பு,
						  (*cexpr_list)[1].மதிப்பு,
						  (*cexpr_list)[2].மதிப்பு);
	    இல்லையெனில்
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		கோவை.set_error ();
	      }
	    set_c_கோவை_source_range (&கோவை, loc, close_paren_loc);
	    நிறுத்து;
	  }
	நிலை RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_கோவை_t, va_gc> *cexpr_list;
	    unsigned முழு i;
	    c_கோவை_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    எனில் (!c_parser_get_builtin_args (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, பொய்,
					    &close_paren_loc))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, உண்மை, உண்மை);

	    எனில் (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		கோவை.set_error ();
	      }
	    இல்லையெனில்
	      {
		auto_vec<மரம், 16> mask;
		க்கு (i = 2; i < cexpr_list->length (); ++i)
		  mask.safe_தள்ளு ((*cexpr_list)[i].மதிப்பு);
		கோவை.மதிப்பு = c_build_shufflevector (loc, (*cexpr_list)[0].மதிப்பு,
						    (*cexpr_list)[1].மதிப்பு,
						    mask);
	      }
	    set_c_கோவை_source_range (&கோவை, loc, close_paren_loc);
	    நிறுத்து;
	  }
	நிலை RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    எனில் (!parens.require_open (parser))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    e1 = c_parser_கோவை_no_commas (parser, வெற்று);
	    mark_exp_read (e1.மதிப்பு);
	    எனில் (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    எனில் (t1 == வெற்று)
	      கோவை.set_error ();
	    இல்லையெனில்
	      {
		மரம் type_கோவை = NULL_மரம்;
		கோவை.மதிப்பு = c_build_vec_convert (start_loc, e1.மதிப்பு, loc,
						  groktypename (t1, &type_கோவை,
								வெற்று));
		set_c_கோவை_source_range (&கோவை, start_loc, end_loc);
	      }
	  }
	  நிறுத்து;
	நிலை RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    எனில் (!parens.require_open (parser))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    e1 = c_parser_கோவை_no_commas (parser, வெற்று);
	    mark_exp_read (e1.மதிப்பு);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    parens.skip_until_found_close (parser);
	    கோவை = parser_build_unary_op (loc, PAREN_கோவை, e1);
	    set_c_கோவை_source_range (&கோவை, start_loc, end_loc);
	  }
	  நிறுத்து;
	நிலை RID_BUILTIN_STDC:
	  {
	    vec<c_கோவை_t, va_gc> *cexpr_list;
	    c_கோவை_t *arg_p;
	    location_t close_paren_loc;
	    எண்ணிக்கை c_builtin_stdc {
	      C_BUILTIN_STDC_BIT_CEIL,
	      C_BUILTIN_STDC_BIT_FLOOR,
	      C_BUILTIN_STDC_BIT_WIDTH,
	      C_BUILTIN_STDC_மொத்தம்_ONES,
	      C_BUILTIN_STDC_மொத்தம்_ZEROS,
	      C_BUILTIN_STDC_FIRST_LEADING_ONE,
	      C_BUILTIN_STDC_FIRST_LEADING_ZERO,
	      C_BUILTIN_STDC_FIRST_TRAILING_ONE,
	      C_BUILTIN_STDC_FIRST_TRAILING_ZERO,
	      C_BUILTIN_STDC_HAS_SINGLE_BIT,
	      C_BUILTIN_STDC_LEADING_ONES,
	      C_BUILTIN_STDC_LEADING_ZEROS,
	      C_BUILTIN_STDC_ROTATE_இடது,
	      C_BUILTIN_STDC_ROTATE_வலது,
	      C_BUILTIN_STDC_TRAILING_ONES,
	      C_BUILTIN_STDC_TRAILING_ZEROS,
	      C_BUILTIN_STDC_MAX
	    } stdc_rid = C_BUILTIN_STDC_MAX;
	    மாறிலி எழுத்து *name
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
	    unsigned இலக்கம்_args = 1;
	    தேர்வு (name[அளவு ("__builtin_stdc_") - 1])
	      {
	      நிலை 'b':
		தேர்வு (name[அளவு ("__builtin_stdc_bit_") - 1])
		  {
		  நிலை 'c':
		    stdc_rid = C_BUILTIN_STDC_BIT_CEIL;
		    நிறுத்து;
		  நிலை 'f':
		    stdc_rid = C_BUILTIN_STDC_BIT_FLOOR;
		    நிறுத்து;
		  இயல்பு:
		    stdc_rid = C_BUILTIN_STDC_BIT_WIDTH;
		    நிறுத்து;
		  }
		நிறுத்து;
	      நிலை 'c':
		எனில் (name[அளவு ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_மொத்தம்_ONES;
		இல்லையெனில்
		  stdc_rid = C_BUILTIN_STDC_மொத்தம்_ZEROS;
		நிறுத்து;
	      நிலை 'f':
		தேர்வு (name[அளவு ("__builtin_stdc_first_trailing_") - 1])
		  {
		  நிலை 'n':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ONE;
		    நிறுத்து;
		  நிலை 'e':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ZERO;
		    நிறுத்து;
		  நிலை 'o':
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ONE;
		    நிறுத்து;
		  இயல்பு:
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ZERO;
		    நிறுத்து;
		  }
		நிறுத்து;
	      நிலை 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_BIT;
		நிறுத்து;
	      நிலை 'l':
		எனில் (name[அளவு ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		இல்லையெனில்
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		நிறுத்து;
	      நிலை 'r':
		எனில் (name[அளவு ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_இடது;
		இல்லையெனில்
		  stdc_rid = C_BUILTIN_STDC_ROTATE_வலது;
		இலக்கம்_args = 2;
		நிறுத்து;
	      நிலை 't':
		எனில் (name[அளவு ("__builtin_stdc_trailing_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ONES;
		இல்லையெனில்
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ZEROS;
		நிறுத்து;
	      }
	    gcc_checking_assert (stdc_rid != C_BUILTIN_STDC_MAX);

	    c_parser_consume_token (parser);
	    எனில் (!c_parser_get_builtin_args (parser, name,
					    &cexpr_list, பொய்,
					    &close_paren_loc))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }

	    எனில் (vec_safe_length (cexpr_list) != இலக்கம்_args)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		கோவை.set_error ();
		நிறுத்து;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, உண்மை, உண்மை);
	    எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (arg_p->மதிப்பு)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (மரம்_CODE (மரம்_TYPE (arg_p->மதிப்பு)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (மரம்_CODE (மரம்_TYPE (arg_p->மதிப்பு)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (!TYPE_UNSIGNED (மரம்_TYPE (arg_p->மதிப்பு)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (TYPE_MAIN_VARIANT (மரம்_TYPE (arg_p->மதிப்பு))
		== char_type_முனை)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    மரம் arg = arg_p->மதிப்பு;
	    மரம் type = TYPE_MAIN_VARIANT (மரம்_TYPE (arg));
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
	    முழு prec = TYPE_PRECISION (type);
	    எனில் (இலக்கம்_args == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_to_rvalue (loc, *arg_p, உண்மை, உண்மை);
		எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (arg_p->மதிப்பு)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    கோவை.set_error ();
		    நிறுத்து;
		  }
		எனில் (மரம்_CODE (மரம்_TYPE (arg_p->மதிப்பு)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    கோவை.set_error ();
		    நிறுத்து;
		  }
		மரம் arg1 = save_கோவை (arg);
		மரம் arg2 = save_கோவை (arg_p->மதிப்பு);
		மரம்_code code;
		எனில் (stdc_rid == C_BUILTIN_STDC_ROTATE_இடது)
		  code = LROTATE_கோவை;
		இல்லையெனில்
		  code = RROTATE_கோவை;

		எனில் (மரம்_CODE (arg2) == INTEGER_CST
		    && மரம்_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_மொத்தம்_negative,
			      "rotate count is negative");

		மரம் instrument_கோவை = NULL_மரம்;
		எனில் (sanitize_flags_p (SANITIZE_SHIFT))
		  instrument_கோவை = ubsan_instrument_shift (loc, code,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		எனில் (TYPE_PRECISION (மரம்_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_முனை))
		  arg2 = fold_convert (unsigned_type_முனை, arg2);

		எனில் (TYPE_UNSIGNED (மரம்_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_கோவை, மரம்_TYPE (arg2),
				     arg2, build_int_cst (மரம்_TYPE (arg2),
							  prec));
		இல்லையெனில்
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    மரம் utype = c_common_unsigned_type (மரம்_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_கோவை, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		எனில் (type_has_mode_precision_p (மரம்_TYPE (arg1))
		    || (மரம்_CODE (மரம்_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_MODE_SIZE))
		  கோவை.மதிப்பு = build2_loc (loc, code, மரம்_TYPE (arg1), arg1,
					   arg2);
		இல்லையெனில்
		  {
		    arg2 = save_கோவை (arg2);
		    மரம் t1 = build2_loc (loc, (code == LROTATE_கோவை
						? LSHIFT_கோவை : RSHIFT_கோவை),
					  மரம்_TYPE (arg1), arg1, arg2);
		    மரம் t2 = build2_loc (loc, MINUS_கோவை,
					  மரம்_TYPE (arg2),
					  build_int_cst (மரம்_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (code == LROTATE_கோவை
					   ? RSHIFT_கோவை : LSHIFT_கோவை),
				     மரம்_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_மொத்தம்_overflow);
		    மரம் t3 = build2_loc (loc, BIT_IOR_கோவை,
					  மரம்_TYPE (arg1), t1, t2);
		    மரம் t4 = build2_loc (loc, NE_கோவை, boolean_type_முனை,
					  arg2,
					  build_zero_cst (மரம்_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_கோவை, boolean_type_முனை,
				     arg1, t4);
		    கோவை.மதிப்பு = build3_loc (loc, COND_கோவை,
					     மரம்_TYPE (arg1), t4, t3, arg1);
		  }
		எனில் (instrument_கோவை)
		  கோவை.மதிப்பு = build2_loc (loc, COMPOUND_கோவை,
					   மரம்_TYPE (கோவை.மதிப்பு),
					   instrument_கோவை, கோவை.மதிப்பு);
		set_c_கோவை_source_range (&கோவை, loc, close_paren_loc);
		நிறுத்து;
	      }
	    மரம் barg1 = arg;
	    தேர்வு (stdc_rid)
	      {
	      நிலை C_BUILTIN_STDC_BIT_CEIL:
		arg = save_கோவை (arg);
		barg1 = build2_loc (loc, PLUS_கோவை, type, arg,
				    build_int_cst (type, -1));
		நிறுத்து;
	      நிலை C_BUILTIN_STDC_BIT_FLOOR:
		barg1 = arg = save_கோவை (arg);
		நிறுத்து;
	      நிலை C_BUILTIN_STDC_மொத்தம்_ZEROS:
	      நிலை C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      நிலை C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      நிலை C_BUILTIN_STDC_LEADING_ONES:
	      நிலை C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, BIT_NOT_கோவை, type, arg);
		நிறுத்து;
	      இயல்பு:
		நிறுத்து;
	      }
	    மரம் barg2 = NULL_மரம்;
	    தேர்வு (stdc_rid)
	      {
	      நிலை C_BUILTIN_STDC_BIT_WIDTH:
	      நிலை C_BUILTIN_STDC_LEADING_ONES:
	      நிலை C_BUILTIN_STDC_LEADING_ZEROS:
	      நிலை C_BUILTIN_STDC_TRAILING_ONES:
	      நிலை C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_முனை, prec);
		நிறுத்து;
	      நிலை C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      நிலை C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      நிலை C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      நிலை C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		barg2 = integer_minus_one_முனை;
		நிறுத்து;
	      இயல்பு:
		நிறுத்து;
	      }
	    மரம் fndecl = NULL_மரம்;
	    தேர்வு (stdc_rid)
	      {
	      நிலை C_BUILTIN_STDC_BIT_CEIL:
	      நிலை C_BUILTIN_STDC_BIT_FLOOR:
	      நிலை C_BUILTIN_STDC_BIT_WIDTH:
	      நிலை C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      நிலை C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      நிலை C_BUILTIN_STDC_LEADING_ONES:
	      நிலை C_BUILTIN_STDC_LEADING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CLZG);
		நிறுத்து;
	      நிலை C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      நிலை C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      நிலை C_BUILTIN_STDC_TRAILING_ONES:
	      நிலை C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CTZG);
		நிறுத்து;
	      நிலை C_BUILTIN_STDC_மொத்தம்_ONES:
	      நிலை C_BUILTIN_STDC_மொத்தம்_ZEROS:
	      நிலை C_BUILTIN_STDC_HAS_SINGLE_BIT:
		fndecl = builtin_decl_explicit (BUILT_IN_POPCOUNTG);
		நிறுத்து;
	      இயல்பு:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    முழு nargs = barg2 != NULL_மரம் ? 2 : 1;
	    vec<மரம், va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<மரம், va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    args->quick_தள்ளு (barg1);
	    arg_loc.quick_தள்ளு (arg_p->get_location ());
	    origtypes->quick_தள்ளு (arg_p->original_type);
	    எனில் (nargs == 2)
	      {
		args->quick_தள்ளு (barg2);
		arg_loc.quick_தள்ளு (loc);
		origtypes->quick_தள்ளு (integer_type_முனை);
	      }
	    கோவை.மதிப்பு = c_build_function_call_vec (loc, arg_loc, fndecl,
						    args, origtypes);
	    set_c_கோவை_source_range (&கோவை, loc, close_paren_loc);
	    எனில் (கோவை.மதிப்பு == error_mark_முனை)
	      நிறுத்து;
	    தேர்வு (stdc_rid)
	      {
	      நிலை C_BUILTIN_STDC_BIT_CEIL:
	      நிலை C_BUILTIN_STDC_BIT_FLOOR:
		--prec;
		/* FALLTHRU */
	      நிலை C_BUILTIN_STDC_BIT_WIDTH:
		கோவை.மதிப்பு = build2_loc (loc, MINUS_கோவை, integer_type_முனை,
					 build_int_cst (integer_type_முனை,
							prec), கோவை.மதிப்பு);
		நிறுத்து;
	      நிலை C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      நிலை C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      நிலை C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      நிலை C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		கோவை.மதிப்பு = build2_loc (loc, PLUS_கோவை, integer_type_முனை,
					 கோவை.மதிப்பு, integer_one_முனை);
		நிறுத்து;
	      நிலை C_BUILTIN_STDC_HAS_SINGLE_BIT:
		கோவை.மதிப்பு = build2_loc (loc, EQ_கோவை, boolean_type_முனை,
					 கோவை.மதிப்பு, integer_one_முனை);
		நிறுத்து;
	      இயல்பு:
		நிறுத்து;
	      }

	    எனில் (stdc_rid != C_BUILTIN_STDC_BIT_CEIL
		&& stdc_rid != C_BUILTIN_STDC_BIT_FLOOR)
	      {
		எனில் (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_BIT)
		  கோவை.மதிப்பு = fold_convert_loc (loc, unsigned_type_முனை,
						 கோவை.மதிப்பு);
		நிறுத்து;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    எனில் (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_BIT_CEIL && integer_onep (arg)))
	      கோவை.மதிப்பு = build_int_cst (type, 0);
	    இல்லையெனில்
	      கோவை.மதிப்பு
		= build2_loc (loc, LSHIFT_கோவை, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_BIT_CEIL
					      ? 2 : 1)), கோவை.மதிப்பு);
	    எனில் (stdc_rid == C_BUILTIN_STDC_BIT_CEIL)
	      கோவை.மதிப்பு = build3_loc (loc, COND_கோவை, type,
				       build2_loc (loc, LE_கோவை,
						   boolean_type_முனை, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       கோவை.மதிப்பு);
	    இல்லையெனில்
	      கோவை.மதிப்பு = build3_loc (loc, COND_கோவை, type,
				       build2_loc (loc, EQ_கோவை,
						   boolean_type_முனை, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       கோவை.மதிப்பு);
	    நிறுத்து;
	  }
	நிலை RID_BUILTIN_BSWAPG:
	நிலை RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_கோவை_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    internal_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    மாறிலி எழுத்து *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    எனில் (!c_parser_get_builtin_args (parser, name, &cexpr_list, பொய்,
					    &close_paren_loc))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }

	    எனில் (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		கோவை.set_error ();
		நிறுத்து;
	      }

	    c_கோவை_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, உண்மை, உண்மை);
	    மரம் arg = arg_p->மதிப்பு;
	    எனில் (error_operand_p (arg))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    மரம் type = TYPE_MAIN_VARIANT (மரம்_TYPE (arg));
	    எனில் (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (மரம்_CODE (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (மரம்_CODE (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    arg = c_fully_fold (arg, பொய், வெற்று);
	    கோவை.மதிப்பு = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    set_c_கோவை_source_range (&கோவை, loc, close_paren_loc);
	    நிறுத்து;
	  }
	நிலை RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    எனில் (!parens.require_open (parser))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    மரம் sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    கோவை.மதிப்பு = objc_build_selector_கோவை (loc, sel);
	    set_c_கோவை_source_range (&கோவை, loc, close_loc);
	  }
	  நிறுத்து;
	நிலை RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    எனில் (!parens.require_open (parser))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
		கோவை.set_error ();
		நிறுத்து;
	      }
	    மரம் id = c_parser_peek_token (parser)->மதிப்பு;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    கோவை.மதிப்பு = objc_build_protocol_கோவை (id);
	    set_c_கோவை_source_range (&கோவை, loc, close_loc);
	  }
	  நிறுத்து;
	நிலை RID_AT_ENCODE:
	  {
	    /* Extension to support C-structures in the archiver.  */
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    எனில் (!parens.require_open (parser))
	      {
		கோவை.set_error ();
		நிறுத்து;
	      }
	    t1 = c_parser_type_name (parser);
	    எனில் (t1 == வெற்று)
	      {
		கோவை.set_error ();
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
		நிறுத்து;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    மரம் type = groktypename (t1, வெற்று, வெற்று);
	    கோவை.மதிப்பு = objc_build_encode_கோவை (type);
	    set_c_கோவை_source_range (&கோவை, loc, close_loc);
	  }
	  நிறுத்து;
	நிலை RID_GENERIC:
	  கோவை = c_parser_generic_selection (parser);
	  நிறுத்து;
	நிலை RID_OMP_ALL_MEMORY:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  கோவை.set_error ();
	  நிறுத்து;
	/* C23 'nullptr' literal.  */
	நிலை RID_NULLPTR:
	  c_parser_consume_token (parser);
	  கோவை.மதிப்பு = nullptr_முனை;
	  set_c_கோவை_source_range (&கோவை, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  நிறுத்து;
	நிலை RID_TRUE:
	  c_parser_consume_token (parser);
	  கோவை.மதிப்பு = boolean_true_முனை;
	  set_c_கோவை_source_range (&கோவை, tok_range);
	  நிறுத்து;
	நிலை RID_FALSE:
	  c_parser_consume_token (parser);
	  கோவை.மதிப்பு = boolean_false_முனை;
	  set_c_கோவை_source_range (&கோவை, tok_range);
	  நிறுத்து;
	இயல்பு:
	  c_parser_error (parser, "expected expression");
	  கோவை.set_error ();
	  நிறுத்து;
	}
      நிறுத்து;
    நிலை CPP_OPEN_SQUARE:
      எனில் (c_dialect_objc ())
	{
	  மரம் receiver, args;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  args = c_parser_objc_message_args (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  கோவை.மதிப்பு = objc_build_message_கோவை (receiver, args);
	  set_c_கோவை_source_range (&கோவை, loc, close_loc);
	  நிறுத்து;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    இயல்பு:
      c_parser_error (parser, "expected expression");
      கோவை.set_error ();
      நிறுத்து;
    }
 out:
  திரும்பு c_parser_postfix_expression_after_primary
    (parser, கோவை_LOC_OR_LOC (கோவை.மதிப்பு, loc), கோவை);
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

நிலையான கட்டமைப்பு c_கோவை
c_parser_postfix_expression_after_paren_type (c_parser *parser,
					      கட்டமைப்பு c_declspecs *scspecs,
					      கட்டமைப்பு c_type_name *type_name,
					      location_t type_loc)
{
  மரம் type;
  கட்டமைப்பு c_கோவை init;
  தருக்க non_const;
  கட்டமைப்பு c_கோவை கோவை;
  location_t start_loc;
  மரம் type_கோவை = NULL_மரம்;
  தருக்க type_கோவை_const = உண்மை;
  தருக்க constexpr_p = scspecs ? scspecs->constexpr_p : பொய்;
  unsigned முழு underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (வரி_table, type_loc);
  start_loc = c_parser_peek_token (parser)->location;
  எனில் (constexpr_p)
    {
      underspec_state = start_underspecified_init (start_loc, NULL_மரம்);
      /* A constexpr compound literal is subject to the constraints on
	 underspecified declarations, which may not declare tags or
	 members or structures or unions; it is undefined behavior to
	 declare the members of an enumeration.  Where the structure,
	 union or enumeration type is declared within the compound
	 literal initializer, this is diagnosed elsewhere as a result
	 of the above call to start_underspecified_init.  Diagnose
	 here the case of declaring such a type in the type specifiers
	 of the compound literal.  */
      தேர்வு (type_name->specs->typespec_kind)
	{
	நிலை ctsk_tagfirstref:
	நிலை ctsk_tagfirstref_attrs:
	  error_at (type_loc, "%qT declared in %<constexpr%> compound literal",
		    type_name->specs->type);
	  நிறுத்து;

	நிலை ctsk_tagdef:
	  error_at (type_loc, "%qT defined in %<constexpr%> compound literal",
		    type_name->specs->type);
	  நிறுத்து;

	இயல்பு:
	  நிறுத்து;
	}
    }
  start_init (NULL_மரம், வெற்று,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_கோவை, &type_கோவை_const);
  தருக்க varsize_p = பொய்;
  எனில் (type != error_mark_முனை && C_TYPE_VARIABLE_SIZE (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = உண்மை;
    }
  இல்லையெனில் எனில் (மரம்_CODE (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_முனை;
    }
  எனில் (constexpr_p && type != error_mark_முனை)
    {
      மரம் type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      எனில் (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      இல்லையெனில் எனில் (RECORD_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, பொய், வெற்று, varsize_p);
  எனில் (constexpr_p)
    finish_underspecified_init (NULL_மரம், underspec_state);
  finish_init ();
  maybe_warn_string_init (type_loc, type, init);

  எனில் (type != error_mark_முனை
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_முனை;
    }

  எனில் (!pedwarn_c90 (start_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (start_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.மதிப்பு && மரம்_CODE (init.மதிப்பு) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.மதிப்பு)
	       : init.original_code == C_MAYBE_CONST_கோவை);
  non_const |= !type_கோவை_const;
  unsigned முழு alignas_align = 0;
  எனில் (type != error_mark_முனை
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      எனில் (alignas_align < min_align_of_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  கோவை.மதிப்பு = build_compound_literal (start_loc, type, init.மதிப்பு, non_const,
				       alignas_align, scspecs);
  set_c_கோவை_source_range (&கோவை, init.src_range);
  கோவை.m_decimal = 0;
  கோவை.original_code = ERROR_MARK;
  கோவை.original_type = வெற்று;
  எனில் (type != error_mark_முனை
      && கோவை.மதிப்பு != error_mark_முனை
      && type_கோவை)
    {
      எனில் (மரம்_CODE (கோவை.மதிப்பு) == C_MAYBE_CONST_கோவை)
	{
	  gcc_assert (C_MAYBE_CONST_கோவை_PRE (கோவை.மதிப்பு) == NULL_மரம்);
	  C_MAYBE_CONST_கோவை_PRE (கோவை.மதிப்பு) = type_கோவை;
	}
      இல்லையெனில்
	{
	  gcc_assert (!non_const);
	  கோவை.மதிப்பு = build2 (C_MAYBE_CONST_கோவை, type,
			       type_கோவை, கோவை.மதிப்பு);
	}
    }
  திரும்பு c_parser_postfix_expression_after_primary (parser, start_loc, கோவை);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

நிலையான தருக்க
sizeof_ptr_memacc_comptypes (மரம் type1, மரம் type2)
{
  திரும்பு comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

நிலையான வெறுமை
warn_for_abs (location_t loc, மரம் fndecl, மரம் arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  எனில் (c_inhibit_evaluation_warnings)
    திரும்பு;

  மரம் atype = மரம்_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  எனில் (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && மரம்_CODE (atype) != COMPLEX_TYPE)
    திரும்பு;

  எண்ணிக்கை built_in_function fcode = DECL_FUNCTION_CODE (fndecl);

  தேர்வு (fcode)
    {
    நிலை BUILT_IN_ABS:
    நிலை BUILT_IN_LABS:
    நிலை BUILT_IN_LLABS:
    நிலை BUILT_IN_IMAXABS:
      எனில் (!INTEGRAL_TYPE_P (atype))
	{
	  எனில் (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_மதிப்பு,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  இல்லையெனில் எனில் (மரம்_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_மதிப்பு,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  இல்லையெனில்
	    gcc_unreachable ();
	  திரும்பு;
	}
      எனில் (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_மதிப்பு,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      நிறுத்து;

    CASE_FLT_FN (BUILT_IN_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FABS):
      எனில் (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_MODE_P (TYPE_MODE (atype)))
	{
	  எனில் (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_மதிப்பு,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  இல்லையெனில் எனில் (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_மதிப்பு,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  இல்லையெனில் எனில் (மரம்_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_மதிப்பு,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  இல்லையெனில்
	    gcc_unreachable ();
	  திரும்பு;
	}
      நிறுத்து;

    CASE_FLT_FN (BUILT_IN_CABS):
      எனில் (மரம்_CODE (atype) != COMPLEX_TYPE)
	{
	  எனில் (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_மதிப்பு,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  இல்லையெனில் எனில் (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_மதிப்பு,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  இல்லையெனில்
	    gcc_unreachable ();

	  திரும்பு;
	}
      நிறுத்து;

    நிலை BUILT_IN_FABSD32:
    நிலை BUILT_IN_FABSD64:
    நிலை BUILT_IN_FABSD128:
    நிலை BUILT_IN_FABSD64X:
      எனில் (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  எனில் (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_மதிப்பு,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  இல்லையெனில் எனில் (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_மதிப்பு,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  இல்லையெனில் எனில் (மரம்_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_மதிப்பு,
			"using decimal floating-point absolute value "
			"function %qD when argument is of complex type %qT",
			fndecl, atype);
	  இல்லையெனில்
	    gcc_unreachable ();
	  திரும்பு;
	}
      நிறுத்து;

    இயல்பு:
      திரும்பு;
    }

  எனில் (!TYPE_ARG_TYPES (மரம்_TYPE (fndecl)))
    திரும்பு;

  மரம் ftype = மரம்_மதிப்பு (TYPE_ARG_TYPES (மரம்_TYPE (fndecl)));
  எனில் (மரம்_CODE (atype) == COMPLEX_TYPE)
    {
      gcc_assert (மரம்_CODE (ftype) == COMPLEX_TYPE);
      atype = மரம்_TYPE (atype);
      ftype = மரம்_TYPE (ftype);
    }

  எனில் (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_மதிப்பு,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

நிலையான கட்டமைப்பு c_கோவை
c_parser_postfix_expression_after_primary (c_parser *parser,
					   location_t கோவை_loc,
					   கட்டமைப்பு c_கோவை கோவை)
{
  கட்டமைப்பு c_கோவை orig_கோவை;
  மரம் ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  மரம் sizeof_arg[6];
  unsigned முழு literal_zero_mask;
  unsigned முழு i;
  vec<மரம், va_gc> *exprlist;
  vec<மரம், va_gc> *origtypes = வெற்று;
  vec<location_t> arg_loc = vNULL;
  location_t start;
  location_t finish;

  போது (உண்மை)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      தேர்வு (c_parser_peek_token (parser)->type)
	{
	நிலை CPP_OPEN_SQUARE:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_மரம்;
	  எனில் (!c_omp_array_section_p
	      || c_parser_next_token_is_not (parser, CPP_COLON))
	    idx = c_parser_expression (parser).மதிப்பு;

	  எனில் (c_omp_array_section_p
	      && c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      எனில் (c_parser_next_token_is_not (parser, CPP_CLOSE_SQUARE))
		len = c_parser_expression (parser).மதிப்பு;

	      கோவை.மதிப்பு = build_omp_array_section (op_loc, கோவை.மதிப்பு, idx,
						    len);
	    }
	  இல்லையெனில்
	    கோவை.மதிப்பு = build_array_ref (op_loc, கோவை.மதிப்பு, idx);

	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");

	  start = கோவை.get_start ();
	  finish = parser->tokens_buf[0].location;
	  set_c_கோவை_source_range (&கோவை, start, finish);
	  கோவை.original_code = ERROR_MARK;
	  கோவை.original_type = வெற்று;
	  கோவை.m_decimal = 0;
	  நிறுத்து;
	நிலை CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    க்கு (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_மரம்;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_mask = 0;
	    எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = வெற்று;
	    இல்லையெனில் எனில் (மரம்_CODE (கோவை.மதிப்பு) == FUNCTION_DECL
		     && fndecl_built_in_p (கோவை.மதிப்பு, BUILT_IN_CLASSIFY_TYPE)
		     && c_parser_next_tokens_start_typename (parser,
							     cla_prefer_id))
	      {
		/* __builtin_classify_type (type)  */
		c_inhibit_evaluation_warnings++;
		in_alignof++;
		கட்டமைப்பு c_type_name *type = c_parser_type_name (parser);
		c_inhibit_evaluation_warnings--;
		in_alignof--;
		கட்டமைப்பு c_typespec ret;
		ret.கோவை = NULL_மரம்;
		ret.spec = error_mark_முனை;
		ret.கோவை_const_operands = பொய்;
		எனில் (type != வெற்று)
		  ret.spec = groktypename (type, &ret.கோவை,
					   &ret.கோவை_const_operands);
		parens.skip_until_found_close (parser);
		கோவை.மதிப்பு = build_int_cst (integer_type_முனை,
					    type_to_class (ret.spec));
		நிறுத்து;
	      }
	    இல்லையெனில்
	      exprlist = c_parser_கோவை_list (parser, உண்மை, பொய், &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_mask);
	    parens.skip_until_found_close (parser);
	  }
	  orig_கோவை = கோவை;
	  mark_exp_read (கோவை.மதிப்பு);
	  எனில் (warn_sizeof_pointer_memaccess)
	    sizeof_pointer_memaccess_warning (sizeof_arg_loc,
					      கோவை.மதிப்பு, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  எனில் (மரம்_CODE (கோவை.மதிப்பு) == FUNCTION_DECL)
	    {
	      எனில் (fndecl_built_in_p (கோவை.மதிப்பு, BUILT_IN_MEMSET)
		  && vec_safe_length (exprlist) == 3)
		{
		  மரம் arg0 = (*exprlist)[0];
		  மரம் arg2 = (*exprlist)[2];
		  warn_for_memset (கோவை_loc, arg0, arg2, literal_zero_mask);
		}
	      எனில் (warn_absolute_மதிப்பு
		  && fndecl_built_in_p (கோவை.மதிப்பு, BUILT_IN_NORMAL)
		  && vec_safe_length (exprlist) == 1)
		warn_for_abs (கோவை_loc, கோவை.மதிப்பு, (*exprlist)[0]);
	      எனில் (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->in_intervening_code
		  && omp_runtime_api_call (கோவை.மதிப்பு))
		{
		  error_at (கோவை_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->fail = உண்மை;
		}
	      எனில் (warn_calloc_transposed_args)
		எனில் (மரம் attr = lookup_attribute ("alloc_size",
						  TYPE_ATTRIBUTES
						    (மரம்_TYPE (கோவை.மதிப்பு))))
		  எனில் (மரம்_மதிப்பு (attr) && மரம்_CHAIN (மரம்_மதிப்பு (attr)))
		    warn_for_calloc (sizeof_arg_loc, கோவை.மதிப்பு, exprlist,
				     sizeof_arg, attr);
	    }

	  start = கோவை.get_start ();
	  finish = parser->tokens_buf[0].get_finish ();
	  கோவை.மதிப்பு
	    = c_build_function_call_vec (கோவை_loc, arg_loc, கோவை.மதிப்பு,
					 exprlist, origtypes);
	  set_c_கோவை_source_range (&கோவை, start, finish);
	  கோவை.m_decimal = 0;

	  கோவை.original_code = ERROR_MARK;
	  எனில் (மரம்_CODE (கோவை.மதிப்பு) == INTEGER_CST
	      && மரம்_CODE (orig_கோவை.மதிப்பு) == FUNCTION_DECL
	      && fndecl_built_in_p (orig_கோவை.மதிப்பு, BUILT_IN_CONSTANT_P))
	    கோவை.original_code = C_MAYBE_CONST_கோவை;
	  கோவை.original_type = வெற்று;
	  எனில் (exprlist)
	    {
	      release_மரம்_vector (exprlist);
	      release_மரம்_vector (origtypes);
	    }
	  arg_loc.release ();
	  நிறுத்து;
	நிலை CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  கோவை = default_function_array_conversion (கோவை_loc, கோவை);
	  எனில் (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->மதிப்பு;
	      comp_loc = comp_tok->location;
	    }
	  இல்லையெனில்
	    {
	      c_parser_error (parser, "expected identifier");
	      கோவை.set_error ();
	      கோவை.original_code = ERROR_MARK;
              கோவை.original_type = வெற்று;
	      திரும்பு கோவை;
	    }
	  start = கோவை.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  கோவை.மதிப்பு = build_component_ref (op_loc, கோவை.மதிப்பு, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  set_c_கோவை_source_range (&கோவை, start, finish);
	  கோவை.original_code = ERROR_MARK;
	  எனில் (மரம்_CODE (கோவை.மதிப்பு) != COMPONENT_REF)
	    கோவை.original_type = வெற்று;
	  இல்லையெனில்
	    {
	      /* Remember the original type of a bitfield.  */
	      மரம் field = மரம்_OPERAND (கோவை.மதிப்பு, 1);
	      எனில் (மரம்_CODE (field) != FIELD_DECL)
		கோவை.original_type = வெற்று;
	      இல்லையெனில்
		கோவை.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  கோவை.m_decimal = 0;
	  நிறுத்து;
	நிலை CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, உண்மை, பொய்);
	  எனில் (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->மதிப்பு;
	      comp_loc = comp_tok->location;
	    }
	  இல்லையெனில்
	    {
	      c_parser_error (parser, "expected identifier");
	      கோவை.set_error ();
	      கோவை.original_code = ERROR_MARK;
	      கோவை.original_type = வெற்று;
	      திரும்பு கோவை;
	    }
	  start = கோவை.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  கோவை.மதிப்பு = build_component_ref (op_loc,
					    build_indirect_ref (op_loc,
								கோவை.மதிப்பு,
								RO_ARROW),
					    ident, comp_loc,
					    கோவை.get_location ());
	  set_c_கோவை_source_range (&கோவை, start, finish);
	  கோவை.original_code = ERROR_MARK;
	  எனில் (மரம்_CODE (கோவை.மதிப்பு) != COMPONENT_REF)
	    கோவை.original_type = வெற்று;
	  இல்லையெனில்
	    {
	      /* Remember the original type of a bitfield.  */
	      மரம் field = மரம்_OPERAND (கோவை.மதிப்பு, 1);
	      எனில் (மரம்_CODE (field) != FIELD_DECL)
		கோவை.original_type = வெற்று;
	      இல்லையெனில்
		கோவை.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  கோவை.m_decimal = 0;
	  நிறுத்து;
	நிலை CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  start = கோவை.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (கோவை.மதிப்பு);
	  கோவை = default_function_array_conversion (கோவை_loc, கோவை);
	  கோவை.மதிப்பு = build_unary_op (op_loc, POSTINCREMENT_கோவை,
				       கோவை.மதிப்பு, பொய்);
	  set_c_கோவை_source_range (&கோவை, start, finish);
	  கோவை.original_code = ERROR_MARK;
	  கோவை.original_type = வெற்று;
	  நிறுத்து;
	நிலை CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  start = கோவை.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (கோவை.மதிப்பு);
	  கோவை = default_function_array_conversion (கோவை_loc, கோவை);
	  கோவை.மதிப்பு = build_unary_op (op_loc, POSTDECREMENT_கோவை,
				       கோவை.மதிப்பு, பொய்);
	  set_c_கோவை_source_range (&கோவை, start, finish);
	  கோவை.original_code = ERROR_MARK;
	  கோவை.original_type = வெற்று;
	  நிறுத்து;
	இயல்பு:
	  திரும்பு கோவை;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

நிலையான கட்டமைப்பு c_கோவை
c_parser_expression (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  கட்டமைப்பு c_கோவை கோவை;
  கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
    கோவை = convert_lvalue_to_rvalue (tloc, கோவை, உண்மை, பொய்);
  போது (c_parser_next_token_is (parser, CPP_COMMA))
    {
      கட்டமைப்பு c_கோவை next;
      மரம் lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t கோவை_loc;
      c_parser_consume_token (parser);
      கோவை_loc = c_parser_peek_token (parser)->location;
      lhsval = கோவை.மதிப்பு;
      போது (மரம்_CODE (lhsval) == COMPOUND_கோவை
	     || மரம்_CODE (lhsval) == NOP_கோவை)
	{
	  எனில் (மரம்_CODE (lhsval) == COMPOUND_கோவை)
	    lhsval = மரம்_OPERAND (lhsval, 1);
	  இல்லையெனில்
	    lhsval = மரம்_OPERAND (lhsval, 0);
	}
      எனில் (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      எனில் (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  மரம் val = embed->மதிப்பு;
	  unsigned last = RAW_DATA_LENGTH (val) - 1;
	  next.மதிப்பு = build_int_cst (மரம்_TYPE (val),
				      RAW_DATA_UCHAR_ELT (val, last));
	  next.original_type = integer_type_முனை;
	  c_parser_consume_token (parser);
	}
      இல்லையெனில்
	{
	  next = c_parser_கோவை_no_commas (parser, வெற்று);
	  next = convert_lvalue_to_rvalue (கோவை_loc, next, உண்மை, பொய்);
	}
      கோவை.மதிப்பு = build_compound_கோவை (loc, கோவை.மதிப்பு, next.மதிப்பு);
      கோவை.original_code = COMPOUND_கோவை;
      கோவை.original_type = next.original_type;
      கோவை.m_decimal = 0;
    }
  திரும்பு கோவை;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

நிலையான கட்டமைப்பு c_கோவை
c_parser_expression_conv (c_parser *parser)
{
  கட்டமைப்பு c_கோவை கோவை;
  location_t loc = c_parser_peek_token (parser)->location;
  கோவை = c_parser_expression (parser);
  கோவை = convert_lvalue_to_rvalue (loc, கோவை, உண்மை, பொய்);
  திரும்பு கோவை;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

நிலையான உள்வரி வெறுமை
c_parser_check_literal_zero (c_parser *parser, unsigned *literal_zero_mask,
			     unsigned முழு idx)
{
  எனில் (idx >= HOST_BITS_PER_INT)
    திரும்பு;

  c_token *tok = c_parser_peek_token (parser);
  தேர்வு (tok->type)
    {
    நிலை CPP_எண்:
    நிலை CPP_CHAR:
    நிலை CPP_WCHAR:
    நிலை CPP_CHAR16:
    நிலை CPP_CHAR32:
    நிலை CPP_UTF8CHAR:
      /* If a parameter is literal zero alone, remember it
	 for -Wmemset-transposed-args warning.  */
      எனில் (integer_zerop (tok->மதிப்பு)
	  && !மரம்_OVERFLOW (tok->மதிப்பு)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_mask |= 1U << idx;
    இயல்பு:
      நிறுத்து;
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

நிலையான vec<மரம், va_gc> *
c_parser_கோவை_list (c_parser *parser, தருக்க convert_p, தருக்க fold_p,
		    vec<மரம், va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, மரம் *sizeof_arg,
		    vec<location_t> *locations,
		    unsigned முழு *literal_zero_mask)
{
  vec<மரம், va_gc> *ret;
  vec<மரம், va_gc> *orig_types;
  கட்டமைப்பு c_கோவை கோவை;
  unsigned முழு idx = 0;
  தருக்க save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = பொய்;

  ret = make_மரம்_vector ();
  எனில் (p_orig_types == வெற்று)
    orig_types = வெற்று;
  இல்லையெனில்
    orig_types = make_மரம்_vector ();

  எனில் (literal_zero_mask)
    c_parser_check_literal_zero (parser, literal_zero_mask, 0);
  கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
  எனில் (convert_p)
    கோவை = convert_lvalue_to_rvalue (கோவை.get_location (), கோவை, உண்மை, உண்மை);
  எனில் (fold_p)
    கோவை.மதிப்பு = c_fully_fold (கோவை.மதிப்பு, பொய், வெற்று);
  ret->quick_தள்ளு (கோவை.மதிப்பு);
  எனில் (orig_types)
    orig_types->quick_தள்ளு (கோவை.original_type);
  எனில் (locations)
    locations->safe_தள்ளு (கோவை.get_location ());
  எனில் (sizeof_arg != வெற்று
      && (கோவை.original_code == SIZEOF_கோவை
	  || கோவை.original_code == PAREN_SIZEOF_கோவை))
    {
      sizeof_arg[0] = c_last_sizeof_arg;
      sizeof_arg_loc[0] = c_last_sizeof_loc;
    }
  போது (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      எனில் (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  மரம் மதிப்பு = embed->மதிப்பு;
	  கோவை.original_code = INTEGER_CST;
	  கோவை.original_type = integer_type_முனை;
	  கோவை.மதிப்பு = NULL_மரம்;
	  set_c_கோவை_source_range (&கோவை, embed->get_range ());
	  கோவை.m_decimal = 0;
	  க்கு (unsigned முழு i = 0; i < (unsigned) RAW_DATA_LENGTH (மதிப்பு); i++)
	    {
	      எனில் (literal_zero_mask
		  && idx + 1 < HOST_BITS_PER_INT
		  && RAW_DATA_POINTER (மதிப்பு)[i] == 0)
		*literal_zero_mask |= 1U << (idx + 1);
	      கோவை.மதிப்பு = build_int_cst (integer_type_முனை,
					  RAW_DATA_UCHAR_ELT (மதிப்பு, i));
	      vec_safe_தள்ளு (ret, கோவை.மதிப்பு);
	      எனில் (orig_types)
		vec_safe_தள்ளு (orig_types, கோவை.original_type);
	      எனில் (locations)
		locations->safe_தள்ளு (கோவை.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  தொடர்;
	}
      எனில் (literal_zero_mask)
	c_parser_check_literal_zero (parser, literal_zero_mask, idx + 1);
      கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      எனில் (convert_p)
	கோவை = convert_lvalue_to_rvalue (கோவை.get_location (), கோவை, உண்மை,
					 உண்மை);
      எனில் (fold_p)
	கோவை.மதிப்பு = c_fully_fold (கோவை.மதிப்பு, பொய், வெற்று);
      vec_safe_தள்ளு (ret, கோவை.மதிப்பு);
      எனில் (orig_types)
	vec_safe_தள்ளு (orig_types, கோவை.original_type);
      எனில் (locations)
	locations->safe_தள்ளு (கோவை.get_location ());
      எனில் (++idx < 6
	  && sizeof_arg != வெற்று
	  && (கோவை.original_code == SIZEOF_கோவை
	      || கோவை.original_code == PAREN_SIZEOF_கோவை))
	{
	  sizeof_arg[idx] = c_last_sizeof_arg;
	  sizeof_arg_loc[idx] = c_last_sizeof_loc;
	}
    }
  எனில் (orig_types)
    *p_orig_types = orig_types;
  c_omp_array_section_p = save_c_omp_array_section_p;
  திரும்பு ret;
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

நிலையான வெறுமை
c_parser_objc_class_definition (c_parser *parser, மரம் attributes)
{
  தருக்க iface_p;
  மரம் id1;
  மரம் superclass;
  எனில் (c_parser_next_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = உண்மை;
  இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = பொய்;
  இல்லையெனில்
    gcc_unreachable ();

  c_parser_consume_token (parser);
  எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      திரும்பு;
    }
  id1 = c_parser_peek_token (parser)->மதிப்பு;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      மரம் id2;
      மரம் proto = NULL_மரம்;
      matching_parens parens;
      parens.consume_open (parser);
      எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  எனில் (iface_p && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_மரம்;
	    }
	  இல்லையெனில்
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
	      திரும்பு;
	    }
	}
      இல்லையெனில்
	{
	  id2 = c_parser_peek_token (parser)->மதிப்பு;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_found_close (parser);
      எனில் (!iface_p)
	{
	  objc_start_category_implementation (id1, id2);
	  திரும்பு;
	}
      எனில் (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_category_interface (id1, id2, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
      திரும்பு;
    }
  எனில் (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  திரும்பு;
	}
      superclass = c_parser_peek_token (parser)->மதிப்பு;
      c_parser_consume_token (parser);
    }
  இல்லையெனில்
    superclass = NULL_மரம்;
  எனில் (iface_p)
    {
      மரம் proto = NULL_மரம்;
      எனில் (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_class_interface (id1, loc1, superclass, proto, attributes);
    }
  இல்லையெனில்
    objc_start_class_implementation (id1, superclass);
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  எனில் (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
    }
  இல்லையெனில்
    {
      objc_continue_implementation ();
      திரும்பு;
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

நிலையான வெறுமை
c_parser_objc_class_instance_variables (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  போது (c_parser_next_token_is_not (parser, CPP_EOF))
    {
      மரம் decls;
      /* Parse any stray semicolon.  */
      எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  தொடர்;
	}
      /* Stop if at the end of the instance variables.  */
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  நிறுத்து;
	}
      /* Parse any objc-visibility-spec.  */
      எனில் (c_parser_next_token_is_keyword (parser, RID_AT_PRIVATE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PRIVATE);
	  தொடர்;
	}
      இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PROTECTED);
	  தொடர்;
	}
      இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_AT_PUBLIC))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PUBLIC);
	  தொடர்;
	}
      இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PACKAGE);
	  தொடர்;
	}
      இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, வெற்று, NULL_மரம்);
	  தொடர்;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser, வெற்று);
      எனில் (decls == வெற்று)
	{
	  /* There is a syntax error.  We want to skip the offending
	     tokens up to the next ';' (included) or '}'
	     (excluded).  */

	  /* First, skip manually a ')' or ']'.  This is because they
	     reduce the nesting level, so c_parser_skip_until_found()
	     wouldn't be able to skip past them.  */
	  c_token *token = c_parser_peek_token (parser);
	  எனில் (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_SQUARE)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, வெற்று);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = பொய்;
	  தொடர்;
	}
      இல்லையெனில்
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  மரம் ivar = nreverse (decls);
	  க்கு (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_add_instance_variable (copy_முனை (ivar));
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}

/* Parse an objc-class-declaration.

   objc-class-declaration:
     @class identifier-list ;
*/

நிலையான வெறுமை
c_parser_objc_class_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_CLASS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  போது (உண்மை)
    {
      மரம் id;
      எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, வெற்று);
	  parser->error = பொய்;
	  திரும்பு;
	}
      id = c_parser_peek_token (parser)->மதிப்பு;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      இல்லையெனில்
	நிறுத்து;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse an objc-alias-declaration.

   objc-alias-declaration:
     @compatibility_alias identifier identifier ;
*/

நிலையான வெறுமை
c_parser_objc_alias_declaration (c_parser *parser)
{
  மரம் id1, id2;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, வெற்று);
      திரும்பு;
    }
  id1 = c_parser_peek_token (parser)->மதிப்பு;
  c_parser_consume_token (parser);
  எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, வெற்று);
      திரும்பு;
    }
  id2 = c_parser_peek_token (parser)->மதிப்பு;
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

நிலையான வெறுமை
c_parser_objc_protocol_definition (c_parser *parser, மரம் attributes)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      திரும்பு;
    }
  எனில் (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      போது (உண்மை)
	{
	  மரம் id;
	  எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      நிறுத்து;
	    }
	  id = c_parser_peek_token (parser)->மதிப்பு;
	  objc_declare_protocol (id, attributes);
	  c_parser_consume_token (parser);
	  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  இல்லையெனில்
	    நிறுத்து;
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  இல்லையெனில்
    {
      மரம் id = c_parser_peek_token (parser)->மதிப்பு;
      மரம் proto = NULL_மரம்;
      c_parser_consume_token (parser);
      எனில் (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = உண்மை;
      objc_start_protocol (id, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      parser->objc_pq_context = பொய்;
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
நிலையான உள்வரி தருக்க
c_parser_objc_method_type (c_parser *parser)
{
  தேர்வு (c_parser_peek_token (parser)->type)
    {
    நிலை CPP_PLUS:
      c_parser_consume_token (parser);
      திரும்பு உண்மை;
    நிலை CPP_MINUS:
      c_parser_consume_token (parser);
      திரும்பு பொய்;
    இயல்பு:
      gcc_unreachable ();
    }
}

/* Parse an objc-method-definition.

   objc-method-definition:
     objc-method-type objc-method-decl ;[opt] compound-statement
*/

நிலையான வெறுமை
c_parser_objc_method_definition (c_parser *parser)
{
  தருக்க is_class_method = c_parser_objc_method_type (parser);
  மரம் decl, attributes = NULL_மரம், கோவை = NULL_மரம்;
  parser->objc_pq_context = உண்மை;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    &கோவை);
  எனில் (decl == error_mark_முனை)
    திரும்பு;  /* Bail here. */

  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  எனில் (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      திரும்பு;
    }

  parser->objc_pq_context = பொய்;
  எனில் (objc_start_method_definition (is_class_method, decl, attributes, கோவை))
    {
      add_stmt (c_parser_compound_statement (parser));
      objc_finish_method_definition (current_function_decl);
    }
  இல்லையெனில்
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

நிலையான வெறுமை
c_parser_objc_methodprotolist (c_parser *parser)
{
  போது (உண்மை)
    {
      /* The list is terminated by @end.  */
      தேர்வு (c_parser_peek_token (parser)->type)
	{
	நிலை CPP_SEMICOLON:
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  நிறுத்து;
	நிலை CPP_PLUS:
	நிலை CPP_MINUS:
	  c_parser_objc_methodproto (parser);
	  நிறுத்து;
	நிலை CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external, வெற்று, NULL_மரம்);
	  நிறுத்து;
	நிலை CPP_EOF:
	  திரும்பு;
	இயல்பு:
	  எனில் (c_parser_next_token_is_keyword (parser, RID_AT_END))
	    திரும்பு;
	  இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_set_method_opt (உண்மை);
	      c_parser_consume_token (parser);
	    }
	  இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_set_method_opt (பொய்);
	      c_parser_consume_token (parser);
	    }
	  இல்லையெனில்
	    c_parser_declaration_or_fndef (parser, பொய், பொய், உண்மை,
					   பொய், உண்மை, பொய்);
	  நிறுத்து;
	}
    }
}

/* Parse an objc-methodproto.

   objc-methodproto:
     objc-method-type objc-method-decl ;
*/

நிலையான வெறுமை
c_parser_objc_methodproto (c_parser *parser)
{
  தருக்க is_class_method = c_parser_objc_method_type (parser);
  மரம் decl, attributes = NULL_மரம்;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = உண்மை;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    வெற்று);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = பொய்;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  எனில் (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      திரும்பு;
    }

  எனில் (decl != error_mark_முனை)
    objc_add_method_declaration (is_class_method, decl, attributes);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

நிலையான தருக்க
c_parser_objc_maybe_method_attributes (c_parser* parser, மரம்* attributes)
{
  தருக்க bad = பொய்;
  எனில் (*attributes)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *attributes = NULL_மரம்;
      bad = உண்மை;
    }

  எனில் (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    *attributes = c_parser_gnu_attributes (parser);

  /* If there were no attributes here, just report any earlier error.  */
  எனில் (*attributes == NULL_மரம் || bad)
    திரும்பு bad;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    திரும்பு bad;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  திரும்பு உண்மை;
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

நிலையான மரம்
c_parser_objc_method_decl (c_parser *parser, தருக்க is_class_method,
			   மரம் *attributes, மரம் *கோவை)
{
  மரம் type = NULL_மரம்;
  மரம் sel;
  மரம் parms = NULL_மரம்;
  தருக்க ellipsis = பொய்;
  தருக்க attr_err = பொய்;

  *attributes = NULL_மரம்;
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
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
  எனில் (!sel || c_parser_next_token_is (parser, CPP_COLON))
    {
      மரம் tsel = sel;
      மரம் list = NULL_மரம்;
      போது (உண்மை)
	{
	  மரம் atype = NULL_மரம், id, keyworddecl;
	  மரம் param_attr = NULL_மரம்;
	  எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    நிறுத்து;
	  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  எனில் (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_attributes (parser);
	  எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      திரும்பு error_mark_முனை;
	    }
	  id = c_parser_peek_token (parser)->மதிப்பு;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  எனில் (!tsel && c_parser_next_token_is_not (parser, CPP_COLON))
	    நிறுத்து;
	}

      attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_முனை (மரம்_LIST);
      போது (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  கட்டமைப்பு c_parm *parm;
	  c_parser_consume_token (parser);
	  எனில் (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = உண்மை;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_method_attributes
						(parser, attributes) ;
	      நிறுத்து;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_மரம், பொய்);
	  எனில் (parm == வெற்று)
	    நிறுத்து;
	  parms = chainon (parms,
			   build_மரம்_list (NULL_மரம், grokparm (parm, கோவை)));
	}
      sel = list;
    }
  இல்லையெனில்
    attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

  எனில் (sel == வெற்று)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      திரும்பு error_mark_முனை;
    }

  எனில் (attr_err)
    திரும்பு error_mark_முனை;

  திரும்பு objc_build_method_signature (is_class_method, type, sel, parms, ellipsis);
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

நிலையான மரம்
c_parser_objc_type_name (c_parser *parser)
{
  மரம் quals = NULL_மரம்;
  கட்டமைப்பு c_type_name *type_name = வெற்று;
  மரம் type = NULL_மரம்;
  போது (உண்மை)
    {
      c_token *token = c_parser_peek_token (parser);
      எனில் (token->type == CPP_KEYWORD
	  && (token->keyword == RID_IN
	      || token->keyword == RID_OUT
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_மரம்_list (NULL_மரம், token->மதிப்பு), quals);
	  c_parser_consume_token (parser);
	}
      இல்லையெனில்
	நிறுத்து;
    }
  எனில் (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  எனில் (type_name)
    type = groktypename (type_name, வெற்று, வெற்று);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  எனில் (type == error_mark_முனை)
    type = NULL_மரம்;

  திரும்பு build_மரம்_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

நிலையான மரம்
c_parser_objc_protocol_refs (c_parser *parser)
{
  மரம் list = NULL_மரம்;
  gcc_assert (c_parser_next_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  போது (உண்மை)
    {
      மரம் id;
      எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  நிறுத்து;
	}
      id = c_parser_peek_token (parser)->மதிப்பு;
      list = chainon (list, build_மரம்_list (NULL_மரம், id));
      c_parser_consume_token (parser);
      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      இல்லையெனில்
	நிறுத்து;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  திரும்பு list;
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

நிலையான வெறுமை
c_parser_objc_try_catch_finally_statement (c_parser *parser)
{
  location_t location;
  மரம் stmt;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  போது (c_parser_next_token_is_keyword (parser, RID_AT_CATCH))
    {
      கட்டமைப்பு c_parm *parm;
      மரம் parameter_declaration = error_mark_முனை;
      தருக்க seen_open_paren = பொய்;

      c_parser_consume_token (parser);
      matching_parens parens;
      எனில் (!parens.require_open (parser))
	seen_open_paren = உண்மை;
      எனில் (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_மரம்;
	}
      இல்லையெனில்
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_மரம், பொய்);
	  எனில் (parm == வெற்று)
	    parameter_declaration = error_mark_முனை;
	  இல்லையெனில்
	    parameter_declaration = grokparm (parm, வெற்று);
	}
      எனில் (seen_open_paren)
	parens.require_close (parser);
      இல்லையெனில்
	{
	  /* If there was no open parenthesis, we are recovering from
	     an error, and we are trying to figure out what mistake
	     the user has made.  */

	  /* If there is an immediate closing parenthesis, the user
	     probably forgot the opening one (ie, they typed "@catch
	     NSException *e)".  Parse the closing parenthesis and keep
	     going.  */
	  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      எனில் (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_finish_catch_clause ();
    }
  எனில் (c_parser_next_token_is_keyword (parser, RID_AT_FINALLY))
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

நிலையான வெறுமை
c_parser_objc_synchronized_statement (c_parser *parser)
{
  location_t loc;
  மரம் கோவை, stmt;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      கட்டமைப்பு c_கோவை ce = c_parser_expression (parser);
      ce = convert_lvalue_to_rvalue (loc, ce, பொய், பொய்);
      கோவை = ce.மதிப்பு;
      கோவை = c_fully_fold (கோவை, பொய், வெற்று);
      parens.skip_until_found_close (parser);
    }
  இல்லையெனில்
    கோவை = error_mark_முனை;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, கோவை, stmt);
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

நிலையான மரம்
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  மரம் மதிப்பு = token->மதிப்பு;
  எனில் (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      திரும்பு மதிப்பு;
    }
  எனில் (token->type != CPP_KEYWORD)
    திரும்பு NULL_மரம்;
  தேர்வு (token->keyword)
    {
    நிலை RID_ENUM:
    நிலை RID_STRUCT:
    நிலை RID_UNION:
    நிலை RID_IF:
    நிலை RID_ELSE:
    நிலை RID_WHILE:
    நிலை RID_DO:
    நிலை RID_FOR:
    நிலை RID_SWITCH:
    நிலை RID_CASE:
    நிலை RID_DEFAULT:
    நிலை RID_BREAK:
    நிலை RID_CONTINUE:
    நிலை RID_RETURN:
    நிலை RID_GOTO:
    நிலை RID_ASM:
    நிலை RID_SIZEOF:
    நிலை RID_TYPEOF:
    நிலை RID_TYPEOF_UNQUAL:
    நிலை RID_ALIGNOF:
    நிலை RID_UNSIGNED:
    நிலை RID_LONG:
    நிலை RID_CONST:
    நிலை RID_SHORT:
    நிலை RID_VOLATILE:
    நிலை RID_SIGNED:
    நிலை RID_RESTRICT:
    நிலை RID_COMPLEX:
    நிலை RID_IN:
    நிலை RID_OUT:
    நிலை RID_INOUT:
    நிலை RID_BYCOPY:
    நிலை RID_BYREF:
    நிலை RID_ONEWAY:
    நிலை RID_INT:
    நிலை RID_CHAR:
    நிலை RID_FLOAT:
    நிலை RID_DOUBLE:
    CASE_RID_FLOATN_NX:
    நிலை RID_VOID:
    நிலை RID_BOOL:
    நிலை RID_ATOMIC:
    நிலை RID_AUTO_TYPE:
    நிலை RID_INT_N_0:
    நிலை RID_INT_N_1:
    நிலை RID_INT_N_2:
    நிலை RID_INT_N_3:
      c_parser_consume_token (parser);
      திரும்பு மதிப்பு;
    இயல்பு:
      திரும்பு NULL_மரம்;
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

நிலையான மரம்
c_parser_objc_selector_arg (c_parser *parser)
{
  மரம் sel = c_parser_objc_selector (parser);
  மரம் list = NULL_மரம்;
  எனில் (sel
      && c_parser_next_token_is_not (parser, CPP_COLON)
      && c_parser_next_token_is_not (parser, CPP_SCOPE))
    திரும்பு sel;
  போது (உண்மை)
    {
      எனில் (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_மரம்_list (sel, NULL_மரம்));
	  list = chainon (list, build_மரம்_list (NULL_மரம், NULL_மரம்));
	}
      இல்லையெனில்
	{
	  எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    திரும்பு list;
	  list = chainon (list, build_மரம்_list (sel, NULL_மரம்));
	}
      sel = c_parser_objc_selector (parser);
      எனில் (!sel
	  && c_parser_next_token_is_not (parser, CPP_COLON)
	  && c_parser_next_token_is_not (parser, CPP_SCOPE))
	நிறுத்து;
    }
  திரும்பு list;
}

/* Parse an objc-receiver.

   objc-receiver:
     expression
     class-name
     type-name
*/

நிலையான மரம்
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  எனில் (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
    {
      மரம் id = c_parser_peek_token (parser)->மதிப்பு;
      c_parser_consume_token (parser);
      திரும்பு objc_get_class_reference (id);
    }
  கட்டமைப்பு c_கோவை ce = c_parser_expression (parser);
  ce = convert_lvalue_to_rvalue (loc, ce, பொய், பொய்);
  திரும்பு c_fully_fold (ce.மதிப்பு, பொய், வெற்று);
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

நிலையான மரம்
c_parser_objc_message_args (c_parser *parser)
{
  மரம் sel = c_parser_objc_selector (parser);
  மரம் list = NULL_மரம்;
  எனில் (sel && c_parser_next_token_is_not (parser, CPP_COLON))
    திரும்பு sel;
  போது (உண்மை)
    {
      மரம் keywordexpr;
      எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	திரும்பு error_mark_முனை;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_மரம்_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      எனில் (!sel && c_parser_next_token_is_not (parser, CPP_COLON))
	நிறுத்து;
    }
  திரும்பு list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

நிலையான மரம்
c_parser_objc_keywordexpr (c_parser *parser)
{
  மரம் ret;
  vec<மரம், va_gc> *கோவை_list = c_parser_கோவை_list (parser, உண்மை, உண்மை,
						வெற்று, வெற்று, வெற்று, வெற்று);
  எனில் (vec_safe_length (கோவை_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*கோவை_list)[0];
    }
  இல்லையெனில்
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_மரம்_list_vec (கோவை_list);
    }
  release_மரம்_vector (கோவை_list);
  திரும்பு ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
நிலையான தருக்க
c_parser_objc_diagnose_bad_element_prefix (c_parser *parser,
					   கட்டமைப்பு c_declspecs *specs)
{
  எனில் (!specs->declspecs_seen_p || specs->non_sc_seen_p
      || specs->typespec_kind != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_to_end_of_block_or_statement (parser);
      திரும்பு உண்மை;
    }
  திரும்பு பொய்;
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
நிலையான வெறுமை
c_parser_objc_at_property_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY));
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);  /* Eat '@property'.  */

  /* Parse the optional attribute list.

     A list of parsed, but not verified, attributes.  */
  vec<property_attribute_info *> prop_attr_list = vNULL;

  தருக்க syntax_error = பொய்;
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_start = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = உண்மை;

      /* Allow @property (), with a warning.  */
      location_t attr_end = c_parser_peek_token (parser)->location;

      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_end, attr_start, attr_end);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      இல்லையெனில்
	போது (உண்மை)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_start = token->location;
	    attr_end = get_finish (token->location);
	    location_t attr_comb = make_location (attr_start, attr_start,
						  attr_end);

	    எனில் (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		எனில் (token->type == CPP_CLOSE_PAREN)
		  நிறுத்து;
		c_parser_consume_token (parser);
		தொடர்;
	      }

	    மரம் attr_name = NULL_மரம்;
	    எண்ணிக்கை rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    தருக்க add_at = பொய்;
	    எனில் (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		எனில் (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->மதிப்பு;
		    add_at = உண்மை;
		  }
		இல்லையெனில்
		  attr_name = ridpointers[(முழு)keyword];
	      }
	    இல்லையெனில் எனில் (token->type == CPP_NAME)
	      attr_name = token->மதிப்பு;
	    c_parser_consume_token (parser);

	    எண்ணிக்கை objc_property_attribute_kind prop_kind
	      = objc_prop_attr_kind_for_rid (keyword);
	    property_attribute_info *prop
	      = புதிய property_attribute_info (attr_name, attr_comb, prop_kind);
	    prop_attr_list.safe_தள்ளு (prop);

	    மரம் meth_name;
	    தேர்வு (prop->prop_kind)
	      {
	      இயல்பு: நிறுத்து;
	      நிலை OBJC_PROPERTY_ATTR_UNKNOWN:
		எனில் (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    add_at ? "@" : "", IDENTIFIER_POINTER (attr_name));
		இல்லையெனில்
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = உண்மை;
		நிறுத்து;

	      நிலை OBJC_PROPERTY_ATTR_GETTER:
	      நிலை OBJC_PROPERTY_ATTR_SETTER:
		எனில் (c_parser_next_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = உண்மை;
		    நிறுத்து;
		  }
		token = c_parser_peek_token (parser);
		attr_end = token->location;
		c_parser_consume_token (parser); /* eat the = */
		எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = உண்மை;
		    நிறுத்து;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_end = get_finish (token->location);
		meth_name = token->மதிப்பு;
		c_parser_consume_token (parser);
		எனில் (prop->prop_kind == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    எனில் (c_parser_next_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_end, attr_start,
						   attr_end);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = உண்மை;
		      }
		    இல்லையெனில்
		      {
			attr_end = get_finish (c_parser_peek_token
					       (parser)->location);
			c_parser_consume_token (parser);
		      }
		    attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		  }
		இல்லையெனில்
		  attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		prop->ident = meth_name;
		/* Updated location including all that was successfully
		   parsed.  */
		prop->prop_loc = attr_comb;
		நிறுத்து;
	    }

	  /* If we see a comma here, then keep going - even if we already
	     saw a syntax error.  For simple mistakes e.g. (assign, getter=x)
	     this makes a more useful output and avoid spurious warnings about
	     missing attributes that are, in fact, specified after the one with
	     the syntax error.  */
	  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  இல்லையெனில்
	    நிறுத்து;
	}
      parser->objc_property_attr_context = பொய்;

      எனில் (syntax_error && c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      இல்லையெனில்
	syntax_error = பொய், parens.skip_until_found_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  மரம் properties = c_parser_struct_declaration (parser, வெற்று);

  எனில் (properties == error_mark_முனை)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, வெற்று);
  இல்லையெனில்
    {
      எனில் (properties == NULL_மரம்)
	c_parser_error (parser, "expected identifier");
      இல்லையெனில்
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  க்கு (; properties; properties = மரம்_CHAIN (properties))
	    objc_add_property_declaration (loc, copy_முனை (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  போது (!prop_attr_list.is_empty())
    delete prop_attr_list.எடு ();
  prop_attr_list.release ();
  parser->error = பொய்;
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
நிலையான வெறுமை
c_parser_objc_at_synthesize_declaration (c_parser *parser)
{
  மரம் list = NULL_மரம்;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  போது (உண்மை)
    {
      மரம் property, ivar;
      எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, வெற்று);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = பொய்;
	  திரும்பு;
	}
      property = c_parser_peek_token (parser)->மதிப்பு;
      c_parser_consume_token (parser);
      எனில் (c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_SEMICOLON, வெற்று);
	      parser->error = பொய்;
	      திரும்பு;
	    }
	  ivar = c_parser_peek_token (parser)->மதிப்பு;
	  c_parser_consume_token (parser);
	}
      இல்லையெனில்
	ivar = NULL_மரம்;
      list = chainon (list, build_மரம்_list (ivar, property));
      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      இல்லையெனில்
	நிறுத்து;
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
நிலையான வெறுமை
c_parser_objc_at_dynamic_declaration (c_parser *parser)
{
  மரம் list = NULL_மரம்;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  போது (உண்மை)
    {
      மரம் property;
      எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, வெற்று);
	  parser->error = பொய்;
	  திரும்பு;
	}
      property = c_parser_peek_token (parser)->மதிப்பு;
      list = chainon (list, build_மரம்_list (NULL_மரம், property));
      c_parser_consume_token (parser);
      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      இல்லையெனில்
	நிறுத்து;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_add_dynamic_declaration (loc, list);
}


/* Parse a pragma GCC ivdep.  */

நிலையான தருக்க
c_parse_pragma_ivdep (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  திரும்பு உண்மை;
}

/* Parse a pragma GCC novector.  */

நிலையான தருக்க
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  திரும்பு உண்மை;
}

/* Parse a pragma GCC unroll.  */

நிலையான unsigned short
c_parser_pragma_unroll (c_parser *parser)
{
  unsigned short unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  மரம் கோவை = c_parser_கோவை_no_commas (parser, வெற்று).மதிப்பு;
  mark_exp_read (கோவை);
  கோவை = c_fully_fold (கோவை, பொய், வெற்று);
  HOST_WIDE_INT lunroll = 0;
  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (கோவை))
      || மரம்_CODE (கோவை) != INTEGER_CST
      || (lunroll = மரம்_to_shwi (கோவை)) < 0
      || lunroll >= USHRT_MAX)
    {
      error_at (location, "%<#pragma GCC unroll%> requires an"
		" assignment-expression that evaluates to a non-negative"
		" integral constant less than %u", USHRT_MAX);
      unroll = 0;
    }
  இல்லையெனில்
    {
      unroll = (unsigned short)lunroll;
      எனில் (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_to_pragma_eol (parser);
  திரும்பு unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

நிலையான தருக்க
c_parser_pragma (c_parser *parser, எண்ணிக்கை pragma_context context, தருக்க *if_p,
		 மரம் before_labels)
{
  unsigned முழு id;
  மாறிலி எழுத்து *construct = வெற்று;

  உள்ளீடு_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_kind;
  gcc_assert (id != PRAGMA_NONE);
  எனில் (parser->omp_for_parse_state
      && parser->omp_for_parse_state->in_intervening_code
      && id >= PRAGMA_OMP__START_ && id <= PRAGMA_OMP__LAST_
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	உள்ளீடு_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->fail = உண்மை;
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, வெற்று);
      திரும்பு பொய்;
    }

  தேர்வு (id)
    {
    நிலை PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OACC_ENTER_DATA:
      எனில் (context != pragma_compound)
	{
	  construct = "acc enter data";
	in_compound:
	  எனில் (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, வெற்று);
	      திரும்பு உண்மை;
	    }
	  செல் bad_stmt;
	}
      c_parser_oacc_enter_exit_data (parser, உண்மை);
      திரும்பு பொய்;

    நிலை PRAGMA_OACC_EXIT_DATA:
      எனில் (context != pragma_compound)
	{
	  construct = "acc exit data";
	  செல் in_compound;
	}
      c_parser_oacc_enter_exit_data (parser, பொய்);
      திரும்பு பொய்;

    நிலை PRAGMA_OACC_ROUTINE:
      எனில் (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, வெற்று);
	  திரும்பு பொய்;
	}
      c_parser_oacc_routine (parser, context);
      திரும்பு பொய்;

    நிலை PRAGMA_OACC_UPDATE:
      எனில் (context != pragma_compound)
	{
	  construct = "acc update";
	  செல் in_compound;
	}
      c_parser_oacc_update (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_BARRIER:
      எனில் (context != pragma_compound)
	{
	  construct = "omp barrier";
	  செல் in_compound;
	}
      c_parser_omp_barrier (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_DEPOBJ:
      எனில் (context != pragma_compound)
	{
	  construct = "omp depobj";
	  செல் in_compound;
	}
      c_parser_omp_depobj (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_FLUSH:
      எனில் (context != pragma_compound)
	{
	  construct = "omp flush";
	  செல் in_compound;
	}
      c_parser_omp_flush (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_INTEROP:
      எனில் (context != pragma_compound)
	{
	  construct = "omp interop";
	  செல் in_compound;
	}
      c_parser_omp_interop (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_TASKWAIT:
      எனில் (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  செல் in_compound;
	}
      c_parser_omp_taskwait (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_TASKYIELD:
      எனில் (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  செல் in_compound;
	}
      c_parser_omp_taskyield (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_CANCEL:
      எனில் (context != pragma_compound)
	{
	  construct = "omp cancel";
	  செல் in_compound;
	}
      c_parser_omp_cancel (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_CANCELLATION_POINT:
      திரும்பு c_parser_omp_cancellation_point (parser, context);

    நிலை PRAGMA_OMP_GROUPPRIVATE:
      c_parser_omp_groupprivate (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_THREADPRIVATE:
      c_parser_omp_threadprivate (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_TARGET:
      திரும்பு c_parser_omp_target (parser, context, if_p);

    நிலை PRAGMA_OMP_BEGIN:
      c_parser_omp_begin (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_END:
      c_parser_omp_end (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_SCAN:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, வெற்று);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, வெற்று);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_DECLARE:
      திரும்பு c_parser_omp_declare (parser, context);

    நிலை PRAGMA_OMP_REQUIRES:
      எனில் (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, வெற்று);
	  திரும்பு பொய்;
	}
      c_parser_omp_requires (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_ALLOCATE:
      c_parser_omp_allocate (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_ASSUMES:
      எனில் (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp assumes");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, வெற்று);
	  திரும்பு பொய்;
	}
      c_parser_omp_assumes (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      திரும்பு பொய்;

    நிலை PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      திரும்பு உண்மை;

    நிலை PRAGMA_OMP_ERROR:
      திரும்பு c_parser_omp_error (parser, context);

    நிலை PRAGMA_OMP_ORDERED:
      திரும்பு c_parser_omp_ordered (parser, context, if_p);

    நிலை PRAGMA_NOVECTOR:
    நிலை PRAGMA_UNROLL:
    நிலை PRAGMA_IVDEP:
      {
	தருக்க novector = பொய்;
	unsigned short unroll = 0;
	தருக்க ivdep = பொய்;

	தேர்வு (id)
	  {
	  நிலை PRAGMA_NOVECTOR:
	    novector = c_parse_pragma_novector (parser);
	    நிறுத்து;
	  நிலை PRAGMA_UNROLL:
	    unroll = c_parser_pragma_unroll (parser);
	    நிறுத்து;
	  நிலை PRAGMA_IVDEP:
	    ivdep = c_parse_pragma_ivdep (parser);
	    நிறுத்து;
	  இயல்பு:
	    gcc_unreachable ();
	  }

	c_token *tok = c_parser_peek_token (parser);
	தருக்க has_more = tok->type == CPP_PRAGMA;
	போது (has_more)
	  {
	    தேர்வு (tok->pragma_kind)
	      {
	      நிலை PRAGMA_IVDEP:
		ivdep = c_parse_pragma_ivdep (parser);
		நிறுத்து;
	      நிலை PRAGMA_UNROLL:
		unroll = c_parser_pragma_unroll (parser);
		நிறுத்து;
	      நிலை PRAGMA_NOVECTOR:
		novector = c_parse_pragma_novector (parser);
		நிறுத்து;
	      இயல்பு:
		has_more = பொய்;
		நிறுத்து;
	      }
	    tok = c_parser_peek_token (parser);
	    has_more = has_more && tok->type == CPP_PRAGMA;
	  }
	எனில் (!c_parser_next_token_is_keyword (parser, RID_FOR)
	    && !c_parser_next_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_next_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    திரும்பு பொய்;
	  }
	எனில் (c_parser_next_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	இல்லையெனில்
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      திரும்பு உண்மை;

    நிலை PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, வெற்று);
      திரும்பு பொய்;

    நிலை PRAGMA_OACC_WAIT:
      எனில் (context != pragma_compound)
	{
	  construct = "acc wait";
	  செல் in_compound;
	}
	/* FALL THROUGH.  */

    இயல்பு:
      எனில் (id < PRAGMA_FIRST_EXTERNAL)
	{
	  எனில் (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, வெற்று);
	      திரும்பு பொய்;
	    }
	  c_parser_omp_construct (parser, if_p);
	  திரும்பு உண்மை;
	}
      நிறுத்து;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = உண்மை;
  c_parser_skip_to_pragma_eol (parser);

  திரும்பு பொய்;
}

/* The interface the pragma parsers have to the lexer.  */

எண்ணிக்கை cpp_ttype
pragma_lex (மரம் *மதிப்பு, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  எண்ணிக்கை cpp_ttype ret = tok->type;

  *மதிப்பு = tok->மதிப்பு;
  எனில் (loc)
    *loc = tok->location;

  எனில் (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  இல்லையெனில் எனில் (ret == CPP_STRING)
    *மதிப்பு = c_parser_string_literal (the_parser, பொய், பொய்).மதிப்பு;
  இல்லையெனில்
    {
      எனில் (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  திரும்பு ret;
}

வெறுமை
pragma_lex_discard_to_eol ()
{
  cpp_ttype type;
  செய்
    {
      type = c_parser_peek_token (the_parser)->type;
      gcc_assert (type != CPP_EOF);
      c_parser_consume_token (the_parser);
    } போது (type != CPP_PRAGMA_EOL);
}

நிலையான வெறுமை
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  மரம் name = வெற்று;

  parser->lex_joined_string = உண்மை;
  c_parser_consume_pragma (parser);
  எனில் (c_parser_next_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->மதிப்பு;
      c_parser_consume_token (parser);
    }
  இல்லையெனில்
    c_parser_error (parser, "expected string literal");
  c_parser_skip_to_pragma_eol (parser);
  parser->lex_joined_string = பொய்;

  எனில் (name)
    c_common_pch_pragma (parse_in, மரம்_STRING_POINTER (name));
}

/* OpenACC and OpenMP parsing routines.  */

/* Returns name of the next clause.
   If the clause is not recognized PRAGMA_OMP_CLAUSE_NONE is returned and
   the token is not consumed.  Otherwise appropriate pragma_omp_clause is
   returned and the token is consumed.  */

நிலையான pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause result = PRAGMA_OMP_CLAUSE_NONE;

  எனில் (c_parser_next_token_is_keyword (parser, RID_AUTO))
    result = PRAGMA_OACC_CLAUSE_AUTO;
  இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_IF))
    result = PRAGMA_OMP_CLAUSE_IF;
  இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    result = PRAGMA_OMP_CLAUSE_DEFAULT;
  இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_FOR))
    result = PRAGMA_OMP_CLAUSE_FOR;
  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);

      தேர்வு (p[0])
	{
	நிலை 'a':
	  எனில் (!strcmp ("affinity", p))
	    result = PRAGMA_OMP_CLAUSE_AFFINITY;
	  இல்லையெனில் எனில் (!strcmp ("aligned", p))
	    result = PRAGMA_OMP_CLAUSE_ALIGNED;
	  இல்லையெனில் எனில் (!strcmp ("allocate", p))
	    result = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  இல்லையெனில் எனில் (!strcmp ("async", p))
	    result = PRAGMA_OACC_CLAUSE_ASYNC;
	  இல்லையெனில் எனில் (!strcmp ("attach", p))
	    result = PRAGMA_OACC_CLAUSE_ATTACH;
	  நிறுத்து;
	நிலை 'b':
	  எனில் (!strcmp ("bind", p))
	    result = PRAGMA_OMP_CLAUSE_BIND;
	  நிறுத்து;
	நிலை 'c':
	  எனில் (!strcmp ("collapse", p))
	    result = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  இல்லையெனில் எனில் (!strcmp ("copy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  இல்லையெனில் எனில் (!strcmp ("copyin", p))
	    result = PRAGMA_OMP_CLAUSE_COPYIN;
	  இல்லையெனில் எனில் (!strcmp ("copyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
          இல்லையெனில் எனில் (!strcmp ("copyprivate", p))
	    result = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  இல்லையெனில் எனில் (!strcmp ("create", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  நிறுத்து;
	நிலை 'd':
	  எனில் (!strcmp ("defaultmap", p))
	    result = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  இல்லையெனில் எனில் (!strcmp ("delete", p))
	    result = PRAGMA_OACC_CLAUSE_DELETE;
	  இல்லையெனில் எனில் (!strcmp ("depend", p))
	    result = PRAGMA_OMP_CLAUSE_DEPEND;
	  இல்லையெனில் எனில் (!strcmp ("destroy", p))
	    result = PRAGMA_OMP_CLAUSE_DESTROY;
	  இல்லையெனில் எனில் (!strcmp ("detach", p))
	    result = PRAGMA_OACC_CLAUSE_DETACH;
	  இல்லையெனில் எனில் (!strcmp ("device", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE;
	  இல்லையெனில் எனில் (!strcmp ("deviceptr", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  இல்லையெனில் எனில் (!strcmp ("device_resident", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  இல்லையெனில் எனில் (!strcmp ("device_type", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  இல்லையெனில் எனில் (!strcmp ("dist_schedule", p))
	    result = PRAGMA_OMP_CLAUSE_DIST_SCHEDULE;
	  இல்லையெனில் எனில் (!strcmp ("doacross", p))
	    result = PRAGMA_OMP_CLAUSE_DOACROSS;
	  இல்லையெனில் எனில் (!strcmp ("dyn_groupprivate", p))
	    result = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  நிறுத்து;
	நிலை 'e':
	  எனில் (!strcmp ("enter", p))
	    result = PRAGMA_OMP_CLAUSE_ENTER;
	  நிறுத்து;
	நிலை 'f':
	  எனில் (!strcmp ("filter", p))
	    result = PRAGMA_OMP_CLAUSE_FILTER;
	  இல்லையெனில் எனில் (!strcmp ("final", p))
	    result = PRAGMA_OMP_CLAUSE_FINAL;
	  இல்லையெனில் எனில் (!strcmp ("finalize", p))
	    result = PRAGMA_OACC_CLAUSE_FINALIZE;
	  இல்லையெனில் எனில் (!strcmp ("firstprivate", p))
	    result = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  இல்லையெனில் எனில் (!strcmp ("from", p))
	    result = PRAGMA_OMP_CLAUSE_FROM;
	  இல்லையெனில் எனில் (!strcmp ("full", p))
	    result = PRAGMA_OMP_CLAUSE_FULL;
	  நிறுத்து;
	நிலை 'g':
	  எனில் (!strcmp ("gang", p))
	    result = PRAGMA_OACC_CLAUSE_GANG;
	  இல்லையெனில் எனில் (!strcmp ("grainsize", p))
	    result = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  நிறுத்து;
	நிலை 'h':
	  எனில் (!strcmp ("has_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  இல்லையெனில் எனில் (!strcmp ("hint", p))
	    result = PRAGMA_OMP_CLAUSE_HINT;
	  இல்லையெனில் எனில் (!strcmp ("host", p))
	    result = PRAGMA_OACC_CLAUSE_HOST;
	  நிறுத்து;
	நிலை 'i':
	  எனில் (!strcmp ("if_present", p))
	    result = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  இல்லையெனில் எனில் (!strcmp ("in_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_IN_REDUCTION;
	  இல்லையெனில் எனில் (!strcmp ("inbranch", p))
	    result = PRAGMA_OMP_CLAUSE_INBRANCH;
	  இல்லையெனில் எனில் (!strcmp ("independent", p))
	    result = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  இல்லையெனில் எனில் (!strcmp ("indirect", p))
	    result = PRAGMA_OMP_CLAUSE_INDIRECT;
	  இல்லையெனில் எனில் (!strcmp ("init", p))
	    result = PRAGMA_OMP_CLAUSE_INIT;
	  இல்லையெனில் எனில் (!strcmp ("is_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  இல்லையெனில் எனில் (!strcmp ("interop", p))
	    result = PRAGMA_OMP_CLAUSE_INTEROP;
	  நிறுத்து;
	நிலை 'l':
	  எனில் (!strcmp ("lastprivate", p))
	    result = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  இல்லையெனில் எனில் (!strcmp ("linear", p))
	    result = PRAGMA_OMP_CLAUSE_LINEAR;
	  இல்லையெனில் எனில் (!strcmp ("link", p))
	    result = PRAGMA_OMP_CLAUSE_LINK;
	  இல்லையெனில் எனில் (!strcmp ("local", p))
	    result = PRAGMA_OMP_CLAUSE_LOCAL;
	  நிறுத்து;
	நிலை 'm':
	  எனில் (!strcmp ("map", p))
	    result = PRAGMA_OMP_CLAUSE_MAP;
	  இல்லையெனில் எனில் (!strcmp ("mergeable", p))
	    result = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  நிறுத்து;
	நிலை 'n':
	  எனில் (!strcmp ("no_create", p))
	    result = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  இல்லையெனில் எனில் (!strcmp ("nocontext", p))
	    result = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  இல்லையெனில் எனில் (!strcmp ("nogroup", p))
	    result = PRAGMA_OMP_CLAUSE_NOGROUP;
	  இல்லையெனில் எனில் (!strcmp ("nohost", p))
	    result = PRAGMA_OACC_CLAUSE_NOHOST;
	  இல்லையெனில் எனில் (!strcmp ("nontemporal", p))
	    result = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  இல்லையெனில் எனில் (!strcmp ("notinbranch", p))
	    result = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  இல்லையெனில் எனில் (!strcmp ("novariants", p))
	    result = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  இல்லையெனில் எனில் (!strcmp ("nowait", p))
	    result = PRAGMA_OMP_CLAUSE_NOWAIT;
	  இல்லையெனில் எனில் (!strcmp ("num_gangs", p))
	    result = PRAGMA_OACC_CLAUSE_இலக்கம்_GANGS;
	  இல்லையெனில் எனில் (!strcmp ("num_tasks", p))
	    result = PRAGMA_OMP_CLAUSE_இலக்கம்_TASKS;
	  இல்லையெனில் எனில் (!strcmp ("num_teams", p))
	    result = PRAGMA_OMP_CLAUSE_இலக்கம்_TEAMS;
	  இல்லையெனில் எனில் (!strcmp ("num_threads", p))
	    result = PRAGMA_OMP_CLAUSE_இலக்கம்_THREADS;
	  இல்லையெனில் எனில் (!strcmp ("num_workers", p))
	    result = PRAGMA_OACC_CLAUSE_இலக்கம்_WORKERS;
	  நிறுத்து;
	நிலை 'o':
	  எனில் (!strcmp ("ordered", p))
	    result = PRAGMA_OMP_CLAUSE_ORDERED;
	  இல்லையெனில் எனில் (!strcmp ("order", p))
	    result = PRAGMA_OMP_CLAUSE_ORDER;
	  நிறுத்து;
	நிலை 'p':
	  எனில் (!strcmp ("parallel", p))
	    result = PRAGMA_OMP_CLAUSE_PARALLEL;
	  இல்லையெனில் எனில் (!strcmp ("partial", p))
	    result = PRAGMA_OMP_CLAUSE_PARTIAL;
	  இல்லையெனில் எனில் (!strcmp ("present", p))
	    result = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  இல்லையெனில் எனில் (!strcmp ("present_or_copy", p)
		   || !strcmp ("pcopy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  இல்லையெனில் எனில் (!strcmp ("present_or_copyin", p)
		   || !strcmp ("pcopyin", p))
	    result = PRAGMA_OACC_CLAUSE_COPYIN;
	  இல்லையெனில் எனில் (!strcmp ("present_or_copyout", p)
		   || !strcmp ("pcopyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
	  இல்லையெனில் எனில் (!strcmp ("present_or_create", p)
		   || !strcmp ("pcreate", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  இல்லையெனில் எனில் (!strcmp ("priority", p))
	    result = PRAGMA_OMP_CLAUSE_PRIORITY;
	  இல்லையெனில் எனில் (!strcmp ("private", p))
	    result = PRAGMA_OMP_CLAUSE_PRIVATE;
	  இல்லையெனில் எனில் (!strcmp ("proc_bind", p))
	    result = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  நிறுத்து;
	நிலை 'r':
	  எனில் (!strcmp ("reduction", p))
	    result = PRAGMA_OMP_CLAUSE_REDUCTION;
	  நிறுத்து;
	நிலை 's':
	  எனில் (!strcmp ("safelen", p))
	    result = PRAGMA_OMP_CLAUSE_SAFELEN;
	  இல்லையெனில் எனில் (!strcmp ("schedule", p))
	    result = PRAGMA_OMP_CLAUSE_SCHEDULE;
	  இல்லையெனில் எனில் (!strcmp ("sections", p))
	    result = PRAGMA_OMP_CLAUSE_SECTIONS;
	  இல்லையெனில் எனில் (!strcmp ("self", p))
	    result = PRAGMA_OACC_CLAUSE_SELF;
	  இல்லையெனில் எனில் (!strcmp ("seq", p))
	    result = PRAGMA_OACC_CLAUSE_SEQ;
	  இல்லையெனில் எனில் (!strcmp ("shared", p))
	    result = PRAGMA_OMP_CLAUSE_SHARED;
	  இல்லையெனில் எனில் (!strcmp ("simd", p))
	    result = PRAGMA_OMP_CLAUSE_SIMD;
	  இல்லையெனில் எனில் (!strcmp ("simdlen", p))
	    result = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  நிறுத்து;
	நிலை 't':
	  எனில் (!strcmp ("task_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  இல்லையெனில் எனில் (!strcmp ("taskgroup", p))
	    result = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  இல்லையெனில் எனில் (!strcmp ("thread_limit", p))
	    result = PRAGMA_OMP_CLAUSE_THREAD_LIMIT;
	  இல்லையெனில் எனில் (!strcmp ("threads", p))
	    result = PRAGMA_OMP_CLAUSE_THREADS;
	  இல்லையெனில் எனில் (!strcmp ("tile", p))
	    result = PRAGMA_OACC_CLAUSE_TILE;
	  இல்லையெனில் எனில் (!strcmp ("to", p))
	    result = PRAGMA_OMP_CLAUSE_TO;
	  நிறுத்து;
	நிலை 'u':
	  எனில் (!strcmp ("uniform", p))
	    result = PRAGMA_OMP_CLAUSE_UNIFORM;
	  இல்லையெனில் எனில் (!strcmp ("untied", p))
	    result = PRAGMA_OMP_CLAUSE_UNTIED;
	  இல்லையெனில் எனில் (!strcmp ("use", p))
	    result = PRAGMA_OMP_CLAUSE_USE;
	  இல்லையெனில் எனில் (!strcmp ("use_device", p))
	    result = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  இல்லையெனில் எனில் (!strcmp ("use_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  இல்லையெனில் எனில் (!strcmp ("use_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  இல்லையெனில் எனில் (!strcmp ("uses_allocators", p))
	    result = PRAGMA_OMP_CLAUSE_USES_ALLOCATORS;
	  நிறுத்து;
	நிலை 'v':
	  எனில் (!strcmp ("vector", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR;
	  இல்லையெனில் எனில் (!strcmp ("vector_length", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR_LENGTH;
	  நிறுத்து;
	நிலை 'w':
	  எனில் (!strcmp ("wait", p))
	    result = PRAGMA_OACC_CLAUSE_WAIT;
	  இல்லையெனில் எனில் (!strcmp ("worker", p))
	    result = PRAGMA_OACC_CLAUSE_WORKER;
	  நிறுத்து;
	}
    }

  எனில் (result != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  திரும்பு result;
}

/* Validate that a clause of the given type does not already exist.  */

நிலையான வெறுமை
check_no_duplicate_clause (மரம் clauses, எண்ணிக்கை omp_clause_code code,
			   மாறிலி எழுத்து *name)
{
  எனில் (மரம் c = omp_find_clause (clauses, code))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

நிலையான மரம்
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, மரம் list)
{
  vec<மரம், va_gc> *args;
  மரம் t, args_மரம்;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  args = c_parser_கோவை_list (parser, பொய், உண்மை, வெற்று, வெற்று, வெற்று, வெற்று);
  args_மரம் = build_மரம்_list_vec (args);

  க்கு (t = args_மரம்; t; t = மரம்_CHAIN (t))
    {
      மரம் targ = மரம்_மதிப்பு (t);

      எனில் (targ != error_mark_முனை)
	{
	  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_முனை;
	    }
	  இல்லையெனில்
	    {
	      மரம் c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_மரம்_vector (args);
  parens.require_close (parser);
  திரும்பு list;
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

கட்டமைப்பு omp_dim
{
  மரம் கீழ்_bound, length;
  location_t loc;
  தருக்க no_colon;
  omp_dim (மரம் lb, மரம் len, location_t lo, தருக்க nc)
  : கீழ்_bound (lb), length (len), loc (lo), no_colon (nc) {}
};

நிலையான மரம்
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    எண்ணிக்கை omp_clause_code kind, மரம் list,
			    தருக்க map_lvalue = பொய்)
{
  auto_vec<omp_dim> dims;
  தருக்க array_section_p;
  auto_vec<c_token> tokens;
  unsigned முழு tokens_avail = 0;
  c_token *saved_tokens = வெற்று;

  போது (1)
    {
      மரம் t = NULL_மரம்;
      location_t tloc = c_parser_peek_token (parser)->location;

      எனில் (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  எனில் (c_parser_next_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
	    {
	      கட்டமைப்பு c_கோவை கோவை;
	      எனில் (kind == OMP_CLAUSE_DEPEND
		  && c_parser_next_token_is_keyword (parser,
						     RID_OMP_ALL_MEMORY)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  கோவை.மதிப்பு = ridpointers[RID_OMP_ALL_MEMORY];
		  c_parser_consume_token (parser);
		}
	      இல்லையெனில்
		கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	      எனில் (கோவை.மதிப்பு != error_mark_முனை)
		{
		  மரம் u = build_omp_clause (clause_loc, kind);
		  OMP_CLAUSE_DECL (u) = கோவை.மதிப்பு;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      எனில் (c_parser_next_token_is_not (parser, CPP_COMMA))
		நிறுத்து;

	      c_parser_consume_token (parser);
	      தொடர்;
	    }

	  tokens.truncate (0);
	  unsigned முழு nesting_depth = 0;
	  போது (1)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      தேர்வு (token->type)
		{
		நிலை CPP_EOF:
		நிலை CPP_PRAGMA_EOL:
		  நிறுத்து;
		நிலை CPP_OPEN_BRACE:
		நிலை CPP_OPEN_PAREN:
		நிலை CPP_OPEN_SQUARE:
		  ++nesting_depth;
		  செல் add;
		நிலை CPP_CLOSE_BRACE:
		நிலை CPP_CLOSE_PAREN:
		நிலை CPP_CLOSE_SQUARE:
		  எனில் (nesting_depth-- == 0)
		    நிறுத்து;
		  செல் add;
		நிலை CPP_COMMA:
		  எனில் (nesting_depth == 0)
		    நிறுத்து;
		  செல் add;
		இயல்பு:
		add:
		  tokens.safe_தள்ளு (*token);
		  c_parser_consume_token (parser);
		  தொடர்;
		}
	      நிறுத்து;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  memset (&eof_token, 0, அளவு (eof_token));
	  eof_token.type = CPP_EOF;
	  tokens.safe_தள்ளு (eof_token);
	  tokens.safe_தள்ளு (eof_token);

	  saved_tokens = parser->tokens;
	  tokens_avail = parser->tokens_avail;
	  parser->tokens = tokens.address ();
	  parser->tokens_avail = tokens.length ();
	}
      இல்லையெனில் எனில் (map_lvalue
	       && (kind == OMP_CLAUSE_MAP
		   || kind == OMP_CLAUSE_TO
		   || kind == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  தருக்க save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = உண்மை;
	  c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	  எனில் (கோவை.மதிப்பு != error_mark_முனை)
	    mark_exp_read (கோவை.மதிப்பு);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  மரம் decl = கோவை.மதிப்பு;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  எனில் (மரம்_CODE (decl) == OMP_ARRAY_SECTION)
	    {
	      போது (மரம்_CODE (decl) == OMP_ARRAY_SECTION)
		{
		  மரம் கீழ்_bound = மரம்_OPERAND (decl, 1);
		  மரம் length = மரம்_OPERAND (decl, 2);
		  dims.safe_தள்ளு (omp_dim (கீழ்_bound, length, loc, பொய்));
		  decl = மரம்_OPERAND (decl, 0);
		}

	      போது (மரம்_CODE (decl) == ARRAY_REF
		     || மரம்_CODE (decl) == INDIRECT_REF
		     || மரம்_CODE (decl) == COMPOUND_கோவை)
		{
		  எனில் (மரம்_CODE (decl) == COMPOUND_கோவை)
		    {
		      decl = மரம்_OPERAND (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  இல்லையெனில் எனில் (மரம்_CODE (decl) == INDIRECT_REF)
		    {
		      dims.safe_தள்ளு (omp_dim (integer_zero_முனை,
					       integer_one_முனை, loc, உண்மை));
		      decl = மரம்_OPERAND (decl, 0);
		    }
		  இல்லையெனில்  /* ARRAY_REF. */
		    {
		      மரம் index = மரம்_OPERAND (decl, 1);
		      dims.safe_தள்ளு (omp_dim (index, integer_one_முனை, loc,
					       உண்மை));
		      decl = மரம்_OPERAND (decl, 0);
		    }
		}

	      க்கு (முழு i = dims.length () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].கீழ்_bound,
						dims[i].length);
	    }
	  இல்லையெனில் எனில் (மரம்_CODE (decl) == INDIRECT_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = மரம்_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_முனை,
					      integer_one_முனை);
	    }
	  இல்லையெனில் எனில் (மரம்_CODE (decl) == ARRAY_REF)
	    {
	      மரம் idx = மரம்_OPERAND (decl, 1);

	      decl = மரம்_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_முனை);
	    }
	  இல்லையெனில் எனில் (மரம்_CODE (decl) == NON_LVALUE_கோவை
		   || CONVERT_கோவை_P (decl))
	    decl = மரம்_OPERAND (decl, 0);

	  மரம் u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  செல் next_item;
	}

      எனில் (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->மதிப்பு);

	  எனில் (t == NULL_மரம்)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->மதிப்பு);
	      t = error_mark_முனை;
	    }

	  c_parser_consume_token (parser);
	}
      இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).மதிப்பு;
      இல்லையெனில்
	{
	  c_parser_error (parser, "expected identifier");
	  நிறுத்து;
	}

      எனில் (t == error_mark_முனை)
	;
      இல்லையெனில் எனில் (kind != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  தேர்வு (kind)
	    {
	    நிலை OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      எனில் (c_parser_peek_token (parser)->type != CPP_OPEN_SQUARE)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_முனை;
		  நிறுத்து;
		}
	      /* FALLTHROUGH  */
	    நிலை OMP_CLAUSE_MAP:
	    நிலை OMP_CLAUSE_FROM:
	    நிலை OMP_CLAUSE_TO:
	    start_component_ref:
	      போது (c_parser_next_token_is (parser, CPP_DOT)
		     || c_parser_next_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  எனில் (c_parser_next_token_is (parser, CPP_DEREF))
		    {
		      c_கோவை t_கோவை;
		      t_கோவை.மதிப்பு = t;
		      t_கோவை.original_code = ERROR_MARK;
		      t_கோவை.original_type = வெற்று;
		      set_c_கோவை_source_range (&t_கோவை, op_loc, op_loc);
		      t_கோவை.m_decimal = 0;
		      t_கோவை = convert_lvalue_to_rvalue (op_loc, t_கோவை,
							 உண்மை, பொய்);
		      t = build_indirect_ref (op_loc, t_கோவை.மதிப்பு, RO_ARROW);
		      arrow_loc = t_கோவை.get_location ();
		    }
		  c_parser_consume_token (parser);
		  எனில் (!c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_முனை;
		      நிறுத்து;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  மரம் ident = comp_tok->மதிப்பு;
		  location_t comp_loc = comp_tok->location;
		  c_parser_consume_token (parser);
		  t = build_component_ref (op_loc, t, ident, comp_loc,
					   arrow_loc);
		}
	      /* FALLTHROUGH  */
	    நிலை OMP_CLAUSE_AFFINITY:
	    நிலை OMP_CLAUSE_DEPEND:
	    நிலை OMP_CLAUSE_REDUCTION:
	    நிலை OMP_CLAUSE_IN_REDUCTION:
	    நிலை OMP_CLAUSE_TASK_REDUCTION:
	    நிலை OMP_CLAUSE_HAS_DEVICE_ADDR:
	      array_section_p = பொய்;
	      dims.truncate (0);
	      போது (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  மரம் கீழ்_bound = NULL_மரம், length = NULL_மரம்;
		  தருக்க no_colon = பொய்;

		  c_parser_consume_token (parser);
		  எனில் (!c_parser_next_token_is (parser, CPP_COLON))
		    {
		      location_t கோவை_loc
			= c_parser_peek_token (parser)->location;
		      c_கோவை கோவை = c_parser_expression (parser);
		      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை,
						       பொய், உண்மை);
		      கீழ்_bound = கோவை.மதிப்பு;
		      loc = கோவை_loc;
		    }
		  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    {
		      length = integer_one_முனை;
		      no_colon = உண்மை;
		    }
		  இல்லையெனில்
		    {
		      /* Look for `:'.  */
		      எனில் (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_முனை;
			  நிறுத்து;
			}
		      array_section_p = உண்மை;
		      எனில் (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
			{
			  location_t கோவை_loc
			    = c_parser_peek_token (parser)->location;
			  c_கோவை கோவை = c_parser_expression (parser);
			  கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை,
							   பொய், உண்மை);
			  length = கோவை.மதிப்பு;
			}
		    }
		  /* Look for the closing `]'.  */
		  எனில் (!c_parser_require (parser, CPP_CLOSE_SQUARE,
					 "expected %<]%>"))
		    {
		      t = error_mark_முனை;
		      நிறுத்து;
		    }

		  dims.safe_தள்ளு (omp_dim (கீழ்_bound, length, loc, no_colon));
		}

	      எனில் (t != error_mark_முனை)
		{
		  எனில் ((kind == OMP_CLAUSE_MAP
		       || kind == OMP_CLAUSE_FROM
		       || kind == OMP_CLAUSE_TO)
		      && !array_section_p
		      && (c_parser_next_token_is (parser, CPP_DOT)
			  || c_parser_next_token_is (parser, CPP_DEREF)))
		    {
		      க்கு (unsigned i = 0; i < dims.length (); i++)
			{
			  gcc_assert (dims[i].length == integer_one_முனை);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].கீழ்_bound);
			}
		      செல் start_component_ref;
		    }
		  இல்லையெனில்
		    க்கு (unsigned i = 0; i < dims.length (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].கீழ்_bound,
						   dims[i].length);
		}

	      எனில் ((kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_முனை
		  && parser->tokens_avail != 2)
		{
		  எனில் (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_முனை;
		    }
		  இல்லையெனில்
		    {
		      parser->tokens = tokens.address ();
		      parser->tokens_avail = tokens.length ();

		      t = c_parser_கோவை_no_commas (parser, வெற்று).மதிப்பு;
		      எனில் (t != error_mark_முனை && parser->tokens_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_முனை;
			}
		    }
		}
	      நிறுத்து;
	    இயல்பு:
	      நிறுத்து;
	    }

	  எனில் (t != error_mark_முனை)
	    {
	      மரம் u = build_omp_clause (clause_loc, kind);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      இல்லையெனில்  /* kind == OMP_CLAUSE_ERROR */
	list = மரம்_cons (t, build_empty_stmt (tloc), list);

      எனில் (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}

    next_item:
      எனில் (c_parser_next_token_is_not (parser, CPP_COMMA))
	நிறுத்து;

      c_parser_consume_token (parser);
    }

  திரும்பு list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

நிலையான மரம்
c_parser_omp_var_list_parens (c_parser *parser, எண்ணிக்கை omp_clause_code kind,
			      மரம் list, தருக்க map_lvalue = பொய்)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  எனில் (parser->in_omp_decl_attribute)
    {
      எனில் (kind)
	{
	  மரம் u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = parser->in_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  திரும்பு u;
	}
      இல்லையெனில்
	திரும்பு மரம்_cons (parser->in_omp_decl_attribute, NULL_மரம், list);
    }

  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, kind, list, map_lvalue);
      parens.skip_until_found_close (parser);
    }
  திரும்பு list;
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

நிலையான மரம்
c_parser_oacc_data_clause (c_parser *parser, pragma_omp_clause c_kind,
			   மரம் list)
{
  எண்ணிக்கை gomp_map_kind kind;
  தேர்வு (c_kind)
    {
    நிலை PRAGMA_OACC_CLAUSE_ATTACH:
      kind = GOMP_MAP_ATTACH;
      நிறுத்து;
    நிலை PRAGMA_OACC_CLAUSE_COPY:
      kind = GOMP_MAP_TOFROM;
      நிறுத்து;
    நிலை PRAGMA_OACC_CLAUSE_COPYIN:
      kind = GOMP_MAP_TO;
      நிறுத்து;
    நிலை PRAGMA_OACC_CLAUSE_COPYOUT:
      kind = GOMP_MAP_FROM;
      நிறுத்து;
    நிலை PRAGMA_OACC_CLAUSE_CREATE:
      kind = GOMP_MAP_ALLOC;
      நிறுத்து;
    நிலை PRAGMA_OACC_CLAUSE_DELETE:
      kind = GOMP_MAP_RELEASE;
      நிறுத்து;
    நிலை PRAGMA_OACC_CLAUSE_DETACH:
      kind = GOMP_MAP_DETACH;
      நிறுத்து;
    நிலை PRAGMA_OACC_CLAUSE_DEVICE:
      kind = GOMP_MAP_FORCE_TO;
      நிறுத்து;
    நிலை PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      kind = GOMP_MAP_DEVICE_RESIDENT;
      நிறுத்து;
    நிலை PRAGMA_OACC_CLAUSE_LINK:
      kind = GOMP_MAP_LINK;
      நிறுத்து;
    நிலை PRAGMA_OACC_CLAUSE_NO_CREATE:
      kind = GOMP_MAP_IF_PRESENT;
      நிறுத்து;
    நிலை PRAGMA_OACC_CLAUSE_PRESENT:
      kind = GOMP_MAP_FORCE_PRESENT;
      நிறுத்து;
    நிலை PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    நிலை PRAGMA_OACC_CLAUSE_HOST:
      kind = GOMP_MAP_FORCE_FROM;
      நிறுத்து;
    இயல்பு:
      gcc_unreachable ();
    }

  மரம் nl = list;
  தருக்க readonly = பொய்;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      எனில் (c_kind == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  எனில் (token->type == CPP_NAME
	      && !strcmp (IDENTIFIER_POINTER (token->மதிப்பு), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = உண்மை;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       பொய்);
      parens.skip_until_found_close (parser);
    }

  க்கு (மரம் c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      எனில் (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  திரும்பு nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

நிலையான மரம்
c_parser_oacc_data_clause_deviceptr (c_parser *parser, மரம் list)
{
  மரம் vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, வெற்று);
  க்கு (t = vars; t && t; t = மரம்_CHAIN (t))
    {
      மரம் v = மரம்_PURPOSE (t);
      location_t loc = கோவை_LOCATION (மரம்_மதிப்பு (t));

      எனில் (!VAR_P (v) && மரம்_CODE (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      இல்லையெனில் எனில் (மரம்_TYPE (v) == error_mark_முனை)
	;
      இல்லையெனில் எனில் (!POINTER_TYPE_P (மரம்_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      மரம் u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  திரும்பு list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

நிலையான மரம்
c_parser_omp_clause_collapse (c_parser *parser, மரம் list)
{
  மரம் c, இலக்கம் = error_mark_முனை;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      இலக்கம் = c_parser_கோவை_no_commas (parser, வெற்று).மதிப்பு;
      parens.skip_until_found_close (parser);
    }
  எனில் (இலக்கம் == error_mark_முனை)
    திரும்பு list;
  mark_exp_read (இலக்கம்);
  இலக்கம் = c_fully_fold (இலக்கம், பொய், வெற்று);
  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (இலக்கம்))
      || !மரம்_fits_shwi_p (இலக்கம்)
      || (n = மரம்_to_shwi (இலக்கம்)) <= 0
      || (முழு) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      திரும்பு list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_கோவை (c) = இலக்கம்;
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

நிலையான மரம்
c_parser_omp_clause_copyin (c_parser *parser, மரம் list)
{
  திரும்பு c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

நிலையான மரம்
c_parser_omp_clause_copyprivate (c_parser *parser, மரம் list)
{
  திரும்பு c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

நிலையான மரம்
c_parser_omp_clause_default (c_parser *parser, மரம் list, தருக்க is_oacc)
{
  எண்ணிக்கை omp_clause_default_kind kind = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  மரம் c;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;
  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);

      தேர்வு (p[0])
	{
	நிலை 'n':
	  எனில் (strcmp ("none", p) != 0)
	    செல் invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_NONE;
	  நிறுத்து;

	நிலை 'p':
	  எனில் (is_oacc)
	    {
	      எனில் (strcmp ("present", p) != 0)
		செல் invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  இல்லையெனில்
	    {
	      எனில் (strcmp ("private", p) != 0)
		செல் invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRIVATE;
	    }
	  நிறுத்து;

	நிலை 'f':
	  எனில் (strcmp ("firstprivate", p) != 0 || is_oacc)
	    செல் invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  நிறுத்து;

	நிலை 's':
	  எனில் (strcmp ("shared", p) != 0 || is_oacc)
	    செல் invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_SHARED;
	  நிறுத்து;

	இயல்பு:
	  செல் invalid_kind;
	}

      c_parser_consume_token (parser);
    }
  இல்லையெனில்
    {
    invalid_kind:
      எனில் (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      இல்லையெனில்
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_found_close (parser);

  எனில் (kind == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    திரும்பு list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_KIND (c) = kind;

  திரும்பு c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

நிலையான மரம்
c_parser_omp_clause_firstprivate (c_parser *parser, மரம் list)
{
  திரும்பு c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

நிலையான மரம்
c_parser_omp_clause_final (c_parser *parser, மரம் list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      மரம் t, c;
      எனில் (!parens.require_open (parser))
	t = error_mark_முனை;
      இல்லையெனில்
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	  t = convert_lvalue_to_rvalue (eloc, கோவை, உண்மை, உண்மை).மதிப்பு;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, பொய், வெற்று);
	  parens.skip_until_found_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_கோவை (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }
  இல்லையெனில்
    c_parser_error (parser, "expected %<(%>");

  திரும்பு list;
}

/* OpenMP 5.1:
   indirect [( expression )]
*/

நிலையான மரம்
c_parser_omp_clause_indirect (c_parser *parser, மரம் list)
{
  location_t location = c_parser_peek_token (parser)->location;
  மரம் t;

  எனில் (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      எனில் (!parens.require_open (parser))
	திரும்பு list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (loc, கோவை, உண்மை, உண்மை);
      t = c_objc_common_truthvalue_conversion (loc, கோவை.மதிப்பு);
      t = c_fully_fold (t, பொய், வெற்று);
      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (t))
	  || மரம்_CODE (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  திரும்பு list;
	}
      parens.skip_until_found_close (parser);
    }
  இல்லையெனில்
    t = integer_one_முனை;

  check_no_duplicate_clause (list, OMP_CLAUSE_INDIRECT, "indirect");

  மரம் c = build_omp_clause (location, OMP_CLAUSE_INDIRECT);
  OMP_CLAUSE_INDIRECT_கோவை (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;

  திரும்பு c;
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

நிலையான மரம்
c_parser_omp_clause_if (c_parser *parser, மரம் list, தருக்க is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  எண்ணிக்கை மரம்_code if_modifier = ERROR_MARK;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  எனில் (is_omp && c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      முழு n = 2;
      எனில் (strcmp (p, "cancel") == 0)
	if_modifier = VOID_CST;
      இல்லையெனில் எனில் (strcmp (p, "parallel") == 0)
	if_modifier = OMP_PARALLEL;
      இல்லையெனில் எனில் (strcmp (p, "simd") == 0)
	if_modifier = OMP_SIMD;
      இல்லையெனில் எனில் (strcmp (p, "task") == 0)
	if_modifier = OMP_TASK;
      இல்லையெனில் எனில் (strcmp (p, "taskloop") == 0)
	if_modifier = OMP_TASKLOOP;
      இல்லையெனில் எனில் (strcmp (p, "target") == 0)
	{
	  if_modifier = OMP_TARGET;
	  எனில் (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	    {
	      p = IDENTIFIER_POINTER (c_parser_peek_2nd_token (parser)->மதிப்பு);
	      எனில் (strcmp ("data", p) == 0)
		if_modifier = OMP_TARGET_DATA;
	      இல்லையெனில் எனில் (strcmp ("update", p) == 0)
		if_modifier = OMP_TARGET_UPDATE;
	      இல்லையெனில் எனில் (strcmp ("enter", p) == 0)
		if_modifier = OMP_TARGET_ENTER_DATA;
	      இல்லையெனில் எனில் (strcmp ("exit", p) == 0)
		if_modifier = OMP_TARGET_EXIT_DATA;
	      எனில் (if_modifier != OMP_TARGET)
		{
		  n = 3;
		  c_parser_consume_token (parser);
		}
	      இல்லையெனில்
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<data%>, %<update%>, %<enter%> "
				 "or %<exit%>");
		  if_modifier = ERROR_MARK;
		}
	      எனில் (if_modifier == OMP_TARGET_ENTER_DATA
		  || if_modifier == OMP_TARGET_EXIT_DATA)
		{
		  எனில் (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_POINTER
				(c_parser_peek_2nd_token (parser)->மதிப்பு);
		      எனில் (strcmp ("data", p) == 0)
			n = 4;
		    }
		  எனில் (n == 4)
		    c_parser_consume_token (parser);
		  இல்லையெனில்
		    {
		      location_t loc
			= c_parser_peek_2nd_token (parser)->location;
		      error_at (loc, "expected %<data%>");
		      if_modifier = ERROR_MARK;
		    }
		}
	    }
	}
      எனில் (if_modifier != ERROR_MARK)
	{
	  எனில் (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  இல்லையெனில்
	    {
	      எனில் (n > 2)
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<:%>");
		}
	      if_modifier = ERROR_MARK;
	    }
	}
    }

  location_t loc = c_parser_peek_token (parser)->location;
  c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
  கோவை = convert_lvalue_to_rvalue (loc, கோவை, உண்மை, உண்மை);
  மரம் t = c_objc_common_truthvalue_conversion (loc, கோவை.மதிப்பு), c;
  t = c_fully_fold (t, பொய், வெற்று);
  parens.skip_until_found_close (parser);

  க்கு (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IF)
      {
	எனில் (if_modifier != ERROR_MARK
	    && OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    மாறிலி எழுத்து *p = வெற்று;
	    தேர்வு (if_modifier)
	      {
	      நிலை VOID_CST: p = "cancel"; நிறுத்து;
	      நிலை OMP_PARALLEL: p = "parallel"; நிறுத்து;
	      நிலை OMP_SIMD: p = "simd"; நிறுத்து;
	      நிலை OMP_TASK: p = "task"; நிறுத்து;
	      நிலை OMP_TASKLOOP: p = "taskloop"; நிறுத்து;
	      நிலை OMP_TARGET_DATA: p = "target data"; நிறுத்து;
	      நிலை OMP_TARGET: p = "target"; நிறுத்து;
	      நிலை OMP_TARGET_UPDATE: p = "target update"; நிறுத்து;
	      நிலை OMP_TARGET_ENTER_DATA: p = "target enter data"; நிறுத்து;
	      நிலை OMP_TARGET_EXIT_DATA: p = "target exit data"; நிறுத்து;
	      இயல்பு: gcc_unreachable ();
	      }
	    error_at (location, "too many %<if%> clauses with %qs modifier",
		      p);
	    திரும்பு list;
	  }
	இல்லையெனில் எனில் (OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    எனில் (!is_omp)
	      error_at (location, "too many %<if%> clauses");
	    இல்லையெனில்
	      error_at (location, "too many %<if%> clauses without modifier");
	    திரும்பு list;
	  }
	இல்லையெனில் எனில் (if_modifier == ERROR_MARK
		 || OMP_CLAUSE_IF_MODIFIER (c) == ERROR_MARK)
	  {
	    error_at (location, "if any %<if%> clause has modifier, then all "
				"%<if%> clauses have to use modifier");
	    திரும்பு list;
	  }
      }

  c = build_omp_clause (location, OMP_CLAUSE_IF);
  OMP_CLAUSE_IF_MODIFIER (c) = if_modifier;
  OMP_CLAUSE_IF_கோவை (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

நிலையான மரம்
c_parser_omp_clause_lastprivate (c_parser *parser, மரம் list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  எனில் (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      தருக்க conditional = பொய்;
      எனில் (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  மாறிலி எழுத்து *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
	  எனில் (strcmp (p, "conditional") == 0)
	    {
	      conditional = உண்மை;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      மரம் nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      எனில் (conditional)
	க்கு (மரம் c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      திரும்பு nlist;
    }
  திரும்பு list;
}

/* OpenMP 3.1:
   mergeable */

நிலையான மரம்
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_UNUSED, மரம் list)
{
  மரம் c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  திரும்பு c;
}

/* OpenMP 2.5:
   nowait */

நிலையான மரம்
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_UNUSED, மரம் list)
{
  மரம் c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

நிலையான மரம்
c_parser_omp_clause_இலக்கம்_threads (c_parser *parser, மரம் list)
{
  location_t இலக்கம்_threads_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      location_t கோவை_loc = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
      மரம் c, t = கோவை.மதிப்பு;
      t = c_fully_fold (t, பொய், வெற்று);

      parens.skip_until_found_close (parser);

      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  திரும்பு list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (கோவை_loc, LE_கோவை, boolean_type_முனை, t,
		       build_int_cst (மரம்_TYPE (t), 0));
      protected_set_கோவை_location (c, கோவை_loc);
      எனில் (c == boolean_true_முனை)
	{
	  warning_at (கோவை_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_முனை;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_இலக்கம்_THREADS, "num_threads");

      c = build_omp_clause (இலக்கம்_threads_loc, OMP_CLAUSE_இலக்கம்_THREADS);
      OMP_CLAUSE_இலக்கம்_THREADS_கோவை (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  திரும்பு list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

நிலையான மரம்
c_parser_omp_clause_இலக்கம்_tasks (c_parser *parser, மரம் list)
{
  location_t இலக்கம்_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      தருக்க strict = பொய்;
      எனில் (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு),
		     "strict") == 0)
	{
	  strict = உண்மை;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t கோவை_loc = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
      மரம் c, t = கோவை.மதிப்பு;
      t = c_fully_fold (t, பொய், வெற்று);

      parens.skip_until_found_close (parser);

      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  திரும்பு list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (கோவை_loc, LE_கோவை, boolean_type_முனை, t,
			   build_int_cst (மரம்_TYPE (t), 0));
      எனில் (CAN_HAVE_LOCATION_P (c))
	SET_கோவை_LOCATION (c, கோவை_loc);
      எனில் (c == boolean_true_முனை)
	{
	  warning_at (கோவை_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_முனை;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_இலக்கம்_TASKS, "num_tasks");

      c = build_omp_clause (இலக்கம்_tasks_loc, OMP_CLAUSE_இலக்கம்_TASKS);
      OMP_CLAUSE_இலக்கம்_TASKS_கோவை (c) = t;
      OMP_CLAUSE_இலக்கம்_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  திரும்பு list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

நிலையான மரம்
c_parser_omp_clause_grainsize (c_parser *parser, மரம் list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      தருக்க strict = பொய்;
      எனில் (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு),
		     "strict") == 0)
	{
	  strict = உண்மை;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t கோவை_loc = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
      மரம் c, t = கோவை.மதிப்பு;
      t = c_fully_fold (t, பொய், வெற்று);

      parens.skip_until_found_close (parser);

      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  திரும்பு list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (கோவை_loc, LE_கோவை, boolean_type_முனை, t,
			   build_int_cst (மரம்_TYPE (t), 0));
      எனில் (CAN_HAVE_LOCATION_P (c))
	SET_கோவை_LOCATION (c, கோவை_loc);
      எனில் (c == boolean_true_முனை)
	{
	  warning_at (கோவை_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_முனை;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_கோவை (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  திரும்பு list;
}

/* OpenMP 4.5:
   priority ( expression ) */

நிலையான மரம்
c_parser_omp_clause_priority (c_parser *parser, மரம் list)
{
  location_t priority_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      location_t கோவை_loc = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
      மரம் c, t = கோவை.மதிப்பு;
      t = c_fully_fold (t, பொய், வெற்று);

      parens.skip_until_found_close (parser);

      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  திரும்பு list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (கோவை_loc, LT_கோவை, boolean_type_முனை, t,
			   build_int_cst (மரம்_TYPE (t), 0));
      எனில் (CAN_HAVE_LOCATION_P (c))
	SET_கோவை_LOCATION (c, கோவை_loc);
      எனில் (c == boolean_true_முனை)
	{
	  warning_at (கோவை_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_முனை;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_PRIORITY, "priority");

      c = build_omp_clause (priority_loc, OMP_CLAUSE_PRIORITY);
      OMP_CLAUSE_PRIORITY_கோவை (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  திரும்பு list;
}

/* OpenMP 4.5:
   hint ( expression ) */

நிலையான மரம்
c_parser_omp_clause_hint (c_parser *parser, மரம் list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      location_t கோவை_loc = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
      மரம் c, t = கோவை.மதிப்பு;
      t = c_fully_fold (t, பொய், வெற்று);
      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (t))
	  || மரம்_CODE (t) != INTEGER_CST
	  || மரம்_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  திரும்பு list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_கோவை (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  திரும்பு list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

நிலையான மரம்
c_parser_omp_clause_filter (c_parser *parser, மரம் list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      location_t கோவை_loc = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
      மரம் c, t = கோவை.மதிப்பு;
      t = c_fully_fold (t, பொய், வெற்று);
      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  திரும்பு list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_கோவை (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  திரும்பு list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

நிலையான மரம்
c_parser_omp_clause_defaultmap (c_parser *parser, மரம் list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  மரம் c;
  மாறிலி எழுத்து *p;
  எண்ணிக்கை omp_clause_defaultmap_kind behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  எண்ணிக்கை omp_clause_defaultmap_kind category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;
  எனில் (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  இல்லையெனில் எனில் (!c_parser_next_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      செல் out_err;
    }
  இல்லையெனில்
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);

  தேர்வு (p[0])
    {
    நிலை 'a':
      எனில் (strcmp ("alloc", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ALLOC;
      இல்லையெனில்
	செல் invalid_behavior;
      நிறுத்து;

    நிலை 'd':
      எனில் (strcmp ("default", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
      இல்லையெனில்
	செல் invalid_behavior;
      நிறுத்து;

    நிலை 'f':
      எனில் (strcmp ("firstprivate", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FIRSTPRIVATE;
      இல்லையெனில் எனில் (strcmp ("from", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FROM;
      இல்லையெனில்
	செல் invalid_behavior;
      நிறுத்து;

    நிலை 'n':
      எனில் (strcmp ("none", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_NONE;
      இல்லையெனில்
	செல் invalid_behavior;
      நிறுத்து;

    நிலை 'p':
      எனில் (strcmp ("present", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_PRESENT;
      இல்லையெனில்
	செல் invalid_behavior;
      நிறுத்து;

    நிலை 't':
      எனில் (strcmp ("tofrom", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TOFROM;
      இல்லையெனில் எனில் (strcmp ("to", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TO;
      இல்லையெனில்
	செல் invalid_behavior;
      நிறுத்து;

    இயல்பு:
      செல் invalid_behavior;
    }
  c_parser_consume_token (parser);

  எனில் (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	செல் out_err;
      எனில் (!c_parser_next_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  செல் out_err;
	}
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      தேர்வு (p[0])
	{
	நிலை 'a':
	  எனில் (strcmp ("aggregate", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE;
	  இல்லையெனில் எனில் (strcmp ("all", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL;
	  இல்லையெனில்
	    செல் invalid_category;
	  நிறுத்து;

	நிலை 'p':
	  எனில் (strcmp ("pointer", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER;
	  இல்லையெனில்
	    செல் invalid_category;
	  நிறுத்து;

	நிலை 's':
	  எனில் (strcmp ("scalar", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR;
	  இல்லையெனில்
	    செல் invalid_category;
	  நிறுத்து;

	இயல்பு:
	  செல் invalid_category;
	}

      c_parser_consume_token (parser);
    }
  parens.skip_until_found_close (parser);

  க்கு (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEFAULTMAP
	&& (category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
	    || OMP_CLAUSE_DEFAULTMAP_CATEGORY (c) == category
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL)))
      {
	எண்ணிக்கை omp_clause_defaultmap_kind cat = category;
	location_t loc = OMP_CLAUSE_LOCATION (c);
	எனில் (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
		&& (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		    != OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)))
	  cat = OMP_CLAUSE_DEFAULTMAP_CATEGORY (c);
	p = வெற்று;
	தேர்வு (cat)
	  {
	  நிலை OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED:
	    p = வெற்று;
	    நிறுத்து;
	  நிலை OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL:
	    p = "all";
	    நிறுத்து;
	  நிலை OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE:
	    p = "aggregate";
	    நிறுத்து;
	  நிலை OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER:
	    p = "pointer";
	    நிறுத்து;
	  நிலை OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR:
	    p = "scalar";
	    நிறுத்து;
	  இயல்பு:
	    gcc_unreachable ();
	  }
	எனில் (p)
	  error_at (loc, "too many %<defaultmap%> clauses with %qs category",
		    p);
	இல்லையெனில்
	  error_at (loc, "too many %<defaultmap%> clauses with unspecified "
			 "category");
	நிறுத்து;
      }

  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULTMAP);
  OMP_CLAUSE_DEFAULTMAP_SET_KIND (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;

 out_err:
  parens.skip_until_found_close (parser);
  திரும்பு list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

நிலையான மரம்
c_parser_omp_clause_use_device_ptr (c_parser *parser, மரம் list)
{
  திரும்பு c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

நிலையான மரம்
c_parser_omp_clause_use_device_addr (c_parser *parser, மரம் list)
{
  திரும்பு c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

நிலையான மரம்
c_parser_omp_clause_has_device_addr (c_parser *parser, மரம் list)
{
  திரும்பு c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

நிலையான மரம்
c_parser_omp_clause_is_device_ptr (c_parser *parser, மரம் list)
{
  திரும்பு c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

நிலையான மரம்
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_code code,
				 மரம் list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  location_t கோவை_loc = c_parser_peek_token (parser)->location;
  c_கோவை கோவை = c_parser_expression (parser);
  கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
  மரம் c, t = கோவை.மதிப்பு;
  t = c_fully_fold (t, பொய், வெற்று);

  parens.skip_until_found_close (parser);

  எனில் (t == error_mark_முனை)
    திரும்பு list;
  இல்லையெனில் எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (t)))
    {
      error_at (கோவை_loc, "%qs expression must be integral",
		omp_clause_code_name[code]);
      திரும்பு list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (கோவை_loc, LE_கோவை, boolean_type_முனை, t,
		       build_int_cst (மரம்_TYPE (t), 0));
  protected_set_கோவை_location (c, கோவை_loc);
  எனில் (c == boolean_true_முனை)
    {
      warning_at (கோவை_loc, 0,
		  "%qs value must be positive",
		  omp_clause_code_name[code]);
      t = integer_one_முனை;
    }

  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  c = build_omp_clause (loc, code);
  OMP_CLAUSE_OPERAND (c, 0) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
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

நிலையான மரம்
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_code kind,
			    மாறிலி எழுத்து *str, மரம் list)
{
  மாறிலி எழுத்து *id = "num";
  மரம் ops[2] = { NULL_மரம், NULL_மரம் }, c;

  எனில் (kind == OMP_CLAUSE_VECTOR)
    id = "length";

  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      செய்
	{
	  c_token *next = c_parser_peek_token (parser);
	  முழு idx = 0;

	  /* Gang static argument.  */
	  எனில் (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		செல் cleanup_error;

	      idx = 1;
	      எனில் (ops[idx] != NULL_மரம்)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  செல் cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      எனில் (c_parser_next_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_முனை;

		  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      தொடர்;
		    }
		  இல்லையெனில்
		    நிறுத்து;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_NAME)
		   && strcmp (id, IDENTIFIER_POINTER (next->மதிப்பு)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  எனில் (ops[idx] != NULL_மரம்)
	    {
	      c_parser_error (parser, "unexpected argument");
	      செல் cleanup_error;
	    }

	  location_t கோவை_loc = c_parser_peek_token (parser)->location;
	  c_கோவை cexpr = c_parser_கோவை_no_commas (parser, வெற்று);
	  cexpr = convert_lvalue_to_rvalue (கோவை_loc, cexpr, பொய், உண்மை);
	  மரம் கோவை = cexpr.மதிப்பு;
	  எனில் (கோவை == error_mark_முனை)
	    செல் cleanup_error;

	  கோவை = c_fully_fold (கோவை, பொய், வெற்று);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (கோவை)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      திரும்பு list;
	    }

	  மரம் c = fold_build2_loc (கோவை_loc, LE_கோவை, boolean_type_முனை, கோவை,
				    build_int_cst (மரம்_TYPE (கோவை), 0));
	  எனில் (c == boolean_true_முனை)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      கோவை = integer_one_முனை;
	    }

	  ops[idx] = கோவை;

	  எனில் (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      தொடர்;
	    }
	  நிறுத்து;
	}
      போது (1);

      எனில் (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	செல் cleanup_error;
    }

  check_no_duplicate_clause (list, kind, str);

  c = build_omp_clause (loc, kind);

  எனில் (ops[1])
    OMP_CLAUSE_OPERAND (c, 1) = ops[1];

  OMP_CLAUSE_OPERAND (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  திரும்பு c;

 cleanup_error:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  திரும்பு list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

நிலையான மரம்
c_parser_oacc_simple_clause (location_t loc, எண்ணிக்கை omp_clause_code code,
			     மரம் list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  மரம் c = build_omp_clause (loc, code);
  OMP_CLAUSE_CHAIN (c) = list;

  திரும்பு c;
}

/* OpenACC:
   async [( int-expr )] */

நிலையான மரம்
c_parser_oacc_clause_async (c_parser *parser, மரம் list)
{
  மரம் c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_முனை, GOMP_ASYNC_NOVAL);

  எனில் (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_கோவை_no_commas (parser, வெற்று).மதிப்பு;
      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      இல்லையெனில் எனில் (t == error_mark_முனை
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	திரும்பு list;
    }
  இல்லையெனில்
    t = c_fully_fold (t, பொய், வெற்று);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_கோவை (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  திரும்பு list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

நிலையான மரம்
c_parser_oacc_clause_tile (c_parser *parser, மரம் list)
{
  மரம் c, கோவை = error_mark_முனை;
  location_t loc;
  மரம் tile = NULL_மரம்;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  எனில் (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    திரும்பு list;

  செய்
    {
      எனில் (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	திரும்பு list;

      எனில் (c_parser_next_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  கோவை = integer_zero_முனை;
	}
      இல்லையெனில்
	{
	  location_t கோவை_loc = c_parser_peek_token (parser)->location;
	  c_கோவை cexpr = c_parser_கோவை_no_commas (parser, வெற்று);
	  cexpr = convert_lvalue_to_rvalue (கோவை_loc, cexpr, பொய், உண்மை);
	  கோவை = cexpr.மதிப்பு;

	  எனில் (கோவை == error_mark_முனை)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      திரும்பு list;
	    }

	  கோவை = c_fully_fold (கோவை, பொய், வெற்று);

	  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (கோவை))
	      || !மரம்_fits_shwi_p (கோவை)
	      || மரம்_to_shwi (கோவை) <= 0)
	    {
	      error_at (கோவை_loc, "%<tile%> argument needs positive"
			" integral constant");
	      கோவை = integer_zero_முனை;
	    }
	}

      tile = மரம்_cons (NULL_மரம், கோவை, tile);
    }
  போது (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN));

  /* Consume the trailing ')'.  */
  c_parser_consume_token (parser);

  c = build_omp_clause (loc, OMP_CLAUSE_TILE);
  tile = nreverse (tile);
  OMP_CLAUSE_TILE_LIST (c) = tile;
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
}

/* OpenACC:
   wait [( int-expr-list )] */

நிலையான மரம்
c_parser_oacc_clause_wait (c_parser *parser, மரம் list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  எனில் (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  இல்லையெனில்
    {
      மரம் c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_முனை, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  திரும்பு list;
}

/* OpenACC 2.7:
   self [( expression )] */

நிலையான மரம்
c_parser_oacc_compute_clause_self (c_parser *parser, மரம் list)
{
  மரம் t;
  location_t location = c_parser_peek_token (parser)->location;
  எனில் (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (loc, கோவை, உண்மை, உண்மை);
      t = c_objc_common_truthvalue_conversion (loc, கோவை.மதிப்பு);
      t = c_fully_fold (t, பொய், வெற்று);
      parens.skip_until_found_close (parser);
    }
  இல்லையெனில்
    t = truthvalue_true_முனை;

  க்கு (மரம் c = list; c; c = OMP_CLAUSE_CHAIN (c))
    எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	திரும்பு list;
      }

  மரம் c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_கோவை (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
}

/* OpenMP 5.0:
   order ( concurrent )

   OpenMP 5.1:
   order ( order-modifier : concurrent )

   order-modifier:
     reproducible
     unconstrained  */

நிலையான மரம்
c_parser_omp_clause_order (c_parser *parser, மரம் list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  மரம் c;
  மாறிலி எழுத்து *p;
  தருக்க unconstrained = பொய்;
  தருக்க reproducible = பொய்;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;
  எனில் (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp (p, "unconstrained") == 0)
	unconstrained = உண்மை;
      இல்லையெனில் எனில் (strcmp (p, "reproducible") == 0)
	reproducible = உண்மை;
      இல்லையெனில்
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  செல் out_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  எனில் (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      செல் out_err;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
  எனில் (strcmp (p, "concurrent") != 0)
    {
      c_parser_error (parser, "expected %<concurrent%>");
      செல் out_err;
    }
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDER, "order");
  c = build_omp_clause (loc, OMP_CLAUSE_ORDER);
  OMP_CLAUSE_ORDER_UNCONSTRAINED (c) = unconstrained;
  OMP_CLAUSE_ORDER_REPRODUCIBLE (c) = reproducible;
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;

 out_err:
  parens.skip_until_found_close (parser);
  திரும்பு list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

நிலையான மரம்
c_parser_omp_clause_bind (c_parser *parser, மரம் list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  மரம் c;
  மாறிலி எழுத்து *p;
  எண்ணிக்கை omp_clause_bind_kind kind = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;
  எனில் (!c_parser_next_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_found_close (parser);
      திரும்பு list;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
  எனில் (strcmp (p, "teams") == 0)
    kind = OMP_CLAUSE_BIND_TEAMS;
  இல்லையெனில் எனில் (strcmp (p, "parallel") == 0)
    kind = OMP_CLAUSE_BIND_PARALLEL;
  இல்லையெனில் எனில் (strcmp (p, "thread") != 0)
    செல் invalid;
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

நிலையான மரம்
c_parser_omp_clause_ordered (c_parser *parser, மரம் list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  மரம் c, இலக்கம் = NULL_மரம்;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      இலக்கம் = c_parser_கோவை_no_commas (parser, வெற்று).மதிப்பு;
      parens.skip_until_found_close (parser);
    }
  எனில் (இலக்கம் == error_mark_முனை)
    திரும்பு list;
  எனில் (இலக்கம்)
    {
      mark_exp_read (இலக்கம்);
      இலக்கம் = c_fully_fold (இலக்கம், பொய், வெற்று);
      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (இலக்கம்))
	  || !மரம்_fits_shwi_p (இலக்கம்)
	  || (n = மரம்_to_shwi (இலக்கம்)) <= 0
	  || (முழு) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  திரும்பு list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_கோவை (c) = இலக்கம்;
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

நிலையான மரம்
c_parser_omp_clause_private (c_parser *parser, மரம் list)
{
  திரும்பு c_parser_omp_var_list_parens (parser, OMP_CLAUSE_PRIVATE, list);
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

நிலையான மரம்
c_parser_omp_clause_reduction (c_parser *parser, எண்ணிக்கை omp_clause_code kind,
			       தருக்க is_omp, மரம் list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      தருக்க task = பொய்;
      தருக்க inscan = பொய்;
      எண்ணிக்கை மரம்_code code = ERROR_MARK;
      மரம் reduc_id = NULL_மரம்;

      எனில் (kind == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  எனில் (c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      மாறிலி எழுத்து *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
	      எனில் (strcmp (p, "task") == 0)
		task = உண்மை;
	      இல்லையெனில் எனில் (strcmp (p, "inscan") == 0)
		inscan = உண்மை;
	      எனில் (task || inscan)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		}
	    }
	}

      தேர்வு (c_parser_peek_token (parser)->type)
	{
	நிலை CPP_PLUS:
	  code = PLUS_கோவை;
	  நிறுத்து;
	நிலை CPP_MULT:
	  code = MULT_கோவை;
	  நிறுத்து;
	நிலை CPP_MINUS:
	  எனில் (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.add_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  code = MINUS_கோவை;
	  நிறுத்து;
	நிலை CPP_AND:
	  code = BIT_AND_கோவை;
	  நிறுத்து;
	நிலை CPP_XOR:
	  code = BIT_XOR_கோவை;
	  நிறுத்து;
	நிலை CPP_OR:
	  code = BIT_IOR_கோவை;
	  நிறுத்து;
	நிலை CPP_AND_AND:
	  code = TRUTH_ANDIF_கோவை;
	  நிறுத்து;
	நிலை CPP_OR_OR:
	  code = TRUTH_ORIF_கோவை;
	  நிறுத்து;
        நிலை CPP_NAME:
	  {
	    மாறிலி எழுத்து *p
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
	    எனில் (strcmp (p, "min") == 0)
	      {
		code = MIN_கோவை;
		நிறுத்து;
	      }
	    எனில் (strcmp (p, "max") == 0)
	      {
		code = MAX_கோவை;
		நிறுத்து;
	      }
	    reduc_id = c_parser_peek_token (parser)->மதிப்பு;
	    நிறுத்து;
	  }
	இயல்பு:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
	  திரும்பு list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (code, reduc_id);
      எனில் (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  மரம் nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, kind, list);
	  க்கு (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      மரம் d = OMP_CLAUSE_DECL (c), type;
	      எனில் (மரம்_CODE (d) != OMP_ARRAY_SECTION)
		type = மரம்_TYPE (d);
	      இல்லையெனில்
		{
		  முழு cnt = 0;
		  மரம் t;
		  க்கு (t = d;
		      மரம்_CODE (t) == OMP_ARRAY_SECTION;
		      t = மரம்_OPERAND (t, 0))
		    cnt++;
		  type = மரம்_TYPE (t);
		  போது (cnt > 0)
		    {
		      எனில் (மரம்_CODE (type) != POINTER_TYPE
			  && மரம்_CODE (type) != ARRAY_TYPE)
			நிறுத்து;
		      type = மரம்_TYPE (type);
		      cnt--;
		    }
		}
	      போது (மரம்_CODE (type) == ARRAY_TYPE)
		type = மரம்_TYPE (type);
	      OMP_CLAUSE_REDUCTION_CODE (c) = code;
	      எனில் (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      இல்லையெனில் எனில் (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      எனில் (code == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || மரம்_CODE (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_found_close (parser);
    }
  திரும்பு list;
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

நிலையான மரம்
c_parser_omp_clause_schedule (c_parser *parser, மரம் list)
{
  மரம் c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  முழு modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  c = build_omp_clause (loc, OMP_CLAUSE_SCHEDULE);

  location_t comma = UNKNOWN_LOCATION;
  போது (c_parser_next_token_is (parser, CPP_NAME))
    {
      மரம் kind = c_parser_peek_token (parser)->மதிப்பு;
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (kind);
      எனில் (strcmp ("simd", p) == 0)
	OMP_CLAUSE_SCHEDULE_SIMD (c) = 1;
      இல்லையெனில் எனில் (strcmp ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_MONOTONIC;
      இல்லையெனில் எனில் (strcmp ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_NONMONOTONIC;
      இல்லையெனில்
	நிறுத்து;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      எனில் (nmodifiers++ == 0
	  && c_parser_next_token_is (parser, CPP_COMMA))
	{
	  comma = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	}
      இல்லையெனில்
	{
	  c_parser_require (parser, CPP_COLON, "expected %<:%>");
	  நிறுத்து;
	}
    }
  எனில் (comma != UNKNOWN_LOCATION)
    error_at (comma, "expected %<:%>");

  எனில் ((modifiers & (OMP_CLAUSE_SCHEDULE_MONOTONIC
		    | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
      == (OMP_CLAUSE_SCHEDULE_MONOTONIC
	  | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மரம் kind = c_parser_peek_token (parser)->மதிப்பு;
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (kind);

      தேர்வு (p[0])
	{
	நிலை 'd':
	  எனில் (strcmp ("dynamic", p) != 0)
	    செல் invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_DYNAMIC;
	  நிறுத்து;

        நிலை 'g':
	  எனில் (strcmp ("guided", p) != 0)
	    செல் invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_GUIDED;
	  நிறுத்து;

	நிலை 'r':
	  எனில் (strcmp ("runtime", p) != 0)
	    செல் invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_RUNTIME;
	  நிறுத்து;

	இயல்பு:
	  செல் invalid_kind;
	}
    }
  இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_STATIC;
  இல்லையெனில் எனில் (c_parser_next_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_AUTO;
  இல்லையெனில்
    செல் invalid_kind;

  c_parser_consume_token (parser);
  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
    {
      location_t here;
      c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (here, கோவை, பொய், உண்மை);
      t = கோவை.மதிப்பு;
      t = c_fully_fold (t, பொய், வெற்று);

      எனில் (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_RUNTIME)
	error_at (here, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      இல்லையெனில் எனில் (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_AUTO)
	error_at (here,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      இல்லையெனில் எனில் (மரம்_CODE (மரம்_TYPE (t)) == INTEGER_TYPE
	       || மரம்_CODE (மரம்_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  மரம் s = fold_build2_loc (loc, LE_கோவை, boolean_type_முனை, t,
				    build_int_cst (மரம்_TYPE (t), 0));
	  protected_set_கோவை_location (s, loc);
	  எனில் (s == boolean_true_முனை)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_முனை;
	    }
	  OMP_CLAUSE_SCHEDULE_CHUNK_கோவை (c) = t;
	}
      இல்லையெனில்
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_found_close (parser);
    }
  இல்லையெனில்
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_SCHEDULE_KIND (c)
    = (எண்ணிக்கை omp_clause_schedule_kind)
      (OMP_CLAUSE_SCHEDULE_KIND (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_SCHEDULE, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;

 invalid_kind:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  திரும்பு list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

நிலையான மரம்
c_parser_omp_clause_shared (c_parser *parser, மரம் list)
{
  திரும்பு c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

நிலையான மரம்
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_UNUSED, மரம் list)
{
  மரம் c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_UNTIED, "untied");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_UNTIED);
  OMP_CLAUSE_CHAIN (c) = list;

  திரும்பு c;
}

/* OpenMP 4.0:
   inbranch
   notinbranch */

நிலையான மரம்
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_UNUSED,
			    எண்ணிக்கை omp_clause_code code, மரம் list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  மரம் c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  திரும்பு c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

நிலையான மரம்
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_UNUSED,
				எண்ணிக்கை omp_clause_code code, மரம் list)
{
  மரம் c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  திரும்பு c;
}

/* OpenMP 4.5:
   nogroup */

நிலையான மரம்
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_UNUSED, மரம் list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  மரம் c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
}

/* OpenMP 4.5:
   simd
   threads */

நிலையான மரம்
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_UNUSED,
				 எண்ணிக்கை omp_clause_code code, மரம் list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);
  மரம் c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

நிலையான மரம்
c_parser_omp_clause_இலக்கம்_teams (c_parser *parser, மரம் list)
{
  location_t இலக்கம்_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      location_t upper_loc = c_parser_peek_token (parser)->location;
      location_t lower_loc = UNKNOWN_LOCATION;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (upper_loc, கோவை, பொய், உண்மை);
      மரம் c, upper = கோவை.மதிப்பு, lower = NULL_மரம்;
      upper = c_fully_fold (upper, பொய், வெற்று);

      எனில் (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  lower_loc = upper_loc;
	  lower = upper;
	  upper_loc = c_parser_peek_token (parser)->location;
	  கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	  கோவை = convert_lvalue_to_rvalue (upper_loc, கோவை, பொய், உண்மை);
	  upper = கோவை.மதிப்பு;
	  upper = c_fully_fold (upper, பொய், வெற்று);
	}

      parens.skip_until_found_close (parser);

      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (upper))
	  || (lower && !INTEGRAL_TYPE_P (மரம்_TYPE (lower))))
	{
	  c_parser_error (parser, "expected integer expression");
	  திரும்பு list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (upper_loc, LE_கோவை, boolean_type_முனை, upper,
			   build_int_cst (மரம்_TYPE (upper), 0));
      protected_set_கோவை_location (c, upper_loc);
      எனில் (c == boolean_true_முனை)
	{
	  warning_at (upper_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  upper = integer_one_முனை;
	}
      எனில் (lower)
	{
	  c = fold_build2_loc (lower_loc, LE_கோவை, boolean_type_முனை, lower,
			       build_int_cst (மரம்_TYPE (lower), 0));
	  protected_set_கோவை_location (c, lower_loc);
	  எனில் (c == boolean_true_முனை)
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      lower = NULL_மரம்;
	    }
	  இல்லையெனில் எனில் (மரம்_CODE (lower) == INTEGER_CST
		   && மரம்_CODE (upper) == INTEGER_CST
		   && மரம்_int_cst_lt (upper, lower))
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", lower, upper);
	      lower = NULL_மரம்;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_இலக்கம்_TEAMS, "num_teams");

      c = build_omp_clause (இலக்கம்_teams_loc, OMP_CLAUSE_இலக்கம்_TEAMS);
      OMP_CLAUSE_இலக்கம்_TEAMS_UPPER_கோவை (c) = upper;
      OMP_CLAUSE_இலக்கம்_TEAMS_LOWER_கோவை (c) = lower;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  திரும்பு list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

நிலையான மரம்
c_parser_omp_clause_thread_limit (c_parser *parser, மரம் list)
{
  location_t இலக்கம்_thread_limit_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      location_t கோவை_loc = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
      மரம் c, t = கோவை.மதிப்பு;
      t = c_fully_fold (t, பொய், வெற்று);

      parens.skip_until_found_close (parser);

      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  திரும்பு list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (கோவை_loc, LE_கோவை, boolean_type_முனை, t,
			   build_int_cst (மரம்_TYPE (t), 0));
      protected_set_கோவை_location (c, கோவை_loc);
      எனில் (c == boolean_true_முனை)
	{
	  warning_at (கோவை_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_முனை;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_LIMIT,
				 "thread_limit");

      c = build_omp_clause (இலக்கம்_thread_limit_loc, OMP_CLAUSE_THREAD_LIMIT);
      OMP_CLAUSE_THREAD_LIMIT_கோவை (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  திரும்பு list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

நிலையான மரம்
c_parser_omp_clause_aligned (c_parser *parser, மரம் list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  மரம் nl, c;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  எனில் (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t கோவை_loc = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
      மரம் alignment = கோவை.மதிப்பு;
      alignment = c_fully_fold (alignment, பொய், வெற்று);
      எனில் (மரம்_CODE (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (மரம்_TYPE (alignment))
	  || மரம்_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_மரம்;
	}

      க்கு (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_found_close (parser);
  திரும்பு nl;
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

நிலையான மரம்
c_parser_omp_clause_allocate (c_parser *parser, மரம் list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  மரம் nl, c;
  மரம் allocator = NULL_மரம்;
  மரம் align = NULL_மரம்;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  எனில் ((c_parser_next_token_is_not (parser, CPP_NAME)
       && c_parser_next_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      தருக்க has_modifiers = பொய்;
      மரம் orig_type = NULL_மரம்;
      எனில் (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  unsigned முழு n = 3;
	  மாறிலி எழுத்து *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
	  எனில் ((strcmp (p, "allocator") == 0 || strcmp (p, "align") == 0)
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      எனில் (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = உண்மை;
	      இல்லையெனில் எனில் (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  மாறிலி எழுத்து *q = IDENTIFIER_POINTER (tok->மதிப்பு);
		  n += 4;
		  எனில் ((strcmp (q, "allocator") == 0
		       || strcmp (q, "align") == 0)
		      && c_parser_check_balanced_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = உண்மை;
		}
	    }
	  எனில் (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t கோவை_loc = c_parser_peek_token (parser)->location;
	      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
	      எனில் (கோவை.மதிப்பு == error_mark_முனை)
		;
	      இல்லையெனில் எனில் (strcmp (p, "allocator") == 0)
		{
		  allocator = கோவை.மதிப்பு;
		  allocator = c_fully_fold (allocator, பொய், வெற்று);
		  orig_type = கோவை.original_type
			      ? கோவை.original_type : மரம்_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      இல்லையெனில்
		{
		  align = கோவை.மதிப்பு;
		  align = c_fully_fold (align, பொய், வெற்று);
		}
	      parens2.skip_until_found_close (parser);
	      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  மாறிலி எழுத்து *q = "";
		  எனில் (c_parser_next_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_POINTER (tok->மதிப்பு);
		  எனில் (strcmp (q, "allocator") != 0 && strcmp (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_found_close (parser);
		      திரும்பு list;
		    }
		  இல்லையெனில் எனில் (strcmp (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_found_close (parser);
		      திரும்பு list;
		    }
		  c_parser_consume_token (parser);
		  எனில் (!parens2.require_open (parser))
		    {
		      parens.skip_until_found_close (parser);
		      திரும்பு list;
		    }
		  கோவை_loc = c_parser_peek_token (parser)->location;
		  கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
		  கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய்,
						   உண்மை);
		  எனில் (strcmp (q, "allocator") == 0)
		    {
		      allocator = கோவை.மதிப்பு;
		      allocator = c_fully_fold (allocator, பொய், வெற்று);
		      orig_type = கோவை.original_type
				  ? கோவை.original_type : மரம்_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  இல்லையெனில்
		    {
		      align = கோவை.மதிப்பு;
		      align = c_fully_fold (align, பொய், வெற்று);
		    }
		  parens2.skip_until_found_close (parser);
		}
	    }
	}
      எனில் (!has_modifiers)
	{
	  location_t கோவை_loc = c_parser_peek_token (parser)->location;
	  c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	  கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
	  எனில் (கோவை.மதிப்பு != error_mark_முனை)
	    {
	      allocator = கோவை.மதிப்பு;
	      allocator = c_fully_fold (allocator, பொய், வெற்று);
	      orig_type = கோவை.original_type
			  ? கோவை.original_type : மரம்_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      எனில் (allocator
	  && (!INTEGRAL_TYPE_P (மரம்_TYPE (allocator))
	      || மரம்_CODE (orig_type) != ENUMERAL_TYPE
	      || (TYPE_NAME (orig_type)
		  != get_identifier ("omp_allocator_handle_t"))))
        {
          error_at (clause_loc, "%<allocate%> clause allocator expression "
				"has type %qT rather than "
				"%<omp_allocator_handle_t%>",
				மரம்_TYPE (allocator));
          allocator = NULL_மரம்;
        }
      எனில் (align
	  && (!INTEGRAL_TYPE_P (மரம்_TYPE (align))
	      || !மரம்_fits_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_மரம்;
	}
      எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_found_close (parser);
	  திரும்பு list;
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALLOCATE, list);

  எனில் (allocator || align)
    க்கு (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      {
	OMP_CLAUSE_ALLOCATE_ALLOCATOR (c) = allocator;
	OMP_CLAUSE_ALLOCATE_ALIGN (c) = align;
      }

  parens.skip_until_found_close (parser);
  திரும்பு nl;
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

நிலையான மரம்
c_parser_omp_clause_uses_allocators (c_parser *parser, மரம் list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  மரம் nl = list;
  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

parse_next:

  தருக்க has_modifiers = பொய்;
  தருக்க seen_allocators = பொய்;
  மரம் memspace_கோவை = NULL_மரம்;
  மரம் traits_var = NULL_மரம்;

  எனில் (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      unsigned முழு n = 3;
      மாறிலி எழுத்து *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் ((strcmp (p, "traits") == 0 || strcmp (p, "memspace") == 0)
	  && c_parser_check_balanced_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  எனில் (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = உண்மை;
	  இல்லையெனில் எனில் (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      மாறிலி எழுத்து *q = IDENTIFIER_POINTER (tok->மதிப்பு);
	      n += 4;
	      எனில் ((strcmp (q, "traits") == 0
		   || strcmp (q, "memspace") == 0)
		  && c_parser_check_balanced_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  எனில் (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = உண்மை;
		  எனில் ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      மாறிலி எழுத்து *m = IDENTIFIER_POINTER (tok->மதிப்பு);
		      எனில் (strcmp (p, m) == 0 || strcmp (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  செல் end;
			}
		    }
		}
	    }
	}
      எனில் (has_modifiers)
	{
	  c_parser_consume_token (parser);
	  matching_parens parens2;
	  parens2.require_open (parser);
	  c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	  எனில் (கோவை.மதிப்பு == error_mark_முனை)
	    ;
	  இல்லையெனில் எனில் (strcmp (p, "traits") == 0)
	    {
	      traits_var = கோவை.மதிப்பு;
	      traits_var = c_fully_fold (traits_var, பொய், வெற்று);
	      mark_exp_read (traits_var);
	    }
	  இல்லையெனில்
	    {
	      memspace_கோவை = கோவை.மதிப்பு;
	      memspace_கோவை = c_fully_fold (memspace_கோவை, பொய், வெற்று);
	    }
	  parens2.skip_until_found_close (parser);
	  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      மாறிலி எழுத்து *q = "";
	      எனில் (c_parser_next_token_is (parser, CPP_NAME))
		q = IDENTIFIER_POINTER (tok->மதிப்பு);
	      எனில் (strcmp (q, "traits") != 0 && strcmp (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_found_close (parser);
		  திரும்பு list;
		}
	      இல்லையெனில் எனில் (strcmp (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_found_close (parser);
		  திரும்பு list;
		}
	      c_parser_consume_token (parser);
	      எனில் (!parens2.require_open (parser))
		{
		  parens.skip_until_found_close (parser);
		  திரும்பு list;
		}
	      கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	      எனில் (strcmp (q, "traits") == 0)
		{
		  traits_var = கோவை.மதிப்பு;
		  traits_var = c_fully_fold (traits_var, பொய், வெற்று);
		  mark_exp_read (traits_var);
		}
	      இல்லையெனில்
		{
		  memspace_கோவை = கோவை.மதிப்பு;
		  memspace_கோவை = c_fully_fold (memspace_கோவை, பொய், வெற்று);
		}
	      parens2.skip_until_found_close (parser);
	    }
	  எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    செல் end;
	}
    }

  போது (c_parser_next_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      மாறிலி எழுத்து *tok_s = IDENTIFIER_POINTER (tok->மதிப்பு);
      மரம் t = lookup_name (tok->மதிப்பு);
      எனில் (t == NULL_மரம்)
	{
	  undeclared_variable (tok->location, tok->மதிப்பு);
	  t = error_mark_முனை;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      மரம் legacy_traits = NULL_மரம்;
      எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  மாறிலி எழுத்து *tok_a
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
	  c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_found_close (parser);

	  எனில் (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      செல் end;
	    }
	  legacy_traits = c_fully_fold (கோவை.மதிப்பு, பொய், வெற்று);
	  எனில் (legacy_traits == error_mark_முனை)
	    செல் end;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  எனில் (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.add_fixit_replace (alloc_loc, "traits");
	      richloc.add_fixit_செருகு_after (close_loc, ": ");
	      richloc.add_fixit_செருகு_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      எனில் (seen_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  செல் end;
	}
      seen_allocators = உண்மை;

      மரம் c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_USES_ALLOCATORS);
      OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c) = memspace_கோவை;
      OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      இல்லையெனில்
	நிறுத்து;
    }

  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      செல் parse_next;
    }

 end:
  parens.skip_until_found_close (parser);
  திரும்பு nl;
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

நிலையான மரம்
c_parser_omp_clause_linear (c_parser *parser, மரம் list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  மரம் nl, c, step;
  எண்ணிக்கை omp_clause_linear_kind kind = OMP_CLAUSE_LINEAR_DEFAULT;
  தருக்க old_linear_modifier = பொய்;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (tok->மதிப்பு);
      எனில் (strcmp ("val", p) == 0)
	kind = OMP_CLAUSE_LINEAR_VAL;
      எனில் (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	kind = OMP_CLAUSE_LINEAR_DEFAULT;
      எனில் (kind != OMP_CLAUSE_LINEAR_DEFAULT)
	{
	  old_linear_modifier = உண்மை;
	  rm1_loc = make_location (tok->location, tok->location,
				   c_parser_peek_2nd_token (parser)->location);
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_LINEAR, list);

  எனில் (kind != OMP_CLAUSE_LINEAR_DEFAULT)
    {
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
    }

  எனில் (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t கோவை_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = கோவை_loc;
      தருக்க has_modifiers = பொய்;
      எனில் (kind == OMP_CLAUSE_LINEAR_DEFAULT
	  && c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  மாறிலி எழுத்து *p = IDENTIFIER_POINTER (tok->மதிப்பு);
	  unsigned முழு pos = 0;
	  எனில் (strcmp ("val", p) == 0)
	    pos = 2;
	  இல்லையெனில் எனில் (strcmp ("step", p) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      pos = 3;
	      எனில் (c_parser_check_balanced_raw_token_sequence (parser, &pos)
		  && (c_parser_peek_nth_token_raw (parser, pos)->type
		      == CPP_CLOSE_PAREN))
		++pos;
	      இல்லையெனில்
		pos = 0;
	    }
	  எனில் (pos)
	    {
	      tok = c_parser_peek_nth_token_raw (parser, pos);
	      எனில் (tok->type == CPP_COMMA || tok->type == CPP_CLOSE_PAREN)
		has_modifiers = உண்மை;
	    }
	}
      எனில் (has_modifiers)
	{
	  step = NULL_மரம்;
	  போது (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (tok->மதிப்பு);
	      எனில் (strcmp ("val", p) == 0)
		{
		  எனில் (kind != OMP_CLAUSE_LINEAR_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  kind = OMP_CLAUSE_LINEAR_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      இல்லையெனில் எனில் (strcmp ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  எனில் (parens2.require_open (parser))
		    {
		      எனில் (step)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      கோவை_loc = c_parser_peek_token (parser)->location;
		      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
		      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய்,
						       உண்மை);
		      step = c_fully_fold (கோவை.மதிப்பு, பொய், வெற்று);
		      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (step)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  step = integer_one_முனை;
			}
		      parens2.skip_until_found_close (parser);
		    }
		  இல்லையெனில்
		    நிறுத்து;
		}
	      இல்லையெனில்
		நிறுத்து;
	      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  தொடர்;
		}
	      நிறுத்து;
	    }
	  எனில் (!step)
	    step = integer_one_முனை;
	}
      இல்லையெனில்
	{
	  c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	  கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
	  step = c_fully_fold (கோவை.மதிப்பு, பொய், வெற்று);
	  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (step)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      step = integer_one_முனை;
	    }
	}

    }
  இல்லையெனில்
    step = integer_one_முனை;

  க்கு (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_LINEAR_STEP (c) = step;
      OMP_CLAUSE_LINEAR_KIND (c) = kind;
      OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c) = old_linear_modifier;
    }

  எனில் (old_linear_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      எனில் (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_remove (rm1_loc);
	  எனில் (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.add_fixit_remove (rm2_loc);
	      richloc.add_fixit_செருகு_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.add_fixit_செருகு_before (close_loc, ")");
	    }
	  இல்லையெனில்
	    richloc.add_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_found_close (parser);
  திரும்பு nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

நிலையான மரம்
c_parser_omp_clause_nontemporal (c_parser *parser, மரம் list)
{
  திரும்பு c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

நிலையான மரம்
c_parser_omp_clause_safelen (c_parser *parser, மரம் list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  மரம் c, t;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  location_t கோவை_loc = c_parser_peek_token (parser)->location;
  c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
  கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
  t = கோவை.மதிப்பு;
  t = c_fully_fold (t, பொய், வெற்று);
  எனில் (மரம்_CODE (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (மரம்_TYPE (t))
      || மரம்_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_மரம்;
    }

  parens.skip_until_found_close (parser);
  எனில் (t == NULL_மரம் || t == error_mark_முனை)
    திரும்பு list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_கோவை (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

நிலையான மரம்
c_parser_omp_clause_simdlen (c_parser *parser, மரம் list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  மரம் c, t = NULL_மரம், type = NULL_மரம், வகுஎண் = NULL_மரம்;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  unsigned pos = 3;
  எனில் (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு),
		 "scaled") == 0
      && c_parser_check_balanced_raw_token_sequence (parser, &pos)
      && c_parser_peek_nth_token_raw (parser, ++pos)->type == CPP_COLON)
    {
      c_parser_consume_token (parser);
      matching_parens parens2;
      parens2.require_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      கட்டமைப்பு c_type_name *ctype = c_parser_type_name (parser);
      எனில் (ctype == வெற்று
	  || (type = groktypename (ctype, வெற்று, வெற்று)) == வெற்று
	  || (!INTEGRAL_TYPE_P (type)
	      && !SCALAR_FLOAT_TYPE_P (type)
	      && மரம்_CODE (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_முனை;
	}
      இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	  கோவை = convert_lvalue_to_rvalue (loc, கோவை, பொய், உண்மை);
	  வகுஎண் = கோவை.மதிப்பு;
	  வகுஎண் = c_fully_fold (வகுஎண், பொய், வெற்று);
	  எனில் (மரம்_CODE (வகுஎண்) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (மரம்_TYPE (வகுஎண்))
	      || மரம்_int_cst_sgn (வகுஎண்) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_முனை;
	    }
	}
      parens2.skip_until_found_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  எனில் (type != error_mark_முனை)
    {
      location_t கோவை_loc = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
      t = கோவை.மதிப்பு;
      t = c_fully_fold (t, பொய், வெற்று);
      எனில் (மரம்_CODE (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (மரம்_TYPE (t))
	  || மரம்_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_மரம்;
	}
    }

  parens.skip_until_found_close (parser);
  எனில் (type == error_mark_முனை || t == NULL_மரம் || t == error_mark_முனை)
    திரும்பு list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_கோவை (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_வகுஎண் (c) = வகுஎண்;
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

நிலையான மரம்
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   மரம் list, தருக்க depend_p)
{
  மரம் vec = வெற்று;
  எனில் (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      திரும்பு list;
    }

  எனில் (!depend_p)
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_எண்
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  மரம் val = c_parser_peek_nth_token (parser, 3)->மதிப்பு;
	  எனில் (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      மரம் u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      திரும்பு u;
	    }
	}
    }



  போது (c_parser_next_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_kind == C_ID_ID)
    {
      மரம் t = lookup_name (c_parser_peek_token (parser)->மதிப்பு);
      மரம் addend = வெற்று;

      எனில் (t == NULL_மரம்)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->மதிப்பு);
	  t = error_mark_முனை;
	}

      c_parser_consume_token (parser);

      தருக்க neg = பொய்;
      எனில் (c_parser_next_token_is (parser, CPP_MINUS))
	neg = உண்மை;
      இல்லையெனில் எனில் (!c_parser_next_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_முனை;
	  neg = பொய்;
	  செல் add_to_vector;
	}
      c_parser_consume_token (parser);

      எனில் (c_parser_next_token_is_not (parser, CPP_எண்))
	{
	  c_parser_error (parser, "expected integer");
	  திரும்பு list;
	}

      addend = c_parser_peek_token (parser)->மதிப்பு;
      எனில் (மரம்_CODE (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  திரும்பு list;
	}
      c_parser_consume_token (parser);

    add_to_vector:
      எனில் (t != error_mark_முனை)
	{
	  vec = மரம்_cons (addend, t, vec);
	  எனில் (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      எனில் (c_parser_next_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_kind != C_ID_ID)
	நிறுத்து;

      c_parser_consume_token (parser);
    }

  எனில் (vec == NULL_மரம்)
    திரும்பு list;

  மரம் u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
  OMP_CLAUSE_DOACROSS_DEPEND (u) = depend_p;
  OMP_CLAUSE_DECL (u) = nreverse (vec);
  OMP_CLAUSE_CHAIN (u) = list;
  திரும்பு u;
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

நிலையான மரம்
c_parser_omp_iterators (c_parser *parser)
{
  மரம் ret = NULL_மரம், *last = &ret;
  c_parser_consume_token (parser);

  தள்ளு_scope ();

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு error_mark_முனை;

  செய்
    {
      மரம் iter_type = NULL_மரம், type_கோவை = NULL_மரம்;
      எனில் (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
	{
	  கட்டமைப்பு c_type_name *type = c_parser_type_name (parser);
	  எனில் (type != வெற்று)
	    iter_type = groktypename (type, &type_கோவை, வெற்று);
	}
      எனில் (iter_type == NULL_மரம்)
	iter_type = integer_type_முனை;

      location_t loc = c_parser_peek_token (parser)->location;
      எனில் (!c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  நிறுத்து;
	}

      மரம் id = c_parser_peek_token (parser)->மதிப்பு;
      c_parser_consume_token (parser);

      எனில் (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	நிறுத்து;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (eloc, கோவை, உண்மை, பொய்);
      மரம் begin = கோவை.மதிப்பு;

      எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	நிறுத்து;

      eloc = c_parser_peek_token (parser)->location;
      கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (eloc, கோவை, உண்மை, பொய்);
      மரம் end = கோவை.மதிப்பு;

      மரம் step = integer_one_முனை;
      எனில் (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	  கோவை = convert_lvalue_to_rvalue (eloc, கோவை, உண்மை, பொய்);
	  step = கோவை.மதிப்பு;
	}

      மரம் iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *last = make_omp_iterator ();
      OMP_ITERATOR_VAR (*last) = iter_var;
      OMP_ITERATOR_BEGIN (*last) = begin;
      OMP_ITERATOR_END (*last) = end;
      OMP_ITERATOR_STEP (*last) = step;
      last = &மரம்_CHAIN (*last);

      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  தொடர்;
	}
      நிறுத்து;
    }
  போது (1);

  parens.skip_until_found_close (parser);
  திரும்பு ret ? ret : error_mark_முனை;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

நிலையான மரம்
c_parser_omp_clause_affinity (c_parser *parser, மரம் list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  மரம் nl, iterators = NULL_மரம்;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      தருக்க parse_iter = ((strcmp ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      எனில் (parse_iter)
	{
	  unsigned n = 3;
	  parse_iter = (c_parser_check_balanced_raw_token_sequence (parser, &n)
			&& (c_parser_peek_nth_token_raw (parser, n)->type
			    == CPP_CLOSE_PAREN)
			&& (c_parser_peek_nth_token_raw (parser, n + 1)->type
			    == CPP_COLON));
	}
      எனில் (parse_iter)
	{
	  iterators = c_parser_omp_iterators (parser);
	  எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    {
	      எனில் (iterators)
		எடு_scope ();
	      parens.skip_until_found_close (parser);
	      திரும்பு list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  எனில் (iterators)
    {
      மரம் block = எடு_scope ();
      எனில் (iterators != error_mark_முனை)
	{
	  OMP_ITERATOR_BLOCK (iterators) = block;
	  க்கு (மரம் c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_மரம்_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  திரும்பு nl;
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

நிலையான மரம்
c_parser_omp_clause_depend (c_parser *parser, மரம் list, location_t here)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  எண்ணிக்கை omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_LAST;
  எண்ணிக்கை omp_clause_doacross_kind dkind = OMP_CLAUSE_DOACROSS_LAST;
  மரம் nl, c, iterators = NULL_மரம்;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  செய்
    {
      எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
	செல் invalid_kind;

      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp ("iterator", p) == 0 && iterators == NULL_மரம்)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  தொடர்;
	}
      எனில் (strcmp ("in", p) == 0)
	kind = OMP_CLAUSE_DEPEND_IN;
      இல்லையெனில் எனில் (strcmp ("inout", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUT;
      இல்லையெனில் எனில் (strcmp ("inoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUTSET;
      இல்லையெனில் எனில் (strcmp ("mutexinoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      இல்லையெனில் எனில் (strcmp ("out", p) == 0)
	kind = OMP_CLAUSE_DEPEND_OUT;
      இல்லையெனில் எனில் (strcmp ("depobj", p) == 0)
	kind = OMP_CLAUSE_DEPEND_DEPOBJ;
      இல்லையெனில் எனில் (strcmp ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      இல்லையெனில் எனில் (strcmp ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SOURCE;
	}
      இல்லையெனில்
	செல் invalid_kind;
      நிறுத்து;
    }
  போது (1);

  c_parser_consume_token (parser);

  எனில் (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_SOURCE
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      எடு_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_SOURCE ? "source" : "sink");
      iterators = NULL_மரம்;
    }

  எனில் (dkind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_மரம்;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_found_close (parser);
      திரும்பு c;
    }

  எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    செல் resync_fail;

  எனில் (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, உண்மை);
  இல்லையெனில்
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      எனில் (iterators)
	{
	  மரம் block = எடு_scope ();
	  எனில் (iterators == error_mark_முனை)
	    iterators = NULL_மரம்;
	  இல்லையெனில்
	    OMP_ITERATOR_BLOCK (iterators) = block;
	}

      க்கு (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_KIND (c) = kind;
	  எனில் (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_மரம்_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  திரும்பு nl;

 invalid_kind:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  எனில் (iterators)
    எடு_scope ();
  திரும்பு list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

நிலையான மரம்
c_parser_omp_clause_doacross (c_parser *parser, மரம் list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  எண்ணிக்கை omp_clause_doacross_kind kind = OMP_CLAUSE_DOACROSS_LAST;
  மரம் nl;
  மாறிலி எழுத்து *p;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  எனில் (c_parser_next_token_is_not (parser, CPP_NAME))
    செல் invalid_kind;

  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
  எனில் (strcmp ("sink", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SINK;
  இல்லையெனில் எனில் (strcmp ("source", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SOURCE;
  இல்லையெனில்
    செல் invalid_kind;

  c_parser_consume_token (parser);

  எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    செல் resync_fail;

  எனில் (kind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      எனில் (c_parser_next_token_is (parser, CPP_NAME)
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (nl) = OMP_CLAUSE_DOACROSS_SOURCE;
      OMP_CLAUSE_DECL (nl) = NULL_மரம்;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  இல்லையெனில்
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, பொய்);

  parens.skip_until_found_close (parser);
  திரும்பு nl;

 invalid_kind:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  திரும்பு list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

நிலையான மரம்
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, மரம் list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  எண்ணிக்கை omp_clause_fallback_kind kind = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  unsigned n = 3;
  எனில் (c_parser_next_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  திரும்பு list;
	}
      c_parser_consume_token (parser);
      எனில் (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	திரும்பு list;
      p = "";
      எனில் (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp (p, "abort") == 0)
	kind = OMP_CLAUSE_FALLBACK_ABORT;
      இல்லையெனில் எனில் (strcmp (p, "default_mem") == 0)
	kind = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      இல்லையெனில் எனில் (strcmp (p, "null") == 0)
	kind = OMP_CLAUSE_FALLBACK_NULL;
      இல்லையெனில்
	{
	  c_parser_error (parser, "expected %<abort%>, %<default_mem%>, or "
				  "%<null%> as fallback mode");
	  திரும்பு list;
	}
      c_parser_consume_token (parser);
      எனில் (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	திரும்பு list;
      எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	திரும்பு list;
    }
  location_t கோவை_loc = c_parser_peek_token (parser)->location;
  c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
  கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
  மரம் size = c_fully_fold (கோவை.மதிப்பு, பொய், வெற்று);
  parens.skip_until_found_close (parser);

  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (size)))
    {
      error_at (கோவை_loc, "expected integer expression");
      திரும்பு list;
    }

  /* Attempt to statically determine when the number is negative.  */
  மரம் c = fold_build2_loc (கோவை_loc, LT_கோவை, boolean_type_முனை, size,
			    build_int_cst (மரம்_TYPE (size), 0));
  protected_set_கோவை_location (c, கோவை_loc);
  எனில் (c == boolean_true_முனை)
    {
      warning_at (கோவை_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      size = integer_zero_முனை;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_KIND (c) = kind;
  OMP_CLAUSE_DYN_GROUPPRIVATE_கோவை (c) = size;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  திரும்பு list;
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

நிலையான மரம்
c_parser_omp_clause_map (c_parser *parser, மரம் list, தருக்க declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  மரம் nl, c;
  எண்ணிக்கை gomp_map_kind kind = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  முழு pos = 1;
  முழு map_kind_pos = 0;
  முழு iterator_length = 0;
  க்கு (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      எனில் (tok->type != CPP_NAME)
	நிறுத்து;

      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (tok->மதிப்பு);
      c_token *next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      எனில் (strcmp (p, "iterator") == 0 && next_tok->type == CPP_OPEN_PAREN)
	{
	  unsigned n = pos + 2;
	  எனில் (c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_length = n - pos + 1;
	      pos = n;
	      next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      எனில் (next_tok->type == CPP_COLON)
	{
	  map_kind_pos = pos;
	  நிறுத்து;
	}

      எனில் (next_tok->type == CPP_COMMA)
	pos++;
      இல்லையெனில் எனில் (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  unsigned முழு npos = pos + 2;
	  எனில் (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, npos + 1)->type
		  == CPP_COMMA))
	    pos = npos + 1;
	}

      pos++;
    }

  முழு always_modifier = 0;
  முழு close_modifier = 0;
  முழு present_modifier = 0;
  முழு mapper_modifier = 0;
  முழு இலக்கம்_commas = 0;
  முழு இலக்கம்_identifiers = 0;
  மரம் mapper_name = NULL_மரம்;
  மரம் iterators = NULL_மரம்;
  க்கு (முழு pos = 1; pos < map_kind_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      எனில் (tok->type == CPP_COMMA)
	{
	  ++இலக்கம்_commas;
	  எனில் (இலக்கம்_commas > இலக்கம்_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  தொடர்;
	}

      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (tok->மதிப்பு);
      எனில் (strcmp ("always", p) == 0)
	{
	  எனில் (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_found_close (parser);
	      திரும்பு list;
	    }
	  always_modifier++;
	  c_parser_consume_token (parser);
	}
      இல்லையெனில் எனில் (strcmp ("close", p) == 0)
	{
	  எனில் (close_modifier)
	    {
	      c_parser_error (parser, "too many %<close%> modifiers");
	      parens.skip_until_found_close (parser);
	      திரும்பு list;
	    }
	  close_modifier++;
	  c_parser_consume_token (parser);
	}
      இல்லையெனில் எனில் (strcmp ("iterator", p) == 0)
	{
	  எனில் (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      திரும்பு list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      இல்லையெனில் எனில் (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  எனில் (mparens.require_open (parser))
	    {
	      எனில் (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  திரும்பு list;
		}

	      tok = c_parser_peek_token (parser);

	      தேர்வு (tok->type)
		{
		நிலை CPP_NAME:
		  {
		    mapper_name = tok->மதிப்பு;
		    c_parser_consume_token (parser);
		    எனில் (declare_mapper_p)
		      {
			error_at (tok->location,
				  "in %<declare mapper%> directives, parameter "
				  "to %<mapper%> modifier must be %<default%>");
		      }
		  }
		  நிறுத்து;

		நிலை CPP_KEYWORD:
		  எனில் (tok->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      நிறுத்து;
		    }
		  /* Fallthrough.  */

		இயல்பு:
		  error_at (tok->location,
			    "expected identifier or %<default%>");
		  திரும்பு list;
		}

	      எனில் (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  திரும்பு list;
		}

	      mapper_modifier++;
	      pos += 3;
	    }
	}
      இல்லையெனில் எனில் (strcmp ("present", p) == 0)
	{
	  எனில் (present_modifier)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      திரும்பு list;
	    }
	  present_modifier++;
	  c_parser_consume_token (parser);
	}
      இல்லையெனில்
	{
	  c_parser_error (parser, "%<map%> clause with map-type modifier other "
				  "than %<always%>, %<close%>, %<iterator%>, "
				  "%<mapper%> or %<present%>");
	  parens.skip_until_found_close (parser);
	  திரும்பு list;
	}
      ++இலக்கம்_identifiers;
      எனில் (இலக்கம்_identifiers - 1 > இலக்கம்_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_செருகு_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      இலக்கம்_commas = இலக்கம்_identifiers - 1;
    }

  எனில் (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      முழு always_present_modifier = always_modifier && present_modifier;

      எனில் (strcmp ("alloc", p) == 0)
	kind = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      இல்லையெனில் எனில் (strcmp ("to", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TO
		: present_modifier ? GOMP_MAP_PRESENT_TO
		: always_modifier ? GOMP_MAP_ALWAYS_TO
		: GOMP_MAP_TO);
      இல்லையெனில் எனில் (strcmp ("from", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      இல்லையெனில் எனில் (strcmp ("tofrom", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      இல்லையெனில் எனில் (strcmp ("release", p) == 0)
	kind = GOMP_MAP_RELEASE;
      இல்லையெனில் எனில் (strcmp ("delete", p) == 0)
	kind = GOMP_MAP_DELETE;
      இல்லையெனில்
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  திரும்பு list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   உண்மை);

  மரம் last_new = NULL_மரம்;

  எனில் (iterators)
    {
      மரம் block = எடு_scope ();
      எனில் (iterators == error_mark_முனை)
	iterators = NULL_மரம்;
      இல்லையெனில்
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  க்கு (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      last_new = c;
    }

  எனில் (mapper_name)
    {
      மரம் name = build_omp_clause (உள்ளீடு_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_தள்ளு_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (உள்ளீடு_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_எடு_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_முனை;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  parens.skip_until_found_close (parser);
  திரும்பு nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

நிலையான மரம்
c_parser_omp_clause_device (c_parser *parser, மரம் list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t கோவை_loc;
  c_கோவை கோவை;
  மரம் c, t;
  தருக்க ancestor = பொய்;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  எனில் (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (tok->மதிப்பு);
      எனில் (strcmp ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  எனில் ((omp_requires_mask & OMP_REQUIRES_REVERSE_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_found_close (parser);
	      திரும்பு list;
	    }
	  ancestor = உண்மை;
	}
      இல்லையெனில் எனில் (strcmp ("device_num", p) == 0)
	;
      இல்லையெனில்
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_found_close (parser);
	  திரும்பு list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  கோவை_loc = c_parser_peek_token (parser)->location;
  கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
  கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
  t = கோவை.மதிப்பு;
  t = c_fully_fold (t, பொய், வெற்று);

  parens.skip_until_found_close (parser);

  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      திரும்பு list;
    }
  எனில் (ancestor && மரம்_CODE (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (கோவை_loc, "the %<device%> clause expression must evaluate to "
			  "%<1%>");
      திரும்பு list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE, "device");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE);

  OMP_CLAUSE_DEVICE_ID (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEVICE_ANCESTOR (c) = ancestor;

  list = c;
  திரும்பு list;
}

/* OpenMP 4.0:
   dist_schedule ( static )
   dist_schedule ( static , expression ) */

நிலையான மரம்
c_parser_omp_clause_dist_schedule (c_parser *parser, மரம் list)
{
  மரம் c, t = NULL_மரம்;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  எனில் (!c_parser_next_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      திரும்பு list;
    }

  c_parser_consume_token (parser);
  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t கோவை_loc = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
      t = கோவை.மதிப்பு;
      t = c_fully_fold (t, பொய், வெற்று);
      parens.skip_until_found_close (parser);
    }
  இல்லையெனில்
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  எனில் (omp_find_clause (list, OMP_CLAUSE_DIST_SCHEDULE))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  எனில் (t == error_mark_முனை)
    திரும்பு list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_SCHEDULE);
  OMP_CLAUSE_DIST_SCHEDULE_CHUNK_கோவை (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

நிலையான மரம்
c_parser_omp_clause_proc_bind (c_parser *parser, மரம் list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  எண்ணிக்கை omp_clause_proc_bind_kind kind;
  மரம் c;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp ("primary", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_PRIMARY;
      இல்லையெனில் எனில் (strcmp ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  kind = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      இல்லையெனில் எனில் (strcmp ("close", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_CLOSE;
      இல்லையெனில் எனில் (strcmp ("spread", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_SPREAD;
      இல்லையெனில்
	செல் invalid_kind;
    }
  இல்லையெனில்
    செல் invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;

 invalid_kind:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_found_close (parser);
  திரும்பு list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

நிலையான மரம்
c_parser_omp_clause_device_type (c_parser *parser, மரம் list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  எண்ணிக்கை omp_clause_device_type_kind kind;
  மரம் c;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp ("host", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_HOST;
      இல்லையெனில் எனில் (strcmp ("nohost", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      இல்லையெனில் எனில் (strcmp ("any", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_ANY;
      இல்லையெனில்
	செல் invalid_kind;
    }
  இல்லையெனில்
    செல் invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;

 invalid_kind:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_found_close (parser);
  திரும்பு list;
}

/* OpenMP 4.0:
   from ( variable-list )
   to ( variable-list )

   OpenMP 5.1:
   from ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )
   to ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )

   motion-modifier:
     present | iterator (iterators-definition) | mapper (id)  */

நிலையான மரம்
c_parser_omp_clause_from_to (c_parser *parser, எண்ணிக்கை omp_clause_code kind,
			     மரம் list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  முழு pos = 1, colon_pos = 0;
  முழு iterator_length = 0;

  போது (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      மாறிலி எழுத்து *identifier =
	IDENTIFIER_POINTER (c_parser_peek_nth_token_raw (parser, pos)->மதிப்பு);
      எனில் (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  unsigned முழு npos = pos + 2;
	  எனில் (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      எனில் (strcmp (identifier, "iterator") == 0)
		iterator_length = npos - pos + 1;
	      pos = npos;
	    }
	}
      எனில் (c_parser_peek_nth_token_raw (parser, pos + 1)->type == CPP_COMMA)
	pos += 2;
      இல்லையெனில்
	pos++;
      எனில் (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_COLON)
	{
	  colon_pos = pos;
	  நிறுத்து;
	}
    }

  தருக்க present = பொய், mapper_modifier = பொய்;
  மரம் iterators = NULL_மரம்;
  மரம் mapper_name = NULL_மரம்;

  க்கு (முழு pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      எனில் (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  தொடர்;
	}
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (token->மதிப்பு);
      எனில் (strcmp ("present", p) == 0)
	{
	  எனில் (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      திரும்பு list;
	    }
	  present = உண்மை;
	  c_parser_consume_token (parser);
	}
      இல்லையெனில் எனில் (strcmp ("iterator", p) == 0)
	{
	  எனில் (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      திரும்பு list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      இல்லையெனில் எனில் (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  எனில் (mparens.require_open (parser))
	    {
	      எனில் (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  திரும்பு list;
		}

	      token = c_parser_peek_token (parser);
	      தேர்வு (token->type)
		{
		நிலை CPP_NAME:
		  {
		    mapper_name = token->மதிப்பு;
		    c_parser_consume_token (parser);
		  }
		  நிறுத்து;
		நிலை CPP_KEYWORD:
		  எனில் (token->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      நிறுத்து;
		    }
		  /* FALLTHROUGH  */
		இயல்பு:
		  error_at (token->location,
			    "expected identifier or %<default%>");
		  திரும்பு list;
		}
	      எனில் (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  திரும்பு list;
		}
	      mapper_modifier = உண்மை;
	      pos += 3;
	    }
	}
      இல்லையெனில்
	{
	  error_at (token->location,
		    "%qs clause with modifier other than %<iterator%>, "
		    "%<mapper%>, or %<present%>",
		    kind == OMP_CLAUSE_TO ? "to" : "from");
	  parens.skip_until_found_close (parser);
	  திரும்பு list;
	}
    }

  எனில் (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  மரம் nl = c_parser_omp_variable_list (parser, loc, kind, list);
  parens.skip_until_found_close (parser);

  எனில் (present)
    க்கு (மரம் c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  எனில் (iterators)
    {
      மரம் block = எடு_scope ();
      எனில் (iterators == error_mark_முனை)
	iterators = NULL_மரம்;
      இல்லையெனில்
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  எனில் (iterators)
    க்கு (மரம் c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  எனில் (mapper_name)
    {
      மரம் last_new = NULL_மரம்;
      க்கு (மரம் c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	last_new = c;

      மரம் name = build_omp_clause (உள்ளீடு_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_தள்ளு_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (உள்ளீடு_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_எடு_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_முனை;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  திரும்பு nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

நிலையான மரம்
c_parser_omp_clause_uniform (c_parser *parser, மரம் list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_UNIFORM,
					 list);
      parens.skip_until_found_close (parser);
    }
  திரும்பு list;
}

/* OpenMP 5.1
   full */

நிலையான மரம்
c_parser_omp_clause_full (c_parser *parser, மரம் list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_FULL, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  மரம் c = build_omp_clause (loc, OMP_CLAUSE_FULL);
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

நிலையான மரம்
c_parser_omp_clause_partial (c_parser *parser, மரம் list)
{
  மரம் இலக்கம் = NULL_மரம்;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      இலக்கம் = c_parser_கோவை_no_commas (parser, வெற்று).மதிப்பு;
      parens.skip_until_found_close (parser);

      எனில் (இலக்கம் == error_mark_முனை)
	திரும்பு list;

      mark_exp_read (இலக்கம்);
      இலக்கம் = c_fully_fold (இலக்கம், பொய், வெற்று);
      HOST_WIDE_INT n;
      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (இலக்கம்))
	  || !மரம்_fits_shwi_p (இலக்கம்)
	  || (n = மரம்_to_shwi (இலக்கம்)) <= 0
	  || (முழு) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  திரும்பு list;
	}
    }

  மரம் c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_கோவை (c) = இலக்கம்;
  OMP_CLAUSE_CHAIN (c) = list;
  திரும்பு c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

நிலையான மரம்
c_parser_omp_clause_novariants (c_parser *parser, மரம் list)
{
  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
  மரம் t = convert_lvalue_to_rvalue (loc, கோவை, உண்மை, உண்மை).மதிப்பு;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, பொய், வெற்று);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  மரம் c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_கோவை (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  திரும்பு list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

நிலையான மரம்
c_parser_omp_clause_nocontext (c_parser *parser, மரம் list)
{
  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
  மரம் t = convert_lvalue_to_rvalue (loc, கோவை, உண்மை, உண்மை).மதிப்பு;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, பொய், வெற்று);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  மரம் c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_கோவை (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  திரும்பு list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

நிலையான மரம்
c_parser_omp_clause_detach (c_parser *parser, மரம் list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  எனில் (!parens.require_open (parser))
    திரும்பு list;

  எனில் (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_found_close (parser);
      திரும்பு list;
    }

  மரம் t = lookup_name (c_parser_peek_token (parser)->மதிப்பு);
  எனில் (t == NULL_மரம்)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->மதிப்பு);
      parens.skip_until_found_close (parser);
      திரும்பு list;
    }
  c_parser_consume_token (parser);

  மரம் type = TYPE_MAIN_VARIANT (மரம்_TYPE (t));
  எனில் (!INTEGRAL_TYPE_P (type)
      || மரம்_CODE (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_found_close (parser);
      திரும்பு list;
    }

  மரம் u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_found_close (parser);
  திரும்பு u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

நிலையான மரம்
c_parser_omp_clause_destroy (c_parser *parser, மரம் list)
{
  மரம் nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  க்கு (மரம் c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    மரம்_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
  திரும்பு nl;
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

நிலையான மரம்
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  எனில் (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    திரும்பு error_mark_முனை;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  எனில் (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    போது (உண்மை)
      {
	str += (எழுத்து) GOMP_INTEROP_IFR_SEPARATOR;
	எனில் (c_parser_next_token_is (parser, CPP_STRING))
	  {
	    c_கோவை cval = c_parser_string_literal (parser, பொய், பொய்);
	    எனில் (cval.மதிப்பு == error_mark_முனை)
	      திரும்பு error_mark_முனை;
	    எனில் ((size_t) மரம்_STRING_LENGTH (cval.மதிப்பு)
		!= strlen (மரம்_STRING_POINTER (cval.மதிப்பு)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = உண்மை;
		திரும்பு error_mark_முனை;
	      }

	    எழுத்து c = omp_get_fr_id_from_name (மரம்_STRING_POINTER (cval.மதிப்பு));
	    எனில் (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  மரம்_STRING_POINTER (cval.மதிப்பு));
	    str += c;
	  }
	இல்லையெனில்
	  {
	    c_கோவை cval = c_parser_கோவை_no_commas (parser, வெற்று);
	    மரம் மதிப்பு = c_fully_fold (cval.மதிப்பு, பொய், வெற்று);
	    எனில் (INTEGRAL_TYPE_P (மரம்_TYPE (மதிப்பு))
		&& மரம்_CODE (மதிப்பு) != INTEGER_CST)
	      மதிப்பு = convert_lvalue_to_rvalue (cval.get_start (), cval,
						பொய், உண்மை).மதிப்பு;
	    எனில் (மரம்_CODE (மதிப்பு) != INTEGER_CST
		|| !மரம்_fits_shwi_p (மதிப்பு))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		திரும்பு error_mark_முனை;
	      }
	    HOST_WIDE_INT n = மரம்_to_shwi (மதிப்பு);
	    எனில் (n < 1 || n > GOMP_INTEROP_IFR_LAST)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (எழுத்து) n;
	  }
	str += (எழுத்து) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    தொடர்;
	  }
	எனில் (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  திரும்பு error_mark_முனை;
	str += '\0';
	மரம் res = build_string (str.length (), str.data ());
	மரம்_TYPE (res) = build_array_type_nelts (unsigned_char_type_முனை,
						  str.length ());
	திரும்பு res;
      }

  /* New format. */
  std::string str2;
  போது (உண்மை)
    {
      எனில் (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	திரும்பு error_mark_முனை;
      str += (எழுத்து) GOMP_INTEROP_IFR_SEPARATOR;
      str2.clear ();
      தருக்க has_fr = பொய்;
      போது (உண்மை)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  எனில் (tok->type != CPP_NAME
	      || (strcmp("fr", IDENTIFIER_POINTER (tok->மதிப்பு)) != 0
		  && strcmp("attr", IDENTIFIER_POINTER (tok->மதிப்பு)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      திரும்பு error_mark_முனை;
	    }
	  c_parser_consume_token (parser);
	  தருக்க is_fr = IDENTIFIER_POINTER (tok->மதிப்பு)[0] == 'f';
	  எனில் (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      திரும்பு error_mark_முனை;
	    }
	  எனில் (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    திரும்பு error_mark_முனை;
	  போது (உண்மை)
	    {
	      எனில் (c_parser_next_token_is (parser, CPP_STRING))
		{
		  c_கோவை cval = c_parser_string_literal (parser, பொய், பொய்);
		  மரம் மதிப்பு = cval.மதிப்பு;
		  எனில் (மதிப்பு == error_mark_முனை)
		    திரும்பு error_mark_முனை;
		  எனில் ((size_t) மரம்_STRING_LENGTH (மதிப்பு)
		      != strlen (மரம்_STRING_POINTER (மதிப்பு)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = உண்மை;
		      திரும்பு error_mark_முனை;
		    }
		  எனில் (!is_fr)
		    {
		      எனில் (!startswith (மரம்_STRING_POINTER (மதிப்பு), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = உண்மை;
			  திரும்பு error_mark_முனை;
			}
		      எனில் (strchr (மரம்_STRING_POINTER (மதிப்பு), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = உண்மை;
			  திரும்பு error_mark_முனை;
			}
		      str2 += மரம்_STRING_POINTER (மதிப்பு);
		      str2 += '\0';
		    }
		  இல்லையெனில்
		    {
		      எனில் (*மரம்_STRING_POINTER (மதிப்பு) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  திரும்பு error_mark_முனை;
			}
		      எழுத்து c = omp_get_fr_id_from_name (மரம்_STRING_POINTER (மதிப்பு));
		      எனில் (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    மரம்_STRING_POINTER (மதிப்பு));
		     str += c;
		     has_fr = உண்மை;
		    }
		}
	      இல்லையெனில் எனில் (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  திரும்பு error_mark_முனை;
		}
	      இல்லையெனில்
		{
		  c_கோவை cval = c_parser_கோவை_no_commas (parser, வெற்று);
		  மரம் மதிப்பு = c_fully_fold (cval.மதிப்பு, பொய், வெற்று);
		  எனில் (INTEGRAL_TYPE_P (மரம்_TYPE (மதிப்பு))
		      && மரம்_CODE (மதிப்பு) != INTEGER_CST)
		    மதிப்பு = convert_lvalue_to_rvalue (cval.get_start (), cval,
						      பொய், உண்மை).மதிப்பு;

		  எனில் (மரம்_CODE (மதிப்பு) != INTEGER_CST
		      || !மரம்_fits_shwi_p (மதிப்பு))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      திரும்பு error_mark_முனை;
		    }
		  HOST_WIDE_INT n = மரம்_to_shwi (மதிப்பு);
		  எனில் (n < 1 || n > GOMP_INTEROP_IFR_LAST)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (எழுத்து) n;
		  has_fr = உண்மை;
		}
	      எனில் (!is_fr
		  && c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  தொடர்;
		}
	      எனில் (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		திரும்பு error_mark_முனை;
	      நிறுத்து;
	    }
	  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      தொடர்;
	    }
	  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    நிறுத்து;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  திரும்பு error_mark_முனை;
	}
      str += (எழுத்து) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	நிறுத்து;
      எனில் (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	திரும்பு error_mark_முனை;
    }
  c_parser_consume_token (parser);
  str += '\0';
  மரம் res = build_string (str.length (), str.data ());
  மரம்_TYPE (res) = build_array_type_nelts (unsigned_char_type_முனை,
						  str.length ());
  திரும்பு res;
}

/* OpenMP 5.1
     modifiers of the 'init' clause, used by the 'init' and the
     'append_args' clauses.

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification)

  Returns 'false' if an error has been issued.  */

நிலையான தருக்க
c_parser_omp_clause_init_modifiers (c_parser *parser, தருக்க *target,
				    தருக்க *targetsync, மரம் *prefer_type_மரம்)
{
  *target = பொய்;
  *targetsync = பொய்;
  *prefer_type_மரம் = NULL_மரம்;

  செய்
    {
      c_token *tok = c_parser_peek_token (parser);
      எனில் (tok->type != CPP_NAME)
	செல் fail;
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (tok->மதிப்பு);
      எனில் (strcmp ("targetsync", p) == 0)
	{
	  எனில் (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = உண்மை;
	  c_parser_consume_token (parser);
	}
      இல்லையெனில் எனில் (strcmp ("target", p) == 0)
	{
	  எனில் (*target)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *target = உண்மை;
	  c_parser_consume_token (parser);
	}
      இல்லையெனில் எனில் (strcmp ("prefer_type", p) == 0)
	{
	  எனில் (*prefer_type_மரம் != NULL_மரம்)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_மரம் = c_parser_omp_modifier_prefer_type (parser);
	  எனில் (*prefer_type_மரம் == error_mark_முனை)
	    திரும்பு பொய்;
	}
      இல்லையெனில்
	செல் fail;
      tok = c_parser_peek_token (parser);
      எனில் (tok->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  தொடர்;
	}
      /* Unknown token - either done or an error; handle it in the caller.  */
      திரும்பு உண்மை;
    }
  போது (உண்மை);

fail:
  c_parser_error (parser,
		  "expected %<prefer_type%>, %<target%>, or %<targetsync%>");
  திரும்பு பொய்;
}

/* OpenMP 5.1:
   init ( [init-modifier-list : ] variable-list )

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification) */

நிலையான மரம்
c_parser_omp_clause_init (c_parser *parser, மரம் list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு list;

  தருக்க target = பொய்;
  தருக்க targetsync = பொய்;
  மரம் prefer_type_மரம் = NULL_மரம்;

  எனில் (!c_parser_omp_clause_init_modifiers (parser, &target, &targetsync,
					   &prefer_type_மரம்)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      எனில் (prefer_type_மரம் != error_mark_முனை)
	parens.skip_until_found_close (parser);
      திரும்பு list;
    }

  எனில் (!target && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  மரம் nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					பொய்);
  parens.skip_until_found_close (parser);

  க்கு (மரம் c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      மரம்_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      எனில் (target)
	OMP_CLAUSE_INIT_TARGET (c) = 1;
      எனில் (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      எனில் (prefer_type_மரம்)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_மரம்;
    }
  திரும்பு nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

நிலையான மரம்
c_parser_omp_clause_use (c_parser *parser, மரம் list)
{
  திரும்பு c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

நிலையான மரம்
c_parser_omp_clause_interop (c_parser *parser, மரம் list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  மரம் nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  க்கு (மரம் c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      மரம்_USED (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  திரும்பு nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

நிலையான மரம்
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_mask mask,
			   மாறிலி எழுத்து *where, தருக்க finish_p = உண்மை,
			   தருக்க target_p = பொய்)
{
  மரம் clauses = வெற்று;
  தருக்க first = உண்மை;

  போது (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      மாறிலி எழுத்து *c_name;
      மரம் prev = clauses;

      எனில் (!first && c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      தேர்வு (c_kind)
	{
	நிலை PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "attach";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copy";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyin";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyout";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "create";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "delete";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, உண்மை);
	  c_name = "default";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "detach";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_data_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device_resident";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_GANG,
						c_name, clauses);
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "host";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, பொய்);
	  c_name = "if";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "link";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "no_create";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_இலக்கம்_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_இலக்கம்_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_இலக்கம்_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_இலக்கம்_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "present";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     பொய், clauses);
	  c_name = "reduction";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_SELF:
	  எனில் ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  இல்லையெனில்
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "self";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_SEQ,
						 clauses);
	  c_name = "seq";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_TILE:
	  clauses = c_parser_oacc_clause_tile (parser, clauses);
	  c_name = "tile";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_USE_DEVICE:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_VECTOR:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_VECTOR,
						c_name,	clauses);
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_VECTOR_LENGTH:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_VECTOR_LENGTH,
						     clauses);
	  c_name = "vector_length";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  நிறுத்து;
	நிலை PRAGMA_OACC_CLAUSE_WORKER:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_WORKER,
						c_name, clauses);
	  நிறுத்து;
	இயல்பு:
	  c_parser_error (parser, "expected an OpenACC clause");
	  செல் saw_error;
	}

      first = பொய்;

      எனில் (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_to_pragma_eol (parser);

  எனில் (finish_p)
    திரும்பு c_finish_omp_clauses (clauses, target_p ? C_ORT_ACC_TARGET
						   : C_ORT_ACC);

  திரும்பு clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

நிலையான மரம்
c_parser_omp_all_clauses (c_parser *parser, omp_clause_mask mask,
			  மாறிலி எழுத்து *where, தருக்க finish_p = உண்மை,
			  முழு nested = 0)
{
  மரம் clauses = வெற்று;
  தருக்க first = உண்மை;

  போது (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      மாறிலி எழுத்து *c_name;
      மரம் prev = clauses;

      எனில் (nested && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	நிறுத்து;

      எனில் (!first || nested != 2)
	{
	  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  இல்லையெனில் எனில் (nested == 2)
	    error_at (c_parser_peek_token (parser)->location,
		      "clauses in %<simd%> trait should be separated "
		      "by %<,%>");
	}

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      தேர்வு (c_kind)
	{
	நிலை PRAGMA_OMP_CLAUSE_BIND:
	  clauses = c_parser_omp_clause_bind (parser, clauses);
	  c_name = "bind";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, பொய்);
	  c_name = "default";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_DETACH:
	  clauses = c_parser_omp_clause_detach (parser, clauses);
	  c_name = "detach";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_FILTER:
	  clauses = c_parser_omp_clause_filter (parser, clauses);
	  c_name = "filter";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_FINAL:
	  clauses = c_parser_omp_clause_final (parser, clauses);
	  c_name = "final";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_GRAINSIZE:
	  clauses = c_parser_omp_clause_grainsize (parser, clauses);
	  c_name = "grainsize";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_HINT:
	  clauses = c_parser_omp_clause_hint (parser, clauses);
	  c_name = "hint";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_DEFAULTMAP:
	  clauses = c_parser_omp_clause_defaultmap (parser, clauses);
	  c_name = "defaultmap";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, உண்மை);
	  c_name = "if";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_IN_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_IN_REDUCTION,
					     உண்மை, clauses);
	  c_name = "in_reduction";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_INDIRECT:
	  clauses = c_parser_omp_clause_indirect (parser, clauses);
	  c_name = "indirect";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_MERGEABLE:
	  clauses = c_parser_omp_clause_mergeable (parser, clauses);
	  c_name = "mergeable";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_இலக்கம்_TASKS:
	  clauses = c_parser_omp_clause_இலக்கம்_tasks (parser, clauses);
	  c_name = "num_tasks";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_இலக்கம்_THREADS:
	  clauses = c_parser_omp_clause_இலக்கம்_threads (parser, clauses);
	  c_name = "num_threads";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_ORDER:
	  clauses = c_parser_omp_clause_order (parser, clauses);
	  c_name = "order";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_PRIORITY:
	  clauses = c_parser_omp_clause_priority (parser, clauses);
	  c_name = "priority";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     உண்மை, clauses);
	  c_name = "reduction";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_SCHEDULE:
	  clauses = c_parser_omp_clause_schedule (parser, clauses);
	  c_name = "schedule";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     உண்மை, clauses);
	  c_name = "task_reduction";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_UNTIED:
	  clauses = c_parser_omp_clause_untied (parser, clauses);
	  c_name = "untied";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_INBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_INBRANCH,
						clauses);
	  c_name = "inbranch";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_NONTEMPORAL:
	  clauses = c_parser_omp_clause_nontemporal (parser, clauses);
	  c_name = "nontemporal";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_NOTINBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_NOTINBRANCH,
						clauses);
	  c_name = "notinbranch";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_PARALLEL:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_PARALLEL,
					      clauses);
	  c_name = "parallel";
	  எனில் (!first)
	    {
	     clause_not_first:
	      error_at (here, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = prev;
	    }
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  எனில் (!first)
	    செல் clause_not_first;
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  எனில் (!first)
	    செல் clause_not_first;
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  எனில் (!first)
	    செல் clause_not_first;
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_LINK:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LINK, clauses);
	  c_name = "link";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_LOCAL:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LOCAL, clauses);
	  c_name = "local";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_TO:
	  எனில் ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (here);
	      richloc.add_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      மரம் nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      க்கு (மரம் c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_TO (c) = 1;
	      clauses = nl;
	    }
	  இல்லையெனில்
	    clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_TO,
						   clauses);
	  c_name = "to";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_UNIFORM:
	  clauses = c_parser_omp_clause_uniform (parser, clauses);
	  c_name = "uniform";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_இலக்கம்_TEAMS:
	  clauses = c_parser_omp_clause_இலக்கம்_teams (parser, clauses);
	  c_name = "num_teams";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_THREAD_LIMIT:
	  clauses = c_parser_omp_clause_thread_limit (parser, clauses);
	  c_name = "thread_limit";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_ALIGNED:
	  clauses = c_parser_omp_clause_aligned (parser, clauses);
	  c_name = "aligned";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_ALLOCATE:
	  clauses = c_parser_omp_clause_allocate (parser, clauses);
	  c_name = "allocate";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_LINEAR:
	  clauses = c_parser_omp_clause_linear (parser, clauses);
	  c_name = "linear";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_USES_ALLOCATORS:
	  clauses = c_parser_omp_clause_uses_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, here);
	  c_name = "depend";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_DOACROSS:
	  clauses = c_parser_omp_clause_doacross (parser, clauses);
	  c_name = "doacross";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_DESTROY:
	  clauses = c_parser_omp_clause_destroy (parser, clauses);
	  c_name = "destroy";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE:
	  clauses = c_parser_omp_clause_dyn_groupprivate (parser, clauses);
	  c_name = "dyn_groupprivate";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_INIT:
	  clauses = c_parser_omp_clause_init (parser, clauses);
	  c_name = "init";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_USE:
	  clauses = c_parser_omp_clause_use (parser, clauses);
	  c_name = "use";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_INTEROP:
	  clauses = c_parser_omp_clause_interop (parser, clauses);
	  c_name = "interop";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_MAP:
	  clauses = c_parser_omp_clause_map (parser, clauses, பொய்);
	  c_name = "map";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device_ptr";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_use_device_addr (parser, clauses);
	  c_name = "use_device_addr";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_has_device_addr (parser, clauses);
	  c_name = "has_device_addr";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR:
	  clauses = c_parser_omp_clause_is_device_ptr (parser, clauses);
	  c_name = "is_device_ptr";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_DEVICE:
	  clauses = c_parser_omp_clause_device (parser, clauses);
	  c_name = "device";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_DIST_SCHEDULE:
	  clauses = c_parser_omp_clause_dist_schedule (parser, clauses);
	  c_name = "dist_schedule";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_PROC_BIND:
	  clauses = c_parser_omp_clause_proc_bind (parser, clauses);
	  c_name = "proc_bind";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_DEVICE_TYPE:
	  clauses = c_parser_omp_clause_device_type (parser, clauses);
	  c_name = "device_type";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_SAFELEN:
	  clauses = c_parser_omp_clause_safelen (parser, clauses);
	  c_name = "safelen";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_SIMDLEN:
	  clauses = c_parser_omp_clause_simdlen (parser, clauses);
	  c_name = "simdlen";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_NOGROUP:
	  clauses = c_parser_omp_clause_nogroup (parser, clauses);
	  c_name = "nogroup";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_THREADS:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_THREADS,
					       clauses);
	  c_name = "threads";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_SIMD:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_SIMD,
					       clauses);
	  c_name = "simd";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_ENTER:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					    clauses);
	  c_name = "enter";
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_FULL:
	  c_name = "full";
	  clauses = c_parser_omp_clause_full (parser, clauses);
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_PARTIAL:
	  c_name = "partial";
	  clauses = c_parser_omp_clause_partial (parser, clauses);
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_NOVARIANTS:
	  c_name = "novariants";
	  clauses = c_parser_omp_clause_novariants (parser, clauses);
	  நிறுத்து;
	நிலை PRAGMA_OMP_CLAUSE_NOCONTEXT:
	  c_name = "nocontext";
	  clauses = c_parser_omp_clause_nocontext (parser, clauses);
	  நிறுத்து;
	இயல்பு:
	  c_parser_error (parser, "expected an OpenMP clause");
	  செல் saw_error;
	}

      first = பொய்;

      எனில் (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  எனில் (!nested)
    c_parser_skip_to_pragma_eol (parser);

  எனில் (finish_p)
    {
      எனில் ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_UNIFORM)) != 0)
	திரும்பு c_finish_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      எனில் ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	திரும்பு c_finish_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      திரும்பு c_finish_omp_clauses (clauses, C_ORT_OMP);
    }

  திரும்பு clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

நிலையான மரம்
c_parser_omp_structured_block (c_parser *parser, தருக்க *if_p)
{
  மரம் stmt = தள்ளு_stmt_list ();
  parser->omp_attrs_forbidden_p = உண்மை;
  c_parser_statement (parser, if_p);
  திரும்பு எடு_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

நிலையான மரம்
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  மரம் stmt, clauses = NULL_மரம்;
  தருக்க readonly = பொய்;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      எனில் (token->type == CPP_NAME
	  && !strcmp (IDENTIFIER_POINTER (token->மதிப்பு), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = உண்மை;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_மரம்);
      parens.skip_until_found_close (parser);
    }

  எனில் (readonly)
    க்கு (மரம் c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_to_pragma_eol (parser);

  stmt = make_முனை (OACC_CACHE);
  மரம்_TYPE (stmt) = void_type_முனை;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  SET_கோவை_LOCATION (stmt, loc);
  add_stmt (stmt);

  திரும்பு stmt;
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

நிலையான மரம்
c_parser_oacc_data (location_t loc, c_parser *parser, தருக்க *if_p)
{
  மரம் stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_DATA_CLAUSE_MASK,
				       "#pragma acc data");

  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  stmt = c_finish_oacc_data (loc, clauses, block);

  திரும்பு stmt;
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

நிலையான வெறுமை
c_parser_oacc_declare (c_parser *parser)
{
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  மரம் clauses, stmt, t, decl;

  தருக்க error = பொய்;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_MASK,
				       "#pragma acc declare");
  எனில் (!clauses)
    {
      error_at (pragma_loc,
		"no valid clauses specified in %<#pragma acc declare%>");
      திரும்பு;
    }

  க்கு (t = clauses; t; t = OMP_CLAUSE_CHAIN (t))
    {
      location_t loc = OMP_CLAUSE_LOCATION (t);
      decl = OMP_CLAUSE_DECL (t);
      எனில் (!DECL_P (decl))
	{
	  error_at (loc, "array section in %<#pragma acc declare%>");
	  error = உண்மை;
	  தொடர்;
	}

      தேர்வு (OMP_CLAUSE_MAP_KIND (t))
	{
	நிலை GOMP_MAP_FIRSTPRIVATE_POINTER:
	நிலை GOMP_MAP_ALLOC:
	நிலை GOMP_MAP_TO:
	நிலை GOMP_MAP_FORCE_DEVICEPTR:
	நிலை GOMP_MAP_DEVICE_RESIDENT:
	  நிறுத்து;

	நிலை GOMP_MAP_LINK:
	  எனில் (!global_bindings_p ()
	      && (மரம்_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = உண்மை;
	      தொடர்;
	    }
	  நிறுத்து;

	இயல்பு:
	  எனில் (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = உண்மை;
	      தொடர்;
	    }
	  எனில் (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = உண்மை;
	      தொடர்;
	    }
	  இல்லையெனில் எனில் (மரம்_PUBLIC (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = உண்மை;
	      தொடர்;
	    }
	  நிறுத்து;
	}

      எனில் (!c_check_in_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = உண்மை;
	  தொடர்;
	}

      எனில் (lookup_attribute ("omp declare target", DECL_ATTRIBUTES (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_ATTRIBUTES (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = உண்மை;
	  தொடர்;
	}

      எனில் (!error)
	{
	  மரம் id;

	  எனில் (OMP_CLAUSE_MAP_KIND (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  இல்லையெனில்
	    id = get_identifier ("omp declare target");

	  DECL_ATTRIBUTES (decl)
			   = மரம்_cons (id, NULL_மரம், DECL_ATTRIBUTES (decl));

	  எனில் (global_bindings_p ())
	    {
	      symtab_முனை *முனை = symtab_முனை::get (decl);
	      எனில் (முனை != வெற்று)
		{
		  முனை->offloadable = 1;
		  எனில் (ENABLE_OFFLOADING)
		    {
		      g->have_offload = உண்மை;
		      எனில் (is_a <varpool_முனை *> (முனை))
			vec_safe_தள்ளு (offload_vars, decl);
		    }
		}
	    }
	}
    }

  எனில் (error || global_bindings_p ())
    திரும்பு;

  stmt = make_முனை (OACC_DECLARE);
  மரம்_TYPE (stmt) = void_type_முனை;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  SET_கோவை_LOCATION (stmt, pragma_loc);

  add_stmt (stmt);

  திரும்பு;
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

நிலையான வெறுமை
c_parser_oacc_enter_exit_data (c_parser *parser, தருக்க enter)
{
  location_t loc = c_parser_peek_token (parser)->location;
  மரம் clauses, stmt;
  மாறிலி எழுத்து *p = "";

  c_parser_consume_pragma (parser);

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      c_parser_consume_token (parser);
    }

  எனில் (strcmp (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = உண்மை;
      c_parser_skip_to_pragma_eol (parser);
      திரும்பு;
    }

  எனில் (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_DATA_CLAUSE_MASK,
					 "#pragma acc enter data");
  இல்லையெனில்
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_DATA_CLAUSE_MASK,
					 "#pragma acc exit data");

  எனில் (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_மரம்)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      திரும்பு;
    }

  stmt = enter ? make_முனை (OACC_ENTER_DATA) : make_முனை (OACC_EXIT_DATA);
  மரம்_TYPE (stmt) = void_type_முனை;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  SET_கோவை_LOCATION (stmt, loc);
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

நிலையான மரம்
c_parser_oacc_host_data (location_t loc, c_parser *parser, தருக்க *if_p)
{
  மரம் stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_DATA_CLAUSE_MASK,
				       "#pragma acc host_data", பொய்);
  எனில் (!omp_find_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      திரும்பு error_mark_முனை;
    }
  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  stmt = c_finish_oacc_host_data (loc, clauses, block);
  திரும்பு stmt;
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
நிலையான மரம்
c_parser_oacc_loop (location_t loc, c_parser *parser, எழுத்து *p_name,
		    omp_clause_mask mask, மரம் *cclauses, தருக்க *if_p)
{
  தருக்க is_parallel = ((mask >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  strcat (p_name, " loop");
  mask |= OACC_LOOP_CLAUSE_MASK;

  மரம் clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/cclauses == வெற்று,
					    /*target=*/is_parallel);
  எனில் (cclauses)
    {
      clauses = c_oacc_split_loop_clauses (clauses, cclauses, is_parallel);
      எனில் (*cclauses)
	*cclauses = c_finish_omp_clauses (*cclauses, C_ORT_ACC_TARGET);
      எனில் (clauses)
	clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
    }

  மரம் block = c_begin_compound_stmt (உண்மை);
  மரம் stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, வெற்று,
				     if_p);
  block = c_end_compound_stmt (loc, block, உண்மை);
  add_stmt (block);

  திரும்பு stmt;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_இலக்கம்_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_இலக்கம்_WORKERS)		\
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_இலக்கம்_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_இலக்கம்_WORKERS)		\
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

நிலையான மரம்
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       எண்ணிக்கை pragma_kind p_kind, எழுத்து *p_name, தருக்க *if_p)
{
  omp_clause_mask mask;
  எண்ணிக்கை மரம்_code code;
  தேர்வு (p_kind)
    {
    நிலை PRAGMA_OACC_KERNELS:
      strcat (p_name, " kernels");
      mask = OACC_KERNELS_CLAUSE_MASK;
      code = OACC_KERNELS;
      நிறுத்து;
    நிலை PRAGMA_OACC_PARALLEL:
      strcat (p_name, " parallel");
      mask = OACC_PARALLEL_CLAUSE_MASK;
      code = OACC_PARALLEL;
      நிறுத்து;
    நிலை PRAGMA_OACC_SERIAL:
      strcat (p_name, " serial");
      mask = OACC_SERIAL_CLAUSE_MASK;
      code = OACC_SERIAL;
      நிறுத்து;
    இயல்பு:
      gcc_unreachable ();
    }

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  மரம் block = c_begin_omp_parallel ();
	  மரம் clauses;
	  c_parser_oacc_loop (loc, parser, p_name, mask, &clauses, if_p);
	  திரும்பு c_finish_omp_construct (loc, code, block, clauses);
	}
    }

  மரம் clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/உண்மை,
					    /*target=*/உண்மை);

  மரம் block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  திரும்பு c_finish_omp_construct (loc, code, block, clauses);
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

நிலையான வெறுமை
c_parser_oacc_routine (c_parser *parser, எண்ணிக்கை pragma_context context)
{
  gcc_checking_assert (context == pragma_external);

  oacc_routine_data data;
  data.error_seen = பொய்;
  data.fndecl_seen = பொய்;
  data.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      மரம் decl = NULL_மரம்;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      எனில் (name_token->type == CPP_NAME
	  && (name_token->id_kind == C_ID_ID
	      || name_token->id_kind == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->மதிப்பு);
	  எனில் (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->மதிப்பு);
	  c_parser_consume_token (parser);
	}
      இல்லையெனில்
	c_parser_error (parser, "expected function name");

      எனில் (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_to_pragma_eol (parser, பொய்);
	  திரும்பு;
	}

      data.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_MASK,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      data.clauses = nreverse (data.clauses);

      எனில் (மரம்_CODE (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  திரும்பு;
	}

      c_finish_oacc_routine (&data, decl, பொய்);
    }
  இல்லையெனில் /* No optional '( name )'.  */
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
      எனில் (c_parser_next_token_is (parser, CPP_PRAGMA)
	  || c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (data.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  திரும்பு;
	}

      /* We only have to consider the pragma_external case here.  */
      எனில் (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  முழு ext = disable_extension_diagnostics ();
	  செய்
	    c_parser_consume_token (parser);
	  போது (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, உண்மை, உண்மை, உண்மை, பொய், உண்மை,
					 பொய், வெற்று, வெற்று, பொய், வெற்று, &data);
	  restore_extension_diagnostics (ext);
	}
      இல்லையெனில்
	c_parser_declaration_or_fndef (parser, உண்மை, உண்மை, உண்மை, பொய், உண்மை,
				       பொய், வெற்று, வெற்று, பொய், வெற்று, &data);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

நிலையான வெறுமை
c_finish_oacc_routine (கட்டமைப்பு oacc_routine_data *data, மரம் fndecl,
		       தருக்க is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  எனில் (data->error_seen
      || fndecl == error_mark_முனை)
    திரும்பு;

  எனில் (data->fndecl_seen)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      data->error_seen = உண்மை;
      திரும்பு;
    }
  எனில் (fndecl == NULL_மரம் || மரம்_CODE (fndecl) != FUNCTION_DECL)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      data->error_seen = உண்மை;
      திரும்பு;
    }

  முழு compatible
    = oacc_verify_routine_clauses (fndecl, &data->clauses, data->loc,
				   "#pragma acc routine");
  எனில் (compatible < 0)
    {
      data->error_seen = உண்மை;
      திரும்பு;
    }
  எனில் (compatible > 0)
    {
    }
  இல்லையெனில்
    {
      எனில் (மரம்_USED (fndecl) || (!is_defn && DECL_SAVED_மரம் (fndecl)))
	{
	  error_at (data->loc,
		    மரம்_USED (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  data->error_seen = உண்மை;
	  திரும்பு;
	}

      /* Set the routine's level of parallelism.  */
      மரம் dims = oacc_build_routine_dims (data->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_ATTRIBUTES (fndecl)
	= மரம்_cons (get_identifier ("omp declare target"),
		     data->clauses, DECL_ATTRIBUTES (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  data->fndecl_seen = உண்மை;
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

நிலையான வெறுமை
c_parser_oacc_update (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  மரம் clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_MASK,
					    "#pragma acc update");
  எனில் (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_மரம்)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      திரும்பு;
    }

  எனில் (parser->error)
    திரும்பு;

  மரம் stmt = make_முனை (OACC_UPDATE);
  மரம்_TYPE (stmt) = void_type_முனை;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  SET_கோவை_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#define OACC_WAIT_CLAUSE_MASK						\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF) )

நிலையான மரம்
c_parser_oacc_wait (location_t loc, c_parser *parser, எழுத்து *p_name)
{
  மரம் clauses, list = NULL_மரம், stmt = NULL_மரம்;

  எனில் (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  strcpy (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_MASK, p_name);
  stmt = c_finish_oacc_wait (loc, list, clauses);
  add_stmt (stmt);

  திரும்பு stmt;
}

கட்டமைப்பு c_omp_loc_மரம்
{
  location_t loc;
  மரம் var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
நிலையான மரம்
c_check_omp_allocate_allocator_r (மரம் *tp, முழு *, வெறுமை *data)
{
  மரம் var = ((கட்டமைப்பு c_omp_loc_மரம் *) data)->var;
  location_t loc = ((கட்டமைப்பு c_omp_loc_மரம் *) data)->loc;
  எனில் (மரம்_CODE (*tp) == VAR_DECL && c_check_in_current_scope (*tp))
    {
      எனில் (linemap_location_before_p (வரி_table, DECL_SOURCE_LOCATION (var),
				     DECL_SOURCE_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_SOURCE_LOCATION (*tp), "declared here");
	  inform (DECL_SOURCE_LOCATION (var),
		  "to be allocated variable declared here");
	  திரும்பு *tp;
	}
      இல்லையெனில்
	{
	  gcc_assert (cur_stmt_list
		      && மரம்_CODE (cur_stmt_list) == STATEMENT_LIST);

	  மரம்_stmt_iterator l = tsi_last (cur_stmt_list);
	  போது (!tsi_end_p (l))
	    {
	      எனில் (linemap_location_before_p (வரி_table, கோவை_LOCATION (*l),
					     DECL_SOURCE_LOCATION (var)))
		  நிறுத்து;
	      எனில் (மரம்_CODE (*l) == MODIFY_கோவை
		  && மரம்_OPERAND (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (கோவை_LOCATION (*l), "modified here");
		  inform (DECL_SOURCE_LOCATION (var),
			  "to be allocated variable declared here");
		  திரும்பு *tp;
		}
	      --l;
	    }
	}
    }
  திரும்பு NULL_மரம்;
}

/* OpenMP 5.x:
   # pragma omp allocate (list)  clauses

   OpenMP 5.0 clause:
   allocator (omp_allocator_handle_t expression)

   OpenMP 5.1 additional clause:
   align (constant-expression)]  */

நிலையான வெறுமை
c_parser_omp_allocate (c_parser *parser)
{
  மரம் alignment = NULL_மரம்;
  மரம் allocator = NULL_மரம்;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  மரம் nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_மரம்);
  செய்
    {
      எனில் (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      எனில் (!c_parser_next_token_is (parser, CPP_NAME))
	நிறுத்து;
      matching_parens parens;
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      c_parser_consume_token (parser);
      location_t கோவை_loc = c_parser_peek_token (parser)->location;
      எனில் (strcmp ("align", p) != 0 && strcmp ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  நிறுத்து;
	}
      எனில் (!parens.require_open (parser))
	நிறுத்து;

      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, பொய், உண்மை);
      கோவை_loc = c_parser_peek_token (parser)->location;
      எனில் (கோவை.மதிப்பு == error_mark_முனை)
	;
      இல்லையெனில் எனில் (p[2] == 'i' && alignment)
	{
	  error_at (கோவை_loc, "too many %qs clauses", "align");
	  நிறுத்து;
	}
      இல்லையெனில் எனில் (p[2] == 'i')
	{
	  alignment = c_fully_fold (கோவை.மதிப்பு, பொய், வெற்று);
	  எனில் (மரம்_CODE (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (மரம்_TYPE (alignment))
	      || மரம்_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (கோவை_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_மரம்;
	    }
	}
      இல்லையெனில் எனில் (allocator)
	{
	  error_at (கோவை_loc, "too many %qs clauses", "allocator");
	  நிறுத்து;
	}
      இல்லையெனில்
	{
	  allocator = c_fully_fold (கோவை.மதிப்பு, பொய், வெற்று);
	  allocator_loc = கோவை_loc;
	  மரம் orig_type
	    = கோவை.original_type ? கோவை.original_type : மரம்_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (allocator))
	      || மரம்_CODE (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (கோவை_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			மரம்_TYPE (allocator));
	      allocator = NULL_மரம்;
	    }
	}
      parens.skip_until_found_close (parser);
    } போது (உண்மை);
  c_parser_skip_to_pragma_eol (parser);

  c_mark_decl_jump_unsafe_in_current_scope ();
  க்கு (மரம் c = nl; c != NULL_மரம்; c = OMP_CLAUSE_CHAIN (c))
    {
      மரம் var = OMP_CLAUSE_DECL (c);
      எனில் (மரம்_CODE (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  தொடர்;
	}
      எனில் (!parser->in_omp_decl_attribute && !c_check_in_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_SOURCE_LOCATION (var), "declared here");
	  தொடர்;
	}
      எனில் (lookup_attribute ("omp allocate", DECL_ATTRIBUTES (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  தொடர்;
	}
      எனில் (மரம்_STATIC (var))
	{
	  எனில் (allocator == NULL_மரம் && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      தொடர்;
	    }
	  இல்லையெனில் எனில் (allocator
		   && (wi::to_widest (allocator) < 1
		       || wi::to_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::to_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::to_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  இல்லையெனில் எனில் (allocator
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
      எனில் (allocator)
	{
	  கட்டமைப்பு c_omp_loc_மரம் data
	    = {கோவை_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_மரம் (&allocator, c_check_omp_allocate_allocator_r, &data, வெற்று);
	}
      DECL_ATTRIBUTES (var) = மரம்_cons (get_identifier ("omp allocate"),
					 build_மரம்_list (allocator, alignment),
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

நிலையான வெறுமை
c_parser_omp_atomic (location_t loc, c_parser *parser, தருக்க openacc)
{
  மரம் lhs = NULL_மரம், rhs = NULL_மரம், v = NULL_மரம், r = NULL_மரம்;
  மரம் lhs1 = NULL_மரம், rhs1 = NULL_மரம்;
  மரம் stmt, orig_lhs, unfolded_lhs = NULL_மரம், unfolded_lhs1 = NULL_மரம்;
  எண்ணிக்கை மரம்_code code = ERROR_MARK, opcode = NOP_கோவை;
  எண்ணிக்கை omp_memory_order memory_order = OMP_MEMORY_ORDER_UNSPECIFIED;
  கட்டமைப்பு c_கோவை கோவை;
  location_t eloc;
  தருக்க structured_block = பொய்;
  தருக்க swapped = பொய்;
  தருக்க non_lvalue_p;
  மரம் clauses = NULL_மரம்;
  தருக்க capture = பொய்;
  தருக்க compare = பொய்;
  தருக்க weak = பொய்;
  எண்ணிக்கை omp_memory_order fail = OMP_MEMORY_ORDER_UNSPECIFIED;
  தருக்க no_semicolon = பொய்;
  தருக்க extra_scope = பொய்;

  போது (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      எனில் (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      எனில் (c_parser_next_token_is (parser, CPP_NAME))
	{
	  மாறிலி எழுத்து *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  எண்ணிக்கை மரம்_code new_code = ERROR_MARK;
	  எண்ணிக்கை omp_memory_order new_memory_order
	    = OMP_MEMORY_ORDER_UNSPECIFIED;
	  தருக்க new_capture = பொய்;
	  தருக்க new_compare = பொய்;
	  தருக்க new_weak = பொய்;
	  எண்ணிக்கை omp_memory_order new_fail = OMP_MEMORY_ORDER_UNSPECIFIED;

	  எனில் (!strcmp (p, "read"))
	    new_code = OMP_ATOMIC_READ;
	  இல்லையெனில் எனில் (!strcmp (p, "write"))
	    new_code = NOP_கோவை;
	  இல்லையெனில் எனில் (!strcmp (p, "update"))
	    new_code = OMP_ATOMIC;
	  இல்லையெனில் எனில் (openacc && !strcmp (p, "capture"))
	    new_code = OMP_ATOMIC_CAPTURE_NEW;
	  இல்லையெனில் எனில் (openacc)
	    {
	      p = வெற்று;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  இல்லையெனில் எனில் (!strcmp (p, "capture"))
	    new_capture = உண்மை;
	  இல்லையெனில் எனில் (!strcmp (p, "compare"))
	    new_compare = உண்மை;
	  இல்லையெனில் எனில் (!strcmp (p, "weak"))
	    new_weak = உண்மை;
	  இல்லையெனில் எனில் (!strcmp (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      எனில் (!parens.require_open (parser))
		தொடர்;

	      எனில் (c_parser_next_token_is (parser, CPP_NAME))
		{
		  மாறிலி எழுத்து *q
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);

		  எனில் (!strcmp (q, "seq_cst"))
		    new_fail = OMP_MEMORY_ORDER_SEQ_CST;
		  இல்லையெனில் எனில் (!strcmp (q, "acquire"))
		    new_fail = OMP_MEMORY_ORDER_ACQUIRE;
		  இல்லையெனில் எனில் (!strcmp (q, "relaxed"))
		    new_fail = OMP_MEMORY_ORDER_RELAXED;
		}

	      எனில் (new_fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  எனில் (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  இல்லையெனில்
		    fail = new_fail;
		}
	      இல்லையெனில்
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_found_close (parser);
	      தொடர்;
	    }
	  இல்லையெனில் எனில் (!strcmp (p, "seq_cst"))
	    new_memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  இல்லையெனில் எனில் (!strcmp (p, "acq_rel"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	  இல்லையெனில் எனில் (!strcmp (p, "release"))
	    new_memory_order = OMP_MEMORY_ORDER_RELEASE;
	  இல்லையெனில் எனில் (!strcmp (p, "acquire"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  இல்லையெனில் எனில் (!strcmp (p, "relaxed"))
	    new_memory_order = OMP_MEMORY_ORDER_RELAXED;
	  இல்லையெனில் எனில் (!strcmp (p, "hint"))
	    {
	      c_parser_consume_token (parser);
	      clauses = c_parser_omp_clause_hint (parser, clauses);
	      தொடர்;
	    }
	  இல்லையெனில்
	    {
	      p = வெற்று;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "%<capture%>, %<compare%>, %<weak%>, %<fail%>, "
			      "%<seq_cst%>, %<acq_rel%>, %<release%>, "
			      "%<relaxed%> or %<hint%> clause");
	    }
	  எனில் (p)
	    {
	      எனில் (new_code != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  எனில் (openacc
		      && code == OMP_ATOMIC
		      && new_code == OMP_ATOMIC_CAPTURE_NEW)
		    code = new_code;
		  இல்லையெனில் எனில் (code != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  இல்லையெனில்
		    code = new_code;
		}
	      இல்லையெனில் எனில் (new_memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  எனில் (memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  இல்லையெனில்
		    memory_order = new_memory_order;
		}
	      இல்லையெனில் எனில் (new_capture)
		{
		  எனில் (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  இல்லையெனில்
		    capture = உண்மை;
		}
	      இல்லையெனில் எனில் (new_compare)
		{
		  எனில் (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  இல்லையெனில்
		    compare = உண்மை;
		}
	      இல்லையெனில் எனில் (new_weak)
		{
		  எனில் (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  இல்லையெனில்
		    weak = உண்மை;
		}
	      c_parser_consume_token (parser);
	      தொடர்;
	    }
	}
      நிறுத்து;
    }
  c_parser_skip_to_pragma_eol (parser);

  எனில் (code == ERROR_MARK)
    code = OMP_ATOMIC;
  எனில் (capture)
    {
      எனில் (code != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      இல்லையெனில்
	code = OMP_ATOMIC_CAPTURE_NEW;
    }
  எனில் (compare && code != OMP_ATOMIC && code != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = பொய்;
    }
  எனில் (fail != OMP_MEMORY_ORDER_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      fail = OMP_MEMORY_ORDER_UNSPECIFIED;
    }
  எனில் (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = பொய்;
    }
  எனில் (openacc)
    memory_order = OMP_MEMORY_ORDER_RELAXED;
  இல்லையெனில் எனில் (memory_order == OMP_MEMORY_ORDER_UNSPECIFIED)
    {
      omp_requires_mask
	= (எண்ணிக்கை omp_requires) (omp_requires_mask
			       | OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED);
      தேர்வு ((எண்ணிக்கை omp_memory_order)
	      (omp_requires_mask & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER))
	{
	நிலை OMP_MEMORY_ORDER_UNSPECIFIED:
	நிலை OMP_MEMORY_ORDER_RELAXED:
	  memory_order = OMP_MEMORY_ORDER_RELAXED;
	  நிறுத்து;
	நிலை OMP_MEMORY_ORDER_SEQ_CST:
	  memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  நிறுத்து;
	நிலை OMP_MEMORY_ORDER_ACQUIRE:
	  எனில் (code == NOP_கோவை)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  இல்லையெனில்
	    memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  நிறுத்து;
	நிலை OMP_MEMORY_ORDER_RELEASE:
	  எனில் (code == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  இல்லையெனில்
	    memory_order = OMP_MEMORY_ORDER_RELEASE;
	  நிறுத்து;
	நிலை OMP_MEMORY_ORDER_ACQ_REL:
	  தேர்வு (code)
	    {
	    நிலை OMP_ATOMIC_READ:
	      memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	      நிறுத்து;
	    நிலை NOP_கோவை: /* atomic write */
	      memory_order = OMP_MEMORY_ORDER_RELEASE;
	      நிறுத்து;
	    இயல்பு:
	      memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	      நிறுத்து;
	    }
	  நிறுத்து;
	இயல்பு:
	  gcc_unreachable ();
	}
    }
  இல்லையெனில்
    தேர்வு (code)
      {
      நிலை OMP_ATOMIC_READ:
	எனில் (memory_order == OMP_MEMORY_ORDER_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	இல்லையெனில் எனில் (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	நிறுத்து;
      நிலை NOP_கோவை: /* atomic write */
	எனில் (memory_order == OMP_MEMORY_ORDER_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	இல்லையெனில் எனில் (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_RELEASE;
	நிறுத்து;
      இயல்பு:
	நிறுத்து;
      }
  எனில் (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
    memory_order
      = (எண்ணிக்கை omp_memory_order) (memory_order
				 | (fail << OMP_FAIL_MEMORY_ORDER_SHIFT));

  தேர்வு (code)
    {
    நிலை OMP_ATOMIC_READ:
    நிலை NOP_கோவை: /* atomic write */
      v = c_parser_cast_expression (parser, வெற்று).மதிப்பு;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, பொய், வெற்று, உண்மை);
      எனில் (v == error_mark_முனை)
	செல் saw_error;
      எனில் (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      எனில் (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	செல் saw_error;
      எனில் (code == NOP_கோவை)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  கோவை = c_parser_expression (parser);
	  கோவை = default_function_array_read_conversion (eloc, கோவை);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  code = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_மரம்;
	  rhs = c_fully_fold (கோவை.மதிப்பு, பொய், வெற்று);
	  எனில் (rhs == error_mark_முனை)
	    செல் saw_error;
	}
      இல்லையெனில்
	{
	  lhs = c_parser_cast_expression (parser, வெற்று).மதிப்பு;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, பொய், வெற்று, உண்மை);
	  எனில் (lhs == error_mark_முனை)
	    செல் saw_error;
	  எனில் (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      செல் done;
    நிலை OMP_ATOMIC_CAPTURE_NEW:
      எனில் (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_block = உண்மை;
	}
      இல்லையெனில் எனில் (compare
	       && c_parser_next_token_is_keyword (parser, RID_IF))
	நிறுத்து;
      இல்லையெனில்
	{
	  v = c_parser_cast_expression (parser, வெற்று).மதிப்பு;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, பொய், வெற்று, உண்மை);
	  எனில் (v == error_mark_முனை)
	    செல் saw_error;
	  எனில் (non_lvalue_p)
	    v = non_lvalue (v);
	  எனில் (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    செல் saw_error;
	  எனில் (compare && c_parser_next_token_is_keyword (parser, RID_IF))
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "expected expression");
	      செல் saw_error;
	    }
	}
      நிறுத்து;
    இயல்பு:
      நிறுத்து;
    }

  /* For structured_block case we don't know yet whether
     old or new x should be captured.  */
restart:
  எனில் (compare && c_parser_next_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      எனில் (!parens.require_open (parser))
	செல் saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_கோவை cmp_கோவை;
      எனில் (r)
	{
	  cmp_கோவை = c_parser_cast_expression (parser, வெற்று);
	  cmp_கோவை = default_function_array_conversion (eloc, cmp_கோவை);
	}
      இல்லையெனில்
	cmp_கோவை = c_parser_இருமம்_expression (parser, வெற்று, void_list_முனை);
      parens.skip_until_found_close (parser);
      எனில் (cmp_கோவை.மதிப்பு == error_mark_முனை)
	செல் saw_error;
      எனில் (r)
	{
	  எனில் (!c_மரம்_equal (cmp_கோவை.மதிப்பு, unfolded_lhs))
	    செல் bad_if;
	  cmp_கோவை.மதிப்பு = rhs1;
	  rhs1 = NULL_மரம்;
	  gcc_assert (மரம்_CODE (cmp_கோவை.மதிப்பு) == EQ_கோவை);
	}
      எனில் (மரம்_CODE (cmp_கோவை.மதிப்பு) == EQ_கோவை)
	;
      இல்லையெனில் எனில் (!structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (கோவை_LOC_OR_LOC (cmp_கோவை.மதிப்பு, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  செல் saw_error;
	}
      இல்லையெனில் எனில் (மரம்_CODE (cmp_கோவை.மதிப்பு) != GT_கோவை
	       && மரம்_CODE (cmp_கோவை.மதிப்பு) != LT_கோவை)
	{
	  error_at (கோவை_LOC_OR_LOC (cmp_கோவை.மதிப்பு, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  செல் saw_error;
	}
      எனில் (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	செல் saw_error;

      extra_scope = உண்மை;
      eloc = c_parser_peek_token (parser)->location;
      கோவை = c_parser_cast_expression (parser, வெற்று);
      lhs = கோவை.மதிப்பு;
      கோவை = default_function_array_conversion (eloc, கோவை);
      unfolded_lhs = கோவை.மதிப்பு;
      lhs = c_fully_fold (lhs, பொய், வெற்று, உண்மை);
      orig_lhs = lhs;
      எனில் (lhs == error_mark_முனை)
	செல் saw_error;
      எனில் (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      எனில் (!c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  செல் saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
      rhs1 = கோவை.மதிப்பு;

      எனில் (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	செல் saw_error;

      எனில் (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	செல் saw_error;

      extra_scope = பொய்;
      no_semicolon = உண்மை;

      எனில் (c_மரம்_equal (மரம்_OPERAND (cmp_கோவை.மதிப்பு, 0), unfolded_lhs))
	{
	  எனில் (மரம்_CODE (cmp_கோவை.மதிப்பு) == EQ_கோவை)
	    {
	      opcode = COND_கோவை;
	      rhs = c_fully_fold (மரம்_OPERAND (cmp_கோவை.மதிப்பு, 1),
				  பொய், வெற்று, உண்மை);
	      rhs1 = c_fully_fold (rhs1, பொய், வெற்று, உண்மை);
	    }
	  இல்லையெனில் எனில் (c_மரம்_equal (மரம்_OPERAND (cmp_கோவை.மதிப்பு, 1), rhs1))
	    {
	      opcode = (மரம்_CODE (cmp_கோவை.மதிப்பு) == GT_கோவை
			? MIN_கோவை : MAX_கோவை);
	      rhs = c_fully_fold (rhs1, பொய், வெற்று, உண்மை);
	      rhs1 = c_fully_fold (மரம்_OPERAND (cmp_கோவை.மதிப்பு, 0),
				   பொய், வெற்று, உண்மை);
	    }
	  இல்லையெனில்
	    செல் bad_if;
	}
      இல்லையெனில் எனில் (மரம்_CODE (cmp_கோவை.மதிப்பு) == EQ_கோவை)
	செல் bad_if;
      இல்லையெனில் எனில் (c_மரம்_equal (மரம்_OPERAND (cmp_கோவை.மதிப்பு, 1), unfolded_lhs)
	       && c_மரம்_equal (மரம்_OPERAND (cmp_கோவை.மதிப்பு, 0), rhs1))
	{
	  opcode = (மரம்_CODE (cmp_கோவை.மதிப்பு) == GT_கோவை
		    ? MAX_கோவை : MIN_கோவை);
	  rhs = c_fully_fold (rhs1, பொய், வெற்று, உண்மை);
	  rhs1 = c_fully_fold (மரம்_OPERAND (cmp_கோவை.மதிப்பு, 1),
			       பொய், வெற்று, உண்மை);
	}
      இல்லையெனில்
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  செல் saw_error;
	}

      எனில் (c_parser_next_token_is_keyword (parser, RID_ELSE))
	{
	  எனில் (code != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_block && r == NULL_மரம்)
	      || மரம்_CODE (cmp_கோவை.மதிப்பு) != EQ_கோவை)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      செல் saw_error;
	    }

	  c_parser_consume_token (parser);

	  எனில் (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    செல் saw_error;

	  extra_scope = உண்மை;
	  v = c_parser_cast_expression (parser, வெற்று).மதிப்பு;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, பொய், வெற்று, உண்மை);
	  எனில் (v == error_mark_முனை)
	    செல் saw_error;
	  எனில் (non_lvalue_p)
	    v = non_lvalue (v);
	  எனில் (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    செல் saw_error;

	  கோவை = c_parser_கோவை_no_commas (parser, வெற்று);

	  எனில் (!c_மரம்_equal (கோவை.மதிப்பு, unfolded_lhs))
	    செல் bad_if;

	  எனில் (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    செல் saw_error;

	  எனில் (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    செல் saw_error;

	  extra_scope = பொய்;
	  code = OMP_ATOMIC_CAPTURE_OLD;
	  எனில் (r == NULL_மரம்)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_முனை;
	}
      இல்லையெனில் எனில் (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  செல் saw_error;
	}
      இல்லையெனில் எனில் (code == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_மரம்
	       && v == NULL_மரம்)
	code = OMP_ATOMIC;
      செல் stmt_done;
    }
  eloc = c_parser_peek_token (parser)->location;
  கோவை = c_parser_cast_expression (parser, வெற்று);
  lhs = கோவை.மதிப்பு;
  கோவை = default_function_array_conversion (eloc, கோவை);
  unfolded_lhs = கோவை.மதிப்பு;
  lhs = c_fully_fold (lhs, பொய், வெற்று, உண்மை);
  orig_lhs = lhs;
  தேர்வு (மரம்_CODE (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    நிலை ERROR_MARK:
    saw_error:
      c_parser_skip_to_end_of_block_or_statement (parser);
      எனில் (extra_scope && c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      எனில் (structured_block)
	{
	  எனில் (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  இல்லையெனில் எனில் (code == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      திரும்பு;

    நிலை POSTINCREMENT_கோவை:
      எனில் (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    நிலை PREINCREMENT_கோவை:
      lhs = மரம்_OPERAND (lhs, 0);
      unfolded_lhs = NULL_மரம்;
      opcode = PLUS_கோவை;
      rhs = integer_one_முனை;
      எனில் (compare)
	செல் invalid_compare;
      நிறுத்து;

    நிலை POSTDECREMENT_கோவை:
      எனில் (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    நிலை PREDECREMENT_கோவை:
      lhs = மரம்_OPERAND (lhs, 0);
      unfolded_lhs = NULL_மரம்;
      opcode = MINUS_கோவை;
      rhs = integer_one_முனை;
      எனில் (compare)
	செல் invalid_compare;
      நிறுத்து;

    நிலை COMPOUND_கோவை:
      எனில் (மரம்_CODE (மரம்_OPERAND (lhs, 0)) == SAVE_கோவை
	  && மரம்_CODE (மரம்_OPERAND (lhs, 1)) == COMPOUND_கோவை
	  && மரம்_CODE (மரம்_OPERAND (மரம்_OPERAND (lhs, 1), 0)) == MODIFY_கோவை
	  && மரம்_OPERAND (மரம்_OPERAND (lhs, 1), 1) == மரம்_OPERAND (lhs, 0)
	  && C_BOOLEAN_TYPE_P (மரம்_TYPE (மரம்_OPERAND (மரம்_OPERAND
					      (மரம்_OPERAND (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = மரம்_OPERAND (மரம்_OPERAND (lhs, 1), 0);
      /* FALLTHRU */
    நிலை MODIFY_கோவை:
      எனில் (மரம்_CODE (lhs) == MODIFY_கோவை
	  && C_BOOLEAN_TYPE_P (மரம்_TYPE (மரம்_OPERAND (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  எனில் (integer_onep (மரம்_OPERAND (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = மரம்_OPERAND (lhs, 1);
	      lhs = மரம்_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_மரம்;
	      opcode = NOP_கோவை;
	      எனில் (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && மரம்_CODE (orig_lhs) == COMPOUND_கோவை)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      எனில் (compare)
		செல் invalid_compare;
	      நிறுத்து;
	    }
	  எனில் (மரம்_CODE (மரம்_OPERAND (lhs, 1)) == TRUTH_NOT_கோவை
	      && மரம்_OPERAND (lhs, 0)
		 == மரம்_OPERAND (மரம்_OPERAND (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = மரம்_OPERAND (lhs, 1);
	      lhs = மரம்_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_மரம்;
	      opcode = NOP_கோவை;
	      எனில் (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && மரம்_CODE (orig_lhs) == COMPOUND_கோவை)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      எனில் (compare)
		செல் invalid_compare;
	      நிறுத்து;
	    }
	}
      /* FALLTHRU */
    இயல்பு:
      எனில் (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      எனில் (compare && !c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  செல் saw_error;
	}
      தேர்வு (c_parser_peek_token (parser)->type)
	{
	நிலை CPP_MULT_EQ:
	  opcode = MULT_கோவை;
	  நிறுத்து;
	நிலை CPP_DIV_EQ:
	  opcode = TRUNC_DIV_கோவை;
	  நிறுத்து;
	நிலை CPP_PLUS_EQ:
	  opcode = PLUS_கோவை;
	  நிறுத்து;
	நிலை CPP_MINUS_EQ:
	  opcode = MINUS_கோவை;
	  நிறுத்து;
	நிலை CPP_LSHIFT_EQ:
	  opcode = LSHIFT_கோவை;
	  நிறுத்து;
	நிலை CPP_RSHIFT_EQ:
	  opcode = RSHIFT_கோவை;
	  நிறுத்து;
	நிலை CPP_AND_EQ:
	  opcode = BIT_AND_கோவை;
	  நிறுத்து;
	நிலை CPP_OR_EQ:
	  opcode = BIT_IOR_கோவை;
	  நிறுத்து;
	நிலை CPP_XOR_EQ:
	  opcode = BIT_XOR_கோவை;
	  நிறுத்து;
	நிலை CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  கோவை = c_parser_கோவை_no_commas (parser, வெற்று, unfolded_lhs);
	  rhs1 = கோவை.மதிப்பு;
	  தேர்வு (மரம்_CODE (rhs1))
	    {
	    நிலை MULT_கோவை:
	    நிலை TRUNC_DIV_கோவை:
	    நிலை RDIV_கோவை:
	    நிலை PLUS_கோவை:
	    நிலை MINUS_கோவை:
	    நிலை LSHIFT_கோவை:
	    நிலை RSHIFT_கோவை:
	    நிலை BIT_AND_கோவை:
	    நிலை BIT_IOR_கோவை:
	    நிலை BIT_XOR_கோவை:
	      எனில் (compare)
		நிறுத்து;
	      எனில் (c_மரம்_equal (மரம்_OPERAND (rhs1, 0), unfolded_lhs))
		{
		  opcode = மரம்_CODE (rhs1);
		  rhs = c_fully_fold (மரம்_OPERAND (rhs1, 1), பொய், வெற்று,
				      உண்மை);
		  rhs1 = c_fully_fold (மரம்_OPERAND (rhs1, 0), பொய், வெற்று,
				       உண்மை);
		  செல் stmt_done;
		}
	      எனில் (c_மரம்_equal (மரம்_OPERAND (rhs1, 1), unfolded_lhs))
		{
		  opcode = மரம்_CODE (rhs1);
		  rhs = c_fully_fold (மரம்_OPERAND (rhs1, 0), பொய், வெற்று,
				      உண்மை);
		  rhs1 = c_fully_fold (மரம்_OPERAND (rhs1, 1), பொய், வெற்று,
				       உண்மை);
		  swapped = !commutative_மரம்_code (opcode);
		  செல் stmt_done;
		}
	      நிறுத்து;
	    நிலை COND_கோவை:
	      எனில் (!compare)
		நிறுத்து;
	      எனில் (மரம்_CODE (மரம்_OPERAND (rhs1, 0)) != GT_கோவை
		  && மரம்_CODE (மரம்_OPERAND (rhs1, 0)) != LT_கோவை
		  && மரம்_CODE (மரம்_OPERAND (rhs1, 0)) != EQ_கோவை)
		நிறுத்து;
	      எனில் (!மரம்_OPERAND (rhs1, 1))
		நிறுத்து;
	      எனில் (!c_மரம்_equal (மரம்_OPERAND (rhs1, 2), unfolded_lhs))
		நிறுத்து;
	      எனில் (c_மரம்_equal (மரம்_OPERAND (மரம்_OPERAND (rhs1, 0), 0),
				unfolded_lhs))
		{
		  எனில் (மரம்_CODE (மரம்_OPERAND (rhs1, 0)) == EQ_கோவை)
		    {
		      opcode = COND_கோவை;
		      rhs = c_fully_fold (மரம்_OPERAND (மரம்_OPERAND (rhs1,
								      0), 1),
					  பொய், வெற்று, உண்மை);
		      rhs1 = c_fully_fold (மரம்_OPERAND (rhs1, 1), பொய்,
					   வெற்று, உண்மை);
		      செல் stmt_done;
		    }
		  எனில் (c_மரம்_equal (மரம்_OPERAND (மரம்_OPERAND (rhs1, 0), 1),
				    மரம்_OPERAND (rhs1, 1)))
		    {
		      opcode = (மரம்_CODE (மரம்_OPERAND (rhs1, 0)) == GT_கோவை
				? MIN_கோவை : MAX_கோவை);
		      rhs = c_fully_fold (மரம்_OPERAND (rhs1, 1), பொய், வெற்று,
					  உண்மை);
		      rhs1 = c_fully_fold (மரம்_OPERAND (மரம்_OPERAND (rhs1,
								       0), 0),
					   பொய், வெற்று, உண்மை);
		      செல் stmt_done;
		    }
		}
	      இல்லையெனில் எனில் (மரம்_CODE (மரம்_OPERAND (rhs1, 0)) == EQ_கோவை)
		நிறுத்து;
	      இல்லையெனில் எனில் (c_மரம்_equal (மரம்_OPERAND (மரம்_OPERAND (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  எனில் (c_மரம்_equal (மரம்_OPERAND (மரம்_OPERAND (rhs1, 0), 0),
				    மரம்_OPERAND (rhs1, 1)))
		    {
		      opcode = (மரம்_CODE (மரம்_OPERAND (rhs1, 0)) == GT_கோவை
				? MAX_கோவை : MIN_கோவை);
		      rhs = c_fully_fold (மரம்_OPERAND (rhs1, 1), பொய், வெற்று,
					  உண்மை);
		      rhs1 = c_fully_fold (மரம்_OPERAND (மரம்_OPERAND (rhs1,
								       0), 1),
					   பொய், வெற்று, உண்மை);
		      செல் stmt_done;
		    }
		}
	      நிறுத்து;
	    நிலை EQ_கோவை:
	      எனில் (!compare
		  || code != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_block
		  || v
		  || r)
		நிறுத்து;
	      எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_மரம்;
		  c_parser_consume_token (parser);
		  செல் restart;
		}
	      நிறுத்து;
	    நிலை ERROR_MARK:
	      செல் saw_error;
	    இயல்பு:
	      நிறுத்து;
	    }
	  எனில் (c_parser_peek_token (parser)->type == CPP_SEMICOLON)
	    {
	      எனில் (structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
		{
		  code = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_மரம்;
		  கோவை = default_function_array_read_conversion (eloc, கோவை);
		  unfolded_lhs1 = கோவை.மதிப்பு;
		  lhs1 = c_fully_fold (unfolded_lhs1, பொய், வெற்று, உண்மை);
		  rhs1 = NULL_மரம்;
		  c_parser_consume_token (parser);
		  செல் restart;
		}
	      எனில் (structured_block && !compare)
		{
		  opcode = NOP_கோவை;
		  கோவை = default_function_array_read_conversion (eloc, கோவை);
		  rhs = c_fully_fold (கோவை.மதிப்பு, பொய், வெற்று, உண்மை);
		  rhs1 = NULL_மரம்;
		  செல் stmt_done;
		}
	    }
	  c_parser_error (parser, "invalid form of %<#pragma omp atomic%>");
	  செல் saw_error;
	இயல்பு:
	  c_parser_error (parser,
			  "invalid operator for %<#pragma omp atomic%>");
	  செல் saw_error;
	}

      /* Arrange to pass the location of the assignment operator to
	 c_finish_omp_atomic.  */
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      கோவை = c_parser_expression (parser);
      கோவை = default_function_array_read_conversion (eloc, கோவை);
      rhs = கோவை.மதிப்பு;
      rhs = c_fully_fold (rhs, பொய், வெற்று, உண்மை);
      நிறுத்து;
    }
stmt_done:
  எனில் (structured_block && code == OMP_ATOMIC_CAPTURE_NEW && r == NULL_மரம்)
    {
      எனில் (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	செல் saw_error;
      no_semicolon = பொய்;
      v = c_parser_cast_expression (parser, வெற்று).மதிப்பு;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, பொய், வெற்று, உண்மை);
      எனில் (v == error_mark_முனை)
	செல் saw_error;
      எனில் (non_lvalue_p)
	v = non_lvalue (v);
      எனில் (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	செல் saw_error;
      eloc = c_parser_peek_token (parser)->location;
      கோவை = c_parser_cast_expression (parser, வெற்று);
      lhs1 = கோவை.மதிப்பு;
      கோவை = default_function_array_read_conversion (eloc, கோவை);
      unfolded_lhs1 = கோவை.மதிப்பு;
      lhs1 = c_fully_fold (lhs1, பொய், வெற்று, உண்மை);
      எனில் (lhs1 == error_mark_முனை)
	செல் saw_error;
      எனில் (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  எனில் (structured_block)
    {
      எனில் (!no_semicolon)
	c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
done:
  எனில் (weak && opcode != COND_கோவை)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = பொய்;
    }
  எனில் (unfolded_lhs && unfolded_lhs1
      && !c_மரம்_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_முனை;
    }
  இல்லையெனில்
    stmt = c_finish_omp_atomic (loc, code, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, memory_order, weak);
  எனில் (stmt != error_mark_முனை)
    add_stmt (stmt);

  எனில் (!structured_block && !no_semicolon)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}


/* OpenMP 2.5:
   # pragma omp barrier new-line
*/

நிலையான வெறுமை
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

நிலையான மரம்
c_parser_omp_critical (location_t loc, c_parser *parser, தருக்க *if_p)
{
  மரம் stmt, name = NULL_மரம், clauses = NULL_மரம்;

  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      எனில் (c_parser_next_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->மதிப்பு;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      இல்லையெனில்
	c_parser_error (parser, "expected identifier");

      எனில் (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_MASK,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_block (parser, if_p);
  திரும்பு c_finish_omp_critical (loc, stmt, name, clauses);
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

நிலையான வெறுமை
c_parser_omp_depobj (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  matching_parens parens;
  எனில் (!parens.require_open (parser))
    {
      c_parser_skip_to_pragma_eol (parser);
      திரும்பு;
    }

  மரம் depobj = c_parser_கோவை_no_commas (parser, வெற்று).மதிப்பு;
  எனில் (depobj != error_mark_முனை)
    {
      எனில் (!lvalue_p (depobj))
	{
	  error_at (கோவை_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_முனை;
	}
      இல்லையெனில்
	{
	  மரம் addr = build_unary_op (கோவை_LOC_OR_LOC (depobj, loc), ADDR_கோவை,
				      depobj, பொய்);
	  எனில் (addr == error_mark_முனை)
	    depobj = error_mark_முனை;
	  இல்லையெனில்
	    depobj = build_indirect_ref (கோவை_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_STAR);
	}
    }

  parens.skip_until_found_close (parser);
  மரம் clause = NULL_மரம்;
  எண்ணிக்கை omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_INVALID;
  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);

      c_parser_consume_token (parser);
      எனில் (!strcmp ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_மரம், c_loc);
	  clause = c_finish_omp_clauses (clause, C_ORT_OMP);
	  எனில் (!clause)
	    clause = error_mark_முனை;
	}
      இல்லையெனில் எனில் (!strcmp ("destroy", p))
	{
	  matching_parens c_parens;
	  kind = OMP_CLAUSE_DEPEND_LAST;
	  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      மரம் destobj = c_parser_கோவை_no_commas (parser, வெற்று).மதிப்பு;
	      எனில் (!lvalue_p (destobj))
		error_at (கோவை_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      இல்லையெனில் எனில் (depobj != error_mark_முனை
		       && !operand_equal_p (destobj, depobj,
					    OEP_MATCH_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (கோவை_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_found_close (parser);
	    }
	}
      இல்லையெனில் எனில் (!strcmp ("update", p))
	{
	  matching_parens c_parens;
	  எனில் (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      எனில் (c_parser_next_token_is (parser, CPP_NAME))
		{
		  மாறிலி எழுத்து *p2
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);

		  c_parser_consume_token (parser);
		  எனில் (!strcmp ("in", p2))
		    kind = OMP_CLAUSE_DEPEND_IN;
		  இல்லையெனில் எனில் (!strcmp ("out", p2))
		    kind = OMP_CLAUSE_DEPEND_OUT;
		  இல்லையெனில் எனில் (!strcmp ("inout", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUT;
		  இல்லையெனில் எனில் (!strcmp ("mutexinoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  இல்லையெனில் எனில் (!strcmp ("inoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      எனில் (kind == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_முனை;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_found_close (parser);
	    }
	  இல்லையெனில்
	    clause = error_mark_முனை;
	}
    }
  எனில் (!clause && kind == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_முனை;
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

நிலையான வெறுமை
c_parser_omp_flush (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  எண்ணிக்கை memmodel mo = MEMMODEL_LAST;
  எனில் (c_parser_next_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);

      எனில் (!strcmp (p, "seq_cst"))
	mo = MEMMODEL_SEQ_CST;
      இல்லையெனில் எனில் (!strcmp (p, "acq_rel"))
	mo = MEMMODEL_ACQ_REL;
      இல்லையெனில் எனில் (!strcmp (p, "release"))
	mo = MEMMODEL_RELEASE;
      இல்லையெனில் எனில் (!strcmp (p, "acquire"))
	mo = MEMMODEL_ACQUIRE;
      இல்லையெனில்
	error_at (c_parser_peek_token (parser)->location,
		  "expected %<seq_cst%>, %<acq_rel%>, %<release%> or "
		  "%<acquire%>");
      c_parser_consume_token (parser);
    }
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      எனில் (mo != MEMMODEL_LAST)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, வெற்று);
    }
  இல்லையெனில் எனில் (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_to_pragma_eol (parser);

  c_finish_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

நிலையான தருக்க
c_parser_omp_section_scan (c_parser *parser, மாறிலி எழுத்து *directive,
			   தருக்க tentative)
{
  எனில் (!c_parser_nth_token_starts_std_attributes (parser, 1))
    திரும்பு பொய்;
  unsigned முழு n = 3;
  எனில் (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    திரும்பு பொய்;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  எனில் (token->type != CPP_CLOSE_SQUARE)
    திரும்பு பொய்;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  எனில் (token->type != CPP_CLOSE_SQUARE)
    திரும்பு பொய்;
  எனில் (n < 9)
    திரும்பு பொய்;
  எனில் (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      மரம் first = c_parser_peek_nth_token_raw (parser, 3)->மதிப்பு;
      மரம் second = c_parser_peek_nth_token_raw (parser, 5)->மதிப்பு;
      எனில் (strcmp (IDENTIFIER_POINTER (first), "directive")
	  && strcmp (IDENTIFIER_POINTER (first), "__directive__"))
	திரும்பு பொய்;
      எனில் (strcmp (IDENTIFIER_POINTER (second), directive))
	திரும்பு பொய்;
    }
  எனில் (tentative)
    திரும்பு உண்மை;
  location_t first_loc = c_parser_peek_token (parser)->location;
  location_t last_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t நடு_loc = UNKNOWN_LOCATION;
  மரம் std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  தருக்க seen = பொய்;
  முழு cnt = 0;
  க்கு (மரம் attr = std_attrs; attr; attr = மரம்_CHAIN (attr))
    எனில் (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	க்கு (மரம் a = மரம்_மதிப்பு (attr); a; a = மரம்_CHAIN (a))
	  {
	    மரம் d = மரம்_மதிப்பு (a);
	    gcc_assert (மரம்_CODE (d) == C_TOKEN_VEC);
	    c_token *first = C_TOKEN_VEC_TOKENS (d)->address ();
	    cnt++;
	    எனில் (first->type == CPP_NAME
		&& strcmp (IDENTIFIER_POINTER (first->மதிப்பு),
			   directive) == 0)
	      {
		seen = உண்மை;
		எனில் (நடு_loc == UNKNOWN_LOCATION)
		  நடு_loc = first->location;
	      }
	  }
      }
  எனில் (!seen)
    திரும்பு பொய்;
  எனில் (cnt != 1 || மரம்_CHAIN (std_attrs))
    {
      error_at (make_location (first_loc, last_loc, நடு_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      திரும்பு பொய்;
    }
  c_parser_handle_statement_omp_attributes (parser, std_attrs, வெற்று);
  திரும்பு உண்மை;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

நிலையான மரம்
c_parser_omp_structured_block_sequence (c_parser *parser,
					எண்ணிக்கை pragma_kind kind)
{
  மரம் stmt = தள்ளு_stmt_list ();
  c_parser_statement (parser, வெற்று);
  செய்
    {
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	நிறுத்து;
      எனில் (c_parser_next_token_is (parser, CPP_EOF))
	நிறுத்து;

      எனில் (kind != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_kind == kind)
	நிறுத்து;

      எனில் (kind != PRAGMA_NONE
	  && c_parser_omp_section_scan (parser,
					kind == PRAGMA_OMP_SCAN
					? "scan" : "section", பொய்))
	நிறுத்து;

      c_parser_statement (parser, வெற்று);
    }
  போது (1);
  திரும்பு எடு_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

நிலையான வெறுமை
c_parser_omp_scan_loop_body (c_parser *parser, தருக்க open_brace_parsed)
{
  மரம் substmt;
  location_t loc;
  மரம் clauses = NULL_மரம்;
  தருக்க found_scan = பொய்;

  loc = c_parser_peek_token (parser)->location;
  எனில் (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = பொய்;
      திரும்பு;
    }

  எனில் (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SCAN)
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_OMP_SCAN);
  இல்லையெனில்
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_முனை, substmt, NULL_மரம்);
  SET_கோவை_LOCATION (substmt, loc);
  add_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  எனில் (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SCAN)
    {
      எண்ணிக்கை omp_clause_code clause = OMP_CLAUSE_ERROR;
      found_scan = உண்மை;

      c_parser_consume_pragma (parser);

      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      எனில் (c_parser_next_token_is (parser, CPP_NAME))
	{
	  மாறிலி எழுத்து *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
	  எனில் (strcmp (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  இல்லையெனில் எனில் (strcmp (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      எனில் (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_மரம்);
	}
      இல்லையெனில்
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_to_pragma_eol (parser);
    }
  இல்லையெனில்
    error ("expected %<#pragma omp scan%>");

  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  எனில் (!c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_NONE);
  இல்லையெனில்
    {
      எனில் (found_scan)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_முனை, substmt, clauses);
  SET_கோவை_LOCATION (substmt, loc);
  add_stmt (substmt);

  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
நிலையான தருக்க
c_parser_omp_next_tokens_can_be_canon_loop (c_parser *parser,
					    எண்ணிக்கை மரம்_code code,
					    தருக்க error_p)
{
  எனில் (code == OACC_LOOP)
    {
      எனில் (c_parser_next_token_is_keyword (parser, RID_FOR))
	திரும்பு உண்மை;
      எனில் (error_p)
	c_parser_error (parser, "for statement expected");
    }
  இல்லையெனில்
    {
      எனில் (c_parser_next_token_is_keyword (parser, RID_FOR))
	திரும்பு உண்மை;

      எனில் (c_parser_next_token_is (parser, CPP_PRAGMA))
	தேர்வு (c_parser_peek_token (parser)->pragma_kind)
	  {
	  நிலை PRAGMA_OMP_UNROLL:
	  நிலை PRAGMA_OMP_TILE:
	    திரும்பு உண்மை;
	  இயல்பு:
	    நிறுத்து;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      size_t n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      எனில் (token->type == CPP_NAME
	  && C_IS_RESERVED_WORD (token->மதிப்பு)
	  && C_RID_CODE (token->மதிப்பு) == RID_FOR)
	திரும்பு உண்மை;
      எனில் (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  திரும்பு பொய்;
}

நிலையான மரம் c_parser_omp_tile (location_t, c_parser *, தருக்க *);
நிலையான மரம் c_parser_omp_unroll (location_t, c_parser *, தருக்க *);

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

நிலையான மரம்
c_parser_omp_loop_nest (c_parser *parser, தருக்க *if_p)
{
  மரம் decl = NULL_மரம், cond = NULL_மரம், incr = NULL_மரம், init = NULL_மரம்;
  மரம் body = NULL_மரம்;
  matching_parens parens;
  தருக்க moreloops;
  unsigned எழுத்து save_in_statement;
  மரம் loop_scope;
  location_t loc;
  கட்டமைப்பு omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  முழு depth = omp_for_parse_state->depth;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  எனில் (c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      மரம் std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_attributes (parser, std_attrs, வெற்று);
      எனில் (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  எனில் (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      மரம் transform = NULL_மரம், sizes, body = NULL_மரம்;
      முழு மொத்தம் = 0;
      தேர்வு (c_parser_peek_token (parser)->pragma_kind)
	{
	நிலை PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = தள்ளு_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = எடு_stmt_list (body);
	  எனில் (transform == NULL_மரம் || transform == error_mark_முனை)
	    {
	      transform = error_mark_முனை;
	      நிறுத்து;
	    }
	  gcc_assert (மரம்_CODE (transform) == OMP_UNROLL);
	  எனில் (omp_find_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      எனில் (omp_for_parse_state->மொத்தம் - depth > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->மொத்தம் - depth);
		  transform = error_mark_முனை;
		}
	      இல்லையெனில்
		மொத்தம் = 1;
	    }
	  இல்லையெனில்
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_முனை;
	    }
	  நிறுத்து;
	நிலை PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = தள்ளு_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = எடு_stmt_list (body);
	  எனில் (transform == NULL_மரம் || transform == error_mark_முனை)
	    {
	      transform = error_mark_முனை;
	      நிறுத்து;
	    }
	  gcc_assert (மரம்_CODE (transform) == OMP_TILE);
	  sizes = omp_find_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  மொத்தம் = list_length (OMP_CLAUSE_SIZES_LIST (sizes));
	  எனில் (depth + மொத்தம் < omp_for_parse_state->மொத்தம்)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			மொத்தம், omp_for_parse_state->மொத்தம் - depth);
	      transform = error_mark_முனை;
	    }
	  நிறுத்து;
	இயல்பு:
	  c_parser_pragma (parser, pragma_stmt, வெற்று, void_list_முனை);
	  நிறுத்து;
	}
      எனில் (transform == NULL_மரம்)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      எனில் (transform == NULL_மரம் || transform == error_mark_முனை)
	{
	  omp_for_parse_state->fail = உண்மை;
	  திரும்பு NULL_மரம்;
	}
      க்கு (மொத்தம் = omp_for_parse_state->மொத்தம்; depth < மொத்தம்; ++depth)
	{
	  மரம்_VEC_ELT (omp_for_parse_state->declv, depth) = NULL_மரம்;
	  மரம்_VEC_ELT (omp_for_parse_state->initv, depth) = NULL_மரம்;
	  மரம்_VEC_ELT (omp_for_parse_state->condv, depth) = NULL_மரம்;
	  மரம்_VEC_ELT (omp_for_parse_state->incrv, depth) = NULL_மரம்;
	}
      omp_for_parse_state->want_nested_loop = பொய்;
      திரும்பு body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_in_statement = in_statement;
  in_statement = IN_OMP_BLOCK;

  /* We are not in intervening code now.  */
  omp_for_parse_state->in_intervening_code = பொய்;

  எனில் (!parens.require_open (parser))
    {
      omp_for_parse_state->fail = உண்மை;
      திரும்பு NULL_மரம்;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (உண்மை);

  /* Parse the initialization declaration or expression.  */
  எனில் (c_parser_next_tokens_start_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      மரம் this_pre_body = தள்ளு_stmt_list ();
      c_in_omp_for = உண்மை;
      c_parser_declaration_or_fndef (parser, உண்மை, உண்மை, உண்மை, உண்மை, உண்மை,
				     பொய்);
      c_in_omp_for = பொய்;
      this_pre_body = எடு_stmt_list (this_pre_body);
      append_to_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      எனில் (decl == வெற்று)
	செல் error_init;
      எனில் (DECL_INITIAL (decl) == error_mark_முனை)
	decl = error_mark_முனை;
      init = decl;
    }
  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      கட்டமைப்பு c_கோவை decl_exp;
      கட்டமைப்பு c_கோவை init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_expression (parser);
      decl = decl_exp.மதிப்பு;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_கோவை_no_commas (parser, வெற்று);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_in_omp_for = உண்மை;
      init = build_modify_கோவை (init_loc, decl, decl_exp.original_type,
				NOP_கோவை, init_loc, init_exp.மதிப்பு,
				init_exp.original_type);
      c_in_omp_for = பொய்;
      init = c_process_கோவை_stmt (init_loc, init);

      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  இல்லையெனில்
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->fail = உண்மை;
      செல் parse_next;
    }

  /* Parse the loop condition.  */
  எனில் (c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_in_omp_for = உண்மை;
      கட்டமைப்பு c_கோவை cond_கோவை
	= c_parser_இருமம்_expression (parser, வெற்று, NULL_மரம்);
      c_in_omp_for = பொய்;

      cond = cond_கோவை.மதிப்பு;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      தேர்வு (cond_கோவை.original_code)
	{
	நிலை GT_கோவை:
	நிலை GE_கோவை:
	நிலை LT_கோவை:
	நிலை LE_கோவை:
	  நிறுத்து;
	நிலை NE_கோவை:
	  எனில் (omp_for_parse_state->code != OACC_LOOP)
	    நிறுத்து;
	  /* FALLTHRU.  */
	இயல்பு:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_கோவை, boolean_type_முனை, error_mark_முனை);
	  நிறுத்து;
	}
      protected_set_கோவை_location (cond, cond_loc);
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  எனில் (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_கோவை_stmt (incr_loc,
				  c_parser_expression (parser).மதிப்பு);
    }
  parens.skip_until_found_close (parser);

  எனில் (decl == வெற்று || decl == error_mark_முனை || init == error_mark_முனை)
    omp_for_parse_state->fail = உண்மை;
  இல்லையெனில்
    {
      மரம்_VEC_ELT (omp_for_parse_state->declv, depth) = decl;
      மரம்_VEC_ELT (omp_for_parse_state->initv, depth) = init;
      மரம்_VEC_ELT (omp_for_parse_state->condv, depth) = cond;
      மரம்_VEC_ELT (omp_for_parse_state->incrv, depth) = incr;
    }

parse_next:
  moreloops = depth < omp_for_parse_state->மொத்தம் - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  எனில் (moreloops
      && c_parser_omp_next_tokens_can_be_canon_loop (parser,
						     omp_for_parse_state->code,
						     பொய்))
    {
      omp_for_parse_state->depth++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->depth--;
    }
  இல்லையெனில் எனில் (moreloops && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* This is the open brace in the loop-body grammar production.  Rather
	 than trying to special-case braces, just parse it as a compound
	 statement and handle the nested loop-body case there.  Note that
	 when we see a further open brace inside the compound statement
	 loop-body, we don't know whether it is the start of intervening
	 code that is a compound statement, or a level of braces
	 surrounding a nested loop-body.  Use the WANT_NESTED_LOOP state
	 bit to ensure we have only one nested loop at each level.  */
      omp_for_parse_state->in_intervening_code = உண்மை;
      body = c_parser_compound_statement (parser, வெற்று);
      omp_for_parse_state->in_intervening_code = பொய்;
      எனில் (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = உண்மை;
	}
      if_p = வெற்று;
    }
  இல்லையெனில்
    {
      /* This is the final-loop-body case in the grammar: we have
	 something that is not a FOR and not an open brace.  */
      எனில் (moreloops)
	{
	  /* If we were expecting a nested loop, give an error and mark
	     that parsing has failed, and try to recover by parsing the
	     body as regular code without further collapsing.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = உண்மை;
	}
      in_statement = IN_OMP_FOR;
      parser->omp_for_parse_state = வெற்று;
      body = தள்ளு_stmt_list ();
      எனில் (omp_for_parse_state->inscan)
	c_parser_omp_scan_loop_body (parser, பொய்);
      இல்லையெனில்
	add_stmt (c_parser_c99_block_statement (parser, if_p));
      body = எடு_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  in_statement = save_in_statement;
  omp_for_parse_state->want_nested_loop = பொய்;
  omp_for_parse_state->in_intervening_code = உண்மை;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  எனில் (body)
    add_stmt (body);
  body = c_end_compound_stmt (loc, loop_scope, உண்மை);
  எனில் (decl && மரம்_CODE (body) == BIND_கோவை)
    {
      மரம் t = BIND_கோவை_VARS (body);
      மரம் prev = NULL_மரம், next = NULL_மரம்;
      போது (t)
	{
	  next = DECL_CHAIN (t);
	  எனில் (t == decl)
	    {
	      எனில் (prev)
		DECL_CHAIN (prev) = next;
	      இல்லையெனில்
		{
		  BIND_கோவை_VARS (body) = next;
		  BLOCK_VARS (BIND_கோவை_BLOCK (body)) = next;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      நிறுத்து;
	    }
	  இல்லையெனில்
	    {
	      prev = t;
	      t = next;
	    }
	}
      எனில் (BIND_கோவை_VARS (body) == NULL_மரம்)
	body = BIND_கோவை_BODY (body);
    }

  திரும்பு body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

நிலையான மரம்
c_parser_omp_for_loop (location_t loc, c_parser *parser, எண்ணிக்கை மரம்_code code,
		       மரம் clauses, மரம் *cclauses, தருக்க *if_p)
{
  மரம் body, stmt, cl;
  மரம் ret = NULL_மரம்;
  மரம் ordered_cl = NULL_மரம்;
  முழு i, collapse = 1, ordered = 0, மொத்தம்;
  தருக்க oacc_tiling = பொய்;
  தருக்க inscan = பொய்;
  கட்டமைப்பு omp_for_parse_data data;
  கட்டமைப்பு omp_for_parse_data *save_data = parser->omp_for_parse_state;

  க்கு (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    எனில் (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = மரம்_to_shwi (OMP_CLAUSE_COLLAPSE_கோவை (cl));
    இல்லையெனில் எனில் (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = உண்மை;
	collapse = list_length (OMP_CLAUSE_TILE_LIST (cl));
      }
    இல்லையெனில் எனில் (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_SIZES)
      collapse = list_length (OMP_CLAUSE_SIZES_LIST (cl));
    இல்லையெனில் எனில் (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_கோவை (cl))
      {
	ordered_cl = cl;
	ordered = மரம்_to_shwi (OMP_CLAUSE_ORDERED_கோவை (cl));
      }
    இல்லையெனில் எனில் (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (code == OMP_SIMD || code == OMP_FOR))
      inscan = உண்மை;

  எனில் (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_கோவை (ordered_cl)
	= build_int_cst (integer_type_முனை, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  மொத்தம் = ordered ? ordered : collapse;

  எனில் (!c_parser_omp_next_tokens_can_be_canon_loop (parser, code, உண்மை))
    திரும்பு வெற்று;

  /* Initialize parse state for recursive descent.  */
  data.declv = make_மரம்_vec (மொத்தம்);
  data.initv = make_மரம்_vec (மொத்தம்);
  data.condv = make_மரம்_vec (மொத்தம்);
  data.incrv = make_மரம்_vec (மொத்தம்);
  data.pre_body = NULL_மரம்;
  data.bindings = NULL_மரம்;
  data.for_loc = c_parser_peek_token (parser)->location;
  data.மொத்தம் = மொத்தம்;
  data.depth = 0;
  data.want_nested_loop = உண்மை;
  data.ordered = ordered > 0;
  data.in_intervening_code = பொய்;
  data.perfect_nesting_fail = பொய்;
  data.fail = பொய்;
  data.inscan = inscan;
  data.saw_intervening_code = பொய்;
  data.code = code;
  parser->omp_for_parse_state = &data;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  க்கு (மரம் t = data.bindings; t; )
    {
      மரம் n = மரம்_CHAIN (t);
      மரம்_CHAIN (t) = NULL_மரம்;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  எனில் (!data.fail)
    {
      c_in_omp_for = உண்மை;
      stmt = c_finish_omp_for (loc, code, data.declv, வெற்று, data.initv,
			       data.condv, data.incrv,
			       body, data.pre_body, உண்மை);
      c_in_omp_for = பொய்;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      எனில் (stmt && !c_omp_check_loop_iv (stmt, data.declv, வெற்று))
	stmt = NULL_மரம்;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      எனில் (data.saw_intervening_code
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, வெற்று))
	stmt = NULL_மரம்;

      எனில் (stmt)
	{
	  add_stmt (stmt);

	  க்கு (i = 0; i < மரம்_VEC_LENGTH (OMP_FOR_INIT (stmt)); i++)
	    {
	      மரம் init = மரம்_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      எனில் (init == NULL_மரம்)
		நிறுத்து;
	      gcc_assert (மரம்_CODE (init) == MODIFY_கோவை);
	      மரம் decl = மரம்_OPERAND (init, 0);
	      மரம் cond = மரம்_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (மரம்_OPERAND (cond, 0) == decl);

	      மரம் op0 = மரம்_OPERAND (init, 1);
	      எனில் (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || மரம்_CODE (op0) != மரம்_VEC)
		மரம்_OPERAND (init, 1) = c_fully_fold (op0, பொய், வெற்று);
	      இல்லையெனில்
		{
		  மரம்_VEC_ELT (op0, 1)
		    = c_fully_fold (மரம்_VEC_ELT (op0, 1), பொய், வெற்று);
		  மரம்_VEC_ELT (op0, 2)
		    = c_fully_fold (மரம்_VEC_ELT (op0, 2), பொய், வெற்று);
		}

	      மரம் op1 = மரம்_OPERAND (cond, 1);
	      எனில் (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || மரம்_CODE (op1) != மரம்_VEC)
		மரம்_OPERAND (cond, 1) = c_fully_fold (op1, பொய், வெற்று);
	      இல்லையெனில்
		{
		  மரம்_VEC_ELT (op1, 1)
		    = c_fully_fold (மரம்_VEC_ELT (op1, 1), பொய், வெற்று);
		  மரம்_VEC_ELT (op1, 2)
		    = c_fully_fold (மரம்_VEC_ELT (op1, 2), பொய், வெற்று);
		}
	    }

	  எனில் (cclauses != வெற்று
	      && cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL] != வெற்று)
	    {
	      மரம் *c;
	      க்கு (c = &cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL]; *c ; )
		எனில் (OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		இல்லையெனில்
		  {
		    க்கு (i = 0; i < மொத்தம்; i++)
		      எனில் (மரம்_VEC_ELT (data.declv, i) == OMP_CLAUSE_DECL (*c))
			நிறுத்து;
		    எனில் (i == மொத்தம்)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    இல்லையெனில் எனில் (OMP_CLAUSE_CODE (*c) == OMP_CLAUSE_FIRSTPRIVATE)
		      {
			error_at (loc,
				  "iteration variable %qD should not be firstprivate",
				  OMP_CLAUSE_DECL (*c));
			*c = OMP_CLAUSE_CHAIN (*c);
		      }
		    இல்லையெனில்
		      {
			/* Move lastprivate (decl) clause to
			   OMP_FOR_CLAUSES.  */
			மரம் l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			எனில் (code == OMP_SIMD)
			  {
			    OMP_CLAUSE_CHAIN (l)
			      = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
			    cclauses[C_OMP_CLAUSE_SPLIT_FOR] = l;
			  }
			இல்லையெனில்
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
  திரும்பு ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

நிலையான வெறுமை
omp_split_clauses (location_t loc, எண்ணிக்கை மரம்_code code,
		   omp_clause_mask mask, மரம் clauses, மரம் *cclauses)
{
  முழு i;
  c_omp_split_clauses (loc, code, mask, clauses, cclauses);
  க்கு (i = 0; i < C_OMP_CLAUSE_SPLIT_மொத்தம்; i++)
    எனில் (cclauses[i])
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

நிலையான மரம்
c_parser_omp_loop (location_t loc, c_parser *parser,
		   எழுத்து *p_name, omp_clause_mask mask, மரம் *cclauses,
		   தருக்க *if_p)
{
  மரம் block, clauses, ret;

  strcat (p_name, " loop");
  mask |= OMP_LOOP_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == வெற்று);
  எனில் (cclauses)
    {
      omp_split_clauses (loc, OMP_LOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_LOOP];
    }

  block = c_begin_compound_stmt (உண்மை);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, உண்மை);
  add_stmt (block);

  திரும்பு ret;
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

நிலையான மரம்
c_parser_omp_simd (location_t loc, c_parser *parser,
		   எழுத்து *p_name, omp_clause_mask mask, மரம் *cclauses,
		   தருக்க *if_p)
{
  மரம் block, clauses, ret;

  strcat (p_name, " simd");
  mask |= OMP_SIMD_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == வெற்று);
  எனில் (cclauses)
    {
      omp_split_clauses (loc, OMP_SIMD, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SIMD];
    }

  block = c_begin_compound_stmt (உண்மை);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, உண்மை);
  add_stmt (block);

  திரும்பு ret;
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

நிலையான மரம்
c_parser_omp_for (location_t loc, c_parser *parser,
		  எழுத்து *p_name, omp_clause_mask mask, மரம் *cclauses,
		  தருக்க *if_p)
{
  மரம் block, clauses, ret;

  strcat (p_name, " for");
  mask |= OMP_FOR_CLAUSE_MASK;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  எனில் (cclauses && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  எனில் ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);

      எனில் (strcmp (p, "simd") == 0)
	{
	  மரம் cclauses_buf[C_OMP_CLAUSE_SPLIT_மொத்தம்];
	  எனில் (cclauses == வெற்று)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  எனில் (!flag_openmp)  /* flag_openmp_simd  */
	    திரும்பு c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (உண்மை);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, உண்மை);
	  எனில் (ret == NULL_மரம்)
	    திரும்பு ret;
	  ret = make_முனை (OMP_FOR);
	  மரம்_TYPE (ret) = void_type_முனை;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
	  SET_கோவை_LOCATION (ret, loc);
	  add_stmt (ret);
	  திரும்பு ret;
	}
    }
  எனில் (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, பொய்);
      திரும்பு NULL_மரம்;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  எனில் ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINEAR);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == வெற்று);
  எனில் (cclauses)
    {
      omp_split_clauses (loc, OMP_FOR, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
    }

  block = c_begin_compound_stmt (உண்மை);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, உண்மை);
  add_stmt (block);

  திரும்பு ret;
}

நிலையான மரம் c_parser_omp_taskloop (location_t, c_parser *, எழுத்து *,
				   omp_clause_mask, மரம் *, தருக்க *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

நிலையான மரம்
c_parser_omp_master (location_t loc, c_parser *parser,
		     எழுத்து *p_name, omp_clause_mask mask, மரம் *cclauses,
		     தருக்க *if_p, location_t master_loc)
{
  மரம் block, clauses, ret;
  gcc_rich_location richloc (loc);
  எனில் (master_loc != UNKNOWN_LOCATION)
    richloc.add_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  strcat (p_name, " master");

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);

      எனில் (strcmp (p, "taskloop") == 0)
	{
	  மரம் cclauses_buf[C_OMP_CLAUSE_SPLIT_மொத்தம்];
	  எனில் (cclauses == வெற்று)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  எனில் (!flag_openmp)  /* flag_openmp_simd  */
	    திரும்பு c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (உண்மை);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, உண்மை);
	  எனில் (ret == NULL_மரம்)
	    திரும்பு ret;
	  ret = c_finish_omp_master (loc, block);
	  OMP_MASTER_COMBINED (ret) = 1;
	  திரும்பு ret;
	}
    }
  எனில் (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, பொய்);
      திரும்பு NULL_மரம்;
    }

  எனில் (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, mask, p_name, பொய்);
      omp_split_clauses (loc, OMP_MASTER, mask, clauses, cclauses);
    }
  இல்லையெனில்
    c_parser_skip_to_pragma_eol (parser);

  திரும்பு c_finish_omp_master (loc, c_parser_omp_structured_block (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#define OMP_MASKED_CLAUSE_MASK					\
	(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FILTER)

நிலையான மரம்
c_parser_omp_masked (location_t loc, c_parser *parser,
		     எழுத்து *p_name, omp_clause_mask mask, மரம் *cclauses,
		     தருக்க *if_p)
{
  மரம் block, clauses, ret;

  strcat (p_name, " masked");
  mask |= OMP_MASKED_CLAUSE_MASK;

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);

      எனில் (strcmp (p, "taskloop") == 0)
	{
	  மரம் cclauses_buf[C_OMP_CLAUSE_SPLIT_மொத்தம்];
	  எனில் (cclauses == வெற்று)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  எனில் (!flag_openmp)  /* flag_openmp_simd  */
	    திரும்பு c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (உண்மை);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, உண்மை);
	  எனில் (ret == NULL_மரம்)
	    திரும்பு ret;
	  ret = c_finish_omp_masked (loc, block,
				     cclauses[C_OMP_CLAUSE_SPLIT_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  திரும்பு ret;
	}
    }
  எனில் (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, பொய்);
      திரும்பு NULL_மரம்;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == வெற்று);
  எனில் (cclauses)
    {
      omp_split_clauses (loc, OMP_MASKED, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_MASKED];
    }

  திரும்பு c_finish_omp_masked (loc, c_parser_omp_structured_block (parser,
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

நிலையான வெறுமை
c_parser_omp_interop (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  மரம் clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_MASK,
					   "#pragma omp interop");
  மரம் stmt = make_முனை (OMP_INTEROP);
  மரம்_TYPE (stmt) = void_type_முனை;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  SET_கோவை_LOCATION (stmt, loc);
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

நிலையான தருக்க
c_parser_omp_ordered (c_parser *parser, எண்ணிக்கை pragma_context context,
		      தருக்க *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  எனில் (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, பொய்);
      திரும்பு பொய்;
    }

  முழு n = 1;
  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
    n = 2;

  எனில் (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      மாறிலி எழுத்து *p
	= IDENTIFIER_POINTER (c_parser_peek_nth_token (parser, n)->மதிப்பு);

      எனில் (!strcmp ("depend", p) || !strcmp ("doacross", p))
	{
	  எனில் (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_to_pragma_eol (parser, பொய்);
	      திரும்பு பொய்;
	    }
	  எனில் (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_to_pragma_eol (parser, பொய்);
	      திரும்பு உண்மை;
	    }

	  மரம் clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_MASK,
					"#pragma omp ordered");
	  c_finish_omp_ordered (loc, clauses, NULL_மரம்);
	  திரும்பு பொய்;
	}
    }

  மரம் clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_MASK,
					   "#pragma omp ordered");

  எனில் (!flag_openmp	/* flag_openmp_simd  */
      && omp_find_clause (clauses, OMP_CLAUSE_SIMD) == NULL_மரம்)
    திரும்பு பொய்;

  c_finish_omp_ordered (loc, clauses,
			c_parser_omp_structured_block (parser, if_p));
  திரும்பு உண்மை;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

நிலையான மரம்
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  மரம் stmt, substmt;
  தருக்க error_suppress = பொய்;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  எனில் (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = பொய்;
      திரும்பு NULL_மரம்;
    }

  stmt = தள்ளு_stmt_list ();

  எனில் (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_scan (parser, "section", உண்மை))
    {
      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_முனை, substmt);
      SET_கோவை_LOCATION (substmt, loc);
      add_stmt (substmt);
    }

  போது (1)
    {
      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	நிறுத்து;
      எனில் (c_parser_next_token_is (parser, CPP_EOF))
	நிறுத்து;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_scan (parser, "section", பொய்);
      எனில் (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser);
	  error_suppress = பொய்;
	}
      இல்லையெனில் எனில் (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = உண்மை;
	}

      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_முனை, substmt);
      SET_கோவை_LOCATION (substmt, loc);
      add_stmt (substmt);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = எடு_stmt_list (stmt);

  stmt = make_முனை (OMP_SECTIONS);
  SET_கோவை_LOCATION (stmt, sections_loc);
  மரம்_TYPE (stmt) = void_type_முனை;
  OMP_SECTIONS_BODY (stmt) = substmt;

  திரும்பு add_stmt (stmt);
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

நிலையான மரம்
c_parser_omp_sections (location_t loc, c_parser *parser,
		       எழுத்து *p_name, omp_clause_mask mask, மரம் *cclauses)
{
  மரம் block, clauses, ret;

  strcat (p_name, " sections");
  mask |= OMP_SECTIONS_CLAUSE_MASK;
  எனில் (cclauses)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == வெற்று);
  எனில் (cclauses)
    {
      omp_split_clauses (loc, OMP_SECTIONS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SECTIONS];
    }

  block = c_begin_compound_stmt (உண்மை);
  ret = c_parser_omp_sections_scope (loc, parser);
  எனில் (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  block = c_end_compound_stmt (loc, block, உண்மை);
  add_stmt (block);

  திரும்பு ret;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_இலக்கம்_THREADS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

நிலையான மரம்
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       எழுத்து *p_name, omp_clause_mask mask, மரம் *cclauses,
		       தருக்க *if_p)
{
  மரம் stmt, clauses, block;

  strcat (p_name, " parallel");
  mask |= OMP_PARALLEL_CLAUSE_MASK;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  எனில் ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  எனில் (c_parser_next_token_is_keyword (parser, RID_FOR))
    {
      மரம் cclauses_buf[C_OMP_CLAUSE_SPLIT_மொத்தம்];
      எனில் (cclauses == வெற்று)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      எனில் (!flag_openmp)  /* flag_openmp_simd  */
	திரும்பு c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      block = c_begin_omp_parallel ();
      மரம் ret = c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      stmt
	= c_finish_omp_parallel (loc, cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				 block);
      எனில் (ret == NULL_மரம்)
	திரும்பு ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      திரும்பு stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  இல்லையெனில் எனில் (cclauses
	   && (mask & (OMP_CLAUSE_MASK_1
		       << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_to_pragma_eol (parser);
      திரும்பு NULL_மரம்;
    }
  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      location_t ploc = c_parser_peek_token (parser)->location;
      எனில் (cclauses == வெற்று && strcmp (p, "masked") == 0)
	{
	  மரம் cclauses_buf[C_OMP_CLAUSE_SPLIT_மொத்தம்];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  எனில் (!flag_openmp)  /* flag_openmp_simd  */
	    திரும்பு c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					if_p);
	  block = c_begin_omp_parallel ();
	  மரம் ret = c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					  if_p);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  எனில் (ret == வெற்று)
	    திரும்பு ret;
	  /* masked does have just filter clause, but during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel masked don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel masked
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel masked taskloop simd lastprivate (x)  */
	  எனில் (OMP_MASKED_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  திரும்பு stmt;
	}
      இல்லையெனில் எனில் (cclauses == வெற்று && strcmp (p, "master") == 0)
	{
	  மரம் cclauses_buf[C_OMP_CLAUSE_SPLIT_மொத்தம்];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  எனில் (!flag_openmp)  /* flag_openmp_simd  */
	    திரும்பு c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					if_p, ploc);
	  block = c_begin_omp_parallel ();
	  மரம் ret = c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					  if_p, ploc);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  எனில் (ret == வெற்று)
	    திரும்பு ret;
	  /* master doesn't have any clauses and during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel master don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel master
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel master taskloop simd lastprivate (x)  */
	  எனில் (OMP_MASTER_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  திரும்பு stmt;
	}
      இல்லையெனில் எனில் (strcmp (p, "loop") == 0)
	{
	  மரம் cclauses_buf[C_OMP_CLAUSE_SPLIT_மொத்தம்];
	  எனில் (cclauses == வெற்று)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  எனில் (!flag_openmp)  /* flag_openmp_simd  */
	    திரும்பு c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  மரம் ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
					if_p);
	  stmt
	    = c_finish_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				     block);
	  எனில் (ret == NULL_மரம்)
	    திரும்பு ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  திரும்பு stmt;
	}
      இல்லையெனில் எனில் (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, பொய்);
	  திரும்பு NULL_மரம்;
	}
      இல்லையெனில் எனில் (cclauses == வெற்று && strcmp (p, "sections") == 0)
	{
	  மரம் cclauses_buf[C_OMP_CLAUSE_SPLIT_மொத்தம்];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  block = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, mask, cclauses);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  திரும்பு stmt;
	}
    }
  இல்லையெனில் எனில் (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, பொய்);
      திரும்பு NULL_மரம்;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == வெற்று);
  எனில் (cclauses)
    {
      omp_split_clauses (loc, OMP_PARALLEL, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL];
    }

  block = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = உண்மை;
  c_parser_statement (parser, if_p);
  stmt = c_finish_omp_parallel (loc, clauses, block);

  திரும்பு stmt;
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

நிலையான மரம்
c_parser_omp_single (location_t loc, c_parser *parser, தருக்க *if_p)
{
  மரம் stmt = make_முனை (OMP_SINGLE);
  SET_கோவை_LOCATION (stmt, loc);
  மரம்_TYPE (stmt) = void_type_முனை;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_MASK,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  திரும்பு add_stmt (stmt);
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

நிலையான மரம்
c_parser_omp_scope (location_t loc, c_parser *parser, தருக்க *if_p)
{
  மரம் stmt = make_முனை (OMP_SCOPE);
  SET_கோவை_LOCATION (stmt, loc);
  மரம்_TYPE (stmt) = void_type_முனை;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_MASK,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  திரும்பு add_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
நிலையான மரம்
c_parser_omp_dispatch_body (c_parser *parser)
{
  கட்டமைப்பு c_கோவை lhs, rhs, ret;
  location_t கோவை_loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_expression (parser, வெற்று, வெற்று);
  எனில் (மரம்_CODE (lhs.மதிப்பு) == CALL_கோவை)
    திரும்பு lhs.மதிப்பு;

  location_t op_location = c_parser_peek_token (parser)->location;
  எனில் (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    திரும்பு error_mark_முனை;

  /* Parse function name.  */
  எனில் (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      திரும்பு error_mark_முனை;
    }
  கோவை_loc = c_parser_peek_token (parser)->location;
  மரம் id = c_parser_peek_token (parser)->மதிப்பு;
  c_parser_consume_token (parser);
  எனில் (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      திரும்பு error_mark_முனை;
    }

  rhs.மதிப்பு = build_external_ref (கோவை_loc, id, உண்மை, &rhs.original_type);
  set_c_கோவை_source_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_expression_after_primary (
    parser, கோவை_LOC_OR_LOC (rhs.மதிப்பு, கோவை_loc), rhs);
  எனில் (மரம்_CODE (rhs.மதிப்பு) != CALL_கோவை)
    {
      error_at (கோவை_LOC_OR_LOC (rhs.மதிப்பு, கோவை_loc),
		"expected target-function call");
      திரும்பு error_mark_முனை;
    }

  /* Build assignment. */
  rhs = convert_lvalue_to_rvalue (கோவை_loc, rhs, உண்மை, உண்மை);
  ret.மதிப்பு
    = build_modify_கோவை (op_location, lhs.மதிப்பு, lhs.original_type, NOP_கோவை,
			 கோவை_loc, rhs.மதிப்பு, rhs.original_type);
  ret.m_decimal = 0;
  set_c_கோவை_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  ret.original_code = MODIFY_கோவை;
  ret.original_type = வெற்று;
  திரும்பு ret.மதிப்பு;
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

நிலையான மரம்
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  மரம் stmt = make_முனை (OMP_DISPATCH);
  SET_கோவை_LOCATION (stmt, loc);
  மரம்_TYPE (stmt) = void_type_முனை;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_MASK,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  மரம் depend_clauses = NULL_மரம்;
  மரம் *depend_clauses_ptr = &depend_clauses;
  க்கு (மரம் c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  எனில் (depend_clauses != NULL_மரம்)
    {
      மரம் stmt = make_முனை (OMP_TASK);
      மரம்_TYPE (stmt) = void_முனை;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_மரம்;
      SET_கோவை_LOCATION (stmt, loc);
      add_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  மரம் dispatch_body = c_parser_omp_dispatch_body (parser);
  எனில் (dispatch_body == error_mark_முனை)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_to_end_of_block_or_statement (parser);
      திரும்பு NULL_மரம்;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (மரம்_CODE (dispatch_body) == CALL_கோவை
	      || மரம்_CODE (dispatch_body) == MODIFY_கோவை);
  மரம் *dispatch_call = மரம்_CODE (dispatch_body) == MODIFY_கோவை
			  ? &மரம்_OPERAND (dispatch_body, 1)
			  : &dispatch_body;
  போது (மரம்_CODE (*dispatch_call) == FLOAT_கோவை
	 || மரம்_CODE (*dispatch_call) == CONVERT_கோவை
	 || மரம்_CODE (*dispatch_call) == NOP_கோவை)
    dispatch_call = &மரம்_OPERAND (*dispatch_call, 0);
  *dispatch_call = build_call_கோவை_internal_loc (
    loc, IFN_GOMP_DISPATCH,
    மரம்_TYPE (மரம்_TYPE (CALL_கோவை_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  திரும்பு add_stmt (stmt);
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

நிலையான மரம்
c_parser_omp_task (location_t loc, c_parser *parser, தருக்க *if_p)
{
  மரம் clauses, block;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_MASK,
				      "#pragma omp task");

  block = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = உண்மை;
  c_parser_statement (parser, if_p);
  திரும்பு c_finish_omp_task (loc, clauses, block);
}

/* OpenMP 3.0:
   # pragma omp taskwait new-line

   OpenMP 5.0:
   # pragma omp taskwait taskwait-clause[optseq] new-line
*/

#define OMP_TASKWAIT_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

நிலையான வெறுமை
c_parser_omp_taskwait (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  மரம் clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_MASK,
				"#pragma omp taskwait");

  எனில் (clauses)
    {
      மரம் stmt = make_முனை (OMP_TASK);
      மரம்_TYPE (stmt) = void_முனை;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_மரம்;
      SET_கோவை_LOCATION (stmt, loc);
      add_stmt (stmt);
    }
  இல்லையெனில்
    c_finish_omp_taskwait (loc);
}

/* OpenMP 3.1:
   # pragma omp taskyield new-line
*/

நிலையான வெறுமை
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

நிலையான மரம்
c_parser_omp_taskgroup (location_t loc, c_parser *parser, தருக்க *if_p)
{
  மரம் clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_MASK,
					   "#pragma omp taskgroup");

  மரம் body = c_parser_omp_structured_block (parser, if_p);
  திரும்பு c_finish_omp_taskgroup (loc, body, clauses);
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

நிலையான வெறுமை
c_parser_omp_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);
  மரம் clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_MASK,
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

நிலையான தருக்க
c_parser_omp_cancellation_point (c_parser *parser, எண்ணிக்கை pragma_context context)
{
  location_t loc = c_parser_peek_token (parser)->location;
  மரம் clauses;
  தருக்க point_seen = பொய்;

  c_parser_consume_pragma (parser);
  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  point_seen = உண்மை;
	}
    }
  எனில் (!point_seen)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_to_pragma_eol (parser);
      திரும்பு பொய்;
    }

  எனில் (context != pragma_compound)
    {
      எனில் (context == pragma_stmt)
	error_at (loc,
		  "%<#pragma %s%> may only be used in compound statements",
		  "omp cancellation point");
      இல்லையெனில்
	c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, பொய்);
      திரும்பு உண்மை;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_POINT_CLAUSE_MASK,
				"#pragma omp cancellation point");

  c_finish_omp_cancellation_point (loc, clauses);
  திரும்பு உண்மை;
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

நிலையான மரம்
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 எழுத்து *p_name, omp_clause_mask mask, மரம் *cclauses,
			 தருக்க *if_p)
{
  மரம் clauses, block, ret;

  strcat (p_name, " distribute");
  mask |= OMP_DISTRIBUTE_CLAUSE_MASK;

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      தருக்க simd = பொய்;
      தருக்க parallel = பொய்;

      எனில் (strcmp (p, "simd") == 0)
	simd = உண்மை;
      இல்லையெனில்
	parallel = strcmp (p, "parallel") == 0;
      எனில் (parallel || simd)
	{
	  மரம் cclauses_buf[C_OMP_CLAUSE_SPLIT_மொத்தம்];
	  எனில் (cclauses == வெற்று)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  எனில் (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      எனில் (simd)
		திரும்பு c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
					  if_p);
	      இல்லையெனில்
		திரும்பு c_parser_omp_parallel (loc, parser, p_name, mask,
					      cclauses, if_p);
	    }
	  block = c_begin_compound_stmt (உண்மை);
	  எனில் (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				     if_p);
	  இல்லையெனில்
	    ret = c_parser_omp_parallel (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, உண்மை);
	  எனில் (ret == வெற்று)
	    திரும்பு ret;
	  ret = make_முனை (OMP_DISTRIBUTE);
	  மரம்_TYPE (ret) = void_type_முனை;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
	  SET_கோவை_LOCATION (ret, loc);
	  add_stmt (ret);
	  திரும்பு ret;
	}
    }
  எனில் (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, பொய்);
      திரும்பு NULL_மரம்;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == வெற்று);
  எனில் (cclauses)
    {
      omp_split_clauses (loc, OMP_DISTRIBUTE, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
    }

  block = c_begin_compound_stmt (உண்மை);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, வெற்று,
			       if_p);
  block = c_end_compound_stmt (loc, block, உண்மை);
  add_stmt (block);

  திரும்பு ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#define OMP_TEAMS_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_இலக்கம்_TEAMS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_THREAD_LIMIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

நிலையான மரம்
c_parser_omp_teams (location_t loc, c_parser *parser,
		    எழுத்து *p_name, omp_clause_mask mask, மரம் *cclauses,
		    தருக்க *if_p)
{
  மரம் clauses, block, ret;

  strcat (p_name, " teams");
  mask |= OMP_TEAMS_CLAUSE_MASK;

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp (p, "distribute") == 0)
	{
	  மரம் cclauses_buf[C_OMP_CLAUSE_SPLIT_மொத்தம்];
	  எனில் (cclauses == வெற்று)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  எனில் (!flag_openmp)  /* flag_openmp_simd  */
	    திரும்பு c_parser_omp_distribute (loc, parser, p_name, mask,
					    cclauses, if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, உண்மை);
	  எனில் (ret == வெற்று)
	    திரும்பு ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_முனை (OMP_TEAMS);
	  மரம்_TYPE (ret) = void_type_முனை;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_கோவை_LOCATION (ret, loc);
	  திரும்பு add_stmt (ret);
	}
      இல்லையெனில் எனில் (strcmp (p, "loop") == 0)
	{
	  மரம் cclauses_buf[C_OMP_CLAUSE_SPLIT_மொத்தம்];
	  எனில் (cclauses == வெற்று)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  எனில் (!flag_openmp)  /* flag_openmp_simd  */
	    திரும்பு c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, உண்மை);
	  எனில் (ret == வெற்று)
	    திரும்பு ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_முனை (OMP_TEAMS);
	  மரம்_TYPE (ret) = void_type_முனை;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_கோவை_LOCATION (ret, loc);
	  திரும்பு add_stmt (ret);
	}
    }
  எனில் (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, பொய்);
      திரும்பு NULL_மரம்;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == வெற்று);
  எனில் (cclauses)
    {
      omp_split_clauses (loc, OMP_TEAMS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
    }

  மரம் stmt = make_முனை (OMP_TEAMS);
  மரம்_TYPE (stmt) = void_type_முனை;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_end_compound_stmt (loc, block, உண்மை);
  SET_கோவை_LOCATION (stmt, loc);

  திரும்பு add_stmt (stmt);
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

நிலையான மரம்
c_parser_omp_target_data (location_t loc, c_parser *parser, தருக்க *if_p)
{
  எனில் (flag_openmp)
    omp_requires_mask
      = (எண்ணிக்கை omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  மரம் clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_DATA_CLAUSE_MASK,
				"#pragma omp target data", பொய்);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, பொய்);
  முழு map_seen = 0;
  க்கு (மரம் *pc = &clauses; *pc;)
    {
      எனில் (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	தேர்வு (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  நிலை GOMP_MAP_TO:
	  நிலை GOMP_MAP_ALWAYS_TO:
	  நிலை GOMP_MAP_PRESENT_TO:
	  நிலை GOMP_MAP_ALWAYS_PRESENT_TO:
	  நிலை GOMP_MAP_FROM:
	  நிலை GOMP_MAP_ALWAYS_FROM:
	  நிலை GOMP_MAP_PRESENT_FROM:
	  நிலை GOMP_MAP_ALWAYS_PRESENT_FROM:
	  நிலை GOMP_MAP_TOFROM:
	  நிலை GOMP_MAP_ALWAYS_TOFROM:
	  நிலை GOMP_MAP_PRESENT_TOFROM:
	  நிலை GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  நிலை GOMP_MAP_ALLOC:
	  நிலை GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    நிறுத்து;
	  நிலை GOMP_MAP_FIRSTPRIVATE_POINTER:
	  நிலை GOMP_MAP_ALWAYS_POINTER:
	  நிலை GOMP_MAP_ATTACH_DETACH:
	  நிலை GOMP_MAP_ATTACH:
	    நிறுத்து;
	  இயல்பு:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    தொடர்;
	  }
      இல்லையெனில் எனில் (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_seen = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  எனில் (map_seen != 3)
    {
      எனில் (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      திரும்பு NULL_மரம்;
    }

  மரம் stmt = make_முனை (OMP_TARGET_DATA);
  மரம்_TYPE (stmt) = void_type_முனை;
  OMP_TARGET_DATA_CLAUSES (stmt) = clauses;
  keep_next_level ();
  மரம் block = c_begin_compound_stmt (உண்மை);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TARGET_DATA_BODY (stmt) = c_end_compound_stmt (loc, block, உண்மை);

  SET_கோவை_LOCATION (stmt, loc);
  திரும்பு add_stmt (stmt);
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

நிலையான தருக்க
c_parser_omp_target_update (location_t loc, c_parser *parser,
			    எண்ணிக்கை pragma_context context)
{
  எனில் (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_to_pragma_eol (parser, பொய்);
      திரும்பு உண்மை;
    }

  மரம் clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_UPDATE_CLAUSE_MASK,
				"#pragma omp target update",
				/* finish_p = */ பொய்);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  எனில் (omp_find_clause (clauses, OMP_CLAUSE_TO) == NULL_மரம்
      && omp_find_clause (clauses, OMP_CLAUSE_FROM) == NULL_மரம்)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      திரும்பு பொய்;
    }

  எனில் (flag_openmp)
    omp_requires_mask
      = (எண்ணிக்கை omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  மரம் stmt = make_முனை (OMP_TARGET_UPDATE);
  மரம்_TYPE (stmt) = void_type_முனை;
  OMP_TARGET_UPDATE_CLAUSES (stmt) = clauses;
  SET_கோவை_LOCATION (stmt, loc);
  add_stmt (stmt);
  திரும்பு பொய்;
}

/* OpenMP 4.5:
   # pragma omp target enter data target-data-clause[optseq] new-line  */

#define OMP_TARGET_ENTER_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

நிலையான தருக்க
c_parser_omp_target_enter_data (location_t loc, c_parser *parser,
				எண்ணிக்கை pragma_context context)
{
  தருக்க data_seen = பொய்;
  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = உண்மை;
	}
    }
  எனில் (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      திரும்பு பொய்;
    }

  எனில் (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_to_pragma_eol (parser, பொய்);
      திரும்பு உண்மை;
    }

  எனில் (flag_openmp)
    omp_requires_mask
      = (எண்ணிக்கை omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  மரம் clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_ENTER_DATA_CLAUSE_MASK,
				"#pragma omp target enter data", பொய்);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, பொய்);
  முழு map_seen = 0;
  க்கு (மரம் *pc = &clauses; *pc;)
    {
      எனில் (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	தேர்வு (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  நிலை GOMP_MAP_TO:
	  நிலை GOMP_MAP_ALWAYS_TO:
	  நிலை GOMP_MAP_PRESENT_TO:
	  நிலை GOMP_MAP_ALWAYS_PRESENT_TO:
	  நிலை GOMP_MAP_ALLOC:
	  நிலை GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    நிறுத்து;
	  நிலை GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_TO);
	    map_seen = 3;
	    நிறுத்து;
	  நிலை GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_TO);
	    map_seen = 3;
	    நிறுத்து;
	  நிலை GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_TO);
	    map_seen = 3;
	    நிறுத்து;
	  நிலை GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_TO);
	    map_seen = 3;
	    நிறுத்து;
	  நிலை GOMP_MAP_FIRSTPRIVATE_POINTER:
	  நிலை GOMP_MAP_ALWAYS_POINTER:
	  நிலை GOMP_MAP_ATTACH_DETACH:
	  நிலை GOMP_MAP_ATTACH:
	    நிறுத்து;
	  இயல்பு:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    தொடர்;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  எனில் (map_seen != 3)
    {
      எனில் (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      திரும்பு உண்மை;
    }

  மரம் stmt = make_முனை (OMP_TARGET_ENTER_DATA);
  மரம்_TYPE (stmt) = void_type_முனை;
  OMP_TARGET_ENTER_DATA_CLAUSES (stmt) = clauses;
  SET_கோவை_LOCATION (stmt, loc);
  add_stmt (stmt);
  திரும்பு உண்மை;
}

/* OpenMP 4.5:
   # pragma omp target exit data target-data-clause[optseq] new-line  */

#define OMP_TARGET_EXIT_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

நிலையான தருக்க
c_parser_omp_target_exit_data (location_t loc, c_parser *parser,
			       எண்ணிக்கை pragma_context context)
{
  தருக்க data_seen = பொய்;
  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = உண்மை;
	}
    }
  எனில் (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      திரும்பு பொய்;
    }

  எனில் (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_to_pragma_eol (parser, பொய்);
      திரும்பு உண்மை;
    }

  எனில் (flag_openmp)
    omp_requires_mask
      = (எண்ணிக்கை omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  மரம் clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_EXIT_DATA_CLAUSE_MASK,
				"#pragma omp target exit data", பொய்);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_DATA);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_EXIT_DATA);
  c_omp_adjust_map_clauses (clauses, பொய்);
  முழு map_seen = 0;
  க்கு (மரம் *pc = &clauses; *pc;)
    {
      எனில் (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	தேர்வு (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  நிலை GOMP_MAP_FROM:
	  நிலை GOMP_MAP_ALWAYS_FROM:
	  நிலை GOMP_MAP_PRESENT_FROM:
	  நிலை GOMP_MAP_ALWAYS_PRESENT_FROM:
	  நிலை GOMP_MAP_RELEASE:
	  நிலை GOMP_MAP_DELETE:
	    map_seen = 3;
	    நிறுத்து;
	  நிலை GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_FROM);
	    map_seen = 3;
	    நிறுத்து;
	  நிலை GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_seen = 3;
	    நிறுத்து;
	  நிலை GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_FROM);
	    map_seen = 3;
	    நிறுத்து;
	  நிலை GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_seen = 3;
	    நிறுத்து;
	  நிலை GOMP_MAP_FIRSTPRIVATE_POINTER:
	  நிலை GOMP_MAP_ALWAYS_POINTER:
	  நிலை GOMP_MAP_ATTACH_DETACH:
	  நிலை GOMP_MAP_DETACH:
	    நிறுத்து;
	  இயல்பு:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target exit data%> with map-type other "
		      "than %<from%>, %<tofrom%>, %<release%> or %<delete%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    தொடர்;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  எனில் (map_seen != 3)
    {
      எனில் (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      திரும்பு உண்மை;
    }

  மரம் stmt = make_முனை (OMP_TARGET_EXIT_DATA);
  மரம்_TYPE (stmt) = void_type_முனை;
  OMP_TARGET_EXIT_DATA_CLAUSES (stmt) = clauses;
  SET_கோவை_LOCATION (stmt, loc);
  add_stmt (stmt);
  திரும்பு உண்மை;
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

நிலையான தருக்க
c_parser_omp_target (c_parser *parser, எண்ணிக்கை pragma_context context, தருக்க *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  மரம் *pc = வெற்று, stmt, block, body, clauses;

  எனில் (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser);
      திரும்பு பொய்;
    }

  எனில் (flag_openmp)
    omp_requires_mask
      = (எண்ணிக்கை omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எண்ணிக்கை மரம்_code ccode = ERROR_MARK;

      எனில் (strcmp (p, "teams") == 0)
	ccode = OMP_TEAMS;
      இல்லையெனில் எனில் (strcmp (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      இல்லையெனில் எனில் (strcmp (p, "simd") == 0)
	ccode = OMP_SIMD;
      எனில் (ccode != ERROR_MARK)
	{
	  மரம் cclauses[C_OMP_CLAUSE_SPLIT_மொத்தம்];
	  எழுத்து p_name[அளவு ("#pragma omp target teams distribute "
			      "parallel for simd")];

	  c_parser_consume_token (parser);
	  strcpy (p_name, "#pragma omp target");
	  எனில் (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      மரம் stmt;
	      தேர்வு (ccode)
		{
		நிலை OMP_TEAMS:
		  stmt = c_parser_omp_teams (loc, parser, p_name,
					     OMP_TARGET_CLAUSE_MASK,
					     cclauses, if_p);
		  நிறுத்து;
		நிலை OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_TARGET_CLAUSE_MASK,
						cclauses, if_p);
		  நிறுத்து;
		நிலை OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_TARGET_CLAUSE_MASK,
					    cclauses, if_p);
		  நிறுத்து;
		இயல்பு:
		  gcc_unreachable ();
		}
	      திரும்பு stmt != NULL_மரம்;
	    }
	  keep_next_level ();
	  மரம் block = c_begin_compound_stmt (உண்மை), ret;
	  தேர்வு (ccode)
	    {
	    நிலை OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_TARGET_CLAUSE_MASK, cclauses,
					if_p);
	      நிறுத்து;
	    நிலை OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_TARGET_CLAUSE_MASK, cclauses,
					   if_p);
	      நிறுத்து;
	    நிலை OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_TARGET_CLAUSE_MASK, cclauses,
				       if_p);
	      நிறுத்து;
	    இயல்பு:
	      gcc_unreachable ();
	    }
	  block = c_end_compound_stmt (loc, block, உண்மை);
	  எனில் (ret == NULL_மரம்)
	    திரும்பு பொய்;
	  எனில் (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    க்கு (மரம் c = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_இலக்கம்_TEAMS
		  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_THREAD_LIMIT)
		க்கு (முழு i = 0;
		     i <= (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_இலக்கம்_TEAMS); ++i)
		  எனில் (OMP_CLAUSE_OPERAND (c, i)
		      && மரம்_CODE (OMP_CLAUSE_OPERAND (c, i)) != INTEGER_CST)
		    {
		      மரம் கோவை = OMP_CLAUSE_OPERAND (c, i);
		      மரம் tmp = create_tmp_var_raw (மரம்_TYPE (கோவை));
		      கோவை = build4 (TARGET_கோவை, மரம்_TYPE (கோவை), tmp,
				     கோவை, NULL_மரம், NULL_மரம்);
		      add_stmt (கோவை);
		      OMP_CLAUSE_OPERAND (c, i) = கோவை;
		      மரம் tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
		      cclauses[C_OMP_CLAUSE_SPLIT_TARGET] = tc;
		    }
	  மரம் stmt = make_முனை (OMP_TARGET);
	  மரம்_TYPE (stmt) = void_type_முனை;
	  OMP_TARGET_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
	  c_omp_adjust_map_clauses (OMP_TARGET_CLAUSES (stmt), உண்மை);
	  OMP_TARGET_BODY (stmt) = block;
	  OMP_TARGET_COMBINED (stmt) = 1;
	  SET_கோவை_LOCATION (stmt, loc);
	  add_stmt (stmt);
	  pc = &OMP_TARGET_CLAUSES (stmt);
	  செல் check_clauses;
	}
      இல்லையெனில் எனில் (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, பொய்);
	  திரும்பு பொய்;
	}
      இல்லையெனில் எனில் (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_target_data (loc, parser, if_p);
	  திரும்பு உண்மை;
	}
      இல்லையெனில் எனில் (strcmp (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  திரும்பு c_parser_omp_target_enter_data (loc, parser, context);
	}
      இல்லையெனில் எனில் (strcmp (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  திரும்பு c_parser_omp_target_exit_data (loc, parser, context);
	}
      இல்லையெனில் எனில் (strcmp (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  திரும்பு c_parser_omp_target_update (loc, parser, context);
	}
    }
  எனில் (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, பொய்);
      திரும்பு பொய்;
    }

  stmt = make_முனை (OMP_TARGET);
  மரம்_TYPE (stmt) = void_type_முனை;

  clauses = c_parser_omp_all_clauses (parser, OMP_TARGET_CLAUSE_MASK,
				      "#pragma omp target", பொய்);
  க்கு (மரம் c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
      {
	மரம் nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_SET_MAP_KIND (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_TARGET);
  clauses  = c_finish_omp_clauses (clauses, C_ORT_OMP_TARGET);
  c_omp_adjust_map_clauses (clauses, உண்மை);

  keep_next_level ();
  block = c_begin_compound_stmt (உண்மை);
  body = c_parser_omp_structured_block (parser, if_p);

  c_omp_scan_mapper_bindings (loc, &clauses, body);

  add_stmt (body);
  OMP_TARGET_CLAUSES (stmt) = clauses;
  pc = &OMP_TARGET_CLAUSES (stmt);
  OMP_TARGET_BODY (stmt) = c_end_compound_stmt (loc, block, உண்மை);

  SET_கோவை_LOCATION (stmt, loc);
  add_stmt (stmt);

check_clauses:
  போது (*pc)
    {
      எனில் (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	தேர்வு (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  நிலை GOMP_MAP_TO:
	  நிலை GOMP_MAP_ALWAYS_TO:
	  நிலை GOMP_MAP_PRESENT_TO:
	  நிலை GOMP_MAP_ALWAYS_PRESENT_TO:
	  நிலை GOMP_MAP_FROM:
	  நிலை GOMP_MAP_ALWAYS_FROM:
	  நிலை GOMP_MAP_PRESENT_FROM:
	  நிலை GOMP_MAP_ALWAYS_PRESENT_FROM:
	  நிலை GOMP_MAP_TOFROM:
	  நிலை GOMP_MAP_ALWAYS_TOFROM:
	  நிலை GOMP_MAP_PRESENT_TOFROM:
	  நிலை GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  நிலை GOMP_MAP_ALLOC:
	  நிலை GOMP_MAP_PRESENT_ALLOC:
	  நிலை GOMP_MAP_FIRSTPRIVATE_POINTER:
	  நிலை GOMP_MAP_ALWAYS_POINTER:
	  நிலை GOMP_MAP_POINTER:
	  நிலை GOMP_MAP_ATTACH_DETACH:
	  நிலை GOMP_MAP_ATTACH:
	    நிறுத்து;
	  இயல்பு:
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    தொடர்;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }
  cfun->has_omp_target = உண்மை;
  திரும்பு உண்மை;
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

நிலையான வெறுமை
c_parser_omp_declare_simd (c_parser *parser, எண்ணிக்கை pragma_context context)
{
  c_token *token = c_parser_peek_token (parser);
  gcc_assert (token->type == CPP_NAME);
  மரம் kind = token->மதிப்பு;
  gcc_assert (strcmp (IDENTIFIER_POINTER (kind), "simd") == 0
	      || strcmp (IDENTIFIER_POINTER (kind), "variant") == 0);

  auto_vec<c_token> clauses;
  போது (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      எனில் (token->type == CPP_EOF)
	{
	  c_parser_skip_to_pragma_eol (parser);
	  திரும்பு;
	}
      clauses.safe_தள்ளு (*token);
      c_parser_consume_token (parser);
    }
  clauses.safe_தள்ளு (*c_parser_peek_token (parser));
  c_parser_skip_to_pragma_eol (parser);

  போது (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      எனில் (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->மதிப்பு != kind)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_POINTER (kind), IDENTIFIER_POINTER (kind));
	  திரும்பு;
	}
      c_parser_consume_pragma (parser);
      போது (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  எனில் (token->type == CPP_EOF)
	    {
	      c_parser_skip_to_pragma_eol (parser);
	      திரும்பு;
	    }
	  clauses.safe_தள்ளு (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_தள்ளு (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  memset (&eof_token, 0, அளவு (eof_token));
  eof_token.type = CPP_EOF;
  clauses.safe_தள்ளு (eof_token);
  clauses.safe_தள்ளு (eof_token);

  தேர்வு (context)
    {
    நிலை pragma_external:
      எனில் (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  முழு ext = disable_extension_diagnostics ();
	  செய்
	    c_parser_consume_token (parser);
	  போது (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, உண்மை, உண்மை, உண்மை, பொய், உண்மை,
					 பொய், வெற்று, &clauses);
	  restore_extension_diagnostics (ext);
	}
      இல்லையெனில்
	c_parser_declaration_or_fndef (parser, உண்மை, உண்மை, உண்மை, பொய், உண்மை,
				       பொய், வெற்று, &clauses);
      நிறுத்து;
    நிலை pragma_struct:
    நிலை pragma_param:
    நிலை pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      நிறுத்து;
    நிலை pragma_compound:
      தருக்க have_std_attrs;
      மரம் std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
      எனில் (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      இல்லையெனில்
	std_attrs = NULL_மரம்;
      எனில் (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  முழு ext = disable_extension_diagnostics ();
	  செய்
	    c_parser_consume_token (parser);
	  போது (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  எனில் (c_parser_next_tokens_start_declaration (parser)
	      || c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, உண்மை, உண்மை, உண்மை, உண்மை,
					     உண்மை, பொய், வெற்று, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      நிறுத்து;
	    }
	  restore_extension_diagnostics (ext);
	}
      இல்லையெனில் எனில் (c_parser_next_tokens_start_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, உண்மை, உண்மை, உண்மை, உண்மை, உண்மை,
					 பொய், வெற்று, &clauses, have_std_attrs,
					 std_attrs);
	  நிறுத்து;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      நிறுத்து;
    இயல்பு:
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

நிலையான மரம்
c_parser_omp_context_selector (c_parser *parser, எண்ணிக்கை omp_tss_code set,
			       மரம் parms)
{
  மரம் ret = NULL_மரம்;
  செய்
    {
      மரம் selector;
      எனில் (c_parser_next_token_is (parser, CPP_KEYWORD)
	  || c_parser_next_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->மதிப்பு;
      இல்லையெனில்
	{
	  c_parser_error (parser, "expected trait selector name");
	  திரும்பு error_mark_முனை;
	}
      எண்ணிக்கை omp_ts_code sel
	= omp_lookup_ts_code (set, IDENTIFIER_POINTER (selector));

      எனில் (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_POINTER (selector),  omp_tss_map[set]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_மரம், NULL_மரம், ret);
	  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_balanced_token_sequence (parser);
	  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      தொடர்;
	    }
	  இல்லையெனில்
	    நிறுத்து;
	}

      c_parser_consume_token (parser);

      மரம் properties = NULL_மரம்;
      மரம் scoreval = NULL_மரம்;
      எண்ணிக்கை omp_tp_type property_kind = omp_ts_map[sel].tp_type;
      தருக்க allow_score = omp_ts_map[sel].allow_score;
      மரம் t;

      எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  எனில் (property_kind == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_POINTER (selector));
	      திரும்பு error_mark_முனை;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  எனில் (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER (token->மதிப்பு), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      மரம் score = c_parser_கோவை_no_commas (parser, வெற்று).மதிப்பு;
	      parens2.skip_until_found_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      எனில் (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[set]);
	      இல்லையெனில் எனில் (score != error_mark_முனை)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, பொய், வெற்று);
		  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (score))
		      || மரம்_CODE (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  இல்லையெனில் எனில் (மரம்_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  இல்லையெனில்
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  தேர்வு (property_kind)
	    {
	    நிலை OMP_TRAIT_PROPERTY_ID:
	      எனில் (c_parser_next_token_is (parser, CPP_KEYWORD)
		  || c_parser_next_token_is (parser, CPP_NAME))
		{
		  மரம் prop = c_parser_peek_token (parser)->மதிப்பு;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_மரம்,
						    properties);
		}
	      இல்லையெனில்
		{
		  c_parser_error (parser, "expected identifier");
		  திரும்பு error_mark_முனை;
		}
	      நிறுத்து;
	    நிலை OMP_TRAIT_PROPERTY_NAME_LIST:
	      செய்
		{
		  மரம் prop = OMP_TP_NAMELIST_முனை;
		  மரம் மதிப்பு = NULL_மரம்;
		  எனில் (c_parser_next_token_is (parser, CPP_KEYWORD)
		      || c_parser_next_token_is (parser, CPP_NAME))
		    {
		      மதிப்பு = c_parser_peek_token (parser)->மதிப்பு;
		      c_parser_consume_token (parser);
		    }
		  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_STRING))
		    மதிப்பு = c_parser_string_literal (parser, பொய்,
						     பொய்).மதிப்பு;
		  இல்லையெனில்
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      திரும்பு error_mark_முனை;
		    }

		  properties = make_trait_property (prop, மதிப்பு, properties);

		  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  இல்லையெனில்
		    நிறுத்து;
		}
	      போது (1);
	      நிறுத்து;
	    நிலை OMP_TRAIT_PROPERTY_DEV_இலக்கம்_கோவை:
	    நிலை OMP_TRAIT_PROPERTY_BOOL_கோவை:
	      {
		c_கோவை texpr = c_parser_கோவை_no_commas (parser, வெற்று);
		texpr = convert_lvalue_to_rvalue (token->location, texpr,
						  உண்மை, உண்மை);
		t = texpr.மதிப்பு;
	      }
	      எனில் (t == error_mark_முனை)
		திரும்பு error_mark_முனை;
	      mark_exp_read (t);
	      எனில் (property_kind == OMP_TRAIT_PROPERTY_BOOL_கோவை)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_முனை);
		  எனில் (t == error_mark_முனை)
		    திரும்பு error_mark_முனை;
		}
	      இல்லையெனில் எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  திரும்பு error_mark_முனை;
		}
	      t = c_fully_fold (t, பொய், வெற்று);
	      properties = make_trait_property (NULL_மரம், t, properties);
	      நிறுத்து;
	    நிலை OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      எனில் (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  எனில் (parms == NULL_மரம்)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      திரும்பு error_mark_முனை;
		    }
		  மரம் c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_MASK,
						"simd", உண்மை, 2);
		  c = c_omp_declare_simd_clauses_to_numbers (parms
							     == error_mark_முனை
							     ? NULL_மரம் : parms,
							     c);
		  properties = c;
		}
	      இல்லையெனில் எனில் (sel == OMP_TRAIT_IMPLEMENTATION_REQUIRES)
		{
		  /* FIXME: The "requires" selector was added in OpenMP 5.1.
		     Currently only the now-deprecated syntax
		     from OpenMP 5.0 is supported.  */
		  sorry_at (token->location,
			    "%<requires%> selector is not supported yet");
		  திரும்பு error_mark_முனை;
		}
	      இல்லையெனில்
		gcc_unreachable ();
	      நிறுத்து;
	    இயல்பு:
	      gcc_unreachable ();
	    }

	  parens.skip_until_found_close (parser);
	  properties = nreverse (properties);
	}
      இல்லையெனில் எனில் (property_kind != OMP_TRAIT_PROPERTY_NONE
	       && property_kind != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_kind != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  திரும்பு error_mark_முனை;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      இல்லையெனில்
	நிறுத்து;
    }
  போது (1);

  திரும்பு nreverse (ret);
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

நிலையான மரம்
c_parser_omp_context_selector_specification (c_parser *parser, மரம் parms)
{
  மரம் ret = NULL_மரம்;
  செய்
    {
      மாறிலி எழுத்து *setp = "";
      எனில் (c_parser_next_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எண்ணிக்கை omp_tss_code set = omp_lookup_tss_code (setp);

      எனில் (set == OMP_TRAIT_SET_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  திரும்பு error_mark_முனை;
	}

      c_parser_consume_token (parser);

      எனில் (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	திரும்பு error_mark_முனை;

      matching_braces braces;
      எனில் (!braces.require_open (parser))
	திரும்பு error_mark_முனை;

      மரம் selectors = c_parser_omp_context_selector (parser, set, parms);
      எனில் (selectors == error_mark_முனை)
	{
	  c_parser_skip_to_closing_brace (parser);
	  ret = error_mark_முனை;
	}
      இல்லையெனில் எனில் (ret != error_mark_முனை)
	ret = make_trait_set_selector (set, selectors, ret);

      braces.require_close (parser);

      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      இல்லையெனில்
	நிறுத்து;
    }
  போது (1);

  எனில் (ret == error_mark_முனை)
    திரும்பு ret;
  திரும்பு nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

நிலையான வெறுமை
c_finish_omp_declare_variant (c_parser *parser, மரம் fndecl, மரம் parms)
{
  matching_parens parens;
  எனில் (!parens.require_open (parser))
    {
     fail:
      c_parser_skip_to_pragma_eol (parser, பொய்);
      திரும்பு;
    }

  எனில் (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      செல் fail;
    }

  c_token *token = c_parser_peek_token (parser);
  மரம் variant = lookup_name (token->மதிப்பு);

  எனில் (variant == NULL_மரம்)
    {
      undeclared_variable (token->location, token->மதிப்பு);
      variant = error_mark_முனை;
    }
  இல்லையெனில் எனில் (மரம்_CODE (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_முனை;
    }
  இல்லையெனில் எனில் (fndecl_built_in_p (variant)
	   && (strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			"__builtin_", strlen ("__builtin_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__sync_", strlen ("__sync_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__atomic_", strlen ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_முனை;
    }
  இல்லையெனில் எனில் (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_முனை;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  மரம் append_args_மரம் = NULL_மரம்;
  மரம் append_args_last;
  vec<மரம்> adjust_args_list = vNULL;
  தருக்க has_match = பொய், has_adjust_args = பொய்;
  location_t adjust_args_loc = UNKNOWN_LOCATION;
  location_t append_args_loc = UNKNOWN_LOCATION;
  location_t match_loc = UNKNOWN_LOCATION;
  மரம் need_device_ptr_list = NULL_மரம்;
  மரம் ctx = error_mark_முனை;

  செய்
    {
      எனில் (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      மாறிலி எழுத்து *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      எனில் (c_parser_next_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);

      எண்ணிக்கை clause
      {
	match,
	adjust_args,
	append_args
      } ccode;

      எனில் (strcmp (clause, "match") == 0)
	{
	  ccode = match;
	  match_loc = loc;
	}
      இல்லையெனில் எனில் (strcmp (clause, "adjust_args") == 0)
	{
	  ccode = adjust_args;
	  adjust_args_loc = loc;
	}
      இல்லையெனில் எனில் (strcmp (clause, "append_args") == 0)
	{
	  ccode = append_args;
	  append_args_loc = loc;
	}
      இல்லையெனில்
	{
	  c_parser_error (parser, "expected %<match%>, %<adjust_args%> or "
				  "%<append_args%> clause");
	  செல் fail;
	}

      c_parser_consume_token (parser);

      எனில் (!parens.require_open (parser))
	செல் fail;

      எனில் (parms == NULL_மரம்)
	parms = error_mark_முனை;

      எனில் (ccode == match)
	{
	  எனில் (has_match)
	    error_at (match_loc, "too many %<match%> clauses");
	  has_match = உண்மை;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  எனில் (ctx == error_mark_முனை)
	    செல் fail;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  எனில் (ctx != error_mark_முனை
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      மரம் outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      இல்லையெனில் எனில் (ccode == adjust_args)
	{
	  has_adjust_args = உண்மை;
	  எனில் (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      மாறிலி எழுத்து *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
	      எனில் (strcmp (p, "need_device_ptr") == 0
		  || strcmp (p, "nothing") == 0)
		{
		  c_parser_consume_token (parser); // need_device_ptr
		  c_parser_consume_token (parser); // :

		  loc = c_parser_peek_token (parser)->location;
		  மரம் list
		    = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ERROR,
						  NULL_மரம்);

		  மரம் arg;
		  எனில் (variant != error_mark_முனை)
		    க்கு (மரம் c = list; c != NULL_மரம்; c = மரம்_CHAIN (c))
		      {
			மரம் decl = மரம்_PURPOSE (c);
			location_t arg_loc = கோவை_LOCATION (மரம்_மதிப்பு (c));
			முழு idx;
			க்கு (arg = parms, idx = 0; arg != வெற்று;
			     arg = மரம்_CHAIN (arg), idx++)
			  எனில் (arg == decl)
			    நிறுத்து;
			எனில் (arg == NULL_மரம்)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    செல் fail;
			  }
			எனில் (adjust_args_list.contains (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    செல் fail;
			  }
			எனில் (strcmp (p, "need_device_ptr") == 0
			    && மரம்_CODE (மரம்_TYPE (arg)) != POINTER_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    செல் fail;
			  }
			adjust_args_list.safe_தள்ளு (arg);
			எனில் (strcmp (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_மரம்_list (
				NULL_மரம்,
				build_int_cst (
				  integer_type_முனை,
				  idx))); // Store 0-based argument index,
					  // as in gimplify_call_expr
			  }
		      }
		}
	      இல்லையெனில்
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %<nothing%> or %<need_device_ptr%>");
		  எனில் (strcmp (p, "need_device_addr") == 0)
		    inform (c_parser_peek_token (parser)->location,
			    "%<need_device_addr%> is not valid for C");
		  செல் fail;
		}
	    }
	  இல்லையெனில்
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected %<nothing%> or %<need_device_ptr%> "
			"followed by %<:%>");
	      செல் fail;
	    }
	}
      இல்லையெனில் எனில் (ccode == append_args)
	{
	  எனில் (append_args_மரம்)
	    {
	      error_at (append_args_loc, "too many %qs clauses", "append_args");
	      append_args_மரம் = NULL_மரம்;
	    }
	  செய்
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      எனில் (!c_parser_next_token_is (parser, CPP_NAME)
		  || strcmp ("interop",
			     IDENTIFIER_POINTER (
			       c_parser_peek_token (parser)->மதிப்பு)))
		{
		  error_at (loc, "expected %<interop%>");
		  செல் fail;
		}
	      c_parser_consume_token (parser);

	      எனில் (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		செல் fail;
	      தருக்க target = பொய்;
	      தருக்க targetsync = பொய்;
	      மரம் prefer_type_மரம் = NULL_மரம்;
	      எனில் (!c_parser_omp_clause_init_modifiers (parser, &target,
						       &targetsync,
						       &prefer_type_மரம்)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		செல் fail;
	      எனில் (!target && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      மரம் t = build_மரம்_list (target ? boolean_true_முனை
					       : boolean_false_முனை,
					targetsync ? boolean_true_முனை
						   : boolean_false_முனை);
	      t = build1_loc (loc, NOP_கோவை, void_type_முனை, t);
	      t = build_மரம்_list (t, prefer_type_மரம்);
	      எனில் (append_args_மரம்)
		{
		  மரம்_CHAIN (append_args_last) = t;
		  append_args_last = t;
		}
	      இல்லையெனில்
		append_args_மரம் = append_args_last = t;
	      எனில் (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		நிறுத்து;
	      எனில் (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		செல் fail;
	    }
	  போது (உண்மை);
	}

      parens.require_close (parser);
  } போது (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL));
  எனில் (variant != error_mark_முனை && !has_match)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_முனை;
    }
  c_parser_skip_to_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  எனில் (variant == error_mark_முனை || ctx == error_mark_முனை)
    /* Previously diagnosed error.  */
    திரும்பு;

  எனில் ((has_adjust_args || append_args_மரம்)
      && !omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_args ? adjust_args_loc : append_args_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_args ? "adjust_args" : "append_args");
      திரும்பு;
    }

  எனில் (!omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      மரம் base_type = மரம்_TYPE (fndecl);
      மரம் variant_type = மரம்_TYPE (variant);
      தருக்க unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_மரம்
	   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type));

      எனில் (append_args_மரம்
	  && TYPE_ARG_TYPES (base_type) == NULL_மரம்
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
	  திரும்பு;
	}
      இல்லையெனில் எனில் (append_args_மரம்)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  முழு nappend_args = 0;
	  முழு nbase_args = 0;
	  க்கு (மரம் t = TYPE_ARG_TYPES (base_type);
	       t && மரம்_மதிப்பு (t) != void_type_முனை; t = மரம்_CHAIN (t))
	    nbase_args++;
	  க்கு (மரம் t = append_args_மரம்; t; t = மரம்_CHAIN (t))
	    nappend_args++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_args_மரம் = build_மரம்_list (build_int_cst (integer_type_முனை,
							     nbase_args),
					      append_args_மரம்);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  எனில் (!unprototyped_variant)
	    {
	      மரம் args = TYPE_ARG_TYPES (variant_type);
	      க்கு (முழு i = 0; args && i < nbase_args;
		   i++, args = மரம்_CHAIN (args))
		;
	      க்கு (முழு i = 0; i < nappend_args; i++, args = மரம்_CHAIN (args))
		எனில் (!args || !c_omp_interop_t_p (மரம்_மதிப்பு (args)))
		  {
		    error_at (DECL_SOURCE_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_args + i + 1, variant);
		    inform (append_args_loc,
			    "%<append_args%> specified here");
		    திரும்பு;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  மரம் args = TYPE_ARG_TYPES (base_type);
	  மரம் newargs = NULL_மரம்;
	  மரம் lastarg = NULL_மரம்;
	  க்கு (முழு j = 0; j < nbase_args; j++, args = மரம்_CHAIN (args))
	    {
	      மரம் t = மரம்_cons (மரம்_PURPOSE (args),
				  மரம்_மதிப்பு (args), NULL_மரம்);
	      எனில் (lastarg)
		மரம்_CHAIN (lastarg) = t;
	      இல்லையெனில்
		newargs = t;
	      lastarg = t;
	    }
	  மரம் type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? மரம்_TYPE (type) : pointer_sized_int_முனை;
	  க்கு (முழு j = 0; j < nappend_args; j++)
	    {
	      மரம் t = மரம்_cons (NULL_மரம், type, NULL_மரம்);
	      எனில் (lastarg)
		மரம்_CHAIN (lastarg) = t;
	      இல்லையெனில்
		newargs = t;
	      lastarg = t;
	    }
	  மரம்_CHAIN (lastarg) = args;

	  /* Temporarily stuff newargs into the original base_type.  */
	  மரம் saveargs = TYPE_ARG_TYPES (base_type);
	  TYPE_ARG_TYPES (base_type) = newargs;
	  தருக்க fail = !comptypes (base_type, variant_type);
	  TYPE_ARG_TYPES (base_type) = saveargs;

	  எனில் (fail)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      திரும்பு;
	    }
	  இல்லையெனில் எனில் (unprototyped_variant)
	    /* If we've got an unprototyped variant, copy the transformed
	       base arg types to the variant.  This is needed later by
	       modify_call_for_omp_dispatch.  */
	    TYPE_ARG_TYPES (variant_type) = newargs;
	}
      இல்லையெனில்  /* No append_args present.  */
	{
	  எனில் (!comptypes (base_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      திரும்பு;
	    }
	  இல்லையெனில் எனில் (TYPE_ARG_TYPES (variant_type) == NULL_மரம்
		   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (base_type) != NULL_மரம்)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (base_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_USED (variant) = 1;
  மரம் construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (match_loc, variant, construct);
  எனில் (omp_context_selector_matches (ctx, NULL_மரம், பொய்))
    {
      மரம் attr = மரம்_cons (get_identifier ("omp declare variant base"),
			     build_மரம்_list (variant, ctx),
			     DECL_ATTRIBUTES (fndecl));
      DECL_ATTRIBUTES (fndecl) = attr;
    }

  எனில் (need_device_ptr_list || append_args_மரம்)
    {
      மரம் variant_decl = மரம்_strip_nop_conversions (variant);
      மரம் t = build_மரம்_list (need_device_ptr_list,
				NULL_மரம் /* need_device_addr */);
      மரம்_CHAIN (t) = append_args_மரம்;
      DECL_ATTRIBUTES (variant_decl)
	= மரம்_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_ATTRIBUTES (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

நிலையான வெறுமை
c_finish_omp_declare_simd (c_parser *parser, மரம் fndecl, மரம் parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  எனில் (clauses.exists () && clauses[0].type == CPP_EOF)
    திரும்பு;
  மாறிலி எழுத்து *kind = "simd";
  எனில் (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    kind = IDENTIFIER_POINTER (clauses[0].மதிப்பு);
  gcc_assert (strcmp (kind, "simd") == 0 || strcmp (kind, "variant") == 0);
  எனில் (fndecl == NULL_மரம் || மரம்_CODE (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      திரும்பு;
    }
  எனில் (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      திரும்பு;
    }
  எனில் (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", kind);
      திரும்பு;
    }

  எனில் (parms == NULL_மரம்)
    parms = DECL_ARGUMENTS (fndecl);

  unsigned முழு tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);

  parser->tokens = clauses.address ();
  parser->tokens_avail = clauses.length ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  போது (parser->tokens_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      kind = IDENTIFIER_POINTER (token->மதிப்பு);
      c_parser_consume_token (parser);
      parser->in_pragma = உண்மை;

      எனில் (strcmp (kind, "simd") == 0)
	{
	  மரம் c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_MASK,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_to_numbers (parms, c);
	  எனில் (c != NULL_மரம்)
	    c = மரம்_cons (NULL_மரம், c, NULL_மரம்);
	  c = build_மரம்_list (get_identifier ("omp declare simd"), c);
	  மரம்_CHAIN (c) = DECL_ATTRIBUTES (fndecl);
	  DECL_ATTRIBUTES (fndecl) = c;
	}
      இல்லையெனில்
	{
	  gcc_assert (strcmp (kind, "variant") == 0);
	  c_finish_omp_declare_variant (parser, fndecl, parms);
	}
    }

  parser->tokens = &parser->tokens_buf[0];
  parser->tokens_avail = tokens_avail;
  எனில் (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#எனில் !defined (NO_DOT_IN_LABEL)
#define JOIN_STR "."
#அல்லதெனில் !defined (NO_DOLLAR_IN_LABEL)
#define JOIN_STR "$"
#இல்லையெனில்
#define JOIN_STR "_"
#endif

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
நிலையான மரம்
omp_start_variant_function (c_declarator *declarator, மரம் ctx)
{
  c_declarator *id = declarator;
  போது (id->kind != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  மரம் name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  திரும்பு name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
நிலையான வெறுமை
omp_finish_variant_function (மரம் decl, மரம் base_name, மரம் ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  மரம் base_decl = lookup_name (base_name);
  எனில் (base_decl == error_mark_முனை)
    base_decl = NULL_மரம்;
  எனில் (!base_decl)
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_POINTER (base_name));
      திரும்பு;
    }

  எனில் (!comptypes (மரம்_TYPE (decl), மரம்_TYPE (base_decl)))
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", base_decl);
      inform (DECL_SOURCE_LOCATION (base_decl),
	      "%qE declared here", base_decl);
      திரும்பு;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_SOURCE_LOCATION (decl),
				   base_decl, ctx);
  மரம் construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (DECL_SOURCE_LOCATION (decl), decl, construct);
  மரம் attrs = DECL_ATTRIBUTES (base_decl);
  மரம் match_loc_முனை
    = maybe_wrap_with_location (integer_zero_முனை,
				DECL_SOURCE_LOCATION (base_decl));
  மரம் loc_முனை = மரம்_cons (match_loc_முனை, integer_zero_முனை,
			     build_மரம்_list (match_loc_முனை,
					      integer_zero_முனை));
  attrs = மரம்_cons (get_identifier ("omp declare variant base"),
		     மரம்_cons (decl, ctx, loc_முனை), attrs);
  DECL_ATTRIBUTES (base_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  மரம்_PUBLIC (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

தருக்க
c_maybe_parse_omp_decl (மரம் decl, மரம் d)
{
  gcc_assert (மரம்_CODE (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
  c_token *first = toks->address ();
  c_token *last = first + toks->length ();
  மாறிலி எழுத்து *directive[3] = {};
  க்கு (முழு j = 0; j < 3; j++)
    {
      மரம் id = NULL_மரம்;
      எனில் (first + j == last)
	நிறுத்து;
      எனில் (first[j].type == CPP_NAME)
	id = first[j].மதிப்பு;
      இல்லையெனில் எனில் (first[j].type == CPP_KEYWORD)
	id = ridpointers[(முழு) first[j].keyword];
      இல்லையெனில்
	நிறுத்து;
      directive[j] = IDENTIFIER_POINTER (id);
    }
  மாறிலி c_omp_directive *dir = வெற்று;
  எனில் (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  எனில் (dir == வெற்று)
    {
      error_at (first->location,
		"unknown OpenMP directive name in "
		"%qs attribute argument", "omp::decl");
      திரும்பு பொய்;
    }
  எனில் (dir->id != PRAGMA_OMP_THREADPRIVATE
      && dir->id != PRAGMA_OMP_GROUPPRIVATE
      && dir->id != PRAGMA_OMP_ALLOCATE
      && (dir->id != PRAGMA_OMP_DECLARE
	  || strcmp (directive[1], "target") != 0))
    திரும்பு பொய்;

  எனில் (!flag_openmp && !dir->simd)
    திரும்பு உண்மை;

  c_parser *parser = the_parser;
  unsigned முழு tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);
  toks = வெற்று;
  vec_safe_reserve (toks, last - first + 2, உண்மை);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_kind = pragma_kind (dir->id);
  tok.location = first->location;
  toks->quick_தள்ளு (tok);
  போது (++first < last)
    toks->quick_தள்ளு (*first);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_தள்ளு (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_தள்ளு (tok);
  parser->in_omp_decl_attribute = decl;
  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = toks->length ();
  c_parser_pragma (parser, pragma_external, வெற்று, NULL_மரம்);
  parser->in_omp_decl_attribute = NULL_மரம்;
  திரும்பு உண்மை;
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

நிலையான வெறுமை
c_parser_omp_declare_target (c_parser *parser)
{
  மரம் clauses = NULL_மரம்;
  முழு device_type = 0;
  தருக்க indirect = பொய்;
  தருக்க only_device_type_or_indirect = உண்மை;
  எனில் (flag_openmp)
    omp_requires_mask
      = (எண்ணிக்கை omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);
  எனில் (c_parser_next_token_is (parser, CPP_NAME)
      || (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp declare target");
  இல்லையெனில் எனில் (parser->in_omp_decl_attribute
	   || c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      clauses = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					      clauses);
      clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
      c_parser_skip_to_pragma_eol (parser);
    }
  இல்லையெனில்
    {
      warning_at (c_parser_peek_token (parser)->location,
		  OPT_Wdeprecated_openmp,
		  "use of %<omp declare target%> as a synonym for "
		  "%<omp begin declare target%> has been deprecated since "
		  "OpenMP 5.2");
      தருக்க attr_syntax = parser->in_omp_attribute_pragma != வெற்று;
      c_parser_skip_to_pragma_eol (parser);
      c_omp_declare_target_attr attr = { attr_syntax, -1, 0 };
      vec_safe_தள்ளு (current_omp_declare_target_attribute, attr);
      திரும்பு;
    }
  க்கு (மரம் c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_கோவை (c));
    }
  க்கு (மரம் c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	தொடர்;
      மரம் t = OMP_CLAUSE_DECL (c), id;
      மரம் at1 = lookup_attribute ("omp declare target", DECL_ATTRIBUTES (t));
      மரம் at2 = lookup_attribute ("omp declare target link",
				   DECL_ATTRIBUTES (t));
      only_device_type_or_indirect = பொய்;
      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::swap (at1, at2);
	}
      இல்லையெனில்
	id = get_identifier ("omp declare target");
      எனில் (at2)
	{
	  எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	  இல்லையெனில் எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL
		   || மதிப்பு_member (get_identifier ("local"), மரம்_மதிப்பு (at2)))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<local%> clauses", t);
	  இல்லையெனில்
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<to%> or %<enter%> clauses", t);
	  தொடர்;
	}
      எனில் (!at1)
	{
	  DECL_ATTRIBUTES (t) = மரம்_cons (id, NULL_மரம், DECL_ATTRIBUTES (t));
	  எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    மரம்_மதிப்பு (DECL_ATTRIBUTES (t))
	      = மரம்_cons (NULL_மரம், get_identifier ("local"),
			   மரம்_மதிப்பு (DECL_ATTRIBUTES (t)));

	  எனில் (மரம்_CODE (t) != FUNCTION_DECL && !is_global_var (t))
	    தொடர்;

	  symtab_முனை *முனை = symtab_முனை::get (t);
	  எனில் (முனை != வெற்று)
	    {
	      முனை->offloadable = 1;
	      எனில் (ENABLE_OFFLOADING)
		{
		  g->have_offload = உண்மை;
		  எனில் (is_a <varpool_முனை *> (முனை)
		      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_LOCAL)
		    vec_safe_தள்ளு (offload_vars, t);
		}
	    }
	}
      இல்லையெனில்
	{
	  தருக்க saw_local = மதிப்பு_member (get_identifier ("local"),
					 மரம்_மதிப்பு (at1));
	  எனில் (saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	      தொடர்;
	    }
	  இல்லையெனில் எனில் (!saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      தொடர்;
	    }
	}
      எனில் (மரம்_CODE (t) != FUNCTION_DECL)
	தொடர்;
      எனில் ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  மரம் at3 = lookup_attribute ("omp declare target host",
				       DECL_ATTRIBUTES (t));
	  எனில் (at3 == NULL_மரம்)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_ATTRIBUTES (t)
		= மரம்_cons (id, NULL_மரம், DECL_ATTRIBUTES (t));
	    }
	}
      எனில் ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  மரம் at3 = lookup_attribute ("omp declare target nohost",
				       DECL_ATTRIBUTES (t));
	  எனில் (at3 == NULL_மரம்)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_ATTRIBUTES (t)
		= மரம்_cons (id, NULL_மரம், DECL_ATTRIBUTES (t));
	    }
	}
      எனில் (indirect)
	{
	  மரம் at4 = lookup_attribute ("omp declare target indirect",
				       DECL_ATTRIBUTES (t));
	  எனில் (at4 == NULL_மரம்)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_ATTRIBUTES (t)
		= மரம்_cons (id, NULL_மரம், DECL_ATTRIBUTES (t));
	    }
	}
    }
  எனில் ((device_type || indirect) && only_device_type_or_indirect)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  எனில் (indirect && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
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

நிலையான வெறுமை
c_parser_omp_begin (c_parser *parser)
{
  மாறிலி எழுத்து *p = "";
  c_parser_consume_pragma (parser);
  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
  எனில் (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      எனில் (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  தருக்க attr_syntax = parser->in_omp_attribute_pragma != வெற்று;
	  மரம் clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp begin declare target");
	  முழு device_type = 0;
	  முழு indirect = 0;
	  க்கு (மரம் c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
	      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
		indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_கோவை (c));
	    }
	  c_omp_declare_target_attr attr = { attr_syntax, device_type,
					     indirect };
	  vec_safe_தள்ளு (current_omp_declare_target_attribute, attr);
	}
      இல்லையெனில் எனில் (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  மாறிலி எழுத்து *clause = "";
	  matching_parens parens;
	  location_t match_loc = c_parser_peek_token (parser)->location;
	  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  எனில் (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      மரம் id = c_parser_peek_token (parser)->மதிப்பு;
	      clause = IDENTIFIER_POINTER (id);
	    }
	  எனில் (strcmp (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_to_pragma_eol (parser);
	      திரும்பு;
	    }

	  c_parser_consume_token (parser);

	  எனில் (!parens.require_open (parser))
	    {
	      c_parser_skip_to_pragma_eol (parser, பொய்);
	      திரும்பு;
	    }

	  மரம் ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_மரம்);
	  எனில் (ctx != error_mark_முனை)
	    ctx = omp_check_context_selector (match_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  எனில் (ctx != error_mark_முனை
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      மரம் outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  எனில் (ctx == error_mark_முனை
	      || !omp_context_selector_matches (ctx, NULL_மரம், பொய், உண்மை))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_to_pragma_eol (parser, பொய்);
	      c_parser_skip_to_pragma_omp_end_declare_variant (parser);
	      திரும்பு;
	    }
	  இல்லையெனில்
	    {
	      தருக்க attr_syntax = parser->in_omp_attribute_pragma != வெற்று;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_safe_தள்ளு (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_to_pragma_eol (parser);
	}
      இல்லையெனில்
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser, பொய்);
	}
    }
  இல்லையெனில் எனில் (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      தருக்க attr_syntax = parser->in_omp_attribute_pragma != வெற்று;
      c_parser_omp_assumption_clauses (parser, பொய்);
      கட்டமைப்பு c_omp_begin_assumes_data a = { attr_syntax };
      vec_safe_தள்ளு (current_omp_begin_assumes, a);
    }
  இல்லையெனில்
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

நிலையான வெறுமை
c_parser_omp_end (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  மாறிலி எழுத்து *p = "";
  c_parser_consume_pragma (parser);
  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
  எனில் (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      எனில் (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  தருக்க attr_syntax = parser->in_omp_attribute_pragma != வெற்று;
	  c_parser_skip_to_pragma_eol (parser);
	  எனில் (!vec_safe_length (current_omp_declare_target_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  இல்லையெனில்
	    {
	      c_omp_declare_target_attr
		a = current_omp_declare_target_attribute->எடு ();
	      எனில் (a.attr_syntax != attr_syntax)
		{
		  எனில் (a.attr_syntax)
		    error_at (loc,
			      "%qs in attribute syntax terminated "
			      "with %qs in pragma syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		  இல்லையெனில்
		    error_at (loc,
			      "%qs in pragma syntax terminated "
			      "with %qs in attribute syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		}
	    }
	}
      இல்லையெனில் எனில் (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  தருக்க attr_syntax = parser->in_omp_attribute_pragma != வெற்று;
	  c_parser_skip_to_pragma_eol (parser);
	  எனில் (!vec_safe_length (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  இல்லையெனில்
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->எடு ();
	      எனில் (a.attr_syntax != attr_syntax)
		{
		  எனில் (a.attr_syntax)
		    error_at (loc,
			      "%<begin declare variant%> in attribute syntax "
			      "terminated with "
			      "%<end declare variant%> in pragma syntax");
		  இல்லையெனில்
		    error_at (loc,
			      "%<begin declare variant%> in pragma syntax "
			      "terminated with "
			      "%<end declare variant%> in attribute syntax");
		}
	    }
	}
      இல்லையெனில்
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser);
	  திரும்பு;
	}
    }
  இல்லையெனில் எனில் (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      தருக்க attr_syntax = parser->in_omp_attribute_pragma != வெற்று;
      c_parser_skip_to_pragma_eol (parser);
      எனில் (!vec_safe_length (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      இல்லையெனில்
	{
	  c_omp_begin_assumes_data
	    a = current_omp_begin_assumes->எடு ();
	  எனில் (a.attr_syntax != attr_syntax)
	    {
	      எனில் (a.attr_syntax)
		error_at (loc,
			  "%qs in attribute syntax terminated "
			  "with %qs in pragma syntax",
			  "begin assumes", "end assumes");
	      இல்லையெனில்
		error_at (loc,
			  "%qs in pragma syntax terminated "
			  "with %qs in attribute syntax",
			  "begin assumes", "end assumes");
	    }
	}
    }
  இல்லையெனில்
    {
      c_parser_error (parser, "expected %<declare%> or %<assumes%>");
      c_parser_skip_to_pragma_eol (parser);
    }
}

/* OpenMP 5.0
   #pragma omp declare mapper ([mapper-identifier :] type var) \
			      [clause [ [,] clause ] ... ] new-line  */

நிலையான வெறுமை
c_parser_omp_declare_mapper (c_parser *parser, எண்ணிக்கை pragma_context context)
{
  மரம் type, mapper_name = NULL_மரம், var = NULL_மரம், stmt, stmtlist;
  மரம் maplist = NULL_மரம், mapper_id, mapper_decl, t;
  c_token *token;

  எனில் (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare mapper%> not at file or block scope");
      செல் fail;
    }

  எனில் (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    செல் fail;

  token = c_parser_peek_token (parser);

  எனில் (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      தேர்வு (token->type)
	{
	நிலை CPP_NAME:
	  mapper_name = token->மதிப்பு;
	  c_parser_consume_token (parser);
	  நிறுத்து;
	நிலை CPP_KEYWORD:
	  எனில் (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_மரம்;
	      c_parser_consume_token (parser);
	      நிறுத்து;
	    }
	  /* Fallthrough.  */
	இயல்பு:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_to_pragma_eol (parser, பொய்);
	  திரும்பு;
	}

      எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	செல் fail;
    }

  mapper_id = c_omp_mapper_id (mapper_name);
  mapper_decl = c_omp_mapper_decl (mapper_id);

  {
    location_t loc = c_parser_peek_token (parser)->location;
    கட்டமைப்பு c_type_name *ctype = c_parser_type_name (parser);
    type = groktypename (ctype, வெற்று, வெற்று);
    எனில் (type == error_mark_முனை)
      செல் fail;
    எனில் (!RECORD_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_to_pragma_eol (parser, பொய்);
	திரும்பு;
      }
    க்கு (மரம் t = DECL_INITIAL (mapper_decl); t; t = மரம்_CHAIN (t))
      எனில் (comptypes (மரம்_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_POINTER (mapper_id)
		      + அளவு ("omp declare mapper ") - 1,
		    type);
	  மரம் prevmapper = மரம்_மதிப்பு (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_SOURCE_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_to_pragma_eol (parser, பொய்);
	  திரும்பு;
	}
  }

  token = c_parser_peek_token (parser);
  எனில் (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->மதிப்பு, type);
      c_parser_consume_token (parser);
      DECL_ARTIFICIAL (var) = 1;
    }
  இல்லையெனில்
    {
      error_at (token->location, "expected identifier");
      செல் fail;
    }

  எனில் (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    செல் fail;

  தள்ளு_scope ();
  stmtlist = தள்ளு_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  போது (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);
      எனில் (c_kind != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (here, "unexpected clause");
	  செல் fail;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, உண்மை);
    }

  எனில் (maplist == NULL_மரம்)
    {
      error_at (உள்ளீடு_location, "missing %<map%> clause");
      செல் fail;
    }
  மரம் list;
  க்கு (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      மரம் dvar = OMP_CLAUSE_DECL (list);
      போது (!DECL_P (dvar) && மரம்_OPERAND_LENGTH (dvar))
	dvar = மரம்_OPERAND (dvar, 0);
      எனில் (dvar == var)
	நிறுத்து;
    }
  எனில் (!list)
    error_at (உள்ளீடு_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_முனை (OMP_DECLARE_MAPPER);
  மரம்_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  add_stmt (stmt);

  எடு_stmt_list (stmtlist);
  எடு_scope ();

  c_parser_skip_to_pragma_eol (parser);

  t = மரம்_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  திரும்பு;

 fail:
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 4.0
   #pragma omp declare reduction (reduction-id : typename-list : expression) \
      initializer-clause[opt] new-line

   initializer-clause:
      initializer (omp_priv = initializer)
      initializer (function-name (argument-list))  */

நிலையான வெறுமை
c_parser_omp_declare_reduction (c_parser *parser, எண்ணிக்கை pragma_context context)
{
  unsigned முழு tokens_avail = 0, i;
  c_token *saved_tokens = வெற்று;
  vec<மரம்> types = vNULL;
  vec<c_token> clauses = vNULL;
  எண்ணிக்கை மரம்_code reduc_code = ERROR_MARK;
  மரம் reduc_id = NULL_மரம்;
  மரம் type;
  location_t rloc = c_parser_peek_token (parser)->location;

  எனில் (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare reduction%> not at file or block scope");
      செல் fail;
    }

  எனில் (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    செல் fail;

  தேர்வு (c_parser_peek_token (parser)->type)
    {
    நிலை CPP_PLUS:
      reduc_code = PLUS_கோவை;
      நிறுத்து;
    நிலை CPP_MULT:
      reduc_code = MULT_கோவை;
      நிறுத்து;
    நிலை CPP_MINUS:
      reduc_code = MINUS_கோவை;
      நிறுத்து;
    நிலை CPP_AND:
      reduc_code = BIT_AND_கோவை;
      நிறுத்து;
    நிலை CPP_XOR:
      reduc_code = BIT_XOR_கோவை;
      நிறுத்து;
    நிலை CPP_OR:
      reduc_code = BIT_IOR_கோவை;
      நிறுத்து;
    நிலை CPP_AND_AND:
      reduc_code = TRUTH_ANDIF_கோவை;
      நிறுத்து;
    நிலை CPP_OR_OR:
      reduc_code = TRUTH_ORIF_கோவை;
      நிறுத்து;
    நிலை CPP_NAME:
      மாறிலி எழுத்து *p;
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp (p, "min") == 0)
	{
	  reduc_code = MIN_கோவை;
	  நிறுத்து;
	}
      எனில் (strcmp (p, "max") == 0)
	{
	  reduc_code = MAX_கோவை;
	  நிறுத்து;
	}
      reduc_id = c_parser_peek_token (parser)->மதிப்பு;
      நிறுத்து;
    இயல்பு:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      செல் fail;
    }

  மரம் orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_code, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    செல் fail;

  போது (உண்மை)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      கட்டமைப்பு c_type_name *ctype = c_parser_type_name (parser);
      எனில் (ctype != வெற்று)
	{
	  type = groktypename (ctype, வெற்று, வெற்று);
	  எனில் (type == error_mark_முனை)
	    ;
	  இல்லையெனில் எனில் ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || மரம்_CODE (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_மரம்)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  இல்லையெனில் எனில் (மரம்_CODE (type) == FUNCTION_TYPE
		   || மரம்_CODE (type) == ARRAY_TYPE)
	    error_at (loc, "function or array type in "
		      "%<#pragma omp declare reduction%>");
	  இல்லையெனில் எனில் (TYPE_ATOMIC (type))
	    error_at (loc, "%<_Atomic%> qualified type in "
			   "%<#pragma omp declare reduction%>");
	  இல்லையெனில் எனில் (TYPE_QUALS_NO_ADDR_SPACE (type))
	    error_at (loc, "const, volatile or restrict qualified type in "
			   "%<#pragma omp declare reduction%>");
	  இல்லையெனில்
	    {
	      மரம் t;
	      க்கு (t = DECL_INITIAL (reduc_decl); t; t = மரம்_CHAIN (t))
		எனில் (comptypes (மரம்_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_POINTER (reduc_id)
				   + அளவு ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_SOURCE_LOCATION (மரம்_VEC_ELT (மரம்_மதிப்பு (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    நிறுத்து;
		  }
	      எனில் (t == NULL_மரம்)
		types.safe_தள்ளு (type);
	    }
	  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  இல்லையெனில்
	    நிறுத்து;
	}
      இல்லையெனில்
	நிறுத்து;
    }

  எனில் (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_empty ())
    {
     fail:
      clauses.release ();
      types.release ();
      போது (உண்மை)
	{
	  c_token *token = c_parser_peek_token (parser);
	  எனில் (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    நிறுத்து;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_to_pragma_eol (parser);
      திரும்பு;
    }

  எனில் (types.length () > 1)
    {
      போது (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  எனில் (token->type == CPP_EOF)
	    செல் fail;
	  clauses.safe_தள்ளு (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_தள்ளு (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, அளவு (eof_token));
      eof_token.type = CPP_EOF;
      clauses.safe_தள்ளு (eof_token);
      clauses.safe_தள்ளு (eof_token);
    }

  முழு errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_tokens = parser->tokens;
      tokens_avail = parser->tokens_avail;
      எனில் (!clauses.is_empty ())
	{
	  parser->tokens = clauses.address ();
	  parser->tokens_avail = clauses.length ();
	  parser->in_pragma = உண்மை;
	}

      தருக்க nested = current_function_decl != NULL_மரம்;
      எனில் (nested)
	c_தள்ளு_function_context ();
      மரம் fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, உண்மை);
      தள்ளு_scope ();
      மரம் stmt = தள்ளு_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      மரம் omp_out = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_out) = 1;
      DECL_CONTEXT (omp_out) = fndecl;
      pushdecl (omp_out);
      மரம் omp_in = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_in) = 1;
      DECL_CONTEXT (omp_in) = fndecl;
      pushdecl (omp_in);
      கட்டமைப்பு c_கோவை combiner = c_parser_expression (parser);
      கட்டமைப்பு c_கோவை initializer;
      மரம் omp_priv = NULL_மரம், omp_orig = NULL_மரம்;
      தருக்க bad = பொய்;
      initializer.set_error ();
      எனில் (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	bad = உண்மை;
      இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      எனில் (!bad
	  && (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->மதிப்பு),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  எடு_scope ();
	  தள்ளு_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_முனை;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  எனில் (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    bad = உண்மை;
	  இல்லையெனில் எனில் (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      bad = உண்மை;
	    }
	  இல்லையெனில் எனில் (strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->மதிப்பு),
			   "omp_priv") != 0)
	    {
	      எனில் (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_kind != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  bad = உண்மை;
		}
	      இல்லையெனில்
		initializer = c_parser_postfix_expression (parser);
	      எனில் (initializer.மதிப்பு
		  && மரம்_CODE (initializer.மதிப்பு) == CALL_கோவை)
		{
		  முழு j;
		  மரம் c = initializer.மதிப்பு;
		  க்கு (j = 0; j < call_கோவை_nargs (c); j++)
		    {
		      மரம் a = CALL_கோவை_ARG (c, j);
		      STRIP_NOPS (a);
		      எனில் (மரம்_CODE (a) == ADDR_கோவை
			  && மரம்_OPERAND (a, 0) == omp_priv)
			நிறுத்து;
		    }
		  எனில் (j == call_கோவை_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  இல்லையெனில்
	    {
	      c_parser_consume_token (parser);
	      எனில் (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		bad = உண்மை;
	      இல்லையெனில்
		{
		  மரம் st = தள்ளு_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (வரி_table, loc);
		  start_init (omp_priv, NULL_மரம், பொய், பொய், &richloc);
		  கட்டமைப்பு c_கோவை init = c_parser_initializer (parser, omp_priv);
		  finish_init ();
		  finish_decl (omp_priv, loc, init.மதிப்பு,
		      	       init.original_type, NULL_மரம்);
		  எடு_stmt_list (st);
		}
	    }
	  எனில் (!bad
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    bad = உண்மை;
	}

      எனில் (!bad)
	{
	  c_parser_skip_to_pragma_eol (parser);

	  மரம் t = மரம்_cons (type, make_மரம்_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_SOURCE_LOCATION (omp_out) = rloc;
	  மரம்_VEC_ELT (மரம்_மதிப்பு (t), 0) = omp_out;
	  மரம்_VEC_ELT (மரம்_மதிப்பு (t), 1) = omp_in;
	  மரம்_VEC_ELT (மரம்_மதிப்பு (t), 2) = combiner.மதிப்பு;
	  walk_மரம் (&combiner.மதிப்பு, c_check_omp_declare_reduction_r,
		     &மரம்_VEC_ELT (மரம்_மதிப்பு (t), 0), வெற்று);
	  எனில் (omp_priv)
	    {
	      DECL_SOURCE_LOCATION (omp_priv) = rloc;
	      மரம்_VEC_ELT (மரம்_மதிப்பு (t), 3) = omp_priv;
	      மரம்_VEC_ELT (மரம்_மதிப்பு (t), 4) = omp_orig;
	      மரம்_VEC_ELT (மரம்_மதிப்பு (t), 5) = initializer.மதிப்பு;
	      walk_மரம் (&initializer.மதிப்பு, c_check_omp_declare_reduction_r,
			 &மரம்_VEC_ELT (மரம்_மதிப்பு (t), 3), வெற்று);
	      walk_மரம் (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &மரம்_VEC_ELT (மரம்_மதிப்பு (t), 3), வெற்று);
	    }
	}

      எடு_stmt_list (stmt);
      எடு_scope ();
      எனில் (cfun->language != வெற்று)
	{
	  ggc_free (cfun->language);
	  cfun->language = வெற்று;
	}
      set_cfun (வெற்று);
      current_function_decl = NULL_மரம்;
      எனில் (nested)
	c_எடு_function_context ();

      எனில் (!clauses.is_empty ())
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}
      எனில் (bad)
	செல் fail;
      எனில் (errs != errorcount)
	நிறுத்து;
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

நிலையான தருக்க
c_parser_omp_declare (c_parser *parser, எண்ணிக்கை pragma_context context)
{
  c_parser_consume_pragma (parser);
  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  திரும்பு உண்மை;
	}
      எனில் (strcmp (p, "reduction") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_reduction (parser, context);
	  திரும்பு பொய்;
	}
      எனில் (strcmp (p, "mapper") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_mapper (parser, context);
	  திரும்பு பொய்;
	}
      எனில் (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, பொய்);
	  திரும்பு பொய்;
	}
      எனில் (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_target (parser);
	  திரும்பு பொய்;
	}
      எனில் (strcmp (p, "variant") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  திரும்பு உண்மை;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_to_pragma_eol (parser);
  திரும்பு பொய்;
}

/* OpenMP 5.0
   #pragma omp requires clauses[optseq] new-line  */

நிலையான வெறுமை
c_parser_omp_requires (c_parser *parser)
{
  எண்ணிக்கை omp_requires new_req = (எண்ணிக்கை omp_requires) 0;

  c_parser_consume_pragma (parser);

  location_t loc = c_parser_peek_token (parser)->location;
  போது (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      எனில் (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      எனில் (c_parser_next_token_is (parser, CPP_NAME))
	{
	  மாறிலி எழுத்து *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  எண்ணிக்கை omp_requires this_req = (எண்ணிக்கை omp_requires) 0;

	  எனில் (!strcmp (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_ADDRESS;
	  இல்லையெனில் எனில் (!strcmp (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_MEMORY;
	  இல்லையெனில் எனில் (!strcmp (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  இல்லையெனில் எனில் (!strcmp (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  இல்லையெனில் எனில் (!strcmp (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_REVERSE_OFFLOAD;
	  இல்லையெனில் எனில் (!strcmp (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      எனில் (parens.require_open (parser))
		{
		  எனில் (c_parser_next_token_is (parser, CPP_NAME))
		    {
		      மரம் v = c_parser_peek_token (parser)->மதிப்பு;
		      p = IDENTIFIER_POINTER (v);

		      எனில் (!strcmp (p, "seq_cst"))
			this_req
			  = (எண்ணிக்கை omp_requires) OMP_MEMORY_ORDER_SEQ_CST;
		      இல்லையெனில் எனில் (!strcmp (p, "relaxed"))
			this_req
			  = (எண்ணிக்கை omp_requires) OMP_MEMORY_ORDER_RELAXED;
		      இல்லையெனில் எனில் (!strcmp (p, "release"))
			this_req
			  = (எண்ணிக்கை omp_requires) OMP_MEMORY_ORDER_RELEASE;
		      இல்லையெனில் எனில் (!strcmp (p, "acq_rel"))
			this_req
			  = (எண்ணிக்கை omp_requires) OMP_MEMORY_ORDER_ACQ_REL;
		      இல்லையெனில் எனில் (!strcmp (p, "acquire"))
			this_req
			  = (எண்ணிக்கை omp_requires) OMP_MEMORY_ORDER_ACQUIRE;
		    }
		  எனில் (this_req == 0)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<acq_rel%>, %<acquire%>, "
				"%<relaxed%>, %<release%> or %<seq_cst%>");
		      தேர்வு (c_parser_peek_token (parser)->type)
			{
			நிலை CPP_EOF:
			நிலை CPP_PRAGMA_EOL:
			நிலை CPP_CLOSE_PAREN:
			  நிறுத்து;
			இயல்பு:
			  எனில் (c_parser_peek_2nd_token (parser)->type
			      == CPP_CLOSE_PAREN)
			    c_parser_consume_token (parser);
			  நிறுத்து;
			}
		    }
		  இல்லையெனில்
		    c_parser_consume_token (parser);

		  parens.skip_until_found_close (parser);
		  எனில் (this_req == 0)
		    {
		      c_parser_skip_to_pragma_eol (parser, பொய்);
		      திரும்பு;
		    }
		}
	      p = வெற்று;
	    }
	  இல்லையெனில்
	    {
	      error_at (cloc, "expected %<unified_address%>, "
			      "%<unified_shared_memory%>, "
			      "%<self_maps%>, "
			      "%<dynamic_allocators%>, "
			       "%<reverse_offload%> "
			       "or %<atomic_default_mem_order%> clause");
	      c_parser_skip_to_pragma_eol (parser, பொய்);
	      திரும்பு;
	    }
	  எனில் (p)
	    c_parser_consume_token (parser);
	  எனில் (this_req)
	    {
	      எனில் ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  எனில் ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  எனில் (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_mask & OMP_REQUIRES_TARGET_USED) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      இல்லையெனில் எனில் ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (எண்ணிக்கை omp_requires) 0;
		}
	      இல்லையெனில் எனில் ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (எண்ணிக்கை omp_requires)
		       (omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER);
		}
	      இல்லையெனில் எனில் ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (எண்ணிக்கை omp_requires) (new_req | this_req);
	      omp_requires_mask
		= (எண்ணிக்கை omp_requires) (omp_requires_mask | this_req);
	      தொடர்;
	    }
	}
      நிறுத்து;
    }
  c_parser_skip_to_pragma_eol (parser);

  எனில் (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

நிலையான மரம்
c_finish_taskloop_clauses (மரம் clauses)
{
  மரம் *pc = &clauses;
  க்கு (மரம் c = clauses; c; c = *pc)
    {
      தருக்க remove = பொய்;
      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
	{
	  மரம் type = strip_array_types (மரம்_TYPE (OMP_CLAUSE_DECL (c)));
	  எனில் (integer_zerop (TYPE_SIZE_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் (மரம்_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      remove = உண்மை;
	    }
	}
      எனில் (remove)
	*pc = OMP_CLAUSE_CHAIN (c);
      இல்லையெனில்
	pc = &OMP_CLAUSE_CHAIN (c);
    }
  திரும்பு clauses;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_இலக்கம்_TASKS)	\
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

நிலையான மரம்
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       எழுத்து *p_name, omp_clause_mask mask, மரம் *cclauses,
		       தருக்க *if_p)
{
  மரம் clauses, block, ret;

  strcat (p_name, " taskloop");
  mask |= OMP_TASKLOOP_CLAUSE_MASK;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  எனில் ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_இலக்கம்_THREADS)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IN_REDUCTION);

  எனில் (c_parser_next_token_is (parser, CPP_NAME))
    {
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);

      எனில் (strcmp (p, "simd") == 0)
	{
	  மரம் cclauses_buf[C_OMP_CLAUSE_SPLIT_மொத்தம்];
	  எனில் (cclauses == வெற்று)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  எனில் (!flag_openmp)  /* flag_openmp_simd  */
	    திரும்பு c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (உண்மை);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, உண்மை);
	  எனில் (ret == வெற்று)
	    திரும்பு ret;
	  ret = make_முனை (OMP_TASKLOOP);
	  மரம்_TYPE (ret) = void_type_முனை;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_finish_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  SET_கோவை_LOCATION (ret, loc);
	  add_stmt (ret);
	  திரும்பு ret;
	}
    }
  எனில் (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, பொய்);
      திரும்பு NULL_மரம்;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == வெற்று);
  எனில் (cclauses)
    {
      omp_split_clauses (loc, OMP_TASKLOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
    }

  clauses = c_finish_taskloop_clauses (clauses);
  block = c_begin_compound_stmt (உண்மை);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, வெற்று, if_p);
  block = c_end_compound_stmt (loc, block, உண்மை);
  add_stmt (block);

  திரும்பு ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
நிலையான மரம்
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  மரம் sizes = NULL_மரம்;

  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  எனில் (tok->type != CPP_NAME
      || strcmp ("sizes", IDENTIFIER_POINTER (tok->மதிப்பு)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      திரும்பு error_mark_முனை;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  எனில் (!parens.require_open (parser))
    திரும்பு error_mark_முனை;

  vec<மரம், va_gc> *sizes_vec
    = c_parser_கோவை_list (parser, உண்மை, உண்மை, வெற்று, வெற்று, வெற்று, வெற்று);
  sizes = build_மரம்_list_vec (sizes_vec);
  release_மரம்_vector (sizes_vec);

  க்கு (மரம் s = sizes; s; s = மரம்_CHAIN (s))
    {
      மரம் கோவை = மரம்_மதிப்பு (s);
      எனில் (கோவை == error_mark_முனை)
	{
	  parens.skip_until_found_close (parser);
	  திரும்பு error_mark_முனை;
	}

      HOST_WIDE_INT n;
      எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (கோவை))
	  || !மரம்_fits_shwi_p (கோவை)
	  || (n = மரம்_to_shwi (கோவை)) <= 0
	  || (முழு) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  மரம்_மதிப்பு (s) = integer_one_முனை;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  மரம் c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  திரும்பு c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

நிலையான மரம்
c_parser_omp_tile (location_t loc, c_parser *parser, தருக்க *if_p)
{
  மரம் clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_to_pragma_eol (parser);

  எனில் (!clauses || clauses == error_mark_முனை)
    திரும்பு error_mark_முனை;

  மரம் block = c_begin_compound_stmt (உண்மை);
  மரம் ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    வெற்று, if_p);
  block = c_end_compound_stmt (loc, block, உண்மை);
  add_stmt (block);

  திரும்பு ret;
}

#define OMP_UNROLL_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FULL))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

நிலையான மரம்
c_parser_omp_unroll (location_t loc, c_parser *parser, தருக்க *if_p)
{
  மரம் clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_MASK,
					   "#pragma omp unroll", உண்மை);

  மரம் block = c_begin_compound_stmt (உண்மை);
  மரம் ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    வெற்று, if_p);
  block = c_end_compound_stmt (loc, block, உண்மை);
  add_stmt (block);

  திரும்பு ret;
}

/* OpenMP 5.1
   #pragma omp nothing new-line  */

நிலையான வெறுமை
c_parser_omp_nothing (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp error clauses[optseq] new-line  */

நிலையான தருக்க
c_parser_omp_error (c_parser *parser, எண்ணிக்கை pragma_context context)
{
  முழு at_compilation = -1;
  முழு severity_fatal = -1;
  மரம் message = NULL_மரம்;
  தருக்க bad = பொய்;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  போது (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      எனில் (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      எனில் (!c_parser_next_token_is (parser, CPP_NAME))
	நிறுத்து;

      மாறிலி எழுத்து *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      location_t cloc = c_parser_peek_token (parser)->location;
      நிலையான மாறிலி எழுத்து *args[] = {
	"execution", "compilation", "warning", "fatal"
      };
      முழு *v = வெற்று;
      முழு idx = 0, n = -1;
      மரம் m = NULL_மரம்;

      எனில் (!strcmp (p, "at"))
	v = &at_compilation;
      இல்லையெனில் எனில் (!strcmp (p, "severity"))
	{
	  v = &severity_fatal;
	  idx += 2;
	}
      இல்லையெனில் எனில் (strcmp (p, "message"))
	{
	  error_at (cloc,
		    "expected %<at%>, %<severity%> or %<message%> clause");
	  c_parser_skip_to_pragma_eol (parser, பொய்);
	  திரும்பு பொய்;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      எனில் (parens.require_open (parser))
	{
	  எனில் (v == வெற்று)
	    {
	      location_t கோவை_loc = c_parser_peek_token (parser)->location;
	      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	      கோவை = convert_lvalue_to_rvalue (கோவை_loc, கோவை, உண்மை, உண்மை);
	      m = convert (const_string_type_முனை, கோவை.மதிப்பு);
	      m = c_fully_fold (m, பொய், வெற்று);
	    }
	  இல்லையெனில்
	    {
	      எனில் (c_parser_next_token_is (parser, CPP_NAME))
		{
		  மரம் val = c_parser_peek_token (parser)->மதிப்பு;
		  மாறிலி எழுத்து *q = IDENTIFIER_POINTER (val);

		  எனில் (!strcmp (q, args[idx]))
		    n = 0;
		  இல்லையெனில் எனில் (!strcmp (q, args[idx + 1]))
		    n = 1;
		}
	      எனில் (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", args[idx], args[idx + 1]);
		  bad = உண்மை;
		  தேர்வு (c_parser_peek_token (parser)->type)
		    {
		    நிலை CPP_EOF:
		    நிலை CPP_PRAGMA_EOL:
		    நிலை CPP_CLOSE_PAREN:
		      நிறுத்து;
		    இயல்பு:
		      எனில் (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)
			c_parser_consume_token (parser);
		      நிறுத்து;
		    }
		}
	      இல்லையெனில்
		c_parser_consume_token (parser);
	    }

	  parens.skip_until_found_close (parser);

	  எனில் (v == வெற்று)
	    {
	      எனில் (message)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = உண்மை;
		}
	      இல்லையெனில்
		message = m;
	    }
	  இல்லையெனில் எனில் (n != -1)
	    {
	      எனில் (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = உண்மை;
		}
	      இல்லையெனில்
		*v = n;
	    }
	}
      இல்லையெனில்
	bad = உண்மை;
    }
  c_parser_skip_to_pragma_eol (parser);
  எனில் (bad)
    திரும்பு உண்மை;

  எனில் (at_compilation == -1)
    at_compilation = 1;
  எனில் (severity_fatal == -1)
    severity_fatal = 1;
  எனில் (!at_compilation)
    {
      எனில் (context != pragma_compound)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may only be used in compound statements");
	  திரும்பு உண்மை;
	}
      எனில் (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->in_intervening_code)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->fail = உண்மை;
	  திரும்பு உண்மை;
	}
      மரம் fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_IN_GOMP_ERROR
						: BUILT_IN_GOMP_WARNING);
      எனில் (!message)
	message = build_zero_cst (const_string_type_முனை);
      மரம் stmt = build_call_கோவை_loc (loc, fndecl, 2, message,
				       build_all_ones_cst (size_type_முனை));
      add_stmt (stmt);
      திரும்பு உண்மை;
    }
  மாறிலி எழுத்து *செய்தி = வெற்று;
  எனில் (message)
    {
      செய்தி = c_getstr (message);
      எனில் (செய்தி == வெற்று)
	செய்தி = _("<message unknown at compile time>");
    }
  மாறிலி எண்ணிக்கை diagnostics::kind diag_kind = (severity_fatal
					    ? diagnostics::kind::error
					    : diagnostics::kind::warning);
  எனில் (செய்தி)
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered: %s", செய்தி);
  இல்லையெனில்
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered");
  திரும்பு பொய்;
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

நிலையான வெறுமை
c_parser_omp_assumption_clauses (c_parser *parser, தருக்க is_assume)
{
  தருக்க no_openmp = பொய்;
  தருக்க no_openmp_constructs = பொய்;
  தருக்க no_openmp_routines = பொய்;
  தருக்க no_parallelism = பொய்;
  bitmap_head absent_head, contains_head;

  bitmap_obstack_initialize (வெற்று);
  bitmap_initialize (&absent_head, &bitmap_default_obstack);
  bitmap_initialize (&contains_head, &bitmap_default_obstack);

  எனில் (c_parser_next_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  போது (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      எனில் (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      எனில் (!c_parser_next_token_is (parser, CPP_NAME))
	நிறுத்து;

      மாறிலி எழுத்து *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      location_t cloc = c_parser_peek_token (parser)->location;

      எனில் (!strcmp (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  எனில் (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = உண்மை;
	}
      இல்லையெனில் எனில் (!strcmp (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  எனில் (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = உண்மை;
	}
      இல்லையெனில் எனில் (!strcmp (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  எனில் (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = உண்மை;
	}
      இல்லையெனில் எனில் (!strcmp (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  எனில் (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = உண்மை;
	}
      இல்லையெனில் எனில் (!strcmp (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  எனில் (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_கோவை கோவை = c_parser_கோவை_no_commas (parser, வெற்று);
	      மரம் t = convert_lvalue_to_rvalue (eloc, கோவை, உண்மை, உண்மை).மதிப்பு;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, பொய், வெற்று);
	      எனில் (is_assume && t != error_mark_முனை)
		{
		  மரம் fn = build_call_கோவை_internal_loc (eloc, IFN_ASSUME,
							  void_type_முனை, 1,
							  t);
		  add_stmt (fn);
		}
	      parens.skip_until_found_close (parser);
	    }
	}
      இல்லையெனில் எனில் (!strcmp (p, "absent") || !strcmp (p, "contains"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  எனில் (parens.require_open (parser))
	    {
	      செய்
		{
		  மாறிலி எழுத்து *directive[3] = {};
		  முழு i;
		  location_t dloc = c_parser_peek_token (parser)->location;
		  க்கு (i = 0; i < 3; i++)
		    {
		      மரம் id;
		      எனில் (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->மதிப்பு;
		      இல்லையெனில் எனில் (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  எண்ணிக்கை rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      இல்லையெனில்
			நிறுத்து;
		      directive[i] = IDENTIFIER_POINTER (id);
		    }
		  எனில் (i == 0)
		    error_at (dloc, "expected directive name");
		  இல்லையெனில்
		    {
		      மாறிலி கட்டமைப்பு c_omp_directive *dir
			= c_omp_categorize_directive (directive[0],
						      directive[1],
						      directive[2]);
		      எனில் (dir
			  && dir->id != PRAGMA_OMP_END
			  && (dir->kind == C_OMP_DIR_DECLARATIVE
			      || dir->kind == C_OMP_DIR_INFORMATIONAL
			      || dir->kind == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      இல்லையெனில் எனில் (dir == வெற்று
			       || dir->id == PRAGMA_OMP_END
			       || (!dir->second && directive[1])
			       || (!dir->third && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      இல்லையெனில்
			{
			  முழு id = dir - c_omp_directives;
			  எனில் (bitmap_bit_p (p[0] == 'a' ? &contains_head
							: &absent_head, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  இல்லையெனில் எனில் (!bitmap_set_bit (p[0] == 'a'
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
		      க்கு (; i; --i)
			c_parser_consume_token (parser);
		    }
		  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  இல்லையெனில்
		    நிறுத்து;
		}
	      போது (1);
	      parens.skip_until_found_close (parser);
	    }
	}
      இல்லையெனில் எனில் (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      matching_parens parens;
	      parens.consume_open (parser);
	      c_parser_balanced_token_sequence (parser);
	      parens.require_close (parser);
	    }
	}
      இல்லையெனில்
	{
	  c_parser_consume_token (parser);
	  error_at (cloc, "expected assumption clause");
	  நிறுத்து;
	}
    }
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

நிலையான வெறுமை
c_parser_omp_assume (c_parser *parser, தருக்க *if_p)
{
  c_parser_omp_assumption_clauses (parser, உண்மை);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
}

/* OpenMP 5.1
   #pragma omp assumes clauses[optseq] new-line  */

நிலையான வெறுமை
c_parser_omp_assumes (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_omp_assumption_clauses (parser, பொய்);
}

/* Helper function for c_parser_omp_metadirective.  */

நிலையான வெறுமை
analyze_metadirective_body (c_parser *parser,
			    vec<c_token> &tokens,
			    vec<மரம்> &labels)
{
  முழு nesting_depth = 0;
  முழு bracket_depth = 0;
  தருக்க ignore_label = பொய்;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  போது (1)
    {
      c_token *token = c_parser_peek_token (parser);
      தருக்க stop = பொய்;

      எனில் (c_parser_next_token_is_keyword (parser, RID_CASE))
	ignore_label = உண்மை;

      தேர்வு (token->type)
	{
	நிலை CPP_EOF:
	  நிறுத்து;
	நிலை CPP_NAME:
	  எனில் (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.safe_தள்ளு (token->மதிப்பு);
	  செல் add;
	நிலை CPP_OPEN_BRACE:
	  ++nesting_depth;
	  செல் add;
	நிலை CPP_CLOSE_BRACE:
	  எனில் (--nesting_depth == 0 && bracket_depth == 0)
	    stop = உண்மை;
	  செல் add;
	நிலை CPP_OPEN_PAREN:
	  ++bracket_depth;
	  செல் add;
	நிலை CPP_CLOSE_PAREN:
	  --bracket_depth;
	  செல் add;
	நிலை CPP_COLON:
	  ignore_label = பொய்;
	  செல் add;
	நிலை CPP_SEMICOLON:
	  எனில் (nesting_depth == 0 && bracket_depth == 0)
	    stop = உண்மை;
	  செல் add;
	இயல்பு:
	add:
	  tokens.safe_தள்ளு (*token);
	  எனில் (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  இல்லையெனில் எனில் (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_to_pragma_eol (parser);
	  இல்லையெனில்
	    c_parser_consume_token (parser);
	  எனில் (stop)
	    நிறுத்து;
	  தொடர்;
	}
      நிறுத்து;
    }
}

/* OpenMP 5.0:

  # pragma omp metadirective [clause[, clause]]
*/

நிலையான வெறுமை
c_parser_omp_metadirective (c_parser *parser, தருக்க *if_p)
{
  நிலையான unsigned முழு metadirective_region_மொத்தம் = 0;

  மரம் ret;
  auto_vec<c_token> directive_tokens;
  auto_vec<c_token> body_tokens;
  auto_vec<மரம்> body_labels;
  auto_vec<மாறிலி கட்டமைப்பு c_omp_directive *> directives;
  auto_vec<மரம்> ctxs;
  vec<கட்டமைப்பு omp_variant> candidates;
  தருக்க default_seen = பொய்;
  முழு directive_token_idx = 0;
  மரம் standalone_body = NULL_மரம்;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  தருக்க requires_body = பொய்;

  ret = make_முனை (OMP_METADIRECTIVE);
  SET_கோவை_LOCATION (ret, pragma_loc);
  மரம்_TYPE (ret) = void_type_முனை;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_மரம்;

  c_parser_consume_pragma (parser);
  போது (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      எனில் (c_parser_next_token_is_not (parser, CPP_NAME)
	  && c_parser_next_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  செல் error;
	}

      location_t match_loc = c_parser_peek_token (parser)->location;
      மாறிலி எழுத்து *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      எனில் (strcmp (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.add_fixit_replace (match_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      தருக்க default_p
	= strcmp (p, "default") == 0 || strcmp (p, "otherwise") == 0;
      எனில் (default_p)
	{
	  எனில் (default_seen)
	    {
	      error_at (match_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      செல் error;
	    }
	  default_seen = உண்மை;
	}
      இல்லையெனில் எனில் (default_seen)
	{
	  error_at (match_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  செல் error;
	}
      எனில் (!default_p && strcmp (p, "when") != 0)
	{
	  error_at (match_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  செல் error;
	}

      matching_parens parens;
      மரம் ctx = NULL_மரம்;
      தருக்க skip = பொய்;

      எனில் (!parens.require_open (parser))
	செல் error;

      எனில் (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_மரம்);
	  எனில் (ctx == error_mark_முனை)
	    செல் error;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  எனில் (ctx == error_mark_முனை)
	    செல் error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_மரம், பொய்) == 0);

	  எனில் (c_parser_next_token_is_not (parser, CPP_COLON))
	    {
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      செல் error;
	    }
	  c_parser_consume_token (parser);
	}

      /* Read in the directive type and create a dummy pragma token for
	 it.  */
      location_t loc = c_parser_peek_token (parser)->location;

      மாறிலி எழுத்து *directive[3] = {};
      முழு i;
      க்கு (i = 0; i < 3; i++)
	{
	  மரம் id;
	  எனில் (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      எனில் (i == 0)
		directive[i++] = "nothing";
	      நிறுத்து;
	    }
	  இல்லையெனில் எனில் (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->மதிப்பு;
	  இல்லையெனில் எனில் (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      எண்ணிக்கை rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  இல்லையெனில்
	    நிறுத்து;

	  directive[i] = IDENTIFIER_POINTER (id);
	}
      எனில் (i == 0)
	{
	  error_at (loc, "expected directive name");
	  செல் error;
	}

      மாறிலி கட்டமைப்பு c_omp_directive *omp_directive
	= c_omp_categorize_directive (directive[0],
				      directive[1],
				      directive[2]);

      எனில் (omp_directive == வெற்று)
	{
	  க்கு (முழு j = 0; j < i; j++)
	    c_parser_consume_token (parser);
	  c_parser_error (parser, "unknown directive name");
	  செல் error;
	}
      இல்லையெனில்
	{
	  முழு token_மொத்தம் = 0;
	  எனில் (omp_directive->first) token_மொத்தம்++;
	  எனில் (omp_directive->second) token_மொத்தம்++;
	  எனில் (omp_directive->third) token_மொத்தம்++;
	  க்கு (முழு j = 0; j < token_மொத்தம்; j++)
	    c_parser_consume_token (parser);
	}
      எனில் (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  செல் error;
	}
      எனில் (omp_directive->kind == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  செல் error;
	}
      எனில் (omp_directive->kind == C_OMP_DIR_CONSTRUCT)
	requires_body = உண்மை;

      எனில் (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_kind = (எண்ணிக்கை pragma_kind) omp_directive->id;

	  directives.safe_தள்ளு (omp_directive);
	  directive_tokens.safe_தள்ளு (pragma_token);
	  ctxs.safe_தள்ளு (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      முழு nesting_depth = 0;
      போது (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  தேர்வு (token->type)
	    {
	    நிலை CPP_EOF:
	    நிலை CPP_PRAGMA_EOL:
	      நிறுத்து;
	    நிலை CPP_OPEN_PAREN:
	      ++nesting_depth;
	      செல் add;
	    நிலை CPP_CLOSE_PAREN:
	      எனில் (nesting_depth-- == 0)
		{
		  c_parser_consume_token (parser);
		  நிறுத்து;
		}
	      செல் add;
	    இயல்பு:
	    add:
	      எனில் (!skip)
		directive_tokens.safe_தள்ளு (*token);
	      c_parser_consume_token (parser);
	      தொடர்;
	    }
	  நிறுத்து;
	}

      எனில் (!skip)
	{
	  c_token eol_token;
	  memset (&eol_token, 0, அளவு (eol_token));
	  eol_token.type = CPP_PRAGMA_EOL;
	  directive_tokens.safe_தள்ளு (eol_token);
	}
    }
  c_parser_skip_to_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  எனில் (ctxs.length () == 1)
    {
      மரம் ctx = ctxs[0];
      எனில் (ctx == NULL_மரம்
	  || (omp_context_selector_matches (ctx, NULL_மரம், பொய்) == 1
	      && directive_tokens[0].pragma_kind == PRAGMA_OMP_NOTHING))
	திரும்பு;
    }

  எனில் (!default_seen)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      மாறிலி கட்டமைப்பு c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", வெற்று, வெற்று);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_kind = PRAGMA_OMP_NOTHING;

      directives.safe_தள்ளு (omp_directive);
      directive_tokens.safe_தள்ளு (pragma_token);
      ctxs.safe_தள்ளு (NULL_மரம்);

      c_token eol_token;
      memset (&eol_token, 0, அளவு (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_tokens.safe_தள்ளு (eol_token);
    }

  எனில் (requires_body)
    analyze_metadirective_body (parser, body_tokens, body_labels);

  /* Process each candidate directive.  */
  unsigned i;
  மரம் ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> tokens;

      /* Add the directive tokens.  */
      செய்
	tokens.safe_தள்ளு (directive_tokens [directive_token_idx++]);
      போது (tokens.last ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_tokens.is_empty ());
      க்கு (unsigned j = 0; j < body_tokens.length (); j++)
	tokens.safe_தள்ளு (body_tokens[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, அளவு (eof_token));
      eof_token.type = CPP_EOF;
      tokens.safe_தள்ளு (eof_token);
      tokens.safe_தள்ளு (eof_token);

      unsigned முழு old_tokens_avail = parser->tokens_avail;
      c_token *old_tokens = parser->tokens;
      கட்டமைப்பு omp_attribute_pragma_state *old_in_omp_attribute_pragma
	= parser->in_omp_attribute_pragma;
      கட்டமைப்பு omp_metadirective_parse_data *old_state
	= parser->omp_metadirective_state;

      கட்டமைப்பு omp_metadirective_parse_data new_state;
      new_state.body_labels = &body_labels;
      new_state.region_இலக்கம் = ++metadirective_region_மொத்தம்;

      parser->tokens = tokens.address ();
      parser->tokens_avail = tokens.length ();
      parser->in_omp_attribute_pragma = வெற்று;
      parser->omp_metadirective_state = &new_state;

      முழு prev_errorcount = errorcount;
      மரம் directive = c_begin_compound_stmt (உண்மை);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_மரம்);
      directive = c_end_compound_stmt (pragma_loc, directive, உண்மை);
      தருக்க standalone_p
	= directives[i]->kind == C_OMP_DIR_STANDALONE
	  || directives[i]->kind == C_OMP_DIR_UTILITY;
      எனில் (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  எனில் (standalone_body == NULL_மரம்)
	    {
	      standalone_body = தள்ளு_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = எடு_stmt_list (standalone_body);
	    }
	  இல்லையெனில்
	    c_parser_skip_to_end_of_block_or_statement (parser, உண்மை);
	}

      மரம் body = standalone_p ? standalone_body : NULL_மரம்;
      மரம் variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      எனில் (errorcount == prev_errorcount)
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
  எனில் (!candidates.is_empty ())
    ret = c_omp_expand_variant_construct (candidates);

  add_stmt (ret);
  திரும்பு;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  எனில் (parser->in_pragma)
    c_parser_skip_to_pragma_eol (parser, பொய்);
}

/* Main entry point to parsing most OpenMP pragmas.  */

நிலையான வெறுமை
c_parser_omp_construct (c_parser *parser, தருக்க *if_p)
{
  எண்ணிக்கை pragma_kind p_kind;
  location_t loc;
  மரம் stmt;
  எழுத்து p_name[அளவு "#pragma omp teams distribute parallel for simd"];
  omp_clause_mask mask (0);

  loc = c_parser_peek_token (parser)->location;
  p_kind = c_parser_peek_token (parser)->pragma_kind;
  c_parser_consume_pragma (parser);

  தேர்வு (p_kind)
    {
    நிலை PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, உண்மை);
      திரும்பு;
    நிலை PRAGMA_OACC_CACHE:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      நிறுத்து;
    நிலை PRAGMA_OACC_DATA:
      stmt = c_parser_oacc_data (loc, parser, if_p);
      நிறுத்து;
    நிலை PRAGMA_OACC_HOST_DATA:
      stmt = c_parser_oacc_host_data (loc, parser, if_p);
      நிறுத்து;
    நிலை PRAGMA_OACC_KERNELS:
    நிலை PRAGMA_OACC_PARALLEL:
    நிலை PRAGMA_OACC_SERIAL:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_kind, p_name, if_p);
      நிறுத்து;
    நிலை PRAGMA_OACC_LOOP:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, mask, வெற்று, if_p);
      நிறுத்து;
    நிலை PRAGMA_OACC_WAIT:
      strcpy (p_name, "#pragma wait");
      stmt = c_parser_oacc_wait (loc, parser, p_name);
      நிறுத்து;
    நிலை PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (loc, parser, பொய்);
      திரும்பு;
    நிலை PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (loc, parser, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_DISTRIBUTE:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_distribute (loc, parser, p_name, mask, வெற்று, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_FOR:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, mask, வெற்று, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_LOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, mask, வெற்று, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_MASKED:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, mask, வெற்று, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_MASTER:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, mask, வெற்று, if_p,
				  UNKNOWN_LOCATION);
      நிறுத்து;
    நிலை PRAGMA_OMP_PARALLEL:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, mask, வெற்று, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_SECTIONS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, mask, வெற்று);
      நிறுத்து;
    நிலை PRAGMA_OMP_SIMD:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, mask, வெற்று, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (loc, parser, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_TASK:
      stmt = c_parser_omp_task (loc, parser, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_TASKGROUP:
      stmt = c_parser_omp_taskgroup (loc, parser, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_TASKLOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_taskloop (loc, parser, p_name, mask, வெற்று, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_TEAMS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, mask, வெற்று, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_ASSUME:
      c_parser_omp_assume (parser, if_p);
      திரும்பு;
    நிலை PRAGMA_OMP_TILE:
      stmt = c_parser_omp_tile (loc, parser, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_UNROLL:
      stmt = c_parser_omp_unroll (loc, parser, if_p);
      நிறுத்து;
    நிலை PRAGMA_OMP_DISPATCH:
      stmt = c_parser_omp_dispatch (loc, parser);
      நிறுத்து;
    இயல்பு:
      gcc_unreachable ();
    }

  எனில் (stmt && stmt != error_mark_முனை)
    gcc_assert (கோவை_LOCATION (stmt) != UNKNOWN_LOCATION);
}

/* OpenMP 6.0:
   # pragma omp groupprivate (variable-list) [device_type(...)]  */

#define OMP_GROUPPRIVATE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE) )

நிலையான வெறுமை
c_parser_omp_groupprivate (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  மரம் vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, வெற்று);
  மரம் clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_MASK,
					   "#pragma omp groupprivate");
  /* TODO: Implies 'declare target local' with specified device_type, check for
     conflicts.  Check for other restrictions.  */
  (வெறுமை) vars;
  (வெறுமை) clauses;
  sorry_at (loc, "%<omp groupprivate%>");
}

/* OpenMP 2.5:
   # pragma omp threadprivate (variable-list) */

நிலையான வெறுமை
c_parser_omp_threadprivate (c_parser *parser)
{
  மரம் vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, வெற்று);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  க்கு (t = vars; t; t = மரம்_CHAIN (t))
    {
      மரம் v = மரம்_PURPOSE (t);
      loc = கோவை_LOCATION (மரம்_மதிப்பு (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      எனில் (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      இல்லையெனில் எனில் (மரம்_USED (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      இல்லையெனில் எனில் (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      இல்லையெனில் எனில் (மரம்_TYPE (v) == error_mark_முனை)
	;
      இல்லையெனில் எனில் (! COMPLETE_TYPE_P (மரம்_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      இல்லையெனில்
	{
	  எனில் (! DECL_THREAD_LOCAL_P (v))
	    {
	      set_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      எனில் (DECL_RTL_SET_P (v))
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

நிலையான மரம்
c_parser_transaction_attributes (c_parser *parser)
{
  எனில் (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    திரும்பு c_parser_gnu_attributes (parser);

  எனில் (!c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
    திரும்பு NULL_மரம்;
  திரும்பு c_parser_std_attribute_specifier (parser, உண்மை);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

நிலையான மரம்
c_parser_transaction (c_parser *parser, எண்ணிக்கை rid keyword)
{
  unsigned முழு old_in = parser->in_transaction;
  unsigned முழு this_in = 1, new_in;
  location_t loc = c_parser_peek_token (parser)->location;
  மரம் stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  எனில் (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  இல்லையெனில்
    {
      attrs = c_parser_transaction_attributes (parser);
      எனில் (attrs)
	this_in |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_in = this_in | (old_in & TM_STMT_ATTR_OUTER);

  parser->in_transaction = new_in;
  stmt = c_parser_compound_statement (parser);
  parser->in_transaction = old_in;

  எனில் (flag_tm)
    stmt = c_finish_transaction (loc, stmt, this_in);
  இல்லையெனில்
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  திரும்பு stmt;
}

/* Parse a __transaction_atomic or __transaction_relaxed expression
   (GCC Extension).

   transaction-expression:
     __transaction_atomic ( expression )
     __transaction_relaxed ( expression )
*/

நிலையான கட்டமைப்பு c_கோவை
c_parser_transaction_expression (c_parser *parser, எண்ணிக்கை rid keyword)
{
  கட்டமைப்பு c_கோவை ret;
  unsigned முழு old_in = parser->in_transaction;
  unsigned முழு this_in = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  மரம் attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  எனில் (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  இல்லையெனில்
    {
      attrs = c_parser_transaction_attributes (parser);
      எனில் (attrs)
	this_in |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->in_transaction = this_in;
  matching_parens parens;
  எனில் (parens.require_open (parser))
    {
      மரம் கோவை = c_parser_expression (parser).மதிப்பு;
      ret.original_type = மரம்_TYPE (கோவை);
      ret.மதிப்பு = build1 (TRANSACTION_கோவை, ret.original_type, கோவை);
      எனில் (this_in & TM_STMT_ATTR_RELAXED)
	TRANSACTION_கோவை_RELAXED (ret.மதிப்பு) = 1;
      SET_கோவை_LOCATION (ret.மதிப்பு, loc);
      ret.original_code = TRANSACTION_கோவை;
      ret.m_decimal = 0;
      எனில் (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, வெற்று);
	  செல் error;
	}
    }
  இல்லையெனில்
    {
     error:
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = வெற்று;
    }
  parser->in_transaction = old_in;

  எனில் (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  set_c_கோவை_source_range (&ret, loc, loc);

  திரும்பு ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

நிலையான மரம்
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  மரம் attrs;
  தருக்க is_outer = பொய்;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_attributes (parser);
  எனில் (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  எனில் (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      செல் ret_error;
    }
  இல்லையெனில் எனில் (parser->in_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      செல் ret_error;
    }
  இல்லையெனில் எனில் (is_outer)
    {
      எனில் ((parser->in_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  செல் ret_error;
	}
    }
  இல்லையெனில் எனில் (parser->in_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      செல் ret_error;
    }

  திரும்பு add_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  திரும்பு build1 (NOP_கோவை, void_type_முனை, error_mark_முனை);
}

/* Parse a single source file.  */

வெறுமை
c_parse_file (வெறுமை)
{
  /* Use local storage to begin.  If the first token is a pragma, parse it.
     If it is #pragma GCC pch_preprocess, then this will load a PCH file
     which will cause garbage collection.  */
  c_parser tparser;

  memset (&tparser, 0, அளவு tparser);
  tparser.translate_strings_p = உண்மை;
  tparser.tokens = &tparser.tokens_buf[0];
  the_parser = &tparser;

  எனில் (c_parser_peek_token (&tparser)->pragma_kind == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  இல்லையெனில்
    c_common_no_more_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  எனில் (tparser.tokens == &tparser.tokens_buf[0])
    the_parser->tokens = &the_parser->tokens_buf[0];

  /* Initialize EH, if we've been told to do so.  */
  எனில் (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = வெற்று;
}

வெறுமை
c_init_preprocess (வெறுமை)
{
  /* Create a parser for use by pragma_lex during preprocessing.  */
  the_parser = ggc_alloc<c_parser> ();
  memset (the_parser, 0, அளவு (c_parser));
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
c_parser_parse_rtl_body (c_parser *parser, எழுத்து *start_with_pass)
{
  எனில் (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      விடுவி (start_with_pass);
      திரும்பு c_parser_peek_token (parser)->location;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  முழு இலக்கம்_open_braces = 1;
  போது (1)
    {
      தேர்வு (c_parser_peek_token (parser)->type)
	{
	நிலை CPP_OPEN_BRACE:
	  இலக்கம்_open_braces++;
	  நிறுத்து;
	நிலை CPP_CLOSE_BRACE:
	  எனில் (--இலக்கம்_open_braces == 0)
	    செல் found_closing_brace;
	  நிறுத்து;
	நிலை CPP_EOF:
	  error_at (start_loc, "no closing brace");
	  விடுவி (start_with_pass);
	  திரும்பு c_parser_peek_token (parser)->location;
	இயல்பு:
	  நிறுத்து;
	}
      c_parser_consume_token (parser);
    }

 found_closing_brace:
  /* At the closing brace; record its location.  */
  location_t end_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  எனில் (!read_rtl_function_body_from_file_range (start_loc, end_loc))
    {
      விடுவி (start_with_pass);
      திரும்பு end_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  run_rtl_passes (start_with_pass);
  திரும்பு end_loc;
}

#அந்தர்பாவ "gt-c-c-parser.h"
