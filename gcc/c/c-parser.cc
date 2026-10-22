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

#অন্তর্ভাব "config.h"
#define INCLUDE_STRING
#অন্তর্ভাব "system.h"
#অন্তর্ভাব "coretypes.h"
#অন্তর্ভাব "target.h"
#অন্তর্ভাব "function.h"
#অন্তর্ভাব "c-tree.h"
#অন্তর্ভাব "timevar.h"
#অন্তর্ভাব "stringpool.h"
#অন্তর্ভাব "cgraph.h"
#অন্তর্ভাব "attribs.h"
#অন্তর্ভাব "stor-layout.h"
#অন্তর্ভাব "varasm.h"
#অন্তর্ভাব "trans-mem.h"
#অন্তর্ভাব "c-family/c-pragma.h"
#অন্তর্ভাব "c-lang.h"
#অন্তর্ভাব "c-family/c-objc.h"
#অন্তর্ভাব "plugin.h"
#অন্তর্ভাব "omp-general.h"
#অন্তর্ভাব "omp-offload.h"
#অন্তর্ভাব "builtins.h"
#অন্তর্ভাব "gomp-constants.h"
#অন্তর্ভাব "c-family/c-indentation.h"
#অন্তর্ভাব "gimple-expr.h"
#অন্তর্ভাব "context.h"
#অন্তর্ভাব "gcc-rich-location.h"
#অন্তর্ভাব "c-parser.h"
#অন্তর্ভাব "gimple-parser.h"
#অন্তর্ভাব "read-rtl-function.h"
#অন্তর্ভাব "run-rtl-passes.h"
#অন্তর্ভাব "intl.h"
#অন্তর্ভাব "c-family/name-hint.h"
#অন্তর্ভাব "tree-iterator.h"
#অন্তর্ভাব "tree-pretty-print.h"
#অন্তর্ভাব "memmodel.h"
#অন্তর্ভাব "c-family/known-headers.h"
#অন্তর্ভাব "bitmap.h"
#অন্তর্ভাব "analyzer/analyzer-language.h"
#অন্তর্ভাব "toplev.h"
#অন্তর্ভাব "asan.h"
#অন্তর্ভাব "c-family/c-ubsan.h"
#অন্তর্ভাব "gcc-urlifier.h"

/* We need to walk over decls with incomplete struct/union/enum types
   after parsing the whole translation unit.
   In finish_decl(), if the decl is static, has incomplete
   struct/union/enum type, it is appended to incomplete_record_decls.
   In c_parser_translation_unit(), we iterate over incomplete_record_decls
   and report error if any of the decls are still incomplete.  */

vec<বৃক্ষ> incomplete_record_decls;

শূন্য
set_c_রাশিমালা_source_range (c_রাশিমালা *রাশিমালা,
			 location_t start, location_t finish)
{
  রাশিমালা->src_range.m_start = start;
  রাশিমালা->src_range.m_finish = finish;
  যদি (রাশিমালা->মান)
    set_source_range (রাশিমালা->মান, start, finish);
}

শূন্য
set_c_রাশিমালা_source_range (c_রাশিমালা *রাশিমালা,
			 source_range src_range)
{
  রাশিমালা->src_range = src_range;
  যদি (রাশিমালা->মান)
    set_source_range (রাশিমালা->মান, src_range);
}


/* Initialization routine for this file.  */

শূন্য
c_parse_init (শূন্য)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  unsigned পূর্ণাঙ্ক i;
  বৃক্ষ id;
  পূর্ণাঙ্ক mask = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  mask |= D_CXXONLY;
  যদি (!flag_isoc99)
    mask |= D_C99;
  যদি (!flag_isoc23)
    mask |= D_C23;
  যদি (flag_no_asm)
    {
      mask |= D_ASM | D_EXT;
      যদি (!flag_isoc99)
	mask |= D_EXT89;
      যদি (!flag_isoc23)
	mask |= D_EXT11;
    }
  যদি (!c_dialect_objc ())
    mask |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<বৃক্ষ> ((পূর্ণাঙ্ক) RID_MAX);
  প্রতি (i = 0; i < অঙ্ক_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      যদি (c_common_reswords[i].disable & mask)
	{
	  যদি (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].word);
	      C_SET_RID_CODE (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_WORD (id) = 1;
	    }
	  অনুবর্ত;
	}

      id = get_identifier (c_common_reswords[i].word);
      C_SET_RID_CODE (id, c_common_reswords[i].rid);
      C_IS_RESERVED_WORD (id) = 1;
      ridpointers [(পূর্ণাঙ্ক) c_common_reswords[i].rid] = id;
    }

  প্রতি (i = 0; i < অঙ্ক_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      বর্ণ name[50];
      sprintf (name, "__int%d", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;

      sprintf (name, "__int%d__", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;
    }

  যদি (flag_openmp)
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
সংরচনা GTY(()) c_parser {
  /* The look-ahead tokens.  */
  c_token * GTY((skip)) tokens;
  /* Buffer for look-ahead tokens.  */
  c_token tokens_buf[4];
  /* How many look-ahead tokens are available (0 - 4, or
     more if parsing from pre-lexed tokens).  */
  unsigned পূর্ণাঙ্ক tokens_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_tokens;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  unsigned পূর্ণাঙ্ক raw_tokens_used;
  /* True if a syntax error is being recovered from; false otherwise.
     c_parser_error sets this flag.  It should clear this flag when
     enough tokens have been consumed to recover from the error.  */
  তার্কিক error : 1;
  /* True if we're processing a pragma, and shouldn't automatically
     consume CPP_PRAGMA_EOL.  */
  তার্কিক in_pragma : 1;
  /* True if we're parsing the outermost block of an if statement.  */
  তার্কিক in_if_block : 1;
  /* True if we want to lex a translated, joined string (for an
     initial #pragma pch_preprocess).  Otherwise the parser is
     responsible for concatenating strings and translating to the
     execution character set as needed.  */
  তার্কিক lex_joined_string : 1;
  /* True if, when the parser is concatenating string literals, it
     should translate them to the execution character set (false
     inside attributes).  */
  তার্কিক translate_strings_p : 1;

  /* Objective-C specific parser/lexer information.  */

  /* True if we are in a context where the Objective-C "PQ" keywords
     are considered keywords.  */
  তার্কিক objc_pq_context : 1;
  /* True if we are parsing a (potential) Objective-C foreach
     statement.  This is set to true after we parsed 'for (' and while
     we wait for 'in' or ';' to decide if it's a standard C for loop or an
     Objective-C foreach loop.  */
  তার্কিক objc_could_be_foreach_context : 1;
  /* The following flag is needed to contextualize Objective-C lexical
     analysis.  In some cases (e.g., 'int NSObject;'), it is
     undesirable to bind an identifier to an Objective-C class, even
     if a class with that name exists.  */
  তার্কিক objc_need_raw_identifier : 1;
  /* Nonzero if we're processing a __transaction statement.  The value
     is 1 | TM_STMT_ATTR_*.  */
  unsigned পূর্ণাঙ্ক in_transaction : 4;
  /* True if we are in a context where the Objective-C "Property attribute"
     keywords are valid.  */
  তার্কিক objc_property_attr_context : 1;

  /* Whether we have just seen/constructed a string-literal.  Set when
     returning a string-literal from c_parser_string_literal.  Reset
     in consume_token.  Useful when we get a parse error and see an
     unknown token, which could have been a string-literal constant
     macro.  */
  তার্কিক seen_string_literal : 1;

  /* TRUE if omp::directive, omp::decl or omp::sequence attributes may not
     appear.  */
  তার্কিক omp_attrs_forbidden_p : 1;

  /* Location of the last consumed token.  */
  location_t last_token_location;

  /* Holds state for parsing collapsed OMP_FOR loops.  Managed by
     c_parser_omp_for_loop.  */
  সংরচনা omp_for_parse_data * GTY((skip)) omp_for_parse_state;

  /* If we're in the context of OpenMP directives written as C23
     attributes turned into pragma, the tokens field is temporarily
     redirected.  This holds data needed to restore state afterwards.
     It's NULL otherwise.  */
  সংরচনা omp_attribute_pragma_state *in_omp_attribute_pragma;

  /* Set for omp::decl attribute parsing to the decl to which it
     appertains.  */
  বৃক্ষ in_omp_decl_attribute;

  /* Non-null only when parsing the body of an OpenMP metadirective.
     Managed by c_parser_omp_metadirective.  */
  সংরচনা omp_metadirective_parse_data * GTY((skip))
    omp_metadirective_state;
};

/* Holds data needed to restore the token stream to its previous state
   after parsing an OpenMP attribute-syntax pragma.  */
সংরচনা GTY(()) omp_attribute_pragma_state
{
  vec<c_token, va_gc> *token_vec;
  c_token * GTY((skip)) save_tokens;
  unsigned পূর্ণাঙ্ক save_tokens_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
সংরচনা GTY(()) omp_begin_declare_variant_map_entry {
  বৃক্ষ variant;		/* The variant decl.  */
  বৃক্ষ id;		/* Name of base function.  */
  বৃক্ষ ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_entry, va_gc> *omp_begin_declare_variant_map;

স্থির বৃক্ষ omp_start_variant_function (c_declarator *, বৃক্ষ);
স্থির শূন্য omp_finish_variant_function (বৃক্ষ, বৃক্ষ, বৃক্ষ);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_tokens_buf (c_parser *parser, unsigned n)
{
  প্রত্যাগম &parser->tokens_buf[n];
}

/* Return the error state of PARSER.  */

তার্কিক
c_parser_error (c_parser *parser)
{
  প্রত্যাগম parser->error;
}

/* Set the error state of PARSER to ERR.  */

শূন্য
c_parser_set_error (c_parser *parser, তার্কিক err)
{
  parser->error = err;
}


/* The actual parser and external interface.  ??? Does this need to be
   garbage-collected?  */

স্থির GTY (()) c_parser *the_parser;

/* Read in and lex a single token, storing it in *TOKEN.  If RAW,
   context-sensitive postprocessing of the token is not done.  */

স্থির শূন্য
c_lex_one_token (c_parser *parser, c_token *token, তার্কিক raw = অসত্য)
{
  timevar_ঠেলো (TV_LEX);

  যদি (raw || vec_safe_length (parser->raw_tokens) == 0)
    {
      token->type = c_lex_with_flags (&token->মান, &token->location,
				      &token->flags,
				      (parser->lex_joined_string
				       ? 0 : C_LEX_STRING_NO_JOIN));
      token->id_kind = C_ID_NONE;
      token->keyword = RID_MAX;
      token->pragma_kind = PRAGMA_NONE;
    }
  অন্যথা
    {
      /* Use a token previously lexed as a raw look-ahead token, and
	 complete the processing on it.  */
      *token = (*parser->raw_tokens)[parser->raw_tokens_used];
      ++parser->raw_tokens_used;
      যদি (parser->raw_tokens_used == vec_safe_length (parser->raw_tokens))
	{
	  vec_free (parser->raw_tokens);
	  parser->raw_tokens_used = 0;
	}
    }

  যদি (raw)
    গচ্ছ out;

  বিকল্প (token->type)
    {
    পক্ষ CPP_NAME:
      {
	বৃক্ষ decl;

	তার্কিক objc_force_identifier = parser->objc_need_raw_identifier;
	যদি (c_dialect_objc ())
	  parser->objc_need_raw_identifier = অসত্য;

	যদি (C_IS_RESERVED_WORD (token->মান))
	  {
	    গণনা rid rid_code = C_RID_CODE (token->মান);

	    যদি (rid_code == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->মান);
	      }
	    অন্যথা যদি (rid_code >= RID_FIRST_ADDR_SPACE
		     && rid_code <= RID_LAST_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_code - RID_FIRST_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_kind = C_ID_ADDRSPACE;
		token->keyword = rid_code;
		ভঙ্গ;
	      }
	    অন্যথা যদি (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		যদি (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    ভঙ্গ;
		  }
		অন্যথা যদি (parser->objc_could_be_foreach_context
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
		    ভঙ্গ;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    অন্যথা যদি (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		যদি (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    ভঙ্গ;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    অন্যথা যদি (c_dialect_objc ()
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
	    অন্যথা
	      {
		token->type = CPP_KEYWORD;
		token->keyword = rid_code;
		ভঙ্গ;
	      }
	  }

	decl = lookup_name (token->মান);
	যদি (decl)
	  {
	    যদি (বৃক্ষ_CODE (decl) == TYPE_DECL)
	      {
		token->id_kind = C_ID_TYPENAME;
		ভঙ্গ;
	      }
	  }
	অন্যথা যদি (c_dialect_objc ())
	  {
	    বৃক্ষ objc_interface_decl = objc_is_class_name (token->মান);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    যদি (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->মান = objc_interface_decl;
		token->id_kind = C_ID_CLASSNAME;
		ভঙ্গ;
	      }
	  }
        token->id_kind = C_ID_ID;
      }
      ভঙ্গ;
    পক্ষ CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      বিকল্প (C_RID_CODE (token->মান))
	{
	  /* Replace 'class' with '@class', 'private' with '@private',
	     etc.  This prevents confusion with the C++ keyword
	     'class', and makes the tokens consistent with other
	     Objective-C 'AT' keywords.  For example '@class' is
	     reported as RID_AT_CLASS which is consistent with
	     '@synchronized', which is reported as
	     RID_AT_SYNCHRONIZED.
	  */
	পক্ষ RID_CLASS:     token->keyword = RID_AT_CLASS; ভঙ্গ;
	পক্ষ RID_PRIVATE:   token->keyword = RID_AT_PRIVATE; ভঙ্গ;
	পক্ষ RID_PROTECTED: token->keyword = RID_AT_PROTECTED; ভঙ্গ;
	পক্ষ RID_PUBLIC:    token->keyword = RID_AT_PUBLIC; ভঙ্গ;
	পক্ষ RID_THROW:     token->keyword = RID_AT_THROW; ভঙ্গ;
	পক্ষ RID_TRY:       token->keyword = RID_AT_TRY; ভঙ্গ;
	পক্ষ RID_CATCH:     token->keyword = RID_AT_CATCH; ভঙ্গ;
	পক্ষ RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; ভঙ্গ;
	স্বভাব:            token->keyword = C_RID_CODE (token->মান);
	}
      ভঙ্গ;
    পক্ষ CPP_COLON:
    পক্ষ CPP_COMMA:
    পক্ষ CPP_CLOSE_PAREN:
    পক্ষ CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      যদি (c_dialect_objc ())
	parser->objc_need_raw_identifier = অসত্য;
      ভঙ্গ;
    পক্ষ CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_kind = (গণনা pragma_kind) বৃক্ষ_INT_CST_নিচের (token->মান);
      token->মান = রিক্ত;
      ভঙ্গ;
    স্বভাব:
      ভঙ্গ;
    }
 out:
  timevar_বের_করো (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  যদি (parser->tokens_avail == 0)
    {
      c_lex_one_token (parser, &parser->tokens[0]);
      parser->tokens_avail = 1;
    }
  প্রত্যাগম &parser->tokens[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  যদি (parser->tokens_avail >= 2)
    প্রত্যাগম &parser->tokens[1];
  gcc_assert (parser->tokens_avail == 1);
  gcc_assert (parser->tokens[0].type != CPP_EOF);
  gcc_assert (parser->tokens[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->tokens[1]);
  parser->tokens_avail = 2;
  প্রত্যাগম &parser->tokens[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, unsigned পূর্ণাঙ্ক n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  যদি (parser->tokens_avail >= n)
    প্রত্যাগম &parser->tokens[n - 1];
  gcc_assert (parser->tokens_avail == n - 1);
  c_lex_one_token (parser, &parser->tokens[n - 1]);
  parser->tokens_avail = n;
  প্রত্যাগম &parser->tokens[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, unsigned পূর্ণাঙ্ক n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  যদি (parser->tokens_avail >= n)
    প্রত্যাগম &parser->tokens[n - 1];
  unsigned পূর্ণাঙ্ক raw_len = vec_safe_length (parser->raw_tokens);
  unsigned পূর্ণাঙ্ক raw_avail
    = parser->tokens_avail + raw_len - parser->raw_tokens_used;
  gcc_assert (raw_avail >= n - 1);
  যদি (raw_avail >= n)
    প্রত্যাগম &(*parser->raw_tokens)[parser->raw_tokens_used
				  + n - 1 - parser->tokens_avail];
  vec_safe_reserve (parser->raw_tokens, 1);
  parser->raw_tokens->quick_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_tokens)[raw_len], সত্য);
  প্রত্যাগম &(*parser->raw_tokens)[raw_len];
}

তার্কিক
c_keyword_starts_typename (গণনা rid keyword)
{
  বিকল্প (keyword)
    {
    পক্ষ RID_UNSIGNED:
    পক্ষ RID_LONG:
    পক্ষ RID_SHORT:
    পক্ষ RID_SIGNED:
    পক্ষ RID_COMPLEX:
    পক্ষ RID_INT:
    পক্ষ RID_CHAR:
    পক্ষ RID_FLOAT:
    পক্ষ RID_DOUBLE:
    পক্ষ RID_VOID:
    পক্ষ RID_DFLOAT32:
    পক্ষ RID_DFLOAT64:
    পক্ষ RID_DFLOAT128:
    পক্ষ RID_DFLOAT64X:
    CASE_RID_FLOATN_NX:
    পক্ষ RID_BOOL:
    পক্ষ RID_BITINT:
    পক্ষ RID_ENUM:
    পক্ষ RID_STRUCT:
    পক্ষ RID_UNION:
    পক্ষ RID_TYPEOF:
    পক্ষ RID_TYPEOF_UNQUAL:
    পক্ষ RID_CONST:
    পক্ষ RID_ATOMIC:
    পক্ষ RID_VOLATILE:
    পক্ষ RID_RESTRICT:
    পক্ষ RID_ATTRIBUTE:
    পক্ষ RID_FRACT:
    পক্ষ RID_ACCUM:
    পক্ষ RID_SAT:
    পক্ষ RID_AUTO_TYPE:
    পক্ষ RID_ALIGNAS:
      প্রত্যাগম সত্য;
    স্বভাব:
      যদি (keyword >= RID_FIRST_INT_N
	  && keyword < RID_FIRST_INT_N + অঙ্ক_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_FIRST_INT_N])
	প্রত্যাগম সত্য;
      প্রত্যাগম অসত্য;
    }
}

/* Return true if TOKEN can start a type name,
   false otherwise.  */
তার্কিক
c_token_starts_typename (c_token *token)
{
  বিকল্প (token->type)
    {
    পক্ষ CPP_NAME:
      বিকল্প (token->id_kind)
	{
	পক্ষ C_ID_ID:
	  প্রত্যাগম অসত্য;
	পক্ষ C_ID_ADDRSPACE:
	  প্রত্যাগম সত্য;
	পক্ষ C_ID_TYPENAME:
	  প্রত্যাগম সত্য;
	পক্ষ C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  প্রত্যাগম সত্য;
	স্বভাব:
	  gcc_unreachable ();
	}
    পক্ষ CPP_KEYWORD:
      প্রত্যাগম c_keyword_starts_typename (token->keyword);
    পক্ষ CPP_LESS:
      যদি (c_dialect_objc ())
	প্রত্যাগম সত্য;
      প্রত্যাগম অসত্য;
    স্বভাব:
      প্রত্যাগম অসত্য;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

স্থির অন্তঃস্থ তার্কিক
c_parser_next_tokens_start_typename (c_parser *parser, গণনা c_lookahead_kind la,
				     unsigned পূর্ণাঙ্ক n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  যদি (c_token_starts_typename (token))
    প্রত্যাগম সত্য;

  /* Try a bit harder to detect an unknown typename.  */
  যদি (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_kind == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->মান))
    প্রত্যাগম সত্য;

  প্রত্যাগম অসত্য;
}

/* Return true if TOKEN, after an open parenthesis, can start a
   compound literal (either a storage class specifier allowed in that
   context, or a type name), false otherwise.  */
স্থির তার্কিক
c_token_starts_compound_literal (c_token *token)
{
  বিকল্প (token->type)
    {
    পক্ষ CPP_KEYWORD:
      বিকল্প (token->keyword)
	{
	পক্ষ RID_CONSTEXPR:
	পক্ষ RID_REGISTER:
	পক্ষ RID_STATIC:
	পক্ষ RID_THREAD:
	  প্রত্যাগম সত্য;
	স্বভাব:
	  ভঙ্গ;
	}
      /* Fall through.  */
    স্বভাব:
      প্রত্যাগম c_token_starts_typename (token);
    }
}

/* Return true if TOKEN is a type qualifier, false otherwise.  */
স্থির তার্কিক
c_token_is_qualifier (c_token *token)
{
  বিকল্প (token->type)
    {
    পক্ষ CPP_NAME:
      বিকল্প (token->id_kind)
	{
	পক্ষ C_ID_ADDRSPACE:
	  প্রত্যাগম সত্য;
	স্বভাব:
	  প্রত্যাগম অসত্য;
	}
    পক্ষ CPP_KEYWORD:
      বিকল্প (token->keyword)
	{
	পক্ষ RID_CONST:
	পক্ষ RID_VOLATILE:
	পক্ষ RID_RESTRICT:
	পক্ষ RID_ATTRIBUTE:
	পক্ষ RID_ATOMIC:
	  প্রত্যাগম সত্য;
	স্বভাব:
	  প্রত্যাগম অসত্য;
	}
    পক্ষ CPP_LESS:
      প্রত্যাগম অসত্য;
    স্বভাব:
      gcc_unreachable ();
    }
}

/* Return true if the next token from PARSER is a type qualifier,
   false otherwise.  */
স্থির অন্তঃস্থ তার্কিক
c_parser_next_token_is_qualifier (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  প্রত্যাগম c_token_is_qualifier (token);
}

/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes), false otherwise.  */
স্থির তার্কিক
c_token_starts_declspecs (c_token *token)
{
  বিকল্প (token->type)
    {
    পক্ষ CPP_NAME:
      বিকল্প (token->id_kind)
	{
	পক্ষ C_ID_ID:
	  প্রত্যাগম অসত্য;
	পক্ষ C_ID_ADDRSPACE:
	  প্রত্যাগম সত্য;
	পক্ষ C_ID_TYPENAME:
	  প্রত্যাগম সত্য;
	পক্ষ C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  প্রত্যাগম সত্য;
	স্বভাব:
	  gcc_unreachable ();
	}
    পক্ষ CPP_KEYWORD:
      বিকল্প (token->keyword)
	{
	পক্ষ RID_STATIC:
	পক্ষ RID_EXTERN:
	পক্ষ RID_REGISTER:
	পক্ষ RID_TYPEDEF:
	পক্ষ RID_INLINE:
	পক্ষ RID_NORETURN:
	পক্ষ RID_AUTO:
	পক্ষ RID_THREAD:
	পক্ষ RID_UNSIGNED:
	পক্ষ RID_LONG:
	পক্ষ RID_SHORT:
	পক্ষ RID_SIGNED:
	পক্ষ RID_COMPLEX:
	পক্ষ RID_INT:
	পক্ষ RID_CHAR:
	পক্ষ RID_FLOAT:
	পক্ষ RID_DOUBLE:
	পক্ষ RID_VOID:
	পক্ষ RID_DFLOAT32:
	পক্ষ RID_DFLOAT64:
	পক্ষ RID_DFLOAT128:
	পক্ষ RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	পক্ষ RID_BOOL:
	পক্ষ RID_BITINT:
	পক্ষ RID_ENUM:
	পক্ষ RID_STRUCT:
	পক্ষ RID_UNION:
	পক্ষ RID_TYPEOF:
	পক্ষ RID_TYPEOF_UNQUAL:
	পক্ষ RID_CONST:
	পক্ষ RID_VOLATILE:
	পক্ষ RID_RESTRICT:
	পক্ষ RID_ATTRIBUTE:
	পক্ষ RID_FRACT:
	পক্ষ RID_ACCUM:
	পক্ষ RID_SAT:
	পক্ষ RID_ALIGNAS:
	পক্ষ RID_ATOMIC:
	পক্ষ RID_AUTO_TYPE:
	পক্ষ RID_CONSTEXPR:
	  প্রত্যাগম সত্য;
	স্বভাব:
	  যদি (token->keyword >= RID_FIRST_INT_N
	      && token->keyword < RID_FIRST_INT_N + অঙ্ক_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_FIRST_INT_N])
	    প্রত্যাগম সত্য;
	  প্রত্যাগম অসত্য;
	}
    পক্ষ CPP_LESS:
      যদি (c_dialect_objc ())
	প্রত্যাগম সত্য;
      প্রত্যাগম অসত্য;
    স্বভাব:
      প্রত্যাগম অসত্য;
    }
}


/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes) or a static assertion, false
   otherwise.  */
স্থির তার্কিক
c_token_starts_declaration (c_token *token)
{
  যদি (c_token_starts_declspecs (token)
      || token->keyword == RID_STATIC_ASSERT)
    প্রত্যাগম সত্য;
  অন্যথা
    প্রত্যাগম অসত্য;
}

/* Return true if the next token from PARSER can start declaration
   specifiers (not including standard attributes), false
   otherwise.  */
তার্কিক
c_parser_next_token_starts_declspecs (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);

  /* In Objective-C, a classname normally starts a declspecs unless it
     is immediately followed by a dot.  In that case, it is the
     Objective-C 2.0 "dot-syntax" for class objects, ie, calls the
     setter/getter on the class.  c_token_starts_declspecs() can't
     differentiate between the two cases because it only checks the
     current token, so we have a special check here.  */
  যদি (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    প্রত্যাগম অসত্য;

  প্রত্যাগম c_token_starts_declspecs (token);
}

স্থির তার্কিক c_parser_check_balanced_raw_token_sequence (c_parser *,
							unsigned পূর্ণাঙ্ক *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
তার্কিক
c_parser_next_tokens_start_declaration (c_parser *parser, unsigned পূর্ণাঙ্ক n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  যদি (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_DOT)
    প্রত্যাগম অসত্য;

  /* Labels do not start declarations.  */
  যদি (token->type == CPP_NAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_COLON)
    প্রত্যাগম অসত্য;

  /* A static assertion is only a declaration if followed by a semicolon;
     otherwise, it may be an expression in C2Y.  */
  যদি (token->keyword == RID_STATIC_ASSERT
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_PAREN)
    {
      n += 2;
      যদি (!c_parser_check_balanced_raw_token_sequence (parser, &n)
	  || c_parser_peek_nth_token_raw (parser, n)->type != CPP_CLOSE_PAREN)
	/* Invalid static assertion syntax; treat as a declaration and report a
	   syntax error there.  */
	প্রত্যাগম সত্য;
      প্রত্যাগম c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  যদি (c_token_starts_declaration (token))
    প্রত্যাগম সত্য;

  যদি (c_parser_next_tokens_start_typename (parser, cla_nonabstract_decl, n))
    প্রত্যাগম সত্য;

  প্রত্যাগম অসত্য;
}

/* Consume the next token from PARSER.  */

শূন্য
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
  যদি (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  অন্যথা যদি (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      যদি (parser->tokens_avail >= 3)
        {
          parser->tokens[1] = parser->tokens[2];
          যদি (parser->tokens_avail >= 4)
            parser->tokens[2] = parser->tokens[3];
        }
    }
  parser->tokens_avail--;
  parser->seen_string_literal = অসত্য;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

স্থির শূন্য
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->in_pragma);
  gcc_assert (parser->tokens_avail >= 1);
  gcc_assert (parser->tokens[0].type == CPP_PRAGMA);
  যদি (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  অন্যথা যদি (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      যদি (parser->tokens_avail >= 3)
	parser->tokens[1] = parser->tokens[2];
    }
  parser->tokens_avail--;
  parser->in_pragma = সত্য;
}

/* Update the global input_location from TOKEN.  */
স্থির অন্তঃস্থ শূন্য
c_parser_set_source_position_from_token (c_token *token)
{
  যদি (token->type != CPP_EOF)
    {
      প্রবেশ_location = token->location;
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

স্থির তার্কিক
c_parser_peek_conflict_marker (c_parser *parser, গণনা cpp_ttype tok1_kind,
			       location_t *out_loc)
{
  c_token *token2 = c_parser_peek_2nd_token (parser);
  যদি (token2->type != tok1_kind)
    প্রত্যাগম অসত্য;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  যদি (token3->type != tok1_kind)
    প্রত্যাগম অসত্য;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  যদি (token4->type != conflict_marker_get_final_tok_kind (tok1_kind))
    প্রত্যাগম অসত্য;

  /* It must be at the start of the line.  */
  location_t start_loc = c_parser_peek_token (parser)->location;
  যদি (LOCATION_COLUMN (start_loc) != 1)
    প্রত্যাগম অসত্য;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t finish_loc = get_finish (token4->location);
  *out_loc = make_location (start_loc, start_loc, finish_loc);

  প্রত্যাগম সত্য;
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

স্থির তার্কিক
c_parser_error_richloc (c_parser *parser, ধ্রুব বর্ণ *gmsgid,
			rich_location *richloc)
{
  c_token *token = c_parser_peek_token (parser);
  যদি (parser->error)
    প্রত্যাগম অসত্য;
  parser->error = সত্য;
  যদি (!gmsgid)
    প্রত্যাগম অসত্য;

  /* If this is actually a conflict marker, report it as such.  */
  যদি (token->type == CPP_LSHIFT
      || token->type == CPP_RSHIFT
      || token->type == CPP_EQ_EQ)
    {
      location_t loc;
      যদি (c_parser_peek_conflict_marker (parser, token->type, &loc))
	{
	  error_at (loc, "version control conflict marker in file");
	  প্রত্যাগম সত্য;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_group d;
  name_hint h;
  যদি (parser->seen_string_literal && token->type == CPP_NAME)
    {
      বৃক্ষ name = token->মান;
      ধ্রুব বর্ণ *token_name = IDENTIFIER_POINTER (name);
      ধ্রুব বর্ণ *header_hint
	= get_c_stdlib_header_for_string_macro_name (token_name);
      যদি (header_hint != রিক্ত)
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
		 token->মান, /*flags=*/0, richloc);
  প্রত্যাগম সত্য;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

তার্কিক
c_parser_error (c_parser *parser, ধ্রুব বর্ণ *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_set_source_position_from_token (token);
  rich_location richloc (সারি_table, প্রবেশ_location);
  প্রত্যাগম c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

template <typename traits_t>
বর্গ token_pair
{
 সার্বজনিক:
  /* token_pair's ctor.  */
  token_pair () : m_open_loc (UNKNOWN_LOCATION) {}

  /* If the next token is the opening symbol for this pair, consume it and
     return true.
     Otherwise, issue an error and return false.
     In either case, record the location of the opening token.  */

  তার্কিক require_open (c_parser *parser)
  {
    c_token *token = c_parser_peek_token (parser);
    যদি (token)
      m_open_loc = token->location;

    প্রত্যাগম c_parser_require (parser, traits_t::open_token_type,
			     traits_t::open_gmsgid);
  }

  /* Consume the next token from PARSER, recording its location as
     that of the opening token within the pair.  */

  শূন্য consume_open (c_parser *parser)
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

  তার্কিক require_close (c_parser *parser) ধ্রুব
  {
    প্রত্যাগম c_parser_require (parser, traits_t::close_token_type,
			     traits_t::close_gmsgid, m_open_loc);
  }

  /* Like token_pair::require_close, except that tokens will be skipped
     until the desired token is found.  An error message is still produced
     if the next token is not as expected.  */

  শূন্য skip_until_found_close (c_parser *parser) ধ্রুব
  {
    c_parser_skip_until_found (parser, traits_t::close_token_type,
			       traits_t::close_gmsgid, m_open_loc);
  }

 গুপ্ত:
  location_t m_open_loc;
};

/* Traits for token_pair<T> for tracking matching pairs of parentheses.  */

সংরচনা matching_paren_traits
{
  স্থির ধ্রুব গণনা cpp_ttype open_token_type = CPP_OPEN_PAREN;
  স্থির ধ্রুব বর্ণ * ধ্রুব open_gmsgid;
  স্থির ধ্রুব গণনা cpp_ttype close_token_type = CPP_CLOSE_PAREN;
  স্থির ধ্রুব বর্ণ * ধ্রুব close_gmsgid;
};

ধ্রুব বর্ণ * ধ্রুব matching_paren_traits::open_gmsgid = "expected %<(%>";
ধ্রুব বর্ণ * ধ্রুব matching_paren_traits::close_gmsgid = "expected %<)%>";

/* "matching_parens" is a token_pair<T> class for tracking matching
   pairs of parentheses.  */

প্রকারনির্দেশ token_pair<matching_paren_traits> matching_parens;

/* Traits for token_pair<T> for tracking matching pairs of braces.  */

সংরচনা matching_brace_traits
{
  স্থির ধ্রুব গণনা cpp_ttype open_token_type = CPP_OPEN_BRACE;
  স্থির ধ্রুব বর্ণ * ধ্রুব open_gmsgid;
  স্থির ধ্রুব গণনা cpp_ttype close_token_type = CPP_CLOSE_BRACE;
  স্থির ধ্রুব বর্ণ * ধ্রুব close_gmsgid;
};

ধ্রুব বর্ণ * ধ্রুব matching_brace_traits::open_gmsgid = "expected %<{%>";
ধ্রুব বর্ণ * ধ্রুব matching_brace_traits::close_gmsgid = "expected %<}%>";

/* "matching_braces" is a token_pair<T> class for tracking matching
   pairs of braces.  */

প্রকারনির্দেশ token_pair<matching_brace_traits> matching_braces;

/* Get a description of the matching symbol to TYPE e.g. "(" for
   CPP_CLOSE_PAREN.  */

স্থির ধ্রুব বর্ণ *
get_matching_প্রতীক (গণনা cpp_ttype type)
{
  বিকল্প (type)
    {
    স্বভাব:
      gcc_unreachable ();
    পক্ষ CPP_CLOSE_PAREN:
      প্রত্যাগম "(";
    পক্ষ CPP_CLOSE_BRACE:
      প্রত্যাগম "{";
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

তার্কিক
c_parser_require (c_parser *parser,
		  গণনা cpp_ttype type,
		  ধ্রুব বর্ণ *msgid,
		  location_t matching_location,
		  তার্কিক type_is_unique)
{
  যদি (c_parser_next_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      প্রত্যাগম সত্য;
    }
  অন্যথা
    {
      location_t next_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (next_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      যদি (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->last_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      তার্কিক added_matching_location = অসত্য;
      যদি (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.add_location_if_nearby (*global_dc, matching_location);

      যদি (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	যদি (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_প্রতীক (type));

      প্রত্যাগম অসত্য;
    }
}

/* If the next token is the indicated keyword, consume it.  Otherwise,
   issue the error MSGID.  Returns true if found, false otherwise.  */

স্থির তার্কিক
c_parser_require_keyword (c_parser *parser,
			  গণনা rid keyword,
			  ধ্রুব বর্ণ *msgid)
{
  যদি (c_parser_next_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      প্রত্যাগম সত্য;
    }
  অন্যথা
    {
      c_parser_error (parser, msgid);
      প্রত্যাগম অসত্য;
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

শূন্য
c_parser_skip_until_found (c_parser *parser,
			   গণনা cpp_ttype type,
			   ধ্রুব বর্ণ *msgid,
			   location_t matching_location)
{
  unsigned nesting_depth = 0;

  যদি (c_parser_require (parser, type, msgid, matching_location))
    {
      যদি (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->in_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  যদি (token->type == CPP_EOF)
	    {
	      parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	      parser->tokens_avail
		= parser->in_omp_attribute_pragma->save_tokens_avail;
	      parser->in_omp_attribute_pragma = রিক্ত;
	    }
	}
      প্রত্যাগম;
    }

  /* Skip tokens until the desired token is found.  */
  যাবত্ (সত্য)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      যদি (token->type == type && !nesting_depth)
	{
	  c_parser_consume_token (parser);
	  যদি (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->in_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      যদি (token->type == CPP_EOF)
		{
		  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
		  parser->tokens_avail
		    = parser->in_omp_attribute_pragma->save_tokens_avail;
		  parser->in_omp_attribute_pragma = রিক্ত;
		}
	    }
	  ভঙ্গ;
	}

      /* If we've run out of tokens, stop.  */
      যদি (token->type == CPP_EOF)
	প্রত্যাগম;
      যদি (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	প্রত্যাগম;
      যদি (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      অন্যথা যদি (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  যদি (nesting_depth-- == 0)
	    ভঙ্গ;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = অসত্য;
}

/* Skip tokens until the end of a parameter is found, but do not
   consume the comma, semicolon or closing delimiter.  */

স্থির শূন্য
c_parser_skip_to_end_of_parameter (c_parser *parser)
{
  unsigned nesting_depth = 0;

  যাবত্ (সত্য)
    {
      c_token *token = c_parser_peek_token (parser);
      যদি ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_depth)
	ভঙ্গ;
      /* If we've run out of tokens, stop.  */
      যদি (token->type == CPP_EOF)
	প্রত্যাগম;
      যদি (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	প্রত্যাগম;
      যদি (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      অন্যথা যদি (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  যদি (nesting_depth-- == 0)
	    ভঙ্গ;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = অসত্য;
}

/* Skip tokens until a non-nested closing curly brace is the next
   token, or there are no more tokens. Return true in the first case,
   false otherwise.  */

স্থির তার্কিক
c_parser_skip_to_closing_brace (c_parser *parser)
{
  unsigned nesting_depth = 0;

  যাবত্ (সত্য)
    {
      c_token *token = c_parser_peek_token (parser);

      বিকল্প (token->type)
	{
	পক্ষ CPP_PRAGMA_EOL:
	  যদি (!parser->in_pragma)
	    ভঙ্গ;
	  /* FALLTHRU */
	পক্ষ CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  প্রত্যাগম অসত্য;

	পক্ষ CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  যদি (nesting_depth-- == 0)
	    প্রত্যাগম সত্য;
	  ভঙ্গ;

	পক্ষ CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  ভঙ্গ;

	স্বভাব:
	  ভঙ্গ;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Expect to be at the end of the pragma directive and consume an
   end of line marker.  */

স্থির শূন্য
c_parser_skip_to_pragma_eol (c_parser *parser, তার্কিক error_if_not_eol = সত্য)
{
  gcc_assert (parser->in_pragma);
  parser->in_pragma = অসত্য;

  যদি (error_if_not_eol && c_parser_peek_token (parser)->type != CPP_PRAGMA_EOL)
    c_parser_error (parser, "expected end of line");

  cpp_ttype token_type;
  কুরু
    {
      c_token *token = c_parser_peek_token (parser);
      token_type = token->type;
      যদি (token_type == CPP_EOF)
	ভঙ্গ;
      c_parser_consume_token (parser);
    }
  যাবত্ (token_type != CPP_PRAGMA_EOL);

  যদি (parser->in_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      যদি (token->type == CPP_EOF)
	{
	  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	  parser->tokens_avail
	    = parser->in_omp_attribute_pragma->save_tokens_avail;
	  parser->in_omp_attribute_pragma = রিক্ত;
	}
    }

  parser->error = অসত্য;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
স্থির শূন্য
c_parser_skip_to_pragma_omp_end_declare_variant (c_parser *parser)
{
  প্রতি (পূর্ণাঙ্ক depth = 0; depth >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      বিকল্প (token->type)
	{
	পক্ষ CPP_PRAGMA_EOL:
	  যদি (!parser->in_pragma)
	    ভঙ্গ;
	  /* FALLTHRU */
	পক্ষ CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  প্রত্যাগম;

	পক্ষ CPP_PRAGMA:
	  যদি ((token->pragma_kind == PRAGMA_OMP_BEGIN
	       || token->pragma_kind == PRAGMA_OMP_END)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      বৃক্ষ id1 = c_parser_peek_nth_token (parser, 2)->মান;
	      বৃক্ষ id2 = c_parser_peek_nth_token (parser, 3)->মান;
	      যদি (strcmp (IDENTIFIER_POINTER (id1), "declare") == 0
		  && strcmp (IDENTIFIER_POINTER (id2), "variant") == 0)
		{
		  যদি (token->pragma_kind == PRAGMA_OMP_BEGIN)
		    depth++;
		  অন্যথা
		    depth--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, অসত্য);
	  অনুবর্ত;

	স্বভাব:
	  ভঙ্গ;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Skip tokens until we have consumed an entire block, or until we
   have consumed a non-nested ';'.  */

স্থির শূন্য
c_parser_skip_to_end_of_block_or_statement (c_parser *parser,
					    তার্কিক metadirective_p = অসত্য)
{
  unsigned nesting_depth = 0;
  পূর্ণাঙ্ক bracket_depth = 0;
  তার্কিক save_error = parser->error;

  যাবত্ (সত্য)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      বিকল্প (token->type)
	{
	পক্ষ CPP_EOF:
	  প্রত্যাগম;

	পক্ষ CPP_PRAGMA_EOL:
	  যদি (parser->in_pragma)
	    প্রত্যাগম;
	  ভঙ্গ;

	পক্ষ CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  যদি (!nesting_depth && (!metadirective_p || bracket_depth <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      গচ্ছ finished;
	    }
	  ভঙ্গ;

	পক্ষ CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  যদি ((nesting_depth == 0 || --nesting_depth == 0)
	      && (!metadirective_p || bracket_depth <= 0))
	    {
	      c_parser_consume_token (parser);
	      গচ্ছ finished;
	    }
	  ভঙ্গ;

	পক্ষ CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  ভঙ্গ;

	পক্ষ CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  যদি (metadirective_p && nesting_depth == 0)
	    ++bracket_depth;
	  ভঙ্গ;

	পক্ষ CPP_CLOSE_PAREN:
	  যদি (metadirective_p && nesting_depth == 0)
	    --bracket_depth;
	  ভঙ্গ;

	পক্ষ CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, অসত্য);
	  parser->error = save_error;
	  অনুবর্ত;

	স্বভাব:
	  ভঙ্গ;
	}

      c_parser_consume_token (parser);
    }

 finished:
  parser->error = অসত্য;
}

/* CPP's options (initialized by c-opts.cc).  */
বাহ্য cpp_options *cpp_opts;

/* Save the warning flags which are controlled by __extension__.  */

স্থির অন্তঃস্থ পূর্ণাঙ্ক
disable_extension_diagnostics (শূন্য)
{
  পূর্ণাঙ্ক ret = (pedantic
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
  প্রত্যাগম ret;
}

/* Restore the warning flags which are controlled by __extension__.
   FLAGS is the return value from disable_extension_diagnostics.  */

স্থির অন্তঃস্থ শূন্য
restore_extension_diagnostics (পূর্ণাঙ্ক flags)
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
সংরচনা oacc_routine_data {
  তার্কিক error_seen; /* Set if error has been reported.  */
  তার্কিক fndecl_seen; /* Set if one fn decl/definition has been seen already.  */
  বৃক্ষ clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
স্থির বৃক্ষ objc_foreach_break_label, objc_foreach_continue_label;

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
সংরচনা omp_for_parse_data {
  গণনা বৃক্ষ_code code;
  বৃক্ষ declv, condv, incrv, initv;
  বৃক্ষ pre_body;
  বৃক্ষ bindings;
  পূর্ণাঙ্ক গুনতি;	/* Expected nesting depth.  */
  পূর্ণাঙ্ক depth;	/* Current nesting depth.  */
  location_t for_loc;
  তার্কিক ordered : 1;
  তার্কিক inscan : 1;
  তার্কিক want_nested_loop : 1;
  তার্কিক in_intervening_code : 1;
  তার্কিক saw_intervening_code: 1;
  তার্কিক perfect_nesting_fail : 1;
  তার্কিক fail : 1;
};

সংরচনা attr_state
{
  /* True if we parsed a musttail attribute for return.  */
  তার্কিক musttail_p;

  শূন্য reset () { musttail_p = অসত্য; }
};

স্থির তার্কিক c_parser_nth_token_starts_std_attributes (c_parser *,
						      unsigned পূর্ণাঙ্ক);
স্থির বৃক্ষ c_parser_std_attribute_specifier_sequence (c_parser *);
স্থির শূন্য c_parser_external_declaration (c_parser *);
স্থির শূন্য c_parser_asm_definition (c_parser *);
স্থির বৃক্ষ c_parser_declaration_or_fndef (c_parser *, তার্কিক, তার্কিক, তার্কিক,
					   তার্কিক, তার্কিক, তার্কিক, বৃক্ষ * = রিক্ত,
					   vec<c_token> * = রিক্ত,
					   তার্কিক have_attrs = অসত্য,
					   বৃক্ষ attrs = রিক্ত,
					   সংরচনা oacc_routine_data * = রিক্ত,
					   তার্কিক * = রিক্ত);
স্থির তার্কিক c_parser_handle_statement_omp_attributes (c_parser *, বৃক্ষ &,
						      তার্কিক *);
স্থির শূন্য c_parser_static_assert_declaration_no_semi (c_parser *);
স্থির শূন্য c_parser_static_assert_declaration (c_parser *);
স্থির সংরচনা c_typespec c_parser_enum_specifier (c_parser *);
স্থির সংরচনা c_typespec c_parser_struct_or_union_specifier (c_parser *);
স্থির বৃক্ষ c_parser_struct_declaration (c_parser *, বৃক্ষ *);
স্থির সংরচনা c_typespec c_parser_typeof_specifier (c_parser *);
স্থির বৃক্ষ c_parser_alignas_specifier (c_parser *);
স্থির সংরচনা c_declarator *c_parser_direct_declarator (c_parser *, তার্কিক,
							c_dtr_syn, তার্কিক *);
স্থির সংরচনা c_declarator *c_parser_direct_declarator_inner (c_parser *,
							      তার্কিক,
							      সংরচনা c_declarator *);
স্থির সংরচনা c_arg_info *c_parser_parms_declarator (c_parser *, তার্কিক, বৃক্ষ,
						     তার্কিক);
স্থির সংরচনা c_arg_info *c_parser_parms_list_declarator (c_parser *, বৃক্ষ,
							  বৃক্ষ, তার্কিক);
স্থির সংরচনা c_parm *c_parser_parameter_declaration (c_parser *, বৃক্ষ, তার্কিক);
স্থির বৃক্ষ c_parser_asm_string_literal (c_parser *);
স্থির বৃক্ষ c_parser_simple_asm_রাশিমালা (c_parser *);
স্থির বৃক্ষ c_parser_gnu_attributes (c_parser *);
স্থির সংরচনা c_রাশিমালা c_parser_initializer (c_parser *, বৃক্ষ);
স্থির সংরচনা c_রাশিমালা c_parser_braced_init (c_parser *, বৃক্ষ, তার্কিক,
					   সংরচনা obstack *, তার্কিক);
স্থির শূন্য c_parser_initelt (c_parser *, সংরচনা obstack *);
স্থির শূন্য c_parser_initval (c_parser *, সংরচনা c_রাশিমালা *,
			      সংরচনা obstack *);
স্থির বৃক্ষ c_parser_compound_statement (c_parser *, location_t * = রিক্ত);
স্থির location_t c_parser_compound_statement_nostart (c_parser *);
স্থির শূন্য c_parser_label (c_parser *, বৃক্ষ);
স্থির শূন্য c_parser_statement (c_parser *, তার্কিক *, location_t * = রিক্ত);
স্থির শূন্য c_parser_statement_after_labels (c_parser *, তার্কিক *, বৃক্ষ,
					     vec<বৃক্ষ> * = রিক্ত,
					     attr_state = {});
স্থির বৃক্ষ c_parser_c99_block_statement (c_parser *, তার্কিক *,
					  location_t * = রিক্ত);
স্থির শূন্য c_parser_if_statement (c_parser *, তার্কিক *, vec<বৃক্ষ> *);
স্থির শূন্য c_parser_switch_statement (c_parser *, তার্কিক *, বৃক্ষ);
স্থির শূন্য c_parser_while_statement (c_parser *, তার্কিক, unsigned short, তার্কিক,
				      তার্কিক *, বৃক্ষ);
স্থির শূন্য c_parser_do_statement (c_parser *, তার্কিক, unsigned short, তার্কিক,
				   বৃক্ষ);
স্থির শূন্য c_parser_for_statement (c_parser *, তার্কিক, unsigned short, তার্কিক,
				    তার্কিক *, বৃক্ষ);
স্থির বৃক্ষ c_parser_asm_statement (c_parser *);
স্থির বৃক্ষ c_parser_asm_operands (c_parser *);
স্থির বৃক্ষ c_parser_asm_goto_operands (c_parser *);
স্থির বৃক্ষ c_parser_asm_clobbers (c_parser *);
স্থির সংরচনা c_রাশিমালা c_parser_রাশিমালা_no_commas (c_parser *, সংরচনা c_রাশিমালা *,
					      বৃক্ষ = NULL_বৃক্ষ);
স্থির সংরচনা c_রাশিমালা c_parser_conditional_expression (c_parser *,
						      সংরচনা c_রাশিমালা *, বৃক্ষ);
স্থির সংরচনা c_রাশিমালা c_parser_দ্বিমিক_expression (c_parser *, সংরচনা c_রাশিমালা *,
						 বৃক্ষ);
স্থির সংরচনা c_রাশিমালা c_parser_cast_expression (c_parser *, সংরচনা c_রাশিমালা *);
স্থির সংরচনা c_রাশিমালা c_parser_unary_expression (c_parser *);
স্থির সংরচনা c_রাশিমালা c_parser_sizeof_or_countof_expression (c_parser *,
							    গণনা rid);
স্থির সংরচনা c_রাশিমালা c_parser_alignof_expression (c_parser *);
স্থির সংরচনা c_রাশিমালা c_parser_maxof_or_minof_expression (c_parser *, গণনা rid);
স্থির সংরচনা c_রাশিমালা c_parser_postfix_expression (c_parser *);
স্থির সংরচনা c_রাশিমালা c_parser_postfix_expression_after_paren_type (c_parser *,
								   সংরচনা c_declspecs *,
								   সংরচনা c_type_name *,
								   location_t);
স্থির সংরচনা c_রাশিমালা c_parser_postfix_expression_after_primary (c_parser *,
								location_t loc,
								সংরচনা c_রাশিমালা);
স্থির বৃক্ষ c_parser_transaction (c_parser *, গণনা rid);
স্থির সংরচনা c_রাশিমালা c_parser_transaction_expression (c_parser *, গণনা rid);
স্থির বৃক্ষ c_parser_transaction_cancel (c_parser *);
স্থির সংরচনা c_রাশিমালা c_parser_expression (c_parser *);
স্থির সংরচনা c_রাশিমালা c_parser_expression_conv (c_parser *);
স্থির vec<বৃক্ষ, va_gc> *c_parser_রাশিমালা_list (c_parser *, তার্কিক, তার্কিক,
					     vec<বৃক্ষ, va_gc> **, location_t *,
					     বৃক্ষ *, vec<location_t> *,
					     unsigned পূর্ণাঙ্ক * = রিক্ত);
স্থির সংরচনা c_রাশিমালা c_parser_has_attribute_expression (c_parser *);

স্থির শূন্য c_parser_oacc_declare (c_parser *);
স্থির শূন্য c_parser_oacc_enter_exit_data (c_parser *, তার্কিক);
স্থির শূন্য c_parser_oacc_update (c_parser *);
স্থির শূন্য c_parser_omp_construct (c_parser *, তার্কিক *);
স্থির শূন্য c_parser_omp_groupprivate (c_parser *);
স্থির শূন্য c_parser_omp_threadprivate (c_parser *);
স্থির শূন্য c_parser_omp_barrier (c_parser *);
স্থির শূন্য c_parser_omp_depobj (c_parser *);
স্থির শূন্য c_parser_omp_flush (c_parser *);
স্থির তার্কিক c_parser_omp_next_tokens_can_be_canon_loop (c_parser *,
							গণনা বৃক্ষ_code, তার্কিক);
স্থির বৃক্ষ c_parser_omp_loop_nest (c_parser *, তার্কিক *);
স্থির বৃক্ষ c_parser_omp_for_loop (location_t, c_parser *, গণনা বৃক্ষ_code,
				   বৃক্ষ, বৃক্ষ *, তার্কিক *);
স্থির শূন্য c_parser_omp_taskwait (c_parser *);
স্থির শূন্য c_parser_omp_taskyield (c_parser *);
স্থির শূন্য c_parser_omp_cancel (c_parser *);
স্থির শূন্য c_parser_omp_nothing (c_parser *);
স্থির শূন্য c_parser_omp_metadirective (c_parser *, তার্কিক *);

গণনা pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
স্থির তার্কিক c_parser_pragma (c_parser *, গণনা pragma_context, তার্কিক *, বৃক্ষ);
স্থির তার্কিক c_parser_omp_cancellation_point (c_parser *, গণনা pragma_context);
স্থির তার্কিক c_parser_omp_target (c_parser *, গণনা pragma_context, তার্কিক *);
স্থির শূন্য c_parser_omp_begin (c_parser *);
স্থির শূন্য c_parser_omp_end (c_parser *);
স্থির তার্কিক c_parser_omp_declare (c_parser *, গণনা pragma_context);
স্থির শূন্য c_parser_omp_requires (c_parser *);
স্থির তার্কিক c_parser_omp_error (c_parser *, গণনা pragma_context);
স্থির শূন্য c_parser_omp_assumption_clauses (c_parser *, তার্কিক);
স্থির শূন্য c_parser_omp_allocate (c_parser *);
স্থির শূন্য c_parser_omp_assumes (c_parser *);
স্থির তার্কিক c_parser_omp_ordered (c_parser *, গণনা pragma_context, তার্কিক *);
স্থির বৃক্ষ c_parser_omp_dispatch (location_t, c_parser *);
স্থির শূন্য c_parser_omp_interop (c_parser *);
স্থির শূন্য c_parser_oacc_routine (c_parser *, গণনা pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
স্থির শূন্য c_parser_objc_class_definition (c_parser *, বৃক্ষ);
স্থির শূন্য c_parser_objc_class_instance_variables (c_parser *);
স্থির শূন্য c_parser_objc_class_declaration (c_parser *);
স্থির শূন্য c_parser_objc_alias_declaration (c_parser *);
স্থির শূন্য c_parser_objc_protocol_definition (c_parser *, বৃক্ষ);
স্থির তার্কিক c_parser_objc_method_type (c_parser *);
স্থির শূন্য c_parser_objc_method_definition (c_parser *);
স্থির শূন্য c_parser_objc_methodprotolist (c_parser *);
স্থির শূন্য c_parser_objc_methodproto (c_parser *);
স্থির বৃক্ষ c_parser_objc_method_decl (c_parser *, তার্কিক, বৃক্ষ *, বৃক্ষ *);
স্থির বৃক্ষ c_parser_objc_type_name (c_parser *);
স্থির বৃক্ষ c_parser_objc_protocol_refs (c_parser *);
স্থির শূন্য c_parser_objc_try_catch_finally_statement (c_parser *);
স্থির শূন্য c_parser_objc_synchronized_statement (c_parser *);
স্থির বৃক্ষ c_parser_objc_selector (c_parser *);
স্থির বৃক্ষ c_parser_objc_selector_arg (c_parser *);
স্থির বৃক্ষ c_parser_objc_receiver (c_parser *);
স্থির বৃক্ষ c_parser_objc_message_args (c_parser *);
স্থির বৃক্ষ c_parser_objc_keywordexpr (c_parser *);
স্থির শূন্য c_parser_objc_at_property_declaration (c_parser *);
স্থির শূন্য c_parser_objc_at_synthesize_declaration (c_parser *);
স্থির শূন্য c_parser_objc_at_dynamic_declaration (c_parser *);
স্থির তার্কিক c_parser_objc_diagnose_bad_element_prefix
  (c_parser *, সংরচনা c_declspecs *);
স্থির location_t c_parser_parse_rtl_body (c_parser *, বর্ণ *);
স্থির বৃক্ষ c_parser_handle_musttail (c_parser *, বৃক্ষ, attr_state &);

#যদি ENABLE_ANALYZER

নামাকাশ ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

বর্গ c_translation_unit : সার্বজনিক translation_unit
{
সার্বজনিক:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  বৃক্ষ lookup_constant_by_id (বৃক্ষ id) ধ্রুব final override
  {
    /* Consider decls.  */
    যদি (বৃক্ষ decl = lookup_name (id))
      যদি (বৃক্ষ_CODE (decl) == CONST_DECL)
	যদি (বৃক্ষ মান = DECL_INITIAL (decl))
	  যদি (বৃক্ষ_CODE (মান) == INTEGER_CST)
	    প্রত্যাগম মান;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    যদি (cpp_macro_p (hashnode))
      যদি (বৃক্ষ মান = consider_macro (hashnode->মান.macro))
	প্রত্যাগম মান;

    প্রত্যাগম NULL_বৃক্ষ;
  }

  বৃক্ষ
  lookup_type_by_id (বৃক্ষ id) ধ্রুব final override
  {
    যদি (বৃক্ষ type_decl = lookup_name (id))
	যদি (বৃক্ষ_CODE (type_decl) == TYPE_DECL)
	  {
	    বৃক্ষ record_type = বৃক্ষ_TYPE (type_decl);
	    যদি (বৃক্ষ_CODE (record_type) == RECORD_TYPE)
	      প্রত্যাগম record_type;
	  }

    প্রত্যাগম NULL_বৃক্ষ;
  }

  বৃক্ষ
  lookup_global_var_by_id (বৃক্ষ id) ধ্রুব final override
  {
    যদি (বৃক্ষ var_decl = lookup_name (id))
      যদি (বৃক্ষ_CODE (var_decl) == VAR_DECL)
				প্রত্যাগম var_decl;

    প্রত্যাগম NULL_বৃক্ষ;
  }

গুপ্ত:
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
  বৃক্ষ consider_macro (cpp_macro *macro, পূর্ণাঙ্ক depth = 0) ধ্রুব
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (depth >= 0);

    যদি (macro->paramc > 0)
      প্রত্যাগম NULL_বৃক্ষ;
    যদি (macro->kind != cmk_macro)
      প্রত্যাগম NULL_বৃক্ষ;
    যদি (macro->গুনতি != 1)
      প্রত্যাগম NULL_বৃক্ষ;
    ধ্রুব cpp_token &tok = macro->exp.tokens[0];
    যদি (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	যদি (depth >= param_analyzer_max_macro_alias_depth)
	  প্রত্যাগম NULL_বৃক্ষ;

	cpp_hashnode *alias = tok.val.গ্রন্থি.গ্রন্থি;
	যদি (cpp_macro_p (alias))
	  প্রত্যাগম consider_macro (alias->মান.macro, depth + 1);

	/* Not a simple alias.  */
	প্রত্যাগম NULL_বৃক্ষ;
      }
    অন্যথা যদি (tok.type != CPP_সংখ্যা)
      প্রত্যাগম NULL_বৃক্ষ;

    cpp_reader *old_parse_in = parse_in;
    parse_in = cpp_create_reader (CLK_GNUC89, রিক্ত, সারি_table);

    pretty_printer pp;
    pp_string (&pp, (ধ্রুব বর্ণ *) tok.val.str.text);
    pp_newline (&pp);
    cpp_ঠেলো_buffer (parse_in,
		     (ধ্রুব unsigned বর্ণ *) pp_formatted_text (&pp),
		     strlen (pp_formatted_text (&pp)),
		     0);

    বৃক্ষ মান;
    location_t loc;
    unsigned বর্ণ cpp_flags;
    c_lex_with_flags (&মান, &loc, &cpp_flags, 0);

    cpp_destroy (parse_in);
    parse_in = old_parse_in;

    যদি (মান && বৃক্ষ_CODE (মান) == INTEGER_CST)
      প্রত্যাগম মান;

    প্রত্যাগম NULL_বৃক্ষ;
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

স্থির শূন্য
c_parser_translation_unit (c_parser *parser)
{
  যদি (c_parser_next_token_is (parser, CPP_EOF))
    {
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C forbids an empty translation unit");
    }
  অন্যথা
    {
      শূন্য *obstack_position = obstack_alloc (&parser_obstack, 0);
      mark_valid_location_for_stdc_pragma (অসত্য);
      কুরু
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      যাবত্ (c_parser_next_token_is_not (parser, CPP_EOF));
    }

  unsigned পূর্ণাঙ্ক i;
  বৃক্ষ decl;
  FOR_EACH_VEC_ELT (incomplete_record_decls, i, decl)
    যদি (DECL_SIZE (decl) == NULL_বৃক্ষ && বৃক্ষ_TYPE (decl) != error_mark_গ্রন্থি)
      error ("storage size of %q+D isn%'t known", decl);

  যদি (vec_safe_length (current_omp_declare_target_attribute))
    {
      c_omp_declare_target_attr
	a = current_omp_declare_target_attribute->বের_করো ();
      যদি (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_safe_truncate (current_omp_declare_target_attribute, 0);
    }
  যদি (vec_safe_length (current_omp_begin_assumes))
    {
      যদি (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_safe_truncate (current_omp_begin_assumes, 0);
    }
  যদি (vec_safe_length (current_omp_declare_variant_attribute))
    {
      যদি (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_safe_truncate (current_omp_declare_variant_attribute, 0);
    }
  যদি (vec_safe_length (omp_begin_declare_variant_map))
    {
      unsigned পূর্ণাঙ্ক i;
      omp_begin_declare_variant_map_entry *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_finish_variant_function (e->variant, e->id, e->ctx);
      vec_safe_truncate (omp_begin_declare_variant_map, 0);
    }

#যদি ENABLE_ANALYZER
  যদি (flag_analyzer)
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

স্থির শূন্য
c_parser_external_declaration (c_parser *parser)
{
  পূর্ণাঙ্ক ext;
  বিকল্প (c_parser_peek_token (parser)->type)
    {
    পক্ষ CPP_KEYWORD:
      বিকল্প (c_parser_peek_token (parser)->keyword)
	{
	পক্ষ RID_EXTENSION:
	  ext = disable_extension_diagnostics ();
	  c_parser_consume_token (parser);
	  c_parser_external_declaration (parser);
	  restore_extension_diagnostics (ext);
	  ভঙ্গ;
	পক্ষ RID_ASM:
	  c_parser_asm_definition (parser);
	  ভঙ্গ;
	পক্ষ RID_AT_INTERFACE:
	পক্ষ RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_definition (parser, NULL_বৃক্ষ);
	  ভঙ্গ;
	পক্ষ RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  ভঙ্গ;
	পক্ষ RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  ভঙ্গ;
	পক্ষ RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_protocol_definition (parser, NULL_বৃক্ষ);
	  ভঙ্গ;
	পক্ষ RID_AT_PROPERTY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_property_declaration (parser);
	  ভঙ্গ;
	পক্ষ RID_AT_SYNTHESIZE:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_synthesize_declaration (parser);
	  ভঙ্গ;
	পক্ষ RID_AT_DYNAMIC:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_dynamic_declaration (parser);
	  ভঙ্গ;
	পক্ষ RID_AT_END:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_finish_implementation ();
	  ভঙ্গ;
	স্বভাব:
	  গচ্ছ decl_or_fndef;
	}
      ভঙ্গ;
    পক্ষ CPP_SEMICOLON:
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      ভঙ্গ;
    পক্ষ CPP_PRAGMA:
      mark_valid_location_for_stdc_pragma (সত্য);
      c_parser_pragma (parser, pragma_external, রিক্ত, NULL_বৃক্ষ);
      mark_valid_location_for_stdc_pragma (অসত্য);
      ভঙ্গ;
    পক্ষ CPP_PLUS:
    পক্ষ CPP_MINUS:
      যদি (c_dialect_objc ())
	{
	  c_parser_objc_method_definition (parser);
	  ভঙ্গ;
	}
      /* Else fall through, and yield a syntax error trying to parse
	 as a declaration or function definition.  */
      /* FALLTHRU */
    স্বভাব:
    decl_or_fndef:
      /* A declaration or a function definition (or, in Objective-C,
	 an @interface or @protocol with prefix attributes).  We can
	 only tell which after parsing the declaration specifiers, if
	 any, and the first declarator.  */
      c_parser_declaration_or_fndef (parser, সত্য, সত্য, সত্য, অসত্য, সত্য,
				     অসত্য);
      ভঙ্গ;
    }
}

স্থির শূন্য c_parser_handle_directive_omp_attributes (বৃক্ষ &, vec<c_token> *&,
						      vec<c_token> *);
স্থির শূন্য c_finish_omp_declare_simd (c_parser *, বৃক্ষ, বৃক্ষ, vec<c_token> *);
স্থির শূন্য c_finish_oacc_routine (সংরচনা oacc_routine_data *, বৃক্ষ, তার্কিক);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

স্থির শূন্য
add_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  যদি (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    প্রত্যাগম;

  বৃক্ষ stmt = build0 (DEBUG_BEGIN_STMT, void_type_গ্রন্থি);
  SET_রাশিমালা_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

স্থির বৃক্ষ
handle_assume_attribute (location_t here, বৃক্ষ attrs, তার্কিক nested)
{
  যদি (nested)
    প্রতি (বৃক্ষ attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", বৃক্ষ_CHAIN (attr)))
      {
	বৃক্ষ args = বৃক্ষ_মান (attr);
	পূর্ণাঙ্ক nargs = list_length (args);
	যদি (nargs != 1)
	  {
	    error_at (here, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (here, "expected %i, found %i", 1, nargs);
	  }
	অন্যথা
	  {
	    বৃক্ষ arg = বৃক্ষ_মান (args);
	    arg = c_objc_common_truthvalue_conversion (here, arg);
	    arg = c_fully_fold (arg, অসত্য, রিক্ত);
	    যদি (arg != error_mark_গ্রন্থি)
	      {
		বৃক্ষ fn = build_call_রাশিমালা_internal_loc (here, IFN_ASSUME,
							void_type_গ্রন্থি, 1,
							arg);
		add_stmt (fn);
	      }
	  }
      }
  অন্যথা
    pedwarn (here, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  প্রত্যাগম remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

স্থির শূন্য
c_parser_maybe_reclassify_token (c_parser *parser)
{
  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      যদি (token->id_kind == C_ID_ID || token->id_kind == C_ID_TYPENAME)
	{
	  বৃক্ষ decl = lookup_name (token->মান);

	  token->id_kind = C_ID_ID;
	  যদি (decl)
	    {
	      যদি (বৃক্ষ_CODE (decl) == TYPE_DECL)
		token->id_kind = C_ID_TYPENAME;
	    }
	  অন্যথা যদি (c_dialect_objc ())
	    {
	      বৃক্ষ objc_interface_decl = objc_is_class_name (token->মান);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      যদি (objc_interface_decl)
		{
		  token->মান = objc_interface_decl;
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

স্থির বৃক্ষ
c_parser_declaration_or_fndef (c_parser *parser, তার্কিক fndef_ok,
			       তার্কিক static_assert_ok, তার্কিক empty_ok,
			       তার্কিক nested, তার্কিক start_attr_ok,
			       তার্কিক simple_ok,
			       বৃক্ষ *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       তার্কিক have_attrs /* = false */,
			       বৃক্ষ attrs /* = NULL_TREE */,
			       সংরচনা oacc_routine_data *oacc_routine_data
			       /* = NULL */,
			       তার্কিক *fallthru_attr_p /* = NULL */)
{
  সংরচনা c_declspecs *specs;
  বৃক্ষ prefix_attrs;
  বৃক্ষ all_prefix_attrs;
  তার্কিক diagnosed_no_specs = অসত্য;
  location_t here = c_parser_peek_token (parser)->location;
  বৃক্ষ result = NULL_বৃক্ষ;

  add_debug_begin_stmt (c_parser_peek_token (parser)->location);

  যদি (static_assert_ok
      && c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      প্রত্যাগম result;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  যদি (have_attrs)
    {
      declspecs_add_attrs (here, specs, attrs);
      specs->non_std_attrs_seen_p = অসত্য;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  যদি (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_kind == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->মান)))
    {
      বৃক্ষ name = c_parser_peek_token (parser)->মান;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (here);
      যদি (tag_exists_p (RECORD_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.add_fixit_ঢোকাও_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      অন্যথা যদি (tag_exists_p (UNION_TYPE, name))
	{
	  richloc.add_fixit_ঢোকাও_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      অন্যথা যদি (tag_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.add_fixit_ঢোকাও_before ("enum ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<enum%> keyword to refer to the type",
		    name);
	}
      অন্যথা
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (name, FUZZY_LOOKUP_TYPENAME,
					      here);
	  যদি (ধ্রুব বর্ণ *suggestion = hint.suggestion ())
	    {
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			name, suggestion);
	    }
	  অন্যথা
	    error_at (here, "unknown type name %qE", name);
	}

      /* Parse declspecs normally to get a correct pointer type, but avoid
         a further "fails to be a type name" error.  Refuse nested functions
         since it is not how the user likely wants us to recover.  */
      c_parser_peek_token (parser)->type = CPP_KEYWORD;
      c_parser_peek_token (parser)->keyword = RID_VOID;
      c_parser_peek_token (parser)->মান = error_mark_গ্রন্থি;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  যদি (c_parser_nth_token_starts_std_attributes (parser, 1))
    have_attrs = সত্য;

  c_parser_declspecs (parser, specs, সত্য, সত্য, start_attr_ok,
		      সত্য, সত্য, start_attr_ok, সত্য, cla_nonabstract_decl);
  যদি (parser->error)
    {
      c_parser_skip_to_end_of_block_or_statement (parser);
      প্রত্যাগম result;
    }
  যদি (nested && !specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_end_of_block_or_statement (parser);
      প্রত্যাগম result;
    }

  finish_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  যদি (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_শীর্ষ_anonymous_type (specs->type);

  তার্কিক gnu_auto_type_p = specs->typespec_word == cts_auto_type;
  তার্কিক std_auto_type_p = specs->c23_auto_p;
  তার্কিক any_auto_type_p = gnu_auto_type_p || std_auto_type_p;
  gcc_assert (!(gnu_auto_type_p && std_auto_type_p));
  ধ্রুব বর্ণ *auto_type_keyword = gnu_auto_type_p ? "__auto_type" : "auto";
  যদি (specs->constexpr_p)
    {
      /* An underspecified declaration may not declare tags or members
	 or structures or unions; it is undefined behavior to declare
	 the members of an enumeration.  Where the structure, union or
	 enumeration type is declared within an initializer, this is
	 diagnosed elsewhere.  Diagnose here the case of declaring
	 such a type in the type specifiers of a constexpr
	 declaration.  */
      বিকল্প (specs->typespec_kind)
	{
	পক্ষ ctsk_tagfirstref:
	পক্ষ ctsk_tagfirstref_attrs:
	  error_at (here, "%qT declared in underspecified object declaration",
		    specs->type);
	  ভঙ্গ;

	পক্ষ ctsk_tagdef:
	  error_at (here, "%qT defined in underspecified object declaration",
		    specs->type);
	  ভঙ্গ;

	স্বভাব:
	  ভঙ্গ;
	}
    }

  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      তার্কিক handled_assume = অসত্য;
      যদি (specs->attrs
	  && !nested
	  && specs->typespec_kind == ctsk_none
	  && c_parser_handle_statement_omp_attributes (parser, specs->attrs,
						       রিক্ত))
	{
	  যদি (specs->attrs)
	    c_warn_unused_attributes (specs->attrs);
	  যাবত্ (parser->in_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_next_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, রিক্ত, NULL_বৃক্ষ);
	    }
	  c_parser_consume_token (parser);
	  প্রত্যাগম result;
	}
      যদি (specs->typespec_kind == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = সত্য;
	  specs->attrs
	    = handle_assume_attribute (here, specs->attrs, nested);
	}
      যদি (any_auto_type_p)
	error_at (here, "%qs in empty declaration", auto_type_keyword);
      অন্যথা যদি (specs->typespec_kind == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  যদি (fallthru_attr_p != রিক্ত)
	    *fallthru_attr_p = সত্য;
	  যদি (nested)
	    {
	      বৃক্ষ fn = build_call_রাশিমালা_internal_loc (here, IFN_FALLTHROUGH,
						      void_type_গ্রন্থি, 0);
	      add_stmt (fn);
	    }
	  অন্যথা
	    pedwarn (here, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      অন্যথা যদি (empty_ok
	       && !(have_attrs && specs->non_std_attrs_seen_p)
	       && !handled_assume)
	shadow_tag (specs);
      অন্যথা
	{
	  shadow_tag_warned (specs, 1);
	  যদি (!handled_assume)
	    pedwarn (here, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      যদি (specs->রাশিমালা)
	add_stmt (fold_convert (void_type_গ্রন্থি, specs->রাশিমালা));
      c_parser_consume_token (parser);
      যদি (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, NULL_বৃক্ষ, অসত্য);
      প্রত্যাগম result;
    }
  অন্যথা যদি (specs->typespec_kind == ctsk_none
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
      যদি (astate.musttail_p)
	{
	  যদি (specs->attrs)
	    {
	      auto_urlify_attributes sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, রিক্ত, NULL_বৃক্ষ, রিক্ত,
					   astate);
	  প্রত্যাগম result;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  যদি (empty_ok
      && specs->typespec_kind == ctsk_tagdef
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = অসত্য;
      shadow_tag_warned (specs, 1);
      প্রত্যাগম result;
    }
  অন্যথা যদি (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      বিকল্প (c_parser_peek_token (parser)->type)
	{
	  পক্ষ CPP_PLUS:
	  পক্ষ CPP_MINUS:
	    যদি (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      প্রত্যাগম result;
	    যদি (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_বৃক্ষ;
	      }
	    যদি (fndef_ok)
	      c_parser_objc_method_definition (parser);
	    অন্যথা
	      c_parser_objc_methodproto (parser);
	    প্রত্যাগম result;
	    ভঙ্গ;
	  স্বভাব:
	    ভঙ্গ;
	}
      /* This is where we parse 'attributes @interface ...',
	 'attributes @implementation ...', 'attributes @protocol ...'
	 (where attributes could be, for example, __attribute__
	 ((deprecated)).
      */
      বিকল্প (c_parser_peek_token (parser)->keyword)
	{
	পক্ষ RID_AT_INTERFACE:
	  {
	    যদি (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      প্রত্যাগম result;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    প্রত্যাগম result;
	  }
	  ভঙ্গ;
	পক্ষ RID_AT_IMPLEMENTATION:
	  {
	    যদি (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      প্রত্যাগম result;
	    যদি (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_বৃক্ষ;
	      }
	    c_parser_objc_class_definition (parser, NULL_বৃক্ষ);
	    প্রত্যাগম result;
	  }
	  ভঙ্গ;
	পক্ষ RID_AT_PROTOCOL:
	  {
	    যদি (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      প্রত্যাগম result;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    প্রত্যাগম result;
	  }
	  ভঙ্গ;
	পক্ষ RID_AT_ALIAS:
	পক্ষ RID_AT_CLASS:
	পক্ষ RID_AT_END:
	পক্ষ RID_AT_PROPERTY:
	  যদি (specs->attrs)
	    {
	      c_parser_error (parser, "unexpected attribute");
	      specs->attrs = রিক্ত;
	    }
	  ভঙ্গ;
	স্বভাব:
	  ভঙ্গ;
	}
    }
  অন্যথা যদি (attribute_fallthrough_p (specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  অন্যথা যদি (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_attributes (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_বৃক্ষ;
  তার্কিক more_than_one_decl = অসত্য;
  যাবত্ (সত্য)
    {
      সংরচনা c_declarator *declarator;
      তার্কিক dummy = অসত্য;
      timevar_id_t tv;
      বৃক্ষ fnbody = NULL_বৃক্ষ;
      বৃক্ষ underspec_name = NULL_বৃক্ষ;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_kind != ctsk_none,
					C_DTR_NORMAL, &dummy);
      যদি (declarator == রিক্ত)
	{
	  যদি (omp_declare_simd_clauses)
	    c_finish_omp_declare_simd (parser, NULL_বৃক্ষ, NULL_বৃক্ষ,
				       omp_declare_simd_clauses);
	  যদি (oacc_routine_data)
	    c_finish_oacc_routine (oacc_routine_data, NULL_বৃক্ষ, অসত্য);
	  /* This check is here purely to improve the diagnostic.  */
	  যদি (!simple_ok)
	    c_parser_skip_to_end_of_block_or_statement (parser);
	  প্রত্যাগম result;
	}
      যদি (flag_openmp || flag_openmp_simd)
	{
	  সংরচনা c_declarator *d = declarator;
	  যাবত্ (d->kind != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = রিক্ত;
	  c_parser_handle_directive_omp_attributes (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      যদি (gnu_auto_type_p && declarator->kind != cdk_id)
	{
	  error_at (here,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  প্রত্যাগম result;
	}
      যদি (std_auto_type_p)
	{
	  সংরচনা c_declarator *d = declarator;
	  যাবত্ (d->kind == cdk_attrs)
	    d = d->declarator;
	  যদি (d->kind != cdk_id)
	    {
	      error_at (here,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      প্রত্যাগম result;
	    }
	  underspec_name = d->u.id.id;
	}
      অন্যথা যদি (specs->constexpr_p)
	{
	  সংরচনা c_declarator *d = declarator;
	  যাবত্ (d->kind != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      যদি (c_parser_next_token_is (parser, CPP_EQ)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is_keyword (parser, RID_ASM)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_next_token_is_keyword (parser, RID_IN))
	{
	  বৃক্ষ asm_name = NULL_বৃক্ষ;
	  বৃক্ষ postfix_attrs = NULL_বৃক্ষ;
	  যদি (!diagnosed_no_specs && !specs->declspecs_seen_p)
	    {
	      diagnosed_no_specs = সত্য;
	      pedwarn (here, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = অসত্য;
	  যদি (c_parser_next_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_রাশিমালা (parser);
	  যদি (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_attributes (parser);
	      যদি (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (here, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  প্রত্যাগম result;
		}
	    }
	  যদি (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      বৃক্ষ d;
	      সংরচনা c_রাশিমালা init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      যদি (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (সারি_table, init_loc);
		  unsigned পূর্ণাঙ্ক underspec_state = 0;
		  যদি (std_auto_type_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  start_init (NULL_বৃক্ষ, asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  যদি (nested && !empty_ok)
		    flag_sanitize = 0;
		  init = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
		  যদি (std_auto_type_p)
		    finish_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  যদি (gnu_auto_type_p
		      && বৃক্ষ_CODE (init.মান) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (বৃক্ষ_OPERAND (init.মান, 1)))
		    error_at (here,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_to_rvalue (init_loc, init, সত্য, সত্য,
						   সত্য);
		  বৃক্ষ init_type = বৃক্ষ_TYPE (init.মান);
		  তার্কিক vm_type = c_type_variably_modified_p (init_type);
		  যদি (vm_type)
		    init.মান = save_রাশিমালা (init.মান);
		  finish_init ();
		  specs->typespec_kind = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = সত্য;
		  specs->type = init_type;
		  যদি (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_attributes (specs->type,
						  specs->postfix_attrs);
		      decl_attributes (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_বৃক্ষ;
		    }
		  যদি (vm_type)
		    {
		      তার্কিক maybe_const = সত্য;
		      বৃক্ষ type_রাশিমালা = c_fully_fold (init.মান, অসত্য,
						     &maybe_const);
		      specs->রাশিমালা_const_operands &= maybe_const;
		      যদি (specs->রাশিমালা)
			specs->রাশিমালা = build2 (COMPOUND_রাশিমালা,
					      বৃক্ষ_TYPE (type_রাশিমালা),
					      specs->রাশিমালা, type_রাশিমালা);
		      অন্যথা
			specs->রাশিমালা = type_রাশিমালা;
		    }
		  d = start_decl (declarator, specs, সত্য,
				  chainon (postfix_attrs, all_prefix_attrs));
		  যদি (!d)
		    d = error_mark_গ্রন্থি;
		  যদি (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_বৃক্ষ,
					       omp_declare_simd_clauses);
		  যদি (!omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_বৃক্ষ,
					       &omp_dsimd_idattr_clauses);
		}
	      অন্যথা
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (সারি_table, init_loc);
		  unsigned পূর্ণাঙ্ক underspec_state = 0;
		  যদি (specs->constexpr_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  d = start_decl (declarator, specs, সত্য,
				  chainon (postfix_attrs,
					   all_prefix_attrs),
				  !specs->constexpr_p);
		  যদি (!d)
		    d = error_mark_গ্রন্থি;
		  যদি (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_বৃক্ষ,
					       omp_declare_simd_clauses);
		  যদি (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_বৃক্ষ,
					       &omp_dsimd_idattr_clauses);
		  start_init (d, asm_name,
			      বৃক্ষ_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  যদি (বৃক্ষ_CODE (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  যদি (specs->constexpr_p)
		    {
		      finish_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      যদি (omp_declare_simd_clauses)
			c_finish_omp_declare_simd (parser, d, NULL_বৃক্ষ,
						   omp_declare_simd_clauses);
		  যদি (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_বৃক্ষ,
					       &omp_dsimd_idattr_clauses);
		    }
		  finish_init ();
		}
	      যদি (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, অসত্য);
	      যদি (d != error_mark_গ্রন্থি)
		{
		  maybe_warn_string_init (init_loc, বৃক্ষ_TYPE (d), init);
		  finish_decl (d, init_loc, init.মান,
			       init.original_type, asm_name);
		  result = d;
		}
	    }
	  অন্যথা
	    {
	      যদি (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  প্রত্যাগম result;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      বৃক্ষ attrs = chainon (postfix_attrs, all_prefix_attrs);
	      বৃক্ষ d = start_decl (declarator, specs, অসত্য, attrs, সত্য,
				   &lastloc);
	      যদি (d && বৃক্ষ_CODE (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  ধ্রুব সংরচনা c_declarator *decl = declarator;
		  ধ্রুব সংরচনা c_declarator *last_non_id_attrs = রিক্ত;

		  যাবত্ (decl)
		    বিকল্প (decl->kind)
		      {
		      পক্ষ cdk_array:
		      পক্ষ cdk_function:
		      পক্ষ cdk_pointer:
			last_non_id_attrs = decl;
			decl = decl->declarator;
			ভঙ্গ;

		      পক্ষ cdk_attrs:
			decl = decl->declarator;
			ভঙ্গ;

		      পক্ষ cdk_id:
			decl = 0;
			ভঙ্গ;

		      স্বভাব:
			gcc_unreachable ();
		      }

		  /* If it exists and is cdk_function declaration whose
		     arguments have not been set yet, use its arguments.  */
		  যদি (last_non_id_attrs
		      && last_non_id_attrs->kind == cdk_function)
		    {
		      বৃক্ষ parms = last_non_id_attrs->u.arg_info->parms;
		      যদি (DECL_ARGUMENTS (d) == NULL_বৃক্ষ
			  && DECL_INITIAL (d) == NULL_বৃক্ষ)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      যদি (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_empty ())
		{
		  বৃক্ষ parms = NULL_বৃক্ষ;
		  যদি (d && বৃক্ষ_CODE (d) == FUNCTION_DECL)
		    {
		      সংরচনা c_declarator *ce = declarator;
		      যাবত্ (ce != রিক্ত)
			যদি (ce->kind == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    ভঙ্গ;
			  }
			অন্যথা
			  ce = ce->declarator;
		    }
		  যদি (parms)
		    temp_store_parm_decls (d, parms);
		  যদি (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  যদি (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  যদি (parms)
		    temp_বের_করো_parm_decls ();
		}
	      যদি (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, অসত্য);
	      যদি (d)
		finish_decl (d, UNKNOWN_LOCATION, NULL_বৃক্ষ,
			     NULL_বৃক্ষ, asm_name);

	      যদি (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  যদি (d)
		    *objc_foreach_object_declaration = d;
		  অন্যথা
		    *objc_foreach_object_declaration = error_mark_গ্রন্থি;
		}
	    }
	  যদি (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      more_than_one_decl = সত্য;
	      যদি (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  প্রত্যাগম result;
		}
	      c_parser_consume_token (parser);
	      যদি (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
		all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					    prefix_attrs);
	      অন্যথা
		all_prefix_attrs = prefix_attrs;
	      অনুবর্ত;
	    }
	  অন্যথা যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      যদি (!simple_ok)
		c_parser_consume_token (parser);
	      প্রত্যাগম result;
	    }
	  অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      প্রত্যাগম result;
	    }
	  অন্যথা
	    {
	      যদি (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      অন্যথা যদি (more_than_one_decl)
		error_at (here, "declaration in condition can only declare "
			  "a single object");
	      প্রত্যাগম result;
	    }
	}
      অন্যথা যদি (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (here,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  প্রত্যাগম result;
	}
      অন্যথা যদি (!fndef_ok)
	{
	  যদি (simple_ok && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  অন্যথা
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	    }
	  প্রত্যাগম result;
	}
      /* Function definition (nested or otherwise).  */
      যদি (nested)
	{
	  pedwarn (here, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_ঠেলো_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      বৃক্ষ dv_base = NULL_বৃক্ষ;
      বৃক্ষ dv_ctx = NULL_বৃক্ষ;
      যদি (!vec_safe_is_empty (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->last ();
	  dv_ctx = copy_list (a.selector);
	  dv_base = omp_start_variant_function (declarator, dv_ctx);
	}

      যদি (!start_function (specs, declarator, all_prefix_attrs))
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
	  যদি (c_parser_next_token_starts_declspecs (parser))
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
	      parser->error = অসত্য;
	    }
	  অন্যথা
	    {
	      /* This can appear in many cases looking nothing like a
		 function definition, so we don't give a more specific
		 error suggesting there was one.  */
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			      "or %<__attribute__%>");
	    }
	  যদি (nested)
	    c_বের_করো_function_context ();
	  ভঙ্গ;
	}

      যদি (DECL_DECLARED_INLINE_P (current_function_decl))
        tv = TV_PARSE_INLINE;
      অন্যথা
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
      পূর্ণাঙ্ক save_debug_nonbind_markers_p = debug_nonbind_markers_p;
      debug_nonbind_markers_p = 0;
      c_parser_maybe_reclassify_token (parser);
      যাবত্ (c_parser_next_token_is_not (parser, CPP_EOF)
	     && c_parser_next_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, অসত্য, অসত্য, অসত্য,
				       সত্য, অসত্য, অসত্য);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      যদি (omp_declare_simd_clauses)
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_বৃক্ষ,
				   omp_declare_simd_clauses);
      যদি (!omp_dsimd_idattr_clauses.is_empty ())
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_বৃক্ষ,
				   &omp_dsimd_idattr_clauses);
      যদি (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, current_function_decl, সত্য);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_start_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      যদি (dv_base && current_function_decl != error_mark_গ্রন্থি)
	{
	  omp_begin_declare_variant_map_entry e
	    = { current_function_decl, dv_base, dv_ctx };
	  vec_safe_ঠেলো (omp_begin_declare_variant_map, e);
	}

      /* If the definition was marked with __RTL, use the RTL parser now,
	 consuming the function body.  */
      যদি (specs->declspec_il == cdil_rtl)
	{
	  endloc = c_parser_parse_rtl_body (parser, specs->gimple_or_rtl_pass);

	  /* Normally, store_parm_decls sets next_is_function_body,
	     anticipating a function body.  We need a push_scope/pop_scope
	     pair to flush out this state, or subsequent function parsing
	     will go wrong.  */
	  ঠেলো_scope ();
	  বের_করো_scope ();

	  finish_function (endloc);
	  প্রত্যাগম result;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      অন্যথা যদি (specs->declspec_il != cdil_none)
	{
	  তার্কিক saved = in_late_দ্বিমিক_op;
	  in_late_দ্বিমিক_op = সত্য;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->entry_bb_গুনতি);
	  in_late_দ্বিমিক_op = saved;
	}
      অন্যথা
	fnbody = c_parser_compound_statement (parser, &endloc);
      বৃক্ষ fndecl = current_function_decl;
      যদি (nested && specs->declspec_il == cdil_none)
	{
	  বৃক্ষ decl = current_function_decl;
	  /* Mark nested functions as needing static-chain initially.
	     lower_nested_functions will recompute it but the
	     DECL_STATIC_CHAIN flag is also used before that happens,
	     by initializer_constant_valid_p.  See gcc.dg/nested-fn-2.c.  */
	  DECL_STATIC_CHAIN (decl) = 1;
	  add_stmt (fnbody);
	  finish_function (endloc);
	  c_বের_করো_function_context ();
	  add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_রাশিমালা, decl));
	}
      অন্যথা যদি (nested)
	{
	  যদি (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  অন্যথা
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  finish_function (endloc);
	  c_বের_করো_function_context ();
	}
      অন্যথা
	{
	  যদি (fnbody)
	    add_stmt (fnbody);
	  finish_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      যদি (specs->declspec_il != cdil_none)
	DECL_SAVED_বৃক্ষ (fndecl) = NULL_বৃক্ষ;

      ভঙ্গ;
    }

  প্রত্যাগম result;
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

স্থির শূন্য
c_parser_asm_definition (c_parser *parser)
{
  location_t asm_loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  বৃক্ষ asm_str = NULL_বৃক্ষ;
  বৃক্ষ outputs = NULL_বৃক্ষ, inputs = NULL_বৃক্ষ;
  যদি (!parens.require_open (parser))
    গচ্ছ done;
  asm_str = c_parser_asm_string_literal (parser);
  যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      গচ্ছ done;
    }
  প্রতি (পূর্ণাঙ্ক section = 0; section < 2; ++section)
    {
      যদি (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  যদি (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
	      asm_str = NULL_বৃক্ষ;
	      গচ্ছ done;
	    }
	  c_parser_consume_token (parser);
	}
      অন্যথা যদি (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, অসত্য))
	গচ্ছ error_close_paren;
      যদি (!c_parser_next_token_is (parser, CPP_COLON)
	  && !c_parser_next_token_is (parser, CPP_SCOPE)
	  && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  যদি (section)
	    inputs = c_parser_asm_operands (parser);
	  অন্যথা
	    outputs = c_parser_asm_operands (parser);
	}
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	ভঙ্গ;
    }

  যদি (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
      asm_str = NULL_বৃক্ষ;
    }

  যদি (asm_str)
    asm_str = build_asm_রাশিমালা (asm_loc, asm_str, outputs, inputs,
			      NULL_বৃক্ষ, NULL_বৃক্ষ, অসত্য, অসত্য);
done:
  যদি (asm_str)
    symtab->finalize_toplevel_asm (asm_str);
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse a static assertion (C11 6.7.10).

   static_assert-declaration:
     static_assert-declaration-no-semi ;
*/

স্থির শূন্য
c_parser_static_assert_declaration (c_parser *parser)
{
  c_parser_static_assert_declaration_no_semi (parser);
  যদি (parser->error
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

স্থির শূন্য
c_parser_static_assert_declaration_no_semi (c_parser *parser)
{
  location_t assert_loc, মান_loc;
  বৃক্ষ মান;
  বৃক্ষ string = NULL_বৃক্ষ;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT));
  বৃক্ষ spelling = c_parser_peek_token (parser)->মান;
  assert_loc = c_parser_peek_token (parser)->location;
  যদি (flag_isoc99)
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  অন্যথা
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  c_parser_consume_token (parser);
  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম;
  location_t মান_tok_loc = c_parser_peek_token (parser)->location;
  মান = convert_lvalue_to_rvalue (মান_tok_loc,
				    c_parser_রাশিমালা_no_commas (parser, রিক্ত),
				    সত্য, সত্য).মান;
  মান_loc = রাশিমালা_LOC_OR_LOC (মান, মান_tok_loc);
  যদি (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      বিকল্প (c_parser_peek_token (parser)->type)
	{
	পক্ষ CPP_STRING:
	পক্ষ CPP_STRING16:
	পক্ষ CPP_STRING32:
	পক্ষ CPP_WSTRING:
	পক্ষ CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, অসত্য, সত্য).মান;
	  ভঙ্গ;
	স্বভাব:
	  c_parser_error (parser, "expected string literal");
	  প্রত্যাগম;
	}
    }
  অন্যথা যদি (flag_isoc11)
    /* If pedantic for pre-C11, the use of _Static_assert itself will
       have been diagnosed, so do not also diagnose the use of this
       new C23 feature of _Static_assert.  */
    pedwarn_c11 (assert_loc, OPT_Wpedantic,
		 "ISO C11 does not support omitting the string in "
		 "%qE", spelling);
  parens.require_close (parser);

  যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (মান)))
    {
      error_at (মান_loc, "expression in static assertion is not an integer");
      প্রত্যাগম;
    }
  যদি (বৃক্ষ_CODE (মান) != INTEGER_CST)
    {
      মান = c_fully_fold (মান, অসত্য, রিক্ত);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (মান);
      যদি (বৃক্ষ_CODE (মান) == INTEGER_CST)
	pedwarn (মান_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  যদি (বৃক্ষ_CODE (মান) != INTEGER_CST)
    {
      error_at (মান_loc, "expression in static assertion is not constant");
      প্রত্যাগম;
    }
  constant_expression_warning (মান);
  যদি (integer_zerop (মান))
    {
      যদি (string)
	error_at (assert_loc, "static assertion failed: %E", string);
      অন্যথা
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

শূন্য
c_parser_declspecs (c_parser *parser, সংরচনা c_declspecs *specs,
		    তার্কিক scspec_ok, তার্কিক typespec_ok, তার্কিক start_attr_ok,
		    তার্কিক alignspec_ok, তার্কিক auto_type_ok,
		    তার্কিক start_std_attr_ok, তার্কিক end_std_attr_ok,
		    গণনা c_lookahead_kind la)
{
  তার্কিক attrs_ok = start_attr_ok;
  তার্কিক seen_type = specs->typespec_kind != ctsk_none;

  যদি (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  যদি (start_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_seen_p);
      location_t loc = c_parser_peek_token (parser)->location;
      বৃক্ষ attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_add_attrs (loc, specs, attrs);
      specs->non_std_attrs_seen_p = অসত্য;
    }

  যাবত্ (c_parser_next_token_is (parser, CPP_NAME)
	 || c_parser_next_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_next_token_is (parser, CPP_LESS)))
    {
      সংরচনা c_typespec t;
      বৃক্ষ attrs;
      বৃক্ষ align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      যদি ((!typespec_ok || specs->typespec_kind == ctsk_tagdef)
	  && c_parser_next_tokens_start_typename (parser, la)
	  && !c_parser_next_token_is_qualifier (parser)
	  && !c_parser_next_token_is_keyword (parser, RID_ALIGNAS))
	ভঙ্গ;

      যদি (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  বৃক্ষ মান = name_token->মান;
	  c_id_kind kind = name_token->id_kind;

	  যদি (kind == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_FIRST_ADDR_SPACE;
	      declspecs_add_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = সত্য;
	      অনুবর্ত;
	    }

	  gcc_assert (!c_parser_next_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  যদি (seen_type || !c_parser_next_tokens_start_typename (parser, la))
	    ভঙ্গ;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  seen_type = সত্য;
	  attrs_ok = সত্য;
	  যদি (kind == C_ID_ID)
	    {
	      auto_diagnostic_group d;
	      name_hint hint = lookup_name_fuzzy (মান, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      যদি (ধ্রুব বর্ণ *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.add_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    মান, suggestion);
		}
	      অন্যথা
		error_at (loc, "unknown type name %qE", মান);
	      t.kind = ctsk_typedef;
	      t.spec = error_mark_গ্রন্থি;
	    }
	  অন্যথা যদি (kind == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_next_token_is_not (parser, CPP_LESS)))
	    {
	      t.kind = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (মান);
	    }
	  অন্যথা
	    {
	      বৃক্ষ proto = NULL_বৃক্ষ;
	      gcc_assert (c_dialect_objc ());
	      t.kind = ctsk_objc;
	      যদি (c_parser_next_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (মান, proto);
	    }
	  t.রাশিমালা = NULL_বৃক্ষ;
	  t.রাশিমালা_const_operands = সত্য;
	  t.has_enum_type_specifier = অসত্য;
	  declspecs_add_type (name_token->location, specs, t);
	  অনুবর্ত;
	}
      যদি (c_parser_next_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  বৃক্ষ proto;
	  gcc_assert (c_dialect_objc ());
	  যদি (!typespec_ok || seen_type)
	    ভঙ্গ;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.kind = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_বৃক্ষ, proto);
	  t.রাশিমালা = NULL_বৃক্ষ;
	  t.রাশিমালা_const_operands = সত্য;
	  t.has_enum_type_specifier = অসত্য;
	  declspecs_add_type (loc, specs, t);
	  অনুবর্ত;
	}
      gcc_assert (c_parser_next_token_is (parser, CPP_KEYWORD));
      বিকল্প (c_parser_peek_token (parser)->keyword)
	{
	পক্ষ RID_STATIC:
	পক্ষ RID_EXTERN:
	পক্ষ RID_REGISTER:
	পক্ষ RID_TYPEDEF:
	পক্ষ RID_INLINE:
	পক্ষ RID_NORETURN:
	পক্ষ RID_AUTO:
	পক্ষ RID_THREAD:
	পক্ষ RID_CONSTEXPR:
	  যদি (!scspec_ok)
	    গচ্ছ out;
	  attrs_ok = সত্য;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_add_scspec (loc, specs,
				c_parser_peek_token (parser)->মান);
	  c_parser_consume_token (parser);
	  ভঙ্গ;
	পক্ষ RID_AUTO_TYPE:
	  যদি (!auto_type_ok)
	    গচ্ছ out;
	  /* Fall through.  */
	পক্ষ RID_UNSIGNED:
	পক্ষ RID_LONG:
	পক্ষ RID_SHORT:
	পক্ষ RID_SIGNED:
	পক্ষ RID_COMPLEX:
	পক্ষ RID_INT:
	পক্ষ RID_CHAR:
	পক্ষ RID_FLOAT:
	পক্ষ RID_DOUBLE:
	পক্ষ RID_VOID:
	পক্ষ RID_DFLOAT32:
	পক্ষ RID_DFLOAT64:
	পক্ষ RID_DFLOAT128:
	পক্ষ RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	পক্ষ RID_BOOL:
	পক্ষ RID_FRACT:
	পক্ষ RID_ACCUM:
	পক্ষ RID_SAT:
	পক্ষ RID_INT_N_0:
	পক্ষ RID_INT_N_1:
	পক্ষ RID_INT_N_2:
	পক্ষ RID_INT_N_3:
	  যদি (!typespec_ok)
	    গচ্ছ out;
	  attrs_ok = সত্য;
	  seen_type = সত্য;
	  যদি (c_dialect_objc ())
	    parser->objc_need_raw_identifier = সত্য;
	  t.kind = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->মান;
	  t.রাশিমালা = NULL_বৃক্ষ;
	  t.রাশিমালা_const_operands = সত্য;
	  t.has_enum_type_specifier = অসত্য;
	  declspecs_add_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  ভঙ্গ;
	পক্ষ RID_ENUM:
	  যদি (!typespec_ok)
	    গচ্ছ out;
	  attrs_ok = সত্য;
	  seen_type = সত্য;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  ভঙ্গ;
	পক্ষ RID_STRUCT:
	পক্ষ RID_UNION:
	  যদি (!typespec_ok)
	    গচ্ছ out;
	  attrs_ok = সত্য;
	  seen_type = সত্য;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  ভঙ্গ;
	পক্ষ RID_TYPEOF:
	পক্ষ RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  যদি (!typespec_ok || seen_type)
	    গচ্ছ out;
	  attrs_ok = সত্য;
	  seen_type = সত্য;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_add_type (loc, specs, t);
	  ভঙ্গ;
	পক্ষ RID_BITINT:
	  যদি (!typespec_ok)
	    গচ্ছ out;
	  অন্যথা
	    {
	      attrs_ok = সত্য;
	      seen_type = সত্য;
	      t.kind = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->মান;
	      t.রাশিমালা = error_mark_গ্রন্থি;
	      t.রাশিমালা_const_operands = সত্য;
	      t.has_enum_type_specifier = অসত্য;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      যদি (parens.require_open (parser))
		{
		  c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
		  t.রাশিমালা = convert_lvalue_to_rvalue (loc, রাশিমালা, সত্য,
						     সত্য).মান;
		  parens.skip_until_found_close (parser);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  ভঙ্গ;
	পক্ষ RID_ATOMIC:
	  /* C parser handling of Objective-C constructs needs
	     checking for correct lvalue-to-rvalue conversions, and
	     the code in build_modify_expr handling various
	     Objective-C cases, and that in build_unary_op handling
	     Objective-C cases for increment / decrement, also needs
	     updating; uses of TYPE_MAIN_VARIANT in objc_compare_types
	     and objc_types_are_equivalent may also need updates.  */
	  যদি (c_dialect_objc ())
	    sorry ("%<_Atomic%> in Objective-C");
	  যদি (flag_isoc99)
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C99 does not support the %<_Atomic%> qualifier");
	  অন্যথা
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C90 does not support the %<_Atomic%> qualifier");
	  attrs_ok = সত্য;
	  বৃক্ষ মান;
	  মান = c_parser_peek_token (parser)->মান;
	  c_parser_consume_token (parser);
	  যদি (typespec_ok && c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      seen_type = সত্য;
	      c_parser_consume_token (parser);
	      সংরচনা c_type_name *type = c_parser_type_name (parser);
	      t.kind = ctsk_typeof;
	      t.spec = error_mark_গ্রন্থি;
	      t.রাশিমালা = NULL_বৃক্ষ;
	      t.রাশিমালা_const_operands = সত্য;
	      t.has_enum_type_specifier = অসত্য;
	      যদি (type != রিক্ত)
		t.spec = groktypename (type, &t.রাশিমালা,
				       &t.রাশিমালা_const_operands);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      যদি (t.spec != error_mark_গ্রন্থি)
		{
		  যদি (বৃক্ষ_CODE (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  অন্যথা যদি (বৃক্ষ_CODE (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  অন্যথা যদি (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  অন্যথা
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  অন্যথা
	    declspecs_add_qual (loc, specs, মান);
	  ভঙ্গ;
	পক্ষ RID_CONST:
	পক্ষ RID_VOLATILE:
	পক্ষ RID_RESTRICT:
	  attrs_ok = সত্য;
	  declspecs_add_qual (loc, specs, c_parser_peek_token (parser)->মান);
	  c_parser_consume_token (parser);
	  ভঙ্গ;
	পক্ষ RID_ATTRIBUTE:
	  যদি (!attrs_ok)
	    গচ্ছ out;
	  attrs = c_parser_gnu_attributes (parser);
	  declspecs_add_attrs (loc, specs, attrs);
	  ভঙ্গ;
	পক্ষ RID_ALIGNAS:
	  যদি (!alignspec_ok)
	    গচ্ছ out;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_add_alignas (loc, specs, align);
	  ভঙ্গ;
	পক্ষ RID_GIMPLE:
	  যদি (! flag_gimple)
	    error_at (loc, "%<__GIMPLE%> only valid with %<-fgimple%>");
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_gimple;
	  specs->locations[cdw_gimple] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  ভঙ্গ;
	পক্ষ RID_RTL:
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_rtl;
	  specs->locations[cdw_rtl] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  ভঙ্গ;
	স্বভাব:
	  গচ্ছ out;
	}
    }
 out:
  যদি (end_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    specs->postfix_attrs = c_parser_std_attribute_specifier_sequence (parser);
}

/* Complain about a non-CPP_NAME within an enumerator list.  */

স্থির শূন্য
report_bad_enum_name (c_parser *parser)
{
  যদি (!parser->error)
    {
      c_token *token = c_parser_peek_token (parser);
      বিকল্প (token->type)
	{
	স্বভাব:
	  ভঙ্গ;
	পক্ষ CPP_CLOSE_BRACE:
	  /* Give a nicer error for "enum {}".  */
	  error_at (token->location,
		    "empty enum is invalid");
	  parser->error = সত্য;
	  প্রত্যাগম;
	পক্ষ CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  যদি (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_group d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_POINTER (token->মান));
	      add_note_about_new_keyword (token->location,
					  token->মান);
	      parser->error = সত্য;
	      প্রত্যাগম;
	    }
	  ভঙ্গ;
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

স্থির সংরচনা c_typespec
c_parser_enum_specifier (c_parser *parser)
{
  সংরচনা c_typespec ret;
  তার্কিক have_std_attrs;
  তার্কিক potential_nesting_p = অসত্য;
  বৃক্ষ std_attrs = NULL_বৃক্ষ;
  বৃক্ষ attrs;
  বৃক্ষ ident = NULL_বৃক্ষ;
  বৃক্ষ fixed_underlying_type = NULL_বৃক্ষ;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  যদি (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));
  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->মান;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  যদি (c_parser_next_token_is (parser, CPP_COLON)
      /* Distinguish an enum-type-specifier from a bit-field
	 declaration of the form "enum e : constant-expression;".  */
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      pedwarn_c11 (enum_loc, OPT_Wpedantic,
		   "ISO C does not support specifying %<enum%> underlying "
		   "types before C23");
      যদি (ident)
	{
	  /* The tag is in scope during the enum-type-specifier (which
	     may refer to the tag inside typeof).  */
	  ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, সত্য);
	  যদি (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_বৃক্ষ == TYPE_মানসমূহ (ret.spec);
	}
      অন্যথা
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_বৃক্ষ;
	  ret.kind = ctsk_tagdef;
	  ret.রাশিমালা = NULL_বৃক্ষ;
	  ret.রাশিমালা_const_operands = সত্য;
	  ret.has_enum_type_specifier = সত্য;
	}
      c_parser_consume_token (parser);
      সংরচনা c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, অসত্য, সত্য, অসত্য, অসত্য, অসত্য,
			  অসত্য, সত্য, cla_prefer_id);
      finish_declspecs (specs);
      যদি (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      অন্যথা যদি (বৃক্ষ_CODE (specs->type) != INTEGER_TYPE
	       && বৃক্ষ_CODE (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || বৃক্ষ_CODE (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_গ্রন্থি;
	}
      অন্যথা যদি (specs->restrict_p)
	error_at (enum_loc, "invalid use of %<restrict%>");
      fixed_underlying_type = TYPE_MAIN_VARIANT (specs->type);
      যদি (ident)
	{
	  /* The type specified must be consistent with any previously
	     specified underlying type.  If this is a newly declared
	     type, it is now a complete type.  */
	  যদি (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
	      && ENUM_UNDERLYING_TYPE (ret.spec) == NULL_বৃক্ষ)
	    {
	      TYPE_MIN_মান (ret.spec) =
		TYPE_MIN_মান (fixed_underlying_type);
	      TYPE_MAX_মান (ret.spec) =
		TYPE_MAX_মান (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      SET_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_SIZE (ret.spec) = NULL_বৃক্ষ;
	      TYPE_PRECISION (ret.spec) =
		TYPE_PRECISION (fixed_underlying_type);
	      ENUM_UNDERLYING_TYPE (ret.spec) = fixed_underlying_type;
	      layout_type (ret.spec);
	    }
	  অন্যথা যদি (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
		   && !comptypes (fixed_underlying_type,
				  ENUM_UNDERLYING_TYPE (ret.spec)))
	    {
	      error_at (enum_loc, "%<enum%> underlying type incompatible with "
			"previous declaration");
	      fixed_underlying_type = ENUM_UNDERLYING_TYPE (ret.spec);
	    }
	}
    }
  যদি (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      সংরচনা c_enum_contents the_enum;
      বৃক্ষ type;
      বৃক্ষ postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      বৃক্ষ মানসমূহ;
      timevar_ঠেলো (TV_PARSE_ENUM);
      type = start_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      মানসমূহ = NULL_বৃক্ষ;
      c_parser_consume_token (parser);
      যাবত্ (সত্য)
	{
	  বৃক্ষ enum_id;
	  বৃক্ষ enum_মান;
	  বৃক্ষ enum_decl;
	  তার্কিক seen_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, মান_loc;
	  যদি (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, রিক্ত);
	      মানসমূহ = error_mark_গ্রন্থি;
	      ভঙ্গ;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->মান;
	  /* Set the location in case we create a decl now.  */
	  c_parser_set_source_position_from_token (token);
	  decl_loc = মান_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  বৃক্ষ std_attrs = NULL_বৃক্ষ;
	  যদি (c_parser_nth_token_starts_std_attributes (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  বৃক্ষ enum_attrs = chainon (std_attrs,
				     c_parser_gnu_attributes (parser));
	  যদি (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      মান_loc = c_parser_peek_token (parser)->location;
	      enum_মান = convert_lvalue_to_rvalue (মান_loc,
						     (c_parser_রাশিমালা_no_commas
						      (parser, রিক্ত)),
						     সত্য, সত্য).মান;
	    }
	  অন্যথা
	    enum_মান = NULL_বৃক্ষ;
	  enum_decl = build_enumerator (decl_loc, মান_loc,
					&the_enum, enum_id, enum_মান);
	  যদি (enum_attrs)
	    decl_attributes (&বৃক্ষ_PURPOSE (enum_decl), enum_attrs, 0);
	  বৃক্ষ_CHAIN (enum_decl) = মানসমূহ;
	  মানসমূহ = enum_decl;
	  seen_comma = অসত্য;
	  যদি (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      seen_comma = সত্য;
	      c_parser_consume_token (parser);
	    }
	  যদি (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      যদি (seen_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      ভঙ্গ;
	    }
	  যদি (!seen_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, রিক্ত);
	      মানসমূহ = error_mark_গ্রন্থি;
	      ভঙ্গ;
	    }
	}
      postfix_attrs = c_parser_gnu_attributes (parser);
      ret.spec = finish_enum (type, nreverse (মানসমূহ),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.kind = ctsk_tagdef;
      ret.রাশিমালা = NULL_বৃক্ষ;
      ret.রাশিমালা_const_operands = সত্য;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_বৃক্ষ;
      timevar_বের_করো (TV_PARSE_ENUM);
      প্রত্যাগম ret;
    }
  অন্যথা যদি (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_গ্রন্থি;
      ret.kind = ctsk_tagref;
      ret.রাশিমালা = NULL_বৃক্ষ;
      ret.রাশিমালা_const_operands = সত্য;
      ret.has_enum_type_specifier = অসত্য;
      প্রত্যাগম ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  যদি (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  যদি (fixed_underlying_type == NULL_বৃক্ষ)
    {
      ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
			     std_attrs, অসত্য);
      /* In ISO C, enumerated types without a fixed underlying type
	 can be referred to only if already defined.  */
      যদি (pedantic && !COMPLETE_TYPE_P (ret.spec))
	{
	  gcc_assert (ident);
	  pedwarn (enum_loc, OPT_Wpedantic,
		   "ISO C forbids forward references to %<enum%> types");
	}
    }
  প্রত্যাগম ret;
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

স্থির সংরচনা c_typespec
c_parser_struct_or_union_specifier (c_parser *parser)
{
  সংরচনা c_typespec ret;
  তার্কিক have_std_attrs;
  বৃক্ষ std_attrs = NULL_বৃক্ষ;
  বৃক্ষ attrs;
  বৃক্ষ ident = NULL_বৃক্ষ;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  গণনা বৃক্ষ_code code;
  বিকল্প (c_parser_peek_token (parser)->keyword)
    {
    পক্ষ RID_STRUCT:
      code = RECORD_TYPE;
      ভঙ্গ;
    পক্ষ RID_UNION:
      code = UNION_TYPE;
      ভঙ্গ;
    স্বভাব:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  যদি (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->মান;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  যদি (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      বর্গ c_struct_parse_info *struct_info;
      বৃক্ষ type = start_struct (struct_loc, code, ident, &struct_info);
      বৃক্ষ postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      বৃক্ষ contents;
      বৃক্ষ রাশিমালা = রিক্ত;
      timevar_ঠেলো (TV_PARSE_STRUCT);
      contents = NULL_বৃক্ষ;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      যদি (c_parser_next_token_is_keyword (parser, RID_AT_DEFS))
	{
	  বৃক্ষ name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  যদি (!parens.require_open (parser))
	    গচ্ছ end_at_defs;
	  যদি (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->মান;
	      c_parser_consume_token (parser);
	    }
	  অন্যথা
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
	      গচ্ছ end_at_defs;
	    }
	  parens.skip_until_found_close (parser);
	  contents = nreverse (objc_get_class_ivars (name));
	}
    end_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      যাবত্ (সত্য)
	{
	  বৃক্ষ decls;
	  /* Parse any stray semicolon.  */
	  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      location_t semicolon_loc
		= c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (semicolon_loc);
	      richloc.add_fixit_remove ();
	      pedwarn (&richloc, OPT_Wpedantic,
		       "extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      অনুবর্ত;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  যদি (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      ভঙ্গ;
	    }
	  /* Accept #pragmas at struct scope.  */
	  যদি (c_parser_next_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, রিক্ত, NULL_বৃক্ষ);
	      অনুবর্ত;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &রাশিমালা);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  অন্যথা
	    {
	      যদি (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      অন্যথা যদি (parser->error
		       || !c_parser_next_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, রিক্ত);
		  ভঙ্গ;
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
				struct_info, &রাশিমালা);
      ret.kind = ctsk_tagdef;
      ret.রাশিমালা = রাশিমালা;
      ret.রাশিমালা_const_operands = সত্য;
      ret.has_enum_type_specifier = অসত্য;
      timevar_বের_করো (TV_PARSE_STRUCT);
      প্রত্যাগম ret;
    }
  অন্যথা যদি (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_গ্রন্থি;
      ret.kind = ctsk_tagref;
      ret.রাশিমালা = NULL_বৃক্ষ;
      ret.রাশিমালা_const_operands = সত্য;
      ret.has_enum_type_specifier = অসত্য;
      প্রত্যাগম ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  যদি (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_tag (ident_loc, code, ident, have_std_attrs, std_attrs,
			 অসত্য);
  প্রত্যাগম ret;
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

স্থির বৃক্ষ
c_parser_struct_declaration (c_parser *parser, বৃক্ষ *রাশিমালা)
{
  সংরচনা c_declspecs *specs;
  বৃক্ষ prefix_attrs;
  বৃক্ষ all_prefix_attrs;
  বৃক্ষ decls;
  location_t decl_loc;
  যদি (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      পূর্ণাঙ্ক ext;
      বৃক্ষ decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, রাশিমালা);
      restore_extension_diagnostics (ext);
      প্রত্যাগম decl;
    }
  যদি (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      প্রত্যাগম NULL_বৃক্ষ;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, অসত্য, সত্য, সত্য,
		      সত্য, অসত্য, সত্য, সত্য, cla_nonabstract_decl);
  যদি (parser->error)
    প্রত্যাগম NULL_বৃক্ষ;
  যদি (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      প্রত্যাগম NULL_বৃক্ষ;
    }
  finish_declspecs (specs);
  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      বৃক্ষ ret;
      যদি (specs->typespec_kind == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_tag_warned (specs, pedantic);
	  ret = NULL_বৃক্ষ;
	}
      অন্যথা
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  বৃক্ষ attrs = রিক্ত;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_বৃক্ষ), specs,
			   NULL_বৃক্ষ, &attrs, রাশিমালা);
	  যদি (ret)
	    decl_attributes (&ret, attrs, 0);
	}
      প্রত্যাগম ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  যদি (specs->typespec_kind == ctsk_tagdef
      && বৃক্ষ_CODE (specs->type) != ENUMERAL_TYPE
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = অসত্য;
      প্রত্যাগম NULL_বৃক্ষ;
    }

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_বৃক্ষ;
  decls = NULL_বৃক্ষ;
  যাবত্ (সত্য)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      সংরচনা c_declarator *declarator;
      তার্কিক dummy = অসত্য;
      যদি (c_parser_next_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_বৃক্ষ);
      অন্যথা
	declarator = c_parser_declarator (parser,
					  specs->typespec_kind != ctsk_none,
					  C_DTR_NORMAL, &dummy);
      যদি (declarator == রিক্ত)
	{
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  ভঙ্গ;
	}
      যদি (c_parser_next_token_is (parser, CPP_COLON)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  বৃক্ষ postfix_attrs = NULL_বৃক্ষ;
	  বৃক্ষ width = NULL_বৃক্ষ;
	  বৃক্ষ d;
	  যদি (c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      width = convert_lvalue_to_rvalue (loc,
						(c_parser_রাশিমালা_no_commas
						 (parser, রিক্ত)),
						সত্য, সত্য).মান;
	    }
	  যদি (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_attributes (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, width, &all_prefix_attrs, রাশিমালা);
	  decl_attributes (&d, chainon (postfix_attrs,
					all_prefix_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  যদি (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					prefix_attrs);
	  অন্যথা
	    all_prefix_attrs = prefix_attrs;
	  যদি (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  অন্যথা যদি (c_parser_next_token_is (parser, CPP_SEMICOLON)
		   || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      /* Semicolon consumed in caller.  */
	      ভঙ্গ;
	    }
	  অন্যথা
	    {
	      c_parser_error (parser, "expected %<,%>, %<;%> or %<}%>");
	      ভঙ্গ;
	    }
	}
      অন্যথা
	{
	  c_parser_error (parser,
			  "expected %<:%>, %<,%>, %<;%>, %<}%> or "
			  "%<__attribute__%>");
	  ভঙ্গ;
	}
    }
  প্রত্যাগম decls;
}

/* Parse a typeof specifier (a GNU extension adopted in C23).

   typeof-specifier:
     typeof ( expression )
     typeof ( type-name )
     typeof_unqual ( expression )
     typeof_unqual ( type-name )
*/

স্থির সংরচনা c_typespec
c_parser_typeof_specifier (c_parser *parser)
{
  তার্কিক is_unqual;
  তার্কিক is_std;
  সংরচনা c_typespec ret;
  ret.kind = ctsk_typeof;
  ret.spec = error_mark_গ্রন্থি;
  ret.রাশিমালা = NULL_বৃক্ষ;
  ret.রাশিমালা_const_operands = সত্য;
  ret.has_enum_type_specifier = অসত্য;
  যদি (c_parser_next_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = অসত্য;
      বৃক্ষ spelling = c_parser_peek_token (parser)->মান;
      is_std = (flag_isoc23
		&& strcmp (IDENTIFIER_POINTER (spelling), "typeof") == 0);
    }
  অন্যথা
    {
      gcc_assert (c_parser_next_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = সত্য;
      বৃক্ষ spelling = c_parser_peek_token (parser)->মান;
      is_std = strcmp (IDENTIFIER_POINTER (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_typeof++;
  matching_parens parens;
  যদি (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      প্রত্যাগম ret;
    }
  যদি (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      সংরচনা c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      যদি (type != রিক্ত)
	{
	  ret.spec = groktypename (type, &ret.রাশিমালা, &ret.রাশিমালা_const_operands);
	  বের_করো_maybe_used (c_type_variably_modified_p (ret.spec));
	}
    }
  অন্যথা
    {
      তার্কিক was_vm;
      location_t here = c_parser_peek_token (parser)->location;
      সংরচনা c_রাশিমালা রাশিমালা = c_parser_expression (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      যদি (বৃক্ষ_CODE (রাশিমালা.মান) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (বৃক্ষ_OPERAND (রাশিমালা.মান, 1)))
	error_at (here, "%<typeof%> applied to a bit-field");
      mark_exp_read (রাশিমালা.মান);
      ret.spec = বৃক্ষ_TYPE (রাশিমালা.মান);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      যদি (was_vm)
	ret.রাশিমালা = c_fully_fold (রাশিমালা.মান, অসত্য, &ret.রাশিমালা_const_operands);
      বের_করো_maybe_used (was_vm);
    }
  parens.skip_until_found_close (parser);
  যদি (ret.spec != error_mark_গ্রন্থি)
    {
      যদি (is_unqual)
	{
	  তার্কিক is_array = বৃক্ষ_CODE (ret.spec) == ARRAY_TYPE;
	  পূর্ণাঙ্ক quals = TYPE_QUALS (strip_array_types (ret.spec));
	  যদি ((is_array ? quals & ~TYPE_QUAL_ATOMIC : quals)
	      != TYPE_UNQUALIFIED)
	    {
	      ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	      যদি (quals & TYPE_QUAL_ATOMIC && is_array)
		ret.spec = c_build_qualified_type (ret.spec,
						   TYPE_QUAL_ATOMIC);
	    }
	}
      যদি (is_std)
	{
	  /* In ISO C terms, _Noreturn is not part of the type of
	     expressions such as &abort, but in GCC it is represented
	     internally as a type qualifier.  */
	  যদি (বৃক্ষ_CODE (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  অন্যথা যদি (FUNCTION_POINTER_TYPE_P (ret.spec)
		   && TYPE_QUALS (বৃক্ষ_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_pointer_type (TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (ret.spec)));
	}
    }
  প্রত্যাগম ret;
}

/* Parse an alignment-specifier.

   C11 6.7.5:

   alignment-specifier:
     _Alignas ( type-name )
     _Alignas ( constant-expression )
*/

স্থির বৃক্ষ
c_parser_alignas_specifier (c_parser * parser)
{
  বৃক্ষ ret = error_mark_গ্রন্থি;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNAS));
  বৃক্ষ spelling = c_parser_peek_token (parser)->মান;
  c_parser_consume_token (parser);
  যদি (flag_isoc99)
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  অন্যথা
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম ret;
  যদি (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      সংরচনা c_type_name *type = c_parser_type_name (parser);
      যদি (type != রিক্ত)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, রিক্ত, রিক্ত),
					অসত্য, সত্য, 1);
    }
  অন্যথা
    ret = convert_lvalue_to_rvalue (loc,
				    c_parser_রাশিমালা_no_commas (parser, রিক্ত),
				    সত্য, সত্য).মান;
  parens.skip_until_found_close (parser);
  প্রত্যাগম ret;
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

সংরচনা c_declarator *
c_parser_declarator (c_parser *parser, তার্কিক type_seen_p, c_dtr_syn kind,
		     তার্কিক *seen_id)
{
  /* Parse any initial pointer part.  */
  যদি (c_parser_next_token_is (parser, CPP_MULT))
    {
      সংরচনা c_declspecs *quals_attrs = build_null_declspecs ();
      সংরচনা c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, অসত্য, অসত্য, সত্য,
			  অসত্য, অসত্য, সত্য, অসত্য, cla_prefer_id);
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      যদি (inner == রিক্ত)
	প্রত্যাগম রিক্ত;
      অন্যথা
	প্রত্যাগম make_pointer_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  প্রত্যাগম c_parser_direct_declarator (parser, type_seen_p, kind, seen_id);
}

/* Parse a direct declarator or direct abstract declarator; arguments
   as c_parser_declarator.  */

স্থির সংরচনা c_declarator *
c_parser_direct_declarator (c_parser *parser, তার্কিক type_seen_p, c_dtr_syn kind,
			    তার্কিক *seen_id)
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

  যদি (kind != C_DTR_ABSTRACT
      && c_parser_next_token_is (parser, CPP_NAME)
      && ((type_seen_p
	   && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_kind == C_ID_ID))
    {
      সংরচনা c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->মান);
      *seen_id = সত্য;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      যদি (c_parser_nth_token_starts_std_attributes (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      প্রত্যাগম c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  যদি (kind != C_DTR_NORMAL
      && c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      সংরচনা c_declarator *inner = build_id_declarator (NULL_বৃক্ষ);
      inner->id_loc = c_parser_peek_token (parser)->location;
      প্রত্যাগম c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      বৃক্ষ attrs;
      সংরচনা c_declarator *inner;
      c_parser_consume_token (parser);
      তার্কিক have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      যদি (kind != C_DTR_NORMAL
	  && (c_parser_next_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_attributes (parser, 1)
		      || c_parser_next_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  সংরচনা c_arg_info *args
	    = c_parser_parms_declarator (parser, kind == C_DTR_NORMAL,
					 attrs, have_gnu_attrs);
	  যদি (args == রিক্ত)
	    প্রত্যাগম রিক্ত;
	  অন্যথা
	    {
	      inner = build_id_declarator (NULL_বৃক্ষ);
	      যদি (!(args->types
		    && args->types != error_mark_গ্রন্থি
		    && বৃক্ষ_CODE (বৃক্ষ_মান (args->types)) == IDENTIFIER_গ্রন্থি)
		  && c_parser_nth_token_starts_std_attributes (parser, 1))
		{
		  বৃক্ষ std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  যদি (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (args, inner);
	      প্রত্যাগম c_parser_direct_declarator_inner (parser, *seen_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      যদি (inner != রিক্ত && attrs != রিক্ত)
	inner = build_attrs_declarator (attrs, inner);
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  যদি (inner == রিক্ত)
	    প্রত্যাগম রিক্ত;
	  অন্যথা
	    প্রত্যাগম c_parser_direct_declarator_inner (parser, *seen_id, inner);
	}
      অন্যথা
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  প্রত্যাগম রিক্ত;
	}
    }
  অন্যথা
    {
      যদি (kind == C_DTR_NORMAL)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  প্রত্যাগম রিক্ত;
	}
      অন্যথা
	প্রত্যাগম build_id_declarator (NULL_বৃক্ষ);
    }
}

/* Parse part of a direct declarator or direct abstract declarator,
   given that some (in INNER) has already been parsed; ID_PRESENT is
   true if an identifier is present, false for an abstract
   declarator.  */

স্থির সংরচনা c_declarator *
c_parser_direct_declarator_inner (c_parser *parser, তার্কিক id_present,
				  সংরচনা c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  যদি (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      সংরচনা c_declarator *declarator;
      সংরচনা c_declspecs *quals_attrs = build_null_declspecs ();
      সংরচনা c_রাশিমালা dimen;
      dimen.মান = NULL_বৃক্ষ;
      dimen.original_code = ERROR_MARK;
      dimen.original_type = NULL_বৃক্ষ;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, অসত্য, অসত্য, সত্য,
			  অসত্য, অসত্য, অসত্য, অসত্য, cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      যদি (c_parser_next_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  যদি (!quals_attrs->declspecs_seen_p)
	    c_parser_declspecs (parser, quals_attrs, অসত্য, অসত্য, সত্য,
				অসত্য, অসত্য, অসত্য, অসত্য, cla_prefer_id);
	}
      যদি (!quals_attrs->declspecs_seen_p)
	quals_attrs = রিক্ত;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      ধ্রুব তার্কিক static_seen = (static_loc != UNKNOWN_LOCATION);
      তার্কিক star_seen = অসত্য;
      যদি (c_parser_next_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_SQUARE)
	{
	  star_seen = সত্য;
	  c_parser_consume_token (parser);
	}
      অন্যথা যদি (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	dimen = c_parser_রাশিমালা_no_commas (parser, রিক্ত);

      যদি (static_seen)
	{
	  যদি (star_seen)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      star_seen = অসত্য;
	      dimen.মান = error_mark_গ্রন্থি;
	    }
	  অন্যথা যদি (!dimen.মান)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      যদি (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	c_parser_consume_token (parser);
      অন্যথা
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  প্রত্যাগম রিক্ত;
	}
      যদি (dimen.মান)
	dimen = convert_lvalue_to_rvalue (brace_loc, dimen, সত্য, সত্য);
      declarator = build_array_declarator (brace_loc, dimen.মান, quals_attrs,
					   static_seen, star_seen);
      যদি (declarator == রিক্ত)
	প্রত্যাগম রিক্ত;
      যদি (c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  বৃক্ষ std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  যদি (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = set_array_declarator_inner (declarator, inner);
      প্রত্যাগম c_parser_direct_declarator_inner (parser, id_present, inner);
    }
  অন্যথা যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      বৃক্ষ attrs;
      সংরচনা c_arg_info *args;
      c_parser_consume_token (parser);
      তার্কিক have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      args = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      যদি (args == রিক্ত)
	প্রত্যাগম রিক্ত;
      অন্যথা
	{
	  যদি (!(args->types
		&& args->types != error_mark_গ্রন্থি
		&& বৃক্ষ_CODE (বৃক্ষ_মান (args->types)) == IDENTIFIER_গ্রন্থি)
	      && c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      বৃক্ষ std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      যদি (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (args, inner);
	  প্রত্যাগম c_parser_direct_declarator_inner (parser, id_present, inner);
	}
    }
  প্রত্যাগম inner;
}

/* Parse a parameter list or identifier list, including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list.  ID_LIST_OK is true if an identifier list
   is acceptable; such a list must not have attributes at the start.
   HAVE_GNU_ATTRS says whether any gnu-attributes (including empty
   attributes) were present (in which case standard attributes cannot
   occur).  */

স্থির সংরচনা c_arg_info *
c_parser_parms_declarator (c_parser *parser, তার্কিক id_list_ok, বৃক্ষ attrs,
			   তার্কিক have_gnu_attrs)
{
  ঠেলো_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  যদি (id_list_ok
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
      বৃক্ষ list = NULL_বৃক্ষ, *nextp = &list;
      যাবত্ (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  *nextp = build_বৃক্ষ_list (NULL_বৃক্ষ,
				    c_parser_peek_token (parser)->মান);
	  nextp = & বৃক্ষ_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  যদি (c_parser_next_token_is_not (parser, CPP_COMMA))
	    ভঙ্গ;
	  c_parser_consume_token (parser);
	  যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      ভঙ্গ;
	    }
	}
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  সংরচনা c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  বের_করো_scope ();
	  প্রত্যাগম ret;
	}
      অন্যথা
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  বের_করো_scope ();
	  প্রত্যাগম রিক্ত;
	}
    }
  অন্যথা
    {
      সংরচনা c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, রিক্ত, have_gnu_attrs);
      বের_করো_scope ();
      প্রত্যাগম ret;
    }
}

/* Parse a parameter list (possibly empty), including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list; if HAVE_GNU_ATTRS, there were some such
   attributes (possibly empty, in which case ATTRS is NULL_TREE),
   which means standard attributes cannot start the list.  EXPR is
   NULL or an expression that needs to be evaluated for the side
   effects of array size expressions in the parameters.  */

স্থির সংরচনা c_arg_info *
c_parser_parms_list_declarator (c_parser *parser, বৃক্ষ attrs, বৃক্ষ রাশিমালা,
				তার্কিক have_gnu_attrs)
{
  তার্কিক bad_parm = অসত্য;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      সংরচনা c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      প্রত্যাগম ret;
    }
  যদি (c_parser_next_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      সংরচনা c_arg_info *ret = build_arg_info ();

      ret->types = NULL_বৃক্ষ;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_args_stdarg_p = সত্য;
	  c_parser_consume_token (parser);
	  প্রত্যাগম ret;
	}
      অন্যথা
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  প্রত্যাগম রিক্ত;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  যাবত্ (সত্য)
    {
      /* Parse a parameter.  */
      সংরচনা c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_বৃক্ষ;
      have_gnu_attrs = অসত্য;
      যদি (parm == রিক্ত)
	bad_parm = সত্য;
      অন্যথা
	ঠেলো_parm_decl (parm, &রাশিমালা);
      যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  বৃক্ষ new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  তার্কিক new_have_gnu_attrs
	    = c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_attributes (parser);
	  প্রত্যাগম c_parser_parms_list_declarator (parser, new_attrs, রাশিমালা,
						 new_have_gnu_attrs);
	}
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  যদি (bad_parm)
	    প্রত্যাগম রিক্ত;
	  অন্যথা
	    প্রত্যাগম get_parm_info (অসত্য, রাশিমালা);
	}
      যদি (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, অসত্য))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
	  প্রত্যাগম রিক্ত;
	}
      যদি (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      যদি (bad_parm)
		প্রত্যাগম রিক্ত;
	      অন্যথা
		প্রত্যাগম get_parm_info (সত্য, রাশিমালা);
	    }
	  অন্যথা
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      প্রত্যাগম রিক্ত;
	    }
	}
    }
}

/* Parse a parameter declaration.  ATTRS are the gnu-attributes at the
   start of the declaration if it is the first parameter;
   HAVE_GNU_ATTRS is true if there were any gnu-attributes there (even
   empty) there.  */

স্থির সংরচনা c_parm *
c_parser_parameter_declaration (c_parser *parser, বৃক্ষ attrs,
				তার্কিক have_gnu_attrs)
{
  সংরচনা c_declspecs *specs;
  সংরচনা c_declarator *declarator;
  বৃক্ষ prefix_attrs;
  বৃক্ষ postfix_attrs = NULL_বৃক্ষ;
  তার্কিক dummy = অসত্য;

  /* Accept #pragmas between parameter declarations.  */
  যাবত্ (c_parser_next_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, রিক্ত, NULL_বৃক্ষ);

  যদি (!c_parser_next_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      যদি (parser->error)
	প্রত্যাগম রিক্ত;
      c_parser_set_source_position_from_token (token);
      যদি (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (token->মান,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  যদি (ধ্রুব বর্ণ *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->মান, suggestion);
	    }
	  অন্যথা
	    error_at (token->location, "unknown type name %qE", token->মান);
	  parser->error = সত্য;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      অন্যথা
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_to_end_of_parameter (parser);
      প্রত্যাগম রিক্ত;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  যদি (attrs)
    {
      declspecs_add_attrs (প্রবেশ_location, specs, attrs);
      attrs = NULL_বৃক্ষ;
    }
  c_parser_declspecs (parser, specs, সত্য, সত্য, সত্য, সত্য, অসত্য,
		      !have_gnu_attrs, সত্য, cla_nonabstract_decl);
  finish_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  যদি (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_শীর্ষ_anonymous_type (specs->type);

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  specs->attrs = NULL_বৃক্ষ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_PARM, &dummy);
  যদি (declarator == রিক্ত)
    {
      c_parser_skip_until_found (parser, CPP_COMMA, রিক্ত);
      প্রত্যাগম রিক্ত;
    }
  যদি (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
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
  যাবত্ (id_declarator && id_declarator->kind != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : start_loc);
  location_t param_loc = make_location (caret_loc, start_loc, end_loc);

  প্রত্যাগম build_c_parm (specs, chainon (postfix_attrs, prefix_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

স্থির বৃক্ষ
c_parser_asm_string_literal (c_parser *parser)
{
  বৃক্ষ str;
  পূর্ণাঙ্ক save_flag = warn_overlength_strings;
  warn_overlength_strings = 0;
  str = c_parser_string_literal (parser, অসত্য, অসত্য).মান;
  warn_overlength_strings = save_flag;
  প্রত্যাগম str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

স্থির বৃক্ষ
c_parser_simple_asm_রাশিমালা (c_parser *parser)
{
  বৃক্ষ str;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম NULL_বৃক্ষ;
  str = c_parser_asm_string_literal (parser);
  যদি (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
      প্রত্যাগম NULL_বৃক্ষ;
    }
  প্রত্যাগম str;
}

স্থির বৃক্ষ
c_parser_gnu_attribute_any_word (c_parser *parser)
{
  বৃক্ষ attr_name = NULL_বৃক্ষ;

  যদি (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      /* ??? See comment above about what keywords are accepted here.  */
      তার্কিক ok;
      বিকল্প (c_parser_peek_token (parser)->keyword)
	{
	পক্ষ RID_STATIC:
	পক্ষ RID_UNSIGNED:
	পক্ষ RID_LONG:
	পক্ষ RID_CONST:
	পক্ষ RID_EXTERN:
	পক্ষ RID_REGISTER:
	পক্ষ RID_TYPEDEF:
	পক্ষ RID_SHORT:
	পক্ষ RID_INLINE:
	পক্ষ RID_NORETURN:
	পক্ষ RID_VOLATILE:
	পক্ষ RID_SIGNED:
	পক্ষ RID_AUTO:
	পক্ষ RID_RESTRICT:
	পক্ষ RID_COMPLEX:
	পক্ষ RID_THREAD:
	পক্ষ RID_INT:
	পক্ষ RID_CHAR:
	পক্ষ RID_FLOAT:
	পক্ষ RID_DOUBLE:
	পক্ষ RID_VOID:
	পক্ষ RID_DFLOAT32:
	পক্ষ RID_DFLOAT64:
	পক্ষ RID_DFLOAT128:
	পক্ষ RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	পক্ষ RID_BOOL:
	পক্ষ RID_BITINT:
	পক্ষ RID_FRACT:
	পক্ষ RID_ACCUM:
	পক্ষ RID_SAT:
	পক্ষ RID_TRANSACTION_ATOMIC:
	পক্ষ RID_TRANSACTION_CANCEL:
	পক্ষ RID_ATOMIC:
	পক্ষ RID_AUTO_TYPE:
	পক্ষ RID_CONSTEXPR:
	পক্ষ RID_INT_N_0:
	পক্ষ RID_INT_N_1:
	পক্ষ RID_INT_N_2:
	পক্ষ RID_INT_N_3:
	  ok = সত্য;
	  ভঙ্গ;
	স্বভাব:
	  ok = অসত্য;
	  ভঙ্গ;
	}
      যদি (!ok)
	প্রত্যাগম NULL_বৃক্ষ;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(পূর্ণাঙ্ক) c_parser_peek_token (parser)->keyword];
    }
  অন্যথা যদি (c_parser_next_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->মান;

  প্রত্যাগম attr_name;
}

/* Parse attribute arguments.  This is a common form of syntax
   covering all currently valid GNU and standard attributes.

   gnu-attribute-arguments:
     identifier
     identifier , nonempty-expr-list
     expr-list

   where the "identifier" must not be declared as a type.  ??? Why not
   allow identifiers declared as types to start the arguments?  */

স্থির বৃক্ষ
c_parser_attribute_arguments (c_parser *parser, তার্কিক takes_identifier,
			      তার্কিক require_string, তার্কিক assume_attr,
			      তার্কিক allow_empty_args)
{
  vec<বৃক্ষ, va_gc> *রাশিমালা_list;
  বৃক্ষ attr_args;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  যদি (c_parser_next_token_is (parser, CPP_NAME)
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
      বৃক্ষ arg1 = c_parser_peek_token (parser)->মান;
      c_parser_consume_token (parser);
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	attr_args = build_বৃক্ষ_list (NULL_বৃক্ষ, arg1);
      অন্যথা
	{
	  বৃক্ষ বৃক্ষ_list;
	  c_parser_consume_token (parser);
	  রাশিমালা_list = c_parser_রাশিমালা_list (parser, অসত্য, সত্য,
					  রিক্ত, রিক্ত, রিক্ত, রিক্ত);
	  বৃক্ষ_list = build_বৃক্ষ_list_vec (রাশিমালা_list);
	  attr_args = বৃক্ষ_cons (NULL_বৃক্ষ, arg1, বৃক্ষ_list);
	  release_বৃক্ষ_vector (রাশিমালা_list);
	}
    }
  অন্যথা
    {
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  যদি (!allow_empty_args)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_args = NULL_বৃক্ষ;
	}
      অন্যথা যদি (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  বৃক্ষ string = c_parser_string_literal (parser, অসত্য, সত্য).মান;
	  attr_args = build_বৃক্ষ_list (NULL_বৃক্ষ, string);
	}
      অন্যথা যদি (assume_attr)
	{
	  বৃক্ষ cond
	    = c_parser_conditional_expression (parser, রিক্ত, NULL_বৃক্ষ).মান;
	  যদি (!c_parser_next_token_is (parser, CPP_COMMA))
	    attr_args = build_বৃক্ষ_list (NULL_বৃক্ষ, cond);
	  অন্যথা
	    {
	      বৃক্ষ বৃক্ষ_list;
	      c_parser_consume_token (parser);
	      রাশিমালা_list = c_parser_রাশিমালা_list (parser, অসত্য, সত্য,
					      রিক্ত, রিক্ত, রিক্ত, রিক্ত);
	      বৃক্ষ_list = build_বৃক্ষ_list_vec (রাশিমালা_list);
	      attr_args = বৃক্ষ_cons (NULL_বৃক্ষ, cond, বৃক্ষ_list);
	      release_বৃক্ষ_vector (রাশিমালা_list);
	    }
	}
      অন্যথা
	{
	  রাশিমালা_list = c_parser_রাশিমালা_list (parser, অসত্য, সত্য,
					  রিক্ত, রিক্ত, রিক্ত, রিক্ত);
	  attr_args = build_বৃক্ষ_list_vec (রাশিমালা_list);
	  release_বৃক্ষ_vector (রাশিমালা_list);
	}
    }
  প্রত্যাগম attr_args;
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

স্থির বৃক্ষ
c_parser_gnu_attribute (c_parser *parser, বৃক্ষ attrs,
			তার্কিক expect_comma = অসত্য, তার্কিক empty_ok = সত্য)
{
  তার্কিক comma_first = c_parser_next_token_is (parser, CPP_COMMA);
  যদি (!comma_first
      && !c_parser_next_token_is (parser, CPP_NAME)
      && !c_parser_next_token_is (parser, CPP_KEYWORD))
    প্রত্যাগম NULL_বৃক্ষ;

  যাবত্ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      যদি (!empty_ok)
	প্রত্যাগম attrs;
    }

  বৃক্ষ attr_name = c_parser_gnu_attribute_any_word (parser);
  যদি (attr_name == NULL_বৃক্ষ)
    প্রত্যাগম NULL_বৃক্ষ;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  বৃক্ষ attr;
  যদি (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      যদি (expect_comma && !comma_first)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  প্রত্যাগম error_mark_গ্রন্থি;
	}
      attr = build_বৃক্ষ_list (attr_name, NULL_বৃক্ষ);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      প্রত্যাগম attrs;
    }
  c_parser_consume_token (parser);

  বৃক্ষ attr_args
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    অসত্য,
				    is_attribute_p ("assume", attr_name),
				    সত্য);

  attr = build_বৃক্ষ_list (attr_name, attr_args);
  যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  অন্যথা
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      প্রত্যাগম error_mark_গ্রন্থি;
    }

  যদি (expect_comma && !comma_first)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      প্রত্যাগম error_mark_গ্রন্থি;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  প্রত্যাগম attrs;
}

স্থির বৃক্ষ
c_parser_gnu_attributes (c_parser *parser)
{
  বৃক্ষ attrs = NULL_বৃক্ষ;
  যাবত্ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      তার্কিক save_translate_strings_p = parser->translate_strings_p;
      parser->translate_strings_p = অসত্য;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  প্রত্যাগম attrs;
	}
      যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
	  প্রত্যাগম attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      প্রতি (তার্কিক expect_comma = অসত্য; ; expect_comma = সত্য)
	{
	  /* Parse a single attribute.  */
	  বৃক্ষ attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  যদি (attr == error_mark_গ্রন্থি)
	    প্রত্যাগম attrs;
	  যদি (!attr)
	    ভঙ্গ;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      অন্যথা
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  প্রত্যাগম attrs;
	}
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      অন্যথা
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  প্রত্যাগম attrs;
	}
      parser->translate_strings_p = save_translate_strings_p;
    }

  প্রত্যাগম attrs;
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

স্থির শূন্য
c_parser_balanced_token_sequence (c_parser *parser)
{
  যাবত্ (সত্য)
    {
      c_token *token = c_parser_peek_token (parser);
      বিকল্প (token->type)
	{
	পক্ষ CPP_OPEN_BRACE:
	  {
	    matching_braces braces;
	    braces.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    braces.require_close (parser);
	    ভঙ্গ;
	  }

	পক্ষ CPP_OPEN_PAREN:
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    parens.require_close (parser);
	    ভঙ্গ;
	  }

	পক্ষ CPP_OPEN_SQUARE:
	  c_parser_consume_token (parser);
	  c_parser_balanced_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
	  ভঙ্গ;

	পক্ষ CPP_CLOSE_BRACE:
	পক্ষ CPP_CLOSE_PAREN:
	পক্ষ CPP_CLOSE_SQUARE:
	পক্ষ CPP_EOF:
	  প্রত্যাগম;

	পক্ষ CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, অসত্য);
	  ভঙ্গ;

	স্বভাব:
	  c_parser_consume_token (parser);
	  ভঙ্গ;
	}
    }
}

/* Parse arguments of omp::directive or omp::decl attribute.

   directive-name ,[opt] clause-list[opt]

   For directive just remember the tokens in a vector for subsequent
   parsing.  */

স্থির শূন্য
c_parser_omp_directive_args (c_parser *parser, বৃক্ষ attribute, তার্কিক decl_p)
{
  unsigned পূর্ণাঙ্ক n = 1;
  c_token *first = c_parser_peek_token (parser);
  যদি (!c_parser_check_balanced_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_balanced_token_sequence (parser);
      বৃক্ষ_মান (attribute) = NULL_বৃক্ষ;
      প্রত্যাগম;
    }
  যদি (n == 1)
    {
      error_at (first->location, "expected OpenMP directive name");
      বৃক্ষ_মান (attribute) = NULL_বৃক্ষ;
      প্রত্যাগম;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  প্রতি (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->quick_ঠেলো (*tok);
      c_parser_consume_token (parser);
    }
  বৃক্ষ arg = make_গ্রন্থি (C_TOKEN_VEC);
  C_TOKEN_VEC_TOKENS (arg) = v;
  যদি (decl_p)
    বৃক্ষ_PUBLIC (arg) = 1;
  বৃক্ষ_মান (attribute) = বৃক্ষ_cons (NULL_বৃক্ষ, arg, বৃক্ষ_মান (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

স্থির শূন্য
c_parser_omp_sequence_args (c_parser *parser, বৃক্ষ attribute)
{
  কুরু
    {
      c_token *token = c_parser_peek_token (parser);
      যদি (token->type == CPP_NAME
	  && strcmp (IDENTIFIER_POINTER (token->মান), "omp") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_SCOPE)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  token = c_parser_peek_token (parser);
	}
      তার্কিক directive = অসত্য;
      ধ্রুব বর্ণ *p;
      যদি (token->type != CPP_NAME)
	p = "";
      অন্যথা
	p = IDENTIFIER_POINTER (token->মান);
      যদি (strcmp (p, "directive") == 0)
	directive = সত্য;
      অন্যথা যদি (strcmp (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  unsigned nesting_depth = 0;

	  যাবত্ (সত্য)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      যদি ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_depth)
		ভঙ্গ;
	      /* If we've run out of tokens, stop.  */
	      যদি (token->type == CPP_EOF)
		ভঙ্গ;
	      যদি (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
		ভঙ্গ;
	      যদি (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_SQUARE)
		++nesting_depth;
	      অন্যথা যদি (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_SQUARE)
		{
		  যদি (nesting_depth-- == 0)
		    ভঙ্গ;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  যদি (c_parser_next_token_is_not (parser, CPP_COMMA))
	    ভঙ্গ;
	  c_parser_consume_token (parser);
	  অনুবর্ত;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      যদি (parens.require_open (parser))
	{
	  যদি (directive)
	    c_parser_omp_directive_args (parser, attribute, অসত্য);
	  অন্যথা
	    c_parser_omp_sequence_args (parser, attribute);
	  parens.skip_until_found_close (parser);
	  যদি (c_parser_next_token_is_not (parser, CPP_COMMA))
	    ভঙ্গ;
	  c_parser_consume_token (parser);
	}
      অন্যথা যদি (c_parser_next_token_is_not (parser, CPP_COMMA))
	ভঙ্গ;
      অন্যথা
	c_parser_consume_token (parser);
    }
  যাবত্ (1);
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

স্থির বৃক্ষ
c_parser_std_attribute (c_parser *parser, তার্কিক for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  বৃক্ষ ns, name, attribute;

  /* Parse the attribute-token.  */
  যদি (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      প্রত্যাগম error_mark_গ্রন্থি;
    }
  name = canonicalize_attr_name (token->মান);
  c_parser_consume_token (parser);
  যদি (c_parser_next_token_is (parser, CPP_SCOPE)
      || (c_parser_next_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      যদি (c_parser_next_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      যদি (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  প্রত্যাগম error_mark_গ্রন্থি;
	}
      name = canonicalize_attr_name (token->মান);
      c_parser_consume_token (parser);
    }
  অন্যথা
    ns = NULL_বৃক্ষ;
  attribute = build_বৃক্ষ_list (build_বৃক্ষ_list (ns, name), NULL_বৃক্ষ);

  /* Parse the arguments, if any.  */
  ধ্রুব attribute_spec *as = lookup_attribute_spec (বৃক্ষ_PURPOSE (attribute));
  যদি (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      যদি ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  প্রত্যাগম error_mark_গ্রন্থি;
	}
      গচ্ছ out;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    যদি ((as && as->max_length == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_found_close (parser);
	প্রত্যাগম error_mark_গ্রন্থি;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    যদি (as && !attribute_ignored_p (as))
      {
	তার্কিক takes_identifier
	  = (ns != NULL_বৃক্ষ
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	তার্কিক require_string
	  = (ns == NULL_বৃক্ষ
	     && (strcmp (IDENTIFIER_POINTER (name), "deprecated") == 0
		 || strcmp (IDENTIFIER_POINTER (name), "nodiscard") == 0));
	তার্কিক assume_attr
	  = (ns != NULL_বৃক্ষ
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && strcmp (IDENTIFIER_POINTER (name), "assume") == 0);
	বৃক্ষ_মান (attribute)
	  = c_parser_attribute_arguments (parser, takes_identifier,
					  require_string, assume_attr, অসত্য);
      }
    অন্যথা
      {
	যদি ((flag_openmp || flag_openmp_simd)
	    && ns
	    && is_attribute_p ("omp", ns))
	  {
	    যদি (is_attribute_p ("directive", name))
	      {
		c_parser_omp_directive_args (parser, attribute, অসত্য);
		parens.skip_until_found_close (parser);
		প্রত্যাগম attribute;
	      }
	    অন্যথা যদি (is_attribute_p ("decl", name))
	      {
		বৃক্ষ_মান (বৃক্ষ_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_args (parser, attribute, সত্য);
		parens.skip_until_found_close (parser);
		প্রত্যাগম attribute;
	      }
	    অন্যথা যদি (is_attribute_p ("sequence", name))
	      {
		বৃক্ষ_মান (বৃক্ষ_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_args (parser, attribute);
		parens.skip_until_found_close (parser);
		বৃক্ষ_মান (attribute) = nreverse (বৃক্ষ_মান (attribute));
		প্রত্যাগম attribute;
	      }
	  }
	c_parser_balanced_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 out:
  যদি (ns == NULL_বৃক্ষ && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (প্রবেশ_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      প্রত্যাগম error_mark_গ্রন্থি;
    }
  প্রত্যাগম attribute;
}

স্থির বৃক্ষ
c_parser_std_attribute_list (c_parser *parser, তার্কিক for_tm)
{
  বৃক্ষ attributes = NULL_বৃক্ষ;
  যাবত্ (সত্য)
    {
      c_token *token = c_parser_peek_token (parser);
      যদি (token->type == CPP_CLOSE_SQUARE)
	ভঙ্গ;
      যদি (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  অনুবর্ত;
	}
      বৃক্ষ attribute = c_parser_std_attribute (parser, for_tm);
      যদি (attribute != error_mark_গ্রন্থি)
	{
	  বৃক্ষ_CHAIN (attribute) = attributes;
	  attributes = attribute;
	}
      যদি (c_parser_next_token_is_not (parser, CPP_COMMA))
	ভঙ্গ;
    }
  প্রত্যাগম attributes;
}

স্থির বৃক্ষ
c_parser_std_attribute_specifier (c_parser *parser, তার্কিক for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  যদি (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    প্রত্যাগম NULL_বৃক্ষ;
  যদি (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
      প্রত্যাগম NULL_বৃক্ষ;
    }
  বৃক্ষ attributes;
  যদি (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      auto ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      attributes = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  অন্যথা
    {
      যদি (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      attributes = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  প্রত্যাগম nreverse (attributes);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

স্থির তার্কিক
c_parser_check_balanced_raw_token_sequence (c_parser *parser, unsigned পূর্ণাঙ্ক *n)
{
  যাবত্ (সত্য)
    {
      c_token *token = c_parser_peek_nth_token_raw (parser, *n);
      বিকল্প (token->type)
	{
	পক্ষ CPP_OPEN_BRACE:
	  {
	    ++*n;
	    যদি (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		যদি (token->type == CPP_CLOSE_BRACE)
		  ++*n;
		অন্যথা
		  প্রত্যাগম অসত্য;
	      }
	    অন্যথা
	      প্রত্যাগম অসত্য;
	    ভঙ্গ;
	  }

	পক্ষ CPP_OPEN_PAREN:
	  {
	    ++*n;
	    যদি (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		যদি (token->type == CPP_CLOSE_PAREN)
		  ++*n;
		অন্যথা
		  প্রত্যাগম অসত্য;
	      }
	    অন্যথা
	      প্রত্যাগম অসত্য;
	    ভঙ্গ;
	  }

	পক্ষ CPP_OPEN_SQUARE:
	  {
	    ++*n;
	    যদি (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		যদি (token->type == CPP_CLOSE_SQUARE)
		  ++*n;
		অন্যথা
		  প্রত্যাগম অসত্য;
	      }
	    অন্যথা
	      প্রত্যাগম অসত্য;
	    ভঙ্গ;
	  }

	পক্ষ CPP_CLOSE_BRACE:
	পক্ষ CPP_CLOSE_PAREN:
	পক্ষ CPP_CLOSE_SQUARE:
	পক্ষ CPP_EOF:
	  প্রত্যাগম সত্য;

	স্বভাব:
	  ++*n;
	  ভঙ্গ;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

স্থির তার্কিক
c_parser_nth_token_starts_std_attributes (c_parser *parser, unsigned পূর্ণাঙ্ক n)
{
  যদি (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_SQUARE
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_SQUARE))
    প্রত্যাগম অসত্য;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  যদি (!c_dialect_objc ())
    প্রত্যাগম সত্য;
  n += 2;
  যদি (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    প্রত্যাগম অসত্য;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  যদি (token->type != CPP_CLOSE_SQUARE)
    প্রত্যাগম অসত্য;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  প্রত্যাগম token->type == CPP_CLOSE_SQUARE;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

স্থির size_t
c_parser_skip_std_attribute_spec_seq (c_parser *parser, size_t n)
{
  size_t orig_n = n;
  যাবত্ (সত্য)
    {
      যদি (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_SQUARE
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_SQUARE))
	{
	  unsigned পূর্ণাঙ্ক m = n + 2;
	  যদি (!c_parser_check_balanced_raw_token_sequence (parser, &m))
	    প্রত্যাগম orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  যদি (token->type != CPP_CLOSE_SQUARE)
	    প্রত্যাগম orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  যদি (token->type != CPP_CLOSE_SQUARE)
	    প্রত্যাগম orig_n;
	  n = m + 2;
	}
      অন্যথা
	ভঙ্গ;
    }
  প্রত্যাগম n;
}

স্থির বৃক্ষ
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  বৃক্ষ attributes = NULL_বৃক্ষ;
  কুরু
    {
      বৃক্ষ attrs = c_parser_std_attribute_specifier (parser, অসত্য);
      attributes = chainon (attributes, attrs);
    }
  যাবত্ (c_parser_nth_token_starts_std_attributes (parser, 1));
  প্রত্যাগম attributes;
}

/* Parse a type name (C90 6.5.5, C99 6.7.6, C11 6.7.7).  ALIGNAS_OK
   says whether alignment specifiers are OK (only in cases that might
   be the type name of a compound literal).

   type-name:
     specifier-qualifier-list abstract-declarator[opt]
*/

সংরচনা c_type_name *
c_parser_type_name (c_parser *parser, তার্কিক alignas_ok)
{
  সংরচনা c_declspecs *specs = build_null_declspecs ();
  সংরচনা c_declarator *declarator;
  সংরচনা c_type_name *ret;
  তার্কিক dummy = অসত্য;
  c_parser_declspecs (parser, specs, অসত্য, সত্য, সত্য, alignas_ok, অসত্য,
		      অসত্য, সত্য, cla_prefer_type);
  যদি (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      প্রত্যাগম রিক্ত;
    }
  যদি (specs->type != error_mark_গ্রন্থি)
    {
      pending_xref_error ();
      finish_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      যদি (specs->typespec_kind == ctsk_tagdef)
	verify_counted_by_for_শীর্ষ_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_ABSTRACT, &dummy);
  যদি (declarator == রিক্ত)
    প্রত্যাগম রিক্ত;
  ret = XOBNEW (&parser_obstack, সংরচনা c_type_name);
  ret->specs = specs;
  ret->declarator = declarator;
  প্রত্যাগম ret;
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

স্থির সংরচনা c_রাশিমালা
c_parser_initializer (c_parser *parser, বৃক্ষ decl)
{
  যদি (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    প্রত্যাগম c_parser_braced_init (parser, NULL_বৃক্ষ, অসত্য, রিক্ত,
				 decl != error_mark_গ্রন্থি
				 && C_DECL_VARIABLE_SIZE (decl));
  অন্যথা
    {
      সংরচনা c_রাশিমালা ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      যদি (decl != error_mark_গ্রন্থি && C_DECL_VARIABLE_SIZE (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.set_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      যদি (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !বৃক্ষ_STATIC (decl)
	  && ret.মান == decl
	  && !warning_enabled_at (DECL_SOURCE_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      যদি (বৃক্ষ_CODE (ret.মান) != STRING_CST
	  && (বৃক্ষ_CODE (ret.মান) != COMPOUND_LITERAL_রাশিমালা
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_রাশিমালা_DECL
					    (ret.মান))))
	ret = convert_lvalue_to_rvalue (loc, ret, সত্য, সত্য, সত্য);
      প্রত্যাগম ret;
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

স্থির সংরচনা c_রাশিমালা
c_parser_braced_init (c_parser *parser, বৃক্ষ type, তার্কিক nested_p,
		      সংরচনা obstack *outer_obstack, তার্কিক varsize_p)
{
  সংরচনা c_রাশিমালা ret;
  সংরচনা obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  তার্কিক save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = অসত্য;
  তার্কিক zero_init_padding_bits = অসত্য;
  matching_braces braces;
  braces.consume_open (parser);
  যদি (nested_p)
    {
      finish_implicit_inits (brace_loc, outer_obstack);
      ঠেলো_init_level (brace_loc, 0, &braced_init_obstack);
    }
  অন্যথা
    really_start_incremental_init (type);
  যদি (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      যদি (flag_isoc23)
	zero_init_padding_bits = সত্য;
    }
  অন্যথা
    {
      যদি (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      যাবত্ (সত্য)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  যদি (parser->error)
	    ভঙ্গ;
	  যদি (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      last_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      যাবত্ (c_parser_next_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_রাশিমালা embed_val;
		  embed_val.মান = embed->মান;
		  embed_val.original_code = RAW_DATA_CST;
		  embed_val.original_type = integer_type_গ্রন্থি;
		  set_c_রাশিমালা_source_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, অসত্য,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_next_token_is (parser,
							       CPP_COMMA));
		  last_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  অন্যথা
	    ভঙ্গ;
	  যদি (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    ভঙ্গ;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *next_tok = c_parser_peek_token (parser);
  যদি (next_tok->type != CPP_CLOSE_BRACE)
    {
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = রিক্ত;
      braces.skip_until_found_close (parser);
      বের_করো_init_level (brace_loc, 0, &braced_init_obstack, last_init_list_comma);
      obstack_free (&braced_init_obstack, রিক্ত);
      প্রত্যাগম ret;
    }
  location_t close_loc = next_tok->location;
  c_parser_consume_token (parser);
  ret = বের_করো_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  যদি (zero_init_padding_bits
      && ret.মান
      && বৃক্ষ_CODE (ret.মান) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_BITS (ret.মান) = 1;
  obstack_free (&braced_init_obstack, রিক্ত);
  set_c_রাশিমালা_source_range (&ret, brace_loc, close_loc);
  প্রত্যাগম ret;
}

/* Parse a nested initializer, including designators.  */

স্থির শূন্য
c_parser_initelt (c_parser *parser, সংরচনা obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  যদি (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      set_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->মান,
		      c_parser_peek_token (parser)->location,
		      braced_init_obstack);
      /* Use the colon as the error location.  */
      pedwarn (c_parser_peek_2nd_token (parser)->location, OPT_Wpedantic,
	       "obsolete use of designated initializer with %<:%>");
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  অন্যথা
    {
      /* des_seen is 0 if there have been no designators, 1 if there
	 has been a single array designator and 2 otherwise.  */
      পূর্ণাঙ্ক des_seen = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      যাবত্ (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
	     || c_parser_next_token_is (parser, CPP_DOT))
	{
	  পূর্ণাঙ্ক des_prev = des_seen;
	  যদি (!des_seen)
	    des_loc = c_parser_peek_token (parser)->location;
	  যদি (des_seen < 2)
	    des_seen++;
	  যদি (c_parser_next_token_is (parser, CPP_DOT))
	    {
	      des_seen = 2;
	      c_parser_consume_token (parser);
	      যদি (c_parser_next_token_is (parser, CPP_NAME))
		{
		  set_init_label (des_loc, c_parser_peek_token (parser)->মান,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      অন্যথা
		{
		  সংরচনা c_রাশিমালা init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = রিক্ত;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_found (parser, CPP_COMMA, রিক্ত);
		  process_init_element (প্রবেশ_location, init, অসত্য,
					braced_init_obstack);
		  প্রত্যাগম;
		}
	    }
	  অন্যথা
	    {
	      সংরচনা c_রাশিমালা first_রাশিমালা;
	      বৃক্ষ first, second;
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
	      যদি (des_prev == 1 && c_dialect_objc ())
		{
		  des_seen = des_prev;
		  ভঙ্গ;
		}
	      যদি (des_prev == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  বৃক্ষ rec, args;
		  সংরচনা c_রাশিমালা mexpr;
		  c_parser_consume_token (parser);
		  যদি (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_kind
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_kind
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      বৃক্ষ id = c_parser_peek_token (parser)->মান;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      গচ্ছ parse_message_args;
		    }
		  array_index_loc = c_parser_peek_token (parser)->location;
		  first_রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
		  mark_exp_read (first_রাশিমালা.মান);
		  যদি (c_parser_next_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    গচ্ছ array_desig_after_first;
		  first = first_রাশিমালা.মান;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = first;
		  যাবত্ (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      সংরচনা c_রাশিমালা next;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      next = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
		      next = convert_lvalue_to_rvalue (exp_loc, next,
						       সত্য, সত্য);
		      rec = build_compound_রাশিমালা (comma_loc, rec, next.মান);
		    }
		parse_message_args:
		  /* Now parse the objc-message-args.  */
		  args = c_parser_objc_message_args (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					     "expected %<]%>");
		  mexpr.মান
		    = objc_build_message_রাশিমালা (rec, args);
		  mexpr.original_code = ERROR_MARK;
		  mexpr.original_type = রিক্ত;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  প্রত্যাগম;
		}
	      c_parser_consume_token (parser);
	      array_index_loc = c_parser_peek_token (parser)->location;
	      first_রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	      mark_exp_read (first_রাশিমালা.মান);
	    array_desig_after_first:
	      first_রাশিমালা = convert_lvalue_to_rvalue (array_index_loc,
						     first_রাশিমালা,
						     সত্য, সত্য);
	      first = first_রাশিমালা.মান;
	      যদি (c_parser_next_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  second = convert_lvalue_to_rvalue (ellipsis_loc,
						     (c_parser_রাশিমালা_no_commas
						      (parser, রিক্ত)),
						     সত্য, সত্য).মান;
		  mark_exp_read (second);
		}
	      অন্যথা
		second = NULL_বৃক্ষ;
	      যদি (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		{
		  c_parser_consume_token (parser);
		  set_init_index (array_index_loc, first, second,
				  braced_init_obstack);
		  যদি (second)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      অন্যথা
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					   "expected %<]%>");
	    }
	}
      যদি (des_seen >= 1)
	{
	  যদি (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  অন্যথা
	    {
	      যদি (des_seen == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      অন্যথা
		{
		  সংরচনা c_রাশিমালা init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = রিক্ত;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_found (parser, CPP_COMMA, রিক্ত);
		  process_init_element (প্রবেশ_location, init, অসত্য,
					braced_init_obstack);
		  প্রত্যাগম;
		}
	    }
	}
    }
  c_parser_initval (parser, রিক্ত, braced_init_obstack);
}

/* Parse a nested initializer; as c_parser_initializer but parses
   initializers within braced lists, after any designators have been
   applied.  If AFTER is not NULL then it is an Objective-C message
   expression which is the primary-expression starting the
   initializer.  */

স্থির শূন্য
c_parser_initval (c_parser *parser, সংরচনা c_রাশিমালা *after,
		  সংরচনা obstack * braced_init_obstack)
{
  সংরচনা c_রাশিমালা init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  যদি (c_parser_next_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_বৃক্ষ, সত্য,
				 braced_init_obstack, অসত্য);
  অন্যথা
    {
      init = c_parser_রাশিমালা_no_commas (parser, after);
      যদি (init.মান != NULL_বৃক্ষ
	  && বৃক্ষ_CODE (init.মান) != STRING_CST
	  && (বৃক্ষ_CODE (init.মান) != COMPOUND_LITERAL_রাশিমালা
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_রাশিমালা_DECL
					    (init.মান))))
	init = convert_lvalue_to_rvalue (loc, init, সত্য, সত্য, সত্য);
    }
  বৃক্ষ val = init.মান;
  process_init_element (loc, init, অসত্য, braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  স্থির unsigned vals_to_ignore;
  যদি (vals_to_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_to_ignore;
  অন্যথা যদি (val
	   && বৃক্ষ_CODE (val) == INTEGER_CST
	   && বৃক্ষ_TYPE (val) == integer_type_গ্রন্থি
	   && c_parser_next_token_is (parser, CPP_COMMA))
    যদি (unsigned পূর্ণাঙ্ক len = c_maybe_optimize_large_byte_initializer ())
      {
	বর্ণ buf1[64];
	unsigned পূর্ণাঙ্ক i;
	gcc_checking_assert (len >= 64);
	location_t last_loc = UNKNOWN_LOCATION;
	প্রতি (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    যদি (tok->type != CPP_COMMA)
	      ভঙ্গ;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    যদি (tok->type != CPP_সংখ্যা
		|| বৃক্ষ_CODE (tok->মান) != INTEGER_CST
		|| বৃক্ষ_TYPE (tok->মান) != integer_type_গ্রন্থি
		|| wi::neg_p (wi::to_wide (tok->মান))
		|| wi::to_widest (tok->মান) > UCHAR_MAX)
	      ভঙ্গ;
	    buf1[i] = (বর্ণ) বৃক্ষ_to_uhwi (tok->মান);
	    যদি (i == 0)
	      loc = tok->location;
	    last_loc = tok->location;
	  }
	যদি (i < 64)
	  {
	    vals_to_ignore = i;
	    প্রত্যাগম;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	যদি (tok->type == CPP_CLOSE_BRACE && len != INT_MAX)
	  len = i;
	অন্যথা যদি (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_সংখ্যা))
	  {
	    vals_to_ignore = i;
	    প্রত্যাগম;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	unsigned পূর্ণাঙ্ক max_len = 131072 - offsetof (সংরচনা বৃক্ষ_string, str) - 1;
	unsigned পূর্ণাঙ্ক orig_len = len;
	unsigned পূর্ণাঙ্ক off = 0, last = 0;
	যদি (!wi::neg_p (wi::to_wide (val)) && wi::to_widest (val) <= UCHAR_MAX)
	  off = 1;
	len = MIN (len, max_len - off);
	বর্ণ *buf2 = XNEWVEC (বর্ণ, len + off);
	যদি (off)
	  buf2[0] = (বর্ণ) বৃক্ষ_to_uhwi (val);
	memcpy (buf2 + off, buf1, i);
	প্রতি (unsigned পূর্ণাঙ্ক j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	প্রতি (; i < len; ++i)
	  {
	    যদি (!c_parser_next_token_is (parser, CPP_COMMA))
	      ভঙ্গ;
	    tok = c_parser_peek_2nd_token (parser);
	    যদি (tok->type != CPP_সংখ্যা
		|| বৃক্ষ_CODE (tok->মান) != INTEGER_CST
		|| বৃক্ষ_TYPE (tok->মান) != integer_type_গ্রন্থি
		|| wi::neg_p (wi::to_wide (tok->মান))
		|| wi::to_widest (tok->মান) > UCHAR_MAX)
	      ভঙ্গ;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    যদি (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      ভঙ্গ;
	    buf2[i + off] = (বর্ণ) বৃক্ষ_to_uhwi (tok->মান);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    যদি (orig_len == INT_MAX
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_সংখ্যা)))
	      {
		last = 1;
		ভঙ্গ;
	      }
	    last_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_গ্রন্থি (RAW_DATA_CST);
	বৃক্ষ_TYPE (val) = integer_type_গ্রন্থি;
	RAW_DATA_LENGTH (val) = i;
	বৃক্ষ owner = build_string (i + off + last, buf2);
	XDELETEVEC (buf2);
	বৃক্ষ_TYPE (owner) = build_array_type_nelts (unsigned_char_type_গ্রন্থি,
						    i + off + last);
	RAW_DATA_OWNER (val) = owner;
	RAW_DATA_POINTER (val) = বৃক্ষ_STRING_POINTER (owner) + off;
	init.মান = val;
	set_c_রাশিমালা_source_range (&init, loc, last_loc);
	init.original_code = RAW_DATA_CST;
	init.original_type = integer_type_গ্রন্থি;
	init.m_decimal = 0;
	process_init_element (loc, init, অসত্য, braced_init_obstack);
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

স্থির বৃক্ষ
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  বৃক্ষ stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  যদি (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (সত্য);
      c_end_compound_stmt (brace_loc, stmt, সত্য);
      প্রত্যাগম error_mark_গ্রন্থি;
    }
  stmt = c_begin_compound_stmt (সত্য);
  location_t end_loc = c_parser_compound_statement_nostart (parser);
  যদি (endlocp)
    *endlocp = end_loc;

  প্রত্যাগম c_end_compound_stmt (brace_loc, stmt, সত্য);
}

/* Diagnose errors related to imperfectly nested loops in an OMP
   loop construct.  This function is called when such code is seen.
   Only issue one such diagnostic no matter how much invalid
   intervening code there is in the loop.
   FIXME: maybe the location associated with the diagnostic should
   be the current parser token instead of the location of the outer loop
   nest.  */

স্থির শূন্য
check_omp_intervening_code (c_parser *parser)
{
  সংরচনা omp_for_parse_data *omp_for_parse_state = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);

  যদি (!omp_for_parse_state->in_intervening_code)
    প্রত্যাগম;
  omp_for_parse_state->saw_intervening_code = সত্য;

  /* Only diagnose errors related to perfect nesting once.  */
  যদি (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      যদি (omp_for_parse_state->code == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = সত্য;
	}
      অন্যথা যদি (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = সত্য;
	}
      অন্যথা যদি (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = সত্য;
	}
      অন্যথা যদি (omp_for_parse_state->code == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = সত্য;
	}
      যদি (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->fail = সত্য;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
স্থির শূন্য
add_structured_block_stmt (বৃক্ষ sl)
{
  যদি (বৃক্ষ_CODE (sl) != STATEMENT_LIST
      || !tsi_end_p (tsi_start (sl)))
    add_stmt (build1 (OMP_STRUCTURED_BLOCK, void_type_গ্রন্থি, sl));
}

সংরচনা c_omp_attribute_data
{
  vec<c_token, va_gc> *tokens;
  ধ্রুব c_omp_directive *dir;
  c_omp_directive_kind kind;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

স্থির তার্কিক
c_parser_handle_statement_omp_attributes (c_parser *parser, বৃক্ষ &attrs,
					  তার্কিক *have_std_attrs)
{
  যদি (!flag_openmp && !flag_openmp_simd)
    প্রত্যাগম অসত্য;

  auto_vec<c_omp_attribute_data, 16> vd;
  পূর্ণাঙ্ক cnt = 0;
  পূর্ণাঙ্ক tokens = 0;
  তার্কিক bad = অসত্য;
  প্রতি (বৃক্ষ *pa = &attrs; *pa; )
    যদি (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	প্রতি (বৃক্ষ a = বৃক্ষ_মান (*pa); a; a = বৃক্ষ_CHAIN (a))
	  {
	    বৃক্ষ d = বৃক্ষ_মান (a);
	    gcc_assert (বৃক্ষ_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    যদি (parser->omp_attrs_forbidden_p)
	      {
		error_at (first->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = অসত্য;
		bad = সত্য;
	      }
	    অন্যথা যদি (বৃক্ষ_PUBLIC (d))
	      {
		error_at (first->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		bad = সত্য;
	      }
	    ধ্রুব বর্ণ *directive[3] = {};
	    প্রতি (পূর্ণাঙ্ক i = 0; i < 3; i++)
	      {
		বৃক্ষ id = NULL_বৃক্ষ;
		যদি (first + i == last)
		  ভঙ্গ;
		যদি (first[i].type == CPP_NAME)
		  id = first[i].মান;
		অন্যথা যদি (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(পূর্ণাঙ্ক) first[i].keyword];
		অন্যথা
		  ভঙ্গ;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    ধ্রুব c_omp_directive *dir = রিক্ত;
	    যদি (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    যদি (dir == রিক্ত)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  বৃক্ষ_PUBLIC (d) ? "omp::decl" : "omp::directive");
		অনুবর্ত;
	      }
	    c_omp_directive_kind kind = dir->kind;
	    যদি (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		যদি (directive[1]
		    && (strcmp (directive[1], "depend") == 0
			|| strcmp (directive[1], "doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
		অন্যথা যদি (first + 2 < last
			 && first[1].type == CPP_COMMA
			 && first[2].type == CPP_NAME
			 && (strcmp (IDENTIFIER_POINTER (first[2].মান),
				     "depend") == 0
			     || strcmp (IDENTIFIER_POINTER (first[2].মান),
					"doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
	      }
	    অন্যথা যদি (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		পূর্ণাঙ্ক paren_depth = 0;
		প্রতি (পূর্ণাঙ্ক i = 1; first + i < last; i++)
		  যদি (first[i].type == CPP_OPEN_PAREN)
		    paren_depth++;
		  অন্যথা যদি (first[i].type == CPP_CLOSE_PAREN)
		    paren_depth--;
		  অন্যথা যদি (paren_depth == 0
			   && first + i + 2 < last
			   && first[i].type == CPP_NAME
			   && first[i + 1].type == CPP_OPEN_PAREN
			   && first[i + 2].type == CPP_NAME
			   && !strcmp (IDENTIFIER_POINTER (first[i].মান),
				       "at")
			   && !strcmp (IDENTIFIER_POINTER (first[i
								 + 2].মান),
				       "execution"))
		    {
		      kind = C_OMP_DIR_STANDALONE;
		      ভঙ্গ;
		    }
	      }
	    c_omp_attribute_data v = { toks, dir, kind };
	    vd.safe_ঠেলো (v);
	    যদি (flag_openmp || dir->simd)
	      tokens += (last - first) + 1;
	  }
	c_omp_attribute_data v = {};
	vd.safe_ঠেলো (v);
	*pa = বৃক্ষ_CHAIN (*pa);
      }
    অন্যথা
      pa = &বৃক্ষ_CHAIN (*pa);

  যদি (bad)
    {
    fail:
      যদি (have_std_attrs && attrs == রিক্ত)
	*have_std_attrs = অসত্য;
      প্রত্যাগম অসত্য;
    }

  unsigned পূর্ণাঙ্ক i;
  c_omp_attribute_data *v;
  c_omp_attribute_data *construct_seen = nullptr;
  c_omp_attribute_data *standalone_seen = nullptr;
  c_omp_attribute_data *prev_standalone_seen = nullptr;
  FOR_EACH_VEC_ELT (vd, i, v)
    যদি (v->tokens)
      {
	যদি (v->kind == C_OMP_DIR_CONSTRUCT && !construct_seen)
	  construct_seen = v;
	অন্যথা যদি (v->kind == C_OMP_DIR_STANDALONE && !standalone_seen)
	  standalone_seen = v;
      }
    অন্যথা
      {
	যদি (standalone_seen && !prev_standalone_seen)
	  {
	    prev_standalone_seen = standalone_seen;
	    standalone_seen = nullptr;
	  }
      }

  যদি (cnt > 1 && construct_seen)
    {
      error_at ((*construct_seen->tokens)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      গচ্ছ fail;
    }
  যদি (cnt > 1 && standalone_seen && prev_standalone_seen)
    {
      error_at ((*standalone_seen->tokens)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      গচ্ছ fail;
    }

  যদি (prev_standalone_seen)
    standalone_seen = prev_standalone_seen;
  যদি (standalone_seen
      && !c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_seen->tokens->address ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      গচ্ছ fail;
    }
  যদি (cnt && c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      গণনা pragma_kind kind = token->pragma_kind;
      যদি (kind >= PRAGMA_OMP__START_ && kind <= PRAGMA_OMP__LAST_)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  গচ্ছ fail;
	}
    }

  যদি (!tokens)
    প্রত্যাগম অসত্য;

  unsigned পূর্ণাঙ্ক tokens_avail = parser->tokens_avail;

  tokens++;
  vec<c_token, va_gc> *toks = রিক্ত;
  vec_safe_reserve (toks, tokens, সত্য);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      যদি (!v->tokens)
	অনুবর্ত;
      যদি (!flag_openmp && !v->dir->simd)
	অনুবর্ত;
      c_token *first = v->tokens->address ();
      c_token *last = first + v->tokens->length ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_kind = pragma_kind (v->dir->id);
      tok.location = first->location;
      toks->quick_ঠেলো (tok);
      যাবত্ (++first < last)
	toks->quick_ঠেলো (*first);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = last[-1].location;
      toks->quick_ঠেলো (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->last ().location;
  toks->quick_ঠেলো (tok);

  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = tokens;
  প্রত্যাগম সত্য;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

স্থির শূন্য
c_parser_handle_directive_omp_attributes (বৃক্ষ &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  যদি (!flag_openmp && !flag_openmp_simd)
    প্রত্যাগম;

  প্রতি (বৃক্ষ *pa = &attrs; *pa; )
    যদি (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	পূর্ণাঙ্ক cnt = 0;
	প্রতি (বৃক্ষ *pa2 = &বৃক্ষ_মান (*pa); *pa2; )
	  {
	    বৃক্ষ a = *pa2;
	    বৃক্ষ d = বৃক্ষ_মান (a);
	    gcc_assert (বৃক্ষ_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    ধ্রুব বর্ণ *directive[3] = {};
	    প্রতি (পূর্ণাঙ্ক i = 0; i < 3; i++)
	      {
		বৃক্ষ id = NULL_বৃক্ষ;
		যদি (first + i == last)
		  ভঙ্গ;
		যদি (first[i].type == CPP_NAME)
		  id = first[i].মান;
		অন্যথা যদি (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(পূর্ণাঙ্ক) first[i].keyword];
		অন্যথা
		  ভঙ্গ;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    ধ্রুব c_omp_directive *dir = রিক্ত;
	    যদি (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    যদি (dir == রিক্ত)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  বৃক্ষ_PUBLIC (d) ? "omp::decl" : "omp::directive");
		*pa2 = বৃক্ষ_CHAIN (a);
	      }
	    অন্যথা যদি (dir->id == PRAGMA_OMP_DECLARE
		     && (strcmp (directive[1], "simd") == 0
			 || strcmp (directive[1], "variant") == 0))
	      {
		যদি (pragma_clauses)
		  {
		    error_at (first->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    প্রতি (pa = &attrs; *pa; )
		      যদি (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = বৃক্ষ_CHAIN (*pa);
		      অন্যথা
			pa = &বৃক্ষ_CHAIN (*pa);
		    প্রত্যাগম;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->length ()
				       + toks->length () + 2);
		প্রতি (++first; first < last; ++first)
		  attr_clauses->quick_ঠেলো (*first);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = last[-1].location;
		attr_clauses->quick_ঠেলো (tok);
		*pa2 = বৃক্ষ_CHAIN (a);
	      }
	    অন্যথা
	      pa2 = &বৃক্ষ_CHAIN (a);
	  }
	যদি (cnt && বৃক্ষ_মান (*pa) == NULL_বৃক্ষ)
	  *pa = বৃক্ষ_CHAIN (*pa);
	অন্যথা
	  pa = &বৃক্ষ_CHAIN (*pa);
      }
    অন্যথা
      pa = &বৃক্ষ_CHAIN (*pa);
  যদি (attr_clauses->length ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->last ().location;
      attr_clauses->quick_ঠেলো (tok);
      attr_clauses->quick_ঠেলো (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

স্থির বৃক্ষ
c_parser_handle_musttail (c_parser *parser, বৃক্ষ std_attrs, attr_state &attr)
{
  যদি (c_parser_next_token_is_keyword (parser, RID_RETURN))
    {
      যদি (বৃক্ষ a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  প্রতি (; a; a = lookup_attribute ("gnu", "musttail", বৃক্ষ_CHAIN (a)))
	    যদি (বৃক্ষ_মান (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = সত্য;
	}
      যদি (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = সত্য;
	}
    }
  প্রত্যাগম std_attrs;
}

/* Return a statement before optional series of LABEL_EXPR/CASE_LABEL_EXPRs.
   Instead of collecting vectors of labels before each stmt just in case
   the statement would be iteration or switch statement for named loops,
   we just remember last emitted statement and let the iteration/switch
   statement search backwards in cur_stmt_list until that stmt for loop
   names if any.  */

স্থির বৃক্ষ
get_before_labels ()
{
  যদি (!building_stmt_list_p ())
    প্রত্যাগম NULL_বৃক্ষ;
  বৃক্ষ_stmt_iterator tsi = tsi_last (cur_stmt_list);
  যদি (tsi_end_p (tsi))
    প্রত্যাগম NULL_বৃক্ষ;
  প্রত্যাগম tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

স্থির location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  তার্কিক last_stmt = অসত্য;
  তার্কিক last_label = অসত্য;
  তার্কিক save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  সংরচনা omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  তার্কিক in_omp_loop_block
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : অসত্য;
  বৃক্ষ sl = NULL_বৃক্ষ;
  attr_state astate = {};

  যদি (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      add_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      প্রত্যাগম endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  যদি (in_omp_loop_block)
    sl = ঠেলো_stmt_list ();

  mark_valid_location_for_stdc_pragma (সত্য);
  যদি (c_parser_next_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (অসত্য);
      যদি (in_omp_loop_block)
	check_omp_intervening_code (parser);
      যাবত্ (c_parser_next_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  যাবত্ (সত্য)
	    {
	      বৃক্ষ label;
	      যদি (c_parser_next_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  ভঙ্গ;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->মান);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      add_stmt (build_stmt (label_loc, DECL_রাশিমালা, label));
	      c_parser_consume_token (parser);
	      যদি (c_parser_next_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      অন্যথা
		ভঙ্গ;
	    }
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  যদি (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      প্রত্যাগম endloc;
    }
  বৃক্ষ before_labels = get_before_labels ();
  যাবত্ (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_point_location_if_in_system_header (loc);

      তার্কিক want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : অসত্য);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      যদি (in_omp_loop_block && !last_label)
	{
	  বৃক্ষ_code code = omp_for_parse_state->code;
	  যদি (want_nested_loop
	      && c_parser_omp_next_tokens_can_be_canon_loop (parser, code,
							     অসত্য))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      add_structured_block_stmt (বের_করো_stmt_list (sl));
	      omp_for_parse_state->depth++;
	      add_stmt (c_parser_omp_loop_nest (parser, রিক্ত));
	      omp_for_parse_state->depth--;
	      sl = ঠেলো_stmt_list ();
	      parser->error = অসত্য;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      অনুবর্ত;
	    }
	  অন্যথা যদি (want_nested_loop
		   && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      বৃক্ষ pre_sl = বের_করো_stmt_list (sl);
	      বৃক্ষ nested_sl = ঠেলো_stmt_list ();
	      mark_valid_location_for_stdc_pragma (অসত্য);
	      c_parser_statement_after_labels (parser, রিক্ত, NULL_বৃক্ষ);
	      nested_sl = বের_করো_stmt_list (nested_sl);
	      যদি (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_code (parser);
		  sl = ঠেলো_stmt_list ();
		  add_stmt (pre_sl);
		  add_stmt (nested_sl);
		}
	      অন্যথা
		{
		  /* It contains the nested loop.  */
		  add_structured_block_stmt (pre_sl);
		  add_stmt (nested_sl);
		  sl = ঠেলো_stmt_list ();
		}
	      parser->error = অসত্য;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      অনুবর্ত;
	    }
	  অন্যথা যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      /* Prior to implementing the OpenMP 5.1 syntax for canonical
		 loop form, GCC used to accept an empty statements that
		 would now be flagged as intervening code.  Continue to
		 do that, as an extension.  */
	      /* FIXME:  Maybe issue a warning or something here?  */
	      c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
	      অনুবর্ত;
	    }
	}

      /* Standard attributes may start a label, statement or declaration.  */
      তার্কিক have_std_attrs
	= c_parser_nth_token_starts_std_attributes (parser, 1);
      বৃক্ষ std_attrs = NULL_বৃক্ষ;
      যদি (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      যদি (c_parser_next_token_is_keyword (parser, RID_CASE)
	  || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  যদি (c_parser_next_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  অন্যথা
	    label_loc = c_parser_peek_token (parser)->location;
	  last_label = সত্য;
	  last_stmt = অসত্য;
	  mark_valid_location_for_stdc_pragma (অসত্য);
	  যদি (in_omp_loop_block)
	    check_omp_intervening_code (parser);
	  c_parser_label (parser, std_attrs);
	}
      অন্যথা যদি (c_parser_next_tokens_start_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_attributes
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_next_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = সত্য)))
	{
	  যদি (last_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  যদি (in_omp_loop_block)
	    {
	      check_omp_intervening_code (parser);
	      omp_for_parse_state->want_nested_loop = অসত্য;
	    }
	  mark_valid_location_for_stdc_pragma (অসত্য);
	  তার্কিক fallthru_attr_p = অসত্য;
	  c_parser_declaration_or_fndef (parser, সত্য, !have_std_attrs,
					 সত্য, সত্য, সত্য, অসত্য, রিক্ত,
					 রিক্ত, have_std_attrs, std_attrs,
					 রিক্ত, &fallthru_attr_p);

	  যদি (in_omp_loop_block)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  যদি (last_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  last_stmt = fallthru_attr_p;
	  last_label = অসত্য;
	  before_labels = get_before_labels ();
	}
      অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  If standard attributes have already
	     been seen, it must start a statement, not a declaration,
	     but standard attributes starting a declaration may appear
	     after __extension__.  */
	  যাবত্ (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  যদি (!have_std_attrs
	      && (c_parser_next_tokens_start_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_attributes (parser, 2)))
	    {
	      পূর্ণাঙ্ক ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      last_label = অসত্য;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      যদি (in_omp_loop_block)
		{
		  check_omp_intervening_code (parser);
		  omp_for_parse_state->want_nested_loop = অসত্য;
		}
	      mark_valid_location_for_stdc_pragma (অসত্য);
	      c_parser_declaration_or_fndef (parser, সত্য, সত্য, সত্য, সত্য,
					     সত্য, অসত্য);
	      যদি (in_omp_loop_block)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      যদি (last_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      last_stmt = অসত্য;
	      before_labels = get_before_labels ();
	    }
	  অন্যথা
	    গচ্ছ statement;
	}
      অন্যথা যদি (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  যদি (have_std_attrs && !parser->in_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  অন্যথা যদি (std_attrs)
	    c_warn_unused_attributes (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  যদি (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = অসত্য;
	  যদি (c_parser_pragma (parser,
			       last_label ? pragma_stmt : pragma_compound,
			       রিক্ত, before_labels))
	    {
	      last_label = অসত্য;
	      last_stmt = সত্য;
	      যদি (omp_for_parse_state)
		check_omp_intervening_code (parser);
	    }
	  যদি (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      অন্যথা যদি (c_parser_next_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  প্রত্যাগম c_parser_peek_token (parser)->location;
	}
      অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_ELSE))
        {
          যদি (parser->in_if_block)
            {
	      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	      error_at (loc, "expected %<}%> before %<else%>");
	      প্রত্যাগম c_parser_peek_token (parser)->location;
            }
          অন্যথা
            {
              error_at (loc, "%<else%> without a previous %<if%>");
              c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
              অনুবর্ত;
            }
        }
      অন্যথা
	{
	statement:
	  c_warn_unused_attributes (std_attrs);
	  last_label = অসত্য;
	  last_stmt = সত্য;
	  mark_valid_location_for_stdc_pragma (অসত্য);
	  যদি (!omp_for_parse_state)
	    c_parser_statement_after_labels (parser, রিক্ত, before_labels,
					     রিক্ত, astate);
	  অন্যথা
	    {
	      /* In canonical loop nest form, nested loops can only appear
		 directly, or in a directly nested compound statement.  We
		 already took care of those cases above, so now we have
		 something else.  This statement and everything inside
		 it must be intervening code.  */
	      omp_for_parse_state->want_nested_loop = অসত্য;
	      check_omp_intervening_code (parser);
	      c_parser_statement_after_labels (parser, রিক্ত, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = অসত্য;
      astate.reset ();
    }
  যদি (last_label)
    pedwarn_c11 (label_loc, OPT_Wfree_labels,
		 "label at end of compound statement");
  location_t endloc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  /* Restore the value we started with.  */
  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);

  /* Package leftover intervening code, or the whole contents of the
     compound statement if we were looking for a nested loop in an OMP_FOR
     construct and didn't find one.  */
  যদি (sl)
    {
      sl = বের_করো_stmt_list (sl);
      যদি (omp_for_parse_state->want_nested_loop)
	add_stmt (sl);
      অন্যথা
	add_structured_block_stmt (sl);
    }
  প্রত্যাগম endloc;
}

/* Parse all consecutive labels, possibly preceded by standard
   attributes.  In this context, a statement is required, not a
   declaration, so attributes must be followed by a statement that is
   not just a semicolon.  Returns an attr_state.  */

স্থির attr_state
c_parser_all_labels (c_parser *parser)
{
  attr_state attr = {};
  তার্কিক have_std_attrs;
  বৃক্ষ std_attrs = রিক্ত;
  যদি ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  যাবত্ (c_parser_next_token_is_keyword (parser, RID_CASE)
	 || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = রিক্ত;
      যদি ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  যদি (std_attrs
      && (!c_parser_handle_statement_omp_attributes (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      যদি (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_unused_attributes (std_attrs);
    }
  অন্যথা যদি (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  প্রত্যাগম attr;
}


/* Information used while parsing an OpenMP metadirective.  */
সংরচনা omp_metadirective_parse_data {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<বৃক্ষ> * GTY((skip)) body_labels;
  unsigned পূর্ণাঙ্ক region_অঙ্ক;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
স্থির বৃক্ষ
mangle_metadirective_region_label (c_parser *parser, বৃক্ষ name)
{
  যদি (parser->omp_metadirective_state->body_labels->contains (name))
    {
      ধ্রুব বর্ণ *old_name = IDENTIFIER_POINTER (name);
      বর্ণ *new_name = (বর্ণ *) XALLOCAVEC (বর্ণ, strlen (old_name) + 32);
      sprintf (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_অঙ্ক);
      প্রত্যাগম get_identifier (new_name);
    }
  প্রত্যাগম name;
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
স্থির শূন্য
c_parser_label (c_parser *parser, বৃক্ষ std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  বৃক্ষ label = NULL_বৃক্ষ;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  তার্কিক fallthrough_p = c_parser_peek_token (parser)->flags & PREV_FALLTHROUGH;

  যদি (c_parser_next_token_is_keyword (parser, RID_CASE))
    {
      বৃক্ষ exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_to_rvalue (loc1,
				       c_parser_রাশিমালা_no_commas (parser, রিক্ত),
				       সত্য, সত্য).মান;
      যদি (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_বৃক্ষ, std_attrs);
	}
      অন্যথা যদি (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_to_rvalue (loc1,
					   c_parser_রাশিমালা_no_commas (parser,
								    রিক্ত),
					   সত্য, সত্য).মান;
	  যদি (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      অন্যথা
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      যদি (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_বৃক্ষ, NULL_বৃক্ষ, std_attrs);
    }
  অন্যথা
    {
      বৃক্ষ name = c_parser_peek_token (parser)->মান;
      বৃক্ষ tlab;
      বৃক্ষ attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_attributes (parser);
      যদি (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      যদি (tlab)
	{
	  decl_attributes (&tlab, attrs, 0);
	  decl_attributes (&tlab, std_attrs, 0);
	  label = add_stmt (build_stmt (loc1, LABEL_রাশিমালা, tlab));
	}
      যদি (attrs
	  && c_parser_next_tokens_start_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  যদি (label)
    {
      যদি (বৃক্ষ_CODE (label) == LABEL_রাশিমালা)
	FALLTHROUGH_LABEL_P (LABEL_রাশিমালা_LABEL (label)) = fallthrough_p;
      অন্যথা
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

স্থির শূন্য
c_parser_statement (c_parser *parser, তার্কিক *if_p, location_t *loc_after_labels)
{
  বৃক্ষ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  যদি (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = অসত্য;
  c_parser_statement_after_labels (parser, if_p, before_labels, রিক্ত, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

স্থির বৃক্ষ
c_parser_bc_name (c_parser *parser, তার্কিক is_break)
{
  যদি (!c_parser_next_token_is (parser, CPP_NAME))
    প্রত্যাগম NULL_বৃক্ষ;

  c_token *tok = c_parser_peek_token (parser);
  বৃক্ষ label = c_finish_bc_name (tok->location, tok->মান, is_break);
  c_parser_consume_token (parser);
  প্রত্যাগম label;
}

/* Parse a statement, other than a labeled statement.  CHAIN is a vector
   of if-else-if conditions.  All labels and standard attributes have
   been parsed in the caller.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  ASTATE is an earlier parsed attribute state.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

স্থির শূন্য
c_parser_statement_after_labels (c_parser *parser, তার্কিক *if_p,
				 বৃক্ষ before_labels,
				 vec<বৃক্ষ> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  বৃক্ষ stmt = NULL_বৃক্ষ;
  তার্কিক in_if_block = parser->in_if_block;
  parser->in_if_block = অসত্য;
  যদি (if_p != রিক্ত)
    *if_p = অসত্য;

  যদি (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    add_debug_begin_stmt (loc);

 restart:
  বিকল্প (c_parser_peek_token (parser)->type)
    {
    পক্ষ CPP_OPEN_BRACE:
      add_stmt (c_parser_compound_statement (parser));
      ভঙ্গ;
    পক্ষ CPP_KEYWORD:
      বিকল্প (c_parser_peek_token (parser)->keyword)
	{
	পক্ষ RID_IF:
	  c_parser_if_statement (parser, if_p, chain);
	  ভঙ্গ;
	পক্ষ RID_SWITCH:
	  c_parser_switch_statement (parser, if_p, before_labels);
	  ভঙ্গ;
	পক্ষ RID_WHILE:
	  c_parser_while_statement (parser, অসত্য, 0, অসত্য, if_p, before_labels);
	  ভঙ্গ;
	পক্ষ RID_DO:
	  c_parser_do_statement (parser, অসত্য, 0, অসত্য, before_labels);
	  ভঙ্গ;
	পক্ষ RID_FOR:
	  c_parser_for_statement (parser, অসত্য, 0, অসত্য, if_p, before_labels);
	  ভঙ্গ;
	পক্ষ RID_GOTO:
	  c_parser_consume_token (parser);
	  যদি (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      বৃক্ষ name = c_parser_peek_token (parser)->মান;
	      যদি (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_finish_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  অন্যথা যদি (c_parser_next_token_is (parser, CPP_MULT))
	    {
	      সংরচনা c_রাশিমালা val;

	      c_parser_consume_token (parser);
	      val = c_parser_expression (parser);
	      val = convert_lvalue_to_rvalue (loc, val, অসত্য, সত্য);
	      stmt = c_finish_goto_ptr (loc, val);
	    }
	  অন্যথা
	    c_parser_error (parser, "expected identifier or %<*%>");
	  গচ্ছ expect_semicolon;
	পক্ষ RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_continue_label, অসত্য,
				   c_parser_bc_name (parser, অসত্য));
	  গচ্ছ expect_semicolon;
	পক্ষ RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_break_label, সত্য,
				   c_parser_bc_name (parser, সত্য));
	  গচ্ছ expect_semicolon;
	পক্ষ RID_RETURN:
	  c_parser_consume_token (parser);
	  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_finish_return (loc, NULL_বৃক্ষ, NULL_বৃক্ষ,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  অন্যথা
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      সংরচনা c_রাশিমালা রাশিমালা = c_parser_expression_conv (parser);
	      mark_exp_read (রাশিমালা.মান);
	      stmt = c_finish_return (রাশিমালা_LOC_OR_LOC (রাশিমালা.মান, xloc),
				      রাশিমালা.মান, রাশিমালা.original_type,
				      astate.musttail_p);
	      গচ্ছ expect_semicolon;
	    }
	  ভঙ্গ;
	পক্ষ RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  ভঙ্গ;
	পক্ষ RID_TRANSACTION_ATOMIC:
	পক্ষ RID_TRANSACTION_RELAXED:
	  stmt = c_parser_transaction (parser,
	      c_parser_peek_token (parser)->keyword);
	  ভঙ্গ;
	পক্ষ RID_TRANSACTION_CANCEL:
	  stmt = c_parser_transaction_cancel (parser);
	  গচ্ছ expect_semicolon;
	পক্ষ RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_বৃক্ষ);
	      c_parser_consume_token (parser);
	    }
	  অন্যথা
	    {
	      সংরচনা c_রাশিমালা রাশিমালা = c_parser_expression (parser);
	      রাশিমালা = convert_lvalue_to_rvalue (loc, রাশিমালা, অসত্য, অসত্য);
	      রাশিমালা.মান = c_fully_fold (রাশিমালা.মান, অসত্য, রিক্ত);
	      stmt = objc_build_throw_stmt (loc, রাশিমালা.মান);
	      গচ্ছ expect_semicolon;
	    }
	  ভঙ্গ;
	পক্ষ RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_finally_statement (parser);
	  ভঙ্গ;
	পক্ষ RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  ভঙ্গ;
	পক্ষ RID_ATTRIBUTE:
	  {
	    /* Allow '__attribute__((fallthrough));' or
	       '__attribute__((assume(cond)));' or
	       '__attribute__((musttail))) return'.  */
	    বৃক্ষ attrs = c_parser_gnu_attributes (parser);
	    তার্কিক has_assume = lookup_attribute ("assume", attrs);
	    যদি (has_assume)
	      {
		যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, সত্য);
		অন্যথা
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<assume%> attribute not followed by %<;%>");
		    has_assume = অসত্য;
		  }
	      }
	    gcc_assert (!astate.musttail_p);
	    attrs = c_parser_handle_musttail (parser, attrs, astate);
	    যদি (astate.musttail_p)
	      {
		যদি (attrs)
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		গচ্ছ restart;
	      }
	    যদি (attribute_fallthrough_p (attrs))
	      {
		যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  {
		    বৃক্ষ fn = build_call_রাশিমালা_internal_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_গ্রন্থি, 0);
		    add_stmt (fn);
		    /* Eat the ';'.  */
		    c_parser_consume_token (parser);
		  }
		অন্যথা
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<fallthrough%> attribute not followed "
				"by %<;%>");
		  }
	      }
	    অন্যথা যদি (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    অন্যথা যদি (attrs != NULL_বৃক্ষ)
	      {
		auto_urlify_attributes sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    ভঙ্গ;
	  }
	স্বভাব:
	  গচ্ছ রাশিমালা_stmt;
	}
      ভঙ্গ;
    পক্ষ CPP_SEMICOLON:
      c_parser_consume_token (parser);
      ভঙ্গ;
    পক্ষ CPP_CLOSE_PAREN:
    পক্ষ CPP_CLOSE_SQUARE:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      ভঙ্গ;
    পক্ষ CPP_PRAGMA:
      যদি (!c_parser_pragma (parser, pragma_stmt, if_p, before_labels))
        গচ্ছ restart;
      ভঙ্গ;
    স্বভাব:
    রাশিমালা_stmt:
      stmt = c_finish_রাশিমালা_stmt (loc, c_parser_expression_conv (parser).মান);
    expect_semicolon:
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      ভঙ্গ;
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
  যদি (রাশিমালা_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_set_রাশিমালা_location (stmt, loc);

  parser->in_if_block = in_if_block;
}

/* Parse the condition from an if, do, while or for statements.  */

স্থির বৃক্ষ
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  বৃক্ষ cond;
  cond = c_parser_expression_conv (parser).মান;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, অসত্য, রিক্ত);
  যদি (warn_sequence_point)
    verify_sequence_points (cond);
  প্রত্যাগম cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

স্থির বৃক্ষ
c_parser_paren_condition (c_parser *parser)
{
  বৃক্ষ cond;
  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম error_mark_গ্রন্থি;
  cond = c_parser_condition (parser);
  parens.skip_until_found_close (parser);
  প্রত্যাগম cond;
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

স্থির c_রাশিমালা
c_parser_selection_header (c_parser *parser, তার্কিক switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_রাশিমালা রাশিমালা;
  তার্কিক parse_রাশিমালা = সত্য;
  বৃক্ষ std_attrs;
  তার্কিক have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  যদি (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  অন্যথা
    std_attrs = NULL_বৃক্ষ;
  যদি (c_parser_next_tokens_start_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      রাশিমালা.মান
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/অসত্য,
					 /*static_assert_ok=*/অসত্য,
					 /*empty_ok=*/অসত্য,
					 /*nested=*/সত্য,
					 /*start_attr_ok=*/সত্য,
					 /*simple_ok=*/সত্য,
					 /*objc_foreach_object_decl=*/nullptr,
					 /*omp_declare_simd_clauses=*/nullptr,
					 have_std_attrs,
					 std_attrs);
      যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      অন্যথা
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  যদি (!রাশিমালা.মান)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      রাশিমালা.original_type = error_mark_গ্রন্থি;
	      রাশিমালা.set_error ();
	      প্রত্যাগম রাশিমালা;
	    }
	  parse_রাশিমালা = অসত্য;
	}
      যদি (রাশিমালা.মান)
	{
	  রাশিমালা.original_type = বৃক্ষ_TYPE (রাশিমালা.মান);
	  রাশিমালা = convert_lvalue_to_rvalue (loc, রাশিমালা, /*convert_p=*/সত্য,
					   /*read_p=*/সত্য);
	}
    }
  অন্যথা যদি (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      রাশিমালা.original_type = error_mark_গ্রন্থি;
      রাশিমালা.set_error ();
      প্রত্যাগম রাশিমালা;
    }

  যদি (parse_রাশিমালা)
    রাশিমালা = c_parser_expression_conv (parser);
  যদি (!switch_p)
    {
      রাশিমালা.মান = c_objc_common_truthvalue_conversion (loc, রাশিমালা.মান);
      রাশিমালা.মান = c_fully_fold (রাশিমালা.মান, অসত্য, রিক্ত);
      যদি (warn_sequence_point)
	verify_sequence_points (রাশিমালা.মান);
    }
  প্রত্যাগম রাশিমালা;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

স্থির বৃক্ষ
c_parser_paren_selection_header (c_parser *parser)
{
  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম error_mark_গ্রন্থি;
  বৃক্ষ cond = c_parser_selection_header (parser, /*switch_p=*/অসত্য).মান;
  parens.skip_until_found_close (parser);
  প্রত্যাগম cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

স্থির বৃক্ষ
c_parser_c99_block_statement (c_parser *parser, তার্কিক *if_p,
			      location_t *loc_after_labels)
{
  বৃক্ষ block = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  প্রত্যাগম c_end_compound_stmt (loc, block, flag_isoc99);
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

স্থির বৃক্ষ
c_parser_if_body (c_parser *parser, তার্কিক *if_p,
		  ধ্রুব token_indent_info &if_tinfo)
{
  বৃক্ষ block = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  বৃক্ষ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
      যদি (!c_parser_next_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  অন্যথা যদি (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    add_stmt (c_parser_compound_statement (parser));
  অন্যথা
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, রিক্ত, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, next_tinfo);
  যদি (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    if_tinfo.location, RID_IF);

  প্রত্যাগম c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

স্থির বৃক্ষ
c_parser_else_body (c_parser *parser, ধ্রুব token_indent_info &else_tinfo,
		    vec<বৃক্ষ> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  বৃক্ষ block = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  বৃক্ষ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      warning_at (loc,
		  OPT_Wempty_body,
	         "suggest braces around empty body in an %<else%> statement");
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
    }
  অন্যথা
    {
      যদি (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, রিক্ত, before_labels, chain, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, next_tinfo);
  যদি (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  প্রত্যাগম c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse an if statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   if-statement:
     if ( selection-header ) statement
     if ( selection-header ) statement else statement

   CHAIN is a vector of if-else-if conditions.
   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

স্থির শূন্য
c_parser_if_statement (c_parser *parser, তার্কিক *if_p, vec<বৃক্ষ> *chain)
{
  বৃক্ষ block;
  location_t loc;
  বৃক্ষ cond;
  তার্কিক nested_if = অসত্য;
  বৃক্ষ first_body, second_body;
  তার্কিক in_if_block;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_IF));
  token_indent_info if_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_selection_header (parser);
  in_if_block = parser->in_if_block;
  parser->in_if_block = সত্য;
  first_body = c_parser_if_body (parser, &nested_if, if_tinfo);
  parser->in_if_block = in_if_block;

  যদি (warn_duplicated_cond)
    warn_duplicated_cond_add_or_warn (রাশিমালা_LOCATION (cond), cond, &chain);

  যদি (c_parser_next_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      যদি (warn_duplicated_cond)
	{
	  যদি (c_parser_next_token_is_keyword (parser, RID_IF)
	      && chain == রিক্ত)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = নূতন vec<বৃক্ষ> ();
	      যদি (!CONSTANT_CLASS_P (cond) && !বৃক্ষ_SIDE_EFFECTS (cond))
		chain->safe_ঠেলো (cond);
	    }
	  অন্যথা যদি (!c_parser_next_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      second_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      যদি (if_p != রিক্ত)
	*if_p = সত্য;
    }
  অন্যথা
    {
      second_body = NULL_বৃক্ষ;

      /* Diagnose an ambiguous else if if-then-else is nested inside
	 if-then.  */
      যদি (nested_if)
	warning_at (loc, OPT_Wdangling_else,
		    "suggest explicit braces to avoid ambiguous %<else%>");

      যদি (warn_duplicated_cond)
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

স্থির শূন্য
c_parser_switch_statement (c_parser *parser, তার্কিক *if_p, বৃক্ষ before_labels)
{
  সংরচনা c_রাশিমালা ce;
  বৃক্ষ block, রাশিমালা, body;
  unsigned বর্ণ save_in_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  বৃক্ষ switch_name;
  পূর্ণাঙ্ক অঙ্ক_names = c_get_loop_names (before_labels, সত্য, &switch_name);
  block = c_begin_compound_stmt (flag_isoc99);
  তার্কিক explicit_cast_p = অসত্য;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = সত্য;
      ce = c_parser_selection_header (parser, /*switch_p=*/সত্য);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_to_rvalue (switch_cond_loc, ce, সত্য, সত্য);
      রাশিমালা = ce.মান;
      /* ??? expr has no valid location?  */
      parens.skip_until_found_close (parser);
    }
  অন্যথা
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      রাশিমালা = error_mark_গ্রন্থি;
      ce.original_type = error_mark_গ্রন্থি;
    }
  বৃক্ষ stmt
    = c_start_switch (switch_loc, switch_cond_loc, রাশিমালা, explicit_cast_p,
		      switch_name);
  save_in_statement = in_statement;
  in_statement |= IN_SWITCH_STMT;
  যদি (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  অন্যথা
    in_statement &= ~IN_NAMED_STMT;
  location_t loc_after_labels;
  তার্কিক open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  location_t next_loc = c_parser_peek_token (parser)->location;
  যদি (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, next_loc, switch_loc,
				    RID_SWITCH);
  c_finish_switch (body, ce.original_type);
  in_statement = save_in_statement;
  যদি (অঙ্ক_names)
    {
      যদি (!C_DECL_LOOP_SWITCH_NAME_USED (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_বৃক্ষ;
      অন্যথা
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_names (অঙ্ক_names);
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

স্থির শূন্য
c_parser_while_statement (c_parser *parser, তার্কিক ivdep, unsigned short unroll,
			  তার্কিক novector, তার্কিক *if_p, বৃক্ষ before_labels)
{
  বৃক্ষ block, cond, body;
  unsigned বর্ণ save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  বৃক্ষ loop_name;
  পূর্ণাঙ্ক অঙ্ক_names = c_get_loop_names (before_labels, অসত্য, &loop_name);

  যদি (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = সত্য;
    }

  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  যদি (ivdep && cond != error_mark_গ্রন্থি)
    cond = build3 (ANNOTATE_রাশিমালা, বৃক্ষ_TYPE (cond), cond,
		   build_int_cst (integer_type_গ্রন্থি,
				  annot_রাশিমালা_ivdep_kind),
		   integer_zero_গ্রন্থি);
  যদি (unroll && cond != error_mark_গ্রন্থি)
    cond = build3 (ANNOTATE_রাশিমালা, বৃক্ষ_TYPE (cond), cond,
		   build_int_cst (integer_type_গ্রন্থি,
				  annot_রাশিমালা_unroll_kind),
		   build_int_cst (integer_type_গ্রন্থি, unroll));
  যদি (novector && cond != error_mark_গ্রন্থি)
    cond = build3 (ANNOTATE_রাশিমালা, বৃক্ষ_TYPE (cond), cond,
		   build_int_cst (integer_type_গ্রন্থি,
				  annot_রাশিমালা_no_vector_kind),
		   integer_zero_গ্রন্থি);
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  যদি (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  তার্কিক open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  যদি (loop_name && !C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
    loop_name = NULL_বৃক্ষ;
  add_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_বৃক্ষ,
			NULL_বৃক্ষ));
  add_stmt (c_end_compound_stmt (loc, block, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  যদি (অঙ্ক_names)
    c_release_loop_names (অঙ্ক_names);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, next_tinfo);

  যদি (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    while_tinfo.location, RID_WHILE);

  in_statement = save_in_statement;
}

/* Parse a do statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   do-statement:
     do statement while ( expression ) ;

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

স্থির শূন্য
c_parser_do_statement (c_parser *parser, তার্কিক ivdep, unsigned short unroll,
		       তার্কিক novector, বৃক্ষ before_labels)
{
  বৃক্ষ block, cond, body;
  unsigned বর্ণ save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_DO));
  বৃক্ষ loop_name;
  পূর্ণাঙ্ক অঙ্ক_names = c_get_loop_names (before_labels, অসত্য, &loop_name);

  যদি (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = সত্য;
    }

  c_parser_consume_token (parser);
  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  যদি (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  body = c_parser_c99_block_statement (parser, রিক্ত);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  in_statement = save_in_statement;
  যদি (অঙ্ক_names)
    {
      যদি (!C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
	loop_name = NULL_বৃক্ষ;
      c_release_loop_names (অঙ্ক_names);
    }
  cond = c_parser_paren_condition (parser);
  যদি (ivdep && cond != error_mark_গ্রন্থি)
    cond = build3 (ANNOTATE_রাশিমালা, বৃক্ষ_TYPE (cond), cond,
		   build_int_cst (integer_type_গ্রন্থি,
				  annot_রাশিমালা_ivdep_kind),
		   integer_zero_গ্রন্থি);
  যদি (unroll && cond != error_mark_গ্রন্থি)
    cond = build3 (ANNOTATE_রাশিমালা, বৃক্ষ_TYPE (cond), cond,
		   build_int_cst (integer_type_গ্রন্থি,
				  annot_রাশিমালা_unroll_kind),
 		   build_int_cst (integer_type_গ্রন্থি, unroll));
  যদি (novector && cond != error_mark_গ্রন্থি)
    cond = build3 (ANNOTATE_রাশিমালা, বৃক্ষ_TYPE (cond), cond,
		   build_int_cst (integer_type_গ্রন্থি,
				  annot_রাশিমালা_no_vector_kind),
		   integer_zero_গ্রন্থি);
  যদি (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
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

স্থির শূন্য
c_parser_for_statement (c_parser *parser, তার্কিক ivdep, unsigned short unroll,
			তার্কিক novector, তার্কিক *if_p, বৃক্ষ before_labels)
{
  বৃক্ষ block, cond, incr, body;
  unsigned বর্ণ save_in_statement;
  বৃক্ষ save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  বৃক্ষ object_expression;
  /* Silence the bogus uninitialized warning.  */
  বৃক্ষ collection_expression = রিক্ত;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  তার্কিক is_foreach_statement = অসত্য;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  বৃক্ষ loop_name;
  পূর্ণাঙ্ক অঙ্ক_names = c_get_loop_names (before_labels, অসত্য, &loop_name);

  যদি (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = সত্য;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  block = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_গ্রন্থি;
  incr = error_mark_গ্রন্থি;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_expression = error_mark_গ্রন্থি;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = অসত্য;
	  c_parser_consume_token (parser);
	  c_finish_রাশিমালা_stmt (loc, NULL_বৃক্ষ);
	}
      অন্যথা যদি (c_parser_next_tokens_start_declaration (parser)
	       || c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, সত্য, সত্য, সত্য, সত্য, সত্য,
					 অসত্য, &object_expression);
	  parser->objc_could_be_foreach_context = অসত্য;

	  যদি (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = সত্য;
	      যদি (check_for_loop_decls (for_loc, সত্য) == NULL_বৃক্ষ)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  অন্যথা
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  যাবত্ (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  যদি (c_parser_next_tokens_start_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_attributes (parser, 2))
	    {
	      পূর্ণাঙ্ক ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, সত্য, সত্য, সত্য, সত্য,
					     সত্য, অসত্য, &object_expression);
	      parser->objc_could_be_foreach_context = অসত্য;

	      restore_extension_diagnostics (ext);
	      যদি (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = সত্য;
		  যদি (check_for_loop_decls (for_loc, সত্য) == NULL_বৃক্ষ)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      অন্যথা
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  অন্যথা
	    গচ্ছ init_রাশিমালা;
	}
      অন্যথা
	{
	init_রাশিমালা:
	  {
	    সংরচনা c_রাশিমালা ce;
	    বৃক্ষ init_expression;
	    ce = c_parser_expression (parser);
	    init_expression = ce.মান;
	    parser->objc_could_be_foreach_context = অসত্য;
	    যদি (c_parser_next_token_is_keyword (parser, RID_IN))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = সত্য;
		যদি (! lvalue_p (init_expression))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_expression
		  = c_fully_fold (init_expression, অসত্য, রিক্ত);
	      }
	    অন্যথা
	      {
		ce = convert_lvalue_to_rvalue (loc, ce, সত্য, অসত্য);
		init_expression = ce.মান;
		c_finish_রাশিমালা_stmt (loc, init_expression);
		c_parser_skip_until_found (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      যদি (!is_foreach_statement)
	{
	  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      যদি (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_গ্রন্থি;
		}
	      অন্যথা যদি (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_গ্রন্থি;
		}
	      অন্যথা
		{
		  c_parser_consume_token (parser);
		  cond = NULL_বৃক্ষ;
		}
	    }
	  অন্যথা
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_found (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  যদি (ivdep && cond != error_mark_গ্রন্থি)
	    cond = build3 (ANNOTATE_রাশিমালা, বৃক্ষ_TYPE (cond), cond,
			   build_int_cst (integer_type_গ্রন্থি,
					  annot_রাশিমালা_ivdep_kind),
			   integer_zero_গ্রন্থি);
	  যদি (unroll && cond != error_mark_গ্রন্থি)
	    cond = build3 (ANNOTATE_রাশিমালা, বৃক্ষ_TYPE (cond), cond,
 			   build_int_cst (integer_type_গ্রন্থি,
					  annot_রাশিমালা_unroll_kind),
			   build_int_cst (integer_type_গ্রন্থি, unroll));
	  যদি (novector && cond && cond != error_mark_গ্রন্থি)
	    cond = build3 (ANNOTATE_রাশিমালা, বৃক্ষ_TYPE (cond), cond,
			   build_int_cst (integer_type_গ্রন্থি,
					  annot_রাশিমালা_no_vector_kind),
			   integer_zero_গ্রন্থি);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  যদি (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_expression = error_mark_গ্রন্থি;
	    }
	  অন্যথা
	    incr = c_process_রাশিমালা_stmt (loc, NULL_বৃক্ষ);
	}
      অন্যথা
	{
	  যদি (is_foreach_statement)
	    collection_expression
	      = c_fully_fold (c_parser_expression (parser).মান, অসত্য, রিক্ত);
	  অন্যথা
	    {
	      সংরচনা c_রাশিমালা ce = c_parser_expression (parser);
	      ce = convert_lvalue_to_rvalue (loc, ce, সত্য, অসত্য);
	      incr = c_process_রাশিমালা_stmt (loc, ce.মান);
	    }
	}
      parens.skip_until_found_close (parser);
    }
  save_in_statement = in_statement;
  যদি (is_foreach_statement)
    {
      in_statement = IN_OBJC_FOREACH;
      save_objc_foreach_break_label = objc_foreach_break_label;
      save_objc_foreach_continue_label = objc_foreach_continue_label;
      objc_foreach_break_label = create_artificial_label (loc);
      objc_foreach_continue_label = create_artificial_label (loc);
      যদি (loop_name)
	{
	  gcc_checking_assert (!DECL_CHAIN (loop_name)
			       && !DECL_CHAIN (objc_foreach_break_label));
	  C_DECL_SWITCH_NAME (loop_name) = 1;
	  DECL_CHAIN (loop_name) = objc_foreach_break_label;
	  DECL_CHAIN (objc_foreach_break_label) = objc_foreach_continue_label;
	}
    }
  অন্যথা
    in_statement = IN_ITERATION_STMT;
  যদি (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  তার্কিক open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);

  যদি (loop_name && is_foreach_statement)
    {
      gcc_checking_assert (DECL_CHAIN (loop_name) == objc_foreach_break_label
			   && (DECL_CHAIN (objc_foreach_break_label)
			       == objc_foreach_continue_label));
      C_DECL_SWITCH_NAME (loop_name) = 0;
      DECL_CHAIN (loop_name) = NULL_বৃক্ষ;
      DECL_CHAIN (objc_foreach_break_label) = NULL_বৃক্ষ;
    }

  যদি (is_foreach_statement)
    objc_finish_foreach_loop (for_loc, object_expression,
			      collection_expression, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  অন্যথা
    add_stmt (build_stmt (for_loc, FOR_STMT, NULL_বৃক্ষ, cond, incr,
			  body, NULL_বৃক্ষ,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_USED (loop_name)
			  ? loop_name : NULL_বৃক্ষ, NULL_বৃক্ষ, NULL_বৃক্ষ));
  add_stmt (c_end_compound_stmt (for_loc, block,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, next_tinfo);

  যদি (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    for_tinfo.location, RID_FOR);

  in_statement = save_in_statement;
  যদি (অঙ্ক_names)
    c_release_loop_names (অঙ্ক_names);
  যদি (is_foreach_statement)
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

স্থির বৃক্ষ
c_parser_asm_statement (c_parser *parser)
{
  বৃক্ষ str, outputs, inputs, clobbers, labels, ret;
  তার্কিক simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  পূর্ণাঙ্ক section, nsections;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);

  /* Handle the asm-qualifier-list.  */
  location_t volatile_loc = UNKNOWN_LOCATION;
  location_t inline_loc = UNKNOWN_LOCATION;
  location_t goto_loc = UNKNOWN_LOCATION;
  প্রতি (;;)
    {
      c_token *token = c_parser_peek_token (parser);
      location_t loc = token->location;
      বিকল্প (token->keyword)
	{
	পক্ষ RID_VOLATILE:
	  যদি (volatile_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->মান);
	      inform (volatile_loc, "first seen here");
	    }
	  অন্যথা
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  অনুবর্ত;

	পক্ষ RID_INLINE:
	  যদি (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->মান);
	      inform (inline_loc, "first seen here");
	    }
	  অন্যথা
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  অনুবর্ত;

	পক্ষ RID_GOTO:
	  যদি (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->মান);
	      inform (goto_loc, "first seen here");
	    }
	  অন্যথা
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  অনুবর্ত;

	পক্ষ RID_CONST:
	পক্ষ RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->মান);
	  c_parser_consume_token (parser);
	  অনুবর্ত;

	স্বভাব:
	  ভঙ্গ;
	}
      ভঙ্গ;
    }

  তার্কিক is_volatile = (volatile_loc != UNKNOWN_LOCATION);
  তার্কিক is_inline = (inline_loc != UNKNOWN_LOCATION);
  তার্কিক is_goto = (goto_loc != UNKNOWN_LOCATION);

  ret = রিক্ত;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    গচ্ছ error;

  str = c_parser_asm_string_literal (parser);
  যদি (str == NULL_বৃক্ষ)
    গচ্ছ error_close_paren;

  simple = সত্য;
  outputs = NULL_বৃক্ষ;
  inputs = NULL_বৃক্ষ;
  clobbers = NULL_বৃক্ষ;
  labels = NULL_বৃক্ষ;

  যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    গচ্ছ done_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  প্রতি (section = 0; section < nsections; ++section)
    {
      যদি (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  যদি (section == nsections)
	    {
	      c_parser_error (parser, "expected %<)%>");
	      গচ্ছ error_close_paren;
	    }
	  c_parser_consume_token (parser);
	}
      অন্যথা যদি (!c_parser_require (parser, CPP_COLON,
				  is_goto
				  ? G_("expected %<:%>")
				  : G_("expected %<:%> or %<)%>"),
				  UNKNOWN_LOCATION, is_goto))
	গচ্ছ error_close_paren;

      /* Once past any colon, we're no longer a simple asm.  */
      simple = অসত্য;

      যদি ((!c_parser_next_token_is (parser, CPP_COLON)
	   && !c_parser_next_token_is (parser, CPP_SCOPE)
	   && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	  || section == 3)
	বিকল্প (section)
	  {
	  পক্ষ 0:
	    outputs = c_parser_asm_operands (parser);
	    ভঙ্গ;
	  পক্ষ 1:
	    inputs = c_parser_asm_operands (parser);
	    ভঙ্গ;
	  পক্ষ 2:
	    clobbers = c_parser_asm_clobbers (parser);
	    ভঙ্গ;
	  পক্ষ 3:
	    labels = c_parser_asm_goto_operands (parser);
	    ভঙ্গ;
	  স্বভাব:
	    gcc_unreachable ();
	  }

      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	গচ্ছ done_asm;
    }

 done_asm:
  যদি (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
      গচ্ছ error;
    }

  যদি (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_to_end_of_block_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_রাশিমালা (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  প্রত্যাগম ret;

 error_close_paren:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
  গচ্ছ error;
}

/* Parse asm operands, a GNU extension.

   asm-operands:
     asm-operand
     asm-operands , asm-operand

   asm-operand:
     asm-string-literal ( expression )
     [ identifier ] asm-string-literal ( expression )
*/

স্থির বৃক্ষ
c_parser_asm_operands (c_parser *parser)
{
  বৃক্ষ list = NULL_বৃক্ষ;
  যাবত্ (সত্য)
    {
      বৃক্ষ name, str;
      সংরচনা c_রাশিমালা রাশিমালা;
      যদি (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
	{
	  c_parser_consume_token (parser);
	  যদি (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      বৃক্ষ id = c_parser_peek_token (parser)->মান;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_LENGTH (id),
				   IDENTIFIER_POINTER (id));
	    }
	  অন্যথা
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, রিক্ত);
	      প্রত্যাগম NULL_বৃক্ষ;
	    }
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	}
      অন্যথা
	name = NULL_বৃক্ষ;
      str = c_parser_asm_string_literal (parser);
      যদি (str == NULL_বৃক্ষ)
	প্রত্যাগম NULL_বৃক্ষ;
      matching_parens parens;
      যদি (!parens.require_open (parser))
	প্রত্যাগম NULL_বৃক্ষ;
      রাশিমালা = c_parser_expression (parser);
      mark_exp_read (রাশিমালা.মান);
      যদি (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
	  প্রত্যাগম NULL_বৃক্ষ;
	}
      list = chainon (list, build_বৃক্ষ_list (build_বৃক্ষ_list (name, str),
					     রাশিমালা.মান));
      যদি (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      অন্যথা
	ভঙ্গ;
    }
  প্রত্যাগম list;
}

/* Parse asm clobbers, a GNU extension.

   asm-clobbers:
     asm-string-literal
     asm-clobbers , asm-string-literal
*/

স্থির বৃক্ষ
c_parser_asm_clobbers (c_parser *parser)
{
  বৃক্ষ list = NULL_বৃক্ষ;
  যাবত্ (সত্য)
    {
      বৃক্ষ str = c_parser_asm_string_literal (parser);
      যদি (str)
	list = বৃক্ষ_cons (NULL_বৃক্ষ, str, list);
      অন্যথা
	প্রত্যাগম NULL_বৃক্ষ;
      যদি (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      অন্যথা
	ভঙ্গ;
    }
  প্রত্যাগম list;
}

/* Parse asm goto labels, a GNU extension.

   asm-goto-operands:
     identifier
     asm-goto-operands , identifier
*/

স্থির বৃক্ষ
c_parser_asm_goto_operands (c_parser *parser)
{
  বৃক্ষ list = NULL_বৃক্ষ;
  যাবত্ (সত্য)
    {
      বৃক্ষ name, label;

      যদি (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->মান;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  বৃক্ষ_USED (label) = 1;
	}
      অন্যথা
	{
	  c_parser_error (parser, "expected identifier");
	  প্রত্যাগম NULL_বৃক্ষ;
	}

      name = build_string (IDENTIFIER_LENGTH (name),
			   IDENTIFIER_POINTER (name));
      list = বৃক্ষ_cons (name, label, list);
      যদি (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      অন্যথা
	প্রত্যাগম nreverse (list);
    }
}

/* Parse a possibly concatenated sequence of string literals.
   TRANSLATE says whether to translate them to the execution character
   set; WIDE_OK says whether any kind of prefixed string literal is
   permitted in this context.  This code is based on that in
   lex_string.  */

সংরচনা c_রাশিমালা
c_parser_string_literal (c_parser *parser, তার্কিক translate, তার্কিক wide_ok)
{
  সংরচনা c_রাশিমালা ret;
  size_t গুনতি;
  সংরচনা obstack str_ob;
  সংরচনা obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, last_tok_loc;
  গণনা cpp_ttype type;
  বৃক্ষ মান, string_বৃক্ষ;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  last_tok_loc = linemap_resolve_location (সারি_table, loc,
					   LRK_MACRO_DEFINITION_LOCATION,
					   রিক্ত);
  type = tok->type;
  বিকল্প (type)
    {
    পক্ষ CPP_STRING:
    পক্ষ CPP_WSTRING:
    পক্ষ CPP_STRING16:
    পক্ষ CPP_STRING32:
    পক্ষ CPP_UTF8STRING:
      string_বৃক্ষ = tok->মান;
      ভঙ্গ;

    স্বভাব:
      c_parser_error (parser, "expected string literal");
      ret.set_error ();
      ret.মান = NULL_বৃক্ষ;
      ret.original_code = ERROR_MARK;
      ret.original_type = NULL_বৃক্ষ;
      প্রত্যাগম ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  বিকল্প (c_parser_peek_2nd_token (parser)->type)
    {
    স্বভাব:
      c_parser_consume_token (parser);
      str.text = (ধ্রুব unsigned বর্ণ *) বৃক্ষ_STRING_POINTER (string_বৃক্ষ);
      str.len = বৃক্ষ_STRING_LENGTH (string_বৃক্ষ);
      গুনতি = 1;
      strs = &str;
      ভঙ্গ;

    পক্ষ CPP_STRING:
    পক্ষ CPP_WSTRING:
    পক্ষ CPP_STRING16:
    পক্ষ CPP_STRING32:
    পক্ষ CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      গুনতি = 0;
      কুরু
	{
	  c_parser_consume_token (parser);
	  গুনতি++;
	  str.text = (ধ্রুব unsigned বর্ণ *) বৃক্ষ_STRING_POINTER (string_বৃক্ষ);
	  str.len = বৃক্ষ_STRING_LENGTH (string_বৃক্ষ);
	  যদি (type != tok->type)
	    {
	      যদি (type == CPP_STRING)
		type = tok->type;
	      অন্যথা যদি (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, পরিমাণ (cpp_string));
	  obstack_grow (&loc_ob, &last_tok_loc, পরিমাণ (location_t));
	  tok = c_parser_peek_token (parser);
	  string_বৃক্ষ = tok->মান;
	  last_tok_loc
	    = linemap_resolve_location (সারি_table, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, রিক্ত);
	}
      যাবত্ (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_finish (&str_ob);
    }

  যদি (গুনতি > 1 && !in_system_header_at (প্রবেশ_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  যদি ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_in, strs, গুনতি, &istr, type)))
    {
      মান = build_string (istr.len, (ধ্রুব বর্ণ *) istr.text);
      মুক্ত (const_cast<unsigned বর্ণ *> (istr.text));
      যদি (গুনতি > 1)
	{
	  location_t *locs = (location_t *) obstack_finish (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->record_string_concatenation (গুনতি, locs);
	}
    }
  অন্যথা
    {
      যদি (type != CPP_STRING && !wide_ok)
	{
	  error_at (loc, "a wide string is invalid in this context");
	  type = CPP_STRING;
	}
      /* Callers cannot generally handle error_mark_node in this
	 context, so return the empty string instead.  An error has
	 been issued, either above or from cpp_interpret_string.  */
      বিকল্প (type)
	{
	স্বভাব:
	পক্ষ CPP_STRING:
	পক্ষ CPP_UTF8STRING:
	  যদি (type == CPP_UTF8STRING && flag_char8_t)
	    {
	      মান = build_string (TYPE_PRECISION (char8_type_গ্রন্থি)
				    / TYPE_PRECISION (char_type_গ্রন্থি),
				    "");  /* char8_t is 8 bits */
	    }
	  অন্যথা
	    মান = build_string (1, "");
	  ভঙ্গ;
	পক্ষ CPP_STRING16:
	  মান = build_string (TYPE_PRECISION (char16_type_গ্রন্থি)
				/ TYPE_PRECISION (char_type_গ্রন্থি),
				"\0");  /* char16_t is 16 bits */
	  ভঙ্গ;
	পক্ষ CPP_STRING32:
	  মান = build_string (TYPE_PRECISION (char32_type_গ্রন্থি)
				/ TYPE_PRECISION (char_type_গ্রন্থি),
				"\0\0\0");  /* char32_t is 32 bits */
	  ভঙ্গ;
	পক্ষ CPP_WSTRING:
	  মান = build_string (TYPE_PRECISION (wchar_type_গ্রন্থি)
				/ TYPE_PRECISION (char_type_গ্রন্থি),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  ভঙ্গ;
        }
    }

  বিকল্প (type)
    {
    স্বভাব:
    পক্ষ CPP_STRING:
      বৃক্ষ_TYPE (মান) = char_array_type_গ্রন্থি;
      ভঙ্গ;
    পক্ষ CPP_UTF8STRING:
      যদি (flag_char8_t)
	বৃক্ষ_TYPE (মান) = char8_array_type_গ্রন্থি;
      অন্যথা
	বৃক্ষ_TYPE (মান) = char_array_type_গ্রন্থি;
      ভঙ্গ;
    পক্ষ CPP_STRING16:
      বৃক্ষ_TYPE (মান) = char16_array_type_গ্রন্থি;
      ভঙ্গ;
    পক্ষ CPP_STRING32:
      বৃক্ষ_TYPE (মান) = char32_array_type_গ্রন্থি;
      ভঙ্গ;
    পক্ষ CPP_WSTRING:
      বৃক্ষ_TYPE (মান) = wchar_array_type_গ্রন্থি;
    }
  মান = fix_string_type (মান);

  যদি (গুনতি > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.মান = মান;
  ret.original_code = STRING_CST;
  ret.original_type = NULL_বৃক্ষ;
  set_c_রাশিমালা_source_range (&ret, get_range_from_loc (সারি_table, loc));
  ret.m_decimal = 0;
  parser->seen_string_literal = সত্য;
  প্রত্যাগম ret;
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

স্থির সংরচনা c_রাশিমালা
c_parser_রাশিমালা_no_commas (c_parser *parser, সংরচনা c_রাশিমালা *after,
			 বৃক্ষ omp_atomic_lhs)
{
  সংরচনা c_রাশিমালা lhs, rhs, ret;
  গণনা বৃক্ষ_code code;
  location_t op_location, exp_location;
  তার্কিক save_in_omp_for = c_in_omp_for;
  c_in_omp_for = অসত্য;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_expression (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  বিকল্প (c_parser_peek_token (parser)->type)
    {
    পক্ষ CPP_EQ:
      code = NOP_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_MULT_EQ:
      code = MULT_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_DIV_EQ:
      code = TRUNC_DIV_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_MOD_EQ:
      code = TRUNC_MOD_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_PLUS_EQ:
      code = PLUS_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_MINUS_EQ:
      code = MINUS_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_LSHIFT_EQ:
      code = LSHIFT_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_RSHIFT_EQ:
      code = RSHIFT_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_AND_EQ:
      code = BIT_AND_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_XOR_EQ:
      code = BIT_XOR_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_OR_EQ:
      code = BIT_IOR_রাশিমালা;
      ভঙ্গ;
    স্বভাব:
      c_in_omp_for = save_in_omp_for;
      প্রত্যাগম lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
  rhs = convert_lvalue_to_rvalue (exp_location, rhs, সত্য, সত্য);

  ret.মান = build_modify_রাশিমালা (op_location, lhs.মান, lhs.original_type,
				 code, exp_location, rhs.মান,
				 rhs.original_type);
  ret.m_decimal = 0;
  set_c_রাশিমালা_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  যদি (code == NOP_রাশিমালা)
    ret.original_code = MODIFY_রাশিমালা;
  অন্যথা
    {
      suppress_warning (ret.মান, OPT_Wparentheses);
      ret.original_code = ERROR_MARK;
    }
  ret.original_type = রিক্ত;
  c_in_omp_for = save_in_omp_for;
  প্রত্যাগম ret;
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

স্থির সংরচনা c_রাশিমালা
c_parser_conditional_expression (c_parser *parser, সংরচনা c_রাশিমালা *after,
				 বৃক্ষ omp_atomic_lhs)
{
  সংরচনা c_রাশিমালা cond, exp1, exp2, ret;
  location_t start, cond_loc, colon_loc;
  তার্কিক save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_দ্বিমিক_expression (parser, after, omp_atomic_lhs);

  যদি (c_parser_next_token_is_not (parser, CPP_QUERY))
    প্রত্যাগম cond;
  c_omp_array_section_p = অসত্য;
  যদি (cond.মান != error_mark_গ্রন্থি)
    start = cond.get_start ();
  অন্যথা
    start = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_to_rvalue (cond_loc, cond, সত্য, সত্য);
  c_parser_consume_token (parser);
  যদি (c_parser_next_token_is (parser, CPP_COLON))
    {
      বৃক্ষ eptype = NULL_বৃক্ষ;

      location_t মধ্য_loc = c_parser_peek_token (parser)->location;
      pedwarn (মধ্য_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      যদি (বৃক্ষ_CODE (cond.মান) == EXCESS_PRECISION_রাশিমালা)
	{
	  eptype = বৃক্ষ_TYPE (cond.মান);
	  cond.মান = বৃক্ষ_OPERAND (cond.মান, 0);
	}
      বৃক্ষ e = cond.মান;
      যাবত্ (বৃক্ষ_CODE (e) == COMPOUND_রাশিমালা)
	e = বৃক্ষ_OPERAND (e, 1);
      warn_for_omitted_condop (মধ্য_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.মান = save_রাশিমালা (default_conversion (cond.মান));
      যদি (eptype)
	exp1.মান = build1 (EXCESS_PRECISION_রাশিমালা, eptype, exp1.মান);
      exp1.original_type = রিক্ত;
      exp1.src_range = cond.src_range;
      cond.মান = c_objc_common_truthvalue_conversion (cond_loc, exp1.মান);
      c_inhibit_evaluation_warnings += cond.মান == truthvalue_true_গ্রন্থি;
    }
  অন্যথা
    {
      cond.মান
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.মান));
      c_inhibit_evaluation_warnings += cond.মান == truthvalue_false_গ্রন্থি;
      exp1 = c_parser_expression_conv (parser);
      mark_exp_read (exp1.মান);
      c_inhibit_evaluation_warnings +=
	((cond.মান == truthvalue_true_গ্রন্থি)
	 - (cond.মান == truthvalue_false_গ্রন্থি));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.মান == truthvalue_true_গ্রন্থি;
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = রিক্ত;
      c_omp_array_section_p = save_c_omp_array_section_p;
      প্রত্যাগম ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_expression (parser, রিক্ত, NULL_বৃক্ষ);
    exp2 = convert_lvalue_to_rvalue (exp2_loc, exp2, সত্য, সত্য);
  }
  c_inhibit_evaluation_warnings -= cond.মান == truthvalue_true_গ্রন্থি;
  location_t loc1 = make_location (exp1.get_start (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_start (), exp2.src_range);
  যদি (UNLIKELY (omp_atomic_lhs != রিক্ত)
      && (বৃক্ষ_CODE (cond.মান) == GT_রাশিমালা
	  || বৃক্ষ_CODE (cond.মান) == LT_রাশিমালা
	  || বৃক্ষ_CODE (cond.মান) == EQ_রাশিমালা)
      && c_বৃক্ষ_equal (exp2.মান, omp_atomic_lhs)
      && (c_বৃক্ষ_equal (বৃক্ষ_OPERAND (cond.মান, 0), omp_atomic_lhs)
	  || c_বৃক্ষ_equal (বৃক্ষ_OPERAND (cond.মান, 1), omp_atomic_lhs)))
    ret.মান = build3_loc (colon_loc, COND_রাশিমালা, বৃক্ষ_TYPE (omp_atomic_lhs),
			    cond.মান, exp1.মান, exp2.মান);
  অন্যথা
    ret.মান
      = build_conditional_রাশিমালা (colon_loc, cond.মান,
				cond.original_code == C_MAYBE_CONST_রাশিমালা,
				exp1.মান, exp1.original_type, loc1,
				exp2.মান, exp2.original_type, loc2);
  ret.original_code = ERROR_MARK;
  যদি (exp1.মান == error_mark_গ্রন্থি || exp2.মান == error_mark_গ্রন্থি)
    ret.original_type = রিক্ত;
  অন্যথা
    {
      বৃক্ষ t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : বৃক্ষ_TYPE (exp1.মান);
      t2 = exp2.original_type ? exp2.original_type : বৃক্ষ_TYPE (exp2.মান);
      ret.original_type = ((t1 != error_mark_গ্রন্থি
			    && t2 != error_mark_গ্রন্থি
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : রিক্ত);
    }
  set_c_রাশিমালা_source_range (&ret, start, exp2.get_finish ());
  ret.m_decimal = 0;
  c_omp_array_section_p = save_c_omp_array_section_p;
  প্রত্যাগম ret;
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

স্থির সংরচনা c_রাশিমালা
c_parser_দ্বিমিক_expression (c_parser *parser, সংরচনা c_রাশিমালা *after,
			    বৃক্ষ omp_atomic_lhs)
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

  সংরচনা {
    /* The expression at this stack level.  */
    সংরচনা c_রাশিমালা রাশিমালা;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    গণনা c_parser_prec prec;
    /* The operation on its left.  */
    গণনা বৃক্ষ_code op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    বৃক্ষ sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    বৃক্ষ orig_রাশিমালা;
  } স্তূপ[অঙ্ক_PRECS];
  পূর্ণাঙ্ক sp;
  /* Location of the binary operator.  */
  location_t দ্বিমিক_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#define বের_করো_2								      \
  কুরু {									      \
    বিকল্প (স্তূপ[sp].op)						      \
      {									      \
      পক্ষ TRUTH_ANDIF_রাশিমালা:						      \
	c_inhibit_evaluation_warnings -= (স্তূপ[sp - 1].রাশিমালা.মান	      \
					  == truthvalue_false_গ্রন্থি);	      \
	ভঙ্গ;								      \
      পক্ষ TRUTH_ORIF_রাশিমালা:						      \
	c_inhibit_evaluation_warnings -= (স্তূপ[sp - 1].রাশিমালা.মান	      \
					  == truthvalue_true_গ্রন্থি);	      \
	ভঙ্গ;								      \
      পক্ষ TRUNC_DIV_রাশিমালা:						      \
	যদি ((স্তূপ[sp - 1].রাশিমালা.original_code == SIZEOF_রাশিমালা		      \
	     || স্তূপ[sp - 1].রাশিমালা.original_code == PAREN_SIZEOF_রাশিমালা)	      \
	    && (স্তূপ[sp].রাশিমালা.original_code == SIZEOF_রাশিমালা		      \
		|| স্তূপ[sp].রাশিমালা.original_code == PAREN_SIZEOF_রাশিমালা))	      \
	  {								      \
	    বৃক্ষ type0 = স্তূপ[sp - 1].sizeof_arg;			      \
	    বৃক্ষ type1 = স্তূপ[sp].sizeof_arg;				      \
	    বৃক্ষ first_arg = type0;					      \
	    যদি (!TYPE_P (type0))					      \
	      type0 = বৃক্ষ_TYPE (type0);				      \
	    যদি (!TYPE_P (type1))					      \
	      type1 = বৃক্ষ_TYPE (type1);				      \
	    যদি (POINTER_TYPE_P (type0)					      \
		&& comptypes (বৃক্ষ_TYPE (type0), type1)			      \
		&& !(বৃক্ষ_CODE (first_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (first_arg)			      \
		     && warn_sizeof_array_argument))			      \
	      {								      \
		auto_diagnostic_group d;				      \
		যদি (warning_at (স্তূপ[sp].loc, OPT_Wsizeof_pointer_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  যদি (DECL_P (first_arg))				      \
		    inform (DECL_SOURCE_LOCATION (first_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    অন্যথা যদি (বৃক্ষ_CODE (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (type0)))  \
		     && স্তূপ[sp].রাশিমালা.original_code != PAREN_SIZEOF_রাশিমালা)    \
	      maybe_warn_sizeof_array_div (স্তূপ[sp].loc, first_arg, type0,   \
					   স্তূপ[sp].sizeof_arg, type1);      \
	  }								      \
	ভঙ্গ;								      \
      স্বভাব:								      \
	ভঙ্গ;								      \
      }									      \
    স্তূপ[sp - 1].রাশিমালা							      \
      = convert_lvalue_to_rvalue (স্তূপ[sp - 1].loc,			      \
				  স্তূপ[sp - 1].রাশিমালা, সত্য, সত্য);	      \
    স্তূপ[sp].রাশিমালা							      \
      = convert_lvalue_to_rvalue (স্তূপ[sp].loc,			      \
				  স্তূপ[sp].রাশিমালা, সত্য, সত্য);		      \
    যদি (UNLIKELY (omp_atomic_lhs != NULL_বৃক্ষ) && sp == 1		      \
	&& ((c_parser_next_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << স্তূপ[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_SHIFT)		      \
		     | (1 << PREC_ADD) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_next_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_গ্রন্থি			      \
		     && c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (স্তূপ[sp].prec == PREC_REL || স্তূপ[sp].prec == PREC_EQ)))\
	&& স্তূপ[sp].op != TRUNC_MOD_রাশিমালা				      \
	&& স্তূপ[sp].op != GE_রাশিমালা					      \
	&& স্তূপ[sp].op != LE_রাশিমালা					      \
	&& স্তূপ[sp].op != NE_রাশিমালা					      \
	&& স্তূপ[0].রাশিমালা.মান != error_mark_গ্রন্থি			      \
	&& স্তূপ[1].রাশিমালা.মান != error_mark_গ্রন্থি			      \
	&& (omp_atomic_lhs == void_list_গ্রন্থি				      \
	    || c_বৃক্ষ_equal (স্তূপ[0].রাশিমালা.মান, omp_atomic_lhs)	      \
	    || c_বৃক্ষ_equal (স্তূপ[1].রাশিমালা.মান, omp_atomic_lhs)	      \
	    || (স্তূপ[sp].op == EQ_রাশিমালা					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	বৃক্ষ t = make_গ্রন্থি (স্তূপ[1].op);				      \
	বৃক্ষ_TYPE (t) = বৃক্ষ_TYPE (স্তূপ[0].রাশিমালা.মান);		      \
	বৃক্ষ_OPERAND (t, 0) = স্তূপ[0].রাশিমালা.মান;			      \
	বৃক্ষ_OPERAND (t, 1) = স্তূপ[1].রাশিমালা.মান;			      \
	স্তূপ[0].রাশিমালা.মান = t;					      \
	স্তূপ[0].রাশিমালা.m_decimal = 0;					      \
      }									      \
    অন্যথা								      \
      স্তূপ[sp - 1].রাশিমালা = parser_build_দ্বিমিক_op (স্তূপ[sp].loc,	      \
						   স্তূপ[sp].op,	      \
						   স্তূপ[sp - 1].রাশিমালা,	      \
						   স্তূপ[sp].রাশিমালা,	      \
						   স্তূপ[sp - 1].orig_রাশিমালা);  \
    স্তূপ[sp - 1].orig_রাশিমালা = NULL_বৃক্ষ;				      \
    sp--;								      \
  } যাবত্ (0)
  gcc_assert (!after || c_dialect_objc ());
  স্তূপ[0].loc = c_parser_peek_token (parser)->location;
  স্তূপ[0].রাশিমালা = c_parser_cast_expression (parser, after);
  স্তূপ[0].prec = PREC_NONE;
  স্তূপ[0].sizeof_arg = c_last_sizeof_arg;
  স্তূপ[0].orig_রাশিমালা = NULL_বৃক্ষ;
  sp = 0;
  যাবত্ (সত্য)
    {
      গণনা c_parser_prec oprec;
      গণনা বৃক্ষ_code ocode;
      source_range src_range;
      যদি (parser->error)
	গচ্ছ out;
      বিকল্প (c_parser_peek_token (parser)->type)
	{
	পক্ষ CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_PLUS:
	  oprec = PREC_ADD;
	  ocode = PLUS_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_MINUS:
	  oprec = PREC_ADD;
	  ocode = MINUS_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_LSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = LSHIFT_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_RSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = RSHIFT_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = BIT_AND_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = BIT_XOR_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = BIT_IOR_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_রাশিমালা;
	  ভঙ্গ;
	স্বভাব:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  গচ্ছ out;
	}
      দ্বিমিক_loc = c_parser_peek_token (parser)->location;
      যাবত্ (oprec <= স্তূপ[sp].prec)
	বের_করো_2;
      c_parser_consume_token (parser);
      বিকল্প (ocode)
	{
	পক্ষ TRUTH_ANDIF_রাশিমালা:
	  src_range = স্তূপ[sp].রাশিমালা.src_range;
	  স্তূপ[sp].রাশিমালা
	    = convert_lvalue_to_rvalue (স্তূপ[sp].loc,
					স্তূপ[sp].রাশিমালা, সত্য, সত্য);
	  স্তূপ[sp].orig_রাশিমালা = স্তূপ[sp].রাশিমালা.মান;
	  স্তূপ[sp].রাশিমালা.মান = c_objc_common_truthvalue_conversion
	    (স্তূপ[sp].loc, default_conversion (স্তূপ[sp].রাশিমালা.মান));
	  c_inhibit_evaluation_warnings += (স্তূপ[sp].রাশিমালা.মান
					    == truthvalue_false_গ্রন্থি);
	  set_c_রাশিমালা_source_range (&স্তূপ[sp].রাশিমালা, src_range);
	  ভঙ্গ;
	পক্ষ TRUTH_ORIF_রাশিমালা:
	  src_range = স্তূপ[sp].রাশিমালা.src_range;
	  স্তূপ[sp].রাশিমালা
	    = convert_lvalue_to_rvalue (স্তূপ[sp].loc,
					স্তূপ[sp].রাশিমালা, সত্য, সত্য);
	  স্তূপ[sp].orig_রাশিমালা = স্তূপ[sp].রাশিমালা.মান;
	  স্তূপ[sp].রাশিমালা.মান = c_objc_common_truthvalue_conversion
	    (স্তূপ[sp].loc, default_conversion (স্তূপ[sp].রাশিমালা.মান));
	  c_inhibit_evaluation_warnings += (স্তূপ[sp].রাশিমালা.মান
					    == truthvalue_true_গ্রন্থি);
	  set_c_রাশিমালা_source_range (&স্তূপ[sp].রাশিমালা, src_range);
	  ভঙ্গ;
	স্বভাব:
	  ভঙ্গ;
	}
      sp++;
      স্তূপ[sp].loc = দ্বিমিক_loc;
      স্তূপ[sp].রাশিমালা = c_parser_cast_expression (parser, রিক্ত);
      স্তূপ[sp].prec = oprec;
      স্তূপ[sp].op = ocode;
      স্তূপ[sp].sizeof_arg = c_last_sizeof_arg;
      স্তূপ[sp].orig_রাশিমালা = NULL_বৃক্ষ;
    }
 out:
  যাবত্ (sp > 0)
    বের_করো_2;
  প্রত্যাগম স্তূপ[0].রাশিমালা;
#undef বের_করো_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

স্থির সংরচনা c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  তার্কিক seen_scspec = অসত্য;
  সংরচনা c_declspecs *specs = build_null_declspecs ();
  যাবত্ (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      বিকল্প (c_parser_peek_token (parser)->keyword)
	{
	পক্ষ RID_CONSTEXPR:
	পক্ষ RID_REGISTER:
	পক্ষ RID_STATIC:
	পক্ষ RID_THREAD:
	  seen_scspec = সত্য;
	  declspecs_add_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->মান);
	  c_parser_consume_token (parser);
	  ভঙ্গ;
	স্বভাব:
	  গচ্ছ out;
	}
    }
 out:
  প্রত্যাগম seen_scspec ? specs : রিক্ত;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

স্থির সংরচনা c_রাশিমালা
c_parser_cast_expression (c_parser *parser, সংরচনা c_রাশিমালা *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  যদি (after)
    প্রত্যাগম c_parser_postfix_expression_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      সংরচনা c_declspecs *scspecs;
      সংরচনা c_type_name *type_name;
      সংরচনা c_রাশিমালা ret;
      সংরচনা c_রাশিমালা রাশিমালা;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, সত্য);
      parens.skip_until_found_close (parser);
      যদি (type_name == রিক্ত)
	{
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = রিক্ত;
	  প্রত্যাগম ret;
	}

      /* Save casted types in the function's used types hash table.  */
      used_types_ঢোকাও (type_name->specs->type);

      যদি (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	প্রত্যাগম c_parser_postfix_expression_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      যদি (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      যদি (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
	রাশিমালা = c_parser_cast_expression (parser, রিক্ত);
	রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, সত্য, সত্য);
      }
      ret.মান = c_cast_রাশিমালা (cast_loc, type_name, রাশিমালা.মান);
      যদি (ret.মান && রাশিমালা.মান)
	set_c_রাশিমালা_source_range (&ret, cast_loc, রাশিমালা.get_finish ());
      ret.original_code = ERROR_MARK;
      ret.original_type = রিক্ত;
      ret.m_decimal = 0;
      প্রত্যাগম ret;
    }
  অন্যথা
    প্রত্যাগম c_parser_unary_expression (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

স্থির শূন্য
mark_exp_read_cond (বৃক্ষ exp)
{
  যদি ((VAR_P (exp) || বৃক্ষ_CODE (exp) == PARM_DECL)
      && (VAR_P (exp) ? warn_unused_but_set_variable
		      : warn_unused_but_set_parameter) > 1)
    প্রত্যাগম;

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

স্থির সংরচনা c_রাশিমালা
c_parser_unary_expression (c_parser *parser)
{
  পূর্ণাঙ্ক ext;
  সংরচনা c_রাশিমালা ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t exp_loc;
  location_t finish;
  ret.original_code = ERROR_MARK;
  ret.original_type = রিক্ত;
  বিকল্প (c_parser_peek_token (parser)->type)
    {
    পক্ষ CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, রিক্ত);
      mark_exp_read_cond (op.মান);
      op = default_function_array_conversion (exp_loc, op);
      প্রত্যাগম parser_build_unary_op (op_loc, PREINCREMENT_রাশিমালা, op);
    পক্ষ CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, রিক্ত);
      mark_exp_read_cond (op.মান);
      op = default_function_array_conversion (exp_loc, op);
      প্রত্যাগম parser_build_unary_op (op_loc, PREDECREMENT_রাশিমালা, op);
    পক্ষ CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, রিক্ত);
      mark_exp_read (op.মান);
      প্রত্যাগম parser_build_unary_op (op_loc, ADDR_রাশিমালা, op);
    পক্ষ CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_expression (parser, রিক্ত);
	finish = op.get_finish ();
	op = convert_lvalue_to_rvalue (exp_loc, op, সত্য, সত্য);
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.মান = build_indirect_ref (combined_loc, op.মান, RO_UNARY_STAR);
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ret.m_decimal = 0;
	প্রত্যাগম ret;
      }
    পক্ষ CPP_PLUS:
      যদি (!c_dialect_objc () && !in_system_header_at (প্রবেশ_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, রিক্ত);
      op = convert_lvalue_to_rvalue (exp_loc, op, সত্য, সত্য);
      প্রত্যাগম parser_build_unary_op (op_loc, CONVERT_রাশিমালা, op);
    পক্ষ CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, রিক্ত);
      op = convert_lvalue_to_rvalue (exp_loc, op, সত্য, সত্য);
      প্রত্যাগম parser_build_unary_op (op_loc, NEGATE_রাশিমালা, op);
    পক্ষ CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, রিক্ত);
      op = convert_lvalue_to_rvalue (exp_loc, op, সত্য, সত্য);
      প্রত্যাগম parser_build_unary_op (op_loc, BIT_NOT_রাশিমালা, op);
    পক্ষ CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, রিক্ত);
      op = convert_lvalue_to_rvalue (exp_loc, op, সত্য, সত্য);
      প্রত্যাগম parser_build_unary_op (op_loc, TRUTH_NOT_রাশিমালা, op);
    পক্ষ CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      যদি (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ret.মান = finish_label_address_রাশিমালা
	    (c_parser_peek_token (parser)->মান, op_loc);
	  set_c_রাশিমালা_source_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_finish ());
	  c_parser_consume_token (parser);
	}
      অন্যথা
	{
	  c_parser_error (parser, "expected identifier");
	  ret.set_error ();
	}
      প্রত্যাগম ret;
    পক্ষ CPP_KEYWORD:
      {
	গণনা rid rid = c_parser_peek_token (parser)->keyword;
	বিকল্প (rid)
	  {
	  পক্ষ RID_COUNTOF:
	  পক্ষ RID_SIZEOF:
	    প্রত্যাগম c_parser_sizeof_or_countof_expression (parser, rid);
	  পক্ষ RID_ALIGNOF:
	    প্রত্যাগম c_parser_alignof_expression (parser);
	  পক্ষ RID_MAXOF:
	  পক্ষ RID_MINOF:
	    প্রত্যাগম c_parser_maxof_or_minof_expression (parser, rid);
	  পক্ষ RID_BUILTIN_HAS_ATTRIBUTE:
	    প্রত্যাগম c_parser_has_attribute_expression (parser);
	  পক্ষ RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_expression (parser, রিক্ত);
	    restore_extension_diagnostics (ext);
	    প্রত্যাগম ret;
	  পক্ষ RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, রিক্ত);
	    op = default_function_array_conversion (exp_loc, op);
	    প্রত্যাগম parser_build_unary_op (op_loc, REALPART_রাশিমালা, op);
	  পক্ষ RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, রিক্ত);
	    op = default_function_array_conversion (exp_loc, op);
	    প্রত্যাগম parser_build_unary_op (op_loc, IMAGPART_রাশিমালা, op);
	  পক্ষ RID_TRANSACTION_ATOMIC:
	  পক্ষ RID_TRANSACTION_RELAXED:
	    প্রত্যাগম c_parser_transaction_expression (parser, rid);
	  পক্ষ RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.মান = void_গ্রন্থি;
	    set_c_রাশিমালা_source_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    প্রত্যাগম ret;
	  স্বভাব:
	    প্রত্যাগম c_parser_postfix_expression (parser);
	  }
      }
    স্বভাব:
      প্রত্যাগম c_parser_postfix_expression (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

স্থির সংরচনা c_রাশিমালা
c_parser_sizeof_or_countof_expression (c_parser *parser, গণনা rid rid)
{
  ধ্রুব বর্ণ *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  সংরচনা c_রাশিমালা রাশিমালা;
  সংরচনা c_রাশিমালা result;
  location_t রাশিমালা_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  যদি (rid == RID_COUNTOF)
    pedwarn_c23 (start, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  যদি (rid == RID_COUNTOF)
    in_countof++;
  অন্যথা
    in_sizeof++;
  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      সংরচনা c_declspecs *scspecs;
      সংরচনা c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      রাশিমালা_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, সত্য);
      parens.skip_until_found_close (parser);
      finish = parser->tokens_buf[0].location;
      যদি (type_name == রিক্ত)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  রাশিমালা.set_error ();
	  গচ্ছ Xof_রাশিমালা;
	}
      যদি (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  রাশিমালা = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       রাশিমালা_loc);
	  finish = রাশিমালা.get_finish ();
	  গচ্ছ Xof_রাশিমালা;
	}
      /* sizeof ( type-name ).  */
      যদি (scspecs)
	error_at (রাশিমালা_loc, "storage class specifier in %qs", op_name);
      যদি (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      যদি (rid == RID_COUNTOF)
	{
	  in_countof--;
	  result = c_রাশিমালা_countof_type (রাশিমালা_loc, type_name);
	}
      অন্যথা
	{
	  in_sizeof--;
	  result = c_রাশিমালা_sizeof_type (রাশিমালা_loc, type_name);
	}
    }
  অন্যথা
    {
      রাশিমালা_loc = c_parser_peek_token (parser)->location;
      রাশিমালা = c_parser_unary_expression (parser);
      finish = রাশিমালা.get_finish ();
    Xof_রাশিমালা:
      c_inhibit_evaluation_warnings--;
      যদি (rid == RID_COUNTOF)
	in_countof--;
      অন্যথা
	in_sizeof--;
      mark_exp_read (রাশিমালা.মান);
      যদি (বৃক্ষ_CODE (রাশিমালা.মান) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (বৃক্ষ_OPERAND (রাশিমালা.মান, 1)))
	error_at (রাশিমালা_loc, "%qs applied to a bit-field", op_name);
      যদি (rid == RID_COUNTOF)
	result = c_রাশিমালা_countof_রাশিমালা (রাশিমালা_loc, রাশিমালা);
      অন্যথা
	result = c_রাশিমালা_sizeof_রাশিমালা (রাশিমালা_loc, রাশিমালা);
    }
  যদি (finish == UNKNOWN_LOCATION)
    finish = start;
  set_c_রাশিমালা_source_range (&result, start, finish);
  প্রত্যাগম result;
}

/* Parse an alignof expression.  */

স্থির সংরচনা c_রাশিমালা
c_parser_alignof_expression (c_parser *parser)
{
  সংরচনা c_রাশিমালা রাশিমালা;
  location_t start_loc = c_parser_peek_token (parser)->location;
  location_t end_loc;
  বৃক্ষ alignof_spelling = c_parser_peek_token (parser)->মান;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNOF));
  তার্কিক is_c11_alignof = (strcmp (IDENTIFIER_POINTER (alignof_spelling),
				"_Alignof") == 0
			 || strcmp (IDENTIFIER_POINTER (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  যদি (is_c11_alignof)
    {
      যদি (flag_isoc99)
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      অন্যথা
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_alignof++;
  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      সংরচনা c_declspecs *scspecs;
      সংরচনা c_type_name *type_name;
      সংরচনা c_রাশিমালা ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, সত্য);
      end_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
      যদি (type_name == রিক্ত)
	{
	  সংরচনা c_রাশিমালা ret;
	  c_inhibit_evaluation_warnings--;
	  in_alignof--;
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = রিক্ত;
	  প্রত্যাগম ret;
	}
      যদি (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  রাশিমালা = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  গচ্ছ alignof_রাশিমালা;
	}
      /* alignof ( type-name ).  */
      যদি (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      যদি (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      ret.মান = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       রিক্ত, রিক্ত),
					    অসত্য, is_c11_alignof, 1);
      ret.original_code = ERROR_MARK;
      ret.original_type = রিক্ত;
      set_c_রাশিমালা_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      প্রত্যাগম ret;
    }
  অন্যথা
    {
      সংরচনা c_রাশিমালা ret;
      রাশিমালা = c_parser_unary_expression (parser);
      end_loc = রাশিমালা.src_range.m_finish;
    alignof_রাশিমালা:
      mark_exp_read (রাশিমালা.মান);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      যদি (is_c11_alignof)
	pedwarn (start_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.মান = c_alignof_রাশিমালা (start_loc, রাশিমালা.মান);
      ret.original_code = ERROR_MARK;
      ret.original_type = রিক্ত;
      set_c_রাশিমালা_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      প্রত্যাগম ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

স্থির সংরচনা c_রাশিমালা
c_parser_maxof_or_minof_expression (c_parser *parser, গণনা rid rid)
{
  ধ্রুব বর্ণ *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  সংরচনা c_রাশিমালা result;
  location_t রাশিমালা_loc;
  সংরচনা c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  pedwarn (start, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  যদি (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      গচ্ছ fail;
    }
  parens.consume_open (parser);
  রাশিমালা_loc = c_parser_peek_token (parser)->location;
  যদি (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (রাশিমালা_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_found_close (parser);
      গচ্ছ fail;
    }
  type_name = c_parser_type_name (parser, সত্য);
  যদি (type_name == রিক্ত)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_found_close (parser);
      গচ্ছ fail;
    }
  parens.skip_until_found_close (parser);
  finish = parser->tokens_buf[0].location;
  যদি (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  যদি (rid == RID_MAXOF)
    result = c_রাশিমালা_maxof_type (রাশিমালা_loc, type_name);
  অন্যথা
    result = c_রাশিমালা_minof_type (রাশিমালা_loc, type_name);
  set_c_রাশিমালা_source_range (&result, start, finish);
  প্রত্যাগম result;
fail:
  c_inhibit_evaluation_warnings--;
  result.set_error ();
  result.original_code = ERROR_MARK;
  result.original_type = রিক্ত;
  প্রত্যাগম result;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

স্থির সংরচনা c_রাশিমালা
c_parser_has_attribute_expression (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t start = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;

      সংরচনা c_রাশিমালা result;
      result.set_error ();
      result.original_code = ERROR_MARK;
      result.original_type = রিক্ত;
      প্রত্যাগম result;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  in_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  বৃক্ষ oper = NULL_বৃক্ষ;
  যদি (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      সংরচনা c_type_name *tname = c_parser_type_name (parser);
      in_typeof--;
      যদি (tname)
	{
	  oper = groktypename (tname, রিক্ত, রিক্ত);
	  বের_করো_maybe_used (c_type_variably_modified_p (oper));
	}
    }
  অন্যথা
    {
      সংরচনা c_রাশিমালা cexpr = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      যদি (cexpr.মান != error_mark_গ্রন্থি)
	{
	  mark_exp_read (cexpr.মান);
	  oper = cexpr.মান;
	  বৃক্ষ etype = বৃক্ষ_TYPE (oper);
	  তার্কিক was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  যদি (was_vm)
	    oper = c_fully_fold (oper, অসত্য, রিক্ত);
	  বের_করো_maybe_used (was_vm);
	}
    }

  সংরচনা c_রাশিমালা result;
  result.original_code = ERROR_MARK;
  result.original_type = রিক্ত;

  যদি (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      result.set_error ();
      প্রত্যাগম result;
    }

  তার্কিক save_translate_strings_p = parser->translate_strings_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  বৃক্ষ attr = c_parser_gnu_attribute (parser, NULL_বৃক্ষ, অসত্য, অসত্য);

  parser->translate_strings_p = save_translate_strings_p;

  location_t finish = c_parser_peek_token (parser)->location;
  যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  অন্যথা
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);

      result.set_error ();
      প্রত্যাগম result;
    }

  যদি (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      result.set_error ();
      প্রত্যাগম result;
    }

  result.original_code = INTEGER_CST;
  result.original_type = boolean_type_গ্রন্থি;

  যদি (has_attribute (atloc, oper, attr, default_conversion))
    result.মান = boolean_true_গ্রন্থি;
  অন্যথা
    result.মান =  boolean_false_গ্রন্থি;

  set_c_রাশিমালা_source_range (&result, start, finish);
  result.m_decimal = 0;
  প্রত্যাগম result;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
স্থির তার্কিক
c_parser_get_builtin_args (c_parser *parser, ধ্রুব বর্ণ *bname,
			   vec<c_রাশিমালা_t, va_gc> **ret_cexpr_list,
			   তার্কিক choose_রাশিমালা_p,
			   location_t *out_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_রাশিমালা_t, va_gc> *cexpr_list;
  c_রাশিমালা_t রাশিমালা;
  তার্কিক saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = রিক্ত;
  যদি (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      প্রত্যাগম অসত্য;
    }

  c_parser_consume_token (parser);

  যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      *out_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      প্রত্যাগম সত্য;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= choose_রাশিমালা_p;
  রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_safe_ঠেলো (cexpr_list, রাশিমালা);
  যাবত্ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      যদি (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  বৃক্ষ মান = embed->মান;
	  রাশিমালা.original_code = INTEGER_CST;
	  রাশিমালা.original_type = integer_type_গ্রন্থি;
	  রাশিমালা.মান = NULL_বৃক্ষ;
	  set_c_রাশিমালা_source_range (&রাশিমালা, embed->get_range ());
	  রাশিমালা.m_decimal = 0;
	  প্রতি (unsigned পূর্ণাঙ্ক i = 0; i < (unsigned) RAW_DATA_LENGTH (মান); i++)
	    {
	      রাশিমালা.মান = build_int_cst (integer_type_গ্রন্থি,
					  RAW_DATA_UCHAR_ELT (মান, i));
	      vec_safe_ঠেলো (cexpr_list, রাশিমালা);
	    }
	  c_parser_consume_token (parser);
	  অনুবর্ত;
	}
      রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      vec_safe_ঠেলো (cexpr_list, রাশিমালা);
    }

  *out_close_paren_loc = c_parser_peek_token (parser)->location;
  যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    প্রত্যাগম অসত্য;

  *ret_cexpr_list = cexpr_list;
  প্রত্যাগম সত্য;
}

/* This represents a single generic-association.  */

সংরচনা c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  বৃক্ষ type;
  /* The association's expression.  */
  সংরচনা c_রাশিমালা expression;
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

স্থির সংরচনা c_রাশিমালা
c_parser_generic_selection (c_parser *parser)
{
  সংরচনা c_রাশিমালা selector, error_রাশিমালা;
  বৃক্ষ selector_type;
  সংরচনা c_generic_association matched_assoc;
  পূর্ণাঙ্ক match_found = -1;
  location_t generic_loc, selector_loc;

  error_রাশিমালা.original_code = ERROR_MARK;
  error_রাশিমালা.original_type = রিক্ত;
  error_রাশিমালা.set_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_বৃক্ষ;
  matched_assoc.expression = error_রাশিমালা;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_GENERIC));
  generic_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  যদি (flag_isoc99)
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C99 does not support %<_Generic%>");
  অন্যথা
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C90 does not support %<_Generic%>");

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম error_রাশিমালা;

  selector_loc = c_parser_peek_token (parser)->location;
  যদি (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      c_inhibit_evaluation_warnings++;
      pedwarn_c23 (selector_loc, OPT_Wpedantic,
		   "ISO C does not support use of type name as %<_Generic%> "
		   "controlling operand before C2Y");
      সংরচনা c_type_name *type = c_parser_type_name (parser);
      যদি (type)
	selector_type = groktypename (type, রিক্ত, রিক্ত);
      c_inhibit_evaluation_warnings--;
      যদি (!type)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
	  প্রত্যাগম error_রাশিমালা;
	}
    }
  অন্যথা
    {
      c_inhibit_evaluation_warnings++;
      in_generic++;
      selector = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      in_generic--;
      বের_করো_maybe_used (!flag_isoc23);

      যদি (selector.মান == error_mark_গ্রন্থি)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
	  প্রত্যাগম selector;
	}
      mark_exp_read (selector.মান);
      selector_type = বৃক্ষ_TYPE (selector.মান);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      যদি (বৃক্ষ_CODE (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      যদি (FUNCTION_POINTER_TYPE_P (selector_type)
	  && TYPE_QUALS (বৃক্ষ_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_pointer_type (TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (selector_type)));
    }

  যদি (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
      প্রত্যাগম error_রাশিমালা;
    }

  auto_vec<c_generic_association> associations;
  সংরচনা maybe_used_decl *maybe_used_default = রিক্ত;
  যাবত্ (1)
    {
      সংরচনা c_generic_association assoc, *iter;
      unsigned পূর্ণাঙ্ক ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      যদি (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_বৃক্ষ;
	}
      অন্যথা
	{
	  সংরচনা c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  যদি (type_name == রিক্ত)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
	      প্রত্যাগম error_রাশিমালা;
	    }
	  assoc.type = grokgenassoc (type_name);
	  যদি (assoc.type == error_mark_গ্রন্থি)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
	      প্রত্যাগম error_রাশিমালা;
	    }

	  যদি (বৃক্ষ_CODE (assoc.type) == FUNCTION_TYPE)
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "function type before C2Y");
	  অন্যথা যদি (!COMPLETE_TYPE_P (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "incomplete type before C2Y");

	  যদি (c_type_variably_modified_p (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "variably-modified type before C2Y");
	}

      যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
	  প্রত্যাগম error_রাশিমালা;
	}

      তার্কিক match = assoc.type == NULL_বৃক্ষ
		   || comptypes (assoc.type, selector_type);

      যদি (!match || matched_assoc.type != NULL_বৃক্ষ)
	c_inhibit_evaluation_warnings++;
      in_generic++;

      assoc.expression = c_parser_রাশিমালা_no_commas (parser, রিক্ত);

      যদি (!match || matched_assoc.type != NULL_বৃক্ষ)
	c_inhibit_evaluation_warnings--;
      in_generic--;
      যদি (!match)
	বের_করো_maybe_used (!flag_isoc23);
      অন্যথা যদি (assoc.type == NULL_বৃক্ষ)
	maybe_used_default = save_maybe_used ();
      অন্যথা
	বের_করো_maybe_used (সত্য);

      যদি (assoc.expression.মান == error_mark_গ্রন্থি)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
	  প্রত্যাগম error_রাশিমালা;
	}

      প্রতি (ix = 0; associations.iterate (ix, &iter); ++ix)
	{
	  যদি (assoc.type == NULL_বৃক্ষ)
	    {
	      যদি (iter->type == NULL_বৃক্ষ)
		{
		  error_at (assoc.type_location,
			    "duplicate %<default%> case in %<_Generic%>");
		  inform (iter->type_location, "original %<default%> is here");
		}
	    }
	  অন্যথা যদি (iter->type != NULL_বৃক্ষ)
	    {
	      যদি (comptypes (assoc.type, iter->type))
		{
		  error_at (assoc.type_location,
			    "%<_Generic%> specifies two compatible types");
		  inform (iter->type_location, "compatible type is here");
		}
	    }
	}

      যদি (assoc.type == NULL_বৃক্ষ)
	{
	  যদি (match_found < 0)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	}
      অন্যথা যদি (match)
	{
	  যদি (match_found < 0 || matched_assoc.type == NULL_বৃক্ষ)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	  অন্যথা
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.safe_ঠেলো (assoc);

      যদি (c_parser_peek_token (parser)->type != CPP_COMMA)
	ভঙ্গ;
      c_parser_consume_token (parser);
    }

  যদি (match_found >= 0 && matched_assoc.type == NULL_বৃক্ষ)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_used (maybe_used_default);
      বের_করো_maybe_used (সত্য);
    }
  অন্যথা যদি (maybe_used_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_used (maybe_used_default);
      বের_করো_maybe_used (!flag_isoc23);
    }

  unsigned পূর্ণাঙ্ক ix;
  সংরচনা c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    যদি (ix != (unsigned) match_found)
      mark_exp_read (iter->expression.মান);

  যদি (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
      প্রত্যাগম error_রাশিমালা;
    }

  যদি (match_found < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      প্রত্যাগম error_রাশিমালা;
    }

  প্রত্যাগম matched_assoc.expression;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

স্থির unsigned পূর্ণাঙ্ক
check_tgmath_function (c_রাশিমালা *রাশিমালা, unsigned পূর্ণাঙ্ক pos)
{
  বৃক্ষ type = বৃক্ষ_TYPE (রাশিমালা->মান);
  যদি (!FUNCTION_POINTER_TYPE_P (type))
    {
      error_at (রাশিমালা->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      প্রত্যাগম 0;
    }
  type = বৃক্ষ_TYPE (type);
  যদি (!prototype_p (type))
    {
      error_at (রাশিমালা->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      প্রত্যাগম 0;
    }
  যদি (stdarg_p (type))
    {
      error_at (রাশিমালা->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      প্রত্যাগম 0;
    }
  unsigned পূর্ণাঙ্ক nargs = 0;
  function_args_iterator iter;
  বৃক্ষ t;
  FOREACH_FUNCTION_ARGS (type, t, iter)
    {
      যদি (t == void_type_গ্রন্থি)
	ভঙ্গ;
      nargs++;
    }
  যদি (nargs == 0)
    {
      error_at (রাশিমালা->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      প্রত্যাগম 0;
    }
  প্রত্যাগম nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
গণনা tgmath_parm_kind
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

স্থির সংরচনা c_রাশিমালা
c_parser_predefined_identifier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  বিকল্প (c_parser_peek_token (parser)->keyword)
    {
    পক্ষ RID_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__FUNCTION__");
      ভঙ্গ;
    পক্ষ RID_PRETTY_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__PRETTY_FUNCTION__");
      ভঙ্গ;
    পক্ষ RID_C99_FUNCTION_NAME:
      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support "
		   "%<__func__%> predefined identifier");
      ভঙ্গ;
    স্বভাব:
      gcc_unreachable ();
    }

  সংরচনা c_রাশিমালা রাশিমালা;
  রাশিমালা.original_code = ERROR_MARK;
  রাশিমালা.original_type = রিক্ত;
  রাশিমালা.মান = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->মান);
  set_c_রাশিমালা_source_range (&রাশিমালা, loc, loc);
  রাশিমালা.m_decimal = 0;
  c_parser_consume_token (parser);
  প্রত্যাগম রাশিমালা;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

স্থির তার্কিক
has_counted_by_object (বৃক্ষ ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  যদি ((বৃক্ষ_CODE (ref) == INDIRECT_REF
       && is_access_with_size_p (বৃক্ষ_OPERAND (ref, 0)))
      || is_access_with_size_p (ref))
    প্রত্যাগম সত্য;
  প্রত্যাগম অসত্য;
}

/* Get the reference to the counted-by object associated with the REF.  */

স্থির বৃক্ষ
get_counted_by_ref (বৃক্ষ ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  যদি (বৃক্ষ_CODE (ref) == INDIRECT_REF
      && is_access_with_size_p (বৃক্ষ_OPERAND (ref, 0)))
    প্রত্যাগম CALL_রাশিমালা_ARG (বৃক্ষ_OPERAND (ref, 0), 1);
  অন্যথা যদি (is_access_with_size_p (ref))
    প্রত্যাগম CALL_রাশিমালা_ARG (ref, 1);

  প্রত্যাগম NULL_বৃক্ষ;
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

স্থির সংরচনা c_রাশিমালা
c_parser_postfix_expression (c_parser *parser)
{
  সংরচনা c_রাশিমালা রাশিমালা, e1;
  সংরচনা c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  রাশিমালা.original_code = ERROR_MARK;
  রাশিমালা.original_type = রিক্ত;
  রাশিমালা.m_decimal = 0;
  বিকল্প (c_parser_peek_token (parser)->type)
    {
    পক্ষ CPP_সংখ্যা:
      রাশিমালা.মান = c_parser_peek_token (parser)->মান;
      set_c_রাশিমালা_source_range (&রাশিমালা, tok_range);
      loc = c_parser_peek_token (parser)->location;
      রাশিমালা.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      যদি (বৃক্ষ_CODE (রাশিমালা.মান) == FIXED_CST
	  && !targetm.fixed_point_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  রাশিমালা.set_error ();
	}
      ভঙ্গ;
    পক্ষ CPP_CHAR:
    পক্ষ CPP_CHAR16:
    পক্ষ CPP_CHAR32:
    পক্ষ CPP_UTF8CHAR:
    পক্ষ CPP_WCHAR:
      রাশিমালা.মান = c_parser_peek_token (parser)->মান;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      রাশিমালা.original_type = char_type_গ্রন্থি;
      set_c_রাশিমালা_source_range (&রাশিমালা, tok_range);
      c_parser_consume_token (parser);
      ভঙ্গ;
    পক্ষ CPP_STRING:
    পক্ষ CPP_STRING16:
    পক্ষ CPP_STRING32:
    পক্ষ CPP_WSTRING:
    পক্ষ CPP_UTF8STRING:
      রাশিমালা = c_parser_string_literal (parser, parser->translate_strings_p,
				      সত্য);
      ভঙ্গ;
    পক্ষ CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      রাশিমালা.মান
	= objc_build_string_object (c_parser_peek_token (parser)->মান);
      set_c_রাশিমালা_source_range (&রাশিমালা, tok_range);
      c_parser_consume_token (parser);
      ভঙ্গ;
    পক্ষ CPP_NAME:
      বিকল্প (c_parser_peek_token (parser)->id_kind)
	{
	পক্ষ C_ID_ID:
	  {
	    বৃক্ষ id = c_parser_peek_token (parser)->মান;
	    c_parser_consume_token (parser);
	    রাশিমালা.মান = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &রাশিমালা.original_type);
	    set_c_রাশিমালা_source_range (&রাশিমালা, tok_range);
	    ভঙ্গ;
	  }
	পক্ষ C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    বৃক্ষ class_name = c_parser_peek_token (parser)->মান;
	    বৃক্ষ component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    যদি (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->মান;
	    location_t end_loc = component_tok->get_finish ();
	    c_parser_consume_token (parser);
	    রাশিমালা.মান = objc_build_class_component_ref (class_name,
							 component);
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, end_loc);
	    ভঙ্গ;
	  }
	স্বভাব:
	  c_parser_error (parser, "expected expression");
	  রাশিমালা.set_error ();
	  ভঙ্গ;
	}
      ভঙ্গ;
    পক্ষ CPP_OPEN_PAREN:
      /* A parenthesized expression, statement expression or compound
	 literal.  */
      যদি (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_BRACE)
	{
	  /* A statement expression.  */
	  বৃক্ষ stmt;
	  location_t brace_loc;
	  তার্কিক save_c_omp_array_section_p = c_omp_array_section_p;
	  c_parser_consume_token (parser);
	  brace_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* If we've not yet started the current function's statement list,
	     or we're in the parameter scope of an old-style function
	     declaration, statement expressions are not allowed.  */
	  যদি (!building_stmt_list_p () || old_style_parameter_scope ())
	    {
	      error_at (loc, "braced-group within expression allowed "
			"only inside a function");
	      parser->error = সত্য;
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, রিক্ত);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
	      রাশিমালা.set_error ();
	      ভঙ্গ;
	    }
	  c_omp_array_section_p = অসত্য;
	  stmt = c_begin_stmt_রাশিমালা ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  রাশিমালা.মান = c_finish_stmt_রাশিমালা (brace_loc, stmt);
	  set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_loc);
	  mark_exp_read (রাশিমালা.মান);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      অন্যথা
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  রাশিমালা = c_parser_expression (parser);
	  যদি (বৃক্ষ_CODE (রাশিমালা.মান) == MODIFY_রাশিমালা)
	    suppress_warning (রাশিমালা.মান, OPT_Wparentheses);
	  যদি (রাশিমালা.original_code != C_MAYBE_CONST_রাশিমালা
	      && রাশিমালা.original_code != SIZEOF_রাশিমালা)
	    রাশিমালা.original_code = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  যদি (রাশিমালা.original_code == SIZEOF_রাশিমালা)
	    রাশিমালা.original_code = PAREN_SIZEOF_রাশিমালা;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  set_c_রাশিমালা_source_range (&রাশিমালা, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      ভঙ্গ;
    পক্ষ CPP_KEYWORD:
      বিকল্প (c_parser_peek_token (parser)->keyword)
	{
	পক্ষ RID_FUNCTION_NAME:
	পক্ষ RID_PRETTY_FUNCTION_NAME:
	পক্ষ RID_C99_FUNCTION_NAME:
	  রাশিমালা = c_parser_predefined_identifier (parser);
	  ভঙ্গ;
	পক্ষ RID_VA_ARG:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    যদি (!parens.require_open (parser))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    e1 = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	    mark_exp_read (e1.মান);
	    e1.মান = c_fully_fold (e1.মান, অসত্য, রিক্ত);
	    যদি (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    যদি (t1 == রিক্ত)
	      {
		রাশিমালা.set_error ();
	      }
	    অন্যথা
	      {
		বৃক্ষ type_রাশিমালা = NULL_বৃক্ষ;
		বৃক্ষ type = groktypename (t1, &type_রাশিমালা, রিক্ত);
		রাশিমালা.মান = c_build_va_arg (start_loc, e1.মান, loc,
					     type, type_রাশিমালা);
		set_c_রাশিমালা_source_range (&রাশিমালা, start_loc, end_loc);
	      }
	  }
	  ভঙ্গ;
	পক্ষ RID_C23_VA_START:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    যদি (!parens.require_open (parser))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    e1 = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	    e1 = convert_lvalue_to_rvalue (e1.get_location (), e1, সত্য, সত্য);
	    যদি (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		যদি (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
		    রাশিমালা.set_error ();
		    ভঙ্গ;
		  }
		যদি (c_parser_next_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_kind == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    বৃক্ষ name = c_parser_peek_token (parser)->মান;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    বৃক্ষ decl = lookup_name (name);
		    বৃক্ষ last_parm
		      = বৃক্ষ_last (DECL_ARGUMENTS (current_function_decl));
		    যদি (!last_parm || decl != last_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    অন্যথা যদি (DECL_REGISTER (decl))
		      warning_at (nloc, OPT_Wvarargs,
				  "undefined behavior when second parameter "
				  "of %<va_start%> is declared with "
				  "%<register%> storage");
		    c_parser_consume_token (parser);
		  }
		অন্যথা
		  {
		    unsigned nesting_depth = 0;
		    location_t sloc = c_parser_peek_token (parser)->location;
		    location_t eloc = sloc;

		    /* For va_start (ap,) the ) comes from stdarg.h.
		       Use location of , in that case, otherwise without
		       -Wsystem-headers nothing is reported.  After all,
		       the problematic token is the comma in that case.  */
		    যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    যাবত্ (সত্য)
		      {
			c_token *token = c_parser_peek_token (parser);
			যদি (token->type == CPP_CLOSE_PAREN && !nesting_depth)
			  ভঙ্গ;

			যদি (token->type == CPP_EOF)
			  ভঙ্গ;
			যদি (token->type == CPP_OPEN_PAREN)
			  ++nesting_depth;
			অন্যথা যদি (token->type == CPP_CLOSE_PAREN)
			  --nesting_depth;
			eloc = token->location;
			c_parser_consume_token (parser);
		      }
		    যদি (sloc != eloc)
		      sloc = make_location (sloc, sloc, eloc);
		    warning_at (sloc, OPT_Wvarargs,
				"%<va_start%> macro used with additional "
				"arguments other than identifier of the "
				"last named argument");
		  }
	      }
	    parens.skip_until_found_close (parser);
	    বৃক্ষ fndecl = builtin_decl_explicit (BUILT_IN_VA_START);
	    vec<বৃক্ষ, va_gc> *params;
	    vec_alloc (params, 2);
	    params->quick_ঠেলো (e1.মান);
	    params->quick_ঠেলো (integer_zero_গ্রন্থি);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.quick_ঠেলো (e1.get_location ());
	    arg_loc.quick_ঠেলো (UNKNOWN_LOCATION);
	    রাশিমালা.মান = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, রিক্ত);
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc,
				     parser->tokens_buf[0].get_finish ());
	    রাশিমালা.m_decimal = 0;
	    রাশিমালা.original_code = ERROR_MARK;
	    রাশিমালা.original_type = রিক্ত;
	    release_বৃক্ষ_vector (params);
	    ভঙ্গ;
	  }
	পক্ষ RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    যদি (!parens.require_open (parser))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    t1 = c_parser_type_name (parser);
	    যদি (t1 == রিক্ত)
	      parser->error = সত্য;
	    যদি (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    যদি (parser->error)
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    বৃক্ষ type = groktypename (t1, রিক্ত, রিক্ত);
	    বৃক্ষ offsetof_ref;
	    যদি (type == error_mark_গ্রন্থি)
	      offsetof_ref = error_mark_গ্রন্থি;
	    অন্যথা
	      {
		offsetof_ref = build1 (INDIRECT_REF, type, null_pointer_গ্রন্থি);
		SET_রাশিমালা_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    যদি (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->মান,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		যাবত্ (c_parser_next_token_is (parser, CPP_DOT)
		       || c_parser_next_token_is (parser,
						  CPP_OPEN_SQUARE)
		       || c_parser_next_token_is (parser,
						  CPP_DEREF))
		  {
		    যদি (c_parser_next_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_গ্রন্থি);
			গচ্ছ do_dot;
		      }
		    অন্যথা যদি (c_parser_next_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			যদি (c_parser_next_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    ভঙ্গ;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->মান,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    অন্যথা
		      {
			সংরচনা c_রাশিমালা ce;
			বৃক্ষ idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_expression (parser);
			ce = convert_lvalue_to_rvalue (loc, ce, অসত্য, অসত্য);
			idx = ce.মান;
			idx = c_fully_fold (idx, অসত্য, রিক্ত);
			c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
						   "expected %<]%>");
			offsetof_ref = build_array_ref (loc, offsetof_ref, idx);
		      }
		  }
	      }
	    অন্যথা
	      c_parser_error (parser, "expected identifier");
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    রাশিমালা.মান = fold_offsetof (offsetof_ref);
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, end_loc);
	  }
	  ভঙ্গ;
	পক্ষ RID_CHOOSE_রাশিমালা:
	  {
	    vec<c_রাশিমালা_t, va_gc> *cexpr_list;
	    c_রাশিমালা_t *e1_p, *e2_p, *e3_p;
	    বৃক্ষ c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    যদি (!c_parser_get_builtin_args (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, সত্য,
					    &close_paren_loc))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    যদি (vec_safe_length (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->মান;
	    mark_exp_read (e2_p->মান);
	    mark_exp_read (e3_p->মান);
	    যদি (বৃক্ষ_CODE (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (বৃক্ষ_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_expression_warning (c);
	    রাশিমালা = integer_zerop (c) ? *e3_p : *e2_p;
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_paren_loc);
	    ভঙ্গ;
	  }
	পক্ষ RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    যদি (!parens.require_open (parser))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    t1 = c_parser_type_name (parser);
	    যদি (t1 == রিক্ত)
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    t2 = c_parser_type_name (parser);
	    যদি (t2 == রিক্ত)
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    বৃক্ষ e1, e2;
	    e1 = groktypename (t1, রিক্ত, রিক্ত);
	    e2 = groktypename (t2, রিক্ত, রিক্ত);
	    যদি (e1 == error_mark_গ্রন্থি || e2 == error_mark_গ্রন্থি)
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    রাশিমালা.মান
	      = comptypes (e1, e2) ? integer_one_গ্রন্থি : integer_zero_গ্রন্থি;
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_paren_loc);
	  }
	  ভঙ্গ;
	পক্ষ RID_BUILTIN_TGMATH:
	  {
	    vec<c_রাশিমালা_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    যদি (!c_parser_get_builtin_args (parser,
					    "__builtin_tgmath",
					    &cexpr_list, অসত্য,
					    &close_paren_loc))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    যদি (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    unsigned পূর্ণাঙ্ক i;
	    c_রাশিমালা_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, সত্য, সত্য);
	    unsigned পূর্ণাঙ্ক nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    যদি (nargs == 0)
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (vec_safe_length (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    unsigned পূর্ণাঙ্ক অঙ্ক_functions = vec_safe_length (cexpr_list) - nargs;
	    যদি (অঙ্ক_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    প্রতি (unsigned পূর্ণাঙ্ক j = 1; j < অঙ্ক_functions; j++)
	      {
		unsigned পূর্ণাঙ্ক this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		যদি (this_nargs == 0)
		  {
		    রাশিমালা.set_error ();
		    গচ্ছ out;
		  }
		যদি (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    রাশিমালা.set_error ();
		    গচ্ছ out;
		  }
	      }

	    /* The functions all have the same number of arguments.
	       Determine whether arguments and return types vary in
	       ways permitted for <tgmath.h> functions.  */
	    /* The first entry in each of these vectors is for the
	       return type, subsequent entries for parameter
	       types.  */
	    auto_vec<গণনা tgmath_parm_kind> parm_kind (nargs + 1);
	    auto_vec<বৃক্ষ> parm_first (nargs + 1);
	    auto_vec<তার্কিক> parm_complex (nargs + 1);
	    auto_vec<তার্কিক> parm_varies (nargs + 1);
	    বৃক্ষ first_type = বৃক্ষ_TYPE (বৃক্ষ_TYPE ((*cexpr_list)[0].মান));
	    বৃক্ষ first_ret = TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (first_type));
	    parm_first.quick_ঠেলো (first_ret);
	    parm_complex.quick_ঠেলো (বৃক্ষ_CODE (first_ret) == COMPLEX_TYPE);
	    parm_varies.quick_ঠেলো (অসত্য);
	    function_args_iterator iter;
	    বৃক্ষ t;
	    unsigned পূর্ণাঙ্ক argpos;
	    FOREACH_FUNCTION_ARGS (first_type, t, iter)
	      {
		যদি (t == void_type_গ্রন্থি)
		  ভঙ্গ;
		parm_first.quick_ঠেলো (TYPE_MAIN_VARIANT (t));
		parm_complex.quick_ঠেলো (বৃক্ষ_CODE (t) == COMPLEX_TYPE);
		parm_varies.quick_ঠেলো (অসত্য);
	      }
	    প্রতি (unsigned পূর্ণাঙ্ক j = 1; j < অঙ্ক_functions; j++)
	      {
		বৃক্ষ type = বৃক্ষ_TYPE (বৃক্ষ_TYPE ((*cexpr_list)[j].মান));
		বৃক্ষ ret = TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (type));
		যদি (ret != parm_first[0])
		  {
		    parm_varies[0] = সত্য;
		    যদি (!SCALAR_FLOAT_TYPE_P (parm_first[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_first[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			রাশিমালা.set_error ();
			গচ্ছ out;
		      }
		    যদি (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			রাশিমালা.set_error ();
			গচ্ছ out;
		      }
		  }
		যদি (বৃক্ষ_CODE (ret) == COMPLEX_TYPE)
		  parm_complex[0] = সত্য;
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    যদি (t == void_type_গ্রন্থি)
		      ভঙ্গ;
		    t = TYPE_MAIN_VARIANT (t);
		    যদি (t != parm_first[argpos])
		      {
			parm_varies[argpos] = সত্য;
			যদি (!SCALAR_FLOAT_TYPE_P (parm_first[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_first[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    রাশিমালা.set_error ();
			    গচ্ছ out;
			  }
			যদি (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    রাশিমালা.set_error ();
			    গচ্ছ out;
			  }
		      }
		    যদি (বৃক্ষ_CODE (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = সত্য;
		    argpos++;
		  }
	      }
	    গণনা tgmath_parm_kind max_variation = tgmath_fixed;
	    প্রতি (unsigned পূর্ণাঙ্ক j = 0; j <= nargs; j++)
	      {
		গণনা tgmath_parm_kind this_kind;
		যদি (parm_varies[j])
		  {
		    যদি (parm_complex[j])
		      max_variation = this_kind = tgmath_complex;
		    অন্যথা
		      {
			this_kind = tgmath_real;
			যদি (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		অন্যথা
		  this_kind = tgmath_fixed;
		parm_kind.quick_ঠেলো (this_kind);
	      }
	    যদি (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    unsigned পূর্ণাঙ্ক tgarg = 0;
	    প্রতি (unsigned পূর্ণাঙ্ক j = 1; j <= nargs; j++)
	      যদি (parm_kind[j] == max_variation)
		{
		  tgarg = j;
		  ভঙ্গ;
		}
	    যদি (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<বৃক্ষ> tg_type (অঙ্ক_functions);
	    প্রতি (unsigned পূর্ণাঙ্ক j = 0; j < অঙ্ক_functions; j++)
	      {
		বৃক্ষ type = বৃক্ষ_TYPE (বৃক্ষ_TYPE ((*cexpr_list)[j].মান));
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    যদি (argpos == tgarg)
		      {
			tg_type.quick_ঠেলো (TYPE_MAIN_VARIANT (t));
			ভঙ্গ;
		      }
		    argpos++;
		  }
	      }

	    /* Verify that the corresponding types are different for
	       all the listed functions.  Also determine whether all
	       the types are complex, whether all the types are
	       standard or binary, and whether all the types are
	       decimal.  */
	    তার্কিক all_complex = সত্য;
	    তার্কিক all_দ্বিমিক = সত্য;
	    তার্কিক all_decimal = সত্য;
	    hash_set<বৃক্ষ> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		যদি (বৃক্ষ_CODE (t) == COMPLEX_TYPE)
		  all_decimal = অসত্য;
		অন্যথা
		  {
		    all_complex = অসত্য;
		    যদি (DECIMAL_FLOAT_TYPE_P (t))
		      all_দ্বিমিক = অসত্য;
		    অন্যথা
		      all_decimal = অসত্য;
		  }
		যদি (tg_types.add (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    রাশিমালা.set_error ();
		    গচ্ছ out;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    প্রতি (unsigned পূর্ণাঙ্ক j = 0; j < অঙ্ক_functions; j++)
	      {
		বৃক্ষ exp_type = tg_type[j];
		বৃক্ষ exp_real_type = exp_type;
		যদি (বৃক্ষ_CODE (exp_type) == COMPLEX_TYPE)
		  exp_real_type = বৃক্ষ_TYPE (exp_type);
		বৃক্ষ type = বৃক্ষ_TYPE (বৃক্ষ_TYPE ((*cexpr_list)[j].মান));
		বৃক্ষ ret = TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (type));
		যদি ((parm_kind[0] == tgmath_complex && ret != exp_type)
		    || (parm_kind[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    রাশিমালা.set_error ();
		    গচ্ছ out;
		  }
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    যদি (t == void_type_গ্রন্থি)
		      ভঙ্গ;
		    t = TYPE_MAIN_VARIANT (t);
		    যদি ((parm_kind[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_kind[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			রাশিমালা.set_error ();
			গচ্ছ out;
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
	    তার্কিক arg_complex = all_complex;
	    তার্কিক arg_দ্বিমিক = all_দ্বিমিক;
	    তার্কিক arg_int_decimal = all_decimal;
	    তার্কিক arg_int_floatnx = অসত্য;
	    তার্কিক arg_int_decimalx = অসত্য;
	    প্রতি (unsigned পূর্ণাঙ্ক j = 1; j <= nargs; j++)
	      {
		যদি (parm_kind[j] == tgmath_fixed)
		  অনুবর্ত;
		c_রাশিমালা_t *ce = &(*cexpr_list)[অঙ্ক_functions + j - 1];
		বৃক্ষ type = বৃক্ষ_TYPE (ce->মান);
		যদি (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && বৃক্ষ_CODE (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    রাশিমালা.set_error ();
		    গচ্ছ out;
		  }
		যদি (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = সত্য;
		    যদি (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			রাশিমালা.set_error ();
			গচ্ছ out;
		      }
		    অন্যথা যদি (all_দ্বিমিক)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			রাশিমালা.set_error ();
			গচ্ছ out;
		      }
		    অন্যথা যদি (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			রাশিমালা.set_error ();
			গচ্ছ out;
		      }
		    অন্যথা যদি (arg_দ্বিমিক)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			রাশিমালা.set_error ();
			গচ্ছ out;
		      }
		  }
		অন্যথা যদি (বৃক্ষ_CODE (type) == COMPLEX_TYPE)
		  {
		    arg_complex = সত্য;
		    যদি (COMPLEX_FLOAT_TYPE_P (type))
		      arg_দ্বিমিক = সত্য;
		    যদি (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			রাশিমালা.set_error ();
			গচ্ছ out;
		      }
		    অন্যথা যদি (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			রাশিমালা.set_error ();
			গচ্ছ out;
		      }
		  }
		অন্যথা যদি (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_দ্বিমিক = সত্য;
		    যদি (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			রাশিমালা.set_error ();
			গচ্ছ out;
		      }
		    অন্যথা যদি (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			রাশিমালা.set_error ();
			গচ্ছ out;
		      }
		  }
		বৃক্ষ rtype = TYPE_MAIN_VARIANT (type);
		যদি (বৃক্ষ_CODE (rtype) == COMPLEX_TYPE)
		  rtype = বৃক্ষ_TYPE (rtype);
		যদি (SCALAR_FLOAT_TYPE_P (rtype))
		  প্রতি (unsigned পূর্ণাঙ্ক j = 0; j < অঙ্ক_FLOATNX_TYPES; j++)
		    যদি (rtype == FLOATNX_TYPE_গ্রন্থি (j))
		      {
			arg_int_floatnx = সত্য;
			ভঙ্গ;
		      }
		যদি (rtype == dfloat64x_type_গ্রন্থি)
		  arg_int_decimalx = সত্য;
	      }
	    বৃক্ষ arg_real = NULL_বৃক্ষ;
	    প্রতি (unsigned পূর্ণাঙ্ক j = 1; j <= nargs; j++)
	      {
		যদি (parm_kind[j] == tgmath_fixed)
		  অনুবর্ত;
		c_রাশিমালা_t *ce = &(*cexpr_list)[অঙ্ক_functions + j - 1];
		বৃক্ষ type = TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (ce->মান));
		যদি (বৃক্ষ_CODE (type) == COMPLEX_TYPE)
		  type = বৃক্ষ_TYPE (type);
		যদি (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_গ্রন্থি
			  : arg_int_floatnx
			  ? float32x_type_গ্রন্থি
			  : arg_int_decimal
			  ? dfloat64_type_গ্রন্থি
			  : double_type_গ্রন্থি);
		যদি (arg_real == NULL_বৃক্ষ)
		  arg_real = type;
		অন্যথা
		  arg_real = common_type (arg_real, type);
		যদি (arg_real == error_mark_গ্রন্থি)
		  {
		    রাশিমালা.set_error ();
		    গচ্ছ out;
		  }
	      }
	    বৃক্ষ arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_রাশিমালা_t *fn = রিক্ত;
	    প্রতি (unsigned পূর্ণাঙ্ক j = 0; j < অঙ্ক_functions; j++)
	      {
		যদি (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    ভঙ্গ;
		  }
	      }
	    যদি (fn == রিক্ত
		&& parm_kind[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_first[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		প্রতি (unsigned পূর্ণাঙ্ক j = 0; j < অঙ্ক_functions; j++)
		  {
		    যদি (arg_complex
			!= (বৃক্ষ_CODE (tg_type[j]) == COMPLEX_TYPE))
		      অনুবর্ত;
		    বৃক্ষ real_tg_type = (arg_complex
					 ? বৃক্ষ_TYPE (tg_type[j])
					 : tg_type[j]);
		    যদি (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      অনুবর্ত;
		    scalar_float_mode arg_mode
		      = SCALAR_FLOAT_TYPE_MODE (arg_real);
		    scalar_float_mode tg_mode
		      = SCALAR_FLOAT_TYPE_MODE (real_tg_type);
		    ধ্রুব real_format *arg_fmt = REAL_MODE_FORMAT (arg_mode);
		    ধ্রুব real_format *tg_fmt = REAL_MODE_FORMAT (tg_mode);
		    যদি (arg_fmt->b == tg_fmt->b
			&& arg_fmt->p <= tg_fmt->p
			&& arg_fmt->emax <= tg_fmt->emax
			&& (arg_fmt->emin - arg_fmt->p
			    >= tg_fmt->emin - tg_fmt->p))
		      {
			fn = &(*cexpr_list)[j];
			ভঙ্গ;
		      }
		  }
	      }
	    যদি (fn == রিক্ত)
	      {
		error_at (loc, "no matching function for type-generic call");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    /* Construct a call to FN.  */
	    vec<বৃক্ষ, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<বৃক্ষ, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    প্রতি (unsigned পূর্ণাঙ্ক j = 0; j < nargs; j++)
	      {
		c_রাশিমালা_t *ce = &(*cexpr_list)[অঙ্ক_functions + j];
		args->quick_ঠেলো (ce->মান);
		arg_loc.quick_ঠেলো (ce->get_location ());
		origtypes->quick_ঠেলো (ce->original_type);
	      }
	    রাশিমালা.মান = c_build_function_call_vec (loc, arg_loc, fn->মান,
						    args, origtypes);
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_paren_loc);
	    ভঙ্গ;
	  }
	পক্ষ RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_রাশিমালা_t, va_gc> *cexpr_list;
	    c_রাশিমালা_t *e2_p;
	    বৃক্ষ chain_মান;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    যদি (!c_parser_get_builtin_args (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, অসত্য,
					    &close_paren_loc))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    রাশিমালা = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, সত্য, সত্য);
	    chain_মান = e2_p->মান;
	    mark_exp_read (chain_মান);

	    যদি (বৃক্ষ_CODE (রাশিমালা.মান) != CALL_রাশিমালা)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    অন্যথা যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (chain_মান)) != POINTER_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    অন্যথা
	      CALL_রাশিমালা_STATIC_CHAIN (রাশিমালা.মান) = chain_মান;
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_paren_loc);
	    ভঙ্গ;
	  }
	পক্ষ RID_BUILTIN_COMPLEX:
	  {
	    vec<c_রাশিমালা_t, va_gc> *cexpr_list;
	    c_রাশিমালা_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    যদি (!c_parser_get_builtin_args (parser,
					    "__builtin_complex",
					    &cexpr_list, অসত্য,
					    &close_paren_loc))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    যদি (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_to_rvalue (loc, *e1_p, সত্য, সত্য);
	    যদি (বৃক্ষ_CODE (e1_p->মান) == EXCESS_PRECISION_রাশিমালা)
	      e1_p->মান = convert (বৃক্ষ_TYPE (e1_p->মান),
				     বৃক্ষ_OPERAND (e1_p->মান, 0));
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, সত্য, সত্য);
	    যদি (বৃক্ষ_CODE (e2_p->মান) == EXCESS_PRECISION_রাশিমালা)
	      e2_p->মান = convert (বৃক্ষ_TYPE (e2_p->মান),
				     বৃক্ষ_OPERAND (e2_p->মান, 0));
	    যদি (!SCALAR_FLOAT_TYPE_P (বৃক্ষ_TYPE (e1_p->মান))
		|| DECIMAL_FLOAT_TYPE_P (বৃক্ষ_TYPE (e1_p->মান))
		|| !SCALAR_FLOAT_TYPE_P (বৃক্ষ_TYPE (e2_p->মান))
		|| DECIMAL_FLOAT_TYPE_P (বৃক্ষ_TYPE (e2_p->মান)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (e1_p->মান))
		!= TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (e2_p->মান)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    রাশিমালা.মান = build2_loc (loc, COMPLEX_রাশিমালা,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (বৃক্ষ_TYPE (e1_p->মান))),
				     e1_p->মান, e2_p->মান);
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_paren_loc);
	    ভঙ্গ;
	  }
	পক্ষ RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_রাশিমালা_t, va_gc> *cexpr_list;
	    c_রাশিমালা_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    যদি (!c_parser_get_builtin_args (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, অসত্য,
					    &close_paren_loc))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    e_p = &(*cexpr_list)[0];
	    বৃক্ষ ref = e_p->মান;

	    যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (ref)) != ARRAY_TYPE
		 && বৃক্ষ_CODE (বৃক্ষ_TYPE (ref)) != POINTER_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    যদি (বৃক্ষ_CODE (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    যদি (বৃক্ষ_CODE (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    যদি (has_counted_by_object (ref))
	      রাশিমালা.মান = get_counted_by_ref (ref);
	    অন্যথা
	      রাশিমালা.মান = null_pointer_গ্রন্থি;

	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_paren_loc);
	    ভঙ্গ;
	  }
	পক্ষ RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_রাশিমালা_t, va_gc> *cexpr_list;
	    unsigned পূর্ণাঙ্ক i;
	    c_রাশিমালা_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    যদি (!c_parser_get_builtin_args (parser,
					    "__builtin_shuffle",
					    &cexpr_list, অসত্য,
					    &close_paren_loc))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, সত্য, সত্য);

	    যদি (vec_safe_length (cexpr_list) == 2)
	      রাশিমালা.মান = c_build_vec_perm_রাশিমালা (loc, (*cexpr_list)[0].মান,
						  NULL_বৃক্ষ,
						  (*cexpr_list)[1].মান);

	    অন্যথা যদি (vec_safe_length (cexpr_list) == 3)
	      রাশিমালা.মান = c_build_vec_perm_রাশিমালা (loc, (*cexpr_list)[0].মান,
						  (*cexpr_list)[1].মান,
						  (*cexpr_list)[2].মান);
	    অন্যথা
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		রাশিমালা.set_error ();
	      }
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_paren_loc);
	    ভঙ্গ;
	  }
	পক্ষ RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_রাশিমালা_t, va_gc> *cexpr_list;
	    unsigned পূর্ণাঙ্ক i;
	    c_রাশিমালা_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    যদি (!c_parser_get_builtin_args (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, অসত্য,
					    &close_paren_loc))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, সত্য, সত্য);

	    যদি (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		রাশিমালা.set_error ();
	      }
	    অন্যথা
	      {
		auto_vec<বৃক্ষ, 16> mask;
		প্রতি (i = 2; i < cexpr_list->length (); ++i)
		  mask.safe_ঠেলো ((*cexpr_list)[i].মান);
		রাশিমালা.মান = c_build_shufflevector (loc, (*cexpr_list)[0].মান,
						    (*cexpr_list)[1].মান,
						    mask);
	      }
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_paren_loc);
	    ভঙ্গ;
	  }
	পক্ষ RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    যদি (!parens.require_open (parser))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    e1 = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	    mark_exp_read (e1.মান);
	    যদি (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    যদি (t1 == রিক্ত)
	      রাশিমালা.set_error ();
	    অন্যথা
	      {
		বৃক্ষ type_রাশিমালা = NULL_বৃক্ষ;
		রাশিমালা.মান = c_build_vec_convert (start_loc, e1.মান, loc,
						  groktypename (t1, &type_রাশিমালা,
								রিক্ত));
		set_c_রাশিমালা_source_range (&রাশিমালা, start_loc, end_loc);
	      }
	  }
	  ভঙ্গ;
	পক্ষ RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    যদি (!parens.require_open (parser))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    e1 = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	    mark_exp_read (e1.মান);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    parens.skip_until_found_close (parser);
	    রাশিমালা = parser_build_unary_op (loc, PAREN_রাশিমালা, e1);
	    set_c_রাশিমালা_source_range (&রাশিমালা, start_loc, end_loc);
	  }
	  ভঙ্গ;
	পক্ষ RID_BUILTIN_STDC:
	  {
	    vec<c_রাশিমালা_t, va_gc> *cexpr_list;
	    c_রাশিমালা_t *arg_p;
	    location_t close_paren_loc;
	    গণনা c_builtin_stdc {
	      C_BUILTIN_STDC_BIT_CEIL,
	      C_BUILTIN_STDC_BIT_FLOOR,
	      C_BUILTIN_STDC_BIT_WIDTH,
	      C_BUILTIN_STDC_গুনতি_ONES,
	      C_BUILTIN_STDC_গুনতি_ZEROS,
	      C_BUILTIN_STDC_FIRST_LEADING_ONE,
	      C_BUILTIN_STDC_FIRST_LEADING_ZERO,
	      C_BUILTIN_STDC_FIRST_TRAILING_ONE,
	      C_BUILTIN_STDC_FIRST_TRAILING_ZERO,
	      C_BUILTIN_STDC_HAS_SINGLE_BIT,
	      C_BUILTIN_STDC_LEADING_ONES,
	      C_BUILTIN_STDC_LEADING_ZEROS,
	      C_BUILTIN_STDC_ROTATE_বাম,
	      C_BUILTIN_STDC_ROTATE_ডান,
	      C_BUILTIN_STDC_TRAILING_ONES,
	      C_BUILTIN_STDC_TRAILING_ZEROS,
	      C_BUILTIN_STDC_MAX
	    } stdc_rid = C_BUILTIN_STDC_MAX;
	    ধ্রুব বর্ণ *name
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
	    unsigned অঙ্ক_args = 1;
	    বিকল্প (name[পরিমাণ ("__builtin_stdc_") - 1])
	      {
	      পক্ষ 'b':
		বিকল্প (name[পরিমাণ ("__builtin_stdc_bit_") - 1])
		  {
		  পক্ষ 'c':
		    stdc_rid = C_BUILTIN_STDC_BIT_CEIL;
		    ভঙ্গ;
		  পক্ষ 'f':
		    stdc_rid = C_BUILTIN_STDC_BIT_FLOOR;
		    ভঙ্গ;
		  স্বভাব:
		    stdc_rid = C_BUILTIN_STDC_BIT_WIDTH;
		    ভঙ্গ;
		  }
		ভঙ্গ;
	      পক্ষ 'c':
		যদি (name[পরিমাণ ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_গুনতি_ONES;
		অন্যথা
		  stdc_rid = C_BUILTIN_STDC_গুনতি_ZEROS;
		ভঙ্গ;
	      পক্ষ 'f':
		বিকল্প (name[পরিমাণ ("__builtin_stdc_first_trailing_") - 1])
		  {
		  পক্ষ 'n':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ONE;
		    ভঙ্গ;
		  পক্ষ 'e':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ZERO;
		    ভঙ্গ;
		  পক্ষ 'o':
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ONE;
		    ভঙ্গ;
		  স্বভাব:
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ZERO;
		    ভঙ্গ;
		  }
		ভঙ্গ;
	      পক্ষ 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_BIT;
		ভঙ্গ;
	      পক্ষ 'l':
		যদি (name[পরিমাণ ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		অন্যথা
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		ভঙ্গ;
	      পক্ষ 'r':
		যদি (name[পরিমাণ ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_বাম;
		অন্যথা
		  stdc_rid = C_BUILTIN_STDC_ROTATE_ডান;
		অঙ্ক_args = 2;
		ভঙ্গ;
	      পক্ষ 't':
		যদি (name[পরিমাণ ("__builtin_stdc_trailing_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ONES;
		অন্যথা
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ZEROS;
		ভঙ্গ;
	      }
	    gcc_checking_assert (stdc_rid != C_BUILTIN_STDC_MAX);

	    c_parser_consume_token (parser);
	    যদি (!c_parser_get_builtin_args (parser, name,
					    &cexpr_list, অসত্য,
					    &close_paren_loc))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    যদি (vec_safe_length (cexpr_list) != অঙ্ক_args)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, সত্য, সত্য);
	    যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (arg_p->মান)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (arg_p->মান)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (arg_p->মান)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (!TYPE_UNSIGNED (বৃক্ষ_TYPE (arg_p->মান)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (arg_p->মান))
		== char_type_গ্রন্থি)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    বৃক্ষ arg = arg_p->মান;
	    বৃক্ষ type = TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (arg));
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
	    পূর্ণাঙ্ক prec = TYPE_PRECISION (type);
	    যদি (অঙ্ক_args == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_to_rvalue (loc, *arg_p, সত্য, সত্য);
		যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (arg_p->মান)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    রাশিমালা.set_error ();
		    ভঙ্গ;
		  }
		যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (arg_p->মান)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    রাশিমালা.set_error ();
		    ভঙ্গ;
		  }
		বৃক্ষ arg1 = save_রাশিমালা (arg);
		বৃক্ষ arg2 = save_রাশিমালা (arg_p->মান);
		বৃক্ষ_code code;
		যদি (stdc_rid == C_BUILTIN_STDC_ROTATE_বাম)
		  code = LROTATE_রাশিমালা;
		অন্যথা
		  code = RROTATE_রাশিমালা;

		যদি (বৃক্ষ_CODE (arg2) == INTEGER_CST
		    && বৃক্ষ_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_গুনতি_negative,
			      "rotate count is negative");

		বৃক্ষ instrument_রাশিমালা = NULL_বৃক্ষ;
		যদি (sanitize_flags_p (SANITIZE_SHIFT))
		  instrument_রাশিমালা = ubsan_instrument_shift (loc, code,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		যদি (TYPE_PRECISION (বৃক্ষ_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_গ্রন্থি))
		  arg2 = fold_convert (unsigned_type_গ্রন্থি, arg2);

		যদি (TYPE_UNSIGNED (বৃক্ষ_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_রাশিমালা, বৃক্ষ_TYPE (arg2),
				     arg2, build_int_cst (বৃক্ষ_TYPE (arg2),
							  prec));
		অন্যথা
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    বৃক্ষ utype = c_common_unsigned_type (বৃক্ষ_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_রাশিমালা, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		যদি (type_has_mode_precision_p (বৃক্ষ_TYPE (arg1))
		    || (বৃক্ষ_CODE (বৃক্ষ_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_MODE_SIZE))
		  রাশিমালা.মান = build2_loc (loc, code, বৃক্ষ_TYPE (arg1), arg1,
					   arg2);
		অন্যথা
		  {
		    arg2 = save_রাশিমালা (arg2);
		    বৃক্ষ t1 = build2_loc (loc, (code == LROTATE_রাশিমালা
						? LSHIFT_রাশিমালা : RSHIFT_রাশিমালা),
					  বৃক্ষ_TYPE (arg1), arg1, arg2);
		    বৃক্ষ t2 = build2_loc (loc, MINUS_রাশিমালা,
					  বৃক্ষ_TYPE (arg2),
					  build_int_cst (বৃক্ষ_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (code == LROTATE_রাশিমালা
					   ? RSHIFT_রাশিমালা : LSHIFT_রাশিমালা),
				     বৃক্ষ_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_গুনতি_overflow);
		    বৃক্ষ t3 = build2_loc (loc, BIT_IOR_রাশিমালা,
					  বৃক্ষ_TYPE (arg1), t1, t2);
		    বৃক্ষ t4 = build2_loc (loc, NE_রাশিমালা, boolean_type_গ্রন্থি,
					  arg2,
					  build_zero_cst (বৃক্ষ_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_রাশিমালা, boolean_type_গ্রন্থি,
				     arg1, t4);
		    রাশিমালা.মান = build3_loc (loc, COND_রাশিমালা,
					     বৃক্ষ_TYPE (arg1), t4, t3, arg1);
		  }
		যদি (instrument_রাশিমালা)
		  রাশিমালা.মান = build2_loc (loc, COMPOUND_রাশিমালা,
					   বৃক্ষ_TYPE (রাশিমালা.মান),
					   instrument_রাশিমালা, রাশিমালা.মান);
		set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_paren_loc);
		ভঙ্গ;
	      }
	    বৃক্ষ barg1 = arg;
	    বিকল্প (stdc_rid)
	      {
	      পক্ষ C_BUILTIN_STDC_BIT_CEIL:
		arg = save_রাশিমালা (arg);
		barg1 = build2_loc (loc, PLUS_রাশিমালা, type, arg,
				    build_int_cst (type, -1));
		ভঙ্গ;
	      পক্ষ C_BUILTIN_STDC_BIT_FLOOR:
		barg1 = arg = save_রাশিমালা (arg);
		ভঙ্গ;
	      পক্ষ C_BUILTIN_STDC_গুনতি_ZEROS:
	      পক্ষ C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      পক্ষ C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      পক্ষ C_BUILTIN_STDC_LEADING_ONES:
	      পক্ষ C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, BIT_NOT_রাশিমালা, type, arg);
		ভঙ্গ;
	      স্বভাব:
		ভঙ্গ;
	      }
	    বৃক্ষ barg2 = NULL_বৃক্ষ;
	    বিকল্প (stdc_rid)
	      {
	      পক্ষ C_BUILTIN_STDC_BIT_WIDTH:
	      পক্ষ C_BUILTIN_STDC_LEADING_ONES:
	      পক্ষ C_BUILTIN_STDC_LEADING_ZEROS:
	      পক্ষ C_BUILTIN_STDC_TRAILING_ONES:
	      পক্ষ C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_গ্রন্থি, prec);
		ভঙ্গ;
	      পক্ষ C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      পক্ষ C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      পক্ষ C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      পক্ষ C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		barg2 = integer_minus_one_গ্রন্থি;
		ভঙ্গ;
	      স্বভাব:
		ভঙ্গ;
	      }
	    বৃক্ষ fndecl = NULL_বৃক্ষ;
	    বিকল্প (stdc_rid)
	      {
	      পক্ষ C_BUILTIN_STDC_BIT_CEIL:
	      পক্ষ C_BUILTIN_STDC_BIT_FLOOR:
	      পক্ষ C_BUILTIN_STDC_BIT_WIDTH:
	      পক্ষ C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      পক্ষ C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      পক্ষ C_BUILTIN_STDC_LEADING_ONES:
	      পক্ষ C_BUILTIN_STDC_LEADING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CLZG);
		ভঙ্গ;
	      পক্ষ C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      পক্ষ C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      পক্ষ C_BUILTIN_STDC_TRAILING_ONES:
	      পক্ষ C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CTZG);
		ভঙ্গ;
	      পক্ষ C_BUILTIN_STDC_গুনতি_ONES:
	      পক্ষ C_BUILTIN_STDC_গুনতি_ZEROS:
	      পক্ষ C_BUILTIN_STDC_HAS_SINGLE_BIT:
		fndecl = builtin_decl_explicit (BUILT_IN_POPCOUNTG);
		ভঙ্গ;
	      স্বভাব:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    পূর্ণাঙ্ক nargs = barg2 != NULL_বৃক্ষ ? 2 : 1;
	    vec<বৃক্ষ, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<বৃক্ষ, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    args->quick_ঠেলো (barg1);
	    arg_loc.quick_ঠেলো (arg_p->get_location ());
	    origtypes->quick_ঠেলো (arg_p->original_type);
	    যদি (nargs == 2)
	      {
		args->quick_ঠেলো (barg2);
		arg_loc.quick_ঠেলো (loc);
		origtypes->quick_ঠেলো (integer_type_গ্রন্থি);
	      }
	    রাশিমালা.মান = c_build_function_call_vec (loc, arg_loc, fndecl,
						    args, origtypes);
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_paren_loc);
	    যদি (রাশিমালা.মান == error_mark_গ্রন্থি)
	      ভঙ্গ;
	    বিকল্প (stdc_rid)
	      {
	      পক্ষ C_BUILTIN_STDC_BIT_CEIL:
	      পক্ষ C_BUILTIN_STDC_BIT_FLOOR:
		--prec;
		/* FALLTHRU */
	      পক্ষ C_BUILTIN_STDC_BIT_WIDTH:
		রাশিমালা.মান = build2_loc (loc, MINUS_রাশিমালা, integer_type_গ্রন্থি,
					 build_int_cst (integer_type_গ্রন্থি,
							prec), রাশিমালা.মান);
		ভঙ্গ;
	      পক্ষ C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      পক্ষ C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      পক্ষ C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      পক্ষ C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		রাশিমালা.মান = build2_loc (loc, PLUS_রাশিমালা, integer_type_গ্রন্থি,
					 রাশিমালা.মান, integer_one_গ্রন্থি);
		ভঙ্গ;
	      পক্ষ C_BUILTIN_STDC_HAS_SINGLE_BIT:
		রাশিমালা.মান = build2_loc (loc, EQ_রাশিমালা, boolean_type_গ্রন্থি,
					 রাশিমালা.মান, integer_one_গ্রন্থি);
		ভঙ্গ;
	      স্বভাব:
		ভঙ্গ;
	      }

	    যদি (stdc_rid != C_BUILTIN_STDC_BIT_CEIL
		&& stdc_rid != C_BUILTIN_STDC_BIT_FLOOR)
	      {
		যদি (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_BIT)
		  রাশিমালা.মান = fold_convert_loc (loc, unsigned_type_গ্রন্থি,
						 রাশিমালা.মান);
		ভঙ্গ;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    যদি (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_BIT_CEIL && integer_onep (arg)))
	      রাশিমালা.মান = build_int_cst (type, 0);
	    অন্যথা
	      রাশিমালা.মান
		= build2_loc (loc, LSHIFT_রাশিমালা, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_BIT_CEIL
					      ? 2 : 1)), রাশিমালা.মান);
	    যদি (stdc_rid == C_BUILTIN_STDC_BIT_CEIL)
	      রাশিমালা.মান = build3_loc (loc, COND_রাশিমালা, type,
				       build2_loc (loc, LE_রাশিমালা,
						   boolean_type_গ্রন্থি, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       রাশিমালা.মান);
	    অন্যথা
	      রাশিমালা.মান = build3_loc (loc, COND_রাশিমালা, type,
				       build2_loc (loc, EQ_রাশিমালা,
						   boolean_type_গ্রন্থি, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       রাশিমালা.মান);
	    ভঙ্গ;
	  }
	পক্ষ RID_BUILTIN_BSWAPG:
	পক্ষ RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_রাশিমালা_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    internal_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    ধ্রুব বর্ণ *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    যদি (!c_parser_get_builtin_args (parser, name, &cexpr_list, অসত্য,
					    &close_paren_loc))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    যদি (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }

	    c_রাশিমালা_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, সত্য, সত্য);
	    বৃক্ষ arg = arg_p->মান;
	    যদি (error_operand_p (arg))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    বৃক্ষ type = TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (arg));
	    যদি (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (বৃক্ষ_CODE (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (বৃক্ষ_CODE (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    arg = c_fully_fold (arg, অসত্য, রিক্ত);
	    রাশিমালা.মান = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_paren_loc);
	    ভঙ্গ;
	  }
	পক্ষ RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    যদি (!parens.require_open (parser))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    বৃক্ষ sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    রাশিমালা.মান = objc_build_selector_রাশিমালা (loc, sel);
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_loc);
	  }
	  ভঙ্গ;
	পক্ষ RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    যদি (!parens.require_open (parser))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    যদি (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    বৃক্ষ id = c_parser_peek_token (parser)->মান;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    রাশিমালা.মান = objc_build_protocol_রাশিমালা (id);
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_loc);
	  }
	  ভঙ্গ;
	পক্ষ RID_AT_ENCODE:
	  {
	    /* Extension to support C-structures in the archiver.  */
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    যদি (!parens.require_open (parser))
	      {
		রাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    t1 = c_parser_type_name (parser);
	    যদি (t1 == রিক্ত)
	      {
		রাশিমালা.set_error ();
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
		ভঙ্গ;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    বৃক্ষ type = groktypename (t1, রিক্ত, রিক্ত);
	    রাশিমালা.মান = objc_build_encode_রাশিমালা (type);
	    set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_loc);
	  }
	  ভঙ্গ;
	পক্ষ RID_GENERIC:
	  রাশিমালা = c_parser_generic_selection (parser);
	  ভঙ্গ;
	পক্ষ RID_OMP_ALL_MEMORY:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  রাশিমালা.set_error ();
	  ভঙ্গ;
	/* C23 'nullptr' literal.  */
	পক্ষ RID_NULLPTR:
	  c_parser_consume_token (parser);
	  রাশিমালা.মান = nullptr_গ্রন্থি;
	  set_c_রাশিমালা_source_range (&রাশিমালা, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  ভঙ্গ;
	পক্ষ RID_TRUE:
	  c_parser_consume_token (parser);
	  রাশিমালা.মান = boolean_true_গ্রন্থি;
	  set_c_রাশিমালা_source_range (&রাশিমালা, tok_range);
	  ভঙ্গ;
	পক্ষ RID_FALSE:
	  c_parser_consume_token (parser);
	  রাশিমালা.মান = boolean_false_গ্রন্থি;
	  set_c_রাশিমালা_source_range (&রাশিমালা, tok_range);
	  ভঙ্গ;
	স্বভাব:
	  c_parser_error (parser, "expected expression");
	  রাশিমালা.set_error ();
	  ভঙ্গ;
	}
      ভঙ্গ;
    পক্ষ CPP_OPEN_SQUARE:
      যদি (c_dialect_objc ())
	{
	  বৃক্ষ receiver, args;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  args = c_parser_objc_message_args (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  রাশিমালা.মান = objc_build_message_রাশিমালা (receiver, args);
	  set_c_রাশিমালা_source_range (&রাশিমালা, loc, close_loc);
	  ভঙ্গ;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    স্বভাব:
      c_parser_error (parser, "expected expression");
      রাশিমালা.set_error ();
      ভঙ্গ;
    }
 out:
  প্রত্যাগম c_parser_postfix_expression_after_primary
    (parser, রাশিমালা_LOC_OR_LOC (রাশিমালা.মান, loc), রাশিমালা);
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

স্থির সংরচনা c_রাশিমালা
c_parser_postfix_expression_after_paren_type (c_parser *parser,
					      সংরচনা c_declspecs *scspecs,
					      সংরচনা c_type_name *type_name,
					      location_t type_loc)
{
  বৃক্ষ type;
  সংরচনা c_রাশিমালা init;
  তার্কিক non_const;
  সংরচনা c_রাশিমালা রাশিমালা;
  location_t start_loc;
  বৃক্ষ type_রাশিমালা = NULL_বৃক্ষ;
  তার্কিক type_রাশিমালা_const = সত্য;
  তার্কিক constexpr_p = scspecs ? scspecs->constexpr_p : অসত্য;
  unsigned পূর্ণাঙ্ক underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (সারি_table, type_loc);
  start_loc = c_parser_peek_token (parser)->location;
  যদি (constexpr_p)
    {
      underspec_state = start_underspecified_init (start_loc, NULL_বৃক্ষ);
      /* A constexpr compound literal is subject to the constraints on
	 underspecified declarations, which may not declare tags or
	 members or structures or unions; it is undefined behavior to
	 declare the members of an enumeration.  Where the structure,
	 union or enumeration type is declared within the compound
	 literal initializer, this is diagnosed elsewhere as a result
	 of the above call to start_underspecified_init.  Diagnose
	 here the case of declaring such a type in the type specifiers
	 of the compound literal.  */
      বিকল্প (type_name->specs->typespec_kind)
	{
	পক্ষ ctsk_tagfirstref:
	পক্ষ ctsk_tagfirstref_attrs:
	  error_at (type_loc, "%qT declared in %<constexpr%> compound literal",
		    type_name->specs->type);
	  ভঙ্গ;

	পক্ষ ctsk_tagdef:
	  error_at (type_loc, "%qT defined in %<constexpr%> compound literal",
		    type_name->specs->type);
	  ভঙ্গ;

	স্বভাব:
	  ভঙ্গ;
	}
    }
  start_init (NULL_বৃক্ষ, রিক্ত,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_রাশিমালা, &type_রাশিমালা_const);
  তার্কিক varsize_p = অসত্য;
  যদি (type != error_mark_গ্রন্থি && C_TYPE_VARIABLE_SIZE (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = সত্য;
    }
  অন্যথা যদি (বৃক্ষ_CODE (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_গ্রন্থি;
    }
  যদি (constexpr_p && type != error_mark_গ্রন্থি)
    {
      বৃক্ষ type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      যদি (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      অন্যথা যদি (RECORD_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, অসত্য, রিক্ত, varsize_p);
  যদি (constexpr_p)
    finish_underspecified_init (NULL_বৃক্ষ, underspec_state);
  finish_init ();
  maybe_warn_string_init (type_loc, type, init);

  যদি (type != error_mark_গ্রন্থি
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_গ্রন্থি;
    }

  যদি (!pedwarn_c90 (start_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (start_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.মান && বৃক্ষ_CODE (init.মান) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.মান)
	       : init.original_code == C_MAYBE_CONST_রাশিমালা);
  non_const |= !type_রাশিমালা_const;
  unsigned পূর্ণাঙ্ক alignas_align = 0;
  যদি (type != error_mark_গ্রন্থি
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      যদি (alignas_align < min_align_of_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  রাশিমালা.মান = build_compound_literal (start_loc, type, init.মান, non_const,
				       alignas_align, scspecs);
  set_c_রাশিমালা_source_range (&রাশিমালা, init.src_range);
  রাশিমালা.m_decimal = 0;
  রাশিমালা.original_code = ERROR_MARK;
  রাশিমালা.original_type = রিক্ত;
  যদি (type != error_mark_গ্রন্থি
      && রাশিমালা.মান != error_mark_গ্রন্থি
      && type_রাশিমালা)
    {
      যদি (বৃক্ষ_CODE (রাশিমালা.মান) == C_MAYBE_CONST_রাশিমালা)
	{
	  gcc_assert (C_MAYBE_CONST_রাশিমালা_PRE (রাশিমালা.মান) == NULL_বৃক্ষ);
	  C_MAYBE_CONST_রাশিমালা_PRE (রাশিমালা.মান) = type_রাশিমালা;
	}
      অন্যথা
	{
	  gcc_assert (!non_const);
	  রাশিমালা.মান = build2 (C_MAYBE_CONST_রাশিমালা, type,
			       type_রাশিমালা, রাশিমালা.মান);
	}
    }
  প্রত্যাগম c_parser_postfix_expression_after_primary (parser, start_loc, রাশিমালা);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

স্থির তার্কিক
sizeof_ptr_memacc_comptypes (বৃক্ষ type1, বৃক্ষ type2)
{
  প্রত্যাগম comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

স্থির শূন্য
warn_for_abs (location_t loc, বৃক্ষ fndecl, বৃক্ষ arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  যদি (c_inhibit_evaluation_warnings)
    প্রত্যাগম;

  বৃক্ষ atype = বৃক্ষ_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  যদি (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && বৃক্ষ_CODE (atype) != COMPLEX_TYPE)
    প্রত্যাগম;

  গণনা built_in_function fcode = DECL_FUNCTION_CODE (fndecl);

  বিকল্প (fcode)
    {
    পক্ষ BUILT_IN_ABS:
    পক্ষ BUILT_IN_LABS:
    পক্ষ BUILT_IN_LLABS:
    পক্ষ BUILT_IN_IMAXABS:
      যদি (!INTEGRAL_TYPE_P (atype))
	{
	  যদি (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_মান,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  অন্যথা যদি (বৃক্ষ_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_মান,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  অন্যথা
	    gcc_unreachable ();
	  প্রত্যাগম;
	}
      যদি (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_মান,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      ভঙ্গ;

    CASE_FLT_FN (BUILT_IN_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FABS):
      যদি (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_MODE_P (TYPE_MODE (atype)))
	{
	  যদি (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_মান,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  অন্যথা যদি (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_মান,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  অন্যথা যদি (বৃক্ষ_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_মান,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  অন্যথা
	    gcc_unreachable ();
	  প্রত্যাগম;
	}
      ভঙ্গ;

    CASE_FLT_FN (BUILT_IN_CABS):
      যদি (বৃক্ষ_CODE (atype) != COMPLEX_TYPE)
	{
	  যদি (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_মান,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  অন্যথা যদি (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_মান,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  অন্যথা
	    gcc_unreachable ();

	  প্রত্যাগম;
	}
      ভঙ্গ;

    পক্ষ BUILT_IN_FABSD32:
    পক্ষ BUILT_IN_FABSD64:
    পক্ষ BUILT_IN_FABSD128:
    পক্ষ BUILT_IN_FABSD64X:
      যদি (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  যদি (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_মান,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  অন্যথা যদি (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_মান,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  অন্যথা যদি (বৃক্ষ_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_মান,
			"using decimal floating-point absolute value "
			"function %qD when argument is of complex type %qT",
			fndecl, atype);
	  অন্যথা
	    gcc_unreachable ();
	  প্রত্যাগম;
	}
      ভঙ্গ;

    স্বভাব:
      প্রত্যাগম;
    }

  যদি (!TYPE_ARG_TYPES (বৃক্ষ_TYPE (fndecl)))
    প্রত্যাগম;

  বৃক্ষ ftype = বৃক্ষ_মান (TYPE_ARG_TYPES (বৃক্ষ_TYPE (fndecl)));
  যদি (বৃক্ষ_CODE (atype) == COMPLEX_TYPE)
    {
      gcc_assert (বৃক্ষ_CODE (ftype) == COMPLEX_TYPE);
      atype = বৃক্ষ_TYPE (atype);
      ftype = বৃক্ষ_TYPE (ftype);
    }

  যদি (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_মান,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

স্থির সংরচনা c_রাশিমালা
c_parser_postfix_expression_after_primary (c_parser *parser,
					   location_t রাশিমালা_loc,
					   সংরচনা c_রাশিমালা রাশিমালা)
{
  সংরচনা c_রাশিমালা orig_রাশিমালা;
  বৃক্ষ ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  বৃক্ষ sizeof_arg[6];
  unsigned পূর্ণাঙ্ক literal_zero_mask;
  unsigned পূর্ণাঙ্ক i;
  vec<বৃক্ষ, va_gc> *exprlist;
  vec<বৃক্ষ, va_gc> *origtypes = রিক্ত;
  vec<location_t> arg_loc = vNULL;
  location_t start;
  location_t finish;

  যাবত্ (সত্য)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      বিকল্প (c_parser_peek_token (parser)->type)
	{
	পক্ষ CPP_OPEN_SQUARE:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_বৃক্ষ;
	  যদি (!c_omp_array_section_p
	      || c_parser_next_token_is_not (parser, CPP_COLON))
	    idx = c_parser_expression (parser).মান;

	  যদি (c_omp_array_section_p
	      && c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      যদি (c_parser_next_token_is_not (parser, CPP_CLOSE_SQUARE))
		len = c_parser_expression (parser).মান;

	      রাশিমালা.মান = build_omp_array_section (op_loc, রাশিমালা.মান, idx,
						    len);
	    }
	  অন্যথা
	    রাশিমালা.মান = build_array_ref (op_loc, রাশিমালা.মান, idx);

	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");

	  start = রাশিমালা.get_start ();
	  finish = parser->tokens_buf[0].location;
	  set_c_রাশিমালা_source_range (&রাশিমালা, start, finish);
	  রাশিমালা.original_code = ERROR_MARK;
	  রাশিমালা.original_type = রিক্ত;
	  রাশিমালা.m_decimal = 0;
	  ভঙ্গ;
	পক্ষ CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    প্রতি (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_বৃক্ষ;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_mask = 0;
	    যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = রিক্ত;
	    অন্যথা যদি (বৃক্ষ_CODE (রাশিমালা.মান) == FUNCTION_DECL
		     && fndecl_built_in_p (রাশিমালা.মান, BUILT_IN_CLASSIFY_TYPE)
		     && c_parser_next_tokens_start_typename (parser,
							     cla_prefer_id))
	      {
		/* __builtin_classify_type (type)  */
		c_inhibit_evaluation_warnings++;
		in_alignof++;
		সংরচনা c_type_name *type = c_parser_type_name (parser);
		c_inhibit_evaluation_warnings--;
		in_alignof--;
		সংরচনা c_typespec ret;
		ret.রাশিমালা = NULL_বৃক্ষ;
		ret.spec = error_mark_গ্রন্থি;
		ret.রাশিমালা_const_operands = অসত্য;
		যদি (type != রিক্ত)
		  ret.spec = groktypename (type, &ret.রাশিমালা,
					   &ret.রাশিমালা_const_operands);
		parens.skip_until_found_close (parser);
		রাশিমালা.মান = build_int_cst (integer_type_গ্রন্থি,
					    type_to_class (ret.spec));
		ভঙ্গ;
	      }
	    অন্যথা
	      exprlist = c_parser_রাশিমালা_list (parser, সত্য, অসত্য, &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_mask);
	    parens.skip_until_found_close (parser);
	  }
	  orig_রাশিমালা = রাশিমালা;
	  mark_exp_read (রাশিমালা.মান);
	  যদি (warn_sizeof_pointer_memaccess)
	    sizeof_pointer_memaccess_warning (sizeof_arg_loc,
					      রাশিমালা.মান, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  যদি (বৃক্ষ_CODE (রাশিমালা.মান) == FUNCTION_DECL)
	    {
	      যদি (fndecl_built_in_p (রাশিমালা.মান, BUILT_IN_MEMSET)
		  && vec_safe_length (exprlist) == 3)
		{
		  বৃক্ষ arg0 = (*exprlist)[0];
		  বৃক্ষ arg2 = (*exprlist)[2];
		  warn_for_memset (রাশিমালা_loc, arg0, arg2, literal_zero_mask);
		}
	      যদি (warn_absolute_মান
		  && fndecl_built_in_p (রাশিমালা.মান, BUILT_IN_NORMAL)
		  && vec_safe_length (exprlist) == 1)
		warn_for_abs (রাশিমালা_loc, রাশিমালা.মান, (*exprlist)[0]);
	      যদি (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->in_intervening_code
		  && omp_runtime_api_call (রাশিমালা.মান))
		{
		  error_at (রাশিমালা_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->fail = সত্য;
		}
	      যদি (warn_calloc_transposed_args)
		যদি (বৃক্ষ attr = lookup_attribute ("alloc_size",
						  TYPE_ATTRIBUTES
						    (বৃক্ষ_TYPE (রাশিমালা.মান))))
		  যদি (বৃক্ষ_মান (attr) && বৃক্ষ_CHAIN (বৃক্ষ_মান (attr)))
		    warn_for_calloc (sizeof_arg_loc, রাশিমালা.মান, exprlist,
				     sizeof_arg, attr);
	    }

	  start = রাশিমালা.get_start ();
	  finish = parser->tokens_buf[0].get_finish ();
	  রাশিমালা.মান
	    = c_build_function_call_vec (রাশিমালা_loc, arg_loc, রাশিমালা.মান,
					 exprlist, origtypes);
	  set_c_রাশিমালা_source_range (&রাশিমালা, start, finish);
	  রাশিমালা.m_decimal = 0;

	  রাশিমালা.original_code = ERROR_MARK;
	  যদি (বৃক্ষ_CODE (রাশিমালা.মান) == INTEGER_CST
	      && বৃক্ষ_CODE (orig_রাশিমালা.মান) == FUNCTION_DECL
	      && fndecl_built_in_p (orig_রাশিমালা.মান, BUILT_IN_CONSTANT_P))
	    রাশিমালা.original_code = C_MAYBE_CONST_রাশিমালা;
	  রাশিমালা.original_type = রিক্ত;
	  যদি (exprlist)
	    {
	      release_বৃক্ষ_vector (exprlist);
	      release_বৃক্ষ_vector (origtypes);
	    }
	  arg_loc.release ();
	  ভঙ্গ;
	পক্ষ CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  রাশিমালা = default_function_array_conversion (রাশিমালা_loc, রাশিমালা);
	  যদি (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->মান;
	      comp_loc = comp_tok->location;
	    }
	  অন্যথা
	    {
	      c_parser_error (parser, "expected identifier");
	      রাশিমালা.set_error ();
	      রাশিমালা.original_code = ERROR_MARK;
              রাশিমালা.original_type = রিক্ত;
	      প্রত্যাগম রাশিমালা;
	    }
	  start = রাশিমালা.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  রাশিমালা.মান = build_component_ref (op_loc, রাশিমালা.মান, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  set_c_রাশিমালা_source_range (&রাশিমালা, start, finish);
	  রাশিমালা.original_code = ERROR_MARK;
	  যদি (বৃক্ষ_CODE (রাশিমালা.মান) != COMPONENT_REF)
	    রাশিমালা.original_type = রিক্ত;
	  অন্যথা
	    {
	      /* Remember the original type of a bitfield.  */
	      বৃক্ষ field = বৃক্ষ_OPERAND (রাশিমালা.মান, 1);
	      যদি (বৃক্ষ_CODE (field) != FIELD_DECL)
		রাশিমালা.original_type = রিক্ত;
	      অন্যথা
		রাশিমালা.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  রাশিমালা.m_decimal = 0;
	  ভঙ্গ;
	পক্ষ CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, সত্য, অসত্য);
	  যদি (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->মান;
	      comp_loc = comp_tok->location;
	    }
	  অন্যথা
	    {
	      c_parser_error (parser, "expected identifier");
	      রাশিমালা.set_error ();
	      রাশিমালা.original_code = ERROR_MARK;
	      রাশিমালা.original_type = রিক্ত;
	      প্রত্যাগম রাশিমালা;
	    }
	  start = রাশিমালা.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  রাশিমালা.মান = build_component_ref (op_loc,
					    build_indirect_ref (op_loc,
								রাশিমালা.মান,
								RO_ARROW),
					    ident, comp_loc,
					    রাশিমালা.get_location ());
	  set_c_রাশিমালা_source_range (&রাশিমালা, start, finish);
	  রাশিমালা.original_code = ERROR_MARK;
	  যদি (বৃক্ষ_CODE (রাশিমালা.মান) != COMPONENT_REF)
	    রাশিমালা.original_type = রিক্ত;
	  অন্যথা
	    {
	      /* Remember the original type of a bitfield.  */
	      বৃক্ষ field = বৃক্ষ_OPERAND (রাশিমালা.মান, 1);
	      যদি (বৃক্ষ_CODE (field) != FIELD_DECL)
		রাশিমালা.original_type = রিক্ত;
	      অন্যথা
		রাশিমালা.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  রাশিমালা.m_decimal = 0;
	  ভঙ্গ;
	পক্ষ CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  start = রাশিমালা.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (রাশিমালা.মান);
	  রাশিমালা = default_function_array_conversion (রাশিমালা_loc, রাশিমালা);
	  রাশিমালা.মান = build_unary_op (op_loc, POSTINCREMENT_রাশিমালা,
				       রাশিমালা.মান, অসত্য);
	  set_c_রাশিমালা_source_range (&রাশিমালা, start, finish);
	  রাশিমালা.original_code = ERROR_MARK;
	  রাশিমালা.original_type = রিক্ত;
	  ভঙ্গ;
	পক্ষ CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  start = রাশিমালা.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (রাশিমালা.মান);
	  রাশিমালা = default_function_array_conversion (রাশিমালা_loc, রাশিমালা);
	  রাশিমালা.মান = build_unary_op (op_loc, POSTDECREMENT_রাশিমালা,
				       রাশিমালা.মান, অসত্য);
	  set_c_রাশিমালা_source_range (&রাশিমালা, start, finish);
	  রাশিমালা.original_code = ERROR_MARK;
	  রাশিমালা.original_type = রিক্ত;
	  ভঙ্গ;
	স্বভাব:
	  প্রত্যাগম রাশিমালা;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

স্থির সংরচনা c_রাশিমালা
c_parser_expression (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  সংরচনা c_রাশিমালা রাশিমালা;
  রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
  যদি (c_parser_next_token_is (parser, CPP_COMMA))
    রাশিমালা = convert_lvalue_to_rvalue (tloc, রাশিমালা, সত্য, অসত্য);
  যাবত্ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      সংরচনা c_রাশিমালা next;
      বৃক্ষ lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t রাশিমালা_loc;
      c_parser_consume_token (parser);
      রাশিমালা_loc = c_parser_peek_token (parser)->location;
      lhsval = রাশিমালা.মান;
      যাবত্ (বৃক্ষ_CODE (lhsval) == COMPOUND_রাশিমালা
	     || বৃক্ষ_CODE (lhsval) == NOP_রাশিমালা)
	{
	  যদি (বৃক্ষ_CODE (lhsval) == COMPOUND_রাশিমালা)
	    lhsval = বৃক্ষ_OPERAND (lhsval, 1);
	  অন্যথা
	    lhsval = বৃক্ষ_OPERAND (lhsval, 0);
	}
      যদি (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      যদি (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  বৃক্ষ val = embed->মান;
	  unsigned last = RAW_DATA_LENGTH (val) - 1;
	  next.মান = build_int_cst (বৃক্ষ_TYPE (val),
				      RAW_DATA_UCHAR_ELT (val, last));
	  next.original_type = integer_type_গ্রন্থি;
	  c_parser_consume_token (parser);
	}
      অন্যথা
	{
	  next = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	  next = convert_lvalue_to_rvalue (রাশিমালা_loc, next, সত্য, অসত্য);
	}
      রাশিমালা.মান = build_compound_রাশিমালা (loc, রাশিমালা.মান, next.মান);
      রাশিমালা.original_code = COMPOUND_রাশিমালা;
      রাশিমালা.original_type = next.original_type;
      রাশিমালা.m_decimal = 0;
    }
  প্রত্যাগম রাশিমালা;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

স্থির সংরচনা c_রাশিমালা
c_parser_expression_conv (c_parser *parser)
{
  সংরচনা c_রাশিমালা রাশিমালা;
  location_t loc = c_parser_peek_token (parser)->location;
  রাশিমালা = c_parser_expression (parser);
  রাশিমালা = convert_lvalue_to_rvalue (loc, রাশিমালা, সত্য, অসত্য);
  প্রত্যাগম রাশিমালা;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

স্থির অন্তঃস্থ শূন্য
c_parser_check_literal_zero (c_parser *parser, unsigned *literal_zero_mask,
			     unsigned পূর্ণাঙ্ক idx)
{
  যদি (idx >= HOST_BITS_PER_INT)
    প্রত্যাগম;

  c_token *tok = c_parser_peek_token (parser);
  বিকল্প (tok->type)
    {
    পক্ষ CPP_সংখ্যা:
    পক্ষ CPP_CHAR:
    পক্ষ CPP_WCHAR:
    পক্ষ CPP_CHAR16:
    পক্ষ CPP_CHAR32:
    পক্ষ CPP_UTF8CHAR:
      /* If a parameter is literal zero alone, remember it
	 for -Wmemset-transposed-args warning.  */
      যদি (integer_zerop (tok->মান)
	  && !বৃক্ষ_OVERFLOW (tok->মান)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_mask |= 1U << idx;
    স্বভাব:
      ভঙ্গ;
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

স্থির vec<বৃক্ষ, va_gc> *
c_parser_রাশিমালা_list (c_parser *parser, তার্কিক convert_p, তার্কিক fold_p,
		    vec<বৃক্ষ, va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, বৃক্ষ *sizeof_arg,
		    vec<location_t> *locations,
		    unsigned পূর্ণাঙ্ক *literal_zero_mask)
{
  vec<বৃক্ষ, va_gc> *ret;
  vec<বৃক্ষ, va_gc> *orig_types;
  সংরচনা c_রাশিমালা রাশিমালা;
  unsigned পূর্ণাঙ্ক idx = 0;
  তার্কিক save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = অসত্য;

  ret = make_বৃক্ষ_vector ();
  যদি (p_orig_types == রিক্ত)
    orig_types = রিক্ত;
  অন্যথা
    orig_types = make_বৃক্ষ_vector ();

  যদি (literal_zero_mask)
    c_parser_check_literal_zero (parser, literal_zero_mask, 0);
  রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
  যদি (convert_p)
    রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা.get_location (), রাশিমালা, সত্য, সত্য);
  যদি (fold_p)
    রাশিমালা.মান = c_fully_fold (রাশিমালা.মান, অসত্য, রিক্ত);
  ret->quick_ঠেলো (রাশিমালা.মান);
  যদি (orig_types)
    orig_types->quick_ঠেলো (রাশিমালা.original_type);
  যদি (locations)
    locations->safe_ঠেলো (রাশিমালা.get_location ());
  যদি (sizeof_arg != রিক্ত
      && (রাশিমালা.original_code == SIZEOF_রাশিমালা
	  || রাশিমালা.original_code == PAREN_SIZEOF_রাশিমালা))
    {
      sizeof_arg[0] = c_last_sizeof_arg;
      sizeof_arg_loc[0] = c_last_sizeof_loc;
    }
  যাবত্ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      যদি (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  বৃক্ষ মান = embed->মান;
	  রাশিমালা.original_code = INTEGER_CST;
	  রাশিমালা.original_type = integer_type_গ্রন্থি;
	  রাশিমালা.মান = NULL_বৃক্ষ;
	  set_c_রাশিমালা_source_range (&রাশিমালা, embed->get_range ());
	  রাশিমালা.m_decimal = 0;
	  প্রতি (unsigned পূর্ণাঙ্ক i = 0; i < (unsigned) RAW_DATA_LENGTH (মান); i++)
	    {
	      যদি (literal_zero_mask
		  && idx + 1 < HOST_BITS_PER_INT
		  && RAW_DATA_POINTER (মান)[i] == 0)
		*literal_zero_mask |= 1U << (idx + 1);
	      রাশিমালা.মান = build_int_cst (integer_type_গ্রন্থি,
					  RAW_DATA_UCHAR_ELT (মান, i));
	      vec_safe_ঠেলো (ret, রাশিমালা.মান);
	      যদি (orig_types)
		vec_safe_ঠেলো (orig_types, রাশিমালা.original_type);
	      যদি (locations)
		locations->safe_ঠেলো (রাশিমালা.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  অনুবর্ত;
	}
      যদি (literal_zero_mask)
	c_parser_check_literal_zero (parser, literal_zero_mask, idx + 1);
      রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      যদি (convert_p)
	রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা.get_location (), রাশিমালা, সত্য,
					 সত্য);
      যদি (fold_p)
	রাশিমালা.মান = c_fully_fold (রাশিমালা.মান, অসত্য, রিক্ত);
      vec_safe_ঠেলো (ret, রাশিমালা.মান);
      যদি (orig_types)
	vec_safe_ঠেলো (orig_types, রাশিমালা.original_type);
      যদি (locations)
	locations->safe_ঠেলো (রাশিমালা.get_location ());
      যদি (++idx < 6
	  && sizeof_arg != রিক্ত
	  && (রাশিমালা.original_code == SIZEOF_রাশিমালা
	      || রাশিমালা.original_code == PAREN_SIZEOF_রাশিমালা))
	{
	  sizeof_arg[idx] = c_last_sizeof_arg;
	  sizeof_arg_loc[idx] = c_last_sizeof_loc;
	}
    }
  যদি (orig_types)
    *p_orig_types = orig_types;
  c_omp_array_section_p = save_c_omp_array_section_p;
  প্রত্যাগম ret;
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

স্থির শূন্য
c_parser_objc_class_definition (c_parser *parser, বৃক্ষ attributes)
{
  তার্কিক iface_p;
  বৃক্ষ id1;
  বৃক্ষ superclass;
  যদি (c_parser_next_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = সত্য;
  অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = অসত্য;
  অন্যথা
    gcc_unreachable ();

  c_parser_consume_token (parser);
  যদি (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      প্রত্যাগম;
    }
  id1 = c_parser_peek_token (parser)->মান;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      বৃক্ষ id2;
      বৃক্ষ proto = NULL_বৃক্ষ;
      matching_parens parens;
      parens.consume_open (parser);
      যদি (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  যদি (iface_p && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_বৃক্ষ;
	    }
	  অন্যথা
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
	      প্রত্যাগম;
	    }
	}
      অন্যথা
	{
	  id2 = c_parser_peek_token (parser)->মান;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_found_close (parser);
      যদি (!iface_p)
	{
	  objc_start_category_implementation (id1, id2);
	  প্রত্যাগম;
	}
      যদি (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_category_interface (id1, id2, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
      প্রত্যাগম;
    }
  যদি (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      যদি (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  প্রত্যাগম;
	}
      superclass = c_parser_peek_token (parser)->মান;
      c_parser_consume_token (parser);
    }
  অন্যথা
    superclass = NULL_বৃক্ষ;
  যদি (iface_p)
    {
      বৃক্ষ proto = NULL_বৃক্ষ;
      যদি (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_class_interface (id1, loc1, superclass, proto, attributes);
    }
  অন্যথা
    objc_start_class_implementation (id1, superclass);
  যদি (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  যদি (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
    }
  অন্যথা
    {
      objc_continue_implementation ();
      প্রত্যাগম;
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

স্থির শূন্য
c_parser_objc_class_instance_variables (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  যাবত্ (c_parser_next_token_is_not (parser, CPP_EOF))
    {
      বৃক্ষ decls;
      /* Parse any stray semicolon.  */
      যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  অনুবর্ত;
	}
      /* Stop if at the end of the instance variables.  */
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  ভঙ্গ;
	}
      /* Parse any objc-visibility-spec.  */
      যদি (c_parser_next_token_is_keyword (parser, RID_AT_PRIVATE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PRIVATE);
	  অনুবর্ত;
	}
      অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PROTECTED);
	  অনুবর্ত;
	}
      অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_AT_PUBLIC))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PUBLIC);
	  অনুবর্ত;
	}
      অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PACKAGE);
	  অনুবর্ত;
	}
      অন্যথা যদি (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, রিক্ত, NULL_বৃক্ষ);
	  অনুবর্ত;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser, রিক্ত);
      যদি (decls == রিক্ত)
	{
	  /* There is a syntax error.  We want to skip the offending
	     tokens up to the next ';' (included) or '}'
	     (excluded).  */

	  /* First, skip manually a ')' or ']'.  This is because they
	     reduce the nesting level, so c_parser_skip_until_found()
	     wouldn't be able to skip past them.  */
	  c_token *token = c_parser_peek_token (parser);
	  যদি (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_SQUARE)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, রিক্ত);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = অসত্য;
	  অনুবর্ত;
	}
      অন্যথা
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  বৃক্ষ ivar = nreverse (decls);
	  প্রতি (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_add_instance_variable (copy_গ্রন্থি (ivar));
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}

/* Parse an objc-class-declaration.

   objc-class-declaration:
     @class identifier-list ;
*/

স্থির শূন্য
c_parser_objc_class_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_CLASS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  যাবত্ (সত্য)
    {
      বৃক্ষ id;
      যদি (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, রিক্ত);
	  parser->error = অসত্য;
	  প্রত্যাগম;
	}
      id = c_parser_peek_token (parser)->মান;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      যদি (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      অন্যথা
	ভঙ্গ;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse an objc-alias-declaration.

   objc-alias-declaration:
     @compatibility_alias identifier identifier ;
*/

স্থির শূন্য
c_parser_objc_alias_declaration (c_parser *parser)
{
  বৃক্ষ id1, id2;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  যদি (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, রিক্ত);
      প্রত্যাগম;
    }
  id1 = c_parser_peek_token (parser)->মান;
  c_parser_consume_token (parser);
  যদি (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, রিক্ত);
      প্রত্যাগম;
    }
  id2 = c_parser_peek_token (parser)->মান;
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

স্থির শূন্য
c_parser_objc_protocol_definition (c_parser *parser, বৃক্ষ attributes)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  যদি (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      প্রত্যাগম;
    }
  যদি (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      যাবত্ (সত্য)
	{
	  বৃক্ষ id;
	  যদি (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      ভঙ্গ;
	    }
	  id = c_parser_peek_token (parser)->মান;
	  objc_declare_protocol (id, attributes);
	  c_parser_consume_token (parser);
	  যদি (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  অন্যথা
	    ভঙ্গ;
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  অন্যথা
    {
      বৃক্ষ id = c_parser_peek_token (parser)->মান;
      বৃক্ষ proto = NULL_বৃক্ষ;
      c_parser_consume_token (parser);
      যদি (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = সত্য;
      objc_start_protocol (id, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      parser->objc_pq_context = অসত্য;
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
স্থির অন্তঃস্থ তার্কিক
c_parser_objc_method_type (c_parser *parser)
{
  বিকল্প (c_parser_peek_token (parser)->type)
    {
    পক্ষ CPP_PLUS:
      c_parser_consume_token (parser);
      প্রত্যাগম সত্য;
    পক্ষ CPP_MINUS:
      c_parser_consume_token (parser);
      প্রত্যাগম অসত্য;
    স্বভাব:
      gcc_unreachable ();
    }
}

/* Parse an objc-method-definition.

   objc-method-definition:
     objc-method-type objc-method-decl ;[opt] compound-statement
*/

স্থির শূন্য
c_parser_objc_method_definition (c_parser *parser)
{
  তার্কিক is_class_method = c_parser_objc_method_type (parser);
  বৃক্ষ decl, attributes = NULL_বৃক্ষ, রাশিমালা = NULL_বৃক্ষ;
  parser->objc_pq_context = সত্য;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    &রাশিমালা);
  যদি (decl == error_mark_গ্রন্থি)
    প্রত্যাগম;  /* Bail here. */

  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  যদি (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      প্রত্যাগম;
    }

  parser->objc_pq_context = অসত্য;
  যদি (objc_start_method_definition (is_class_method, decl, attributes, রাশিমালা))
    {
      add_stmt (c_parser_compound_statement (parser));
      objc_finish_method_definition (current_function_decl);
    }
  অন্যথা
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

স্থির শূন্য
c_parser_objc_methodprotolist (c_parser *parser)
{
  যাবত্ (সত্য)
    {
      /* The list is terminated by @end.  */
      বিকল্প (c_parser_peek_token (parser)->type)
	{
	পক্ষ CPP_SEMICOLON:
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  ভঙ্গ;
	পক্ষ CPP_PLUS:
	পক্ষ CPP_MINUS:
	  c_parser_objc_methodproto (parser);
	  ভঙ্গ;
	পক্ষ CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external, রিক্ত, NULL_বৃক্ষ);
	  ভঙ্গ;
	পক্ষ CPP_EOF:
	  প্রত্যাগম;
	স্বভাব:
	  যদি (c_parser_next_token_is_keyword (parser, RID_AT_END))
	    প্রত্যাগম;
	  অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_set_method_opt (সত্য);
	      c_parser_consume_token (parser);
	    }
	  অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_set_method_opt (অসত্য);
	      c_parser_consume_token (parser);
	    }
	  অন্যথা
	    c_parser_declaration_or_fndef (parser, অসত্য, অসত্য, সত্য,
					   অসত্য, সত্য, অসত্য);
	  ভঙ্গ;
	}
    }
}

/* Parse an objc-methodproto.

   objc-methodproto:
     objc-method-type objc-method-decl ;
*/

স্থির শূন্য
c_parser_objc_methodproto (c_parser *parser)
{
  তার্কিক is_class_method = c_parser_objc_method_type (parser);
  বৃক্ষ decl, attributes = NULL_বৃক্ষ;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = সত্য;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    রিক্ত);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = অসত্য;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  যদি (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      প্রত্যাগম;
    }

  যদি (decl != error_mark_গ্রন্থি)
    objc_add_method_declaration (is_class_method, decl, attributes);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

স্থির তার্কিক
c_parser_objc_maybe_method_attributes (c_parser* parser, বৃক্ষ* attributes)
{
  তার্কিক bad = অসত্য;
  যদি (*attributes)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *attributes = NULL_বৃক্ষ;
      bad = সত্য;
    }

  যদি (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    *attributes = c_parser_gnu_attributes (parser);

  /* If there were no attributes here, just report any earlier error.  */
  যদি (*attributes == NULL_বৃক্ষ || bad)
    প্রত্যাগম bad;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    প্রত্যাগম bad;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  প্রত্যাগম সত্য;
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

স্থির বৃক্ষ
c_parser_objc_method_decl (c_parser *parser, তার্কিক is_class_method,
			   বৃক্ষ *attributes, বৃক্ষ *রাশিমালা)
{
  বৃক্ষ type = NULL_বৃক্ষ;
  বৃক্ষ sel;
  বৃক্ষ parms = NULL_বৃক্ষ;
  তার্কিক ellipsis = অসত্য;
  তার্কিক attr_err = অসত্য;

  *attributes = NULL_বৃক্ষ;
  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
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
  যদি (!sel || c_parser_next_token_is (parser, CPP_COLON))
    {
      বৃক্ষ tsel = sel;
      বৃক্ষ list = NULL_বৃক্ষ;
      যাবত্ (সত্য)
	{
	  বৃক্ষ atype = NULL_বৃক্ষ, id, keyworddecl;
	  বৃক্ষ param_attr = NULL_বৃক্ষ;
	  যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    ভঙ্গ;
	  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  যদি (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_attributes (parser);
	  যদি (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      প্রত্যাগম error_mark_গ্রন্থি;
	    }
	  id = c_parser_peek_token (parser)->মান;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  যদি (!tsel && c_parser_next_token_is_not (parser, CPP_COLON))
	    ভঙ্গ;
	}

      attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_গ্রন্থি (বৃক্ষ_LIST);
      যাবত্ (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  সংরচনা c_parm *parm;
	  c_parser_consume_token (parser);
	  যদি (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = সত্য;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_method_attributes
						(parser, attributes) ;
	      ভঙ্গ;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_বৃক্ষ, অসত্য);
	  যদি (parm == রিক্ত)
	    ভঙ্গ;
	  parms = chainon (parms,
			   build_বৃক্ষ_list (NULL_বৃক্ষ, grokparm (parm, রাশিমালা)));
	}
      sel = list;
    }
  অন্যথা
    attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

  যদি (sel == রিক্ত)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      প্রত্যাগম error_mark_গ্রন্থি;
    }

  যদি (attr_err)
    প্রত্যাগম error_mark_গ্রন্থি;

  প্রত্যাগম objc_build_method_signature (is_class_method, type, sel, parms, ellipsis);
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

স্থির বৃক্ষ
c_parser_objc_type_name (c_parser *parser)
{
  বৃক্ষ quals = NULL_বৃক্ষ;
  সংরচনা c_type_name *type_name = রিক্ত;
  বৃক্ষ type = NULL_বৃক্ষ;
  যাবত্ (সত্য)
    {
      c_token *token = c_parser_peek_token (parser);
      যদি (token->type == CPP_KEYWORD
	  && (token->keyword == RID_IN
	      || token->keyword == RID_OUT
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_বৃক্ষ_list (NULL_বৃক্ষ, token->মান), quals);
	  c_parser_consume_token (parser);
	}
      অন্যথা
	ভঙ্গ;
    }
  যদি (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  যদি (type_name)
    type = groktypename (type_name, রিক্ত, রিক্ত);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  যদি (type == error_mark_গ্রন্থি)
    type = NULL_বৃক্ষ;

  প্রত্যাগম build_বৃক্ষ_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

স্থির বৃক্ষ
c_parser_objc_protocol_refs (c_parser *parser)
{
  বৃক্ষ list = NULL_বৃক্ষ;
  gcc_assert (c_parser_next_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  যাবত্ (সত্য)
    {
      বৃক্ষ id;
      যদি (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  ভঙ্গ;
	}
      id = c_parser_peek_token (parser)->মান;
      list = chainon (list, build_বৃক্ষ_list (NULL_বৃক্ষ, id));
      c_parser_consume_token (parser);
      যদি (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      অন্যথা
	ভঙ্গ;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  প্রত্যাগম list;
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

স্থির শূন্য
c_parser_objc_try_catch_finally_statement (c_parser *parser)
{
  location_t location;
  বৃক্ষ stmt;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  যাবত্ (c_parser_next_token_is_keyword (parser, RID_AT_CATCH))
    {
      সংরচনা c_parm *parm;
      বৃক্ষ parameter_declaration = error_mark_গ্রন্থি;
      তার্কিক seen_open_paren = অসত্য;

      c_parser_consume_token (parser);
      matching_parens parens;
      যদি (!parens.require_open (parser))
	seen_open_paren = সত্য;
      যদি (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_বৃক্ষ;
	}
      অন্যথা
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_বৃক্ষ, অসত্য);
	  যদি (parm == রিক্ত)
	    parameter_declaration = error_mark_গ্রন্থি;
	  অন্যথা
	    parameter_declaration = grokparm (parm, রিক্ত);
	}
      যদি (seen_open_paren)
	parens.require_close (parser);
      অন্যথা
	{
	  /* If there was no open parenthesis, we are recovering from
	     an error, and we are trying to figure out what mistake
	     the user has made.  */

	  /* If there is an immediate closing parenthesis, the user
	     probably forgot the opening one (ie, they typed "@catch
	     NSException *e)".  Parse the closing parenthesis and keep
	     going.  */
	  যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      যদি (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_finish_catch_clause ();
    }
  যদি (c_parser_next_token_is_keyword (parser, RID_AT_FINALLY))
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

স্থির শূন্য
c_parser_objc_synchronized_statement (c_parser *parser)
{
  location_t loc;
  বৃক্ষ রাশিমালা, stmt;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      সংরচনা c_রাশিমালা ce = c_parser_expression (parser);
      ce = convert_lvalue_to_rvalue (loc, ce, অসত্য, অসত্য);
      রাশিমালা = ce.মান;
      রাশিমালা = c_fully_fold (রাশিমালা, অসত্য, রিক্ত);
      parens.skip_until_found_close (parser);
    }
  অন্যথা
    রাশিমালা = error_mark_গ্রন্থি;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, রাশিমালা, stmt);
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

স্থির বৃক্ষ
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  বৃক্ষ মান = token->মান;
  যদি (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      প্রত্যাগম মান;
    }
  যদি (token->type != CPP_KEYWORD)
    প্রত্যাগম NULL_বৃক্ষ;
  বিকল্প (token->keyword)
    {
    পক্ষ RID_ENUM:
    পক্ষ RID_STRUCT:
    পক্ষ RID_UNION:
    পক্ষ RID_IF:
    পক্ষ RID_ELSE:
    পক্ষ RID_WHILE:
    পক্ষ RID_DO:
    পক্ষ RID_FOR:
    পক্ষ RID_SWITCH:
    পক্ষ RID_CASE:
    পক্ষ RID_DEFAULT:
    পক্ষ RID_BREAK:
    পক্ষ RID_CONTINUE:
    পক্ষ RID_RETURN:
    পক্ষ RID_GOTO:
    পক্ষ RID_ASM:
    পক্ষ RID_SIZEOF:
    পক্ষ RID_TYPEOF:
    পক্ষ RID_TYPEOF_UNQUAL:
    পক্ষ RID_ALIGNOF:
    পক্ষ RID_UNSIGNED:
    পক্ষ RID_LONG:
    পক্ষ RID_CONST:
    পক্ষ RID_SHORT:
    পক্ষ RID_VOLATILE:
    পক্ষ RID_SIGNED:
    পক্ষ RID_RESTRICT:
    পক্ষ RID_COMPLEX:
    পক্ষ RID_IN:
    পক্ষ RID_OUT:
    পক্ষ RID_INOUT:
    পক্ষ RID_BYCOPY:
    পক্ষ RID_BYREF:
    পক্ষ RID_ONEWAY:
    পক্ষ RID_INT:
    পক্ষ RID_CHAR:
    পক্ষ RID_FLOAT:
    পক্ষ RID_DOUBLE:
    CASE_RID_FLOATN_NX:
    পক্ষ RID_VOID:
    পক্ষ RID_BOOL:
    পক্ষ RID_ATOMIC:
    পক্ষ RID_AUTO_TYPE:
    পক্ষ RID_INT_N_0:
    পক্ষ RID_INT_N_1:
    পক্ষ RID_INT_N_2:
    পক্ষ RID_INT_N_3:
      c_parser_consume_token (parser);
      প্রত্যাগম মান;
    স্বভাব:
      প্রত্যাগম NULL_বৃক্ষ;
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

স্থির বৃক্ষ
c_parser_objc_selector_arg (c_parser *parser)
{
  বৃক্ষ sel = c_parser_objc_selector (parser);
  বৃক্ষ list = NULL_বৃক্ষ;
  যদি (sel
      && c_parser_next_token_is_not (parser, CPP_COLON)
      && c_parser_next_token_is_not (parser, CPP_SCOPE))
    প্রত্যাগম sel;
  যাবত্ (সত্য)
    {
      যদি (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_বৃক্ষ_list (sel, NULL_বৃক্ষ));
	  list = chainon (list, build_বৃক্ষ_list (NULL_বৃক্ষ, NULL_বৃক্ষ));
	}
      অন্যথা
	{
	  যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    প্রত্যাগম list;
	  list = chainon (list, build_বৃক্ষ_list (sel, NULL_বৃক্ষ));
	}
      sel = c_parser_objc_selector (parser);
      যদি (!sel
	  && c_parser_next_token_is_not (parser, CPP_COLON)
	  && c_parser_next_token_is_not (parser, CPP_SCOPE))
	ভঙ্গ;
    }
  প্রত্যাগম list;
}

/* Parse an objc-receiver.

   objc-receiver:
     expression
     class-name
     type-name
*/

স্থির বৃক্ষ
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  যদি (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
    {
      বৃক্ষ id = c_parser_peek_token (parser)->মান;
      c_parser_consume_token (parser);
      প্রত্যাগম objc_get_class_reference (id);
    }
  সংরচনা c_রাশিমালা ce = c_parser_expression (parser);
  ce = convert_lvalue_to_rvalue (loc, ce, অসত্য, অসত্য);
  প্রত্যাগম c_fully_fold (ce.মান, অসত্য, রিক্ত);
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

স্থির বৃক্ষ
c_parser_objc_message_args (c_parser *parser)
{
  বৃক্ষ sel = c_parser_objc_selector (parser);
  বৃক্ষ list = NULL_বৃক্ষ;
  যদি (sel && c_parser_next_token_is_not (parser, CPP_COLON))
    প্রত্যাগম sel;
  যাবত্ (সত্য)
    {
      বৃক্ষ keywordexpr;
      যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	প্রত্যাগম error_mark_গ্রন্থি;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_বৃক্ষ_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      যদি (!sel && c_parser_next_token_is_not (parser, CPP_COLON))
	ভঙ্গ;
    }
  প্রত্যাগম list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

স্থির বৃক্ষ
c_parser_objc_keywordexpr (c_parser *parser)
{
  বৃক্ষ ret;
  vec<বৃক্ষ, va_gc> *রাশিমালা_list = c_parser_রাশিমালা_list (parser, সত্য, সত্য,
						রিক্ত, রিক্ত, রিক্ত, রিক্ত);
  যদি (vec_safe_length (রাশিমালা_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*রাশিমালা_list)[0];
    }
  অন্যথা
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_বৃক্ষ_list_vec (রাশিমালা_list);
    }
  release_বৃক্ষ_vector (রাশিমালা_list);
  প্রত্যাগম ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
স্থির তার্কিক
c_parser_objc_diagnose_bad_element_prefix (c_parser *parser,
					   সংরচনা c_declspecs *specs)
{
  যদি (!specs->declspecs_seen_p || specs->non_sc_seen_p
      || specs->typespec_kind != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_to_end_of_block_or_statement (parser);
      প্রত্যাগম সত্য;
    }
  প্রত্যাগম অসত্য;
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
স্থির শূন্য
c_parser_objc_at_property_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY));
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);  /* Eat '@property'.  */

  /* Parse the optional attribute list.

     A list of parsed, but not verified, attributes.  */
  vec<property_attribute_info *> prop_attr_list = vNULL;

  তার্কিক syntax_error = অসত্য;
  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_start = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = সত্য;

      /* Allow @property (), with a warning.  */
      location_t attr_end = c_parser_peek_token (parser)->location;

      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_end, attr_start, attr_end);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      অন্যথা
	যাবত্ (সত্য)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_start = token->location;
	    attr_end = get_finish (token->location);
	    location_t attr_comb = make_location (attr_start, attr_start,
						  attr_end);

	    যদি (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		যদি (token->type == CPP_CLOSE_PAREN)
		  ভঙ্গ;
		c_parser_consume_token (parser);
		অনুবর্ত;
	      }

	    বৃক্ষ attr_name = NULL_বৃক্ষ;
	    গণনা rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    তার্কিক add_at = অসত্য;
	    যদি (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		যদি (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->মান;
		    add_at = সত্য;
		  }
		অন্যথা
		  attr_name = ridpointers[(পূর্ণাঙ্ক)keyword];
	      }
	    অন্যথা যদি (token->type == CPP_NAME)
	      attr_name = token->মান;
	    c_parser_consume_token (parser);

	    গণনা objc_property_attribute_kind prop_kind
	      = objc_prop_attr_kind_for_rid (keyword);
	    property_attribute_info *prop
	      = নূতন property_attribute_info (attr_name, attr_comb, prop_kind);
	    prop_attr_list.safe_ঠেলো (prop);

	    বৃক্ষ meth_name;
	    বিকল্প (prop->prop_kind)
	      {
	      স্বভাব: ভঙ্গ;
	      পক্ষ OBJC_PROPERTY_ATTR_UNKNOWN:
		যদি (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    add_at ? "@" : "", IDENTIFIER_POINTER (attr_name));
		অন্যথা
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = সত্য;
		ভঙ্গ;

	      পক্ষ OBJC_PROPERTY_ATTR_GETTER:
	      পক্ষ OBJC_PROPERTY_ATTR_SETTER:
		যদি (c_parser_next_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = সত্য;
		    ভঙ্গ;
		  }
		token = c_parser_peek_token (parser);
		attr_end = token->location;
		c_parser_consume_token (parser); /* eat the = */
		যদি (c_parser_next_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = সত্য;
		    ভঙ্গ;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_end = get_finish (token->location);
		meth_name = token->মান;
		c_parser_consume_token (parser);
		যদি (prop->prop_kind == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    যদি (c_parser_next_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_end, attr_start,
						   attr_end);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = সত্য;
		      }
		    অন্যথা
		      {
			attr_end = get_finish (c_parser_peek_token
					       (parser)->location);
			c_parser_consume_token (parser);
		      }
		    attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		  }
		অন্যথা
		  attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		prop->ident = meth_name;
		/* Updated location including all that was successfully
		   parsed.  */
		prop->prop_loc = attr_comb;
		ভঙ্গ;
	    }

	  /* If we see a comma here, then keep going - even if we already
	     saw a syntax error.  For simple mistakes e.g. (assign, getter=x)
	     this makes a more useful output and avoid spurious warnings about
	     missing attributes that are, in fact, specified after the one with
	     the syntax error.  */
	  যদি (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  অন্যথা
	    ভঙ্গ;
	}
      parser->objc_property_attr_context = অসত্য;

      যদি (syntax_error && c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      অন্যথা
	syntax_error = অসত্য, parens.skip_until_found_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  বৃক্ষ properties = c_parser_struct_declaration (parser, রিক্ত);

  যদি (properties == error_mark_গ্রন্থি)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, রিক্ত);
  অন্যথা
    {
      যদি (properties == NULL_বৃক্ষ)
	c_parser_error (parser, "expected identifier");
      অন্যথা
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  প্রতি (; properties; properties = বৃক্ষ_CHAIN (properties))
	    objc_add_property_declaration (loc, copy_গ্রন্থি (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  যাবত্ (!prop_attr_list.is_empty())
    delete prop_attr_list.বের_করো ();
  prop_attr_list.release ();
  parser->error = অসত্য;
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
স্থির শূন্য
c_parser_objc_at_synthesize_declaration (c_parser *parser)
{
  বৃক্ষ list = NULL_বৃক্ষ;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  যাবত্ (সত্য)
    {
      বৃক্ষ property, ivar;
      যদি (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, রিক্ত);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = অসত্য;
	  প্রত্যাগম;
	}
      property = c_parser_peek_token (parser)->মান;
      c_parser_consume_token (parser);
      যদি (c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  যদি (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_SEMICOLON, রিক্ত);
	      parser->error = অসত্য;
	      প্রত্যাগম;
	    }
	  ivar = c_parser_peek_token (parser)->মান;
	  c_parser_consume_token (parser);
	}
      অন্যথা
	ivar = NULL_বৃক্ষ;
      list = chainon (list, build_বৃক্ষ_list (ivar, property));
      যদি (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      অন্যথা
	ভঙ্গ;
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
স্থির শূন্য
c_parser_objc_at_dynamic_declaration (c_parser *parser)
{
  বৃক্ষ list = NULL_বৃক্ষ;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  যাবত্ (সত্য)
    {
      বৃক্ষ property;
      যদি (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, রিক্ত);
	  parser->error = অসত্য;
	  প্রত্যাগম;
	}
      property = c_parser_peek_token (parser)->মান;
      list = chainon (list, build_বৃক্ষ_list (NULL_বৃক্ষ, property));
      c_parser_consume_token (parser);
      যদি (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      অন্যথা
	ভঙ্গ;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_add_dynamic_declaration (loc, list);
}


/* Parse a pragma GCC ivdep.  */

স্থির তার্কিক
c_parse_pragma_ivdep (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  প্রত্যাগম সত্য;
}

/* Parse a pragma GCC novector.  */

স্থির তার্কিক
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  প্রত্যাগম সত্য;
}

/* Parse a pragma GCC unroll.  */

স্থির unsigned short
c_parser_pragma_unroll (c_parser *parser)
{
  unsigned short unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  বৃক্ষ রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত).মান;
  mark_exp_read (রাশিমালা);
  রাশিমালা = c_fully_fold (রাশিমালা, অসত্য, রিক্ত);
  HOST_WIDE_INT lunroll = 0;
  যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (রাশিমালা))
      || বৃক্ষ_CODE (রাশিমালা) != INTEGER_CST
      || (lunroll = বৃক্ষ_to_shwi (রাশিমালা)) < 0
      || lunroll >= USHRT_MAX)
    {
      error_at (location, "%<#pragma GCC unroll%> requires an"
		" assignment-expression that evaluates to a non-negative"
		" integral constant less than %u", USHRT_MAX);
      unroll = 0;
    }
  অন্যথা
    {
      unroll = (unsigned short)lunroll;
      যদি (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_to_pragma_eol (parser);
  প্রত্যাগম unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

স্থির তার্কিক
c_parser_pragma (c_parser *parser, গণনা pragma_context context, তার্কিক *if_p,
		 বৃক্ষ before_labels)
{
  unsigned পূর্ণাঙ্ক id;
  ধ্রুব বর্ণ *construct = রিক্ত;

  প্রবেশ_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_kind;
  gcc_assert (id != PRAGMA_NONE);
  যদি (parser->omp_for_parse_state
      && parser->omp_for_parse_state->in_intervening_code
      && id >= PRAGMA_OMP__START_ && id <= PRAGMA_OMP__LAST_
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	প্রবেশ_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->fail = সত্য;
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, রিক্ত);
      প্রত্যাগম অসত্য;
    }

  বিকল্প (id)
    {
    পক্ষ PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OACC_ENTER_DATA:
      যদি (context != pragma_compound)
	{
	  construct = "acc enter data";
	in_compound:
	  যদি (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, রিক্ত);
	      প্রত্যাগম সত্য;
	    }
	  গচ্ছ bad_stmt;
	}
      c_parser_oacc_enter_exit_data (parser, সত্য);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OACC_EXIT_DATA:
      যদি (context != pragma_compound)
	{
	  construct = "acc exit data";
	  গচ্ছ in_compound;
	}
      c_parser_oacc_enter_exit_data (parser, অসত্য);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OACC_ROUTINE:
      যদি (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, রিক্ত);
	  প্রত্যাগম অসত্য;
	}
      c_parser_oacc_routine (parser, context);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OACC_UPDATE:
      যদি (context != pragma_compound)
	{
	  construct = "acc update";
	  গচ্ছ in_compound;
	}
      c_parser_oacc_update (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_BARRIER:
      যদি (context != pragma_compound)
	{
	  construct = "omp barrier";
	  গচ্ছ in_compound;
	}
      c_parser_omp_barrier (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_DEPOBJ:
      যদি (context != pragma_compound)
	{
	  construct = "omp depobj";
	  গচ্ছ in_compound;
	}
      c_parser_omp_depobj (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_FLUSH:
      যদি (context != pragma_compound)
	{
	  construct = "omp flush";
	  গচ্ছ in_compound;
	}
      c_parser_omp_flush (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_INTEROP:
      যদি (context != pragma_compound)
	{
	  construct = "omp interop";
	  গচ্ছ in_compound;
	}
      c_parser_omp_interop (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_TASKWAIT:
      যদি (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  গচ্ছ in_compound;
	}
      c_parser_omp_taskwait (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_TASKYIELD:
      যদি (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  গচ্ছ in_compound;
	}
      c_parser_omp_taskyield (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_CANCEL:
      যদি (context != pragma_compound)
	{
	  construct = "omp cancel";
	  গচ্ছ in_compound;
	}
      c_parser_omp_cancel (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_CANCELLATION_POINT:
      প্রত্যাগম c_parser_omp_cancellation_point (parser, context);

    পক্ষ PRAGMA_OMP_GROUPPRIVATE:
      c_parser_omp_groupprivate (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_THREADPRIVATE:
      c_parser_omp_threadprivate (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_TARGET:
      প্রত্যাগম c_parser_omp_target (parser, context, if_p);

    পক্ষ PRAGMA_OMP_BEGIN:
      c_parser_omp_begin (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_END:
      c_parser_omp_end (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_SCAN:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, রিক্ত);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, রিক্ত);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_DECLARE:
      প্রত্যাগম c_parser_omp_declare (parser, context);

    পক্ষ PRAGMA_OMP_REQUIRES:
      যদি (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, রিক্ত);
	  প্রত্যাগম অসত্য;
	}
      c_parser_omp_requires (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_ALLOCATE:
      c_parser_omp_allocate (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_ASSUMES:
      যদি (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp assumes");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, রিক্ত);
	  প্রত্যাগম অসত্য;
	}
      c_parser_omp_assumes (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      প্রত্যাগম সত্য;

    পক্ষ PRAGMA_OMP_ERROR:
      প্রত্যাগম c_parser_omp_error (parser, context);

    পক্ষ PRAGMA_OMP_ORDERED:
      প্রত্যাগম c_parser_omp_ordered (parser, context, if_p);

    পক্ষ PRAGMA_NOVECTOR:
    পক্ষ PRAGMA_UNROLL:
    পক্ষ PRAGMA_IVDEP:
      {
	তার্কিক novector = অসত্য;
	unsigned short unroll = 0;
	তার্কিক ivdep = অসত্য;

	বিকল্প (id)
	  {
	  পক্ষ PRAGMA_NOVECTOR:
	    novector = c_parse_pragma_novector (parser);
	    ভঙ্গ;
	  পক্ষ PRAGMA_UNROLL:
	    unroll = c_parser_pragma_unroll (parser);
	    ভঙ্গ;
	  পক্ষ PRAGMA_IVDEP:
	    ivdep = c_parse_pragma_ivdep (parser);
	    ভঙ্গ;
	  স্বভাব:
	    gcc_unreachable ();
	  }

	c_token *tok = c_parser_peek_token (parser);
	তার্কিক has_more = tok->type == CPP_PRAGMA;
	যাবত্ (has_more)
	  {
	    বিকল্প (tok->pragma_kind)
	      {
	      পক্ষ PRAGMA_IVDEP:
		ivdep = c_parse_pragma_ivdep (parser);
		ভঙ্গ;
	      পক্ষ PRAGMA_UNROLL:
		unroll = c_parser_pragma_unroll (parser);
		ভঙ্গ;
	      পক্ষ PRAGMA_NOVECTOR:
		novector = c_parse_pragma_novector (parser);
		ভঙ্গ;
	      স্বভাব:
		has_more = অসত্য;
		ভঙ্গ;
	      }
	    tok = c_parser_peek_token (parser);
	    has_more = has_more && tok->type == CPP_PRAGMA;
	  }
	যদি (!c_parser_next_token_is_keyword (parser, RID_FOR)
	    && !c_parser_next_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_next_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    প্রত্যাগম অসত্য;
	  }
	যদি (c_parser_next_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	অন্যথা
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      প্রত্যাগম সত্য;

    পক্ষ PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, রিক্ত);
      প্রত্যাগম অসত্য;

    পক্ষ PRAGMA_OACC_WAIT:
      যদি (context != pragma_compound)
	{
	  construct = "acc wait";
	  গচ্ছ in_compound;
	}
	/* FALL THROUGH.  */

    স্বভাব:
      যদি (id < PRAGMA_FIRST_EXTERNAL)
	{
	  যদি (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, রিক্ত);
	      প্রত্যাগম অসত্য;
	    }
	  c_parser_omp_construct (parser, if_p);
	  প্রত্যাগম সত্য;
	}
      ভঙ্গ;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = সত্য;
  c_parser_skip_to_pragma_eol (parser);

  প্রত্যাগম অসত্য;
}

/* The interface the pragma parsers have to the lexer.  */

গণনা cpp_ttype
pragma_lex (বৃক্ষ *মান, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  গণনা cpp_ttype ret = tok->type;

  *মান = tok->মান;
  যদি (loc)
    *loc = tok->location;

  যদি (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  অন্যথা যদি (ret == CPP_STRING)
    *মান = c_parser_string_literal (the_parser, অসত্য, অসত্য).মান;
  অন্যথা
    {
      যদি (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  প্রত্যাগম ret;
}

শূন্য
pragma_lex_discard_to_eol ()
{
  cpp_ttype type;
  কুরু
    {
      type = c_parser_peek_token (the_parser)->type;
      gcc_assert (type != CPP_EOF);
      c_parser_consume_token (the_parser);
    } যাবত্ (type != CPP_PRAGMA_EOL);
}

স্থির শূন্য
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  বৃক্ষ name = রিক্ত;

  parser->lex_joined_string = সত্য;
  c_parser_consume_pragma (parser);
  যদি (c_parser_next_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->মান;
      c_parser_consume_token (parser);
    }
  অন্যথা
    c_parser_error (parser, "expected string literal");
  c_parser_skip_to_pragma_eol (parser);
  parser->lex_joined_string = অসত্য;

  যদি (name)
    c_common_pch_pragma (parse_in, বৃক্ষ_STRING_POINTER (name));
}

/* OpenACC and OpenMP parsing routines.  */

/* Returns name of the next clause.
   If the clause is not recognized PRAGMA_OMP_CLAUSE_NONE is returned and
   the token is not consumed.  Otherwise appropriate pragma_omp_clause is
   returned and the token is consumed.  */

স্থির pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause result = PRAGMA_OMP_CLAUSE_NONE;

  যদি (c_parser_next_token_is_keyword (parser, RID_AUTO))
    result = PRAGMA_OACC_CLAUSE_AUTO;
  অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_IF))
    result = PRAGMA_OMP_CLAUSE_IF;
  অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    result = PRAGMA_OMP_CLAUSE_DEFAULT;
  অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_FOR))
    result = PRAGMA_OMP_CLAUSE_FOR;
  অন্যথা যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);

      বিকল্প (p[0])
	{
	পক্ষ 'a':
	  যদি (!strcmp ("affinity", p))
	    result = PRAGMA_OMP_CLAUSE_AFFINITY;
	  অন্যথা যদি (!strcmp ("aligned", p))
	    result = PRAGMA_OMP_CLAUSE_ALIGNED;
	  অন্যথা যদি (!strcmp ("allocate", p))
	    result = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  অন্যথা যদি (!strcmp ("async", p))
	    result = PRAGMA_OACC_CLAUSE_ASYNC;
	  অন্যথা যদি (!strcmp ("attach", p))
	    result = PRAGMA_OACC_CLAUSE_ATTACH;
	  ভঙ্গ;
	পক্ষ 'b':
	  যদি (!strcmp ("bind", p))
	    result = PRAGMA_OMP_CLAUSE_BIND;
	  ভঙ্গ;
	পক্ষ 'c':
	  যদি (!strcmp ("collapse", p))
	    result = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  অন্যথা যদি (!strcmp ("copy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  অন্যথা যদি (!strcmp ("copyin", p))
	    result = PRAGMA_OMP_CLAUSE_COPYIN;
	  অন্যথা যদি (!strcmp ("copyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
          অন্যথা যদি (!strcmp ("copyprivate", p))
	    result = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  অন্যথা যদি (!strcmp ("create", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  ভঙ্গ;
	পক্ষ 'd':
	  যদি (!strcmp ("defaultmap", p))
	    result = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  অন্যথা যদি (!strcmp ("delete", p))
	    result = PRAGMA_OACC_CLAUSE_DELETE;
	  অন্যথা যদি (!strcmp ("depend", p))
	    result = PRAGMA_OMP_CLAUSE_DEPEND;
	  অন্যথা যদি (!strcmp ("destroy", p))
	    result = PRAGMA_OMP_CLAUSE_DESTROY;
	  অন্যথা যদি (!strcmp ("detach", p))
	    result = PRAGMA_OACC_CLAUSE_DETACH;
	  অন্যথা যদি (!strcmp ("device", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE;
	  অন্যথা যদি (!strcmp ("deviceptr", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  অন্যথা যদি (!strcmp ("device_resident", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  অন্যথা যদি (!strcmp ("device_type", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  অন্যথা যদি (!strcmp ("dist_schedule", p))
	    result = PRAGMA_OMP_CLAUSE_DIST_SCHEDULE;
	  অন্যথা যদি (!strcmp ("doacross", p))
	    result = PRAGMA_OMP_CLAUSE_DOACROSS;
	  অন্যথা যদি (!strcmp ("dyn_groupprivate", p))
	    result = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  ভঙ্গ;
	পক্ষ 'e':
	  যদি (!strcmp ("enter", p))
	    result = PRAGMA_OMP_CLAUSE_ENTER;
	  ভঙ্গ;
	পক্ষ 'f':
	  যদি (!strcmp ("filter", p))
	    result = PRAGMA_OMP_CLAUSE_FILTER;
	  অন্যথা যদি (!strcmp ("final", p))
	    result = PRAGMA_OMP_CLAUSE_FINAL;
	  অন্যথা যদি (!strcmp ("finalize", p))
	    result = PRAGMA_OACC_CLAUSE_FINALIZE;
	  অন্যথা যদি (!strcmp ("firstprivate", p))
	    result = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  অন্যথা যদি (!strcmp ("from", p))
	    result = PRAGMA_OMP_CLAUSE_FROM;
	  অন্যথা যদি (!strcmp ("full", p))
	    result = PRAGMA_OMP_CLAUSE_FULL;
	  ভঙ্গ;
	পক্ষ 'g':
	  যদি (!strcmp ("gang", p))
	    result = PRAGMA_OACC_CLAUSE_GANG;
	  অন্যথা যদি (!strcmp ("grainsize", p))
	    result = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  ভঙ্গ;
	পক্ষ 'h':
	  যদি (!strcmp ("has_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  অন্যথা যদি (!strcmp ("hint", p))
	    result = PRAGMA_OMP_CLAUSE_HINT;
	  অন্যথা যদি (!strcmp ("host", p))
	    result = PRAGMA_OACC_CLAUSE_HOST;
	  ভঙ্গ;
	পক্ষ 'i':
	  যদি (!strcmp ("if_present", p))
	    result = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  অন্যথা যদি (!strcmp ("in_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_IN_REDUCTION;
	  অন্যথা যদি (!strcmp ("inbranch", p))
	    result = PRAGMA_OMP_CLAUSE_INBRANCH;
	  অন্যথা যদি (!strcmp ("independent", p))
	    result = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  অন্যথা যদি (!strcmp ("indirect", p))
	    result = PRAGMA_OMP_CLAUSE_INDIRECT;
	  অন্যথা যদি (!strcmp ("init", p))
	    result = PRAGMA_OMP_CLAUSE_INIT;
	  অন্যথা যদি (!strcmp ("is_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  অন্যথা যদি (!strcmp ("interop", p))
	    result = PRAGMA_OMP_CLAUSE_INTEROP;
	  ভঙ্গ;
	পক্ষ 'l':
	  যদি (!strcmp ("lastprivate", p))
	    result = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  অন্যথা যদি (!strcmp ("linear", p))
	    result = PRAGMA_OMP_CLAUSE_LINEAR;
	  অন্যথা যদি (!strcmp ("link", p))
	    result = PRAGMA_OMP_CLAUSE_LINK;
	  অন্যথা যদি (!strcmp ("local", p))
	    result = PRAGMA_OMP_CLAUSE_LOCAL;
	  ভঙ্গ;
	পক্ষ 'm':
	  যদি (!strcmp ("map", p))
	    result = PRAGMA_OMP_CLAUSE_MAP;
	  অন্যথা যদি (!strcmp ("mergeable", p))
	    result = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  ভঙ্গ;
	পক্ষ 'n':
	  যদি (!strcmp ("no_create", p))
	    result = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  অন্যথা যদি (!strcmp ("nocontext", p))
	    result = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  অন্যথা যদি (!strcmp ("nogroup", p))
	    result = PRAGMA_OMP_CLAUSE_NOGROUP;
	  অন্যথা যদি (!strcmp ("nohost", p))
	    result = PRAGMA_OACC_CLAUSE_NOHOST;
	  অন্যথা যদি (!strcmp ("nontemporal", p))
	    result = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  অন্যথা যদি (!strcmp ("notinbranch", p))
	    result = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  অন্যথা যদি (!strcmp ("novariants", p))
	    result = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  অন্যথা যদি (!strcmp ("nowait", p))
	    result = PRAGMA_OMP_CLAUSE_NOWAIT;
	  অন্যথা যদি (!strcmp ("num_gangs", p))
	    result = PRAGMA_OACC_CLAUSE_অঙ্ক_GANGS;
	  অন্যথা যদি (!strcmp ("num_tasks", p))
	    result = PRAGMA_OMP_CLAUSE_অঙ্ক_TASKS;
	  অন্যথা যদি (!strcmp ("num_teams", p))
	    result = PRAGMA_OMP_CLAUSE_অঙ্ক_TEAMS;
	  অন্যথা যদি (!strcmp ("num_threads", p))
	    result = PRAGMA_OMP_CLAUSE_অঙ্ক_THREADS;
	  অন্যথা যদি (!strcmp ("num_workers", p))
	    result = PRAGMA_OACC_CLAUSE_অঙ্ক_WORKERS;
	  ভঙ্গ;
	পক্ষ 'o':
	  যদি (!strcmp ("ordered", p))
	    result = PRAGMA_OMP_CLAUSE_ORDERED;
	  অন্যথা যদি (!strcmp ("order", p))
	    result = PRAGMA_OMP_CLAUSE_ORDER;
	  ভঙ্গ;
	পক্ষ 'p':
	  যদি (!strcmp ("parallel", p))
	    result = PRAGMA_OMP_CLAUSE_PARALLEL;
	  অন্যথা যদি (!strcmp ("partial", p))
	    result = PRAGMA_OMP_CLAUSE_PARTIAL;
	  অন্যথা যদি (!strcmp ("present", p))
	    result = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  অন্যথা যদি (!strcmp ("present_or_copy", p)
		   || !strcmp ("pcopy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  অন্যথা যদি (!strcmp ("present_or_copyin", p)
		   || !strcmp ("pcopyin", p))
	    result = PRAGMA_OACC_CLAUSE_COPYIN;
	  অন্যথা যদি (!strcmp ("present_or_copyout", p)
		   || !strcmp ("pcopyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
	  অন্যথা যদি (!strcmp ("present_or_create", p)
		   || !strcmp ("pcreate", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  অন্যথা যদি (!strcmp ("priority", p))
	    result = PRAGMA_OMP_CLAUSE_PRIORITY;
	  অন্যথা যদি (!strcmp ("private", p))
	    result = PRAGMA_OMP_CLAUSE_PRIVATE;
	  অন্যথা যদি (!strcmp ("proc_bind", p))
	    result = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  ভঙ্গ;
	পক্ষ 'r':
	  যদি (!strcmp ("reduction", p))
	    result = PRAGMA_OMP_CLAUSE_REDUCTION;
	  ভঙ্গ;
	পক্ষ 's':
	  যদি (!strcmp ("safelen", p))
	    result = PRAGMA_OMP_CLAUSE_SAFELEN;
	  অন্যথা যদি (!strcmp ("schedule", p))
	    result = PRAGMA_OMP_CLAUSE_SCHEDULE;
	  অন্যথা যদি (!strcmp ("sections", p))
	    result = PRAGMA_OMP_CLAUSE_SECTIONS;
	  অন্যথা যদি (!strcmp ("self", p))
	    result = PRAGMA_OACC_CLAUSE_SELF;
	  অন্যথা যদি (!strcmp ("seq", p))
	    result = PRAGMA_OACC_CLAUSE_SEQ;
	  অন্যথা যদি (!strcmp ("shared", p))
	    result = PRAGMA_OMP_CLAUSE_SHARED;
	  অন্যথা যদি (!strcmp ("simd", p))
	    result = PRAGMA_OMP_CLAUSE_SIMD;
	  অন্যথা যদি (!strcmp ("simdlen", p))
	    result = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  ভঙ্গ;
	পক্ষ 't':
	  যদি (!strcmp ("task_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  অন্যথা যদি (!strcmp ("taskgroup", p))
	    result = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  অন্যথা যদি (!strcmp ("thread_limit", p))
	    result = PRAGMA_OMP_CLAUSE_THREAD_LIMIT;
	  অন্যথা যদি (!strcmp ("threads", p))
	    result = PRAGMA_OMP_CLAUSE_THREADS;
	  অন্যথা যদি (!strcmp ("tile", p))
	    result = PRAGMA_OACC_CLAUSE_TILE;
	  অন্যথা যদি (!strcmp ("to", p))
	    result = PRAGMA_OMP_CLAUSE_TO;
	  ভঙ্গ;
	পক্ষ 'u':
	  যদি (!strcmp ("uniform", p))
	    result = PRAGMA_OMP_CLAUSE_UNIFORM;
	  অন্যথা যদি (!strcmp ("untied", p))
	    result = PRAGMA_OMP_CLAUSE_UNTIED;
	  অন্যথা যদি (!strcmp ("use", p))
	    result = PRAGMA_OMP_CLAUSE_USE;
	  অন্যথা যদি (!strcmp ("use_device", p))
	    result = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  অন্যথা যদি (!strcmp ("use_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  অন্যথা যদি (!strcmp ("use_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  অন্যথা যদি (!strcmp ("uses_allocators", p))
	    result = PRAGMA_OMP_CLAUSE_USES_ALLOCATORS;
	  ভঙ্গ;
	পক্ষ 'v':
	  যদি (!strcmp ("vector", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR;
	  অন্যথা যদি (!strcmp ("vector_length", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR_LENGTH;
	  ভঙ্গ;
	পক্ষ 'w':
	  যদি (!strcmp ("wait", p))
	    result = PRAGMA_OACC_CLAUSE_WAIT;
	  অন্যথা যদি (!strcmp ("worker", p))
	    result = PRAGMA_OACC_CLAUSE_WORKER;
	  ভঙ্গ;
	}
    }

  যদি (result != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  প্রত্যাগম result;
}

/* Validate that a clause of the given type does not already exist.  */

স্থির শূন্য
check_no_duplicate_clause (বৃক্ষ clauses, গণনা omp_clause_code code,
			   ধ্রুব বর্ণ *name)
{
  যদি (বৃক্ষ c = omp_find_clause (clauses, code))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

স্থির বৃক্ষ
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, বৃক্ষ list)
{
  vec<বৃক্ষ, va_gc> *args;
  বৃক্ষ t, args_বৃক্ষ;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  args = c_parser_রাশিমালা_list (parser, অসত্য, সত্য, রিক্ত, রিক্ত, রিক্ত, রিক্ত);
  args_বৃক্ষ = build_বৃক্ষ_list_vec (args);

  প্রতি (t = args_বৃক্ষ; t; t = বৃক্ষ_CHAIN (t))
    {
      বৃক্ষ targ = বৃক্ষ_মান (t);

      যদি (targ != error_mark_গ্রন্থি)
	{
	  যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_গ্রন্থি;
	    }
	  অন্যথা
	    {
	      বৃক্ষ c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_বৃক্ষ_vector (args);
  parens.require_close (parser);
  প্রত্যাগম list;
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

সংরচনা omp_dim
{
  বৃক্ষ নিচের_bound, length;
  location_t loc;
  তার্কিক no_colon;
  omp_dim (বৃক্ষ lb, বৃক্ষ len, location_t lo, তার্কিক nc)
  : নিচের_bound (lb), length (len), loc (lo), no_colon (nc) {}
};

স্থির বৃক্ষ
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    গণনা omp_clause_code kind, বৃক্ষ list,
			    তার্কিক map_lvalue = অসত্য)
{
  auto_vec<omp_dim> dims;
  তার্কিক array_section_p;
  auto_vec<c_token> tokens;
  unsigned পূর্ণাঙ্ক tokens_avail = 0;
  c_token *saved_tokens = রিক্ত;

  যাবত্ (1)
    {
      বৃক্ষ t = NULL_বৃক্ষ;
      location_t tloc = c_parser_peek_token (parser)->location;

      যদি (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  যদি (c_parser_next_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
	    {
	      সংরচনা c_রাশিমালা রাশিমালা;
	      যদি (kind == OMP_CLAUSE_DEPEND
		  && c_parser_next_token_is_keyword (parser,
						     RID_OMP_ALL_MEMORY)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  রাশিমালা.মান = ridpointers[RID_OMP_ALL_MEMORY];
		  c_parser_consume_token (parser);
		}
	      অন্যথা
		রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	      যদি (রাশিমালা.মান != error_mark_গ্রন্থি)
		{
		  বৃক্ষ u = build_omp_clause (clause_loc, kind);
		  OMP_CLAUSE_DECL (u) = রাশিমালা.মান;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      যদি (c_parser_next_token_is_not (parser, CPP_COMMA))
		ভঙ্গ;

	      c_parser_consume_token (parser);
	      অনুবর্ত;
	    }

	  tokens.truncate (0);
	  unsigned পূর্ণাঙ্ক nesting_depth = 0;
	  যাবত্ (1)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      বিকল্প (token->type)
		{
		পক্ষ CPP_EOF:
		পক্ষ CPP_PRAGMA_EOL:
		  ভঙ্গ;
		পক্ষ CPP_OPEN_BRACE:
		পক্ষ CPP_OPEN_PAREN:
		পক্ষ CPP_OPEN_SQUARE:
		  ++nesting_depth;
		  গচ্ছ add;
		পক্ষ CPP_CLOSE_BRACE:
		পক্ষ CPP_CLOSE_PAREN:
		পক্ষ CPP_CLOSE_SQUARE:
		  যদি (nesting_depth-- == 0)
		    ভঙ্গ;
		  গচ্ছ add;
		পক্ষ CPP_COMMA:
		  যদি (nesting_depth == 0)
		    ভঙ্গ;
		  গচ্ছ add;
		স্বভাব:
		add:
		  tokens.safe_ঠেলো (*token);
		  c_parser_consume_token (parser);
		  অনুবর্ত;
		}
	      ভঙ্গ;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  memset (&eof_token, 0, পরিমাণ (eof_token));
	  eof_token.type = CPP_EOF;
	  tokens.safe_ঠেলো (eof_token);
	  tokens.safe_ঠেলো (eof_token);

	  saved_tokens = parser->tokens;
	  tokens_avail = parser->tokens_avail;
	  parser->tokens = tokens.address ();
	  parser->tokens_avail = tokens.length ();
	}
      অন্যথা যদি (map_lvalue
	       && (kind == OMP_CLAUSE_MAP
		   || kind == OMP_CLAUSE_TO
		   || kind == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  তার্কিক save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = সত্য;
	  c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	  যদি (রাশিমালা.মান != error_mark_গ্রন্থি)
	    mark_exp_read (রাশিমালা.মান);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  বৃক্ষ decl = রাশিমালা.মান;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  যদি (বৃক্ষ_CODE (decl) == OMP_ARRAY_SECTION)
	    {
	      যাবত্ (বৃক্ষ_CODE (decl) == OMP_ARRAY_SECTION)
		{
		  বৃক্ষ নিচের_bound = বৃক্ষ_OPERAND (decl, 1);
		  বৃক্ষ length = বৃক্ষ_OPERAND (decl, 2);
		  dims.safe_ঠেলো (omp_dim (নিচের_bound, length, loc, অসত্য));
		  decl = বৃক্ষ_OPERAND (decl, 0);
		}

	      যাবত্ (বৃক্ষ_CODE (decl) == ARRAY_REF
		     || বৃক্ষ_CODE (decl) == INDIRECT_REF
		     || বৃক্ষ_CODE (decl) == COMPOUND_রাশিমালা)
		{
		  যদি (বৃক্ষ_CODE (decl) == COMPOUND_রাশিমালা)
		    {
		      decl = বৃক্ষ_OPERAND (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  অন্যথা যদি (বৃক্ষ_CODE (decl) == INDIRECT_REF)
		    {
		      dims.safe_ঠেলো (omp_dim (integer_zero_গ্রন্থি,
					       integer_one_গ্রন্থি, loc, সত্য));
		      decl = বৃক্ষ_OPERAND (decl, 0);
		    }
		  অন্যথা  /* ARRAY_REF. */
		    {
		      বৃক্ষ index = বৃক্ষ_OPERAND (decl, 1);
		      dims.safe_ঠেলো (omp_dim (index, integer_one_গ্রন্থি, loc,
					       সত্য));
		      decl = বৃক্ষ_OPERAND (decl, 0);
		    }
		}

	      প্রতি (পূর্ণাঙ্ক i = dims.length () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].নিচের_bound,
						dims[i].length);
	    }
	  অন্যথা যদি (বৃক্ষ_CODE (decl) == INDIRECT_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = বৃক্ষ_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_গ্রন্থি,
					      integer_one_গ্রন্থি);
	    }
	  অন্যথা যদি (বৃক্ষ_CODE (decl) == ARRAY_REF)
	    {
	      বৃক্ষ idx = বৃক্ষ_OPERAND (decl, 1);

	      decl = বৃক্ষ_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_গ্রন্থি);
	    }
	  অন্যথা যদি (বৃক্ষ_CODE (decl) == NON_LVALUE_রাশিমালা
		   || CONVERT_রাশিমালা_P (decl))
	    decl = বৃক্ষ_OPERAND (decl, 0);

	  বৃক্ষ u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  গচ্ছ next_item;
	}

      যদি (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->মান);

	  যদি (t == NULL_বৃক্ষ)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->মান);
	      t = error_mark_গ্রন্থি;
	    }

	  c_parser_consume_token (parser);
	}
      অন্যথা যদি (c_parser_next_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).মান;
      অন্যথা
	{
	  c_parser_error (parser, "expected identifier");
	  ভঙ্গ;
	}

      যদি (t == error_mark_গ্রন্থি)
	;
      অন্যথা যদি (kind != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  বিকল্প (kind)
	    {
	    পক্ষ OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      যদি (c_parser_peek_token (parser)->type != CPP_OPEN_SQUARE)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_গ্রন্থি;
		  ভঙ্গ;
		}
	      /* FALLTHROUGH  */
	    পক্ষ OMP_CLAUSE_MAP:
	    পক্ষ OMP_CLAUSE_FROM:
	    পক্ষ OMP_CLAUSE_TO:
	    start_component_ref:
	      যাবত্ (c_parser_next_token_is (parser, CPP_DOT)
		     || c_parser_next_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  যদি (c_parser_next_token_is (parser, CPP_DEREF))
		    {
		      c_রাশিমালা t_রাশিমালা;
		      t_রাশিমালা.মান = t;
		      t_রাশিমালা.original_code = ERROR_MARK;
		      t_রাশিমালা.original_type = রিক্ত;
		      set_c_রাশিমালা_source_range (&t_রাশিমালা, op_loc, op_loc);
		      t_রাশিমালা.m_decimal = 0;
		      t_রাশিমালা = convert_lvalue_to_rvalue (op_loc, t_রাশিমালা,
							 সত্য, অসত্য);
		      t = build_indirect_ref (op_loc, t_রাশিমালা.মান, RO_ARROW);
		      arrow_loc = t_রাশিমালা.get_location ();
		    }
		  c_parser_consume_token (parser);
		  যদি (!c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_গ্রন্থি;
		      ভঙ্গ;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  বৃক্ষ ident = comp_tok->মান;
		  location_t comp_loc = comp_tok->location;
		  c_parser_consume_token (parser);
		  t = build_component_ref (op_loc, t, ident, comp_loc,
					   arrow_loc);
		}
	      /* FALLTHROUGH  */
	    পক্ষ OMP_CLAUSE_AFFINITY:
	    পক্ষ OMP_CLAUSE_DEPEND:
	    পক্ষ OMP_CLAUSE_REDUCTION:
	    পক্ষ OMP_CLAUSE_IN_REDUCTION:
	    পক্ষ OMP_CLAUSE_TASK_REDUCTION:
	    পক্ষ OMP_CLAUSE_HAS_DEVICE_ADDR:
	      array_section_p = অসত্য;
	      dims.truncate (0);
	      যাবত্ (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  বৃক্ষ নিচের_bound = NULL_বৃক্ষ, length = NULL_বৃক্ষ;
		  তার্কিক no_colon = অসত্য;

		  c_parser_consume_token (parser);
		  যদি (!c_parser_next_token_is (parser, CPP_COLON))
		    {
		      location_t রাশিমালা_loc
			= c_parser_peek_token (parser)->location;
		      c_রাশিমালা রাশিমালা = c_parser_expression (parser);
		      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা,
						       অসত্য, সত্য);
		      নিচের_bound = রাশিমালা.মান;
		      loc = রাশিমালা_loc;
		    }
		  যদি (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    {
		      length = integer_one_গ্রন্থি;
		      no_colon = সত্য;
		    }
		  অন্যথা
		    {
		      /* Look for `:'.  */
		      যদি (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_গ্রন্থি;
			  ভঙ্গ;
			}
		      array_section_p = সত্য;
		      যদি (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
			{
			  location_t রাশিমালা_loc
			    = c_parser_peek_token (parser)->location;
			  c_রাশিমালা রাশিমালা = c_parser_expression (parser);
			  রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা,
							   অসত্য, সত্য);
			  length = রাশিমালা.মান;
			}
		    }
		  /* Look for the closing `]'.  */
		  যদি (!c_parser_require (parser, CPP_CLOSE_SQUARE,
					 "expected %<]%>"))
		    {
		      t = error_mark_গ্রন্থি;
		      ভঙ্গ;
		    }

		  dims.safe_ঠেলো (omp_dim (নিচের_bound, length, loc, no_colon));
		}

	      যদি (t != error_mark_গ্রন্থি)
		{
		  যদি ((kind == OMP_CLAUSE_MAP
		       || kind == OMP_CLAUSE_FROM
		       || kind == OMP_CLAUSE_TO)
		      && !array_section_p
		      && (c_parser_next_token_is (parser, CPP_DOT)
			  || c_parser_next_token_is (parser, CPP_DEREF)))
		    {
		      প্রতি (unsigned i = 0; i < dims.length (); i++)
			{
			  gcc_assert (dims[i].length == integer_one_গ্রন্থি);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].নিচের_bound);
			}
		      গচ্ছ start_component_ref;
		    }
		  অন্যথা
		    প্রতি (unsigned i = 0; i < dims.length (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].নিচের_bound,
						   dims[i].length);
		}

	      যদি ((kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_গ্রন্থি
		  && parser->tokens_avail != 2)
		{
		  যদি (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_গ্রন্থি;
		    }
		  অন্যথা
		    {
		      parser->tokens = tokens.address ();
		      parser->tokens_avail = tokens.length ();

		      t = c_parser_রাশিমালা_no_commas (parser, রিক্ত).মান;
		      যদি (t != error_mark_গ্রন্থি && parser->tokens_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_গ্রন্থি;
			}
		    }
		}
	      ভঙ্গ;
	    স্বভাব:
	      ভঙ্গ;
	    }

	  যদি (t != error_mark_গ্রন্থি)
	    {
	      বৃক্ষ u = build_omp_clause (clause_loc, kind);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      অন্যথা  /* kind == OMP_CLAUSE_ERROR */
	list = বৃক্ষ_cons (t, build_empty_stmt (tloc), list);

      যদি (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}

    next_item:
      যদি (c_parser_next_token_is_not (parser, CPP_COMMA))
	ভঙ্গ;

      c_parser_consume_token (parser);
    }

  প্রত্যাগম list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

স্থির বৃক্ষ
c_parser_omp_var_list_parens (c_parser *parser, গণনা omp_clause_code kind,
			      বৃক্ষ list, তার্কিক map_lvalue = অসত্য)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  যদি (parser->in_omp_decl_attribute)
    {
      যদি (kind)
	{
	  বৃক্ষ u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = parser->in_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  প্রত্যাগম u;
	}
      অন্যথা
	প্রত্যাগম বৃক্ষ_cons (parser->in_omp_decl_attribute, NULL_বৃক্ষ, list);
    }

  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, kind, list, map_lvalue);
      parens.skip_until_found_close (parser);
    }
  প্রত্যাগম list;
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

স্থির বৃক্ষ
c_parser_oacc_data_clause (c_parser *parser, pragma_omp_clause c_kind,
			   বৃক্ষ list)
{
  গণনা gomp_map_kind kind;
  বিকল্প (c_kind)
    {
    পক্ষ PRAGMA_OACC_CLAUSE_ATTACH:
      kind = GOMP_MAP_ATTACH;
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_CLAUSE_COPY:
      kind = GOMP_MAP_TOFROM;
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_CLAUSE_COPYIN:
      kind = GOMP_MAP_TO;
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_CLAUSE_COPYOUT:
      kind = GOMP_MAP_FROM;
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_CLAUSE_CREATE:
      kind = GOMP_MAP_ALLOC;
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_CLAUSE_DELETE:
      kind = GOMP_MAP_RELEASE;
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_CLAUSE_DETACH:
      kind = GOMP_MAP_DETACH;
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_CLAUSE_DEVICE:
      kind = GOMP_MAP_FORCE_TO;
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      kind = GOMP_MAP_DEVICE_RESIDENT;
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_CLAUSE_LINK:
      kind = GOMP_MAP_LINK;
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_CLAUSE_NO_CREATE:
      kind = GOMP_MAP_IF_PRESENT;
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_CLAUSE_PRESENT:
      kind = GOMP_MAP_FORCE_PRESENT;
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    পক্ষ PRAGMA_OACC_CLAUSE_HOST:
      kind = GOMP_MAP_FORCE_FROM;
      ভঙ্গ;
    স্বভাব:
      gcc_unreachable ();
    }

  বৃক্ষ nl = list;
  তার্কিক readonly = অসত্য;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      যদি (c_kind == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  যদি (token->type == CPP_NAME
	      && !strcmp (IDENTIFIER_POINTER (token->মান), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = সত্য;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       অসত্য);
      parens.skip_until_found_close (parser);
    }

  প্রতি (বৃক্ষ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      যদি (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  প্রত্যাগম nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

স্থির বৃক্ষ
c_parser_oacc_data_clause_deviceptr (c_parser *parser, বৃক্ষ list)
{
  বৃক্ষ vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, রিক্ত);
  প্রতি (t = vars; t && t; t = বৃক্ষ_CHAIN (t))
    {
      বৃক্ষ v = বৃক্ষ_PURPOSE (t);
      location_t loc = রাশিমালা_LOCATION (বৃক্ষ_মান (t));

      যদি (!VAR_P (v) && বৃক্ষ_CODE (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      অন্যথা যদি (বৃক্ষ_TYPE (v) == error_mark_গ্রন্থি)
	;
      অন্যথা যদি (!POINTER_TYPE_P (বৃক্ষ_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      বৃক্ষ u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  প্রত্যাগম list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_collapse (c_parser *parser, বৃক্ষ list)
{
  বৃক্ষ c, অঙ্ক = error_mark_গ্রন্থি;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      অঙ্ক = c_parser_রাশিমালা_no_commas (parser, রিক্ত).মান;
      parens.skip_until_found_close (parser);
    }
  যদি (অঙ্ক == error_mark_গ্রন্থি)
    প্রত্যাগম list;
  mark_exp_read (অঙ্ক);
  অঙ্ক = c_fully_fold (অঙ্ক, অসত্য, রিক্ত);
  যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (অঙ্ক))
      || !বৃক্ষ_fits_shwi_p (অঙ্ক)
      || (n = বৃক্ষ_to_shwi (অঙ্ক)) <= 0
      || (পূর্ণাঙ্ক) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      প্রত্যাগম list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_রাশিমালা (c) = অঙ্ক;
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_copyin (c_parser *parser, বৃক্ষ list)
{
  প্রত্যাগম c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_copyprivate (c_parser *parser, বৃক্ষ list)
{
  প্রত্যাগম c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

স্থির বৃক্ষ
c_parser_omp_clause_default (c_parser *parser, বৃক্ষ list, তার্কিক is_oacc)
{
  গণনা omp_clause_default_kind kind = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  বৃক্ষ c;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;
  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);

      বিকল্প (p[0])
	{
	পক্ষ 'n':
	  যদি (strcmp ("none", p) != 0)
	    গচ্ছ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_NONE;
	  ভঙ্গ;

	পক্ষ 'p':
	  যদি (is_oacc)
	    {
	      যদি (strcmp ("present", p) != 0)
		গচ্ছ invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  অন্যথা
	    {
	      যদি (strcmp ("private", p) != 0)
		গচ্ছ invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRIVATE;
	    }
	  ভঙ্গ;

	পক্ষ 'f':
	  যদি (strcmp ("firstprivate", p) != 0 || is_oacc)
	    গচ্ছ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  ভঙ্গ;

	পক্ষ 's':
	  যদি (strcmp ("shared", p) != 0 || is_oacc)
	    গচ্ছ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_SHARED;
	  ভঙ্গ;

	স্বভাব:
	  গচ্ছ invalid_kind;
	}

      c_parser_consume_token (parser);
    }
  অন্যথা
    {
    invalid_kind:
      যদি (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      অন্যথা
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_found_close (parser);

  যদি (kind == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    প্রত্যাগম list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_KIND (c) = kind;

  প্রত্যাগম c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_firstprivate (c_parser *parser, বৃক্ষ list)
{
  প্রত্যাগম c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_final (c_parser *parser, বৃক্ষ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      বৃক্ষ t, c;
      যদি (!parens.require_open (parser))
	t = error_mark_গ্রন্থি;
      অন্যথা
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	  t = convert_lvalue_to_rvalue (eloc, রাশিমালা, সত্য, সত্য).মান;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, অসত্য, রিক্ত);
	  parens.skip_until_found_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_রাশিমালা (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }
  অন্যথা
    c_parser_error (parser, "expected %<(%>");

  প্রত্যাগম list;
}

/* OpenMP 5.1:
   indirect [( expression )]
*/

স্থির বৃক্ষ
c_parser_omp_clause_indirect (c_parser *parser, বৃক্ষ list)
{
  location_t location = c_parser_peek_token (parser)->location;
  বৃক্ষ t;

  যদি (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      যদি (!parens.require_open (parser))
	প্রত্যাগম list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (loc, রাশিমালা, সত্য, সত্য);
      t = c_objc_common_truthvalue_conversion (loc, রাশিমালা.মান);
      t = c_fully_fold (t, অসত্য, রিক্ত);
      যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t))
	  || বৃক্ষ_CODE (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  প্রত্যাগম list;
	}
      parens.skip_until_found_close (parser);
    }
  অন্যথা
    t = integer_one_গ্রন্থি;

  check_no_duplicate_clause (list, OMP_CLAUSE_INDIRECT, "indirect");

  বৃক্ষ c = build_omp_clause (location, OMP_CLAUSE_INDIRECT);
  OMP_CLAUSE_INDIRECT_রাশিমালা (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;

  প্রত্যাগম c;
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

স্থির বৃক্ষ
c_parser_omp_clause_if (c_parser *parser, বৃক্ষ list, তার্কিক is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  গণনা বৃক্ষ_code if_modifier = ERROR_MARK;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  যদি (is_omp && c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      পূর্ণাঙ্ক n = 2;
      যদি (strcmp (p, "cancel") == 0)
	if_modifier = VOID_CST;
      অন্যথা যদি (strcmp (p, "parallel") == 0)
	if_modifier = OMP_PARALLEL;
      অন্যথা যদি (strcmp (p, "simd") == 0)
	if_modifier = OMP_SIMD;
      অন্যথা যদি (strcmp (p, "task") == 0)
	if_modifier = OMP_TASK;
      অন্যথা যদি (strcmp (p, "taskloop") == 0)
	if_modifier = OMP_TASKLOOP;
      অন্যথা যদি (strcmp (p, "target") == 0)
	{
	  if_modifier = OMP_TARGET;
	  যদি (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	    {
	      p = IDENTIFIER_POINTER (c_parser_peek_2nd_token (parser)->মান);
	      যদি (strcmp ("data", p) == 0)
		if_modifier = OMP_TARGET_DATA;
	      অন্যথা যদি (strcmp ("update", p) == 0)
		if_modifier = OMP_TARGET_UPDATE;
	      অন্যথা যদি (strcmp ("enter", p) == 0)
		if_modifier = OMP_TARGET_ENTER_DATA;
	      অন্যথা যদি (strcmp ("exit", p) == 0)
		if_modifier = OMP_TARGET_EXIT_DATA;
	      যদি (if_modifier != OMP_TARGET)
		{
		  n = 3;
		  c_parser_consume_token (parser);
		}
	      অন্যথা
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<data%>, %<update%>, %<enter%> "
				 "or %<exit%>");
		  if_modifier = ERROR_MARK;
		}
	      যদি (if_modifier == OMP_TARGET_ENTER_DATA
		  || if_modifier == OMP_TARGET_EXIT_DATA)
		{
		  যদি (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_POINTER
				(c_parser_peek_2nd_token (parser)->মান);
		      যদি (strcmp ("data", p) == 0)
			n = 4;
		    }
		  যদি (n == 4)
		    c_parser_consume_token (parser);
		  অন্যথা
		    {
		      location_t loc
			= c_parser_peek_2nd_token (parser)->location;
		      error_at (loc, "expected %<data%>");
		      if_modifier = ERROR_MARK;
		    }
		}
	    }
	}
      যদি (if_modifier != ERROR_MARK)
	{
	  যদি (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  অন্যথা
	    {
	      যদি (n > 2)
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<:%>");
		}
	      if_modifier = ERROR_MARK;
	    }
	}
    }

  location_t loc = c_parser_peek_token (parser)->location;
  c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
  রাশিমালা = convert_lvalue_to_rvalue (loc, রাশিমালা, সত্য, সত্য);
  বৃক্ষ t = c_objc_common_truthvalue_conversion (loc, রাশিমালা.মান), c;
  t = c_fully_fold (t, অসত্য, রিক্ত);
  parens.skip_until_found_close (parser);

  প্রতি (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IF)
      {
	যদি (if_modifier != ERROR_MARK
	    && OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    ধ্রুব বর্ণ *p = রিক্ত;
	    বিকল্প (if_modifier)
	      {
	      পক্ষ VOID_CST: p = "cancel"; ভঙ্গ;
	      পক্ষ OMP_PARALLEL: p = "parallel"; ভঙ্গ;
	      পক্ষ OMP_SIMD: p = "simd"; ভঙ্গ;
	      পক্ষ OMP_TASK: p = "task"; ভঙ্গ;
	      পক্ষ OMP_TASKLOOP: p = "taskloop"; ভঙ্গ;
	      পক্ষ OMP_TARGET_DATA: p = "target data"; ভঙ্গ;
	      পক্ষ OMP_TARGET: p = "target"; ভঙ্গ;
	      পক্ষ OMP_TARGET_UPDATE: p = "target update"; ভঙ্গ;
	      পক্ষ OMP_TARGET_ENTER_DATA: p = "target enter data"; ভঙ্গ;
	      পক্ষ OMP_TARGET_EXIT_DATA: p = "target exit data"; ভঙ্গ;
	      স্বভাব: gcc_unreachable ();
	      }
	    error_at (location, "too many %<if%> clauses with %qs modifier",
		      p);
	    প্রত্যাগম list;
	  }
	অন্যথা যদি (OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    যদি (!is_omp)
	      error_at (location, "too many %<if%> clauses");
	    অন্যথা
	      error_at (location, "too many %<if%> clauses without modifier");
	    প্রত্যাগম list;
	  }
	অন্যথা যদি (if_modifier == ERROR_MARK
		 || OMP_CLAUSE_IF_MODIFIER (c) == ERROR_MARK)
	  {
	    error_at (location, "if any %<if%> clause has modifier, then all "
				"%<if%> clauses have to use modifier");
	    প্রত্যাগম list;
	  }
      }

  c = build_omp_clause (location, OMP_CLAUSE_IF);
  OMP_CLAUSE_IF_MODIFIER (c) = if_modifier;
  OMP_CLAUSE_IF_রাশিমালা (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_lastprivate (c_parser *parser, বৃক্ষ list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  যদি (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      তার্কিক conditional = অসত্য;
      যদি (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  ধ্রুব বর্ণ *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
	  যদি (strcmp (p, "conditional") == 0)
	    {
	      conditional = সত্য;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      বৃক্ষ nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      যদি (conditional)
	প্রতি (বৃক্ষ c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      প্রত্যাগম nlist;
    }
  প্রত্যাগম list;
}

/* OpenMP 3.1:
   mergeable */

স্থির বৃক্ষ
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_UNUSED, বৃক্ষ list)
{
  বৃক্ষ c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  প্রত্যাগম c;
}

/* OpenMP 2.5:
   nowait */

স্থির বৃক্ষ
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_UNUSED, বৃক্ষ list)
{
  বৃক্ষ c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_অঙ্ক_threads (c_parser *parser, বৃক্ষ list)
{
  location_t অঙ্ক_threads_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
      বৃক্ষ c, t = রাশিমালা.মান;
      t = c_fully_fold (t, অসত্য, রিক্ত);

      parens.skip_until_found_close (parser);

      যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  প্রত্যাগম list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (রাশিমালা_loc, LE_রাশিমালা, boolean_type_গ্রন্থি, t,
		       build_int_cst (বৃক্ষ_TYPE (t), 0));
      protected_set_রাশিমালা_location (c, রাশিমালা_loc);
      যদি (c == boolean_true_গ্রন্থি)
	{
	  warning_at (রাশিমালা_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_গ্রন্থি;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_অঙ্ক_THREADS, "num_threads");

      c = build_omp_clause (অঙ্ক_threads_loc, OMP_CLAUSE_অঙ্ক_THREADS);
      OMP_CLAUSE_অঙ্ক_THREADS_রাশিমালা (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  প্রত্যাগম list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_অঙ্ক_tasks (c_parser *parser, বৃক্ষ list)
{
  location_t অঙ্ক_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      তার্কিক strict = অসত্য;
      যদি (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান),
		     "strict") == 0)
	{
	  strict = সত্য;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
      বৃক্ষ c, t = রাশিমালা.মান;
      t = c_fully_fold (t, অসত্য, রিক্ত);

      parens.skip_until_found_close (parser);

      যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  প্রত্যাগম list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (রাশিমালা_loc, LE_রাশিমালা, boolean_type_গ্রন্থি, t,
			   build_int_cst (বৃক্ষ_TYPE (t), 0));
      যদি (CAN_HAVE_LOCATION_P (c))
	SET_রাশিমালা_LOCATION (c, রাশিমালা_loc);
      যদি (c == boolean_true_গ্রন্থি)
	{
	  warning_at (রাশিমালা_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_গ্রন্থি;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_অঙ্ক_TASKS, "num_tasks");

      c = build_omp_clause (অঙ্ক_tasks_loc, OMP_CLAUSE_অঙ্ক_TASKS);
      OMP_CLAUSE_অঙ্ক_TASKS_রাশিমালা (c) = t;
      OMP_CLAUSE_অঙ্ক_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  প্রত্যাগম list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_grainsize (c_parser *parser, বৃক্ষ list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      তার্কিক strict = অসত্য;
      যদি (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান),
		     "strict") == 0)
	{
	  strict = সত্য;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
      বৃক্ষ c, t = রাশিমালা.মান;
      t = c_fully_fold (t, অসত্য, রিক্ত);

      parens.skip_until_found_close (parser);

      যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  প্রত্যাগম list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (রাশিমালা_loc, LE_রাশিমালা, boolean_type_গ্রন্থি, t,
			   build_int_cst (বৃক্ষ_TYPE (t), 0));
      যদি (CAN_HAVE_LOCATION_P (c))
	SET_রাশিমালা_LOCATION (c, রাশিমালা_loc);
      যদি (c == boolean_true_গ্রন্থি)
	{
	  warning_at (রাশিমালা_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_গ্রন্থি;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_রাশিমালা (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  প্রত্যাগম list;
}

/* OpenMP 4.5:
   priority ( expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_priority (c_parser *parser, বৃক্ষ list)
{
  location_t priority_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
      বৃক্ষ c, t = রাশিমালা.মান;
      t = c_fully_fold (t, অসত্য, রিক্ত);

      parens.skip_until_found_close (parser);

      যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  প্রত্যাগম list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (রাশিমালা_loc, LT_রাশিমালা, boolean_type_গ্রন্থি, t,
			   build_int_cst (বৃক্ষ_TYPE (t), 0));
      যদি (CAN_HAVE_LOCATION_P (c))
	SET_রাশিমালা_LOCATION (c, রাশিমালা_loc);
      যদি (c == boolean_true_গ্রন্থি)
	{
	  warning_at (রাশিমালা_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_গ্রন্থি;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_PRIORITY, "priority");

      c = build_omp_clause (priority_loc, OMP_CLAUSE_PRIORITY);
      OMP_CLAUSE_PRIORITY_রাশিমালা (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  প্রত্যাগম list;
}

/* OpenMP 4.5:
   hint ( expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_hint (c_parser *parser, বৃক্ষ list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
      বৃক্ষ c, t = রাশিমালা.মান;
      t = c_fully_fold (t, অসত্য, রিক্ত);
      যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t))
	  || বৃক্ষ_CODE (t) != INTEGER_CST
	  || বৃক্ষ_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  প্রত্যাগম list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_রাশিমালা (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  প্রত্যাগম list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_filter (c_parser *parser, বৃক্ষ list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
      বৃক্ষ c, t = রাশিমালা.মান;
      t = c_fully_fold (t, অসত্য, রিক্ত);
      যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  প্রত্যাগম list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_রাশিমালা (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  প্রত্যাগম list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

স্থির বৃক্ষ
c_parser_omp_clause_defaultmap (c_parser *parser, বৃক্ষ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  বৃক্ষ c;
  ধ্রুব বর্ণ *p;
  গণনা omp_clause_defaultmap_kind behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  গণনা omp_clause_defaultmap_kind category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;
  যদি (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  অন্যথা যদি (!c_parser_next_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      গচ্ছ out_err;
    }
  অন্যথা
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);

  বিকল্প (p[0])
    {
    পক্ষ 'a':
      যদি (strcmp ("alloc", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ALLOC;
      অন্যথা
	গচ্ছ invalid_behavior;
      ভঙ্গ;

    পক্ষ 'd':
      যদি (strcmp ("default", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
      অন্যথা
	গচ্ছ invalid_behavior;
      ভঙ্গ;

    পক্ষ 'f':
      যদি (strcmp ("firstprivate", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FIRSTPRIVATE;
      অন্যথা যদি (strcmp ("from", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FROM;
      অন্যথা
	গচ্ছ invalid_behavior;
      ভঙ্গ;

    পক্ষ 'n':
      যদি (strcmp ("none", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_NONE;
      অন্যথা
	গচ্ছ invalid_behavior;
      ভঙ্গ;

    পক্ষ 'p':
      যদি (strcmp ("present", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_PRESENT;
      অন্যথা
	গচ্ছ invalid_behavior;
      ভঙ্গ;

    পক্ষ 't':
      যদি (strcmp ("tofrom", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TOFROM;
      অন্যথা যদি (strcmp ("to", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TO;
      অন্যথা
	গচ্ছ invalid_behavior;
      ভঙ্গ;

    স্বভাব:
      গচ্ছ invalid_behavior;
    }
  c_parser_consume_token (parser);

  যদি (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	গচ্ছ out_err;
      যদি (!c_parser_next_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  গচ্ছ out_err;
	}
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      বিকল্প (p[0])
	{
	পক্ষ 'a':
	  যদি (strcmp ("aggregate", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE;
	  অন্যথা যদি (strcmp ("all", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL;
	  অন্যথা
	    গচ্ছ invalid_category;
	  ভঙ্গ;

	পক্ষ 'p':
	  যদি (strcmp ("pointer", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER;
	  অন্যথা
	    গচ্ছ invalid_category;
	  ভঙ্গ;

	পক্ষ 's':
	  যদি (strcmp ("scalar", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR;
	  অন্যথা
	    গচ্ছ invalid_category;
	  ভঙ্গ;

	স্বভাব:
	  গচ্ছ invalid_category;
	}

      c_parser_consume_token (parser);
    }
  parens.skip_until_found_close (parser);

  প্রতি (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEFAULTMAP
	&& (category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
	    || OMP_CLAUSE_DEFAULTMAP_CATEGORY (c) == category
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL)))
      {
	গণনা omp_clause_defaultmap_kind cat = category;
	location_t loc = OMP_CLAUSE_LOCATION (c);
	যদি (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
		&& (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		    != OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)))
	  cat = OMP_CLAUSE_DEFAULTMAP_CATEGORY (c);
	p = রিক্ত;
	বিকল্প (cat)
	  {
	  পক্ষ OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED:
	    p = রিক্ত;
	    ভঙ্গ;
	  পক্ষ OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL:
	    p = "all";
	    ভঙ্গ;
	  পক্ষ OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE:
	    p = "aggregate";
	    ভঙ্গ;
	  পক্ষ OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER:
	    p = "pointer";
	    ভঙ্গ;
	  পক্ষ OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR:
	    p = "scalar";
	    ভঙ্গ;
	  স্বভাব:
	    gcc_unreachable ();
	  }
	যদি (p)
	  error_at (loc, "too many %<defaultmap%> clauses with %qs category",
		    p);
	অন্যথা
	  error_at (loc, "too many %<defaultmap%> clauses with unspecified "
			 "category");
	ভঙ্গ;
      }

  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULTMAP);
  OMP_CLAUSE_DEFAULTMAP_SET_KIND (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;

 out_err:
  parens.skip_until_found_close (parser);
  প্রত্যাগম list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_use_device_ptr (c_parser *parser, বৃক্ষ list)
{
  প্রত্যাগম c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_use_device_addr (c_parser *parser, বৃক্ষ list)
{
  প্রত্যাগম c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_has_device_addr (c_parser *parser, বৃক্ষ list)
{
  প্রত্যাগম c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_is_device_ptr (c_parser *parser, বৃক্ষ list)
{
  প্রত্যাগম c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

স্থির বৃক্ষ
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_code code,
				 বৃক্ষ list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
  c_রাশিমালা রাশিমালা = c_parser_expression (parser);
  রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
  বৃক্ষ c, t = রাশিমালা.মান;
  t = c_fully_fold (t, অসত্য, রিক্ত);

  parens.skip_until_found_close (parser);

  যদি (t == error_mark_গ্রন্থি)
    প্রত্যাগম list;
  অন্যথা যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t)))
    {
      error_at (রাশিমালা_loc, "%qs expression must be integral",
		omp_clause_code_name[code]);
      প্রত্যাগম list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (রাশিমালা_loc, LE_রাশিমালা, boolean_type_গ্রন্থি, t,
		       build_int_cst (বৃক্ষ_TYPE (t), 0));
  protected_set_রাশিমালা_location (c, রাশিমালা_loc);
  যদি (c == boolean_true_গ্রন্থি)
    {
      warning_at (রাশিমালা_loc, 0,
		  "%qs value must be positive",
		  omp_clause_code_name[code]);
      t = integer_one_গ্রন্থি;
    }

  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  c = build_omp_clause (loc, code);
  OMP_CLAUSE_OPERAND (c, 0) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
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

স্থির বৃক্ষ
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_code kind,
			    ধ্রুব বর্ণ *str, বৃক্ষ list)
{
  ধ্রুব বর্ণ *id = "num";
  বৃক্ষ ops[2] = { NULL_বৃক্ষ, NULL_বৃক্ষ }, c;

  যদি (kind == OMP_CLAUSE_VECTOR)
    id = "length";

  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      কুরু
	{
	  c_token *next = c_parser_peek_token (parser);
	  পূর্ণাঙ্ক idx = 0;

	  /* Gang static argument.  */
	  যদি (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		গচ্ছ cleanup_error;

	      idx = 1;
	      যদি (ops[idx] != NULL_বৃক্ষ)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  গচ্ছ cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      যদি (c_parser_next_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_গ্রন্থি;

		  যদি (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      অনুবর্ত;
		    }
		  অন্যথা
		    ভঙ্গ;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  অন্যথা যদি (c_parser_next_token_is (parser, CPP_NAME)
		   && strcmp (id, IDENTIFIER_POINTER (next->মান)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  যদি (ops[idx] != NULL_বৃক্ষ)
	    {
	      c_parser_error (parser, "unexpected argument");
	      গচ্ছ cleanup_error;
	    }

	  location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
	  c_রাশিমালা cexpr = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	  cexpr = convert_lvalue_to_rvalue (রাশিমালা_loc, cexpr, অসত্য, সত্য);
	  বৃক্ষ রাশিমালা = cexpr.মান;
	  যদি (রাশিমালা == error_mark_গ্রন্থি)
	    গচ্ছ cleanup_error;

	  রাশিমালা = c_fully_fold (রাশিমালা, অসত্য, রিক্ত);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (রাশিমালা)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      প্রত্যাগম list;
	    }

	  বৃক্ষ c = fold_build2_loc (রাশিমালা_loc, LE_রাশিমালা, boolean_type_গ্রন্থি, রাশিমালা,
				    build_int_cst (বৃক্ষ_TYPE (রাশিমালা), 0));
	  যদি (c == boolean_true_গ্রন্থি)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      রাশিমালা = integer_one_গ্রন্থি;
	    }

	  ops[idx] = রাশিমালা;

	  যদি (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      অনুবর্ত;
	    }
	  ভঙ্গ;
	}
      যাবত্ (1);

      যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	গচ্ছ cleanup_error;
    }

  check_no_duplicate_clause (list, kind, str);

  c = build_omp_clause (loc, kind);

  যদি (ops[1])
    OMP_CLAUSE_OPERAND (c, 1) = ops[1];

  OMP_CLAUSE_OPERAND (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  প্রত্যাগম c;

 cleanup_error:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  প্রত্যাগম list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

স্থির বৃক্ষ
c_parser_oacc_simple_clause (location_t loc, গণনা omp_clause_code code,
			     বৃক্ষ list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  বৃক্ষ c = build_omp_clause (loc, code);
  OMP_CLAUSE_CHAIN (c) = list;

  প্রত্যাগম c;
}

/* OpenACC:
   async [( int-expr )] */

স্থির বৃক্ষ
c_parser_oacc_clause_async (c_parser *parser, বৃক্ষ list)
{
  বৃক্ষ c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_গ্রন্থি, GOMP_ASYNC_NOVAL);

  যদি (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_রাশিমালা_no_commas (parser, রিক্ত).মান;
      যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      অন্যথা যদি (t == error_mark_গ্রন্থি
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	প্রত্যাগম list;
    }
  অন্যথা
    t = c_fully_fold (t, অসত্য, রিক্ত);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_রাশিমালা (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  প্রত্যাগম list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

স্থির বৃক্ষ
c_parser_oacc_clause_tile (c_parser *parser, বৃক্ষ list)
{
  বৃক্ষ c, রাশিমালা = error_mark_গ্রন্থি;
  location_t loc;
  বৃক্ষ tile = NULL_বৃক্ষ;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    প্রত্যাগম list;

  কুরু
    {
      যদি (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	প্রত্যাগম list;

      যদি (c_parser_next_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  রাশিমালা = integer_zero_গ্রন্থি;
	}
      অন্যথা
	{
	  location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
	  c_রাশিমালা cexpr = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	  cexpr = convert_lvalue_to_rvalue (রাশিমালা_loc, cexpr, অসত্য, সত্য);
	  রাশিমালা = cexpr.মান;

	  যদি (রাশিমালা == error_mark_গ্রন্থি)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      প্রত্যাগম list;
	    }

	  রাশিমালা = c_fully_fold (রাশিমালা, অসত্য, রিক্ত);

	  যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (রাশিমালা))
	      || !বৃক্ষ_fits_shwi_p (রাশিমালা)
	      || বৃক্ষ_to_shwi (রাশিমালা) <= 0)
	    {
	      error_at (রাশিমালা_loc, "%<tile%> argument needs positive"
			" integral constant");
	      রাশিমালা = integer_zero_গ্রন্থি;
	    }
	}

      tile = বৃক্ষ_cons (NULL_বৃক্ষ, রাশিমালা, tile);
    }
  যাবত্ (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN));

  /* Consume the trailing ')'.  */
  c_parser_consume_token (parser);

  c = build_omp_clause (loc, OMP_CLAUSE_TILE);
  tile = nreverse (tile);
  OMP_CLAUSE_TILE_LIST (c) = tile;
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
}

/* OpenACC:
   wait [( int-expr-list )] */

স্থির বৃক্ষ
c_parser_oacc_clause_wait (c_parser *parser, বৃক্ষ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  যদি (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  অন্যথা
    {
      বৃক্ষ c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_গ্রন্থি, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  প্রত্যাগম list;
}

/* OpenACC 2.7:
   self [( expression )] */

স্থির বৃক্ষ
c_parser_oacc_compute_clause_self (c_parser *parser, বৃক্ষ list)
{
  বৃক্ষ t;
  location_t location = c_parser_peek_token (parser)->location;
  যদি (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (loc, রাশিমালা, সত্য, সত্য);
      t = c_objc_common_truthvalue_conversion (loc, রাশিমালা.মান);
      t = c_fully_fold (t, অসত্য, রিক্ত);
      parens.skip_until_found_close (parser);
    }
  অন্যথা
    t = truthvalue_true_গ্রন্থি;

  প্রতি (বৃক্ষ c = list; c; c = OMP_CLAUSE_CHAIN (c))
    যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	প্রত্যাগম list;
      }

  বৃক্ষ c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_রাশিমালা (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
}

/* OpenMP 5.0:
   order ( concurrent )

   OpenMP 5.1:
   order ( order-modifier : concurrent )

   order-modifier:
     reproducible
     unconstrained  */

স্থির বৃক্ষ
c_parser_omp_clause_order (c_parser *parser, বৃক্ষ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  বৃক্ষ c;
  ধ্রুব বর্ণ *p;
  তার্কিক unconstrained = অসত্য;
  তার্কিক reproducible = অসত্য;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;
  যদি (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp (p, "unconstrained") == 0)
	unconstrained = সত্য;
      অন্যথা যদি (strcmp (p, "reproducible") == 0)
	reproducible = সত্য;
      অন্যথা
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  গচ্ছ out_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  যদি (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      গচ্ছ out_err;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
  যদি (strcmp (p, "concurrent") != 0)
    {
      c_parser_error (parser, "expected %<concurrent%>");
      গচ্ছ out_err;
    }
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDER, "order");
  c = build_omp_clause (loc, OMP_CLAUSE_ORDER);
  OMP_CLAUSE_ORDER_UNCONSTRAINED (c) = unconstrained;
  OMP_CLAUSE_ORDER_REPRODUCIBLE (c) = reproducible;
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;

 out_err:
  parens.skip_until_found_close (parser);
  প্রত্যাগম list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

স্থির বৃক্ষ
c_parser_omp_clause_bind (c_parser *parser, বৃক্ষ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  বৃক্ষ c;
  ধ্রুব বর্ণ *p;
  গণনা omp_clause_bind_kind kind = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;
  যদি (!c_parser_next_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_found_close (parser);
      প্রত্যাগম list;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
  যদি (strcmp (p, "teams") == 0)
    kind = OMP_CLAUSE_BIND_TEAMS;
  অন্যথা যদি (strcmp (p, "parallel") == 0)
    kind = OMP_CLAUSE_BIND_PARALLEL;
  অন্যথা যদি (strcmp (p, "thread") != 0)
    গচ্ছ invalid;
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_ordered (c_parser *parser, বৃক্ষ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  বৃক্ষ c, অঙ্ক = NULL_বৃক্ষ;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      অঙ্ক = c_parser_রাশিমালা_no_commas (parser, রিক্ত).মান;
      parens.skip_until_found_close (parser);
    }
  যদি (অঙ্ক == error_mark_গ্রন্থি)
    প্রত্যাগম list;
  যদি (অঙ্ক)
    {
      mark_exp_read (অঙ্ক);
      অঙ্ক = c_fully_fold (অঙ্ক, অসত্য, রিক্ত);
      যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (অঙ্ক))
	  || !বৃক্ষ_fits_shwi_p (অঙ্ক)
	  || (n = বৃক্ষ_to_shwi (অঙ্ক)) <= 0
	  || (পূর্ণাঙ্ক) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  প্রত্যাগম list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_রাশিমালা (c) = অঙ্ক;
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_private (c_parser *parser, বৃক্ষ list)
{
  প্রত্যাগম c_parser_omp_var_list_parens (parser, OMP_CLAUSE_PRIVATE, list);
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

স্থির বৃক্ষ
c_parser_omp_clause_reduction (c_parser *parser, গণনা omp_clause_code kind,
			       তার্কিক is_omp, বৃক্ষ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      তার্কিক task = অসত্য;
      তার্কিক inscan = অসত্য;
      গণনা বৃক্ষ_code code = ERROR_MARK;
      বৃক্ষ reduc_id = NULL_বৃক্ষ;

      যদি (kind == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  যদি (c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  অন্যথা যদি (c_parser_next_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      ধ্রুব বর্ণ *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
	      যদি (strcmp (p, "task") == 0)
		task = সত্য;
	      অন্যথা যদি (strcmp (p, "inscan") == 0)
		inscan = সত্য;
	      যদি (task || inscan)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		}
	    }
	}

      বিকল্প (c_parser_peek_token (parser)->type)
	{
	পক্ষ CPP_PLUS:
	  code = PLUS_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_MULT:
	  code = MULT_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_MINUS:
	  যদি (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.add_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  code = MINUS_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_AND:
	  code = BIT_AND_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_XOR:
	  code = BIT_XOR_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_OR:
	  code = BIT_IOR_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_AND_AND:
	  code = TRUTH_ANDIF_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_OR_OR:
	  code = TRUTH_ORIF_রাশিমালা;
	  ভঙ্গ;
        পক্ষ CPP_NAME:
	  {
	    ধ্রুব বর্ণ *p
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
	    যদি (strcmp (p, "min") == 0)
	      {
		code = MIN_রাশিমালা;
		ভঙ্গ;
	      }
	    যদি (strcmp (p, "max") == 0)
	      {
		code = MAX_রাশিমালা;
		ভঙ্গ;
	      }
	    reduc_id = c_parser_peek_token (parser)->মান;
	    ভঙ্গ;
	  }
	স্বভাব:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
	  প্রত্যাগম list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (code, reduc_id);
      যদি (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  বৃক্ষ nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, kind, list);
	  প্রতি (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      বৃক্ষ d = OMP_CLAUSE_DECL (c), type;
	      যদি (বৃক্ষ_CODE (d) != OMP_ARRAY_SECTION)
		type = বৃক্ষ_TYPE (d);
	      অন্যথা
		{
		  পূর্ণাঙ্ক cnt = 0;
		  বৃক্ষ t;
		  প্রতি (t = d;
		      বৃক্ষ_CODE (t) == OMP_ARRAY_SECTION;
		      t = বৃক্ষ_OPERAND (t, 0))
		    cnt++;
		  type = বৃক্ষ_TYPE (t);
		  যাবত্ (cnt > 0)
		    {
		      যদি (বৃক্ষ_CODE (type) != POINTER_TYPE
			  && বৃক্ষ_CODE (type) != ARRAY_TYPE)
			ভঙ্গ;
		      type = বৃক্ষ_TYPE (type);
		      cnt--;
		    }
		}
	      যাবত্ (বৃক্ষ_CODE (type) == ARRAY_TYPE)
		type = বৃক্ষ_TYPE (type);
	      OMP_CLAUSE_REDUCTION_CODE (c) = code;
	      যদি (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      অন্যথা যদি (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      যদি (code == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || বৃক্ষ_CODE (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_found_close (parser);
    }
  প্রত্যাগম list;
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

স্থির বৃক্ষ
c_parser_omp_clause_schedule (c_parser *parser, বৃক্ষ list)
{
  বৃক্ষ c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  পূর্ণাঙ্ক modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  c = build_omp_clause (loc, OMP_CLAUSE_SCHEDULE);

  location_t comma = UNKNOWN_LOCATION;
  যাবত্ (c_parser_next_token_is (parser, CPP_NAME))
    {
      বৃক্ষ kind = c_parser_peek_token (parser)->মান;
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (kind);
      যদি (strcmp ("simd", p) == 0)
	OMP_CLAUSE_SCHEDULE_SIMD (c) = 1;
      অন্যথা যদি (strcmp ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_MONOTONIC;
      অন্যথা যদি (strcmp ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_NONMONOTONIC;
      অন্যথা
	ভঙ্গ;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      যদি (nmodifiers++ == 0
	  && c_parser_next_token_is (parser, CPP_COMMA))
	{
	  comma = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	}
      অন্যথা
	{
	  c_parser_require (parser, CPP_COLON, "expected %<:%>");
	  ভঙ্গ;
	}
    }
  যদি (comma != UNKNOWN_LOCATION)
    error_at (comma, "expected %<:%>");

  যদি ((modifiers & (OMP_CLAUSE_SCHEDULE_MONOTONIC
		    | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
      == (OMP_CLAUSE_SCHEDULE_MONOTONIC
	  | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      বৃক্ষ kind = c_parser_peek_token (parser)->মান;
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (kind);

      বিকল্প (p[0])
	{
	পক্ষ 'd':
	  যদি (strcmp ("dynamic", p) != 0)
	    গচ্ছ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_DYNAMIC;
	  ভঙ্গ;

        পক্ষ 'g':
	  যদি (strcmp ("guided", p) != 0)
	    গচ্ছ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_GUIDED;
	  ভঙ্গ;

	পক্ষ 'r':
	  যদি (strcmp ("runtime", p) != 0)
	    গচ্ছ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_RUNTIME;
	  ভঙ্গ;

	স্বভাব:
	  গচ্ছ invalid_kind;
	}
    }
  অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_STATIC;
  অন্যথা যদি (c_parser_next_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_AUTO;
  অন্যথা
    গচ্ছ invalid_kind;

  c_parser_consume_token (parser);
  যদি (c_parser_next_token_is (parser, CPP_COMMA))
    {
      location_t here;
      c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (here, রাশিমালা, অসত্য, সত্য);
      t = রাশিমালা.মান;
      t = c_fully_fold (t, অসত্য, রিক্ত);

      যদি (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_RUNTIME)
	error_at (here, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      অন্যথা যদি (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_AUTO)
	error_at (here,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      অন্যথা যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (t)) == INTEGER_TYPE
	       || বৃক্ষ_CODE (বৃক্ষ_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  বৃক্ষ s = fold_build2_loc (loc, LE_রাশিমালা, boolean_type_গ্রন্থি, t,
				    build_int_cst (বৃক্ষ_TYPE (t), 0));
	  protected_set_রাশিমালা_location (s, loc);
	  যদি (s == boolean_true_গ্রন্থি)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_গ্রন্থি;
	    }
	  OMP_CLAUSE_SCHEDULE_CHUNK_রাশিমালা (c) = t;
	}
      অন্যথা
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_found_close (parser);
    }
  অন্যথা
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_SCHEDULE_KIND (c)
    = (গণনা omp_clause_schedule_kind)
      (OMP_CLAUSE_SCHEDULE_KIND (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_SCHEDULE, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;

 invalid_kind:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  প্রত্যাগম list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_shared (c_parser *parser, বৃক্ষ list)
{
  প্রত্যাগম c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

স্থির বৃক্ষ
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_UNUSED, বৃক্ষ list)
{
  বৃক্ষ c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_UNTIED, "untied");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_UNTIED);
  OMP_CLAUSE_CHAIN (c) = list;

  প্রত্যাগম c;
}

/* OpenMP 4.0:
   inbranch
   notinbranch */

স্থির বৃক্ষ
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_UNUSED,
			    গণনা omp_clause_code code, বৃক্ষ list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  বৃক্ষ c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  প্রত্যাগম c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

স্থির বৃক্ষ
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_UNUSED,
				গণনা omp_clause_code code, বৃক্ষ list)
{
  বৃক্ষ c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  প্রত্যাগম c;
}

/* OpenMP 4.5:
   nogroup */

স্থির বৃক্ষ
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_UNUSED, বৃক্ষ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  বৃক্ষ c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
}

/* OpenMP 4.5:
   simd
   threads */

স্থির বৃক্ষ
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_UNUSED,
				 গণনা omp_clause_code code, বৃক্ষ list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);
  বৃক্ষ c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_অঙ্ক_teams (c_parser *parser, বৃক্ষ list)
{
  location_t অঙ্ক_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      location_t upper_loc = c_parser_peek_token (parser)->location;
      location_t lower_loc = UNKNOWN_LOCATION;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (upper_loc, রাশিমালা, অসত্য, সত্য);
      বৃক্ষ c, upper = রাশিমালা.মান, lower = NULL_বৃক্ষ;
      upper = c_fully_fold (upper, অসত্য, রিক্ত);

      যদি (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  lower_loc = upper_loc;
	  lower = upper;
	  upper_loc = c_parser_peek_token (parser)->location;
	  রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	  রাশিমালা = convert_lvalue_to_rvalue (upper_loc, রাশিমালা, অসত্য, সত্য);
	  upper = রাশিমালা.মান;
	  upper = c_fully_fold (upper, অসত্য, রিক্ত);
	}

      parens.skip_until_found_close (parser);

      যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (upper))
	  || (lower && !INTEGRAL_TYPE_P (বৃক্ষ_TYPE (lower))))
	{
	  c_parser_error (parser, "expected integer expression");
	  প্রত্যাগম list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (upper_loc, LE_রাশিমালা, boolean_type_গ্রন্থি, upper,
			   build_int_cst (বৃক্ষ_TYPE (upper), 0));
      protected_set_রাশিমালা_location (c, upper_loc);
      যদি (c == boolean_true_গ্রন্থি)
	{
	  warning_at (upper_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  upper = integer_one_গ্রন্থি;
	}
      যদি (lower)
	{
	  c = fold_build2_loc (lower_loc, LE_রাশিমালা, boolean_type_গ্রন্থি, lower,
			       build_int_cst (বৃক্ষ_TYPE (lower), 0));
	  protected_set_রাশিমালা_location (c, lower_loc);
	  যদি (c == boolean_true_গ্রন্থি)
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      lower = NULL_বৃক্ষ;
	    }
	  অন্যথা যদি (বৃক্ষ_CODE (lower) == INTEGER_CST
		   && বৃক্ষ_CODE (upper) == INTEGER_CST
		   && বৃক্ষ_int_cst_lt (upper, lower))
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", lower, upper);
	      lower = NULL_বৃক্ষ;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_অঙ্ক_TEAMS, "num_teams");

      c = build_omp_clause (অঙ্ক_teams_loc, OMP_CLAUSE_অঙ্ক_TEAMS);
      OMP_CLAUSE_অঙ্ক_TEAMS_UPPER_রাশিমালা (c) = upper;
      OMP_CLAUSE_অঙ্ক_TEAMS_LOWER_রাশিমালা (c) = lower;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  প্রত্যাগম list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_thread_limit (c_parser *parser, বৃক্ষ list)
{
  location_t অঙ্ক_thread_limit_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
      বৃক্ষ c, t = রাশিমালা.মান;
      t = c_fully_fold (t, অসত্য, রিক্ত);

      parens.skip_until_found_close (parser);

      যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  প্রত্যাগম list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (রাশিমালা_loc, LE_রাশিমালা, boolean_type_গ্রন্থি, t,
			   build_int_cst (বৃক্ষ_TYPE (t), 0));
      protected_set_রাশিমালা_location (c, রাশিমালা_loc);
      যদি (c == boolean_true_গ্রন্থি)
	{
	  warning_at (রাশিমালা_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_গ্রন্থি;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_LIMIT,
				 "thread_limit");

      c = build_omp_clause (অঙ্ক_thread_limit_loc, OMP_CLAUSE_THREAD_LIMIT);
      OMP_CLAUSE_THREAD_LIMIT_রাশিমালা (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  প্রত্যাগম list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_aligned (c_parser *parser, বৃক্ষ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  বৃক্ষ nl, c;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  যদি (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
      বৃক্ষ alignment = রাশিমালা.মান;
      alignment = c_fully_fold (alignment, অসত্য, রিক্ত);
      যদি (বৃক্ষ_CODE (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (বৃক্ষ_TYPE (alignment))
	  || বৃক্ষ_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_বৃক্ষ;
	}

      প্রতি (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_found_close (parser);
  প্রত্যাগম nl;
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

স্থির বৃক্ষ
c_parser_omp_clause_allocate (c_parser *parser, বৃক্ষ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  বৃক্ষ nl, c;
  বৃক্ষ allocator = NULL_বৃক্ষ;
  বৃক্ষ align = NULL_বৃক্ষ;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  যদি ((c_parser_next_token_is_not (parser, CPP_NAME)
       && c_parser_next_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      তার্কিক has_modifiers = অসত্য;
      বৃক্ষ orig_type = NULL_বৃক্ষ;
      যদি (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  unsigned পূর্ণাঙ্ক n = 3;
	  ধ্রুব বর্ণ *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
	  যদি ((strcmp (p, "allocator") == 0 || strcmp (p, "align") == 0)
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      যদি (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = সত্য;
	      অন্যথা যদি (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  ধ্রুব বর্ণ *q = IDENTIFIER_POINTER (tok->মান);
		  n += 4;
		  যদি ((strcmp (q, "allocator") == 0
		       || strcmp (q, "align") == 0)
		      && c_parser_check_balanced_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = সত্য;
		}
	    }
	  যদি (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
	      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
	      যদি (রাশিমালা.মান == error_mark_গ্রন্থি)
		;
	      অন্যথা যদি (strcmp (p, "allocator") == 0)
		{
		  allocator = রাশিমালা.মান;
		  allocator = c_fully_fold (allocator, অসত্য, রিক্ত);
		  orig_type = রাশিমালা.original_type
			      ? রাশিমালা.original_type : বৃক্ষ_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      অন্যথা
		{
		  align = রাশিমালা.মান;
		  align = c_fully_fold (align, অসত্য, রিক্ত);
		}
	      parens2.skip_until_found_close (parser);
	      যদি (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  ধ্রুব বর্ণ *q = "";
		  যদি (c_parser_next_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_POINTER (tok->মান);
		  যদি (strcmp (q, "allocator") != 0 && strcmp (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_found_close (parser);
		      প্রত্যাগম list;
		    }
		  অন্যথা যদি (strcmp (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_found_close (parser);
		      প্রত্যাগম list;
		    }
		  c_parser_consume_token (parser);
		  যদি (!parens2.require_open (parser))
		    {
		      parens.skip_until_found_close (parser);
		      প্রত্যাগম list;
		    }
		  রাশিমালা_loc = c_parser_peek_token (parser)->location;
		  রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
		  রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য,
						   সত্য);
		  যদি (strcmp (q, "allocator") == 0)
		    {
		      allocator = রাশিমালা.মান;
		      allocator = c_fully_fold (allocator, অসত্য, রিক্ত);
		      orig_type = রাশিমালা.original_type
				  ? রাশিমালা.original_type : বৃক্ষ_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  অন্যথা
		    {
		      align = রাশিমালা.মান;
		      align = c_fully_fold (align, অসত্য, রিক্ত);
		    }
		  parens2.skip_until_found_close (parser);
		}
	    }
	}
      যদি (!has_modifiers)
	{
	  location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
	  c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	  রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
	  যদি (রাশিমালা.মান != error_mark_গ্রন্থি)
	    {
	      allocator = রাশিমালা.মান;
	      allocator = c_fully_fold (allocator, অসত্য, রিক্ত);
	      orig_type = রাশিমালা.original_type
			  ? রাশিমালা.original_type : বৃক্ষ_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      যদি (allocator
	  && (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (allocator))
	      || বৃক্ষ_CODE (orig_type) != ENUMERAL_TYPE
	      || (TYPE_NAME (orig_type)
		  != get_identifier ("omp_allocator_handle_t"))))
        {
          error_at (clause_loc, "%<allocate%> clause allocator expression "
				"has type %qT rather than "
				"%<omp_allocator_handle_t%>",
				বৃক্ষ_TYPE (allocator));
          allocator = NULL_বৃক্ষ;
        }
      যদি (align
	  && (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (align))
	      || !বৃক্ষ_fits_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_বৃক্ষ;
	}
      যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_found_close (parser);
	  প্রত্যাগম list;
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALLOCATE, list);

  যদি (allocator || align)
    প্রতি (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      {
	OMP_CLAUSE_ALLOCATE_ALLOCATOR (c) = allocator;
	OMP_CLAUSE_ALLOCATE_ALIGN (c) = align;
      }

  parens.skip_until_found_close (parser);
  প্রত্যাগম nl;
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

স্থির বৃক্ষ
c_parser_omp_clause_uses_allocators (c_parser *parser, বৃক্ষ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  বৃক্ষ nl = list;
  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

parse_next:

  তার্কিক has_modifiers = অসত্য;
  তার্কিক seen_allocators = অসত্য;
  বৃক্ষ memspace_রাশিমালা = NULL_বৃক্ষ;
  বৃক্ষ traits_var = NULL_বৃক্ষ;

  যদি (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      unsigned পূর্ণাঙ্ক n = 3;
      ধ্রুব বর্ণ *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি ((strcmp (p, "traits") == 0 || strcmp (p, "memspace") == 0)
	  && c_parser_check_balanced_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  যদি (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = সত্য;
	  অন্যথা যদি (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      ধ্রুব বর্ণ *q = IDENTIFIER_POINTER (tok->মান);
	      n += 4;
	      যদি ((strcmp (q, "traits") == 0
		   || strcmp (q, "memspace") == 0)
		  && c_parser_check_balanced_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  যদি (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = সত্য;
		  যদি ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      ধ্রুব বর্ণ *m = IDENTIFIER_POINTER (tok->মান);
		      যদি (strcmp (p, m) == 0 || strcmp (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  গচ্ছ end;
			}
		    }
		}
	    }
	}
      যদি (has_modifiers)
	{
	  c_parser_consume_token (parser);
	  matching_parens parens2;
	  parens2.require_open (parser);
	  c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	  যদি (রাশিমালা.মান == error_mark_গ্রন্থি)
	    ;
	  অন্যথা যদি (strcmp (p, "traits") == 0)
	    {
	      traits_var = রাশিমালা.মান;
	      traits_var = c_fully_fold (traits_var, অসত্য, রিক্ত);
	      mark_exp_read (traits_var);
	    }
	  অন্যথা
	    {
	      memspace_রাশিমালা = রাশিমালা.মান;
	      memspace_রাশিমালা = c_fully_fold (memspace_রাশিমালা, অসত্য, রিক্ত);
	    }
	  parens2.skip_until_found_close (parser);
	  যদি (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      ধ্রুব বর্ণ *q = "";
	      যদি (c_parser_next_token_is (parser, CPP_NAME))
		q = IDENTIFIER_POINTER (tok->মান);
	      যদি (strcmp (q, "traits") != 0 && strcmp (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_found_close (parser);
		  প্রত্যাগম list;
		}
	      অন্যথা যদি (strcmp (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_found_close (parser);
		  প্রত্যাগম list;
		}
	      c_parser_consume_token (parser);
	      যদি (!parens2.require_open (parser))
		{
		  parens.skip_until_found_close (parser);
		  প্রত্যাগম list;
		}
	      রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	      যদি (strcmp (q, "traits") == 0)
		{
		  traits_var = রাশিমালা.মান;
		  traits_var = c_fully_fold (traits_var, অসত্য, রিক্ত);
		  mark_exp_read (traits_var);
		}
	      অন্যথা
		{
		  memspace_রাশিমালা = রাশিমালা.মান;
		  memspace_রাশিমালা = c_fully_fold (memspace_রাশিমালা, অসত্য, রিক্ত);
		}
	      parens2.skip_until_found_close (parser);
	    }
	  যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    গচ্ছ end;
	}
    }

  যাবত্ (c_parser_next_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      ধ্রুব বর্ণ *tok_s = IDENTIFIER_POINTER (tok->মান);
      বৃক্ষ t = lookup_name (tok->মান);
      যদি (t == NULL_বৃক্ষ)
	{
	  undeclared_variable (tok->location, tok->মান);
	  t = error_mark_গ্রন্থি;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      বৃক্ষ legacy_traits = NULL_বৃক্ষ;
      যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  ধ্রুব বর্ণ *tok_a
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
	  c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_found_close (parser);

	  যদি (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      গচ্ছ end;
	    }
	  legacy_traits = c_fully_fold (রাশিমালা.মান, অসত্য, রিক্ত);
	  যদি (legacy_traits == error_mark_গ্রন্থি)
	    গচ্ছ end;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  যদি (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.add_fixit_replace (alloc_loc, "traits");
	      richloc.add_fixit_ঢোকাও_after (close_loc, ": ");
	      richloc.add_fixit_ঢোকাও_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      যদি (seen_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  গচ্ছ end;
	}
      seen_allocators = সত্য;

      বৃক্ষ c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_USES_ALLOCATORS);
      OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c) = memspace_রাশিমালা;
      OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      যদি (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      অন্যথা
	ভঙ্গ;
    }

  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      গচ্ছ parse_next;
    }

 end:
  parens.skip_until_found_close (parser);
  প্রত্যাগম nl;
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

স্থির বৃক্ষ
c_parser_omp_clause_linear (c_parser *parser, বৃক্ষ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  বৃক্ষ nl, c, step;
  গণনা omp_clause_linear_kind kind = OMP_CLAUSE_LINEAR_DEFAULT;
  তার্কিক old_linear_modifier = অসত্য;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (tok->মান);
      যদি (strcmp ("val", p) == 0)
	kind = OMP_CLAUSE_LINEAR_VAL;
      যদি (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	kind = OMP_CLAUSE_LINEAR_DEFAULT;
      যদি (kind != OMP_CLAUSE_LINEAR_DEFAULT)
	{
	  old_linear_modifier = সত্য;
	  rm1_loc = make_location (tok->location, tok->location,
				   c_parser_peek_2nd_token (parser)->location);
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_LINEAR, list);

  যদি (kind != OMP_CLAUSE_LINEAR_DEFAULT)
    {
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
    }

  যদি (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = রাশিমালা_loc;
      তার্কিক has_modifiers = অসত্য;
      যদি (kind == OMP_CLAUSE_LINEAR_DEFAULT
	  && c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (tok->মান);
	  unsigned পূর্ণাঙ্ক pos = 0;
	  যদি (strcmp ("val", p) == 0)
	    pos = 2;
	  অন্যথা যদি (strcmp ("step", p) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      pos = 3;
	      যদি (c_parser_check_balanced_raw_token_sequence (parser, &pos)
		  && (c_parser_peek_nth_token_raw (parser, pos)->type
		      == CPP_CLOSE_PAREN))
		++pos;
	      অন্যথা
		pos = 0;
	    }
	  যদি (pos)
	    {
	      tok = c_parser_peek_nth_token_raw (parser, pos);
	      যদি (tok->type == CPP_COMMA || tok->type == CPP_CLOSE_PAREN)
		has_modifiers = সত্য;
	    }
	}
      যদি (has_modifiers)
	{
	  step = NULL_বৃক্ষ;
	  যাবত্ (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (tok->মান);
	      যদি (strcmp ("val", p) == 0)
		{
		  যদি (kind != OMP_CLAUSE_LINEAR_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  kind = OMP_CLAUSE_LINEAR_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      অন্যথা যদি (strcmp ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  যদি (parens2.require_open (parser))
		    {
		      যদি (step)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      রাশিমালা_loc = c_parser_peek_token (parser)->location;
		      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
		      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য,
						       সত্য);
		      step = c_fully_fold (রাশিমালা.মান, অসত্য, রিক্ত);
		      যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (step)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  step = integer_one_গ্রন্থি;
			}
		      parens2.skip_until_found_close (parser);
		    }
		  অন্যথা
		    ভঙ্গ;
		}
	      অন্যথা
		ভঙ্গ;
	      যদি (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  অনুবর্ত;
		}
	      ভঙ্গ;
	    }
	  যদি (!step)
	    step = integer_one_গ্রন্থি;
	}
      অন্যথা
	{
	  c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	  রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
	  step = c_fully_fold (রাশিমালা.মান, অসত্য, রিক্ত);
	  যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (step)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      step = integer_one_গ্রন্থি;
	    }
	}

    }
  অন্যথা
    step = integer_one_গ্রন্থি;

  প্রতি (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_LINEAR_STEP (c) = step;
      OMP_CLAUSE_LINEAR_KIND (c) = kind;
      OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c) = old_linear_modifier;
    }

  যদি (old_linear_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      যদি (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_remove (rm1_loc);
	  যদি (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.add_fixit_remove (rm2_loc);
	      richloc.add_fixit_ঢোকাও_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.add_fixit_ঢোকাও_before (close_loc, ")");
	    }
	  অন্যথা
	    richloc.add_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_found_close (parser);
  প্রত্যাগম nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_nontemporal (c_parser *parser, বৃক্ষ list)
{
  প্রত্যাগম c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_safelen (c_parser *parser, বৃক্ষ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  বৃক্ষ c, t;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
  c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
  রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
  t = রাশিমালা.মান;
  t = c_fully_fold (t, অসত্য, রিক্ত);
  যদি (বৃক্ষ_CODE (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t))
      || বৃক্ষ_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_বৃক্ষ;
    }

  parens.skip_until_found_close (parser);
  যদি (t == NULL_বৃক্ষ || t == error_mark_গ্রন্থি)
    প্রত্যাগম list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_রাশিমালা (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

স্থির বৃক্ষ
c_parser_omp_clause_simdlen (c_parser *parser, বৃক্ষ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  বৃক্ষ c, t = NULL_বৃক্ষ, type = NULL_বৃক্ষ, ভাজক = NULL_বৃক্ষ;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  unsigned pos = 3;
  যদি (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান),
		 "scaled") == 0
      && c_parser_check_balanced_raw_token_sequence (parser, &pos)
      && c_parser_peek_nth_token_raw (parser, ++pos)->type == CPP_COLON)
    {
      c_parser_consume_token (parser);
      matching_parens parens2;
      parens2.require_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      সংরচনা c_type_name *ctype = c_parser_type_name (parser);
      যদি (ctype == রিক্ত
	  || (type = groktypename (ctype, রিক্ত, রিক্ত)) == রিক্ত
	  || (!INTEGRAL_TYPE_P (type)
	      && !SCALAR_FLOAT_TYPE_P (type)
	      && বৃক্ষ_CODE (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_গ্রন্থি;
	}
      অন্যথা যদি (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	  রাশিমালা = convert_lvalue_to_rvalue (loc, রাশিমালা, অসত্য, সত্য);
	  ভাজক = রাশিমালা.মান;
	  ভাজক = c_fully_fold (ভাজক, অসত্য, রিক্ত);
	  যদি (বৃক্ষ_CODE (ভাজক) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (বৃক্ষ_TYPE (ভাজক))
	      || বৃক্ষ_int_cst_sgn (ভাজক) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_গ্রন্থি;
	    }
	}
      parens2.skip_until_found_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  যদি (type != error_mark_গ্রন্থি)
    {
      location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
      t = রাশিমালা.মান;
      t = c_fully_fold (t, অসত্য, রিক্ত);
      যদি (বৃক্ষ_CODE (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t))
	  || বৃক্ষ_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_বৃক্ষ;
	}
    }

  parens.skip_until_found_close (parser);
  যদি (type == error_mark_গ্রন্থি || t == NULL_বৃক্ষ || t == error_mark_গ্রন্থি)
    প্রত্যাগম list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_রাশিমালা (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_ভাজক (c) = ভাজক;
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

স্থির বৃক্ষ
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   বৃক্ষ list, তার্কিক depend_p)
{
  বৃক্ষ vec = রিক্ত;
  যদি (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      প্রত্যাগম list;
    }

  যদি (!depend_p)
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_সংখ্যা
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  বৃক্ষ val = c_parser_peek_nth_token (parser, 3)->মান;
	  যদি (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      বৃক্ষ u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      প্রত্যাগম u;
	    }
	}
    }



  যাবত্ (c_parser_next_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_kind == C_ID_ID)
    {
      বৃক্ষ t = lookup_name (c_parser_peek_token (parser)->মান);
      বৃক্ষ addend = রিক্ত;

      যদি (t == NULL_বৃক্ষ)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->মান);
	  t = error_mark_গ্রন্থি;
	}

      c_parser_consume_token (parser);

      তার্কিক neg = অসত্য;
      যদি (c_parser_next_token_is (parser, CPP_MINUS))
	neg = সত্য;
      অন্যথা যদি (!c_parser_next_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_গ্রন্থি;
	  neg = অসত্য;
	  গচ্ছ add_to_vector;
	}
      c_parser_consume_token (parser);

      যদি (c_parser_next_token_is_not (parser, CPP_সংখ্যা))
	{
	  c_parser_error (parser, "expected integer");
	  প্রত্যাগম list;
	}

      addend = c_parser_peek_token (parser)->মান;
      যদি (বৃক্ষ_CODE (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  প্রত্যাগম list;
	}
      c_parser_consume_token (parser);

    add_to_vector:
      যদি (t != error_mark_গ্রন্থি)
	{
	  vec = বৃক্ষ_cons (addend, t, vec);
	  যদি (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      যদি (c_parser_next_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_kind != C_ID_ID)
	ভঙ্গ;

      c_parser_consume_token (parser);
    }

  যদি (vec == NULL_বৃক্ষ)
    প্রত্যাগম list;

  বৃক্ষ u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
  OMP_CLAUSE_DOACROSS_DEPEND (u) = depend_p;
  OMP_CLAUSE_DECL (u) = nreverse (vec);
  OMP_CLAUSE_CHAIN (u) = list;
  প্রত্যাগম u;
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

স্থির বৃক্ষ
c_parser_omp_iterators (c_parser *parser)
{
  বৃক্ষ ret = NULL_বৃক্ষ, *last = &ret;
  c_parser_consume_token (parser);

  ঠেলো_scope ();

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম error_mark_গ্রন্থি;

  কুরু
    {
      বৃক্ষ iter_type = NULL_বৃক্ষ, type_রাশিমালা = NULL_বৃক্ষ;
      যদি (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
	{
	  সংরচনা c_type_name *type = c_parser_type_name (parser);
	  যদি (type != রিক্ত)
	    iter_type = groktypename (type, &type_রাশিমালা, রিক্ত);
	}
      যদি (iter_type == NULL_বৃক্ষ)
	iter_type = integer_type_গ্রন্থি;

      location_t loc = c_parser_peek_token (parser)->location;
      যদি (!c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  ভঙ্গ;
	}

      বৃক্ষ id = c_parser_peek_token (parser)->মান;
      c_parser_consume_token (parser);

      যদি (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	ভঙ্গ;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (eloc, রাশিমালা, সত্য, অসত্য);
      বৃক্ষ begin = রাশিমালা.মান;

      যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ভঙ্গ;

      eloc = c_parser_peek_token (parser)->location;
      রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (eloc, রাশিমালা, সত্য, অসত্য);
      বৃক্ষ end = রাশিমালা.মান;

      বৃক্ষ step = integer_one_গ্রন্থি;
      যদি (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	  রাশিমালা = convert_lvalue_to_rvalue (eloc, রাশিমালা, সত্য, অসত্য);
	  step = রাশিমালা.মান;
	}

      বৃক্ষ iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *last = make_omp_iterator ();
      OMP_ITERATOR_VAR (*last) = iter_var;
      OMP_ITERATOR_BEGIN (*last) = begin;
      OMP_ITERATOR_END (*last) = end;
      OMP_ITERATOR_STEP (*last) = step;
      last = &বৃক্ষ_CHAIN (*last);

      যদি (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  অনুবর্ত;
	}
      ভঙ্গ;
    }
  যাবত্ (1);

  parens.skip_until_found_close (parser);
  প্রত্যাগম ret ? ret : error_mark_গ্রন্থি;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

স্থির বৃক্ষ
c_parser_omp_clause_affinity (c_parser *parser, বৃক্ষ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  বৃক্ষ nl, iterators = NULL_বৃক্ষ;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      তার্কিক parse_iter = ((strcmp ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      যদি (parse_iter)
	{
	  unsigned n = 3;
	  parse_iter = (c_parser_check_balanced_raw_token_sequence (parser, &n)
			&& (c_parser_peek_nth_token_raw (parser, n)->type
			    == CPP_CLOSE_PAREN)
			&& (c_parser_peek_nth_token_raw (parser, n + 1)->type
			    == CPP_COLON));
	}
      যদি (parse_iter)
	{
	  iterators = c_parser_omp_iterators (parser);
	  যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    {
	      যদি (iterators)
		বের_করো_scope ();
	      parens.skip_until_found_close (parser);
	      প্রত্যাগম list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  যদি (iterators)
    {
      বৃক্ষ block = বের_করো_scope ();
      যদি (iterators != error_mark_গ্রন্থি)
	{
	  OMP_ITERATOR_BLOCK (iterators) = block;
	  প্রতি (বৃক্ষ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_বৃক্ষ_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  প্রত্যাগম nl;
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

স্থির বৃক্ষ
c_parser_omp_clause_depend (c_parser *parser, বৃক্ষ list, location_t here)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  গণনা omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_LAST;
  গণনা omp_clause_doacross_kind dkind = OMP_CLAUSE_DOACROSS_LAST;
  বৃক্ষ nl, c, iterators = NULL_বৃক্ষ;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  কুরু
    {
      যদি (c_parser_next_token_is_not (parser, CPP_NAME))
	গচ্ছ invalid_kind;

      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp ("iterator", p) == 0 && iterators == NULL_বৃক্ষ)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  অনুবর্ত;
	}
      যদি (strcmp ("in", p) == 0)
	kind = OMP_CLAUSE_DEPEND_IN;
      অন্যথা যদি (strcmp ("inout", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUT;
      অন্যথা যদি (strcmp ("inoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUTSET;
      অন্যথা যদি (strcmp ("mutexinoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      অন্যথা যদি (strcmp ("out", p) == 0)
	kind = OMP_CLAUSE_DEPEND_OUT;
      অন্যথা যদি (strcmp ("depobj", p) == 0)
	kind = OMP_CLAUSE_DEPEND_DEPOBJ;
      অন্যথা যদি (strcmp ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      অন্যথা যদি (strcmp ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SOURCE;
	}
      অন্যথা
	গচ্ছ invalid_kind;
      ভঙ্গ;
    }
  যাবত্ (1);

  c_parser_consume_token (parser);

  যদি (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_SOURCE
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      বের_করো_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_SOURCE ? "source" : "sink");
      iterators = NULL_বৃক্ষ;
    }

  যদি (dkind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_বৃক্ষ;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_found_close (parser);
      প্রত্যাগম c;
    }

  যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    গচ্ছ resync_fail;

  যদি (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, সত্য);
  অন্যথা
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      যদি (iterators)
	{
	  বৃক্ষ block = বের_করো_scope ();
	  যদি (iterators == error_mark_গ্রন্থি)
	    iterators = NULL_বৃক্ষ;
	  অন্যথা
	    OMP_ITERATOR_BLOCK (iterators) = block;
	}

      প্রতি (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_KIND (c) = kind;
	  যদি (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_বৃক্ষ_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  প্রত্যাগম nl;

 invalid_kind:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  যদি (iterators)
    বের_করো_scope ();
  প্রত্যাগম list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

স্থির বৃক্ষ
c_parser_omp_clause_doacross (c_parser *parser, বৃক্ষ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  গণনা omp_clause_doacross_kind kind = OMP_CLAUSE_DOACROSS_LAST;
  বৃক্ষ nl;
  ধ্রুব বর্ণ *p;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  যদি (c_parser_next_token_is_not (parser, CPP_NAME))
    গচ্ছ invalid_kind;

  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
  যদি (strcmp ("sink", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SINK;
  অন্যথা যদি (strcmp ("source", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SOURCE;
  অন্যথা
    গচ্ছ invalid_kind;

  c_parser_consume_token (parser);

  যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    গচ্ছ resync_fail;

  যদি (kind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      যদি (c_parser_next_token_is (parser, CPP_NAME)
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (nl) = OMP_CLAUSE_DOACROSS_SOURCE;
      OMP_CLAUSE_DECL (nl) = NULL_বৃক্ষ;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  অন্যথা
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, অসত্য);

  parens.skip_until_found_close (parser);
  প্রত্যাগম nl;

 invalid_kind:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  প্রত্যাগম list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

স্থির বৃক্ষ
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, বৃক্ষ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  গণনা omp_clause_fallback_kind kind = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  unsigned n = 3;
  যদি (c_parser_next_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  প্রত্যাগম list;
	}
      c_parser_consume_token (parser);
      যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	প্রত্যাগম list;
      p = "";
      যদি (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp (p, "abort") == 0)
	kind = OMP_CLAUSE_FALLBACK_ABORT;
      অন্যথা যদি (strcmp (p, "default_mem") == 0)
	kind = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      অন্যথা যদি (strcmp (p, "null") == 0)
	kind = OMP_CLAUSE_FALLBACK_NULL;
      অন্যথা
	{
	  c_parser_error (parser, "expected %<abort%>, %<default_mem%>, or "
				  "%<null%> as fallback mode");
	  প্রত্যাগম list;
	}
      c_parser_consume_token (parser);
      যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	প্রত্যাগম list;
      যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	প্রত্যাগম list;
    }
  location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
  c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
  রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
  বৃক্ষ size = c_fully_fold (রাশিমালা.মান, অসত্য, রিক্ত);
  parens.skip_until_found_close (parser);

  যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (size)))
    {
      error_at (রাশিমালা_loc, "expected integer expression");
      প্রত্যাগম list;
    }

  /* Attempt to statically determine when the number is negative.  */
  বৃক্ষ c = fold_build2_loc (রাশিমালা_loc, LT_রাশিমালা, boolean_type_গ্রন্থি, size,
			    build_int_cst (বৃক্ষ_TYPE (size), 0));
  protected_set_রাশিমালা_location (c, রাশিমালা_loc);
  যদি (c == boolean_true_গ্রন্থি)
    {
      warning_at (রাশিমালা_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      size = integer_zero_গ্রন্থি;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_KIND (c) = kind;
  OMP_CLAUSE_DYN_GROUPPRIVATE_রাশিমালা (c) = size;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  প্রত্যাগম list;
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

স্থির বৃক্ষ
c_parser_omp_clause_map (c_parser *parser, বৃক্ষ list, তার্কিক declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  বৃক্ষ nl, c;
  গণনা gomp_map_kind kind = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  পূর্ণাঙ্ক pos = 1;
  পূর্ণাঙ্ক map_kind_pos = 0;
  পূর্ণাঙ্ক iterator_length = 0;
  প্রতি (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      যদি (tok->type != CPP_NAME)
	ভঙ্গ;

      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (tok->মান);
      c_token *next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      যদি (strcmp (p, "iterator") == 0 && next_tok->type == CPP_OPEN_PAREN)
	{
	  unsigned n = pos + 2;
	  যদি (c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_length = n - pos + 1;
	      pos = n;
	      next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      যদি (next_tok->type == CPP_COLON)
	{
	  map_kind_pos = pos;
	  ভঙ্গ;
	}

      যদি (next_tok->type == CPP_COMMA)
	pos++;
      অন্যথা যদি (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  unsigned পূর্ণাঙ্ক npos = pos + 2;
	  যদি (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, npos + 1)->type
		  == CPP_COMMA))
	    pos = npos + 1;
	}

      pos++;
    }

  পূর্ণাঙ্ক always_modifier = 0;
  পূর্ণাঙ্ক close_modifier = 0;
  পূর্ণাঙ্ক present_modifier = 0;
  পূর্ণাঙ্ক mapper_modifier = 0;
  পূর্ণাঙ্ক অঙ্ক_commas = 0;
  পূর্ণাঙ্ক অঙ্ক_identifiers = 0;
  বৃক্ষ mapper_name = NULL_বৃক্ষ;
  বৃক্ষ iterators = NULL_বৃক্ষ;
  প্রতি (পূর্ণাঙ্ক pos = 1; pos < map_kind_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      যদি (tok->type == CPP_COMMA)
	{
	  ++অঙ্ক_commas;
	  যদি (অঙ্ক_commas > অঙ্ক_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  অনুবর্ত;
	}

      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (tok->মান);
      যদি (strcmp ("always", p) == 0)
	{
	  যদি (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_found_close (parser);
	      প্রত্যাগম list;
	    }
	  always_modifier++;
	  c_parser_consume_token (parser);
	}
      অন্যথা যদি (strcmp ("close", p) == 0)
	{
	  যদি (close_modifier)
	    {
	      c_parser_error (parser, "too many %<close%> modifiers");
	      parens.skip_until_found_close (parser);
	      প্রত্যাগম list;
	    }
	  close_modifier++;
	  c_parser_consume_token (parser);
	}
      অন্যথা যদি (strcmp ("iterator", p) == 0)
	{
	  যদি (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      প্রত্যাগম list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      অন্যথা যদি (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  যদি (mparens.require_open (parser))
	    {
	      যদি (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  প্রত্যাগম list;
		}

	      tok = c_parser_peek_token (parser);

	      বিকল্প (tok->type)
		{
		পক্ষ CPP_NAME:
		  {
		    mapper_name = tok->মান;
		    c_parser_consume_token (parser);
		    যদি (declare_mapper_p)
		      {
			error_at (tok->location,
				  "in %<declare mapper%> directives, parameter "
				  "to %<mapper%> modifier must be %<default%>");
		      }
		  }
		  ভঙ্গ;

		পক্ষ CPP_KEYWORD:
		  যদি (tok->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      ভঙ্গ;
		    }
		  /* Fallthrough.  */

		স্বভাব:
		  error_at (tok->location,
			    "expected identifier or %<default%>");
		  প্রত্যাগম list;
		}

	      যদি (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  প্রত্যাগম list;
		}

	      mapper_modifier++;
	      pos += 3;
	    }
	}
      অন্যথা যদি (strcmp ("present", p) == 0)
	{
	  যদি (present_modifier)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      প্রত্যাগম list;
	    }
	  present_modifier++;
	  c_parser_consume_token (parser);
	}
      অন্যথা
	{
	  c_parser_error (parser, "%<map%> clause with map-type modifier other "
				  "than %<always%>, %<close%>, %<iterator%>, "
				  "%<mapper%> or %<present%>");
	  parens.skip_until_found_close (parser);
	  প্রত্যাগম list;
	}
      ++অঙ্ক_identifiers;
      যদি (অঙ্ক_identifiers - 1 > অঙ্ক_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_ঢোকাও_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      অঙ্ক_commas = অঙ্ক_identifiers - 1;
    }

  যদি (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      পূর্ণাঙ্ক always_present_modifier = always_modifier && present_modifier;

      যদি (strcmp ("alloc", p) == 0)
	kind = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      অন্যথা যদি (strcmp ("to", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TO
		: present_modifier ? GOMP_MAP_PRESENT_TO
		: always_modifier ? GOMP_MAP_ALWAYS_TO
		: GOMP_MAP_TO);
      অন্যথা যদি (strcmp ("from", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      অন্যথা যদি (strcmp ("tofrom", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      অন্যথা যদি (strcmp ("release", p) == 0)
	kind = GOMP_MAP_RELEASE;
      অন্যথা যদি (strcmp ("delete", p) == 0)
	kind = GOMP_MAP_DELETE;
      অন্যথা
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  প্রত্যাগম list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   সত্য);

  বৃক্ষ last_new = NULL_বৃক্ষ;

  যদি (iterators)
    {
      বৃক্ষ block = বের_করো_scope ();
      যদি (iterators == error_mark_গ্রন্থি)
	iterators = NULL_বৃক্ষ;
      অন্যথা
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  প্রতি (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      last_new = c;
    }

  যদি (mapper_name)
    {
      বৃক্ষ name = build_omp_clause (প্রবেশ_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_ঠেলো_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (প্রবেশ_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_বের_করো_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_গ্রন্থি;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  parens.skip_until_found_close (parser);
  প্রত্যাগম nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

স্থির বৃক্ষ
c_parser_omp_clause_device (c_parser *parser, বৃক্ষ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t রাশিমালা_loc;
  c_রাশিমালা রাশিমালা;
  বৃক্ষ c, t;
  তার্কিক ancestor = অসত্য;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  যদি (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (tok->মান);
      যদি (strcmp ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  যদি ((omp_requires_mask & OMP_REQUIRES_REVERSE_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_found_close (parser);
	      প্রত্যাগম list;
	    }
	  ancestor = সত্য;
	}
      অন্যথা যদি (strcmp ("device_num", p) == 0)
	;
      অন্যথা
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_found_close (parser);
	  প্রত্যাগম list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  রাশিমালা_loc = c_parser_peek_token (parser)->location;
  রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
  রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
  t = রাশিমালা.মান;
  t = c_fully_fold (t, অসত্য, রিক্ত);

  parens.skip_until_found_close (parser);

  যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      প্রত্যাগম list;
    }
  যদি (ancestor && বৃক্ষ_CODE (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (রাশিমালা_loc, "the %<device%> clause expression must evaluate to "
			  "%<1%>");
      প্রত্যাগম list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE, "device");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE);

  OMP_CLAUSE_DEVICE_ID (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEVICE_ANCESTOR (c) = ancestor;

  list = c;
  প্রত্যাগম list;
}

/* OpenMP 4.0:
   dist_schedule ( static )
   dist_schedule ( static , expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_dist_schedule (c_parser *parser, বৃক্ষ list)
{
  বৃক্ষ c, t = NULL_বৃক্ষ;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  যদি (!c_parser_next_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      প্রত্যাগম list;
    }

  c_parser_consume_token (parser);
  যদি (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
      t = রাশিমালা.মান;
      t = c_fully_fold (t, অসত্য, রিক্ত);
      parens.skip_until_found_close (parser);
    }
  অন্যথা
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  যদি (omp_find_clause (list, OMP_CLAUSE_DIST_SCHEDULE))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  যদি (t == error_mark_গ্রন্থি)
    প্রত্যাগম list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_SCHEDULE);
  OMP_CLAUSE_DIST_SCHEDULE_CHUNK_রাশিমালা (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

স্থির বৃক্ষ
c_parser_omp_clause_proc_bind (c_parser *parser, বৃক্ষ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  গণনা omp_clause_proc_bind_kind kind;
  বৃক্ষ c;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp ("primary", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_PRIMARY;
      অন্যথা যদি (strcmp ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  kind = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      অন্যথা যদি (strcmp ("close", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_CLOSE;
      অন্যথা যদি (strcmp ("spread", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_SPREAD;
      অন্যথা
	গচ্ছ invalid_kind;
    }
  অন্যথা
    গচ্ছ invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;

 invalid_kind:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_found_close (parser);
  প্রত্যাগম list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

স্থির বৃক্ষ
c_parser_omp_clause_device_type (c_parser *parser, বৃক্ষ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  গণনা omp_clause_device_type_kind kind;
  বৃক্ষ c;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp ("host", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_HOST;
      অন্যথা যদি (strcmp ("nohost", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      অন্যথা যদি (strcmp ("any", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_ANY;
      অন্যথা
	গচ্ছ invalid_kind;
    }
  অন্যথা
    গচ্ছ invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;

 invalid_kind:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_found_close (parser);
  প্রত্যাগম list;
}

/* OpenMP 4.0:
   from ( variable-list )
   to ( variable-list )

   OpenMP 5.1:
   from ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )
   to ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )

   motion-modifier:
     present | iterator (iterators-definition) | mapper (id)  */

স্থির বৃক্ষ
c_parser_omp_clause_from_to (c_parser *parser, গণনা omp_clause_code kind,
			     বৃক্ষ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  পূর্ণাঙ্ক pos = 1, colon_pos = 0;
  পূর্ণাঙ্ক iterator_length = 0;

  যাবত্ (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      ধ্রুব বর্ণ *identifier =
	IDENTIFIER_POINTER (c_parser_peek_nth_token_raw (parser, pos)->মান);
      যদি (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  unsigned পূর্ণাঙ্ক npos = pos + 2;
	  যদি (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      যদি (strcmp (identifier, "iterator") == 0)
		iterator_length = npos - pos + 1;
	      pos = npos;
	    }
	}
      যদি (c_parser_peek_nth_token_raw (parser, pos + 1)->type == CPP_COMMA)
	pos += 2;
      অন্যথা
	pos++;
      যদি (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_COLON)
	{
	  colon_pos = pos;
	  ভঙ্গ;
	}
    }

  তার্কিক present = অসত্য, mapper_modifier = অসত্য;
  বৃক্ষ iterators = NULL_বৃক্ষ;
  বৃক্ষ mapper_name = NULL_বৃক্ষ;

  প্রতি (পূর্ণাঙ্ক pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      যদি (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  অনুবর্ত;
	}
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (token->মান);
      যদি (strcmp ("present", p) == 0)
	{
	  যদি (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      প্রত্যাগম list;
	    }
	  present = সত্য;
	  c_parser_consume_token (parser);
	}
      অন্যথা যদি (strcmp ("iterator", p) == 0)
	{
	  যদি (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      প্রত্যাগম list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      অন্যথা যদি (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  যদি (mparens.require_open (parser))
	    {
	      যদি (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  প্রত্যাগম list;
		}

	      token = c_parser_peek_token (parser);
	      বিকল্প (token->type)
		{
		পক্ষ CPP_NAME:
		  {
		    mapper_name = token->মান;
		    c_parser_consume_token (parser);
		  }
		  ভঙ্গ;
		পক্ষ CPP_KEYWORD:
		  যদি (token->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      ভঙ্গ;
		    }
		  /* FALLTHROUGH  */
		স্বভাব:
		  error_at (token->location,
			    "expected identifier or %<default%>");
		  প্রত্যাগম list;
		}
	      যদি (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  প্রত্যাগম list;
		}
	      mapper_modifier = সত্য;
	      pos += 3;
	    }
	}
      অন্যথা
	{
	  error_at (token->location,
		    "%qs clause with modifier other than %<iterator%>, "
		    "%<mapper%>, or %<present%>",
		    kind == OMP_CLAUSE_TO ? "to" : "from");
	  parens.skip_until_found_close (parser);
	  প্রত্যাগম list;
	}
    }

  যদি (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  বৃক্ষ nl = c_parser_omp_variable_list (parser, loc, kind, list);
  parens.skip_until_found_close (parser);

  যদি (present)
    প্রতি (বৃক্ষ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  যদি (iterators)
    {
      বৃক্ষ block = বের_করো_scope ();
      যদি (iterators == error_mark_গ্রন্থি)
	iterators = NULL_বৃক্ষ;
      অন্যথা
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  যদি (iterators)
    প্রতি (বৃক্ষ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  যদি (mapper_name)
    {
      বৃক্ষ last_new = NULL_বৃক্ষ;
      প্রতি (বৃক্ষ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	last_new = c;

      বৃক্ষ name = build_omp_clause (প্রবেশ_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_ঠেলো_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (প্রবেশ_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_বের_করো_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_গ্রন্থি;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  প্রত্যাগম nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_uniform (c_parser *parser, বৃক্ষ list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_UNIFORM,
					 list);
      parens.skip_until_found_close (parser);
    }
  প্রত্যাগম list;
}

/* OpenMP 5.1
   full */

স্থির বৃক্ষ
c_parser_omp_clause_full (c_parser *parser, বৃক্ষ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_FULL, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  বৃক্ষ c = build_omp_clause (loc, OMP_CLAUSE_FULL);
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_partial (c_parser *parser, বৃক্ষ list)
{
  বৃক্ষ অঙ্ক = NULL_বৃক্ষ;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      অঙ্ক = c_parser_রাশিমালা_no_commas (parser, রিক্ত).মান;
      parens.skip_until_found_close (parser);

      যদি (অঙ্ক == error_mark_গ্রন্থি)
	প্রত্যাগম list;

      mark_exp_read (অঙ্ক);
      অঙ্ক = c_fully_fold (অঙ্ক, অসত্য, রিক্ত);
      HOST_WIDE_INT n;
      যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (অঙ্ক))
	  || !বৃক্ষ_fits_shwi_p (অঙ্ক)
	  || (n = বৃক্ষ_to_shwi (অঙ্ক)) <= 0
	  || (পূর্ণাঙ্ক) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  প্রত্যাগম list;
	}
    }

  বৃক্ষ c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_রাশিমালা (c) = অঙ্ক;
  OMP_CLAUSE_CHAIN (c) = list;
  প্রত্যাগম c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_novariants (c_parser *parser, বৃক্ষ list)
{
  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
  বৃক্ষ t = convert_lvalue_to_rvalue (loc, রাশিমালা, সত্য, সত্য).মান;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, অসত্য, রিক্ত);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  বৃক্ষ c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_রাশিমালা (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  প্রত্যাগম list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

স্থির বৃক্ষ
c_parser_omp_clause_nocontext (c_parser *parser, বৃক্ষ list)
{
  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
  বৃক্ষ t = convert_lvalue_to_rvalue (loc, রাশিমালা, সত্য, সত্য).মান;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, অসত্য, রিক্ত);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  বৃক্ষ c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_রাশিমালা (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  প্রত্যাগম list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

স্থির বৃক্ষ
c_parser_omp_clause_detach (c_parser *parser, বৃক্ষ list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  যদি (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_found_close (parser);
      প্রত্যাগম list;
    }

  বৃক্ষ t = lookup_name (c_parser_peek_token (parser)->মান);
  যদি (t == NULL_বৃক্ষ)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->মান);
      parens.skip_until_found_close (parser);
      প্রত্যাগম list;
    }
  c_parser_consume_token (parser);

  বৃক্ষ type = TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (t));
  যদি (!INTEGRAL_TYPE_P (type)
      || বৃক্ষ_CODE (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_found_close (parser);
      প্রত্যাগম list;
    }

  বৃক্ষ u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_found_close (parser);
  প্রত্যাগম u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_destroy (c_parser *parser, বৃক্ষ list)
{
  বৃক্ষ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  প্রতি (বৃক্ষ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    বৃক্ষ_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
  প্রত্যাগম nl;
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

স্থির বৃক্ষ
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    প্রত্যাগম error_mark_গ্রন্থি;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  যদি (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    যাবত্ (সত্য)
      {
	str += (বর্ণ) GOMP_INTEROP_IFR_SEPARATOR;
	যদি (c_parser_next_token_is (parser, CPP_STRING))
	  {
	    c_রাশিমালা cval = c_parser_string_literal (parser, অসত্য, অসত্য);
	    যদি (cval.মান == error_mark_গ্রন্থি)
	      প্রত্যাগম error_mark_গ্রন্থি;
	    যদি ((size_t) বৃক্ষ_STRING_LENGTH (cval.মান)
		!= strlen (বৃক্ষ_STRING_POINTER (cval.মান)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = সত্য;
		প্রত্যাগম error_mark_গ্রন্থি;
	      }

	    বর্ণ c = omp_get_fr_id_from_name (বৃক্ষ_STRING_POINTER (cval.মান));
	    যদি (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  বৃক্ষ_STRING_POINTER (cval.মান));
	    str += c;
	  }
	অন্যথা
	  {
	    c_রাশিমালা cval = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	    বৃক্ষ মান = c_fully_fold (cval.মান, অসত্য, রিক্ত);
	    যদি (INTEGRAL_TYPE_P (বৃক্ষ_TYPE (মান))
		&& বৃক্ষ_CODE (মান) != INTEGER_CST)
	      মান = convert_lvalue_to_rvalue (cval.get_start (), cval,
						অসত্য, সত্য).মান;
	    যদি (বৃক্ষ_CODE (মান) != INTEGER_CST
		|| !বৃক্ষ_fits_shwi_p (মান))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		প্রত্যাগম error_mark_গ্রন্থি;
	      }
	    HOST_WIDE_INT n = বৃক্ষ_to_shwi (মান);
	    যদি (n < 1 || n > GOMP_INTEROP_IFR_LAST)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (বর্ণ) n;
	  }
	str += (বর্ণ) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	যদি (c_parser_next_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    অনুবর্ত;
	  }
	যদি (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  প্রত্যাগম error_mark_গ্রন্থি;
	str += '\0';
	বৃক্ষ res = build_string (str.length (), str.data ());
	বৃক্ষ_TYPE (res) = build_array_type_nelts (unsigned_char_type_গ্রন্থি,
						  str.length ());
	প্রত্যাগম res;
      }

  /* New format. */
  std::string str2;
  যাবত্ (সত্য)
    {
      যদি (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	প্রত্যাগম error_mark_গ্রন্থি;
      str += (বর্ণ) GOMP_INTEROP_IFR_SEPARATOR;
      str2.clear ();
      তার্কিক has_fr = অসত্য;
      যাবত্ (সত্য)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  যদি (tok->type != CPP_NAME
	      || (strcmp("fr", IDENTIFIER_POINTER (tok->মান)) != 0
		  && strcmp("attr", IDENTIFIER_POINTER (tok->মান)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      প্রত্যাগম error_mark_গ্রন্থি;
	    }
	  c_parser_consume_token (parser);
	  তার্কিক is_fr = IDENTIFIER_POINTER (tok->মান)[0] == 'f';
	  যদি (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      প্রত্যাগম error_mark_গ্রন্থি;
	    }
	  যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    প্রত্যাগম error_mark_গ্রন্থি;
	  যাবত্ (সত্য)
	    {
	      যদি (c_parser_next_token_is (parser, CPP_STRING))
		{
		  c_রাশিমালা cval = c_parser_string_literal (parser, অসত্য, অসত্য);
		  বৃক্ষ মান = cval.মান;
		  যদি (মান == error_mark_গ্রন্থি)
		    প্রত্যাগম error_mark_গ্রন্থি;
		  যদি ((size_t) বৃক্ষ_STRING_LENGTH (মান)
		      != strlen (বৃক্ষ_STRING_POINTER (মান)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = সত্য;
		      প্রত্যাগম error_mark_গ্রন্থি;
		    }
		  যদি (!is_fr)
		    {
		      যদি (!startswith (বৃক্ষ_STRING_POINTER (মান), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = সত্য;
			  প্রত্যাগম error_mark_গ্রন্থি;
			}
		      যদি (strchr (বৃক্ষ_STRING_POINTER (মান), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = সত্য;
			  প্রত্যাগম error_mark_গ্রন্থি;
			}
		      str2 += বৃক্ষ_STRING_POINTER (মান);
		      str2 += '\0';
		    }
		  অন্যথা
		    {
		      যদি (*বৃক্ষ_STRING_POINTER (মান) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  প্রত্যাগম error_mark_গ্রন্থি;
			}
		      বর্ণ c = omp_get_fr_id_from_name (বৃক্ষ_STRING_POINTER (মান));
		      যদি (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    বৃক্ষ_STRING_POINTER (মান));
		     str += c;
		     has_fr = সত্য;
		    }
		}
	      অন্যথা যদি (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  প্রত্যাগম error_mark_গ্রন্থি;
		}
	      অন্যথা
		{
		  c_রাশিমালা cval = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
		  বৃক্ষ মান = c_fully_fold (cval.মান, অসত্য, রিক্ত);
		  যদি (INTEGRAL_TYPE_P (বৃক্ষ_TYPE (মান))
		      && বৃক্ষ_CODE (মান) != INTEGER_CST)
		    মান = convert_lvalue_to_rvalue (cval.get_start (), cval,
						      অসত্য, সত্য).মান;

		  যদি (বৃক্ষ_CODE (মান) != INTEGER_CST
		      || !বৃক্ষ_fits_shwi_p (মান))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      প্রত্যাগম error_mark_গ্রন্থি;
		    }
		  HOST_WIDE_INT n = বৃক্ষ_to_shwi (মান);
		  যদি (n < 1 || n > GOMP_INTEROP_IFR_LAST)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (বর্ণ) n;
		  has_fr = সত্য;
		}
	      যদি (!is_fr
		  && c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  অনুবর্ত;
		}
	      যদি (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		প্রত্যাগম error_mark_গ্রন্থি;
	      ভঙ্গ;
	    }
	  যদি (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      অনুবর্ত;
	    }
	  যদি (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    ভঙ্গ;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  প্রত্যাগম error_mark_গ্রন্থি;
	}
      str += (বর্ণ) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	ভঙ্গ;
      যদি (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	প্রত্যাগম error_mark_গ্রন্থি;
    }
  c_parser_consume_token (parser);
  str += '\0';
  বৃক্ষ res = build_string (str.length (), str.data ());
  বৃক্ষ_TYPE (res) = build_array_type_nelts (unsigned_char_type_গ্রন্থি,
						  str.length ());
  প্রত্যাগম res;
}

/* OpenMP 5.1
     modifiers of the 'init' clause, used by the 'init' and the
     'append_args' clauses.

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification)

  Returns 'false' if an error has been issued.  */

স্থির তার্কিক
c_parser_omp_clause_init_modifiers (c_parser *parser, তার্কিক *target,
				    তার্কিক *targetsync, বৃক্ষ *prefer_type_বৃক্ষ)
{
  *target = অসত্য;
  *targetsync = অসত্য;
  *prefer_type_বৃক্ষ = NULL_বৃক্ষ;

  কুরু
    {
      c_token *tok = c_parser_peek_token (parser);
      যদি (tok->type != CPP_NAME)
	গচ্ছ fail;
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (tok->মান);
      যদি (strcmp ("targetsync", p) == 0)
	{
	  যদি (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = সত্য;
	  c_parser_consume_token (parser);
	}
      অন্যথা যদি (strcmp ("target", p) == 0)
	{
	  যদি (*target)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *target = সত্য;
	  c_parser_consume_token (parser);
	}
      অন্যথা যদি (strcmp ("prefer_type", p) == 0)
	{
	  যদি (*prefer_type_বৃক্ষ != NULL_বৃক্ষ)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_বৃক্ষ = c_parser_omp_modifier_prefer_type (parser);
	  যদি (*prefer_type_বৃক্ষ == error_mark_গ্রন্থি)
	    প্রত্যাগম অসত্য;
	}
      অন্যথা
	গচ্ছ fail;
      tok = c_parser_peek_token (parser);
      যদি (tok->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  অনুবর্ত;
	}
      /* Unknown token - either done or an error; handle it in the caller.  */
      প্রত্যাগম সত্য;
    }
  যাবত্ (সত্য);

fail:
  c_parser_error (parser,
		  "expected %<prefer_type%>, %<target%>, or %<targetsync%>");
  প্রত্যাগম অসত্য;
}

/* OpenMP 5.1:
   init ( [init-modifier-list : ] variable-list )

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification) */

স্থির বৃক্ষ
c_parser_omp_clause_init (c_parser *parser, বৃক্ষ list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম list;

  তার্কিক target = অসত্য;
  তার্কিক targetsync = অসত্য;
  বৃক্ষ prefer_type_বৃক্ষ = NULL_বৃক্ষ;

  যদি (!c_parser_omp_clause_init_modifiers (parser, &target, &targetsync,
					   &prefer_type_বৃক্ষ)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      যদি (prefer_type_বৃক্ষ != error_mark_গ্রন্থি)
	parens.skip_until_found_close (parser);
      প্রত্যাগম list;
    }

  যদি (!target && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  বৃক্ষ nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					অসত্য);
  parens.skip_until_found_close (parser);

  প্রতি (বৃক্ষ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      বৃক্ষ_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      যদি (target)
	OMP_CLAUSE_INIT_TARGET (c) = 1;
      যদি (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      যদি (prefer_type_বৃক্ষ)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_বৃক্ষ;
    }
  প্রত্যাগম nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_use (c_parser *parser, বৃক্ষ list)
{
  প্রত্যাগম c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

স্থির বৃক্ষ
c_parser_omp_clause_interop (c_parser *parser, বৃক্ষ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  বৃক্ষ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  প্রতি (বৃক্ষ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      বৃক্ষ_USED (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  প্রত্যাগম nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

স্থির বৃক্ষ
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_mask mask,
			   ধ্রুব বর্ণ *where, তার্কিক finish_p = সত্য,
			   তার্কিক target_p = অসত্য)
{
  বৃক্ষ clauses = রিক্ত;
  তার্কিক first = সত্য;

  যাবত্ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      ধ্রুব বর্ণ *c_name;
      বৃক্ষ prev = clauses;

      যদি (!first && c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      বিকল্প (c_kind)
	{
	পক্ষ PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "attach";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copy";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyin";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyout";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "create";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "delete";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, সত্য);
	  c_name = "default";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "detach";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_data_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device_resident";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_GANG,
						c_name, clauses);
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "host";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, অসত্য);
	  c_name = "if";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "link";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "no_create";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_অঙ্ক_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_অঙ্ক_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_অঙ্ক_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_অঙ্ক_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "present";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     অসত্য, clauses);
	  c_name = "reduction";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_SELF:
	  যদি ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  অন্যথা
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "self";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_SEQ,
						 clauses);
	  c_name = "seq";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_TILE:
	  clauses = c_parser_oacc_clause_tile (parser, clauses);
	  c_name = "tile";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_USE_DEVICE:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_VECTOR:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_VECTOR,
						c_name,	clauses);
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_VECTOR_LENGTH:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_VECTOR_LENGTH,
						     clauses);
	  c_name = "vector_length";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  ভঙ্গ;
	পক্ষ PRAGMA_OACC_CLAUSE_WORKER:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_WORKER,
						c_name, clauses);
	  ভঙ্গ;
	স্বভাব:
	  c_parser_error (parser, "expected an OpenACC clause");
	  গচ্ছ saw_error;
	}

      first = অসত্য;

      যদি (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_to_pragma_eol (parser);

  যদি (finish_p)
    প্রত্যাগম c_finish_omp_clauses (clauses, target_p ? C_ORT_ACC_TARGET
						   : C_ORT_ACC);

  প্রত্যাগম clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

স্থির বৃক্ষ
c_parser_omp_all_clauses (c_parser *parser, omp_clause_mask mask,
			  ধ্রুব বর্ণ *where, তার্কিক finish_p = সত্য,
			  পূর্ণাঙ্ক nested = 0)
{
  বৃক্ষ clauses = রিক্ত;
  তার্কিক first = সত্য;

  যাবত্ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      ধ্রুব বর্ণ *c_name;
      বৃক্ষ prev = clauses;

      যদি (nested && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	ভঙ্গ;

      যদি (!first || nested != 2)
	{
	  যদি (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  অন্যথা যদি (nested == 2)
	    error_at (c_parser_peek_token (parser)->location,
		      "clauses in %<simd%> trait should be separated "
		      "by %<,%>");
	}

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      বিকল্প (c_kind)
	{
	পক্ষ PRAGMA_OMP_CLAUSE_BIND:
	  clauses = c_parser_omp_clause_bind (parser, clauses);
	  c_name = "bind";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, অসত্য);
	  c_name = "default";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_DETACH:
	  clauses = c_parser_omp_clause_detach (parser, clauses);
	  c_name = "detach";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_FILTER:
	  clauses = c_parser_omp_clause_filter (parser, clauses);
	  c_name = "filter";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_FINAL:
	  clauses = c_parser_omp_clause_final (parser, clauses);
	  c_name = "final";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_GRAINSIZE:
	  clauses = c_parser_omp_clause_grainsize (parser, clauses);
	  c_name = "grainsize";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_HINT:
	  clauses = c_parser_omp_clause_hint (parser, clauses);
	  c_name = "hint";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_DEFAULTMAP:
	  clauses = c_parser_omp_clause_defaultmap (parser, clauses);
	  c_name = "defaultmap";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, সত্য);
	  c_name = "if";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_IN_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_IN_REDUCTION,
					     সত্য, clauses);
	  c_name = "in_reduction";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_INDIRECT:
	  clauses = c_parser_omp_clause_indirect (parser, clauses);
	  c_name = "indirect";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_MERGEABLE:
	  clauses = c_parser_omp_clause_mergeable (parser, clauses);
	  c_name = "mergeable";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_অঙ্ক_TASKS:
	  clauses = c_parser_omp_clause_অঙ্ক_tasks (parser, clauses);
	  c_name = "num_tasks";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_অঙ্ক_THREADS:
	  clauses = c_parser_omp_clause_অঙ্ক_threads (parser, clauses);
	  c_name = "num_threads";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_ORDER:
	  clauses = c_parser_omp_clause_order (parser, clauses);
	  c_name = "order";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_PRIORITY:
	  clauses = c_parser_omp_clause_priority (parser, clauses);
	  c_name = "priority";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     সত্য, clauses);
	  c_name = "reduction";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_SCHEDULE:
	  clauses = c_parser_omp_clause_schedule (parser, clauses);
	  c_name = "schedule";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     সত্য, clauses);
	  c_name = "task_reduction";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_UNTIED:
	  clauses = c_parser_omp_clause_untied (parser, clauses);
	  c_name = "untied";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_INBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_INBRANCH,
						clauses);
	  c_name = "inbranch";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_NONTEMPORAL:
	  clauses = c_parser_omp_clause_nontemporal (parser, clauses);
	  c_name = "nontemporal";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_NOTINBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_NOTINBRANCH,
						clauses);
	  c_name = "notinbranch";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_PARALLEL:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_PARALLEL,
					      clauses);
	  c_name = "parallel";
	  যদি (!first)
	    {
	     clause_not_first:
	      error_at (here, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = prev;
	    }
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  যদি (!first)
	    গচ্ছ clause_not_first;
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  যদি (!first)
	    গচ্ছ clause_not_first;
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  যদি (!first)
	    গচ্ছ clause_not_first;
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_LINK:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LINK, clauses);
	  c_name = "link";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_LOCAL:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LOCAL, clauses);
	  c_name = "local";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_TO:
	  যদি ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (here);
	      richloc.add_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      বৃক্ষ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      প্রতি (বৃক্ষ c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_TO (c) = 1;
	      clauses = nl;
	    }
	  অন্যথা
	    clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_TO,
						   clauses);
	  c_name = "to";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_UNIFORM:
	  clauses = c_parser_omp_clause_uniform (parser, clauses);
	  c_name = "uniform";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_অঙ্ক_TEAMS:
	  clauses = c_parser_omp_clause_অঙ্ক_teams (parser, clauses);
	  c_name = "num_teams";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_THREAD_LIMIT:
	  clauses = c_parser_omp_clause_thread_limit (parser, clauses);
	  c_name = "thread_limit";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_ALIGNED:
	  clauses = c_parser_omp_clause_aligned (parser, clauses);
	  c_name = "aligned";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_ALLOCATE:
	  clauses = c_parser_omp_clause_allocate (parser, clauses);
	  c_name = "allocate";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_LINEAR:
	  clauses = c_parser_omp_clause_linear (parser, clauses);
	  c_name = "linear";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_USES_ALLOCATORS:
	  clauses = c_parser_omp_clause_uses_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, here);
	  c_name = "depend";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_DOACROSS:
	  clauses = c_parser_omp_clause_doacross (parser, clauses);
	  c_name = "doacross";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_DESTROY:
	  clauses = c_parser_omp_clause_destroy (parser, clauses);
	  c_name = "destroy";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE:
	  clauses = c_parser_omp_clause_dyn_groupprivate (parser, clauses);
	  c_name = "dyn_groupprivate";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_INIT:
	  clauses = c_parser_omp_clause_init (parser, clauses);
	  c_name = "init";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_USE:
	  clauses = c_parser_omp_clause_use (parser, clauses);
	  c_name = "use";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_INTEROP:
	  clauses = c_parser_omp_clause_interop (parser, clauses);
	  c_name = "interop";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_MAP:
	  clauses = c_parser_omp_clause_map (parser, clauses, অসত্য);
	  c_name = "map";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device_ptr";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_use_device_addr (parser, clauses);
	  c_name = "use_device_addr";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_has_device_addr (parser, clauses);
	  c_name = "has_device_addr";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR:
	  clauses = c_parser_omp_clause_is_device_ptr (parser, clauses);
	  c_name = "is_device_ptr";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_DEVICE:
	  clauses = c_parser_omp_clause_device (parser, clauses);
	  c_name = "device";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_DIST_SCHEDULE:
	  clauses = c_parser_omp_clause_dist_schedule (parser, clauses);
	  c_name = "dist_schedule";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_PROC_BIND:
	  clauses = c_parser_omp_clause_proc_bind (parser, clauses);
	  c_name = "proc_bind";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_DEVICE_TYPE:
	  clauses = c_parser_omp_clause_device_type (parser, clauses);
	  c_name = "device_type";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_SAFELEN:
	  clauses = c_parser_omp_clause_safelen (parser, clauses);
	  c_name = "safelen";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_SIMDLEN:
	  clauses = c_parser_omp_clause_simdlen (parser, clauses);
	  c_name = "simdlen";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_NOGROUP:
	  clauses = c_parser_omp_clause_nogroup (parser, clauses);
	  c_name = "nogroup";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_THREADS:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_THREADS,
					       clauses);
	  c_name = "threads";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_SIMD:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_SIMD,
					       clauses);
	  c_name = "simd";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_ENTER:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					    clauses);
	  c_name = "enter";
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_FULL:
	  c_name = "full";
	  clauses = c_parser_omp_clause_full (parser, clauses);
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_PARTIAL:
	  c_name = "partial";
	  clauses = c_parser_omp_clause_partial (parser, clauses);
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_NOVARIANTS:
	  c_name = "novariants";
	  clauses = c_parser_omp_clause_novariants (parser, clauses);
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_CLAUSE_NOCONTEXT:
	  c_name = "nocontext";
	  clauses = c_parser_omp_clause_nocontext (parser, clauses);
	  ভঙ্গ;
	স্বভাব:
	  c_parser_error (parser, "expected an OpenMP clause");
	  গচ্ছ saw_error;
	}

      first = অসত্য;

      যদি (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  যদি (!nested)
    c_parser_skip_to_pragma_eol (parser);

  যদি (finish_p)
    {
      যদি ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_UNIFORM)) != 0)
	প্রত্যাগম c_finish_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      যদি ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	প্রত্যাগম c_finish_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      প্রত্যাগম c_finish_omp_clauses (clauses, C_ORT_OMP);
    }

  প্রত্যাগম clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

স্থির বৃক্ষ
c_parser_omp_structured_block (c_parser *parser, তার্কিক *if_p)
{
  বৃক্ষ stmt = ঠেলো_stmt_list ();
  parser->omp_attrs_forbidden_p = সত্য;
  c_parser_statement (parser, if_p);
  প্রত্যাগম বের_করো_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

স্থির বৃক্ষ
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  বৃক্ষ stmt, clauses = NULL_বৃক্ষ;
  তার্কিক readonly = অসত্য;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      যদি (token->type == CPP_NAME
	  && !strcmp (IDENTIFIER_POINTER (token->মান), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = সত্য;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_বৃক্ষ);
      parens.skip_until_found_close (parser);
    }

  যদি (readonly)
    প্রতি (বৃক্ষ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_to_pragma_eol (parser);

  stmt = make_গ্রন্থি (OACC_CACHE);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  SET_রাশিমালা_LOCATION (stmt, loc);
  add_stmt (stmt);

  প্রত্যাগম stmt;
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

স্থির বৃক্ষ
c_parser_oacc_data (location_t loc, c_parser *parser, তার্কিক *if_p)
{
  বৃক্ষ stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_DATA_CLAUSE_MASK,
				       "#pragma acc data");

  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  stmt = c_finish_oacc_data (loc, clauses, block);

  প্রত্যাগম stmt;
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

স্থির শূন্য
c_parser_oacc_declare (c_parser *parser)
{
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  বৃক্ষ clauses, stmt, t, decl;

  তার্কিক error = অসত্য;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_MASK,
				       "#pragma acc declare");
  যদি (!clauses)
    {
      error_at (pragma_loc,
		"no valid clauses specified in %<#pragma acc declare%>");
      প্রত্যাগম;
    }

  প্রতি (t = clauses; t; t = OMP_CLAUSE_CHAIN (t))
    {
      location_t loc = OMP_CLAUSE_LOCATION (t);
      decl = OMP_CLAUSE_DECL (t);
      যদি (!DECL_P (decl))
	{
	  error_at (loc, "array section in %<#pragma acc declare%>");
	  error = সত্য;
	  অনুবর্ত;
	}

      বিকল্প (OMP_CLAUSE_MAP_KIND (t))
	{
	পক্ষ GOMP_MAP_FIRSTPRIVATE_POINTER:
	পক্ষ GOMP_MAP_ALLOC:
	পক্ষ GOMP_MAP_TO:
	পক্ষ GOMP_MAP_FORCE_DEVICEPTR:
	পক্ষ GOMP_MAP_DEVICE_RESIDENT:
	  ভঙ্গ;

	পক্ষ GOMP_MAP_LINK:
	  যদি (!global_bindings_p ()
	      && (বৃক্ষ_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = সত্য;
	      অনুবর্ত;
	    }
	  ভঙ্গ;

	স্বভাব:
	  যদি (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = সত্য;
	      অনুবর্ত;
	    }
	  যদি (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = সত্য;
	      অনুবর্ত;
	    }
	  অন্যথা যদি (বৃক্ষ_PUBLIC (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = সত্য;
	      অনুবর্ত;
	    }
	  ভঙ্গ;
	}

      যদি (!c_check_in_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = সত্য;
	  অনুবর্ত;
	}

      যদি (lookup_attribute ("omp declare target", DECL_ATTRIBUTES (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_ATTRIBUTES (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = সত্য;
	  অনুবর্ত;
	}

      যদি (!error)
	{
	  বৃক্ষ id;

	  যদি (OMP_CLAUSE_MAP_KIND (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  অন্যথা
	    id = get_identifier ("omp declare target");

	  DECL_ATTRIBUTES (decl)
			   = বৃক্ষ_cons (id, NULL_বৃক্ষ, DECL_ATTRIBUTES (decl));

	  যদি (global_bindings_p ())
	    {
	      symtab_গ্রন্থি *গ্রন্থি = symtab_গ্রন্থি::get (decl);
	      যদি (গ্রন্থি != রিক্ত)
		{
		  গ্রন্থি->offloadable = 1;
		  যদি (ENABLE_OFFLOADING)
		    {
		      g->have_offload = সত্য;
		      যদি (is_a <varpool_গ্রন্থি *> (গ্রন্থি))
			vec_safe_ঠেলো (offload_vars, decl);
		    }
		}
	    }
	}
    }

  যদি (error || global_bindings_p ())
    প্রত্যাগম;

  stmt = make_গ্রন্থি (OACC_DECLARE);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  SET_রাশিমালা_LOCATION (stmt, pragma_loc);

  add_stmt (stmt);

  প্রত্যাগম;
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

স্থির শূন্য
c_parser_oacc_enter_exit_data (c_parser *parser, তার্কিক enter)
{
  location_t loc = c_parser_peek_token (parser)->location;
  বৃক্ষ clauses, stmt;
  ধ্রুব বর্ণ *p = "";

  c_parser_consume_pragma (parser);

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      c_parser_consume_token (parser);
    }

  যদি (strcmp (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = সত্য;
      c_parser_skip_to_pragma_eol (parser);
      প্রত্যাগম;
    }

  যদি (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_DATA_CLAUSE_MASK,
					 "#pragma acc enter data");
  অন্যথা
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_DATA_CLAUSE_MASK,
					 "#pragma acc exit data");

  যদি (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_বৃক্ষ)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      প্রত্যাগম;
    }

  stmt = enter ? make_গ্রন্থি (OACC_ENTER_DATA) : make_গ্রন্থি (OACC_EXIT_DATA);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  SET_রাশিমালা_LOCATION (stmt, loc);
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

স্থির বৃক্ষ
c_parser_oacc_host_data (location_t loc, c_parser *parser, তার্কিক *if_p)
{
  বৃক্ষ stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_DATA_CLAUSE_MASK,
				       "#pragma acc host_data", অসত্য);
  যদি (!omp_find_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      প্রত্যাগম error_mark_গ্রন্থি;
    }
  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  stmt = c_finish_oacc_host_data (loc, clauses, block);
  প্রত্যাগম stmt;
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
স্থির বৃক্ষ
c_parser_oacc_loop (location_t loc, c_parser *parser, বর্ণ *p_name,
		    omp_clause_mask mask, বৃক্ষ *cclauses, তার্কিক *if_p)
{
  তার্কিক is_parallel = ((mask >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  strcat (p_name, " loop");
  mask |= OACC_LOOP_CLAUSE_MASK;

  বৃক্ষ clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/cclauses == রিক্ত,
					    /*target=*/is_parallel);
  যদি (cclauses)
    {
      clauses = c_oacc_split_loop_clauses (clauses, cclauses, is_parallel);
      যদি (*cclauses)
	*cclauses = c_finish_omp_clauses (*cclauses, C_ORT_ACC_TARGET);
      যদি (clauses)
	clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
    }

  বৃক্ষ block = c_begin_compound_stmt (সত্য);
  বৃক্ষ stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, রিক্ত,
				     if_p);
  block = c_end_compound_stmt (loc, block, সত্য);
  add_stmt (block);

  প্রত্যাগম stmt;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_অঙ্ক_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_অঙ্ক_WORKERS)		\
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_অঙ্ক_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_অঙ্ক_WORKERS)		\
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

স্থির বৃক্ষ
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       গণনা pragma_kind p_kind, বর্ণ *p_name, তার্কিক *if_p)
{
  omp_clause_mask mask;
  গণনা বৃক্ষ_code code;
  বিকল্প (p_kind)
    {
    পক্ষ PRAGMA_OACC_KERNELS:
      strcat (p_name, " kernels");
      mask = OACC_KERNELS_CLAUSE_MASK;
      code = OACC_KERNELS;
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_PARALLEL:
      strcat (p_name, " parallel");
      mask = OACC_PARALLEL_CLAUSE_MASK;
      code = OACC_PARALLEL;
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_SERIAL:
      strcat (p_name, " serial");
      mask = OACC_SERIAL_CLAUSE_MASK;
      code = OACC_SERIAL;
      ভঙ্গ;
    স্বভাব:
      gcc_unreachable ();
    }

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  বৃক্ষ block = c_begin_omp_parallel ();
	  বৃক্ষ clauses;
	  c_parser_oacc_loop (loc, parser, p_name, mask, &clauses, if_p);
	  প্রত্যাগম c_finish_omp_construct (loc, code, block, clauses);
	}
    }

  বৃক্ষ clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/সত্য,
					    /*target=*/সত্য);

  বৃক্ষ block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  প্রত্যাগম c_finish_omp_construct (loc, code, block, clauses);
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

স্থির শূন্য
c_parser_oacc_routine (c_parser *parser, গণনা pragma_context context)
{
  gcc_checking_assert (context == pragma_external);

  oacc_routine_data data;
  data.error_seen = অসত্য;
  data.fndecl_seen = অসত্য;
  data.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      বৃক্ষ decl = NULL_বৃক্ষ;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      যদি (name_token->type == CPP_NAME
	  && (name_token->id_kind == C_ID_ID
	      || name_token->id_kind == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->মান);
	  যদি (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->মান);
	  c_parser_consume_token (parser);
	}
      অন্যথা
	c_parser_error (parser, "expected function name");

      যদি (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_to_pragma_eol (parser, অসত্য);
	  প্রত্যাগম;
	}

      data.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_MASK,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      data.clauses = nreverse (data.clauses);

      যদি (বৃক্ষ_CODE (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  প্রত্যাগম;
	}

      c_finish_oacc_routine (&data, decl, অসত্য);
    }
  অন্যথা /* No optional '( name )'.  */
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
      যদি (c_parser_next_token_is (parser, CPP_PRAGMA)
	  || c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (data.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  প্রত্যাগম;
	}

      /* We only have to consider the pragma_external case here.  */
      যদি (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  পূর্ণাঙ্ক ext = disable_extension_diagnostics ();
	  কুরু
	    c_parser_consume_token (parser);
	  যাবত্ (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, সত্য, সত্য, সত্য, অসত্য, সত্য,
					 অসত্য, রিক্ত, রিক্ত, অসত্য, রিক্ত, &data);
	  restore_extension_diagnostics (ext);
	}
      অন্যথা
	c_parser_declaration_or_fndef (parser, সত্য, সত্য, সত্য, অসত্য, সত্য,
				       অসত্য, রিক্ত, রিক্ত, অসত্য, রিক্ত, &data);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

স্থির শূন্য
c_finish_oacc_routine (সংরচনা oacc_routine_data *data, বৃক্ষ fndecl,
		       তার্কিক is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  যদি (data->error_seen
      || fndecl == error_mark_গ্রন্থি)
    প্রত্যাগম;

  যদি (data->fndecl_seen)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      data->error_seen = সত্য;
      প্রত্যাগম;
    }
  যদি (fndecl == NULL_বৃক্ষ || বৃক্ষ_CODE (fndecl) != FUNCTION_DECL)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      data->error_seen = সত্য;
      প্রত্যাগম;
    }

  পূর্ণাঙ্ক compatible
    = oacc_verify_routine_clauses (fndecl, &data->clauses, data->loc,
				   "#pragma acc routine");
  যদি (compatible < 0)
    {
      data->error_seen = সত্য;
      প্রত্যাগম;
    }
  যদি (compatible > 0)
    {
    }
  অন্যথা
    {
      যদি (বৃক্ষ_USED (fndecl) || (!is_defn && DECL_SAVED_বৃক্ষ (fndecl)))
	{
	  error_at (data->loc,
		    বৃক্ষ_USED (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  data->error_seen = সত্য;
	  প্রত্যাগম;
	}

      /* Set the routine's level of parallelism.  */
      বৃক্ষ dims = oacc_build_routine_dims (data->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_ATTRIBUTES (fndecl)
	= বৃক্ষ_cons (get_identifier ("omp declare target"),
		     data->clauses, DECL_ATTRIBUTES (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  data->fndecl_seen = সত্য;
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

স্থির শূন্য
c_parser_oacc_update (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  বৃক্ষ clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_MASK,
					    "#pragma acc update");
  যদি (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_বৃক্ষ)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      প্রত্যাগম;
    }

  যদি (parser->error)
    প্রত্যাগম;

  বৃক্ষ stmt = make_গ্রন্থি (OACC_UPDATE);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  SET_রাশিমালা_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#define OACC_WAIT_CLAUSE_MASK						\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF) )

স্থির বৃক্ষ
c_parser_oacc_wait (location_t loc, c_parser *parser, বর্ণ *p_name)
{
  বৃক্ষ clauses, list = NULL_বৃক্ষ, stmt = NULL_বৃক্ষ;

  যদি (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  strcpy (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_MASK, p_name);
  stmt = c_finish_oacc_wait (loc, list, clauses);
  add_stmt (stmt);

  প্রত্যাগম stmt;
}

সংরচনা c_omp_loc_বৃক্ষ
{
  location_t loc;
  বৃক্ষ var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
স্থির বৃক্ষ
c_check_omp_allocate_allocator_r (বৃক্ষ *tp, পূর্ণাঙ্ক *, শূন্য *data)
{
  বৃক্ষ var = ((সংরচনা c_omp_loc_বৃক্ষ *) data)->var;
  location_t loc = ((সংরচনা c_omp_loc_বৃক্ষ *) data)->loc;
  যদি (বৃক্ষ_CODE (*tp) == VAR_DECL && c_check_in_current_scope (*tp))
    {
      যদি (linemap_location_before_p (সারি_table, DECL_SOURCE_LOCATION (var),
				     DECL_SOURCE_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_SOURCE_LOCATION (*tp), "declared here");
	  inform (DECL_SOURCE_LOCATION (var),
		  "to be allocated variable declared here");
	  প্রত্যাগম *tp;
	}
      অন্যথা
	{
	  gcc_assert (cur_stmt_list
		      && বৃক্ষ_CODE (cur_stmt_list) == STATEMENT_LIST);

	  বৃক্ষ_stmt_iterator l = tsi_last (cur_stmt_list);
	  যাবত্ (!tsi_end_p (l))
	    {
	      যদি (linemap_location_before_p (সারি_table, রাশিমালা_LOCATION (*l),
					     DECL_SOURCE_LOCATION (var)))
		  ভঙ্গ;
	      যদি (বৃক্ষ_CODE (*l) == MODIFY_রাশিমালা
		  && বৃক্ষ_OPERAND (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (রাশিমালা_LOCATION (*l), "modified here");
		  inform (DECL_SOURCE_LOCATION (var),
			  "to be allocated variable declared here");
		  প্রত্যাগম *tp;
		}
	      --l;
	    }
	}
    }
  প্রত্যাগম NULL_বৃক্ষ;
}

/* OpenMP 5.x:
   # pragma omp allocate (list)  clauses

   OpenMP 5.0 clause:
   allocator (omp_allocator_handle_t expression)

   OpenMP 5.1 additional clause:
   align (constant-expression)]  */

স্থির শূন্য
c_parser_omp_allocate (c_parser *parser)
{
  বৃক্ষ alignment = NULL_বৃক্ষ;
  বৃক্ষ allocator = NULL_বৃক্ষ;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  বৃক্ষ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_বৃক্ষ);
  কুরু
    {
      যদি (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      যদি (!c_parser_next_token_is (parser, CPP_NAME))
	ভঙ্গ;
      matching_parens parens;
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      c_parser_consume_token (parser);
      location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
      যদি (strcmp ("align", p) != 0 && strcmp ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  ভঙ্গ;
	}
      যদি (!parens.require_open (parser))
	ভঙ্গ;

      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, অসত্য, সত্য);
      রাশিমালা_loc = c_parser_peek_token (parser)->location;
      যদি (রাশিমালা.মান == error_mark_গ্রন্থি)
	;
      অন্যথা যদি (p[2] == 'i' && alignment)
	{
	  error_at (রাশিমালা_loc, "too many %qs clauses", "align");
	  ভঙ্গ;
	}
      অন্যথা যদি (p[2] == 'i')
	{
	  alignment = c_fully_fold (রাশিমালা.মান, অসত্য, রিক্ত);
	  যদি (বৃক্ষ_CODE (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (বৃক্ষ_TYPE (alignment))
	      || বৃক্ষ_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (রাশিমালা_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_বৃক্ষ;
	    }
	}
      অন্যথা যদি (allocator)
	{
	  error_at (রাশিমালা_loc, "too many %qs clauses", "allocator");
	  ভঙ্গ;
	}
      অন্যথা
	{
	  allocator = c_fully_fold (রাশিমালা.মান, অসত্য, রিক্ত);
	  allocator_loc = রাশিমালা_loc;
	  বৃক্ষ orig_type
	    = রাশিমালা.original_type ? রাশিমালা.original_type : বৃক্ষ_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (allocator))
	      || বৃক্ষ_CODE (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (রাশিমালা_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			বৃক্ষ_TYPE (allocator));
	      allocator = NULL_বৃক্ষ;
	    }
	}
      parens.skip_until_found_close (parser);
    } যাবত্ (সত্য);
  c_parser_skip_to_pragma_eol (parser);

  c_mark_decl_jump_unsafe_in_current_scope ();
  প্রতি (বৃক্ষ c = nl; c != NULL_বৃক্ষ; c = OMP_CLAUSE_CHAIN (c))
    {
      বৃক্ষ var = OMP_CLAUSE_DECL (c);
      যদি (বৃক্ষ_CODE (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  অনুবর্ত;
	}
      যদি (!parser->in_omp_decl_attribute && !c_check_in_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_SOURCE_LOCATION (var), "declared here");
	  অনুবর্ত;
	}
      যদি (lookup_attribute ("omp allocate", DECL_ATTRIBUTES (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  অনুবর্ত;
	}
      যদি (বৃক্ষ_STATIC (var))
	{
	  যদি (allocator == NULL_বৃক্ষ && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      অনুবর্ত;
	    }
	  অন্যথা যদি (allocator
		   && (wi::to_widest (allocator) < 1
		       || wi::to_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::to_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::to_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  অন্যথা যদি (allocator
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
      যদি (allocator)
	{
	  সংরচনা c_omp_loc_বৃক্ষ data
	    = {রাশিমালা_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_বৃক্ষ (&allocator, c_check_omp_allocate_allocator_r, &data, রিক্ত);
	}
      DECL_ATTRIBUTES (var) = বৃক্ষ_cons (get_identifier ("omp allocate"),
					 build_বৃক্ষ_list (allocator, alignment),
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

স্থির শূন্য
c_parser_omp_atomic (location_t loc, c_parser *parser, তার্কিক openacc)
{
  বৃক্ষ lhs = NULL_বৃক্ষ, rhs = NULL_বৃক্ষ, v = NULL_বৃক্ষ, r = NULL_বৃক্ষ;
  বৃক্ষ lhs1 = NULL_বৃক্ষ, rhs1 = NULL_বৃক্ষ;
  বৃক্ষ stmt, orig_lhs, unfolded_lhs = NULL_বৃক্ষ, unfolded_lhs1 = NULL_বৃক্ষ;
  গণনা বৃক্ষ_code code = ERROR_MARK, opcode = NOP_রাশিমালা;
  গণনা omp_memory_order memory_order = OMP_MEMORY_ORDER_UNSPECIFIED;
  সংরচনা c_রাশিমালা রাশিমালা;
  location_t eloc;
  তার্কিক structured_block = অসত্য;
  তার্কিক swapped = অসত্য;
  তার্কিক non_lvalue_p;
  বৃক্ষ clauses = NULL_বৃক্ষ;
  তার্কিক capture = অসত্য;
  তার্কিক compare = অসত্য;
  তার্কিক weak = অসত্য;
  গণনা omp_memory_order fail = OMP_MEMORY_ORDER_UNSPECIFIED;
  তার্কিক no_semicolon = অসত্য;
  তার্কিক extra_scope = অসত্য;

  যাবত্ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      যদি (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      যদি (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ধ্রুব বর্ণ *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  গণনা বৃক্ষ_code new_code = ERROR_MARK;
	  গণনা omp_memory_order new_memory_order
	    = OMP_MEMORY_ORDER_UNSPECIFIED;
	  তার্কিক new_capture = অসত্য;
	  তার্কিক new_compare = অসত্য;
	  তার্কিক new_weak = অসত্য;
	  গণনা omp_memory_order new_fail = OMP_MEMORY_ORDER_UNSPECIFIED;

	  যদি (!strcmp (p, "read"))
	    new_code = OMP_ATOMIC_READ;
	  অন্যথা যদি (!strcmp (p, "write"))
	    new_code = NOP_রাশিমালা;
	  অন্যথা যদি (!strcmp (p, "update"))
	    new_code = OMP_ATOMIC;
	  অন্যথা যদি (openacc && !strcmp (p, "capture"))
	    new_code = OMP_ATOMIC_CAPTURE_NEW;
	  অন্যথা যদি (openacc)
	    {
	      p = রিক্ত;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  অন্যথা যদি (!strcmp (p, "capture"))
	    new_capture = সত্য;
	  অন্যথা যদি (!strcmp (p, "compare"))
	    new_compare = সত্য;
	  অন্যথা যদি (!strcmp (p, "weak"))
	    new_weak = সত্য;
	  অন্যথা যদি (!strcmp (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      যদি (!parens.require_open (parser))
		অনুবর্ত;

	      যদি (c_parser_next_token_is (parser, CPP_NAME))
		{
		  ধ্রুব বর্ণ *q
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);

		  যদি (!strcmp (q, "seq_cst"))
		    new_fail = OMP_MEMORY_ORDER_SEQ_CST;
		  অন্যথা যদি (!strcmp (q, "acquire"))
		    new_fail = OMP_MEMORY_ORDER_ACQUIRE;
		  অন্যথা যদি (!strcmp (q, "relaxed"))
		    new_fail = OMP_MEMORY_ORDER_RELAXED;
		}

	      যদি (new_fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  যদি (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  অন্যথা
		    fail = new_fail;
		}
	      অন্যথা
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_found_close (parser);
	      অনুবর্ত;
	    }
	  অন্যথা যদি (!strcmp (p, "seq_cst"))
	    new_memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  অন্যথা যদি (!strcmp (p, "acq_rel"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	  অন্যথা যদি (!strcmp (p, "release"))
	    new_memory_order = OMP_MEMORY_ORDER_RELEASE;
	  অন্যথা যদি (!strcmp (p, "acquire"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  অন্যথা যদি (!strcmp (p, "relaxed"))
	    new_memory_order = OMP_MEMORY_ORDER_RELAXED;
	  অন্যথা যদি (!strcmp (p, "hint"))
	    {
	      c_parser_consume_token (parser);
	      clauses = c_parser_omp_clause_hint (parser, clauses);
	      অনুবর্ত;
	    }
	  অন্যথা
	    {
	      p = রিক্ত;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "%<capture%>, %<compare%>, %<weak%>, %<fail%>, "
			      "%<seq_cst%>, %<acq_rel%>, %<release%>, "
			      "%<relaxed%> or %<hint%> clause");
	    }
	  যদি (p)
	    {
	      যদি (new_code != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  যদি (openacc
		      && code == OMP_ATOMIC
		      && new_code == OMP_ATOMIC_CAPTURE_NEW)
		    code = new_code;
		  অন্যথা যদি (code != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  অন্যথা
		    code = new_code;
		}
	      অন্যথা যদি (new_memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  যদি (memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  অন্যথা
		    memory_order = new_memory_order;
		}
	      অন্যথা যদি (new_capture)
		{
		  যদি (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  অন্যথা
		    capture = সত্য;
		}
	      অন্যথা যদি (new_compare)
		{
		  যদি (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  অন্যথা
		    compare = সত্য;
		}
	      অন্যথা যদি (new_weak)
		{
		  যদি (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  অন্যথা
		    weak = সত্য;
		}
	      c_parser_consume_token (parser);
	      অনুবর্ত;
	    }
	}
      ভঙ্গ;
    }
  c_parser_skip_to_pragma_eol (parser);

  যদি (code == ERROR_MARK)
    code = OMP_ATOMIC;
  যদি (capture)
    {
      যদি (code != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      অন্যথা
	code = OMP_ATOMIC_CAPTURE_NEW;
    }
  যদি (compare && code != OMP_ATOMIC && code != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = অসত্য;
    }
  যদি (fail != OMP_MEMORY_ORDER_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      fail = OMP_MEMORY_ORDER_UNSPECIFIED;
    }
  যদি (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = অসত্য;
    }
  যদি (openacc)
    memory_order = OMP_MEMORY_ORDER_RELAXED;
  অন্যথা যদি (memory_order == OMP_MEMORY_ORDER_UNSPECIFIED)
    {
      omp_requires_mask
	= (গণনা omp_requires) (omp_requires_mask
			       | OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED);
      বিকল্প ((গণনা omp_memory_order)
	      (omp_requires_mask & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER))
	{
	পক্ষ OMP_MEMORY_ORDER_UNSPECIFIED:
	পক্ষ OMP_MEMORY_ORDER_RELAXED:
	  memory_order = OMP_MEMORY_ORDER_RELAXED;
	  ভঙ্গ;
	পক্ষ OMP_MEMORY_ORDER_SEQ_CST:
	  memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  ভঙ্গ;
	পক্ষ OMP_MEMORY_ORDER_ACQUIRE:
	  যদি (code == NOP_রাশিমালা)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  অন্যথা
	    memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  ভঙ্গ;
	পক্ষ OMP_MEMORY_ORDER_RELEASE:
	  যদি (code == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  অন্যথা
	    memory_order = OMP_MEMORY_ORDER_RELEASE;
	  ভঙ্গ;
	পক্ষ OMP_MEMORY_ORDER_ACQ_REL:
	  বিকল্প (code)
	    {
	    পক্ষ OMP_ATOMIC_READ:
	      memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	      ভঙ্গ;
	    পক্ষ NOP_রাশিমালা: /* atomic write */
	      memory_order = OMP_MEMORY_ORDER_RELEASE;
	      ভঙ্গ;
	    স্বভাব:
	      memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	      ভঙ্গ;
	    }
	  ভঙ্গ;
	স্বভাব:
	  gcc_unreachable ();
	}
    }
  অন্যথা
    বিকল্প (code)
      {
      পক্ষ OMP_ATOMIC_READ:
	যদি (memory_order == OMP_MEMORY_ORDER_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	অন্যথা যদি (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	ভঙ্গ;
      পক্ষ NOP_রাশিমালা: /* atomic write */
	যদি (memory_order == OMP_MEMORY_ORDER_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	অন্যথা যদি (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_RELEASE;
	ভঙ্গ;
      স্বভাব:
	ভঙ্গ;
      }
  যদি (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
    memory_order
      = (গণনা omp_memory_order) (memory_order
				 | (fail << OMP_FAIL_MEMORY_ORDER_SHIFT));

  বিকল্প (code)
    {
    পক্ষ OMP_ATOMIC_READ:
    পক্ষ NOP_রাশিমালা: /* atomic write */
      v = c_parser_cast_expression (parser, রিক্ত).মান;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, অসত্য, রিক্ত, সত্য);
      যদি (v == error_mark_গ্রন্থি)
	গচ্ছ saw_error;
      যদি (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      যদি (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	গচ্ছ saw_error;
      যদি (code == NOP_রাশিমালা)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  রাশিমালা = c_parser_expression (parser);
	  রাশিমালা = default_function_array_read_conversion (eloc, রাশিমালা);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  code = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_বৃক্ষ;
	  rhs = c_fully_fold (রাশিমালা.মান, অসত্য, রিক্ত);
	  যদি (rhs == error_mark_গ্রন্থি)
	    গচ্ছ saw_error;
	}
      অন্যথা
	{
	  lhs = c_parser_cast_expression (parser, রিক্ত).মান;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, অসত্য, রিক্ত, সত্য);
	  যদি (lhs == error_mark_গ্রন্থি)
	    গচ্ছ saw_error;
	  যদি (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      গচ্ছ done;
    পক্ষ OMP_ATOMIC_CAPTURE_NEW:
      যদি (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_block = সত্য;
	}
      অন্যথা যদি (compare
	       && c_parser_next_token_is_keyword (parser, RID_IF))
	ভঙ্গ;
      অন্যথা
	{
	  v = c_parser_cast_expression (parser, রিক্ত).মান;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, অসত্য, রিক্ত, সত্য);
	  যদি (v == error_mark_গ্রন্থি)
	    গচ্ছ saw_error;
	  যদি (non_lvalue_p)
	    v = non_lvalue (v);
	  যদি (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    গচ্ছ saw_error;
	  যদি (compare && c_parser_next_token_is_keyword (parser, RID_IF))
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "expected expression");
	      গচ্ছ saw_error;
	    }
	}
      ভঙ্গ;
    স্বভাব:
      ভঙ্গ;
    }

  /* For structured_block case we don't know yet whether
     old or new x should be captured.  */
restart:
  যদি (compare && c_parser_next_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      যদি (!parens.require_open (parser))
	গচ্ছ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_রাশিমালা cmp_রাশিমালা;
      যদি (r)
	{
	  cmp_রাশিমালা = c_parser_cast_expression (parser, রিক্ত);
	  cmp_রাশিমালা = default_function_array_conversion (eloc, cmp_রাশিমালা);
	}
      অন্যথা
	cmp_রাশিমালা = c_parser_দ্বিমিক_expression (parser, রিক্ত, void_list_গ্রন্থি);
      parens.skip_until_found_close (parser);
      যদি (cmp_রাশিমালা.মান == error_mark_গ্রন্থি)
	গচ্ছ saw_error;
      যদি (r)
	{
	  যদি (!c_বৃক্ষ_equal (cmp_রাশিমালা.মান, unfolded_lhs))
	    গচ্ছ bad_if;
	  cmp_রাশিমালা.মান = rhs1;
	  rhs1 = NULL_বৃক্ষ;
	  gcc_assert (বৃক্ষ_CODE (cmp_রাশিমালা.মান) == EQ_রাশিমালা);
	}
      যদি (বৃক্ষ_CODE (cmp_রাশিমালা.মান) == EQ_রাশিমালা)
	;
      অন্যথা যদি (!structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (রাশিমালা_LOC_OR_LOC (cmp_রাশিমালা.মান, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  গচ্ছ saw_error;
	}
      অন্যথা যদি (বৃক্ষ_CODE (cmp_রাশিমালা.মান) != GT_রাশিমালা
	       && বৃক্ষ_CODE (cmp_রাশিমালা.মান) != LT_রাশিমালা)
	{
	  error_at (রাশিমালা_LOC_OR_LOC (cmp_রাশিমালা.মান, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  গচ্ছ saw_error;
	}
      যদি (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	গচ্ছ saw_error;

      extra_scope = সত্য;
      eloc = c_parser_peek_token (parser)->location;
      রাশিমালা = c_parser_cast_expression (parser, রিক্ত);
      lhs = রাশিমালা.মান;
      রাশিমালা = default_function_array_conversion (eloc, রাশিমালা);
      unfolded_lhs = রাশিমালা.মান;
      lhs = c_fully_fold (lhs, অসত্য, রিক্ত, সত্য);
      orig_lhs = lhs;
      যদি (lhs == error_mark_গ্রন্থি)
	গচ্ছ saw_error;
      যদি (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      যদি (!c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  গচ্ছ saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      rhs1 = রাশিমালা.মান;

      যদি (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	গচ্ছ saw_error;

      যদি (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	গচ্ছ saw_error;

      extra_scope = অসত্য;
      no_semicolon = সত্য;

      যদি (c_বৃক্ষ_equal (বৃক্ষ_OPERAND (cmp_রাশিমালা.মান, 0), unfolded_lhs))
	{
	  যদি (বৃক্ষ_CODE (cmp_রাশিমালা.মান) == EQ_রাশিমালা)
	    {
	      opcode = COND_রাশিমালা;
	      rhs = c_fully_fold (বৃক্ষ_OPERAND (cmp_রাশিমালা.মান, 1),
				  অসত্য, রিক্ত, সত্য);
	      rhs1 = c_fully_fold (rhs1, অসত্য, রিক্ত, সত্য);
	    }
	  অন্যথা যদি (c_বৃক্ষ_equal (বৃক্ষ_OPERAND (cmp_রাশিমালা.মান, 1), rhs1))
	    {
	      opcode = (বৃক্ষ_CODE (cmp_রাশিমালা.মান) == GT_রাশিমালা
			? MIN_রাশিমালা : MAX_রাশিমালা);
	      rhs = c_fully_fold (rhs1, অসত্য, রিক্ত, সত্য);
	      rhs1 = c_fully_fold (বৃক্ষ_OPERAND (cmp_রাশিমালা.মান, 0),
				   অসত্য, রিক্ত, সত্য);
	    }
	  অন্যথা
	    গচ্ছ bad_if;
	}
      অন্যথা যদি (বৃক্ষ_CODE (cmp_রাশিমালা.মান) == EQ_রাশিমালা)
	গচ্ছ bad_if;
      অন্যথা যদি (c_বৃক্ষ_equal (বৃক্ষ_OPERAND (cmp_রাশিমালা.মান, 1), unfolded_lhs)
	       && c_বৃক্ষ_equal (বৃক্ষ_OPERAND (cmp_রাশিমালা.মান, 0), rhs1))
	{
	  opcode = (বৃক্ষ_CODE (cmp_রাশিমালা.মান) == GT_রাশিমালা
		    ? MAX_রাশিমালা : MIN_রাশিমালা);
	  rhs = c_fully_fold (rhs1, অসত্য, রিক্ত, সত্য);
	  rhs1 = c_fully_fold (বৃক্ষ_OPERAND (cmp_রাশিমালা.মান, 1),
			       অসত্য, রিক্ত, সত্য);
	}
      অন্যথা
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  গচ্ছ saw_error;
	}

      যদি (c_parser_next_token_is_keyword (parser, RID_ELSE))
	{
	  যদি (code != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_block && r == NULL_বৃক্ষ)
	      || বৃক্ষ_CODE (cmp_রাশিমালা.মান) != EQ_রাশিমালা)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      গচ্ছ saw_error;
	    }

	  c_parser_consume_token (parser);

	  যদি (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    গচ্ছ saw_error;

	  extra_scope = সত্য;
	  v = c_parser_cast_expression (parser, রিক্ত).মান;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, অসত্য, রিক্ত, সত্য);
	  যদি (v == error_mark_গ্রন্থি)
	    গচ্ছ saw_error;
	  যদি (non_lvalue_p)
	    v = non_lvalue (v);
	  যদি (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    গচ্ছ saw_error;

	  রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);

	  যদি (!c_বৃক্ষ_equal (রাশিমালা.মান, unfolded_lhs))
	    গচ্ছ bad_if;

	  যদি (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    গচ্ছ saw_error;

	  যদি (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    গচ্ছ saw_error;

	  extra_scope = অসত্য;
	  code = OMP_ATOMIC_CAPTURE_OLD;
	  যদি (r == NULL_বৃক্ষ)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_গ্রন্থি;
	}
      অন্যথা যদি (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  গচ্ছ saw_error;
	}
      অন্যথা যদি (code == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_বৃক্ষ
	       && v == NULL_বৃক্ষ)
	code = OMP_ATOMIC;
      গচ্ছ stmt_done;
    }
  eloc = c_parser_peek_token (parser)->location;
  রাশিমালা = c_parser_cast_expression (parser, রিক্ত);
  lhs = রাশিমালা.মান;
  রাশিমালা = default_function_array_conversion (eloc, রাশিমালা);
  unfolded_lhs = রাশিমালা.মান;
  lhs = c_fully_fold (lhs, অসত্য, রিক্ত, সত্য);
  orig_lhs = lhs;
  বিকল্প (বৃক্ষ_CODE (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    পক্ষ ERROR_MARK:
    saw_error:
      c_parser_skip_to_end_of_block_or_statement (parser);
      যদি (extra_scope && c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      যদি (structured_block)
	{
	  যদি (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  অন্যথা যদি (code == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      যদি (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      প্রত্যাগম;

    পক্ষ POSTINCREMENT_রাশিমালা:
      যদি (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    পক্ষ PREINCREMENT_রাশিমালা:
      lhs = বৃক্ষ_OPERAND (lhs, 0);
      unfolded_lhs = NULL_বৃক্ষ;
      opcode = PLUS_রাশিমালা;
      rhs = integer_one_গ্রন্থি;
      যদি (compare)
	গচ্ছ invalid_compare;
      ভঙ্গ;

    পক্ষ POSTDECREMENT_রাশিমালা:
      যদি (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    পক্ষ PREDECREMENT_রাশিমালা:
      lhs = বৃক্ষ_OPERAND (lhs, 0);
      unfolded_lhs = NULL_বৃক্ষ;
      opcode = MINUS_রাশিমালা;
      rhs = integer_one_গ্রন্থি;
      যদি (compare)
	গচ্ছ invalid_compare;
      ভঙ্গ;

    পক্ষ COMPOUND_রাশিমালা:
      যদি (বৃক্ষ_CODE (বৃক্ষ_OPERAND (lhs, 0)) == SAVE_রাশিমালা
	  && বৃক্ষ_CODE (বৃক্ষ_OPERAND (lhs, 1)) == COMPOUND_রাশিমালা
	  && বৃক্ষ_CODE (বৃক্ষ_OPERAND (বৃক্ষ_OPERAND (lhs, 1), 0)) == MODIFY_রাশিমালা
	  && বৃক্ষ_OPERAND (বৃক্ষ_OPERAND (lhs, 1), 1) == বৃক্ষ_OPERAND (lhs, 0)
	  && C_BOOLEAN_TYPE_P (বৃক্ষ_TYPE (বৃক্ষ_OPERAND (বৃক্ষ_OPERAND
					      (বৃক্ষ_OPERAND (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = বৃক্ষ_OPERAND (বৃক্ষ_OPERAND (lhs, 1), 0);
      /* FALLTHRU */
    পক্ষ MODIFY_রাশিমালা:
      যদি (বৃক্ষ_CODE (lhs) == MODIFY_রাশিমালা
	  && C_BOOLEAN_TYPE_P (বৃক্ষ_TYPE (বৃক্ষ_OPERAND (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  যদি (integer_onep (বৃক্ষ_OPERAND (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = বৃক্ষ_OPERAND (lhs, 1);
	      lhs = বৃক্ষ_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_বৃক্ষ;
	      opcode = NOP_রাশিমালা;
	      যদি (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && বৃক্ষ_CODE (orig_lhs) == COMPOUND_রাশিমালা)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      যদি (compare)
		গচ্ছ invalid_compare;
	      ভঙ্গ;
	    }
	  যদি (বৃক্ষ_CODE (বৃক্ষ_OPERAND (lhs, 1)) == TRUTH_NOT_রাশিমালা
	      && বৃক্ষ_OPERAND (lhs, 0)
		 == বৃক্ষ_OPERAND (বৃক্ষ_OPERAND (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = বৃক্ষ_OPERAND (lhs, 1);
	      lhs = বৃক্ষ_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_বৃক্ষ;
	      opcode = NOP_রাশিমালা;
	      যদি (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && বৃক্ষ_CODE (orig_lhs) == COMPOUND_রাশিমালা)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      যদি (compare)
		গচ্ছ invalid_compare;
	      ভঙ্গ;
	    }
	}
      /* FALLTHRU */
    স্বভাব:
      যদি (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      যদি (compare && !c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  গচ্ছ saw_error;
	}
      বিকল্প (c_parser_peek_token (parser)->type)
	{
	পক্ষ CPP_MULT_EQ:
	  opcode = MULT_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_DIV_EQ:
	  opcode = TRUNC_DIV_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_PLUS_EQ:
	  opcode = PLUS_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_MINUS_EQ:
	  opcode = MINUS_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_LSHIFT_EQ:
	  opcode = LSHIFT_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_RSHIFT_EQ:
	  opcode = RSHIFT_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_AND_EQ:
	  opcode = BIT_AND_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_OR_EQ:
	  opcode = BIT_IOR_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_XOR_EQ:
	  opcode = BIT_XOR_রাশিমালা;
	  ভঙ্গ;
	পক্ষ CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত, unfolded_lhs);
	  rhs1 = রাশিমালা.মান;
	  বিকল্প (বৃক্ষ_CODE (rhs1))
	    {
	    পক্ষ MULT_রাশিমালা:
	    পক্ষ TRUNC_DIV_রাশিমালা:
	    পক্ষ RDIV_রাশিমালা:
	    পক্ষ PLUS_রাশিমালা:
	    পক্ষ MINUS_রাশিমালা:
	    পক্ষ LSHIFT_রাশিমালা:
	    পক্ষ RSHIFT_রাশিমালা:
	    পক্ষ BIT_AND_রাশিমালা:
	    পক্ষ BIT_IOR_রাশিমালা:
	    পক্ষ BIT_XOR_রাশিমালা:
	      যদি (compare)
		ভঙ্গ;
	      যদি (c_বৃক্ষ_equal (বৃক্ষ_OPERAND (rhs1, 0), unfolded_lhs))
		{
		  opcode = বৃক্ষ_CODE (rhs1);
		  rhs = c_fully_fold (বৃক্ষ_OPERAND (rhs1, 1), অসত্য, রিক্ত,
				      সত্য);
		  rhs1 = c_fully_fold (বৃক্ষ_OPERAND (rhs1, 0), অসত্য, রিক্ত,
				       সত্য);
		  গচ্ছ stmt_done;
		}
	      যদি (c_বৃক্ষ_equal (বৃক্ষ_OPERAND (rhs1, 1), unfolded_lhs))
		{
		  opcode = বৃক্ষ_CODE (rhs1);
		  rhs = c_fully_fold (বৃক্ষ_OPERAND (rhs1, 0), অসত্য, রিক্ত,
				      সত্য);
		  rhs1 = c_fully_fold (বৃক্ষ_OPERAND (rhs1, 1), অসত্য, রিক্ত,
				       সত্য);
		  swapped = !commutative_বৃক্ষ_code (opcode);
		  গচ্ছ stmt_done;
		}
	      ভঙ্গ;
	    পক্ষ COND_রাশিমালা:
	      যদি (!compare)
		ভঙ্গ;
	      যদি (বৃক্ষ_CODE (বৃক্ষ_OPERAND (rhs1, 0)) != GT_রাশিমালা
		  && বৃক্ষ_CODE (বৃক্ষ_OPERAND (rhs1, 0)) != LT_রাশিমালা
		  && বৃক্ষ_CODE (বৃক্ষ_OPERAND (rhs1, 0)) != EQ_রাশিমালা)
		ভঙ্গ;
	      যদি (!বৃক্ষ_OPERAND (rhs1, 1))
		ভঙ্গ;
	      যদি (!c_বৃক্ষ_equal (বৃক্ষ_OPERAND (rhs1, 2), unfolded_lhs))
		ভঙ্গ;
	      যদি (c_বৃক্ষ_equal (বৃক্ষ_OPERAND (বৃক্ষ_OPERAND (rhs1, 0), 0),
				unfolded_lhs))
		{
		  যদি (বৃক্ষ_CODE (বৃক্ষ_OPERAND (rhs1, 0)) == EQ_রাশিমালা)
		    {
		      opcode = COND_রাশিমালা;
		      rhs = c_fully_fold (বৃক্ষ_OPERAND (বৃক্ষ_OPERAND (rhs1,
								      0), 1),
					  অসত্য, রিক্ত, সত্য);
		      rhs1 = c_fully_fold (বৃক্ষ_OPERAND (rhs1, 1), অসত্য,
					   রিক্ত, সত্য);
		      গচ্ছ stmt_done;
		    }
		  যদি (c_বৃক্ষ_equal (বৃক্ষ_OPERAND (বৃক্ষ_OPERAND (rhs1, 0), 1),
				    বৃক্ষ_OPERAND (rhs1, 1)))
		    {
		      opcode = (বৃক্ষ_CODE (বৃক্ষ_OPERAND (rhs1, 0)) == GT_রাশিমালা
				? MIN_রাশিমালা : MAX_রাশিমালা);
		      rhs = c_fully_fold (বৃক্ষ_OPERAND (rhs1, 1), অসত্য, রিক্ত,
					  সত্য);
		      rhs1 = c_fully_fold (বৃক্ষ_OPERAND (বৃক্ষ_OPERAND (rhs1,
								       0), 0),
					   অসত্য, রিক্ত, সত্য);
		      গচ্ছ stmt_done;
		    }
		}
	      অন্যথা যদি (বৃক্ষ_CODE (বৃক্ষ_OPERAND (rhs1, 0)) == EQ_রাশিমালা)
		ভঙ্গ;
	      অন্যথা যদি (c_বৃক্ষ_equal (বৃক্ষ_OPERAND (বৃক্ষ_OPERAND (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  যদি (c_বৃক্ষ_equal (বৃক্ষ_OPERAND (বৃক্ষ_OPERAND (rhs1, 0), 0),
				    বৃক্ষ_OPERAND (rhs1, 1)))
		    {
		      opcode = (বৃক্ষ_CODE (বৃক্ষ_OPERAND (rhs1, 0)) == GT_রাশিমালা
				? MAX_রাশিমালা : MIN_রাশিমালা);
		      rhs = c_fully_fold (বৃক্ষ_OPERAND (rhs1, 1), অসত্য, রিক্ত,
					  সত্য);
		      rhs1 = c_fully_fold (বৃক্ষ_OPERAND (বৃক্ষ_OPERAND (rhs1,
								       0), 1),
					   অসত্য, রিক্ত, সত্য);
		      গচ্ছ stmt_done;
		    }
		}
	      ভঙ্গ;
	    পক্ষ EQ_রাশিমালা:
	      যদি (!compare
		  || code != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_block
		  || v
		  || r)
		ভঙ্গ;
	      যদি (c_parser_next_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_বৃক্ষ;
		  c_parser_consume_token (parser);
		  গচ্ছ restart;
		}
	      ভঙ্গ;
	    পক্ষ ERROR_MARK:
	      গচ্ছ saw_error;
	    স্বভাব:
	      ভঙ্গ;
	    }
	  যদি (c_parser_peek_token (parser)->type == CPP_SEMICOLON)
	    {
	      যদি (structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
		{
		  code = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_বৃক্ষ;
		  রাশিমালা = default_function_array_read_conversion (eloc, রাশিমালা);
		  unfolded_lhs1 = রাশিমালা.মান;
		  lhs1 = c_fully_fold (unfolded_lhs1, অসত্য, রিক্ত, সত্য);
		  rhs1 = NULL_বৃক্ষ;
		  c_parser_consume_token (parser);
		  গচ্ছ restart;
		}
	      যদি (structured_block && !compare)
		{
		  opcode = NOP_রাশিমালা;
		  রাশিমালা = default_function_array_read_conversion (eloc, রাশিমালা);
		  rhs = c_fully_fold (রাশিমালা.মান, অসত্য, রিক্ত, সত্য);
		  rhs1 = NULL_বৃক্ষ;
		  গচ্ছ stmt_done;
		}
	    }
	  c_parser_error (parser, "invalid form of %<#pragma omp atomic%>");
	  গচ্ছ saw_error;
	স্বভাব:
	  c_parser_error (parser,
			  "invalid operator for %<#pragma omp atomic%>");
	  গচ্ছ saw_error;
	}

      /* Arrange to pass the location of the assignment operator to
	 c_finish_omp_atomic.  */
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      রাশিমালা = c_parser_expression (parser);
      রাশিমালা = default_function_array_read_conversion (eloc, রাশিমালা);
      rhs = রাশিমালা.মান;
      rhs = c_fully_fold (rhs, অসত্য, রিক্ত, সত্য);
      ভঙ্গ;
    }
stmt_done:
  যদি (structured_block && code == OMP_ATOMIC_CAPTURE_NEW && r == NULL_বৃক্ষ)
    {
      যদি (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	গচ্ছ saw_error;
      no_semicolon = অসত্য;
      v = c_parser_cast_expression (parser, রিক্ত).মান;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, অসত্য, রিক্ত, সত্য);
      যদি (v == error_mark_গ্রন্থি)
	গচ্ছ saw_error;
      যদি (non_lvalue_p)
	v = non_lvalue (v);
      যদি (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	গচ্ছ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      রাশিমালা = c_parser_cast_expression (parser, রিক্ত);
      lhs1 = রাশিমালা.মান;
      রাশিমালা = default_function_array_read_conversion (eloc, রাশিমালা);
      unfolded_lhs1 = রাশিমালা.মান;
      lhs1 = c_fully_fold (lhs1, অসত্য, রিক্ত, সত্য);
      যদি (lhs1 == error_mark_গ্রন্থি)
	গচ্ছ saw_error;
      যদি (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  যদি (structured_block)
    {
      যদি (!no_semicolon)
	c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
done:
  যদি (weak && opcode != COND_রাশিমালা)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = অসত্য;
    }
  যদি (unfolded_lhs && unfolded_lhs1
      && !c_বৃক্ষ_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_গ্রন্থি;
    }
  অন্যথা
    stmt = c_finish_omp_atomic (loc, code, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, memory_order, weak);
  যদি (stmt != error_mark_গ্রন্থি)
    add_stmt (stmt);

  যদি (!structured_block && !no_semicolon)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}


/* OpenMP 2.5:
   # pragma omp barrier new-line
*/

স্থির শূন্য
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

স্থির বৃক্ষ
c_parser_omp_critical (location_t loc, c_parser *parser, তার্কিক *if_p)
{
  বৃক্ষ stmt, name = NULL_বৃক্ষ, clauses = NULL_বৃক্ষ;

  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      যদি (c_parser_next_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->মান;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      অন্যথা
	c_parser_error (parser, "expected identifier");

      যদি (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_MASK,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_block (parser, if_p);
  প্রত্যাগম c_finish_omp_critical (loc, stmt, name, clauses);
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

স্থির শূন্য
c_parser_omp_depobj (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  matching_parens parens;
  যদি (!parens.require_open (parser))
    {
      c_parser_skip_to_pragma_eol (parser);
      প্রত্যাগম;
    }

  বৃক্ষ depobj = c_parser_রাশিমালা_no_commas (parser, রিক্ত).মান;
  যদি (depobj != error_mark_গ্রন্থি)
    {
      যদি (!lvalue_p (depobj))
	{
	  error_at (রাশিমালা_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_গ্রন্থি;
	}
      অন্যথা
	{
	  বৃক্ষ addr = build_unary_op (রাশিমালা_LOC_OR_LOC (depobj, loc), ADDR_রাশিমালা,
				      depobj, অসত্য);
	  যদি (addr == error_mark_গ্রন্থি)
	    depobj = error_mark_গ্রন্থি;
	  অন্যথা
	    depobj = build_indirect_ref (রাশিমালা_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_STAR);
	}
    }

  parens.skip_until_found_close (parser);
  বৃক্ষ clause = NULL_বৃক্ষ;
  গণনা omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_INVALID;
  যদি (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);

      c_parser_consume_token (parser);
      যদি (!strcmp ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_বৃক্ষ, c_loc);
	  clause = c_finish_omp_clauses (clause, C_ORT_OMP);
	  যদি (!clause)
	    clause = error_mark_গ্রন্থি;
	}
      অন্যথা যদি (!strcmp ("destroy", p))
	{
	  matching_parens c_parens;
	  kind = OMP_CLAUSE_DEPEND_LAST;
	  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      বৃক্ষ destobj = c_parser_রাশিমালা_no_commas (parser, রিক্ত).মান;
	      যদি (!lvalue_p (destobj))
		error_at (রাশিমালা_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      অন্যথা যদি (depobj != error_mark_গ্রন্থি
		       && !operand_equal_p (destobj, depobj,
					    OEP_MATCH_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (রাশিমালা_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_found_close (parser);
	    }
	}
      অন্যথা যদি (!strcmp ("update", p))
	{
	  matching_parens c_parens;
	  যদি (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      যদি (c_parser_next_token_is (parser, CPP_NAME))
		{
		  ধ্রুব বর্ণ *p2
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);

		  c_parser_consume_token (parser);
		  যদি (!strcmp ("in", p2))
		    kind = OMP_CLAUSE_DEPEND_IN;
		  অন্যথা যদি (!strcmp ("out", p2))
		    kind = OMP_CLAUSE_DEPEND_OUT;
		  অন্যথা যদি (!strcmp ("inout", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUT;
		  অন্যথা যদি (!strcmp ("mutexinoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  অন্যথা যদি (!strcmp ("inoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      যদি (kind == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_গ্রন্থি;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_found_close (parser);
	    }
	  অন্যথা
	    clause = error_mark_গ্রন্থি;
	}
    }
  যদি (!clause && kind == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_গ্রন্থি;
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

স্থির শূন্য
c_parser_omp_flush (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  গণনা memmodel mo = MEMMODEL_LAST;
  যদি (c_parser_next_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);

      যদি (!strcmp (p, "seq_cst"))
	mo = MEMMODEL_SEQ_CST;
      অন্যথা যদি (!strcmp (p, "acq_rel"))
	mo = MEMMODEL_ACQ_REL;
      অন্যথা যদি (!strcmp (p, "release"))
	mo = MEMMODEL_RELEASE;
      অন্যথা যদি (!strcmp (p, "acquire"))
	mo = MEMMODEL_ACQUIRE;
      অন্যথা
	error_at (c_parser_peek_token (parser)->location,
		  "expected %<seq_cst%>, %<acq_rel%>, %<release%> or "
		  "%<acquire%>");
      c_parser_consume_token (parser);
    }
  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      যদি (mo != MEMMODEL_LAST)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, রিক্ত);
    }
  অন্যথা যদি (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_to_pragma_eol (parser);

  c_finish_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

স্থির তার্কিক
c_parser_omp_section_scan (c_parser *parser, ধ্রুব বর্ণ *directive,
			   তার্কিক tentative)
{
  যদি (!c_parser_nth_token_starts_std_attributes (parser, 1))
    প্রত্যাগম অসত্য;
  unsigned পূর্ণাঙ্ক n = 3;
  যদি (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    প্রত্যাগম অসত্য;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  যদি (token->type != CPP_CLOSE_SQUARE)
    প্রত্যাগম অসত্য;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  যদি (token->type != CPP_CLOSE_SQUARE)
    প্রত্যাগম অসত্য;
  যদি (n < 9)
    প্রত্যাগম অসত্য;
  যদি (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      বৃক্ষ first = c_parser_peek_nth_token_raw (parser, 3)->মান;
      বৃক্ষ second = c_parser_peek_nth_token_raw (parser, 5)->মান;
      যদি (strcmp (IDENTIFIER_POINTER (first), "directive")
	  && strcmp (IDENTIFIER_POINTER (first), "__directive__"))
	প্রত্যাগম অসত্য;
      যদি (strcmp (IDENTIFIER_POINTER (second), directive))
	প্রত্যাগম অসত্য;
    }
  যদি (tentative)
    প্রত্যাগম সত্য;
  location_t first_loc = c_parser_peek_token (parser)->location;
  location_t last_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t মধ্য_loc = UNKNOWN_LOCATION;
  বৃক্ষ std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  তার্কিক seen = অসত্য;
  পূর্ণাঙ্ক cnt = 0;
  প্রতি (বৃক্ষ attr = std_attrs; attr; attr = বৃক্ষ_CHAIN (attr))
    যদি (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	প্রতি (বৃক্ষ a = বৃক্ষ_মান (attr); a; a = বৃক্ষ_CHAIN (a))
	  {
	    বৃক্ষ d = বৃক্ষ_মান (a);
	    gcc_assert (বৃক্ষ_CODE (d) == C_TOKEN_VEC);
	    c_token *first = C_TOKEN_VEC_TOKENS (d)->address ();
	    cnt++;
	    যদি (first->type == CPP_NAME
		&& strcmp (IDENTIFIER_POINTER (first->মান),
			   directive) == 0)
	      {
		seen = সত্য;
		যদি (মধ্য_loc == UNKNOWN_LOCATION)
		  মধ্য_loc = first->location;
	      }
	  }
      }
  যদি (!seen)
    প্রত্যাগম অসত্য;
  যদি (cnt != 1 || বৃক্ষ_CHAIN (std_attrs))
    {
      error_at (make_location (first_loc, last_loc, মধ্য_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      প্রত্যাগম অসত্য;
    }
  c_parser_handle_statement_omp_attributes (parser, std_attrs, রিক্ত);
  প্রত্যাগম সত্য;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

স্থির বৃক্ষ
c_parser_omp_structured_block_sequence (c_parser *parser,
					গণনা pragma_kind kind)
{
  বৃক্ষ stmt = ঠেলো_stmt_list ();
  c_parser_statement (parser, রিক্ত);
  কুরু
    {
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	ভঙ্গ;
      যদি (c_parser_next_token_is (parser, CPP_EOF))
	ভঙ্গ;

      যদি (kind != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_kind == kind)
	ভঙ্গ;

      যদি (kind != PRAGMA_NONE
	  && c_parser_omp_section_scan (parser,
					kind == PRAGMA_OMP_SCAN
					? "scan" : "section", অসত্য))
	ভঙ্গ;

      c_parser_statement (parser, রিক্ত);
    }
  যাবত্ (1);
  প্রত্যাগম বের_করো_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

স্থির শূন্য
c_parser_omp_scan_loop_body (c_parser *parser, তার্কিক open_brace_parsed)
{
  বৃক্ষ substmt;
  location_t loc;
  বৃক্ষ clauses = NULL_বৃক্ষ;
  তার্কিক found_scan = অসত্য;

  loc = c_parser_peek_token (parser)->location;
  যদি (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = অসত্য;
      প্রত্যাগম;
    }

  যদি (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SCAN)
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_OMP_SCAN);
  অন্যথা
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_গ্রন্থি, substmt, NULL_বৃক্ষ);
  SET_রাশিমালা_LOCATION (substmt, loc);
  add_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  যদি (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SCAN)
    {
      গণনা omp_clause_code clause = OMP_CLAUSE_ERROR;
      found_scan = সত্য;

      c_parser_consume_pragma (parser);

      যদি (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      যদি (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ধ্রুব বর্ণ *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
	  যদি (strcmp (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  অন্যথা যদি (strcmp (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      যদি (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_বৃক্ষ);
	}
      অন্যথা
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_to_pragma_eol (parser);
    }
  অন্যথা
    error ("expected %<#pragma omp scan%>");

  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  যদি (!c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_NONE);
  অন্যথা
    {
      যদি (found_scan)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_গ্রন্থি, substmt, clauses);
  SET_রাশিমালা_LOCATION (substmt, loc);
  add_stmt (substmt);

  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
স্থির তার্কিক
c_parser_omp_next_tokens_can_be_canon_loop (c_parser *parser,
					    গণনা বৃক্ষ_code code,
					    তার্কিক error_p)
{
  যদি (code == OACC_LOOP)
    {
      যদি (c_parser_next_token_is_keyword (parser, RID_FOR))
	প্রত্যাগম সত্য;
      যদি (error_p)
	c_parser_error (parser, "for statement expected");
    }
  অন্যথা
    {
      যদি (c_parser_next_token_is_keyword (parser, RID_FOR))
	প্রত্যাগম সত্য;

      যদি (c_parser_next_token_is (parser, CPP_PRAGMA))
	বিকল্প (c_parser_peek_token (parser)->pragma_kind)
	  {
	  পক্ষ PRAGMA_OMP_UNROLL:
	  পক্ষ PRAGMA_OMP_TILE:
	    প্রত্যাগম সত্য;
	  স্বভাব:
	    ভঙ্গ;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      size_t n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      যদি (token->type == CPP_NAME
	  && C_IS_RESERVED_WORD (token->মান)
	  && C_RID_CODE (token->মান) == RID_FOR)
	প্রত্যাগম সত্য;
      যদি (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  প্রত্যাগম অসত্য;
}

স্থির বৃক্ষ c_parser_omp_tile (location_t, c_parser *, তার্কিক *);
স্থির বৃক্ষ c_parser_omp_unroll (location_t, c_parser *, তার্কিক *);

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

স্থির বৃক্ষ
c_parser_omp_loop_nest (c_parser *parser, তার্কিক *if_p)
{
  বৃক্ষ decl = NULL_বৃক্ষ, cond = NULL_বৃক্ষ, incr = NULL_বৃক্ষ, init = NULL_বৃক্ষ;
  বৃক্ষ body = NULL_বৃক্ষ;
  matching_parens parens;
  তার্কিক moreloops;
  unsigned বর্ণ save_in_statement;
  বৃক্ষ loop_scope;
  location_t loc;
  সংরচনা omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  পূর্ণাঙ্ক depth = omp_for_parse_state->depth;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  যদি (c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      বৃক্ষ std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_attributes (parser, std_attrs, রিক্ত);
      যদি (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  যদি (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      বৃক্ষ transform = NULL_বৃক্ষ, sizes, body = NULL_বৃক্ষ;
      পূর্ণাঙ্ক গুনতি = 0;
      বিকল্প (c_parser_peek_token (parser)->pragma_kind)
	{
	পক্ষ PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = ঠেলো_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = বের_করো_stmt_list (body);
	  যদি (transform == NULL_বৃক্ষ || transform == error_mark_গ্রন্থি)
	    {
	      transform = error_mark_গ্রন্থি;
	      ভঙ্গ;
	    }
	  gcc_assert (বৃক্ষ_CODE (transform) == OMP_UNROLL);
	  যদি (omp_find_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      যদি (omp_for_parse_state->গুনতি - depth > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->গুনতি - depth);
		  transform = error_mark_গ্রন্থি;
		}
	      অন্যথা
		গুনতি = 1;
	    }
	  অন্যথা
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_গ্রন্থি;
	    }
	  ভঙ্গ;
	পক্ষ PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = ঠেলো_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = বের_করো_stmt_list (body);
	  যদি (transform == NULL_বৃক্ষ || transform == error_mark_গ্রন্থি)
	    {
	      transform = error_mark_গ্রন্থি;
	      ভঙ্গ;
	    }
	  gcc_assert (বৃক্ষ_CODE (transform) == OMP_TILE);
	  sizes = omp_find_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  গুনতি = list_length (OMP_CLAUSE_SIZES_LIST (sizes));
	  যদি (depth + গুনতি < omp_for_parse_state->গুনতি)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			গুনতি, omp_for_parse_state->গুনতি - depth);
	      transform = error_mark_গ্রন্থি;
	    }
	  ভঙ্গ;
	স্বভাব:
	  c_parser_pragma (parser, pragma_stmt, রিক্ত, void_list_গ্রন্থি);
	  ভঙ্গ;
	}
      যদি (transform == NULL_বৃক্ষ)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      যদি (transform == NULL_বৃক্ষ || transform == error_mark_গ্রন্থি)
	{
	  omp_for_parse_state->fail = সত্য;
	  প্রত্যাগম NULL_বৃক্ষ;
	}
      প্রতি (গুনতি = omp_for_parse_state->গুনতি; depth < গুনতি; ++depth)
	{
	  বৃক্ষ_VEC_ELT (omp_for_parse_state->declv, depth) = NULL_বৃক্ষ;
	  বৃক্ষ_VEC_ELT (omp_for_parse_state->initv, depth) = NULL_বৃক্ষ;
	  বৃক্ষ_VEC_ELT (omp_for_parse_state->condv, depth) = NULL_বৃক্ষ;
	  বৃক্ষ_VEC_ELT (omp_for_parse_state->incrv, depth) = NULL_বৃক্ষ;
	}
      omp_for_parse_state->want_nested_loop = অসত্য;
      প্রত্যাগম body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_in_statement = in_statement;
  in_statement = IN_OMP_BLOCK;

  /* We are not in intervening code now.  */
  omp_for_parse_state->in_intervening_code = অসত্য;

  যদি (!parens.require_open (parser))
    {
      omp_for_parse_state->fail = সত্য;
      প্রত্যাগম NULL_বৃক্ষ;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (সত্য);

  /* Parse the initialization declaration or expression.  */
  যদি (c_parser_next_tokens_start_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      বৃক্ষ this_pre_body = ঠেলো_stmt_list ();
      c_in_omp_for = সত্য;
      c_parser_declaration_or_fndef (parser, সত্য, সত্য, সত্য, সত্য, সত্য,
				     অসত্য);
      c_in_omp_for = অসত্য;
      this_pre_body = বের_করো_stmt_list (this_pre_body);
      append_to_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      যদি (decl == রিক্ত)
	গচ্ছ error_init;
      যদি (DECL_INITIAL (decl) == error_mark_গ্রন্থি)
	decl = error_mark_গ্রন্থি;
      init = decl;
    }
  অন্যথা যদি (c_parser_next_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      সংরচনা c_রাশিমালা decl_exp;
      সংরচনা c_রাশিমালা init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_expression (parser);
      decl = decl_exp.মান;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_in_omp_for = সত্য;
      init = build_modify_রাশিমালা (init_loc, decl, decl_exp.original_type,
				NOP_রাশিমালা, init_loc, init_exp.মান,
				init_exp.original_type);
      c_in_omp_for = অসত্য;
      init = c_process_রাশিমালা_stmt (init_loc, init);

      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  অন্যথা
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->fail = সত্য;
      গচ্ছ parse_next;
    }

  /* Parse the loop condition.  */
  যদি (c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_in_omp_for = সত্য;
      সংরচনা c_রাশিমালা cond_রাশিমালা
	= c_parser_দ্বিমিক_expression (parser, রিক্ত, NULL_বৃক্ষ);
      c_in_omp_for = অসত্য;

      cond = cond_রাশিমালা.মান;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      বিকল্প (cond_রাশিমালা.original_code)
	{
	পক্ষ GT_রাশিমালা:
	পক্ষ GE_রাশিমালা:
	পক্ষ LT_রাশিমালা:
	পক্ষ LE_রাশিমালা:
	  ভঙ্গ;
	পক্ষ NE_রাশিমালা:
	  যদি (omp_for_parse_state->code != OACC_LOOP)
	    ভঙ্গ;
	  /* FALLTHRU.  */
	স্বভাব:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_রাশিমালা, boolean_type_গ্রন্থি, error_mark_গ্রন্থি);
	  ভঙ্গ;
	}
      protected_set_রাশিমালা_location (cond, cond_loc);
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  যদি (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_রাশিমালা_stmt (incr_loc,
				  c_parser_expression (parser).মান);
    }
  parens.skip_until_found_close (parser);

  যদি (decl == রিক্ত || decl == error_mark_গ্রন্থি || init == error_mark_গ্রন্থি)
    omp_for_parse_state->fail = সত্য;
  অন্যথা
    {
      বৃক্ষ_VEC_ELT (omp_for_parse_state->declv, depth) = decl;
      বৃক্ষ_VEC_ELT (omp_for_parse_state->initv, depth) = init;
      বৃক্ষ_VEC_ELT (omp_for_parse_state->condv, depth) = cond;
      বৃক্ষ_VEC_ELT (omp_for_parse_state->incrv, depth) = incr;
    }

parse_next:
  moreloops = depth < omp_for_parse_state->গুনতি - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  যদি (moreloops
      && c_parser_omp_next_tokens_can_be_canon_loop (parser,
						     omp_for_parse_state->code,
						     অসত্য))
    {
      omp_for_parse_state->depth++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->depth--;
    }
  অন্যথা যদি (moreloops && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* This is the open brace in the loop-body grammar production.  Rather
	 than trying to special-case braces, just parse it as a compound
	 statement and handle the nested loop-body case there.  Note that
	 when we see a further open brace inside the compound statement
	 loop-body, we don't know whether it is the start of intervening
	 code that is a compound statement, or a level of braces
	 surrounding a nested loop-body.  Use the WANT_NESTED_LOOP state
	 bit to ensure we have only one nested loop at each level.  */
      omp_for_parse_state->in_intervening_code = সত্য;
      body = c_parser_compound_statement (parser, রিক্ত);
      omp_for_parse_state->in_intervening_code = অসত্য;
      যদি (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = সত্য;
	}
      if_p = রিক্ত;
    }
  অন্যথা
    {
      /* This is the final-loop-body case in the grammar: we have
	 something that is not a FOR and not an open brace.  */
      যদি (moreloops)
	{
	  /* If we were expecting a nested loop, give an error and mark
	     that parsing has failed, and try to recover by parsing the
	     body as regular code without further collapsing.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = সত্য;
	}
      in_statement = IN_OMP_FOR;
      parser->omp_for_parse_state = রিক্ত;
      body = ঠেলো_stmt_list ();
      যদি (omp_for_parse_state->inscan)
	c_parser_omp_scan_loop_body (parser, অসত্য);
      অন্যথা
	add_stmt (c_parser_c99_block_statement (parser, if_p));
      body = বের_করো_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  in_statement = save_in_statement;
  omp_for_parse_state->want_nested_loop = অসত্য;
  omp_for_parse_state->in_intervening_code = সত্য;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  যদি (body)
    add_stmt (body);
  body = c_end_compound_stmt (loc, loop_scope, সত্য);
  যদি (decl && বৃক্ষ_CODE (body) == BIND_রাশিমালা)
    {
      বৃক্ষ t = BIND_রাশিমালা_VARS (body);
      বৃক্ষ prev = NULL_বৃক্ষ, next = NULL_বৃক্ষ;
      যাবত্ (t)
	{
	  next = DECL_CHAIN (t);
	  যদি (t == decl)
	    {
	      যদি (prev)
		DECL_CHAIN (prev) = next;
	      অন্যথা
		{
		  BIND_রাশিমালা_VARS (body) = next;
		  BLOCK_VARS (BIND_রাশিমালা_BLOCK (body)) = next;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      ভঙ্গ;
	    }
	  অন্যথা
	    {
	      prev = t;
	      t = next;
	    }
	}
      যদি (BIND_রাশিমালা_VARS (body) == NULL_বৃক্ষ)
	body = BIND_রাশিমালা_BODY (body);
    }

  প্রত্যাগম body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

স্থির বৃক্ষ
c_parser_omp_for_loop (location_t loc, c_parser *parser, গণনা বৃক্ষ_code code,
		       বৃক্ষ clauses, বৃক্ষ *cclauses, তার্কিক *if_p)
{
  বৃক্ষ body, stmt, cl;
  বৃক্ষ ret = NULL_বৃক্ষ;
  বৃক্ষ ordered_cl = NULL_বৃক্ষ;
  পূর্ণাঙ্ক i, collapse = 1, ordered = 0, গুনতি;
  তার্কিক oacc_tiling = অসত্য;
  তার্কিক inscan = অসত্য;
  সংরচনা omp_for_parse_data data;
  সংরচনা omp_for_parse_data *save_data = parser->omp_for_parse_state;

  প্রতি (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    যদি (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = বৃক্ষ_to_shwi (OMP_CLAUSE_COLLAPSE_রাশিমালা (cl));
    অন্যথা যদি (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = সত্য;
	collapse = list_length (OMP_CLAUSE_TILE_LIST (cl));
      }
    অন্যথা যদি (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_SIZES)
      collapse = list_length (OMP_CLAUSE_SIZES_LIST (cl));
    অন্যথা যদি (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_রাশিমালা (cl))
      {
	ordered_cl = cl;
	ordered = বৃক্ষ_to_shwi (OMP_CLAUSE_ORDERED_রাশিমালা (cl));
      }
    অন্যথা যদি (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (code == OMP_SIMD || code == OMP_FOR))
      inscan = সত্য;

  যদি (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_রাশিমালা (ordered_cl)
	= build_int_cst (integer_type_গ্রন্থি, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  গুনতি = ordered ? ordered : collapse;

  যদি (!c_parser_omp_next_tokens_can_be_canon_loop (parser, code, সত্য))
    প্রত্যাগম রিক্ত;

  /* Initialize parse state for recursive descent.  */
  data.declv = make_বৃক্ষ_vec (গুনতি);
  data.initv = make_বৃক্ষ_vec (গুনতি);
  data.condv = make_বৃক্ষ_vec (গুনতি);
  data.incrv = make_বৃক্ষ_vec (গুনতি);
  data.pre_body = NULL_বৃক্ষ;
  data.bindings = NULL_বৃক্ষ;
  data.for_loc = c_parser_peek_token (parser)->location;
  data.গুনতি = গুনতি;
  data.depth = 0;
  data.want_nested_loop = সত্য;
  data.ordered = ordered > 0;
  data.in_intervening_code = অসত্য;
  data.perfect_nesting_fail = অসত্য;
  data.fail = অসত্য;
  data.inscan = inscan;
  data.saw_intervening_code = অসত্য;
  data.code = code;
  parser->omp_for_parse_state = &data;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  প্রতি (বৃক্ষ t = data.bindings; t; )
    {
      বৃক্ষ n = বৃক্ষ_CHAIN (t);
      বৃক্ষ_CHAIN (t) = NULL_বৃক্ষ;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  যদি (!data.fail)
    {
      c_in_omp_for = সত্য;
      stmt = c_finish_omp_for (loc, code, data.declv, রিক্ত, data.initv,
			       data.condv, data.incrv,
			       body, data.pre_body, সত্য);
      c_in_omp_for = অসত্য;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      যদি (stmt && !c_omp_check_loop_iv (stmt, data.declv, রিক্ত))
	stmt = NULL_বৃক্ষ;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      যদি (data.saw_intervening_code
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, রিক্ত))
	stmt = NULL_বৃক্ষ;

      যদি (stmt)
	{
	  add_stmt (stmt);

	  প্রতি (i = 0; i < বৃক্ষ_VEC_LENGTH (OMP_FOR_INIT (stmt)); i++)
	    {
	      বৃক্ষ init = বৃক্ষ_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      যদি (init == NULL_বৃক্ষ)
		ভঙ্গ;
	      gcc_assert (বৃক্ষ_CODE (init) == MODIFY_রাশিমালা);
	      বৃক্ষ decl = বৃক্ষ_OPERAND (init, 0);
	      বৃক্ষ cond = বৃক্ষ_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (বৃক্ষ_OPERAND (cond, 0) == decl);

	      বৃক্ষ op0 = বৃক্ষ_OPERAND (init, 1);
	      যদি (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || বৃক্ষ_CODE (op0) != বৃক্ষ_VEC)
		বৃক্ষ_OPERAND (init, 1) = c_fully_fold (op0, অসত্য, রিক্ত);
	      অন্যথা
		{
		  বৃক্ষ_VEC_ELT (op0, 1)
		    = c_fully_fold (বৃক্ষ_VEC_ELT (op0, 1), অসত্য, রিক্ত);
		  বৃক্ষ_VEC_ELT (op0, 2)
		    = c_fully_fold (বৃক্ষ_VEC_ELT (op0, 2), অসত্য, রিক্ত);
		}

	      বৃক্ষ op1 = বৃক্ষ_OPERAND (cond, 1);
	      যদি (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || বৃক্ষ_CODE (op1) != বৃক্ষ_VEC)
		বৃক্ষ_OPERAND (cond, 1) = c_fully_fold (op1, অসত্য, রিক্ত);
	      অন্যথা
		{
		  বৃক্ষ_VEC_ELT (op1, 1)
		    = c_fully_fold (বৃক্ষ_VEC_ELT (op1, 1), অসত্য, রিক্ত);
		  বৃক্ষ_VEC_ELT (op1, 2)
		    = c_fully_fold (বৃক্ষ_VEC_ELT (op1, 2), অসত্য, রিক্ত);
		}
	    }

	  যদি (cclauses != রিক্ত
	      && cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL] != রিক্ত)
	    {
	      বৃক্ষ *c;
	      প্রতি (c = &cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL]; *c ; )
		যদি (OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		অন্যথা
		  {
		    প্রতি (i = 0; i < গুনতি; i++)
		      যদি (বৃক্ষ_VEC_ELT (data.declv, i) == OMP_CLAUSE_DECL (*c))
			ভঙ্গ;
		    যদি (i == গুনতি)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    অন্যথা যদি (OMP_CLAUSE_CODE (*c) == OMP_CLAUSE_FIRSTPRIVATE)
		      {
			error_at (loc,
				  "iteration variable %qD should not be firstprivate",
				  OMP_CLAUSE_DECL (*c));
			*c = OMP_CLAUSE_CHAIN (*c);
		      }
		    অন্যথা
		      {
			/* Move lastprivate (decl) clause to
			   OMP_FOR_CLAUSES.  */
			বৃক্ষ l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			যদি (code == OMP_SIMD)
			  {
			    OMP_CLAUSE_CHAIN (l)
			      = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
			    cclauses[C_OMP_CLAUSE_SPLIT_FOR] = l;
			  }
			অন্যথা
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
  প্রত্যাগম ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

স্থির শূন্য
omp_split_clauses (location_t loc, গণনা বৃক্ষ_code code,
		   omp_clause_mask mask, বৃক্ষ clauses, বৃক্ষ *cclauses)
{
  পূর্ণাঙ্ক i;
  c_omp_split_clauses (loc, code, mask, clauses, cclauses);
  প্রতি (i = 0; i < C_OMP_CLAUSE_SPLIT_গুনতি; i++)
    যদি (cclauses[i])
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

স্থির বৃক্ষ
c_parser_omp_loop (location_t loc, c_parser *parser,
		   বর্ণ *p_name, omp_clause_mask mask, বৃক্ষ *cclauses,
		   তার্কিক *if_p)
{
  বৃক্ষ block, clauses, ret;

  strcat (p_name, " loop");
  mask |= OMP_LOOP_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == রিক্ত);
  যদি (cclauses)
    {
      omp_split_clauses (loc, OMP_LOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_LOOP];
    }

  block = c_begin_compound_stmt (সত্য);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, সত্য);
  add_stmt (block);

  প্রত্যাগম ret;
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

স্থির বৃক্ষ
c_parser_omp_simd (location_t loc, c_parser *parser,
		   বর্ণ *p_name, omp_clause_mask mask, বৃক্ষ *cclauses,
		   তার্কিক *if_p)
{
  বৃক্ষ block, clauses, ret;

  strcat (p_name, " simd");
  mask |= OMP_SIMD_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == রিক্ত);
  যদি (cclauses)
    {
      omp_split_clauses (loc, OMP_SIMD, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SIMD];
    }

  block = c_begin_compound_stmt (সত্য);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, সত্য);
  add_stmt (block);

  প্রত্যাগম ret;
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

স্থির বৃক্ষ
c_parser_omp_for (location_t loc, c_parser *parser,
		  বর্ণ *p_name, omp_clause_mask mask, বৃক্ষ *cclauses,
		  তার্কিক *if_p)
{
  বৃক্ষ block, clauses, ret;

  strcat (p_name, " for");
  mask |= OMP_FOR_CLAUSE_MASK;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  যদি (cclauses && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  যদি ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);

      যদি (strcmp (p, "simd") == 0)
	{
	  বৃক্ষ cclauses_buf[C_OMP_CLAUSE_SPLIT_গুনতি];
	  যদি (cclauses == রিক্ত)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  যদি (!flag_openmp)  /* flag_openmp_simd  */
	    প্রত্যাগম c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (সত্য);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, সত্য);
	  যদি (ret == NULL_বৃক্ষ)
	    প্রত্যাগম ret;
	  ret = make_গ্রন্থি (OMP_FOR);
	  বৃক্ষ_TYPE (ret) = void_type_গ্রন্থি;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
	  SET_রাশিমালা_LOCATION (ret, loc);
	  add_stmt (ret);
	  প্রত্যাগম ret;
	}
    }
  যদি (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, অসত্য);
      প্রত্যাগম NULL_বৃক্ষ;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  যদি ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINEAR);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == রিক্ত);
  যদি (cclauses)
    {
      omp_split_clauses (loc, OMP_FOR, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
    }

  block = c_begin_compound_stmt (সত্য);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, সত্য);
  add_stmt (block);

  প্রত্যাগম ret;
}

স্থির বৃক্ষ c_parser_omp_taskloop (location_t, c_parser *, বর্ণ *,
				   omp_clause_mask, বৃক্ষ *, তার্কিক *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

স্থির বৃক্ষ
c_parser_omp_master (location_t loc, c_parser *parser,
		     বর্ণ *p_name, omp_clause_mask mask, বৃক্ষ *cclauses,
		     তার্কিক *if_p, location_t master_loc)
{
  বৃক্ষ block, clauses, ret;
  gcc_rich_location richloc (loc);
  যদি (master_loc != UNKNOWN_LOCATION)
    richloc.add_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  strcat (p_name, " master");

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);

      যদি (strcmp (p, "taskloop") == 0)
	{
	  বৃক্ষ cclauses_buf[C_OMP_CLAUSE_SPLIT_গুনতি];
	  যদি (cclauses == রিক্ত)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  যদি (!flag_openmp)  /* flag_openmp_simd  */
	    প্রত্যাগম c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (সত্য);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, সত্য);
	  যদি (ret == NULL_বৃক্ষ)
	    প্রত্যাগম ret;
	  ret = c_finish_omp_master (loc, block);
	  OMP_MASTER_COMBINED (ret) = 1;
	  প্রত্যাগম ret;
	}
    }
  যদি (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, অসত্য);
      প্রত্যাগম NULL_বৃক্ষ;
    }

  যদি (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, mask, p_name, অসত্য);
      omp_split_clauses (loc, OMP_MASTER, mask, clauses, cclauses);
    }
  অন্যথা
    c_parser_skip_to_pragma_eol (parser);

  প্রত্যাগম c_finish_omp_master (loc, c_parser_omp_structured_block (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#define OMP_MASKED_CLAUSE_MASK					\
	(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FILTER)

স্থির বৃক্ষ
c_parser_omp_masked (location_t loc, c_parser *parser,
		     বর্ণ *p_name, omp_clause_mask mask, বৃক্ষ *cclauses,
		     তার্কিক *if_p)
{
  বৃক্ষ block, clauses, ret;

  strcat (p_name, " masked");
  mask |= OMP_MASKED_CLAUSE_MASK;

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);

      যদি (strcmp (p, "taskloop") == 0)
	{
	  বৃক্ষ cclauses_buf[C_OMP_CLAUSE_SPLIT_গুনতি];
	  যদি (cclauses == রিক্ত)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  যদি (!flag_openmp)  /* flag_openmp_simd  */
	    প্রত্যাগম c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (সত্য);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, সত্য);
	  যদি (ret == NULL_বৃক্ষ)
	    প্রত্যাগম ret;
	  ret = c_finish_omp_masked (loc, block,
				     cclauses[C_OMP_CLAUSE_SPLIT_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  প্রত্যাগম ret;
	}
    }
  যদি (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, অসত্য);
      প্রত্যাগম NULL_বৃক্ষ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == রিক্ত);
  যদি (cclauses)
    {
      omp_split_clauses (loc, OMP_MASKED, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_MASKED];
    }

  প্রত্যাগম c_finish_omp_masked (loc, c_parser_omp_structured_block (parser,
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

স্থির শূন্য
c_parser_omp_interop (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  বৃক্ষ clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_MASK,
					   "#pragma omp interop");
  বৃক্ষ stmt = make_গ্রন্থি (OMP_INTEROP);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  SET_রাশিমালা_LOCATION (stmt, loc);
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

স্থির তার্কিক
c_parser_omp_ordered (c_parser *parser, গণনা pragma_context context,
		      তার্কিক *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  যদি (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, অসত্য);
      প্রত্যাগম অসত্য;
    }

  পূর্ণাঙ্ক n = 1;
  যদি (c_parser_next_token_is (parser, CPP_COMMA))
    n = 2;

  যদি (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      ধ্রুব বর্ণ *p
	= IDENTIFIER_POINTER (c_parser_peek_nth_token (parser, n)->মান);

      যদি (!strcmp ("depend", p) || !strcmp ("doacross", p))
	{
	  যদি (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_to_pragma_eol (parser, অসত্য);
	      প্রত্যাগম অসত্য;
	    }
	  যদি (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_to_pragma_eol (parser, অসত্য);
	      প্রত্যাগম সত্য;
	    }

	  বৃক্ষ clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_MASK,
					"#pragma omp ordered");
	  c_finish_omp_ordered (loc, clauses, NULL_বৃক্ষ);
	  প্রত্যাগম অসত্য;
	}
    }

  বৃক্ষ clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_MASK,
					   "#pragma omp ordered");

  যদি (!flag_openmp	/* flag_openmp_simd  */
      && omp_find_clause (clauses, OMP_CLAUSE_SIMD) == NULL_বৃক্ষ)
    প্রত্যাগম অসত্য;

  c_finish_omp_ordered (loc, clauses,
			c_parser_omp_structured_block (parser, if_p));
  প্রত্যাগম সত্য;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

স্থির বৃক্ষ
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  বৃক্ষ stmt, substmt;
  তার্কিক error_suppress = অসত্য;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  যদি (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = অসত্য;
      প্রত্যাগম NULL_বৃক্ষ;
    }

  stmt = ঠেলো_stmt_list ();

  যদি (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_scan (parser, "section", সত্য))
    {
      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_গ্রন্থি, substmt);
      SET_রাশিমালা_LOCATION (substmt, loc);
      add_stmt (substmt);
    }

  যাবত্ (1)
    {
      যদি (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	ভঙ্গ;
      যদি (c_parser_next_token_is (parser, CPP_EOF))
	ভঙ্গ;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_scan (parser, "section", অসত্য);
      যদি (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser);
	  error_suppress = অসত্য;
	}
      অন্যথা যদি (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = সত্য;
	}

      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_গ্রন্থি, substmt);
      SET_রাশিমালা_LOCATION (substmt, loc);
      add_stmt (substmt);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = বের_করো_stmt_list (stmt);

  stmt = make_গ্রন্থি (OMP_SECTIONS);
  SET_রাশিমালা_LOCATION (stmt, sections_loc);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OMP_SECTIONS_BODY (stmt) = substmt;

  প্রত্যাগম add_stmt (stmt);
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

স্থির বৃক্ষ
c_parser_omp_sections (location_t loc, c_parser *parser,
		       বর্ণ *p_name, omp_clause_mask mask, বৃক্ষ *cclauses)
{
  বৃক্ষ block, clauses, ret;

  strcat (p_name, " sections");
  mask |= OMP_SECTIONS_CLAUSE_MASK;
  যদি (cclauses)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == রিক্ত);
  যদি (cclauses)
    {
      omp_split_clauses (loc, OMP_SECTIONS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SECTIONS];
    }

  block = c_begin_compound_stmt (সত্য);
  ret = c_parser_omp_sections_scope (loc, parser);
  যদি (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  block = c_end_compound_stmt (loc, block, সত্য);
  add_stmt (block);

  প্রত্যাগম ret;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_অঙ্ক_THREADS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

স্থির বৃক্ষ
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       বর্ণ *p_name, omp_clause_mask mask, বৃক্ষ *cclauses,
		       তার্কিক *if_p)
{
  বৃক্ষ stmt, clauses, block;

  strcat (p_name, " parallel");
  mask |= OMP_PARALLEL_CLAUSE_MASK;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  যদি ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  যদি (c_parser_next_token_is_keyword (parser, RID_FOR))
    {
      বৃক্ষ cclauses_buf[C_OMP_CLAUSE_SPLIT_গুনতি];
      যদি (cclauses == রিক্ত)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      যদি (!flag_openmp)  /* flag_openmp_simd  */
	প্রত্যাগম c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      block = c_begin_omp_parallel ();
      বৃক্ষ ret = c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      stmt
	= c_finish_omp_parallel (loc, cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				 block);
      যদি (ret == NULL_বৃক্ষ)
	প্রত্যাগম ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      প্রত্যাগম stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  অন্যথা যদি (cclauses
	   && (mask & (OMP_CLAUSE_MASK_1
		       << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_to_pragma_eol (parser);
      প্রত্যাগম NULL_বৃক্ষ;
    }
  অন্যথা যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      location_t ploc = c_parser_peek_token (parser)->location;
      যদি (cclauses == রিক্ত && strcmp (p, "masked") == 0)
	{
	  বৃক্ষ cclauses_buf[C_OMP_CLAUSE_SPLIT_গুনতি];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  যদি (!flag_openmp)  /* flag_openmp_simd  */
	    প্রত্যাগম c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					if_p);
	  block = c_begin_omp_parallel ();
	  বৃক্ষ ret = c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					  if_p);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  যদি (ret == রিক্ত)
	    প্রত্যাগম ret;
	  /* masked does have just filter clause, but during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel masked don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel masked
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel masked taskloop simd lastprivate (x)  */
	  যদি (OMP_MASKED_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  প্রত্যাগম stmt;
	}
      অন্যথা যদি (cclauses == রিক্ত && strcmp (p, "master") == 0)
	{
	  বৃক্ষ cclauses_buf[C_OMP_CLAUSE_SPLIT_গুনতি];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  যদি (!flag_openmp)  /* flag_openmp_simd  */
	    প্রত্যাগম c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					if_p, ploc);
	  block = c_begin_omp_parallel ();
	  বৃক্ষ ret = c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					  if_p, ploc);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  যদি (ret == রিক্ত)
	    প্রত্যাগম ret;
	  /* master doesn't have any clauses and during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel master don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel master
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel master taskloop simd lastprivate (x)  */
	  যদি (OMP_MASTER_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  প্রত্যাগম stmt;
	}
      অন্যথা যদি (strcmp (p, "loop") == 0)
	{
	  বৃক্ষ cclauses_buf[C_OMP_CLAUSE_SPLIT_গুনতি];
	  যদি (cclauses == রিক্ত)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  যদি (!flag_openmp)  /* flag_openmp_simd  */
	    প্রত্যাগম c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  বৃক্ষ ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
					if_p);
	  stmt
	    = c_finish_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				     block);
	  যদি (ret == NULL_বৃক্ষ)
	    প্রত্যাগম ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  প্রত্যাগম stmt;
	}
      অন্যথা যদি (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, অসত্য);
	  প্রত্যাগম NULL_বৃক্ষ;
	}
      অন্যথা যদি (cclauses == রিক্ত && strcmp (p, "sections") == 0)
	{
	  বৃক্ষ cclauses_buf[C_OMP_CLAUSE_SPLIT_গুনতি];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  block = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, mask, cclauses);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  প্রত্যাগম stmt;
	}
    }
  অন্যথা যদি (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, অসত্য);
      প্রত্যাগম NULL_বৃক্ষ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == রিক্ত);
  যদি (cclauses)
    {
      omp_split_clauses (loc, OMP_PARALLEL, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL];
    }

  block = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = সত্য;
  c_parser_statement (parser, if_p);
  stmt = c_finish_omp_parallel (loc, clauses, block);

  প্রত্যাগম stmt;
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

স্থির বৃক্ষ
c_parser_omp_single (location_t loc, c_parser *parser, তার্কিক *if_p)
{
  বৃক্ষ stmt = make_গ্রন্থি (OMP_SINGLE);
  SET_রাশিমালা_LOCATION (stmt, loc);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_MASK,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  প্রত্যাগম add_stmt (stmt);
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

স্থির বৃক্ষ
c_parser_omp_scope (location_t loc, c_parser *parser, তার্কিক *if_p)
{
  বৃক্ষ stmt = make_গ্রন্থি (OMP_SCOPE);
  SET_রাশিমালা_LOCATION (stmt, loc);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_MASK,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  প্রত্যাগম add_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
স্থির বৃক্ষ
c_parser_omp_dispatch_body (c_parser *parser)
{
  সংরচনা c_রাশিমালা lhs, rhs, ret;
  location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_expression (parser, রিক্ত, রিক্ত);
  যদি (বৃক্ষ_CODE (lhs.মান) == CALL_রাশিমালা)
    প্রত্যাগম lhs.মান;

  location_t op_location = c_parser_peek_token (parser)->location;
  যদি (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    প্রত্যাগম error_mark_গ্রন্থি;

  /* Parse function name.  */
  যদি (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      প্রত্যাগম error_mark_গ্রন্থি;
    }
  রাশিমালা_loc = c_parser_peek_token (parser)->location;
  বৃক্ষ id = c_parser_peek_token (parser)->মান;
  c_parser_consume_token (parser);
  যদি (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      প্রত্যাগম error_mark_গ্রন্থি;
    }

  rhs.মান = build_external_ref (রাশিমালা_loc, id, সত্য, &rhs.original_type);
  set_c_রাশিমালা_source_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_expression_after_primary (
    parser, রাশিমালা_LOC_OR_LOC (rhs.মান, রাশিমালা_loc), rhs);
  যদি (বৃক্ষ_CODE (rhs.মান) != CALL_রাশিমালা)
    {
      error_at (রাশিমালা_LOC_OR_LOC (rhs.মান, রাশিমালা_loc),
		"expected target-function call");
      প্রত্যাগম error_mark_গ্রন্থি;
    }

  /* Build assignment. */
  rhs = convert_lvalue_to_rvalue (রাশিমালা_loc, rhs, সত্য, সত্য);
  ret.মান
    = build_modify_রাশিমালা (op_location, lhs.মান, lhs.original_type, NOP_রাশিমালা,
			 রাশিমালা_loc, rhs.মান, rhs.original_type);
  ret.m_decimal = 0;
  set_c_রাশিমালা_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  ret.original_code = MODIFY_রাশিমালা;
  ret.original_type = রিক্ত;
  প্রত্যাগম ret.মান;
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

স্থির বৃক্ষ
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  বৃক্ষ stmt = make_গ্রন্থি (OMP_DISPATCH);
  SET_রাশিমালা_LOCATION (stmt, loc);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_MASK,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  বৃক্ষ depend_clauses = NULL_বৃক্ষ;
  বৃক্ষ *depend_clauses_ptr = &depend_clauses;
  প্রতি (বৃক্ষ c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  যদি (depend_clauses != NULL_বৃক্ষ)
    {
      বৃক্ষ stmt = make_গ্রন্থি (OMP_TASK);
      বৃক্ষ_TYPE (stmt) = void_গ্রন্থি;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_বৃক্ষ;
      SET_রাশিমালা_LOCATION (stmt, loc);
      add_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  বৃক্ষ dispatch_body = c_parser_omp_dispatch_body (parser);
  যদি (dispatch_body == error_mark_গ্রন্থি)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_to_end_of_block_or_statement (parser);
      প্রত্যাগম NULL_বৃক্ষ;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (বৃক্ষ_CODE (dispatch_body) == CALL_রাশিমালা
	      || বৃক্ষ_CODE (dispatch_body) == MODIFY_রাশিমালা);
  বৃক্ষ *dispatch_call = বৃক্ষ_CODE (dispatch_body) == MODIFY_রাশিমালা
			  ? &বৃক্ষ_OPERAND (dispatch_body, 1)
			  : &dispatch_body;
  যাবত্ (বৃক্ষ_CODE (*dispatch_call) == FLOAT_রাশিমালা
	 || বৃক্ষ_CODE (*dispatch_call) == CONVERT_রাশিমালা
	 || বৃক্ষ_CODE (*dispatch_call) == NOP_রাশিমালা)
    dispatch_call = &বৃক্ষ_OPERAND (*dispatch_call, 0);
  *dispatch_call = build_call_রাশিমালা_internal_loc (
    loc, IFN_GOMP_DISPATCH,
    বৃক্ষ_TYPE (বৃক্ষ_TYPE (CALL_রাশিমালা_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  প্রত্যাগম add_stmt (stmt);
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

স্থির বৃক্ষ
c_parser_omp_task (location_t loc, c_parser *parser, তার্কিক *if_p)
{
  বৃক্ষ clauses, block;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_MASK,
				      "#pragma omp task");

  block = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = সত্য;
  c_parser_statement (parser, if_p);
  প্রত্যাগম c_finish_omp_task (loc, clauses, block);
}

/* OpenMP 3.0:
   # pragma omp taskwait new-line

   OpenMP 5.0:
   # pragma omp taskwait taskwait-clause[optseq] new-line
*/

#define OMP_TASKWAIT_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

স্থির শূন্য
c_parser_omp_taskwait (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  বৃক্ষ clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_MASK,
				"#pragma omp taskwait");

  যদি (clauses)
    {
      বৃক্ষ stmt = make_গ্রন্থি (OMP_TASK);
      বৃক্ষ_TYPE (stmt) = void_গ্রন্থি;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_বৃক্ষ;
      SET_রাশিমালা_LOCATION (stmt, loc);
      add_stmt (stmt);
    }
  অন্যথা
    c_finish_omp_taskwait (loc);
}

/* OpenMP 3.1:
   # pragma omp taskyield new-line
*/

স্থির শূন্য
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

স্থির বৃক্ষ
c_parser_omp_taskgroup (location_t loc, c_parser *parser, তার্কিক *if_p)
{
  বৃক্ষ clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_MASK,
					   "#pragma omp taskgroup");

  বৃক্ষ body = c_parser_omp_structured_block (parser, if_p);
  প্রত্যাগম c_finish_omp_taskgroup (loc, body, clauses);
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

স্থির শূন্য
c_parser_omp_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);
  বৃক্ষ clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_MASK,
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

স্থির তার্কিক
c_parser_omp_cancellation_point (c_parser *parser, গণনা pragma_context context)
{
  location_t loc = c_parser_peek_token (parser)->location;
  বৃক্ষ clauses;
  তার্কিক point_seen = অসত্য;

  c_parser_consume_pragma (parser);
  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  point_seen = সত্য;
	}
    }
  যদি (!point_seen)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_to_pragma_eol (parser);
      প্রত্যাগম অসত্য;
    }

  যদি (context != pragma_compound)
    {
      যদি (context == pragma_stmt)
	error_at (loc,
		  "%<#pragma %s%> may only be used in compound statements",
		  "omp cancellation point");
      অন্যথা
	c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, অসত্য);
      প্রত্যাগম সত্য;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_POINT_CLAUSE_MASK,
				"#pragma omp cancellation point");

  c_finish_omp_cancellation_point (loc, clauses);
  প্রত্যাগম সত্য;
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

স্থির বৃক্ষ
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 বর্ণ *p_name, omp_clause_mask mask, বৃক্ষ *cclauses,
			 তার্কিক *if_p)
{
  বৃক্ষ clauses, block, ret;

  strcat (p_name, " distribute");
  mask |= OMP_DISTRIBUTE_CLAUSE_MASK;

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      তার্কিক simd = অসত্য;
      তার্কিক parallel = অসত্য;

      যদি (strcmp (p, "simd") == 0)
	simd = সত্য;
      অন্যথা
	parallel = strcmp (p, "parallel") == 0;
      যদি (parallel || simd)
	{
	  বৃক্ষ cclauses_buf[C_OMP_CLAUSE_SPLIT_গুনতি];
	  যদি (cclauses == রিক্ত)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  যদি (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      যদি (simd)
		প্রত্যাগম c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
					  if_p);
	      অন্যথা
		প্রত্যাগম c_parser_omp_parallel (loc, parser, p_name, mask,
					      cclauses, if_p);
	    }
	  block = c_begin_compound_stmt (সত্য);
	  যদি (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				     if_p);
	  অন্যথা
	    ret = c_parser_omp_parallel (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, সত্য);
	  যদি (ret == রিক্ত)
	    প্রত্যাগম ret;
	  ret = make_গ্রন্থি (OMP_DISTRIBUTE);
	  বৃক্ষ_TYPE (ret) = void_type_গ্রন্থি;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
	  SET_রাশিমালা_LOCATION (ret, loc);
	  add_stmt (ret);
	  প্রত্যাগম ret;
	}
    }
  যদি (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, অসত্য);
      প্রত্যাগম NULL_বৃক্ষ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == রিক্ত);
  যদি (cclauses)
    {
      omp_split_clauses (loc, OMP_DISTRIBUTE, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
    }

  block = c_begin_compound_stmt (সত্য);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, রিক্ত,
			       if_p);
  block = c_end_compound_stmt (loc, block, সত্য);
  add_stmt (block);

  প্রত্যাগম ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#define OMP_TEAMS_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_অঙ্ক_TEAMS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_THREAD_LIMIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

স্থির বৃক্ষ
c_parser_omp_teams (location_t loc, c_parser *parser,
		    বর্ণ *p_name, omp_clause_mask mask, বৃক্ষ *cclauses,
		    তার্কিক *if_p)
{
  বৃক্ষ clauses, block, ret;

  strcat (p_name, " teams");
  mask |= OMP_TEAMS_CLAUSE_MASK;

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp (p, "distribute") == 0)
	{
	  বৃক্ষ cclauses_buf[C_OMP_CLAUSE_SPLIT_গুনতি];
	  যদি (cclauses == রিক্ত)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  যদি (!flag_openmp)  /* flag_openmp_simd  */
	    প্রত্যাগম c_parser_omp_distribute (loc, parser, p_name, mask,
					    cclauses, if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, সত্য);
	  যদি (ret == রিক্ত)
	    প্রত্যাগম ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_গ্রন্থি (OMP_TEAMS);
	  বৃক্ষ_TYPE (ret) = void_type_গ্রন্থি;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_রাশিমালা_LOCATION (ret, loc);
	  প্রত্যাগম add_stmt (ret);
	}
      অন্যথা যদি (strcmp (p, "loop") == 0)
	{
	  বৃক্ষ cclauses_buf[C_OMP_CLAUSE_SPLIT_গুনতি];
	  যদি (cclauses == রিক্ত)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  যদি (!flag_openmp)  /* flag_openmp_simd  */
	    প্রত্যাগম c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, সত্য);
	  যদি (ret == রিক্ত)
	    প্রত্যাগম ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_গ্রন্থি (OMP_TEAMS);
	  বৃক্ষ_TYPE (ret) = void_type_গ্রন্থি;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_রাশিমালা_LOCATION (ret, loc);
	  প্রত্যাগম add_stmt (ret);
	}
    }
  যদি (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, অসত্য);
      প্রত্যাগম NULL_বৃক্ষ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == রিক্ত);
  যদি (cclauses)
    {
      omp_split_clauses (loc, OMP_TEAMS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
    }

  বৃক্ষ stmt = make_গ্রন্থি (OMP_TEAMS);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_end_compound_stmt (loc, block, সত্য);
  SET_রাশিমালা_LOCATION (stmt, loc);

  প্রত্যাগম add_stmt (stmt);
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

স্থির বৃক্ষ
c_parser_omp_target_data (location_t loc, c_parser *parser, তার্কিক *if_p)
{
  যদি (flag_openmp)
    omp_requires_mask
      = (গণনা omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  বৃক্ষ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_DATA_CLAUSE_MASK,
				"#pragma omp target data", অসত্য);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, অসত্য);
  পূর্ণাঙ্ক map_seen = 0;
  প্রতি (বৃক্ষ *pc = &clauses; *pc;)
    {
      যদি (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	বিকল্প (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  পক্ষ GOMP_MAP_TO:
	  পক্ষ GOMP_MAP_ALWAYS_TO:
	  পক্ষ GOMP_MAP_PRESENT_TO:
	  পক্ষ GOMP_MAP_ALWAYS_PRESENT_TO:
	  পক্ষ GOMP_MAP_FROM:
	  পক্ষ GOMP_MAP_ALWAYS_FROM:
	  পক্ষ GOMP_MAP_PRESENT_FROM:
	  পক্ষ GOMP_MAP_ALWAYS_PRESENT_FROM:
	  পক্ষ GOMP_MAP_TOFROM:
	  পক্ষ GOMP_MAP_ALWAYS_TOFROM:
	  পক্ষ GOMP_MAP_PRESENT_TOFROM:
	  পক্ষ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  পক্ষ GOMP_MAP_ALLOC:
	  পক্ষ GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    ভঙ্গ;
	  পক্ষ GOMP_MAP_FIRSTPRIVATE_POINTER:
	  পক্ষ GOMP_MAP_ALWAYS_POINTER:
	  পক্ষ GOMP_MAP_ATTACH_DETACH:
	  পক্ষ GOMP_MAP_ATTACH:
	    ভঙ্গ;
	  স্বভাব:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    অনুবর্ত;
	  }
      অন্যথা যদি (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_seen = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  যদি (map_seen != 3)
    {
      যদি (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      প্রত্যাগম NULL_বৃক্ষ;
    }

  বৃক্ষ stmt = make_গ্রন্থি (OMP_TARGET_DATA);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OMP_TARGET_DATA_CLAUSES (stmt) = clauses;
  keep_next_level ();
  বৃক্ষ block = c_begin_compound_stmt (সত্য);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TARGET_DATA_BODY (stmt) = c_end_compound_stmt (loc, block, সত্য);

  SET_রাশিমালা_LOCATION (stmt, loc);
  প্রত্যাগম add_stmt (stmt);
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

স্থির তার্কিক
c_parser_omp_target_update (location_t loc, c_parser *parser,
			    গণনা pragma_context context)
{
  যদি (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_to_pragma_eol (parser, অসত্য);
      প্রত্যাগম সত্য;
    }

  বৃক্ষ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_UPDATE_CLAUSE_MASK,
				"#pragma omp target update",
				/* finish_p = */ অসত্য);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  যদি (omp_find_clause (clauses, OMP_CLAUSE_TO) == NULL_বৃক্ষ
      && omp_find_clause (clauses, OMP_CLAUSE_FROM) == NULL_বৃক্ষ)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      প্রত্যাগম অসত্য;
    }

  যদি (flag_openmp)
    omp_requires_mask
      = (গণনা omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  বৃক্ষ stmt = make_গ্রন্থি (OMP_TARGET_UPDATE);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OMP_TARGET_UPDATE_CLAUSES (stmt) = clauses;
  SET_রাশিমালা_LOCATION (stmt, loc);
  add_stmt (stmt);
  প্রত্যাগম অসত্য;
}

/* OpenMP 4.5:
   # pragma omp target enter data target-data-clause[optseq] new-line  */

#define OMP_TARGET_ENTER_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

স্থির তার্কিক
c_parser_omp_target_enter_data (location_t loc, c_parser *parser,
				গণনা pragma_context context)
{
  তার্কিক data_seen = অসত্য;
  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = সত্য;
	}
    }
  যদি (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      প্রত্যাগম অসত্য;
    }

  যদি (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_to_pragma_eol (parser, অসত্য);
      প্রত্যাগম সত্য;
    }

  যদি (flag_openmp)
    omp_requires_mask
      = (গণনা omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  বৃক্ষ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_ENTER_DATA_CLAUSE_MASK,
				"#pragma omp target enter data", অসত্য);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, অসত্য);
  পূর্ণাঙ্ক map_seen = 0;
  প্রতি (বৃক্ষ *pc = &clauses; *pc;)
    {
      যদি (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	বিকল্প (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  পক্ষ GOMP_MAP_TO:
	  পক্ষ GOMP_MAP_ALWAYS_TO:
	  পক্ষ GOMP_MAP_PRESENT_TO:
	  পক্ষ GOMP_MAP_ALWAYS_PRESENT_TO:
	  পক্ষ GOMP_MAP_ALLOC:
	  পক্ষ GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    ভঙ্গ;
	  পক্ষ GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_TO);
	    map_seen = 3;
	    ভঙ্গ;
	  পক্ষ GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_TO);
	    map_seen = 3;
	    ভঙ্গ;
	  পক্ষ GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_TO);
	    map_seen = 3;
	    ভঙ্গ;
	  পক্ষ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_TO);
	    map_seen = 3;
	    ভঙ্গ;
	  পক্ষ GOMP_MAP_FIRSTPRIVATE_POINTER:
	  পক্ষ GOMP_MAP_ALWAYS_POINTER:
	  পক্ষ GOMP_MAP_ATTACH_DETACH:
	  পক্ষ GOMP_MAP_ATTACH:
	    ভঙ্গ;
	  স্বভাব:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    অনুবর্ত;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  যদি (map_seen != 3)
    {
      যদি (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      প্রত্যাগম সত্য;
    }

  বৃক্ষ stmt = make_গ্রন্থি (OMP_TARGET_ENTER_DATA);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OMP_TARGET_ENTER_DATA_CLAUSES (stmt) = clauses;
  SET_রাশিমালা_LOCATION (stmt, loc);
  add_stmt (stmt);
  প্রত্যাগম সত্য;
}

/* OpenMP 4.5:
   # pragma omp target exit data target-data-clause[optseq] new-line  */

#define OMP_TARGET_EXIT_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

স্থির তার্কিক
c_parser_omp_target_exit_data (location_t loc, c_parser *parser,
			       গণনা pragma_context context)
{
  তার্কিক data_seen = অসত্য;
  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = সত্য;
	}
    }
  যদি (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      প্রত্যাগম অসত্য;
    }

  যদি (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_to_pragma_eol (parser, অসত্য);
      প্রত্যাগম সত্য;
    }

  যদি (flag_openmp)
    omp_requires_mask
      = (গণনা omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  বৃক্ষ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_EXIT_DATA_CLAUSE_MASK,
				"#pragma omp target exit data", অসত্য);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_DATA);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_EXIT_DATA);
  c_omp_adjust_map_clauses (clauses, অসত্য);
  পূর্ণাঙ্ক map_seen = 0;
  প্রতি (বৃক্ষ *pc = &clauses; *pc;)
    {
      যদি (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	বিকল্প (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  পক্ষ GOMP_MAP_FROM:
	  পক্ষ GOMP_MAP_ALWAYS_FROM:
	  পক্ষ GOMP_MAP_PRESENT_FROM:
	  পক্ষ GOMP_MAP_ALWAYS_PRESENT_FROM:
	  পক্ষ GOMP_MAP_RELEASE:
	  পক্ষ GOMP_MAP_DELETE:
	    map_seen = 3;
	    ভঙ্গ;
	  পক্ষ GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_FROM);
	    map_seen = 3;
	    ভঙ্গ;
	  পক্ষ GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_seen = 3;
	    ভঙ্গ;
	  পক্ষ GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_FROM);
	    map_seen = 3;
	    ভঙ্গ;
	  পক্ষ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_seen = 3;
	    ভঙ্গ;
	  পক্ষ GOMP_MAP_FIRSTPRIVATE_POINTER:
	  পক্ষ GOMP_MAP_ALWAYS_POINTER:
	  পক্ষ GOMP_MAP_ATTACH_DETACH:
	  পক্ষ GOMP_MAP_DETACH:
	    ভঙ্গ;
	  স্বভাব:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target exit data%> with map-type other "
		      "than %<from%>, %<tofrom%>, %<release%> or %<delete%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    অনুবর্ত;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  যদি (map_seen != 3)
    {
      যদি (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      প্রত্যাগম সত্য;
    }

  বৃক্ষ stmt = make_গ্রন্থি (OMP_TARGET_EXIT_DATA);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OMP_TARGET_EXIT_DATA_CLAUSES (stmt) = clauses;
  SET_রাশিমালা_LOCATION (stmt, loc);
  add_stmt (stmt);
  প্রত্যাগম সত্য;
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

স্থির তার্কিক
c_parser_omp_target (c_parser *parser, গণনা pragma_context context, তার্কিক *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  বৃক্ষ *pc = রিক্ত, stmt, block, body, clauses;

  যদি (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser);
      প্রত্যাগম অসত্য;
    }

  যদি (flag_openmp)
    omp_requires_mask
      = (গণনা omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      গণনা বৃক্ষ_code ccode = ERROR_MARK;

      যদি (strcmp (p, "teams") == 0)
	ccode = OMP_TEAMS;
      অন্যথা যদি (strcmp (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      অন্যথা যদি (strcmp (p, "simd") == 0)
	ccode = OMP_SIMD;
      যদি (ccode != ERROR_MARK)
	{
	  বৃক্ষ cclauses[C_OMP_CLAUSE_SPLIT_গুনতি];
	  বর্ণ p_name[পরিমাণ ("#pragma omp target teams distribute "
			      "parallel for simd")];

	  c_parser_consume_token (parser);
	  strcpy (p_name, "#pragma omp target");
	  যদি (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      বৃক্ষ stmt;
	      বিকল্প (ccode)
		{
		পক্ষ OMP_TEAMS:
		  stmt = c_parser_omp_teams (loc, parser, p_name,
					     OMP_TARGET_CLAUSE_MASK,
					     cclauses, if_p);
		  ভঙ্গ;
		পক্ষ OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_TARGET_CLAUSE_MASK,
						cclauses, if_p);
		  ভঙ্গ;
		পক্ষ OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_TARGET_CLAUSE_MASK,
					    cclauses, if_p);
		  ভঙ্গ;
		স্বভাব:
		  gcc_unreachable ();
		}
	      প্রত্যাগম stmt != NULL_বৃক্ষ;
	    }
	  keep_next_level ();
	  বৃক্ষ block = c_begin_compound_stmt (সত্য), ret;
	  বিকল্প (ccode)
	    {
	    পক্ষ OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_TARGET_CLAUSE_MASK, cclauses,
					if_p);
	      ভঙ্গ;
	    পক্ষ OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_TARGET_CLAUSE_MASK, cclauses,
					   if_p);
	      ভঙ্গ;
	    পক্ষ OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_TARGET_CLAUSE_MASK, cclauses,
				       if_p);
	      ভঙ্গ;
	    স্বভাব:
	      gcc_unreachable ();
	    }
	  block = c_end_compound_stmt (loc, block, সত্য);
	  যদি (ret == NULL_বৃক্ষ)
	    প্রত্যাগম অসত্য;
	  যদি (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    প্রতি (বৃক্ষ c = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_অঙ্ক_TEAMS
		  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_THREAD_LIMIT)
		প্রতি (পূর্ণাঙ্ক i = 0;
		     i <= (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_অঙ্ক_TEAMS); ++i)
		  যদি (OMP_CLAUSE_OPERAND (c, i)
		      && বৃক্ষ_CODE (OMP_CLAUSE_OPERAND (c, i)) != INTEGER_CST)
		    {
		      বৃক্ষ রাশিমালা = OMP_CLAUSE_OPERAND (c, i);
		      বৃক্ষ tmp = create_tmp_var_raw (বৃক্ষ_TYPE (রাশিমালা));
		      রাশিমালা = build4 (TARGET_রাশিমালা, বৃক্ষ_TYPE (রাশিমালা), tmp,
				     রাশিমালা, NULL_বৃক্ষ, NULL_বৃক্ষ);
		      add_stmt (রাশিমালা);
		      OMP_CLAUSE_OPERAND (c, i) = রাশিমালা;
		      বৃক্ষ tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
		      cclauses[C_OMP_CLAUSE_SPLIT_TARGET] = tc;
		    }
	  বৃক্ষ stmt = make_গ্রন্থি (OMP_TARGET);
	  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
	  OMP_TARGET_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
	  c_omp_adjust_map_clauses (OMP_TARGET_CLAUSES (stmt), সত্য);
	  OMP_TARGET_BODY (stmt) = block;
	  OMP_TARGET_COMBINED (stmt) = 1;
	  SET_রাশিমালা_LOCATION (stmt, loc);
	  add_stmt (stmt);
	  pc = &OMP_TARGET_CLAUSES (stmt);
	  গচ্ছ check_clauses;
	}
      অন্যথা যদি (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, অসত্য);
	  প্রত্যাগম অসত্য;
	}
      অন্যথা যদি (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_target_data (loc, parser, if_p);
	  প্রত্যাগম সত্য;
	}
      অন্যথা যদি (strcmp (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  প্রত্যাগম c_parser_omp_target_enter_data (loc, parser, context);
	}
      অন্যথা যদি (strcmp (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  প্রত্যাগম c_parser_omp_target_exit_data (loc, parser, context);
	}
      অন্যথা যদি (strcmp (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  প্রত্যাগম c_parser_omp_target_update (loc, parser, context);
	}
    }
  যদি (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, অসত্য);
      প্রত্যাগম অসত্য;
    }

  stmt = make_গ্রন্থি (OMP_TARGET);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;

  clauses = c_parser_omp_all_clauses (parser, OMP_TARGET_CLAUSE_MASK,
				      "#pragma omp target", অসত্য);
  প্রতি (বৃক্ষ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
      {
	বৃক্ষ nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_SET_MAP_KIND (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_TARGET);
  clauses  = c_finish_omp_clauses (clauses, C_ORT_OMP_TARGET);
  c_omp_adjust_map_clauses (clauses, সত্য);

  keep_next_level ();
  block = c_begin_compound_stmt (সত্য);
  body = c_parser_omp_structured_block (parser, if_p);

  c_omp_scan_mapper_bindings (loc, &clauses, body);

  add_stmt (body);
  OMP_TARGET_CLAUSES (stmt) = clauses;
  pc = &OMP_TARGET_CLAUSES (stmt);
  OMP_TARGET_BODY (stmt) = c_end_compound_stmt (loc, block, সত্য);

  SET_রাশিমালা_LOCATION (stmt, loc);
  add_stmt (stmt);

check_clauses:
  যাবত্ (*pc)
    {
      যদি (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	বিকল্প (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  পক্ষ GOMP_MAP_TO:
	  পক্ষ GOMP_MAP_ALWAYS_TO:
	  পক্ষ GOMP_MAP_PRESENT_TO:
	  পক্ষ GOMP_MAP_ALWAYS_PRESENT_TO:
	  পক্ষ GOMP_MAP_FROM:
	  পক্ষ GOMP_MAP_ALWAYS_FROM:
	  পক্ষ GOMP_MAP_PRESENT_FROM:
	  পক্ষ GOMP_MAP_ALWAYS_PRESENT_FROM:
	  পক্ষ GOMP_MAP_TOFROM:
	  পক্ষ GOMP_MAP_ALWAYS_TOFROM:
	  পক্ষ GOMP_MAP_PRESENT_TOFROM:
	  পক্ষ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  পক্ষ GOMP_MAP_ALLOC:
	  পক্ষ GOMP_MAP_PRESENT_ALLOC:
	  পক্ষ GOMP_MAP_FIRSTPRIVATE_POINTER:
	  পক্ষ GOMP_MAP_ALWAYS_POINTER:
	  পক্ষ GOMP_MAP_POINTER:
	  পক্ষ GOMP_MAP_ATTACH_DETACH:
	  পক্ষ GOMP_MAP_ATTACH:
	    ভঙ্গ;
	  স্বভাব:
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    অনুবর্ত;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }
  cfun->has_omp_target = সত্য;
  প্রত্যাগম সত্য;
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

স্থির শূন্য
c_parser_omp_declare_simd (c_parser *parser, গণনা pragma_context context)
{
  c_token *token = c_parser_peek_token (parser);
  gcc_assert (token->type == CPP_NAME);
  বৃক্ষ kind = token->মান;
  gcc_assert (strcmp (IDENTIFIER_POINTER (kind), "simd") == 0
	      || strcmp (IDENTIFIER_POINTER (kind), "variant") == 0);

  auto_vec<c_token> clauses;
  যাবত্ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      যদি (token->type == CPP_EOF)
	{
	  c_parser_skip_to_pragma_eol (parser);
	  প্রত্যাগম;
	}
      clauses.safe_ঠেলো (*token);
      c_parser_consume_token (parser);
    }
  clauses.safe_ঠেলো (*c_parser_peek_token (parser));
  c_parser_skip_to_pragma_eol (parser);

  যাবত্ (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      যদি (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->মান != kind)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_POINTER (kind), IDENTIFIER_POINTER (kind));
	  প্রত্যাগম;
	}
      c_parser_consume_pragma (parser);
      যাবত্ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  যদি (token->type == CPP_EOF)
	    {
	      c_parser_skip_to_pragma_eol (parser);
	      প্রত্যাগম;
	    }
	  clauses.safe_ঠেলো (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_ঠেলো (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  memset (&eof_token, 0, পরিমাণ (eof_token));
  eof_token.type = CPP_EOF;
  clauses.safe_ঠেলো (eof_token);
  clauses.safe_ঠেলো (eof_token);

  বিকল্প (context)
    {
    পক্ষ pragma_external:
      যদি (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  পূর্ণাঙ্ক ext = disable_extension_diagnostics ();
	  কুরু
	    c_parser_consume_token (parser);
	  যাবত্ (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, সত্য, সত্য, সত্য, অসত্য, সত্য,
					 অসত্য, রিক্ত, &clauses);
	  restore_extension_diagnostics (ext);
	}
      অন্যথা
	c_parser_declaration_or_fndef (parser, সত্য, সত্য, সত্য, অসত্য, সত্য,
				       অসত্য, রিক্ত, &clauses);
      ভঙ্গ;
    পক্ষ pragma_struct:
    পক্ষ pragma_param:
    পক্ষ pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      ভঙ্গ;
    পক্ষ pragma_compound:
      তার্কিক have_std_attrs;
      বৃক্ষ std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
      যদি (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      অন্যথা
	std_attrs = NULL_বৃক্ষ;
      যদি (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  পূর্ণাঙ্ক ext = disable_extension_diagnostics ();
	  কুরু
	    c_parser_consume_token (parser);
	  যাবত্ (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  যদি (c_parser_next_tokens_start_declaration (parser)
	      || c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, সত্য, সত্য, সত্য, সত্য,
					     সত্য, অসত্য, রিক্ত, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      ভঙ্গ;
	    }
	  restore_extension_diagnostics (ext);
	}
      অন্যথা যদি (c_parser_next_tokens_start_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, সত্য, সত্য, সত্য, সত্য, সত্য,
					 অসত্য, রিক্ত, &clauses, have_std_attrs,
					 std_attrs);
	  ভঙ্গ;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      ভঙ্গ;
    স্বভাব:
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

স্থির বৃক্ষ
c_parser_omp_context_selector (c_parser *parser, গণনা omp_tss_code set,
			       বৃক্ষ parms)
{
  বৃক্ষ ret = NULL_বৃক্ষ;
  কুরু
    {
      বৃক্ষ selector;
      যদি (c_parser_next_token_is (parser, CPP_KEYWORD)
	  || c_parser_next_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->মান;
      অন্যথা
	{
	  c_parser_error (parser, "expected trait selector name");
	  প্রত্যাগম error_mark_গ্রন্থি;
	}
      গণনা omp_ts_code sel
	= omp_lookup_ts_code (set, IDENTIFIER_POINTER (selector));

      যদি (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_POINTER (selector),  omp_tss_map[set]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_বৃক্ষ, NULL_বৃক্ষ, ret);
	  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_balanced_token_sequence (parser);
	  যদি (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      অনুবর্ত;
	    }
	  অন্যথা
	    ভঙ্গ;
	}

      c_parser_consume_token (parser);

      বৃক্ষ properties = NULL_বৃক্ষ;
      বৃক্ষ scoreval = NULL_বৃক্ষ;
      গণনা omp_tp_type property_kind = omp_ts_map[sel].tp_type;
      তার্কিক allow_score = omp_ts_map[sel].allow_score;
      বৃক্ষ t;

      যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  যদি (property_kind == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_POINTER (selector));
	      প্রত্যাগম error_mark_গ্রন্থি;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  যদি (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER (token->মান), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      বৃক্ষ score = c_parser_রাশিমালা_no_commas (parser, রিক্ত).মান;
	      parens2.skip_until_found_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      যদি (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[set]);
	      অন্যথা যদি (score != error_mark_গ্রন্থি)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, অসত্য, রিক্ত);
		  যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (score))
		      || বৃক্ষ_CODE (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  অন্যথা যদি (বৃক্ষ_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  অন্যথা
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  বিকল্প (property_kind)
	    {
	    পক্ষ OMP_TRAIT_PROPERTY_ID:
	      যদি (c_parser_next_token_is (parser, CPP_KEYWORD)
		  || c_parser_next_token_is (parser, CPP_NAME))
		{
		  বৃক্ষ prop = c_parser_peek_token (parser)->মান;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_বৃক্ষ,
						    properties);
		}
	      অন্যথা
		{
		  c_parser_error (parser, "expected identifier");
		  প্রত্যাগম error_mark_গ্রন্থি;
		}
	      ভঙ্গ;
	    পক্ষ OMP_TRAIT_PROPERTY_NAME_LIST:
	      কুরু
		{
		  বৃক্ষ prop = OMP_TP_NAMELIST_গ্রন্থি;
		  বৃক্ষ মান = NULL_বৃক্ষ;
		  যদি (c_parser_next_token_is (parser, CPP_KEYWORD)
		      || c_parser_next_token_is (parser, CPP_NAME))
		    {
		      মান = c_parser_peek_token (parser)->মান;
		      c_parser_consume_token (parser);
		    }
		  অন্যথা যদি (c_parser_next_token_is (parser, CPP_STRING))
		    মান = c_parser_string_literal (parser, অসত্য,
						     অসত্য).মান;
		  অন্যথা
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      প্রত্যাগম error_mark_গ্রন্থি;
		    }

		  properties = make_trait_property (prop, মান, properties);

		  যদি (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  অন্যথা
		    ভঙ্গ;
		}
	      যাবত্ (1);
	      ভঙ্গ;
	    পক্ষ OMP_TRAIT_PROPERTY_DEV_অঙ্ক_রাশিমালা:
	    পক্ষ OMP_TRAIT_PROPERTY_BOOL_রাশিমালা:
	      {
		c_রাশিমালা texpr = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
		texpr = convert_lvalue_to_rvalue (token->location, texpr,
						  সত্য, সত্য);
		t = texpr.মান;
	      }
	      যদি (t == error_mark_গ্রন্থি)
		প্রত্যাগম error_mark_গ্রন্থি;
	      mark_exp_read (t);
	      যদি (property_kind == OMP_TRAIT_PROPERTY_BOOL_রাশিমালা)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_গ্রন্থি);
		  যদি (t == error_mark_গ্রন্থি)
		    প্রত্যাগম error_mark_গ্রন্থি;
		}
	      অন্যথা যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  প্রত্যাগম error_mark_গ্রন্থি;
		}
	      t = c_fully_fold (t, অসত্য, রিক্ত);
	      properties = make_trait_property (NULL_বৃক্ষ, t, properties);
	      ভঙ্গ;
	    পক্ষ OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      যদি (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  যদি (parms == NULL_বৃক্ষ)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      প্রত্যাগম error_mark_গ্রন্থি;
		    }
		  বৃক্ষ c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_MASK,
						"simd", সত্য, 2);
		  c = c_omp_declare_simd_clauses_to_numbers (parms
							     == error_mark_গ্রন্থি
							     ? NULL_বৃক্ষ : parms,
							     c);
		  properties = c;
		}
	      অন্যথা যদি (sel == OMP_TRAIT_IMPLEMENTATION_REQUIRES)
		{
		  /* FIXME: The "requires" selector was added in OpenMP 5.1.
		     Currently only the now-deprecated syntax
		     from OpenMP 5.0 is supported.  */
		  sorry_at (token->location,
			    "%<requires%> selector is not supported yet");
		  প্রত্যাগম error_mark_গ্রন্থি;
		}
	      অন্যথা
		gcc_unreachable ();
	      ভঙ্গ;
	    স্বভাব:
	      gcc_unreachable ();
	    }

	  parens.skip_until_found_close (parser);
	  properties = nreverse (properties);
	}
      অন্যথা যদি (property_kind != OMP_TRAIT_PROPERTY_NONE
	       && property_kind != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_kind != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  প্রত্যাগম error_mark_গ্রন্থি;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      যদি (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      অন্যথা
	ভঙ্গ;
    }
  যাবত্ (1);

  প্রত্যাগম nreverse (ret);
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

স্থির বৃক্ষ
c_parser_omp_context_selector_specification (c_parser *parser, বৃক্ষ parms)
{
  বৃক্ষ ret = NULL_বৃক্ষ;
  কুরু
    {
      ধ্রুব বর্ণ *setp = "";
      যদি (c_parser_next_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      গণনা omp_tss_code set = omp_lookup_tss_code (setp);

      যদি (set == OMP_TRAIT_SET_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  প্রত্যাগম error_mark_গ্রন্থি;
	}

      c_parser_consume_token (parser);

      যদি (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	প্রত্যাগম error_mark_গ্রন্থি;

      matching_braces braces;
      যদি (!braces.require_open (parser))
	প্রত্যাগম error_mark_গ্রন্থি;

      বৃক্ষ selectors = c_parser_omp_context_selector (parser, set, parms);
      যদি (selectors == error_mark_গ্রন্থি)
	{
	  c_parser_skip_to_closing_brace (parser);
	  ret = error_mark_গ্রন্থি;
	}
      অন্যথা যদি (ret != error_mark_গ্রন্থি)
	ret = make_trait_set_selector (set, selectors, ret);

      braces.require_close (parser);

      যদি (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      অন্যথা
	ভঙ্গ;
    }
  যাবত্ (1);

  যদি (ret == error_mark_গ্রন্থি)
    প্রত্যাগম ret;
  প্রত্যাগম nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

স্থির শূন্য
c_finish_omp_declare_variant (c_parser *parser, বৃক্ষ fndecl, বৃক্ষ parms)
{
  matching_parens parens;
  যদি (!parens.require_open (parser))
    {
     fail:
      c_parser_skip_to_pragma_eol (parser, অসত্য);
      প্রত্যাগম;
    }

  যদি (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      গচ্ছ fail;
    }

  c_token *token = c_parser_peek_token (parser);
  বৃক্ষ variant = lookup_name (token->মান);

  যদি (variant == NULL_বৃক্ষ)
    {
      undeclared_variable (token->location, token->মান);
      variant = error_mark_গ্রন্থি;
    }
  অন্যথা যদি (বৃক্ষ_CODE (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_গ্রন্থি;
    }
  অন্যথা যদি (fndecl_built_in_p (variant)
	   && (strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			"__builtin_", strlen ("__builtin_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__sync_", strlen ("__sync_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__atomic_", strlen ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_গ্রন্থি;
    }
  অন্যথা যদি (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_গ্রন্থি;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  বৃক্ষ append_args_বৃক্ষ = NULL_বৃক্ষ;
  বৃক্ষ append_args_last;
  vec<বৃক্ষ> adjust_args_list = vNULL;
  তার্কিক has_match = অসত্য, has_adjust_args = অসত্য;
  location_t adjust_args_loc = UNKNOWN_LOCATION;
  location_t append_args_loc = UNKNOWN_LOCATION;
  location_t match_loc = UNKNOWN_LOCATION;
  বৃক্ষ need_device_ptr_list = NULL_বৃক্ষ;
  বৃক্ষ ctx = error_mark_গ্রন্থি;

  কুরু
    {
      যদি (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ধ্রুব বর্ণ *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      যদি (c_parser_next_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);

      গণনা clause
      {
	match,
	adjust_args,
	append_args
      } ccode;

      যদি (strcmp (clause, "match") == 0)
	{
	  ccode = match;
	  match_loc = loc;
	}
      অন্যথা যদি (strcmp (clause, "adjust_args") == 0)
	{
	  ccode = adjust_args;
	  adjust_args_loc = loc;
	}
      অন্যথা যদি (strcmp (clause, "append_args") == 0)
	{
	  ccode = append_args;
	  append_args_loc = loc;
	}
      অন্যথা
	{
	  c_parser_error (parser, "expected %<match%>, %<adjust_args%> or "
				  "%<append_args%> clause");
	  গচ্ছ fail;
	}

      c_parser_consume_token (parser);

      যদি (!parens.require_open (parser))
	গচ্ছ fail;

      যদি (parms == NULL_বৃক্ষ)
	parms = error_mark_গ্রন্থি;

      যদি (ccode == match)
	{
	  যদি (has_match)
	    error_at (match_loc, "too many %<match%> clauses");
	  has_match = সত্য;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  যদি (ctx == error_mark_গ্রন্থি)
	    গচ্ছ fail;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  যদি (ctx != error_mark_গ্রন্থি
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      বৃক্ষ outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      অন্যথা যদি (ccode == adjust_args)
	{
	  has_adjust_args = সত্য;
	  যদি (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      ধ্রুব বর্ণ *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
	      যদি (strcmp (p, "need_device_ptr") == 0
		  || strcmp (p, "nothing") == 0)
		{
		  c_parser_consume_token (parser); // need_device_ptr
		  c_parser_consume_token (parser); // :

		  loc = c_parser_peek_token (parser)->location;
		  বৃক্ষ list
		    = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ERROR,
						  NULL_বৃক্ষ);

		  বৃক্ষ arg;
		  যদি (variant != error_mark_গ্রন্থি)
		    প্রতি (বৃক্ষ c = list; c != NULL_বৃক্ষ; c = বৃক্ষ_CHAIN (c))
		      {
			বৃক্ষ decl = বৃক্ষ_PURPOSE (c);
			location_t arg_loc = রাশিমালা_LOCATION (বৃক্ষ_মান (c));
			পূর্ণাঙ্ক idx;
			প্রতি (arg = parms, idx = 0; arg != রিক্ত;
			     arg = বৃক্ষ_CHAIN (arg), idx++)
			  যদি (arg == decl)
			    ভঙ্গ;
			যদি (arg == NULL_বৃক্ষ)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    গচ্ছ fail;
			  }
			যদি (adjust_args_list.contains (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    গচ্ছ fail;
			  }
			যদি (strcmp (p, "need_device_ptr") == 0
			    && বৃক্ষ_CODE (বৃক্ষ_TYPE (arg)) != POINTER_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    গচ্ছ fail;
			  }
			adjust_args_list.safe_ঠেলো (arg);
			যদি (strcmp (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_বৃক্ষ_list (
				NULL_বৃক্ষ,
				build_int_cst (
				  integer_type_গ্রন্থি,
				  idx))); // Store 0-based argument index,
					  // as in gimplify_call_expr
			  }
		      }
		}
	      অন্যথা
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %<nothing%> or %<need_device_ptr%>");
		  যদি (strcmp (p, "need_device_addr") == 0)
		    inform (c_parser_peek_token (parser)->location,
			    "%<need_device_addr%> is not valid for C");
		  গচ্ছ fail;
		}
	    }
	  অন্যথা
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected %<nothing%> or %<need_device_ptr%> "
			"followed by %<:%>");
	      গচ্ছ fail;
	    }
	}
      অন্যথা যদি (ccode == append_args)
	{
	  যদি (append_args_বৃক্ষ)
	    {
	      error_at (append_args_loc, "too many %qs clauses", "append_args");
	      append_args_বৃক্ষ = NULL_বৃক্ষ;
	    }
	  কুরু
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      যদি (!c_parser_next_token_is (parser, CPP_NAME)
		  || strcmp ("interop",
			     IDENTIFIER_POINTER (
			       c_parser_peek_token (parser)->মান)))
		{
		  error_at (loc, "expected %<interop%>");
		  গচ্ছ fail;
		}
	      c_parser_consume_token (parser);

	      যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		গচ্ছ fail;
	      তার্কিক target = অসত্য;
	      তার্কিক targetsync = অসত্য;
	      বৃক্ষ prefer_type_বৃক্ষ = NULL_বৃক্ষ;
	      যদি (!c_parser_omp_clause_init_modifiers (parser, &target,
						       &targetsync,
						       &prefer_type_বৃক্ষ)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		গচ্ছ fail;
	      যদি (!target && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      বৃক্ষ t = build_বৃক্ষ_list (target ? boolean_true_গ্রন্থি
					       : boolean_false_গ্রন্থি,
					targetsync ? boolean_true_গ্রন্থি
						   : boolean_false_গ্রন্থি);
	      t = build1_loc (loc, NOP_রাশিমালা, void_type_গ্রন্থি, t);
	      t = build_বৃক্ষ_list (t, prefer_type_বৃক্ষ);
	      যদি (append_args_বৃক্ষ)
		{
		  বৃক্ষ_CHAIN (append_args_last) = t;
		  append_args_last = t;
		}
	      অন্যথা
		append_args_বৃক্ষ = append_args_last = t;
	      যদি (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		ভঙ্গ;
	      যদি (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		গচ্ছ fail;
	    }
	  যাবত্ (সত্য);
	}

      parens.require_close (parser);
  } যাবত্ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL));
  যদি (variant != error_mark_গ্রন্থি && !has_match)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_গ্রন্থি;
    }
  c_parser_skip_to_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  যদি (variant == error_mark_গ্রন্থি || ctx == error_mark_গ্রন্থি)
    /* Previously diagnosed error.  */
    প্রত্যাগম;

  যদি ((has_adjust_args || append_args_বৃক্ষ)
      && !omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_args ? adjust_args_loc : append_args_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_args ? "adjust_args" : "append_args");
      প্রত্যাগম;
    }

  যদি (!omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      বৃক্ষ base_type = বৃক্ষ_TYPE (fndecl);
      বৃক্ষ variant_type = বৃক্ষ_TYPE (variant);
      তার্কিক unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_বৃক্ষ
	   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type));

      যদি (append_args_বৃক্ষ
	  && TYPE_ARG_TYPES (base_type) == NULL_বৃক্ষ
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
	  প্রত্যাগম;
	}
      অন্যথা যদি (append_args_বৃক্ষ)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  পূর্ণাঙ্ক nappend_args = 0;
	  পূর্ণাঙ্ক nbase_args = 0;
	  প্রতি (বৃক্ষ t = TYPE_ARG_TYPES (base_type);
	       t && বৃক্ষ_মান (t) != void_type_গ্রন্থি; t = বৃক্ষ_CHAIN (t))
	    nbase_args++;
	  প্রতি (বৃক্ষ t = append_args_বৃক্ষ; t; t = বৃক্ষ_CHAIN (t))
	    nappend_args++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_args_বৃক্ষ = build_বৃক্ষ_list (build_int_cst (integer_type_গ্রন্থি,
							     nbase_args),
					      append_args_বৃক্ষ);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  যদি (!unprototyped_variant)
	    {
	      বৃক্ষ args = TYPE_ARG_TYPES (variant_type);
	      প্রতি (পূর্ণাঙ্ক i = 0; args && i < nbase_args;
		   i++, args = বৃক্ষ_CHAIN (args))
		;
	      প্রতি (পূর্ণাঙ্ক i = 0; i < nappend_args; i++, args = বৃক্ষ_CHAIN (args))
		যদি (!args || !c_omp_interop_t_p (বৃক্ষ_মান (args)))
		  {
		    error_at (DECL_SOURCE_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_args + i + 1, variant);
		    inform (append_args_loc,
			    "%<append_args%> specified here");
		    প্রত্যাগম;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  বৃক্ষ args = TYPE_ARG_TYPES (base_type);
	  বৃক্ষ newargs = NULL_বৃক্ষ;
	  বৃক্ষ lastarg = NULL_বৃক্ষ;
	  প্রতি (পূর্ণাঙ্ক j = 0; j < nbase_args; j++, args = বৃক্ষ_CHAIN (args))
	    {
	      বৃক্ষ t = বৃক্ষ_cons (বৃক্ষ_PURPOSE (args),
				  বৃক্ষ_মান (args), NULL_বৃক্ষ);
	      যদি (lastarg)
		বৃক্ষ_CHAIN (lastarg) = t;
	      অন্যথা
		newargs = t;
	      lastarg = t;
	    }
	  বৃক্ষ type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? বৃক্ষ_TYPE (type) : pointer_sized_int_গ্রন্থি;
	  প্রতি (পূর্ণাঙ্ক j = 0; j < nappend_args; j++)
	    {
	      বৃক্ষ t = বৃক্ষ_cons (NULL_বৃক্ষ, type, NULL_বৃক্ষ);
	      যদি (lastarg)
		বৃক্ষ_CHAIN (lastarg) = t;
	      অন্যথা
		newargs = t;
	      lastarg = t;
	    }
	  বৃক্ষ_CHAIN (lastarg) = args;

	  /* Temporarily stuff newargs into the original base_type.  */
	  বৃক্ষ saveargs = TYPE_ARG_TYPES (base_type);
	  TYPE_ARG_TYPES (base_type) = newargs;
	  তার্কিক fail = !comptypes (base_type, variant_type);
	  TYPE_ARG_TYPES (base_type) = saveargs;

	  যদি (fail)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      প্রত্যাগম;
	    }
	  অন্যথা যদি (unprototyped_variant)
	    /* If we've got an unprototyped variant, copy the transformed
	       base arg types to the variant.  This is needed later by
	       modify_call_for_omp_dispatch.  */
	    TYPE_ARG_TYPES (variant_type) = newargs;
	}
      অন্যথা  /* No append_args present.  */
	{
	  যদি (!comptypes (base_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      প্রত্যাগম;
	    }
	  অন্যথা যদি (TYPE_ARG_TYPES (variant_type) == NULL_বৃক্ষ
		   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (base_type) != NULL_বৃক্ষ)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (base_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_USED (variant) = 1;
  বৃক্ষ construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (match_loc, variant, construct);
  যদি (omp_context_selector_matches (ctx, NULL_বৃক্ষ, অসত্য))
    {
      বৃক্ষ attr = বৃক্ষ_cons (get_identifier ("omp declare variant base"),
			     build_বৃক্ষ_list (variant, ctx),
			     DECL_ATTRIBUTES (fndecl));
      DECL_ATTRIBUTES (fndecl) = attr;
    }

  যদি (need_device_ptr_list || append_args_বৃক্ষ)
    {
      বৃক্ষ variant_decl = বৃক্ষ_strip_nop_conversions (variant);
      বৃক্ষ t = build_বৃক্ষ_list (need_device_ptr_list,
				NULL_বৃক্ষ /* need_device_addr */);
      বৃক্ষ_CHAIN (t) = append_args_বৃক্ষ;
      DECL_ATTRIBUTES (variant_decl)
	= বৃক্ষ_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_ATTRIBUTES (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

স্থির শূন্য
c_finish_omp_declare_simd (c_parser *parser, বৃক্ষ fndecl, বৃক্ষ parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  যদি (clauses.exists () && clauses[0].type == CPP_EOF)
    প্রত্যাগম;
  ধ্রুব বর্ণ *kind = "simd";
  যদি (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    kind = IDENTIFIER_POINTER (clauses[0].মান);
  gcc_assert (strcmp (kind, "simd") == 0 || strcmp (kind, "variant") == 0);
  যদি (fndecl == NULL_বৃক্ষ || বৃক্ষ_CODE (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      প্রত্যাগম;
    }
  যদি (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      প্রত্যাগম;
    }
  যদি (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", kind);
      প্রত্যাগম;
    }

  যদি (parms == NULL_বৃক্ষ)
    parms = DECL_ARGUMENTS (fndecl);

  unsigned পূর্ণাঙ্ক tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);

  parser->tokens = clauses.address ();
  parser->tokens_avail = clauses.length ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  যাবত্ (parser->tokens_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      kind = IDENTIFIER_POINTER (token->মান);
      c_parser_consume_token (parser);
      parser->in_pragma = সত্য;

      যদি (strcmp (kind, "simd") == 0)
	{
	  বৃক্ষ c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_MASK,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_to_numbers (parms, c);
	  যদি (c != NULL_বৃক্ষ)
	    c = বৃক্ষ_cons (NULL_বৃক্ষ, c, NULL_বৃক্ষ);
	  c = build_বৃক্ষ_list (get_identifier ("omp declare simd"), c);
	  বৃক্ষ_CHAIN (c) = DECL_ATTRIBUTES (fndecl);
	  DECL_ATTRIBUTES (fndecl) = c;
	}
      অন্যথা
	{
	  gcc_assert (strcmp (kind, "variant") == 0);
	  c_finish_omp_declare_variant (parser, fndecl, parms);
	}
    }

  parser->tokens = &parser->tokens_buf[0];
  parser->tokens_avail = tokens_avail;
  যদি (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#যদি !defined (NO_DOT_IN_LABEL)
#define JOIN_STR "."
#নোচেদ্যদি !defined (NO_DOLLAR_IN_LABEL)
#define JOIN_STR "$"
#অন্যথা
#define JOIN_STR "_"
#endif

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
স্থির বৃক্ষ
omp_start_variant_function (c_declarator *declarator, বৃক্ষ ctx)
{
  c_declarator *id = declarator;
  যাবত্ (id->kind != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  বৃক্ষ name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  প্রত্যাগম name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
স্থির শূন্য
omp_finish_variant_function (বৃক্ষ decl, বৃক্ষ base_name, বৃক্ষ ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  বৃক্ষ base_decl = lookup_name (base_name);
  যদি (base_decl == error_mark_গ্রন্থি)
    base_decl = NULL_বৃক্ষ;
  যদি (!base_decl)
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_POINTER (base_name));
      প্রত্যাগম;
    }

  যদি (!comptypes (বৃক্ষ_TYPE (decl), বৃক্ষ_TYPE (base_decl)))
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", base_decl);
      inform (DECL_SOURCE_LOCATION (base_decl),
	      "%qE declared here", base_decl);
      প্রত্যাগম;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_SOURCE_LOCATION (decl),
				   base_decl, ctx);
  বৃক্ষ construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (DECL_SOURCE_LOCATION (decl), decl, construct);
  বৃক্ষ attrs = DECL_ATTRIBUTES (base_decl);
  বৃক্ষ match_loc_গ্রন্থি
    = maybe_wrap_with_location (integer_zero_গ্রন্থি,
				DECL_SOURCE_LOCATION (base_decl));
  বৃক্ষ loc_গ্রন্থি = বৃক্ষ_cons (match_loc_গ্রন্থি, integer_zero_গ্রন্থি,
			     build_বৃক্ষ_list (match_loc_গ্রন্থি,
					      integer_zero_গ্রন্থি));
  attrs = বৃক্ষ_cons (get_identifier ("omp declare variant base"),
		     বৃক্ষ_cons (decl, ctx, loc_গ্রন্থি), attrs);
  DECL_ATTRIBUTES (base_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  বৃক্ষ_PUBLIC (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

তার্কিক
c_maybe_parse_omp_decl (বৃক্ষ decl, বৃক্ষ d)
{
  gcc_assert (বৃক্ষ_CODE (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
  c_token *first = toks->address ();
  c_token *last = first + toks->length ();
  ধ্রুব বর্ণ *directive[3] = {};
  প্রতি (পূর্ণাঙ্ক j = 0; j < 3; j++)
    {
      বৃক্ষ id = NULL_বৃক্ষ;
      যদি (first + j == last)
	ভঙ্গ;
      যদি (first[j].type == CPP_NAME)
	id = first[j].মান;
      অন্যথা যদি (first[j].type == CPP_KEYWORD)
	id = ridpointers[(পূর্ণাঙ্ক) first[j].keyword];
      অন্যথা
	ভঙ্গ;
      directive[j] = IDENTIFIER_POINTER (id);
    }
  ধ্রুব c_omp_directive *dir = রিক্ত;
  যদি (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  যদি (dir == রিক্ত)
    {
      error_at (first->location,
		"unknown OpenMP directive name in "
		"%qs attribute argument", "omp::decl");
      প্রত্যাগম অসত্য;
    }
  যদি (dir->id != PRAGMA_OMP_THREADPRIVATE
      && dir->id != PRAGMA_OMP_GROUPPRIVATE
      && dir->id != PRAGMA_OMP_ALLOCATE
      && (dir->id != PRAGMA_OMP_DECLARE
	  || strcmp (directive[1], "target") != 0))
    প্রত্যাগম অসত্য;

  যদি (!flag_openmp && !dir->simd)
    প্রত্যাগম সত্য;

  c_parser *parser = the_parser;
  unsigned পূর্ণাঙ্ক tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);
  toks = রিক্ত;
  vec_safe_reserve (toks, last - first + 2, সত্য);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_kind = pragma_kind (dir->id);
  tok.location = first->location;
  toks->quick_ঠেলো (tok);
  যাবত্ (++first < last)
    toks->quick_ঠেলো (*first);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_ঠেলো (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_ঠেলো (tok);
  parser->in_omp_decl_attribute = decl;
  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = toks->length ();
  c_parser_pragma (parser, pragma_external, রিক্ত, NULL_বৃক্ষ);
  parser->in_omp_decl_attribute = NULL_বৃক্ষ;
  প্রত্যাগম সত্য;
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

স্থির শূন্য
c_parser_omp_declare_target (c_parser *parser)
{
  বৃক্ষ clauses = NULL_বৃক্ষ;
  পূর্ণাঙ্ক device_type = 0;
  তার্কিক indirect = অসত্য;
  তার্কিক only_device_type_or_indirect = সত্য;
  যদি (flag_openmp)
    omp_requires_mask
      = (গণনা omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);
  যদি (c_parser_next_token_is (parser, CPP_NAME)
      || (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp declare target");
  অন্যথা যদি (parser->in_omp_decl_attribute
	   || c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      clauses = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					      clauses);
      clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
      c_parser_skip_to_pragma_eol (parser);
    }
  অন্যথা
    {
      warning_at (c_parser_peek_token (parser)->location,
		  OPT_Wdeprecated_openmp,
		  "use of %<omp declare target%> as a synonym for "
		  "%<omp begin declare target%> has been deprecated since "
		  "OpenMP 5.2");
      তার্কিক attr_syntax = parser->in_omp_attribute_pragma != রিক্ত;
      c_parser_skip_to_pragma_eol (parser);
      c_omp_declare_target_attr attr = { attr_syntax, -1, 0 };
      vec_safe_ঠেলো (current_omp_declare_target_attribute, attr);
      প্রত্যাগম;
    }
  প্রতি (বৃক্ষ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_রাশিমালা (c));
    }
  প্রতি (বৃক্ষ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	অনুবর্ত;
      বৃক্ষ t = OMP_CLAUSE_DECL (c), id;
      বৃক্ষ at1 = lookup_attribute ("omp declare target", DECL_ATTRIBUTES (t));
      বৃক্ষ at2 = lookup_attribute ("omp declare target link",
				   DECL_ATTRIBUTES (t));
      only_device_type_or_indirect = অসত্য;
      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::swap (at1, at2);
	}
      অন্যথা
	id = get_identifier ("omp declare target");
      যদি (at2)
	{
	  যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	  অন্যথা যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL
		   || মান_member (get_identifier ("local"), বৃক্ষ_মান (at2)))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<local%> clauses", t);
	  অন্যথা
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<to%> or %<enter%> clauses", t);
	  অনুবর্ত;
	}
      যদি (!at1)
	{
	  DECL_ATTRIBUTES (t) = বৃক্ষ_cons (id, NULL_বৃক্ষ, DECL_ATTRIBUTES (t));
	  যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    বৃক্ষ_মান (DECL_ATTRIBUTES (t))
	      = বৃক্ষ_cons (NULL_বৃক্ষ, get_identifier ("local"),
			   বৃক্ষ_মান (DECL_ATTRIBUTES (t)));

	  যদি (বৃক্ষ_CODE (t) != FUNCTION_DECL && !is_global_var (t))
	    অনুবর্ত;

	  symtab_গ্রন্থি *গ্রন্থি = symtab_গ্রন্থি::get (t);
	  যদি (গ্রন্থি != রিক্ত)
	    {
	      গ্রন্থি->offloadable = 1;
	      যদি (ENABLE_OFFLOADING)
		{
		  g->have_offload = সত্য;
		  যদি (is_a <varpool_গ্রন্থি *> (গ্রন্থি)
		      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_LOCAL)
		    vec_safe_ঠেলো (offload_vars, t);
		}
	    }
	}
      অন্যথা
	{
	  তার্কিক saw_local = মান_member (get_identifier ("local"),
					 বৃক্ষ_মান (at1));
	  যদি (saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	      অনুবর্ত;
	    }
	  অন্যথা যদি (!saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      অনুবর্ত;
	    }
	}
      যদি (বৃক্ষ_CODE (t) != FUNCTION_DECL)
	অনুবর্ত;
      যদি ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  বৃক্ষ at3 = lookup_attribute ("omp declare target host",
				       DECL_ATTRIBUTES (t));
	  যদি (at3 == NULL_বৃক্ষ)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_ATTRIBUTES (t)
		= বৃক্ষ_cons (id, NULL_বৃক্ষ, DECL_ATTRIBUTES (t));
	    }
	}
      যদি ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  বৃক্ষ at3 = lookup_attribute ("omp declare target nohost",
				       DECL_ATTRIBUTES (t));
	  যদি (at3 == NULL_বৃক্ষ)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_ATTRIBUTES (t)
		= বৃক্ষ_cons (id, NULL_বৃক্ষ, DECL_ATTRIBUTES (t));
	    }
	}
      যদি (indirect)
	{
	  বৃক্ষ at4 = lookup_attribute ("omp declare target indirect",
				       DECL_ATTRIBUTES (t));
	  যদি (at4 == NULL_বৃক্ষ)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_ATTRIBUTES (t)
		= বৃক্ষ_cons (id, NULL_বৃক্ষ, DECL_ATTRIBUTES (t));
	    }
	}
    }
  যদি ((device_type || indirect) && only_device_type_or_indirect)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  যদি (indirect && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
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

স্থির শূন্য
c_parser_omp_begin (c_parser *parser)
{
  ধ্রুব বর্ণ *p = "";
  c_parser_consume_pragma (parser);
  যদি (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
  যদি (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      যদি (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  তার্কিক attr_syntax = parser->in_omp_attribute_pragma != রিক্ত;
	  বৃক্ষ clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp begin declare target");
	  পূর্ণাঙ্ক device_type = 0;
	  পূর্ণাঙ্ক indirect = 0;
	  প্রতি (বৃক্ষ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
	      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
		indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_রাশিমালা (c));
	    }
	  c_omp_declare_target_attr attr = { attr_syntax, device_type,
					     indirect };
	  vec_safe_ঠেলো (current_omp_declare_target_attribute, attr);
	}
      অন্যথা যদি (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  ধ্রুব বর্ণ *clause = "";
	  matching_parens parens;
	  location_t match_loc = c_parser_peek_token (parser)->location;
	  যদি (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  যদি (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      বৃক্ষ id = c_parser_peek_token (parser)->মান;
	      clause = IDENTIFIER_POINTER (id);
	    }
	  যদি (strcmp (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_to_pragma_eol (parser);
	      প্রত্যাগম;
	    }

	  c_parser_consume_token (parser);

	  যদি (!parens.require_open (parser))
	    {
	      c_parser_skip_to_pragma_eol (parser, অসত্য);
	      প্রত্যাগম;
	    }

	  বৃক্ষ ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_বৃক্ষ);
	  যদি (ctx != error_mark_গ্রন্থি)
	    ctx = omp_check_context_selector (match_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  যদি (ctx != error_mark_গ্রন্থি
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      বৃক্ষ outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  যদি (ctx == error_mark_গ্রন্থি
	      || !omp_context_selector_matches (ctx, NULL_বৃক্ষ, অসত্য, সত্য))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_to_pragma_eol (parser, অসত্য);
	      c_parser_skip_to_pragma_omp_end_declare_variant (parser);
	      প্রত্যাগম;
	    }
	  অন্যথা
	    {
	      তার্কিক attr_syntax = parser->in_omp_attribute_pragma != রিক্ত;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_safe_ঠেলো (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_to_pragma_eol (parser);
	}
      অন্যথা
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser, অসত্য);
	}
    }
  অন্যথা যদি (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      তার্কিক attr_syntax = parser->in_omp_attribute_pragma != রিক্ত;
      c_parser_omp_assumption_clauses (parser, অসত্য);
      সংরচনা c_omp_begin_assumes_data a = { attr_syntax };
      vec_safe_ঠেলো (current_omp_begin_assumes, a);
    }
  অন্যথা
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

স্থির শূন্য
c_parser_omp_end (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ধ্রুব বর্ণ *p = "";
  c_parser_consume_pragma (parser);
  যদি (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
  যদি (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      যদি (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  তার্কিক attr_syntax = parser->in_omp_attribute_pragma != রিক্ত;
	  c_parser_skip_to_pragma_eol (parser);
	  যদি (!vec_safe_length (current_omp_declare_target_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  অন্যথা
	    {
	      c_omp_declare_target_attr
		a = current_omp_declare_target_attribute->বের_করো ();
	      যদি (a.attr_syntax != attr_syntax)
		{
		  যদি (a.attr_syntax)
		    error_at (loc,
			      "%qs in attribute syntax terminated "
			      "with %qs in pragma syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		  অন্যথা
		    error_at (loc,
			      "%qs in pragma syntax terminated "
			      "with %qs in attribute syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		}
	    }
	}
      অন্যথা যদি (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  তার্কিক attr_syntax = parser->in_omp_attribute_pragma != রিক্ত;
	  c_parser_skip_to_pragma_eol (parser);
	  যদি (!vec_safe_length (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  অন্যথা
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->বের_করো ();
	      যদি (a.attr_syntax != attr_syntax)
		{
		  যদি (a.attr_syntax)
		    error_at (loc,
			      "%<begin declare variant%> in attribute syntax "
			      "terminated with "
			      "%<end declare variant%> in pragma syntax");
		  অন্যথা
		    error_at (loc,
			      "%<begin declare variant%> in pragma syntax "
			      "terminated with "
			      "%<end declare variant%> in attribute syntax");
		}
	    }
	}
      অন্যথা
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser);
	  প্রত্যাগম;
	}
    }
  অন্যথা যদি (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      তার্কিক attr_syntax = parser->in_omp_attribute_pragma != রিক্ত;
      c_parser_skip_to_pragma_eol (parser);
      যদি (!vec_safe_length (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      অন্যথা
	{
	  c_omp_begin_assumes_data
	    a = current_omp_begin_assumes->বের_করো ();
	  যদি (a.attr_syntax != attr_syntax)
	    {
	      যদি (a.attr_syntax)
		error_at (loc,
			  "%qs in attribute syntax terminated "
			  "with %qs in pragma syntax",
			  "begin assumes", "end assumes");
	      অন্যথা
		error_at (loc,
			  "%qs in pragma syntax terminated "
			  "with %qs in attribute syntax",
			  "begin assumes", "end assumes");
	    }
	}
    }
  অন্যথা
    {
      c_parser_error (parser, "expected %<declare%> or %<assumes%>");
      c_parser_skip_to_pragma_eol (parser);
    }
}

/* OpenMP 5.0
   #pragma omp declare mapper ([mapper-identifier :] type var) \
			      [clause [ [,] clause ] ... ] new-line  */

স্থির শূন্য
c_parser_omp_declare_mapper (c_parser *parser, গণনা pragma_context context)
{
  বৃক্ষ type, mapper_name = NULL_বৃক্ষ, var = NULL_বৃক্ষ, stmt, stmtlist;
  বৃক্ষ maplist = NULL_বৃক্ষ, mapper_id, mapper_decl, t;
  c_token *token;

  যদি (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare mapper%> not at file or block scope");
      গচ্ছ fail;
    }

  যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    গচ্ছ fail;

  token = c_parser_peek_token (parser);

  যদি (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      বিকল্প (token->type)
	{
	পক্ষ CPP_NAME:
	  mapper_name = token->মান;
	  c_parser_consume_token (parser);
	  ভঙ্গ;
	পক্ষ CPP_KEYWORD:
	  যদি (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_বৃক্ষ;
	      c_parser_consume_token (parser);
	      ভঙ্গ;
	    }
	  /* Fallthrough.  */
	স্বভাব:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_to_pragma_eol (parser, অসত্য);
	  প্রত্যাগম;
	}

      যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	গচ্ছ fail;
    }

  mapper_id = c_omp_mapper_id (mapper_name);
  mapper_decl = c_omp_mapper_decl (mapper_id);

  {
    location_t loc = c_parser_peek_token (parser)->location;
    সংরচনা c_type_name *ctype = c_parser_type_name (parser);
    type = groktypename (ctype, রিক্ত, রিক্ত);
    যদি (type == error_mark_গ্রন্থি)
      গচ্ছ fail;
    যদি (!RECORD_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_to_pragma_eol (parser, অসত্য);
	প্রত্যাগম;
      }
    প্রতি (বৃক্ষ t = DECL_INITIAL (mapper_decl); t; t = বৃক্ষ_CHAIN (t))
      যদি (comptypes (বৃক্ষ_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_POINTER (mapper_id)
		      + পরিমাণ ("omp declare mapper ") - 1,
		    type);
	  বৃক্ষ prevmapper = বৃক্ষ_মান (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_SOURCE_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_to_pragma_eol (parser, অসত্য);
	  প্রত্যাগম;
	}
  }

  token = c_parser_peek_token (parser);
  যদি (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->মান, type);
      c_parser_consume_token (parser);
      DECL_ARTIFICIAL (var) = 1;
    }
  অন্যথা
    {
      error_at (token->location, "expected identifier");
      গচ্ছ fail;
    }

  যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    গচ্ছ fail;

  ঠেলো_scope ();
  stmtlist = ঠেলো_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  যাবত্ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);
      যদি (c_kind != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (here, "unexpected clause");
	  গচ্ছ fail;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, সত্য);
    }

  যদি (maplist == NULL_বৃক্ষ)
    {
      error_at (প্রবেশ_location, "missing %<map%> clause");
      গচ্ছ fail;
    }
  বৃক্ষ list;
  প্রতি (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      বৃক্ষ dvar = OMP_CLAUSE_DECL (list);
      যাবত্ (!DECL_P (dvar) && বৃক্ষ_OPERAND_LENGTH (dvar))
	dvar = বৃক্ষ_OPERAND (dvar, 0);
      যদি (dvar == var)
	ভঙ্গ;
    }
  যদি (!list)
    error_at (প্রবেশ_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_গ্রন্থি (OMP_DECLARE_MAPPER);
  বৃক্ষ_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  add_stmt (stmt);

  বের_করো_stmt_list (stmtlist);
  বের_করো_scope ();

  c_parser_skip_to_pragma_eol (parser);

  t = বৃক্ষ_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  প্রত্যাগম;

 fail:
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 4.0
   #pragma omp declare reduction (reduction-id : typename-list : expression) \
      initializer-clause[opt] new-line

   initializer-clause:
      initializer (omp_priv = initializer)
      initializer (function-name (argument-list))  */

স্থির শূন্য
c_parser_omp_declare_reduction (c_parser *parser, গণনা pragma_context context)
{
  unsigned পূর্ণাঙ্ক tokens_avail = 0, i;
  c_token *saved_tokens = রিক্ত;
  vec<বৃক্ষ> types = vNULL;
  vec<c_token> clauses = vNULL;
  গণনা বৃক্ষ_code reduc_code = ERROR_MARK;
  বৃক্ষ reduc_id = NULL_বৃক্ষ;
  বৃক্ষ type;
  location_t rloc = c_parser_peek_token (parser)->location;

  যদি (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare reduction%> not at file or block scope");
      গচ্ছ fail;
    }

  যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    গচ্ছ fail;

  বিকল্প (c_parser_peek_token (parser)->type)
    {
    পক্ষ CPP_PLUS:
      reduc_code = PLUS_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_MULT:
      reduc_code = MULT_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_MINUS:
      reduc_code = MINUS_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_AND:
      reduc_code = BIT_AND_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_XOR:
      reduc_code = BIT_XOR_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_OR:
      reduc_code = BIT_IOR_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_AND_AND:
      reduc_code = TRUTH_ANDIF_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_OR_OR:
      reduc_code = TRUTH_ORIF_রাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_NAME:
      ধ্রুব বর্ণ *p;
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp (p, "min") == 0)
	{
	  reduc_code = MIN_রাশিমালা;
	  ভঙ্গ;
	}
      যদি (strcmp (p, "max") == 0)
	{
	  reduc_code = MAX_রাশিমালা;
	  ভঙ্গ;
	}
      reduc_id = c_parser_peek_token (parser)->মান;
      ভঙ্গ;
    স্বভাব:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      গচ্ছ fail;
    }

  বৃক্ষ orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_code, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    গচ্ছ fail;

  যাবত্ (সত্য)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      সংরচনা c_type_name *ctype = c_parser_type_name (parser);
      যদি (ctype != রিক্ত)
	{
	  type = groktypename (ctype, রিক্ত, রিক্ত);
	  যদি (type == error_mark_গ্রন্থি)
	    ;
	  অন্যথা যদি ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || বৃক্ষ_CODE (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_বৃক্ষ)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  অন্যথা যদি (বৃক্ষ_CODE (type) == FUNCTION_TYPE
		   || বৃক্ষ_CODE (type) == ARRAY_TYPE)
	    error_at (loc, "function or array type in "
		      "%<#pragma omp declare reduction%>");
	  অন্যথা যদি (TYPE_ATOMIC (type))
	    error_at (loc, "%<_Atomic%> qualified type in "
			   "%<#pragma omp declare reduction%>");
	  অন্যথা যদি (TYPE_QUALS_NO_ADDR_SPACE (type))
	    error_at (loc, "const, volatile or restrict qualified type in "
			   "%<#pragma omp declare reduction%>");
	  অন্যথা
	    {
	      বৃক্ষ t;
	      প্রতি (t = DECL_INITIAL (reduc_decl); t; t = বৃক্ষ_CHAIN (t))
		যদি (comptypes (বৃক্ষ_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_POINTER (reduc_id)
				   + পরিমাণ ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_SOURCE_LOCATION (বৃক্ষ_VEC_ELT (বৃক্ষ_মান (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    ভঙ্গ;
		  }
	      যদি (t == NULL_বৃক্ষ)
		types.safe_ঠেলো (type);
	    }
	  যদি (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  অন্যথা
	    ভঙ্গ;
	}
      অন্যথা
	ভঙ্গ;
    }

  যদি (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_empty ())
    {
     fail:
      clauses.release ();
      types.release ();
      যাবত্ (সত্য)
	{
	  c_token *token = c_parser_peek_token (parser);
	  যদি (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    ভঙ্গ;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_to_pragma_eol (parser);
      প্রত্যাগম;
    }

  যদি (types.length () > 1)
    {
      যাবত্ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  যদি (token->type == CPP_EOF)
	    গচ্ছ fail;
	  clauses.safe_ঠেলো (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_ঠেলো (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, পরিমাণ (eof_token));
      eof_token.type = CPP_EOF;
      clauses.safe_ঠেলো (eof_token);
      clauses.safe_ঠেলো (eof_token);
    }

  পূর্ণাঙ্ক errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_tokens = parser->tokens;
      tokens_avail = parser->tokens_avail;
      যদি (!clauses.is_empty ())
	{
	  parser->tokens = clauses.address ();
	  parser->tokens_avail = clauses.length ();
	  parser->in_pragma = সত্য;
	}

      তার্কিক nested = current_function_decl != NULL_বৃক্ষ;
      যদি (nested)
	c_ঠেলো_function_context ();
      বৃক্ষ fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, সত্য);
      ঠেলো_scope ();
      বৃক্ষ stmt = ঠেলো_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      বৃক্ষ omp_out = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_out) = 1;
      DECL_CONTEXT (omp_out) = fndecl;
      pushdecl (omp_out);
      বৃক্ষ omp_in = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_in) = 1;
      DECL_CONTEXT (omp_in) = fndecl;
      pushdecl (omp_in);
      সংরচনা c_রাশিমালা combiner = c_parser_expression (parser);
      সংরচনা c_রাশিমালা initializer;
      বৃক্ষ omp_priv = NULL_বৃক্ষ, omp_orig = NULL_বৃক্ষ;
      তার্কিক bad = অসত্য;
      initializer.set_error ();
      যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	bad = সত্য;
      অন্যথা যদি (c_parser_next_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      যদি (!bad
	  && (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->মান),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  বের_করো_scope ();
	  ঠেলো_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_গ্রন্থি;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    bad = সত্য;
	  অন্যথা যদি (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      bad = সত্য;
	    }
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->মান),
			   "omp_priv") != 0)
	    {
	      যদি (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_kind != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  bad = সত্য;
		}
	      অন্যথা
		initializer = c_parser_postfix_expression (parser);
	      যদি (initializer.মান
		  && বৃক্ষ_CODE (initializer.মান) == CALL_রাশিমালা)
		{
		  পূর্ণাঙ্ক j;
		  বৃক্ষ c = initializer.মান;
		  প্রতি (j = 0; j < call_রাশিমালা_nargs (c); j++)
		    {
		      বৃক্ষ a = CALL_রাশিমালা_ARG (c, j);
		      STRIP_NOPS (a);
		      যদি (বৃক্ষ_CODE (a) == ADDR_রাশিমালা
			  && বৃক্ষ_OPERAND (a, 0) == omp_priv)
			ভঙ্গ;
		    }
		  যদি (j == call_রাশিমালা_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  অন্যথা
	    {
	      c_parser_consume_token (parser);
	      যদি (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		bad = সত্য;
	      অন্যথা
		{
		  বৃক্ষ st = ঠেলো_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (সারি_table, loc);
		  start_init (omp_priv, NULL_বৃক্ষ, অসত্য, অসত্য, &richloc);
		  সংরচনা c_রাশিমালা init = c_parser_initializer (parser, omp_priv);
		  finish_init ();
		  finish_decl (omp_priv, loc, init.মান,
		      	       init.original_type, NULL_বৃক্ষ);
		  বের_করো_stmt_list (st);
		}
	    }
	  যদি (!bad
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    bad = সত্য;
	}

      যদি (!bad)
	{
	  c_parser_skip_to_pragma_eol (parser);

	  বৃক্ষ t = বৃক্ষ_cons (type, make_বৃক্ষ_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_SOURCE_LOCATION (omp_out) = rloc;
	  বৃক্ষ_VEC_ELT (বৃক্ষ_মান (t), 0) = omp_out;
	  বৃক্ষ_VEC_ELT (বৃক্ষ_মান (t), 1) = omp_in;
	  বৃক্ষ_VEC_ELT (বৃক্ষ_মান (t), 2) = combiner.মান;
	  walk_বৃক্ষ (&combiner.মান, c_check_omp_declare_reduction_r,
		     &বৃক্ষ_VEC_ELT (বৃক্ষ_মান (t), 0), রিক্ত);
	  যদি (omp_priv)
	    {
	      DECL_SOURCE_LOCATION (omp_priv) = rloc;
	      বৃক্ষ_VEC_ELT (বৃক্ষ_মান (t), 3) = omp_priv;
	      বৃক্ষ_VEC_ELT (বৃক্ষ_মান (t), 4) = omp_orig;
	      বৃক্ষ_VEC_ELT (বৃক্ষ_মান (t), 5) = initializer.মান;
	      walk_বৃক্ষ (&initializer.মান, c_check_omp_declare_reduction_r,
			 &বৃক্ষ_VEC_ELT (বৃক্ষ_মান (t), 3), রিক্ত);
	      walk_বৃক্ষ (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &বৃক্ষ_VEC_ELT (বৃক্ষ_মান (t), 3), রিক্ত);
	    }
	}

      বের_করো_stmt_list (stmt);
      বের_করো_scope ();
      যদি (cfun->language != রিক্ত)
	{
	  ggc_free (cfun->language);
	  cfun->language = রিক্ত;
	}
      set_cfun (রিক্ত);
      current_function_decl = NULL_বৃক্ষ;
      যদি (nested)
	c_বের_করো_function_context ();

      যদি (!clauses.is_empty ())
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}
      যদি (bad)
	গচ্ছ fail;
      যদি (errs != errorcount)
	ভঙ্গ;
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

স্থির তার্কিক
c_parser_omp_declare (c_parser *parser, গণনা pragma_context context)
{
  c_parser_consume_pragma (parser);
  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  প্রত্যাগম সত্য;
	}
      যদি (strcmp (p, "reduction") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_reduction (parser, context);
	  প্রত্যাগম অসত্য;
	}
      যদি (strcmp (p, "mapper") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_mapper (parser, context);
	  প্রত্যাগম অসত্য;
	}
      যদি (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, অসত্য);
	  প্রত্যাগম অসত্য;
	}
      যদি (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_target (parser);
	  প্রত্যাগম অসত্য;
	}
      যদি (strcmp (p, "variant") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  প্রত্যাগম সত্য;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_to_pragma_eol (parser);
  প্রত্যাগম অসত্য;
}

/* OpenMP 5.0
   #pragma omp requires clauses[optseq] new-line  */

স্থির শূন্য
c_parser_omp_requires (c_parser *parser)
{
  গণনা omp_requires new_req = (গণনা omp_requires) 0;

  c_parser_consume_pragma (parser);

  location_t loc = c_parser_peek_token (parser)->location;
  যাবত্ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      যদি (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      যদি (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ধ্রুব বর্ণ *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  গণনা omp_requires this_req = (গণনা omp_requires) 0;

	  যদি (!strcmp (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_ADDRESS;
	  অন্যথা যদি (!strcmp (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_MEMORY;
	  অন্যথা যদি (!strcmp (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  অন্যথা যদি (!strcmp (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  অন্যথা যদি (!strcmp (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_REVERSE_OFFLOAD;
	  অন্যথা যদি (!strcmp (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      যদি (parens.require_open (parser))
		{
		  যদি (c_parser_next_token_is (parser, CPP_NAME))
		    {
		      বৃক্ষ v = c_parser_peek_token (parser)->মান;
		      p = IDENTIFIER_POINTER (v);

		      যদি (!strcmp (p, "seq_cst"))
			this_req
			  = (গণনা omp_requires) OMP_MEMORY_ORDER_SEQ_CST;
		      অন্যথা যদি (!strcmp (p, "relaxed"))
			this_req
			  = (গণনা omp_requires) OMP_MEMORY_ORDER_RELAXED;
		      অন্যথা যদি (!strcmp (p, "release"))
			this_req
			  = (গণনা omp_requires) OMP_MEMORY_ORDER_RELEASE;
		      অন্যথা যদি (!strcmp (p, "acq_rel"))
			this_req
			  = (গণনা omp_requires) OMP_MEMORY_ORDER_ACQ_REL;
		      অন্যথা যদি (!strcmp (p, "acquire"))
			this_req
			  = (গণনা omp_requires) OMP_MEMORY_ORDER_ACQUIRE;
		    }
		  যদি (this_req == 0)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<acq_rel%>, %<acquire%>, "
				"%<relaxed%>, %<release%> or %<seq_cst%>");
		      বিকল্প (c_parser_peek_token (parser)->type)
			{
			পক্ষ CPP_EOF:
			পক্ষ CPP_PRAGMA_EOL:
			পক্ষ CPP_CLOSE_PAREN:
			  ভঙ্গ;
			স্বভাব:
			  যদি (c_parser_peek_2nd_token (parser)->type
			      == CPP_CLOSE_PAREN)
			    c_parser_consume_token (parser);
			  ভঙ্গ;
			}
		    }
		  অন্যথা
		    c_parser_consume_token (parser);

		  parens.skip_until_found_close (parser);
		  যদি (this_req == 0)
		    {
		      c_parser_skip_to_pragma_eol (parser, অসত্য);
		      প্রত্যাগম;
		    }
		}
	      p = রিক্ত;
	    }
	  অন্যথা
	    {
	      error_at (cloc, "expected %<unified_address%>, "
			      "%<unified_shared_memory%>, "
			      "%<self_maps%>, "
			      "%<dynamic_allocators%>, "
			       "%<reverse_offload%> "
			       "or %<atomic_default_mem_order%> clause");
	      c_parser_skip_to_pragma_eol (parser, অসত্য);
	      প্রত্যাগম;
	    }
	  যদি (p)
	    c_parser_consume_token (parser);
	  যদি (this_req)
	    {
	      যদি ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  যদি ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  যদি (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_mask & OMP_REQUIRES_TARGET_USED) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      অন্যথা যদি ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (গণনা omp_requires) 0;
		}
	      অন্যথা যদি ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (গণনা omp_requires)
		       (omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER);
		}
	      অন্যথা যদি ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (গণনা omp_requires) (new_req | this_req);
	      omp_requires_mask
		= (গণনা omp_requires) (omp_requires_mask | this_req);
	      অনুবর্ত;
	    }
	}
      ভঙ্গ;
    }
  c_parser_skip_to_pragma_eol (parser);

  যদি (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

স্থির বৃক্ষ
c_finish_taskloop_clauses (বৃক্ষ clauses)
{
  বৃক্ষ *pc = &clauses;
  প্রতি (বৃক্ষ c = clauses; c; c = *pc)
    {
      তার্কিক remove = অসত্য;
      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
	{
	  বৃক্ষ type = strip_array_types (বৃক্ষ_TYPE (OMP_CLAUSE_DECL (c)));
	  যদি (integer_zerop (TYPE_SIZE_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      remove = সত্য;
	    }
	  অন্যথা যদি (বৃক্ষ_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      remove = সত্য;
	    }
	}
      যদি (remove)
	*pc = OMP_CLAUSE_CHAIN (c);
      অন্যথা
	pc = &OMP_CLAUSE_CHAIN (c);
    }
  প্রত্যাগম clauses;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_অঙ্ক_TASKS)	\
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

স্থির বৃক্ষ
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       বর্ণ *p_name, omp_clause_mask mask, বৃক্ষ *cclauses,
		       তার্কিক *if_p)
{
  বৃক্ষ clauses, block, ret;

  strcat (p_name, " taskloop");
  mask |= OMP_TASKLOOP_CLAUSE_MASK;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  যদি ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_অঙ্ক_THREADS)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IN_REDUCTION);

  যদি (c_parser_next_token_is (parser, CPP_NAME))
    {
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);

      যদি (strcmp (p, "simd") == 0)
	{
	  বৃক্ষ cclauses_buf[C_OMP_CLAUSE_SPLIT_গুনতি];
	  যদি (cclauses == রিক্ত)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  যদি (!flag_openmp)  /* flag_openmp_simd  */
	    প্রত্যাগম c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (সত্য);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, সত্য);
	  যদি (ret == রিক্ত)
	    প্রত্যাগম ret;
	  ret = make_গ্রন্থি (OMP_TASKLOOP);
	  বৃক্ষ_TYPE (ret) = void_type_গ্রন্থি;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_finish_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  SET_রাশিমালা_LOCATION (ret, loc);
	  add_stmt (ret);
	  প্রত্যাগম ret;
	}
    }
  যদি (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, অসত্য);
      প্রত্যাগম NULL_বৃক্ষ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == রিক্ত);
  যদি (cclauses)
    {
      omp_split_clauses (loc, OMP_TASKLOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
    }

  clauses = c_finish_taskloop_clauses (clauses);
  block = c_begin_compound_stmt (সত্য);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, রিক্ত, if_p);
  block = c_end_compound_stmt (loc, block, সত্য);
  add_stmt (block);

  প্রত্যাগম ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
স্থির বৃক্ষ
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  বৃক্ষ sizes = NULL_বৃক্ষ;

  যদি (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  যদি (tok->type != CPP_NAME
      || strcmp ("sizes", IDENTIFIER_POINTER (tok->মান)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      প্রত্যাগম error_mark_গ্রন্থি;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  যদি (!parens.require_open (parser))
    প্রত্যাগম error_mark_গ্রন্থি;

  vec<বৃক্ষ, va_gc> *sizes_vec
    = c_parser_রাশিমালা_list (parser, সত্য, সত্য, রিক্ত, রিক্ত, রিক্ত, রিক্ত);
  sizes = build_বৃক্ষ_list_vec (sizes_vec);
  release_বৃক্ষ_vector (sizes_vec);

  প্রতি (বৃক্ষ s = sizes; s; s = বৃক্ষ_CHAIN (s))
    {
      বৃক্ষ রাশিমালা = বৃক্ষ_মান (s);
      যদি (রাশিমালা == error_mark_গ্রন্থি)
	{
	  parens.skip_until_found_close (parser);
	  প্রত্যাগম error_mark_গ্রন্থি;
	}

      HOST_WIDE_INT n;
      যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (রাশিমালা))
	  || !বৃক্ষ_fits_shwi_p (রাশিমালা)
	  || (n = বৃক্ষ_to_shwi (রাশিমালা)) <= 0
	  || (পূর্ণাঙ্ক) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  বৃক্ষ_মান (s) = integer_one_গ্রন্থি;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  বৃক্ষ c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  প্রত্যাগম c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

স্থির বৃক্ষ
c_parser_omp_tile (location_t loc, c_parser *parser, তার্কিক *if_p)
{
  বৃক্ষ clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_to_pragma_eol (parser);

  যদি (!clauses || clauses == error_mark_গ্রন্থি)
    প্রত্যাগম error_mark_গ্রন্থি;

  বৃক্ষ block = c_begin_compound_stmt (সত্য);
  বৃক্ষ ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    রিক্ত, if_p);
  block = c_end_compound_stmt (loc, block, সত্য);
  add_stmt (block);

  প্রত্যাগম ret;
}

#define OMP_UNROLL_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FULL))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

স্থির বৃক্ষ
c_parser_omp_unroll (location_t loc, c_parser *parser, তার্কিক *if_p)
{
  বৃক্ষ clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_MASK,
					   "#pragma omp unroll", সত্য);

  বৃক্ষ block = c_begin_compound_stmt (সত্য);
  বৃক্ষ ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    রিক্ত, if_p);
  block = c_end_compound_stmt (loc, block, সত্য);
  add_stmt (block);

  প্রত্যাগম ret;
}

/* OpenMP 5.1
   #pragma omp nothing new-line  */

স্থির শূন্য
c_parser_omp_nothing (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp error clauses[optseq] new-line  */

স্থির তার্কিক
c_parser_omp_error (c_parser *parser, গণনা pragma_context context)
{
  পূর্ণাঙ্ক at_compilation = -1;
  পূর্ণাঙ্ক severity_fatal = -1;
  বৃক্ষ message = NULL_বৃক্ষ;
  তার্কিক bad = অসত্য;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  যাবত্ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      যদি (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      যদি (!c_parser_next_token_is (parser, CPP_NAME))
	ভঙ্গ;

      ধ্রুব বর্ণ *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      location_t cloc = c_parser_peek_token (parser)->location;
      স্থির ধ্রুব বর্ণ *args[] = {
	"execution", "compilation", "warning", "fatal"
      };
      পূর্ণাঙ্ক *v = রিক্ত;
      পূর্ণাঙ্ক idx = 0, n = -1;
      বৃক্ষ m = NULL_বৃক্ষ;

      যদি (!strcmp (p, "at"))
	v = &at_compilation;
      অন্যথা যদি (!strcmp (p, "severity"))
	{
	  v = &severity_fatal;
	  idx += 2;
	}
      অন্যথা যদি (strcmp (p, "message"))
	{
	  error_at (cloc,
		    "expected %<at%>, %<severity%> or %<message%> clause");
	  c_parser_skip_to_pragma_eol (parser, অসত্য);
	  প্রত্যাগম অসত্য;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      যদি (parens.require_open (parser))
	{
	  যদি (v == রিক্ত)
	    {
	      location_t রাশিমালা_loc = c_parser_peek_token (parser)->location;
	      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	      রাশিমালা = convert_lvalue_to_rvalue (রাশিমালা_loc, রাশিমালা, সত্য, সত্য);
	      m = convert (const_string_type_গ্রন্থি, রাশিমালা.মান);
	      m = c_fully_fold (m, অসত্য, রিক্ত);
	    }
	  অন্যথা
	    {
	      যদি (c_parser_next_token_is (parser, CPP_NAME))
		{
		  বৃক্ষ val = c_parser_peek_token (parser)->মান;
		  ধ্রুব বর্ণ *q = IDENTIFIER_POINTER (val);

		  যদি (!strcmp (q, args[idx]))
		    n = 0;
		  অন্যথা যদি (!strcmp (q, args[idx + 1]))
		    n = 1;
		}
	      যদি (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", args[idx], args[idx + 1]);
		  bad = সত্য;
		  বিকল্প (c_parser_peek_token (parser)->type)
		    {
		    পক্ষ CPP_EOF:
		    পক্ষ CPP_PRAGMA_EOL:
		    পক্ষ CPP_CLOSE_PAREN:
		      ভঙ্গ;
		    স্বভাব:
		      যদি (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)
			c_parser_consume_token (parser);
		      ভঙ্গ;
		    }
		}
	      অন্যথা
		c_parser_consume_token (parser);
	    }

	  parens.skip_until_found_close (parser);

	  যদি (v == রিক্ত)
	    {
	      যদি (message)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = সত্য;
		}
	      অন্যথা
		message = m;
	    }
	  অন্যথা যদি (n != -1)
	    {
	      যদি (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = সত্য;
		}
	      অন্যথা
		*v = n;
	    }
	}
      অন্যথা
	bad = সত্য;
    }
  c_parser_skip_to_pragma_eol (parser);
  যদি (bad)
    প্রত্যাগম সত্য;

  যদি (at_compilation == -1)
    at_compilation = 1;
  যদি (severity_fatal == -1)
    severity_fatal = 1;
  যদি (!at_compilation)
    {
      যদি (context != pragma_compound)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may only be used in compound statements");
	  প্রত্যাগম সত্য;
	}
      যদি (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->in_intervening_code)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->fail = সত্য;
	  প্রত্যাগম সত্য;
	}
      বৃক্ষ fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_IN_GOMP_ERROR
						: BUILT_IN_GOMP_WARNING);
      যদি (!message)
	message = build_zero_cst (const_string_type_গ্রন্থি);
      বৃক্ষ stmt = build_call_রাশিমালা_loc (loc, fndecl, 2, message,
				       build_all_ones_cst (size_type_গ্রন্থি));
      add_stmt (stmt);
      প্রত্যাগম সত্য;
    }
  ধ্রুব বর্ণ *বার্তা = রিক্ত;
  যদি (message)
    {
      বার্তা = c_getstr (message);
      যদি (বার্তা == রিক্ত)
	বার্তা = _("<message unknown at compile time>");
    }
  ধ্রুব গণনা diagnostics::kind diag_kind = (severity_fatal
					    ? diagnostics::kind::error
					    : diagnostics::kind::warning);
  যদি (বার্তা)
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered: %s", বার্তা);
  অন্যথা
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered");
  প্রত্যাগম অসত্য;
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

স্থির শূন্য
c_parser_omp_assumption_clauses (c_parser *parser, তার্কিক is_assume)
{
  তার্কিক no_openmp = অসত্য;
  তার্কিক no_openmp_constructs = অসত্য;
  তার্কিক no_openmp_routines = অসত্য;
  তার্কিক no_parallelism = অসত্য;
  bitmap_head absent_head, contains_head;

  bitmap_obstack_initialize (রিক্ত);
  bitmap_initialize (&absent_head, &bitmap_default_obstack);
  bitmap_initialize (&contains_head, &bitmap_default_obstack);

  যদি (c_parser_next_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  যাবত্ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      যদি (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      যদি (!c_parser_next_token_is (parser, CPP_NAME))
	ভঙ্গ;

      ধ্রুব বর্ণ *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      location_t cloc = c_parser_peek_token (parser)->location;

      যদি (!strcmp (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  যদি (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = সত্য;
	}
      অন্যথা যদি (!strcmp (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  যদি (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = সত্য;
	}
      অন্যথা যদি (!strcmp (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  যদি (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = সত্য;
	}
      অন্যথা যদি (!strcmp (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  যদি (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = সত্য;
	}
      অন্যথা যদি (!strcmp (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  যদি (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_রাশিমালা রাশিমালা = c_parser_রাশিমালা_no_commas (parser, রিক্ত);
	      বৃক্ষ t = convert_lvalue_to_rvalue (eloc, রাশিমালা, সত্য, সত্য).মান;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, অসত্য, রিক্ত);
	      যদি (is_assume && t != error_mark_গ্রন্থি)
		{
		  বৃক্ষ fn = build_call_রাশিমালা_internal_loc (eloc, IFN_ASSUME,
							  void_type_গ্রন্থি, 1,
							  t);
		  add_stmt (fn);
		}
	      parens.skip_until_found_close (parser);
	    }
	}
      অন্যথা যদি (!strcmp (p, "absent") || !strcmp (p, "contains"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  যদি (parens.require_open (parser))
	    {
	      কুরু
		{
		  ধ্রুব বর্ণ *directive[3] = {};
		  পূর্ণাঙ্ক i;
		  location_t dloc = c_parser_peek_token (parser)->location;
		  প্রতি (i = 0; i < 3; i++)
		    {
		      বৃক্ষ id;
		      যদি (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->মান;
		      অন্যথা যদি (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  গণনা rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      অন্যথা
			ভঙ্গ;
		      directive[i] = IDENTIFIER_POINTER (id);
		    }
		  যদি (i == 0)
		    error_at (dloc, "expected directive name");
		  অন্যথা
		    {
		      ধ্রুব সংরচনা c_omp_directive *dir
			= c_omp_categorize_directive (directive[0],
						      directive[1],
						      directive[2]);
		      যদি (dir
			  && dir->id != PRAGMA_OMP_END
			  && (dir->kind == C_OMP_DIR_DECLARATIVE
			      || dir->kind == C_OMP_DIR_INFORMATIONAL
			      || dir->kind == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      অন্যথা যদি (dir == রিক্ত
			       || dir->id == PRAGMA_OMP_END
			       || (!dir->second && directive[1])
			       || (!dir->third && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      অন্যথা
			{
			  পূর্ণাঙ্ক id = dir - c_omp_directives;
			  যদি (bitmap_bit_p (p[0] == 'a' ? &contains_head
							: &absent_head, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  অন্যথা যদি (!bitmap_set_bit (p[0] == 'a'
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
		      প্রতি (; i; --i)
			c_parser_consume_token (parser);
		    }
		  যদি (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  অন্যথা
		    ভঙ্গ;
		}
	      যাবত্ (1);
	      parens.skip_until_found_close (parser);
	    }
	}
      অন্যথা যদি (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      matching_parens parens;
	      parens.consume_open (parser);
	      c_parser_balanced_token_sequence (parser);
	      parens.require_close (parser);
	    }
	}
      অন্যথা
	{
	  c_parser_consume_token (parser);
	  error_at (cloc, "expected assumption clause");
	  ভঙ্গ;
	}
    }
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

স্থির শূন্য
c_parser_omp_assume (c_parser *parser, তার্কিক *if_p)
{
  c_parser_omp_assumption_clauses (parser, সত্য);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
}

/* OpenMP 5.1
   #pragma omp assumes clauses[optseq] new-line  */

স্থির শূন্য
c_parser_omp_assumes (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_omp_assumption_clauses (parser, অসত্য);
}

/* Helper function for c_parser_omp_metadirective.  */

স্থির শূন্য
analyze_metadirective_body (c_parser *parser,
			    vec<c_token> &tokens,
			    vec<বৃক্ষ> &labels)
{
  পূর্ণাঙ্ক nesting_depth = 0;
  পূর্ণাঙ্ক bracket_depth = 0;
  তার্কিক ignore_label = অসত্য;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  যাবত্ (1)
    {
      c_token *token = c_parser_peek_token (parser);
      তার্কিক stop = অসত্য;

      যদি (c_parser_next_token_is_keyword (parser, RID_CASE))
	ignore_label = সত্য;

      বিকল্প (token->type)
	{
	পক্ষ CPP_EOF:
	  ভঙ্গ;
	পক্ষ CPP_NAME:
	  যদি (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.safe_ঠেলো (token->মান);
	  গচ্ছ add;
	পক্ষ CPP_OPEN_BRACE:
	  ++nesting_depth;
	  গচ্ছ add;
	পক্ষ CPP_CLOSE_BRACE:
	  যদি (--nesting_depth == 0 && bracket_depth == 0)
	    stop = সত্য;
	  গচ্ছ add;
	পক্ষ CPP_OPEN_PAREN:
	  ++bracket_depth;
	  গচ্ছ add;
	পক্ষ CPP_CLOSE_PAREN:
	  --bracket_depth;
	  গচ্ছ add;
	পক্ষ CPP_COLON:
	  ignore_label = অসত্য;
	  গচ্ছ add;
	পক্ষ CPP_SEMICOLON:
	  যদি (nesting_depth == 0 && bracket_depth == 0)
	    stop = সত্য;
	  গচ্ছ add;
	স্বভাব:
	add:
	  tokens.safe_ঠেলো (*token);
	  যদি (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  অন্যথা যদি (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_to_pragma_eol (parser);
	  অন্যথা
	    c_parser_consume_token (parser);
	  যদি (stop)
	    ভঙ্গ;
	  অনুবর্ত;
	}
      ভঙ্গ;
    }
}

/* OpenMP 5.0:

  # pragma omp metadirective [clause[, clause]]
*/

স্থির শূন্য
c_parser_omp_metadirective (c_parser *parser, তার্কিক *if_p)
{
  স্থির unsigned পূর্ণাঙ্ক metadirective_region_গুনতি = 0;

  বৃক্ষ ret;
  auto_vec<c_token> directive_tokens;
  auto_vec<c_token> body_tokens;
  auto_vec<বৃক্ষ> body_labels;
  auto_vec<ধ্রুব সংরচনা c_omp_directive *> directives;
  auto_vec<বৃক্ষ> ctxs;
  vec<সংরচনা omp_variant> candidates;
  তার্কিক default_seen = অসত্য;
  পূর্ণাঙ্ক directive_token_idx = 0;
  বৃক্ষ standalone_body = NULL_বৃক্ষ;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  তার্কিক requires_body = অসত্য;

  ret = make_গ্রন্থি (OMP_METADIRECTIVE);
  SET_রাশিমালা_LOCATION (ret, pragma_loc);
  বৃক্ষ_TYPE (ret) = void_type_গ্রন্থি;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_বৃক্ষ;

  c_parser_consume_pragma (parser);
  যাবত্ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      যদি (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      যদি (c_parser_next_token_is_not (parser, CPP_NAME)
	  && c_parser_next_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  গচ্ছ error;
	}

      location_t match_loc = c_parser_peek_token (parser)->location;
      ধ্রুব বর্ণ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      যদি (strcmp (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.add_fixit_replace (match_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      তার্কিক default_p
	= strcmp (p, "default") == 0 || strcmp (p, "otherwise") == 0;
      যদি (default_p)
	{
	  যদি (default_seen)
	    {
	      error_at (match_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      গচ্ছ error;
	    }
	  default_seen = সত্য;
	}
      অন্যথা যদি (default_seen)
	{
	  error_at (match_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  গচ্ছ error;
	}
      যদি (!default_p && strcmp (p, "when") != 0)
	{
	  error_at (match_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  গচ্ছ error;
	}

      matching_parens parens;
      বৃক্ষ ctx = NULL_বৃক্ষ;
      তার্কিক skip = অসত্য;

      যদি (!parens.require_open (parser))
	গচ্ছ error;

      যদি (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_বৃক্ষ);
	  যদি (ctx == error_mark_গ্রন্থি)
	    গচ্ছ error;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  যদি (ctx == error_mark_গ্রন্থি)
	    গচ্ছ error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_বৃক্ষ, অসত্য) == 0);

	  যদি (c_parser_next_token_is_not (parser, CPP_COLON))
	    {
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      গচ্ছ error;
	    }
	  c_parser_consume_token (parser);
	}

      /* Read in the directive type and create a dummy pragma token for
	 it.  */
      location_t loc = c_parser_peek_token (parser)->location;

      ধ্রুব বর্ণ *directive[3] = {};
      পূর্ণাঙ্ক i;
      প্রতি (i = 0; i < 3; i++)
	{
	  বৃক্ষ id;
	  যদি (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      যদি (i == 0)
		directive[i++] = "nothing";
	      ভঙ্গ;
	    }
	  অন্যথা যদি (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->মান;
	  অন্যথা যদি (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      গণনা rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  অন্যথা
	    ভঙ্গ;

	  directive[i] = IDENTIFIER_POINTER (id);
	}
      যদি (i == 0)
	{
	  error_at (loc, "expected directive name");
	  গচ্ছ error;
	}

      ধ্রুব সংরচনা c_omp_directive *omp_directive
	= c_omp_categorize_directive (directive[0],
				      directive[1],
				      directive[2]);

      যদি (omp_directive == রিক্ত)
	{
	  প্রতি (পূর্ণাঙ্ক j = 0; j < i; j++)
	    c_parser_consume_token (parser);
	  c_parser_error (parser, "unknown directive name");
	  গচ্ছ error;
	}
      অন্যথা
	{
	  পূর্ণাঙ্ক token_গুনতি = 0;
	  যদি (omp_directive->first) token_গুনতি++;
	  যদি (omp_directive->second) token_গুনতি++;
	  যদি (omp_directive->third) token_গুনতি++;
	  প্রতি (পূর্ণাঙ্ক j = 0; j < token_গুনতি; j++)
	    c_parser_consume_token (parser);
	}
      যদি (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  গচ্ছ error;
	}
      যদি (omp_directive->kind == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  গচ্ছ error;
	}
      যদি (omp_directive->kind == C_OMP_DIR_CONSTRUCT)
	requires_body = সত্য;

      যদি (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_kind = (গণনা pragma_kind) omp_directive->id;

	  directives.safe_ঠেলো (omp_directive);
	  directive_tokens.safe_ঠেলো (pragma_token);
	  ctxs.safe_ঠেলো (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      পূর্ণাঙ্ক nesting_depth = 0;
      যাবত্ (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  বিকল্প (token->type)
	    {
	    পক্ষ CPP_EOF:
	    পক্ষ CPP_PRAGMA_EOL:
	      ভঙ্গ;
	    পক্ষ CPP_OPEN_PAREN:
	      ++nesting_depth;
	      গচ্ছ add;
	    পক্ষ CPP_CLOSE_PAREN:
	      যদি (nesting_depth-- == 0)
		{
		  c_parser_consume_token (parser);
		  ভঙ্গ;
		}
	      গচ্ছ add;
	    স্বভাব:
	    add:
	      যদি (!skip)
		directive_tokens.safe_ঠেলো (*token);
	      c_parser_consume_token (parser);
	      অনুবর্ত;
	    }
	  ভঙ্গ;
	}

      যদি (!skip)
	{
	  c_token eol_token;
	  memset (&eol_token, 0, পরিমাণ (eol_token));
	  eol_token.type = CPP_PRAGMA_EOL;
	  directive_tokens.safe_ঠেলো (eol_token);
	}
    }
  c_parser_skip_to_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  যদি (ctxs.length () == 1)
    {
      বৃক্ষ ctx = ctxs[0];
      যদি (ctx == NULL_বৃক্ষ
	  || (omp_context_selector_matches (ctx, NULL_বৃক্ষ, অসত্য) == 1
	      && directive_tokens[0].pragma_kind == PRAGMA_OMP_NOTHING))
	প্রত্যাগম;
    }

  যদি (!default_seen)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      ধ্রুব সংরচনা c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", রিক্ত, রিক্ত);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_kind = PRAGMA_OMP_NOTHING;

      directives.safe_ঠেলো (omp_directive);
      directive_tokens.safe_ঠেলো (pragma_token);
      ctxs.safe_ঠেলো (NULL_বৃক্ষ);

      c_token eol_token;
      memset (&eol_token, 0, পরিমাণ (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_tokens.safe_ঠেলো (eol_token);
    }

  যদি (requires_body)
    analyze_metadirective_body (parser, body_tokens, body_labels);

  /* Process each candidate directive.  */
  unsigned i;
  বৃক্ষ ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> tokens;

      /* Add the directive tokens.  */
      কুরু
	tokens.safe_ঠেলো (directive_tokens [directive_token_idx++]);
      যাবত্ (tokens.last ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_tokens.is_empty ());
      প্রতি (unsigned j = 0; j < body_tokens.length (); j++)
	tokens.safe_ঠেলো (body_tokens[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, পরিমাণ (eof_token));
      eof_token.type = CPP_EOF;
      tokens.safe_ঠেলো (eof_token);
      tokens.safe_ঠেলো (eof_token);

      unsigned পূর্ণাঙ্ক old_tokens_avail = parser->tokens_avail;
      c_token *old_tokens = parser->tokens;
      সংরচনা omp_attribute_pragma_state *old_in_omp_attribute_pragma
	= parser->in_omp_attribute_pragma;
      সংরচনা omp_metadirective_parse_data *old_state
	= parser->omp_metadirective_state;

      সংরচনা omp_metadirective_parse_data new_state;
      new_state.body_labels = &body_labels;
      new_state.region_অঙ্ক = ++metadirective_region_গুনতি;

      parser->tokens = tokens.address ();
      parser->tokens_avail = tokens.length ();
      parser->in_omp_attribute_pragma = রিক্ত;
      parser->omp_metadirective_state = &new_state;

      পূর্ণাঙ্ক prev_errorcount = errorcount;
      বৃক্ষ directive = c_begin_compound_stmt (সত্য);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_বৃক্ষ);
      directive = c_end_compound_stmt (pragma_loc, directive, সত্য);
      তার্কিক standalone_p
	= directives[i]->kind == C_OMP_DIR_STANDALONE
	  || directives[i]->kind == C_OMP_DIR_UTILITY;
      যদি (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  যদি (standalone_body == NULL_বৃক্ষ)
	    {
	      standalone_body = ঠেলো_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = বের_করো_stmt_list (standalone_body);
	    }
	  অন্যথা
	    c_parser_skip_to_end_of_block_or_statement (parser, সত্য);
	}

      বৃক্ষ body = standalone_p ? standalone_body : NULL_বৃক্ষ;
      বৃক্ষ variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      যদি (errorcount == prev_errorcount)
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
  যদি (!candidates.is_empty ())
    ret = c_omp_expand_variant_construct (candidates);

  add_stmt (ret);
  প্রত্যাগম;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  যদি (parser->in_pragma)
    c_parser_skip_to_pragma_eol (parser, অসত্য);
}

/* Main entry point to parsing most OpenMP pragmas.  */

স্থির শূন্য
c_parser_omp_construct (c_parser *parser, তার্কিক *if_p)
{
  গণনা pragma_kind p_kind;
  location_t loc;
  বৃক্ষ stmt;
  বর্ণ p_name[পরিমাণ "#pragma omp teams distribute parallel for simd"];
  omp_clause_mask mask (0);

  loc = c_parser_peek_token (parser)->location;
  p_kind = c_parser_peek_token (parser)->pragma_kind;
  c_parser_consume_pragma (parser);

  বিকল্প (p_kind)
    {
    পক্ষ PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, সত্য);
      প্রত্যাগম;
    পক্ষ PRAGMA_OACC_CACHE:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_DATA:
      stmt = c_parser_oacc_data (loc, parser, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_HOST_DATA:
      stmt = c_parser_oacc_host_data (loc, parser, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_KERNELS:
    পক্ষ PRAGMA_OACC_PARALLEL:
    পক্ষ PRAGMA_OACC_SERIAL:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_kind, p_name, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_LOOP:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, mask, রিক্ত, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OACC_WAIT:
      strcpy (p_name, "#pragma wait");
      stmt = c_parser_oacc_wait (loc, parser, p_name);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (loc, parser, অসত্য);
      প্রত্যাগম;
    পক্ষ PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (loc, parser, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_DISTRIBUTE:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_distribute (loc, parser, p_name, mask, রিক্ত, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_FOR:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, mask, রিক্ত, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_LOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, mask, রিক্ত, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_MASKED:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, mask, রিক্ত, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_MASTER:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, mask, রিক্ত, if_p,
				  UNKNOWN_LOCATION);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_PARALLEL:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, mask, রিক্ত, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_SECTIONS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, mask, রিক্ত);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_SIMD:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, mask, রিক্ত, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (loc, parser, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_TASK:
      stmt = c_parser_omp_task (loc, parser, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_TASKGROUP:
      stmt = c_parser_omp_taskgroup (loc, parser, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_TASKLOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_taskloop (loc, parser, p_name, mask, রিক্ত, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_TEAMS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, mask, রিক্ত, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_ASSUME:
      c_parser_omp_assume (parser, if_p);
      প্রত্যাগম;
    পক্ষ PRAGMA_OMP_TILE:
      stmt = c_parser_omp_tile (loc, parser, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_UNROLL:
      stmt = c_parser_omp_unroll (loc, parser, if_p);
      ভঙ্গ;
    পক্ষ PRAGMA_OMP_DISPATCH:
      stmt = c_parser_omp_dispatch (loc, parser);
      ভঙ্গ;
    স্বভাব:
      gcc_unreachable ();
    }

  যদি (stmt && stmt != error_mark_গ্রন্থি)
    gcc_assert (রাশিমালা_LOCATION (stmt) != UNKNOWN_LOCATION);
}

/* OpenMP 6.0:
   # pragma omp groupprivate (variable-list) [device_type(...)]  */

#define OMP_GROUPPRIVATE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE) )

স্থির শূন্য
c_parser_omp_groupprivate (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  বৃক্ষ vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, রিক্ত);
  বৃক্ষ clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_MASK,
					   "#pragma omp groupprivate");
  /* TODO: Implies 'declare target local' with specified device_type, check for
     conflicts.  Check for other restrictions.  */
  (শূন্য) vars;
  (শূন্য) clauses;
  sorry_at (loc, "%<omp groupprivate%>");
}

/* OpenMP 2.5:
   # pragma omp threadprivate (variable-list) */

স্থির শূন্য
c_parser_omp_threadprivate (c_parser *parser)
{
  বৃক্ষ vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, রিক্ত);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  প্রতি (t = vars; t; t = বৃক্ষ_CHAIN (t))
    {
      বৃক্ষ v = বৃক্ষ_PURPOSE (t);
      loc = রাশিমালা_LOCATION (বৃক্ষ_মান (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      যদি (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      অন্যথা যদি (বৃক্ষ_USED (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      অন্যথা যদি (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      অন্যথা যদি (বৃক্ষ_TYPE (v) == error_mark_গ্রন্থি)
	;
      অন্যথা যদি (! COMPLETE_TYPE_P (বৃক্ষ_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      অন্যথা
	{
	  যদি (! DECL_THREAD_LOCAL_P (v))
	    {
	      set_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      যদি (DECL_RTL_SET_P (v))
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

স্থির বৃক্ষ
c_parser_transaction_attributes (c_parser *parser)
{
  যদি (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    প্রত্যাগম c_parser_gnu_attributes (parser);

  যদি (!c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
    প্রত্যাগম NULL_বৃক্ষ;
  প্রত্যাগম c_parser_std_attribute_specifier (parser, সত্য);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

স্থির বৃক্ষ
c_parser_transaction (c_parser *parser, গণনা rid keyword)
{
  unsigned পূর্ণাঙ্ক old_in = parser->in_transaction;
  unsigned পূর্ণাঙ্ক this_in = 1, new_in;
  location_t loc = c_parser_peek_token (parser)->location;
  বৃক্ষ stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  যদি (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  অন্যথা
    {
      attrs = c_parser_transaction_attributes (parser);
      যদি (attrs)
	this_in |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_in = this_in | (old_in & TM_STMT_ATTR_OUTER);

  parser->in_transaction = new_in;
  stmt = c_parser_compound_statement (parser);
  parser->in_transaction = old_in;

  যদি (flag_tm)
    stmt = c_finish_transaction (loc, stmt, this_in);
  অন্যথা
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  প্রত্যাগম stmt;
}

/* Parse a __transaction_atomic or __transaction_relaxed expression
   (GCC Extension).

   transaction-expression:
     __transaction_atomic ( expression )
     __transaction_relaxed ( expression )
*/

স্থির সংরচনা c_রাশিমালা
c_parser_transaction_expression (c_parser *parser, গণনা rid keyword)
{
  সংরচনা c_রাশিমালা ret;
  unsigned পূর্ণাঙ্ক old_in = parser->in_transaction;
  unsigned পূর্ণাঙ্ক this_in = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  বৃক্ষ attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  যদি (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  অন্যথা
    {
      attrs = c_parser_transaction_attributes (parser);
      যদি (attrs)
	this_in |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->in_transaction = this_in;
  matching_parens parens;
  যদি (parens.require_open (parser))
    {
      বৃক্ষ রাশিমালা = c_parser_expression (parser).মান;
      ret.original_type = বৃক্ষ_TYPE (রাশিমালা);
      ret.মান = build1 (TRANSACTION_রাশিমালা, ret.original_type, রাশিমালা);
      যদি (this_in & TM_STMT_ATTR_RELAXED)
	TRANSACTION_রাশিমালা_RELAXED (ret.মান) = 1;
      SET_রাশিমালা_LOCATION (ret.মান, loc);
      ret.original_code = TRANSACTION_রাশিমালা;
      ret.m_decimal = 0;
      যদি (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, রিক্ত);
	  গচ্ছ error;
	}
    }
  অন্যথা
    {
     error:
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = রিক্ত;
    }
  parser->in_transaction = old_in;

  যদি (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  set_c_রাশিমালা_source_range (&ret, loc, loc);

  প্রত্যাগম ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

স্থির বৃক্ষ
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  বৃক্ষ attrs;
  তার্কিক is_outer = অসত্য;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_attributes (parser);
  যদি (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  যদি (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      গচ্ছ ret_error;
    }
  অন্যথা যদি (parser->in_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      গচ্ছ ret_error;
    }
  অন্যথা যদি (is_outer)
    {
      যদি ((parser->in_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  গচ্ছ ret_error;
	}
    }
  অন্যথা যদি (parser->in_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      গচ্ছ ret_error;
    }

  প্রত্যাগম add_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  প্রত্যাগম build1 (NOP_রাশিমালা, void_type_গ্রন্থি, error_mark_গ্রন্থি);
}

/* Parse a single source file.  */

শূন্য
c_parse_file (শূন্য)
{
  /* Use local storage to begin.  If the first token is a pragma, parse it.
     If it is #pragma GCC pch_preprocess, then this will load a PCH file
     which will cause garbage collection.  */
  c_parser tparser;

  memset (&tparser, 0, পরিমাণ tparser);
  tparser.translate_strings_p = সত্য;
  tparser.tokens = &tparser.tokens_buf[0];
  the_parser = &tparser;

  যদি (c_parser_peek_token (&tparser)->pragma_kind == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  অন্যথা
    c_common_no_more_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  যদি (tparser.tokens == &tparser.tokens_buf[0])
    the_parser->tokens = &the_parser->tokens_buf[0];

  /* Initialize EH, if we've been told to do so.  */
  যদি (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = রিক্ত;
}

শূন্য
c_init_preprocess (শূন্য)
{
  /* Create a parser for use by pragma_lex during preprocessing.  */
  the_parser = ggc_alloc<c_parser> ();
  memset (the_parser, 0, পরিমাণ (c_parser));
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
c_parser_parse_rtl_body (c_parser *parser, বর্ণ *start_with_pass)
{
  যদি (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      মুক্ত (start_with_pass);
      প্রত্যাগম c_parser_peek_token (parser)->location;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  পূর্ণাঙ্ক অঙ্ক_open_braces = 1;
  যাবত্ (1)
    {
      বিকল্প (c_parser_peek_token (parser)->type)
	{
	পক্ষ CPP_OPEN_BRACE:
	  অঙ্ক_open_braces++;
	  ভঙ্গ;
	পক্ষ CPP_CLOSE_BRACE:
	  যদি (--অঙ্ক_open_braces == 0)
	    গচ্ছ found_closing_brace;
	  ভঙ্গ;
	পক্ষ CPP_EOF:
	  error_at (start_loc, "no closing brace");
	  মুক্ত (start_with_pass);
	  প্রত্যাগম c_parser_peek_token (parser)->location;
	স্বভাব:
	  ভঙ্গ;
	}
      c_parser_consume_token (parser);
    }

 found_closing_brace:
  /* At the closing brace; record its location.  */
  location_t end_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  যদি (!read_rtl_function_body_from_file_range (start_loc, end_loc))
    {
      মুক্ত (start_with_pass);
      প্রত্যাগম end_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  run_rtl_passes (start_with_pass);
  প্রত্যাগম end_loc;
}

#অন্তর্ভাব "gt-c-c-parser.h"
