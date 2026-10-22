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

#ಅನ್ತರ್ಭಾವ "config.h"
#define INCLUDE_STRING
#ಅನ್ತರ್ಭಾವ "system.h"
#ಅನ್ತರ್ಭಾವ "coretypes.h"
#ಅನ್ತರ್ಭಾವ "target.h"
#ಅನ್ತರ್ಭಾವ "function.h"
#ಅನ್ತರ್ಭಾವ "c-tree.h"
#ಅನ್ತರ್ಭಾವ "timevar.h"
#ಅನ್ತರ್ಭಾವ "stringpool.h"
#ಅನ್ತರ್ಭಾವ "cgraph.h"
#ಅನ್ತರ್ಭಾವ "attribs.h"
#ಅನ್ತರ್ಭಾವ "stor-layout.h"
#ಅನ್ತರ್ಭಾವ "varasm.h"
#ಅನ್ತರ್ಭಾವ "trans-mem.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-pragma.h"
#ಅನ್ತರ್ಭಾವ "c-lang.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-objc.h"
#ಅನ್ತರ್ಭಾವ "plugin.h"
#ಅನ್ತರ್ಭಾವ "omp-general.h"
#ಅನ್ತರ್ಭಾವ "omp-offload.h"
#ಅನ್ತರ್ಭಾವ "builtins.h"
#ಅನ್ತರ್ಭಾವ "gomp-constants.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-indentation.h"
#ಅನ್ತರ್ಭಾವ "gimple-expr.h"
#ಅನ್ತರ್ಭಾವ "context.h"
#ಅನ್ತರ್ಭಾವ "gcc-rich-location.h"
#ಅನ್ತರ್ಭಾವ "c-parser.h"
#ಅನ್ತರ್ಭಾವ "gimple-parser.h"
#ಅನ್ತರ್ಭಾವ "read-rtl-function.h"
#ಅನ್ತರ್ಭಾವ "run-rtl-passes.h"
#ಅನ್ತರ್ಭಾವ "intl.h"
#ಅನ್ತರ್ಭಾವ "c-family/name-hint.h"
#ಅನ್ತರ್ಭಾವ "tree-iterator.h"
#ಅನ್ತರ್ಭಾವ "tree-pretty-print.h"
#ಅನ್ತರ್ಭಾವ "memmodel.h"
#ಅನ್ತರ್ಭಾವ "c-family/known-headers.h"
#ಅನ್ತರ್ಭಾವ "bitmap.h"
#ಅನ್ತರ್ಭಾವ "analyzer/analyzer-language.h"
#ಅನ್ತರ್ಭಾವ "toplev.h"
#ಅನ್ತರ್ಭಾವ "asan.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-ubsan.h"
#ಅನ್ತರ್ಭಾವ "gcc-urlifier.h"

/* We need to walk over decls with incomplete struct/union/enum types
   after parsing the whole translation unit.
   In finish_decl(), if the decl is static, has incomplete
   struct/union/enum type, it is appended to incomplete_record_decls.
   In c_parser_translation_unit(), we iterate over incomplete_record_decls
   and report error if any of the decls are still incomplete.  */

vec<ವೃಕ್ಷ> incomplete_record_decls;

ಶೂನ್ಯ
set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (c_ಅಭಿವ್ಯಕ್ತಿ *ಅಭಿವ್ಯಕ್ತಿ,
			 location_t start, location_t finish)
{
  ಅಭಿವ್ಯಕ್ತಿ->src_range.m_start = start;
  ಅಭಿವ್ಯಕ್ತಿ->src_range.m_finish = finish;
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ->ಮೌಲ್ಯ)
    set_source_range (ಅಭಿವ್ಯಕ್ತಿ->ಮೌಲ್ಯ, start, finish);
}

ಶೂನ್ಯ
set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (c_ಅಭಿವ್ಯಕ್ತಿ *ಅಭಿವ್ಯಕ್ತಿ,
			 source_range src_range)
{
  ಅಭಿವ್ಯಕ್ತಿ->src_range = src_range;
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ->ಮೌಲ್ಯ)
    set_source_range (ಅಭಿವ್ಯಕ್ತಿ->ಮೌಲ್ಯ, src_range);
}


/* Initialization routine for this file.  */

ಶೂನ್ಯ
c_parse_init (ಶೂನ್ಯ)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  unsigned ಪೂರ್ಣಾಙ್ಕ i;
  ವೃಕ್ಷ id;
  ಪೂರ್ಣಾಙ್ಕ mask = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  mask |= D_CXXONLY;
  ಯದಿ (!flag_isoc99)
    mask |= D_C99;
  ಯದಿ (!flag_isoc23)
    mask |= D_C23;
  ಯದಿ (flag_no_asm)
    {
      mask |= D_ASM | D_EXT;
      ಯದಿ (!flag_isoc99)
	mask |= D_EXT89;
      ಯದಿ (!flag_isoc23)
	mask |= D_EXT11;
    }
  ಯದಿ (!c_dialect_objc ())
    mask |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<ವೃಕ್ಷ> ((ಪೂರ್ಣಾಙ್ಕ) RID_MAX);
  ಪ್ರತಿ (i = 0; i < ಅಂಕೆ_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      ಯದಿ (c_common_reswords[i].disable & mask)
	{
	  ಯದಿ (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].word);
	      C_SET_RID_CODE (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_WORD (id) = 1;
	    }
	  ಅನುವರ್ತ;
	}

      id = get_identifier (c_common_reswords[i].word);
      C_SET_RID_CODE (id, c_common_reswords[i].rid);
      C_IS_RESERVED_WORD (id) = 1;
      ridpointers [(ಪೂರ್ಣಾಙ್ಕ) c_common_reswords[i].rid] = id;
    }

  ಪ್ರತಿ (i = 0; i < ಅಂಕೆ_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      ವರ್ಣ name[50];
      sprintf (name, "__int%d", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;

      sprintf (name, "__int%d__", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;
    }

  ಯದಿ (flag_openmp)
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
ಸಂರಚನಾ GTY(()) c_parser {
  /* The look-ahead tokens.  */
  c_token * GTY((skip)) tokens;
  /* Buffer for look-ahead tokens.  */
  c_token tokens_buf[4];
  /* How many look-ahead tokens are available (0 - 4, or
     more if parsing from pre-lexed tokens).  */
  unsigned ಪೂರ್ಣಾಙ್ಕ tokens_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_tokens;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  unsigned ಪೂರ್ಣಾಙ್ಕ raw_tokens_used;
  /* True if a syntax error is being recovered from; false otherwise.
     c_parser_error sets this flag.  It should clear this flag when
     enough tokens have been consumed to recover from the error.  */
  ತಾರ್ಕಿಕ error : 1;
  /* True if we're processing a pragma, and shouldn't automatically
     consume CPP_PRAGMA_EOL.  */
  ತಾರ್ಕಿಕ in_pragma : 1;
  /* True if we're parsing the outermost block of an if statement.  */
  ತಾರ್ಕಿಕ in_if_block : 1;
  /* True if we want to lex a translated, joined string (for an
     initial #pragma pch_preprocess).  Otherwise the parser is
     responsible for concatenating strings and translating to the
     execution character set as needed.  */
  ತಾರ್ಕಿಕ lex_joined_string : 1;
  /* True if, when the parser is concatenating string literals, it
     should translate them to the execution character set (false
     inside attributes).  */
  ತಾರ್ಕಿಕ translate_strings_p : 1;

  /* Objective-C specific parser/lexer information.  */

  /* True if we are in a context where the Objective-C "PQ" keywords
     are considered keywords.  */
  ತಾರ್ಕಿಕ objc_pq_context : 1;
  /* True if we are parsing a (potential) Objective-C foreach
     statement.  This is set to true after we parsed 'for (' and while
     we wait for 'in' or ';' to decide if it's a standard C for loop or an
     Objective-C foreach loop.  */
  ತಾರ್ಕಿಕ objc_could_be_foreach_context : 1;
  /* The following flag is needed to contextualize Objective-C lexical
     analysis.  In some cases (e.g., 'int NSObject;'), it is
     undesirable to bind an identifier to an Objective-C class, even
     if a class with that name exists.  */
  ತಾರ್ಕಿಕ objc_need_raw_identifier : 1;
  /* Nonzero if we're processing a __transaction statement.  The value
     is 1 | TM_STMT_ATTR_*.  */
  unsigned ಪೂರ್ಣಾಙ್ಕ in_transaction : 4;
  /* True if we are in a context where the Objective-C "Property attribute"
     keywords are valid.  */
  ತಾರ್ಕಿಕ objc_property_attr_context : 1;

  /* Whether we have just seen/constructed a string-literal.  Set when
     returning a string-literal from c_parser_string_literal.  Reset
     in consume_token.  Useful when we get a parse error and see an
     unknown token, which could have been a string-literal constant
     macro.  */
  ತಾರ್ಕಿಕ seen_string_literal : 1;

  /* TRUE if omp::directive, omp::decl or omp::sequence attributes may not
     appear.  */
  ತಾರ್ಕಿಕ omp_attrs_forbidden_p : 1;

  /* Location of the last consumed token.  */
  location_t last_token_location;

  /* Holds state for parsing collapsed OMP_FOR loops.  Managed by
     c_parser_omp_for_loop.  */
  ಸಂರಚನಾ omp_for_parse_data * GTY((skip)) omp_for_parse_state;

  /* If we're in the context of OpenMP directives written as C23
     attributes turned into pragma, the tokens field is temporarily
     redirected.  This holds data needed to restore state afterwards.
     It's NULL otherwise.  */
  ಸಂರಚನಾ omp_attribute_pragma_state *in_omp_attribute_pragma;

  /* Set for omp::decl attribute parsing to the decl to which it
     appertains.  */
  ವೃಕ್ಷ in_omp_decl_attribute;

  /* Non-null only when parsing the body of an OpenMP metadirective.
     Managed by c_parser_omp_metadirective.  */
  ಸಂರಚನಾ omp_metadirective_parse_data * GTY((skip))
    omp_metadirective_state;
};

/* Holds data needed to restore the token stream to its previous state
   after parsing an OpenMP attribute-syntax pragma.  */
ಸಂರಚನಾ GTY(()) omp_attribute_pragma_state
{
  vec<c_token, va_gc> *token_vec;
  c_token * GTY((skip)) save_tokens;
  unsigned ಪೂರ್ಣಾಙ್ಕ save_tokens_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
ಸಂರಚನಾ GTY(()) omp_begin_declare_variant_map_entry {
  ವೃಕ್ಷ variant;		/* The variant decl.  */
  ವೃಕ್ಷ id;		/* Name of base function.  */
  ವೃಕ್ಷ ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_entry, va_gc> *omp_begin_declare_variant_map;

ಸ್ಥಿರ ವೃಕ್ಷ omp_start_variant_function (c_declarator *, ವೃಕ್ಷ);
ಸ್ಥಿರ ಶೂನ್ಯ omp_finish_variant_function (ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_tokens_buf (c_parser *parser, unsigned n)
{
  ಪ್ರತ್ಯಾಗಮ &parser->tokens_buf[n];
}

/* Return the error state of PARSER.  */

ತಾರ್ಕಿಕ
c_parser_error (c_parser *parser)
{
  ಪ್ರತ್ಯಾಗಮ parser->error;
}

/* Set the error state of PARSER to ERR.  */

ಶೂನ್ಯ
c_parser_set_error (c_parser *parser, ತಾರ್ಕಿಕ err)
{
  parser->error = err;
}


/* The actual parser and external interface.  ??? Does this need to be
   garbage-collected?  */

ಸ್ಥಿರ GTY (()) c_parser *the_parser;

/* Read in and lex a single token, storing it in *TOKEN.  If RAW,
   context-sensitive postprocessing of the token is not done.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_lex_one_token (c_parser *parser, c_token *token, ತಾರ್ಕಿಕ raw = ಅಸತ್ಯ)
{
  timevar_ತಳ್ಳು (TV_LEX);

  ಯದಿ (raw || vec_safe_length (parser->raw_tokens) == 0)
    {
      token->type = c_lex_with_flags (&token->ಮೌಲ್ಯ, &token->location,
				      &token->flags,
				      (parser->lex_joined_string
				       ? 0 : C_LEX_STRING_NO_JOIN));
      token->id_kind = C_ID_NONE;
      token->keyword = RID_MAX;
      token->pragma_kind = PRAGMA_NONE;
    }
  ಅನ್ಯಥಾ
    {
      /* Use a token previously lexed as a raw look-ahead token, and
	 complete the processing on it.  */
      *token = (*parser->raw_tokens)[parser->raw_tokens_used];
      ++parser->raw_tokens_used;
      ಯದಿ (parser->raw_tokens_used == vec_safe_length (parser->raw_tokens))
	{
	  vec_free (parser->raw_tokens);
	  parser->raw_tokens_used = 0;
	}
    }

  ಯದಿ (raw)
    ಗಚ್ಛ out;

  ವಿಕಲ್ಪ (token->type)
    {
    ಪಕ್ಷ CPP_NAME:
      {
	ವೃಕ್ಷ decl;

	ತಾರ್ಕಿಕ objc_force_identifier = parser->objc_need_raw_identifier;
	ಯದಿ (c_dialect_objc ())
	  parser->objc_need_raw_identifier = ಅಸತ್ಯ;

	ಯದಿ (C_IS_RESERVED_WORD (token->ಮೌಲ್ಯ))
	  {
	    ಗಣನಾ rid rid_code = C_RID_CODE (token->ಮೌಲ್ಯ);

	    ಯದಿ (rid_code == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->ಮೌಲ್ಯ);
	      }
	    ಅನ್ಯಥಾ ಯದಿ (rid_code >= RID_FIRST_ADDR_SPACE
		     && rid_code <= RID_LAST_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_code - RID_FIRST_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_kind = C_ID_ADDRSPACE;
		token->keyword = rid_code;
		ಭಙ್ಗ;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		ಯದಿ (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    ಭಙ್ಗ;
		  }
		ಅನ್ಯಥಾ ಯದಿ (parser->objc_could_be_foreach_context
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
		    ಭಙ್ಗ;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    ಅನ್ಯಥಾ ಯದಿ (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		ಯದಿ (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    ಭಙ್ಗ;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    ಅನ್ಯಥಾ ಯದಿ (c_dialect_objc ()
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
	    ಅನ್ಯಥಾ
	      {
		token->type = CPP_KEYWORD;
		token->keyword = rid_code;
		ಭಙ್ಗ;
	      }
	  }

	decl = lookup_name (token->ಮೌಲ್ಯ);
	ಯದಿ (decl)
	  {
	    ಯದಿ (ವೃಕ್ಷ_CODE (decl) == TYPE_DECL)
	      {
		token->id_kind = C_ID_TYPENAME;
		ಭಙ್ಗ;
	      }
	  }
	ಅನ್ಯಥಾ ಯದಿ (c_dialect_objc ())
	  {
	    ವೃಕ್ಷ objc_interface_decl = objc_is_class_name (token->ಮೌಲ್ಯ);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    ಯದಿ (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->ಮೌಲ್ಯ = objc_interface_decl;
		token->id_kind = C_ID_CLASSNAME;
		ಭಙ್ಗ;
	      }
	  }
        token->id_kind = C_ID_ID;
      }
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      ವಿಕಲ್ಪ (C_RID_CODE (token->ಮೌಲ್ಯ))
	{
	  /* Replace 'class' with '@class', 'private' with '@private',
	     etc.  This prevents confusion with the C++ keyword
	     'class', and makes the tokens consistent with other
	     Objective-C 'AT' keywords.  For example '@class' is
	     reported as RID_AT_CLASS which is consistent with
	     '@synchronized', which is reported as
	     RID_AT_SYNCHRONIZED.
	  */
	ಪಕ್ಷ RID_CLASS:     token->keyword = RID_AT_CLASS; ಭಙ್ಗ;
	ಪಕ್ಷ RID_PRIVATE:   token->keyword = RID_AT_PRIVATE; ಭಙ್ಗ;
	ಪಕ್ಷ RID_PROTECTED: token->keyword = RID_AT_PROTECTED; ಭಙ್ಗ;
	ಪಕ್ಷ RID_PUBLIC:    token->keyword = RID_AT_PUBLIC; ಭಙ್ಗ;
	ಪಕ್ಷ RID_THROW:     token->keyword = RID_AT_THROW; ಭಙ್ಗ;
	ಪಕ್ಷ RID_TRY:       token->keyword = RID_AT_TRY; ಭಙ್ಗ;
	ಪಕ್ಷ RID_CATCH:     token->keyword = RID_AT_CATCH; ಭಙ್ಗ;
	ಪಕ್ಷ RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; ಭಙ್ಗ;
	ಸ್ವಭಾವ:            token->keyword = C_RID_CODE (token->ಮೌಲ್ಯ);
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_COLON:
    ಪಕ್ಷ CPP_COMMA:
    ಪಕ್ಷ CPP_CLOSE_PAREN:
    ಪಕ್ಷ CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      ಯದಿ (c_dialect_objc ())
	parser->objc_need_raw_identifier = ಅಸತ್ಯ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_kind = (ಗಣನಾ pragma_kind) ವೃಕ್ಷ_INT_CST_ಕೆಳಗಿನ (token->ಮೌಲ್ಯ);
      token->ಮೌಲ್ಯ = ರಿಕ್ತ;
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      ಭಙ್ಗ;
    }
 out:
  timevar_ತೆಗೆ (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  ಯದಿ (parser->tokens_avail == 0)
    {
      c_lex_one_token (parser, &parser->tokens[0]);
      parser->tokens_avail = 1;
    }
  ಪ್ರತ್ಯಾಗಮ &parser->tokens[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  ಯದಿ (parser->tokens_avail >= 2)
    ಪ್ರತ್ಯಾಗಮ &parser->tokens[1];
  gcc_assert (parser->tokens_avail == 1);
  gcc_assert (parser->tokens[0].type != CPP_EOF);
  gcc_assert (parser->tokens[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->tokens[1]);
  parser->tokens_avail = 2;
  ಪ್ರತ್ಯಾಗಮ &parser->tokens[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, unsigned ಪೂರ್ಣಾಙ್ಕ n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  ಯದಿ (parser->tokens_avail >= n)
    ಪ್ರತ್ಯಾಗಮ &parser->tokens[n - 1];
  gcc_assert (parser->tokens_avail == n - 1);
  c_lex_one_token (parser, &parser->tokens[n - 1]);
  parser->tokens_avail = n;
  ಪ್ರತ್ಯಾಗಮ &parser->tokens[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, unsigned ಪೂರ್ಣಾಙ್ಕ n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  ಯದಿ (parser->tokens_avail >= n)
    ಪ್ರತ್ಯಾಗಮ &parser->tokens[n - 1];
  unsigned ಪೂರ್ಣಾಙ್ಕ raw_len = vec_safe_length (parser->raw_tokens);
  unsigned ಪೂರ್ಣಾಙ್ಕ raw_avail
    = parser->tokens_avail + raw_len - parser->raw_tokens_used;
  gcc_assert (raw_avail >= n - 1);
  ಯದಿ (raw_avail >= n)
    ಪ್ರತ್ಯಾಗಮ &(*parser->raw_tokens)[parser->raw_tokens_used
				  + n - 1 - parser->tokens_avail];
  vec_safe_reserve (parser->raw_tokens, 1);
  parser->raw_tokens->quick_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_tokens)[raw_len], ಸತ್ಯ);
  ಪ್ರತ್ಯಾಗಮ &(*parser->raw_tokens)[raw_len];
}

ತಾರ್ಕಿಕ
c_keyword_starts_typename (ಗಣನಾ rid keyword)
{
  ವಿಕಲ್ಪ (keyword)
    {
    ಪಕ್ಷ RID_UNSIGNED:
    ಪಕ್ಷ RID_LONG:
    ಪಕ್ಷ RID_SHORT:
    ಪಕ್ಷ RID_SIGNED:
    ಪಕ್ಷ RID_COMPLEX:
    ಪಕ್ಷ RID_INT:
    ಪಕ್ಷ RID_CHAR:
    ಪಕ್ಷ RID_FLOAT:
    ಪಕ್ಷ RID_DOUBLE:
    ಪಕ್ಷ RID_VOID:
    ಪಕ್ಷ RID_DFLOAT32:
    ಪಕ್ಷ RID_DFLOAT64:
    ಪಕ್ಷ RID_DFLOAT128:
    ಪಕ್ಷ RID_DFLOAT64X:
    CASE_RID_FLOATN_NX:
    ಪಕ್ಷ RID_BOOL:
    ಪಕ್ಷ RID_BITINT:
    ಪಕ್ಷ RID_ENUM:
    ಪಕ್ಷ RID_STRUCT:
    ಪಕ್ಷ RID_UNION:
    ಪಕ್ಷ RID_TYPEOF:
    ಪಕ್ಷ RID_TYPEOF_UNQUAL:
    ಪಕ್ಷ RID_CONST:
    ಪಕ್ಷ RID_ATOMIC:
    ಪಕ್ಷ RID_VOLATILE:
    ಪಕ್ಷ RID_RESTRICT:
    ಪಕ್ಷ RID_ATTRIBUTE:
    ಪಕ್ಷ RID_FRACT:
    ಪಕ್ಷ RID_ACCUM:
    ಪಕ್ಷ RID_SAT:
    ಪಕ್ಷ RID_AUTO_TYPE:
    ಪಕ್ಷ RID_ALIGNAS:
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    ಸ್ವಭಾವ:
      ಯದಿ (keyword >= RID_FIRST_INT_N
	  && keyword < RID_FIRST_INT_N + ಅಂಕೆ_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_FIRST_INT_N])
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }
}

/* Return true if TOKEN can start a type name,
   false otherwise.  */
ತಾರ್ಕಿಕ
c_token_starts_typename (c_token *token)
{
  ವಿಕಲ್ಪ (token->type)
    {
    ಪಕ್ಷ CPP_NAME:
      ವಿಕಲ್ಪ (token->id_kind)
	{
	ಪಕ್ಷ C_ID_ID:
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	ಪಕ್ಷ C_ID_ADDRSPACE:
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	ಪಕ್ಷ C_ID_TYPENAME:
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	ಪಕ್ಷ C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	ಸ್ವಭಾವ:
	  gcc_unreachable ();
	}
    ಪಕ್ಷ CPP_KEYWORD:
      ಪ್ರತ್ಯಾಗಮ c_keyword_starts_typename (token->keyword);
    ಪಕ್ಷ CPP_LESS:
      ಯದಿ (c_dialect_objc ())
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    ಸ್ವಭಾವ:
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ತಾರ್ಕಿಕ
c_parser_next_tokens_start_typename (c_parser *parser, ಗಣನಾ c_lookahead_kind la,
				     unsigned ಪೂರ್ಣಾಙ್ಕ n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  ಯದಿ (c_token_starts_typename (token))
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  /* Try a bit harder to detect an unknown typename.  */
  ಯದಿ (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_kind == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->ಮೌಲ್ಯ))
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* Return true if TOKEN, after an open parenthesis, can start a
   compound literal (either a storage class specifier allowed in that
   context, or a type name), false otherwise.  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_token_starts_compound_literal (c_token *token)
{
  ವಿಕಲ್ಪ (token->type)
    {
    ಪಕ್ಷ CPP_KEYWORD:
      ವಿಕಲ್ಪ (token->keyword)
	{
	ಪಕ್ಷ RID_CONSTEXPR:
	ಪಕ್ಷ RID_REGISTER:
	ಪಕ್ಷ RID_STATIC:
	ಪಕ್ಷ RID_THREAD:
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	ಸ್ವಭಾವ:
	  ಭಙ್ಗ;
	}
      /* Fall through.  */
    ಸ್ವಭಾವ:
      ಪ್ರತ್ಯಾಗಮ c_token_starts_typename (token);
    }
}

/* Return true if TOKEN is a type qualifier, false otherwise.  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_token_is_qualifier (c_token *token)
{
  ವಿಕಲ್ಪ (token->type)
    {
    ಪಕ್ಷ CPP_NAME:
      ವಿಕಲ್ಪ (token->id_kind)
	{
	ಪಕ್ಷ C_ID_ADDRSPACE:
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	ಸ್ವಭಾವ:
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
    ಪಕ್ಷ CPP_KEYWORD:
      ವಿಕಲ್ಪ (token->keyword)
	{
	ಪಕ್ಷ RID_CONST:
	ಪಕ್ಷ RID_VOLATILE:
	ಪಕ್ಷ RID_RESTRICT:
	ಪಕ್ಷ RID_ATTRIBUTE:
	ಪಕ್ಷ RID_ATOMIC:
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	ಸ್ವಭಾವ:
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
    ಪಕ್ಷ CPP_LESS:
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }
}

/* Return true if the next token from PARSER is a type qualifier,
   false otherwise.  */
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ತಾರ್ಕಿಕ
c_parser_next_token_is_qualifier (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  ಪ್ರತ್ಯಾಗಮ c_token_is_qualifier (token);
}

/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes), false otherwise.  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_token_starts_declspecs (c_token *token)
{
  ವಿಕಲ್ಪ (token->type)
    {
    ಪಕ್ಷ CPP_NAME:
      ವಿಕಲ್ಪ (token->id_kind)
	{
	ಪಕ್ಷ C_ID_ID:
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	ಪಕ್ಷ C_ID_ADDRSPACE:
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	ಪಕ್ಷ C_ID_TYPENAME:
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	ಪಕ್ಷ C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	ಸ್ವಭಾವ:
	  gcc_unreachable ();
	}
    ಪಕ್ಷ CPP_KEYWORD:
      ವಿಕಲ್ಪ (token->keyword)
	{
	ಪಕ್ಷ RID_STATIC:
	ಪಕ್ಷ RID_EXTERN:
	ಪಕ್ಷ RID_REGISTER:
	ಪಕ್ಷ RID_TYPEDEF:
	ಪಕ್ಷ RID_INLINE:
	ಪಕ್ಷ RID_NORETURN:
	ಪಕ್ಷ RID_AUTO:
	ಪಕ್ಷ RID_THREAD:
	ಪಕ್ಷ RID_UNSIGNED:
	ಪಕ್ಷ RID_LONG:
	ಪಕ್ಷ RID_SHORT:
	ಪಕ್ಷ RID_SIGNED:
	ಪಕ್ಷ RID_COMPLEX:
	ಪಕ್ಷ RID_INT:
	ಪಕ್ಷ RID_CHAR:
	ಪಕ್ಷ RID_FLOAT:
	ಪಕ್ಷ RID_DOUBLE:
	ಪಕ್ಷ RID_VOID:
	ಪಕ್ಷ RID_DFLOAT32:
	ಪಕ್ಷ RID_DFLOAT64:
	ಪಕ್ಷ RID_DFLOAT128:
	ಪಕ್ಷ RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	ಪಕ್ಷ RID_BOOL:
	ಪಕ್ಷ RID_BITINT:
	ಪಕ್ಷ RID_ENUM:
	ಪಕ್ಷ RID_STRUCT:
	ಪಕ್ಷ RID_UNION:
	ಪಕ್ಷ RID_TYPEOF:
	ಪಕ್ಷ RID_TYPEOF_UNQUAL:
	ಪಕ್ಷ RID_CONST:
	ಪಕ್ಷ RID_VOLATILE:
	ಪಕ್ಷ RID_RESTRICT:
	ಪಕ್ಷ RID_ATTRIBUTE:
	ಪಕ್ಷ RID_FRACT:
	ಪಕ್ಷ RID_ACCUM:
	ಪಕ್ಷ RID_SAT:
	ಪಕ್ಷ RID_ALIGNAS:
	ಪಕ್ಷ RID_ATOMIC:
	ಪಕ್ಷ RID_AUTO_TYPE:
	ಪಕ್ಷ RID_CONSTEXPR:
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	ಸ್ವಭಾವ:
	  ಯದಿ (token->keyword >= RID_FIRST_INT_N
	      && token->keyword < RID_FIRST_INT_N + ಅಂಕೆ_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_FIRST_INT_N])
	    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
    ಪಕ್ಷ CPP_LESS:
      ಯದಿ (c_dialect_objc ())
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    ಸ್ವಭಾವ:
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }
}


/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes) or a static assertion, false
   otherwise.  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_token_starts_declaration (c_token *token)
{
  ಯದಿ (c_token_starts_declspecs (token)
      || token->keyword == RID_STATIC_ASSERT)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* Return true if the next token from PARSER can start declaration
   specifiers (not including standard attributes), false
   otherwise.  */
ತಾರ್ಕಿಕ
c_parser_next_token_starts_declspecs (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);

  /* In Objective-C, a classname normally starts a declspecs unless it
     is immediately followed by a dot.  In that case, it is the
     Objective-C 2.0 "dot-syntax" for class objects, ie, calls the
     setter/getter on the class.  c_token_starts_declspecs() can't
     differentiate between the two cases because it only checks the
     current token, so we have a special check here.  */
  ಯದಿ (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಪ್ರತ್ಯಾಗಮ c_token_starts_declspecs (token);
}

ಸ್ಥಿರ ತಾರ್ಕಿಕ c_parser_check_balanced_raw_token_sequence (c_parser *,
							unsigned ಪೂರ್ಣಾಙ್ಕ *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
ತಾರ್ಕಿಕ
c_parser_next_tokens_start_declaration (c_parser *parser, unsigned ಪೂರ್ಣಾಙ್ಕ n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  ಯದಿ (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_DOT)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* Labels do not start declarations.  */
  ಯದಿ (token->type == CPP_NAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_COLON)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* A static assertion is only a declaration if followed by a semicolon;
     otherwise, it may be an expression in C2Y.  */
  ಯದಿ (token->keyword == RID_STATIC_ASSERT
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_PAREN)
    {
      n += 2;
      ಯದಿ (!c_parser_check_balanced_raw_token_sequence (parser, &n)
	  || c_parser_peek_nth_token_raw (parser, n)->type != CPP_CLOSE_PAREN)
	/* Invalid static assertion syntax; treat as a declaration and report a
	   syntax error there.  */
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  ಯದಿ (c_token_starts_declaration (token))
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  ಯದಿ (c_parser_next_tokens_start_typename (parser, cla_nonabstract_decl, n))
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* Consume the next token from PARSER.  */

ಶೂನ್ಯ
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
  ಯದಿ (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  ಅನ್ಯಥಾ ಯದಿ (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      ಯದಿ (parser->tokens_avail >= 3)
        {
          parser->tokens[1] = parser->tokens[2];
          ಯದಿ (parser->tokens_avail >= 4)
            parser->tokens[2] = parser->tokens[3];
        }
    }
  parser->tokens_avail--;
  parser->seen_string_literal = ಅಸತ್ಯ;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->in_pragma);
  gcc_assert (parser->tokens_avail >= 1);
  gcc_assert (parser->tokens[0].type == CPP_PRAGMA);
  ಯದಿ (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  ಅನ್ಯಥಾ ಯದಿ (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      ಯದಿ (parser->tokens_avail >= 3)
	parser->tokens[1] = parser->tokens[2];
    }
  parser->tokens_avail--;
  parser->in_pragma = ಸತ್ಯ;
}

/* Update the global input_location from TOKEN.  */
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ
c_parser_set_source_position_from_token (c_token *token)
{
  ಯದಿ (token->type != CPP_EOF)
    {
      ಒಳಹರಿವು_location = token->location;
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

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_peek_conflict_marker (c_parser *parser, ಗಣನಾ cpp_ttype tok1_kind,
			       location_t *out_loc)
{
  c_token *token2 = c_parser_peek_2nd_token (parser);
  ಯದಿ (token2->type != tok1_kind)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  ಯದಿ (token3->type != tok1_kind)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  ಯದಿ (token4->type != conflict_marker_get_final_tok_kind (tok1_kind))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* It must be at the start of the line.  */
  location_t start_loc = c_parser_peek_token (parser)->location;
  ಯದಿ (LOCATION_COLUMN (start_loc) != 1)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t finish_loc = get_finish (token4->location);
  *out_loc = make_location (start_loc, start_loc, finish_loc);

  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
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

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_error_richloc (c_parser *parser, ಧ್ರುವ ವರ್ಣ *gmsgid,
			rich_location *richloc)
{
  c_token *token = c_parser_peek_token (parser);
  ಯದಿ (parser->error)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  parser->error = ಸತ್ಯ;
  ಯದಿ (!gmsgid)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* If this is actually a conflict marker, report it as such.  */
  ಯದಿ (token->type == CPP_LSHIFT
      || token->type == CPP_RSHIFT
      || token->type == CPP_EQ_EQ)
    {
      location_t loc;
      ಯದಿ (c_parser_peek_conflict_marker (parser, token->type, &loc))
	{
	  error_at (loc, "version control conflict marker in file");
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_group d;
  name_hint h;
  ಯದಿ (parser->seen_string_literal && token->type == CPP_NAME)
    {
      ವೃಕ್ಷ name = token->ಮೌಲ್ಯ;
      ಧ್ರುವ ವರ್ಣ *token_name = IDENTIFIER_POINTER (name);
      ಧ್ರುವ ವರ್ಣ *header_hint
	= get_c_stdlib_header_for_string_macro_name (token_name);
      ಯದಿ (header_hint != ರಿಕ್ತ)
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
		 token->ಮೌಲ್ಯ, /*flags=*/0, richloc);
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

ತಾರ್ಕಿಕ
c_parser_error (c_parser *parser, ಧ್ರುವ ವರ್ಣ *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_set_source_position_from_token (token);
  rich_location richloc (ಸಾಲು_table, ಒಳಹರಿವು_location);
  ಪ್ರತ್ಯಾಗಮ c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

template <typename traits_t>
ವರ್ಗ token_pair
{
 ಸಾರ್ವಜನಿಕ:
  /* token_pair's ctor.  */
  token_pair () : m_open_loc (UNKNOWN_LOCATION) {}

  /* If the next token is the opening symbol for this pair, consume it and
     return true.
     Otherwise, issue an error and return false.
     In either case, record the location of the opening token.  */

  ತಾರ್ಕಿಕ require_open (c_parser *parser)
  {
    c_token *token = c_parser_peek_token (parser);
    ಯದಿ (token)
      m_open_loc = token->location;

    ಪ್ರತ್ಯಾಗಮ c_parser_require (parser, traits_t::open_token_type,
			     traits_t::open_gmsgid);
  }

  /* Consume the next token from PARSER, recording its location as
     that of the opening token within the pair.  */

  ಶೂನ್ಯ consume_open (c_parser *parser)
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

  ತಾರ್ಕಿಕ require_close (c_parser *parser) ಧ್ರುವ
  {
    ಪ್ರತ್ಯಾಗಮ c_parser_require (parser, traits_t::close_token_type,
			     traits_t::close_gmsgid, m_open_loc);
  }

  /* Like token_pair::require_close, except that tokens will be skipped
     until the desired token is found.  An error message is still produced
     if the next token is not as expected.  */

  ಶೂನ್ಯ skip_until_found_close (c_parser *parser) ಧ್ರುವ
  {
    c_parser_skip_until_found (parser, traits_t::close_token_type,
			       traits_t::close_gmsgid, m_open_loc);
  }

 ಗುಪ್ತ:
  location_t m_open_loc;
};

/* Traits for token_pair<T> for tracking matching pairs of parentheses.  */

ಸಂರಚನಾ matching_paren_traits
{
  ಸ್ಥಿರ ಧ್ರುವ ಗಣನಾ cpp_ttype open_token_type = CPP_OPEN_PAREN;
  ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ open_gmsgid;
  ಸ್ಥಿರ ಧ್ರುವ ಗಣನಾ cpp_ttype close_token_type = CPP_CLOSE_PAREN;
  ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ close_gmsgid;
};

ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ matching_paren_traits::open_gmsgid = "expected %<(%>";
ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ matching_paren_traits::close_gmsgid = "expected %<)%>";

/* "matching_parens" is a token_pair<T> class for tracking matching
   pairs of parentheses.  */

ಪ್ರಕಾರನಿರ್ದೇಶ token_pair<matching_paren_traits> matching_parens;

/* Traits for token_pair<T> for tracking matching pairs of braces.  */

ಸಂರಚನಾ matching_brace_traits
{
  ಸ್ಥಿರ ಧ್ರುವ ಗಣನಾ cpp_ttype open_token_type = CPP_OPEN_BRACE;
  ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ open_gmsgid;
  ಸ್ಥಿರ ಧ್ರುವ ಗಣನಾ cpp_ttype close_token_type = CPP_CLOSE_BRACE;
  ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ close_gmsgid;
};

ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ matching_brace_traits::open_gmsgid = "expected %<{%>";
ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ matching_brace_traits::close_gmsgid = "expected %<}%>";

/* "matching_braces" is a token_pair<T> class for tracking matching
   pairs of braces.  */

ಪ್ರಕಾರನಿರ್ದೇಶ token_pair<matching_brace_traits> matching_braces;

/* Get a description of the matching symbol to TYPE e.g. "(" for
   CPP_CLOSE_PAREN.  */

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *
get_matching_ಚಿಹ್ನೆ (ಗಣನಾ cpp_ttype type)
{
  ವಿಕಲ್ಪ (type)
    {
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    ಪಕ್ಷ CPP_CLOSE_PAREN:
      ಪ್ರತ್ಯಾಗಮ "(";
    ಪಕ್ಷ CPP_CLOSE_BRACE:
      ಪ್ರತ್ಯಾಗಮ "{";
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

ತಾರ್ಕಿಕ
c_parser_require (c_parser *parser,
		  ಗಣನಾ cpp_ttype type,
		  ಧ್ರುವ ವರ್ಣ *msgid,
		  location_t matching_location,
		  ತಾರ್ಕಿಕ type_is_unique)
{
  ಯದಿ (c_parser_next_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }
  ಅನ್ಯಥಾ
    {
      location_t next_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (next_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      ಯದಿ (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->last_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      ತಾರ್ಕಿಕ added_matching_location = ಅಸತ್ಯ;
      ಯದಿ (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.add_location_if_nearby (*global_dc, matching_location);

      ಯದಿ (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	ಯದಿ (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_ಚಿಹ್ನೆ (type));

      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }
}

/* If the next token is the indicated keyword, consume it.  Otherwise,
   issue the error MSGID.  Returns true if found, false otherwise.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_require_keyword (c_parser *parser,
			  ಗಣನಾ rid keyword,
			  ಧ್ರುವ ವರ್ಣ *msgid)
{
  ಯದಿ (c_parser_next_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }
  ಅನ್ಯಥಾ
    {
      c_parser_error (parser, msgid);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
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

ಶೂನ್ಯ
c_parser_skip_until_found (c_parser *parser,
			   ಗಣನಾ cpp_ttype type,
			   ಧ್ರುವ ವರ್ಣ *msgid,
			   location_t matching_location)
{
  unsigned nesting_depth = 0;

  ಯದಿ (c_parser_require (parser, type, msgid, matching_location))
    {
      ಯದಿ (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->in_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ಯದಿ (token->type == CPP_EOF)
	    {
	      parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	      parser->tokens_avail
		= parser->in_omp_attribute_pragma->save_tokens_avail;
	      parser->in_omp_attribute_pragma = ರಿಕ್ತ;
	    }
	}
      ಪ್ರತ್ಯಾಗಮ;
    }

  /* Skip tokens until the desired token is found.  */
  ಯಾವತ್ (ಸತ್ಯ)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      ಯದಿ (token->type == type && !nesting_depth)
	{
	  c_parser_consume_token (parser);
	  ಯದಿ (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->in_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      ಯದಿ (token->type == CPP_EOF)
		{
		  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
		  parser->tokens_avail
		    = parser->in_omp_attribute_pragma->save_tokens_avail;
		  parser->in_omp_attribute_pragma = ರಿಕ್ತ;
		}
	    }
	  ಭಙ್ಗ;
	}

      /* If we've run out of tokens, stop.  */
      ಯದಿ (token->type == CPP_EOF)
	ಪ್ರತ್ಯಾಗಮ;
      ಯದಿ (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	ಪ್ರತ್ಯಾಗಮ;
      ಯದಿ (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      ಅನ್ಯಥಾ ಯದಿ (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  ಯದಿ (nesting_depth-- == 0)
	    ಭಙ್ಗ;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = ಅಸತ್ಯ;
}

/* Skip tokens until the end of a parameter is found, but do not
   consume the comma, semicolon or closing delimiter.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_skip_to_end_of_parameter (c_parser *parser)
{
  unsigned nesting_depth = 0;

  ಯಾವತ್ (ಸತ್ಯ)
    {
      c_token *token = c_parser_peek_token (parser);
      ಯದಿ ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_depth)
	ಭಙ್ಗ;
      /* If we've run out of tokens, stop.  */
      ಯದಿ (token->type == CPP_EOF)
	ಪ್ರತ್ಯಾಗಮ;
      ಯದಿ (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	ಪ್ರತ್ಯಾಗಮ;
      ಯದಿ (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      ಅನ್ಯಥಾ ಯದಿ (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  ಯದಿ (nesting_depth-- == 0)
	    ಭಙ್ಗ;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = ಅಸತ್ಯ;
}

/* Skip tokens until a non-nested closing curly brace is the next
   token, or there are no more tokens. Return true in the first case,
   false otherwise.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_skip_to_closing_brace (c_parser *parser)
{
  unsigned nesting_depth = 0;

  ಯಾವತ್ (ಸತ್ಯ)
    {
      c_token *token = c_parser_peek_token (parser);

      ವಿಕಲ್ಪ (token->type)
	{
	ಪಕ್ಷ CPP_PRAGMA_EOL:
	  ಯದಿ (!parser->in_pragma)
	    ಭಙ್ಗ;
	  /* FALLTHRU */
	ಪಕ್ಷ CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	ಪಕ್ಷ CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  ಯದಿ (nesting_depth-- == 0)
	    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	  ಭಙ್ಗ;

	ಪಕ್ಷ CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  ಭಙ್ಗ;

	ಸ್ವಭಾವ:
	  ಭಙ್ಗ;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Expect to be at the end of the pragma directive and consume an
   end of line marker.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_skip_to_pragma_eol (c_parser *parser, ತಾರ್ಕಿಕ error_if_not_eol = ಸತ್ಯ)
{
  gcc_assert (parser->in_pragma);
  parser->in_pragma = ಅಸತ್ಯ;

  ಯದಿ (error_if_not_eol && c_parser_peek_token (parser)->type != CPP_PRAGMA_EOL)
    c_parser_error (parser, "expected end of line");

  cpp_ttype token_type;
  ಕುರು
    {
      c_token *token = c_parser_peek_token (parser);
      token_type = token->type;
      ಯದಿ (token_type == CPP_EOF)
	ಭಙ್ಗ;
      c_parser_consume_token (parser);
    }
  ಯಾವತ್ (token_type != CPP_PRAGMA_EOL);

  ಯದಿ (parser->in_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      ಯದಿ (token->type == CPP_EOF)
	{
	  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	  parser->tokens_avail
	    = parser->in_omp_attribute_pragma->save_tokens_avail;
	  parser->in_omp_attribute_pragma = ರಿಕ್ತ;
	}
    }

  parser->error = ಅಸತ್ಯ;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_skip_to_pragma_omp_end_declare_variant (c_parser *parser)
{
  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ depth = 0; depth >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      ವಿಕಲ್ಪ (token->type)
	{
	ಪಕ್ಷ CPP_PRAGMA_EOL:
	  ಯದಿ (!parser->in_pragma)
	    ಭಙ್ಗ;
	  /* FALLTHRU */
	ಪಕ್ಷ CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  ಪ್ರತ್ಯಾಗಮ;

	ಪಕ್ಷ CPP_PRAGMA:
	  ಯದಿ ((token->pragma_kind == PRAGMA_OMP_BEGIN
	       || token->pragma_kind == PRAGMA_OMP_END)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      ವೃಕ್ಷ id1 = c_parser_peek_nth_token (parser, 2)->ಮೌಲ್ಯ;
	      ವೃಕ್ಷ id2 = c_parser_peek_nth_token (parser, 3)->ಮೌಲ್ಯ;
	      ಯದಿ (strcmp (IDENTIFIER_POINTER (id1), "declare") == 0
		  && strcmp (IDENTIFIER_POINTER (id2), "variant") == 0)
		{
		  ಯದಿ (token->pragma_kind == PRAGMA_OMP_BEGIN)
		    depth++;
		  ಅನ್ಯಥಾ
		    depth--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	  ಅನುವರ್ತ;

	ಸ್ವಭಾವ:
	  ಭಙ್ಗ;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Skip tokens until we have consumed an entire block, or until we
   have consumed a non-nested ';'.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_skip_to_end_of_block_or_statement (c_parser *parser,
					    ತಾರ್ಕಿಕ metadirective_p = ಅಸತ್ಯ)
{
  unsigned nesting_depth = 0;
  ಪೂರ್ಣಾಙ್ಕ bracket_depth = 0;
  ತಾರ್ಕಿಕ save_error = parser->error;

  ಯಾವತ್ (ಸತ್ಯ)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      ವಿಕಲ್ಪ (token->type)
	{
	ಪಕ್ಷ CPP_EOF:
	  ಪ್ರತ್ಯಾಗಮ;

	ಪಕ್ಷ CPP_PRAGMA_EOL:
	  ಯದಿ (parser->in_pragma)
	    ಪ್ರತ್ಯಾಗಮ;
	  ಭಙ್ಗ;

	ಪಕ್ಷ CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  ಯದಿ (!nesting_depth && (!metadirective_p || bracket_depth <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      ಗಚ್ಛ finished;
	    }
	  ಭಙ್ಗ;

	ಪಕ್ಷ CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  ಯದಿ ((nesting_depth == 0 || --nesting_depth == 0)
	      && (!metadirective_p || bracket_depth <= 0))
	    {
	      c_parser_consume_token (parser);
	      ಗಚ್ಛ finished;
	    }
	  ಭಙ್ಗ;

	ಪಕ್ಷ CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  ಭಙ್ಗ;

	ಪಕ್ಷ CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  ಯದಿ (metadirective_p && nesting_depth == 0)
	    ++bracket_depth;
	  ಭಙ್ಗ;

	ಪಕ್ಷ CPP_CLOSE_PAREN:
	  ಯದಿ (metadirective_p && nesting_depth == 0)
	    --bracket_depth;
	  ಭಙ್ಗ;

	ಪಕ್ಷ CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	  parser->error = save_error;
	  ಅನುವರ್ತ;

	ಸ್ವಭಾವ:
	  ಭಙ್ಗ;
	}

      c_parser_consume_token (parser);
    }

 finished:
  parser->error = ಅಸತ್ಯ;
}

/* CPP's options (initialized by c-opts.cc).  */
ಬಾಹ್ಯ cpp_options *cpp_opts;

/* Save the warning flags which are controlled by __extension__.  */

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ
disable_extension_diagnostics (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಙ್ಕ ret = (pedantic
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
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Restore the warning flags which are controlled by __extension__.
   FLAGS is the return value from disable_extension_diagnostics.  */

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ
restore_extension_diagnostics (ಪೂರ್ಣಾಙ್ಕ flags)
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
ಸಂರಚನಾ oacc_routine_data {
  ತಾರ್ಕಿಕ error_seen; /* Set if error has been reported.  */
  ತಾರ್ಕಿಕ fndecl_seen; /* Set if one fn decl/definition has been seen already.  */
  ವೃಕ್ಷ clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
ಸ್ಥಿರ ವೃಕ್ಷ objc_foreach_break_label, objc_foreach_continue_label;

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
ಸಂರಚನಾ omp_for_parse_data {
  ಗಣನಾ ವೃಕ್ಷ_code code;
  ವೃಕ್ಷ declv, condv, incrv, initv;
  ವೃಕ್ಷ pre_body;
  ವೃಕ್ಷ bindings;
  ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ;	/* Expected nesting depth.  */
  ಪೂರ್ಣಾಙ್ಕ depth;	/* Current nesting depth.  */
  location_t for_loc;
  ತಾರ್ಕಿಕ ordered : 1;
  ತಾರ್ಕಿಕ inscan : 1;
  ತಾರ್ಕಿಕ want_nested_loop : 1;
  ತಾರ್ಕಿಕ in_intervening_code : 1;
  ತಾರ್ಕಿಕ saw_intervening_code: 1;
  ತಾರ್ಕಿಕ perfect_nesting_fail : 1;
  ತಾರ್ಕಿಕ fail : 1;
};

ಸಂರಚನಾ attr_state
{
  /* True if we parsed a musttail attribute for return.  */
  ತಾರ್ಕಿಕ musttail_p;

  ಶೂನ್ಯ reset () { musttail_p = ಅಸತ್ಯ; }
};

ಸ್ಥಿರ ತಾರ್ಕಿಕ c_parser_nth_token_starts_std_attributes (c_parser *,
						      unsigned ಪೂರ್ಣಾಙ್ಕ);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_std_attribute_specifier_sequence (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_external_declaration (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_asm_definition (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_declaration_or_fndef (c_parser *, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ,
					   ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ, ವೃಕ್ಷ * = ರಿಕ್ತ,
					   vec<c_token> * = ರಿಕ್ತ,
					   ತಾರ್ಕಿಕ have_attrs = ಅಸತ್ಯ,
					   ವೃಕ್ಷ attrs = ರಿಕ್ತ,
					   ಸಂರಚನಾ oacc_routine_data * = ರಿಕ್ತ,
					   ತಾರ್ಕಿಕ * = ರಿಕ್ತ);
ಸ್ಥಿರ ತಾರ್ಕಿಕ c_parser_handle_statement_omp_attributes (c_parser *, ವೃಕ್ಷ &,
						      ತಾರ್ಕಿಕ *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_static_assert_declaration_no_semi (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_static_assert_declaration (c_parser *);
ಸ್ಥಿರ ಸಂರಚನಾ c_typespec c_parser_enum_specifier (c_parser *);
ಸ್ಥಿರ ಸಂರಚನಾ c_typespec c_parser_struct_or_union_specifier (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_struct_declaration (c_parser *, ವೃಕ್ಷ *);
ಸ್ಥಿರ ಸಂರಚನಾ c_typespec c_parser_typeof_specifier (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_alignas_specifier (c_parser *);
ಸ್ಥಿರ ಸಂರಚನಾ c_declarator *c_parser_direct_declarator (c_parser *, ತಾರ್ಕಿಕ,
							c_dtr_syn, ತಾರ್ಕಿಕ *);
ಸ್ಥಿರ ಸಂರಚನಾ c_declarator *c_parser_direct_declarator_inner (c_parser *,
							      ತಾರ್ಕಿಕ,
							      ಸಂರಚನಾ c_declarator *);
ಸ್ಥಿರ ಸಂರಚನಾ c_arg_info *c_parser_parms_declarator (c_parser *, ತಾರ್ಕಿಕ, ವೃಕ್ಷ,
						     ತಾರ್ಕಿಕ);
ಸ್ಥಿರ ಸಂರಚನಾ c_arg_info *c_parser_parms_list_declarator (c_parser *, ವೃಕ್ಷ,
							  ವೃಕ್ಷ, ತಾರ್ಕಿಕ);
ಸ್ಥಿರ ಸಂರಚನಾ c_parm *c_parser_parameter_declaration (c_parser *, ವೃಕ್ಷ, ತಾರ್ಕಿಕ);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_asm_string_literal (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_simple_asm_ಅಭಿವ್ಯಕ್ತಿ (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_gnu_attributes (c_parser *);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_initializer (c_parser *, ವೃಕ್ಷ);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_braced_init (c_parser *, ವೃಕ್ಷ, ತಾರ್ಕಿಕ,
					   ಸಂರಚನಾ obstack *, ತಾರ್ಕಿಕ);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_initelt (c_parser *, ಸಂರಚನಾ obstack *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_initval (c_parser *, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ *,
			      ಸಂರಚನಾ obstack *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_compound_statement (c_parser *, location_t * = ರಿಕ್ತ);
ಸ್ಥಿರ location_t c_parser_compound_statement_nostart (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_label (c_parser *, ವೃಕ್ಷ);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_statement (c_parser *, ತಾರ್ಕಿಕ *, location_t * = ರಿಕ್ತ);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_statement_after_labels (c_parser *, ತಾರ್ಕಿಕ *, ವೃಕ್ಷ,
					     vec<ವೃಕ್ಷ> * = ರಿಕ್ತ,
					     attr_state = {});
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_c99_block_statement (c_parser *, ತಾರ್ಕಿಕ *,
					  location_t * = ರಿಕ್ತ);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_if_statement (c_parser *, ತಾರ್ಕಿಕ *, vec<ವೃಕ್ಷ> *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_switch_statement (c_parser *, ತಾರ್ಕಿಕ *, ವೃಕ್ಷ);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_while_statement (c_parser *, ತಾರ್ಕಿಕ, unsigned short, ತಾರ್ಕಿಕ,
				      ತಾರ್ಕಿಕ *, ವೃಕ್ಷ);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_do_statement (c_parser *, ತಾರ್ಕಿಕ, unsigned short, ತಾರ್ಕಿಕ,
				   ವೃಕ್ಷ);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_for_statement (c_parser *, ತಾರ್ಕಿಕ, unsigned short, ತಾರ್ಕಿಕ,
				    ತಾರ್ಕಿಕ *, ವೃಕ್ಷ);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_asm_statement (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_asm_operands (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_asm_goto_operands (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_asm_clobbers (c_parser *);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (c_parser *, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ *,
					      ವೃಕ್ಷ = NULL_ವೃಕ್ಷ);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_conditional_expression (c_parser *,
						      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ *, ವೃಕ್ಷ);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_ದ್ವಿಮಾನ_expression (c_parser *, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ *,
						 ವೃಕ್ಷ);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_cast_expression (c_parser *, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ *);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_unary_expression (c_parser *);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_sizeof_or_countof_expression (c_parser *,
							    ಗಣನಾ rid);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_alignof_expression (c_parser *);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_maxof_or_minof_expression (c_parser *, ಗಣನಾ rid);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_postfix_expression (c_parser *);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_postfix_expression_after_paren_type (c_parser *,
								   ಸಂರಚನಾ c_declspecs *,
								   ಸಂರಚನಾ c_type_name *,
								   location_t);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_postfix_expression_after_primary (c_parser *,
								location_t loc,
								ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_transaction (c_parser *, ಗಣನಾ rid);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_transaction_expression (c_parser *, ಗಣನಾ rid);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_transaction_cancel (c_parser *);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_expression (c_parser *);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_expression_conv (c_parser *);
ಸ್ಥಿರ vec<ವೃಕ್ಷ, va_gc> *c_parser_ಅಭಿವ್ಯಕ್ತಿ_list (c_parser *, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ,
					     vec<ವೃಕ್ಷ, va_gc> **, location_t *,
					     ವೃಕ್ಷ *, vec<location_t> *,
					     unsigned ಪೂರ್ಣಾಙ್ಕ * = ರಿಕ್ತ);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_has_attribute_expression (c_parser *);

ಸ್ಥಿರ ಶೂನ್ಯ c_parser_oacc_declare (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_oacc_enter_exit_data (c_parser *, ತಾರ್ಕಿಕ);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_oacc_update (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_construct (c_parser *, ತಾರ್ಕಿಕ *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_groupprivate (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_threadprivate (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_barrier (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_depobj (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_flush (c_parser *);
ಸ್ಥಿರ ತಾರ್ಕಿಕ c_parser_omp_next_tokens_can_be_canon_loop (c_parser *,
							ಗಣನಾ ವೃಕ್ಷ_code, ತಾರ್ಕಿಕ);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_omp_loop_nest (c_parser *, ತಾರ್ಕಿಕ *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_omp_for_loop (location_t, c_parser *, ಗಣನಾ ವೃಕ್ಷ_code,
				   ವೃಕ್ಷ, ವೃಕ್ಷ *, ತಾರ್ಕಿಕ *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_taskwait (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_taskyield (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_cancel (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_nothing (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_metadirective (c_parser *, ತಾರ್ಕಿಕ *);

ಗಣನಾ pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
ಸ್ಥಿರ ತಾರ್ಕಿಕ c_parser_pragma (c_parser *, ಗಣನಾ pragma_context, ತಾರ್ಕಿಕ *, ವೃಕ್ಷ);
ಸ್ಥಿರ ತಾರ್ಕಿಕ c_parser_omp_cancellation_point (c_parser *, ಗಣನಾ pragma_context);
ಸ್ಥಿರ ತಾರ್ಕಿಕ c_parser_omp_target (c_parser *, ಗಣನಾ pragma_context, ತಾರ್ಕಿಕ *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_begin (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_end (c_parser *);
ಸ್ಥಿರ ತಾರ್ಕಿಕ c_parser_omp_declare (c_parser *, ಗಣನಾ pragma_context);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_requires (c_parser *);
ಸ್ಥಿರ ತಾರ್ಕಿಕ c_parser_omp_error (c_parser *, ಗಣನಾ pragma_context);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_assumption_clauses (c_parser *, ತಾರ್ಕಿಕ);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_allocate (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_assumes (c_parser *);
ಸ್ಥಿರ ತಾರ್ಕಿಕ c_parser_omp_ordered (c_parser *, ಗಣನಾ pragma_context, ತಾರ್ಕಿಕ *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_omp_dispatch (location_t, c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_omp_interop (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_oacc_routine (c_parser *, ಗಣನಾ pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_objc_class_definition (c_parser *, ವೃಕ್ಷ);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_objc_class_instance_variables (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_objc_class_declaration (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_objc_alias_declaration (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_objc_protocol_definition (c_parser *, ವೃಕ್ಷ);
ಸ್ಥಿರ ತಾರ್ಕಿಕ c_parser_objc_method_type (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_objc_method_definition (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_objc_methodprotolist (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_objc_methodproto (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_objc_method_decl (c_parser *, ತಾರ್ಕಿಕ, ವೃಕ್ಷ *, ವೃಕ್ಷ *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_objc_type_name (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_objc_protocol_refs (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_objc_try_catch_finally_statement (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_objc_synchronized_statement (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_objc_selector (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_objc_selector_arg (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_objc_receiver (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_objc_message_args (c_parser *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_objc_keywordexpr (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_objc_at_property_declaration (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_objc_at_synthesize_declaration (c_parser *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_objc_at_dynamic_declaration (c_parser *);
ಸ್ಥಿರ ತಾರ್ಕಿಕ c_parser_objc_diagnose_bad_element_prefix
  (c_parser *, ಸಂರಚನಾ c_declspecs *);
ಸ್ಥಿರ location_t c_parser_parse_rtl_body (c_parser *, ವರ್ಣ *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_handle_musttail (c_parser *, ವೃಕ್ಷ, attr_state &);

#ಯದಿ ENABLE_ANALYZER

ನಾಮಾಕಾಶ ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

ವರ್ಗ c_translation_unit : ಸಾರ್ವಜನಿಕ translation_unit
{
ಸಾರ್ವಜನಿಕ:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  ವೃಕ್ಷ lookup_constant_by_id (ವೃಕ್ಷ id) ಧ್ರುವ final override
  {
    /* Consider decls.  */
    ಯದಿ (ವೃಕ್ಷ decl = lookup_name (id))
      ಯದಿ (ವೃಕ್ಷ_CODE (decl) == CONST_DECL)
	ಯದಿ (ವೃಕ್ಷ ಮೌಲ್ಯ = DECL_INITIAL (decl))
	  ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == INTEGER_CST)
	    ಪ್ರತ್ಯಾಗಮ ಮೌಲ್ಯ;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    ಯದಿ (cpp_macro_p (hashnode))
      ಯದಿ (ವೃಕ್ಷ ಮೌಲ್ಯ = consider_macro (hashnode->ಮೌಲ್ಯ.macro))
	ಪ್ರತ್ಯಾಗಮ ಮೌಲ್ಯ;

    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  }

  ವೃಕ್ಷ
  lookup_type_by_id (ವೃಕ್ಷ id) ಧ್ರುವ final override
  {
    ಯದಿ (ವೃಕ್ಷ type_decl = lookup_name (id))
	ಯದಿ (ವೃಕ್ಷ_CODE (type_decl) == TYPE_DECL)
	  {
	    ವೃಕ್ಷ record_type = ವೃಕ್ಷ_TYPE (type_decl);
	    ಯದಿ (ವೃಕ್ಷ_CODE (record_type) == RECORD_TYPE)
	      ಪ್ರತ್ಯಾಗಮ record_type;
	  }

    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  }

  ವೃಕ್ಷ
  lookup_global_var_by_id (ವೃಕ್ಷ id) ಧ್ರುವ final override
  {
    ಯದಿ (ವೃಕ್ಷ var_decl = lookup_name (id))
      ಯದಿ (ವೃಕ್ಷ_CODE (var_decl) == VAR_DECL)
				ಪ್ರತ್ಯಾಗಮ var_decl;

    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  }

ಗುಪ್ತ:
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
  ವೃಕ್ಷ consider_macro (cpp_macro *macro, ಪೂರ್ಣಾಙ್ಕ depth = 0) ಧ್ರುವ
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (depth >= 0);

    ಯದಿ (macro->paramc > 0)
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    ಯದಿ (macro->kind != cmk_macro)
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    ಯದಿ (macro->ಎಣಿಕೆ != 1)
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    ಧ್ರುವ cpp_token &tok = macro->exp.tokens[0];
    ಯದಿ (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	ಯದಿ (depth >= param_analyzer_max_macro_alias_depth)
	  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

	cpp_hashnode *alias = tok.val.ಗಂಟು.ಗಂಟು;
	ಯದಿ (cpp_macro_p (alias))
	  ಪ್ರತ್ಯಾಗಮ consider_macro (alias->ಮೌಲ್ಯ.macro, depth + 1);

	/* Not a simple alias.  */
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
      }
    ಅನ್ಯಥಾ ಯದಿ (tok.type != CPP_ಸಂಖ್ಯೆ)
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

    cpp_reader *old_parse_in = parse_in;
    parse_in = cpp_create_reader (CLK_GNUC89, ರಿಕ್ತ, ಸಾಲು_table);

    pretty_printer pp;
    pp_string (&pp, (ಧ್ರುವ ವರ್ಣ *) tok.val.str.text);
    pp_newline (&pp);
    cpp_ತಳ್ಳು_buffer (parse_in,
		     (ಧ್ರುವ unsigned ವರ್ಣ *) pp_formatted_text (&pp),
		     strlen (pp_formatted_text (&pp)),
		     0);

    ವೃಕ್ಷ ಮೌಲ್ಯ;
    location_t loc;
    unsigned ವರ್ಣ cpp_flags;
    c_lex_with_flags (&ಮೌಲ್ಯ, &loc, &cpp_flags, 0);

    cpp_destroy (parse_in);
    parse_in = old_parse_in;

    ಯದಿ (ಮೌಲ್ಯ && ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == INTEGER_CST)
      ಪ್ರತ್ಯಾಗಮ ಮೌಲ್ಯ;

    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_translation_unit (c_parser *parser)
{
  ಯದಿ (c_parser_next_token_is (parser, CPP_EOF))
    {
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C forbids an empty translation unit");
    }
  ಅನ್ಯಥಾ
    {
      ಶೂನ್ಯ *obstack_position = obstack_alloc (&parser_obstack, 0);
      mark_valid_location_for_stdc_pragma (ಅಸತ್ಯ);
      ಕುರು
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_EOF));
    }

  unsigned ಪೂರ್ಣಾಙ್ಕ i;
  ವೃಕ್ಷ decl;
  FOR_EACH_VEC_ELT (incomplete_record_decls, i, decl)
    ಯದಿ (DECL_SIZE (decl) == NULL_ವೃಕ್ಷ && ವೃಕ್ಷ_TYPE (decl) != error_mark_ಗಂಟು)
      error ("storage size of %q+D isn%'t known", decl);

  ಯದಿ (vec_safe_length (current_omp_declare_target_attribute))
    {
      c_omp_declare_target_attr
	a = current_omp_declare_target_attribute->ತೆಗೆ ();
      ಯದಿ (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_safe_truncate (current_omp_declare_target_attribute, 0);
    }
  ಯದಿ (vec_safe_length (current_omp_begin_assumes))
    {
      ಯದಿ (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_safe_truncate (current_omp_begin_assumes, 0);
    }
  ಯದಿ (vec_safe_length (current_omp_declare_variant_attribute))
    {
      ಯದಿ (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_safe_truncate (current_omp_declare_variant_attribute, 0);
    }
  ಯದಿ (vec_safe_length (omp_begin_declare_variant_map))
    {
      unsigned ಪೂರ್ಣಾಙ್ಕ i;
      omp_begin_declare_variant_map_entry *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_finish_variant_function (e->variant, e->id, e->ctx);
      vec_safe_truncate (omp_begin_declare_variant_map, 0);
    }

#ಯದಿ ENABLE_ANALYZER
  ಯದಿ (flag_analyzer)
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_external_declaration (c_parser *parser)
{
  ಪೂರ್ಣಾಙ್ಕ ext;
  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
    {
    ಪಕ್ಷ CPP_KEYWORD:
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->keyword)
	{
	ಪಕ್ಷ RID_EXTENSION:
	  ext = disable_extension_diagnostics ();
	  c_parser_consume_token (parser);
	  c_parser_external_declaration (parser);
	  restore_extension_diagnostics (ext);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_ASM:
	  c_parser_asm_definition (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_INTERFACE:
	ಪಕ್ಷ RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_definition (parser, NULL_ವೃಕ್ಷ);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_protocol_definition (parser, NULL_ವೃಕ್ಷ);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_PROPERTY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_property_declaration (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_SYNTHESIZE:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_synthesize_declaration (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_DYNAMIC:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_dynamic_declaration (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_END:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_finish_implementation ();
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  ಗಚ್ಛ decl_or_fndef;
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_SEMICOLON:
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_PRAGMA:
      mark_valid_location_for_stdc_pragma (ಸತ್ಯ);
      c_parser_pragma (parser, pragma_external, ರಿಕ್ತ, NULL_ವೃಕ್ಷ);
      mark_valid_location_for_stdc_pragma (ಅಸತ್ಯ);
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_PLUS:
    ಪಕ್ಷ CPP_MINUS:
      ಯದಿ (c_dialect_objc ())
	{
	  c_parser_objc_method_definition (parser);
	  ಭಙ್ಗ;
	}
      /* Else fall through, and yield a syntax error trying to parse
	 as a declaration or function definition.  */
      /* FALLTHRU */
    ಸ್ವಭಾವ:
    decl_or_fndef:
      /* A declaration or a function definition (or, in Objective-C,
	 an @interface or @protocol with prefix attributes).  We can
	 only tell which after parsing the declaration specifiers, if
	 any, and the first declarator.  */
      c_parser_declaration_or_fndef (parser, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಅಸತ್ಯ, ಸತ್ಯ,
				     ಅಸತ್ಯ);
      ಭಙ್ಗ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ c_parser_handle_directive_omp_attributes (ವೃಕ್ಷ &, vec<c_token> *&,
						      vec<c_token> *);
ಸ್ಥಿರ ಶೂನ್ಯ c_finish_omp_declare_simd (c_parser *, ವೃಕ್ಷ, ವೃಕ್ಷ, vec<c_token> *);
ಸ್ಥಿರ ಶೂನ್ಯ c_finish_oacc_routine (ಸಂರಚನಾ oacc_routine_data *, ವೃಕ್ಷ, ತಾರ್ಕಿಕ);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

ಸ್ಥಿರ ಶೂನ್ಯ
add_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  ಯದಿ (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    ಪ್ರತ್ಯಾಗಮ;

  ವೃಕ್ಷ stmt = build0 (DEBUG_BEGIN_STMT, void_type_ಗಂಟು);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

ಸ್ಥಿರ ವೃಕ್ಷ
handle_assume_attribute (location_t here, ವೃಕ್ಷ attrs, ತಾರ್ಕಿಕ nested)
{
  ಯದಿ (nested)
    ಪ್ರತಿ (ವೃಕ್ಷ attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", ವೃಕ್ಷ_CHAIN (attr)))
      {
	ವೃಕ್ಷ args = ವೃಕ್ಷ_ಮೌಲ್ಯ (attr);
	ಪೂರ್ಣಾಙ್ಕ nargs = list_length (args);
	ಯದಿ (nargs != 1)
	  {
	    error_at (here, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (here, "expected %i, found %i", 1, nargs);
	  }
	ಅನ್ಯಥಾ
	  {
	    ವೃಕ್ಷ arg = ವೃಕ್ಷ_ಮೌಲ್ಯ (args);
	    arg = c_objc_common_truthvalue_conversion (here, arg);
	    arg = c_fully_fold (arg, ಅಸತ್ಯ, ರಿಕ್ತ);
	    ಯದಿ (arg != error_mark_ಗಂಟು)
	      {
		ವೃಕ್ಷ fn = build_call_ಅಭಿವ್ಯಕ್ತಿ_internal_loc (here, IFN_ASSUME,
							void_type_ಗಂಟು, 1,
							arg);
		add_stmt (fn);
	      }
	  }
      }
  ಅನ್ಯಥಾ
    pedwarn (here, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  ಪ್ರತ್ಯಾಗಮ remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_maybe_reclassify_token (c_parser *parser)
{
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      ಯದಿ (token->id_kind == C_ID_ID || token->id_kind == C_ID_TYPENAME)
	{
	  ವೃಕ್ಷ decl = lookup_name (token->ಮೌಲ್ಯ);

	  token->id_kind = C_ID_ID;
	  ಯದಿ (decl)
	    {
	      ಯದಿ (ವೃಕ್ಷ_CODE (decl) == TYPE_DECL)
		token->id_kind = C_ID_TYPENAME;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (c_dialect_objc ())
	    {
	      ವೃಕ್ಷ objc_interface_decl = objc_is_class_name (token->ಮೌಲ್ಯ);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      ಯದಿ (objc_interface_decl)
		{
		  token->ಮೌಲ್ಯ = objc_interface_decl;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_declaration_or_fndef (c_parser *parser, ತಾರ್ಕಿಕ fndef_ok,
			       ತಾರ್ಕಿಕ static_assert_ok, ತಾರ್ಕಿಕ empty_ok,
			       ತಾರ್ಕಿಕ nested, ತಾರ್ಕಿಕ start_attr_ok,
			       ತಾರ್ಕಿಕ simple_ok,
			       ವೃಕ್ಷ *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       ತಾರ್ಕಿಕ have_attrs /* = false */,
			       ವೃಕ್ಷ attrs /* = NULL_TREE */,
			       ಸಂರಚನಾ oacc_routine_data *oacc_routine_data
			       /* = NULL */,
			       ತಾರ್ಕಿಕ *fallthru_attr_p /* = NULL */)
{
  ಸಂರಚನಾ c_declspecs *specs;
  ವೃಕ್ಷ prefix_attrs;
  ವೃಕ್ಷ all_prefix_attrs;
  ತಾರ್ಕಿಕ diagnosed_no_specs = ಅಸತ್ಯ;
  location_t here = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ result = NULL_ವೃಕ್ಷ;

  add_debug_begin_stmt (c_parser_peek_token (parser)->location);

  ಯದಿ (static_assert_ok
      && c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      ಪ್ರತ್ಯಾಗಮ result;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  ಯದಿ (have_attrs)
    {
      declspecs_add_attrs (here, specs, attrs);
      specs->non_std_attrs_seen_p = ಅಸತ್ಯ;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  ಯದಿ (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_kind == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->ಮೌಲ್ಯ)))
    {
      ವೃಕ್ಷ name = c_parser_peek_token (parser)->ಮೌಲ್ಯ;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (here);
      ಯದಿ (tag_exists_p (RECORD_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.add_fixit_ಸೇರಿಸು_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      ಅನ್ಯಥಾ ಯದಿ (tag_exists_p (UNION_TYPE, name))
	{
	  richloc.add_fixit_ಸೇರಿಸು_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      ಅನ್ಯಥಾ ಯದಿ (tag_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.add_fixit_ಸೇರಿಸು_before ("enum ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<enum%> keyword to refer to the type",
		    name);
	}
      ಅನ್ಯಥಾ
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (name, FUZZY_LOOKUP_TYPENAME,
					      here);
	  ಯದಿ (ಧ್ರುವ ವರ್ಣ *suggestion = hint.suggestion ())
	    {
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			name, suggestion);
	    }
	  ಅನ್ಯಥಾ
	    error_at (here, "unknown type name %qE", name);
	}

      /* Parse declspecs normally to get a correct pointer type, but avoid
         a further "fails to be a type name" error.  Refuse nested functions
         since it is not how the user likely wants us to recover.  */
      c_parser_peek_token (parser)->type = CPP_KEYWORD;
      c_parser_peek_token (parser)->keyword = RID_VOID;
      c_parser_peek_token (parser)->ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  ಯದಿ (c_parser_nth_token_starts_std_attributes (parser, 1))
    have_attrs = ಸತ್ಯ;

  c_parser_declspecs (parser, specs, ಸತ್ಯ, ಸತ್ಯ, start_attr_ok,
		      ಸತ್ಯ, ಸತ್ಯ, start_attr_ok, ಸತ್ಯ, cla_nonabstract_decl);
  ಯದಿ (parser->error)
    {
      c_parser_skip_to_end_of_block_or_statement (parser);
      ಪ್ರತ್ಯಾಗಮ result;
    }
  ಯದಿ (nested && !specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_end_of_block_or_statement (parser);
      ಪ್ರತ್ಯಾಗಮ result;
    }

  finish_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  ಯದಿ (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_ತುದಿ_anonymous_type (specs->type);

  ತಾರ್ಕಿಕ gnu_auto_type_p = specs->typespec_word == cts_auto_type;
  ತಾರ್ಕಿಕ std_auto_type_p = specs->c23_auto_p;
  ತಾರ್ಕಿಕ any_auto_type_p = gnu_auto_type_p || std_auto_type_p;
  gcc_assert (!(gnu_auto_type_p && std_auto_type_p));
  ಧ್ರುವ ವರ್ಣ *auto_type_keyword = gnu_auto_type_p ? "__auto_type" : "auto";
  ಯದಿ (specs->constexpr_p)
    {
      /* An underspecified declaration may not declare tags or members
	 or structures or unions; it is undefined behavior to declare
	 the members of an enumeration.  Where the structure, union or
	 enumeration type is declared within an initializer, this is
	 diagnosed elsewhere.  Diagnose here the case of declaring
	 such a type in the type specifiers of a constexpr
	 declaration.  */
      ವಿಕಲ್ಪ (specs->typespec_kind)
	{
	ಪಕ್ಷ ctsk_tagfirstref:
	ಪಕ್ಷ ctsk_tagfirstref_attrs:
	  error_at (here, "%qT declared in underspecified object declaration",
		    specs->type);
	  ಭಙ್ಗ;

	ಪಕ್ಷ ctsk_tagdef:
	  error_at (here, "%qT defined in underspecified object declaration",
		    specs->type);
	  ಭಙ್ಗ;

	ಸ್ವಭಾವ:
	  ಭಙ್ಗ;
	}
    }

  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      ತಾರ್ಕಿಕ handled_assume = ಅಸತ್ಯ;
      ಯದಿ (specs->attrs
	  && !nested
	  && specs->typespec_kind == ctsk_none
	  && c_parser_handle_statement_omp_attributes (parser, specs->attrs,
						       ರಿಕ್ತ))
	{
	  ಯದಿ (specs->attrs)
	    c_warn_unused_attributes (specs->attrs);
	  ಯಾವತ್ (parser->in_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_next_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, ರಿಕ್ತ, NULL_ವೃಕ್ಷ);
	    }
	  c_parser_consume_token (parser);
	  ಪ್ರತ್ಯಾಗಮ result;
	}
      ಯದಿ (specs->typespec_kind == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = ಸತ್ಯ;
	  specs->attrs
	    = handle_assume_attribute (here, specs->attrs, nested);
	}
      ಯದಿ (any_auto_type_p)
	error_at (here, "%qs in empty declaration", auto_type_keyword);
      ಅನ್ಯಥಾ ಯದಿ (specs->typespec_kind == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  ಯದಿ (fallthru_attr_p != ರಿಕ್ತ)
	    *fallthru_attr_p = ಸತ್ಯ;
	  ಯದಿ (nested)
	    {
	      ವೃಕ್ಷ fn = build_call_ಅಭಿವ್ಯಕ್ತಿ_internal_loc (here, IFN_FALLTHROUGH,
						      void_type_ಗಂಟು, 0);
	      add_stmt (fn);
	    }
	  ಅನ್ಯಥಾ
	    pedwarn (here, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      ಅನ್ಯಥಾ ಯದಿ (empty_ok
	       && !(have_attrs && specs->non_std_attrs_seen_p)
	       && !handled_assume)
	shadow_tag (specs);
      ಅನ್ಯಥಾ
	{
	  shadow_tag_warned (specs, 1);
	  ಯದಿ (!handled_assume)
	    pedwarn (here, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      ಯದಿ (specs->ಅಭಿವ್ಯಕ್ತಿ)
	add_stmt (fold_convert (void_type_ಗಂಟು, specs->ಅಭಿವ್ಯಕ್ತಿ));
      c_parser_consume_token (parser);
      ಯದಿ (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, NULL_ವೃಕ್ಷ, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ result;
    }
  ಅನ್ಯಥಾ ಯದಿ (specs->typespec_kind == ctsk_none
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
      ಯದಿ (astate.musttail_p)
	{
	  ಯದಿ (specs->attrs)
	    {
	      auto_urlify_attributes sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, ರಿಕ್ತ, NULL_ವೃಕ್ಷ, ರಿಕ್ತ,
					   astate);
	  ಪ್ರತ್ಯಾಗಮ result;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  ಯದಿ (empty_ok
      && specs->typespec_kind == ctsk_tagdef
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = ಅಸತ್ಯ;
      shadow_tag_warned (specs, 1);
      ಪ್ರತ್ಯಾಗಮ result;
    }
  ಅನ್ಯಥಾ ಯದಿ (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
	{
	  ಪಕ್ಷ CPP_PLUS:
	  ಪಕ್ಷ CPP_MINUS:
	    ಯದಿ (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      ಪ್ರತ್ಯಾಗಮ result;
	    ಯದಿ (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_ವೃಕ್ಷ;
	      }
	    ಯದಿ (fndef_ok)
	      c_parser_objc_method_definition (parser);
	    ಅನ್ಯಥಾ
	      c_parser_objc_methodproto (parser);
	    ಪ್ರತ್ಯಾಗಮ result;
	    ಭಙ್ಗ;
	  ಸ್ವಭಾವ:
	    ಭಙ್ಗ;
	}
      /* This is where we parse 'attributes @interface ...',
	 'attributes @implementation ...', 'attributes @protocol ...'
	 (where attributes could be, for example, __attribute__
	 ((deprecated)).
      */
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->keyword)
	{
	ಪಕ್ಷ RID_AT_INTERFACE:
	  {
	    ಯದಿ (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      ಪ್ರತ್ಯಾಗಮ result;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    ಪ್ರತ್ಯಾಗಮ result;
	  }
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_IMPLEMENTATION:
	  {
	    ಯದಿ (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      ಪ್ರತ್ಯಾಗಮ result;
	    ಯದಿ (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_ವೃಕ್ಷ;
	      }
	    c_parser_objc_class_definition (parser, NULL_ವೃಕ್ಷ);
	    ಪ್ರತ್ಯಾಗಮ result;
	  }
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_PROTOCOL:
	  {
	    ಯದಿ (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      ಪ್ರತ್ಯಾಗಮ result;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    ಪ್ರತ್ಯಾಗಮ result;
	  }
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_ALIAS:
	ಪಕ್ಷ RID_AT_CLASS:
	ಪಕ್ಷ RID_AT_END:
	ಪಕ್ಷ RID_AT_PROPERTY:
	  ಯದಿ (specs->attrs)
	    {
	      c_parser_error (parser, "unexpected attribute");
	      specs->attrs = ರಿಕ್ತ;
	    }
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  ಭಙ್ಗ;
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (attribute_fallthrough_p (specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  ಅನ್ಯಥಾ ಯದಿ (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_attributes (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ more_than_one_decl = ಅಸತ್ಯ;
  ಯಾವತ್ (ಸತ್ಯ)
    {
      ಸಂರಚನಾ c_declarator *declarator;
      ತಾರ್ಕಿಕ dummy = ಅಸತ್ಯ;
      timevar_id_t tv;
      ವೃಕ್ಷ fnbody = NULL_ವೃಕ್ಷ;
      ವೃಕ್ಷ underspec_name = NULL_ವೃಕ್ಷ;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_kind != ctsk_none,
					C_DTR_NORMAL, &dummy);
      ಯದಿ (declarator == ರಿಕ್ತ)
	{
	  ಯದಿ (omp_declare_simd_clauses)
	    c_finish_omp_declare_simd (parser, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ,
				       omp_declare_simd_clauses);
	  ಯದಿ (oacc_routine_data)
	    c_finish_oacc_routine (oacc_routine_data, NULL_ವೃಕ್ಷ, ಅಸತ್ಯ);
	  /* This check is here purely to improve the diagnostic.  */
	  ಯದಿ (!simple_ok)
	    c_parser_skip_to_end_of_block_or_statement (parser);
	  ಪ್ರತ್ಯಾಗಮ result;
	}
      ಯದಿ (flag_openmp || flag_openmp_simd)
	{
	  ಸಂರಚನಾ c_declarator *d = declarator;
	  ಯಾವತ್ (d->kind != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = ರಿಕ್ತ;
	  c_parser_handle_directive_omp_attributes (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      ಯದಿ (gnu_auto_type_p && declarator->kind != cdk_id)
	{
	  error_at (here,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  ಪ್ರತ್ಯಾಗಮ result;
	}
      ಯದಿ (std_auto_type_p)
	{
	  ಸಂರಚನಾ c_declarator *d = declarator;
	  ಯಾವತ್ (d->kind == cdk_attrs)
	    d = d->declarator;
	  ಯದಿ (d->kind != cdk_id)
	    {
	      error_at (here,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      ಪ್ರತ್ಯಾಗಮ result;
	    }
	  underspec_name = d->u.id.id;
	}
      ಅನ್ಯಥಾ ಯದಿ (specs->constexpr_p)
	{
	  ಸಂರಚನಾ c_declarator *d = declarator;
	  ಯಾವತ್ (d->kind != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      ಯದಿ (c_parser_next_token_is (parser, CPP_EQ)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is_keyword (parser, RID_ASM)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_next_token_is_keyword (parser, RID_IN))
	{
	  ವೃಕ್ಷ asm_name = NULL_ವೃಕ್ಷ;
	  ವೃಕ್ಷ postfix_attrs = NULL_ವೃಕ್ಷ;
	  ಯದಿ (!diagnosed_no_specs && !specs->declspecs_seen_p)
	    {
	      diagnosed_no_specs = ಸತ್ಯ;
	      pedwarn (here, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = ಅಸತ್ಯ;
	  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_ಅಭಿವ್ಯಕ್ತಿ (parser);
	  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_attributes (parser);
	      ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (here, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  ಪ್ರತ್ಯಾಗಮ result;
		}
	    }
	  ಯದಿ (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      ವೃಕ್ಷ d;
	      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      ಯದಿ (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (ಸಾಲು_table, init_loc);
		  unsigned ಪೂರ್ಣಾಙ್ಕ underspec_state = 0;
		  ಯದಿ (std_auto_type_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  start_init (NULL_ವೃಕ್ಷ, asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  ಯದಿ (nested && !empty_ok)
		    flag_sanitize = 0;
		  init = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
		  ಯದಿ (std_auto_type_p)
		    finish_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  ಯದಿ (gnu_auto_type_p
		      && ವೃಕ್ಷ_CODE (init.ಮೌಲ್ಯ) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (ವೃಕ್ಷ_OPERAND (init.ಮೌಲ್ಯ, 1)))
		    error_at (here,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_to_rvalue (init_loc, init, ಸತ್ಯ, ಸತ್ಯ,
						   ಸತ್ಯ);
		  ವೃಕ್ಷ init_type = ವೃಕ್ಷ_TYPE (init.ಮೌಲ್ಯ);
		  ತಾರ್ಕಿಕ vm_type = c_type_variably_modified_p (init_type);
		  ಯದಿ (vm_type)
		    init.ಮೌಲ್ಯ = save_ಅಭಿವ್ಯಕ್ತಿ (init.ಮೌಲ್ಯ);
		  finish_init ();
		  specs->typespec_kind = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = ಸತ್ಯ;
		  specs->type = init_type;
		  ಯದಿ (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_attributes (specs->type,
						  specs->postfix_attrs);
		      decl_attributes (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_ವೃಕ್ಷ;
		    }
		  ಯದಿ (vm_type)
		    {
		      ತಾರ್ಕಿಕ maybe_const = ಸತ್ಯ;
		      ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (init.ಮೌಲ್ಯ, ಅಸತ್ಯ,
						     &maybe_const);
		      specs->ಅಭಿವ್ಯಕ್ತಿ_const_operands &= maybe_const;
		      ಯದಿ (specs->ಅಭಿವ್ಯಕ್ತಿ)
			specs->ಅಭಿವ್ಯಕ್ತಿ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ,
					      ವೃಕ್ಷ_TYPE (type_ಅಭಿವ್ಯಕ್ತಿ),
					      specs->ಅಭಿವ್ಯಕ್ತಿ, type_ಅಭಿವ್ಯಕ್ತಿ);
		      ಅನ್ಯಥಾ
			specs->ಅಭಿವ್ಯಕ್ತಿ = type_ಅಭಿವ್ಯಕ್ತಿ;
		    }
		  d = start_decl (declarator, specs, ಸತ್ಯ,
				  chainon (postfix_attrs, all_prefix_attrs));
		  ಯದಿ (!d)
		    d = error_mark_ಗಂಟು;
		  ಯದಿ (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_ವೃಕ್ಷ,
					       omp_declare_simd_clauses);
		  ಯದಿ (!omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_ವೃಕ್ಷ,
					       &omp_dsimd_idattr_clauses);
		}
	      ಅನ್ಯಥಾ
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (ಸಾಲು_table, init_loc);
		  unsigned ಪೂರ್ಣಾಙ್ಕ underspec_state = 0;
		  ಯದಿ (specs->constexpr_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  d = start_decl (declarator, specs, ಸತ್ಯ,
				  chainon (postfix_attrs,
					   all_prefix_attrs),
				  !specs->constexpr_p);
		  ಯದಿ (!d)
		    d = error_mark_ಗಂಟು;
		  ಯದಿ (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_ವೃಕ್ಷ,
					       omp_declare_simd_clauses);
		  ಯದಿ (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_ವೃಕ್ಷ,
					       &omp_dsimd_idattr_clauses);
		  start_init (d, asm_name,
			      ವೃಕ್ಷ_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  ಯದಿ (ವೃಕ್ಷ_CODE (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  ಯದಿ (specs->constexpr_p)
		    {
		      finish_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      ಯದಿ (omp_declare_simd_clauses)
			c_finish_omp_declare_simd (parser, d, NULL_ವೃಕ್ಷ,
						   omp_declare_simd_clauses);
		  ಯದಿ (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_ವೃಕ್ಷ,
					       &omp_dsimd_idattr_clauses);
		    }
		  finish_init ();
		}
	      ಯದಿ (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, ಅಸತ್ಯ);
	      ಯದಿ (d != error_mark_ಗಂಟು)
		{
		  maybe_warn_string_init (init_loc, ವೃಕ್ಷ_TYPE (d), init);
		  finish_decl (d, init_loc, init.ಮೌಲ್ಯ,
			       init.original_type, asm_name);
		  result = d;
		}
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಯದಿ (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  ಪ್ರತ್ಯಾಗಮ result;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      ವೃಕ್ಷ attrs = chainon (postfix_attrs, all_prefix_attrs);
	      ವೃಕ್ಷ d = start_decl (declarator, specs, ಅಸತ್ಯ, attrs, ಸತ್ಯ,
				   &lastloc);
	      ಯದಿ (d && ವೃಕ್ಷ_CODE (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  ಧ್ರುವ ಸಂರಚನಾ c_declarator *decl = declarator;
		  ಧ್ರುವ ಸಂರಚನಾ c_declarator *last_non_id_attrs = ರಿಕ್ತ;

		  ಯಾವತ್ (decl)
		    ವಿಕಲ್ಪ (decl->kind)
		      {
		      ಪಕ್ಷ cdk_array:
		      ಪಕ್ಷ cdk_function:
		      ಪಕ್ಷ cdk_pointer:
			last_non_id_attrs = decl;
			decl = decl->declarator;
			ಭಙ್ಗ;

		      ಪಕ್ಷ cdk_attrs:
			decl = decl->declarator;
			ಭಙ್ಗ;

		      ಪಕ್ಷ cdk_id:
			decl = 0;
			ಭಙ್ಗ;

		      ಸ್ವಭಾವ:
			gcc_unreachable ();
		      }

		  /* If it exists and is cdk_function declaration whose
		     arguments have not been set yet, use its arguments.  */
		  ಯದಿ (last_non_id_attrs
		      && last_non_id_attrs->kind == cdk_function)
		    {
		      ವೃಕ್ಷ parms = last_non_id_attrs->u.arg_info->parms;
		      ಯದಿ (DECL_ARGUMENTS (d) == NULL_ವೃಕ್ಷ
			  && DECL_INITIAL (d) == NULL_ವೃಕ್ಷ)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      ಯದಿ (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_empty ())
		{
		  ವೃಕ್ಷ parms = NULL_ವೃಕ್ಷ;
		  ಯದಿ (d && ವೃಕ್ಷ_CODE (d) == FUNCTION_DECL)
		    {
		      ಸಂರಚನಾ c_declarator *ce = declarator;
		      ಯಾವತ್ (ce != ರಿಕ್ತ)
			ಯದಿ (ce->kind == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    ಭಙ್ಗ;
			  }
			ಅನ್ಯಥಾ
			  ce = ce->declarator;
		    }
		  ಯದಿ (parms)
		    temp_store_parm_decls (d, parms);
		  ಯದಿ (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  ಯದಿ (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  ಯದಿ (parms)
		    temp_ತೆಗೆ_parm_decls ();
		}
	      ಯದಿ (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, ಅಸತ್ಯ);
	      ಯದಿ (d)
		finish_decl (d, UNKNOWN_LOCATION, NULL_ವೃಕ್ಷ,
			     NULL_ವೃಕ್ಷ, asm_name);

	      ಯದಿ (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  ಯದಿ (d)
		    *objc_foreach_object_declaration = d;
		  ಅನ್ಯಥಾ
		    *objc_foreach_object_declaration = error_mark_ಗಂಟು;
		}
	    }
	  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      more_than_one_decl = ಸತ್ಯ;
	      ಯದಿ (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  ಪ್ರತ್ಯಾಗಮ result;
		}
	      c_parser_consume_token (parser);
	      ಯದಿ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
		all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					    prefix_attrs);
	      ಅನ್ಯಥಾ
		all_prefix_attrs = prefix_attrs;
	      ಅನುವರ್ತ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      ಯದಿ (!simple_ok)
		c_parser_consume_token (parser);
	      ಪ್ರತ್ಯಾಗಮ result;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      ಪ್ರತ್ಯಾಗಮ result;
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಯದಿ (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      ಅನ್ಯಥಾ ಯದಿ (more_than_one_decl)
		error_at (here, "declaration in condition can only declare "
			  "a single object");
	      ಪ್ರತ್ಯಾಗಮ result;
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (here,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  ಪ್ರತ್ಯಾಗಮ result;
	}
      ಅನ್ಯಥಾ ಯದಿ (!fndef_ok)
	{
	  ಯದಿ (simple_ok && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  ಅನ್ಯಥಾ
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	    }
	  ಪ್ರತ್ಯಾಗಮ result;
	}
      /* Function definition (nested or otherwise).  */
      ಯದಿ (nested)
	{
	  pedwarn (here, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_ತಳ್ಳು_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      ವೃಕ್ಷ dv_base = NULL_ವೃಕ್ಷ;
      ವೃಕ್ಷ dv_ctx = NULL_ವೃಕ್ಷ;
      ಯದಿ (!vec_safe_is_empty (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->last ();
	  dv_ctx = copy_list (a.selector);
	  dv_base = omp_start_variant_function (declarator, dv_ctx);
	}

      ಯದಿ (!start_function (specs, declarator, all_prefix_attrs))
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
	  ಯದಿ (c_parser_next_token_starts_declspecs (parser))
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
	      parser->error = ಅಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ
	    {
	      /* This can appear in many cases looking nothing like a
		 function definition, so we don't give a more specific
		 error suggesting there was one.  */
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			      "or %<__attribute__%>");
	    }
	  ಯದಿ (nested)
	    c_ತೆಗೆ_function_context ();
	  ಭಙ್ಗ;
	}

      ಯದಿ (DECL_DECLARED_INLINE_P (current_function_decl))
        tv = TV_PARSE_INLINE;
      ಅನ್ಯಥಾ
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
      ಪೂರ್ಣಾಙ್ಕ save_debug_nonbind_markers_p = debug_nonbind_markers_p;
      debug_nonbind_markers_p = 0;
      c_parser_maybe_reclassify_token (parser);
      ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_EOF)
	     && c_parser_next_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ,
				       ಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      ಯದಿ (omp_declare_simd_clauses)
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_ವೃಕ್ಷ,
				   omp_declare_simd_clauses);
      ಯದಿ (!omp_dsimd_idattr_clauses.is_empty ())
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_ವೃಕ್ಷ,
				   &omp_dsimd_idattr_clauses);
      ಯದಿ (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, current_function_decl, ಸತ್ಯ);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_start_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      ಯದಿ (dv_base && current_function_decl != error_mark_ಗಂಟು)
	{
	  omp_begin_declare_variant_map_entry e
	    = { current_function_decl, dv_base, dv_ctx };
	  vec_safe_ತಳ್ಳು (omp_begin_declare_variant_map, e);
	}

      /* If the definition was marked with __RTL, use the RTL parser now,
	 consuming the function body.  */
      ಯದಿ (specs->declspec_il == cdil_rtl)
	{
	  endloc = c_parser_parse_rtl_body (parser, specs->gimple_or_rtl_pass);

	  /* Normally, store_parm_decls sets next_is_function_body,
	     anticipating a function body.  We need a push_scope/pop_scope
	     pair to flush out this state, or subsequent function parsing
	     will go wrong.  */
	  ತಳ್ಳು_scope ();
	  ತೆಗೆ_scope ();

	  finish_function (endloc);
	  ಪ್ರತ್ಯಾಗಮ result;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      ಅನ್ಯಥಾ ಯದಿ (specs->declspec_il != cdil_none)
	{
	  ತಾರ್ಕಿಕ saved = in_late_ದ್ವಿಮಾನ_op;
	  in_late_ದ್ವಿಮಾನ_op = ಸತ್ಯ;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->entry_bb_ಎಣಿಕೆ);
	  in_late_ದ್ವಿಮಾನ_op = saved;
	}
      ಅನ್ಯಥಾ
	fnbody = c_parser_compound_statement (parser, &endloc);
      ವೃಕ್ಷ fndecl = current_function_decl;
      ಯದಿ (nested && specs->declspec_il == cdil_none)
	{
	  ವೃಕ್ಷ decl = current_function_decl;
	  /* Mark nested functions as needing static-chain initially.
	     lower_nested_functions will recompute it but the
	     DECL_STATIC_CHAIN flag is also used before that happens,
	     by initializer_constant_valid_p.  See gcc.dg/nested-fn-2.c.  */
	  DECL_STATIC_CHAIN (decl) = 1;
	  add_stmt (fnbody);
	  finish_function (endloc);
	  c_ತೆಗೆ_function_context ();
	  add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_ಅಭಿವ್ಯಕ್ತಿ, decl));
	}
      ಅನ್ಯಥಾ ಯದಿ (nested)
	{
	  ಯದಿ (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  ಅನ್ಯಥಾ
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  finish_function (endloc);
	  c_ತೆಗೆ_function_context ();
	}
      ಅನ್ಯಥಾ
	{
	  ಯದಿ (fnbody)
	    add_stmt (fnbody);
	  finish_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      ಯದಿ (specs->declspec_il != cdil_none)
	DECL_SAVED_ವೃಕ್ಷ (fndecl) = NULL_ವೃಕ್ಷ;

      ಭಙ್ಗ;
    }

  ಪ್ರತ್ಯಾಗಮ result;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_asm_definition (c_parser *parser)
{
  location_t asm_loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  ವೃಕ್ಷ asm_str = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ outputs = NULL_ವೃಕ್ಷ, inputs = NULL_ವೃಕ್ಷ;
  ಯದಿ (!parens.require_open (parser))
    ಗಚ್ಛ done;
  asm_str = c_parser_asm_string_literal (parser);
  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      ಗಚ್ಛ done;
    }
  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ section = 0; section < 2; ++section)
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  ಯದಿ (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
	      asm_str = NULL_ವೃಕ್ಷ;
	      ಗಚ್ಛ done;
	    }
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ ಯದಿ (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, ಅಸತ್ಯ))
	ಗಚ್ಛ error_close_paren;
      ಯದಿ (!c_parser_next_token_is (parser, CPP_COLON)
	  && !c_parser_next_token_is (parser, CPP_SCOPE)
	  && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ಯದಿ (section)
	    inputs = c_parser_asm_operands (parser);
	  ಅನ್ಯಥಾ
	    outputs = c_parser_asm_operands (parser);
	}
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	ಭಙ್ಗ;
    }

  ಯದಿ (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
      asm_str = NULL_ವೃಕ್ಷ;
    }

  ಯದಿ (asm_str)
    asm_str = build_asm_ಅಭಿವ್ಯಕ್ತಿ (asm_loc, asm_str, outputs, inputs,
			      NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ, ಅಸತ್ಯ, ಅಸತ್ಯ);
done:
  ಯದಿ (asm_str)
    symtab->finalize_toplevel_asm (asm_str);
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse a static assertion (C11 6.7.10).

   static_assert-declaration:
     static_assert-declaration-no-semi ;
*/

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_static_assert_declaration (c_parser *parser)
{
  c_parser_static_assert_declaration_no_semi (parser);
  ಯದಿ (parser->error
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_static_assert_declaration_no_semi (c_parser *parser)
{
  location_t assert_loc, ಮೌಲ್ಯ_loc;
  ವೃಕ್ಷ ಮೌಲ್ಯ;
  ವೃಕ್ಷ string = NULL_ವೃಕ್ಷ;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT));
  ವೃಕ್ಷ spelling = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
  assert_loc = c_parser_peek_token (parser)->location;
  ಯದಿ (flag_isoc99)
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  ಅನ್ಯಥಾ
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  c_parser_consume_token (parser);
  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ;
  location_t ಮೌಲ್ಯ_tok_loc = c_parser_peek_token (parser)->location;
  ಮೌಲ್ಯ = convert_lvalue_to_rvalue (ಮೌಲ್ಯ_tok_loc,
				    c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ),
				    ಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;
  ಮೌಲ್ಯ_loc = ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಮೌಲ್ಯ, ಮೌಲ್ಯ_tok_loc);
  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
	{
	ಪಕ್ಷ CPP_STRING:
	ಪಕ್ಷ CPP_STRING16:
	ಪಕ್ಷ CPP_STRING32:
	ಪಕ್ಷ CPP_WSTRING:
	ಪಕ್ಷ CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, ಅಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  c_parser_error (parser, "expected string literal");
	  ಪ್ರತ್ಯಾಗಮ;
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (flag_isoc11)
    /* If pedantic for pre-C11, the use of _Static_assert itself will
       have been diagnosed, so do not also diagnose the use of this
       new C23 feature of _Static_assert.  */
    pedwarn_c11 (assert_loc, OPT_Wpedantic,
		 "ISO C11 does not support omitting the string in "
		 "%qE", spelling);
  parens.require_close (parser);

  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)))
    {
      error_at (ಮೌಲ್ಯ_loc, "expression in static assertion is not an integer");
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != INTEGER_CST)
    {
      ಮೌಲ್ಯ = c_fully_fold (ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (ಮೌಲ್ಯ);
      ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == INTEGER_CST)
	pedwarn (ಮೌಲ್ಯ_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != INTEGER_CST)
    {
      error_at (ಮೌಲ್ಯ_loc, "expression in static assertion is not constant");
      ಪ್ರತ್ಯಾಗಮ;
    }
  constant_expression_warning (ಮೌಲ್ಯ);
  ಯದಿ (integer_zerop (ಮೌಲ್ಯ))
    {
      ಯದಿ (string)
	error_at (assert_loc, "static assertion failed: %E", string);
      ಅನ್ಯಥಾ
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

ಶೂನ್ಯ
c_parser_declspecs (c_parser *parser, ಸಂರಚನಾ c_declspecs *specs,
		    ತಾರ್ಕಿಕ scspec_ok, ತಾರ್ಕಿಕ typespec_ok, ತಾರ್ಕಿಕ start_attr_ok,
		    ತಾರ್ಕಿಕ alignspec_ok, ತಾರ್ಕಿಕ auto_type_ok,
		    ತಾರ್ಕಿಕ start_std_attr_ok, ತಾರ್ಕಿಕ end_std_attr_ok,
		    ಗಣನಾ c_lookahead_kind la)
{
  ತಾರ್ಕಿಕ attrs_ok = start_attr_ok;
  ತಾರ್ಕಿಕ seen_type = specs->typespec_kind != ctsk_none;

  ಯದಿ (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  ಯದಿ (start_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_seen_p);
      location_t loc = c_parser_peek_token (parser)->location;
      ವೃಕ್ಷ attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_add_attrs (loc, specs, attrs);
      specs->non_std_attrs_seen_p = ಅಸತ್ಯ;
    }

  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_NAME)
	 || c_parser_next_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_next_token_is (parser, CPP_LESS)))
    {
      ಸಂರಚನಾ c_typespec t;
      ವೃಕ್ಷ attrs;
      ವೃಕ್ಷ align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      ಯದಿ ((!typespec_ok || specs->typespec_kind == ctsk_tagdef)
	  && c_parser_next_tokens_start_typename (parser, la)
	  && !c_parser_next_token_is_qualifier (parser)
	  && !c_parser_next_token_is_keyword (parser, RID_ALIGNAS))
	ಭಙ್ಗ;

      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  ವೃಕ್ಷ ಮೌಲ್ಯ = name_token->ಮೌಲ್ಯ;
	  c_id_kind kind = name_token->id_kind;

	  ಯದಿ (kind == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_FIRST_ADDR_SPACE;
	      declspecs_add_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = ಸತ್ಯ;
	      ಅನುವರ್ತ;
	    }

	  gcc_assert (!c_parser_next_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  ಯದಿ (seen_type || !c_parser_next_tokens_start_typename (parser, la))
	    ಭಙ್ಗ;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  seen_type = ಸತ್ಯ;
	  attrs_ok = ಸತ್ಯ;
	  ಯದಿ (kind == C_ID_ID)
	    {
	      auto_diagnostic_group d;
	      name_hint hint = lookup_name_fuzzy (ಮೌಲ್ಯ, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      ಯದಿ (ಧ್ರುವ ವರ್ಣ *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.add_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    ಮೌಲ್ಯ, suggestion);
		}
	      ಅನ್ಯಥಾ
		error_at (loc, "unknown type name %qE", ಮೌಲ್ಯ);
	      t.kind = ctsk_typedef;
	      t.spec = error_mark_ಗಂಟು;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (kind == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_next_token_is_not (parser, CPP_LESS)))
	    {
	      t.kind = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (ಮೌಲ್ಯ);
	    }
	  ಅನ್ಯಥಾ
	    {
	      ವೃಕ್ಷ proto = NULL_ವೃಕ್ಷ;
	      gcc_assert (c_dialect_objc ());
	      t.kind = ctsk_objc;
	      ಯದಿ (c_parser_next_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (ಮೌಲ್ಯ, proto);
	    }
	  t.ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
	  t.ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;
	  t.has_enum_type_specifier = ಅಸತ್ಯ;
	  declspecs_add_type (name_token->location, specs, t);
	  ಅನುವರ್ತ;
	}
      ಯದಿ (c_parser_next_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  ವೃಕ್ಷ proto;
	  gcc_assert (c_dialect_objc ());
	  ಯದಿ (!typespec_ok || seen_type)
	    ಭಙ್ಗ;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.kind = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_ವೃಕ್ಷ, proto);
	  t.ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
	  t.ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;
	  t.has_enum_type_specifier = ಅಸತ್ಯ;
	  declspecs_add_type (loc, specs, t);
	  ಅನುವರ್ತ;
	}
      gcc_assert (c_parser_next_token_is (parser, CPP_KEYWORD));
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->keyword)
	{
	ಪಕ್ಷ RID_STATIC:
	ಪಕ್ಷ RID_EXTERN:
	ಪಕ್ಷ RID_REGISTER:
	ಪಕ್ಷ RID_TYPEDEF:
	ಪಕ್ಷ RID_INLINE:
	ಪಕ್ಷ RID_NORETURN:
	ಪಕ್ಷ RID_AUTO:
	ಪಕ್ಷ RID_THREAD:
	ಪಕ್ಷ RID_CONSTEXPR:
	  ಯದಿ (!scspec_ok)
	    ಗಚ್ಛ out;
	  attrs_ok = ಸತ್ಯ;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_add_scspec (loc, specs,
				c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	  c_parser_consume_token (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AUTO_TYPE:
	  ಯದಿ (!auto_type_ok)
	    ಗಚ್ಛ out;
	  /* Fall through.  */
	ಪಕ್ಷ RID_UNSIGNED:
	ಪಕ್ಷ RID_LONG:
	ಪಕ್ಷ RID_SHORT:
	ಪಕ್ಷ RID_SIGNED:
	ಪಕ್ಷ RID_COMPLEX:
	ಪಕ್ಷ RID_INT:
	ಪಕ್ಷ RID_CHAR:
	ಪಕ್ಷ RID_FLOAT:
	ಪಕ್ಷ RID_DOUBLE:
	ಪಕ್ಷ RID_VOID:
	ಪಕ್ಷ RID_DFLOAT32:
	ಪಕ್ಷ RID_DFLOAT64:
	ಪಕ್ಷ RID_DFLOAT128:
	ಪಕ್ಷ RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	ಪಕ್ಷ RID_BOOL:
	ಪಕ್ಷ RID_FRACT:
	ಪಕ್ಷ RID_ACCUM:
	ಪಕ್ಷ RID_SAT:
	ಪಕ್ಷ RID_INT_N_0:
	ಪಕ್ಷ RID_INT_N_1:
	ಪಕ್ಷ RID_INT_N_2:
	ಪಕ್ಷ RID_INT_N_3:
	  ಯದಿ (!typespec_ok)
	    ಗಚ್ಛ out;
	  attrs_ok = ಸತ್ಯ;
	  seen_type = ಸತ್ಯ;
	  ಯದಿ (c_dialect_objc ())
	    parser->objc_need_raw_identifier = ಸತ್ಯ;
	  t.kind = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	  t.ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
	  t.ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;
	  t.has_enum_type_specifier = ಅಸತ್ಯ;
	  declspecs_add_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_ENUM:
	  ಯದಿ (!typespec_ok)
	    ಗಚ್ಛ out;
	  attrs_ok = ಸತ್ಯ;
	  seen_type = ಸತ್ಯ;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_STRUCT:
	ಪಕ್ಷ RID_UNION:
	  ಯದಿ (!typespec_ok)
	    ಗಚ್ಛ out;
	  attrs_ok = ಸತ್ಯ;
	  seen_type = ಸತ್ಯ;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_TYPEOF:
	ಪಕ್ಷ RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  ಯದಿ (!typespec_ok || seen_type)
	    ಗಚ್ಛ out;
	  attrs_ok = ಸತ್ಯ;
	  seen_type = ಸತ್ಯ;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_add_type (loc, specs, t);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_BITINT:
	  ಯದಿ (!typespec_ok)
	    ಗಚ್ಛ out;
	  ಅನ್ಯಥಾ
	    {
	      attrs_ok = ಸತ್ಯ;
	      seen_type = ಸತ್ಯ;
	      t.kind = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	      t.ಅಭಿವ್ಯಕ್ತಿ = error_mark_ಗಂಟು;
	      t.ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;
	      t.has_enum_type_specifier = ಅಸತ್ಯ;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      ಯದಿ (parens.require_open (parser))
		{
		  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
		  t.ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (loc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ,
						     ಸತ್ಯ).ಮೌಲ್ಯ;
		  parens.skip_until_found_close (parser);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_ATOMIC:
	  /* C parser handling of Objective-C constructs needs
	     checking for correct lvalue-to-rvalue conversions, and
	     the code in build_modify_expr handling various
	     Objective-C cases, and that in build_unary_op handling
	     Objective-C cases for increment / decrement, also needs
	     updating; uses of TYPE_MAIN_VARIANT in objc_compare_types
	     and objc_types_are_equivalent may also need updates.  */
	  ಯದಿ (c_dialect_objc ())
	    sorry ("%<_Atomic%> in Objective-C");
	  ಯದಿ (flag_isoc99)
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C99 does not support the %<_Atomic%> qualifier");
	  ಅನ್ಯಥಾ
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C90 does not support the %<_Atomic%> qualifier");
	  attrs_ok = ಸತ್ಯ;
	  ವೃಕ್ಷ ಮೌಲ್ಯ;
	  ಮೌಲ್ಯ = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	  c_parser_consume_token (parser);
	  ಯದಿ (typespec_ok && c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      seen_type = ಸತ್ಯ;
	      c_parser_consume_token (parser);
	      ಸಂರಚನಾ c_type_name *type = c_parser_type_name (parser);
	      t.kind = ctsk_typeof;
	      t.spec = error_mark_ಗಂಟು;
	      t.ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
	      t.ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;
	      t.has_enum_type_specifier = ಅಸತ್ಯ;
	      ಯದಿ (type != ರಿಕ್ತ)
		t.spec = groktypename (type, &t.ಅಭಿವ್ಯಕ್ತಿ,
				       &t.ಅಭಿವ್ಯಕ್ತಿ_const_operands);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      ಯದಿ (t.spec != error_mark_ಗಂಟು)
		{
		  ಯದಿ (ವೃಕ್ಷ_CODE (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  ಅನ್ಯಥಾ ಯದಿ (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  ಅನ್ಯಥಾ
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  ಅನ್ಯಥಾ
	    declspecs_add_qual (loc, specs, ಮೌಲ್ಯ);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_CONST:
	ಪಕ್ಷ RID_VOLATILE:
	ಪಕ್ಷ RID_RESTRICT:
	  attrs_ok = ಸತ್ಯ;
	  declspecs_add_qual (loc, specs, c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	  c_parser_consume_token (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_ATTRIBUTE:
	  ಯದಿ (!attrs_ok)
	    ಗಚ್ಛ out;
	  attrs = c_parser_gnu_attributes (parser);
	  declspecs_add_attrs (loc, specs, attrs);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_ALIGNAS:
	  ಯದಿ (!alignspec_ok)
	    ಗಚ್ಛ out;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_add_alignas (loc, specs, align);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_GIMPLE:
	  ಯದಿ (! flag_gimple)
	    error_at (loc, "%<__GIMPLE%> only valid with %<-fgimple%>");
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_gimple;
	  specs->locations[cdw_gimple] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_RTL:
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_rtl;
	  specs->locations[cdw_rtl] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  ಗಚ್ಛ out;
	}
    }
 out:
  ಯದಿ (end_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    specs->postfix_attrs = c_parser_std_attribute_specifier_sequence (parser);
}

/* Complain about a non-CPP_NAME within an enumerator list.  */

ಸ್ಥಿರ ಶೂನ್ಯ
report_bad_enum_name (c_parser *parser)
{
  ಯದಿ (!parser->error)
    {
      c_token *token = c_parser_peek_token (parser);
      ವಿಕಲ್ಪ (token->type)
	{
	ಸ್ವಭಾವ:
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_CLOSE_BRACE:
	  /* Give a nicer error for "enum {}".  */
	  error_at (token->location,
		    "empty enum is invalid");
	  parser->error = ಸತ್ಯ;
	  ಪ್ರತ್ಯಾಗಮ;
	ಪಕ್ಷ CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  ಯದಿ (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_group d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_POINTER (token->ಮೌಲ್ಯ));
	      add_note_about_new_keyword (token->location,
					  token->ಮೌಲ್ಯ);
	      parser->error = ಸತ್ಯ;
	      ಪ್ರತ್ಯಾಗಮ;
	    }
	  ಭಙ್ಗ;
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

ಸ್ಥಿರ ಸಂರಚನಾ c_typespec
c_parser_enum_specifier (c_parser *parser)
{
  ಸಂರಚನಾ c_typespec ret;
  ತಾರ್ಕಿಕ have_std_attrs;
  ತಾರ್ಕಿಕ potential_nesting_p = ಅಸತ್ಯ;
  ವೃಕ್ಷ std_attrs = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ attrs;
  ವೃಕ್ಷ ident = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ fixed_underlying_type = NULL_ವೃಕ್ಷ;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  ಯದಿ (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  ಯದಿ (c_parser_next_token_is (parser, CPP_COLON)
      /* Distinguish an enum-type-specifier from a bit-field
	 declaration of the form "enum e : constant-expression;".  */
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      pedwarn_c11 (enum_loc, OPT_Wpedantic,
		   "ISO C does not support specifying %<enum%> underlying "
		   "types before C23");
      ಯದಿ (ident)
	{
	  /* The tag is in scope during the enum-type-specifier (which
	     may refer to the tag inside typeof).  */
	  ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, ಸತ್ಯ);
	  ಯದಿ (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_ವೃಕ್ಷ == TYPE_ಮೌಲ್ಯಗಳು (ret.spec);
	}
      ಅನ್ಯಥಾ
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_ವೃಕ್ಷ;
	  ret.kind = ctsk_tagdef;
	  ret.ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
	  ret.ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;
	  ret.has_enum_type_specifier = ಸತ್ಯ;
	}
      c_parser_consume_token (parser);
      ಸಂರಚನಾ c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, ಅಸತ್ಯ, ಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ,
			  ಅಸತ್ಯ, ಸತ್ಯ, cla_prefer_id);
      finish_declspecs (specs);
      ಯದಿ (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (specs->type) != INTEGER_TYPE
	       && ವೃಕ್ಷ_CODE (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || ವೃಕ್ಷ_CODE (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (specs->restrict_p)
	error_at (enum_loc, "invalid use of %<restrict%>");
      fixed_underlying_type = TYPE_MAIN_VARIANT (specs->type);
      ಯದಿ (ident)
	{
	  /* The type specified must be consistent with any previously
	     specified underlying type.  If this is a newly declared
	     type, it is now a complete type.  */
	  ಯದಿ (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
	      && ENUM_UNDERLYING_TYPE (ret.spec) == NULL_ವೃಕ್ಷ)
	    {
	      TYPE_MIN_ಮೌಲ್ಯ (ret.spec) =
		TYPE_MIN_ಮೌಲ್ಯ (fixed_underlying_type);
	      TYPE_MAX_ಮೌಲ್ಯ (ret.spec) =
		TYPE_MAX_ಮೌಲ್ಯ (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      SET_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_SIZE (ret.spec) = NULL_ವೃಕ್ಷ;
	      TYPE_PRECISION (ret.spec) =
		TYPE_PRECISION (fixed_underlying_type);
	      ENUM_UNDERLYING_TYPE (ret.spec) = fixed_underlying_type;
	      layout_type (ret.spec);
	    }
	  ಅನ್ಯಥಾ ಯದಿ (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
		   && !comptypes (fixed_underlying_type,
				  ENUM_UNDERLYING_TYPE (ret.spec)))
	    {
	      error_at (enum_loc, "%<enum%> underlying type incompatible with "
			"previous declaration");
	      fixed_underlying_type = ENUM_UNDERLYING_TYPE (ret.spec);
	    }
	}
    }
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      ಸಂರಚನಾ c_enum_contents the_enum;
      ವೃಕ್ಷ type;
      ವೃಕ್ಷ postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      ವೃಕ್ಷ ಮೌಲ್ಯಗಳು;
      timevar_ತಳ್ಳು (TV_PARSE_ENUM);
      type = start_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      ಮೌಲ್ಯಗಳು = NULL_ವೃಕ್ಷ;
      c_parser_consume_token (parser);
      ಯಾವತ್ (ಸತ್ಯ)
	{
	  ವೃಕ್ಷ enum_id;
	  ವೃಕ್ಷ enum_ಮೌಲ್ಯ;
	  ವೃಕ್ಷ enum_decl;
	  ತಾರ್ಕಿಕ seen_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, ಮೌಲ್ಯ_loc;
	  ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ರಿಕ್ತ);
	      ಮೌಲ್ಯಗಳು = error_mark_ಗಂಟು;
	      ಭಙ್ಗ;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->ಮೌಲ್ಯ;
	  /* Set the location in case we create a decl now.  */
	  c_parser_set_source_position_from_token (token);
	  decl_loc = ಮೌಲ್ಯ_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  ವೃಕ್ಷ std_attrs = NULL_ವೃಕ್ಷ;
	  ಯದಿ (c_parser_nth_token_starts_std_attributes (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  ವೃಕ್ಷ enum_attrs = chainon (std_attrs,
				     c_parser_gnu_attributes (parser));
	  ಯದಿ (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      ಮೌಲ್ಯ_loc = c_parser_peek_token (parser)->location;
	      enum_ಮೌಲ್ಯ = convert_lvalue_to_rvalue (ಮೌಲ್ಯ_loc,
						     (c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas
						      (parser, ರಿಕ್ತ)),
						     ಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;
	    }
	  ಅನ್ಯಥಾ
	    enum_ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	  enum_decl = build_enumerator (decl_loc, ಮೌಲ್ಯ_loc,
					&the_enum, enum_id, enum_ಮೌಲ್ಯ);
	  ಯದಿ (enum_attrs)
	    decl_attributes (&ವೃಕ್ಷ_PURPOSE (enum_decl), enum_attrs, 0);
	  ವೃಕ್ಷ_CHAIN (enum_decl) = ಮೌಲ್ಯಗಳು;
	  ಮೌಲ್ಯಗಳು = enum_decl;
	  seen_comma = ಅಸತ್ಯ;
	  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      seen_comma = ಸತ್ಯ;
	      c_parser_consume_token (parser);
	    }
	  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      ಯದಿ (seen_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (!seen_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ರಿಕ್ತ);
	      ಮೌಲ್ಯಗಳು = error_mark_ಗಂಟು;
	      ಭಙ್ಗ;
	    }
	}
      postfix_attrs = c_parser_gnu_attributes (parser);
      ret.spec = finish_enum (type, nreverse (ಮೌಲ್ಯಗಳು),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.kind = ctsk_tagdef;
      ret.ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
      ret.ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_ವೃಕ್ಷ;
      timevar_ತೆಗೆ (TV_PARSE_ENUM);
      ಪ್ರತ್ಯಾಗಮ ret;
    }
  ಅನ್ಯಥಾ ಯದಿ (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_ಗಂಟು;
      ret.kind = ctsk_tagref;
      ret.ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
      ret.ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;
      ret.has_enum_type_specifier = ಅಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  ಯದಿ (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  ಯದಿ (fixed_underlying_type == NULL_ವೃಕ್ಷ)
    {
      ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
			     std_attrs, ಅಸತ್ಯ);
      /* In ISO C, enumerated types without a fixed underlying type
	 can be referred to only if already defined.  */
      ಯದಿ (pedantic && !COMPLETE_TYPE_P (ret.spec))
	{
	  gcc_assert (ident);
	  pedwarn (enum_loc, OPT_Wpedantic,
		   "ISO C forbids forward references to %<enum%> types");
	}
    }
  ಪ್ರತ್ಯಾಗಮ ret;
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

ಸ್ಥಿರ ಸಂರಚನಾ c_typespec
c_parser_struct_or_union_specifier (c_parser *parser)
{
  ಸಂರಚನಾ c_typespec ret;
  ತಾರ್ಕಿಕ have_std_attrs;
  ವೃಕ್ಷ std_attrs = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ attrs;
  ವೃಕ್ಷ ident = NULL_ವೃಕ್ಷ;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  ಗಣನಾ ವೃಕ್ಷ_code code;
  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->keyword)
    {
    ಪಕ್ಷ RID_STRUCT:
      code = RECORD_TYPE;
      ಭಙ್ಗ;
    ಪಕ್ಷ RID_UNION:
      code = UNION_TYPE;
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  ಯದಿ (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      ವರ್ಗ c_struct_parse_info *struct_info;
      ವೃಕ್ಷ type = start_struct (struct_loc, code, ident, &struct_info);
      ವೃಕ್ಷ postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      ವೃಕ್ಷ contents;
      ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = ರಿಕ್ತ;
      timevar_ತಳ್ಳು (TV_PARSE_STRUCT);
      contents = NULL_ವೃಕ್ಷ;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      ಯದಿ (c_parser_next_token_is_keyword (parser, RID_AT_DEFS))
	{
	  ವೃಕ್ಷ name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  ಯದಿ (!parens.require_open (parser))
	    ಗಚ್ಛ end_at_defs;
	  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	      c_parser_consume_token (parser);
	    }
	  ಅನ್ಯಥಾ
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
	      ಗಚ್ಛ end_at_defs;
	    }
	  parens.skip_until_found_close (parser);
	  contents = nreverse (objc_get_class_ivars (name));
	}
    end_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      ಯಾವತ್ (ಸತ್ಯ)
	{
	  ವೃಕ್ಷ decls;
	  /* Parse any stray semicolon.  */
	  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      location_t semicolon_loc
		= c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (semicolon_loc);
	      richloc.add_fixit_remove ();
	      pedwarn (&richloc, OPT_Wpedantic,
		       "extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      ಅನುವರ್ತ;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      ಭಙ್ಗ;
	    }
	  /* Accept #pragmas at struct scope.  */
	  ಯದಿ (c_parser_next_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, ರಿಕ್ತ, NULL_ವೃಕ್ಷ);
	      ಅನುವರ್ತ;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &ಅಭಿವ್ಯಕ್ತಿ);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  ಅನ್ಯಥಾ
	    {
	      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      ಅನ್ಯಥಾ ಯದಿ (parser->error
		       || !c_parser_next_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ರಿಕ್ತ);
		  ಭಙ್ಗ;
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
				struct_info, &ಅಭಿವ್ಯಕ್ತಿ);
      ret.kind = ctsk_tagdef;
      ret.ಅಭಿವ್ಯಕ್ತಿ = ಅಭಿವ್ಯಕ್ತಿ;
      ret.ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;
      ret.has_enum_type_specifier = ಅಸತ್ಯ;
      timevar_ತೆಗೆ (TV_PARSE_STRUCT);
      ಪ್ರತ್ಯಾಗಮ ret;
    }
  ಅನ್ಯಥಾ ಯದಿ (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_ಗಂಟು;
      ret.kind = ctsk_tagref;
      ret.ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
      ret.ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;
      ret.has_enum_type_specifier = ಅಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  ಯದಿ (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_tag (ident_loc, code, ident, have_std_attrs, std_attrs,
			 ಅಸತ್ಯ);
  ಪ್ರತ್ಯಾಗಮ ret;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_struct_declaration (c_parser *parser, ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ)
{
  ಸಂರಚನಾ c_declspecs *specs;
  ವೃಕ್ಷ prefix_attrs;
  ವೃಕ್ಷ all_prefix_attrs;
  ವೃಕ್ಷ decls;
  location_t decl_loc;
  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      ಪೂರ್ಣಾಙ್ಕ ext;
      ವೃಕ್ಷ decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, ಅಭಿವ್ಯಕ್ತಿ);
      restore_extension_diagnostics (ext);
      ಪ್ರತ್ಯಾಗಮ decl;
    }
  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, ಅಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ,
		      ಸತ್ಯ, ಅಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, cla_nonabstract_decl);
  ಯದಿ (parser->error)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  ಯದಿ (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }
  finish_declspecs (specs);
  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      ವೃಕ್ಷ ret;
      ಯದಿ (specs->typespec_kind == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_tag_warned (specs, pedantic);
	  ret = NULL_ವೃಕ್ಷ;
	}
      ಅನ್ಯಥಾ
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  ವೃಕ್ಷ attrs = ರಿಕ್ತ;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_ವೃಕ್ಷ), specs,
			   NULL_ವೃಕ್ಷ, &attrs, ಅಭಿವ್ಯಕ್ತಿ);
	  ಯದಿ (ret)
	    decl_attributes (&ret, attrs, 0);
	}
      ಪ್ರತ್ಯಾಗಮ ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  ಯದಿ (specs->typespec_kind == ctsk_tagdef
      && ವೃಕ್ಷ_CODE (specs->type) != ENUMERAL_TYPE
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = ಅಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_ವೃಕ್ಷ;
  decls = NULL_ವೃಕ್ಷ;
  ಯಾವತ್ (ಸತ್ಯ)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      ಸಂರಚನಾ c_declarator *declarator;
      ತಾರ್ಕಿಕ dummy = ಅಸತ್ಯ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_ವೃಕ್ಷ);
      ಅನ್ಯಥಾ
	declarator = c_parser_declarator (parser,
					  specs->typespec_kind != ctsk_none,
					  C_DTR_NORMAL, &dummy);
      ಯದಿ (declarator == ರಿಕ್ತ)
	{
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  ಭಙ್ಗ;
	}
      ಯದಿ (c_parser_next_token_is (parser, CPP_COLON)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  ವೃಕ್ಷ postfix_attrs = NULL_ವೃಕ್ಷ;
	  ವೃಕ್ಷ width = NULL_ವೃಕ್ಷ;
	  ವೃಕ್ಷ d;
	  ಯದಿ (c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      width = convert_lvalue_to_rvalue (loc,
						(c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas
						 (parser, ರಿಕ್ತ)),
						ಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;
	    }
	  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_attributes (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, width, &all_prefix_attrs, ಅಭಿವ್ಯಕ್ತಿ);
	  decl_attributes (&d, chainon (postfix_attrs,
					all_prefix_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					prefix_attrs);
	  ಅನ್ಯಥಾ
	    all_prefix_attrs = prefix_attrs;
	  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON)
		   || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      /* Semicolon consumed in caller.  */
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ
	    {
	      c_parser_error (parser, "expected %<,%>, %<;%> or %<}%>");
	      ಭಙ್ಗ;
	    }
	}
      ಅನ್ಯಥಾ
	{
	  c_parser_error (parser,
			  "expected %<:%>, %<,%>, %<;%>, %<}%> or "
			  "%<__attribute__%>");
	  ಭಙ್ಗ;
	}
    }
  ಪ್ರತ್ಯಾಗಮ decls;
}

/* Parse a typeof specifier (a GNU extension adopted in C23).

   typeof-specifier:
     typeof ( expression )
     typeof ( type-name )
     typeof_unqual ( expression )
     typeof_unqual ( type-name )
*/

ಸ್ಥಿರ ಸಂರಚನಾ c_typespec
c_parser_typeof_specifier (c_parser *parser)
{
  ತಾರ್ಕಿಕ is_unqual;
  ತಾರ್ಕಿಕ is_std;
  ಸಂರಚನಾ c_typespec ret;
  ret.kind = ctsk_typeof;
  ret.spec = error_mark_ಗಂಟು;
  ret.ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ret.ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;
  ret.has_enum_type_specifier = ಅಸತ್ಯ;
  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = ಅಸತ್ಯ;
      ವೃಕ್ಷ spelling = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      is_std = (flag_isoc23
		&& strcmp (IDENTIFIER_POINTER (spelling), "typeof") == 0);
    }
  ಅನ್ಯಥಾ
    {
      gcc_assert (c_parser_next_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = ಸತ್ಯ;
      ವೃಕ್ಷ spelling = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      is_std = strcmp (IDENTIFIER_POINTER (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_typeof++;
  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      ಪ್ರತ್ಯಾಗಮ ret;
    }
  ಯದಿ (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      ಸಂರಚನಾ c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      ಯದಿ (type != ರಿಕ್ತ)
	{
	  ret.spec = groktypename (type, &ret.ಅಭಿವ್ಯಕ್ತಿ, &ret.ಅಭಿವ್ಯಕ್ತಿ_const_operands);
	  ತೆಗೆ_maybe_used (c_type_variably_modified_p (ret.spec));
	}
    }
  ಅನ್ಯಥಾ
    {
      ತಾರ್ಕಿಕ was_vm;
      location_t here = c_parser_peek_token (parser)->location;
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_expression (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 1)))
	error_at (here, "%<typeof%> applied to a bit-field");
      mark_exp_read (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
      ret.spec = ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      ಯದಿ (was_vm)
	ret.ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ, &ret.ಅಭಿವ್ಯಕ್ತಿ_const_operands);
      ತೆಗೆ_maybe_used (was_vm);
    }
  parens.skip_until_found_close (parser);
  ಯದಿ (ret.spec != error_mark_ಗಂಟು)
    {
      ಯದಿ (is_unqual)
	{
	  ತಾರ್ಕಿಕ is_array = ವೃಕ್ಷ_CODE (ret.spec) == ARRAY_TYPE;
	  ಪೂರ್ಣಾಙ್ಕ quals = TYPE_QUALS (strip_array_types (ret.spec));
	  ಯದಿ ((is_array ? quals & ~TYPE_QUAL_ATOMIC : quals)
	      != TYPE_UNQUALIFIED)
	    {
	      ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	      ಯದಿ (quals & TYPE_QUAL_ATOMIC && is_array)
		ret.spec = c_build_qualified_type (ret.spec,
						   TYPE_QUAL_ATOMIC);
	    }
	}
      ಯದಿ (is_std)
	{
	  /* In ISO C terms, _Noreturn is not part of the type of
	     expressions such as &abort, but in GCC it is represented
	     internally as a type qualifier.  */
	  ಯದಿ (ವೃಕ್ಷ_CODE (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  ಅನ್ಯಥಾ ಯದಿ (FUNCTION_POINTER_TYPE_P (ret.spec)
		   && TYPE_QUALS (ವೃಕ್ಷ_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_pointer_type (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ret.spec)));
	}
    }
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Parse an alignment-specifier.

   C11 6.7.5:

   alignment-specifier:
     _Alignas ( type-name )
     _Alignas ( constant-expression )
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_alignas_specifier (c_parser * parser)
{
  ವೃಕ್ಷ ret = error_mark_ಗಂಟು;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNAS));
  ವೃಕ್ಷ spelling = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
  c_parser_consume_token (parser);
  ಯದಿ (flag_isoc99)
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  ಅನ್ಯಥಾ
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ ret;
  ಯದಿ (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      ಸಂರಚನಾ c_type_name *type = c_parser_type_name (parser);
      ಯದಿ (type != ರಿಕ್ತ)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, ರಿಕ್ತ, ರಿಕ್ತ),
					ಅಸತ್ಯ, ಸತ್ಯ, 1);
    }
  ಅನ್ಯಥಾ
    ret = convert_lvalue_to_rvalue (loc,
				    c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ),
				    ಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;
  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ ret;
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

ಸಂರಚನಾ c_declarator *
c_parser_declarator (c_parser *parser, ತಾರ್ಕಿಕ type_seen_p, c_dtr_syn kind,
		     ತಾರ್ಕಿಕ *seen_id)
{
  /* Parse any initial pointer part.  */
  ಯದಿ (c_parser_next_token_is (parser, CPP_MULT))
    {
      ಸಂರಚನಾ c_declspecs *quals_attrs = build_null_declspecs ();
      ಸಂರಚನಾ c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, ಅಸತ್ಯ, ಅಸತ್ಯ, ಸತ್ಯ,
			  ಅಸತ್ಯ, ಅಸತ್ಯ, ಸತ್ಯ, ಅಸತ್ಯ, cla_prefer_id);
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      ಯದಿ (inner == ರಿಕ್ತ)
	ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
      ಅನ್ಯಥಾ
	ಪ್ರತ್ಯಾಗಮ make_pointer_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  ಪ್ರತ್ಯಾಗಮ c_parser_direct_declarator (parser, type_seen_p, kind, seen_id);
}

/* Parse a direct declarator or direct abstract declarator; arguments
   as c_parser_declarator.  */

ಸ್ಥಿರ ಸಂರಚನಾ c_declarator *
c_parser_direct_declarator (c_parser *parser, ತಾರ್ಕಿಕ type_seen_p, c_dtr_syn kind,
			    ತಾರ್ಕಿಕ *seen_id)
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

  ಯದಿ (kind != C_DTR_ABSTRACT
      && c_parser_next_token_is (parser, CPP_NAME)
      && ((type_seen_p
	   && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_kind == C_ID_ID))
    {
      ಸಂರಚನಾ c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      *seen_id = ಸತ್ಯ;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_nth_token_starts_std_attributes (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      ಪ್ರತ್ಯಾಗಮ c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  ಯದಿ (kind != C_DTR_NORMAL
      && c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      ಸಂರಚನಾ c_declarator *inner = build_id_declarator (NULL_ವೃಕ್ಷ);
      inner->id_loc = c_parser_peek_token (parser)->location;
      ಪ್ರತ್ಯಾಗಮ c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      ವೃಕ್ಷ attrs;
      ಸಂರಚನಾ c_declarator *inner;
      c_parser_consume_token (parser);
      ತಾರ್ಕಿಕ have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      ಯದಿ (kind != C_DTR_NORMAL
	  && (c_parser_next_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_attributes (parser, 1)
		      || c_parser_next_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  ಸಂರಚನಾ c_arg_info *args
	    = c_parser_parms_declarator (parser, kind == C_DTR_NORMAL,
					 attrs, have_gnu_attrs);
	  ಯದಿ (args == ರಿಕ್ತ)
	    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
	  ಅನ್ಯಥಾ
	    {
	      inner = build_id_declarator (NULL_ವೃಕ್ಷ);
	      ಯದಿ (!(args->types
		    && args->types != error_mark_ಗಂಟು
		    && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_ಮೌಲ್ಯ (args->types)) == IDENTIFIER_ಗಂಟು)
		  && c_parser_nth_token_starts_std_attributes (parser, 1))
		{
		  ವೃಕ್ಷ std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  ಯದಿ (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (args, inner);
	      ಪ್ರತ್ಯಾಗಮ c_parser_direct_declarator_inner (parser, *seen_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      ಯದಿ (inner != ರಿಕ್ತ && attrs != ರಿಕ್ತ)
	inner = build_attrs_declarator (attrs, inner);
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  ಯದಿ (inner == ರಿಕ್ತ)
	    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
	  ಅನ್ಯಥಾ
	    ಪ್ರತ್ಯಾಗಮ c_parser_direct_declarator_inner (parser, *seen_id, inner);
	}
      ಅನ್ಯಥಾ
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
	}
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (kind == C_DTR_NORMAL)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
	}
      ಅನ್ಯಥಾ
	ಪ್ರತ್ಯಾಗಮ build_id_declarator (NULL_ವೃಕ್ಷ);
    }
}

/* Parse part of a direct declarator or direct abstract declarator,
   given that some (in INNER) has already been parsed; ID_PRESENT is
   true if an identifier is present, false for an abstract
   declarator.  */

ಸ್ಥಿರ ಸಂರಚನಾ c_declarator *
c_parser_direct_declarator_inner (c_parser *parser, ತಾರ್ಕಿಕ id_present,
				  ಸಂರಚನಾ c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      ಸಂರಚನಾ c_declarator *declarator;
      ಸಂರಚನಾ c_declspecs *quals_attrs = build_null_declspecs ();
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ dimen;
      dimen.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
      dimen.original_code = ERROR_MARK;
      dimen.original_type = NULL_ವೃಕ್ಷ;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, ಅಸತ್ಯ, ಅಸತ್ಯ, ಸತ್ಯ,
			  ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ, cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      ಯದಿ (c_parser_next_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  ಯದಿ (!quals_attrs->declspecs_seen_p)
	    c_parser_declspecs (parser, quals_attrs, ಅಸತ್ಯ, ಅಸತ್ಯ, ಸತ್ಯ,
				ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ, cla_prefer_id);
	}
      ಯದಿ (!quals_attrs->declspecs_seen_p)
	quals_attrs = ರಿಕ್ತ;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      ಧ್ರುವ ತಾರ್ಕಿಕ static_seen = (static_loc != UNKNOWN_LOCATION);
      ತಾರ್ಕಿಕ star_seen = ಅಸತ್ಯ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_SQUARE)
	{
	  star_seen = ಸತ್ಯ;
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ ಯದಿ (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	dimen = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);

      ಯದಿ (static_seen)
	{
	  ಯದಿ (star_seen)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      star_seen = ಅಸತ್ಯ;
	      dimen.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (!dimen.ಮೌಲ್ಯ)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	c_parser_consume_token (parser);
      ಅನ್ಯಥಾ
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
	}
      ಯದಿ (dimen.ಮೌಲ್ಯ)
	dimen = convert_lvalue_to_rvalue (brace_loc, dimen, ಸತ್ಯ, ಸತ್ಯ);
      declarator = build_array_declarator (brace_loc, dimen.ಮೌಲ್ಯ, quals_attrs,
					   static_seen, star_seen);
      ಯದಿ (declarator == ರಿಕ್ತ)
	ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
      ಯದಿ (c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  ವೃಕ್ಷ std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  ಯದಿ (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = set_array_declarator_inner (declarator, inner);
      ಪ್ರತ್ಯಾಗಮ c_parser_direct_declarator_inner (parser, id_present, inner);
    }
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      ವೃಕ್ಷ attrs;
      ಸಂರಚನಾ c_arg_info *args;
      c_parser_consume_token (parser);
      ತಾರ್ಕಿಕ have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      args = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      ಯದಿ (args == ರಿಕ್ತ)
	ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
      ಅನ್ಯಥಾ
	{
	  ಯದಿ (!(args->types
		&& args->types != error_mark_ಗಂಟು
		&& ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_ಮೌಲ್ಯ (args->types)) == IDENTIFIER_ಗಂಟು)
	      && c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      ವೃಕ್ಷ std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      ಯದಿ (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (args, inner);
	  ಪ್ರತ್ಯಾಗಮ c_parser_direct_declarator_inner (parser, id_present, inner);
	}
    }
  ಪ್ರತ್ಯಾಗಮ inner;
}

/* Parse a parameter list or identifier list, including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list.  ID_LIST_OK is true if an identifier list
   is acceptable; such a list must not have attributes at the start.
   HAVE_GNU_ATTRS says whether any gnu-attributes (including empty
   attributes) were present (in which case standard attributes cannot
   occur).  */

ಸ್ಥಿರ ಸಂರಚನಾ c_arg_info *
c_parser_parms_declarator (c_parser *parser, ತಾರ್ಕಿಕ id_list_ok, ವೃಕ್ಷ attrs,
			   ತಾರ್ಕಿಕ have_gnu_attrs)
{
  ತಳ್ಳು_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  ಯದಿ (id_list_ok
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
      ವೃಕ್ಷ list = NULL_ವೃಕ್ಷ, *nextp = &list;
      ಯಾವತ್ (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  *nextp = build_ವೃಕ್ಷ_list (NULL_ವೃಕ್ಷ,
				    c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	  nextp = & ವೃಕ್ಷ_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  ಯದಿ (c_parser_next_token_is_not (parser, CPP_COMMA))
	    ಭಙ್ಗ;
	  c_parser_consume_token (parser);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      ಭಙ್ಗ;
	    }
	}
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ಸಂರಚನಾ c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  ತೆಗೆ_scope ();
	  ಪ್ರತ್ಯಾಗಮ ret;
	}
      ಅನ್ಯಥಾ
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ತೆಗೆ_scope ();
	  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
	}
    }
  ಅನ್ಯಥಾ
    {
      ಸಂರಚನಾ c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, ರಿಕ್ತ, have_gnu_attrs);
      ತೆಗೆ_scope ();
      ಪ್ರತ್ಯಾಗಮ ret;
    }
}

/* Parse a parameter list (possibly empty), including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list; if HAVE_GNU_ATTRS, there were some such
   attributes (possibly empty, in which case ATTRS is NULL_TREE),
   which means standard attributes cannot start the list.  EXPR is
   NULL or an expression that needs to be evaluated for the side
   effects of array size expressions in the parameters.  */

ಸ್ಥಿರ ಸಂರಚನಾ c_arg_info *
c_parser_parms_list_declarator (c_parser *parser, ವೃಕ್ಷ attrs, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ,
				ತಾರ್ಕಿಕ have_gnu_attrs)
{
  ತಾರ್ಕಿಕ bad_parm = ಅಸತ್ಯ;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      ಸಂರಚನಾ c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      ಪ್ರತ್ಯಾಗಮ ret;
    }
  ಯದಿ (c_parser_next_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      ಸಂರಚನಾ c_arg_info *ret = build_arg_info ();

      ret->types = NULL_ವೃಕ್ಷ;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_args_stdarg_p = ಸತ್ಯ;
	  c_parser_consume_token (parser);
	  ಪ್ರತ್ಯಾಗಮ ret;
	}
      ಅನ್ಯಥಾ
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  ಯಾವತ್ (ಸತ್ಯ)
    {
      /* Parse a parameter.  */
      ಸಂರಚನಾ c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_ವೃಕ್ಷ;
      have_gnu_attrs = ಅಸತ್ಯ;
      ಯದಿ (parm == ರಿಕ್ತ)
	bad_parm = ಸತ್ಯ;
      ಅನ್ಯಥಾ
	ತಳ್ಳು_parm_decl (parm, &ಅಭಿವ್ಯಕ್ತಿ);
      ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  ವೃಕ್ಷ new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  ತಾರ್ಕಿಕ new_have_gnu_attrs
	    = c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_attributes (parser);
	  ಪ್ರತ್ಯಾಗಮ c_parser_parms_list_declarator (parser, new_attrs, ಅಭಿವ್ಯಕ್ತಿ,
						 new_have_gnu_attrs);
	}
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  ಯದಿ (bad_parm)
	    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
	  ಅನ್ಯಥಾ
	    ಪ್ರತ್ಯಾಗಮ get_parm_info (ಅಸತ್ಯ, ಅಭಿವ್ಯಕ್ತಿ);
	}
      ಯದಿ (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, ಅಸತ್ಯ))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
	  ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
	}
      ಯದಿ (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      ಯದಿ (bad_parm)
		ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
	      ಅನ್ಯಥಾ
		ಪ್ರತ್ಯಾಗಮ get_parm_info (ಸತ್ಯ, ಅಭಿವ್ಯಕ್ತಿ);
	    }
	  ಅನ್ಯಥಾ
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
	    }
	}
    }
}

/* Parse a parameter declaration.  ATTRS are the gnu-attributes at the
   start of the declaration if it is the first parameter;
   HAVE_GNU_ATTRS is true if there were any gnu-attributes there (even
   empty) there.  */

ಸ್ಥಿರ ಸಂರಚನಾ c_parm *
c_parser_parameter_declaration (c_parser *parser, ವೃಕ್ಷ attrs,
				ತಾರ್ಕಿಕ have_gnu_attrs)
{
  ಸಂರಚನಾ c_declspecs *specs;
  ಸಂರಚನಾ c_declarator *declarator;
  ವೃಕ್ಷ prefix_attrs;
  ವೃಕ್ಷ postfix_attrs = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ dummy = ಅಸತ್ಯ;

  /* Accept #pragmas between parameter declarations.  */
  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, ರಿಕ್ತ, NULL_ವೃಕ್ಷ);

  ಯದಿ (!c_parser_next_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      ಯದಿ (parser->error)
	ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
      c_parser_set_source_position_from_token (token);
      ಯದಿ (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (token->ಮೌಲ್ಯ,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  ಯದಿ (ಧ್ರುವ ವರ್ಣ *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->ಮೌಲ್ಯ, suggestion);
	    }
	  ಅನ್ಯಥಾ
	    error_at (token->location, "unknown type name %qE", token->ಮೌಲ್ಯ);
	  parser->error = ಸತ್ಯ;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      ಅನ್ಯಥಾ
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_to_end_of_parameter (parser);
      ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  ಯದಿ (attrs)
    {
      declspecs_add_attrs (ಒಳಹರಿವು_location, specs, attrs);
      attrs = NULL_ವೃಕ್ಷ;
    }
  c_parser_declspecs (parser, specs, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಅಸತ್ಯ,
		      !have_gnu_attrs, ಸತ್ಯ, cla_nonabstract_decl);
  finish_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  ಯದಿ (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_ತುದಿ_anonymous_type (specs->type);

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  specs->attrs = NULL_ವೃಕ್ಷ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_PARM, &dummy);
  ಯದಿ (declarator == ರಿಕ್ತ)
    {
      c_parser_skip_until_found (parser, CPP_COMMA, ರಿಕ್ತ);
      ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
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
  ಯಾವತ್ (id_declarator && id_declarator->kind != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : start_loc);
  location_t param_loc = make_location (caret_loc, start_loc, end_loc);

  ಪ್ರತ್ಯಾಗಮ build_c_parm (specs, chainon (postfix_attrs, prefix_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_asm_string_literal (c_parser *parser)
{
  ವೃಕ್ಷ str;
  ಪೂರ್ಣಾಙ್ಕ save_flag = warn_overlength_strings;
  warn_overlength_strings = 0;
  str = c_parser_string_literal (parser, ಅಸತ್ಯ, ಅಸತ್ಯ).ಮೌಲ್ಯ;
  warn_overlength_strings = save_flag;
  ಪ್ರತ್ಯಾಗಮ str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_simple_asm_ಅಭಿವ್ಯಕ್ತಿ (c_parser *parser)
{
  ವೃಕ್ಷ str;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  str = c_parser_asm_string_literal (parser);
  ಯದಿ (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }
  ಪ್ರತ್ಯಾಗಮ str;
}

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_gnu_attribute_any_word (c_parser *parser)
{
  ವೃಕ್ಷ attr_name = NULL_ವೃಕ್ಷ;

  ಯದಿ (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      /* ??? See comment above about what keywords are accepted here.  */
      ತಾರ್ಕಿಕ ok;
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->keyword)
	{
	ಪಕ್ಷ RID_STATIC:
	ಪಕ್ಷ RID_UNSIGNED:
	ಪಕ್ಷ RID_LONG:
	ಪಕ್ಷ RID_CONST:
	ಪಕ್ಷ RID_EXTERN:
	ಪಕ್ಷ RID_REGISTER:
	ಪಕ್ಷ RID_TYPEDEF:
	ಪಕ್ಷ RID_SHORT:
	ಪಕ್ಷ RID_INLINE:
	ಪಕ್ಷ RID_NORETURN:
	ಪಕ್ಷ RID_VOLATILE:
	ಪಕ್ಷ RID_SIGNED:
	ಪಕ್ಷ RID_AUTO:
	ಪಕ್ಷ RID_RESTRICT:
	ಪಕ್ಷ RID_COMPLEX:
	ಪಕ್ಷ RID_THREAD:
	ಪಕ್ಷ RID_INT:
	ಪಕ್ಷ RID_CHAR:
	ಪಕ್ಷ RID_FLOAT:
	ಪಕ್ಷ RID_DOUBLE:
	ಪಕ್ಷ RID_VOID:
	ಪಕ್ಷ RID_DFLOAT32:
	ಪಕ್ಷ RID_DFLOAT64:
	ಪಕ್ಷ RID_DFLOAT128:
	ಪಕ್ಷ RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	ಪಕ್ಷ RID_BOOL:
	ಪಕ್ಷ RID_BITINT:
	ಪಕ್ಷ RID_FRACT:
	ಪಕ್ಷ RID_ACCUM:
	ಪಕ್ಷ RID_SAT:
	ಪಕ್ಷ RID_TRANSACTION_ATOMIC:
	ಪಕ್ಷ RID_TRANSACTION_CANCEL:
	ಪಕ್ಷ RID_ATOMIC:
	ಪಕ್ಷ RID_AUTO_TYPE:
	ಪಕ್ಷ RID_CONSTEXPR:
	ಪಕ್ಷ RID_INT_N_0:
	ಪಕ್ಷ RID_INT_N_1:
	ಪಕ್ಷ RID_INT_N_2:
	ಪಕ್ಷ RID_INT_N_3:
	  ok = ಸತ್ಯ;
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  ok = ಅಸತ್ಯ;
	  ಭಙ್ಗ;
	}
      ಯದಿ (!ok)
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(ಪೂರ್ಣಾಙ್ಕ) c_parser_peek_token (parser)->keyword];
    }
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->ಮೌಲ್ಯ;

  ಪ್ರತ್ಯಾಗಮ attr_name;
}

/* Parse attribute arguments.  This is a common form of syntax
   covering all currently valid GNU and standard attributes.

   gnu-attribute-arguments:
     identifier
     identifier , nonempty-expr-list
     expr-list

   where the "identifier" must not be declared as a type.  ??? Why not
   allow identifiers declared as types to start the arguments?  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_attribute_arguments (c_parser *parser, ತಾರ್ಕಿಕ takes_identifier,
			      ತಾರ್ಕಿಕ require_string, ತಾರ್ಕಿಕ assume_attr,
			      ತಾರ್ಕಿಕ allow_empty_args)
{
  vec<ವೃಕ್ಷ, va_gc> *ಅಭಿವ್ಯಕ್ತಿ_list;
  ವೃಕ್ಷ attr_args;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
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
      ವೃಕ್ಷ arg1 = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	attr_args = build_ವೃಕ್ಷ_list (NULL_ವೃಕ್ಷ, arg1);
      ಅನ್ಯಥಾ
	{
	  ವೃಕ್ಷ ವೃಕ್ಷ_list;
	  c_parser_consume_token (parser);
	  ಅಭಿವ್ಯಕ್ತಿ_list = c_parser_ಅಭಿವ್ಯಕ್ತಿ_list (parser, ಅಸತ್ಯ, ಸತ್ಯ,
					  ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ);
	  ವೃಕ್ಷ_list = build_ವೃಕ್ಷ_list_vec (ಅಭಿವ್ಯಕ್ತಿ_list);
	  attr_args = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, arg1, ವೃಕ್ಷ_list);
	  release_ವೃಕ್ಷ_vector (ಅಭಿವ್ಯಕ್ತಿ_list);
	}
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ಯದಿ (!allow_empty_args)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_args = NULL_ವೃಕ್ಷ;
	}
      ಅನ್ಯಥಾ ಯದಿ (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  ವೃಕ್ಷ string = c_parser_string_literal (parser, ಅಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;
	  attr_args = build_ವೃಕ್ಷ_list (NULL_ವೃಕ್ಷ, string);
	}
      ಅನ್ಯಥಾ ಯದಿ (assume_attr)
	{
	  ವೃಕ್ಷ cond
	    = c_parser_conditional_expression (parser, ರಿಕ್ತ, NULL_ವೃಕ್ಷ).ಮೌಲ್ಯ;
	  ಯದಿ (!c_parser_next_token_is (parser, CPP_COMMA))
	    attr_args = build_ವೃಕ್ಷ_list (NULL_ವೃಕ್ಷ, cond);
	  ಅನ್ಯಥಾ
	    {
	      ವೃಕ್ಷ ವೃಕ್ಷ_list;
	      c_parser_consume_token (parser);
	      ಅಭಿವ್ಯಕ್ತಿ_list = c_parser_ಅಭಿವ್ಯಕ್ತಿ_list (parser, ಅಸತ್ಯ, ಸತ್ಯ,
					      ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ);
	      ವೃಕ್ಷ_list = build_ವೃಕ್ಷ_list_vec (ಅಭಿವ್ಯಕ್ತಿ_list);
	      attr_args = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, cond, ವೃಕ್ಷ_list);
	      release_ವೃಕ್ಷ_vector (ಅಭಿವ್ಯಕ್ತಿ_list);
	    }
	}
      ಅನ್ಯಥಾ
	{
	  ಅಭಿವ್ಯಕ್ತಿ_list = c_parser_ಅಭಿವ್ಯಕ್ತಿ_list (parser, ಅಸತ್ಯ, ಸತ್ಯ,
					  ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ);
	  attr_args = build_ವೃಕ್ಷ_list_vec (ಅಭಿವ್ಯಕ್ತಿ_list);
	  release_ವೃಕ್ಷ_vector (ಅಭಿವ್ಯಕ್ತಿ_list);
	}
    }
  ಪ್ರತ್ಯಾಗಮ attr_args;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_gnu_attribute (c_parser *parser, ವೃಕ್ಷ attrs,
			ತಾರ್ಕಿಕ expect_comma = ಅಸತ್ಯ, ತಾರ್ಕಿಕ empty_ok = ಸತ್ಯ)
{
  ತಾರ್ಕಿಕ comma_first = c_parser_next_token_is (parser, CPP_COMMA);
  ಯದಿ (!comma_first
      && !c_parser_next_token_is (parser, CPP_NAME)
      && !c_parser_next_token_is (parser, CPP_KEYWORD))
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ಯದಿ (!empty_ok)
	ಪ್ರತ್ಯಾಗಮ attrs;
    }

  ವೃಕ್ಷ attr_name = c_parser_gnu_attribute_any_word (parser);
  ಯದಿ (attr_name == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  ವೃಕ್ಷ attr;
  ಯದಿ (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      ಯದಿ (expect_comma && !comma_first)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      attr = build_ವೃಕ್ಷ_list (attr_name, NULL_ವೃಕ್ಷ);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      ಪ್ರತ್ಯಾಗಮ attrs;
    }
  c_parser_consume_token (parser);

  ವೃಕ್ಷ attr_args
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    ಅಸತ್ಯ,
				    is_attribute_p ("assume", attr_name),
				    ಸತ್ಯ);

  attr = build_ವೃಕ್ಷ_list (attr_name, attr_args);
  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  ಅನ್ಯಥಾ
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ಯದಿ (expect_comma && !comma_first)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  ಪ್ರತ್ಯಾಗಮ attrs;
}

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_gnu_attributes (c_parser *parser)
{
  ವೃಕ್ಷ attrs = NULL_ವೃಕ್ಷ;
  ಯಾವತ್ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      ತಾರ್ಕಿಕ save_translate_strings_p = parser->translate_strings_p;
      parser->translate_strings_p = ಅಸತ್ಯ;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  ಪ್ರತ್ಯಾಗಮ attrs;
	}
      ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
	  ಪ್ರತ್ಯಾಗಮ attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      ಪ್ರತಿ (ತಾರ್ಕಿಕ expect_comma = ಅಸತ್ಯ; ; expect_comma = ಸತ್ಯ)
	{
	  /* Parse a single attribute.  */
	  ವೃಕ್ಷ attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  ಯದಿ (attr == error_mark_ಗಂಟು)
	    ಪ್ರತ್ಯಾಗಮ attrs;
	  ಯದಿ (!attr)
	    ಭಙ್ಗ;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      ಅನ್ಯಥಾ
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ಪ್ರತ್ಯಾಗಮ attrs;
	}
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      ಅನ್ಯಥಾ
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ಪ್ರತ್ಯಾಗಮ attrs;
	}
      parser->translate_strings_p = save_translate_strings_p;
    }

  ಪ್ರತ್ಯಾಗಮ attrs;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_balanced_token_sequence (c_parser *parser)
{
  ಯಾವತ್ (ಸತ್ಯ)
    {
      c_token *token = c_parser_peek_token (parser);
      ವಿಕಲ್ಪ (token->type)
	{
	ಪಕ್ಷ CPP_OPEN_BRACE:
	  {
	    matching_braces braces;
	    braces.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    braces.require_close (parser);
	    ಭಙ್ಗ;
	  }

	ಪಕ್ಷ CPP_OPEN_PAREN:
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    parens.require_close (parser);
	    ಭಙ್ಗ;
	  }

	ಪಕ್ಷ CPP_OPEN_SQUARE:
	  c_parser_consume_token (parser);
	  c_parser_balanced_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
	  ಭಙ್ಗ;

	ಪಕ್ಷ CPP_CLOSE_BRACE:
	ಪಕ್ಷ CPP_CLOSE_PAREN:
	ಪಕ್ಷ CPP_CLOSE_SQUARE:
	ಪಕ್ಷ CPP_EOF:
	  ಪ್ರತ್ಯಾಗಮ;

	ಪಕ್ಷ CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	  ಭಙ್ಗ;

	ಸ್ವಭಾವ:
	  c_parser_consume_token (parser);
	  ಭಙ್ಗ;
	}
    }
}

/* Parse arguments of omp::directive or omp::decl attribute.

   directive-name ,[opt] clause-list[opt]

   For directive just remember the tokens in a vector for subsequent
   parsing.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_directive_args (c_parser *parser, ವೃಕ್ಷ attribute, ತಾರ್ಕಿಕ decl_p)
{
  unsigned ಪೂರ್ಣಾಙ್ಕ n = 1;
  c_token *first = c_parser_peek_token (parser);
  ಯದಿ (!c_parser_check_balanced_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_balanced_token_sequence (parser);
      ವೃಕ್ಷ_ಮೌಲ್ಯ (attribute) = NULL_ವೃಕ್ಷ;
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (n == 1)
    {
      error_at (first->location, "expected OpenMP directive name");
      ವೃಕ್ಷ_ಮೌಲ್ಯ (attribute) = NULL_ವೃಕ್ಷ;
      ಪ್ರತ್ಯಾಗಮ;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  ಪ್ರತಿ (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->quick_ತಳ್ಳು (*tok);
      c_parser_consume_token (parser);
    }
  ವೃಕ್ಷ arg = make_ಗಂಟು (C_TOKEN_VEC);
  C_TOKEN_VEC_TOKENS (arg) = v;
  ಯದಿ (decl_p)
    ವೃಕ್ಷ_PUBLIC (arg) = 1;
  ವೃಕ್ಷ_ಮೌಲ್ಯ (attribute) = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, arg, ವೃಕ್ಷ_ಮೌಲ್ಯ (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_sequence_args (c_parser *parser, ವೃಕ್ಷ attribute)
{
  ಕುರು
    {
      c_token *token = c_parser_peek_token (parser);
      ಯದಿ (token->type == CPP_NAME
	  && strcmp (IDENTIFIER_POINTER (token->ಮೌಲ್ಯ), "omp") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_SCOPE)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  token = c_parser_peek_token (parser);
	}
      ತಾರ್ಕಿಕ directive = ಅಸತ್ಯ;
      ಧ್ರುವ ವರ್ಣ *p;
      ಯದಿ (token->type != CPP_NAME)
	p = "";
      ಅನ್ಯಥಾ
	p = IDENTIFIER_POINTER (token->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "directive") == 0)
	directive = ಸತ್ಯ;
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  unsigned nesting_depth = 0;

	  ಯಾವತ್ (ಸತ್ಯ)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      ಯದಿ ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_depth)
		ಭಙ್ಗ;
	      /* If we've run out of tokens, stop.  */
	      ಯದಿ (token->type == CPP_EOF)
		ಭಙ್ಗ;
	      ಯದಿ (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
		ಭಙ್ಗ;
	      ಯದಿ (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_SQUARE)
		++nesting_depth;
	      ಅನ್ಯಥಾ ಯದಿ (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_SQUARE)
		{
		  ಯದಿ (nesting_depth-- == 0)
		    ಭಙ್ಗ;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  ಯದಿ (c_parser_next_token_is_not (parser, CPP_COMMA))
	    ಭಙ್ಗ;
	  c_parser_consume_token (parser);
	  ಅನುವರ್ತ;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      ಯದಿ (parens.require_open (parser))
	{
	  ಯದಿ (directive)
	    c_parser_omp_directive_args (parser, attribute, ಅಸತ್ಯ);
	  ಅನ್ಯಥಾ
	    c_parser_omp_sequence_args (parser, attribute);
	  parens.skip_until_found_close (parser);
	  ಯದಿ (c_parser_next_token_is_not (parser, CPP_COMMA))
	    ಭಙ್ಗ;
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_not (parser, CPP_COMMA))
	ಭಙ್ಗ;
      ಅನ್ಯಥಾ
	c_parser_consume_token (parser);
    }
  ಯಾವತ್ (1);
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_std_attribute (c_parser *parser, ತಾರ್ಕಿಕ for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  ವೃಕ್ಷ ns, name, attribute;

  /* Parse the attribute-token.  */
  ಯದಿ (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  name = canonicalize_attr_name (token->ಮೌಲ್ಯ);
  c_parser_consume_token (parser);
  ಯದಿ (c_parser_next_token_is (parser, CPP_SCOPE)
      || (c_parser_next_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      ಯದಿ (c_parser_next_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      ಯದಿ (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      name = canonicalize_attr_name (token->ಮೌಲ್ಯ);
      c_parser_consume_token (parser);
    }
  ಅನ್ಯಥಾ
    ns = NULL_ವೃಕ್ಷ;
  attribute = build_ವೃಕ್ಷ_list (build_ವೃಕ್ಷ_list (ns, name), NULL_ವೃಕ್ಷ);

  /* Parse the arguments, if any.  */
  ಧ್ರುವ attribute_spec *as = lookup_attribute_spec (ವೃಕ್ಷ_PURPOSE (attribute));
  ಯದಿ (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      ಯದಿ ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಗಚ್ಛ out;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    ಯದಿ ((as && as->max_length == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_found_close (parser);
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    ಯದಿ (as && !attribute_ignored_p (as))
      {
	ತಾರ್ಕಿಕ takes_identifier
	  = (ns != NULL_ವೃಕ್ಷ
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	ತಾರ್ಕಿಕ require_string
	  = (ns == NULL_ವೃಕ್ಷ
	     && (strcmp (IDENTIFIER_POINTER (name), "deprecated") == 0
		 || strcmp (IDENTIFIER_POINTER (name), "nodiscard") == 0));
	ತಾರ್ಕಿಕ assume_attr
	  = (ns != NULL_ವೃಕ್ಷ
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && strcmp (IDENTIFIER_POINTER (name), "assume") == 0);
	ವೃಕ್ಷ_ಮೌಲ್ಯ (attribute)
	  = c_parser_attribute_arguments (parser, takes_identifier,
					  require_string, assume_attr, ಅಸತ್ಯ);
      }
    ಅನ್ಯಥಾ
      {
	ಯದಿ ((flag_openmp || flag_openmp_simd)
	    && ns
	    && is_attribute_p ("omp", ns))
	  {
	    ಯದಿ (is_attribute_p ("directive", name))
	      {
		c_parser_omp_directive_args (parser, attribute, ಅಸತ್ಯ);
		parens.skip_until_found_close (parser);
		ಪ್ರತ್ಯಾಗಮ attribute;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (is_attribute_p ("decl", name))
	      {
		ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_args (parser, attribute, ಸತ್ಯ);
		parens.skip_until_found_close (parser);
		ಪ್ರತ್ಯಾಗಮ attribute;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (is_attribute_p ("sequence", name))
	      {
		ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_args (parser, attribute);
		parens.skip_until_found_close (parser);
		ವೃಕ್ಷ_ಮೌಲ್ಯ (attribute) = nreverse (ವೃಕ್ಷ_ಮೌಲ್ಯ (attribute));
		ಪ್ರತ್ಯಾಗಮ attribute;
	      }
	  }
	c_parser_balanced_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 out:
  ಯದಿ (ns == NULL_ವೃಕ್ಷ && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (ಒಳಹರಿವು_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  ಪ್ರತ್ಯಾಗಮ attribute;
}

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_std_attribute_list (c_parser *parser, ತಾರ್ಕಿಕ for_tm)
{
  ವೃಕ್ಷ attributes = NULL_ವೃಕ್ಷ;
  ಯಾವತ್ (ಸತ್ಯ)
    {
      c_token *token = c_parser_peek_token (parser);
      ಯದಿ (token->type == CPP_CLOSE_SQUARE)
	ಭಙ್ಗ;
      ಯದಿ (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ಅನುವರ್ತ;
	}
      ವೃಕ್ಷ attribute = c_parser_std_attribute (parser, for_tm);
      ಯದಿ (attribute != error_mark_ಗಂಟು)
	{
	  ವೃಕ್ಷ_CHAIN (attribute) = attributes;
	  attributes = attribute;
	}
      ಯದಿ (c_parser_next_token_is_not (parser, CPP_COMMA))
	ಭಙ್ಗ;
    }
  ಪ್ರತ್ಯಾಗಮ attributes;
}

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_std_attribute_specifier (c_parser *parser, ತಾರ್ಕಿಕ for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ಯದಿ (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  ಯದಿ (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }
  ವೃಕ್ಷ attributes;
  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      auto ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      attributes = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      attributes = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  ಪ್ರತ್ಯಾಗಮ nreverse (attributes);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_check_balanced_raw_token_sequence (c_parser *parser, unsigned ಪೂರ್ಣಾಙ್ಕ *n)
{
  ಯಾವತ್ (ಸತ್ಯ)
    {
      c_token *token = c_parser_peek_nth_token_raw (parser, *n);
      ವಿಕಲ್ಪ (token->type)
	{
	ಪಕ್ಷ CPP_OPEN_BRACE:
	  {
	    ++*n;
	    ಯದಿ (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		ಯದಿ (token->type == CPP_CLOSE_BRACE)
		  ++*n;
		ಅನ್ಯಥಾ
		  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	      }
	    ಅನ್ಯಥಾ
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    ಭಙ್ಗ;
	  }

	ಪಕ್ಷ CPP_OPEN_PAREN:
	  {
	    ++*n;
	    ಯದಿ (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		ಯದಿ (token->type == CPP_CLOSE_PAREN)
		  ++*n;
		ಅನ್ಯಥಾ
		  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	      }
	    ಅನ್ಯಥಾ
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    ಭಙ್ಗ;
	  }

	ಪಕ್ಷ CPP_OPEN_SQUARE:
	  {
	    ++*n;
	    ಯದಿ (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		ಯದಿ (token->type == CPP_CLOSE_SQUARE)
		  ++*n;
		ಅನ್ಯಥಾ
		  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	      }
	    ಅನ್ಯಥಾ
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    ಭಙ್ಗ;
	  }

	ಪಕ್ಷ CPP_CLOSE_BRACE:
	ಪಕ್ಷ CPP_CLOSE_PAREN:
	ಪಕ್ಷ CPP_CLOSE_SQUARE:
	ಪಕ್ಷ CPP_EOF:
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

	ಸ್ವಭಾವ:
	  ++*n;
	  ಭಙ್ಗ;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_nth_token_starts_std_attributes (c_parser *parser, unsigned ಪೂರ್ಣಾಙ್ಕ n)
{
  ಯದಿ (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_SQUARE
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_SQUARE))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  ಯದಿ (!c_dialect_objc ())
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
  n += 2;
  ಯದಿ (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  ಯದಿ (token->type != CPP_CLOSE_SQUARE)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  ಪ್ರತ್ಯಾಗಮ token->type == CPP_CLOSE_SQUARE;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

ಸ್ಥಿರ size_t
c_parser_skip_std_attribute_spec_seq (c_parser *parser, size_t n)
{
  size_t orig_n = n;
  ಯಾವತ್ (ಸತ್ಯ)
    {
      ಯದಿ (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_SQUARE
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_SQUARE))
	{
	  unsigned ಪೂರ್ಣಾಙ್ಕ m = n + 2;
	  ಯದಿ (!c_parser_check_balanced_raw_token_sequence (parser, &m))
	    ಪ್ರತ್ಯಾಗಮ orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  ಯದಿ (token->type != CPP_CLOSE_SQUARE)
	    ಪ್ರತ್ಯಾಗಮ orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  ಯದಿ (token->type != CPP_CLOSE_SQUARE)
	    ಪ್ರತ್ಯಾಗಮ orig_n;
	  n = m + 2;
	}
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
    }
  ಪ್ರತ್ಯಾಗಮ n;
}

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  ವೃಕ್ಷ attributes = NULL_ವೃಕ್ಷ;
  ಕುರು
    {
      ವೃಕ್ಷ attrs = c_parser_std_attribute_specifier (parser, ಅಸತ್ಯ);
      attributes = chainon (attributes, attrs);
    }
  ಯಾವತ್ (c_parser_nth_token_starts_std_attributes (parser, 1));
  ಪ್ರತ್ಯಾಗಮ attributes;
}

/* Parse a type name (C90 6.5.5, C99 6.7.6, C11 6.7.7).  ALIGNAS_OK
   says whether alignment specifiers are OK (only in cases that might
   be the type name of a compound literal).

   type-name:
     specifier-qualifier-list abstract-declarator[opt]
*/

ಸಂರಚನಾ c_type_name *
c_parser_type_name (c_parser *parser, ತಾರ್ಕಿಕ alignas_ok)
{
  ಸಂರಚನಾ c_declspecs *specs = build_null_declspecs ();
  ಸಂರಚನಾ c_declarator *declarator;
  ಸಂರಚನಾ c_type_name *ret;
  ತಾರ್ಕಿಕ dummy = ಅಸತ್ಯ;
  c_parser_declspecs (parser, specs, ಅಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, alignas_ok, ಅಸತ್ಯ,
		      ಅಸತ್ಯ, ಸತ್ಯ, cla_prefer_type);
  ಯದಿ (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
  ಯದಿ (specs->type != error_mark_ಗಂಟು)
    {
      pending_xref_error ();
      finish_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      ಯದಿ (specs->typespec_kind == ctsk_tagdef)
	verify_counted_by_for_ತುದಿ_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_ABSTRACT, &dummy);
  ಯದಿ (declarator == ರಿಕ್ತ)
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
  ret = XOBNEW (&parser_obstack, ಸಂರಚನಾ c_type_name);
  ret->specs = specs;
  ret->declarator = declarator;
  ಪ್ರತ್ಯಾಗಮ ret;
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

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_initializer (c_parser *parser, ವೃಕ್ಷ decl)
{
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    ಪ್ರತ್ಯಾಗಮ c_parser_braced_init (parser, NULL_ವೃಕ್ಷ, ಅಸತ್ಯ, ರಿಕ್ತ,
				 decl != error_mark_ಗಂಟು
				 && C_DECL_VARIABLE_SIZE (decl));
  ಅನ್ಯಥಾ
    {
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಯದಿ (decl != error_mark_ಗಂಟು && C_DECL_VARIABLE_SIZE (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.set_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      ಯದಿ (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !ವೃಕ್ಷ_STATIC (decl)
	  && ret.ಮೌಲ್ಯ == decl
	  && !warning_enabled_at (DECL_SOURCE_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      ಯದಿ (ವೃಕ್ಷ_CODE (ret.ಮೌಲ್ಯ) != STRING_CST
	  && (ವೃಕ್ಷ_CODE (ret.ಮೌಲ್ಯ) != COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL
					    (ret.ಮೌಲ್ಯ))))
	ret = convert_lvalue_to_rvalue (loc, ret, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ ret;
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

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_braced_init (c_parser *parser, ವೃಕ್ಷ type, ತಾರ್ಕಿಕ nested_p,
		      ಸಂರಚನಾ obstack *outer_obstack, ತಾರ್ಕಿಕ varsize_p)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ಸಂರಚನಾ obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  ತಾರ್ಕಿಕ save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ zero_init_padding_bits = ಅಸತ್ಯ;
  matching_braces braces;
  braces.consume_open (parser);
  ಯದಿ (nested_p)
    {
      finish_implicit_inits (brace_loc, outer_obstack);
      ತಳ್ಳು_init_level (brace_loc, 0, &braced_init_obstack);
    }
  ಅನ್ಯಥಾ
    really_start_incremental_init (type);
  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      ಯದಿ (flag_isoc23)
	zero_init_padding_bits = ಸತ್ಯ;
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      ಯಾವತ್ (ಸತ್ಯ)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  ಯದಿ (parser->error)
	    ಭಙ್ಗ;
	  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      last_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      ಯಾವತ್ (c_parser_next_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_ಅಭಿವ್ಯಕ್ತಿ embed_val;
		  embed_val.ಮೌಲ್ಯ = embed->ಮೌಲ್ಯ;
		  embed_val.original_code = RAW_DATA_CST;
		  embed_val.original_type = integer_type_ಗಂಟು;
		  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, ಅಸತ್ಯ,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_next_token_is (parser,
							       CPP_COMMA));
		  last_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  ಅನ್ಯಥಾ
	    ಭಙ್ಗ;
	  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    ಭಙ್ಗ;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *next_tok = c_parser_peek_token (parser);
  ಯದಿ (next_tok->type != CPP_CLOSE_BRACE)
    {
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = ರಿಕ್ತ;
      braces.skip_until_found_close (parser);
      ತೆಗೆ_init_level (brace_loc, 0, &braced_init_obstack, last_init_list_comma);
      obstack_free (&braced_init_obstack, ರಿಕ್ತ);
      ಪ್ರತ್ಯಾಗಮ ret;
    }
  location_t close_loc = next_tok->location;
  c_parser_consume_token (parser);
  ret = ತೆಗೆ_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  ಯದಿ (zero_init_padding_bits
      && ret.ಮೌಲ್ಯ
      && ವೃಕ್ಷ_CODE (ret.ಮೌಲ್ಯ) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_BITS (ret.ಮೌಲ್ಯ) = 1;
  obstack_free (&braced_init_obstack, ರಿಕ್ತ);
  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ret, brace_loc, close_loc);
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Parse a nested initializer, including designators.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_initelt (c_parser *parser, ಸಂರಚನಾ obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      set_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->ಮೌಲ್ಯ,
		      c_parser_peek_token (parser)->location,
		      braced_init_obstack);
      /* Use the colon as the error location.  */
      pedwarn (c_parser_peek_2nd_token (parser)->location, OPT_Wpedantic,
	       "obsolete use of designated initializer with %<:%>");
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  ಅನ್ಯಥಾ
    {
      /* des_seen is 0 if there have been no designators, 1 if there
	 has been a single array designator and 2 otherwise.  */
      ಪೂರ್ಣಾಙ್ಕ des_seen = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      ಯಾವತ್ (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
	     || c_parser_next_token_is (parser, CPP_DOT))
	{
	  ಪೂರ್ಣಾಙ್ಕ des_prev = des_seen;
	  ಯದಿ (!des_seen)
	    des_loc = c_parser_peek_token (parser)->location;
	  ಯದಿ (des_seen < 2)
	    des_seen++;
	  ಯದಿ (c_parser_next_token_is (parser, CPP_DOT))
	    {
	      des_seen = 2;
	      c_parser_consume_token (parser);
	      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
		{
		  set_init_label (des_loc, c_parser_peek_token (parser)->ಮೌಲ್ಯ,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      ಅನ್ಯಥಾ
		{
		  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = ರಿಕ್ತ;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_found (parser, CPP_COMMA, ರಿಕ್ತ);
		  process_init_element (ಒಳಹರಿವು_location, init, ಅಸತ್ಯ,
					braced_init_obstack);
		  ಪ್ರತ್ಯಾಗಮ;
		}
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ first_ಅಭಿವ್ಯಕ್ತಿ;
	      ವೃಕ್ಷ first, second;
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
	      ಯದಿ (des_prev == 1 && c_dialect_objc ())
		{
		  des_seen = des_prev;
		  ಭಙ್ಗ;
		}
	      ಯದಿ (des_prev == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  ವೃಕ್ಷ rec, args;
		  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ mexpr;
		  c_parser_consume_token (parser);
		  ಯದಿ (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_kind
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_kind
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      ಗಚ್ಛ parse_message_args;
		    }
		  array_index_loc = c_parser_peek_token (parser)->location;
		  first_ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
		  mark_exp_read (first_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
		  ಯದಿ (c_parser_next_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    ಗಚ್ಛ array_desig_after_first;
		  first = first_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = first;
		  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ next;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      next = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
		      next = convert_lvalue_to_rvalue (exp_loc, next,
						       ಸತ್ಯ, ಸತ್ಯ);
		      rec = build_compound_ಅಭಿವ್ಯಕ್ತಿ (comma_loc, rec, next.ಮೌಲ್ಯ);
		    }
		parse_message_args:
		  /* Now parse the objc-message-args.  */
		  args = c_parser_objc_message_args (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					     "expected %<]%>");
		  mexpr.ಮೌಲ್ಯ
		    = objc_build_message_ಅಭಿವ್ಯಕ್ತಿ (rec, args);
		  mexpr.original_code = ERROR_MARK;
		  mexpr.original_type = ರಿಕ್ತ;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  ಪ್ರತ್ಯಾಗಮ;
		}
	      c_parser_consume_token (parser);
	      array_index_loc = c_parser_peek_token (parser)->location;
	      first_ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	      mark_exp_read (first_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	    array_desig_after_first:
	      first_ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (array_index_loc,
						     first_ಅಭಿವ್ಯಕ್ತಿ,
						     ಸತ್ಯ, ಸತ್ಯ);
	      first = first_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
	      ಯದಿ (c_parser_next_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  second = convert_lvalue_to_rvalue (ellipsis_loc,
						     (c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas
						      (parser, ರಿಕ್ತ)),
						     ಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;
		  mark_exp_read (second);
		}
	      ಅನ್ಯಥಾ
		second = NULL_ವೃಕ್ಷ;
	      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		{
		  c_parser_consume_token (parser);
		  set_init_index (array_index_loc, first, second,
				  braced_init_obstack);
		  ಯದಿ (second)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      ಅನ್ಯಥಾ
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					   "expected %<]%>");
	    }
	}
      ಯದಿ (des_seen >= 1)
	{
	  ಯದಿ (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಯದಿ (des_seen == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      ಅನ್ಯಥಾ
		{
		  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = ರಿಕ್ತ;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_found (parser, CPP_COMMA, ರಿಕ್ತ);
		  process_init_element (ಒಳಹರಿವು_location, init, ಅಸತ್ಯ,
					braced_init_obstack);
		  ಪ್ರತ್ಯಾಗಮ;
		}
	    }
	}
    }
  c_parser_initval (parser, ರಿಕ್ತ, braced_init_obstack);
}

/* Parse a nested initializer; as c_parser_initializer but parses
   initializers within braced lists, after any designators have been
   applied.  If AFTER is not NULL then it is an Objective-C message
   expression which is the primary-expression starting the
   initializer.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_initval (c_parser *parser, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ *after,
		  ಸಂರಚನಾ obstack * braced_init_obstack)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_ವೃಕ್ಷ, ಸತ್ಯ,
				 braced_init_obstack, ಅಸತ್ಯ);
  ಅನ್ಯಥಾ
    {
      init = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, after);
      ಯದಿ (init.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_CODE (init.ಮೌಲ್ಯ) != STRING_CST
	  && (ವೃಕ್ಷ_CODE (init.ಮೌಲ್ಯ) != COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL
					    (init.ಮೌಲ್ಯ))))
	init = convert_lvalue_to_rvalue (loc, init, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ);
    }
  ವೃಕ್ಷ val = init.ಮೌಲ್ಯ;
  process_init_element (loc, init, ಅಸತ್ಯ, braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  ಸ್ಥಿರ unsigned vals_to_ignore;
  ಯದಿ (vals_to_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_to_ignore;
  ಅನ್ಯಥಾ ಯದಿ (val
	   && ವೃಕ್ಷ_CODE (val) == INTEGER_CST
	   && ವೃಕ್ಷ_TYPE (val) == integer_type_ಗಂಟು
	   && c_parser_next_token_is (parser, CPP_COMMA))
    ಯದಿ (unsigned ಪೂರ್ಣಾಙ್ಕ len = c_maybe_optimize_large_byte_initializer ())
      {
	ವರ್ಣ buf1[64];
	unsigned ಪೂರ್ಣಾಙ್ಕ i;
	gcc_checking_assert (len >= 64);
	location_t last_loc = UNKNOWN_LOCATION;
	ಪ್ರತಿ (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    ಯದಿ (tok->type != CPP_COMMA)
	      ಭಙ್ಗ;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    ಯದಿ (tok->type != CPP_ಸಂಖ್ಯೆ
		|| ವೃಕ್ಷ_CODE (tok->ಮೌಲ್ಯ) != INTEGER_CST
		|| ವೃಕ್ಷ_TYPE (tok->ಮೌಲ್ಯ) != integer_type_ಗಂಟು
		|| wi::neg_p (wi::to_wide (tok->ಮೌಲ್ಯ))
		|| wi::to_widest (tok->ಮೌಲ್ಯ) > UCHAR_MAX)
	      ಭಙ್ಗ;
	    buf1[i] = (ವರ್ಣ) ವೃಕ್ಷ_to_uhwi (tok->ಮೌಲ್ಯ);
	    ಯದಿ (i == 0)
	      loc = tok->location;
	    last_loc = tok->location;
	  }
	ಯದಿ (i < 64)
	  {
	    vals_to_ignore = i;
	    ಪ್ರತ್ಯಾಗಮ;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	ಯದಿ (tok->type == CPP_CLOSE_BRACE && len != INT_MAX)
	  len = i;
	ಅನ್ಯಥಾ ಯದಿ (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_ಸಂಖ್ಯೆ))
	  {
	    vals_to_ignore = i;
	    ಪ್ರತ್ಯಾಗಮ;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	unsigned ಪೂರ್ಣಾಙ್ಕ max_len = 131072 - offsetof (ಸಂರಚನಾ ವೃಕ್ಷ_string, str) - 1;
	unsigned ಪೂರ್ಣಾಙ್ಕ orig_len = len;
	unsigned ಪೂರ್ಣಾಙ್ಕ off = 0, last = 0;
	ಯದಿ (!wi::neg_p (wi::to_wide (val)) && wi::to_widest (val) <= UCHAR_MAX)
	  off = 1;
	len = MIN (len, max_len - off);
	ವರ್ಣ *buf2 = XNEWVEC (ವರ್ಣ, len + off);
	ಯದಿ (off)
	  buf2[0] = (ವರ್ಣ) ವೃಕ್ಷ_to_uhwi (val);
	memcpy (buf2 + off, buf1, i);
	ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	ಪ್ರತಿ (; i < len; ++i)
	  {
	    ಯದಿ (!c_parser_next_token_is (parser, CPP_COMMA))
	      ಭಙ್ಗ;
	    tok = c_parser_peek_2nd_token (parser);
	    ಯದಿ (tok->type != CPP_ಸಂಖ್ಯೆ
		|| ವೃಕ್ಷ_CODE (tok->ಮೌಲ್ಯ) != INTEGER_CST
		|| ವೃಕ್ಷ_TYPE (tok->ಮೌಲ್ಯ) != integer_type_ಗಂಟು
		|| wi::neg_p (wi::to_wide (tok->ಮೌಲ್ಯ))
		|| wi::to_widest (tok->ಮೌಲ್ಯ) > UCHAR_MAX)
	      ಭಙ್ಗ;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    ಯದಿ (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      ಭಙ್ಗ;
	    buf2[i + off] = (ವರ್ಣ) ವೃಕ್ಷ_to_uhwi (tok->ಮೌಲ್ಯ);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    ಯದಿ (orig_len == INT_MAX
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_ಸಂಖ್ಯೆ)))
	      {
		last = 1;
		ಭಙ್ಗ;
	      }
	    last_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_ಗಂಟು (RAW_DATA_CST);
	ವೃಕ್ಷ_TYPE (val) = integer_type_ಗಂಟು;
	RAW_DATA_LENGTH (val) = i;
	ವೃಕ್ಷ owner = build_string (i + off + last, buf2);
	XDELETEVEC (buf2);
	ವೃಕ್ಷ_TYPE (owner) = build_array_type_nelts (unsigned_char_type_ಗಂಟು,
						    i + off + last);
	RAW_DATA_OWNER (val) = owner;
	RAW_DATA_POINTER (val) = ವೃಕ್ಷ_STRING_POINTER (owner) + off;
	init.ಮೌಲ್ಯ = val;
	set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&init, loc, last_loc);
	init.original_code = RAW_DATA_CST;
	init.original_type = integer_type_ಗಂಟು;
	init.m_decimal = 0;
	process_init_element (loc, init, ಅಸತ್ಯ, braced_init_obstack);
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  ವೃಕ್ಷ stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  ಯದಿ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (ಸತ್ಯ);
      c_end_compound_stmt (brace_loc, stmt, ಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  stmt = c_begin_compound_stmt (ಸತ್ಯ);
  location_t end_loc = c_parser_compound_statement_nostart (parser);
  ಯದಿ (endlocp)
    *endlocp = end_loc;

  ಪ್ರತ್ಯಾಗಮ c_end_compound_stmt (brace_loc, stmt, ಸತ್ಯ);
}

/* Diagnose errors related to imperfectly nested loops in an OMP
   loop construct.  This function is called when such code is seen.
   Only issue one such diagnostic no matter how much invalid
   intervening code there is in the loop.
   FIXME: maybe the location associated with the diagnostic should
   be the current parser token instead of the location of the outer loop
   nest.  */

ಸ್ಥಿರ ಶೂನ್ಯ
check_omp_intervening_code (c_parser *parser)
{
  ಸಂರಚನಾ omp_for_parse_data *omp_for_parse_state = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);

  ಯದಿ (!omp_for_parse_state->in_intervening_code)
    ಪ್ರತ್ಯಾಗಮ;
  omp_for_parse_state->saw_intervening_code = ಸತ್ಯ;

  /* Only diagnose errors related to perfect nesting once.  */
  ಯದಿ (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      ಯದಿ (omp_for_parse_state->code == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = ಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = ಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = ಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (omp_for_parse_state->code == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = ಸತ್ಯ;
	}
      ಯದಿ (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->fail = ಸತ್ಯ;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
ಸ್ಥಿರ ಶೂನ್ಯ
add_structured_block_stmt (ವೃಕ್ಷ sl)
{
  ಯದಿ (ವೃಕ್ಷ_CODE (sl) != STATEMENT_LIST
      || !tsi_end_p (tsi_start (sl)))
    add_stmt (build1 (OMP_STRUCTURED_BLOCK, void_type_ಗಂಟು, sl));
}

ಸಂರಚನಾ c_omp_attribute_data
{
  vec<c_token, va_gc> *tokens;
  ಧ್ರುವ c_omp_directive *dir;
  c_omp_directive_kind kind;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_handle_statement_omp_attributes (c_parser *parser, ವೃಕ್ಷ &attrs,
					  ತಾರ್ಕಿಕ *have_std_attrs)
{
  ಯದಿ (!flag_openmp && !flag_openmp_simd)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  auto_vec<c_omp_attribute_data, 16> vd;
  ಪೂರ್ಣಾಙ್ಕ cnt = 0;
  ಪೂರ್ಣಾಙ್ಕ tokens = 0;
  ತಾರ್ಕಿಕ bad = ಅಸತ್ಯ;
  ಪ್ರತಿ (ವೃಕ್ಷ *pa = &attrs; *pa; )
    ಯದಿ (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	ಪ್ರತಿ (ವೃಕ್ಷ a = ವೃಕ್ಷ_ಮೌಲ್ಯ (*pa); a; a = ವೃಕ್ಷ_CHAIN (a))
	  {
	    ವೃಕ್ಷ d = ವೃಕ್ಷ_ಮೌಲ್ಯ (a);
	    gcc_assert (ವೃಕ್ಷ_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    ಯದಿ (parser->omp_attrs_forbidden_p)
	      {
		error_at (first->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = ಅಸತ್ಯ;
		bad = ಸತ್ಯ;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_PUBLIC (d))
	      {
		error_at (first->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		bad = ಸತ್ಯ;
	      }
	    ಧ್ರುವ ವರ್ಣ *directive[3] = {};
	    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 3; i++)
	      {
		ವೃಕ್ಷ id = NULL_ವೃಕ್ಷ;
		ಯದಿ (first + i == last)
		  ಭಙ್ಗ;
		ಯದಿ (first[i].type == CPP_NAME)
		  id = first[i].ಮೌಲ್ಯ;
		ಅನ್ಯಥಾ ಯದಿ (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(ಪೂರ್ಣಾಙ್ಕ) first[i].keyword];
		ಅನ್ಯಥಾ
		  ಭಙ್ಗ;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    ಧ್ರುವ c_omp_directive *dir = ರಿಕ್ತ;
	    ಯದಿ (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    ಯದಿ (dir == ರಿಕ್ತ)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  ವೃಕ್ಷ_PUBLIC (d) ? "omp::decl" : "omp::directive");
		ಅನುವರ್ತ;
	      }
	    c_omp_directive_kind kind = dir->kind;
	    ಯದಿ (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		ಯದಿ (directive[1]
		    && (strcmp (directive[1], "depend") == 0
			|| strcmp (directive[1], "doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
		ಅನ್ಯಥಾ ಯದಿ (first + 2 < last
			 && first[1].type == CPP_COMMA
			 && first[2].type == CPP_NAME
			 && (strcmp (IDENTIFIER_POINTER (first[2].ಮೌಲ್ಯ),
				     "depend") == 0
			     || strcmp (IDENTIFIER_POINTER (first[2].ಮೌಲ್ಯ),
					"doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		ಪೂರ್ಣಾಙ್ಕ paren_depth = 0;
		ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 1; first + i < last; i++)
		  ಯದಿ (first[i].type == CPP_OPEN_PAREN)
		    paren_depth++;
		  ಅನ್ಯಥಾ ಯದಿ (first[i].type == CPP_CLOSE_PAREN)
		    paren_depth--;
		  ಅನ್ಯಥಾ ಯದಿ (paren_depth == 0
			   && first + i + 2 < last
			   && first[i].type == CPP_NAME
			   && first[i + 1].type == CPP_OPEN_PAREN
			   && first[i + 2].type == CPP_NAME
			   && !strcmp (IDENTIFIER_POINTER (first[i].ಮೌಲ್ಯ),
				       "at")
			   && !strcmp (IDENTIFIER_POINTER (first[i
								 + 2].ಮೌಲ್ಯ),
				       "execution"))
		    {
		      kind = C_OMP_DIR_STANDALONE;
		      ಭಙ್ಗ;
		    }
	      }
	    c_omp_attribute_data v = { toks, dir, kind };
	    vd.safe_ತಳ್ಳು (v);
	    ಯದಿ (flag_openmp || dir->simd)
	      tokens += (last - first) + 1;
	  }
	c_omp_attribute_data v = {};
	vd.safe_ತಳ್ಳು (v);
	*pa = ವೃಕ್ಷ_CHAIN (*pa);
      }
    ಅನ್ಯಥಾ
      pa = &ವೃಕ್ಷ_CHAIN (*pa);

  ಯದಿ (bad)
    {
    fail:
      ಯದಿ (have_std_attrs && attrs == ರಿಕ್ತ)
	*have_std_attrs = ಅಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  unsigned ಪೂರ್ಣಾಙ್ಕ i;
  c_omp_attribute_data *v;
  c_omp_attribute_data *construct_seen = nullptr;
  c_omp_attribute_data *standalone_seen = nullptr;
  c_omp_attribute_data *prev_standalone_seen = nullptr;
  FOR_EACH_VEC_ELT (vd, i, v)
    ಯದಿ (v->tokens)
      {
	ಯದಿ (v->kind == C_OMP_DIR_CONSTRUCT && !construct_seen)
	  construct_seen = v;
	ಅನ್ಯಥಾ ಯದಿ (v->kind == C_OMP_DIR_STANDALONE && !standalone_seen)
	  standalone_seen = v;
      }
    ಅನ್ಯಥಾ
      {
	ಯದಿ (standalone_seen && !prev_standalone_seen)
	  {
	    prev_standalone_seen = standalone_seen;
	    standalone_seen = nullptr;
	  }
      }

  ಯದಿ (cnt > 1 && construct_seen)
    {
      error_at ((*construct_seen->tokens)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      ಗಚ್ಛ fail;
    }
  ಯದಿ (cnt > 1 && standalone_seen && prev_standalone_seen)
    {
      error_at ((*standalone_seen->tokens)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      ಗಚ್ಛ fail;
    }

  ಯದಿ (prev_standalone_seen)
    standalone_seen = prev_standalone_seen;
  ಯದಿ (standalone_seen
      && !c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_seen->tokens->address ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      ಗಚ್ಛ fail;
    }
  ಯದಿ (cnt && c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      ಗಣನಾ pragma_kind kind = token->pragma_kind;
      ಯದಿ (kind >= PRAGMA_OMP__START_ && kind <= PRAGMA_OMP__LAST_)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  ಗಚ್ಛ fail;
	}
    }

  ಯದಿ (!tokens)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  unsigned ಪೂರ್ಣಾಙ್ಕ tokens_avail = parser->tokens_avail;

  tokens++;
  vec<c_token, va_gc> *toks = ರಿಕ್ತ;
  vec_safe_reserve (toks, tokens, ಸತ್ಯ);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      ಯದಿ (!v->tokens)
	ಅನುವರ್ತ;
      ಯದಿ (!flag_openmp && !v->dir->simd)
	ಅನುವರ್ತ;
      c_token *first = v->tokens->address ();
      c_token *last = first + v->tokens->length ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_kind = pragma_kind (v->dir->id);
      tok.location = first->location;
      toks->quick_ತಳ್ಳು (tok);
      ಯಾವತ್ (++first < last)
	toks->quick_ತಳ್ಳು (*first);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = last[-1].location;
      toks->quick_ತಳ್ಳು (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->last ().location;
  toks->quick_ತಳ್ಳು (tok);

  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = tokens;
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_handle_directive_omp_attributes (ವೃಕ್ಷ &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  ಯದಿ (!flag_openmp && !flag_openmp_simd)
    ಪ್ರತ್ಯಾಗಮ;

  ಪ್ರತಿ (ವೃಕ್ಷ *pa = &attrs; *pa; )
    ಯದಿ (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	ಪೂರ್ಣಾಙ್ಕ cnt = 0;
	ಪ್ರತಿ (ವೃಕ್ಷ *pa2 = &ವೃಕ್ಷ_ಮೌಲ್ಯ (*pa); *pa2; )
	  {
	    ವೃಕ್ಷ a = *pa2;
	    ವೃಕ್ಷ d = ವೃಕ್ಷ_ಮೌಲ್ಯ (a);
	    gcc_assert (ವೃಕ್ಷ_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    ಧ್ರುವ ವರ್ಣ *directive[3] = {};
	    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 3; i++)
	      {
		ವೃಕ್ಷ id = NULL_ವೃಕ್ಷ;
		ಯದಿ (first + i == last)
		  ಭಙ್ಗ;
		ಯದಿ (first[i].type == CPP_NAME)
		  id = first[i].ಮೌಲ್ಯ;
		ಅನ್ಯಥಾ ಯದಿ (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(ಪೂರ್ಣಾಙ್ಕ) first[i].keyword];
		ಅನ್ಯಥಾ
		  ಭಙ್ಗ;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    ಧ್ರುವ c_omp_directive *dir = ರಿಕ್ತ;
	    ಯದಿ (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    ಯದಿ (dir == ರಿಕ್ತ)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  ವೃಕ್ಷ_PUBLIC (d) ? "omp::decl" : "omp::directive");
		*pa2 = ವೃಕ್ಷ_CHAIN (a);
	      }
	    ಅನ್ಯಥಾ ಯದಿ (dir->id == PRAGMA_OMP_DECLARE
		     && (strcmp (directive[1], "simd") == 0
			 || strcmp (directive[1], "variant") == 0))
	      {
		ಯದಿ (pragma_clauses)
		  {
		    error_at (first->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    ಪ್ರತಿ (pa = &attrs; *pa; )
		      ಯದಿ (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = ವೃಕ್ಷ_CHAIN (*pa);
		      ಅನ್ಯಥಾ
			pa = &ವೃಕ್ಷ_CHAIN (*pa);
		    ಪ್ರತ್ಯಾಗಮ;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->length ()
				       + toks->length () + 2);
		ಪ್ರತಿ (++first; first < last; ++first)
		  attr_clauses->quick_ತಳ್ಳು (*first);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = last[-1].location;
		attr_clauses->quick_ತಳ್ಳು (tok);
		*pa2 = ವೃಕ್ಷ_CHAIN (a);
	      }
	    ಅನ್ಯಥಾ
	      pa2 = &ವೃಕ್ಷ_CHAIN (a);
	  }
	ಯದಿ (cnt && ವೃಕ್ಷ_ಮೌಲ್ಯ (*pa) == NULL_ವೃಕ್ಷ)
	  *pa = ವೃಕ್ಷ_CHAIN (*pa);
	ಅನ್ಯಥಾ
	  pa = &ವೃಕ್ಷ_CHAIN (*pa);
      }
    ಅನ್ಯಥಾ
      pa = &ವೃಕ್ಷ_CHAIN (*pa);
  ಯದಿ (attr_clauses->length ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->last ().location;
      attr_clauses->quick_ತಳ್ಳು (tok);
      attr_clauses->quick_ತಳ್ಳು (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_handle_musttail (c_parser *parser, ವೃಕ್ಷ std_attrs, attr_state &attr)
{
  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_RETURN))
    {
      ಯದಿ (ವೃಕ್ಷ a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  ಪ್ರತಿ (; a; a = lookup_attribute ("gnu", "musttail", ವೃಕ್ಷ_CHAIN (a)))
	    ಯದಿ (ವೃಕ್ಷ_ಮೌಲ್ಯ (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = ಸತ್ಯ;
	}
      ಯದಿ (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = ಸತ್ಯ;
	}
    }
  ಪ್ರತ್ಯಾಗಮ std_attrs;
}

/* Return a statement before optional series of LABEL_EXPR/CASE_LABEL_EXPRs.
   Instead of collecting vectors of labels before each stmt just in case
   the statement would be iteration or switch statement for named loops,
   we just remember last emitted statement and let the iteration/switch
   statement search backwards in cur_stmt_list until that stmt for loop
   names if any.  */

ಸ್ಥಿರ ವೃಕ್ಷ
get_before_labels ()
{
  ಯದಿ (!building_stmt_list_p ())
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ_stmt_iterator tsi = tsi_last (cur_stmt_list);
  ಯದಿ (tsi_end_p (tsi))
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  ಪ್ರತ್ಯಾಗಮ tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

ಸ್ಥಿರ location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  ತಾರ್ಕಿಕ last_stmt = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ last_label = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  ಸಂರಚನಾ omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  ತಾರ್ಕಿಕ in_omp_loop_block
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : ಅಸತ್ಯ;
  ವೃಕ್ಷ sl = NULL_ವೃಕ್ಷ;
  attr_state astate = {};

  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      add_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      ಪ್ರತ್ಯಾಗಮ endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  ಯದಿ (in_omp_loop_block)
    sl = ತಳ್ಳು_stmt_list ();

  mark_valid_location_for_stdc_pragma (ಸತ್ಯ);
  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (ಅಸತ್ಯ);
      ಯದಿ (in_omp_loop_block)
	check_omp_intervening_code (parser);
      ಯಾವತ್ (c_parser_next_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  ಯಾವತ್ (ಸತ್ಯ)
	    {
	      ವೃಕ್ಷ label;
	      ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  ಭಙ್ಗ;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      add_stmt (build_stmt (label_loc, DECL_ಅಭಿವ್ಯಕ್ತಿ, label));
	      c_parser_consume_token (parser);
	      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      ಅನ್ಯಥಾ
		ಭಙ್ಗ;
	    }
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ಪ್ರತ್ಯಾಗಮ endloc;
    }
  ವೃಕ್ಷ before_labels = get_before_labels ();
  ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_point_location_if_in_system_header (loc);

      ತಾರ್ಕಿಕ want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : ಅಸತ್ಯ);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      ಯದಿ (in_omp_loop_block && !last_label)
	{
	  ವೃಕ್ಷ_code code = omp_for_parse_state->code;
	  ಯದಿ (want_nested_loop
	      && c_parser_omp_next_tokens_can_be_canon_loop (parser, code,
							     ಅಸತ್ಯ))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      add_structured_block_stmt (ತೆಗೆ_stmt_list (sl));
	      omp_for_parse_state->depth++;
	      add_stmt (c_parser_omp_loop_nest (parser, ರಿಕ್ತ));
	      omp_for_parse_state->depth--;
	      sl = ತಳ್ಳು_stmt_list ();
	      parser->error = ಅಸತ್ಯ;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ಅನುವರ್ತ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (want_nested_loop
		   && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      ವೃಕ್ಷ pre_sl = ತೆಗೆ_stmt_list (sl);
	      ವೃಕ್ಷ nested_sl = ತಳ್ಳು_stmt_list ();
	      mark_valid_location_for_stdc_pragma (ಅಸತ್ಯ);
	      c_parser_statement_after_labels (parser, ರಿಕ್ತ, NULL_ವೃಕ್ಷ);
	      nested_sl = ತೆಗೆ_stmt_list (nested_sl);
	      ಯದಿ (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_code (parser);
		  sl = ತಳ್ಳು_stmt_list ();
		  add_stmt (pre_sl);
		  add_stmt (nested_sl);
		}
	      ಅನ್ಯಥಾ
		{
		  /* It contains the nested loop.  */
		  add_structured_block_stmt (pre_sl);
		  add_stmt (nested_sl);
		  sl = ತಳ್ಳು_stmt_list ();
		}
	      parser->error = ಅಸತ್ಯ;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ಅನುವರ್ತ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      /* Prior to implementing the OpenMP 5.1 syntax for canonical
		 loop form, GCC used to accept an empty statements that
		 would now be flagged as intervening code.  Continue to
		 do that, as an extension.  */
	      /* FIXME:  Maybe issue a warning or something here?  */
	      c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ಅನುವರ್ತ;
	    }
	}

      /* Standard attributes may start a label, statement or declaration.  */
      ತಾರ್ಕಿಕ have_std_attrs
	= c_parser_nth_token_starts_std_attributes (parser, 1);
      ವೃಕ್ಷ std_attrs = NULL_ವೃಕ್ಷ;
      ಯದಿ (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      ಯದಿ (c_parser_next_token_is_keyword (parser, RID_CASE)
	  || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  ಅನ್ಯಥಾ
	    label_loc = c_parser_peek_token (parser)->location;
	  last_label = ಸತ್ಯ;
	  last_stmt = ಅಸತ್ಯ;
	  mark_valid_location_for_stdc_pragma (ಅಸತ್ಯ);
	  ಯದಿ (in_omp_loop_block)
	    check_omp_intervening_code (parser);
	  c_parser_label (parser, std_attrs);
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_tokens_start_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_attributes
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_next_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = ಸತ್ಯ)))
	{
	  ಯದಿ (last_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  ಯದಿ (in_omp_loop_block)
	    {
	      check_omp_intervening_code (parser);
	      omp_for_parse_state->want_nested_loop = ಅಸತ್ಯ;
	    }
	  mark_valid_location_for_stdc_pragma (ಅಸತ್ಯ);
	  ತಾರ್ಕಿಕ fallthru_attr_p = ಅಸತ್ಯ;
	  c_parser_declaration_or_fndef (parser, ಸತ್ಯ, !have_std_attrs,
					 ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ,
					 ರಿಕ್ತ, have_std_attrs, std_attrs,
					 ರಿಕ್ತ, &fallthru_attr_p);

	  ಯದಿ (in_omp_loop_block)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  ಯದಿ (last_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  last_stmt = fallthru_attr_p;
	  last_label = ಅಸತ್ಯ;
	  before_labels = get_before_labels ();
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  If standard attributes have already
	     been seen, it must start a statement, not a declaration,
	     but standard attributes starting a declaration may appear
	     after __extension__.  */
	  ಯಾವತ್ (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  ಯದಿ (!have_std_attrs
	      && (c_parser_next_tokens_start_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_attributes (parser, 2)))
	    {
	      ಪೂರ್ಣಾಙ್ಕ ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      last_label = ಅಸತ್ಯ;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      ಯದಿ (in_omp_loop_block)
		{
		  check_omp_intervening_code (parser);
		  omp_for_parse_state->want_nested_loop = ಅಸತ್ಯ;
		}
	      mark_valid_location_for_stdc_pragma (ಅಸತ್ಯ);
	      c_parser_declaration_or_fndef (parser, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ,
					     ಸತ್ಯ, ಅಸತ್ಯ);
	      ಯದಿ (in_omp_loop_block)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      ಯದಿ (last_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      last_stmt = ಅಸತ್ಯ;
	      before_labels = get_before_labels ();
	    }
	  ಅನ್ಯಥಾ
	    ಗಚ್ಛ statement;
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  ಯದಿ (have_std_attrs && !parser->in_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  ಅನ್ಯಥಾ ಯದಿ (std_attrs)
	    c_warn_unused_attributes (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  ಯದಿ (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = ಅಸತ್ಯ;
	  ಯದಿ (c_parser_pragma (parser,
			       last_label ? pragma_stmt : pragma_compound,
			       ರಿಕ್ತ, before_labels))
	    {
	      last_label = ಅಸತ್ಯ;
	      last_stmt = ಸತ್ಯ;
	      ಯದಿ (omp_for_parse_state)
		check_omp_intervening_code (parser);
	    }
	  ಯದಿ (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  ಪ್ರತ್ಯಾಗಮ c_parser_peek_token (parser)->location;
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_ELSE))
        {
          ಯದಿ (parser->in_if_block)
            {
	      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	      error_at (loc, "expected %<}%> before %<else%>");
	      ಪ್ರತ್ಯಾಗಮ c_parser_peek_token (parser)->location;
            }
          ಅನ್ಯಥಾ
            {
              error_at (loc, "%<else%> without a previous %<if%>");
              c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
              ಅನುವರ್ತ;
            }
        }
      ಅನ್ಯಥಾ
	{
	statement:
	  c_warn_unused_attributes (std_attrs);
	  last_label = ಅಸತ್ಯ;
	  last_stmt = ಸತ್ಯ;
	  mark_valid_location_for_stdc_pragma (ಅಸತ್ಯ);
	  ಯದಿ (!omp_for_parse_state)
	    c_parser_statement_after_labels (parser, ರಿಕ್ತ, before_labels,
					     ರಿಕ್ತ, astate);
	  ಅನ್ಯಥಾ
	    {
	      /* In canonical loop nest form, nested loops can only appear
		 directly, or in a directly nested compound statement.  We
		 already took care of those cases above, so now we have
		 something else.  This statement and everything inside
		 it must be intervening code.  */
	      omp_for_parse_state->want_nested_loop = ಅಸತ್ಯ;
	      check_omp_intervening_code (parser);
	      c_parser_statement_after_labels (parser, ರಿಕ್ತ, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = ಅಸತ್ಯ;
      astate.reset ();
    }
  ಯದಿ (last_label)
    pedwarn_c11 (label_loc, OPT_Wfree_labels,
		 "label at end of compound statement");
  location_t endloc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  /* Restore the value we started with.  */
  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);

  /* Package leftover intervening code, or the whole contents of the
     compound statement if we were looking for a nested loop in an OMP_FOR
     construct and didn't find one.  */
  ಯದಿ (sl)
    {
      sl = ತೆಗೆ_stmt_list (sl);
      ಯದಿ (omp_for_parse_state->want_nested_loop)
	add_stmt (sl);
      ಅನ್ಯಥಾ
	add_structured_block_stmt (sl);
    }
  ಪ್ರತ್ಯಾಗಮ endloc;
}

/* Parse all consecutive labels, possibly preceded by standard
   attributes.  In this context, a statement is required, not a
   declaration, so attributes must be followed by a statement that is
   not just a semicolon.  Returns an attr_state.  */

ಸ್ಥಿರ attr_state
c_parser_all_labels (c_parser *parser)
{
  attr_state attr = {};
  ತಾರ್ಕಿಕ have_std_attrs;
  ವೃಕ್ಷ std_attrs = ರಿಕ್ತ;
  ಯದಿ ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  ಯಾವತ್ (c_parser_next_token_is_keyword (parser, RID_CASE)
	 || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = ರಿಕ್ತ;
      ಯದಿ ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  ಯದಿ (std_attrs
      && (!c_parser_handle_statement_omp_attributes (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      ಯದಿ (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_unused_attributes (std_attrs);
    }
  ಅನ್ಯಥಾ ಯದಿ (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  ಪ್ರತ್ಯಾಗಮ attr;
}


/* Information used while parsing an OpenMP metadirective.  */
ಸಂರಚನಾ omp_metadirective_parse_data {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<ವೃಕ್ಷ> * GTY((skip)) body_labels;
  unsigned ಪೂರ್ಣಾಙ್ಕ region_ಅಂಕೆ;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
ಸ್ಥಿರ ವೃಕ್ಷ
mangle_metadirective_region_label (c_parser *parser, ವೃಕ್ಷ name)
{
  ಯದಿ (parser->omp_metadirective_state->body_labels->contains (name))
    {
      ಧ್ರುವ ವರ್ಣ *old_name = IDENTIFIER_POINTER (name);
      ವರ್ಣ *new_name = (ವರ್ಣ *) XALLOCAVEC (ವರ್ಣ, strlen (old_name) + 32);
      sprintf (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_ಅಂಕೆ);
      ಪ್ರತ್ಯಾಗಮ get_identifier (new_name);
    }
  ಪ್ರತ್ಯಾಗಮ name;
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
ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_label (c_parser *parser, ವೃಕ್ಷ std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ label = NULL_ವೃಕ್ಷ;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  ತಾರ್ಕಿಕ fallthrough_p = c_parser_peek_token (parser)->flags & PREV_FALLTHROUGH;

  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_CASE))
    {
      ವೃಕ್ಷ exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_to_rvalue (loc1,
				       c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ),
				       ಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_ವೃಕ್ಷ, std_attrs);
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_to_rvalue (loc1,
					   c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser,
								    ರಿಕ್ತ),
					   ಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;
	  ಯದಿ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      ಅನ್ಯಥಾ
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ, std_attrs);
    }
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ name = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      ವೃಕ್ಷ tlab;
      ವೃಕ್ಷ attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_attributes (parser);
      ಯದಿ (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      ಯದಿ (tlab)
	{
	  decl_attributes (&tlab, attrs, 0);
	  decl_attributes (&tlab, std_attrs, 0);
	  label = add_stmt (build_stmt (loc1, LABEL_ಅಭಿವ್ಯಕ್ತಿ, tlab));
	}
      ಯದಿ (attrs
	  && c_parser_next_tokens_start_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  ಯದಿ (label)
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (label) == LABEL_ಅಭಿವ್ಯಕ್ತಿ)
	FALLTHROUGH_LABEL_P (LABEL_ಅಭಿವ್ಯಕ್ತಿ_LABEL (label)) = fallthrough_p;
      ಅನ್ಯಥಾ
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_statement (c_parser *parser, ತಾರ್ಕಿಕ *if_p, location_t *loc_after_labels)
{
  ವೃಕ್ಷ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  ಯದಿ (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = ಅಸತ್ಯ;
  c_parser_statement_after_labels (parser, if_p, before_labels, ರಿಕ್ತ, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_bc_name (c_parser *parser, ತಾರ್ಕಿಕ is_break)
{
  ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME))
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  c_token *tok = c_parser_peek_token (parser);
  ವೃಕ್ಷ label = c_finish_bc_name (tok->location, tok->ಮೌಲ್ಯ, is_break);
  c_parser_consume_token (parser);
  ಪ್ರತ್ಯಾಗಮ label;
}

/* Parse a statement, other than a labeled statement.  CHAIN is a vector
   of if-else-if conditions.  All labels and standard attributes have
   been parsed in the caller.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  ASTATE is an earlier parsed attribute state.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_statement_after_labels (c_parser *parser, ತಾರ್ಕಿಕ *if_p,
				 ವೃಕ್ಷ before_labels,
				 vec<ವೃಕ್ಷ> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ stmt = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ in_if_block = parser->in_if_block;
  parser->in_if_block = ಅಸತ್ಯ;
  ಯದಿ (if_p != ರಿಕ್ತ)
    *if_p = ಅಸತ್ಯ;

  ಯದಿ (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    add_debug_begin_stmt (loc);

 restart:
  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
    {
    ಪಕ್ಷ CPP_OPEN_BRACE:
      add_stmt (c_parser_compound_statement (parser));
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_KEYWORD:
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->keyword)
	{
	ಪಕ್ಷ RID_IF:
	  c_parser_if_statement (parser, if_p, chain);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_SWITCH:
	  c_parser_switch_statement (parser, if_p, before_labels);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_WHILE:
	  c_parser_while_statement (parser, ಅಸತ್ಯ, 0, ಅಸತ್ಯ, if_p, before_labels);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_DO:
	  c_parser_do_statement (parser, ಅಸತ್ಯ, 0, ಅಸತ್ಯ, before_labels);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_FOR:
	  c_parser_for_statement (parser, ಅಸತ್ಯ, 0, ಅಸತ್ಯ, if_p, before_labels);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_GOTO:
	  c_parser_consume_token (parser);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      ವೃಕ್ಷ name = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	      ಯದಿ (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_finish_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_MULT))
	    {
	      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ val;

	      c_parser_consume_token (parser);
	      val = c_parser_expression (parser);
	      val = convert_lvalue_to_rvalue (loc, val, ಅಸತ್ಯ, ಸತ್ಯ);
	      stmt = c_finish_goto_ptr (loc, val);
	    }
	  ಅನ್ಯಥಾ
	    c_parser_error (parser, "expected identifier or %<*%>");
	  ಗಚ್ಛ expect_semicolon;
	ಪಕ್ಷ RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_continue_label, ಅಸತ್ಯ,
				   c_parser_bc_name (parser, ಅಸತ್ಯ));
	  ಗಚ್ಛ expect_semicolon;
	ಪಕ್ಷ RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_break_label, ಸತ್ಯ,
				   c_parser_bc_name (parser, ಸತ್ಯ));
	  ಗಚ್ಛ expect_semicolon;
	ಪಕ್ಷ RID_RETURN:
	  c_parser_consume_token (parser);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_finish_return (loc, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  ಅನ್ಯಥಾ
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_expression_conv (parser);
	      mark_exp_read (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	      stmt = c_finish_return (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, xloc),
				      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಭಿವ್ಯಕ್ತಿ.original_type,
				      astate.musttail_p);
	      ಗಚ್ಛ expect_semicolon;
	    }
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_TRANSACTION_ATOMIC:
	ಪಕ್ಷ RID_TRANSACTION_RELAXED:
	  stmt = c_parser_transaction (parser,
	      c_parser_peek_token (parser)->keyword);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_TRANSACTION_CANCEL:
	  stmt = c_parser_transaction_cancel (parser);
	  ಗಚ್ಛ expect_semicolon;
	ಪಕ್ಷ RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_ವೃಕ್ಷ);
	      c_parser_consume_token (parser);
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_expression (parser);
	      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಅಸತ್ಯ);
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
	      stmt = objc_build_throw_stmt (loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	      ಗಚ್ಛ expect_semicolon;
	    }
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_finally_statement (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_ATTRIBUTE:
	  {
	    /* Allow '__attribute__((fallthrough));' or
	       '__attribute__((assume(cond)));' or
	       '__attribute__((musttail))) return'.  */
	    ವೃಕ್ಷ attrs = c_parser_gnu_attributes (parser);
	    ತಾರ್ಕಿಕ has_assume = lookup_attribute ("assume", attrs);
	    ಯದಿ (has_assume)
	      {
		ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, ಸತ್ಯ);
		ಅನ್ಯಥಾ
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<assume%> attribute not followed by %<;%>");
		    has_assume = ಅಸತ್ಯ;
		  }
	      }
	    gcc_assert (!astate.musttail_p);
	    attrs = c_parser_handle_musttail (parser, attrs, astate);
	    ಯದಿ (astate.musttail_p)
	      {
		ಯದಿ (attrs)
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		ಗಚ್ಛ restart;
	      }
	    ಯದಿ (attribute_fallthrough_p (attrs))
	      {
		ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  {
		    ವೃಕ್ಷ fn = build_call_ಅಭಿವ್ಯಕ್ತಿ_internal_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_ಗಂಟು, 0);
		    add_stmt (fn);
		    /* Eat the ';'.  */
		    c_parser_consume_token (parser);
		  }
		ಅನ್ಯಥಾ
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<fallthrough%> attribute not followed "
				"by %<;%>");
		  }
	      }
	    ಅನ್ಯಥಾ ಯದಿ (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    ಅನ್ಯಥಾ ಯದಿ (attrs != NULL_ವೃಕ್ಷ)
	      {
		auto_urlify_attributes sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    ಭಙ್ಗ;
	  }
	ಸ್ವಭಾವ:
	  ಗಚ್ಛ ಅಭಿವ್ಯಕ್ತಿ_stmt;
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_SEMICOLON:
      c_parser_consume_token (parser);
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_CLOSE_PAREN:
    ಪಕ್ಷ CPP_CLOSE_SQUARE:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_PRAGMA:
      ಯದಿ (!c_parser_pragma (parser, pragma_stmt, if_p, before_labels))
        ಗಚ್ಛ restart;
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
    ಅಭಿವ್ಯಕ್ತಿ_stmt:
      stmt = c_finish_ಅಭಿವ್ಯಕ್ತಿ_stmt (loc, c_parser_expression_conv (parser).ಮೌಲ್ಯ);
    expect_semicolon:
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      ಭಙ್ಗ;
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
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (stmt, loc);

  parser->in_if_block = in_if_block;
}

/* Parse the condition from an if, do, while or for statements.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ cond;
  cond = c_parser_expression_conv (parser).ಮೌಲ್ಯ;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, ಅಸತ್ಯ, ರಿಕ್ತ);
  ಯದಿ (warn_sequence_point)
    verify_sequence_points (cond);
  ಪ್ರತ್ಯಾಗಮ cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_paren_condition (c_parser *parser)
{
  ವೃಕ್ಷ cond;
  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
  cond = c_parser_condition (parser);
  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ cond;
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

ಸ್ಥಿರ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_selection_header (c_parser *parser, ತಾರ್ಕಿಕ switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  ತಾರ್ಕಿಕ parse_ಅಭಿವ್ಯಕ್ತಿ = ಸತ್ಯ;
  ವೃಕ್ಷ std_attrs;
  ತಾರ್ಕಿಕ have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  ಯದಿ (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  ಅನ್ಯಥಾ
    std_attrs = NULL_ವೃಕ್ಷ;
  ಯದಿ (c_parser_next_tokens_start_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/ಅಸತ್ಯ,
					 /*static_assert_ok=*/ಅಸತ್ಯ,
					 /*empty_ok=*/ಅಸತ್ಯ,
					 /*nested=*/ಸತ್ಯ,
					 /*start_attr_ok=*/ಸತ್ಯ,
					 /*simple_ok=*/ಸತ್ಯ,
					 /*objc_foreach_object_decl=*/nullptr,
					 /*omp_declare_simd_clauses=*/nullptr,
					 have_std_attrs,
					 std_attrs);
      ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      ಅನ್ಯಥಾ
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  ಯದಿ (!ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      ಅಭಿವ್ಯಕ್ತಿ.original_type = error_mark_ಗಂಟು;
	      ಅಭಿವ್ಯಕ್ತಿ.set_error ();
	      ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
	    }
	  parse_ಅಭಿವ್ಯಕ್ತಿ = ಅಸತ್ಯ;
	}
      ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ)
	{
	  ಅಭಿವ್ಯಕ್ತಿ.original_type = ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (loc, ಅಭಿವ್ಯಕ್ತಿ, /*convert_p=*/ಸತ್ಯ,
					   /*read_p=*/ಸತ್ಯ);
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      ಅಭಿವ್ಯಕ್ತಿ.original_type = error_mark_ಗಂಟು;
      ಅಭಿವ್ಯಕ್ತಿ.set_error ();
      ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
    }

  ಯದಿ (parse_ಅಭಿವ್ಯಕ್ತಿ)
    ಅಭಿವ್ಯಕ್ತಿ = c_parser_expression_conv (parser);
  ಯದಿ (!switch_p)
    {
      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_objc_common_truthvalue_conversion (loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
      ಯದಿ (warn_sequence_point)
	verify_sequence_points (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
    }
  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_paren_selection_header (c_parser *parser)
{
  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
  ವೃಕ್ಷ cond = c_parser_selection_header (parser, /*switch_p=*/ಅಸತ್ಯ).ಮೌಲ್ಯ;
  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_c99_block_statement (c_parser *parser, ತಾರ್ಕಿಕ *if_p,
			      location_t *loc_after_labels)
{
  ವೃಕ್ಷ block = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  ಪ್ರತ್ಯಾಗಮ c_end_compound_stmt (loc, block, flag_isoc99);
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_if_body (c_parser *parser, ತಾರ್ಕಿಕ *if_p,
		  ಧ್ರುವ token_indent_info &if_tinfo)
{
  ವೃಕ್ಷ block = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  ವೃಕ್ಷ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
      ಯದಿ (!c_parser_next_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    add_stmt (c_parser_compound_statement (parser));
  ಅನ್ಯಥಾ
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, ರಿಕ್ತ, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, next_tinfo);
  ಯದಿ (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    if_tinfo.location, RID_IF);

  ಪ್ರತ್ಯಾಗಮ c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_else_body (c_parser *parser, ಧ್ರುವ token_indent_info &else_tinfo,
		    vec<ವೃಕ್ಷ> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ block = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  ವೃಕ್ಷ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      warning_at (loc,
		  OPT_Wempty_body,
	         "suggest braces around empty body in an %<else%> statement");
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, ರಿಕ್ತ, before_labels, chain, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, next_tinfo);
  ಯದಿ (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  ಪ್ರತ್ಯಾಗಮ c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse an if statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   if-statement:
     if ( selection-header ) statement
     if ( selection-header ) statement else statement

   CHAIN is a vector of if-else-if conditions.
   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_if_statement (c_parser *parser, ತಾರ್ಕಿಕ *if_p, vec<ವೃಕ್ಷ> *chain)
{
  ವೃಕ್ಷ block;
  location_t loc;
  ವೃಕ್ಷ cond;
  ತಾರ್ಕಿಕ nested_if = ಅಸತ್ಯ;
  ವೃಕ್ಷ first_body, second_body;
  ತಾರ್ಕಿಕ in_if_block;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_IF));
  token_indent_info if_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_selection_header (parser);
  in_if_block = parser->in_if_block;
  parser->in_if_block = ಸತ್ಯ;
  first_body = c_parser_if_body (parser, &nested_if, if_tinfo);
  parser->in_if_block = in_if_block;

  ಯದಿ (warn_duplicated_cond)
    warn_duplicated_cond_add_or_warn (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (cond), cond, &chain);

  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      ಯದಿ (warn_duplicated_cond)
	{
	  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_IF)
	      && chain == ರಿಕ್ತ)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = ನೂತನ vec<ವೃಕ್ಷ> ();
	      ಯದಿ (!CONSTANT_CLASS_P (cond) && !ವೃಕ್ಷ_SIDE_EFFECTS (cond))
		chain->safe_ತಳ್ಳು (cond);
	    }
	  ಅನ್ಯಥಾ ಯದಿ (!c_parser_next_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      second_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      ಯದಿ (if_p != ರಿಕ್ತ)
	*if_p = ಸತ್ಯ;
    }
  ಅನ್ಯಥಾ
    {
      second_body = NULL_ವೃಕ್ಷ;

      /* Diagnose an ambiguous else if if-then-else is nested inside
	 if-then.  */
      ಯದಿ (nested_if)
	warning_at (loc, OPT_Wdangling_else,
		    "suggest explicit braces to avoid ambiguous %<else%>");

      ಯದಿ (warn_duplicated_cond)
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_switch_statement (c_parser *parser, ತಾರ್ಕಿಕ *if_p, ವೃಕ್ಷ before_labels)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ce;
  ವೃಕ್ಷ block, ಅಭಿವ್ಯಕ್ತಿ, body;
  unsigned ವರ್ಣ save_in_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  ವೃಕ್ಷ switch_name;
  ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_names = c_get_loop_names (before_labels, ಸತ್ಯ, &switch_name);
  block = c_begin_compound_stmt (flag_isoc99);
  ತಾರ್ಕಿಕ explicit_cast_p = ಅಸತ್ಯ;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = ಸತ್ಯ;
      ce = c_parser_selection_header (parser, /*switch_p=*/ಸತ್ಯ);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_to_rvalue (switch_cond_loc, ce, ಸತ್ಯ, ಸತ್ಯ);
      ಅಭಿವ್ಯಕ್ತಿ = ce.ಮೌಲ್ಯ;
      /* ??? expr has no valid location?  */
      parens.skip_until_found_close (parser);
    }
  ಅನ್ಯಥಾ
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      ಅಭಿವ್ಯಕ್ತಿ = error_mark_ಗಂಟು;
      ce.original_type = error_mark_ಗಂಟು;
    }
  ವೃಕ್ಷ stmt
    = c_start_switch (switch_loc, switch_cond_loc, ಅಭಿವ್ಯಕ್ತಿ, explicit_cast_p,
		      switch_name);
  save_in_statement = in_statement;
  in_statement |= IN_SWITCH_STMT;
  ಯದಿ (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  ಅನ್ಯಥಾ
    in_statement &= ~IN_NAMED_STMT;
  location_t loc_after_labels;
  ತಾರ್ಕಿಕ open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  location_t next_loc = c_parser_peek_token (parser)->location;
  ಯದಿ (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, next_loc, switch_loc,
				    RID_SWITCH);
  c_finish_switch (body, ce.original_type);
  in_statement = save_in_statement;
  ಯದಿ (ಅಂಕೆ_names)
    {
      ಯದಿ (!C_DECL_LOOP_SWITCH_NAME_USED (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_ವೃಕ್ಷ;
      ಅನ್ಯಥಾ
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_names (ಅಂಕೆ_names);
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_while_statement (c_parser *parser, ತಾರ್ಕಿಕ ivdep, unsigned short unroll,
			  ತಾರ್ಕಿಕ novector, ತಾರ್ಕಿಕ *if_p, ವೃಕ್ಷ before_labels)
{
  ವೃಕ್ಷ block, cond, body;
  unsigned ವರ್ಣ save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  ವೃಕ್ಷ loop_name;
  ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_names = c_get_loop_names (before_labels, ಅಸತ್ಯ, &loop_name);

  ಯದಿ (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = ಸತ್ಯ;
    }

  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  ಯದಿ (ivdep && cond != error_mark_ಗಂಟು)
    cond = build3 (ANNOTATE_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (cond), cond,
		   build_int_cst (integer_type_ಗಂಟು,
				  annot_ಅಭಿವ್ಯಕ್ತಿ_ivdep_kind),
		   integer_zero_ಗಂಟು);
  ಯದಿ (unroll && cond != error_mark_ಗಂಟು)
    cond = build3 (ANNOTATE_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (cond), cond,
		   build_int_cst (integer_type_ಗಂಟು,
				  annot_ಅಭಿವ್ಯಕ್ತಿ_unroll_kind),
		   build_int_cst (integer_type_ಗಂಟು, unroll));
  ಯದಿ (novector && cond != error_mark_ಗಂಟು)
    cond = build3 (ANNOTATE_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (cond), cond,
		   build_int_cst (integer_type_ಗಂಟು,
				  annot_ಅಭಿವ್ಯಕ್ತಿ_no_vector_kind),
		   integer_zero_ಗಂಟು);
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  ಯದಿ (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  ತಾರ್ಕಿಕ open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  ಯದಿ (loop_name && !C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
    loop_name = NULL_ವೃಕ್ಷ;
  add_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_ವೃಕ್ಷ,
			NULL_ವೃಕ್ಷ));
  add_stmt (c_end_compound_stmt (loc, block, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  ಯದಿ (ಅಂಕೆ_names)
    c_release_loop_names (ಅಂಕೆ_names);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, next_tinfo);

  ಯದಿ (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    while_tinfo.location, RID_WHILE);

  in_statement = save_in_statement;
}

/* Parse a do statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   do-statement:
     do statement while ( expression ) ;

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_do_statement (c_parser *parser, ತಾರ್ಕಿಕ ivdep, unsigned short unroll,
		       ತಾರ್ಕಿಕ novector, ವೃಕ್ಷ before_labels)
{
  ವೃಕ್ಷ block, cond, body;
  unsigned ವರ್ಣ save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_DO));
  ವೃಕ್ಷ loop_name;
  ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_names = c_get_loop_names (before_labels, ಅಸತ್ಯ, &loop_name);

  ಯದಿ (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = ಸತ್ಯ;
    }

  c_parser_consume_token (parser);
  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  ಯದಿ (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  body = c_parser_c99_block_statement (parser, ರಿಕ್ತ);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  in_statement = save_in_statement;
  ಯದಿ (ಅಂಕೆ_names)
    {
      ಯದಿ (!C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
	loop_name = NULL_ವೃಕ್ಷ;
      c_release_loop_names (ಅಂಕೆ_names);
    }
  cond = c_parser_paren_condition (parser);
  ಯದಿ (ivdep && cond != error_mark_ಗಂಟು)
    cond = build3 (ANNOTATE_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (cond), cond,
		   build_int_cst (integer_type_ಗಂಟು,
				  annot_ಅಭಿವ್ಯಕ್ತಿ_ivdep_kind),
		   integer_zero_ಗಂಟು);
  ಯದಿ (unroll && cond != error_mark_ಗಂಟು)
    cond = build3 (ANNOTATE_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (cond), cond,
		   build_int_cst (integer_type_ಗಂಟು,
				  annot_ಅಭಿವ್ಯಕ್ತಿ_unroll_kind),
 		   build_int_cst (integer_type_ಗಂಟು, unroll));
  ಯದಿ (novector && cond != error_mark_ಗಂಟು)
    cond = build3 (ANNOTATE_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (cond), cond,
		   build_int_cst (integer_type_ಗಂಟು,
				  annot_ಅಭಿವ್ಯಕ್ತಿ_no_vector_kind),
		   integer_zero_ಗಂಟು);
  ಯದಿ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_for_statement (c_parser *parser, ತಾರ್ಕಿಕ ivdep, unsigned short unroll,
			ತಾರ್ಕಿಕ novector, ತಾರ್ಕಿಕ *if_p, ವೃಕ್ಷ before_labels)
{
  ವೃಕ್ಷ block, cond, incr, body;
  unsigned ವರ್ಣ save_in_statement;
  ವೃಕ್ಷ save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  ವೃಕ್ಷ object_expression;
  /* Silence the bogus uninitialized warning.  */
  ವೃಕ್ಷ collection_expression = ರಿಕ್ತ;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  ತಾರ್ಕಿಕ is_foreach_statement = ಅಸತ್ಯ;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  ವೃಕ್ಷ loop_name;
  ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_names = c_get_loop_names (before_labels, ಅಸತ್ಯ, &loop_name);

  ಯದಿ (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = ಸತ್ಯ;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  block = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_ಗಂಟು;
  incr = error_mark_ಗಂಟು;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_expression = error_mark_ಗಂಟು;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = ಅಸತ್ಯ;
	  c_parser_consume_token (parser);
	  c_finish_ಅಭಿವ್ಯಕ್ತಿ_stmt (loc, NULL_ವೃಕ್ಷ);
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_tokens_start_declaration (parser)
	       || c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ,
					 ಅಸತ್ಯ, &object_expression);
	  parser->objc_could_be_foreach_context = ಅಸತ್ಯ;

	  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = ಸತ್ಯ;
	      ಯದಿ (check_for_loop_decls (for_loc, ಸತ್ಯ) == NULL_ವೃಕ್ಷ)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  ಅನ್ಯಥಾ
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  ಯಾವತ್ (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  ಯದಿ (c_parser_next_tokens_start_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_attributes (parser, 2))
	    {
	      ಪೂರ್ಣಾಙ್ಕ ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ,
					     ಸತ್ಯ, ಅಸತ್ಯ, &object_expression);
	      parser->objc_could_be_foreach_context = ಅಸತ್ಯ;

	      restore_extension_diagnostics (ext);
	      ಯದಿ (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = ಸತ್ಯ;
		  ಯದಿ (check_for_loop_decls (for_loc, ಸತ್ಯ) == NULL_ವೃಕ್ಷ)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      ಅನ್ಯಥಾ
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  ಅನ್ಯಥಾ
	    ಗಚ್ಛ init_ಅಭಿವ್ಯಕ್ತಿ;
	}
      ಅನ್ಯಥಾ
	{
	init_ಅಭಿವ್ಯಕ್ತಿ:
	  {
	    ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ce;
	    ವೃಕ್ಷ init_expression;
	    ce = c_parser_expression (parser);
	    init_expression = ce.ಮೌಲ್ಯ;
	    parser->objc_could_be_foreach_context = ಅಸತ್ಯ;
	    ಯದಿ (c_parser_next_token_is_keyword (parser, RID_IN))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = ಸತ್ಯ;
		ಯದಿ (! lvalue_p (init_expression))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_expression
		  = c_fully_fold (init_expression, ಅಸತ್ಯ, ರಿಕ್ತ);
	      }
	    ಅನ್ಯಥಾ
	      {
		ce = convert_lvalue_to_rvalue (loc, ce, ಸತ್ಯ, ಅಸತ್ಯ);
		init_expression = ce.ಮೌಲ್ಯ;
		c_finish_ಅಭಿವ್ಯಕ್ತಿ_stmt (loc, init_expression);
		c_parser_skip_until_found (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      ಯದಿ (!is_foreach_statement)
	{
	  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      ಯದಿ (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_ಗಂಟು;
		}
	      ಅನ್ಯಥಾ ಯದಿ (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_ಗಂಟು;
		}
	      ಅನ್ಯಥಾ
		{
		  c_parser_consume_token (parser);
		  cond = NULL_ವೃಕ್ಷ;
		}
	    }
	  ಅನ್ಯಥಾ
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_found (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  ಯದಿ (ivdep && cond != error_mark_ಗಂಟು)
	    cond = build3 (ANNOTATE_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (cond), cond,
			   build_int_cst (integer_type_ಗಂಟು,
					  annot_ಅಭಿವ್ಯಕ್ತಿ_ivdep_kind),
			   integer_zero_ಗಂಟು);
	  ಯದಿ (unroll && cond != error_mark_ಗಂಟು)
	    cond = build3 (ANNOTATE_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (cond), cond,
 			   build_int_cst (integer_type_ಗಂಟು,
					  annot_ಅಭಿವ್ಯಕ್ತಿ_unroll_kind),
			   build_int_cst (integer_type_ಗಂಟು, unroll));
	  ಯದಿ (novector && cond && cond != error_mark_ಗಂಟು)
	    cond = build3 (ANNOTATE_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (cond), cond,
			   build_int_cst (integer_type_ಗಂಟು,
					  annot_ಅಭಿವ್ಯಕ್ತಿ_no_vector_kind),
			   integer_zero_ಗಂಟು);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ಯದಿ (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_expression = error_mark_ಗಂಟು;
	    }
	  ಅನ್ಯಥಾ
	    incr = c_process_ಅಭಿವ್ಯಕ್ತಿ_stmt (loc, NULL_ವೃಕ್ಷ);
	}
      ಅನ್ಯಥಾ
	{
	  ಯದಿ (is_foreach_statement)
	    collection_expression
	      = c_fully_fold (c_parser_expression (parser).ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
	  ಅನ್ಯಥಾ
	    {
	      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ce = c_parser_expression (parser);
	      ce = convert_lvalue_to_rvalue (loc, ce, ಸತ್ಯ, ಅಸತ್ಯ);
	      incr = c_process_ಅಭಿವ್ಯಕ್ತಿ_stmt (loc, ce.ಮೌಲ್ಯ);
	    }
	}
      parens.skip_until_found_close (parser);
    }
  save_in_statement = in_statement;
  ಯದಿ (is_foreach_statement)
    {
      in_statement = IN_OBJC_FOREACH;
      save_objc_foreach_break_label = objc_foreach_break_label;
      save_objc_foreach_continue_label = objc_foreach_continue_label;
      objc_foreach_break_label = create_artificial_label (loc);
      objc_foreach_continue_label = create_artificial_label (loc);
      ಯದಿ (loop_name)
	{
	  gcc_checking_assert (!DECL_CHAIN (loop_name)
			       && !DECL_CHAIN (objc_foreach_break_label));
	  C_DECL_SWITCH_NAME (loop_name) = 1;
	  DECL_CHAIN (loop_name) = objc_foreach_break_label;
	  DECL_CHAIN (objc_foreach_break_label) = objc_foreach_continue_label;
	}
    }
  ಅನ್ಯಥಾ
    in_statement = IN_ITERATION_STMT;
  ಯದಿ (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  ತಾರ್ಕಿಕ open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);

  ಯದಿ (loop_name && is_foreach_statement)
    {
      gcc_checking_assert (DECL_CHAIN (loop_name) == objc_foreach_break_label
			   && (DECL_CHAIN (objc_foreach_break_label)
			       == objc_foreach_continue_label));
      C_DECL_SWITCH_NAME (loop_name) = 0;
      DECL_CHAIN (loop_name) = NULL_ವೃಕ್ಷ;
      DECL_CHAIN (objc_foreach_break_label) = NULL_ವೃಕ್ಷ;
    }

  ಯದಿ (is_foreach_statement)
    objc_finish_foreach_loop (for_loc, object_expression,
			      collection_expression, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  ಅನ್ಯಥಾ
    add_stmt (build_stmt (for_loc, FOR_STMT, NULL_ವೃಕ್ಷ, cond, incr,
			  body, NULL_ವೃಕ್ಷ,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_USED (loop_name)
			  ? loop_name : NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ));
  add_stmt (c_end_compound_stmt (for_loc, block,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, next_tinfo);

  ಯದಿ (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    for_tinfo.location, RID_FOR);

  in_statement = save_in_statement;
  ಯದಿ (ಅಂಕೆ_names)
    c_release_loop_names (ಅಂಕೆ_names);
  ಯದಿ (is_foreach_statement)
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_asm_statement (c_parser *parser)
{
  ವೃಕ್ಷ str, outputs, inputs, clobbers, labels, ret;
  ತಾರ್ಕಿಕ simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  ಪೂರ್ಣಾಙ್ಕ section, nsections;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);

  /* Handle the asm-qualifier-list.  */
  location_t volatile_loc = UNKNOWN_LOCATION;
  location_t inline_loc = UNKNOWN_LOCATION;
  location_t goto_loc = UNKNOWN_LOCATION;
  ಪ್ರತಿ (;;)
    {
      c_token *token = c_parser_peek_token (parser);
      location_t loc = token->location;
      ವಿಕಲ್ಪ (token->keyword)
	{
	ಪಕ್ಷ RID_VOLATILE:
	  ಯದಿ (volatile_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->ಮೌಲ್ಯ);
	      inform (volatile_loc, "first seen here");
	    }
	  ಅನ್ಯಥಾ
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ RID_INLINE:
	  ಯದಿ (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->ಮೌಲ್ಯ);
	      inform (inline_loc, "first seen here");
	    }
	  ಅನ್ಯಥಾ
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ RID_GOTO:
	  ಯದಿ (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->ಮೌಲ್ಯ);
	      inform (goto_loc, "first seen here");
	    }
	  ಅನ್ಯಥಾ
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ RID_CONST:
	ಪಕ್ಷ RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->ಮೌಲ್ಯ);
	  c_parser_consume_token (parser);
	  ಅನುವರ್ತ;

	ಸ್ವಭಾವ:
	  ಭಙ್ಗ;
	}
      ಭಙ್ಗ;
    }

  ತಾರ್ಕಿಕ is_volatile = (volatile_loc != UNKNOWN_LOCATION);
  ತಾರ್ಕಿಕ is_inline = (inline_loc != UNKNOWN_LOCATION);
  ತಾರ್ಕಿಕ is_goto = (goto_loc != UNKNOWN_LOCATION);

  ret = ರಿಕ್ತ;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಗಚ್ಛ error;

  str = c_parser_asm_string_literal (parser);
  ಯದಿ (str == NULL_ವೃಕ್ಷ)
    ಗಚ್ಛ error_close_paren;

  simple = ಸತ್ಯ;
  outputs = NULL_ವೃಕ್ಷ;
  inputs = NULL_ವೃಕ್ಷ;
  clobbers = NULL_ವೃಕ್ಷ;
  labels = NULL_ವೃಕ್ಷ;

  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    ಗಚ್ಛ done_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  ಪ್ರತಿ (section = 0; section < nsections; ++section)
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  ಯದಿ (section == nsections)
	    {
	      c_parser_error (parser, "expected %<)%>");
	      ಗಚ್ಛ error_close_paren;
	    }
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ ಯದಿ (!c_parser_require (parser, CPP_COLON,
				  is_goto
				  ? G_("expected %<:%>")
				  : G_("expected %<:%> or %<)%>"),
				  UNKNOWN_LOCATION, is_goto))
	ಗಚ್ಛ error_close_paren;

      /* Once past any colon, we're no longer a simple asm.  */
      simple = ಅಸತ್ಯ;

      ಯದಿ ((!c_parser_next_token_is (parser, CPP_COLON)
	   && !c_parser_next_token_is (parser, CPP_SCOPE)
	   && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	  || section == 3)
	ವಿಕಲ್ಪ (section)
	  {
	  ಪಕ್ಷ 0:
	    outputs = c_parser_asm_operands (parser);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ 1:
	    inputs = c_parser_asm_operands (parser);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ 2:
	    clobbers = c_parser_asm_clobbers (parser);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ 3:
	    labels = c_parser_asm_goto_operands (parser);
	    ಭಙ್ಗ;
	  ಸ್ವಭಾವ:
	    gcc_unreachable ();
	  }

      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	ಗಚ್ಛ done_asm;
    }

 done_asm:
  ಯದಿ (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
      ಗಚ್ಛ error;
    }

  ಯದಿ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_to_end_of_block_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_ಅಭಿವ್ಯಕ್ತಿ (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  ಪ್ರತ್ಯಾಗಮ ret;

 error_close_paren:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
  ಗಚ್ಛ error;
}

/* Parse asm operands, a GNU extension.

   asm-operands:
     asm-operand
     asm-operands , asm-operand

   asm-operand:
     asm-string-literal ( expression )
     [ identifier ] asm-string-literal ( expression )
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_asm_operands (c_parser *parser)
{
  ವೃಕ್ಷ list = NULL_ವೃಕ್ಷ;
  ಯಾವತ್ (ಸತ್ಯ)
    {
      ವೃಕ್ಷ name, str;
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
	{
	  c_parser_consume_token (parser);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_LENGTH (id),
				   IDENTIFIER_POINTER (id));
	    }
	  ಅನ್ಯಥಾ
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, ರಿಕ್ತ);
	      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
	    }
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	}
      ಅನ್ಯಥಾ
	name = NULL_ವೃಕ್ಷ;
      str = c_parser_asm_string_literal (parser);
      ಯದಿ (str == NULL_ವೃಕ್ಷ)
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
      matching_parens parens;
      ಯದಿ (!parens.require_open (parser))
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_expression (parser);
      mark_exp_read (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
      ಯದಿ (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
	  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
	}
      list = chainon (list, build_ವೃಕ್ಷ_list (build_ವೃಕ್ಷ_list (name, str),
					     ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ));
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
    }
  ಪ್ರತ್ಯಾಗಮ list;
}

/* Parse asm clobbers, a GNU extension.

   asm-clobbers:
     asm-string-literal
     asm-clobbers , asm-string-literal
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_asm_clobbers (c_parser *parser)
{
  ವೃಕ್ಷ list = NULL_ವೃಕ್ಷ;
  ಯಾವತ್ (ಸತ್ಯ)
    {
      ವೃಕ್ಷ str = c_parser_asm_string_literal (parser);
      ಯದಿ (str)
	list = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, str, list);
      ಅನ್ಯಥಾ
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
    }
  ಪ್ರತ್ಯಾಗಮ list;
}

/* Parse asm goto labels, a GNU extension.

   asm-goto-operands:
     identifier
     asm-goto-operands , identifier
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_asm_goto_operands (c_parser *parser)
{
  ವೃಕ್ಷ list = NULL_ವೃಕ್ಷ;
  ಯಾವತ್ (ಸತ್ಯ)
    {
      ವೃಕ್ಷ name, label;

      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->ಮೌಲ್ಯ;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  ವೃಕ್ಷ_USED (label) = 1;
	}
      ಅನ್ಯಥಾ
	{
	  c_parser_error (parser, "expected identifier");
	  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
	}

      name = build_string (IDENTIFIER_LENGTH (name),
			   IDENTIFIER_POINTER (name));
      list = ವೃಕ್ಷ_cons (name, label, list);
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ಅನ್ಯಥಾ
	ಪ್ರತ್ಯಾಗಮ nreverse (list);
    }
}

/* Parse a possibly concatenated sequence of string literals.
   TRANSLATE says whether to translate them to the execution character
   set; WIDE_OK says whether any kind of prefixed string literal is
   permitted in this context.  This code is based on that in
   lex_string.  */

ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_string_literal (c_parser *parser, ತಾರ್ಕಿಕ translate, ತಾರ್ಕಿಕ wide_ok)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  size_t ಎಣಿಕೆ;
  ಸಂರಚನಾ obstack str_ob;
  ಸಂರಚನಾ obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, last_tok_loc;
  ಗಣನಾ cpp_ttype type;
  ವೃಕ್ಷ ಮೌಲ್ಯ, string_ವೃಕ್ಷ;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  last_tok_loc = linemap_resolve_location (ಸಾಲು_table, loc,
					   LRK_MACRO_DEFINITION_LOCATION,
					   ರಿಕ್ತ);
  type = tok->type;
  ವಿಕಲ್ಪ (type)
    {
    ಪಕ್ಷ CPP_STRING:
    ಪಕ್ಷ CPP_WSTRING:
    ಪಕ್ಷ CPP_STRING16:
    ಪಕ್ಷ CPP_STRING32:
    ಪಕ್ಷ CPP_UTF8STRING:
      string_ವೃಕ್ಷ = tok->ಮೌಲ್ಯ;
      ಭಙ್ಗ;

    ಸ್ವಭಾವ:
      c_parser_error (parser, "expected string literal");
      ret.set_error ();
      ret.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
      ret.original_code = ERROR_MARK;
      ret.original_type = NULL_ವೃಕ್ಷ;
      ಪ್ರತ್ಯಾಗಮ ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  ವಿಕಲ್ಪ (c_parser_peek_2nd_token (parser)->type)
    {
    ಸ್ವಭಾವ:
      c_parser_consume_token (parser);
      str.text = (ಧ್ರುವ unsigned ವರ್ಣ *) ವೃಕ್ಷ_STRING_POINTER (string_ವೃಕ್ಷ);
      str.len = ವೃಕ್ಷ_STRING_LENGTH (string_ವೃಕ್ಷ);
      ಎಣಿಕೆ = 1;
      strs = &str;
      ಭಙ್ಗ;

    ಪಕ್ಷ CPP_STRING:
    ಪಕ್ಷ CPP_WSTRING:
    ಪಕ್ಷ CPP_STRING16:
    ಪಕ್ಷ CPP_STRING32:
    ಪಕ್ಷ CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      ಎಣಿಕೆ = 0;
      ಕುರು
	{
	  c_parser_consume_token (parser);
	  ಎಣಿಕೆ++;
	  str.text = (ಧ್ರುವ unsigned ವರ್ಣ *) ವೃಕ್ಷ_STRING_POINTER (string_ವೃಕ್ಷ);
	  str.len = ವೃಕ್ಷ_STRING_LENGTH (string_ವೃಕ್ಷ);
	  ಯದಿ (type != tok->type)
	    {
	      ಯದಿ (type == CPP_STRING)
		type = tok->type;
	      ಅನ್ಯಥಾ ಯದಿ (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, ಪರಿಮಾಣ (cpp_string));
	  obstack_grow (&loc_ob, &last_tok_loc, ಪರಿಮಾಣ (location_t));
	  tok = c_parser_peek_token (parser);
	  string_ವೃಕ್ಷ = tok->ಮೌಲ್ಯ;
	  last_tok_loc
	    = linemap_resolve_location (ಸಾಲು_table, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, ರಿಕ್ತ);
	}
      ಯಾವತ್ (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_finish (&str_ob);
    }

  ಯದಿ (ಎಣಿಕೆ > 1 && !in_system_header_at (ಒಳಹರಿವು_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  ಯದಿ ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_in, strs, ಎಣಿಕೆ, &istr, type)))
    {
      ಮೌಲ್ಯ = build_string (istr.len, (ಧ್ರುವ ವರ್ಣ *) istr.text);
      ಮುಕ್ತ (const_cast<unsigned ವರ್ಣ *> (istr.text));
      ಯದಿ (ಎಣಿಕೆ > 1)
	{
	  location_t *locs = (location_t *) obstack_finish (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->record_string_concatenation (ಎಣಿಕೆ, locs);
	}
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (type != CPP_STRING && !wide_ok)
	{
	  error_at (loc, "a wide string is invalid in this context");
	  type = CPP_STRING;
	}
      /* Callers cannot generally handle error_mark_node in this
	 context, so return the empty string instead.  An error has
	 been issued, either above or from cpp_interpret_string.  */
      ವಿಕಲ್ಪ (type)
	{
	ಸ್ವಭಾವ:
	ಪಕ್ಷ CPP_STRING:
	ಪಕ್ಷ CPP_UTF8STRING:
	  ಯದಿ (type == CPP_UTF8STRING && flag_char8_t)
	    {
	      ಮೌಲ್ಯ = build_string (TYPE_PRECISION (char8_type_ಗಂಟು)
				    / TYPE_PRECISION (char_type_ಗಂಟು),
				    "");  /* char8_t is 8 bits */
	    }
	  ಅನ್ಯಥಾ
	    ಮೌಲ್ಯ = build_string (1, "");
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_STRING16:
	  ಮೌಲ್ಯ = build_string (TYPE_PRECISION (char16_type_ಗಂಟು)
				/ TYPE_PRECISION (char_type_ಗಂಟು),
				"\0");  /* char16_t is 16 bits */
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_STRING32:
	  ಮೌಲ್ಯ = build_string (TYPE_PRECISION (char32_type_ಗಂಟು)
				/ TYPE_PRECISION (char_type_ಗಂಟು),
				"\0\0\0");  /* char32_t is 32 bits */
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_WSTRING:
	  ಮೌಲ್ಯ = build_string (TYPE_PRECISION (wchar_type_ಗಂಟು)
				/ TYPE_PRECISION (char_type_ಗಂಟು),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  ಭಙ್ಗ;
        }
    }

  ವಿಕಲ್ಪ (type)
    {
    ಸ್ವಭಾವ:
    ಪಕ್ಷ CPP_STRING:
      ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ) = char_array_type_ಗಂಟು;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_UTF8STRING:
      ಯದಿ (flag_char8_t)
	ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ) = char8_array_type_ಗಂಟು;
      ಅನ್ಯಥಾ
	ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ) = char_array_type_ಗಂಟು;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_STRING16:
      ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ) = char16_array_type_ಗಂಟು;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_STRING32:
      ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ) = char32_array_type_ಗಂಟು;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_WSTRING:
      ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ) = wchar_array_type_ಗಂಟು;
    }
  ಮೌಲ್ಯ = fix_string_type (ಮೌಲ್ಯ);

  ಯದಿ (ಎಣಿಕೆ > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.ಮೌಲ್ಯ = ಮೌಲ್ಯ;
  ret.original_code = STRING_CST;
  ret.original_type = NULL_ವೃಕ್ಷ;
  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ret, get_range_from_loc (ಸಾಲು_table, loc));
  ret.m_decimal = 0;
  parser->seen_string_literal = ಸತ್ಯ;
  ಪ್ರತ್ಯಾಗಮ ret;
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

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (c_parser *parser, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ *after,
			 ವೃಕ್ಷ omp_atomic_lhs)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ lhs, rhs, ret;
  ಗಣನಾ ವೃಕ್ಷ_code code;
  location_t op_location, exp_location;
  ತಾರ್ಕಿಕ save_in_omp_for = c_in_omp_for;
  c_in_omp_for = ಅಸತ್ಯ;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_expression (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
    {
    ಪಕ್ಷ CPP_EQ:
      code = NOP_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_MULT_EQ:
      code = MULT_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_DIV_EQ:
      code = TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_MOD_EQ:
      code = TRUNC_MOD_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_PLUS_EQ:
      code = PLUS_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_MINUS_EQ:
      code = MINUS_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_LSHIFT_EQ:
      code = LSHIFT_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_RSHIFT_EQ:
      code = RSHIFT_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_AND_EQ:
      code = BIT_AND_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_XOR_EQ:
      code = BIT_XOR_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_OR_EQ:
      code = BIT_IOR_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      c_in_omp_for = save_in_omp_for;
      ಪ್ರತ್ಯಾಗಮ lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
  rhs = convert_lvalue_to_rvalue (exp_location, rhs, ಸತ್ಯ, ಸತ್ಯ);

  ret.ಮೌಲ್ಯ = build_modify_ಅಭಿವ್ಯಕ್ತಿ (op_location, lhs.ಮೌಲ್ಯ, lhs.original_type,
				 code, exp_location, rhs.ಮೌಲ್ಯ,
				 rhs.original_type);
  ret.m_decimal = 0;
  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  ಯದಿ (code == NOP_ಅಭಿವ್ಯಕ್ತಿ)
    ret.original_code = MODIFY_ಅಭಿವ್ಯಕ್ತಿ;
  ಅನ್ಯಥಾ
    {
      suppress_warning (ret.ಮೌಲ್ಯ, OPT_Wparentheses);
      ret.original_code = ERROR_MARK;
    }
  ret.original_type = ರಿಕ್ತ;
  c_in_omp_for = save_in_omp_for;
  ಪ್ರತ್ಯಾಗಮ ret;
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

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_conditional_expression (c_parser *parser, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ *after,
				 ವೃಕ್ಷ omp_atomic_lhs)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ cond, exp1, exp2, ret;
  location_t start, cond_loc, colon_loc;
  ತಾರ್ಕಿಕ save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_ದ್ವಿಮಾನ_expression (parser, after, omp_atomic_lhs);

  ಯದಿ (c_parser_next_token_is_not (parser, CPP_QUERY))
    ಪ್ರತ್ಯಾಗಮ cond;
  c_omp_array_section_p = ಅಸತ್ಯ;
  ಯದಿ (cond.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
    start = cond.get_start ();
  ಅನ್ಯಥಾ
    start = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_to_rvalue (cond_loc, cond, ಸತ್ಯ, ಸತ್ಯ);
  c_parser_consume_token (parser);
  ಯದಿ (c_parser_next_token_is (parser, CPP_COLON))
    {
      ವೃಕ್ಷ eptype = NULL_ವೃಕ್ಷ;

      location_t ಮಧ್ಯ_loc = c_parser_peek_token (parser)->location;
      pedwarn (ಮಧ್ಯ_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      ಯದಿ (ವೃಕ್ಷ_CODE (cond.ಮೌಲ್ಯ) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  eptype = ವೃಕ್ಷ_TYPE (cond.ಮೌಲ್ಯ);
	  cond.ಮೌಲ್ಯ = ವೃಕ್ಷ_OPERAND (cond.ಮೌಲ್ಯ, 0);
	}
      ವೃಕ್ಷ e = cond.ಮೌಲ್ಯ;
      ಯಾವತ್ (ವೃಕ್ಷ_CODE (e) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
	e = ವೃಕ್ಷ_OPERAND (e, 1);
      warn_for_omitted_condop (ಮಧ್ಯ_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.ಮೌಲ್ಯ = save_ಅಭಿವ್ಯಕ್ತಿ (default_conversion (cond.ಮೌಲ್ಯ));
      ಯದಿ (eptype)
	exp1.ಮೌಲ್ಯ = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, eptype, exp1.ಮೌಲ್ಯ);
      exp1.original_type = ರಿಕ್ತ;
      exp1.src_range = cond.src_range;
      cond.ಮೌಲ್ಯ = c_objc_common_truthvalue_conversion (cond_loc, exp1.ಮೌಲ್ಯ);
      c_inhibit_evaluation_warnings += cond.ಮೌಲ್ಯ == truthvalue_true_ಗಂಟು;
    }
  ಅನ್ಯಥಾ
    {
      cond.ಮೌಲ್ಯ
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.ಮೌಲ್ಯ));
      c_inhibit_evaluation_warnings += cond.ಮೌಲ್ಯ == truthvalue_false_ಗಂಟು;
      exp1 = c_parser_expression_conv (parser);
      mark_exp_read (exp1.ಮೌಲ್ಯ);
      c_inhibit_evaluation_warnings +=
	((cond.ಮೌಲ್ಯ == truthvalue_true_ಗಂಟು)
	 - (cond.ಮೌಲ್ಯ == truthvalue_false_ಗಂಟು));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.ಮೌಲ್ಯ == truthvalue_true_ಗಂಟು;
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = ರಿಕ್ತ;
      c_omp_array_section_p = save_c_omp_array_section_p;
      ಪ್ರತ್ಯಾಗಮ ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_expression (parser, ರಿಕ್ತ, NULL_ವೃಕ್ಷ);
    exp2 = convert_lvalue_to_rvalue (exp2_loc, exp2, ಸತ್ಯ, ಸತ್ಯ);
  }
  c_inhibit_evaluation_warnings -= cond.ಮೌಲ್ಯ == truthvalue_true_ಗಂಟು;
  location_t loc1 = make_location (exp1.get_start (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_start (), exp2.src_range);
  ಯದಿ (UNLIKELY (omp_atomic_lhs != ರಿಕ್ತ)
      && (ವೃಕ್ಷ_CODE (cond.ಮೌಲ್ಯ) == GT_ಅಭಿವ್ಯಕ್ತಿ
	  || ವೃಕ್ಷ_CODE (cond.ಮೌಲ್ಯ) == LT_ಅಭಿವ್ಯಕ್ತಿ
	  || ವೃಕ್ಷ_CODE (cond.ಮೌಲ್ಯ) == EQ_ಅಭಿವ್ಯಕ್ತಿ)
      && c_ವೃಕ್ಷ_equal (exp2.ಮೌಲ್ಯ, omp_atomic_lhs)
      && (c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (cond.ಮೌಲ್ಯ, 0), omp_atomic_lhs)
	  || c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (cond.ಮೌಲ್ಯ, 1), omp_atomic_lhs)))
    ret.ಮೌಲ್ಯ = build3_loc (colon_loc, COND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (omp_atomic_lhs),
			    cond.ಮೌಲ್ಯ, exp1.ಮೌಲ್ಯ, exp2.ಮೌಲ್ಯ);
  ಅನ್ಯಥಾ
    ret.ಮೌಲ್ಯ
      = build_conditional_ಅಭಿವ್ಯಕ್ತಿ (colon_loc, cond.ಮೌಲ್ಯ,
				cond.original_code == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ,
				exp1.ಮೌಲ್ಯ, exp1.original_type, loc1,
				exp2.ಮೌಲ್ಯ, exp2.original_type, loc2);
  ret.original_code = ERROR_MARK;
  ಯದಿ (exp1.ಮೌಲ್ಯ == error_mark_ಗಂಟು || exp2.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    ret.original_type = ರಿಕ್ತ;
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : ವೃಕ್ಷ_TYPE (exp1.ಮೌಲ್ಯ);
      t2 = exp2.original_type ? exp2.original_type : ವೃಕ್ಷ_TYPE (exp2.ಮೌಲ್ಯ);
      ret.original_type = ((t1 != error_mark_ಗಂಟು
			    && t2 != error_mark_ಗಂಟು
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : ರಿಕ್ತ);
    }
  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ret, start, exp2.get_finish ());
  ret.m_decimal = 0;
  c_omp_array_section_p = save_c_omp_array_section_p;
  ಪ್ರತ್ಯಾಗಮ ret;
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

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_ದ್ವಿಮಾನ_expression (c_parser *parser, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ *after,
			    ವೃಕ್ಷ omp_atomic_lhs)
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

  ಸಂರಚನಾ {
    /* The expression at this stack level.  */
    ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    ಗಣನಾ c_parser_prec prec;
    /* The operation on its left.  */
    ಗಣನಾ ವೃಕ್ಷ_code op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    ವೃಕ್ಷ sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    ವೃಕ್ಷ orig_ಅಭಿವ್ಯಕ್ತಿ;
  } ರಾಶಿ[ಅಂಕೆ_PRECS];
  ಪೂರ್ಣಾಙ್ಕ sp;
  /* Location of the binary operator.  */
  location_t ದ್ವಿಮಾನ_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#define ತೆಗೆ_2								      \
  ಕುರು {									      \
    ವಿಕಲ್ಪ (ರಾಶಿ[sp].op)						      \
      {									      \
      ಪಕ್ಷ TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ:						      \
	c_inhibit_evaluation_warnings -= (ರಾಶಿ[sp - 1].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ	      \
					  == truthvalue_false_ಗಂಟು);	      \
	ಭಙ್ಗ;								      \
      ಪಕ್ಷ TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ:						      \
	c_inhibit_evaluation_warnings -= (ರಾಶಿ[sp - 1].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ	      \
					  == truthvalue_true_ಗಂಟು);	      \
	ಭಙ್ಗ;								      \
      ಪಕ್ಷ TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ:						      \
	ಯದಿ ((ರಾಶಿ[sp - 1].ಅಭಿವ್ಯಕ್ತಿ.original_code == SIZEOF_ಅಭಿವ್ಯಕ್ತಿ		      \
	     || ರಾಶಿ[sp - 1].ಅಭಿವ್ಯಕ್ತಿ.original_code == PAREN_SIZEOF_ಅಭಿವ್ಯಕ್ತಿ)	      \
	    && (ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ.original_code == SIZEOF_ಅಭಿವ್ಯಕ್ತಿ		      \
		|| ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ.original_code == PAREN_SIZEOF_ಅಭಿವ್ಯಕ್ತಿ))	      \
	  {								      \
	    ವೃಕ್ಷ type0 = ರಾಶಿ[sp - 1].sizeof_arg;			      \
	    ವೃಕ್ಷ type1 = ರಾಶಿ[sp].sizeof_arg;				      \
	    ವೃಕ್ಷ first_arg = type0;					      \
	    ಯದಿ (!TYPE_P (type0))					      \
	      type0 = ವೃಕ್ಷ_TYPE (type0);				      \
	    ಯದಿ (!TYPE_P (type1))					      \
	      type1 = ವೃಕ್ಷ_TYPE (type1);				      \
	    ಯದಿ (POINTER_TYPE_P (type0)					      \
		&& comptypes (ವೃಕ್ಷ_TYPE (type0), type1)			      \
		&& !(ವೃಕ್ಷ_CODE (first_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (first_arg)			      \
		     && warn_sizeof_array_argument))			      \
	      {								      \
		auto_diagnostic_group d;				      \
		ಯದಿ (warning_at (ರಾಶಿ[sp].loc, OPT_Wsizeof_pointer_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  ಯದಿ (DECL_P (first_arg))				      \
		    inform (DECL_SOURCE_LOCATION (first_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (type0)))  \
		     && ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ.original_code != PAREN_SIZEOF_ಅಭಿವ್ಯಕ್ತಿ)    \
	      maybe_warn_sizeof_array_div (ರಾಶಿ[sp].loc, first_arg, type0,   \
					   ರಾಶಿ[sp].sizeof_arg, type1);      \
	  }								      \
	ಭಙ್ಗ;								      \
      ಸ್ವಭಾವ:								      \
	ಭಙ್ಗ;								      \
      }									      \
    ರಾಶಿ[sp - 1].ಅಭಿವ್ಯಕ್ತಿ							      \
      = convert_lvalue_to_rvalue (ರಾಶಿ[sp - 1].loc,			      \
				  ರಾಶಿ[sp - 1].ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಸತ್ಯ);	      \
    ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ							      \
      = convert_lvalue_to_rvalue (ರಾಶಿ[sp].loc,			      \
				  ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಸತ್ಯ);		      \
    ಯದಿ (UNLIKELY (omp_atomic_lhs != NULL_ವೃಕ್ಷ) && sp == 1		      \
	&& ((c_parser_next_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << ರಾಶಿ[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_SHIFT)		      \
		     | (1 << PREC_ADD) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_next_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_ಗಂಟು			      \
		     && c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (ರಾಶಿ[sp].prec == PREC_REL || ರಾಶಿ[sp].prec == PREC_EQ)))\
	&& ರಾಶಿ[sp].op != TRUNC_MOD_ಅಭಿವ್ಯಕ್ತಿ				      \
	&& ರಾಶಿ[sp].op != GE_ಅಭಿವ್ಯಕ್ತಿ					      \
	&& ರಾಶಿ[sp].op != LE_ಅಭಿವ್ಯಕ್ತಿ					      \
	&& ರಾಶಿ[sp].op != NE_ಅಭಿವ್ಯಕ್ತಿ					      \
	&& ರಾಶಿ[0].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ != error_mark_ಗಂಟು			      \
	&& ರಾಶಿ[1].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ != error_mark_ಗಂಟು			      \
	&& (omp_atomic_lhs == void_list_ಗಂಟು				      \
	    || c_ವೃಕ್ಷ_equal (ರಾಶಿ[0].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, omp_atomic_lhs)	      \
	    || c_ವೃಕ್ಷ_equal (ರಾಶಿ[1].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, omp_atomic_lhs)	      \
	    || (ರಾಶಿ[sp].op == EQ_ಅಭಿವ್ಯಕ್ತಿ					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	ವೃಕ್ಷ t = make_ಗಂಟು (ರಾಶಿ[1].op);				      \
	ವೃಕ್ಷ_TYPE (t) = ವೃಕ್ಷ_TYPE (ರಾಶಿ[0].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);		      \
	ವೃಕ್ಷ_OPERAND (t, 0) = ರಾಶಿ[0].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;			      \
	ವೃಕ್ಷ_OPERAND (t, 1) = ರಾಶಿ[1].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;			      \
	ರಾಶಿ[0].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = t;					      \
	ರಾಶಿ[0].ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;					      \
      }									      \
    ಅನ್ಯಥಾ								      \
      ರಾಶಿ[sp - 1].ಅಭಿವ್ಯಕ್ತಿ = parser_build_ದ್ವಿಮಾನ_op (ರಾಶಿ[sp].loc,	      \
						   ರಾಶಿ[sp].op,	      \
						   ರಾಶಿ[sp - 1].ಅಭಿವ್ಯಕ್ತಿ,	      \
						   ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ,	      \
						   ರಾಶಿ[sp - 1].orig_ಅಭಿವ್ಯಕ್ತಿ);  \
    ರಾಶಿ[sp - 1].orig_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;				      \
    sp--;								      \
  } ಯಾವತ್ (0)
  gcc_assert (!after || c_dialect_objc ());
  ರಾಶಿ[0].loc = c_parser_peek_token (parser)->location;
  ರಾಶಿ[0].ಅಭಿವ್ಯಕ್ತಿ = c_parser_cast_expression (parser, after);
  ರಾಶಿ[0].prec = PREC_NONE;
  ರಾಶಿ[0].sizeof_arg = c_last_sizeof_arg;
  ರಾಶಿ[0].orig_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  sp = 0;
  ಯಾವತ್ (ಸತ್ಯ)
    {
      ಗಣನಾ c_parser_prec oprec;
      ಗಣನಾ ವೃಕ್ಷ_code ocode;
      source_range src_range;
      ಯದಿ (parser->error)
	ಗಚ್ಛ out;
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
	{
	ಪಕ್ಷ CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_PLUS:
	  oprec = PREC_ADD;
	  ocode = PLUS_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_MINUS:
	  oprec = PREC_ADD;
	  ocode = MINUS_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_LSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = LSHIFT_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_RSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = RSHIFT_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = BIT_AND_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = BIT_XOR_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = BIT_IOR_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  ಗಚ್ಛ out;
	}
      ದ್ವಿಮಾನ_loc = c_parser_peek_token (parser)->location;
      ಯಾವತ್ (oprec <= ರಾಶಿ[sp].prec)
	ತೆಗೆ_2;
      c_parser_consume_token (parser);
      ವಿಕಲ್ಪ (ocode)
	{
	ಪಕ್ಷ TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ:
	  src_range = ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ.src_range;
	  ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ
	    = convert_lvalue_to_rvalue (ರಾಶಿ[sp].loc,
					ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಸತ್ಯ);
	  ರಾಶಿ[sp].orig_ಅಭಿವ್ಯಕ್ತಿ = ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
	  ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_objc_common_truthvalue_conversion
	    (ರಾಶಿ[sp].loc, default_conversion (ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ));
	  c_inhibit_evaluation_warnings += (ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ
					    == truthvalue_false_ಗಂಟು);
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ, src_range);
	  ಭಙ್ಗ;
	ಪಕ್ಷ TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ:
	  src_range = ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ.src_range;
	  ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ
	    = convert_lvalue_to_rvalue (ರಾಶಿ[sp].loc,
					ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಸತ್ಯ);
	  ರಾಶಿ[sp].orig_ಅಭಿವ್ಯಕ್ತಿ = ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
	  ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_objc_common_truthvalue_conversion
	    (ರಾಶಿ[sp].loc, default_conversion (ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ));
	  c_inhibit_evaluation_warnings += (ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ
					    == truthvalue_true_ಗಂಟು);
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ, src_range);
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  ಭಙ್ಗ;
	}
      sp++;
      ರಾಶಿ[sp].loc = ದ್ವಿಮಾನ_loc;
      ರಾಶಿ[sp].ಅಭಿವ್ಯಕ್ತಿ = c_parser_cast_expression (parser, ರಿಕ್ತ);
      ರಾಶಿ[sp].prec = oprec;
      ರಾಶಿ[sp].op = ocode;
      ರಾಶಿ[sp].sizeof_arg = c_last_sizeof_arg;
      ರಾಶಿ[sp].orig_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
    }
 out:
  ಯಾವತ್ (sp > 0)
    ತೆಗೆ_2;
  ಪ್ರತ್ಯಾಗಮ ರಾಶಿ[0].ಅಭಿವ್ಯಕ್ತಿ;
#undef ತೆಗೆ_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

ಸ್ಥಿರ ಸಂರಚನಾ c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  ತಾರ್ಕಿಕ seen_scspec = ಅಸತ್ಯ;
  ಸಂರಚನಾ c_declspecs *specs = build_null_declspecs ();
  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->keyword)
	{
	ಪಕ್ಷ RID_CONSTEXPR:
	ಪಕ್ಷ RID_REGISTER:
	ಪಕ್ಷ RID_STATIC:
	ಪಕ್ಷ RID_THREAD:
	  seen_scspec = ಸತ್ಯ;
	  declspecs_add_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	  c_parser_consume_token (parser);
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  ಗಚ್ಛ out;
	}
    }
 out:
  ಪ್ರತ್ಯಾಗಮ seen_scspec ? specs : ರಿಕ್ತ;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_cast_expression (c_parser *parser, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  ಯದಿ (after)
    ಪ್ರತ್ಯಾಗಮ c_parser_postfix_expression_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      ಸಂರಚನಾ c_declspecs *scspecs;
      ಸಂರಚನಾ c_type_name *type_name;
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, ಸತ್ಯ);
      parens.skip_until_found_close (parser);
      ಯದಿ (type_name == ರಿಕ್ತ)
	{
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = ರಿಕ್ತ;
	  ಪ್ರತ್ಯಾಗಮ ret;
	}

      /* Save casted types in the function's used types hash table.  */
      used_types_ಸೇರಿಸು (type_name->specs->type);

      ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	ಪ್ರತ್ಯಾಗಮ c_parser_postfix_expression_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      ಯದಿ (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      ಯದಿ (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
	ಅಭಿವ್ಯಕ್ತಿ = c_parser_cast_expression (parser, ರಿಕ್ತ);
	ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಸತ್ಯ);
      }
      ret.ಮೌಲ್ಯ = c_cast_ಅಭಿವ್ಯಕ್ತಿ (cast_loc, type_name, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
      ಯದಿ (ret.ಮೌಲ್ಯ && ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ)
	set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ret, cast_loc, ಅಭಿವ್ಯಕ್ತಿ.get_finish ());
      ret.original_code = ERROR_MARK;
      ret.original_type = ರಿಕ್ತ;
      ret.m_decimal = 0;
      ಪ್ರತ್ಯಾಗಮ ret;
    }
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ c_parser_unary_expression (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

ಸ್ಥಿರ ಶೂನ್ಯ
mark_exp_read_cond (ವೃಕ್ಷ exp)
{
  ಯದಿ ((VAR_P (exp) || ವೃಕ್ಷ_CODE (exp) == PARM_DECL)
      && (VAR_P (exp) ? warn_unused_but_set_variable
		      : warn_unused_but_set_parameter) > 1)
    ಪ್ರತ್ಯಾಗಮ;

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

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_unary_expression (c_parser *parser)
{
  ಪೂರ್ಣಾಙ್ಕ ext;
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t exp_loc;
  location_t finish;
  ret.original_code = ERROR_MARK;
  ret.original_type = ರಿಕ್ತ;
  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
    {
    ಪಕ್ಷ CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ರಿಕ್ತ);
      mark_exp_read_cond (op.ಮೌಲ್ಯ);
      op = default_function_array_conversion (exp_loc, op);
      ಪ್ರತ್ಯಾಗಮ parser_build_unary_op (op_loc, PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಪಕ್ಷ CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ರಿಕ್ತ);
      mark_exp_read_cond (op.ಮೌಲ್ಯ);
      op = default_function_array_conversion (exp_loc, op);
      ಪ್ರತ್ಯಾಗಮ parser_build_unary_op (op_loc, PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಪಕ್ಷ CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, ರಿಕ್ತ);
      mark_exp_read (op.ಮೌಲ್ಯ);
      ಪ್ರತ್ಯಾಗಮ parser_build_unary_op (op_loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಪಕ್ಷ CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_expression (parser, ರಿಕ್ತ);
	finish = op.get_finish ();
	op = convert_lvalue_to_rvalue (exp_loc, op, ಸತ್ಯ, ಸತ್ಯ);
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.ಮೌಲ್ಯ = build_indirect_ref (combined_loc, op.ಮೌಲ್ಯ, RO_UNARY_STAR);
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ret.m_decimal = 0;
	ಪ್ರತ್ಯಾಗಮ ret;
      }
    ಪಕ್ಷ CPP_PLUS:
      ಯದಿ (!c_dialect_objc () && !in_system_header_at (ಒಳಹರಿವು_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ರಿಕ್ತ);
      op = convert_lvalue_to_rvalue (exp_loc, op, ಸತ್ಯ, ಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ parser_build_unary_op (op_loc, CONVERT_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಪಕ್ಷ CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ರಿಕ್ತ);
      op = convert_lvalue_to_rvalue (exp_loc, op, ಸತ್ಯ, ಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ parser_build_unary_op (op_loc, NEGATE_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಪಕ್ಷ CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ರಿಕ್ತ);
      op = convert_lvalue_to_rvalue (exp_loc, op, ಸತ್ಯ, ಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ parser_build_unary_op (op_loc, BIT_NOT_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಪಕ್ಷ CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ರಿಕ್ತ);
      op = convert_lvalue_to_rvalue (exp_loc, op, ಸತ್ಯ, ಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ parser_build_unary_op (op_loc, TRUTH_NOT_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಪಕ್ಷ CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ret.ಮೌಲ್ಯ = finish_label_address_ಅಭಿವ್ಯಕ್ತಿ
	    (c_parser_peek_token (parser)->ಮೌಲ್ಯ, op_loc);
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_finish ());
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ
	{
	  c_parser_error (parser, "expected identifier");
	  ret.set_error ();
	}
      ಪ್ರತ್ಯಾಗಮ ret;
    ಪಕ್ಷ CPP_KEYWORD:
      {
	ಗಣನಾ rid rid = c_parser_peek_token (parser)->keyword;
	ವಿಕಲ್ಪ (rid)
	  {
	  ಪಕ್ಷ RID_COUNTOF:
	  ಪಕ್ಷ RID_SIZEOF:
	    ಪ್ರತ್ಯಾಗಮ c_parser_sizeof_or_countof_expression (parser, rid);
	  ಪಕ್ಷ RID_ALIGNOF:
	    ಪ್ರತ್ಯಾಗಮ c_parser_alignof_expression (parser);
	  ಪಕ್ಷ RID_MAXOF:
	  ಪಕ್ಷ RID_MINOF:
	    ಪ್ರತ್ಯಾಗಮ c_parser_maxof_or_minof_expression (parser, rid);
	  ಪಕ್ಷ RID_BUILTIN_HAS_ATTRIBUTE:
	    ಪ್ರತ್ಯಾಗಮ c_parser_has_attribute_expression (parser);
	  ಪಕ್ಷ RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_expression (parser, ರಿಕ್ತ);
	    restore_extension_diagnostics (ext);
	    ಪ್ರತ್ಯಾಗಮ ret;
	  ಪಕ್ಷ RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, ರಿಕ್ತ);
	    op = default_function_array_conversion (exp_loc, op);
	    ಪ್ರತ್ಯಾಗಮ parser_build_unary_op (op_loc, REALPART_ಅಭಿವ್ಯಕ್ತಿ, op);
	  ಪಕ್ಷ RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, ರಿಕ್ತ);
	    op = default_function_array_conversion (exp_loc, op);
	    ಪ್ರತ್ಯಾಗಮ parser_build_unary_op (op_loc, IMAGPART_ಅಭಿವ್ಯಕ್ತಿ, op);
	  ಪಕ್ಷ RID_TRANSACTION_ATOMIC:
	  ಪಕ್ಷ RID_TRANSACTION_RELAXED:
	    ಪ್ರತ್ಯಾಗಮ c_parser_transaction_expression (parser, rid);
	  ಪಕ್ಷ RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.ಮೌಲ್ಯ = void_ಗಂಟು;
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    ಪ್ರತ್ಯಾಗಮ ret;
	  ಸ್ವಭಾವ:
	    ಪ್ರತ್ಯಾಗಮ c_parser_postfix_expression (parser);
	  }
      }
    ಸ್ವಭಾವ:
      ಪ್ರತ್ಯಾಗಮ c_parser_postfix_expression (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_sizeof_or_countof_expression (c_parser *parser, ಗಣನಾ rid rid)
{
  ಧ್ರುವ ವರ್ಣ *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ result;
  location_t ಅಭಿವ್ಯಕ್ತಿ_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  ಯದಿ (rid == RID_COUNTOF)
    pedwarn_c23 (start, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  ಯದಿ (rid == RID_COUNTOF)
    in_countof++;
  ಅನ್ಯಥಾ
    in_sizeof++;
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      ಸಂರಚನಾ c_declspecs *scspecs;
      ಸಂರಚನಾ c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, ಸತ್ಯ);
      parens.skip_until_found_close (parser);
      finish = parser->tokens_buf[0].location;
      ಯದಿ (type_name == ರಿಕ್ತ)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  ಅಭಿವ್ಯಕ್ತಿ.set_error ();
	  ಗಚ್ಛ Xof_ಅಭಿವ್ಯಕ್ತಿ;
	}
      ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  ಅಭಿವ್ಯಕ್ತಿ = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       ಅಭಿವ್ಯಕ್ತಿ_loc);
	  finish = ಅಭಿವ್ಯಕ್ತಿ.get_finish ();
	  ಗಚ್ಛ Xof_ಅಭಿವ್ಯಕ್ತಿ;
	}
      /* sizeof ( type-name ).  */
      ಯದಿ (scspecs)
	error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, "storage class specifier in %qs", op_name);
      ಯದಿ (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      ಯದಿ (rid == RID_COUNTOF)
	{
	  in_countof--;
	  result = c_ಅಭಿವ್ಯಕ್ತಿ_countof_type (ಅಭಿವ್ಯಕ್ತಿ_loc, type_name);
	}
      ಅನ್ಯಥಾ
	{
	  in_sizeof--;
	  result = c_ಅಭಿವ್ಯಕ್ತಿ_sizeof_type (ಅಭಿವ್ಯಕ್ತಿ_loc, type_name);
	}
    }
  ಅನ್ಯಥಾ
    {
      ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_unary_expression (parser);
      finish = ಅಭಿವ್ಯಕ್ತಿ.get_finish ();
    Xof_ಅಭಿವ್ಯಕ್ತಿ:
      c_inhibit_evaluation_warnings--;
      ಯದಿ (rid == RID_COUNTOF)
	in_countof--;
      ಅನ್ಯಥಾ
	in_sizeof--;
      mark_exp_read (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
      ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 1)))
	error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, "%qs applied to a bit-field", op_name);
      ಯದಿ (rid == RID_COUNTOF)
	result = c_ಅಭಿವ್ಯಕ್ತಿ_countof_ಅಭಿವ್ಯಕ್ತಿ (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ);
      ಅನ್ಯಥಾ
	result = c_ಅಭಿವ್ಯಕ್ತಿ_sizeof_ಅಭಿವ್ಯಕ್ತಿ (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ);
    }
  ಯದಿ (finish == UNKNOWN_LOCATION)
    finish = start;
  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&result, start, finish);
  ಪ್ರತ್ಯಾಗಮ result;
}

/* Parse an alignof expression.  */

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_alignof_expression (c_parser *parser)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  location_t start_loc = c_parser_peek_token (parser)->location;
  location_t end_loc;
  ವೃಕ್ಷ alignof_spelling = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNOF));
  ತಾರ್ಕಿಕ is_c11_alignof = (strcmp (IDENTIFIER_POINTER (alignof_spelling),
				"_Alignof") == 0
			 || strcmp (IDENTIFIER_POINTER (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  ಯದಿ (is_c11_alignof)
    {
      ಯದಿ (flag_isoc99)
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      ಅನ್ಯಥಾ
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_alignof++;
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      ಸಂರಚನಾ c_declspecs *scspecs;
      ಸಂರಚನಾ c_type_name *type_name;
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, ಸತ್ಯ);
      end_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
      ಯದಿ (type_name == ರಿಕ್ತ)
	{
	  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
	  c_inhibit_evaluation_warnings--;
	  in_alignof--;
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = ರಿಕ್ತ;
	  ಪ್ರತ್ಯಾಗಮ ret;
	}
      ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  ಅಭಿವ್ಯಕ್ತಿ = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  ಗಚ್ಛ alignof_ಅಭಿವ್ಯಕ್ತಿ;
	}
      /* alignof ( type-name ).  */
      ಯದಿ (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      ಯದಿ (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      ret.ಮೌಲ್ಯ = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       ರಿಕ್ತ, ರಿಕ್ತ),
					    ಅಸತ್ಯ, is_c11_alignof, 1);
      ret.original_code = ERROR_MARK;
      ret.original_type = ರಿಕ್ತ;
      set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      ಪ್ರತ್ಯಾಗಮ ret;
    }
  ಅನ್ಯಥಾ
    {
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_unary_expression (parser);
      end_loc = ಅಭಿವ್ಯಕ್ತಿ.src_range.m_finish;
    alignof_ಅಭಿವ್ಯಕ್ತಿ:
      mark_exp_read (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      ಯದಿ (is_c11_alignof)
	pedwarn (start_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.ಮೌಲ್ಯ = c_alignof_ಅಭಿವ್ಯಕ್ತಿ (start_loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
      ret.original_code = ERROR_MARK;
      ret.original_type = ರಿಕ್ತ;
      set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      ಪ್ರತ್ಯಾಗಮ ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_maxof_or_minof_expression (c_parser *parser, ಗಣನಾ rid rid)
{
  ಧ್ರುವ ವರ್ಣ *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ result;
  location_t ಅಭಿವ್ಯಕ್ತಿ_loc;
  ಸಂರಚನಾ c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  pedwarn (start, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  ಯದಿ (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      ಗಚ್ಛ fail;
    }
  parens.consume_open (parser);
  ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
  ಯದಿ (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_found_close (parser);
      ಗಚ್ಛ fail;
    }
  type_name = c_parser_type_name (parser, ಸತ್ಯ);
  ಯದಿ (type_name == ರಿಕ್ತ)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_found_close (parser);
      ಗಚ್ಛ fail;
    }
  parens.skip_until_found_close (parser);
  finish = parser->tokens_buf[0].location;
  ಯದಿ (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  ಯದಿ (rid == RID_MAXOF)
    result = c_ಅಭಿವ್ಯಕ್ತಿ_maxof_type (ಅಭಿವ್ಯಕ್ತಿ_loc, type_name);
  ಅನ್ಯಥಾ
    result = c_ಅಭಿವ್ಯಕ್ತಿ_minof_type (ಅಭಿವ್ಯಕ್ತಿ_loc, type_name);
  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&result, start, finish);
  ಪ್ರತ್ಯಾಗಮ result;
fail:
  c_inhibit_evaluation_warnings--;
  result.set_error ();
  result.original_code = ERROR_MARK;
  result.original_type = ರಿಕ್ತ;
  ಪ್ರತ್ಯಾಗಮ result;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_has_attribute_expression (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t start = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;

      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ result;
      result.set_error ();
      result.original_code = ERROR_MARK;
      result.original_type = ರಿಕ್ತ;
      ಪ್ರತ್ಯಾಗಮ result;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  in_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  ವೃಕ್ಷ oper = NULL_ವೃಕ್ಷ;
  ಯದಿ (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      ಸಂರಚನಾ c_type_name *tname = c_parser_type_name (parser);
      in_typeof--;
      ಯದಿ (tname)
	{
	  oper = groktypename (tname, ರಿಕ್ತ, ರಿಕ್ತ);
	  ತೆಗೆ_maybe_used (c_type_variably_modified_p (oper));
	}
    }
  ಅನ್ಯಥಾ
    {
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ cexpr = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      ಯದಿ (cexpr.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
	{
	  mark_exp_read (cexpr.ಮೌಲ್ಯ);
	  oper = cexpr.ಮೌಲ್ಯ;
	  ವೃಕ್ಷ etype = ವೃಕ್ಷ_TYPE (oper);
	  ತಾರ್ಕಿಕ was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  ಯದಿ (was_vm)
	    oper = c_fully_fold (oper, ಅಸತ್ಯ, ರಿಕ್ತ);
	  ತೆಗೆ_maybe_used (was_vm);
	}
    }

  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ result;
  result.original_code = ERROR_MARK;
  result.original_type = ರಿಕ್ತ;

  ಯದಿ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      result.set_error ();
      ಪ್ರತ್ಯಾಗಮ result;
    }

  ತಾರ್ಕಿಕ save_translate_strings_p = parser->translate_strings_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  ವೃಕ್ಷ attr = c_parser_gnu_attribute (parser, NULL_ವೃಕ್ಷ, ಅಸತ್ಯ, ಅಸತ್ಯ);

  parser->translate_strings_p = save_translate_strings_p;

  location_t finish = c_parser_peek_token (parser)->location;
  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  ಅನ್ಯಥಾ
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);

      result.set_error ();
      ಪ್ರತ್ಯಾಗಮ result;
    }

  ಯದಿ (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      result.set_error ();
      ಪ್ರತ್ಯಾಗಮ result;
    }

  result.original_code = INTEGER_CST;
  result.original_type = boolean_type_ಗಂಟು;

  ಯದಿ (has_attribute (atloc, oper, attr, default_conversion))
    result.ಮೌಲ್ಯ = boolean_true_ಗಂಟು;
  ಅನ್ಯಥಾ
    result.ಮೌಲ್ಯ =  boolean_false_ಗಂಟು;

  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&result, start, finish);
  result.m_decimal = 0;
  ಪ್ರತ್ಯಾಗಮ result;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_get_builtin_args (c_parser *parser, ಧ್ರುವ ವರ್ಣ *bname,
			   vec<c_ಅಭಿವ್ಯಕ್ತಿ_t, va_gc> **ret_cexpr_list,
			   ತಾರ್ಕಿಕ choose_ಅಭಿವ್ಯಕ್ತಿ_p,
			   location_t *out_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_ಅಭಿವ್ಯಕ್ತಿ_t, va_gc> *cexpr_list;
  c_ಅಭಿವ್ಯಕ್ತಿ_t ಅಭಿವ್ಯಕ್ತಿ;
  ತಾರ್ಕಿಕ saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = ರಿಕ್ತ;
  ಯದಿ (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  c_parser_consume_token (parser);

  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      *out_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= choose_ಅಭಿವ್ಯಕ್ತಿ_p;
  ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_safe_ತಳ್ಳು (cexpr_list, ಅಭಿವ್ಯಕ್ತಿ);
  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  ವೃಕ್ಷ ಮೌಲ್ಯ = embed->ಮೌಲ್ಯ;
	  ಅಭಿವ್ಯಕ್ತಿ.original_code = INTEGER_CST;
	  ಅಭಿವ್ಯಕ್ತಿ.original_type = integer_type_ಗಂಟು;
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, embed->get_range ());
	  ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	  ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ i = 0; i < (unsigned) RAW_DATA_LENGTH (ಮೌಲ್ಯ); i++)
	    {
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_int_cst (integer_type_ಗಂಟು,
					  RAW_DATA_UCHAR_ELT (ಮೌಲ್ಯ, i));
	      vec_safe_ತಳ್ಳು (cexpr_list, ಅಭಿವ್ಯಕ್ತಿ);
	    }
	  c_parser_consume_token (parser);
	  ಅನುವರ್ತ;
	}
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      vec_safe_ತಳ್ಳು (cexpr_list, ಅಭಿವ್ಯಕ್ತಿ);
    }

  *out_close_paren_loc = c_parser_peek_token (parser)->location;
  ಯದಿ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  *ret_cexpr_list = cexpr_list;
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* This represents a single generic-association.  */

ಸಂರಚನಾ c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  ವೃಕ್ಷ type;
  /* The association's expression.  */
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ expression;
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

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_generic_selection (c_parser *parser)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ selector, error_ಅಭಿವ್ಯಕ್ತಿ;
  ವೃಕ್ಷ selector_type;
  ಸಂರಚನಾ c_generic_association matched_assoc;
  ಪೂರ್ಣಾಙ್ಕ match_found = -1;
  location_t generic_loc, selector_loc;

  error_ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
  error_ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
  error_ಅಭಿವ್ಯಕ್ತಿ.set_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_ವೃಕ್ಷ;
  matched_assoc.expression = error_ಅಭಿವ್ಯಕ್ತಿ;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_GENERIC));
  generic_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  ಯದಿ (flag_isoc99)
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C99 does not support %<_Generic%>");
  ಅನ್ಯಥಾ
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C90 does not support %<_Generic%>");

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ error_ಅಭಿವ್ಯಕ್ತಿ;

  selector_loc = c_parser_peek_token (parser)->location;
  ಯದಿ (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      c_inhibit_evaluation_warnings++;
      pedwarn_c23 (selector_loc, OPT_Wpedantic,
		   "ISO C does not support use of type name as %<_Generic%> "
		   "controlling operand before C2Y");
      ಸಂರಚನಾ c_type_name *type = c_parser_type_name (parser);
      ಯದಿ (type)
	selector_type = groktypename (type, ರಿಕ್ತ, ರಿಕ್ತ);
      c_inhibit_evaluation_warnings--;
      ಯದಿ (!type)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
	  ಪ್ರತ್ಯಾಗಮ error_ಅಭಿವ್ಯಕ್ತಿ;
	}
    }
  ಅನ್ಯಥಾ
    {
      c_inhibit_evaluation_warnings++;
      in_generic++;
      selector = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      in_generic--;
      ತೆಗೆ_maybe_used (!flag_isoc23);

      ಯದಿ (selector.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
	  ಪ್ರತ್ಯಾಗಮ selector;
	}
      mark_exp_read (selector.ಮೌಲ್ಯ);
      selector_type = ವೃಕ್ಷ_TYPE (selector.ಮೌಲ್ಯ);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      ಯದಿ (FUNCTION_POINTER_TYPE_P (selector_type)
	  && TYPE_QUALS (ವೃಕ್ಷ_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_pointer_type (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (selector_type)));
    }

  ಯದಿ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
      ಪ್ರತ್ಯಾಗಮ error_ಅಭಿವ್ಯಕ್ತಿ;
    }

  auto_vec<c_generic_association> associations;
  ಸಂರಚನಾ maybe_used_decl *maybe_used_default = ರಿಕ್ತ;
  ಯಾವತ್ (1)
    {
      ಸಂರಚನಾ c_generic_association assoc, *iter;
      unsigned ಪೂರ್ಣಾಙ್ಕ ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      ಯದಿ (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_ವೃಕ್ಷ;
	}
      ಅನ್ಯಥಾ
	{
	  ಸಂರಚನಾ c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  ಯದಿ (type_name == ರಿಕ್ತ)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
	      ಪ್ರತ್ಯಾಗಮ error_ಅಭಿವ್ಯಕ್ತಿ;
	    }
	  assoc.type = grokgenassoc (type_name);
	  ಯದಿ (assoc.type == error_mark_ಗಂಟು)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
	      ಪ್ರತ್ಯಾಗಮ error_ಅಭಿವ್ಯಕ್ತಿ;
	    }

	  ಯದಿ (ವೃಕ್ಷ_CODE (assoc.type) == FUNCTION_TYPE)
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "function type before C2Y");
	  ಅನ್ಯಥಾ ಯದಿ (!COMPLETE_TYPE_P (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "incomplete type before C2Y");

	  ಯದಿ (c_type_variably_modified_p (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "variably-modified type before C2Y");
	}

      ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
	  ಪ್ರತ್ಯಾಗಮ error_ಅಭಿವ್ಯಕ್ತಿ;
	}

      ತಾರ್ಕಿಕ match = assoc.type == NULL_ವೃಕ್ಷ
		   || comptypes (assoc.type, selector_type);

      ಯದಿ (!match || matched_assoc.type != NULL_ವೃಕ್ಷ)
	c_inhibit_evaluation_warnings++;
      in_generic++;

      assoc.expression = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);

      ಯದಿ (!match || matched_assoc.type != NULL_ವೃಕ್ಷ)
	c_inhibit_evaluation_warnings--;
      in_generic--;
      ಯದಿ (!match)
	ತೆಗೆ_maybe_used (!flag_isoc23);
      ಅನ್ಯಥಾ ಯದಿ (assoc.type == NULL_ವೃಕ್ಷ)
	maybe_used_default = save_maybe_used ();
      ಅನ್ಯಥಾ
	ತೆಗೆ_maybe_used (ಸತ್ಯ);

      ಯದಿ (assoc.expression.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
	  ಪ್ರತ್ಯಾಗಮ error_ಅಭಿವ್ಯಕ್ತಿ;
	}

      ಪ್ರತಿ (ix = 0; associations.iterate (ix, &iter); ++ix)
	{
	  ಯದಿ (assoc.type == NULL_ವೃಕ್ಷ)
	    {
	      ಯದಿ (iter->type == NULL_ವೃಕ್ಷ)
		{
		  error_at (assoc.type_location,
			    "duplicate %<default%> case in %<_Generic%>");
		  inform (iter->type_location, "original %<default%> is here");
		}
	    }
	  ಅನ್ಯಥಾ ಯದಿ (iter->type != NULL_ವೃಕ್ಷ)
	    {
	      ಯದಿ (comptypes (assoc.type, iter->type))
		{
		  error_at (assoc.type_location,
			    "%<_Generic%> specifies two compatible types");
		  inform (iter->type_location, "compatible type is here");
		}
	    }
	}

      ಯದಿ (assoc.type == NULL_ವೃಕ್ಷ)
	{
	  ಯದಿ (match_found < 0)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (match)
	{
	  ಯದಿ (match_found < 0 || matched_assoc.type == NULL_ವೃಕ್ಷ)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	  ಅನ್ಯಥಾ
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.safe_ತಳ್ಳು (assoc);

      ಯದಿ (c_parser_peek_token (parser)->type != CPP_COMMA)
	ಭಙ್ಗ;
      c_parser_consume_token (parser);
    }

  ಯದಿ (match_found >= 0 && matched_assoc.type == NULL_ವೃಕ್ಷ)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_used (maybe_used_default);
      ತೆಗೆ_maybe_used (ಸತ್ಯ);
    }
  ಅನ್ಯಥಾ ಯದಿ (maybe_used_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_used (maybe_used_default);
      ತೆಗೆ_maybe_used (!flag_isoc23);
    }

  unsigned ಪೂರ್ಣಾಙ್ಕ ix;
  ಸಂರಚನಾ c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    ಯದಿ (ix != (unsigned) match_found)
      mark_exp_read (iter->expression.ಮೌಲ್ಯ);

  ಯದಿ (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
      ಪ್ರತ್ಯಾಗಮ error_ಅಭಿವ್ಯಕ್ತಿ;
    }

  ಯದಿ (match_found < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      ಪ್ರತ್ಯಾಗಮ error_ಅಭಿವ್ಯಕ್ತಿ;
    }

  ಪ್ರತ್ಯಾಗಮ matched_assoc.expression;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

ಸ್ಥಿರ unsigned ಪೂರ್ಣಾಙ್ಕ
check_tgmath_function (c_ಅಭಿವ್ಯಕ್ತಿ *ಅಭಿವ್ಯಕ್ತಿ, unsigned ಪೂರ್ಣಾಙ್ಕ pos)
{
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ->ಮೌಲ್ಯ);
  ಯದಿ (!FUNCTION_POINTER_TYPE_P (type))
    {
      error_at (ಅಭಿವ್ಯಕ್ತಿ->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      ಪ್ರತ್ಯಾಗಮ 0;
    }
  type = ವೃಕ್ಷ_TYPE (type);
  ಯದಿ (!prototype_p (type))
    {
      error_at (ಅಭಿವ್ಯಕ್ತಿ->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      ಪ್ರತ್ಯಾಗಮ 0;
    }
  ಯದಿ (stdarg_p (type))
    {
      error_at (ಅಭಿವ್ಯಕ್ತಿ->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      ಪ್ರತ್ಯಾಗಮ 0;
    }
  unsigned ಪೂರ್ಣಾಙ್ಕ nargs = 0;
  function_args_iterator iter;
  ವೃಕ್ಷ t;
  FOREACH_FUNCTION_ARGS (type, t, iter)
    {
      ಯದಿ (t == void_type_ಗಂಟು)
	ಭಙ್ಗ;
      nargs++;
    }
  ಯದಿ (nargs == 0)
    {
      error_at (ಅಭಿವ್ಯಕ್ತಿ->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      ಪ್ರತ್ಯಾಗಮ 0;
    }
  ಪ್ರತ್ಯಾಗಮ nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
ಗಣನಾ tgmath_parm_kind
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_predefined_identifier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->keyword)
    {
    ಪಕ್ಷ RID_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__FUNCTION__");
      ಭಙ್ಗ;
    ಪಕ್ಷ RID_PRETTY_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__PRETTY_FUNCTION__");
      ಭಙ್ಗ;
    ಪಕ್ಷ RID_C99_FUNCTION_NAME:
      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support "
		   "%<__func__%> predefined identifier");
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }

  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
  ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->ಮೌಲ್ಯ);
  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, loc);
  ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
  c_parser_consume_token (parser);
  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
has_counted_by_object (ವೃಕ್ಷ ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  ಯದಿ ((ವೃಕ್ಷ_CODE (ref) == INDIRECT_REF
       && is_access_with_size_p (ವೃಕ್ಷ_OPERAND (ref, 0)))
      || is_access_with_size_p (ref))
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* Get the reference to the counted-by object associated with the REF.  */

ಸ್ಥಿರ ವೃಕ್ಷ
get_counted_by_ref (ವೃಕ್ಷ ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (ref) == INDIRECT_REF
      && is_access_with_size_p (ವೃಕ್ಷ_OPERAND (ref, 0)))
    ಪ್ರತ್ಯಾಗಮ CALL_ಅಭಿವ್ಯಕ್ತಿ_ARG (ವೃಕ್ಷ_OPERAND (ref, 0), 1);
  ಅನ್ಯಥಾ ಯದಿ (is_access_with_size_p (ref))
    ಪ್ರತ್ಯಾಗಮ CALL_ಅಭಿವ್ಯಕ್ತಿ_ARG (ref, 1);

  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
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

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_postfix_expression (c_parser *parser)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ, e1;
  ಸಂರಚನಾ c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
  ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
  ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
    {
    ಪಕ್ಷ CPP_ಸಂಖ್ಯೆ:
      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
      loc = c_parser_peek_token (parser)->location;
      ಅಭಿವ್ಯಕ್ತಿ.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == FIXED_CST
	  && !targetm.fixed_point_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  ಅಭಿವ್ಯಕ್ತಿ.set_error ();
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_CHAR:
    ಪಕ್ಷ CPP_CHAR16:
    ಪಕ್ಷ CPP_CHAR32:
    ಪಕ್ಷ CPP_UTF8CHAR:
    ಪಕ್ಷ CPP_WCHAR:
      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      ಅಭಿವ್ಯಕ್ತಿ.original_type = char_type_ಗಂಟು;
      set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
      c_parser_consume_token (parser);
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_STRING:
    ಪಕ್ಷ CPP_STRING16:
    ಪಕ್ಷ CPP_STRING32:
    ಪಕ್ಷ CPP_WSTRING:
    ಪಕ್ಷ CPP_UTF8STRING:
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_string_literal (parser, parser->translate_strings_p,
				      ಸತ್ಯ);
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ
	= objc_build_string_object (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
      c_parser_consume_token (parser);
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_NAME:
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->id_kind)
	{
	ಪಕ್ಷ C_ID_ID:
	  {
	    ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	    c_parser_consume_token (parser);
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &ಅಭಿವ್ಯಕ್ತಿ.original_type);
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    ವೃಕ್ಷ class_name = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	    ವೃಕ್ಷ component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    ಯದಿ (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->ಮೌಲ್ಯ;
	    location_t end_loc = component_tok->get_finish ();
	    c_parser_consume_token (parser);
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = objc_build_class_component_ref (class_name,
							 component);
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, end_loc);
	    ಭಙ್ಗ;
	  }
	ಸ್ವಭಾವ:
	  c_parser_error (parser, "expected expression");
	  ಅಭಿವ್ಯಕ್ತಿ.set_error ();
	  ಭಙ್ಗ;
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_OPEN_PAREN:
      /* A parenthesized expression, statement expression or compound
	 literal.  */
      ಯದಿ (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_BRACE)
	{
	  /* A statement expression.  */
	  ವೃಕ್ಷ stmt;
	  location_t brace_loc;
	  ತಾರ್ಕಿಕ save_c_omp_array_section_p = c_omp_array_section_p;
	  c_parser_consume_token (parser);
	  brace_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* If we've not yet started the current function's statement list,
	     or we're in the parameter scope of an old-style function
	     declaration, statement expressions are not allowed.  */
	  ಯದಿ (!building_stmt_list_p () || old_style_parameter_scope ())
	    {
	      error_at (loc, "braced-group within expression allowed "
			"only inside a function");
	      parser->error = ಸತ್ಯ;
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ರಿಕ್ತ);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
	      ಅಭಿವ್ಯಕ್ತಿ.set_error ();
	      ಭಙ್ಗ;
	    }
	  c_omp_array_section_p = ಅಸತ್ಯ;
	  stmt = c_begin_stmt_ಅಭಿವ್ಯಕ್ತಿ ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_finish_stmt_ಅಭಿವ್ಯಕ್ತಿ (brace_loc, stmt);
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_loc);
	  mark_exp_read (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      ಅನ್ಯಥಾ
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  ಅಭಿವ್ಯಕ್ತಿ = c_parser_expression (parser);
	  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == MODIFY_ಅಭಿವ್ಯಕ್ತಿ)
	    suppress_warning (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, OPT_Wparentheses);
	  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.original_code != C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ
	      && ಅಭಿವ್ಯಕ್ತಿ.original_code != SIZEOF_ಅಭಿವ್ಯಕ್ತಿ)
	    ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.original_code == SIZEOF_ಅಭಿವ್ಯಕ್ತಿ)
	    ಅಭಿವ್ಯಕ್ತಿ.original_code = PAREN_SIZEOF_ಅಭಿವ್ಯಕ್ತಿ;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_KEYWORD:
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->keyword)
	{
	ಪಕ್ಷ RID_FUNCTION_NAME:
	ಪಕ್ಷ RID_PRETTY_FUNCTION_NAME:
	ಪಕ್ಷ RID_C99_FUNCTION_NAME:
	  ಅಭಿವ್ಯಕ್ತಿ = c_parser_predefined_identifier (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_VA_ARG:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ಯದಿ (!parens.require_open (parser))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    e1 = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	    mark_exp_read (e1.ಮೌಲ್ಯ);
	    e1.ಮೌಲ್ಯ = c_fully_fold (e1.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
	    ಯದಿ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ಯದಿ (t1 == ರಿಕ್ತ)
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
	      }
	    ಅನ್ಯಥಾ
	      {
		ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
		ವೃಕ್ಷ type = groktypename (t1, &type_ಅಭಿವ್ಯಕ್ತಿ, ರಿಕ್ತ);
		ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_build_va_arg (start_loc, e1.ಮೌಲ್ಯ, loc,
					     type, type_ಅಭಿವ್ಯಕ್ತಿ);
		set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, start_loc, end_loc);
	      }
	  }
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_C23_VA_START:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ಯದಿ (!parens.require_open (parser))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    e1 = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	    e1 = convert_lvalue_to_rvalue (e1.get_location (), e1, ಸತ್ಯ, ಸತ್ಯ);
	    ಯದಿ (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		ಯದಿ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
		    ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		    ಭಙ್ಗ;
		  }
		ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_kind == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    ವೃಕ್ಷ name = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    ವೃಕ್ಷ decl = lookup_name (name);
		    ವೃಕ್ಷ last_parm
		      = ವೃಕ್ಷ_last (DECL_ARGUMENTS (current_function_decl));
		    ಯದಿ (!last_parm || decl != last_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    ಅನ್ಯಥಾ ಯದಿ (DECL_REGISTER (decl))
		      warning_at (nloc, OPT_Wvarargs,
				  "undefined behavior when second parameter "
				  "of %<va_start%> is declared with "
				  "%<register%> storage");
		    c_parser_consume_token (parser);
		  }
		ಅನ್ಯಥಾ
		  {
		    unsigned nesting_depth = 0;
		    location_t sloc = c_parser_peek_token (parser)->location;
		    location_t eloc = sloc;

		    /* For va_start (ap,) the ) comes from stdarg.h.
		       Use location of , in that case, otherwise without
		       -Wsystem-headers nothing is reported.  After all,
		       the problematic token is the comma in that case.  */
		    ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    ಯಾವತ್ (ಸತ್ಯ)
		      {
			c_token *token = c_parser_peek_token (parser);
			ಯದಿ (token->type == CPP_CLOSE_PAREN && !nesting_depth)
			  ಭಙ್ಗ;

			ಯದಿ (token->type == CPP_EOF)
			  ಭಙ್ಗ;
			ಯದಿ (token->type == CPP_OPEN_PAREN)
			  ++nesting_depth;
			ಅನ್ಯಥಾ ಯದಿ (token->type == CPP_CLOSE_PAREN)
			  --nesting_depth;
			eloc = token->location;
			c_parser_consume_token (parser);
		      }
		    ಯದಿ (sloc != eloc)
		      sloc = make_location (sloc, sloc, eloc);
		    warning_at (sloc, OPT_Wvarargs,
				"%<va_start%> macro used with additional "
				"arguments other than identifier of the "
				"last named argument");
		  }
	      }
	    parens.skip_until_found_close (parser);
	    ವೃಕ್ಷ fndecl = builtin_decl_explicit (BUILT_IN_VA_START);
	    vec<ವೃಕ್ಷ, va_gc> *params;
	    vec_alloc (params, 2);
	    params->quick_ತಳ್ಳು (e1.ಮೌಲ್ಯ);
	    params->quick_ತಳ್ಳು (integer_zero_ಗಂಟು);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.quick_ತಳ್ಳು (e1.get_location ());
	    arg_loc.quick_ತಳ್ಳು (UNKNOWN_LOCATION);
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, ರಿಕ್ತ);
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc,
				     parser->tokens_buf[0].get_finish ());
	    ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	    ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
	    ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	    release_ವೃಕ್ಷ_vector (params);
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ಯದಿ (!parens.require_open (parser))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    t1 = c_parser_type_name (parser);
	    ಯದಿ (t1 == ರಿಕ್ತ)
	      parser->error = ಸತ್ಯ;
	    ಯದಿ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    ಯದಿ (parser->error)
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ವೃಕ್ಷ type = groktypename (t1, ರಿಕ್ತ, ರಿಕ್ತ);
	    ವೃಕ್ಷ offsetof_ref;
	    ಯದಿ (type == error_mark_ಗಂಟು)
	      offsetof_ref = error_mark_ಗಂಟು;
	    ಅನ್ಯಥಾ
	      {
		offsetof_ref = build1 (INDIRECT_REF, type, null_pointer_ಗಂಟು);
		SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->ಮೌಲ್ಯ,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		ಯಾವತ್ (c_parser_next_token_is (parser, CPP_DOT)
		       || c_parser_next_token_is (parser,
						  CPP_OPEN_SQUARE)
		       || c_parser_next_token_is (parser,
						  CPP_DEREF))
		  {
		    ಯದಿ (c_parser_next_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_ಗಂಟು);
			ಗಚ್ಛ do_dot;
		      }
		    ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			ಯದಿ (c_parser_next_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    ಭಙ್ಗ;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->ಮೌಲ್ಯ,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    ಅನ್ಯಥಾ
		      {
			ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ce;
			ವೃಕ್ಷ idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_expression (parser);
			ce = convert_lvalue_to_rvalue (loc, ce, ಅಸತ್ಯ, ಅಸತ್ಯ);
			idx = ce.ಮೌಲ್ಯ;
			idx = c_fully_fold (idx, ಅಸತ್ಯ, ರಿಕ್ತ);
			c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
						   "expected %<]%>");
			offsetof_ref = build_array_ref (loc, offsetof_ref, idx);
		      }
		  }
	      }
	    ಅನ್ಯಥಾ
	      c_parser_error (parser, "expected identifier");
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = fold_offsetof (offsetof_ref);
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, end_loc);
	  }
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_CHOOSE_ಅಭಿವ್ಯಕ್ತಿ:
	  {
	    vec<c_ಅಭಿವ್ಯಕ್ತಿ_t, va_gc> *cexpr_list;
	    c_ಅಭಿವ್ಯಕ್ತಿ_t *e1_p, *e2_p, *e3_p;
	    ವೃಕ್ಷ c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ಯದಿ (!c_parser_get_builtin_args (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, ಸತ್ಯ,
					    &close_paren_loc))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    ಯದಿ (vec_safe_length (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->ಮೌಲ್ಯ;
	    mark_exp_read (e2_p->ಮೌಲ್ಯ);
	    mark_exp_read (e3_p->ಮೌಲ್ಯ);
	    ಯದಿ (ವೃಕ್ಷ_CODE (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_expression_warning (c);
	    ಅಭಿವ್ಯಕ್ತಿ = integer_zerop (c) ? *e3_p : *e2_p;
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_paren_loc);
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ಯದಿ (!parens.require_open (parser))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    t1 = c_parser_type_name (parser);
	    ಯದಿ (t1 == ರಿಕ್ತ)
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    t2 = c_parser_type_name (parser);
	    ಯದಿ (t2 == ರಿಕ್ತ)
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    ವೃಕ್ಷ e1, e2;
	    e1 = groktypename (t1, ರಿಕ್ತ, ರಿಕ್ತ);
	    e2 = groktypename (t2, ರಿಕ್ತ, ರಿಕ್ತ);
	    ಯದಿ (e1 == error_mark_ಗಂಟು || e2 == error_mark_ಗಂಟು)
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ
	      = comptypes (e1, e2) ? integer_one_ಗಂಟು : integer_zero_ಗಂಟು;
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_paren_loc);
	  }
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_BUILTIN_TGMATH:
	  {
	    vec<c_ಅಭಿವ್ಯಕ್ತಿ_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ಯದಿ (!c_parser_get_builtin_args (parser,
					    "__builtin_tgmath",
					    &cexpr_list, ಅಸತ್ಯ,
					    &close_paren_loc))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    ಯದಿ (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    unsigned ಪೂರ್ಣಾಙ್ಕ i;
	    c_ಅಭಿವ್ಯಕ್ತಿ_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, ಸತ್ಯ, ಸತ್ಯ);
	    unsigned ಪೂರ್ಣಾಙ್ಕ nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    ಯದಿ (nargs == 0)
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (vec_safe_length (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    unsigned ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_functions = vec_safe_length (cexpr_list) - nargs;
	    ಯದಿ (ಅಂಕೆ_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ j = 1; j < ಅಂಕೆ_functions; j++)
	      {
		unsigned ಪೂರ್ಣಾಙ್ಕ this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		ಯದಿ (this_nargs == 0)
		  {
		    ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		    ಗಚ್ಛ out;
		  }
		ಯದಿ (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		    ಗಚ್ಛ out;
		  }
	      }

	    /* The functions all have the same number of arguments.
	       Determine whether arguments and return types vary in
	       ways permitted for <tgmath.h> functions.  */
	    /* The first entry in each of these vectors is for the
	       return type, subsequent entries for parameter
	       types.  */
	    auto_vec<ಗಣನಾ tgmath_parm_kind> parm_kind (nargs + 1);
	    auto_vec<ವೃಕ್ಷ> parm_first (nargs + 1);
	    auto_vec<ತಾರ್ಕಿಕ> parm_complex (nargs + 1);
	    auto_vec<ತಾರ್ಕಿಕ> parm_varies (nargs + 1);
	    ವೃಕ್ಷ first_type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE ((*cexpr_list)[0].ಮೌಲ್ಯ));
	    ವೃಕ್ಷ first_ret = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (first_type));
	    parm_first.quick_ತಳ್ಳು (first_ret);
	    parm_complex.quick_ತಳ್ಳು (ವೃಕ್ಷ_CODE (first_ret) == COMPLEX_TYPE);
	    parm_varies.quick_ತಳ್ಳು (ಅಸತ್ಯ);
	    function_args_iterator iter;
	    ವೃಕ್ಷ t;
	    unsigned ಪೂರ್ಣಾಙ್ಕ argpos;
	    FOREACH_FUNCTION_ARGS (first_type, t, iter)
	      {
		ಯದಿ (t == void_type_ಗಂಟು)
		  ಭಙ್ಗ;
		parm_first.quick_ತಳ್ಳು (TYPE_MAIN_VARIANT (t));
		parm_complex.quick_ತಳ್ಳು (ವೃಕ್ಷ_CODE (t) == COMPLEX_TYPE);
		parm_varies.quick_ತಳ್ಳು (ಅಸತ್ಯ);
	      }
	    ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ j = 1; j < ಅಂಕೆ_functions; j++)
	      {
		ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE ((*cexpr_list)[j].ಮೌಲ್ಯ));
		ವೃಕ್ಷ ret = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (type));
		ಯದಿ (ret != parm_first[0])
		  {
		    parm_varies[0] = ಸತ್ಯ;
		    ಯದಿ (!SCALAR_FLOAT_TYPE_P (parm_first[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_first[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			ಅಭಿವ್ಯಕ್ತಿ.set_error ();
			ಗಚ್ಛ out;
		      }
		    ಯದಿ (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			ಅಭಿವ್ಯಕ್ತಿ.set_error ();
			ಗಚ್ಛ out;
		      }
		  }
		ಯದಿ (ವೃಕ್ಷ_CODE (ret) == COMPLEX_TYPE)
		  parm_complex[0] = ಸತ್ಯ;
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    ಯದಿ (t == void_type_ಗಂಟು)
		      ಭಙ್ಗ;
		    t = TYPE_MAIN_VARIANT (t);
		    ಯದಿ (t != parm_first[argpos])
		      {
			parm_varies[argpos] = ಸತ್ಯ;
			ಯದಿ (!SCALAR_FLOAT_TYPE_P (parm_first[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_first[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    ಅಭಿವ್ಯಕ್ತಿ.set_error ();
			    ಗಚ್ಛ out;
			  }
			ಯದಿ (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    ಅಭಿವ್ಯಕ್ತಿ.set_error ();
			    ಗಚ್ಛ out;
			  }
		      }
		    ಯದಿ (ವೃಕ್ಷ_CODE (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = ಸತ್ಯ;
		    argpos++;
		  }
	      }
	    ಗಣನಾ tgmath_parm_kind max_variation = tgmath_fixed;
	    ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ j = 0; j <= nargs; j++)
	      {
		ಗಣನಾ tgmath_parm_kind this_kind;
		ಯದಿ (parm_varies[j])
		  {
		    ಯದಿ (parm_complex[j])
		      max_variation = this_kind = tgmath_complex;
		    ಅನ್ಯಥಾ
		      {
			this_kind = tgmath_real;
			ಯದಿ (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		ಅನ್ಯಥಾ
		  this_kind = tgmath_fixed;
		parm_kind.quick_ತಳ್ಳು (this_kind);
	      }
	    ಯದಿ (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    unsigned ಪೂರ್ಣಾಙ್ಕ tgarg = 0;
	    ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ j = 1; j <= nargs; j++)
	      ಯದಿ (parm_kind[j] == max_variation)
		{
		  tgarg = j;
		  ಭಙ್ಗ;
		}
	    ಯದಿ (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<ವೃಕ್ಷ> tg_type (ಅಂಕೆ_functions);
	    ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ j = 0; j < ಅಂಕೆ_functions; j++)
	      {
		ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE ((*cexpr_list)[j].ಮೌಲ್ಯ));
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    ಯದಿ (argpos == tgarg)
		      {
			tg_type.quick_ತಳ್ಳು (TYPE_MAIN_VARIANT (t));
			ಭಙ್ಗ;
		      }
		    argpos++;
		  }
	      }

	    /* Verify that the corresponding types are different for
	       all the listed functions.  Also determine whether all
	       the types are complex, whether all the types are
	       standard or binary, and whether all the types are
	       decimal.  */
	    ತಾರ್ಕಿಕ all_complex = ಸತ್ಯ;
	    ತಾರ್ಕಿಕ all_ದ್ವಿಮಾನ = ಸತ್ಯ;
	    ತಾರ್ಕಿಕ all_decimal = ಸತ್ಯ;
	    hash_set<ವೃಕ್ಷ> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		ಯದಿ (ವೃಕ್ಷ_CODE (t) == COMPLEX_TYPE)
		  all_decimal = ಅಸತ್ಯ;
		ಅನ್ಯಥಾ
		  {
		    all_complex = ಅಸತ್ಯ;
		    ಯದಿ (DECIMAL_FLOAT_TYPE_P (t))
		      all_ದ್ವಿಮಾನ = ಅಸತ್ಯ;
		    ಅನ್ಯಥಾ
		      all_decimal = ಅಸತ್ಯ;
		  }
		ಯದಿ (tg_types.add (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		    ಗಚ್ಛ out;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ j = 0; j < ಅಂಕೆ_functions; j++)
	      {
		ವೃಕ್ಷ exp_type = tg_type[j];
		ವೃಕ್ಷ exp_real_type = exp_type;
		ಯದಿ (ವೃಕ್ಷ_CODE (exp_type) == COMPLEX_TYPE)
		  exp_real_type = ವೃಕ್ಷ_TYPE (exp_type);
		ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE ((*cexpr_list)[j].ಮೌಲ್ಯ));
		ವೃಕ್ಷ ret = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (type));
		ಯದಿ ((parm_kind[0] == tgmath_complex && ret != exp_type)
		    || (parm_kind[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		    ಗಚ್ಛ out;
		  }
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    ಯದಿ (t == void_type_ಗಂಟು)
		      ಭಙ್ಗ;
		    t = TYPE_MAIN_VARIANT (t);
		    ಯದಿ ((parm_kind[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_kind[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			ಅಭಿವ್ಯಕ್ತಿ.set_error ();
			ಗಚ್ಛ out;
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
	    ತಾರ್ಕಿಕ arg_complex = all_complex;
	    ತಾರ್ಕಿಕ arg_ದ್ವಿಮಾನ = all_ದ್ವಿಮಾನ;
	    ತಾರ್ಕಿಕ arg_int_decimal = all_decimal;
	    ತಾರ್ಕಿಕ arg_int_floatnx = ಅಸತ್ಯ;
	    ತಾರ್ಕಿಕ arg_int_decimalx = ಅಸತ್ಯ;
	    ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ j = 1; j <= nargs; j++)
	      {
		ಯದಿ (parm_kind[j] == tgmath_fixed)
		  ಅನುವರ್ತ;
		c_ಅಭಿವ್ಯಕ್ತಿ_t *ce = &(*cexpr_list)[ಅಂಕೆ_functions + j - 1];
		ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ce->ಮೌಲ್ಯ);
		ಯದಿ (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && ವೃಕ್ಷ_CODE (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		    ಗಚ್ಛ out;
		  }
		ಯದಿ (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = ಸತ್ಯ;
		    ಯದಿ (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			ಅಭಿವ್ಯಕ್ತಿ.set_error ();
			ಗಚ್ಛ out;
		      }
		    ಅನ್ಯಥಾ ಯದಿ (all_ದ್ವಿಮಾನ)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			ಅಭಿವ್ಯಕ್ತಿ.set_error ();
			ಗಚ್ಛ out;
		      }
		    ಅನ್ಯಥಾ ಯದಿ (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			ಅಭಿವ್ಯಕ್ತಿ.set_error ();
			ಗಚ್ಛ out;
		      }
		    ಅನ್ಯಥಾ ಯದಿ (arg_ದ್ವಿಮಾನ)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			ಅಭಿವ್ಯಕ್ತಿ.set_error ();
			ಗಚ್ಛ out;
		      }
		  }
		ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == COMPLEX_TYPE)
		  {
		    arg_complex = ಸತ್ಯ;
		    ಯದಿ (COMPLEX_FLOAT_TYPE_P (type))
		      arg_ದ್ವಿಮಾನ = ಸತ್ಯ;
		    ಯದಿ (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			ಅಭಿವ್ಯಕ್ತಿ.set_error ();
			ಗಚ್ಛ out;
		      }
		    ಅನ್ಯಥಾ ಯದಿ (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			ಅಭಿವ್ಯಕ್ತಿ.set_error ();
			ಗಚ್ಛ out;
		      }
		  }
		ಅನ್ಯಥಾ ಯದಿ (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_ದ್ವಿಮಾನ = ಸತ್ಯ;
		    ಯದಿ (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			ಅಭಿವ್ಯಕ್ತಿ.set_error ();
			ಗಚ್ಛ out;
		      }
		    ಅನ್ಯಥಾ ಯದಿ (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			ಅಭಿವ್ಯಕ್ತಿ.set_error ();
			ಗಚ್ಛ out;
		      }
		  }
		ವೃಕ್ಷ rtype = TYPE_MAIN_VARIANT (type);
		ಯದಿ (ವೃಕ್ಷ_CODE (rtype) == COMPLEX_TYPE)
		  rtype = ವೃಕ್ಷ_TYPE (rtype);
		ಯದಿ (SCALAR_FLOAT_TYPE_P (rtype))
		  ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ j = 0; j < ಅಂಕೆ_FLOATNX_TYPES; j++)
		    ಯದಿ (rtype == FLOATNX_TYPE_ಗಂಟು (j))
		      {
			arg_int_floatnx = ಸತ್ಯ;
			ಭಙ್ಗ;
		      }
		ಯದಿ (rtype == dfloat64x_type_ಗಂಟು)
		  arg_int_decimalx = ಸತ್ಯ;
	      }
	    ವೃಕ್ಷ arg_real = NULL_ವೃಕ್ಷ;
	    ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ j = 1; j <= nargs; j++)
	      {
		ಯದಿ (parm_kind[j] == tgmath_fixed)
		  ಅನುವರ್ತ;
		c_ಅಭಿವ್ಯಕ್ತಿ_t *ce = &(*cexpr_list)[ಅಂಕೆ_functions + j - 1];
		ವೃಕ್ಷ type = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ce->ಮೌಲ್ಯ));
		ಯದಿ (ವೃಕ್ಷ_CODE (type) == COMPLEX_TYPE)
		  type = ವೃಕ್ಷ_TYPE (type);
		ಯದಿ (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_ಗಂಟು
			  : arg_int_floatnx
			  ? float32x_type_ಗಂಟು
			  : arg_int_decimal
			  ? dfloat64_type_ಗಂಟು
			  : double_type_ಗಂಟು);
		ಯದಿ (arg_real == NULL_ವೃಕ್ಷ)
		  arg_real = type;
		ಅನ್ಯಥಾ
		  arg_real = common_type (arg_real, type);
		ಯದಿ (arg_real == error_mark_ಗಂಟು)
		  {
		    ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		    ಗಚ್ಛ out;
		  }
	      }
	    ವೃಕ್ಷ arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_ಅಭಿವ್ಯಕ್ತಿ_t *fn = ರಿಕ್ತ;
	    ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ j = 0; j < ಅಂಕೆ_functions; j++)
	      {
		ಯದಿ (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    ಭಙ್ಗ;
		  }
	      }
	    ಯದಿ (fn == ರಿಕ್ತ
		&& parm_kind[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_first[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ j = 0; j < ಅಂಕೆ_functions; j++)
		  {
		    ಯದಿ (arg_complex
			!= (ವೃಕ್ಷ_CODE (tg_type[j]) == COMPLEX_TYPE))
		      ಅನುವರ್ತ;
		    ವೃಕ್ಷ real_tg_type = (arg_complex
					 ? ವೃಕ್ಷ_TYPE (tg_type[j])
					 : tg_type[j]);
		    ಯದಿ (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      ಅನುವರ್ತ;
		    scalar_float_mode arg_mode
		      = SCALAR_FLOAT_TYPE_MODE (arg_real);
		    scalar_float_mode tg_mode
		      = SCALAR_FLOAT_TYPE_MODE (real_tg_type);
		    ಧ್ರುವ real_format *arg_fmt = REAL_MODE_FORMAT (arg_mode);
		    ಧ್ರುವ real_format *tg_fmt = REAL_MODE_FORMAT (tg_mode);
		    ಯದಿ (arg_fmt->b == tg_fmt->b
			&& arg_fmt->p <= tg_fmt->p
			&& arg_fmt->emax <= tg_fmt->emax
			&& (arg_fmt->emin - arg_fmt->p
			    >= tg_fmt->emin - tg_fmt->p))
		      {
			fn = &(*cexpr_list)[j];
			ಭಙ್ಗ;
		      }
		  }
	      }
	    ಯದಿ (fn == ರಿಕ್ತ)
	      {
		error_at (loc, "no matching function for type-generic call");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    /* Construct a call to FN.  */
	    vec<ವೃಕ್ಷ, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<ವೃಕ್ಷ, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ j = 0; j < nargs; j++)
	      {
		c_ಅಭಿವ್ಯಕ್ತಿ_t *ce = &(*cexpr_list)[ಅಂಕೆ_functions + j];
		args->quick_ತಳ್ಳು (ce->ಮೌಲ್ಯ);
		arg_loc.quick_ತಳ್ಳು (ce->get_location ());
		origtypes->quick_ತಳ್ಳು (ce->original_type);
	      }
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_build_function_call_vec (loc, arg_loc, fn->ಮೌಲ್ಯ,
						    args, origtypes);
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_paren_loc);
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_ಅಭಿವ್ಯಕ್ತಿ_t, va_gc> *cexpr_list;
	    c_ಅಭಿವ್ಯಕ್ತಿ_t *e2_p;
	    ವೃಕ್ಷ chain_ಮೌಲ್ಯ;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ಯದಿ (!c_parser_get_builtin_args (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, ಅಸತ್ಯ,
					    &close_paren_loc))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    ಅಭಿವ್ಯಕ್ತಿ = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, ಸತ್ಯ, ಸತ್ಯ);
	    chain_ಮೌಲ್ಯ = e2_p->ಮೌಲ್ಯ;
	    mark_exp_read (chain_ಮೌಲ್ಯ);

	    ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) != CALL_ಅಭಿವ್ಯಕ್ತಿ)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (chain_ಮೌಲ್ಯ)) != POINTER_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    ಅನ್ಯಥಾ
	      CALL_ಅಭಿವ್ಯಕ್ತಿ_STATIC_CHAIN (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) = chain_ಮೌಲ್ಯ;
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_paren_loc);
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ RID_BUILTIN_COMPLEX:
	  {
	    vec<c_ಅಭಿವ್ಯಕ್ತಿ_t, va_gc> *cexpr_list;
	    c_ಅಭಿವ್ಯಕ್ತಿ_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ಯದಿ (!c_parser_get_builtin_args (parser,
					    "__builtin_complex",
					    &cexpr_list, ಅಸತ್ಯ,
					    &close_paren_loc))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    ಯದಿ (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_to_rvalue (loc, *e1_p, ಸತ್ಯ, ಸತ್ಯ);
	    ಯದಿ (ವೃಕ್ಷ_CODE (e1_p->ಮೌಲ್ಯ) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	      e1_p->ಮೌಲ್ಯ = convert (ವೃಕ್ಷ_TYPE (e1_p->ಮೌಲ್ಯ),
				     ವೃಕ್ಷ_OPERAND (e1_p->ಮೌಲ್ಯ, 0));
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, ಸತ್ಯ, ಸತ್ಯ);
	    ಯದಿ (ವೃಕ್ಷ_CODE (e2_p->ಮೌಲ್ಯ) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	      e2_p->ಮೌಲ್ಯ = convert (ವೃಕ್ಷ_TYPE (e2_p->ಮೌಲ್ಯ),
				     ವೃಕ್ಷ_OPERAND (e2_p->ಮೌಲ್ಯ, 0));
	    ಯದಿ (!SCALAR_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (e1_p->ಮೌಲ್ಯ))
		|| DECIMAL_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (e1_p->ಮೌಲ್ಯ))
		|| !SCALAR_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (e2_p->ಮೌಲ್ಯ))
		|| DECIMAL_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (e2_p->ಮೌಲ್ಯ)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (e1_p->ಮೌಲ್ಯ))
		!= TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (e2_p->ಮೌಲ್ಯ)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build2_loc (loc, COMPLEX_ಅಭಿವ್ಯಕ್ತಿ,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (ವೃಕ್ಷ_TYPE (e1_p->ಮೌಲ್ಯ))),
				     e1_p->ಮೌಲ್ಯ, e2_p->ಮೌಲ್ಯ);
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_paren_loc);
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_ಅಭಿವ್ಯಕ್ತಿ_t, va_gc> *cexpr_list;
	    c_ಅಭಿವ್ಯಕ್ತಿ_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ಯದಿ (!c_parser_get_builtin_args (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, ಅಸತ್ಯ,
					    &close_paren_loc))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    e_p = &(*cexpr_list)[0];
	    ವೃಕ್ಷ ref = e_p->ಮೌಲ್ಯ;

	    ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ref)) != ARRAY_TYPE
		 && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ref)) != POINTER_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    ಯದಿ (ವೃಕ್ಷ_CODE (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    ಯದಿ (ವೃಕ್ಷ_CODE (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    ಯದಿ (has_counted_by_object (ref))
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = get_counted_by_ref (ref);
	    ಅನ್ಯಥಾ
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = null_pointer_ಗಂಟು;

	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_paren_loc);
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_ಅಭಿವ್ಯಕ್ತಿ_t, va_gc> *cexpr_list;
	    unsigned ಪೂರ್ಣಾಙ್ಕ i;
	    c_ಅಭಿವ್ಯಕ್ತಿ_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ಯದಿ (!c_parser_get_builtin_args (parser,
					    "__builtin_shuffle",
					    &cexpr_list, ಅಸತ್ಯ,
					    &close_paren_loc))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, ಸತ್ಯ, ಸತ್ಯ);

	    ಯದಿ (vec_safe_length (cexpr_list) == 2)
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_build_vec_perm_ಅಭಿವ್ಯಕ್ತಿ (loc, (*cexpr_list)[0].ಮೌಲ್ಯ,
						  NULL_ವೃಕ್ಷ,
						  (*cexpr_list)[1].ಮೌಲ್ಯ);

	    ಅನ್ಯಥಾ ಯದಿ (vec_safe_length (cexpr_list) == 3)
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_build_vec_perm_ಅಭಿವ್ಯಕ್ತಿ (loc, (*cexpr_list)[0].ಮೌಲ್ಯ,
						  (*cexpr_list)[1].ಮೌಲ್ಯ,
						  (*cexpr_list)[2].ಮೌಲ್ಯ);
	    ಅನ್ಯಥಾ
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
	      }
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_paren_loc);
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_ಅಭಿವ್ಯಕ್ತಿ_t, va_gc> *cexpr_list;
	    unsigned ಪೂರ್ಣಾಙ್ಕ i;
	    c_ಅಭಿವ್ಯಕ್ತಿ_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ಯದಿ (!c_parser_get_builtin_args (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, ಅಸತ್ಯ,
					    &close_paren_loc))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, ಸತ್ಯ, ಸತ್ಯ);

	    ಯದಿ (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
	      }
	    ಅನ್ಯಥಾ
	      {
		auto_vec<ವೃಕ್ಷ, 16> mask;
		ಪ್ರತಿ (i = 2; i < cexpr_list->length (); ++i)
		  mask.safe_ತಳ್ಳು ((*cexpr_list)[i].ಮೌಲ್ಯ);
		ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_build_shufflevector (loc, (*cexpr_list)[0].ಮೌಲ್ಯ,
						    (*cexpr_list)[1].ಮೌಲ್ಯ,
						    mask);
	      }
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_paren_loc);
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ಯದಿ (!parens.require_open (parser))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    e1 = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	    mark_exp_read (e1.ಮೌಲ್ಯ);
	    ಯದಿ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ಯದಿ (t1 == ರಿಕ್ತ)
	      ಅಭಿವ್ಯಕ್ತಿ.set_error ();
	    ಅನ್ಯಥಾ
	      {
		ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
		ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_build_vec_convert (start_loc, e1.ಮೌಲ್ಯ, loc,
						  groktypename (t1, &type_ಅಭಿವ್ಯಕ್ತಿ,
								ರಿಕ್ತ));
		set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, start_loc, end_loc);
	      }
	  }
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ಯದಿ (!parens.require_open (parser))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    e1 = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	    mark_exp_read (e1.ಮೌಲ್ಯ);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    parens.skip_until_found_close (parser);
	    ಅಭಿವ್ಯಕ್ತಿ = parser_build_unary_op (loc, PAREN_ಅಭಿವ್ಯಕ್ತಿ, e1);
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, start_loc, end_loc);
	  }
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_BUILTIN_STDC:
	  {
	    vec<c_ಅಭಿವ್ಯಕ್ತಿ_t, va_gc> *cexpr_list;
	    c_ಅಭಿವ್ಯಕ್ತಿ_t *arg_p;
	    location_t close_paren_loc;
	    ಗಣನಾ c_builtin_stdc {
	      C_BUILTIN_STDC_BIT_CEIL,
	      C_BUILTIN_STDC_BIT_FLOOR,
	      C_BUILTIN_STDC_BIT_WIDTH,
	      C_BUILTIN_STDC_ಎಣಿಕೆ_ONES,
	      C_BUILTIN_STDC_ಎಣಿಕೆ_ZEROS,
	      C_BUILTIN_STDC_FIRST_LEADING_ONE,
	      C_BUILTIN_STDC_FIRST_LEADING_ZERO,
	      C_BUILTIN_STDC_FIRST_TRAILING_ONE,
	      C_BUILTIN_STDC_FIRST_TRAILING_ZERO,
	      C_BUILTIN_STDC_HAS_SINGLE_BIT,
	      C_BUILTIN_STDC_LEADING_ONES,
	      C_BUILTIN_STDC_LEADING_ZEROS,
	      C_BUILTIN_STDC_ROTATE_ಎಡ,
	      C_BUILTIN_STDC_ROTATE_ಬಲ,
	      C_BUILTIN_STDC_TRAILING_ONES,
	      C_BUILTIN_STDC_TRAILING_ZEROS,
	      C_BUILTIN_STDC_MAX
	    } stdc_rid = C_BUILTIN_STDC_MAX;
	    ಧ್ರುವ ವರ್ಣ *name
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	    unsigned ಅಂಕೆ_args = 1;
	    ವಿಕಲ್ಪ (name[ಪರಿಮಾಣ ("__builtin_stdc_") - 1])
	      {
	      ಪಕ್ಷ 'b':
		ವಿಕಲ್ಪ (name[ಪರಿಮಾಣ ("__builtin_stdc_bit_") - 1])
		  {
		  ಪಕ್ಷ 'c':
		    stdc_rid = C_BUILTIN_STDC_BIT_CEIL;
		    ಭಙ್ಗ;
		  ಪಕ್ಷ 'f':
		    stdc_rid = C_BUILTIN_STDC_BIT_FLOOR;
		    ಭಙ್ಗ;
		  ಸ್ವಭಾವ:
		    stdc_rid = C_BUILTIN_STDC_BIT_WIDTH;
		    ಭಙ್ಗ;
		  }
		ಭಙ್ಗ;
	      ಪಕ್ಷ 'c':
		ಯದಿ (name[ಪರಿಮಾಣ ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_ಎಣಿಕೆ_ONES;
		ಅನ್ಯಥಾ
		  stdc_rid = C_BUILTIN_STDC_ಎಣಿಕೆ_ZEROS;
		ಭಙ್ಗ;
	      ಪಕ್ಷ 'f':
		ವಿಕಲ್ಪ (name[ಪರಿಮಾಣ ("__builtin_stdc_first_trailing_") - 1])
		  {
		  ಪಕ್ಷ 'n':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ONE;
		    ಭಙ್ಗ;
		  ಪಕ್ಷ 'e':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ZERO;
		    ಭಙ್ಗ;
		  ಪಕ್ಷ 'o':
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ONE;
		    ಭಙ್ಗ;
		  ಸ್ವಭಾವ:
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ZERO;
		    ಭಙ್ಗ;
		  }
		ಭಙ್ಗ;
	      ಪಕ್ಷ 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_BIT;
		ಭಙ್ಗ;
	      ಪಕ್ಷ 'l':
		ಯದಿ (name[ಪರಿಮಾಣ ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		ಅನ್ಯಥಾ
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		ಭಙ್ಗ;
	      ಪಕ್ಷ 'r':
		ಯದಿ (name[ಪರಿಮಾಣ ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_ಎಡ;
		ಅನ್ಯಥಾ
		  stdc_rid = C_BUILTIN_STDC_ROTATE_ಬಲ;
		ಅಂಕೆ_args = 2;
		ಭಙ್ಗ;
	      ಪಕ್ಷ 't':
		ಯದಿ (name[ಪರಿಮಾಣ ("__builtin_stdc_trailing_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ONES;
		ಅನ್ಯಥಾ
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ZEROS;
		ಭಙ್ಗ;
	      }
	    gcc_checking_assert (stdc_rid != C_BUILTIN_STDC_MAX);

	    c_parser_consume_token (parser);
	    ಯದಿ (!c_parser_get_builtin_args (parser, name,
					    &cexpr_list, ಅಸತ್ಯ,
					    &close_paren_loc))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    ಯದಿ (vec_safe_length (cexpr_list) != ಅಂಕೆ_args)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, ಸತ್ಯ, ಸತ್ಯ);
	    ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (arg_p->ಮೌಲ್ಯ)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (arg_p->ಮೌಲ್ಯ)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (arg_p->ಮೌಲ್ಯ)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (!TYPE_UNSIGNED (ವೃಕ್ಷ_TYPE (arg_p->ಮೌಲ್ಯ)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (arg_p->ಮೌಲ್ಯ))
		== char_type_ಗಂಟು)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ವೃಕ್ಷ arg = arg_p->ಮೌಲ್ಯ;
	    ವೃಕ್ಷ type = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (arg));
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
	    ಪೂರ್ಣಾಙ್ಕ prec = TYPE_PRECISION (type);
	    ಯದಿ (ಅಂಕೆ_args == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_to_rvalue (loc, *arg_p, ಸತ್ಯ, ಸತ್ಯ);
		ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (arg_p->ಮೌಲ್ಯ)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		    ಭಙ್ಗ;
		  }
		ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (arg_p->ಮೌಲ್ಯ)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		    ಭಙ್ಗ;
		  }
		ವೃಕ್ಷ arg1 = save_ಅಭಿವ್ಯಕ್ತಿ (arg);
		ವೃಕ್ಷ arg2 = save_ಅಭಿವ್ಯಕ್ತಿ (arg_p->ಮೌಲ್ಯ);
		ವೃಕ್ಷ_code code;
		ಯದಿ (stdc_rid == C_BUILTIN_STDC_ROTATE_ಎಡ)
		  code = LROTATE_ಅಭಿವ್ಯಕ್ತಿ;
		ಅನ್ಯಥಾ
		  code = RROTATE_ಅಭಿವ್ಯಕ್ತಿ;

		ಯದಿ (ವೃಕ್ಷ_CODE (arg2) == INTEGER_CST
		    && ವೃಕ್ಷ_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_ಎಣಿಕೆ_negative,
			      "rotate count is negative");

		ವೃಕ್ಷ instrument_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
		ಯದಿ (sanitize_flags_p (SANITIZE_SHIFT))
		  instrument_ಅಭಿವ್ಯಕ್ತಿ = ubsan_instrument_shift (loc, code,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		ಯದಿ (TYPE_PRECISION (ವೃಕ್ಷ_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_ಗಂಟು))
		  arg2 = fold_convert (unsigned_type_ಗಂಟು, arg2);

		ಯದಿ (TYPE_UNSIGNED (ವೃಕ್ಷ_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (arg2),
				     arg2, build_int_cst (ವೃಕ್ಷ_TYPE (arg2),
							  prec));
		ಅನ್ಯಥಾ
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    ವೃಕ್ಷ utype = c_common_unsigned_type (ವೃಕ್ಷ_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_ಅಭಿವ್ಯಕ್ತಿ, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		ಯದಿ (type_has_mode_precision_p (ವೃಕ್ಷ_TYPE (arg1))
		    || (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_MODE_SIZE))
		  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build2_loc (loc, code, ವೃಕ್ಷ_TYPE (arg1), arg1,
					   arg2);
		ಅನ್ಯಥಾ
		  {
		    arg2 = save_ಅಭಿವ್ಯಕ್ತಿ (arg2);
		    ವೃಕ್ಷ t1 = build2_loc (loc, (code == LROTATE_ಅಭಿವ್ಯಕ್ತಿ
						? LSHIFT_ಅಭಿವ್ಯಕ್ತಿ : RSHIFT_ಅಭಿವ್ಯಕ್ತಿ),
					  ವೃಕ್ಷ_TYPE (arg1), arg1, arg2);
		    ವೃಕ್ಷ t2 = build2_loc (loc, MINUS_ಅಭಿವ್ಯಕ್ತಿ,
					  ವೃಕ್ಷ_TYPE (arg2),
					  build_int_cst (ವೃಕ್ಷ_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (code == LROTATE_ಅಭಿವ್ಯಕ್ತಿ
					   ? RSHIFT_ಅಭಿವ್ಯಕ್ತಿ : LSHIFT_ಅಭಿವ್ಯಕ್ತಿ),
				     ವೃಕ್ಷ_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_ಎಣಿಕೆ_overflow);
		    ವೃಕ್ಷ t3 = build2_loc (loc, BIT_IOR_ಅಭಿವ್ಯಕ್ತಿ,
					  ವೃಕ್ಷ_TYPE (arg1), t1, t2);
		    ವೃಕ್ಷ t4 = build2_loc (loc, NE_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು,
					  arg2,
					  build_zero_cst (ವೃಕ್ಷ_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು,
				     arg1, t4);
		    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build3_loc (loc, COND_ಅಭಿವ್ಯಕ್ತಿ,
					     ವೃಕ್ಷ_TYPE (arg1), t4, t3, arg1);
		  }
		ಯದಿ (instrument_ಅಭಿವ್ಯಕ್ತಿ)
		  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build2_loc (loc, COMPOUND_ಅಭಿವ್ಯಕ್ತಿ,
					   ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ),
					   instrument_ಅಭಿವ್ಯಕ್ತಿ, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
		set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_paren_loc);
		ಭಙ್ಗ;
	      }
	    ವೃಕ್ಷ barg1 = arg;
	    ವಿಕಲ್ಪ (stdc_rid)
	      {
	      ಪಕ್ಷ C_BUILTIN_STDC_BIT_CEIL:
		arg = save_ಅಭಿವ್ಯಕ್ತಿ (arg);
		barg1 = build2_loc (loc, PLUS_ಅಭಿವ್ಯಕ್ತಿ, type, arg,
				    build_int_cst (type, -1));
		ಭಙ್ಗ;
	      ಪಕ್ಷ C_BUILTIN_STDC_BIT_FLOOR:
		barg1 = arg = save_ಅಭಿವ್ಯಕ್ತಿ (arg);
		ಭಙ್ಗ;
	      ಪಕ್ಷ C_BUILTIN_STDC_ಎಣಿಕೆ_ZEROS:
	      ಪಕ್ಷ C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      ಪಕ್ಷ C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      ಪಕ್ಷ C_BUILTIN_STDC_LEADING_ONES:
	      ಪಕ್ಷ C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, BIT_NOT_ಅಭಿವ್ಯಕ್ತಿ, type, arg);
		ಭಙ್ಗ;
	      ಸ್ವಭಾವ:
		ಭಙ್ಗ;
	      }
	    ವೃಕ್ಷ barg2 = NULL_ವೃಕ್ಷ;
	    ವಿಕಲ್ಪ (stdc_rid)
	      {
	      ಪಕ್ಷ C_BUILTIN_STDC_BIT_WIDTH:
	      ಪಕ್ಷ C_BUILTIN_STDC_LEADING_ONES:
	      ಪಕ್ಷ C_BUILTIN_STDC_LEADING_ZEROS:
	      ಪಕ್ಷ C_BUILTIN_STDC_TRAILING_ONES:
	      ಪಕ್ಷ C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_ಗಂಟು, prec);
		ಭಙ್ಗ;
	      ಪಕ್ಷ C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      ಪಕ್ಷ C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      ಪಕ್ಷ C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      ಪಕ್ಷ C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		barg2 = integer_minus_one_ಗಂಟು;
		ಭಙ್ಗ;
	      ಸ್ವಭಾವ:
		ಭಙ್ಗ;
	      }
	    ವೃಕ್ಷ fndecl = NULL_ವೃಕ್ಷ;
	    ವಿಕಲ್ಪ (stdc_rid)
	      {
	      ಪಕ್ಷ C_BUILTIN_STDC_BIT_CEIL:
	      ಪಕ್ಷ C_BUILTIN_STDC_BIT_FLOOR:
	      ಪಕ್ಷ C_BUILTIN_STDC_BIT_WIDTH:
	      ಪಕ್ಷ C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      ಪಕ್ಷ C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      ಪಕ್ಷ C_BUILTIN_STDC_LEADING_ONES:
	      ಪಕ್ಷ C_BUILTIN_STDC_LEADING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CLZG);
		ಭಙ್ಗ;
	      ಪಕ್ಷ C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      ಪಕ್ಷ C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      ಪಕ್ಷ C_BUILTIN_STDC_TRAILING_ONES:
	      ಪಕ್ಷ C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CTZG);
		ಭಙ್ಗ;
	      ಪಕ್ಷ C_BUILTIN_STDC_ಎಣಿಕೆ_ONES:
	      ಪಕ್ಷ C_BUILTIN_STDC_ಎಣಿಕೆ_ZEROS:
	      ಪಕ್ಷ C_BUILTIN_STDC_HAS_SINGLE_BIT:
		fndecl = builtin_decl_explicit (BUILT_IN_POPCOUNTG);
		ಭಙ್ಗ;
	      ಸ್ವಭಾವ:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    ಪೂರ್ಣಾಙ್ಕ nargs = barg2 != NULL_ವೃಕ್ಷ ? 2 : 1;
	    vec<ವೃಕ್ಷ, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<ವೃಕ್ಷ, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    args->quick_ತಳ್ಳು (barg1);
	    arg_loc.quick_ತಳ್ಳು (arg_p->get_location ());
	    origtypes->quick_ತಳ್ಳು (arg_p->original_type);
	    ಯದಿ (nargs == 2)
	      {
		args->quick_ತಳ್ಳು (barg2);
		arg_loc.quick_ತಳ್ಳು (loc);
		origtypes->quick_ತಳ್ಳು (integer_type_ಗಂಟು);
	      }
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_build_function_call_vec (loc, arg_loc, fndecl,
						    args, origtypes);
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_paren_loc);
	    ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	      ಭಙ್ಗ;
	    ವಿಕಲ್ಪ (stdc_rid)
	      {
	      ಪಕ್ಷ C_BUILTIN_STDC_BIT_CEIL:
	      ಪಕ್ಷ C_BUILTIN_STDC_BIT_FLOOR:
		--prec;
		/* FALLTHRU */
	      ಪಕ್ಷ C_BUILTIN_STDC_BIT_WIDTH:
		ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build2_loc (loc, MINUS_ಅಭಿವ್ಯಕ್ತಿ, integer_type_ಗಂಟು,
					 build_int_cst (integer_type_ಗಂಟು,
							prec), ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
		ಭಙ್ಗ;
	      ಪಕ್ಷ C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      ಪಕ್ಷ C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      ಪಕ್ಷ C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      ಪಕ್ಷ C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build2_loc (loc, PLUS_ಅಭಿವ್ಯಕ್ತಿ, integer_type_ಗಂಟು,
					 ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, integer_one_ಗಂಟು);
		ಭಙ್ಗ;
	      ಪಕ್ಷ C_BUILTIN_STDC_HAS_SINGLE_BIT:
		ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build2_loc (loc, EQ_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು,
					 ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, integer_one_ಗಂಟು);
		ಭಙ್ಗ;
	      ಸ್ವಭಾವ:
		ಭಙ್ಗ;
	      }

	    ಯದಿ (stdc_rid != C_BUILTIN_STDC_BIT_CEIL
		&& stdc_rid != C_BUILTIN_STDC_BIT_FLOOR)
	      {
		ಯದಿ (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_BIT)
		  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = fold_convert_loc (loc, unsigned_type_ಗಂಟು,
						 ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
		ಭಙ್ಗ;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    ಯದಿ (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_BIT_CEIL && integer_onep (arg)))
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_int_cst (type, 0);
	    ಅನ್ಯಥಾ
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ
		= build2_loc (loc, LSHIFT_ಅಭಿವ್ಯಕ್ತಿ, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_BIT_CEIL
					      ? 2 : 1)), ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	    ಯದಿ (stdc_rid == C_BUILTIN_STDC_BIT_CEIL)
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build3_loc (loc, COND_ಅಭಿವ್ಯಕ್ತಿ, type,
				       build2_loc (loc, LE_ಅಭಿವ್ಯಕ್ತಿ,
						   boolean_type_ಗಂಟು, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	    ಅನ್ಯಥಾ
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build3_loc (loc, COND_ಅಭಿವ್ಯಕ್ತಿ, type,
				       build2_loc (loc, EQ_ಅಭಿವ್ಯಕ್ತಿ,
						   boolean_type_ಗಂಟು, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ RID_BUILTIN_BSWAPG:
	ಪಕ್ಷ RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_ಅಭಿವ್ಯಕ್ತಿ_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    internal_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    ಧ್ರುವ ವರ್ಣ *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    ಯದಿ (!c_parser_get_builtin_args (parser, name, &cexpr_list, ಅಸತ್ಯ,
					    &close_paren_loc))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    ಯದಿ (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }

	    c_ಅಭಿವ್ಯಕ್ತಿ_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, ಸತ್ಯ, ಸತ್ಯ);
	    ವೃಕ್ಷ arg = arg_p->ಮೌಲ್ಯ;
	    ಯದಿ (error_operand_p (arg))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ವೃಕ್ಷ type = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (arg));
	    ಯದಿ (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (ವೃಕ್ಷ_CODE (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (ವೃಕ್ಷ_CODE (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    arg = c_fully_fold (arg, ಅಸತ್ಯ, ರಿಕ್ತ);
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_paren_loc);
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ಯದಿ (!parens.require_open (parser))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ವೃಕ್ಷ sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = objc_build_selector_ಅಭಿವ್ಯಕ್ತಿ (loc, sel);
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_loc);
	  }
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ಯದಿ (!parens.require_open (parser))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = objc_build_protocol_ಅಭಿವ್ಯಕ್ತಿ (id);
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_loc);
	  }
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_AT_ENCODE:
	  {
	    /* Extension to support C-structures in the archiver.  */
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ಯದಿ (!parens.require_open (parser))
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    t1 = c_parser_type_name (parser);
	    ಯದಿ (t1 == ರಿಕ್ತ)
	      {
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
		ಭಙ್ಗ;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    ವೃಕ್ಷ type = groktypename (t1, ರಿಕ್ತ, ರಿಕ್ತ);
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = objc_build_encode_ಅಭಿವ್ಯಕ್ತಿ (type);
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_loc);
	  }
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_GENERIC:
	  ಅಭಿವ್ಯಕ್ತಿ = c_parser_generic_selection (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_OMP_ALL_MEMORY:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  ಅಭಿವ್ಯಕ್ತಿ.set_error ();
	  ಭಙ್ಗ;
	/* C23 'nullptr' literal.  */
	ಪಕ್ಷ RID_NULLPTR:
	  c_parser_consume_token (parser);
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = nullptr_ಗಂಟು;
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_TRUE:
	  c_parser_consume_token (parser);
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = boolean_true_ಗಂಟು;
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
	  ಭಙ್ಗ;
	ಪಕ್ಷ RID_FALSE:
	  c_parser_consume_token (parser);
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = boolean_false_ಗಂಟು;
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  c_parser_error (parser, "expected expression");
	  ಅಭಿವ್ಯಕ್ತಿ.set_error ();
	  ಭಙ್ಗ;
	}
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_OPEN_SQUARE:
      ಯದಿ (c_dialect_objc ())
	{
	  ವೃಕ್ಷ receiver, args;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  args = c_parser_objc_message_args (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = objc_build_message_ಅಭಿವ್ಯಕ್ತಿ (receiver, args);
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, loc, close_loc);
	  ಭಙ್ಗ;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    ಸ್ವಭಾವ:
      c_parser_error (parser, "expected expression");
      ಅಭಿವ್ಯಕ್ತಿ.set_error ();
      ಭಙ್ಗ;
    }
 out:
  ಪ್ರತ್ಯಾಗಮ c_parser_postfix_expression_after_primary
    (parser, ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, loc), ಅಭಿವ್ಯಕ್ತಿ);
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

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_postfix_expression_after_paren_type (c_parser *parser,
					      ಸಂರಚನಾ c_declspecs *scspecs,
					      ಸಂರಚನಾ c_type_name *type_name,
					      location_t type_loc)
{
  ವೃಕ್ಷ type;
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ init;
  ತಾರ್ಕಿಕ non_const;
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  location_t start_loc;
  ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ type_ಅಭಿವ್ಯಕ್ತಿ_const = ಸತ್ಯ;
  ತಾರ್ಕಿಕ constexpr_p = scspecs ? scspecs->constexpr_p : ಅಸತ್ಯ;
  unsigned ಪೂರ್ಣಾಙ್ಕ underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (ಸಾಲು_table, type_loc);
  start_loc = c_parser_peek_token (parser)->location;
  ಯದಿ (constexpr_p)
    {
      underspec_state = start_underspecified_init (start_loc, NULL_ವೃಕ್ಷ);
      /* A constexpr compound literal is subject to the constraints on
	 underspecified declarations, which may not declare tags or
	 members or structures or unions; it is undefined behavior to
	 declare the members of an enumeration.  Where the structure,
	 union or enumeration type is declared within the compound
	 literal initializer, this is diagnosed elsewhere as a result
	 of the above call to start_underspecified_init.  Diagnose
	 here the case of declaring such a type in the type specifiers
	 of the compound literal.  */
      ವಿಕಲ್ಪ (type_name->specs->typespec_kind)
	{
	ಪಕ್ಷ ctsk_tagfirstref:
	ಪಕ್ಷ ctsk_tagfirstref_attrs:
	  error_at (type_loc, "%qT declared in %<constexpr%> compound literal",
		    type_name->specs->type);
	  ಭಙ್ಗ;

	ಪಕ್ಷ ctsk_tagdef:
	  error_at (type_loc, "%qT defined in %<constexpr%> compound literal",
		    type_name->specs->type);
	  ಭಙ್ಗ;

	ಸ್ವಭಾವ:
	  ಭಙ್ಗ;
	}
    }
  start_init (NULL_ವೃಕ್ಷ, ರಿಕ್ತ,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_ಅಭಿವ್ಯಕ್ತಿ, &type_ಅಭಿವ್ಯಕ್ತಿ_const);
  ತಾರ್ಕಿಕ varsize_p = ಅಸತ್ಯ;
  ಯದಿ (type != error_mark_ಗಂಟು && C_TYPE_VARIABLE_SIZE (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = ಸತ್ಯ;
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_ಗಂಟು;
    }
  ಯದಿ (constexpr_p && type != error_mark_ಗಂಟು)
    {
      ವೃಕ್ಷ type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      ಯದಿ (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      ಅನ್ಯಥಾ ಯದಿ (RECORD_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, ಅಸತ್ಯ, ರಿಕ್ತ, varsize_p);
  ಯದಿ (constexpr_p)
    finish_underspecified_init (NULL_ವೃಕ್ಷ, underspec_state);
  finish_init ();
  maybe_warn_string_init (type_loc, type, init);

  ಯದಿ (type != error_mark_ಗಂಟು
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_ಗಂಟು;
    }

  ಯದಿ (!pedwarn_c90 (start_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (start_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.ಮೌಲ್ಯ && ವೃಕ್ಷ_CODE (init.ಮೌಲ್ಯ) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.ಮೌಲ್ಯ)
	       : init.original_code == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ);
  non_const |= !type_ಅಭಿವ್ಯಕ್ತಿ_const;
  unsigned ಪೂರ್ಣಾಙ್ಕ alignas_align = 0;
  ಯದಿ (type != error_mark_ಗಂಟು
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      ಯದಿ (alignas_align < min_align_of_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_compound_literal (start_loc, type, init.ಮೌಲ್ಯ, non_const,
				       alignas_align, scspecs);
  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, init.src_range);
  ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
  ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
  ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
  ಯದಿ (type != error_mark_ಗಂಟು
      && ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ != error_mark_ಗಂಟು
      && type_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  gcc_assert (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == NULL_ವೃಕ್ಷ);
	  C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) = type_ಅಭಿವ್ಯಕ್ತಿ;
	}
      ಅನ್ಯಥಾ
	{
	  gcc_assert (!non_const);
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, type,
			       type_ಅಭಿವ್ಯಕ್ತಿ, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	}
    }
  ಪ್ರತ್ಯಾಗಮ c_parser_postfix_expression_after_primary (parser, start_loc, ಅಭಿವ್ಯಕ್ತಿ);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
sizeof_ptr_memacc_comptypes (ವೃಕ್ಷ type1, ವೃಕ್ಷ type2)
{
  ಪ್ರತ್ಯಾಗಮ comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

ಸ್ಥಿರ ಶೂನ್ಯ
warn_for_abs (location_t loc, ವೃಕ್ಷ fndecl, ವೃಕ್ಷ arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  ಯದಿ (c_inhibit_evaluation_warnings)
    ಪ್ರತ್ಯಾಗಮ;

  ವೃಕ್ಷ atype = ವೃಕ್ಷ_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  ಯದಿ (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && ವೃಕ್ಷ_CODE (atype) != COMPLEX_TYPE)
    ಪ್ರತ್ಯಾಗಮ;

  ಗಣನಾ built_in_function fcode = DECL_FUNCTION_CODE (fndecl);

  ವಿಕಲ್ಪ (fcode)
    {
    ಪಕ್ಷ BUILT_IN_ABS:
    ಪಕ್ಷ BUILT_IN_LABS:
    ಪಕ್ಷ BUILT_IN_LLABS:
    ಪಕ್ಷ BUILT_IN_IMAXABS:
      ಯದಿ (!INTEGRAL_TYPE_P (atype))
	{
	  ಯದಿ (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ಮೌಲ್ಯ,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_ಮೌಲ್ಯ,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  ಅನ್ಯಥಾ
	    gcc_unreachable ();
	  ಪ್ರತ್ಯಾಗಮ;
	}
      ಯದಿ (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_ಮೌಲ್ಯ,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      ಭಙ್ಗ;

    CASE_FLT_FN (BUILT_IN_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FABS):
      ಯದಿ (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_MODE_P (TYPE_MODE (atype)))
	{
	  ಯದಿ (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ಮೌಲ್ಯ,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  ಅನ್ಯಥಾ ಯದಿ (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ಮೌಲ್ಯ,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_ಮೌಲ್ಯ,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  ಅನ್ಯಥಾ
	    gcc_unreachable ();
	  ಪ್ರತ್ಯಾಗಮ;
	}
      ಭಙ್ಗ;

    CASE_FLT_FN (BUILT_IN_CABS):
      ಯದಿ (ವೃಕ್ಷ_CODE (atype) != COMPLEX_TYPE)
	{
	  ಯದಿ (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ಮೌಲ್ಯ,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  ಅನ್ಯಥಾ ಯದಿ (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ಮೌಲ್ಯ,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  ಅನ್ಯಥಾ
	    gcc_unreachable ();

	  ಪ್ರತ್ಯಾಗಮ;
	}
      ಭಙ್ಗ;

    ಪಕ್ಷ BUILT_IN_FABSD32:
    ಪಕ್ಷ BUILT_IN_FABSD64:
    ಪಕ್ಷ BUILT_IN_FABSD128:
    ಪಕ್ಷ BUILT_IN_FABSD64X:
      ಯದಿ (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  ಯದಿ (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ಮೌಲ್ಯ,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  ಅನ್ಯಥಾ ಯದಿ (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ಮೌಲ್ಯ,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_ಮೌಲ್ಯ,
			"using decimal floating-point absolute value "
			"function %qD when argument is of complex type %qT",
			fndecl, atype);
	  ಅನ್ಯಥಾ
	    gcc_unreachable ();
	  ಪ್ರತ್ಯಾಗಮ;
	}
      ಭಙ್ಗ;

    ಸ್ವಭಾವ:
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (!TYPE_ARG_TYPES (ವೃಕ್ಷ_TYPE (fndecl)))
    ಪ್ರತ್ಯಾಗಮ;

  ವೃಕ್ಷ ftype = ವೃಕ್ಷ_ಮೌಲ್ಯ (TYPE_ARG_TYPES (ವೃಕ್ಷ_TYPE (fndecl)));
  ಯದಿ (ವೃಕ್ಷ_CODE (atype) == COMPLEX_TYPE)
    {
      gcc_assert (ವೃಕ್ಷ_CODE (ftype) == COMPLEX_TYPE);
      atype = ವೃಕ್ಷ_TYPE (atype);
      ftype = ವೃಕ್ಷ_TYPE (ftype);
    }

  ಯದಿ (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_ಮೌಲ್ಯ,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_postfix_expression_after_primary (c_parser *parser,
					   location_t ಅಭಿವ್ಯಕ್ತಿ_loc,
					   ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ orig_ಅಭಿವ್ಯಕ್ತಿ;
  ವೃಕ್ಷ ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  ವೃಕ್ಷ sizeof_arg[6];
  unsigned ಪೂರ್ಣಾಙ್ಕ literal_zero_mask;
  unsigned ಪೂರ್ಣಾಙ್ಕ i;
  vec<ವೃಕ್ಷ, va_gc> *exprlist;
  vec<ವೃಕ್ಷ, va_gc> *origtypes = ರಿಕ್ತ;
  vec<location_t> arg_loc = vNULL;
  location_t start;
  location_t finish;

  ಯಾವತ್ (ಸತ್ಯ)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
	{
	ಪಕ್ಷ CPP_OPEN_SQUARE:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_ವೃಕ್ಷ;
	  ಯದಿ (!c_omp_array_section_p
	      || c_parser_next_token_is_not (parser, CPP_COLON))
	    idx = c_parser_expression (parser).ಮೌಲ್ಯ;

	  ಯದಿ (c_omp_array_section_p
	      && c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      ಯದಿ (c_parser_next_token_is_not (parser, CPP_CLOSE_SQUARE))
		len = c_parser_expression (parser).ಮೌಲ್ಯ;

	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_omp_array_section (op_loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, idx,
						    len);
	    }
	  ಅನ್ಯಥಾ
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_array_ref (op_loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, idx);

	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");

	  start = ಅಭಿವ್ಯಕ್ತಿ.get_start ();
	  finish = parser->tokens_buf[0].location;
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, start, finish);
	  ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
	  ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	  ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    ಪ್ರತಿ (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_ವೃಕ್ಷ;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_mask = 0;
	    ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = ರಿಕ್ತ;
	    ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == FUNCTION_DECL
		     && fndecl_built_in_p (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, BUILT_IN_CLASSIFY_TYPE)
		     && c_parser_next_tokens_start_typename (parser,
							     cla_prefer_id))
	      {
		/* __builtin_classify_type (type)  */
		c_inhibit_evaluation_warnings++;
		in_alignof++;
		ಸಂರಚನಾ c_type_name *type = c_parser_type_name (parser);
		c_inhibit_evaluation_warnings--;
		in_alignof--;
		ಸಂರಚನಾ c_typespec ret;
		ret.ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
		ret.spec = error_mark_ಗಂಟು;
		ret.ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಅಸತ್ಯ;
		ಯದಿ (type != ರಿಕ್ತ)
		  ret.spec = groktypename (type, &ret.ಅಭಿವ್ಯಕ್ತಿ,
					   &ret.ಅಭಿವ್ಯಕ್ತಿ_const_operands);
		parens.skip_until_found_close (parser);
		ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_int_cst (integer_type_ಗಂಟು,
					    type_to_class (ret.spec));
		ಭಙ್ಗ;
	      }
	    ಅನ್ಯಥಾ
	      exprlist = c_parser_ಅಭಿವ್ಯಕ್ತಿ_list (parser, ಸತ್ಯ, ಅಸತ್ಯ, &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_mask);
	    parens.skip_until_found_close (parser);
	  }
	  orig_ಅಭಿವ್ಯಕ್ತಿ = ಅಭಿವ್ಯಕ್ತಿ;
	  mark_exp_read (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	  ಯದಿ (warn_sizeof_pointer_memaccess)
	    sizeof_pointer_memaccess_warning (sizeof_arg_loc,
					      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == FUNCTION_DECL)
	    {
	      ಯದಿ (fndecl_built_in_p (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, BUILT_IN_MEMSET)
		  && vec_safe_length (exprlist) == 3)
		{
		  ವೃಕ್ಷ arg0 = (*exprlist)[0];
		  ವೃಕ್ಷ arg2 = (*exprlist)[2];
		  warn_for_memset (ಅಭಿವ್ಯಕ್ತಿ_loc, arg0, arg2, literal_zero_mask);
		}
	      ಯದಿ (warn_absolute_ಮೌಲ್ಯ
		  && fndecl_built_in_p (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, BUILT_IN_NORMAL)
		  && vec_safe_length (exprlist) == 1)
		warn_for_abs (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, (*exprlist)[0]);
	      ಯದಿ (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->in_intervening_code
		  && omp_runtime_api_call (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ))
		{
		  error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->fail = ಸತ್ಯ;
		}
	      ಯದಿ (warn_calloc_transposed_args)
		ಯದಿ (ವೃಕ್ಷ attr = lookup_attribute ("alloc_size",
						  TYPE_ATTRIBUTES
						    (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ))))
		  ಯದಿ (ವೃಕ್ಷ_ಮೌಲ್ಯ (attr) && ವೃಕ್ಷ_CHAIN (ವೃಕ್ಷ_ಮೌಲ್ಯ (attr)))
		    warn_for_calloc (sizeof_arg_loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, exprlist,
				     sizeof_arg, attr);
	    }

	  start = ಅಭಿವ್ಯಕ್ತಿ.get_start ();
	  finish = parser->tokens_buf[0].get_finish ();
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ
	    = c_build_function_call_vec (ಅಭಿವ್ಯಕ್ತಿ_loc, arg_loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ,
					 exprlist, origtypes);
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, start, finish);
	  ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;

	  ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
	  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == INTEGER_CST
	      && ವೃಕ್ಷ_CODE (orig_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == FUNCTION_DECL
	      && fndecl_built_in_p (orig_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, BUILT_IN_CONSTANT_P))
	    ಅಭಿವ್ಯಕ್ತಿ.original_code = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ;
	  ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	  ಯದಿ (exprlist)
	    {
	      release_ವೃಕ್ಷ_vector (exprlist);
	      release_ವೃಕ್ಷ_vector (origtypes);
	    }
	  arg_loc.release ();
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  ಅಭಿವ್ಯಕ್ತಿ = default_function_array_conversion (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->ಮೌಲ್ಯ;
	      comp_loc = comp_tok->location;
	    }
	  ಅನ್ಯಥಾ
	    {
	      c_parser_error (parser, "expected identifier");
	      ಅಭಿವ್ಯಕ್ತಿ.set_error ();
	      ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
              ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	      ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
	    }
	  start = ಅಭಿವ್ಯಕ್ತಿ.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_component_ref (op_loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, start, finish);
	  ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
	  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) != COMPONENT_REF)
	    ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	  ಅನ್ಯಥಾ
	    {
	      /* Remember the original type of a bitfield.  */
	      ವೃಕ್ಷ field = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 1);
	      ಯದಿ (ವೃಕ್ಷ_CODE (field) != FIELD_DECL)
		ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	      ಅನ್ಯಥಾ
		ಅಭಿವ್ಯಕ್ತಿ.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಅಸತ್ಯ);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->ಮೌಲ್ಯ;
	      comp_loc = comp_tok->location;
	    }
	  ಅನ್ಯಥಾ
	    {
	      c_parser_error (parser, "expected identifier");
	      ಅಭಿವ್ಯಕ್ತಿ.set_error ();
	      ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
	      ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	      ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
	    }
	  start = ಅಭಿವ್ಯಕ್ತಿ.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_component_ref (op_loc,
					    build_indirect_ref (op_loc,
								ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ,
								RO_ARROW),
					    ident, comp_loc,
					    ಅಭಿವ್ಯಕ್ತಿ.get_location ());
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, start, finish);
	  ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
	  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) != COMPONENT_REF)
	    ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	  ಅನ್ಯಥಾ
	    {
	      /* Remember the original type of a bitfield.  */
	      ವೃಕ್ಷ field = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 1);
	      ಯದಿ (ವೃಕ್ಷ_CODE (field) != FIELD_DECL)
		ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	      ಅನ್ಯಥಾ
		ಅಭಿವ್ಯಕ್ತಿ.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  start = ಅಭಿವ್ಯಕ್ತಿ.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	  ಅಭಿವ್ಯಕ್ತಿ = default_function_array_conversion (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ);
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_unary_op (op_loc, POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ,
				       ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ);
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, start, finish);
	  ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
	  ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  start = ಅಭಿವ್ಯಕ್ತಿ.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	  ಅಭಿವ್ಯಕ್ತಿ = default_function_array_conversion (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ);
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_unary_op (op_loc, POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ,
				       ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ);
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, start, finish);
	  ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
	  ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_expression (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
    ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (tloc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಅಸತ್ಯ);
  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ next;
      ವೃಕ್ಷ lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t ಅಭಿವ್ಯಕ್ತಿ_loc;
      c_parser_consume_token (parser);
      ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      lhsval = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      ಯಾವತ್ (ವೃಕ್ಷ_CODE (lhsval) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ
	     || ವೃಕ್ಷ_CODE (lhsval) == NOP_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ಯದಿ (ವೃಕ್ಷ_CODE (lhsval) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
	    lhsval = ವೃಕ್ಷ_OPERAND (lhsval, 1);
	  ಅನ್ಯಥಾ
	    lhsval = ವೃಕ್ಷ_OPERAND (lhsval, 0);
	}
      ಯದಿ (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      ಯದಿ (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  ವೃಕ್ಷ val = embed->ಮೌಲ್ಯ;
	  unsigned last = RAW_DATA_LENGTH (val) - 1;
	  next.ಮೌಲ್ಯ = build_int_cst (ವೃಕ್ಷ_TYPE (val),
				      RAW_DATA_UCHAR_ELT (val, last));
	  next.original_type = integer_type_ಗಂಟು;
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ
	{
	  next = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	  next = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, next, ಸತ್ಯ, ಅಸತ್ಯ);
	}
      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_compound_ಅಭಿವ್ಯಕ್ತಿ (loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, next.ಮೌಲ್ಯ);
      ಅಭಿವ್ಯಕ್ತಿ.original_code = COMPOUND_ಅಭಿವ್ಯಕ್ತಿ;
      ಅಭಿವ್ಯಕ್ತಿ.original_type = next.original_type;
      ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
    }
  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_expression_conv (c_parser *parser)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  location_t loc = c_parser_peek_token (parser)->location;
  ಅಭಿವ್ಯಕ್ತಿ = c_parser_expression (parser);
  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (loc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಅಸತ್ಯ);
  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ
c_parser_check_literal_zero (c_parser *parser, unsigned *literal_zero_mask,
			     unsigned ಪೂರ್ಣಾಙ್ಕ idx)
{
  ಯದಿ (idx >= HOST_BITS_PER_INT)
    ಪ್ರತ್ಯಾಗಮ;

  c_token *tok = c_parser_peek_token (parser);
  ವಿಕಲ್ಪ (tok->type)
    {
    ಪಕ್ಷ CPP_ಸಂಖ್ಯೆ:
    ಪಕ್ಷ CPP_CHAR:
    ಪಕ್ಷ CPP_WCHAR:
    ಪಕ್ಷ CPP_CHAR16:
    ಪಕ್ಷ CPP_CHAR32:
    ಪಕ್ಷ CPP_UTF8CHAR:
      /* If a parameter is literal zero alone, remember it
	 for -Wmemset-transposed-args warning.  */
      ಯದಿ (integer_zerop (tok->ಮೌಲ್ಯ)
	  && !ವೃಕ್ಷ_OVERFLOW (tok->ಮೌಲ್ಯ)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_mask |= 1U << idx;
    ಸ್ವಭಾವ:
      ಭಙ್ಗ;
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

ಸ್ಥಿರ vec<ವೃಕ್ಷ, va_gc> *
c_parser_ಅಭಿವ್ಯಕ್ತಿ_list (c_parser *parser, ತಾರ್ಕಿಕ convert_p, ತಾರ್ಕಿಕ fold_p,
		    vec<ವೃಕ್ಷ, va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, ವೃಕ್ಷ *sizeof_arg,
		    vec<location_t> *locations,
		    unsigned ಪೂರ್ಣಾಙ್ಕ *literal_zero_mask)
{
  vec<ವೃಕ್ಷ, va_gc> *ret;
  vec<ವೃಕ್ಷ, va_gc> *orig_types;
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  unsigned ಪೂರ್ಣಾಙ್ಕ idx = 0;
  ತಾರ್ಕಿಕ save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = ಅಸತ್ಯ;

  ret = make_ವೃಕ್ಷ_vector ();
  ಯದಿ (p_orig_types == ರಿಕ್ತ)
    orig_types = ರಿಕ್ತ;
  ಅನ್ಯಥಾ
    orig_types = make_ವೃಕ್ಷ_vector ();

  ಯದಿ (literal_zero_mask)
    c_parser_check_literal_zero (parser, literal_zero_mask, 0);
  ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
  ಯದಿ (convert_p)
    ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ.get_location (), ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಸತ್ಯ);
  ಯದಿ (fold_p)
    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
  ret->quick_ತಳ್ಳು (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
  ಯದಿ (orig_types)
    orig_types->quick_ತಳ್ಳು (ಅಭಿವ್ಯಕ್ತಿ.original_type);
  ಯದಿ (locations)
    locations->safe_ತಳ್ಳು (ಅಭಿವ್ಯಕ್ತಿ.get_location ());
  ಯದಿ (sizeof_arg != ರಿಕ್ತ
      && (ಅಭಿವ್ಯಕ್ತಿ.original_code == SIZEOF_ಅಭಿವ್ಯಕ್ತಿ
	  || ಅಭಿವ್ಯಕ್ತಿ.original_code == PAREN_SIZEOF_ಅಭಿವ್ಯಕ್ತಿ))
    {
      sizeof_arg[0] = c_last_sizeof_arg;
      sizeof_arg_loc[0] = c_last_sizeof_loc;
    }
  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  ವೃಕ್ಷ ಮೌಲ್ಯ = embed->ಮೌಲ್ಯ;
	  ಅಭಿವ್ಯಕ್ತಿ.original_code = INTEGER_CST;
	  ಅಭಿವ್ಯಕ್ತಿ.original_type = integer_type_ಗಂಟು;
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, embed->get_range ());
	  ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	  ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ i = 0; i < (unsigned) RAW_DATA_LENGTH (ಮೌಲ್ಯ); i++)
	    {
	      ಯದಿ (literal_zero_mask
		  && idx + 1 < HOST_BITS_PER_INT
		  && RAW_DATA_POINTER (ಮೌಲ್ಯ)[i] == 0)
		*literal_zero_mask |= 1U << (idx + 1);
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_int_cst (integer_type_ಗಂಟು,
					  RAW_DATA_UCHAR_ELT (ಮೌಲ್ಯ, i));
	      vec_safe_ತಳ್ಳು (ret, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	      ಯದಿ (orig_types)
		vec_safe_ತಳ್ಳು (orig_types, ಅಭಿವ್ಯಕ್ತಿ.original_type);
	      ಯದಿ (locations)
		locations->safe_ತಳ್ಳು (ಅಭಿವ್ಯಕ್ತಿ.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  ಅನುವರ್ತ;
	}
      ಯದಿ (literal_zero_mask)
	c_parser_check_literal_zero (parser, literal_zero_mask, idx + 1);
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಯದಿ (convert_p)
	ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ.get_location (), ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ,
					 ಸತ್ಯ);
      ಯದಿ (fold_p)
	ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
      vec_safe_ತಳ್ಳು (ret, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
      ಯದಿ (orig_types)
	vec_safe_ತಳ್ಳು (orig_types, ಅಭಿವ್ಯಕ್ತಿ.original_type);
      ಯದಿ (locations)
	locations->safe_ತಳ್ಳು (ಅಭಿವ್ಯಕ್ತಿ.get_location ());
      ಯದಿ (++idx < 6
	  && sizeof_arg != ರಿಕ್ತ
	  && (ಅಭಿವ್ಯಕ್ತಿ.original_code == SIZEOF_ಅಭಿವ್ಯಕ್ತಿ
	      || ಅಭಿವ್ಯಕ್ತಿ.original_code == PAREN_SIZEOF_ಅಭಿವ್ಯಕ್ತಿ))
	{
	  sizeof_arg[idx] = c_last_sizeof_arg;
	  sizeof_arg_loc[idx] = c_last_sizeof_loc;
	}
    }
  ಯದಿ (orig_types)
    *p_orig_types = orig_types;
  c_omp_array_section_p = save_c_omp_array_section_p;
  ಪ್ರತ್ಯಾಗಮ ret;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_objc_class_definition (c_parser *parser, ವೃಕ್ಷ attributes)
{
  ತಾರ್ಕಿಕ iface_p;
  ವೃಕ್ಷ id1;
  ವೃಕ್ಷ superclass;
  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = ಸತ್ಯ;
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = ಅಸತ್ಯ;
  ಅನ್ಯಥಾ
    gcc_unreachable ();

  c_parser_consume_token (parser);
  ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      ಪ್ರತ್ಯಾಗಮ;
    }
  id1 = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      ವೃಕ್ಷ id2;
      ವೃಕ್ಷ proto = NULL_ವೃಕ್ಷ;
      matching_parens parens;
      parens.consume_open (parser);
      ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  ಯದಿ (iface_p && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_ವೃಕ್ಷ;
	    }
	  ಅನ್ಯಥಾ
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
	      ಪ್ರತ್ಯಾಗಮ;
	    }
	}
      ಅನ್ಯಥಾ
	{
	  id2 = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_found_close (parser);
      ಯದಿ (!iface_p)
	{
	  objc_start_category_implementation (id1, id2);
	  ಪ್ರತ್ಯಾಗಮ;
	}
      ಯದಿ (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_category_interface (id1, id2, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  ಪ್ರತ್ಯಾಗಮ;
	}
      superclass = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      c_parser_consume_token (parser);
    }
  ಅನ್ಯಥಾ
    superclass = NULL_ವೃಕ್ಷ;
  ಯದಿ (iface_p)
    {
      ವೃಕ್ಷ proto = NULL_ವೃಕ್ಷ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_class_interface (id1, loc1, superclass, proto, attributes);
    }
  ಅನ್ಯಥಾ
    objc_start_class_implementation (id1, superclass);
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  ಯದಿ (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
    }
  ಅನ್ಯಥಾ
    {
      objc_continue_implementation ();
      ಪ್ರತ್ಯಾಗಮ;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_objc_class_instance_variables (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_EOF))
    {
      ವೃಕ್ಷ decls;
      /* Parse any stray semicolon.  */
      ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  ಅನುವರ್ತ;
	}
      /* Stop if at the end of the instance variables.  */
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  ಭಙ್ಗ;
	}
      /* Parse any objc-visibility-spec.  */
      ಯದಿ (c_parser_next_token_is_keyword (parser, RID_AT_PRIVATE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PRIVATE);
	  ಅನುವರ್ತ;
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PROTECTED);
	  ಅನುವರ್ತ;
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_AT_PUBLIC))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PUBLIC);
	  ಅನುವರ್ತ;
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PACKAGE);
	  ಅನುವರ್ತ;
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, ರಿಕ್ತ, NULL_ವೃಕ್ಷ);
	  ಅನುವರ್ತ;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser, ರಿಕ್ತ);
      ಯದಿ (decls == ರಿಕ್ತ)
	{
	  /* There is a syntax error.  We want to skip the offending
	     tokens up to the next ';' (included) or '}'
	     (excluded).  */

	  /* First, skip manually a ')' or ']'.  This is because they
	     reduce the nesting level, so c_parser_skip_until_found()
	     wouldn't be able to skip past them.  */
	  c_token *token = c_parser_peek_token (parser);
	  ಯದಿ (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_SQUARE)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, ರಿಕ್ತ);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = ಅಸತ್ಯ;
	  ಅನುವರ್ತ;
	}
      ಅನ್ಯಥಾ
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  ವೃಕ್ಷ ivar = nreverse (decls);
	  ಪ್ರತಿ (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_add_instance_variable (copy_ಗಂಟು (ivar));
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}

/* Parse an objc-class-declaration.

   objc-class-declaration:
     @class identifier-list ;
*/

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_objc_class_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_CLASS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  ಯಾವತ್ (ಸತ್ಯ)
    {
      ವೃಕ್ಷ id;
      ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, ರಿಕ್ತ);
	  parser->error = ಅಸತ್ಯ;
	  ಪ್ರತ್ಯಾಗಮ;
	}
      id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse an objc-alias-declaration.

   objc-alias-declaration:
     @compatibility_alias identifier identifier ;
*/

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_objc_alias_declaration (c_parser *parser)
{
  ವೃಕ್ಷ id1, id2;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, ರಿಕ್ತ);
      ಪ್ರತ್ಯಾಗಮ;
    }
  id1 = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
  c_parser_consume_token (parser);
  ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, ರಿಕ್ತ);
      ಪ್ರತ್ಯಾಗಮ;
    }
  id2 = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_objc_protocol_definition (c_parser *parser, ವೃಕ್ಷ attributes)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      ಯಾವತ್ (ಸತ್ಯ)
	{
	  ವೃಕ್ಷ id;
	  ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      ಭಙ್ಗ;
	    }
	  id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	  objc_declare_protocol (id, attributes);
	  c_parser_consume_token (parser);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ಅನ್ಯಥಾ
	    ಭಙ್ಗ;
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      ವೃಕ್ಷ proto = NULL_ವೃಕ್ಷ;
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = ಸತ್ಯ;
      objc_start_protocol (id, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      parser->objc_pq_context = ಅಸತ್ಯ;
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
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ತಾರ್ಕಿಕ
c_parser_objc_method_type (c_parser *parser)
{
  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
    {
    ಪಕ್ಷ CPP_PLUS:
      c_parser_consume_token (parser);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    ಪಕ್ಷ CPP_MINUS:
      c_parser_consume_token (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }
}

/* Parse an objc-method-definition.

   objc-method-definition:
     objc-method-type objc-method-decl ;[opt] compound-statement
*/

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_objc_method_definition (c_parser *parser)
{
  ತಾರ್ಕಿಕ is_class_method = c_parser_objc_method_type (parser);
  ವೃಕ್ಷ decl, attributes = NULL_ವೃಕ್ಷ, ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  parser->objc_pq_context = ಸತ್ಯ;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    &ಅಭಿವ್ಯಕ್ತಿ);
  ಯದಿ (decl == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ;  /* Bail here. */

  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  ಯದಿ (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      ಪ್ರತ್ಯಾಗಮ;
    }

  parser->objc_pq_context = ಅಸತ್ಯ;
  ಯದಿ (objc_start_method_definition (is_class_method, decl, attributes, ಅಭಿವ್ಯಕ್ತಿ))
    {
      add_stmt (c_parser_compound_statement (parser));
      objc_finish_method_definition (current_function_decl);
    }
  ಅನ್ಯಥಾ
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_objc_methodprotolist (c_parser *parser)
{
  ಯಾವತ್ (ಸತ್ಯ)
    {
      /* The list is terminated by @end.  */
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
	{
	ಪಕ್ಷ CPP_SEMICOLON:
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_PLUS:
	ಪಕ್ಷ CPP_MINUS:
	  c_parser_objc_methodproto (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external, ರಿಕ್ತ, NULL_ವೃಕ್ಷ);
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_EOF:
	  ಪ್ರತ್ಯಾಗಮ;
	ಸ್ವಭಾವ:
	  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_AT_END))
	    ಪ್ರತ್ಯಾಗಮ;
	  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_set_method_opt (ಸತ್ಯ);
	      c_parser_consume_token (parser);
	    }
	  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_set_method_opt (ಅಸತ್ಯ);
	      c_parser_consume_token (parser);
	    }
	  ಅನ್ಯಥಾ
	    c_parser_declaration_or_fndef (parser, ಅಸತ್ಯ, ಅಸತ್ಯ, ಸತ್ಯ,
					   ಅಸತ್ಯ, ಸತ್ಯ, ಅಸತ್ಯ);
	  ಭಙ್ಗ;
	}
    }
}

/* Parse an objc-methodproto.

   objc-methodproto:
     objc-method-type objc-method-decl ;
*/

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_objc_methodproto (c_parser *parser)
{
  ತಾರ್ಕಿಕ is_class_method = c_parser_objc_method_type (parser);
  ವೃಕ್ಷ decl, attributes = NULL_ವೃಕ್ಷ;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = ಸತ್ಯ;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    ರಿಕ್ತ);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = ಅಸತ್ಯ;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  ಯದಿ (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (decl != error_mark_ಗಂಟು)
    objc_add_method_declaration (is_class_method, decl, attributes);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_objc_maybe_method_attributes (c_parser* parser, ವೃಕ್ಷ* attributes)
{
  ತಾರ್ಕಿಕ bad = ಅಸತ್ಯ;
  ಯದಿ (*attributes)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *attributes = NULL_ವೃಕ್ಷ;
      bad = ಸತ್ಯ;
    }

  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    *attributes = c_parser_gnu_attributes (parser);

  /* If there were no attributes here, just report any earlier error.  */
  ಯದಿ (*attributes == NULL_ವೃಕ್ಷ || bad)
    ಪ್ರತ್ಯಾಗಮ bad;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    ಪ್ರತ್ಯಾಗಮ bad;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_objc_method_decl (c_parser *parser, ತಾರ್ಕಿಕ is_class_method,
			   ವೃಕ್ಷ *attributes, ವೃಕ್ಷ *ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ type = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ sel;
  ವೃಕ್ಷ parms = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ ellipsis = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ attr_err = ಅಸತ್ಯ;

  *attributes = NULL_ವೃಕ್ಷ;
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
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
  ಯದಿ (!sel || c_parser_next_token_is (parser, CPP_COLON))
    {
      ವೃಕ್ಷ tsel = sel;
      ವೃಕ್ಷ list = NULL_ವೃಕ್ಷ;
      ಯಾವತ್ (ಸತ್ಯ)
	{
	  ವೃಕ್ಷ atype = NULL_ವೃಕ್ಷ, id, keyworddecl;
	  ವೃಕ್ಷ param_attr = NULL_ವೃಕ್ಷ;
	  ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    ಭಙ್ಗ;
	  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_attributes (parser);
	  ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	    }
	  id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  ಯದಿ (!tsel && c_parser_next_token_is_not (parser, CPP_COLON))
	    ಭಙ್ಗ;
	}

      attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_ಗಂಟು (ವೃಕ್ಷ_LIST);
      ಯಾವತ್ (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  ಸಂರಚನಾ c_parm *parm;
	  c_parser_consume_token (parser);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = ಸತ್ಯ;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_method_attributes
						(parser, attributes) ;
	      ಭಙ್ಗ;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_ವೃಕ್ಷ, ಅಸತ್ಯ);
	  ಯದಿ (parm == ರಿಕ್ತ)
	    ಭಙ್ಗ;
	  parms = chainon (parms,
			   build_ವೃಕ್ಷ_list (NULL_ವೃಕ್ಷ, grokparm (parm, ಅಭಿವ್ಯಕ್ತಿ)));
	}
      sel = list;
    }
  ಅನ್ಯಥಾ
    attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

  ಯದಿ (sel == ರಿಕ್ತ)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ಯದಿ (attr_err)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಪ್ರತ್ಯಾಗಮ objc_build_method_signature (is_class_method, type, sel, parms, ellipsis);
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_objc_type_name (c_parser *parser)
{
  ವೃಕ್ಷ quals = NULL_ವೃಕ್ಷ;
  ಸಂರಚನಾ c_type_name *type_name = ರಿಕ್ತ;
  ವೃಕ್ಷ type = NULL_ವೃಕ್ಷ;
  ಯಾವತ್ (ಸತ್ಯ)
    {
      c_token *token = c_parser_peek_token (parser);
      ಯದಿ (token->type == CPP_KEYWORD
	  && (token->keyword == RID_IN
	      || token->keyword == RID_OUT
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_ವೃಕ್ಷ_list (NULL_ವೃಕ್ಷ, token->ಮೌಲ್ಯ), quals);
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
    }
  ಯದಿ (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  ಯದಿ (type_name)
    type = groktypename (type_name, ರಿಕ್ತ, ರಿಕ್ತ);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  ಯದಿ (type == error_mark_ಗಂಟು)
    type = NULL_ವೃಕ್ಷ;

  ಪ್ರತ್ಯಾಗಮ build_ವೃಕ್ಷ_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_objc_protocol_refs (c_parser *parser)
{
  ವೃಕ್ಷ list = NULL_ವೃಕ್ಷ;
  gcc_assert (c_parser_next_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  ಯಾವತ್ (ಸತ್ಯ)
    {
      ವೃಕ್ಷ id;
      ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  ಭಙ್ಗ;
	}
      id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      list = chainon (list, build_ವೃಕ್ಷ_list (NULL_ವೃಕ್ಷ, id));
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  ಪ್ರತ್ಯಾಗಮ list;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_objc_try_catch_finally_statement (c_parser *parser)
{
  location_t location;
  ವೃಕ್ಷ stmt;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  ಯಾವತ್ (c_parser_next_token_is_keyword (parser, RID_AT_CATCH))
    {
      ಸಂರಚನಾ c_parm *parm;
      ವೃಕ್ಷ parameter_declaration = error_mark_ಗಂಟು;
      ತಾರ್ಕಿಕ seen_open_paren = ಅಸತ್ಯ;

      c_parser_consume_token (parser);
      matching_parens parens;
      ಯದಿ (!parens.require_open (parser))
	seen_open_paren = ಸತ್ಯ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_ವೃಕ್ಷ;
	}
      ಅನ್ಯಥಾ
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_ವೃಕ್ಷ, ಅಸತ್ಯ);
	  ಯದಿ (parm == ರಿಕ್ತ)
	    parameter_declaration = error_mark_ಗಂಟು;
	  ಅನ್ಯಥಾ
	    parameter_declaration = grokparm (parm, ರಿಕ್ತ);
	}
      ಯದಿ (seen_open_paren)
	parens.require_close (parser);
      ಅನ್ಯಥಾ
	{
	  /* If there was no open parenthesis, we are recovering from
	     an error, and we are trying to figure out what mistake
	     the user has made.  */

	  /* If there is an immediate closing parenthesis, the user
	     probably forgot the opening one (ie, they typed "@catch
	     NSException *e)".  Parse the closing parenthesis and keep
	     going.  */
	  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      ಯದಿ (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_finish_catch_clause ();
    }
  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_AT_FINALLY))
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_objc_synchronized_statement (c_parser *parser)
{
  location_t loc;
  ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, stmt;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ce = c_parser_expression (parser);
      ce = convert_lvalue_to_rvalue (loc, ce, ಅಸತ್ಯ, ಅಸತ್ಯ);
      ಅಭಿವ್ಯಕ್ತಿ = ce.ಮೌಲ್ಯ;
      ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ರಿಕ್ತ);
      parens.skip_until_found_close (parser);
    }
  ಅನ್ಯಥಾ
    ಅಭಿವ್ಯಕ್ತಿ = error_mark_ಗಂಟು;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, ಅಭಿವ್ಯಕ್ತಿ, stmt);
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  ವೃಕ್ಷ ಮೌಲ್ಯ = token->ಮೌಲ್ಯ;
  ಯದಿ (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      ಪ್ರತ್ಯಾಗಮ ಮೌಲ್ಯ;
    }
  ಯದಿ (token->type != CPP_KEYWORD)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  ವಿಕಲ್ಪ (token->keyword)
    {
    ಪಕ್ಷ RID_ENUM:
    ಪಕ್ಷ RID_STRUCT:
    ಪಕ್ಷ RID_UNION:
    ಪಕ್ಷ RID_IF:
    ಪಕ್ಷ RID_ELSE:
    ಪಕ್ಷ RID_WHILE:
    ಪಕ್ಷ RID_DO:
    ಪಕ್ಷ RID_FOR:
    ಪಕ್ಷ RID_SWITCH:
    ಪಕ್ಷ RID_CASE:
    ಪಕ್ಷ RID_DEFAULT:
    ಪಕ್ಷ RID_BREAK:
    ಪಕ್ಷ RID_CONTINUE:
    ಪಕ್ಷ RID_RETURN:
    ಪಕ್ಷ RID_GOTO:
    ಪಕ್ಷ RID_ASM:
    ಪಕ್ಷ RID_SIZEOF:
    ಪಕ್ಷ RID_TYPEOF:
    ಪಕ್ಷ RID_TYPEOF_UNQUAL:
    ಪಕ್ಷ RID_ALIGNOF:
    ಪಕ್ಷ RID_UNSIGNED:
    ಪಕ್ಷ RID_LONG:
    ಪಕ್ಷ RID_CONST:
    ಪಕ್ಷ RID_SHORT:
    ಪಕ್ಷ RID_VOLATILE:
    ಪಕ್ಷ RID_SIGNED:
    ಪಕ್ಷ RID_RESTRICT:
    ಪಕ್ಷ RID_COMPLEX:
    ಪಕ್ಷ RID_IN:
    ಪಕ್ಷ RID_OUT:
    ಪಕ್ಷ RID_INOUT:
    ಪಕ್ಷ RID_BYCOPY:
    ಪಕ್ಷ RID_BYREF:
    ಪಕ್ಷ RID_ONEWAY:
    ಪಕ್ಷ RID_INT:
    ಪಕ್ಷ RID_CHAR:
    ಪಕ್ಷ RID_FLOAT:
    ಪಕ್ಷ RID_DOUBLE:
    CASE_RID_FLOATN_NX:
    ಪಕ್ಷ RID_VOID:
    ಪಕ್ಷ RID_BOOL:
    ಪಕ್ಷ RID_ATOMIC:
    ಪಕ್ಷ RID_AUTO_TYPE:
    ಪಕ್ಷ RID_INT_N_0:
    ಪಕ್ಷ RID_INT_N_1:
    ಪಕ್ಷ RID_INT_N_2:
    ಪಕ್ಷ RID_INT_N_3:
      c_parser_consume_token (parser);
      ಪ್ರತ್ಯಾಗಮ ಮೌಲ್ಯ;
    ಸ್ವಭಾವ:
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_objc_selector_arg (c_parser *parser)
{
  ವೃಕ್ಷ sel = c_parser_objc_selector (parser);
  ವೃಕ್ಷ list = NULL_ವೃಕ್ಷ;
  ಯದಿ (sel
      && c_parser_next_token_is_not (parser, CPP_COLON)
      && c_parser_next_token_is_not (parser, CPP_SCOPE))
    ಪ್ರತ್ಯಾಗಮ sel;
  ಯಾವತ್ (ಸತ್ಯ)
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_ವೃಕ್ಷ_list (sel, NULL_ವೃಕ್ಷ));
	  list = chainon (list, build_ವೃಕ್ಷ_list (NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ));
	}
      ಅನ್ಯಥಾ
	{
	  ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    ಪ್ರತ್ಯಾಗಮ list;
	  list = chainon (list, build_ವೃಕ್ಷ_list (sel, NULL_ವೃಕ್ಷ));
	}
      sel = c_parser_objc_selector (parser);
      ಯದಿ (!sel
	  && c_parser_next_token_is_not (parser, CPP_COLON)
	  && c_parser_next_token_is_not (parser, CPP_SCOPE))
	ಭಙ್ಗ;
    }
  ಪ್ರತ್ಯಾಗಮ list;
}

/* Parse an objc-receiver.

   objc-receiver:
     expression
     class-name
     type-name
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  ಯದಿ (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
    {
      ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      c_parser_consume_token (parser);
      ಪ್ರತ್ಯಾಗಮ objc_get_class_reference (id);
    }
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ce = c_parser_expression (parser);
  ce = convert_lvalue_to_rvalue (loc, ce, ಅಸತ್ಯ, ಅಸತ್ಯ);
  ಪ್ರತ್ಯಾಗಮ c_fully_fold (ce.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_objc_message_args (c_parser *parser)
{
  ವೃಕ್ಷ sel = c_parser_objc_selector (parser);
  ವೃಕ್ಷ list = NULL_ವೃಕ್ಷ;
  ಯದಿ (sel && c_parser_next_token_is_not (parser, CPP_COLON))
    ಪ್ರತ್ಯಾಗಮ sel;
  ಯಾವತ್ (ಸತ್ಯ)
    {
      ವೃಕ್ಷ keywordexpr;
      ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_ವೃಕ್ಷ_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      ಯದಿ (!sel && c_parser_next_token_is_not (parser, CPP_COLON))
	ಭಙ್ಗ;
    }
  ಪ್ರತ್ಯಾಗಮ list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_objc_keywordexpr (c_parser *parser)
{
  ವೃಕ್ಷ ret;
  vec<ವೃಕ್ಷ, va_gc> *ಅಭಿವ್ಯಕ್ತಿ_list = c_parser_ಅಭಿವ್ಯಕ್ತಿ_list (parser, ಸತ್ಯ, ಸತ್ಯ,
						ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ);
  ಯದಿ (vec_safe_length (ಅಭಿವ್ಯಕ್ತಿ_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*ಅಭಿವ್ಯಕ್ತಿ_list)[0];
    }
  ಅನ್ಯಥಾ
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_ವೃಕ್ಷ_list_vec (ಅಭಿವ್ಯಕ್ತಿ_list);
    }
  release_ವೃಕ್ಷ_vector (ಅಭಿವ್ಯಕ್ತಿ_list);
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_objc_diagnose_bad_element_prefix (c_parser *parser,
					   ಸಂರಚನಾ c_declspecs *specs)
{
  ಯದಿ (!specs->declspecs_seen_p || specs->non_sc_seen_p
      || specs->typespec_kind != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_to_end_of_block_or_statement (parser);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }
  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
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
ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_objc_at_property_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY));
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);  /* Eat '@property'.  */

  /* Parse the optional attribute list.

     A list of parsed, but not verified, attributes.  */
  vec<property_attribute_info *> prop_attr_list = vNULL;

  ತಾರ್ಕಿಕ syntax_error = ಅಸತ್ಯ;
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_start = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = ಸತ್ಯ;

      /* Allow @property (), with a warning.  */
      location_t attr_end = c_parser_peek_token (parser)->location;

      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_end, attr_start, attr_end);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      ಅನ್ಯಥಾ
	ಯಾವತ್ (ಸತ್ಯ)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_start = token->location;
	    attr_end = get_finish (token->location);
	    location_t attr_comb = make_location (attr_start, attr_start,
						  attr_end);

	    ಯದಿ (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		ಯದಿ (token->type == CPP_CLOSE_PAREN)
		  ಭಙ್ಗ;
		c_parser_consume_token (parser);
		ಅನುವರ್ತ;
	      }

	    ವೃಕ್ಷ attr_name = NULL_ವೃಕ್ಷ;
	    ಗಣನಾ rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    ತಾರ್ಕಿಕ add_at = ಅಸತ್ಯ;
	    ಯದಿ (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		ಯದಿ (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->ಮೌಲ್ಯ;
		    add_at = ಸತ್ಯ;
		  }
		ಅನ್ಯಥಾ
		  attr_name = ridpointers[(ಪೂರ್ಣಾಙ್ಕ)keyword];
	      }
	    ಅನ್ಯಥಾ ಯದಿ (token->type == CPP_NAME)
	      attr_name = token->ಮೌಲ್ಯ;
	    c_parser_consume_token (parser);

	    ಗಣನಾ objc_property_attribute_kind prop_kind
	      = objc_prop_attr_kind_for_rid (keyword);
	    property_attribute_info *prop
	      = ನೂತನ property_attribute_info (attr_name, attr_comb, prop_kind);
	    prop_attr_list.safe_ತಳ್ಳು (prop);

	    ವೃಕ್ಷ meth_name;
	    ವಿಕಲ್ಪ (prop->prop_kind)
	      {
	      ಸ್ವಭಾವ: ಭಙ್ಗ;
	      ಪಕ್ಷ OBJC_PROPERTY_ATTR_UNKNOWN:
		ಯದಿ (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    add_at ? "@" : "", IDENTIFIER_POINTER (attr_name));
		ಅನ್ಯಥಾ
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = ಸತ್ಯ;
		ಭಙ್ಗ;

	      ಪಕ್ಷ OBJC_PROPERTY_ATTR_GETTER:
	      ಪಕ್ಷ OBJC_PROPERTY_ATTR_SETTER:
		ಯದಿ (c_parser_next_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = ಸತ್ಯ;
		    ಭಙ್ಗ;
		  }
		token = c_parser_peek_token (parser);
		attr_end = token->location;
		c_parser_consume_token (parser); /* eat the = */
		ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = ಸತ್ಯ;
		    ಭಙ್ಗ;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_end = get_finish (token->location);
		meth_name = token->ಮೌಲ್ಯ;
		c_parser_consume_token (parser);
		ಯದಿ (prop->prop_kind == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    ಯದಿ (c_parser_next_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_end, attr_start,
						   attr_end);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = ಸತ್ಯ;
		      }
		    ಅನ್ಯಥಾ
		      {
			attr_end = get_finish (c_parser_peek_token
					       (parser)->location);
			c_parser_consume_token (parser);
		      }
		    attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		  }
		ಅನ್ಯಥಾ
		  attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		prop->ident = meth_name;
		/* Updated location including all that was successfully
		   parsed.  */
		prop->prop_loc = attr_comb;
		ಭಙ್ಗ;
	    }

	  /* If we see a comma here, then keep going - even if we already
	     saw a syntax error.  For simple mistakes e.g. (assign, getter=x)
	     this makes a more useful output and avoid spurious warnings about
	     missing attributes that are, in fact, specified after the one with
	     the syntax error.  */
	  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ಅನ್ಯಥಾ
	    ಭಙ್ಗ;
	}
      parser->objc_property_attr_context = ಅಸತ್ಯ;

      ಯದಿ (syntax_error && c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      ಅನ್ಯಥಾ
	syntax_error = ಅಸತ್ಯ, parens.skip_until_found_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  ವೃಕ್ಷ properties = c_parser_struct_declaration (parser, ರಿಕ್ತ);

  ಯದಿ (properties == error_mark_ಗಂಟು)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, ರಿಕ್ತ);
  ಅನ್ಯಥಾ
    {
      ಯದಿ (properties == NULL_ವೃಕ್ಷ)
	c_parser_error (parser, "expected identifier");
      ಅನ್ಯಥಾ
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  ಪ್ರತಿ (; properties; properties = ವೃಕ್ಷ_CHAIN (properties))
	    objc_add_property_declaration (loc, copy_ಗಂಟು (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  ಯಾವತ್ (!prop_attr_list.is_empty())
    delete prop_attr_list.ತೆಗೆ ();
  prop_attr_list.release ();
  parser->error = ಅಸತ್ಯ;
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
ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_objc_at_synthesize_declaration (c_parser *parser)
{
  ವೃಕ್ಷ list = NULL_ವೃಕ್ಷ;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  ಯಾವತ್ (ಸತ್ಯ)
    {
      ವೃಕ್ಷ property, ivar;
      ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, ರಿಕ್ತ);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = ಅಸತ್ಯ;
	  ಪ್ರತ್ಯಾಗಮ;
	}
      property = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_SEMICOLON, ರಿಕ್ತ);
	      parser->error = ಅಸತ್ಯ;
	      ಪ್ರತ್ಯಾಗಮ;
	    }
	  ivar = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ
	ivar = NULL_ವೃಕ್ಷ;
      list = chainon (list, build_ವೃಕ್ಷ_list (ivar, property));
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
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
ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_objc_at_dynamic_declaration (c_parser *parser)
{
  ವೃಕ್ಷ list = NULL_ವೃಕ್ಷ;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  ಯಾವತ್ (ಸತ್ಯ)
    {
      ವೃಕ್ಷ property;
      ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, ರಿಕ್ತ);
	  parser->error = ಅಸತ್ಯ;
	  ಪ್ರತ್ಯಾಗಮ;
	}
      property = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      list = chainon (list, build_ವೃಕ್ಷ_list (NULL_ವೃಕ್ಷ, property));
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_add_dynamic_declaration (loc, list);
}


/* Parse a pragma GCC ivdep.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parse_pragma_ivdep (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* Parse a pragma GCC novector.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* Parse a pragma GCC unroll.  */

ಸ್ಥಿರ unsigned short
c_parser_pragma_unroll (c_parser *parser)
{
  unsigned short unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ).ಮೌಲ್ಯ;
  mark_exp_read (ಅಭಿವ್ಯಕ್ತಿ);
  ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ರಿಕ್ತ);
  HOST_WIDE_INT lunroll = 0;
  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ))
      || ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) != INTEGER_CST
      || (lunroll = ವೃಕ್ಷ_to_shwi (ಅಭಿವ್ಯಕ್ತಿ)) < 0
      || lunroll >= USHRT_MAX)
    {
      error_at (location, "%<#pragma GCC unroll%> requires an"
		" assignment-expression that evaluates to a non-negative"
		" integral constant less than %u", USHRT_MAX);
      unroll = 0;
    }
  ಅನ್ಯಥಾ
    {
      unroll = (unsigned short)lunroll;
      ಯದಿ (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_to_pragma_eol (parser);
  ಪ್ರತ್ಯಾಗಮ unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_pragma (c_parser *parser, ಗಣನಾ pragma_context context, ತಾರ್ಕಿಕ *if_p,
		 ವೃಕ್ಷ before_labels)
{
  unsigned ಪೂರ್ಣಾಙ್ಕ id;
  ಧ್ರುವ ವರ್ಣ *construct = ರಿಕ್ತ;

  ಒಳಹರಿವು_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_kind;
  gcc_assert (id != PRAGMA_NONE);
  ಯದಿ (parser->omp_for_parse_state
      && parser->omp_for_parse_state->in_intervening_code
      && id >= PRAGMA_OMP__START_ && id <= PRAGMA_OMP__LAST_
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	ಒಳಹರಿವು_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->fail = ಸತ್ಯ;
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ರಿಕ್ತ);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  ವಿಕಲ್ಪ (id)
    {
    ಪಕ್ಷ PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OACC_ENTER_DATA:
      ಯದಿ (context != pragma_compound)
	{
	  construct = "acc enter data";
	in_compound:
	  ಯದಿ (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ರಿಕ್ತ);
	      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	    }
	  ಗಚ್ಛ bad_stmt;
	}
      c_parser_oacc_enter_exit_data (parser, ಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OACC_EXIT_DATA:
      ಯದಿ (context != pragma_compound)
	{
	  construct = "acc exit data";
	  ಗಚ್ಛ in_compound;
	}
      c_parser_oacc_enter_exit_data (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OACC_ROUTINE:
      ಯದಿ (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ರಿಕ್ತ);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
      c_parser_oacc_routine (parser, context);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OACC_UPDATE:
      ಯದಿ (context != pragma_compound)
	{
	  construct = "acc update";
	  ಗಚ್ಛ in_compound;
	}
      c_parser_oacc_update (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_BARRIER:
      ಯದಿ (context != pragma_compound)
	{
	  construct = "omp barrier";
	  ಗಚ್ಛ in_compound;
	}
      c_parser_omp_barrier (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_DEPOBJ:
      ಯದಿ (context != pragma_compound)
	{
	  construct = "omp depobj";
	  ಗಚ್ಛ in_compound;
	}
      c_parser_omp_depobj (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_FLUSH:
      ಯದಿ (context != pragma_compound)
	{
	  construct = "omp flush";
	  ಗಚ್ಛ in_compound;
	}
      c_parser_omp_flush (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_INTEROP:
      ಯದಿ (context != pragma_compound)
	{
	  construct = "omp interop";
	  ಗಚ್ಛ in_compound;
	}
      c_parser_omp_interop (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_TASKWAIT:
      ಯದಿ (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  ಗಚ್ಛ in_compound;
	}
      c_parser_omp_taskwait (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_TASKYIELD:
      ಯದಿ (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  ಗಚ್ಛ in_compound;
	}
      c_parser_omp_taskyield (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_CANCEL:
      ಯದಿ (context != pragma_compound)
	{
	  construct = "omp cancel";
	  ಗಚ್ಛ in_compound;
	}
      c_parser_omp_cancel (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_CANCELLATION_POINT:
      ಪ್ರತ್ಯಾಗಮ c_parser_omp_cancellation_point (parser, context);

    ಪಕ್ಷ PRAGMA_OMP_GROUPPRIVATE:
      c_parser_omp_groupprivate (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_THREADPRIVATE:
      c_parser_omp_threadprivate (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_TARGET:
      ಪ್ರತ್ಯಾಗಮ c_parser_omp_target (parser, context, if_p);

    ಪಕ್ಷ PRAGMA_OMP_BEGIN:
      c_parser_omp_begin (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_END:
      c_parser_omp_end (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_SCAN:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ರಿಕ್ತ);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ರಿಕ್ತ);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_DECLARE:
      ಪ್ರತ್ಯಾಗಮ c_parser_omp_declare (parser, context);

    ಪಕ್ಷ PRAGMA_OMP_REQUIRES:
      ಯದಿ (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ರಿಕ್ತ);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
      c_parser_omp_requires (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_ALLOCATE:
      c_parser_omp_allocate (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_ASSUMES:
      ಯದಿ (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp assumes");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ರಿಕ್ತ);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
      c_parser_omp_assumes (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OMP_ERROR:
      ಪ್ರತ್ಯಾಗಮ c_parser_omp_error (parser, context);

    ಪಕ್ಷ PRAGMA_OMP_ORDERED:
      ಪ್ರತ್ಯಾಗಮ c_parser_omp_ordered (parser, context, if_p);

    ಪಕ್ಷ PRAGMA_NOVECTOR:
    ಪಕ್ಷ PRAGMA_UNROLL:
    ಪಕ್ಷ PRAGMA_IVDEP:
      {
	ತಾರ್ಕಿಕ novector = ಅಸತ್ಯ;
	unsigned short unroll = 0;
	ತಾರ್ಕಿಕ ivdep = ಅಸತ್ಯ;

	ವಿಕಲ್ಪ (id)
	  {
	  ಪಕ್ಷ PRAGMA_NOVECTOR:
	    novector = c_parse_pragma_novector (parser);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ PRAGMA_UNROLL:
	    unroll = c_parser_pragma_unroll (parser);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ PRAGMA_IVDEP:
	    ivdep = c_parse_pragma_ivdep (parser);
	    ಭಙ್ಗ;
	  ಸ್ವಭಾವ:
	    gcc_unreachable ();
	  }

	c_token *tok = c_parser_peek_token (parser);
	ತಾರ್ಕಿಕ has_more = tok->type == CPP_PRAGMA;
	ಯಾವತ್ (has_more)
	  {
	    ವಿಕಲ್ಪ (tok->pragma_kind)
	      {
	      ಪಕ್ಷ PRAGMA_IVDEP:
		ivdep = c_parse_pragma_ivdep (parser);
		ಭಙ್ಗ;
	      ಪಕ್ಷ PRAGMA_UNROLL:
		unroll = c_parser_pragma_unroll (parser);
		ಭಙ್ಗ;
	      ಪಕ್ಷ PRAGMA_NOVECTOR:
		novector = c_parse_pragma_novector (parser);
		ಭಙ್ಗ;
	      ಸ್ವಭಾವ:
		has_more = ಅಸತ್ಯ;
		ಭಙ್ಗ;
	      }
	    tok = c_parser_peek_token (parser);
	    has_more = has_more && tok->type == CPP_PRAGMA;
	  }
	ಯದಿ (!c_parser_next_token_is_keyword (parser, RID_FOR)
	    && !c_parser_next_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_next_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	  }
	ಯದಿ (c_parser_next_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	ಅನ್ಯಥಾ
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ರಿಕ್ತ);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ PRAGMA_OACC_WAIT:
      ಯದಿ (context != pragma_compound)
	{
	  construct = "acc wait";
	  ಗಚ್ಛ in_compound;
	}
	/* FALL THROUGH.  */

    ಸ್ವಭಾವ:
      ಯದಿ (id < PRAGMA_FIRST_EXTERNAL)
	{
	  ಯದಿ (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ರಿಕ್ತ);
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    }
	  c_parser_omp_construct (parser, if_p);
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	}
      ಭಙ್ಗ;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = ಸತ್ಯ;
  c_parser_skip_to_pragma_eol (parser);

  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* The interface the pragma parsers have to the lexer.  */

ಗಣನಾ cpp_ttype
pragma_lex (ವೃಕ್ಷ *ಮೌಲ್ಯ, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  ಗಣನಾ cpp_ttype ret = tok->type;

  *ಮೌಲ್ಯ = tok->ಮೌಲ್ಯ;
  ಯದಿ (loc)
    *loc = tok->location;

  ಯದಿ (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  ಅನ್ಯಥಾ ಯದಿ (ret == CPP_STRING)
    *ಮೌಲ್ಯ = c_parser_string_literal (the_parser, ಅಸತ್ಯ, ಅಸತ್ಯ).ಮೌಲ್ಯ;
  ಅನ್ಯಥಾ
    {
      ಯದಿ (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  ಪ್ರತ್ಯಾಗಮ ret;
}

ಶೂನ್ಯ
pragma_lex_discard_to_eol ()
{
  cpp_ttype type;
  ಕುರು
    {
      type = c_parser_peek_token (the_parser)->type;
      gcc_assert (type != CPP_EOF);
      c_parser_consume_token (the_parser);
    } ಯಾವತ್ (type != CPP_PRAGMA_EOL);
}

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  ವೃಕ್ಷ name = ರಿಕ್ತ;

  parser->lex_joined_string = ಸತ್ಯ;
  c_parser_consume_pragma (parser);
  ಯದಿ (c_parser_next_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      c_parser_consume_token (parser);
    }
  ಅನ್ಯಥಾ
    c_parser_error (parser, "expected string literal");
  c_parser_skip_to_pragma_eol (parser);
  parser->lex_joined_string = ಅಸತ್ಯ;

  ಯದಿ (name)
    c_common_pch_pragma (parse_in, ವೃಕ್ಷ_STRING_POINTER (name));
}

/* OpenACC and OpenMP parsing routines.  */

/* Returns name of the next clause.
   If the clause is not recognized PRAGMA_OMP_CLAUSE_NONE is returned and
   the token is not consumed.  Otherwise appropriate pragma_omp_clause is
   returned and the token is consumed.  */

ಸ್ಥಿರ pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause result = PRAGMA_OMP_CLAUSE_NONE;

  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_AUTO))
    result = PRAGMA_OACC_CLAUSE_AUTO;
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_IF))
    result = PRAGMA_OMP_CLAUSE_IF;
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    result = PRAGMA_OMP_CLAUSE_DEFAULT;
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_FOR))
    result = PRAGMA_OMP_CLAUSE_FOR;
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);

      ವಿಕಲ್ಪ (p[0])
	{
	ಪಕ್ಷ 'a':
	  ಯದಿ (!strcmp ("affinity", p))
	    result = PRAGMA_OMP_CLAUSE_AFFINITY;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("aligned", p))
	    result = PRAGMA_OMP_CLAUSE_ALIGNED;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("allocate", p))
	    result = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("async", p))
	    result = PRAGMA_OACC_CLAUSE_ASYNC;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("attach", p))
	    result = PRAGMA_OACC_CLAUSE_ATTACH;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'b':
	  ಯದಿ (!strcmp ("bind", p))
	    result = PRAGMA_OMP_CLAUSE_BIND;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'c':
	  ಯದಿ (!strcmp ("collapse", p))
	    result = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("copy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("copyin", p))
	    result = PRAGMA_OMP_CLAUSE_COPYIN;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("copyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
          ಅನ್ಯಥಾ ಯದಿ (!strcmp ("copyprivate", p))
	    result = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("create", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'd':
	  ಯದಿ (!strcmp ("defaultmap", p))
	    result = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("delete", p))
	    result = PRAGMA_OACC_CLAUSE_DELETE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("depend", p))
	    result = PRAGMA_OMP_CLAUSE_DEPEND;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("destroy", p))
	    result = PRAGMA_OMP_CLAUSE_DESTROY;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("detach", p))
	    result = PRAGMA_OACC_CLAUSE_DETACH;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("device", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("deviceptr", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("device_resident", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("device_type", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("dist_schedule", p))
	    result = PRAGMA_OMP_CLAUSE_DIST_SCHEDULE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("doacross", p))
	    result = PRAGMA_OMP_CLAUSE_DOACROSS;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("dyn_groupprivate", p))
	    result = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'e':
	  ಯದಿ (!strcmp ("enter", p))
	    result = PRAGMA_OMP_CLAUSE_ENTER;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'f':
	  ಯದಿ (!strcmp ("filter", p))
	    result = PRAGMA_OMP_CLAUSE_FILTER;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("final", p))
	    result = PRAGMA_OMP_CLAUSE_FINAL;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("finalize", p))
	    result = PRAGMA_OACC_CLAUSE_FINALIZE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("firstprivate", p))
	    result = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("from", p))
	    result = PRAGMA_OMP_CLAUSE_FROM;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("full", p))
	    result = PRAGMA_OMP_CLAUSE_FULL;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'g':
	  ಯದಿ (!strcmp ("gang", p))
	    result = PRAGMA_OACC_CLAUSE_GANG;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("grainsize", p))
	    result = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'h':
	  ಯದಿ (!strcmp ("has_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("hint", p))
	    result = PRAGMA_OMP_CLAUSE_HINT;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("host", p))
	    result = PRAGMA_OACC_CLAUSE_HOST;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'i':
	  ಯದಿ (!strcmp ("if_present", p))
	    result = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("in_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_IN_REDUCTION;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("inbranch", p))
	    result = PRAGMA_OMP_CLAUSE_INBRANCH;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("independent", p))
	    result = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("indirect", p))
	    result = PRAGMA_OMP_CLAUSE_INDIRECT;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("init", p))
	    result = PRAGMA_OMP_CLAUSE_INIT;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("is_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("interop", p))
	    result = PRAGMA_OMP_CLAUSE_INTEROP;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'l':
	  ಯದಿ (!strcmp ("lastprivate", p))
	    result = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("linear", p))
	    result = PRAGMA_OMP_CLAUSE_LINEAR;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("link", p))
	    result = PRAGMA_OMP_CLAUSE_LINK;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("local", p))
	    result = PRAGMA_OMP_CLAUSE_LOCAL;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'm':
	  ಯದಿ (!strcmp ("map", p))
	    result = PRAGMA_OMP_CLAUSE_MAP;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("mergeable", p))
	    result = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'n':
	  ಯದಿ (!strcmp ("no_create", p))
	    result = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("nocontext", p))
	    result = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("nogroup", p))
	    result = PRAGMA_OMP_CLAUSE_NOGROUP;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("nohost", p))
	    result = PRAGMA_OACC_CLAUSE_NOHOST;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("nontemporal", p))
	    result = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("notinbranch", p))
	    result = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("novariants", p))
	    result = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("nowait", p))
	    result = PRAGMA_OMP_CLAUSE_NOWAIT;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("num_gangs", p))
	    result = PRAGMA_OACC_CLAUSE_ಅಂಕೆ_GANGS;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("num_tasks", p))
	    result = PRAGMA_OMP_CLAUSE_ಅಂಕೆ_TASKS;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("num_teams", p))
	    result = PRAGMA_OMP_CLAUSE_ಅಂಕೆ_TEAMS;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("num_threads", p))
	    result = PRAGMA_OMP_CLAUSE_ಅಂಕೆ_THREADS;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("num_workers", p))
	    result = PRAGMA_OACC_CLAUSE_ಅಂಕೆ_WORKERS;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'o':
	  ಯದಿ (!strcmp ("ordered", p))
	    result = PRAGMA_OMP_CLAUSE_ORDERED;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("order", p))
	    result = PRAGMA_OMP_CLAUSE_ORDER;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'p':
	  ಯದಿ (!strcmp ("parallel", p))
	    result = PRAGMA_OMP_CLAUSE_PARALLEL;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("partial", p))
	    result = PRAGMA_OMP_CLAUSE_PARTIAL;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("present", p))
	    result = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("present_or_copy", p)
		   || !strcmp ("pcopy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("present_or_copyin", p)
		   || !strcmp ("pcopyin", p))
	    result = PRAGMA_OACC_CLAUSE_COPYIN;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("present_or_copyout", p)
		   || !strcmp ("pcopyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("present_or_create", p)
		   || !strcmp ("pcreate", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("priority", p))
	    result = PRAGMA_OMP_CLAUSE_PRIORITY;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("private", p))
	    result = PRAGMA_OMP_CLAUSE_PRIVATE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("proc_bind", p))
	    result = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'r':
	  ಯದಿ (!strcmp ("reduction", p))
	    result = PRAGMA_OMP_CLAUSE_REDUCTION;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 's':
	  ಯದಿ (!strcmp ("safelen", p))
	    result = PRAGMA_OMP_CLAUSE_SAFELEN;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("schedule", p))
	    result = PRAGMA_OMP_CLAUSE_SCHEDULE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("sections", p))
	    result = PRAGMA_OMP_CLAUSE_SECTIONS;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("self", p))
	    result = PRAGMA_OACC_CLAUSE_SELF;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("seq", p))
	    result = PRAGMA_OACC_CLAUSE_SEQ;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("shared", p))
	    result = PRAGMA_OMP_CLAUSE_SHARED;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("simd", p))
	    result = PRAGMA_OMP_CLAUSE_SIMD;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("simdlen", p))
	    result = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 't':
	  ಯದಿ (!strcmp ("task_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("taskgroup", p))
	    result = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("thread_limit", p))
	    result = PRAGMA_OMP_CLAUSE_THREAD_LIMIT;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("threads", p))
	    result = PRAGMA_OMP_CLAUSE_THREADS;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("tile", p))
	    result = PRAGMA_OACC_CLAUSE_TILE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("to", p))
	    result = PRAGMA_OMP_CLAUSE_TO;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'u':
	  ಯದಿ (!strcmp ("uniform", p))
	    result = PRAGMA_OMP_CLAUSE_UNIFORM;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("untied", p))
	    result = PRAGMA_OMP_CLAUSE_UNTIED;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("use", p))
	    result = PRAGMA_OMP_CLAUSE_USE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("use_device", p))
	    result = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("use_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("use_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("uses_allocators", p))
	    result = PRAGMA_OMP_CLAUSE_USES_ALLOCATORS;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'v':
	  ಯದಿ (!strcmp ("vector", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("vector_length", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR_LENGTH;
	  ಭಙ್ಗ;
	ಪಕ್ಷ 'w':
	  ಯದಿ (!strcmp ("wait", p))
	    result = PRAGMA_OACC_CLAUSE_WAIT;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("worker", p))
	    result = PRAGMA_OACC_CLAUSE_WORKER;
	  ಭಙ್ಗ;
	}
    }

  ಯದಿ (result != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  ಪ್ರತ್ಯಾಗಮ result;
}

/* Validate that a clause of the given type does not already exist.  */

ಸ್ಥಿರ ಶೂನ್ಯ
check_no_duplicate_clause (ವೃಕ್ಷ clauses, ಗಣನಾ omp_clause_code code,
			   ಧ್ರುವ ವರ್ಣ *name)
{
  ಯದಿ (ವೃಕ್ಷ c = omp_find_clause (clauses, code))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, ವೃಕ್ಷ list)
{
  vec<ವೃಕ್ಷ, va_gc> *args;
  ವೃಕ್ಷ t, args_ವೃಕ್ಷ;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  args = c_parser_ಅಭಿವ್ಯಕ್ತಿ_list (parser, ಅಸತ್ಯ, ಸತ್ಯ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ);
  args_ವೃಕ್ಷ = build_ವೃಕ್ಷ_list_vec (args);

  ಪ್ರತಿ (t = args_ವೃಕ್ಷ; t; t = ವೃಕ್ಷ_CHAIN (t))
    {
      ವೃಕ್ಷ targ = ವೃಕ್ಷ_ಮೌಲ್ಯ (t);

      ಯದಿ (targ != error_mark_ಗಂಟು)
	{
	  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_ಗಂಟು;
	    }
	  ಅನ್ಯಥಾ
	    {
	      ವೃಕ್ಷ c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_ವೃಕ್ಷ_vector (args);
  parens.require_close (parser);
  ಪ್ರತ್ಯಾಗಮ list;
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

ಸಂರಚನಾ omp_dim
{
  ವೃಕ್ಷ ಕೆಳಗಿನ_bound, length;
  location_t loc;
  ತಾರ್ಕಿಕ no_colon;
  omp_dim (ವೃಕ್ಷ lb, ವೃಕ್ಷ len, location_t lo, ತಾರ್ಕಿಕ nc)
  : ಕೆಳಗಿನ_bound (lb), length (len), loc (lo), no_colon (nc) {}
};

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    ಗಣನಾ omp_clause_code kind, ವೃಕ್ಷ list,
			    ತಾರ್ಕಿಕ map_lvalue = ಅಸತ್ಯ)
{
  auto_vec<omp_dim> dims;
  ತಾರ್ಕಿಕ array_section_p;
  auto_vec<c_token> tokens;
  unsigned ಪೂರ್ಣಾಙ್ಕ tokens_avail = 0;
  c_token *saved_tokens = ರಿಕ್ತ;

  ಯಾವತ್ (1)
    {
      ವೃಕ್ಷ t = NULL_ವೃಕ್ಷ;
      location_t tloc = c_parser_peek_token (parser)->location;

      ಯದಿ (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
	    {
	      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
	      ಯದಿ (kind == OMP_CLAUSE_DEPEND
		  && c_parser_next_token_is_keyword (parser,
						     RID_OMP_ALL_MEMORY)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = ridpointers[RID_OMP_ALL_MEMORY];
		  c_parser_consume_token (parser);
		}
	      ಅನ್ಯಥಾ
		ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	      ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
		{
		  ವೃಕ್ಷ u = build_omp_clause (clause_loc, kind);
		  OMP_CLAUSE_DECL (u) = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      ಯದಿ (c_parser_next_token_is_not (parser, CPP_COMMA))
		ಭಙ್ಗ;

	      c_parser_consume_token (parser);
	      ಅನುವರ್ತ;
	    }

	  tokens.truncate (0);
	  unsigned ಪೂರ್ಣಾಙ್ಕ nesting_depth = 0;
	  ಯಾವತ್ (1)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      ವಿಕಲ್ಪ (token->type)
		{
		ಪಕ್ಷ CPP_EOF:
		ಪಕ್ಷ CPP_PRAGMA_EOL:
		  ಭಙ್ಗ;
		ಪಕ್ಷ CPP_OPEN_BRACE:
		ಪಕ್ಷ CPP_OPEN_PAREN:
		ಪಕ್ಷ CPP_OPEN_SQUARE:
		  ++nesting_depth;
		  ಗಚ್ಛ add;
		ಪಕ್ಷ CPP_CLOSE_BRACE:
		ಪಕ್ಷ CPP_CLOSE_PAREN:
		ಪಕ್ಷ CPP_CLOSE_SQUARE:
		  ಯದಿ (nesting_depth-- == 0)
		    ಭಙ್ಗ;
		  ಗಚ್ಛ add;
		ಪಕ್ಷ CPP_COMMA:
		  ಯದಿ (nesting_depth == 0)
		    ಭಙ್ಗ;
		  ಗಚ್ಛ add;
		ಸ್ವಭಾವ:
		add:
		  tokens.safe_ತಳ್ಳು (*token);
		  c_parser_consume_token (parser);
		  ಅನುವರ್ತ;
		}
	      ಭಙ್ಗ;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  memset (&eof_token, 0, ಪರಿಮಾಣ (eof_token));
	  eof_token.type = CPP_EOF;
	  tokens.safe_ತಳ್ಳು (eof_token);
	  tokens.safe_ತಳ್ಳು (eof_token);

	  saved_tokens = parser->tokens;
	  tokens_avail = parser->tokens_avail;
	  parser->tokens = tokens.address ();
	  parser->tokens_avail = tokens.length ();
	}
      ಅನ್ಯಥಾ ಯದಿ (map_lvalue
	       && (kind == OMP_CLAUSE_MAP
		   || kind == OMP_CLAUSE_TO
		   || kind == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  ತಾರ್ಕಿಕ save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = ಸತ್ಯ;
	  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
	    mark_exp_read (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  ವೃಕ್ಷ decl = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  ಯದಿ (ವೃಕ್ಷ_CODE (decl) == OMP_ARRAY_SECTION)
	    {
	      ಯಾವತ್ (ವೃಕ್ಷ_CODE (decl) == OMP_ARRAY_SECTION)
		{
		  ವೃಕ್ಷ ಕೆಳಗಿನ_bound = ವೃಕ್ಷ_OPERAND (decl, 1);
		  ವೃಕ್ಷ length = ವೃಕ್ಷ_OPERAND (decl, 2);
		  dims.safe_ತಳ್ಳು (omp_dim (ಕೆಳಗಿನ_bound, length, loc, ಅಸತ್ಯ));
		  decl = ವೃಕ್ಷ_OPERAND (decl, 0);
		}

	      ಯಾವತ್ (ವೃಕ್ಷ_CODE (decl) == ARRAY_REF
		     || ವೃಕ್ಷ_CODE (decl) == INDIRECT_REF
		     || ವೃಕ್ಷ_CODE (decl) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
		{
		  ಯದಿ (ವೃಕ್ಷ_CODE (decl) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
		    {
		      decl = ವೃಕ್ಷ_OPERAND (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (decl) == INDIRECT_REF)
		    {
		      dims.safe_ತಳ್ಳು (omp_dim (integer_zero_ಗಂಟು,
					       integer_one_ಗಂಟು, loc, ಸತ್ಯ));
		      decl = ವೃಕ್ಷ_OPERAND (decl, 0);
		    }
		  ಅನ್ಯಥಾ  /* ARRAY_REF. */
		    {
		      ವೃಕ್ಷ index = ವೃಕ್ಷ_OPERAND (decl, 1);
		      dims.safe_ತಳ್ಳು (omp_dim (index, integer_one_ಗಂಟು, loc,
					       ಸತ್ಯ));
		      decl = ವೃಕ್ಷ_OPERAND (decl, 0);
		    }
		}

	      ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = dims.length () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].ಕೆಳಗಿನ_bound,
						dims[i].length);
	    }
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (decl) == INDIRECT_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = ವೃಕ್ಷ_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_ಗಂಟು,
					      integer_one_ಗಂಟು);
	    }
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (decl) == ARRAY_REF)
	    {
	      ವೃಕ್ಷ idx = ವೃಕ್ಷ_OPERAND (decl, 1);

	      decl = ವೃಕ್ಷ_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_ಗಂಟು);
	    }
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (decl) == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ
		   || CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (decl))
	    decl = ವೃಕ್ಷ_OPERAND (decl, 0);

	  ವೃಕ್ಷ u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  ಗಚ್ಛ next_item;
	}

      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->ಮೌಲ್ಯ);

	  ಯದಿ (t == NULL_ವೃಕ್ಷ)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	      t = error_mark_ಗಂಟು;
	    }

	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).ಮೌಲ್ಯ;
      ಅನ್ಯಥಾ
	{
	  c_parser_error (parser, "expected identifier");
	  ಭಙ್ಗ;
	}

      ಯದಿ (t == error_mark_ಗಂಟು)
	;
      ಅನ್ಯಥಾ ಯದಿ (kind != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  ವಿಕಲ್ಪ (kind)
	    {
	    ಪಕ್ಷ OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      ಯದಿ (c_parser_peek_token (parser)->type != CPP_OPEN_SQUARE)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_ಗಂಟು;
		  ಭಙ್ಗ;
		}
	      /* FALLTHROUGH  */
	    ಪಕ್ಷ OMP_CLAUSE_MAP:
	    ಪಕ್ಷ OMP_CLAUSE_FROM:
	    ಪಕ್ಷ OMP_CLAUSE_TO:
	    start_component_ref:
	      ಯಾವತ್ (c_parser_next_token_is (parser, CPP_DOT)
		     || c_parser_next_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  ಯದಿ (c_parser_next_token_is (parser, CPP_DEREF))
		    {
		      c_ಅಭಿವ್ಯಕ್ತಿ t_ಅಭಿವ್ಯಕ್ತಿ;
		      t_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = t;
		      t_ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
		      t_ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
		      set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&t_ಅಭಿವ್ಯಕ್ತಿ, op_loc, op_loc);
		      t_ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
		      t_ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (op_loc, t_ಅಭಿವ್ಯಕ್ತಿ,
							 ಸತ್ಯ, ಅಸತ್ಯ);
		      t = build_indirect_ref (op_loc, t_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, RO_ARROW);
		      arrow_loc = t_ಅಭಿವ್ಯಕ್ತಿ.get_location ();
		    }
		  c_parser_consume_token (parser);
		  ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_ಗಂಟು;
		      ಭಙ್ಗ;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  ವೃಕ್ಷ ident = comp_tok->ಮೌಲ್ಯ;
		  location_t comp_loc = comp_tok->location;
		  c_parser_consume_token (parser);
		  t = build_component_ref (op_loc, t, ident, comp_loc,
					   arrow_loc);
		}
	      /* FALLTHROUGH  */
	    ಪಕ್ಷ OMP_CLAUSE_AFFINITY:
	    ಪಕ್ಷ OMP_CLAUSE_DEPEND:
	    ಪಕ್ಷ OMP_CLAUSE_REDUCTION:
	    ಪಕ್ಷ OMP_CLAUSE_IN_REDUCTION:
	    ಪಕ್ಷ OMP_CLAUSE_TASK_REDUCTION:
	    ಪಕ್ಷ OMP_CLAUSE_HAS_DEVICE_ADDR:
	      array_section_p = ಅಸತ್ಯ;
	      dims.truncate (0);
	      ಯಾವತ್ (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  ವೃಕ್ಷ ಕೆಳಗಿನ_bound = NULL_ವೃಕ್ಷ, length = NULL_ವೃಕ್ಷ;
		  ತಾರ್ಕಿಕ no_colon = ಅಸತ್ಯ;

		  c_parser_consume_token (parser);
		  ಯದಿ (!c_parser_next_token_is (parser, CPP_COLON))
		    {
		      location_t ಅಭಿವ್ಯಕ್ತಿ_loc
			= c_parser_peek_token (parser)->location;
		      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_expression (parser);
		      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ,
						       ಅಸತ್ಯ, ಸತ್ಯ);
		      ಕೆಳಗಿನ_bound = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
		      loc = ಅಭಿವ್ಯಕ್ತಿ_loc;
		    }
		  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    {
		      length = integer_one_ಗಂಟು;
		      no_colon = ಸತ್ಯ;
		    }
		  ಅನ್ಯಥಾ
		    {
		      /* Look for `:'.  */
		      ಯದಿ (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_ಗಂಟು;
			  ಭಙ್ಗ;
			}
		      array_section_p = ಸತ್ಯ;
		      ಯದಿ (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
			{
			  location_t ಅಭಿವ್ಯಕ್ತಿ_loc
			    = c_parser_peek_token (parser)->location;
			  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_expression (parser);
			  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ,
							   ಅಸತ್ಯ, ಸತ್ಯ);
			  length = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
			}
		    }
		  /* Look for the closing `]'.  */
		  ಯದಿ (!c_parser_require (parser, CPP_CLOSE_SQUARE,
					 "expected %<]%>"))
		    {
		      t = error_mark_ಗಂಟು;
		      ಭಙ್ಗ;
		    }

		  dims.safe_ತಳ್ಳು (omp_dim (ಕೆಳಗಿನ_bound, length, loc, no_colon));
		}

	      ಯದಿ (t != error_mark_ಗಂಟು)
		{
		  ಯದಿ ((kind == OMP_CLAUSE_MAP
		       || kind == OMP_CLAUSE_FROM
		       || kind == OMP_CLAUSE_TO)
		      && !array_section_p
		      && (c_parser_next_token_is (parser, CPP_DOT)
			  || c_parser_next_token_is (parser, CPP_DEREF)))
		    {
		      ಪ್ರತಿ (unsigned i = 0; i < dims.length (); i++)
			{
			  gcc_assert (dims[i].length == integer_one_ಗಂಟು);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].ಕೆಳಗಿನ_bound);
			}
		      ಗಚ್ಛ start_component_ref;
		    }
		  ಅನ್ಯಥಾ
		    ಪ್ರತಿ (unsigned i = 0; i < dims.length (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].ಕೆಳಗಿನ_bound,
						   dims[i].length);
		}

	      ಯದಿ ((kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_ಗಂಟು
		  && parser->tokens_avail != 2)
		{
		  ಯದಿ (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_ಗಂಟು;
		    }
		  ಅನ್ಯಥಾ
		    {
		      parser->tokens = tokens.address ();
		      parser->tokens_avail = tokens.length ();

		      t = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ).ಮೌಲ್ಯ;
		      ಯದಿ (t != error_mark_ಗಂಟು && parser->tokens_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_ಗಂಟು;
			}
		    }
		}
	      ಭಙ್ಗ;
	    ಸ್ವಭಾವ:
	      ಭಙ್ಗ;
	    }

	  ಯದಿ (t != error_mark_ಗಂಟು)
	    {
	      ವೃಕ್ಷ u = build_omp_clause (clause_loc, kind);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      ಅನ್ಯಥಾ  /* kind == OMP_CLAUSE_ERROR */
	list = ವೃಕ್ಷ_cons (t, build_empty_stmt (tloc), list);

      ಯದಿ (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}

    next_item:
      ಯದಿ (c_parser_next_token_is_not (parser, CPP_COMMA))
	ಭಙ್ಗ;

      c_parser_consume_token (parser);
    }

  ಪ್ರತ್ಯಾಗಮ list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_var_list_parens (c_parser *parser, ಗಣನಾ omp_clause_code kind,
			      ವೃಕ್ಷ list, ತಾರ್ಕಿಕ map_lvalue = ಅಸತ್ಯ)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  ಯದಿ (parser->in_omp_decl_attribute)
    {
      ಯದಿ (kind)
	{
	  ವೃಕ್ಷ u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = parser->in_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  ಪ್ರತ್ಯಾಗಮ u;
	}
      ಅನ್ಯಥಾ
	ಪ್ರತ್ಯಾಗಮ ವೃಕ್ಷ_cons (parser->in_omp_decl_attribute, NULL_ವೃಕ್ಷ, list);
    }

  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, kind, list, map_lvalue);
      parens.skip_until_found_close (parser);
    }
  ಪ್ರತ್ಯಾಗಮ list;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_data_clause (c_parser *parser, pragma_omp_clause c_kind,
			   ವೃಕ್ಷ list)
{
  ಗಣನಾ gomp_map_kind kind;
  ವಿಕಲ್ಪ (c_kind)
    {
    ಪಕ್ಷ PRAGMA_OACC_CLAUSE_ATTACH:
      kind = GOMP_MAP_ATTACH;
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_CLAUSE_COPY:
      kind = GOMP_MAP_TOFROM;
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_CLAUSE_COPYIN:
      kind = GOMP_MAP_TO;
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_CLAUSE_COPYOUT:
      kind = GOMP_MAP_FROM;
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_CLAUSE_CREATE:
      kind = GOMP_MAP_ALLOC;
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_CLAUSE_DELETE:
      kind = GOMP_MAP_RELEASE;
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_CLAUSE_DETACH:
      kind = GOMP_MAP_DETACH;
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_CLAUSE_DEVICE:
      kind = GOMP_MAP_FORCE_TO;
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      kind = GOMP_MAP_DEVICE_RESIDENT;
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_CLAUSE_LINK:
      kind = GOMP_MAP_LINK;
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_CLAUSE_NO_CREATE:
      kind = GOMP_MAP_IF_PRESENT;
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_CLAUSE_PRESENT:
      kind = GOMP_MAP_FORCE_PRESENT;
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    ಪಕ್ಷ PRAGMA_OACC_CLAUSE_HOST:
      kind = GOMP_MAP_FORCE_FROM;
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }

  ವೃಕ್ಷ nl = list;
  ತಾರ್ಕಿಕ readonly = ಅಸತ್ಯ;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      ಯದಿ (c_kind == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ಯದಿ (token->type == CPP_NAME
	      && !strcmp (IDENTIFIER_POINTER (token->ಮೌಲ್ಯ), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = ಸತ್ಯ;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       ಅಸತ್ಯ);
      parens.skip_until_found_close (parser);
    }

  ಪ್ರತಿ (ವೃಕ್ಷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      ಯದಿ (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  ಪ್ರತ್ಯಾಗಮ nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_data_clause_deviceptr (c_parser *parser, ವೃಕ್ಷ list)
{
  ವೃಕ್ಷ vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ರಿಕ್ತ);
  ಪ್ರತಿ (t = vars; t && t; t = ವೃಕ್ಷ_CHAIN (t))
    {
      ವೃಕ್ಷ v = ವೃಕ್ಷ_PURPOSE (t);
      location_t loc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ವೃಕ್ಷ_ಮೌಲ್ಯ (t));

      ಯದಿ (!VAR_P (v) && ವೃಕ್ಷ_CODE (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_TYPE (v) == error_mark_ಗಂಟು)
	;
      ಅನ್ಯಥಾ ಯದಿ (!POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      ವೃಕ್ಷ u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_collapse (c_parser *parser, ವೃಕ್ಷ list)
{
  ವೃಕ್ಷ c, ಅಂಕೆ = error_mark_ಗಂಟು;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      ಅಂಕೆ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ).ಮೌಲ್ಯ;
      parens.skip_until_found_close (parser);
    }
  ಯದಿ (ಅಂಕೆ == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ list;
  mark_exp_read (ಅಂಕೆ);
  ಅಂಕೆ = c_fully_fold (ಅಂಕೆ, ಅಸತ್ಯ, ರಿಕ್ತ);
  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಂಕೆ))
      || !ವೃಕ್ಷ_fits_shwi_p (ಅಂಕೆ)
      || (n = ವೃಕ್ಷ_to_shwi (ಅಂಕೆ)) <= 0
      || (ಪೂರ್ಣಾಙ್ಕ) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      ಪ್ರತ್ಯಾಗಮ list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_ಅಭಿವ್ಯಕ್ತಿ (c) = ಅಂಕೆ;
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_copyin (c_parser *parser, ವೃಕ್ಷ list)
{
  ಪ್ರತ್ಯಾಗಮ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_copyprivate (c_parser *parser, ವೃಕ್ಷ list)
{
  ಪ್ರತ್ಯಾಗಮ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_default (c_parser *parser, ವೃಕ್ಷ list, ತಾರ್ಕಿಕ is_oacc)
{
  ಗಣನಾ omp_clause_default_kind kind = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ c;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);

      ವಿಕಲ್ಪ (p[0])
	{
	ಪಕ್ಷ 'n':
	  ಯದಿ (strcmp ("none", p) != 0)
	    ಗಚ್ಛ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_NONE;
	  ಭಙ್ಗ;

	ಪಕ್ಷ 'p':
	  ಯದಿ (is_oacc)
	    {
	      ಯದಿ (strcmp ("present", p) != 0)
		ಗಚ್ಛ invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಯದಿ (strcmp ("private", p) != 0)
		ಗಚ್ಛ invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRIVATE;
	    }
	  ಭಙ್ಗ;

	ಪಕ್ಷ 'f':
	  ಯದಿ (strcmp ("firstprivate", p) != 0 || is_oacc)
	    ಗಚ್ಛ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  ಭಙ್ಗ;

	ಪಕ್ಷ 's':
	  ಯದಿ (strcmp ("shared", p) != 0 || is_oacc)
	    ಗಚ್ಛ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_SHARED;
	  ಭಙ್ಗ;

	ಸ್ವಭಾವ:
	  ಗಚ್ಛ invalid_kind;
	}

      c_parser_consume_token (parser);
    }
  ಅನ್ಯಥಾ
    {
    invalid_kind:
      ಯದಿ (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      ಅನ್ಯಥಾ
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_found_close (parser);

  ಯದಿ (kind == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    ಪ್ರತ್ಯಾಗಮ list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_KIND (c) = kind;

  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_firstprivate (c_parser *parser, ವೃಕ್ಷ list)
{
  ಪ್ರತ್ಯಾಗಮ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_final (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      ವೃಕ್ಷ t, c;
      ಯದಿ (!parens.require_open (parser))
	t = error_mark_ಗಂಟು;
      ಅನ್ಯಥಾ
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	  t = convert_lvalue_to_rvalue (eloc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);
	  parens.skip_until_found_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }
  ಅನ್ಯಥಾ
    c_parser_error (parser, "expected %<(%>");

  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 5.1:
   indirect [( expression )]
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_indirect (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t location = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ t;

  ಯದಿ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      ಯದಿ (!parens.require_open (parser))
	ಪ್ರತ್ಯಾಗಮ list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (loc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಸತ್ಯ);
      t = c_objc_common_truthvalue_conversion (loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
      t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);
      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t))
	  || ವೃಕ್ಷ_CODE (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  ಪ್ರತ್ಯಾಗಮ list;
	}
      parens.skip_until_found_close (parser);
    }
  ಅನ್ಯಥಾ
    t = integer_one_ಗಂಟು;

  check_no_duplicate_clause (list, OMP_CLAUSE_INDIRECT, "indirect");

  ವೃಕ್ಷ c = build_omp_clause (location, OMP_CLAUSE_INDIRECT);
  OMP_CLAUSE_INDIRECT_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;

  ಪ್ರತ್ಯಾಗಮ c;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_if (c_parser *parser, ವೃಕ್ಷ list, ತಾರ್ಕಿಕ is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  ಗಣನಾ ವೃಕ್ಷ_code if_modifier = ERROR_MARK;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ಯದಿ (is_omp && c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಪೂರ್ಣಾಙ್ಕ n = 2;
      ಯದಿ (strcmp (p, "cancel") == 0)
	if_modifier = VOID_CST;
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "parallel") == 0)
	if_modifier = OMP_PARALLEL;
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "simd") == 0)
	if_modifier = OMP_SIMD;
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "task") == 0)
	if_modifier = OMP_TASK;
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "taskloop") == 0)
	if_modifier = OMP_TASKLOOP;
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "target") == 0)
	{
	  if_modifier = OMP_TARGET;
	  ಯದಿ (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	    {
	      p = IDENTIFIER_POINTER (c_parser_peek_2nd_token (parser)->ಮೌಲ್ಯ);
	      ಯದಿ (strcmp ("data", p) == 0)
		if_modifier = OMP_TARGET_DATA;
	      ಅನ್ಯಥಾ ಯದಿ (strcmp ("update", p) == 0)
		if_modifier = OMP_TARGET_UPDATE;
	      ಅನ್ಯಥಾ ಯದಿ (strcmp ("enter", p) == 0)
		if_modifier = OMP_TARGET_ENTER_DATA;
	      ಅನ್ಯಥಾ ಯದಿ (strcmp ("exit", p) == 0)
		if_modifier = OMP_TARGET_EXIT_DATA;
	      ಯದಿ (if_modifier != OMP_TARGET)
		{
		  n = 3;
		  c_parser_consume_token (parser);
		}
	      ಅನ್ಯಥಾ
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<data%>, %<update%>, %<enter%> "
				 "or %<exit%>");
		  if_modifier = ERROR_MARK;
		}
	      ಯದಿ (if_modifier == OMP_TARGET_ENTER_DATA
		  || if_modifier == OMP_TARGET_EXIT_DATA)
		{
		  ಯದಿ (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_POINTER
				(c_parser_peek_2nd_token (parser)->ಮೌಲ್ಯ);
		      ಯದಿ (strcmp ("data", p) == 0)
			n = 4;
		    }
		  ಯದಿ (n == 4)
		    c_parser_consume_token (parser);
		  ಅನ್ಯಥಾ
		    {
		      location_t loc
			= c_parser_peek_2nd_token (parser)->location;
		      error_at (loc, "expected %<data%>");
		      if_modifier = ERROR_MARK;
		    }
		}
	    }
	}
      ಯದಿ (if_modifier != ERROR_MARK)
	{
	  ಯದಿ (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಯದಿ (n > 2)
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<:%>");
		}
	      if_modifier = ERROR_MARK;
	    }
	}
    }

  location_t loc = c_parser_peek_token (parser)->location;
  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (loc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಸತ್ಯ);
  ವೃಕ್ಷ t = c_objc_common_truthvalue_conversion (loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ), c;
  t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);
  parens.skip_until_found_close (parser);

  ಪ್ರತಿ (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IF)
      {
	ಯದಿ (if_modifier != ERROR_MARK
	    && OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    ಧ್ರುವ ವರ್ಣ *p = ರಿಕ್ತ;
	    ವಿಕಲ್ಪ (if_modifier)
	      {
	      ಪಕ್ಷ VOID_CST: p = "cancel"; ಭಙ್ಗ;
	      ಪಕ್ಷ OMP_PARALLEL: p = "parallel"; ಭಙ್ಗ;
	      ಪಕ್ಷ OMP_SIMD: p = "simd"; ಭಙ್ಗ;
	      ಪಕ್ಷ OMP_TASK: p = "task"; ಭಙ್ಗ;
	      ಪಕ್ಷ OMP_TASKLOOP: p = "taskloop"; ಭಙ್ಗ;
	      ಪಕ್ಷ OMP_TARGET_DATA: p = "target data"; ಭಙ್ಗ;
	      ಪಕ್ಷ OMP_TARGET: p = "target"; ಭಙ್ಗ;
	      ಪಕ್ಷ OMP_TARGET_UPDATE: p = "target update"; ಭಙ್ಗ;
	      ಪಕ್ಷ OMP_TARGET_ENTER_DATA: p = "target enter data"; ಭಙ್ಗ;
	      ಪಕ್ಷ OMP_TARGET_EXIT_DATA: p = "target exit data"; ಭಙ್ಗ;
	      ಸ್ವಭಾವ: gcc_unreachable ();
	      }
	    error_at (location, "too many %<if%> clauses with %qs modifier",
		      p);
	    ಪ್ರತ್ಯಾಗಮ list;
	  }
	ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    ಯದಿ (!is_omp)
	      error_at (location, "too many %<if%> clauses");
	    ಅನ್ಯಥಾ
	      error_at (location, "too many %<if%> clauses without modifier");
	    ಪ್ರತ್ಯಾಗಮ list;
	  }
	ಅನ್ಯಥಾ ಯದಿ (if_modifier == ERROR_MARK
		 || OMP_CLAUSE_IF_MODIFIER (c) == ERROR_MARK)
	  {
	    error_at (location, "if any %<if%> clause has modifier, then all "
				"%<if%> clauses have to use modifier");
	    ಪ್ರತ್ಯಾಗಮ list;
	  }
      }

  c = build_omp_clause (location, OMP_CLAUSE_IF);
  OMP_CLAUSE_IF_MODIFIER (c) = if_modifier;
  OMP_CLAUSE_IF_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_lastprivate (c_parser *parser, ವೃಕ್ಷ list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  ಯದಿ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      ತಾರ್ಕಿಕ conditional = ಅಸತ್ಯ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  ಧ್ರುವ ವರ್ಣ *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	  ಯದಿ (strcmp (p, "conditional") == 0)
	    {
	      conditional = ಸತ್ಯ;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      ವೃಕ್ಷ nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ಯದಿ (conditional)
	ಪ್ರತಿ (ವೃಕ್ಷ c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      ಪ್ರತ್ಯಾಗಮ nlist;
    }
  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 3.1:
   mergeable */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_UNUSED, ವೃಕ್ಷ list)
{
  ವೃಕ್ಷ c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 2.5:
   nowait */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_UNUSED, ವೃಕ್ಷ list)
{
  ವೃಕ್ಷ c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_ಅಂಕೆ_threads (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t ಅಂಕೆ_threads_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
      ವೃಕ್ಷ c, t = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);

      parens.skip_until_found_close (parser);

      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ಪ್ರತ್ಯಾಗಮ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (ಅಭಿವ್ಯಕ್ತಿ_loc, LE_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು, t,
		       build_int_cst (ವೃಕ್ಷ_TYPE (t), 0));
      protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (c, ಅಭಿವ್ಯಕ್ತಿ_loc);
      ಯದಿ (c == boolean_true_ಗಂಟು)
	{
	  warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_ಗಂಟು;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_ಅಂಕೆ_THREADS, "num_threads");

      c = build_omp_clause (ಅಂಕೆ_threads_loc, OMP_CLAUSE_ಅಂಕೆ_THREADS);
      OMP_CLAUSE_ಅಂಕೆ_THREADS_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_ಅಂಕೆ_tasks (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t ಅಂಕೆ_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      ತಾರ್ಕಿಕ strict = ಅಸತ್ಯ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ),
		     "strict") == 0)
	{
	  strict = ಸತ್ಯ;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
      ವೃಕ್ಷ c, t = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);

      parens.skip_until_found_close (parser);

      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ಪ್ರತ್ಯಾಗಮ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (ಅಭಿವ್ಯಕ್ತಿ_loc, LE_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು, t,
			   build_int_cst (ವೃಕ್ಷ_TYPE (t), 0));
      ಯದಿ (CAN_HAVE_LOCATION_P (c))
	SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (c, ಅಭಿವ್ಯಕ್ತಿ_loc);
      ಯದಿ (c == boolean_true_ಗಂಟು)
	{
	  warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_ಗಂಟು;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_ಅಂಕೆ_TASKS, "num_tasks");

      c = build_omp_clause (ಅಂಕೆ_tasks_loc, OMP_CLAUSE_ಅಂಕೆ_TASKS);
      OMP_CLAUSE_ಅಂಕೆ_TASKS_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
      OMP_CLAUSE_ಅಂಕೆ_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_grainsize (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      ತಾರ್ಕಿಕ strict = ಅಸತ್ಯ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ),
		     "strict") == 0)
	{
	  strict = ಸತ್ಯ;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
      ವೃಕ್ಷ c, t = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);

      parens.skip_until_found_close (parser);

      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ಪ್ರತ್ಯಾಗಮ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (ಅಭಿವ್ಯಕ್ತಿ_loc, LE_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು, t,
			   build_int_cst (ವೃಕ್ಷ_TYPE (t), 0));
      ಯದಿ (CAN_HAVE_LOCATION_P (c))
	SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (c, ಅಭಿವ್ಯಕ್ತಿ_loc);
      ಯದಿ (c == boolean_true_ಗಂಟು)
	{
	  warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_ಗಂಟು;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 4.5:
   priority ( expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_priority (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t priority_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
      ವೃಕ್ಷ c, t = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);

      parens.skip_until_found_close (parser);

      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ಪ್ರತ್ಯಾಗಮ list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (ಅಭಿವ್ಯಕ್ತಿ_loc, LT_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು, t,
			   build_int_cst (ವೃಕ್ಷ_TYPE (t), 0));
      ಯದಿ (CAN_HAVE_LOCATION_P (c))
	SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (c, ಅಭಿವ್ಯಕ್ತಿ_loc);
      ಯದಿ (c == boolean_true_ಗಂಟು)
	{
	  warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_ಗಂಟು;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_PRIORITY, "priority");

      c = build_omp_clause (priority_loc, OMP_CLAUSE_PRIORITY);
      OMP_CLAUSE_PRIORITY_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 4.5:
   hint ( expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_hint (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
      ವೃಕ್ಷ c, t = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);
      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t))
	  || ವೃಕ್ಷ_CODE (t) != INTEGER_CST
	  || ವೃಕ್ಷ_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  ಪ್ರತ್ಯಾಗಮ list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_filter (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
      ವೃಕ್ಷ c, t = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);
      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ಪ್ರತ್ಯಾಗಮ list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_defaultmap (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ c;
  ಧ್ರುವ ವರ್ಣ *p;
  ಗಣನಾ omp_clause_defaultmap_kind behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  ಗಣನಾ omp_clause_defaultmap_kind category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;
  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  ಅನ್ಯಥಾ ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      ಗಚ್ಛ out_err;
    }
  ಅನ್ಯಥಾ
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);

  ವಿಕಲ್ಪ (p[0])
    {
    ಪಕ್ಷ 'a':
      ಯದಿ (strcmp ("alloc", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ALLOC;
      ಅನ್ಯಥಾ
	ಗಚ್ಛ invalid_behavior;
      ಭಙ್ಗ;

    ಪಕ್ಷ 'd':
      ಯದಿ (strcmp ("default", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
      ಅನ್ಯಥಾ
	ಗಚ್ಛ invalid_behavior;
      ಭಙ್ಗ;

    ಪಕ್ಷ 'f':
      ಯದಿ (strcmp ("firstprivate", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FIRSTPRIVATE;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("from", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FROM;
      ಅನ್ಯಥಾ
	ಗಚ್ಛ invalid_behavior;
      ಭಙ್ಗ;

    ಪಕ್ಷ 'n':
      ಯದಿ (strcmp ("none", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_NONE;
      ಅನ್ಯಥಾ
	ಗಚ್ಛ invalid_behavior;
      ಭಙ್ಗ;

    ಪಕ್ಷ 'p':
      ಯದಿ (strcmp ("present", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_PRESENT;
      ಅನ್ಯಥಾ
	ಗಚ್ಛ invalid_behavior;
      ಭಙ್ಗ;

    ಪಕ್ಷ 't':
      ಯದಿ (strcmp ("tofrom", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TOFROM;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("to", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TO;
      ಅನ್ಯಥಾ
	ಗಚ್ಛ invalid_behavior;
      ಭಙ್ಗ;

    ಸ್ವಭಾವ:
      ಗಚ್ಛ invalid_behavior;
    }
  c_parser_consume_token (parser);

  ಯದಿ (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ಗಚ್ಛ out_err;
      ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  ಗಚ್ಛ out_err;
	}
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ವಿಕಲ್ಪ (p[0])
	{
	ಪಕ್ಷ 'a':
	  ಯದಿ (strcmp ("aggregate", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE;
	  ಅನ್ಯಥಾ ಯದಿ (strcmp ("all", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL;
	  ಅನ್ಯಥಾ
	    ಗಚ್ಛ invalid_category;
	  ಭಙ್ಗ;

	ಪಕ್ಷ 'p':
	  ಯದಿ (strcmp ("pointer", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER;
	  ಅನ್ಯಥಾ
	    ಗಚ್ಛ invalid_category;
	  ಭಙ್ಗ;

	ಪಕ್ಷ 's':
	  ಯದಿ (strcmp ("scalar", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR;
	  ಅನ್ಯಥಾ
	    ಗಚ್ಛ invalid_category;
	  ಭಙ್ಗ;

	ಸ್ವಭಾವ:
	  ಗಚ್ಛ invalid_category;
	}

      c_parser_consume_token (parser);
    }
  parens.skip_until_found_close (parser);

  ಪ್ರತಿ (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEFAULTMAP
	&& (category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
	    || OMP_CLAUSE_DEFAULTMAP_CATEGORY (c) == category
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL)))
      {
	ಗಣನಾ omp_clause_defaultmap_kind cat = category;
	location_t loc = OMP_CLAUSE_LOCATION (c);
	ಯದಿ (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
		&& (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		    != OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)))
	  cat = OMP_CLAUSE_DEFAULTMAP_CATEGORY (c);
	p = ರಿಕ್ತ;
	ವಿಕಲ್ಪ (cat)
	  {
	  ಪಕ್ಷ OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED:
	    p = ರಿಕ್ತ;
	    ಭಙ್ಗ;
	  ಪಕ್ಷ OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL:
	    p = "all";
	    ಭಙ್ಗ;
	  ಪಕ್ಷ OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE:
	    p = "aggregate";
	    ಭಙ್ಗ;
	  ಪಕ್ಷ OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER:
	    p = "pointer";
	    ಭಙ್ಗ;
	  ಪಕ್ಷ OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR:
	    p = "scalar";
	    ಭಙ್ಗ;
	  ಸ್ವಭಾವ:
	    gcc_unreachable ();
	  }
	ಯದಿ (p)
	  error_at (loc, "too many %<defaultmap%> clauses with %qs category",
		    p);
	ಅನ್ಯಥಾ
	  error_at (loc, "too many %<defaultmap%> clauses with unspecified "
			 "category");
	ಭಙ್ಗ;
      }

  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULTMAP);
  OMP_CLAUSE_DEFAULTMAP_SET_KIND (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;

 out_err:
  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_use_device_ptr (c_parser *parser, ವೃಕ್ಷ list)
{
  ಪ್ರತ್ಯಾಗಮ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_use_device_addr (c_parser *parser, ವೃಕ್ಷ list)
{
  ಪ್ರತ್ಯಾಗಮ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_has_device_addr (c_parser *parser, ವೃಕ್ಷ list)
{
  ಪ್ರತ್ಯಾಗಮ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_is_device_ptr (c_parser *parser, ವೃಕ್ಷ list)
{
  ಪ್ರತ್ಯಾಗಮ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_code code,
				 ವೃಕ್ಷ list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_expression (parser);
  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
  ವೃಕ್ಷ c, t = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
  t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);

  parens.skip_until_found_close (parser);

  ಯದಿ (t == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ list;
  ಅನ್ಯಥಾ ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
    {
      error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, "%qs expression must be integral",
		omp_clause_code_name[code]);
      ಪ್ರತ್ಯಾಗಮ list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (ಅಭಿವ್ಯಕ್ತಿ_loc, LE_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು, t,
		       build_int_cst (ವೃಕ್ಷ_TYPE (t), 0));
  protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (c, ಅಭಿವ್ಯಕ್ತಿ_loc);
  ಯದಿ (c == boolean_true_ಗಂಟು)
    {
      warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, 0,
		  "%qs value must be positive",
		  omp_clause_code_name[code]);
      t = integer_one_ಗಂಟು;
    }

  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  c = build_omp_clause (loc, code);
  OMP_CLAUSE_OPERAND (c, 0) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_code kind,
			    ಧ್ರುವ ವರ್ಣ *str, ವೃಕ್ಷ list)
{
  ಧ್ರುವ ವರ್ಣ *id = "num";
  ವೃಕ್ಷ ops[2] = { NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ }, c;

  ಯದಿ (kind == OMP_CLAUSE_VECTOR)
    id = "length";

  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      ಕುರು
	{
	  c_token *next = c_parser_peek_token (parser);
	  ಪೂರ್ಣಾಙ್ಕ idx = 0;

	  /* Gang static argument.  */
	  ಯದಿ (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		ಗಚ್ಛ cleanup_error;

	      idx = 1;
	      ಯದಿ (ops[idx] != NULL_ವೃಕ್ಷ)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  ಗಚ್ಛ cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      ಯದಿ (c_parser_next_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_ಗಂಟು;

		  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      ಅನುವರ್ತ;
		    }
		  ಅನ್ಯಥಾ
		    ಭಙ್ಗ;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
		   && strcmp (id, IDENTIFIER_POINTER (next->ಮೌಲ್ಯ)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  ಯದಿ (ops[idx] != NULL_ವೃಕ್ಷ)
	    {
	      c_parser_error (parser, "unexpected argument");
	      ಗಚ್ಛ cleanup_error;
	    }

	  location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
	  c_ಅಭಿವ್ಯಕ್ತಿ cexpr = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	  cexpr = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, cexpr, ಅಸತ್ಯ, ಸತ್ಯ);
	  ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = cexpr.ಮೌಲ್ಯ;
	  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ == error_mark_ಗಂಟು)
	    ಗಚ್ಛ cleanup_error;

	  ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ರಿಕ್ತ);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      ಪ್ರತ್ಯಾಗಮ list;
	    }

	  ವೃಕ್ಷ c = fold_build2_loc (ಅಭಿವ್ಯಕ್ತಿ_loc, LE_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು, ಅಭಿವ್ಯಕ್ತಿ,
				    build_int_cst (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), 0));
	  ಯದಿ (c == boolean_true_ಗಂಟು)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      ಅಭಿವ್ಯಕ್ತಿ = integer_one_ಗಂಟು;
	    }

	  ops[idx] = ಅಭಿವ್ಯಕ್ತಿ;

	  ಯದಿ (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ಅನುವರ್ತ;
	    }
	  ಭಙ್ಗ;
	}
      ಯಾವತ್ (1);

      ಯದಿ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	ಗಚ್ಛ cleanup_error;
    }

  check_no_duplicate_clause (list, kind, str);

  c = build_omp_clause (loc, kind);

  ಯದಿ (ops[1])
    OMP_CLAUSE_OPERAND (c, 1) = ops[1];

  OMP_CLAUSE_OPERAND (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  ಪ್ರತ್ಯಾಗಮ c;

 cleanup_error:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_simple_clause (location_t loc, ಗಣನಾ omp_clause_code code,
			     ವೃಕ್ಷ list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  ವೃಕ್ಷ c = build_omp_clause (loc, code);
  OMP_CLAUSE_CHAIN (c) = list;

  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenACC:
   async [( int-expr )] */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_clause_async (c_parser *parser, ವೃಕ್ಷ list)
{
  ವೃಕ್ಷ c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_ಗಂಟು, GOMP_ASYNC_NOVAL);

  ಯದಿ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ).ಮೌಲ್ಯ;
      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      ಅನ್ಯಥಾ ಯದಿ (t == error_mark_ಗಂಟು
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	ಪ್ರತ್ಯಾಗಮ list;
    }
  ಅನ್ಯಥಾ
    t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_clause_tile (c_parser *parser, ವೃಕ್ಷ list)
{
  ವೃಕ್ಷ c, ಅಭಿವ್ಯಕ್ತಿ = error_mark_ಗಂಟು;
  location_t loc;
  ವೃಕ್ಷ tile = NULL_ವೃಕ್ಷ;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ಪ್ರತ್ಯಾಗಮ list;

  ಕುರು
    {
      ಯದಿ (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	ಪ್ರತ್ಯಾಗಮ list;

      ಯದಿ (c_parser_next_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  ಅಭಿವ್ಯಕ್ತಿ = integer_zero_ಗಂಟು;
	}
      ಅನ್ಯಥಾ
	{
	  location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
	  c_ಅಭಿವ್ಯಕ್ತಿ cexpr = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	  cexpr = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, cexpr, ಅಸತ್ಯ, ಸತ್ಯ);
	  ಅಭಿವ್ಯಕ್ತಿ = cexpr.ಮೌಲ್ಯ;

	  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ == error_mark_ಗಂಟು)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      ಪ್ರತ್ಯಾಗಮ list;
	    }

	  ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ರಿಕ್ತ);

	  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ))
	      || !ವೃಕ್ಷ_fits_shwi_p (ಅಭಿವ್ಯಕ್ತಿ)
	      || ವೃಕ್ಷ_to_shwi (ಅಭಿವ್ಯಕ್ತಿ) <= 0)
	    {
	      error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, "%<tile%> argument needs positive"
			" integral constant");
	      ಅಭಿವ್ಯಕ್ತಿ = integer_zero_ಗಂಟು;
	    }
	}

      tile = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, ಅಭಿವ್ಯಕ್ತಿ, tile);
    }
  ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN));

  /* Consume the trailing ')'.  */
  c_parser_consume_token (parser);

  c = build_omp_clause (loc, OMP_CLAUSE_TILE);
  tile = nreverse (tile);
  OMP_CLAUSE_TILE_LIST (c) = tile;
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenACC:
   wait [( int-expr-list )] */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_clause_wait (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  ಯದಿ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_ಗಂಟು, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenACC 2.7:
   self [( expression )] */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_compute_clause_self (c_parser *parser, ವೃಕ್ಷ list)
{
  ವೃಕ್ಷ t;
  location_t location = c_parser_peek_token (parser)->location;
  ಯದಿ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (loc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಸತ್ಯ);
      t = c_objc_common_truthvalue_conversion (loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
      t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);
      parens.skip_until_found_close (parser);
    }
  ಅನ್ಯಥಾ
    t = truthvalue_true_ಗಂಟು;

  ಪ್ರತಿ (ವೃಕ್ಷ c = list; c; c = OMP_CLAUSE_CHAIN (c))
    ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	ಪ್ರತ್ಯಾಗಮ list;
      }

  ವೃಕ್ಷ c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 5.0:
   order ( concurrent )

   OpenMP 5.1:
   order ( order-modifier : concurrent )

   order-modifier:
     reproducible
     unconstrained  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_order (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ c;
  ಧ್ರುವ ವರ್ಣ *p;
  ತಾರ್ಕಿಕ unconstrained = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ reproducible = ಅಸತ್ಯ;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "unconstrained") == 0)
	unconstrained = ಸತ್ಯ;
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "reproducible") == 0)
	reproducible = ಸತ್ಯ;
      ಅನ್ಯಥಾ
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  ಗಚ್ಛ out_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      ಗಚ್ಛ out_err;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
  ಯದಿ (strcmp (p, "concurrent") != 0)
    {
      c_parser_error (parser, "expected %<concurrent%>");
      ಗಚ್ಛ out_err;
    }
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDER, "order");
  c = build_omp_clause (loc, OMP_CLAUSE_ORDER);
  OMP_CLAUSE_ORDER_UNCONSTRAINED (c) = unconstrained;
  OMP_CLAUSE_ORDER_REPRODUCIBLE (c) = reproducible;
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;

 out_err:
  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_bind (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ c;
  ಧ್ರುವ ವರ್ಣ *p;
  ಗಣನಾ omp_clause_bind_kind kind = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;
  ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_found_close (parser);
      ಪ್ರತ್ಯಾಗಮ list;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
  ಯದಿ (strcmp (p, "teams") == 0)
    kind = OMP_CLAUSE_BIND_TEAMS;
  ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "parallel") == 0)
    kind = OMP_CLAUSE_BIND_PARALLEL;
  ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "thread") != 0)
    ಗಚ್ಛ invalid;
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_ordered (c_parser *parser, ವೃಕ್ಷ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  ವೃಕ್ಷ c, ಅಂಕೆ = NULL_ವೃಕ್ಷ;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      ಅಂಕೆ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ).ಮೌಲ್ಯ;
      parens.skip_until_found_close (parser);
    }
  ಯದಿ (ಅಂಕೆ == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ list;
  ಯದಿ (ಅಂಕೆ)
    {
      mark_exp_read (ಅಂಕೆ);
      ಅಂಕೆ = c_fully_fold (ಅಂಕೆ, ಅಸತ್ಯ, ರಿಕ್ತ);
      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಂಕೆ))
	  || !ವೃಕ್ಷ_fits_shwi_p (ಅಂಕೆ)
	  || (n = ವೃಕ್ಷ_to_shwi (ಅಂಕೆ)) <= 0
	  || (ಪೂರ್ಣಾಙ್ಕ) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  ಪ್ರತ್ಯಾಗಮ list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_ಅಭಿವ್ಯಕ್ತಿ (c) = ಅಂಕೆ;
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_private (c_parser *parser, ವೃಕ್ಷ list)
{
  ಪ್ರತ್ಯಾಗಮ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_PRIVATE, list);
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_reduction (c_parser *parser, ಗಣನಾ omp_clause_code kind,
			       ತಾರ್ಕಿಕ is_omp, ವೃಕ್ಷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      ತಾರ್ಕಿಕ task = ಅಸತ್ಯ;
      ತಾರ್ಕಿಕ inscan = ಅಸತ್ಯ;
      ಗಣನಾ ವೃಕ್ಷ_code code = ERROR_MARK;
      ವೃಕ್ಷ reduc_id = NULL_ವೃಕ್ಷ;

      ಯದಿ (kind == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      ಧ್ರುವ ವರ್ಣ *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	      ಯದಿ (strcmp (p, "task") == 0)
		task = ಸತ್ಯ;
	      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "inscan") == 0)
		inscan = ಸತ್ಯ;
	      ಯದಿ (task || inscan)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		}
	    }
	}

      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
	{
	ಪಕ್ಷ CPP_PLUS:
	  code = PLUS_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_MULT:
	  code = MULT_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_MINUS:
	  ಯದಿ (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.add_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  code = MINUS_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_AND:
	  code = BIT_AND_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_XOR:
	  code = BIT_XOR_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_OR:
	  code = BIT_IOR_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_AND_AND:
	  code = TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_OR_OR:
	  code = TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
        ಪಕ್ಷ CPP_NAME:
	  {
	    ಧ್ರುವ ವರ್ಣ *p
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	    ಯದಿ (strcmp (p, "min") == 0)
	      {
		code = MIN_ಅಭಿವ್ಯಕ್ತಿ;
		ಭಙ್ಗ;
	      }
	    ಯದಿ (strcmp (p, "max") == 0)
	      {
		code = MAX_ಅಭಿವ್ಯಕ್ತಿ;
		ಭಙ್ಗ;
	      }
	    reduc_id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	    ಭಙ್ಗ;
	  }
	ಸ್ವಭಾವ:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
	  ಪ್ರತ್ಯಾಗಮ list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (code, reduc_id);
      ಯದಿ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  ವೃಕ್ಷ nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, kind, list);
	  ಪ್ರತಿ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      ವೃಕ್ಷ d = OMP_CLAUSE_DECL (c), type;
	      ಯದಿ (ವೃಕ್ಷ_CODE (d) != OMP_ARRAY_SECTION)
		type = ವೃಕ್ಷ_TYPE (d);
	      ಅನ್ಯಥಾ
		{
		  ಪೂರ್ಣಾಙ್ಕ cnt = 0;
		  ವೃಕ್ಷ t;
		  ಪ್ರತಿ (t = d;
		      ವೃಕ್ಷ_CODE (t) == OMP_ARRAY_SECTION;
		      t = ವೃಕ್ಷ_OPERAND (t, 0))
		    cnt++;
		  type = ವೃಕ್ಷ_TYPE (t);
		  ಯಾವತ್ (cnt > 0)
		    {
		      ಯದಿ (ವೃಕ್ಷ_CODE (type) != POINTER_TYPE
			  && ವೃಕ್ಷ_CODE (type) != ARRAY_TYPE)
			ಭಙ್ಗ;
		      type = ವೃಕ್ಷ_TYPE (type);
		      cnt--;
		    }
		}
	      ಯಾವತ್ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE)
		type = ವೃಕ್ಷ_TYPE (type);
	      OMP_CLAUSE_REDUCTION_CODE (c) = code;
	      ಯದಿ (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      ಅನ್ಯಥಾ ಯದಿ (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      ಯದಿ (code == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || ವೃಕ್ಷ_CODE (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_found_close (parser);
    }
  ಪ್ರತ್ಯಾಗಮ list;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_schedule (c_parser *parser, ವೃಕ್ಷ list)
{
  ವೃಕ್ಷ c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  ಪೂರ್ಣಾಙ್ಕ modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  c = build_omp_clause (loc, OMP_CLAUSE_SCHEDULE);

  location_t comma = UNKNOWN_LOCATION;
  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ವೃಕ್ಷ kind = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (kind);
      ಯದಿ (strcmp ("simd", p) == 0)
	OMP_CLAUSE_SCHEDULE_SIMD (c) = 1;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_MONOTONIC;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_NONMONOTONIC;
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      ಯದಿ (nmodifiers++ == 0
	  && c_parser_next_token_is (parser, CPP_COMMA))
	{
	  comma = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ
	{
	  c_parser_require (parser, CPP_COLON, "expected %<:%>");
	  ಭಙ್ಗ;
	}
    }
  ಯದಿ (comma != UNKNOWN_LOCATION)
    error_at (comma, "expected %<:%>");

  ಯದಿ ((modifiers & (OMP_CLAUSE_SCHEDULE_MONOTONIC
		    | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
      == (OMP_CLAUSE_SCHEDULE_MONOTONIC
	  | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ವೃಕ್ಷ kind = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (kind);

      ವಿಕಲ್ಪ (p[0])
	{
	ಪಕ್ಷ 'd':
	  ಯದಿ (strcmp ("dynamic", p) != 0)
	    ಗಚ್ಛ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_DYNAMIC;
	  ಭಙ್ಗ;

        ಪಕ್ಷ 'g':
	  ಯದಿ (strcmp ("guided", p) != 0)
	    ಗಚ್ಛ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_GUIDED;
	  ಭಙ್ಗ;

	ಪಕ್ಷ 'r':
	  ಯದಿ (strcmp ("runtime", p) != 0)
	    ಗಚ್ಛ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_RUNTIME;
	  ಭಙ್ಗ;

	ಸ್ವಭಾವ:
	  ಗಚ್ಛ invalid_kind;
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_STATIC;
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_AUTO;
  ಅನ್ಯಥಾ
    ಗಚ್ಛ invalid_kind;

  c_parser_consume_token (parser);
  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      location_t here;
      c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (here, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
      t = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);

      ಯದಿ (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_RUNTIME)
	error_at (here, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_AUTO)
	error_at (here,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (t)) == INTEGER_TYPE
	       || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  ವೃಕ್ಷ s = fold_build2_loc (loc, LE_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು, t,
				    build_int_cst (ವೃಕ್ಷ_TYPE (t), 0));
	  protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (s, loc);
	  ಯದಿ (s == boolean_true_ಗಂಟು)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_ಗಂಟು;
	    }
	  OMP_CLAUSE_SCHEDULE_CHUNK_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
	}
      ಅನ್ಯಥಾ
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_found_close (parser);
    }
  ಅನ್ಯಥಾ
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_SCHEDULE_KIND (c)
    = (ಗಣನಾ omp_clause_schedule_kind)
      (OMP_CLAUSE_SCHEDULE_KIND (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_SCHEDULE, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;

 invalid_kind:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_shared (c_parser *parser, ವೃಕ್ಷ list)
{
  ಪ್ರತ್ಯಾಗಮ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_UNUSED, ವೃಕ್ಷ list)
{
  ವೃಕ್ಷ c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_UNTIED, "untied");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_UNTIED);
  OMP_CLAUSE_CHAIN (c) = list;

  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 4.0:
   inbranch
   notinbranch */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_UNUSED,
			    ಗಣನಾ omp_clause_code code, ವೃಕ್ಷ list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  ವೃಕ್ಷ c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_UNUSED,
				ಗಣನಾ omp_clause_code code, ವೃಕ್ಷ list)
{
  ವೃಕ್ಷ c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 4.5:
   nogroup */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_UNUSED, ವೃಕ್ಷ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  ವೃಕ್ಷ c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 4.5:
   simd
   threads */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_UNUSED,
				 ಗಣನಾ omp_clause_code code, ವೃಕ್ಷ list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);
  ವೃಕ್ಷ c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_ಅಂಕೆ_teams (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t ಅಂಕೆ_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      location_t upper_loc = c_parser_peek_token (parser)->location;
      location_t lower_loc = UNKNOWN_LOCATION;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (upper_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
      ವೃಕ್ಷ c, upper = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, lower = NULL_ವೃಕ್ಷ;
      upper = c_fully_fold (upper, ಅಸತ್ಯ, ರಿಕ್ತ);

      ಯದಿ (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  lower_loc = upper_loc;
	  lower = upper;
	  upper_loc = c_parser_peek_token (parser)->location;
	  ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (upper_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
	  upper = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
	  upper = c_fully_fold (upper, ಅಸತ್ಯ, ರಿಕ್ತ);
	}

      parens.skip_until_found_close (parser);

      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (upper))
	  || (lower && !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (lower))))
	{
	  c_parser_error (parser, "expected integer expression");
	  ಪ್ರತ್ಯಾಗಮ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (upper_loc, LE_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು, upper,
			   build_int_cst (ವೃಕ್ಷ_TYPE (upper), 0));
      protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (c, upper_loc);
      ಯದಿ (c == boolean_true_ಗಂಟು)
	{
	  warning_at (upper_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  upper = integer_one_ಗಂಟು;
	}
      ಯದಿ (lower)
	{
	  c = fold_build2_loc (lower_loc, LE_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು, lower,
			       build_int_cst (ವೃಕ್ಷ_TYPE (lower), 0));
	  protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (c, lower_loc);
	  ಯದಿ (c == boolean_true_ಗಂಟು)
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      lower = NULL_ವೃಕ್ಷ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (lower) == INTEGER_CST
		   && ವೃಕ್ಷ_CODE (upper) == INTEGER_CST
		   && ವೃಕ್ಷ_int_cst_lt (upper, lower))
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", lower, upper);
	      lower = NULL_ವೃಕ್ಷ;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_ಅಂಕೆ_TEAMS, "num_teams");

      c = build_omp_clause (ಅಂಕೆ_teams_loc, OMP_CLAUSE_ಅಂಕೆ_TEAMS);
      OMP_CLAUSE_ಅಂಕೆ_TEAMS_UPPER_ಅಭಿವ್ಯಕ್ತಿ (c) = upper;
      OMP_CLAUSE_ಅಂಕೆ_TEAMS_LOWER_ಅಭಿವ್ಯಕ್ತಿ (c) = lower;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_thread_limit (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t ಅಂಕೆ_thread_limit_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
      ವೃಕ್ಷ c, t = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);

      parens.skip_until_found_close (parser);

      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ಪ್ರತ್ಯಾಗಮ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (ಅಭಿವ್ಯಕ್ತಿ_loc, LE_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು, t,
			   build_int_cst (ವೃಕ್ಷ_TYPE (t), 0));
      protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (c, ಅಭಿವ್ಯಕ್ತಿ_loc);
      ಯದಿ (c == boolean_true_ಗಂಟು)
	{
	  warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_ಗಂಟು;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_LIMIT,
				 "thread_limit");

      c = build_omp_clause (ಅಂಕೆ_thread_limit_loc, OMP_CLAUSE_THREAD_LIMIT);
      OMP_CLAUSE_THREAD_LIMIT_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_aligned (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ nl, c;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  ಯದಿ (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
      ವೃಕ್ಷ alignment = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      alignment = c_fully_fold (alignment, ಅಸತ್ಯ, ರಿಕ್ತ);
      ಯದಿ (ವೃಕ್ಷ_CODE (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (alignment))
	  || ವೃಕ್ಷ_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_ವೃಕ್ಷ;
	}

      ಪ್ರತಿ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ nl;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_allocate (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ nl, c;
  ವೃಕ್ಷ allocator = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ align = NULL_ವೃಕ್ಷ;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ಯದಿ ((c_parser_next_token_is_not (parser, CPP_NAME)
       && c_parser_next_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      ತಾರ್ಕಿಕ has_modifiers = ಅಸತ್ಯ;
      ವೃಕ್ಷ orig_type = NULL_ವೃಕ್ಷ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  unsigned ಪೂರ್ಣಾಙ್ಕ n = 3;
	  ಧ್ರುವ ವರ್ಣ *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	  ಯದಿ ((strcmp (p, "allocator") == 0 || strcmp (p, "align") == 0)
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      ಯದಿ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = ಸತ್ಯ;
	      ಅನ್ಯಥಾ ಯದಿ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  ಧ್ರುವ ವರ್ಣ *q = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ);
		  n += 4;
		  ಯದಿ ((strcmp (q, "allocator") == 0
		       || strcmp (q, "align") == 0)
		      && c_parser_check_balanced_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = ಸತ್ಯ;
		}
	    }
	  ಯದಿ (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
	      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
	      ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
		;
	      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "allocator") == 0)
		{
		  allocator = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
		  allocator = c_fully_fold (allocator, ಅಸತ್ಯ, ರಿಕ್ತ);
		  orig_type = ಅಭಿವ್ಯಕ್ತಿ.original_type
			      ? ಅಭಿವ್ಯಕ್ತಿ.original_type : ವೃಕ್ಷ_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      ಅನ್ಯಥಾ
		{
		  align = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
		  align = c_fully_fold (align, ಅಸತ್ಯ, ರಿಕ್ತ);
		}
	      parens2.skip_until_found_close (parser);
	      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  ಧ್ರುವ ವರ್ಣ *q = "";
		  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ);
		  ಯದಿ (strcmp (q, "allocator") != 0 && strcmp (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_found_close (parser);
		      ಪ್ರತ್ಯಾಗಮ list;
		    }
		  ಅನ್ಯಥಾ ಯದಿ (strcmp (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_found_close (parser);
		      ಪ್ರತ್ಯಾಗಮ list;
		    }
		  c_parser_consume_token (parser);
		  ಯದಿ (!parens2.require_open (parser))
		    {
		      parens.skip_until_found_close (parser);
		      ಪ್ರತ್ಯಾಗಮ list;
		    }
		  ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
		  ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
		  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ,
						   ಸತ್ಯ);
		  ಯದಿ (strcmp (q, "allocator") == 0)
		    {
		      allocator = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
		      allocator = c_fully_fold (allocator, ಅಸತ್ಯ, ರಿಕ್ತ);
		      orig_type = ಅಭಿವ್ಯಕ್ತಿ.original_type
				  ? ಅಭಿವ್ಯಕ್ತಿ.original_type : ವೃಕ್ಷ_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  ಅನ್ಯಥಾ
		    {
		      align = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
		      align = c_fully_fold (align, ಅಸತ್ಯ, ರಿಕ್ತ);
		    }
		  parens2.skip_until_found_close (parser);
		}
	    }
	}
      ಯದಿ (!has_modifiers)
	{
	  location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
	  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
	  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
	    {
	      allocator = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
	      allocator = c_fully_fold (allocator, ಅಸತ್ಯ, ರಿಕ್ತ);
	      orig_type = ಅಭಿವ್ಯಕ್ತಿ.original_type
			  ? ಅಭಿವ್ಯಕ್ತಿ.original_type : ವೃಕ್ಷ_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      ಯದಿ (allocator
	  && (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (allocator))
	      || ವೃಕ್ಷ_CODE (orig_type) != ENUMERAL_TYPE
	      || (TYPE_NAME (orig_type)
		  != get_identifier ("omp_allocator_handle_t"))))
        {
          error_at (clause_loc, "%<allocate%> clause allocator expression "
				"has type %qT rather than "
				"%<omp_allocator_handle_t%>",
				ವೃಕ್ಷ_TYPE (allocator));
          allocator = NULL_ವೃಕ್ಷ;
        }
      ಯದಿ (align
	  && (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (align))
	      || !ವೃಕ್ಷ_fits_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_ವೃಕ್ಷ;
	}
      ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_found_close (parser);
	  ಪ್ರತ್ಯಾಗಮ list;
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALLOCATE, list);

  ಯದಿ (allocator || align)
    ಪ್ರತಿ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      {
	OMP_CLAUSE_ALLOCATE_ALLOCATOR (c) = allocator;
	OMP_CLAUSE_ALLOCATE_ALIGN (c) = align;
      }

  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ nl;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_uses_allocators (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ nl = list;
  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

parse_next:

  ತಾರ್ಕಿಕ has_modifiers = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ seen_allocators = ಅಸತ್ಯ;
  ವೃಕ್ಷ memspace_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ traits_var = NULL_ವೃಕ್ಷ;

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      unsigned ಪೂರ್ಣಾಙ್ಕ n = 3;
      ಧ್ರುವ ವರ್ಣ *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ ((strcmp (p, "traits") == 0 || strcmp (p, "memspace") == 0)
	  && c_parser_check_balanced_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  ಯದಿ (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = ಸತ್ಯ;
	  ಅನ್ಯಥಾ ಯದಿ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      ಧ್ರುವ ವರ್ಣ *q = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ);
	      n += 4;
	      ಯದಿ ((strcmp (q, "traits") == 0
		   || strcmp (q, "memspace") == 0)
		  && c_parser_check_balanced_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  ಯದಿ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = ಸತ್ಯ;
		  ಯದಿ ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      ಧ್ರುವ ವರ್ಣ *m = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ);
		      ಯದಿ (strcmp (p, m) == 0 || strcmp (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  ಗಚ್ಛ end;
			}
		    }
		}
	    }
	}
      ಯದಿ (has_modifiers)
	{
	  c_parser_consume_token (parser);
	  matching_parens parens2;
	  parens2.require_open (parser);
	  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	    ;
	  ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "traits") == 0)
	    {
	      traits_var = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
	      traits_var = c_fully_fold (traits_var, ಅಸತ್ಯ, ರಿಕ್ತ);
	      mark_exp_read (traits_var);
	    }
	  ಅನ್ಯಥಾ
	    {
	      memspace_ಅಭಿವ್ಯಕ್ತಿ = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
	      memspace_ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (memspace_ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ರಿಕ್ತ);
	    }
	  parens2.skip_until_found_close (parser);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      ಧ್ರುವ ವರ್ಣ *q = "";
	      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
		q = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ);
	      ಯದಿ (strcmp (q, "traits") != 0 && strcmp (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_found_close (parser);
		  ಪ್ರತ್ಯಾಗಮ list;
		}
	      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_found_close (parser);
		  ಪ್ರತ್ಯಾಗಮ list;
		}
	      c_parser_consume_token (parser);
	      ಯದಿ (!parens2.require_open (parser))
		{
		  parens.skip_until_found_close (parser);
		  ಪ್ರತ್ಯಾಗಮ list;
		}
	      ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	      ಯದಿ (strcmp (q, "traits") == 0)
		{
		  traits_var = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
		  traits_var = c_fully_fold (traits_var, ಅಸತ್ಯ, ರಿಕ್ತ);
		  mark_exp_read (traits_var);
		}
	      ಅನ್ಯಥಾ
		{
		  memspace_ಅಭಿವ್ಯಕ್ತಿ = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
		  memspace_ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (memspace_ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ರಿಕ್ತ);
		}
	      parens2.skip_until_found_close (parser);
	    }
	  ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    ಗಚ್ಛ end;
	}
    }

  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      ಧ್ರುವ ವರ್ಣ *tok_s = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ);
      ವೃಕ್ಷ t = lookup_name (tok->ಮೌಲ್ಯ);
      ಯದಿ (t == NULL_ವೃಕ್ಷ)
	{
	  undeclared_variable (tok->location, tok->ಮೌಲ್ಯ);
	  t = error_mark_ಗಂಟು;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      ವೃಕ್ಷ legacy_traits = NULL_ವೃಕ್ಷ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  ಧ್ರುವ ವರ್ಣ *tok_a
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_found_close (parser);

	  ಯದಿ (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      ಗಚ್ಛ end;
	    }
	  legacy_traits = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
	  ಯದಿ (legacy_traits == error_mark_ಗಂಟು)
	    ಗಚ್ಛ end;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  ಯದಿ (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.add_fixit_replace (alloc_loc, "traits");
	      richloc.add_fixit_ಸೇರಿಸು_after (close_loc, ": ");
	      richloc.add_fixit_ಸೇರಿಸು_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      ಯದಿ (seen_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  ಗಚ್ಛ end;
	}
      seen_allocators = ಸತ್ಯ;

      ವೃಕ್ಷ c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_USES_ALLOCATORS);
      OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c) = memspace_ಅಭಿವ್ಯಕ್ತಿ;
      OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
    }

  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      ಗಚ್ಛ parse_next;
    }

 end:
  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ nl;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_linear (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  ವೃಕ್ಷ nl, c, step;
  ಗಣನಾ omp_clause_linear_kind kind = OMP_CLAUSE_LINEAR_DEFAULT;
  ತಾರ್ಕಿಕ old_linear_modifier = ಅಸತ್ಯ;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ);
      ಯದಿ (strcmp ("val", p) == 0)
	kind = OMP_CLAUSE_LINEAR_VAL;
      ಯದಿ (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	kind = OMP_CLAUSE_LINEAR_DEFAULT;
      ಯದಿ (kind != OMP_CLAUSE_LINEAR_DEFAULT)
	{
	  old_linear_modifier = ಸತ್ಯ;
	  rm1_loc = make_location (tok->location, tok->location,
				   c_parser_peek_2nd_token (parser)->location);
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_LINEAR, list);

  ಯದಿ (kind != OMP_CLAUSE_LINEAR_DEFAULT)
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
    }

  ಯದಿ (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = ಅಭಿವ್ಯಕ್ತಿ_loc;
      ತಾರ್ಕಿಕ has_modifiers = ಅಸತ್ಯ;
      ಯದಿ (kind == OMP_CLAUSE_LINEAR_DEFAULT
	  && c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ);
	  unsigned ಪೂರ್ಣಾಙ್ಕ pos = 0;
	  ಯದಿ (strcmp ("val", p) == 0)
	    pos = 2;
	  ಅನ್ಯಥಾ ಯದಿ (strcmp ("step", p) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      pos = 3;
	      ಯದಿ (c_parser_check_balanced_raw_token_sequence (parser, &pos)
		  && (c_parser_peek_nth_token_raw (parser, pos)->type
		      == CPP_CLOSE_PAREN))
		++pos;
	      ಅನ್ಯಥಾ
		pos = 0;
	    }
	  ಯದಿ (pos)
	    {
	      tok = c_parser_peek_nth_token_raw (parser, pos);
	      ಯದಿ (tok->type == CPP_COMMA || tok->type == CPP_CLOSE_PAREN)
		has_modifiers = ಸತ್ಯ;
	    }
	}
      ಯದಿ (has_modifiers)
	{
	  step = NULL_ವೃಕ್ಷ;
	  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ);
	      ಯದಿ (strcmp ("val", p) == 0)
		{
		  ಯದಿ (kind != OMP_CLAUSE_LINEAR_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  kind = OMP_CLAUSE_LINEAR_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      ಅನ್ಯಥಾ ಯದಿ (strcmp ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  ಯದಿ (parens2.require_open (parser))
		    {
		      ಯದಿ (step)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
		      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
		      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ,
						       ಸತ್ಯ);
		      step = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
		      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (step)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  step = integer_one_ಗಂಟು;
			}
		      parens2.skip_until_found_close (parser);
		    }
		  ಅನ್ಯಥಾ
		    ಭಙ್ಗ;
		}
	      ಅನ್ಯಥಾ
		ಭಙ್ಗ;
	      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ಅನುವರ್ತ;
		}
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (!step)
	    step = integer_one_ಗಂಟು;
	}
      ಅನ್ಯಥಾ
	{
	  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
	  step = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
	  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (step)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      step = integer_one_ಗಂಟು;
	    }
	}

    }
  ಅನ್ಯಥಾ
    step = integer_one_ಗಂಟು;

  ಪ್ರತಿ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_LINEAR_STEP (c) = step;
      OMP_CLAUSE_LINEAR_KIND (c) = kind;
      OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c) = old_linear_modifier;
    }

  ಯದಿ (old_linear_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      ಯದಿ (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_remove (rm1_loc);
	  ಯದಿ (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.add_fixit_remove (rm2_loc);
	      richloc.add_fixit_ಸೇರಿಸು_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.add_fixit_ಸೇರಿಸು_before (close_loc, ")");
	    }
	  ಅನ್ಯಥಾ
	    richloc.add_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_nontemporal (c_parser *parser, ವೃಕ್ಷ list)
{
  ಪ್ರತ್ಯಾಗಮ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_safelen (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ c, t;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
  t = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
  t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);
  ಯದಿ (ವೃಕ್ಷ_CODE (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t))
      || ವೃಕ್ಷ_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_ವೃಕ್ಷ;
    }

  parens.skip_until_found_close (parser);
  ಯದಿ (t == NULL_ವೃಕ್ಷ || t == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_simdlen (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ c, t = NULL_ವೃಕ್ಷ, type = NULL_ವೃಕ್ಷ, ಭಾಜಕ = NULL_ವೃಕ್ಷ;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  unsigned pos = 3;
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ),
		 "scaled") == 0
      && c_parser_check_balanced_raw_token_sequence (parser, &pos)
      && c_parser_peek_nth_token_raw (parser, ++pos)->type == CPP_COLON)
    {
      c_parser_consume_token (parser);
      matching_parens parens2;
      parens2.require_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      ಸಂರಚನಾ c_type_name *ctype = c_parser_type_name (parser);
      ಯದಿ (ctype == ರಿಕ್ತ
	  || (type = groktypename (ctype, ರಿಕ್ತ, ರಿಕ್ತ)) == ರಿಕ್ತ
	  || (!INTEGRAL_TYPE_P (type)
	      && !SCALAR_FLOAT_TYPE_P (type)
	      && ವೃಕ್ಷ_CODE (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
	  ಭಾಜಕ = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
	  ಭಾಜಕ = c_fully_fold (ಭಾಜಕ, ಅಸತ್ಯ, ರಿಕ್ತ);
	  ಯದಿ (ವೃಕ್ಷ_CODE (ಭಾಜಕ) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಭಾಜಕ))
	      || ವೃಕ್ಷ_int_cst_sgn (ಭಾಜಕ) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_ಗಂಟು;
	    }
	}
      parens2.skip_until_found_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  ಯದಿ (type != error_mark_ಗಂಟು)
    {
      location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
      t = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);
      ಯದಿ (ವೃಕ್ಷ_CODE (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t))
	  || ವೃಕ್ಷ_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_ವೃಕ್ಷ;
	}
    }

  parens.skip_until_found_close (parser);
  ಯದಿ (type == error_mark_ಗಂಟು || t == NULL_ವೃಕ್ಷ || t == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_ಭಾಜಕ (c) = ಭಾಜಕ;
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   ವೃಕ್ಷ list, ತಾರ್ಕಿಕ depend_p)
{
  ವೃಕ್ಷ vec = ರಿಕ್ತ;
  ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      ಪ್ರತ್ಯಾಗಮ list;
    }

  ಯದಿ (!depend_p)
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_ಸಂಖ್ಯೆ
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  ವೃಕ್ಷ val = c_parser_peek_nth_token (parser, 3)->ಮೌಲ್ಯ;
	  ಯದಿ (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      ವೃಕ್ಷ u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      ಪ್ರತ್ಯಾಗಮ u;
	    }
	}
    }



  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_kind == C_ID_ID)
    {
      ವೃಕ್ಷ t = lookup_name (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ವೃಕ್ಷ addend = ರಿಕ್ತ;

      ಯದಿ (t == NULL_ವೃಕ್ಷ)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	  t = error_mark_ಗಂಟು;
	}

      c_parser_consume_token (parser);

      ತಾರ್ಕಿಕ neg = ಅಸತ್ಯ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_MINUS))
	neg = ಸತ್ಯ;
      ಅನ್ಯಥಾ ಯದಿ (!c_parser_next_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_ಗಂಟು;
	  neg = ಅಸತ್ಯ;
	  ಗಚ್ಛ add_to_vector;
	}
      c_parser_consume_token (parser);

      ಯದಿ (c_parser_next_token_is_not (parser, CPP_ಸಂಖ್ಯೆ))
	{
	  c_parser_error (parser, "expected integer");
	  ಪ್ರತ್ಯಾಗಮ list;
	}

      addend = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      ಯದಿ (ವೃಕ್ಷ_CODE (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  ಪ್ರತ್ಯಾಗಮ list;
	}
      c_parser_consume_token (parser);

    add_to_vector:
      ಯದಿ (t != error_mark_ಗಂಟು)
	{
	  vec = ವೃಕ್ಷ_cons (addend, t, vec);
	  ಯದಿ (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      ಯದಿ (c_parser_next_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_kind != C_ID_ID)
	ಭಙ್ಗ;

      c_parser_consume_token (parser);
    }

  ಯದಿ (vec == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ list;

  ವೃಕ್ಷ u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
  OMP_CLAUSE_DOACROSS_DEPEND (u) = depend_p;
  OMP_CLAUSE_DECL (u) = nreverse (vec);
  OMP_CLAUSE_CHAIN (u) = list;
  ಪ್ರತ್ಯಾಗಮ u;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_iterators (c_parser *parser)
{
  ವೃಕ್ಷ ret = NULL_ವೃಕ್ಷ, *last = &ret;
  c_parser_consume_token (parser);

  ತಳ್ಳು_scope ();

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಕುರು
    {
      ವೃಕ್ಷ iter_type = NULL_ವೃಕ್ಷ, type_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
      ಯದಿ (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
	{
	  ಸಂರಚನಾ c_type_name *type = c_parser_type_name (parser);
	  ಯದಿ (type != ರಿಕ್ತ)
	    iter_type = groktypename (type, &type_ಅಭಿವ್ಯಕ್ತಿ, ರಿಕ್ತ);
	}
      ಯದಿ (iter_type == NULL_ವೃಕ್ಷ)
	iter_type = integer_type_ಗಂಟು;

      location_t loc = c_parser_peek_token (parser)->location;
      ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  ಭಙ್ಗ;
	}

      ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      c_parser_consume_token (parser);

      ಯದಿ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	ಭಙ್ಗ;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (eloc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಅಸತ್ಯ);
      ವೃಕ್ಷ begin = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;

      ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ಭಙ್ಗ;

      eloc = c_parser_peek_token (parser)->location;
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (eloc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಅಸತ್ಯ);
      ವೃಕ್ಷ end = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;

      ವೃಕ್ಷ step = integer_one_ಗಂಟು;
      ಯದಿ (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (eloc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಅಸತ್ಯ);
	  step = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
	}

      ವೃಕ್ಷ iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *last = make_omp_iterator ();
      OMP_ITERATOR_VAR (*last) = iter_var;
      OMP_ITERATOR_BEGIN (*last) = begin;
      OMP_ITERATOR_END (*last) = end;
      OMP_ITERATOR_STEP (*last) = step;
      last = &ವೃಕ್ಷ_CHAIN (*last);

      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  ಅನುವರ್ತ;
	}
      ಭಙ್ಗ;
    }
  ಯಾವತ್ (1);

  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ ret ? ret : error_mark_ಗಂಟು;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_affinity (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ nl, iterators = NULL_ವೃಕ್ಷ;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ತಾರ್ಕಿಕ parse_iter = ((strcmp ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      ಯದಿ (parse_iter)
	{
	  unsigned n = 3;
	  parse_iter = (c_parser_check_balanced_raw_token_sequence (parser, &n)
			&& (c_parser_peek_nth_token_raw (parser, n)->type
			    == CPP_CLOSE_PAREN)
			&& (c_parser_peek_nth_token_raw (parser, n + 1)->type
			    == CPP_COLON));
	}
      ಯದಿ (parse_iter)
	{
	  iterators = c_parser_omp_iterators (parser);
	  ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    {
	      ಯದಿ (iterators)
		ತೆಗೆ_scope ();
	      parens.skip_until_found_close (parser);
	      ಪ್ರತ್ಯಾಗಮ list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  ಯದಿ (iterators)
    {
      ವೃಕ್ಷ block = ತೆಗೆ_scope ();
      ಯದಿ (iterators != error_mark_ಗಂಟು)
	{
	  OMP_ITERATOR_BLOCK (iterators) = block;
	  ಪ್ರತಿ (ವೃಕ್ಷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_ವೃಕ್ಷ_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ nl;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_depend (c_parser *parser, ವೃಕ್ಷ list, location_t here)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ಗಣನಾ omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_LAST;
  ಗಣನಾ omp_clause_doacross_kind dkind = OMP_CLAUSE_DOACROSS_LAST;
  ವೃಕ್ಷ nl, c, iterators = NULL_ವೃಕ್ಷ;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ಕುರು
    {
      ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
	ಗಚ್ಛ invalid_kind;

      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp ("iterator", p) == 0 && iterators == NULL_ವೃಕ್ಷ)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  ಅನುವರ್ತ;
	}
      ಯದಿ (strcmp ("in", p) == 0)
	kind = OMP_CLAUSE_DEPEND_IN;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("inout", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUT;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("inoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUTSET;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("mutexinoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("out", p) == 0)
	kind = OMP_CLAUSE_DEPEND_OUT;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("depobj", p) == 0)
	kind = OMP_CLAUSE_DEPEND_DEPOBJ;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SOURCE;
	}
      ಅನ್ಯಥಾ
	ಗಚ್ಛ invalid_kind;
      ಭಙ್ಗ;
    }
  ಯಾವತ್ (1);

  c_parser_consume_token (parser);

  ಯದಿ (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_SOURCE
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      ತೆಗೆ_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_SOURCE ? "source" : "sink");
      iterators = NULL_ವೃಕ್ಷ;
    }

  ಯದಿ (dkind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_ವೃಕ್ಷ;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_found_close (parser);
      ಪ್ರತ್ಯಾಗಮ c;
    }

  ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    ಗಚ್ಛ resync_fail;

  ಯದಿ (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, ಸತ್ಯ);
  ಅನ್ಯಥಾ
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      ಯದಿ (iterators)
	{
	  ವೃಕ್ಷ block = ತೆಗೆ_scope ();
	  ಯದಿ (iterators == error_mark_ಗಂಟು)
	    iterators = NULL_ವೃಕ್ಷ;
	  ಅನ್ಯಥಾ
	    OMP_ITERATOR_BLOCK (iterators) = block;
	}

      ಪ್ರತಿ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_KIND (c) = kind;
	  ಯದಿ (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_ವೃಕ್ಷ_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ nl;

 invalid_kind:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  ಯದಿ (iterators)
    ತೆಗೆ_scope ();
  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_doacross (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ಗಣನಾ omp_clause_doacross_kind kind = OMP_CLAUSE_DOACROSS_LAST;
  ವೃಕ್ಷ nl;
  ಧ್ರುವ ವರ್ಣ *p;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME))
    ಗಚ್ಛ invalid_kind;

  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
  ಯದಿ (strcmp ("sink", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SINK;
  ಅನ್ಯಥಾ ಯದಿ (strcmp ("source", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SOURCE;
  ಅನ್ಯಥಾ
    ಗಚ್ಛ invalid_kind;

  c_parser_consume_token (parser);

  ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    ಗಚ್ಛ resync_fail;

  ಯದಿ (kind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (nl) = OMP_CLAUSE_DOACROSS_SOURCE;
      OMP_CLAUSE_DECL (nl) = NULL_ವೃಕ್ಷ;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  ಅನ್ಯಥಾ
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, ಅಸತ್ಯ);

  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ nl;

 invalid_kind:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ಗಣನಾ omp_clause_fallback_kind kind = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  unsigned n = 3;
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  ಪ್ರತ್ಯಾಗಮ list;
	}
      c_parser_consume_token (parser);
      ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	ಪ್ರತ್ಯಾಗಮ list;
      p = "";
      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "abort") == 0)
	kind = OMP_CLAUSE_FALLBACK_ABORT;
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "default_mem") == 0)
	kind = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "null") == 0)
	kind = OMP_CLAUSE_FALLBACK_NULL;
      ಅನ್ಯಥಾ
	{
	  c_parser_error (parser, "expected %<abort%>, %<default_mem%>, or "
				  "%<null%> as fallback mode");
	  ಪ್ರತ್ಯಾಗಮ list;
	}
      c_parser_consume_token (parser);
      ಯದಿ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	ಪ್ರತ್ಯಾಗಮ list;
      ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ಪ್ರತ್ಯಾಗಮ list;
    }
  location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
  ವೃಕ್ಷ size = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
  parens.skip_until_found_close (parser);

  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (size)))
    {
      error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, "expected integer expression");
      ಪ್ರತ್ಯಾಗಮ list;
    }

  /* Attempt to statically determine when the number is negative.  */
  ವೃಕ್ಷ c = fold_build2_loc (ಅಭಿವ್ಯಕ್ತಿ_loc, LT_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು, size,
			    build_int_cst (ವೃಕ್ಷ_TYPE (size), 0));
  protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (c, ಅಭಿವ್ಯಕ್ತಿ_loc);
  ಯದಿ (c == boolean_true_ಗಂಟು)
    {
      warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      size = integer_zero_ಗಂಟು;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_KIND (c) = kind;
  OMP_CLAUSE_DYN_GROUPPRIVATE_ಅಭಿವ್ಯಕ್ತಿ (c) = size;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  ಪ್ರತ್ಯಾಗಮ list;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_map (c_parser *parser, ವೃಕ್ಷ list, ತಾರ್ಕಿಕ declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ nl, c;
  ಗಣನಾ gomp_map_kind kind = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ಪೂರ್ಣಾಙ್ಕ pos = 1;
  ಪೂರ್ಣಾಙ್ಕ map_kind_pos = 0;
  ಪೂರ್ಣಾಙ್ಕ iterator_length = 0;
  ಪ್ರತಿ (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      ಯದಿ (tok->type != CPP_NAME)
	ಭಙ್ಗ;

      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ);
      c_token *next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      ಯದಿ (strcmp (p, "iterator") == 0 && next_tok->type == CPP_OPEN_PAREN)
	{
	  unsigned n = pos + 2;
	  ಯದಿ (c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_length = n - pos + 1;
	      pos = n;
	      next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      ಯದಿ (next_tok->type == CPP_COLON)
	{
	  map_kind_pos = pos;
	  ಭಙ್ಗ;
	}

      ಯದಿ (next_tok->type == CPP_COMMA)
	pos++;
      ಅನ್ಯಥಾ ಯದಿ (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  unsigned ಪೂರ್ಣಾಙ್ಕ npos = pos + 2;
	  ಯದಿ (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, npos + 1)->type
		  == CPP_COMMA))
	    pos = npos + 1;
	}

      pos++;
    }

  ಪೂರ್ಣಾಙ್ಕ always_modifier = 0;
  ಪೂರ್ಣಾಙ್ಕ close_modifier = 0;
  ಪೂರ್ಣಾಙ್ಕ present_modifier = 0;
  ಪೂರ್ಣಾಙ್ಕ mapper_modifier = 0;
  ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_commas = 0;
  ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_identifiers = 0;
  ವೃಕ್ಷ mapper_name = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ iterators = NULL_ವೃಕ್ಷ;
  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ pos = 1; pos < map_kind_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      ಯದಿ (tok->type == CPP_COMMA)
	{
	  ++ಅಂಕೆ_commas;
	  ಯದಿ (ಅಂಕೆ_commas > ಅಂಕೆ_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  ಅನುವರ್ತ;
	}

      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ);
      ಯದಿ (strcmp ("always", p) == 0)
	{
	  ಯದಿ (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_found_close (parser);
	      ಪ್ರತ್ಯಾಗಮ list;
	    }
	  always_modifier++;
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("close", p) == 0)
	{
	  ಯದಿ (close_modifier)
	    {
	      c_parser_error (parser, "too many %<close%> modifiers");
	      parens.skip_until_found_close (parser);
	      ಪ್ರತ್ಯಾಗಮ list;
	    }
	  close_modifier++;
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("iterator", p) == 0)
	{
	  ಯದಿ (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      ಪ್ರತ್ಯಾಗಮ list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  ಯದಿ (mparens.require_open (parser))
	    {
	      ಯದಿ (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  ಪ್ರತ್ಯಾಗಮ list;
		}

	      tok = c_parser_peek_token (parser);

	      ವಿಕಲ್ಪ (tok->type)
		{
		ಪಕ್ಷ CPP_NAME:
		  {
		    mapper_name = tok->ಮೌಲ್ಯ;
		    c_parser_consume_token (parser);
		    ಯದಿ (declare_mapper_p)
		      {
			error_at (tok->location,
				  "in %<declare mapper%> directives, parameter "
				  "to %<mapper%> modifier must be %<default%>");
		      }
		  }
		  ಭಙ್ಗ;

		ಪಕ್ಷ CPP_KEYWORD:
		  ಯದಿ (tok->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      ಭಙ್ಗ;
		    }
		  /* Fallthrough.  */

		ಸ್ವಭಾವ:
		  error_at (tok->location,
			    "expected identifier or %<default%>");
		  ಪ್ರತ್ಯಾಗಮ list;
		}

	      ಯದಿ (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  ಪ್ರತ್ಯಾಗಮ list;
		}

	      mapper_modifier++;
	      pos += 3;
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("present", p) == 0)
	{
	  ಯದಿ (present_modifier)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      ಪ್ರತ್ಯಾಗಮ list;
	    }
	  present_modifier++;
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ
	{
	  c_parser_error (parser, "%<map%> clause with map-type modifier other "
				  "than %<always%>, %<close%>, %<iterator%>, "
				  "%<mapper%> or %<present%>");
	  parens.skip_until_found_close (parser);
	  ಪ್ರತ್ಯಾಗಮ list;
	}
      ++ಅಂಕೆ_identifiers;
      ಯದಿ (ಅಂಕೆ_identifiers - 1 > ಅಂಕೆ_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_ಸೇರಿಸು_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      ಅಂಕೆ_commas = ಅಂಕೆ_identifiers - 1;
    }

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಪೂರ್ಣಾಙ್ಕ always_present_modifier = always_modifier && present_modifier;

      ಯದಿ (strcmp ("alloc", p) == 0)
	kind = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("to", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TO
		: present_modifier ? GOMP_MAP_PRESENT_TO
		: always_modifier ? GOMP_MAP_ALWAYS_TO
		: GOMP_MAP_TO);
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("from", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("tofrom", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("release", p) == 0)
	kind = GOMP_MAP_RELEASE;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("delete", p) == 0)
	kind = GOMP_MAP_DELETE;
      ಅನ್ಯಥಾ
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ಪ್ರತ್ಯಾಗಮ list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   ಸತ್ಯ);

  ವೃಕ್ಷ last_new = NULL_ವೃಕ್ಷ;

  ಯದಿ (iterators)
    {
      ವೃಕ್ಷ block = ತೆಗೆ_scope ();
      ಯದಿ (iterators == error_mark_ಗಂಟು)
	iterators = NULL_ವೃಕ್ಷ;
      ಅನ್ಯಥಾ
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  ಪ್ರತಿ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      last_new = c;
    }

  ಯದಿ (mapper_name)
    {
      ವೃಕ್ಷ name = build_omp_clause (ಒಳಹರಿವು_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_ತಳ್ಳು_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (ಒಳಹರಿವು_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_ತೆಗೆ_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_ಗಂಟು;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_device (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t ಅಭಿವ್ಯಕ್ತಿ_loc;
  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  ವೃಕ್ಷ c, t;
  ತಾರ್ಕಿಕ ancestor = ಅಸತ್ಯ;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ);
      ಯದಿ (strcmp ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  ಯದಿ ((omp_requires_mask & OMP_REQUIRES_REVERSE_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_found_close (parser);
	      ಪ್ರತ್ಯಾಗಮ list;
	    }
	  ancestor = ಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("device_num", p) == 0)
	;
      ಅನ್ಯಥಾ
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_found_close (parser);
	  ಪ್ರತ್ಯಾಗಮ list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
  ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
  t = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
  t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);

  parens.skip_until_found_close (parser);

  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      ಪ್ರತ್ಯಾಗಮ list;
    }
  ಯದಿ (ancestor && ವೃಕ್ಷ_CODE (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, "the %<device%> clause expression must evaluate to "
			  "%<1%>");
      ಪ್ರತ್ಯಾಗಮ list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE, "device");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE);

  OMP_CLAUSE_DEVICE_ID (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEVICE_ANCESTOR (c) = ancestor;

  list = c;
  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 4.0:
   dist_schedule ( static )
   dist_schedule ( static , expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_dist_schedule (c_parser *parser, ವೃಕ್ಷ list)
{
  ವೃಕ್ಷ c, t = NULL_ವೃಕ್ಷ;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ಯದಿ (!c_parser_next_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      ಪ್ರತ್ಯಾಗಮ list;
    }

  c_parser_consume_token (parser);
  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
      t = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);
      parens.skip_until_found_close (parser);
    }
  ಅನ್ಯಥಾ
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  ಯದಿ (omp_find_clause (list, OMP_CLAUSE_DIST_SCHEDULE))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  ಯದಿ (t == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_SCHEDULE);
  OMP_CLAUSE_DIST_SCHEDULE_CHUNK_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_proc_bind (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ಗಣನಾ omp_clause_proc_bind_kind kind;
  ವೃಕ್ಷ c;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp ("primary", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_PRIMARY;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  kind = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("close", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_CLOSE;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("spread", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_SPREAD;
      ಅನ್ಯಥಾ
	ಗಚ್ಛ invalid_kind;
    }
  ಅನ್ಯಥಾ
    ಗಚ್ಛ invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;

 invalid_kind:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_device_type (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ಗಣನಾ omp_clause_device_type_kind kind;
  ವೃಕ್ಷ c;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp ("host", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_HOST;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("nohost", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("any", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_ANY;
      ಅನ್ಯಥಾ
	ಗಚ್ಛ invalid_kind;
    }
  ಅನ್ಯಥಾ
    ಗಚ್ಛ invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;

 invalid_kind:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 4.0:
   from ( variable-list )
   to ( variable-list )

   OpenMP 5.1:
   from ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )
   to ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )

   motion-modifier:
     present | iterator (iterators-definition) | mapper (id)  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_from_to (c_parser *parser, ಗಣನಾ omp_clause_code kind,
			     ವೃಕ್ಷ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ಪೂರ್ಣಾಙ್ಕ pos = 1, colon_pos = 0;
  ಪೂರ್ಣಾಙ್ಕ iterator_length = 0;

  ಯಾವತ್ (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      ಧ್ರುವ ವರ್ಣ *identifier =
	IDENTIFIER_POINTER (c_parser_peek_nth_token_raw (parser, pos)->ಮೌಲ್ಯ);
      ಯದಿ (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  unsigned ಪೂರ್ಣಾಙ್ಕ npos = pos + 2;
	  ಯದಿ (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      ಯದಿ (strcmp (identifier, "iterator") == 0)
		iterator_length = npos - pos + 1;
	      pos = npos;
	    }
	}
      ಯದಿ (c_parser_peek_nth_token_raw (parser, pos + 1)->type == CPP_COMMA)
	pos += 2;
      ಅನ್ಯಥಾ
	pos++;
      ಯದಿ (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_COLON)
	{
	  colon_pos = pos;
	  ಭಙ್ಗ;
	}
    }

  ತಾರ್ಕಿಕ present = ಅಸತ್ಯ, mapper_modifier = ಅಸತ್ಯ;
  ವೃಕ್ಷ iterators = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ mapper_name = NULL_ವೃಕ್ಷ;

  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      ಯದಿ (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ಅನುವರ್ತ;
	}
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (token->ಮೌಲ್ಯ);
      ಯದಿ (strcmp ("present", p) == 0)
	{
	  ಯದಿ (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      ಪ್ರತ್ಯಾಗಮ list;
	    }
	  present = ಸತ್ಯ;
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("iterator", p) == 0)
	{
	  ಯದಿ (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      ಪ್ರತ್ಯಾಗಮ list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  ಯದಿ (mparens.require_open (parser))
	    {
	      ಯದಿ (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  ಪ್ರತ್ಯಾಗಮ list;
		}

	      token = c_parser_peek_token (parser);
	      ವಿಕಲ್ಪ (token->type)
		{
		ಪಕ್ಷ CPP_NAME:
		  {
		    mapper_name = token->ಮೌಲ್ಯ;
		    c_parser_consume_token (parser);
		  }
		  ಭಙ್ಗ;
		ಪಕ್ಷ CPP_KEYWORD:
		  ಯದಿ (token->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      ಭಙ್ಗ;
		    }
		  /* FALLTHROUGH  */
		ಸ್ವಭಾವ:
		  error_at (token->location,
			    "expected identifier or %<default%>");
		  ಪ್ರತ್ಯಾಗಮ list;
		}
	      ಯದಿ (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  ಪ್ರತ್ಯಾಗಮ list;
		}
	      mapper_modifier = ಸತ್ಯ;
	      pos += 3;
	    }
	}
      ಅನ್ಯಥಾ
	{
	  error_at (token->location,
		    "%qs clause with modifier other than %<iterator%>, "
		    "%<mapper%>, or %<present%>",
		    kind == OMP_CLAUSE_TO ? "to" : "from");
	  parens.skip_until_found_close (parser);
	  ಪ್ರತ್ಯಾಗಮ list;
	}
    }

  ಯದಿ (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  ವೃಕ್ಷ nl = c_parser_omp_variable_list (parser, loc, kind, list);
  parens.skip_until_found_close (parser);

  ಯದಿ (present)
    ಪ್ರತಿ (ವೃಕ್ಷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  ಯದಿ (iterators)
    {
      ವೃಕ್ಷ block = ತೆಗೆ_scope ();
      ಯದಿ (iterators == error_mark_ಗಂಟು)
	iterators = NULL_ವೃಕ್ಷ;
      ಅನ್ಯಥಾ
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  ಯದಿ (iterators)
    ಪ್ರತಿ (ವೃಕ್ಷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  ಯದಿ (mapper_name)
    {
      ವೃಕ್ಷ last_new = NULL_ವೃಕ್ಷ;
      ಪ್ರತಿ (ವೃಕ್ಷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	last_new = c;

      ವೃಕ್ಷ name = build_omp_clause (ಒಳಹರಿವು_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_ತಳ್ಳು_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (ಒಳಹರಿವು_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_ತೆಗೆ_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_ಗಂಟು;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  ಪ್ರತ್ಯಾಗಮ nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_uniform (c_parser *parser, ವೃಕ್ಷ list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_UNIFORM,
					 list);
      parens.skip_until_found_close (parser);
    }
  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 5.1
   full */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_full (c_parser *parser, ವೃಕ್ಷ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_FULL, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ c = build_omp_clause (loc, OMP_CLAUSE_FULL);
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_partial (c_parser *parser, ವೃಕ್ಷ list)
{
  ವೃಕ್ಷ ಅಂಕೆ = NULL_ವೃಕ್ಷ;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      ಅಂಕೆ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ).ಮೌಲ್ಯ;
      parens.skip_until_found_close (parser);

      ಯದಿ (ಅಂಕೆ == error_mark_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ list;

      mark_exp_read (ಅಂಕೆ);
      ಅಂಕೆ = c_fully_fold (ಅಂಕೆ, ಅಸತ್ಯ, ರಿಕ್ತ);
      HOST_WIDE_INT n;
      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಂಕೆ))
	  || !ವೃಕ್ಷ_fits_shwi_p (ಅಂಕೆ)
	  || (n = ವೃಕ್ಷ_to_shwi (ಅಂಕೆ)) <= 0
	  || (ಪೂರ್ಣಾಙ್ಕ) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  ಪ್ರತ್ಯಾಗಮ list;
	}
    }

  ವೃಕ್ಷ c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_ಅಭಿವ್ಯಕ್ತಿ (c) = ಅಂಕೆ;
  OMP_CLAUSE_CHAIN (c) = list;
  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_novariants (c_parser *parser, ವೃಕ್ಷ list)
{
  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
  ವೃಕ್ಷ t = convert_lvalue_to_rvalue (loc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  ವೃಕ್ಷ c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_nocontext (c_parser *parser, ವೃಕ್ಷ list)
{
  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
  ವೃಕ್ಷ t = convert_lvalue_to_rvalue (loc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  ವೃಕ್ಷ c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_ಅಭಿವ್ಯಕ್ತಿ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  ಪ್ರತ್ಯಾಗಮ list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_detach (c_parser *parser, ವೃಕ್ಷ list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_found_close (parser);
      ಪ್ರತ್ಯಾಗಮ list;
    }

  ವೃಕ್ಷ t = lookup_name (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
  ಯದಿ (t == NULL_ವೃಕ್ಷ)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      parens.skip_until_found_close (parser);
      ಪ್ರತ್ಯಾಗಮ list;
    }
  c_parser_consume_token (parser);

  ವೃಕ್ಷ type = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (t));
  ಯದಿ (!INTEGRAL_TYPE_P (type)
      || ವೃಕ್ಷ_CODE (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_found_close (parser);
      ಪ್ರತ್ಯಾಗಮ list;
    }

  ವೃಕ್ಷ u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_found_close (parser);
  ಪ್ರತ್ಯಾಗಮ u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_destroy (c_parser *parser, ವೃಕ್ಷ list)
{
  ವೃಕ್ಷ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  ಪ್ರತಿ (ವೃಕ್ಷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    ವೃಕ್ಷ_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
  ಪ್ರತ್ಯಾಗಮ nl;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  ಯದಿ (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    ಯಾವತ್ (ಸತ್ಯ)
      {
	str += (ವರ್ಣ) GOMP_INTEROP_IFR_SEPARATOR;
	ಯದಿ (c_parser_next_token_is (parser, CPP_STRING))
	  {
	    c_ಅಭಿವ್ಯಕ್ತಿ cval = c_parser_string_literal (parser, ಅಸತ್ಯ, ಅಸತ್ಯ);
	    ಯದಿ (cval.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	    ಯದಿ ((size_t) ವೃಕ್ಷ_STRING_LENGTH (cval.ಮೌಲ್ಯ)
		!= strlen (ವೃಕ್ಷ_STRING_POINTER (cval.ಮೌಲ್ಯ)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = ಸತ್ಯ;
		ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	      }

	    ವರ್ಣ c = omp_get_fr_id_from_name (ವೃಕ್ಷ_STRING_POINTER (cval.ಮೌಲ್ಯ));
	    ಯದಿ (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  ವೃಕ್ಷ_STRING_POINTER (cval.ಮೌಲ್ಯ));
	    str += c;
	  }
	ಅನ್ಯಥಾ
	  {
	    c_ಅಭಿವ್ಯಕ್ತಿ cval = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	    ವೃಕ್ಷ ಮೌಲ್ಯ = c_fully_fold (cval.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
	    ಯದಿ (INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ))
		&& ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != INTEGER_CST)
	      ಮೌಲ್ಯ = convert_lvalue_to_rvalue (cval.get_start (), cval,
						ಅಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;
	    ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != INTEGER_CST
		|| !ವೃಕ್ಷ_fits_shwi_p (ಮೌಲ್ಯ))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	      }
	    HOST_WIDE_INT n = ವೃಕ್ಷ_to_shwi (ಮೌಲ್ಯ);
	    ಯದಿ (n < 1 || n > GOMP_INTEROP_IFR_LAST)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (ವರ್ಣ) n;
	  }
	str += (ವರ್ಣ) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    ಅನುವರ್ತ;
	  }
	ಯದಿ (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	str += '\0';
	ವೃಕ್ಷ res = build_string (str.length (), str.data ());
	ವೃಕ್ಷ_TYPE (res) = build_array_type_nelts (unsigned_char_type_ಗಂಟು,
						  str.length ());
	ಪ್ರತ್ಯಾಗಮ res;
      }

  /* New format. */
  std::string str2;
  ಯಾವತ್ (ಸತ್ಯ)
    {
      ಯದಿ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
      str += (ವರ್ಣ) GOMP_INTEROP_IFR_SEPARATOR;
      str2.clear ();
      ತಾರ್ಕಿಕ has_fr = ಅಸತ್ಯ;
      ಯಾವತ್ (ಸತ್ಯ)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  ಯದಿ (tok->type != CPP_NAME
	      || (strcmp("fr", IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ)) != 0
		  && strcmp("attr", IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	    }
	  c_parser_consume_token (parser);
	  ತಾರ್ಕಿಕ is_fr = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ)[0] == 'f';
	  ಯದಿ (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	    }
	  ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	  ಯಾವತ್ (ಸತ್ಯ)
	    {
	      ಯದಿ (c_parser_next_token_is (parser, CPP_STRING))
		{
		  c_ಅಭಿವ್ಯಕ್ತಿ cval = c_parser_string_literal (parser, ಅಸತ್ಯ, ಅಸತ್ಯ);
		  ವೃಕ್ಷ ಮೌಲ್ಯ = cval.ಮೌಲ್ಯ;
		  ಯದಿ (ಮೌಲ್ಯ == error_mark_ಗಂಟು)
		    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		  ಯದಿ ((size_t) ವೃಕ್ಷ_STRING_LENGTH (ಮೌಲ್ಯ)
		      != strlen (ವೃಕ್ಷ_STRING_POINTER (ಮೌಲ್ಯ)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = ಸತ್ಯ;
		      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		    }
		  ಯದಿ (!is_fr)
		    {
		      ಯದಿ (!startswith (ವೃಕ್ಷ_STRING_POINTER (ಮೌಲ್ಯ), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = ಸತ್ಯ;
			  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
			}
		      ಯದಿ (strchr (ವೃಕ್ಷ_STRING_POINTER (ಮೌಲ್ಯ), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = ಸತ್ಯ;
			  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
			}
		      str2 += ವೃಕ್ಷ_STRING_POINTER (ಮೌಲ್ಯ);
		      str2 += '\0';
		    }
		  ಅನ್ಯಥಾ
		    {
		      ಯದಿ (*ವೃಕ್ಷ_STRING_POINTER (ಮೌಲ್ಯ) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
			}
		      ವರ್ಣ c = omp_get_fr_id_from_name (ವೃಕ್ಷ_STRING_POINTER (ಮೌಲ್ಯ));
		      ಯದಿ (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    ವೃಕ್ಷ_STRING_POINTER (ಮೌಲ್ಯ));
		     str += c;
		     has_fr = ಸತ್ಯ;
		    }
		}
	      ಅನ್ಯಥಾ ಯದಿ (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		}
	      ಅನ್ಯಥಾ
		{
		  c_ಅಭಿವ್ಯಕ್ತಿ cval = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
		  ವೃಕ್ಷ ಮೌಲ್ಯ = c_fully_fold (cval.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
		  ಯದಿ (INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ))
		      && ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != INTEGER_CST)
		    ಮೌಲ್ಯ = convert_lvalue_to_rvalue (cval.get_start (), cval,
						      ಅಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;

		  ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != INTEGER_CST
		      || !ವೃಕ್ಷ_fits_shwi_p (ಮೌಲ್ಯ))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		    }
		  HOST_WIDE_INT n = ವೃಕ್ಷ_to_shwi (ಮೌಲ್ಯ);
		  ಯದಿ (n < 1 || n > GOMP_INTEROP_IFR_LAST)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (ವರ್ಣ) n;
		  has_fr = ಸತ್ಯ;
		}
	      ಯದಿ (!is_fr
		  && c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ಅನುವರ್ತ;
		}
	      ಯದಿ (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ಅನುವರ್ತ;
	    }
	  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    ಭಙ್ಗ;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      str += (ವರ್ಣ) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	ಭಙ್ಗ;
      ಯದಿ (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  c_parser_consume_token (parser);
  str += '\0';
  ವೃಕ್ಷ res = build_string (str.length (), str.data ());
  ವೃಕ್ಷ_TYPE (res) = build_array_type_nelts (unsigned_char_type_ಗಂಟು,
						  str.length ());
  ಪ್ರತ್ಯಾಗಮ res;
}

/* OpenMP 5.1
     modifiers of the 'init' clause, used by the 'init' and the
     'append_args' clauses.

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification)

  Returns 'false' if an error has been issued.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_omp_clause_init_modifiers (c_parser *parser, ತಾರ್ಕಿಕ *target,
				    ತಾರ್ಕಿಕ *targetsync, ವೃಕ್ಷ *prefer_type_ವೃಕ್ಷ)
{
  *target = ಅಸತ್ಯ;
  *targetsync = ಅಸತ್ಯ;
  *prefer_type_ವೃಕ್ಷ = NULL_ವೃಕ್ಷ;

  ಕುರು
    {
      c_token *tok = c_parser_peek_token (parser);
      ಯದಿ (tok->type != CPP_NAME)
	ಗಚ್ಛ fail;
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ);
      ಯದಿ (strcmp ("targetsync", p) == 0)
	{
	  ಯದಿ (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = ಸತ್ಯ;
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("target", p) == 0)
	{
	  ಯದಿ (*target)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *target = ಸತ್ಯ;
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp ("prefer_type", p) == 0)
	{
	  ಯದಿ (*prefer_type_ವೃಕ್ಷ != NULL_ವೃಕ್ಷ)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_ವೃಕ್ಷ = c_parser_omp_modifier_prefer_type (parser);
	  ಯದಿ (*prefer_type_ವೃಕ್ಷ == error_mark_ಗಂಟು)
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
      ಅನ್ಯಥಾ
	ಗಚ್ಛ fail;
      tok = c_parser_peek_token (parser);
      ಯದಿ (tok->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ಅನುವರ್ತ;
	}
      /* Unknown token - either done or an error; handle it in the caller.  */
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }
  ಯಾವತ್ (ಸತ್ಯ);

fail:
  c_parser_error (parser,
		  "expected %<prefer_type%>, %<target%>, or %<targetsync%>");
  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* OpenMP 5.1:
   init ( [init-modifier-list : ] variable-list )

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_init (c_parser *parser, ವೃಕ್ಷ list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ list;

  ತಾರ್ಕಿಕ target = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ targetsync = ಅಸತ್ಯ;
  ವೃಕ್ಷ prefer_type_ವೃಕ್ಷ = NULL_ವೃಕ್ಷ;

  ಯದಿ (!c_parser_omp_clause_init_modifiers (parser, &target, &targetsync,
					   &prefer_type_ವೃಕ್ಷ)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      ಯದಿ (prefer_type_ವೃಕ್ಷ != error_mark_ಗಂಟು)
	parens.skip_until_found_close (parser);
      ಪ್ರತ್ಯಾಗಮ list;
    }

  ಯದಿ (!target && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  ವೃಕ್ಷ nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					ಅಸತ್ಯ);
  parens.skip_until_found_close (parser);

  ಪ್ರತಿ (ವೃಕ್ಷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      ವೃಕ್ಷ_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      ಯದಿ (target)
	OMP_CLAUSE_INIT_TARGET (c) = 1;
      ಯದಿ (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      ಯದಿ (prefer_type_ವೃಕ್ಷ)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_ವೃಕ್ಷ;
    }
  ಪ್ರತ್ಯಾಗಮ nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_use (c_parser *parser, ವೃಕ್ಷ list)
{
  ಪ್ರತ್ಯಾಗಮ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_clause_interop (c_parser *parser, ವೃಕ್ಷ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  ವೃಕ್ಷ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  ಪ್ರತಿ (ವೃಕ್ಷ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      ವೃಕ್ಷ_USED (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  ಪ್ರತ್ಯಾಗಮ nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_mask mask,
			   ಧ್ರುವ ವರ್ಣ *where, ತಾರ್ಕಿಕ finish_p = ಸತ್ಯ,
			   ತಾರ್ಕಿಕ target_p = ಅಸತ್ಯ)
{
  ವೃಕ್ಷ clauses = ರಿಕ್ತ;
  ತಾರ್ಕಿಕ first = ಸತ್ಯ;

  ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      ಧ್ರುವ ವರ್ಣ *c_name;
      ವೃಕ್ಷ prev = clauses;

      ಯದಿ (!first && c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      ವಿಕಲ್ಪ (c_kind)
	{
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "attach";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copy";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyin";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyout";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "create";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "delete";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, ಸತ್ಯ);
	  c_name = "default";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "detach";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_data_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device_resident";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_GANG,
						c_name, clauses);
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "host";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, ಅಸತ್ಯ);
	  c_name = "if";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "link";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "no_create";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_ಅಂಕೆ_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_ಅಂಕೆ_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_ಅಂಕೆ_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_ಅಂಕೆ_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "present";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     ಅಸತ್ಯ, clauses);
	  c_name = "reduction";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_SELF:
	  ಯದಿ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  ಅನ್ಯಥಾ
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "self";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_SEQ,
						 clauses);
	  c_name = "seq";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_TILE:
	  clauses = c_parser_oacc_clause_tile (parser, clauses);
	  c_name = "tile";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_USE_DEVICE:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_VECTOR:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_VECTOR,
						c_name,	clauses);
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_VECTOR_LENGTH:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_VECTOR_LENGTH,
						     clauses);
	  c_name = "vector_length";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OACC_CLAUSE_WORKER:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_WORKER,
						c_name, clauses);
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  c_parser_error (parser, "expected an OpenACC clause");
	  ಗಚ್ಛ saw_error;
	}

      first = ಅಸತ್ಯ;

      ಯದಿ (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_to_pragma_eol (parser);

  ಯದಿ (finish_p)
    ಪ್ರತ್ಯಾಗಮ c_finish_omp_clauses (clauses, target_p ? C_ORT_ACC_TARGET
						   : C_ORT_ACC);

  ಪ್ರತ್ಯಾಗಮ clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_all_clauses (c_parser *parser, omp_clause_mask mask,
			  ಧ್ರುವ ವರ್ಣ *where, ತಾರ್ಕಿಕ finish_p = ಸತ್ಯ,
			  ಪೂರ್ಣಾಙ್ಕ nested = 0)
{
  ವೃಕ್ಷ clauses = ರಿಕ್ತ;
  ತಾರ್ಕಿಕ first = ಸತ್ಯ;

  ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      ಧ್ರುವ ವರ್ಣ *c_name;
      ವೃಕ್ಷ prev = clauses;

      ಯದಿ (nested && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	ಭಙ್ಗ;

      ಯದಿ (!first || nested != 2)
	{
	  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ಅನ್ಯಥಾ ಯದಿ (nested == 2)
	    error_at (c_parser_peek_token (parser)->location,
		      "clauses in %<simd%> trait should be separated "
		      "by %<,%>");
	}

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      ವಿಕಲ್ಪ (c_kind)
	{
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_BIND:
	  clauses = c_parser_omp_clause_bind (parser, clauses);
	  c_name = "bind";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, ಅಸತ್ಯ);
	  c_name = "default";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_DETACH:
	  clauses = c_parser_omp_clause_detach (parser, clauses);
	  c_name = "detach";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_FILTER:
	  clauses = c_parser_omp_clause_filter (parser, clauses);
	  c_name = "filter";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_FINAL:
	  clauses = c_parser_omp_clause_final (parser, clauses);
	  c_name = "final";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_GRAINSIZE:
	  clauses = c_parser_omp_clause_grainsize (parser, clauses);
	  c_name = "grainsize";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_HINT:
	  clauses = c_parser_omp_clause_hint (parser, clauses);
	  c_name = "hint";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_DEFAULTMAP:
	  clauses = c_parser_omp_clause_defaultmap (parser, clauses);
	  c_name = "defaultmap";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, ಸತ್ಯ);
	  c_name = "if";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_IN_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_IN_REDUCTION,
					     ಸತ್ಯ, clauses);
	  c_name = "in_reduction";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_INDIRECT:
	  clauses = c_parser_omp_clause_indirect (parser, clauses);
	  c_name = "indirect";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_MERGEABLE:
	  clauses = c_parser_omp_clause_mergeable (parser, clauses);
	  c_name = "mergeable";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_ಅಂಕೆ_TASKS:
	  clauses = c_parser_omp_clause_ಅಂಕೆ_tasks (parser, clauses);
	  c_name = "num_tasks";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_ಅಂಕೆ_THREADS:
	  clauses = c_parser_omp_clause_ಅಂಕೆ_threads (parser, clauses);
	  c_name = "num_threads";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_ORDER:
	  clauses = c_parser_omp_clause_order (parser, clauses);
	  c_name = "order";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_PRIORITY:
	  clauses = c_parser_omp_clause_priority (parser, clauses);
	  c_name = "priority";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     ಸತ್ಯ, clauses);
	  c_name = "reduction";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_SCHEDULE:
	  clauses = c_parser_omp_clause_schedule (parser, clauses);
	  c_name = "schedule";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     ಸತ್ಯ, clauses);
	  c_name = "task_reduction";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_UNTIED:
	  clauses = c_parser_omp_clause_untied (parser, clauses);
	  c_name = "untied";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_INBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_INBRANCH,
						clauses);
	  c_name = "inbranch";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_NONTEMPORAL:
	  clauses = c_parser_omp_clause_nontemporal (parser, clauses);
	  c_name = "nontemporal";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_NOTINBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_NOTINBRANCH,
						clauses);
	  c_name = "notinbranch";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_PARALLEL:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_PARALLEL,
					      clauses);
	  c_name = "parallel";
	  ಯದಿ (!first)
	    {
	     clause_not_first:
	      error_at (here, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = prev;
	    }
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  ಯದಿ (!first)
	    ಗಚ್ಛ clause_not_first;
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  ಯದಿ (!first)
	    ಗಚ್ಛ clause_not_first;
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  ಯದಿ (!first)
	    ಗಚ್ಛ clause_not_first;
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_LINK:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LINK, clauses);
	  c_name = "link";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_LOCAL:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LOCAL, clauses);
	  c_name = "local";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_TO:
	  ಯದಿ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (here);
	      richloc.add_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      ವೃಕ್ಷ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      ಪ್ರತಿ (ವೃಕ್ಷ c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_TO (c) = 1;
	      clauses = nl;
	    }
	  ಅನ್ಯಥಾ
	    clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_TO,
						   clauses);
	  c_name = "to";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_UNIFORM:
	  clauses = c_parser_omp_clause_uniform (parser, clauses);
	  c_name = "uniform";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_ಅಂಕೆ_TEAMS:
	  clauses = c_parser_omp_clause_ಅಂಕೆ_teams (parser, clauses);
	  c_name = "num_teams";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_THREAD_LIMIT:
	  clauses = c_parser_omp_clause_thread_limit (parser, clauses);
	  c_name = "thread_limit";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_ALIGNED:
	  clauses = c_parser_omp_clause_aligned (parser, clauses);
	  c_name = "aligned";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_ALLOCATE:
	  clauses = c_parser_omp_clause_allocate (parser, clauses);
	  c_name = "allocate";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_LINEAR:
	  clauses = c_parser_omp_clause_linear (parser, clauses);
	  c_name = "linear";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_USES_ALLOCATORS:
	  clauses = c_parser_omp_clause_uses_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, here);
	  c_name = "depend";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_DOACROSS:
	  clauses = c_parser_omp_clause_doacross (parser, clauses);
	  c_name = "doacross";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_DESTROY:
	  clauses = c_parser_omp_clause_destroy (parser, clauses);
	  c_name = "destroy";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE:
	  clauses = c_parser_omp_clause_dyn_groupprivate (parser, clauses);
	  c_name = "dyn_groupprivate";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_INIT:
	  clauses = c_parser_omp_clause_init (parser, clauses);
	  c_name = "init";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_USE:
	  clauses = c_parser_omp_clause_use (parser, clauses);
	  c_name = "use";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_INTEROP:
	  clauses = c_parser_omp_clause_interop (parser, clauses);
	  c_name = "interop";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_MAP:
	  clauses = c_parser_omp_clause_map (parser, clauses, ಅಸತ್ಯ);
	  c_name = "map";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device_ptr";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_use_device_addr (parser, clauses);
	  c_name = "use_device_addr";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_has_device_addr (parser, clauses);
	  c_name = "has_device_addr";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR:
	  clauses = c_parser_omp_clause_is_device_ptr (parser, clauses);
	  c_name = "is_device_ptr";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_DEVICE:
	  clauses = c_parser_omp_clause_device (parser, clauses);
	  c_name = "device";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_DIST_SCHEDULE:
	  clauses = c_parser_omp_clause_dist_schedule (parser, clauses);
	  c_name = "dist_schedule";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_PROC_BIND:
	  clauses = c_parser_omp_clause_proc_bind (parser, clauses);
	  c_name = "proc_bind";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_DEVICE_TYPE:
	  clauses = c_parser_omp_clause_device_type (parser, clauses);
	  c_name = "device_type";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_SAFELEN:
	  clauses = c_parser_omp_clause_safelen (parser, clauses);
	  c_name = "safelen";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_SIMDLEN:
	  clauses = c_parser_omp_clause_simdlen (parser, clauses);
	  c_name = "simdlen";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_NOGROUP:
	  clauses = c_parser_omp_clause_nogroup (parser, clauses);
	  c_name = "nogroup";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_THREADS:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_THREADS,
					       clauses);
	  c_name = "threads";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_SIMD:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_SIMD,
					       clauses);
	  c_name = "simd";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_ENTER:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					    clauses);
	  c_name = "enter";
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_FULL:
	  c_name = "full";
	  clauses = c_parser_omp_clause_full (parser, clauses);
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_PARTIAL:
	  c_name = "partial";
	  clauses = c_parser_omp_clause_partial (parser, clauses);
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_NOVARIANTS:
	  c_name = "novariants";
	  clauses = c_parser_omp_clause_novariants (parser, clauses);
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_CLAUSE_NOCONTEXT:
	  c_name = "nocontext";
	  clauses = c_parser_omp_clause_nocontext (parser, clauses);
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  c_parser_error (parser, "expected an OpenMP clause");
	  ಗಚ್ಛ saw_error;
	}

      first = ಅಸತ್ಯ;

      ಯದಿ (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  ಯದಿ (!nested)
    c_parser_skip_to_pragma_eol (parser);

  ಯದಿ (finish_p)
    {
      ಯದಿ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_UNIFORM)) != 0)
	ಪ್ರತ್ಯಾಗಮ c_finish_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      ಯದಿ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	ಪ್ರತ್ಯಾಗಮ c_finish_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      ಪ್ರತ್ಯಾಗಮ c_finish_omp_clauses (clauses, C_ORT_OMP);
    }

  ಪ್ರತ್ಯಾಗಮ clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_structured_block (c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ stmt = ತಳ್ಳು_stmt_list ();
  parser->omp_attrs_forbidden_p = ಸತ್ಯ;
  c_parser_statement (parser, if_p);
  ಪ್ರತ್ಯಾಗಮ ತೆಗೆ_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  ವೃಕ್ಷ stmt, clauses = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ readonly = ಅಸತ್ಯ;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      ಯದಿ (token->type == CPP_NAME
	  && !strcmp (IDENTIFIER_POINTER (token->ಮೌಲ್ಯ), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = ಸತ್ಯ;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_ವೃಕ್ಷ);
      parens.skip_until_found_close (parser);
    }

  ಯದಿ (readonly)
    ಪ್ರತಿ (ವೃಕ್ಷ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_to_pragma_eol (parser);

  stmt = make_ಗಂಟು (OACC_CACHE);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
  add_stmt (stmt);

  ಪ್ರತ್ಯಾಗಮ stmt;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_data (location_t loc, c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_DATA_CLAUSE_MASK,
				       "#pragma acc data");

  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  stmt = c_finish_oacc_data (loc, clauses, block);

  ಪ್ರತ್ಯಾಗಮ stmt;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_oacc_declare (c_parser *parser)
{
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ clauses, stmt, t, decl;

  ತಾರ್ಕಿಕ error = ಅಸತ್ಯ;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_MASK,
				       "#pragma acc declare");
  ಯದಿ (!clauses)
    {
      error_at (pragma_loc,
		"no valid clauses specified in %<#pragma acc declare%>");
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಪ್ರತಿ (t = clauses; t; t = OMP_CLAUSE_CHAIN (t))
    {
      location_t loc = OMP_CLAUSE_LOCATION (t);
      decl = OMP_CLAUSE_DECL (t);
      ಯದಿ (!DECL_P (decl))
	{
	  error_at (loc, "array section in %<#pragma acc declare%>");
	  error = ಸತ್ಯ;
	  ಅನುವರ್ತ;
	}

      ವಿಕಲ್ಪ (OMP_CLAUSE_MAP_KIND (t))
	{
	ಪಕ್ಷ GOMP_MAP_FIRSTPRIVATE_POINTER:
	ಪಕ್ಷ GOMP_MAP_ALLOC:
	ಪಕ್ಷ GOMP_MAP_TO:
	ಪಕ್ಷ GOMP_MAP_FORCE_DEVICEPTR:
	ಪಕ್ಷ GOMP_MAP_DEVICE_RESIDENT:
	  ಭಙ್ಗ;

	ಪಕ್ಷ GOMP_MAP_LINK:
	  ಯದಿ (!global_bindings_p ()
	      && (ವೃಕ್ಷ_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = ಸತ್ಯ;
	      ಅನುವರ್ತ;
	    }
	  ಭಙ್ಗ;

	ಸ್ವಭಾವ:
	  ಯದಿ (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = ಸತ್ಯ;
	      ಅನುವರ್ತ;
	    }
	  ಯದಿ (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = ಸತ್ಯ;
	      ಅನುವರ್ತ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_PUBLIC (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = ಸತ್ಯ;
	      ಅನುವರ್ತ;
	    }
	  ಭಙ್ಗ;
	}

      ಯದಿ (!c_check_in_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = ಸತ್ಯ;
	  ಅನುವರ್ತ;
	}

      ಯದಿ (lookup_attribute ("omp declare target", DECL_ATTRIBUTES (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_ATTRIBUTES (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = ಸತ್ಯ;
	  ಅನುವರ್ತ;
	}

      ಯದಿ (!error)
	{
	  ವೃಕ್ಷ id;

	  ಯದಿ (OMP_CLAUSE_MAP_KIND (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  ಅನ್ಯಥಾ
	    id = get_identifier ("omp declare target");

	  DECL_ATTRIBUTES (decl)
			   = ವೃಕ್ಷ_cons (id, NULL_ವೃಕ್ಷ, DECL_ATTRIBUTES (decl));

	  ಯದಿ (global_bindings_p ())
	    {
	      symtab_ಗಂಟು *ಗಂಟು = symtab_ಗಂಟು::get (decl);
	      ಯದಿ (ಗಂಟು != ರಿಕ್ತ)
		{
		  ಗಂಟು->offloadable = 1;
		  ಯದಿ (ENABLE_OFFLOADING)
		    {
		      g->have_offload = ಸತ್ಯ;
		      ಯದಿ (is_a <varpool_ಗಂಟು *> (ಗಂಟು))
			vec_safe_ತಳ್ಳು (offload_vars, decl);
		    }
		}
	    }
	}
    }

  ಯದಿ (error || global_bindings_p ())
    ಪ್ರತ್ಯಾಗಮ;

  stmt = make_ಗಂಟು (OACC_DECLARE);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, pragma_loc);

  add_stmt (stmt);

  ಪ್ರತ್ಯಾಗಮ;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_oacc_enter_exit_data (c_parser *parser, ತಾರ್ಕಿಕ enter)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ clauses, stmt;
  ಧ್ರುವ ವರ್ಣ *p = "";

  c_parser_consume_pragma (parser);

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      c_parser_consume_token (parser);
    }

  ಯದಿ (strcmp (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = ಸತ್ಯ;
      c_parser_skip_to_pragma_eol (parser);
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_DATA_CLAUSE_MASK,
					 "#pragma acc enter data");
  ಅನ್ಯಥಾ
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_DATA_CLAUSE_MASK,
					 "#pragma acc exit data");

  ಯದಿ (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_ವೃಕ್ಷ)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      ಪ್ರತ್ಯಾಗಮ;
    }

  stmt = enter ? make_ಗಂಟು (OACC_ENTER_DATA) : make_ಗಂಟು (OACC_EXIT_DATA);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_host_data (location_t loc, c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_DATA_CLAUSE_MASK,
				       "#pragma acc host_data", ಅಸತ್ಯ);
  ಯದಿ (!omp_find_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  stmt = c_finish_oacc_host_data (loc, clauses, block);
  ಪ್ರತ್ಯಾಗಮ stmt;
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
ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_loop (location_t loc, c_parser *parser, ವರ್ಣ *p_name,
		    omp_clause_mask mask, ವೃಕ್ಷ *cclauses, ತಾರ್ಕಿಕ *if_p)
{
  ತಾರ್ಕಿಕ is_parallel = ((mask >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  strcat (p_name, " loop");
  mask |= OACC_LOOP_CLAUSE_MASK;

  ವೃಕ್ಷ clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/cclauses == ರಿಕ್ತ,
					    /*target=*/is_parallel);
  ಯದಿ (cclauses)
    {
      clauses = c_oacc_split_loop_clauses (clauses, cclauses, is_parallel);
      ಯದಿ (*cclauses)
	*cclauses = c_finish_omp_clauses (*cclauses, C_ORT_ACC_TARGET);
      ಯದಿ (clauses)
	clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
    }

  ವೃಕ್ಷ block = c_begin_compound_stmt (ಸತ್ಯ);
  ವೃಕ್ಷ stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, ರಿಕ್ತ,
				     if_p);
  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
  add_stmt (block);

  ಪ್ರತ್ಯಾಗಮ stmt;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ಅಂಕೆ_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ಅಂಕೆ_WORKERS)		\
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ಅಂಕೆ_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ಅಂಕೆ_WORKERS)		\
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       ಗಣನಾ pragma_kind p_kind, ವರ್ಣ *p_name, ತಾರ್ಕಿಕ *if_p)
{
  omp_clause_mask mask;
  ಗಣನಾ ವೃಕ್ಷ_code code;
  ವಿಕಲ್ಪ (p_kind)
    {
    ಪಕ್ಷ PRAGMA_OACC_KERNELS:
      strcat (p_name, " kernels");
      mask = OACC_KERNELS_CLAUSE_MASK;
      code = OACC_KERNELS;
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_PARALLEL:
      strcat (p_name, " parallel");
      mask = OACC_PARALLEL_CLAUSE_MASK;
      code = OACC_PARALLEL;
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_SERIAL:
      strcat (p_name, " serial");
      mask = OACC_SERIAL_CLAUSE_MASK;
      code = OACC_SERIAL;
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  ವೃಕ್ಷ block = c_begin_omp_parallel ();
	  ವೃಕ್ಷ clauses;
	  c_parser_oacc_loop (loc, parser, p_name, mask, &clauses, if_p);
	  ಪ್ರತ್ಯಾಗಮ c_finish_omp_construct (loc, code, block, clauses);
	}
    }

  ವೃಕ್ಷ clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/ಸತ್ಯ,
					    /*target=*/ಸತ್ಯ);

  ವೃಕ್ಷ block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  ಪ್ರತ್ಯಾಗಮ c_finish_omp_construct (loc, code, block, clauses);
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_oacc_routine (c_parser *parser, ಗಣನಾ pragma_context context)
{
  gcc_checking_assert (context == pragma_external);

  oacc_routine_data data;
  data.error_seen = ಅಸತ್ಯ;
  data.fndecl_seen = ಅಸತ್ಯ;
  data.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      ವೃಕ್ಷ decl = NULL_ವೃಕ್ಷ;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      ಯದಿ (name_token->type == CPP_NAME
	  && (name_token->id_kind == C_ID_ID
	      || name_token->id_kind == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->ಮೌಲ್ಯ);
	  ಯದಿ (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->ಮೌಲ್ಯ);
	  c_parser_consume_token (parser);
	}
      ಅನ್ಯಥಾ
	c_parser_error (parser, "expected function name");

      ಯದಿ (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	  ಪ್ರತ್ಯಾಗಮ;
	}

      data.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_MASK,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      data.clauses = nreverse (data.clauses);

      ಯದಿ (ವೃಕ್ಷ_CODE (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  ಪ್ರತ್ಯಾಗಮ;
	}

      c_finish_oacc_routine (&data, decl, ಅಸತ್ಯ);
    }
  ಅನ್ಯಥಾ /* No optional '( name )'.  */
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
      ಯದಿ (c_parser_next_token_is (parser, CPP_PRAGMA)
	  || c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (data.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  ಪ್ರತ್ಯಾಗಮ;
	}

      /* We only have to consider the pragma_external case here.  */
      ಯದಿ (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  ಪೂರ್ಣಾಙ್ಕ ext = disable_extension_diagnostics ();
	  ಕುರು
	    c_parser_consume_token (parser);
	  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಅಸತ್ಯ, ಸತ್ಯ,
					 ಅಸತ್ಯ, ರಿಕ್ತ, ರಿಕ್ತ, ಅಸತ್ಯ, ರಿಕ್ತ, &data);
	  restore_extension_diagnostics (ext);
	}
      ಅನ್ಯಥಾ
	c_parser_declaration_or_fndef (parser, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಅಸತ್ಯ, ಸತ್ಯ,
				       ಅಸತ್ಯ, ರಿಕ್ತ, ರಿಕ್ತ, ಅಸತ್ಯ, ರಿಕ್ತ, &data);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_finish_oacc_routine (ಸಂರಚನಾ oacc_routine_data *data, ವೃಕ್ಷ fndecl,
		       ತಾರ್ಕಿಕ is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  ಯದಿ (data->error_seen
      || fndecl == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ;

  ಯದಿ (data->fndecl_seen)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      data->error_seen = ಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (fndecl == NULL_ವೃಕ್ಷ || ವೃಕ್ಷ_CODE (fndecl) != FUNCTION_DECL)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      data->error_seen = ಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಪೂರ್ಣಾಙ್ಕ compatible
    = oacc_verify_routine_clauses (fndecl, &data->clauses, data->loc,
				   "#pragma acc routine");
  ಯದಿ (compatible < 0)
    {
      data->error_seen = ಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (compatible > 0)
    {
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (ವೃಕ್ಷ_USED (fndecl) || (!is_defn && DECL_SAVED_ವೃಕ್ಷ (fndecl)))
	{
	  error_at (data->loc,
		    ವೃಕ್ಷ_USED (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  data->error_seen = ಸತ್ಯ;
	  ಪ್ರತ್ಯಾಗಮ;
	}

      /* Set the routine's level of parallelism.  */
      ವೃಕ್ಷ dims = oacc_build_routine_dims (data->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_ATTRIBUTES (fndecl)
	= ವೃಕ್ಷ_cons (get_identifier ("omp declare target"),
		     data->clauses, DECL_ATTRIBUTES (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  data->fndecl_seen = ಸತ್ಯ;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_oacc_update (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  ವೃಕ್ಷ clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_MASK,
					    "#pragma acc update");
  ಯದಿ (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_ವೃಕ್ಷ)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (parser->error)
    ಪ್ರತ್ಯಾಗಮ;

  ವೃಕ್ಷ stmt = make_ಗಂಟು (OACC_UPDATE);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#define OACC_WAIT_CLAUSE_MASK						\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF) )

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_oacc_wait (location_t loc, c_parser *parser, ವರ್ಣ *p_name)
{
  ವೃಕ್ಷ clauses, list = NULL_ವೃಕ್ಷ, stmt = NULL_ವೃಕ್ಷ;

  ಯದಿ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  strcpy (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_MASK, p_name);
  stmt = c_finish_oacc_wait (loc, list, clauses);
  add_stmt (stmt);

  ಪ್ರತ್ಯಾಗಮ stmt;
}

ಸಂರಚನಾ c_omp_loc_ವೃಕ್ಷ
{
  location_t loc;
  ವೃಕ್ಷ var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
ಸ್ಥಿರ ವೃಕ್ಷ
c_check_omp_allocate_allocator_r (ವೃಕ್ಷ *tp, ಪೂರ್ಣಾಙ್ಕ *, ಶೂನ್ಯ *data)
{
  ವೃಕ್ಷ var = ((ಸಂರಚನಾ c_omp_loc_ವೃಕ್ಷ *) data)->var;
  location_t loc = ((ಸಂರಚನಾ c_omp_loc_ವೃಕ್ಷ *) data)->loc;
  ಯದಿ (ವೃಕ್ಷ_CODE (*tp) == VAR_DECL && c_check_in_current_scope (*tp))
    {
      ಯದಿ (linemap_location_before_p (ಸಾಲು_table, DECL_SOURCE_LOCATION (var),
				     DECL_SOURCE_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_SOURCE_LOCATION (*tp), "declared here");
	  inform (DECL_SOURCE_LOCATION (var),
		  "to be allocated variable declared here");
	  ಪ್ರತ್ಯಾಗಮ *tp;
	}
      ಅನ್ಯಥಾ
	{
	  gcc_assert (cur_stmt_list
		      && ವೃಕ್ಷ_CODE (cur_stmt_list) == STATEMENT_LIST);

	  ವೃಕ್ಷ_stmt_iterator l = tsi_last (cur_stmt_list);
	  ಯಾವತ್ (!tsi_end_p (l))
	    {
	      ಯದಿ (linemap_location_before_p (ಸಾಲು_table, ಅಭಿವ್ಯಕ್ತಿ_LOCATION (*l),
					     DECL_SOURCE_LOCATION (var)))
		  ಭಙ್ಗ;
	      ಯದಿ (ವೃಕ್ಷ_CODE (*l) == MODIFY_ಅಭಿವ್ಯಕ್ತಿ
		  && ವೃಕ್ಷ_OPERAND (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (*l), "modified here");
		  inform (DECL_SOURCE_LOCATION (var),
			  "to be allocated variable declared here");
		  ಪ್ರತ್ಯಾಗಮ *tp;
		}
	      --l;
	    }
	}
    }
  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
}

/* OpenMP 5.x:
   # pragma omp allocate (list)  clauses

   OpenMP 5.0 clause:
   allocator (omp_allocator_handle_t expression)

   OpenMP 5.1 additional clause:
   align (constant-expression)]  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_allocate (c_parser *parser)
{
  ವೃಕ್ಷ alignment = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ allocator = NULL_ವೃಕ್ಷ;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  ವೃಕ್ಷ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_ವೃಕ್ಷ);
  ಕುರು
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME))
	ಭಙ್ಗ;
      matching_parens parens;
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      c_parser_consume_token (parser);
      location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      ಯದಿ (strcmp ("align", p) != 0 && strcmp ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  ಭಙ್ಗ;
	}
      ಯದಿ (!parens.require_open (parser))
	ಭಙ್ಗ;

      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ಸತ್ಯ);
      ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
      ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	;
      ಅನ್ಯಥಾ ಯದಿ (p[2] == 'i' && alignment)
	{
	  error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, "too many %qs clauses", "align");
	  ಭಙ್ಗ;
	}
      ಅನ್ಯಥಾ ಯದಿ (p[2] == 'i')
	{
	  alignment = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
	  ಯದಿ (ವೃಕ್ಷ_CODE (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (alignment))
	      || ವೃಕ್ಷ_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_ವೃಕ್ಷ;
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (allocator)
	{
	  error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, "too many %qs clauses", "allocator");
	  ಭಙ್ಗ;
	}
      ಅನ್ಯಥಾ
	{
	  allocator = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
	  allocator_loc = ಅಭಿವ್ಯಕ್ತಿ_loc;
	  ವೃಕ್ಷ orig_type
	    = ಅಭಿವ್ಯಕ್ತಿ.original_type ? ಅಭಿವ್ಯಕ್ತಿ.original_type : ವೃಕ್ಷ_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (allocator))
	      || ವೃಕ್ಷ_CODE (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (ಅಭಿವ್ಯಕ್ತಿ_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			ವೃಕ್ಷ_TYPE (allocator));
	      allocator = NULL_ವೃಕ್ಷ;
	    }
	}
      parens.skip_until_found_close (parser);
    } ಯಾವತ್ (ಸತ್ಯ);
  c_parser_skip_to_pragma_eol (parser);

  c_mark_decl_jump_unsafe_in_current_scope ();
  ಪ್ರತಿ (ವೃಕ್ಷ c = nl; c != NULL_ವೃಕ್ಷ; c = OMP_CLAUSE_CHAIN (c))
    {
      ವೃಕ್ಷ var = OMP_CLAUSE_DECL (c);
      ಯದಿ (ವೃಕ್ಷ_CODE (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  ಅನುವರ್ತ;
	}
      ಯದಿ (!parser->in_omp_decl_attribute && !c_check_in_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_SOURCE_LOCATION (var), "declared here");
	  ಅನುವರ್ತ;
	}
      ಯದಿ (lookup_attribute ("omp allocate", DECL_ATTRIBUTES (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  ಅನುವರ್ತ;
	}
      ಯದಿ (ವೃಕ್ಷ_STATIC (var))
	{
	  ಯದಿ (allocator == NULL_ವೃಕ್ಷ && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      ಅನುವರ್ತ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (allocator
		   && (wi::to_widest (allocator) < 1
		       || wi::to_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::to_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::to_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  ಅನ್ಯಥಾ ಯದಿ (allocator
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
      ಯದಿ (allocator)
	{
	  ಸಂರಚನಾ c_omp_loc_ವೃಕ್ಷ data
	    = {ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_ವೃಕ್ಷ (&allocator, c_check_omp_allocate_allocator_r, &data, ರಿಕ್ತ);
	}
      DECL_ATTRIBUTES (var) = ವೃಕ್ಷ_cons (get_identifier ("omp allocate"),
					 build_ವೃಕ್ಷ_list (allocator, alignment),
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_atomic (location_t loc, c_parser *parser, ತಾರ್ಕಿಕ openacc)
{
  ವೃಕ್ಷ lhs = NULL_ವೃಕ್ಷ, rhs = NULL_ವೃಕ್ಷ, v = NULL_ವೃಕ್ಷ, r = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ lhs1 = NULL_ವೃಕ್ಷ, rhs1 = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ stmt, orig_lhs, unfolded_lhs = NULL_ವೃಕ್ಷ, unfolded_lhs1 = NULL_ವೃಕ್ಷ;
  ಗಣನಾ ವೃಕ್ಷ_code code = ERROR_MARK, opcode = NOP_ಅಭಿವ್ಯಕ್ತಿ;
  ಗಣನಾ omp_memory_order memory_order = OMP_MEMORY_ORDER_UNSPECIFIED;
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  location_t eloc;
  ತಾರ್ಕಿಕ structured_block = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ swapped = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ non_lvalue_p;
  ವೃಕ್ಷ clauses = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ capture = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ compare = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ weak = ಅಸತ್ಯ;
  ಗಣನಾ omp_memory_order fail = OMP_MEMORY_ORDER_UNSPECIFIED;
  ತಾರ್ಕಿಕ no_semicolon = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ extra_scope = ಅಸತ್ಯ;

  ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ಧ್ರುವ ವರ್ಣ *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  ಗಣನಾ ವೃಕ್ಷ_code new_code = ERROR_MARK;
	  ಗಣನಾ omp_memory_order new_memory_order
	    = OMP_MEMORY_ORDER_UNSPECIFIED;
	  ತಾರ್ಕಿಕ new_capture = ಅಸತ್ಯ;
	  ತಾರ್ಕಿಕ new_compare = ಅಸತ್ಯ;
	  ತಾರ್ಕಿಕ new_weak = ಅಸತ್ಯ;
	  ಗಣನಾ omp_memory_order new_fail = OMP_MEMORY_ORDER_UNSPECIFIED;

	  ಯದಿ (!strcmp (p, "read"))
	    new_code = OMP_ATOMIC_READ;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "write"))
	    new_code = NOP_ಅಭಿವ್ಯಕ್ತಿ;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "update"))
	    new_code = OMP_ATOMIC;
	  ಅನ್ಯಥಾ ಯದಿ (openacc && !strcmp (p, "capture"))
	    new_code = OMP_ATOMIC_CAPTURE_NEW;
	  ಅನ್ಯಥಾ ಯದಿ (openacc)
	    {
	      p = ರಿಕ್ತ;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "capture"))
	    new_capture = ಸತ್ಯ;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "compare"))
	    new_compare = ಸತ್ಯ;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "weak"))
	    new_weak = ಸತ್ಯ;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      ಯದಿ (!parens.require_open (parser))
		ಅನುವರ್ತ;

	      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
		{
		  ಧ್ರುವ ವರ್ಣ *q
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);

		  ಯದಿ (!strcmp (q, "seq_cst"))
		    new_fail = OMP_MEMORY_ORDER_SEQ_CST;
		  ಅನ್ಯಥಾ ಯದಿ (!strcmp (q, "acquire"))
		    new_fail = OMP_MEMORY_ORDER_ACQUIRE;
		  ಅನ್ಯಥಾ ಯದಿ (!strcmp (q, "relaxed"))
		    new_fail = OMP_MEMORY_ORDER_RELAXED;
		}

	      ಯದಿ (new_fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  ಯದಿ (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  ಅನ್ಯಥಾ
		    fail = new_fail;
		}
	      ಅನ್ಯಥಾ
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_found_close (parser);
	      ಅನುವರ್ತ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "seq_cst"))
	    new_memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "acq_rel"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "release"))
	    new_memory_order = OMP_MEMORY_ORDER_RELEASE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "acquire"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "relaxed"))
	    new_memory_order = OMP_MEMORY_ORDER_RELAXED;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "hint"))
	    {
	      c_parser_consume_token (parser);
	      clauses = c_parser_omp_clause_hint (parser, clauses);
	      ಅನುವರ್ತ;
	    }
	  ಅನ್ಯಥಾ
	    {
	      p = ರಿಕ್ತ;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "%<capture%>, %<compare%>, %<weak%>, %<fail%>, "
			      "%<seq_cst%>, %<acq_rel%>, %<release%>, "
			      "%<relaxed%> or %<hint%> clause");
	    }
	  ಯದಿ (p)
	    {
	      ಯದಿ (new_code != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  ಯದಿ (openacc
		      && code == OMP_ATOMIC
		      && new_code == OMP_ATOMIC_CAPTURE_NEW)
		    code = new_code;
		  ಅನ್ಯಥಾ ಯದಿ (code != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  ಅನ್ಯಥಾ
		    code = new_code;
		}
	      ಅನ್ಯಥಾ ಯದಿ (new_memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  ಯದಿ (memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  ಅನ್ಯಥಾ
		    memory_order = new_memory_order;
		}
	      ಅನ್ಯಥಾ ಯದಿ (new_capture)
		{
		  ಯದಿ (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  ಅನ್ಯಥಾ
		    capture = ಸತ್ಯ;
		}
	      ಅನ್ಯಥಾ ಯದಿ (new_compare)
		{
		  ಯದಿ (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  ಅನ್ಯಥಾ
		    compare = ಸತ್ಯ;
		}
	      ಅನ್ಯಥಾ ಯದಿ (new_weak)
		{
		  ಯದಿ (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  ಅನ್ಯಥಾ
		    weak = ಸತ್ಯ;
		}
	      c_parser_consume_token (parser);
	      ಅನುವರ್ತ;
	    }
	}
      ಭಙ್ಗ;
    }
  c_parser_skip_to_pragma_eol (parser);

  ಯದಿ (code == ERROR_MARK)
    code = OMP_ATOMIC;
  ಯದಿ (capture)
    {
      ಯದಿ (code != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      ಅನ್ಯಥಾ
	code = OMP_ATOMIC_CAPTURE_NEW;
    }
  ಯದಿ (compare && code != OMP_ATOMIC && code != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = ಅಸತ್ಯ;
    }
  ಯದಿ (fail != OMP_MEMORY_ORDER_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      fail = OMP_MEMORY_ORDER_UNSPECIFIED;
    }
  ಯದಿ (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = ಅಸತ್ಯ;
    }
  ಯದಿ (openacc)
    memory_order = OMP_MEMORY_ORDER_RELAXED;
  ಅನ್ಯಥಾ ಯದಿ (memory_order == OMP_MEMORY_ORDER_UNSPECIFIED)
    {
      omp_requires_mask
	= (ಗಣನಾ omp_requires) (omp_requires_mask
			       | OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED);
      ವಿಕಲ್ಪ ((ಗಣನಾ omp_memory_order)
	      (omp_requires_mask & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER))
	{
	ಪಕ್ಷ OMP_MEMORY_ORDER_UNSPECIFIED:
	ಪಕ್ಷ OMP_MEMORY_ORDER_RELAXED:
	  memory_order = OMP_MEMORY_ORDER_RELAXED;
	  ಭಙ್ಗ;
	ಪಕ್ಷ OMP_MEMORY_ORDER_SEQ_CST:
	  memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  ಭಙ್ಗ;
	ಪಕ್ಷ OMP_MEMORY_ORDER_ACQUIRE:
	  ಯದಿ (code == NOP_ಅಭಿವ್ಯಕ್ತಿ)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  ಅನ್ಯಥಾ
	    memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  ಭಙ್ಗ;
	ಪಕ್ಷ OMP_MEMORY_ORDER_RELEASE:
	  ಯದಿ (code == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  ಅನ್ಯಥಾ
	    memory_order = OMP_MEMORY_ORDER_RELEASE;
	  ಭಙ್ಗ;
	ಪಕ್ಷ OMP_MEMORY_ORDER_ACQ_REL:
	  ವಿಕಲ್ಪ (code)
	    {
	    ಪಕ್ಷ OMP_ATOMIC_READ:
	      memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	      ಭಙ್ಗ;
	    ಪಕ್ಷ NOP_ಅಭಿವ್ಯಕ್ತಿ: /* atomic write */
	      memory_order = OMP_MEMORY_ORDER_RELEASE;
	      ಭಙ್ಗ;
	    ಸ್ವಭಾವ:
	      memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	      ಭಙ್ಗ;
	    }
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  gcc_unreachable ();
	}
    }
  ಅನ್ಯಥಾ
    ವಿಕಲ್ಪ (code)
      {
      ಪಕ್ಷ OMP_ATOMIC_READ:
	ಯದಿ (memory_order == OMP_MEMORY_ORDER_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	ಅನ್ಯಥಾ ಯದಿ (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	ಭಙ್ಗ;
      ಪಕ್ಷ NOP_ಅಭಿವ್ಯಕ್ತಿ: /* atomic write */
	ಯದಿ (memory_order == OMP_MEMORY_ORDER_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	ಅನ್ಯಥಾ ಯದಿ (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_RELEASE;
	ಭಙ್ಗ;
      ಸ್ವಭಾವ:
	ಭಙ್ಗ;
      }
  ಯದಿ (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
    memory_order
      = (ಗಣನಾ omp_memory_order) (memory_order
				 | (fail << OMP_FAIL_MEMORY_ORDER_SHIFT));

  ವಿಕಲ್ಪ (code)
    {
    ಪಕ್ಷ OMP_ATOMIC_READ:
    ಪಕ್ಷ NOP_ಅಭಿವ್ಯಕ್ತಿ: /* atomic write */
      v = c_parser_cast_expression (parser, ರಿಕ್ತ).ಮೌಲ್ಯ;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
      ಯದಿ (v == error_mark_ಗಂಟು)
	ಗಚ್ಛ saw_error;
      ಯದಿ (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      ಯದಿ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	ಗಚ್ಛ saw_error;
      ಯದಿ (code == NOP_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  ಅಭಿವ್ಯಕ್ತಿ = c_parser_expression (parser);
	  ಅಭಿವ್ಯಕ್ತಿ = default_function_array_read_conversion (eloc, ಅಭಿವ್ಯಕ್ತಿ);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  code = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_ವೃಕ್ಷ;
	  rhs = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
	  ಯದಿ (rhs == error_mark_ಗಂಟು)
	    ಗಚ್ಛ saw_error;
	}
      ಅನ್ಯಥಾ
	{
	  lhs = c_parser_cast_expression (parser, ರಿಕ್ತ).ಮೌಲ್ಯ;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
	  ಯದಿ (lhs == error_mark_ಗಂಟು)
	    ಗಚ್ಛ saw_error;
	  ಯದಿ (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      ಗಚ್ಛ done;
    ಪಕ್ಷ OMP_ATOMIC_CAPTURE_NEW:
      ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_block = ಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (compare
	       && c_parser_next_token_is_keyword (parser, RID_IF))
	ಭಙ್ಗ;
      ಅನ್ಯಥಾ
	{
	  v = c_parser_cast_expression (parser, ರಿಕ್ತ).ಮೌಲ್ಯ;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
	  ಯದಿ (v == error_mark_ಗಂಟು)
	    ಗಚ್ಛ saw_error;
	  ಯದಿ (non_lvalue_p)
	    v = non_lvalue (v);
	  ಯದಿ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    ಗಚ್ಛ saw_error;
	  ಯದಿ (compare && c_parser_next_token_is_keyword (parser, RID_IF))
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "expected expression");
	      ಗಚ್ಛ saw_error;
	    }
	}
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      ಭಙ್ಗ;
    }

  /* For structured_block case we don't know yet whether
     old or new x should be captured.  */
restart:
  ಯದಿ (compare && c_parser_next_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      ಯದಿ (!parens.require_open (parser))
	ಗಚ್ಛ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ cmp_ಅಭಿವ್ಯಕ್ತಿ;
      ಯದಿ (r)
	{
	  cmp_ಅಭಿವ್ಯಕ್ತಿ = c_parser_cast_expression (parser, ರಿಕ್ತ);
	  cmp_ಅಭಿವ್ಯಕ್ತಿ = default_function_array_conversion (eloc, cmp_ಅಭಿವ್ಯಕ್ತಿ);
	}
      ಅನ್ಯಥಾ
	cmp_ಅಭಿವ್ಯಕ್ತಿ = c_parser_ದ್ವಿಮಾನ_expression (parser, ರಿಕ್ತ, void_list_ಗಂಟು);
      parens.skip_until_found_close (parser);
      ಯದಿ (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	ಗಚ್ಛ saw_error;
      ಯದಿ (r)
	{
	  ಯದಿ (!c_ವೃಕ್ಷ_equal (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, unfolded_lhs))
	    ಗಚ್ಛ bad_if;
	  cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = rhs1;
	  rhs1 = NULL_ವೃಕ್ಷ;
	  gcc_assert (ವೃಕ್ಷ_CODE (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == EQ_ಅಭಿವ್ಯಕ್ತಿ);
	}
      ಯದಿ (ವೃಕ್ಷ_CODE (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == EQ_ಅಭಿವ್ಯಕ್ತಿ)
	;
      ಅನ್ಯಥಾ ಯದಿ (!structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  ಗಚ್ಛ saw_error;
	}
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) != GT_ಅಭಿವ್ಯಕ್ತಿ
	       && ವೃಕ್ಷ_CODE (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) != LT_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  ಗಚ್ಛ saw_error;
	}
      ಯದಿ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	ಗಚ್ಛ saw_error;

      extra_scope = ಸತ್ಯ;
      eloc = c_parser_peek_token (parser)->location;
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_cast_expression (parser, ರಿಕ್ತ);
      lhs = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      ಅಭಿವ್ಯಕ್ತಿ = default_function_array_conversion (eloc, ಅಭಿವ್ಯಕ್ತಿ);
      unfolded_lhs = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      lhs = c_fully_fold (lhs, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
      orig_lhs = lhs;
      ಯದಿ (lhs == error_mark_ಗಂಟು)
	ಗಚ್ಛ saw_error;
      ಯದಿ (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      ಯದಿ (!c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  ಗಚ್ಛ saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      rhs1 = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;

      ಯದಿ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ಗಚ್ಛ saw_error;

      ಯದಿ (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	ಗಚ್ಛ saw_error;

      extra_scope = ಅಸತ್ಯ;
      no_semicolon = ಸತ್ಯ;

      ಯದಿ (c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 0), unfolded_lhs))
	{
	  ಯದಿ (ವೃಕ್ಷ_CODE (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == EQ_ಅಭಿವ್ಯಕ್ತಿ)
	    {
	      opcode = COND_ಅಭಿವ್ಯಕ್ತಿ;
	      rhs = c_fully_fold (ವೃಕ್ಷ_OPERAND (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 1),
				  ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
	      rhs1 = c_fully_fold (rhs1, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
	    }
	  ಅನ್ಯಥಾ ಯದಿ (c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 1), rhs1))
	    {
	      opcode = (ವೃಕ್ಷ_CODE (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == GT_ಅಭಿವ್ಯಕ್ತಿ
			? MIN_ಅಭಿವ್ಯಕ್ತಿ : MAX_ಅಭಿವ್ಯಕ್ತಿ);
	      rhs = c_fully_fold (rhs1, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
	      rhs1 = c_fully_fold (ವೃಕ್ಷ_OPERAND (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 0),
				   ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
	    }
	  ಅನ್ಯಥಾ
	    ಗಚ್ಛ bad_if;
	}
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == EQ_ಅಭಿವ್ಯಕ್ತಿ)
	ಗಚ್ಛ bad_if;
      ಅನ್ಯಥಾ ಯದಿ (c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 1), unfolded_lhs)
	       && c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 0), rhs1))
	{
	  opcode = (ವೃಕ್ಷ_CODE (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == GT_ಅಭಿವ್ಯಕ್ತಿ
		    ? MAX_ಅಭಿವ್ಯಕ್ತಿ : MIN_ಅಭಿವ್ಯಕ್ತಿ);
	  rhs = c_fully_fold (rhs1, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
	  rhs1 = c_fully_fold (ವೃಕ್ಷ_OPERAND (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 1),
			       ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
	}
      ಅನ್ಯಥಾ
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  ಗಚ್ಛ saw_error;
	}

      ಯದಿ (c_parser_next_token_is_keyword (parser, RID_ELSE))
	{
	  ಯದಿ (code != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_block && r == NULL_ವೃಕ್ಷ)
	      || ವೃಕ್ಷ_CODE (cmp_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) != EQ_ಅಭಿವ್ಯಕ್ತಿ)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      ಗಚ್ಛ saw_error;
	    }

	  c_parser_consume_token (parser);

	  ಯದಿ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    ಗಚ್ಛ saw_error;

	  extra_scope = ಸತ್ಯ;
	  v = c_parser_cast_expression (parser, ರಿಕ್ತ).ಮೌಲ್ಯ;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
	  ಯದಿ (v == error_mark_ಗಂಟು)
	    ಗಚ್ಛ saw_error;
	  ಯದಿ (non_lvalue_p)
	    v = non_lvalue (v);
	  ಯದಿ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    ಗಚ್ಛ saw_error;

	  ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);

	  ಯದಿ (!c_ವೃಕ್ಷ_equal (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, unfolded_lhs))
	    ಗಚ್ಛ bad_if;

	  ಯದಿ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    ಗಚ್ಛ saw_error;

	  ಯದಿ (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    ಗಚ್ಛ saw_error;

	  extra_scope = ಅಸತ್ಯ;
	  code = OMP_ATOMIC_CAPTURE_OLD;
	  ಯದಿ (r == NULL_ವೃಕ್ಷ)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  ಗಚ್ಛ saw_error;
	}
      ಅನ್ಯಥಾ ಯದಿ (code == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_ವೃಕ್ಷ
	       && v == NULL_ವೃಕ್ಷ)
	code = OMP_ATOMIC;
      ಗಚ್ಛ stmt_done;
    }
  eloc = c_parser_peek_token (parser)->location;
  ಅಭಿವ್ಯಕ್ತಿ = c_parser_cast_expression (parser, ರಿಕ್ತ);
  lhs = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
  ಅಭಿವ್ಯಕ್ತಿ = default_function_array_conversion (eloc, ಅಭಿವ್ಯಕ್ತಿ);
  unfolded_lhs = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
  lhs = c_fully_fold (lhs, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
  orig_lhs = lhs;
  ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    ಪಕ್ಷ ERROR_MARK:
    saw_error:
      c_parser_skip_to_end_of_block_or_statement (parser);
      ಯದಿ (extra_scope && c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      ಯದಿ (structured_block)
	{
	  ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  ಅನ್ಯಥಾ ಯದಿ (code == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      ಪ್ರತ್ಯಾಗಮ;

    ಪಕ್ಷ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
      ಯದಿ (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    ಪಕ್ಷ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
      lhs = ವೃಕ್ಷ_OPERAND (lhs, 0);
      unfolded_lhs = NULL_ವೃಕ್ಷ;
      opcode = PLUS_ಅಭಿವ್ಯಕ್ತಿ;
      rhs = integer_one_ಗಂಟು;
      ಯದಿ (compare)
	ಗಚ್ಛ invalid_compare;
      ಭಙ್ಗ;

    ಪಕ್ಷ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
      ಯದಿ (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    ಪಕ್ಷ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
      lhs = ವೃಕ್ಷ_OPERAND (lhs, 0);
      unfolded_lhs = NULL_ವೃಕ್ಷ;
      opcode = MINUS_ಅಭಿವ್ಯಕ್ತಿ;
      rhs = integer_one_ಗಂಟು;
      ಯದಿ (compare)
	ಗಚ್ಛ invalid_compare;
      ಭಙ್ಗ;

    ಪಕ್ಷ COMPOUND_ಅಭಿವ್ಯಕ್ತಿ:
      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (lhs, 0)) == SAVE_ಅಭಿವ್ಯಕ್ತಿ
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (lhs, 1)) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND (lhs, 1), 0)) == MODIFY_ಅಭಿವ್ಯಕ್ತಿ
	  && ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND (lhs, 1), 1) == ವೃಕ್ಷ_OPERAND (lhs, 0)
	  && C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND
					      (ವೃಕ್ಷ_OPERAND (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND (lhs, 1), 0);
      /* FALLTHRU */
    ಪಕ್ಷ MODIFY_ಅಭಿವ್ಯಕ್ತಿ:
      ಯದಿ (ವೃಕ್ಷ_CODE (lhs) == MODIFY_ಅಭಿವ್ಯಕ್ತಿ
	  && C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_OPERAND (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  ಯದಿ (integer_onep (ವೃಕ್ಷ_OPERAND (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = ವೃಕ್ಷ_OPERAND (lhs, 1);
	      lhs = ವೃಕ್ಷ_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_ವೃಕ್ಷ;
	      opcode = NOP_ಅಭಿವ್ಯಕ್ತಿ;
	      ಯದಿ (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && ವೃಕ್ಷ_CODE (orig_lhs) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      ಯದಿ (compare)
		ಗಚ್ಛ invalid_compare;
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (lhs, 1)) == TRUTH_NOT_ಅಭಿವ್ಯಕ್ತಿ
	      && ವೃಕ್ಷ_OPERAND (lhs, 0)
		 == ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = ವೃಕ್ಷ_OPERAND (lhs, 1);
	      lhs = ವೃಕ್ಷ_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_ವೃಕ್ಷ;
	      opcode = NOP_ಅಭಿವ್ಯಕ್ತಿ;
	      ಯದಿ (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && ವೃಕ್ಷ_CODE (orig_lhs) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      ಯದಿ (compare)
		ಗಚ್ಛ invalid_compare;
	      ಭಙ್ಗ;
	    }
	}
      /* FALLTHRU */
    ಸ್ವಭಾವ:
      ಯದಿ (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      ಯದಿ (compare && !c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  ಗಚ್ಛ saw_error;
	}
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
	{
	ಪಕ್ಷ CPP_MULT_EQ:
	  opcode = MULT_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_DIV_EQ:
	  opcode = TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_PLUS_EQ:
	  opcode = PLUS_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_MINUS_EQ:
	  opcode = MINUS_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_LSHIFT_EQ:
	  opcode = LSHIFT_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_RSHIFT_EQ:
	  opcode = RSHIFT_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_AND_EQ:
	  opcode = BIT_AND_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_OR_EQ:
	  opcode = BIT_IOR_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_XOR_EQ:
	  opcode = BIT_XOR_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ, unfolded_lhs);
	  rhs1 = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
	  ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (rhs1))
	    {
	    ಪಕ್ಷ MULT_ಅಭಿವ್ಯಕ್ತಿ:
	    ಪಕ್ಷ TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ:
	    ಪಕ್ಷ RDIV_ಅಭಿವ್ಯಕ್ತಿ:
	    ಪಕ್ಷ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
	    ಪಕ್ಷ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
	    ಪಕ್ಷ LSHIFT_ಅಭಿವ್ಯಕ್ತಿ:
	    ಪಕ್ಷ RSHIFT_ಅಭಿವ್ಯಕ್ತಿ:
	    ಪಕ್ಷ BIT_AND_ಅಭಿವ್ಯಕ್ತಿ:
	    ಪಕ್ಷ BIT_IOR_ಅಭಿವ್ಯಕ್ತಿ:
	    ಪಕ್ಷ BIT_XOR_ಅಭಿವ್ಯಕ್ತಿ:
	      ಯದಿ (compare)
		ಭಙ್ಗ;
	      ಯದಿ (c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (rhs1, 0), unfolded_lhs))
		{
		  opcode = ವೃಕ್ಷ_CODE (rhs1);
		  rhs = c_fully_fold (ವೃಕ್ಷ_OPERAND (rhs1, 1), ಅಸತ್ಯ, ರಿಕ್ತ,
				      ಸತ್ಯ);
		  rhs1 = c_fully_fold (ವೃಕ್ಷ_OPERAND (rhs1, 0), ಅಸತ್ಯ, ರಿಕ್ತ,
				       ಸತ್ಯ);
		  ಗಚ್ಛ stmt_done;
		}
	      ಯದಿ (c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (rhs1, 1), unfolded_lhs))
		{
		  opcode = ವೃಕ್ಷ_CODE (rhs1);
		  rhs = c_fully_fold (ವೃಕ್ಷ_OPERAND (rhs1, 0), ಅಸತ್ಯ, ರಿಕ್ತ,
				      ಸತ್ಯ);
		  rhs1 = c_fully_fold (ವೃಕ್ಷ_OPERAND (rhs1, 1), ಅಸತ್ಯ, ರಿಕ್ತ,
				       ಸತ್ಯ);
		  swapped = !commutative_ವೃಕ್ಷ_code (opcode);
		  ಗಚ್ಛ stmt_done;
		}
	      ಭಙ್ಗ;
	    ಪಕ್ಷ COND_ಅಭಿವ್ಯಕ್ತಿ:
	      ಯದಿ (!compare)
		ಭಙ್ಗ;
	      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (rhs1, 0)) != GT_ಅಭಿವ್ಯಕ್ತಿ
		  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (rhs1, 0)) != LT_ಅಭಿವ್ಯಕ್ತಿ
		  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (rhs1, 0)) != EQ_ಅಭಿವ್ಯಕ್ತಿ)
		ಭಙ್ಗ;
	      ಯದಿ (!ವೃಕ್ಷ_OPERAND (rhs1, 1))
		ಭಙ್ಗ;
	      ಯದಿ (!c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (rhs1, 2), unfolded_lhs))
		ಭಙ್ಗ;
	      ಯದಿ (c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND (rhs1, 0), 0),
				unfolded_lhs))
		{
		  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (rhs1, 0)) == EQ_ಅಭಿವ್ಯಕ್ತಿ)
		    {
		      opcode = COND_ಅಭಿವ್ಯಕ್ತಿ;
		      rhs = c_fully_fold (ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND (rhs1,
								      0), 1),
					  ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
		      rhs1 = c_fully_fold (ವೃಕ್ಷ_OPERAND (rhs1, 1), ಅಸತ್ಯ,
					   ರಿಕ್ತ, ಸತ್ಯ);
		      ಗಚ್ಛ stmt_done;
		    }
		  ಯದಿ (c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND (rhs1, 0), 1),
				    ವೃಕ್ಷ_OPERAND (rhs1, 1)))
		    {
		      opcode = (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (rhs1, 0)) == GT_ಅಭಿವ್ಯಕ್ತಿ
				? MIN_ಅಭಿವ್ಯಕ್ತಿ : MAX_ಅಭಿವ್ಯಕ್ತಿ);
		      rhs = c_fully_fold (ವೃಕ್ಷ_OPERAND (rhs1, 1), ಅಸತ್ಯ, ರಿಕ್ತ,
					  ಸತ್ಯ);
		      rhs1 = c_fully_fold (ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND (rhs1,
								       0), 0),
					   ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
		      ಗಚ್ಛ stmt_done;
		    }
		}
	      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (rhs1, 0)) == EQ_ಅಭಿವ್ಯಕ್ತಿ)
		ಭಙ್ಗ;
	      ಅನ್ಯಥಾ ಯದಿ (c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  ಯದಿ (c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND (rhs1, 0), 0),
				    ವೃಕ್ಷ_OPERAND (rhs1, 1)))
		    {
		      opcode = (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (rhs1, 0)) == GT_ಅಭಿವ್ಯಕ್ತಿ
				? MAX_ಅಭಿವ್ಯಕ್ತಿ : MIN_ಅಭಿವ್ಯಕ್ತಿ);
		      rhs = c_fully_fold (ವೃಕ್ಷ_OPERAND (rhs1, 1), ಅಸತ್ಯ, ರಿಕ್ತ,
					  ಸತ್ಯ);
		      rhs1 = c_fully_fold (ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND (rhs1,
								       0), 1),
					   ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
		      ಗಚ್ಛ stmt_done;
		    }
		}
	      ಭಙ್ಗ;
	    ಪಕ್ಷ EQ_ಅಭಿವ್ಯಕ್ತಿ:
	      ಯದಿ (!compare
		  || code != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_block
		  || v
		  || r)
		ಭಙ್ಗ;
	      ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_ವೃಕ್ಷ;
		  c_parser_consume_token (parser);
		  ಗಚ್ಛ restart;
		}
	      ಭಙ್ಗ;
	    ಪಕ್ಷ ERROR_MARK:
	      ಗಚ್ಛ saw_error;
	    ಸ್ವಭಾವ:
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (c_parser_peek_token (parser)->type == CPP_SEMICOLON)
	    {
	      ಯದಿ (structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
		{
		  code = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_ವೃಕ್ಷ;
		  ಅಭಿವ್ಯಕ್ತಿ = default_function_array_read_conversion (eloc, ಅಭಿವ್ಯಕ್ತಿ);
		  unfolded_lhs1 = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
		  lhs1 = c_fully_fold (unfolded_lhs1, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
		  rhs1 = NULL_ವೃಕ್ಷ;
		  c_parser_consume_token (parser);
		  ಗಚ್ಛ restart;
		}
	      ಯದಿ (structured_block && !compare)
		{
		  opcode = NOP_ಅಭಿವ್ಯಕ್ತಿ;
		  ಅಭಿವ್ಯಕ್ತಿ = default_function_array_read_conversion (eloc, ಅಭಿವ್ಯಕ್ತಿ);
		  rhs = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
		  rhs1 = NULL_ವೃಕ್ಷ;
		  ಗಚ್ಛ stmt_done;
		}
	    }
	  c_parser_error (parser, "invalid form of %<#pragma omp atomic%>");
	  ಗಚ್ಛ saw_error;
	ಸ್ವಭಾವ:
	  c_parser_error (parser,
			  "invalid operator for %<#pragma omp atomic%>");
	  ಗಚ್ಛ saw_error;
	}

      /* Arrange to pass the location of the assignment operator to
	 c_finish_omp_atomic.  */
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_expression (parser);
      ಅಭಿವ್ಯಕ್ತಿ = default_function_array_read_conversion (eloc, ಅಭಿವ್ಯಕ್ತಿ);
      rhs = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      rhs = c_fully_fold (rhs, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
      ಭಙ್ಗ;
    }
stmt_done:
  ಯದಿ (structured_block && code == OMP_ATOMIC_CAPTURE_NEW && r == NULL_ವೃಕ್ಷ)
    {
      ಯದಿ (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ಗಚ್ಛ saw_error;
      no_semicolon = ಅಸತ್ಯ;
      v = c_parser_cast_expression (parser, ರಿಕ್ತ).ಮೌಲ್ಯ;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
      ಯದಿ (v == error_mark_ಗಂಟು)
	ಗಚ್ಛ saw_error;
      ಯದಿ (non_lvalue_p)
	v = non_lvalue (v);
      ಯದಿ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	ಗಚ್ಛ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_cast_expression (parser, ರಿಕ್ತ);
      lhs1 = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      ಅಭಿವ್ಯಕ್ತಿ = default_function_array_read_conversion (eloc, ಅಭಿವ್ಯಕ್ತಿ);
      unfolded_lhs1 = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      lhs1 = c_fully_fold (lhs1, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
      ಯದಿ (lhs1 == error_mark_ಗಂಟು)
	ಗಚ್ಛ saw_error;
      ಯದಿ (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  ಯದಿ (structured_block)
    {
      ಯದಿ (!no_semicolon)
	c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
done:
  ಯದಿ (weak && opcode != COND_ಅಭಿವ್ಯಕ್ತಿ)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = ಅಸತ್ಯ;
    }
  ಯದಿ (unfolded_lhs && unfolded_lhs1
      && !c_ವೃಕ್ಷ_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_ಗಂಟು;
    }
  ಅನ್ಯಥಾ
    stmt = c_finish_omp_atomic (loc, code, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, memory_order, weak);
  ಯದಿ (stmt != error_mark_ಗಂಟು)
    add_stmt (stmt);

  ಯದಿ (!structured_block && !no_semicolon)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}


/* OpenMP 2.5:
   # pragma omp barrier new-line
*/

ಸ್ಥಿರ ಶೂನ್ಯ
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_critical (location_t loc, c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ stmt, name = NULL_ವೃಕ್ಷ, clauses = NULL_ವೃಕ್ಷ;

  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      ಅನ್ಯಥಾ
	c_parser_error (parser, "expected identifier");

      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_MASK,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_block (parser, if_p);
  ಪ್ರತ್ಯಾಗಮ c_finish_omp_critical (loc, stmt, name, clauses);
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_depobj (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    {
      c_parser_skip_to_pragma_eol (parser);
      ಪ್ರತ್ಯಾಗಮ;
    }

  ವೃಕ್ಷ depobj = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ).ಮೌಲ್ಯ;
  ಯದಿ (depobj != error_mark_ಗಂಟು)
    {
      ಯದಿ (!lvalue_p (depobj))
	{
	  error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ
	{
	  ವೃಕ್ಷ addr = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (depobj, loc), ADDR_ಅಭಿವ್ಯಕ್ತಿ,
				      depobj, ಅಸತ್ಯ);
	  ಯದಿ (addr == error_mark_ಗಂಟು)
	    depobj = error_mark_ಗಂಟು;
	  ಅನ್ಯಥಾ
	    depobj = build_indirect_ref (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_STAR);
	}
    }

  parens.skip_until_found_close (parser);
  ವೃಕ್ಷ clause = NULL_ವೃಕ್ಷ;
  ಗಣನಾ omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_INVALID;
  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);

      c_parser_consume_token (parser);
      ಯದಿ (!strcmp ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_ವೃಕ್ಷ, c_loc);
	  clause = c_finish_omp_clauses (clause, C_ORT_OMP);
	  ಯದಿ (!clause)
	    clause = error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (!strcmp ("destroy", p))
	{
	  matching_parens c_parens;
	  kind = OMP_CLAUSE_DEPEND_LAST;
	  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      ವೃಕ್ಷ destobj = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ).ಮೌಲ್ಯ;
	      ಯದಿ (!lvalue_p (destobj))
		error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      ಅನ್ಯಥಾ ಯದಿ (depobj != error_mark_ಗಂಟು
		       && !operand_equal_p (destobj, depobj,
					    OEP_MATCH_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_found_close (parser);
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (!strcmp ("update", p))
	{
	  matching_parens c_parens;
	  ಯದಿ (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
		{
		  ಧ್ರುವ ವರ್ಣ *p2
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);

		  c_parser_consume_token (parser);
		  ಯದಿ (!strcmp ("in", p2))
		    kind = OMP_CLAUSE_DEPEND_IN;
		  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("out", p2))
		    kind = OMP_CLAUSE_DEPEND_OUT;
		  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("inout", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUT;
		  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("mutexinoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  ಅನ್ಯಥಾ ಯದಿ (!strcmp ("inoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      ಯದಿ (kind == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_ಗಂಟು;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_found_close (parser);
	    }
	  ಅನ್ಯಥಾ
	    clause = error_mark_ಗಂಟು;
	}
    }
  ಯದಿ (!clause && kind == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_ಗಂಟು;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_flush (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  ಗಣನಾ memmodel mo = MEMMODEL_LAST;
  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);

      ಯದಿ (!strcmp (p, "seq_cst"))
	mo = MEMMODEL_SEQ_CST;
      ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "acq_rel"))
	mo = MEMMODEL_ACQ_REL;
      ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "release"))
	mo = MEMMODEL_RELEASE;
      ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "acquire"))
	mo = MEMMODEL_ACQUIRE;
      ಅನ್ಯಥಾ
	error_at (c_parser_peek_token (parser)->location,
		  "expected %<seq_cst%>, %<acq_rel%>, %<release%> or "
		  "%<acquire%>");
      c_parser_consume_token (parser);
    }
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      ಯದಿ (mo != MEMMODEL_LAST)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ರಿಕ್ತ);
    }
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_to_pragma_eol (parser);

  c_finish_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_omp_section_scan (c_parser *parser, ಧ್ರುವ ವರ್ಣ *directive,
			   ತಾರ್ಕಿಕ tentative)
{
  ಯದಿ (!c_parser_nth_token_starts_std_attributes (parser, 1))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  unsigned ಪೂರ್ಣಾಙ್ಕ n = 3;
  ಯದಿ (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  ಯದಿ (token->type != CPP_CLOSE_SQUARE)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  ಯದಿ (token->type != CPP_CLOSE_SQUARE)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಯದಿ (n < 9)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಯದಿ (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      ವೃಕ್ಷ first = c_parser_peek_nth_token_raw (parser, 3)->ಮೌಲ್ಯ;
      ವೃಕ್ಷ second = c_parser_peek_nth_token_raw (parser, 5)->ಮೌಲ್ಯ;
      ಯದಿ (strcmp (IDENTIFIER_POINTER (first), "directive")
	  && strcmp (IDENTIFIER_POINTER (first), "__directive__"))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      ಯದಿ (strcmp (IDENTIFIER_POINTER (second), directive))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }
  ಯದಿ (tentative)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
  location_t first_loc = c_parser_peek_token (parser)->location;
  location_t last_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t ಮಧ್ಯ_loc = UNKNOWN_LOCATION;
  ವೃಕ್ಷ std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  ತಾರ್ಕಿಕ seen = ಅಸತ್ಯ;
  ಪೂರ್ಣಾಙ್ಕ cnt = 0;
  ಪ್ರತಿ (ವೃಕ್ಷ attr = std_attrs; attr; attr = ವೃಕ್ಷ_CHAIN (attr))
    ಯದಿ (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	ಪ್ರತಿ (ವೃಕ್ಷ a = ವೃಕ್ಷ_ಮೌಲ್ಯ (attr); a; a = ವೃಕ್ಷ_CHAIN (a))
	  {
	    ವೃಕ್ಷ d = ವೃಕ್ಷ_ಮೌಲ್ಯ (a);
	    gcc_assert (ವೃಕ್ಷ_CODE (d) == C_TOKEN_VEC);
	    c_token *first = C_TOKEN_VEC_TOKENS (d)->address ();
	    cnt++;
	    ಯದಿ (first->type == CPP_NAME
		&& strcmp (IDENTIFIER_POINTER (first->ಮೌಲ್ಯ),
			   directive) == 0)
	      {
		seen = ಸತ್ಯ;
		ಯದಿ (ಮಧ್ಯ_loc == UNKNOWN_LOCATION)
		  ಮಧ್ಯ_loc = first->location;
	      }
	  }
      }
  ಯದಿ (!seen)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಯದಿ (cnt != 1 || ವೃಕ್ಷ_CHAIN (std_attrs))
    {
      error_at (make_location (first_loc, last_loc, ಮಧ್ಯ_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }
  c_parser_handle_statement_omp_attributes (parser, std_attrs, ರಿಕ್ತ);
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_structured_block_sequence (c_parser *parser,
					ಗಣನಾ pragma_kind kind)
{
  ವೃಕ್ಷ stmt = ತಳ್ಳು_stmt_list ();
  c_parser_statement (parser, ರಿಕ್ತ);
  ಕುರು
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	ಭಙ್ಗ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_EOF))
	ಭಙ್ಗ;

      ಯದಿ (kind != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_kind == kind)
	ಭಙ್ಗ;

      ಯದಿ (kind != PRAGMA_NONE
	  && c_parser_omp_section_scan (parser,
					kind == PRAGMA_OMP_SCAN
					? "scan" : "section", ಅಸತ್ಯ))
	ಭಙ್ಗ;

      c_parser_statement (parser, ರಿಕ್ತ);
    }
  ಯಾವತ್ (1);
  ಪ್ರತ್ಯಾಗಮ ತೆಗೆ_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_scan_loop_body (c_parser *parser, ತಾರ್ಕಿಕ open_brace_parsed)
{
  ವೃಕ್ಷ substmt;
  location_t loc;
  ವೃಕ್ಷ clauses = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ found_scan = ಅಸತ್ಯ;

  loc = c_parser_peek_token (parser)->location;
  ಯದಿ (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = ಅಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SCAN)
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_OMP_SCAN);
  ಅನ್ಯಥಾ
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_ಗಂಟು, substmt, NULL_ವೃಕ್ಷ);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (substmt, loc);
  add_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  ಯದಿ (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SCAN)
    {
      ಗಣನಾ omp_clause_code clause = OMP_CLAUSE_ERROR;
      found_scan = ಸತ್ಯ;

      c_parser_consume_pragma (parser);

      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ಧ್ರುವ ವರ್ಣ *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	  ಯದಿ (strcmp (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      ಯದಿ (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_ವೃಕ್ಷ);
	}
      ಅನ್ಯಥಾ
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_to_pragma_eol (parser);
    }
  ಅನ್ಯಥಾ
    error ("expected %<#pragma omp scan%>");

  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  ಯದಿ (!c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_NONE);
  ಅನ್ಯಥಾ
    {
      ಯದಿ (found_scan)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_ಗಂಟು, substmt, clauses);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (substmt, loc);
  add_stmt (substmt);

  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_omp_next_tokens_can_be_canon_loop (c_parser *parser,
					    ಗಣನಾ ವೃಕ್ಷ_code code,
					    ತಾರ್ಕಿಕ error_p)
{
  ಯದಿ (code == OACC_LOOP)
    {
      ಯದಿ (c_parser_next_token_is_keyword (parser, RID_FOR))
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
      ಯದಿ (error_p)
	c_parser_error (parser, "for statement expected");
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (c_parser_next_token_is_keyword (parser, RID_FOR))
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

      ಯದಿ (c_parser_next_token_is (parser, CPP_PRAGMA))
	ವಿಕಲ್ಪ (c_parser_peek_token (parser)->pragma_kind)
	  {
	  ಪಕ್ಷ PRAGMA_OMP_UNROLL:
	  ಪಕ್ಷ PRAGMA_OMP_TILE:
	    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	  ಸ್ವಭಾವ:
	    ಭಙ್ಗ;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      size_t n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      ಯದಿ (token->type == CPP_NAME
	  && C_IS_RESERVED_WORD (token->ಮೌಲ್ಯ)
	  && C_RID_CODE (token->ಮೌಲ್ಯ) == RID_FOR)
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
      ಯದಿ (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

ಸ್ಥಿರ ವೃಕ್ಷ c_parser_omp_tile (location_t, c_parser *, ತಾರ್ಕಿಕ *);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_omp_unroll (location_t, c_parser *, ತಾರ್ಕಿಕ *);

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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_loop_nest (c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ decl = NULL_ವೃಕ್ಷ, cond = NULL_ವೃಕ್ಷ, incr = NULL_ವೃಕ್ಷ, init = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ body = NULL_ವೃಕ್ಷ;
  matching_parens parens;
  ತಾರ್ಕಿಕ moreloops;
  unsigned ವರ್ಣ save_in_statement;
  ವೃಕ್ಷ loop_scope;
  location_t loc;
  ಸಂರಚನಾ omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  ಪೂರ್ಣಾಙ್ಕ depth = omp_for_parse_state->depth;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  ಯದಿ (c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      ವೃಕ್ಷ std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_attributes (parser, std_attrs, ರಿಕ್ತ);
      ಯದಿ (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  ಯದಿ (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      ವೃಕ್ಷ transform = NULL_ವೃಕ್ಷ, sizes, body = NULL_ವೃಕ್ಷ;
      ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ = 0;
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->pragma_kind)
	{
	ಪಕ್ಷ PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = ತಳ್ಳು_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = ತೆಗೆ_stmt_list (body);
	  ಯದಿ (transform == NULL_ವೃಕ್ಷ || transform == error_mark_ಗಂಟು)
	    {
	      transform = error_mark_ಗಂಟು;
	      ಭಙ್ಗ;
	    }
	  gcc_assert (ವೃಕ್ಷ_CODE (transform) == OMP_UNROLL);
	  ಯದಿ (omp_find_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      ಯದಿ (omp_for_parse_state->ಎಣಿಕೆ - depth > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->ಎಣಿಕೆ - depth);
		  transform = error_mark_ಗಂಟು;
		}
	      ಅನ್ಯಥಾ
		ಎಣಿಕೆ = 1;
	    }
	  ಅನ್ಯಥಾ
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_ಗಂಟು;
	    }
	  ಭಙ್ಗ;
	ಪಕ್ಷ PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = ತಳ್ಳು_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = ತೆಗೆ_stmt_list (body);
	  ಯದಿ (transform == NULL_ವೃಕ್ಷ || transform == error_mark_ಗಂಟು)
	    {
	      transform = error_mark_ಗಂಟು;
	      ಭಙ್ಗ;
	    }
	  gcc_assert (ವೃಕ್ಷ_CODE (transform) == OMP_TILE);
	  sizes = omp_find_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  ಎಣಿಕೆ = list_length (OMP_CLAUSE_SIZES_LIST (sizes));
	  ಯದಿ (depth + ಎಣಿಕೆ < omp_for_parse_state->ಎಣಿಕೆ)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			ಎಣಿಕೆ, omp_for_parse_state->ಎಣಿಕೆ - depth);
	      transform = error_mark_ಗಂಟು;
	    }
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  c_parser_pragma (parser, pragma_stmt, ರಿಕ್ತ, void_list_ಗಂಟು);
	  ಭಙ್ಗ;
	}
      ಯದಿ (transform == NULL_ವೃಕ್ಷ)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      ಯದಿ (transform == NULL_ವೃಕ್ಷ || transform == error_mark_ಗಂಟು)
	{
	  omp_for_parse_state->fail = ಸತ್ಯ;
	  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
	}
      ಪ್ರತಿ (ಎಣಿಕೆ = omp_for_parse_state->ಎಣಿಕೆ; depth < ಎಣಿಕೆ; ++depth)
	{
	  ವೃಕ್ಷ_VEC_ELT (omp_for_parse_state->declv, depth) = NULL_ವೃಕ್ಷ;
	  ವೃಕ್ಷ_VEC_ELT (omp_for_parse_state->initv, depth) = NULL_ವೃಕ್ಷ;
	  ವೃಕ್ಷ_VEC_ELT (omp_for_parse_state->condv, depth) = NULL_ವೃಕ್ಷ;
	  ವೃಕ್ಷ_VEC_ELT (omp_for_parse_state->incrv, depth) = NULL_ವೃಕ್ಷ;
	}
      omp_for_parse_state->want_nested_loop = ಅಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_in_statement = in_statement;
  in_statement = IN_OMP_BLOCK;

  /* We are not in intervening code now.  */
  omp_for_parse_state->in_intervening_code = ಅಸತ್ಯ;

  ಯದಿ (!parens.require_open (parser))
    {
      omp_for_parse_state->fail = ಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (ಸತ್ಯ);

  /* Parse the initialization declaration or expression.  */
  ಯದಿ (c_parser_next_tokens_start_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      ವೃಕ್ಷ this_pre_body = ತಳ್ಳು_stmt_list ();
      c_in_omp_for = ಸತ್ಯ;
      c_parser_declaration_or_fndef (parser, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ,
				     ಅಸತ್ಯ);
      c_in_omp_for = ಅಸತ್ಯ;
      this_pre_body = ತೆಗೆ_stmt_list (this_pre_body);
      append_to_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      ಯದಿ (decl == ರಿಕ್ತ)
	ಗಚ್ಛ error_init;
      ಯದಿ (DECL_INITIAL (decl) == error_mark_ಗಂಟು)
	decl = error_mark_ಗಂಟು;
      init = decl;
    }
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ decl_exp;
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_expression (parser);
      decl = decl_exp.ಮೌಲ್ಯ;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_in_omp_for = ಸತ್ಯ;
      init = build_modify_ಅಭಿವ್ಯಕ್ತಿ (init_loc, decl, decl_exp.original_type,
				NOP_ಅಭಿವ್ಯಕ್ತಿ, init_loc, init_exp.ಮೌಲ್ಯ,
				init_exp.original_type);
      c_in_omp_for = ಅಸತ್ಯ;
      init = c_process_ಅಭಿವ್ಯಕ್ತಿ_stmt (init_loc, init);

      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  ಅನ್ಯಥಾ
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->fail = ಸತ್ಯ;
      ಗಚ್ಛ parse_next;
    }

  /* Parse the loop condition.  */
  ಯದಿ (c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_in_omp_for = ಸತ್ಯ;
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ cond_ಅಭಿವ್ಯಕ್ತಿ
	= c_parser_ದ್ವಿಮಾನ_expression (parser, ರಿಕ್ತ, NULL_ವೃಕ್ಷ);
      c_in_omp_for = ಅಸತ್ಯ;

      cond = cond_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      ವಿಕಲ್ಪ (cond_ಅಭಿವ್ಯಕ್ತಿ.original_code)
	{
	ಪಕ್ಷ GT_ಅಭಿವ್ಯಕ್ತಿ:
	ಪಕ್ಷ GE_ಅಭಿವ್ಯಕ್ತಿ:
	ಪಕ್ಷ LT_ಅಭಿವ್ಯಕ್ತಿ:
	ಪಕ್ಷ LE_ಅಭಿವ್ಯಕ್ತಿ:
	  ಭಙ್ಗ;
	ಪಕ್ಷ NE_ಅಭಿವ್ಯಕ್ತಿ:
	  ಯದಿ (omp_for_parse_state->code != OACC_LOOP)
	    ಭಙ್ಗ;
	  /* FALLTHRU.  */
	ಸ್ವಭಾವ:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು, error_mark_ಗಂಟು);
	  ಭಙ್ಗ;
	}
      protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (cond, cond_loc);
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  ಯದಿ (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_ಅಭಿವ್ಯಕ್ತಿ_stmt (incr_loc,
				  c_parser_expression (parser).ಮೌಲ್ಯ);
    }
  parens.skip_until_found_close (parser);

  ಯದಿ (decl == ರಿಕ್ತ || decl == error_mark_ಗಂಟು || init == error_mark_ಗಂಟು)
    omp_for_parse_state->fail = ಸತ್ಯ;
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ_VEC_ELT (omp_for_parse_state->declv, depth) = decl;
      ವೃಕ್ಷ_VEC_ELT (omp_for_parse_state->initv, depth) = init;
      ವೃಕ್ಷ_VEC_ELT (omp_for_parse_state->condv, depth) = cond;
      ವೃಕ್ಷ_VEC_ELT (omp_for_parse_state->incrv, depth) = incr;
    }

parse_next:
  moreloops = depth < omp_for_parse_state->ಎಣಿಕೆ - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  ಯದಿ (moreloops
      && c_parser_omp_next_tokens_can_be_canon_loop (parser,
						     omp_for_parse_state->code,
						     ಅಸತ್ಯ))
    {
      omp_for_parse_state->depth++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->depth--;
    }
  ಅನ್ಯಥಾ ಯದಿ (moreloops && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* This is the open brace in the loop-body grammar production.  Rather
	 than trying to special-case braces, just parse it as a compound
	 statement and handle the nested loop-body case there.  Note that
	 when we see a further open brace inside the compound statement
	 loop-body, we don't know whether it is the start of intervening
	 code that is a compound statement, or a level of braces
	 surrounding a nested loop-body.  Use the WANT_NESTED_LOOP state
	 bit to ensure we have only one nested loop at each level.  */
      omp_for_parse_state->in_intervening_code = ಸತ್ಯ;
      body = c_parser_compound_statement (parser, ರಿಕ್ತ);
      omp_for_parse_state->in_intervening_code = ಅಸತ್ಯ;
      ಯದಿ (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = ಸತ್ಯ;
	}
      if_p = ರಿಕ್ತ;
    }
  ಅನ್ಯಥಾ
    {
      /* This is the final-loop-body case in the grammar: we have
	 something that is not a FOR and not an open brace.  */
      ಯದಿ (moreloops)
	{
	  /* If we were expecting a nested loop, give an error and mark
	     that parsing has failed, and try to recover by parsing the
	     body as regular code without further collapsing.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = ಸತ್ಯ;
	}
      in_statement = IN_OMP_FOR;
      parser->omp_for_parse_state = ರಿಕ್ತ;
      body = ತಳ್ಳು_stmt_list ();
      ಯದಿ (omp_for_parse_state->inscan)
	c_parser_omp_scan_loop_body (parser, ಅಸತ್ಯ);
      ಅನ್ಯಥಾ
	add_stmt (c_parser_c99_block_statement (parser, if_p));
      body = ತೆಗೆ_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  in_statement = save_in_statement;
  omp_for_parse_state->want_nested_loop = ಅಸತ್ಯ;
  omp_for_parse_state->in_intervening_code = ಸತ್ಯ;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  ಯದಿ (body)
    add_stmt (body);
  body = c_end_compound_stmt (loc, loop_scope, ಸತ್ಯ);
  ಯದಿ (decl && ವೃಕ್ಷ_CODE (body) == BIND_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ವೃಕ್ಷ t = BIND_ಅಭಿವ್ಯಕ್ತಿ_VARS (body);
      ವೃಕ್ಷ prev = NULL_ವೃಕ್ಷ, next = NULL_ವೃಕ್ಷ;
      ಯಾವತ್ (t)
	{
	  next = DECL_CHAIN (t);
	  ಯದಿ (t == decl)
	    {
	      ಯದಿ (prev)
		DECL_CHAIN (prev) = next;
	      ಅನ್ಯಥಾ
		{
		  BIND_ಅಭಿವ್ಯಕ್ತಿ_VARS (body) = next;
		  BLOCK_VARS (BIND_ಅಭಿವ್ಯಕ್ತಿ_BLOCK (body)) = next;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ
	    {
	      prev = t;
	      t = next;
	    }
	}
      ಯದಿ (BIND_ಅಭಿವ್ಯಕ್ತಿ_VARS (body) == NULL_ವೃಕ್ಷ)
	body = BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (body);
    }

  ಪ್ರತ್ಯಾಗಮ body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_for_loop (location_t loc, c_parser *parser, ಗಣನಾ ವೃಕ್ಷ_code code,
		       ವೃಕ್ಷ clauses, ವೃಕ್ಷ *cclauses, ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ body, stmt, cl;
  ವೃಕ್ಷ ret = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ ordered_cl = NULL_ವೃಕ್ಷ;
  ಪೂರ್ಣಾಙ್ಕ i, collapse = 1, ordered = 0, ಎಣಿಕೆ;
  ತಾರ್ಕಿಕ oacc_tiling = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ inscan = ಅಸತ್ಯ;
  ಸಂರಚನಾ omp_for_parse_data data;
  ಸಂರಚನಾ omp_for_parse_data *save_data = parser->omp_for_parse_state;

  ಪ್ರತಿ (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    ಯದಿ (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = ವೃಕ್ಷ_to_shwi (OMP_CLAUSE_COLLAPSE_ಅಭಿವ್ಯಕ್ತಿ (cl));
    ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = ಸತ್ಯ;
	collapse = list_length (OMP_CLAUSE_TILE_LIST (cl));
      }
    ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_SIZES)
      collapse = list_length (OMP_CLAUSE_SIZES_LIST (cl));
    ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_ಅಭಿವ್ಯಕ್ತಿ (cl))
      {
	ordered_cl = cl;
	ordered = ವೃಕ್ಷ_to_shwi (OMP_CLAUSE_ORDERED_ಅಭಿವ್ಯಕ್ತಿ (cl));
      }
    ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (code == OMP_SIMD || code == OMP_FOR))
      inscan = ಸತ್ಯ;

  ಯದಿ (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_ಅಭಿವ್ಯಕ್ತಿ (ordered_cl)
	= build_int_cst (integer_type_ಗಂಟು, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  ಎಣಿಕೆ = ordered ? ordered : collapse;

  ಯದಿ (!c_parser_omp_next_tokens_can_be_canon_loop (parser, code, ಸತ್ಯ))
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

  /* Initialize parse state for recursive descent.  */
  data.declv = make_ವೃಕ್ಷ_vec (ಎಣಿಕೆ);
  data.initv = make_ವೃಕ್ಷ_vec (ಎಣಿಕೆ);
  data.condv = make_ವೃಕ್ಷ_vec (ಎಣಿಕೆ);
  data.incrv = make_ವೃಕ್ಷ_vec (ಎಣಿಕೆ);
  data.pre_body = NULL_ವೃಕ್ಷ;
  data.bindings = NULL_ವೃಕ್ಷ;
  data.for_loc = c_parser_peek_token (parser)->location;
  data.ಎಣಿಕೆ = ಎಣಿಕೆ;
  data.depth = 0;
  data.want_nested_loop = ಸತ್ಯ;
  data.ordered = ordered > 0;
  data.in_intervening_code = ಅಸತ್ಯ;
  data.perfect_nesting_fail = ಅಸತ್ಯ;
  data.fail = ಅಸತ್ಯ;
  data.inscan = inscan;
  data.saw_intervening_code = ಅಸತ್ಯ;
  data.code = code;
  parser->omp_for_parse_state = &data;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  ಪ್ರತಿ (ವೃಕ್ಷ t = data.bindings; t; )
    {
      ವೃಕ್ಷ n = ವೃಕ್ಷ_CHAIN (t);
      ವೃಕ್ಷ_CHAIN (t) = NULL_ವೃಕ್ಷ;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  ಯದಿ (!data.fail)
    {
      c_in_omp_for = ಸತ್ಯ;
      stmt = c_finish_omp_for (loc, code, data.declv, ರಿಕ್ತ, data.initv,
			       data.condv, data.incrv,
			       body, data.pre_body, ಸತ್ಯ);
      c_in_omp_for = ಅಸತ್ಯ;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      ಯದಿ (stmt && !c_omp_check_loop_iv (stmt, data.declv, ರಿಕ್ತ))
	stmt = NULL_ವೃಕ್ಷ;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      ಯದಿ (data.saw_intervening_code
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, ರಿಕ್ತ))
	stmt = NULL_ವೃಕ್ಷ;

      ಯದಿ (stmt)
	{
	  add_stmt (stmt);

	  ಪ್ರತಿ (i = 0; i < ವೃಕ್ಷ_VEC_LENGTH (OMP_FOR_INIT (stmt)); i++)
	    {
	      ವೃಕ್ಷ init = ವೃಕ್ಷ_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      ಯದಿ (init == NULL_ವೃಕ್ಷ)
		ಭಙ್ಗ;
	      gcc_assert (ವೃಕ್ಷ_CODE (init) == MODIFY_ಅಭಿವ್ಯಕ್ತಿ);
	      ವೃಕ್ಷ decl = ವೃಕ್ಷ_OPERAND (init, 0);
	      ವೃಕ್ಷ cond = ವೃಕ್ಷ_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (ವೃಕ್ಷ_OPERAND (cond, 0) == decl);

	      ವೃಕ್ಷ op0 = ವೃಕ್ಷ_OPERAND (init, 1);
	      ಯದಿ (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || ವೃಕ್ಷ_CODE (op0) != ವೃಕ್ಷ_VEC)
		ವೃಕ್ಷ_OPERAND (init, 1) = c_fully_fold (op0, ಅಸತ್ಯ, ರಿಕ್ತ);
	      ಅನ್ಯಥಾ
		{
		  ವೃಕ್ಷ_VEC_ELT (op0, 1)
		    = c_fully_fold (ವೃಕ್ಷ_VEC_ELT (op0, 1), ಅಸತ್ಯ, ರಿಕ್ತ);
		  ವೃಕ್ಷ_VEC_ELT (op0, 2)
		    = c_fully_fold (ವೃಕ್ಷ_VEC_ELT (op0, 2), ಅಸತ್ಯ, ರಿಕ್ತ);
		}

	      ವೃಕ್ಷ op1 = ವೃಕ್ಷ_OPERAND (cond, 1);
	      ಯದಿ (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || ವೃಕ್ಷ_CODE (op1) != ವೃಕ್ಷ_VEC)
		ವೃಕ್ಷ_OPERAND (cond, 1) = c_fully_fold (op1, ಅಸತ್ಯ, ರಿಕ್ತ);
	      ಅನ್ಯಥಾ
		{
		  ವೃಕ್ಷ_VEC_ELT (op1, 1)
		    = c_fully_fold (ವೃಕ್ಷ_VEC_ELT (op1, 1), ಅಸತ್ಯ, ರಿಕ್ತ);
		  ವೃಕ್ಷ_VEC_ELT (op1, 2)
		    = c_fully_fold (ವೃಕ್ಷ_VEC_ELT (op1, 2), ಅಸತ್ಯ, ರಿಕ್ತ);
		}
	    }

	  ಯದಿ (cclauses != ರಿಕ್ತ
	      && cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL] != ರಿಕ್ತ)
	    {
	      ವೃಕ್ಷ *c;
	      ಪ್ರತಿ (c = &cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL]; *c ; )
		ಯದಿ (OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		ಅನ್ಯಥಾ
		  {
		    ಪ್ರತಿ (i = 0; i < ಎಣಿಕೆ; i++)
		      ಯದಿ (ವೃಕ್ಷ_VEC_ELT (data.declv, i) == OMP_CLAUSE_DECL (*c))
			ಭಙ್ಗ;
		    ಯದಿ (i == ಎಣಿಕೆ)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (*c) == OMP_CLAUSE_FIRSTPRIVATE)
		      {
			error_at (loc,
				  "iteration variable %qD should not be firstprivate",
				  OMP_CLAUSE_DECL (*c));
			*c = OMP_CLAUSE_CHAIN (*c);
		      }
		    ಅನ್ಯಥಾ
		      {
			/* Move lastprivate (decl) clause to
			   OMP_FOR_CLAUSES.  */
			ವೃಕ್ಷ l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			ಯದಿ (code == OMP_SIMD)
			  {
			    OMP_CLAUSE_CHAIN (l)
			      = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
			    cclauses[C_OMP_CLAUSE_SPLIT_FOR] = l;
			  }
			ಅನ್ಯಥಾ
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
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

ಸ್ಥಿರ ಶೂನ್ಯ
omp_split_clauses (location_t loc, ಗಣನಾ ವೃಕ್ಷ_code code,
		   omp_clause_mask mask, ವೃಕ್ಷ clauses, ವೃಕ್ಷ *cclauses)
{
  ಪೂರ್ಣಾಙ್ಕ i;
  c_omp_split_clauses (loc, code, mask, clauses, cclauses);
  ಪ್ರತಿ (i = 0; i < C_OMP_CLAUSE_SPLIT_ಎಣಿಕೆ; i++)
    ಯದಿ (cclauses[i])
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_loop (location_t loc, c_parser *parser,
		   ವರ್ಣ *p_name, omp_clause_mask mask, ವೃಕ್ಷ *cclauses,
		   ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ block, clauses, ret;

  strcat (p_name, " loop");
  mask |= OMP_LOOP_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ರಿಕ್ತ);
  ಯದಿ (cclauses)
    {
      omp_split_clauses (loc, OMP_LOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_LOOP];
    }

  block = c_begin_compound_stmt (ಸತ್ಯ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
  add_stmt (block);

  ಪ್ರತ್ಯಾಗಮ ret;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_simd (location_t loc, c_parser *parser,
		   ವರ್ಣ *p_name, omp_clause_mask mask, ವೃಕ್ಷ *cclauses,
		   ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ block, clauses, ret;

  strcat (p_name, " simd");
  mask |= OMP_SIMD_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ರಿಕ್ತ);
  ಯದಿ (cclauses)
    {
      omp_split_clauses (loc, OMP_SIMD, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SIMD];
    }

  block = c_begin_compound_stmt (ಸತ್ಯ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
  add_stmt (block);

  ಪ್ರತ್ಯಾಗಮ ret;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_for (location_t loc, c_parser *parser,
		  ವರ್ಣ *p_name, omp_clause_mask mask, ವೃಕ್ಷ *cclauses,
		  ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ block, clauses, ret;

  strcat (p_name, " for");
  mask |= OMP_FOR_CLAUSE_MASK;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  ಯದಿ (cclauses && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  ಯದಿ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);

      ಯದಿ (strcmp (p, "simd") == 0)
	{
	  ವೃಕ್ಷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ಎಣಿಕೆ];
	  ಯದಿ (cclauses == ರಿಕ್ತ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	    ಪ್ರತ್ಯಾಗಮ c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (ಸತ್ಯ);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
	  ಯದಿ (ret == NULL_ವೃಕ್ಷ)
	    ಪ್ರತ್ಯಾಗಮ ret;
	  ret = make_ಗಂಟು (OMP_FOR);
	  ವೃಕ್ಷ_TYPE (ret) = void_type_ಗಂಟು;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
	  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret, loc);
	  add_stmt (ret);
	  ಪ್ರತ್ಯಾಗಮ ret;
	}
    }
  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  ಯದಿ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINEAR);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ರಿಕ್ತ);
  ಯದಿ (cclauses)
    {
      omp_split_clauses (loc, OMP_FOR, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
    }

  block = c_begin_compound_stmt (ಸತ್ಯ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
  add_stmt (block);

  ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ವೃಕ್ಷ c_parser_omp_taskloop (location_t, c_parser *, ವರ್ಣ *,
				   omp_clause_mask, ವೃಕ್ಷ *, ತಾರ್ಕಿಕ *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_master (location_t loc, c_parser *parser,
		     ವರ್ಣ *p_name, omp_clause_mask mask, ವೃಕ್ಷ *cclauses,
		     ತಾರ್ಕಿಕ *if_p, location_t master_loc)
{
  ವೃಕ್ಷ block, clauses, ret;
  gcc_rich_location richloc (loc);
  ಯದಿ (master_loc != UNKNOWN_LOCATION)
    richloc.add_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  strcat (p_name, " master");

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);

      ಯದಿ (strcmp (p, "taskloop") == 0)
	{
	  ವೃಕ್ಷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ಎಣಿಕೆ];
	  ಯದಿ (cclauses == ರಿಕ್ತ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	    ಪ್ರತ್ಯಾಗಮ c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (ಸತ್ಯ);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
	  ಯದಿ (ret == NULL_ವೃಕ್ಷ)
	    ಪ್ರತ್ಯಾಗಮ ret;
	  ret = c_finish_omp_master (loc, block);
	  OMP_MASTER_COMBINED (ret) = 1;
	  ಪ್ರತ್ಯಾಗಮ ret;
	}
    }
  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  ಯದಿ (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, mask, p_name, ಅಸತ್ಯ);
      omp_split_clauses (loc, OMP_MASTER, mask, clauses, cclauses);
    }
  ಅನ್ಯಥಾ
    c_parser_skip_to_pragma_eol (parser);

  ಪ್ರತ್ಯಾಗಮ c_finish_omp_master (loc, c_parser_omp_structured_block (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#define OMP_MASKED_CLAUSE_MASK					\
	(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FILTER)

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_masked (location_t loc, c_parser *parser,
		     ವರ್ಣ *p_name, omp_clause_mask mask, ವೃಕ್ಷ *cclauses,
		     ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ block, clauses, ret;

  strcat (p_name, " masked");
  mask |= OMP_MASKED_CLAUSE_MASK;

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);

      ಯದಿ (strcmp (p, "taskloop") == 0)
	{
	  ವೃಕ್ಷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ಎಣಿಕೆ];
	  ಯದಿ (cclauses == ರಿಕ್ತ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	    ಪ್ರತ್ಯಾಗಮ c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (ಸತ್ಯ);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
	  ಯದಿ (ret == NULL_ವೃಕ್ಷ)
	    ಪ್ರತ್ಯಾಗಮ ret;
	  ret = c_finish_omp_masked (loc, block,
				     cclauses[C_OMP_CLAUSE_SPLIT_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  ಪ್ರತ್ಯಾಗಮ ret;
	}
    }
  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ರಿಕ್ತ);
  ಯದಿ (cclauses)
    {
      omp_split_clauses (loc, OMP_MASKED, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_MASKED];
    }

  ಪ್ರತ್ಯಾಗಮ c_finish_omp_masked (loc, c_parser_omp_structured_block (parser,
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_interop (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  ವೃಕ್ಷ clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_MASK,
					   "#pragma omp interop");
  ವೃಕ್ಷ stmt = make_ಗಂಟು (OMP_INTEROP);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
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

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_omp_ordered (c_parser *parser, ಗಣನಾ pragma_context context,
		      ತಾರ್ಕಿಕ *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  ಯದಿ (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  ಪೂರ್ಣಾಙ್ಕ n = 1;
  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
    n = 2;

  ಯದಿ (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      ಧ್ರುವ ವರ್ಣ *p
	= IDENTIFIER_POINTER (c_parser_peek_nth_token (parser, n)->ಮೌಲ್ಯ);

      ಯದಿ (!strcmp ("depend", p) || !strcmp ("doacross", p))
	{
	  ಯದಿ (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    }
	  ಯದಿ (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	    }

	  ವೃಕ್ಷ clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_MASK,
					"#pragma omp ordered");
	  c_finish_omp_ordered (loc, clauses, NULL_ವೃಕ್ಷ);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
    }

  ವೃಕ್ಷ clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_MASK,
					   "#pragma omp ordered");

  ಯದಿ (!flag_openmp	/* flag_openmp_simd  */
      && omp_find_clause (clauses, OMP_CLAUSE_SIMD) == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  c_finish_omp_ordered (loc, clauses,
			c_parser_omp_structured_block (parser, if_p));
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  ವೃಕ್ಷ stmt, substmt;
  ತಾರ್ಕಿಕ error_suppress = ಅಸತ್ಯ;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  ಯದಿ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = ಅಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  stmt = ತಳ್ಳು_stmt_list ();

  ಯದಿ (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_scan (parser, "section", ಸತ್ಯ))
    {
      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_ಗಂಟು, substmt);
      SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (substmt, loc);
      add_stmt (substmt);
    }

  ಯಾವತ್ (1)
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	ಭಙ್ಗ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_EOF))
	ಭಙ್ಗ;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_scan (parser, "section", ಅಸತ್ಯ);
      ಯದಿ (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser);
	  error_suppress = ಅಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = ಸತ್ಯ;
	}

      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_ಗಂಟು, substmt);
      SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (substmt, loc);
      add_stmt (substmt);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = ತೆಗೆ_stmt_list (stmt);

  stmt = make_ಗಂಟು (OMP_SECTIONS);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, sections_loc);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OMP_SECTIONS_BODY (stmt) = substmt;

  ಪ್ರತ್ಯಾಗಮ add_stmt (stmt);
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_sections (location_t loc, c_parser *parser,
		       ವರ್ಣ *p_name, omp_clause_mask mask, ವೃಕ್ಷ *cclauses)
{
  ವೃಕ್ಷ block, clauses, ret;

  strcat (p_name, " sections");
  mask |= OMP_SECTIONS_CLAUSE_MASK;
  ಯದಿ (cclauses)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ರಿಕ್ತ);
  ಯದಿ (cclauses)
    {
      omp_split_clauses (loc, OMP_SECTIONS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SECTIONS];
    }

  block = c_begin_compound_stmt (ಸತ್ಯ);
  ret = c_parser_omp_sections_scope (loc, parser);
  ಯದಿ (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
  add_stmt (block);

  ಪ್ರತ್ಯಾಗಮ ret;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ಅಂಕೆ_THREADS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       ವರ್ಣ *p_name, omp_clause_mask mask, ವೃಕ್ಷ *cclauses,
		       ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ stmt, clauses, block;

  strcat (p_name, " parallel");
  mask |= OMP_PARALLEL_CLAUSE_MASK;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  ಯದಿ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_FOR))
    {
      ವೃಕ್ಷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ಎಣಿಕೆ];
      ಯದಿ (cclauses == ರಿಕ್ತ)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	ಪ್ರತ್ಯಾಗಮ c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      block = c_begin_omp_parallel ();
      ವೃಕ್ಷ ret = c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      stmt
	= c_finish_omp_parallel (loc, cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				 block);
      ಯದಿ (ret == NULL_ವೃಕ್ಷ)
	ಪ್ರತ್ಯಾಗಮ ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      ಪ್ರತ್ಯಾಗಮ stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  ಅನ್ಯಥಾ ಯದಿ (cclauses
	   && (mask & (OMP_CLAUSE_MASK_1
		       << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_to_pragma_eol (parser);
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      location_t ploc = c_parser_peek_token (parser)->location;
      ಯದಿ (cclauses == ರಿಕ್ತ && strcmp (p, "masked") == 0)
	{
	  ವೃಕ್ಷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ಎಣಿಕೆ];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	    ಪ್ರತ್ಯಾಗಮ c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					if_p);
	  block = c_begin_omp_parallel ();
	  ವೃಕ್ಷ ret = c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					  if_p);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  ಯದಿ (ret == ರಿಕ್ತ)
	    ಪ್ರತ್ಯಾಗಮ ret;
	  /* masked does have just filter clause, but during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel masked don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel masked
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel masked taskloop simd lastprivate (x)  */
	  ಯದಿ (OMP_MASKED_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  ಪ್ರತ್ಯಾಗಮ stmt;
	}
      ಅನ್ಯಥಾ ಯದಿ (cclauses == ರಿಕ್ತ && strcmp (p, "master") == 0)
	{
	  ವೃಕ್ಷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ಎಣಿಕೆ];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	    ಪ್ರತ್ಯಾಗಮ c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					if_p, ploc);
	  block = c_begin_omp_parallel ();
	  ವೃಕ್ಷ ret = c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					  if_p, ploc);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  ಯದಿ (ret == ರಿಕ್ತ)
	    ಪ್ರತ್ಯಾಗಮ ret;
	  /* master doesn't have any clauses and during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel master don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel master
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel master taskloop simd lastprivate (x)  */
	  ಯದಿ (OMP_MASTER_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  ಪ್ರತ್ಯಾಗಮ stmt;
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "loop") == 0)
	{
	  ವೃಕ್ಷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ಎಣಿಕೆ];
	  ಯದಿ (cclauses == ರಿಕ್ತ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	    ಪ್ರತ್ಯಾಗಮ c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  ವೃಕ್ಷ ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
					if_p);
	  stmt
	    = c_finish_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				     block);
	  ಯದಿ (ret == NULL_ವೃಕ್ಷ)
	    ಪ್ರತ್ಯಾಗಮ ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  ಪ್ರತ್ಯಾಗಮ stmt;
	}
      ಅನ್ಯಥಾ ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
	}
      ಅನ್ಯಥಾ ಯದಿ (cclauses == ರಿಕ್ತ && strcmp (p, "sections") == 0)
	{
	  ವೃಕ್ಷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ಎಣಿಕೆ];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  block = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, mask, cclauses);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  ಪ್ರತ್ಯಾಗಮ stmt;
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ರಿಕ್ತ);
  ಯದಿ (cclauses)
    {
      omp_split_clauses (loc, OMP_PARALLEL, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL];
    }

  block = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = ಸತ್ಯ;
  c_parser_statement (parser, if_p);
  stmt = c_finish_omp_parallel (loc, clauses, block);

  ಪ್ರತ್ಯಾಗಮ stmt;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_single (location_t loc, c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ stmt = make_ಗಂಟು (OMP_SINGLE);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_MASK,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  ಪ್ರತ್ಯಾಗಮ add_stmt (stmt);
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_scope (location_t loc, c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ stmt = make_ಗಂಟು (OMP_SCOPE);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_MASK,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  ಪ್ರತ್ಯಾಗಮ add_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_dispatch_body (c_parser *parser)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ lhs, rhs, ret;
  location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_expression (parser, ರಿಕ್ತ, ರಿಕ್ತ);
  ಯದಿ (ವೃಕ್ಷ_CODE (lhs.ಮೌಲ್ಯ) == CALL_ಅಭಿವ್ಯಕ್ತಿ)
    ಪ್ರತ್ಯಾಗಮ lhs.ಮೌಲ್ಯ;

  location_t op_location = c_parser_peek_token (parser)->location;
  ಯದಿ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  /* Parse function name.  */
  ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
  c_parser_consume_token (parser);
  ಯದಿ (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  rhs.ಮೌಲ್ಯ = build_external_ref (ಅಭಿವ್ಯಕ್ತಿ_loc, id, ಸತ್ಯ, &rhs.original_type);
  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_expression_after_primary (
    parser, ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (rhs.ಮೌಲ್ಯ, ಅಭಿವ್ಯಕ್ತಿ_loc), rhs);
  ಯದಿ (ವೃಕ್ಷ_CODE (rhs.ಮೌಲ್ಯ) != CALL_ಅಭಿವ್ಯಕ್ತಿ)
    {
      error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (rhs.ಮೌಲ್ಯ, ಅಭಿವ್ಯಕ್ತಿ_loc),
		"expected target-function call");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  /* Build assignment. */
  rhs = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, rhs, ಸತ್ಯ, ಸತ್ಯ);
  ret.ಮೌಲ್ಯ
    = build_modify_ಅಭಿವ್ಯಕ್ತಿ (op_location, lhs.ಮೌಲ್ಯ, lhs.original_type, NOP_ಅಭಿವ್ಯಕ್ತಿ,
			 ಅಭಿವ್ಯಕ್ತಿ_loc, rhs.ಮೌಲ್ಯ, rhs.original_type);
  ret.m_decimal = 0;
  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  ret.original_code = MODIFY_ಅಭಿವ್ಯಕ್ತಿ;
  ret.original_type = ರಿಕ್ತ;
  ಪ್ರತ್ಯಾಗಮ ret.ಮೌಲ್ಯ;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  ವೃಕ್ಷ stmt = make_ಗಂಟು (OMP_DISPATCH);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_MASK,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  ವೃಕ್ಷ depend_clauses = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ *depend_clauses_ptr = &depend_clauses;
  ಪ್ರತಿ (ವೃಕ್ಷ c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  ಯದಿ (depend_clauses != NULL_ವೃಕ್ಷ)
    {
      ವೃಕ್ಷ stmt = make_ಗಂಟು (OMP_TASK);
      ವೃಕ್ಷ_TYPE (stmt) = void_ಗಂಟು;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_ವೃಕ್ಷ;
      SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
      add_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ dispatch_body = c_parser_omp_dispatch_body (parser);
  ಯದಿ (dispatch_body == error_mark_ಗಂಟು)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_to_end_of_block_or_statement (parser);
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (ವೃಕ್ಷ_CODE (dispatch_body) == CALL_ಅಭಿವ್ಯಕ್ತಿ
	      || ವೃಕ್ಷ_CODE (dispatch_body) == MODIFY_ಅಭಿವ್ಯಕ್ತಿ);
  ವೃಕ್ಷ *dispatch_call = ವೃಕ್ಷ_CODE (dispatch_body) == MODIFY_ಅಭಿವ್ಯಕ್ತಿ
			  ? &ವೃಕ್ಷ_OPERAND (dispatch_body, 1)
			  : &dispatch_body;
  ಯಾವತ್ (ವೃಕ್ಷ_CODE (*dispatch_call) == FLOAT_ಅಭಿವ್ಯಕ್ತಿ
	 || ವೃಕ್ಷ_CODE (*dispatch_call) == CONVERT_ಅಭಿವ್ಯಕ್ತಿ
	 || ವೃಕ್ಷ_CODE (*dispatch_call) == NOP_ಅಭಿವ್ಯಕ್ತಿ)
    dispatch_call = &ವೃಕ್ಷ_OPERAND (*dispatch_call, 0);
  *dispatch_call = build_call_ಅಭಿವ್ಯಕ್ತಿ_internal_loc (
    loc, IFN_GOMP_DISPATCH,
    ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (CALL_ಅಭಿವ್ಯಕ್ತಿ_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  ಪ್ರತ್ಯಾಗಮ add_stmt (stmt);
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_task (location_t loc, c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ clauses, block;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_MASK,
				      "#pragma omp task");

  block = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = ಸತ್ಯ;
  c_parser_statement (parser, if_p);
  ಪ್ರತ್ಯಾಗಮ c_finish_omp_task (loc, clauses, block);
}

/* OpenMP 3.0:
   # pragma omp taskwait new-line

   OpenMP 5.0:
   # pragma omp taskwait taskwait-clause[optseq] new-line
*/

#define OMP_TASKWAIT_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_taskwait (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  ವೃಕ್ಷ clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_MASK,
				"#pragma omp taskwait");

  ಯದಿ (clauses)
    {
      ವೃಕ್ಷ stmt = make_ಗಂಟು (OMP_TASK);
      ವೃಕ್ಷ_TYPE (stmt) = void_ಗಂಟು;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_ವೃಕ್ಷ;
      SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
      add_stmt (stmt);
    }
  ಅನ್ಯಥಾ
    c_finish_omp_taskwait (loc);
}

/* OpenMP 3.1:
   # pragma omp taskyield new-line
*/

ಸ್ಥಿರ ಶೂನ್ಯ
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_taskgroup (location_t loc, c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_MASK,
					   "#pragma omp taskgroup");

  ವೃಕ್ಷ body = c_parser_omp_structured_block (parser, if_p);
  ಪ್ರತ್ಯಾಗಮ c_finish_omp_taskgroup (loc, body, clauses);
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);
  ವೃಕ್ಷ clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_MASK,
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

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_omp_cancellation_point (c_parser *parser, ಗಣನಾ pragma_context context)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ clauses;
  ತಾರ್ಕಿಕ point_seen = ಅಸತ್ಯ;

  c_parser_consume_pragma (parser);
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  point_seen = ಸತ್ಯ;
	}
    }
  ಯದಿ (!point_seen)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_to_pragma_eol (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  ಯದಿ (context != pragma_compound)
    {
      ಯದಿ (context == pragma_stmt)
	error_at (loc,
		  "%<#pragma %s%> may only be used in compound statements",
		  "omp cancellation point");
      ಅನ್ಯಥಾ
	c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_POINT_CLAUSE_MASK,
				"#pragma omp cancellation point");

  c_finish_omp_cancellation_point (loc, clauses);
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 ವರ್ಣ *p_name, omp_clause_mask mask, ವೃಕ್ಷ *cclauses,
			 ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ clauses, block, ret;

  strcat (p_name, " distribute");
  mask |= OMP_DISTRIBUTE_CLAUSE_MASK;

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ತಾರ್ಕಿಕ simd = ಅಸತ್ಯ;
      ತಾರ್ಕಿಕ parallel = ಅಸತ್ಯ;

      ಯದಿ (strcmp (p, "simd") == 0)
	simd = ಸತ್ಯ;
      ಅನ್ಯಥಾ
	parallel = strcmp (p, "parallel") == 0;
      ಯದಿ (parallel || simd)
	{
	  ವೃಕ್ಷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ಎಣಿಕೆ];
	  ಯದಿ (cclauses == ರಿಕ್ತ)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      ಯದಿ (simd)
		ಪ್ರತ್ಯಾಗಮ c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
					  if_p);
	      ಅನ್ಯಥಾ
		ಪ್ರತ್ಯಾಗಮ c_parser_omp_parallel (loc, parser, p_name, mask,
					      cclauses, if_p);
	    }
	  block = c_begin_compound_stmt (ಸತ್ಯ);
	  ಯದಿ (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				     if_p);
	  ಅನ್ಯಥಾ
	    ret = c_parser_omp_parallel (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
	  ಯದಿ (ret == ರಿಕ್ತ)
	    ಪ್ರತ್ಯಾಗಮ ret;
	  ret = make_ಗಂಟು (OMP_DISTRIBUTE);
	  ವೃಕ್ಷ_TYPE (ret) = void_type_ಗಂಟು;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
	  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret, loc);
	  add_stmt (ret);
	  ಪ್ರತ್ಯಾಗಮ ret;
	}
    }
  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ರಿಕ್ತ);
  ಯದಿ (cclauses)
    {
      omp_split_clauses (loc, OMP_DISTRIBUTE, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
    }

  block = c_begin_compound_stmt (ಸತ್ಯ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, ರಿಕ್ತ,
			       if_p);
  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
  add_stmt (block);

  ಪ್ರತ್ಯಾಗಮ ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#define OMP_TEAMS_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ಅಂಕೆ_TEAMS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_THREAD_LIMIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_teams (location_t loc, c_parser *parser,
		    ವರ್ಣ *p_name, omp_clause_mask mask, ವೃಕ್ಷ *cclauses,
		    ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ clauses, block, ret;

  strcat (p_name, " teams");
  mask |= OMP_TEAMS_CLAUSE_MASK;

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "distribute") == 0)
	{
	  ವೃಕ್ಷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ಎಣಿಕೆ];
	  ಯದಿ (cclauses == ರಿಕ್ತ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	    ಪ್ರತ್ಯಾಗಮ c_parser_omp_distribute (loc, parser, p_name, mask,
					    cclauses, if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
	  ಯದಿ (ret == ರಿಕ್ತ)
	    ಪ್ರತ್ಯಾಗಮ ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_ಗಂಟು (OMP_TEAMS);
	  ವೃಕ್ಷ_TYPE (ret) = void_type_ಗಂಟು;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret, loc);
	  ಪ್ರತ್ಯಾಗಮ add_stmt (ret);
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "loop") == 0)
	{
	  ವೃಕ್ಷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ಎಣಿಕೆ];
	  ಯದಿ (cclauses == ರಿಕ್ತ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	    ಪ್ರತ್ಯಾಗಮ c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
	  ಯದಿ (ret == ರಿಕ್ತ)
	    ಪ್ರತ್ಯಾಗಮ ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_ಗಂಟು (OMP_TEAMS);
	  ವೃಕ್ಷ_TYPE (ret) = void_type_ಗಂಟು;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret, loc);
	  ಪ್ರತ್ಯಾಗಮ add_stmt (ret);
	}
    }
  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ರಿಕ್ತ);
  ಯದಿ (cclauses)
    {
      omp_split_clauses (loc, OMP_TEAMS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
    }

  ವೃಕ್ಷ stmt = make_ಗಂಟು (OMP_TEAMS);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_end_compound_stmt (loc, block, ಸತ್ಯ);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);

  ಪ್ರತ್ಯಾಗಮ add_stmt (stmt);
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_target_data (location_t loc, c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  ಯದಿ (flag_openmp)
    omp_requires_mask
      = (ಗಣನಾ omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  ವೃಕ್ಷ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_DATA_CLAUSE_MASK,
				"#pragma omp target data", ಅಸತ್ಯ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, ಅಸತ್ಯ);
  ಪೂರ್ಣಾಙ್ಕ map_seen = 0;
  ಪ್ರತಿ (ವೃಕ್ಷ *pc = &clauses; *pc;)
    {
      ಯದಿ (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	ವಿಕಲ್ಪ (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  ಪಕ್ಷ GOMP_MAP_TO:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_TO:
	  ಪಕ್ಷ GOMP_MAP_PRESENT_TO:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_PRESENT_TO:
	  ಪಕ್ಷ GOMP_MAP_FROM:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_FROM:
	  ಪಕ್ಷ GOMP_MAP_PRESENT_FROM:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_PRESENT_FROM:
	  ಪಕ್ಷ GOMP_MAP_TOFROM:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_TOFROM:
	  ಪಕ್ಷ GOMP_MAP_PRESENT_TOFROM:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  ಪಕ್ಷ GOMP_MAP_ALLOC:
	  ಪಕ್ಷ GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    ಭಙ್ಗ;
	  ಪಕ್ಷ GOMP_MAP_FIRSTPRIVATE_POINTER:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_POINTER:
	  ಪಕ್ಷ GOMP_MAP_ATTACH_DETACH:
	  ಪಕ್ಷ GOMP_MAP_ATTACH:
	    ಭಙ್ಗ;
	  ಸ್ವಭಾವ:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ಅನುವರ್ತ;
	  }
      ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_seen = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  ಯದಿ (map_seen != 3)
    {
      ಯದಿ (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  ವೃಕ್ಷ stmt = make_ಗಂಟು (OMP_TARGET_DATA);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OMP_TARGET_DATA_CLAUSES (stmt) = clauses;
  keep_next_level ();
  ವೃಕ್ಷ block = c_begin_compound_stmt (ಸತ್ಯ);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TARGET_DATA_BODY (stmt) = c_end_compound_stmt (loc, block, ಸತ್ಯ);

  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
  ಪ್ರತ್ಯಾಗಮ add_stmt (stmt);
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

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_omp_target_update (location_t loc, c_parser *parser,
			    ಗಣನಾ pragma_context context)
{
  ಯದಿ (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }

  ವೃಕ್ಷ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_UPDATE_CLAUSE_MASK,
				"#pragma omp target update",
				/* finish_p = */ ಅಸತ್ಯ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  ಯದಿ (omp_find_clause (clauses, OMP_CLAUSE_TO) == NULL_ವೃಕ್ಷ
      && omp_find_clause (clauses, OMP_CLAUSE_FROM) == NULL_ವೃಕ್ಷ)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  ಯದಿ (flag_openmp)
    omp_requires_mask
      = (ಗಣನಾ omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  ವೃಕ್ಷ stmt = make_ಗಂಟು (OMP_TARGET_UPDATE);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OMP_TARGET_UPDATE_CLAUSES (stmt) = clauses;
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
  add_stmt (stmt);
  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* OpenMP 4.5:
   # pragma omp target enter data target-data-clause[optseq] new-line  */

#define OMP_TARGET_ENTER_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_omp_target_enter_data (location_t loc, c_parser *parser,
				ಗಣನಾ pragma_context context)
{
  ತಾರ್ಕಿಕ data_seen = ಅಸತ್ಯ;
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = ಸತ್ಯ;
	}
    }
  ಯದಿ (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  ಯದಿ (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }

  ಯದಿ (flag_openmp)
    omp_requires_mask
      = (ಗಣನಾ omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  ವೃಕ್ಷ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_ENTER_DATA_CLAUSE_MASK,
				"#pragma omp target enter data", ಅಸತ್ಯ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, ಅಸತ್ಯ);
  ಪೂರ್ಣಾಙ್ಕ map_seen = 0;
  ಪ್ರತಿ (ವೃಕ್ಷ *pc = &clauses; *pc;)
    {
      ಯದಿ (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	ವಿಕಲ್ಪ (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  ಪಕ್ಷ GOMP_MAP_TO:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_TO:
	  ಪಕ್ಷ GOMP_MAP_PRESENT_TO:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_PRESENT_TO:
	  ಪಕ್ಷ GOMP_MAP_ALLOC:
	  ಪಕ್ಷ GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    ಭಙ್ಗ;
	  ಪಕ್ಷ GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_TO);
	    map_seen = 3;
	    ಭಙ್ಗ;
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_TO);
	    map_seen = 3;
	    ಭಙ್ಗ;
	  ಪಕ್ಷ GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_TO);
	    map_seen = 3;
	    ಭಙ್ಗ;
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_TO);
	    map_seen = 3;
	    ಭಙ್ಗ;
	  ಪಕ್ಷ GOMP_MAP_FIRSTPRIVATE_POINTER:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_POINTER:
	  ಪಕ್ಷ GOMP_MAP_ATTACH_DETACH:
	  ಪಕ್ಷ GOMP_MAP_ATTACH:
	    ಭಙ್ಗ;
	  ಸ್ವಭಾವ:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ಅನುವರ್ತ;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  ಯದಿ (map_seen != 3)
    {
      ಯದಿ (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }

  ವೃಕ್ಷ stmt = make_ಗಂಟು (OMP_TARGET_ENTER_DATA);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OMP_TARGET_ENTER_DATA_CLAUSES (stmt) = clauses;
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
  add_stmt (stmt);
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* OpenMP 4.5:
   # pragma omp target exit data target-data-clause[optseq] new-line  */

#define OMP_TARGET_EXIT_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_omp_target_exit_data (location_t loc, c_parser *parser,
			       ಗಣನಾ pragma_context context)
{
  ತಾರ್ಕಿಕ data_seen = ಅಸತ್ಯ;
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = ಸತ್ಯ;
	}
    }
  ಯದಿ (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  ಯದಿ (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }

  ಯದಿ (flag_openmp)
    omp_requires_mask
      = (ಗಣನಾ omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  ವೃಕ್ಷ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_EXIT_DATA_CLAUSE_MASK,
				"#pragma omp target exit data", ಅಸತ್ಯ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_DATA);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_EXIT_DATA);
  c_omp_adjust_map_clauses (clauses, ಅಸತ್ಯ);
  ಪೂರ್ಣಾಙ್ಕ map_seen = 0;
  ಪ್ರತಿ (ವೃಕ್ಷ *pc = &clauses; *pc;)
    {
      ಯದಿ (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	ವಿಕಲ್ಪ (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  ಪಕ್ಷ GOMP_MAP_FROM:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_FROM:
	  ಪಕ್ಷ GOMP_MAP_PRESENT_FROM:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_PRESENT_FROM:
	  ಪಕ್ಷ GOMP_MAP_RELEASE:
	  ಪಕ್ಷ GOMP_MAP_DELETE:
	    map_seen = 3;
	    ಭಙ್ಗ;
	  ಪಕ್ಷ GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_FROM);
	    map_seen = 3;
	    ಭಙ್ಗ;
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_seen = 3;
	    ಭಙ್ಗ;
	  ಪಕ್ಷ GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_FROM);
	    map_seen = 3;
	    ಭಙ್ಗ;
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_seen = 3;
	    ಭಙ್ಗ;
	  ಪಕ್ಷ GOMP_MAP_FIRSTPRIVATE_POINTER:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_POINTER:
	  ಪಕ್ಷ GOMP_MAP_ATTACH_DETACH:
	  ಪಕ್ಷ GOMP_MAP_DETACH:
	    ಭಙ್ಗ;
	  ಸ್ವಭಾವ:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target exit data%> with map-type other "
		      "than %<from%>, %<tofrom%>, %<release%> or %<delete%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ಅನುವರ್ತ;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  ಯದಿ (map_seen != 3)
    {
      ಯದಿ (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }

  ವೃಕ್ಷ stmt = make_ಗಂಟು (OMP_TARGET_EXIT_DATA);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OMP_TARGET_EXIT_DATA_CLAUSES (stmt) = clauses;
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
  add_stmt (stmt);
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
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

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_omp_target (c_parser *parser, ಗಣನಾ pragma_context context, ತಾರ್ಕಿಕ *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  ವೃಕ್ಷ *pc = ರಿಕ್ತ, stmt, block, body, clauses;

  ಯದಿ (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  ಯದಿ (flag_openmp)
    omp_requires_mask
      = (ಗಣನಾ omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಗಣನಾ ವೃಕ್ಷ_code ccode = ERROR_MARK;

      ಯದಿ (strcmp (p, "teams") == 0)
	ccode = OMP_TEAMS;
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "simd") == 0)
	ccode = OMP_SIMD;
      ಯದಿ (ccode != ERROR_MARK)
	{
	  ವೃಕ್ಷ cclauses[C_OMP_CLAUSE_SPLIT_ಎಣಿಕೆ];
	  ವರ್ಣ p_name[ಪರಿಮಾಣ ("#pragma omp target teams distribute "
			      "parallel for simd")];

	  c_parser_consume_token (parser);
	  strcpy (p_name, "#pragma omp target");
	  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      ವೃಕ್ಷ stmt;
	      ವಿಕಲ್ಪ (ccode)
		{
		ಪಕ್ಷ OMP_TEAMS:
		  stmt = c_parser_omp_teams (loc, parser, p_name,
					     OMP_TARGET_CLAUSE_MASK,
					     cclauses, if_p);
		  ಭಙ್ಗ;
		ಪಕ್ಷ OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_TARGET_CLAUSE_MASK,
						cclauses, if_p);
		  ಭಙ್ಗ;
		ಪಕ್ಷ OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_TARGET_CLAUSE_MASK,
					    cclauses, if_p);
		  ಭಙ್ಗ;
		ಸ್ವಭಾವ:
		  gcc_unreachable ();
		}
	      ಪ್ರತ್ಯಾಗಮ stmt != NULL_ವೃಕ್ಷ;
	    }
	  keep_next_level ();
	  ವೃಕ್ಷ block = c_begin_compound_stmt (ಸತ್ಯ), ret;
	  ವಿಕಲ್ಪ (ccode)
	    {
	    ಪಕ್ಷ OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_TARGET_CLAUSE_MASK, cclauses,
					if_p);
	      ಭಙ್ಗ;
	    ಪಕ್ಷ OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_TARGET_CLAUSE_MASK, cclauses,
					   if_p);
	      ಭಙ್ಗ;
	    ಪಕ್ಷ OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_TARGET_CLAUSE_MASK, cclauses,
				       if_p);
	      ಭಙ್ಗ;
	    ಸ್ವಭಾವ:
	      gcc_unreachable ();
	    }
	  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
	  ಯದಿ (ret == NULL_ವೃಕ್ಷ)
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	  ಯದಿ (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    ಪ್ರತಿ (ವೃಕ್ಷ c = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ಅಂಕೆ_TEAMS
		  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_THREAD_LIMIT)
		ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0;
		     i <= (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ಅಂಕೆ_TEAMS); ++i)
		  ಯದಿ (OMP_CLAUSE_OPERAND (c, i)
		      && ವೃಕ್ಷ_CODE (OMP_CLAUSE_OPERAND (c, i)) != INTEGER_CST)
		    {
		      ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = OMP_CLAUSE_OPERAND (c, i);
		      ವೃಕ್ಷ tmp = create_tmp_var_raw (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ));
		      ಅಭಿವ್ಯಕ್ತಿ = build4 (TARGET_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), tmp,
				     ಅಭಿವ್ಯಕ್ತಿ, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
		      add_stmt (ಅಭಿವ್ಯಕ್ತಿ);
		      OMP_CLAUSE_OPERAND (c, i) = ಅಭಿವ್ಯಕ್ತಿ;
		      ವೃಕ್ಷ tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
		      cclauses[C_OMP_CLAUSE_SPLIT_TARGET] = tc;
		    }
	  ವೃಕ್ಷ stmt = make_ಗಂಟು (OMP_TARGET);
	  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
	  OMP_TARGET_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
	  c_omp_adjust_map_clauses (OMP_TARGET_CLAUSES (stmt), ಸತ್ಯ);
	  OMP_TARGET_BODY (stmt) = block;
	  OMP_TARGET_COMBINED (stmt) = 1;
	  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
	  add_stmt (stmt);
	  pc = &OMP_TARGET_CLAUSES (stmt);
	  ಗಚ್ಛ check_clauses;
	}
      ಅನ್ಯಥಾ ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_target_data (loc, parser, if_p);
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  ಪ್ರತ್ಯಾಗಮ c_parser_omp_target_enter_data (loc, parser, context);
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  ಪ್ರತ್ಯಾಗಮ c_parser_omp_target_exit_data (loc, parser, context);
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  ಪ್ರತ್ಯಾಗಮ c_parser_omp_target_update (loc, parser, context);
	}
    }
  ಯದಿ (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  stmt = make_ಗಂಟು (OMP_TARGET);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;

  clauses = c_parser_omp_all_clauses (parser, OMP_TARGET_CLAUSE_MASK,
				      "#pragma omp target", ಅಸತ್ಯ);
  ಪ್ರತಿ (ವೃಕ್ಷ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
      {
	ವೃಕ್ಷ nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_SET_MAP_KIND (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_TARGET);
  clauses  = c_finish_omp_clauses (clauses, C_ORT_OMP_TARGET);
  c_omp_adjust_map_clauses (clauses, ಸತ್ಯ);

  keep_next_level ();
  block = c_begin_compound_stmt (ಸತ್ಯ);
  body = c_parser_omp_structured_block (parser, if_p);

  c_omp_scan_mapper_bindings (loc, &clauses, body);

  add_stmt (body);
  OMP_TARGET_CLAUSES (stmt) = clauses;
  pc = &OMP_TARGET_CLAUSES (stmt);
  OMP_TARGET_BODY (stmt) = c_end_compound_stmt (loc, block, ಸತ್ಯ);

  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
  add_stmt (stmt);

check_clauses:
  ಯಾವತ್ (*pc)
    {
      ಯದಿ (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	ವಿಕಲ್ಪ (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  ಪಕ್ಷ GOMP_MAP_TO:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_TO:
	  ಪಕ್ಷ GOMP_MAP_PRESENT_TO:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_PRESENT_TO:
	  ಪಕ್ಷ GOMP_MAP_FROM:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_FROM:
	  ಪಕ್ಷ GOMP_MAP_PRESENT_FROM:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_PRESENT_FROM:
	  ಪಕ್ಷ GOMP_MAP_TOFROM:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_TOFROM:
	  ಪಕ್ಷ GOMP_MAP_PRESENT_TOFROM:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  ಪಕ್ಷ GOMP_MAP_ALLOC:
	  ಪಕ್ಷ GOMP_MAP_PRESENT_ALLOC:
	  ಪಕ್ಷ GOMP_MAP_FIRSTPRIVATE_POINTER:
	  ಪಕ್ಷ GOMP_MAP_ALWAYS_POINTER:
	  ಪಕ್ಷ GOMP_MAP_POINTER:
	  ಪಕ್ಷ GOMP_MAP_ATTACH_DETACH:
	  ಪಕ್ಷ GOMP_MAP_ATTACH:
	    ಭಙ್ಗ;
	  ಸ್ವಭಾವ:
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ಅನುವರ್ತ;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }
  cfun->has_omp_target = ಸತ್ಯ;
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_declare_simd (c_parser *parser, ಗಣನಾ pragma_context context)
{
  c_token *token = c_parser_peek_token (parser);
  gcc_assert (token->type == CPP_NAME);
  ವೃಕ್ಷ kind = token->ಮೌಲ್ಯ;
  gcc_assert (strcmp (IDENTIFIER_POINTER (kind), "simd") == 0
	      || strcmp (IDENTIFIER_POINTER (kind), "variant") == 0);

  auto_vec<c_token> clauses;
  ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      ಯದಿ (token->type == CPP_EOF)
	{
	  c_parser_skip_to_pragma_eol (parser);
	  ಪ್ರತ್ಯಾಗಮ;
	}
      clauses.safe_ತಳ್ಳು (*token);
      c_parser_consume_token (parser);
    }
  clauses.safe_ತಳ್ಳು (*c_parser_peek_token (parser));
  c_parser_skip_to_pragma_eol (parser);

  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      ಯದಿ (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->ಮೌಲ್ಯ != kind)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_POINTER (kind), IDENTIFIER_POINTER (kind));
	  ಪ್ರತ್ಯಾಗಮ;
	}
      c_parser_consume_pragma (parser);
      ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  ಯದಿ (token->type == CPP_EOF)
	    {
	      c_parser_skip_to_pragma_eol (parser);
	      ಪ್ರತ್ಯಾಗಮ;
	    }
	  clauses.safe_ತಳ್ಳು (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_ತಳ್ಳು (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  memset (&eof_token, 0, ಪರಿಮಾಣ (eof_token));
  eof_token.type = CPP_EOF;
  clauses.safe_ತಳ್ಳು (eof_token);
  clauses.safe_ತಳ್ಳು (eof_token);

  ವಿಕಲ್ಪ (context)
    {
    ಪಕ್ಷ pragma_external:
      ಯದಿ (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  ಪೂರ್ಣಾಙ್ಕ ext = disable_extension_diagnostics ();
	  ಕುರು
	    c_parser_consume_token (parser);
	  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಅಸತ್ಯ, ಸತ್ಯ,
					 ಅಸತ್ಯ, ರಿಕ್ತ, &clauses);
	  restore_extension_diagnostics (ext);
	}
      ಅನ್ಯಥಾ
	c_parser_declaration_or_fndef (parser, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಅಸತ್ಯ, ಸತ್ಯ,
				       ಅಸತ್ಯ, ರಿಕ್ತ, &clauses);
      ಭಙ್ಗ;
    ಪಕ್ಷ pragma_struct:
    ಪಕ್ಷ pragma_param:
    ಪಕ್ಷ pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      ಭಙ್ಗ;
    ಪಕ್ಷ pragma_compound:
      ತಾರ್ಕಿಕ have_std_attrs;
      ವೃಕ್ಷ std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
      ಯದಿ (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      ಅನ್ಯಥಾ
	std_attrs = NULL_ವೃಕ್ಷ;
      ಯದಿ (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  ಪೂರ್ಣಾಙ್ಕ ext = disable_extension_diagnostics ();
	  ಕುರು
	    c_parser_consume_token (parser);
	  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  ಯದಿ (c_parser_next_tokens_start_declaration (parser)
	      || c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ,
					     ಸತ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      ಭಙ್ಗ;
	    }
	  restore_extension_diagnostics (ext);
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_tokens_start_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ,
					 ಅಸತ್ಯ, ರಿಕ್ತ, &clauses, have_std_attrs,
					 std_attrs);
	  ಭಙ್ಗ;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_context_selector (c_parser *parser, ಗಣನಾ omp_tss_code set,
			       ವೃಕ್ಷ parms)
{
  ವೃಕ್ಷ ret = NULL_ವೃಕ್ಷ;
  ಕುರು
    {
      ವೃಕ್ಷ selector;
      ಯದಿ (c_parser_next_token_is (parser, CPP_KEYWORD)
	  || c_parser_next_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      ಅನ್ಯಥಾ
	{
	  c_parser_error (parser, "expected trait selector name");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಗಣನಾ omp_ts_code sel
	= omp_lookup_ts_code (set, IDENTIFIER_POINTER (selector));

      ಯದಿ (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_POINTER (selector),  omp_tss_map[set]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ, ret);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_balanced_token_sequence (parser);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ಅನುವರ್ತ;
	    }
	  ಅನ್ಯಥಾ
	    ಭಙ್ಗ;
	}

      c_parser_consume_token (parser);

      ವೃಕ್ಷ properties = NULL_ವೃಕ್ಷ;
      ವೃಕ್ಷ scoreval = NULL_ವೃಕ್ಷ;
      ಗಣನಾ omp_tp_type property_kind = omp_ts_map[sel].tp_type;
      ತಾರ್ಕಿಕ allow_score = omp_ts_map[sel].allow_score;
      ವೃಕ್ಷ t;

      ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  ಯದಿ (property_kind == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_POINTER (selector));
	      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER (token->ಮೌಲ್ಯ), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      ವೃಕ್ಷ score = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ).ಮೌಲ್ಯ;
	      parens2.skip_until_found_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      ಯದಿ (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[set]);
	      ಅನ್ಯಥಾ ಯದಿ (score != error_mark_ಗಂಟು)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, ಅಸತ್ಯ, ರಿಕ್ತ);
		  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (score))
		      || ವೃಕ್ಷ_CODE (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  ಅನ್ಯಥಾ
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  ವಿಕಲ್ಪ (property_kind)
	    {
	    ಪಕ್ಷ OMP_TRAIT_PROPERTY_ID:
	      ಯದಿ (c_parser_next_token_is (parser, CPP_KEYWORD)
		  || c_parser_next_token_is (parser, CPP_NAME))
		{
		  ವೃಕ್ಷ prop = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_ವೃಕ್ಷ,
						    properties);
		}
	      ಅನ್ಯಥಾ
		{
		  c_parser_error (parser, "expected identifier");
		  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		}
	      ಭಙ್ಗ;
	    ಪಕ್ಷ OMP_TRAIT_PROPERTY_NAME_LIST:
	      ಕುರು
		{
		  ವೃಕ್ಷ prop = OMP_TP_NAMELIST_ಗಂಟು;
		  ವೃಕ್ಷ ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
		  ಯದಿ (c_parser_next_token_is (parser, CPP_KEYWORD)
		      || c_parser_next_token_is (parser, CPP_NAME))
		    {
		      ಮೌಲ್ಯ = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
		      c_parser_consume_token (parser);
		    }
		  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_STRING))
		    ಮೌಲ್ಯ = c_parser_string_literal (parser, ಅಸತ್ಯ,
						     ಅಸತ್ಯ).ಮೌಲ್ಯ;
		  ಅನ್ಯಥಾ
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		    }

		  properties = make_trait_property (prop, ಮೌಲ್ಯ, properties);

		  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  ಅನ್ಯಥಾ
		    ಭಙ್ಗ;
		}
	      ಯಾವತ್ (1);
	      ಭಙ್ಗ;
	    ಪಕ್ಷ OMP_TRAIT_PROPERTY_DEV_ಅಂಕೆ_ಅಭಿವ್ಯಕ್ತಿ:
	    ಪಕ್ಷ OMP_TRAIT_PROPERTY_BOOL_ಅಭಿವ್ಯಕ್ತಿ:
	      {
		c_ಅಭಿವ್ಯಕ್ತಿ texpr = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
		texpr = convert_lvalue_to_rvalue (token->location, texpr,
						  ಸತ್ಯ, ಸತ್ಯ);
		t = texpr.ಮೌಲ್ಯ;
	      }
	      ಯದಿ (t == error_mark_ಗಂಟು)
		ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	      mark_exp_read (t);
	      ಯದಿ (property_kind == OMP_TRAIT_PROPERTY_BOOL_ಅಭಿವ್ಯಕ್ತಿ)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_ಗಂಟು);
		  ಯದಿ (t == error_mark_ಗಂಟು)
		    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		}
	      ಅನ್ಯಥಾ ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		}
	      t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);
	      properties = make_trait_property (NULL_ವೃಕ್ಷ, t, properties);
	      ಭಙ್ಗ;
	    ಪಕ್ಷ OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      ಯದಿ (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  ಯದಿ (parms == NULL_ವೃಕ್ಷ)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		    }
		  ವೃಕ್ಷ c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_MASK,
						"simd", ಸತ್ಯ, 2);
		  c = c_omp_declare_simd_clauses_to_numbers (parms
							     == error_mark_ಗಂಟು
							     ? NULL_ವೃಕ್ಷ : parms,
							     c);
		  properties = c;
		}
	      ಅನ್ಯಥಾ ಯದಿ (sel == OMP_TRAIT_IMPLEMENTATION_REQUIRES)
		{
		  /* FIXME: The "requires" selector was added in OpenMP 5.1.
		     Currently only the now-deprecated syntax
		     from OpenMP 5.0 is supported.  */
		  sorry_at (token->location,
			    "%<requires%> selector is not supported yet");
		  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		}
	      ಅನ್ಯಥಾ
		gcc_unreachable ();
	      ಭಙ್ಗ;
	    ಸ್ವಭಾವ:
	      gcc_unreachable ();
	    }

	  parens.skip_until_found_close (parser);
	  properties = nreverse (properties);
	}
      ಅನ್ಯಥಾ ಯದಿ (property_kind != OMP_TRAIT_PROPERTY_NONE
	       && property_kind != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_kind != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
    }
  ಯಾವತ್ (1);

  ಪ್ರತ್ಯಾಗಮ nreverse (ret);
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_context_selector_specification (c_parser *parser, ವೃಕ್ಷ parms)
{
  ವೃಕ್ಷ ret = NULL_ವೃಕ್ಷ;
  ಕುರು
    {
      ಧ್ರುವ ವರ್ಣ *setp = "";
      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಗಣನಾ omp_tss_code set = omp_lookup_tss_code (setp);

      ಯದಿ (set == OMP_TRAIT_SET_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}

      c_parser_consume_token (parser);

      ಯದಿ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

      matching_braces braces;
      ಯದಿ (!braces.require_open (parser))
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

      ವೃಕ್ಷ selectors = c_parser_omp_context_selector (parser, set, parms);
      ಯದಿ (selectors == error_mark_ಗಂಟು)
	{
	  c_parser_skip_to_closing_brace (parser);
	  ret = error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (ret != error_mark_ಗಂಟು)
	ret = make_trait_set_selector (set, selectors, ret);

      braces.require_close (parser);

      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
    }
  ಯಾವತ್ (1);

  ಯದಿ (ret == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ ret;
  ಪ್ರತ್ಯಾಗಮ nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_finish_omp_declare_variant (c_parser *parser, ವೃಕ್ಷ fndecl, ವೃಕ್ಷ parms)
{
  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    {
     fail:
      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      ಗಚ್ಛ fail;
    }

  c_token *token = c_parser_peek_token (parser);
  ವೃಕ್ಷ variant = lookup_name (token->ಮೌಲ್ಯ);

  ಯದಿ (variant == NULL_ವೃಕ್ಷ)
    {
      undeclared_variable (token->location, token->ಮೌಲ್ಯ);
      variant = error_mark_ಗಂಟು;
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_ಗಂಟು;
    }
  ಅನ್ಯಥಾ ಯದಿ (fndecl_built_in_p (variant)
	   && (strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			"__builtin_", strlen ("__builtin_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__sync_", strlen ("__sync_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__atomic_", strlen ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_ಗಂಟು;
    }
  ಅನ್ಯಥಾ ಯದಿ (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_ಗಂಟು;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  ವೃಕ್ಷ append_args_ವೃಕ್ಷ = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ append_args_last;
  vec<ವೃಕ್ಷ> adjust_args_list = vNULL;
  ತಾರ್ಕಿಕ has_match = ಅಸತ್ಯ, has_adjust_args = ಅಸತ್ಯ;
  location_t adjust_args_loc = UNKNOWN_LOCATION;
  location_t append_args_loc = UNKNOWN_LOCATION;
  location_t match_loc = UNKNOWN_LOCATION;
  ವೃಕ್ಷ need_device_ptr_list = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ ctx = error_mark_ಗಂಟು;

  ಕುರು
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ಧ್ರುವ ವರ್ಣ *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);

      ಗಣನಾ clause
      {
	match,
	adjust_args,
	append_args
      } ccode;

      ಯದಿ (strcmp (clause, "match") == 0)
	{
	  ccode = match;
	  match_loc = loc;
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp (clause, "adjust_args") == 0)
	{
	  ccode = adjust_args;
	  adjust_args_loc = loc;
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp (clause, "append_args") == 0)
	{
	  ccode = append_args;
	  append_args_loc = loc;
	}
      ಅನ್ಯಥಾ
	{
	  c_parser_error (parser, "expected %<match%>, %<adjust_args%> or "
				  "%<append_args%> clause");
	  ಗಚ್ಛ fail;
	}

      c_parser_consume_token (parser);

      ಯದಿ (!parens.require_open (parser))
	ಗಚ್ಛ fail;

      ಯದಿ (parms == NULL_ವೃಕ್ಷ)
	parms = error_mark_ಗಂಟು;

      ಯದಿ (ccode == match)
	{
	  ಯದಿ (has_match)
	    error_at (match_loc, "too many %<match%> clauses");
	  has_match = ಸತ್ಯ;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  ಯದಿ (ctx == error_mark_ಗಂಟು)
	    ಗಚ್ಛ fail;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  ಯದಿ (ctx != error_mark_ಗಂಟು
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      ವೃಕ್ಷ outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (ccode == adjust_args)
	{
	  has_adjust_args = ಸತ್ಯ;
	  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      ಧ್ರುವ ವರ್ಣ *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	      ಯದಿ (strcmp (p, "need_device_ptr") == 0
		  || strcmp (p, "nothing") == 0)
		{
		  c_parser_consume_token (parser); // need_device_ptr
		  c_parser_consume_token (parser); // :

		  loc = c_parser_peek_token (parser)->location;
		  ವೃಕ್ಷ list
		    = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ERROR,
						  NULL_ವೃಕ್ಷ);

		  ವೃಕ್ಷ arg;
		  ಯದಿ (variant != error_mark_ಗಂಟು)
		    ಪ್ರತಿ (ವೃಕ್ಷ c = list; c != NULL_ವೃಕ್ಷ; c = ವೃಕ್ಷ_CHAIN (c))
		      {
			ವೃಕ್ಷ decl = ವೃಕ್ಷ_PURPOSE (c);
			location_t arg_loc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ವೃಕ್ಷ_ಮೌಲ್ಯ (c));
			ಪೂರ್ಣಾಙ್ಕ idx;
			ಪ್ರತಿ (arg = parms, idx = 0; arg != ರಿಕ್ತ;
			     arg = ವೃಕ್ಷ_CHAIN (arg), idx++)
			  ಯದಿ (arg == decl)
			    ಭಙ್ಗ;
			ಯದಿ (arg == NULL_ವೃಕ್ಷ)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    ಗಚ್ಛ fail;
			  }
			ಯದಿ (adjust_args_list.contains (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    ಗಚ್ಛ fail;
			  }
			ಯದಿ (strcmp (p, "need_device_ptr") == 0
			    && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (arg)) != POINTER_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    ಗಚ್ಛ fail;
			  }
			adjust_args_list.safe_ತಳ್ಳು (arg);
			ಯದಿ (strcmp (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_ವೃಕ್ಷ_list (
				NULL_ವೃಕ್ಷ,
				build_int_cst (
				  integer_type_ಗಂಟು,
				  idx))); // Store 0-based argument index,
					  // as in gimplify_call_expr
			  }
		      }
		}
	      ಅನ್ಯಥಾ
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %<nothing%> or %<need_device_ptr%>");
		  ಯದಿ (strcmp (p, "need_device_addr") == 0)
		    inform (c_parser_peek_token (parser)->location,
			    "%<need_device_addr%> is not valid for C");
		  ಗಚ್ಛ fail;
		}
	    }
	  ಅನ್ಯಥಾ
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected %<nothing%> or %<need_device_ptr%> "
			"followed by %<:%>");
	      ಗಚ್ಛ fail;
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (ccode == append_args)
	{
	  ಯದಿ (append_args_ವೃಕ್ಷ)
	    {
	      error_at (append_args_loc, "too many %qs clauses", "append_args");
	      append_args_ವೃಕ್ಷ = NULL_ವೃಕ್ಷ;
	    }
	  ಕುರು
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME)
		  || strcmp ("interop",
			     IDENTIFIER_POINTER (
			       c_parser_peek_token (parser)->ಮೌಲ್ಯ)))
		{
		  error_at (loc, "expected %<interop%>");
		  ಗಚ್ಛ fail;
		}
	      c_parser_consume_token (parser);

	      ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		ಗಚ್ಛ fail;
	      ತಾರ್ಕಿಕ target = ಅಸತ್ಯ;
	      ತಾರ್ಕಿಕ targetsync = ಅಸತ್ಯ;
	      ವೃಕ್ಷ prefer_type_ವೃಕ್ಷ = NULL_ವೃಕ್ಷ;
	      ಯದಿ (!c_parser_omp_clause_init_modifiers (parser, &target,
						       &targetsync,
						       &prefer_type_ವೃಕ್ಷ)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		ಗಚ್ಛ fail;
	      ಯದಿ (!target && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      ವೃಕ್ಷ t = build_ವೃಕ್ಷ_list (target ? boolean_true_ಗಂಟು
					       : boolean_false_ಗಂಟು,
					targetsync ? boolean_true_ಗಂಟು
						   : boolean_false_ಗಂಟು);
	      t = build1_loc (loc, NOP_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, t);
	      t = build_ವೃಕ್ಷ_list (t, prefer_type_ವೃಕ್ಷ);
	      ಯದಿ (append_args_ವೃಕ್ಷ)
		{
		  ವೃಕ್ಷ_CHAIN (append_args_last) = t;
		  append_args_last = t;
		}
	      ಅನ್ಯಥಾ
		append_args_ವೃಕ್ಷ = append_args_last = t;
	      ಯದಿ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		ಭಙ್ಗ;
	      ಯದಿ (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		ಗಚ್ಛ fail;
	    }
	  ಯಾವತ್ (ಸತ್ಯ);
	}

      parens.require_close (parser);
  } ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL));
  ಯದಿ (variant != error_mark_ಗಂಟು && !has_match)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_ಗಂಟು;
    }
  c_parser_skip_to_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  ಯದಿ (variant == error_mark_ಗಂಟು || ctx == error_mark_ಗಂಟು)
    /* Previously diagnosed error.  */
    ಪ್ರತ್ಯಾಗಮ;

  ಯದಿ ((has_adjust_args || append_args_ವೃಕ್ಷ)
      && !omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_args ? adjust_args_loc : append_args_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_args ? "adjust_args" : "append_args");
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (!omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      ವೃಕ್ಷ base_type = ವೃಕ್ಷ_TYPE (fndecl);
      ವೃಕ್ಷ variant_type = ವೃಕ್ಷ_TYPE (variant);
      ತಾರ್ಕಿಕ unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_ವೃಕ್ಷ
	   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type));

      ಯದಿ (append_args_ವೃಕ್ಷ
	  && TYPE_ARG_TYPES (base_type) == NULL_ವೃಕ್ಷ
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
	  ಪ್ರತ್ಯಾಗಮ;
	}
      ಅನ್ಯಥಾ ಯದಿ (append_args_ವೃಕ್ಷ)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  ಪೂರ್ಣಾಙ್ಕ nappend_args = 0;
	  ಪೂರ್ಣಾಙ್ಕ nbase_args = 0;
	  ಪ್ರತಿ (ವೃಕ್ಷ t = TYPE_ARG_TYPES (base_type);
	       t && ವೃಕ್ಷ_ಮೌಲ್ಯ (t) != void_type_ಗಂಟು; t = ವೃಕ್ಷ_CHAIN (t))
	    nbase_args++;
	  ಪ್ರತಿ (ವೃಕ್ಷ t = append_args_ವೃಕ್ಷ; t; t = ವೃಕ್ಷ_CHAIN (t))
	    nappend_args++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_args_ವೃಕ್ಷ = build_ವೃಕ್ಷ_list (build_int_cst (integer_type_ಗಂಟು,
							     nbase_args),
					      append_args_ವೃಕ್ಷ);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  ಯದಿ (!unprototyped_variant)
	    {
	      ವೃಕ್ಷ args = TYPE_ARG_TYPES (variant_type);
	      ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; args && i < nbase_args;
		   i++, args = ವೃಕ್ಷ_CHAIN (args))
		;
	      ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nappend_args; i++, args = ವೃಕ್ಷ_CHAIN (args))
		ಯದಿ (!args || !c_omp_interop_t_p (ವೃಕ್ಷ_ಮೌಲ್ಯ (args)))
		  {
		    error_at (DECL_SOURCE_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_args + i + 1, variant);
		    inform (append_args_loc,
			    "%<append_args%> specified here");
		    ಪ್ರತ್ಯಾಗಮ;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  ವೃಕ್ಷ args = TYPE_ARG_TYPES (base_type);
	  ವೃಕ್ಷ newargs = NULL_ವೃಕ್ಷ;
	  ವೃಕ್ಷ lastarg = NULL_ವೃಕ್ಷ;
	  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < nbase_args; j++, args = ವೃಕ್ಷ_CHAIN (args))
	    {
	      ವೃಕ್ಷ t = ವೃಕ್ಷ_cons (ವೃಕ್ಷ_PURPOSE (args),
				  ವೃಕ್ಷ_ಮೌಲ್ಯ (args), NULL_ವೃಕ್ಷ);
	      ಯದಿ (lastarg)
		ವೃಕ್ಷ_CHAIN (lastarg) = t;
	      ಅನ್ಯಥಾ
		newargs = t;
	      lastarg = t;
	    }
	  ವೃಕ್ಷ type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? ವೃಕ್ಷ_TYPE (type) : pointer_sized_int_ಗಂಟು;
	  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < nappend_args; j++)
	    {
	      ವೃಕ್ಷ t = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, type, NULL_ವೃಕ್ಷ);
	      ಯದಿ (lastarg)
		ವೃಕ್ಷ_CHAIN (lastarg) = t;
	      ಅನ್ಯಥಾ
		newargs = t;
	      lastarg = t;
	    }
	  ವೃಕ್ಷ_CHAIN (lastarg) = args;

	  /* Temporarily stuff newargs into the original base_type.  */
	  ವೃಕ್ಷ saveargs = TYPE_ARG_TYPES (base_type);
	  TYPE_ARG_TYPES (base_type) = newargs;
	  ತಾರ್ಕಿಕ fail = !comptypes (base_type, variant_type);
	  TYPE_ARG_TYPES (base_type) = saveargs;

	  ಯದಿ (fail)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      ಪ್ರತ್ಯಾಗಮ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (unprototyped_variant)
	    /* If we've got an unprototyped variant, copy the transformed
	       base arg types to the variant.  This is needed later by
	       modify_call_for_omp_dispatch.  */
	    TYPE_ARG_TYPES (variant_type) = newargs;
	}
      ಅನ್ಯಥಾ  /* No append_args present.  */
	{
	  ಯದಿ (!comptypes (base_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      ಪ್ರತ್ಯಾಗಮ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (TYPE_ARG_TYPES (variant_type) == NULL_ವೃಕ್ಷ
		   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (base_type) != NULL_ವೃಕ್ಷ)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (base_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_USED (variant) = 1;
  ವೃಕ್ಷ construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (match_loc, variant, construct);
  ಯದಿ (omp_context_selector_matches (ctx, NULL_ವೃಕ್ಷ, ಅಸತ್ಯ))
    {
      ವೃಕ್ಷ attr = ವೃಕ್ಷ_cons (get_identifier ("omp declare variant base"),
			     build_ವೃಕ್ಷ_list (variant, ctx),
			     DECL_ATTRIBUTES (fndecl));
      DECL_ATTRIBUTES (fndecl) = attr;
    }

  ಯದಿ (need_device_ptr_list || append_args_ವೃಕ್ಷ)
    {
      ವೃಕ್ಷ variant_decl = ವೃಕ್ಷ_strip_nop_conversions (variant);
      ವೃಕ್ಷ t = build_ವೃಕ್ಷ_list (need_device_ptr_list,
				NULL_ವೃಕ್ಷ /* need_device_addr */);
      ವೃಕ್ಷ_CHAIN (t) = append_args_ವೃಕ್ಷ;
      DECL_ATTRIBUTES (variant_decl)
	= ವೃಕ್ಷ_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_ATTRIBUTES (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_finish_omp_declare_simd (c_parser *parser, ವೃಕ್ಷ fndecl, ವೃಕ್ಷ parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  ಯದಿ (clauses.exists () && clauses[0].type == CPP_EOF)
    ಪ್ರತ್ಯಾಗಮ;
  ಧ್ರುವ ವರ್ಣ *kind = "simd";
  ಯದಿ (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    kind = IDENTIFIER_POINTER (clauses[0].ಮೌಲ್ಯ);
  gcc_assert (strcmp (kind, "simd") == 0 || strcmp (kind, "variant") == 0);
  ಯದಿ (fndecl == NULL_ವೃಕ್ಷ || ವೃಕ್ಷ_CODE (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", kind);
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (parms == NULL_ವೃಕ್ಷ)
    parms = DECL_ARGUMENTS (fndecl);

  unsigned ಪೂರ್ಣಾಙ್ಕ tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);

  parser->tokens = clauses.address ();
  parser->tokens_avail = clauses.length ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  ಯಾವತ್ (parser->tokens_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      kind = IDENTIFIER_POINTER (token->ಮೌಲ್ಯ);
      c_parser_consume_token (parser);
      parser->in_pragma = ಸತ್ಯ;

      ಯದಿ (strcmp (kind, "simd") == 0)
	{
	  ವೃಕ್ಷ c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_MASK,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_to_numbers (parms, c);
	  ಯದಿ (c != NULL_ವೃಕ್ಷ)
	    c = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, c, NULL_ವೃಕ್ಷ);
	  c = build_ವೃಕ್ಷ_list (get_identifier ("omp declare simd"), c);
	  ವೃಕ್ಷ_CHAIN (c) = DECL_ATTRIBUTES (fndecl);
	  DECL_ATTRIBUTES (fndecl) = c;
	}
      ಅನ್ಯಥಾ
	{
	  gcc_assert (strcmp (kind, "variant") == 0);
	  c_finish_omp_declare_variant (parser, fndecl, parms);
	}
    }

  parser->tokens = &parser->tokens_buf[0];
  parser->tokens_avail = tokens_avail;
  ಯದಿ (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#ಯದಿ !defined (NO_DOT_IN_LABEL)
#define JOIN_STR "."
#ನೋಚೇದ್ಯದಿ !defined (NO_DOLLAR_IN_LABEL)
#define JOIN_STR "$"
#ಅನ್ಯಥಾ
#define JOIN_STR "_"
#endif

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
ಸ್ಥಿರ ವೃಕ್ಷ
omp_start_variant_function (c_declarator *declarator, ವೃಕ್ಷ ctx)
{
  c_declarator *id = declarator;
  ಯಾವತ್ (id->kind != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  ವೃಕ್ಷ name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  ಪ್ರತ್ಯಾಗಮ name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
ಸ್ಥಿರ ಶೂನ್ಯ
omp_finish_variant_function (ವೃಕ್ಷ decl, ವೃಕ್ಷ base_name, ವೃಕ್ಷ ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  ವೃಕ್ಷ base_decl = lookup_name (base_name);
  ಯದಿ (base_decl == error_mark_ಗಂಟು)
    base_decl = NULL_ವೃಕ್ಷ;
  ಯದಿ (!base_decl)
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_POINTER (base_name));
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (!comptypes (ವೃಕ್ಷ_TYPE (decl), ವೃಕ್ಷ_TYPE (base_decl)))
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", base_decl);
      inform (DECL_SOURCE_LOCATION (base_decl),
	      "%qE declared here", base_decl);
      ಪ್ರತ್ಯಾಗಮ;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_SOURCE_LOCATION (decl),
				   base_decl, ctx);
  ವೃಕ್ಷ construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (DECL_SOURCE_LOCATION (decl), decl, construct);
  ವೃಕ್ಷ attrs = DECL_ATTRIBUTES (base_decl);
  ವೃಕ್ಷ match_loc_ಗಂಟು
    = maybe_wrap_with_location (integer_zero_ಗಂಟು,
				DECL_SOURCE_LOCATION (base_decl));
  ವೃಕ್ಷ loc_ಗಂಟು = ವೃಕ್ಷ_cons (match_loc_ಗಂಟು, integer_zero_ಗಂಟು,
			     build_ವೃಕ್ಷ_list (match_loc_ಗಂಟು,
					      integer_zero_ಗಂಟು));
  attrs = ವೃಕ್ಷ_cons (get_identifier ("omp declare variant base"),
		     ವೃಕ್ಷ_cons (decl, ctx, loc_ಗಂಟು), attrs);
  DECL_ATTRIBUTES (base_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  ವೃಕ್ಷ_PUBLIC (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

ತಾರ್ಕಿಕ
c_maybe_parse_omp_decl (ವೃಕ್ಷ decl, ವೃಕ್ಷ d)
{
  gcc_assert (ವೃಕ್ಷ_CODE (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
  c_token *first = toks->address ();
  c_token *last = first + toks->length ();
  ಧ್ರುವ ವರ್ಣ *directive[3] = {};
  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < 3; j++)
    {
      ವೃಕ್ಷ id = NULL_ವೃಕ್ಷ;
      ಯದಿ (first + j == last)
	ಭಙ್ಗ;
      ಯದಿ (first[j].type == CPP_NAME)
	id = first[j].ಮೌಲ್ಯ;
      ಅನ್ಯಥಾ ಯದಿ (first[j].type == CPP_KEYWORD)
	id = ridpointers[(ಪೂರ್ಣಾಙ್ಕ) first[j].keyword];
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
      directive[j] = IDENTIFIER_POINTER (id);
    }
  ಧ್ರುವ c_omp_directive *dir = ರಿಕ್ತ;
  ಯದಿ (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  ಯದಿ (dir == ರಿಕ್ತ)
    {
      error_at (first->location,
		"unknown OpenMP directive name in "
		"%qs attribute argument", "omp::decl");
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }
  ಯದಿ (dir->id != PRAGMA_OMP_THREADPRIVATE
      && dir->id != PRAGMA_OMP_GROUPPRIVATE
      && dir->id != PRAGMA_OMP_ALLOCATE
      && (dir->id != PRAGMA_OMP_DECLARE
	  || strcmp (directive[1], "target") != 0))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಯದಿ (!flag_openmp && !dir->simd)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  c_parser *parser = the_parser;
  unsigned ಪೂರ್ಣಾಙ್ಕ tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);
  toks = ರಿಕ್ತ;
  vec_safe_reserve (toks, last - first + 2, ಸತ್ಯ);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_kind = pragma_kind (dir->id);
  tok.location = first->location;
  toks->quick_ತಳ್ಳು (tok);
  ಯಾವತ್ (++first < last)
    toks->quick_ತಳ್ಳು (*first);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_ತಳ್ಳು (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_ತಳ್ಳು (tok);
  parser->in_omp_decl_attribute = decl;
  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = toks->length ();
  c_parser_pragma (parser, pragma_external, ರಿಕ್ತ, NULL_ವೃಕ್ಷ);
  parser->in_omp_decl_attribute = NULL_ವೃಕ್ಷ;
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_declare_target (c_parser *parser)
{
  ವೃಕ್ಷ clauses = NULL_ವೃಕ್ಷ;
  ಪೂರ್ಣಾಙ್ಕ device_type = 0;
  ತಾರ್ಕಿಕ indirect = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ only_device_type_or_indirect = ಸತ್ಯ;
  ಯದಿ (flag_openmp)
    omp_requires_mask
      = (ಗಣನಾ omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
      || (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp declare target");
  ಅನ್ಯಥಾ ಯದಿ (parser->in_omp_decl_attribute
	   || c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      clauses = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					      clauses);
      clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
      c_parser_skip_to_pragma_eol (parser);
    }
  ಅನ್ಯಥಾ
    {
      warning_at (c_parser_peek_token (parser)->location,
		  OPT_Wdeprecated_openmp,
		  "use of %<omp declare target%> as a synonym for "
		  "%<omp begin declare target%> has been deprecated since "
		  "OpenMP 5.2");
      ತಾರ್ಕಿಕ attr_syntax = parser->in_omp_attribute_pragma != ರಿಕ್ತ;
      c_parser_skip_to_pragma_eol (parser);
      c_omp_declare_target_attr attr = { attr_syntax, -1, 0 };
      vec_safe_ತಳ್ಳು (current_omp_declare_target_attribute, attr);
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಪ್ರತಿ (ವೃಕ್ಷ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_ಅಭಿವ್ಯಕ್ತಿ (c));
    }
  ಪ್ರತಿ (ವೃಕ್ಷ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	ಅನುವರ್ತ;
      ವೃಕ್ಷ t = OMP_CLAUSE_DECL (c), id;
      ವೃಕ್ಷ at1 = lookup_attribute ("omp declare target", DECL_ATTRIBUTES (t));
      ವೃಕ್ಷ at2 = lookup_attribute ("omp declare target link",
				   DECL_ATTRIBUTES (t));
      only_device_type_or_indirect = ಅಸತ್ಯ;
      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::swap (at1, at2);
	}
      ಅನ್ಯಥಾ
	id = get_identifier ("omp declare target");
      ಯದಿ (at2)
	{
	  ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	  ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL
		   || ಮೌಲ್ಯ_member (get_identifier ("local"), ವೃಕ್ಷ_ಮೌಲ್ಯ (at2)))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<local%> clauses", t);
	  ಅನ್ಯಥಾ
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<to%> or %<enter%> clauses", t);
	  ಅನುವರ್ತ;
	}
      ಯದಿ (!at1)
	{
	  DECL_ATTRIBUTES (t) = ವೃಕ್ಷ_cons (id, NULL_ವೃಕ್ಷ, DECL_ATTRIBUTES (t));
	  ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    ವೃಕ್ಷ_ಮೌಲ್ಯ (DECL_ATTRIBUTES (t))
	      = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, get_identifier ("local"),
			   ವೃಕ್ಷ_ಮೌಲ್ಯ (DECL_ATTRIBUTES (t)));

	  ಯದಿ (ವೃಕ್ಷ_CODE (t) != FUNCTION_DECL && !is_global_var (t))
	    ಅನುವರ್ತ;

	  symtab_ಗಂಟು *ಗಂಟು = symtab_ಗಂಟು::get (t);
	  ಯದಿ (ಗಂಟು != ರಿಕ್ತ)
	    {
	      ಗಂಟು->offloadable = 1;
	      ಯದಿ (ENABLE_OFFLOADING)
		{
		  g->have_offload = ಸತ್ಯ;
		  ಯದಿ (is_a <varpool_ಗಂಟು *> (ಗಂಟು)
		      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_LOCAL)
		    vec_safe_ತಳ್ಳು (offload_vars, t);
		}
	    }
	}
      ಅನ್ಯಥಾ
	{
	  ತಾರ್ಕಿಕ saw_local = ಮೌಲ್ಯ_member (get_identifier ("local"),
					 ವೃಕ್ಷ_ಮೌಲ್ಯ (at1));
	  ಯದಿ (saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	      ಅನುವರ್ತ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (!saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      ಅನುವರ್ತ;
	    }
	}
      ಯದಿ (ವೃಕ್ಷ_CODE (t) != FUNCTION_DECL)
	ಅನುವರ್ತ;
      ಯದಿ ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  ವೃಕ್ಷ at3 = lookup_attribute ("omp declare target host",
				       DECL_ATTRIBUTES (t));
	  ಯದಿ (at3 == NULL_ವೃಕ್ಷ)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_ATTRIBUTES (t)
		= ವೃಕ್ಷ_cons (id, NULL_ವೃಕ್ಷ, DECL_ATTRIBUTES (t));
	    }
	}
      ಯದಿ ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  ವೃಕ್ಷ at3 = lookup_attribute ("omp declare target nohost",
				       DECL_ATTRIBUTES (t));
	  ಯದಿ (at3 == NULL_ವೃಕ್ಷ)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_ATTRIBUTES (t)
		= ವೃಕ್ಷ_cons (id, NULL_ವೃಕ್ಷ, DECL_ATTRIBUTES (t));
	    }
	}
      ಯದಿ (indirect)
	{
	  ವೃಕ್ಷ at4 = lookup_attribute ("omp declare target indirect",
				       DECL_ATTRIBUTES (t));
	  ಯದಿ (at4 == NULL_ವೃಕ್ಷ)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_ATTRIBUTES (t)
		= ವೃಕ್ಷ_cons (id, NULL_ವೃಕ್ಷ, DECL_ATTRIBUTES (t));
	    }
	}
    }
  ಯದಿ ((device_type || indirect) && only_device_type_or_indirect)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  ಯದಿ (indirect && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_begin (c_parser *parser)
{
  ಧ್ರುವ ವರ್ಣ *p = "";
  c_parser_consume_pragma (parser);
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
  ಯದಿ (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  ತಾರ್ಕಿಕ attr_syntax = parser->in_omp_attribute_pragma != ರಿಕ್ತ;
	  ವೃಕ್ಷ clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp begin declare target");
	  ಪೂರ್ಣಾಙ್ಕ device_type = 0;
	  ಪೂರ್ಣಾಙ್ಕ indirect = 0;
	  ಪ್ರತಿ (ವೃಕ್ಷ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
	      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
		indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_ಅಭಿವ್ಯಕ್ತಿ (c));
	    }
	  c_omp_declare_target_attr attr = { attr_syntax, device_type,
					     indirect };
	  vec_safe_ತಳ್ಳು (current_omp_declare_target_attribute, attr);
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  ಧ್ರುವ ವರ್ಣ *clause = "";
	  matching_parens parens;
	  location_t match_loc = c_parser_peek_token (parser)->location;
	  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	      clause = IDENTIFIER_POINTER (id);
	    }
	  ಯದಿ (strcmp (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_to_pragma_eol (parser);
	      ಪ್ರತ್ಯಾಗಮ;
	    }

	  c_parser_consume_token (parser);

	  ಯದಿ (!parens.require_open (parser))
	    {
	      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	      ಪ್ರತ್ಯಾಗಮ;
	    }

	  ವೃಕ್ಷ ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_ವೃಕ್ಷ);
	  ಯದಿ (ctx != error_mark_ಗಂಟು)
	    ctx = omp_check_context_selector (match_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  ಯದಿ (ctx != error_mark_ಗಂಟು
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      ವೃಕ್ಷ outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  ಯದಿ (ctx == error_mark_ಗಂಟು
	      || !omp_context_selector_matches (ctx, NULL_ವೃಕ್ಷ, ಅಸತ್ಯ, ಸತ್ಯ))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	      c_parser_skip_to_pragma_omp_end_declare_variant (parser);
	      ಪ್ರತ್ಯಾಗಮ;
	    }
	  ಅನ್ಯಥಾ
	    {
	      ತಾರ್ಕಿಕ attr_syntax = parser->in_omp_attribute_pragma != ರಿಕ್ತ;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_safe_ತಳ್ಳು (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_to_pragma_eol (parser);
	}
      ಅನ್ಯಥಾ
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      ತಾರ್ಕಿಕ attr_syntax = parser->in_omp_attribute_pragma != ರಿಕ್ತ;
      c_parser_omp_assumption_clauses (parser, ಅಸತ್ಯ);
      ಸಂರಚನಾ c_omp_begin_assumes_data a = { attr_syntax };
      vec_safe_ತಳ್ಳು (current_omp_begin_assumes, a);
    }
  ಅನ್ಯಥಾ
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_end (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ಧ್ರುವ ವರ್ಣ *p = "";
  c_parser_consume_pragma (parser);
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
  ಯದಿ (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  ತಾರ್ಕಿಕ attr_syntax = parser->in_omp_attribute_pragma != ರಿಕ್ತ;
	  c_parser_skip_to_pragma_eol (parser);
	  ಯದಿ (!vec_safe_length (current_omp_declare_target_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  ಅನ್ಯಥಾ
	    {
	      c_omp_declare_target_attr
		a = current_omp_declare_target_attribute->ತೆಗೆ ();
	      ಯದಿ (a.attr_syntax != attr_syntax)
		{
		  ಯದಿ (a.attr_syntax)
		    error_at (loc,
			      "%qs in attribute syntax terminated "
			      "with %qs in pragma syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		  ಅನ್ಯಥಾ
		    error_at (loc,
			      "%qs in pragma syntax terminated "
			      "with %qs in attribute syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		}
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  ತಾರ್ಕಿಕ attr_syntax = parser->in_omp_attribute_pragma != ರಿಕ್ತ;
	  c_parser_skip_to_pragma_eol (parser);
	  ಯದಿ (!vec_safe_length (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  ಅನ್ಯಥಾ
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->ತೆಗೆ ();
	      ಯದಿ (a.attr_syntax != attr_syntax)
		{
		  ಯದಿ (a.attr_syntax)
		    error_at (loc,
			      "%<begin declare variant%> in attribute syntax "
			      "terminated with "
			      "%<end declare variant%> in pragma syntax");
		  ಅನ್ಯಥಾ
		    error_at (loc,
			      "%<begin declare variant%> in pragma syntax "
			      "terminated with "
			      "%<end declare variant%> in attribute syntax");
		}
	    }
	}
      ಅನ್ಯಥಾ
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser);
	  ಪ್ರತ್ಯಾಗಮ;
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      ತಾರ್ಕಿಕ attr_syntax = parser->in_omp_attribute_pragma != ರಿಕ್ತ;
      c_parser_skip_to_pragma_eol (parser);
      ಯದಿ (!vec_safe_length (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      ಅನ್ಯಥಾ
	{
	  c_omp_begin_assumes_data
	    a = current_omp_begin_assumes->ತೆಗೆ ();
	  ಯದಿ (a.attr_syntax != attr_syntax)
	    {
	      ಯದಿ (a.attr_syntax)
		error_at (loc,
			  "%qs in attribute syntax terminated "
			  "with %qs in pragma syntax",
			  "begin assumes", "end assumes");
	      ಅನ್ಯಥಾ
		error_at (loc,
			  "%qs in pragma syntax terminated "
			  "with %qs in attribute syntax",
			  "begin assumes", "end assumes");
	    }
	}
    }
  ಅನ್ಯಥಾ
    {
      c_parser_error (parser, "expected %<declare%> or %<assumes%>");
      c_parser_skip_to_pragma_eol (parser);
    }
}

/* OpenMP 5.0
   #pragma omp declare mapper ([mapper-identifier :] type var) \
			      [clause [ [,] clause ] ... ] new-line  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_declare_mapper (c_parser *parser, ಗಣನಾ pragma_context context)
{
  ವೃಕ್ಷ type, mapper_name = NULL_ವೃಕ್ಷ, var = NULL_ವೃಕ್ಷ, stmt, stmtlist;
  ವೃಕ್ಷ maplist = NULL_ವೃಕ್ಷ, mapper_id, mapper_decl, t;
  c_token *token;

  ಯದಿ (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare mapper%> not at file or block scope");
      ಗಚ್ಛ fail;
    }

  ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ಗಚ್ಛ fail;

  token = c_parser_peek_token (parser);

  ಯದಿ (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      ವಿಕಲ್ಪ (token->type)
	{
	ಪಕ್ಷ CPP_NAME:
	  mapper_name = token->ಮೌಲ್ಯ;
	  c_parser_consume_token (parser);
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_KEYWORD:
	  ಯದಿ (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_ವೃಕ್ಷ;
	      c_parser_consume_token (parser);
	      ಭಙ್ಗ;
	    }
	  /* Fallthrough.  */
	ಸ್ವಭಾವ:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	  ಪ್ರತ್ಯಾಗಮ;
	}

      ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ಗಚ್ಛ fail;
    }

  mapper_id = c_omp_mapper_id (mapper_name);
  mapper_decl = c_omp_mapper_decl (mapper_id);

  {
    location_t loc = c_parser_peek_token (parser)->location;
    ಸಂರಚನಾ c_type_name *ctype = c_parser_type_name (parser);
    type = groktypename (ctype, ರಿಕ್ತ, ರಿಕ್ತ);
    ಯದಿ (type == error_mark_ಗಂಟು)
      ಗಚ್ಛ fail;
    ಯದಿ (!RECORD_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	ಪ್ರತ್ಯಾಗಮ;
      }
    ಪ್ರತಿ (ವೃಕ್ಷ t = DECL_INITIAL (mapper_decl); t; t = ವೃಕ್ಷ_CHAIN (t))
      ಯದಿ (comptypes (ವೃಕ್ಷ_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_POINTER (mapper_id)
		      + ಪರಿಮಾಣ ("omp declare mapper ") - 1,
		    type);
	  ವೃಕ್ಷ prevmapper = ವೃಕ್ಷ_ಮೌಲ್ಯ (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_SOURCE_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	  ಪ್ರತ್ಯಾಗಮ;
	}
  }

  token = c_parser_peek_token (parser);
  ಯದಿ (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->ಮೌಲ್ಯ, type);
      c_parser_consume_token (parser);
      DECL_ARTIFICIAL (var) = 1;
    }
  ಅನ್ಯಥಾ
    {
      error_at (token->location, "expected identifier");
      ಗಚ್ಛ fail;
    }

  ಯದಿ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ಗಚ್ಛ fail;

  ತಳ್ಳು_scope ();
  stmtlist = ತಳ್ಳು_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);
      ಯದಿ (c_kind != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (here, "unexpected clause");
	  ಗಚ್ಛ fail;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, ಸತ್ಯ);
    }

  ಯದಿ (maplist == NULL_ವೃಕ್ಷ)
    {
      error_at (ಒಳಹರಿವು_location, "missing %<map%> clause");
      ಗಚ್ಛ fail;
    }
  ವೃಕ್ಷ list;
  ಪ್ರತಿ (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      ವೃಕ್ಷ dvar = OMP_CLAUSE_DECL (list);
      ಯಾವತ್ (!DECL_P (dvar) && ವೃಕ್ಷ_OPERAND_LENGTH (dvar))
	dvar = ವೃಕ್ಷ_OPERAND (dvar, 0);
      ಯದಿ (dvar == var)
	ಭಙ್ಗ;
    }
  ಯದಿ (!list)
    error_at (ಒಳಹರಿವು_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_ಗಂಟು (OMP_DECLARE_MAPPER);
  ವೃಕ್ಷ_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  add_stmt (stmt);

  ತೆಗೆ_stmt_list (stmtlist);
  ತೆಗೆ_scope ();

  c_parser_skip_to_pragma_eol (parser);

  t = ವೃಕ್ಷ_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  ಪ್ರತ್ಯಾಗಮ;

 fail:
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 4.0
   #pragma omp declare reduction (reduction-id : typename-list : expression) \
      initializer-clause[opt] new-line

   initializer-clause:
      initializer (omp_priv = initializer)
      initializer (function-name (argument-list))  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_declare_reduction (c_parser *parser, ಗಣನಾ pragma_context context)
{
  unsigned ಪೂರ್ಣಾಙ್ಕ tokens_avail = 0, i;
  c_token *saved_tokens = ರಿಕ್ತ;
  vec<ವೃಕ್ಷ> types = vNULL;
  vec<c_token> clauses = vNULL;
  ಗಣನಾ ವೃಕ್ಷ_code reduc_code = ERROR_MARK;
  ವೃಕ್ಷ reduc_id = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ type;
  location_t rloc = c_parser_peek_token (parser)->location;

  ಯದಿ (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare reduction%> not at file or block scope");
      ಗಚ್ಛ fail;
    }

  ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ಗಚ್ಛ fail;

  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
    {
    ಪಕ್ಷ CPP_PLUS:
      reduc_code = PLUS_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_MULT:
      reduc_code = MULT_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_MINUS:
      reduc_code = MINUS_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_AND:
      reduc_code = BIT_AND_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_XOR:
      reduc_code = BIT_XOR_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_OR:
      reduc_code = BIT_IOR_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_AND_AND:
      reduc_code = TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_OR_OR:
      reduc_code = TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_NAME:
      ಧ್ರುವ ವರ್ಣ *p;
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "min") == 0)
	{
	  reduc_code = MIN_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	}
      ಯದಿ (strcmp (p, "max") == 0)
	{
	  reduc_code = MAX_ಅಭಿವ್ಯಕ್ತಿ;
	  ಭಙ್ಗ;
	}
      reduc_id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      ಗಚ್ಛ fail;
    }

  ವೃಕ್ಷ orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_code, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    ಗಚ್ಛ fail;

  ಯಾವತ್ (ಸತ್ಯ)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      ಸಂರಚನಾ c_type_name *ctype = c_parser_type_name (parser);
      ಯದಿ (ctype != ರಿಕ್ತ)
	{
	  type = groktypename (ctype, ರಿಕ್ತ, ರಿಕ್ತ);
	  ಯದಿ (type == error_mark_ಗಂಟು)
	    ;
	  ಅನ್ಯಥಾ ಯದಿ ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || ವೃಕ್ಷ_CODE (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_ವೃಕ್ಷ)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE
		   || ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE)
	    error_at (loc, "function or array type in "
		      "%<#pragma omp declare reduction%>");
	  ಅನ್ಯಥಾ ಯದಿ (TYPE_ATOMIC (type))
	    error_at (loc, "%<_Atomic%> qualified type in "
			   "%<#pragma omp declare reduction%>");
	  ಅನ್ಯಥಾ ಯದಿ (TYPE_QUALS_NO_ADDR_SPACE (type))
	    error_at (loc, "const, volatile or restrict qualified type in "
			   "%<#pragma omp declare reduction%>");
	  ಅನ್ಯಥಾ
	    {
	      ವೃಕ್ಷ t;
	      ಪ್ರತಿ (t = DECL_INITIAL (reduc_decl); t; t = ವೃಕ್ಷ_CHAIN (t))
		ಯದಿ (comptypes (ವೃಕ್ಷ_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_POINTER (reduc_id)
				   + ಪರಿಮಾಣ ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_SOURCE_LOCATION (ವೃಕ್ಷ_VEC_ELT (ವೃಕ್ಷ_ಮೌಲ್ಯ (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    ಭಙ್ಗ;
		  }
	      ಯದಿ (t == NULL_ವೃಕ್ಷ)
		types.safe_ತಳ್ಳು (type);
	    }
	  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ಅನ್ಯಥಾ
	    ಭಙ್ಗ;
	}
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
    }

  ಯದಿ (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_empty ())
    {
     fail:
      clauses.release ();
      types.release ();
      ಯಾವತ್ (ಸತ್ಯ)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ಯದಿ (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    ಭಙ್ಗ;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_to_pragma_eol (parser);
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (types.length () > 1)
    {
      ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  ಯದಿ (token->type == CPP_EOF)
	    ಗಚ್ಛ fail;
	  clauses.safe_ತಳ್ಳು (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_ತಳ್ಳು (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, ಪರಿಮಾಣ (eof_token));
      eof_token.type = CPP_EOF;
      clauses.safe_ತಳ್ಳು (eof_token);
      clauses.safe_ತಳ್ಳು (eof_token);
    }

  ಪೂರ್ಣಾಙ್ಕ errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_tokens = parser->tokens;
      tokens_avail = parser->tokens_avail;
      ಯದಿ (!clauses.is_empty ())
	{
	  parser->tokens = clauses.address ();
	  parser->tokens_avail = clauses.length ();
	  parser->in_pragma = ಸತ್ಯ;
	}

      ತಾರ್ಕಿಕ nested = current_function_decl != NULL_ವೃಕ್ಷ;
      ಯದಿ (nested)
	c_ತಳ್ಳು_function_context ();
      ವೃಕ್ಷ fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, ಸತ್ಯ);
      ತಳ್ಳು_scope ();
      ವೃಕ್ಷ stmt = ತಳ್ಳು_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      ವೃಕ್ಷ omp_out = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_out) = 1;
      DECL_CONTEXT (omp_out) = fndecl;
      pushdecl (omp_out);
      ವೃಕ್ಷ omp_in = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_in) = 1;
      DECL_CONTEXT (omp_in) = fndecl;
      pushdecl (omp_in);
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ combiner = c_parser_expression (parser);
      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ initializer;
      ವೃಕ್ಷ omp_priv = NULL_ವೃಕ್ಷ, omp_orig = NULL_ವೃಕ್ಷ;
      ತಾರ್ಕಿಕ bad = ಅಸತ್ಯ;
      initializer.set_error ();
      ಯದಿ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	bad = ಸತ್ಯ;
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      ಯದಿ (!bad
	  && (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->ಮೌಲ್ಯ),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  ತೆಗೆ_scope ();
	  ತಳ್ಳು_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_ಗಂಟು;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    bad = ಸತ್ಯ;
	  ಅನ್ಯಥಾ ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      bad = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->ಮೌಲ್ಯ),
			   "omp_priv") != 0)
	    {
	      ಯದಿ (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_kind != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  bad = ಸತ್ಯ;
		}
	      ಅನ್ಯಥಾ
		initializer = c_parser_postfix_expression (parser);
	      ಯದಿ (initializer.ಮೌಲ್ಯ
		  && ವೃಕ್ಷ_CODE (initializer.ಮೌಲ್ಯ) == CALL_ಅಭಿವ್ಯಕ್ತಿ)
		{
		  ಪೂರ್ಣಾಙ್ಕ j;
		  ವೃಕ್ಷ c = initializer.ಮೌಲ್ಯ;
		  ಪ್ರತಿ (j = 0; j < call_ಅಭಿವ್ಯಕ್ತಿ_nargs (c); j++)
		    {
		      ವೃಕ್ಷ a = CALL_ಅಭಿವ್ಯಕ್ತಿ_ARG (c, j);
		      STRIP_NOPS (a);
		      ಯದಿ (ವೃಕ್ಷ_CODE (a) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
			  && ವೃಕ್ಷ_OPERAND (a, 0) == omp_priv)
			ಭಙ್ಗ;
		    }
		  ಯದಿ (j == call_ಅಭಿವ್ಯಕ್ತಿ_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  ಅನ್ಯಥಾ
	    {
	      c_parser_consume_token (parser);
	      ಯದಿ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		bad = ಸತ್ಯ;
	      ಅನ್ಯಥಾ
		{
		  ವೃಕ್ಷ st = ತಳ್ಳು_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (ಸಾಲು_table, loc);
		  start_init (omp_priv, NULL_ವೃಕ್ಷ, ಅಸತ್ಯ, ಅಸತ್ಯ, &richloc);
		  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ init = c_parser_initializer (parser, omp_priv);
		  finish_init ();
		  finish_decl (omp_priv, loc, init.ಮೌಲ್ಯ,
		      	       init.original_type, NULL_ವೃಕ್ಷ);
		  ತೆಗೆ_stmt_list (st);
		}
	    }
	  ಯದಿ (!bad
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    bad = ಸತ್ಯ;
	}

      ಯದಿ (!bad)
	{
	  c_parser_skip_to_pragma_eol (parser);

	  ವೃಕ್ಷ t = ವೃಕ್ಷ_cons (type, make_ವೃಕ್ಷ_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_SOURCE_LOCATION (omp_out) = rloc;
	  ವೃಕ್ಷ_VEC_ELT (ವೃಕ್ಷ_ಮೌಲ್ಯ (t), 0) = omp_out;
	  ವೃಕ್ಷ_VEC_ELT (ವೃಕ್ಷ_ಮೌಲ್ಯ (t), 1) = omp_in;
	  ವೃಕ್ಷ_VEC_ELT (ವೃಕ್ಷ_ಮೌಲ್ಯ (t), 2) = combiner.ಮೌಲ್ಯ;
	  walk_ವೃಕ್ಷ (&combiner.ಮೌಲ್ಯ, c_check_omp_declare_reduction_r,
		     &ವೃಕ್ಷ_VEC_ELT (ವೃಕ್ಷ_ಮೌಲ್ಯ (t), 0), ರಿಕ್ತ);
	  ಯದಿ (omp_priv)
	    {
	      DECL_SOURCE_LOCATION (omp_priv) = rloc;
	      ವೃಕ್ಷ_VEC_ELT (ವೃಕ್ಷ_ಮೌಲ್ಯ (t), 3) = omp_priv;
	      ವೃಕ್ಷ_VEC_ELT (ವೃಕ್ಷ_ಮೌಲ್ಯ (t), 4) = omp_orig;
	      ವೃಕ್ಷ_VEC_ELT (ವೃಕ್ಷ_ಮೌಲ್ಯ (t), 5) = initializer.ಮೌಲ್ಯ;
	      walk_ವೃಕ್ಷ (&initializer.ಮೌಲ್ಯ, c_check_omp_declare_reduction_r,
			 &ವೃಕ್ಷ_VEC_ELT (ವೃಕ್ಷ_ಮೌಲ್ಯ (t), 3), ರಿಕ್ತ);
	      walk_ವೃಕ್ಷ (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &ವೃಕ್ಷ_VEC_ELT (ವೃಕ್ಷ_ಮೌಲ್ಯ (t), 3), ರಿಕ್ತ);
	    }
	}

      ತೆಗೆ_stmt_list (stmt);
      ತೆಗೆ_scope ();
      ಯದಿ (cfun->language != ರಿಕ್ತ)
	{
	  ggc_free (cfun->language);
	  cfun->language = ರಿಕ್ತ;
	}
      set_cfun (ರಿಕ್ತ);
      current_function_decl = NULL_ವೃಕ್ಷ;
      ಯದಿ (nested)
	c_ತೆಗೆ_function_context ();

      ಯದಿ (!clauses.is_empty ())
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}
      ಯದಿ (bad)
	ಗಚ್ಛ fail;
      ಯದಿ (errs != errorcount)
	ಭಙ್ಗ;
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

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_omp_declare (c_parser *parser, ಗಣನಾ pragma_context context)
{
  c_parser_consume_pragma (parser);
  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	}
      ಯದಿ (strcmp (p, "reduction") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_reduction (parser, context);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
      ಯದಿ (strcmp (p, "mapper") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_mapper (parser, context);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
      ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
      ಯದಿ (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_target (parser);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
      ಯದಿ (strcmp (p, "variant") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_to_pragma_eol (parser);
  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* OpenMP 5.0
   #pragma omp requires clauses[optseq] new-line  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_requires (c_parser *parser)
{
  ಗಣನಾ omp_requires new_req = (ಗಣನಾ omp_requires) 0;

  c_parser_consume_pragma (parser);

  location_t loc = c_parser_peek_token (parser)->location;
  ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ಧ್ರುವ ವರ್ಣ *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  ಗಣನಾ omp_requires this_req = (ಗಣನಾ omp_requires) 0;

	  ಯದಿ (!strcmp (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_ADDRESS;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_MEMORY;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_REVERSE_OFFLOAD;
	  ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      ಯದಿ (parens.require_open (parser))
		{
		  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
		    {
		      ವೃಕ್ಷ v = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
		      p = IDENTIFIER_POINTER (v);

		      ಯದಿ (!strcmp (p, "seq_cst"))
			this_req
			  = (ಗಣನಾ omp_requires) OMP_MEMORY_ORDER_SEQ_CST;
		      ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "relaxed"))
			this_req
			  = (ಗಣನಾ omp_requires) OMP_MEMORY_ORDER_RELAXED;
		      ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "release"))
			this_req
			  = (ಗಣನಾ omp_requires) OMP_MEMORY_ORDER_RELEASE;
		      ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "acq_rel"))
			this_req
			  = (ಗಣನಾ omp_requires) OMP_MEMORY_ORDER_ACQ_REL;
		      ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "acquire"))
			this_req
			  = (ಗಣನಾ omp_requires) OMP_MEMORY_ORDER_ACQUIRE;
		    }
		  ಯದಿ (this_req == 0)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<acq_rel%>, %<acquire%>, "
				"%<relaxed%>, %<release%> or %<seq_cst%>");
		      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
			{
			ಪಕ್ಷ CPP_EOF:
			ಪಕ್ಷ CPP_PRAGMA_EOL:
			ಪಕ್ಷ CPP_CLOSE_PAREN:
			  ಭಙ್ಗ;
			ಸ್ವಭಾವ:
			  ಯದಿ (c_parser_peek_2nd_token (parser)->type
			      == CPP_CLOSE_PAREN)
			    c_parser_consume_token (parser);
			  ಭಙ್ಗ;
			}
		    }
		  ಅನ್ಯಥಾ
		    c_parser_consume_token (parser);

		  parens.skip_until_found_close (parser);
		  ಯದಿ (this_req == 0)
		    {
		      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
		      ಪ್ರತ್ಯಾಗಮ;
		    }
		}
	      p = ರಿಕ್ತ;
	    }
	  ಅನ್ಯಥಾ
	    {
	      error_at (cloc, "expected %<unified_address%>, "
			      "%<unified_shared_memory%>, "
			      "%<self_maps%>, "
			      "%<dynamic_allocators%>, "
			       "%<reverse_offload%> "
			       "or %<atomic_default_mem_order%> clause");
	      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	      ಪ್ರತ್ಯಾಗಮ;
	    }
	  ಯದಿ (p)
	    c_parser_consume_token (parser);
	  ಯದಿ (this_req)
	    {
	      ಯದಿ ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  ಯದಿ ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  ಯದಿ (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_mask & OMP_REQUIRES_TARGET_USED) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      ಅನ್ಯಥಾ ಯದಿ ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (ಗಣನಾ omp_requires) 0;
		}
	      ಅನ್ಯಥಾ ಯದಿ ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (ಗಣನಾ omp_requires)
		       (omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER);
		}
	      ಅನ್ಯಥಾ ಯದಿ ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (ಗಣನಾ omp_requires) (new_req | this_req);
	      omp_requires_mask
		= (ಗಣನಾ omp_requires) (omp_requires_mask | this_req);
	      ಅನುವರ್ತ;
	    }
	}
      ಭಙ್ಗ;
    }
  c_parser_skip_to_pragma_eol (parser);

  ಯದಿ (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_finish_taskloop_clauses (ವೃಕ್ಷ clauses)
{
  ವೃಕ್ಷ *pc = &clauses;
  ಪ್ರತಿ (ವೃಕ್ಷ c = clauses; c; c = *pc)
    {
      ತಾರ್ಕಿಕ remove = ಅಸತ್ಯ;
      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
	{
	  ವೃಕ್ಷ type = strip_array_types (ವೃಕ್ಷ_TYPE (OMP_CLAUSE_DECL (c)));
	  ಯದಿ (integer_zerop (TYPE_SIZE_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      remove = ಸತ್ಯ;
	    }
	}
      ಯದಿ (remove)
	*pc = OMP_CLAUSE_CHAIN (c);
      ಅನ್ಯಥಾ
	pc = &OMP_CLAUSE_CHAIN (c);
    }
  ಪ್ರತ್ಯಾಗಮ clauses;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ಅಂಕೆ_TASKS)	\
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       ವರ್ಣ *p_name, omp_clause_mask mask, ವೃಕ್ಷ *cclauses,
		       ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ clauses, block, ret;

  strcat (p_name, " taskloop");
  mask |= OMP_TASKLOOP_CLAUSE_MASK;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  ಯದಿ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ಅಂಕೆ_THREADS)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IN_REDUCTION);

  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);

      ಯದಿ (strcmp (p, "simd") == 0)
	{
	  ವೃಕ್ಷ cclauses_buf[C_OMP_CLAUSE_SPLIT_ಎಣಿಕೆ];
	  ಯದಿ (cclauses == ರಿಕ್ತ)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
	    ಪ್ರತ್ಯಾಗಮ c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (ಸತ್ಯ);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
	  ಯದಿ (ret == ರಿಕ್ತ)
	    ಪ್ರತ್ಯಾಗಮ ret;
	  ret = make_ಗಂಟು (OMP_TASKLOOP);
	  ವೃಕ್ಷ_TYPE (ret) = void_type_ಗಂಟು;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_finish_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret, loc);
	  add_stmt (ret);
	  ಪ್ರತ್ಯಾಗಮ ret;
	}
    }
  ಯದಿ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ರಿಕ್ತ);
  ಯದಿ (cclauses)
    {
      omp_split_clauses (loc, OMP_TASKLOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
    }

  clauses = c_finish_taskloop_clauses (clauses);
  block = c_begin_compound_stmt (ಸತ್ಯ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, ರಿಕ್ತ, if_p);
  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
  add_stmt (block);

  ಪ್ರತ್ಯಾಗಮ ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  ವೃಕ್ಷ sizes = NULL_ವೃಕ್ಷ;

  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  ಯದಿ (tok->type != CPP_NAME
      || strcmp ("sizes", IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  ಯದಿ (!parens.require_open (parser))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  vec<ವೃಕ್ಷ, va_gc> *sizes_vec
    = c_parser_ಅಭಿವ್ಯಕ್ತಿ_list (parser, ಸತ್ಯ, ಸತ್ಯ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ);
  sizes = build_ವೃಕ್ಷ_list_vec (sizes_vec);
  release_ವೃಕ್ಷ_vector (sizes_vec);

  ಪ್ರತಿ (ವೃಕ್ಷ s = sizes; s; s = ವೃಕ್ಷ_CHAIN (s))
    {
      ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = ವೃಕ್ಷ_ಮೌಲ್ಯ (s);
      ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ == error_mark_ಗಂಟು)
	{
	  parens.skip_until_found_close (parser);
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}

      HOST_WIDE_INT n;
      ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ))
	  || !ವೃಕ್ಷ_fits_shwi_p (ಅಭಿವ್ಯಕ್ತಿ)
	  || (n = ವೃಕ್ಷ_to_shwi (ಅಭಿವ್ಯಕ್ತಿ)) <= 0
	  || (ಪೂರ್ಣಾಙ್ಕ) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  ವೃಕ್ಷ_ಮೌಲ್ಯ (s) = integer_one_ಗಂಟು;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  ವೃಕ್ಷ c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  ಪ್ರತ್ಯಾಗಮ c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_tile (location_t loc, c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_to_pragma_eol (parser);

  ಯದಿ (!clauses || clauses == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ವೃಕ್ಷ block = c_begin_compound_stmt (ಸತ್ಯ);
  ವೃಕ್ಷ ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    ರಿಕ್ತ, if_p);
  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
  add_stmt (block);

  ಪ್ರತ್ಯಾಗಮ ret;
}

#define OMP_UNROLL_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FULL))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_omp_unroll (location_t loc, c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  ವೃಕ್ಷ clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_MASK,
					   "#pragma omp unroll", ಸತ್ಯ);

  ವೃಕ್ಷ block = c_begin_compound_stmt (ಸತ್ಯ);
  ವೃಕ್ಷ ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    ರಿಕ್ತ, if_p);
  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);
  add_stmt (block);

  ಪ್ರತ್ಯಾಗಮ ret;
}

/* OpenMP 5.1
   #pragma omp nothing new-line  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_nothing (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp error clauses[optseq] new-line  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_omp_error (c_parser *parser, ಗಣನಾ pragma_context context)
{
  ಪೂರ್ಣಾಙ್ಕ at_compilation = -1;
  ಪೂರ್ಣಾಙ್ಕ severity_fatal = -1;
  ವೃಕ್ಷ message = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ bad = ಅಸತ್ಯ;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME))
	ಭಙ್ಗ;

      ಧ್ರುವ ವರ್ಣ *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      location_t cloc = c_parser_peek_token (parser)->location;
      ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *args[] = {
	"execution", "compilation", "warning", "fatal"
      };
      ಪೂರ್ಣಾಙ್ಕ *v = ರಿಕ್ತ;
      ಪೂರ್ಣಾಙ್ಕ idx = 0, n = -1;
      ವೃಕ್ಷ m = NULL_ವೃಕ್ಷ;

      ಯದಿ (!strcmp (p, "at"))
	v = &at_compilation;
      ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "severity"))
	{
	  v = &severity_fatal;
	  idx += 2;
	}
      ಅನ್ಯಥಾ ಯದಿ (strcmp (p, "message"))
	{
	  error_at (cloc,
		    "expected %<at%>, %<severity%> or %<message%> clause");
	  c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      ಯದಿ (parens.require_open (parser))
	{
	  ಯದಿ (v == ರಿಕ್ತ)
	    {
	      location_t ಅಭಿವ್ಯಕ್ತಿ_loc = c_parser_peek_token (parser)->location;
	      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	      ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (ಅಭಿವ್ಯಕ್ತಿ_loc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಸತ್ಯ);
	      m = convert (const_string_type_ಗಂಟು, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	      m = c_fully_fold (m, ಅಸತ್ಯ, ರಿಕ್ತ);
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
		{
		  ವೃಕ್ಷ val = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
		  ಧ್ರುವ ವರ್ಣ *q = IDENTIFIER_POINTER (val);

		  ಯದಿ (!strcmp (q, args[idx]))
		    n = 0;
		  ಅನ್ಯಥಾ ಯದಿ (!strcmp (q, args[idx + 1]))
		    n = 1;
		}
	      ಯದಿ (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", args[idx], args[idx + 1]);
		  bad = ಸತ್ಯ;
		  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
		    {
		    ಪಕ್ಷ CPP_EOF:
		    ಪಕ್ಷ CPP_PRAGMA_EOL:
		    ಪಕ್ಷ CPP_CLOSE_PAREN:
		      ಭಙ್ಗ;
		    ಸ್ವಭಾವ:
		      ಯದಿ (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)
			c_parser_consume_token (parser);
		      ಭಙ್ಗ;
		    }
		}
	      ಅನ್ಯಥಾ
		c_parser_consume_token (parser);
	    }

	  parens.skip_until_found_close (parser);

	  ಯದಿ (v == ರಿಕ್ತ)
	    {
	      ಯದಿ (message)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = ಸತ್ಯ;
		}
	      ಅನ್ಯಥಾ
		message = m;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (n != -1)
	    {
	      ಯದಿ (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = ಸತ್ಯ;
		}
	      ಅನ್ಯಥಾ
		*v = n;
	    }
	}
      ಅನ್ಯಥಾ
	bad = ಸತ್ಯ;
    }
  c_parser_skip_to_pragma_eol (parser);
  ಯದಿ (bad)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  ಯದಿ (at_compilation == -1)
    at_compilation = 1;
  ಯದಿ (severity_fatal == -1)
    severity_fatal = 1;
  ಯದಿ (!at_compilation)
    {
      ಯದಿ (context != pragma_compound)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may only be used in compound statements");
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	}
      ಯದಿ (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->in_intervening_code)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->fail = ಸತ್ಯ;
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	}
      ವೃಕ್ಷ fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_IN_GOMP_ERROR
						: BUILT_IN_GOMP_WARNING);
      ಯದಿ (!message)
	message = build_zero_cst (const_string_type_ಗಂಟು);
      ವೃಕ್ಷ stmt = build_call_ಅಭಿವ್ಯಕ್ತಿ_loc (loc, fndecl, 2, message,
				       build_all_ones_cst (size_type_ಗಂಟು));
      add_stmt (stmt);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }
  ಧ್ರುವ ವರ್ಣ *ಸಂದೇಶ = ರಿಕ್ತ;
  ಯದಿ (message)
    {
      ಸಂದೇಶ = c_getstr (message);
      ಯದಿ (ಸಂದೇಶ == ರಿಕ್ತ)
	ಸಂದೇಶ = _("<message unknown at compile time>");
    }
  ಧ್ರುವ ಗಣನಾ diagnostics::kind diag_kind = (severity_fatal
					    ? diagnostics::kind::error
					    : diagnostics::kind::warning);
  ಯದಿ (ಸಂದೇಶ)
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered: %s", ಸಂದೇಶ);
  ಅನ್ಯಥಾ
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered");
  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_assumption_clauses (c_parser *parser, ತಾರ್ಕಿಕ is_assume)
{
  ತಾರ್ಕಿಕ no_openmp = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ no_openmp_constructs = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ no_openmp_routines = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ no_parallelism = ಅಸತ್ಯ;
  bitmap_head absent_head, contains_head;

  bitmap_obstack_initialize (ರಿಕ್ತ);
  bitmap_initialize (&absent_head, &bitmap_default_obstack);
  bitmap_initialize (&contains_head, &bitmap_default_obstack);

  ಯದಿ (c_parser_next_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME))
	ಭಙ್ಗ;

      ಧ್ರುವ ವರ್ಣ *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      location_t cloc = c_parser_peek_token (parser)->location;

      ಯದಿ (!strcmp (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  ಯದಿ (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = ಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  ಯದಿ (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = ಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  ಯದಿ (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = ಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  ಯದಿ (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = ಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  ಯದಿ (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_ಅಭಿವ್ಯಕ್ತಿ_no_commas (parser, ರಿಕ್ತ);
	      ವೃಕ್ಷ t = convert_lvalue_to_rvalue (eloc, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ, ಸತ್ಯ).ಮೌಲ್ಯ;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, ಅಸತ್ಯ, ರಿಕ್ತ);
	      ಯದಿ (is_assume && t != error_mark_ಗಂಟು)
		{
		  ವೃಕ್ಷ fn = build_call_ಅಭಿವ್ಯಕ್ತಿ_internal_loc (eloc, IFN_ASSUME,
							  void_type_ಗಂಟು, 1,
							  t);
		  add_stmt (fn);
		}
	      parens.skip_until_found_close (parser);
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (!strcmp (p, "absent") || !strcmp (p, "contains"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  ಯದಿ (parens.require_open (parser))
	    {
	      ಕುರು
		{
		  ಧ್ರುವ ವರ್ಣ *directive[3] = {};
		  ಪೂರ್ಣಾಙ್ಕ i;
		  location_t dloc = c_parser_peek_token (parser)->location;
		  ಪ್ರತಿ (i = 0; i < 3; i++)
		    {
		      ವೃಕ್ಷ id;
		      ಯದಿ (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->ಮೌಲ್ಯ;
		      ಅನ್ಯಥಾ ಯದಿ (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  ಗಣನಾ rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      ಅನ್ಯಥಾ
			ಭಙ್ಗ;
		      directive[i] = IDENTIFIER_POINTER (id);
		    }
		  ಯದಿ (i == 0)
		    error_at (dloc, "expected directive name");
		  ಅನ್ಯಥಾ
		    {
		      ಧ್ರುವ ಸಂರಚನಾ c_omp_directive *dir
			= c_omp_categorize_directive (directive[0],
						      directive[1],
						      directive[2]);
		      ಯದಿ (dir
			  && dir->id != PRAGMA_OMP_END
			  && (dir->kind == C_OMP_DIR_DECLARATIVE
			      || dir->kind == C_OMP_DIR_INFORMATIONAL
			      || dir->kind == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      ಅನ್ಯಥಾ ಯದಿ (dir == ರಿಕ್ತ
			       || dir->id == PRAGMA_OMP_END
			       || (!dir->second && directive[1])
			       || (!dir->third && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      ಅನ್ಯಥಾ
			{
			  ಪೂರ್ಣಾಙ್ಕ id = dir - c_omp_directives;
			  ಯದಿ (bitmap_bit_p (p[0] == 'a' ? &contains_head
							: &absent_head, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  ಅನ್ಯಥಾ ಯದಿ (!bitmap_set_bit (p[0] == 'a'
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
		      ಪ್ರತಿ (; i; --i)
			c_parser_consume_token (parser);
		    }
		  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  ಅನ್ಯಥಾ
		    ಭಙ್ಗ;
		}
	      ಯಾವತ್ (1);
	      parens.skip_until_found_close (parser);
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      matching_parens parens;
	      parens.consume_open (parser);
	      c_parser_balanced_token_sequence (parser);
	      parens.require_close (parser);
	    }
	}
      ಅನ್ಯಥಾ
	{
	  c_parser_consume_token (parser);
	  error_at (cloc, "expected assumption clause");
	  ಭಙ್ಗ;
	}
    }
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_assume (c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  c_parser_omp_assumption_clauses (parser, ಸತ್ಯ);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
}

/* OpenMP 5.1
   #pragma omp assumes clauses[optseq] new-line  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_assumes (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_omp_assumption_clauses (parser, ಅಸತ್ಯ);
}

/* Helper function for c_parser_omp_metadirective.  */

ಸ್ಥಿರ ಶೂನ್ಯ
analyze_metadirective_body (c_parser *parser,
			    vec<c_token> &tokens,
			    vec<ವೃಕ್ಷ> &labels)
{
  ಪೂರ್ಣಾಙ್ಕ nesting_depth = 0;
  ಪೂರ್ಣಾಙ್ಕ bracket_depth = 0;
  ತಾರ್ಕಿಕ ignore_label = ಅಸತ್ಯ;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  ಯಾವತ್ (1)
    {
      c_token *token = c_parser_peek_token (parser);
      ತಾರ್ಕಿಕ stop = ಅಸತ್ಯ;

      ಯದಿ (c_parser_next_token_is_keyword (parser, RID_CASE))
	ignore_label = ಸತ್ಯ;

      ವಿಕಲ್ಪ (token->type)
	{
	ಪಕ್ಷ CPP_EOF:
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_NAME:
	  ಯದಿ (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.safe_ತಳ್ಳು (token->ಮೌಲ್ಯ);
	  ಗಚ್ಛ add;
	ಪಕ್ಷ CPP_OPEN_BRACE:
	  ++nesting_depth;
	  ಗಚ್ಛ add;
	ಪಕ್ಷ CPP_CLOSE_BRACE:
	  ಯದಿ (--nesting_depth == 0 && bracket_depth == 0)
	    stop = ಸತ್ಯ;
	  ಗಚ್ಛ add;
	ಪಕ್ಷ CPP_OPEN_PAREN:
	  ++bracket_depth;
	  ಗಚ್ಛ add;
	ಪಕ್ಷ CPP_CLOSE_PAREN:
	  --bracket_depth;
	  ಗಚ್ಛ add;
	ಪಕ್ಷ CPP_COLON:
	  ignore_label = ಅಸತ್ಯ;
	  ಗಚ್ಛ add;
	ಪಕ್ಷ CPP_SEMICOLON:
	  ಯದಿ (nesting_depth == 0 && bracket_depth == 0)
	    stop = ಸತ್ಯ;
	  ಗಚ್ಛ add;
	ಸ್ವಭಾವ:
	add:
	  tokens.safe_ತಳ್ಳು (*token);
	  ಯದಿ (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  ಅನ್ಯಥಾ ಯದಿ (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_to_pragma_eol (parser);
	  ಅನ್ಯಥಾ
	    c_parser_consume_token (parser);
	  ಯದಿ (stop)
	    ಭಙ್ಗ;
	  ಅನುವರ್ತ;
	}
      ಭಙ್ಗ;
    }
}

/* OpenMP 5.0:

  # pragma omp metadirective [clause[, clause]]
*/

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_metadirective (c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  ಸ್ಥಿರ unsigned ಪೂರ್ಣಾಙ್ಕ metadirective_region_ಎಣಿಕೆ = 0;

  ವೃಕ್ಷ ret;
  auto_vec<c_token> directive_tokens;
  auto_vec<c_token> body_tokens;
  auto_vec<ವೃಕ್ಷ> body_labels;
  auto_vec<ಧ್ರುವ ಸಂರಚನಾ c_omp_directive *> directives;
  auto_vec<ವೃಕ್ಷ> ctxs;
  vec<ಸಂರಚನಾ omp_variant> candidates;
  ತಾರ್ಕಿಕ default_seen = ಅಸತ್ಯ;
  ಪೂರ್ಣಾಙ್ಕ directive_token_idx = 0;
  ವೃಕ್ಷ standalone_body = NULL_ವೃಕ್ಷ;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  ತಾರ್ಕಿಕ requires_body = ಅಸತ್ಯ;

  ret = make_ಗಂಟು (OMP_METADIRECTIVE);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret, pragma_loc);
  ವೃಕ್ಷ_TYPE (ret) = void_type_ಗಂಟು;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_ವೃಕ್ಷ;

  c_parser_consume_pragma (parser);
  ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ಯದಿ (c_parser_next_token_is_not (parser, CPP_NAME)
	  && c_parser_next_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  ಗಚ್ಛ error;
	}

      location_t match_loc = c_parser_peek_token (parser)->location;
      ಧ್ರುವ ವರ್ಣ *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      ಯದಿ (strcmp (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.add_fixit_replace (match_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      ತಾರ್ಕಿಕ default_p
	= strcmp (p, "default") == 0 || strcmp (p, "otherwise") == 0;
      ಯದಿ (default_p)
	{
	  ಯದಿ (default_seen)
	    {
	      error_at (match_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      ಗಚ್ಛ error;
	    }
	  default_seen = ಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (default_seen)
	{
	  error_at (match_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  ಗಚ್ಛ error;
	}
      ಯದಿ (!default_p && strcmp (p, "when") != 0)
	{
	  error_at (match_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  ಗಚ್ಛ error;
	}

      matching_parens parens;
      ವೃಕ್ಷ ctx = NULL_ವೃಕ್ಷ;
      ತಾರ್ಕಿಕ skip = ಅಸತ್ಯ;

      ಯದಿ (!parens.require_open (parser))
	ಗಚ್ಛ error;

      ಯದಿ (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_ವೃಕ್ಷ);
	  ಯದಿ (ctx == error_mark_ಗಂಟು)
	    ಗಚ್ಛ error;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  ಯದಿ (ctx == error_mark_ಗಂಟು)
	    ಗಚ್ಛ error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_ವೃಕ್ಷ, ಅಸತ್ಯ) == 0);

	  ಯದಿ (c_parser_next_token_is_not (parser, CPP_COLON))
	    {
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      ಗಚ್ಛ error;
	    }
	  c_parser_consume_token (parser);
	}

      /* Read in the directive type and create a dummy pragma token for
	 it.  */
      location_t loc = c_parser_peek_token (parser)->location;

      ಧ್ರುವ ವರ್ಣ *directive[3] = {};
      ಪೂರ್ಣಾಙ್ಕ i;
      ಪ್ರತಿ (i = 0; i < 3; i++)
	{
	  ವೃಕ್ಷ id;
	  ಯದಿ (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      ಯದಿ (i == 0)
		directive[i++] = "nothing";
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->ಮೌಲ್ಯ;
	  ಅನ್ಯಥಾ ಯದಿ (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      ಗಣನಾ rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  ಅನ್ಯಥಾ
	    ಭಙ್ಗ;

	  directive[i] = IDENTIFIER_POINTER (id);
	}
      ಯದಿ (i == 0)
	{
	  error_at (loc, "expected directive name");
	  ಗಚ್ಛ error;
	}

      ಧ್ರುವ ಸಂರಚನಾ c_omp_directive *omp_directive
	= c_omp_categorize_directive (directive[0],
				      directive[1],
				      directive[2]);

      ಯದಿ (omp_directive == ರಿಕ್ತ)
	{
	  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < i; j++)
	    c_parser_consume_token (parser);
	  c_parser_error (parser, "unknown directive name");
	  ಗಚ್ಛ error;
	}
      ಅನ್ಯಥಾ
	{
	  ಪೂರ್ಣಾಙ್ಕ token_ಎಣಿಕೆ = 0;
	  ಯದಿ (omp_directive->first) token_ಎಣಿಕೆ++;
	  ಯದಿ (omp_directive->second) token_ಎಣಿಕೆ++;
	  ಯದಿ (omp_directive->third) token_ಎಣಿಕೆ++;
	  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < token_ಎಣಿಕೆ; j++)
	    c_parser_consume_token (parser);
	}
      ಯದಿ (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  ಗಚ್ಛ error;
	}
      ಯದಿ (omp_directive->kind == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  ಗಚ್ಛ error;
	}
      ಯದಿ (omp_directive->kind == C_OMP_DIR_CONSTRUCT)
	requires_body = ಸತ್ಯ;

      ಯದಿ (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_kind = (ಗಣನಾ pragma_kind) omp_directive->id;

	  directives.safe_ತಳ್ಳು (omp_directive);
	  directive_tokens.safe_ತಳ್ಳು (pragma_token);
	  ctxs.safe_ತಳ್ಳು (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      ಪೂರ್ಣಾಙ್ಕ nesting_depth = 0;
      ಯಾವತ್ (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ವಿಕಲ್ಪ (token->type)
	    {
	    ಪಕ್ಷ CPP_EOF:
	    ಪಕ್ಷ CPP_PRAGMA_EOL:
	      ಭಙ್ಗ;
	    ಪಕ್ಷ CPP_OPEN_PAREN:
	      ++nesting_depth;
	      ಗಚ್ಛ add;
	    ಪಕ್ಷ CPP_CLOSE_PAREN:
	      ಯದಿ (nesting_depth-- == 0)
		{
		  c_parser_consume_token (parser);
		  ಭಙ್ಗ;
		}
	      ಗಚ್ಛ add;
	    ಸ್ವಭಾವ:
	    add:
	      ಯದಿ (!skip)
		directive_tokens.safe_ತಳ್ಳು (*token);
	      c_parser_consume_token (parser);
	      ಅನುವರ್ತ;
	    }
	  ಭಙ್ಗ;
	}

      ಯದಿ (!skip)
	{
	  c_token eol_token;
	  memset (&eol_token, 0, ಪರಿಮಾಣ (eol_token));
	  eol_token.type = CPP_PRAGMA_EOL;
	  directive_tokens.safe_ತಳ್ಳು (eol_token);
	}
    }
  c_parser_skip_to_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  ಯದಿ (ctxs.length () == 1)
    {
      ವೃಕ್ಷ ctx = ctxs[0];
      ಯದಿ (ctx == NULL_ವೃಕ್ಷ
	  || (omp_context_selector_matches (ctx, NULL_ವೃಕ್ಷ, ಅಸತ್ಯ) == 1
	      && directive_tokens[0].pragma_kind == PRAGMA_OMP_NOTHING))
	ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (!default_seen)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      ಧ್ರುವ ಸಂರಚನಾ c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", ರಿಕ್ತ, ರಿಕ್ತ);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_kind = PRAGMA_OMP_NOTHING;

      directives.safe_ತಳ್ಳು (omp_directive);
      directive_tokens.safe_ತಳ್ಳು (pragma_token);
      ctxs.safe_ತಳ್ಳು (NULL_ವೃಕ್ಷ);

      c_token eol_token;
      memset (&eol_token, 0, ಪರಿಮಾಣ (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_tokens.safe_ತಳ್ಳು (eol_token);
    }

  ಯದಿ (requires_body)
    analyze_metadirective_body (parser, body_tokens, body_labels);

  /* Process each candidate directive.  */
  unsigned i;
  ವೃಕ್ಷ ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> tokens;

      /* Add the directive tokens.  */
      ಕುರು
	tokens.safe_ತಳ್ಳು (directive_tokens [directive_token_idx++]);
      ಯಾವತ್ (tokens.last ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_tokens.is_empty ());
      ಪ್ರತಿ (unsigned j = 0; j < body_tokens.length (); j++)
	tokens.safe_ತಳ್ಳು (body_tokens[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, ಪರಿಮಾಣ (eof_token));
      eof_token.type = CPP_EOF;
      tokens.safe_ತಳ್ಳು (eof_token);
      tokens.safe_ತಳ್ಳು (eof_token);

      unsigned ಪೂರ್ಣಾಙ್ಕ old_tokens_avail = parser->tokens_avail;
      c_token *old_tokens = parser->tokens;
      ಸಂರಚನಾ omp_attribute_pragma_state *old_in_omp_attribute_pragma
	= parser->in_omp_attribute_pragma;
      ಸಂರಚನಾ omp_metadirective_parse_data *old_state
	= parser->omp_metadirective_state;

      ಸಂರಚನಾ omp_metadirective_parse_data new_state;
      new_state.body_labels = &body_labels;
      new_state.region_ಅಂಕೆ = ++metadirective_region_ಎಣಿಕೆ;

      parser->tokens = tokens.address ();
      parser->tokens_avail = tokens.length ();
      parser->in_omp_attribute_pragma = ರಿಕ್ತ;
      parser->omp_metadirective_state = &new_state;

      ಪೂರ್ಣಾಙ್ಕ prev_errorcount = errorcount;
      ವೃಕ್ಷ directive = c_begin_compound_stmt (ಸತ್ಯ);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_ವೃಕ್ಷ);
      directive = c_end_compound_stmt (pragma_loc, directive, ಸತ್ಯ);
      ತಾರ್ಕಿಕ standalone_p
	= directives[i]->kind == C_OMP_DIR_STANDALONE
	  || directives[i]->kind == C_OMP_DIR_UTILITY;
      ಯದಿ (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  ಯದಿ (standalone_body == NULL_ವೃಕ್ಷ)
	    {
	      standalone_body = ತಳ್ಳು_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = ತೆಗೆ_stmt_list (standalone_body);
	    }
	  ಅನ್ಯಥಾ
	    c_parser_skip_to_end_of_block_or_statement (parser, ಸತ್ಯ);
	}

      ವೃಕ್ಷ body = standalone_p ? standalone_body : NULL_ವೃಕ್ಷ;
      ವೃಕ್ಷ variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      ಯದಿ (errorcount == prev_errorcount)
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
  ಯದಿ (!candidates.is_empty ())
    ret = c_omp_expand_variant_construct (candidates);

  add_stmt (ret);
  ಪ್ರತ್ಯಾಗಮ;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  ಯದಿ (parser->in_pragma)
    c_parser_skip_to_pragma_eol (parser, ಅಸತ್ಯ);
}

/* Main entry point to parsing most OpenMP pragmas.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_construct (c_parser *parser, ತಾರ್ಕಿಕ *if_p)
{
  ಗಣನಾ pragma_kind p_kind;
  location_t loc;
  ವೃಕ್ಷ stmt;
  ವರ್ಣ p_name[ಪರಿಮಾಣ "#pragma omp teams distribute parallel for simd"];
  omp_clause_mask mask (0);

  loc = c_parser_peek_token (parser)->location;
  p_kind = c_parser_peek_token (parser)->pragma_kind;
  c_parser_consume_pragma (parser);

  ವಿಕಲ್ಪ (p_kind)
    {
    ಪಕ್ಷ PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, ಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ;
    ಪಕ್ಷ PRAGMA_OACC_CACHE:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_DATA:
      stmt = c_parser_oacc_data (loc, parser, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_HOST_DATA:
      stmt = c_parser_oacc_host_data (loc, parser, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_KERNELS:
    ಪಕ್ಷ PRAGMA_OACC_PARALLEL:
    ಪಕ್ಷ PRAGMA_OACC_SERIAL:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_kind, p_name, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_LOOP:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, mask, ರಿಕ್ತ, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OACC_WAIT:
      strcpy (p_name, "#pragma wait");
      stmt = c_parser_oacc_wait (loc, parser, p_name);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (loc, parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ;
    ಪಕ್ಷ PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (loc, parser, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_DISTRIBUTE:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_distribute (loc, parser, p_name, mask, ರಿಕ್ತ, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_FOR:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, mask, ರಿಕ್ತ, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_LOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, mask, ರಿಕ್ತ, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_MASKED:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, mask, ರಿಕ್ತ, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_MASTER:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, mask, ರಿಕ್ತ, if_p,
				  UNKNOWN_LOCATION);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_PARALLEL:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, mask, ರಿಕ್ತ, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_SECTIONS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, mask, ರಿಕ್ತ);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_SIMD:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, mask, ರಿಕ್ತ, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (loc, parser, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_TASK:
      stmt = c_parser_omp_task (loc, parser, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_TASKGROUP:
      stmt = c_parser_omp_taskgroup (loc, parser, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_TASKLOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_taskloop (loc, parser, p_name, mask, ರಿಕ್ತ, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_TEAMS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, mask, ರಿಕ್ತ, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_ASSUME:
      c_parser_omp_assume (parser, if_p);
      ಪ್ರತ್ಯಾಗಮ;
    ಪಕ್ಷ PRAGMA_OMP_TILE:
      stmt = c_parser_omp_tile (loc, parser, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_UNROLL:
      stmt = c_parser_omp_unroll (loc, parser, if_p);
      ಭಙ್ಗ;
    ಪಕ್ಷ PRAGMA_OMP_DISPATCH:
      stmt = c_parser_omp_dispatch (loc, parser);
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }

  ಯದಿ (stmt && stmt != error_mark_ಗಂಟು)
    gcc_assert (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt) != UNKNOWN_LOCATION);
}

/* OpenMP 6.0:
   # pragma omp groupprivate (variable-list) [device_type(...)]  */

#define OMP_GROUPPRIVATE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE) )

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_groupprivate (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  ವೃಕ್ಷ vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ರಿಕ್ತ);
  ವೃಕ್ಷ clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_MASK,
					   "#pragma omp groupprivate");
  /* TODO: Implies 'declare target local' with specified device_type, check for
     conflicts.  Check for other restrictions.  */
  (ಶೂನ್ಯ) vars;
  (ಶೂನ್ಯ) clauses;
  sorry_at (loc, "%<omp groupprivate%>");
}

/* OpenMP 2.5:
   # pragma omp threadprivate (variable-list) */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_omp_threadprivate (c_parser *parser)
{
  ವೃಕ್ಷ vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ರಿಕ್ತ);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  ಪ್ರತಿ (t = vars; t; t = ವೃಕ್ಷ_CHAIN (t))
    {
      ವೃಕ್ಷ v = ವೃಕ್ಷ_PURPOSE (t);
      loc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ವೃಕ್ಷ_ಮೌಲ್ಯ (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      ಯದಿ (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_USED (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      ಅನ್ಯಥಾ ಯದಿ (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_TYPE (v) == error_mark_ಗಂಟು)
	;
      ಅನ್ಯಥಾ ಯದಿ (! COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      ಅನ್ಯಥಾ
	{
	  ಯದಿ (! DECL_THREAD_LOCAL_P (v))
	    {
	      set_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      ಯದಿ (DECL_RTL_SET_P (v))
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_transaction_attributes (c_parser *parser)
{
  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    ಪ್ರತ್ಯಾಗಮ c_parser_gnu_attributes (parser);

  ಯದಿ (!c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  ಪ್ರತ್ಯಾಗಮ c_parser_std_attribute_specifier (parser, ಸತ್ಯ);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_transaction (c_parser *parser, ಗಣನಾ rid keyword)
{
  unsigned ಪೂರ್ಣಾಙ್ಕ old_in = parser->in_transaction;
  unsigned ಪೂರ್ಣಾಙ್ಕ this_in = 1, new_in;
  location_t loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  ಯದಿ (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  ಅನ್ಯಥಾ
    {
      attrs = c_parser_transaction_attributes (parser);
      ಯದಿ (attrs)
	this_in |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_in = this_in | (old_in & TM_STMT_ATTR_OUTER);

  parser->in_transaction = new_in;
  stmt = c_parser_compound_statement (parser);
  parser->in_transaction = old_in;

  ಯದಿ (flag_tm)
    stmt = c_finish_transaction (loc, stmt, this_in);
  ಅನ್ಯಥಾ
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  ಪ್ರತ್ಯಾಗಮ stmt;
}

/* Parse a __transaction_atomic or __transaction_relaxed expression
   (GCC Extension).

   transaction-expression:
     __transaction_atomic ( expression )
     __transaction_relaxed ( expression )
*/

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_transaction_expression (c_parser *parser, ಗಣನಾ rid keyword)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  unsigned ಪೂರ್ಣಾಙ್ಕ old_in = parser->in_transaction;
  unsigned ಪೂರ್ಣಾಙ್ಕ this_in = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  ಯದಿ (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  ಅನ್ಯಥಾ
    {
      attrs = c_parser_transaction_attributes (parser);
      ಯದಿ (attrs)
	this_in |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->in_transaction = this_in;
  matching_parens parens;
  ಯದಿ (parens.require_open (parser))
    {
      ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = c_parser_expression (parser).ಮೌಲ್ಯ;
      ret.original_type = ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ);
      ret.ಮೌಲ್ಯ = build1 (TRANSACTION_ಅಭಿವ್ಯಕ್ತಿ, ret.original_type, ಅಭಿವ್ಯಕ್ತಿ);
      ಯದಿ (this_in & TM_STMT_ATTR_RELAXED)
	TRANSACTION_ಅಭಿವ್ಯಕ್ತಿ_RELAXED (ret.ಮೌಲ್ಯ) = 1;
      SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret.ಮೌಲ್ಯ, loc);
      ret.original_code = TRANSACTION_ಅಭಿವ್ಯಕ್ತಿ;
      ret.m_decimal = 0;
      ಯದಿ (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ರಿಕ್ತ);
	  ಗಚ್ಛ error;
	}
    }
  ಅನ್ಯಥಾ
    {
     error:
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = ರಿಕ್ತ;
    }
  parser->in_transaction = old_in;

  ಯದಿ (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ret, loc, loc);

  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ವೃಕ್ಷ attrs;
  ತಾರ್ಕಿಕ is_outer = ಅಸತ್ಯ;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_attributes (parser);
  ಯದಿ (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  ಯದಿ (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      ಗಚ್ಛ ret_error;
    }
  ಅನ್ಯಥಾ ಯದಿ (parser->in_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      ಗಚ್ಛ ret_error;
    }
  ಅನ್ಯಥಾ ಯದಿ (is_outer)
    {
      ಯದಿ ((parser->in_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  ಗಚ್ಛ ret_error;
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (parser->in_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      ಗಚ್ಛ ret_error;
    }

  ಪ್ರತ್ಯಾಗಮ add_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  ಪ್ರತ್ಯಾಗಮ build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, error_mark_ಗಂಟು);
}

/* Parse a single source file.  */

ಶೂನ್ಯ
c_parse_file (ಶೂನ್ಯ)
{
  /* Use local storage to begin.  If the first token is a pragma, parse it.
     If it is #pragma GCC pch_preprocess, then this will load a PCH file
     which will cause garbage collection.  */
  c_parser tparser;

  memset (&tparser, 0, ಪರಿಮಾಣ tparser);
  tparser.translate_strings_p = ಸತ್ಯ;
  tparser.tokens = &tparser.tokens_buf[0];
  the_parser = &tparser;

  ಯದಿ (c_parser_peek_token (&tparser)->pragma_kind == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  ಅನ್ಯಥಾ
    c_common_no_more_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  ಯದಿ (tparser.tokens == &tparser.tokens_buf[0])
    the_parser->tokens = &the_parser->tokens_buf[0];

  /* Initialize EH, if we've been told to do so.  */
  ಯದಿ (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = ರಿಕ್ತ;
}

ಶೂನ್ಯ
c_init_preprocess (ಶೂನ್ಯ)
{
  /* Create a parser for use by pragma_lex during preprocessing.  */
  the_parser = ggc_alloc<c_parser> ();
  memset (the_parser, 0, ಪರಿಮಾಣ (c_parser));
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
c_parser_parse_rtl_body (c_parser *parser, ವರ್ಣ *start_with_pass)
{
  ಯದಿ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      ಮುಕ್ತ (start_with_pass);
      ಪ್ರತ್ಯಾಗಮ c_parser_peek_token (parser)->location;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_open_braces = 1;
  ಯಾವತ್ (1)
    {
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
	{
	ಪಕ್ಷ CPP_OPEN_BRACE:
	  ಅಂಕೆ_open_braces++;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_CLOSE_BRACE:
	  ಯದಿ (--ಅಂಕೆ_open_braces == 0)
	    ಗಚ್ಛ found_closing_brace;
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_EOF:
	  error_at (start_loc, "no closing brace");
	  ಮುಕ್ತ (start_with_pass);
	  ಪ್ರತ್ಯಾಗಮ c_parser_peek_token (parser)->location;
	ಸ್ವಭಾವ:
	  ಭಙ್ಗ;
	}
      c_parser_consume_token (parser);
    }

 found_closing_brace:
  /* At the closing brace; record its location.  */
  location_t end_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  ಯದಿ (!read_rtl_function_body_from_file_range (start_loc, end_loc))
    {
      ಮುಕ್ತ (start_with_pass);
      ಪ್ರತ್ಯಾಗಮ end_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  run_rtl_passes (start_with_pass);
  ಪ್ರತ್ಯಾಗಮ end_loc;
}

#ಅನ್ತರ್ಭಾವ "gt-c-c-parser.h"
