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

#ଅନ୍ତର୍ଭାଵ "config.h"
#define INCLUDE_STRING
#ଅନ୍ତର୍ଭାଵ "system.h"
#ଅନ୍ତର୍ଭାଵ "coretypes.h"
#ଅନ୍ତର୍ଭାଵ "target.h"
#ଅନ୍ତର୍ଭାଵ "function.h"
#ଅନ୍ତର୍ଭାଵ "c-tree.h"
#ଅନ୍ତର୍ଭାଵ "timevar.h"
#ଅନ୍ତର୍ଭାଵ "stringpool.h"
#ଅନ୍ତର୍ଭାଵ "cgraph.h"
#ଅନ୍ତର୍ଭାଵ "attribs.h"
#ଅନ୍ତର୍ଭାଵ "stor-layout.h"
#ଅନ୍ତର୍ଭାଵ "varasm.h"
#ଅନ୍ତର୍ଭାଵ "trans-mem.h"
#ଅନ୍ତର୍ଭାଵ "c-family/c-pragma.h"
#ଅନ୍ତର୍ଭାଵ "c-lang.h"
#ଅନ୍ତର୍ଭାଵ "c-family/c-objc.h"
#ଅନ୍ତର୍ଭାଵ "plugin.h"
#ଅନ୍ତର୍ଭାଵ "omp-general.h"
#ଅନ୍ତର୍ଭାଵ "omp-offload.h"
#ଅନ୍ତର୍ଭାଵ "builtins.h"
#ଅନ୍ତର୍ଭାଵ "gomp-constants.h"
#ଅନ୍ତର୍ଭାଵ "c-family/c-indentation.h"
#ଅନ୍ତର୍ଭାଵ "gimple-expr.h"
#ଅନ୍ତର୍ଭାଵ "context.h"
#ଅନ୍ତର୍ଭାଵ "gcc-rich-location.h"
#ଅନ୍ତର୍ଭାଵ "c-parser.h"
#ଅନ୍ତର୍ଭାଵ "gimple-parser.h"
#ଅନ୍ତର୍ଭାଵ "read-rtl-function.h"
#ଅନ୍ତର୍ଭାଵ "run-rtl-passes.h"
#ଅନ୍ତର୍ଭାଵ "intl.h"
#ଅନ୍ତର୍ଭାଵ "c-family/name-hint.h"
#ଅନ୍ତର୍ଭାଵ "tree-iterator.h"
#ଅନ୍ତର୍ଭାଵ "tree-pretty-print.h"
#ଅନ୍ତର୍ଭାଵ "memmodel.h"
#ଅନ୍ତର୍ଭାଵ "c-family/known-headers.h"
#ଅନ୍ତର୍ଭାଵ "bitmap.h"
#ଅନ୍ତର୍ଭାଵ "analyzer/analyzer-language.h"
#ଅନ୍ତର୍ଭାଵ "toplev.h"
#ଅନ୍ତର୍ଭାଵ "asan.h"
#ଅନ୍ତର୍ଭାଵ "c-family/c-ubsan.h"
#ଅନ୍ତର୍ଭାଵ "gcc-urlifier.h"

/* We need to walk over decls with incomplete struct/union/enum types
   after parsing the whole translation unit.
   In finish_decl(), if the decl is static, has incomplete
   struct/union/enum type, it is appended to incomplete_record_decls.
   In c_parser_translation_unit(), we iterate over incomplete_record_decls
   and report error if any of the decls are still incomplete.  */

vec<ବୃକ୍ଷ> incomplete_record_decls;

ଶୂନ୍ୟ
set_c_ପଦସମଷ୍ଟି_source_range (c_ପଦସମଷ୍ଟି *ପଦସମଷ୍ଟି,
			 location_t start, location_t finish)
{
  ପଦସମଷ୍ଟି->src_range.m_start = start;
  ପଦସମଷ୍ଟି->src_range.m_finish = finish;
  ଯଦି (ପଦସମଷ୍ଟି->ମୂଲ୍ୟ)
    set_source_range (ପଦସମଷ୍ଟି->ମୂଲ୍ୟ, start, finish);
}

ଶୂନ୍ୟ
set_c_ପଦସମଷ୍ଟି_source_range (c_ପଦସମଷ୍ଟି *ପଦସମଷ୍ଟି,
			 source_range src_range)
{
  ପଦସମଷ୍ଟି->src_range = src_range;
  ଯଦି (ପଦସମଷ୍ଟି->ମୂଲ୍ୟ)
    set_source_range (ପଦସମଷ୍ଟି->ମୂଲ୍ୟ, src_range);
}


/* Initialization routine for this file.  */

ଶୂନ୍ୟ
c_parse_init (ଶୂନ୍ୟ)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
  ବୃକ୍ଷ id;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା mask = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  mask |= D_CXXONLY;
  ଯଦି (!flag_isoc99)
    mask |= D_C99;
  ଯଦି (!flag_isoc23)
    mask |= D_C23;
  ଯଦି (flag_no_asm)
    {
      mask |= D_ASM | D_EXT;
      ଯଦି (!flag_isoc99)
	mask |= D_EXT89;
      ଯଦି (!flag_isoc23)
	mask |= D_EXT11;
    }
  ଯଦି (!c_dialect_objc ())
    mask |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<ବୃକ୍ଷ> ((ପୂର୍ଣ୍ଣସଂଖ୍ୟା) RID_MAX);
  ପାଇଁ (i = 0; i < ଅଙ୍କ_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      ଯଦି (c_common_reswords[i].disable & mask)
	{
	  ଯଦି (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].word);
	      C_SET_RID_CODE (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_WORD (id) = 1;
	    }
	  ଜାରି;
	}

      id = get_identifier (c_common_reswords[i].word);
      C_SET_RID_CODE (id, c_common_reswords[i].rid);
      C_IS_RESERVED_WORD (id) = 1;
      ridpointers [(ପୂର୍ଣ୍ଣସଂଖ୍ୟା) c_common_reswords[i].rid] = id;
    }

  ପାଇଁ (i = 0; i < ଅଙ୍କ_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      ଅକ୍ଷର name[50];
      sprintf (name, "__int%d", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;

      sprintf (name, "__int%d__", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;
    }

  ଯଦି (flag_openmp)
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
ସଂରଚନା GTY(()) c_parser {
  /* The look-ahead tokens.  */
  c_token * GTY((skip)) tokens;
  /* Buffer for look-ahead tokens.  */
  c_token tokens_buf[4];
  /* How many look-ahead tokens are available (0 - 4, or
     more if parsing from pre-lexed tokens).  */
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା tokens_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_tokens;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା raw_tokens_used;
  /* True if a syntax error is being recovered from; false otherwise.
     c_parser_error sets this flag.  It should clear this flag when
     enough tokens have been consumed to recover from the error.  */
  ତାର୍କିକ error : 1;
  /* True if we're processing a pragma, and shouldn't automatically
     consume CPP_PRAGMA_EOL.  */
  ତାର୍କିକ in_pragma : 1;
  /* True if we're parsing the outermost block of an if statement.  */
  ତାର୍କିକ in_if_block : 1;
  /* True if we want to lex a translated, joined string (for an
     initial #pragma pch_preprocess).  Otherwise the parser is
     responsible for concatenating strings and translating to the
     execution character set as needed.  */
  ତାର୍କିକ lex_joined_string : 1;
  /* True if, when the parser is concatenating string literals, it
     should translate them to the execution character set (false
     inside attributes).  */
  ତାର୍କିକ translate_strings_p : 1;

  /* Objective-C specific parser/lexer information.  */

  /* True if we are in a context where the Objective-C "PQ" keywords
     are considered keywords.  */
  ତାର୍କିକ objc_pq_context : 1;
  /* True if we are parsing a (potential) Objective-C foreach
     statement.  This is set to true after we parsed 'for (' and while
     we wait for 'in' or ';' to decide if it's a standard C for loop or an
     Objective-C foreach loop.  */
  ତାର୍କିକ objc_could_be_foreach_context : 1;
  /* The following flag is needed to contextualize Objective-C lexical
     analysis.  In some cases (e.g., 'int NSObject;'), it is
     undesirable to bind an identifier to an Objective-C class, even
     if a class with that name exists.  */
  ତାର୍କିକ objc_need_raw_identifier : 1;
  /* Nonzero if we're processing a __transaction statement.  The value
     is 1 | TM_STMT_ATTR_*.  */
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା in_transaction : 4;
  /* True if we are in a context where the Objective-C "Property attribute"
     keywords are valid.  */
  ତାର୍କିକ objc_property_attr_context : 1;

  /* Whether we have just seen/constructed a string-literal.  Set when
     returning a string-literal from c_parser_string_literal.  Reset
     in consume_token.  Useful when we get a parse error and see an
     unknown token, which could have been a string-literal constant
     macro.  */
  ତାର୍କିକ seen_string_literal : 1;

  /* TRUE if omp::directive, omp::decl or omp::sequence attributes may not
     appear.  */
  ତାର୍କିକ omp_attrs_forbidden_p : 1;

  /* Location of the last consumed token.  */
  location_t last_token_location;

  /* Holds state for parsing collapsed OMP_FOR loops.  Managed by
     c_parser_omp_for_loop.  */
  ସଂରଚନା omp_for_parse_data * GTY((skip)) omp_for_parse_state;

  /* If we're in the context of OpenMP directives written as C23
     attributes turned into pragma, the tokens field is temporarily
     redirected.  This holds data needed to restore state afterwards.
     It's NULL otherwise.  */
  ସଂରଚନା omp_attribute_pragma_state *in_omp_attribute_pragma;

  /* Set for omp::decl attribute parsing to the decl to which it
     appertains.  */
  ବୃକ୍ଷ in_omp_decl_attribute;

  /* Non-null only when parsing the body of an OpenMP metadirective.
     Managed by c_parser_omp_metadirective.  */
  ସଂରଚନା omp_metadirective_parse_data * GTY((skip))
    omp_metadirective_state;
};

/* Holds data needed to restore the token stream to its previous state
   after parsing an OpenMP attribute-syntax pragma.  */
ସଂରଚନା GTY(()) omp_attribute_pragma_state
{
  vec<c_token, va_gc> *token_vec;
  c_token * GTY((skip)) save_tokens;
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା save_tokens_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
ସଂରଚନା GTY(()) omp_begin_declare_variant_map_entry {
  ବୃକ୍ଷ variant;		/* The variant decl.  */
  ବୃକ୍ଷ id;		/* Name of base function.  */
  ବୃକ୍ଷ ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_entry, va_gc> *omp_begin_declare_variant_map;

ସ୍ଥିର ବୃକ୍ଷ omp_start_variant_function (c_declarator *, ବୃକ୍ଷ);
ସ୍ଥିର ଶୂନ୍ୟ omp_finish_variant_function (ବୃକ୍ଷ, ବୃକ୍ଷ, ବୃକ୍ଷ);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_tokens_buf (c_parser *parser, unsigned n)
{
  ଫେରନ୍ତୁ &parser->tokens_buf[n];
}

/* Return the error state of PARSER.  */

ତାର୍କିକ
c_parser_error (c_parser *parser)
{
  ଫେରନ୍ତୁ parser->error;
}

/* Set the error state of PARSER to ERR.  */

ଶୂନ୍ୟ
c_parser_set_error (c_parser *parser, ତାର୍କିକ err)
{
  parser->error = err;
}


/* The actual parser and external interface.  ??? Does this need to be
   garbage-collected?  */

ସ୍ଥିର GTY (()) c_parser *the_parser;

/* Read in and lex a single token, storing it in *TOKEN.  If RAW,
   context-sensitive postprocessing of the token is not done.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_lex_one_token (c_parser *parser, c_token *token, ତାର୍କିକ raw = ମିଥ୍ୟା)
{
  timevar_ଠେଲ (TV_LEX);

  ଯଦି (raw || vec_safe_length (parser->raw_tokens) == 0)
    {
      token->type = c_lex_with_flags (&token->ମୂଲ୍ୟ, &token->location,
				      &token->flags,
				      (parser->lex_joined_string
				       ? 0 : C_LEX_STRING_NO_JOIN));
      token->id_kind = C_ID_NONE;
      token->keyword = RID_MAX;
      token->pragma_kind = PRAGMA_NONE;
    }
  ଅନ୍ୟଥା
    {
      /* Use a token previously lexed as a raw look-ahead token, and
	 complete the processing on it.  */
      *token = (*parser->raw_tokens)[parser->raw_tokens_used];
      ++parser->raw_tokens_used;
      ଯଦି (parser->raw_tokens_used == vec_safe_length (parser->raw_tokens))
	{
	  vec_free (parser->raw_tokens);
	  parser->raw_tokens_used = 0;
	}
    }

  ଯଦି (raw)
    ଯାଅ out;

  ବାଛ (token->type)
    {
    ସ୍ଥିତି CPP_NAME:
      {
	ବୃକ୍ଷ decl;

	ତାର୍କିକ objc_force_identifier = parser->objc_need_raw_identifier;
	ଯଦି (c_dialect_objc ())
	  parser->objc_need_raw_identifier = ମିଥ୍ୟା;

	ଯଦି (C_IS_RESERVED_WORD (token->ମୂଲ୍ୟ))
	  {
	    ଗଣନା rid rid_code = C_RID_CODE (token->ମୂଲ୍ୟ);

	    ଯଦି (rid_code == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->ମୂଲ୍ୟ);
	      }
	    ଅନ୍ୟଥା ଯଦି (rid_code >= RID_FIRST_ADDR_SPACE
		     && rid_code <= RID_LAST_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_code - RID_FIRST_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_kind = C_ID_ADDRSPACE;
		token->keyword = rid_code;
		ଭାଙ୍ଗ;
	      }
	    ଅନ୍ୟଥା ଯଦି (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		ଯଦି (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    ଭାଙ୍ଗ;
		  }
		ଅନ୍ୟଥା ଯଦି (parser->objc_could_be_foreach_context
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
		    ଭାଙ୍ଗ;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    ଅନ୍ୟଥା ଯଦି (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		ଯଦି (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    ଭାଙ୍ଗ;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    ଅନ୍ୟଥା ଯଦି (c_dialect_objc ()
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
	    ଅନ୍ୟଥା
	      {
		token->type = CPP_KEYWORD;
		token->keyword = rid_code;
		ଭାଙ୍ଗ;
	      }
	  }

	decl = lookup_name (token->ମୂଲ୍ୟ);
	ଯଦି (decl)
	  {
	    ଯଦି (ବୃକ୍ଷ_CODE (decl) == TYPE_DECL)
	      {
		token->id_kind = C_ID_TYPENAME;
		ଭାଙ୍ଗ;
	      }
	  }
	ଅନ୍ୟଥା ଯଦି (c_dialect_objc ())
	  {
	    ବୃକ୍ଷ objc_interface_decl = objc_is_class_name (token->ମୂଲ୍ୟ);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    ଯଦି (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->ମୂଲ୍ୟ = objc_interface_decl;
		token->id_kind = C_ID_CLASSNAME;
		ଭାଙ୍ଗ;
	      }
	  }
        token->id_kind = C_ID_ID;
      }
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      ବାଛ (C_RID_CODE (token->ମୂଲ୍ୟ))
	{
	  /* Replace 'class' with '@class', 'private' with '@private',
	     etc.  This prevents confusion with the C++ keyword
	     'class', and makes the tokens consistent with other
	     Objective-C 'AT' keywords.  For example '@class' is
	     reported as RID_AT_CLASS which is consistent with
	     '@synchronized', which is reported as
	     RID_AT_SYNCHRONIZED.
	  */
	ସ୍ଥିତି RID_CLASS:     token->keyword = RID_AT_CLASS; ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_PRIVATE:   token->keyword = RID_AT_PRIVATE; ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_PROTECTED: token->keyword = RID_AT_PROTECTED; ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_PUBLIC:    token->keyword = RID_AT_PUBLIC; ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_THROW:     token->keyword = RID_AT_THROW; ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_TRY:       token->keyword = RID_AT_TRY; ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_CATCH:     token->keyword = RID_AT_CATCH; ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:            token->keyword = C_RID_CODE (token->ମୂଲ୍ୟ);
	}
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_COLON:
    ସ୍ଥିତି CPP_COMMA:
    ସ୍ଥିତି CPP_CLOSE_PAREN:
    ସ୍ଥିତି CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      ଯଦି (c_dialect_objc ())
	parser->objc_need_raw_identifier = ମିଥ୍ୟା;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_kind = (ଗଣନା pragma_kind) ବୃକ୍ଷ_INT_CST_ତଳ (token->ମୂଲ୍ୟ);
      token->ମୂଲ୍ୟ = ଖାଲି;
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଭାଙ୍ଗ;
    }
 out:
  timevar_କାଢ଼ (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  ଯଦି (parser->tokens_avail == 0)
    {
      c_lex_one_token (parser, &parser->tokens[0]);
      parser->tokens_avail = 1;
    }
  ଫେରନ୍ତୁ &parser->tokens[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  ଯଦି (parser->tokens_avail >= 2)
    ଫେରନ୍ତୁ &parser->tokens[1];
  gcc_assert (parser->tokens_avail == 1);
  gcc_assert (parser->tokens[0].type != CPP_EOF);
  gcc_assert (parser->tokens[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->tokens[1]);
  parser->tokens_avail = 2;
  ଫେରନ୍ତୁ &parser->tokens[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  ଯଦି (parser->tokens_avail >= n)
    ଫେରନ୍ତୁ &parser->tokens[n - 1];
  gcc_assert (parser->tokens_avail == n - 1);
  c_lex_one_token (parser, &parser->tokens[n - 1]);
  parser->tokens_avail = n;
  ଫେରନ୍ତୁ &parser->tokens[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  ଯଦି (parser->tokens_avail >= n)
    ଫେରନ୍ତୁ &parser->tokens[n - 1];
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା raw_len = vec_safe_length (parser->raw_tokens);
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା raw_avail
    = parser->tokens_avail + raw_len - parser->raw_tokens_used;
  gcc_assert (raw_avail >= n - 1);
  ଯଦି (raw_avail >= n)
    ଫେରନ୍ତୁ &(*parser->raw_tokens)[parser->raw_tokens_used
				  + n - 1 - parser->tokens_avail];
  vec_safe_reserve (parser->raw_tokens, 1);
  parser->raw_tokens->quick_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_tokens)[raw_len], ସତ୍ୟ);
  ଫେରନ୍ତୁ &(*parser->raw_tokens)[raw_len];
}

ତାର୍କିକ
c_keyword_starts_typename (ଗଣନା rid keyword)
{
  ବାଛ (keyword)
    {
    ସ୍ଥିତି RID_UNSIGNED:
    ସ୍ଥିତି RID_LONG:
    ସ୍ଥିତି RID_SHORT:
    ସ୍ଥିତି RID_SIGNED:
    ସ୍ଥିତି RID_COMPLEX:
    ସ୍ଥିତି RID_INT:
    ସ୍ଥିତି RID_CHAR:
    ସ୍ଥିତି RID_FLOAT:
    ସ୍ଥିତି RID_DOUBLE:
    ସ୍ଥିତି RID_VOID:
    ସ୍ଥିତି RID_DFLOAT32:
    ସ୍ଥିତି RID_DFLOAT64:
    ସ୍ଥିତି RID_DFLOAT128:
    ସ୍ଥିତି RID_DFLOAT64X:
    CASE_RID_FLOATN_NX:
    ସ୍ଥିତି RID_BOOL:
    ସ୍ଥିତି RID_BITINT:
    ସ୍ଥିତି RID_ENUM:
    ସ୍ଥିତି RID_STRUCT:
    ସ୍ଥିତି RID_UNION:
    ସ୍ଥିତି RID_TYPEOF:
    ସ୍ଥିତି RID_TYPEOF_UNQUAL:
    ସ୍ଥିତି RID_CONST:
    ସ୍ଥିତି RID_ATOMIC:
    ସ୍ଥିତି RID_VOLATILE:
    ସ୍ଥିତି RID_RESTRICT:
    ସ୍ଥିତି RID_ATTRIBUTE:
    ସ୍ଥିତି RID_FRACT:
    ସ୍ଥିତି RID_ACCUM:
    ସ୍ଥିତି RID_SAT:
    ସ୍ଥିତି RID_AUTO_TYPE:
    ସ୍ଥିତି RID_ALIGNAS:
      ଫେରନ୍ତୁ ସତ୍ୟ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଯଦି (keyword >= RID_FIRST_INT_N
	  && keyword < RID_FIRST_INT_N + ଅଙ୍କ_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_FIRST_INT_N])
	ଫେରନ୍ତୁ ସତ୍ୟ;
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }
}

/* Return true if TOKEN can start a type name,
   false otherwise.  */
ତାର୍କିକ
c_token_starts_typename (c_token *token)
{
  ବାଛ (token->type)
    {
    ସ୍ଥିତି CPP_NAME:
      ବାଛ (token->id_kind)
	{
	ସ୍ଥିତି C_ID_ID:
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	ସ୍ଥିତି C_ID_ADDRSPACE:
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	ସ୍ଥିତି C_ID_TYPENAME:
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	ସ୍ଥିତି C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  gcc_unreachable ();
	}
    ସ୍ଥିତି CPP_KEYWORD:
      ଫେରନ୍ତୁ c_keyword_starts_typename (token->keyword);
    ସ୍ଥିତି CPP_LESS:
      ଯଦି (c_dialect_objc ())
	ଫେରନ୍ତୁ ସତ୍ୟ;
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ତାର୍କିକ
c_parser_next_tokens_start_typename (c_parser *parser, ଗଣନା c_lookahead_kind la,
				     unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  ଯଦି (c_token_starts_typename (token))
    ଫେରନ୍ତୁ ସତ୍ୟ;

  /* Try a bit harder to detect an unknown typename.  */
  ଯଦି (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_kind == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->ମୂଲ୍ୟ))
    ଫେରନ୍ତୁ ସତ୍ୟ;

  ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* Return true if TOKEN, after an open parenthesis, can start a
   compound literal (either a storage class specifier allowed in that
   context, or a type name), false otherwise.  */
ସ୍ଥିର ତାର୍କିକ
c_token_starts_compound_literal (c_token *token)
{
  ବାଛ (token->type)
    {
    ସ୍ଥିତି CPP_KEYWORD:
      ବାଛ (token->keyword)
	{
	ସ୍ଥିତି RID_CONSTEXPR:
	ସ୍ଥିତି RID_REGISTER:
	ସ୍ଥିତି RID_STATIC:
	ସ୍ଥିତି RID_THREAD:
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଭାଙ୍ଗ;
	}
      /* Fall through.  */
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଫେରନ୍ତୁ c_token_starts_typename (token);
    }
}

/* Return true if TOKEN is a type qualifier, false otherwise.  */
ସ୍ଥିର ତାର୍କିକ
c_token_is_qualifier (c_token *token)
{
  ବାଛ (token->type)
    {
    ସ୍ଥିତି CPP_NAME:
      ବାଛ (token->id_kind)
	{
	ସ୍ଥିତି C_ID_ADDRSPACE:
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
    ସ୍ଥିତି CPP_KEYWORD:
      ବାଛ (token->keyword)
	{
	ସ୍ଥିତି RID_CONST:
	ସ୍ଥିତି RID_VOLATILE:
	ସ୍ଥିତି RID_RESTRICT:
	ସ୍ଥିତି RID_ATTRIBUTE:
	ସ୍ଥିତି RID_ATOMIC:
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
    ସ୍ଥିତି CPP_LESS:
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    }
}

/* Return true if the next token from PARSER is a type qualifier,
   false otherwise.  */
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ତାର୍କିକ
c_parser_next_token_is_qualifier (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  ଫେରନ୍ତୁ c_token_is_qualifier (token);
}

/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes), false otherwise.  */
ସ୍ଥିର ତାର୍କିକ
c_token_starts_declspecs (c_token *token)
{
  ବାଛ (token->type)
    {
    ସ୍ଥିତି CPP_NAME:
      ବାଛ (token->id_kind)
	{
	ସ୍ଥିତି C_ID_ID:
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	ସ୍ଥିତି C_ID_ADDRSPACE:
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	ସ୍ଥିତି C_ID_TYPENAME:
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	ସ୍ଥିତି C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  gcc_unreachable ();
	}
    ସ୍ଥିତି CPP_KEYWORD:
      ବାଛ (token->keyword)
	{
	ସ୍ଥିତି RID_STATIC:
	ସ୍ଥିତି RID_EXTERN:
	ସ୍ଥିତି RID_REGISTER:
	ସ୍ଥିତି RID_TYPEDEF:
	ସ୍ଥିତି RID_INLINE:
	ସ୍ଥିତି RID_NORETURN:
	ସ୍ଥିତି RID_AUTO:
	ସ୍ଥିତି RID_THREAD:
	ସ୍ଥିତି RID_UNSIGNED:
	ସ୍ଥିତି RID_LONG:
	ସ୍ଥିତି RID_SHORT:
	ସ୍ଥିତି RID_SIGNED:
	ସ୍ଥିତି RID_COMPLEX:
	ସ୍ଥିତି RID_INT:
	ସ୍ଥିତି RID_CHAR:
	ସ୍ଥିତି RID_FLOAT:
	ସ୍ଥିତି RID_DOUBLE:
	ସ୍ଥିତି RID_VOID:
	ସ୍ଥିତି RID_DFLOAT32:
	ସ୍ଥିତି RID_DFLOAT64:
	ସ୍ଥିତି RID_DFLOAT128:
	ସ୍ଥିତି RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	ସ୍ଥିତି RID_BOOL:
	ସ୍ଥିତି RID_BITINT:
	ସ୍ଥିତି RID_ENUM:
	ସ୍ଥିତି RID_STRUCT:
	ସ୍ଥିତି RID_UNION:
	ସ୍ଥିତି RID_TYPEOF:
	ସ୍ଥିତି RID_TYPEOF_UNQUAL:
	ସ୍ଥିତି RID_CONST:
	ସ୍ଥିତି RID_VOLATILE:
	ସ୍ଥିତି RID_RESTRICT:
	ସ୍ଥିତି RID_ATTRIBUTE:
	ସ୍ଥିତି RID_FRACT:
	ସ୍ଥିତି RID_ACCUM:
	ସ୍ଥିତି RID_SAT:
	ସ୍ଥିତି RID_ALIGNAS:
	ସ୍ଥିତି RID_ATOMIC:
	ସ୍ଥିତି RID_AUTO_TYPE:
	ସ୍ଥିତି RID_CONSTEXPR:
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଯଦି (token->keyword >= RID_FIRST_INT_N
	      && token->keyword < RID_FIRST_INT_N + ଅଙ୍କ_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_FIRST_INT_N])
	    ଫେରନ୍ତୁ ସତ୍ୟ;
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
    ସ୍ଥିତି CPP_LESS:
      ଯଦି (c_dialect_objc ())
	ଫେରନ୍ତୁ ସତ୍ୟ;
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }
}


/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes) or a static assertion, false
   otherwise.  */
ସ୍ଥିର ତାର୍କିକ
c_token_starts_declaration (c_token *token)
{
  ଯଦି (c_token_starts_declspecs (token)
      || token->keyword == RID_STATIC_ASSERT)
    ଫେରନ୍ତୁ ସତ୍ୟ;
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* Return true if the next token from PARSER can start declaration
   specifiers (not including standard attributes), false
   otherwise.  */
ତାର୍କିକ
c_parser_next_token_starts_declspecs (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);

  /* In Objective-C, a classname normally starts a declspecs unless it
     is immediately followed by a dot.  In that case, it is the
     Objective-C 2.0 "dot-syntax" for class objects, ie, calls the
     setter/getter on the class.  c_token_starts_declspecs() can't
     differentiate between the two cases because it only checks the
     current token, so we have a special check here.  */
  ଯଦି (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଫେରନ୍ତୁ c_token_starts_declspecs (token);
}

ସ୍ଥିର ତାର୍କିକ c_parser_check_balanced_raw_token_sequence (c_parser *,
							unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
ତାର୍କିକ
c_parser_next_tokens_start_declaration (c_parser *parser, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  ଯଦି (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_DOT)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  /* Labels do not start declarations.  */
  ଯଦି (token->type == CPP_NAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_COLON)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  /* A static assertion is only a declaration if followed by a semicolon;
     otherwise, it may be an expression in C2Y.  */
  ଯଦି (token->keyword == RID_STATIC_ASSERT
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_PAREN)
    {
      n += 2;
      ଯଦି (!c_parser_check_balanced_raw_token_sequence (parser, &n)
	  || c_parser_peek_nth_token_raw (parser, n)->type != CPP_CLOSE_PAREN)
	/* Invalid static assertion syntax; treat as a declaration and report a
	   syntax error there.  */
	ଫେରନ୍ତୁ ସତ୍ୟ;
      ଫେରନ୍ତୁ c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  ଯଦି (c_token_starts_declaration (token))
    ଫେରନ୍ତୁ ସତ୍ୟ;

  ଯଦି (c_parser_next_tokens_start_typename (parser, cla_nonabstract_decl, n))
    ଫେରନ୍ତୁ ସତ୍ୟ;

  ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* Consume the next token from PARSER.  */

ଶୂନ୍ୟ
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
  ଯଦି (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  ଅନ୍ୟଥା ଯଦି (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      ଯଦି (parser->tokens_avail >= 3)
        {
          parser->tokens[1] = parser->tokens[2];
          ଯଦି (parser->tokens_avail >= 4)
            parser->tokens[2] = parser->tokens[3];
        }
    }
  parser->tokens_avail--;
  parser->seen_string_literal = ମିଥ୍ୟା;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->in_pragma);
  gcc_assert (parser->tokens_avail >= 1);
  gcc_assert (parser->tokens[0].type == CPP_PRAGMA);
  ଯଦି (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  ଅନ୍ୟଥା ଯଦି (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      ଯଦି (parser->tokens_avail >= 3)
	parser->tokens[1] = parser->tokens[2];
    }
  parser->tokens_avail--;
  parser->in_pragma = ସତ୍ୟ;
}

/* Update the global input_location from TOKEN.  */
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ
c_parser_set_source_position_from_token (c_token *token)
{
  ଯଦି (token->type != CPP_EOF)
    {
      ନିବେଶ_location = token->location;
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

ସ୍ଥିର ତାର୍କିକ
c_parser_peek_conflict_marker (c_parser *parser, ଗଣନା cpp_ttype tok1_kind,
			       location_t *out_loc)
{
  c_token *token2 = c_parser_peek_2nd_token (parser);
  ଯଦି (token2->type != tok1_kind)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  ଯଦି (token3->type != tok1_kind)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  ଯଦି (token4->type != conflict_marker_get_final_tok_kind (tok1_kind))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  /* It must be at the start of the line.  */
  location_t start_loc = c_parser_peek_token (parser)->location;
  ଯଦି (LOCATION_COLUMN (start_loc) != 1)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t finish_loc = get_finish (token4->location);
  *out_loc = make_location (start_loc, start_loc, finish_loc);

  ଫେରନ୍ତୁ ସତ୍ୟ;
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

ସ୍ଥିର ତାର୍କିକ
c_parser_error_richloc (c_parser *parser, ଅଚଳ ଅକ୍ଷର *gmsgid,
			rich_location *richloc)
{
  c_token *token = c_parser_peek_token (parser);
  ଯଦି (parser->error)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  parser->error = ସତ୍ୟ;
  ଯଦି (!gmsgid)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  /* If this is actually a conflict marker, report it as such.  */
  ଯଦି (token->type == CPP_LSHIFT
      || token->type == CPP_RSHIFT
      || token->type == CPP_EQ_EQ)
    {
      location_t loc;
      ଯଦି (c_parser_peek_conflict_marker (parser, token->type, &loc))
	{
	  error_at (loc, "version control conflict marker in file");
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_group d;
  name_hint h;
  ଯଦି (parser->seen_string_literal && token->type == CPP_NAME)
    {
      ବୃକ୍ଷ name = token->ମୂଲ୍ୟ;
      ଅଚଳ ଅକ୍ଷର *token_name = IDENTIFIER_POINTER (name);
      ଅଚଳ ଅକ୍ଷର *header_hint
	= get_c_stdlib_header_for_string_macro_name (token_name);
      ଯଦି (header_hint != ଖାଲି)
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
		 token->ମୂଲ୍ୟ, /*flags=*/0, richloc);
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

ତାର୍କିକ
c_parser_error (c_parser *parser, ଅଚଳ ଅକ୍ଷର *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_set_source_position_from_token (token);
  rich_location richloc (ଧାଡ଼ି_table, ନିବେଶ_location);
  ଫେରନ୍ତୁ c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

template <typename traits_t>
ଶ୍ରେଣୀ token_pair
{
 ସର୍ବସାଧାରଣ:
  /* token_pair's ctor.  */
  token_pair () : m_open_loc (UNKNOWN_LOCATION) {}

  /* If the next token is the opening symbol for this pair, consume it and
     return true.
     Otherwise, issue an error and return false.
     In either case, record the location of the opening token.  */

  ତାର୍କିକ require_open (c_parser *parser)
  {
    c_token *token = c_parser_peek_token (parser);
    ଯଦି (token)
      m_open_loc = token->location;

    ଫେରନ୍ତୁ c_parser_require (parser, traits_t::open_token_type,
			     traits_t::open_gmsgid);
  }

  /* Consume the next token from PARSER, recording its location as
     that of the opening token within the pair.  */

  ଶୂନ୍ୟ consume_open (c_parser *parser)
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

  ତାର୍କିକ require_close (c_parser *parser) ଅଚଳ
  {
    ଫେରନ୍ତୁ c_parser_require (parser, traits_t::close_token_type,
			     traits_t::close_gmsgid, m_open_loc);
  }

  /* Like token_pair::require_close, except that tokens will be skipped
     until the desired token is found.  An error message is still produced
     if the next token is not as expected.  */

  ଶୂନ୍ୟ skip_until_found_close (c_parser *parser) ଅଚଳ
  {
    c_parser_skip_until_found (parser, traits_t::close_token_type,
			       traits_t::close_gmsgid, m_open_loc);
  }

 ବ୍ୟକ୍ତିଗତ:
  location_t m_open_loc;
};

/* Traits for token_pair<T> for tracking matching pairs of parentheses.  */

ସଂରଚନା matching_paren_traits
{
  ସ୍ଥିର ଅଚଳ ଗଣନା cpp_ttype open_token_type = CPP_OPEN_PAREN;
  ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ open_gmsgid;
  ସ୍ଥିର ଅଚଳ ଗଣନା cpp_ttype close_token_type = CPP_CLOSE_PAREN;
  ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ close_gmsgid;
};

ଅଚଳ ଅକ୍ଷର * ଅଚଳ matching_paren_traits::open_gmsgid = "expected %<(%>";
ଅଚଳ ଅକ୍ଷର * ଅଚଳ matching_paren_traits::close_gmsgid = "expected %<)%>";

/* "matching_parens" is a token_pair<T> class for tracking matching
   pairs of parentheses.  */

ପ୍ରକାରବ୍ୟାଖ୍ୟା token_pair<matching_paren_traits> matching_parens;

/* Traits for token_pair<T> for tracking matching pairs of braces.  */

ସଂରଚନା matching_brace_traits
{
  ସ୍ଥିର ଅଚଳ ଗଣନା cpp_ttype open_token_type = CPP_OPEN_BRACE;
  ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ open_gmsgid;
  ସ୍ଥିର ଅଚଳ ଗଣନା cpp_ttype close_token_type = CPP_CLOSE_BRACE;
  ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ close_gmsgid;
};

ଅଚଳ ଅକ୍ଷର * ଅଚଳ matching_brace_traits::open_gmsgid = "expected %<{%>";
ଅଚଳ ଅକ୍ଷର * ଅଚଳ matching_brace_traits::close_gmsgid = "expected %<}%>";

/* "matching_braces" is a token_pair<T> class for tracking matching
   pairs of braces.  */

ପ୍ରକାରବ୍ୟାଖ୍ୟା token_pair<matching_brace_traits> matching_braces;

/* Get a description of the matching symbol to TYPE e.g. "(" for
   CPP_CLOSE_PAREN.  */

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *
get_matching_ପ୍ରତୀକ (ଗଣନା cpp_ttype type)
{
  ବାଛ (type)
    {
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    ସ୍ଥିତି CPP_CLOSE_PAREN:
      ଫେରନ୍ତୁ "(";
    ସ୍ଥିତି CPP_CLOSE_BRACE:
      ଫେରନ୍ତୁ "{";
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

ତାର୍କିକ
c_parser_require (c_parser *parser,
		  ଗଣନା cpp_ttype type,
		  ଅଚଳ ଅକ୍ଷର *msgid,
		  location_t matching_location,
		  ତାର୍କିକ type_is_unique)
{
  ଯଦି (c_parser_next_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }
  ଅନ୍ୟଥା
    {
      location_t next_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (next_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      ଯଦି (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->last_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      ତାର୍କିକ added_matching_location = ମିଥ୍ୟା;
      ଯଦି (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.add_location_if_nearby (*global_dc, matching_location);

      ଯଦି (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	ଯଦି (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_ପ୍ରତୀକ (type));

      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }
}

/* If the next token is the indicated keyword, consume it.  Otherwise,
   issue the error MSGID.  Returns true if found, false otherwise.  */

ସ୍ଥିର ତାର୍କିକ
c_parser_require_keyword (c_parser *parser,
			  ଗଣନା rid keyword,
			  ଅଚଳ ଅକ୍ଷର *msgid)
{
  ଯଦି (c_parser_next_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }
  ଅନ୍ୟଥା
    {
      c_parser_error (parser, msgid);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
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

ଶୂନ୍ୟ
c_parser_skip_until_found (c_parser *parser,
			   ଗଣନା cpp_ttype type,
			   ଅଚଳ ଅକ୍ଷର *msgid,
			   location_t matching_location)
{
  unsigned nesting_depth = 0;

  ଯଦି (c_parser_require (parser, type, msgid, matching_location))
    {
      ଯଦି (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->in_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ଯଦି (token->type == CPP_EOF)
	    {
	      parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	      parser->tokens_avail
		= parser->in_omp_attribute_pragma->save_tokens_avail;
	      parser->in_omp_attribute_pragma = ଖାଲି;
	    }
	}
      ଫେରନ୍ତୁ;
    }

  /* Skip tokens until the desired token is found.  */
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      ଯଦି (token->type == type && !nesting_depth)
	{
	  c_parser_consume_token (parser);
	  ଯଦି (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->in_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      ଯଦି (token->type == CPP_EOF)
		{
		  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
		  parser->tokens_avail
		    = parser->in_omp_attribute_pragma->save_tokens_avail;
		  parser->in_omp_attribute_pragma = ଖାଲି;
		}
	    }
	  ଭାଙ୍ଗ;
	}

      /* If we've run out of tokens, stop.  */
      ଯଦି (token->type == CPP_EOF)
	ଫେରନ୍ତୁ;
      ଯଦି (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	ଫେରନ୍ତୁ;
      ଯଦି (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      ଅନ୍ୟଥା ଯଦି (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  ଯଦି (nesting_depth-- == 0)
	    ଭାଙ୍ଗ;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = ମିଥ୍ୟା;
}

/* Skip tokens until the end of a parameter is found, but do not
   consume the comma, semicolon or closing delimiter.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_skip_to_end_of_parameter (c_parser *parser)
{
  unsigned nesting_depth = 0;

  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      c_token *token = c_parser_peek_token (parser);
      ଯଦି ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_depth)
	ଭାଙ୍ଗ;
      /* If we've run out of tokens, stop.  */
      ଯଦି (token->type == CPP_EOF)
	ଫେରନ୍ତୁ;
      ଯଦି (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	ଫେରନ୍ତୁ;
      ଯଦି (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      ଅନ୍ୟଥା ଯଦି (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  ଯଦି (nesting_depth-- == 0)
	    ଭାଙ୍ଗ;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = ମିଥ୍ୟା;
}

/* Skip tokens until a non-nested closing curly brace is the next
   token, or there are no more tokens. Return true in the first case,
   false otherwise.  */

ସ୍ଥିର ତାର୍କିକ
c_parser_skip_to_closing_brace (c_parser *parser)
{
  unsigned nesting_depth = 0;

  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      c_token *token = c_parser_peek_token (parser);

      ବାଛ (token->type)
	{
	ସ୍ଥିତି CPP_PRAGMA_EOL:
	  ଯଦି (!parser->in_pragma)
	    ଭାଙ୍ଗ;
	  /* FALLTHRU */
	ସ୍ଥିତି CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;

	ସ୍ଥିତି CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  ଯଦି (nesting_depth-- == 0)
	    ଫେରନ୍ତୁ ସତ୍ୟ;
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  ଭାଙ୍ଗ;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଭାଙ୍ଗ;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Expect to be at the end of the pragma directive and consume an
   end of line marker.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_skip_to_pragma_eol (c_parser *parser, ତାର୍କିକ error_if_not_eol = ସତ୍ୟ)
{
  gcc_assert (parser->in_pragma);
  parser->in_pragma = ମିଥ୍ୟା;

  ଯଦି (error_if_not_eol && c_parser_peek_token (parser)->type != CPP_PRAGMA_EOL)
    c_parser_error (parser, "expected end of line");

  cpp_ttype token_type;
  କର
    {
      c_token *token = c_parser_peek_token (parser);
      token_type = token->type;
      ଯଦି (token_type == CPP_EOF)
	ଭାଙ୍ଗ;
      c_parser_consume_token (parser);
    }
  ଯେତେବେଳେ (token_type != CPP_PRAGMA_EOL);

  ଯଦି (parser->in_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      ଯଦି (token->type == CPP_EOF)
	{
	  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	  parser->tokens_avail
	    = parser->in_omp_attribute_pragma->save_tokens_avail;
	  parser->in_omp_attribute_pragma = ଖାଲି;
	}
    }

  parser->error = ମିଥ୍ୟା;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
ସ୍ଥିର ଶୂନ୍ୟ
c_parser_skip_to_pragma_omp_end_declare_variant (c_parser *parser)
{
  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth = 0; depth >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      ବାଛ (token->type)
	{
	ସ୍ଥିତି CPP_PRAGMA_EOL:
	  ଯଦି (!parser->in_pragma)
	    ଭାଙ୍ଗ;
	  /* FALLTHRU */
	ସ୍ଥିତି CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  ଫେରନ୍ତୁ;

	ସ୍ଥିତି CPP_PRAGMA:
	  ଯଦି ((token->pragma_kind == PRAGMA_OMP_BEGIN
	       || token->pragma_kind == PRAGMA_OMP_END)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      ବୃକ୍ଷ id1 = c_parser_peek_nth_token (parser, 2)->ମୂଲ୍ୟ;
	      ବୃକ୍ଷ id2 = c_parser_peek_nth_token (parser, 3)->ମୂଲ୍ୟ;
	      ଯଦି (strcmp (IDENTIFIER_POINTER (id1), "declare") == 0
		  && strcmp (IDENTIFIER_POINTER (id2), "variant") == 0)
		{
		  ଯଦି (token->pragma_kind == PRAGMA_OMP_BEGIN)
		    depth++;
		  ଅନ୍ୟଥା
		    depth--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	  ଜାରି;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଭାଙ୍ଗ;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Skip tokens until we have consumed an entire block, or until we
   have consumed a non-nested ';'.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_skip_to_end_of_block_or_statement (c_parser *parser,
					    ତାର୍କିକ metadirective_p = ମିଥ୍ୟା)
{
  unsigned nesting_depth = 0;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା bracket_depth = 0;
  ତାର୍କିକ save_error = parser->error;

  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      ବାଛ (token->type)
	{
	ସ୍ଥିତି CPP_EOF:
	  ଫେରନ୍ତୁ;

	ସ୍ଥିତି CPP_PRAGMA_EOL:
	  ଯଦି (parser->in_pragma)
	    ଫେରନ୍ତୁ;
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  ଯଦି (!nesting_depth && (!metadirective_p || bracket_depth <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      ଯାଅ finished;
	    }
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  ଯଦି ((nesting_depth == 0 || --nesting_depth == 0)
	      && (!metadirective_p || bracket_depth <= 0))
	    {
	      c_parser_consume_token (parser);
	      ଯାଅ finished;
	    }
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  ଯଦି (metadirective_p && nesting_depth == 0)
	    ++bracket_depth;
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି CPP_CLOSE_PAREN:
	  ଯଦି (metadirective_p && nesting_depth == 0)
	    --bracket_depth;
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	  parser->error = save_error;
	  ଜାରି;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଭାଙ୍ଗ;
	}

      c_parser_consume_token (parser);
    }

 finished:
  parser->error = ମିଥ୍ୟା;
}

/* CPP's options (initialized by c-opts.cc).  */
ବାହ୍ୟ cpp_options *cpp_opts;

/* Save the warning flags which are controlled by __extension__.  */

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା
disable_extension_diagnostics (ଶୂନ୍ୟ)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = (pedantic
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
  ଫେରନ୍ତୁ ret;
}

/* Restore the warning flags which are controlled by __extension__.
   FLAGS is the return value from disable_extension_diagnostics.  */

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ
restore_extension_diagnostics (ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
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
ସଂରଚନା oacc_routine_data {
  ତାର୍କିକ error_seen; /* Set if error has been reported.  */
  ତାର୍କିକ fndecl_seen; /* Set if one fn decl/definition has been seen already.  */
  ବୃକ୍ଷ clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
ସ୍ଥିର ବୃକ୍ଷ objc_foreach_break_label, objc_foreach_continue_label;

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
ସଂରଚନା omp_for_parse_data {
  ଗଣନା ବୃକ୍ଷ_code code;
  ବୃକ୍ଷ declv, condv, incrv, initv;
  ବୃକ୍ଷ pre_body;
  ବୃକ୍ଷ bindings;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2;	/* Expected nesting depth.  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth;	/* Current nesting depth.  */
  location_t for_loc;
  ତାର୍କିକ ordered : 1;
  ତାର୍କିକ inscan : 1;
  ତାର୍କିକ want_nested_loop : 1;
  ତାର୍କିକ in_intervening_code : 1;
  ତାର୍କିକ saw_intervening_code: 1;
  ତାର୍କିକ perfect_nesting_fail : 1;
  ତାର୍କିକ fail : 1;
};

ସଂରଚନା attr_state
{
  /* True if we parsed a musttail attribute for return.  */
  ତାର୍କିକ musttail_p;

  ଶୂନ୍ୟ reset () { musttail_p = ମିଥ୍ୟା; }
};

ସ୍ଥିର ତାର୍କିକ c_parser_nth_token_starts_std_attributes (c_parser *,
						      unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ସ୍ଥିର ବୃକ୍ଷ c_parser_std_attribute_specifier_sequence (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_external_declaration (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_asm_definition (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_declaration_or_fndef (c_parser *, ତାର୍କିକ, ତାର୍କିକ, ତାର୍କିକ,
					   ତାର୍କିକ, ତାର୍କିକ, ତାର୍କିକ, ବୃକ୍ଷ * = ଖାଲି,
					   vec<c_token> * = ଖାଲି,
					   ତାର୍କିକ have_attrs = ମିଥ୍ୟା,
					   ବୃକ୍ଷ attrs = ଖାଲି,
					   ସଂରଚନା oacc_routine_data * = ଖାଲି,
					   ତାର୍କିକ * = ଖାଲି);
ସ୍ଥିର ତାର୍କିକ c_parser_handle_statement_omp_attributes (c_parser *, ବୃକ୍ଷ &,
						      ତାର୍କିକ *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_static_assert_declaration_no_semi (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_static_assert_declaration (c_parser *);
ସ୍ଥିର ସଂରଚନା c_typespec c_parser_enum_specifier (c_parser *);
ସ୍ଥିର ସଂରଚନା c_typespec c_parser_struct_or_union_specifier (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_struct_declaration (c_parser *, ବୃକ୍ଷ *);
ସ୍ଥିର ସଂରଚନା c_typespec c_parser_typeof_specifier (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_alignas_specifier (c_parser *);
ସ୍ଥିର ସଂରଚନା c_declarator *c_parser_direct_declarator (c_parser *, ତାର୍କିକ,
							c_dtr_syn, ତାର୍କିକ *);
ସ୍ଥିର ସଂରଚନା c_declarator *c_parser_direct_declarator_inner (c_parser *,
							      ତାର୍କିକ,
							      ସଂରଚନା c_declarator *);
ସ୍ଥିର ସଂରଚନା c_arg_info *c_parser_parms_declarator (c_parser *, ତାର୍କିକ, ବୃକ୍ଷ,
						     ତାର୍କିକ);
ସ୍ଥିର ସଂରଚନା c_arg_info *c_parser_parms_list_declarator (c_parser *, ବୃକ୍ଷ,
							  ବୃକ୍ଷ, ତାର୍କିକ);
ସ୍ଥିର ସଂରଚନା c_parm *c_parser_parameter_declaration (c_parser *, ବୃକ୍ଷ, ତାର୍କିକ);
ସ୍ଥିର ବୃକ୍ଷ c_parser_asm_string_literal (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_simple_asm_ପଦସମଷ୍ଟି (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_gnu_attributes (c_parser *);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_initializer (c_parser *, ବୃକ୍ଷ);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_braced_init (c_parser *, ବୃକ୍ଷ, ତାର୍କିକ,
					   ସଂରଚନା obstack *, ତାର୍କିକ);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_initelt (c_parser *, ସଂରଚନା obstack *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_initval (c_parser *, ସଂରଚନା c_ପଦସମଷ୍ଟି *,
			      ସଂରଚନା obstack *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_compound_statement (c_parser *, location_t * = ଖାଲି);
ସ୍ଥିର location_t c_parser_compound_statement_nostart (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_label (c_parser *, ବୃକ୍ଷ);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_statement (c_parser *, ତାର୍କିକ *, location_t * = ଖାଲି);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_statement_after_labels (c_parser *, ତାର୍କିକ *, ବୃକ୍ଷ,
					     vec<ବୃକ୍ଷ> * = ଖାଲି,
					     attr_state = {});
ସ୍ଥିର ବୃକ୍ଷ c_parser_c99_block_statement (c_parser *, ତାର୍କିକ *,
					  location_t * = ଖାଲି);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_if_statement (c_parser *, ତାର୍କିକ *, vec<ବୃକ୍ଷ> *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_switch_statement (c_parser *, ତାର୍କିକ *, ବୃକ୍ଷ);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_while_statement (c_parser *, ତାର୍କିକ, unsigned short, ତାର୍କିକ,
				      ତାର୍କିକ *, ବୃକ୍ଷ);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_do_statement (c_parser *, ତାର୍କିକ, unsigned short, ତାର୍କିକ,
				   ବୃକ୍ଷ);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_for_statement (c_parser *, ତାର୍କିକ, unsigned short, ତାର୍କିକ,
				    ତାର୍କିକ *, ବୃକ୍ଷ);
ସ୍ଥିର ବୃକ୍ଷ c_parser_asm_statement (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_asm_operands (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_asm_goto_operands (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_asm_clobbers (c_parser *);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_ପଦସମଷ୍ଟି_no_commas (c_parser *, ସଂରଚନା c_ପଦସମଷ୍ଟି *,
					      ବୃକ୍ଷ = NULL_ବୃକ୍ଷ);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_conditional_expression (c_parser *,
						      ସଂରଚନା c_ପଦସମଷ୍ଟି *, ବୃକ୍ଷ);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_ଦ୍ୱିମିକ_expression (c_parser *, ସଂରଚନା c_ପଦସମଷ୍ଟି *,
						 ବୃକ୍ଷ);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_cast_expression (c_parser *, ସଂରଚନା c_ପଦସମଷ୍ଟି *);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_unary_expression (c_parser *);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_sizeof_or_countof_expression (c_parser *,
							    ଗଣନା rid);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_alignof_expression (c_parser *);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_maxof_or_minof_expression (c_parser *, ଗଣନା rid);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_postfix_expression (c_parser *);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_postfix_expression_after_paren_type (c_parser *,
								   ସଂରଚନା c_declspecs *,
								   ସଂରଚନା c_type_name *,
								   location_t);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_postfix_expression_after_primary (c_parser *,
								location_t loc,
								ସଂରଚନା c_ପଦସମଷ୍ଟି);
ସ୍ଥିର ବୃକ୍ଷ c_parser_transaction (c_parser *, ଗଣନା rid);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_transaction_expression (c_parser *, ଗଣନା rid);
ସ୍ଥିର ବୃକ୍ଷ c_parser_transaction_cancel (c_parser *);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_expression (c_parser *);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_expression_conv (c_parser *);
ସ୍ଥିର vec<ବୃକ୍ଷ, va_gc> *c_parser_ପଦସମଷ୍ଟି_list (c_parser *, ତାର୍କିକ, ତାର୍କିକ,
					     vec<ବୃକ୍ଷ, va_gc> **, location_t *,
					     ବୃକ୍ଷ *, vec<location_t> *,
					     unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା * = ଖାଲି);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_has_attribute_expression (c_parser *);

ସ୍ଥିର ଶୂନ୍ୟ c_parser_oacc_declare (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_oacc_enter_exit_data (c_parser *, ତାର୍କିକ);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_oacc_update (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_construct (c_parser *, ତାର୍କିକ *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_groupprivate (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_threadprivate (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_barrier (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_depobj (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_flush (c_parser *);
ସ୍ଥିର ତାର୍କିକ c_parser_omp_next_tokens_can_be_canon_loop (c_parser *,
							ଗଣନା ବୃକ୍ଷ_code, ତାର୍କିକ);
ସ୍ଥିର ବୃକ୍ଷ c_parser_omp_loop_nest (c_parser *, ତାର୍କିକ *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_omp_for_loop (location_t, c_parser *, ଗଣନା ବୃକ୍ଷ_code,
				   ବୃକ୍ଷ, ବୃକ୍ଷ *, ତାର୍କିକ *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_taskwait (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_taskyield (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_cancel (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_nothing (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_metadirective (c_parser *, ତାର୍କିକ *);

ଗଣନା pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
ସ୍ଥିର ତାର୍କିକ c_parser_pragma (c_parser *, ଗଣନା pragma_context, ତାର୍କିକ *, ବୃକ୍ଷ);
ସ୍ଥିର ତାର୍କିକ c_parser_omp_cancellation_point (c_parser *, ଗଣନା pragma_context);
ସ୍ଥିର ତାର୍କିକ c_parser_omp_target (c_parser *, ଗଣନା pragma_context, ତାର୍କିକ *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_begin (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_end (c_parser *);
ସ୍ଥିର ତାର୍କିକ c_parser_omp_declare (c_parser *, ଗଣନା pragma_context);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_requires (c_parser *);
ସ୍ଥିର ତାର୍କିକ c_parser_omp_error (c_parser *, ଗଣନା pragma_context);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_assumption_clauses (c_parser *, ତାର୍କିକ);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_allocate (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_assumes (c_parser *);
ସ୍ଥିର ତାର୍କିକ c_parser_omp_ordered (c_parser *, ଗଣନା pragma_context, ତାର୍କିକ *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_omp_dispatch (location_t, c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_omp_interop (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_oacc_routine (c_parser *, ଗଣନା pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
ସ୍ଥିର ଶୂନ୍ୟ c_parser_objc_class_definition (c_parser *, ବୃକ୍ଷ);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_objc_class_instance_variables (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_objc_class_declaration (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_objc_alias_declaration (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_objc_protocol_definition (c_parser *, ବୃକ୍ଷ);
ସ୍ଥିର ତାର୍କିକ c_parser_objc_method_type (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_objc_method_definition (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_objc_methodprotolist (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_objc_methodproto (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_objc_method_decl (c_parser *, ତାର୍କିକ, ବୃକ୍ଷ *, ବୃକ୍ଷ *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_objc_type_name (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_objc_protocol_refs (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_objc_try_catch_finally_statement (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_objc_synchronized_statement (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_objc_selector (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_objc_selector_arg (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_objc_receiver (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_objc_message_args (c_parser *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_objc_keywordexpr (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_objc_at_property_declaration (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_objc_at_synthesize_declaration (c_parser *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_objc_at_dynamic_declaration (c_parser *);
ସ୍ଥିର ତାର୍କିକ c_parser_objc_diagnose_bad_element_prefix
  (c_parser *, ସଂରଚନା c_declspecs *);
ସ୍ଥିର location_t c_parser_parse_rtl_body (c_parser *, ଅକ୍ଷର *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_handle_musttail (c_parser *, ବୃକ୍ଷ, attr_state &);

#ଯଦି ENABLE_ANALYZER

ନାମାକାଶ ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

ଶ୍ରେଣୀ c_translation_unit : ସର୍ବସାଧାରଣ translation_unit
{
ସର୍ବସାଧାରଣ:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  ବୃକ୍ଷ lookup_constant_by_id (ବୃକ୍ଷ id) ଅଚଳ final override
  {
    /* Consider decls.  */
    ଯଦି (ବୃକ୍ଷ decl = lookup_name (id))
      ଯଦି (ବୃକ୍ଷ_CODE (decl) == CONST_DECL)
	ଯଦି (ବୃକ୍ଷ ମୂଲ୍ୟ = DECL_INITIAL (decl))
	  ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == INTEGER_CST)
	    ଫେରନ୍ତୁ ମୂଲ୍ୟ;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    ଯଦି (cpp_macro_p (hashnode))
      ଯଦି (ବୃକ୍ଷ ମୂଲ୍ୟ = consider_macro (hashnode->ମୂଲ୍ୟ.macro))
	ଫେରନ୍ତୁ ମୂଲ୍ୟ;

    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  }

  ବୃକ୍ଷ
  lookup_type_by_id (ବୃକ୍ଷ id) ଅଚଳ final override
  {
    ଯଦି (ବୃକ୍ଷ type_decl = lookup_name (id))
	ଯଦି (ବୃକ୍ଷ_CODE (type_decl) == TYPE_DECL)
	  {
	    ବୃକ୍ଷ record_type = ବୃକ୍ଷ_TYPE (type_decl);
	    ଯଦି (ବୃକ୍ଷ_CODE (record_type) == RECORD_TYPE)
	      ଫେରନ୍ତୁ record_type;
	  }

    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  }

  ବୃକ୍ଷ
  lookup_global_var_by_id (ବୃକ୍ଷ id) ଅଚଳ final override
  {
    ଯଦି (ବୃକ୍ଷ var_decl = lookup_name (id))
      ଯଦି (ବୃକ୍ଷ_CODE (var_decl) == VAR_DECL)
				ଫେରନ୍ତୁ var_decl;

    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  }

ବ୍ୟକ୍ତିଗତ:
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
  ବୃକ୍ଷ consider_macro (cpp_macro *macro, ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth = 0) ଅଚଳ
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (depth >= 0);

    ଯଦି (macro->paramc > 0)
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    ଯଦି (macro->kind != cmk_macro)
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    ଯଦି (macro->ଗଣନା_2 != 1)
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    ଅଚଳ cpp_token &tok = macro->exp.tokens[0];
    ଯଦି (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	ଯଦି (depth >= param_analyzer_max_macro_alias_depth)
	  ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;

	cpp_hashnode *alias = tok.val.ଗଣ୍ଠି.ଗଣ୍ଠି;
	ଯଦି (cpp_macro_p (alias))
	  ଫେରନ୍ତୁ consider_macro (alias->ମୂଲ୍ୟ.macro, depth + 1);

	/* Not a simple alias.  */
	ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
      }
    ଅନ୍ୟଥା ଯଦି (tok.type != CPP_ସଂଖ୍ୟା)
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;

    cpp_reader *old_parse_in = parse_in;
    parse_in = cpp_create_reader (CLK_GNUC89, ଖାଲି, ଧାଡ଼ି_table);

    pretty_printer pp;
    pp_string (&pp, (ଅଚଳ ଅକ୍ଷର *) tok.val.str.text);
    pp_newline (&pp);
    cpp_ଠେଲ_buffer (parse_in,
		     (ଅଚଳ unsigned ଅକ୍ଷର *) pp_formatted_text (&pp),
		     strlen (pp_formatted_text (&pp)),
		     0);

    ବୃକ୍ଷ ମୂଲ୍ୟ;
    location_t loc;
    unsigned ଅକ୍ଷର cpp_flags;
    c_lex_with_flags (&ମୂଲ୍ୟ, &loc, &cpp_flags, 0);

    cpp_destroy (parse_in);
    parse_in = old_parse_in;

    ଯଦି (ମୂଲ୍ୟ && ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == INTEGER_CST)
      ଫେରନ୍ତୁ ମୂଲ୍ୟ;

    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_translation_unit (c_parser *parser)
{
  ଯଦି (c_parser_next_token_is (parser, CPP_EOF))
    {
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C forbids an empty translation unit");
    }
  ଅନ୍ୟଥା
    {
      ଶୂନ୍ୟ *obstack_position = obstack_alloc (&parser_obstack, 0);
      mark_valid_location_for_stdc_pragma (ମିଥ୍ୟା);
      କର
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_EOF));
    }

  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
  ବୃକ୍ଷ decl;
  FOR_EACH_VEC_ELT (incomplete_record_decls, i, decl)
    ଯଦି (DECL_SIZE (decl) == NULL_ବୃକ୍ଷ && ବୃକ୍ଷ_TYPE (decl) != error_mark_ଗଣ୍ଠି)
      error ("storage size of %q+D isn%'t known", decl);

  ଯଦି (vec_safe_length (current_omp_declare_target_attribute))
    {
      c_omp_declare_target_attr
	a = current_omp_declare_target_attribute->କାଢ଼ ();
      ଯଦି (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_safe_truncate (current_omp_declare_target_attribute, 0);
    }
  ଯଦି (vec_safe_length (current_omp_begin_assumes))
    {
      ଯଦି (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_safe_truncate (current_omp_begin_assumes, 0);
    }
  ଯଦି (vec_safe_length (current_omp_declare_variant_attribute))
    {
      ଯଦି (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_safe_truncate (current_omp_declare_variant_attribute, 0);
    }
  ଯଦି (vec_safe_length (omp_begin_declare_variant_map))
    {
      unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
      omp_begin_declare_variant_map_entry *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_finish_variant_function (e->variant, e->id, e->ctx);
      vec_safe_truncate (omp_begin_declare_variant_map, 0);
    }

#ଯଦି ENABLE_ANALYZER
  ଯଦି (flag_analyzer)
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_external_declaration (c_parser *parser)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ext;
  ବାଛ (c_parser_peek_token (parser)->type)
    {
    ସ୍ଥିତି CPP_KEYWORD:
      ବାଛ (c_parser_peek_token (parser)->keyword)
	{
	ସ୍ଥିତି RID_EXTENSION:
	  ext = disable_extension_diagnostics ();
	  c_parser_consume_token (parser);
	  c_parser_external_declaration (parser);
	  restore_extension_diagnostics (ext);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_ASM:
	  c_parser_asm_definition (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_INTERFACE:
	ସ୍ଥିତି RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_definition (parser, NULL_ବୃକ୍ଷ);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_protocol_definition (parser, NULL_ବୃକ୍ଷ);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_PROPERTY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_property_declaration (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_SYNTHESIZE:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_synthesize_declaration (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_DYNAMIC:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_dynamic_declaration (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_END:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_finish_implementation ();
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଯାଅ decl_or_fndef;
	}
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_SEMICOLON:
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_PRAGMA:
      mark_valid_location_for_stdc_pragma (ସତ୍ୟ);
      c_parser_pragma (parser, pragma_external, ଖାଲି, NULL_ବୃକ୍ଷ);
      mark_valid_location_for_stdc_pragma (ମିଥ୍ୟା);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_PLUS:
    ସ୍ଥିତି CPP_MINUS:
      ଯଦି (c_dialect_objc ())
	{
	  c_parser_objc_method_definition (parser);
	  ଭାଙ୍ଗ;
	}
      /* Else fall through, and yield a syntax error trying to parse
	 as a declaration or function definition.  */
      /* FALLTHRU */
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
    decl_or_fndef:
      /* A declaration or a function definition (or, in Objective-C,
	 an @interface or @protocol with prefix attributes).  We can
	 only tell which after parsing the declaration specifiers, if
	 any, and the first declarator.  */
      c_parser_declaration_or_fndef (parser, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ମିଥ୍ୟା, ସତ୍ୟ,
				     ମିଥ୍ୟା);
      ଭାଙ୍ଗ;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ c_parser_handle_directive_omp_attributes (ବୃକ୍ଷ &, vec<c_token> *&,
						      vec<c_token> *);
ସ୍ଥିର ଶୂନ୍ୟ c_finish_omp_declare_simd (c_parser *, ବୃକ୍ଷ, ବୃକ୍ଷ, vec<c_token> *);
ସ୍ଥିର ଶୂନ୍ୟ c_finish_oacc_routine (ସଂରଚନା oacc_routine_data *, ବୃକ୍ଷ, ତାର୍କିକ);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

ସ୍ଥିର ଶୂନ୍ୟ
add_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  ଯଦି (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    ଫେରନ୍ତୁ;

  ବୃକ୍ଷ stmt = build0 (DEBUG_BEGIN_STMT, void_type_ଗଣ୍ଠି);
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

ସ୍ଥିର ବୃକ୍ଷ
handle_assume_attribute (location_t here, ବୃକ୍ଷ attrs, ତାର୍କିକ nested)
{
  ଯଦି (nested)
    ପାଇଁ (ବୃକ୍ଷ attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", ବୃକ୍ଷ_CHAIN (attr)))
      {
	ବୃକ୍ଷ args = ବୃକ୍ଷ_ମୂଲ୍ୟ (attr);
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା nargs = list_length (args);
	ଯଦି (nargs != 1)
	  {
	    error_at (here, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (here, "expected %i, found %i", 1, nargs);
	  }
	ଅନ୍ୟଥା
	  {
	    ବୃକ୍ଷ arg = ବୃକ୍ଷ_ମୂଲ୍ୟ (args);
	    arg = c_objc_common_truthvalue_conversion (here, arg);
	    arg = c_fully_fold (arg, ମିଥ୍ୟା, ଖାଲି);
	    ଯଦି (arg != error_mark_ଗଣ୍ଠି)
	      {
		ବୃକ୍ଷ fn = build_call_ପଦସମଷ୍ଟି_internal_loc (here, IFN_ASSUME,
							void_type_ଗଣ୍ଠି, 1,
							arg);
		add_stmt (fn);
	      }
	  }
      }
  ଅନ୍ୟଥା
    pedwarn (here, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  ଫେରନ୍ତୁ remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_maybe_reclassify_token (c_parser *parser)
{
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      ଯଦି (token->id_kind == C_ID_ID || token->id_kind == C_ID_TYPENAME)
	{
	  ବୃକ୍ଷ decl = lookup_name (token->ମୂଲ୍ୟ);

	  token->id_kind = C_ID_ID;
	  ଯଦି (decl)
	    {
	      ଯଦି (ବୃକ୍ଷ_CODE (decl) == TYPE_DECL)
		token->id_kind = C_ID_TYPENAME;
	    }
	  ଅନ୍ୟଥା ଯଦି (c_dialect_objc ())
	    {
	      ବୃକ୍ଷ objc_interface_decl = objc_is_class_name (token->ମୂଲ୍ୟ);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      ଯଦି (objc_interface_decl)
		{
		  token->ମୂଲ୍ୟ = objc_interface_decl;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_declaration_or_fndef (c_parser *parser, ତାର୍କିକ fndef_ok,
			       ତାର୍କିକ static_assert_ok, ତାର୍କିକ empty_ok,
			       ତାର୍କିକ nested, ତାର୍କିକ start_attr_ok,
			       ତାର୍କିକ simple_ok,
			       ବୃକ୍ଷ *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       ତାର୍କିକ have_attrs /* = false */,
			       ବୃକ୍ଷ attrs /* = NULL_TREE */,
			       ସଂରଚନା oacc_routine_data *oacc_routine_data
			       /* = NULL */,
			       ତାର୍କିକ *fallthru_attr_p /* = NULL */)
{
  ସଂରଚନା c_declspecs *specs;
  ବୃକ୍ଷ prefix_attrs;
  ବୃକ୍ଷ all_prefix_attrs;
  ତାର୍କିକ diagnosed_no_specs = ମିଥ୍ୟା;
  location_t here = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ result = NULL_ବୃକ୍ଷ;

  add_debug_begin_stmt (c_parser_peek_token (parser)->location);

  ଯଦି (static_assert_ok
      && c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      ଫେରନ୍ତୁ result;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  ଯଦି (have_attrs)
    {
      declspecs_add_attrs (here, specs, attrs);
      specs->non_std_attrs_seen_p = ମିଥ୍ୟା;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  ଯଦି (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_kind == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->ମୂଲ୍ୟ)))
    {
      ବୃକ୍ଷ name = c_parser_peek_token (parser)->ମୂଲ୍ୟ;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (here);
      ଯଦି (tag_exists_p (RECORD_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.add_fixit_ଭର୍ତ୍ତି_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      ଅନ୍ୟଥା ଯଦି (tag_exists_p (UNION_TYPE, name))
	{
	  richloc.add_fixit_ଭର୍ତ୍ତି_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      ଅନ୍ୟଥା ଯଦି (tag_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.add_fixit_ଭର୍ତ୍ତି_before ("enum ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<enum%> keyword to refer to the type",
		    name);
	}
      ଅନ୍ୟଥା
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (name, FUZZY_LOOKUP_TYPENAME,
					      here);
	  ଯଦି (ଅଚଳ ଅକ୍ଷର *suggestion = hint.suggestion ())
	    {
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			name, suggestion);
	    }
	  ଅନ୍ୟଥା
	    error_at (here, "unknown type name %qE", name);
	}

      /* Parse declspecs normally to get a correct pointer type, but avoid
         a further "fails to be a type name" error.  Refuse nested functions
         since it is not how the user likely wants us to recover.  */
      c_parser_peek_token (parser)->type = CPP_KEYWORD;
      c_parser_peek_token (parser)->keyword = RID_VOID;
      c_parser_peek_token (parser)->ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  ଯଦି (c_parser_nth_token_starts_std_attributes (parser, 1))
    have_attrs = ସତ୍ୟ;

  c_parser_declspecs (parser, specs, ସତ୍ୟ, ସତ୍ୟ, start_attr_ok,
		      ସତ୍ୟ, ସତ୍ୟ, start_attr_ok, ସତ୍ୟ, cla_nonabstract_decl);
  ଯଦି (parser->error)
    {
      c_parser_skip_to_end_of_block_or_statement (parser);
      ଫେରନ୍ତୁ result;
    }
  ଯଦି (nested && !specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_end_of_block_or_statement (parser);
      ଫେରନ୍ତୁ result;
    }

  finish_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  ଯଦି (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_ଶୀର୍ଷ_anonymous_type (specs->type);

  ତାର୍କିକ gnu_auto_type_p = specs->typespec_word == cts_auto_type;
  ତାର୍କିକ std_auto_type_p = specs->c23_auto_p;
  ତାର୍କିକ any_auto_type_p = gnu_auto_type_p || std_auto_type_p;
  gcc_assert (!(gnu_auto_type_p && std_auto_type_p));
  ଅଚଳ ଅକ୍ଷର *auto_type_keyword = gnu_auto_type_p ? "__auto_type" : "auto";
  ଯଦି (specs->constexpr_p)
    {
      /* An underspecified declaration may not declare tags or members
	 or structures or unions; it is undefined behavior to declare
	 the members of an enumeration.  Where the structure, union or
	 enumeration type is declared within an initializer, this is
	 diagnosed elsewhere.  Diagnose here the case of declaring
	 such a type in the type specifiers of a constexpr
	 declaration.  */
      ବାଛ (specs->typespec_kind)
	{
	ସ୍ଥିତି ctsk_tagfirstref:
	ସ୍ଥିତି ctsk_tagfirstref_attrs:
	  error_at (here, "%qT declared in underspecified object declaration",
		    specs->type);
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି ctsk_tagdef:
	  error_at (here, "%qT defined in underspecified object declaration",
		    specs->type);
	  ଭାଙ୍ଗ;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଭାଙ୍ଗ;
	}
    }

  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      ତାର୍କିକ handled_assume = ମିଥ୍ୟା;
      ଯଦି (specs->attrs
	  && !nested
	  && specs->typespec_kind == ctsk_none
	  && c_parser_handle_statement_omp_attributes (parser, specs->attrs,
						       ଖାଲି))
	{
	  ଯଦି (specs->attrs)
	    c_warn_unused_attributes (specs->attrs);
	  ଯେତେବେଳେ (parser->in_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_next_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, ଖାଲି, NULL_ବୃକ୍ଷ);
	    }
	  c_parser_consume_token (parser);
	  ଫେରନ୍ତୁ result;
	}
      ଯଦି (specs->typespec_kind == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = ସତ୍ୟ;
	  specs->attrs
	    = handle_assume_attribute (here, specs->attrs, nested);
	}
      ଯଦି (any_auto_type_p)
	error_at (here, "%qs in empty declaration", auto_type_keyword);
      ଅନ୍ୟଥା ଯଦି (specs->typespec_kind == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  ଯଦି (fallthru_attr_p != ଖାଲି)
	    *fallthru_attr_p = ସତ୍ୟ;
	  ଯଦି (nested)
	    {
	      ବୃକ୍ଷ fn = build_call_ପଦସମଷ୍ଟି_internal_loc (here, IFN_FALLTHROUGH,
						      void_type_ଗଣ୍ଠି, 0);
	      add_stmt (fn);
	    }
	  ଅନ୍ୟଥା
	    pedwarn (here, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      ଅନ୍ୟଥା ଯଦି (empty_ok
	       && !(have_attrs && specs->non_std_attrs_seen_p)
	       && !handled_assume)
	shadow_tag (specs);
      ଅନ୍ୟଥା
	{
	  shadow_tag_warned (specs, 1);
	  ଯଦି (!handled_assume)
	    pedwarn (here, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      ଯଦି (specs->ପଦସମଷ୍ଟି)
	add_stmt (fold_convert (void_type_ଗଣ୍ଠି, specs->ପଦସମଷ୍ଟି));
      c_parser_consume_token (parser);
      ଯଦି (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, NULL_ବୃକ୍ଷ, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ result;
    }
  ଅନ୍ୟଥା ଯଦି (specs->typespec_kind == ctsk_none
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
      ଯଦି (astate.musttail_p)
	{
	  ଯଦି (specs->attrs)
	    {
	      auto_urlify_attributes sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, ଖାଲି, NULL_ବୃକ୍ଷ, ଖାଲି,
					   astate);
	  ଫେରନ୍ତୁ result;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  ଯଦି (empty_ok
      && specs->typespec_kind == ctsk_tagdef
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = ମିଥ୍ୟା;
      shadow_tag_warned (specs, 1);
      ଫେରନ୍ତୁ result;
    }
  ଅନ୍ୟଥା ଯଦି (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      ବାଛ (c_parser_peek_token (parser)->type)
	{
	  ସ୍ଥିତି CPP_PLUS:
	  ସ୍ଥିତି CPP_MINUS:
	    ଯଦି (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      ଫେରନ୍ତୁ result;
	    ଯଦି (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_ବୃକ୍ଷ;
	      }
	    ଯଦି (fndef_ok)
	      c_parser_objc_method_definition (parser);
	    ଅନ୍ୟଥା
	      c_parser_objc_methodproto (parser);
	    ଫେରନ୍ତୁ result;
	    ଭାଙ୍ଗ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    ଭାଙ୍ଗ;
	}
      /* This is where we parse 'attributes @interface ...',
	 'attributes @implementation ...', 'attributes @protocol ...'
	 (where attributes could be, for example, __attribute__
	 ((deprecated)).
      */
      ବାଛ (c_parser_peek_token (parser)->keyword)
	{
	ସ୍ଥିତି RID_AT_INTERFACE:
	  {
	    ଯଦି (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      ଫେରନ୍ତୁ result;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    ଫେରନ୍ତୁ result;
	  }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_IMPLEMENTATION:
	  {
	    ଯଦି (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      ଫେରନ୍ତୁ result;
	    ଯଦି (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_ବୃକ୍ଷ;
	      }
	    c_parser_objc_class_definition (parser, NULL_ବୃକ୍ଷ);
	    ଫେରନ୍ତୁ result;
	  }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_PROTOCOL:
	  {
	    ଯଦି (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      ଫେରନ୍ତୁ result;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    ଫେରନ୍ତୁ result;
	  }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_ALIAS:
	ସ୍ଥିତି RID_AT_CLASS:
	ସ୍ଥିତି RID_AT_END:
	ସ୍ଥିତି RID_AT_PROPERTY:
	  ଯଦି (specs->attrs)
	    {
	      c_parser_error (parser, "unexpected attribute");
	      specs->attrs = ଖାଲି;
	    }
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଭାଙ୍ଗ;
	}
    }
  ଅନ୍ୟଥା ଯଦି (attribute_fallthrough_p (specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  ଅନ୍ୟଥା ଯଦି (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_attributes (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ more_than_one_decl = ମିଥ୍ୟା;
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      ସଂରଚନା c_declarator *declarator;
      ତାର୍କିକ dummy = ମିଥ୍ୟା;
      timevar_id_t tv;
      ବୃକ୍ଷ fnbody = NULL_ବୃକ୍ଷ;
      ବୃକ୍ଷ underspec_name = NULL_ବୃକ୍ଷ;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_kind != ctsk_none,
					C_DTR_NORMAL, &dummy);
      ଯଦି (declarator == ଖାଲି)
	{
	  ଯଦି (omp_declare_simd_clauses)
	    c_finish_omp_declare_simd (parser, NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ,
				       omp_declare_simd_clauses);
	  ଯଦି (oacc_routine_data)
	    c_finish_oacc_routine (oacc_routine_data, NULL_ବୃକ୍ଷ, ମିଥ୍ୟା);
	  /* This check is here purely to improve the diagnostic.  */
	  ଯଦି (!simple_ok)
	    c_parser_skip_to_end_of_block_or_statement (parser);
	  ଫେରନ୍ତୁ result;
	}
      ଯଦି (flag_openmp || flag_openmp_simd)
	{
	  ସଂରଚନା c_declarator *d = declarator;
	  ଯେତେବେଳେ (d->kind != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = ଖାଲି;
	  c_parser_handle_directive_omp_attributes (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      ଯଦି (gnu_auto_type_p && declarator->kind != cdk_id)
	{
	  error_at (here,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  ଫେରନ୍ତୁ result;
	}
      ଯଦି (std_auto_type_p)
	{
	  ସଂରଚନା c_declarator *d = declarator;
	  ଯେତେବେଳେ (d->kind == cdk_attrs)
	    d = d->declarator;
	  ଯଦି (d->kind != cdk_id)
	    {
	      error_at (here,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      ଫେରନ୍ତୁ result;
	    }
	  underspec_name = d->u.id.id;
	}
      ଅନ୍ୟଥା ଯଦି (specs->constexpr_p)
	{
	  ସଂରଚନା c_declarator *d = declarator;
	  ଯେତେବେଳେ (d->kind != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      ଯଦି (c_parser_next_token_is (parser, CPP_EQ)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is_keyword (parser, RID_ASM)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_next_token_is_keyword (parser, RID_IN))
	{
	  ବୃକ୍ଷ asm_name = NULL_ବୃକ୍ଷ;
	  ବୃକ୍ଷ postfix_attrs = NULL_ବୃକ୍ଷ;
	  ଯଦି (!diagnosed_no_specs && !specs->declspecs_seen_p)
	    {
	      diagnosed_no_specs = ସତ୍ୟ;
	      pedwarn (here, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = ମିଥ୍ୟା;
	  ଯଦି (c_parser_next_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_ପଦସମଷ୍ଟି (parser);
	  ଯଦି (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_attributes (parser);
	      ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (here, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  ଫେରନ୍ତୁ result;
		}
	    }
	  ଯଦି (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      ବୃକ୍ଷ d;
	      ସଂରଚନା c_ପଦସମଷ୍ଟି init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      ଯଦି (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (ଧାଡ଼ି_table, init_loc);
		  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା underspec_state = 0;
		  ଯଦି (std_auto_type_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  start_init (NULL_ବୃକ୍ଷ, asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  ଯଦି (nested && !empty_ok)
		    flag_sanitize = 0;
		  init = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
		  ଯଦି (std_auto_type_p)
		    finish_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  ଯଦି (gnu_auto_type_p
		      && ବୃକ୍ଷ_CODE (init.ମୂଲ୍ୟ) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (ବୃକ୍ଷ_OPERAND (init.ମୂଲ୍ୟ, 1)))
		    error_at (here,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_to_rvalue (init_loc, init, ସତ୍ୟ, ସତ୍ୟ,
						   ସତ୍ୟ);
		  ବୃକ୍ଷ init_type = ବୃକ୍ଷ_TYPE (init.ମୂଲ୍ୟ);
		  ତାର୍କିକ vm_type = c_type_variably_modified_p (init_type);
		  ଯଦି (vm_type)
		    init.ମୂଲ୍ୟ = save_ପଦସମଷ୍ଟି (init.ମୂଲ୍ୟ);
		  finish_init ();
		  specs->typespec_kind = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = ସତ୍ୟ;
		  specs->type = init_type;
		  ଯଦି (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_attributes (specs->type,
						  specs->postfix_attrs);
		      decl_attributes (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_ବୃକ୍ଷ;
		    }
		  ଯଦି (vm_type)
		    {
		      ତାର୍କିକ maybe_const = ସତ୍ୟ;
		      ବୃକ୍ଷ type_ପଦସମଷ୍ଟି = c_fully_fold (init.ମୂଲ୍ୟ, ମିଥ୍ୟା,
						     &maybe_const);
		      specs->ପଦସମଷ୍ଟି_const_operands &= maybe_const;
		      ଯଦି (specs->ପଦସମଷ୍ଟି)
			specs->ପଦସମଷ୍ଟି = build2 (COMPOUND_ପଦସମଷ୍ଟି,
					      ବୃକ୍ଷ_TYPE (type_ପଦସମଷ୍ଟି),
					      specs->ପଦସମଷ୍ଟି, type_ପଦସମଷ୍ଟି);
		      ଅନ୍ୟଥା
			specs->ପଦସମଷ୍ଟି = type_ପଦସମଷ୍ଟି;
		    }
		  d = start_decl (declarator, specs, ସତ୍ୟ,
				  chainon (postfix_attrs, all_prefix_attrs));
		  ଯଦି (!d)
		    d = error_mark_ଗଣ୍ଠି;
		  ଯଦି (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_ବୃକ୍ଷ,
					       omp_declare_simd_clauses);
		  ଯଦି (!omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_ବୃକ୍ଷ,
					       &omp_dsimd_idattr_clauses);
		}
	      ଅନ୍ୟଥା
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (ଧାଡ଼ି_table, init_loc);
		  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା underspec_state = 0;
		  ଯଦି (specs->constexpr_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  d = start_decl (declarator, specs, ସତ୍ୟ,
				  chainon (postfix_attrs,
					   all_prefix_attrs),
				  !specs->constexpr_p);
		  ଯଦି (!d)
		    d = error_mark_ଗଣ୍ଠି;
		  ଯଦି (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_ବୃକ୍ଷ,
					       omp_declare_simd_clauses);
		  ଯଦି (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_ବୃକ୍ଷ,
					       &omp_dsimd_idattr_clauses);
		  start_init (d, asm_name,
			      ବୃକ୍ଷ_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  ଯଦି (ବୃକ୍ଷ_CODE (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  ଯଦି (specs->constexpr_p)
		    {
		      finish_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      ଯଦି (omp_declare_simd_clauses)
			c_finish_omp_declare_simd (parser, d, NULL_ବୃକ୍ଷ,
						   omp_declare_simd_clauses);
		  ଯଦି (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_ବୃକ୍ଷ,
					       &omp_dsimd_idattr_clauses);
		    }
		  finish_init ();
		}
	      ଯଦି (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, ମିଥ୍ୟା);
	      ଯଦି (d != error_mark_ଗଣ୍ଠି)
		{
		  maybe_warn_string_init (init_loc, ବୃକ୍ଷ_TYPE (d), init);
		  finish_decl (d, init_loc, init.ମୂଲ୍ୟ,
			       init.original_type, asm_name);
		  result = d;
		}
	    }
	  ଅନ୍ୟଥା
	    {
	      ଯଦି (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  ଫେରନ୍ତୁ result;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      ବୃକ୍ଷ attrs = chainon (postfix_attrs, all_prefix_attrs);
	      ବୃକ୍ଷ d = start_decl (declarator, specs, ମିଥ୍ୟା, attrs, ସତ୍ୟ,
				   &lastloc);
	      ଯଦି (d && ବୃକ୍ଷ_CODE (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  ଅଚଳ ସଂରଚନା c_declarator *decl = declarator;
		  ଅଚଳ ସଂରଚନା c_declarator *last_non_id_attrs = ଖାଲି;

		  ଯେତେବେଳେ (decl)
		    ବାଛ (decl->kind)
		      {
		      ସ୍ଥିତି cdk_array:
		      ସ୍ଥିତି cdk_function:
		      ସ୍ଥିତି cdk_pointer:
			last_non_id_attrs = decl;
			decl = decl->declarator;
			ଭାଙ୍ଗ;

		      ସ୍ଥିତି cdk_attrs:
			decl = decl->declarator;
			ଭାଙ୍ଗ;

		      ସ୍ଥିତି cdk_id:
			decl = 0;
			ଭାଙ୍ଗ;

		      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
			gcc_unreachable ();
		      }

		  /* If it exists and is cdk_function declaration whose
		     arguments have not been set yet, use its arguments.  */
		  ଯଦି (last_non_id_attrs
		      && last_non_id_attrs->kind == cdk_function)
		    {
		      ବୃକ୍ଷ parms = last_non_id_attrs->u.arg_info->parms;
		      ଯଦି (DECL_ARGUMENTS (d) == NULL_ବୃକ୍ଷ
			  && DECL_INITIAL (d) == NULL_ବୃକ୍ଷ)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      ଯଦି (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_empty ())
		{
		  ବୃକ୍ଷ parms = NULL_ବୃକ୍ଷ;
		  ଯଦି (d && ବୃକ୍ଷ_CODE (d) == FUNCTION_DECL)
		    {
		      ସଂରଚନା c_declarator *ce = declarator;
		      ଯେତେବେଳେ (ce != ଖାଲି)
			ଯଦି (ce->kind == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    ଭାଙ୍ଗ;
			  }
			ଅନ୍ୟଥା
			  ce = ce->declarator;
		    }
		  ଯଦି (parms)
		    temp_store_parm_decls (d, parms);
		  ଯଦି (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  ଯଦି (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  ଯଦି (parms)
		    temp_କାଢ଼_parm_decls ();
		}
	      ଯଦି (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, ମିଥ୍ୟା);
	      ଯଦି (d)
		finish_decl (d, UNKNOWN_LOCATION, NULL_ବୃକ୍ଷ,
			     NULL_ବୃକ୍ଷ, asm_name);

	      ଯଦି (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  ଯଦି (d)
		    *objc_foreach_object_declaration = d;
		  ଅନ୍ୟଥା
		    *objc_foreach_object_declaration = error_mark_ଗଣ୍ଠି;
		}
	    }
	  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      more_than_one_decl = ସତ୍ୟ;
	      ଯଦି (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  ଫେରନ୍ତୁ result;
		}
	      c_parser_consume_token (parser);
	      ଯଦି (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
		all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					    prefix_attrs);
	      ଅନ୍ୟଥା
		all_prefix_attrs = prefix_attrs;
	      ଜାରି;
	    }
	  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      ଯଦି (!simple_ok)
		c_parser_consume_token (parser);
	      ଫେରନ୍ତୁ result;
	    }
	  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      ଫେରନ୍ତୁ result;
	    }
	  ଅନ୍ୟଥା
	    {
	      ଯଦି (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      ଅନ୍ୟଥା ଯଦି (more_than_one_decl)
		error_at (here, "declaration in condition can only declare "
			  "a single object");
	      ଫେରନ୍ତୁ result;
	    }
	}
      ଅନ୍ୟଥା ଯଦି (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (here,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  ଫେରନ୍ତୁ result;
	}
      ଅନ୍ୟଥା ଯଦି (!fndef_ok)
	{
	  ଯଦି (simple_ok && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  ଅନ୍ୟଥା
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	    }
	  ଫେରନ୍ତୁ result;
	}
      /* Function definition (nested or otherwise).  */
      ଯଦି (nested)
	{
	  pedwarn (here, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_ଠେଲ_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      ବୃକ୍ଷ dv_base = NULL_ବୃକ୍ଷ;
      ବୃକ୍ଷ dv_ctx = NULL_ବୃକ୍ଷ;
      ଯଦି (!vec_safe_is_empty (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->last ();
	  dv_ctx = copy_list (a.selector);
	  dv_base = omp_start_variant_function (declarator, dv_ctx);
	}

      ଯଦି (!start_function (specs, declarator, all_prefix_attrs))
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
	  ଯଦି (c_parser_next_token_starts_declspecs (parser))
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
	      parser->error = ମିଥ୍ୟା;
	    }
	  ଅନ୍ୟଥା
	    {
	      /* This can appear in many cases looking nothing like a
		 function definition, so we don't give a more specific
		 error suggesting there was one.  */
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			      "or %<__attribute__%>");
	    }
	  ଯଦି (nested)
	    c_କାଢ଼_function_context ();
	  ଭାଙ୍ଗ;
	}

      ଯଦି (DECL_DECLARED_INLINE_P (current_function_decl))
        tv = TV_PARSE_INLINE;
      ଅନ୍ୟଥା
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
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା save_debug_nonbind_markers_p = debug_nonbind_markers_p;
      debug_nonbind_markers_p = 0;
      c_parser_maybe_reclassify_token (parser);
      ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_EOF)
	     && c_parser_next_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, ମିଥ୍ୟା, ମିଥ୍ୟା, ମିଥ୍ୟା,
				       ସତ୍ୟ, ମିଥ୍ୟା, ମିଥ୍ୟା);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      ଯଦି (omp_declare_simd_clauses)
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_ବୃକ୍ଷ,
				   omp_declare_simd_clauses);
      ଯଦି (!omp_dsimd_idattr_clauses.is_empty ())
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_ବୃକ୍ଷ,
				   &omp_dsimd_idattr_clauses);
      ଯଦି (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, current_function_decl, ସତ୍ୟ);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_start_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      ଯଦି (dv_base && current_function_decl != error_mark_ଗଣ୍ଠି)
	{
	  omp_begin_declare_variant_map_entry e
	    = { current_function_decl, dv_base, dv_ctx };
	  vec_safe_ଠେଲ (omp_begin_declare_variant_map, e);
	}

      /* If the definition was marked with __RTL, use the RTL parser now,
	 consuming the function body.  */
      ଯଦି (specs->declspec_il == cdil_rtl)
	{
	  endloc = c_parser_parse_rtl_body (parser, specs->gimple_or_rtl_pass);

	  /* Normally, store_parm_decls sets next_is_function_body,
	     anticipating a function body.  We need a push_scope/pop_scope
	     pair to flush out this state, or subsequent function parsing
	     will go wrong.  */
	  ଠେଲ_scope ();
	  କାଢ଼_scope ();

	  finish_function (endloc);
	  ଫେରନ୍ତୁ result;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      ଅନ୍ୟଥା ଯଦି (specs->declspec_il != cdil_none)
	{
	  ତାର୍କିକ saved = in_late_ଦ୍ୱିମିକ_op;
	  in_late_ଦ୍ୱିମିକ_op = ସତ୍ୟ;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->entry_bb_ଗଣନା);
	  in_late_ଦ୍ୱିମିକ_op = saved;
	}
      ଅନ୍ୟଥା
	fnbody = c_parser_compound_statement (parser, &endloc);
      ବୃକ୍ଷ fndecl = current_function_decl;
      ଯଦି (nested && specs->declspec_il == cdil_none)
	{
	  ବୃକ୍ଷ decl = current_function_decl;
	  /* Mark nested functions as needing static-chain initially.
	     lower_nested_functions will recompute it but the
	     DECL_STATIC_CHAIN flag is also used before that happens,
	     by initializer_constant_valid_p.  See gcc.dg/nested-fn-2.c.  */
	  DECL_STATIC_CHAIN (decl) = 1;
	  add_stmt (fnbody);
	  finish_function (endloc);
	  c_କାଢ଼_function_context ();
	  add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_ପଦସମଷ୍ଟି, decl));
	}
      ଅନ୍ୟଥା ଯଦି (nested)
	{
	  ଯଦି (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  ଅନ୍ୟଥା
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  finish_function (endloc);
	  c_କାଢ଼_function_context ();
	}
      ଅନ୍ୟଥା
	{
	  ଯଦି (fnbody)
	    add_stmt (fnbody);
	  finish_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      ଯଦି (specs->declspec_il != cdil_none)
	DECL_SAVED_ବୃକ୍ଷ (fndecl) = NULL_ବୃକ୍ଷ;

      ଭାଙ୍ଗ;
    }

  ଫେରନ୍ତୁ result;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_asm_definition (c_parser *parser)
{
  location_t asm_loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  ବୃକ୍ଷ asm_str = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ outputs = NULL_ବୃକ୍ଷ, inputs = NULL_ବୃକ୍ଷ;
  ଯଦି (!parens.require_open (parser))
    ଯାଅ done;
  asm_str = c_parser_asm_string_literal (parser);
  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      ଯାଅ done;
    }
  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା section = 0; section < 2; ++section)
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  ଯଦି (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
	      asm_str = NULL_ବୃକ୍ଷ;
	      ଯାଅ done;
	    }
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା ଯଦି (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, ମିଥ୍ୟା))
	ଯାଅ error_close_paren;
      ଯଦି (!c_parser_next_token_is (parser, CPP_COLON)
	  && !c_parser_next_token_is (parser, CPP_SCOPE)
	  && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ଯଦି (section)
	    inputs = c_parser_asm_operands (parser);
	  ଅନ୍ୟଥା
	    outputs = c_parser_asm_operands (parser);
	}
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	ଭାଙ୍ଗ;
    }

  ଯଦି (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
      asm_str = NULL_ବୃକ୍ଷ;
    }

  ଯଦି (asm_str)
    asm_str = build_asm_ପଦସମଷ୍ଟି (asm_loc, asm_str, outputs, inputs,
			      NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ, ମିଥ୍ୟା, ମିଥ୍ୟା);
done:
  ଯଦି (asm_str)
    symtab->finalize_toplevel_asm (asm_str);
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse a static assertion (C11 6.7.10).

   static_assert-declaration:
     static_assert-declaration-no-semi ;
*/

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_static_assert_declaration (c_parser *parser)
{
  c_parser_static_assert_declaration_no_semi (parser);
  ଯଦି (parser->error
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_static_assert_declaration_no_semi (c_parser *parser)
{
  location_t assert_loc, ମୂଲ୍ୟ_loc;
  ବୃକ୍ଷ ମୂଲ୍ୟ;
  ବୃକ୍ଷ string = NULL_ବୃକ୍ଷ;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT));
  ବୃକ୍ଷ spelling = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
  assert_loc = c_parser_peek_token (parser)->location;
  ଯଦି (flag_isoc99)
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  ଅନ୍ୟଥା
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  c_parser_consume_token (parser);
  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ;
  location_t ମୂଲ୍ୟ_tok_loc = c_parser_peek_token (parser)->location;
  ମୂଲ୍ୟ = convert_lvalue_to_rvalue (ମୂଲ୍ୟ_tok_loc,
				    c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି),
				    ସତ୍ୟ, ସତ୍ୟ).ମୂଲ୍ୟ;
  ମୂଲ୍ୟ_loc = ପଦସମଷ୍ଟି_LOC_OR_LOC (ମୂଲ୍ୟ, ମୂଲ୍ୟ_tok_loc);
  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ବାଛ (c_parser_peek_token (parser)->type)
	{
	ସ୍ଥିତି CPP_STRING:
	ସ୍ଥିତି CPP_STRING16:
	ସ୍ଥିତି CPP_STRING32:
	ସ୍ଥିତି CPP_WSTRING:
	ସ୍ଥିତି CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, ମିଥ୍ୟା, ସତ୍ୟ).ମୂଲ୍ୟ;
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  c_parser_error (parser, "expected string literal");
	  ଫେରନ୍ତୁ;
	}
    }
  ଅନ୍ୟଥା ଯଦି (flag_isoc11)
    /* If pedantic for pre-C11, the use of _Static_assert itself will
       have been diagnosed, so do not also diagnose the use of this
       new C23 feature of _Static_assert.  */
    pedwarn_c11 (assert_loc, OPT_Wpedantic,
		 "ISO C11 does not support omitting the string in "
		 "%qE", spelling);
  parens.require_close (parser);

  ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ)))
    {
      error_at (ମୂଲ୍ୟ_loc, "expression in static assertion is not an integer");
      ଫେରନ୍ତୁ;
    }
  ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) != INTEGER_CST)
    {
      ମୂଲ୍ୟ = c_fully_fold (ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (ମୂଲ୍ୟ);
      ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) == INTEGER_CST)
	pedwarn (ମୂଲ୍ୟ_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) != INTEGER_CST)
    {
      error_at (ମୂଲ୍ୟ_loc, "expression in static assertion is not constant");
      ଫେରନ୍ତୁ;
    }
  constant_expression_warning (ମୂଲ୍ୟ);
  ଯଦି (integer_zerop (ମୂଲ୍ୟ))
    {
      ଯଦି (string)
	error_at (assert_loc, "static assertion failed: %E", string);
      ଅନ୍ୟଥା
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

ଶୂନ୍ୟ
c_parser_declspecs (c_parser *parser, ସଂରଚନା c_declspecs *specs,
		    ତାର୍କିକ scspec_ok, ତାର୍କିକ typespec_ok, ତାର୍କିକ start_attr_ok,
		    ତାର୍କିକ alignspec_ok, ତାର୍କିକ auto_type_ok,
		    ତାର୍କିକ start_std_attr_ok, ତାର୍କିକ end_std_attr_ok,
		    ଗଣନା c_lookahead_kind la)
{
  ତାର୍କିକ attrs_ok = start_attr_ok;
  ତାର୍କିକ seen_type = specs->typespec_kind != ctsk_none;

  ଯଦି (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  ଯଦି (start_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_seen_p);
      location_t loc = c_parser_peek_token (parser)->location;
      ବୃକ୍ଷ attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_add_attrs (loc, specs, attrs);
      specs->non_std_attrs_seen_p = ମିଥ୍ୟା;
    }

  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_NAME)
	 || c_parser_next_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_next_token_is (parser, CPP_LESS)))
    {
      ସଂରଚନା c_typespec t;
      ବୃକ୍ଷ attrs;
      ବୃକ୍ଷ align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      ଯଦି ((!typespec_ok || specs->typespec_kind == ctsk_tagdef)
	  && c_parser_next_tokens_start_typename (parser, la)
	  && !c_parser_next_token_is_qualifier (parser)
	  && !c_parser_next_token_is_keyword (parser, RID_ALIGNAS))
	ଭାଙ୍ଗ;

      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  ବୃକ୍ଷ ମୂଲ୍ୟ = name_token->ମୂଲ୍ୟ;
	  c_id_kind kind = name_token->id_kind;

	  ଯଦି (kind == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_FIRST_ADDR_SPACE;
	      declspecs_add_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = ସତ୍ୟ;
	      ଜାରି;
	    }

	  gcc_assert (!c_parser_next_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  ଯଦି (seen_type || !c_parser_next_tokens_start_typename (parser, la))
	    ଭାଙ୍ଗ;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  seen_type = ସତ୍ୟ;
	  attrs_ok = ସତ୍ୟ;
	  ଯଦି (kind == C_ID_ID)
	    {
	      auto_diagnostic_group d;
	      name_hint hint = lookup_name_fuzzy (ମୂଲ୍ୟ, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      ଯଦି (ଅଚଳ ଅକ୍ଷର *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.add_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    ମୂଲ୍ୟ, suggestion);
		}
	      ଅନ୍ୟଥା
		error_at (loc, "unknown type name %qE", ମୂଲ୍ୟ);
	      t.kind = ctsk_typedef;
	      t.spec = error_mark_ଗଣ୍ଠି;
	    }
	  ଅନ୍ୟଥା ଯଦି (kind == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_next_token_is_not (parser, CPP_LESS)))
	    {
	      t.kind = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (ମୂଲ୍ୟ);
	    }
	  ଅନ୍ୟଥା
	    {
	      ବୃକ୍ଷ proto = NULL_ବୃକ୍ଷ;
	      gcc_assert (c_dialect_objc ());
	      t.kind = ctsk_objc;
	      ଯଦି (c_parser_next_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (ମୂଲ୍ୟ, proto);
	    }
	  t.ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
	  t.ପଦସମଷ୍ଟି_const_operands = ସତ୍ୟ;
	  t.has_enum_type_specifier = ମିଥ୍ୟା;
	  declspecs_add_type (name_token->location, specs, t);
	  ଜାରି;
	}
      ଯଦି (c_parser_next_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  ବୃକ୍ଷ proto;
	  gcc_assert (c_dialect_objc ());
	  ଯଦି (!typespec_ok || seen_type)
	    ଭାଙ୍ଗ;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.kind = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_ବୃକ୍ଷ, proto);
	  t.ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
	  t.ପଦସମଷ୍ଟି_const_operands = ସତ୍ୟ;
	  t.has_enum_type_specifier = ମିଥ୍ୟା;
	  declspecs_add_type (loc, specs, t);
	  ଜାରି;
	}
      gcc_assert (c_parser_next_token_is (parser, CPP_KEYWORD));
      ବାଛ (c_parser_peek_token (parser)->keyword)
	{
	ସ୍ଥିତି RID_STATIC:
	ସ୍ଥିତି RID_EXTERN:
	ସ୍ଥିତି RID_REGISTER:
	ସ୍ଥିତି RID_TYPEDEF:
	ସ୍ଥିତି RID_INLINE:
	ସ୍ଥିତି RID_NORETURN:
	ସ୍ଥିତି RID_AUTO:
	ସ୍ଥିତି RID_THREAD:
	ସ୍ଥିତି RID_CONSTEXPR:
	  ଯଦି (!scspec_ok)
	    ଯାଅ out;
	  attrs_ok = ସତ୍ୟ;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_add_scspec (loc, specs,
				c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	  c_parser_consume_token (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AUTO_TYPE:
	  ଯଦି (!auto_type_ok)
	    ଯାଅ out;
	  /* Fall through.  */
	ସ୍ଥିତି RID_UNSIGNED:
	ସ୍ଥିତି RID_LONG:
	ସ୍ଥିତି RID_SHORT:
	ସ୍ଥିତି RID_SIGNED:
	ସ୍ଥିତି RID_COMPLEX:
	ସ୍ଥିତି RID_INT:
	ସ୍ଥିତି RID_CHAR:
	ସ୍ଥିତି RID_FLOAT:
	ସ୍ଥିତି RID_DOUBLE:
	ସ୍ଥିତି RID_VOID:
	ସ୍ଥିତି RID_DFLOAT32:
	ସ୍ଥିତି RID_DFLOAT64:
	ସ୍ଥିତି RID_DFLOAT128:
	ସ୍ଥିତି RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	ସ୍ଥିତି RID_BOOL:
	ସ୍ଥିତି RID_FRACT:
	ସ୍ଥିତି RID_ACCUM:
	ସ୍ଥିତି RID_SAT:
	ସ୍ଥିତି RID_INT_N_0:
	ସ୍ଥିତି RID_INT_N_1:
	ସ୍ଥିତି RID_INT_N_2:
	ସ୍ଥିତି RID_INT_N_3:
	  ଯଦି (!typespec_ok)
	    ଯାଅ out;
	  attrs_ok = ସତ୍ୟ;
	  seen_type = ସତ୍ୟ;
	  ଯଦି (c_dialect_objc ())
	    parser->objc_need_raw_identifier = ସତ୍ୟ;
	  t.kind = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	  t.ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
	  t.ପଦସମଷ୍ଟି_const_operands = ସତ୍ୟ;
	  t.has_enum_type_specifier = ମିଥ୍ୟା;
	  declspecs_add_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_ENUM:
	  ଯଦି (!typespec_ok)
	    ଯାଅ out;
	  attrs_ok = ସତ୍ୟ;
	  seen_type = ସତ୍ୟ;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_STRUCT:
	ସ୍ଥିତି RID_UNION:
	  ଯଦି (!typespec_ok)
	    ଯାଅ out;
	  attrs_ok = ସତ୍ୟ;
	  seen_type = ସତ୍ୟ;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_TYPEOF:
	ସ୍ଥିତି RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  ଯଦି (!typespec_ok || seen_type)
	    ଯାଅ out;
	  attrs_ok = ସତ୍ୟ;
	  seen_type = ସତ୍ୟ;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_add_type (loc, specs, t);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_BITINT:
	  ଯଦି (!typespec_ok)
	    ଯାଅ out;
	  ଅନ୍ୟଥା
	    {
	      attrs_ok = ସତ୍ୟ;
	      seen_type = ସତ୍ୟ;
	      t.kind = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	      t.ପଦସମଷ୍ଟି = error_mark_ଗଣ୍ଠି;
	      t.ପଦସମଷ୍ଟି_const_operands = ସତ୍ୟ;
	      t.has_enum_type_specifier = ମିଥ୍ୟା;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      ଯଦି (parens.require_open (parser))
		{
		  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
		  t.ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (loc, ପଦସମଷ୍ଟି, ସତ୍ୟ,
						     ସତ୍ୟ).ମୂଲ୍ୟ;
		  parens.skip_until_found_close (parser);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_ATOMIC:
	  /* C parser handling of Objective-C constructs needs
	     checking for correct lvalue-to-rvalue conversions, and
	     the code in build_modify_expr handling various
	     Objective-C cases, and that in build_unary_op handling
	     Objective-C cases for increment / decrement, also needs
	     updating; uses of TYPE_MAIN_VARIANT in objc_compare_types
	     and objc_types_are_equivalent may also need updates.  */
	  ଯଦି (c_dialect_objc ())
	    sorry ("%<_Atomic%> in Objective-C");
	  ଯଦି (flag_isoc99)
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C99 does not support the %<_Atomic%> qualifier");
	  ଅନ୍ୟଥା
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C90 does not support the %<_Atomic%> qualifier");
	  attrs_ok = ସତ୍ୟ;
	  ବୃକ୍ଷ ମୂଲ୍ୟ;
	  ମୂଲ୍ୟ = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	  c_parser_consume_token (parser);
	  ଯଦି (typespec_ok && c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      seen_type = ସତ୍ୟ;
	      c_parser_consume_token (parser);
	      ସଂରଚନା c_type_name *type = c_parser_type_name (parser);
	      t.kind = ctsk_typeof;
	      t.spec = error_mark_ଗଣ୍ଠି;
	      t.ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
	      t.ପଦସମଷ୍ଟି_const_operands = ସତ୍ୟ;
	      t.has_enum_type_specifier = ମିଥ୍ୟା;
	      ଯଦି (type != ଖାଲି)
		t.spec = groktypename (type, &t.ପଦସମଷ୍ଟି,
				       &t.ପଦସମଷ୍ଟି_const_operands);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      ଯଦି (t.spec != error_mark_ଗଣ୍ଠି)
		{
		  ଯଦି (ବୃକ୍ଷ_CODE (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  ଅନ୍ୟଥା ଯଦି (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  ଅନ୍ୟଥା
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  ଅନ୍ୟଥା
	    declspecs_add_qual (loc, specs, ମୂଲ୍ୟ);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_CONST:
	ସ୍ଥିତି RID_VOLATILE:
	ସ୍ଥିତି RID_RESTRICT:
	  attrs_ok = ସତ୍ୟ;
	  declspecs_add_qual (loc, specs, c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	  c_parser_consume_token (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_ATTRIBUTE:
	  ଯଦି (!attrs_ok)
	    ଯାଅ out;
	  attrs = c_parser_gnu_attributes (parser);
	  declspecs_add_attrs (loc, specs, attrs);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_ALIGNAS:
	  ଯଦି (!alignspec_ok)
	    ଯାଅ out;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_add_alignas (loc, specs, align);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_GIMPLE:
	  ଯଦି (! flag_gimple)
	    error_at (loc, "%<__GIMPLE%> only valid with %<-fgimple%>");
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_gimple;
	  specs->locations[cdw_gimple] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_RTL:
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_rtl;
	  specs->locations[cdw_rtl] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଯାଅ out;
	}
    }
 out:
  ଯଦି (end_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    specs->postfix_attrs = c_parser_std_attribute_specifier_sequence (parser);
}

/* Complain about a non-CPP_NAME within an enumerator list.  */

ସ୍ଥିର ଶୂନ୍ୟ
report_bad_enum_name (c_parser *parser)
{
  ଯଦି (!parser->error)
    {
      c_token *token = c_parser_peek_token (parser);
      ବାଛ (token->type)
	{
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_CLOSE_BRACE:
	  /* Give a nicer error for "enum {}".  */
	  error_at (token->location,
		    "empty enum is invalid");
	  parser->error = ସତ୍ୟ;
	  ଫେରନ୍ତୁ;
	ସ୍ଥିତି CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  ଯଦି (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_group d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_POINTER (token->ମୂଲ୍ୟ));
	      add_note_about_new_keyword (token->location,
					  token->ମୂଲ୍ୟ);
	      parser->error = ସତ୍ୟ;
	      ଫେରନ୍ତୁ;
	    }
	  ଭାଙ୍ଗ;
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

ସ୍ଥିର ସଂରଚନା c_typespec
c_parser_enum_specifier (c_parser *parser)
{
  ସଂରଚନା c_typespec ret;
  ତାର୍କିକ have_std_attrs;
  ତାର୍କିକ potential_nesting_p = ମିଥ୍ୟା;
  ବୃକ୍ଷ std_attrs = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ attrs;
  ବୃକ୍ଷ ident = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ fixed_underlying_type = NULL_ବୃକ୍ଷ;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  ଯଦି (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  ଯଦି (c_parser_next_token_is (parser, CPP_COLON)
      /* Distinguish an enum-type-specifier from a bit-field
	 declaration of the form "enum e : constant-expression;".  */
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      pedwarn_c11 (enum_loc, OPT_Wpedantic,
		   "ISO C does not support specifying %<enum%> underlying "
		   "types before C23");
      ଯଦି (ident)
	{
	  /* The tag is in scope during the enum-type-specifier (which
	     may refer to the tag inside typeof).  */
	  ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, ସତ୍ୟ);
	  ଯଦି (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_ବୃକ୍ଷ == TYPE_ମୂଲ୍ୟଗୁଡ଼ିକ (ret.spec);
	}
      ଅନ୍ୟଥା
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_ବୃକ୍ଷ;
	  ret.kind = ctsk_tagdef;
	  ret.ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
	  ret.ପଦସମଷ୍ଟି_const_operands = ସତ୍ୟ;
	  ret.has_enum_type_specifier = ସତ୍ୟ;
	}
      c_parser_consume_token (parser);
      ସଂରଚନା c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, ମିଥ୍ୟା, ସତ୍ୟ, ମିଥ୍ୟା, ମିଥ୍ୟା, ମିଥ୍ୟା,
			  ମିଥ୍ୟା, ସତ୍ୟ, cla_prefer_id);
      finish_declspecs (specs);
      ଯଦି (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (specs->type) != INTEGER_TYPE
	       && ବୃକ୍ଷ_CODE (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || ବୃକ୍ଷ_CODE (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (specs->restrict_p)
	error_at (enum_loc, "invalid use of %<restrict%>");
      fixed_underlying_type = TYPE_MAIN_VARIANT (specs->type);
      ଯଦି (ident)
	{
	  /* The type specified must be consistent with any previously
	     specified underlying type.  If this is a newly declared
	     type, it is now a complete type.  */
	  ଯଦି (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
	      && ENUM_UNDERLYING_TYPE (ret.spec) == NULL_ବୃକ୍ଷ)
	    {
	      TYPE_MIN_ମୂଲ୍ୟ (ret.spec) =
		TYPE_MIN_ମୂଲ୍ୟ (fixed_underlying_type);
	      TYPE_MAX_ମୂଲ୍ୟ (ret.spec) =
		TYPE_MAX_ମୂଲ୍ୟ (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      SET_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_SIZE (ret.spec) = NULL_ବୃକ୍ଷ;
	      TYPE_PRECISION (ret.spec) =
		TYPE_PRECISION (fixed_underlying_type);
	      ENUM_UNDERLYING_TYPE (ret.spec) = fixed_underlying_type;
	      layout_type (ret.spec);
	    }
	  ଅନ୍ୟଥା ଯଦି (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
		   && !comptypes (fixed_underlying_type,
				  ENUM_UNDERLYING_TYPE (ret.spec)))
	    {
	      error_at (enum_loc, "%<enum%> underlying type incompatible with "
			"previous declaration");
	      fixed_underlying_type = ENUM_UNDERLYING_TYPE (ret.spec);
	    }
	}
    }
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      ସଂରଚନା c_enum_contents the_enum;
      ବୃକ୍ଷ type;
      ବୃକ୍ଷ postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      ବୃକ୍ଷ ମୂଲ୍ୟଗୁଡ଼ିକ;
      timevar_ଠେଲ (TV_PARSE_ENUM);
      type = start_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      ମୂଲ୍ୟଗୁଡ଼ିକ = NULL_ବୃକ୍ଷ;
      c_parser_consume_token (parser);
      ଯେତେବେଳେ (ସତ୍ୟ)
	{
	  ବୃକ୍ଷ enum_id;
	  ବୃକ୍ଷ enum_ମୂଲ୍ୟ;
	  ବୃକ୍ଷ enum_decl;
	  ତାର୍କିକ seen_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, ମୂଲ୍ୟ_loc;
	  ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ଖାଲି);
	      ମୂଲ୍ୟଗୁଡ଼ିକ = error_mark_ଗଣ୍ଠି;
	      ଭାଙ୍ଗ;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->ମୂଲ୍ୟ;
	  /* Set the location in case we create a decl now.  */
	  c_parser_set_source_position_from_token (token);
	  decl_loc = ମୂଲ୍ୟ_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  ବୃକ୍ଷ std_attrs = NULL_ବୃକ୍ଷ;
	  ଯଦି (c_parser_nth_token_starts_std_attributes (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  ବୃକ୍ଷ enum_attrs = chainon (std_attrs,
				     c_parser_gnu_attributes (parser));
	  ଯଦି (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      ମୂଲ୍ୟ_loc = c_parser_peek_token (parser)->location;
	      enum_ମୂଲ୍ୟ = convert_lvalue_to_rvalue (ମୂଲ୍ୟ_loc,
						     (c_parser_ପଦସମଷ୍ଟି_no_commas
						      (parser, ଖାଲି)),
						     ସତ୍ୟ, ସତ୍ୟ).ମୂଲ୍ୟ;
	    }
	  ଅନ୍ୟଥା
	    enum_ମୂଲ୍ୟ = NULL_ବୃକ୍ଷ;
	  enum_decl = build_enumerator (decl_loc, ମୂଲ୍ୟ_loc,
					&the_enum, enum_id, enum_ମୂଲ୍ୟ);
	  ଯଦି (enum_attrs)
	    decl_attributes (&ବୃକ୍ଷ_PURPOSE (enum_decl), enum_attrs, 0);
	  ବୃକ୍ଷ_CHAIN (enum_decl) = ମୂଲ୍ୟଗୁଡ଼ିକ;
	  ମୂଲ୍ୟଗୁଡ଼ିକ = enum_decl;
	  seen_comma = ମିଥ୍ୟା;
	  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      seen_comma = ସତ୍ୟ;
	      c_parser_consume_token (parser);
	    }
	  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      ଯଦି (seen_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (!seen_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ଖାଲି);
	      ମୂଲ୍ୟଗୁଡ଼ିକ = error_mark_ଗଣ୍ଠି;
	      ଭାଙ୍ଗ;
	    }
	}
      postfix_attrs = c_parser_gnu_attributes (parser);
      ret.spec = finish_enum (type, nreverse (ମୂଲ୍ୟଗୁଡ଼ିକ),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.kind = ctsk_tagdef;
      ret.ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
      ret.ପଦସମଷ୍ଟି_const_operands = ସତ୍ୟ;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_ବୃକ୍ଷ;
      timevar_କାଢ଼ (TV_PARSE_ENUM);
      ଫେରନ୍ତୁ ret;
    }
  ଅନ୍ୟଥା ଯଦି (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_ଗଣ୍ଠି;
      ret.kind = ctsk_tagref;
      ret.ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
      ret.ପଦସମଷ୍ଟି_const_operands = ସତ୍ୟ;
      ret.has_enum_type_specifier = ମିଥ୍ୟା;
      ଫେରନ୍ତୁ ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  ଯଦି (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  ଯଦି (fixed_underlying_type == NULL_ବୃକ୍ଷ)
    {
      ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
			     std_attrs, ମିଥ୍ୟା);
      /* In ISO C, enumerated types without a fixed underlying type
	 can be referred to only if already defined.  */
      ଯଦି (pedantic && !COMPLETE_TYPE_P (ret.spec))
	{
	  gcc_assert (ident);
	  pedwarn (enum_loc, OPT_Wpedantic,
		   "ISO C forbids forward references to %<enum%> types");
	}
    }
  ଫେରନ୍ତୁ ret;
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

ସ୍ଥିର ସଂରଚନା c_typespec
c_parser_struct_or_union_specifier (c_parser *parser)
{
  ସଂରଚନା c_typespec ret;
  ତାର୍କିକ have_std_attrs;
  ବୃକ୍ଷ std_attrs = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ attrs;
  ବୃକ୍ଷ ident = NULL_ବୃକ୍ଷ;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  ଗଣନା ବୃକ୍ଷ_code code;
  ବାଛ (c_parser_peek_token (parser)->keyword)
    {
    ସ୍ଥିତି RID_STRUCT:
      code = RECORD_TYPE;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି RID_UNION:
      code = UNION_TYPE;
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  ଯଦି (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      ଶ୍ରେଣୀ c_struct_parse_info *struct_info;
      ବୃକ୍ଷ type = start_struct (struct_loc, code, ident, &struct_info);
      ବୃକ୍ଷ postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      ବୃକ୍ଷ contents;
      ବୃକ୍ଷ ପଦସମଷ୍ଟି = ଖାଲି;
      timevar_ଠେଲ (TV_PARSE_STRUCT);
      contents = NULL_ବୃକ୍ଷ;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      ଯଦି (c_parser_next_token_is_keyword (parser, RID_AT_DEFS))
	{
	  ବୃକ୍ଷ name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  ଯଦି (!parens.require_open (parser))
	    ଯାଅ end_at_defs;
	  ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	      c_parser_consume_token (parser);
	    }
	  ଅନ୍ୟଥା
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
	      ଯାଅ end_at_defs;
	    }
	  parens.skip_until_found_close (parser);
	  contents = nreverse (objc_get_class_ivars (name));
	}
    end_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      ଯେତେବେଳେ (ସତ୍ୟ)
	{
	  ବୃକ୍ଷ decls;
	  /* Parse any stray semicolon.  */
	  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      location_t semicolon_loc
		= c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (semicolon_loc);
	      richloc.add_fixit_remove ();
	      pedwarn (&richloc, OPT_Wpedantic,
		       "extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      ଜାରି;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      ଭାଙ୍ଗ;
	    }
	  /* Accept #pragmas at struct scope.  */
	  ଯଦି (c_parser_next_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, ଖାଲି, NULL_ବୃକ୍ଷ);
	      ଜାରି;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &ପଦସମଷ୍ଟି);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  ଅନ୍ୟଥା
	    {
	      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      ଅନ୍ୟଥା ଯଦି (parser->error
		       || !c_parser_next_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ଖାଲି);
		  ଭାଙ୍ଗ;
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
				struct_info, &ପଦସମଷ୍ଟି);
      ret.kind = ctsk_tagdef;
      ret.ପଦସମଷ୍ଟି = ପଦସମଷ୍ଟି;
      ret.ପଦସମଷ୍ଟି_const_operands = ସତ୍ୟ;
      ret.has_enum_type_specifier = ମିଥ୍ୟା;
      timevar_କାଢ଼ (TV_PARSE_STRUCT);
      ଫେରନ୍ତୁ ret;
    }
  ଅନ୍ୟଥା ଯଦି (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_ଗଣ୍ଠି;
      ret.kind = ctsk_tagref;
      ret.ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
      ret.ପଦସମଷ୍ଟି_const_operands = ସତ୍ୟ;
      ret.has_enum_type_specifier = ମିଥ୍ୟା;
      ଫେରନ୍ତୁ ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  ଯଦି (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_tag (ident_loc, code, ident, have_std_attrs, std_attrs,
			 ମିଥ୍ୟା);
  ଫେରନ୍ତୁ ret;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_struct_declaration (c_parser *parser, ବୃକ୍ଷ *ପଦସମଷ୍ଟି)
{
  ସଂରଚନା c_declspecs *specs;
  ବୃକ୍ଷ prefix_attrs;
  ବୃକ୍ଷ all_prefix_attrs;
  ବୃକ୍ଷ decls;
  location_t decl_loc;
  ଯଦି (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା ext;
      ବୃକ୍ଷ decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, ପଦସମଷ୍ଟି);
      restore_extension_diagnostics (ext);
      ଫେରନ୍ତୁ decl;
    }
  ଯଦି (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, ମିଥ୍ୟା, ସତ୍ୟ, ସତ୍ୟ,
		      ସତ୍ୟ, ମିଥ୍ୟା, ସତ୍ୟ, ସତ୍ୟ, cla_nonabstract_decl);
  ଯଦି (parser->error)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  ଯଦି (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }
  finish_declspecs (specs);
  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      ବୃକ୍ଷ ret;
      ଯଦି (specs->typespec_kind == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_tag_warned (specs, pedantic);
	  ret = NULL_ବୃକ୍ଷ;
	}
      ଅନ୍ୟଥା
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  ବୃକ୍ଷ attrs = ଖାଲି;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_ବୃକ୍ଷ), specs,
			   NULL_ବୃକ୍ଷ, &attrs, ପଦସମଷ୍ଟି);
	  ଯଦି (ret)
	    decl_attributes (&ret, attrs, 0);
	}
      ଫେରନ୍ତୁ ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  ଯଦି (specs->typespec_kind == ctsk_tagdef
      && ବୃକ୍ଷ_CODE (specs->type) != ENUMERAL_TYPE
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = ମିଥ୍ୟା;
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_ବୃକ୍ଷ;
  decls = NULL_ବୃକ୍ଷ;
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      ସଂରଚନା c_declarator *declarator;
      ତାର୍କିକ dummy = ମିଥ୍ୟା;
      ଯଦି (c_parser_next_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_ବୃକ୍ଷ);
      ଅନ୍ୟଥା
	declarator = c_parser_declarator (parser,
					  specs->typespec_kind != ctsk_none,
					  C_DTR_NORMAL, &dummy);
      ଯଦି (declarator == ଖାଲି)
	{
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  ଭାଙ୍ଗ;
	}
      ଯଦି (c_parser_next_token_is (parser, CPP_COLON)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  ବୃକ୍ଷ postfix_attrs = NULL_ବୃକ୍ଷ;
	  ବୃକ୍ଷ width = NULL_ବୃକ୍ଷ;
	  ବୃକ୍ଷ d;
	  ଯଦି (c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      width = convert_lvalue_to_rvalue (loc,
						(c_parser_ପଦସମଷ୍ଟି_no_commas
						 (parser, ଖାଲି)),
						ସତ୍ୟ, ସତ୍ୟ).ମୂଲ୍ୟ;
	    }
	  ଯଦି (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_attributes (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, width, &all_prefix_attrs, ପଦସମଷ୍ଟି);
	  decl_attributes (&d, chainon (postfix_attrs,
					all_prefix_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  ଯଦି (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					prefix_attrs);
	  ଅନ୍ୟଥା
	    all_prefix_attrs = prefix_attrs;
	  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON)
		   || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      /* Semicolon consumed in caller.  */
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା
	    {
	      c_parser_error (parser, "expected %<,%>, %<;%> or %<}%>");
	      ଭାଙ୍ଗ;
	    }
	}
      ଅନ୍ୟଥା
	{
	  c_parser_error (parser,
			  "expected %<:%>, %<,%>, %<;%>, %<}%> or "
			  "%<__attribute__%>");
	  ଭାଙ୍ଗ;
	}
    }
  ଫେରନ୍ତୁ decls;
}

/* Parse a typeof specifier (a GNU extension adopted in C23).

   typeof-specifier:
     typeof ( expression )
     typeof ( type-name )
     typeof_unqual ( expression )
     typeof_unqual ( type-name )
*/

ସ୍ଥିର ସଂରଚନା c_typespec
c_parser_typeof_specifier (c_parser *parser)
{
  ତାର୍କିକ is_unqual;
  ତାର୍କିକ is_std;
  ସଂରଚନା c_typespec ret;
  ret.kind = ctsk_typeof;
  ret.spec = error_mark_ଗଣ୍ଠି;
  ret.ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
  ret.ପଦସମଷ୍ଟି_const_operands = ସତ୍ୟ;
  ret.has_enum_type_specifier = ମିଥ୍ୟା;
  ଯଦି (c_parser_next_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = ମିଥ୍ୟା;
      ବୃକ୍ଷ spelling = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      is_std = (flag_isoc23
		&& strcmp (IDENTIFIER_POINTER (spelling), "typeof") == 0);
    }
  ଅନ୍ୟଥା
    {
      gcc_assert (c_parser_next_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = ସତ୍ୟ;
      ବୃକ୍ଷ spelling = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      is_std = strcmp (IDENTIFIER_POINTER (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_typeof++;
  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      ଫେରନ୍ତୁ ret;
    }
  ଯଦି (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      ସଂରଚନା c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      ଯଦି (type != ଖାଲି)
	{
	  ret.spec = groktypename (type, &ret.ପଦସମଷ୍ଟି, &ret.ପଦସମଷ୍ଟି_const_operands);
	  କାଢ଼_maybe_used (c_type_variably_modified_p (ret.spec));
	}
    }
  ଅନ୍ୟଥା
    {
      ତାର୍କିକ was_vm;
      location_t here = c_parser_peek_token (parser)->location;
      ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_expression (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, 1)))
	error_at (here, "%<typeof%> applied to a bit-field");
      mark_exp_read (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
      ret.spec = ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      ଯଦି (was_vm)
	ret.ପଦସମଷ୍ଟି = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା, &ret.ପଦସମଷ୍ଟି_const_operands);
      କାଢ଼_maybe_used (was_vm);
    }
  parens.skip_until_found_close (parser);
  ଯଦି (ret.spec != error_mark_ଗଣ୍ଠି)
    {
      ଯଦି (is_unqual)
	{
	  ତାର୍କିକ is_array = ବୃକ୍ଷ_CODE (ret.spec) == ARRAY_TYPE;
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା quals = TYPE_QUALS (strip_array_types (ret.spec));
	  ଯଦି ((is_array ? quals & ~TYPE_QUAL_ATOMIC : quals)
	      != TYPE_UNQUALIFIED)
	    {
	      ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	      ଯଦି (quals & TYPE_QUAL_ATOMIC && is_array)
		ret.spec = c_build_qualified_type (ret.spec,
						   TYPE_QUAL_ATOMIC);
	    }
	}
      ଯଦି (is_std)
	{
	  /* In ISO C terms, _Noreturn is not part of the type of
	     expressions such as &abort, but in GCC it is represented
	     internally as a type qualifier.  */
	  ଯଦି (ବୃକ୍ଷ_CODE (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  ଅନ୍ୟଥା ଯଦି (FUNCTION_POINTER_TYPE_P (ret.spec)
		   && TYPE_QUALS (ବୃକ୍ଷ_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_pointer_type (TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (ret.spec)));
	}
    }
  ଫେରନ୍ତୁ ret;
}

/* Parse an alignment-specifier.

   C11 6.7.5:

   alignment-specifier:
     _Alignas ( type-name )
     _Alignas ( constant-expression )
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_alignas_specifier (c_parser * parser)
{
  ବୃକ୍ଷ ret = error_mark_ଗଣ୍ଠି;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNAS));
  ବୃକ୍ଷ spelling = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
  c_parser_consume_token (parser);
  ଯଦି (flag_isoc99)
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  ଅନ୍ୟଥା
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ ret;
  ଯଦି (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      ସଂରଚନା c_type_name *type = c_parser_type_name (parser);
      ଯଦି (type != ଖାଲି)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, ଖାଲି, ଖାଲି),
					ମିଥ୍ୟା, ସତ୍ୟ, 1);
    }
  ଅନ୍ୟଥା
    ret = convert_lvalue_to_rvalue (loc,
				    c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି),
				    ସତ୍ୟ, ସତ୍ୟ).ମୂଲ୍ୟ;
  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ ret;
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

ସଂରଚନା c_declarator *
c_parser_declarator (c_parser *parser, ତାର୍କିକ type_seen_p, c_dtr_syn kind,
		     ତାର୍କିକ *seen_id)
{
  /* Parse any initial pointer part.  */
  ଯଦି (c_parser_next_token_is (parser, CPP_MULT))
    {
      ସଂରଚନା c_declspecs *quals_attrs = build_null_declspecs ();
      ସଂରଚନା c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, ମିଥ୍ୟା, ମିଥ୍ୟା, ସତ୍ୟ,
			  ମିଥ୍ୟା, ମିଥ୍ୟା, ସତ୍ୟ, ମିଥ୍ୟା, cla_prefer_id);
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      ଯଦି (inner == ଖାଲି)
	ଫେରନ୍ତୁ ଖାଲି;
      ଅନ୍ୟଥା
	ଫେରନ୍ତୁ make_pointer_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  ଫେରନ୍ତୁ c_parser_direct_declarator (parser, type_seen_p, kind, seen_id);
}

/* Parse a direct declarator or direct abstract declarator; arguments
   as c_parser_declarator.  */

ସ୍ଥିର ସଂରଚନା c_declarator *
c_parser_direct_declarator (c_parser *parser, ତାର୍କିକ type_seen_p, c_dtr_syn kind,
			    ତାର୍କିକ *seen_id)
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

  ଯଦି (kind != C_DTR_ABSTRACT
      && c_parser_next_token_is (parser, CPP_NAME)
      && ((type_seen_p
	   && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_kind == C_ID_ID))
    {
      ସଂରଚନା c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      *seen_id = ସତ୍ୟ;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ଯଦି (c_parser_nth_token_starts_std_attributes (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      ଫେରନ୍ତୁ c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  ଯଦି (kind != C_DTR_NORMAL
      && c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      ସଂରଚନା c_declarator *inner = build_id_declarator (NULL_ବୃକ୍ଷ);
      inner->id_loc = c_parser_peek_token (parser)->location;
      ଫେରନ୍ତୁ c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      ବୃକ୍ଷ attrs;
      ସଂରଚନା c_declarator *inner;
      c_parser_consume_token (parser);
      ତାର୍କିକ have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      ଯଦି (kind != C_DTR_NORMAL
	  && (c_parser_next_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_attributes (parser, 1)
		      || c_parser_next_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  ସଂରଚନା c_arg_info *args
	    = c_parser_parms_declarator (parser, kind == C_DTR_NORMAL,
					 attrs, have_gnu_attrs);
	  ଯଦି (args == ଖାଲି)
	    ଫେରନ୍ତୁ ଖାଲି;
	  ଅନ୍ୟଥା
	    {
	      inner = build_id_declarator (NULL_ବୃକ୍ଷ);
	      ଯଦି (!(args->types
		    && args->types != error_mark_ଗଣ୍ଠି
		    && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_ମୂଲ୍ୟ (args->types)) == IDENTIFIER_ଗଣ୍ଠି)
		  && c_parser_nth_token_starts_std_attributes (parser, 1))
		{
		  ବୃକ୍ଷ std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  ଯଦି (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (args, inner);
	      ଫେରନ୍ତୁ c_parser_direct_declarator_inner (parser, *seen_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      ଯଦି (inner != ଖାଲି && attrs != ଖାଲି)
	inner = build_attrs_declarator (attrs, inner);
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  ଯଦି (inner == ଖାଲି)
	    ଫେରନ୍ତୁ ଖାଲି;
	  ଅନ୍ୟଥା
	    ଫେରନ୍ତୁ c_parser_direct_declarator_inner (parser, *seen_id, inner);
	}
      ଅନ୍ୟଥା
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ଫେରନ୍ତୁ ଖାଲି;
	}
    }
  ଅନ୍ୟଥା
    {
      ଯଦି (kind == C_DTR_NORMAL)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  ଫେରନ୍ତୁ ଖାଲି;
	}
      ଅନ୍ୟଥା
	ଫେରନ୍ତୁ build_id_declarator (NULL_ବୃକ୍ଷ);
    }
}

/* Parse part of a direct declarator or direct abstract declarator,
   given that some (in INNER) has already been parsed; ID_PRESENT is
   true if an identifier is present, false for an abstract
   declarator.  */

ସ୍ଥିର ସଂରଚନା c_declarator *
c_parser_direct_declarator_inner (c_parser *parser, ତାର୍କିକ id_present,
				  ସଂରଚନା c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      ସଂରଚନା c_declarator *declarator;
      ସଂରଚନା c_declspecs *quals_attrs = build_null_declspecs ();
      ସଂରଚନା c_ପଦସମଷ୍ଟି dimen;
      dimen.ମୂଲ୍ୟ = NULL_ବୃକ୍ଷ;
      dimen.original_code = ERROR_MARK;
      dimen.original_type = NULL_ବୃକ୍ଷ;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, ମିଥ୍ୟା, ମିଥ୍ୟା, ସତ୍ୟ,
			  ମିଥ୍ୟା, ମିଥ୍ୟା, ମିଥ୍ୟା, ମିଥ୍ୟା, cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      ଯଦି (c_parser_next_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  ଯଦି (!quals_attrs->declspecs_seen_p)
	    c_parser_declspecs (parser, quals_attrs, ମିଥ୍ୟା, ମିଥ୍ୟା, ସତ୍ୟ,
				ମିଥ୍ୟା, ମିଥ୍ୟା, ମିଥ୍ୟା, ମିଥ୍ୟା, cla_prefer_id);
	}
      ଯଦି (!quals_attrs->declspecs_seen_p)
	quals_attrs = ଖାଲି;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      ଅଚଳ ତାର୍କିକ static_seen = (static_loc != UNKNOWN_LOCATION);
      ତାର୍କିକ star_seen = ମିଥ୍ୟା;
      ଯଦି (c_parser_next_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_SQUARE)
	{
	  star_seen = ସତ୍ୟ;
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା ଯଦି (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	dimen = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);

      ଯଦି (static_seen)
	{
	  ଯଦି (star_seen)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      star_seen = ମିଥ୍ୟା;
	      dimen.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
	    }
	  ଅନ୍ୟଥା ଯଦି (!dimen.ମୂଲ୍ୟ)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	c_parser_consume_token (parser);
      ଅନ୍ୟଥା
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  ଫେରନ୍ତୁ ଖାଲି;
	}
      ଯଦି (dimen.ମୂଲ୍ୟ)
	dimen = convert_lvalue_to_rvalue (brace_loc, dimen, ସତ୍ୟ, ସତ୍ୟ);
      declarator = build_array_declarator (brace_loc, dimen.ମୂଲ୍ୟ, quals_attrs,
					   static_seen, star_seen);
      ଯଦି (declarator == ଖାଲି)
	ଫେରନ୍ତୁ ଖାଲି;
      ଯଦି (c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  ବୃକ୍ଷ std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  ଯଦି (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = set_array_declarator_inner (declarator, inner);
      ଫେରନ୍ତୁ c_parser_direct_declarator_inner (parser, id_present, inner);
    }
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      ବୃକ୍ଷ attrs;
      ସଂରଚନା c_arg_info *args;
      c_parser_consume_token (parser);
      ତାର୍କିକ have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      args = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      ଯଦି (args == ଖାଲି)
	ଫେରନ୍ତୁ ଖାଲି;
      ଅନ୍ୟଥା
	{
	  ଯଦି (!(args->types
		&& args->types != error_mark_ଗଣ୍ଠି
		&& ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_ମୂଲ୍ୟ (args->types)) == IDENTIFIER_ଗଣ୍ଠି)
	      && c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      ବୃକ୍ଷ std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      ଯଦି (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (args, inner);
	  ଫେରନ୍ତୁ c_parser_direct_declarator_inner (parser, id_present, inner);
	}
    }
  ଫେରନ୍ତୁ inner;
}

/* Parse a parameter list or identifier list, including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list.  ID_LIST_OK is true if an identifier list
   is acceptable; such a list must not have attributes at the start.
   HAVE_GNU_ATTRS says whether any gnu-attributes (including empty
   attributes) were present (in which case standard attributes cannot
   occur).  */

ସ୍ଥିର ସଂରଚନା c_arg_info *
c_parser_parms_declarator (c_parser *parser, ତାର୍କିକ id_list_ok, ବୃକ୍ଷ attrs,
			   ତାର୍କିକ have_gnu_attrs)
{
  ଠେଲ_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  ଯଦି (id_list_ok
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
      ବୃକ୍ଷ list = NULL_ବୃକ୍ଷ, *nextp = &list;
      ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  *nextp = build_ବୃକ୍ଷ_list (NULL_ବୃକ୍ଷ,
				    c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	  nextp = & ବୃକ୍ଷ_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  ଯଦି (c_parser_next_token_is_not (parser, CPP_COMMA))
	    ଭାଙ୍ଗ;
	  c_parser_consume_token (parser);
	  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      ଭାଙ୍ଗ;
	    }
	}
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ସଂରଚନା c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  କାଢ଼_scope ();
	  ଫେରନ୍ତୁ ret;
	}
      ଅନ୍ୟଥା
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  କାଢ଼_scope ();
	  ଫେରନ୍ତୁ ଖାଲି;
	}
    }
  ଅନ୍ୟଥା
    {
      ସଂରଚନା c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, ଖାଲି, have_gnu_attrs);
      କାଢ଼_scope ();
      ଫେରନ୍ତୁ ret;
    }
}

/* Parse a parameter list (possibly empty), including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list; if HAVE_GNU_ATTRS, there were some such
   attributes (possibly empty, in which case ATTRS is NULL_TREE),
   which means standard attributes cannot start the list.  EXPR is
   NULL or an expression that needs to be evaluated for the side
   effects of array size expressions in the parameters.  */

ସ୍ଥିର ସଂରଚନା c_arg_info *
c_parser_parms_list_declarator (c_parser *parser, ବୃକ୍ଷ attrs, ବୃକ୍ଷ ପଦସମଷ୍ଟି,
				ତାର୍କିକ have_gnu_attrs)
{
  ତାର୍କିକ bad_parm = ମିଥ୍ୟା;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      ସଂରଚନା c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      ଫେରନ୍ତୁ ret;
    }
  ଯଦି (c_parser_next_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      ସଂରଚନା c_arg_info *ret = build_arg_info ();

      ret->types = NULL_ବୃକ୍ଷ;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_args_stdarg_p = ସତ୍ୟ;
	  c_parser_consume_token (parser);
	  ଫେରନ୍ତୁ ret;
	}
      ଅନ୍ୟଥା
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ଫେରନ୍ତୁ ଖାଲି;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      /* Parse a parameter.  */
      ସଂରଚନା c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_ବୃକ୍ଷ;
      have_gnu_attrs = ମିଥ୍ୟା;
      ଯଦି (parm == ଖାଲି)
	bad_parm = ସତ୍ୟ;
      ଅନ୍ୟଥା
	ଠେଲ_parm_decl (parm, &ପଦସମଷ୍ଟି);
      ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  ବୃକ୍ଷ new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  ତାର୍କିକ new_have_gnu_attrs
	    = c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_attributes (parser);
	  ଫେରନ୍ତୁ c_parser_parms_list_declarator (parser, new_attrs, ପଦସମଷ୍ଟି,
						 new_have_gnu_attrs);
	}
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  ଯଦି (bad_parm)
	    ଫେରନ୍ତୁ ଖାଲି;
	  ଅନ୍ୟଥା
	    ଫେରନ୍ତୁ get_parm_info (ମିଥ୍ୟା, ପଦସମଷ୍ଟି);
	}
      ଯଦି (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, ମିଥ୍ୟା))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
	  ଫେରନ୍ତୁ ଖାଲି;
	}
      ଯଦି (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      ଯଦି (bad_parm)
		ଫେରନ୍ତୁ ଖାଲି;
	      ଅନ୍ୟଥା
		ଫେରନ୍ତୁ get_parm_info (ସତ୍ୟ, ପଦସମଷ୍ଟି);
	    }
	  ଅନ୍ୟଥା
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      ଫେରନ୍ତୁ ଖାଲି;
	    }
	}
    }
}

/* Parse a parameter declaration.  ATTRS are the gnu-attributes at the
   start of the declaration if it is the first parameter;
   HAVE_GNU_ATTRS is true if there were any gnu-attributes there (even
   empty) there.  */

ସ୍ଥିର ସଂରଚନା c_parm *
c_parser_parameter_declaration (c_parser *parser, ବୃକ୍ଷ attrs,
				ତାର୍କିକ have_gnu_attrs)
{
  ସଂରଚନା c_declspecs *specs;
  ସଂରଚନା c_declarator *declarator;
  ବୃକ୍ଷ prefix_attrs;
  ବୃକ୍ଷ postfix_attrs = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ dummy = ମିଥ୍ୟା;

  /* Accept #pragmas between parameter declarations.  */
  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, ଖାଲି, NULL_ବୃକ୍ଷ);

  ଯଦି (!c_parser_next_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      ଯଦି (parser->error)
	ଫେରନ୍ତୁ ଖାଲି;
      c_parser_set_source_position_from_token (token);
      ଯଦି (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (token->ମୂଲ୍ୟ,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  ଯଦି (ଅଚଳ ଅକ୍ଷର *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->ମୂଲ୍ୟ, suggestion);
	    }
	  ଅନ୍ୟଥା
	    error_at (token->location, "unknown type name %qE", token->ମୂଲ୍ୟ);
	  parser->error = ସତ୍ୟ;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      ଅନ୍ୟଥା
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_to_end_of_parameter (parser);
      ଫେରନ୍ତୁ ଖାଲି;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  ଯଦି (attrs)
    {
      declspecs_add_attrs (ନିବେଶ_location, specs, attrs);
      attrs = NULL_ବୃକ୍ଷ;
    }
  c_parser_declspecs (parser, specs, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ମିଥ୍ୟା,
		      !have_gnu_attrs, ସତ୍ୟ, cla_nonabstract_decl);
  finish_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  ଯଦି (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_ଶୀର୍ଷ_anonymous_type (specs->type);

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  specs->attrs = NULL_ବୃକ୍ଷ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_PARM, &dummy);
  ଯଦି (declarator == ଖାଲି)
    {
      c_parser_skip_until_found (parser, CPP_COMMA, ଖାଲି);
      ଫେରନ୍ତୁ ଖାଲି;
    }
  ଯଦି (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
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
  ଯେତେବେଳେ (id_declarator && id_declarator->kind != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : start_loc);
  location_t param_loc = make_location (caret_loc, start_loc, end_loc);

  ଫେରନ୍ତୁ build_c_parm (specs, chainon (postfix_attrs, prefix_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_asm_string_literal (c_parser *parser)
{
  ବୃକ୍ଷ str;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା save_flag = warn_overlength_strings;
  warn_overlength_strings = 0;
  str = c_parser_string_literal (parser, ମିଥ୍ୟା, ମିଥ୍ୟା).ମୂଲ୍ୟ;
  warn_overlength_strings = save_flag;
  ଫେରନ୍ତୁ str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_simple_asm_ପଦସମଷ୍ଟି (c_parser *parser)
{
  ବୃକ୍ଷ str;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  str = c_parser_asm_string_literal (parser);
  ଯଦି (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }
  ଫେରନ୍ତୁ str;
}

ସ୍ଥିର ବୃକ୍ଷ
c_parser_gnu_attribute_any_word (c_parser *parser)
{
  ବୃକ୍ଷ attr_name = NULL_ବୃକ୍ଷ;

  ଯଦି (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      /* ??? See comment above about what keywords are accepted here.  */
      ତାର୍କିକ ok;
      ବାଛ (c_parser_peek_token (parser)->keyword)
	{
	ସ୍ଥିତି RID_STATIC:
	ସ୍ଥିତି RID_UNSIGNED:
	ସ୍ଥିତି RID_LONG:
	ସ୍ଥିତି RID_CONST:
	ସ୍ଥିତି RID_EXTERN:
	ସ୍ଥିତି RID_REGISTER:
	ସ୍ଥିତି RID_TYPEDEF:
	ସ୍ଥିତି RID_SHORT:
	ସ୍ଥିତି RID_INLINE:
	ସ୍ଥିତି RID_NORETURN:
	ସ୍ଥିତି RID_VOLATILE:
	ସ୍ଥିତି RID_SIGNED:
	ସ୍ଥିତି RID_AUTO:
	ସ୍ଥିତି RID_RESTRICT:
	ସ୍ଥିତି RID_COMPLEX:
	ସ୍ଥିତି RID_THREAD:
	ସ୍ଥିତି RID_INT:
	ସ୍ଥିତି RID_CHAR:
	ସ୍ଥିତି RID_FLOAT:
	ସ୍ଥିତି RID_DOUBLE:
	ସ୍ଥିତି RID_VOID:
	ସ୍ଥିତି RID_DFLOAT32:
	ସ୍ଥିତି RID_DFLOAT64:
	ସ୍ଥିତି RID_DFLOAT128:
	ସ୍ଥିତି RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	ସ୍ଥିତି RID_BOOL:
	ସ୍ଥିତି RID_BITINT:
	ସ୍ଥିତି RID_FRACT:
	ସ୍ଥିତି RID_ACCUM:
	ସ୍ଥିତି RID_SAT:
	ସ୍ଥିତି RID_TRANSACTION_ATOMIC:
	ସ୍ଥିତି RID_TRANSACTION_CANCEL:
	ସ୍ଥିତି RID_ATOMIC:
	ସ୍ଥିତି RID_AUTO_TYPE:
	ସ୍ଥିତି RID_CONSTEXPR:
	ସ୍ଥିତି RID_INT_N_0:
	ସ୍ଥିତି RID_INT_N_1:
	ସ୍ଥିତି RID_INT_N_2:
	ସ୍ଥିତି RID_INT_N_3:
	  ok = ସତ୍ୟ;
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ok = ମିଥ୍ୟା;
	  ଭାଙ୍ଗ;
	}
      ଯଦି (!ok)
	ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(ପୂର୍ଣ୍ଣସଂଖ୍ୟା) c_parser_peek_token (parser)->keyword];
    }
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->ମୂଲ୍ୟ;

  ଫେରନ୍ତୁ attr_name;
}

/* Parse attribute arguments.  This is a common form of syntax
   covering all currently valid GNU and standard attributes.

   gnu-attribute-arguments:
     identifier
     identifier , nonempty-expr-list
     expr-list

   where the "identifier" must not be declared as a type.  ??? Why not
   allow identifiers declared as types to start the arguments?  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_attribute_arguments (c_parser *parser, ତାର୍କିକ takes_identifier,
			      ତାର୍କିକ require_string, ତାର୍କିକ assume_attr,
			      ତାର୍କିକ allow_empty_args)
{
  vec<ବୃକ୍ଷ, va_gc> *ପଦସମଷ୍ଟି_list;
  ବୃକ୍ଷ attr_args;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
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
      ବୃକ୍ଷ arg1 = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      c_parser_consume_token (parser);
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	attr_args = build_ବୃକ୍ଷ_list (NULL_ବୃକ୍ଷ, arg1);
      ଅନ୍ୟଥା
	{
	  ବୃକ୍ଷ ବୃକ୍ଷ_list;
	  c_parser_consume_token (parser);
	  ପଦସମଷ୍ଟି_list = c_parser_ପଦସମଷ୍ଟି_list (parser, ମିଥ୍ୟା, ସତ୍ୟ,
					  ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି);
	  ବୃକ୍ଷ_list = build_ବୃକ୍ଷ_list_vec (ପଦସମଷ୍ଟି_list);
	  attr_args = ବୃକ୍ଷ_cons (NULL_ବୃକ୍ଷ, arg1, ବୃକ୍ଷ_list);
	  release_ବୃକ୍ଷ_vector (ପଦସମଷ୍ଟି_list);
	}
    }
  ଅନ୍ୟଥା
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ଯଦି (!allow_empty_args)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_args = NULL_ବୃକ୍ଷ;
	}
      ଅନ୍ୟଥା ଯଦି (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  ବୃକ୍ଷ string = c_parser_string_literal (parser, ମିଥ୍ୟା, ସତ୍ୟ).ମୂଲ୍ୟ;
	  attr_args = build_ବୃକ୍ଷ_list (NULL_ବୃକ୍ଷ, string);
	}
      ଅନ୍ୟଥା ଯଦି (assume_attr)
	{
	  ବୃକ୍ଷ cond
	    = c_parser_conditional_expression (parser, ଖାଲି, NULL_ବୃକ୍ଷ).ମୂଲ୍ୟ;
	  ଯଦି (!c_parser_next_token_is (parser, CPP_COMMA))
	    attr_args = build_ବୃକ୍ଷ_list (NULL_ବୃକ୍ଷ, cond);
	  ଅନ୍ୟଥା
	    {
	      ବୃକ୍ଷ ବୃକ୍ଷ_list;
	      c_parser_consume_token (parser);
	      ପଦସମଷ୍ଟି_list = c_parser_ପଦସମଷ୍ଟି_list (parser, ମିଥ୍ୟା, ସତ୍ୟ,
					      ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି);
	      ବୃକ୍ଷ_list = build_ବୃକ୍ଷ_list_vec (ପଦସମଷ୍ଟି_list);
	      attr_args = ବୃକ୍ଷ_cons (NULL_ବୃକ୍ଷ, cond, ବୃକ୍ଷ_list);
	      release_ବୃକ୍ଷ_vector (ପଦସମଷ୍ଟି_list);
	    }
	}
      ଅନ୍ୟଥା
	{
	  ପଦସମଷ୍ଟି_list = c_parser_ପଦସମଷ୍ଟି_list (parser, ମିଥ୍ୟା, ସତ୍ୟ,
					  ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି);
	  attr_args = build_ବୃକ୍ଷ_list_vec (ପଦସମଷ୍ଟି_list);
	  release_ବୃକ୍ଷ_vector (ପଦସମଷ୍ଟି_list);
	}
    }
  ଫେରନ୍ତୁ attr_args;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_gnu_attribute (c_parser *parser, ବୃକ୍ଷ attrs,
			ତାର୍କିକ expect_comma = ମିଥ୍ୟା, ତାର୍କିକ empty_ok = ସତ୍ୟ)
{
  ତାର୍କିକ comma_first = c_parser_next_token_is (parser, CPP_COMMA);
  ଯଦି (!comma_first
      && !c_parser_next_token_is (parser, CPP_NAME)
      && !c_parser_next_token_is (parser, CPP_KEYWORD))
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;

  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ଯଦି (!empty_ok)
	ଫେରନ୍ତୁ attrs;
    }

  ବୃକ୍ଷ attr_name = c_parser_gnu_attribute_any_word (parser);
  ଯଦି (attr_name == NULL_ବୃକ୍ଷ)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  ବୃକ୍ଷ attr;
  ଯଦି (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      ଯଦି (expect_comma && !comma_first)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      attr = build_ବୃକ୍ଷ_list (attr_name, NULL_ବୃକ୍ଷ);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      ଫେରନ୍ତୁ attrs;
    }
  c_parser_consume_token (parser);

  ବୃକ୍ଷ attr_args
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    ମିଥ୍ୟା,
				    is_attribute_p ("assume", attr_name),
				    ସତ୍ୟ);

  attr = build_ବୃକ୍ଷ_list (attr_name, attr_args);
  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  ଅନ୍ୟଥା
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  ଯଦି (expect_comma && !comma_first)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  ଫେରନ୍ତୁ attrs;
}

ସ୍ଥିର ବୃକ୍ଷ
c_parser_gnu_attributes (c_parser *parser)
{
  ବୃକ୍ଷ attrs = NULL_ବୃକ୍ଷ;
  ଯେତେବେଳେ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      ତାର୍କିକ save_translate_strings_p = parser->translate_strings_p;
      parser->translate_strings_p = ମିଥ୍ୟା;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  ଫେରନ୍ତୁ attrs;
	}
      ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
	  ଫେରନ୍ତୁ attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      ପାଇଁ (ତାର୍କିକ expect_comma = ମିଥ୍ୟା; ; expect_comma = ସତ୍ୟ)
	{
	  /* Parse a single attribute.  */
	  ବୃକ୍ଷ attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  ଯଦି (attr == error_mark_ଗଣ୍ଠି)
	    ଫେରନ୍ତୁ attrs;
	  ଯଦି (!attr)
	    ଭାଙ୍ଗ;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      ଅନ୍ୟଥା
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ଫେରନ୍ତୁ attrs;
	}
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      ଅନ୍ୟଥା
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ଫେରନ୍ତୁ attrs;
	}
      parser->translate_strings_p = save_translate_strings_p;
    }

  ଫେରନ୍ତୁ attrs;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_balanced_token_sequence (c_parser *parser)
{
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      c_token *token = c_parser_peek_token (parser);
      ବାଛ (token->type)
	{
	ସ୍ଥିତି CPP_OPEN_BRACE:
	  {
	    matching_braces braces;
	    braces.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    braces.require_close (parser);
	    ଭାଙ୍ଗ;
	  }

	ସ୍ଥିତି CPP_OPEN_PAREN:
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    parens.require_close (parser);
	    ଭାଙ୍ଗ;
	  }

	ସ୍ଥିତି CPP_OPEN_SQUARE:
	  c_parser_consume_token (parser);
	  c_parser_balanced_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି CPP_CLOSE_BRACE:
	ସ୍ଥିତି CPP_CLOSE_PAREN:
	ସ୍ଥିତି CPP_CLOSE_SQUARE:
	ସ୍ଥିତି CPP_EOF:
	  ଫେରନ୍ତୁ;

	ସ୍ଥିତି CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	  ଭାଙ୍ଗ;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  c_parser_consume_token (parser);
	  ଭାଙ୍ଗ;
	}
    }
}

/* Parse arguments of omp::directive or omp::decl attribute.

   directive-name ,[opt] clause-list[opt]

   For directive just remember the tokens in a vector for subsequent
   parsing.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_directive_args (c_parser *parser, ବୃକ୍ଷ attribute, ତାର୍କିକ decl_p)
{
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା n = 1;
  c_token *first = c_parser_peek_token (parser);
  ଯଦି (!c_parser_check_balanced_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_balanced_token_sequence (parser);
      ବୃକ୍ଷ_ମୂଲ୍ୟ (attribute) = NULL_ବୃକ୍ଷ;
      ଫେରନ୍ତୁ;
    }
  ଯଦି (n == 1)
    {
      error_at (first->location, "expected OpenMP directive name");
      ବୃକ୍ଷ_ମୂଲ୍ୟ (attribute) = NULL_ବୃକ୍ଷ;
      ଫେରନ୍ତୁ;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  ପାଇଁ (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->quick_ଠେଲ (*tok);
      c_parser_consume_token (parser);
    }
  ବୃକ୍ଷ arg = make_ଗଣ୍ଠି (C_TOKEN_VEC);
  C_TOKEN_VEC_TOKENS (arg) = v;
  ଯଦି (decl_p)
    ବୃକ୍ଷ_PUBLIC (arg) = 1;
  ବୃକ୍ଷ_ମୂଲ୍ୟ (attribute) = ବୃକ୍ଷ_cons (NULL_ବୃକ୍ଷ, arg, ବୃକ୍ଷ_ମୂଲ୍ୟ (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_sequence_args (c_parser *parser, ବୃକ୍ଷ attribute)
{
  କର
    {
      c_token *token = c_parser_peek_token (parser);
      ଯଦି (token->type == CPP_NAME
	  && strcmp (IDENTIFIER_POINTER (token->ମୂଲ୍ୟ), "omp") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_SCOPE)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  token = c_parser_peek_token (parser);
	}
      ତାର୍କିକ directive = ମିଥ୍ୟା;
      ଅଚଳ ଅକ୍ଷର *p;
      ଯଦି (token->type != CPP_NAME)
	p = "";
      ଅନ୍ୟଥା
	p = IDENTIFIER_POINTER (token->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "directive") == 0)
	directive = ସତ୍ୟ;
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  unsigned nesting_depth = 0;

	  ଯେତେବେଳେ (ସତ୍ୟ)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      ଯଦି ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_depth)
		ଭାଙ୍ଗ;
	      /* If we've run out of tokens, stop.  */
	      ଯଦି (token->type == CPP_EOF)
		ଭାଙ୍ଗ;
	      ଯଦି (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
		ଭାଙ୍ଗ;
	      ଯଦି (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_SQUARE)
		++nesting_depth;
	      ଅନ୍ୟଥା ଯଦି (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_SQUARE)
		{
		  ଯଦି (nesting_depth-- == 0)
		    ଭାଙ୍ଗ;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  ଯଦି (c_parser_next_token_is_not (parser, CPP_COMMA))
	    ଭାଙ୍ଗ;
	  c_parser_consume_token (parser);
	  ଜାରି;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      ଯଦି (parens.require_open (parser))
	{
	  ଯଦି (directive)
	    c_parser_omp_directive_args (parser, attribute, ମିଥ୍ୟା);
	  ଅନ୍ୟଥା
	    c_parser_omp_sequence_args (parser, attribute);
	  parens.skip_until_found_close (parser);
	  ଯଦି (c_parser_next_token_is_not (parser, CPP_COMMA))
	    ଭାଙ୍ଗ;
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_not (parser, CPP_COMMA))
	ଭାଙ୍ଗ;
      ଅନ୍ୟଥା
	c_parser_consume_token (parser);
    }
  ଯେତେବେଳେ (1);
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_std_attribute (c_parser *parser, ତାର୍କିକ for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  ବୃକ୍ଷ ns, name, attribute;

  /* Parse the attribute-token.  */
  ଯଦି (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  name = canonicalize_attr_name (token->ମୂଲ୍ୟ);
  c_parser_consume_token (parser);
  ଯଦି (c_parser_next_token_is (parser, CPP_SCOPE)
      || (c_parser_next_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      ଯଦି (c_parser_next_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      ଯଦି (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      name = canonicalize_attr_name (token->ମୂଲ୍ୟ);
      c_parser_consume_token (parser);
    }
  ଅନ୍ୟଥା
    ns = NULL_ବୃକ୍ଷ;
  attribute = build_ବୃକ୍ଷ_list (build_ବୃକ୍ଷ_list (ns, name), NULL_ବୃକ୍ଷ);

  /* Parse the arguments, if any.  */
  ଅଚଳ attribute_spec *as = lookup_attribute_spec (ବୃକ୍ଷ_PURPOSE (attribute));
  ଯଦି (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      ଯଦି ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଯାଅ out;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    ଯଦି ((as && as->max_length == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_found_close (parser);
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    ଯଦି (as && !attribute_ignored_p (as))
      {
	ତାର୍କିକ takes_identifier
	  = (ns != NULL_ବୃକ୍ଷ
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	ତାର୍କିକ require_string
	  = (ns == NULL_ବୃକ୍ଷ
	     && (strcmp (IDENTIFIER_POINTER (name), "deprecated") == 0
		 || strcmp (IDENTIFIER_POINTER (name), "nodiscard") == 0));
	ତାର୍କିକ assume_attr
	  = (ns != NULL_ବୃକ୍ଷ
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && strcmp (IDENTIFIER_POINTER (name), "assume") == 0);
	ବୃକ୍ଷ_ମୂଲ୍ୟ (attribute)
	  = c_parser_attribute_arguments (parser, takes_identifier,
					  require_string, assume_attr, ମିଥ୍ୟା);
      }
    ଅନ୍ୟଥା
      {
	ଯଦି ((flag_openmp || flag_openmp_simd)
	    && ns
	    && is_attribute_p ("omp", ns))
	  {
	    ଯଦି (is_attribute_p ("directive", name))
	      {
		c_parser_omp_directive_args (parser, attribute, ମିଥ୍ୟା);
		parens.skip_until_found_close (parser);
		ଫେରନ୍ତୁ attribute;
	      }
	    ଅନ୍ୟଥା ଯଦି (is_attribute_p ("decl", name))
	      {
		ବୃକ୍ଷ_ମୂଲ୍ୟ (ବୃକ୍ଷ_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_args (parser, attribute, ସତ୍ୟ);
		parens.skip_until_found_close (parser);
		ଫେରନ୍ତୁ attribute;
	      }
	    ଅନ୍ୟଥା ଯଦି (is_attribute_p ("sequence", name))
	      {
		ବୃକ୍ଷ_ମୂଲ୍ୟ (ବୃକ୍ଷ_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_args (parser, attribute);
		parens.skip_until_found_close (parser);
		ବୃକ୍ଷ_ମୂଲ୍ୟ (attribute) = nreverse (ବୃକ୍ଷ_ମୂଲ୍ୟ (attribute));
		ଫେରନ୍ତୁ attribute;
	      }
	  }
	c_parser_balanced_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 out:
  ଯଦି (ns == NULL_ବୃକ୍ଷ && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (ନିବେଶ_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  ଫେରନ୍ତୁ attribute;
}

ସ୍ଥିର ବୃକ୍ଷ
c_parser_std_attribute_list (c_parser *parser, ତାର୍କିକ for_tm)
{
  ବୃକ୍ଷ attributes = NULL_ବୃକ୍ଷ;
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      c_token *token = c_parser_peek_token (parser);
      ଯଦି (token->type == CPP_CLOSE_SQUARE)
	ଭାଙ୍ଗ;
      ଯଦି (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ଜାରି;
	}
      ବୃକ୍ଷ attribute = c_parser_std_attribute (parser, for_tm);
      ଯଦି (attribute != error_mark_ଗଣ୍ଠି)
	{
	  ବୃକ୍ଷ_CHAIN (attribute) = attributes;
	  attributes = attribute;
	}
      ଯଦି (c_parser_next_token_is_not (parser, CPP_COMMA))
	ଭାଙ୍ଗ;
    }
  ଫେରନ୍ତୁ attributes;
}

ସ୍ଥିର ବୃକ୍ଷ
c_parser_std_attribute_specifier (c_parser *parser, ତାର୍କିକ for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ଯଦି (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  ଯଦି (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }
  ବୃକ୍ଷ attributes;
  ଯଦି (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      auto ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      attributes = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  ଅନ୍ୟଥା
    {
      ଯଦି (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      attributes = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  ଫେରନ୍ତୁ nreverse (attributes);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

ସ୍ଥିର ତାର୍କିକ
c_parser_check_balanced_raw_token_sequence (c_parser *parser, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *n)
{
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      c_token *token = c_parser_peek_nth_token_raw (parser, *n);
      ବାଛ (token->type)
	{
	ସ୍ଥିତି CPP_OPEN_BRACE:
	  {
	    ++*n;
	    ଯଦି (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		ଯଦି (token->type == CPP_CLOSE_BRACE)
		  ++*n;
		ଅନ୍ୟଥା
		  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	      }
	    ଅନ୍ୟଥା
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;
	    ଭାଙ୍ଗ;
	  }

	ସ୍ଥିତି CPP_OPEN_PAREN:
	  {
	    ++*n;
	    ଯଦି (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		ଯଦି (token->type == CPP_CLOSE_PAREN)
		  ++*n;
		ଅନ୍ୟଥା
		  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	      }
	    ଅନ୍ୟଥା
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;
	    ଭାଙ୍ଗ;
	  }

	ସ୍ଥିତି CPP_OPEN_SQUARE:
	  {
	    ++*n;
	    ଯଦି (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		ଯଦି (token->type == CPP_CLOSE_SQUARE)
		  ++*n;
		ଅନ୍ୟଥା
		  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	      }
	    ଅନ୍ୟଥା
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;
	    ଭାଙ୍ଗ;
	  }

	ସ୍ଥିତି CPP_CLOSE_BRACE:
	ସ୍ଥିତି CPP_CLOSE_PAREN:
	ସ୍ଥିତି CPP_CLOSE_SQUARE:
	ସ୍ଥିତି CPP_EOF:
	  ଫେରନ୍ତୁ ସତ୍ୟ;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ++*n;
	  ଭାଙ୍ଗ;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

ସ୍ଥିର ତାର୍କିକ
c_parser_nth_token_starts_std_attributes (c_parser *parser, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା n)
{
  ଯଦି (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_SQUARE
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_SQUARE))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  ଯଦି (!c_dialect_objc ())
    ଫେରନ୍ତୁ ସତ୍ୟ;
  n += 2;
  ଯଦି (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  ଯଦି (token->type != CPP_CLOSE_SQUARE)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  ଫେରନ୍ତୁ token->type == CPP_CLOSE_SQUARE;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

ସ୍ଥିର size_t
c_parser_skip_std_attribute_spec_seq (c_parser *parser, size_t n)
{
  size_t orig_n = n;
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      ଯଦି (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_SQUARE
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_SQUARE))
	{
	  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା m = n + 2;
	  ଯଦି (!c_parser_check_balanced_raw_token_sequence (parser, &m))
	    ଫେରନ୍ତୁ orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  ଯଦି (token->type != CPP_CLOSE_SQUARE)
	    ଫେରନ୍ତୁ orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  ଯଦି (token->type != CPP_CLOSE_SQUARE)
	    ଫେରନ୍ତୁ orig_n;
	  n = m + 2;
	}
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
    }
  ଫେରନ୍ତୁ n;
}

ସ୍ଥିର ବୃକ୍ଷ
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  ବୃକ୍ଷ attributes = NULL_ବୃକ୍ଷ;
  କର
    {
      ବୃକ୍ଷ attrs = c_parser_std_attribute_specifier (parser, ମିଥ୍ୟା);
      attributes = chainon (attributes, attrs);
    }
  ଯେତେବେଳେ (c_parser_nth_token_starts_std_attributes (parser, 1));
  ଫେରନ୍ତୁ attributes;
}

/* Parse a type name (C90 6.5.5, C99 6.7.6, C11 6.7.7).  ALIGNAS_OK
   says whether alignment specifiers are OK (only in cases that might
   be the type name of a compound literal).

   type-name:
     specifier-qualifier-list abstract-declarator[opt]
*/

ସଂରଚନା c_type_name *
c_parser_type_name (c_parser *parser, ତାର୍କିକ alignas_ok)
{
  ସଂରଚନା c_declspecs *specs = build_null_declspecs ();
  ସଂରଚନା c_declarator *declarator;
  ସଂରଚନା c_type_name *ret;
  ତାର୍କିକ dummy = ମିଥ୍ୟା;
  c_parser_declspecs (parser, specs, ମିଥ୍ୟା, ସତ୍ୟ, ସତ୍ୟ, alignas_ok, ମିଥ୍ୟା,
		      ମିଥ୍ୟା, ସତ୍ୟ, cla_prefer_type);
  ଯଦି (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      ଫେରନ୍ତୁ ଖାଲି;
    }
  ଯଦି (specs->type != error_mark_ଗଣ୍ଠି)
    {
      pending_xref_error ();
      finish_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      ଯଦି (specs->typespec_kind == ctsk_tagdef)
	verify_counted_by_for_ଶୀର୍ଷ_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_ABSTRACT, &dummy);
  ଯଦି (declarator == ଖାଲି)
    ଫେରନ୍ତୁ ଖାଲି;
  ret = XOBNEW (&parser_obstack, ସଂରଚନା c_type_name);
  ret->specs = specs;
  ret->declarator = declarator;
  ଫେରନ୍ତୁ ret;
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

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_initializer (c_parser *parser, ବୃକ୍ଷ decl)
{
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    ଫେରନ୍ତୁ c_parser_braced_init (parser, NULL_ବୃକ୍ଷ, ମିଥ୍ୟା, ଖାଲି,
				 decl != error_mark_ଗଣ୍ଠି
				 && C_DECL_VARIABLE_SIZE (decl));
  ଅନ୍ୟଥା
    {
      ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ଯଦି (decl != error_mark_ଗଣ୍ଠି && C_DECL_VARIABLE_SIZE (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.set_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      ଯଦି (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !ବୃକ୍ଷ_STATIC (decl)
	  && ret.ମୂଲ୍ୟ == decl
	  && !warning_enabled_at (DECL_SOURCE_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      ଯଦି (ବୃକ୍ଷ_CODE (ret.ମୂଲ୍ୟ) != STRING_CST
	  && (ବୃକ୍ଷ_CODE (ret.ମୂଲ୍ୟ) != COMPOUND_LITERAL_ପଦସମଷ୍ଟି
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_ପଦସମଷ୍ଟି_DECL
					    (ret.ମୂଲ୍ୟ))))
	ret = convert_lvalue_to_rvalue (loc, ret, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ);
      ଫେରନ୍ତୁ ret;
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

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_braced_init (c_parser *parser, ବୃକ୍ଷ type, ତାର୍କିକ nested_p,
		      ସଂରଚନା obstack *outer_obstack, ତାର୍କିକ varsize_p)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
  ସଂରଚନା obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  ତାର୍କିକ save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = ମିଥ୍ୟା;
  ତାର୍କିକ zero_init_padding_bits = ମିଥ୍ୟା;
  matching_braces braces;
  braces.consume_open (parser);
  ଯଦି (nested_p)
    {
      finish_implicit_inits (brace_loc, outer_obstack);
      ଠେଲ_init_level (brace_loc, 0, &braced_init_obstack);
    }
  ଅନ୍ୟଥା
    really_start_incremental_init (type);
  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      ଯଦି (flag_isoc23)
	zero_init_padding_bits = ସତ୍ୟ;
    }
  ଅନ୍ୟଥା
    {
      ଯଦି (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      ଯେତେବେଳେ (ସତ୍ୟ)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  ଯଦି (parser->error)
	    ଭାଙ୍ଗ;
	  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      last_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_ପଦସମଷ୍ଟି embed_val;
		  embed_val.ମୂଲ୍ୟ = embed->ମୂଲ୍ୟ;
		  embed_val.original_code = RAW_DATA_CST;
		  embed_val.original_type = integer_type_ଗଣ୍ଠି;
		  set_c_ପଦସମଷ୍ଟି_source_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, ମିଥ୍ୟା,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_next_token_is (parser,
							       CPP_COMMA));
		  last_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  ଅନ୍ୟଥା
	    ଭାଙ୍ଗ;
	  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    ଭାଙ୍ଗ;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *next_tok = c_parser_peek_token (parser);
  ଯଦି (next_tok->type != CPP_CLOSE_BRACE)
    {
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = ଖାଲି;
      braces.skip_until_found_close (parser);
      କାଢ଼_init_level (brace_loc, 0, &braced_init_obstack, last_init_list_comma);
      obstack_free (&braced_init_obstack, ଖାଲି);
      ଫେରନ୍ତୁ ret;
    }
  location_t close_loc = next_tok->location;
  c_parser_consume_token (parser);
  ret = କାଢ଼_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  ଯଦି (zero_init_padding_bits
      && ret.ମୂଲ୍ୟ
      && ବୃକ୍ଷ_CODE (ret.ମୂଲ୍ୟ) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_BITS (ret.ମୂଲ୍ୟ) = 1;
  obstack_free (&braced_init_obstack, ଖାଲି);
  set_c_ପଦସମଷ୍ଟି_source_range (&ret, brace_loc, close_loc);
  ଫେରନ୍ତୁ ret;
}

/* Parse a nested initializer, including designators.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_initelt (c_parser *parser, ସଂରଚନା obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      set_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->ମୂଲ୍ୟ,
		      c_parser_peek_token (parser)->location,
		      braced_init_obstack);
      /* Use the colon as the error location.  */
      pedwarn (c_parser_peek_2nd_token (parser)->location, OPT_Wpedantic,
	       "obsolete use of designated initializer with %<:%>");
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  ଅନ୍ୟଥା
    {
      /* des_seen is 0 if there have been no designators, 1 if there
	 has been a single array designator and 2 otherwise.  */
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା des_seen = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
	     || c_parser_next_token_is (parser, CPP_DOT))
	{
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା des_prev = des_seen;
	  ଯଦି (!des_seen)
	    des_loc = c_parser_peek_token (parser)->location;
	  ଯଦି (des_seen < 2)
	    des_seen++;
	  ଯଦି (c_parser_next_token_is (parser, CPP_DOT))
	    {
	      des_seen = 2;
	      c_parser_consume_token (parser);
	      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
		{
		  set_init_label (des_loc, c_parser_peek_token (parser)->ମୂଲ୍ୟ,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      ଅନ୍ୟଥା
		{
		  ସଂରଚନା c_ପଦସମଷ୍ଟି init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = ଖାଲି;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_found (parser, CPP_COMMA, ଖାଲି);
		  process_init_element (ନିବେଶ_location, init, ମିଥ୍ୟା,
					braced_init_obstack);
		  ଫେରନ୍ତୁ;
		}
	    }
	  ଅନ୍ୟଥା
	    {
	      ସଂରଚନା c_ପଦସମଷ୍ଟି first_ପଦସମଷ୍ଟି;
	      ବୃକ୍ଷ first, second;
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
	      ଯଦି (des_prev == 1 && c_dialect_objc ())
		{
		  des_seen = des_prev;
		  ଭାଙ୍ଗ;
		}
	      ଯଦି (des_prev == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  ବୃକ୍ଷ rec, args;
		  ସଂରଚନା c_ପଦସମଷ୍ଟି mexpr;
		  c_parser_consume_token (parser);
		  ଯଦି (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_kind
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_kind
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      ବୃକ୍ଷ id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      ଯାଅ parse_message_args;
		    }
		  array_index_loc = c_parser_peek_token (parser)->location;
		  first_ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
		  mark_exp_read (first_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
		  ଯଦି (c_parser_next_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    ଯାଅ array_desig_after_first;
		  first = first_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = first;
		  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      ସଂରଚନା c_ପଦସମଷ୍ଟି next;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      next = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
		      next = convert_lvalue_to_rvalue (exp_loc, next,
						       ସତ୍ୟ, ସତ୍ୟ);
		      rec = build_compound_ପଦସମଷ୍ଟି (comma_loc, rec, next.ମୂଲ୍ୟ);
		    }
		parse_message_args:
		  /* Now parse the objc-message-args.  */
		  args = c_parser_objc_message_args (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					     "expected %<]%>");
		  mexpr.ମୂଲ୍ୟ
		    = objc_build_message_ପଦସମଷ୍ଟି (rec, args);
		  mexpr.original_code = ERROR_MARK;
		  mexpr.original_type = ଖାଲି;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  ଫେରନ୍ତୁ;
		}
	      c_parser_consume_token (parser);
	      array_index_loc = c_parser_peek_token (parser)->location;
	      first_ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	      mark_exp_read (first_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	    array_desig_after_first:
	      first_ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (array_index_loc,
						     first_ପଦସମଷ୍ଟି,
						     ସତ୍ୟ, ସତ୍ୟ);
	      first = first_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
	      ଯଦି (c_parser_next_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  second = convert_lvalue_to_rvalue (ellipsis_loc,
						     (c_parser_ପଦସମଷ୍ଟି_no_commas
						      (parser, ଖାଲି)),
						     ସତ୍ୟ, ସତ୍ୟ).ମୂଲ୍ୟ;
		  mark_exp_read (second);
		}
	      ଅନ୍ୟଥା
		second = NULL_ବୃକ୍ଷ;
	      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		{
		  c_parser_consume_token (parser);
		  set_init_index (array_index_loc, first, second,
				  braced_init_obstack);
		  ଯଦି (second)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      ଅନ୍ୟଥା
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					   "expected %<]%>");
	    }
	}
      ଯଦି (des_seen >= 1)
	{
	  ଯଦି (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  ଅନ୍ୟଥା
	    {
	      ଯଦି (des_seen == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      ଅନ୍ୟଥା
		{
		  ସଂରଚନା c_ପଦସମଷ୍ଟି init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = ଖାଲି;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_found (parser, CPP_COMMA, ଖାଲି);
		  process_init_element (ନିବେଶ_location, init, ମିଥ୍ୟା,
					braced_init_obstack);
		  ଫେରନ୍ତୁ;
		}
	    }
	}
    }
  c_parser_initval (parser, ଖାଲି, braced_init_obstack);
}

/* Parse a nested initializer; as c_parser_initializer but parses
   initializers within braced lists, after any designators have been
   applied.  If AFTER is not NULL then it is an Objective-C message
   expression which is the primary-expression starting the
   initializer.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_initval (c_parser *parser, ସଂରଚନା c_ପଦସମଷ୍ଟି *after,
		  ସଂରଚନା obstack * braced_init_obstack)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_ବୃକ୍ଷ, ସତ୍ୟ,
				 braced_init_obstack, ମିଥ୍ୟା);
  ଅନ୍ୟଥା
    {
      init = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, after);
      ଯଦି (init.ମୂଲ୍ୟ != NULL_ବୃକ୍ଷ
	  && ବୃକ୍ଷ_CODE (init.ମୂଲ୍ୟ) != STRING_CST
	  && (ବୃକ୍ଷ_CODE (init.ମୂଲ୍ୟ) != COMPOUND_LITERAL_ପଦସମଷ୍ଟି
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_ପଦସମଷ୍ଟି_DECL
					    (init.ମୂଲ୍ୟ))))
	init = convert_lvalue_to_rvalue (loc, init, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ);
    }
  ବୃକ୍ଷ val = init.ମୂଲ୍ୟ;
  process_init_element (loc, init, ମିଥ୍ୟା, braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  ସ୍ଥିର unsigned vals_to_ignore;
  ଯଦି (vals_to_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_to_ignore;
  ଅନ୍ୟଥା ଯଦି (val
	   && ବୃକ୍ଷ_CODE (val) == INTEGER_CST
	   && ବୃକ୍ଷ_TYPE (val) == integer_type_ଗଣ୍ଠି
	   && c_parser_next_token_is (parser, CPP_COMMA))
    ଯଦି (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା len = c_maybe_optimize_large_byte_initializer ())
      {
	ଅକ୍ଷର buf1[64];
	unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
	gcc_checking_assert (len >= 64);
	location_t last_loc = UNKNOWN_LOCATION;
	ପାଇଁ (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    ଯଦି (tok->type != CPP_COMMA)
	      ଭାଙ୍ଗ;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    ଯଦି (tok->type != CPP_ସଂଖ୍ୟା
		|| ବୃକ୍ଷ_CODE (tok->ମୂଲ୍ୟ) != INTEGER_CST
		|| ବୃକ୍ଷ_TYPE (tok->ମୂଲ୍ୟ) != integer_type_ଗଣ୍ଠି
		|| wi::neg_p (wi::to_wide (tok->ମୂଲ୍ୟ))
		|| wi::to_widest (tok->ମୂଲ୍ୟ) > UCHAR_MAX)
	      ଭାଙ୍ଗ;
	    buf1[i] = (ଅକ୍ଷର) ବୃକ୍ଷ_to_uhwi (tok->ମୂଲ୍ୟ);
	    ଯଦି (i == 0)
	      loc = tok->location;
	    last_loc = tok->location;
	  }
	ଯଦି (i < 64)
	  {
	    vals_to_ignore = i;
	    ଫେରନ୍ତୁ;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	ଯଦି (tok->type == CPP_CLOSE_BRACE && len != INT_MAX)
	  len = i;
	ଅନ୍ୟଥା ଯଦି (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_ସଂଖ୍ୟା))
	  {
	    vals_to_ignore = i;
	    ଫେରନ୍ତୁ;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_len = 131072 - offsetof (ସଂରଚନା ବୃକ୍ଷ_string, str) - 1;
	unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା orig_len = len;
	unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା off = 0, last = 0;
	ଯଦି (!wi::neg_p (wi::to_wide (val)) && wi::to_widest (val) <= UCHAR_MAX)
	  off = 1;
	len = MIN (len, max_len - off);
	ଅକ୍ଷର *buf2 = XNEWVEC (ଅକ୍ଷର, len + off);
	ଯଦି (off)
	  buf2[0] = (ଅକ୍ଷର) ବୃକ୍ଷ_to_uhwi (val);
	memcpy (buf2 + off, buf1, i);
	ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	ପାଇଁ (; i < len; ++i)
	  {
	    ଯଦି (!c_parser_next_token_is (parser, CPP_COMMA))
	      ଭାଙ୍ଗ;
	    tok = c_parser_peek_2nd_token (parser);
	    ଯଦି (tok->type != CPP_ସଂଖ୍ୟା
		|| ବୃକ୍ଷ_CODE (tok->ମୂଲ୍ୟ) != INTEGER_CST
		|| ବୃକ୍ଷ_TYPE (tok->ମୂଲ୍ୟ) != integer_type_ଗଣ୍ଠି
		|| wi::neg_p (wi::to_wide (tok->ମୂଲ୍ୟ))
		|| wi::to_widest (tok->ମୂଲ୍ୟ) > UCHAR_MAX)
	      ଭାଙ୍ଗ;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    ଯଦି (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      ଭାଙ୍ଗ;
	    buf2[i + off] = (ଅକ୍ଷର) ବୃକ୍ଷ_to_uhwi (tok->ମୂଲ୍ୟ);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    ଯଦି (orig_len == INT_MAX
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_ସଂଖ୍ୟା)))
	      {
		last = 1;
		ଭାଙ୍ଗ;
	      }
	    last_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_ଗଣ୍ଠି (RAW_DATA_CST);
	ବୃକ୍ଷ_TYPE (val) = integer_type_ଗଣ୍ଠି;
	RAW_DATA_LENGTH (val) = i;
	ବୃକ୍ଷ owner = build_string (i + off + last, buf2);
	XDELETEVEC (buf2);
	ବୃକ୍ଷ_TYPE (owner) = build_array_type_nelts (unsigned_char_type_ଗଣ୍ଠି,
						    i + off + last);
	RAW_DATA_OWNER (val) = owner;
	RAW_DATA_POINTER (val) = ବୃକ୍ଷ_STRING_POINTER (owner) + off;
	init.ମୂଲ୍ୟ = val;
	set_c_ପଦସମଷ୍ଟି_source_range (&init, loc, last_loc);
	init.original_code = RAW_DATA_CST;
	init.original_type = integer_type_ଗଣ୍ଠି;
	init.m_decimal = 0;
	process_init_element (loc, init, ମିଥ୍ୟା, braced_init_obstack);
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  ବୃକ୍ଷ stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  ଯଦି (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (ସତ୍ୟ);
      c_end_compound_stmt (brace_loc, stmt, ସତ୍ୟ);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  stmt = c_begin_compound_stmt (ସତ୍ୟ);
  location_t end_loc = c_parser_compound_statement_nostart (parser);
  ଯଦି (endlocp)
    *endlocp = end_loc;

  ଫେରନ୍ତୁ c_end_compound_stmt (brace_loc, stmt, ସତ୍ୟ);
}

/* Diagnose errors related to imperfectly nested loops in an OMP
   loop construct.  This function is called when such code is seen.
   Only issue one such diagnostic no matter how much invalid
   intervening code there is in the loop.
   FIXME: maybe the location associated with the diagnostic should
   be the current parser token instead of the location of the outer loop
   nest.  */

ସ୍ଥିର ଶୂନ୍ୟ
check_omp_intervening_code (c_parser *parser)
{
  ସଂରଚନା omp_for_parse_data *omp_for_parse_state = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);

  ଯଦି (!omp_for_parse_state->in_intervening_code)
    ଫେରନ୍ତୁ;
  omp_for_parse_state->saw_intervening_code = ସତ୍ୟ;

  /* Only diagnose errors related to perfect nesting once.  */
  ଯଦି (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      ଯଦି (omp_for_parse_state->code == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = ସତ୍ୟ;
	}
      ଅନ୍ୟଥା ଯଦି (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = ସତ୍ୟ;
	}
      ଅନ୍ୟଥା ଯଦି (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = ସତ୍ୟ;
	}
      ଅନ୍ୟଥା ଯଦି (omp_for_parse_state->code == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = ସତ୍ୟ;
	}
      ଯଦି (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->fail = ସତ୍ୟ;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
ସ୍ଥିର ଶୂନ୍ୟ
add_structured_block_stmt (ବୃକ୍ଷ sl)
{
  ଯଦି (ବୃକ୍ଷ_CODE (sl) != STATEMENT_LIST
      || !tsi_end_p (tsi_start (sl)))
    add_stmt (build1 (OMP_STRUCTURED_BLOCK, void_type_ଗଣ୍ଠି, sl));
}

ସଂରଚନା c_omp_attribute_data
{
  vec<c_token, va_gc> *tokens;
  ଅଚଳ c_omp_directive *dir;
  c_omp_directive_kind kind;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

ସ୍ଥିର ତାର୍କିକ
c_parser_handle_statement_omp_attributes (c_parser *parser, ବୃକ୍ଷ &attrs,
					  ତାର୍କିକ *have_std_attrs)
{
  ଯଦି (!flag_openmp && !flag_openmp_simd)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  auto_vec<c_omp_attribute_data, 16> vd;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା cnt = 0;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା tokens = 0;
  ତାର୍କିକ bad = ମିଥ୍ୟା;
  ପାଇଁ (ବୃକ୍ଷ *pa = &attrs; *pa; )
    ଯଦି (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	ପାଇଁ (ବୃକ୍ଷ a = ବୃକ୍ଷ_ମୂଲ୍ୟ (*pa); a; a = ବୃକ୍ଷ_CHAIN (a))
	  {
	    ବୃକ୍ଷ d = ବୃକ୍ଷ_ମୂଲ୍ୟ (a);
	    gcc_assert (ବୃକ୍ଷ_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    ଯଦି (parser->omp_attrs_forbidden_p)
	      {
		error_at (first->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = ମିଥ୍ୟା;
		bad = ସତ୍ୟ;
	      }
	    ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_PUBLIC (d))
	      {
		error_at (first->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		bad = ସତ୍ୟ;
	      }
	    ଅଚଳ ଅକ୍ଷର *directive[3] = {};
	    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 3; i++)
	      {
		ବୃକ୍ଷ id = NULL_ବୃକ୍ଷ;
		ଯଦି (first + i == last)
		  ଭାଙ୍ଗ;
		ଯଦି (first[i].type == CPP_NAME)
		  id = first[i].ମୂଲ୍ୟ;
		ଅନ୍ୟଥା ଯଦି (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(ପୂର୍ଣ୍ଣସଂଖ୍ୟା) first[i].keyword];
		ଅନ୍ୟଥା
		  ଭାଙ୍ଗ;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    ଅଚଳ c_omp_directive *dir = ଖାଲି;
	    ଯଦି (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    ଯଦି (dir == ଖାଲି)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  ବୃକ୍ଷ_PUBLIC (d) ? "omp::decl" : "omp::directive");
		ଜାରି;
	      }
	    c_omp_directive_kind kind = dir->kind;
	    ଯଦି (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		ଯଦି (directive[1]
		    && (strcmp (directive[1], "depend") == 0
			|| strcmp (directive[1], "doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
		ଅନ୍ୟଥା ଯଦି (first + 2 < last
			 && first[1].type == CPP_COMMA
			 && first[2].type == CPP_NAME
			 && (strcmp (IDENTIFIER_POINTER (first[2].ମୂଲ୍ୟ),
				     "depend") == 0
			     || strcmp (IDENTIFIER_POINTER (first[2].ମୂଲ୍ୟ),
					"doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
	      }
	    ଅନ୍ୟଥା ଯଦି (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		ପୂର୍ଣ୍ଣସଂଖ୍ୟା paren_depth = 0;
		ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 1; first + i < last; i++)
		  ଯଦି (first[i].type == CPP_OPEN_PAREN)
		    paren_depth++;
		  ଅନ୍ୟଥା ଯଦି (first[i].type == CPP_CLOSE_PAREN)
		    paren_depth--;
		  ଅନ୍ୟଥା ଯଦି (paren_depth == 0
			   && first + i + 2 < last
			   && first[i].type == CPP_NAME
			   && first[i + 1].type == CPP_OPEN_PAREN
			   && first[i + 2].type == CPP_NAME
			   && !strcmp (IDENTIFIER_POINTER (first[i].ମୂଲ୍ୟ),
				       "at")
			   && !strcmp (IDENTIFIER_POINTER (first[i
								 + 2].ମୂଲ୍ୟ),
				       "execution"))
		    {
		      kind = C_OMP_DIR_STANDALONE;
		      ଭାଙ୍ଗ;
		    }
	      }
	    c_omp_attribute_data v = { toks, dir, kind };
	    vd.safe_ଠେଲ (v);
	    ଯଦି (flag_openmp || dir->simd)
	      tokens += (last - first) + 1;
	  }
	c_omp_attribute_data v = {};
	vd.safe_ଠେଲ (v);
	*pa = ବୃକ୍ଷ_CHAIN (*pa);
      }
    ଅନ୍ୟଥା
      pa = &ବୃକ୍ଷ_CHAIN (*pa);

  ଯଦି (bad)
    {
    fail:
      ଯଦି (have_std_attrs && attrs == ଖାଲି)
	*have_std_attrs = ମିଥ୍ୟା;
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
  c_omp_attribute_data *v;
  c_omp_attribute_data *construct_seen = nullptr;
  c_omp_attribute_data *standalone_seen = nullptr;
  c_omp_attribute_data *prev_standalone_seen = nullptr;
  FOR_EACH_VEC_ELT (vd, i, v)
    ଯଦି (v->tokens)
      {
	ଯଦି (v->kind == C_OMP_DIR_CONSTRUCT && !construct_seen)
	  construct_seen = v;
	ଅନ୍ୟଥା ଯଦି (v->kind == C_OMP_DIR_STANDALONE && !standalone_seen)
	  standalone_seen = v;
      }
    ଅନ୍ୟଥା
      {
	ଯଦି (standalone_seen && !prev_standalone_seen)
	  {
	    prev_standalone_seen = standalone_seen;
	    standalone_seen = nullptr;
	  }
      }

  ଯଦି (cnt > 1 && construct_seen)
    {
      error_at ((*construct_seen->tokens)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      ଯାଅ fail;
    }
  ଯଦି (cnt > 1 && standalone_seen && prev_standalone_seen)
    {
      error_at ((*standalone_seen->tokens)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      ଯାଅ fail;
    }

  ଯଦି (prev_standalone_seen)
    standalone_seen = prev_standalone_seen;
  ଯଦି (standalone_seen
      && !c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_seen->tokens->address ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      ଯାଅ fail;
    }
  ଯଦି (cnt && c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      ଗଣନା pragma_kind kind = token->pragma_kind;
      ଯଦି (kind >= PRAGMA_OMP__START_ && kind <= PRAGMA_OMP__LAST_)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  ଯାଅ fail;
	}
    }

  ଯଦି (!tokens)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା tokens_avail = parser->tokens_avail;

  tokens++;
  vec<c_token, va_gc> *toks = ଖାଲି;
  vec_safe_reserve (toks, tokens, ସତ୍ୟ);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      ଯଦି (!v->tokens)
	ଜାରି;
      ଯଦି (!flag_openmp && !v->dir->simd)
	ଜାରି;
      c_token *first = v->tokens->address ();
      c_token *last = first + v->tokens->length ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_kind = pragma_kind (v->dir->id);
      tok.location = first->location;
      toks->quick_ଠେଲ (tok);
      ଯେତେବେଳେ (++first < last)
	toks->quick_ଠେଲ (*first);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = last[-1].location;
      toks->quick_ଠେଲ (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->last ().location;
  toks->quick_ଠେଲ (tok);

  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = tokens;
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_handle_directive_omp_attributes (ବୃକ୍ଷ &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  ଯଦି (!flag_openmp && !flag_openmp_simd)
    ଫେରନ୍ତୁ;

  ପାଇଁ (ବୃକ୍ଷ *pa = &attrs; *pa; )
    ଯଦି (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା cnt = 0;
	ପାଇଁ (ବୃକ୍ଷ *pa2 = &ବୃକ୍ଷ_ମୂଲ୍ୟ (*pa); *pa2; )
	  {
	    ବୃକ୍ଷ a = *pa2;
	    ବୃକ୍ଷ d = ବୃକ୍ଷ_ମୂଲ୍ୟ (a);
	    gcc_assert (ବୃକ୍ଷ_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    ଅଚଳ ଅକ୍ଷର *directive[3] = {};
	    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 3; i++)
	      {
		ବୃକ୍ଷ id = NULL_ବୃକ୍ଷ;
		ଯଦି (first + i == last)
		  ଭାଙ୍ଗ;
		ଯଦି (first[i].type == CPP_NAME)
		  id = first[i].ମୂଲ୍ୟ;
		ଅନ୍ୟଥା ଯଦି (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(ପୂର୍ଣ୍ଣସଂଖ୍ୟା) first[i].keyword];
		ଅନ୍ୟଥା
		  ଭାଙ୍ଗ;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    ଅଚଳ c_omp_directive *dir = ଖାଲି;
	    ଯଦି (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    ଯଦି (dir == ଖାଲି)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  ବୃକ୍ଷ_PUBLIC (d) ? "omp::decl" : "omp::directive");
		*pa2 = ବୃକ୍ଷ_CHAIN (a);
	      }
	    ଅନ୍ୟଥା ଯଦି (dir->id == PRAGMA_OMP_DECLARE
		     && (strcmp (directive[1], "simd") == 0
			 || strcmp (directive[1], "variant") == 0))
	      {
		ଯଦି (pragma_clauses)
		  {
		    error_at (first->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    ପାଇଁ (pa = &attrs; *pa; )
		      ଯଦି (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = ବୃକ୍ଷ_CHAIN (*pa);
		      ଅନ୍ୟଥା
			pa = &ବୃକ୍ଷ_CHAIN (*pa);
		    ଫେରନ୍ତୁ;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->length ()
				       + toks->length () + 2);
		ପାଇଁ (++first; first < last; ++first)
		  attr_clauses->quick_ଠେଲ (*first);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = last[-1].location;
		attr_clauses->quick_ଠେଲ (tok);
		*pa2 = ବୃକ୍ଷ_CHAIN (a);
	      }
	    ଅନ୍ୟଥା
	      pa2 = &ବୃକ୍ଷ_CHAIN (a);
	  }
	ଯଦି (cnt && ବୃକ୍ଷ_ମୂଲ୍ୟ (*pa) == NULL_ବୃକ୍ଷ)
	  *pa = ବୃକ୍ଷ_CHAIN (*pa);
	ଅନ୍ୟଥା
	  pa = &ବୃକ୍ଷ_CHAIN (*pa);
      }
    ଅନ୍ୟଥା
      pa = &ବୃକ୍ଷ_CHAIN (*pa);
  ଯଦି (attr_clauses->length ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->last ().location;
      attr_clauses->quick_ଠେଲ (tok);
      attr_clauses->quick_ଠେଲ (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_handle_musttail (c_parser *parser, ବୃକ୍ଷ std_attrs, attr_state &attr)
{
  ଯଦି (c_parser_next_token_is_keyword (parser, RID_RETURN))
    {
      ଯଦି (ବୃକ୍ଷ a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  ପାଇଁ (; a; a = lookup_attribute ("gnu", "musttail", ବୃକ୍ଷ_CHAIN (a)))
	    ଯଦି (ବୃକ୍ଷ_ମୂଲ୍ୟ (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = ସତ୍ୟ;
	}
      ଯଦି (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = ସତ୍ୟ;
	}
    }
  ଫେରନ୍ତୁ std_attrs;
}

/* Return a statement before optional series of LABEL_EXPR/CASE_LABEL_EXPRs.
   Instead of collecting vectors of labels before each stmt just in case
   the statement would be iteration or switch statement for named loops,
   we just remember last emitted statement and let the iteration/switch
   statement search backwards in cur_stmt_list until that stmt for loop
   names if any.  */

ସ୍ଥିର ବୃକ୍ଷ
get_before_labels ()
{
  ଯଦି (!building_stmt_list_p ())
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ_stmt_iterator tsi = tsi_last (cur_stmt_list);
  ଯଦି (tsi_end_p (tsi))
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  ଫେରନ୍ତୁ tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

ସ୍ଥିର location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  ତାର୍କିକ last_stmt = ମିଥ୍ୟା;
  ତାର୍କିକ last_label = ମିଥ୍ୟା;
  ତାର୍କିକ save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  ସଂରଚନା omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  ତାର୍କିକ in_omp_loop_block
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : ମିଥ୍ୟା;
  ବୃକ୍ଷ sl = NULL_ବୃକ୍ଷ;
  attr_state astate = {};

  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      add_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      ଫେରନ୍ତୁ endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  ଯଦି (in_omp_loop_block)
    sl = ଠେଲ_stmt_list ();

  mark_valid_location_for_stdc_pragma (ସତ୍ୟ);
  ଯଦି (c_parser_next_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (ମିଥ୍ୟା);
      ଯଦି (in_omp_loop_block)
	check_omp_intervening_code (parser);
      ଯେତେବେଳେ (c_parser_next_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  ଯେତେବେଳେ (ସତ୍ୟ)
	    {
	      ବୃକ୍ଷ label;
	      ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  ଭାଙ୍ଗ;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      add_stmt (build_stmt (label_loc, DECL_ପଦସମଷ୍ଟି, label));
	      c_parser_consume_token (parser);
	      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      ଅନ୍ୟଥା
		ଭାଙ୍ଗ;
	    }
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ଫେରନ୍ତୁ endloc;
    }
  ବୃକ୍ଷ before_labels = get_before_labels ();
  ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_point_location_if_in_system_header (loc);

      ତାର୍କିକ want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : ମିଥ୍ୟା);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      ଯଦି (in_omp_loop_block && !last_label)
	{
	  ବୃକ୍ଷ_code code = omp_for_parse_state->code;
	  ଯଦି (want_nested_loop
	      && c_parser_omp_next_tokens_can_be_canon_loop (parser, code,
							     ମିଥ୍ୟା))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      add_structured_block_stmt (କାଢ଼_stmt_list (sl));
	      omp_for_parse_state->depth++;
	      add_stmt (c_parser_omp_loop_nest (parser, ଖାଲି));
	      omp_for_parse_state->depth--;
	      sl = ଠେଲ_stmt_list ();
	      parser->error = ମିଥ୍ୟା;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ଜାରି;
	    }
	  ଅନ୍ୟଥା ଯଦି (want_nested_loop
		   && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      ବୃକ୍ଷ pre_sl = କାଢ଼_stmt_list (sl);
	      ବୃକ୍ଷ nested_sl = ଠେଲ_stmt_list ();
	      mark_valid_location_for_stdc_pragma (ମିଥ୍ୟା);
	      c_parser_statement_after_labels (parser, ଖାଲି, NULL_ବୃକ୍ଷ);
	      nested_sl = କାଢ଼_stmt_list (nested_sl);
	      ଯଦି (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_code (parser);
		  sl = ଠେଲ_stmt_list ();
		  add_stmt (pre_sl);
		  add_stmt (nested_sl);
		}
	      ଅନ୍ୟଥା
		{
		  /* It contains the nested loop.  */
		  add_structured_block_stmt (pre_sl);
		  add_stmt (nested_sl);
		  sl = ଠେଲ_stmt_list ();
		}
	      parser->error = ମିଥ୍ୟା;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ଜାରି;
	    }
	  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      /* Prior to implementing the OpenMP 5.1 syntax for canonical
		 loop form, GCC used to accept an empty statements that
		 would now be flagged as intervening code.  Continue to
		 do that, as an extension.  */
	      /* FIXME:  Maybe issue a warning or something here?  */
	      c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ଜାରି;
	    }
	}

      /* Standard attributes may start a label, statement or declaration.  */
      ତାର୍କିକ have_std_attrs
	= c_parser_nth_token_starts_std_attributes (parser, 1);
      ବୃକ୍ଷ std_attrs = NULL_ବୃକ୍ଷ;
      ଯଦି (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      ଯଦି (c_parser_next_token_is_keyword (parser, RID_CASE)
	  || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  ଯଦି (c_parser_next_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  ଅନ୍ୟଥା
	    label_loc = c_parser_peek_token (parser)->location;
	  last_label = ସତ୍ୟ;
	  last_stmt = ମିଥ୍ୟା;
	  mark_valid_location_for_stdc_pragma (ମିଥ୍ୟା);
	  ଯଦି (in_omp_loop_block)
	    check_omp_intervening_code (parser);
	  c_parser_label (parser, std_attrs);
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_tokens_start_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_attributes
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_next_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = ସତ୍ୟ)))
	{
	  ଯଦି (last_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  ଯଦି (in_omp_loop_block)
	    {
	      check_omp_intervening_code (parser);
	      omp_for_parse_state->want_nested_loop = ମିଥ୍ୟା;
	    }
	  mark_valid_location_for_stdc_pragma (ମିଥ୍ୟା);
	  ତାର୍କିକ fallthru_attr_p = ମିଥ୍ୟା;
	  c_parser_declaration_or_fndef (parser, ସତ୍ୟ, !have_std_attrs,
					 ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ମିଥ୍ୟା, ଖାଲି,
					 ଖାଲି, have_std_attrs, std_attrs,
					 ଖାଲି, &fallthru_attr_p);

	  ଯଦି (in_omp_loop_block)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  ଯଦି (last_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  last_stmt = fallthru_attr_p;
	  last_label = ମିଥ୍ୟା;
	  before_labels = get_before_labels ();
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  If standard attributes have already
	     been seen, it must start a statement, not a declaration,
	     but standard attributes starting a declaration may appear
	     after __extension__.  */
	  ଯେତେବେଳେ (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  ଯଦି (!have_std_attrs
	      && (c_parser_next_tokens_start_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_attributes (parser, 2)))
	    {
	      ପୂର୍ଣ୍ଣସଂଖ୍ୟା ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      last_label = ମିଥ୍ୟା;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      ଯଦି (in_omp_loop_block)
		{
		  check_omp_intervening_code (parser);
		  omp_for_parse_state->want_nested_loop = ମିଥ୍ୟା;
		}
	      mark_valid_location_for_stdc_pragma (ମିଥ୍ୟା);
	      c_parser_declaration_or_fndef (parser, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ,
					     ସତ୍ୟ, ମିଥ୍ୟା);
	      ଯଦି (in_omp_loop_block)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      ଯଦି (last_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      last_stmt = ମିଥ୍ୟା;
	      before_labels = get_before_labels ();
	    }
	  ଅନ୍ୟଥା
	    ଯାଅ statement;
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  ଯଦି (have_std_attrs && !parser->in_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  ଅନ୍ୟଥା ଯଦି (std_attrs)
	    c_warn_unused_attributes (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  ଯଦି (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = ମିଥ୍ୟା;
	  ଯଦି (c_parser_pragma (parser,
			       last_label ? pragma_stmt : pragma_compound,
			       ଖାଲି, before_labels))
	    {
	      last_label = ମିଥ୍ୟା;
	      last_stmt = ସତ୍ୟ;
	      ଯଦି (omp_for_parse_state)
		check_omp_intervening_code (parser);
	    }
	  ଯଦି (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  ଫେରନ୍ତୁ c_parser_peek_token (parser)->location;
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_ELSE))
        {
          ଯଦି (parser->in_if_block)
            {
	      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	      error_at (loc, "expected %<}%> before %<else%>");
	      ଫେରନ୍ତୁ c_parser_peek_token (parser)->location;
            }
          ଅନ୍ୟଥା
            {
              error_at (loc, "%<else%> without a previous %<if%>");
              c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
              ଜାରି;
            }
        }
      ଅନ୍ୟଥା
	{
	statement:
	  c_warn_unused_attributes (std_attrs);
	  last_label = ମିଥ୍ୟା;
	  last_stmt = ସତ୍ୟ;
	  mark_valid_location_for_stdc_pragma (ମିଥ୍ୟା);
	  ଯଦି (!omp_for_parse_state)
	    c_parser_statement_after_labels (parser, ଖାଲି, before_labels,
					     ଖାଲି, astate);
	  ଅନ୍ୟଥା
	    {
	      /* In canonical loop nest form, nested loops can only appear
		 directly, or in a directly nested compound statement.  We
		 already took care of those cases above, so now we have
		 something else.  This statement and everything inside
		 it must be intervening code.  */
	      omp_for_parse_state->want_nested_loop = ମିଥ୍ୟା;
	      check_omp_intervening_code (parser);
	      c_parser_statement_after_labels (parser, ଖାଲି, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = ମିଥ୍ୟା;
      astate.reset ();
    }
  ଯଦି (last_label)
    pedwarn_c11 (label_loc, OPT_Wfree_labels,
		 "label at end of compound statement");
  location_t endloc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  /* Restore the value we started with.  */
  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);

  /* Package leftover intervening code, or the whole contents of the
     compound statement if we were looking for a nested loop in an OMP_FOR
     construct and didn't find one.  */
  ଯଦି (sl)
    {
      sl = କାଢ଼_stmt_list (sl);
      ଯଦି (omp_for_parse_state->want_nested_loop)
	add_stmt (sl);
      ଅନ୍ୟଥା
	add_structured_block_stmt (sl);
    }
  ଫେରନ୍ତୁ endloc;
}

/* Parse all consecutive labels, possibly preceded by standard
   attributes.  In this context, a statement is required, not a
   declaration, so attributes must be followed by a statement that is
   not just a semicolon.  Returns an attr_state.  */

ସ୍ଥିର attr_state
c_parser_all_labels (c_parser *parser)
{
  attr_state attr = {};
  ତାର୍କିକ have_std_attrs;
  ବୃକ୍ଷ std_attrs = ଖାଲି;
  ଯଦି ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  ଯେତେବେଳେ (c_parser_next_token_is_keyword (parser, RID_CASE)
	 || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = ଖାଲି;
      ଯଦି ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  ଯଦି (std_attrs
      && (!c_parser_handle_statement_omp_attributes (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      ଯଦି (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_unused_attributes (std_attrs);
    }
  ଅନ୍ୟଥା ଯଦି (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  ଫେରନ୍ତୁ attr;
}


/* Information used while parsing an OpenMP metadirective.  */
ସଂରଚନା omp_metadirective_parse_data {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<ବୃକ୍ଷ> * GTY((skip)) body_labels;
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା region_ଅଙ୍କ;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
ସ୍ଥିର ବୃକ୍ଷ
mangle_metadirective_region_label (c_parser *parser, ବୃକ୍ଷ name)
{
  ଯଦି (parser->omp_metadirective_state->body_labels->contains (name))
    {
      ଅଚଳ ଅକ୍ଷର *old_name = IDENTIFIER_POINTER (name);
      ଅକ୍ଷର *new_name = (ଅକ୍ଷର *) XALLOCAVEC (ଅକ୍ଷର, strlen (old_name) + 32);
      sprintf (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_ଅଙ୍କ);
      ଫେରନ୍ତୁ get_identifier (new_name);
    }
  ଫେରନ୍ତୁ name;
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
ସ୍ଥିର ଶୂନ୍ୟ
c_parser_label (c_parser *parser, ବୃକ୍ଷ std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ label = NULL_ବୃକ୍ଷ;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  ତାର୍କିକ fallthrough_p = c_parser_peek_token (parser)->flags & PREV_FALLTHROUGH;

  ଯଦି (c_parser_next_token_is_keyword (parser, RID_CASE))
    {
      ବୃକ୍ଷ exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_to_rvalue (loc1,
				       c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି),
				       ସତ୍ୟ, ସତ୍ୟ).ମୂଲ୍ୟ;
      ଯଦି (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_ବୃକ୍ଷ, std_attrs);
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_to_rvalue (loc1,
					   c_parser_ପଦସମଷ୍ଟି_no_commas (parser,
								    ଖାଲି),
					   ସତ୍ୟ, ସତ୍ୟ).ମୂଲ୍ୟ;
	  ଯଦି (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      ଅନ୍ୟଥା
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      ଯଦି (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ, std_attrs);
    }
  ଅନ୍ୟଥା
    {
      ବୃକ୍ଷ name = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      ବୃକ୍ଷ tlab;
      ବୃକ୍ଷ attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_attributes (parser);
      ଯଦି (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      ଯଦି (tlab)
	{
	  decl_attributes (&tlab, attrs, 0);
	  decl_attributes (&tlab, std_attrs, 0);
	  label = add_stmt (build_stmt (loc1, LABEL_ପଦସମଷ୍ଟି, tlab));
	}
      ଯଦି (attrs
	  && c_parser_next_tokens_start_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  ଯଦି (label)
    {
      ଯଦି (ବୃକ୍ଷ_CODE (label) == LABEL_ପଦସମଷ୍ଟି)
	FALLTHROUGH_LABEL_P (LABEL_ପଦସମଷ୍ଟି_LABEL (label)) = fallthrough_p;
      ଅନ୍ୟଥା
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_statement (c_parser *parser, ତାର୍କିକ *if_p, location_t *loc_after_labels)
{
  ବୃକ୍ଷ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  ଯଦି (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = ମିଥ୍ୟା;
  c_parser_statement_after_labels (parser, if_p, before_labels, ଖାଲି, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_bc_name (c_parser *parser, ତାର୍କିକ is_break)
{
  ଯଦି (!c_parser_next_token_is (parser, CPP_NAME))
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;

  c_token *tok = c_parser_peek_token (parser);
  ବୃକ୍ଷ label = c_finish_bc_name (tok->location, tok->ମୂଲ୍ୟ, is_break);
  c_parser_consume_token (parser);
  ଫେରନ୍ତୁ label;
}

/* Parse a statement, other than a labeled statement.  CHAIN is a vector
   of if-else-if conditions.  All labels and standard attributes have
   been parsed in the caller.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  ASTATE is an earlier parsed attribute state.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_statement_after_labels (c_parser *parser, ତାର୍କିକ *if_p,
				 ବୃକ୍ଷ before_labels,
				 vec<ବୃକ୍ଷ> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ stmt = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ in_if_block = parser->in_if_block;
  parser->in_if_block = ମିଥ୍ୟା;
  ଯଦି (if_p != ଖାଲି)
    *if_p = ମିଥ୍ୟା;

  ଯଦି (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    add_debug_begin_stmt (loc);

 restart:
  ବାଛ (c_parser_peek_token (parser)->type)
    {
    ସ୍ଥିତି CPP_OPEN_BRACE:
      add_stmt (c_parser_compound_statement (parser));
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_KEYWORD:
      ବାଛ (c_parser_peek_token (parser)->keyword)
	{
	ସ୍ଥିତି RID_IF:
	  c_parser_if_statement (parser, if_p, chain);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_SWITCH:
	  c_parser_switch_statement (parser, if_p, before_labels);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_WHILE:
	  c_parser_while_statement (parser, ମିଥ୍ୟା, 0, ମିଥ୍ୟା, if_p, before_labels);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_DO:
	  c_parser_do_statement (parser, ମିଥ୍ୟା, 0, ମିଥ୍ୟା, before_labels);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_FOR:
	  c_parser_for_statement (parser, ମିଥ୍ୟା, 0, ମିଥ୍ୟା, if_p, before_labels);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_GOTO:
	  c_parser_consume_token (parser);
	  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      ବୃକ୍ଷ name = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	      ଯଦି (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_finish_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_MULT))
	    {
	      ସଂରଚନା c_ପଦସମଷ୍ଟି val;

	      c_parser_consume_token (parser);
	      val = c_parser_expression (parser);
	      val = convert_lvalue_to_rvalue (loc, val, ମିଥ୍ୟା, ସତ୍ୟ);
	      stmt = c_finish_goto_ptr (loc, val);
	    }
	  ଅନ୍ୟଥା
	    c_parser_error (parser, "expected identifier or %<*%>");
	  ଯାଅ expect_semicolon;
	ସ୍ଥିତି RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_continue_label, ମିଥ୍ୟା,
				   c_parser_bc_name (parser, ମିଥ୍ୟା));
	  ଯାଅ expect_semicolon;
	ସ୍ଥିତି RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_break_label, ସତ୍ୟ,
				   c_parser_bc_name (parser, ସତ୍ୟ));
	  ଯାଅ expect_semicolon;
	ସ୍ଥିତି RID_RETURN:
	  c_parser_consume_token (parser);
	  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_finish_return (loc, NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  ଅନ୍ୟଥା
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_expression_conv (parser);
	      mark_exp_read (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	      stmt = c_finish_return (ପଦସମଷ୍ଟି_LOC_OR_LOC (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, xloc),
				      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ପଦସମଷ୍ଟି.original_type,
				      astate.musttail_p);
	      ଯାଅ expect_semicolon;
	    }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_TRANSACTION_ATOMIC:
	ସ୍ଥିତି RID_TRANSACTION_RELAXED:
	  stmt = c_parser_transaction (parser,
	      c_parser_peek_token (parser)->keyword);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_TRANSACTION_CANCEL:
	  stmt = c_parser_transaction_cancel (parser);
	  ଯାଅ expect_semicolon;
	ସ୍ଥିତି RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_ବୃକ୍ଷ);
	      c_parser_consume_token (parser);
	    }
	  ଅନ୍ୟଥା
	    {
	      ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_expression (parser);
	      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ମିଥ୍ୟା);
	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
	      stmt = objc_build_throw_stmt (loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	      ଯାଅ expect_semicolon;
	    }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_finally_statement (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_ATTRIBUTE:
	  {
	    /* Allow '__attribute__((fallthrough));' or
	       '__attribute__((assume(cond)));' or
	       '__attribute__((musttail))) return'.  */
	    ବୃକ୍ଷ attrs = c_parser_gnu_attributes (parser);
	    ତାର୍କିକ has_assume = lookup_attribute ("assume", attrs);
	    ଯଦି (has_assume)
	      {
		ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, ସତ୍ୟ);
		ଅନ୍ୟଥା
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<assume%> attribute not followed by %<;%>");
		    has_assume = ମିଥ୍ୟା;
		  }
	      }
	    gcc_assert (!astate.musttail_p);
	    attrs = c_parser_handle_musttail (parser, attrs, astate);
	    ଯଦି (astate.musttail_p)
	      {
		ଯଦି (attrs)
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		ଯାଅ restart;
	      }
	    ଯଦି (attribute_fallthrough_p (attrs))
	      {
		ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  {
		    ବୃକ୍ଷ fn = build_call_ପଦସମଷ୍ଟି_internal_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_ଗଣ୍ଠି, 0);
		    add_stmt (fn);
		    /* Eat the ';'.  */
		    c_parser_consume_token (parser);
		  }
		ଅନ୍ୟଥା
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<fallthrough%> attribute not followed "
				"by %<;%>");
		  }
	      }
	    ଅନ୍ୟଥା ଯଦି (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    ଅନ୍ୟଥା ଯଦି (attrs != NULL_ବୃକ୍ଷ)
	      {
		auto_urlify_attributes sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    ଭାଙ୍ଗ;
	  }
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଯାଅ ପଦସମଷ୍ଟି_stmt;
	}
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_SEMICOLON:
      c_parser_consume_token (parser);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_CLOSE_PAREN:
    ସ୍ଥିତି CPP_CLOSE_SQUARE:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_PRAGMA:
      ଯଦି (!c_parser_pragma (parser, pragma_stmt, if_p, before_labels))
        ଯାଅ restart;
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
    ପଦସମଷ୍ଟି_stmt:
      stmt = c_finish_ପଦସମଷ୍ଟି_stmt (loc, c_parser_expression_conv (parser).ମୂଲ୍ୟ);
    expect_semicolon:
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      ଭାଙ୍ଗ;
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
  ଯଦି (ପଦସମଷ୍ଟି_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_set_ପଦସମଷ୍ଟି_location (stmt, loc);

  parser->in_if_block = in_if_block;
}

/* Parse the condition from an if, do, while or for statements.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ cond;
  cond = c_parser_expression_conv (parser).ମୂଲ୍ୟ;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, ମିଥ୍ୟା, ଖାଲି);
  ଯଦି (warn_sequence_point)
    verify_sequence_points (cond);
  ଫେରନ୍ତୁ cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_paren_condition (c_parser *parser)
{
  ବୃକ୍ଷ cond;
  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
  cond = c_parser_condition (parser);
  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ cond;
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

ସ୍ଥିର c_ପଦସମଷ୍ଟି
c_parser_selection_header (c_parser *parser, ତାର୍କିକ switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
  ତାର୍କିକ parse_ପଦସମଷ୍ଟି = ସତ୍ୟ;
  ବୃକ୍ଷ std_attrs;
  ତାର୍କିକ have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  ଯଦି (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  ଅନ୍ୟଥା
    std_attrs = NULL_ବୃକ୍ଷ;
  ଯଦି (c_parser_next_tokens_start_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/ମିଥ୍ୟା,
					 /*static_assert_ok=*/ମିଥ୍ୟା,
					 /*empty_ok=*/ମିଥ୍ୟା,
					 /*nested=*/ସତ୍ୟ,
					 /*start_attr_ok=*/ସତ୍ୟ,
					 /*simple_ok=*/ସତ୍ୟ,
					 /*objc_foreach_object_decl=*/nullptr,
					 /*omp_declare_simd_clauses=*/nullptr,
					 have_std_attrs,
					 std_attrs);
      ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      ଅନ୍ୟଥା
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  ଯଦି (!ପଦସମଷ୍ଟି.ମୂଲ୍ୟ)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      ପଦସମଷ୍ଟି.original_type = error_mark_ଗଣ୍ଠି;
	      ପଦସମଷ୍ଟି.set_error ();
	      ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
	    }
	  parse_ପଦସମଷ୍ଟି = ମିଥ୍ୟା;
	}
      ଯଦି (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ)
	{
	  ପଦସମଷ୍ଟି.original_type = ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (loc, ପଦସମଷ୍ଟି, /*convert_p=*/ସତ୍ୟ,
					   /*read_p=*/ସତ୍ୟ);
	}
    }
  ଅନ୍ୟଥା ଯଦି (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      ପଦସମଷ୍ଟି.original_type = error_mark_ଗଣ୍ଠି;
      ପଦସମଷ୍ଟି.set_error ();
      ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
    }

  ଯଦି (parse_ପଦସମଷ୍ଟି)
    ପଦସମଷ୍ଟି = c_parser_expression_conv (parser);
  ଯଦି (!switch_p)
    {
      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_objc_common_truthvalue_conversion (loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
      ଯଦି (warn_sequence_point)
	verify_sequence_points (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
    }
  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_paren_selection_header (c_parser *parser)
{
  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
  ବୃକ୍ଷ cond = c_parser_selection_header (parser, /*switch_p=*/ମିଥ୍ୟା).ମୂଲ୍ୟ;
  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_c99_block_statement (c_parser *parser, ତାର୍କିକ *if_p,
			      location_t *loc_after_labels)
{
  ବୃକ୍ଷ block = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  ଫେରନ୍ତୁ c_end_compound_stmt (loc, block, flag_isoc99);
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_if_body (c_parser *parser, ତାର୍କିକ *if_p,
		  ଅଚଳ token_indent_info &if_tinfo)
{
  ବୃକ୍ଷ block = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  ବୃକ୍ଷ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
      ଯଦି (!c_parser_next_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    add_stmt (c_parser_compound_statement (parser));
  ଅନ୍ୟଥା
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, ଖାଲି, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, next_tinfo);
  ଯଦି (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    if_tinfo.location, RID_IF);

  ଫେରନ୍ତୁ c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_else_body (c_parser *parser, ଅଚଳ token_indent_info &else_tinfo,
		    vec<ବୃକ୍ଷ> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ block = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  ବୃକ୍ଷ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      warning_at (loc,
		  OPT_Wempty_body,
	         "suggest braces around empty body in an %<else%> statement");
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
    }
  ଅନ୍ୟଥା
    {
      ଯଦି (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, ଖାଲି, before_labels, chain, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, next_tinfo);
  ଯଦି (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  ଫେରନ୍ତୁ c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse an if statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   if-statement:
     if ( selection-header ) statement
     if ( selection-header ) statement else statement

   CHAIN is a vector of if-else-if conditions.
   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_if_statement (c_parser *parser, ତାର୍କିକ *if_p, vec<ବୃକ୍ଷ> *chain)
{
  ବୃକ୍ଷ block;
  location_t loc;
  ବୃକ୍ଷ cond;
  ତାର୍କିକ nested_if = ମିଥ୍ୟା;
  ବୃକ୍ଷ first_body, second_body;
  ତାର୍କିକ in_if_block;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_IF));
  token_indent_info if_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_selection_header (parser);
  in_if_block = parser->in_if_block;
  parser->in_if_block = ସତ୍ୟ;
  first_body = c_parser_if_body (parser, &nested_if, if_tinfo);
  parser->in_if_block = in_if_block;

  ଯଦି (warn_duplicated_cond)
    warn_duplicated_cond_add_or_warn (ପଦସମଷ୍ଟି_LOCATION (cond), cond, &chain);

  ଯଦି (c_parser_next_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      ଯଦି (warn_duplicated_cond)
	{
	  ଯଦି (c_parser_next_token_is_keyword (parser, RID_IF)
	      && chain == ଖାଲି)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = ନୂତନ vec<ବୃକ୍ଷ> ();
	      ଯଦି (!CONSTANT_CLASS_P (cond) && !ବୃକ୍ଷ_SIDE_EFFECTS (cond))
		chain->safe_ଠେଲ (cond);
	    }
	  ଅନ୍ୟଥା ଯଦି (!c_parser_next_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      second_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      ଯଦି (if_p != ଖାଲି)
	*if_p = ସତ୍ୟ;
    }
  ଅନ୍ୟଥା
    {
      second_body = NULL_ବୃକ୍ଷ;

      /* Diagnose an ambiguous else if if-then-else is nested inside
	 if-then.  */
      ଯଦି (nested_if)
	warning_at (loc, OPT_Wdangling_else,
		    "suggest explicit braces to avoid ambiguous %<else%>");

      ଯଦି (warn_duplicated_cond)
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_switch_statement (c_parser *parser, ତାର୍କିକ *if_p, ବୃକ୍ଷ before_labels)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ce;
  ବୃକ୍ଷ block, ପଦସମଷ୍ଟି, body;
  unsigned ଅକ୍ଷର save_in_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  ବୃକ୍ଷ switch_name;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_names = c_get_loop_names (before_labels, ସତ୍ୟ, &switch_name);
  block = c_begin_compound_stmt (flag_isoc99);
  ତାର୍କିକ explicit_cast_p = ମିଥ୍ୟା;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = ସତ୍ୟ;
      ce = c_parser_selection_header (parser, /*switch_p=*/ସତ୍ୟ);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_to_rvalue (switch_cond_loc, ce, ସତ୍ୟ, ସତ୍ୟ);
      ପଦସମଷ୍ଟି = ce.ମୂଲ୍ୟ;
      /* ??? expr has no valid location?  */
      parens.skip_until_found_close (parser);
    }
  ଅନ୍ୟଥା
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      ପଦସମଷ୍ଟି = error_mark_ଗଣ୍ଠି;
      ce.original_type = error_mark_ଗଣ୍ଠି;
    }
  ବୃକ୍ଷ stmt
    = c_start_switch (switch_loc, switch_cond_loc, ପଦସମଷ୍ଟି, explicit_cast_p,
		      switch_name);
  save_in_statement = in_statement;
  in_statement |= IN_SWITCH_STMT;
  ଯଦି (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  ଅନ୍ୟଥା
    in_statement &= ~IN_NAMED_STMT;
  location_t loc_after_labels;
  ତାର୍କିକ open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  location_t next_loc = c_parser_peek_token (parser)->location;
  ଯଦି (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, next_loc, switch_loc,
				    RID_SWITCH);
  c_finish_switch (body, ce.original_type);
  in_statement = save_in_statement;
  ଯଦି (ଅଙ୍କ_names)
    {
      ଯଦି (!C_DECL_LOOP_SWITCH_NAME_USED (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_ବୃକ୍ଷ;
      ଅନ୍ୟଥା
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_names (ଅଙ୍କ_names);
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_while_statement (c_parser *parser, ତାର୍କିକ ivdep, unsigned short unroll,
			  ତାର୍କିକ novector, ତାର୍କିକ *if_p, ବୃକ୍ଷ before_labels)
{
  ବୃକ୍ଷ block, cond, body;
  unsigned ଅକ୍ଷର save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  ବୃକ୍ଷ loop_name;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_names = c_get_loop_names (before_labels, ମିଥ୍ୟା, &loop_name);

  ଯଦି (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = ସତ୍ୟ;
    }

  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  ଯଦି (ivdep && cond != error_mark_ଗଣ୍ଠି)
    cond = build3 (ANNOTATE_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (cond), cond,
		   build_int_cst (integer_type_ଗଣ୍ଠି,
				  annot_ପଦସମଷ୍ଟି_ivdep_kind),
		   integer_zero_ଗଣ୍ଠି);
  ଯଦି (unroll && cond != error_mark_ଗଣ୍ଠି)
    cond = build3 (ANNOTATE_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (cond), cond,
		   build_int_cst (integer_type_ଗଣ୍ଠି,
				  annot_ପଦସମଷ୍ଟି_unroll_kind),
		   build_int_cst (integer_type_ଗଣ୍ଠି, unroll));
  ଯଦି (novector && cond != error_mark_ଗଣ୍ଠି)
    cond = build3 (ANNOTATE_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (cond), cond,
		   build_int_cst (integer_type_ଗଣ୍ଠି,
				  annot_ପଦସମଷ୍ଟି_no_vector_kind),
		   integer_zero_ଗଣ୍ଠି);
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  ଯଦି (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  ତାର୍କିକ open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  ଯଦି (loop_name && !C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
    loop_name = NULL_ବୃକ୍ଷ;
  add_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_ବୃକ୍ଷ,
			NULL_ବୃକ୍ଷ));
  add_stmt (c_end_compound_stmt (loc, block, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  ଯଦି (ଅଙ୍କ_names)
    c_release_loop_names (ଅଙ୍କ_names);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, next_tinfo);

  ଯଦି (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    while_tinfo.location, RID_WHILE);

  in_statement = save_in_statement;
}

/* Parse a do statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   do-statement:
     do statement while ( expression ) ;

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_do_statement (c_parser *parser, ତାର୍କିକ ivdep, unsigned short unroll,
		       ତାର୍କିକ novector, ବୃକ୍ଷ before_labels)
{
  ବୃକ୍ଷ block, cond, body;
  unsigned ଅକ୍ଷର save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_DO));
  ବୃକ୍ଷ loop_name;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_names = c_get_loop_names (before_labels, ମିଥ୍ୟା, &loop_name);

  ଯଦି (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = ସତ୍ୟ;
    }

  c_parser_consume_token (parser);
  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  ଯଦି (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  body = c_parser_c99_block_statement (parser, ଖାଲି);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  in_statement = save_in_statement;
  ଯଦି (ଅଙ୍କ_names)
    {
      ଯଦି (!C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
	loop_name = NULL_ବୃକ୍ଷ;
      c_release_loop_names (ଅଙ୍କ_names);
    }
  cond = c_parser_paren_condition (parser);
  ଯଦି (ivdep && cond != error_mark_ଗଣ୍ଠି)
    cond = build3 (ANNOTATE_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (cond), cond,
		   build_int_cst (integer_type_ଗଣ୍ଠି,
				  annot_ପଦସମଷ୍ଟି_ivdep_kind),
		   integer_zero_ଗଣ୍ଠି);
  ଯଦି (unroll && cond != error_mark_ଗଣ୍ଠି)
    cond = build3 (ANNOTATE_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (cond), cond,
		   build_int_cst (integer_type_ଗଣ୍ଠି,
				  annot_ପଦସମଷ୍ଟି_unroll_kind),
 		   build_int_cst (integer_type_ଗଣ୍ଠି, unroll));
  ଯଦି (novector && cond != error_mark_ଗଣ୍ଠି)
    cond = build3 (ANNOTATE_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (cond), cond,
		   build_int_cst (integer_type_ଗଣ୍ଠି,
				  annot_ପଦସମଷ୍ଟି_no_vector_kind),
		   integer_zero_ଗଣ୍ଠି);
  ଯଦି (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_for_statement (c_parser *parser, ତାର୍କିକ ivdep, unsigned short unroll,
			ତାର୍କିକ novector, ତାର୍କିକ *if_p, ବୃକ୍ଷ before_labels)
{
  ବୃକ୍ଷ block, cond, incr, body;
  unsigned ଅକ୍ଷର save_in_statement;
  ବୃକ୍ଷ save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  ବୃକ୍ଷ object_expression;
  /* Silence the bogus uninitialized warning.  */
  ବୃକ୍ଷ collection_expression = ଖାଲି;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  ତାର୍କିକ is_foreach_statement = ମିଥ୍ୟା;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  ବୃକ୍ଷ loop_name;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_names = c_get_loop_names (before_labels, ମିଥ୍ୟା, &loop_name);

  ଯଦି (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = ସତ୍ୟ;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  block = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_ଗଣ୍ଠି;
  incr = error_mark_ଗଣ୍ଠି;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_expression = error_mark_ଗଣ୍ଠି;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = ମିଥ୍ୟା;
	  c_parser_consume_token (parser);
	  c_finish_ପଦସମଷ୍ଟି_stmt (loc, NULL_ବୃକ୍ଷ);
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_tokens_start_declaration (parser)
	       || c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ,
					 ମିଥ୍ୟା, &object_expression);
	  parser->objc_could_be_foreach_context = ମିଥ୍ୟା;

	  ଯଦି (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = ସତ୍ୟ;
	      ଯଦି (check_for_loop_decls (for_loc, ସତ୍ୟ) == NULL_ବୃକ୍ଷ)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  ଅନ୍ୟଥା
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  ଯେତେବେଳେ (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  ଯଦି (c_parser_next_tokens_start_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_attributes (parser, 2))
	    {
	      ପୂର୍ଣ୍ଣସଂଖ୍ୟା ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ,
					     ସତ୍ୟ, ମିଥ୍ୟା, &object_expression);
	      parser->objc_could_be_foreach_context = ମିଥ୍ୟା;

	      restore_extension_diagnostics (ext);
	      ଯଦି (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = ସତ୍ୟ;
		  ଯଦି (check_for_loop_decls (for_loc, ସତ୍ୟ) == NULL_ବୃକ୍ଷ)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      ଅନ୍ୟଥା
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  ଅନ୍ୟଥା
	    ଯାଅ init_ପଦସମଷ୍ଟି;
	}
      ଅନ୍ୟଥା
	{
	init_ପଦସମଷ୍ଟି:
	  {
	    ସଂରଚନା c_ପଦସମଷ୍ଟି ce;
	    ବୃକ୍ଷ init_expression;
	    ce = c_parser_expression (parser);
	    init_expression = ce.ମୂଲ୍ୟ;
	    parser->objc_could_be_foreach_context = ମିଥ୍ୟା;
	    ଯଦି (c_parser_next_token_is_keyword (parser, RID_IN))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = ସତ୍ୟ;
		ଯଦି (! lvalue_p (init_expression))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_expression
		  = c_fully_fold (init_expression, ମିଥ୍ୟା, ଖାଲି);
	      }
	    ଅନ୍ୟଥା
	      {
		ce = convert_lvalue_to_rvalue (loc, ce, ସତ୍ୟ, ମିଥ୍ୟା);
		init_expression = ce.ମୂଲ୍ୟ;
		c_finish_ପଦସମଷ୍ଟି_stmt (loc, init_expression);
		c_parser_skip_until_found (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      ଯଦି (!is_foreach_statement)
	{
	  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      ଯଦି (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_ଗଣ୍ଠି;
		}
	      ଅନ୍ୟଥା ଯଦି (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_ଗଣ୍ଠି;
		}
	      ଅନ୍ୟଥା
		{
		  c_parser_consume_token (parser);
		  cond = NULL_ବୃକ୍ଷ;
		}
	    }
	  ଅନ୍ୟଥା
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_found (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  ଯଦି (ivdep && cond != error_mark_ଗଣ୍ଠି)
	    cond = build3 (ANNOTATE_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (cond), cond,
			   build_int_cst (integer_type_ଗଣ୍ଠି,
					  annot_ପଦସମଷ୍ଟି_ivdep_kind),
			   integer_zero_ଗଣ୍ଠି);
	  ଯଦି (unroll && cond != error_mark_ଗଣ୍ଠି)
	    cond = build3 (ANNOTATE_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (cond), cond,
 			   build_int_cst (integer_type_ଗଣ୍ଠି,
					  annot_ପଦସମଷ୍ଟି_unroll_kind),
			   build_int_cst (integer_type_ଗଣ୍ଠି, unroll));
	  ଯଦି (novector && cond && cond != error_mark_ଗଣ୍ଠି)
	    cond = build3 (ANNOTATE_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (cond), cond,
			   build_int_cst (integer_type_ଗଣ୍ଠି,
					  annot_ପଦସମଷ୍ଟି_no_vector_kind),
			   integer_zero_ଗଣ୍ଠି);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ଯଦି (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_expression = error_mark_ଗଣ୍ଠି;
	    }
	  ଅନ୍ୟଥା
	    incr = c_process_ପଦସମଷ୍ଟି_stmt (loc, NULL_ବୃକ୍ଷ);
	}
      ଅନ୍ୟଥା
	{
	  ଯଦି (is_foreach_statement)
	    collection_expression
	      = c_fully_fold (c_parser_expression (parser).ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
	  ଅନ୍ୟଥା
	    {
	      ସଂରଚନା c_ପଦସମଷ୍ଟି ce = c_parser_expression (parser);
	      ce = convert_lvalue_to_rvalue (loc, ce, ସତ୍ୟ, ମିଥ୍ୟା);
	      incr = c_process_ପଦସମଷ୍ଟି_stmt (loc, ce.ମୂଲ୍ୟ);
	    }
	}
      parens.skip_until_found_close (parser);
    }
  save_in_statement = in_statement;
  ଯଦି (is_foreach_statement)
    {
      in_statement = IN_OBJC_FOREACH;
      save_objc_foreach_break_label = objc_foreach_break_label;
      save_objc_foreach_continue_label = objc_foreach_continue_label;
      objc_foreach_break_label = create_artificial_label (loc);
      objc_foreach_continue_label = create_artificial_label (loc);
      ଯଦି (loop_name)
	{
	  gcc_checking_assert (!DECL_CHAIN (loop_name)
			       && !DECL_CHAIN (objc_foreach_break_label));
	  C_DECL_SWITCH_NAME (loop_name) = 1;
	  DECL_CHAIN (loop_name) = objc_foreach_break_label;
	  DECL_CHAIN (objc_foreach_break_label) = objc_foreach_continue_label;
	}
    }
  ଅନ୍ୟଥା
    in_statement = IN_ITERATION_STMT;
  ଯଦି (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  ତାର୍କିକ open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);

  ଯଦି (loop_name && is_foreach_statement)
    {
      gcc_checking_assert (DECL_CHAIN (loop_name) == objc_foreach_break_label
			   && (DECL_CHAIN (objc_foreach_break_label)
			       == objc_foreach_continue_label));
      C_DECL_SWITCH_NAME (loop_name) = 0;
      DECL_CHAIN (loop_name) = NULL_ବୃକ୍ଷ;
      DECL_CHAIN (objc_foreach_break_label) = NULL_ବୃକ୍ଷ;
    }

  ଯଦି (is_foreach_statement)
    objc_finish_foreach_loop (for_loc, object_expression,
			      collection_expression, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  ଅନ୍ୟଥା
    add_stmt (build_stmt (for_loc, FOR_STMT, NULL_ବୃକ୍ଷ, cond, incr,
			  body, NULL_ବୃକ୍ଷ,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_USED (loop_name)
			  ? loop_name : NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ));
  add_stmt (c_end_compound_stmt (for_loc, block,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, next_tinfo);

  ଯଦି (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    for_tinfo.location, RID_FOR);

  in_statement = save_in_statement;
  ଯଦି (ଅଙ୍କ_names)
    c_release_loop_names (ଅଙ୍କ_names);
  ଯଦି (is_foreach_statement)
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_asm_statement (c_parser *parser)
{
  ବୃକ୍ଷ str, outputs, inputs, clobbers, labels, ret;
  ତାର୍କିକ simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା section, nsections;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);

  /* Handle the asm-qualifier-list.  */
  location_t volatile_loc = UNKNOWN_LOCATION;
  location_t inline_loc = UNKNOWN_LOCATION;
  location_t goto_loc = UNKNOWN_LOCATION;
  ପାଇଁ (;;)
    {
      c_token *token = c_parser_peek_token (parser);
      location_t loc = token->location;
      ବାଛ (token->keyword)
	{
	ସ୍ଥିତି RID_VOLATILE:
	  ଯଦି (volatile_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->ମୂଲ୍ୟ);
	      inform (volatile_loc, "first seen here");
	    }
	  ଅନ୍ୟଥା
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  ଜାରି;

	ସ୍ଥିତି RID_INLINE:
	  ଯଦି (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->ମୂଲ୍ୟ);
	      inform (inline_loc, "first seen here");
	    }
	  ଅନ୍ୟଥା
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  ଜାରି;

	ସ୍ଥିତି RID_GOTO:
	  ଯଦି (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->ମୂଲ୍ୟ);
	      inform (goto_loc, "first seen here");
	    }
	  ଅନ୍ୟଥା
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  ଜାରି;

	ସ୍ଥିତି RID_CONST:
	ସ୍ଥିତି RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->ମୂଲ୍ୟ);
	  c_parser_consume_token (parser);
	  ଜାରି;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଭାଙ୍ଗ;
	}
      ଭାଙ୍ଗ;
    }

  ତାର୍କିକ is_volatile = (volatile_loc != UNKNOWN_LOCATION);
  ତାର୍କିକ is_inline = (inline_loc != UNKNOWN_LOCATION);
  ତାର୍କିକ is_goto = (goto_loc != UNKNOWN_LOCATION);

  ret = ଖାଲି;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଯାଅ error;

  str = c_parser_asm_string_literal (parser);
  ଯଦି (str == NULL_ବୃକ୍ଷ)
    ଯାଅ error_close_paren;

  simple = ସତ୍ୟ;
  outputs = NULL_ବୃକ୍ଷ;
  inputs = NULL_ବୃକ୍ଷ;
  clobbers = NULL_ବୃକ୍ଷ;
  labels = NULL_ବୃକ୍ଷ;

  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    ଯାଅ done_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  ପାଇଁ (section = 0; section < nsections; ++section)
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  ଯଦି (section == nsections)
	    {
	      c_parser_error (parser, "expected %<)%>");
	      ଯାଅ error_close_paren;
	    }
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା ଯଦି (!c_parser_require (parser, CPP_COLON,
				  is_goto
				  ? G_("expected %<:%>")
				  : G_("expected %<:%> or %<)%>"),
				  UNKNOWN_LOCATION, is_goto))
	ଯାଅ error_close_paren;

      /* Once past any colon, we're no longer a simple asm.  */
      simple = ମିଥ୍ୟା;

      ଯଦି ((!c_parser_next_token_is (parser, CPP_COLON)
	   && !c_parser_next_token_is (parser, CPP_SCOPE)
	   && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	  || section == 3)
	ବାଛ (section)
	  {
	  ସ୍ଥିତି 0:
	    outputs = c_parser_asm_operands (parser);
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି 1:
	    inputs = c_parser_asm_operands (parser);
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି 2:
	    clobbers = c_parser_asm_clobbers (parser);
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି 3:
	    labels = c_parser_asm_goto_operands (parser);
	    ଭାଙ୍ଗ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    gcc_unreachable ();
	  }

      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	ଯାଅ done_asm;
    }

 done_asm:
  ଯଦି (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
      ଯାଅ error;
    }

  ଯଦି (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_to_end_of_block_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_ପଦସମଷ୍ଟି (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  ଫେରନ୍ତୁ ret;

 error_close_paren:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
  ଯାଅ error;
}

/* Parse asm operands, a GNU extension.

   asm-operands:
     asm-operand
     asm-operands , asm-operand

   asm-operand:
     asm-string-literal ( expression )
     [ identifier ] asm-string-literal ( expression )
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_asm_operands (c_parser *parser)
{
  ବୃକ୍ଷ list = NULL_ବୃକ୍ଷ;
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      ବୃକ୍ଷ name, str;
      ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
      ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
	{
	  c_parser_consume_token (parser);
	  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      ବୃକ୍ଷ id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_LENGTH (id),
				   IDENTIFIER_POINTER (id));
	    }
	  ଅନ୍ୟଥା
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, ଖାଲି);
	      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
	    }
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	}
      ଅନ୍ୟଥା
	name = NULL_ବୃକ୍ଷ;
      str = c_parser_asm_string_literal (parser);
      ଯଦି (str == NULL_ବୃକ୍ଷ)
	ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
      matching_parens parens;
      ଯଦି (!parens.require_open (parser))
	ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
      ପଦସମଷ୍ଟି = c_parser_expression (parser);
      mark_exp_read (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
      ଯଦି (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
	  ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
	}
      list = chainon (list, build_ବୃକ୍ଷ_list (build_ବୃକ୍ଷ_list (name, str),
					     ପଦସମଷ୍ଟି.ମୂଲ୍ୟ));
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
    }
  ଫେରନ୍ତୁ list;
}

/* Parse asm clobbers, a GNU extension.

   asm-clobbers:
     asm-string-literal
     asm-clobbers , asm-string-literal
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_asm_clobbers (c_parser *parser)
{
  ବୃକ୍ଷ list = NULL_ବୃକ୍ଷ;
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      ବୃକ୍ଷ str = c_parser_asm_string_literal (parser);
      ଯଦି (str)
	list = ବୃକ୍ଷ_cons (NULL_ବୃକ୍ଷ, str, list);
      ଅନ୍ୟଥା
	ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
    }
  ଫେରନ୍ତୁ list;
}

/* Parse asm goto labels, a GNU extension.

   asm-goto-operands:
     identifier
     asm-goto-operands , identifier
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_asm_goto_operands (c_parser *parser)
{
  ବୃକ୍ଷ list = NULL_ବୃକ୍ଷ;
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      ବୃକ୍ଷ name, label;

      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->ମୂଲ୍ୟ;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  ବୃକ୍ଷ_USED (label) = 1;
	}
      ଅନ୍ୟଥା
	{
	  c_parser_error (parser, "expected identifier");
	  ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
	}

      name = build_string (IDENTIFIER_LENGTH (name),
			   IDENTIFIER_POINTER (name));
      list = ବୃକ୍ଷ_cons (name, label, list);
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ଅନ୍ୟଥା
	ଫେରନ୍ତୁ nreverse (list);
    }
}

/* Parse a possibly concatenated sequence of string literals.
   TRANSLATE says whether to translate them to the execution character
   set; WIDE_OK says whether any kind of prefixed string literal is
   permitted in this context.  This code is based on that in
   lex_string.  */

ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_string_literal (c_parser *parser, ତାର୍କିକ translate, ତାର୍କିକ wide_ok)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
  size_t ଗଣନା_2;
  ସଂରଚନା obstack str_ob;
  ସଂରଚନା obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, last_tok_loc;
  ଗଣନା cpp_ttype type;
  ବୃକ୍ଷ ମୂଲ୍ୟ, string_ବୃକ୍ଷ;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  last_tok_loc = linemap_resolve_location (ଧାଡ଼ି_table, loc,
					   LRK_MACRO_DEFINITION_LOCATION,
					   ଖାଲି);
  type = tok->type;
  ବାଛ (type)
    {
    ସ୍ଥିତି CPP_STRING:
    ସ୍ଥିତି CPP_WSTRING:
    ସ୍ଥିତି CPP_STRING16:
    ସ୍ଥିତି CPP_STRING32:
    ସ୍ଥିତି CPP_UTF8STRING:
      string_ବୃକ୍ଷ = tok->ମୂଲ୍ୟ;
      ଭାଙ୍ଗ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      c_parser_error (parser, "expected string literal");
      ret.set_error ();
      ret.ମୂଲ୍ୟ = NULL_ବୃକ୍ଷ;
      ret.original_code = ERROR_MARK;
      ret.original_type = NULL_ବୃକ୍ଷ;
      ଫେରନ୍ତୁ ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  ବାଛ (c_parser_peek_2nd_token (parser)->type)
    {
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      c_parser_consume_token (parser);
      str.text = (ଅଚଳ unsigned ଅକ୍ଷର *) ବୃକ୍ଷ_STRING_POINTER (string_ବୃକ୍ଷ);
      str.len = ବୃକ୍ଷ_STRING_LENGTH (string_ବୃକ୍ଷ);
      ଗଣନା_2 = 1;
      strs = &str;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି CPP_STRING:
    ସ୍ଥିତି CPP_WSTRING:
    ସ୍ଥିତି CPP_STRING16:
    ସ୍ଥିତି CPP_STRING32:
    ସ୍ଥିତି CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      ଗଣନା_2 = 0;
      କର
	{
	  c_parser_consume_token (parser);
	  ଗଣନା_2++;
	  str.text = (ଅଚଳ unsigned ଅକ୍ଷର *) ବୃକ୍ଷ_STRING_POINTER (string_ବୃକ୍ଷ);
	  str.len = ବୃକ୍ଷ_STRING_LENGTH (string_ବୃକ୍ଷ);
	  ଯଦି (type != tok->type)
	    {
	      ଯଦି (type == CPP_STRING)
		type = tok->type;
	      ଅନ୍ୟଥା ଯଦି (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, ଆକାର (cpp_string));
	  obstack_grow (&loc_ob, &last_tok_loc, ଆକାର (location_t));
	  tok = c_parser_peek_token (parser);
	  string_ବୃକ୍ଷ = tok->ମୂଲ୍ୟ;
	  last_tok_loc
	    = linemap_resolve_location (ଧାଡ଼ି_table, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, ଖାଲି);
	}
      ଯେତେବେଳେ (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_finish (&str_ob);
    }

  ଯଦି (ଗଣନା_2 > 1 && !in_system_header_at (ନିବେଶ_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  ଯଦି ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_in, strs, ଗଣନା_2, &istr, type)))
    {
      ମୂଲ୍ୟ = build_string (istr.len, (ଅଚଳ ଅକ୍ଷର *) istr.text);
      ମୁକ୍ତ (const_cast<unsigned ଅକ୍ଷର *> (istr.text));
      ଯଦି (ଗଣନା_2 > 1)
	{
	  location_t *locs = (location_t *) obstack_finish (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->record_string_concatenation (ଗଣନା_2, locs);
	}
    }
  ଅନ୍ୟଥା
    {
      ଯଦି (type != CPP_STRING && !wide_ok)
	{
	  error_at (loc, "a wide string is invalid in this context");
	  type = CPP_STRING;
	}
      /* Callers cannot generally handle error_mark_node in this
	 context, so return the empty string instead.  An error has
	 been issued, either above or from cpp_interpret_string.  */
      ବାଛ (type)
	{
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	ସ୍ଥିତି CPP_STRING:
	ସ୍ଥିତି CPP_UTF8STRING:
	  ଯଦି (type == CPP_UTF8STRING && flag_char8_t)
	    {
	      ମୂଲ୍ୟ = build_string (TYPE_PRECISION (char8_type_ଗଣ୍ଠି)
				    / TYPE_PRECISION (char_type_ଗଣ୍ଠି),
				    "");  /* char8_t is 8 bits */
	    }
	  ଅନ୍ୟଥା
	    ମୂଲ୍ୟ = build_string (1, "");
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_STRING16:
	  ମୂଲ୍ୟ = build_string (TYPE_PRECISION (char16_type_ଗଣ୍ଠି)
				/ TYPE_PRECISION (char_type_ଗଣ୍ଠି),
				"\0");  /* char16_t is 16 bits */
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_STRING32:
	  ମୂଲ୍ୟ = build_string (TYPE_PRECISION (char32_type_ଗଣ୍ଠି)
				/ TYPE_PRECISION (char_type_ଗଣ୍ଠି),
				"\0\0\0");  /* char32_t is 32 bits */
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_WSTRING:
	  ମୂଲ୍ୟ = build_string (TYPE_PRECISION (wchar_type_ଗଣ୍ଠି)
				/ TYPE_PRECISION (char_type_ଗଣ୍ଠି),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  ଭାଙ୍ଗ;
        }
    }

  ବାଛ (type)
    {
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
    ସ୍ଥିତି CPP_STRING:
      ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ) = char_array_type_ଗଣ୍ଠି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_UTF8STRING:
      ଯଦି (flag_char8_t)
	ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ) = char8_array_type_ଗଣ୍ଠି;
      ଅନ୍ୟଥା
	ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ) = char_array_type_ଗଣ୍ଠି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_STRING16:
      ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ) = char16_array_type_ଗଣ୍ଠି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_STRING32:
      ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ) = char32_array_type_ଗଣ୍ଠି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_WSTRING:
      ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ) = wchar_array_type_ଗଣ୍ଠି;
    }
  ମୂଲ୍ୟ = fix_string_type (ମୂଲ୍ୟ);

  ଯଦି (ଗଣନା_2 > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.ମୂଲ୍ୟ = ମୂଲ୍ୟ;
  ret.original_code = STRING_CST;
  ret.original_type = NULL_ବୃକ୍ଷ;
  set_c_ପଦସମଷ୍ଟି_source_range (&ret, get_range_from_loc (ଧାଡ଼ି_table, loc));
  ret.m_decimal = 0;
  parser->seen_string_literal = ସତ୍ୟ;
  ଫେରନ୍ତୁ ret;
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

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_ପଦସମଷ୍ଟି_no_commas (c_parser *parser, ସଂରଚନା c_ପଦସମଷ୍ଟି *after,
			 ବୃକ୍ଷ omp_atomic_lhs)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି lhs, rhs, ret;
  ଗଣନା ବୃକ୍ଷ_code code;
  location_t op_location, exp_location;
  ତାର୍କିକ save_in_omp_for = c_in_omp_for;
  c_in_omp_for = ମିଥ୍ୟା;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_expression (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  ବାଛ (c_parser_peek_token (parser)->type)
    {
    ସ୍ଥିତି CPP_EQ:
      code = NOP_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_MULT_EQ:
      code = MULT_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_DIV_EQ:
      code = TRUNC_DIV_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_MOD_EQ:
      code = TRUNC_MOD_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_PLUS_EQ:
      code = PLUS_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_MINUS_EQ:
      code = MINUS_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_LSHIFT_EQ:
      code = LSHIFT_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_RSHIFT_EQ:
      code = RSHIFT_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_AND_EQ:
      code = BIT_AND_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_XOR_EQ:
      code = BIT_XOR_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_OR_EQ:
      code = BIT_IOR_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      c_in_omp_for = save_in_omp_for;
      ଫେରନ୍ତୁ lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
  rhs = convert_lvalue_to_rvalue (exp_location, rhs, ସତ୍ୟ, ସତ୍ୟ);

  ret.ମୂଲ୍ୟ = build_modify_ପଦସମଷ୍ଟି (op_location, lhs.ମୂଲ୍ୟ, lhs.original_type,
				 code, exp_location, rhs.ମୂଲ୍ୟ,
				 rhs.original_type);
  ret.m_decimal = 0;
  set_c_ପଦସମଷ୍ଟି_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  ଯଦି (code == NOP_ପଦସମଷ୍ଟି)
    ret.original_code = MODIFY_ପଦସମଷ୍ଟି;
  ଅନ୍ୟଥା
    {
      suppress_warning (ret.ମୂଲ୍ୟ, OPT_Wparentheses);
      ret.original_code = ERROR_MARK;
    }
  ret.original_type = ଖାଲି;
  c_in_omp_for = save_in_omp_for;
  ଫେରନ୍ତୁ ret;
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

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_conditional_expression (c_parser *parser, ସଂରଚନା c_ପଦସମଷ୍ଟି *after,
				 ବୃକ୍ଷ omp_atomic_lhs)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି cond, exp1, exp2, ret;
  location_t start, cond_loc, colon_loc;
  ତାର୍କିକ save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_ଦ୍ୱିମିକ_expression (parser, after, omp_atomic_lhs);

  ଯଦି (c_parser_next_token_is_not (parser, CPP_QUERY))
    ଫେରନ୍ତୁ cond;
  c_omp_array_section_p = ମିଥ୍ୟା;
  ଯଦି (cond.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
    start = cond.get_start ();
  ଅନ୍ୟଥା
    start = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_to_rvalue (cond_loc, cond, ସତ୍ୟ, ସତ୍ୟ);
  c_parser_consume_token (parser);
  ଯଦି (c_parser_next_token_is (parser, CPP_COLON))
    {
      ବୃକ୍ଷ eptype = NULL_ବୃକ୍ଷ;

      location_t ମଧ୍ୟ_loc = c_parser_peek_token (parser)->location;
      pedwarn (ମଧ୍ୟ_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      ଯଦି (ବୃକ୍ଷ_CODE (cond.ମୂଲ୍ୟ) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
	{
	  eptype = ବୃକ୍ଷ_TYPE (cond.ମୂଲ୍ୟ);
	  cond.ମୂଲ୍ୟ = ବୃକ୍ଷ_OPERAND (cond.ମୂଲ୍ୟ, 0);
	}
      ବୃକ୍ଷ e = cond.ମୂଲ୍ୟ;
      ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (e) == COMPOUND_ପଦସମଷ୍ଟି)
	e = ବୃକ୍ଷ_OPERAND (e, 1);
      warn_for_omitted_condop (ମଧ୍ୟ_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.ମୂଲ୍ୟ = save_ପଦସମଷ୍ଟି (default_conversion (cond.ମୂଲ୍ୟ));
      ଯଦି (eptype)
	exp1.ମୂଲ୍ୟ = build1 (EXCESS_PRECISION_ପଦସମଷ୍ଟି, eptype, exp1.ମୂଲ୍ୟ);
      exp1.original_type = ଖାଲି;
      exp1.src_range = cond.src_range;
      cond.ମୂଲ୍ୟ = c_objc_common_truthvalue_conversion (cond_loc, exp1.ମୂଲ୍ୟ);
      c_inhibit_evaluation_warnings += cond.ମୂଲ୍ୟ == truthvalue_true_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା
    {
      cond.ମୂଲ୍ୟ
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.ମୂଲ୍ୟ));
      c_inhibit_evaluation_warnings += cond.ମୂଲ୍ୟ == truthvalue_false_ଗଣ୍ଠି;
      exp1 = c_parser_expression_conv (parser);
      mark_exp_read (exp1.ମୂଲ୍ୟ);
      c_inhibit_evaluation_warnings +=
	((cond.ମୂଲ୍ୟ == truthvalue_true_ଗଣ୍ଠି)
	 - (cond.ମୂଲ୍ୟ == truthvalue_false_ଗଣ୍ଠି));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.ମୂଲ୍ୟ == truthvalue_true_ଗଣ୍ଠି;
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = ଖାଲି;
      c_omp_array_section_p = save_c_omp_array_section_p;
      ଫେରନ୍ତୁ ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_expression (parser, ଖାଲି, NULL_ବୃକ୍ଷ);
    exp2 = convert_lvalue_to_rvalue (exp2_loc, exp2, ସତ୍ୟ, ସତ୍ୟ);
  }
  c_inhibit_evaluation_warnings -= cond.ମୂଲ୍ୟ == truthvalue_true_ଗଣ୍ଠି;
  location_t loc1 = make_location (exp1.get_start (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_start (), exp2.src_range);
  ଯଦି (UNLIKELY (omp_atomic_lhs != ଖାଲି)
      && (ବୃକ୍ଷ_CODE (cond.ମୂଲ୍ୟ) == GT_ପଦସମଷ୍ଟି
	  || ବୃକ୍ଷ_CODE (cond.ମୂଲ୍ୟ) == LT_ପଦସମଷ୍ଟି
	  || ବୃକ୍ଷ_CODE (cond.ମୂଲ୍ୟ) == EQ_ପଦସମଷ୍ଟି)
      && c_ବୃକ୍ଷ_equal (exp2.ମୂଲ୍ୟ, omp_atomic_lhs)
      && (c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (cond.ମୂଲ୍ୟ, 0), omp_atomic_lhs)
	  || c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (cond.ମୂଲ୍ୟ, 1), omp_atomic_lhs)))
    ret.ମୂଲ୍ୟ = build3_loc (colon_loc, COND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (omp_atomic_lhs),
			    cond.ମୂଲ୍ୟ, exp1.ମୂଲ୍ୟ, exp2.ମୂଲ୍ୟ);
  ଅନ୍ୟଥା
    ret.ମୂଲ୍ୟ
      = build_conditional_ପଦସମଷ୍ଟି (colon_loc, cond.ମୂଲ୍ୟ,
				cond.original_code == C_MAYBE_CONST_ପଦସମଷ୍ଟି,
				exp1.ମୂଲ୍ୟ, exp1.original_type, loc1,
				exp2.ମୂଲ୍ୟ, exp2.original_type, loc2);
  ret.original_code = ERROR_MARK;
  ଯଦି (exp1.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି || exp2.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
    ret.original_type = ଖାଲି;
  ଅନ୍ୟଥା
    {
      ବୃକ୍ଷ t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : ବୃକ୍ଷ_TYPE (exp1.ମୂଲ୍ୟ);
      t2 = exp2.original_type ? exp2.original_type : ବୃକ୍ଷ_TYPE (exp2.ମୂଲ୍ୟ);
      ret.original_type = ((t1 != error_mark_ଗଣ୍ଠି
			    && t2 != error_mark_ଗଣ୍ଠି
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : ଖାଲି);
    }
  set_c_ପଦସମଷ୍ଟି_source_range (&ret, start, exp2.get_finish ());
  ret.m_decimal = 0;
  c_omp_array_section_p = save_c_omp_array_section_p;
  ଫେରନ୍ତୁ ret;
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

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_ଦ୍ୱିମିକ_expression (c_parser *parser, ସଂରଚନା c_ପଦସମଷ୍ଟି *after,
			    ବୃକ୍ଷ omp_atomic_lhs)
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

  ସଂରଚନା {
    /* The expression at this stack level.  */
    ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    ଗଣନା c_parser_prec prec;
    /* The operation on its left.  */
    ଗଣନା ବୃକ୍ଷ_code op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    ବୃକ୍ଷ sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    ବୃକ୍ଷ orig_ପଦସମଷ୍ଟି;
  } ଗଦା[ଅଙ୍କ_PRECS];
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା sp;
  /* Location of the binary operator.  */
  location_t ଦ୍ୱିମିକ_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#define କାଢ଼_2								      \
  କର {									      \
    ବାଛ (ଗଦା[sp].op)						      \
      {									      \
      ସ୍ଥିତି TRUTH_ANDIF_ପଦସମଷ୍ଟି:						      \
	c_inhibit_evaluation_warnings -= (ଗଦା[sp - 1].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ	      \
					  == truthvalue_false_ଗଣ୍ଠି);	      \
	ଭାଙ୍ଗ;								      \
      ସ୍ଥିତି TRUTH_ORIF_ପଦସମଷ୍ଟି:						      \
	c_inhibit_evaluation_warnings -= (ଗଦା[sp - 1].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ	      \
					  == truthvalue_true_ଗଣ୍ଠି);	      \
	ଭାଙ୍ଗ;								      \
      ସ୍ଥିତି TRUNC_DIV_ପଦସମଷ୍ଟି:						      \
	ଯଦି ((ଗଦା[sp - 1].ପଦସମଷ୍ଟି.original_code == SIZEOF_ପଦସମଷ୍ଟି		      \
	     || ଗଦା[sp - 1].ପଦସମଷ୍ଟି.original_code == PAREN_SIZEOF_ପଦସମଷ୍ଟି)	      \
	    && (ଗଦା[sp].ପଦସମଷ୍ଟି.original_code == SIZEOF_ପଦସମଷ୍ଟି		      \
		|| ଗଦା[sp].ପଦସମଷ୍ଟି.original_code == PAREN_SIZEOF_ପଦସମଷ୍ଟି))	      \
	  {								      \
	    ବୃକ୍ଷ type0 = ଗଦା[sp - 1].sizeof_arg;			      \
	    ବୃକ୍ଷ type1 = ଗଦା[sp].sizeof_arg;				      \
	    ବୃକ୍ଷ first_arg = type0;					      \
	    ଯଦି (!TYPE_P (type0))					      \
	      type0 = ବୃକ୍ଷ_TYPE (type0);				      \
	    ଯଦି (!TYPE_P (type1))					      \
	      type1 = ବୃକ୍ଷ_TYPE (type1);				      \
	    ଯଦି (POINTER_TYPE_P (type0)					      \
		&& comptypes (ବୃକ୍ଷ_TYPE (type0), type1)			      \
		&& !(ବୃକ୍ଷ_CODE (first_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (first_arg)			      \
		     && warn_sizeof_array_argument))			      \
	      {								      \
		auto_diagnostic_group d;				      \
		ଯଦି (warning_at (ଗଦା[sp].loc, OPT_Wsizeof_pointer_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  ଯଦି (DECL_P (first_arg))				      \
		    inform (DECL_SOURCE_LOCATION (first_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (type0)))  \
		     && ଗଦା[sp].ପଦସମଷ୍ଟି.original_code != PAREN_SIZEOF_ପଦସମଷ୍ଟି)    \
	      maybe_warn_sizeof_array_div (ଗଦା[sp].loc, first_arg, type0,   \
					   ଗଦା[sp].sizeof_arg, type1);      \
	  }								      \
	ଭାଙ୍ଗ;								      \
      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:								      \
	ଭାଙ୍ଗ;								      \
      }									      \
    ଗଦା[sp - 1].ପଦସମଷ୍ଟି							      \
      = convert_lvalue_to_rvalue (ଗଦା[sp - 1].loc,			      \
				  ଗଦା[sp - 1].ପଦସମଷ୍ଟି, ସତ୍ୟ, ସତ୍ୟ);	      \
    ଗଦା[sp].ପଦସମଷ୍ଟି							      \
      = convert_lvalue_to_rvalue (ଗଦା[sp].loc,			      \
				  ଗଦା[sp].ପଦସମଷ୍ଟି, ସତ୍ୟ, ସତ୍ୟ);		      \
    ଯଦି (UNLIKELY (omp_atomic_lhs != NULL_ବୃକ୍ଷ) && sp == 1		      \
	&& ((c_parser_next_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << ଗଦା[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_SHIFT)		      \
		     | (1 << PREC_ADD) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_next_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_ଗଣ୍ଠି			      \
		     && c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (ଗଦା[sp].prec == PREC_REL || ଗଦା[sp].prec == PREC_EQ)))\
	&& ଗଦା[sp].op != TRUNC_MOD_ପଦସମଷ୍ଟି				      \
	&& ଗଦା[sp].op != GE_ପଦସମଷ୍ଟି					      \
	&& ଗଦା[sp].op != LE_ପଦସମଷ୍ଟି					      \
	&& ଗଦା[sp].op != NE_ପଦସମଷ୍ଟି					      \
	&& ଗଦା[0].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି			      \
	&& ଗଦା[1].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି			      \
	&& (omp_atomic_lhs == void_list_ଗଣ୍ଠି				      \
	    || c_ବୃକ୍ଷ_equal (ଗଦା[0].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, omp_atomic_lhs)	      \
	    || c_ବୃକ୍ଷ_equal (ଗଦା[1].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, omp_atomic_lhs)	      \
	    || (ଗଦା[sp].op == EQ_ପଦସମଷ୍ଟି					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	ବୃକ୍ଷ t = make_ଗଣ୍ଠି (ଗଦା[1].op);				      \
	ବୃକ୍ଷ_TYPE (t) = ବୃକ୍ଷ_TYPE (ଗଦା[0].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);		      \
	ବୃକ୍ଷ_OPERAND (t, 0) = ଗଦା[0].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;			      \
	ବୃକ୍ଷ_OPERAND (t, 1) = ଗଦା[1].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;			      \
	ଗଦା[0].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = t;					      \
	ଗଦା[0].ପଦସମଷ୍ଟି.m_decimal = 0;					      \
      }									      \
    ଅନ୍ୟଥା								      \
      ଗଦା[sp - 1].ପଦସମଷ୍ଟି = parser_build_ଦ୍ୱିମିକ_op (ଗଦା[sp].loc,	      \
						   ଗଦା[sp].op,	      \
						   ଗଦା[sp - 1].ପଦସମଷ୍ଟି,	      \
						   ଗଦା[sp].ପଦସମଷ୍ଟି,	      \
						   ଗଦା[sp - 1].orig_ପଦସମଷ୍ଟି);  \
    ଗଦା[sp - 1].orig_ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;				      \
    sp--;								      \
  } ଯେତେବେଳେ (0)
  gcc_assert (!after || c_dialect_objc ());
  ଗଦା[0].loc = c_parser_peek_token (parser)->location;
  ଗଦା[0].ପଦସମଷ୍ଟି = c_parser_cast_expression (parser, after);
  ଗଦା[0].prec = PREC_NONE;
  ଗଦା[0].sizeof_arg = c_last_sizeof_arg;
  ଗଦା[0].orig_ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
  sp = 0;
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      ଗଣନା c_parser_prec oprec;
      ଗଣନା ବୃକ୍ଷ_code ocode;
      source_range src_range;
      ଯଦି (parser->error)
	ଯାଅ out;
      ବାଛ (c_parser_peek_token (parser)->type)
	{
	ସ୍ଥିତି CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_PLUS:
	  oprec = PREC_ADD;
	  ocode = PLUS_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_MINUS:
	  oprec = PREC_ADD;
	  ocode = MINUS_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_LSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = LSHIFT_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_RSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = RSHIFT_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = BIT_AND_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = BIT_XOR_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = BIT_IOR_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  ଯାଅ out;
	}
      ଦ୍ୱିମିକ_loc = c_parser_peek_token (parser)->location;
      ଯେତେବେଳେ (oprec <= ଗଦା[sp].prec)
	କାଢ଼_2;
      c_parser_consume_token (parser);
      ବାଛ (ocode)
	{
	ସ୍ଥିତି TRUTH_ANDIF_ପଦସମଷ୍ଟି:
	  src_range = ଗଦା[sp].ପଦସମଷ୍ଟି.src_range;
	  ଗଦା[sp].ପଦସମଷ୍ଟି
	    = convert_lvalue_to_rvalue (ଗଦା[sp].loc,
					ଗଦା[sp].ପଦସମଷ୍ଟି, ସତ୍ୟ, ସତ୍ୟ);
	  ଗଦା[sp].orig_ପଦସମଷ୍ଟି = ଗଦା[sp].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
	  ଗଦା[sp].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_objc_common_truthvalue_conversion
	    (ଗଦା[sp].loc, default_conversion (ଗଦା[sp].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ));
	  c_inhibit_evaluation_warnings += (ଗଦା[sp].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ
					    == truthvalue_false_ଗଣ୍ଠି);
	  set_c_ପଦସମଷ୍ଟି_source_range (&ଗଦା[sp].ପଦସମଷ୍ଟି, src_range);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି TRUTH_ORIF_ପଦସମଷ୍ଟି:
	  src_range = ଗଦା[sp].ପଦସମଷ୍ଟି.src_range;
	  ଗଦା[sp].ପଦସମଷ୍ଟି
	    = convert_lvalue_to_rvalue (ଗଦା[sp].loc,
					ଗଦା[sp].ପଦସମଷ୍ଟି, ସତ୍ୟ, ସତ୍ୟ);
	  ଗଦା[sp].orig_ପଦସମଷ୍ଟି = ଗଦା[sp].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
	  ଗଦା[sp].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_objc_common_truthvalue_conversion
	    (ଗଦା[sp].loc, default_conversion (ଗଦା[sp].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ));
	  c_inhibit_evaluation_warnings += (ଗଦା[sp].ପଦସମଷ୍ଟି.ମୂଲ୍ୟ
					    == truthvalue_true_ଗଣ୍ଠି);
	  set_c_ପଦସମଷ୍ଟି_source_range (&ଗଦା[sp].ପଦସମଷ୍ଟି, src_range);
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଭାଙ୍ଗ;
	}
      sp++;
      ଗଦା[sp].loc = ଦ୍ୱିମିକ_loc;
      ଗଦା[sp].ପଦସମଷ୍ଟି = c_parser_cast_expression (parser, ଖାଲି);
      ଗଦା[sp].prec = oprec;
      ଗଦା[sp].op = ocode;
      ଗଦା[sp].sizeof_arg = c_last_sizeof_arg;
      ଗଦା[sp].orig_ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
    }
 out:
  ଯେତେବେଳେ (sp > 0)
    କାଢ଼_2;
  ଫେରନ୍ତୁ ଗଦା[0].ପଦସମଷ୍ଟି;
#undef କାଢ଼_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

ସ୍ଥିର ସଂରଚନା c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  ତାର୍କିକ seen_scspec = ମିଥ୍ୟା;
  ସଂରଚନା c_declspecs *specs = build_null_declspecs ();
  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      ବାଛ (c_parser_peek_token (parser)->keyword)
	{
	ସ୍ଥିତି RID_CONSTEXPR:
	ସ୍ଥିତି RID_REGISTER:
	ସ୍ଥିତି RID_STATIC:
	ସ୍ଥିତି RID_THREAD:
	  seen_scspec = ସତ୍ୟ;
	  declspecs_add_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	  c_parser_consume_token (parser);
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଯାଅ out;
	}
    }
 out:
  ଫେରନ୍ତୁ seen_scspec ? specs : ଖାଲି;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_cast_expression (c_parser *parser, ସଂରଚନା c_ପଦସମଷ୍ଟି *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  ଯଦି (after)
    ଫେରନ୍ତୁ c_parser_postfix_expression_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      ସଂରଚନା c_declspecs *scspecs;
      ସଂରଚନା c_type_name *type_name;
      ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
      ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, ସତ୍ୟ);
      parens.skip_until_found_close (parser);
      ଯଦି (type_name == ଖାଲି)
	{
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = ଖାଲି;
	  ଫେରନ୍ତୁ ret;
	}

      /* Save casted types in the function's used types hash table.  */
      used_types_ଭର୍ତ୍ତି (type_name->specs->type);

      ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	ଫେରନ୍ତୁ c_parser_postfix_expression_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      ଯଦି (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      ଯଦି (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
	ପଦସମଷ୍ଟି = c_parser_cast_expression (parser, ଖାଲି);
	ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ସତ୍ୟ);
      }
      ret.ମୂଲ୍ୟ = c_cast_ପଦସମଷ୍ଟି (cast_loc, type_name, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
      ଯଦି (ret.ମୂଲ୍ୟ && ପଦସମଷ୍ଟି.ମୂଲ୍ୟ)
	set_c_ପଦସମଷ୍ଟି_source_range (&ret, cast_loc, ପଦସମଷ୍ଟି.get_finish ());
      ret.original_code = ERROR_MARK;
      ret.original_type = ଖାଲି;
      ret.m_decimal = 0;
      ଫେରନ୍ତୁ ret;
    }
  ଅନ୍ୟଥା
    ଫେରନ୍ତୁ c_parser_unary_expression (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

ସ୍ଥିର ଶୂନ୍ୟ
mark_exp_read_cond (ବୃକ୍ଷ exp)
{
  ଯଦି ((VAR_P (exp) || ବୃକ୍ଷ_CODE (exp) == PARM_DECL)
      && (VAR_P (exp) ? warn_unused_but_set_variable
		      : warn_unused_but_set_parameter) > 1)
    ଫେରନ୍ତୁ;

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

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_unary_expression (c_parser *parser)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ext;
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t exp_loc;
  location_t finish;
  ret.original_code = ERROR_MARK;
  ret.original_type = ଖାଲି;
  ବାଛ (c_parser_peek_token (parser)->type)
    {
    ସ୍ଥିତି CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ଖାଲି);
      mark_exp_read_cond (op.ମୂଲ୍ୟ);
      op = default_function_array_conversion (exp_loc, op);
      ଫେରନ୍ତୁ parser_build_unary_op (op_loc, PREINCREMENT_ପଦସମଷ୍ଟି, op);
    ସ୍ଥିତି CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ଖାଲି);
      mark_exp_read_cond (op.ମୂଲ୍ୟ);
      op = default_function_array_conversion (exp_loc, op);
      ଫେରନ୍ତୁ parser_build_unary_op (op_loc, PREDECREMENT_ପଦସମଷ୍ଟି, op);
    ସ୍ଥିତି CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, ଖାଲି);
      mark_exp_read (op.ମୂଲ୍ୟ);
      ଫେରନ୍ତୁ parser_build_unary_op (op_loc, ADDR_ପଦସମଷ୍ଟି, op);
    ସ୍ଥିତି CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_expression (parser, ଖାଲି);
	finish = op.get_finish ();
	op = convert_lvalue_to_rvalue (exp_loc, op, ସତ୍ୟ, ସତ୍ୟ);
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.ମୂଲ୍ୟ = build_indirect_ref (combined_loc, op.ମୂଲ୍ୟ, RO_UNARY_STAR);
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ret.m_decimal = 0;
	ଫେରନ୍ତୁ ret;
      }
    ସ୍ଥିତି CPP_PLUS:
      ଯଦି (!c_dialect_objc () && !in_system_header_at (ନିବେଶ_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ଖାଲି);
      op = convert_lvalue_to_rvalue (exp_loc, op, ସତ୍ୟ, ସତ୍ୟ);
      ଫେରନ୍ତୁ parser_build_unary_op (op_loc, CONVERT_ପଦସମଷ୍ଟି, op);
    ସ୍ଥିତି CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ଖାଲି);
      op = convert_lvalue_to_rvalue (exp_loc, op, ସତ୍ୟ, ସତ୍ୟ);
      ଫେରନ୍ତୁ parser_build_unary_op (op_loc, NEGATE_ପଦସମଷ୍ଟି, op);
    ସ୍ଥିତି CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ଖାଲି);
      op = convert_lvalue_to_rvalue (exp_loc, op, ସତ୍ୟ, ସତ୍ୟ);
      ଫେରନ୍ତୁ parser_build_unary_op (op_loc, BIT_NOT_ପଦସମଷ୍ଟି, op);
    ସ୍ଥିତି CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ଖାଲି);
      op = convert_lvalue_to_rvalue (exp_loc, op, ସତ୍ୟ, ସତ୍ୟ);
      ଫେରନ୍ତୁ parser_build_unary_op (op_loc, TRUTH_NOT_ପଦସମଷ୍ଟି, op);
    ସ୍ଥିତି CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ret.ମୂଲ୍ୟ = finish_label_address_ପଦସମଷ୍ଟି
	    (c_parser_peek_token (parser)->ମୂଲ୍ୟ, op_loc);
	  set_c_ପଦସମଷ୍ଟି_source_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_finish ());
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା
	{
	  c_parser_error (parser, "expected identifier");
	  ret.set_error ();
	}
      ଫେରନ୍ତୁ ret;
    ସ୍ଥିତି CPP_KEYWORD:
      {
	ଗଣନା rid rid = c_parser_peek_token (parser)->keyword;
	ବାଛ (rid)
	  {
	  ସ୍ଥିତି RID_COUNTOF:
	  ସ୍ଥିତି RID_SIZEOF:
	    ଫେରନ୍ତୁ c_parser_sizeof_or_countof_expression (parser, rid);
	  ସ୍ଥିତି RID_ALIGNOF:
	    ଫେରନ୍ତୁ c_parser_alignof_expression (parser);
	  ସ୍ଥିତି RID_MAXOF:
	  ସ୍ଥିତି RID_MINOF:
	    ଫେରନ୍ତୁ c_parser_maxof_or_minof_expression (parser, rid);
	  ସ୍ଥିତି RID_BUILTIN_HAS_ATTRIBUTE:
	    ଫେରନ୍ତୁ c_parser_has_attribute_expression (parser);
	  ସ୍ଥିତି RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_expression (parser, ଖାଲି);
	    restore_extension_diagnostics (ext);
	    ଫେରନ୍ତୁ ret;
	  ସ୍ଥିତି RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, ଖାଲି);
	    op = default_function_array_conversion (exp_loc, op);
	    ଫେରନ୍ତୁ parser_build_unary_op (op_loc, REALPART_ପଦସମଷ୍ଟି, op);
	  ସ୍ଥିତି RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, ଖାଲି);
	    op = default_function_array_conversion (exp_loc, op);
	    ଫେରନ୍ତୁ parser_build_unary_op (op_loc, IMAGPART_ପଦସମଷ୍ଟି, op);
	  ସ୍ଥିତି RID_TRANSACTION_ATOMIC:
	  ସ୍ଥିତି RID_TRANSACTION_RELAXED:
	    ଫେରନ୍ତୁ c_parser_transaction_expression (parser, rid);
	  ସ୍ଥିତି RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.ମୂଲ୍ୟ = void_ଗଣ୍ଠି;
	    set_c_ପଦସମଷ୍ଟି_source_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    ଫେରନ୍ତୁ ret;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    ଫେରନ୍ତୁ c_parser_postfix_expression (parser);
	  }
      }
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଫେରନ୍ତୁ c_parser_postfix_expression (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_sizeof_or_countof_expression (c_parser *parser, ଗଣନା rid rid)
{
  ଅଚଳ ଅକ୍ଷର *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
  ସଂରଚନା c_ପଦସମଷ୍ଟି result;
  location_t ପଦସମଷ୍ଟି_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  ଯଦି (rid == RID_COUNTOF)
    pedwarn_c23 (start, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  ଯଦି (rid == RID_COUNTOF)
    in_countof++;
  ଅନ୍ୟଥା
    in_sizeof++;
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      ସଂରଚନା c_declspecs *scspecs;
      ସଂରଚନା c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, ସତ୍ୟ);
      parens.skip_until_found_close (parser);
      finish = parser->tokens_buf[0].location;
      ଯଦି (type_name == ଖାଲି)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  ପଦସମଷ୍ଟି.set_error ();
	  ଯାଅ Xof_ପଦସମଷ୍ଟି;
	}
      ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  ପଦସମଷ୍ଟି = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       ପଦସମଷ୍ଟି_loc);
	  finish = ପଦସମଷ୍ଟି.get_finish ();
	  ଯାଅ Xof_ପଦସମଷ୍ଟି;
	}
      /* sizeof ( type-name ).  */
      ଯଦି (scspecs)
	error_at (ପଦସମଷ୍ଟି_loc, "storage class specifier in %qs", op_name);
      ଯଦି (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      ଯଦି (rid == RID_COUNTOF)
	{
	  in_countof--;
	  result = c_ପଦସମଷ୍ଟି_countof_type (ପଦସମଷ୍ଟି_loc, type_name);
	}
      ଅନ୍ୟଥା
	{
	  in_sizeof--;
	  result = c_ପଦସମଷ୍ଟି_sizeof_type (ପଦସମଷ୍ଟି_loc, type_name);
	}
    }
  ଅନ୍ୟଥା
    {
      ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      ପଦସମଷ୍ଟି = c_parser_unary_expression (parser);
      finish = ପଦସମଷ୍ଟି.get_finish ();
    Xof_ପଦସମଷ୍ଟି:
      c_inhibit_evaluation_warnings--;
      ଯଦି (rid == RID_COUNTOF)
	in_countof--;
      ଅନ୍ୟଥା
	in_sizeof--;
      mark_exp_read (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
      ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, 1)))
	error_at (ପଦସମଷ୍ଟି_loc, "%qs applied to a bit-field", op_name);
      ଯଦି (rid == RID_COUNTOF)
	result = c_ପଦସମଷ୍ଟି_countof_ପଦସମଷ୍ଟି (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି);
      ଅନ୍ୟଥା
	result = c_ପଦସମଷ୍ଟି_sizeof_ପଦସମଷ୍ଟି (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି);
    }
  ଯଦି (finish == UNKNOWN_LOCATION)
    finish = start;
  set_c_ପଦସମଷ୍ଟି_source_range (&result, start, finish);
  ଫେରନ୍ତୁ result;
}

/* Parse an alignof expression.  */

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_alignof_expression (c_parser *parser)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
  location_t start_loc = c_parser_peek_token (parser)->location;
  location_t end_loc;
  ବୃକ୍ଷ alignof_spelling = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNOF));
  ତାର୍କିକ is_c11_alignof = (strcmp (IDENTIFIER_POINTER (alignof_spelling),
				"_Alignof") == 0
			 || strcmp (IDENTIFIER_POINTER (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  ଯଦି (is_c11_alignof)
    {
      ଯଦି (flag_isoc99)
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      ଅନ୍ୟଥା
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_alignof++;
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      ସଂରଚନା c_declspecs *scspecs;
      ସଂରଚନା c_type_name *type_name;
      ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, ସତ୍ୟ);
      end_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
      ଯଦି (type_name == ଖାଲି)
	{
	  ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
	  c_inhibit_evaluation_warnings--;
	  in_alignof--;
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = ଖାଲି;
	  ଫେରନ୍ତୁ ret;
	}
      ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  ପଦସମଷ୍ଟି = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  ଯାଅ alignof_ପଦସମଷ୍ଟି;
	}
      /* alignof ( type-name ).  */
      ଯଦି (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      ଯଦି (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      ret.ମୂଲ୍ୟ = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       ଖାଲି, ଖାଲି),
					    ମିଥ୍ୟା, is_c11_alignof, 1);
      ret.original_code = ERROR_MARK;
      ret.original_type = ଖାଲି;
      set_c_ପଦସମଷ୍ଟି_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      ଫେରନ୍ତୁ ret;
    }
  ଅନ୍ୟଥା
    {
      ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
      ପଦସମଷ୍ଟି = c_parser_unary_expression (parser);
      end_loc = ପଦସମଷ୍ଟି.src_range.m_finish;
    alignof_ପଦସମଷ୍ଟି:
      mark_exp_read (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      ଯଦି (is_c11_alignof)
	pedwarn (start_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.ମୂଲ୍ୟ = c_alignof_ପଦସମଷ୍ଟି (start_loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
      ret.original_code = ERROR_MARK;
      ret.original_type = ଖାଲି;
      set_c_ପଦସମଷ୍ଟି_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      ଫେରନ୍ତୁ ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_maxof_or_minof_expression (c_parser *parser, ଗଣନା rid rid)
{
  ଅଚଳ ଅକ୍ଷର *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  ସଂରଚନା c_ପଦସମଷ୍ଟି result;
  location_t ପଦସମଷ୍ଟି_loc;
  ସଂରଚନା c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  pedwarn (start, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  ଯଦି (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      ଯାଅ fail;
    }
  parens.consume_open (parser);
  ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
  ଯଦି (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (ପଦସମଷ୍ଟି_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_found_close (parser);
      ଯାଅ fail;
    }
  type_name = c_parser_type_name (parser, ସତ୍ୟ);
  ଯଦି (type_name == ଖାଲି)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_found_close (parser);
      ଯାଅ fail;
    }
  parens.skip_until_found_close (parser);
  finish = parser->tokens_buf[0].location;
  ଯଦି (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  ଯଦି (rid == RID_MAXOF)
    result = c_ପଦସମଷ୍ଟି_maxof_type (ପଦସମଷ୍ଟି_loc, type_name);
  ଅନ୍ୟଥା
    result = c_ପଦସମଷ୍ଟି_minof_type (ପଦସମଷ୍ଟି_loc, type_name);
  set_c_ପଦସମଷ୍ଟି_source_range (&result, start, finish);
  ଫେରନ୍ତୁ result;
fail:
  c_inhibit_evaluation_warnings--;
  result.set_error ();
  result.original_code = ERROR_MARK;
  result.original_type = ଖାଲି;
  ଫେରନ୍ତୁ result;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_has_attribute_expression (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t start = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;

      ସଂରଚନା c_ପଦସମଷ୍ଟି result;
      result.set_error ();
      result.original_code = ERROR_MARK;
      result.original_type = ଖାଲି;
      ଫେରନ୍ତୁ result;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  in_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  ବୃକ୍ଷ oper = NULL_ବୃକ୍ଷ;
  ଯଦି (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      ସଂରଚନା c_type_name *tname = c_parser_type_name (parser);
      in_typeof--;
      ଯଦି (tname)
	{
	  oper = groktypename (tname, ଖାଲି, ଖାଲି);
	  କାଢ଼_maybe_used (c_type_variably_modified_p (oper));
	}
    }
  ଅନ୍ୟଥା
    {
      ସଂରଚନା c_ପଦସମଷ୍ଟି cexpr = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      ଯଦି (cexpr.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
	{
	  mark_exp_read (cexpr.ମୂଲ୍ୟ);
	  oper = cexpr.ମୂଲ୍ୟ;
	  ବୃକ୍ଷ etype = ବୃକ୍ଷ_TYPE (oper);
	  ତାର୍କିକ was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  ଯଦି (was_vm)
	    oper = c_fully_fold (oper, ମିଥ୍ୟା, ଖାଲି);
	  କାଢ଼_maybe_used (was_vm);
	}
    }

  ସଂରଚନା c_ପଦସମଷ୍ଟି result;
  result.original_code = ERROR_MARK;
  result.original_type = ଖାଲି;

  ଯଦି (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      result.set_error ();
      ଫେରନ୍ତୁ result;
    }

  ତାର୍କିକ save_translate_strings_p = parser->translate_strings_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  ବୃକ୍ଷ attr = c_parser_gnu_attribute (parser, NULL_ବୃକ୍ଷ, ମିଥ୍ୟା, ମିଥ୍ୟା);

  parser->translate_strings_p = save_translate_strings_p;

  location_t finish = c_parser_peek_token (parser)->location;
  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  ଅନ୍ୟଥା
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);

      result.set_error ();
      ଫେରନ୍ତୁ result;
    }

  ଯଦି (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      result.set_error ();
      ଫେରନ୍ତୁ result;
    }

  result.original_code = INTEGER_CST;
  result.original_type = boolean_type_ଗଣ୍ଠି;

  ଯଦି (has_attribute (atloc, oper, attr, default_conversion))
    result.ମୂଲ୍ୟ = boolean_true_ଗଣ୍ଠି;
  ଅନ୍ୟଥା
    result.ମୂଲ୍ୟ =  boolean_false_ଗଣ୍ଠି;

  set_c_ପଦସମଷ୍ଟି_source_range (&result, start, finish);
  result.m_decimal = 0;
  ଫେରନ୍ତୁ result;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
ସ୍ଥିର ତାର୍କିକ
c_parser_get_builtin_args (c_parser *parser, ଅଚଳ ଅକ୍ଷର *bname,
			   vec<c_ପଦସମଷ୍ଟି_t, va_gc> **ret_cexpr_list,
			   ତାର୍କିକ choose_ପଦସମଷ୍ଟି_p,
			   location_t *out_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_ପଦସମଷ୍ଟି_t, va_gc> *cexpr_list;
  c_ପଦସମଷ୍ଟି_t ପଦସମଷ୍ଟି;
  ତାର୍କିକ saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = ଖାଲି;
  ଯଦି (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

  c_parser_consume_token (parser);

  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      *out_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= choose_ପଦସମଷ୍ଟି_p;
  ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_safe_ଠେଲ (cexpr_list, ପଦସମଷ୍ଟି);
  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ଯଦି (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  ବୃକ୍ଷ ମୂଲ୍ୟ = embed->ମୂଲ୍ୟ;
	  ପଦସମଷ୍ଟି.original_code = INTEGER_CST;
	  ପଦସମଷ୍ଟି.original_type = integer_type_ଗଣ୍ଠି;
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = NULL_ବୃକ୍ଷ;
	  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, embed->get_range ());
	  ପଦସମଷ୍ଟି.m_decimal = 0;
	  ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < (unsigned) RAW_DATA_LENGTH (ମୂଲ୍ୟ); i++)
	    {
	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_int_cst (integer_type_ଗଣ୍ଠି,
					  RAW_DATA_UCHAR_ELT (ମୂଲ୍ୟ, i));
	      vec_safe_ଠେଲ (cexpr_list, ପଦସମଷ୍ଟି);
	    }
	  c_parser_consume_token (parser);
	  ଜାରି;
	}
      ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      vec_safe_ଠେଲ (cexpr_list, ପଦସମଷ୍ଟି);
    }

  *out_close_paren_loc = c_parser_peek_token (parser)->location;
  ଯଦି (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  *ret_cexpr_list = cexpr_list;
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* This represents a single generic-association.  */

ସଂରଚନା c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  ବୃକ୍ଷ type;
  /* The association's expression.  */
  ସଂରଚନା c_ପଦସମଷ୍ଟି expression;
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

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_generic_selection (c_parser *parser)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି selector, error_ପଦସମଷ୍ଟି;
  ବୃକ୍ଷ selector_type;
  ସଂରଚନା c_generic_association matched_assoc;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା match_found = -1;
  location_t generic_loc, selector_loc;

  error_ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
  error_ପଦସମଷ୍ଟି.original_type = ଖାଲି;
  error_ପଦସମଷ୍ଟି.set_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_ବୃକ୍ଷ;
  matched_assoc.expression = error_ପଦସମଷ୍ଟି;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_GENERIC));
  generic_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  ଯଦି (flag_isoc99)
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C99 does not support %<_Generic%>");
  ଅନ୍ୟଥା
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C90 does not support %<_Generic%>");

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ error_ପଦସମଷ୍ଟି;

  selector_loc = c_parser_peek_token (parser)->location;
  ଯଦି (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      c_inhibit_evaluation_warnings++;
      pedwarn_c23 (selector_loc, OPT_Wpedantic,
		   "ISO C does not support use of type name as %<_Generic%> "
		   "controlling operand before C2Y");
      ସଂରଚନା c_type_name *type = c_parser_type_name (parser);
      ଯଦି (type)
	selector_type = groktypename (type, ଖାଲି, ଖାଲି);
      c_inhibit_evaluation_warnings--;
      ଯଦି (!type)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
	  ଫେରନ୍ତୁ error_ପଦସମଷ୍ଟି;
	}
    }
  ଅନ୍ୟଥା
    {
      c_inhibit_evaluation_warnings++;
      in_generic++;
      selector = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      in_generic--;
      କାଢ଼_maybe_used (!flag_isoc23);

      ଯଦି (selector.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
	  ଫେରନ୍ତୁ selector;
	}
      mark_exp_read (selector.ମୂଲ୍ୟ);
      selector_type = ବୃକ୍ଷ_TYPE (selector.ମୂଲ୍ୟ);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      ଯଦି (ବୃକ୍ଷ_CODE (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      ଯଦି (FUNCTION_POINTER_TYPE_P (selector_type)
	  && TYPE_QUALS (ବୃକ୍ଷ_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_pointer_type (TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (selector_type)));
    }

  ଯଦି (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
      ଫେରନ୍ତୁ error_ପଦସମଷ୍ଟି;
    }

  auto_vec<c_generic_association> associations;
  ସଂରଚନା maybe_used_decl *maybe_used_default = ଖାଲି;
  ଯେତେବେଳେ (1)
    {
      ସଂରଚନା c_generic_association assoc, *iter;
      unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      ଯଦି (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_ବୃକ୍ଷ;
	}
      ଅନ୍ୟଥା
	{
	  ସଂରଚନା c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  ଯଦି (type_name == ଖାଲି)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
	      ଫେରନ୍ତୁ error_ପଦସମଷ୍ଟି;
	    }
	  assoc.type = grokgenassoc (type_name);
	  ଯଦି (assoc.type == error_mark_ଗଣ୍ଠି)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
	      ଫେରନ୍ତୁ error_ପଦସମଷ୍ଟି;
	    }

	  ଯଦି (ବୃକ୍ଷ_CODE (assoc.type) == FUNCTION_TYPE)
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "function type before C2Y");
	  ଅନ୍ୟଥା ଯଦି (!COMPLETE_TYPE_P (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "incomplete type before C2Y");

	  ଯଦି (c_type_variably_modified_p (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "variably-modified type before C2Y");
	}

      ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
	  ଫେରନ୍ତୁ error_ପଦସମଷ୍ଟି;
	}

      ତାର୍କିକ match = assoc.type == NULL_ବୃକ୍ଷ
		   || comptypes (assoc.type, selector_type);

      ଯଦି (!match || matched_assoc.type != NULL_ବୃକ୍ଷ)
	c_inhibit_evaluation_warnings++;
      in_generic++;

      assoc.expression = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);

      ଯଦି (!match || matched_assoc.type != NULL_ବୃକ୍ଷ)
	c_inhibit_evaluation_warnings--;
      in_generic--;
      ଯଦି (!match)
	କାଢ଼_maybe_used (!flag_isoc23);
      ଅନ୍ୟଥା ଯଦି (assoc.type == NULL_ବୃକ୍ଷ)
	maybe_used_default = save_maybe_used ();
      ଅନ୍ୟଥା
	କାଢ଼_maybe_used (ସତ୍ୟ);

      ଯଦି (assoc.expression.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
	  ଫେରନ୍ତୁ error_ପଦସମଷ୍ଟି;
	}

      ପାଇଁ (ix = 0; associations.iterate (ix, &iter); ++ix)
	{
	  ଯଦି (assoc.type == NULL_ବୃକ୍ଷ)
	    {
	      ଯଦି (iter->type == NULL_ବୃକ୍ଷ)
		{
		  error_at (assoc.type_location,
			    "duplicate %<default%> case in %<_Generic%>");
		  inform (iter->type_location, "original %<default%> is here");
		}
	    }
	  ଅନ୍ୟଥା ଯଦି (iter->type != NULL_ବୃକ୍ଷ)
	    {
	      ଯଦି (comptypes (assoc.type, iter->type))
		{
		  error_at (assoc.type_location,
			    "%<_Generic%> specifies two compatible types");
		  inform (iter->type_location, "compatible type is here");
		}
	    }
	}

      ଯଦି (assoc.type == NULL_ବୃକ୍ଷ)
	{
	  ଯଦି (match_found < 0)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	}
      ଅନ୍ୟଥା ଯଦି (match)
	{
	  ଯଦି (match_found < 0 || matched_assoc.type == NULL_ବୃକ୍ଷ)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	  ଅନ୍ୟଥା
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.safe_ଠେଲ (assoc);

      ଯଦି (c_parser_peek_token (parser)->type != CPP_COMMA)
	ଭାଙ୍ଗ;
      c_parser_consume_token (parser);
    }

  ଯଦି (match_found >= 0 && matched_assoc.type == NULL_ବୃକ୍ଷ)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_used (maybe_used_default);
      କାଢ଼_maybe_used (ସତ୍ୟ);
    }
  ଅନ୍ୟଥା ଯଦି (maybe_used_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_used (maybe_used_default);
      କାଢ଼_maybe_used (!flag_isoc23);
    }

  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା ix;
  ସଂରଚନା c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    ଯଦି (ix != (unsigned) match_found)
      mark_exp_read (iter->expression.ମୂଲ୍ୟ);

  ଯଦି (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
      ଫେରନ୍ତୁ error_ପଦସମଷ୍ଟି;
    }

  ଯଦି (match_found < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      ଫେରନ୍ତୁ error_ପଦସମଷ୍ଟି;
    }

  ଫେରନ୍ତୁ matched_assoc.expression;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

ସ୍ଥିର unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା
check_tgmath_function (c_ପଦସମଷ୍ଟି *ପଦସମଷ୍ଟି, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା pos)
{
  ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି->ମୂଲ୍ୟ);
  ଯଦି (!FUNCTION_POINTER_TYPE_P (type))
    {
      error_at (ପଦସମଷ୍ଟି->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      ଫେରନ୍ତୁ 0;
    }
  type = ବୃକ୍ଷ_TYPE (type);
  ଯଦି (!prototype_p (type))
    {
      error_at (ପଦସମଷ୍ଟି->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      ଫେରନ୍ତୁ 0;
    }
  ଯଦି (stdarg_p (type))
    {
      error_at (ପଦସମଷ୍ଟି->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      ଫେରନ୍ତୁ 0;
    }
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା nargs = 0;
  function_args_iterator iter;
  ବୃକ୍ଷ t;
  FOREACH_FUNCTION_ARGS (type, t, iter)
    {
      ଯଦି (t == void_type_ଗଣ୍ଠି)
	ଭାଙ୍ଗ;
      nargs++;
    }
  ଯଦି (nargs == 0)
    {
      error_at (ପଦସମଷ୍ଟି->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      ଫେରନ୍ତୁ 0;
    }
  ଫେରନ୍ତୁ nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
ଗଣନା tgmath_parm_kind
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_predefined_identifier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ବାଛ (c_parser_peek_token (parser)->keyword)
    {
    ସ୍ଥିତି RID_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__FUNCTION__");
      ଭାଙ୍ଗ;
    ସ୍ଥିତି RID_PRETTY_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__PRETTY_FUNCTION__");
      ଭାଙ୍ଗ;
    ସ୍ଥିତି RID_C99_FUNCTION_NAME:
      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support "
		   "%<__func__%> predefined identifier");
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    }

  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
  ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
  ପଦସମଷ୍ଟି.original_type = ଖାଲି;
  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->ମୂଲ୍ୟ);
  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, loc);
  ପଦସମଷ୍ଟି.m_decimal = 0;
  c_parser_consume_token (parser);
  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

ସ୍ଥିର ତାର୍କିକ
has_counted_by_object (ବୃକ୍ଷ ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  ଯଦି ((ବୃକ୍ଷ_CODE (ref) == INDIRECT_REF
       && is_access_with_size_p (ବୃକ୍ଷ_OPERAND (ref, 0)))
      || is_access_with_size_p (ref))
    ଫେରନ୍ତୁ ସତ୍ୟ;
  ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* Get the reference to the counted-by object associated with the REF.  */

ସ୍ଥିର ବୃକ୍ଷ
get_counted_by_ref (ବୃକ୍ଷ ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  ଯଦି (ବୃକ୍ଷ_CODE (ref) == INDIRECT_REF
      && is_access_with_size_p (ବୃକ୍ଷ_OPERAND (ref, 0)))
    ଫେରନ୍ତୁ CALL_ପଦସମଷ୍ଟି_ARG (ବୃକ୍ଷ_OPERAND (ref, 0), 1);
  ଅନ୍ୟଥା ଯଦି (is_access_with_size_p (ref))
    ଫେରନ୍ତୁ CALL_ପଦସମଷ୍ଟି_ARG (ref, 1);

  ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
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

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_postfix_expression (c_parser *parser)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି, e1;
  ସଂରଚନା c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
  ପଦସମଷ୍ଟି.original_type = ଖାଲି;
  ପଦସମଷ୍ଟି.m_decimal = 0;
  ବାଛ (c_parser_peek_token (parser)->type)
    {
    ସ୍ଥିତି CPP_ସଂଖ୍ୟା:
      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, tok_range);
      loc = c_parser_peek_token (parser)->location;
      ପଦସମଷ୍ଟି.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == FIXED_CST
	  && !targetm.fixed_point_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  ପଦସମଷ୍ଟି.set_error ();
	}
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_CHAR:
    ସ୍ଥିତି CPP_CHAR16:
    ସ୍ଥିତି CPP_CHAR32:
    ସ୍ଥିତି CPP_UTF8CHAR:
    ସ୍ଥିତି CPP_WCHAR:
      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      ପଦସମଷ୍ଟି.original_type = char_type_ଗଣ୍ଠି;
      set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, tok_range);
      c_parser_consume_token (parser);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_STRING:
    ସ୍ଥିତି CPP_STRING16:
    ସ୍ଥିତି CPP_STRING32:
    ସ୍ଥିତି CPP_WSTRING:
    ସ୍ଥିତି CPP_UTF8STRING:
      ପଦସମଷ୍ଟି = c_parser_string_literal (parser, parser->translate_strings_p,
				      ସତ୍ୟ);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ
	= objc_build_string_object (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, tok_range);
      c_parser_consume_token (parser);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_NAME:
      ବାଛ (c_parser_peek_token (parser)->id_kind)
	{
	ସ୍ଥିତି C_ID_ID:
	  {
	    ବୃକ୍ଷ id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	    c_parser_consume_token (parser);
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &ପଦସମଷ୍ଟି.original_type);
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, tok_range);
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    ବୃକ୍ଷ class_name = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	    ବୃକ୍ଷ component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    ଯଦି (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->ମୂଲ୍ୟ;
	    location_t end_loc = component_tok->get_finish ();
	    c_parser_consume_token (parser);
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = objc_build_class_component_ref (class_name,
							 component);
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, end_loc);
	    ଭାଙ୍ଗ;
	  }
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  c_parser_error (parser, "expected expression");
	  ପଦସମଷ୍ଟି.set_error ();
	  ଭାଙ୍ଗ;
	}
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_OPEN_PAREN:
      /* A parenthesized expression, statement expression or compound
	 literal.  */
      ଯଦି (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_BRACE)
	{
	  /* A statement expression.  */
	  ବୃକ୍ଷ stmt;
	  location_t brace_loc;
	  ତାର୍କିକ save_c_omp_array_section_p = c_omp_array_section_p;
	  c_parser_consume_token (parser);
	  brace_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* If we've not yet started the current function's statement list,
	     or we're in the parameter scope of an old-style function
	     declaration, statement expressions are not allowed.  */
	  ଯଦି (!building_stmt_list_p () || old_style_parameter_scope ())
	    {
	      error_at (loc, "braced-group within expression allowed "
			"only inside a function");
	      parser->error = ସତ୍ୟ;
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ଖାଲି);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
	      ପଦସମଷ୍ଟି.set_error ();
	      ଭାଙ୍ଗ;
	    }
	  c_omp_array_section_p = ମିଥ୍ୟା;
	  stmt = c_begin_stmt_ପଦସମଷ୍ଟି ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_finish_stmt_ପଦସମଷ୍ଟି (brace_loc, stmt);
	  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_loc);
	  mark_exp_read (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      ଅନ୍ୟଥା
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  ପଦସମଷ୍ଟି = c_parser_expression (parser);
	  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == MODIFY_ପଦସମଷ୍ଟି)
	    suppress_warning (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, OPT_Wparentheses);
	  ଯଦି (ପଦସମଷ୍ଟି.original_code != C_MAYBE_CONST_ପଦସମଷ୍ଟି
	      && ପଦସମଷ୍ଟି.original_code != SIZEOF_ପଦସମଷ୍ଟି)
	    ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  ଯଦି (ପଦସମଷ୍ଟି.original_code == SIZEOF_ପଦସମଷ୍ଟି)
	    ପଦସମଷ୍ଟି.original_code = PAREN_SIZEOF_ପଦସମଷ୍ଟି;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_KEYWORD:
      ବାଛ (c_parser_peek_token (parser)->keyword)
	{
	ସ୍ଥିତି RID_FUNCTION_NAME:
	ସ୍ଥିତି RID_PRETTY_FUNCTION_NAME:
	ସ୍ଥିତି RID_C99_FUNCTION_NAME:
	  ପଦସମଷ୍ଟି = c_parser_predefined_identifier (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_VA_ARG:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ଯଦି (!parens.require_open (parser))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    e1 = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	    mark_exp_read (e1.ମୂଲ୍ୟ);
	    e1.ମୂଲ୍ୟ = c_fully_fold (e1.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
	    ଯଦି (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ଯଦି (t1 == ଖାଲି)
	      {
		ପଦସମଷ୍ଟି.set_error ();
	      }
	    ଅନ୍ୟଥା
	      {
		ବୃକ୍ଷ type_ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
		ବୃକ୍ଷ type = groktypename (t1, &type_ପଦସମଷ୍ଟି, ଖାଲି);
		ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_build_va_arg (start_loc, e1.ମୂଲ୍ୟ, loc,
					     type, type_ପଦସମଷ୍ଟି);
		set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, start_loc, end_loc);
	      }
	  }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_C23_VA_START:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ଯଦି (!parens.require_open (parser))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    e1 = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	    e1 = convert_lvalue_to_rvalue (e1.get_location (), e1, ସତ୍ୟ, ସତ୍ୟ);
	    ଯଦି (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		ଯଦି (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
		    ପଦସମଷ୍ଟି.set_error ();
		    ଭାଙ୍ଗ;
		  }
		ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_kind == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    ବୃକ୍ଷ name = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    ବୃକ୍ଷ decl = lookup_name (name);
		    ବୃକ୍ଷ last_parm
		      = ବୃକ୍ଷ_last (DECL_ARGUMENTS (current_function_decl));
		    ଯଦି (!last_parm || decl != last_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    ଅନ୍ୟଥା ଯଦି (DECL_REGISTER (decl))
		      warning_at (nloc, OPT_Wvarargs,
				  "undefined behavior when second parameter "
				  "of %<va_start%> is declared with "
				  "%<register%> storage");
		    c_parser_consume_token (parser);
		  }
		ଅନ୍ୟଥା
		  {
		    unsigned nesting_depth = 0;
		    location_t sloc = c_parser_peek_token (parser)->location;
		    location_t eloc = sloc;

		    /* For va_start (ap,) the ) comes from stdarg.h.
		       Use location of , in that case, otherwise without
		       -Wsystem-headers nothing is reported.  After all,
		       the problematic token is the comma in that case.  */
		    ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    ଯେତେବେଳେ (ସତ୍ୟ)
		      {
			c_token *token = c_parser_peek_token (parser);
			ଯଦି (token->type == CPP_CLOSE_PAREN && !nesting_depth)
			  ଭାଙ୍ଗ;

			ଯଦି (token->type == CPP_EOF)
			  ଭାଙ୍ଗ;
			ଯଦି (token->type == CPP_OPEN_PAREN)
			  ++nesting_depth;
			ଅନ୍ୟଥା ଯଦି (token->type == CPP_CLOSE_PAREN)
			  --nesting_depth;
			eloc = token->location;
			c_parser_consume_token (parser);
		      }
		    ଯଦି (sloc != eloc)
		      sloc = make_location (sloc, sloc, eloc);
		    warning_at (sloc, OPT_Wvarargs,
				"%<va_start%> macro used with additional "
				"arguments other than identifier of the "
				"last named argument");
		  }
	      }
	    parens.skip_until_found_close (parser);
	    ବୃକ୍ଷ fndecl = builtin_decl_explicit (BUILT_IN_VA_START);
	    vec<ବୃକ୍ଷ, va_gc> *params;
	    vec_alloc (params, 2);
	    params->quick_ଠେଲ (e1.ମୂଲ୍ୟ);
	    params->quick_ଠେଲ (integer_zero_ଗଣ୍ଠି);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.quick_ଠେଲ (e1.get_location ());
	    arg_loc.quick_ଠେଲ (UNKNOWN_LOCATION);
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, ଖାଲି);
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc,
				     parser->tokens_buf[0].get_finish ());
	    ପଦସମଷ୍ଟି.m_decimal = 0;
	    ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
	    ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	    release_ବୃକ୍ଷ_vector (params);
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ଯଦି (!parens.require_open (parser))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    t1 = c_parser_type_name (parser);
	    ଯଦି (t1 == ଖାଲି)
	      parser->error = ସତ୍ୟ;
	    ଯଦି (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    ଯଦି (parser->error)
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ବୃକ୍ଷ type = groktypename (t1, ଖାଲି, ଖାଲି);
	    ବୃକ୍ଷ offsetof_ref;
	    ଯଦି (type == error_mark_ଗଣ୍ଠି)
	      offsetof_ref = error_mark_ଗଣ୍ଠି;
	    ଅନ୍ୟଥା
	      {
		offsetof_ref = build1 (INDIRECT_REF, type, null_pointer_ଗଣ୍ଠି);
		SET_ପଦସମଷ୍ଟି_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->ମୂଲ୍ୟ,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_DOT)
		       || c_parser_next_token_is (parser,
						  CPP_OPEN_SQUARE)
		       || c_parser_next_token_is (parser,
						  CPP_DEREF))
		  {
		    ଯଦି (c_parser_next_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_ଗଣ୍ଠି);
			ଯାଅ do_dot;
		      }
		    ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			ଯଦି (c_parser_next_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    ଭାଙ୍ଗ;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->ମୂଲ୍ୟ,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    ଅନ୍ୟଥା
		      {
			ସଂରଚନା c_ପଦସମଷ୍ଟି ce;
			ବୃକ୍ଷ idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_expression (parser);
			ce = convert_lvalue_to_rvalue (loc, ce, ମିଥ୍ୟା, ମିଥ୍ୟା);
			idx = ce.ମୂଲ୍ୟ;
			idx = c_fully_fold (idx, ମିଥ୍ୟା, ଖାଲି);
			c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
						   "expected %<]%>");
			offsetof_ref = build_array_ref (loc, offsetof_ref, idx);
		      }
		  }
	      }
	    ଅନ୍ୟଥା
	      c_parser_error (parser, "expected identifier");
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = fold_offsetof (offsetof_ref);
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, end_loc);
	  }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_CHOOSE_ପଦସମଷ୍ଟି:
	  {
	    vec<c_ପଦସମଷ୍ଟି_t, va_gc> *cexpr_list;
	    c_ପଦସମଷ୍ଟି_t *e1_p, *e2_p, *e3_p;
	    ବୃକ୍ଷ c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ଯଦି (!c_parser_get_builtin_args (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, ସତ୍ୟ,
					    &close_paren_loc))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    ଯଦି (vec_safe_length (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->ମୂଲ୍ୟ;
	    mark_exp_read (e2_p->ମୂଲ୍ୟ);
	    mark_exp_read (e3_p->ମୂଲ୍ୟ);
	    ଯଦି (ବୃକ୍ଷ_CODE (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_expression_warning (c);
	    ପଦସମଷ୍ଟି = integer_zerop (c) ? *e3_p : *e2_p;
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_paren_loc);
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ଯଦି (!parens.require_open (parser))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    t1 = c_parser_type_name (parser);
	    ଯଦି (t1 == ଖାଲି)
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    t2 = c_parser_type_name (parser);
	    ଯଦି (t2 == ଖାଲି)
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    ବୃକ୍ଷ e1, e2;
	    e1 = groktypename (t1, ଖାଲି, ଖାଲି);
	    e2 = groktypename (t2, ଖାଲି, ଖାଲି);
	    ଯଦି (e1 == error_mark_ଗଣ୍ଠି || e2 == error_mark_ଗଣ୍ଠି)
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ
	      = comptypes (e1, e2) ? integer_one_ଗଣ୍ଠି : integer_zero_ଗଣ୍ଠି;
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_paren_loc);
	  }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_BUILTIN_TGMATH:
	  {
	    vec<c_ପଦସମଷ୍ଟି_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ଯଦି (!c_parser_get_builtin_args (parser,
					    "__builtin_tgmath",
					    &cexpr_list, ମିଥ୍ୟା,
					    &close_paren_loc))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    ଯଦି (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
	    c_ପଦସମଷ୍ଟି_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, ସତ୍ୟ, ସତ୍ୟ);
	    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    ଯଦି (nargs == 0)
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (vec_safe_length (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_functions = vec_safe_length (cexpr_list) - nargs;
	    ଯଦି (ଅଙ୍କ_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 1; j < ଅଙ୍କ_functions; j++)
	      {
		unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		ଯଦି (this_nargs == 0)
		  {
		    ପଦସମଷ୍ଟି.set_error ();
		    ଯାଅ out;
		  }
		ଯଦି (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    ପଦସମଷ୍ଟି.set_error ();
		    ଯାଅ out;
		  }
	      }

	    /* The functions all have the same number of arguments.
	       Determine whether arguments and return types vary in
	       ways permitted for <tgmath.h> functions.  */
	    /* The first entry in each of these vectors is for the
	       return type, subsequent entries for parameter
	       types.  */
	    auto_vec<ଗଣନା tgmath_parm_kind> parm_kind (nargs + 1);
	    auto_vec<ବୃକ୍ଷ> parm_first (nargs + 1);
	    auto_vec<ତାର୍କିକ> parm_complex (nargs + 1);
	    auto_vec<ତାର୍କିକ> parm_varies (nargs + 1);
	    ବୃକ୍ଷ first_type = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE ((*cexpr_list)[0].ମୂଲ୍ୟ));
	    ବୃକ୍ଷ first_ret = TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (first_type));
	    parm_first.quick_ଠେଲ (first_ret);
	    parm_complex.quick_ଠେଲ (ବୃକ୍ଷ_CODE (first_ret) == COMPLEX_TYPE);
	    parm_varies.quick_ଠେଲ (ମିଥ୍ୟା);
	    function_args_iterator iter;
	    ବୃକ୍ଷ t;
	    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା argpos;
	    FOREACH_FUNCTION_ARGS (first_type, t, iter)
	      {
		ଯଦି (t == void_type_ଗଣ୍ଠି)
		  ଭାଙ୍ଗ;
		parm_first.quick_ଠେଲ (TYPE_MAIN_VARIANT (t));
		parm_complex.quick_ଠେଲ (ବୃକ୍ଷ_CODE (t) == COMPLEX_TYPE);
		parm_varies.quick_ଠେଲ (ମିଥ୍ୟା);
	      }
	    ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 1; j < ଅଙ୍କ_functions; j++)
	      {
		ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE ((*cexpr_list)[j].ମୂଲ୍ୟ));
		ବୃକ୍ଷ ret = TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (type));
		ଯଦି (ret != parm_first[0])
		  {
		    parm_varies[0] = ସତ୍ୟ;
		    ଯଦି (!SCALAR_FLOAT_TYPE_P (parm_first[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_first[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			ପଦସମଷ୍ଟି.set_error ();
			ଯାଅ out;
		      }
		    ଯଦି (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			ପଦସମଷ୍ଟି.set_error ();
			ଯାଅ out;
		      }
		  }
		ଯଦି (ବୃକ୍ଷ_CODE (ret) == COMPLEX_TYPE)
		  parm_complex[0] = ସତ୍ୟ;
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    ଯଦି (t == void_type_ଗଣ୍ଠି)
		      ଭାଙ୍ଗ;
		    t = TYPE_MAIN_VARIANT (t);
		    ଯଦି (t != parm_first[argpos])
		      {
			parm_varies[argpos] = ସତ୍ୟ;
			ଯଦି (!SCALAR_FLOAT_TYPE_P (parm_first[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_first[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    ପଦସମଷ୍ଟି.set_error ();
			    ଯାଅ out;
			  }
			ଯଦି (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    ପଦସମଷ୍ଟି.set_error ();
			    ଯାଅ out;
			  }
		      }
		    ଯଦି (ବୃକ୍ଷ_CODE (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = ସତ୍ୟ;
		    argpos++;
		  }
	      }
	    ଗଣନା tgmath_parm_kind max_variation = tgmath_fixed;
	    ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j <= nargs; j++)
	      {
		ଗଣନା tgmath_parm_kind this_kind;
		ଯଦି (parm_varies[j])
		  {
		    ଯଦି (parm_complex[j])
		      max_variation = this_kind = tgmath_complex;
		    ଅନ୍ୟଥା
		      {
			this_kind = tgmath_real;
			ଯଦି (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		ଅନ୍ୟଥା
		  this_kind = tgmath_fixed;
		parm_kind.quick_ଠେଲ (this_kind);
	      }
	    ଯଦି (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା tgarg = 0;
	    ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 1; j <= nargs; j++)
	      ଯଦି (parm_kind[j] == max_variation)
		{
		  tgarg = j;
		  ଭାଙ୍ଗ;
		}
	    ଯଦି (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<ବୃକ୍ଷ> tg_type (ଅଙ୍କ_functions);
	    ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < ଅଙ୍କ_functions; j++)
	      {
		ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE ((*cexpr_list)[j].ମୂଲ୍ୟ));
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    ଯଦି (argpos == tgarg)
		      {
			tg_type.quick_ଠେଲ (TYPE_MAIN_VARIANT (t));
			ଭାଙ୍ଗ;
		      }
		    argpos++;
		  }
	      }

	    /* Verify that the corresponding types are different for
	       all the listed functions.  Also determine whether all
	       the types are complex, whether all the types are
	       standard or binary, and whether all the types are
	       decimal.  */
	    ତାର୍କିକ all_complex = ସତ୍ୟ;
	    ତାର୍କିକ all_ଦ୍ୱିମିକ = ସତ୍ୟ;
	    ତାର୍କିକ all_decimal = ସତ୍ୟ;
	    hash_set<ବୃକ୍ଷ> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		ଯଦି (ବୃକ୍ଷ_CODE (t) == COMPLEX_TYPE)
		  all_decimal = ମିଥ୍ୟା;
		ଅନ୍ୟଥା
		  {
		    all_complex = ମିଥ୍ୟା;
		    ଯଦି (DECIMAL_FLOAT_TYPE_P (t))
		      all_ଦ୍ୱିମିକ = ମିଥ୍ୟା;
		    ଅନ୍ୟଥା
		      all_decimal = ମିଥ୍ୟା;
		  }
		ଯଦି (tg_types.add (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    ପଦସମଷ୍ଟି.set_error ();
		    ଯାଅ out;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < ଅଙ୍କ_functions; j++)
	      {
		ବୃକ୍ଷ exp_type = tg_type[j];
		ବୃକ୍ଷ exp_real_type = exp_type;
		ଯଦି (ବୃକ୍ଷ_CODE (exp_type) == COMPLEX_TYPE)
		  exp_real_type = ବୃକ୍ଷ_TYPE (exp_type);
		ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE ((*cexpr_list)[j].ମୂଲ୍ୟ));
		ବୃକ୍ଷ ret = TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (type));
		ଯଦି ((parm_kind[0] == tgmath_complex && ret != exp_type)
		    || (parm_kind[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    ପଦସମଷ୍ଟି.set_error ();
		    ଯାଅ out;
		  }
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    ଯଦି (t == void_type_ଗଣ୍ଠି)
		      ଭାଙ୍ଗ;
		    t = TYPE_MAIN_VARIANT (t);
		    ଯଦି ((parm_kind[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_kind[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			ପଦସମଷ୍ଟି.set_error ();
			ଯାଅ out;
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
	    ତାର୍କିକ arg_complex = all_complex;
	    ତାର୍କିକ arg_ଦ୍ୱିମିକ = all_ଦ୍ୱିମିକ;
	    ତାର୍କିକ arg_int_decimal = all_decimal;
	    ତାର୍କିକ arg_int_floatnx = ମିଥ୍ୟା;
	    ତାର୍କିକ arg_int_decimalx = ମିଥ୍ୟା;
	    ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 1; j <= nargs; j++)
	      {
		ଯଦି (parm_kind[j] == tgmath_fixed)
		  ଜାରି;
		c_ପଦସମଷ୍ଟି_t *ce = &(*cexpr_list)[ଅଙ୍କ_functions + j - 1];
		ବୃକ୍ଷ type = ବୃକ୍ଷ_TYPE (ce->ମୂଲ୍ୟ);
		ଯଦି (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && ବୃକ୍ଷ_CODE (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    ପଦସମଷ୍ଟି.set_error ();
		    ଯାଅ out;
		  }
		ଯଦି (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = ସତ୍ୟ;
		    ଯଦି (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			ପଦସମଷ୍ଟି.set_error ();
			ଯାଅ out;
		      }
		    ଅନ୍ୟଥା ଯଦି (all_ଦ୍ୱିମିକ)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			ପଦସମଷ୍ଟି.set_error ();
			ଯାଅ out;
		      }
		    ଅନ୍ୟଥା ଯଦି (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			ପଦସମଷ୍ଟି.set_error ();
			ଯାଅ out;
		      }
		    ଅନ୍ୟଥା ଯଦି (arg_ଦ୍ୱିମିକ)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			ପଦସମଷ୍ଟି.set_error ();
			ଯାଅ out;
		      }
		  }
		ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == COMPLEX_TYPE)
		  {
		    arg_complex = ସତ୍ୟ;
		    ଯଦି (COMPLEX_FLOAT_TYPE_P (type))
		      arg_ଦ୍ୱିମିକ = ସତ୍ୟ;
		    ଯଦି (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			ପଦସମଷ୍ଟି.set_error ();
			ଯାଅ out;
		      }
		    ଅନ୍ୟଥା ଯଦି (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			ପଦସମଷ୍ଟି.set_error ();
			ଯାଅ out;
		      }
		  }
		ଅନ୍ୟଥା ଯଦି (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_ଦ୍ୱିମିକ = ସତ୍ୟ;
		    ଯଦି (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			ପଦସମଷ୍ଟି.set_error ();
			ଯାଅ out;
		      }
		    ଅନ୍ୟଥା ଯଦି (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			ପଦସମଷ୍ଟି.set_error ();
			ଯାଅ out;
		      }
		  }
		ବୃକ୍ଷ rtype = TYPE_MAIN_VARIANT (type);
		ଯଦି (ବୃକ୍ଷ_CODE (rtype) == COMPLEX_TYPE)
		  rtype = ବୃକ୍ଷ_TYPE (rtype);
		ଯଦି (SCALAR_FLOAT_TYPE_P (rtype))
		  ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < ଅଙ୍କ_FLOATNX_TYPES; j++)
		    ଯଦି (rtype == FLOATNX_TYPE_ଗଣ୍ଠି (j))
		      {
			arg_int_floatnx = ସତ୍ୟ;
			ଭାଙ୍ଗ;
		      }
		ଯଦି (rtype == dfloat64x_type_ଗଣ୍ଠି)
		  arg_int_decimalx = ସତ୍ୟ;
	      }
	    ବୃକ୍ଷ arg_real = NULL_ବୃକ୍ଷ;
	    ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 1; j <= nargs; j++)
	      {
		ଯଦି (parm_kind[j] == tgmath_fixed)
		  ଜାରି;
		c_ପଦସମଷ୍ଟି_t *ce = &(*cexpr_list)[ଅଙ୍କ_functions + j - 1];
		ବୃକ୍ଷ type = TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (ce->ମୂଲ୍ୟ));
		ଯଦି (ବୃକ୍ଷ_CODE (type) == COMPLEX_TYPE)
		  type = ବୃକ୍ଷ_TYPE (type);
		ଯଦି (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_ଗଣ୍ଠି
			  : arg_int_floatnx
			  ? float32x_type_ଗଣ୍ଠି
			  : arg_int_decimal
			  ? dfloat64_type_ଗଣ୍ଠି
			  : double_type_ଗଣ୍ଠି);
		ଯଦି (arg_real == NULL_ବୃକ୍ଷ)
		  arg_real = type;
		ଅନ୍ୟଥା
		  arg_real = common_type (arg_real, type);
		ଯଦି (arg_real == error_mark_ଗଣ୍ଠି)
		  {
		    ପଦସମଷ୍ଟି.set_error ();
		    ଯାଅ out;
		  }
	      }
	    ବୃକ୍ଷ arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_ପଦସମଷ୍ଟି_t *fn = ଖାଲି;
	    ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < ଅଙ୍କ_functions; j++)
	      {
		ଯଦି (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    ଭାଙ୍ଗ;
		  }
	      }
	    ଯଦି (fn == ଖାଲି
		&& parm_kind[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_first[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < ଅଙ୍କ_functions; j++)
		  {
		    ଯଦି (arg_complex
			!= (ବୃକ୍ଷ_CODE (tg_type[j]) == COMPLEX_TYPE))
		      ଜାରି;
		    ବୃକ୍ଷ real_tg_type = (arg_complex
					 ? ବୃକ୍ଷ_TYPE (tg_type[j])
					 : tg_type[j]);
		    ଯଦି (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      ଜାରି;
		    scalar_float_mode arg_mode
		      = SCALAR_FLOAT_TYPE_MODE (arg_real);
		    scalar_float_mode tg_mode
		      = SCALAR_FLOAT_TYPE_MODE (real_tg_type);
		    ଅଚଳ real_format *arg_fmt = REAL_MODE_FORMAT (arg_mode);
		    ଅଚଳ real_format *tg_fmt = REAL_MODE_FORMAT (tg_mode);
		    ଯଦି (arg_fmt->b == tg_fmt->b
			&& arg_fmt->p <= tg_fmt->p
			&& arg_fmt->emax <= tg_fmt->emax
			&& (arg_fmt->emin - arg_fmt->p
			    >= tg_fmt->emin - tg_fmt->p))
		      {
			fn = &(*cexpr_list)[j];
			ଭାଙ୍ଗ;
		      }
		  }
	      }
	    ଯଦି (fn == ଖାଲି)
	      {
		error_at (loc, "no matching function for type-generic call");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    /* Construct a call to FN.  */
	    vec<ବୃକ୍ଷ, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<ବୃକ୍ଷ, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < nargs; j++)
	      {
		c_ପଦସମଷ୍ଟି_t *ce = &(*cexpr_list)[ଅଙ୍କ_functions + j];
		args->quick_ଠେଲ (ce->ମୂଲ୍ୟ);
		arg_loc.quick_ଠେଲ (ce->get_location ());
		origtypes->quick_ଠେଲ (ce->original_type);
	      }
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_build_function_call_vec (loc, arg_loc, fn->ମୂଲ୍ୟ,
						    args, origtypes);
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_paren_loc);
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_ପଦସମଷ୍ଟି_t, va_gc> *cexpr_list;
	    c_ପଦସମଷ୍ଟି_t *e2_p;
	    ବୃକ୍ଷ chain_ମୂଲ୍ୟ;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ଯଦି (!c_parser_get_builtin_args (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, ମିଥ୍ୟା,
					    &close_paren_loc))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    ପଦସମଷ୍ଟି = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, ସତ୍ୟ, ସତ୍ୟ);
	    chain_ମୂଲ୍ୟ = e2_p->ମୂଲ୍ୟ;
	    mark_exp_read (chain_ମୂଲ୍ୟ);

	    ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) != CALL_ପଦସମଷ୍ଟି)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (chain_ମୂଲ୍ୟ)) != POINTER_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    ଅନ୍ୟଥା
	      CALL_ପଦସମଷ୍ଟି_STATIC_CHAIN (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) = chain_ମୂଲ୍ୟ;
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_paren_loc);
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି RID_BUILTIN_COMPLEX:
	  {
	    vec<c_ପଦସମଷ୍ଟି_t, va_gc> *cexpr_list;
	    c_ପଦସମଷ୍ଟି_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ଯଦି (!c_parser_get_builtin_args (parser,
					    "__builtin_complex",
					    &cexpr_list, ମିଥ୍ୟା,
					    &close_paren_loc))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    ଯଦି (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_to_rvalue (loc, *e1_p, ସତ୍ୟ, ସତ୍ୟ);
	    ଯଦି (ବୃକ୍ଷ_CODE (e1_p->ମୂଲ୍ୟ) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
	      e1_p->ମୂଲ୍ୟ = convert (ବୃକ୍ଷ_TYPE (e1_p->ମୂଲ୍ୟ),
				     ବୃକ୍ଷ_OPERAND (e1_p->ମୂଲ୍ୟ, 0));
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, ସତ୍ୟ, ସତ୍ୟ);
	    ଯଦି (ବୃକ୍ଷ_CODE (e2_p->ମୂଲ୍ୟ) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
	      e2_p->ମୂଲ୍ୟ = convert (ବୃକ୍ଷ_TYPE (e2_p->ମୂଲ୍ୟ),
				     ବୃକ୍ଷ_OPERAND (e2_p->ମୂଲ୍ୟ, 0));
	    ଯଦି (!SCALAR_FLOAT_TYPE_P (ବୃକ୍ଷ_TYPE (e1_p->ମୂଲ୍ୟ))
		|| DECIMAL_FLOAT_TYPE_P (ବୃକ୍ଷ_TYPE (e1_p->ମୂଲ୍ୟ))
		|| !SCALAR_FLOAT_TYPE_P (ବୃକ୍ଷ_TYPE (e2_p->ମୂଲ୍ୟ))
		|| DECIMAL_FLOAT_TYPE_P (ବୃକ୍ଷ_TYPE (e2_p->ମୂଲ୍ୟ)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (e1_p->ମୂଲ୍ୟ))
		!= TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (e2_p->ମୂଲ୍ୟ)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build2_loc (loc, COMPLEX_ପଦସମଷ୍ଟି,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (ବୃକ୍ଷ_TYPE (e1_p->ମୂଲ୍ୟ))),
				     e1_p->ମୂଲ୍ୟ, e2_p->ମୂଲ୍ୟ);
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_paren_loc);
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_ପଦସମଷ୍ଟି_t, va_gc> *cexpr_list;
	    c_ପଦସମଷ୍ଟି_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ଯଦି (!c_parser_get_builtin_args (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, ମିଥ୍ୟା,
					    &close_paren_loc))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    e_p = &(*cexpr_list)[0];
	    ବୃକ୍ଷ ref = e_p->ମୂଲ୍ୟ;

	    ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ref)) != ARRAY_TYPE
		 && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ref)) != POINTER_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    ଯଦି (ବୃକ୍ଷ_CODE (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    ଯଦି (ବୃକ୍ଷ_CODE (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    ଯଦି (has_counted_by_object (ref))
	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = get_counted_by_ref (ref);
	    ଅନ୍ୟଥା
	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = null_pointer_ଗଣ୍ଠି;

	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_paren_loc);
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_ପଦସମଷ୍ଟି_t, va_gc> *cexpr_list;
	    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
	    c_ପଦସମଷ୍ଟି_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ଯଦି (!c_parser_get_builtin_args (parser,
					    "__builtin_shuffle",
					    &cexpr_list, ମିଥ୍ୟା,
					    &close_paren_loc))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, ସତ୍ୟ, ସତ୍ୟ);

	    ଯଦି (vec_safe_length (cexpr_list) == 2)
	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_build_vec_perm_ପଦସମଷ୍ଟି (loc, (*cexpr_list)[0].ମୂଲ୍ୟ,
						  NULL_ବୃକ୍ଷ,
						  (*cexpr_list)[1].ମୂଲ୍ୟ);

	    ଅନ୍ୟଥା ଯଦି (vec_safe_length (cexpr_list) == 3)
	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_build_vec_perm_ପଦସମଷ୍ଟି (loc, (*cexpr_list)[0].ମୂଲ୍ୟ,
						  (*cexpr_list)[1].ମୂଲ୍ୟ,
						  (*cexpr_list)[2].ମୂଲ୍ୟ);
	    ଅନ୍ୟଥା
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		ପଦସମଷ୍ଟି.set_error ();
	      }
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_paren_loc);
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_ପଦସମଷ୍ଟି_t, va_gc> *cexpr_list;
	    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
	    c_ପଦସମଷ୍ଟି_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ଯଦି (!c_parser_get_builtin_args (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, ମିଥ୍ୟା,
					    &close_paren_loc))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, ସତ୍ୟ, ସତ୍ୟ);

	    ଯଦି (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		ପଦସମଷ୍ଟି.set_error ();
	      }
	    ଅନ୍ୟଥା
	      {
		auto_vec<ବୃକ୍ଷ, 16> mask;
		ପାଇଁ (i = 2; i < cexpr_list->length (); ++i)
		  mask.safe_ଠେଲ ((*cexpr_list)[i].ମୂଲ୍ୟ);
		ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_build_shufflevector (loc, (*cexpr_list)[0].ମୂଲ୍ୟ,
						    (*cexpr_list)[1].ମୂଲ୍ୟ,
						    mask);
	      }
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_paren_loc);
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ଯଦି (!parens.require_open (parser))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    e1 = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	    mark_exp_read (e1.ମୂଲ୍ୟ);
	    ଯଦି (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ଯଦି (t1 == ଖାଲି)
	      ପଦସମଷ୍ଟି.set_error ();
	    ଅନ୍ୟଥା
	      {
		ବୃକ୍ଷ type_ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
		ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_build_vec_convert (start_loc, e1.ମୂଲ୍ୟ, loc,
						  groktypename (t1, &type_ପଦସମଷ୍ଟି,
								ଖାଲି));
		set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, start_loc, end_loc);
	      }
	  }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ଯଦି (!parens.require_open (parser))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    e1 = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	    mark_exp_read (e1.ମୂଲ୍ୟ);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    parens.skip_until_found_close (parser);
	    ପଦସମଷ୍ଟି = parser_build_unary_op (loc, PAREN_ପଦସମଷ୍ଟି, e1);
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, start_loc, end_loc);
	  }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_BUILTIN_STDC:
	  {
	    vec<c_ପଦସମଷ୍ଟି_t, va_gc> *cexpr_list;
	    c_ପଦସମଷ୍ଟି_t *arg_p;
	    location_t close_paren_loc;
	    ଗଣନା c_builtin_stdc {
	      C_BUILTIN_STDC_BIT_CEIL,
	      C_BUILTIN_STDC_BIT_FLOOR,
	      C_BUILTIN_STDC_BIT_WIDTH,
	      C_BUILTIN_STDC_ଗଣନା_ONES,
	      C_BUILTIN_STDC_ଗଣନା_ZEROS,
	      C_BUILTIN_STDC_FIRST_LEADING_ONE,
	      C_BUILTIN_STDC_FIRST_LEADING_ZERO,
	      C_BUILTIN_STDC_FIRST_TRAILING_ONE,
	      C_BUILTIN_STDC_FIRST_TRAILING_ZERO,
	      C_BUILTIN_STDC_HAS_SINGLE_BIT,
	      C_BUILTIN_STDC_LEADING_ONES,
	      C_BUILTIN_STDC_LEADING_ZEROS,
	      C_BUILTIN_STDC_ROTATE_ବାମ,
	      C_BUILTIN_STDC_ROTATE_ଡାହାଣ,
	      C_BUILTIN_STDC_TRAILING_ONES,
	      C_BUILTIN_STDC_TRAILING_ZEROS,
	      C_BUILTIN_STDC_MAX
	    } stdc_rid = C_BUILTIN_STDC_MAX;
	    ଅଚଳ ଅକ୍ଷର *name
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	    unsigned ଅଙ୍କ_args = 1;
	    ବାଛ (name[ଆକାର ("__builtin_stdc_") - 1])
	      {
	      ସ୍ଥିତି 'b':
		ବାଛ (name[ଆକାର ("__builtin_stdc_bit_") - 1])
		  {
		  ସ୍ଥିତି 'c':
		    stdc_rid = C_BUILTIN_STDC_BIT_CEIL;
		    ଭାଙ୍ଗ;
		  ସ୍ଥିତି 'f':
		    stdc_rid = C_BUILTIN_STDC_BIT_FLOOR;
		    ଭାଙ୍ଗ;
		  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		    stdc_rid = C_BUILTIN_STDC_BIT_WIDTH;
		    ଭାଙ୍ଗ;
		  }
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି 'c':
		ଯଦି (name[ଆକାର ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_ଗଣନା_ONES;
		ଅନ୍ୟଥା
		  stdc_rid = C_BUILTIN_STDC_ଗଣନା_ZEROS;
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି 'f':
		ବାଛ (name[ଆକାର ("__builtin_stdc_first_trailing_") - 1])
		  {
		  ସ୍ଥିତି 'n':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ONE;
		    ଭାଙ୍ଗ;
		  ସ୍ଥିତି 'e':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ZERO;
		    ଭାଙ୍ଗ;
		  ସ୍ଥିତି 'o':
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ONE;
		    ଭାଙ୍ଗ;
		  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ZERO;
		    ଭାଙ୍ଗ;
		  }
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_BIT;
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି 'l':
		ଯଦି (name[ଆକାର ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		ଅନ୍ୟଥା
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି 'r':
		ଯଦି (name[ଆକାର ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_ବାମ;
		ଅନ୍ୟଥା
		  stdc_rid = C_BUILTIN_STDC_ROTATE_ଡାହାଣ;
		ଅଙ୍କ_args = 2;
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି 't':
		ଯଦି (name[ଆକାର ("__builtin_stdc_trailing_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ONES;
		ଅନ୍ୟଥା
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ZEROS;
		ଭାଙ୍ଗ;
	      }
	    gcc_checking_assert (stdc_rid != C_BUILTIN_STDC_MAX);

	    c_parser_consume_token (parser);
	    ଯଦି (!c_parser_get_builtin_args (parser, name,
					    &cexpr_list, ମିଥ୍ୟା,
					    &close_paren_loc))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    ଯଦି (vec_safe_length (cexpr_list) != ଅଙ୍କ_args)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, ସତ୍ୟ, ସତ୍ୟ);
	    ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (arg_p->ମୂଲ୍ୟ)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (arg_p->ମୂଲ୍ୟ)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (arg_p->ମୂଲ୍ୟ)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (!TYPE_UNSIGNED (ବୃକ୍ଷ_TYPE (arg_p->ମୂଲ୍ୟ)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (arg_p->ମୂଲ୍ୟ))
		== char_type_ଗଣ୍ଠି)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ବୃକ୍ଷ arg = arg_p->ମୂଲ୍ୟ;
	    ବୃକ୍ଷ type = TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (arg));
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
	    ପୂର୍ଣ୍ଣସଂଖ୍ୟା prec = TYPE_PRECISION (type);
	    ଯଦି (ଅଙ୍କ_args == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_to_rvalue (loc, *arg_p, ସତ୍ୟ, ସତ୍ୟ);
		ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (arg_p->ମୂଲ୍ୟ)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    ପଦସମଷ୍ଟି.set_error ();
		    ଭାଙ୍ଗ;
		  }
		ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (arg_p->ମୂଲ୍ୟ)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    ପଦସମଷ୍ଟି.set_error ();
		    ଭାଙ୍ଗ;
		  }
		ବୃକ୍ଷ arg1 = save_ପଦସମଷ୍ଟି (arg);
		ବୃକ୍ଷ arg2 = save_ପଦସମଷ୍ଟି (arg_p->ମୂଲ୍ୟ);
		ବୃକ୍ଷ_code code;
		ଯଦି (stdc_rid == C_BUILTIN_STDC_ROTATE_ବାମ)
		  code = LROTATE_ପଦସମଷ୍ଟି;
		ଅନ୍ୟଥା
		  code = RROTATE_ପଦସମଷ୍ଟି;

		ଯଦି (ବୃକ୍ଷ_CODE (arg2) == INTEGER_CST
		    && ବୃକ୍ଷ_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_ଗଣନା_negative,
			      "rotate count is negative");

		ବୃକ୍ଷ instrument_ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
		ଯଦି (sanitize_flags_p (SANITIZE_SHIFT))
		  instrument_ପଦସମଷ୍ଟି = ubsan_instrument_shift (loc, code,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		ଯଦି (TYPE_PRECISION (ବୃକ୍ଷ_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_ଗଣ୍ଠି))
		  arg2 = fold_convert (unsigned_type_ଗଣ୍ଠି, arg2);

		ଯଦି (TYPE_UNSIGNED (ବୃକ୍ଷ_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (arg2),
				     arg2, build_int_cst (ବୃକ୍ଷ_TYPE (arg2),
							  prec));
		ଅନ୍ୟଥା
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    ବୃକ୍ଷ utype = c_common_unsigned_type (ବୃକ୍ଷ_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_ପଦସମଷ୍ଟି, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		ଯଦି (type_has_mode_precision_p (ବୃକ୍ଷ_TYPE (arg1))
		    || (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_MODE_SIZE))
		  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build2_loc (loc, code, ବୃକ୍ଷ_TYPE (arg1), arg1,
					   arg2);
		ଅନ୍ୟଥା
		  {
		    arg2 = save_ପଦସମଷ୍ଟି (arg2);
		    ବୃକ୍ଷ t1 = build2_loc (loc, (code == LROTATE_ପଦସମଷ୍ଟି
						? LSHIFT_ପଦସମଷ୍ଟି : RSHIFT_ପଦସମଷ୍ଟି),
					  ବୃକ୍ଷ_TYPE (arg1), arg1, arg2);
		    ବୃକ୍ଷ t2 = build2_loc (loc, MINUS_ପଦସମଷ୍ଟି,
					  ବୃକ୍ଷ_TYPE (arg2),
					  build_int_cst (ବୃକ୍ଷ_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (code == LROTATE_ପଦସମଷ୍ଟି
					   ? RSHIFT_ପଦସମଷ୍ଟି : LSHIFT_ପଦସମଷ୍ଟି),
				     ବୃକ୍ଷ_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_ଗଣନା_overflow);
		    ବୃକ୍ଷ t3 = build2_loc (loc, BIT_IOR_ପଦସମଷ୍ଟି,
					  ବୃକ୍ଷ_TYPE (arg1), t1, t2);
		    ବୃକ୍ଷ t4 = build2_loc (loc, NE_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି,
					  arg2,
					  build_zero_cst (ବୃକ୍ଷ_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି,
				     arg1, t4);
		    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build3_loc (loc, COND_ପଦସମଷ୍ଟି,
					     ବୃକ୍ଷ_TYPE (arg1), t4, t3, arg1);
		  }
		ଯଦି (instrument_ପଦସମଷ୍ଟି)
		  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build2_loc (loc, COMPOUND_ପଦସମଷ୍ଟି,
					   ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ),
					   instrument_ପଦସମଷ୍ଟି, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
		set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_paren_loc);
		ଭାଙ୍ଗ;
	      }
	    ବୃକ୍ଷ barg1 = arg;
	    ବାଛ (stdc_rid)
	      {
	      ସ୍ଥିତି C_BUILTIN_STDC_BIT_CEIL:
		arg = save_ପଦସମଷ୍ଟି (arg);
		barg1 = build2_loc (loc, PLUS_ପଦସମଷ୍ଟି, type, arg,
				    build_int_cst (type, -1));
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି C_BUILTIN_STDC_BIT_FLOOR:
		barg1 = arg = save_ପଦସମଷ୍ଟି (arg);
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି C_BUILTIN_STDC_ଗଣନା_ZEROS:
	      ସ୍ଥିତି C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      ସ୍ଥିତି C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      ସ୍ଥିତି C_BUILTIN_STDC_LEADING_ONES:
	      ସ୍ଥିତି C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, BIT_NOT_ପଦସମଷ୍ଟି, type, arg);
		ଭାଙ୍ଗ;
	      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		ଭାଙ୍ଗ;
	      }
	    ବୃକ୍ଷ barg2 = NULL_ବୃକ୍ଷ;
	    ବାଛ (stdc_rid)
	      {
	      ସ୍ଥିତି C_BUILTIN_STDC_BIT_WIDTH:
	      ସ୍ଥିତି C_BUILTIN_STDC_LEADING_ONES:
	      ସ୍ଥିତି C_BUILTIN_STDC_LEADING_ZEROS:
	      ସ୍ଥିତି C_BUILTIN_STDC_TRAILING_ONES:
	      ସ୍ଥିତି C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_ଗଣ୍ଠି, prec);
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      ସ୍ଥିତି C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      ସ୍ଥିତି C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      ସ୍ଥିତି C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		barg2 = integer_minus_one_ଗଣ୍ଠି;
		ଭାଙ୍ଗ;
	      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		ଭାଙ୍ଗ;
	      }
	    ବୃକ୍ଷ fndecl = NULL_ବୃକ୍ଷ;
	    ବାଛ (stdc_rid)
	      {
	      ସ୍ଥିତି C_BUILTIN_STDC_BIT_CEIL:
	      ସ୍ଥିତି C_BUILTIN_STDC_BIT_FLOOR:
	      ସ୍ଥିତି C_BUILTIN_STDC_BIT_WIDTH:
	      ସ୍ଥିତି C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      ସ୍ଥିତି C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      ସ୍ଥିତି C_BUILTIN_STDC_LEADING_ONES:
	      ସ୍ଥିତି C_BUILTIN_STDC_LEADING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CLZG);
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      ସ୍ଥିତି C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      ସ୍ଥିତି C_BUILTIN_STDC_TRAILING_ONES:
	      ସ୍ଥିତି C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CTZG);
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି C_BUILTIN_STDC_ଗଣନା_ONES:
	      ସ୍ଥିତି C_BUILTIN_STDC_ଗଣନା_ZEROS:
	      ସ୍ଥିତି C_BUILTIN_STDC_HAS_SINGLE_BIT:
		fndecl = builtin_decl_explicit (BUILT_IN_POPCOUNTG);
		ଭାଙ୍ଗ;
	      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nargs = barg2 != NULL_ବୃକ୍ଷ ? 2 : 1;
	    vec<ବୃକ୍ଷ, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<ବୃକ୍ଷ, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    args->quick_ଠେଲ (barg1);
	    arg_loc.quick_ଠେଲ (arg_p->get_location ());
	    origtypes->quick_ଠେଲ (arg_p->original_type);
	    ଯଦି (nargs == 2)
	      {
		args->quick_ଠେଲ (barg2);
		arg_loc.quick_ଠେଲ (loc);
		origtypes->quick_ଠେଲ (integer_type_ଗଣ୍ଠି);
	      }
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_build_function_call_vec (loc, arg_loc, fndecl,
						    args, origtypes);
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_paren_loc);
	    ଯଦି (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
	      ଭାଙ୍ଗ;
	    ବାଛ (stdc_rid)
	      {
	      ସ୍ଥିତି C_BUILTIN_STDC_BIT_CEIL:
	      ସ୍ଥିତି C_BUILTIN_STDC_BIT_FLOOR:
		--prec;
		/* FALLTHRU */
	      ସ୍ଥିତି C_BUILTIN_STDC_BIT_WIDTH:
		ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build2_loc (loc, MINUS_ପଦସମଷ୍ଟି, integer_type_ଗଣ୍ଠି,
					 build_int_cst (integer_type_ଗଣ୍ଠି,
							prec), ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      ସ୍ଥିତି C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      ସ୍ଥିତି C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      ସ୍ଥିତି C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build2_loc (loc, PLUS_ପଦସମଷ୍ଟି, integer_type_ଗଣ୍ଠି,
					 ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, integer_one_ଗଣ୍ଠି);
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି C_BUILTIN_STDC_HAS_SINGLE_BIT:
		ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build2_loc (loc, EQ_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି,
					 ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, integer_one_ଗଣ୍ଠି);
		ଭାଙ୍ଗ;
	      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		ଭାଙ୍ଗ;
	      }

	    ଯଦି (stdc_rid != C_BUILTIN_STDC_BIT_CEIL
		&& stdc_rid != C_BUILTIN_STDC_BIT_FLOOR)
	      {
		ଯଦି (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_BIT)
		  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = fold_convert_loc (loc, unsigned_type_ଗଣ୍ଠି,
						 ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
		ଭାଙ୍ଗ;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    ଯଦି (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_BIT_CEIL && integer_onep (arg)))
	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_int_cst (type, 0);
	    ଅନ୍ୟଥା
	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ
		= build2_loc (loc, LSHIFT_ପଦସମଷ୍ଟି, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_BIT_CEIL
					      ? 2 : 1)), ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	    ଯଦି (stdc_rid == C_BUILTIN_STDC_BIT_CEIL)
	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build3_loc (loc, COND_ପଦସମଷ୍ଟି, type,
				       build2_loc (loc, LE_ପଦସମଷ୍ଟି,
						   boolean_type_ଗଣ୍ଠି, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	    ଅନ୍ୟଥା
	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build3_loc (loc, COND_ପଦସମଷ୍ଟି, type,
				       build2_loc (loc, EQ_ପଦସମଷ୍ଟି,
						   boolean_type_ଗଣ୍ଠି, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି RID_BUILTIN_BSWAPG:
	ସ୍ଥିତି RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_ପଦସମଷ୍ଟି_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    internal_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    ଅଚଳ ଅକ୍ଷର *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    ଯଦି (!c_parser_get_builtin_args (parser, name, &cexpr_list, ମିଥ୍ୟା,
					    &close_paren_loc))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    ଯଦି (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }

	    c_ପଦସମଷ୍ଟି_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, ସତ୍ୟ, ସତ୍ୟ);
	    ବୃକ୍ଷ arg = arg_p->ମୂଲ୍ୟ;
	    ଯଦି (error_operand_p (arg))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ବୃକ୍ଷ type = TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (arg));
	    ଯଦି (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (ବୃକ୍ଷ_CODE (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (ବୃକ୍ଷ_CODE (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    arg = c_fully_fold (arg, ମିଥ୍ୟା, ଖାଲି);
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_paren_loc);
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ଯଦି (!parens.require_open (parser))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ବୃକ୍ଷ sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = objc_build_selector_ପଦସମଷ୍ଟି (loc, sel);
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_loc);
	  }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ଯଦି (!parens.require_open (parser))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ବୃକ୍ଷ id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = objc_build_protocol_ପଦସମଷ୍ଟି (id);
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_loc);
	  }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_AT_ENCODE:
	  {
	    /* Extension to support C-structures in the archiver.  */
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ଯଦି (!parens.require_open (parser))
	      {
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    t1 = c_parser_type_name (parser);
	    ଯଦି (t1 == ଖାଲି)
	      {
		ପଦସମଷ୍ଟି.set_error ();
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
		ଭାଙ୍ଗ;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    ବୃକ୍ଷ type = groktypename (t1, ଖାଲି, ଖାଲି);
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = objc_build_encode_ପଦସମଷ୍ଟି (type);
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_loc);
	  }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_GENERIC:
	  ପଦସମଷ୍ଟି = c_parser_generic_selection (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_OMP_ALL_MEMORY:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  ପଦସମଷ୍ଟି.set_error ();
	  ଭାଙ୍ଗ;
	/* C23 'nullptr' literal.  */
	ସ୍ଥିତି RID_NULLPTR:
	  c_parser_consume_token (parser);
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = nullptr_ଗଣ୍ଠି;
	  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_TRUE:
	  c_parser_consume_token (parser);
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = boolean_true_ଗଣ୍ଠି;
	  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, tok_range);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି RID_FALSE:
	  c_parser_consume_token (parser);
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = boolean_false_ଗଣ୍ଠି;
	  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, tok_range);
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  c_parser_error (parser, "expected expression");
	  ପଦସମଷ୍ଟି.set_error ();
	  ଭାଙ୍ଗ;
	}
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_OPEN_SQUARE:
      ଯଦି (c_dialect_objc ())
	{
	  ବୃକ୍ଷ receiver, args;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  args = c_parser_objc_message_args (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = objc_build_message_ପଦସମଷ୍ଟି (receiver, args);
	  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, loc, close_loc);
	  ଭାଙ୍ଗ;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      c_parser_error (parser, "expected expression");
      ପଦସମଷ୍ଟି.set_error ();
      ଭାଙ୍ଗ;
    }
 out:
  ଫେରନ୍ତୁ c_parser_postfix_expression_after_primary
    (parser, ପଦସମଷ୍ଟି_LOC_OR_LOC (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, loc), ପଦସମଷ୍ଟି);
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

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_postfix_expression_after_paren_type (c_parser *parser,
					      ସଂରଚନା c_declspecs *scspecs,
					      ସଂରଚନା c_type_name *type_name,
					      location_t type_loc)
{
  ବୃକ୍ଷ type;
  ସଂରଚନା c_ପଦସମଷ୍ଟି init;
  ତାର୍କିକ non_const;
  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
  location_t start_loc;
  ବୃକ୍ଷ type_ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ type_ପଦସମଷ୍ଟି_const = ସତ୍ୟ;
  ତାର୍କିକ constexpr_p = scspecs ? scspecs->constexpr_p : ମିଥ୍ୟା;
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (ଧାଡ଼ି_table, type_loc);
  start_loc = c_parser_peek_token (parser)->location;
  ଯଦି (constexpr_p)
    {
      underspec_state = start_underspecified_init (start_loc, NULL_ବୃକ୍ଷ);
      /* A constexpr compound literal is subject to the constraints on
	 underspecified declarations, which may not declare tags or
	 members or structures or unions; it is undefined behavior to
	 declare the members of an enumeration.  Where the structure,
	 union or enumeration type is declared within the compound
	 literal initializer, this is diagnosed elsewhere as a result
	 of the above call to start_underspecified_init.  Diagnose
	 here the case of declaring such a type in the type specifiers
	 of the compound literal.  */
      ବାଛ (type_name->specs->typespec_kind)
	{
	ସ୍ଥିତି ctsk_tagfirstref:
	ସ୍ଥିତି ctsk_tagfirstref_attrs:
	  error_at (type_loc, "%qT declared in %<constexpr%> compound literal",
		    type_name->specs->type);
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି ctsk_tagdef:
	  error_at (type_loc, "%qT defined in %<constexpr%> compound literal",
		    type_name->specs->type);
	  ଭାଙ୍ଗ;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଭାଙ୍ଗ;
	}
    }
  start_init (NULL_ବୃକ୍ଷ, ଖାଲି,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_ପଦସମଷ୍ଟି, &type_ପଦସମଷ୍ଟି_const);
  ତାର୍କିକ varsize_p = ମିଥ୍ୟା;
  ଯଦି (type != error_mark_ଗଣ୍ଠି && C_TYPE_VARIABLE_SIZE (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = ସତ୍ୟ;
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_ଗଣ୍ଠି;
    }
  ଯଦି (constexpr_p && type != error_mark_ଗଣ୍ଠି)
    {
      ବୃକ୍ଷ type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      ଯଦି (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      ଅନ୍ୟଥା ଯଦି (RECORD_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, ମିଥ୍ୟା, ଖାଲି, varsize_p);
  ଯଦି (constexpr_p)
    finish_underspecified_init (NULL_ବୃକ୍ଷ, underspec_state);
  finish_init ();
  maybe_warn_string_init (type_loc, type, init);

  ଯଦି (type != error_mark_ଗଣ୍ଠି
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_ଗଣ୍ଠି;
    }

  ଯଦି (!pedwarn_c90 (start_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (start_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.ମୂଲ୍ୟ && ବୃକ୍ଷ_CODE (init.ମୂଲ୍ୟ) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.ମୂଲ୍ୟ)
	       : init.original_code == C_MAYBE_CONST_ପଦସମଷ୍ଟି);
  non_const |= !type_ପଦସମଷ୍ଟି_const;
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା alignas_align = 0;
  ଯଦି (type != error_mark_ଗଣ୍ଠି
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      ଯଦି (alignas_align < min_align_of_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_compound_literal (start_loc, type, init.ମୂଲ୍ୟ, non_const,
				       alignas_align, scspecs);
  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, init.src_range);
  ପଦସମଷ୍ଟି.m_decimal = 0;
  ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
  ପଦସମଷ୍ଟି.original_type = ଖାଲି;
  ଯଦି (type != error_mark_ଗଣ୍ଠି
      && ପଦସମଷ୍ଟି.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି
      && type_ପଦସମଷ୍ଟି)
    {
      ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == C_MAYBE_CONST_ପଦସମଷ୍ଟି)
	{
	  gcc_assert (C_MAYBE_CONST_ପଦସମଷ୍ଟି_PRE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == NULL_ବୃକ୍ଷ);
	  C_MAYBE_CONST_ପଦସମଷ୍ଟି_PRE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) = type_ପଦସମଷ୍ଟି;
	}
      ଅନ୍ୟଥା
	{
	  gcc_assert (!non_const);
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build2 (C_MAYBE_CONST_ପଦସମଷ୍ଟି, type,
			       type_ପଦସମଷ୍ଟି, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	}
    }
  ଫେରନ୍ତୁ c_parser_postfix_expression_after_primary (parser, start_loc, ପଦସମଷ୍ଟି);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

ସ୍ଥିର ତାର୍କିକ
sizeof_ptr_memacc_comptypes (ବୃକ୍ଷ type1, ବୃକ୍ଷ type2)
{
  ଫେରନ୍ତୁ comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

ସ୍ଥିର ଶୂନ୍ୟ
warn_for_abs (location_t loc, ବୃକ୍ଷ fndecl, ବୃକ୍ଷ arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  ଯଦି (c_inhibit_evaluation_warnings)
    ଫେରନ୍ତୁ;

  ବୃକ୍ଷ atype = ବୃକ୍ଷ_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  ଯଦି (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && ବୃକ୍ଷ_CODE (atype) != COMPLEX_TYPE)
    ଫେରନ୍ତୁ;

  ଗଣନା built_in_function fcode = DECL_FUNCTION_CODE (fndecl);

  ବାଛ (fcode)
    {
    ସ୍ଥିତି BUILT_IN_ABS:
    ସ୍ଥିତି BUILT_IN_LABS:
    ସ୍ଥିତି BUILT_IN_LLABS:
    ସ୍ଥିତି BUILT_IN_IMAXABS:
      ଯଦି (!INTEGRAL_TYPE_P (atype))
	{
	  ଯଦି (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ମୂଲ୍ୟ,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_ମୂଲ୍ୟ,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  ଅନ୍ୟଥା
	    gcc_unreachable ();
	  ଫେରନ୍ତୁ;
	}
      ଯଦି (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_ମୂଲ୍ୟ,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      ଭାଙ୍ଗ;

    CASE_FLT_FN (BUILT_IN_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FABS):
      ଯଦି (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_MODE_P (TYPE_MODE (atype)))
	{
	  ଯଦି (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ମୂଲ୍ୟ,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  ଅନ୍ୟଥା ଯଦି (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ମୂଲ୍ୟ,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_ମୂଲ୍ୟ,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  ଅନ୍ୟଥା
	    gcc_unreachable ();
	  ଫେରନ୍ତୁ;
	}
      ଭାଙ୍ଗ;

    CASE_FLT_FN (BUILT_IN_CABS):
      ଯଦି (ବୃକ୍ଷ_CODE (atype) != COMPLEX_TYPE)
	{
	  ଯଦି (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ମୂଲ୍ୟ,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  ଅନ୍ୟଥା ଯଦି (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ମୂଲ୍ୟ,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  ଅନ୍ୟଥା
	    gcc_unreachable ();

	  ଫେରନ୍ତୁ;
	}
      ଭାଙ୍ଗ;

    ସ୍ଥିତି BUILT_IN_FABSD32:
    ସ୍ଥିତି BUILT_IN_FABSD64:
    ସ୍ଥିତି BUILT_IN_FABSD128:
    ସ୍ଥିତି BUILT_IN_FABSD64X:
      ଯଦି (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  ଯଦି (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ମୂଲ୍ୟ,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  ଅନ୍ୟଥା ଯଦି (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ମୂଲ୍ୟ,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_ମୂଲ୍ୟ,
			"using decimal floating-point absolute value "
			"function %qD when argument is of complex type %qT",
			fndecl, atype);
	  ଅନ୍ୟଥା
	    gcc_unreachable ();
	  ଫେରନ୍ତୁ;
	}
      ଭାଙ୍ଗ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଫେରନ୍ତୁ;
    }

  ଯଦି (!TYPE_ARG_TYPES (ବୃକ୍ଷ_TYPE (fndecl)))
    ଫେରନ୍ତୁ;

  ବୃକ୍ଷ ftype = ବୃକ୍ଷ_ମୂଲ୍ୟ (TYPE_ARG_TYPES (ବୃକ୍ଷ_TYPE (fndecl)));
  ଯଦି (ବୃକ୍ଷ_CODE (atype) == COMPLEX_TYPE)
    {
      gcc_assert (ବୃକ୍ଷ_CODE (ftype) == COMPLEX_TYPE);
      atype = ବୃକ୍ଷ_TYPE (atype);
      ftype = ବୃକ୍ଷ_TYPE (ftype);
    }

  ଯଦି (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_ମୂଲ୍ୟ,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_postfix_expression_after_primary (c_parser *parser,
					   location_t ପଦସମଷ୍ଟି_loc,
					   ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି orig_ପଦସମଷ୍ଟି;
  ବୃକ୍ଷ ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  ବୃକ୍ଷ sizeof_arg[6];
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା literal_zero_mask;
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
  vec<ବୃକ୍ଷ, va_gc> *exprlist;
  vec<ବୃକ୍ଷ, va_gc> *origtypes = ଖାଲି;
  vec<location_t> arg_loc = vNULL;
  location_t start;
  location_t finish;

  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      ବାଛ (c_parser_peek_token (parser)->type)
	{
	ସ୍ଥିତି CPP_OPEN_SQUARE:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_ବୃକ୍ଷ;
	  ଯଦି (!c_omp_array_section_p
	      || c_parser_next_token_is_not (parser, CPP_COLON))
	    idx = c_parser_expression (parser).ମୂଲ୍ୟ;

	  ଯଦି (c_omp_array_section_p
	      && c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      ଯଦି (c_parser_next_token_is_not (parser, CPP_CLOSE_SQUARE))
		len = c_parser_expression (parser).ମୂଲ୍ୟ;

	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_omp_array_section (op_loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, idx,
						    len);
	    }
	  ଅନ୍ୟଥା
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_array_ref (op_loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, idx);

	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");

	  start = ପଦସମଷ୍ଟି.get_start ();
	  finish = parser->tokens_buf[0].location;
	  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, start, finish);
	  ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
	  ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	  ପଦସମଷ୍ଟି.m_decimal = 0;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    ପାଇଁ (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_ବୃକ୍ଷ;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_mask = 0;
	    ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = ଖାଲି;
	    ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == FUNCTION_DECL
		     && fndecl_built_in_p (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, BUILT_IN_CLASSIFY_TYPE)
		     && c_parser_next_tokens_start_typename (parser,
							     cla_prefer_id))
	      {
		/* __builtin_classify_type (type)  */
		c_inhibit_evaluation_warnings++;
		in_alignof++;
		ସଂରଚନା c_type_name *type = c_parser_type_name (parser);
		c_inhibit_evaluation_warnings--;
		in_alignof--;
		ସଂରଚନା c_typespec ret;
		ret.ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
		ret.spec = error_mark_ଗଣ୍ଠି;
		ret.ପଦସମଷ୍ଟି_const_operands = ମିଥ୍ୟା;
		ଯଦି (type != ଖାଲି)
		  ret.spec = groktypename (type, &ret.ପଦସମଷ୍ଟି,
					   &ret.ପଦସମଷ୍ଟି_const_operands);
		parens.skip_until_found_close (parser);
		ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_int_cst (integer_type_ଗଣ୍ଠି,
					    type_to_class (ret.spec));
		ଭାଙ୍ଗ;
	      }
	    ଅନ୍ୟଥା
	      exprlist = c_parser_ପଦସମଷ୍ଟି_list (parser, ସତ୍ୟ, ମିଥ୍ୟା, &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_mask);
	    parens.skip_until_found_close (parser);
	  }
	  orig_ପଦସମଷ୍ଟି = ପଦସମଷ୍ଟି;
	  mark_exp_read (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	  ଯଦି (warn_sizeof_pointer_memaccess)
	    sizeof_pointer_memaccess_warning (sizeof_arg_loc,
					      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == FUNCTION_DECL)
	    {
	      ଯଦି (fndecl_built_in_p (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, BUILT_IN_MEMSET)
		  && vec_safe_length (exprlist) == 3)
		{
		  ବୃକ୍ଷ arg0 = (*exprlist)[0];
		  ବୃକ୍ଷ arg2 = (*exprlist)[2];
		  warn_for_memset (ପଦସମଷ୍ଟି_loc, arg0, arg2, literal_zero_mask);
		}
	      ଯଦି (warn_absolute_ମୂଲ୍ୟ
		  && fndecl_built_in_p (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, BUILT_IN_NORMAL)
		  && vec_safe_length (exprlist) == 1)
		warn_for_abs (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, (*exprlist)[0]);
	      ଯଦି (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->in_intervening_code
		  && omp_runtime_api_call (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ))
		{
		  error_at (ପଦସମଷ୍ଟି_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->fail = ସତ୍ୟ;
		}
	      ଯଦି (warn_calloc_transposed_args)
		ଯଦି (ବୃକ୍ଷ attr = lookup_attribute ("alloc_size",
						  TYPE_ATTRIBUTES
						    (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ))))
		  ଯଦି (ବୃକ୍ଷ_ମୂଲ୍ୟ (attr) && ବୃକ୍ଷ_CHAIN (ବୃକ୍ଷ_ମୂଲ୍ୟ (attr)))
		    warn_for_calloc (sizeof_arg_loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, exprlist,
				     sizeof_arg, attr);
	    }

	  start = ପଦସମଷ୍ଟି.get_start ();
	  finish = parser->tokens_buf[0].get_finish ();
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ
	    = c_build_function_call_vec (ପଦସମଷ୍ଟି_loc, arg_loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ,
					 exprlist, origtypes);
	  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, start, finish);
	  ପଦସମଷ୍ଟି.m_decimal = 0;

	  ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
	  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == INTEGER_CST
	      && ବୃକ୍ଷ_CODE (orig_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == FUNCTION_DECL
	      && fndecl_built_in_p (orig_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, BUILT_IN_CONSTANT_P))
	    ପଦସମଷ୍ଟି.original_code = C_MAYBE_CONST_ପଦସମଷ୍ଟି;
	  ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	  ଯଦି (exprlist)
	    {
	      release_ବୃକ୍ଷ_vector (exprlist);
	      release_ବୃକ୍ଷ_vector (origtypes);
	    }
	  arg_loc.release ();
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  ପଦସମଷ୍ଟି = default_function_array_conversion (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି);
	  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->ମୂଲ୍ୟ;
	      comp_loc = comp_tok->location;
	    }
	  ଅନ୍ୟଥା
	    {
	      c_parser_error (parser, "expected identifier");
	      ପଦସମଷ୍ଟି.set_error ();
	      ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
              ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	      ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
	    }
	  start = ପଦସମଷ୍ଟି.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_component_ref (op_loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, start, finish);
	  ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
	  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) != COMPONENT_REF)
	    ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	  ଅନ୍ୟଥା
	    {
	      /* Remember the original type of a bitfield.  */
	      ବୃକ୍ଷ field = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, 1);
	      ଯଦି (ବୃକ୍ଷ_CODE (field) != FIELD_DECL)
		ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	      ଅନ୍ୟଥା
		ପଦସମଷ୍ଟି.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  ପଦସମଷ୍ଟି.m_decimal = 0;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ମିଥ୍ୟା);
	  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->ମୂଲ୍ୟ;
	      comp_loc = comp_tok->location;
	    }
	  ଅନ୍ୟଥା
	    {
	      c_parser_error (parser, "expected identifier");
	      ପଦସମଷ୍ଟି.set_error ();
	      ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
	      ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	      ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
	    }
	  start = ପଦସମଷ୍ଟି.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_component_ref (op_loc,
					    build_indirect_ref (op_loc,
								ପଦସମଷ୍ଟି.ମୂଲ୍ୟ,
								RO_ARROW),
					    ident, comp_loc,
					    ପଦସମଷ୍ଟି.get_location ());
	  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, start, finish);
	  ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
	  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) != COMPONENT_REF)
	    ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	  ଅନ୍ୟଥା
	    {
	      /* Remember the original type of a bitfield.  */
	      ବୃକ୍ଷ field = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, 1);
	      ଯଦି (ବୃକ୍ଷ_CODE (field) != FIELD_DECL)
		ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	      ଅନ୍ୟଥା
		ପଦସମଷ୍ଟି.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  ପଦସମଷ୍ଟି.m_decimal = 0;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  start = ପଦସମଷ୍ଟି.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	  ପଦସମଷ୍ଟି = default_function_array_conversion (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି);
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_unary_op (op_loc, POSTINCREMENT_ପଦସମଷ୍ଟି,
				       ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା);
	  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, start, finish);
	  ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
	  ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  start = ପଦସମଷ୍ଟି.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	  ପଦସମଷ୍ଟି = default_function_array_conversion (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି);
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_unary_op (op_loc, POSTDECREMENT_ପଦସମଷ୍ଟି,
				       ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା);
	  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, start, finish);
	  ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
	  ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_expression (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
  ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
    ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (tloc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ମିଥ୍ୟା);
  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      ସଂରଚନା c_ପଦସମଷ୍ଟି next;
      ବୃକ୍ଷ lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t ପଦସମଷ୍ଟି_loc;
      c_parser_consume_token (parser);
      ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      lhsval = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (lhsval) == COMPOUND_ପଦସମଷ୍ଟି
	     || ବୃକ୍ଷ_CODE (lhsval) == NOP_ପଦସମଷ୍ଟି)
	{
	  ଯଦି (ବୃକ୍ଷ_CODE (lhsval) == COMPOUND_ପଦସମଷ୍ଟି)
	    lhsval = ବୃକ୍ଷ_OPERAND (lhsval, 1);
	  ଅନ୍ୟଥା
	    lhsval = ବୃକ୍ଷ_OPERAND (lhsval, 0);
	}
      ଯଦି (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      ଯଦି (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  ବୃକ୍ଷ val = embed->ମୂଲ୍ୟ;
	  unsigned last = RAW_DATA_LENGTH (val) - 1;
	  next.ମୂଲ୍ୟ = build_int_cst (ବୃକ୍ଷ_TYPE (val),
				      RAW_DATA_UCHAR_ELT (val, last));
	  next.original_type = integer_type_ଗଣ୍ଠି;
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା
	{
	  next = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	  next = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, next, ସତ୍ୟ, ମିଥ୍ୟା);
	}
      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_compound_ପଦସମଷ୍ଟି (loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, next.ମୂଲ୍ୟ);
      ପଦସମଷ୍ଟି.original_code = COMPOUND_ପଦସମଷ୍ଟି;
      ପଦସମଷ୍ଟି.original_type = next.original_type;
      ପଦସମଷ୍ଟି.m_decimal = 0;
    }
  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_expression_conv (c_parser *parser)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
  location_t loc = c_parser_peek_token (parser)->location;
  ପଦସମଷ୍ଟି = c_parser_expression (parser);
  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (loc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ମିଥ୍ୟା);
  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ
c_parser_check_literal_zero (c_parser *parser, unsigned *literal_zero_mask,
			     unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା idx)
{
  ଯଦି (idx >= HOST_BITS_PER_INT)
    ଫେରନ୍ତୁ;

  c_token *tok = c_parser_peek_token (parser);
  ବାଛ (tok->type)
    {
    ସ୍ଥିତି CPP_ସଂଖ୍ୟା:
    ସ୍ଥିତି CPP_CHAR:
    ସ୍ଥିତି CPP_WCHAR:
    ସ୍ଥିତି CPP_CHAR16:
    ସ୍ଥିତି CPP_CHAR32:
    ସ୍ଥିତି CPP_UTF8CHAR:
      /* If a parameter is literal zero alone, remember it
	 for -Wmemset-transposed-args warning.  */
      ଯଦି (integer_zerop (tok->ମୂଲ୍ୟ)
	  && !ବୃକ୍ଷ_OVERFLOW (tok->ମୂଲ୍ୟ)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_mask |= 1U << idx;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଭାଙ୍ଗ;
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

ସ୍ଥିର vec<ବୃକ୍ଷ, va_gc> *
c_parser_ପଦସମଷ୍ଟି_list (c_parser *parser, ତାର୍କିକ convert_p, ତାର୍କିକ fold_p,
		    vec<ବୃକ୍ଷ, va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, ବୃକ୍ଷ *sizeof_arg,
		    vec<location_t> *locations,
		    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *literal_zero_mask)
{
  vec<ବୃକ୍ଷ, va_gc> *ret;
  vec<ବୃକ୍ଷ, va_gc> *orig_types;
  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା idx = 0;
  ତାର୍କିକ save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = ମିଥ୍ୟା;

  ret = make_ବୃକ୍ଷ_vector ();
  ଯଦି (p_orig_types == ଖାଲି)
    orig_types = ଖାଲି;
  ଅନ୍ୟଥା
    orig_types = make_ବୃକ୍ଷ_vector ();

  ଯଦି (literal_zero_mask)
    c_parser_check_literal_zero (parser, literal_zero_mask, 0);
  ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
  ଯଦି (convert_p)
    ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି.get_location (), ପଦସମଷ୍ଟି, ସତ୍ୟ, ସତ୍ୟ);
  ଯଦି (fold_p)
    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
  ret->quick_ଠେଲ (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
  ଯଦି (orig_types)
    orig_types->quick_ଠେଲ (ପଦସମଷ୍ଟି.original_type);
  ଯଦି (locations)
    locations->safe_ଠେଲ (ପଦସମଷ୍ଟି.get_location ());
  ଯଦି (sizeof_arg != ଖାଲି
      && (ପଦସମଷ୍ଟି.original_code == SIZEOF_ପଦସମଷ୍ଟି
	  || ପଦସମଷ୍ଟି.original_code == PAREN_SIZEOF_ପଦସମଷ୍ଟି))
    {
      sizeof_arg[0] = c_last_sizeof_arg;
      sizeof_arg_loc[0] = c_last_sizeof_loc;
    }
  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ଯଦି (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  ବୃକ୍ଷ ମୂଲ୍ୟ = embed->ମୂଲ୍ୟ;
	  ପଦସମଷ୍ଟି.original_code = INTEGER_CST;
	  ପଦସମଷ୍ଟି.original_type = integer_type_ଗଣ୍ଠି;
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = NULL_ବୃକ୍ଷ;
	  set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, embed->get_range ());
	  ପଦସମଷ୍ଟି.m_decimal = 0;
	  ପାଇଁ (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < (unsigned) RAW_DATA_LENGTH (ମୂଲ୍ୟ); i++)
	    {
	      ଯଦି (literal_zero_mask
		  && idx + 1 < HOST_BITS_PER_INT
		  && RAW_DATA_POINTER (ମୂଲ୍ୟ)[i] == 0)
		*literal_zero_mask |= 1U << (idx + 1);
	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_int_cst (integer_type_ଗଣ୍ଠି,
					  RAW_DATA_UCHAR_ELT (ମୂଲ୍ୟ, i));
	      vec_safe_ଠେଲ (ret, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	      ଯଦି (orig_types)
		vec_safe_ଠେଲ (orig_types, ପଦସମଷ୍ଟି.original_type);
	      ଯଦି (locations)
		locations->safe_ଠେଲ (ପଦସମଷ୍ଟି.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  ଜାରି;
	}
      ଯଦି (literal_zero_mask)
	c_parser_check_literal_zero (parser, literal_zero_mask, idx + 1);
      ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ଯଦି (convert_p)
	ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି.get_location (), ପଦସମଷ୍ଟି, ସତ୍ୟ,
					 ସତ୍ୟ);
      ଯଦି (fold_p)
	ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
      vec_safe_ଠେଲ (ret, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
      ଯଦି (orig_types)
	vec_safe_ଠେଲ (orig_types, ପଦସମଷ୍ଟି.original_type);
      ଯଦି (locations)
	locations->safe_ଠେଲ (ପଦସମଷ୍ଟି.get_location ());
      ଯଦି (++idx < 6
	  && sizeof_arg != ଖାଲି
	  && (ପଦସମଷ୍ଟି.original_code == SIZEOF_ପଦସମଷ୍ଟି
	      || ପଦସମଷ୍ଟି.original_code == PAREN_SIZEOF_ପଦସମଷ୍ଟି))
	{
	  sizeof_arg[idx] = c_last_sizeof_arg;
	  sizeof_arg_loc[idx] = c_last_sizeof_loc;
	}
    }
  ଯଦି (orig_types)
    *p_orig_types = orig_types;
  c_omp_array_section_p = save_c_omp_array_section_p;
  ଫେରନ୍ତୁ ret;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_objc_class_definition (c_parser *parser, ବୃକ୍ଷ attributes)
{
  ତାର୍କିକ iface_p;
  ବୃକ୍ଷ id1;
  ବୃକ୍ଷ superclass;
  ଯଦି (c_parser_next_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = ସତ୍ୟ;
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = ମିଥ୍ୟା;
  ଅନ୍ୟଥା
    gcc_unreachable ();

  c_parser_consume_token (parser);
  ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      ଫେରନ୍ତୁ;
    }
  id1 = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      ବୃକ୍ଷ id2;
      ବୃକ୍ଷ proto = NULL_ବୃକ୍ଷ;
      matching_parens parens;
      parens.consume_open (parser);
      ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  ଯଦି (iface_p && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_ବୃକ୍ଷ;
	    }
	  ଅନ୍ୟଥା
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
	      ଫେରନ୍ତୁ;
	    }
	}
      ଅନ୍ୟଥା
	{
	  id2 = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_found_close (parser);
      ଯଦି (!iface_p)
	{
	  objc_start_category_implementation (id1, id2);
	  ଫେରନ୍ତୁ;
	}
      ଯଦି (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_category_interface (id1, id2, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
      ଫେରନ୍ତୁ;
    }
  ଯଦି (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  ଫେରନ୍ତୁ;
	}
      superclass = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      c_parser_consume_token (parser);
    }
  ଅନ୍ୟଥା
    superclass = NULL_ବୃକ୍ଷ;
  ଯଦି (iface_p)
    {
      ବୃକ୍ଷ proto = NULL_ବୃକ୍ଷ;
      ଯଦି (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_class_interface (id1, loc1, superclass, proto, attributes);
    }
  ଅନ୍ୟଥା
    objc_start_class_implementation (id1, superclass);
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  ଯଦି (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
    }
  ଅନ୍ୟଥା
    {
      objc_continue_implementation ();
      ଫେରନ୍ତୁ;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_objc_class_instance_variables (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_EOF))
    {
      ବୃକ୍ଷ decls;
      /* Parse any stray semicolon.  */
      ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  ଜାରି;
	}
      /* Stop if at the end of the instance variables.  */
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  ଭାଙ୍ଗ;
	}
      /* Parse any objc-visibility-spec.  */
      ଯଦି (c_parser_next_token_is_keyword (parser, RID_AT_PRIVATE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PRIVATE);
	  ଜାରି;
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PROTECTED);
	  ଜାରି;
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_AT_PUBLIC))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PUBLIC);
	  ଜାରି;
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PACKAGE);
	  ଜାରି;
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, ଖାଲି, NULL_ବୃକ୍ଷ);
	  ଜାରି;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser, ଖାଲି);
      ଯଦି (decls == ଖାଲି)
	{
	  /* There is a syntax error.  We want to skip the offending
	     tokens up to the next ';' (included) or '}'
	     (excluded).  */

	  /* First, skip manually a ')' or ']'.  This is because they
	     reduce the nesting level, so c_parser_skip_until_found()
	     wouldn't be able to skip past them.  */
	  c_token *token = c_parser_peek_token (parser);
	  ଯଦି (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_SQUARE)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, ଖାଲି);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = ମିଥ୍ୟା;
	  ଜାରି;
	}
      ଅନ୍ୟଥା
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  ବୃକ୍ଷ ivar = nreverse (decls);
	  ପାଇଁ (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_add_instance_variable (copy_ଗଣ୍ଠି (ivar));
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}

/* Parse an objc-class-declaration.

   objc-class-declaration:
     @class identifier-list ;
*/

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_objc_class_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_CLASS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      ବୃକ୍ଷ id;
      ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, ଖାଲି);
	  parser->error = ମିଥ୍ୟା;
	  ଫେରନ୍ତୁ;
	}
      id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse an objc-alias-declaration.

   objc-alias-declaration:
     @compatibility_alias identifier identifier ;
*/

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_objc_alias_declaration (c_parser *parser)
{
  ବୃକ୍ଷ id1, id2;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, ଖାଲି);
      ଫେରନ୍ତୁ;
    }
  id1 = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
  c_parser_consume_token (parser);
  ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, ଖାଲି);
      ଫେରନ୍ତୁ;
    }
  id2 = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_objc_protocol_definition (c_parser *parser, ବୃକ୍ଷ attributes)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      ଫେରନ୍ତୁ;
    }
  ଯଦି (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      ଯେତେବେଳେ (ସତ୍ୟ)
	{
	  ବୃକ୍ଷ id;
	  ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      ଭାଙ୍ଗ;
	    }
	  id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	  objc_declare_protocol (id, attributes);
	  c_parser_consume_token (parser);
	  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ଅନ୍ୟଥା
	    ଭାଙ୍ଗ;
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  ଅନ୍ୟଥା
    {
      ବୃକ୍ଷ id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      ବୃକ୍ଷ proto = NULL_ବୃକ୍ଷ;
      c_parser_consume_token (parser);
      ଯଦି (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = ସତ୍ୟ;
      objc_start_protocol (id, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      parser->objc_pq_context = ମିଥ୍ୟା;
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
ସ୍ଥିର ଧାଡ଼ିଭିତରେ ତାର୍କିକ
c_parser_objc_method_type (c_parser *parser)
{
  ବାଛ (c_parser_peek_token (parser)->type)
    {
    ସ୍ଥିତି CPP_PLUS:
      c_parser_consume_token (parser);
      ଫେରନ୍ତୁ ସତ୍ୟ;
    ସ୍ଥିତି CPP_MINUS:
      c_parser_consume_token (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    }
}

/* Parse an objc-method-definition.

   objc-method-definition:
     objc-method-type objc-method-decl ;[opt] compound-statement
*/

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_objc_method_definition (c_parser *parser)
{
  ତାର୍କିକ is_class_method = c_parser_objc_method_type (parser);
  ବୃକ୍ଷ decl, attributes = NULL_ବୃକ୍ଷ, ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
  parser->objc_pq_context = ସତ୍ୟ;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    &ପଦସମଷ୍ଟି);
  ଯଦି (decl == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ;  /* Bail here. */

  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  ଯଦି (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      ଫେରନ୍ତୁ;
    }

  parser->objc_pq_context = ମିଥ୍ୟା;
  ଯଦି (objc_start_method_definition (is_class_method, decl, attributes, ପଦସମଷ୍ଟି))
    {
      add_stmt (c_parser_compound_statement (parser));
      objc_finish_method_definition (current_function_decl);
    }
  ଅନ୍ୟଥା
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_objc_methodprotolist (c_parser *parser)
{
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      /* The list is terminated by @end.  */
      ବାଛ (c_parser_peek_token (parser)->type)
	{
	ସ୍ଥିତି CPP_SEMICOLON:
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_PLUS:
	ସ୍ଥିତି CPP_MINUS:
	  c_parser_objc_methodproto (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external, ଖାଲି, NULL_ବୃକ୍ଷ);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_EOF:
	  ଫେରନ୍ତୁ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଯଦି (c_parser_next_token_is_keyword (parser, RID_AT_END))
	    ଫେରନ୍ତୁ;
	  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_set_method_opt (ସତ୍ୟ);
	      c_parser_consume_token (parser);
	    }
	  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_set_method_opt (ମିଥ୍ୟା);
	      c_parser_consume_token (parser);
	    }
	  ଅନ୍ୟଥା
	    c_parser_declaration_or_fndef (parser, ମିଥ୍ୟା, ମିଥ୍ୟା, ସତ୍ୟ,
					   ମିଥ୍ୟା, ସତ୍ୟ, ମିଥ୍ୟା);
	  ଭାଙ୍ଗ;
	}
    }
}

/* Parse an objc-methodproto.

   objc-methodproto:
     objc-method-type objc-method-decl ;
*/

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_objc_methodproto (c_parser *parser)
{
  ତାର୍କିକ is_class_method = c_parser_objc_method_type (parser);
  ବୃକ୍ଷ decl, attributes = NULL_ବୃକ୍ଷ;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = ସତ୍ୟ;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    ଖାଲି);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = ମିଥ୍ୟା;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  ଯଦି (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      ଫେରନ୍ତୁ;
    }

  ଯଦି (decl != error_mark_ଗଣ୍ଠି)
    objc_add_method_declaration (is_class_method, decl, attributes);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

ସ୍ଥିର ତାର୍କିକ
c_parser_objc_maybe_method_attributes (c_parser* parser, ବୃକ୍ଷ* attributes)
{
  ତାର୍କିକ bad = ମିଥ୍ୟା;
  ଯଦି (*attributes)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *attributes = NULL_ବୃକ୍ଷ;
      bad = ସତ୍ୟ;
    }

  ଯଦି (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    *attributes = c_parser_gnu_attributes (parser);

  /* If there were no attributes here, just report any earlier error.  */
  ଯଦି (*attributes == NULL_ବୃକ୍ଷ || bad)
    ଫେରନ୍ତୁ bad;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    ଫେରନ୍ତୁ bad;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  ଫେରନ୍ତୁ ସତ୍ୟ;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_objc_method_decl (c_parser *parser, ତାର୍କିକ is_class_method,
			   ବୃକ୍ଷ *attributes, ବୃକ୍ଷ *ପଦସମଷ୍ଟି)
{
  ବୃକ୍ଷ type = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ sel;
  ବୃକ୍ଷ parms = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ ellipsis = ମିଥ୍ୟା;
  ତାର୍କିକ attr_err = ମିଥ୍ୟା;

  *attributes = NULL_ବୃକ୍ଷ;
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
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
  ଯଦି (!sel || c_parser_next_token_is (parser, CPP_COLON))
    {
      ବୃକ୍ଷ tsel = sel;
      ବୃକ୍ଷ list = NULL_ବୃକ୍ଷ;
      ଯେତେବେଳେ (ସତ୍ୟ)
	{
	  ବୃକ୍ଷ atype = NULL_ବୃକ୍ଷ, id, keyworddecl;
	  ବୃକ୍ଷ param_attr = NULL_ବୃକ୍ଷ;
	  ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    ଭାଙ୍ଗ;
	  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  ଯଦି (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_attributes (parser);
	  ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	    }
	  id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  ଯଦି (!tsel && c_parser_next_token_is_not (parser, CPP_COLON))
	    ଭାଙ୍ଗ;
	}

      attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_ଗଣ୍ଠି (ବୃକ୍ଷ_LIST);
      ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  ସଂରଚନା c_parm *parm;
	  c_parser_consume_token (parser);
	  ଯଦି (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = ସତ୍ୟ;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_method_attributes
						(parser, attributes) ;
	      ଭାଙ୍ଗ;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_ବୃକ୍ଷ, ମିଥ୍ୟା);
	  ଯଦି (parm == ଖାଲି)
	    ଭାଙ୍ଗ;
	  parms = chainon (parms,
			   build_ବୃକ୍ଷ_list (NULL_ବୃକ୍ଷ, grokparm (parm, ପଦସମଷ୍ଟି)));
	}
      sel = list;
    }
  ଅନ୍ୟଥା
    attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

  ଯଦି (sel == ଖାଲି)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  ଯଦି (attr_err)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ଫେରନ୍ତୁ objc_build_method_signature (is_class_method, type, sel, parms, ellipsis);
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_objc_type_name (c_parser *parser)
{
  ବୃକ୍ଷ quals = NULL_ବୃକ୍ଷ;
  ସଂରଚନା c_type_name *type_name = ଖାଲି;
  ବୃକ୍ଷ type = NULL_ବୃକ୍ଷ;
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      c_token *token = c_parser_peek_token (parser);
      ଯଦି (token->type == CPP_KEYWORD
	  && (token->keyword == RID_IN
	      || token->keyword == RID_OUT
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_ବୃକ୍ଷ_list (NULL_ବୃକ୍ଷ, token->ମୂଲ୍ୟ), quals);
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
    }
  ଯଦି (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  ଯଦି (type_name)
    type = groktypename (type_name, ଖାଲି, ଖାଲି);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  ଯଦି (type == error_mark_ଗଣ୍ଠି)
    type = NULL_ବୃକ୍ଷ;

  ଫେରନ୍ତୁ build_ବୃକ୍ଷ_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_objc_protocol_refs (c_parser *parser)
{
  ବୃକ୍ଷ list = NULL_ବୃକ୍ଷ;
  gcc_assert (c_parser_next_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      ବୃକ୍ଷ id;
      ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  ଭାଙ୍ଗ;
	}
      id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      list = chainon (list, build_ବୃକ୍ଷ_list (NULL_ବୃକ୍ଷ, id));
      c_parser_consume_token (parser);
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  ଫେରନ୍ତୁ list;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_objc_try_catch_finally_statement (c_parser *parser)
{
  location_t location;
  ବୃକ୍ଷ stmt;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  ଯେତେବେଳେ (c_parser_next_token_is_keyword (parser, RID_AT_CATCH))
    {
      ସଂରଚନା c_parm *parm;
      ବୃକ୍ଷ parameter_declaration = error_mark_ଗଣ୍ଠି;
      ତାର୍କିକ seen_open_paren = ମିଥ୍ୟା;

      c_parser_consume_token (parser);
      matching_parens parens;
      ଯଦି (!parens.require_open (parser))
	seen_open_paren = ସତ୍ୟ;
      ଯଦି (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_ବୃକ୍ଷ;
	}
      ଅନ୍ୟଥା
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_ବୃକ୍ଷ, ମିଥ୍ୟା);
	  ଯଦି (parm == ଖାଲି)
	    parameter_declaration = error_mark_ଗଣ୍ଠି;
	  ଅନ୍ୟଥା
	    parameter_declaration = grokparm (parm, ଖାଲି);
	}
      ଯଦି (seen_open_paren)
	parens.require_close (parser);
      ଅନ୍ୟଥା
	{
	  /* If there was no open parenthesis, we are recovering from
	     an error, and we are trying to figure out what mistake
	     the user has made.  */

	  /* If there is an immediate closing parenthesis, the user
	     probably forgot the opening one (ie, they typed "@catch
	     NSException *e)".  Parse the closing parenthesis and keep
	     going.  */
	  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      ଯଦି (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_finish_catch_clause ();
    }
  ଯଦି (c_parser_next_token_is_keyword (parser, RID_AT_FINALLY))
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_objc_synchronized_statement (c_parser *parser)
{
  location_t loc;
  ବୃକ୍ଷ ପଦସମଷ୍ଟି, stmt;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      ସଂରଚନା c_ପଦସମଷ୍ଟି ce = c_parser_expression (parser);
      ce = convert_lvalue_to_rvalue (loc, ce, ମିଥ୍ୟା, ମିଥ୍ୟା);
      ପଦସମଷ୍ଟି = ce.ମୂଲ୍ୟ;
      ପଦସମଷ୍ଟି = c_fully_fold (ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ଖାଲି);
      parens.skip_until_found_close (parser);
    }
  ଅନ୍ୟଥା
    ପଦସମଷ୍ଟି = error_mark_ଗଣ୍ଠି;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, ପଦସମଷ୍ଟି, stmt);
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  ବୃକ୍ଷ ମୂଲ୍ୟ = token->ମୂଲ୍ୟ;
  ଯଦି (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      ଫେରନ୍ତୁ ମୂଲ୍ୟ;
    }
  ଯଦି (token->type != CPP_KEYWORD)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  ବାଛ (token->keyword)
    {
    ସ୍ଥିତି RID_ENUM:
    ସ୍ଥିତି RID_STRUCT:
    ସ୍ଥିତି RID_UNION:
    ସ୍ଥିତି RID_IF:
    ସ୍ଥିତି RID_ELSE:
    ସ୍ଥିତି RID_WHILE:
    ସ୍ଥିତି RID_DO:
    ସ୍ଥିତି RID_FOR:
    ସ୍ଥିତି RID_SWITCH:
    ସ୍ଥିତି RID_CASE:
    ସ୍ଥିତି RID_DEFAULT:
    ସ୍ଥିତି RID_BREAK:
    ସ୍ଥିତି RID_CONTINUE:
    ସ୍ଥିତି RID_RETURN:
    ସ୍ଥିତି RID_GOTO:
    ସ୍ଥିତି RID_ASM:
    ସ୍ଥିତି RID_SIZEOF:
    ସ୍ଥିତି RID_TYPEOF:
    ସ୍ଥିତି RID_TYPEOF_UNQUAL:
    ସ୍ଥିତି RID_ALIGNOF:
    ସ୍ଥିତି RID_UNSIGNED:
    ସ୍ଥିତି RID_LONG:
    ସ୍ଥିତି RID_CONST:
    ସ୍ଥିତି RID_SHORT:
    ସ୍ଥିତି RID_VOLATILE:
    ସ୍ଥିତି RID_SIGNED:
    ସ୍ଥିତି RID_RESTRICT:
    ସ୍ଥିତି RID_COMPLEX:
    ସ୍ଥିତି RID_IN:
    ସ୍ଥିତି RID_OUT:
    ସ୍ଥିତି RID_INOUT:
    ସ୍ଥିତି RID_BYCOPY:
    ସ୍ଥିତି RID_BYREF:
    ସ୍ଥିତି RID_ONEWAY:
    ସ୍ଥିତି RID_INT:
    ସ୍ଥିତି RID_CHAR:
    ସ୍ଥିତି RID_FLOAT:
    ସ୍ଥିତି RID_DOUBLE:
    CASE_RID_FLOATN_NX:
    ସ୍ଥିତି RID_VOID:
    ସ୍ଥିତି RID_BOOL:
    ସ୍ଥିତି RID_ATOMIC:
    ସ୍ଥିତି RID_AUTO_TYPE:
    ସ୍ଥିତି RID_INT_N_0:
    ସ୍ଥିତି RID_INT_N_1:
    ସ୍ଥିତି RID_INT_N_2:
    ସ୍ଥିତି RID_INT_N_3:
      c_parser_consume_token (parser);
      ଫେରନ୍ତୁ ମୂଲ୍ୟ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_objc_selector_arg (c_parser *parser)
{
  ବୃକ୍ଷ sel = c_parser_objc_selector (parser);
  ବୃକ୍ଷ list = NULL_ବୃକ୍ଷ;
  ଯଦି (sel
      && c_parser_next_token_is_not (parser, CPP_COLON)
      && c_parser_next_token_is_not (parser, CPP_SCOPE))
    ଫେରନ୍ତୁ sel;
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_ବୃକ୍ଷ_list (sel, NULL_ବୃକ୍ଷ));
	  list = chainon (list, build_ବୃକ୍ଷ_list (NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ));
	}
      ଅନ୍ୟଥା
	{
	  ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    ଫେରନ୍ତୁ list;
	  list = chainon (list, build_ବୃକ୍ଷ_list (sel, NULL_ବୃକ୍ଷ));
	}
      sel = c_parser_objc_selector (parser);
      ଯଦି (!sel
	  && c_parser_next_token_is_not (parser, CPP_COLON)
	  && c_parser_next_token_is_not (parser, CPP_SCOPE))
	ଭାଙ୍ଗ;
    }
  ଫେରନ୍ତୁ list;
}

/* Parse an objc-receiver.

   objc-receiver:
     expression
     class-name
     type-name
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  ଯଦି (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
    {
      ବୃକ୍ଷ id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      c_parser_consume_token (parser);
      ଫେରନ୍ତୁ objc_get_class_reference (id);
    }
  ସଂରଚନା c_ପଦସମଷ୍ଟି ce = c_parser_expression (parser);
  ce = convert_lvalue_to_rvalue (loc, ce, ମିଥ୍ୟା, ମିଥ୍ୟା);
  ଫେରନ୍ତୁ c_fully_fold (ce.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_objc_message_args (c_parser *parser)
{
  ବୃକ୍ଷ sel = c_parser_objc_selector (parser);
  ବୃକ୍ଷ list = NULL_ବୃକ୍ଷ;
  ଯଦି (sel && c_parser_next_token_is_not (parser, CPP_COLON))
    ଫେରନ୍ତୁ sel;
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      ବୃକ୍ଷ keywordexpr;
      ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_ବୃକ୍ଷ_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      ଯଦି (!sel && c_parser_next_token_is_not (parser, CPP_COLON))
	ଭାଙ୍ଗ;
    }
  ଫେରନ୍ତୁ list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_objc_keywordexpr (c_parser *parser)
{
  ବୃକ୍ଷ ret;
  vec<ବୃକ୍ଷ, va_gc> *ପଦସମଷ୍ଟି_list = c_parser_ପଦସମଷ୍ଟି_list (parser, ସତ୍ୟ, ସତ୍ୟ,
						ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି);
  ଯଦି (vec_safe_length (ପଦସମଷ୍ଟି_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*ପଦସମଷ୍ଟି_list)[0];
    }
  ଅନ୍ୟଥା
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_ବୃକ୍ଷ_list_vec (ପଦସମଷ୍ଟି_list);
    }
  release_ବୃକ୍ଷ_vector (ପଦସମଷ୍ଟି_list);
  ଫେରନ୍ତୁ ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
ସ୍ଥିର ତାର୍କିକ
c_parser_objc_diagnose_bad_element_prefix (c_parser *parser,
					   ସଂରଚନା c_declspecs *specs)
{
  ଯଦି (!specs->declspecs_seen_p || specs->non_sc_seen_p
      || specs->typespec_kind != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_to_end_of_block_or_statement (parser);
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }
  ଫେରନ୍ତୁ ମିଥ୍ୟା;
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
ସ୍ଥିର ଶୂନ୍ୟ
c_parser_objc_at_property_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY));
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);  /* Eat '@property'.  */

  /* Parse the optional attribute list.

     A list of parsed, but not verified, attributes.  */
  vec<property_attribute_info *> prop_attr_list = vNULL;

  ତାର୍କିକ syntax_error = ମିଥ୍ୟା;
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_start = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = ସତ୍ୟ;

      /* Allow @property (), with a warning.  */
      location_t attr_end = c_parser_peek_token (parser)->location;

      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_end, attr_start, attr_end);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      ଅନ୍ୟଥା
	ଯେତେବେଳେ (ସତ୍ୟ)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_start = token->location;
	    attr_end = get_finish (token->location);
	    location_t attr_comb = make_location (attr_start, attr_start,
						  attr_end);

	    ଯଦି (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		ଯଦି (token->type == CPP_CLOSE_PAREN)
		  ଭାଙ୍ଗ;
		c_parser_consume_token (parser);
		ଜାରି;
	      }

	    ବୃକ୍ଷ attr_name = NULL_ବୃକ୍ଷ;
	    ଗଣନା rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    ତାର୍କିକ add_at = ମିଥ୍ୟା;
	    ଯଦି (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		ଯଦି (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->ମୂଲ୍ୟ;
		    add_at = ସତ୍ୟ;
		  }
		ଅନ୍ୟଥା
		  attr_name = ridpointers[(ପୂର୍ଣ୍ଣସଂଖ୍ୟା)keyword];
	      }
	    ଅନ୍ୟଥା ଯଦି (token->type == CPP_NAME)
	      attr_name = token->ମୂଲ୍ୟ;
	    c_parser_consume_token (parser);

	    ଗଣନା objc_property_attribute_kind prop_kind
	      = objc_prop_attr_kind_for_rid (keyword);
	    property_attribute_info *prop
	      = ନୂତନ property_attribute_info (attr_name, attr_comb, prop_kind);
	    prop_attr_list.safe_ଠେଲ (prop);

	    ବୃକ୍ଷ meth_name;
	    ବାଛ (prop->prop_kind)
	      {
	      ପୂର୍ବନିର୍ଦ୍ଧାରିତ: ଭାଙ୍ଗ;
	      ସ୍ଥିତି OBJC_PROPERTY_ATTR_UNKNOWN:
		ଯଦି (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    add_at ? "@" : "", IDENTIFIER_POINTER (attr_name));
		ଅନ୍ୟଥା
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = ସତ୍ୟ;
		ଭାଙ୍ଗ;

	      ସ୍ଥିତି OBJC_PROPERTY_ATTR_GETTER:
	      ସ୍ଥିତି OBJC_PROPERTY_ATTR_SETTER:
		ଯଦି (c_parser_next_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = ସତ୍ୟ;
		    ଭାଙ୍ଗ;
		  }
		token = c_parser_peek_token (parser);
		attr_end = token->location;
		c_parser_consume_token (parser); /* eat the = */
		ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = ସତ୍ୟ;
		    ଭାଙ୍ଗ;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_end = get_finish (token->location);
		meth_name = token->ମୂଲ୍ୟ;
		c_parser_consume_token (parser);
		ଯଦି (prop->prop_kind == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    ଯଦି (c_parser_next_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_end, attr_start,
						   attr_end);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = ସତ୍ୟ;
		      }
		    ଅନ୍ୟଥା
		      {
			attr_end = get_finish (c_parser_peek_token
					       (parser)->location);
			c_parser_consume_token (parser);
		      }
		    attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		  }
		ଅନ୍ୟଥା
		  attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		prop->ident = meth_name;
		/* Updated location including all that was successfully
		   parsed.  */
		prop->prop_loc = attr_comb;
		ଭାଙ୍ଗ;
	    }

	  /* If we see a comma here, then keep going - even if we already
	     saw a syntax error.  For simple mistakes e.g. (assign, getter=x)
	     this makes a more useful output and avoid spurious warnings about
	     missing attributes that are, in fact, specified after the one with
	     the syntax error.  */
	  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ଅନ୍ୟଥା
	    ଭାଙ୍ଗ;
	}
      parser->objc_property_attr_context = ମିଥ୍ୟା;

      ଯଦି (syntax_error && c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      ଅନ୍ୟଥା
	syntax_error = ମିଥ୍ୟା, parens.skip_until_found_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  ବୃକ୍ଷ properties = c_parser_struct_declaration (parser, ଖାଲି);

  ଯଦି (properties == error_mark_ଗଣ୍ଠି)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, ଖାଲି);
  ଅନ୍ୟଥା
    {
      ଯଦି (properties == NULL_ବୃକ୍ଷ)
	c_parser_error (parser, "expected identifier");
      ଅନ୍ୟଥା
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  ପାଇଁ (; properties; properties = ବୃକ୍ଷ_CHAIN (properties))
	    objc_add_property_declaration (loc, copy_ଗଣ୍ଠି (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  ଯେତେବେଳେ (!prop_attr_list.is_empty())
    delete prop_attr_list.କାଢ଼ ();
  prop_attr_list.release ();
  parser->error = ମିଥ୍ୟା;
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
ସ୍ଥିର ଶୂନ୍ୟ
c_parser_objc_at_synthesize_declaration (c_parser *parser)
{
  ବୃକ୍ଷ list = NULL_ବୃକ୍ଷ;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      ବୃକ୍ଷ property, ivar;
      ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, ଖାଲି);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = ମିଥ୍ୟା;
	  ଫେରନ୍ତୁ;
	}
      property = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      c_parser_consume_token (parser);
      ଯଦି (c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_SEMICOLON, ଖାଲି);
	      parser->error = ମିଥ୍ୟା;
	      ଫେରନ୍ତୁ;
	    }
	  ivar = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା
	ivar = NULL_ବୃକ୍ଷ;
      list = chainon (list, build_ବୃକ୍ଷ_list (ivar, property));
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
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
ସ୍ଥିର ଶୂନ୍ୟ
c_parser_objc_at_dynamic_declaration (c_parser *parser)
{
  ବୃକ୍ଷ list = NULL_ବୃକ୍ଷ;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      ବୃକ୍ଷ property;
      ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, ଖାଲି);
	  parser->error = ମିଥ୍ୟା;
	  ଫେରନ୍ତୁ;
	}
      property = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      list = chainon (list, build_ବୃକ୍ଷ_list (NULL_ବୃକ୍ଷ, property));
      c_parser_consume_token (parser);
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_add_dynamic_declaration (loc, list);
}


/* Parse a pragma GCC ivdep.  */

ସ୍ଥିର ତାର୍କିକ
c_parse_pragma_ivdep (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* Parse a pragma GCC novector.  */

ସ୍ଥିର ତାର୍କିକ
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* Parse a pragma GCC unroll.  */

ସ୍ଥିର unsigned short
c_parser_pragma_unroll (c_parser *parser)
{
  unsigned short unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି).ମୂଲ୍ୟ;
  mark_exp_read (ପଦସମଷ୍ଟି);
  ପଦସମଷ୍ଟି = c_fully_fold (ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ଖାଲି);
  HOST_WIDE_INT lunroll = 0;
  ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି))
      || ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) != INTEGER_CST
      || (lunroll = ବୃକ୍ଷ_to_shwi (ପଦସମଷ୍ଟି)) < 0
      || lunroll >= USHRT_MAX)
    {
      error_at (location, "%<#pragma GCC unroll%> requires an"
		" assignment-expression that evaluates to a non-negative"
		" integral constant less than %u", USHRT_MAX);
      unroll = 0;
    }
  ଅନ୍ୟଥା
    {
      unroll = (unsigned short)lunroll;
      ଯଦି (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_to_pragma_eol (parser);
  ଫେରନ୍ତୁ unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

ସ୍ଥିର ତାର୍କିକ
c_parser_pragma (c_parser *parser, ଗଣନା pragma_context context, ତାର୍କିକ *if_p,
		 ବୃକ୍ଷ before_labels)
{
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା id;
  ଅଚଳ ଅକ୍ଷର *construct = ଖାଲି;

  ନିବେଶ_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_kind;
  gcc_assert (id != PRAGMA_NONE);
  ଯଦି (parser->omp_for_parse_state
      && parser->omp_for_parse_state->in_intervening_code
      && id >= PRAGMA_OMP__START_ && id <= PRAGMA_OMP__LAST_
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	ନିବେଶ_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->fail = ସତ୍ୟ;
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ଖାଲି);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

  ବାଛ (id)
    {
    ସ୍ଥିତି PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OACC_ENTER_DATA:
      ଯଦି (context != pragma_compound)
	{
	  construct = "acc enter data";
	in_compound:
	  ଯଦି (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ଖାଲି);
	      ଫେରନ୍ତୁ ସତ୍ୟ;
	    }
	  ଯାଅ bad_stmt;
	}
      c_parser_oacc_enter_exit_data (parser, ସତ୍ୟ);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OACC_EXIT_DATA:
      ଯଦି (context != pragma_compound)
	{
	  construct = "acc exit data";
	  ଯାଅ in_compound;
	}
      c_parser_oacc_enter_exit_data (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OACC_ROUTINE:
      ଯଦି (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ଖାଲି);
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
      c_parser_oacc_routine (parser, context);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OACC_UPDATE:
      ଯଦି (context != pragma_compound)
	{
	  construct = "acc update";
	  ଯାଅ in_compound;
	}
      c_parser_oacc_update (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_BARRIER:
      ଯଦି (context != pragma_compound)
	{
	  construct = "omp barrier";
	  ଯାଅ in_compound;
	}
      c_parser_omp_barrier (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_DEPOBJ:
      ଯଦି (context != pragma_compound)
	{
	  construct = "omp depobj";
	  ଯାଅ in_compound;
	}
      c_parser_omp_depobj (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_FLUSH:
      ଯଦି (context != pragma_compound)
	{
	  construct = "omp flush";
	  ଯାଅ in_compound;
	}
      c_parser_omp_flush (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_INTEROP:
      ଯଦି (context != pragma_compound)
	{
	  construct = "omp interop";
	  ଯାଅ in_compound;
	}
      c_parser_omp_interop (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_TASKWAIT:
      ଯଦି (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  ଯାଅ in_compound;
	}
      c_parser_omp_taskwait (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_TASKYIELD:
      ଯଦି (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  ଯାଅ in_compound;
	}
      c_parser_omp_taskyield (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_CANCEL:
      ଯଦି (context != pragma_compound)
	{
	  construct = "omp cancel";
	  ଯାଅ in_compound;
	}
      c_parser_omp_cancel (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_CANCELLATION_POINT:
      ଫେରନ୍ତୁ c_parser_omp_cancellation_point (parser, context);

    ସ୍ଥିତି PRAGMA_OMP_GROUPPRIVATE:
      c_parser_omp_groupprivate (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_THREADPRIVATE:
      c_parser_omp_threadprivate (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_TARGET:
      ଫେରନ୍ତୁ c_parser_omp_target (parser, context, if_p);

    ସ୍ଥିତି PRAGMA_OMP_BEGIN:
      c_parser_omp_begin (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_END:
      c_parser_omp_end (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_SCAN:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ଖାଲି);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ଖାଲି);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_DECLARE:
      ଫେରନ୍ତୁ c_parser_omp_declare (parser, context);

    ସ୍ଥିତି PRAGMA_OMP_REQUIRES:
      ଯଦି (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ଖାଲି);
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
      c_parser_omp_requires (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_ALLOCATE:
      c_parser_omp_allocate (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_ASSUMES:
      ଯଦି (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp assumes");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ଖାଲି);
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
      c_parser_omp_assumes (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      ଫେରନ୍ତୁ ସତ୍ୟ;

    ସ୍ଥିତି PRAGMA_OMP_ERROR:
      ଫେରନ୍ତୁ c_parser_omp_error (parser, context);

    ସ୍ଥିତି PRAGMA_OMP_ORDERED:
      ଫେରନ୍ତୁ c_parser_omp_ordered (parser, context, if_p);

    ସ୍ଥିତି PRAGMA_NOVECTOR:
    ସ୍ଥିତି PRAGMA_UNROLL:
    ସ୍ଥିତି PRAGMA_IVDEP:
      {
	ତାର୍କିକ novector = ମିଥ୍ୟା;
	unsigned short unroll = 0;
	ତାର୍କିକ ivdep = ମିଥ୍ୟା;

	ବାଛ (id)
	  {
	  ସ୍ଥିତି PRAGMA_NOVECTOR:
	    novector = c_parse_pragma_novector (parser);
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି PRAGMA_UNROLL:
	    unroll = c_parser_pragma_unroll (parser);
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି PRAGMA_IVDEP:
	    ivdep = c_parse_pragma_ivdep (parser);
	    ଭାଙ୍ଗ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    gcc_unreachable ();
	  }

	c_token *tok = c_parser_peek_token (parser);
	ତାର୍କିକ has_more = tok->type == CPP_PRAGMA;
	ଯେତେବେଳେ (has_more)
	  {
	    ବାଛ (tok->pragma_kind)
	      {
	      ସ୍ଥିତି PRAGMA_IVDEP:
		ivdep = c_parse_pragma_ivdep (parser);
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି PRAGMA_UNROLL:
		unroll = c_parser_pragma_unroll (parser);
		ଭାଙ୍ଗ;
	      ସ୍ଥିତି PRAGMA_NOVECTOR:
		novector = c_parse_pragma_novector (parser);
		ଭାଙ୍ଗ;
	      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		has_more = ମିଥ୍ୟା;
		ଭାଙ୍ଗ;
	      }
	    tok = c_parser_peek_token (parser);
	    has_more = has_more && tok->type == CPP_PRAGMA;
	  }
	ଯଦି (!c_parser_next_token_is_keyword (parser, RID_FOR)
	    && !c_parser_next_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_next_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	  }
	ଯଦି (c_parser_next_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	ଅନ୍ୟଥା
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      ଫେରନ୍ତୁ ସତ୍ୟ;

    ସ୍ଥିତି PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ଖାଲି);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;

    ସ୍ଥିତି PRAGMA_OACC_WAIT:
      ଯଦି (context != pragma_compound)
	{
	  construct = "acc wait";
	  ଯାଅ in_compound;
	}
	/* FALL THROUGH.  */

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଯଦି (id < PRAGMA_FIRST_EXTERNAL)
	{
	  ଯଦି (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ଖାଲି);
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;
	    }
	  c_parser_omp_construct (parser, if_p);
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	}
      ଭାଙ୍ଗ;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = ସତ୍ୟ;
  c_parser_skip_to_pragma_eol (parser);

  ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* The interface the pragma parsers have to the lexer.  */

ଗଣନା cpp_ttype
pragma_lex (ବୃକ୍ଷ *ମୂଲ୍ୟ, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  ଗଣନା cpp_ttype ret = tok->type;

  *ମୂଲ୍ୟ = tok->ମୂଲ୍ୟ;
  ଯଦି (loc)
    *loc = tok->location;

  ଯଦି (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  ଅନ୍ୟଥା ଯଦି (ret == CPP_STRING)
    *ମୂଲ୍ୟ = c_parser_string_literal (the_parser, ମିଥ୍ୟା, ମିଥ୍ୟା).ମୂଲ୍ୟ;
  ଅନ୍ୟଥା
    {
      ଯଦି (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  ଫେରନ୍ତୁ ret;
}

ଶୂନ୍ୟ
pragma_lex_discard_to_eol ()
{
  cpp_ttype type;
  କର
    {
      type = c_parser_peek_token (the_parser)->type;
      gcc_assert (type != CPP_EOF);
      c_parser_consume_token (the_parser);
    } ଯେତେବେଳେ (type != CPP_PRAGMA_EOL);
}

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  ବୃକ୍ଷ name = ଖାଲି;

  parser->lex_joined_string = ସତ୍ୟ;
  c_parser_consume_pragma (parser);
  ଯଦି (c_parser_next_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      c_parser_consume_token (parser);
    }
  ଅନ୍ୟଥା
    c_parser_error (parser, "expected string literal");
  c_parser_skip_to_pragma_eol (parser);
  parser->lex_joined_string = ମିଥ୍ୟା;

  ଯଦି (name)
    c_common_pch_pragma (parse_in, ବୃକ୍ଷ_STRING_POINTER (name));
}

/* OpenACC and OpenMP parsing routines.  */

/* Returns name of the next clause.
   If the clause is not recognized PRAGMA_OMP_CLAUSE_NONE is returned and
   the token is not consumed.  Otherwise appropriate pragma_omp_clause is
   returned and the token is consumed.  */

ସ୍ଥିର pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause result = PRAGMA_OMP_CLAUSE_NONE;

  ଯଦି (c_parser_next_token_is_keyword (parser, RID_AUTO))
    result = PRAGMA_OACC_CLAUSE_AUTO;
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_IF))
    result = PRAGMA_OMP_CLAUSE_IF;
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    result = PRAGMA_OMP_CLAUSE_DEFAULT;
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_FOR))
    result = PRAGMA_OMP_CLAUSE_FOR;
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);

      ବାଛ (p[0])
	{
	ସ୍ଥିତି 'a':
	  ଯଦି (!strcmp ("affinity", p))
	    result = PRAGMA_OMP_CLAUSE_AFFINITY;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("aligned", p))
	    result = PRAGMA_OMP_CLAUSE_ALIGNED;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("allocate", p))
	    result = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("async", p))
	    result = PRAGMA_OACC_CLAUSE_ASYNC;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("attach", p))
	    result = PRAGMA_OACC_CLAUSE_ATTACH;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'b':
	  ଯଦି (!strcmp ("bind", p))
	    result = PRAGMA_OMP_CLAUSE_BIND;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'c':
	  ଯଦି (!strcmp ("collapse", p))
	    result = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("copy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("copyin", p))
	    result = PRAGMA_OMP_CLAUSE_COPYIN;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("copyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
          ଅନ୍ୟଥା ଯଦି (!strcmp ("copyprivate", p))
	    result = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("create", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'd':
	  ଯଦି (!strcmp ("defaultmap", p))
	    result = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("delete", p))
	    result = PRAGMA_OACC_CLAUSE_DELETE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("depend", p))
	    result = PRAGMA_OMP_CLAUSE_DEPEND;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("destroy", p))
	    result = PRAGMA_OMP_CLAUSE_DESTROY;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("detach", p))
	    result = PRAGMA_OACC_CLAUSE_DETACH;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("device", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("deviceptr", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("device_resident", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("device_type", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("dist_schedule", p))
	    result = PRAGMA_OMP_CLAUSE_DIST_SCHEDULE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("doacross", p))
	    result = PRAGMA_OMP_CLAUSE_DOACROSS;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("dyn_groupprivate", p))
	    result = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'e':
	  ଯଦି (!strcmp ("enter", p))
	    result = PRAGMA_OMP_CLAUSE_ENTER;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'f':
	  ଯଦି (!strcmp ("filter", p))
	    result = PRAGMA_OMP_CLAUSE_FILTER;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("final", p))
	    result = PRAGMA_OMP_CLAUSE_FINAL;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("finalize", p))
	    result = PRAGMA_OACC_CLAUSE_FINALIZE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("firstprivate", p))
	    result = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("from", p))
	    result = PRAGMA_OMP_CLAUSE_FROM;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("full", p))
	    result = PRAGMA_OMP_CLAUSE_FULL;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'g':
	  ଯଦି (!strcmp ("gang", p))
	    result = PRAGMA_OACC_CLAUSE_GANG;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("grainsize", p))
	    result = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'h':
	  ଯଦି (!strcmp ("has_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("hint", p))
	    result = PRAGMA_OMP_CLAUSE_HINT;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("host", p))
	    result = PRAGMA_OACC_CLAUSE_HOST;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'i':
	  ଯଦି (!strcmp ("if_present", p))
	    result = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("in_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_IN_REDUCTION;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("inbranch", p))
	    result = PRAGMA_OMP_CLAUSE_INBRANCH;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("independent", p))
	    result = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("indirect", p))
	    result = PRAGMA_OMP_CLAUSE_INDIRECT;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("init", p))
	    result = PRAGMA_OMP_CLAUSE_INIT;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("is_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("interop", p))
	    result = PRAGMA_OMP_CLAUSE_INTEROP;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'l':
	  ଯଦି (!strcmp ("lastprivate", p))
	    result = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("linear", p))
	    result = PRAGMA_OMP_CLAUSE_LINEAR;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("link", p))
	    result = PRAGMA_OMP_CLAUSE_LINK;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("local", p))
	    result = PRAGMA_OMP_CLAUSE_LOCAL;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'm':
	  ଯଦି (!strcmp ("map", p))
	    result = PRAGMA_OMP_CLAUSE_MAP;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("mergeable", p))
	    result = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'n':
	  ଯଦି (!strcmp ("no_create", p))
	    result = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("nocontext", p))
	    result = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("nogroup", p))
	    result = PRAGMA_OMP_CLAUSE_NOGROUP;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("nohost", p))
	    result = PRAGMA_OACC_CLAUSE_NOHOST;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("nontemporal", p))
	    result = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("notinbranch", p))
	    result = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("novariants", p))
	    result = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("nowait", p))
	    result = PRAGMA_OMP_CLAUSE_NOWAIT;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("num_gangs", p))
	    result = PRAGMA_OACC_CLAUSE_ଅଙ୍କ_GANGS;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("num_tasks", p))
	    result = PRAGMA_OMP_CLAUSE_ଅଙ୍କ_TASKS;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("num_teams", p))
	    result = PRAGMA_OMP_CLAUSE_ଅଙ୍କ_TEAMS;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("num_threads", p))
	    result = PRAGMA_OMP_CLAUSE_ଅଙ୍କ_THREADS;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("num_workers", p))
	    result = PRAGMA_OACC_CLAUSE_ଅଙ୍କ_WORKERS;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'o':
	  ଯଦି (!strcmp ("ordered", p))
	    result = PRAGMA_OMP_CLAUSE_ORDERED;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("order", p))
	    result = PRAGMA_OMP_CLAUSE_ORDER;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'p':
	  ଯଦି (!strcmp ("parallel", p))
	    result = PRAGMA_OMP_CLAUSE_PARALLEL;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("partial", p))
	    result = PRAGMA_OMP_CLAUSE_PARTIAL;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("present", p))
	    result = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("present_or_copy", p)
		   || !strcmp ("pcopy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("present_or_copyin", p)
		   || !strcmp ("pcopyin", p))
	    result = PRAGMA_OACC_CLAUSE_COPYIN;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("present_or_copyout", p)
		   || !strcmp ("pcopyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("present_or_create", p)
		   || !strcmp ("pcreate", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("priority", p))
	    result = PRAGMA_OMP_CLAUSE_PRIORITY;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("private", p))
	    result = PRAGMA_OMP_CLAUSE_PRIVATE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("proc_bind", p))
	    result = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'r':
	  ଯଦି (!strcmp ("reduction", p))
	    result = PRAGMA_OMP_CLAUSE_REDUCTION;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 's':
	  ଯଦି (!strcmp ("safelen", p))
	    result = PRAGMA_OMP_CLAUSE_SAFELEN;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("schedule", p))
	    result = PRAGMA_OMP_CLAUSE_SCHEDULE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("sections", p))
	    result = PRAGMA_OMP_CLAUSE_SECTIONS;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("self", p))
	    result = PRAGMA_OACC_CLAUSE_SELF;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("seq", p))
	    result = PRAGMA_OACC_CLAUSE_SEQ;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("shared", p))
	    result = PRAGMA_OMP_CLAUSE_SHARED;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("simd", p))
	    result = PRAGMA_OMP_CLAUSE_SIMD;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("simdlen", p))
	    result = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 't':
	  ଯଦି (!strcmp ("task_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("taskgroup", p))
	    result = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("thread_limit", p))
	    result = PRAGMA_OMP_CLAUSE_THREAD_LIMIT;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("threads", p))
	    result = PRAGMA_OMP_CLAUSE_THREADS;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("tile", p))
	    result = PRAGMA_OACC_CLAUSE_TILE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("to", p))
	    result = PRAGMA_OMP_CLAUSE_TO;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'u':
	  ଯଦି (!strcmp ("uniform", p))
	    result = PRAGMA_OMP_CLAUSE_UNIFORM;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("untied", p))
	    result = PRAGMA_OMP_CLAUSE_UNTIED;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("use", p))
	    result = PRAGMA_OMP_CLAUSE_USE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("use_device", p))
	    result = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("use_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("use_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("uses_allocators", p))
	    result = PRAGMA_OMP_CLAUSE_USES_ALLOCATORS;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'v':
	  ଯଦି (!strcmp ("vector", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("vector_length", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR_LENGTH;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି 'w':
	  ଯଦି (!strcmp ("wait", p))
	    result = PRAGMA_OACC_CLAUSE_WAIT;
	  ଅନ୍ୟଥା ଯଦି (!strcmp ("worker", p))
	    result = PRAGMA_OACC_CLAUSE_WORKER;
	  ଭାଙ୍ଗ;
	}
    }

  ଯଦି (result != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  ଫେରନ୍ତୁ result;
}

/* Validate that a clause of the given type does not already exist.  */

ସ୍ଥିର ଶୂନ୍ୟ
check_no_duplicate_clause (ବୃକ୍ଷ clauses, ଗଣନା omp_clause_code code,
			   ଅଚଳ ଅକ୍ଷର *name)
{
  ଯଦି (ବୃକ୍ଷ c = omp_find_clause (clauses, code))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, ବୃକ୍ଷ list)
{
  vec<ବୃକ୍ଷ, va_gc> *args;
  ବୃକ୍ଷ t, args_ବୃକ୍ଷ;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  args = c_parser_ପଦସମଷ୍ଟି_list (parser, ମିଥ୍ୟା, ସତ୍ୟ, ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି);
  args_ବୃକ୍ଷ = build_ବୃକ୍ଷ_list_vec (args);

  ପାଇଁ (t = args_ବୃକ୍ଷ; t; t = ବୃକ୍ଷ_CHAIN (t))
    {
      ବୃକ୍ଷ targ = ବୃକ୍ଷ_ମୂଲ୍ୟ (t);

      ଯଦି (targ != error_mark_ଗଣ୍ଠି)
	{
	  ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_ଗଣ୍ଠି;
	    }
	  ଅନ୍ୟଥା
	    {
	      ବୃକ୍ଷ c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_ବୃକ୍ଷ_vector (args);
  parens.require_close (parser);
  ଫେରନ୍ତୁ list;
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

ସଂରଚନା omp_dim
{
  ବୃକ୍ଷ ତଳ_bound, length;
  location_t loc;
  ତାର୍କିକ no_colon;
  omp_dim (ବୃକ୍ଷ lb, ବୃକ୍ଷ len, location_t lo, ତାର୍କିକ nc)
  : ତଳ_bound (lb), length (len), loc (lo), no_colon (nc) {}
};

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    ଗଣନା omp_clause_code kind, ବୃକ୍ଷ list,
			    ତାର୍କିକ map_lvalue = ମିଥ୍ୟା)
{
  auto_vec<omp_dim> dims;
  ତାର୍କିକ array_section_p;
  auto_vec<c_token> tokens;
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା tokens_avail = 0;
  c_token *saved_tokens = ଖାଲି;

  ଯେତେବେଳେ (1)
    {
      ବୃକ୍ଷ t = NULL_ବୃକ୍ଷ;
      location_t tloc = c_parser_peek_token (parser)->location;

      ଯଦି (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
	    {
	      ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
	      ଯଦି (kind == OMP_CLAUSE_DEPEND
		  && c_parser_next_token_is_keyword (parser,
						     RID_OMP_ALL_MEMORY)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = ridpointers[RID_OMP_ALL_MEMORY];
		  c_parser_consume_token (parser);
		}
	      ଅନ୍ୟଥା
		ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	      ଯଦି (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
		{
		  ବୃକ୍ଷ u = build_omp_clause (clause_loc, kind);
		  OMP_CLAUSE_DECL (u) = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      ଯଦି (c_parser_next_token_is_not (parser, CPP_COMMA))
		ଭାଙ୍ଗ;

	      c_parser_consume_token (parser);
	      ଜାରି;
	    }

	  tokens.truncate (0);
	  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା nesting_depth = 0;
	  ଯେତେବେଳେ (1)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      ବାଛ (token->type)
		{
		ସ୍ଥିତି CPP_EOF:
		ସ୍ଥିତି CPP_PRAGMA_EOL:
		  ଭାଙ୍ଗ;
		ସ୍ଥିତି CPP_OPEN_BRACE:
		ସ୍ଥିତି CPP_OPEN_PAREN:
		ସ୍ଥିତି CPP_OPEN_SQUARE:
		  ++nesting_depth;
		  ଯାଅ add;
		ସ୍ଥିତି CPP_CLOSE_BRACE:
		ସ୍ଥିତି CPP_CLOSE_PAREN:
		ସ୍ଥିତି CPP_CLOSE_SQUARE:
		  ଯଦି (nesting_depth-- == 0)
		    ଭାଙ୍ଗ;
		  ଯାଅ add;
		ସ୍ଥିତି CPP_COMMA:
		  ଯଦି (nesting_depth == 0)
		    ଭାଙ୍ଗ;
		  ଯାଅ add;
		ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		add:
		  tokens.safe_ଠେଲ (*token);
		  c_parser_consume_token (parser);
		  ଜାରି;
		}
	      ଭାଙ୍ଗ;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  memset (&eof_token, 0, ଆକାର (eof_token));
	  eof_token.type = CPP_EOF;
	  tokens.safe_ଠେଲ (eof_token);
	  tokens.safe_ଠେଲ (eof_token);

	  saved_tokens = parser->tokens;
	  tokens_avail = parser->tokens_avail;
	  parser->tokens = tokens.address ();
	  parser->tokens_avail = tokens.length ();
	}
      ଅନ୍ୟଥା ଯଦି (map_lvalue
	       && (kind == OMP_CLAUSE_MAP
		   || kind == OMP_CLAUSE_TO
		   || kind == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  ତାର୍କିକ save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = ସତ୍ୟ;
	  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	  ଯଦି (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
	    mark_exp_read (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  ବୃକ୍ଷ decl = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  ଯଦି (ବୃକ୍ଷ_CODE (decl) == OMP_ARRAY_SECTION)
	    {
	      ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (decl) == OMP_ARRAY_SECTION)
		{
		  ବୃକ୍ଷ ତଳ_bound = ବୃକ୍ଷ_OPERAND (decl, 1);
		  ବୃକ୍ଷ length = ବୃକ୍ଷ_OPERAND (decl, 2);
		  dims.safe_ଠେଲ (omp_dim (ତଳ_bound, length, loc, ମିଥ୍ୟା));
		  decl = ବୃକ୍ଷ_OPERAND (decl, 0);
		}

	      ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (decl) == ARRAY_REF
		     || ବୃକ୍ଷ_CODE (decl) == INDIRECT_REF
		     || ବୃକ୍ଷ_CODE (decl) == COMPOUND_ପଦସମଷ୍ଟି)
		{
		  ଯଦି (ବୃକ୍ଷ_CODE (decl) == COMPOUND_ପଦସମଷ୍ଟି)
		    {
		      decl = ବୃକ୍ଷ_OPERAND (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (decl) == INDIRECT_REF)
		    {
		      dims.safe_ଠେଲ (omp_dim (integer_zero_ଗଣ୍ଠି,
					       integer_one_ଗଣ୍ଠି, loc, ସତ୍ୟ));
		      decl = ବୃକ୍ଷ_OPERAND (decl, 0);
		    }
		  ଅନ୍ୟଥା  /* ARRAY_REF. */
		    {
		      ବୃକ୍ଷ index = ବୃକ୍ଷ_OPERAND (decl, 1);
		      dims.safe_ଠେଲ (omp_dim (index, integer_one_ଗଣ୍ଠି, loc,
					       ସତ୍ୟ));
		      decl = ବୃକ୍ଷ_OPERAND (decl, 0);
		    }
		}

	      ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = dims.length () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].ତଳ_bound,
						dims[i].length);
	    }
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (decl) == INDIRECT_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = ବୃକ୍ଷ_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_ଗଣ୍ଠି,
					      integer_one_ଗଣ୍ଠି);
	    }
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (decl) == ARRAY_REF)
	    {
	      ବୃକ୍ଷ idx = ବୃକ୍ଷ_OPERAND (decl, 1);

	      decl = ବୃକ୍ଷ_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_ଗଣ୍ଠି);
	    }
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (decl) == NON_LVALUE_ପଦସମଷ୍ଟି
		   || CONVERT_ପଦସମଷ୍ଟି_P (decl))
	    decl = ବୃକ୍ଷ_OPERAND (decl, 0);

	  ବୃକ୍ଷ u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  ଯାଅ next_item;
	}

      ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->ମୂଲ୍ୟ);

	  ଯଦି (t == NULL_ବୃକ୍ଷ)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	      t = error_mark_ଗଣ୍ଠି;
	    }

	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).ମୂଲ୍ୟ;
      ଅନ୍ୟଥା
	{
	  c_parser_error (parser, "expected identifier");
	  ଭାଙ୍ଗ;
	}

      ଯଦି (t == error_mark_ଗଣ୍ଠି)
	;
      ଅନ୍ୟଥା ଯଦି (kind != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  ବାଛ (kind)
	    {
	    ସ୍ଥିତି OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      ଯଦି (c_parser_peek_token (parser)->type != CPP_OPEN_SQUARE)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_ଗଣ୍ଠି;
		  ଭାଙ୍ଗ;
		}
	      /* FALLTHROUGH  */
	    ସ୍ଥିତି OMP_CLAUSE_MAP:
	    ସ୍ଥିତି OMP_CLAUSE_FROM:
	    ସ୍ଥିତି OMP_CLAUSE_TO:
	    start_component_ref:
	      ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_DOT)
		     || c_parser_next_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  ଯଦି (c_parser_next_token_is (parser, CPP_DEREF))
		    {
		      c_ପଦସମଷ୍ଟି t_ପଦସମଷ୍ଟି;
		      t_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = t;
		      t_ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
		      t_ପଦସମଷ୍ଟି.original_type = ଖାଲି;
		      set_c_ପଦସମଷ୍ଟି_source_range (&t_ପଦସମଷ୍ଟି, op_loc, op_loc);
		      t_ପଦସମଷ୍ଟି.m_decimal = 0;
		      t_ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (op_loc, t_ପଦସମଷ୍ଟି,
							 ସତ୍ୟ, ମିଥ୍ୟା);
		      t = build_indirect_ref (op_loc, t_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, RO_ARROW);
		      arrow_loc = t_ପଦସମଷ୍ଟି.get_location ();
		    }
		  c_parser_consume_token (parser);
		  ଯଦି (!c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_ଗଣ୍ଠି;
		      ଭାଙ୍ଗ;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  ବୃକ୍ଷ ident = comp_tok->ମୂଲ୍ୟ;
		  location_t comp_loc = comp_tok->location;
		  c_parser_consume_token (parser);
		  t = build_component_ref (op_loc, t, ident, comp_loc,
					   arrow_loc);
		}
	      /* FALLTHROUGH  */
	    ସ୍ଥିତି OMP_CLAUSE_AFFINITY:
	    ସ୍ଥିତି OMP_CLAUSE_DEPEND:
	    ସ୍ଥିତି OMP_CLAUSE_REDUCTION:
	    ସ୍ଥିତି OMP_CLAUSE_IN_REDUCTION:
	    ସ୍ଥିତି OMP_CLAUSE_TASK_REDUCTION:
	    ସ୍ଥିତି OMP_CLAUSE_HAS_DEVICE_ADDR:
	      array_section_p = ମିଥ୍ୟା;
	      dims.truncate (0);
	      ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  ବୃକ୍ଷ ତଳ_bound = NULL_ବୃକ୍ଷ, length = NULL_ବୃକ୍ଷ;
		  ତାର୍କିକ no_colon = ମିଥ୍ୟା;

		  c_parser_consume_token (parser);
		  ଯଦି (!c_parser_next_token_is (parser, CPP_COLON))
		    {
		      location_t ପଦସମଷ୍ଟି_loc
			= c_parser_peek_token (parser)->location;
		      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_expression (parser);
		      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି,
						       ମିଥ୍ୟା, ସତ୍ୟ);
		      ତଳ_bound = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
		      loc = ପଦସମଷ୍ଟି_loc;
		    }
		  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    {
		      length = integer_one_ଗଣ୍ଠି;
		      no_colon = ସତ୍ୟ;
		    }
		  ଅନ୍ୟଥା
		    {
		      /* Look for `:'.  */
		      ଯଦି (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_ଗଣ୍ଠି;
			  ଭାଙ୍ଗ;
			}
		      array_section_p = ସତ୍ୟ;
		      ଯଦି (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
			{
			  location_t ପଦସମଷ୍ଟି_loc
			    = c_parser_peek_token (parser)->location;
			  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_expression (parser);
			  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି,
							   ମିଥ୍ୟା, ସତ୍ୟ);
			  length = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
			}
		    }
		  /* Look for the closing `]'.  */
		  ଯଦି (!c_parser_require (parser, CPP_CLOSE_SQUARE,
					 "expected %<]%>"))
		    {
		      t = error_mark_ଗଣ୍ଠି;
		      ଭାଙ୍ଗ;
		    }

		  dims.safe_ଠେଲ (omp_dim (ତଳ_bound, length, loc, no_colon));
		}

	      ଯଦି (t != error_mark_ଗଣ୍ଠି)
		{
		  ଯଦି ((kind == OMP_CLAUSE_MAP
		       || kind == OMP_CLAUSE_FROM
		       || kind == OMP_CLAUSE_TO)
		      && !array_section_p
		      && (c_parser_next_token_is (parser, CPP_DOT)
			  || c_parser_next_token_is (parser, CPP_DEREF)))
		    {
		      ପାଇଁ (unsigned i = 0; i < dims.length (); i++)
			{
			  gcc_assert (dims[i].length == integer_one_ଗଣ୍ଠି);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].ତଳ_bound);
			}
		      ଯାଅ start_component_ref;
		    }
		  ଅନ୍ୟଥା
		    ପାଇଁ (unsigned i = 0; i < dims.length (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].ତଳ_bound,
						   dims[i].length);
		}

	      ଯଦି ((kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_ଗଣ୍ଠି
		  && parser->tokens_avail != 2)
		{
		  ଯଦି (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_ଗଣ୍ଠି;
		    }
		  ଅନ୍ୟଥା
		    {
		      parser->tokens = tokens.address ();
		      parser->tokens_avail = tokens.length ();

		      t = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି).ମୂଲ୍ୟ;
		      ଯଦି (t != error_mark_ଗଣ୍ଠି && parser->tokens_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_ଗଣ୍ଠି;
			}
		    }
		}
	      ଭାଙ୍ଗ;
	    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	      ଭାଙ୍ଗ;
	    }

	  ଯଦି (t != error_mark_ଗଣ୍ଠି)
	    {
	      ବୃକ୍ଷ u = build_omp_clause (clause_loc, kind);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      ଅନ୍ୟଥା  /* kind == OMP_CLAUSE_ERROR */
	list = ବୃକ୍ଷ_cons (t, build_empty_stmt (tloc), list);

      ଯଦି (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}

    next_item:
      ଯଦି (c_parser_next_token_is_not (parser, CPP_COMMA))
	ଭାଙ୍ଗ;

      c_parser_consume_token (parser);
    }

  ଫେରନ୍ତୁ list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_var_list_parens (c_parser *parser, ଗଣନା omp_clause_code kind,
			      ବୃକ୍ଷ list, ତାର୍କିକ map_lvalue = ମିଥ୍ୟା)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  ଯଦି (parser->in_omp_decl_attribute)
    {
      ଯଦି (kind)
	{
	  ବୃକ୍ଷ u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = parser->in_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  ଫେରନ୍ତୁ u;
	}
      ଅନ୍ୟଥା
	ଫେରନ୍ତୁ ବୃକ୍ଷ_cons (parser->in_omp_decl_attribute, NULL_ବୃକ୍ଷ, list);
    }

  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, kind, list, map_lvalue);
      parens.skip_until_found_close (parser);
    }
  ଫେରନ୍ତୁ list;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_data_clause (c_parser *parser, pragma_omp_clause c_kind,
			   ବୃକ୍ଷ list)
{
  ଗଣନା gomp_map_kind kind;
  ବାଛ (c_kind)
    {
    ସ୍ଥିତି PRAGMA_OACC_CLAUSE_ATTACH:
      kind = GOMP_MAP_ATTACH;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_CLAUSE_COPY:
      kind = GOMP_MAP_TOFROM;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_CLAUSE_COPYIN:
      kind = GOMP_MAP_TO;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_CLAUSE_COPYOUT:
      kind = GOMP_MAP_FROM;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_CLAUSE_CREATE:
      kind = GOMP_MAP_ALLOC;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_CLAUSE_DELETE:
      kind = GOMP_MAP_RELEASE;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_CLAUSE_DETACH:
      kind = GOMP_MAP_DETACH;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_CLAUSE_DEVICE:
      kind = GOMP_MAP_FORCE_TO;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      kind = GOMP_MAP_DEVICE_RESIDENT;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_CLAUSE_LINK:
      kind = GOMP_MAP_LINK;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_CLAUSE_NO_CREATE:
      kind = GOMP_MAP_IF_PRESENT;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_CLAUSE_PRESENT:
      kind = GOMP_MAP_FORCE_PRESENT;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    ସ୍ଥିତି PRAGMA_OACC_CLAUSE_HOST:
      kind = GOMP_MAP_FORCE_FROM;
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    }

  ବୃକ୍ଷ nl = list;
  ତାର୍କିକ readonly = ମିଥ୍ୟା;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      ଯଦି (c_kind == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ଯଦି (token->type == CPP_NAME
	      && !strcmp (IDENTIFIER_POINTER (token->ମୂଲ୍ୟ), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = ସତ୍ୟ;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       ମିଥ୍ୟା);
      parens.skip_until_found_close (parser);
    }

  ପାଇଁ (ବୃକ୍ଷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      ଯଦି (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  ଫେରନ୍ତୁ nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_data_clause_deviceptr (c_parser *parser, ବୃକ୍ଷ list)
{
  ବୃକ୍ଷ vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ଖାଲି);
  ପାଇଁ (t = vars; t && t; t = ବୃକ୍ଷ_CHAIN (t))
    {
      ବୃକ୍ଷ v = ବୃକ୍ଷ_PURPOSE (t);
      location_t loc = ପଦସମଷ୍ଟି_LOCATION (ବୃକ୍ଷ_ମୂଲ୍ୟ (t));

      ଯଦି (!VAR_P (v) && ବୃକ୍ଷ_CODE (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_TYPE (v) == error_mark_ଗଣ୍ଠି)
	;
      ଅନ୍ୟଥା ଯଦି (!POINTER_TYPE_P (ବୃକ୍ଷ_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      ବୃକ୍ଷ u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  ଫେରନ୍ତୁ list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_collapse (c_parser *parser, ବୃକ୍ଷ list)
{
  ବୃକ୍ଷ c, ଅଙ୍କ = error_mark_ଗଣ୍ଠି;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      ଅଙ୍କ = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି).ମୂଲ୍ୟ;
      parens.skip_until_found_close (parser);
    }
  ଯଦି (ଅଙ୍କ == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ list;
  mark_exp_read (ଅଙ୍କ);
  ଅଙ୍କ = c_fully_fold (ଅଙ୍କ, ମିଥ୍ୟା, ଖାଲି);
  ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ଅଙ୍କ))
      || !ବୃକ୍ଷ_fits_shwi_p (ଅଙ୍କ)
      || (n = ବୃକ୍ଷ_to_shwi (ଅଙ୍କ)) <= 0
      || (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      ଫେରନ୍ତୁ list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_ପଦସମଷ୍ଟି (c) = ଅଙ୍କ;
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_copyin (c_parser *parser, ବୃକ୍ଷ list)
{
  ଫେରନ୍ତୁ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_copyprivate (c_parser *parser, ବୃକ୍ଷ list)
{
  ଫେରନ୍ତୁ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_default (c_parser *parser, ବୃକ୍ଷ list, ତାର୍କିକ is_oacc)
{
  ଗଣନା omp_clause_default_kind kind = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ c;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);

      ବାଛ (p[0])
	{
	ସ୍ଥିତି 'n':
	  ଯଦି (strcmp ("none", p) != 0)
	    ଯାଅ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_NONE;
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି 'p':
	  ଯଦି (is_oacc)
	    {
	      ଯଦି (strcmp ("present", p) != 0)
		ଯାଅ invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  ଅନ୍ୟଥା
	    {
	      ଯଦି (strcmp ("private", p) != 0)
		ଯାଅ invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRIVATE;
	    }
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି 'f':
	  ଯଦି (strcmp ("firstprivate", p) != 0 || is_oacc)
	    ଯାଅ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି 's':
	  ଯଦି (strcmp ("shared", p) != 0 || is_oacc)
	    ଯାଅ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_SHARED;
	  ଭାଙ୍ଗ;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଯାଅ invalid_kind;
	}

      c_parser_consume_token (parser);
    }
  ଅନ୍ୟଥା
    {
    invalid_kind:
      ଯଦି (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      ଅନ୍ୟଥା
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_found_close (parser);

  ଯଦି (kind == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    ଫେରନ୍ତୁ list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_KIND (c) = kind;

  ଫେରନ୍ତୁ c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_firstprivate (c_parser *parser, ବୃକ୍ଷ list)
{
  ଫେରନ୍ତୁ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_final (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      ବୃକ୍ଷ t, c;
      ଯଦି (!parens.require_open (parser))
	t = error_mark_ଗଣ୍ଠି;
      ଅନ୍ୟଥା
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	  t = convert_lvalue_to_rvalue (eloc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ସତ୍ୟ).ମୂଲ୍ୟ;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);
	  parens.skip_until_found_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_ପଦସମଷ୍ଟି (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }
  ଅନ୍ୟଥା
    c_parser_error (parser, "expected %<(%>");

  ଫେରନ୍ତୁ list;
}

/* OpenMP 5.1:
   indirect [( expression )]
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_indirect (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t location = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ t;

  ଯଦି (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      ଯଦି (!parens.require_open (parser))
	ଫେରନ୍ତୁ list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (loc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ସତ୍ୟ);
      t = c_objc_common_truthvalue_conversion (loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
      t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);
      ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t))
	  || ବୃକ୍ଷ_CODE (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  ଫେରନ୍ତୁ list;
	}
      parens.skip_until_found_close (parser);
    }
  ଅନ୍ୟଥା
    t = integer_one_ଗଣ୍ଠି;

  check_no_duplicate_clause (list, OMP_CLAUSE_INDIRECT, "indirect");

  ବୃକ୍ଷ c = build_omp_clause (location, OMP_CLAUSE_INDIRECT);
  OMP_CLAUSE_INDIRECT_ପଦସମଷ୍ଟି (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;

  ଫେରନ୍ତୁ c;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_if (c_parser *parser, ବୃକ୍ଷ list, ତାର୍କିକ is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  ଗଣନା ବୃକ୍ଷ_code if_modifier = ERROR_MARK;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  ଯଦି (is_omp && c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା n = 2;
      ଯଦି (strcmp (p, "cancel") == 0)
	if_modifier = VOID_CST;
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "parallel") == 0)
	if_modifier = OMP_PARALLEL;
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "simd") == 0)
	if_modifier = OMP_SIMD;
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "task") == 0)
	if_modifier = OMP_TASK;
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "taskloop") == 0)
	if_modifier = OMP_TASKLOOP;
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "target") == 0)
	{
	  if_modifier = OMP_TARGET;
	  ଯଦି (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	    {
	      p = IDENTIFIER_POINTER (c_parser_peek_2nd_token (parser)->ମୂଲ୍ୟ);
	      ଯଦି (strcmp ("data", p) == 0)
		if_modifier = OMP_TARGET_DATA;
	      ଅନ୍ୟଥା ଯଦି (strcmp ("update", p) == 0)
		if_modifier = OMP_TARGET_UPDATE;
	      ଅନ୍ୟଥା ଯଦି (strcmp ("enter", p) == 0)
		if_modifier = OMP_TARGET_ENTER_DATA;
	      ଅନ୍ୟଥା ଯଦି (strcmp ("exit", p) == 0)
		if_modifier = OMP_TARGET_EXIT_DATA;
	      ଯଦି (if_modifier != OMP_TARGET)
		{
		  n = 3;
		  c_parser_consume_token (parser);
		}
	      ଅନ୍ୟଥା
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<data%>, %<update%>, %<enter%> "
				 "or %<exit%>");
		  if_modifier = ERROR_MARK;
		}
	      ଯଦି (if_modifier == OMP_TARGET_ENTER_DATA
		  || if_modifier == OMP_TARGET_EXIT_DATA)
		{
		  ଯଦି (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_POINTER
				(c_parser_peek_2nd_token (parser)->ମୂଲ୍ୟ);
		      ଯଦି (strcmp ("data", p) == 0)
			n = 4;
		    }
		  ଯଦି (n == 4)
		    c_parser_consume_token (parser);
		  ଅନ୍ୟଥା
		    {
		      location_t loc
			= c_parser_peek_2nd_token (parser)->location;
		      error_at (loc, "expected %<data%>");
		      if_modifier = ERROR_MARK;
		    }
		}
	    }
	}
      ଯଦି (if_modifier != ERROR_MARK)
	{
	  ଯଦି (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  ଅନ୍ୟଥା
	    {
	      ଯଦି (n > 2)
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<:%>");
		}
	      if_modifier = ERROR_MARK;
	    }
	}
    }

  location_t loc = c_parser_peek_token (parser)->location;
  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (loc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ସତ୍ୟ);
  ବୃକ୍ଷ t = c_objc_common_truthvalue_conversion (loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ), c;
  t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);
  parens.skip_until_found_close (parser);

  ପାଇଁ (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IF)
      {
	ଯଦି (if_modifier != ERROR_MARK
	    && OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    ଅଚଳ ଅକ୍ଷର *p = ଖାଲି;
	    ବାଛ (if_modifier)
	      {
	      ସ୍ଥିତି VOID_CST: p = "cancel"; ଭାଙ୍ଗ;
	      ସ୍ଥିତି OMP_PARALLEL: p = "parallel"; ଭାଙ୍ଗ;
	      ସ୍ଥିତି OMP_SIMD: p = "simd"; ଭାଙ୍ଗ;
	      ସ୍ଥିତି OMP_TASK: p = "task"; ଭାଙ୍ଗ;
	      ସ୍ଥିତି OMP_TASKLOOP: p = "taskloop"; ଭାଙ୍ଗ;
	      ସ୍ଥିତି OMP_TARGET_DATA: p = "target data"; ଭାଙ୍ଗ;
	      ସ୍ଥିତି OMP_TARGET: p = "target"; ଭାଙ୍ଗ;
	      ସ୍ଥିତି OMP_TARGET_UPDATE: p = "target update"; ଭାଙ୍ଗ;
	      ସ୍ଥିତି OMP_TARGET_ENTER_DATA: p = "target enter data"; ଭାଙ୍ଗ;
	      ସ୍ଥିତି OMP_TARGET_EXIT_DATA: p = "target exit data"; ଭାଙ୍ଗ;
	      ପୂର୍ବନିର୍ଦ୍ଧାରିତ: gcc_unreachable ();
	      }
	    error_at (location, "too many %<if%> clauses with %qs modifier",
		      p);
	    ଫେରନ୍ତୁ list;
	  }
	ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    ଯଦି (!is_omp)
	      error_at (location, "too many %<if%> clauses");
	    ଅନ୍ୟଥା
	      error_at (location, "too many %<if%> clauses without modifier");
	    ଫେରନ୍ତୁ list;
	  }
	ଅନ୍ୟଥା ଯଦି (if_modifier == ERROR_MARK
		 || OMP_CLAUSE_IF_MODIFIER (c) == ERROR_MARK)
	  {
	    error_at (location, "if any %<if%> clause has modifier, then all "
				"%<if%> clauses have to use modifier");
	    ଫେରନ୍ତୁ list;
	  }
      }

  c = build_omp_clause (location, OMP_CLAUSE_IF);
  OMP_CLAUSE_IF_MODIFIER (c) = if_modifier;
  OMP_CLAUSE_IF_ପଦସମଷ୍ଟି (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_lastprivate (c_parser *parser, ବୃକ୍ଷ list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  ଯଦି (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      ତାର୍କିକ conditional = ମିଥ୍ୟା;
      ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  ଅଚଳ ଅକ୍ଷର *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	  ଯଦି (strcmp (p, "conditional") == 0)
	    {
	      conditional = ସତ୍ୟ;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      ବୃକ୍ଷ nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ଯଦି (conditional)
	ପାଇଁ (ବୃକ୍ଷ c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      ଫେରନ୍ତୁ nlist;
    }
  ଫେରନ୍ତୁ list;
}

/* OpenMP 3.1:
   mergeable */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_UNUSED, ବୃକ୍ଷ list)
{
  ବୃକ୍ଷ c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  ଫେରନ୍ତୁ c;
}

/* OpenMP 2.5:
   nowait */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_UNUSED, ବୃକ୍ଷ list)
{
  ବୃକ୍ଷ c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_ଅଙ୍କ_threads (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t ଅଙ୍କ_threads_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
      ବୃକ୍ଷ c, t = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);

      parens.skip_until_found_close (parser);

      ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ଫେରନ୍ତୁ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (ପଦସମଷ୍ଟି_loc, LE_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି, t,
		       build_int_cst (ବୃକ୍ଷ_TYPE (t), 0));
      protected_set_ପଦସମଷ୍ଟି_location (c, ପଦସମଷ୍ଟି_loc);
      ଯଦି (c == boolean_true_ଗଣ୍ଠି)
	{
	  warning_at (ପଦସମଷ୍ଟି_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_ଗଣ୍ଠି;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_ଅଙ୍କ_THREADS, "num_threads");

      c = build_omp_clause (ଅଙ୍କ_threads_loc, OMP_CLAUSE_ଅଙ୍କ_THREADS);
      OMP_CLAUSE_ଅଙ୍କ_THREADS_ପଦସମଷ୍ଟି (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ଫେରନ୍ତୁ list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_ଅଙ୍କ_tasks (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t ଅଙ୍କ_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      ତାର୍କିକ strict = ମିଥ୍ୟା;
      ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ),
		     "strict") == 0)
	{
	  strict = ସତ୍ୟ;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
      ବୃକ୍ଷ c, t = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);

      parens.skip_until_found_close (parser);

      ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ଫେରନ୍ତୁ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (ପଦସମଷ୍ଟି_loc, LE_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି, t,
			   build_int_cst (ବୃକ୍ଷ_TYPE (t), 0));
      ଯଦି (CAN_HAVE_LOCATION_P (c))
	SET_ପଦସମଷ୍ଟି_LOCATION (c, ପଦସମଷ୍ଟି_loc);
      ଯଦି (c == boolean_true_ଗଣ୍ଠି)
	{
	  warning_at (ପଦସମଷ୍ଟି_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_ଗଣ୍ଠି;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_ଅଙ୍କ_TASKS, "num_tasks");

      c = build_omp_clause (ଅଙ୍କ_tasks_loc, OMP_CLAUSE_ଅଙ୍କ_TASKS);
      OMP_CLAUSE_ଅଙ୍କ_TASKS_ପଦସମଷ୍ଟି (c) = t;
      OMP_CLAUSE_ଅଙ୍କ_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ଫେରନ୍ତୁ list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_grainsize (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      ତାର୍କିକ strict = ମିଥ୍ୟା;
      ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ),
		     "strict") == 0)
	{
	  strict = ସତ୍ୟ;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
      ବୃକ୍ଷ c, t = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);

      parens.skip_until_found_close (parser);

      ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ଫେରନ୍ତୁ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (ପଦସମଷ୍ଟି_loc, LE_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି, t,
			   build_int_cst (ବୃକ୍ଷ_TYPE (t), 0));
      ଯଦି (CAN_HAVE_LOCATION_P (c))
	SET_ପଦସମଷ୍ଟି_LOCATION (c, ପଦସମଷ୍ଟି_loc);
      ଯଦି (c == boolean_true_ଗଣ୍ଠି)
	{
	  warning_at (ପଦସମଷ୍ଟି_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_ଗଣ୍ଠି;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_ପଦସମଷ୍ଟି (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ଫେରନ୍ତୁ list;
}

/* OpenMP 4.5:
   priority ( expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_priority (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t priority_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
      ବୃକ୍ଷ c, t = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);

      parens.skip_until_found_close (parser);

      ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ଫେରନ୍ତୁ list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (ପଦସମଷ୍ଟି_loc, LT_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି, t,
			   build_int_cst (ବୃକ୍ଷ_TYPE (t), 0));
      ଯଦି (CAN_HAVE_LOCATION_P (c))
	SET_ପଦସମଷ୍ଟି_LOCATION (c, ପଦସମଷ୍ଟି_loc);
      ଯଦି (c == boolean_true_ଗଣ୍ଠି)
	{
	  warning_at (ପଦସମଷ୍ଟି_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_ଗଣ୍ଠି;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_PRIORITY, "priority");

      c = build_omp_clause (priority_loc, OMP_CLAUSE_PRIORITY);
      OMP_CLAUSE_PRIORITY_ପଦସମଷ୍ଟି (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ଫେରନ୍ତୁ list;
}

/* OpenMP 4.5:
   hint ( expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_hint (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
      ବୃକ୍ଷ c, t = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);
      ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t))
	  || ବୃକ୍ଷ_CODE (t) != INTEGER_CST
	  || ବୃକ୍ଷ_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  ଫେରନ୍ତୁ list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_ପଦସମଷ୍ଟି (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ଫେରନ୍ତୁ list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_filter (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
      ବୃକ୍ଷ c, t = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);
      ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ଫେରନ୍ତୁ list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_ପଦସମଷ୍ଟି (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ଫେରନ୍ତୁ list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_defaultmap (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ c;
  ଅଚଳ ଅକ୍ଷର *p;
  ଗଣନା omp_clause_defaultmap_kind behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  ଗଣନା omp_clause_defaultmap_kind category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;
  ଯଦି (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  ଅନ୍ୟଥା ଯଦି (!c_parser_next_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      ଯାଅ out_err;
    }
  ଅନ୍ୟଥା
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);

  ବାଛ (p[0])
    {
    ସ୍ଥିତି 'a':
      ଯଦି (strcmp ("alloc", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ALLOC;
      ଅନ୍ୟଥା
	ଯାଅ invalid_behavior;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି 'd':
      ଯଦି (strcmp ("default", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
      ଅନ୍ୟଥା
	ଯାଅ invalid_behavior;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି 'f':
      ଯଦି (strcmp ("firstprivate", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FIRSTPRIVATE;
      ଅନ୍ୟଥା ଯଦି (strcmp ("from", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FROM;
      ଅନ୍ୟଥା
	ଯାଅ invalid_behavior;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି 'n':
      ଯଦି (strcmp ("none", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_NONE;
      ଅନ୍ୟଥା
	ଯାଅ invalid_behavior;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି 'p':
      ଯଦି (strcmp ("present", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_PRESENT;
      ଅନ୍ୟଥା
	ଯାଅ invalid_behavior;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି 't':
      ଯଦି (strcmp ("tofrom", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TOFROM;
      ଅନ୍ୟଥା ଯଦି (strcmp ("to", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TO;
      ଅନ୍ୟଥା
	ଯାଅ invalid_behavior;
      ଭାଙ୍ଗ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଯାଅ invalid_behavior;
    }
  c_parser_consume_token (parser);

  ଯଦି (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ଯାଅ out_err;
      ଯଦି (!c_parser_next_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  ଯାଅ out_err;
	}
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ବାଛ (p[0])
	{
	ସ୍ଥିତି 'a':
	  ଯଦି (strcmp ("aggregate", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE;
	  ଅନ୍ୟଥା ଯଦି (strcmp ("all", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL;
	  ଅନ୍ୟଥା
	    ଯାଅ invalid_category;
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି 'p':
	  ଯଦି (strcmp ("pointer", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER;
	  ଅନ୍ୟଥା
	    ଯାଅ invalid_category;
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି 's':
	  ଯଦି (strcmp ("scalar", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR;
	  ଅନ୍ୟଥା
	    ଯାଅ invalid_category;
	  ଭାଙ୍ଗ;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଯାଅ invalid_category;
	}

      c_parser_consume_token (parser);
    }
  parens.skip_until_found_close (parser);

  ପାଇଁ (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEFAULTMAP
	&& (category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
	    || OMP_CLAUSE_DEFAULTMAP_CATEGORY (c) == category
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL)))
      {
	ଗଣନା omp_clause_defaultmap_kind cat = category;
	location_t loc = OMP_CLAUSE_LOCATION (c);
	ଯଦି (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
		&& (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		    != OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)))
	  cat = OMP_CLAUSE_DEFAULTMAP_CATEGORY (c);
	p = ଖାଲି;
	ବାଛ (cat)
	  {
	  ସ୍ଥିତି OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED:
	    p = ଖାଲି;
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL:
	    p = "all";
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE:
	    p = "aggregate";
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER:
	    p = "pointer";
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR:
	    p = "scalar";
	    ଭାଙ୍ଗ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    gcc_unreachable ();
	  }
	ଯଦି (p)
	  error_at (loc, "too many %<defaultmap%> clauses with %qs category",
		    p);
	ଅନ୍ୟଥା
	  error_at (loc, "too many %<defaultmap%> clauses with unspecified "
			 "category");
	ଭାଙ୍ଗ;
      }

  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULTMAP);
  OMP_CLAUSE_DEFAULTMAP_SET_KIND (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;

 out_err:
  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_use_device_ptr (c_parser *parser, ବୃକ୍ଷ list)
{
  ଫେରନ୍ତୁ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_use_device_addr (c_parser *parser, ବୃକ୍ଷ list)
{
  ଫେରନ୍ତୁ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_has_device_addr (c_parser *parser, ବୃକ୍ଷ list)
{
  ଫେରନ୍ତୁ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_is_device_ptr (c_parser *parser, ବୃକ୍ଷ list)
{
  ଫେରନ୍ତୁ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_code code,
				 ବୃକ୍ଷ list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_expression (parser);
  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
  ବୃକ୍ଷ c, t = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
  t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);

  parens.skip_until_found_close (parser);

  ଯଦି (t == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ list;
  ଅନ୍ୟଥା ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t)))
    {
      error_at (ପଦସମଷ୍ଟି_loc, "%qs expression must be integral",
		omp_clause_code_name[code]);
      ଫେରନ୍ତୁ list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (ପଦସମଷ୍ଟି_loc, LE_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି, t,
		       build_int_cst (ବୃକ୍ଷ_TYPE (t), 0));
  protected_set_ପଦସମଷ୍ଟି_location (c, ପଦସମଷ୍ଟି_loc);
  ଯଦି (c == boolean_true_ଗଣ୍ଠି)
    {
      warning_at (ପଦସମଷ୍ଟି_loc, 0,
		  "%qs value must be positive",
		  omp_clause_code_name[code]);
      t = integer_one_ଗଣ୍ଠି;
    }

  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  c = build_omp_clause (loc, code);
  OMP_CLAUSE_OPERAND (c, 0) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_code kind,
			    ଅଚଳ ଅକ୍ଷର *str, ବୃକ୍ଷ list)
{
  ଅଚଳ ଅକ୍ଷର *id = "num";
  ବୃକ୍ଷ ops[2] = { NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ }, c;

  ଯଦି (kind == OMP_CLAUSE_VECTOR)
    id = "length";

  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      କର
	{
	  c_token *next = c_parser_peek_token (parser);
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା idx = 0;

	  /* Gang static argument.  */
	  ଯଦି (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		ଯାଅ cleanup_error;

	      idx = 1;
	      ଯଦି (ops[idx] != NULL_ବୃକ୍ଷ)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  ଯାଅ cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      ଯଦି (c_parser_next_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_ଗଣ୍ଠି;

		  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      ଜାରି;
		    }
		  ଅନ୍ୟଥା
		    ଭାଙ୍ଗ;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
		   && strcmp (id, IDENTIFIER_POINTER (next->ମୂଲ୍ୟ)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  ଯଦି (ops[idx] != NULL_ବୃକ୍ଷ)
	    {
	      c_parser_error (parser, "unexpected argument");
	      ଯାଅ cleanup_error;
	    }

	  location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
	  c_ପଦସମଷ୍ଟି cexpr = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	  cexpr = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, cexpr, ମିଥ୍ୟା, ସତ୍ୟ);
	  ବୃକ୍ଷ ପଦସମଷ୍ଟି = cexpr.ମୂଲ୍ୟ;
	  ଯଦି (ପଦସମଷ୍ଟି == error_mark_ଗଣ୍ଠି)
	    ଯାଅ cleanup_error;

	  ପଦସମଷ୍ଟି = c_fully_fold (ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ଖାଲି);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      ଫେରନ୍ତୁ list;
	    }

	  ବୃକ୍ଷ c = fold_build2_loc (ପଦସମଷ୍ଟି_loc, LE_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି, ପଦସମଷ୍ଟି,
				    build_int_cst (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), 0));
	  ଯଦି (c == boolean_true_ଗଣ୍ଠି)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      ପଦସମଷ୍ଟି = integer_one_ଗଣ୍ଠି;
	    }

	  ops[idx] = ପଦସମଷ୍ଟି;

	  ଯଦି (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ଜାରି;
	    }
	  ଭାଙ୍ଗ;
	}
      ଯେତେବେଳେ (1);

      ଯଦି (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	ଯାଅ cleanup_error;
    }

  check_no_duplicate_clause (list, kind, str);

  c = build_omp_clause (loc, kind);

  ଯଦି (ops[1])
    OMP_CLAUSE_OPERAND (c, 1) = ops[1];

  OMP_CLAUSE_OPERAND (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  ଫେରନ୍ତୁ c;

 cleanup_error:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  ଫେରନ୍ତୁ list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_simple_clause (location_t loc, ଗଣନା omp_clause_code code,
			     ବୃକ୍ଷ list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  ବୃକ୍ଷ c = build_omp_clause (loc, code);
  OMP_CLAUSE_CHAIN (c) = list;

  ଫେରନ୍ତୁ c;
}

/* OpenACC:
   async [( int-expr )] */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_clause_async (c_parser *parser, ବୃକ୍ଷ list)
{
  ବୃକ୍ଷ c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_ଗଣ୍ଠି, GOMP_ASYNC_NOVAL);

  ଯଦି (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି).ମୂଲ୍ୟ;
      ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      ଅନ୍ୟଥା ଯଦି (t == error_mark_ଗଣ୍ଠି
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	ଫେରନ୍ତୁ list;
    }
  ଅନ୍ୟଥା
    t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_ପଦସମଷ୍ଟି (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  ଫେରନ୍ତୁ list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_clause_tile (c_parser *parser, ବୃକ୍ଷ list)
{
  ବୃକ୍ଷ c, ପଦସମଷ୍ଟି = error_mark_ଗଣ୍ଠି;
  location_t loc;
  ବୃକ୍ଷ tile = NULL_ବୃକ୍ଷ;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ଫେରନ୍ତୁ list;

  କର
    {
      ଯଦି (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	ଫେରନ୍ତୁ list;

      ଯଦି (c_parser_next_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  ପଦସମଷ୍ଟି = integer_zero_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା
	{
	  location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
	  c_ପଦସମଷ୍ଟି cexpr = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	  cexpr = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, cexpr, ମିଥ୍ୟା, ସତ୍ୟ);
	  ପଦସମଷ୍ଟି = cexpr.ମୂଲ୍ୟ;

	  ଯଦି (ପଦସମଷ୍ଟି == error_mark_ଗଣ୍ଠି)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      ଫେରନ୍ତୁ list;
	    }

	  ପଦସମଷ୍ଟି = c_fully_fold (ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ଖାଲି);

	  ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି))
	      || !ବୃକ୍ଷ_fits_shwi_p (ପଦସମଷ୍ଟି)
	      || ବୃକ୍ଷ_to_shwi (ପଦସମଷ୍ଟି) <= 0)
	    {
	      error_at (ପଦସମଷ୍ଟି_loc, "%<tile%> argument needs positive"
			" integral constant");
	      ପଦସମଷ୍ଟି = integer_zero_ଗଣ୍ଠି;
	    }
	}

      tile = ବୃକ୍ଷ_cons (NULL_ବୃକ୍ଷ, ପଦସମଷ୍ଟି, tile);
    }
  ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN));

  /* Consume the trailing ')'.  */
  c_parser_consume_token (parser);

  c = build_omp_clause (loc, OMP_CLAUSE_TILE);
  tile = nreverse (tile);
  OMP_CLAUSE_TILE_LIST (c) = tile;
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
}

/* OpenACC:
   wait [( int-expr-list )] */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_clause_wait (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  ଯଦି (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  ଅନ୍ୟଥା
    {
      ବୃକ୍ଷ c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_ଗଣ୍ଠି, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ଫେରନ୍ତୁ list;
}

/* OpenACC 2.7:
   self [( expression )] */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_compute_clause_self (c_parser *parser, ବୃକ୍ଷ list)
{
  ବୃକ୍ଷ t;
  location_t location = c_parser_peek_token (parser)->location;
  ଯଦି (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (loc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ସତ୍ୟ);
      t = c_objc_common_truthvalue_conversion (loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
      t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);
      parens.skip_until_found_close (parser);
    }
  ଅନ୍ୟଥା
    t = truthvalue_true_ଗଣ୍ଠି;

  ପାଇଁ (ବୃକ୍ଷ c = list; c; c = OMP_CLAUSE_CHAIN (c))
    ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	ଫେରନ୍ତୁ list;
      }

  ବୃକ୍ଷ c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_ପଦସମଷ୍ଟି (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
}

/* OpenMP 5.0:
   order ( concurrent )

   OpenMP 5.1:
   order ( order-modifier : concurrent )

   order-modifier:
     reproducible
     unconstrained  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_order (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ c;
  ଅଚଳ ଅକ୍ଷର *p;
  ତାର୍କିକ unconstrained = ମିଥ୍ୟା;
  ତାର୍କିକ reproducible = ମିଥ୍ୟା;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "unconstrained") == 0)
	unconstrained = ସତ୍ୟ;
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "reproducible") == 0)
	reproducible = ସତ୍ୟ;
      ଅନ୍ୟଥା
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  ଯାଅ out_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  ଯଦି (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      ଯାଅ out_err;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
  ଯଦି (strcmp (p, "concurrent") != 0)
    {
      c_parser_error (parser, "expected %<concurrent%>");
      ଯାଅ out_err;
    }
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDER, "order");
  c = build_omp_clause (loc, OMP_CLAUSE_ORDER);
  OMP_CLAUSE_ORDER_UNCONSTRAINED (c) = unconstrained;
  OMP_CLAUSE_ORDER_REPRODUCIBLE (c) = reproducible;
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;

 out_err:
  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_bind (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ c;
  ଅଚଳ ଅକ୍ଷର *p;
  ଗଣନା omp_clause_bind_kind kind = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;
  ଯଦି (!c_parser_next_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_found_close (parser);
      ଫେରନ୍ତୁ list;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
  ଯଦି (strcmp (p, "teams") == 0)
    kind = OMP_CLAUSE_BIND_TEAMS;
  ଅନ୍ୟଥା ଯଦି (strcmp (p, "parallel") == 0)
    kind = OMP_CLAUSE_BIND_PARALLEL;
  ଅନ୍ୟଥା ଯଦି (strcmp (p, "thread") != 0)
    ଯାଅ invalid;
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_ordered (c_parser *parser, ବୃକ୍ଷ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  ବୃକ୍ଷ c, ଅଙ୍କ = NULL_ବୃକ୍ଷ;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      ଅଙ୍କ = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି).ମୂଲ୍ୟ;
      parens.skip_until_found_close (parser);
    }
  ଯଦି (ଅଙ୍କ == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ list;
  ଯଦି (ଅଙ୍କ)
    {
      mark_exp_read (ଅଙ୍କ);
      ଅଙ୍କ = c_fully_fold (ଅଙ୍କ, ମିଥ୍ୟା, ଖାଲି);
      ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ଅଙ୍କ))
	  || !ବୃକ୍ଷ_fits_shwi_p (ଅଙ୍କ)
	  || (n = ବୃକ୍ଷ_to_shwi (ଅଙ୍କ)) <= 0
	  || (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  ଫେରନ୍ତୁ list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_ପଦସମଷ୍ଟି (c) = ଅଙ୍କ;
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_private (c_parser *parser, ବୃକ୍ଷ list)
{
  ଫେରନ୍ତୁ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_PRIVATE, list);
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_reduction (c_parser *parser, ଗଣନା omp_clause_code kind,
			       ତାର୍କିକ is_omp, ବୃକ୍ଷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      ତାର୍କିକ task = ମିଥ୍ୟା;
      ତାର୍କିକ inscan = ମିଥ୍ୟା;
      ଗଣନା ବୃକ୍ଷ_code code = ERROR_MARK;
      ବୃକ୍ଷ reduc_id = NULL_ବୃକ୍ଷ;

      ଯଦି (kind == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  ଯଦି (c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      ଅଚଳ ଅକ୍ଷର *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	      ଯଦି (strcmp (p, "task") == 0)
		task = ସତ୍ୟ;
	      ଅନ୍ୟଥା ଯଦି (strcmp (p, "inscan") == 0)
		inscan = ସତ୍ୟ;
	      ଯଦି (task || inscan)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		}
	    }
	}

      ବାଛ (c_parser_peek_token (parser)->type)
	{
	ସ୍ଥିତି CPP_PLUS:
	  code = PLUS_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_MULT:
	  code = MULT_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_MINUS:
	  ଯଦି (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.add_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  code = MINUS_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_AND:
	  code = BIT_AND_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_XOR:
	  code = BIT_XOR_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_OR:
	  code = BIT_IOR_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_AND_AND:
	  code = TRUTH_ANDIF_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_OR_OR:
	  code = TRUTH_ORIF_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
        ସ୍ଥିତି CPP_NAME:
	  {
	    ଅଚଳ ଅକ୍ଷର *p
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	    ଯଦି (strcmp (p, "min") == 0)
	      {
		code = MIN_ପଦସମଷ୍ଟି;
		ଭାଙ୍ଗ;
	      }
	    ଯଦି (strcmp (p, "max") == 0)
	      {
		code = MAX_ପଦସମଷ୍ଟି;
		ଭାଙ୍ଗ;
	      }
	    reduc_id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	    ଭାଙ୍ଗ;
	  }
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
	  ଫେରନ୍ତୁ list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (code, reduc_id);
      ଯଦି (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  ବୃକ୍ଷ nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, kind, list);
	  ପାଇଁ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      ବୃକ୍ଷ d = OMP_CLAUSE_DECL (c), type;
	      ଯଦି (ବୃକ୍ଷ_CODE (d) != OMP_ARRAY_SECTION)
		type = ବୃକ୍ଷ_TYPE (d);
	      ଅନ୍ୟଥା
		{
		  ପୂର୍ଣ୍ଣସଂଖ୍ୟା cnt = 0;
		  ବୃକ୍ଷ t;
		  ପାଇଁ (t = d;
		      ବୃକ୍ଷ_CODE (t) == OMP_ARRAY_SECTION;
		      t = ବୃକ୍ଷ_OPERAND (t, 0))
		    cnt++;
		  type = ବୃକ୍ଷ_TYPE (t);
		  ଯେତେବେଳେ (cnt > 0)
		    {
		      ଯଦି (ବୃକ୍ଷ_CODE (type) != POINTER_TYPE
			  && ବୃକ୍ଷ_CODE (type) != ARRAY_TYPE)
			ଭାଙ୍ଗ;
		      type = ବୃକ୍ଷ_TYPE (type);
		      cnt--;
		    }
		}
	      ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE)
		type = ବୃକ୍ଷ_TYPE (type);
	      OMP_CLAUSE_REDUCTION_CODE (c) = code;
	      ଯଦି (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      ଅନ୍ୟଥା ଯଦି (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      ଯଦି (code == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || ବୃକ୍ଷ_CODE (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_found_close (parser);
    }
  ଫେରନ୍ତୁ list;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_schedule (c_parser *parser, ବୃକ୍ଷ list)
{
  ବୃକ୍ଷ c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  c = build_omp_clause (loc, OMP_CLAUSE_SCHEDULE);

  location_t comma = UNKNOWN_LOCATION;
  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ବୃକ୍ଷ kind = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (kind);
      ଯଦି (strcmp ("simd", p) == 0)
	OMP_CLAUSE_SCHEDULE_SIMD (c) = 1;
      ଅନ୍ୟଥା ଯଦି (strcmp ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_MONOTONIC;
      ଅନ୍ୟଥା ଯଦି (strcmp ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_NONMONOTONIC;
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      ଯଦି (nmodifiers++ == 0
	  && c_parser_next_token_is (parser, CPP_COMMA))
	{
	  comma = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା
	{
	  c_parser_require (parser, CPP_COLON, "expected %<:%>");
	  ଭାଙ୍ଗ;
	}
    }
  ଯଦି (comma != UNKNOWN_LOCATION)
    error_at (comma, "expected %<:%>");

  ଯଦି ((modifiers & (OMP_CLAUSE_SCHEDULE_MONOTONIC
		    | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
      == (OMP_CLAUSE_SCHEDULE_MONOTONIC
	  | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ବୃକ୍ଷ kind = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (kind);

      ବାଛ (p[0])
	{
	ସ୍ଥିତି 'd':
	  ଯଦି (strcmp ("dynamic", p) != 0)
	    ଯାଅ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_DYNAMIC;
	  ଭାଙ୍ଗ;

        ସ୍ଥିତି 'g':
	  ଯଦି (strcmp ("guided", p) != 0)
	    ଯାଅ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_GUIDED;
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି 'r':
	  ଯଦି (strcmp ("runtime", p) != 0)
	    ଯାଅ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_RUNTIME;
	  ଭାଙ୍ଗ;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଯାଅ invalid_kind;
	}
    }
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_STATIC;
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_AUTO;
  ଅନ୍ୟଥା
    ଯାଅ invalid_kind;

  c_parser_consume_token (parser);
  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
    {
      location_t here;
      c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (here, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
      t = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);

      ଯଦି (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_RUNTIME)
	error_at (here, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_AUTO)
	error_at (here,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (t)) == INTEGER_TYPE
	       || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  ବୃକ୍ଷ s = fold_build2_loc (loc, LE_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି, t,
				    build_int_cst (ବୃକ୍ଷ_TYPE (t), 0));
	  protected_set_ପଦସମଷ୍ଟି_location (s, loc);
	  ଯଦି (s == boolean_true_ଗଣ୍ଠି)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_ଗଣ୍ଠି;
	    }
	  OMP_CLAUSE_SCHEDULE_CHUNK_ପଦସମଷ୍ଟି (c) = t;
	}
      ଅନ୍ୟଥା
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_found_close (parser);
    }
  ଅନ୍ୟଥା
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_SCHEDULE_KIND (c)
    = (ଗଣନା omp_clause_schedule_kind)
      (OMP_CLAUSE_SCHEDULE_KIND (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_SCHEDULE, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;

 invalid_kind:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  ଫେରନ୍ତୁ list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_shared (c_parser *parser, ବୃକ୍ଷ list)
{
  ଫେରନ୍ତୁ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_UNUSED, ବୃକ୍ଷ list)
{
  ବୃକ୍ଷ c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_UNTIED, "untied");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_UNTIED);
  OMP_CLAUSE_CHAIN (c) = list;

  ଫେରନ୍ତୁ c;
}

/* OpenMP 4.0:
   inbranch
   notinbranch */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_UNUSED,
			    ଗଣନା omp_clause_code code, ବୃକ୍ଷ list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  ବୃକ୍ଷ c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  ଫେରନ୍ତୁ c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_UNUSED,
				ଗଣନା omp_clause_code code, ବୃକ୍ଷ list)
{
  ବୃକ୍ଷ c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  ଫେରନ୍ତୁ c;
}

/* OpenMP 4.5:
   nogroup */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_UNUSED, ବୃକ୍ଷ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  ବୃକ୍ଷ c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
}

/* OpenMP 4.5:
   simd
   threads */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_UNUSED,
				 ଗଣନା omp_clause_code code, ବୃକ୍ଷ list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);
  ବୃକ୍ଷ c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_ଅଙ୍କ_teams (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t ଅଙ୍କ_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      location_t upper_loc = c_parser_peek_token (parser)->location;
      location_t lower_loc = UNKNOWN_LOCATION;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (upper_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
      ବୃକ୍ଷ c, upper = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, lower = NULL_ବୃକ୍ଷ;
      upper = c_fully_fold (upper, ମିଥ୍ୟା, ଖାଲି);

      ଯଦି (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  lower_loc = upper_loc;
	  lower = upper;
	  upper_loc = c_parser_peek_token (parser)->location;
	  ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (upper_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
	  upper = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
	  upper = c_fully_fold (upper, ମିଥ୍ୟା, ଖାଲି);
	}

      parens.skip_until_found_close (parser);

      ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (upper))
	  || (lower && !INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (lower))))
	{
	  c_parser_error (parser, "expected integer expression");
	  ଫେରନ୍ତୁ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (upper_loc, LE_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି, upper,
			   build_int_cst (ବୃକ୍ଷ_TYPE (upper), 0));
      protected_set_ପଦସମଷ୍ଟି_location (c, upper_loc);
      ଯଦି (c == boolean_true_ଗଣ୍ଠି)
	{
	  warning_at (upper_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  upper = integer_one_ଗଣ୍ଠି;
	}
      ଯଦି (lower)
	{
	  c = fold_build2_loc (lower_loc, LE_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି, lower,
			       build_int_cst (ବୃକ୍ଷ_TYPE (lower), 0));
	  protected_set_ପଦସମଷ୍ଟି_location (c, lower_loc);
	  ଯଦି (c == boolean_true_ଗଣ୍ଠି)
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      lower = NULL_ବୃକ୍ଷ;
	    }
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (lower) == INTEGER_CST
		   && ବୃକ୍ଷ_CODE (upper) == INTEGER_CST
		   && ବୃକ୍ଷ_int_cst_lt (upper, lower))
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", lower, upper);
	      lower = NULL_ବୃକ୍ଷ;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_ଅଙ୍କ_TEAMS, "num_teams");

      c = build_omp_clause (ଅଙ୍କ_teams_loc, OMP_CLAUSE_ଅଙ୍କ_TEAMS);
      OMP_CLAUSE_ଅଙ୍କ_TEAMS_UPPER_ପଦସମଷ୍ଟି (c) = upper;
      OMP_CLAUSE_ଅଙ୍କ_TEAMS_LOWER_ପଦସମଷ୍ଟି (c) = lower;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ଫେରନ୍ତୁ list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_thread_limit (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t ଅଙ୍କ_thread_limit_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
      ବୃକ୍ଷ c, t = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);

      parens.skip_until_found_close (parser);

      ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ଫେରନ୍ତୁ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (ପଦସମଷ୍ଟି_loc, LE_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି, t,
			   build_int_cst (ବୃକ୍ଷ_TYPE (t), 0));
      protected_set_ପଦସମଷ୍ଟି_location (c, ପଦସମଷ୍ଟି_loc);
      ଯଦି (c == boolean_true_ଗଣ୍ଠି)
	{
	  warning_at (ପଦସମଷ୍ଟି_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_ଗଣ୍ଠି;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_LIMIT,
				 "thread_limit");

      c = build_omp_clause (ଅଙ୍କ_thread_limit_loc, OMP_CLAUSE_THREAD_LIMIT);
      OMP_CLAUSE_THREAD_LIMIT_ପଦସମଷ୍ଟି (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ଫେରନ୍ତୁ list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_aligned (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ nl, c;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  ଯଦି (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
      ବୃକ୍ଷ alignment = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      alignment = c_fully_fold (alignment, ମିଥ୍ୟା, ଖାଲି);
      ଯଦି (ବୃକ୍ଷ_CODE (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (alignment))
	  || ବୃକ୍ଷ_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_ବୃକ୍ଷ;
	}

      ପାଇଁ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ nl;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_allocate (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ nl, c;
  ବୃକ୍ଷ allocator = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ align = NULL_ବୃକ୍ଷ;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  ଯଦି ((c_parser_next_token_is_not (parser, CPP_NAME)
       && c_parser_next_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      ତାର୍କିକ has_modifiers = ମିଥ୍ୟା;
      ବୃକ୍ଷ orig_type = NULL_ବୃକ୍ଷ;
      ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା n = 3;
	  ଅଚଳ ଅକ୍ଷର *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	  ଯଦି ((strcmp (p, "allocator") == 0 || strcmp (p, "align") == 0)
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      ଯଦି (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = ସତ୍ୟ;
	      ଅନ୍ୟଥା ଯଦି (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  ଅଚଳ ଅକ୍ଷର *q = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ);
		  n += 4;
		  ଯଦି ((strcmp (q, "allocator") == 0
		       || strcmp (q, "align") == 0)
		      && c_parser_check_balanced_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = ସତ୍ୟ;
		}
	    }
	  ଯଦି (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
	      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
	      ଯଦି (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
		;
	      ଅନ୍ୟଥା ଯଦି (strcmp (p, "allocator") == 0)
		{
		  allocator = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
		  allocator = c_fully_fold (allocator, ମିଥ୍ୟା, ଖାଲି);
		  orig_type = ପଦସମଷ୍ଟି.original_type
			      ? ପଦସମଷ୍ଟି.original_type : ବୃକ୍ଷ_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      ଅନ୍ୟଥା
		{
		  align = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
		  align = c_fully_fold (align, ମିଥ୍ୟା, ଖାଲି);
		}
	      parens2.skip_until_found_close (parser);
	      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  ଅଚଳ ଅକ୍ଷର *q = "";
		  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ);
		  ଯଦି (strcmp (q, "allocator") != 0 && strcmp (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_found_close (parser);
		      ଫେରନ୍ତୁ list;
		    }
		  ଅନ୍ୟଥା ଯଦି (strcmp (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_found_close (parser);
		      ଫେରନ୍ତୁ list;
		    }
		  c_parser_consume_token (parser);
		  ଯଦି (!parens2.require_open (parser))
		    {
		      parens.skip_until_found_close (parser);
		      ଫେରନ୍ତୁ list;
		    }
		  ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
		  ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
		  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା,
						   ସତ୍ୟ);
		  ଯଦି (strcmp (q, "allocator") == 0)
		    {
		      allocator = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
		      allocator = c_fully_fold (allocator, ମିଥ୍ୟା, ଖାଲି);
		      orig_type = ପଦସମଷ୍ଟି.original_type
				  ? ପଦସମଷ୍ଟି.original_type : ବୃକ୍ଷ_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  ଅନ୍ୟଥା
		    {
		      align = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
		      align = c_fully_fold (align, ମିଥ୍ୟା, ଖାଲି);
		    }
		  parens2.skip_until_found_close (parser);
		}
	    }
	}
      ଯଦି (!has_modifiers)
	{
	  location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
	  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
	  ଯଦି (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
	    {
	      allocator = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
	      allocator = c_fully_fold (allocator, ମିଥ୍ୟା, ଖାଲି);
	      orig_type = ପଦସମଷ୍ଟି.original_type
			  ? ପଦସମଷ୍ଟି.original_type : ବୃକ୍ଷ_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      ଯଦି (allocator
	  && (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (allocator))
	      || ବୃକ୍ଷ_CODE (orig_type) != ENUMERAL_TYPE
	      || (TYPE_NAME (orig_type)
		  != get_identifier ("omp_allocator_handle_t"))))
        {
          error_at (clause_loc, "%<allocate%> clause allocator expression "
				"has type %qT rather than "
				"%<omp_allocator_handle_t%>",
				ବୃକ୍ଷ_TYPE (allocator));
          allocator = NULL_ବୃକ୍ଷ;
        }
      ଯଦି (align
	  && (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (align))
	      || !ବୃକ୍ଷ_fits_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_ବୃକ୍ଷ;
	}
      ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_found_close (parser);
	  ଫେରନ୍ତୁ list;
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALLOCATE, list);

  ଯଦି (allocator || align)
    ପାଇଁ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      {
	OMP_CLAUSE_ALLOCATE_ALLOCATOR (c) = allocator;
	OMP_CLAUSE_ALLOCATE_ALIGN (c) = align;
      }

  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ nl;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_uses_allocators (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ nl = list;
  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

parse_next:

  ତାର୍କିକ has_modifiers = ମିଥ୍ୟା;
  ତାର୍କିକ seen_allocators = ମିଥ୍ୟା;
  ବୃକ୍ଷ memspace_ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ traits_var = NULL_ବୃକ୍ଷ;

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା n = 3;
      ଅଚଳ ଅକ୍ଷର *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି ((strcmp (p, "traits") == 0 || strcmp (p, "memspace") == 0)
	  && c_parser_check_balanced_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  ଯଦି (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = ସତ୍ୟ;
	  ଅନ୍ୟଥା ଯଦି (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      ଅଚଳ ଅକ୍ଷର *q = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ);
	      n += 4;
	      ଯଦି ((strcmp (q, "traits") == 0
		   || strcmp (q, "memspace") == 0)
		  && c_parser_check_balanced_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  ଯଦି (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = ସତ୍ୟ;
		  ଯଦି ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      ଅଚଳ ଅକ୍ଷର *m = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ);
		      ଯଦି (strcmp (p, m) == 0 || strcmp (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  ଯାଅ end;
			}
		    }
		}
	    }
	}
      ଯଦି (has_modifiers)
	{
	  c_parser_consume_token (parser);
	  matching_parens parens2;
	  parens2.require_open (parser);
	  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	  ଯଦି (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
	    ;
	  ଅନ୍ୟଥା ଯଦି (strcmp (p, "traits") == 0)
	    {
	      traits_var = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
	      traits_var = c_fully_fold (traits_var, ମିଥ୍ୟା, ଖାଲି);
	      mark_exp_read (traits_var);
	    }
	  ଅନ୍ୟଥା
	    {
	      memspace_ପଦସମଷ୍ଟି = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
	      memspace_ପଦସମଷ୍ଟି = c_fully_fold (memspace_ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ଖାଲି);
	    }
	  parens2.skip_until_found_close (parser);
	  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      ଅଚଳ ଅକ୍ଷର *q = "";
	      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
		q = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ);
	      ଯଦି (strcmp (q, "traits") != 0 && strcmp (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_found_close (parser);
		  ଫେରନ୍ତୁ list;
		}
	      ଅନ୍ୟଥା ଯଦି (strcmp (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_found_close (parser);
		  ଫେରନ୍ତୁ list;
		}
	      c_parser_consume_token (parser);
	      ଯଦି (!parens2.require_open (parser))
		{
		  parens.skip_until_found_close (parser);
		  ଫେରନ୍ତୁ list;
		}
	      ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	      ଯଦି (strcmp (q, "traits") == 0)
		{
		  traits_var = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
		  traits_var = c_fully_fold (traits_var, ମିଥ୍ୟା, ଖାଲି);
		  mark_exp_read (traits_var);
		}
	      ଅନ୍ୟଥା
		{
		  memspace_ପଦସମଷ୍ଟି = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
		  memspace_ପଦସମଷ୍ଟି = c_fully_fold (memspace_ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ଖାଲି);
		}
	      parens2.skip_until_found_close (parser);
	    }
	  ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    ଯାଅ end;
	}
    }

  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      ଅଚଳ ଅକ୍ଷର *tok_s = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ);
      ବୃକ୍ଷ t = lookup_name (tok->ମୂଲ୍ୟ);
      ଯଦି (t == NULL_ବୃକ୍ଷ)
	{
	  undeclared_variable (tok->location, tok->ମୂଲ୍ୟ);
	  t = error_mark_ଗଣ୍ଠି;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      ବୃକ୍ଷ legacy_traits = NULL_ବୃକ୍ଷ;
      ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  ଅଚଳ ଅକ୍ଷର *tok_a
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_found_close (parser);

	  ଯଦି (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      ଯାଅ end;
	    }
	  legacy_traits = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
	  ଯଦି (legacy_traits == error_mark_ଗଣ୍ଠି)
	    ଯାଅ end;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  ଯଦି (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.add_fixit_replace (alloc_loc, "traits");
	      richloc.add_fixit_ଭର୍ତ୍ତି_after (close_loc, ": ");
	      richloc.add_fixit_ଭର୍ତ୍ତି_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      ଯଦି (seen_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  ଯାଅ end;
	}
      seen_allocators = ସତ୍ୟ;

      ବୃକ୍ଷ c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_USES_ALLOCATORS);
      OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c) = memspace_ପଦସମଷ୍ଟି;
      OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
    }

  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      ଯାଅ parse_next;
    }

 end:
  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ nl;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_linear (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  ବୃକ୍ଷ nl, c, step;
  ଗଣନା omp_clause_linear_kind kind = OMP_CLAUSE_LINEAR_DEFAULT;
  ତାର୍କିକ old_linear_modifier = ମିଥ୍ୟା;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ);
      ଯଦି (strcmp ("val", p) == 0)
	kind = OMP_CLAUSE_LINEAR_VAL;
      ଯଦି (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	kind = OMP_CLAUSE_LINEAR_DEFAULT;
      ଯଦି (kind != OMP_CLAUSE_LINEAR_DEFAULT)
	{
	  old_linear_modifier = ସତ୍ୟ;
	  rm1_loc = make_location (tok->location, tok->location,
				   c_parser_peek_2nd_token (parser)->location);
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_LINEAR, list);

  ଯଦି (kind != OMP_CLAUSE_LINEAR_DEFAULT)
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
    }

  ଯଦି (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = ପଦସମଷ୍ଟି_loc;
      ତାର୍କିକ has_modifiers = ମିଥ୍ୟା;
      ଯଦି (kind == OMP_CLAUSE_LINEAR_DEFAULT
	  && c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ);
	  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା pos = 0;
	  ଯଦି (strcmp ("val", p) == 0)
	    pos = 2;
	  ଅନ୍ୟଥା ଯଦି (strcmp ("step", p) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      pos = 3;
	      ଯଦି (c_parser_check_balanced_raw_token_sequence (parser, &pos)
		  && (c_parser_peek_nth_token_raw (parser, pos)->type
		      == CPP_CLOSE_PAREN))
		++pos;
	      ଅନ୍ୟଥା
		pos = 0;
	    }
	  ଯଦି (pos)
	    {
	      tok = c_parser_peek_nth_token_raw (parser, pos);
	      ଯଦି (tok->type == CPP_COMMA || tok->type == CPP_CLOSE_PAREN)
		has_modifiers = ସତ୍ୟ;
	    }
	}
      ଯଦି (has_modifiers)
	{
	  step = NULL_ବୃକ୍ଷ;
	  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ);
	      ଯଦି (strcmp ("val", p) == 0)
		{
		  ଯଦି (kind != OMP_CLAUSE_LINEAR_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  kind = OMP_CLAUSE_LINEAR_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      ଅନ୍ୟଥା ଯଦି (strcmp ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  ଯଦି (parens2.require_open (parser))
		    {
		      ଯଦି (step)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
		      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
		      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା,
						       ସତ୍ୟ);
		      step = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
		      ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (step)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  step = integer_one_ଗଣ୍ଠି;
			}
		      parens2.skip_until_found_close (parser);
		    }
		  ଅନ୍ୟଥା
		    ଭାଙ୍ଗ;
		}
	      ଅନ୍ୟଥା
		ଭାଙ୍ଗ;
	      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ଜାରି;
		}
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (!step)
	    step = integer_one_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା
	{
	  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
	  step = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
	  ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (step)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      step = integer_one_ଗଣ୍ଠି;
	    }
	}

    }
  ଅନ୍ୟଥା
    step = integer_one_ଗଣ୍ଠି;

  ପାଇଁ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_LINEAR_STEP (c) = step;
      OMP_CLAUSE_LINEAR_KIND (c) = kind;
      OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c) = old_linear_modifier;
    }

  ଯଦି (old_linear_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      ଯଦି (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_remove (rm1_loc);
	  ଯଦି (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.add_fixit_remove (rm2_loc);
	      richloc.add_fixit_ଭର୍ତ୍ତି_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.add_fixit_ଭର୍ତ୍ତି_before (close_loc, ")");
	    }
	  ଅନ୍ୟଥା
	    richloc.add_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_nontemporal (c_parser *parser, ବୃକ୍ଷ list)
{
  ଫେରନ୍ତୁ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_safelen (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ c, t;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
  t = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
  t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);
  ଯଦି (ବୃକ୍ଷ_CODE (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t))
      || ବୃକ୍ଷ_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_ବୃକ୍ଷ;
    }

  parens.skip_until_found_close (parser);
  ଯଦି (t == NULL_ବୃକ୍ଷ || t == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_ପଦସମଷ୍ଟି (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_simdlen (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ c, t = NULL_ବୃକ୍ଷ, type = NULL_ବୃକ୍ଷ, ଭାଜକ = NULL_ବୃକ୍ଷ;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  unsigned pos = 3;
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ),
		 "scaled") == 0
      && c_parser_check_balanced_raw_token_sequence (parser, &pos)
      && c_parser_peek_nth_token_raw (parser, ++pos)->type == CPP_COLON)
    {
      c_parser_consume_token (parser);
      matching_parens parens2;
      parens2.require_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      ସଂରଚନା c_type_name *ctype = c_parser_type_name (parser);
      ଯଦି (ctype == ଖାଲି
	  || (type = groktypename (ctype, ଖାଲି, ଖାଲି)) == ଖାଲି
	  || (!INTEGRAL_TYPE_P (type)
	      && !SCALAR_FLOAT_TYPE_P (type)
	      && ବୃକ୍ଷ_CODE (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
	  ଭାଜକ = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
	  ଭାଜକ = c_fully_fold (ଭାଜକ, ମିଥ୍ୟା, ଖାଲି);
	  ଯଦି (ବୃକ୍ଷ_CODE (ଭାଜକ) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ଭାଜକ))
	      || ବୃକ୍ଷ_int_cst_sgn (ଭାଜକ) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_ଗଣ୍ଠି;
	    }
	}
      parens2.skip_until_found_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  ଯଦି (type != error_mark_ଗଣ୍ଠି)
    {
      location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
      t = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);
      ଯଦି (ବୃକ୍ଷ_CODE (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t))
	  || ବୃକ୍ଷ_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_ବୃକ୍ଷ;
	}
    }

  parens.skip_until_found_close (parser);
  ଯଦି (type == error_mark_ଗଣ୍ଠି || t == NULL_ବୃକ୍ଷ || t == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_ପଦସମଷ୍ଟି (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_ଭାଜକ (c) = ଭାଜକ;
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   ବୃକ୍ଷ list, ତାର୍କିକ depend_p)
{
  ବୃକ୍ଷ vec = ଖାଲି;
  ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      ଫେରନ୍ତୁ list;
    }

  ଯଦି (!depend_p)
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_ସଂଖ୍ୟା
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  ବୃକ୍ଷ val = c_parser_peek_nth_token (parser, 3)->ମୂଲ୍ୟ;
	  ଯଦି (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      ବୃକ୍ଷ u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      ଫେରନ୍ତୁ u;
	    }
	}
    }



  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_kind == C_ID_ID)
    {
      ବୃକ୍ଷ t = lookup_name (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ବୃକ୍ଷ addend = ଖାଲି;

      ଯଦି (t == NULL_ବୃକ୍ଷ)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	  t = error_mark_ଗଣ୍ଠି;
	}

      c_parser_consume_token (parser);

      ତାର୍କିକ neg = ମିଥ୍ୟା;
      ଯଦି (c_parser_next_token_is (parser, CPP_MINUS))
	neg = ସତ୍ୟ;
      ଅନ୍ୟଥା ଯଦି (!c_parser_next_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_ଗଣ୍ଠି;
	  neg = ମିଥ୍ୟା;
	  ଯାଅ add_to_vector;
	}
      c_parser_consume_token (parser);

      ଯଦି (c_parser_next_token_is_not (parser, CPP_ସଂଖ୍ୟା))
	{
	  c_parser_error (parser, "expected integer");
	  ଫେରନ୍ତୁ list;
	}

      addend = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      ଯଦି (ବୃକ୍ଷ_CODE (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  ଫେରନ୍ତୁ list;
	}
      c_parser_consume_token (parser);

    add_to_vector:
      ଯଦି (t != error_mark_ଗଣ୍ଠି)
	{
	  vec = ବୃକ୍ଷ_cons (addend, t, vec);
	  ଯଦି (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      ଯଦି (c_parser_next_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_kind != C_ID_ID)
	ଭାଙ୍ଗ;

      c_parser_consume_token (parser);
    }

  ଯଦି (vec == NULL_ବୃକ୍ଷ)
    ଫେରନ୍ତୁ list;

  ବୃକ୍ଷ u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
  OMP_CLAUSE_DOACROSS_DEPEND (u) = depend_p;
  OMP_CLAUSE_DECL (u) = nreverse (vec);
  OMP_CLAUSE_CHAIN (u) = list;
  ଫେରନ୍ତୁ u;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_iterators (c_parser *parser)
{
  ବୃକ୍ଷ ret = NULL_ବୃକ୍ଷ, *last = &ret;
  c_parser_consume_token (parser);

  ଠେଲ_scope ();

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  କର
    {
      ବୃକ୍ଷ iter_type = NULL_ବୃକ୍ଷ, type_ପଦସମଷ୍ଟି = NULL_ବୃକ୍ଷ;
      ଯଦି (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
	{
	  ସଂରଚନା c_type_name *type = c_parser_type_name (parser);
	  ଯଦି (type != ଖାଲି)
	    iter_type = groktypename (type, &type_ପଦସମଷ୍ଟି, ଖାଲି);
	}
      ଯଦି (iter_type == NULL_ବୃକ୍ଷ)
	iter_type = integer_type_ଗଣ୍ଠି;

      location_t loc = c_parser_peek_token (parser)->location;
      ଯଦି (!c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  ଭାଙ୍ଗ;
	}

      ବୃକ୍ଷ id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      c_parser_consume_token (parser);

      ଯଦି (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	ଭାଙ୍ଗ;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (eloc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ମିଥ୍ୟା);
      ବୃକ୍ଷ begin = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;

      ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ଭାଙ୍ଗ;

      eloc = c_parser_peek_token (parser)->location;
      ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (eloc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ମିଥ୍ୟା);
      ବୃକ୍ଷ end = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;

      ବୃକ୍ଷ step = integer_one_ଗଣ୍ଠି;
      ଯଦି (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (eloc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ମିଥ୍ୟା);
	  step = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
	}

      ବୃକ୍ଷ iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *last = make_omp_iterator ();
      OMP_ITERATOR_VAR (*last) = iter_var;
      OMP_ITERATOR_BEGIN (*last) = begin;
      OMP_ITERATOR_END (*last) = end;
      OMP_ITERATOR_STEP (*last) = step;
      last = &ବୃକ୍ଷ_CHAIN (*last);

      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  ଜାରି;
	}
      ଭାଙ୍ଗ;
    }
  ଯେତେବେଳେ (1);

  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ ret ? ret : error_mark_ଗଣ୍ଠି;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_affinity (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ nl, iterators = NULL_ବୃକ୍ଷ;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ତାର୍କିକ parse_iter = ((strcmp ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      ଯଦି (parse_iter)
	{
	  unsigned n = 3;
	  parse_iter = (c_parser_check_balanced_raw_token_sequence (parser, &n)
			&& (c_parser_peek_nth_token_raw (parser, n)->type
			    == CPP_CLOSE_PAREN)
			&& (c_parser_peek_nth_token_raw (parser, n + 1)->type
			    == CPP_COLON));
	}
      ଯଦି (parse_iter)
	{
	  iterators = c_parser_omp_iterators (parser);
	  ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    {
	      ଯଦି (iterators)
		କାଢ଼_scope ();
	      parens.skip_until_found_close (parser);
	      ଫେରନ୍ତୁ list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  ଯଦି (iterators)
    {
      ବୃକ୍ଷ block = କାଢ଼_scope ();
      ଯଦି (iterators != error_mark_ଗଣ୍ଠି)
	{
	  OMP_ITERATOR_BLOCK (iterators) = block;
	  ପାଇଁ (ବୃକ୍ଷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_ବୃକ୍ଷ_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ nl;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_depend (c_parser *parser, ବୃକ୍ଷ list, location_t here)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ଗଣନା omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_LAST;
  ଗଣନା omp_clause_doacross_kind dkind = OMP_CLAUSE_DOACROSS_LAST;
  ବୃକ୍ଷ nl, c, iterators = NULL_ବୃକ୍ଷ;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  କର
    {
      ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
	ଯାଅ invalid_kind;

      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp ("iterator", p) == 0 && iterators == NULL_ବୃକ୍ଷ)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  ଜାରି;
	}
      ଯଦି (strcmp ("in", p) == 0)
	kind = OMP_CLAUSE_DEPEND_IN;
      ଅନ୍ୟଥା ଯଦି (strcmp ("inout", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUT;
      ଅନ୍ୟଥା ଯଦି (strcmp ("inoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUTSET;
      ଅନ୍ୟଥା ଯଦି (strcmp ("mutexinoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      ଅନ୍ୟଥା ଯଦି (strcmp ("out", p) == 0)
	kind = OMP_CLAUSE_DEPEND_OUT;
      ଅନ୍ୟଥା ଯଦି (strcmp ("depobj", p) == 0)
	kind = OMP_CLAUSE_DEPEND_DEPOBJ;
      ଅନ୍ୟଥା ଯଦି (strcmp ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      ଅନ୍ୟଥା ଯଦି (strcmp ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SOURCE;
	}
      ଅନ୍ୟଥା
	ଯାଅ invalid_kind;
      ଭାଙ୍ଗ;
    }
  ଯେତେବେଳେ (1);

  c_parser_consume_token (parser);

  ଯଦି (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_SOURCE
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      କାଢ଼_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_SOURCE ? "source" : "sink");
      iterators = NULL_ବୃକ୍ଷ;
    }

  ଯଦି (dkind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_ବୃକ୍ଷ;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_found_close (parser);
      ଫେରନ୍ତୁ c;
    }

  ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    ଯାଅ resync_fail;

  ଯଦି (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, ସତ୍ୟ);
  ଅନ୍ୟଥା
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      ଯଦି (iterators)
	{
	  ବୃକ୍ଷ block = କାଢ଼_scope ();
	  ଯଦି (iterators == error_mark_ଗଣ୍ଠି)
	    iterators = NULL_ବୃକ୍ଷ;
	  ଅନ୍ୟଥା
	    OMP_ITERATOR_BLOCK (iterators) = block;
	}

      ପାଇଁ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_KIND (c) = kind;
	  ଯଦି (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_ବୃକ୍ଷ_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ nl;

 invalid_kind:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  ଯଦି (iterators)
    କାଢ଼_scope ();
  ଫେରନ୍ତୁ list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_doacross (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ଗଣନା omp_clause_doacross_kind kind = OMP_CLAUSE_DOACROSS_LAST;
  ବୃକ୍ଷ nl;
  ଅଚଳ ଅକ୍ଷର *p;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME))
    ଯାଅ invalid_kind;

  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
  ଯଦି (strcmp ("sink", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SINK;
  ଅନ୍ୟଥା ଯଦି (strcmp ("source", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SOURCE;
  ଅନ୍ୟଥା
    ଯାଅ invalid_kind;

  c_parser_consume_token (parser);

  ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    ଯାଅ resync_fail;

  ଯଦି (kind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (nl) = OMP_CLAUSE_DOACROSS_SOURCE;
      OMP_CLAUSE_DECL (nl) = NULL_ବୃକ୍ଷ;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  ଅନ୍ୟଥା
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, ମିଥ୍ୟା);

  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ nl;

 invalid_kind:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  ଗଣନା omp_clause_fallback_kind kind = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  unsigned n = 3;
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  ଫେରନ୍ତୁ list;
	}
      c_parser_consume_token (parser);
      ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	ଫେରନ୍ତୁ list;
      p = "";
      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "abort") == 0)
	kind = OMP_CLAUSE_FALLBACK_ABORT;
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "default_mem") == 0)
	kind = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "null") == 0)
	kind = OMP_CLAUSE_FALLBACK_NULL;
      ଅନ୍ୟଥା
	{
	  c_parser_error (parser, "expected %<abort%>, %<default_mem%>, or "
				  "%<null%> as fallback mode");
	  ଫେରନ୍ତୁ list;
	}
      c_parser_consume_token (parser);
      ଯଦି (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	ଫେରନ୍ତୁ list;
      ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ଫେରନ୍ତୁ list;
    }
  location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
  ବୃକ୍ଷ size = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
  parens.skip_until_found_close (parser);

  ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (size)))
    {
      error_at (ପଦସମଷ୍ଟି_loc, "expected integer expression");
      ଫେରନ୍ତୁ list;
    }

  /* Attempt to statically determine when the number is negative.  */
  ବୃକ୍ଷ c = fold_build2_loc (ପଦସମଷ୍ଟି_loc, LT_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି, size,
			    build_int_cst (ବୃକ୍ଷ_TYPE (size), 0));
  protected_set_ପଦସମଷ୍ଟି_location (c, ପଦସମଷ୍ଟି_loc);
  ଯଦି (c == boolean_true_ଗଣ୍ଠି)
    {
      warning_at (ପଦସମଷ୍ଟି_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      size = integer_zero_ଗଣ୍ଠି;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_KIND (c) = kind;
  OMP_CLAUSE_DYN_GROUPPRIVATE_ପଦସମଷ୍ଟି (c) = size;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  ଫେରନ୍ତୁ list;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_map (c_parser *parser, ବୃକ୍ଷ list, ତାର୍କିକ declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ nl, c;
  ଗଣନା gomp_map_kind kind = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା pos = 1;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା map_kind_pos = 0;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା iterator_length = 0;
  ପାଇଁ (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      ଯଦି (tok->type != CPP_NAME)
	ଭାଙ୍ଗ;

      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ);
      c_token *next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      ଯଦି (strcmp (p, "iterator") == 0 && next_tok->type == CPP_OPEN_PAREN)
	{
	  unsigned n = pos + 2;
	  ଯଦି (c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_length = n - pos + 1;
	      pos = n;
	      next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      ଯଦି (next_tok->type == CPP_COLON)
	{
	  map_kind_pos = pos;
	  ଭାଙ୍ଗ;
	}

      ଯଦି (next_tok->type == CPP_COMMA)
	pos++;
      ଅନ୍ୟଥା ଯଦି (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା npos = pos + 2;
	  ଯଦି (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, npos + 1)->type
		  == CPP_COMMA))
	    pos = npos + 1;
	}

      pos++;
    }

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା always_modifier = 0;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା close_modifier = 0;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା present_modifier = 0;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା mapper_modifier = 0;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_commas = 0;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_identifiers = 0;
  ବୃକ୍ଷ mapper_name = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ iterators = NULL_ବୃକ୍ଷ;
  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା pos = 1; pos < map_kind_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      ଯଦି (tok->type == CPP_COMMA)
	{
	  ++ଅଙ୍କ_commas;
	  ଯଦି (ଅଙ୍କ_commas > ଅଙ୍କ_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  ଜାରି;
	}

      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ);
      ଯଦି (strcmp ("always", p) == 0)
	{
	  ଯଦି (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_found_close (parser);
	      ଫେରନ୍ତୁ list;
	    }
	  always_modifier++;
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା ଯଦି (strcmp ("close", p) == 0)
	{
	  ଯଦି (close_modifier)
	    {
	      c_parser_error (parser, "too many %<close%> modifiers");
	      parens.skip_until_found_close (parser);
	      ଫେରନ୍ତୁ list;
	    }
	  close_modifier++;
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା ଯଦି (strcmp ("iterator", p) == 0)
	{
	  ଯଦି (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      ଫେରନ୍ତୁ list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      ଅନ୍ୟଥା ଯଦି (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  ଯଦି (mparens.require_open (parser))
	    {
	      ଯଦି (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  ଫେରନ୍ତୁ list;
		}

	      tok = c_parser_peek_token (parser);

	      ବାଛ (tok->type)
		{
		ସ୍ଥିତି CPP_NAME:
		  {
		    mapper_name = tok->ମୂଲ୍ୟ;
		    c_parser_consume_token (parser);
		    ଯଦି (declare_mapper_p)
		      {
			error_at (tok->location,
				  "in %<declare mapper%> directives, parameter "
				  "to %<mapper%> modifier must be %<default%>");
		      }
		  }
		  ଭାଙ୍ଗ;

		ସ୍ଥିତି CPP_KEYWORD:
		  ଯଦି (tok->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      ଭାଙ୍ଗ;
		    }
		  /* Fallthrough.  */

		ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		  error_at (tok->location,
			    "expected identifier or %<default%>");
		  ଫେରନ୍ତୁ list;
		}

	      ଯଦି (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  ଫେରନ୍ତୁ list;
		}

	      mapper_modifier++;
	      pos += 3;
	    }
	}
      ଅନ୍ୟଥା ଯଦି (strcmp ("present", p) == 0)
	{
	  ଯଦି (present_modifier)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      ଫେରନ୍ତୁ list;
	    }
	  present_modifier++;
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା
	{
	  c_parser_error (parser, "%<map%> clause with map-type modifier other "
				  "than %<always%>, %<close%>, %<iterator%>, "
				  "%<mapper%> or %<present%>");
	  parens.skip_until_found_close (parser);
	  ଫେରନ୍ତୁ list;
	}
      ++ଅଙ୍କ_identifiers;
      ଯଦି (ଅଙ୍କ_identifiers - 1 > ଅଙ୍କ_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_ଭର୍ତ୍ତି_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      ଅଙ୍କ_commas = ଅଙ୍କ_identifiers - 1;
    }

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା always_present_modifier = always_modifier && present_modifier;

      ଯଦି (strcmp ("alloc", p) == 0)
	kind = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      ଅନ୍ୟଥା ଯଦି (strcmp ("to", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TO
		: present_modifier ? GOMP_MAP_PRESENT_TO
		: always_modifier ? GOMP_MAP_ALWAYS_TO
		: GOMP_MAP_TO);
      ଅନ୍ୟଥା ଯଦି (strcmp ("from", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      ଅନ୍ୟଥା ଯଦି (strcmp ("tofrom", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      ଅନ୍ୟଥା ଯଦି (strcmp ("release", p) == 0)
	kind = GOMP_MAP_RELEASE;
      ଅନ୍ୟଥା ଯଦି (strcmp ("delete", p) == 0)
	kind = GOMP_MAP_DELETE;
      ଅନ୍ୟଥା
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ଫେରନ୍ତୁ list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   ସତ୍ୟ);

  ବୃକ୍ଷ last_new = NULL_ବୃକ୍ଷ;

  ଯଦି (iterators)
    {
      ବୃକ୍ଷ block = କାଢ଼_scope ();
      ଯଦି (iterators == error_mark_ଗଣ୍ଠି)
	iterators = NULL_ବୃକ୍ଷ;
      ଅନ୍ୟଥା
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  ପାଇଁ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      last_new = c;
    }

  ଯଦି (mapper_name)
    {
      ବୃକ୍ଷ name = build_omp_clause (ନିବେଶ_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_ଠେଲ_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (ନିବେଶ_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_କାଢ଼_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_ଗଣ୍ଠି;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_device (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t ପଦସମଷ୍ଟି_loc;
  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
  ବୃକ୍ଷ c, t;
  ତାର୍କିକ ancestor = ମିଥ୍ୟା;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ);
      ଯଦି (strcmp ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  ଯଦି ((omp_requires_mask & OMP_REQUIRES_REVERSE_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_found_close (parser);
	      ଫେରନ୍ତୁ list;
	    }
	  ancestor = ସତ୍ୟ;
	}
      ଅନ୍ୟଥା ଯଦି (strcmp ("device_num", p) == 0)
	;
      ଅନ୍ୟଥା
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_found_close (parser);
	  ଫେରନ୍ତୁ list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
  ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
  ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
  t = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
  t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);

  parens.skip_until_found_close (parser);

  ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      ଫେରନ୍ତୁ list;
    }
  ଯଦି (ancestor && ବୃକ୍ଷ_CODE (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (ପଦସମଷ୍ଟି_loc, "the %<device%> clause expression must evaluate to "
			  "%<1%>");
      ଫେରନ୍ତୁ list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE, "device");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE);

  OMP_CLAUSE_DEVICE_ID (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEVICE_ANCESTOR (c) = ancestor;

  list = c;
  ଫେରନ୍ତୁ list;
}

/* OpenMP 4.0:
   dist_schedule ( static )
   dist_schedule ( static , expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_dist_schedule (c_parser *parser, ବୃକ୍ଷ list)
{
  ବୃକ୍ଷ c, t = NULL_ବୃକ୍ଷ;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  ଯଦି (!c_parser_next_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      ଫେରନ୍ତୁ list;
    }

  c_parser_consume_token (parser);
  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
      t = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);
      parens.skip_until_found_close (parser);
    }
  ଅନ୍ୟଥା
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  ଯଦି (omp_find_clause (list, OMP_CLAUSE_DIST_SCHEDULE))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  ଯଦି (t == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_SCHEDULE);
  OMP_CLAUSE_DIST_SCHEDULE_CHUNK_ପଦସମଷ୍ଟି (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_proc_bind (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ଗଣନା omp_clause_proc_bind_kind kind;
  ବୃକ୍ଷ c;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp ("primary", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_PRIMARY;
      ଅନ୍ୟଥା ଯଦି (strcmp ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  kind = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      ଅନ୍ୟଥା ଯଦି (strcmp ("close", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_CLOSE;
      ଅନ୍ୟଥା ଯଦି (strcmp ("spread", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_SPREAD;
      ଅନ୍ୟଥା
	ଯାଅ invalid_kind;
    }
  ଅନ୍ୟଥା
    ଯାଅ invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;

 invalid_kind:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_device_type (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ଗଣନା omp_clause_device_type_kind kind;
  ବୃକ୍ଷ c;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp ("host", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_HOST;
      ଅନ୍ୟଥା ଯଦି (strcmp ("nohost", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      ଅନ୍ୟଥା ଯଦି (strcmp ("any", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_ANY;
      ଅନ୍ୟଥା
	ଯାଅ invalid_kind;
    }
  ଅନ୍ୟଥା
    ଯାଅ invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;

 invalid_kind:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ list;
}

/* OpenMP 4.0:
   from ( variable-list )
   to ( variable-list )

   OpenMP 5.1:
   from ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )
   to ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )

   motion-modifier:
     present | iterator (iterators-definition) | mapper (id)  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_from_to (c_parser *parser, ଗଣନା omp_clause_code kind,
			     ବୃକ୍ଷ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା pos = 1, colon_pos = 0;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା iterator_length = 0;

  ଯେତେବେଳେ (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      ଅଚଳ ଅକ୍ଷର *identifier =
	IDENTIFIER_POINTER (c_parser_peek_nth_token_raw (parser, pos)->ମୂଲ୍ୟ);
      ଯଦି (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା npos = pos + 2;
	  ଯଦି (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      ଯଦି (strcmp (identifier, "iterator") == 0)
		iterator_length = npos - pos + 1;
	      pos = npos;
	    }
	}
      ଯଦି (c_parser_peek_nth_token_raw (parser, pos + 1)->type == CPP_COMMA)
	pos += 2;
      ଅନ୍ୟଥା
	pos++;
      ଯଦି (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_COLON)
	{
	  colon_pos = pos;
	  ଭାଙ୍ଗ;
	}
    }

  ତାର୍କିକ present = ମିଥ୍ୟା, mapper_modifier = ମିଥ୍ୟା;
  ବୃକ୍ଷ iterators = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ mapper_name = NULL_ବୃକ୍ଷ;

  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      ଯଦି (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ଜାରି;
	}
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (token->ମୂଲ୍ୟ);
      ଯଦି (strcmp ("present", p) == 0)
	{
	  ଯଦି (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      ଫେରନ୍ତୁ list;
	    }
	  present = ସତ୍ୟ;
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା ଯଦି (strcmp ("iterator", p) == 0)
	{
	  ଯଦି (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      ଫେରନ୍ତୁ list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      ଅନ୍ୟଥା ଯଦି (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  ଯଦି (mparens.require_open (parser))
	    {
	      ଯଦି (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  ଫେରନ୍ତୁ list;
		}

	      token = c_parser_peek_token (parser);
	      ବାଛ (token->type)
		{
		ସ୍ଥିତି CPP_NAME:
		  {
		    mapper_name = token->ମୂଲ୍ୟ;
		    c_parser_consume_token (parser);
		  }
		  ଭାଙ୍ଗ;
		ସ୍ଥିତି CPP_KEYWORD:
		  ଯଦି (token->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      ଭାଙ୍ଗ;
		    }
		  /* FALLTHROUGH  */
		ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		  error_at (token->location,
			    "expected identifier or %<default%>");
		  ଫେରନ୍ତୁ list;
		}
	      ଯଦି (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  ଫେରନ୍ତୁ list;
		}
	      mapper_modifier = ସତ୍ୟ;
	      pos += 3;
	    }
	}
      ଅନ୍ୟଥା
	{
	  error_at (token->location,
		    "%qs clause with modifier other than %<iterator%>, "
		    "%<mapper%>, or %<present%>",
		    kind == OMP_CLAUSE_TO ? "to" : "from");
	  parens.skip_until_found_close (parser);
	  ଫେରନ୍ତୁ list;
	}
    }

  ଯଦି (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  ବୃକ୍ଷ nl = c_parser_omp_variable_list (parser, loc, kind, list);
  parens.skip_until_found_close (parser);

  ଯଦି (present)
    ପାଇଁ (ବୃକ୍ଷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  ଯଦି (iterators)
    {
      ବୃକ୍ଷ block = କାଢ଼_scope ();
      ଯଦି (iterators == error_mark_ଗଣ୍ଠି)
	iterators = NULL_ବୃକ୍ଷ;
      ଅନ୍ୟଥା
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  ଯଦି (iterators)
    ପାଇଁ (ବୃକ୍ଷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  ଯଦି (mapper_name)
    {
      ବୃକ୍ଷ last_new = NULL_ବୃକ୍ଷ;
      ପାଇଁ (ବୃକ୍ଷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	last_new = c;

      ବୃକ୍ଷ name = build_omp_clause (ନିବେଶ_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_ଠେଲ_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (ନିବେଶ_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_କାଢ଼_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_ଗଣ୍ଠି;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  ଫେରନ୍ତୁ nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_uniform (c_parser *parser, ବୃକ୍ଷ list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_UNIFORM,
					 list);
      parens.skip_until_found_close (parser);
    }
  ଫେରନ୍ତୁ list;
}

/* OpenMP 5.1
   full */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_full (c_parser *parser, ବୃକ୍ଷ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_FULL, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ c = build_omp_clause (loc, OMP_CLAUSE_FULL);
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_partial (c_parser *parser, ବୃକ୍ଷ list)
{
  ବୃକ୍ଷ ଅଙ୍କ = NULL_ବୃକ୍ଷ;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      ଅଙ୍କ = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି).ମୂଲ୍ୟ;
      parens.skip_until_found_close (parser);

      ଯଦି (ଅଙ୍କ == error_mark_ଗଣ୍ଠି)
	ଫେରନ୍ତୁ list;

      mark_exp_read (ଅଙ୍କ);
      ଅଙ୍କ = c_fully_fold (ଅଙ୍କ, ମିଥ୍ୟା, ଖାଲି);
      HOST_WIDE_INT n;
      ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ଅଙ୍କ))
	  || !ବୃକ୍ଷ_fits_shwi_p (ଅଙ୍କ)
	  || (n = ବୃକ୍ଷ_to_shwi (ଅଙ୍କ)) <= 0
	  || (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  ଫେରନ୍ତୁ list;
	}
    }

  ବୃକ୍ଷ c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_ପଦସମଷ୍ଟି (c) = ଅଙ୍କ;
  OMP_CLAUSE_CHAIN (c) = list;
  ଫେରନ୍ତୁ c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_novariants (c_parser *parser, ବୃକ୍ଷ list)
{
  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
  ବୃକ୍ଷ t = convert_lvalue_to_rvalue (loc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ସତ୍ୟ).ମୂଲ୍ୟ;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  ବୃକ୍ଷ c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_ପଦସମଷ୍ଟି (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  ଫେରନ୍ତୁ list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_nocontext (c_parser *parser, ବୃକ୍ଷ list)
{
  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
  ବୃକ୍ଷ t = convert_lvalue_to_rvalue (loc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ସତ୍ୟ).ମୂଲ୍ୟ;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  ବୃକ୍ଷ c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_ପଦସମଷ୍ଟି (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  ଫେରନ୍ତୁ list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_detach (c_parser *parser, ବୃକ୍ଷ list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_found_close (parser);
      ଫେରନ୍ତୁ list;
    }

  ବୃକ୍ଷ t = lookup_name (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
  ଯଦି (t == NULL_ବୃକ୍ଷ)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      parens.skip_until_found_close (parser);
      ଫେରନ୍ତୁ list;
    }
  c_parser_consume_token (parser);

  ବୃକ୍ଷ type = TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (t));
  ଯଦି (!INTEGRAL_TYPE_P (type)
      || ବୃକ୍ଷ_CODE (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_found_close (parser);
      ଫେରନ୍ତୁ list;
    }

  ବୃକ୍ଷ u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_found_close (parser);
  ଫେରନ୍ତୁ u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_destroy (c_parser *parser, ବୃକ୍ଷ list)
{
  ବୃକ୍ଷ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  ପାଇଁ (ବୃକ୍ଷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    ବୃକ୍ଷ_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
  ଫେରନ୍ତୁ nl;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  ଯଦି (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    ଯେତେବେଳେ (ସତ୍ୟ)
      {
	str += (ଅକ୍ଷର) GOMP_INTEROP_IFR_SEPARATOR;
	ଯଦି (c_parser_next_token_is (parser, CPP_STRING))
	  {
	    c_ପଦସମଷ୍ଟି cval = c_parser_string_literal (parser, ମିଥ୍ୟା, ମିଥ୍ୟା);
	    ଯଦି (cval.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
	      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	    ଯଦି ((size_t) ବୃକ୍ଷ_STRING_LENGTH (cval.ମୂଲ୍ୟ)
		!= strlen (ବୃକ୍ଷ_STRING_POINTER (cval.ମୂଲ୍ୟ)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = ସତ୍ୟ;
		ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	      }

	    ଅକ୍ଷର c = omp_get_fr_id_from_name (ବୃକ୍ଷ_STRING_POINTER (cval.ମୂଲ୍ୟ));
	    ଯଦି (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  ବୃକ୍ଷ_STRING_POINTER (cval.ମୂଲ୍ୟ));
	    str += c;
	  }
	ଅନ୍ୟଥା
	  {
	    c_ପଦସମଷ୍ଟି cval = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	    ବୃକ୍ଷ ମୂଲ୍ୟ = c_fully_fold (cval.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
	    ଯଦି (INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ))
		&& ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) != INTEGER_CST)
	      ମୂଲ୍ୟ = convert_lvalue_to_rvalue (cval.get_start (), cval,
						ମିଥ୍ୟା, ସତ୍ୟ).ମୂଲ୍ୟ;
	    ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) != INTEGER_CST
		|| !ବୃକ୍ଷ_fits_shwi_p (ମୂଲ୍ୟ))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	      }
	    HOST_WIDE_INT n = ବୃକ୍ଷ_to_shwi (ମୂଲ୍ୟ);
	    ଯଦି (n < 1 || n > GOMP_INTEROP_IFR_LAST)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (ଅକ୍ଷର) n;
	  }
	str += (ଅକ୍ଷର) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    ଜାରି;
	  }
	ଯଦି (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	str += '\0';
	ବୃକ୍ଷ res = build_string (str.length (), str.data ());
	ବୃକ୍ଷ_TYPE (res) = build_array_type_nelts (unsigned_char_type_ଗଣ୍ଠି,
						  str.length ());
	ଫେରନ୍ତୁ res;
      }

  /* New format. */
  std::string str2;
  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      ଯଦି (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
      str += (ଅକ୍ଷର) GOMP_INTEROP_IFR_SEPARATOR;
      str2.clear ();
      ତାର୍କିକ has_fr = ମିଥ୍ୟା;
      ଯେତେବେଳେ (ସତ୍ୟ)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  ଯଦି (tok->type != CPP_NAME
	      || (strcmp("fr", IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ)) != 0
		  && strcmp("attr", IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	    }
	  c_parser_consume_token (parser);
	  ତାର୍କିକ is_fr = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ)[0] == 'f';
	  ଯଦି (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	    }
	  ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	  ଯେତେବେଳେ (ସତ୍ୟ)
	    {
	      ଯଦି (c_parser_next_token_is (parser, CPP_STRING))
		{
		  c_ପଦସମଷ୍ଟି cval = c_parser_string_literal (parser, ମିଥ୍ୟା, ମିଥ୍ୟା);
		  ବୃକ୍ଷ ମୂଲ୍ୟ = cval.ମୂଲ୍ୟ;
		  ଯଦି (ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
		    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		  ଯଦି ((size_t) ବୃକ୍ଷ_STRING_LENGTH (ମୂଲ୍ୟ)
		      != strlen (ବୃକ୍ଷ_STRING_POINTER (ମୂଲ୍ୟ)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = ସତ୍ୟ;
		      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		    }
		  ଯଦି (!is_fr)
		    {
		      ଯଦି (!startswith (ବୃକ୍ଷ_STRING_POINTER (ମୂଲ୍ୟ), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = ସତ୍ୟ;
			  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
			}
		      ଯଦି (strchr (ବୃକ୍ଷ_STRING_POINTER (ମୂଲ୍ୟ), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = ସତ୍ୟ;
			  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
			}
		      str2 += ବୃକ୍ଷ_STRING_POINTER (ମୂଲ୍ୟ);
		      str2 += '\0';
		    }
		  ଅନ୍ୟଥା
		    {
		      ଯଦି (*ବୃକ୍ଷ_STRING_POINTER (ମୂଲ୍ୟ) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
			}
		      ଅକ୍ଷର c = omp_get_fr_id_from_name (ବୃକ୍ଷ_STRING_POINTER (ମୂଲ୍ୟ));
		      ଯଦି (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    ବୃକ୍ଷ_STRING_POINTER (ମୂଲ୍ୟ));
		     str += c;
		     has_fr = ସତ୍ୟ;
		    }
		}
	      ଅନ୍ୟଥା ଯଦି (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		}
	      ଅନ୍ୟଥା
		{
		  c_ପଦସମଷ୍ଟି cval = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
		  ବୃକ୍ଷ ମୂଲ୍ୟ = c_fully_fold (cval.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
		  ଯଦି (INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ମୂଲ୍ୟ))
		      && ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) != INTEGER_CST)
		    ମୂଲ୍ୟ = convert_lvalue_to_rvalue (cval.get_start (), cval,
						      ମିଥ୍ୟା, ସତ୍ୟ).ମୂଲ୍ୟ;

		  ଯଦି (ବୃକ୍ଷ_CODE (ମୂଲ୍ୟ) != INTEGER_CST
		      || !ବୃକ୍ଷ_fits_shwi_p (ମୂଲ୍ୟ))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		    }
		  HOST_WIDE_INT n = ବୃକ୍ଷ_to_shwi (ମୂଲ୍ୟ);
		  ଯଦି (n < 1 || n > GOMP_INTEROP_IFR_LAST)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (ଅକ୍ଷର) n;
		  has_fr = ସତ୍ୟ;
		}
	      ଯଦି (!is_fr
		  && c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ଜାରି;
		}
	      ଯଦି (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ଜାରି;
	    }
	  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    ଭାଙ୍ଗ;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      str += (ଅକ୍ଷର) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	ଭାଙ୍ଗ;
      ଯଦି (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  c_parser_consume_token (parser);
  str += '\0';
  ବୃକ୍ଷ res = build_string (str.length (), str.data ());
  ବୃକ୍ଷ_TYPE (res) = build_array_type_nelts (unsigned_char_type_ଗଣ୍ଠି,
						  str.length ());
  ଫେରନ୍ତୁ res;
}

/* OpenMP 5.1
     modifiers of the 'init' clause, used by the 'init' and the
     'append_args' clauses.

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification)

  Returns 'false' if an error has been issued.  */

ସ୍ଥିର ତାର୍କିକ
c_parser_omp_clause_init_modifiers (c_parser *parser, ତାର୍କିକ *target,
				    ତାର୍କିକ *targetsync, ବୃକ୍ଷ *prefer_type_ବୃକ୍ଷ)
{
  *target = ମିଥ୍ୟା;
  *targetsync = ମିଥ୍ୟା;
  *prefer_type_ବୃକ୍ଷ = NULL_ବୃକ୍ଷ;

  କର
    {
      c_token *tok = c_parser_peek_token (parser);
      ଯଦି (tok->type != CPP_NAME)
	ଯାଅ fail;
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ);
      ଯଦି (strcmp ("targetsync", p) == 0)
	{
	  ଯଦି (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = ସତ୍ୟ;
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା ଯଦି (strcmp ("target", p) == 0)
	{
	  ଯଦି (*target)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *target = ସତ୍ୟ;
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା ଯଦି (strcmp ("prefer_type", p) == 0)
	{
	  ଯଦି (*prefer_type_ବୃକ୍ଷ != NULL_ବୃକ୍ଷ)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_ବୃକ୍ଷ = c_parser_omp_modifier_prefer_type (parser);
	  ଯଦି (*prefer_type_ବୃକ୍ଷ == error_mark_ଗଣ୍ଠି)
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
      ଅନ୍ୟଥା
	ଯାଅ fail;
      tok = c_parser_peek_token (parser);
      ଯଦି (tok->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ଜାରି;
	}
      /* Unknown token - either done or an error; handle it in the caller.  */
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }
  ଯେତେବେଳେ (ସତ୍ୟ);

fail:
  c_parser_error (parser,
		  "expected %<prefer_type%>, %<target%>, or %<targetsync%>");
  ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* OpenMP 5.1:
   init ( [init-modifier-list : ] variable-list )

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_init (c_parser *parser, ବୃକ୍ଷ list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ list;

  ତାର୍କିକ target = ମିଥ୍ୟା;
  ତାର୍କିକ targetsync = ମିଥ୍ୟା;
  ବୃକ୍ଷ prefer_type_ବୃକ୍ଷ = NULL_ବୃକ୍ଷ;

  ଯଦି (!c_parser_omp_clause_init_modifiers (parser, &target, &targetsync,
					   &prefer_type_ବୃକ୍ଷ)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      ଯଦି (prefer_type_ବୃକ୍ଷ != error_mark_ଗଣ୍ଠି)
	parens.skip_until_found_close (parser);
      ଫେରନ୍ତୁ list;
    }

  ଯଦି (!target && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  ବୃକ୍ଷ nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					ମିଥ୍ୟା);
  parens.skip_until_found_close (parser);

  ପାଇଁ (ବୃକ୍ଷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      ବୃକ୍ଷ_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      ଯଦି (target)
	OMP_CLAUSE_INIT_TARGET (c) = 1;
      ଯଦି (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      ଯଦି (prefer_type_ବୃକ୍ଷ)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_ବୃକ୍ଷ;
    }
  ଫେରନ୍ତୁ nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_use (c_parser *parser, ବୃକ୍ଷ list)
{
  ଫେରନ୍ତୁ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_clause_interop (c_parser *parser, ବୃକ୍ଷ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  ବୃକ୍ଷ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  ପାଇଁ (ବୃକ୍ଷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      ବୃକ୍ଷ_USED (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  ଫେରନ୍ତୁ nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_mask mask,
			   ଅଚଳ ଅକ୍ଷର *where, ତାର୍କିକ finish_p = ସତ୍ୟ,
			   ତାର୍କିକ target_p = ମିଥ୍ୟା)
{
  ବୃକ୍ଷ clauses = ଖାଲି;
  ତାର୍କିକ first = ସତ୍ୟ;

  ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      ଅଚଳ ଅକ୍ଷର *c_name;
      ବୃକ୍ଷ prev = clauses;

      ଯଦି (!first && c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      ବାଛ (c_kind)
	{
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "attach";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copy";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyin";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyout";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "create";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "delete";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, ସତ୍ୟ);
	  c_name = "default";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "detach";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_data_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device_resident";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_GANG,
						c_name, clauses);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "host";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, ମିଥ୍ୟା);
	  c_name = "if";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "link";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "no_create";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_ଅଙ୍କ_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_ଅଙ୍କ_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_ଅଙ୍କ_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_ଅଙ୍କ_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "present";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     ମିଥ୍ୟା, clauses);
	  c_name = "reduction";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_SELF:
	  ଯଦି ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  ଅନ୍ୟଥା
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "self";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_SEQ,
						 clauses);
	  c_name = "seq";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_TILE:
	  clauses = c_parser_oacc_clause_tile (parser, clauses);
	  c_name = "tile";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_USE_DEVICE:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_VECTOR:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_VECTOR,
						c_name,	clauses);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_VECTOR_LENGTH:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_VECTOR_LENGTH,
						     clauses);
	  c_name = "vector_length";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OACC_CLAUSE_WORKER:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_WORKER,
						c_name, clauses);
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  c_parser_error (parser, "expected an OpenACC clause");
	  ଯାଅ saw_error;
	}

      first = ମିଥ୍ୟା;

      ଯଦି (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_to_pragma_eol (parser);

  ଯଦି (finish_p)
    ଫେରନ୍ତୁ c_finish_omp_clauses (clauses, target_p ? C_ORT_ACC_TARGET
						   : C_ORT_ACC);

  ଫେରନ୍ତୁ clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_all_clauses (c_parser *parser, omp_clause_mask mask,
			  ଅଚଳ ଅକ୍ଷର *where, ତାର୍କିକ finish_p = ସତ୍ୟ,
			  ପୂର୍ଣ୍ଣସଂଖ୍ୟା nested = 0)
{
  ବୃକ୍ଷ clauses = ଖାଲି;
  ତାର୍କିକ first = ସତ୍ୟ;

  ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      ଅଚଳ ଅକ୍ଷର *c_name;
      ବୃକ୍ଷ prev = clauses;

      ଯଦି (nested && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	ଭାଙ୍ଗ;

      ଯଦି (!first || nested != 2)
	{
	  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ଅନ୍ୟଥା ଯଦି (nested == 2)
	    error_at (c_parser_peek_token (parser)->location,
		      "clauses in %<simd%> trait should be separated "
		      "by %<,%>");
	}

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      ବାଛ (c_kind)
	{
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_BIND:
	  clauses = c_parser_omp_clause_bind (parser, clauses);
	  c_name = "bind";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, ମିଥ୍ୟା);
	  c_name = "default";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_DETACH:
	  clauses = c_parser_omp_clause_detach (parser, clauses);
	  c_name = "detach";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_FILTER:
	  clauses = c_parser_omp_clause_filter (parser, clauses);
	  c_name = "filter";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_FINAL:
	  clauses = c_parser_omp_clause_final (parser, clauses);
	  c_name = "final";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_GRAINSIZE:
	  clauses = c_parser_omp_clause_grainsize (parser, clauses);
	  c_name = "grainsize";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_HINT:
	  clauses = c_parser_omp_clause_hint (parser, clauses);
	  c_name = "hint";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_DEFAULTMAP:
	  clauses = c_parser_omp_clause_defaultmap (parser, clauses);
	  c_name = "defaultmap";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, ସତ୍ୟ);
	  c_name = "if";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_IN_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_IN_REDUCTION,
					     ସତ୍ୟ, clauses);
	  c_name = "in_reduction";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_INDIRECT:
	  clauses = c_parser_omp_clause_indirect (parser, clauses);
	  c_name = "indirect";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_MERGEABLE:
	  clauses = c_parser_omp_clause_mergeable (parser, clauses);
	  c_name = "mergeable";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_ଅଙ୍କ_TASKS:
	  clauses = c_parser_omp_clause_ଅଙ୍କ_tasks (parser, clauses);
	  c_name = "num_tasks";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_ଅଙ୍କ_THREADS:
	  clauses = c_parser_omp_clause_ଅଙ୍କ_threads (parser, clauses);
	  c_name = "num_threads";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_ORDER:
	  clauses = c_parser_omp_clause_order (parser, clauses);
	  c_name = "order";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_PRIORITY:
	  clauses = c_parser_omp_clause_priority (parser, clauses);
	  c_name = "priority";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     ସତ୍ୟ, clauses);
	  c_name = "reduction";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_SCHEDULE:
	  clauses = c_parser_omp_clause_schedule (parser, clauses);
	  c_name = "schedule";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     ସତ୍ୟ, clauses);
	  c_name = "task_reduction";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_UNTIED:
	  clauses = c_parser_omp_clause_untied (parser, clauses);
	  c_name = "untied";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_INBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_INBRANCH,
						clauses);
	  c_name = "inbranch";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_NONTEMPORAL:
	  clauses = c_parser_omp_clause_nontemporal (parser, clauses);
	  c_name = "nontemporal";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_NOTINBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_NOTINBRANCH,
						clauses);
	  c_name = "notinbranch";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_PARALLEL:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_PARALLEL,
					      clauses);
	  c_name = "parallel";
	  ଯଦି (!first)
	    {
	     clause_not_first:
	      error_at (here, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = prev;
	    }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  ଯଦି (!first)
	    ଯାଅ clause_not_first;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  ଯଦି (!first)
	    ଯାଅ clause_not_first;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  ଯଦି (!first)
	    ଯାଅ clause_not_first;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_LINK:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LINK, clauses);
	  c_name = "link";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_LOCAL:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LOCAL, clauses);
	  c_name = "local";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_TO:
	  ଯଦି ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (here);
	      richloc.add_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      ବୃକ୍ଷ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      ପାଇଁ (ବୃକ୍ଷ c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_TO (c) = 1;
	      clauses = nl;
	    }
	  ଅନ୍ୟଥା
	    clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_TO,
						   clauses);
	  c_name = "to";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_UNIFORM:
	  clauses = c_parser_omp_clause_uniform (parser, clauses);
	  c_name = "uniform";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_ଅଙ୍କ_TEAMS:
	  clauses = c_parser_omp_clause_ଅଙ୍କ_teams (parser, clauses);
	  c_name = "num_teams";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_THREAD_LIMIT:
	  clauses = c_parser_omp_clause_thread_limit (parser, clauses);
	  c_name = "thread_limit";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_ALIGNED:
	  clauses = c_parser_omp_clause_aligned (parser, clauses);
	  c_name = "aligned";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_ALLOCATE:
	  clauses = c_parser_omp_clause_allocate (parser, clauses);
	  c_name = "allocate";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_LINEAR:
	  clauses = c_parser_omp_clause_linear (parser, clauses);
	  c_name = "linear";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_USES_ALLOCATORS:
	  clauses = c_parser_omp_clause_uses_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, here);
	  c_name = "depend";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_DOACROSS:
	  clauses = c_parser_omp_clause_doacross (parser, clauses);
	  c_name = "doacross";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_DESTROY:
	  clauses = c_parser_omp_clause_destroy (parser, clauses);
	  c_name = "destroy";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE:
	  clauses = c_parser_omp_clause_dyn_groupprivate (parser, clauses);
	  c_name = "dyn_groupprivate";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_INIT:
	  clauses = c_parser_omp_clause_init (parser, clauses);
	  c_name = "init";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_USE:
	  clauses = c_parser_omp_clause_use (parser, clauses);
	  c_name = "use";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_INTEROP:
	  clauses = c_parser_omp_clause_interop (parser, clauses);
	  c_name = "interop";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_MAP:
	  clauses = c_parser_omp_clause_map (parser, clauses, ମିଥ୍ୟା);
	  c_name = "map";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device_ptr";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_use_device_addr (parser, clauses);
	  c_name = "use_device_addr";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_has_device_addr (parser, clauses);
	  c_name = "has_device_addr";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR:
	  clauses = c_parser_omp_clause_is_device_ptr (parser, clauses);
	  c_name = "is_device_ptr";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_DEVICE:
	  clauses = c_parser_omp_clause_device (parser, clauses);
	  c_name = "device";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_DIST_SCHEDULE:
	  clauses = c_parser_omp_clause_dist_schedule (parser, clauses);
	  c_name = "dist_schedule";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_PROC_BIND:
	  clauses = c_parser_omp_clause_proc_bind (parser, clauses);
	  c_name = "proc_bind";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_DEVICE_TYPE:
	  clauses = c_parser_omp_clause_device_type (parser, clauses);
	  c_name = "device_type";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_SAFELEN:
	  clauses = c_parser_omp_clause_safelen (parser, clauses);
	  c_name = "safelen";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_SIMDLEN:
	  clauses = c_parser_omp_clause_simdlen (parser, clauses);
	  c_name = "simdlen";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_NOGROUP:
	  clauses = c_parser_omp_clause_nogroup (parser, clauses);
	  c_name = "nogroup";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_THREADS:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_THREADS,
					       clauses);
	  c_name = "threads";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_SIMD:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_SIMD,
					       clauses);
	  c_name = "simd";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_ENTER:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					    clauses);
	  c_name = "enter";
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_FULL:
	  c_name = "full";
	  clauses = c_parser_omp_clause_full (parser, clauses);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_PARTIAL:
	  c_name = "partial";
	  clauses = c_parser_omp_clause_partial (parser, clauses);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_NOVARIANTS:
	  c_name = "novariants";
	  clauses = c_parser_omp_clause_novariants (parser, clauses);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_CLAUSE_NOCONTEXT:
	  c_name = "nocontext";
	  clauses = c_parser_omp_clause_nocontext (parser, clauses);
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  c_parser_error (parser, "expected an OpenMP clause");
	  ଯାଅ saw_error;
	}

      first = ମିଥ୍ୟା;

      ଯଦି (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  ଯଦି (!nested)
    c_parser_skip_to_pragma_eol (parser);

  ଯଦି (finish_p)
    {
      ଯଦି ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_UNIFORM)) != 0)
	ଫେରନ୍ତୁ c_finish_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      ଯଦି ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	ଫେରନ୍ତୁ c_finish_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      ଫେରନ୍ତୁ c_finish_omp_clauses (clauses, C_ORT_OMP);
    }

  ଫେରନ୍ତୁ clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_structured_block (c_parser *parser, ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ stmt = ଠେଲ_stmt_list ();
  parser->omp_attrs_forbidden_p = ସତ୍ୟ;
  c_parser_statement (parser, if_p);
  ଫେରନ୍ତୁ କାଢ଼_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  ବୃକ୍ଷ stmt, clauses = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ readonly = ମିଥ୍ୟା;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      ଯଦି (token->type == CPP_NAME
	  && !strcmp (IDENTIFIER_POINTER (token->ମୂଲ୍ୟ), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = ସତ୍ୟ;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_ବୃକ୍ଷ);
      parens.skip_until_found_close (parser);
    }

  ଯଦି (readonly)
    ପାଇଁ (ବୃକ୍ଷ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_to_pragma_eol (parser);

  stmt = make_ଗଣ୍ଠି (OACC_CACHE);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
  add_stmt (stmt);

  ଫେରନ୍ତୁ stmt;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_data (location_t loc, c_parser *parser, ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_DATA_CLAUSE_MASK,
				       "#pragma acc data");

  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  stmt = c_finish_oacc_data (loc, clauses, block);

  ଫେରନ୍ତୁ stmt;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_oacc_declare (c_parser *parser)
{
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ clauses, stmt, t, decl;

  ତାର୍କିକ error = ମିଥ୍ୟା;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_MASK,
				       "#pragma acc declare");
  ଯଦି (!clauses)
    {
      error_at (pragma_loc,
		"no valid clauses specified in %<#pragma acc declare%>");
      ଫେରନ୍ତୁ;
    }

  ପାଇଁ (t = clauses; t; t = OMP_CLAUSE_CHAIN (t))
    {
      location_t loc = OMP_CLAUSE_LOCATION (t);
      decl = OMP_CLAUSE_DECL (t);
      ଯଦି (!DECL_P (decl))
	{
	  error_at (loc, "array section in %<#pragma acc declare%>");
	  error = ସତ୍ୟ;
	  ଜାରି;
	}

      ବାଛ (OMP_CLAUSE_MAP_KIND (t))
	{
	ସ୍ଥିତି GOMP_MAP_FIRSTPRIVATE_POINTER:
	ସ୍ଥିତି GOMP_MAP_ALLOC:
	ସ୍ଥିତି GOMP_MAP_TO:
	ସ୍ଥିତି GOMP_MAP_FORCE_DEVICEPTR:
	ସ୍ଥିତି GOMP_MAP_DEVICE_RESIDENT:
	  ଭାଙ୍ଗ;

	ସ୍ଥିତି GOMP_MAP_LINK:
	  ଯଦି (!global_bindings_p ()
	      && (ବୃକ୍ଷ_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = ସତ୍ୟ;
	      ଜାରି;
	    }
	  ଭାଙ୍ଗ;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଯଦି (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = ସତ୍ୟ;
	      ଜାରି;
	    }
	  ଯଦି (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = ସତ୍ୟ;
	      ଜାରି;
	    }
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_PUBLIC (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = ସତ୍ୟ;
	      ଜାରି;
	    }
	  ଭାଙ୍ଗ;
	}

      ଯଦି (!c_check_in_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = ସତ୍ୟ;
	  ଜାରି;
	}

      ଯଦି (lookup_attribute ("omp declare target", DECL_ATTRIBUTES (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_ATTRIBUTES (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = ସତ୍ୟ;
	  ଜାରି;
	}

      ଯଦି (!error)
	{
	  ବୃକ୍ଷ id;

	  ଯଦି (OMP_CLAUSE_MAP_KIND (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  ଅନ୍ୟଥା
	    id = get_identifier ("omp declare target");

	  DECL_ATTRIBUTES (decl)
			   = ବୃକ୍ଷ_cons (id, NULL_ବୃକ୍ଷ, DECL_ATTRIBUTES (decl));

	  ଯଦି (global_bindings_p ())
	    {
	      symtab_ଗଣ୍ଠି *ଗଣ୍ଠି = symtab_ଗଣ୍ଠି::get (decl);
	      ଯଦି (ଗଣ୍ଠି != ଖାଲି)
		{
		  ଗଣ୍ଠି->offloadable = 1;
		  ଯଦି (ENABLE_OFFLOADING)
		    {
		      g->have_offload = ସତ୍ୟ;
		      ଯଦି (is_a <varpool_ଗଣ୍ଠି *> (ଗଣ୍ଠି))
			vec_safe_ଠେଲ (offload_vars, decl);
		    }
		}
	    }
	}
    }

  ଯଦି (error || global_bindings_p ())
    ଫେରନ୍ତୁ;

  stmt = make_ଗଣ୍ଠି (OACC_DECLARE);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, pragma_loc);

  add_stmt (stmt);

  ଫେରନ୍ତୁ;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_oacc_enter_exit_data (c_parser *parser, ତାର୍କିକ enter)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ clauses, stmt;
  ଅଚଳ ଅକ୍ଷର *p = "";

  c_parser_consume_pragma (parser);

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      c_parser_consume_token (parser);
    }

  ଯଦି (strcmp (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = ସତ୍ୟ;
      c_parser_skip_to_pragma_eol (parser);
      ଫେରନ୍ତୁ;
    }

  ଯଦି (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_DATA_CLAUSE_MASK,
					 "#pragma acc enter data");
  ଅନ୍ୟଥା
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_DATA_CLAUSE_MASK,
					 "#pragma acc exit data");

  ଯଦି (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_ବୃକ୍ଷ)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      ଫେରନ୍ତୁ;
    }

  stmt = enter ? make_ଗଣ୍ଠି (OACC_ENTER_DATA) : make_ଗଣ୍ଠି (OACC_EXIT_DATA);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_host_data (location_t loc, c_parser *parser, ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_DATA_CLAUSE_MASK,
				       "#pragma acc host_data", ମିଥ୍ୟା);
  ଯଦି (!omp_find_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  stmt = c_finish_oacc_host_data (loc, clauses, block);
  ଫେରନ୍ତୁ stmt;
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
ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_loop (location_t loc, c_parser *parser, ଅକ୍ଷର *p_name,
		    omp_clause_mask mask, ବୃକ୍ଷ *cclauses, ତାର୍କିକ *if_p)
{
  ତାର୍କିକ is_parallel = ((mask >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  strcat (p_name, " loop");
  mask |= OACC_LOOP_CLAUSE_MASK;

  ବୃକ୍ଷ clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/cclauses == ଖାଲି,
					    /*target=*/is_parallel);
  ଯଦି (cclauses)
    {
      clauses = c_oacc_split_loop_clauses (clauses, cclauses, is_parallel);
      ଯଦି (*cclauses)
	*cclauses = c_finish_omp_clauses (*cclauses, C_ORT_ACC_TARGET);
      ଯଦି (clauses)
	clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
    }

  ବୃକ୍ଷ block = c_begin_compound_stmt (ସତ୍ୟ);
  ବୃକ୍ଷ stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, ଖାଲି,
				     if_p);
  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
  add_stmt (block);

  ଫେରନ୍ତୁ stmt;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ଅଙ୍କ_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ଅଙ୍କ_WORKERS)		\
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ଅଙ୍କ_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ଅଙ୍କ_WORKERS)		\
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       ଗଣନା pragma_kind p_kind, ଅକ୍ଷର *p_name, ତାର୍କିକ *if_p)
{
  omp_clause_mask mask;
  ଗଣନା ବୃକ୍ଷ_code code;
  ବାଛ (p_kind)
    {
    ସ୍ଥିତି PRAGMA_OACC_KERNELS:
      strcat (p_name, " kernels");
      mask = OACC_KERNELS_CLAUSE_MASK;
      code = OACC_KERNELS;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_PARALLEL:
      strcat (p_name, " parallel");
      mask = OACC_PARALLEL_CLAUSE_MASK;
      code = OACC_PARALLEL;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_SERIAL:
      strcat (p_name, " serial");
      mask = OACC_SERIAL_CLAUSE_MASK;
      code = OACC_SERIAL;
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    }

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  ବୃକ୍ଷ block = c_begin_omp_parallel ();
	  ବୃକ୍ଷ clauses;
	  c_parser_oacc_loop (loc, parser, p_name, mask, &clauses, if_p);
	  ଫେରନ୍ତୁ c_finish_omp_construct (loc, code, block, clauses);
	}
    }

  ବୃକ୍ଷ clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/ସତ୍ୟ,
					    /*target=*/ସତ୍ୟ);

  ବୃକ୍ଷ block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  ଫେରନ୍ତୁ c_finish_omp_construct (loc, code, block, clauses);
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_oacc_routine (c_parser *parser, ଗଣନା pragma_context context)
{
  gcc_checking_assert (context == pragma_external);

  oacc_routine_data data;
  data.error_seen = ମିଥ୍ୟା;
  data.fndecl_seen = ମିଥ୍ୟା;
  data.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      ବୃକ୍ଷ decl = NULL_ବୃକ୍ଷ;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      ଯଦି (name_token->type == CPP_NAME
	  && (name_token->id_kind == C_ID_ID
	      || name_token->id_kind == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->ମୂଲ୍ୟ);
	  ଯଦି (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->ମୂଲ୍ୟ);
	  c_parser_consume_token (parser);
	}
      ଅନ୍ୟଥା
	c_parser_error (parser, "expected function name");

      ଯଦି (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	  ଫେରନ୍ତୁ;
	}

      data.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_MASK,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      data.clauses = nreverse (data.clauses);

      ଯଦି (ବୃକ୍ଷ_CODE (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  ଫେରନ୍ତୁ;
	}

      c_finish_oacc_routine (&data, decl, ମିଥ୍ୟା);
    }
  ଅନ୍ୟଥା /* No optional '( name )'.  */
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
      ଯଦି (c_parser_next_token_is (parser, CPP_PRAGMA)
	  || c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (data.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  ଫେରନ୍ତୁ;
	}

      /* We only have to consider the pragma_external case here.  */
      ଯଦି (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ext = disable_extension_diagnostics ();
	  କର
	    c_parser_consume_token (parser);
	  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ମିଥ୍ୟା, ସତ୍ୟ,
					 ମିଥ୍ୟା, ଖାଲି, ଖାଲି, ମିଥ୍ୟା, ଖାଲି, &data);
	  restore_extension_diagnostics (ext);
	}
      ଅନ୍ୟଥା
	c_parser_declaration_or_fndef (parser, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ମିଥ୍ୟା, ସତ୍ୟ,
				       ମିଥ୍ୟା, ଖାଲି, ଖାଲି, ମିଥ୍ୟା, ଖାଲି, &data);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_finish_oacc_routine (ସଂରଚନା oacc_routine_data *data, ବୃକ୍ଷ fndecl,
		       ତାର୍କିକ is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  ଯଦି (data->error_seen
      || fndecl == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ;

  ଯଦି (data->fndecl_seen)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      data->error_seen = ସତ୍ୟ;
      ଫେରନ୍ତୁ;
    }
  ଯଦି (fndecl == NULL_ବୃକ୍ଷ || ବୃକ୍ଷ_CODE (fndecl) != FUNCTION_DECL)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      data->error_seen = ସତ୍ୟ;
      ଫେରନ୍ତୁ;
    }

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା compatible
    = oacc_verify_routine_clauses (fndecl, &data->clauses, data->loc,
				   "#pragma acc routine");
  ଯଦି (compatible < 0)
    {
      data->error_seen = ସତ୍ୟ;
      ଫେରନ୍ତୁ;
    }
  ଯଦି (compatible > 0)
    {
    }
  ଅନ୍ୟଥା
    {
      ଯଦି (ବୃକ୍ଷ_USED (fndecl) || (!is_defn && DECL_SAVED_ବୃକ୍ଷ (fndecl)))
	{
	  error_at (data->loc,
		    ବୃକ୍ଷ_USED (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  data->error_seen = ସତ୍ୟ;
	  ଫେରନ୍ତୁ;
	}

      /* Set the routine's level of parallelism.  */
      ବୃକ୍ଷ dims = oacc_build_routine_dims (data->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_ATTRIBUTES (fndecl)
	= ବୃକ୍ଷ_cons (get_identifier ("omp declare target"),
		     data->clauses, DECL_ATTRIBUTES (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  data->fndecl_seen = ସତ୍ୟ;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_oacc_update (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  ବୃକ୍ଷ clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_MASK,
					    "#pragma acc update");
  ଯଦି (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_ବୃକ୍ଷ)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      ଫେରନ୍ତୁ;
    }

  ଯଦି (parser->error)
    ଫେରନ୍ତୁ;

  ବୃକ୍ଷ stmt = make_ଗଣ୍ଠି (OACC_UPDATE);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#define OACC_WAIT_CLAUSE_MASK						\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF) )

ସ୍ଥିର ବୃକ୍ଷ
c_parser_oacc_wait (location_t loc, c_parser *parser, ଅକ୍ଷର *p_name)
{
  ବୃକ୍ଷ clauses, list = NULL_ବୃକ୍ଷ, stmt = NULL_ବୃକ୍ଷ;

  ଯଦି (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  strcpy (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_MASK, p_name);
  stmt = c_finish_oacc_wait (loc, list, clauses);
  add_stmt (stmt);

  ଫେରନ୍ତୁ stmt;
}

ସଂରଚନା c_omp_loc_ବୃକ୍ଷ
{
  location_t loc;
  ବୃକ୍ଷ var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
ସ୍ଥିର ବୃକ୍ଷ
c_check_omp_allocate_allocator_r (ବୃକ୍ଷ *tp, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ଶୂନ୍ୟ *data)
{
  ବୃକ୍ଷ var = ((ସଂରଚନା c_omp_loc_ବୃକ୍ଷ *) data)->var;
  location_t loc = ((ସଂରଚନା c_omp_loc_ବୃକ୍ଷ *) data)->loc;
  ଯଦି (ବୃକ୍ଷ_CODE (*tp) == VAR_DECL && c_check_in_current_scope (*tp))
    {
      ଯଦି (linemap_location_before_p (ଧାଡ଼ି_table, DECL_SOURCE_LOCATION (var),
				     DECL_SOURCE_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_SOURCE_LOCATION (*tp), "declared here");
	  inform (DECL_SOURCE_LOCATION (var),
		  "to be allocated variable declared here");
	  ଫେରନ୍ତୁ *tp;
	}
      ଅନ୍ୟଥା
	{
	  gcc_assert (cur_stmt_list
		      && ବୃକ୍ଷ_CODE (cur_stmt_list) == STATEMENT_LIST);

	  ବୃକ୍ଷ_stmt_iterator l = tsi_last (cur_stmt_list);
	  ଯେତେବେଳେ (!tsi_end_p (l))
	    {
	      ଯଦି (linemap_location_before_p (ଧାଡ଼ି_table, ପଦସମଷ୍ଟି_LOCATION (*l),
					     DECL_SOURCE_LOCATION (var)))
		  ଭାଙ୍ଗ;
	      ଯଦି (ବୃକ୍ଷ_CODE (*l) == MODIFY_ପଦସମଷ୍ଟି
		  && ବୃକ୍ଷ_OPERAND (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (ପଦସମଷ୍ଟି_LOCATION (*l), "modified here");
		  inform (DECL_SOURCE_LOCATION (var),
			  "to be allocated variable declared here");
		  ଫେରନ୍ତୁ *tp;
		}
	      --l;
	    }
	}
    }
  ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
}

/* OpenMP 5.x:
   # pragma omp allocate (list)  clauses

   OpenMP 5.0 clause:
   allocator (omp_allocator_handle_t expression)

   OpenMP 5.1 additional clause:
   align (constant-expression)]  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_allocate (c_parser *parser)
{
  ବୃକ୍ଷ alignment = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ allocator = NULL_ବୃକ୍ଷ;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  ବୃକ୍ଷ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_ବୃକ୍ଷ);
  କର
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      ଯଦି (!c_parser_next_token_is (parser, CPP_NAME))
	ଭାଙ୍ଗ;
      matching_parens parens;
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      c_parser_consume_token (parser);
      location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      ଯଦି (strcmp ("align", p) != 0 && strcmp ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  ଭାଙ୍ଗ;
	}
      ଯଦି (!parens.require_open (parser))
	ଭାଙ୍ଗ;

      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ମିଥ୍ୟା, ସତ୍ୟ);
      ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
      ଯଦି (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
	;
      ଅନ୍ୟଥା ଯଦି (p[2] == 'i' && alignment)
	{
	  error_at (ପଦସମଷ୍ଟି_loc, "too many %qs clauses", "align");
	  ଭାଙ୍ଗ;
	}
      ଅନ୍ୟଥା ଯଦି (p[2] == 'i')
	{
	  alignment = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
	  ଯଦି (ବୃକ୍ଷ_CODE (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (alignment))
	      || ବୃକ୍ଷ_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (ପଦସମଷ୍ଟି_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_ବୃକ୍ଷ;
	    }
	}
      ଅନ୍ୟଥା ଯଦି (allocator)
	{
	  error_at (ପଦସମଷ୍ଟି_loc, "too many %qs clauses", "allocator");
	  ଭାଙ୍ଗ;
	}
      ଅନ୍ୟଥା
	{
	  allocator = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
	  allocator_loc = ପଦସମଷ୍ଟି_loc;
	  ବୃକ୍ଷ orig_type
	    = ପଦସମଷ୍ଟି.original_type ? ପଦସମଷ୍ଟି.original_type : ବୃକ୍ଷ_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (allocator))
	      || ବୃକ୍ଷ_CODE (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (ପଦସମଷ୍ଟି_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			ବୃକ୍ଷ_TYPE (allocator));
	      allocator = NULL_ବୃକ୍ଷ;
	    }
	}
      parens.skip_until_found_close (parser);
    } ଯେତେବେଳେ (ସତ୍ୟ);
  c_parser_skip_to_pragma_eol (parser);

  c_mark_decl_jump_unsafe_in_current_scope ();
  ପାଇଁ (ବୃକ୍ଷ c = nl; c != NULL_ବୃକ୍ଷ; c = OMP_CLAUSE_CHAIN (c))
    {
      ବୃକ୍ଷ var = OMP_CLAUSE_DECL (c);
      ଯଦି (ବୃକ୍ଷ_CODE (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  ଜାରି;
	}
      ଯଦି (!parser->in_omp_decl_attribute && !c_check_in_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_SOURCE_LOCATION (var), "declared here");
	  ଜାରି;
	}
      ଯଦି (lookup_attribute ("omp allocate", DECL_ATTRIBUTES (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  ଜାରି;
	}
      ଯଦି (ବୃକ୍ଷ_STATIC (var))
	{
	  ଯଦି (allocator == NULL_ବୃକ୍ଷ && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      ଜାରି;
	    }
	  ଅନ୍ୟଥା ଯଦି (allocator
		   && (wi::to_widest (allocator) < 1
		       || wi::to_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::to_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::to_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  ଅନ୍ୟଥା ଯଦି (allocator
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
      ଯଦି (allocator)
	{
	  ସଂରଚନା c_omp_loc_ବୃକ୍ଷ data
	    = {ପଦସମଷ୍ଟି_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_ବୃକ୍ଷ (&allocator, c_check_omp_allocate_allocator_r, &data, ଖାଲି);
	}
      DECL_ATTRIBUTES (var) = ବୃକ୍ଷ_cons (get_identifier ("omp allocate"),
					 build_ବୃକ୍ଷ_list (allocator, alignment),
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_atomic (location_t loc, c_parser *parser, ତାର୍କିକ openacc)
{
  ବୃକ୍ଷ lhs = NULL_ବୃକ୍ଷ, rhs = NULL_ବୃକ୍ଷ, v = NULL_ବୃକ୍ଷ, r = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ lhs1 = NULL_ବୃକ୍ଷ, rhs1 = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ stmt, orig_lhs, unfolded_lhs = NULL_ବୃକ୍ଷ, unfolded_lhs1 = NULL_ବୃକ୍ଷ;
  ଗଣନା ବୃକ୍ଷ_code code = ERROR_MARK, opcode = NOP_ପଦସମଷ୍ଟି;
  ଗଣନା omp_memory_order memory_order = OMP_MEMORY_ORDER_UNSPECIFIED;
  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
  location_t eloc;
  ତାର୍କିକ structured_block = ମିଥ୍ୟା;
  ତାର୍କିକ swapped = ମିଥ୍ୟା;
  ତାର୍କିକ non_lvalue_p;
  ବୃକ୍ଷ clauses = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ capture = ମିଥ୍ୟା;
  ତାର୍କିକ compare = ମିଥ୍ୟା;
  ତାର୍କିକ weak = ମିଥ୍ୟା;
  ଗଣନା omp_memory_order fail = OMP_MEMORY_ORDER_UNSPECIFIED;
  ତାର୍କିକ no_semicolon = ମିଥ୍ୟା;
  ତାର୍କିକ extra_scope = ମିଥ୍ୟା;

  ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ଅଚଳ ଅକ୍ଷର *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  ଗଣନା ବୃକ୍ଷ_code new_code = ERROR_MARK;
	  ଗଣନା omp_memory_order new_memory_order
	    = OMP_MEMORY_ORDER_UNSPECIFIED;
	  ତାର୍କିକ new_capture = ମିଥ୍ୟା;
	  ତାର୍କିକ new_compare = ମିଥ୍ୟା;
	  ତାର୍କିକ new_weak = ମିଥ୍ୟା;
	  ଗଣନା omp_memory_order new_fail = OMP_MEMORY_ORDER_UNSPECIFIED;

	  ଯଦି (!strcmp (p, "read"))
	    new_code = OMP_ATOMIC_READ;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "write"))
	    new_code = NOP_ପଦସମଷ୍ଟି;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "update"))
	    new_code = OMP_ATOMIC;
	  ଅନ୍ୟଥା ଯଦି (openacc && !strcmp (p, "capture"))
	    new_code = OMP_ATOMIC_CAPTURE_NEW;
	  ଅନ୍ୟଥା ଯଦି (openacc)
	    {
	      p = ଖାଲି;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "capture"))
	    new_capture = ସତ୍ୟ;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "compare"))
	    new_compare = ସତ୍ୟ;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "weak"))
	    new_weak = ସତ୍ୟ;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      ଯଦି (!parens.require_open (parser))
		ଜାରି;

	      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
		{
		  ଅଚଳ ଅକ୍ଷର *q
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);

		  ଯଦି (!strcmp (q, "seq_cst"))
		    new_fail = OMP_MEMORY_ORDER_SEQ_CST;
		  ଅନ୍ୟଥା ଯଦି (!strcmp (q, "acquire"))
		    new_fail = OMP_MEMORY_ORDER_ACQUIRE;
		  ଅନ୍ୟଥା ଯଦି (!strcmp (q, "relaxed"))
		    new_fail = OMP_MEMORY_ORDER_RELAXED;
		}

	      ଯଦି (new_fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  ଯଦି (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  ଅନ୍ୟଥା
		    fail = new_fail;
		}
	      ଅନ୍ୟଥା
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_found_close (parser);
	      ଜାରି;
	    }
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "seq_cst"))
	    new_memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "acq_rel"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "release"))
	    new_memory_order = OMP_MEMORY_ORDER_RELEASE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "acquire"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "relaxed"))
	    new_memory_order = OMP_MEMORY_ORDER_RELAXED;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "hint"))
	    {
	      c_parser_consume_token (parser);
	      clauses = c_parser_omp_clause_hint (parser, clauses);
	      ଜାରି;
	    }
	  ଅନ୍ୟଥା
	    {
	      p = ଖାଲି;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "%<capture%>, %<compare%>, %<weak%>, %<fail%>, "
			      "%<seq_cst%>, %<acq_rel%>, %<release%>, "
			      "%<relaxed%> or %<hint%> clause");
	    }
	  ଯଦି (p)
	    {
	      ଯଦି (new_code != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  ଯଦି (openacc
		      && code == OMP_ATOMIC
		      && new_code == OMP_ATOMIC_CAPTURE_NEW)
		    code = new_code;
		  ଅନ୍ୟଥା ଯଦି (code != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  ଅନ୍ୟଥା
		    code = new_code;
		}
	      ଅନ୍ୟଥା ଯଦି (new_memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  ଯଦି (memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  ଅନ୍ୟଥା
		    memory_order = new_memory_order;
		}
	      ଅନ୍ୟଥା ଯଦି (new_capture)
		{
		  ଯଦି (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  ଅନ୍ୟଥା
		    capture = ସତ୍ୟ;
		}
	      ଅନ୍ୟଥା ଯଦି (new_compare)
		{
		  ଯଦି (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  ଅନ୍ୟଥା
		    compare = ସତ୍ୟ;
		}
	      ଅନ୍ୟଥା ଯଦି (new_weak)
		{
		  ଯଦି (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  ଅନ୍ୟଥା
		    weak = ସତ୍ୟ;
		}
	      c_parser_consume_token (parser);
	      ଜାରି;
	    }
	}
      ଭାଙ୍ଗ;
    }
  c_parser_skip_to_pragma_eol (parser);

  ଯଦି (code == ERROR_MARK)
    code = OMP_ATOMIC;
  ଯଦି (capture)
    {
      ଯଦି (code != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      ଅନ୍ୟଥା
	code = OMP_ATOMIC_CAPTURE_NEW;
    }
  ଯଦି (compare && code != OMP_ATOMIC && code != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = ମିଥ୍ୟା;
    }
  ଯଦି (fail != OMP_MEMORY_ORDER_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      fail = OMP_MEMORY_ORDER_UNSPECIFIED;
    }
  ଯଦି (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = ମିଥ୍ୟା;
    }
  ଯଦି (openacc)
    memory_order = OMP_MEMORY_ORDER_RELAXED;
  ଅନ୍ୟଥା ଯଦି (memory_order == OMP_MEMORY_ORDER_UNSPECIFIED)
    {
      omp_requires_mask
	= (ଗଣନା omp_requires) (omp_requires_mask
			       | OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED);
      ବାଛ ((ଗଣନା omp_memory_order)
	      (omp_requires_mask & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER))
	{
	ସ୍ଥିତି OMP_MEMORY_ORDER_UNSPECIFIED:
	ସ୍ଥିତି OMP_MEMORY_ORDER_RELAXED:
	  memory_order = OMP_MEMORY_ORDER_RELAXED;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି OMP_MEMORY_ORDER_SEQ_CST:
	  memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି OMP_MEMORY_ORDER_ACQUIRE:
	  ଯଦି (code == NOP_ପଦସମଷ୍ଟି)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  ଅନ୍ୟଥା
	    memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି OMP_MEMORY_ORDER_RELEASE:
	  ଯଦି (code == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  ଅନ୍ୟଥା
	    memory_order = OMP_MEMORY_ORDER_RELEASE;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି OMP_MEMORY_ORDER_ACQ_REL:
	  ବାଛ (code)
	    {
	    ସ୍ଥିତି OMP_ATOMIC_READ:
	      memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି NOP_ପଦସମଷ୍ଟି: /* atomic write */
	      memory_order = OMP_MEMORY_ORDER_RELEASE;
	      ଭାଙ୍ଗ;
	    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	      memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	      ଭାଙ୍ଗ;
	    }
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  gcc_unreachable ();
	}
    }
  ଅନ୍ୟଥା
    ବାଛ (code)
      {
      ସ୍ଥିତି OMP_ATOMIC_READ:
	ଯଦି (memory_order == OMP_MEMORY_ORDER_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	ଅନ୍ୟଥା ଯଦି (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	ଭାଙ୍ଗ;
      ସ୍ଥିତି NOP_ପଦସମଷ୍ଟି: /* atomic write */
	ଯଦି (memory_order == OMP_MEMORY_ORDER_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	ଅନ୍ୟଥା ଯଦି (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_RELEASE;
	ଭାଙ୍ଗ;
      ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	ଭାଙ୍ଗ;
      }
  ଯଦି (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
    memory_order
      = (ଗଣନା omp_memory_order) (memory_order
				 | (fail << OMP_FAIL_MEMORY_ORDER_SHIFT));

  ବାଛ (code)
    {
    ସ୍ଥିତି OMP_ATOMIC_READ:
    ସ୍ଥିତି NOP_ପଦସମଷ୍ଟି: /* atomic write */
      v = c_parser_cast_expression (parser, ଖାଲି).ମୂଲ୍ୟ;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
      ଯଦି (v == error_mark_ଗଣ୍ଠି)
	ଯାଅ saw_error;
      ଯଦି (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      ଯଦି (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	ଯାଅ saw_error;
      ଯଦି (code == NOP_ପଦସମଷ୍ଟି)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  ପଦସମଷ୍ଟି = c_parser_expression (parser);
	  ପଦସମଷ୍ଟି = default_function_array_read_conversion (eloc, ପଦସମଷ୍ଟି);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  code = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_ବୃକ୍ଷ;
	  rhs = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି);
	  ଯଦି (rhs == error_mark_ଗଣ୍ଠି)
	    ଯାଅ saw_error;
	}
      ଅନ୍ୟଥା
	{
	  lhs = c_parser_cast_expression (parser, ଖାଲି).ମୂଲ୍ୟ;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
	  ଯଦି (lhs == error_mark_ଗଣ୍ଠି)
	    ଯାଅ saw_error;
	  ଯଦି (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      ଯାଅ done;
    ସ୍ଥିତି OMP_ATOMIC_CAPTURE_NEW:
      ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_block = ସତ୍ୟ;
	}
      ଅନ୍ୟଥା ଯଦି (compare
	       && c_parser_next_token_is_keyword (parser, RID_IF))
	ଭାଙ୍ଗ;
      ଅନ୍ୟଥା
	{
	  v = c_parser_cast_expression (parser, ଖାଲି).ମୂଲ୍ୟ;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
	  ଯଦି (v == error_mark_ଗଣ୍ଠି)
	    ଯାଅ saw_error;
	  ଯଦି (non_lvalue_p)
	    v = non_lvalue (v);
	  ଯଦି (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    ଯାଅ saw_error;
	  ଯଦି (compare && c_parser_next_token_is_keyword (parser, RID_IF))
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "expected expression");
	      ଯାଅ saw_error;
	    }
	}
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଭାଙ୍ଗ;
    }

  /* For structured_block case we don't know yet whether
     old or new x should be captured.  */
restart:
  ଯଦି (compare && c_parser_next_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      ଯଦି (!parens.require_open (parser))
	ଯାଅ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି cmp_ପଦସମଷ୍ଟି;
      ଯଦି (r)
	{
	  cmp_ପଦସମଷ୍ଟି = c_parser_cast_expression (parser, ଖାଲି);
	  cmp_ପଦସମଷ୍ଟି = default_function_array_conversion (eloc, cmp_ପଦସମଷ୍ଟି);
	}
      ଅନ୍ୟଥା
	cmp_ପଦସମଷ୍ଟି = c_parser_ଦ୍ୱିମିକ_expression (parser, ଖାଲି, void_list_ଗଣ୍ଠି);
      parens.skip_until_found_close (parser);
      ଯଦି (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
	ଯାଅ saw_error;
      ଯଦି (r)
	{
	  ଯଦି (!c_ବୃକ୍ଷ_equal (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, unfolded_lhs))
	    ଯାଅ bad_if;
	  cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = rhs1;
	  rhs1 = NULL_ବୃକ୍ଷ;
	  gcc_assert (ବୃକ୍ଷ_CODE (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == EQ_ପଦସମଷ୍ଟି);
	}
      ଯଦି (ବୃକ୍ଷ_CODE (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == EQ_ପଦସମଷ୍ଟି)
	;
      ଅନ୍ୟଥା ଯଦି (!structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (ପଦସମଷ୍ଟି_LOC_OR_LOC (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  ଯାଅ saw_error;
	}
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) != GT_ପଦସମଷ୍ଟି
	       && ବୃକ୍ଷ_CODE (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) != LT_ପଦସମଷ୍ଟି)
	{
	  error_at (ପଦସମଷ୍ଟି_LOC_OR_LOC (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  ଯାଅ saw_error;
	}
      ଯଦି (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	ଯାଅ saw_error;

      extra_scope = ସତ୍ୟ;
      eloc = c_parser_peek_token (parser)->location;
      ପଦସମଷ୍ଟି = c_parser_cast_expression (parser, ଖାଲି);
      lhs = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      ପଦସମଷ୍ଟି = default_function_array_conversion (eloc, ପଦସମଷ୍ଟି);
      unfolded_lhs = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      lhs = c_fully_fold (lhs, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
      orig_lhs = lhs;
      ଯଦି (lhs == error_mark_ଗଣ୍ଠି)
	ଯାଅ saw_error;
      ଯଦି (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      ଯଦି (!c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  ଯାଅ saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      rhs1 = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;

      ଯଦି (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ଯାଅ saw_error;

      ଯଦି (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	ଯାଅ saw_error;

      extra_scope = ମିଥ୍ୟା;
      no_semicolon = ସତ୍ୟ;

      ଯଦି (c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, 0), unfolded_lhs))
	{
	  ଯଦି (ବୃକ୍ଷ_CODE (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == EQ_ପଦସମଷ୍ଟି)
	    {
	      opcode = COND_ପଦସମଷ୍ଟି;
	      rhs = c_fully_fold (ବୃକ୍ଷ_OPERAND (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, 1),
				  ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
	      rhs1 = c_fully_fold (rhs1, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
	    }
	  ଅନ୍ୟଥା ଯଦି (c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, 1), rhs1))
	    {
	      opcode = (ବୃକ୍ଷ_CODE (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == GT_ପଦସମଷ୍ଟି
			? MIN_ପଦସମଷ୍ଟି : MAX_ପଦସମଷ୍ଟି);
	      rhs = c_fully_fold (rhs1, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
	      rhs1 = c_fully_fold (ବୃକ୍ଷ_OPERAND (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, 0),
				   ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
	    }
	  ଅନ୍ୟଥା
	    ଯାଅ bad_if;
	}
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == EQ_ପଦସମଷ୍ଟି)
	ଯାଅ bad_if;
      ଅନ୍ୟଥା ଯଦି (c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, 1), unfolded_lhs)
	       && c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, 0), rhs1))
	{
	  opcode = (ବୃକ୍ଷ_CODE (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == GT_ପଦସମଷ୍ଟି
		    ? MAX_ପଦସମଷ୍ଟି : MIN_ପଦସମଷ୍ଟି);
	  rhs = c_fully_fold (rhs1, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
	  rhs1 = c_fully_fold (ବୃକ୍ଷ_OPERAND (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, 1),
			       ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
	}
      ଅନ୍ୟଥା
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  ଯାଅ saw_error;
	}

      ଯଦି (c_parser_next_token_is_keyword (parser, RID_ELSE))
	{
	  ଯଦି (code != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_block && r == NULL_ବୃକ୍ଷ)
	      || ବୃକ୍ଷ_CODE (cmp_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) != EQ_ପଦସମଷ୍ଟି)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      ଯାଅ saw_error;
	    }

	  c_parser_consume_token (parser);

	  ଯଦି (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    ଯାଅ saw_error;

	  extra_scope = ସତ୍ୟ;
	  v = c_parser_cast_expression (parser, ଖାଲି).ମୂଲ୍ୟ;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
	  ଯଦି (v == error_mark_ଗଣ୍ଠି)
	    ଯାଅ saw_error;
	  ଯଦି (non_lvalue_p)
	    v = non_lvalue (v);
	  ଯଦି (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    ଯାଅ saw_error;

	  ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);

	  ଯଦି (!c_ବୃକ୍ଷ_equal (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, unfolded_lhs))
	    ଯାଅ bad_if;

	  ଯଦି (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    ଯାଅ saw_error;

	  ଯଦି (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    ଯାଅ saw_error;

	  extra_scope = ମିଥ୍ୟା;
	  code = OMP_ATOMIC_CAPTURE_OLD;
	  ଯଦି (r == NULL_ବୃକ୍ଷ)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  ଯାଅ saw_error;
	}
      ଅନ୍ୟଥା ଯଦି (code == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_ବୃକ୍ଷ
	       && v == NULL_ବୃକ୍ଷ)
	code = OMP_ATOMIC;
      ଯାଅ stmt_done;
    }
  eloc = c_parser_peek_token (parser)->location;
  ପଦସମଷ୍ଟି = c_parser_cast_expression (parser, ଖାଲି);
  lhs = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
  ପଦସମଷ୍ଟି = default_function_array_conversion (eloc, ପଦସମଷ୍ଟି);
  unfolded_lhs = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
  lhs = c_fully_fold (lhs, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
  orig_lhs = lhs;
  ବାଛ (ବୃକ୍ଷ_CODE (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    ସ୍ଥିତି ERROR_MARK:
    saw_error:
      c_parser_skip_to_end_of_block_or_statement (parser);
      ଯଦି (extra_scope && c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      ଯଦି (structured_block)
	{
	  ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  ଅନ୍ୟଥା ଯଦି (code == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      ଫେରନ୍ତୁ;

    ସ୍ଥିତି POSTINCREMENT_ପଦସମଷ୍ଟି:
      ଯଦି (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    ସ୍ଥିତି PREINCREMENT_ପଦସମଷ୍ଟି:
      lhs = ବୃକ୍ଷ_OPERAND (lhs, 0);
      unfolded_lhs = NULL_ବୃକ୍ଷ;
      opcode = PLUS_ପଦସମଷ୍ଟି;
      rhs = integer_one_ଗଣ୍ଠି;
      ଯଦି (compare)
	ଯାଅ invalid_compare;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି POSTDECREMENT_ପଦସମଷ୍ଟି:
      ଯଦି (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    ସ୍ଥିତି PREDECREMENT_ପଦସମଷ୍ଟି:
      lhs = ବୃକ୍ଷ_OPERAND (lhs, 0);
      unfolded_lhs = NULL_ବୃକ୍ଷ;
      opcode = MINUS_ପଦସମଷ୍ଟି;
      rhs = integer_one_ଗଣ୍ଠି;
      ଯଦି (compare)
	ଯାଅ invalid_compare;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି COMPOUND_ପଦସମଷ୍ଟି:
      ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (lhs, 0)) == SAVE_ପଦସମଷ୍ଟି
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (lhs, 1)) == COMPOUND_ପଦସମଷ୍ଟି
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND (lhs, 1), 0)) == MODIFY_ପଦସମଷ୍ଟି
	  && ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND (lhs, 1), 1) == ବୃକ୍ଷ_OPERAND (lhs, 0)
	  && C_BOOLEAN_TYPE_P (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND
					      (ବୃକ୍ଷ_OPERAND (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND (lhs, 1), 0);
      /* FALLTHRU */
    ସ୍ଥିତି MODIFY_ପଦସମଷ୍ଟି:
      ଯଦି (ବୃକ୍ଷ_CODE (lhs) == MODIFY_ପଦସମଷ୍ଟି
	  && C_BOOLEAN_TYPE_P (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_OPERAND (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  ଯଦି (integer_onep (ବୃକ୍ଷ_OPERAND (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = ବୃକ୍ଷ_OPERAND (lhs, 1);
	      lhs = ବୃକ୍ଷ_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_ବୃକ୍ଷ;
	      opcode = NOP_ପଦସମଷ୍ଟି;
	      ଯଦି (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && ବୃକ୍ଷ_CODE (orig_lhs) == COMPOUND_ପଦସମଷ୍ଟି)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      ଯଦି (compare)
		ଯାଅ invalid_compare;
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (lhs, 1)) == TRUTH_NOT_ପଦସମଷ୍ଟି
	      && ବୃକ୍ଷ_OPERAND (lhs, 0)
		 == ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = ବୃକ୍ଷ_OPERAND (lhs, 1);
	      lhs = ବୃକ୍ଷ_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_ବୃକ୍ଷ;
	      opcode = NOP_ପଦସମଷ୍ଟି;
	      ଯଦି (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && ବୃକ୍ଷ_CODE (orig_lhs) == COMPOUND_ପଦସମଷ୍ଟି)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      ଯଦି (compare)
		ଯାଅ invalid_compare;
	      ଭାଙ୍ଗ;
	    }
	}
      /* FALLTHRU */
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଯଦି (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      ଯଦି (compare && !c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  ଯାଅ saw_error;
	}
      ବାଛ (c_parser_peek_token (parser)->type)
	{
	ସ୍ଥିତି CPP_MULT_EQ:
	  opcode = MULT_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_DIV_EQ:
	  opcode = TRUNC_DIV_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_PLUS_EQ:
	  opcode = PLUS_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_MINUS_EQ:
	  opcode = MINUS_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_LSHIFT_EQ:
	  opcode = LSHIFT_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_RSHIFT_EQ:
	  opcode = RSHIFT_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_AND_EQ:
	  opcode = BIT_AND_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_OR_EQ:
	  opcode = BIT_IOR_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_XOR_EQ:
	  opcode = BIT_XOR_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି, unfolded_lhs);
	  rhs1 = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
	  ବାଛ (ବୃକ୍ଷ_CODE (rhs1))
	    {
	    ସ୍ଥିତି MULT_ପଦସମଷ୍ଟି:
	    ସ୍ଥିତି TRUNC_DIV_ପଦସମଷ୍ଟି:
	    ସ୍ଥିତି RDIV_ପଦସମଷ୍ଟି:
	    ସ୍ଥିତି PLUS_ପଦସମଷ୍ଟି:
	    ସ୍ଥିତି MINUS_ପଦସମଷ୍ଟି:
	    ସ୍ଥିତି LSHIFT_ପଦସମଷ୍ଟି:
	    ସ୍ଥିତି RSHIFT_ପଦସମଷ୍ଟି:
	    ସ୍ଥିତି BIT_AND_ପଦସମଷ୍ଟି:
	    ସ୍ଥିତି BIT_IOR_ପଦସମଷ୍ଟି:
	    ସ୍ଥିତି BIT_XOR_ପଦସମଷ୍ଟି:
	      ଯଦି (compare)
		ଭାଙ୍ଗ;
	      ଯଦି (c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (rhs1, 0), unfolded_lhs))
		{
		  opcode = ବୃକ୍ଷ_CODE (rhs1);
		  rhs = c_fully_fold (ବୃକ୍ଷ_OPERAND (rhs1, 1), ମିଥ୍ୟା, ଖାଲି,
				      ସତ୍ୟ);
		  rhs1 = c_fully_fold (ବୃକ୍ଷ_OPERAND (rhs1, 0), ମିଥ୍ୟା, ଖାଲି,
				       ସତ୍ୟ);
		  ଯାଅ stmt_done;
		}
	      ଯଦି (c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (rhs1, 1), unfolded_lhs))
		{
		  opcode = ବୃକ୍ଷ_CODE (rhs1);
		  rhs = c_fully_fold (ବୃକ୍ଷ_OPERAND (rhs1, 0), ମିଥ୍ୟା, ଖାଲି,
				      ସତ୍ୟ);
		  rhs1 = c_fully_fold (ବୃକ୍ଷ_OPERAND (rhs1, 1), ମିଥ୍ୟା, ଖାଲି,
				       ସତ୍ୟ);
		  swapped = !commutative_ବୃକ୍ଷ_code (opcode);
		  ଯାଅ stmt_done;
		}
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି COND_ପଦସମଷ୍ଟି:
	      ଯଦି (!compare)
		ଭାଙ୍ଗ;
	      ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (rhs1, 0)) != GT_ପଦସମଷ୍ଟି
		  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (rhs1, 0)) != LT_ପଦସମଷ୍ଟି
		  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (rhs1, 0)) != EQ_ପଦସମଷ୍ଟି)
		ଭାଙ୍ଗ;
	      ଯଦି (!ବୃକ୍ଷ_OPERAND (rhs1, 1))
		ଭାଙ୍ଗ;
	      ଯଦି (!c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (rhs1, 2), unfolded_lhs))
		ଭାଙ୍ଗ;
	      ଯଦି (c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND (rhs1, 0), 0),
				unfolded_lhs))
		{
		  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (rhs1, 0)) == EQ_ପଦସମଷ୍ଟି)
		    {
		      opcode = COND_ପଦସମଷ୍ଟି;
		      rhs = c_fully_fold (ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND (rhs1,
								      0), 1),
					  ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
		      rhs1 = c_fully_fold (ବୃକ୍ଷ_OPERAND (rhs1, 1), ମିଥ୍ୟା,
					   ଖାଲି, ସତ୍ୟ);
		      ଯାଅ stmt_done;
		    }
		  ଯଦି (c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND (rhs1, 0), 1),
				    ବୃକ୍ଷ_OPERAND (rhs1, 1)))
		    {
		      opcode = (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (rhs1, 0)) == GT_ପଦସମଷ୍ଟି
				? MIN_ପଦସମଷ୍ଟି : MAX_ପଦସମଷ୍ଟି);
		      rhs = c_fully_fold (ବୃକ୍ଷ_OPERAND (rhs1, 1), ମିଥ୍ୟା, ଖାଲି,
					  ସତ୍ୟ);
		      rhs1 = c_fully_fold (ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND (rhs1,
								       0), 0),
					   ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
		      ଯାଅ stmt_done;
		    }
		}
	      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (rhs1, 0)) == EQ_ପଦସମଷ୍ଟି)
		ଭାଙ୍ଗ;
	      ଅନ୍ୟଥା ଯଦି (c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  ଯଦି (c_ବୃକ୍ଷ_equal (ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND (rhs1, 0), 0),
				    ବୃକ୍ଷ_OPERAND (rhs1, 1)))
		    {
		      opcode = (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_OPERAND (rhs1, 0)) == GT_ପଦସମଷ୍ଟି
				? MAX_ପଦସମଷ୍ଟି : MIN_ପଦସମଷ୍ଟି);
		      rhs = c_fully_fold (ବୃକ୍ଷ_OPERAND (rhs1, 1), ମିଥ୍ୟା, ଖାଲି,
					  ସତ୍ୟ);
		      rhs1 = c_fully_fold (ବୃକ୍ଷ_OPERAND (ବୃକ୍ଷ_OPERAND (rhs1,
								       0), 1),
					   ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
		      ଯାଅ stmt_done;
		    }
		}
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି EQ_ପଦସମଷ୍ଟି:
	      ଯଦି (!compare
		  || code != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_block
		  || v
		  || r)
		ଭାଙ୍ଗ;
	      ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_ବୃକ୍ଷ;
		  c_parser_consume_token (parser);
		  ଯାଅ restart;
		}
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି ERROR_MARK:
	      ଯାଅ saw_error;
	    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (c_parser_peek_token (parser)->type == CPP_SEMICOLON)
	    {
	      ଯଦି (structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
		{
		  code = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_ବୃକ୍ଷ;
		  ପଦସମଷ୍ଟି = default_function_array_read_conversion (eloc, ପଦସମଷ୍ଟି);
		  unfolded_lhs1 = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
		  lhs1 = c_fully_fold (unfolded_lhs1, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
		  rhs1 = NULL_ବୃକ୍ଷ;
		  c_parser_consume_token (parser);
		  ଯାଅ restart;
		}
	      ଯଦି (structured_block && !compare)
		{
		  opcode = NOP_ପଦସମଷ୍ଟି;
		  ପଦସମଷ୍ଟି = default_function_array_read_conversion (eloc, ପଦସମଷ୍ଟି);
		  rhs = c_fully_fold (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
		  rhs1 = NULL_ବୃକ୍ଷ;
		  ଯାଅ stmt_done;
		}
	    }
	  c_parser_error (parser, "invalid form of %<#pragma omp atomic%>");
	  ଯାଅ saw_error;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  c_parser_error (parser,
			  "invalid operator for %<#pragma omp atomic%>");
	  ଯାଅ saw_error;
	}

      /* Arrange to pass the location of the assignment operator to
	 c_finish_omp_atomic.  */
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      ପଦସମଷ୍ଟି = c_parser_expression (parser);
      ପଦସମଷ୍ଟି = default_function_array_read_conversion (eloc, ପଦସମଷ୍ଟି);
      rhs = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      rhs = c_fully_fold (rhs, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
      ଭାଙ୍ଗ;
    }
stmt_done:
  ଯଦି (structured_block && code == OMP_ATOMIC_CAPTURE_NEW && r == NULL_ବୃକ୍ଷ)
    {
      ଯଦି (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ଯାଅ saw_error;
      no_semicolon = ମିଥ୍ୟା;
      v = c_parser_cast_expression (parser, ଖାଲି).ମୂଲ୍ୟ;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
      ଯଦି (v == error_mark_ଗଣ୍ଠି)
	ଯାଅ saw_error;
      ଯଦି (non_lvalue_p)
	v = non_lvalue (v);
      ଯଦି (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	ଯାଅ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      ପଦସମଷ୍ଟି = c_parser_cast_expression (parser, ଖାଲି);
      lhs1 = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      ପଦସମଷ୍ଟି = default_function_array_read_conversion (eloc, ପଦସମଷ୍ଟି);
      unfolded_lhs1 = ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      lhs1 = c_fully_fold (lhs1, ମିଥ୍ୟା, ଖାଲି, ସତ୍ୟ);
      ଯଦି (lhs1 == error_mark_ଗଣ୍ଠି)
	ଯାଅ saw_error;
      ଯଦି (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  ଯଦି (structured_block)
    {
      ଯଦି (!no_semicolon)
	c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
done:
  ଯଦି (weak && opcode != COND_ପଦସମଷ୍ଟି)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = ମିଥ୍ୟା;
    }
  ଯଦି (unfolded_lhs && unfolded_lhs1
      && !c_ବୃକ୍ଷ_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା
    stmt = c_finish_omp_atomic (loc, code, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, memory_order, weak);
  ଯଦି (stmt != error_mark_ଗଣ୍ଠି)
    add_stmt (stmt);

  ଯଦି (!structured_block && !no_semicolon)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}


/* OpenMP 2.5:
   # pragma omp barrier new-line
*/

ସ୍ଥିର ଶୂନ୍ୟ
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_critical (location_t loc, c_parser *parser, ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ stmt, name = NULL_ବୃକ୍ଷ, clauses = NULL_ବୃକ୍ଷ;

  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      ଅନ୍ୟଥା
	c_parser_error (parser, "expected identifier");

      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_MASK,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_block (parser, if_p);
  ଫେରନ୍ତୁ c_finish_omp_critical (loc, stmt, name, clauses);
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_depobj (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    {
      c_parser_skip_to_pragma_eol (parser);
      ଫେରନ୍ତୁ;
    }

  ବୃକ୍ଷ depobj = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି).ମୂଲ୍ୟ;
  ଯଦି (depobj != error_mark_ଗଣ୍ଠି)
    {
      ଯଦି (!lvalue_p (depobj))
	{
	  error_at (ପଦସମଷ୍ଟି_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା
	{
	  ବୃକ୍ଷ addr = build_unary_op (ପଦସମଷ୍ଟି_LOC_OR_LOC (depobj, loc), ADDR_ପଦସମଷ୍ଟି,
				      depobj, ମିଥ୍ୟା);
	  ଯଦି (addr == error_mark_ଗଣ୍ଠି)
	    depobj = error_mark_ଗଣ୍ଠି;
	  ଅନ୍ୟଥା
	    depobj = build_indirect_ref (ପଦସମଷ୍ଟି_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_STAR);
	}
    }

  parens.skip_until_found_close (parser);
  ବୃକ୍ଷ clause = NULL_ବୃକ୍ଷ;
  ଗଣନା omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_INVALID;
  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);

      c_parser_consume_token (parser);
      ଯଦି (!strcmp ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_ବୃକ୍ଷ, c_loc);
	  clause = c_finish_omp_clauses (clause, C_ORT_OMP);
	  ଯଦି (!clause)
	    clause = error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (!strcmp ("destroy", p))
	{
	  matching_parens c_parens;
	  kind = OMP_CLAUSE_DEPEND_LAST;
	  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      ବୃକ୍ଷ destobj = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି).ମୂଲ୍ୟ;
	      ଯଦି (!lvalue_p (destobj))
		error_at (ପଦସମଷ୍ଟି_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      ଅନ୍ୟଥା ଯଦି (depobj != error_mark_ଗଣ୍ଠି
		       && !operand_equal_p (destobj, depobj,
					    OEP_MATCH_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (ପଦସମଷ୍ଟି_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_found_close (parser);
	    }
	}
      ଅନ୍ୟଥା ଯଦି (!strcmp ("update", p))
	{
	  matching_parens c_parens;
	  ଯଦି (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
		{
		  ଅଚଳ ଅକ୍ଷର *p2
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);

		  c_parser_consume_token (parser);
		  ଯଦି (!strcmp ("in", p2))
		    kind = OMP_CLAUSE_DEPEND_IN;
		  ଅନ୍ୟଥା ଯଦି (!strcmp ("out", p2))
		    kind = OMP_CLAUSE_DEPEND_OUT;
		  ଅନ୍ୟଥା ଯଦି (!strcmp ("inout", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUT;
		  ଅନ୍ୟଥା ଯଦି (!strcmp ("mutexinoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  ଅନ୍ୟଥା ଯଦି (!strcmp ("inoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      ଯଦି (kind == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_ଗଣ୍ଠି;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_found_close (parser);
	    }
	  ଅନ୍ୟଥା
	    clause = error_mark_ଗଣ୍ଠି;
	}
    }
  ଯଦି (!clause && kind == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_ଗଣ୍ଠି;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_flush (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  ଗଣନା memmodel mo = MEMMODEL_LAST;
  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);

      ଯଦି (!strcmp (p, "seq_cst"))
	mo = MEMMODEL_SEQ_CST;
      ଅନ୍ୟଥା ଯଦି (!strcmp (p, "acq_rel"))
	mo = MEMMODEL_ACQ_REL;
      ଅନ୍ୟଥା ଯଦି (!strcmp (p, "release"))
	mo = MEMMODEL_RELEASE;
      ଅନ୍ୟଥା ଯଦି (!strcmp (p, "acquire"))
	mo = MEMMODEL_ACQUIRE;
      ଅନ୍ୟଥା
	error_at (c_parser_peek_token (parser)->location,
		  "expected %<seq_cst%>, %<acq_rel%>, %<release%> or "
		  "%<acquire%>");
      c_parser_consume_token (parser);
    }
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      ଯଦି (mo != MEMMODEL_LAST)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ଖାଲି);
    }
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_to_pragma_eol (parser);

  c_finish_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

ସ୍ଥିର ତାର୍କିକ
c_parser_omp_section_scan (c_parser *parser, ଅଚଳ ଅକ୍ଷର *directive,
			   ତାର୍କିକ tentative)
{
  ଯଦି (!c_parser_nth_token_starts_std_attributes (parser, 1))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା n = 3;
  ଯଦି (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  ଯଦି (token->type != CPP_CLOSE_SQUARE)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  ଯଦି (token->type != CPP_CLOSE_SQUARE)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  ଯଦି (n < 9)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  ଯଦି (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      ବୃକ୍ଷ first = c_parser_peek_nth_token_raw (parser, 3)->ମୂଲ୍ୟ;
      ବୃକ୍ଷ second = c_parser_peek_nth_token_raw (parser, 5)->ମୂଲ୍ୟ;
      ଯଦି (strcmp (IDENTIFIER_POINTER (first), "directive")
	  && strcmp (IDENTIFIER_POINTER (first), "__directive__"))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
      ଯଦି (strcmp (IDENTIFIER_POINTER (second), directive))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }
  ଯଦି (tentative)
    ଫେରନ୍ତୁ ସତ୍ୟ;
  location_t first_loc = c_parser_peek_token (parser)->location;
  location_t last_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t ମଧ୍ୟ_loc = UNKNOWN_LOCATION;
  ବୃକ୍ଷ std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  ତାର୍କିକ seen = ମିଥ୍ୟା;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା cnt = 0;
  ପାଇଁ (ବୃକ୍ଷ attr = std_attrs; attr; attr = ବୃକ୍ଷ_CHAIN (attr))
    ଯଦି (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	ପାଇଁ (ବୃକ୍ଷ a = ବୃକ୍ଷ_ମୂଲ୍ୟ (attr); a; a = ବୃକ୍ଷ_CHAIN (a))
	  {
	    ବୃକ୍ଷ d = ବୃକ୍ଷ_ମୂଲ୍ୟ (a);
	    gcc_assert (ବୃକ୍ଷ_CODE (d) == C_TOKEN_VEC);
	    c_token *first = C_TOKEN_VEC_TOKENS (d)->address ();
	    cnt++;
	    ଯଦି (first->type == CPP_NAME
		&& strcmp (IDENTIFIER_POINTER (first->ମୂଲ୍ୟ),
			   directive) == 0)
	      {
		seen = ସତ୍ୟ;
		ଯଦି (ମଧ୍ୟ_loc == UNKNOWN_LOCATION)
		  ମଧ୍ୟ_loc = first->location;
	      }
	  }
      }
  ଯଦି (!seen)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  ଯଦି (cnt != 1 || ବୃକ୍ଷ_CHAIN (std_attrs))
    {
      error_at (make_location (first_loc, last_loc, ମଧ୍ୟ_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }
  c_parser_handle_statement_omp_attributes (parser, std_attrs, ଖାଲି);
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_structured_block_sequence (c_parser *parser,
					ଗଣନା pragma_kind kind)
{
  ବୃକ୍ଷ stmt = ଠେଲ_stmt_list ();
  c_parser_statement (parser, ଖାଲି);
  କର
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	ଭାଙ୍ଗ;
      ଯଦି (c_parser_next_token_is (parser, CPP_EOF))
	ଭାଙ୍ଗ;

      ଯଦି (kind != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_kind == kind)
	ଭାଙ୍ଗ;

      ଯଦି (kind != PRAGMA_NONE
	  && c_parser_omp_section_scan (parser,
					kind == PRAGMA_OMP_SCAN
					? "scan" : "section", ମିଥ୍ୟା))
	ଭାଙ୍ଗ;

      c_parser_statement (parser, ଖାଲି);
    }
  ଯେତେବେଳେ (1);
  ଫେରନ୍ତୁ କାଢ଼_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_scan_loop_body (c_parser *parser, ତାର୍କିକ open_brace_parsed)
{
  ବୃକ୍ଷ substmt;
  location_t loc;
  ବୃକ୍ଷ clauses = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ found_scan = ମିଥ୍ୟା;

  loc = c_parser_peek_token (parser)->location;
  ଯଦି (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = ମିଥ୍ୟା;
      ଫେରନ୍ତୁ;
    }

  ଯଦି (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SCAN)
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_OMP_SCAN);
  ଅନ୍ୟଥା
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_ଗଣ୍ଠି, substmt, NULL_ବୃକ୍ଷ);
  SET_ପଦସମଷ୍ଟି_LOCATION (substmt, loc);
  add_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  ଯଦି (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SCAN)
    {
      ଗଣନା omp_clause_code clause = OMP_CLAUSE_ERROR;
      found_scan = ସତ୍ୟ;

      c_parser_consume_pragma (parser);

      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ଅଚଳ ଅକ୍ଷର *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	  ଯଦି (strcmp (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  ଅନ୍ୟଥା ଯଦି (strcmp (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      ଯଦି (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_ବୃକ୍ଷ);
	}
      ଅନ୍ୟଥା
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_to_pragma_eol (parser);
    }
  ଅନ୍ୟଥା
    error ("expected %<#pragma omp scan%>");

  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  ଯଦି (!c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_NONE);
  ଅନ୍ୟଥା
    {
      ଯଦି (found_scan)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_ଗଣ୍ଠି, substmt, clauses);
  SET_ପଦସମଷ୍ଟି_LOCATION (substmt, loc);
  add_stmt (substmt);

  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
ସ୍ଥିର ତାର୍କିକ
c_parser_omp_next_tokens_can_be_canon_loop (c_parser *parser,
					    ଗଣନା ବୃକ୍ଷ_code code,
					    ତାର୍କିକ error_p)
{
  ଯଦି (code == OACC_LOOP)
    {
      ଯଦି (c_parser_next_token_is_keyword (parser, RID_FOR))
	ଫେରନ୍ତୁ ସତ୍ୟ;
      ଯଦି (error_p)
	c_parser_error (parser, "for statement expected");
    }
  ଅନ୍ୟଥା
    {
      ଯଦି (c_parser_next_token_is_keyword (parser, RID_FOR))
	ଫେରନ୍ତୁ ସତ୍ୟ;

      ଯଦି (c_parser_next_token_is (parser, CPP_PRAGMA))
	ବାଛ (c_parser_peek_token (parser)->pragma_kind)
	  {
	  ସ୍ଥିତି PRAGMA_OMP_UNROLL:
	  ସ୍ଥିତି PRAGMA_OMP_TILE:
	    ଫେରନ୍ତୁ ସତ୍ୟ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    ଭାଙ୍ଗ;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      size_t n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      ଯଦି (token->type == CPP_NAME
	  && C_IS_RESERVED_WORD (token->ମୂଲ୍ୟ)
	  && C_RID_CODE (token->ମୂଲ୍ୟ) == RID_FOR)
	ଫେରନ୍ତୁ ସତ୍ୟ;
      ଯଦି (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

ସ୍ଥିର ବୃକ୍ଷ c_parser_omp_tile (location_t, c_parser *, ତାର୍କିକ *);
ସ୍ଥିର ବୃକ୍ଷ c_parser_omp_unroll (location_t, c_parser *, ତାର୍କିକ *);

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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_loop_nest (c_parser *parser, ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ decl = NULL_ବୃକ୍ଷ, cond = NULL_ବୃକ୍ଷ, incr = NULL_ବୃକ୍ଷ, init = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ body = NULL_ବୃକ୍ଷ;
  matching_parens parens;
  ତାର୍କିକ moreloops;
  unsigned ଅକ୍ଷର save_in_statement;
  ବୃକ୍ଷ loop_scope;
  location_t loc;
  ସଂରଚନା omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth = omp_for_parse_state->depth;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  ଯଦି (c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      ବୃକ୍ଷ std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_attributes (parser, std_attrs, ଖାଲି);
      ଯଦି (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  ଯଦି (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      ବୃକ୍ଷ transform = NULL_ବୃକ୍ଷ, sizes, body = NULL_ବୃକ୍ଷ;
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2 = 0;
      ବାଛ (c_parser_peek_token (parser)->pragma_kind)
	{
	ସ୍ଥିତି PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = ଠେଲ_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = କାଢ଼_stmt_list (body);
	  ଯଦି (transform == NULL_ବୃକ୍ଷ || transform == error_mark_ଗଣ୍ଠି)
	    {
	      transform = error_mark_ଗଣ୍ଠି;
	      ଭାଙ୍ଗ;
	    }
	  gcc_assert (ବୃକ୍ଷ_CODE (transform) == OMP_UNROLL);
	  ଯଦି (omp_find_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      ଯଦି (omp_for_parse_state->ଗଣନା_2 - depth > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->ଗଣନା_2 - depth);
		  transform = error_mark_ଗଣ୍ଠି;
		}
	      ଅନ୍ୟଥା
		ଗଣନା_2 = 1;
	    }
	  ଅନ୍ୟଥା
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_ଗଣ୍ଠି;
	    }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = ଠେଲ_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = କାଢ଼_stmt_list (body);
	  ଯଦି (transform == NULL_ବୃକ୍ଷ || transform == error_mark_ଗଣ୍ଠି)
	    {
	      transform = error_mark_ଗଣ୍ଠି;
	      ଭାଙ୍ଗ;
	    }
	  gcc_assert (ବୃକ୍ଷ_CODE (transform) == OMP_TILE);
	  sizes = omp_find_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  ଗଣନା_2 = list_length (OMP_CLAUSE_SIZES_LIST (sizes));
	  ଯଦି (depth + ଗଣନା_2 < omp_for_parse_state->ଗଣନା_2)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			ଗଣନା_2, omp_for_parse_state->ଗଣନା_2 - depth);
	      transform = error_mark_ଗଣ୍ଠି;
	    }
	  ଭାଙ୍ଗ;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  c_parser_pragma (parser, pragma_stmt, ଖାଲି, void_list_ଗଣ୍ଠି);
	  ଭାଙ୍ଗ;
	}
      ଯଦି (transform == NULL_ବୃକ୍ଷ)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      ଯଦି (transform == NULL_ବୃକ୍ଷ || transform == error_mark_ଗଣ୍ଠି)
	{
	  omp_for_parse_state->fail = ସତ୍ୟ;
	  ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
	}
      ପାଇଁ (ଗଣନା_2 = omp_for_parse_state->ଗଣନା_2; depth < ଗଣନା_2; ++depth)
	{
	  ବୃକ୍ଷ_VEC_ELT (omp_for_parse_state->declv, depth) = NULL_ବୃକ୍ଷ;
	  ବୃକ୍ଷ_VEC_ELT (omp_for_parse_state->initv, depth) = NULL_ବୃକ୍ଷ;
	  ବୃକ୍ଷ_VEC_ELT (omp_for_parse_state->condv, depth) = NULL_ବୃକ୍ଷ;
	  ବୃକ୍ଷ_VEC_ELT (omp_for_parse_state->incrv, depth) = NULL_ବୃକ୍ଷ;
	}
      omp_for_parse_state->want_nested_loop = ମିଥ୍ୟା;
      ଫେରନ୍ତୁ body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_in_statement = in_statement;
  in_statement = IN_OMP_BLOCK;

  /* We are not in intervening code now.  */
  omp_for_parse_state->in_intervening_code = ମିଥ୍ୟା;

  ଯଦି (!parens.require_open (parser))
    {
      omp_for_parse_state->fail = ସତ୍ୟ;
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (ସତ୍ୟ);

  /* Parse the initialization declaration or expression.  */
  ଯଦି (c_parser_next_tokens_start_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      ବୃକ୍ଷ this_pre_body = ଠେଲ_stmt_list ();
      c_in_omp_for = ସତ୍ୟ;
      c_parser_declaration_or_fndef (parser, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ,
				     ମିଥ୍ୟା);
      c_in_omp_for = ମିଥ୍ୟା;
      this_pre_body = କାଢ଼_stmt_list (this_pre_body);
      append_to_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      ଯଦି (decl == ଖାଲି)
	ଯାଅ error_init;
      ଯଦି (DECL_INITIAL (decl) == error_mark_ଗଣ୍ଠି)
	decl = error_mark_ଗଣ୍ଠି;
      init = decl;
    }
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      ସଂରଚନା c_ପଦସମଷ୍ଟି decl_exp;
      ସଂରଚନା c_ପଦସମଷ୍ଟି init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_expression (parser);
      decl = decl_exp.ମୂଲ୍ୟ;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_in_omp_for = ସତ୍ୟ;
      init = build_modify_ପଦସମଷ୍ଟି (init_loc, decl, decl_exp.original_type,
				NOP_ପଦସମଷ୍ଟି, init_loc, init_exp.ମୂଲ୍ୟ,
				init_exp.original_type);
      c_in_omp_for = ମିଥ୍ୟା;
      init = c_process_ପଦସମଷ୍ଟି_stmt (init_loc, init);

      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  ଅନ୍ୟଥା
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->fail = ସତ୍ୟ;
      ଯାଅ parse_next;
    }

  /* Parse the loop condition.  */
  ଯଦି (c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_in_omp_for = ସତ୍ୟ;
      ସଂରଚନା c_ପଦସମଷ୍ଟି cond_ପଦସମଷ୍ଟି
	= c_parser_ଦ୍ୱିମିକ_expression (parser, ଖାଲି, NULL_ବୃକ୍ଷ);
      c_in_omp_for = ମିଥ୍ୟା;

      cond = cond_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      ବାଛ (cond_ପଦସମଷ୍ଟି.original_code)
	{
	ସ୍ଥିତି GT_ପଦସମଷ୍ଟି:
	ସ୍ଥିତି GE_ପଦସମଷ୍ଟି:
	ସ୍ଥିତି LT_ପଦସମଷ୍ଟି:
	ସ୍ଥିତି LE_ପଦସମଷ୍ଟି:
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି NE_ପଦସମଷ୍ଟି:
	  ଯଦି (omp_for_parse_state->code != OACC_LOOP)
	    ଭାଙ୍ଗ;
	  /* FALLTHRU.  */
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_ପଦସମଷ୍ଟି, boolean_type_ଗଣ୍ଠି, error_mark_ଗଣ୍ଠି);
	  ଭାଙ୍ଗ;
	}
      protected_set_ପଦସମଷ୍ଟି_location (cond, cond_loc);
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  ଯଦି (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_ପଦସମଷ୍ଟି_stmt (incr_loc,
				  c_parser_expression (parser).ମୂଲ୍ୟ);
    }
  parens.skip_until_found_close (parser);

  ଯଦି (decl == ଖାଲି || decl == error_mark_ଗଣ୍ଠି || init == error_mark_ଗଣ୍ଠି)
    omp_for_parse_state->fail = ସତ୍ୟ;
  ଅନ୍ୟଥା
    {
      ବୃକ୍ଷ_VEC_ELT (omp_for_parse_state->declv, depth) = decl;
      ବୃକ୍ଷ_VEC_ELT (omp_for_parse_state->initv, depth) = init;
      ବୃକ୍ଷ_VEC_ELT (omp_for_parse_state->condv, depth) = cond;
      ବୃକ୍ଷ_VEC_ELT (omp_for_parse_state->incrv, depth) = incr;
    }

parse_next:
  moreloops = depth < omp_for_parse_state->ଗଣନା_2 - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  ଯଦି (moreloops
      && c_parser_omp_next_tokens_can_be_canon_loop (parser,
						     omp_for_parse_state->code,
						     ମିଥ୍ୟା))
    {
      omp_for_parse_state->depth++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->depth--;
    }
  ଅନ୍ୟଥା ଯଦି (moreloops && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* This is the open brace in the loop-body grammar production.  Rather
	 than trying to special-case braces, just parse it as a compound
	 statement and handle the nested loop-body case there.  Note that
	 when we see a further open brace inside the compound statement
	 loop-body, we don't know whether it is the start of intervening
	 code that is a compound statement, or a level of braces
	 surrounding a nested loop-body.  Use the WANT_NESTED_LOOP state
	 bit to ensure we have only one nested loop at each level.  */
      omp_for_parse_state->in_intervening_code = ସତ୍ୟ;
      body = c_parser_compound_statement (parser, ଖାଲି);
      omp_for_parse_state->in_intervening_code = ମିଥ୍ୟା;
      ଯଦି (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = ସତ୍ୟ;
	}
      if_p = ଖାଲି;
    }
  ଅନ୍ୟଥା
    {
      /* This is the final-loop-body case in the grammar: we have
	 something that is not a FOR and not an open brace.  */
      ଯଦି (moreloops)
	{
	  /* If we were expecting a nested loop, give an error and mark
	     that parsing has failed, and try to recover by parsing the
	     body as regular code without further collapsing.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = ସତ୍ୟ;
	}
      in_statement = IN_OMP_FOR;
      parser->omp_for_parse_state = ଖାଲି;
      body = ଠେଲ_stmt_list ();
      ଯଦି (omp_for_parse_state->inscan)
	c_parser_omp_scan_loop_body (parser, ମିଥ୍ୟା);
      ଅନ୍ୟଥା
	add_stmt (c_parser_c99_block_statement (parser, if_p));
      body = କାଢ଼_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  in_statement = save_in_statement;
  omp_for_parse_state->want_nested_loop = ମିଥ୍ୟା;
  omp_for_parse_state->in_intervening_code = ସତ୍ୟ;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  ଯଦି (body)
    add_stmt (body);
  body = c_end_compound_stmt (loc, loop_scope, ସତ୍ୟ);
  ଯଦି (decl && ବୃକ୍ଷ_CODE (body) == BIND_ପଦସମଷ୍ଟି)
    {
      ବୃକ୍ଷ t = BIND_ପଦସମଷ୍ଟି_VARS (body);
      ବୃକ୍ଷ prev = NULL_ବୃକ୍ଷ, next = NULL_ବୃକ୍ଷ;
      ଯେତେବେଳେ (t)
	{
	  next = DECL_CHAIN (t);
	  ଯଦି (t == decl)
	    {
	      ଯଦି (prev)
		DECL_CHAIN (prev) = next;
	      ଅନ୍ୟଥା
		{
		  BIND_ପଦସମଷ୍ଟି_VARS (body) = next;
		  BLOCK_VARS (BIND_ପଦସମଷ୍ଟି_BLOCK (body)) = next;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା
	    {
	      prev = t;
	      t = next;
	    }
	}
      ଯଦି (BIND_ପଦସମଷ୍ଟି_VARS (body) == NULL_ବୃକ୍ଷ)
	body = BIND_ପଦସମଷ୍ଟି_BODY (body);
    }

  ଫେରନ୍ତୁ body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_for_loop (location_t loc, c_parser *parser, ଗଣନା ବୃକ୍ଷ_code code,
		       ବୃକ୍ଷ clauses, ବୃକ୍ଷ *cclauses, ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ body, stmt, cl;
  ବୃକ୍ଷ ret = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ ordered_cl = NULL_ବୃକ୍ଷ;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, collapse = 1, ordered = 0, ଗଣନା_2;
  ତାର୍କିକ oacc_tiling = ମିଥ୍ୟା;
  ତାର୍କିକ inscan = ମିଥ୍ୟା;
  ସଂରଚନା omp_for_parse_data data;
  ସଂରଚନା omp_for_parse_data *save_data = parser->omp_for_parse_state;

  ପାଇଁ (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    ଯଦି (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = ବୃକ୍ଷ_to_shwi (OMP_CLAUSE_COLLAPSE_ପଦସମଷ୍ଟି (cl));
    ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = ସତ୍ୟ;
	collapse = list_length (OMP_CLAUSE_TILE_LIST (cl));
      }
    ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_SIZES)
      collapse = list_length (OMP_CLAUSE_SIZES_LIST (cl));
    ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_ପଦସମଷ୍ଟି (cl))
      {
	ordered_cl = cl;
	ordered = ବୃକ୍ଷ_to_shwi (OMP_CLAUSE_ORDERED_ପଦସମଷ୍ଟି (cl));
      }
    ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (code == OMP_SIMD || code == OMP_FOR))
      inscan = ସତ୍ୟ;

  ଯଦି (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_ପଦସମଷ୍ଟି (ordered_cl)
	= build_int_cst (integer_type_ଗଣ୍ଠି, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  ଗଣନା_2 = ordered ? ordered : collapse;

  ଯଦି (!c_parser_omp_next_tokens_can_be_canon_loop (parser, code, ସତ୍ୟ))
    ଫେରନ୍ତୁ ଖାଲି;

  /* Initialize parse state for recursive descent.  */
  data.declv = make_ବୃକ୍ଷ_vec (ଗଣନା_2);
  data.initv = make_ବୃକ୍ଷ_vec (ଗଣନା_2);
  data.condv = make_ବୃକ୍ଷ_vec (ଗଣନା_2);
  data.incrv = make_ବୃକ୍ଷ_vec (ଗଣନା_2);
  data.pre_body = NULL_ବୃକ୍ଷ;
  data.bindings = NULL_ବୃକ୍ଷ;
  data.for_loc = c_parser_peek_token (parser)->location;
  data.ଗଣନା_2 = ଗଣନା_2;
  data.depth = 0;
  data.want_nested_loop = ସତ୍ୟ;
  data.ordered = ordered > 0;
  data.in_intervening_code = ମିଥ୍ୟା;
  data.perfect_nesting_fail = ମିଥ୍ୟା;
  data.fail = ମିଥ୍ୟା;
  data.inscan = inscan;
  data.saw_intervening_code = ମିଥ୍ୟା;
  data.code = code;
  parser->omp_for_parse_state = &data;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  ପାଇଁ (ବୃକ୍ଷ t = data.bindings; t; )
    {
      ବୃକ୍ଷ n = ବୃକ୍ଷ_CHAIN (t);
      ବୃକ୍ଷ_CHAIN (t) = NULL_ବୃକ୍ଷ;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  ଯଦି (!data.fail)
    {
      c_in_omp_for = ସତ୍ୟ;
      stmt = c_finish_omp_for (loc, code, data.declv, ଖାଲି, data.initv,
			       data.condv, data.incrv,
			       body, data.pre_body, ସତ୍ୟ);
      c_in_omp_for = ମିଥ୍ୟା;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      ଯଦି (stmt && !c_omp_check_loop_iv (stmt, data.declv, ଖାଲି))
	stmt = NULL_ବୃକ୍ଷ;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      ଯଦି (data.saw_intervening_code
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, ଖାଲି))
	stmt = NULL_ବୃକ୍ଷ;

      ଯଦି (stmt)
	{
	  add_stmt (stmt);

	  ପାଇଁ (i = 0; i < ବୃକ୍ଷ_VEC_LENGTH (OMP_FOR_INIT (stmt)); i++)
	    {
	      ବୃକ୍ଷ init = ବୃକ୍ଷ_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      ଯଦି (init == NULL_ବୃକ୍ଷ)
		ଭାଙ୍ଗ;
	      gcc_assert (ବୃକ୍ଷ_CODE (init) == MODIFY_ପଦସମଷ୍ଟି);
	      ବୃକ୍ଷ decl = ବୃକ୍ଷ_OPERAND (init, 0);
	      ବୃକ୍ଷ cond = ବୃକ୍ଷ_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (ବୃକ୍ଷ_OPERAND (cond, 0) == decl);

	      ବୃକ୍ଷ op0 = ବୃକ୍ଷ_OPERAND (init, 1);
	      ଯଦି (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || ବୃକ୍ଷ_CODE (op0) != ବୃକ୍ଷ_VEC)
		ବୃକ୍ଷ_OPERAND (init, 1) = c_fully_fold (op0, ମିଥ୍ୟା, ଖାଲି);
	      ଅନ୍ୟଥା
		{
		  ବୃକ୍ଷ_VEC_ELT (op0, 1)
		    = c_fully_fold (ବୃକ୍ଷ_VEC_ELT (op0, 1), ମିଥ୍ୟା, ଖାଲି);
		  ବୃକ୍ଷ_VEC_ELT (op0, 2)
		    = c_fully_fold (ବୃକ୍ଷ_VEC_ELT (op0, 2), ମିଥ୍ୟା, ଖାଲି);
		}

	      ବୃକ୍ଷ op1 = ବୃକ୍ଷ_OPERAND (cond, 1);
	      ଯଦି (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || ବୃକ୍ଷ_CODE (op1) != ବୃକ୍ଷ_VEC)
		ବୃକ୍ଷ_OPERAND (cond, 1) = c_fully_fold (op1, ମିଥ୍ୟା, ଖାଲି);
	      ଅନ୍ୟଥା
		{
		  ବୃକ୍ଷ_VEC_ELT (op1, 1)
		    = c_fully_fold (ବୃକ୍ଷ_VEC_ELT (op1, 1), ମିଥ୍ୟା, ଖାଲି);
		  ବୃକ୍ଷ_VEC_ELT (op1, 2)
		    = c_fully_fold (ବୃକ୍ଷ_VEC_ELT (op1, 2), ମିଥ୍ୟା, ଖାଲି);
		}
	    }

	  ଯଦି (cclauses != ଖାଲି
	      && cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL] != ଖାଲି)
	    {
	      ବୃକ୍ଷ *c;
	      ପାଇଁ (c = &cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL]; *c ; )
		ଯଦି (OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		ଅନ୍ୟଥା
		  {
		    ପାଇଁ (i = 0; i < ଗଣନା_2; i++)
		      ଯଦି (ବୃକ୍ଷ_VEC_ELT (data.declv, i) == OMP_CLAUSE_DECL (*c))
			ଭାଙ୍ଗ;
		    ଯଦି (i == ଗଣନା_2)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (*c) == OMP_CLAUSE_FIRSTPRIVATE)
		      {
			error_at (loc,
				  "iteration variable %qD should not be firstprivate",
				  OMP_CLAUSE_DECL (*c));
			*c = OMP_CLAUSE_CHAIN (*c);
		      }
		    ଅନ୍ୟଥା
		      {
			/* Move lastprivate (decl) clause to
			   OMP_FOR_CLAUSES.  */
			ବୃକ୍ଷ l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			ଯଦି (code == OMP_SIMD)
			  {
			    OMP_CLAUSE_CHAIN (l)
			      = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
			    cclauses[C_OMP_CLAUSE_SPLIT_FOR] = l;
			  }
			ଅନ୍ୟଥା
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
  ଫେରନ୍ତୁ ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

ସ୍ଥିର ଶୂନ୍ୟ
omp_split_clauses (location_t loc, ଗଣନା ବୃକ୍ଷ_code code,
		   omp_clause_mask mask, ବୃକ୍ଷ clauses, ବୃକ୍ଷ *cclauses)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
  c_omp_split_clauses (loc, code, mask, clauses, cclauses);
  ପାଇଁ (i = 0; i < C_OMP_CLAUSE_SPLIT_ଗଣନା; i++)
    ଯଦି (cclauses[i])
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_loop (location_t loc, c_parser *parser,
		   ଅକ୍ଷର *p_name, omp_clause_mask mask, ବୃକ୍ଷ *cclauses,
		   ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ block, clauses, ret;

  strcat (p_name, " loop");
  mask |= OMP_LOOP_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ଖାଲି);
  ଯଦି (cclauses)
    {
      omp_split_clauses (loc, OMP_LOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_LOOP];
    }

  block = c_begin_compound_stmt (ସତ୍ୟ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
  add_stmt (block);

  ଫେରନ୍ତୁ ret;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_simd (location_t loc, c_parser *parser,
		   ଅକ୍ଷର *p_name, omp_clause_mask mask, ବୃକ୍ଷ *cclauses,
		   ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ block, clauses, ret;

  strcat (p_name, " simd");
  mask |= OMP_SIMD_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ଖାଲି);
  ଯଦି (cclauses)
    {
      omp_split_clauses (loc, OMP_SIMD, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SIMD];
    }

  block = c_begin_compound_stmt (ସତ୍ୟ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
  add_stmt (block);

  ଫେରନ୍ତୁ ret;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_for (location_t loc, c_parser *parser,
		  ଅକ୍ଷର *p_name, omp_clause_mask mask, ବୃକ୍ଷ *cclauses,
		  ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ block, clauses, ret;

  strcat (p_name, " for");
  mask |= OMP_FOR_CLAUSE_MASK;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  ଯଦି (cclauses && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  ଯଦି ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);

      ଯଦି (strcmp (p, "simd") == 0)
	{
	  ବୃକ୍ଷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ଗଣନା];
	  ଯଦି (cclauses == ଖାଲି)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	    ଫେରନ୍ତୁ c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (ସତ୍ୟ);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
	  ଯଦି (ret == NULL_ବୃକ୍ଷ)
	    ଫେରନ୍ତୁ ret;
	  ret = make_ଗଣ୍ଠି (OMP_FOR);
	  ବୃକ୍ଷ_TYPE (ret) = void_type_ଗଣ୍ଠି;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
	  SET_ପଦସମଷ୍ଟି_LOCATION (ret, loc);
	  add_stmt (ret);
	  ଫେରନ୍ତୁ ret;
	}
    }
  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  ଯଦି ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINEAR);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ଖାଲି);
  ଯଦି (cclauses)
    {
      omp_split_clauses (loc, OMP_FOR, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
    }

  block = c_begin_compound_stmt (ସତ୍ୟ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
  add_stmt (block);

  ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ବୃକ୍ଷ c_parser_omp_taskloop (location_t, c_parser *, ଅକ୍ଷର *,
				   omp_clause_mask, ବୃକ୍ଷ *, ତାର୍କିକ *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_master (location_t loc, c_parser *parser,
		     ଅକ୍ଷର *p_name, omp_clause_mask mask, ବୃକ୍ଷ *cclauses,
		     ତାର୍କିକ *if_p, location_t master_loc)
{
  ବୃକ୍ଷ block, clauses, ret;
  gcc_rich_location richloc (loc);
  ଯଦି (master_loc != UNKNOWN_LOCATION)
    richloc.add_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  strcat (p_name, " master");

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);

      ଯଦି (strcmp (p, "taskloop") == 0)
	{
	  ବୃକ୍ଷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ଗଣନା];
	  ଯଦି (cclauses == ଖାଲି)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	    ଫେରନ୍ତୁ c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (ସତ୍ୟ);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
	  ଯଦି (ret == NULL_ବୃକ୍ଷ)
	    ଫେରନ୍ତୁ ret;
	  ret = c_finish_omp_master (loc, block);
	  OMP_MASTER_COMBINED (ret) = 1;
	  ଫେରନ୍ତୁ ret;
	}
    }
  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }

  ଯଦି (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, mask, p_name, ମିଥ୍ୟା);
      omp_split_clauses (loc, OMP_MASTER, mask, clauses, cclauses);
    }
  ଅନ୍ୟଥା
    c_parser_skip_to_pragma_eol (parser);

  ଫେରନ୍ତୁ c_finish_omp_master (loc, c_parser_omp_structured_block (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#define OMP_MASKED_CLAUSE_MASK					\
	(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FILTER)

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_masked (location_t loc, c_parser *parser,
		     ଅକ୍ଷର *p_name, omp_clause_mask mask, ବୃକ୍ଷ *cclauses,
		     ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ block, clauses, ret;

  strcat (p_name, " masked");
  mask |= OMP_MASKED_CLAUSE_MASK;

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);

      ଯଦି (strcmp (p, "taskloop") == 0)
	{
	  ବୃକ୍ଷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ଗଣନା];
	  ଯଦି (cclauses == ଖାଲି)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	    ଫେରନ୍ତୁ c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (ସତ୍ୟ);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
	  ଯଦି (ret == NULL_ବୃକ୍ଷ)
	    ଫେରନ୍ତୁ ret;
	  ret = c_finish_omp_masked (loc, block,
				     cclauses[C_OMP_CLAUSE_SPLIT_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  ଫେରନ୍ତୁ ret;
	}
    }
  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ଖାଲି);
  ଯଦି (cclauses)
    {
      omp_split_clauses (loc, OMP_MASKED, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_MASKED];
    }

  ଫେରନ୍ତୁ c_finish_omp_masked (loc, c_parser_omp_structured_block (parser,
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_interop (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  ବୃକ୍ଷ clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_MASK,
					   "#pragma omp interop");
  ବୃକ୍ଷ stmt = make_ଗଣ୍ଠି (OMP_INTEROP);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
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

ସ୍ଥିର ତାର୍କିକ
c_parser_omp_ordered (c_parser *parser, ଗଣନା pragma_context context,
		      ତାର୍କିକ *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  ଯଦି (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା n = 1;
  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
    n = 2;

  ଯଦି (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      ଅଚଳ ଅକ୍ଷର *p
	= IDENTIFIER_POINTER (c_parser_peek_nth_token (parser, n)->ମୂଲ୍ୟ);

      ଯଦି (!strcmp ("depend", p) || !strcmp ("doacross", p))
	{
	  ଯଦି (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;
	    }
	  ଯଦି (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	      ଫେରନ୍ତୁ ସତ୍ୟ;
	    }

	  ବୃକ୍ଷ clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_MASK,
					"#pragma omp ordered");
	  c_finish_omp_ordered (loc, clauses, NULL_ବୃକ୍ଷ);
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
    }

  ବୃକ୍ଷ clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_MASK,
					   "#pragma omp ordered");

  ଯଦି (!flag_openmp	/* flag_openmp_simd  */
      && omp_find_clause (clauses, OMP_CLAUSE_SIMD) == NULL_ବୃକ୍ଷ)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  c_finish_omp_ordered (loc, clauses,
			c_parser_omp_structured_block (parser, if_p));
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  ବୃକ୍ଷ stmt, substmt;
  ତାର୍କିକ error_suppress = ମିଥ୍ୟା;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  ଯଦି (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = ମିଥ୍ୟା;
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }

  stmt = ଠେଲ_stmt_list ();

  ଯଦି (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_scan (parser, "section", ସତ୍ୟ))
    {
      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_ଗଣ୍ଠି, substmt);
      SET_ପଦସମଷ୍ଟି_LOCATION (substmt, loc);
      add_stmt (substmt);
    }

  ଯେତେବେଳେ (1)
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	ଭାଙ୍ଗ;
      ଯଦି (c_parser_next_token_is (parser, CPP_EOF))
	ଭାଙ୍ଗ;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_scan (parser, "section", ମିଥ୍ୟା);
      ଯଦି (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser);
	  error_suppress = ମିଥ୍ୟା;
	}
      ଅନ୍ୟଥା ଯଦି (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = ସତ୍ୟ;
	}

      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_ଗଣ୍ଠି, substmt);
      SET_ପଦସମଷ୍ଟି_LOCATION (substmt, loc);
      add_stmt (substmt);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = କାଢ଼_stmt_list (stmt);

  stmt = make_ଗଣ୍ଠି (OMP_SECTIONS);
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, sections_loc);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OMP_SECTIONS_BODY (stmt) = substmt;

  ଫେରନ୍ତୁ add_stmt (stmt);
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_sections (location_t loc, c_parser *parser,
		       ଅକ୍ଷର *p_name, omp_clause_mask mask, ବୃକ୍ଷ *cclauses)
{
  ବୃକ୍ଷ block, clauses, ret;

  strcat (p_name, " sections");
  mask |= OMP_SECTIONS_CLAUSE_MASK;
  ଯଦି (cclauses)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ଖାଲି);
  ଯଦି (cclauses)
    {
      omp_split_clauses (loc, OMP_SECTIONS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SECTIONS];
    }

  block = c_begin_compound_stmt (ସତ୍ୟ);
  ret = c_parser_omp_sections_scope (loc, parser);
  ଯଦି (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
  add_stmt (block);

  ଫେରନ୍ତୁ ret;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ଅଙ୍କ_THREADS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       ଅକ୍ଷର *p_name, omp_clause_mask mask, ବୃକ୍ଷ *cclauses,
		       ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ stmt, clauses, block;

  strcat (p_name, " parallel");
  mask |= OMP_PARALLEL_CLAUSE_MASK;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  ଯଦି ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  ଯଦି (c_parser_next_token_is_keyword (parser, RID_FOR))
    {
      ବୃକ୍ଷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ଗଣନା];
      ଯଦି (cclauses == ଖାଲି)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	ଫେରନ୍ତୁ c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      block = c_begin_omp_parallel ();
      ବୃକ୍ଷ ret = c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      stmt
	= c_finish_omp_parallel (loc, cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				 block);
      ଯଦି (ret == NULL_ବୃକ୍ଷ)
	ଫେରନ୍ତୁ ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      ଫେରନ୍ତୁ stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  ଅନ୍ୟଥା ଯଦି (cclauses
	   && (mask & (OMP_CLAUSE_MASK_1
		       << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_to_pragma_eol (parser);
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      location_t ploc = c_parser_peek_token (parser)->location;
      ଯଦି (cclauses == ଖାଲି && strcmp (p, "masked") == 0)
	{
	  ବୃକ୍ଷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ଗଣନା];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	    ଫେରନ୍ତୁ c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					if_p);
	  block = c_begin_omp_parallel ();
	  ବୃକ୍ଷ ret = c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					  if_p);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  ଯଦି (ret == ଖାଲି)
	    ଫେରନ୍ତୁ ret;
	  /* masked does have just filter clause, but during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel masked don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel masked
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel masked taskloop simd lastprivate (x)  */
	  ଯଦି (OMP_MASKED_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  ଫେରନ୍ତୁ stmt;
	}
      ଅନ୍ୟଥା ଯଦି (cclauses == ଖାଲି && strcmp (p, "master") == 0)
	{
	  ବୃକ୍ଷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ଗଣନା];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	    ଫେରନ୍ତୁ c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					if_p, ploc);
	  block = c_begin_omp_parallel ();
	  ବୃକ୍ଷ ret = c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					  if_p, ploc);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  ଯଦି (ret == ଖାଲି)
	    ଫେରନ୍ତୁ ret;
	  /* master doesn't have any clauses and during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel master don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel master
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel master taskloop simd lastprivate (x)  */
	  ଯଦି (OMP_MASTER_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  ଫେରନ୍ତୁ stmt;
	}
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "loop") == 0)
	{
	  ବୃକ୍ଷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ଗଣନା];
	  ଯଦି (cclauses == ଖାଲି)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	    ଫେରନ୍ତୁ c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  ବୃକ୍ଷ ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
					if_p);
	  stmt
	    = c_finish_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				     block);
	  ଯଦି (ret == NULL_ବୃକ୍ଷ)
	    ଫେରନ୍ତୁ ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  ଫେରନ୍ତୁ stmt;
	}
      ଅନ୍ୟଥା ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	  ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
	}
      ଅନ୍ୟଥା ଯଦି (cclauses == ଖାଲି && strcmp (p, "sections") == 0)
	{
	  ବୃକ୍ଷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ଗଣନା];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  block = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, mask, cclauses);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  ଫେରନ୍ତୁ stmt;
	}
    }
  ଅନ୍ୟଥା ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ଖାଲି);
  ଯଦି (cclauses)
    {
      omp_split_clauses (loc, OMP_PARALLEL, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL];
    }

  block = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = ସତ୍ୟ;
  c_parser_statement (parser, if_p);
  stmt = c_finish_omp_parallel (loc, clauses, block);

  ଫେରନ୍ତୁ stmt;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_single (location_t loc, c_parser *parser, ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ stmt = make_ଗଣ୍ଠି (OMP_SINGLE);
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_MASK,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  ଫେରନ୍ତୁ add_stmt (stmt);
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_scope (location_t loc, c_parser *parser, ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ stmt = make_ଗଣ୍ଠି (OMP_SCOPE);
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_MASK,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  ଫେରନ୍ତୁ add_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_dispatch_body (c_parser *parser)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି lhs, rhs, ret;
  location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_expression (parser, ଖାଲି, ଖାଲି);
  ଯଦି (ବୃକ୍ଷ_CODE (lhs.ମୂଲ୍ୟ) == CALL_ପଦସମଷ୍ଟି)
    ଫେରନ୍ତୁ lhs.ମୂଲ୍ୟ;

  location_t op_location = c_parser_peek_token (parser)->location;
  ଯଦି (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  /* Parse function name.  */
  ଯଦି (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
  c_parser_consume_token (parser);
  ଯଦି (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  rhs.ମୂଲ୍ୟ = build_external_ref (ପଦସମଷ୍ଟି_loc, id, ସତ୍ୟ, &rhs.original_type);
  set_c_ପଦସମଷ୍ଟି_source_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_expression_after_primary (
    parser, ପଦସମଷ୍ଟି_LOC_OR_LOC (rhs.ମୂଲ୍ୟ, ପଦସମଷ୍ଟି_loc), rhs);
  ଯଦି (ବୃକ୍ଷ_CODE (rhs.ମୂଲ୍ୟ) != CALL_ପଦସମଷ୍ଟି)
    {
      error_at (ପଦସମଷ୍ଟି_LOC_OR_LOC (rhs.ମୂଲ୍ୟ, ପଦସମଷ୍ଟି_loc),
		"expected target-function call");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  /* Build assignment. */
  rhs = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, rhs, ସତ୍ୟ, ସତ୍ୟ);
  ret.ମୂଲ୍ୟ
    = build_modify_ପଦସମଷ୍ଟି (op_location, lhs.ମୂଲ୍ୟ, lhs.original_type, NOP_ପଦସମଷ୍ଟି,
			 ପଦସମଷ୍ଟି_loc, rhs.ମୂଲ୍ୟ, rhs.original_type);
  ret.m_decimal = 0;
  set_c_ପଦସମଷ୍ଟି_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  ret.original_code = MODIFY_ପଦସମଷ୍ଟି;
  ret.original_type = ଖାଲି;
  ଫେରନ୍ତୁ ret.ମୂଲ୍ୟ;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  ବୃକ୍ଷ stmt = make_ଗଣ୍ଠି (OMP_DISPATCH);
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_MASK,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  ବୃକ୍ଷ depend_clauses = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ *depend_clauses_ptr = &depend_clauses;
  ପାଇଁ (ବୃକ୍ଷ c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  ଯଦି (depend_clauses != NULL_ବୃକ୍ଷ)
    {
      ବୃକ୍ଷ stmt = make_ଗଣ୍ଠି (OMP_TASK);
      ବୃକ୍ଷ_TYPE (stmt) = void_ଗଣ୍ଠି;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_ବୃକ୍ଷ;
      SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
      add_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ dispatch_body = c_parser_omp_dispatch_body (parser);
  ଯଦି (dispatch_body == error_mark_ଗଣ୍ଠି)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_to_end_of_block_or_statement (parser);
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (ବୃକ୍ଷ_CODE (dispatch_body) == CALL_ପଦସମଷ୍ଟି
	      || ବୃକ୍ଷ_CODE (dispatch_body) == MODIFY_ପଦସମଷ୍ଟି);
  ବୃକ୍ଷ *dispatch_call = ବୃକ୍ଷ_CODE (dispatch_body) == MODIFY_ପଦସମଷ୍ଟି
			  ? &ବୃକ୍ଷ_OPERAND (dispatch_body, 1)
			  : &dispatch_body;
  ଯେତେବେଳେ (ବୃକ୍ଷ_CODE (*dispatch_call) == FLOAT_ପଦସମଷ୍ଟି
	 || ବୃକ୍ଷ_CODE (*dispatch_call) == CONVERT_ପଦସମଷ୍ଟି
	 || ବୃକ୍ଷ_CODE (*dispatch_call) == NOP_ପଦସମଷ୍ଟି)
    dispatch_call = &ବୃକ୍ଷ_OPERAND (*dispatch_call, 0);
  *dispatch_call = build_call_ପଦସମଷ୍ଟି_internal_loc (
    loc, IFN_GOMP_DISPATCH,
    ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (CALL_ପଦସମଷ୍ଟି_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  ଫେରନ୍ତୁ add_stmt (stmt);
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_task (location_t loc, c_parser *parser, ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ clauses, block;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_MASK,
				      "#pragma omp task");

  block = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = ସତ୍ୟ;
  c_parser_statement (parser, if_p);
  ଫେରନ୍ତୁ c_finish_omp_task (loc, clauses, block);
}

/* OpenMP 3.0:
   # pragma omp taskwait new-line

   OpenMP 5.0:
   # pragma omp taskwait taskwait-clause[optseq] new-line
*/

#define OMP_TASKWAIT_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_taskwait (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  ବୃକ୍ଷ clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_MASK,
				"#pragma omp taskwait");

  ଯଦି (clauses)
    {
      ବୃକ୍ଷ stmt = make_ଗଣ୍ଠି (OMP_TASK);
      ବୃକ୍ଷ_TYPE (stmt) = void_ଗଣ୍ଠି;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_ବୃକ୍ଷ;
      SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
      add_stmt (stmt);
    }
  ଅନ୍ୟଥା
    c_finish_omp_taskwait (loc);
}

/* OpenMP 3.1:
   # pragma omp taskyield new-line
*/

ସ୍ଥିର ଶୂନ୍ୟ
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_taskgroup (location_t loc, c_parser *parser, ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_MASK,
					   "#pragma omp taskgroup");

  ବୃକ୍ଷ body = c_parser_omp_structured_block (parser, if_p);
  ଫେରନ୍ତୁ c_finish_omp_taskgroup (loc, body, clauses);
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);
  ବୃକ୍ଷ clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_MASK,
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

ସ୍ଥିର ତାର୍କିକ
c_parser_omp_cancellation_point (c_parser *parser, ଗଣନା pragma_context context)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ clauses;
  ତାର୍କିକ point_seen = ମିଥ୍ୟା;

  c_parser_consume_pragma (parser);
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  point_seen = ସତ୍ୟ;
	}
    }
  ଯଦି (!point_seen)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_to_pragma_eol (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

  ଯଦି (context != pragma_compound)
    {
      ଯଦି (context == pragma_stmt)
	error_at (loc,
		  "%<#pragma %s%> may only be used in compound statements",
		  "omp cancellation point");
      ଅନ୍ୟଥା
	c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_POINT_CLAUSE_MASK,
				"#pragma omp cancellation point");

  c_finish_omp_cancellation_point (loc, clauses);
  ଫେରନ୍ତୁ ସତ୍ୟ;
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 ଅକ୍ଷର *p_name, omp_clause_mask mask, ବୃକ୍ଷ *cclauses,
			 ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ clauses, block, ret;

  strcat (p_name, " distribute");
  mask |= OMP_DISTRIBUTE_CLAUSE_MASK;

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ତାର୍କିକ simd = ମିଥ୍ୟା;
      ତାର୍କିକ parallel = ମିଥ୍ୟା;

      ଯଦି (strcmp (p, "simd") == 0)
	simd = ସତ୍ୟ;
      ଅନ୍ୟଥା
	parallel = strcmp (p, "parallel") == 0;
      ଯଦି (parallel || simd)
	{
	  ବୃକ୍ଷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ଗଣନା];
	  ଯଦି (cclauses == ଖାଲି)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      ଯଦି (simd)
		ଫେରନ୍ତୁ c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
					  if_p);
	      ଅନ୍ୟଥା
		ଫେରନ୍ତୁ c_parser_omp_parallel (loc, parser, p_name, mask,
					      cclauses, if_p);
	    }
	  block = c_begin_compound_stmt (ସତ୍ୟ);
	  ଯଦି (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				     if_p);
	  ଅନ୍ୟଥା
	    ret = c_parser_omp_parallel (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
	  ଯଦି (ret == ଖାଲି)
	    ଫେରନ୍ତୁ ret;
	  ret = make_ଗଣ୍ଠି (OMP_DISTRIBUTE);
	  ବୃକ୍ଷ_TYPE (ret) = void_type_ଗଣ୍ଠି;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
	  SET_ପଦସମଷ୍ଟି_LOCATION (ret, loc);
	  add_stmt (ret);
	  ଫେରନ୍ତୁ ret;
	}
    }
  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ଖାଲି);
  ଯଦି (cclauses)
    {
      omp_split_clauses (loc, OMP_DISTRIBUTE, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
    }

  block = c_begin_compound_stmt (ସତ୍ୟ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, ଖାଲି,
			       if_p);
  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
  add_stmt (block);

  ଫେରନ୍ତୁ ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#define OMP_TEAMS_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ଅଙ୍କ_TEAMS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_THREAD_LIMIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_teams (location_t loc, c_parser *parser,
		    ଅକ୍ଷର *p_name, omp_clause_mask mask, ବୃକ୍ଷ *cclauses,
		    ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ clauses, block, ret;

  strcat (p_name, " teams");
  mask |= OMP_TEAMS_CLAUSE_MASK;

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "distribute") == 0)
	{
	  ବୃକ୍ଷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ଗଣନା];
	  ଯଦି (cclauses == ଖାଲି)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	    ଫେରନ୍ତୁ c_parser_omp_distribute (loc, parser, p_name, mask,
					    cclauses, if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
	  ଯଦି (ret == ଖାଲି)
	    ଫେରନ୍ତୁ ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_ଗଣ୍ଠି (OMP_TEAMS);
	  ବୃକ୍ଷ_TYPE (ret) = void_type_ଗଣ୍ଠି;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_ପଦସମଷ୍ଟି_LOCATION (ret, loc);
	  ଫେରନ୍ତୁ add_stmt (ret);
	}
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "loop") == 0)
	{
	  ବୃକ୍ଷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ଗଣନା];
	  ଯଦି (cclauses == ଖାଲି)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	    ଫେରନ୍ତୁ c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
	  ଯଦି (ret == ଖାଲି)
	    ଫେରନ୍ତୁ ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_ଗଣ୍ଠି (OMP_TEAMS);
	  ବୃକ୍ଷ_TYPE (ret) = void_type_ଗଣ୍ଠି;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_ପଦସମଷ୍ଟି_LOCATION (ret, loc);
	  ଫେରନ୍ତୁ add_stmt (ret);
	}
    }
  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ଖାଲି);
  ଯଦି (cclauses)
    {
      omp_split_clauses (loc, OMP_TEAMS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
    }

  ବୃକ୍ଷ stmt = make_ଗଣ୍ଠି (OMP_TEAMS);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_end_compound_stmt (loc, block, ସତ୍ୟ);
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);

  ଫେରନ୍ତୁ add_stmt (stmt);
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_target_data (location_t loc, c_parser *parser, ତାର୍କିକ *if_p)
{
  ଯଦି (flag_openmp)
    omp_requires_mask
      = (ଗଣନା omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  ବୃକ୍ଷ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_DATA_CLAUSE_MASK,
				"#pragma omp target data", ମିଥ୍ୟା);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, ମିଥ୍ୟା);
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା map_seen = 0;
  ପାଇଁ (ବୃକ୍ଷ *pc = &clauses; *pc;)
    {
      ଯଦି (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	ବାଛ (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  ସ୍ଥିତି GOMP_MAP_TO:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_TO:
	  ସ୍ଥିତି GOMP_MAP_PRESENT_TO:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_PRESENT_TO:
	  ସ୍ଥିତି GOMP_MAP_FROM:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_FROM:
	  ସ୍ଥିତି GOMP_MAP_PRESENT_FROM:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_PRESENT_FROM:
	  ସ୍ଥିତି GOMP_MAP_TOFROM:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_TOFROM:
	  ସ୍ଥିତି GOMP_MAP_PRESENT_TOFROM:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  ସ୍ଥିତି GOMP_MAP_ALLOC:
	  ସ୍ଥିତି GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି GOMP_MAP_FIRSTPRIVATE_POINTER:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_POINTER:
	  ସ୍ଥିତି GOMP_MAP_ATTACH_DETACH:
	  ସ୍ଥିତି GOMP_MAP_ATTACH:
	    ଭାଙ୍ଗ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ଜାରି;
	  }
      ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_seen = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  ଯଦି (map_seen != 3)
    {
      ଯଦି (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }

  ବୃକ୍ଷ stmt = make_ଗଣ୍ଠି (OMP_TARGET_DATA);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OMP_TARGET_DATA_CLAUSES (stmt) = clauses;
  keep_next_level ();
  ବୃକ୍ଷ block = c_begin_compound_stmt (ସତ୍ୟ);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TARGET_DATA_BODY (stmt) = c_end_compound_stmt (loc, block, ସତ୍ୟ);

  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
  ଫେରନ୍ତୁ add_stmt (stmt);
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

ସ୍ଥିର ତାର୍କିକ
c_parser_omp_target_update (location_t loc, c_parser *parser,
			    ଗଣନା pragma_context context)
{
  ଯଦି (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }

  ବୃକ୍ଷ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_UPDATE_CLAUSE_MASK,
				"#pragma omp target update",
				/* finish_p = */ ମିଥ୍ୟା);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  ଯଦି (omp_find_clause (clauses, OMP_CLAUSE_TO) == NULL_ବୃକ୍ଷ
      && omp_find_clause (clauses, OMP_CLAUSE_FROM) == NULL_ବୃକ୍ଷ)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

  ଯଦି (flag_openmp)
    omp_requires_mask
      = (ଗଣନା omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  ବୃକ୍ଷ stmt = make_ଗଣ୍ଠି (OMP_TARGET_UPDATE);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OMP_TARGET_UPDATE_CLAUSES (stmt) = clauses;
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
  add_stmt (stmt);
  ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* OpenMP 4.5:
   # pragma omp target enter data target-data-clause[optseq] new-line  */

#define OMP_TARGET_ENTER_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ସ୍ଥିର ତାର୍କିକ
c_parser_omp_target_enter_data (location_t loc, c_parser *parser,
				ଗଣନା pragma_context context)
{
  ତାର୍କିକ data_seen = ମିଥ୍ୟା;
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = ସତ୍ୟ;
	}
    }
  ଯଦି (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

  ଯଦି (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }

  ଯଦି (flag_openmp)
    omp_requires_mask
      = (ଗଣନା omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  ବୃକ୍ଷ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_ENTER_DATA_CLAUSE_MASK,
				"#pragma omp target enter data", ମିଥ୍ୟା);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, ମିଥ୍ୟା);
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା map_seen = 0;
  ପାଇଁ (ବୃକ୍ଷ *pc = &clauses; *pc;)
    {
      ଯଦି (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	ବାଛ (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  ସ୍ଥିତି GOMP_MAP_TO:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_TO:
	  ସ୍ଥିତି GOMP_MAP_PRESENT_TO:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_PRESENT_TO:
	  ସ୍ଥିତି GOMP_MAP_ALLOC:
	  ସ୍ଥିତି GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_TO);
	    map_seen = 3;
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_TO);
	    map_seen = 3;
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_TO);
	    map_seen = 3;
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_TO);
	    map_seen = 3;
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି GOMP_MAP_FIRSTPRIVATE_POINTER:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_POINTER:
	  ସ୍ଥିତି GOMP_MAP_ATTACH_DETACH:
	  ସ୍ଥିତି GOMP_MAP_ATTACH:
	    ଭାଙ୍ଗ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ଜାରି;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  ଯଦି (map_seen != 3)
    {
      ଯଦି (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }

  ବୃକ୍ଷ stmt = make_ଗଣ୍ଠି (OMP_TARGET_ENTER_DATA);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OMP_TARGET_ENTER_DATA_CLAUSES (stmt) = clauses;
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
  add_stmt (stmt);
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* OpenMP 4.5:
   # pragma omp target exit data target-data-clause[optseq] new-line  */

#define OMP_TARGET_EXIT_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ସ୍ଥିର ତାର୍କିକ
c_parser_omp_target_exit_data (location_t loc, c_parser *parser,
			       ଗଣନା pragma_context context)
{
  ତାର୍କିକ data_seen = ମିଥ୍ୟା;
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = ସତ୍ୟ;
	}
    }
  ଯଦି (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

  ଯଦି (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }

  ଯଦି (flag_openmp)
    omp_requires_mask
      = (ଗଣନା omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  ବୃକ୍ଷ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_EXIT_DATA_CLAUSE_MASK,
				"#pragma omp target exit data", ମିଥ୍ୟା);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_DATA);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_EXIT_DATA);
  c_omp_adjust_map_clauses (clauses, ମିଥ୍ୟା);
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା map_seen = 0;
  ପାଇଁ (ବୃକ୍ଷ *pc = &clauses; *pc;)
    {
      ଯଦି (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	ବାଛ (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  ସ୍ଥିତି GOMP_MAP_FROM:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_FROM:
	  ସ୍ଥିତି GOMP_MAP_PRESENT_FROM:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_PRESENT_FROM:
	  ସ୍ଥିତି GOMP_MAP_RELEASE:
	  ସ୍ଥିତି GOMP_MAP_DELETE:
	    map_seen = 3;
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_FROM);
	    map_seen = 3;
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_seen = 3;
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_FROM);
	    map_seen = 3;
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_seen = 3;
	    ଭାଙ୍ଗ;
	  ସ୍ଥିତି GOMP_MAP_FIRSTPRIVATE_POINTER:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_POINTER:
	  ସ୍ଥିତି GOMP_MAP_ATTACH_DETACH:
	  ସ୍ଥିତି GOMP_MAP_DETACH:
	    ଭାଙ୍ଗ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target exit data%> with map-type other "
		      "than %<from%>, %<tofrom%>, %<release%> or %<delete%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ଜାରି;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  ଯଦି (map_seen != 3)
    {
      ଯଦି (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }

  ବୃକ୍ଷ stmt = make_ଗଣ୍ଠି (OMP_TARGET_EXIT_DATA);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
  OMP_TARGET_EXIT_DATA_CLAUSES (stmt) = clauses;
  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
  add_stmt (stmt);
  ଫେରନ୍ତୁ ସତ୍ୟ;
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

ସ୍ଥିର ତାର୍କିକ
c_parser_omp_target (c_parser *parser, ଗଣନା pragma_context context, ତାର୍କିକ *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  ବୃକ୍ଷ *pc = ଖାଲି, stmt, block, body, clauses;

  ଯଦି (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

  ଯଦି (flag_openmp)
    omp_requires_mask
      = (ଗଣନା omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଗଣନା ବୃକ୍ଷ_code ccode = ERROR_MARK;

      ଯଦି (strcmp (p, "teams") == 0)
	ccode = OMP_TEAMS;
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "simd") == 0)
	ccode = OMP_SIMD;
      ଯଦି (ccode != ERROR_MARK)
	{
	  ବୃକ୍ଷ cclauses[C_OMP_CLAUSE_SPLIT_ଗଣନା];
	  ଅକ୍ଷର p_name[ଆକାର ("#pragma omp target teams distribute "
			      "parallel for simd")];

	  c_parser_consume_token (parser);
	  strcpy (p_name, "#pragma omp target");
	  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      ବୃକ୍ଷ stmt;
	      ବାଛ (ccode)
		{
		ସ୍ଥିତି OMP_TEAMS:
		  stmt = c_parser_omp_teams (loc, parser, p_name,
					     OMP_TARGET_CLAUSE_MASK,
					     cclauses, if_p);
		  ଭାଙ୍ଗ;
		ସ୍ଥିତି OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_TARGET_CLAUSE_MASK,
						cclauses, if_p);
		  ଭାଙ୍ଗ;
		ସ୍ଥିତି OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_TARGET_CLAUSE_MASK,
					    cclauses, if_p);
		  ଭାଙ୍ଗ;
		ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		  gcc_unreachable ();
		}
	      ଫେରନ୍ତୁ stmt != NULL_ବୃକ୍ଷ;
	    }
	  keep_next_level ();
	  ବୃକ୍ଷ block = c_begin_compound_stmt (ସତ୍ୟ), ret;
	  ବାଛ (ccode)
	    {
	    ସ୍ଥିତି OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_TARGET_CLAUSE_MASK, cclauses,
					if_p);
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_TARGET_CLAUSE_MASK, cclauses,
					   if_p);
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_TARGET_CLAUSE_MASK, cclauses,
				       if_p);
	      ଭାଙ୍ଗ;
	    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	      gcc_unreachable ();
	    }
	  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
	  ଯଦି (ret == NULL_ବୃକ୍ଷ)
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	  ଯଦି (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    ପାଇଁ (ବୃକ୍ଷ c = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ଅଙ୍କ_TEAMS
		  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_THREAD_LIMIT)
		ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0;
		     i <= (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ଅଙ୍କ_TEAMS); ++i)
		  ଯଦି (OMP_CLAUSE_OPERAND (c, i)
		      && ବୃକ୍ଷ_CODE (OMP_CLAUSE_OPERAND (c, i)) != INTEGER_CST)
		    {
		      ବୃକ୍ଷ ପଦସମଷ୍ଟି = OMP_CLAUSE_OPERAND (c, i);
		      ବୃକ୍ଷ tmp = create_tmp_var_raw (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି));
		      ପଦସମଷ୍ଟି = build4 (TARGET_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), tmp,
				     ପଦସମଷ୍ଟି, NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ);
		      add_stmt (ପଦସମଷ୍ଟି);
		      OMP_CLAUSE_OPERAND (c, i) = ପଦସମଷ୍ଟି;
		      ବୃକ୍ଷ tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
		      cclauses[C_OMP_CLAUSE_SPLIT_TARGET] = tc;
		    }
	  ବୃକ୍ଷ stmt = make_ଗଣ୍ଠି (OMP_TARGET);
	  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;
	  OMP_TARGET_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
	  c_omp_adjust_map_clauses (OMP_TARGET_CLAUSES (stmt), ସତ୍ୟ);
	  OMP_TARGET_BODY (stmt) = block;
	  OMP_TARGET_COMBINED (stmt) = 1;
	  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
	  add_stmt (stmt);
	  pc = &OMP_TARGET_CLAUSES (stmt);
	  ଯାଅ check_clauses;
	}
      ଅନ୍ୟଥା ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_target_data (loc, parser, if_p);
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	}
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  ଫେରନ୍ତୁ c_parser_omp_target_enter_data (loc, parser, context);
	}
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  ଫେରନ୍ତୁ c_parser_omp_target_exit_data (loc, parser, context);
	}
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  ଫେରନ୍ତୁ c_parser_omp_target_update (loc, parser, context);
	}
    }
  ଯଦି (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

  stmt = make_ଗଣ୍ଠି (OMP_TARGET);
  ବୃକ୍ଷ_TYPE (stmt) = void_type_ଗଣ୍ଠି;

  clauses = c_parser_omp_all_clauses (parser, OMP_TARGET_CLAUSE_MASK,
				      "#pragma omp target", ମିଥ୍ୟା);
  ପାଇଁ (ବୃକ୍ଷ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
      {
	ବୃକ୍ଷ nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_SET_MAP_KIND (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_TARGET);
  clauses  = c_finish_omp_clauses (clauses, C_ORT_OMP_TARGET);
  c_omp_adjust_map_clauses (clauses, ସତ୍ୟ);

  keep_next_level ();
  block = c_begin_compound_stmt (ସତ୍ୟ);
  body = c_parser_omp_structured_block (parser, if_p);

  c_omp_scan_mapper_bindings (loc, &clauses, body);

  add_stmt (body);
  OMP_TARGET_CLAUSES (stmt) = clauses;
  pc = &OMP_TARGET_CLAUSES (stmt);
  OMP_TARGET_BODY (stmt) = c_end_compound_stmt (loc, block, ସତ୍ୟ);

  SET_ପଦସମଷ୍ଟି_LOCATION (stmt, loc);
  add_stmt (stmt);

check_clauses:
  ଯେତେବେଳେ (*pc)
    {
      ଯଦି (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	ବାଛ (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  ସ୍ଥିତି GOMP_MAP_TO:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_TO:
	  ସ୍ଥିତି GOMP_MAP_PRESENT_TO:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_PRESENT_TO:
	  ସ୍ଥିତି GOMP_MAP_FROM:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_FROM:
	  ସ୍ଥିତି GOMP_MAP_PRESENT_FROM:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_PRESENT_FROM:
	  ସ୍ଥିତି GOMP_MAP_TOFROM:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_TOFROM:
	  ସ୍ଥିତି GOMP_MAP_PRESENT_TOFROM:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  ସ୍ଥିତି GOMP_MAP_ALLOC:
	  ସ୍ଥିତି GOMP_MAP_PRESENT_ALLOC:
	  ସ୍ଥିତି GOMP_MAP_FIRSTPRIVATE_POINTER:
	  ସ୍ଥିତି GOMP_MAP_ALWAYS_POINTER:
	  ସ୍ଥିତି GOMP_MAP_POINTER:
	  ସ୍ଥିତି GOMP_MAP_ATTACH_DETACH:
	  ସ୍ଥିତି GOMP_MAP_ATTACH:
	    ଭାଙ୍ଗ;
	  ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ଜାରି;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }
  cfun->has_omp_target = ସତ୍ୟ;
  ଫେରନ୍ତୁ ସତ୍ୟ;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_declare_simd (c_parser *parser, ଗଣନା pragma_context context)
{
  c_token *token = c_parser_peek_token (parser);
  gcc_assert (token->type == CPP_NAME);
  ବୃକ୍ଷ kind = token->ମୂଲ୍ୟ;
  gcc_assert (strcmp (IDENTIFIER_POINTER (kind), "simd") == 0
	      || strcmp (IDENTIFIER_POINTER (kind), "variant") == 0);

  auto_vec<c_token> clauses;
  ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      ଯଦି (token->type == CPP_EOF)
	{
	  c_parser_skip_to_pragma_eol (parser);
	  ଫେରନ୍ତୁ;
	}
      clauses.safe_ଠେଲ (*token);
      c_parser_consume_token (parser);
    }
  clauses.safe_ଠେଲ (*c_parser_peek_token (parser));
  c_parser_skip_to_pragma_eol (parser);

  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      ଯଦି (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->ମୂଲ୍ୟ != kind)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_POINTER (kind), IDENTIFIER_POINTER (kind));
	  ଫେରନ୍ତୁ;
	}
      c_parser_consume_pragma (parser);
      ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  ଯଦି (token->type == CPP_EOF)
	    {
	      c_parser_skip_to_pragma_eol (parser);
	      ଫେରନ୍ତୁ;
	    }
	  clauses.safe_ଠେଲ (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_ଠେଲ (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  memset (&eof_token, 0, ଆକାର (eof_token));
  eof_token.type = CPP_EOF;
  clauses.safe_ଠେଲ (eof_token);
  clauses.safe_ଠେଲ (eof_token);

  ବାଛ (context)
    {
    ସ୍ଥିତି pragma_external:
      ଯଦି (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ext = disable_extension_diagnostics ();
	  କର
	    c_parser_consume_token (parser);
	  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ମିଥ୍ୟା, ସତ୍ୟ,
					 ମିଥ୍ୟା, ଖାଲି, &clauses);
	  restore_extension_diagnostics (ext);
	}
      ଅନ୍ୟଥା
	c_parser_declaration_or_fndef (parser, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ମିଥ୍ୟା, ସତ୍ୟ,
				       ମିଥ୍ୟା, ଖାଲି, &clauses);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି pragma_struct:
    ସ୍ଥିତି pragma_param:
    ସ୍ଥିତି pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      ଭାଙ୍ଗ;
    ସ୍ଥିତି pragma_compound:
      ତାର୍କିକ have_std_attrs;
      ବୃକ୍ଷ std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
      ଯଦି (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      ଅନ୍ୟଥା
	std_attrs = NULL_ବୃକ୍ଷ;
      ଯଦି (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ext = disable_extension_diagnostics ();
	  କର
	    c_parser_consume_token (parser);
	  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  ଯଦି (c_parser_next_tokens_start_declaration (parser)
	      || c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ,
					     ସତ୍ୟ, ମିଥ୍ୟା, ଖାଲି, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      ଭାଙ୍ଗ;
	    }
	  restore_extension_diagnostics (ext);
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_tokens_start_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ,
					 ମିଥ୍ୟା, ଖାଲି, &clauses, have_std_attrs,
					 std_attrs);
	  ଭାଙ୍ଗ;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_context_selector (c_parser *parser, ଗଣନା omp_tss_code set,
			       ବୃକ୍ଷ parms)
{
  ବୃକ୍ଷ ret = NULL_ବୃକ୍ଷ;
  କର
    {
      ବୃକ୍ଷ selector;
      ଯଦି (c_parser_next_token_is (parser, CPP_KEYWORD)
	  || c_parser_next_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      ଅନ୍ୟଥା
	{
	  c_parser_error (parser, "expected trait selector name");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}
      ଗଣନା omp_ts_code sel
	= omp_lookup_ts_code (set, IDENTIFIER_POINTER (selector));

      ଯଦି (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_POINTER (selector),  omp_tss_map[set]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ, ret);
	  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_balanced_token_sequence (parser);
	  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ଜାରି;
	    }
	  ଅନ୍ୟଥା
	    ଭାଙ୍ଗ;
	}

      c_parser_consume_token (parser);

      ବୃକ୍ଷ properties = NULL_ବୃକ୍ଷ;
      ବୃକ୍ଷ scoreval = NULL_ବୃକ୍ଷ;
      ଗଣନା omp_tp_type property_kind = omp_ts_map[sel].tp_type;
      ତାର୍କିକ allow_score = omp_ts_map[sel].allow_score;
      ବୃକ୍ଷ t;

      ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  ଯଦି (property_kind == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_POINTER (selector));
	      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER (token->ମୂଲ୍ୟ), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      ବୃକ୍ଷ score = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି).ମୂଲ୍ୟ;
	      parens2.skip_until_found_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      ଯଦି (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[set]);
	      ଅନ୍ୟଥା ଯଦି (score != error_mark_ଗଣ୍ଠି)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, ମିଥ୍ୟା, ଖାଲି);
		  ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (score))
		      || ବୃକ୍ଷ_CODE (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  ଅନ୍ୟଥା
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  ବାଛ (property_kind)
	    {
	    ସ୍ଥିତି OMP_TRAIT_PROPERTY_ID:
	      ଯଦି (c_parser_next_token_is (parser, CPP_KEYWORD)
		  || c_parser_next_token_is (parser, CPP_NAME))
		{
		  ବୃକ୍ଷ prop = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_ବୃକ୍ଷ,
						    properties);
		}
	      ଅନ୍ୟଥା
		{
		  c_parser_error (parser, "expected identifier");
		  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		}
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି OMP_TRAIT_PROPERTY_NAME_LIST:
	      କର
		{
		  ବୃକ୍ଷ prop = OMP_TP_NAMELIST_ଗଣ୍ଠି;
		  ବୃକ୍ଷ ମୂଲ୍ୟ = NULL_ବୃକ୍ଷ;
		  ଯଦି (c_parser_next_token_is (parser, CPP_KEYWORD)
		      || c_parser_next_token_is (parser, CPP_NAME))
		    {
		      ମୂଲ୍ୟ = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
		      c_parser_consume_token (parser);
		    }
		  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_STRING))
		    ମୂଲ୍ୟ = c_parser_string_literal (parser, ମିଥ୍ୟା,
						     ମିଥ୍ୟା).ମୂଲ୍ୟ;
		  ଅନ୍ୟଥା
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		    }

		  properties = make_trait_property (prop, ମୂଲ୍ୟ, properties);

		  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  ଅନ୍ୟଥା
		    ଭାଙ୍ଗ;
		}
	      ଯେତେବେଳେ (1);
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି OMP_TRAIT_PROPERTY_DEV_ଅଙ୍କ_ପଦସମଷ୍ଟି:
	    ସ୍ଥିତି OMP_TRAIT_PROPERTY_BOOL_ପଦସମଷ୍ଟି:
	      {
		c_ପଦସମଷ୍ଟି texpr = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
		texpr = convert_lvalue_to_rvalue (token->location, texpr,
						  ସତ୍ୟ, ସତ୍ୟ);
		t = texpr.ମୂଲ୍ୟ;
	      }
	      ଯଦି (t == error_mark_ଗଣ୍ଠି)
		ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	      mark_exp_read (t);
	      ଯଦି (property_kind == OMP_TRAIT_PROPERTY_BOOL_ପଦସମଷ୍ଟି)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_ଗଣ୍ଠି);
		  ଯଦି (t == error_mark_ଗଣ୍ଠି)
		    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		}
	      ଅନ୍ୟଥା ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		}
	      t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);
	      properties = make_trait_property (NULL_ବୃକ୍ଷ, t, properties);
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      ଯଦି (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  ଯଦି (parms == NULL_ବୃକ୍ଷ)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		    }
		  ବୃକ୍ଷ c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_MASK,
						"simd", ସତ୍ୟ, 2);
		  c = c_omp_declare_simd_clauses_to_numbers (parms
							     == error_mark_ଗଣ୍ଠି
							     ? NULL_ବୃକ୍ଷ : parms,
							     c);
		  properties = c;
		}
	      ଅନ୍ୟଥା ଯଦି (sel == OMP_TRAIT_IMPLEMENTATION_REQUIRES)
		{
		  /* FIXME: The "requires" selector was added in OpenMP 5.1.
		     Currently only the now-deprecated syntax
		     from OpenMP 5.0 is supported.  */
		  sorry_at (token->location,
			    "%<requires%> selector is not supported yet");
		  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
		}
	      ଅନ୍ୟଥା
		gcc_unreachable ();
	      ଭାଙ୍ଗ;
	    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	      gcc_unreachable ();
	    }

	  parens.skip_until_found_close (parser);
	  properties = nreverse (properties);
	}
      ଅନ୍ୟଥା ଯଦି (property_kind != OMP_TRAIT_PROPERTY_NONE
	       && property_kind != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_kind != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
    }
  ଯେତେବେଳେ (1);

  ଫେରନ୍ତୁ nreverse (ret);
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_context_selector_specification (c_parser *parser, ବୃକ୍ଷ parms)
{
  ବୃକ୍ଷ ret = NULL_ବୃକ୍ଷ;
  କର
    {
      ଅଚଳ ଅକ୍ଷର *setp = "";
      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଗଣନା omp_tss_code set = omp_lookup_tss_code (setp);

      ଯଦି (set == OMP_TRAIT_SET_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}

      c_parser_consume_token (parser);

      ଯଦି (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

      matching_braces braces;
      ଯଦି (!braces.require_open (parser))
	ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

      ବୃକ୍ଷ selectors = c_parser_omp_context_selector (parser, set, parms);
      ଯଦି (selectors == error_mark_ଗଣ୍ଠି)
	{
	  c_parser_skip_to_closing_brace (parser);
	  ret = error_mark_ଗଣ୍ଠି;
	}
      ଅନ୍ୟଥା ଯଦି (ret != error_mark_ଗଣ୍ଠି)
	ret = make_trait_set_selector (set, selectors, ret);

      braces.require_close (parser);

      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
    }
  ଯେତେବେଳେ (1);

  ଯଦି (ret == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ ret;
  ଫେରନ୍ତୁ nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_finish_omp_declare_variant (c_parser *parser, ବୃକ୍ଷ fndecl, ବୃକ୍ଷ parms)
{
  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    {
     fail:
      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ;
    }

  ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      ଯାଅ fail;
    }

  c_token *token = c_parser_peek_token (parser);
  ବୃକ୍ଷ variant = lookup_name (token->ମୂଲ୍ୟ);

  ଯଦି (variant == NULL_ବୃକ୍ଷ)
    {
      undeclared_variable (token->location, token->ମୂଲ୍ୟ);
      variant = error_mark_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା ଯଦି (fndecl_built_in_p (variant)
	   && (strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			"__builtin_", strlen ("__builtin_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__sync_", strlen ("__sync_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__atomic_", strlen ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା ଯଦି (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_ଗଣ୍ଠି;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  ବୃକ୍ଷ append_args_ବୃକ୍ଷ = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ append_args_last;
  vec<ବୃକ୍ଷ> adjust_args_list = vNULL;
  ତାର୍କିକ has_match = ମିଥ୍ୟା, has_adjust_args = ମିଥ୍ୟା;
  location_t adjust_args_loc = UNKNOWN_LOCATION;
  location_t append_args_loc = UNKNOWN_LOCATION;
  location_t match_loc = UNKNOWN_LOCATION;
  ବୃକ୍ଷ need_device_ptr_list = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ ctx = error_mark_ଗଣ୍ଠି;

  କର
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ଅଚଳ ଅକ୍ଷର *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);

      ଗଣନା clause
      {
	match,
	adjust_args,
	append_args
      } ccode;

      ଯଦି (strcmp (clause, "match") == 0)
	{
	  ccode = match;
	  match_loc = loc;
	}
      ଅନ୍ୟଥା ଯଦି (strcmp (clause, "adjust_args") == 0)
	{
	  ccode = adjust_args;
	  adjust_args_loc = loc;
	}
      ଅନ୍ୟଥା ଯଦି (strcmp (clause, "append_args") == 0)
	{
	  ccode = append_args;
	  append_args_loc = loc;
	}
      ଅନ୍ୟଥା
	{
	  c_parser_error (parser, "expected %<match%>, %<adjust_args%> or "
				  "%<append_args%> clause");
	  ଯାଅ fail;
	}

      c_parser_consume_token (parser);

      ଯଦି (!parens.require_open (parser))
	ଯାଅ fail;

      ଯଦି (parms == NULL_ବୃକ୍ଷ)
	parms = error_mark_ଗଣ୍ଠି;

      ଯଦି (ccode == match)
	{
	  ଯଦି (has_match)
	    error_at (match_loc, "too many %<match%> clauses");
	  has_match = ସତ୍ୟ;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  ଯଦି (ctx == error_mark_ଗଣ୍ଠି)
	    ଯାଅ fail;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  ଯଦି (ctx != error_mark_ଗଣ୍ଠି
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      ବୃକ୍ଷ outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      ଅନ୍ୟଥା ଯଦି (ccode == adjust_args)
	{
	  has_adjust_args = ସତ୍ୟ;
	  ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      ଅଚଳ ଅକ୍ଷର *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	      ଯଦି (strcmp (p, "need_device_ptr") == 0
		  || strcmp (p, "nothing") == 0)
		{
		  c_parser_consume_token (parser); // need_device_ptr
		  c_parser_consume_token (parser); // :

		  loc = c_parser_peek_token (parser)->location;
		  ବୃକ୍ଷ list
		    = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ERROR,
						  NULL_ବୃକ୍ଷ);

		  ବୃକ୍ଷ arg;
		  ଯଦି (variant != error_mark_ଗଣ୍ଠି)
		    ପାଇଁ (ବୃକ୍ଷ c = list; c != NULL_ବୃକ୍ଷ; c = ବୃକ୍ଷ_CHAIN (c))
		      {
			ବୃକ୍ଷ decl = ବୃକ୍ଷ_PURPOSE (c);
			location_t arg_loc = ପଦସମଷ୍ଟି_LOCATION (ବୃକ୍ଷ_ମୂଲ୍ୟ (c));
			ପୂର୍ଣ୍ଣସଂଖ୍ୟା idx;
			ପାଇଁ (arg = parms, idx = 0; arg != ଖାଲି;
			     arg = ବୃକ୍ଷ_CHAIN (arg), idx++)
			  ଯଦି (arg == decl)
			    ଭାଙ୍ଗ;
			ଯଦି (arg == NULL_ବୃକ୍ଷ)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    ଯାଅ fail;
			  }
			ଯଦି (adjust_args_list.contains (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    ଯାଅ fail;
			  }
			ଯଦି (strcmp (p, "need_device_ptr") == 0
			    && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (arg)) != POINTER_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    ଯାଅ fail;
			  }
			adjust_args_list.safe_ଠେଲ (arg);
			ଯଦି (strcmp (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_ବୃକ୍ଷ_list (
				NULL_ବୃକ୍ଷ,
				build_int_cst (
				  integer_type_ଗଣ୍ଠି,
				  idx))); // Store 0-based argument index,
					  // as in gimplify_call_expr
			  }
		      }
		}
	      ଅନ୍ୟଥା
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %<nothing%> or %<need_device_ptr%>");
		  ଯଦି (strcmp (p, "need_device_addr") == 0)
		    inform (c_parser_peek_token (parser)->location,
			    "%<need_device_addr%> is not valid for C");
		  ଯାଅ fail;
		}
	    }
	  ଅନ୍ୟଥା
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected %<nothing%> or %<need_device_ptr%> "
			"followed by %<:%>");
	      ଯାଅ fail;
	    }
	}
      ଅନ୍ୟଥା ଯଦି (ccode == append_args)
	{
	  ଯଦି (append_args_ବୃକ୍ଷ)
	    {
	      error_at (append_args_loc, "too many %qs clauses", "append_args");
	      append_args_ବୃକ୍ଷ = NULL_ବୃକ୍ଷ;
	    }
	  କର
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      ଯଦି (!c_parser_next_token_is (parser, CPP_NAME)
		  || strcmp ("interop",
			     IDENTIFIER_POINTER (
			       c_parser_peek_token (parser)->ମୂଲ୍ୟ)))
		{
		  error_at (loc, "expected %<interop%>");
		  ଯାଅ fail;
		}
	      c_parser_consume_token (parser);

	      ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		ଯାଅ fail;
	      ତାର୍କିକ target = ମିଥ୍ୟା;
	      ତାର୍କିକ targetsync = ମିଥ୍ୟା;
	      ବୃକ୍ଷ prefer_type_ବୃକ୍ଷ = NULL_ବୃକ୍ଷ;
	      ଯଦି (!c_parser_omp_clause_init_modifiers (parser, &target,
						       &targetsync,
						       &prefer_type_ବୃକ୍ଷ)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		ଯାଅ fail;
	      ଯଦି (!target && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      ବୃକ୍ଷ t = build_ବୃକ୍ଷ_list (target ? boolean_true_ଗଣ୍ଠି
					       : boolean_false_ଗଣ୍ଠି,
					targetsync ? boolean_true_ଗଣ୍ଠି
						   : boolean_false_ଗଣ୍ଠି);
	      t = build1_loc (loc, NOP_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି, t);
	      t = build_ବୃକ୍ଷ_list (t, prefer_type_ବୃକ୍ଷ);
	      ଯଦି (append_args_ବୃକ୍ଷ)
		{
		  ବୃକ୍ଷ_CHAIN (append_args_last) = t;
		  append_args_last = t;
		}
	      ଅନ୍ୟଥା
		append_args_ବୃକ୍ଷ = append_args_last = t;
	      ଯଦି (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		ଭାଙ୍ଗ;
	      ଯଦି (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		ଯାଅ fail;
	    }
	  ଯେତେବେଳେ (ସତ୍ୟ);
	}

      parens.require_close (parser);
  } ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL));
  ଯଦି (variant != error_mark_ଗଣ୍ଠି && !has_match)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_ଗଣ୍ଠି;
    }
  c_parser_skip_to_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  ଯଦି (variant == error_mark_ଗଣ୍ଠି || ctx == error_mark_ଗଣ୍ଠି)
    /* Previously diagnosed error.  */
    ଫେରନ୍ତୁ;

  ଯଦି ((has_adjust_args || append_args_ବୃକ୍ଷ)
      && !omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_args ? adjust_args_loc : append_args_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_args ? "adjust_args" : "append_args");
      ଫେରନ୍ତୁ;
    }

  ଯଦି (!omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      ବୃକ୍ଷ base_type = ବୃକ୍ଷ_TYPE (fndecl);
      ବୃକ୍ଷ variant_type = ବୃକ୍ଷ_TYPE (variant);
      ତାର୍କିକ unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_ବୃକ୍ଷ
	   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type));

      ଯଦି (append_args_ବୃକ୍ଷ
	  && TYPE_ARG_TYPES (base_type) == NULL_ବୃକ୍ଷ
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
	  ଫେରନ୍ତୁ;
	}
      ଅନ୍ୟଥା ଯଦି (append_args_ବୃକ୍ଷ)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା nappend_args = 0;
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା nbase_args = 0;
	  ପାଇଁ (ବୃକ୍ଷ t = TYPE_ARG_TYPES (base_type);
	       t && ବୃକ୍ଷ_ମୂଲ୍ୟ (t) != void_type_ଗଣ୍ଠି; t = ବୃକ୍ଷ_CHAIN (t))
	    nbase_args++;
	  ପାଇଁ (ବୃକ୍ଷ t = append_args_ବୃକ୍ଷ; t; t = ବୃକ୍ଷ_CHAIN (t))
	    nappend_args++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_args_ବୃକ୍ଷ = build_ବୃକ୍ଷ_list (build_int_cst (integer_type_ଗଣ୍ଠି,
							     nbase_args),
					      append_args_ବୃକ୍ଷ);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  ଯଦି (!unprototyped_variant)
	    {
	      ବୃକ୍ଷ args = TYPE_ARG_TYPES (variant_type);
	      ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; args && i < nbase_args;
		   i++, args = ବୃକ୍ଷ_CHAIN (args))
		;
	      ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nappend_args; i++, args = ବୃକ୍ଷ_CHAIN (args))
		ଯଦି (!args || !c_omp_interop_t_p (ବୃକ୍ଷ_ମୂଲ୍ୟ (args)))
		  {
		    error_at (DECL_SOURCE_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_args + i + 1, variant);
		    inform (append_args_loc,
			    "%<append_args%> specified here");
		    ଫେରନ୍ତୁ;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  ବୃକ୍ଷ args = TYPE_ARG_TYPES (base_type);
	  ବୃକ୍ଷ newargs = NULL_ବୃକ୍ଷ;
	  ବୃକ୍ଷ lastarg = NULL_ବୃକ୍ଷ;
	  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < nbase_args; j++, args = ବୃକ୍ଷ_CHAIN (args))
	    {
	      ବୃକ୍ଷ t = ବୃକ୍ଷ_cons (ବୃକ୍ଷ_PURPOSE (args),
				  ବୃକ୍ଷ_ମୂଲ୍ୟ (args), NULL_ବୃକ୍ଷ);
	      ଯଦି (lastarg)
		ବୃକ୍ଷ_CHAIN (lastarg) = t;
	      ଅନ୍ୟଥା
		newargs = t;
	      lastarg = t;
	    }
	  ବୃକ୍ଷ type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? ବୃକ୍ଷ_TYPE (type) : pointer_sized_int_ଗଣ୍ଠି;
	  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < nappend_args; j++)
	    {
	      ବୃକ୍ଷ t = ବୃକ୍ଷ_cons (NULL_ବୃକ୍ଷ, type, NULL_ବୃକ୍ଷ);
	      ଯଦି (lastarg)
		ବୃକ୍ଷ_CHAIN (lastarg) = t;
	      ଅନ୍ୟଥା
		newargs = t;
	      lastarg = t;
	    }
	  ବୃକ୍ଷ_CHAIN (lastarg) = args;

	  /* Temporarily stuff newargs into the original base_type.  */
	  ବୃକ୍ଷ saveargs = TYPE_ARG_TYPES (base_type);
	  TYPE_ARG_TYPES (base_type) = newargs;
	  ତାର୍କିକ fail = !comptypes (base_type, variant_type);
	  TYPE_ARG_TYPES (base_type) = saveargs;

	  ଯଦି (fail)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      ଫେରନ୍ତୁ;
	    }
	  ଅନ୍ୟଥା ଯଦି (unprototyped_variant)
	    /* If we've got an unprototyped variant, copy the transformed
	       base arg types to the variant.  This is needed later by
	       modify_call_for_omp_dispatch.  */
	    TYPE_ARG_TYPES (variant_type) = newargs;
	}
      ଅନ୍ୟଥା  /* No append_args present.  */
	{
	  ଯଦି (!comptypes (base_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      ଫେରନ୍ତୁ;
	    }
	  ଅନ୍ୟଥା ଯଦି (TYPE_ARG_TYPES (variant_type) == NULL_ବୃକ୍ଷ
		   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (base_type) != NULL_ବୃକ୍ଷ)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (base_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_USED (variant) = 1;
  ବୃକ୍ଷ construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (match_loc, variant, construct);
  ଯଦି (omp_context_selector_matches (ctx, NULL_ବୃକ୍ଷ, ମିଥ୍ୟା))
    {
      ବୃକ୍ଷ attr = ବୃକ୍ଷ_cons (get_identifier ("omp declare variant base"),
			     build_ବୃକ୍ଷ_list (variant, ctx),
			     DECL_ATTRIBUTES (fndecl));
      DECL_ATTRIBUTES (fndecl) = attr;
    }

  ଯଦି (need_device_ptr_list || append_args_ବୃକ୍ଷ)
    {
      ବୃକ୍ଷ variant_decl = ବୃକ୍ଷ_strip_nop_conversions (variant);
      ବୃକ୍ଷ t = build_ବୃକ୍ଷ_list (need_device_ptr_list,
				NULL_ବୃକ୍ଷ /* need_device_addr */);
      ବୃକ୍ଷ_CHAIN (t) = append_args_ବୃକ୍ଷ;
      DECL_ATTRIBUTES (variant_decl)
	= ବୃକ୍ଷ_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_ATTRIBUTES (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_finish_omp_declare_simd (c_parser *parser, ବୃକ୍ଷ fndecl, ବୃକ୍ଷ parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  ଯଦି (clauses.exists () && clauses[0].type == CPP_EOF)
    ଫେରନ୍ତୁ;
  ଅଚଳ ଅକ୍ଷର *kind = "simd";
  ଯଦି (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    kind = IDENTIFIER_POINTER (clauses[0].ମୂଲ୍ୟ);
  gcc_assert (strcmp (kind, "simd") == 0 || strcmp (kind, "variant") == 0);
  ଯଦି (fndecl == NULL_ବୃକ୍ଷ || ବୃକ୍ଷ_CODE (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      ଫେରନ୍ତୁ;
    }
  ଯଦି (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      ଫେରନ୍ତୁ;
    }
  ଯଦି (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", kind);
      ଫେରନ୍ତୁ;
    }

  ଯଦି (parms == NULL_ବୃକ୍ଷ)
    parms = DECL_ARGUMENTS (fndecl);

  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);

  parser->tokens = clauses.address ();
  parser->tokens_avail = clauses.length ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  ଯେତେବେଳେ (parser->tokens_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      kind = IDENTIFIER_POINTER (token->ମୂଲ୍ୟ);
      c_parser_consume_token (parser);
      parser->in_pragma = ସତ୍ୟ;

      ଯଦି (strcmp (kind, "simd") == 0)
	{
	  ବୃକ୍ଷ c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_MASK,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_to_numbers (parms, c);
	  ଯଦି (c != NULL_ବୃକ୍ଷ)
	    c = ବୃକ୍ଷ_cons (NULL_ବୃକ୍ଷ, c, NULL_ବୃକ୍ଷ);
	  c = build_ବୃକ୍ଷ_list (get_identifier ("omp declare simd"), c);
	  ବୃକ୍ଷ_CHAIN (c) = DECL_ATTRIBUTES (fndecl);
	  DECL_ATTRIBUTES (fndecl) = c;
	}
      ଅନ୍ୟଥା
	{
	  gcc_assert (strcmp (kind, "variant") == 0);
	  c_finish_omp_declare_variant (parser, fndecl, parms);
	}
    }

  parser->tokens = &parser->tokens_buf[0];
  parser->tokens_avail = tokens_avail;
  ଯଦି (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#ଯଦି !defined (NO_DOT_IN_LABEL)
#define JOIN_STR "."
#ନଚେତଯଦି !defined (NO_DOLLAR_IN_LABEL)
#define JOIN_STR "$"
#ଅନ୍ୟଥା
#define JOIN_STR "_"
#endif

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
ସ୍ଥିର ବୃକ୍ଷ
omp_start_variant_function (c_declarator *declarator, ବୃକ୍ଷ ctx)
{
  c_declarator *id = declarator;
  ଯେତେବେଳେ (id->kind != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  ବୃକ୍ଷ name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  ଫେରନ୍ତୁ name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
ସ୍ଥିର ଶୂନ୍ୟ
omp_finish_variant_function (ବୃକ୍ଷ decl, ବୃକ୍ଷ base_name, ବୃକ୍ଷ ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  ବୃକ୍ଷ base_decl = lookup_name (base_name);
  ଯଦି (base_decl == error_mark_ଗଣ୍ଠି)
    base_decl = NULL_ବୃକ୍ଷ;
  ଯଦି (!base_decl)
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_POINTER (base_name));
      ଫେରନ୍ତୁ;
    }

  ଯଦି (!comptypes (ବୃକ୍ଷ_TYPE (decl), ବୃକ୍ଷ_TYPE (base_decl)))
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", base_decl);
      inform (DECL_SOURCE_LOCATION (base_decl),
	      "%qE declared here", base_decl);
      ଫେରନ୍ତୁ;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_SOURCE_LOCATION (decl),
				   base_decl, ctx);
  ବୃକ୍ଷ construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (DECL_SOURCE_LOCATION (decl), decl, construct);
  ବୃକ୍ଷ attrs = DECL_ATTRIBUTES (base_decl);
  ବୃକ୍ଷ match_loc_ଗଣ୍ଠି
    = maybe_wrap_with_location (integer_zero_ଗଣ୍ଠି,
				DECL_SOURCE_LOCATION (base_decl));
  ବୃକ୍ଷ loc_ଗଣ୍ଠି = ବୃକ୍ଷ_cons (match_loc_ଗଣ୍ଠି, integer_zero_ଗଣ୍ଠି,
			     build_ବୃକ୍ଷ_list (match_loc_ଗଣ୍ଠି,
					      integer_zero_ଗଣ୍ଠି));
  attrs = ବୃକ୍ଷ_cons (get_identifier ("omp declare variant base"),
		     ବୃକ୍ଷ_cons (decl, ctx, loc_ଗଣ୍ଠି), attrs);
  DECL_ATTRIBUTES (base_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  ବୃକ୍ଷ_PUBLIC (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

ତାର୍କିକ
c_maybe_parse_omp_decl (ବୃକ୍ଷ decl, ବୃକ୍ଷ d)
{
  gcc_assert (ବୃକ୍ଷ_CODE (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
  c_token *first = toks->address ();
  c_token *last = first + toks->length ();
  ଅଚଳ ଅକ୍ଷର *directive[3] = {};
  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < 3; j++)
    {
      ବୃକ୍ଷ id = NULL_ବୃକ୍ଷ;
      ଯଦି (first + j == last)
	ଭାଙ୍ଗ;
      ଯଦି (first[j].type == CPP_NAME)
	id = first[j].ମୂଲ୍ୟ;
      ଅନ୍ୟଥା ଯଦି (first[j].type == CPP_KEYWORD)
	id = ridpointers[(ପୂର୍ଣ୍ଣସଂଖ୍ୟା) first[j].keyword];
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
      directive[j] = IDENTIFIER_POINTER (id);
    }
  ଅଚଳ c_omp_directive *dir = ଖାଲି;
  ଯଦି (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  ଯଦି (dir == ଖାଲି)
    {
      error_at (first->location,
		"unknown OpenMP directive name in "
		"%qs attribute argument", "omp::decl");
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }
  ଯଦି (dir->id != PRAGMA_OMP_THREADPRIVATE
      && dir->id != PRAGMA_OMP_GROUPPRIVATE
      && dir->id != PRAGMA_OMP_ALLOCATE
      && (dir->id != PRAGMA_OMP_DECLARE
	  || strcmp (directive[1], "target") != 0))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଯଦି (!flag_openmp && !dir->simd)
    ଫେରନ୍ତୁ ସତ୍ୟ;

  c_parser *parser = the_parser;
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);
  toks = ଖାଲି;
  vec_safe_reserve (toks, last - first + 2, ସତ୍ୟ);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_kind = pragma_kind (dir->id);
  tok.location = first->location;
  toks->quick_ଠେଲ (tok);
  ଯେତେବେଳେ (++first < last)
    toks->quick_ଠେଲ (*first);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_ଠେଲ (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_ଠେଲ (tok);
  parser->in_omp_decl_attribute = decl;
  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = toks->length ();
  c_parser_pragma (parser, pragma_external, ଖାଲି, NULL_ବୃକ୍ଷ);
  parser->in_omp_decl_attribute = NULL_ବୃକ୍ଷ;
  ଫେରନ୍ତୁ ସତ୍ୟ;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_declare_target (c_parser *parser)
{
  ବୃକ୍ଷ clauses = NULL_ବୃକ୍ଷ;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା device_type = 0;
  ତାର୍କିକ indirect = ମିଥ୍ୟା;
  ତାର୍କିକ only_device_type_or_indirect = ସତ୍ୟ;
  ଯଦି (flag_openmp)
    omp_requires_mask
      = (ଗଣନା omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
      || (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp declare target");
  ଅନ୍ୟଥା ଯଦି (parser->in_omp_decl_attribute
	   || c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      clauses = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					      clauses);
      clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
      c_parser_skip_to_pragma_eol (parser);
    }
  ଅନ୍ୟଥା
    {
      warning_at (c_parser_peek_token (parser)->location,
		  OPT_Wdeprecated_openmp,
		  "use of %<omp declare target%> as a synonym for "
		  "%<omp begin declare target%> has been deprecated since "
		  "OpenMP 5.2");
      ତାର୍କିକ attr_syntax = parser->in_omp_attribute_pragma != ଖାଲି;
      c_parser_skip_to_pragma_eol (parser);
      c_omp_declare_target_attr attr = { attr_syntax, -1, 0 };
      vec_safe_ଠେଲ (current_omp_declare_target_attribute, attr);
      ଫେରନ୍ତୁ;
    }
  ପାଇଁ (ବୃକ୍ଷ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_ପଦସମଷ୍ଟି (c));
    }
  ପାଇଁ (ବୃକ୍ଷ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	ଜାରି;
      ବୃକ୍ଷ t = OMP_CLAUSE_DECL (c), id;
      ବୃକ୍ଷ at1 = lookup_attribute ("omp declare target", DECL_ATTRIBUTES (t));
      ବୃକ୍ଷ at2 = lookup_attribute ("omp declare target link",
				   DECL_ATTRIBUTES (t));
      only_device_type_or_indirect = ମିଥ୍ୟା;
      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::swap (at1, at2);
	}
      ଅନ୍ୟଥା
	id = get_identifier ("omp declare target");
      ଯଦି (at2)
	{
	  ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	  ଅନ୍ୟଥା ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL
		   || ମୂଲ୍ୟ_member (get_identifier ("local"), ବୃକ୍ଷ_ମୂଲ୍ୟ (at2)))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<local%> clauses", t);
	  ଅନ୍ୟଥା
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<to%> or %<enter%> clauses", t);
	  ଜାରି;
	}
      ଯଦି (!at1)
	{
	  DECL_ATTRIBUTES (t) = ବୃକ୍ଷ_cons (id, NULL_ବୃକ୍ଷ, DECL_ATTRIBUTES (t));
	  ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    ବୃକ୍ଷ_ମୂଲ୍ୟ (DECL_ATTRIBUTES (t))
	      = ବୃକ୍ଷ_cons (NULL_ବୃକ୍ଷ, get_identifier ("local"),
			   ବୃକ୍ଷ_ମୂଲ୍ୟ (DECL_ATTRIBUTES (t)));

	  ଯଦି (ବୃକ୍ଷ_CODE (t) != FUNCTION_DECL && !is_global_var (t))
	    ଜାରି;

	  symtab_ଗଣ୍ଠି *ଗଣ୍ଠି = symtab_ଗଣ୍ଠି::get (t);
	  ଯଦି (ଗଣ୍ଠି != ଖାଲି)
	    {
	      ଗଣ୍ଠି->offloadable = 1;
	      ଯଦି (ENABLE_OFFLOADING)
		{
		  g->have_offload = ସତ୍ୟ;
		  ଯଦି (is_a <varpool_ଗଣ୍ଠି *> (ଗଣ୍ଠି)
		      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_LOCAL)
		    vec_safe_ଠେଲ (offload_vars, t);
		}
	    }
	}
      ଅନ୍ୟଥା
	{
	  ତାର୍କିକ saw_local = ମୂଲ୍ୟ_member (get_identifier ("local"),
					 ବୃକ୍ଷ_ମୂଲ୍ୟ (at1));
	  ଯଦି (saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	      ଜାରି;
	    }
	  ଅନ୍ୟଥା ଯଦି (!saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      ଜାରି;
	    }
	}
      ଯଦି (ବୃକ୍ଷ_CODE (t) != FUNCTION_DECL)
	ଜାରି;
      ଯଦି ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  ବୃକ୍ଷ at3 = lookup_attribute ("omp declare target host",
				       DECL_ATTRIBUTES (t));
	  ଯଦି (at3 == NULL_ବୃକ୍ଷ)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_ATTRIBUTES (t)
		= ବୃକ୍ଷ_cons (id, NULL_ବୃକ୍ଷ, DECL_ATTRIBUTES (t));
	    }
	}
      ଯଦି ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  ବୃକ୍ଷ at3 = lookup_attribute ("omp declare target nohost",
				       DECL_ATTRIBUTES (t));
	  ଯଦି (at3 == NULL_ବୃକ୍ଷ)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_ATTRIBUTES (t)
		= ବୃକ୍ଷ_cons (id, NULL_ବୃକ୍ଷ, DECL_ATTRIBUTES (t));
	    }
	}
      ଯଦି (indirect)
	{
	  ବୃକ୍ଷ at4 = lookup_attribute ("omp declare target indirect",
				       DECL_ATTRIBUTES (t));
	  ଯଦି (at4 == NULL_ବୃକ୍ଷ)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_ATTRIBUTES (t)
		= ବୃକ୍ଷ_cons (id, NULL_ବୃକ୍ଷ, DECL_ATTRIBUTES (t));
	    }
	}
    }
  ଯଦି ((device_type || indirect) && only_device_type_or_indirect)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  ଯଦି (indirect && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_begin (c_parser *parser)
{
  ଅଚଳ ଅକ୍ଷର *p = "";
  c_parser_consume_pragma (parser);
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
  ଯଦି (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  ତାର୍କିକ attr_syntax = parser->in_omp_attribute_pragma != ଖାଲି;
	  ବୃକ୍ଷ clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp begin declare target");
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା device_type = 0;
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା indirect = 0;
	  ପାଇଁ (ବୃକ୍ଷ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
	      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
		indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_ପଦସମଷ୍ଟି (c));
	    }
	  c_omp_declare_target_attr attr = { attr_syntax, device_type,
					     indirect };
	  vec_safe_ଠେଲ (current_omp_declare_target_attribute, attr);
	}
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  ଅଚଳ ଅକ୍ଷର *clause = "";
	  matching_parens parens;
	  location_t match_loc = c_parser_peek_token (parser)->location;
	  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      ବୃକ୍ଷ id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	      clause = IDENTIFIER_POINTER (id);
	    }
	  ଯଦି (strcmp (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_to_pragma_eol (parser);
	      ଫେରନ୍ତୁ;
	    }

	  c_parser_consume_token (parser);

	  ଯଦି (!parens.require_open (parser))
	    {
	      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	      ଫେରନ୍ତୁ;
	    }

	  ବୃକ୍ଷ ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_ବୃକ୍ଷ);
	  ଯଦି (ctx != error_mark_ଗଣ୍ଠି)
	    ctx = omp_check_context_selector (match_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  ଯଦି (ctx != error_mark_ଗଣ୍ଠି
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      ବୃକ୍ଷ outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  ଯଦି (ctx == error_mark_ଗଣ୍ଠି
	      || !omp_context_selector_matches (ctx, NULL_ବୃକ୍ଷ, ମିଥ୍ୟା, ସତ୍ୟ))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	      c_parser_skip_to_pragma_omp_end_declare_variant (parser);
	      ଫେରନ୍ତୁ;
	    }
	  ଅନ୍ୟଥା
	    {
	      ତାର୍କିକ attr_syntax = parser->in_omp_attribute_pragma != ଖାଲି;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_safe_ଠେଲ (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_to_pragma_eol (parser);
	}
      ଅନ୍ୟଥା
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	}
    }
  ଅନ୍ୟଥା ଯଦି (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      ତାର୍କିକ attr_syntax = parser->in_omp_attribute_pragma != ଖାଲି;
      c_parser_omp_assumption_clauses (parser, ମିଥ୍ୟା);
      ସଂରଚନା c_omp_begin_assumes_data a = { attr_syntax };
      vec_safe_ଠେଲ (current_omp_begin_assumes, a);
    }
  ଅନ୍ୟଥା
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_end (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ଅଚଳ ଅକ୍ଷର *p = "";
  c_parser_consume_pragma (parser);
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
  ଯଦି (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  ତାର୍କିକ attr_syntax = parser->in_omp_attribute_pragma != ଖାଲି;
	  c_parser_skip_to_pragma_eol (parser);
	  ଯଦି (!vec_safe_length (current_omp_declare_target_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  ଅନ୍ୟଥା
	    {
	      c_omp_declare_target_attr
		a = current_omp_declare_target_attribute->କାଢ଼ ();
	      ଯଦି (a.attr_syntax != attr_syntax)
		{
		  ଯଦି (a.attr_syntax)
		    error_at (loc,
			      "%qs in attribute syntax terminated "
			      "with %qs in pragma syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		  ଅନ୍ୟଥା
		    error_at (loc,
			      "%qs in pragma syntax terminated "
			      "with %qs in attribute syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		}
	    }
	}
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  ତାର୍କିକ attr_syntax = parser->in_omp_attribute_pragma != ଖାଲି;
	  c_parser_skip_to_pragma_eol (parser);
	  ଯଦି (!vec_safe_length (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  ଅନ୍ୟଥା
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->କାଢ଼ ();
	      ଯଦି (a.attr_syntax != attr_syntax)
		{
		  ଯଦି (a.attr_syntax)
		    error_at (loc,
			      "%<begin declare variant%> in attribute syntax "
			      "terminated with "
			      "%<end declare variant%> in pragma syntax");
		  ଅନ୍ୟଥା
		    error_at (loc,
			      "%<begin declare variant%> in pragma syntax "
			      "terminated with "
			      "%<end declare variant%> in attribute syntax");
		}
	    }
	}
      ଅନ୍ୟଥା
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser);
	  ଫେରନ୍ତୁ;
	}
    }
  ଅନ୍ୟଥା ଯଦି (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      ତାର୍କିକ attr_syntax = parser->in_omp_attribute_pragma != ଖାଲି;
      c_parser_skip_to_pragma_eol (parser);
      ଯଦି (!vec_safe_length (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      ଅନ୍ୟଥା
	{
	  c_omp_begin_assumes_data
	    a = current_omp_begin_assumes->କାଢ଼ ();
	  ଯଦି (a.attr_syntax != attr_syntax)
	    {
	      ଯଦି (a.attr_syntax)
		error_at (loc,
			  "%qs in attribute syntax terminated "
			  "with %qs in pragma syntax",
			  "begin assumes", "end assumes");
	      ଅନ୍ୟଥା
		error_at (loc,
			  "%qs in pragma syntax terminated "
			  "with %qs in attribute syntax",
			  "begin assumes", "end assumes");
	    }
	}
    }
  ଅନ୍ୟଥା
    {
      c_parser_error (parser, "expected %<declare%> or %<assumes%>");
      c_parser_skip_to_pragma_eol (parser);
    }
}

/* OpenMP 5.0
   #pragma omp declare mapper ([mapper-identifier :] type var) \
			      [clause [ [,] clause ] ... ] new-line  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_declare_mapper (c_parser *parser, ଗଣନା pragma_context context)
{
  ବୃକ୍ଷ type, mapper_name = NULL_ବୃକ୍ଷ, var = NULL_ବୃକ୍ଷ, stmt, stmtlist;
  ବୃକ୍ଷ maplist = NULL_ବୃକ୍ଷ, mapper_id, mapper_decl, t;
  c_token *token;

  ଯଦି (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare mapper%> not at file or block scope");
      ଯାଅ fail;
    }

  ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ଯାଅ fail;

  token = c_parser_peek_token (parser);

  ଯଦି (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      ବାଛ (token->type)
	{
	ସ୍ଥିତି CPP_NAME:
	  mapper_name = token->ମୂଲ୍ୟ;
	  c_parser_consume_token (parser);
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_KEYWORD:
	  ଯଦି (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_ବୃକ୍ଷ;
	      c_parser_consume_token (parser);
	      ଭାଙ୍ଗ;
	    }
	  /* Fallthrough.  */
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	  ଫେରନ୍ତୁ;
	}

      ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ଯାଅ fail;
    }

  mapper_id = c_omp_mapper_id (mapper_name);
  mapper_decl = c_omp_mapper_decl (mapper_id);

  {
    location_t loc = c_parser_peek_token (parser)->location;
    ସଂରଚନା c_type_name *ctype = c_parser_type_name (parser);
    type = groktypename (ctype, ଖାଲି, ଖାଲି);
    ଯଦି (type == error_mark_ଗଣ୍ଠି)
      ଯାଅ fail;
    ଯଦି (!RECORD_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	ଫେରନ୍ତୁ;
      }
    ପାଇଁ (ବୃକ୍ଷ t = DECL_INITIAL (mapper_decl); t; t = ବୃକ୍ଷ_CHAIN (t))
      ଯଦି (comptypes (ବୃକ୍ଷ_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_POINTER (mapper_id)
		      + ଆକାର ("omp declare mapper ") - 1,
		    type);
	  ବୃକ୍ଷ prevmapper = ବୃକ୍ଷ_ମୂଲ୍ୟ (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_SOURCE_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	  ଫେରନ୍ତୁ;
	}
  }

  token = c_parser_peek_token (parser);
  ଯଦି (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->ମୂଲ୍ୟ, type);
      c_parser_consume_token (parser);
      DECL_ARTIFICIAL (var) = 1;
    }
  ଅନ୍ୟଥା
    {
      error_at (token->location, "expected identifier");
      ଯାଅ fail;
    }

  ଯଦି (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ଯାଅ fail;

  ଠେଲ_scope ();
  stmtlist = ଠେଲ_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);
      ଯଦି (c_kind != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (here, "unexpected clause");
	  ଯାଅ fail;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, ସତ୍ୟ);
    }

  ଯଦି (maplist == NULL_ବୃକ୍ଷ)
    {
      error_at (ନିବେଶ_location, "missing %<map%> clause");
      ଯାଅ fail;
    }
  ବୃକ୍ଷ list;
  ପାଇଁ (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      ବୃକ୍ଷ dvar = OMP_CLAUSE_DECL (list);
      ଯେତେବେଳେ (!DECL_P (dvar) && ବୃକ୍ଷ_OPERAND_LENGTH (dvar))
	dvar = ବୃକ୍ଷ_OPERAND (dvar, 0);
      ଯଦି (dvar == var)
	ଭାଙ୍ଗ;
    }
  ଯଦି (!list)
    error_at (ନିବେଶ_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_ଗଣ୍ଠି (OMP_DECLARE_MAPPER);
  ବୃକ୍ଷ_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  add_stmt (stmt);

  କାଢ଼_stmt_list (stmtlist);
  କାଢ଼_scope ();

  c_parser_skip_to_pragma_eol (parser);

  t = ବୃକ୍ଷ_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  ଫେରନ୍ତୁ;

 fail:
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 4.0
   #pragma omp declare reduction (reduction-id : typename-list : expression) \
      initializer-clause[opt] new-line

   initializer-clause:
      initializer (omp_priv = initializer)
      initializer (function-name (argument-list))  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_declare_reduction (c_parser *parser, ଗଣନା pragma_context context)
{
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା tokens_avail = 0, i;
  c_token *saved_tokens = ଖାଲି;
  vec<ବୃକ୍ଷ> types = vNULL;
  vec<c_token> clauses = vNULL;
  ଗଣନା ବୃକ୍ଷ_code reduc_code = ERROR_MARK;
  ବୃକ୍ଷ reduc_id = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ type;
  location_t rloc = c_parser_peek_token (parser)->location;

  ଯଦି (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare reduction%> not at file or block scope");
      ଯାଅ fail;
    }

  ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ଯାଅ fail;

  ବାଛ (c_parser_peek_token (parser)->type)
    {
    ସ୍ଥିତି CPP_PLUS:
      reduc_code = PLUS_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_MULT:
      reduc_code = MULT_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_MINUS:
      reduc_code = MINUS_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_AND:
      reduc_code = BIT_AND_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_XOR:
      reduc_code = BIT_XOR_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_OR:
      reduc_code = BIT_IOR_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_AND_AND:
      reduc_code = TRUTH_ANDIF_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_OR_OR:
      reduc_code = TRUTH_ORIF_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_NAME:
      ଅଚଳ ଅକ୍ଷର *p;
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "min") == 0)
	{
	  reduc_code = MIN_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	}
      ଯଦି (strcmp (p, "max") == 0)
	{
	  reduc_code = MAX_ପଦସମଷ୍ଟି;
	  ଭାଙ୍ଗ;
	}
      reduc_id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      ଯାଅ fail;
    }

  ବୃକ୍ଷ orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_code, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    ଯାଅ fail;

  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      ସଂରଚନା c_type_name *ctype = c_parser_type_name (parser);
      ଯଦି (ctype != ଖାଲି)
	{
	  type = groktypename (ctype, ଖାଲି, ଖାଲି);
	  ଯଦି (type == error_mark_ଗଣ୍ଠି)
	    ;
	  ଅନ୍ୟଥା ଯଦି ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || ବୃକ୍ଷ_CODE (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_ବୃକ୍ଷ)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == FUNCTION_TYPE
		   || ବୃକ୍ଷ_CODE (type) == ARRAY_TYPE)
	    error_at (loc, "function or array type in "
		      "%<#pragma omp declare reduction%>");
	  ଅନ୍ୟଥା ଯଦି (TYPE_ATOMIC (type))
	    error_at (loc, "%<_Atomic%> qualified type in "
			   "%<#pragma omp declare reduction%>");
	  ଅନ୍ୟଥା ଯଦି (TYPE_QUALS_NO_ADDR_SPACE (type))
	    error_at (loc, "const, volatile or restrict qualified type in "
			   "%<#pragma omp declare reduction%>");
	  ଅନ୍ୟଥା
	    {
	      ବୃକ୍ଷ t;
	      ପାଇଁ (t = DECL_INITIAL (reduc_decl); t; t = ବୃକ୍ଷ_CHAIN (t))
		ଯଦି (comptypes (ବୃକ୍ଷ_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_POINTER (reduc_id)
				   + ଆକାର ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_SOURCE_LOCATION (ବୃକ୍ଷ_VEC_ELT (ବୃକ୍ଷ_ମୂଲ୍ୟ (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    ଭାଙ୍ଗ;
		  }
	      ଯଦି (t == NULL_ବୃକ୍ଷ)
		types.safe_ଠେଲ (type);
	    }
	  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ଅନ୍ୟଥା
	    ଭାଙ୍ଗ;
	}
      ଅନ୍ୟଥା
	ଭାଙ୍ଗ;
    }

  ଯଦି (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_empty ())
    {
     fail:
      clauses.release ();
      types.release ();
      ଯେତେବେଳେ (ସତ୍ୟ)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ଯଦି (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    ଭାଙ୍ଗ;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_to_pragma_eol (parser);
      ଫେରନ୍ତୁ;
    }

  ଯଦି (types.length () > 1)
    {
      ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  ଯଦି (token->type == CPP_EOF)
	    ଯାଅ fail;
	  clauses.safe_ଠେଲ (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_ଠେଲ (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, ଆକାର (eof_token));
      eof_token.type = CPP_EOF;
      clauses.safe_ଠେଲ (eof_token);
      clauses.safe_ଠେଲ (eof_token);
    }

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_tokens = parser->tokens;
      tokens_avail = parser->tokens_avail;
      ଯଦି (!clauses.is_empty ())
	{
	  parser->tokens = clauses.address ();
	  parser->tokens_avail = clauses.length ();
	  parser->in_pragma = ସତ୍ୟ;
	}

      ତାର୍କିକ nested = current_function_decl != NULL_ବୃକ୍ଷ;
      ଯଦି (nested)
	c_ଠେଲ_function_context ();
      ବୃକ୍ଷ fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, ସତ୍ୟ);
      ଠେଲ_scope ();
      ବୃକ୍ଷ stmt = ଠେଲ_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      ବୃକ୍ଷ omp_out = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_out) = 1;
      DECL_CONTEXT (omp_out) = fndecl;
      pushdecl (omp_out);
      ବୃକ୍ଷ omp_in = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_in) = 1;
      DECL_CONTEXT (omp_in) = fndecl;
      pushdecl (omp_in);
      ସଂରଚନା c_ପଦସମଷ୍ଟି combiner = c_parser_expression (parser);
      ସଂରଚନା c_ପଦସମଷ୍ଟି initializer;
      ବୃକ୍ଷ omp_priv = NULL_ବୃକ୍ଷ, omp_orig = NULL_ବୃକ୍ଷ;
      ତାର୍କିକ bad = ମିଥ୍ୟା;
      initializer.set_error ();
      ଯଦି (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	bad = ସତ୍ୟ;
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      ଯଦି (!bad
	  && (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->ମୂଲ୍ୟ),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  କାଢ଼_scope ();
	  ଠେଲ_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_ଗଣ୍ଠି;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    bad = ସତ୍ୟ;
	  ଅନ୍ୟଥା ଯଦି (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      bad = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି (strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->ମୂଲ୍ୟ),
			   "omp_priv") != 0)
	    {
	      ଯଦି (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_kind != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  bad = ସତ୍ୟ;
		}
	      ଅନ୍ୟଥା
		initializer = c_parser_postfix_expression (parser);
	      ଯଦି (initializer.ମୂଲ୍ୟ
		  && ବୃକ୍ଷ_CODE (initializer.ମୂଲ୍ୟ) == CALL_ପଦସମଷ୍ଟି)
		{
		  ପୂର୍ଣ୍ଣସଂଖ୍ୟା j;
		  ବୃକ୍ଷ c = initializer.ମୂଲ୍ୟ;
		  ପାଇଁ (j = 0; j < call_ପଦସମଷ୍ଟି_nargs (c); j++)
		    {
		      ବୃକ୍ଷ a = CALL_ପଦସମଷ୍ଟି_ARG (c, j);
		      STRIP_NOPS (a);
		      ଯଦି (ବୃକ୍ଷ_CODE (a) == ADDR_ପଦସମଷ୍ଟି
			  && ବୃକ୍ଷ_OPERAND (a, 0) == omp_priv)
			ଭାଙ୍ଗ;
		    }
		  ଯଦି (j == call_ପଦସମଷ୍ଟି_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  ଅନ୍ୟଥା
	    {
	      c_parser_consume_token (parser);
	      ଯଦି (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		bad = ସତ୍ୟ;
	      ଅନ୍ୟଥା
		{
		  ବୃକ୍ଷ st = ଠେଲ_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (ଧାଡ଼ି_table, loc);
		  start_init (omp_priv, NULL_ବୃକ୍ଷ, ମିଥ୍ୟା, ମିଥ୍ୟା, &richloc);
		  ସଂରଚନା c_ପଦସମଷ୍ଟି init = c_parser_initializer (parser, omp_priv);
		  finish_init ();
		  finish_decl (omp_priv, loc, init.ମୂଲ୍ୟ,
		      	       init.original_type, NULL_ବୃକ୍ଷ);
		  କାଢ଼_stmt_list (st);
		}
	    }
	  ଯଦି (!bad
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    bad = ସତ୍ୟ;
	}

      ଯଦି (!bad)
	{
	  c_parser_skip_to_pragma_eol (parser);

	  ବୃକ୍ଷ t = ବୃକ୍ଷ_cons (type, make_ବୃକ୍ଷ_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_SOURCE_LOCATION (omp_out) = rloc;
	  ବୃକ୍ଷ_VEC_ELT (ବୃକ୍ଷ_ମୂଲ୍ୟ (t), 0) = omp_out;
	  ବୃକ୍ଷ_VEC_ELT (ବୃକ୍ଷ_ମୂଲ୍ୟ (t), 1) = omp_in;
	  ବୃକ୍ଷ_VEC_ELT (ବୃକ୍ଷ_ମୂଲ୍ୟ (t), 2) = combiner.ମୂଲ୍ୟ;
	  walk_ବୃକ୍ଷ (&combiner.ମୂଲ୍ୟ, c_check_omp_declare_reduction_r,
		     &ବୃକ୍ଷ_VEC_ELT (ବୃକ୍ଷ_ମୂଲ୍ୟ (t), 0), ଖାଲି);
	  ଯଦି (omp_priv)
	    {
	      DECL_SOURCE_LOCATION (omp_priv) = rloc;
	      ବୃକ୍ଷ_VEC_ELT (ବୃକ୍ଷ_ମୂଲ୍ୟ (t), 3) = omp_priv;
	      ବୃକ୍ଷ_VEC_ELT (ବୃକ୍ଷ_ମୂଲ୍ୟ (t), 4) = omp_orig;
	      ବୃକ୍ଷ_VEC_ELT (ବୃକ୍ଷ_ମୂଲ୍ୟ (t), 5) = initializer.ମୂଲ୍ୟ;
	      walk_ବୃକ୍ଷ (&initializer.ମୂଲ୍ୟ, c_check_omp_declare_reduction_r,
			 &ବୃକ୍ଷ_VEC_ELT (ବୃକ୍ଷ_ମୂଲ୍ୟ (t), 3), ଖାଲି);
	      walk_ବୃକ୍ଷ (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &ବୃକ୍ଷ_VEC_ELT (ବୃକ୍ଷ_ମୂଲ୍ୟ (t), 3), ଖାଲି);
	    }
	}

      କାଢ଼_stmt_list (stmt);
      କାଢ଼_scope ();
      ଯଦି (cfun->language != ଖାଲି)
	{
	  ggc_free (cfun->language);
	  cfun->language = ଖାଲି;
	}
      set_cfun (ଖାଲି);
      current_function_decl = NULL_ବୃକ୍ଷ;
      ଯଦି (nested)
	c_କାଢ଼_function_context ();

      ଯଦି (!clauses.is_empty ())
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}
      ଯଦି (bad)
	ଯାଅ fail;
      ଯଦି (errs != errorcount)
	ଭାଙ୍ଗ;
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

ସ୍ଥିର ତାର୍କିକ
c_parser_omp_declare (c_parser *parser, ଗଣନା pragma_context context)
{
  c_parser_consume_pragma (parser);
  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	}
      ଯଦି (strcmp (p, "reduction") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_reduction (parser, context);
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
      ଯଦି (strcmp (p, "mapper") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_mapper (parser, context);
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
      ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
      ଯଦି (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_target (parser);
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}
      ଯଦି (strcmp (p, "variant") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_to_pragma_eol (parser);
  ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* OpenMP 5.0
   #pragma omp requires clauses[optseq] new-line  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_requires (c_parser *parser)
{
  ଗଣନା omp_requires new_req = (ଗଣନା omp_requires) 0;

  c_parser_consume_pragma (parser);

  location_t loc = c_parser_peek_token (parser)->location;
  ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ଅଚଳ ଅକ୍ଷର *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  ଗଣନା omp_requires this_req = (ଗଣନା omp_requires) 0;

	  ଯଦି (!strcmp (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_ADDRESS;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_MEMORY;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_REVERSE_OFFLOAD;
	  ଅନ୍ୟଥା ଯଦି (!strcmp (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      ଯଦି (parens.require_open (parser))
		{
		  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
		    {
		      ବୃକ୍ଷ v = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
		      p = IDENTIFIER_POINTER (v);

		      ଯଦି (!strcmp (p, "seq_cst"))
			this_req
			  = (ଗଣନା omp_requires) OMP_MEMORY_ORDER_SEQ_CST;
		      ଅନ୍ୟଥା ଯଦି (!strcmp (p, "relaxed"))
			this_req
			  = (ଗଣନା omp_requires) OMP_MEMORY_ORDER_RELAXED;
		      ଅନ୍ୟଥା ଯଦି (!strcmp (p, "release"))
			this_req
			  = (ଗଣନା omp_requires) OMP_MEMORY_ORDER_RELEASE;
		      ଅନ୍ୟଥା ଯଦି (!strcmp (p, "acq_rel"))
			this_req
			  = (ଗଣନା omp_requires) OMP_MEMORY_ORDER_ACQ_REL;
		      ଅନ୍ୟଥା ଯଦି (!strcmp (p, "acquire"))
			this_req
			  = (ଗଣନା omp_requires) OMP_MEMORY_ORDER_ACQUIRE;
		    }
		  ଯଦି (this_req == 0)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<acq_rel%>, %<acquire%>, "
				"%<relaxed%>, %<release%> or %<seq_cst%>");
		      ବାଛ (c_parser_peek_token (parser)->type)
			{
			ସ୍ଥିତି CPP_EOF:
			ସ୍ଥିତି CPP_PRAGMA_EOL:
			ସ୍ଥିତି CPP_CLOSE_PAREN:
			  ଭାଙ୍ଗ;
			ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
			  ଯଦି (c_parser_peek_2nd_token (parser)->type
			      == CPP_CLOSE_PAREN)
			    c_parser_consume_token (parser);
			  ଭାଙ୍ଗ;
			}
		    }
		  ଅନ୍ୟଥା
		    c_parser_consume_token (parser);

		  parens.skip_until_found_close (parser);
		  ଯଦି (this_req == 0)
		    {
		      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
		      ଫେରନ୍ତୁ;
		    }
		}
	      p = ଖାଲି;
	    }
	  ଅନ୍ୟଥା
	    {
	      error_at (cloc, "expected %<unified_address%>, "
			      "%<unified_shared_memory%>, "
			      "%<self_maps%>, "
			      "%<dynamic_allocators%>, "
			       "%<reverse_offload%> "
			       "or %<atomic_default_mem_order%> clause");
	      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	      ଫେରନ୍ତୁ;
	    }
	  ଯଦି (p)
	    c_parser_consume_token (parser);
	  ଯଦି (this_req)
	    {
	      ଯଦି ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  ଯଦି ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  ଯଦି (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_mask & OMP_REQUIRES_TARGET_USED) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      ଅନ୍ୟଥା ଯଦି ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (ଗଣନା omp_requires) 0;
		}
	      ଅନ୍ୟଥା ଯଦି ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (ଗଣନା omp_requires)
		       (omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER);
		}
	      ଅନ୍ୟଥା ଯଦି ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (ଗଣନା omp_requires) (new_req | this_req);
	      omp_requires_mask
		= (ଗଣନା omp_requires) (omp_requires_mask | this_req);
	      ଜାରି;
	    }
	}
      ଭାଙ୍ଗ;
    }
  c_parser_skip_to_pragma_eol (parser);

  ଯଦି (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

ସ୍ଥିର ବୃକ୍ଷ
c_finish_taskloop_clauses (ବୃକ୍ଷ clauses)
{
  ବୃକ୍ଷ *pc = &clauses;
  ପାଇଁ (ବୃକ୍ଷ c = clauses; c; c = *pc)
    {
      ତାର୍କିକ remove = ମିଥ୍ୟା;
      ଯଦି (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
	{
	  ବୃକ୍ଷ type = strip_array_types (ବୃକ୍ଷ_TYPE (OMP_CLAUSE_DECL (c)));
	  ଯଦି (integer_zerop (TYPE_SIZE_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      remove = ସତ୍ୟ;
	    }
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      remove = ସତ୍ୟ;
	    }
	}
      ଯଦି (remove)
	*pc = OMP_CLAUSE_CHAIN (c);
      ଅନ୍ୟଥା
	pc = &OMP_CLAUSE_CHAIN (c);
    }
  ଫେରନ୍ତୁ clauses;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ଅଙ୍କ_TASKS)	\
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       ଅକ୍ଷର *p_name, omp_clause_mask mask, ବୃକ୍ଷ *cclauses,
		       ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ clauses, block, ret;

  strcat (p_name, " taskloop");
  mask |= OMP_TASKLOOP_CLAUSE_MASK;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  ଯଦି ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ଅଙ୍କ_THREADS)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IN_REDUCTION);

  ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
    {
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);

      ଯଦି (strcmp (p, "simd") == 0)
	{
	  ବୃକ୍ଷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ଗଣନା];
	  ଯଦି (cclauses == ଖାଲି)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
	    ଫେରନ୍ତୁ c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (ସତ୍ୟ);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
	  ଯଦି (ret == ଖାଲି)
	    ଫେରନ୍ତୁ ret;
	  ret = make_ଗଣ୍ଠି (OMP_TASKLOOP);
	  ବୃକ୍ଷ_TYPE (ret) = void_type_ଗଣ୍ଠି;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_finish_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  SET_ପଦସମଷ୍ଟି_LOCATION (ret, loc);
	  add_stmt (ret);
	  ଫେରନ୍ତୁ ret;
	}
    }
  ଯଦି (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ଖାଲି);
  ଯଦି (cclauses)
    {
      omp_split_clauses (loc, OMP_TASKLOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
    }

  clauses = c_finish_taskloop_clauses (clauses);
  block = c_begin_compound_stmt (ସତ୍ୟ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, ଖାଲି, if_p);
  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
  add_stmt (block);

  ଫେରନ୍ତୁ ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  ବୃକ୍ଷ sizes = NULL_ବୃକ୍ଷ;

  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  ଯଦି (tok->type != CPP_NAME
      || strcmp ("sizes", IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  ଯଦି (!parens.require_open (parser))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  vec<ବୃକ୍ଷ, va_gc> *sizes_vec
    = c_parser_ପଦସମଷ୍ଟି_list (parser, ସତ୍ୟ, ସତ୍ୟ, ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି);
  sizes = build_ବୃକ୍ଷ_list_vec (sizes_vec);
  release_ବୃକ୍ଷ_vector (sizes_vec);

  ପାଇଁ (ବୃକ୍ଷ s = sizes; s; s = ବୃକ୍ଷ_CHAIN (s))
    {
      ବୃକ୍ଷ ପଦସମଷ୍ଟି = ବୃକ୍ଷ_ମୂଲ୍ୟ (s);
      ଯଦି (ପଦସମଷ୍ଟି == error_mark_ଗଣ୍ଠି)
	{
	  parens.skip_until_found_close (parser);
	  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	}

      HOST_WIDE_INT n;
      ଯଦି (!INTEGRAL_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି))
	  || !ବୃକ୍ଷ_fits_shwi_p (ପଦସମଷ୍ଟି)
	  || (n = ବୃକ୍ଷ_to_shwi (ପଦସମଷ୍ଟି)) <= 0
	  || (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  ବୃକ୍ଷ_ମୂଲ୍ୟ (s) = integer_one_ଗଣ୍ଠି;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  ବୃକ୍ଷ c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  ଫେରନ୍ତୁ c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_tile (location_t loc, c_parser *parser, ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_to_pragma_eol (parser);

  ଯଦି (!clauses || clauses == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ବୃକ୍ଷ block = c_begin_compound_stmt (ସତ୍ୟ);
  ବୃକ୍ଷ ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    ଖାଲି, if_p);
  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
  add_stmt (block);

  ଫେରନ୍ତୁ ret;
}

#define OMP_UNROLL_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FULL))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_omp_unroll (location_t loc, c_parser *parser, ତାର୍କିକ *if_p)
{
  ବୃକ୍ଷ clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_MASK,
					   "#pragma omp unroll", ସତ୍ୟ);

  ବୃକ୍ଷ block = c_begin_compound_stmt (ସତ୍ୟ);
  ବୃକ୍ଷ ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    ଖାଲି, if_p);
  block = c_end_compound_stmt (loc, block, ସତ୍ୟ);
  add_stmt (block);

  ଫେରନ୍ତୁ ret;
}

/* OpenMP 5.1
   #pragma omp nothing new-line  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_nothing (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp error clauses[optseq] new-line  */

ସ୍ଥିର ତାର୍କିକ
c_parser_omp_error (c_parser *parser, ଗଣନା pragma_context context)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା at_compilation = -1;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା severity_fatal = -1;
  ବୃକ୍ଷ message = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ bad = ମିଥ୍ୟା;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ଯଦି (!c_parser_next_token_is (parser, CPP_NAME))
	ଭାଙ୍ଗ;

      ଅଚଳ ଅକ୍ଷର *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      location_t cloc = c_parser_peek_token (parser)->location;
      ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *args[] = {
	"execution", "compilation", "warning", "fatal"
      };
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା *v = ଖାଲି;
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା idx = 0, n = -1;
      ବୃକ୍ଷ m = NULL_ବୃକ୍ଷ;

      ଯଦି (!strcmp (p, "at"))
	v = &at_compilation;
      ଅନ୍ୟଥା ଯଦି (!strcmp (p, "severity"))
	{
	  v = &severity_fatal;
	  idx += 2;
	}
      ଅନ୍ୟଥା ଯଦି (strcmp (p, "message"))
	{
	  error_at (cloc,
		    "expected %<at%>, %<severity%> or %<message%> clause");
	  c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
	  ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      ଯଦି (parens.require_open (parser))
	{
	  ଯଦି (v == ଖାଲି)
	    {
	      location_t ପଦସମଷ୍ଟି_loc = c_parser_peek_token (parser)->location;
	      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	      ପଦସମଷ୍ଟି = convert_lvalue_to_rvalue (ପଦସମଷ୍ଟି_loc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ସତ୍ୟ);
	      m = convert (const_string_type_ଗଣ୍ଠି, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	      m = c_fully_fold (m, ମିଥ୍ୟା, ଖାଲି);
	    }
	  ଅନ୍ୟଥା
	    {
	      ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
		{
		  ବୃକ୍ଷ val = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
		  ଅଚଳ ଅକ୍ଷର *q = IDENTIFIER_POINTER (val);

		  ଯଦି (!strcmp (q, args[idx]))
		    n = 0;
		  ଅନ୍ୟଥା ଯଦି (!strcmp (q, args[idx + 1]))
		    n = 1;
		}
	      ଯଦି (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", args[idx], args[idx + 1]);
		  bad = ସତ୍ୟ;
		  ବାଛ (c_parser_peek_token (parser)->type)
		    {
		    ସ୍ଥିତି CPP_EOF:
		    ସ୍ଥିତି CPP_PRAGMA_EOL:
		    ସ୍ଥିତି CPP_CLOSE_PAREN:
		      ଭାଙ୍ଗ;
		    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		      ଯଦି (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)
			c_parser_consume_token (parser);
		      ଭାଙ୍ଗ;
		    }
		}
	      ଅନ୍ୟଥା
		c_parser_consume_token (parser);
	    }

	  parens.skip_until_found_close (parser);

	  ଯଦି (v == ଖାଲି)
	    {
	      ଯଦି (message)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = ସତ୍ୟ;
		}
	      ଅନ୍ୟଥା
		message = m;
	    }
	  ଅନ୍ୟଥା ଯଦି (n != -1)
	    {
	      ଯଦି (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = ସତ୍ୟ;
		}
	      ଅନ୍ୟଥା
		*v = n;
	    }
	}
      ଅନ୍ୟଥା
	bad = ସତ୍ୟ;
    }
  c_parser_skip_to_pragma_eol (parser);
  ଯଦି (bad)
    ଫେରନ୍ତୁ ସତ୍ୟ;

  ଯଦି (at_compilation == -1)
    at_compilation = 1;
  ଯଦି (severity_fatal == -1)
    severity_fatal = 1;
  ଯଦି (!at_compilation)
    {
      ଯଦି (context != pragma_compound)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may only be used in compound statements");
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	}
      ଯଦି (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->in_intervening_code)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->fail = ସତ୍ୟ;
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	}
      ବୃକ୍ଷ fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_IN_GOMP_ERROR
						: BUILT_IN_GOMP_WARNING);
      ଯଦି (!message)
	message = build_zero_cst (const_string_type_ଗଣ୍ଠି);
      ବୃକ୍ଷ stmt = build_call_ପଦସମଷ୍ଟି_loc (loc, fndecl, 2, message,
				       build_all_ones_cst (size_type_ଗଣ୍ଠି));
      add_stmt (stmt);
      ଫେରନ୍ତୁ ସତ୍ୟ;
    }
  ଅଚଳ ଅକ୍ଷର *ସନ୍ଦେଶ = ଖାଲି;
  ଯଦି (message)
    {
      ସନ୍ଦେଶ = c_getstr (message);
      ଯଦି (ସନ୍ଦେଶ == ଖାଲି)
	ସନ୍ଦେଶ = _("<message unknown at compile time>");
    }
  ଅଚଳ ଗଣନା diagnostics::kind diag_kind = (severity_fatal
					    ? diagnostics::kind::error
					    : diagnostics::kind::warning);
  ଯଦି (ସନ୍ଦେଶ)
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered: %s", ସନ୍ଦେଶ);
  ଅନ୍ୟଥା
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered");
  ଫେରନ୍ତୁ ମିଥ୍ୟା;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_assumption_clauses (c_parser *parser, ତାର୍କିକ is_assume)
{
  ତାର୍କିକ no_openmp = ମିଥ୍ୟା;
  ତାର୍କିକ no_openmp_constructs = ମିଥ୍ୟା;
  ତାର୍କିକ no_openmp_routines = ମିଥ୍ୟା;
  ତାର୍କିକ no_parallelism = ମିଥ୍ୟା;
  bitmap_head absent_head, contains_head;

  bitmap_obstack_initialize (ଖାଲି);
  bitmap_initialize (&absent_head, &bitmap_default_obstack);
  bitmap_initialize (&contains_head, &bitmap_default_obstack);

  ଯଦି (c_parser_next_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ଯଦି (!c_parser_next_token_is (parser, CPP_NAME))
	ଭାଙ୍ଗ;

      ଅଚଳ ଅକ୍ଷର *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      location_t cloc = c_parser_peek_token (parser)->location;

      ଯଦି (!strcmp (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  ଯଦି (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = ସତ୍ୟ;
	}
      ଅନ୍ୟଥା ଯଦି (!strcmp (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  ଯଦି (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = ସତ୍ୟ;
	}
      ଅନ୍ୟଥା ଯଦି (!strcmp (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  ଯଦି (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = ସତ୍ୟ;
	}
      ଅନ୍ୟଥା ଯଦି (!strcmp (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  ଯଦି (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = ସତ୍ୟ;
	}
      ଅନ୍ୟଥା ଯଦି (!strcmp (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  ଯଦି (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_ପଦସମଷ୍ଟି_no_commas (parser, ଖାଲି);
	      ବୃକ୍ଷ t = convert_lvalue_to_rvalue (eloc, ପଦସମଷ୍ଟି, ସତ୍ୟ, ସତ୍ୟ).ମୂଲ୍ୟ;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, ମିଥ୍ୟା, ଖାଲି);
	      ଯଦି (is_assume && t != error_mark_ଗଣ୍ଠି)
		{
		  ବୃକ୍ଷ fn = build_call_ପଦସମଷ୍ଟି_internal_loc (eloc, IFN_ASSUME,
							  void_type_ଗଣ୍ଠି, 1,
							  t);
		  add_stmt (fn);
		}
	      parens.skip_until_found_close (parser);
	    }
	}
      ଅନ୍ୟଥା ଯଦି (!strcmp (p, "absent") || !strcmp (p, "contains"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  ଯଦି (parens.require_open (parser))
	    {
	      କର
		{
		  ଅଚଳ ଅକ୍ଷର *directive[3] = {};
		  ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
		  location_t dloc = c_parser_peek_token (parser)->location;
		  ପାଇଁ (i = 0; i < 3; i++)
		    {
		      ବୃକ୍ଷ id;
		      ଯଦି (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->ମୂଲ୍ୟ;
		      ଅନ୍ୟଥା ଯଦି (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  ଗଣନା rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      ଅନ୍ୟଥା
			ଭାଙ୍ଗ;
		      directive[i] = IDENTIFIER_POINTER (id);
		    }
		  ଯଦି (i == 0)
		    error_at (dloc, "expected directive name");
		  ଅନ୍ୟଥା
		    {
		      ଅଚଳ ସଂରଚନା c_omp_directive *dir
			= c_omp_categorize_directive (directive[0],
						      directive[1],
						      directive[2]);
		      ଯଦି (dir
			  && dir->id != PRAGMA_OMP_END
			  && (dir->kind == C_OMP_DIR_DECLARATIVE
			      || dir->kind == C_OMP_DIR_INFORMATIONAL
			      || dir->kind == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      ଅନ୍ୟଥା ଯଦି (dir == ଖାଲି
			       || dir->id == PRAGMA_OMP_END
			       || (!dir->second && directive[1])
			       || (!dir->third && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      ଅନ୍ୟଥା
			{
			  ପୂର୍ଣ୍ଣସଂଖ୍ୟା id = dir - c_omp_directives;
			  ଯଦି (bitmap_bit_p (p[0] == 'a' ? &contains_head
							: &absent_head, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  ଅନ୍ୟଥା ଯଦି (!bitmap_set_bit (p[0] == 'a'
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
		      ପାଇଁ (; i; --i)
			c_parser_consume_token (parser);
		    }
		  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  ଅନ୍ୟଥା
		    ଭାଙ୍ଗ;
		}
	      ଯେତେବେଳେ (1);
	      parens.skip_until_found_close (parser);
	    }
	}
      ଅନ୍ୟଥା ଯଦି (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      matching_parens parens;
	      parens.consume_open (parser);
	      c_parser_balanced_token_sequence (parser);
	      parens.require_close (parser);
	    }
	}
      ଅନ୍ୟଥା
	{
	  c_parser_consume_token (parser);
	  error_at (cloc, "expected assumption clause");
	  ଭାଙ୍ଗ;
	}
    }
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_assume (c_parser *parser, ତାର୍କିକ *if_p)
{
  c_parser_omp_assumption_clauses (parser, ସତ୍ୟ);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
}

/* OpenMP 5.1
   #pragma omp assumes clauses[optseq] new-line  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_assumes (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_omp_assumption_clauses (parser, ମିଥ୍ୟା);
}

/* Helper function for c_parser_omp_metadirective.  */

ସ୍ଥିର ଶୂନ୍ୟ
analyze_metadirective_body (c_parser *parser,
			    vec<c_token> &tokens,
			    vec<ବୃକ୍ଷ> &labels)
{
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା nesting_depth = 0;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା bracket_depth = 0;
  ତାର୍କିକ ignore_label = ମିଥ୍ୟା;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  ଯେତେବେଳେ (1)
    {
      c_token *token = c_parser_peek_token (parser);
      ତାର୍କିକ stop = ମିଥ୍ୟା;

      ଯଦି (c_parser_next_token_is_keyword (parser, RID_CASE))
	ignore_label = ସତ୍ୟ;

      ବାଛ (token->type)
	{
	ସ୍ଥିତି CPP_EOF:
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_NAME:
	  ଯଦି (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.safe_ଠେଲ (token->ମୂଲ୍ୟ);
	  ଯାଅ add;
	ସ୍ଥିତି CPP_OPEN_BRACE:
	  ++nesting_depth;
	  ଯାଅ add;
	ସ୍ଥିତି CPP_CLOSE_BRACE:
	  ଯଦି (--nesting_depth == 0 && bracket_depth == 0)
	    stop = ସତ୍ୟ;
	  ଯାଅ add;
	ସ୍ଥିତି CPP_OPEN_PAREN:
	  ++bracket_depth;
	  ଯାଅ add;
	ସ୍ଥିତି CPP_CLOSE_PAREN:
	  --bracket_depth;
	  ଯାଅ add;
	ସ୍ଥିତି CPP_COLON:
	  ignore_label = ମିଥ୍ୟା;
	  ଯାଅ add;
	ସ୍ଥିତି CPP_SEMICOLON:
	  ଯଦି (nesting_depth == 0 && bracket_depth == 0)
	    stop = ସତ୍ୟ;
	  ଯାଅ add;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	add:
	  tokens.safe_ଠେଲ (*token);
	  ଯଦି (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  ଅନ୍ୟଥା ଯଦି (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_to_pragma_eol (parser);
	  ଅନ୍ୟଥା
	    c_parser_consume_token (parser);
	  ଯଦି (stop)
	    ଭାଙ୍ଗ;
	  ଜାରି;
	}
      ଭାଙ୍ଗ;
    }
}

/* OpenMP 5.0:

  # pragma omp metadirective [clause[, clause]]
*/

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_metadirective (c_parser *parser, ତାର୍କିକ *if_p)
{
  ସ୍ଥିର unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା metadirective_region_ଗଣନା = 0;

  ବୃକ୍ଷ ret;
  auto_vec<c_token> directive_tokens;
  auto_vec<c_token> body_tokens;
  auto_vec<ବୃକ୍ଷ> body_labels;
  auto_vec<ଅଚଳ ସଂରଚନା c_omp_directive *> directives;
  auto_vec<ବୃକ୍ଷ> ctxs;
  vec<ସଂରଚନା omp_variant> candidates;
  ତାର୍କିକ default_seen = ମିଥ୍ୟା;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା directive_token_idx = 0;
  ବୃକ୍ଷ standalone_body = NULL_ବୃକ୍ଷ;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  ତାର୍କିକ requires_body = ମିଥ୍ୟା;

  ret = make_ଗଣ୍ଠି (OMP_METADIRECTIVE);
  SET_ପଦସମଷ୍ଟି_LOCATION (ret, pragma_loc);
  ବୃକ୍ଷ_TYPE (ret) = void_type_ଗଣ୍ଠି;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_ବୃକ୍ଷ;

  c_parser_consume_pragma (parser);
  ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ଯଦି (c_parser_next_token_is_not (parser, CPP_NAME)
	  && c_parser_next_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  ଯାଅ error;
	}

      location_t match_loc = c_parser_peek_token (parser)->location;
      ଅଚଳ ଅକ୍ଷର *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      ଯଦି (strcmp (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.add_fixit_replace (match_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      ତାର୍କିକ default_p
	= strcmp (p, "default") == 0 || strcmp (p, "otherwise") == 0;
      ଯଦି (default_p)
	{
	  ଯଦି (default_seen)
	    {
	      error_at (match_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      ଯାଅ error;
	    }
	  default_seen = ସତ୍ୟ;
	}
      ଅନ୍ୟଥା ଯଦି (default_seen)
	{
	  error_at (match_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  ଯାଅ error;
	}
      ଯଦି (!default_p && strcmp (p, "when") != 0)
	{
	  error_at (match_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  ଯାଅ error;
	}

      matching_parens parens;
      ବୃକ୍ଷ ctx = NULL_ବୃକ୍ଷ;
      ତାର୍କିକ skip = ମିଥ୍ୟା;

      ଯଦି (!parens.require_open (parser))
	ଯାଅ error;

      ଯଦି (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_ବୃକ୍ଷ);
	  ଯଦି (ctx == error_mark_ଗଣ୍ଠି)
	    ଯାଅ error;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  ଯଦି (ctx == error_mark_ଗଣ୍ଠି)
	    ଯାଅ error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_ବୃକ୍ଷ, ମିଥ୍ୟା) == 0);

	  ଯଦି (c_parser_next_token_is_not (parser, CPP_COLON))
	    {
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      ଯାଅ error;
	    }
	  c_parser_consume_token (parser);
	}

      /* Read in the directive type and create a dummy pragma token for
	 it.  */
      location_t loc = c_parser_peek_token (parser)->location;

      ଅଚଳ ଅକ୍ଷର *directive[3] = {};
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
      ପାଇଁ (i = 0; i < 3; i++)
	{
	  ବୃକ୍ଷ id;
	  ଯଦି (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      ଯଦି (i == 0)
		directive[i++] = "nothing";
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା ଯଦି (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->ମୂଲ୍ୟ;
	  ଅନ୍ୟଥା ଯଦି (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      ଗଣନା rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  ଅନ୍ୟଥା
	    ଭାଙ୍ଗ;

	  directive[i] = IDENTIFIER_POINTER (id);
	}
      ଯଦି (i == 0)
	{
	  error_at (loc, "expected directive name");
	  ଯାଅ error;
	}

      ଅଚଳ ସଂରଚନା c_omp_directive *omp_directive
	= c_omp_categorize_directive (directive[0],
				      directive[1],
				      directive[2]);

      ଯଦି (omp_directive == ଖାଲି)
	{
	  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < i; j++)
	    c_parser_consume_token (parser);
	  c_parser_error (parser, "unknown directive name");
	  ଯାଅ error;
	}
      ଅନ୍ୟଥା
	{
	  ପୂର୍ଣ୍ଣସଂଖ୍ୟା token_ଗଣନା = 0;
	  ଯଦି (omp_directive->first) token_ଗଣନା++;
	  ଯଦି (omp_directive->second) token_ଗଣନା++;
	  ଯଦି (omp_directive->third) token_ଗଣନା++;
	  ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < token_ଗଣନା; j++)
	    c_parser_consume_token (parser);
	}
      ଯଦି (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  ଯାଅ error;
	}
      ଯଦି (omp_directive->kind == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  ଯାଅ error;
	}
      ଯଦି (omp_directive->kind == C_OMP_DIR_CONSTRUCT)
	requires_body = ସତ୍ୟ;

      ଯଦି (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_kind = (ଗଣନା pragma_kind) omp_directive->id;

	  directives.safe_ଠେଲ (omp_directive);
	  directive_tokens.safe_ଠେଲ (pragma_token);
	  ctxs.safe_ଠେଲ (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା nesting_depth = 0;
      ଯେତେବେଳେ (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ବାଛ (token->type)
	    {
	    ସ୍ଥିତି CPP_EOF:
	    ସ୍ଥିତି CPP_PRAGMA_EOL:
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି CPP_OPEN_PAREN:
	      ++nesting_depth;
	      ଯାଅ add;
	    ସ୍ଥିତି CPP_CLOSE_PAREN:
	      ଯଦି (nesting_depth-- == 0)
		{
		  c_parser_consume_token (parser);
		  ଭାଙ୍ଗ;
		}
	      ଯାଅ add;
	    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	    add:
	      ଯଦି (!skip)
		directive_tokens.safe_ଠେଲ (*token);
	      c_parser_consume_token (parser);
	      ଜାରି;
	    }
	  ଭାଙ୍ଗ;
	}

      ଯଦି (!skip)
	{
	  c_token eol_token;
	  memset (&eol_token, 0, ଆକାର (eol_token));
	  eol_token.type = CPP_PRAGMA_EOL;
	  directive_tokens.safe_ଠେଲ (eol_token);
	}
    }
  c_parser_skip_to_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  ଯଦି (ctxs.length () == 1)
    {
      ବୃକ୍ଷ ctx = ctxs[0];
      ଯଦି (ctx == NULL_ବୃକ୍ଷ
	  || (omp_context_selector_matches (ctx, NULL_ବୃକ୍ଷ, ମିଥ୍ୟା) == 1
	      && directive_tokens[0].pragma_kind == PRAGMA_OMP_NOTHING))
	ଫେରନ୍ତୁ;
    }

  ଯଦି (!default_seen)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      ଅଚଳ ସଂରଚନା c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", ଖାଲି, ଖାଲି);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_kind = PRAGMA_OMP_NOTHING;

      directives.safe_ଠେଲ (omp_directive);
      directive_tokens.safe_ଠେଲ (pragma_token);
      ctxs.safe_ଠେଲ (NULL_ବୃକ୍ଷ);

      c_token eol_token;
      memset (&eol_token, 0, ଆକାର (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_tokens.safe_ଠେଲ (eol_token);
    }

  ଯଦି (requires_body)
    analyze_metadirective_body (parser, body_tokens, body_labels);

  /* Process each candidate directive.  */
  unsigned i;
  ବୃକ୍ଷ ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> tokens;

      /* Add the directive tokens.  */
      କର
	tokens.safe_ଠେଲ (directive_tokens [directive_token_idx++]);
      ଯେତେବେଳେ (tokens.last ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_tokens.is_empty ());
      ପାଇଁ (unsigned j = 0; j < body_tokens.length (); j++)
	tokens.safe_ଠେଲ (body_tokens[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, ଆକାର (eof_token));
      eof_token.type = CPP_EOF;
      tokens.safe_ଠେଲ (eof_token);
      tokens.safe_ଠେଲ (eof_token);

      unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା old_tokens_avail = parser->tokens_avail;
      c_token *old_tokens = parser->tokens;
      ସଂରଚନା omp_attribute_pragma_state *old_in_omp_attribute_pragma
	= parser->in_omp_attribute_pragma;
      ସଂରଚନା omp_metadirective_parse_data *old_state
	= parser->omp_metadirective_state;

      ସଂରଚନା omp_metadirective_parse_data new_state;
      new_state.body_labels = &body_labels;
      new_state.region_ଅଙ୍କ = ++metadirective_region_ଗଣନା;

      parser->tokens = tokens.address ();
      parser->tokens_avail = tokens.length ();
      parser->in_omp_attribute_pragma = ଖାଲି;
      parser->omp_metadirective_state = &new_state;

      ପୂର୍ଣ୍ଣସଂଖ୍ୟା prev_errorcount = errorcount;
      ବୃକ୍ଷ directive = c_begin_compound_stmt (ସତ୍ୟ);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_ବୃକ୍ଷ);
      directive = c_end_compound_stmt (pragma_loc, directive, ସତ୍ୟ);
      ତାର୍କିକ standalone_p
	= directives[i]->kind == C_OMP_DIR_STANDALONE
	  || directives[i]->kind == C_OMP_DIR_UTILITY;
      ଯଦି (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  ଯଦି (standalone_body == NULL_ବୃକ୍ଷ)
	    {
	      standalone_body = ଠେଲ_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = କାଢ଼_stmt_list (standalone_body);
	    }
	  ଅନ୍ୟଥା
	    c_parser_skip_to_end_of_block_or_statement (parser, ସତ୍ୟ);
	}

      ବୃକ୍ଷ body = standalone_p ? standalone_body : NULL_ବୃକ୍ଷ;
      ବୃକ୍ଷ variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      ଯଦି (errorcount == prev_errorcount)
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
  ଯଦି (!candidates.is_empty ())
    ret = c_omp_expand_variant_construct (candidates);

  add_stmt (ret);
  ଫେରନ୍ତୁ;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  ଯଦି (parser->in_pragma)
    c_parser_skip_to_pragma_eol (parser, ମିଥ୍ୟା);
}

/* Main entry point to parsing most OpenMP pragmas.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_construct (c_parser *parser, ତାର୍କିକ *if_p)
{
  ଗଣନା pragma_kind p_kind;
  location_t loc;
  ବୃକ୍ଷ stmt;
  ଅକ୍ଷର p_name[ଆକାର "#pragma omp teams distribute parallel for simd"];
  omp_clause_mask mask (0);

  loc = c_parser_peek_token (parser)->location;
  p_kind = c_parser_peek_token (parser)->pragma_kind;
  c_parser_consume_pragma (parser);

  ବାଛ (p_kind)
    {
    ସ୍ଥିତି PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, ସତ୍ୟ);
      ଫେରନ୍ତୁ;
    ସ୍ଥିତି PRAGMA_OACC_CACHE:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_DATA:
      stmt = c_parser_oacc_data (loc, parser, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_HOST_DATA:
      stmt = c_parser_oacc_host_data (loc, parser, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_KERNELS:
    ସ୍ଥିତି PRAGMA_OACC_PARALLEL:
    ସ୍ଥିତି PRAGMA_OACC_SERIAL:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_kind, p_name, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_LOOP:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, mask, ଖାଲି, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OACC_WAIT:
      strcpy (p_name, "#pragma wait");
      stmt = c_parser_oacc_wait (loc, parser, p_name);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (loc, parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ;
    ସ୍ଥିତି PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (loc, parser, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_DISTRIBUTE:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_distribute (loc, parser, p_name, mask, ଖାଲି, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_FOR:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, mask, ଖାଲି, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_LOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, mask, ଖାଲି, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_MASKED:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, mask, ଖାଲି, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_MASTER:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, mask, ଖାଲି, if_p,
				  UNKNOWN_LOCATION);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_PARALLEL:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, mask, ଖାଲି, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_SECTIONS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, mask, ଖାଲି);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_SIMD:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, mask, ଖାଲି, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (loc, parser, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_TASK:
      stmt = c_parser_omp_task (loc, parser, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_TASKGROUP:
      stmt = c_parser_omp_taskgroup (loc, parser, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_TASKLOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_taskloop (loc, parser, p_name, mask, ଖାଲି, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_TEAMS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, mask, ଖାଲି, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_ASSUME:
      c_parser_omp_assume (parser, if_p);
      ଫେରନ୍ତୁ;
    ସ୍ଥିତି PRAGMA_OMP_TILE:
      stmt = c_parser_omp_tile (loc, parser, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_UNROLL:
      stmt = c_parser_omp_unroll (loc, parser, if_p);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି PRAGMA_OMP_DISPATCH:
      stmt = c_parser_omp_dispatch (loc, parser);
      ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      gcc_unreachable ();
    }

  ଯଦି (stmt && stmt != error_mark_ଗଣ୍ଠି)
    gcc_assert (ପଦସମଷ୍ଟି_LOCATION (stmt) != UNKNOWN_LOCATION);
}

/* OpenMP 6.0:
   # pragma omp groupprivate (variable-list) [device_type(...)]  */

#define OMP_GROUPPRIVATE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE) )

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_groupprivate (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  ବୃକ୍ଷ vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ଖାଲି);
  ବୃକ୍ଷ clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_MASK,
					   "#pragma omp groupprivate");
  /* TODO: Implies 'declare target local' with specified device_type, check for
     conflicts.  Check for other restrictions.  */
  (ଶୂନ୍ୟ) vars;
  (ଶୂନ୍ୟ) clauses;
  sorry_at (loc, "%<omp groupprivate%>");
}

/* OpenMP 2.5:
   # pragma omp threadprivate (variable-list) */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_omp_threadprivate (c_parser *parser)
{
  ବୃକ୍ଷ vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ଖାଲି);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  ପାଇଁ (t = vars; t; t = ବୃକ୍ଷ_CHAIN (t))
    {
      ବୃକ୍ଷ v = ବୃକ୍ଷ_PURPOSE (t);
      loc = ପଦସମଷ୍ଟି_LOCATION (ବୃକ୍ଷ_ମୂଲ୍ୟ (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      ଯଦି (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_USED (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      ଅନ୍ୟଥା ଯଦି (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_TYPE (v) == error_mark_ଗଣ୍ଠି)
	;
      ଅନ୍ୟଥା ଯଦି (! COMPLETE_TYPE_P (ବୃକ୍ଷ_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      ଅନ୍ୟଥା
	{
	  ଯଦି (! DECL_THREAD_LOCAL_P (v))
	    {
	      set_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      ଯଦି (DECL_RTL_SET_P (v))
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

ସ୍ଥିର ବୃକ୍ଷ
c_parser_transaction_attributes (c_parser *parser)
{
  ଯଦି (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    ଫେରନ୍ତୁ c_parser_gnu_attributes (parser);

  ଯଦି (!c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  ଫେରନ୍ତୁ c_parser_std_attribute_specifier (parser, ସତ୍ୟ);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_transaction (c_parser *parser, ଗଣନା rid keyword)
{
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା old_in = parser->in_transaction;
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା this_in = 1, new_in;
  location_t loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  ଯଦି (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  ଅନ୍ୟଥା
    {
      attrs = c_parser_transaction_attributes (parser);
      ଯଦି (attrs)
	this_in |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_in = this_in | (old_in & TM_STMT_ATTR_OUTER);

  parser->in_transaction = new_in;
  stmt = c_parser_compound_statement (parser);
  parser->in_transaction = old_in;

  ଯଦି (flag_tm)
    stmt = c_finish_transaction (loc, stmt, this_in);
  ଅନ୍ୟଥା
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  ଫେରନ୍ତୁ stmt;
}

/* Parse a __transaction_atomic or __transaction_relaxed expression
   (GCC Extension).

   transaction-expression:
     __transaction_atomic ( expression )
     __transaction_relaxed ( expression )
*/

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_transaction_expression (c_parser *parser, ଗଣନା rid keyword)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା old_in = parser->in_transaction;
  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା this_in = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  ଯଦି (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  ଅନ୍ୟଥା
    {
      attrs = c_parser_transaction_attributes (parser);
      ଯଦି (attrs)
	this_in |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->in_transaction = this_in;
  matching_parens parens;
  ଯଦି (parens.require_open (parser))
    {
      ବୃକ୍ଷ ପଦସମଷ୍ଟି = c_parser_expression (parser).ମୂଲ୍ୟ;
      ret.original_type = ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି);
      ret.ମୂଲ୍ୟ = build1 (TRANSACTION_ପଦସମଷ୍ଟି, ret.original_type, ପଦସମଷ୍ଟି);
      ଯଦି (this_in & TM_STMT_ATTR_RELAXED)
	TRANSACTION_ପଦସମଷ୍ଟି_RELAXED (ret.ମୂଲ୍ୟ) = 1;
      SET_ପଦସମଷ୍ଟି_LOCATION (ret.ମୂଲ୍ୟ, loc);
      ret.original_code = TRANSACTION_ପଦସମଷ୍ଟି;
      ret.m_decimal = 0;
      ଯଦି (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ଖାଲି);
	  ଯାଅ error;
	}
    }
  ଅନ୍ୟଥା
    {
     error:
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = ଖାଲି;
    }
  parser->in_transaction = old_in;

  ଯଦି (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  set_c_ପଦସମଷ୍ଟି_source_range (&ret, loc, loc);

  ଫେରନ୍ତୁ ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

ସ୍ଥିର ବୃକ୍ଷ
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ବୃକ୍ଷ attrs;
  ତାର୍କିକ is_outer = ମିଥ୍ୟା;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_attributes (parser);
  ଯଦି (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  ଯଦି (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      ଯାଅ ret_error;
    }
  ଅନ୍ୟଥା ଯଦି (parser->in_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      ଯାଅ ret_error;
    }
  ଅନ୍ୟଥା ଯଦି (is_outer)
    {
      ଯଦି ((parser->in_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  ଯାଅ ret_error;
	}
    }
  ଅନ୍ୟଥା ଯଦି (parser->in_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      ଯାଅ ret_error;
    }

  ଫେରନ୍ତୁ add_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  ଫେରନ୍ତୁ build1 (NOP_ପଦସମଷ୍ଟି, void_type_ଗଣ୍ଠି, error_mark_ଗଣ୍ଠି);
}

/* Parse a single source file.  */

ଶୂନ୍ୟ
c_parse_file (ଶୂନ୍ୟ)
{
  /* Use local storage to begin.  If the first token is a pragma, parse it.
     If it is #pragma GCC pch_preprocess, then this will load a PCH file
     which will cause garbage collection.  */
  c_parser tparser;

  memset (&tparser, 0, ଆକାର tparser);
  tparser.translate_strings_p = ସତ୍ୟ;
  tparser.tokens = &tparser.tokens_buf[0];
  the_parser = &tparser;

  ଯଦି (c_parser_peek_token (&tparser)->pragma_kind == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  ଅନ୍ୟଥା
    c_common_no_more_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  ଯଦି (tparser.tokens == &tparser.tokens_buf[0])
    the_parser->tokens = &the_parser->tokens_buf[0];

  /* Initialize EH, if we've been told to do so.  */
  ଯଦି (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = ଖାଲି;
}

ଶୂନ୍ୟ
c_init_preprocess (ଶୂନ୍ୟ)
{
  /* Create a parser for use by pragma_lex during preprocessing.  */
  the_parser = ggc_alloc<c_parser> ();
  memset (the_parser, 0, ଆକାର (c_parser));
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
c_parser_parse_rtl_body (c_parser *parser, ଅକ୍ଷର *start_with_pass)
{
  ଯଦି (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      ମୁକ୍ତ (start_with_pass);
      ଫେରନ୍ତୁ c_parser_peek_token (parser)->location;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_open_braces = 1;
  ଯେତେବେଳେ (1)
    {
      ବାଛ (c_parser_peek_token (parser)->type)
	{
	ସ୍ଥିତି CPP_OPEN_BRACE:
	  ଅଙ୍କ_open_braces++;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_CLOSE_BRACE:
	  ଯଦି (--ଅଙ୍କ_open_braces == 0)
	    ଯାଅ found_closing_brace;
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_EOF:
	  error_at (start_loc, "no closing brace");
	  ମୁକ୍ତ (start_with_pass);
	  ଫେରନ୍ତୁ c_parser_peek_token (parser)->location;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଭାଙ୍ଗ;
	}
      c_parser_consume_token (parser);
    }

 found_closing_brace:
  /* At the closing brace; record its location.  */
  location_t end_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  ଯଦି (!read_rtl_function_body_from_file_range (start_loc, end_loc))
    {
      ମୁକ୍ତ (start_with_pass);
      ଫେରନ୍ତୁ end_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  run_rtl_passes (start_with_pass);
  ଫେରନ୍ତୁ end_loc;
}

#ଅନ୍ତର୍ଭାଵ "gt-c-c-parser.h"
