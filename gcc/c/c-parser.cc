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

#شامل "config.h"
#define INCLUDE_STRING
#شامل "system.h"
#شامل "coretypes.h"
#شامل "target.h"
#شامل "function.h"
#شامل "c-tree.h"
#شامل "timevar.h"
#شامل "stringpool.h"
#شامل "cgraph.h"
#شامل "attribs.h"
#شامل "stor-layout.h"
#شامل "varasm.h"
#شامل "trans-mem.h"
#شامل "c-family/c-pragma.h"
#شامل "c-lang.h"
#شامل "c-family/c-objc.h"
#شامل "plugin.h"
#شامل "omp-general.h"
#شامل "omp-offload.h"
#شامل "builtins.h"
#شامل "gomp-constants.h"
#شامل "c-family/c-indentation.h"
#شامل "gimple-expr.h"
#شامل "context.h"
#شامل "gcc-rich-location.h"
#شامل "c-parser.h"
#شامل "gimple-parser.h"
#شامل "read-rtl-function.h"
#شامل "run-rtl-passes.h"
#شامل "intl.h"
#شامل "c-family/name-hint.h"
#شامل "tree-iterator.h"
#شامل "tree-pretty-print.h"
#شامل "memmodel.h"
#شامل "c-family/known-headers.h"
#شامل "bitmap.h"
#شامل "analyzer/analyzer-language.h"
#شامل "toplev.h"
#شامل "asan.h"
#شامل "c-family/c-ubsan.h"
#شامل "gcc-urlifier.h"

/* We need to walk over decls with incomplete struct/union/enum types
   after parsing the whole translation unit.
   In finish_decl(), if the decl is static, has incomplete
   struct/union/enum type, it is appended to incomplete_record_decls.
   In c_parser_translation_unit(), we iterate over incomplete_record_decls
   and report error if any of the decls are still incomplete.  */

vec<درخت> incomplete_record_decls;

تهی
set_c_عبارت_source_range (c_عبارت *عبارت,
			 location_t start, location_t finish)
{
  عبارت->src_range.m_start = start;
  عبارت->src_range.m_finish = finish;
  اگر (عبارت->مقدار)
    set_source_range (عبارت->مقدار, start, finish);
}

تهی
set_c_عبارت_source_range (c_عبارت *عبارت,
			 source_range src_range)
{
  عبارت->src_range = src_range;
  اگر (عبارت->مقدار)
    set_source_range (عبارت->مقدار, src_range);
}


/* Initialization routine for this file.  */

تهی
c_parse_init (تهی)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  unsigned صحیح i;
  درخت id;
  صحیح mask = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  mask |= D_CXXONLY;
  اگر (!flag_isoc99)
    mask |= D_C99;
  اگر (!flag_isoc23)
    mask |= D_C23;
  اگر (flag_no_asm)
    {
      mask |= D_ASM | D_EXT;
      اگر (!flag_isoc99)
	mask |= D_EXT89;
      اگر (!flag_isoc23)
	mask |= D_EXT11;
    }
  اگر (!c_dialect_objc ())
    mask |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<درخت> ((صحیح) RID_MAX);
  برای (i = 0; i < رقم_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      اگر (c_common_reswords[i].disable & mask)
	{
	  اگر (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].word);
	      C_SET_RID_CODE (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_WORD (id) = 1;
	    }
	  ادامه;
	}

      id = get_identifier (c_common_reswords[i].word);
      C_SET_RID_CODE (id, c_common_reswords[i].rid);
      C_IS_RESERVED_WORD (id) = 1;
      ridpointers [(صحیح) c_common_reswords[i].rid] = id;
    }

  برای (i = 0; i < رقم_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      نویسه name[50];
      sprintf (name, "__int%d", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;

      sprintf (name, "__int%d__", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;
    }

  اگر (flag_openmp)
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
ساختار GTY(()) c_parser {
  /* The look-ahead tokens.  */
  c_token * GTY((skip)) tokens;
  /* Buffer for look-ahead tokens.  */
  c_token tokens_buf[4];
  /* How many look-ahead tokens are available (0 - 4, or
     more if parsing from pre-lexed tokens).  */
  unsigned صحیح tokens_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_tokens;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  unsigned صحیح raw_tokens_used;
  /* True if a syntax error is being recovered from; false otherwise.
     c_parser_error sets this flag.  It should clear this flag when
     enough tokens have been consumed to recover from the error.  */
  منطقی error : 1;
  /* True if we're processing a pragma, and shouldn't automatically
     consume CPP_PRAGMA_EOL.  */
  منطقی in_pragma : 1;
  /* True if we're parsing the outermost block of an if statement.  */
  منطقی in_if_block : 1;
  /* True if we want to lex a translated, joined string (for an
     initial #pragma pch_preprocess).  Otherwise the parser is
     responsible for concatenating strings and translating to the
     execution character set as needed.  */
  منطقی lex_joined_string : 1;
  /* True if, when the parser is concatenating string literals, it
     should translate them to the execution character set (false
     inside attributes).  */
  منطقی translate_strings_p : 1;

  /* Objective-C specific parser/lexer information.  */

  /* True if we are in a context where the Objective-C "PQ" keywords
     are considered keywords.  */
  منطقی objc_pq_context : 1;
  /* True if we are parsing a (potential) Objective-C foreach
     statement.  This is set to true after we parsed 'for (' and while
     we wait for 'in' or ';' to decide if it's a standard C for loop or an
     Objective-C foreach loop.  */
  منطقی objc_could_be_foreach_context : 1;
  /* The following flag is needed to contextualize Objective-C lexical
     analysis.  In some cases (e.g., 'int NSObject;'), it is
     undesirable to bind an identifier to an Objective-C class, even
     if a class with that name exists.  */
  منطقی objc_need_raw_identifier : 1;
  /* Nonzero if we're processing a __transaction statement.  The value
     is 1 | TM_STMT_ATTR_*.  */
  unsigned صحیح in_transaction : 4;
  /* True if we are in a context where the Objective-C "Property attribute"
     keywords are valid.  */
  منطقی objc_property_attr_context : 1;

  /* Whether we have just seen/constructed a string-literal.  Set when
     returning a string-literal from c_parser_string_literal.  Reset
     in consume_token.  Useful when we get a parse error and see an
     unknown token, which could have been a string-literal constant
     macro.  */
  منطقی seen_string_literal : 1;

  /* TRUE if omp::directive, omp::decl or omp::sequence attributes may not
     appear.  */
  منطقی omp_attrs_forbidden_p : 1;

  /* Location of the last consumed token.  */
  location_t last_token_location;

  /* Holds state for parsing collapsed OMP_FOR loops.  Managed by
     c_parser_omp_for_loop.  */
  ساختار omp_for_parse_data * GTY((skip)) omp_for_parse_state;

  /* If we're in the context of OpenMP directives written as C23
     attributes turned into pragma, the tokens field is temporarily
     redirected.  This holds data needed to restore state afterwards.
     It's NULL otherwise.  */
  ساختار omp_attribute_pragma_state *in_omp_attribute_pragma;

  /* Set for omp::decl attribute parsing to the decl to which it
     appertains.  */
  درخت in_omp_decl_attribute;

  /* Non-null only when parsing the body of an OpenMP metadirective.
     Managed by c_parser_omp_metadirective.  */
  ساختار omp_metadirective_parse_data * GTY((skip))
    omp_metadirective_state;
};

/* Holds data needed to restore the token stream to its previous state
   after parsing an OpenMP attribute-syntax pragma.  */
ساختار GTY(()) omp_attribute_pragma_state
{
  vec<c_token, va_gc> *token_vec;
  c_token * GTY((skip)) save_tokens;
  unsigned صحیح save_tokens_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
ساختار GTY(()) omp_begin_declare_variant_map_entry {
  درخت variant;		/* The variant decl.  */
  درخت id;		/* Name of base function.  */
  درخت ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_entry, va_gc> *omp_begin_declare_variant_map;

ایستا درخت omp_start_variant_function (c_declarator *, درخت);
ایستا تهی omp_finish_variant_function (درخت, درخت, درخت);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_tokens_buf (c_parser *parser, unsigned n)
{
  بازگشت &parser->tokens_buf[n];
}

/* Return the error state of PARSER.  */

منطقی
c_parser_error (c_parser *parser)
{
  بازگشت parser->error;
}

/* Set the error state of PARSER to ERR.  */

تهی
c_parser_set_error (c_parser *parser, منطقی err)
{
  parser->error = err;
}


/* The actual parser and external interface.  ??? Does this need to be
   garbage-collected?  */

ایستا GTY (()) c_parser *the_parser;

/* Read in and lex a single token, storing it in *TOKEN.  If RAW,
   context-sensitive postprocessing of the token is not done.  */

ایستا تهی
c_lex_one_token (c_parser *parser, c_token *token, منطقی raw = نادرست)
{
  timevar_افزودن (TV_LEX);

  اگر (raw || vec_safe_length (parser->raw_tokens) == 0)
    {
      token->type = c_lex_with_flags (&token->مقدار, &token->location,
				      &token->flags,
				      (parser->lex_joined_string
				       ? 0 : C_LEX_STRING_NO_JOIN));
      token->id_kind = C_ID_NONE;
      token->keyword = RID_MAX;
      token->pragma_kind = PRAGMA_NONE;
    }
  وگرنه
    {
      /* Use a token previously lexed as a raw look-ahead token, and
	 complete the processing on it.  */
      *token = (*parser->raw_tokens)[parser->raw_tokens_used];
      ++parser->raw_tokens_used;
      اگر (parser->raw_tokens_used == vec_safe_length (parser->raw_tokens))
	{
	  vec_free (parser->raw_tokens);
	  parser->raw_tokens_used = 0;
	}
    }

  اگر (raw)
    برو out;

  انتخاب (token->type)
    {
    حالت CPP_NAME:
      {
	درخت decl;

	منطقی objc_force_identifier = parser->objc_need_raw_identifier;
	اگر (c_dialect_objc ())
	  parser->objc_need_raw_identifier = نادرست;

	اگر (C_IS_RESERVED_WORD (token->مقدار))
	  {
	    شمارش rid rid_code = C_RID_CODE (token->مقدار);

	    اگر (rid_code == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->مقدار);
	      }
	    وگرنه اگر (rid_code >= RID_FIRST_ADDR_SPACE
		     && rid_code <= RID_LAST_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_code - RID_FIRST_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_kind = C_ID_ADDRSPACE;
		token->keyword = rid_code;
		بشکن;
	      }
	    وگرنه اگر (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		اگر (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    بشکن;
		  }
		وگرنه اگر (parser->objc_could_be_foreach_context
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
		    بشکن;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    وگرنه اگر (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		اگر (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    بشکن;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    وگرنه اگر (c_dialect_objc ()
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
	    وگرنه
	      {
		token->type = CPP_KEYWORD;
		token->keyword = rid_code;
		بشکن;
	      }
	  }

	decl = lookup_name (token->مقدار);
	اگر (decl)
	  {
	    اگر (درخت_CODE (decl) == TYPE_DECL)
	      {
		token->id_kind = C_ID_TYPENAME;
		بشکن;
	      }
	  }
	وگرنه اگر (c_dialect_objc ())
	  {
	    درخت objc_interface_decl = objc_is_class_name (token->مقدار);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    اگر (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->مقدار = objc_interface_decl;
		token->id_kind = C_ID_CLASSNAME;
		بشکن;
	      }
	  }
        token->id_kind = C_ID_ID;
      }
      بشکن;
    حالت CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      انتخاب (C_RID_CODE (token->مقدار))
	{
	  /* Replace 'class' with '@class', 'private' with '@private',
	     etc.  This prevents confusion with the C++ keyword
	     'class', and makes the tokens consistent with other
	     Objective-C 'AT' keywords.  For example '@class' is
	     reported as RID_AT_CLASS which is consistent with
	     '@synchronized', which is reported as
	     RID_AT_SYNCHRONIZED.
	  */
	حالت RID_CLASS:     token->keyword = RID_AT_CLASS; بشکن;
	حالت RID_PRIVATE:   token->keyword = RID_AT_PRIVATE; بشکن;
	حالت RID_PROTECTED: token->keyword = RID_AT_PROTECTED; بشکن;
	حالت RID_PUBLIC:    token->keyword = RID_AT_PUBLIC; بشکن;
	حالت RID_THROW:     token->keyword = RID_AT_THROW; بشکن;
	حالت RID_TRY:       token->keyword = RID_AT_TRY; بشکن;
	حالت RID_CATCH:     token->keyword = RID_AT_CATCH; بشکن;
	حالت RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; بشکن;
	پیشفرض:            token->keyword = C_RID_CODE (token->مقدار);
	}
      بشکن;
    حالت CPP_COLON:
    حالت CPP_COMMA:
    حالت CPP_CLOSE_PAREN:
    حالت CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      اگر (c_dialect_objc ())
	parser->objc_need_raw_identifier = نادرست;
      بشکن;
    حالت CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_kind = (شمارش pragma_kind) درخت_INT_CST_کم (token->مقدار);
      token->مقدار = پوچ;
      بشکن;
    پیشفرض:
      بشکن;
    }
 out:
  timevar_برداشت (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  اگر (parser->tokens_avail == 0)
    {
      c_lex_one_token (parser, &parser->tokens[0]);
      parser->tokens_avail = 1;
    }
  بازگشت &parser->tokens[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  اگر (parser->tokens_avail >= 2)
    بازگشت &parser->tokens[1];
  gcc_assert (parser->tokens_avail == 1);
  gcc_assert (parser->tokens[0].type != CPP_EOF);
  gcc_assert (parser->tokens[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->tokens[1]);
  parser->tokens_avail = 2;
  بازگشت &parser->tokens[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, unsigned صحیح n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  اگر (parser->tokens_avail >= n)
    بازگشت &parser->tokens[n - 1];
  gcc_assert (parser->tokens_avail == n - 1);
  c_lex_one_token (parser, &parser->tokens[n - 1]);
  parser->tokens_avail = n;
  بازگشت &parser->tokens[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, unsigned صحیح n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  اگر (parser->tokens_avail >= n)
    بازگشت &parser->tokens[n - 1];
  unsigned صحیح raw_len = vec_safe_length (parser->raw_tokens);
  unsigned صحیح raw_avail
    = parser->tokens_avail + raw_len - parser->raw_tokens_used;
  gcc_assert (raw_avail >= n - 1);
  اگر (raw_avail >= n)
    بازگشت &(*parser->raw_tokens)[parser->raw_tokens_used
				  + n - 1 - parser->tokens_avail];
  vec_safe_reserve (parser->raw_tokens, 1);
  parser->raw_tokens->quick_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_tokens)[raw_len], درست);
  بازگشت &(*parser->raw_tokens)[raw_len];
}

منطقی
c_keyword_starts_typename (شمارش rid keyword)
{
  انتخاب (keyword)
    {
    حالت RID_UNSIGNED:
    حالت RID_LONG:
    حالت RID_SHORT:
    حالت RID_SIGNED:
    حالت RID_COMPLEX:
    حالت RID_INT:
    حالت RID_CHAR:
    حالت RID_FLOAT:
    حالت RID_DOUBLE:
    حالت RID_VOID:
    حالت RID_DFLOAT32:
    حالت RID_DFLOAT64:
    حالت RID_DFLOAT128:
    حالت RID_DFLOAT64X:
    CASE_RID_FLOATN_NX:
    حالت RID_BOOL:
    حالت RID_BITINT:
    حالت RID_ENUM:
    حالت RID_STRUCT:
    حالت RID_UNION:
    حالت RID_TYPEOF:
    حالت RID_TYPEOF_UNQUAL:
    حالت RID_CONST:
    حالت RID_ATOMIC:
    حالت RID_VOLATILE:
    حالت RID_RESTRICT:
    حالت RID_ATTRIBUTE:
    حالت RID_FRACT:
    حالت RID_ACCUM:
    حالت RID_SAT:
    حالت RID_AUTO_TYPE:
    حالت RID_ALIGNAS:
      بازگشت درست;
    پیشفرض:
      اگر (keyword >= RID_FIRST_INT_N
	  && keyword < RID_FIRST_INT_N + رقم_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_FIRST_INT_N])
	بازگشت درست;
      بازگشت نادرست;
    }
}

/* Return true if TOKEN can start a type name,
   false otherwise.  */
منطقی
c_token_starts_typename (c_token *token)
{
  انتخاب (token->type)
    {
    حالت CPP_NAME:
      انتخاب (token->id_kind)
	{
	حالت C_ID_ID:
	  بازگشت نادرست;
	حالت C_ID_ADDRSPACE:
	  بازگشت درست;
	حالت C_ID_TYPENAME:
	  بازگشت درست;
	حالت C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  بازگشت درست;
	پیشفرض:
	  gcc_unreachable ();
	}
    حالت CPP_KEYWORD:
      بازگشت c_keyword_starts_typename (token->keyword);
    حالت CPP_LESS:
      اگر (c_dialect_objc ())
	بازگشت درست;
      بازگشت نادرست;
    پیشفرض:
      بازگشت نادرست;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

ایستا درونخطی منطقی
c_parser_next_tokens_start_typename (c_parser *parser, شمارش c_lookahead_kind la,
				     unsigned صحیح n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  اگر (c_token_starts_typename (token))
    بازگشت درست;

  /* Try a bit harder to detect an unknown typename.  */
  اگر (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_kind == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->مقدار))
    بازگشت درست;

  بازگشت نادرست;
}

/* Return true if TOKEN, after an open parenthesis, can start a
   compound literal (either a storage class specifier allowed in that
   context, or a type name), false otherwise.  */
ایستا منطقی
c_token_starts_compound_literal (c_token *token)
{
  انتخاب (token->type)
    {
    حالت CPP_KEYWORD:
      انتخاب (token->keyword)
	{
	حالت RID_CONSTEXPR:
	حالت RID_REGISTER:
	حالت RID_STATIC:
	حالت RID_THREAD:
	  بازگشت درست;
	پیشفرض:
	  بشکن;
	}
      /* Fall through.  */
    پیشفرض:
      بازگشت c_token_starts_typename (token);
    }
}

/* Return true if TOKEN is a type qualifier, false otherwise.  */
ایستا منطقی
c_token_is_qualifier (c_token *token)
{
  انتخاب (token->type)
    {
    حالت CPP_NAME:
      انتخاب (token->id_kind)
	{
	حالت C_ID_ADDRSPACE:
	  بازگشت درست;
	پیشفرض:
	  بازگشت نادرست;
	}
    حالت CPP_KEYWORD:
      انتخاب (token->keyword)
	{
	حالت RID_CONST:
	حالت RID_VOLATILE:
	حالت RID_RESTRICT:
	حالت RID_ATTRIBUTE:
	حالت RID_ATOMIC:
	  بازگشت درست;
	پیشفرض:
	  بازگشت نادرست;
	}
    حالت CPP_LESS:
      بازگشت نادرست;
    پیشفرض:
      gcc_unreachable ();
    }
}

/* Return true if the next token from PARSER is a type qualifier,
   false otherwise.  */
ایستا درونخطی منطقی
c_parser_next_token_is_qualifier (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  بازگشت c_token_is_qualifier (token);
}

/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes), false otherwise.  */
ایستا منطقی
c_token_starts_declspecs (c_token *token)
{
  انتخاب (token->type)
    {
    حالت CPP_NAME:
      انتخاب (token->id_kind)
	{
	حالت C_ID_ID:
	  بازگشت نادرست;
	حالت C_ID_ADDRSPACE:
	  بازگشت درست;
	حالت C_ID_TYPENAME:
	  بازگشت درست;
	حالت C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  بازگشت درست;
	پیشفرض:
	  gcc_unreachable ();
	}
    حالت CPP_KEYWORD:
      انتخاب (token->keyword)
	{
	حالت RID_STATIC:
	حالت RID_EXTERN:
	حالت RID_REGISTER:
	حالت RID_TYPEDEF:
	حالت RID_INLINE:
	حالت RID_NORETURN:
	حالت RID_AUTO:
	حالت RID_THREAD:
	حالت RID_UNSIGNED:
	حالت RID_LONG:
	حالت RID_SHORT:
	حالت RID_SIGNED:
	حالت RID_COMPLEX:
	حالت RID_INT:
	حالت RID_CHAR:
	حالت RID_FLOAT:
	حالت RID_DOUBLE:
	حالت RID_VOID:
	حالت RID_DFLOAT32:
	حالت RID_DFLOAT64:
	حالت RID_DFLOAT128:
	حالت RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	حالت RID_BOOL:
	حالت RID_BITINT:
	حالت RID_ENUM:
	حالت RID_STRUCT:
	حالت RID_UNION:
	حالت RID_TYPEOF:
	حالت RID_TYPEOF_UNQUAL:
	حالت RID_CONST:
	حالت RID_VOLATILE:
	حالت RID_RESTRICT:
	حالت RID_ATTRIBUTE:
	حالت RID_FRACT:
	حالت RID_ACCUM:
	حالت RID_SAT:
	حالت RID_ALIGNAS:
	حالت RID_ATOMIC:
	حالت RID_AUTO_TYPE:
	حالت RID_CONSTEXPR:
	  بازگشت درست;
	پیشفرض:
	  اگر (token->keyword >= RID_FIRST_INT_N
	      && token->keyword < RID_FIRST_INT_N + رقم_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_FIRST_INT_N])
	    بازگشت درست;
	  بازگشت نادرست;
	}
    حالت CPP_LESS:
      اگر (c_dialect_objc ())
	بازگشت درست;
      بازگشت نادرست;
    پیشفرض:
      بازگشت نادرست;
    }
}


/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes) or a static assertion, false
   otherwise.  */
ایستا منطقی
c_token_starts_declaration (c_token *token)
{
  اگر (c_token_starts_declspecs (token)
      || token->keyword == RID_STATIC_ASSERT)
    بازگشت درست;
  وگرنه
    بازگشت نادرست;
}

/* Return true if the next token from PARSER can start declaration
   specifiers (not including standard attributes), false
   otherwise.  */
منطقی
c_parser_next_token_starts_declspecs (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);

  /* In Objective-C, a classname normally starts a declspecs unless it
     is immediately followed by a dot.  In that case, it is the
     Objective-C 2.0 "dot-syntax" for class objects, ie, calls the
     setter/getter on the class.  c_token_starts_declspecs() can't
     differentiate between the two cases because it only checks the
     current token, so we have a special check here.  */
  اگر (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    بازگشت نادرست;

  بازگشت c_token_starts_declspecs (token);
}

ایستا منطقی c_parser_check_balanced_raw_token_sequence (c_parser *,
							unsigned صحیح *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
منطقی
c_parser_next_tokens_start_declaration (c_parser *parser, unsigned صحیح n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  اگر (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_DOT)
    بازگشت نادرست;

  /* Labels do not start declarations.  */
  اگر (token->type == CPP_NAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_COLON)
    بازگشت نادرست;

  /* A static assertion is only a declaration if followed by a semicolon;
     otherwise, it may be an expression in C2Y.  */
  اگر (token->keyword == RID_STATIC_ASSERT
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_PAREN)
    {
      n += 2;
      اگر (!c_parser_check_balanced_raw_token_sequence (parser, &n)
	  || c_parser_peek_nth_token_raw (parser, n)->type != CPP_CLOSE_PAREN)
	/* Invalid static assertion syntax; treat as a declaration and report a
	   syntax error there.  */
	بازگشت درست;
      بازگشت c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  اگر (c_token_starts_declaration (token))
    بازگشت درست;

  اگر (c_parser_next_tokens_start_typename (parser, cla_nonabstract_decl, n))
    بازگشت درست;

  بازگشت نادرست;
}

/* Consume the next token from PARSER.  */

تهی
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
  اگر (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  وگرنه اگر (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      اگر (parser->tokens_avail >= 3)
        {
          parser->tokens[1] = parser->tokens[2];
          اگر (parser->tokens_avail >= 4)
            parser->tokens[2] = parser->tokens[3];
        }
    }
  parser->tokens_avail--;
  parser->seen_string_literal = نادرست;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

ایستا تهی
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->in_pragma);
  gcc_assert (parser->tokens_avail >= 1);
  gcc_assert (parser->tokens[0].type == CPP_PRAGMA);
  اگر (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  وگرنه اگر (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      اگر (parser->tokens_avail >= 3)
	parser->tokens[1] = parser->tokens[2];
    }
  parser->tokens_avail--;
  parser->in_pragma = درست;
}

/* Update the global input_location from TOKEN.  */
ایستا درونخطی تهی
c_parser_set_source_position_from_token (c_token *token)
{
  اگر (token->type != CPP_EOF)
    {
      درون_داد_location = token->location;
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

ایستا منطقی
c_parser_peek_conflict_marker (c_parser *parser, شمارش cpp_ttype tok1_kind,
			       location_t *out_loc)
{
  c_token *token2 = c_parser_peek_2nd_token (parser);
  اگر (token2->type != tok1_kind)
    بازگشت نادرست;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  اگر (token3->type != tok1_kind)
    بازگشت نادرست;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  اگر (token4->type != conflict_marker_get_final_tok_kind (tok1_kind))
    بازگشت نادرست;

  /* It must be at the start of the line.  */
  location_t start_loc = c_parser_peek_token (parser)->location;
  اگر (LOCATION_COLUMN (start_loc) != 1)
    بازگشت نادرست;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t finish_loc = get_finish (token4->location);
  *out_loc = make_location (start_loc, start_loc, finish_loc);

  بازگشت درست;
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

ایستا منطقی
c_parser_error_richloc (c_parser *parser, ثابت نویسه *gmsgid,
			rich_location *richloc)
{
  c_token *token = c_parser_peek_token (parser);
  اگر (parser->error)
    بازگشت نادرست;
  parser->error = درست;
  اگر (!gmsgid)
    بازگشت نادرست;

  /* If this is actually a conflict marker, report it as such.  */
  اگر (token->type == CPP_LSHIFT
      || token->type == CPP_RSHIFT
      || token->type == CPP_EQ_EQ)
    {
      location_t loc;
      اگر (c_parser_peek_conflict_marker (parser, token->type, &loc))
	{
	  error_at (loc, "version control conflict marker in file");
	  بازگشت درست;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_group d;
  name_hint h;
  اگر (parser->seen_string_literal && token->type == CPP_NAME)
    {
      درخت name = token->مقدار;
      ثابت نویسه *token_name = IDENTIFIER_POINTER (name);
      ثابت نویسه *header_hint
	= get_c_stdlib_header_for_string_macro_name (token_name);
      اگر (header_hint != پوچ)
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
		 token->مقدار, /*flags=*/0, richloc);
  بازگشت درست;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

منطقی
c_parser_error (c_parser *parser, ثابت نویسه *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_set_source_position_from_token (token);
  rich_location richloc (سطر_table, درون_داد_location);
  بازگشت c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

template <typename traits_t>
رده token_pair
{
 عمومی:
  /* token_pair's ctor.  */
  token_pair () : m_open_loc (UNKNOWN_LOCATION) {}

  /* If the next token is the opening symbol for this pair, consume it and
     return true.
     Otherwise, issue an error and return false.
     In either case, record the location of the opening token.  */

  منطقی require_open (c_parser *parser)
  {
    c_token *token = c_parser_peek_token (parser);
    اگر (token)
      m_open_loc = token->location;

    بازگشت c_parser_require (parser, traits_t::open_token_type,
			     traits_t::open_gmsgid);
  }

  /* Consume the next token from PARSER, recording its location as
     that of the opening token within the pair.  */

  تهی consume_open (c_parser *parser)
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

  منطقی require_close (c_parser *parser) ثابت
  {
    بازگشت c_parser_require (parser, traits_t::close_token_type,
			     traits_t::close_gmsgid, m_open_loc);
  }

  /* Like token_pair::require_close, except that tokens will be skipped
     until the desired token is found.  An error message is still produced
     if the next token is not as expected.  */

  تهی skip_until_found_close (c_parser *parser) ثابت
  {
    c_parser_skip_until_found (parser, traits_t::close_token_type,
			       traits_t::close_gmsgid, m_open_loc);
  }

 خصوصی:
  location_t m_open_loc;
};

/* Traits for token_pair<T> for tracking matching pairs of parentheses.  */

ساختار matching_paren_traits
{
  ایستا ثابت شمارش cpp_ttype open_token_type = CPP_OPEN_PAREN;
  ایستا ثابت نویسه * ثابت open_gmsgid;
  ایستا ثابت شمارش cpp_ttype close_token_type = CPP_CLOSE_PAREN;
  ایستا ثابت نویسه * ثابت close_gmsgid;
};

ثابت نویسه * ثابت matching_paren_traits::open_gmsgid = "expected %<(%>";
ثابت نویسه * ثابت matching_paren_traits::close_gmsgid = "expected %<)%>";

/* "matching_parens" is a token_pair<T> class for tracking matching
   pairs of parentheses.  */

تعریفنوع token_pair<matching_paren_traits> matching_parens;

/* Traits for token_pair<T> for tracking matching pairs of braces.  */

ساختار matching_brace_traits
{
  ایستا ثابت شمارش cpp_ttype open_token_type = CPP_OPEN_BRACE;
  ایستا ثابت نویسه * ثابت open_gmsgid;
  ایستا ثابت شمارش cpp_ttype close_token_type = CPP_CLOSE_BRACE;
  ایستا ثابت نویسه * ثابت close_gmsgid;
};

ثابت نویسه * ثابت matching_brace_traits::open_gmsgid = "expected %<{%>";
ثابت نویسه * ثابت matching_brace_traits::close_gmsgid = "expected %<}%>";

/* "matching_braces" is a token_pair<T> class for tracking matching
   pairs of braces.  */

تعریفنوع token_pair<matching_brace_traits> matching_braces;

/* Get a description of the matching symbol to TYPE e.g. "(" for
   CPP_CLOSE_PAREN.  */

ایستا ثابت نویسه *
get_matching_نماد (شمارش cpp_ttype type)
{
  انتخاب (type)
    {
    پیشفرض:
      gcc_unreachable ();
    حالت CPP_CLOSE_PAREN:
      بازگشت "(";
    حالت CPP_CLOSE_BRACE:
      بازگشت "{";
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

منطقی
c_parser_require (c_parser *parser,
		  شمارش cpp_ttype type,
		  ثابت نویسه *msgid,
		  location_t matching_location,
		  منطقی type_is_unique)
{
  اگر (c_parser_next_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      بازگشت درست;
    }
  وگرنه
    {
      location_t next_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (next_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      اگر (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->last_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      منطقی added_matching_location = نادرست;
      اگر (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.add_location_if_nearby (*global_dc, matching_location);

      اگر (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	اگر (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_نماد (type));

      بازگشت نادرست;
    }
}

/* If the next token is the indicated keyword, consume it.  Otherwise,
   issue the error MSGID.  Returns true if found, false otherwise.  */

ایستا منطقی
c_parser_require_keyword (c_parser *parser,
			  شمارش rid keyword,
			  ثابت نویسه *msgid)
{
  اگر (c_parser_next_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      بازگشت درست;
    }
  وگرنه
    {
      c_parser_error (parser, msgid);
      بازگشت نادرست;
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

تهی
c_parser_skip_until_found (c_parser *parser,
			   شمارش cpp_ttype type,
			   ثابت نویسه *msgid,
			   location_t matching_location)
{
  unsigned nesting_depth = 0;

  اگر (c_parser_require (parser, type, msgid, matching_location))
    {
      اگر (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->in_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  اگر (token->type == CPP_EOF)
	    {
	      parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	      parser->tokens_avail
		= parser->in_omp_attribute_pragma->save_tokens_avail;
	      parser->in_omp_attribute_pragma = پوچ;
	    }
	}
      بازگشت;
    }

  /* Skip tokens until the desired token is found.  */
  وقتی (درست)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      اگر (token->type == type && !nesting_depth)
	{
	  c_parser_consume_token (parser);
	  اگر (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->in_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      اگر (token->type == CPP_EOF)
		{
		  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
		  parser->tokens_avail
		    = parser->in_omp_attribute_pragma->save_tokens_avail;
		  parser->in_omp_attribute_pragma = پوچ;
		}
	    }
	  بشکن;
	}

      /* If we've run out of tokens, stop.  */
      اگر (token->type == CPP_EOF)
	بازگشت;
      اگر (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	بازگشت;
      اگر (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      وگرنه اگر (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  اگر (nesting_depth-- == 0)
	    بشکن;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = نادرست;
}

/* Skip tokens until the end of a parameter is found, but do not
   consume the comma, semicolon or closing delimiter.  */

ایستا تهی
c_parser_skip_to_end_of_parameter (c_parser *parser)
{
  unsigned nesting_depth = 0;

  وقتی (درست)
    {
      c_token *token = c_parser_peek_token (parser);
      اگر ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_depth)
	بشکن;
      /* If we've run out of tokens, stop.  */
      اگر (token->type == CPP_EOF)
	بازگشت;
      اگر (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	بازگشت;
      اگر (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      وگرنه اگر (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  اگر (nesting_depth-- == 0)
	    بشکن;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = نادرست;
}

/* Skip tokens until a non-nested closing curly brace is the next
   token, or there are no more tokens. Return true in the first case,
   false otherwise.  */

ایستا منطقی
c_parser_skip_to_closing_brace (c_parser *parser)
{
  unsigned nesting_depth = 0;

  وقتی (درست)
    {
      c_token *token = c_parser_peek_token (parser);

      انتخاب (token->type)
	{
	حالت CPP_PRAGMA_EOL:
	  اگر (!parser->in_pragma)
	    بشکن;
	  /* FALLTHRU */
	حالت CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  بازگشت نادرست;

	حالت CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  اگر (nesting_depth-- == 0)
	    بازگشت درست;
	  بشکن;

	حالت CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  بشکن;

	پیشفرض:
	  بشکن;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Expect to be at the end of the pragma directive and consume an
   end of line marker.  */

ایستا تهی
c_parser_skip_to_pragma_eol (c_parser *parser, منطقی error_if_not_eol = درست)
{
  gcc_assert (parser->in_pragma);
  parser->in_pragma = نادرست;

  اگر (error_if_not_eol && c_parser_peek_token (parser)->type != CPP_PRAGMA_EOL)
    c_parser_error (parser, "expected end of line");

  cpp_ttype token_type;
  انجامبده
    {
      c_token *token = c_parser_peek_token (parser);
      token_type = token->type;
      اگر (token_type == CPP_EOF)
	بشکن;
      c_parser_consume_token (parser);
    }
  وقتی (token_type != CPP_PRAGMA_EOL);

  اگر (parser->in_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (token->type == CPP_EOF)
	{
	  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	  parser->tokens_avail
	    = parser->in_omp_attribute_pragma->save_tokens_avail;
	  parser->in_omp_attribute_pragma = پوچ;
	}
    }

  parser->error = نادرست;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
ایستا تهی
c_parser_skip_to_pragma_omp_end_declare_variant (c_parser *parser)
{
  برای (صحیح depth = 0; depth >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      انتخاب (token->type)
	{
	حالت CPP_PRAGMA_EOL:
	  اگر (!parser->in_pragma)
	    بشکن;
	  /* FALLTHRU */
	حالت CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  بازگشت;

	حالت CPP_PRAGMA:
	  اگر ((token->pragma_kind == PRAGMA_OMP_BEGIN
	       || token->pragma_kind == PRAGMA_OMP_END)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      درخت id1 = c_parser_peek_nth_token (parser, 2)->مقدار;
	      درخت id2 = c_parser_peek_nth_token (parser, 3)->مقدار;
	      اگر (strcmp (IDENTIFIER_POINTER (id1), "declare") == 0
		  && strcmp (IDENTIFIER_POINTER (id2), "variant") == 0)
		{
		  اگر (token->pragma_kind == PRAGMA_OMP_BEGIN)
		    depth++;
		  وگرنه
		    depth--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, نادرست);
	  ادامه;

	پیشفرض:
	  بشکن;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Skip tokens until we have consumed an entire block, or until we
   have consumed a non-nested ';'.  */

ایستا تهی
c_parser_skip_to_end_of_block_or_statement (c_parser *parser,
					    منطقی metadirective_p = نادرست)
{
  unsigned nesting_depth = 0;
  صحیح bracket_depth = 0;
  منطقی save_error = parser->error;

  وقتی (درست)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      انتخاب (token->type)
	{
	حالت CPP_EOF:
	  بازگشت;

	حالت CPP_PRAGMA_EOL:
	  اگر (parser->in_pragma)
	    بازگشت;
	  بشکن;

	حالت CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  اگر (!nesting_depth && (!metadirective_p || bracket_depth <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      برو finished;
	    }
	  بشکن;

	حالت CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  اگر ((nesting_depth == 0 || --nesting_depth == 0)
	      && (!metadirective_p || bracket_depth <= 0))
	    {
	      c_parser_consume_token (parser);
	      برو finished;
	    }
	  بشکن;

	حالت CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  بشکن;

	حالت CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  اگر (metadirective_p && nesting_depth == 0)
	    ++bracket_depth;
	  بشکن;

	حالت CPP_CLOSE_PAREN:
	  اگر (metadirective_p && nesting_depth == 0)
	    --bracket_depth;
	  بشکن;

	حالت CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, نادرست);
	  parser->error = save_error;
	  ادامه;

	پیشفرض:
	  بشکن;
	}

      c_parser_consume_token (parser);
    }

 finished:
  parser->error = نادرست;
}

/* CPP's options (initialized by c-opts.cc).  */
بیرونی cpp_options *cpp_opts;

/* Save the warning flags which are controlled by __extension__.  */

ایستا درونخطی صحیح
disable_extension_diagnostics (تهی)
{
  صحیح ret = (pedantic
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
  بازگشت ret;
}

/* Restore the warning flags which are controlled by __extension__.
   FLAGS is the return value from disable_extension_diagnostics.  */

ایستا درونخطی تهی
restore_extension_diagnostics (صحیح flags)
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
ساختار oacc_routine_data {
  منطقی error_seen; /* Set if error has been reported.  */
  منطقی fndecl_seen; /* Set if one fn decl/definition has been seen already.  */
  درخت clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
ایستا درخت objc_foreach_break_label, objc_foreach_continue_label;

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
ساختار omp_for_parse_data {
  شمارش درخت_code code;
  درخت declv, condv, incrv, initv;
  درخت pre_body;
  درخت bindings;
  صحیح شمار;	/* Expected nesting depth.  */
  صحیح depth;	/* Current nesting depth.  */
  location_t for_loc;
  منطقی ordered : 1;
  منطقی inscan : 1;
  منطقی want_nested_loop : 1;
  منطقی in_intervening_code : 1;
  منطقی saw_intervening_code: 1;
  منطقی perfect_nesting_fail : 1;
  منطقی fail : 1;
};

ساختار attr_state
{
  /* True if we parsed a musttail attribute for return.  */
  منطقی musttail_p;

  تهی reset () { musttail_p = نادرست; }
};

ایستا منطقی c_parser_nth_token_starts_std_attributes (c_parser *,
						      unsigned صحیح);
ایستا درخت c_parser_std_attribute_specifier_sequence (c_parser *);
ایستا تهی c_parser_external_declaration (c_parser *);
ایستا تهی c_parser_asm_definition (c_parser *);
ایستا درخت c_parser_declaration_or_fndef (c_parser *, منطقی, منطقی, منطقی,
					   منطقی, منطقی, منطقی, درخت * = پوچ,
					   vec<c_token> * = پوچ,
					   منطقی have_attrs = نادرست,
					   درخت attrs = پوچ,
					   ساختار oacc_routine_data * = پوچ,
					   منطقی * = پوچ);
ایستا منطقی c_parser_handle_statement_omp_attributes (c_parser *, درخت &,
						      منطقی *);
ایستا تهی c_parser_static_assert_declaration_no_semi (c_parser *);
ایستا تهی c_parser_static_assert_declaration (c_parser *);
ایستا ساختار c_typespec c_parser_enum_specifier (c_parser *);
ایستا ساختار c_typespec c_parser_struct_or_union_specifier (c_parser *);
ایستا درخت c_parser_struct_declaration (c_parser *, درخت *);
ایستا ساختار c_typespec c_parser_typeof_specifier (c_parser *);
ایستا درخت c_parser_alignas_specifier (c_parser *);
ایستا ساختار c_declarator *c_parser_direct_declarator (c_parser *, منطقی,
							c_dtr_syn, منطقی *);
ایستا ساختار c_declarator *c_parser_direct_declarator_inner (c_parser *,
							      منطقی,
							      ساختار c_declarator *);
ایستا ساختار c_arg_info *c_parser_parms_declarator (c_parser *, منطقی, درخت,
						     منطقی);
ایستا ساختار c_arg_info *c_parser_parms_list_declarator (c_parser *, درخت,
							  درخت, منطقی);
ایستا ساختار c_parm *c_parser_parameter_declaration (c_parser *, درخت, منطقی);
ایستا درخت c_parser_asm_string_literal (c_parser *);
ایستا درخت c_parser_simple_asm_عبارت (c_parser *);
ایستا درخت c_parser_gnu_attributes (c_parser *);
ایستا ساختار c_عبارت c_parser_initializer (c_parser *, درخت);
ایستا ساختار c_عبارت c_parser_braced_init (c_parser *, درخت, منطقی,
					   ساختار obstack *, منطقی);
ایستا تهی c_parser_initelt (c_parser *, ساختار obstack *);
ایستا تهی c_parser_initval (c_parser *, ساختار c_عبارت *,
			      ساختار obstack *);
ایستا درخت c_parser_compound_statement (c_parser *, location_t * = پوچ);
ایستا location_t c_parser_compound_statement_nostart (c_parser *);
ایستا تهی c_parser_label (c_parser *, درخت);
ایستا تهی c_parser_statement (c_parser *, منطقی *, location_t * = پوچ);
ایستا تهی c_parser_statement_after_labels (c_parser *, منطقی *, درخت,
					     vec<درخت> * = پوچ,
					     attr_state = {});
ایستا درخت c_parser_c99_block_statement (c_parser *, منطقی *,
					  location_t * = پوچ);
ایستا تهی c_parser_if_statement (c_parser *, منطقی *, vec<درخت> *);
ایستا تهی c_parser_switch_statement (c_parser *, منطقی *, درخت);
ایستا تهی c_parser_while_statement (c_parser *, منطقی, unsigned short, منطقی,
				      منطقی *, درخت);
ایستا تهی c_parser_do_statement (c_parser *, منطقی, unsigned short, منطقی,
				   درخت);
ایستا تهی c_parser_for_statement (c_parser *, منطقی, unsigned short, منطقی,
				    منطقی *, درخت);
ایستا درخت c_parser_asm_statement (c_parser *);
ایستا درخت c_parser_asm_operands (c_parser *);
ایستا درخت c_parser_asm_goto_operands (c_parser *);
ایستا درخت c_parser_asm_clobbers (c_parser *);
ایستا ساختار c_عبارت c_parser_عبارت_no_commas (c_parser *, ساختار c_عبارت *,
					      درخت = NULL_درخت);
ایستا ساختار c_عبارت c_parser_conditional_expression (c_parser *,
						      ساختار c_عبارت *, درخت);
ایستا ساختار c_عبارت c_parser_دودویی_expression (c_parser *, ساختار c_عبارت *,
						 درخت);
ایستا ساختار c_عبارت c_parser_cast_expression (c_parser *, ساختار c_عبارت *);
ایستا ساختار c_عبارت c_parser_unary_expression (c_parser *);
ایستا ساختار c_عبارت c_parser_sizeof_or_countof_expression (c_parser *,
							    شمارش rid);
ایستا ساختار c_عبارت c_parser_alignof_expression (c_parser *);
ایستا ساختار c_عبارت c_parser_maxof_or_minof_expression (c_parser *, شمارش rid);
ایستا ساختار c_عبارت c_parser_postfix_expression (c_parser *);
ایستا ساختار c_عبارت c_parser_postfix_expression_after_paren_type (c_parser *,
								   ساختار c_declspecs *,
								   ساختار c_type_name *,
								   location_t);
ایستا ساختار c_عبارت c_parser_postfix_expression_after_primary (c_parser *,
								location_t loc,
								ساختار c_عبارت);
ایستا درخت c_parser_transaction (c_parser *, شمارش rid);
ایستا ساختار c_عبارت c_parser_transaction_expression (c_parser *, شمارش rid);
ایستا درخت c_parser_transaction_cancel (c_parser *);
ایستا ساختار c_عبارت c_parser_expression (c_parser *);
ایستا ساختار c_عبارت c_parser_expression_conv (c_parser *);
ایستا vec<درخت, va_gc> *c_parser_عبارت_list (c_parser *, منطقی, منطقی,
					     vec<درخت, va_gc> **, location_t *,
					     درخت *, vec<location_t> *,
					     unsigned صحیح * = پوچ);
ایستا ساختار c_عبارت c_parser_has_attribute_expression (c_parser *);

ایستا تهی c_parser_oacc_declare (c_parser *);
ایستا تهی c_parser_oacc_enter_exit_data (c_parser *, منطقی);
ایستا تهی c_parser_oacc_update (c_parser *);
ایستا تهی c_parser_omp_construct (c_parser *, منطقی *);
ایستا تهی c_parser_omp_groupprivate (c_parser *);
ایستا تهی c_parser_omp_threadprivate (c_parser *);
ایستا تهی c_parser_omp_barrier (c_parser *);
ایستا تهی c_parser_omp_depobj (c_parser *);
ایستا تهی c_parser_omp_flush (c_parser *);
ایستا منطقی c_parser_omp_next_tokens_can_be_canon_loop (c_parser *,
							شمارش درخت_code, منطقی);
ایستا درخت c_parser_omp_loop_nest (c_parser *, منطقی *);
ایستا درخت c_parser_omp_for_loop (location_t, c_parser *, شمارش درخت_code,
				   درخت, درخت *, منطقی *);
ایستا تهی c_parser_omp_taskwait (c_parser *);
ایستا تهی c_parser_omp_taskyield (c_parser *);
ایستا تهی c_parser_omp_cancel (c_parser *);
ایستا تهی c_parser_omp_nothing (c_parser *);
ایستا تهی c_parser_omp_metadirective (c_parser *, منطقی *);

شمارش pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
ایستا منطقی c_parser_pragma (c_parser *, شمارش pragma_context, منطقی *, درخت);
ایستا منطقی c_parser_omp_cancellation_point (c_parser *, شمارش pragma_context);
ایستا منطقی c_parser_omp_target (c_parser *, شمارش pragma_context, منطقی *);
ایستا تهی c_parser_omp_begin (c_parser *);
ایستا تهی c_parser_omp_end (c_parser *);
ایستا منطقی c_parser_omp_declare (c_parser *, شمارش pragma_context);
ایستا تهی c_parser_omp_requires (c_parser *);
ایستا منطقی c_parser_omp_error (c_parser *, شمارش pragma_context);
ایستا تهی c_parser_omp_assumption_clauses (c_parser *, منطقی);
ایستا تهی c_parser_omp_allocate (c_parser *);
ایستا تهی c_parser_omp_assumes (c_parser *);
ایستا منطقی c_parser_omp_ordered (c_parser *, شمارش pragma_context, منطقی *);
ایستا درخت c_parser_omp_dispatch (location_t, c_parser *);
ایستا تهی c_parser_omp_interop (c_parser *);
ایستا تهی c_parser_oacc_routine (c_parser *, شمارش pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
ایستا تهی c_parser_objc_class_definition (c_parser *, درخت);
ایستا تهی c_parser_objc_class_instance_variables (c_parser *);
ایستا تهی c_parser_objc_class_declaration (c_parser *);
ایستا تهی c_parser_objc_alias_declaration (c_parser *);
ایستا تهی c_parser_objc_protocol_definition (c_parser *, درخت);
ایستا منطقی c_parser_objc_method_type (c_parser *);
ایستا تهی c_parser_objc_method_definition (c_parser *);
ایستا تهی c_parser_objc_methodprotolist (c_parser *);
ایستا تهی c_parser_objc_methodproto (c_parser *);
ایستا درخت c_parser_objc_method_decl (c_parser *, منطقی, درخت *, درخت *);
ایستا درخت c_parser_objc_type_name (c_parser *);
ایستا درخت c_parser_objc_protocol_refs (c_parser *);
ایستا تهی c_parser_objc_try_catch_finally_statement (c_parser *);
ایستا تهی c_parser_objc_synchronized_statement (c_parser *);
ایستا درخت c_parser_objc_selector (c_parser *);
ایستا درخت c_parser_objc_selector_arg (c_parser *);
ایستا درخت c_parser_objc_receiver (c_parser *);
ایستا درخت c_parser_objc_message_args (c_parser *);
ایستا درخت c_parser_objc_keywordexpr (c_parser *);
ایستا تهی c_parser_objc_at_property_declaration (c_parser *);
ایستا تهی c_parser_objc_at_synthesize_declaration (c_parser *);
ایستا تهی c_parser_objc_at_dynamic_declaration (c_parser *);
ایستا منطقی c_parser_objc_diagnose_bad_element_prefix
  (c_parser *, ساختار c_declspecs *);
ایستا location_t c_parser_parse_rtl_body (c_parser *, نویسه *);
ایستا درخت c_parser_handle_musttail (c_parser *, درخت, attr_state &);

#اگر ENABLE_ANALYZER

فضاینام ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

رده c_translation_unit : عمومی translation_unit
{
عمومی:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  درخت lookup_constant_by_id (درخت id) ثابت final override
  {
    /* Consider decls.  */
    اگر (درخت decl = lookup_name (id))
      اگر (درخت_CODE (decl) == CONST_DECL)
	اگر (درخت مقدار = DECL_INITIAL (decl))
	  اگر (درخت_CODE (مقدار) == INTEGER_CST)
	    بازگشت مقدار;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    اگر (cpp_macro_p (hashnode))
      اگر (درخت مقدار = consider_macro (hashnode->مقدار.macro))
	بازگشت مقدار;

    بازگشت NULL_درخت;
  }

  درخت
  lookup_type_by_id (درخت id) ثابت final override
  {
    اگر (درخت type_decl = lookup_name (id))
	اگر (درخت_CODE (type_decl) == TYPE_DECL)
	  {
	    درخت record_type = درخت_TYPE (type_decl);
	    اگر (درخت_CODE (record_type) == RECORD_TYPE)
	      بازگشت record_type;
	  }

    بازگشت NULL_درخت;
  }

  درخت
  lookup_global_var_by_id (درخت id) ثابت final override
  {
    اگر (درخت var_decl = lookup_name (id))
      اگر (درخت_CODE (var_decl) == VAR_DECL)
				بازگشت var_decl;

    بازگشت NULL_درخت;
  }

خصوصی:
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
  درخت consider_macro (cpp_macro *macro, صحیح depth = 0) ثابت
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (depth >= 0);

    اگر (macro->paramc > 0)
      بازگشت NULL_درخت;
    اگر (macro->kind != cmk_macro)
      بازگشت NULL_درخت;
    اگر (macro->شمار != 1)
      بازگشت NULL_درخت;
    ثابت cpp_token &tok = macro->exp.tokens[0];
    اگر (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	اگر (depth >= param_analyzer_max_macro_alias_depth)
	  بازگشت NULL_درخت;

	cpp_hashnode *alias = tok.val.گره.گره;
	اگر (cpp_macro_p (alias))
	  بازگشت consider_macro (alias->مقدار.macro, depth + 1);

	/* Not a simple alias.  */
	بازگشت NULL_درخت;
      }
    وگرنه اگر (tok.type != CPP_عدد)
      بازگشت NULL_درخت;

    cpp_reader *old_parse_in = parse_in;
    parse_in = cpp_create_reader (CLK_GNUC89, پوچ, سطر_table);

    pretty_printer pp;
    pp_string (&pp, (ثابت نویسه *) tok.val.str.text);
    pp_newline (&pp);
    cpp_افزودن_buffer (parse_in,
		     (ثابت unsigned نویسه *) pp_formatted_text (&pp),
		     strlen (pp_formatted_text (&pp)),
		     0);

    درخت مقدار;
    location_t loc;
    unsigned نویسه cpp_flags;
    c_lex_with_flags (&مقدار, &loc, &cpp_flags, 0);

    cpp_destroy (parse_in);
    parse_in = old_parse_in;

    اگر (مقدار && درخت_CODE (مقدار) == INTEGER_CST)
      بازگشت مقدار;

    بازگشت NULL_درخت;
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

ایستا تهی
c_parser_translation_unit (c_parser *parser)
{
  اگر (c_parser_next_token_is (parser, CPP_EOF))
    {
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C forbids an empty translation unit");
    }
  وگرنه
    {
      تهی *obstack_position = obstack_alloc (&parser_obstack, 0);
      mark_valid_location_for_stdc_pragma (نادرست);
      انجامبده
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      وقتی (c_parser_next_token_is_not (parser, CPP_EOF));
    }

  unsigned صحیح i;
  درخت decl;
  FOR_EACH_VEC_ELT (incomplete_record_decls, i, decl)
    اگر (DECL_SIZE (decl) == NULL_درخت && درخت_TYPE (decl) != error_mark_گره)
      error ("storage size of %q+D isn%'t known", decl);

  اگر (vec_safe_length (current_omp_declare_target_attribute))
    {
      c_omp_declare_target_attr
	a = current_omp_declare_target_attribute->برداشت ();
      اگر (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_safe_truncate (current_omp_declare_target_attribute, 0);
    }
  اگر (vec_safe_length (current_omp_begin_assumes))
    {
      اگر (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_safe_truncate (current_omp_begin_assumes, 0);
    }
  اگر (vec_safe_length (current_omp_declare_variant_attribute))
    {
      اگر (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_safe_truncate (current_omp_declare_variant_attribute, 0);
    }
  اگر (vec_safe_length (omp_begin_declare_variant_map))
    {
      unsigned صحیح i;
      omp_begin_declare_variant_map_entry *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_finish_variant_function (e->variant, e->id, e->ctx);
      vec_safe_truncate (omp_begin_declare_variant_map, 0);
    }

#اگر ENABLE_ANALYZER
  اگر (flag_analyzer)
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

ایستا تهی
c_parser_external_declaration (c_parser *parser)
{
  صحیح ext;
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_KEYWORD:
      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_EXTENSION:
	  ext = disable_extension_diagnostics ();
	  c_parser_consume_token (parser);
	  c_parser_external_declaration (parser);
	  restore_extension_diagnostics (ext);
	  بشکن;
	حالت RID_ASM:
	  c_parser_asm_definition (parser);
	  بشکن;
	حالت RID_AT_INTERFACE:
	حالت RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_definition (parser, NULL_درخت);
	  بشکن;
	حالت RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  بشکن;
	حالت RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  بشکن;
	حالت RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_protocol_definition (parser, NULL_درخت);
	  بشکن;
	حالت RID_AT_PROPERTY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_property_declaration (parser);
	  بشکن;
	حالت RID_AT_SYNTHESIZE:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_synthesize_declaration (parser);
	  بشکن;
	حالت RID_AT_DYNAMIC:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_dynamic_declaration (parser);
	  بشکن;
	حالت RID_AT_END:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_finish_implementation ();
	  بشکن;
	پیشفرض:
	  برو decl_or_fndef;
	}
      بشکن;
    حالت CPP_SEMICOLON:
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      بشکن;
    حالت CPP_PRAGMA:
      mark_valid_location_for_stdc_pragma (درست);
      c_parser_pragma (parser, pragma_external, پوچ, NULL_درخت);
      mark_valid_location_for_stdc_pragma (نادرست);
      بشکن;
    حالت CPP_PLUS:
    حالت CPP_MINUS:
      اگر (c_dialect_objc ())
	{
	  c_parser_objc_method_definition (parser);
	  بشکن;
	}
      /* Else fall through, and yield a syntax error trying to parse
	 as a declaration or function definition.  */
      /* FALLTHRU */
    پیشفرض:
    decl_or_fndef:
      /* A declaration or a function definition (or, in Objective-C,
	 an @interface or @protocol with prefix attributes).  We can
	 only tell which after parsing the declaration specifiers, if
	 any, and the first declarator.  */
      c_parser_declaration_or_fndef (parser, درست, درست, درست, نادرست, درست,
				     نادرست);
      بشکن;
    }
}

ایستا تهی c_parser_handle_directive_omp_attributes (درخت &, vec<c_token> *&,
						      vec<c_token> *);
ایستا تهی c_finish_omp_declare_simd (c_parser *, درخت, درخت, vec<c_token> *);
ایستا تهی c_finish_oacc_routine (ساختار oacc_routine_data *, درخت, منطقی);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

ایستا تهی
add_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  اگر (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    بازگشت;

  درخت stmt = build0 (DEBUG_BEGIN_STMT, void_type_گره);
  SET_عبارت_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

ایستا درخت
handle_assume_attribute (location_t here, درخت attrs, منطقی nested)
{
  اگر (nested)
    برای (درخت attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", درخت_CHAIN (attr)))
      {
	درخت args = درخت_مقدار (attr);
	صحیح nargs = list_length (args);
	اگر (nargs != 1)
	  {
	    error_at (here, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (here, "expected %i, found %i", 1, nargs);
	  }
	وگرنه
	  {
	    درخت arg = درخت_مقدار (args);
	    arg = c_objc_common_truthvalue_conversion (here, arg);
	    arg = c_fully_fold (arg, نادرست, پوچ);
	    اگر (arg != error_mark_گره)
	      {
		درخت fn = build_call_عبارت_internal_loc (here, IFN_ASSUME,
							void_type_گره, 1,
							arg);
		add_stmt (fn);
	      }
	  }
      }
  وگرنه
    pedwarn (here, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  بازگشت remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

ایستا تهی
c_parser_maybe_reclassify_token (c_parser *parser)
{
  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      اگر (token->id_kind == C_ID_ID || token->id_kind == C_ID_TYPENAME)
	{
	  درخت decl = lookup_name (token->مقدار);

	  token->id_kind = C_ID_ID;
	  اگر (decl)
	    {
	      اگر (درخت_CODE (decl) == TYPE_DECL)
		token->id_kind = C_ID_TYPENAME;
	    }
	  وگرنه اگر (c_dialect_objc ())
	    {
	      درخت objc_interface_decl = objc_is_class_name (token->مقدار);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      اگر (objc_interface_decl)
		{
		  token->مقدار = objc_interface_decl;
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

ایستا درخت
c_parser_declaration_or_fndef (c_parser *parser, منطقی fndef_ok,
			       منطقی static_assert_ok, منطقی empty_ok,
			       منطقی nested, منطقی start_attr_ok,
			       منطقی simple_ok,
			       درخت *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       منطقی have_attrs /* = false */,
			       درخت attrs /* = NULL_TREE */,
			       ساختار oacc_routine_data *oacc_routine_data
			       /* = NULL */,
			       منطقی *fallthru_attr_p /* = NULL */)
{
  ساختار c_declspecs *specs;
  درخت prefix_attrs;
  درخت all_prefix_attrs;
  منطقی diagnosed_no_specs = نادرست;
  location_t here = c_parser_peek_token (parser)->location;
  درخت result = NULL_درخت;

  add_debug_begin_stmt (c_parser_peek_token (parser)->location);

  اگر (static_assert_ok
      && c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      بازگشت result;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  اگر (have_attrs)
    {
      declspecs_add_attrs (here, specs, attrs);
      specs->non_std_attrs_seen_p = نادرست;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  اگر (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_kind == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->مقدار)))
    {
      درخت name = c_parser_peek_token (parser)->مقدار;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (here);
      اگر (tag_exists_p (RECORD_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.add_fixit_درج_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      وگرنه اگر (tag_exists_p (UNION_TYPE, name))
	{
	  richloc.add_fixit_درج_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      وگرنه اگر (tag_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.add_fixit_درج_before ("enum ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<enum%> keyword to refer to the type",
		    name);
	}
      وگرنه
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (name, FUZZY_LOOKUP_TYPENAME,
					      here);
	  اگر (ثابت نویسه *suggestion = hint.suggestion ())
	    {
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			name, suggestion);
	    }
	  وگرنه
	    error_at (here, "unknown type name %qE", name);
	}

      /* Parse declspecs normally to get a correct pointer type, but avoid
         a further "fails to be a type name" error.  Refuse nested functions
         since it is not how the user likely wants us to recover.  */
      c_parser_peek_token (parser)->type = CPP_KEYWORD;
      c_parser_peek_token (parser)->keyword = RID_VOID;
      c_parser_peek_token (parser)->مقدار = error_mark_گره;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  اگر (c_parser_nth_token_starts_std_attributes (parser, 1))
    have_attrs = درست;

  c_parser_declspecs (parser, specs, درست, درست, start_attr_ok,
		      درست, درست, start_attr_ok, درست, cla_nonabstract_decl);
  اگر (parser->error)
    {
      c_parser_skip_to_end_of_block_or_statement (parser);
      بازگشت result;
    }
  اگر (nested && !specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_end_of_block_or_statement (parser);
      بازگشت result;
    }

  finish_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  اگر (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_بالاترین_anonymous_type (specs->type);

  منطقی gnu_auto_type_p = specs->typespec_word == cts_auto_type;
  منطقی std_auto_type_p = specs->c23_auto_p;
  منطقی any_auto_type_p = gnu_auto_type_p || std_auto_type_p;
  gcc_assert (!(gnu_auto_type_p && std_auto_type_p));
  ثابت نویسه *auto_type_keyword = gnu_auto_type_p ? "__auto_type" : "auto";
  اگر (specs->constexpr_p)
    {
      /* An underspecified declaration may not declare tags or members
	 or structures or unions; it is undefined behavior to declare
	 the members of an enumeration.  Where the structure, union or
	 enumeration type is declared within an initializer, this is
	 diagnosed elsewhere.  Diagnose here the case of declaring
	 such a type in the type specifiers of a constexpr
	 declaration.  */
      انتخاب (specs->typespec_kind)
	{
	حالت ctsk_tagfirstref:
	حالت ctsk_tagfirstref_attrs:
	  error_at (here, "%qT declared in underspecified object declaration",
		    specs->type);
	  بشکن;

	حالت ctsk_tagdef:
	  error_at (here, "%qT defined in underspecified object declaration",
		    specs->type);
	  بشکن;

	پیشفرض:
	  بشکن;
	}
    }

  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      منطقی handled_assume = نادرست;
      اگر (specs->attrs
	  && !nested
	  && specs->typespec_kind == ctsk_none
	  && c_parser_handle_statement_omp_attributes (parser, specs->attrs,
						       پوچ))
	{
	  اگر (specs->attrs)
	    c_warn_unused_attributes (specs->attrs);
	  وقتی (parser->in_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_next_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, پوچ, NULL_درخت);
	    }
	  c_parser_consume_token (parser);
	  بازگشت result;
	}
      اگر (specs->typespec_kind == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = درست;
	  specs->attrs
	    = handle_assume_attribute (here, specs->attrs, nested);
	}
      اگر (any_auto_type_p)
	error_at (here, "%qs in empty declaration", auto_type_keyword);
      وگرنه اگر (specs->typespec_kind == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  اگر (fallthru_attr_p != پوچ)
	    *fallthru_attr_p = درست;
	  اگر (nested)
	    {
	      درخت fn = build_call_عبارت_internal_loc (here, IFN_FALLTHROUGH,
						      void_type_گره, 0);
	      add_stmt (fn);
	    }
	  وگرنه
	    pedwarn (here, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      وگرنه اگر (empty_ok
	       && !(have_attrs && specs->non_std_attrs_seen_p)
	       && !handled_assume)
	shadow_tag (specs);
      وگرنه
	{
	  shadow_tag_warned (specs, 1);
	  اگر (!handled_assume)
	    pedwarn (here, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      اگر (specs->عبارت)
	add_stmt (fold_convert (void_type_گره, specs->عبارت));
      c_parser_consume_token (parser);
      اگر (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, NULL_درخت, نادرست);
      بازگشت result;
    }
  وگرنه اگر (specs->typespec_kind == ctsk_none
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
      اگر (astate.musttail_p)
	{
	  اگر (specs->attrs)
	    {
	      auto_urlify_attributes sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, پوچ, NULL_درخت, پوچ,
					   astate);
	  بازگشت result;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  اگر (empty_ok
      && specs->typespec_kind == ctsk_tagdef
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = نادرست;
      shadow_tag_warned (specs, 1);
      بازگشت result;
    }
  وگرنه اگر (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      انتخاب (c_parser_peek_token (parser)->type)
	{
	  حالت CPP_PLUS:
	  حالت CPP_MINUS:
	    اگر (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      بازگشت result;
	    اگر (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_درخت;
	      }
	    اگر (fndef_ok)
	      c_parser_objc_method_definition (parser);
	    وگرنه
	      c_parser_objc_methodproto (parser);
	    بازگشت result;
	    بشکن;
	  پیشفرض:
	    بشکن;
	}
      /* This is where we parse 'attributes @interface ...',
	 'attributes @implementation ...', 'attributes @protocol ...'
	 (where attributes could be, for example, __attribute__
	 ((deprecated)).
      */
      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_AT_INTERFACE:
	  {
	    اگر (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      بازگشت result;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    بازگشت result;
	  }
	  بشکن;
	حالت RID_AT_IMPLEMENTATION:
	  {
	    اگر (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      بازگشت result;
	    اگر (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_درخت;
	      }
	    c_parser_objc_class_definition (parser, NULL_درخت);
	    بازگشت result;
	  }
	  بشکن;
	حالت RID_AT_PROTOCOL:
	  {
	    اگر (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      بازگشت result;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    بازگشت result;
	  }
	  بشکن;
	حالت RID_AT_ALIAS:
	حالت RID_AT_CLASS:
	حالت RID_AT_END:
	حالت RID_AT_PROPERTY:
	  اگر (specs->attrs)
	    {
	      c_parser_error (parser, "unexpected attribute");
	      specs->attrs = پوچ;
	    }
	  بشکن;
	پیشفرض:
	  بشکن;
	}
    }
  وگرنه اگر (attribute_fallthrough_p (specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  وگرنه اگر (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_attributes (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_درخت;
  منطقی more_than_one_decl = نادرست;
  وقتی (درست)
    {
      ساختار c_declarator *declarator;
      منطقی dummy = نادرست;
      timevar_id_t tv;
      درخت fnbody = NULL_درخت;
      درخت underspec_name = NULL_درخت;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_kind != ctsk_none,
					C_DTR_NORMAL, &dummy);
      اگر (declarator == پوچ)
	{
	  اگر (omp_declare_simd_clauses)
	    c_finish_omp_declare_simd (parser, NULL_درخت, NULL_درخت,
				       omp_declare_simd_clauses);
	  اگر (oacc_routine_data)
	    c_finish_oacc_routine (oacc_routine_data, NULL_درخت, نادرست);
	  /* This check is here purely to improve the diagnostic.  */
	  اگر (!simple_ok)
	    c_parser_skip_to_end_of_block_or_statement (parser);
	  بازگشت result;
	}
      اگر (flag_openmp || flag_openmp_simd)
	{
	  ساختار c_declarator *d = declarator;
	  وقتی (d->kind != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = پوچ;
	  c_parser_handle_directive_omp_attributes (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      اگر (gnu_auto_type_p && declarator->kind != cdk_id)
	{
	  error_at (here,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  بازگشت result;
	}
      اگر (std_auto_type_p)
	{
	  ساختار c_declarator *d = declarator;
	  وقتی (d->kind == cdk_attrs)
	    d = d->declarator;
	  اگر (d->kind != cdk_id)
	    {
	      error_at (here,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      بازگشت result;
	    }
	  underspec_name = d->u.id.id;
	}
      وگرنه اگر (specs->constexpr_p)
	{
	  ساختار c_declarator *d = declarator;
	  وقتی (d->kind != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      اگر (c_parser_next_token_is (parser, CPP_EQ)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is_keyword (parser, RID_ASM)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_next_token_is_keyword (parser, RID_IN))
	{
	  درخت asm_name = NULL_درخت;
	  درخت postfix_attrs = NULL_درخت;
	  اگر (!diagnosed_no_specs && !specs->declspecs_seen_p)
	    {
	      diagnosed_no_specs = درست;
	      pedwarn (here, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = نادرست;
	  اگر (c_parser_next_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_عبارت (parser);
	  اگر (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_attributes (parser);
	      اگر (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (here, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  بازگشت result;
		}
	    }
	  اگر (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      درخت d;
	      ساختار c_عبارت init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      اگر (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (سطر_table, init_loc);
		  unsigned صحیح underspec_state = 0;
		  اگر (std_auto_type_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  start_init (NULL_درخت, asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  اگر (nested && !empty_ok)
		    flag_sanitize = 0;
		  init = c_parser_عبارت_no_commas (parser, پوچ);
		  اگر (std_auto_type_p)
		    finish_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  اگر (gnu_auto_type_p
		      && درخت_CODE (init.مقدار) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (درخت_OPERAND (init.مقدار, 1)))
		    error_at (here,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_to_rvalue (init_loc, init, درست, درست,
						   درست);
		  درخت init_type = درخت_TYPE (init.مقدار);
		  منطقی vm_type = c_type_variably_modified_p (init_type);
		  اگر (vm_type)
		    init.مقدار = save_عبارت (init.مقدار);
		  finish_init ();
		  specs->typespec_kind = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = درست;
		  specs->type = init_type;
		  اگر (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_attributes (specs->type,
						  specs->postfix_attrs);
		      decl_attributes (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_درخت;
		    }
		  اگر (vm_type)
		    {
		      منطقی maybe_const = درست;
		      درخت type_عبارت = c_fully_fold (init.مقدار, نادرست,
						     &maybe_const);
		      specs->عبارت_const_operands &= maybe_const;
		      اگر (specs->عبارت)
			specs->عبارت = build2 (COMPOUND_عبارت,
					      درخت_TYPE (type_عبارت),
					      specs->عبارت, type_عبارت);
		      وگرنه
			specs->عبارت = type_عبارت;
		    }
		  d = start_decl (declarator, specs, درست,
				  chainon (postfix_attrs, all_prefix_attrs));
		  اگر (!d)
		    d = error_mark_گره;
		  اگر (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_درخت,
					       omp_declare_simd_clauses);
		  اگر (!omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_درخت,
					       &omp_dsimd_idattr_clauses);
		}
	      وگرنه
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (سطر_table, init_loc);
		  unsigned صحیح underspec_state = 0;
		  اگر (specs->constexpr_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  d = start_decl (declarator, specs, درست,
				  chainon (postfix_attrs,
					   all_prefix_attrs),
				  !specs->constexpr_p);
		  اگر (!d)
		    d = error_mark_گره;
		  اگر (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_درخت,
					       omp_declare_simd_clauses);
		  اگر (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_درخت,
					       &omp_dsimd_idattr_clauses);
		  start_init (d, asm_name,
			      درخت_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  اگر (درخت_CODE (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  اگر (specs->constexpr_p)
		    {
		      finish_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      اگر (omp_declare_simd_clauses)
			c_finish_omp_declare_simd (parser, d, NULL_درخت,
						   omp_declare_simd_clauses);
		  اگر (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_درخت,
					       &omp_dsimd_idattr_clauses);
		    }
		  finish_init ();
		}
	      اگر (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, نادرست);
	      اگر (d != error_mark_گره)
		{
		  maybe_warn_string_init (init_loc, درخت_TYPE (d), init);
		  finish_decl (d, init_loc, init.مقدار,
			       init.original_type, asm_name);
		  result = d;
		}
	    }
	  وگرنه
	    {
	      اگر (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  بازگشت result;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      درخت attrs = chainon (postfix_attrs, all_prefix_attrs);
	      درخت d = start_decl (declarator, specs, نادرست, attrs, درست,
				   &lastloc);
	      اگر (d && درخت_CODE (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  ثابت ساختار c_declarator *decl = declarator;
		  ثابت ساختار c_declarator *last_non_id_attrs = پوچ;

		  وقتی (decl)
		    انتخاب (decl->kind)
		      {
		      حالت cdk_array:
		      حالت cdk_function:
		      حالت cdk_pointer:
			last_non_id_attrs = decl;
			decl = decl->declarator;
			بشکن;

		      حالت cdk_attrs:
			decl = decl->declarator;
			بشکن;

		      حالت cdk_id:
			decl = 0;
			بشکن;

		      پیشفرض:
			gcc_unreachable ();
		      }

		  /* If it exists and is cdk_function declaration whose
		     arguments have not been set yet, use its arguments.  */
		  اگر (last_non_id_attrs
		      && last_non_id_attrs->kind == cdk_function)
		    {
		      درخت parms = last_non_id_attrs->u.arg_info->parms;
		      اگر (DECL_ARGUMENTS (d) == NULL_درخت
			  && DECL_INITIAL (d) == NULL_درخت)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      اگر (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_empty ())
		{
		  درخت parms = NULL_درخت;
		  اگر (d && درخت_CODE (d) == FUNCTION_DECL)
		    {
		      ساختار c_declarator *ce = declarator;
		      وقتی (ce != پوچ)
			اگر (ce->kind == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    بشکن;
			  }
			وگرنه
			  ce = ce->declarator;
		    }
		  اگر (parms)
		    temp_store_parm_decls (d, parms);
		  اگر (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  اگر (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  اگر (parms)
		    temp_برداشت_parm_decls ();
		}
	      اگر (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, نادرست);
	      اگر (d)
		finish_decl (d, UNKNOWN_LOCATION, NULL_درخت,
			     NULL_درخت, asm_name);

	      اگر (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  اگر (d)
		    *objc_foreach_object_declaration = d;
		  وگرنه
		    *objc_foreach_object_declaration = error_mark_گره;
		}
	    }
	  اگر (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      more_than_one_decl = درست;
	      اگر (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  بازگشت result;
		}
	      c_parser_consume_token (parser);
	      اگر (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
		all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					    prefix_attrs);
	      وگرنه
		all_prefix_attrs = prefix_attrs;
	      ادامه;
	    }
	  وگرنه اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      اگر (!simple_ok)
		c_parser_consume_token (parser);
	      بازگشت result;
	    }
	  وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      بازگشت result;
	    }
	  وگرنه
	    {
	      اگر (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      وگرنه اگر (more_than_one_decl)
		error_at (here, "declaration in condition can only declare "
			  "a single object");
	      بازگشت result;
	    }
	}
      وگرنه اگر (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (here,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  بازگشت result;
	}
      وگرنه اگر (!fndef_ok)
	{
	  اگر (simple_ok && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  وگرنه
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	    }
	  بازگشت result;
	}
      /* Function definition (nested or otherwise).  */
      اگر (nested)
	{
	  pedwarn (here, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_افزودن_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      درخت dv_base = NULL_درخت;
      درخت dv_ctx = NULL_درخت;
      اگر (!vec_safe_is_empty (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->last ();
	  dv_ctx = copy_list (a.selector);
	  dv_base = omp_start_variant_function (declarator, dv_ctx);
	}

      اگر (!start_function (specs, declarator, all_prefix_attrs))
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
	  اگر (c_parser_next_token_starts_declspecs (parser))
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
	      parser->error = نادرست;
	    }
	  وگرنه
	    {
	      /* This can appear in many cases looking nothing like a
		 function definition, so we don't give a more specific
		 error suggesting there was one.  */
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			      "or %<__attribute__%>");
	    }
	  اگر (nested)
	    c_برداشت_function_context ();
	  بشکن;
	}

      اگر (DECL_DECLARED_INLINE_P (current_function_decl))
        tv = TV_PARSE_INLINE;
      وگرنه
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
      صحیح save_debug_nonbind_markers_p = debug_nonbind_markers_p;
      debug_nonbind_markers_p = 0;
      c_parser_maybe_reclassify_token (parser);
      وقتی (c_parser_next_token_is_not (parser, CPP_EOF)
	     && c_parser_next_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, نادرست, نادرست, نادرست,
				       درست, نادرست, نادرست);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      اگر (omp_declare_simd_clauses)
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_درخت,
				   omp_declare_simd_clauses);
      اگر (!omp_dsimd_idattr_clauses.is_empty ())
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_درخت,
				   &omp_dsimd_idattr_clauses);
      اگر (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, current_function_decl, درست);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_start_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      اگر (dv_base && current_function_decl != error_mark_گره)
	{
	  omp_begin_declare_variant_map_entry e
	    = { current_function_decl, dv_base, dv_ctx };
	  vec_safe_افزودن (omp_begin_declare_variant_map, e);
	}

      /* If the definition was marked with __RTL, use the RTL parser now,
	 consuming the function body.  */
      اگر (specs->declspec_il == cdil_rtl)
	{
	  endloc = c_parser_parse_rtl_body (parser, specs->gimple_or_rtl_pass);

	  /* Normally, store_parm_decls sets next_is_function_body,
	     anticipating a function body.  We need a push_scope/pop_scope
	     pair to flush out this state, or subsequent function parsing
	     will go wrong.  */
	  افزودن_scope ();
	  برداشت_scope ();

	  finish_function (endloc);
	  بازگشت result;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      وگرنه اگر (specs->declspec_il != cdil_none)
	{
	  منطقی saved = in_late_دودویی_op;
	  in_late_دودویی_op = درست;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->entry_bb_شمار);
	  in_late_دودویی_op = saved;
	}
      وگرنه
	fnbody = c_parser_compound_statement (parser, &endloc);
      درخت fndecl = current_function_decl;
      اگر (nested && specs->declspec_il == cdil_none)
	{
	  درخت decl = current_function_decl;
	  /* Mark nested functions as needing static-chain initially.
	     lower_nested_functions will recompute it but the
	     DECL_STATIC_CHAIN flag is also used before that happens,
	     by initializer_constant_valid_p.  See gcc.dg/nested-fn-2.c.  */
	  DECL_STATIC_CHAIN (decl) = 1;
	  add_stmt (fnbody);
	  finish_function (endloc);
	  c_برداشت_function_context ();
	  add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_عبارت, decl));
	}
      وگرنه اگر (nested)
	{
	  اگر (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  وگرنه
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  finish_function (endloc);
	  c_برداشت_function_context ();
	}
      وگرنه
	{
	  اگر (fnbody)
	    add_stmt (fnbody);
	  finish_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      اگر (specs->declspec_il != cdil_none)
	DECL_SAVED_درخت (fndecl) = NULL_درخت;

      بشکن;
    }

  بازگشت result;
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

ایستا تهی
c_parser_asm_definition (c_parser *parser)
{
  location_t asm_loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  درخت asm_str = NULL_درخت;
  درخت outputs = NULL_درخت, inputs = NULL_درخت;
  اگر (!parens.require_open (parser))
    برو done;
  asm_str = c_parser_asm_string_literal (parser);
  اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      برو done;
    }
  برای (صحیح section = 0; section < 2; ++section)
    {
      اگر (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  اگر (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
	      asm_str = NULL_درخت;
	      برو done;
	    }
	  c_parser_consume_token (parser);
	}
      وگرنه اگر (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, نادرست))
	برو error_close_paren;
      اگر (!c_parser_next_token_is (parser, CPP_COLON)
	  && !c_parser_next_token_is (parser, CPP_SCOPE)
	  && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  اگر (section)
	    inputs = c_parser_asm_operands (parser);
	  وگرنه
	    outputs = c_parser_asm_operands (parser);
	}
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	بشکن;
    }

  اگر (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
      asm_str = NULL_درخت;
    }

  اگر (asm_str)
    asm_str = build_asm_عبارت (asm_loc, asm_str, outputs, inputs,
			      NULL_درخت, NULL_درخت, نادرست, نادرست);
done:
  اگر (asm_str)
    symtab->finalize_toplevel_asm (asm_str);
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse a static assertion (C11 6.7.10).

   static_assert-declaration:
     static_assert-declaration-no-semi ;
*/

ایستا تهی
c_parser_static_assert_declaration (c_parser *parser)
{
  c_parser_static_assert_declaration_no_semi (parser);
  اگر (parser->error
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

ایستا تهی
c_parser_static_assert_declaration_no_semi (c_parser *parser)
{
  location_t assert_loc, مقدار_loc;
  درخت مقدار;
  درخت string = NULL_درخت;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT));
  درخت spelling = c_parser_peek_token (parser)->مقدار;
  assert_loc = c_parser_peek_token (parser)->location;
  اگر (flag_isoc99)
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  وگرنه
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  c_parser_consume_token (parser);
  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت;
  location_t مقدار_tok_loc = c_parser_peek_token (parser)->location;
  مقدار = convert_lvalue_to_rvalue (مقدار_tok_loc,
				    c_parser_عبارت_no_commas (parser, پوچ),
				    درست, درست).مقدار;
  مقدار_loc = عبارت_LOC_OR_LOC (مقدار, مقدار_tok_loc);
  اگر (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_STRING:
	حالت CPP_STRING16:
	حالت CPP_STRING32:
	حالت CPP_WSTRING:
	حالت CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, نادرست, درست).مقدار;
	  بشکن;
	پیشفرض:
	  c_parser_error (parser, "expected string literal");
	  بازگشت;
	}
    }
  وگرنه اگر (flag_isoc11)
    /* If pedantic for pre-C11, the use of _Static_assert itself will
       have been diagnosed, so do not also diagnose the use of this
       new C23 feature of _Static_assert.  */
    pedwarn_c11 (assert_loc, OPT_Wpedantic,
		 "ISO C11 does not support omitting the string in "
		 "%qE", spelling);
  parens.require_close (parser);

  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (مقدار)))
    {
      error_at (مقدار_loc, "expression in static assertion is not an integer");
      بازگشت;
    }
  اگر (درخت_CODE (مقدار) != INTEGER_CST)
    {
      مقدار = c_fully_fold (مقدار, نادرست, پوچ);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (مقدار);
      اگر (درخت_CODE (مقدار) == INTEGER_CST)
	pedwarn (مقدار_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  اگر (درخت_CODE (مقدار) != INTEGER_CST)
    {
      error_at (مقدار_loc, "expression in static assertion is not constant");
      بازگشت;
    }
  constant_expression_warning (مقدار);
  اگر (integer_zerop (مقدار))
    {
      اگر (string)
	error_at (assert_loc, "static assertion failed: %E", string);
      وگرنه
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

تهی
c_parser_declspecs (c_parser *parser, ساختار c_declspecs *specs,
		    منطقی scspec_ok, منطقی typespec_ok, منطقی start_attr_ok,
		    منطقی alignspec_ok, منطقی auto_type_ok,
		    منطقی start_std_attr_ok, منطقی end_std_attr_ok,
		    شمارش c_lookahead_kind la)
{
  منطقی attrs_ok = start_attr_ok;
  منطقی seen_type = specs->typespec_kind != ctsk_none;

  اگر (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  اگر (start_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_seen_p);
      location_t loc = c_parser_peek_token (parser)->location;
      درخت attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_add_attrs (loc, specs, attrs);
      specs->non_std_attrs_seen_p = نادرست;
    }

  وقتی (c_parser_next_token_is (parser, CPP_NAME)
	 || c_parser_next_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_next_token_is (parser, CPP_LESS)))
    {
      ساختار c_typespec t;
      درخت attrs;
      درخت align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      اگر ((!typespec_ok || specs->typespec_kind == ctsk_tagdef)
	  && c_parser_next_tokens_start_typename (parser, la)
	  && !c_parser_next_token_is_qualifier (parser)
	  && !c_parser_next_token_is_keyword (parser, RID_ALIGNAS))
	بشکن;

      اگر (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  درخت مقدار = name_token->مقدار;
	  c_id_kind kind = name_token->id_kind;

	  اگر (kind == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_FIRST_ADDR_SPACE;
	      declspecs_add_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = درست;
	      ادامه;
	    }

	  gcc_assert (!c_parser_next_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  اگر (seen_type || !c_parser_next_tokens_start_typename (parser, la))
	    بشکن;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  seen_type = درست;
	  attrs_ok = درست;
	  اگر (kind == C_ID_ID)
	    {
	      auto_diagnostic_group d;
	      name_hint hint = lookup_name_fuzzy (مقدار, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      اگر (ثابت نویسه *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.add_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    مقدار, suggestion);
		}
	      وگرنه
		error_at (loc, "unknown type name %qE", مقدار);
	      t.kind = ctsk_typedef;
	      t.spec = error_mark_گره;
	    }
	  وگرنه اگر (kind == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_next_token_is_not (parser, CPP_LESS)))
	    {
	      t.kind = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (مقدار);
	    }
	  وگرنه
	    {
	      درخت proto = NULL_درخت;
	      gcc_assert (c_dialect_objc ());
	      t.kind = ctsk_objc;
	      اگر (c_parser_next_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (مقدار, proto);
	    }
	  t.عبارت = NULL_درخت;
	  t.عبارت_const_operands = درست;
	  t.has_enum_type_specifier = نادرست;
	  declspecs_add_type (name_token->location, specs, t);
	  ادامه;
	}
      اگر (c_parser_next_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  درخت proto;
	  gcc_assert (c_dialect_objc ());
	  اگر (!typespec_ok || seen_type)
	    بشکن;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.kind = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_درخت, proto);
	  t.عبارت = NULL_درخت;
	  t.عبارت_const_operands = درست;
	  t.has_enum_type_specifier = نادرست;
	  declspecs_add_type (loc, specs, t);
	  ادامه;
	}
      gcc_assert (c_parser_next_token_is (parser, CPP_KEYWORD));
      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_STATIC:
	حالت RID_EXTERN:
	حالت RID_REGISTER:
	حالت RID_TYPEDEF:
	حالت RID_INLINE:
	حالت RID_NORETURN:
	حالت RID_AUTO:
	حالت RID_THREAD:
	حالت RID_CONSTEXPR:
	  اگر (!scspec_ok)
	    برو out;
	  attrs_ok = درست;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_add_scspec (loc, specs,
				c_parser_peek_token (parser)->مقدار);
	  c_parser_consume_token (parser);
	  بشکن;
	حالت RID_AUTO_TYPE:
	  اگر (!auto_type_ok)
	    برو out;
	  /* Fall through.  */
	حالت RID_UNSIGNED:
	حالت RID_LONG:
	حالت RID_SHORT:
	حالت RID_SIGNED:
	حالت RID_COMPLEX:
	حالت RID_INT:
	حالت RID_CHAR:
	حالت RID_FLOAT:
	حالت RID_DOUBLE:
	حالت RID_VOID:
	حالت RID_DFLOAT32:
	حالت RID_DFLOAT64:
	حالت RID_DFLOAT128:
	حالت RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	حالت RID_BOOL:
	حالت RID_FRACT:
	حالت RID_ACCUM:
	حالت RID_SAT:
	حالت RID_INT_N_0:
	حالت RID_INT_N_1:
	حالت RID_INT_N_2:
	حالت RID_INT_N_3:
	  اگر (!typespec_ok)
	    برو out;
	  attrs_ok = درست;
	  seen_type = درست;
	  اگر (c_dialect_objc ())
	    parser->objc_need_raw_identifier = درست;
	  t.kind = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->مقدار;
	  t.عبارت = NULL_درخت;
	  t.عبارت_const_operands = درست;
	  t.has_enum_type_specifier = نادرست;
	  declspecs_add_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  بشکن;
	حالت RID_ENUM:
	  اگر (!typespec_ok)
	    برو out;
	  attrs_ok = درست;
	  seen_type = درست;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  بشکن;
	حالت RID_STRUCT:
	حالت RID_UNION:
	  اگر (!typespec_ok)
	    برو out;
	  attrs_ok = درست;
	  seen_type = درست;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  بشکن;
	حالت RID_TYPEOF:
	حالت RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  اگر (!typespec_ok || seen_type)
	    برو out;
	  attrs_ok = درست;
	  seen_type = درست;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_add_type (loc, specs, t);
	  بشکن;
	حالت RID_BITINT:
	  اگر (!typespec_ok)
	    برو out;
	  وگرنه
	    {
	      attrs_ok = درست;
	      seen_type = درست;
	      t.kind = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->مقدار;
	      t.عبارت = error_mark_گره;
	      t.عبارت_const_operands = درست;
	      t.has_enum_type_specifier = نادرست;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      اگر (parens.require_open (parser))
		{
		  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
		  t.عبارت = convert_lvalue_to_rvalue (loc, عبارت, درست,
						     درست).مقدار;
		  parens.skip_until_found_close (parser);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  بشکن;
	حالت RID_ATOMIC:
	  /* C parser handling of Objective-C constructs needs
	     checking for correct lvalue-to-rvalue conversions, and
	     the code in build_modify_expr handling various
	     Objective-C cases, and that in build_unary_op handling
	     Objective-C cases for increment / decrement, also needs
	     updating; uses of TYPE_MAIN_VARIANT in objc_compare_types
	     and objc_types_are_equivalent may also need updates.  */
	  اگر (c_dialect_objc ())
	    sorry ("%<_Atomic%> in Objective-C");
	  اگر (flag_isoc99)
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C99 does not support the %<_Atomic%> qualifier");
	  وگرنه
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C90 does not support the %<_Atomic%> qualifier");
	  attrs_ok = درست;
	  درخت مقدار;
	  مقدار = c_parser_peek_token (parser)->مقدار;
	  c_parser_consume_token (parser);
	  اگر (typespec_ok && c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      seen_type = درست;
	      c_parser_consume_token (parser);
	      ساختار c_type_name *type = c_parser_type_name (parser);
	      t.kind = ctsk_typeof;
	      t.spec = error_mark_گره;
	      t.عبارت = NULL_درخت;
	      t.عبارت_const_operands = درست;
	      t.has_enum_type_specifier = نادرست;
	      اگر (type != پوچ)
		t.spec = groktypename (type, &t.عبارت,
				       &t.عبارت_const_operands);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      اگر (t.spec != error_mark_گره)
		{
		  اگر (درخت_CODE (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  وگرنه اگر (درخت_CODE (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  وگرنه اگر (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  وگرنه
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  وگرنه
	    declspecs_add_qual (loc, specs, مقدار);
	  بشکن;
	حالت RID_CONST:
	حالت RID_VOLATILE:
	حالت RID_RESTRICT:
	  attrs_ok = درست;
	  declspecs_add_qual (loc, specs, c_parser_peek_token (parser)->مقدار);
	  c_parser_consume_token (parser);
	  بشکن;
	حالت RID_ATTRIBUTE:
	  اگر (!attrs_ok)
	    برو out;
	  attrs = c_parser_gnu_attributes (parser);
	  declspecs_add_attrs (loc, specs, attrs);
	  بشکن;
	حالت RID_ALIGNAS:
	  اگر (!alignspec_ok)
	    برو out;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_add_alignas (loc, specs, align);
	  بشکن;
	حالت RID_GIMPLE:
	  اگر (! flag_gimple)
	    error_at (loc, "%<__GIMPLE%> only valid with %<-fgimple%>");
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_gimple;
	  specs->locations[cdw_gimple] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  بشکن;
	حالت RID_RTL:
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_rtl;
	  specs->locations[cdw_rtl] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  بشکن;
	پیشفرض:
	  برو out;
	}
    }
 out:
  اگر (end_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    specs->postfix_attrs = c_parser_std_attribute_specifier_sequence (parser);
}

/* Complain about a non-CPP_NAME within an enumerator list.  */

ایستا تهی
report_bad_enum_name (c_parser *parser)
{
  اگر (!parser->error)
    {
      c_token *token = c_parser_peek_token (parser);
      انتخاب (token->type)
	{
	پیشفرض:
	  بشکن;
	حالت CPP_CLOSE_BRACE:
	  /* Give a nicer error for "enum {}".  */
	  error_at (token->location,
		    "empty enum is invalid");
	  parser->error = درست;
	  بازگشت;
	حالت CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  اگر (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_group d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_POINTER (token->مقدار));
	      add_note_about_new_keyword (token->location,
					  token->مقدار);
	      parser->error = درست;
	      بازگشت;
	    }
	  بشکن;
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

ایستا ساختار c_typespec
c_parser_enum_specifier (c_parser *parser)
{
  ساختار c_typespec ret;
  منطقی have_std_attrs;
  منطقی potential_nesting_p = نادرست;
  درخت std_attrs = NULL_درخت;
  درخت attrs;
  درخت ident = NULL_درخت;
  درخت fixed_underlying_type = NULL_درخت;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  اگر (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));
  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->مقدار;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  اگر (c_parser_next_token_is (parser, CPP_COLON)
      /* Distinguish an enum-type-specifier from a bit-field
	 declaration of the form "enum e : constant-expression;".  */
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      pedwarn_c11 (enum_loc, OPT_Wpedantic,
		   "ISO C does not support specifying %<enum%> underlying "
		   "types before C23");
      اگر (ident)
	{
	  /* The tag is in scope during the enum-type-specifier (which
	     may refer to the tag inside typeof).  */
	  ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, درست);
	  اگر (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_درخت == TYPE_مقادیر (ret.spec);
	}
      وگرنه
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_درخت;
	  ret.kind = ctsk_tagdef;
	  ret.عبارت = NULL_درخت;
	  ret.عبارت_const_operands = درست;
	  ret.has_enum_type_specifier = درست;
	}
      c_parser_consume_token (parser);
      ساختار c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, نادرست, درست, نادرست, نادرست, نادرست,
			  نادرست, درست, cla_prefer_id);
      finish_declspecs (specs);
      اگر (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      وگرنه اگر (درخت_CODE (specs->type) != INTEGER_TYPE
	       && درخت_CODE (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || درخت_CODE (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_گره;
	}
      وگرنه اگر (specs->restrict_p)
	error_at (enum_loc, "invalid use of %<restrict%>");
      fixed_underlying_type = TYPE_MAIN_VARIANT (specs->type);
      اگر (ident)
	{
	  /* The type specified must be consistent with any previously
	     specified underlying type.  If this is a newly declared
	     type, it is now a complete type.  */
	  اگر (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
	      && ENUM_UNDERLYING_TYPE (ret.spec) == NULL_درخت)
	    {
	      TYPE_MIN_مقدار (ret.spec) =
		TYPE_MIN_مقدار (fixed_underlying_type);
	      TYPE_MAX_مقدار (ret.spec) =
		TYPE_MAX_مقدار (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      SET_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_SIZE (ret.spec) = NULL_درخت;
	      TYPE_PRECISION (ret.spec) =
		TYPE_PRECISION (fixed_underlying_type);
	      ENUM_UNDERLYING_TYPE (ret.spec) = fixed_underlying_type;
	      layout_type (ret.spec);
	    }
	  وگرنه اگر (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
		   && !comptypes (fixed_underlying_type,
				  ENUM_UNDERLYING_TYPE (ret.spec)))
	    {
	      error_at (enum_loc, "%<enum%> underlying type incompatible with "
			"previous declaration");
	      fixed_underlying_type = ENUM_UNDERLYING_TYPE (ret.spec);
	    }
	}
    }
  اگر (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      ساختار c_enum_contents the_enum;
      درخت type;
      درخت postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      درخت مقادیر;
      timevar_افزودن (TV_PARSE_ENUM);
      type = start_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      مقادیر = NULL_درخت;
      c_parser_consume_token (parser);
      وقتی (درست)
	{
	  درخت enum_id;
	  درخت enum_مقدار;
	  درخت enum_decl;
	  منطقی seen_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, مقدار_loc;
	  اگر (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, پوچ);
	      مقادیر = error_mark_گره;
	      بشکن;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->مقدار;
	  /* Set the location in case we create a decl now.  */
	  c_parser_set_source_position_from_token (token);
	  decl_loc = مقدار_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  درخت std_attrs = NULL_درخت;
	  اگر (c_parser_nth_token_starts_std_attributes (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  درخت enum_attrs = chainon (std_attrs,
				     c_parser_gnu_attributes (parser));
	  اگر (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      مقدار_loc = c_parser_peek_token (parser)->location;
	      enum_مقدار = convert_lvalue_to_rvalue (مقدار_loc,
						     (c_parser_عبارت_no_commas
						      (parser, پوچ)),
						     درست, درست).مقدار;
	    }
	  وگرنه
	    enum_مقدار = NULL_درخت;
	  enum_decl = build_enumerator (decl_loc, مقدار_loc,
					&the_enum, enum_id, enum_مقدار);
	  اگر (enum_attrs)
	    decl_attributes (&درخت_PURPOSE (enum_decl), enum_attrs, 0);
	  درخت_CHAIN (enum_decl) = مقادیر;
	  مقادیر = enum_decl;
	  seen_comma = نادرست;
	  اگر (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      seen_comma = درست;
	      c_parser_consume_token (parser);
	    }
	  اگر (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      اگر (seen_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      بشکن;
	    }
	  اگر (!seen_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, پوچ);
	      مقادیر = error_mark_گره;
	      بشکن;
	    }
	}
      postfix_attrs = c_parser_gnu_attributes (parser);
      ret.spec = finish_enum (type, nreverse (مقادیر),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.kind = ctsk_tagdef;
      ret.عبارت = NULL_درخت;
      ret.عبارت_const_operands = درست;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_درخت;
      timevar_برداشت (TV_PARSE_ENUM);
      بازگشت ret;
    }
  وگرنه اگر (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_گره;
      ret.kind = ctsk_tagref;
      ret.عبارت = NULL_درخت;
      ret.عبارت_const_operands = درست;
      ret.has_enum_type_specifier = نادرست;
      بازگشت ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  اگر (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  اگر (fixed_underlying_type == NULL_درخت)
    {
      ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
			     std_attrs, نادرست);
      /* In ISO C, enumerated types without a fixed underlying type
	 can be referred to only if already defined.  */
      اگر (pedantic && !COMPLETE_TYPE_P (ret.spec))
	{
	  gcc_assert (ident);
	  pedwarn (enum_loc, OPT_Wpedantic,
		   "ISO C forbids forward references to %<enum%> types");
	}
    }
  بازگشت ret;
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

ایستا ساختار c_typespec
c_parser_struct_or_union_specifier (c_parser *parser)
{
  ساختار c_typespec ret;
  منطقی have_std_attrs;
  درخت std_attrs = NULL_درخت;
  درخت attrs;
  درخت ident = NULL_درخت;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  شمارش درخت_code code;
  انتخاب (c_parser_peek_token (parser)->keyword)
    {
    حالت RID_STRUCT:
      code = RECORD_TYPE;
      بشکن;
    حالت RID_UNION:
      code = UNION_TYPE;
      بشکن;
    پیشفرض:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  اگر (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->مقدار;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  اگر (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      رده c_struct_parse_info *struct_info;
      درخت type = start_struct (struct_loc, code, ident, &struct_info);
      درخت postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      درخت contents;
      درخت عبارت = پوچ;
      timevar_افزودن (TV_PARSE_STRUCT);
      contents = NULL_درخت;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      اگر (c_parser_next_token_is_keyword (parser, RID_AT_DEFS))
	{
	  درخت name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  اگر (!parens.require_open (parser))
	    برو end_at_defs;
	  اگر (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->مقدار;
	      c_parser_consume_token (parser);
	    }
	  وگرنه
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
	      برو end_at_defs;
	    }
	  parens.skip_until_found_close (parser);
	  contents = nreverse (objc_get_class_ivars (name));
	}
    end_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      وقتی (درست)
	{
	  درخت decls;
	  /* Parse any stray semicolon.  */
	  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      location_t semicolon_loc
		= c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (semicolon_loc);
	      richloc.add_fixit_remove ();
	      pedwarn (&richloc, OPT_Wpedantic,
		       "extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      ادامه;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  اگر (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      بشکن;
	    }
	  /* Accept #pragmas at struct scope.  */
	  اگر (c_parser_next_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, پوچ, NULL_درخت);
	      ادامه;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &عبارت);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  وگرنه
	    {
	      اگر (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      وگرنه اگر (parser->error
		       || !c_parser_next_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, پوچ);
		  بشکن;
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
				struct_info, &عبارت);
      ret.kind = ctsk_tagdef;
      ret.عبارت = عبارت;
      ret.عبارت_const_operands = درست;
      ret.has_enum_type_specifier = نادرست;
      timevar_برداشت (TV_PARSE_STRUCT);
      بازگشت ret;
    }
  وگرنه اگر (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_گره;
      ret.kind = ctsk_tagref;
      ret.عبارت = NULL_درخت;
      ret.عبارت_const_operands = درست;
      ret.has_enum_type_specifier = نادرست;
      بازگشت ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  اگر (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_tag (ident_loc, code, ident, have_std_attrs, std_attrs,
			 نادرست);
  بازگشت ret;
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

ایستا درخت
c_parser_struct_declaration (c_parser *parser, درخت *عبارت)
{
  ساختار c_declspecs *specs;
  درخت prefix_attrs;
  درخت all_prefix_attrs;
  درخت decls;
  location_t decl_loc;
  اگر (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      صحیح ext;
      درخت decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, عبارت);
      restore_extension_diagnostics (ext);
      بازگشت decl;
    }
  اگر (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      بازگشت NULL_درخت;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, نادرست, درست, درست,
		      درست, نادرست, درست, درست, cla_nonabstract_decl);
  اگر (parser->error)
    بازگشت NULL_درخت;
  اگر (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      بازگشت NULL_درخت;
    }
  finish_declspecs (specs);
  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      درخت ret;
      اگر (specs->typespec_kind == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_tag_warned (specs, pedantic);
	  ret = NULL_درخت;
	}
      وگرنه
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  درخت attrs = پوچ;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_درخت), specs,
			   NULL_درخت, &attrs, عبارت);
	  اگر (ret)
	    decl_attributes (&ret, attrs, 0);
	}
      بازگشت ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  اگر (specs->typespec_kind == ctsk_tagdef
      && درخت_CODE (specs->type) != ENUMERAL_TYPE
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = نادرست;
      بازگشت NULL_درخت;
    }

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_درخت;
  decls = NULL_درخت;
  وقتی (درست)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      ساختار c_declarator *declarator;
      منطقی dummy = نادرست;
      اگر (c_parser_next_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_درخت);
      وگرنه
	declarator = c_parser_declarator (parser,
					  specs->typespec_kind != ctsk_none,
					  C_DTR_NORMAL, &dummy);
      اگر (declarator == پوچ)
	{
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  بشکن;
	}
      اگر (c_parser_next_token_is (parser, CPP_COLON)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  درخت postfix_attrs = NULL_درخت;
	  درخت width = NULL_درخت;
	  درخت d;
	  اگر (c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      width = convert_lvalue_to_rvalue (loc,
						(c_parser_عبارت_no_commas
						 (parser, پوچ)),
						درست, درست).مقدار;
	    }
	  اگر (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_attributes (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, width, &all_prefix_attrs, عبارت);
	  decl_attributes (&d, chainon (postfix_attrs,
					all_prefix_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  اگر (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					prefix_attrs);
	  وگرنه
	    all_prefix_attrs = prefix_attrs;
	  اگر (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وگرنه اگر (c_parser_next_token_is (parser, CPP_SEMICOLON)
		   || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      /* Semicolon consumed in caller.  */
	      بشکن;
	    }
	  وگرنه
	    {
	      c_parser_error (parser, "expected %<,%>, %<;%> or %<}%>");
	      بشکن;
	    }
	}
      وگرنه
	{
	  c_parser_error (parser,
			  "expected %<:%>, %<,%>, %<;%>, %<}%> or "
			  "%<__attribute__%>");
	  بشکن;
	}
    }
  بازگشت decls;
}

/* Parse a typeof specifier (a GNU extension adopted in C23).

   typeof-specifier:
     typeof ( expression )
     typeof ( type-name )
     typeof_unqual ( expression )
     typeof_unqual ( type-name )
*/

ایستا ساختار c_typespec
c_parser_typeof_specifier (c_parser *parser)
{
  منطقی is_unqual;
  منطقی is_std;
  ساختار c_typespec ret;
  ret.kind = ctsk_typeof;
  ret.spec = error_mark_گره;
  ret.عبارت = NULL_درخت;
  ret.عبارت_const_operands = درست;
  ret.has_enum_type_specifier = نادرست;
  اگر (c_parser_next_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = نادرست;
      درخت spelling = c_parser_peek_token (parser)->مقدار;
      is_std = (flag_isoc23
		&& strcmp (IDENTIFIER_POINTER (spelling), "typeof") == 0);
    }
  وگرنه
    {
      gcc_assert (c_parser_next_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = درست;
      درخت spelling = c_parser_peek_token (parser)->مقدار;
      is_std = strcmp (IDENTIFIER_POINTER (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_typeof++;
  matching_parens parens;
  اگر (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      بازگشت ret;
    }
  اگر (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      ساختار c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      اگر (type != پوچ)
	{
	  ret.spec = groktypename (type, &ret.عبارت, &ret.عبارت_const_operands);
	  برداشت_maybe_used (c_type_variably_modified_p (ret.spec));
	}
    }
  وگرنه
    {
      منطقی was_vm;
      location_t here = c_parser_peek_token (parser)->location;
      ساختار c_عبارت عبارت = c_parser_expression (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      اگر (درخت_CODE (عبارت.مقدار) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (درخت_OPERAND (عبارت.مقدار, 1)))
	error_at (here, "%<typeof%> applied to a bit-field");
      mark_exp_read (عبارت.مقدار);
      ret.spec = درخت_TYPE (عبارت.مقدار);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      اگر (was_vm)
	ret.عبارت = c_fully_fold (عبارت.مقدار, نادرست, &ret.عبارت_const_operands);
      برداشت_maybe_used (was_vm);
    }
  parens.skip_until_found_close (parser);
  اگر (ret.spec != error_mark_گره)
    {
      اگر (is_unqual)
	{
	  منطقی is_array = درخت_CODE (ret.spec) == ARRAY_TYPE;
	  صحیح quals = TYPE_QUALS (strip_array_types (ret.spec));
	  اگر ((is_array ? quals & ~TYPE_QUAL_ATOMIC : quals)
	      != TYPE_UNQUALIFIED)
	    {
	      ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	      اگر (quals & TYPE_QUAL_ATOMIC && is_array)
		ret.spec = c_build_qualified_type (ret.spec,
						   TYPE_QUAL_ATOMIC);
	    }
	}
      اگر (is_std)
	{
	  /* In ISO C terms, _Noreturn is not part of the type of
	     expressions such as &abort, but in GCC it is represented
	     internally as a type qualifier.  */
	  اگر (درخت_CODE (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  وگرنه اگر (FUNCTION_POINTER_TYPE_P (ret.spec)
		   && TYPE_QUALS (درخت_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_pointer_type (TYPE_MAIN_VARIANT (درخت_TYPE (ret.spec)));
	}
    }
  بازگشت ret;
}

/* Parse an alignment-specifier.

   C11 6.7.5:

   alignment-specifier:
     _Alignas ( type-name )
     _Alignas ( constant-expression )
*/

ایستا درخت
c_parser_alignas_specifier (c_parser * parser)
{
  درخت ret = error_mark_گره;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNAS));
  درخت spelling = c_parser_peek_token (parser)->مقدار;
  c_parser_consume_token (parser);
  اگر (flag_isoc99)
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  وگرنه
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت ret;
  اگر (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      ساختار c_type_name *type = c_parser_type_name (parser);
      اگر (type != پوچ)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, پوچ, پوچ),
					نادرست, درست, 1);
    }
  وگرنه
    ret = convert_lvalue_to_rvalue (loc,
				    c_parser_عبارت_no_commas (parser, پوچ),
				    درست, درست).مقدار;
  parens.skip_until_found_close (parser);
  بازگشت ret;
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

ساختار c_declarator *
c_parser_declarator (c_parser *parser, منطقی type_seen_p, c_dtr_syn kind,
		     منطقی *seen_id)
{
  /* Parse any initial pointer part.  */
  اگر (c_parser_next_token_is (parser, CPP_MULT))
    {
      ساختار c_declspecs *quals_attrs = build_null_declspecs ();
      ساختار c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, نادرست, نادرست, درست,
			  نادرست, نادرست, درست, نادرست, cla_prefer_id);
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      اگر (inner == پوچ)
	بازگشت پوچ;
      وگرنه
	بازگشت make_pointer_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  بازگشت c_parser_direct_declarator (parser, type_seen_p, kind, seen_id);
}

/* Parse a direct declarator or direct abstract declarator; arguments
   as c_parser_declarator.  */

ایستا ساختار c_declarator *
c_parser_direct_declarator (c_parser *parser, منطقی type_seen_p, c_dtr_syn kind,
			    منطقی *seen_id)
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

  اگر (kind != C_DTR_ABSTRACT
      && c_parser_next_token_is (parser, CPP_NAME)
      && ((type_seen_p
	   && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_kind == C_ID_ID))
    {
      ساختار c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->مقدار);
      *seen_id = درست;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      اگر (c_parser_nth_token_starts_std_attributes (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      بازگشت c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  اگر (kind != C_DTR_NORMAL
      && c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      ساختار c_declarator *inner = build_id_declarator (NULL_درخت);
      inner->id_loc = c_parser_peek_token (parser)->location;
      بازگشت c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      درخت attrs;
      ساختار c_declarator *inner;
      c_parser_consume_token (parser);
      منطقی have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      اگر (kind != C_DTR_NORMAL
	  && (c_parser_next_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_attributes (parser, 1)
		      || c_parser_next_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  ساختار c_arg_info *args
	    = c_parser_parms_declarator (parser, kind == C_DTR_NORMAL,
					 attrs, have_gnu_attrs);
	  اگر (args == پوچ)
	    بازگشت پوچ;
	  وگرنه
	    {
	      inner = build_id_declarator (NULL_درخت);
	      اگر (!(args->types
		    && args->types != error_mark_گره
		    && درخت_CODE (درخت_مقدار (args->types)) == IDENTIFIER_گره)
		  && c_parser_nth_token_starts_std_attributes (parser, 1))
		{
		  درخت std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  اگر (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (args, inner);
	      بازگشت c_parser_direct_declarator_inner (parser, *seen_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      اگر (inner != پوچ && attrs != پوچ)
	inner = build_attrs_declarator (attrs, inner);
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  اگر (inner == پوچ)
	    بازگشت پوچ;
	  وگرنه
	    بازگشت c_parser_direct_declarator_inner (parser, *seen_id, inner);
	}
      وگرنه
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  بازگشت پوچ;
	}
    }
  وگرنه
    {
      اگر (kind == C_DTR_NORMAL)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  بازگشت پوچ;
	}
      وگرنه
	بازگشت build_id_declarator (NULL_درخت);
    }
}

/* Parse part of a direct declarator or direct abstract declarator,
   given that some (in INNER) has already been parsed; ID_PRESENT is
   true if an identifier is present, false for an abstract
   declarator.  */

ایستا ساختار c_declarator *
c_parser_direct_declarator_inner (c_parser *parser, منطقی id_present,
				  ساختار c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  اگر (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      ساختار c_declarator *declarator;
      ساختار c_declspecs *quals_attrs = build_null_declspecs ();
      ساختار c_عبارت dimen;
      dimen.مقدار = NULL_درخت;
      dimen.original_code = ERROR_MARK;
      dimen.original_type = NULL_درخت;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, نادرست, نادرست, درست,
			  نادرست, نادرست, نادرست, نادرست, cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      اگر (c_parser_next_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  اگر (!quals_attrs->declspecs_seen_p)
	    c_parser_declspecs (parser, quals_attrs, نادرست, نادرست, درست,
				نادرست, نادرست, نادرست, نادرست, cla_prefer_id);
	}
      اگر (!quals_attrs->declspecs_seen_p)
	quals_attrs = پوچ;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      ثابت منطقی static_seen = (static_loc != UNKNOWN_LOCATION);
      منطقی star_seen = نادرست;
      اگر (c_parser_next_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_SQUARE)
	{
	  star_seen = درست;
	  c_parser_consume_token (parser);
	}
      وگرنه اگر (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	dimen = c_parser_عبارت_no_commas (parser, پوچ);

      اگر (static_seen)
	{
	  اگر (star_seen)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      star_seen = نادرست;
	      dimen.مقدار = error_mark_گره;
	    }
	  وگرنه اگر (!dimen.مقدار)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      اگر (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	c_parser_consume_token (parser);
      وگرنه
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  بازگشت پوچ;
	}
      اگر (dimen.مقدار)
	dimen = convert_lvalue_to_rvalue (brace_loc, dimen, درست, درست);
      declarator = build_array_declarator (brace_loc, dimen.مقدار, quals_attrs,
					   static_seen, star_seen);
      اگر (declarator == پوچ)
	بازگشت پوچ;
      اگر (c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  درخت std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  اگر (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = set_array_declarator_inner (declarator, inner);
      بازگشت c_parser_direct_declarator_inner (parser, id_present, inner);
    }
  وگرنه اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      درخت attrs;
      ساختار c_arg_info *args;
      c_parser_consume_token (parser);
      منطقی have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      args = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      اگر (args == پوچ)
	بازگشت پوچ;
      وگرنه
	{
	  اگر (!(args->types
		&& args->types != error_mark_گره
		&& درخت_CODE (درخت_مقدار (args->types)) == IDENTIFIER_گره)
	      && c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      درخت std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      اگر (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (args, inner);
	  بازگشت c_parser_direct_declarator_inner (parser, id_present, inner);
	}
    }
  بازگشت inner;
}

/* Parse a parameter list or identifier list, including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list.  ID_LIST_OK is true if an identifier list
   is acceptable; such a list must not have attributes at the start.
   HAVE_GNU_ATTRS says whether any gnu-attributes (including empty
   attributes) were present (in which case standard attributes cannot
   occur).  */

ایستا ساختار c_arg_info *
c_parser_parms_declarator (c_parser *parser, منطقی id_list_ok, درخت attrs,
			   منطقی have_gnu_attrs)
{
  افزودن_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  اگر (id_list_ok
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
      درخت list = NULL_درخت, *nextp = &list;
      وقتی (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  *nextp = build_درخت_list (NULL_درخت,
				    c_parser_peek_token (parser)->مقدار);
	  nextp = & درخت_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  اگر (c_parser_next_token_is_not (parser, CPP_COMMA))
	    بشکن;
	  c_parser_consume_token (parser);
	  اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      بشکن;
	    }
	}
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ساختار c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  برداشت_scope ();
	  بازگشت ret;
	}
      وگرنه
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  برداشت_scope ();
	  بازگشت پوچ;
	}
    }
  وگرنه
    {
      ساختار c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, پوچ, have_gnu_attrs);
      برداشت_scope ();
      بازگشت ret;
    }
}

/* Parse a parameter list (possibly empty), including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list; if HAVE_GNU_ATTRS, there were some such
   attributes (possibly empty, in which case ATTRS is NULL_TREE),
   which means standard attributes cannot start the list.  EXPR is
   NULL or an expression that needs to be evaluated for the side
   effects of array size expressions in the parameters.  */

ایستا ساختار c_arg_info *
c_parser_parms_list_declarator (c_parser *parser, درخت attrs, درخت عبارت,
				منطقی have_gnu_attrs)
{
  منطقی bad_parm = نادرست;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      ساختار c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      بازگشت ret;
    }
  اگر (c_parser_next_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      ساختار c_arg_info *ret = build_arg_info ();

      ret->types = NULL_درخت;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_args_stdarg_p = درست;
	  c_parser_consume_token (parser);
	  بازگشت ret;
	}
      وگرنه
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  بازگشت پوچ;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  وقتی (درست)
    {
      /* Parse a parameter.  */
      ساختار c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_درخت;
      have_gnu_attrs = نادرست;
      اگر (parm == پوچ)
	bad_parm = درست;
      وگرنه
	افزودن_parm_decl (parm, &عبارت);
      اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  درخت new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  منطقی new_have_gnu_attrs
	    = c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_attributes (parser);
	  بازگشت c_parser_parms_list_declarator (parser, new_attrs, عبارت,
						 new_have_gnu_attrs);
	}
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  اگر (bad_parm)
	    بازگشت پوچ;
	  وگرنه
	    بازگشت get_parm_info (نادرست, عبارت);
	}
      اگر (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, نادرست))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
	  بازگشت پوچ;
	}
      اگر (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      اگر (bad_parm)
		بازگشت پوچ;
	      وگرنه
		بازگشت get_parm_info (درست, عبارت);
	    }
	  وگرنه
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      بازگشت پوچ;
	    }
	}
    }
}

/* Parse a parameter declaration.  ATTRS are the gnu-attributes at the
   start of the declaration if it is the first parameter;
   HAVE_GNU_ATTRS is true if there were any gnu-attributes there (even
   empty) there.  */

ایستا ساختار c_parm *
c_parser_parameter_declaration (c_parser *parser, درخت attrs,
				منطقی have_gnu_attrs)
{
  ساختار c_declspecs *specs;
  ساختار c_declarator *declarator;
  درخت prefix_attrs;
  درخت postfix_attrs = NULL_درخت;
  منطقی dummy = نادرست;

  /* Accept #pragmas between parameter declarations.  */
  وقتی (c_parser_next_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, پوچ, NULL_درخت);

  اگر (!c_parser_next_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (parser->error)
	بازگشت پوچ;
      c_parser_set_source_position_from_token (token);
      اگر (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (token->مقدار,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  اگر (ثابت نویسه *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->مقدار, suggestion);
	    }
	  وگرنه
	    error_at (token->location, "unknown type name %qE", token->مقدار);
	  parser->error = درست;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      وگرنه
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_to_end_of_parameter (parser);
      بازگشت پوچ;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  اگر (attrs)
    {
      declspecs_add_attrs (درون_داد_location, specs, attrs);
      attrs = NULL_درخت;
    }
  c_parser_declspecs (parser, specs, درست, درست, درست, درست, نادرست,
		      !have_gnu_attrs, درست, cla_nonabstract_decl);
  finish_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  اگر (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_بالاترین_anonymous_type (specs->type);

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  specs->attrs = NULL_درخت;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_PARM, &dummy);
  اگر (declarator == پوچ)
    {
      c_parser_skip_until_found (parser, CPP_COMMA, پوچ);
      بازگشت پوچ;
    }
  اگر (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
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
  وقتی (id_declarator && id_declarator->kind != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : start_loc);
  location_t param_loc = make_location (caret_loc, start_loc, end_loc);

  بازگشت build_c_parm (specs, chainon (postfix_attrs, prefix_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

ایستا درخت
c_parser_asm_string_literal (c_parser *parser)
{
  درخت str;
  صحیح save_flag = warn_overlength_strings;
  warn_overlength_strings = 0;
  str = c_parser_string_literal (parser, نادرست, نادرست).مقدار;
  warn_overlength_strings = save_flag;
  بازگشت str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

ایستا درخت
c_parser_simple_asm_عبارت (c_parser *parser)
{
  درخت str;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت NULL_درخت;
  str = c_parser_asm_string_literal (parser);
  اگر (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
      بازگشت NULL_درخت;
    }
  بازگشت str;
}

ایستا درخت
c_parser_gnu_attribute_any_word (c_parser *parser)
{
  درخت attr_name = NULL_درخت;

  اگر (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      /* ??? See comment above about what keywords are accepted here.  */
      منطقی ok;
      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_STATIC:
	حالت RID_UNSIGNED:
	حالت RID_LONG:
	حالت RID_CONST:
	حالت RID_EXTERN:
	حالت RID_REGISTER:
	حالت RID_TYPEDEF:
	حالت RID_SHORT:
	حالت RID_INLINE:
	حالت RID_NORETURN:
	حالت RID_VOLATILE:
	حالت RID_SIGNED:
	حالت RID_AUTO:
	حالت RID_RESTRICT:
	حالت RID_COMPLEX:
	حالت RID_THREAD:
	حالت RID_INT:
	حالت RID_CHAR:
	حالت RID_FLOAT:
	حالت RID_DOUBLE:
	حالت RID_VOID:
	حالت RID_DFLOAT32:
	حالت RID_DFLOAT64:
	حالت RID_DFLOAT128:
	حالت RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	حالت RID_BOOL:
	حالت RID_BITINT:
	حالت RID_FRACT:
	حالت RID_ACCUM:
	حالت RID_SAT:
	حالت RID_TRANSACTION_ATOMIC:
	حالت RID_TRANSACTION_CANCEL:
	حالت RID_ATOMIC:
	حالت RID_AUTO_TYPE:
	حالت RID_CONSTEXPR:
	حالت RID_INT_N_0:
	حالت RID_INT_N_1:
	حالت RID_INT_N_2:
	حالت RID_INT_N_3:
	  ok = درست;
	  بشکن;
	پیشفرض:
	  ok = نادرست;
	  بشکن;
	}
      اگر (!ok)
	بازگشت NULL_درخت;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(صحیح) c_parser_peek_token (parser)->keyword];
    }
  وگرنه اگر (c_parser_next_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->مقدار;

  بازگشت attr_name;
}

/* Parse attribute arguments.  This is a common form of syntax
   covering all currently valid GNU and standard attributes.

   gnu-attribute-arguments:
     identifier
     identifier , nonempty-expr-list
     expr-list

   where the "identifier" must not be declared as a type.  ??? Why not
   allow identifiers declared as types to start the arguments?  */

ایستا درخت
c_parser_attribute_arguments (c_parser *parser, منطقی takes_identifier,
			      منطقی require_string, منطقی assume_attr,
			      منطقی allow_empty_args)
{
  vec<درخت, va_gc> *عبارت_list;
  درخت attr_args;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  اگر (c_parser_next_token_is (parser, CPP_NAME)
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
      درخت arg1 = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	attr_args = build_درخت_list (NULL_درخت, arg1);
      وگرنه
	{
	  درخت درخت_list;
	  c_parser_consume_token (parser);
	  عبارت_list = c_parser_عبارت_list (parser, نادرست, درست,
					  پوچ, پوچ, پوچ, پوچ);
	  درخت_list = build_درخت_list_vec (عبارت_list);
	  attr_args = درخت_cons (NULL_درخت, arg1, درخت_list);
	  release_درخت_vector (عبارت_list);
	}
    }
  وگرنه
    {
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  اگر (!allow_empty_args)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_args = NULL_درخت;
	}
      وگرنه اگر (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  درخت string = c_parser_string_literal (parser, نادرست, درست).مقدار;
	  attr_args = build_درخت_list (NULL_درخت, string);
	}
      وگرنه اگر (assume_attr)
	{
	  درخت cond
	    = c_parser_conditional_expression (parser, پوچ, NULL_درخت).مقدار;
	  اگر (!c_parser_next_token_is (parser, CPP_COMMA))
	    attr_args = build_درخت_list (NULL_درخت, cond);
	  وگرنه
	    {
	      درخت درخت_list;
	      c_parser_consume_token (parser);
	      عبارت_list = c_parser_عبارت_list (parser, نادرست, درست,
					      پوچ, پوچ, پوچ, پوچ);
	      درخت_list = build_درخت_list_vec (عبارت_list);
	      attr_args = درخت_cons (NULL_درخت, cond, درخت_list);
	      release_درخت_vector (عبارت_list);
	    }
	}
      وگرنه
	{
	  عبارت_list = c_parser_عبارت_list (parser, نادرست, درست,
					  پوچ, پوچ, پوچ, پوچ);
	  attr_args = build_درخت_list_vec (عبارت_list);
	  release_درخت_vector (عبارت_list);
	}
    }
  بازگشت attr_args;
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

ایستا درخت
c_parser_gnu_attribute (c_parser *parser, درخت attrs,
			منطقی expect_comma = نادرست, منطقی empty_ok = درست)
{
  منطقی comma_first = c_parser_next_token_is (parser, CPP_COMMA);
  اگر (!comma_first
      && !c_parser_next_token_is (parser, CPP_NAME)
      && !c_parser_next_token_is (parser, CPP_KEYWORD))
    بازگشت NULL_درخت;

  وقتی (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      اگر (!empty_ok)
	بازگشت attrs;
    }

  درخت attr_name = c_parser_gnu_attribute_any_word (parser);
  اگر (attr_name == NULL_درخت)
    بازگشت NULL_درخت;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  درخت attr;
  اگر (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      اگر (expect_comma && !comma_first)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  بازگشت error_mark_گره;
	}
      attr = build_درخت_list (attr_name, NULL_درخت);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      بازگشت attrs;
    }
  c_parser_consume_token (parser);

  درخت attr_args
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    نادرست,
				    is_attribute_p ("assume", attr_name),
				    درست);

  attr = build_درخت_list (attr_name, attr_args);
  اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  وگرنه
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      بازگشت error_mark_گره;
    }

  اگر (expect_comma && !comma_first)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      بازگشت error_mark_گره;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  بازگشت attrs;
}

ایستا درخت
c_parser_gnu_attributes (c_parser *parser)
{
  درخت attrs = NULL_درخت;
  وقتی (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      منطقی save_translate_strings_p = parser->translate_strings_p;
      parser->translate_strings_p = نادرست;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  بازگشت attrs;
	}
      اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
	  بازگشت attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      برای (منطقی expect_comma = نادرست; ; expect_comma = درست)
	{
	  /* Parse a single attribute.  */
	  درخت attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  اگر (attr == error_mark_گره)
	    بازگشت attrs;
	  اگر (!attr)
	    بشکن;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      وگرنه
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  بازگشت attrs;
	}
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      وگرنه
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  بازگشت attrs;
	}
      parser->translate_strings_p = save_translate_strings_p;
    }

  بازگشت attrs;
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

ایستا تهی
c_parser_balanced_token_sequence (c_parser *parser)
{
  وقتی (درست)
    {
      c_token *token = c_parser_peek_token (parser);
      انتخاب (token->type)
	{
	حالت CPP_OPEN_BRACE:
	  {
	    matching_braces braces;
	    braces.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    braces.require_close (parser);
	    بشکن;
	  }

	حالت CPP_OPEN_PAREN:
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    parens.require_close (parser);
	    بشکن;
	  }

	حالت CPP_OPEN_SQUARE:
	  c_parser_consume_token (parser);
	  c_parser_balanced_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
	  بشکن;

	حالت CPP_CLOSE_BRACE:
	حالت CPP_CLOSE_PAREN:
	حالت CPP_CLOSE_SQUARE:
	حالت CPP_EOF:
	  بازگشت;

	حالت CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, نادرست);
	  بشکن;

	پیشفرض:
	  c_parser_consume_token (parser);
	  بشکن;
	}
    }
}

/* Parse arguments of omp::directive or omp::decl attribute.

   directive-name ,[opt] clause-list[opt]

   For directive just remember the tokens in a vector for subsequent
   parsing.  */

ایستا تهی
c_parser_omp_directive_args (c_parser *parser, درخت attribute, منطقی decl_p)
{
  unsigned صحیح n = 1;
  c_token *first = c_parser_peek_token (parser);
  اگر (!c_parser_check_balanced_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_balanced_token_sequence (parser);
      درخت_مقدار (attribute) = NULL_درخت;
      بازگشت;
    }
  اگر (n == 1)
    {
      error_at (first->location, "expected OpenMP directive name");
      درخت_مقدار (attribute) = NULL_درخت;
      بازگشت;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  برای (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->quick_افزودن (*tok);
      c_parser_consume_token (parser);
    }
  درخت arg = make_گره (C_TOKEN_VEC);
  C_TOKEN_VEC_TOKENS (arg) = v;
  اگر (decl_p)
    درخت_PUBLIC (arg) = 1;
  درخت_مقدار (attribute) = درخت_cons (NULL_درخت, arg, درخت_مقدار (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

ایستا تهی
c_parser_omp_sequence_args (c_parser *parser, درخت attribute)
{
  انجامبده
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (token->type == CPP_NAME
	  && strcmp (IDENTIFIER_POINTER (token->مقدار), "omp") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_SCOPE)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  token = c_parser_peek_token (parser);
	}
      منطقی directive = نادرست;
      ثابت نویسه *p;
      اگر (token->type != CPP_NAME)
	p = "";
      وگرنه
	p = IDENTIFIER_POINTER (token->مقدار);
      اگر (strcmp (p, "directive") == 0)
	directive = درست;
      وگرنه اگر (strcmp (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  unsigned nesting_depth = 0;

	  وقتی (درست)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      اگر ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_depth)
		بشکن;
	      /* If we've run out of tokens, stop.  */
	      اگر (token->type == CPP_EOF)
		بشکن;
	      اگر (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
		بشکن;
	      اگر (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_SQUARE)
		++nesting_depth;
	      وگرنه اگر (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_SQUARE)
		{
		  اگر (nesting_depth-- == 0)
		    بشکن;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  اگر (c_parser_next_token_is_not (parser, CPP_COMMA))
	    بشکن;
	  c_parser_consume_token (parser);
	  ادامه;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      اگر (parens.require_open (parser))
	{
	  اگر (directive)
	    c_parser_omp_directive_args (parser, attribute, نادرست);
	  وگرنه
	    c_parser_omp_sequence_args (parser, attribute);
	  parens.skip_until_found_close (parser);
	  اگر (c_parser_next_token_is_not (parser, CPP_COMMA))
	    بشکن;
	  c_parser_consume_token (parser);
	}
      وگرنه اگر (c_parser_next_token_is_not (parser, CPP_COMMA))
	بشکن;
      وگرنه
	c_parser_consume_token (parser);
    }
  وقتی (1);
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

ایستا درخت
c_parser_std_attribute (c_parser *parser, منطقی for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  درخت ns, name, attribute;

  /* Parse the attribute-token.  */
  اگر (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      بازگشت error_mark_گره;
    }
  name = canonicalize_attr_name (token->مقدار);
  c_parser_consume_token (parser);
  اگر (c_parser_next_token_is (parser, CPP_SCOPE)
      || (c_parser_next_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      اگر (c_parser_next_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      اگر (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  بازگشت error_mark_گره;
	}
      name = canonicalize_attr_name (token->مقدار);
      c_parser_consume_token (parser);
    }
  وگرنه
    ns = NULL_درخت;
  attribute = build_درخت_list (build_درخت_list (ns, name), NULL_درخت);

  /* Parse the arguments, if any.  */
  ثابت attribute_spec *as = lookup_attribute_spec (درخت_PURPOSE (attribute));
  اگر (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      اگر ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  بازگشت error_mark_گره;
	}
      برو out;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    اگر ((as && as->max_length == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_found_close (parser);
	بازگشت error_mark_گره;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    اگر (as && !attribute_ignored_p (as))
      {
	منطقی takes_identifier
	  = (ns != NULL_درخت
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	منطقی require_string
	  = (ns == NULL_درخت
	     && (strcmp (IDENTIFIER_POINTER (name), "deprecated") == 0
		 || strcmp (IDENTIFIER_POINTER (name), "nodiscard") == 0));
	منطقی assume_attr
	  = (ns != NULL_درخت
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && strcmp (IDENTIFIER_POINTER (name), "assume") == 0);
	درخت_مقدار (attribute)
	  = c_parser_attribute_arguments (parser, takes_identifier,
					  require_string, assume_attr, نادرست);
      }
    وگرنه
      {
	اگر ((flag_openmp || flag_openmp_simd)
	    && ns
	    && is_attribute_p ("omp", ns))
	  {
	    اگر (is_attribute_p ("directive", name))
	      {
		c_parser_omp_directive_args (parser, attribute, نادرست);
		parens.skip_until_found_close (parser);
		بازگشت attribute;
	      }
	    وگرنه اگر (is_attribute_p ("decl", name))
	      {
		درخت_مقدار (درخت_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_args (parser, attribute, درست);
		parens.skip_until_found_close (parser);
		بازگشت attribute;
	      }
	    وگرنه اگر (is_attribute_p ("sequence", name))
	      {
		درخت_مقدار (درخت_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_args (parser, attribute);
		parens.skip_until_found_close (parser);
		درخت_مقدار (attribute) = nreverse (درخت_مقدار (attribute));
		بازگشت attribute;
	      }
	  }
	c_parser_balanced_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 out:
  اگر (ns == NULL_درخت && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (درون_داد_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      بازگشت error_mark_گره;
    }
  بازگشت attribute;
}

ایستا درخت
c_parser_std_attribute_list (c_parser *parser, منطقی for_tm)
{
  درخت attributes = NULL_درخت;
  وقتی (درست)
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (token->type == CPP_CLOSE_SQUARE)
	بشکن;
      اگر (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ادامه;
	}
      درخت attribute = c_parser_std_attribute (parser, for_tm);
      اگر (attribute != error_mark_گره)
	{
	  درخت_CHAIN (attribute) = attributes;
	  attributes = attribute;
	}
      اگر (c_parser_next_token_is_not (parser, CPP_COMMA))
	بشکن;
    }
  بازگشت attributes;
}

ایستا درخت
c_parser_std_attribute_specifier (c_parser *parser, منطقی for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  اگر (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    بازگشت NULL_درخت;
  اگر (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
      بازگشت NULL_درخت;
    }
  درخت attributes;
  اگر (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      auto ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      attributes = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  وگرنه
    {
      اگر (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      attributes = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  بازگشت nreverse (attributes);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

ایستا منطقی
c_parser_check_balanced_raw_token_sequence (c_parser *parser, unsigned صحیح *n)
{
  وقتی (درست)
    {
      c_token *token = c_parser_peek_nth_token_raw (parser, *n);
      انتخاب (token->type)
	{
	حالت CPP_OPEN_BRACE:
	  {
	    ++*n;
	    اگر (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		اگر (token->type == CPP_CLOSE_BRACE)
		  ++*n;
		وگرنه
		  بازگشت نادرست;
	      }
	    وگرنه
	      بازگشت نادرست;
	    بشکن;
	  }

	حالت CPP_OPEN_PAREN:
	  {
	    ++*n;
	    اگر (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		اگر (token->type == CPP_CLOSE_PAREN)
		  ++*n;
		وگرنه
		  بازگشت نادرست;
	      }
	    وگرنه
	      بازگشت نادرست;
	    بشکن;
	  }

	حالت CPP_OPEN_SQUARE:
	  {
	    ++*n;
	    اگر (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		اگر (token->type == CPP_CLOSE_SQUARE)
		  ++*n;
		وگرنه
		  بازگشت نادرست;
	      }
	    وگرنه
	      بازگشت نادرست;
	    بشکن;
	  }

	حالت CPP_CLOSE_BRACE:
	حالت CPP_CLOSE_PAREN:
	حالت CPP_CLOSE_SQUARE:
	حالت CPP_EOF:
	  بازگشت درست;

	پیشفرض:
	  ++*n;
	  بشکن;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

ایستا منطقی
c_parser_nth_token_starts_std_attributes (c_parser *parser, unsigned صحیح n)
{
  اگر (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_SQUARE
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_SQUARE))
    بازگشت نادرست;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  اگر (!c_dialect_objc ())
    بازگشت درست;
  n += 2;
  اگر (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    بازگشت نادرست;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  اگر (token->type != CPP_CLOSE_SQUARE)
    بازگشت نادرست;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  بازگشت token->type == CPP_CLOSE_SQUARE;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

ایستا size_t
c_parser_skip_std_attribute_spec_seq (c_parser *parser, size_t n)
{
  size_t orig_n = n;
  وقتی (درست)
    {
      اگر (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_SQUARE
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_SQUARE))
	{
	  unsigned صحیح m = n + 2;
	  اگر (!c_parser_check_balanced_raw_token_sequence (parser, &m))
	    بازگشت orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  اگر (token->type != CPP_CLOSE_SQUARE)
	    بازگشت orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  اگر (token->type != CPP_CLOSE_SQUARE)
	    بازگشت orig_n;
	  n = m + 2;
	}
      وگرنه
	بشکن;
    }
  بازگشت n;
}

ایستا درخت
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  درخت attributes = NULL_درخت;
  انجامبده
    {
      درخت attrs = c_parser_std_attribute_specifier (parser, نادرست);
      attributes = chainon (attributes, attrs);
    }
  وقتی (c_parser_nth_token_starts_std_attributes (parser, 1));
  بازگشت attributes;
}

/* Parse a type name (C90 6.5.5, C99 6.7.6, C11 6.7.7).  ALIGNAS_OK
   says whether alignment specifiers are OK (only in cases that might
   be the type name of a compound literal).

   type-name:
     specifier-qualifier-list abstract-declarator[opt]
*/

ساختار c_type_name *
c_parser_type_name (c_parser *parser, منطقی alignas_ok)
{
  ساختار c_declspecs *specs = build_null_declspecs ();
  ساختار c_declarator *declarator;
  ساختار c_type_name *ret;
  منطقی dummy = نادرست;
  c_parser_declspecs (parser, specs, نادرست, درست, درست, alignas_ok, نادرست,
		      نادرست, درست, cla_prefer_type);
  اگر (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      بازگشت پوچ;
    }
  اگر (specs->type != error_mark_گره)
    {
      pending_xref_error ();
      finish_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      اگر (specs->typespec_kind == ctsk_tagdef)
	verify_counted_by_for_بالاترین_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_ABSTRACT, &dummy);
  اگر (declarator == پوچ)
    بازگشت پوچ;
  ret = XOBNEW (&parser_obstack, ساختار c_type_name);
  ret->specs = specs;
  ret->declarator = declarator;
  بازگشت ret;
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

ایستا ساختار c_عبارت
c_parser_initializer (c_parser *parser, درخت decl)
{
  اگر (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    بازگشت c_parser_braced_init (parser, NULL_درخت, نادرست, پوچ,
				 decl != error_mark_گره
				 && C_DECL_VARIABLE_SIZE (decl));
  وگرنه
    {
      ساختار c_عبارت ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_عبارت_no_commas (parser, پوچ);
      اگر (decl != error_mark_گره && C_DECL_VARIABLE_SIZE (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.set_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      اگر (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !درخت_STATIC (decl)
	  && ret.مقدار == decl
	  && !warning_enabled_at (DECL_SOURCE_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      اگر (درخت_CODE (ret.مقدار) != STRING_CST
	  && (درخت_CODE (ret.مقدار) != COMPOUND_LITERAL_عبارت
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_عبارت_DECL
					    (ret.مقدار))))
	ret = convert_lvalue_to_rvalue (loc, ret, درست, درست, درست);
      بازگشت ret;
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

ایستا ساختار c_عبارت
c_parser_braced_init (c_parser *parser, درخت type, منطقی nested_p,
		      ساختار obstack *outer_obstack, منطقی varsize_p)
{
  ساختار c_عبارت ret;
  ساختار obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  منطقی save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = نادرست;
  منطقی zero_init_padding_bits = نادرست;
  matching_braces braces;
  braces.consume_open (parser);
  اگر (nested_p)
    {
      finish_implicit_inits (brace_loc, outer_obstack);
      افزودن_init_level (brace_loc, 0, &braced_init_obstack);
    }
  وگرنه
    really_start_incremental_init (type);
  اگر (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      اگر (flag_isoc23)
	zero_init_padding_bits = درست;
    }
  وگرنه
    {
      اگر (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      وقتی (درست)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  اگر (parser->error)
	    بشکن;
	  اگر (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      last_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      وقتی (c_parser_next_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_عبارت embed_val;
		  embed_val.مقدار = embed->مقدار;
		  embed_val.original_code = RAW_DATA_CST;
		  embed_val.original_type = integer_type_گره;
		  set_c_عبارت_source_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, نادرست,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_next_token_is (parser,
							       CPP_COMMA));
		  last_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  وگرنه
	    بشکن;
	  اگر (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    بشکن;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *next_tok = c_parser_peek_token (parser);
  اگر (next_tok->type != CPP_CLOSE_BRACE)
    {
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = پوچ;
      braces.skip_until_found_close (parser);
      برداشت_init_level (brace_loc, 0, &braced_init_obstack, last_init_list_comma);
      obstack_free (&braced_init_obstack, پوچ);
      بازگشت ret;
    }
  location_t close_loc = next_tok->location;
  c_parser_consume_token (parser);
  ret = برداشت_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  اگر (zero_init_padding_bits
      && ret.مقدار
      && درخت_CODE (ret.مقدار) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_BITS (ret.مقدار) = 1;
  obstack_free (&braced_init_obstack, پوچ);
  set_c_عبارت_source_range (&ret, brace_loc, close_loc);
  بازگشت ret;
}

/* Parse a nested initializer, including designators.  */

ایستا تهی
c_parser_initelt (c_parser *parser, ساختار obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  اگر (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      set_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->مقدار,
		      c_parser_peek_token (parser)->location,
		      braced_init_obstack);
      /* Use the colon as the error location.  */
      pedwarn (c_parser_peek_2nd_token (parser)->location, OPT_Wpedantic,
	       "obsolete use of designated initializer with %<:%>");
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  وگرنه
    {
      /* des_seen is 0 if there have been no designators, 1 if there
	 has been a single array designator and 2 otherwise.  */
      صحیح des_seen = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      وقتی (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
	     || c_parser_next_token_is (parser, CPP_DOT))
	{
	  صحیح des_prev = des_seen;
	  اگر (!des_seen)
	    des_loc = c_parser_peek_token (parser)->location;
	  اگر (des_seen < 2)
	    des_seen++;
	  اگر (c_parser_next_token_is (parser, CPP_DOT))
	    {
	      des_seen = 2;
	      c_parser_consume_token (parser);
	      اگر (c_parser_next_token_is (parser, CPP_NAME))
		{
		  set_init_label (des_loc, c_parser_peek_token (parser)->مقدار,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      وگرنه
		{
		  ساختار c_عبارت init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = پوچ;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_found (parser, CPP_COMMA, پوچ);
		  process_init_element (درون_داد_location, init, نادرست,
					braced_init_obstack);
		  بازگشت;
		}
	    }
	  وگرنه
	    {
	      ساختار c_عبارت first_عبارت;
	      درخت first, second;
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
	      اگر (des_prev == 1 && c_dialect_objc ())
		{
		  des_seen = des_prev;
		  بشکن;
		}
	      اگر (des_prev == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  درخت rec, args;
		  ساختار c_عبارت mexpr;
		  c_parser_consume_token (parser);
		  اگر (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_kind
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_kind
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      درخت id = c_parser_peek_token (parser)->مقدار;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      برو parse_message_args;
		    }
		  array_index_loc = c_parser_peek_token (parser)->location;
		  first_عبارت = c_parser_عبارت_no_commas (parser, پوچ);
		  mark_exp_read (first_عبارت.مقدار);
		  اگر (c_parser_next_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    برو array_desig_after_first;
		  first = first_عبارت.مقدار;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = first;
		  وقتی (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      ساختار c_عبارت next;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      next = c_parser_عبارت_no_commas (parser, پوچ);
		      next = convert_lvalue_to_rvalue (exp_loc, next,
						       درست, درست);
		      rec = build_compound_عبارت (comma_loc, rec, next.مقدار);
		    }
		parse_message_args:
		  /* Now parse the objc-message-args.  */
		  args = c_parser_objc_message_args (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					     "expected %<]%>");
		  mexpr.مقدار
		    = objc_build_message_عبارت (rec, args);
		  mexpr.original_code = ERROR_MARK;
		  mexpr.original_type = پوچ;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  بازگشت;
		}
	      c_parser_consume_token (parser);
	      array_index_loc = c_parser_peek_token (parser)->location;
	      first_عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	      mark_exp_read (first_عبارت.مقدار);
	    array_desig_after_first:
	      first_عبارت = convert_lvalue_to_rvalue (array_index_loc,
						     first_عبارت,
						     درست, درست);
	      first = first_عبارت.مقدار;
	      اگر (c_parser_next_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  second = convert_lvalue_to_rvalue (ellipsis_loc,
						     (c_parser_عبارت_no_commas
						      (parser, پوچ)),
						     درست, درست).مقدار;
		  mark_exp_read (second);
		}
	      وگرنه
		second = NULL_درخت;
	      اگر (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		{
		  c_parser_consume_token (parser);
		  set_init_index (array_index_loc, first, second,
				  braced_init_obstack);
		  اگر (second)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      وگرنه
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					   "expected %<]%>");
	    }
	}
      اگر (des_seen >= 1)
	{
	  اگر (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  وگرنه
	    {
	      اگر (des_seen == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      وگرنه
		{
		  ساختار c_عبارت init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = پوچ;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_found (parser, CPP_COMMA, پوچ);
		  process_init_element (درون_داد_location, init, نادرست,
					braced_init_obstack);
		  بازگشت;
		}
	    }
	}
    }
  c_parser_initval (parser, پوچ, braced_init_obstack);
}

/* Parse a nested initializer; as c_parser_initializer but parses
   initializers within braced lists, after any designators have been
   applied.  If AFTER is not NULL then it is an Objective-C message
   expression which is the primary-expression starting the
   initializer.  */

ایستا تهی
c_parser_initval (c_parser *parser, ساختار c_عبارت *after,
		  ساختار obstack * braced_init_obstack)
{
  ساختار c_عبارت init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  اگر (c_parser_next_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_درخت, درست,
				 braced_init_obstack, نادرست);
  وگرنه
    {
      init = c_parser_عبارت_no_commas (parser, after);
      اگر (init.مقدار != NULL_درخت
	  && درخت_CODE (init.مقدار) != STRING_CST
	  && (درخت_CODE (init.مقدار) != COMPOUND_LITERAL_عبارت
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_عبارت_DECL
					    (init.مقدار))))
	init = convert_lvalue_to_rvalue (loc, init, درست, درست, درست);
    }
  درخت val = init.مقدار;
  process_init_element (loc, init, نادرست, braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  ایستا unsigned vals_to_ignore;
  اگر (vals_to_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_to_ignore;
  وگرنه اگر (val
	   && درخت_CODE (val) == INTEGER_CST
	   && درخت_TYPE (val) == integer_type_گره
	   && c_parser_next_token_is (parser, CPP_COMMA))
    اگر (unsigned صحیح len = c_maybe_optimize_large_byte_initializer ())
      {
	نویسه buf1[64];
	unsigned صحیح i;
	gcc_checking_assert (len >= 64);
	location_t last_loc = UNKNOWN_LOCATION;
	برای (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    اگر (tok->type != CPP_COMMA)
	      بشکن;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    اگر (tok->type != CPP_عدد
		|| درخت_CODE (tok->مقدار) != INTEGER_CST
		|| درخت_TYPE (tok->مقدار) != integer_type_گره
		|| wi::neg_p (wi::to_wide (tok->مقدار))
		|| wi::to_widest (tok->مقدار) > UCHAR_MAX)
	      بشکن;
	    buf1[i] = (نویسه) درخت_to_uhwi (tok->مقدار);
	    اگر (i == 0)
	      loc = tok->location;
	    last_loc = tok->location;
	  }
	اگر (i < 64)
	  {
	    vals_to_ignore = i;
	    بازگشت;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	اگر (tok->type == CPP_CLOSE_BRACE && len != INT_MAX)
	  len = i;
	وگرنه اگر (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_عدد))
	  {
	    vals_to_ignore = i;
	    بازگشت;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	unsigned صحیح max_len = 131072 - offsetof (ساختار درخت_string, str) - 1;
	unsigned صحیح orig_len = len;
	unsigned صحیح off = 0, last = 0;
	اگر (!wi::neg_p (wi::to_wide (val)) && wi::to_widest (val) <= UCHAR_MAX)
	  off = 1;
	len = MIN (len, max_len - off);
	نویسه *buf2 = XNEWVEC (نویسه, len + off);
	اگر (off)
	  buf2[0] = (نویسه) درخت_to_uhwi (val);
	memcpy (buf2 + off, buf1, i);
	برای (unsigned صحیح j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	برای (; i < len; ++i)
	  {
	    اگر (!c_parser_next_token_is (parser, CPP_COMMA))
	      بشکن;
	    tok = c_parser_peek_2nd_token (parser);
	    اگر (tok->type != CPP_عدد
		|| درخت_CODE (tok->مقدار) != INTEGER_CST
		|| درخت_TYPE (tok->مقدار) != integer_type_گره
		|| wi::neg_p (wi::to_wide (tok->مقدار))
		|| wi::to_widest (tok->مقدار) > UCHAR_MAX)
	      بشکن;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    اگر (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      بشکن;
	    buf2[i + off] = (نویسه) درخت_to_uhwi (tok->مقدار);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    اگر (orig_len == INT_MAX
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_عدد)))
	      {
		last = 1;
		بشکن;
	      }
	    last_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_گره (RAW_DATA_CST);
	درخت_TYPE (val) = integer_type_گره;
	RAW_DATA_LENGTH (val) = i;
	درخت owner = build_string (i + off + last, buf2);
	XDELETEVEC (buf2);
	درخت_TYPE (owner) = build_array_type_nelts (unsigned_char_type_گره,
						    i + off + last);
	RAW_DATA_OWNER (val) = owner;
	RAW_DATA_POINTER (val) = درخت_STRING_POINTER (owner) + off;
	init.مقدار = val;
	set_c_عبارت_source_range (&init, loc, last_loc);
	init.original_code = RAW_DATA_CST;
	init.original_type = integer_type_گره;
	init.m_decimal = 0;
	process_init_element (loc, init, نادرست, braced_init_obstack);
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

ایستا درخت
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  درخت stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  اگر (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (درست);
      c_end_compound_stmt (brace_loc, stmt, درست);
      بازگشت error_mark_گره;
    }
  stmt = c_begin_compound_stmt (درست);
  location_t end_loc = c_parser_compound_statement_nostart (parser);
  اگر (endlocp)
    *endlocp = end_loc;

  بازگشت c_end_compound_stmt (brace_loc, stmt, درست);
}

/* Diagnose errors related to imperfectly nested loops in an OMP
   loop construct.  This function is called when such code is seen.
   Only issue one such diagnostic no matter how much invalid
   intervening code there is in the loop.
   FIXME: maybe the location associated with the diagnostic should
   be the current parser token instead of the location of the outer loop
   nest.  */

ایستا تهی
check_omp_intervening_code (c_parser *parser)
{
  ساختار omp_for_parse_data *omp_for_parse_state = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);

  اگر (!omp_for_parse_state->in_intervening_code)
    بازگشت;
  omp_for_parse_state->saw_intervening_code = درست;

  /* Only diagnose errors related to perfect nesting once.  */
  اگر (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      اگر (omp_for_parse_state->code == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = درست;
	}
      وگرنه اگر (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = درست;
	}
      وگرنه اگر (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = درست;
	}
      وگرنه اگر (omp_for_parse_state->code == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = درست;
	}
      اگر (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->fail = درست;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
ایستا تهی
add_structured_block_stmt (درخت sl)
{
  اگر (درخت_CODE (sl) != STATEMENT_LIST
      || !tsi_end_p (tsi_start (sl)))
    add_stmt (build1 (OMP_STRUCTURED_BLOCK, void_type_گره, sl));
}

ساختار c_omp_attribute_data
{
  vec<c_token, va_gc> *tokens;
  ثابت c_omp_directive *dir;
  c_omp_directive_kind kind;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

ایستا منطقی
c_parser_handle_statement_omp_attributes (c_parser *parser, درخت &attrs,
					  منطقی *have_std_attrs)
{
  اگر (!flag_openmp && !flag_openmp_simd)
    بازگشت نادرست;

  auto_vec<c_omp_attribute_data, 16> vd;
  صحیح cnt = 0;
  صحیح tokens = 0;
  منطقی bad = نادرست;
  برای (درخت *pa = &attrs; *pa; )
    اگر (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	برای (درخت a = درخت_مقدار (*pa); a; a = درخت_CHAIN (a))
	  {
	    درخت d = درخت_مقدار (a);
	    gcc_assert (درخت_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    اگر (parser->omp_attrs_forbidden_p)
	      {
		error_at (first->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = نادرست;
		bad = درست;
	      }
	    وگرنه اگر (درخت_PUBLIC (d))
	      {
		error_at (first->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		bad = درست;
	      }
	    ثابت نویسه *directive[3] = {};
	    برای (صحیح i = 0; i < 3; i++)
	      {
		درخت id = NULL_درخت;
		اگر (first + i == last)
		  بشکن;
		اگر (first[i].type == CPP_NAME)
		  id = first[i].مقدار;
		وگرنه اگر (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(صحیح) first[i].keyword];
		وگرنه
		  بشکن;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    ثابت c_omp_directive *dir = پوچ;
	    اگر (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    اگر (dir == پوچ)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  درخت_PUBLIC (d) ? "omp::decl" : "omp::directive");
		ادامه;
	      }
	    c_omp_directive_kind kind = dir->kind;
	    اگر (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		اگر (directive[1]
		    && (strcmp (directive[1], "depend") == 0
			|| strcmp (directive[1], "doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
		وگرنه اگر (first + 2 < last
			 && first[1].type == CPP_COMMA
			 && first[2].type == CPP_NAME
			 && (strcmp (IDENTIFIER_POINTER (first[2].مقدار),
				     "depend") == 0
			     || strcmp (IDENTIFIER_POINTER (first[2].مقدار),
					"doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
	      }
	    وگرنه اگر (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		صحیح paren_depth = 0;
		برای (صحیح i = 1; first + i < last; i++)
		  اگر (first[i].type == CPP_OPEN_PAREN)
		    paren_depth++;
		  وگرنه اگر (first[i].type == CPP_CLOSE_PAREN)
		    paren_depth--;
		  وگرنه اگر (paren_depth == 0
			   && first + i + 2 < last
			   && first[i].type == CPP_NAME
			   && first[i + 1].type == CPP_OPEN_PAREN
			   && first[i + 2].type == CPP_NAME
			   && !strcmp (IDENTIFIER_POINTER (first[i].مقدار),
				       "at")
			   && !strcmp (IDENTIFIER_POINTER (first[i
								 + 2].مقدار),
				       "execution"))
		    {
		      kind = C_OMP_DIR_STANDALONE;
		      بشکن;
		    }
	      }
	    c_omp_attribute_data v = { toks, dir, kind };
	    vd.safe_افزودن (v);
	    اگر (flag_openmp || dir->simd)
	      tokens += (last - first) + 1;
	  }
	c_omp_attribute_data v = {};
	vd.safe_افزودن (v);
	*pa = درخت_CHAIN (*pa);
      }
    وگرنه
      pa = &درخت_CHAIN (*pa);

  اگر (bad)
    {
    fail:
      اگر (have_std_attrs && attrs == پوچ)
	*have_std_attrs = نادرست;
      بازگشت نادرست;
    }

  unsigned صحیح i;
  c_omp_attribute_data *v;
  c_omp_attribute_data *construct_seen = nullptr;
  c_omp_attribute_data *standalone_seen = nullptr;
  c_omp_attribute_data *prev_standalone_seen = nullptr;
  FOR_EACH_VEC_ELT (vd, i, v)
    اگر (v->tokens)
      {
	اگر (v->kind == C_OMP_DIR_CONSTRUCT && !construct_seen)
	  construct_seen = v;
	وگرنه اگر (v->kind == C_OMP_DIR_STANDALONE && !standalone_seen)
	  standalone_seen = v;
      }
    وگرنه
      {
	اگر (standalone_seen && !prev_standalone_seen)
	  {
	    prev_standalone_seen = standalone_seen;
	    standalone_seen = nullptr;
	  }
      }

  اگر (cnt > 1 && construct_seen)
    {
      error_at ((*construct_seen->tokens)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      برو fail;
    }
  اگر (cnt > 1 && standalone_seen && prev_standalone_seen)
    {
      error_at ((*standalone_seen->tokens)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      برو fail;
    }

  اگر (prev_standalone_seen)
    standalone_seen = prev_standalone_seen;
  اگر (standalone_seen
      && !c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_seen->tokens->address ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      برو fail;
    }
  اگر (cnt && c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      شمارش pragma_kind kind = token->pragma_kind;
      اگر (kind >= PRAGMA_OMP__START_ && kind <= PRAGMA_OMP__LAST_)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  برو fail;
	}
    }

  اگر (!tokens)
    بازگشت نادرست;

  unsigned صحیح tokens_avail = parser->tokens_avail;

  tokens++;
  vec<c_token, va_gc> *toks = پوچ;
  vec_safe_reserve (toks, tokens, درست);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      اگر (!v->tokens)
	ادامه;
      اگر (!flag_openmp && !v->dir->simd)
	ادامه;
      c_token *first = v->tokens->address ();
      c_token *last = first + v->tokens->length ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_kind = pragma_kind (v->dir->id);
      tok.location = first->location;
      toks->quick_افزودن (tok);
      وقتی (++first < last)
	toks->quick_افزودن (*first);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = last[-1].location;
      toks->quick_افزودن (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->last ().location;
  toks->quick_افزودن (tok);

  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = tokens;
  بازگشت درست;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

ایستا تهی
c_parser_handle_directive_omp_attributes (درخت &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  اگر (!flag_openmp && !flag_openmp_simd)
    بازگشت;

  برای (درخت *pa = &attrs; *pa; )
    اگر (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	صحیح cnt = 0;
	برای (درخت *pa2 = &درخت_مقدار (*pa); *pa2; )
	  {
	    درخت a = *pa2;
	    درخت d = درخت_مقدار (a);
	    gcc_assert (درخت_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    ثابت نویسه *directive[3] = {};
	    برای (صحیح i = 0; i < 3; i++)
	      {
		درخت id = NULL_درخت;
		اگر (first + i == last)
		  بشکن;
		اگر (first[i].type == CPP_NAME)
		  id = first[i].مقدار;
		وگرنه اگر (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(صحیح) first[i].keyword];
		وگرنه
		  بشکن;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    ثابت c_omp_directive *dir = پوچ;
	    اگر (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    اگر (dir == پوچ)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  درخت_PUBLIC (d) ? "omp::decl" : "omp::directive");
		*pa2 = درخت_CHAIN (a);
	      }
	    وگرنه اگر (dir->id == PRAGMA_OMP_DECLARE
		     && (strcmp (directive[1], "simd") == 0
			 || strcmp (directive[1], "variant") == 0))
	      {
		اگر (pragma_clauses)
		  {
		    error_at (first->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    برای (pa = &attrs; *pa; )
		      اگر (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = درخت_CHAIN (*pa);
		      وگرنه
			pa = &درخت_CHAIN (*pa);
		    بازگشت;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->length ()
				       + toks->length () + 2);
		برای (++first; first < last; ++first)
		  attr_clauses->quick_افزودن (*first);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = last[-1].location;
		attr_clauses->quick_افزودن (tok);
		*pa2 = درخت_CHAIN (a);
	      }
	    وگرنه
	      pa2 = &درخت_CHAIN (a);
	  }
	اگر (cnt && درخت_مقدار (*pa) == NULL_درخت)
	  *pa = درخت_CHAIN (*pa);
	وگرنه
	  pa = &درخت_CHAIN (*pa);
      }
    وگرنه
      pa = &درخت_CHAIN (*pa);
  اگر (attr_clauses->length ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->last ().location;
      attr_clauses->quick_افزودن (tok);
      attr_clauses->quick_افزودن (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

ایستا درخت
c_parser_handle_musttail (c_parser *parser, درخت std_attrs, attr_state &attr)
{
  اگر (c_parser_next_token_is_keyword (parser, RID_RETURN))
    {
      اگر (درخت a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  برای (; a; a = lookup_attribute ("gnu", "musttail", درخت_CHAIN (a)))
	    اگر (درخت_مقدار (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = درست;
	}
      اگر (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = درست;
	}
    }
  بازگشت std_attrs;
}

/* Return a statement before optional series of LABEL_EXPR/CASE_LABEL_EXPRs.
   Instead of collecting vectors of labels before each stmt just in case
   the statement would be iteration or switch statement for named loops,
   we just remember last emitted statement and let the iteration/switch
   statement search backwards in cur_stmt_list until that stmt for loop
   names if any.  */

ایستا درخت
get_before_labels ()
{
  اگر (!building_stmt_list_p ())
    بازگشت NULL_درخت;
  درخت_stmt_iterator tsi = tsi_last (cur_stmt_list);
  اگر (tsi_end_p (tsi))
    بازگشت NULL_درخت;
  بازگشت tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

ایستا location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  منطقی last_stmt = نادرست;
  منطقی last_label = نادرست;
  منطقی save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  ساختار omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  منطقی in_omp_loop_block
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : نادرست;
  درخت sl = NULL_درخت;
  attr_state astate = {};

  اگر (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      add_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      بازگشت endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  اگر (in_omp_loop_block)
    sl = افزودن_stmt_list ();

  mark_valid_location_for_stdc_pragma (درست);
  اگر (c_parser_next_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (نادرست);
      اگر (in_omp_loop_block)
	check_omp_intervening_code (parser);
      وقتی (c_parser_next_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  وقتی (درست)
	    {
	      درخت label;
	      اگر (c_parser_next_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  بشکن;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->مقدار);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      add_stmt (build_stmt (label_loc, DECL_عبارت, label));
	      c_parser_consume_token (parser);
	      اگر (c_parser_next_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      وگرنه
		بشکن;
	    }
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  اگر (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      بازگشت endloc;
    }
  درخت before_labels = get_before_labels ();
  وقتی (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_point_location_if_in_system_header (loc);

      منطقی want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : نادرست);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      اگر (in_omp_loop_block && !last_label)
	{
	  درخت_code code = omp_for_parse_state->code;
	  اگر (want_nested_loop
	      && c_parser_omp_next_tokens_can_be_canon_loop (parser, code,
							     نادرست))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      add_structured_block_stmt (برداشت_stmt_list (sl));
	      omp_for_parse_state->depth++;
	      add_stmt (c_parser_omp_loop_nest (parser, پوچ));
	      omp_for_parse_state->depth--;
	      sl = افزودن_stmt_list ();
	      parser->error = نادرست;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ادامه;
	    }
	  وگرنه اگر (want_nested_loop
		   && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      درخت pre_sl = برداشت_stmt_list (sl);
	      درخت nested_sl = افزودن_stmt_list ();
	      mark_valid_location_for_stdc_pragma (نادرست);
	      c_parser_statement_after_labels (parser, پوچ, NULL_درخت);
	      nested_sl = برداشت_stmt_list (nested_sl);
	      اگر (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_code (parser);
		  sl = افزودن_stmt_list ();
		  add_stmt (pre_sl);
		  add_stmt (nested_sl);
		}
	      وگرنه
		{
		  /* It contains the nested loop.  */
		  add_structured_block_stmt (pre_sl);
		  add_stmt (nested_sl);
		  sl = افزودن_stmt_list ();
		}
	      parser->error = نادرست;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ادامه;
	    }
	  وگرنه اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      /* Prior to implementing the OpenMP 5.1 syntax for canonical
		 loop form, GCC used to accept an empty statements that
		 would now be flagged as intervening code.  Continue to
		 do that, as an extension.  */
	      /* FIXME:  Maybe issue a warning or something here?  */
	      c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ادامه;
	    }
	}

      /* Standard attributes may start a label, statement or declaration.  */
      منطقی have_std_attrs
	= c_parser_nth_token_starts_std_attributes (parser, 1);
      درخت std_attrs = NULL_درخت;
      اگر (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      اگر (c_parser_next_token_is_keyword (parser, RID_CASE)
	  || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  اگر (c_parser_next_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  وگرنه
	    label_loc = c_parser_peek_token (parser)->location;
	  last_label = درست;
	  last_stmt = نادرست;
	  mark_valid_location_for_stdc_pragma (نادرست);
	  اگر (in_omp_loop_block)
	    check_omp_intervening_code (parser);
	  c_parser_label (parser, std_attrs);
	}
      وگرنه اگر (c_parser_next_tokens_start_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_attributes
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_next_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = درست)))
	{
	  اگر (last_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  اگر (in_omp_loop_block)
	    {
	      check_omp_intervening_code (parser);
	      omp_for_parse_state->want_nested_loop = نادرست;
	    }
	  mark_valid_location_for_stdc_pragma (نادرست);
	  منطقی fallthru_attr_p = نادرست;
	  c_parser_declaration_or_fndef (parser, درست, !have_std_attrs,
					 درست, درست, درست, نادرست, پوچ,
					 پوچ, have_std_attrs, std_attrs,
					 پوچ, &fallthru_attr_p);

	  اگر (in_omp_loop_block)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  اگر (last_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  last_stmt = fallthru_attr_p;
	  last_label = نادرست;
	  before_labels = get_before_labels ();
	}
      وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  If standard attributes have already
	     been seen, it must start a statement, not a declaration,
	     but standard attributes starting a declaration may appear
	     after __extension__.  */
	  وقتی (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  اگر (!have_std_attrs
	      && (c_parser_next_tokens_start_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_attributes (parser, 2)))
	    {
	      صحیح ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      last_label = نادرست;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      اگر (in_omp_loop_block)
		{
		  check_omp_intervening_code (parser);
		  omp_for_parse_state->want_nested_loop = نادرست;
		}
	      mark_valid_location_for_stdc_pragma (نادرست);
	      c_parser_declaration_or_fndef (parser, درست, درست, درست, درست,
					     درست, نادرست);
	      اگر (in_omp_loop_block)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      اگر (last_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      last_stmt = نادرست;
	      before_labels = get_before_labels ();
	    }
	  وگرنه
	    برو statement;
	}
      وگرنه اگر (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  اگر (have_std_attrs && !parser->in_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  وگرنه اگر (std_attrs)
	    c_warn_unused_attributes (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  اگر (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = نادرست;
	  اگر (c_parser_pragma (parser,
			       last_label ? pragma_stmt : pragma_compound,
			       پوچ, before_labels))
	    {
	      last_label = نادرست;
	      last_stmt = درست;
	      اگر (omp_for_parse_state)
		check_omp_intervening_code (parser);
	    }
	  اگر (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      وگرنه اگر (c_parser_next_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  بازگشت c_parser_peek_token (parser)->location;
	}
      وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_ELSE))
        {
          اگر (parser->in_if_block)
            {
	      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	      error_at (loc, "expected %<}%> before %<else%>");
	      بازگشت c_parser_peek_token (parser)->location;
            }
          وگرنه
            {
              error_at (loc, "%<else%> without a previous %<if%>");
              c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
              ادامه;
            }
        }
      وگرنه
	{
	statement:
	  c_warn_unused_attributes (std_attrs);
	  last_label = نادرست;
	  last_stmt = درست;
	  mark_valid_location_for_stdc_pragma (نادرست);
	  اگر (!omp_for_parse_state)
	    c_parser_statement_after_labels (parser, پوچ, before_labels,
					     پوچ, astate);
	  وگرنه
	    {
	      /* In canonical loop nest form, nested loops can only appear
		 directly, or in a directly nested compound statement.  We
		 already took care of those cases above, so now we have
		 something else.  This statement and everything inside
		 it must be intervening code.  */
	      omp_for_parse_state->want_nested_loop = نادرست;
	      check_omp_intervening_code (parser);
	      c_parser_statement_after_labels (parser, پوچ, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = نادرست;
      astate.reset ();
    }
  اگر (last_label)
    pedwarn_c11 (label_loc, OPT_Wfree_labels,
		 "label at end of compound statement");
  location_t endloc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  /* Restore the value we started with.  */
  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);

  /* Package leftover intervening code, or the whole contents of the
     compound statement if we were looking for a nested loop in an OMP_FOR
     construct and didn't find one.  */
  اگر (sl)
    {
      sl = برداشت_stmt_list (sl);
      اگر (omp_for_parse_state->want_nested_loop)
	add_stmt (sl);
      وگرنه
	add_structured_block_stmt (sl);
    }
  بازگشت endloc;
}

/* Parse all consecutive labels, possibly preceded by standard
   attributes.  In this context, a statement is required, not a
   declaration, so attributes must be followed by a statement that is
   not just a semicolon.  Returns an attr_state.  */

ایستا attr_state
c_parser_all_labels (c_parser *parser)
{
  attr_state attr = {};
  منطقی have_std_attrs;
  درخت std_attrs = پوچ;
  اگر ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  وقتی (c_parser_next_token_is_keyword (parser, RID_CASE)
	 || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = پوچ;
      اگر ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  اگر (std_attrs
      && (!c_parser_handle_statement_omp_attributes (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      اگر (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_unused_attributes (std_attrs);
    }
  وگرنه اگر (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  بازگشت attr;
}


/* Information used while parsing an OpenMP metadirective.  */
ساختار omp_metadirective_parse_data {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<درخت> * GTY((skip)) body_labels;
  unsigned صحیح region_رقم;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
ایستا درخت
mangle_metadirective_region_label (c_parser *parser, درخت name)
{
  اگر (parser->omp_metadirective_state->body_labels->contains (name))
    {
      ثابت نویسه *old_name = IDENTIFIER_POINTER (name);
      نویسه *new_name = (نویسه *) XALLOCAVEC (نویسه, strlen (old_name) + 32);
      sprintf (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_رقم);
      بازگشت get_identifier (new_name);
    }
  بازگشت name;
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
ایستا تهی
c_parser_label (c_parser *parser, درخت std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  درخت label = NULL_درخت;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  منطقی fallthrough_p = c_parser_peek_token (parser)->flags & PREV_FALLTHROUGH;

  اگر (c_parser_next_token_is_keyword (parser, RID_CASE))
    {
      درخت exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_to_rvalue (loc1,
				       c_parser_عبارت_no_commas (parser, پوچ),
				       درست, درست).مقدار;
      اگر (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_درخت, std_attrs);
	}
      وگرنه اگر (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_to_rvalue (loc1,
					   c_parser_عبارت_no_commas (parser,
								    پوچ),
					   درست, درست).مقدار;
	  اگر (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      وگرنه
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      اگر (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_درخت, NULL_درخت, std_attrs);
    }
  وگرنه
    {
      درخت name = c_parser_peek_token (parser)->مقدار;
      درخت tlab;
      درخت attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_attributes (parser);
      اگر (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      اگر (tlab)
	{
	  decl_attributes (&tlab, attrs, 0);
	  decl_attributes (&tlab, std_attrs, 0);
	  label = add_stmt (build_stmt (loc1, LABEL_عبارت, tlab));
	}
      اگر (attrs
	  && c_parser_next_tokens_start_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  اگر (label)
    {
      اگر (درخت_CODE (label) == LABEL_عبارت)
	FALLTHROUGH_LABEL_P (LABEL_عبارت_LABEL (label)) = fallthrough_p;
      وگرنه
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

ایستا تهی
c_parser_statement (c_parser *parser, منطقی *if_p, location_t *loc_after_labels)
{
  درخت before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  اگر (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = نادرست;
  c_parser_statement_after_labels (parser, if_p, before_labels, پوچ, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

ایستا درخت
c_parser_bc_name (c_parser *parser, منطقی is_break)
{
  اگر (!c_parser_next_token_is (parser, CPP_NAME))
    بازگشت NULL_درخت;

  c_token *tok = c_parser_peek_token (parser);
  درخت label = c_finish_bc_name (tok->location, tok->مقدار, is_break);
  c_parser_consume_token (parser);
  بازگشت label;
}

/* Parse a statement, other than a labeled statement.  CHAIN is a vector
   of if-else-if conditions.  All labels and standard attributes have
   been parsed in the caller.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  ASTATE is an earlier parsed attribute state.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ایستا تهی
c_parser_statement_after_labels (c_parser *parser, منطقی *if_p,
				 درخت before_labels,
				 vec<درخت> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت stmt = NULL_درخت;
  منطقی in_if_block = parser->in_if_block;
  parser->in_if_block = نادرست;
  اگر (if_p != پوچ)
    *if_p = نادرست;

  اگر (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    add_debug_begin_stmt (loc);

 restart:
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_OPEN_BRACE:
      add_stmt (c_parser_compound_statement (parser));
      بشکن;
    حالت CPP_KEYWORD:
      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_IF:
	  c_parser_if_statement (parser, if_p, chain);
	  بشکن;
	حالت RID_SWITCH:
	  c_parser_switch_statement (parser, if_p, before_labels);
	  بشکن;
	حالت RID_WHILE:
	  c_parser_while_statement (parser, نادرست, 0, نادرست, if_p, before_labels);
	  بشکن;
	حالت RID_DO:
	  c_parser_do_statement (parser, نادرست, 0, نادرست, before_labels);
	  بشکن;
	حالت RID_FOR:
	  c_parser_for_statement (parser, نادرست, 0, نادرست, if_p, before_labels);
	  بشکن;
	حالت RID_GOTO:
	  c_parser_consume_token (parser);
	  اگر (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      درخت name = c_parser_peek_token (parser)->مقدار;
	      اگر (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_finish_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  وگرنه اگر (c_parser_next_token_is (parser, CPP_MULT))
	    {
	      ساختار c_عبارت val;

	      c_parser_consume_token (parser);
	      val = c_parser_expression (parser);
	      val = convert_lvalue_to_rvalue (loc, val, نادرست, درست);
	      stmt = c_finish_goto_ptr (loc, val);
	    }
	  وگرنه
	    c_parser_error (parser, "expected identifier or %<*%>");
	  برو expect_semicolon;
	حالت RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_continue_label, نادرست,
				   c_parser_bc_name (parser, نادرست));
	  برو expect_semicolon;
	حالت RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_break_label, درست,
				   c_parser_bc_name (parser, درست));
	  برو expect_semicolon;
	حالت RID_RETURN:
	  c_parser_consume_token (parser);
	  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_finish_return (loc, NULL_درخت, NULL_درخت,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  وگرنه
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      ساختار c_عبارت عبارت = c_parser_expression_conv (parser);
	      mark_exp_read (عبارت.مقدار);
	      stmt = c_finish_return (عبارت_LOC_OR_LOC (عبارت.مقدار, xloc),
				      عبارت.مقدار, عبارت.original_type,
				      astate.musttail_p);
	      برو expect_semicolon;
	    }
	  بشکن;
	حالت RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  بشکن;
	حالت RID_TRANSACTION_ATOMIC:
	حالت RID_TRANSACTION_RELAXED:
	  stmt = c_parser_transaction (parser,
	      c_parser_peek_token (parser)->keyword);
	  بشکن;
	حالت RID_TRANSACTION_CANCEL:
	  stmt = c_parser_transaction_cancel (parser);
	  برو expect_semicolon;
	حالت RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_درخت);
	      c_parser_consume_token (parser);
	    }
	  وگرنه
	    {
	      ساختار c_عبارت عبارت = c_parser_expression (parser);
	      عبارت = convert_lvalue_to_rvalue (loc, عبارت, نادرست, نادرست);
	      عبارت.مقدار = c_fully_fold (عبارت.مقدار, نادرست, پوچ);
	      stmt = objc_build_throw_stmt (loc, عبارت.مقدار);
	      برو expect_semicolon;
	    }
	  بشکن;
	حالت RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_finally_statement (parser);
	  بشکن;
	حالت RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  بشکن;
	حالت RID_ATTRIBUTE:
	  {
	    /* Allow '__attribute__((fallthrough));' or
	       '__attribute__((assume(cond)));' or
	       '__attribute__((musttail))) return'.  */
	    درخت attrs = c_parser_gnu_attributes (parser);
	    منطقی has_assume = lookup_attribute ("assume", attrs);
	    اگر (has_assume)
	      {
		اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, درست);
		وگرنه
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<assume%> attribute not followed by %<;%>");
		    has_assume = نادرست;
		  }
	      }
	    gcc_assert (!astate.musttail_p);
	    attrs = c_parser_handle_musttail (parser, attrs, astate);
	    اگر (astate.musttail_p)
	      {
		اگر (attrs)
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		برو restart;
	      }
	    اگر (attribute_fallthrough_p (attrs))
	      {
		اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  {
		    درخت fn = build_call_عبارت_internal_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_گره, 0);
		    add_stmt (fn);
		    /* Eat the ';'.  */
		    c_parser_consume_token (parser);
		  }
		وگرنه
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<fallthrough%> attribute not followed "
				"by %<;%>");
		  }
	      }
	    وگرنه اگر (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    وگرنه اگر (attrs != NULL_درخت)
	      {
		auto_urlify_attributes sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    بشکن;
	  }
	پیشفرض:
	  برو عبارت_stmt;
	}
      بشکن;
    حالت CPP_SEMICOLON:
      c_parser_consume_token (parser);
      بشکن;
    حالت CPP_CLOSE_PAREN:
    حالت CPP_CLOSE_SQUARE:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      بشکن;
    حالت CPP_PRAGMA:
      اگر (!c_parser_pragma (parser, pragma_stmt, if_p, before_labels))
        برو restart;
      بشکن;
    پیشفرض:
    عبارت_stmt:
      stmt = c_finish_عبارت_stmt (loc, c_parser_expression_conv (parser).مقدار);
    expect_semicolon:
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      بشکن;
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
  اگر (عبارت_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_set_عبارت_location (stmt, loc);

  parser->in_if_block = in_if_block;
}

/* Parse the condition from an if, do, while or for statements.  */

ایستا درخت
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت cond;
  cond = c_parser_expression_conv (parser).مقدار;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, نادرست, پوچ);
  اگر (warn_sequence_point)
    verify_sequence_points (cond);
  بازگشت cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

ایستا درخت
c_parser_paren_condition (c_parser *parser)
{
  درخت cond;
  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت error_mark_گره;
  cond = c_parser_condition (parser);
  parens.skip_until_found_close (parser);
  بازگشت cond;
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

ایستا c_عبارت
c_parser_selection_header (c_parser *parser, منطقی switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_عبارت عبارت;
  منطقی parse_عبارت = درست;
  درخت std_attrs;
  منطقی have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  اگر (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  وگرنه
    std_attrs = NULL_درخت;
  اگر (c_parser_next_tokens_start_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      عبارت.مقدار
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/نادرست,
					 /*static_assert_ok=*/نادرست,
					 /*empty_ok=*/نادرست,
					 /*nested=*/درست,
					 /*start_attr_ok=*/درست,
					 /*simple_ok=*/درست,
					 /*objc_foreach_object_decl=*/nullptr,
					 /*omp_declare_simd_clauses=*/nullptr,
					 have_std_attrs,
					 std_attrs);
      اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      وگرنه
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  اگر (!عبارت.مقدار)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      عبارت.original_type = error_mark_گره;
	      عبارت.set_error ();
	      بازگشت عبارت;
	    }
	  parse_عبارت = نادرست;
	}
      اگر (عبارت.مقدار)
	{
	  عبارت.original_type = درخت_TYPE (عبارت.مقدار);
	  عبارت = convert_lvalue_to_rvalue (loc, عبارت, /*convert_p=*/درست,
					   /*read_p=*/درست);
	}
    }
  وگرنه اگر (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      عبارت.original_type = error_mark_گره;
      عبارت.set_error ();
      بازگشت عبارت;
    }

  اگر (parse_عبارت)
    عبارت = c_parser_expression_conv (parser);
  اگر (!switch_p)
    {
      عبارت.مقدار = c_objc_common_truthvalue_conversion (loc, عبارت.مقدار);
      عبارت.مقدار = c_fully_fold (عبارت.مقدار, نادرست, پوچ);
      اگر (warn_sequence_point)
	verify_sequence_points (عبارت.مقدار);
    }
  بازگشت عبارت;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

ایستا درخت
c_parser_paren_selection_header (c_parser *parser)
{
  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت error_mark_گره;
  درخت cond = c_parser_selection_header (parser, /*switch_p=*/نادرست).مقدار;
  parens.skip_until_found_close (parser);
  بازگشت cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ایستا درخت
c_parser_c99_block_statement (c_parser *parser, منطقی *if_p,
			      location_t *loc_after_labels)
{
  درخت block = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  بازگشت c_end_compound_stmt (loc, block, flag_isoc99);
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

ایستا درخت
c_parser_if_body (c_parser *parser, منطقی *if_p,
		  ثابت token_indent_info &if_tinfo)
{
  درخت block = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  درخت before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
      اگر (!c_parser_next_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  وگرنه اگر (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    add_stmt (c_parser_compound_statement (parser));
  وگرنه
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, پوچ, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, next_tinfo);
  اگر (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    if_tinfo.location, RID_IF);

  بازگشت c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

ایستا درخت
c_parser_else_body (c_parser *parser, ثابت token_indent_info &else_tinfo,
		    vec<درخت> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  درخت block = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  درخت before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      warning_at (loc,
		  OPT_Wempty_body,
	         "suggest braces around empty body in an %<else%> statement");
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
    }
  وگرنه
    {
      اگر (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, پوچ, before_labels, chain, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, next_tinfo);
  اگر (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  بازگشت c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse an if statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   if-statement:
     if ( selection-header ) statement
     if ( selection-header ) statement else statement

   CHAIN is a vector of if-else-if conditions.
   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ایستا تهی
c_parser_if_statement (c_parser *parser, منطقی *if_p, vec<درخت> *chain)
{
  درخت block;
  location_t loc;
  درخت cond;
  منطقی nested_if = نادرست;
  درخت first_body, second_body;
  منطقی in_if_block;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_IF));
  token_indent_info if_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_selection_header (parser);
  in_if_block = parser->in_if_block;
  parser->in_if_block = درست;
  first_body = c_parser_if_body (parser, &nested_if, if_tinfo);
  parser->in_if_block = in_if_block;

  اگر (warn_duplicated_cond)
    warn_duplicated_cond_add_or_warn (عبارت_LOCATION (cond), cond, &chain);

  اگر (c_parser_next_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      اگر (warn_duplicated_cond)
	{
	  اگر (c_parser_next_token_is_keyword (parser, RID_IF)
	      && chain == پوچ)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = جدید vec<درخت> ();
	      اگر (!CONSTANT_CLASS_P (cond) && !درخت_SIDE_EFFECTS (cond))
		chain->safe_افزودن (cond);
	    }
	  وگرنه اگر (!c_parser_next_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      second_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      اگر (if_p != پوچ)
	*if_p = درست;
    }
  وگرنه
    {
      second_body = NULL_درخت;

      /* Diagnose an ambiguous else if if-then-else is nested inside
	 if-then.  */
      اگر (nested_if)
	warning_at (loc, OPT_Wdangling_else,
		    "suggest explicit braces to avoid ambiguous %<else%>");

      اگر (warn_duplicated_cond)
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

ایستا تهی
c_parser_switch_statement (c_parser *parser, منطقی *if_p, درخت before_labels)
{
  ساختار c_عبارت ce;
  درخت block, عبارت, body;
  unsigned نویسه save_in_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  درخت switch_name;
  صحیح رقم_names = c_get_loop_names (before_labels, درست, &switch_name);
  block = c_begin_compound_stmt (flag_isoc99);
  منطقی explicit_cast_p = نادرست;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = درست;
      ce = c_parser_selection_header (parser, /*switch_p=*/درست);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_to_rvalue (switch_cond_loc, ce, درست, درست);
      عبارت = ce.مقدار;
      /* ??? expr has no valid location?  */
      parens.skip_until_found_close (parser);
    }
  وگرنه
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      عبارت = error_mark_گره;
      ce.original_type = error_mark_گره;
    }
  درخت stmt
    = c_start_switch (switch_loc, switch_cond_loc, عبارت, explicit_cast_p,
		      switch_name);
  save_in_statement = in_statement;
  in_statement |= IN_SWITCH_STMT;
  اگر (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  وگرنه
    in_statement &= ~IN_NAMED_STMT;
  location_t loc_after_labels;
  منطقی open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  location_t next_loc = c_parser_peek_token (parser)->location;
  اگر (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, next_loc, switch_loc,
				    RID_SWITCH);
  c_finish_switch (body, ce.original_type);
  in_statement = save_in_statement;
  اگر (رقم_names)
    {
      اگر (!C_DECL_LOOP_SWITCH_NAME_USED (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_درخت;
      وگرنه
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_names (رقم_names);
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

ایستا تهی
c_parser_while_statement (c_parser *parser, منطقی ivdep, unsigned short unroll,
			  منطقی novector, منطقی *if_p, درخت before_labels)
{
  درخت block, cond, body;
  unsigned نویسه save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  درخت loop_name;
  صحیح رقم_names = c_get_loop_names (before_labels, نادرست, &loop_name);

  اگر (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = درست;
    }

  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  اگر (ivdep && cond != error_mark_گره)
    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گره,
				  annot_عبارت_ivdep_kind),
		   integer_zero_گره);
  اگر (unroll && cond != error_mark_گره)
    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گره,
				  annot_عبارت_unroll_kind),
		   build_int_cst (integer_type_گره, unroll));
  اگر (novector && cond != error_mark_گره)
    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گره,
				  annot_عبارت_no_vector_kind),
		   integer_zero_گره);
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  اگر (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  منطقی open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  اگر (loop_name && !C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
    loop_name = NULL_درخت;
  add_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_درخت,
			NULL_درخت));
  add_stmt (c_end_compound_stmt (loc, block, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  اگر (رقم_names)
    c_release_loop_names (رقم_names);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, next_tinfo);

  اگر (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    while_tinfo.location, RID_WHILE);

  in_statement = save_in_statement;
}

/* Parse a do statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   do-statement:
     do statement while ( expression ) ;

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ایستا تهی
c_parser_do_statement (c_parser *parser, منطقی ivdep, unsigned short unroll,
		       منطقی novector, درخت before_labels)
{
  درخت block, cond, body;
  unsigned نویسه save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_DO));
  درخت loop_name;
  صحیح رقم_names = c_get_loop_names (before_labels, نادرست, &loop_name);

  اگر (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = درست;
    }

  c_parser_consume_token (parser);
  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  اگر (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  body = c_parser_c99_block_statement (parser, پوچ);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  in_statement = save_in_statement;
  اگر (رقم_names)
    {
      اگر (!C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
	loop_name = NULL_درخت;
      c_release_loop_names (رقم_names);
    }
  cond = c_parser_paren_condition (parser);
  اگر (ivdep && cond != error_mark_گره)
    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گره,
				  annot_عبارت_ivdep_kind),
		   integer_zero_گره);
  اگر (unroll && cond != error_mark_گره)
    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گره,
				  annot_عبارت_unroll_kind),
 		   build_int_cst (integer_type_گره, unroll));
  اگر (novector && cond != error_mark_گره)
    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گره,
				  annot_عبارت_no_vector_kind),
		   integer_zero_گره);
  اگر (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
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

ایستا تهی
c_parser_for_statement (c_parser *parser, منطقی ivdep, unsigned short unroll,
			منطقی novector, منطقی *if_p, درخت before_labels)
{
  درخت block, cond, incr, body;
  unsigned نویسه save_in_statement;
  درخت save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  درخت object_expression;
  /* Silence the bogus uninitialized warning.  */
  درخت collection_expression = پوچ;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  منطقی is_foreach_statement = نادرست;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  درخت loop_name;
  صحیح رقم_names = c_get_loop_names (before_labels, نادرست, &loop_name);

  اگر (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = درست;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  block = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_گره;
  incr = error_mark_گره;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_expression = error_mark_گره;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = نادرست;
	  c_parser_consume_token (parser);
	  c_finish_عبارت_stmt (loc, NULL_درخت);
	}
      وگرنه اگر (c_parser_next_tokens_start_declaration (parser)
	       || c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, درست, درست, درست, درست, درست,
					 نادرست, &object_expression);
	  parser->objc_could_be_foreach_context = نادرست;

	  اگر (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = درست;
	      اگر (check_for_loop_decls (for_loc, درست) == NULL_درخت)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  وگرنه
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  وقتی (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  اگر (c_parser_next_tokens_start_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_attributes (parser, 2))
	    {
	      صحیح ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, درست, درست, درست, درست,
					     درست, نادرست, &object_expression);
	      parser->objc_could_be_foreach_context = نادرست;

	      restore_extension_diagnostics (ext);
	      اگر (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = درست;
		  اگر (check_for_loop_decls (for_loc, درست) == NULL_درخت)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      وگرنه
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  وگرنه
	    برو init_عبارت;
	}
      وگرنه
	{
	init_عبارت:
	  {
	    ساختار c_عبارت ce;
	    درخت init_expression;
	    ce = c_parser_expression (parser);
	    init_expression = ce.مقدار;
	    parser->objc_could_be_foreach_context = نادرست;
	    اگر (c_parser_next_token_is_keyword (parser, RID_IN))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = درست;
		اگر (! lvalue_p (init_expression))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_expression
		  = c_fully_fold (init_expression, نادرست, پوچ);
	      }
	    وگرنه
	      {
		ce = convert_lvalue_to_rvalue (loc, ce, درست, نادرست);
		init_expression = ce.مقدار;
		c_finish_عبارت_stmt (loc, init_expression);
		c_parser_skip_until_found (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      اگر (!is_foreach_statement)
	{
	  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      اگر (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_گره;
		}
	      وگرنه اگر (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_گره;
		}
	      وگرنه
		{
		  c_parser_consume_token (parser);
		  cond = NULL_درخت;
		}
	    }
	  وگرنه
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_found (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  اگر (ivdep && cond != error_mark_گره)
	    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
			   build_int_cst (integer_type_گره,
					  annot_عبارت_ivdep_kind),
			   integer_zero_گره);
	  اگر (unroll && cond != error_mark_گره)
	    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
 			   build_int_cst (integer_type_گره,
					  annot_عبارت_unroll_kind),
			   build_int_cst (integer_type_گره, unroll));
	  اگر (novector && cond && cond != error_mark_گره)
	    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
			   build_int_cst (integer_type_گره,
					  annot_عبارت_no_vector_kind),
			   integer_zero_گره);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  اگر (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_expression = error_mark_گره;
	    }
	  وگرنه
	    incr = c_process_عبارت_stmt (loc, NULL_درخت);
	}
      وگرنه
	{
	  اگر (is_foreach_statement)
	    collection_expression
	      = c_fully_fold (c_parser_expression (parser).مقدار, نادرست, پوچ);
	  وگرنه
	    {
	      ساختار c_عبارت ce = c_parser_expression (parser);
	      ce = convert_lvalue_to_rvalue (loc, ce, درست, نادرست);
	      incr = c_process_عبارت_stmt (loc, ce.مقدار);
	    }
	}
      parens.skip_until_found_close (parser);
    }
  save_in_statement = in_statement;
  اگر (is_foreach_statement)
    {
      in_statement = IN_OBJC_FOREACH;
      save_objc_foreach_break_label = objc_foreach_break_label;
      save_objc_foreach_continue_label = objc_foreach_continue_label;
      objc_foreach_break_label = create_artificial_label (loc);
      objc_foreach_continue_label = create_artificial_label (loc);
      اگر (loop_name)
	{
	  gcc_checking_assert (!DECL_CHAIN (loop_name)
			       && !DECL_CHAIN (objc_foreach_break_label));
	  C_DECL_SWITCH_NAME (loop_name) = 1;
	  DECL_CHAIN (loop_name) = objc_foreach_break_label;
	  DECL_CHAIN (objc_foreach_break_label) = objc_foreach_continue_label;
	}
    }
  وگرنه
    in_statement = IN_ITERATION_STMT;
  اگر (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  منطقی open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);

  اگر (loop_name && is_foreach_statement)
    {
      gcc_checking_assert (DECL_CHAIN (loop_name) == objc_foreach_break_label
			   && (DECL_CHAIN (objc_foreach_break_label)
			       == objc_foreach_continue_label));
      C_DECL_SWITCH_NAME (loop_name) = 0;
      DECL_CHAIN (loop_name) = NULL_درخت;
      DECL_CHAIN (objc_foreach_break_label) = NULL_درخت;
    }

  اگر (is_foreach_statement)
    objc_finish_foreach_loop (for_loc, object_expression,
			      collection_expression, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  وگرنه
    add_stmt (build_stmt (for_loc, FOR_STMT, NULL_درخت, cond, incr,
			  body, NULL_درخت,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_USED (loop_name)
			  ? loop_name : NULL_درخت, NULL_درخت, NULL_درخت));
  add_stmt (c_end_compound_stmt (for_loc, block,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, next_tinfo);

  اگر (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    for_tinfo.location, RID_FOR);

  in_statement = save_in_statement;
  اگر (رقم_names)
    c_release_loop_names (رقم_names);
  اگر (is_foreach_statement)
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

ایستا درخت
c_parser_asm_statement (c_parser *parser)
{
  درخت str, outputs, inputs, clobbers, labels, ret;
  منطقی simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  صحیح section, nsections;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);

  /* Handle the asm-qualifier-list.  */
  location_t volatile_loc = UNKNOWN_LOCATION;
  location_t inline_loc = UNKNOWN_LOCATION;
  location_t goto_loc = UNKNOWN_LOCATION;
  برای (;;)
    {
      c_token *token = c_parser_peek_token (parser);
      location_t loc = token->location;
      انتخاب (token->keyword)
	{
	حالت RID_VOLATILE:
	  اگر (volatile_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->مقدار);
	      inform (volatile_loc, "first seen here");
	    }
	  وگرنه
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  ادامه;

	حالت RID_INLINE:
	  اگر (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->مقدار);
	      inform (inline_loc, "first seen here");
	    }
	  وگرنه
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  ادامه;

	حالت RID_GOTO:
	  اگر (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->مقدار);
	      inform (goto_loc, "first seen here");
	    }
	  وگرنه
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  ادامه;

	حالت RID_CONST:
	حالت RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->مقدار);
	  c_parser_consume_token (parser);
	  ادامه;

	پیشفرض:
	  بشکن;
	}
      بشکن;
    }

  منطقی is_volatile = (volatile_loc != UNKNOWN_LOCATION);
  منطقی is_inline = (inline_loc != UNKNOWN_LOCATION);
  منطقی is_goto = (goto_loc != UNKNOWN_LOCATION);

  ret = پوچ;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    برو error;

  str = c_parser_asm_string_literal (parser);
  اگر (str == NULL_درخت)
    برو error_close_paren;

  simple = درست;
  outputs = NULL_درخت;
  inputs = NULL_درخت;
  clobbers = NULL_درخت;
  labels = NULL_درخت;

  اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    برو done_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  برای (section = 0; section < nsections; ++section)
    {
      اگر (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  اگر (section == nsections)
	    {
	      c_parser_error (parser, "expected %<)%>");
	      برو error_close_paren;
	    }
	  c_parser_consume_token (parser);
	}
      وگرنه اگر (!c_parser_require (parser, CPP_COLON,
				  is_goto
				  ? G_("expected %<:%>")
				  : G_("expected %<:%> or %<)%>"),
				  UNKNOWN_LOCATION, is_goto))
	برو error_close_paren;

      /* Once past any colon, we're no longer a simple asm.  */
      simple = نادرست;

      اگر ((!c_parser_next_token_is (parser, CPP_COLON)
	   && !c_parser_next_token_is (parser, CPP_SCOPE)
	   && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	  || section == 3)
	انتخاب (section)
	  {
	  حالت 0:
	    outputs = c_parser_asm_operands (parser);
	    بشکن;
	  حالت 1:
	    inputs = c_parser_asm_operands (parser);
	    بشکن;
	  حالت 2:
	    clobbers = c_parser_asm_clobbers (parser);
	    بشکن;
	  حالت 3:
	    labels = c_parser_asm_goto_operands (parser);
	    بشکن;
	  پیشفرض:
	    gcc_unreachable ();
	  }

      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	برو done_asm;
    }

 done_asm:
  اگر (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
      برو error;
    }

  اگر (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_to_end_of_block_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_عبارت (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  بازگشت ret;

 error_close_paren:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
  برو error;
}

/* Parse asm operands, a GNU extension.

   asm-operands:
     asm-operand
     asm-operands , asm-operand

   asm-operand:
     asm-string-literal ( expression )
     [ identifier ] asm-string-literal ( expression )
*/

ایستا درخت
c_parser_asm_operands (c_parser *parser)
{
  درخت list = NULL_درخت;
  وقتی (درست)
    {
      درخت name, str;
      ساختار c_عبارت عبارت;
      اگر (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
	{
	  c_parser_consume_token (parser);
	  اگر (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      درخت id = c_parser_peek_token (parser)->مقدار;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_LENGTH (id),
				   IDENTIFIER_POINTER (id));
	    }
	  وگرنه
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, پوچ);
	      بازگشت NULL_درخت;
	    }
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	}
      وگرنه
	name = NULL_درخت;
      str = c_parser_asm_string_literal (parser);
      اگر (str == NULL_درخت)
	بازگشت NULL_درخت;
      matching_parens parens;
      اگر (!parens.require_open (parser))
	بازگشت NULL_درخت;
      عبارت = c_parser_expression (parser);
      mark_exp_read (عبارت.مقدار);
      اگر (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
	  بازگشت NULL_درخت;
	}
      list = chainon (list, build_درخت_list (build_درخت_list (name, str),
					     عبارت.مقدار));
      اگر (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وگرنه
	بشکن;
    }
  بازگشت list;
}

/* Parse asm clobbers, a GNU extension.

   asm-clobbers:
     asm-string-literal
     asm-clobbers , asm-string-literal
*/

ایستا درخت
c_parser_asm_clobbers (c_parser *parser)
{
  درخت list = NULL_درخت;
  وقتی (درست)
    {
      درخت str = c_parser_asm_string_literal (parser);
      اگر (str)
	list = درخت_cons (NULL_درخت, str, list);
      وگرنه
	بازگشت NULL_درخت;
      اگر (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وگرنه
	بشکن;
    }
  بازگشت list;
}

/* Parse asm goto labels, a GNU extension.

   asm-goto-operands:
     identifier
     asm-goto-operands , identifier
*/

ایستا درخت
c_parser_asm_goto_operands (c_parser *parser)
{
  درخت list = NULL_درخت;
  وقتی (درست)
    {
      درخت name, label;

      اگر (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->مقدار;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  درخت_USED (label) = 1;
	}
      وگرنه
	{
	  c_parser_error (parser, "expected identifier");
	  بازگشت NULL_درخت;
	}

      name = build_string (IDENTIFIER_LENGTH (name),
			   IDENTIFIER_POINTER (name));
      list = درخت_cons (name, label, list);
      اگر (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وگرنه
	بازگشت nreverse (list);
    }
}

/* Parse a possibly concatenated sequence of string literals.
   TRANSLATE says whether to translate them to the execution character
   set; WIDE_OK says whether any kind of prefixed string literal is
   permitted in this context.  This code is based on that in
   lex_string.  */

ساختار c_عبارت
c_parser_string_literal (c_parser *parser, منطقی translate, منطقی wide_ok)
{
  ساختار c_عبارت ret;
  size_t شمار;
  ساختار obstack str_ob;
  ساختار obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, last_tok_loc;
  شمارش cpp_ttype type;
  درخت مقدار, string_درخت;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  last_tok_loc = linemap_resolve_location (سطر_table, loc,
					   LRK_MACRO_DEFINITION_LOCATION,
					   پوچ);
  type = tok->type;
  انتخاب (type)
    {
    حالت CPP_STRING:
    حالت CPP_WSTRING:
    حالت CPP_STRING16:
    حالت CPP_STRING32:
    حالت CPP_UTF8STRING:
      string_درخت = tok->مقدار;
      بشکن;

    پیشفرض:
      c_parser_error (parser, "expected string literal");
      ret.set_error ();
      ret.مقدار = NULL_درخت;
      ret.original_code = ERROR_MARK;
      ret.original_type = NULL_درخت;
      بازگشت ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  انتخاب (c_parser_peek_2nd_token (parser)->type)
    {
    پیشفرض:
      c_parser_consume_token (parser);
      str.text = (ثابت unsigned نویسه *) درخت_STRING_POINTER (string_درخت);
      str.len = درخت_STRING_LENGTH (string_درخت);
      شمار = 1;
      strs = &str;
      بشکن;

    حالت CPP_STRING:
    حالت CPP_WSTRING:
    حالت CPP_STRING16:
    حالت CPP_STRING32:
    حالت CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      شمار = 0;
      انجامبده
	{
	  c_parser_consume_token (parser);
	  شمار++;
	  str.text = (ثابت unsigned نویسه *) درخت_STRING_POINTER (string_درخت);
	  str.len = درخت_STRING_LENGTH (string_درخت);
	  اگر (type != tok->type)
	    {
	      اگر (type == CPP_STRING)
		type = tok->type;
	      وگرنه اگر (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, اندازه (cpp_string));
	  obstack_grow (&loc_ob, &last_tok_loc, اندازه (location_t));
	  tok = c_parser_peek_token (parser);
	  string_درخت = tok->مقدار;
	  last_tok_loc
	    = linemap_resolve_location (سطر_table, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, پوچ);
	}
      وقتی (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_finish (&str_ob);
    }

  اگر (شمار > 1 && !in_system_header_at (درون_داد_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  اگر ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_in, strs, شمار, &istr, type)))
    {
      مقدار = build_string (istr.len, (ثابت نویسه *) istr.text);
      آزاد (const_cast<unsigned نویسه *> (istr.text));
      اگر (شمار > 1)
	{
	  location_t *locs = (location_t *) obstack_finish (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->record_string_concatenation (شمار, locs);
	}
    }
  وگرنه
    {
      اگر (type != CPP_STRING && !wide_ok)
	{
	  error_at (loc, "a wide string is invalid in this context");
	  type = CPP_STRING;
	}
      /* Callers cannot generally handle error_mark_node in this
	 context, so return the empty string instead.  An error has
	 been issued, either above or from cpp_interpret_string.  */
      انتخاب (type)
	{
	پیشفرض:
	حالت CPP_STRING:
	حالت CPP_UTF8STRING:
	  اگر (type == CPP_UTF8STRING && flag_char8_t)
	    {
	      مقدار = build_string (TYPE_PRECISION (char8_type_گره)
				    / TYPE_PRECISION (char_type_گره),
				    "");  /* char8_t is 8 bits */
	    }
	  وگرنه
	    مقدار = build_string (1, "");
	  بشکن;
	حالت CPP_STRING16:
	  مقدار = build_string (TYPE_PRECISION (char16_type_گره)
				/ TYPE_PRECISION (char_type_گره),
				"\0");  /* char16_t is 16 bits */
	  بشکن;
	حالت CPP_STRING32:
	  مقدار = build_string (TYPE_PRECISION (char32_type_گره)
				/ TYPE_PRECISION (char_type_گره),
				"\0\0\0");  /* char32_t is 32 bits */
	  بشکن;
	حالت CPP_WSTRING:
	  مقدار = build_string (TYPE_PRECISION (wchar_type_گره)
				/ TYPE_PRECISION (char_type_گره),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  بشکن;
        }
    }

  انتخاب (type)
    {
    پیشفرض:
    حالت CPP_STRING:
      درخت_TYPE (مقدار) = char_array_type_گره;
      بشکن;
    حالت CPP_UTF8STRING:
      اگر (flag_char8_t)
	درخت_TYPE (مقدار) = char8_array_type_گره;
      وگرنه
	درخت_TYPE (مقدار) = char_array_type_گره;
      بشکن;
    حالت CPP_STRING16:
      درخت_TYPE (مقدار) = char16_array_type_گره;
      بشکن;
    حالت CPP_STRING32:
      درخت_TYPE (مقدار) = char32_array_type_گره;
      بشکن;
    حالت CPP_WSTRING:
      درخت_TYPE (مقدار) = wchar_array_type_گره;
    }
  مقدار = fix_string_type (مقدار);

  اگر (شمار > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.مقدار = مقدار;
  ret.original_code = STRING_CST;
  ret.original_type = NULL_درخت;
  set_c_عبارت_source_range (&ret, get_range_from_loc (سطر_table, loc));
  ret.m_decimal = 0;
  parser->seen_string_literal = درست;
  بازگشت ret;
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

ایستا ساختار c_عبارت
c_parser_عبارت_no_commas (c_parser *parser, ساختار c_عبارت *after,
			 درخت omp_atomic_lhs)
{
  ساختار c_عبارت lhs, rhs, ret;
  شمارش درخت_code code;
  location_t op_location, exp_location;
  منطقی save_in_omp_for = c_in_omp_for;
  c_in_omp_for = نادرست;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_expression (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_EQ:
      code = NOP_عبارت;
      بشکن;
    حالت CPP_MULT_EQ:
      code = MULT_عبارت;
      بشکن;
    حالت CPP_DIV_EQ:
      code = TRUNC_DIV_عبارت;
      بشکن;
    حالت CPP_MOD_EQ:
      code = TRUNC_MOD_عبارت;
      بشکن;
    حالت CPP_PLUS_EQ:
      code = PLUS_عبارت;
      بشکن;
    حالت CPP_MINUS_EQ:
      code = MINUS_عبارت;
      بشکن;
    حالت CPP_LSHIFT_EQ:
      code = LSHIFT_عبارت;
      بشکن;
    حالت CPP_RSHIFT_EQ:
      code = RSHIFT_عبارت;
      بشکن;
    حالت CPP_AND_EQ:
      code = BIT_AND_عبارت;
      بشکن;
    حالت CPP_XOR_EQ:
      code = BIT_XOR_عبارت;
      بشکن;
    حالت CPP_OR_EQ:
      code = BIT_IOR_عبارت;
      بشکن;
    پیشفرض:
      c_in_omp_for = save_in_omp_for;
      بازگشت lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_عبارت_no_commas (parser, پوچ);
  rhs = convert_lvalue_to_rvalue (exp_location, rhs, درست, درست);

  ret.مقدار = build_modify_عبارت (op_location, lhs.مقدار, lhs.original_type,
				 code, exp_location, rhs.مقدار,
				 rhs.original_type);
  ret.m_decimal = 0;
  set_c_عبارت_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  اگر (code == NOP_عبارت)
    ret.original_code = MODIFY_عبارت;
  وگرنه
    {
      suppress_warning (ret.مقدار, OPT_Wparentheses);
      ret.original_code = ERROR_MARK;
    }
  ret.original_type = پوچ;
  c_in_omp_for = save_in_omp_for;
  بازگشت ret;
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

ایستا ساختار c_عبارت
c_parser_conditional_expression (c_parser *parser, ساختار c_عبارت *after,
				 درخت omp_atomic_lhs)
{
  ساختار c_عبارت cond, exp1, exp2, ret;
  location_t start, cond_loc, colon_loc;
  منطقی save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_دودویی_expression (parser, after, omp_atomic_lhs);

  اگر (c_parser_next_token_is_not (parser, CPP_QUERY))
    بازگشت cond;
  c_omp_array_section_p = نادرست;
  اگر (cond.مقدار != error_mark_گره)
    start = cond.get_start ();
  وگرنه
    start = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_to_rvalue (cond_loc, cond, درست, درست);
  c_parser_consume_token (parser);
  اگر (c_parser_next_token_is (parser, CPP_COLON))
    {
      درخت eptype = NULL_درخت;

      location_t میانه_loc = c_parser_peek_token (parser)->location;
      pedwarn (میانه_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      اگر (درخت_CODE (cond.مقدار) == EXCESS_PRECISION_عبارت)
	{
	  eptype = درخت_TYPE (cond.مقدار);
	  cond.مقدار = درخت_OPERAND (cond.مقدار, 0);
	}
      درخت e = cond.مقدار;
      وقتی (درخت_CODE (e) == COMPOUND_عبارت)
	e = درخت_OPERAND (e, 1);
      warn_for_omitted_condop (میانه_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.مقدار = save_عبارت (default_conversion (cond.مقدار));
      اگر (eptype)
	exp1.مقدار = build1 (EXCESS_PRECISION_عبارت, eptype, exp1.مقدار);
      exp1.original_type = پوچ;
      exp1.src_range = cond.src_range;
      cond.مقدار = c_objc_common_truthvalue_conversion (cond_loc, exp1.مقدار);
      c_inhibit_evaluation_warnings += cond.مقدار == truthvalue_true_گره;
    }
  وگرنه
    {
      cond.مقدار
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.مقدار));
      c_inhibit_evaluation_warnings += cond.مقدار == truthvalue_false_گره;
      exp1 = c_parser_expression_conv (parser);
      mark_exp_read (exp1.مقدار);
      c_inhibit_evaluation_warnings +=
	((cond.مقدار == truthvalue_true_گره)
	 - (cond.مقدار == truthvalue_false_گره));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.مقدار == truthvalue_true_گره;
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = پوچ;
      c_omp_array_section_p = save_c_omp_array_section_p;
      بازگشت ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_expression (parser, پوچ, NULL_درخت);
    exp2 = convert_lvalue_to_rvalue (exp2_loc, exp2, درست, درست);
  }
  c_inhibit_evaluation_warnings -= cond.مقدار == truthvalue_true_گره;
  location_t loc1 = make_location (exp1.get_start (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_start (), exp2.src_range);
  اگر (UNLIKELY (omp_atomic_lhs != پوچ)
      && (درخت_CODE (cond.مقدار) == GT_عبارت
	  || درخت_CODE (cond.مقدار) == LT_عبارت
	  || درخت_CODE (cond.مقدار) == EQ_عبارت)
      && c_درخت_equal (exp2.مقدار, omp_atomic_lhs)
      && (c_درخت_equal (درخت_OPERAND (cond.مقدار, 0), omp_atomic_lhs)
	  || c_درخت_equal (درخت_OPERAND (cond.مقدار, 1), omp_atomic_lhs)))
    ret.مقدار = build3_loc (colon_loc, COND_عبارت, درخت_TYPE (omp_atomic_lhs),
			    cond.مقدار, exp1.مقدار, exp2.مقدار);
  وگرنه
    ret.مقدار
      = build_conditional_عبارت (colon_loc, cond.مقدار,
				cond.original_code == C_MAYBE_CONST_عبارت,
				exp1.مقدار, exp1.original_type, loc1,
				exp2.مقدار, exp2.original_type, loc2);
  ret.original_code = ERROR_MARK;
  اگر (exp1.مقدار == error_mark_گره || exp2.مقدار == error_mark_گره)
    ret.original_type = پوچ;
  وگرنه
    {
      درخت t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : درخت_TYPE (exp1.مقدار);
      t2 = exp2.original_type ? exp2.original_type : درخت_TYPE (exp2.مقدار);
      ret.original_type = ((t1 != error_mark_گره
			    && t2 != error_mark_گره
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : پوچ);
    }
  set_c_عبارت_source_range (&ret, start, exp2.get_finish ());
  ret.m_decimal = 0;
  c_omp_array_section_p = save_c_omp_array_section_p;
  بازگشت ret;
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

ایستا ساختار c_عبارت
c_parser_دودویی_expression (c_parser *parser, ساختار c_عبارت *after,
			    درخت omp_atomic_lhs)
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

  ساختار {
    /* The expression at this stack level.  */
    ساختار c_عبارت عبارت;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    شمارش c_parser_prec prec;
    /* The operation on its left.  */
    شمارش درخت_code op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    درخت sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    درخت orig_عبارت;
  } پشته[رقم_PRECS];
  صحیح sp;
  /* Location of the binary operator.  */
  location_t دودویی_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#define برداشت_2								      \
  انجامبده {									      \
    انتخاب (پشته[sp].op)						      \
      {									      \
      حالت TRUTH_ANDIF_عبارت:						      \
	c_inhibit_evaluation_warnings -= (پشته[sp - 1].عبارت.مقدار	      \
					  == truthvalue_false_گره);	      \
	بشکن;								      \
      حالت TRUTH_ORIF_عبارت:						      \
	c_inhibit_evaluation_warnings -= (پشته[sp - 1].عبارت.مقدار	      \
					  == truthvalue_true_گره);	      \
	بشکن;								      \
      حالت TRUNC_DIV_عبارت:						      \
	اگر ((پشته[sp - 1].عبارت.original_code == SIZEOF_عبارت		      \
	     || پشته[sp - 1].عبارت.original_code == PAREN_SIZEOF_عبارت)	      \
	    && (پشته[sp].عبارت.original_code == SIZEOF_عبارت		      \
		|| پشته[sp].عبارت.original_code == PAREN_SIZEOF_عبارت))	      \
	  {								      \
	    درخت type0 = پشته[sp - 1].sizeof_arg;			      \
	    درخت type1 = پشته[sp].sizeof_arg;				      \
	    درخت first_arg = type0;					      \
	    اگر (!TYPE_P (type0))					      \
	      type0 = درخت_TYPE (type0);				      \
	    اگر (!TYPE_P (type1))					      \
	      type1 = درخت_TYPE (type1);				      \
	    اگر (POINTER_TYPE_P (type0)					      \
		&& comptypes (درخت_TYPE (type0), type1)			      \
		&& !(درخت_CODE (first_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (first_arg)			      \
		     && warn_sizeof_array_argument))			      \
	      {								      \
		auto_diagnostic_group d;				      \
		اگر (warning_at (پشته[sp].loc, OPT_Wsizeof_pointer_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  اگر (DECL_P (first_arg))				      \
		    inform (DECL_SOURCE_LOCATION (first_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    وگرنه اگر (درخت_CODE (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (درخت_TYPE (type0)))  \
		     && پشته[sp].عبارت.original_code != PAREN_SIZEOF_عبارت)    \
	      maybe_warn_sizeof_array_div (پشته[sp].loc, first_arg, type0,   \
					   پشته[sp].sizeof_arg, type1);      \
	  }								      \
	بشکن;								      \
      پیشفرض:								      \
	بشکن;								      \
      }									      \
    پشته[sp - 1].عبارت							      \
      = convert_lvalue_to_rvalue (پشته[sp - 1].loc,			      \
				  پشته[sp - 1].عبارت, درست, درست);	      \
    پشته[sp].عبارت							      \
      = convert_lvalue_to_rvalue (پشته[sp].loc,			      \
				  پشته[sp].عبارت, درست, درست);		      \
    اگر (UNLIKELY (omp_atomic_lhs != NULL_درخت) && sp == 1		      \
	&& ((c_parser_next_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << پشته[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_SHIFT)		      \
		     | (1 << PREC_ADD) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_next_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_گره			      \
		     && c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (پشته[sp].prec == PREC_REL || پشته[sp].prec == PREC_EQ)))\
	&& پشته[sp].op != TRUNC_MOD_عبارت				      \
	&& پشته[sp].op != GE_عبارت					      \
	&& پشته[sp].op != LE_عبارت					      \
	&& پشته[sp].op != NE_عبارت					      \
	&& پشته[0].عبارت.مقدار != error_mark_گره			      \
	&& پشته[1].عبارت.مقدار != error_mark_گره			      \
	&& (omp_atomic_lhs == void_list_گره				      \
	    || c_درخت_equal (پشته[0].عبارت.مقدار, omp_atomic_lhs)	      \
	    || c_درخت_equal (پشته[1].عبارت.مقدار, omp_atomic_lhs)	      \
	    || (پشته[sp].op == EQ_عبارت					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	درخت t = make_گره (پشته[1].op);				      \
	درخت_TYPE (t) = درخت_TYPE (پشته[0].عبارت.مقدار);		      \
	درخت_OPERAND (t, 0) = پشته[0].عبارت.مقدار;			      \
	درخت_OPERAND (t, 1) = پشته[1].عبارت.مقدار;			      \
	پشته[0].عبارت.مقدار = t;					      \
	پشته[0].عبارت.m_decimal = 0;					      \
      }									      \
    وگرنه								      \
      پشته[sp - 1].عبارت = parser_build_دودویی_op (پشته[sp].loc,	      \
						   پشته[sp].op,	      \
						   پشته[sp - 1].عبارت,	      \
						   پشته[sp].عبارت,	      \
						   پشته[sp - 1].orig_عبارت);  \
    پشته[sp - 1].orig_عبارت = NULL_درخت;				      \
    sp--;								      \
  } وقتی (0)
  gcc_assert (!after || c_dialect_objc ());
  پشته[0].loc = c_parser_peek_token (parser)->location;
  پشته[0].عبارت = c_parser_cast_expression (parser, after);
  پشته[0].prec = PREC_NONE;
  پشته[0].sizeof_arg = c_last_sizeof_arg;
  پشته[0].orig_عبارت = NULL_درخت;
  sp = 0;
  وقتی (درست)
    {
      شمارش c_parser_prec oprec;
      شمارش درخت_code ocode;
      source_range src_range;
      اگر (parser->error)
	برو out;
      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_عبارت;
	  بشکن;
	حالت CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_عبارت;
	  بشکن;
	حالت CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_عبارت;
	  بشکن;
	حالت CPP_PLUS:
	  oprec = PREC_ADD;
	  ocode = PLUS_عبارت;
	  بشکن;
	حالت CPP_MINUS:
	  oprec = PREC_ADD;
	  ocode = MINUS_عبارت;
	  بشکن;
	حالت CPP_LSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = LSHIFT_عبارت;
	  بشکن;
	حالت CPP_RSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = RSHIFT_عبارت;
	  بشکن;
	حالت CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_عبارت;
	  بشکن;
	حالت CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_عبارت;
	  بشکن;
	حالت CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_عبارت;
	  بشکن;
	حالت CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_عبارت;
	  بشکن;
	حالت CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_عبارت;
	  بشکن;
	حالت CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_عبارت;
	  بشکن;
	حالت CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = BIT_AND_عبارت;
	  بشکن;
	حالت CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = BIT_XOR_عبارت;
	  بشکن;
	حالت CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = BIT_IOR_عبارت;
	  بشکن;
	حالت CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_عبارت;
	  بشکن;
	حالت CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_عبارت;
	  بشکن;
	پیشفرض:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  برو out;
	}
      دودویی_loc = c_parser_peek_token (parser)->location;
      وقتی (oprec <= پشته[sp].prec)
	برداشت_2;
      c_parser_consume_token (parser);
      انتخاب (ocode)
	{
	حالت TRUTH_ANDIF_عبارت:
	  src_range = پشته[sp].عبارت.src_range;
	  پشته[sp].عبارت
	    = convert_lvalue_to_rvalue (پشته[sp].loc,
					پشته[sp].عبارت, درست, درست);
	  پشته[sp].orig_عبارت = پشته[sp].عبارت.مقدار;
	  پشته[sp].عبارت.مقدار = c_objc_common_truthvalue_conversion
	    (پشته[sp].loc, default_conversion (پشته[sp].عبارت.مقدار));
	  c_inhibit_evaluation_warnings += (پشته[sp].عبارت.مقدار
					    == truthvalue_false_گره);
	  set_c_عبارت_source_range (&پشته[sp].عبارت, src_range);
	  بشکن;
	حالت TRUTH_ORIF_عبارت:
	  src_range = پشته[sp].عبارت.src_range;
	  پشته[sp].عبارت
	    = convert_lvalue_to_rvalue (پشته[sp].loc,
					پشته[sp].عبارت, درست, درست);
	  پشته[sp].orig_عبارت = پشته[sp].عبارت.مقدار;
	  پشته[sp].عبارت.مقدار = c_objc_common_truthvalue_conversion
	    (پشته[sp].loc, default_conversion (پشته[sp].عبارت.مقدار));
	  c_inhibit_evaluation_warnings += (پشته[sp].عبارت.مقدار
					    == truthvalue_true_گره);
	  set_c_عبارت_source_range (&پشته[sp].عبارت, src_range);
	  بشکن;
	پیشفرض:
	  بشکن;
	}
      sp++;
      پشته[sp].loc = دودویی_loc;
      پشته[sp].عبارت = c_parser_cast_expression (parser, پوچ);
      پشته[sp].prec = oprec;
      پشته[sp].op = ocode;
      پشته[sp].sizeof_arg = c_last_sizeof_arg;
      پشته[sp].orig_عبارت = NULL_درخت;
    }
 out:
  وقتی (sp > 0)
    برداشت_2;
  بازگشت پشته[0].عبارت;
#undef برداشت_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

ایستا ساختار c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  منطقی seen_scspec = نادرست;
  ساختار c_declspecs *specs = build_null_declspecs ();
  وقتی (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_CONSTEXPR:
	حالت RID_REGISTER:
	حالت RID_STATIC:
	حالت RID_THREAD:
	  seen_scspec = درست;
	  declspecs_add_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->مقدار);
	  c_parser_consume_token (parser);
	  بشکن;
	پیشفرض:
	  برو out;
	}
    }
 out:
  بازگشت seen_scspec ? specs : پوچ;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

ایستا ساختار c_عبارت
c_parser_cast_expression (c_parser *parser, ساختار c_عبارت *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  اگر (after)
    بازگشت c_parser_postfix_expression_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      ساختار c_declspecs *scspecs;
      ساختار c_type_name *type_name;
      ساختار c_عبارت ret;
      ساختار c_عبارت عبارت;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, درست);
      parens.skip_until_found_close (parser);
      اگر (type_name == پوچ)
	{
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = پوچ;
	  بازگشت ret;
	}

      /* Save casted types in the function's used types hash table.  */
      used_types_درج (type_name->specs->type);

      اگر (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	بازگشت c_parser_postfix_expression_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      اگر (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      اگر (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t عبارت_loc = c_parser_peek_token (parser)->location;
	عبارت = c_parser_cast_expression (parser, پوچ);
	عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, درست, درست);
      }
      ret.مقدار = c_cast_عبارت (cast_loc, type_name, عبارت.مقدار);
      اگر (ret.مقدار && عبارت.مقدار)
	set_c_عبارت_source_range (&ret, cast_loc, عبارت.get_finish ());
      ret.original_code = ERROR_MARK;
      ret.original_type = پوچ;
      ret.m_decimal = 0;
      بازگشت ret;
    }
  وگرنه
    بازگشت c_parser_unary_expression (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

ایستا تهی
mark_exp_read_cond (درخت exp)
{
  اگر ((VAR_P (exp) || درخت_CODE (exp) == PARM_DECL)
      && (VAR_P (exp) ? warn_unused_but_set_variable
		      : warn_unused_but_set_parameter) > 1)
    بازگشت;

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

ایستا ساختار c_عبارت
c_parser_unary_expression (c_parser *parser)
{
  صحیح ext;
  ساختار c_عبارت ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t exp_loc;
  location_t finish;
  ret.original_code = ERROR_MARK;
  ret.original_type = پوچ;
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, پوچ);
      mark_exp_read_cond (op.مقدار);
      op = default_function_array_conversion (exp_loc, op);
      بازگشت parser_build_unary_op (op_loc, PREINCREMENT_عبارت, op);
    حالت CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, پوچ);
      mark_exp_read_cond (op.مقدار);
      op = default_function_array_conversion (exp_loc, op);
      بازگشت parser_build_unary_op (op_loc, PREDECREMENT_عبارت, op);
    حالت CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, پوچ);
      mark_exp_read (op.مقدار);
      بازگشت parser_build_unary_op (op_loc, ADDR_عبارت, op);
    حالت CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_expression (parser, پوچ);
	finish = op.get_finish ();
	op = convert_lvalue_to_rvalue (exp_loc, op, درست, درست);
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.مقدار = build_indirect_ref (combined_loc, op.مقدار, RO_UNARY_STAR);
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ret.m_decimal = 0;
	بازگشت ret;
      }
    حالت CPP_PLUS:
      اگر (!c_dialect_objc () && !in_system_header_at (درون_داد_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, پوچ);
      op = convert_lvalue_to_rvalue (exp_loc, op, درست, درست);
      بازگشت parser_build_unary_op (op_loc, CONVERT_عبارت, op);
    حالت CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, پوچ);
      op = convert_lvalue_to_rvalue (exp_loc, op, درست, درست);
      بازگشت parser_build_unary_op (op_loc, NEGATE_عبارت, op);
    حالت CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, پوچ);
      op = convert_lvalue_to_rvalue (exp_loc, op, درست, درست);
      بازگشت parser_build_unary_op (op_loc, BIT_NOT_عبارت, op);
    حالت CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, پوچ);
      op = convert_lvalue_to_rvalue (exp_loc, op, درست, درست);
      بازگشت parser_build_unary_op (op_loc, TRUTH_NOT_عبارت, op);
    حالت CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      اگر (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ret.مقدار = finish_label_address_عبارت
	    (c_parser_peek_token (parser)->مقدار, op_loc);
	  set_c_عبارت_source_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_finish ());
	  c_parser_consume_token (parser);
	}
      وگرنه
	{
	  c_parser_error (parser, "expected identifier");
	  ret.set_error ();
	}
      بازگشت ret;
    حالت CPP_KEYWORD:
      {
	شمارش rid rid = c_parser_peek_token (parser)->keyword;
	انتخاب (rid)
	  {
	  حالت RID_COUNTOF:
	  حالت RID_SIZEOF:
	    بازگشت c_parser_sizeof_or_countof_expression (parser, rid);
	  حالت RID_ALIGNOF:
	    بازگشت c_parser_alignof_expression (parser);
	  حالت RID_MAXOF:
	  حالت RID_MINOF:
	    بازگشت c_parser_maxof_or_minof_expression (parser, rid);
	  حالت RID_BUILTIN_HAS_ATTRIBUTE:
	    بازگشت c_parser_has_attribute_expression (parser);
	  حالت RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_expression (parser, پوچ);
	    restore_extension_diagnostics (ext);
	    بازگشت ret;
	  حالت RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, پوچ);
	    op = default_function_array_conversion (exp_loc, op);
	    بازگشت parser_build_unary_op (op_loc, REALPART_عبارت, op);
	  حالت RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, پوچ);
	    op = default_function_array_conversion (exp_loc, op);
	    بازگشت parser_build_unary_op (op_loc, IMAGPART_عبارت, op);
	  حالت RID_TRANSACTION_ATOMIC:
	  حالت RID_TRANSACTION_RELAXED:
	    بازگشت c_parser_transaction_expression (parser, rid);
	  حالت RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.مقدار = void_گره;
	    set_c_عبارت_source_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    بازگشت ret;
	  پیشفرض:
	    بازگشت c_parser_postfix_expression (parser);
	  }
      }
    پیشفرض:
      بازگشت c_parser_postfix_expression (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

ایستا ساختار c_عبارت
c_parser_sizeof_or_countof_expression (c_parser *parser, شمارش rid rid)
{
  ثابت نویسه *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  ساختار c_عبارت عبارت;
  ساختار c_عبارت result;
  location_t عبارت_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  اگر (rid == RID_COUNTOF)
    pedwarn_c23 (start, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  اگر (rid == RID_COUNTOF)
    in_countof++;
  وگرنه
    in_sizeof++;
  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      ساختار c_declspecs *scspecs;
      ساختار c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      عبارت_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, درست);
      parens.skip_until_found_close (parser);
      finish = parser->tokens_buf[0].location;
      اگر (type_name == پوچ)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  عبارت.set_error ();
	  برو Xof_عبارت;
	}
      اگر (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  عبارت = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       عبارت_loc);
	  finish = عبارت.get_finish ();
	  برو Xof_عبارت;
	}
      /* sizeof ( type-name ).  */
      اگر (scspecs)
	error_at (عبارت_loc, "storage class specifier in %qs", op_name);
      اگر (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      اگر (rid == RID_COUNTOF)
	{
	  in_countof--;
	  result = c_عبارت_countof_type (عبارت_loc, type_name);
	}
      وگرنه
	{
	  in_sizeof--;
	  result = c_عبارت_sizeof_type (عبارت_loc, type_name);
	}
    }
  وگرنه
    {
      عبارت_loc = c_parser_peek_token (parser)->location;
      عبارت = c_parser_unary_expression (parser);
      finish = عبارت.get_finish ();
    Xof_عبارت:
      c_inhibit_evaluation_warnings--;
      اگر (rid == RID_COUNTOF)
	in_countof--;
      وگرنه
	in_sizeof--;
      mark_exp_read (عبارت.مقدار);
      اگر (درخت_CODE (عبارت.مقدار) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (درخت_OPERAND (عبارت.مقدار, 1)))
	error_at (عبارت_loc, "%qs applied to a bit-field", op_name);
      اگر (rid == RID_COUNTOF)
	result = c_عبارت_countof_عبارت (عبارت_loc, عبارت);
      وگرنه
	result = c_عبارت_sizeof_عبارت (عبارت_loc, عبارت);
    }
  اگر (finish == UNKNOWN_LOCATION)
    finish = start;
  set_c_عبارت_source_range (&result, start, finish);
  بازگشت result;
}

/* Parse an alignof expression.  */

ایستا ساختار c_عبارت
c_parser_alignof_expression (c_parser *parser)
{
  ساختار c_عبارت عبارت;
  location_t start_loc = c_parser_peek_token (parser)->location;
  location_t end_loc;
  درخت alignof_spelling = c_parser_peek_token (parser)->مقدار;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNOF));
  منطقی is_c11_alignof = (strcmp (IDENTIFIER_POINTER (alignof_spelling),
				"_Alignof") == 0
			 || strcmp (IDENTIFIER_POINTER (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  اگر (is_c11_alignof)
    {
      اگر (flag_isoc99)
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      وگرنه
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_alignof++;
  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      ساختار c_declspecs *scspecs;
      ساختار c_type_name *type_name;
      ساختار c_عبارت ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, درست);
      end_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
      اگر (type_name == پوچ)
	{
	  ساختار c_عبارت ret;
	  c_inhibit_evaluation_warnings--;
	  in_alignof--;
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = پوچ;
	  بازگشت ret;
	}
      اگر (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  عبارت = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  برو alignof_عبارت;
	}
      /* alignof ( type-name ).  */
      اگر (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      اگر (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      ret.مقدار = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       پوچ, پوچ),
					    نادرست, is_c11_alignof, 1);
      ret.original_code = ERROR_MARK;
      ret.original_type = پوچ;
      set_c_عبارت_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      بازگشت ret;
    }
  وگرنه
    {
      ساختار c_عبارت ret;
      عبارت = c_parser_unary_expression (parser);
      end_loc = عبارت.src_range.m_finish;
    alignof_عبارت:
      mark_exp_read (عبارت.مقدار);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      اگر (is_c11_alignof)
	pedwarn (start_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.مقدار = c_alignof_عبارت (start_loc, عبارت.مقدار);
      ret.original_code = ERROR_MARK;
      ret.original_type = پوچ;
      set_c_عبارت_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      بازگشت ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

ایستا ساختار c_عبارت
c_parser_maxof_or_minof_expression (c_parser *parser, شمارش rid rid)
{
  ثابت نویسه *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  ساختار c_عبارت result;
  location_t عبارت_loc;
  ساختار c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  pedwarn (start, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  اگر (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      برو fail;
    }
  parens.consume_open (parser);
  عبارت_loc = c_parser_peek_token (parser)->location;
  اگر (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (عبارت_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_found_close (parser);
      برو fail;
    }
  type_name = c_parser_type_name (parser, درست);
  اگر (type_name == پوچ)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_found_close (parser);
      برو fail;
    }
  parens.skip_until_found_close (parser);
  finish = parser->tokens_buf[0].location;
  اگر (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  اگر (rid == RID_MAXOF)
    result = c_عبارت_maxof_type (عبارت_loc, type_name);
  وگرنه
    result = c_عبارت_minof_type (عبارت_loc, type_name);
  set_c_عبارت_source_range (&result, start, finish);
  بازگشت result;
fail:
  c_inhibit_evaluation_warnings--;
  result.set_error ();
  result.original_code = ERROR_MARK;
  result.original_type = پوچ;
  بازگشت result;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

ایستا ساختار c_عبارت
c_parser_has_attribute_expression (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t start = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;

      ساختار c_عبارت result;
      result.set_error ();
      result.original_code = ERROR_MARK;
      result.original_type = پوچ;
      بازگشت result;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  in_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  درخت oper = NULL_درخت;
  اگر (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      ساختار c_type_name *tname = c_parser_type_name (parser);
      in_typeof--;
      اگر (tname)
	{
	  oper = groktypename (tname, پوچ, پوچ);
	  برداشت_maybe_used (c_type_variably_modified_p (oper));
	}
    }
  وگرنه
    {
      ساختار c_عبارت cexpr = c_parser_عبارت_no_commas (parser, پوچ);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      اگر (cexpr.مقدار != error_mark_گره)
	{
	  mark_exp_read (cexpr.مقدار);
	  oper = cexpr.مقدار;
	  درخت etype = درخت_TYPE (oper);
	  منطقی was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  اگر (was_vm)
	    oper = c_fully_fold (oper, نادرست, پوچ);
	  برداشت_maybe_used (was_vm);
	}
    }

  ساختار c_عبارت result;
  result.original_code = ERROR_MARK;
  result.original_type = پوچ;

  اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      result.set_error ();
      بازگشت result;
    }

  منطقی save_translate_strings_p = parser->translate_strings_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  درخت attr = c_parser_gnu_attribute (parser, NULL_درخت, نادرست, نادرست);

  parser->translate_strings_p = save_translate_strings_p;

  location_t finish = c_parser_peek_token (parser)->location;
  اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  وگرنه
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);

      result.set_error ();
      بازگشت result;
    }

  اگر (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      result.set_error ();
      بازگشت result;
    }

  result.original_code = INTEGER_CST;
  result.original_type = boolean_type_گره;

  اگر (has_attribute (atloc, oper, attr, default_conversion))
    result.مقدار = boolean_true_گره;
  وگرنه
    result.مقدار =  boolean_false_گره;

  set_c_عبارت_source_range (&result, start, finish);
  result.m_decimal = 0;
  بازگشت result;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
ایستا منطقی
c_parser_get_builtin_args (c_parser *parser, ثابت نویسه *bname,
			   vec<c_عبارت_t, va_gc> **ret_cexpr_list,
			   منطقی choose_عبارت_p,
			   location_t *out_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_عبارت_t, va_gc> *cexpr_list;
  c_عبارت_t عبارت;
  منطقی saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = پوچ;
  اگر (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      بازگشت نادرست;
    }

  c_parser_consume_token (parser);

  اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      *out_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      بازگشت درست;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= choose_عبارت_p;
  عبارت = c_parser_عبارت_no_commas (parser, پوچ);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_safe_افزودن (cexpr_list, عبارت);
  وقتی (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      اگر (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  درخت مقدار = embed->مقدار;
	  عبارت.original_code = INTEGER_CST;
	  عبارت.original_type = integer_type_گره;
	  عبارت.مقدار = NULL_درخت;
	  set_c_عبارت_source_range (&عبارت, embed->get_range ());
	  عبارت.m_decimal = 0;
	  برای (unsigned صحیح i = 0; i < (unsigned) RAW_DATA_LENGTH (مقدار); i++)
	    {
	      عبارت.مقدار = build_int_cst (integer_type_گره,
					  RAW_DATA_UCHAR_ELT (مقدار, i));
	      vec_safe_افزودن (cexpr_list, عبارت);
	    }
	  c_parser_consume_token (parser);
	  ادامه;
	}
      عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      vec_safe_افزودن (cexpr_list, عبارت);
    }

  *out_close_paren_loc = c_parser_peek_token (parser)->location;
  اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    بازگشت نادرست;

  *ret_cexpr_list = cexpr_list;
  بازگشت درست;
}

/* This represents a single generic-association.  */

ساختار c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  درخت type;
  /* The association's expression.  */
  ساختار c_عبارت expression;
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

ایستا ساختار c_عبارت
c_parser_generic_selection (c_parser *parser)
{
  ساختار c_عبارت selector, error_عبارت;
  درخت selector_type;
  ساختار c_generic_association matched_assoc;
  صحیح match_found = -1;
  location_t generic_loc, selector_loc;

  error_عبارت.original_code = ERROR_MARK;
  error_عبارت.original_type = پوچ;
  error_عبارت.set_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_درخت;
  matched_assoc.expression = error_عبارت;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_GENERIC));
  generic_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  اگر (flag_isoc99)
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C99 does not support %<_Generic%>");
  وگرنه
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C90 does not support %<_Generic%>");

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت error_عبارت;

  selector_loc = c_parser_peek_token (parser)->location;
  اگر (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      c_inhibit_evaluation_warnings++;
      pedwarn_c23 (selector_loc, OPT_Wpedantic,
		   "ISO C does not support use of type name as %<_Generic%> "
		   "controlling operand before C2Y");
      ساختار c_type_name *type = c_parser_type_name (parser);
      اگر (type)
	selector_type = groktypename (type, پوچ, پوچ);
      c_inhibit_evaluation_warnings--;
      اگر (!type)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
	  بازگشت error_عبارت;
	}
    }
  وگرنه
    {
      c_inhibit_evaluation_warnings++;
      in_generic++;
      selector = c_parser_عبارت_no_commas (parser, پوچ);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      in_generic--;
      برداشت_maybe_used (!flag_isoc23);

      اگر (selector.مقدار == error_mark_گره)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
	  بازگشت selector;
	}
      mark_exp_read (selector.مقدار);
      selector_type = درخت_TYPE (selector.مقدار);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      اگر (درخت_CODE (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      اگر (FUNCTION_POINTER_TYPE_P (selector_type)
	  && TYPE_QUALS (درخت_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_pointer_type (TYPE_MAIN_VARIANT (درخت_TYPE (selector_type)));
    }

  اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
      بازگشت error_عبارت;
    }

  auto_vec<c_generic_association> associations;
  ساختار maybe_used_decl *maybe_used_default = پوچ;
  وقتی (1)
    {
      ساختار c_generic_association assoc, *iter;
      unsigned صحیح ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      اگر (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_درخت;
	}
      وگرنه
	{
	  ساختار c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  اگر (type_name == پوچ)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
	      بازگشت error_عبارت;
	    }
	  assoc.type = grokgenassoc (type_name);
	  اگر (assoc.type == error_mark_گره)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
	      بازگشت error_عبارت;
	    }

	  اگر (درخت_CODE (assoc.type) == FUNCTION_TYPE)
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "function type before C2Y");
	  وگرنه اگر (!COMPLETE_TYPE_P (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "incomplete type before C2Y");

	  اگر (c_type_variably_modified_p (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "variably-modified type before C2Y");
	}

      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
	  بازگشت error_عبارت;
	}

      منطقی match = assoc.type == NULL_درخت
		   || comptypes (assoc.type, selector_type);

      اگر (!match || matched_assoc.type != NULL_درخت)
	c_inhibit_evaluation_warnings++;
      in_generic++;

      assoc.expression = c_parser_عبارت_no_commas (parser, پوچ);

      اگر (!match || matched_assoc.type != NULL_درخت)
	c_inhibit_evaluation_warnings--;
      in_generic--;
      اگر (!match)
	برداشت_maybe_used (!flag_isoc23);
      وگرنه اگر (assoc.type == NULL_درخت)
	maybe_used_default = save_maybe_used ();
      وگرنه
	برداشت_maybe_used (درست);

      اگر (assoc.expression.مقدار == error_mark_گره)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
	  بازگشت error_عبارت;
	}

      برای (ix = 0; associations.iterate (ix, &iter); ++ix)
	{
	  اگر (assoc.type == NULL_درخت)
	    {
	      اگر (iter->type == NULL_درخت)
		{
		  error_at (assoc.type_location,
			    "duplicate %<default%> case in %<_Generic%>");
		  inform (iter->type_location, "original %<default%> is here");
		}
	    }
	  وگرنه اگر (iter->type != NULL_درخت)
	    {
	      اگر (comptypes (assoc.type, iter->type))
		{
		  error_at (assoc.type_location,
			    "%<_Generic%> specifies two compatible types");
		  inform (iter->type_location, "compatible type is here");
		}
	    }
	}

      اگر (assoc.type == NULL_درخت)
	{
	  اگر (match_found < 0)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	}
      وگرنه اگر (match)
	{
	  اگر (match_found < 0 || matched_assoc.type == NULL_درخت)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	  وگرنه
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.safe_افزودن (assoc);

      اگر (c_parser_peek_token (parser)->type != CPP_COMMA)
	بشکن;
      c_parser_consume_token (parser);
    }

  اگر (match_found >= 0 && matched_assoc.type == NULL_درخت)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_used (maybe_used_default);
      برداشت_maybe_used (درست);
    }
  وگرنه اگر (maybe_used_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_used (maybe_used_default);
      برداشت_maybe_used (!flag_isoc23);
    }

  unsigned صحیح ix;
  ساختار c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    اگر (ix != (unsigned) match_found)
      mark_exp_read (iter->expression.مقدار);

  اگر (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
      بازگشت error_عبارت;
    }

  اگر (match_found < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      بازگشت error_عبارت;
    }

  بازگشت matched_assoc.expression;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

ایستا unsigned صحیح
check_tgmath_function (c_عبارت *عبارت, unsigned صحیح pos)
{
  درخت type = درخت_TYPE (عبارت->مقدار);
  اگر (!FUNCTION_POINTER_TYPE_P (type))
    {
      error_at (عبارت->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      بازگشت 0;
    }
  type = درخت_TYPE (type);
  اگر (!prototype_p (type))
    {
      error_at (عبارت->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      بازگشت 0;
    }
  اگر (stdarg_p (type))
    {
      error_at (عبارت->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      بازگشت 0;
    }
  unsigned صحیح nargs = 0;
  function_args_iterator iter;
  درخت t;
  FOREACH_FUNCTION_ARGS (type, t, iter)
    {
      اگر (t == void_type_گره)
	بشکن;
      nargs++;
    }
  اگر (nargs == 0)
    {
      error_at (عبارت->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      بازگشت 0;
    }
  بازگشت nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
شمارش tgmath_parm_kind
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

ایستا ساختار c_عبارت
c_parser_predefined_identifier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  انتخاب (c_parser_peek_token (parser)->keyword)
    {
    حالت RID_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__FUNCTION__");
      بشکن;
    حالت RID_PRETTY_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__PRETTY_FUNCTION__");
      بشکن;
    حالت RID_C99_FUNCTION_NAME:
      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support "
		   "%<__func__%> predefined identifier");
      بشکن;
    پیشفرض:
      gcc_unreachable ();
    }

  ساختار c_عبارت عبارت;
  عبارت.original_code = ERROR_MARK;
  عبارت.original_type = پوچ;
  عبارت.مقدار = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->مقدار);
  set_c_عبارت_source_range (&عبارت, loc, loc);
  عبارت.m_decimal = 0;
  c_parser_consume_token (parser);
  بازگشت عبارت;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

ایستا منطقی
has_counted_by_object (درخت ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  اگر ((درخت_CODE (ref) == INDIRECT_REF
       && is_access_with_size_p (درخت_OPERAND (ref, 0)))
      || is_access_with_size_p (ref))
    بازگشت درست;
  بازگشت نادرست;
}

/* Get the reference to the counted-by object associated with the REF.  */

ایستا درخت
get_counted_by_ref (درخت ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  اگر (درخت_CODE (ref) == INDIRECT_REF
      && is_access_with_size_p (درخت_OPERAND (ref, 0)))
    بازگشت CALL_عبارت_ARG (درخت_OPERAND (ref, 0), 1);
  وگرنه اگر (is_access_with_size_p (ref))
    بازگشت CALL_عبارت_ARG (ref, 1);

  بازگشت NULL_درخت;
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

ایستا ساختار c_عبارت
c_parser_postfix_expression (c_parser *parser)
{
  ساختار c_عبارت عبارت, e1;
  ساختار c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  عبارت.original_code = ERROR_MARK;
  عبارت.original_type = پوچ;
  عبارت.m_decimal = 0;
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_عدد:
      عبارت.مقدار = c_parser_peek_token (parser)->مقدار;
      set_c_عبارت_source_range (&عبارت, tok_range);
      loc = c_parser_peek_token (parser)->location;
      عبارت.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      اگر (درخت_CODE (عبارت.مقدار) == FIXED_CST
	  && !targetm.fixed_point_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  عبارت.set_error ();
	}
      بشکن;
    حالت CPP_CHAR:
    حالت CPP_CHAR16:
    حالت CPP_CHAR32:
    حالت CPP_UTF8CHAR:
    حالت CPP_WCHAR:
      عبارت.مقدار = c_parser_peek_token (parser)->مقدار;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      عبارت.original_type = char_type_گره;
      set_c_عبارت_source_range (&عبارت, tok_range);
      c_parser_consume_token (parser);
      بشکن;
    حالت CPP_STRING:
    حالت CPP_STRING16:
    حالت CPP_STRING32:
    حالت CPP_WSTRING:
    حالت CPP_UTF8STRING:
      عبارت = c_parser_string_literal (parser, parser->translate_strings_p,
				      درست);
      بشکن;
    حالت CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      عبارت.مقدار
	= objc_build_string_object (c_parser_peek_token (parser)->مقدار);
      set_c_عبارت_source_range (&عبارت, tok_range);
      c_parser_consume_token (parser);
      بشکن;
    حالت CPP_NAME:
      انتخاب (c_parser_peek_token (parser)->id_kind)
	{
	حالت C_ID_ID:
	  {
	    درخت id = c_parser_peek_token (parser)->مقدار;
	    c_parser_consume_token (parser);
	    عبارت.مقدار = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &عبارت.original_type);
	    set_c_عبارت_source_range (&عبارت, tok_range);
	    بشکن;
	  }
	حالت C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    درخت class_name = c_parser_peek_token (parser)->مقدار;
	    درخت component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    اگر (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		عبارت.set_error ();
		بشکن;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->مقدار;
	    location_t end_loc = component_tok->get_finish ();
	    c_parser_consume_token (parser);
	    عبارت.مقدار = objc_build_class_component_ref (class_name,
							 component);
	    set_c_عبارت_source_range (&عبارت, loc, end_loc);
	    بشکن;
	  }
	پیشفرض:
	  c_parser_error (parser, "expected expression");
	  عبارت.set_error ();
	  بشکن;
	}
      بشکن;
    حالت CPP_OPEN_PAREN:
      /* A parenthesized expression, statement expression or compound
	 literal.  */
      اگر (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_BRACE)
	{
	  /* A statement expression.  */
	  درخت stmt;
	  location_t brace_loc;
	  منطقی save_c_omp_array_section_p = c_omp_array_section_p;
	  c_parser_consume_token (parser);
	  brace_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* If we've not yet started the current function's statement list,
	     or we're in the parameter scope of an old-style function
	     declaration, statement expressions are not allowed.  */
	  اگر (!building_stmt_list_p () || old_style_parameter_scope ())
	    {
	      error_at (loc, "braced-group within expression allowed "
			"only inside a function");
	      parser->error = درست;
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, پوچ);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
	      عبارت.set_error ();
	      بشکن;
	    }
	  c_omp_array_section_p = نادرست;
	  stmt = c_begin_stmt_عبارت ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  عبارت.مقدار = c_finish_stmt_عبارت (brace_loc, stmt);
	  set_c_عبارت_source_range (&عبارت, loc, close_loc);
	  mark_exp_read (عبارت.مقدار);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      وگرنه
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  عبارت = c_parser_expression (parser);
	  اگر (درخت_CODE (عبارت.مقدار) == MODIFY_عبارت)
	    suppress_warning (عبارت.مقدار, OPT_Wparentheses);
	  اگر (عبارت.original_code != C_MAYBE_CONST_عبارت
	      && عبارت.original_code != SIZEOF_عبارت)
	    عبارت.original_code = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  اگر (عبارت.original_code == SIZEOF_عبارت)
	    عبارت.original_code = PAREN_SIZEOF_عبارت;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  set_c_عبارت_source_range (&عبارت, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      بشکن;
    حالت CPP_KEYWORD:
      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_FUNCTION_NAME:
	حالت RID_PRETTY_FUNCTION_NAME:
	حالت RID_C99_FUNCTION_NAME:
	  عبارت = c_parser_predefined_identifier (parser);
	  بشکن;
	حالت RID_VA_ARG:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    e1 = c_parser_عبارت_no_commas (parser, پوچ);
	    mark_exp_read (e1.مقدار);
	    e1.مقدار = c_fully_fold (e1.مقدار, نادرست, پوچ);
	    اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
		عبارت.set_error ();
		بشکن;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    اگر (t1 == پوچ)
	      {
		عبارت.set_error ();
	      }
	    وگرنه
	      {
		درخت type_عبارت = NULL_درخت;
		درخت type = groktypename (t1, &type_عبارت, پوچ);
		عبارت.مقدار = c_build_va_arg (start_loc, e1.مقدار, loc,
					     type, type_عبارت);
		set_c_عبارت_source_range (&عبارت, start_loc, end_loc);
	      }
	  }
	  بشکن;
	حالت RID_C23_VA_START:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    e1 = c_parser_عبارت_no_commas (parser, پوچ);
	    e1 = convert_lvalue_to_rvalue (e1.get_location (), e1, درست, درست);
	    اگر (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
		    عبارت.set_error ();
		    بشکن;
		  }
		اگر (c_parser_next_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_kind == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    درخت name = c_parser_peek_token (parser)->مقدار;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    درخت decl = lookup_name (name);
		    درخت last_parm
		      = درخت_last (DECL_ARGUMENTS (current_function_decl));
		    اگر (!last_parm || decl != last_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    وگرنه اگر (DECL_REGISTER (decl))
		      warning_at (nloc, OPT_Wvarargs,
				  "undefined behavior when second parameter "
				  "of %<va_start%> is declared with "
				  "%<register%> storage");
		    c_parser_consume_token (parser);
		  }
		وگرنه
		  {
		    unsigned nesting_depth = 0;
		    location_t sloc = c_parser_peek_token (parser)->location;
		    location_t eloc = sloc;

		    /* For va_start (ap,) the ) comes from stdarg.h.
		       Use location of , in that case, otherwise without
		       -Wsystem-headers nothing is reported.  After all,
		       the problematic token is the comma in that case.  */
		    اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    وقتی (درست)
		      {
			c_token *token = c_parser_peek_token (parser);
			اگر (token->type == CPP_CLOSE_PAREN && !nesting_depth)
			  بشکن;

			اگر (token->type == CPP_EOF)
			  بشکن;
			اگر (token->type == CPP_OPEN_PAREN)
			  ++nesting_depth;
			وگرنه اگر (token->type == CPP_CLOSE_PAREN)
			  --nesting_depth;
			eloc = token->location;
			c_parser_consume_token (parser);
		      }
		    اگر (sloc != eloc)
		      sloc = make_location (sloc, sloc, eloc);
		    warning_at (sloc, OPT_Wvarargs,
				"%<va_start%> macro used with additional "
				"arguments other than identifier of the "
				"last named argument");
		  }
	      }
	    parens.skip_until_found_close (parser);
	    درخت fndecl = builtin_decl_explicit (BUILT_IN_VA_START);
	    vec<درخت, va_gc> *params;
	    vec_alloc (params, 2);
	    params->quick_افزودن (e1.مقدار);
	    params->quick_افزودن (integer_zero_گره);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.quick_افزودن (e1.get_location ());
	    arg_loc.quick_افزودن (UNKNOWN_LOCATION);
	    عبارت.مقدار = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, پوچ);
	    set_c_عبارت_source_range (&عبارت, loc,
				     parser->tokens_buf[0].get_finish ());
	    عبارت.m_decimal = 0;
	    عبارت.original_code = ERROR_MARK;
	    عبارت.original_type = پوچ;
	    release_درخت_vector (params);
	    بشکن;
	  }
	حالت RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    t1 = c_parser_type_name (parser);
	    اگر (t1 == پوچ)
	      parser->error = درست;
	    اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    اگر (parser->error)
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
		عبارت.set_error ();
		بشکن;
	      }
	    درخت type = groktypename (t1, پوچ, پوچ);
	    درخت offsetof_ref;
	    اگر (type == error_mark_گره)
	      offsetof_ref = error_mark_گره;
	    وگرنه
	      {
		offsetof_ref = build1 (INDIRECT_REF, type, null_pointer_گره);
		SET_عبارت_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    اگر (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->مقدار,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		وقتی (c_parser_next_token_is (parser, CPP_DOT)
		       || c_parser_next_token_is (parser,
						  CPP_OPEN_SQUARE)
		       || c_parser_next_token_is (parser,
						  CPP_DEREF))
		  {
		    اگر (c_parser_next_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_گره);
			برو do_dot;
		      }
		    وگرنه اگر (c_parser_next_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			اگر (c_parser_next_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    بشکن;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->مقدار,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    وگرنه
		      {
			ساختار c_عبارت ce;
			درخت idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_expression (parser);
			ce = convert_lvalue_to_rvalue (loc, ce, نادرست, نادرست);
			idx = ce.مقدار;
			idx = c_fully_fold (idx, نادرست, پوچ);
			c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
						   "expected %<]%>");
			offsetof_ref = build_array_ref (loc, offsetof_ref, idx);
		      }
		  }
	      }
	    وگرنه
	      c_parser_error (parser, "expected identifier");
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    عبارت.مقدار = fold_offsetof (offsetof_ref);
	    set_c_عبارت_source_range (&عبارت, loc, end_loc);
	  }
	  بشکن;
	حالت RID_CHOOSE_عبارت:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    c_عبارت_t *e1_p, *e2_p, *e3_p;
	    درخت c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_args (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, درست,
					    &close_paren_loc))
	      {
		عبارت.set_error ();
		بشکن;
	      }

	    اگر (vec_safe_length (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		عبارت.set_error ();
		بشکن;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->مقدار;
	    mark_exp_read (e2_p->مقدار);
	    mark_exp_read (e3_p->مقدار);
	    اگر (درخت_CODE (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (درخت_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_expression_warning (c);
	    عبارت = integer_zerop (c) ? *e3_p : *e2_p;
	    set_c_عبارت_source_range (&عبارت, loc, close_paren_loc);
	    بشکن;
	  }
	حالت RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    t1 = c_parser_type_name (parser);
	    اگر (t1 == پوچ)
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
		عبارت.set_error ();
		بشکن;
	      }
	    t2 = c_parser_type_name (parser);
	    اگر (t2 == پوچ)
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    درخت e1, e2;
	    e1 = groktypename (t1, پوچ, پوچ);
	    e2 = groktypename (t2, پوچ, پوچ);
	    اگر (e1 == error_mark_گره || e2 == error_mark_گره)
	      {
		عبارت.set_error ();
		بشکن;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    عبارت.مقدار
	      = comptypes (e1, e2) ? integer_one_گره : integer_zero_گره;
	    set_c_عبارت_source_range (&عبارت, loc, close_paren_loc);
	  }
	  بشکن;
	حالت RID_BUILTIN_TGMATH:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_args (parser,
					    "__builtin_tgmath",
					    &cexpr_list, نادرست,
					    &close_paren_loc))
	      {
		عبارت.set_error ();
		بشکن;
	      }

	    اگر (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		عبارت.set_error ();
		بشکن;
	      }

	    unsigned صحیح i;
	    c_عبارت_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, درست, درست);
	    unsigned صحیح nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    اگر (nargs == 0)
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (vec_safe_length (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		عبارت.set_error ();
		بشکن;
	      }
	    unsigned صحیح رقم_functions = vec_safe_length (cexpr_list) - nargs;
	    اگر (رقم_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		عبارت.set_error ();
		بشکن;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    برای (unsigned صحیح j = 1; j < رقم_functions; j++)
	      {
		unsigned صحیح this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		اگر (this_nargs == 0)
		  {
		    عبارت.set_error ();
		    برو out;
		  }
		اگر (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    عبارت.set_error ();
		    برو out;
		  }
	      }

	    /* The functions all have the same number of arguments.
	       Determine whether arguments and return types vary in
	       ways permitted for <tgmath.h> functions.  */
	    /* The first entry in each of these vectors is for the
	       return type, subsequent entries for parameter
	       types.  */
	    auto_vec<شمارش tgmath_parm_kind> parm_kind (nargs + 1);
	    auto_vec<درخت> parm_first (nargs + 1);
	    auto_vec<منطقی> parm_complex (nargs + 1);
	    auto_vec<منطقی> parm_varies (nargs + 1);
	    درخت first_type = درخت_TYPE (درخت_TYPE ((*cexpr_list)[0].مقدار));
	    درخت first_ret = TYPE_MAIN_VARIANT (درخت_TYPE (first_type));
	    parm_first.quick_افزودن (first_ret);
	    parm_complex.quick_افزودن (درخت_CODE (first_ret) == COMPLEX_TYPE);
	    parm_varies.quick_افزودن (نادرست);
	    function_args_iterator iter;
	    درخت t;
	    unsigned صحیح argpos;
	    FOREACH_FUNCTION_ARGS (first_type, t, iter)
	      {
		اگر (t == void_type_گره)
		  بشکن;
		parm_first.quick_افزودن (TYPE_MAIN_VARIANT (t));
		parm_complex.quick_افزودن (درخت_CODE (t) == COMPLEX_TYPE);
		parm_varies.quick_افزودن (نادرست);
	      }
	    برای (unsigned صحیح j = 1; j < رقم_functions; j++)
	      {
		درخت type = درخت_TYPE (درخت_TYPE ((*cexpr_list)[j].مقدار));
		درخت ret = TYPE_MAIN_VARIANT (درخت_TYPE (type));
		اگر (ret != parm_first[0])
		  {
		    parm_varies[0] = درست;
		    اگر (!SCALAR_FLOAT_TYPE_P (parm_first[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_first[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			عبارت.set_error ();
			برو out;
		      }
		    اگر (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			عبارت.set_error ();
			برو out;
		      }
		  }
		اگر (درخت_CODE (ret) == COMPLEX_TYPE)
		  parm_complex[0] = درست;
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    اگر (t == void_type_گره)
		      بشکن;
		    t = TYPE_MAIN_VARIANT (t);
		    اگر (t != parm_first[argpos])
		      {
			parm_varies[argpos] = درست;
			اگر (!SCALAR_FLOAT_TYPE_P (parm_first[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_first[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    عبارت.set_error ();
			    برو out;
			  }
			اگر (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    عبارت.set_error ();
			    برو out;
			  }
		      }
		    اگر (درخت_CODE (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = درست;
		    argpos++;
		  }
	      }
	    شمارش tgmath_parm_kind max_variation = tgmath_fixed;
	    برای (unsigned صحیح j = 0; j <= nargs; j++)
	      {
		شمارش tgmath_parm_kind this_kind;
		اگر (parm_varies[j])
		  {
		    اگر (parm_complex[j])
		      max_variation = this_kind = tgmath_complex;
		    وگرنه
		      {
			this_kind = tgmath_real;
			اگر (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		وگرنه
		  this_kind = tgmath_fixed;
		parm_kind.quick_افزودن (this_kind);
	      }
	    اگر (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		عبارت.set_error ();
		بشکن;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    unsigned صحیح tgarg = 0;
	    برای (unsigned صحیح j = 1; j <= nargs; j++)
	      اگر (parm_kind[j] == max_variation)
		{
		  tgarg = j;
		  بشکن;
		}
	    اگر (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		عبارت.set_error ();
		بشکن;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<درخت> tg_type (رقم_functions);
	    برای (unsigned صحیح j = 0; j < رقم_functions; j++)
	      {
		درخت type = درخت_TYPE (درخت_TYPE ((*cexpr_list)[j].مقدار));
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    اگر (argpos == tgarg)
		      {
			tg_type.quick_افزودن (TYPE_MAIN_VARIANT (t));
			بشکن;
		      }
		    argpos++;
		  }
	      }

	    /* Verify that the corresponding types are different for
	       all the listed functions.  Also determine whether all
	       the types are complex, whether all the types are
	       standard or binary, and whether all the types are
	       decimal.  */
	    منطقی all_complex = درست;
	    منطقی all_دودویی = درست;
	    منطقی all_decimal = درست;
	    hash_set<درخت> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		اگر (درخت_CODE (t) == COMPLEX_TYPE)
		  all_decimal = نادرست;
		وگرنه
		  {
		    all_complex = نادرست;
		    اگر (DECIMAL_FLOAT_TYPE_P (t))
		      all_دودویی = نادرست;
		    وگرنه
		      all_decimal = نادرست;
		  }
		اگر (tg_types.add (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    عبارت.set_error ();
		    برو out;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    برای (unsigned صحیح j = 0; j < رقم_functions; j++)
	      {
		درخت exp_type = tg_type[j];
		درخت exp_real_type = exp_type;
		اگر (درخت_CODE (exp_type) == COMPLEX_TYPE)
		  exp_real_type = درخت_TYPE (exp_type);
		درخت type = درخت_TYPE (درخت_TYPE ((*cexpr_list)[j].مقدار));
		درخت ret = TYPE_MAIN_VARIANT (درخت_TYPE (type));
		اگر ((parm_kind[0] == tgmath_complex && ret != exp_type)
		    || (parm_kind[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    عبارت.set_error ();
		    برو out;
		  }
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    اگر (t == void_type_گره)
		      بشکن;
		    t = TYPE_MAIN_VARIANT (t);
		    اگر ((parm_kind[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_kind[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			عبارت.set_error ();
			برو out;
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
	    منطقی arg_complex = all_complex;
	    منطقی arg_دودویی = all_دودویی;
	    منطقی arg_int_decimal = all_decimal;
	    منطقی arg_int_floatnx = نادرست;
	    منطقی arg_int_decimalx = نادرست;
	    برای (unsigned صحیح j = 1; j <= nargs; j++)
	      {
		اگر (parm_kind[j] == tgmath_fixed)
		  ادامه;
		c_عبارت_t *ce = &(*cexpr_list)[رقم_functions + j - 1];
		درخت type = درخت_TYPE (ce->مقدار);
		اگر (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && درخت_CODE (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    عبارت.set_error ();
		    برو out;
		  }
		اگر (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = درست;
		    اگر (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			عبارت.set_error ();
			برو out;
		      }
		    وگرنه اگر (all_دودویی)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			عبارت.set_error ();
			برو out;
		      }
		    وگرنه اگر (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			عبارت.set_error ();
			برو out;
		      }
		    وگرنه اگر (arg_دودویی)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			عبارت.set_error ();
			برو out;
		      }
		  }
		وگرنه اگر (درخت_CODE (type) == COMPLEX_TYPE)
		  {
		    arg_complex = درست;
		    اگر (COMPLEX_FLOAT_TYPE_P (type))
		      arg_دودویی = درست;
		    اگر (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			عبارت.set_error ();
			برو out;
		      }
		    وگرنه اگر (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			عبارت.set_error ();
			برو out;
		      }
		  }
		وگرنه اگر (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_دودویی = درست;
		    اگر (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			عبارت.set_error ();
			برو out;
		      }
		    وگرنه اگر (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			عبارت.set_error ();
			برو out;
		      }
		  }
		درخت rtype = TYPE_MAIN_VARIANT (type);
		اگر (درخت_CODE (rtype) == COMPLEX_TYPE)
		  rtype = درخت_TYPE (rtype);
		اگر (SCALAR_FLOAT_TYPE_P (rtype))
		  برای (unsigned صحیح j = 0; j < رقم_FLOATNX_TYPES; j++)
		    اگر (rtype == FLOATNX_TYPE_گره (j))
		      {
			arg_int_floatnx = درست;
			بشکن;
		      }
		اگر (rtype == dfloat64x_type_گره)
		  arg_int_decimalx = درست;
	      }
	    درخت arg_real = NULL_درخت;
	    برای (unsigned صحیح j = 1; j <= nargs; j++)
	      {
		اگر (parm_kind[j] == tgmath_fixed)
		  ادامه;
		c_عبارت_t *ce = &(*cexpr_list)[رقم_functions + j - 1];
		درخت type = TYPE_MAIN_VARIANT (درخت_TYPE (ce->مقدار));
		اگر (درخت_CODE (type) == COMPLEX_TYPE)
		  type = درخت_TYPE (type);
		اگر (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_گره
			  : arg_int_floatnx
			  ? float32x_type_گره
			  : arg_int_decimal
			  ? dfloat64_type_گره
			  : double_type_گره);
		اگر (arg_real == NULL_درخت)
		  arg_real = type;
		وگرنه
		  arg_real = common_type (arg_real, type);
		اگر (arg_real == error_mark_گره)
		  {
		    عبارت.set_error ();
		    برو out;
		  }
	      }
	    درخت arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_عبارت_t *fn = پوچ;
	    برای (unsigned صحیح j = 0; j < رقم_functions; j++)
	      {
		اگر (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    بشکن;
		  }
	      }
	    اگر (fn == پوچ
		&& parm_kind[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_first[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		برای (unsigned صحیح j = 0; j < رقم_functions; j++)
		  {
		    اگر (arg_complex
			!= (درخت_CODE (tg_type[j]) == COMPLEX_TYPE))
		      ادامه;
		    درخت real_tg_type = (arg_complex
					 ? درخت_TYPE (tg_type[j])
					 : tg_type[j]);
		    اگر (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      ادامه;
		    scalar_float_mode arg_mode
		      = SCALAR_FLOAT_TYPE_MODE (arg_real);
		    scalar_float_mode tg_mode
		      = SCALAR_FLOAT_TYPE_MODE (real_tg_type);
		    ثابت real_format *arg_fmt = REAL_MODE_FORMAT (arg_mode);
		    ثابت real_format *tg_fmt = REAL_MODE_FORMAT (tg_mode);
		    اگر (arg_fmt->b == tg_fmt->b
			&& arg_fmt->p <= tg_fmt->p
			&& arg_fmt->emax <= tg_fmt->emax
			&& (arg_fmt->emin - arg_fmt->p
			    >= tg_fmt->emin - tg_fmt->p))
		      {
			fn = &(*cexpr_list)[j];
			بشکن;
		      }
		  }
	      }
	    اگر (fn == پوچ)
	      {
		error_at (loc, "no matching function for type-generic call");
		عبارت.set_error ();
		بشکن;
	      }

	    /* Construct a call to FN.  */
	    vec<درخت, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<درخت, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    برای (unsigned صحیح j = 0; j < nargs; j++)
	      {
		c_عبارت_t *ce = &(*cexpr_list)[رقم_functions + j];
		args->quick_افزودن (ce->مقدار);
		arg_loc.quick_افزودن (ce->get_location ());
		origtypes->quick_افزودن (ce->original_type);
	      }
	    عبارت.مقدار = c_build_function_call_vec (loc, arg_loc, fn->مقدار,
						    args, origtypes);
	    set_c_عبارت_source_range (&عبارت, loc, close_paren_loc);
	    بشکن;
	  }
	حالت RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    c_عبارت_t *e2_p;
	    درخت chain_مقدار;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_args (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, نادرست,
					    &close_paren_loc))
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		عبارت.set_error ();
		بشکن;
	      }

	    عبارت = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, درست, درست);
	    chain_مقدار = e2_p->مقدار;
	    mark_exp_read (chain_مقدار);

	    اگر (درخت_CODE (عبارت.مقدار) != CALL_عبارت)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    وگرنه اگر (درخت_CODE (درخت_TYPE (chain_مقدار)) != POINTER_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    وگرنه
	      CALL_عبارت_STATIC_CHAIN (عبارت.مقدار) = chain_مقدار;
	    set_c_عبارت_source_range (&عبارت, loc, close_paren_loc);
	    بشکن;
	  }
	حالت RID_BUILTIN_COMPLEX:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    c_عبارت_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_args (parser,
					    "__builtin_complex",
					    &cexpr_list, نادرست,
					    &close_paren_loc))
	      {
		عبارت.set_error ();
		بشکن;
	      }

	    اگر (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		عبارت.set_error ();
		بشکن;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_to_rvalue (loc, *e1_p, درست, درست);
	    اگر (درخت_CODE (e1_p->مقدار) == EXCESS_PRECISION_عبارت)
	      e1_p->مقدار = convert (درخت_TYPE (e1_p->مقدار),
				     درخت_OPERAND (e1_p->مقدار, 0));
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, درست, درست);
	    اگر (درخت_CODE (e2_p->مقدار) == EXCESS_PRECISION_عبارت)
	      e2_p->مقدار = convert (درخت_TYPE (e2_p->مقدار),
				     درخت_OPERAND (e2_p->مقدار, 0));
	    اگر (!SCALAR_FLOAT_TYPE_P (درخت_TYPE (e1_p->مقدار))
		|| DECIMAL_FLOAT_TYPE_P (درخت_TYPE (e1_p->مقدار))
		|| !SCALAR_FLOAT_TYPE_P (درخت_TYPE (e2_p->مقدار))
		|| DECIMAL_FLOAT_TYPE_P (درخت_TYPE (e2_p->مقدار)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (TYPE_MAIN_VARIANT (درخت_TYPE (e1_p->مقدار))
		!= TYPE_MAIN_VARIANT (درخت_TYPE (e2_p->مقدار)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		عبارت.set_error ();
		بشکن;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    عبارت.مقدار = build2_loc (loc, COMPLEX_عبارت,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (درخت_TYPE (e1_p->مقدار))),
				     e1_p->مقدار, e2_p->مقدار);
	    set_c_عبارت_source_range (&عبارت, loc, close_paren_loc);
	    بشکن;
	  }
	حالت RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    c_عبارت_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_args (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, نادرست,
					    &close_paren_loc))
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		عبارت.set_error ();
		بشکن;
	      }

	    e_p = &(*cexpr_list)[0];
	    درخت ref = e_p->مقدار;

	    اگر (درخت_CODE (درخت_TYPE (ref)) != ARRAY_TYPE
		 && درخت_CODE (درخت_TYPE (ref)) != POINTER_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		عبارت.set_error ();
		بشکن;
	      }

	    اگر (درخت_CODE (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		عبارت.set_error ();
		بشکن;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    اگر (درخت_CODE (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    اگر (has_counted_by_object (ref))
	      عبارت.مقدار = get_counted_by_ref (ref);
	    وگرنه
	      عبارت.مقدار = null_pointer_گره;

	    set_c_عبارت_source_range (&عبارت, loc, close_paren_loc);
	    بشکن;
	  }
	حالت RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    unsigned صحیح i;
	    c_عبارت_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_args (parser,
					    "__builtin_shuffle",
					    &cexpr_list, نادرست,
					    &close_paren_loc))
	      {
		عبارت.set_error ();
		بشکن;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, درست, درست);

	    اگر (vec_safe_length (cexpr_list) == 2)
	      عبارت.مقدار = c_build_vec_perm_عبارت (loc, (*cexpr_list)[0].مقدار,
						  NULL_درخت,
						  (*cexpr_list)[1].مقدار);

	    وگرنه اگر (vec_safe_length (cexpr_list) == 3)
	      عبارت.مقدار = c_build_vec_perm_عبارت (loc, (*cexpr_list)[0].مقدار,
						  (*cexpr_list)[1].مقدار,
						  (*cexpr_list)[2].مقدار);
	    وگرنه
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		عبارت.set_error ();
	      }
	    set_c_عبارت_source_range (&عبارت, loc, close_paren_loc);
	    بشکن;
	  }
	حالت RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    unsigned صحیح i;
	    c_عبارت_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_args (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, نادرست,
					    &close_paren_loc))
	      {
		عبارت.set_error ();
		بشکن;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, درست, درست);

	    اگر (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		عبارت.set_error ();
	      }
	    وگرنه
	      {
		auto_vec<درخت, 16> mask;
		برای (i = 2; i < cexpr_list->length (); ++i)
		  mask.safe_افزودن ((*cexpr_list)[i].مقدار);
		عبارت.مقدار = c_build_shufflevector (loc, (*cexpr_list)[0].مقدار,
						    (*cexpr_list)[1].مقدار,
						    mask);
	      }
	    set_c_عبارت_source_range (&عبارت, loc, close_paren_loc);
	    بشکن;
	  }
	حالت RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    e1 = c_parser_عبارت_no_commas (parser, پوچ);
	    mark_exp_read (e1.مقدار);
	    اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
		عبارت.set_error ();
		بشکن;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    اگر (t1 == پوچ)
	      عبارت.set_error ();
	    وگرنه
	      {
		درخت type_عبارت = NULL_درخت;
		عبارت.مقدار = c_build_vec_convert (start_loc, e1.مقدار, loc,
						  groktypename (t1, &type_عبارت,
								پوچ));
		set_c_عبارت_source_range (&عبارت, start_loc, end_loc);
	      }
	  }
	  بشکن;
	حالت RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    e1 = c_parser_عبارت_no_commas (parser, پوچ);
	    mark_exp_read (e1.مقدار);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    parens.skip_until_found_close (parser);
	    عبارت = parser_build_unary_op (loc, PAREN_عبارت, e1);
	    set_c_عبارت_source_range (&عبارت, start_loc, end_loc);
	  }
	  بشکن;
	حالت RID_BUILTIN_STDC:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    c_عبارت_t *arg_p;
	    location_t close_paren_loc;
	    شمارش c_builtin_stdc {
	      C_BUILTIN_STDC_BIT_CEIL,
	      C_BUILTIN_STDC_BIT_FLOOR,
	      C_BUILTIN_STDC_BIT_WIDTH,
	      C_BUILTIN_STDC_شمار_ONES,
	      C_BUILTIN_STDC_شمار_ZEROS,
	      C_BUILTIN_STDC_FIRST_LEADING_ONE,
	      C_BUILTIN_STDC_FIRST_LEADING_ZERO,
	      C_BUILTIN_STDC_FIRST_TRAILING_ONE,
	      C_BUILTIN_STDC_FIRST_TRAILING_ZERO,
	      C_BUILTIN_STDC_HAS_SINGLE_BIT,
	      C_BUILTIN_STDC_LEADING_ONES,
	      C_BUILTIN_STDC_LEADING_ZEROS,
	      C_BUILTIN_STDC_ROTATE_چپ,
	      C_BUILTIN_STDC_ROTATE_راست,
	      C_BUILTIN_STDC_TRAILING_ONES,
	      C_BUILTIN_STDC_TRAILING_ZEROS,
	      C_BUILTIN_STDC_MAX
	    } stdc_rid = C_BUILTIN_STDC_MAX;
	    ثابت نویسه *name
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
	    unsigned رقم_args = 1;
	    انتخاب (name[اندازه ("__builtin_stdc_") - 1])
	      {
	      حالت 'b':
		انتخاب (name[اندازه ("__builtin_stdc_bit_") - 1])
		  {
		  حالت 'c':
		    stdc_rid = C_BUILTIN_STDC_BIT_CEIL;
		    بشکن;
		  حالت 'f':
		    stdc_rid = C_BUILTIN_STDC_BIT_FLOOR;
		    بشکن;
		  پیشفرض:
		    stdc_rid = C_BUILTIN_STDC_BIT_WIDTH;
		    بشکن;
		  }
		بشکن;
	      حالت 'c':
		اگر (name[اندازه ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_شمار_ONES;
		وگرنه
		  stdc_rid = C_BUILTIN_STDC_شمار_ZEROS;
		بشکن;
	      حالت 'f':
		انتخاب (name[اندازه ("__builtin_stdc_first_trailing_") - 1])
		  {
		  حالت 'n':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ONE;
		    بشکن;
		  حالت 'e':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ZERO;
		    بشکن;
		  حالت 'o':
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ONE;
		    بشکن;
		  پیشفرض:
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ZERO;
		    بشکن;
		  }
		بشکن;
	      حالت 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_BIT;
		بشکن;
	      حالت 'l':
		اگر (name[اندازه ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		وگرنه
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		بشکن;
	      حالت 'r':
		اگر (name[اندازه ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_چپ;
		وگرنه
		  stdc_rid = C_BUILTIN_STDC_ROTATE_راست;
		رقم_args = 2;
		بشکن;
	      حالت 't':
		اگر (name[اندازه ("__builtin_stdc_trailing_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ONES;
		وگرنه
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ZEROS;
		بشکن;
	      }
	    gcc_checking_assert (stdc_rid != C_BUILTIN_STDC_MAX);

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_args (parser, name,
					    &cexpr_list, نادرست,
					    &close_paren_loc))
	      {
		عبارت.set_error ();
		بشکن;
	      }

	    اگر (vec_safe_length (cexpr_list) != رقم_args)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		عبارت.set_error ();
		بشکن;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, درست, درست);
	    اگر (!INTEGRAL_TYPE_P (درخت_TYPE (arg_p->مقدار)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (درخت_CODE (درخت_TYPE (arg_p->مقدار)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (درخت_CODE (درخت_TYPE (arg_p->مقدار)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (!TYPE_UNSIGNED (درخت_TYPE (arg_p->مقدار)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (TYPE_MAIN_VARIANT (درخت_TYPE (arg_p->مقدار))
		== char_type_گره)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		عبارت.set_error ();
		بشکن;
	      }
	    درخت arg = arg_p->مقدار;
	    درخت type = TYPE_MAIN_VARIANT (درخت_TYPE (arg));
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
	    صحیح prec = TYPE_PRECISION (type);
	    اگر (رقم_args == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_to_rvalue (loc, *arg_p, درست, درست);
		اگر (!INTEGRAL_TYPE_P (درخت_TYPE (arg_p->مقدار)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    عبارت.set_error ();
		    بشکن;
		  }
		اگر (درخت_CODE (درخت_TYPE (arg_p->مقدار)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    عبارت.set_error ();
		    بشکن;
		  }
		درخت arg1 = save_عبارت (arg);
		درخت arg2 = save_عبارت (arg_p->مقدار);
		درخت_code code;
		اگر (stdc_rid == C_BUILTIN_STDC_ROTATE_چپ)
		  code = LROTATE_عبارت;
		وگرنه
		  code = RROTATE_عبارت;

		اگر (درخت_CODE (arg2) == INTEGER_CST
		    && درخت_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_شمار_negative,
			      "rotate count is negative");

		درخت instrument_عبارت = NULL_درخت;
		اگر (sanitize_flags_p (SANITIZE_SHIFT))
		  instrument_عبارت = ubsan_instrument_shift (loc, code,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		اگر (TYPE_PRECISION (درخت_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_گره))
		  arg2 = fold_convert (unsigned_type_گره, arg2);

		اگر (TYPE_UNSIGNED (درخت_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_عبارت, درخت_TYPE (arg2),
				     arg2, build_int_cst (درخت_TYPE (arg2),
							  prec));
		وگرنه
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    درخت utype = c_common_unsigned_type (درخت_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_عبارت, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		اگر (type_has_mode_precision_p (درخت_TYPE (arg1))
		    || (درخت_CODE (درخت_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_MODE_SIZE))
		  عبارت.مقدار = build2_loc (loc, code, درخت_TYPE (arg1), arg1,
					   arg2);
		وگرنه
		  {
		    arg2 = save_عبارت (arg2);
		    درخت t1 = build2_loc (loc, (code == LROTATE_عبارت
						? LSHIFT_عبارت : RSHIFT_عبارت),
					  درخت_TYPE (arg1), arg1, arg2);
		    درخت t2 = build2_loc (loc, MINUS_عبارت,
					  درخت_TYPE (arg2),
					  build_int_cst (درخت_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (code == LROTATE_عبارت
					   ? RSHIFT_عبارت : LSHIFT_عبارت),
				     درخت_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_شمار_overflow);
		    درخت t3 = build2_loc (loc, BIT_IOR_عبارت,
					  درخت_TYPE (arg1), t1, t2);
		    درخت t4 = build2_loc (loc, NE_عبارت, boolean_type_گره,
					  arg2,
					  build_zero_cst (درخت_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_عبارت, boolean_type_گره,
				     arg1, t4);
		    عبارت.مقدار = build3_loc (loc, COND_عبارت,
					     درخت_TYPE (arg1), t4, t3, arg1);
		  }
		اگر (instrument_عبارت)
		  عبارت.مقدار = build2_loc (loc, COMPOUND_عبارت,
					   درخت_TYPE (عبارت.مقدار),
					   instrument_عبارت, عبارت.مقدار);
		set_c_عبارت_source_range (&عبارت, loc, close_paren_loc);
		بشکن;
	      }
	    درخت barg1 = arg;
	    انتخاب (stdc_rid)
	      {
	      حالت C_BUILTIN_STDC_BIT_CEIL:
		arg = save_عبارت (arg);
		barg1 = build2_loc (loc, PLUS_عبارت, type, arg,
				    build_int_cst (type, -1));
		بشکن;
	      حالت C_BUILTIN_STDC_BIT_FLOOR:
		barg1 = arg = save_عبارت (arg);
		بشکن;
	      حالت C_BUILTIN_STDC_شمار_ZEROS:
	      حالت C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      حالت C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      حالت C_BUILTIN_STDC_LEADING_ONES:
	      حالت C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, BIT_NOT_عبارت, type, arg);
		بشکن;
	      پیشفرض:
		بشکن;
	      }
	    درخت barg2 = NULL_درخت;
	    انتخاب (stdc_rid)
	      {
	      حالت C_BUILTIN_STDC_BIT_WIDTH:
	      حالت C_BUILTIN_STDC_LEADING_ONES:
	      حالت C_BUILTIN_STDC_LEADING_ZEROS:
	      حالت C_BUILTIN_STDC_TRAILING_ONES:
	      حالت C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_گره, prec);
		بشکن;
	      حالت C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      حالت C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      حالت C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      حالت C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		barg2 = integer_minus_one_گره;
		بشکن;
	      پیشفرض:
		بشکن;
	      }
	    درخت fndecl = NULL_درخت;
	    انتخاب (stdc_rid)
	      {
	      حالت C_BUILTIN_STDC_BIT_CEIL:
	      حالت C_BUILTIN_STDC_BIT_FLOOR:
	      حالت C_BUILTIN_STDC_BIT_WIDTH:
	      حالت C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      حالت C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      حالت C_BUILTIN_STDC_LEADING_ONES:
	      حالت C_BUILTIN_STDC_LEADING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CLZG);
		بشکن;
	      حالت C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      حالت C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      حالت C_BUILTIN_STDC_TRAILING_ONES:
	      حالت C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CTZG);
		بشکن;
	      حالت C_BUILTIN_STDC_شمار_ONES:
	      حالت C_BUILTIN_STDC_شمار_ZEROS:
	      حالت C_BUILTIN_STDC_HAS_SINGLE_BIT:
		fndecl = builtin_decl_explicit (BUILT_IN_POPCOUNTG);
		بشکن;
	      پیشفرض:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    صحیح nargs = barg2 != NULL_درخت ? 2 : 1;
	    vec<درخت, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<درخت, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    args->quick_افزودن (barg1);
	    arg_loc.quick_افزودن (arg_p->get_location ());
	    origtypes->quick_افزودن (arg_p->original_type);
	    اگر (nargs == 2)
	      {
		args->quick_افزودن (barg2);
		arg_loc.quick_افزودن (loc);
		origtypes->quick_افزودن (integer_type_گره);
	      }
	    عبارت.مقدار = c_build_function_call_vec (loc, arg_loc, fndecl,
						    args, origtypes);
	    set_c_عبارت_source_range (&عبارت, loc, close_paren_loc);
	    اگر (عبارت.مقدار == error_mark_گره)
	      بشکن;
	    انتخاب (stdc_rid)
	      {
	      حالت C_BUILTIN_STDC_BIT_CEIL:
	      حالت C_BUILTIN_STDC_BIT_FLOOR:
		--prec;
		/* FALLTHRU */
	      حالت C_BUILTIN_STDC_BIT_WIDTH:
		عبارت.مقدار = build2_loc (loc, MINUS_عبارت, integer_type_گره,
					 build_int_cst (integer_type_گره,
							prec), عبارت.مقدار);
		بشکن;
	      حالت C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      حالت C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      حالت C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      حالت C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		عبارت.مقدار = build2_loc (loc, PLUS_عبارت, integer_type_گره,
					 عبارت.مقدار, integer_one_گره);
		بشکن;
	      حالت C_BUILTIN_STDC_HAS_SINGLE_BIT:
		عبارت.مقدار = build2_loc (loc, EQ_عبارت, boolean_type_گره,
					 عبارت.مقدار, integer_one_گره);
		بشکن;
	      پیشفرض:
		بشکن;
	      }

	    اگر (stdc_rid != C_BUILTIN_STDC_BIT_CEIL
		&& stdc_rid != C_BUILTIN_STDC_BIT_FLOOR)
	      {
		اگر (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_BIT)
		  عبارت.مقدار = fold_convert_loc (loc, unsigned_type_گره,
						 عبارت.مقدار);
		بشکن;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    اگر (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_BIT_CEIL && integer_onep (arg)))
	      عبارت.مقدار = build_int_cst (type, 0);
	    وگرنه
	      عبارت.مقدار
		= build2_loc (loc, LSHIFT_عبارت, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_BIT_CEIL
					      ? 2 : 1)), عبارت.مقدار);
	    اگر (stdc_rid == C_BUILTIN_STDC_BIT_CEIL)
	      عبارت.مقدار = build3_loc (loc, COND_عبارت, type,
				       build2_loc (loc, LE_عبارت,
						   boolean_type_گره, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       عبارت.مقدار);
	    وگرنه
	      عبارت.مقدار = build3_loc (loc, COND_عبارت, type,
				       build2_loc (loc, EQ_عبارت,
						   boolean_type_گره, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       عبارت.مقدار);
	    بشکن;
	  }
	حالت RID_BUILTIN_BSWAPG:
	حالت RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    internal_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    ثابت نویسه *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_args (parser, name, &cexpr_list, نادرست,
					    &close_paren_loc))
	      {
		عبارت.set_error ();
		بشکن;
	      }

	    اگر (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		عبارت.set_error ();
		بشکن;
	      }

	    c_عبارت_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, درست, درست);
	    درخت arg = arg_p->مقدار;
	    اگر (error_operand_p (arg))
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    درخت type = TYPE_MAIN_VARIANT (درخت_TYPE (arg));
	    اگر (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (درخت_CODE (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (درخت_CODE (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		عبارت.set_error ();
		بشکن;
	      }
	    arg = c_fully_fold (arg, نادرست, پوچ);
	    عبارت.مقدار = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    set_c_عبارت_source_range (&عبارت, loc, close_paren_loc);
	    بشکن;
	  }
	حالت RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    درخت sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    عبارت.مقدار = objc_build_selector_عبارت (loc, sel);
	    set_c_عبارت_source_range (&عبارت, loc, close_loc);
	  }
	  بشکن;
	حالت RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    اگر (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
		عبارت.set_error ();
		بشکن;
	      }
	    درخت id = c_parser_peek_token (parser)->مقدار;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    عبارت.مقدار = objc_build_protocol_عبارت (id);
	    set_c_عبارت_source_range (&عبارت, loc, close_loc);
	  }
	  بشکن;
	حالت RID_AT_ENCODE:
	  {
	    /* Extension to support C-structures in the archiver.  */
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		عبارت.set_error ();
		بشکن;
	      }
	    t1 = c_parser_type_name (parser);
	    اگر (t1 == پوچ)
	      {
		عبارت.set_error ();
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
		بشکن;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    درخت type = groktypename (t1, پوچ, پوچ);
	    عبارت.مقدار = objc_build_encode_عبارت (type);
	    set_c_عبارت_source_range (&عبارت, loc, close_loc);
	  }
	  بشکن;
	حالت RID_GENERIC:
	  عبارت = c_parser_generic_selection (parser);
	  بشکن;
	حالت RID_OMP_ALL_MEMORY:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  عبارت.set_error ();
	  بشکن;
	/* C23 'nullptr' literal.  */
	حالت RID_NULLPTR:
	  c_parser_consume_token (parser);
	  عبارت.مقدار = nullptr_گره;
	  set_c_عبارت_source_range (&عبارت, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  بشکن;
	حالت RID_TRUE:
	  c_parser_consume_token (parser);
	  عبارت.مقدار = boolean_true_گره;
	  set_c_عبارت_source_range (&عبارت, tok_range);
	  بشکن;
	حالت RID_FALSE:
	  c_parser_consume_token (parser);
	  عبارت.مقدار = boolean_false_گره;
	  set_c_عبارت_source_range (&عبارت, tok_range);
	  بشکن;
	پیشفرض:
	  c_parser_error (parser, "expected expression");
	  عبارت.set_error ();
	  بشکن;
	}
      بشکن;
    حالت CPP_OPEN_SQUARE:
      اگر (c_dialect_objc ())
	{
	  درخت receiver, args;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  args = c_parser_objc_message_args (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  عبارت.مقدار = objc_build_message_عبارت (receiver, args);
	  set_c_عبارت_source_range (&عبارت, loc, close_loc);
	  بشکن;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    پیشفرض:
      c_parser_error (parser, "expected expression");
      عبارت.set_error ();
      بشکن;
    }
 out:
  بازگشت c_parser_postfix_expression_after_primary
    (parser, عبارت_LOC_OR_LOC (عبارت.مقدار, loc), عبارت);
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

ایستا ساختار c_عبارت
c_parser_postfix_expression_after_paren_type (c_parser *parser,
					      ساختار c_declspecs *scspecs,
					      ساختار c_type_name *type_name,
					      location_t type_loc)
{
  درخت type;
  ساختار c_عبارت init;
  منطقی non_const;
  ساختار c_عبارت عبارت;
  location_t start_loc;
  درخت type_عبارت = NULL_درخت;
  منطقی type_عبارت_const = درست;
  منطقی constexpr_p = scspecs ? scspecs->constexpr_p : نادرست;
  unsigned صحیح underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (سطر_table, type_loc);
  start_loc = c_parser_peek_token (parser)->location;
  اگر (constexpr_p)
    {
      underspec_state = start_underspecified_init (start_loc, NULL_درخت);
      /* A constexpr compound literal is subject to the constraints on
	 underspecified declarations, which may not declare tags or
	 members or structures or unions; it is undefined behavior to
	 declare the members of an enumeration.  Where the structure,
	 union or enumeration type is declared within the compound
	 literal initializer, this is diagnosed elsewhere as a result
	 of the above call to start_underspecified_init.  Diagnose
	 here the case of declaring such a type in the type specifiers
	 of the compound literal.  */
      انتخاب (type_name->specs->typespec_kind)
	{
	حالت ctsk_tagfirstref:
	حالت ctsk_tagfirstref_attrs:
	  error_at (type_loc, "%qT declared in %<constexpr%> compound literal",
		    type_name->specs->type);
	  بشکن;

	حالت ctsk_tagdef:
	  error_at (type_loc, "%qT defined in %<constexpr%> compound literal",
		    type_name->specs->type);
	  بشکن;

	پیشفرض:
	  بشکن;
	}
    }
  start_init (NULL_درخت, پوچ,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_عبارت, &type_عبارت_const);
  منطقی varsize_p = نادرست;
  اگر (type != error_mark_گره && C_TYPE_VARIABLE_SIZE (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = درست;
    }
  وگرنه اگر (درخت_CODE (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_گره;
    }
  اگر (constexpr_p && type != error_mark_گره)
    {
      درخت type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      اگر (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      وگرنه اگر (RECORD_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, نادرست, پوچ, varsize_p);
  اگر (constexpr_p)
    finish_underspecified_init (NULL_درخت, underspec_state);
  finish_init ();
  maybe_warn_string_init (type_loc, type, init);

  اگر (type != error_mark_گره
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_گره;
    }

  اگر (!pedwarn_c90 (start_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (start_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.مقدار && درخت_CODE (init.مقدار) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.مقدار)
	       : init.original_code == C_MAYBE_CONST_عبارت);
  non_const |= !type_عبارت_const;
  unsigned صحیح alignas_align = 0;
  اگر (type != error_mark_گره
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      اگر (alignas_align < min_align_of_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  عبارت.مقدار = build_compound_literal (start_loc, type, init.مقدار, non_const,
				       alignas_align, scspecs);
  set_c_عبارت_source_range (&عبارت, init.src_range);
  عبارت.m_decimal = 0;
  عبارت.original_code = ERROR_MARK;
  عبارت.original_type = پوچ;
  اگر (type != error_mark_گره
      && عبارت.مقدار != error_mark_گره
      && type_عبارت)
    {
      اگر (درخت_CODE (عبارت.مقدار) == C_MAYBE_CONST_عبارت)
	{
	  gcc_assert (C_MAYBE_CONST_عبارت_PRE (عبارت.مقدار) == NULL_درخت);
	  C_MAYBE_CONST_عبارت_PRE (عبارت.مقدار) = type_عبارت;
	}
      وگرنه
	{
	  gcc_assert (!non_const);
	  عبارت.مقدار = build2 (C_MAYBE_CONST_عبارت, type,
			       type_عبارت, عبارت.مقدار);
	}
    }
  بازگشت c_parser_postfix_expression_after_primary (parser, start_loc, عبارت);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

ایستا منطقی
sizeof_ptr_memacc_comptypes (درخت type1, درخت type2)
{
  بازگشت comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

ایستا تهی
warn_for_abs (location_t loc, درخت fndecl, درخت arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  اگر (c_inhibit_evaluation_warnings)
    بازگشت;

  درخت atype = درخت_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  اگر (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && درخت_CODE (atype) != COMPLEX_TYPE)
    بازگشت;

  شمارش built_in_function fcode = DECL_FUNCTION_CODE (fndecl);

  انتخاب (fcode)
    {
    حالت BUILT_IN_ABS:
    حالت BUILT_IN_LABS:
    حالت BUILT_IN_LLABS:
    حالت BUILT_IN_IMAXABS:
      اگر (!INTEGRAL_TYPE_P (atype))
	{
	  اگر (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  وگرنه اگر (درخت_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  وگرنه
	    gcc_unreachable ();
	  بازگشت;
	}
      اگر (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_مقدار,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      بشکن;

    CASE_FLT_FN (BUILT_IN_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FABS):
      اگر (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_MODE_P (TYPE_MODE (atype)))
	{
	  اگر (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  وگرنه اگر (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  وگرنه اگر (درخت_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  وگرنه
	    gcc_unreachable ();
	  بازگشت;
	}
      بشکن;

    CASE_FLT_FN (BUILT_IN_CABS):
      اگر (درخت_CODE (atype) != COMPLEX_TYPE)
	{
	  اگر (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  وگرنه اگر (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  وگرنه
	    gcc_unreachable ();

	  بازگشت;
	}
      بشکن;

    حالت BUILT_IN_FABSD32:
    حالت BUILT_IN_FABSD64:
    حالت BUILT_IN_FABSD128:
    حالت BUILT_IN_FABSD64X:
      اگر (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  اگر (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  وگرنه اگر (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  وگرنه اگر (درخت_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using decimal floating-point absolute value "
			"function %qD when argument is of complex type %qT",
			fndecl, atype);
	  وگرنه
	    gcc_unreachable ();
	  بازگشت;
	}
      بشکن;

    پیشفرض:
      بازگشت;
    }

  اگر (!TYPE_ARG_TYPES (درخت_TYPE (fndecl)))
    بازگشت;

  درخت ftype = درخت_مقدار (TYPE_ARG_TYPES (درخت_TYPE (fndecl)));
  اگر (درخت_CODE (atype) == COMPLEX_TYPE)
    {
      gcc_assert (درخت_CODE (ftype) == COMPLEX_TYPE);
      atype = درخت_TYPE (atype);
      ftype = درخت_TYPE (ftype);
    }

  اگر (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_مقدار,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

ایستا ساختار c_عبارت
c_parser_postfix_expression_after_primary (c_parser *parser,
					   location_t عبارت_loc,
					   ساختار c_عبارت عبارت)
{
  ساختار c_عبارت orig_عبارت;
  درخت ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  درخت sizeof_arg[6];
  unsigned صحیح literal_zero_mask;
  unsigned صحیح i;
  vec<درخت, va_gc> *exprlist;
  vec<درخت, va_gc> *origtypes = پوچ;
  vec<location_t> arg_loc = vNULL;
  location_t start;
  location_t finish;

  وقتی (درست)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_OPEN_SQUARE:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_درخت;
	  اگر (!c_omp_array_section_p
	      || c_parser_next_token_is_not (parser, CPP_COLON))
	    idx = c_parser_expression (parser).مقدار;

	  اگر (c_omp_array_section_p
	      && c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      اگر (c_parser_next_token_is_not (parser, CPP_CLOSE_SQUARE))
		len = c_parser_expression (parser).مقدار;

	      عبارت.مقدار = build_omp_array_section (op_loc, عبارت.مقدار, idx,
						    len);
	    }
	  وگرنه
	    عبارت.مقدار = build_array_ref (op_loc, عبارت.مقدار, idx);

	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");

	  start = عبارت.get_start ();
	  finish = parser->tokens_buf[0].location;
	  set_c_عبارت_source_range (&عبارت, start, finish);
	  عبارت.original_code = ERROR_MARK;
	  عبارت.original_type = پوچ;
	  عبارت.m_decimal = 0;
	  بشکن;
	حالت CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    برای (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_درخت;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_mask = 0;
	    اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = پوچ;
	    وگرنه اگر (درخت_CODE (عبارت.مقدار) == FUNCTION_DECL
		     && fndecl_built_in_p (عبارت.مقدار, BUILT_IN_CLASSIFY_TYPE)
		     && c_parser_next_tokens_start_typename (parser,
							     cla_prefer_id))
	      {
		/* __builtin_classify_type (type)  */
		c_inhibit_evaluation_warnings++;
		in_alignof++;
		ساختار c_type_name *type = c_parser_type_name (parser);
		c_inhibit_evaluation_warnings--;
		in_alignof--;
		ساختار c_typespec ret;
		ret.عبارت = NULL_درخت;
		ret.spec = error_mark_گره;
		ret.عبارت_const_operands = نادرست;
		اگر (type != پوچ)
		  ret.spec = groktypename (type, &ret.عبارت,
					   &ret.عبارت_const_operands);
		parens.skip_until_found_close (parser);
		عبارت.مقدار = build_int_cst (integer_type_گره,
					    type_to_class (ret.spec));
		بشکن;
	      }
	    وگرنه
	      exprlist = c_parser_عبارت_list (parser, درست, نادرست, &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_mask);
	    parens.skip_until_found_close (parser);
	  }
	  orig_عبارت = عبارت;
	  mark_exp_read (عبارت.مقدار);
	  اگر (warn_sizeof_pointer_memaccess)
	    sizeof_pointer_memaccess_warning (sizeof_arg_loc,
					      عبارت.مقدار, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  اگر (درخت_CODE (عبارت.مقدار) == FUNCTION_DECL)
	    {
	      اگر (fndecl_built_in_p (عبارت.مقدار, BUILT_IN_MEMSET)
		  && vec_safe_length (exprlist) == 3)
		{
		  درخت arg0 = (*exprlist)[0];
		  درخت arg2 = (*exprlist)[2];
		  warn_for_memset (عبارت_loc, arg0, arg2, literal_zero_mask);
		}
	      اگر (warn_absolute_مقدار
		  && fndecl_built_in_p (عبارت.مقدار, BUILT_IN_NORMAL)
		  && vec_safe_length (exprlist) == 1)
		warn_for_abs (عبارت_loc, عبارت.مقدار, (*exprlist)[0]);
	      اگر (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->in_intervening_code
		  && omp_runtime_api_call (عبارت.مقدار))
		{
		  error_at (عبارت_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->fail = درست;
		}
	      اگر (warn_calloc_transposed_args)
		اگر (درخت attr = lookup_attribute ("alloc_size",
						  TYPE_ATTRIBUTES
						    (درخت_TYPE (عبارت.مقدار))))
		  اگر (درخت_مقدار (attr) && درخت_CHAIN (درخت_مقدار (attr)))
		    warn_for_calloc (sizeof_arg_loc, عبارت.مقدار, exprlist,
				     sizeof_arg, attr);
	    }

	  start = عبارت.get_start ();
	  finish = parser->tokens_buf[0].get_finish ();
	  عبارت.مقدار
	    = c_build_function_call_vec (عبارت_loc, arg_loc, عبارت.مقدار,
					 exprlist, origtypes);
	  set_c_عبارت_source_range (&عبارت, start, finish);
	  عبارت.m_decimal = 0;

	  عبارت.original_code = ERROR_MARK;
	  اگر (درخت_CODE (عبارت.مقدار) == INTEGER_CST
	      && درخت_CODE (orig_عبارت.مقدار) == FUNCTION_DECL
	      && fndecl_built_in_p (orig_عبارت.مقدار, BUILT_IN_CONSTANT_P))
	    عبارت.original_code = C_MAYBE_CONST_عبارت;
	  عبارت.original_type = پوچ;
	  اگر (exprlist)
	    {
	      release_درخت_vector (exprlist);
	      release_درخت_vector (origtypes);
	    }
	  arg_loc.release ();
	  بشکن;
	حالت CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  عبارت = default_function_array_conversion (عبارت_loc, عبارت);
	  اگر (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->مقدار;
	      comp_loc = comp_tok->location;
	    }
	  وگرنه
	    {
	      c_parser_error (parser, "expected identifier");
	      عبارت.set_error ();
	      عبارت.original_code = ERROR_MARK;
              عبارت.original_type = پوچ;
	      بازگشت عبارت;
	    }
	  start = عبارت.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  عبارت.مقدار = build_component_ref (op_loc, عبارت.مقدار, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  set_c_عبارت_source_range (&عبارت, start, finish);
	  عبارت.original_code = ERROR_MARK;
	  اگر (درخت_CODE (عبارت.مقدار) != COMPONENT_REF)
	    عبارت.original_type = پوچ;
	  وگرنه
	    {
	      /* Remember the original type of a bitfield.  */
	      درخت field = درخت_OPERAND (عبارت.مقدار, 1);
	      اگر (درخت_CODE (field) != FIELD_DECL)
		عبارت.original_type = پوچ;
	      وگرنه
		عبارت.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  عبارت.m_decimal = 0;
	  بشکن;
	حالت CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, درست, نادرست);
	  اگر (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->مقدار;
	      comp_loc = comp_tok->location;
	    }
	  وگرنه
	    {
	      c_parser_error (parser, "expected identifier");
	      عبارت.set_error ();
	      عبارت.original_code = ERROR_MARK;
	      عبارت.original_type = پوچ;
	      بازگشت عبارت;
	    }
	  start = عبارت.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  عبارت.مقدار = build_component_ref (op_loc,
					    build_indirect_ref (op_loc,
								عبارت.مقدار,
								RO_ARROW),
					    ident, comp_loc,
					    عبارت.get_location ());
	  set_c_عبارت_source_range (&عبارت, start, finish);
	  عبارت.original_code = ERROR_MARK;
	  اگر (درخت_CODE (عبارت.مقدار) != COMPONENT_REF)
	    عبارت.original_type = پوچ;
	  وگرنه
	    {
	      /* Remember the original type of a bitfield.  */
	      درخت field = درخت_OPERAND (عبارت.مقدار, 1);
	      اگر (درخت_CODE (field) != FIELD_DECL)
		عبارت.original_type = پوچ;
	      وگرنه
		عبارت.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  عبارت.m_decimal = 0;
	  بشکن;
	حالت CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  start = عبارت.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (عبارت.مقدار);
	  عبارت = default_function_array_conversion (عبارت_loc, عبارت);
	  عبارت.مقدار = build_unary_op (op_loc, POSTINCREMENT_عبارت,
				       عبارت.مقدار, نادرست);
	  set_c_عبارت_source_range (&عبارت, start, finish);
	  عبارت.original_code = ERROR_MARK;
	  عبارت.original_type = پوچ;
	  بشکن;
	حالت CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  start = عبارت.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (عبارت.مقدار);
	  عبارت = default_function_array_conversion (عبارت_loc, عبارت);
	  عبارت.مقدار = build_unary_op (op_loc, POSTDECREMENT_عبارت,
				       عبارت.مقدار, نادرست);
	  set_c_عبارت_source_range (&عبارت, start, finish);
	  عبارت.original_code = ERROR_MARK;
	  عبارت.original_type = پوچ;
	  بشکن;
	پیشفرض:
	  بازگشت عبارت;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

ایستا ساختار c_عبارت
c_parser_expression (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  ساختار c_عبارت عبارت;
  عبارت = c_parser_عبارت_no_commas (parser, پوچ);
  اگر (c_parser_next_token_is (parser, CPP_COMMA))
    عبارت = convert_lvalue_to_rvalue (tloc, عبارت, درست, نادرست);
  وقتی (c_parser_next_token_is (parser, CPP_COMMA))
    {
      ساختار c_عبارت next;
      درخت lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t عبارت_loc;
      c_parser_consume_token (parser);
      عبارت_loc = c_parser_peek_token (parser)->location;
      lhsval = عبارت.مقدار;
      وقتی (درخت_CODE (lhsval) == COMPOUND_عبارت
	     || درخت_CODE (lhsval) == NOP_عبارت)
	{
	  اگر (درخت_CODE (lhsval) == COMPOUND_عبارت)
	    lhsval = درخت_OPERAND (lhsval, 1);
	  وگرنه
	    lhsval = درخت_OPERAND (lhsval, 0);
	}
      اگر (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      اگر (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  درخت val = embed->مقدار;
	  unsigned last = RAW_DATA_LENGTH (val) - 1;
	  next.مقدار = build_int_cst (درخت_TYPE (val),
				      RAW_DATA_UCHAR_ELT (val, last));
	  next.original_type = integer_type_گره;
	  c_parser_consume_token (parser);
	}
      وگرنه
	{
	  next = c_parser_عبارت_no_commas (parser, پوچ);
	  next = convert_lvalue_to_rvalue (عبارت_loc, next, درست, نادرست);
	}
      عبارت.مقدار = build_compound_عبارت (loc, عبارت.مقدار, next.مقدار);
      عبارت.original_code = COMPOUND_عبارت;
      عبارت.original_type = next.original_type;
      عبارت.m_decimal = 0;
    }
  بازگشت عبارت;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

ایستا ساختار c_عبارت
c_parser_expression_conv (c_parser *parser)
{
  ساختار c_عبارت عبارت;
  location_t loc = c_parser_peek_token (parser)->location;
  عبارت = c_parser_expression (parser);
  عبارت = convert_lvalue_to_rvalue (loc, عبارت, درست, نادرست);
  بازگشت عبارت;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

ایستا درونخطی تهی
c_parser_check_literal_zero (c_parser *parser, unsigned *literal_zero_mask,
			     unsigned صحیح idx)
{
  اگر (idx >= HOST_BITS_PER_INT)
    بازگشت;

  c_token *tok = c_parser_peek_token (parser);
  انتخاب (tok->type)
    {
    حالت CPP_عدد:
    حالت CPP_CHAR:
    حالت CPP_WCHAR:
    حالت CPP_CHAR16:
    حالت CPP_CHAR32:
    حالت CPP_UTF8CHAR:
      /* If a parameter is literal zero alone, remember it
	 for -Wmemset-transposed-args warning.  */
      اگر (integer_zerop (tok->مقدار)
	  && !درخت_OVERFLOW (tok->مقدار)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_mask |= 1U << idx;
    پیشفرض:
      بشکن;
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

ایستا vec<درخت, va_gc> *
c_parser_عبارت_list (c_parser *parser, منطقی convert_p, منطقی fold_p,
		    vec<درخت, va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, درخت *sizeof_arg,
		    vec<location_t> *locations,
		    unsigned صحیح *literal_zero_mask)
{
  vec<درخت, va_gc> *ret;
  vec<درخت, va_gc> *orig_types;
  ساختار c_عبارت عبارت;
  unsigned صحیح idx = 0;
  منطقی save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = نادرست;

  ret = make_درخت_vector ();
  اگر (p_orig_types == پوچ)
    orig_types = پوچ;
  وگرنه
    orig_types = make_درخت_vector ();

  اگر (literal_zero_mask)
    c_parser_check_literal_zero (parser, literal_zero_mask, 0);
  عبارت = c_parser_عبارت_no_commas (parser, پوچ);
  اگر (convert_p)
    عبارت = convert_lvalue_to_rvalue (عبارت.get_location (), عبارت, درست, درست);
  اگر (fold_p)
    عبارت.مقدار = c_fully_fold (عبارت.مقدار, نادرست, پوچ);
  ret->quick_افزودن (عبارت.مقدار);
  اگر (orig_types)
    orig_types->quick_افزودن (عبارت.original_type);
  اگر (locations)
    locations->safe_افزودن (عبارت.get_location ());
  اگر (sizeof_arg != پوچ
      && (عبارت.original_code == SIZEOF_عبارت
	  || عبارت.original_code == PAREN_SIZEOF_عبارت))
    {
      sizeof_arg[0] = c_last_sizeof_arg;
      sizeof_arg_loc[0] = c_last_sizeof_loc;
    }
  وقتی (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      اگر (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  درخت مقدار = embed->مقدار;
	  عبارت.original_code = INTEGER_CST;
	  عبارت.original_type = integer_type_گره;
	  عبارت.مقدار = NULL_درخت;
	  set_c_عبارت_source_range (&عبارت, embed->get_range ());
	  عبارت.m_decimal = 0;
	  برای (unsigned صحیح i = 0; i < (unsigned) RAW_DATA_LENGTH (مقدار); i++)
	    {
	      اگر (literal_zero_mask
		  && idx + 1 < HOST_BITS_PER_INT
		  && RAW_DATA_POINTER (مقدار)[i] == 0)
		*literal_zero_mask |= 1U << (idx + 1);
	      عبارت.مقدار = build_int_cst (integer_type_گره,
					  RAW_DATA_UCHAR_ELT (مقدار, i));
	      vec_safe_افزودن (ret, عبارت.مقدار);
	      اگر (orig_types)
		vec_safe_افزودن (orig_types, عبارت.original_type);
	      اگر (locations)
		locations->safe_افزودن (عبارت.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  ادامه;
	}
      اگر (literal_zero_mask)
	c_parser_check_literal_zero (parser, literal_zero_mask, idx + 1);
      عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      اگر (convert_p)
	عبارت = convert_lvalue_to_rvalue (عبارت.get_location (), عبارت, درست,
					 درست);
      اگر (fold_p)
	عبارت.مقدار = c_fully_fold (عبارت.مقدار, نادرست, پوچ);
      vec_safe_افزودن (ret, عبارت.مقدار);
      اگر (orig_types)
	vec_safe_افزودن (orig_types, عبارت.original_type);
      اگر (locations)
	locations->safe_افزودن (عبارت.get_location ());
      اگر (++idx < 6
	  && sizeof_arg != پوچ
	  && (عبارت.original_code == SIZEOF_عبارت
	      || عبارت.original_code == PAREN_SIZEOF_عبارت))
	{
	  sizeof_arg[idx] = c_last_sizeof_arg;
	  sizeof_arg_loc[idx] = c_last_sizeof_loc;
	}
    }
  اگر (orig_types)
    *p_orig_types = orig_types;
  c_omp_array_section_p = save_c_omp_array_section_p;
  بازگشت ret;
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

ایستا تهی
c_parser_objc_class_definition (c_parser *parser, درخت attributes)
{
  منطقی iface_p;
  درخت id1;
  درخت superclass;
  اگر (c_parser_next_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = درست;
  وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = نادرست;
  وگرنه
    gcc_unreachable ();

  c_parser_consume_token (parser);
  اگر (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      بازگشت;
    }
  id1 = c_parser_peek_token (parser)->مقدار;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      درخت id2;
      درخت proto = NULL_درخت;
      matching_parens parens;
      parens.consume_open (parser);
      اگر (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  اگر (iface_p && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_درخت;
	    }
	  وگرنه
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
	      بازگشت;
	    }
	}
      وگرنه
	{
	  id2 = c_parser_peek_token (parser)->مقدار;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_found_close (parser);
      اگر (!iface_p)
	{
	  objc_start_category_implementation (id1, id2);
	  بازگشت;
	}
      اگر (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_category_interface (id1, id2, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
      بازگشت;
    }
  اگر (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      اگر (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  بازگشت;
	}
      superclass = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);
    }
  وگرنه
    superclass = NULL_درخت;
  اگر (iface_p)
    {
      درخت proto = NULL_درخت;
      اگر (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_class_interface (id1, loc1, superclass, proto, attributes);
    }
  وگرنه
    objc_start_class_implementation (id1, superclass);
  اگر (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  اگر (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
    }
  وگرنه
    {
      objc_continue_implementation ();
      بازگشت;
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

ایستا تهی
c_parser_objc_class_instance_variables (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  وقتی (c_parser_next_token_is_not (parser, CPP_EOF))
    {
      درخت decls;
      /* Parse any stray semicolon.  */
      اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  ادامه;
	}
      /* Stop if at the end of the instance variables.  */
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  بشکن;
	}
      /* Parse any objc-visibility-spec.  */
      اگر (c_parser_next_token_is_keyword (parser, RID_AT_PRIVATE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PRIVATE);
	  ادامه;
	}
      وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PROTECTED);
	  ادامه;
	}
      وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_AT_PUBLIC))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PUBLIC);
	  ادامه;
	}
      وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PACKAGE);
	  ادامه;
	}
      وگرنه اگر (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, پوچ, NULL_درخت);
	  ادامه;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser, پوچ);
      اگر (decls == پوچ)
	{
	  /* There is a syntax error.  We want to skip the offending
	     tokens up to the next ';' (included) or '}'
	     (excluded).  */

	  /* First, skip manually a ')' or ']'.  This is because they
	     reduce the nesting level, so c_parser_skip_until_found()
	     wouldn't be able to skip past them.  */
	  c_token *token = c_parser_peek_token (parser);
	  اگر (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_SQUARE)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, پوچ);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = نادرست;
	  ادامه;
	}
      وگرنه
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  درخت ivar = nreverse (decls);
	  برای (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_add_instance_variable (copy_گره (ivar));
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}

/* Parse an objc-class-declaration.

   objc-class-declaration:
     @class identifier-list ;
*/

ایستا تهی
c_parser_objc_class_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_CLASS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  وقتی (درست)
    {
      درخت id;
      اگر (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, پوچ);
	  parser->error = نادرست;
	  بازگشت;
	}
      id = c_parser_peek_token (parser)->مقدار;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      اگر (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وگرنه
	بشکن;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse an objc-alias-declaration.

   objc-alias-declaration:
     @compatibility_alias identifier identifier ;
*/

ایستا تهی
c_parser_objc_alias_declaration (c_parser *parser)
{
  درخت id1, id2;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  اگر (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, پوچ);
      بازگشت;
    }
  id1 = c_parser_peek_token (parser)->مقدار;
  c_parser_consume_token (parser);
  اگر (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, پوچ);
      بازگشت;
    }
  id2 = c_parser_peek_token (parser)->مقدار;
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

ایستا تهی
c_parser_objc_protocol_definition (c_parser *parser, درخت attributes)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  اگر (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      بازگشت;
    }
  اگر (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      وقتی (درست)
	{
	  درخت id;
	  اگر (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      بشکن;
	    }
	  id = c_parser_peek_token (parser)->مقدار;
	  objc_declare_protocol (id, attributes);
	  c_parser_consume_token (parser);
	  اگر (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وگرنه
	    بشکن;
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  وگرنه
    {
      درخت id = c_parser_peek_token (parser)->مقدار;
      درخت proto = NULL_درخت;
      c_parser_consume_token (parser);
      اگر (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = درست;
      objc_start_protocol (id, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      parser->objc_pq_context = نادرست;
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
ایستا درونخطی منطقی
c_parser_objc_method_type (c_parser *parser)
{
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_PLUS:
      c_parser_consume_token (parser);
      بازگشت درست;
    حالت CPP_MINUS:
      c_parser_consume_token (parser);
      بازگشت نادرست;
    پیشفرض:
      gcc_unreachable ();
    }
}

/* Parse an objc-method-definition.

   objc-method-definition:
     objc-method-type objc-method-decl ;[opt] compound-statement
*/

ایستا تهی
c_parser_objc_method_definition (c_parser *parser)
{
  منطقی is_class_method = c_parser_objc_method_type (parser);
  درخت decl, attributes = NULL_درخت, عبارت = NULL_درخت;
  parser->objc_pq_context = درست;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    &عبارت);
  اگر (decl == error_mark_گره)
    بازگشت;  /* Bail here. */

  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  اگر (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      بازگشت;
    }

  parser->objc_pq_context = نادرست;
  اگر (objc_start_method_definition (is_class_method, decl, attributes, عبارت))
    {
      add_stmt (c_parser_compound_statement (parser));
      objc_finish_method_definition (current_function_decl);
    }
  وگرنه
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

ایستا تهی
c_parser_objc_methodprotolist (c_parser *parser)
{
  وقتی (درست)
    {
      /* The list is terminated by @end.  */
      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_SEMICOLON:
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  بشکن;
	حالت CPP_PLUS:
	حالت CPP_MINUS:
	  c_parser_objc_methodproto (parser);
	  بشکن;
	حالت CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external, پوچ, NULL_درخت);
	  بشکن;
	حالت CPP_EOF:
	  بازگشت;
	پیشفرض:
	  اگر (c_parser_next_token_is_keyword (parser, RID_AT_END))
	    بازگشت;
	  وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_set_method_opt (درست);
	      c_parser_consume_token (parser);
	    }
	  وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_set_method_opt (نادرست);
	      c_parser_consume_token (parser);
	    }
	  وگرنه
	    c_parser_declaration_or_fndef (parser, نادرست, نادرست, درست,
					   نادرست, درست, نادرست);
	  بشکن;
	}
    }
}

/* Parse an objc-methodproto.

   objc-methodproto:
     objc-method-type objc-method-decl ;
*/

ایستا تهی
c_parser_objc_methodproto (c_parser *parser)
{
  منطقی is_class_method = c_parser_objc_method_type (parser);
  درخت decl, attributes = NULL_درخت;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = درست;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    پوچ);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = نادرست;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  اگر (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      بازگشت;
    }

  اگر (decl != error_mark_گره)
    objc_add_method_declaration (is_class_method, decl, attributes);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

ایستا منطقی
c_parser_objc_maybe_method_attributes (c_parser* parser, درخت* attributes)
{
  منطقی bad = نادرست;
  اگر (*attributes)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *attributes = NULL_درخت;
      bad = درست;
    }

  اگر (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    *attributes = c_parser_gnu_attributes (parser);

  /* If there were no attributes here, just report any earlier error.  */
  اگر (*attributes == NULL_درخت || bad)
    بازگشت bad;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    بازگشت bad;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  بازگشت درست;
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

ایستا درخت
c_parser_objc_method_decl (c_parser *parser, منطقی is_class_method,
			   درخت *attributes, درخت *عبارت)
{
  درخت type = NULL_درخت;
  درخت sel;
  درخت parms = NULL_درخت;
  منطقی ellipsis = نادرست;
  منطقی attr_err = نادرست;

  *attributes = NULL_درخت;
  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
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
  اگر (!sel || c_parser_next_token_is (parser, CPP_COLON))
    {
      درخت tsel = sel;
      درخت list = NULL_درخت;
      وقتی (درست)
	{
	  درخت atype = NULL_درخت, id, keyworddecl;
	  درخت param_attr = NULL_درخت;
	  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    بشکن;
	  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  اگر (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_attributes (parser);
	  اگر (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      بازگشت error_mark_گره;
	    }
	  id = c_parser_peek_token (parser)->مقدار;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  اگر (!tsel && c_parser_next_token_is_not (parser, CPP_COLON))
	    بشکن;
	}

      attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_گره (درخت_LIST);
      وقتی (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  ساختار c_parm *parm;
	  c_parser_consume_token (parser);
	  اگر (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = درست;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_method_attributes
						(parser, attributes) ;
	      بشکن;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_درخت, نادرست);
	  اگر (parm == پوچ)
	    بشکن;
	  parms = chainon (parms,
			   build_درخت_list (NULL_درخت, grokparm (parm, عبارت)));
	}
      sel = list;
    }
  وگرنه
    attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

  اگر (sel == پوچ)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      بازگشت error_mark_گره;
    }

  اگر (attr_err)
    بازگشت error_mark_گره;

  بازگشت objc_build_method_signature (is_class_method, type, sel, parms, ellipsis);
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

ایستا درخت
c_parser_objc_type_name (c_parser *parser)
{
  درخت quals = NULL_درخت;
  ساختار c_type_name *type_name = پوچ;
  درخت type = NULL_درخت;
  وقتی (درست)
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (token->type == CPP_KEYWORD
	  && (token->keyword == RID_IN
	      || token->keyword == RID_OUT
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_درخت_list (NULL_درخت, token->مقدار), quals);
	  c_parser_consume_token (parser);
	}
      وگرنه
	بشکن;
    }
  اگر (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  اگر (type_name)
    type = groktypename (type_name, پوچ, پوچ);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  اگر (type == error_mark_گره)
    type = NULL_درخت;

  بازگشت build_درخت_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

ایستا درخت
c_parser_objc_protocol_refs (c_parser *parser)
{
  درخت list = NULL_درخت;
  gcc_assert (c_parser_next_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  وقتی (درست)
    {
      درخت id;
      اگر (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  بشکن;
	}
      id = c_parser_peek_token (parser)->مقدار;
      list = chainon (list, build_درخت_list (NULL_درخت, id));
      c_parser_consume_token (parser);
      اگر (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وگرنه
	بشکن;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  بازگشت list;
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

ایستا تهی
c_parser_objc_try_catch_finally_statement (c_parser *parser)
{
  location_t location;
  درخت stmt;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  وقتی (c_parser_next_token_is_keyword (parser, RID_AT_CATCH))
    {
      ساختار c_parm *parm;
      درخت parameter_declaration = error_mark_گره;
      منطقی seen_open_paren = نادرست;

      c_parser_consume_token (parser);
      matching_parens parens;
      اگر (!parens.require_open (parser))
	seen_open_paren = درست;
      اگر (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_درخت;
	}
      وگرنه
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_درخت, نادرست);
	  اگر (parm == پوچ)
	    parameter_declaration = error_mark_گره;
	  وگرنه
	    parameter_declaration = grokparm (parm, پوچ);
	}
      اگر (seen_open_paren)
	parens.require_close (parser);
      وگرنه
	{
	  /* If there was no open parenthesis, we are recovering from
	     an error, and we are trying to figure out what mistake
	     the user has made.  */

	  /* If there is an immediate closing parenthesis, the user
	     probably forgot the opening one (ie, they typed "@catch
	     NSException *e)".  Parse the closing parenthesis and keep
	     going.  */
	  اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      اگر (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_finish_catch_clause ();
    }
  اگر (c_parser_next_token_is_keyword (parser, RID_AT_FINALLY))
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

ایستا تهی
c_parser_objc_synchronized_statement (c_parser *parser)
{
  location_t loc;
  درخت عبارت, stmt;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      ساختار c_عبارت ce = c_parser_expression (parser);
      ce = convert_lvalue_to_rvalue (loc, ce, نادرست, نادرست);
      عبارت = ce.مقدار;
      عبارت = c_fully_fold (عبارت, نادرست, پوچ);
      parens.skip_until_found_close (parser);
    }
  وگرنه
    عبارت = error_mark_گره;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, عبارت, stmt);
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

ایستا درخت
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  درخت مقدار = token->مقدار;
  اگر (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      بازگشت مقدار;
    }
  اگر (token->type != CPP_KEYWORD)
    بازگشت NULL_درخت;
  انتخاب (token->keyword)
    {
    حالت RID_ENUM:
    حالت RID_STRUCT:
    حالت RID_UNION:
    حالت RID_IF:
    حالت RID_ELSE:
    حالت RID_WHILE:
    حالت RID_DO:
    حالت RID_FOR:
    حالت RID_SWITCH:
    حالت RID_CASE:
    حالت RID_DEFAULT:
    حالت RID_BREAK:
    حالت RID_CONTINUE:
    حالت RID_RETURN:
    حالت RID_GOTO:
    حالت RID_ASM:
    حالت RID_SIZEOF:
    حالت RID_TYPEOF:
    حالت RID_TYPEOF_UNQUAL:
    حالت RID_ALIGNOF:
    حالت RID_UNSIGNED:
    حالت RID_LONG:
    حالت RID_CONST:
    حالت RID_SHORT:
    حالت RID_VOLATILE:
    حالت RID_SIGNED:
    حالت RID_RESTRICT:
    حالت RID_COMPLEX:
    حالت RID_IN:
    حالت RID_OUT:
    حالت RID_INOUT:
    حالت RID_BYCOPY:
    حالت RID_BYREF:
    حالت RID_ONEWAY:
    حالت RID_INT:
    حالت RID_CHAR:
    حالت RID_FLOAT:
    حالت RID_DOUBLE:
    CASE_RID_FLOATN_NX:
    حالت RID_VOID:
    حالت RID_BOOL:
    حالت RID_ATOMIC:
    حالت RID_AUTO_TYPE:
    حالت RID_INT_N_0:
    حالت RID_INT_N_1:
    حالت RID_INT_N_2:
    حالت RID_INT_N_3:
      c_parser_consume_token (parser);
      بازگشت مقدار;
    پیشفرض:
      بازگشت NULL_درخت;
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

ایستا درخت
c_parser_objc_selector_arg (c_parser *parser)
{
  درخت sel = c_parser_objc_selector (parser);
  درخت list = NULL_درخت;
  اگر (sel
      && c_parser_next_token_is_not (parser, CPP_COLON)
      && c_parser_next_token_is_not (parser, CPP_SCOPE))
    بازگشت sel;
  وقتی (درست)
    {
      اگر (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_درخت_list (sel, NULL_درخت));
	  list = chainon (list, build_درخت_list (NULL_درخت, NULL_درخت));
	}
      وگرنه
	{
	  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    بازگشت list;
	  list = chainon (list, build_درخت_list (sel, NULL_درخت));
	}
      sel = c_parser_objc_selector (parser);
      اگر (!sel
	  && c_parser_next_token_is_not (parser, CPP_COLON)
	  && c_parser_next_token_is_not (parser, CPP_SCOPE))
	بشکن;
    }
  بازگشت list;
}

/* Parse an objc-receiver.

   objc-receiver:
     expression
     class-name
     type-name
*/

ایستا درخت
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  اگر (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
    {
      درخت id = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);
      بازگشت objc_get_class_reference (id);
    }
  ساختار c_عبارت ce = c_parser_expression (parser);
  ce = convert_lvalue_to_rvalue (loc, ce, نادرست, نادرست);
  بازگشت c_fully_fold (ce.مقدار, نادرست, پوچ);
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

ایستا درخت
c_parser_objc_message_args (c_parser *parser)
{
  درخت sel = c_parser_objc_selector (parser);
  درخت list = NULL_درخت;
  اگر (sel && c_parser_next_token_is_not (parser, CPP_COLON))
    بازگشت sel;
  وقتی (درست)
    {
      درخت keywordexpr;
      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	بازگشت error_mark_گره;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_درخت_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      اگر (!sel && c_parser_next_token_is_not (parser, CPP_COLON))
	بشکن;
    }
  بازگشت list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

ایستا درخت
c_parser_objc_keywordexpr (c_parser *parser)
{
  درخت ret;
  vec<درخت, va_gc> *عبارت_list = c_parser_عبارت_list (parser, درست, درست,
						پوچ, پوچ, پوچ, پوچ);
  اگر (vec_safe_length (عبارت_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*عبارت_list)[0];
    }
  وگرنه
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_درخت_list_vec (عبارت_list);
    }
  release_درخت_vector (عبارت_list);
  بازگشت ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
ایستا منطقی
c_parser_objc_diagnose_bad_element_prefix (c_parser *parser,
					   ساختار c_declspecs *specs)
{
  اگر (!specs->declspecs_seen_p || specs->non_sc_seen_p
      || specs->typespec_kind != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_to_end_of_block_or_statement (parser);
      بازگشت درست;
    }
  بازگشت نادرست;
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
ایستا تهی
c_parser_objc_at_property_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY));
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);  /* Eat '@property'.  */

  /* Parse the optional attribute list.

     A list of parsed, but not verified, attributes.  */
  vec<property_attribute_info *> prop_attr_list = vNULL;

  منطقی syntax_error = نادرست;
  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_start = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = درست;

      /* Allow @property (), with a warning.  */
      location_t attr_end = c_parser_peek_token (parser)->location;

      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_end, attr_start, attr_end);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      وگرنه
	وقتی (درست)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_start = token->location;
	    attr_end = get_finish (token->location);
	    location_t attr_comb = make_location (attr_start, attr_start,
						  attr_end);

	    اگر (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		اگر (token->type == CPP_CLOSE_PAREN)
		  بشکن;
		c_parser_consume_token (parser);
		ادامه;
	      }

	    درخت attr_name = NULL_درخت;
	    شمارش rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    منطقی add_at = نادرست;
	    اگر (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		اگر (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->مقدار;
		    add_at = درست;
		  }
		وگرنه
		  attr_name = ridpointers[(صحیح)keyword];
	      }
	    وگرنه اگر (token->type == CPP_NAME)
	      attr_name = token->مقدار;
	    c_parser_consume_token (parser);

	    شمارش objc_property_attribute_kind prop_kind
	      = objc_prop_attr_kind_for_rid (keyword);
	    property_attribute_info *prop
	      = جدید property_attribute_info (attr_name, attr_comb, prop_kind);
	    prop_attr_list.safe_افزودن (prop);

	    درخت meth_name;
	    انتخاب (prop->prop_kind)
	      {
	      پیشفرض: بشکن;
	      حالت OBJC_PROPERTY_ATTR_UNKNOWN:
		اگر (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    add_at ? "@" : "", IDENTIFIER_POINTER (attr_name));
		وگرنه
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = درست;
		بشکن;

	      حالت OBJC_PROPERTY_ATTR_GETTER:
	      حالت OBJC_PROPERTY_ATTR_SETTER:
		اگر (c_parser_next_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = درست;
		    بشکن;
		  }
		token = c_parser_peek_token (parser);
		attr_end = token->location;
		c_parser_consume_token (parser); /* eat the = */
		اگر (c_parser_next_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = درست;
		    بشکن;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_end = get_finish (token->location);
		meth_name = token->مقدار;
		c_parser_consume_token (parser);
		اگر (prop->prop_kind == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    اگر (c_parser_next_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_end, attr_start,
						   attr_end);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = درست;
		      }
		    وگرنه
		      {
			attr_end = get_finish (c_parser_peek_token
					       (parser)->location);
			c_parser_consume_token (parser);
		      }
		    attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		  }
		وگرنه
		  attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		prop->ident = meth_name;
		/* Updated location including all that was successfully
		   parsed.  */
		prop->prop_loc = attr_comb;
		بشکن;
	    }

	  /* If we see a comma here, then keep going - even if we already
	     saw a syntax error.  For simple mistakes e.g. (assign, getter=x)
	     this makes a more useful output and avoid spurious warnings about
	     missing attributes that are, in fact, specified after the one with
	     the syntax error.  */
	  اگر (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وگرنه
	    بشکن;
	}
      parser->objc_property_attr_context = نادرست;

      اگر (syntax_error && c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      وگرنه
	syntax_error = نادرست, parens.skip_until_found_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  درخت properties = c_parser_struct_declaration (parser, پوچ);

  اگر (properties == error_mark_گره)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, پوچ);
  وگرنه
    {
      اگر (properties == NULL_درخت)
	c_parser_error (parser, "expected identifier");
      وگرنه
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  برای (; properties; properties = درخت_CHAIN (properties))
	    objc_add_property_declaration (loc, copy_گره (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  وقتی (!prop_attr_list.is_empty())
    delete prop_attr_list.برداشت ();
  prop_attr_list.release ();
  parser->error = نادرست;
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
ایستا تهی
c_parser_objc_at_synthesize_declaration (c_parser *parser)
{
  درخت list = NULL_درخت;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  وقتی (درست)
    {
      درخت property, ivar;
      اگر (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, پوچ);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = نادرست;
	  بازگشت;
	}
      property = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);
      اگر (c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  اگر (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_SEMICOLON, پوچ);
	      parser->error = نادرست;
	      بازگشت;
	    }
	  ivar = c_parser_peek_token (parser)->مقدار;
	  c_parser_consume_token (parser);
	}
      وگرنه
	ivar = NULL_درخت;
      list = chainon (list, build_درخت_list (ivar, property));
      اگر (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وگرنه
	بشکن;
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
ایستا تهی
c_parser_objc_at_dynamic_declaration (c_parser *parser)
{
  درخت list = NULL_درخت;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  وقتی (درست)
    {
      درخت property;
      اگر (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, پوچ);
	  parser->error = نادرست;
	  بازگشت;
	}
      property = c_parser_peek_token (parser)->مقدار;
      list = chainon (list, build_درخت_list (NULL_درخت, property));
      c_parser_consume_token (parser);
      اگر (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وگرنه
	بشکن;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_add_dynamic_declaration (loc, list);
}


/* Parse a pragma GCC ivdep.  */

ایستا منطقی
c_parse_pragma_ivdep (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  بازگشت درست;
}

/* Parse a pragma GCC novector.  */

ایستا منطقی
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  بازگشت درست;
}

/* Parse a pragma GCC unroll.  */

ایستا unsigned short
c_parser_pragma_unroll (c_parser *parser)
{
  unsigned short unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  درخت عبارت = c_parser_عبارت_no_commas (parser, پوچ).مقدار;
  mark_exp_read (عبارت);
  عبارت = c_fully_fold (عبارت, نادرست, پوچ);
  HOST_WIDE_INT lunroll = 0;
  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (عبارت))
      || درخت_CODE (عبارت) != INTEGER_CST
      || (lunroll = درخت_to_shwi (عبارت)) < 0
      || lunroll >= USHRT_MAX)
    {
      error_at (location, "%<#pragma GCC unroll%> requires an"
		" assignment-expression that evaluates to a non-negative"
		" integral constant less than %u", USHRT_MAX);
      unroll = 0;
    }
  وگرنه
    {
      unroll = (unsigned short)lunroll;
      اگر (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_to_pragma_eol (parser);
  بازگشت unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

ایستا منطقی
c_parser_pragma (c_parser *parser, شمارش pragma_context context, منطقی *if_p,
		 درخت before_labels)
{
  unsigned صحیح id;
  ثابت نویسه *construct = پوچ;

  درون_داد_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_kind;
  gcc_assert (id != PRAGMA_NONE);
  اگر (parser->omp_for_parse_state
      && parser->omp_for_parse_state->in_intervening_code
      && id >= PRAGMA_OMP__START_ && id <= PRAGMA_OMP__LAST_
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	درون_داد_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->fail = درست;
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, پوچ);
      بازگشت نادرست;
    }

  انتخاب (id)
    {
    حالت PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      بازگشت نادرست;

    حالت PRAGMA_OACC_ENTER_DATA:
      اگر (context != pragma_compound)
	{
	  construct = "acc enter data";
	in_compound:
	  اگر (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, پوچ);
	      بازگشت درست;
	    }
	  برو bad_stmt;
	}
      c_parser_oacc_enter_exit_data (parser, درست);
      بازگشت نادرست;

    حالت PRAGMA_OACC_EXIT_DATA:
      اگر (context != pragma_compound)
	{
	  construct = "acc exit data";
	  برو in_compound;
	}
      c_parser_oacc_enter_exit_data (parser, نادرست);
      بازگشت نادرست;

    حالت PRAGMA_OACC_ROUTINE:
      اگر (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, پوچ);
	  بازگشت نادرست;
	}
      c_parser_oacc_routine (parser, context);
      بازگشت نادرست;

    حالت PRAGMA_OACC_UPDATE:
      اگر (context != pragma_compound)
	{
	  construct = "acc update";
	  برو in_compound;
	}
      c_parser_oacc_update (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_BARRIER:
      اگر (context != pragma_compound)
	{
	  construct = "omp barrier";
	  برو in_compound;
	}
      c_parser_omp_barrier (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_DEPOBJ:
      اگر (context != pragma_compound)
	{
	  construct = "omp depobj";
	  برو in_compound;
	}
      c_parser_omp_depobj (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_FLUSH:
      اگر (context != pragma_compound)
	{
	  construct = "omp flush";
	  برو in_compound;
	}
      c_parser_omp_flush (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_INTEROP:
      اگر (context != pragma_compound)
	{
	  construct = "omp interop";
	  برو in_compound;
	}
      c_parser_omp_interop (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_TASKWAIT:
      اگر (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  برو in_compound;
	}
      c_parser_omp_taskwait (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_TASKYIELD:
      اگر (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  برو in_compound;
	}
      c_parser_omp_taskyield (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_CANCEL:
      اگر (context != pragma_compound)
	{
	  construct = "omp cancel";
	  برو in_compound;
	}
      c_parser_omp_cancel (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_CANCELLATION_POINT:
      بازگشت c_parser_omp_cancellation_point (parser, context);

    حالت PRAGMA_OMP_GROUPPRIVATE:
      c_parser_omp_groupprivate (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_THREADPRIVATE:
      c_parser_omp_threadprivate (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_TARGET:
      بازگشت c_parser_omp_target (parser, context, if_p);

    حالت PRAGMA_OMP_BEGIN:
      c_parser_omp_begin (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_END:
      c_parser_omp_end (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_SCAN:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, پوچ);
      بازگشت نادرست;

    حالت PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, پوچ);
      بازگشت نادرست;

    حالت PRAGMA_OMP_DECLARE:
      بازگشت c_parser_omp_declare (parser, context);

    حالت PRAGMA_OMP_REQUIRES:
      اگر (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, پوچ);
	  بازگشت نادرست;
	}
      c_parser_omp_requires (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_ALLOCATE:
      c_parser_omp_allocate (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_ASSUMES:
      اگر (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp assumes");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, پوچ);
	  بازگشت نادرست;
	}
      c_parser_omp_assumes (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      بازگشت نادرست;

    حالت PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      بازگشت درست;

    حالت PRAGMA_OMP_ERROR:
      بازگشت c_parser_omp_error (parser, context);

    حالت PRAGMA_OMP_ORDERED:
      بازگشت c_parser_omp_ordered (parser, context, if_p);

    حالت PRAGMA_NOVECTOR:
    حالت PRAGMA_UNROLL:
    حالت PRAGMA_IVDEP:
      {
	منطقی novector = نادرست;
	unsigned short unroll = 0;
	منطقی ivdep = نادرست;

	انتخاب (id)
	  {
	  حالت PRAGMA_NOVECTOR:
	    novector = c_parse_pragma_novector (parser);
	    بشکن;
	  حالت PRAGMA_UNROLL:
	    unroll = c_parser_pragma_unroll (parser);
	    بشکن;
	  حالت PRAGMA_IVDEP:
	    ivdep = c_parse_pragma_ivdep (parser);
	    بشکن;
	  پیشفرض:
	    gcc_unreachable ();
	  }

	c_token *tok = c_parser_peek_token (parser);
	منطقی has_more = tok->type == CPP_PRAGMA;
	وقتی (has_more)
	  {
	    انتخاب (tok->pragma_kind)
	      {
	      حالت PRAGMA_IVDEP:
		ivdep = c_parse_pragma_ivdep (parser);
		بشکن;
	      حالت PRAGMA_UNROLL:
		unroll = c_parser_pragma_unroll (parser);
		بشکن;
	      حالت PRAGMA_NOVECTOR:
		novector = c_parse_pragma_novector (parser);
		بشکن;
	      پیشفرض:
		has_more = نادرست;
		بشکن;
	      }
	    tok = c_parser_peek_token (parser);
	    has_more = has_more && tok->type == CPP_PRAGMA;
	  }
	اگر (!c_parser_next_token_is_keyword (parser, RID_FOR)
	    && !c_parser_next_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_next_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    بازگشت نادرست;
	  }
	اگر (c_parser_next_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	وگرنه
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      بازگشت درست;

    حالت PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, پوچ);
      بازگشت نادرست;

    حالت PRAGMA_OACC_WAIT:
      اگر (context != pragma_compound)
	{
	  construct = "acc wait";
	  برو in_compound;
	}
	/* FALL THROUGH.  */

    پیشفرض:
      اگر (id < PRAGMA_FIRST_EXTERNAL)
	{
	  اگر (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, پوچ);
	      بازگشت نادرست;
	    }
	  c_parser_omp_construct (parser, if_p);
	  بازگشت درست;
	}
      بشکن;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = درست;
  c_parser_skip_to_pragma_eol (parser);

  بازگشت نادرست;
}

/* The interface the pragma parsers have to the lexer.  */

شمارش cpp_ttype
pragma_lex (درخت *مقدار, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  شمارش cpp_ttype ret = tok->type;

  *مقدار = tok->مقدار;
  اگر (loc)
    *loc = tok->location;

  اگر (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  وگرنه اگر (ret == CPP_STRING)
    *مقدار = c_parser_string_literal (the_parser, نادرست, نادرست).مقدار;
  وگرنه
    {
      اگر (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  بازگشت ret;
}

تهی
pragma_lex_discard_to_eol ()
{
  cpp_ttype type;
  انجامبده
    {
      type = c_parser_peek_token (the_parser)->type;
      gcc_assert (type != CPP_EOF);
      c_parser_consume_token (the_parser);
    } وقتی (type != CPP_PRAGMA_EOL);
}

ایستا تهی
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  درخت name = پوچ;

  parser->lex_joined_string = درست;
  c_parser_consume_pragma (parser);
  اگر (c_parser_next_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);
    }
  وگرنه
    c_parser_error (parser, "expected string literal");
  c_parser_skip_to_pragma_eol (parser);
  parser->lex_joined_string = نادرست;

  اگر (name)
    c_common_pch_pragma (parse_in, درخت_STRING_POINTER (name));
}

/* OpenACC and OpenMP parsing routines.  */

/* Returns name of the next clause.
   If the clause is not recognized PRAGMA_OMP_CLAUSE_NONE is returned and
   the token is not consumed.  Otherwise appropriate pragma_omp_clause is
   returned and the token is consumed.  */

ایستا pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause result = PRAGMA_OMP_CLAUSE_NONE;

  اگر (c_parser_next_token_is_keyword (parser, RID_AUTO))
    result = PRAGMA_OACC_CLAUSE_AUTO;
  وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_IF))
    result = PRAGMA_OMP_CLAUSE_IF;
  وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    result = PRAGMA_OMP_CLAUSE_DEFAULT;
  وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_FOR))
    result = PRAGMA_OMP_CLAUSE_FOR;
  وگرنه اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);

      انتخاب (p[0])
	{
	حالت 'a':
	  اگر (!strcmp ("affinity", p))
	    result = PRAGMA_OMP_CLAUSE_AFFINITY;
	  وگرنه اگر (!strcmp ("aligned", p))
	    result = PRAGMA_OMP_CLAUSE_ALIGNED;
	  وگرنه اگر (!strcmp ("allocate", p))
	    result = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  وگرنه اگر (!strcmp ("async", p))
	    result = PRAGMA_OACC_CLAUSE_ASYNC;
	  وگرنه اگر (!strcmp ("attach", p))
	    result = PRAGMA_OACC_CLAUSE_ATTACH;
	  بشکن;
	حالت 'b':
	  اگر (!strcmp ("bind", p))
	    result = PRAGMA_OMP_CLAUSE_BIND;
	  بشکن;
	حالت 'c':
	  اگر (!strcmp ("collapse", p))
	    result = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  وگرنه اگر (!strcmp ("copy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  وگرنه اگر (!strcmp ("copyin", p))
	    result = PRAGMA_OMP_CLAUSE_COPYIN;
	  وگرنه اگر (!strcmp ("copyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
          وگرنه اگر (!strcmp ("copyprivate", p))
	    result = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  وگرنه اگر (!strcmp ("create", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  بشکن;
	حالت 'd':
	  اگر (!strcmp ("defaultmap", p))
	    result = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  وگرنه اگر (!strcmp ("delete", p))
	    result = PRAGMA_OACC_CLAUSE_DELETE;
	  وگرنه اگر (!strcmp ("depend", p))
	    result = PRAGMA_OMP_CLAUSE_DEPEND;
	  وگرنه اگر (!strcmp ("destroy", p))
	    result = PRAGMA_OMP_CLAUSE_DESTROY;
	  وگرنه اگر (!strcmp ("detach", p))
	    result = PRAGMA_OACC_CLAUSE_DETACH;
	  وگرنه اگر (!strcmp ("device", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE;
	  وگرنه اگر (!strcmp ("deviceptr", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  وگرنه اگر (!strcmp ("device_resident", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  وگرنه اگر (!strcmp ("device_type", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  وگرنه اگر (!strcmp ("dist_schedule", p))
	    result = PRAGMA_OMP_CLAUSE_DIST_SCHEDULE;
	  وگرنه اگر (!strcmp ("doacross", p))
	    result = PRAGMA_OMP_CLAUSE_DOACROSS;
	  وگرنه اگر (!strcmp ("dyn_groupprivate", p))
	    result = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  بشکن;
	حالت 'e':
	  اگر (!strcmp ("enter", p))
	    result = PRAGMA_OMP_CLAUSE_ENTER;
	  بشکن;
	حالت 'f':
	  اگر (!strcmp ("filter", p))
	    result = PRAGMA_OMP_CLAUSE_FILTER;
	  وگرنه اگر (!strcmp ("final", p))
	    result = PRAGMA_OMP_CLAUSE_FINAL;
	  وگرنه اگر (!strcmp ("finalize", p))
	    result = PRAGMA_OACC_CLAUSE_FINALIZE;
	  وگرنه اگر (!strcmp ("firstprivate", p))
	    result = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  وگرنه اگر (!strcmp ("from", p))
	    result = PRAGMA_OMP_CLAUSE_FROM;
	  وگرنه اگر (!strcmp ("full", p))
	    result = PRAGMA_OMP_CLAUSE_FULL;
	  بشکن;
	حالت 'g':
	  اگر (!strcmp ("gang", p))
	    result = PRAGMA_OACC_CLAUSE_GANG;
	  وگرنه اگر (!strcmp ("grainsize", p))
	    result = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  بشکن;
	حالت 'h':
	  اگر (!strcmp ("has_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  وگرنه اگر (!strcmp ("hint", p))
	    result = PRAGMA_OMP_CLAUSE_HINT;
	  وگرنه اگر (!strcmp ("host", p))
	    result = PRAGMA_OACC_CLAUSE_HOST;
	  بشکن;
	حالت 'i':
	  اگر (!strcmp ("if_present", p))
	    result = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  وگرنه اگر (!strcmp ("in_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_IN_REDUCTION;
	  وگرنه اگر (!strcmp ("inbranch", p))
	    result = PRAGMA_OMP_CLAUSE_INBRANCH;
	  وگرنه اگر (!strcmp ("independent", p))
	    result = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  وگرنه اگر (!strcmp ("indirect", p))
	    result = PRAGMA_OMP_CLAUSE_INDIRECT;
	  وگرنه اگر (!strcmp ("init", p))
	    result = PRAGMA_OMP_CLAUSE_INIT;
	  وگرنه اگر (!strcmp ("is_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  وگرنه اگر (!strcmp ("interop", p))
	    result = PRAGMA_OMP_CLAUSE_INTEROP;
	  بشکن;
	حالت 'l':
	  اگر (!strcmp ("lastprivate", p))
	    result = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  وگرنه اگر (!strcmp ("linear", p))
	    result = PRAGMA_OMP_CLAUSE_LINEAR;
	  وگرنه اگر (!strcmp ("link", p))
	    result = PRAGMA_OMP_CLAUSE_LINK;
	  وگرنه اگر (!strcmp ("local", p))
	    result = PRAGMA_OMP_CLAUSE_LOCAL;
	  بشکن;
	حالت 'm':
	  اگر (!strcmp ("map", p))
	    result = PRAGMA_OMP_CLAUSE_MAP;
	  وگرنه اگر (!strcmp ("mergeable", p))
	    result = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  بشکن;
	حالت 'n':
	  اگر (!strcmp ("no_create", p))
	    result = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  وگرنه اگر (!strcmp ("nocontext", p))
	    result = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  وگرنه اگر (!strcmp ("nogroup", p))
	    result = PRAGMA_OMP_CLAUSE_NOGROUP;
	  وگرنه اگر (!strcmp ("nohost", p))
	    result = PRAGMA_OACC_CLAUSE_NOHOST;
	  وگرنه اگر (!strcmp ("nontemporal", p))
	    result = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  وگرنه اگر (!strcmp ("notinbranch", p))
	    result = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  وگرنه اگر (!strcmp ("novariants", p))
	    result = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  وگرنه اگر (!strcmp ("nowait", p))
	    result = PRAGMA_OMP_CLAUSE_NOWAIT;
	  وگرنه اگر (!strcmp ("num_gangs", p))
	    result = PRAGMA_OACC_CLAUSE_رقم_GANGS;
	  وگرنه اگر (!strcmp ("num_tasks", p))
	    result = PRAGMA_OMP_CLAUSE_رقم_TASKS;
	  وگرنه اگر (!strcmp ("num_teams", p))
	    result = PRAGMA_OMP_CLAUSE_رقم_TEAMS;
	  وگرنه اگر (!strcmp ("num_threads", p))
	    result = PRAGMA_OMP_CLAUSE_رقم_THREADS;
	  وگرنه اگر (!strcmp ("num_workers", p))
	    result = PRAGMA_OACC_CLAUSE_رقم_WORKERS;
	  بشکن;
	حالت 'o':
	  اگر (!strcmp ("ordered", p))
	    result = PRAGMA_OMP_CLAUSE_ORDERED;
	  وگرنه اگر (!strcmp ("order", p))
	    result = PRAGMA_OMP_CLAUSE_ORDER;
	  بشکن;
	حالت 'p':
	  اگر (!strcmp ("parallel", p))
	    result = PRAGMA_OMP_CLAUSE_PARALLEL;
	  وگرنه اگر (!strcmp ("partial", p))
	    result = PRAGMA_OMP_CLAUSE_PARTIAL;
	  وگرنه اگر (!strcmp ("present", p))
	    result = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  وگرنه اگر (!strcmp ("present_or_copy", p)
		   || !strcmp ("pcopy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  وگرنه اگر (!strcmp ("present_or_copyin", p)
		   || !strcmp ("pcopyin", p))
	    result = PRAGMA_OACC_CLAUSE_COPYIN;
	  وگرنه اگر (!strcmp ("present_or_copyout", p)
		   || !strcmp ("pcopyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
	  وگرنه اگر (!strcmp ("present_or_create", p)
		   || !strcmp ("pcreate", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  وگرنه اگر (!strcmp ("priority", p))
	    result = PRAGMA_OMP_CLAUSE_PRIORITY;
	  وگرنه اگر (!strcmp ("private", p))
	    result = PRAGMA_OMP_CLAUSE_PRIVATE;
	  وگرنه اگر (!strcmp ("proc_bind", p))
	    result = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  بشکن;
	حالت 'r':
	  اگر (!strcmp ("reduction", p))
	    result = PRAGMA_OMP_CLAUSE_REDUCTION;
	  بشکن;
	حالت 's':
	  اگر (!strcmp ("safelen", p))
	    result = PRAGMA_OMP_CLAUSE_SAFELEN;
	  وگرنه اگر (!strcmp ("schedule", p))
	    result = PRAGMA_OMP_CLAUSE_SCHEDULE;
	  وگرنه اگر (!strcmp ("sections", p))
	    result = PRAGMA_OMP_CLAUSE_SECTIONS;
	  وگرنه اگر (!strcmp ("self", p))
	    result = PRAGMA_OACC_CLAUSE_SELF;
	  وگرنه اگر (!strcmp ("seq", p))
	    result = PRAGMA_OACC_CLAUSE_SEQ;
	  وگرنه اگر (!strcmp ("shared", p))
	    result = PRAGMA_OMP_CLAUSE_SHARED;
	  وگرنه اگر (!strcmp ("simd", p))
	    result = PRAGMA_OMP_CLAUSE_SIMD;
	  وگرنه اگر (!strcmp ("simdlen", p))
	    result = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  بشکن;
	حالت 't':
	  اگر (!strcmp ("task_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  وگرنه اگر (!strcmp ("taskgroup", p))
	    result = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  وگرنه اگر (!strcmp ("thread_limit", p))
	    result = PRAGMA_OMP_CLAUSE_THREAD_LIMIT;
	  وگرنه اگر (!strcmp ("threads", p))
	    result = PRAGMA_OMP_CLAUSE_THREADS;
	  وگرنه اگر (!strcmp ("tile", p))
	    result = PRAGMA_OACC_CLAUSE_TILE;
	  وگرنه اگر (!strcmp ("to", p))
	    result = PRAGMA_OMP_CLAUSE_TO;
	  بشکن;
	حالت 'u':
	  اگر (!strcmp ("uniform", p))
	    result = PRAGMA_OMP_CLAUSE_UNIFORM;
	  وگرنه اگر (!strcmp ("untied", p))
	    result = PRAGMA_OMP_CLAUSE_UNTIED;
	  وگرنه اگر (!strcmp ("use", p))
	    result = PRAGMA_OMP_CLAUSE_USE;
	  وگرنه اگر (!strcmp ("use_device", p))
	    result = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  وگرنه اگر (!strcmp ("use_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  وگرنه اگر (!strcmp ("use_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  وگرنه اگر (!strcmp ("uses_allocators", p))
	    result = PRAGMA_OMP_CLAUSE_USES_ALLOCATORS;
	  بشکن;
	حالت 'v':
	  اگر (!strcmp ("vector", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR;
	  وگرنه اگر (!strcmp ("vector_length", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR_LENGTH;
	  بشکن;
	حالت 'w':
	  اگر (!strcmp ("wait", p))
	    result = PRAGMA_OACC_CLAUSE_WAIT;
	  وگرنه اگر (!strcmp ("worker", p))
	    result = PRAGMA_OACC_CLAUSE_WORKER;
	  بشکن;
	}
    }

  اگر (result != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  بازگشت result;
}

/* Validate that a clause of the given type does not already exist.  */

ایستا تهی
check_no_duplicate_clause (درخت clauses, شمارش omp_clause_code code,
			   ثابت نویسه *name)
{
  اگر (درخت c = omp_find_clause (clauses, code))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

ایستا درخت
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, درخت list)
{
  vec<درخت, va_gc> *args;
  درخت t, args_درخت;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  args = c_parser_عبارت_list (parser, نادرست, درست, پوچ, پوچ, پوچ, پوچ);
  args_درخت = build_درخت_list_vec (args);

  برای (t = args_درخت; t; t = درخت_CHAIN (t))
    {
      درخت targ = درخت_مقدار (t);

      اگر (targ != error_mark_گره)
	{
	  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_گره;
	    }
	  وگرنه
	    {
	      درخت c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_درخت_vector (args);
  parens.require_close (parser);
  بازگشت list;
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

ساختار omp_dim
{
  درخت کم_bound, length;
  location_t loc;
  منطقی no_colon;
  omp_dim (درخت lb, درخت len, location_t lo, منطقی nc)
  : کم_bound (lb), length (len), loc (lo), no_colon (nc) {}
};

ایستا درخت
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    شمارش omp_clause_code kind, درخت list,
			    منطقی map_lvalue = نادرست)
{
  auto_vec<omp_dim> dims;
  منطقی array_section_p;
  auto_vec<c_token> tokens;
  unsigned صحیح tokens_avail = 0;
  c_token *saved_tokens = پوچ;

  وقتی (1)
    {
      درخت t = NULL_درخت;
      location_t tloc = c_parser_peek_token (parser)->location;

      اگر (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  اگر (c_parser_next_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
	    {
	      ساختار c_عبارت عبارت;
	      اگر (kind == OMP_CLAUSE_DEPEND
		  && c_parser_next_token_is_keyword (parser,
						     RID_OMP_ALL_MEMORY)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  عبارت.مقدار = ridpointers[RID_OMP_ALL_MEMORY];
		  c_parser_consume_token (parser);
		}
	      وگرنه
		عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	      اگر (عبارت.مقدار != error_mark_گره)
		{
		  درخت u = build_omp_clause (clause_loc, kind);
		  OMP_CLAUSE_DECL (u) = عبارت.مقدار;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      اگر (c_parser_next_token_is_not (parser, CPP_COMMA))
		بشکن;

	      c_parser_consume_token (parser);
	      ادامه;
	    }

	  tokens.truncate (0);
	  unsigned صحیح nesting_depth = 0;
	  وقتی (1)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      انتخاب (token->type)
		{
		حالت CPP_EOF:
		حالت CPP_PRAGMA_EOL:
		  بشکن;
		حالت CPP_OPEN_BRACE:
		حالت CPP_OPEN_PAREN:
		حالت CPP_OPEN_SQUARE:
		  ++nesting_depth;
		  برو add;
		حالت CPP_CLOSE_BRACE:
		حالت CPP_CLOSE_PAREN:
		حالت CPP_CLOSE_SQUARE:
		  اگر (nesting_depth-- == 0)
		    بشکن;
		  برو add;
		حالت CPP_COMMA:
		  اگر (nesting_depth == 0)
		    بشکن;
		  برو add;
		پیشفرض:
		add:
		  tokens.safe_افزودن (*token);
		  c_parser_consume_token (parser);
		  ادامه;
		}
	      بشکن;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  memset (&eof_token, 0, اندازه (eof_token));
	  eof_token.type = CPP_EOF;
	  tokens.safe_افزودن (eof_token);
	  tokens.safe_افزودن (eof_token);

	  saved_tokens = parser->tokens;
	  tokens_avail = parser->tokens_avail;
	  parser->tokens = tokens.address ();
	  parser->tokens_avail = tokens.length ();
	}
      وگرنه اگر (map_lvalue
	       && (kind == OMP_CLAUSE_MAP
		   || kind == OMP_CLAUSE_TO
		   || kind == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  منطقی save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = درست;
	  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	  اگر (عبارت.مقدار != error_mark_گره)
	    mark_exp_read (عبارت.مقدار);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  درخت decl = عبارت.مقدار;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  اگر (درخت_CODE (decl) == OMP_ARRAY_SECTION)
	    {
	      وقتی (درخت_CODE (decl) == OMP_ARRAY_SECTION)
		{
		  درخت کم_bound = درخت_OPERAND (decl, 1);
		  درخت length = درخت_OPERAND (decl, 2);
		  dims.safe_افزودن (omp_dim (کم_bound, length, loc, نادرست));
		  decl = درخت_OPERAND (decl, 0);
		}

	      وقتی (درخت_CODE (decl) == ARRAY_REF
		     || درخت_CODE (decl) == INDIRECT_REF
		     || درخت_CODE (decl) == COMPOUND_عبارت)
		{
		  اگر (درخت_CODE (decl) == COMPOUND_عبارت)
		    {
		      decl = درخت_OPERAND (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  وگرنه اگر (درخت_CODE (decl) == INDIRECT_REF)
		    {
		      dims.safe_افزودن (omp_dim (integer_zero_گره,
					       integer_one_گره, loc, درست));
		      decl = درخت_OPERAND (decl, 0);
		    }
		  وگرنه  /* ARRAY_REF. */
		    {
		      درخت index = درخت_OPERAND (decl, 1);
		      dims.safe_افزودن (omp_dim (index, integer_one_گره, loc,
					       درست));
		      decl = درخت_OPERAND (decl, 0);
		    }
		}

	      برای (صحیح i = dims.length () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].کم_bound,
						dims[i].length);
	    }
	  وگرنه اگر (درخت_CODE (decl) == INDIRECT_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = درخت_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_گره,
					      integer_one_گره);
	    }
	  وگرنه اگر (درخت_CODE (decl) == ARRAY_REF)
	    {
	      درخت idx = درخت_OPERAND (decl, 1);

	      decl = درخت_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_گره);
	    }
	  وگرنه اگر (درخت_CODE (decl) == NON_LVALUE_عبارت
		   || CONVERT_عبارت_P (decl))
	    decl = درخت_OPERAND (decl, 0);

	  درخت u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  برو next_item;
	}

      اگر (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->مقدار);

	  اگر (t == NULL_درخت)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->مقدار);
	      t = error_mark_گره;
	    }

	  c_parser_consume_token (parser);
	}
      وگرنه اگر (c_parser_next_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).مقدار;
      وگرنه
	{
	  c_parser_error (parser, "expected identifier");
	  بشکن;
	}

      اگر (t == error_mark_گره)
	;
      وگرنه اگر (kind != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  انتخاب (kind)
	    {
	    حالت OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      اگر (c_parser_peek_token (parser)->type != CPP_OPEN_SQUARE)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_گره;
		  بشکن;
		}
	      /* FALLTHROUGH  */
	    حالت OMP_CLAUSE_MAP:
	    حالت OMP_CLAUSE_FROM:
	    حالت OMP_CLAUSE_TO:
	    start_component_ref:
	      وقتی (c_parser_next_token_is (parser, CPP_DOT)
		     || c_parser_next_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  اگر (c_parser_next_token_is (parser, CPP_DEREF))
		    {
		      c_عبارت t_عبارت;
		      t_عبارت.مقدار = t;
		      t_عبارت.original_code = ERROR_MARK;
		      t_عبارت.original_type = پوچ;
		      set_c_عبارت_source_range (&t_عبارت, op_loc, op_loc);
		      t_عبارت.m_decimal = 0;
		      t_عبارت = convert_lvalue_to_rvalue (op_loc, t_عبارت,
							 درست, نادرست);
		      t = build_indirect_ref (op_loc, t_عبارت.مقدار, RO_ARROW);
		      arrow_loc = t_عبارت.get_location ();
		    }
		  c_parser_consume_token (parser);
		  اگر (!c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_گره;
		      بشکن;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  درخت ident = comp_tok->مقدار;
		  location_t comp_loc = comp_tok->location;
		  c_parser_consume_token (parser);
		  t = build_component_ref (op_loc, t, ident, comp_loc,
					   arrow_loc);
		}
	      /* FALLTHROUGH  */
	    حالت OMP_CLAUSE_AFFINITY:
	    حالت OMP_CLAUSE_DEPEND:
	    حالت OMP_CLAUSE_REDUCTION:
	    حالت OMP_CLAUSE_IN_REDUCTION:
	    حالت OMP_CLAUSE_TASK_REDUCTION:
	    حالت OMP_CLAUSE_HAS_DEVICE_ADDR:
	      array_section_p = نادرست;
	      dims.truncate (0);
	      وقتی (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  درخت کم_bound = NULL_درخت, length = NULL_درخت;
		  منطقی no_colon = نادرست;

		  c_parser_consume_token (parser);
		  اگر (!c_parser_next_token_is (parser, CPP_COLON))
		    {
		      location_t عبارت_loc
			= c_parser_peek_token (parser)->location;
		      c_عبارت عبارت = c_parser_expression (parser);
		      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت,
						       نادرست, درست);
		      کم_bound = عبارت.مقدار;
		      loc = عبارت_loc;
		    }
		  اگر (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    {
		      length = integer_one_گره;
		      no_colon = درست;
		    }
		  وگرنه
		    {
		      /* Look for `:'.  */
		      اگر (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_گره;
			  بشکن;
			}
		      array_section_p = درست;
		      اگر (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
			{
			  location_t عبارت_loc
			    = c_parser_peek_token (parser)->location;
			  c_عبارت عبارت = c_parser_expression (parser);
			  عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت,
							   نادرست, درست);
			  length = عبارت.مقدار;
			}
		    }
		  /* Look for the closing `]'.  */
		  اگر (!c_parser_require (parser, CPP_CLOSE_SQUARE,
					 "expected %<]%>"))
		    {
		      t = error_mark_گره;
		      بشکن;
		    }

		  dims.safe_افزودن (omp_dim (کم_bound, length, loc, no_colon));
		}

	      اگر (t != error_mark_گره)
		{
		  اگر ((kind == OMP_CLAUSE_MAP
		       || kind == OMP_CLAUSE_FROM
		       || kind == OMP_CLAUSE_TO)
		      && !array_section_p
		      && (c_parser_next_token_is (parser, CPP_DOT)
			  || c_parser_next_token_is (parser, CPP_DEREF)))
		    {
		      برای (unsigned i = 0; i < dims.length (); i++)
			{
			  gcc_assert (dims[i].length == integer_one_گره);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].کم_bound);
			}
		      برو start_component_ref;
		    }
		  وگرنه
		    برای (unsigned i = 0; i < dims.length (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].کم_bound,
						   dims[i].length);
		}

	      اگر ((kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_گره
		  && parser->tokens_avail != 2)
		{
		  اگر (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_گره;
		    }
		  وگرنه
		    {
		      parser->tokens = tokens.address ();
		      parser->tokens_avail = tokens.length ();

		      t = c_parser_عبارت_no_commas (parser, پوچ).مقدار;
		      اگر (t != error_mark_گره && parser->tokens_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_گره;
			}
		    }
		}
	      بشکن;
	    پیشفرض:
	      بشکن;
	    }

	  اگر (t != error_mark_گره)
	    {
	      درخت u = build_omp_clause (clause_loc, kind);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      وگرنه  /* kind == OMP_CLAUSE_ERROR */
	list = درخت_cons (t, build_empty_stmt (tloc), list);

      اگر (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}

    next_item:
      اگر (c_parser_next_token_is_not (parser, CPP_COMMA))
	بشکن;

      c_parser_consume_token (parser);
    }

  بازگشت list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

ایستا درخت
c_parser_omp_var_list_parens (c_parser *parser, شمارش omp_clause_code kind,
			      درخت list, منطقی map_lvalue = نادرست)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  اگر (parser->in_omp_decl_attribute)
    {
      اگر (kind)
	{
	  درخت u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = parser->in_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  بازگشت u;
	}
      وگرنه
	بازگشت درخت_cons (parser->in_omp_decl_attribute, NULL_درخت, list);
    }

  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, kind, list, map_lvalue);
      parens.skip_until_found_close (parser);
    }
  بازگشت list;
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

ایستا درخت
c_parser_oacc_data_clause (c_parser *parser, pragma_omp_clause c_kind,
			   درخت list)
{
  شمارش gomp_map_kind kind;
  انتخاب (c_kind)
    {
    حالت PRAGMA_OACC_CLAUSE_ATTACH:
      kind = GOMP_MAP_ATTACH;
      بشکن;
    حالت PRAGMA_OACC_CLAUSE_COPY:
      kind = GOMP_MAP_TOFROM;
      بشکن;
    حالت PRAGMA_OACC_CLAUSE_COPYIN:
      kind = GOMP_MAP_TO;
      بشکن;
    حالت PRAGMA_OACC_CLAUSE_COPYOUT:
      kind = GOMP_MAP_FROM;
      بشکن;
    حالت PRAGMA_OACC_CLAUSE_CREATE:
      kind = GOMP_MAP_ALLOC;
      بشکن;
    حالت PRAGMA_OACC_CLAUSE_DELETE:
      kind = GOMP_MAP_RELEASE;
      بشکن;
    حالت PRAGMA_OACC_CLAUSE_DETACH:
      kind = GOMP_MAP_DETACH;
      بشکن;
    حالت PRAGMA_OACC_CLAUSE_DEVICE:
      kind = GOMP_MAP_FORCE_TO;
      بشکن;
    حالت PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      kind = GOMP_MAP_DEVICE_RESIDENT;
      بشکن;
    حالت PRAGMA_OACC_CLAUSE_LINK:
      kind = GOMP_MAP_LINK;
      بشکن;
    حالت PRAGMA_OACC_CLAUSE_NO_CREATE:
      kind = GOMP_MAP_IF_PRESENT;
      بشکن;
    حالت PRAGMA_OACC_CLAUSE_PRESENT:
      kind = GOMP_MAP_FORCE_PRESENT;
      بشکن;
    حالت PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    حالت PRAGMA_OACC_CLAUSE_HOST:
      kind = GOMP_MAP_FORCE_FROM;
      بشکن;
    پیشفرض:
      gcc_unreachable ();
    }

  درخت nl = list;
  منطقی readonly = نادرست;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      اگر (c_kind == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  اگر (token->type == CPP_NAME
	      && !strcmp (IDENTIFIER_POINTER (token->مقدار), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = درست;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       نادرست);
      parens.skip_until_found_close (parser);
    }

  برای (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      اگر (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  بازگشت nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

ایستا درخت
c_parser_oacc_data_clause_deviceptr (c_parser *parser, درخت list)
{
  درخت vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, پوچ);
  برای (t = vars; t && t; t = درخت_CHAIN (t))
    {
      درخت v = درخت_PURPOSE (t);
      location_t loc = عبارت_LOCATION (درخت_مقدار (t));

      اگر (!VAR_P (v) && درخت_CODE (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      وگرنه اگر (درخت_TYPE (v) == error_mark_گره)
	;
      وگرنه اگر (!POINTER_TYPE_P (درخت_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      درخت u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  بازگشت list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

ایستا درخت
c_parser_omp_clause_collapse (c_parser *parser, درخت list)
{
  درخت c, رقم = error_mark_گره;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      رقم = c_parser_عبارت_no_commas (parser, پوچ).مقدار;
      parens.skip_until_found_close (parser);
    }
  اگر (رقم == error_mark_گره)
    بازگشت list;
  mark_exp_read (رقم);
  رقم = c_fully_fold (رقم, نادرست, پوچ);
  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (رقم))
      || !درخت_fits_shwi_p (رقم)
      || (n = درخت_to_shwi (رقم)) <= 0
      || (صحیح) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      بازگشت list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_عبارت (c) = رقم;
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

ایستا درخت
c_parser_omp_clause_copyin (c_parser *parser, درخت list)
{
  بازگشت c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

ایستا درخت
c_parser_omp_clause_copyprivate (c_parser *parser, درخت list)
{
  بازگشت c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

ایستا درخت
c_parser_omp_clause_default (c_parser *parser, درخت list, منطقی is_oacc)
{
  شمارش omp_clause_default_kind kind = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  درخت c;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;
  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);

      انتخاب (p[0])
	{
	حالت 'n':
	  اگر (strcmp ("none", p) != 0)
	    برو invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_NONE;
	  بشکن;

	حالت 'p':
	  اگر (is_oacc)
	    {
	      اگر (strcmp ("present", p) != 0)
		برو invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  وگرنه
	    {
	      اگر (strcmp ("private", p) != 0)
		برو invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRIVATE;
	    }
	  بشکن;

	حالت 'f':
	  اگر (strcmp ("firstprivate", p) != 0 || is_oacc)
	    برو invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  بشکن;

	حالت 's':
	  اگر (strcmp ("shared", p) != 0 || is_oacc)
	    برو invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_SHARED;
	  بشکن;

	پیشفرض:
	  برو invalid_kind;
	}

      c_parser_consume_token (parser);
    }
  وگرنه
    {
    invalid_kind:
      اگر (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      وگرنه
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_found_close (parser);

  اگر (kind == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    بازگشت list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_KIND (c) = kind;

  بازگشت c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

ایستا درخت
c_parser_omp_clause_firstprivate (c_parser *parser, درخت list)
{
  بازگشت c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

ایستا درخت
c_parser_omp_clause_final (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      درخت t, c;
      اگر (!parens.require_open (parser))
	t = error_mark_گره;
      وگرنه
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	  t = convert_lvalue_to_rvalue (eloc, عبارت, درست, درست).مقدار;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, نادرست, پوچ);
	  parens.skip_until_found_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_عبارت (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }
  وگرنه
    c_parser_error (parser, "expected %<(%>");

  بازگشت list;
}

/* OpenMP 5.1:
   indirect [( expression )]
*/

ایستا درخت
c_parser_omp_clause_indirect (c_parser *parser, درخت list)
{
  location_t location = c_parser_peek_token (parser)->location;
  درخت t;

  اگر (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      اگر (!parens.require_open (parser))
	بازگشت list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (loc, عبارت, درست, درست);
      t = c_objc_common_truthvalue_conversion (loc, عبارت.مقدار);
      t = c_fully_fold (t, نادرست, پوچ);
      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t))
	  || درخت_CODE (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  بازگشت list;
	}
      parens.skip_until_found_close (parser);
    }
  وگرنه
    t = integer_one_گره;

  check_no_duplicate_clause (list, OMP_CLAUSE_INDIRECT, "indirect");

  درخت c = build_omp_clause (location, OMP_CLAUSE_INDIRECT);
  OMP_CLAUSE_INDIRECT_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;

  بازگشت c;
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

ایستا درخت
c_parser_omp_clause_if (c_parser *parser, درخت list, منطقی is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  شمارش درخت_code if_modifier = ERROR_MARK;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  اگر (is_omp && c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      صحیح n = 2;
      اگر (strcmp (p, "cancel") == 0)
	if_modifier = VOID_CST;
      وگرنه اگر (strcmp (p, "parallel") == 0)
	if_modifier = OMP_PARALLEL;
      وگرنه اگر (strcmp (p, "simd") == 0)
	if_modifier = OMP_SIMD;
      وگرنه اگر (strcmp (p, "task") == 0)
	if_modifier = OMP_TASK;
      وگرنه اگر (strcmp (p, "taskloop") == 0)
	if_modifier = OMP_TASKLOOP;
      وگرنه اگر (strcmp (p, "target") == 0)
	{
	  if_modifier = OMP_TARGET;
	  اگر (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	    {
	      p = IDENTIFIER_POINTER (c_parser_peek_2nd_token (parser)->مقدار);
	      اگر (strcmp ("data", p) == 0)
		if_modifier = OMP_TARGET_DATA;
	      وگرنه اگر (strcmp ("update", p) == 0)
		if_modifier = OMP_TARGET_UPDATE;
	      وگرنه اگر (strcmp ("enter", p) == 0)
		if_modifier = OMP_TARGET_ENTER_DATA;
	      وگرنه اگر (strcmp ("exit", p) == 0)
		if_modifier = OMP_TARGET_EXIT_DATA;
	      اگر (if_modifier != OMP_TARGET)
		{
		  n = 3;
		  c_parser_consume_token (parser);
		}
	      وگرنه
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<data%>, %<update%>, %<enter%> "
				 "or %<exit%>");
		  if_modifier = ERROR_MARK;
		}
	      اگر (if_modifier == OMP_TARGET_ENTER_DATA
		  || if_modifier == OMP_TARGET_EXIT_DATA)
		{
		  اگر (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_POINTER
				(c_parser_peek_2nd_token (parser)->مقدار);
		      اگر (strcmp ("data", p) == 0)
			n = 4;
		    }
		  اگر (n == 4)
		    c_parser_consume_token (parser);
		  وگرنه
		    {
		      location_t loc
			= c_parser_peek_2nd_token (parser)->location;
		      error_at (loc, "expected %<data%>");
		      if_modifier = ERROR_MARK;
		    }
		}
	    }
	}
      اگر (if_modifier != ERROR_MARK)
	{
	  اگر (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  وگرنه
	    {
	      اگر (n > 2)
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<:%>");
		}
	      if_modifier = ERROR_MARK;
	    }
	}
    }

  location_t loc = c_parser_peek_token (parser)->location;
  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
  عبارت = convert_lvalue_to_rvalue (loc, عبارت, درست, درست);
  درخت t = c_objc_common_truthvalue_conversion (loc, عبارت.مقدار), c;
  t = c_fully_fold (t, نادرست, پوچ);
  parens.skip_until_found_close (parser);

  برای (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IF)
      {
	اگر (if_modifier != ERROR_MARK
	    && OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    ثابت نویسه *p = پوچ;
	    انتخاب (if_modifier)
	      {
	      حالت VOID_CST: p = "cancel"; بشکن;
	      حالت OMP_PARALLEL: p = "parallel"; بشکن;
	      حالت OMP_SIMD: p = "simd"; بشکن;
	      حالت OMP_TASK: p = "task"; بشکن;
	      حالت OMP_TASKLOOP: p = "taskloop"; بشکن;
	      حالت OMP_TARGET_DATA: p = "target data"; بشکن;
	      حالت OMP_TARGET: p = "target"; بشکن;
	      حالت OMP_TARGET_UPDATE: p = "target update"; بشکن;
	      حالت OMP_TARGET_ENTER_DATA: p = "target enter data"; بشکن;
	      حالت OMP_TARGET_EXIT_DATA: p = "target exit data"; بشکن;
	      پیشفرض: gcc_unreachable ();
	      }
	    error_at (location, "too many %<if%> clauses with %qs modifier",
		      p);
	    بازگشت list;
	  }
	وگرنه اگر (OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    اگر (!is_omp)
	      error_at (location, "too many %<if%> clauses");
	    وگرنه
	      error_at (location, "too many %<if%> clauses without modifier");
	    بازگشت list;
	  }
	وگرنه اگر (if_modifier == ERROR_MARK
		 || OMP_CLAUSE_IF_MODIFIER (c) == ERROR_MARK)
	  {
	    error_at (location, "if any %<if%> clause has modifier, then all "
				"%<if%> clauses have to use modifier");
	    بازگشت list;
	  }
      }

  c = build_omp_clause (location, OMP_CLAUSE_IF);
  OMP_CLAUSE_IF_MODIFIER (c) = if_modifier;
  OMP_CLAUSE_IF_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

ایستا درخت
c_parser_omp_clause_lastprivate (c_parser *parser, درخت list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  اگر (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      منطقی conditional = نادرست;
      اگر (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  ثابت نویسه *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
	  اگر (strcmp (p, "conditional") == 0)
	    {
	      conditional = درست;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      درخت nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      اگر (conditional)
	برای (درخت c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      بازگشت nlist;
    }
  بازگشت list;
}

/* OpenMP 3.1:
   mergeable */

ایستا درخت
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_UNUSED, درخت list)
{
  درخت c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  بازگشت c;
}

/* OpenMP 2.5:
   nowait */

ایستا درخت
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_UNUSED, درخت list)
{
  درخت c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

ایستا درخت
c_parser_omp_clause_رقم_threads (c_parser *parser, درخت list)
{
  location_t رقم_threads_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
      درخت c, t = عبارت.مقدار;
      t = c_fully_fold (t, نادرست, پوچ);

      parens.skip_until_found_close (parser);

      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  بازگشت list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (عبارت_loc, LE_عبارت, boolean_type_گره, t,
		       build_int_cst (درخت_TYPE (t), 0));
      protected_set_عبارت_location (c, عبارت_loc);
      اگر (c == boolean_true_گره)
	{
	  warning_at (عبارت_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_گره;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_رقم_THREADS, "num_threads");

      c = build_omp_clause (رقم_threads_loc, OMP_CLAUSE_رقم_THREADS);
      OMP_CLAUSE_رقم_THREADS_عبارت (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  بازگشت list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

ایستا درخت
c_parser_omp_clause_رقم_tasks (c_parser *parser, درخت list)
{
  location_t رقم_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      منطقی strict = نادرست;
      اگر (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار),
		     "strict") == 0)
	{
	  strict = درست;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
      درخت c, t = عبارت.مقدار;
      t = c_fully_fold (t, نادرست, پوچ);

      parens.skip_until_found_close (parser);

      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  بازگشت list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (عبارت_loc, LE_عبارت, boolean_type_گره, t,
			   build_int_cst (درخت_TYPE (t), 0));
      اگر (CAN_HAVE_LOCATION_P (c))
	SET_عبارت_LOCATION (c, عبارت_loc);
      اگر (c == boolean_true_گره)
	{
	  warning_at (عبارت_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_گره;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_رقم_TASKS, "num_tasks");

      c = build_omp_clause (رقم_tasks_loc, OMP_CLAUSE_رقم_TASKS);
      OMP_CLAUSE_رقم_TASKS_عبارت (c) = t;
      OMP_CLAUSE_رقم_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  بازگشت list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

ایستا درخت
c_parser_omp_clause_grainsize (c_parser *parser, درخت list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      منطقی strict = نادرست;
      اگر (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار),
		     "strict") == 0)
	{
	  strict = درست;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
      درخت c, t = عبارت.مقدار;
      t = c_fully_fold (t, نادرست, پوچ);

      parens.skip_until_found_close (parser);

      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  بازگشت list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (عبارت_loc, LE_عبارت, boolean_type_گره, t,
			   build_int_cst (درخت_TYPE (t), 0));
      اگر (CAN_HAVE_LOCATION_P (c))
	SET_عبارت_LOCATION (c, عبارت_loc);
      اگر (c == boolean_true_گره)
	{
	  warning_at (عبارت_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_گره;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_عبارت (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  بازگشت list;
}

/* OpenMP 4.5:
   priority ( expression ) */

ایستا درخت
c_parser_omp_clause_priority (c_parser *parser, درخت list)
{
  location_t priority_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
      درخت c, t = عبارت.مقدار;
      t = c_fully_fold (t, نادرست, پوچ);

      parens.skip_until_found_close (parser);

      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  بازگشت list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (عبارت_loc, LT_عبارت, boolean_type_گره, t,
			   build_int_cst (درخت_TYPE (t), 0));
      اگر (CAN_HAVE_LOCATION_P (c))
	SET_عبارت_LOCATION (c, عبارت_loc);
      اگر (c == boolean_true_گره)
	{
	  warning_at (عبارت_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_گره;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_PRIORITY, "priority");

      c = build_omp_clause (priority_loc, OMP_CLAUSE_PRIORITY);
      OMP_CLAUSE_PRIORITY_عبارت (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  بازگشت list;
}

/* OpenMP 4.5:
   hint ( expression ) */

ایستا درخت
c_parser_omp_clause_hint (c_parser *parser, درخت list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
      درخت c, t = عبارت.مقدار;
      t = c_fully_fold (t, نادرست, پوچ);
      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t))
	  || درخت_CODE (t) != INTEGER_CST
	  || درخت_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  بازگشت list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_عبارت (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  بازگشت list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

ایستا درخت
c_parser_omp_clause_filter (c_parser *parser, درخت list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
      درخت c, t = عبارت.مقدار;
      t = c_fully_fold (t, نادرست, پوچ);
      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  بازگشت list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_عبارت (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  بازگشت list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

ایستا درخت
c_parser_omp_clause_defaultmap (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت c;
  ثابت نویسه *p;
  شمارش omp_clause_defaultmap_kind behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  شمارش omp_clause_defaultmap_kind category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;
  اگر (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  وگرنه اگر (!c_parser_next_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      برو out_err;
    }
  وگرنه
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);

  انتخاب (p[0])
    {
    حالت 'a':
      اگر (strcmp ("alloc", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ALLOC;
      وگرنه
	برو invalid_behavior;
      بشکن;

    حالت 'd':
      اگر (strcmp ("default", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
      وگرنه
	برو invalid_behavior;
      بشکن;

    حالت 'f':
      اگر (strcmp ("firstprivate", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FIRSTPRIVATE;
      وگرنه اگر (strcmp ("from", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FROM;
      وگرنه
	برو invalid_behavior;
      بشکن;

    حالت 'n':
      اگر (strcmp ("none", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_NONE;
      وگرنه
	برو invalid_behavior;
      بشکن;

    حالت 'p':
      اگر (strcmp ("present", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_PRESENT;
      وگرنه
	برو invalid_behavior;
      بشکن;

    حالت 't':
      اگر (strcmp ("tofrom", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TOFROM;
      وگرنه اگر (strcmp ("to", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TO;
      وگرنه
	برو invalid_behavior;
      بشکن;

    پیشفرض:
      برو invalid_behavior;
    }
  c_parser_consume_token (parser);

  اگر (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	برو out_err;
      اگر (!c_parser_next_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  برو out_err;
	}
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      انتخاب (p[0])
	{
	حالت 'a':
	  اگر (strcmp ("aggregate", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE;
	  وگرنه اگر (strcmp ("all", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL;
	  وگرنه
	    برو invalid_category;
	  بشکن;

	حالت 'p':
	  اگر (strcmp ("pointer", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER;
	  وگرنه
	    برو invalid_category;
	  بشکن;

	حالت 's':
	  اگر (strcmp ("scalar", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR;
	  وگرنه
	    برو invalid_category;
	  بشکن;

	پیشفرض:
	  برو invalid_category;
	}

      c_parser_consume_token (parser);
    }
  parens.skip_until_found_close (parser);

  برای (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEFAULTMAP
	&& (category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
	    || OMP_CLAUSE_DEFAULTMAP_CATEGORY (c) == category
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL)))
      {
	شمارش omp_clause_defaultmap_kind cat = category;
	location_t loc = OMP_CLAUSE_LOCATION (c);
	اگر (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
		&& (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		    != OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)))
	  cat = OMP_CLAUSE_DEFAULTMAP_CATEGORY (c);
	p = پوچ;
	انتخاب (cat)
	  {
	  حالت OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED:
	    p = پوچ;
	    بشکن;
	  حالت OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL:
	    p = "all";
	    بشکن;
	  حالت OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE:
	    p = "aggregate";
	    بشکن;
	  حالت OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER:
	    p = "pointer";
	    بشکن;
	  حالت OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR:
	    p = "scalar";
	    بشکن;
	  پیشفرض:
	    gcc_unreachable ();
	  }
	اگر (p)
	  error_at (loc, "too many %<defaultmap%> clauses with %qs category",
		    p);
	وگرنه
	  error_at (loc, "too many %<defaultmap%> clauses with unspecified "
			 "category");
	بشکن;
      }

  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULTMAP);
  OMP_CLAUSE_DEFAULTMAP_SET_KIND (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;

 out_err:
  parens.skip_until_found_close (parser);
  بازگشت list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

ایستا درخت
c_parser_omp_clause_use_device_ptr (c_parser *parser, درخت list)
{
  بازگشت c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

ایستا درخت
c_parser_omp_clause_use_device_addr (c_parser *parser, درخت list)
{
  بازگشت c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

ایستا درخت
c_parser_omp_clause_has_device_addr (c_parser *parser, درخت list)
{
  بازگشت c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

ایستا درخت
c_parser_omp_clause_is_device_ptr (c_parser *parser, درخت list)
{
  بازگشت c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

ایستا درخت
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_code code,
				 درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  location_t عبارت_loc = c_parser_peek_token (parser)->location;
  c_عبارت عبارت = c_parser_expression (parser);
  عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
  درخت c, t = عبارت.مقدار;
  t = c_fully_fold (t, نادرست, پوچ);

  parens.skip_until_found_close (parser);

  اگر (t == error_mark_گره)
    بازگشت list;
  وگرنه اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
    {
      error_at (عبارت_loc, "%qs expression must be integral",
		omp_clause_code_name[code]);
      بازگشت list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (عبارت_loc, LE_عبارت, boolean_type_گره, t,
		       build_int_cst (درخت_TYPE (t), 0));
  protected_set_عبارت_location (c, عبارت_loc);
  اگر (c == boolean_true_گره)
    {
      warning_at (عبارت_loc, 0,
		  "%qs value must be positive",
		  omp_clause_code_name[code]);
      t = integer_one_گره;
    }

  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  c = build_omp_clause (loc, code);
  OMP_CLAUSE_OPERAND (c, 0) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
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

ایستا درخت
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_code kind,
			    ثابت نویسه *str, درخت list)
{
  ثابت نویسه *id = "num";
  درخت ops[2] = { NULL_درخت, NULL_درخت }, c;

  اگر (kind == OMP_CLAUSE_VECTOR)
    id = "length";

  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      انجامبده
	{
	  c_token *next = c_parser_peek_token (parser);
	  صحیح idx = 0;

	  /* Gang static argument.  */
	  اگر (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		برو cleanup_error;

	      idx = 1;
	      اگر (ops[idx] != NULL_درخت)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  برو cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      اگر (c_parser_next_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_گره;

		  اگر (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      ادامه;
		    }
		  وگرنه
		    بشکن;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  وگرنه اگر (c_parser_next_token_is (parser, CPP_NAME)
		   && strcmp (id, IDENTIFIER_POINTER (next->مقدار)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  اگر (ops[idx] != NULL_درخت)
	    {
	      c_parser_error (parser, "unexpected argument");
	      برو cleanup_error;
	    }

	  location_t عبارت_loc = c_parser_peek_token (parser)->location;
	  c_عبارت cexpr = c_parser_عبارت_no_commas (parser, پوچ);
	  cexpr = convert_lvalue_to_rvalue (عبارت_loc, cexpr, نادرست, درست);
	  درخت عبارت = cexpr.مقدار;
	  اگر (عبارت == error_mark_گره)
	    برو cleanup_error;

	  عبارت = c_fully_fold (عبارت, نادرست, پوچ);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (عبارت)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      بازگشت list;
	    }

	  درخت c = fold_build2_loc (عبارت_loc, LE_عبارت, boolean_type_گره, عبارت,
				    build_int_cst (درخت_TYPE (عبارت), 0));
	  اگر (c == boolean_true_گره)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      عبارت = integer_one_گره;
	    }

	  ops[idx] = عبارت;

	  اگر (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ادامه;
	    }
	  بشکن;
	}
      وقتی (1);

      اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	برو cleanup_error;
    }

  check_no_duplicate_clause (list, kind, str);

  c = build_omp_clause (loc, kind);

  اگر (ops[1])
    OMP_CLAUSE_OPERAND (c, 1) = ops[1];

  OMP_CLAUSE_OPERAND (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  بازگشت c;

 cleanup_error:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  بازگشت list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

ایستا درخت
c_parser_oacc_simple_clause (location_t loc, شمارش omp_clause_code code,
			     درخت list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  درخت c = build_omp_clause (loc, code);
  OMP_CLAUSE_CHAIN (c) = list;

  بازگشت c;
}

/* OpenACC:
   async [( int-expr )] */

ایستا درخت
c_parser_oacc_clause_async (c_parser *parser, درخت list)
{
  درخت c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_گره, GOMP_ASYNC_NOVAL);

  اگر (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_عبارت_no_commas (parser, پوچ).مقدار;
      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      وگرنه اگر (t == error_mark_گره
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	بازگشت list;
    }
  وگرنه
    t = c_fully_fold (t, نادرست, پوچ);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  بازگشت list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

ایستا درخت
c_parser_oacc_clause_tile (c_parser *parser, درخت list)
{
  درخت c, عبارت = error_mark_گره;
  location_t loc;
  درخت tile = NULL_درخت;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    بازگشت list;

  انجامبده
    {
      اگر (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	بازگشت list;

      اگر (c_parser_next_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  عبارت = integer_zero_گره;
	}
      وگرنه
	{
	  location_t عبارت_loc = c_parser_peek_token (parser)->location;
	  c_عبارت cexpr = c_parser_عبارت_no_commas (parser, پوچ);
	  cexpr = convert_lvalue_to_rvalue (عبارت_loc, cexpr, نادرست, درست);
	  عبارت = cexpr.مقدار;

	  اگر (عبارت == error_mark_گره)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      بازگشت list;
	    }

	  عبارت = c_fully_fold (عبارت, نادرست, پوچ);

	  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (عبارت))
	      || !درخت_fits_shwi_p (عبارت)
	      || درخت_to_shwi (عبارت) <= 0)
	    {
	      error_at (عبارت_loc, "%<tile%> argument needs positive"
			" integral constant");
	      عبارت = integer_zero_گره;
	    }
	}

      tile = درخت_cons (NULL_درخت, عبارت, tile);
    }
  وقتی (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN));

  /* Consume the trailing ')'.  */
  c_parser_consume_token (parser);

  c = build_omp_clause (loc, OMP_CLAUSE_TILE);
  tile = nreverse (tile);
  OMP_CLAUSE_TILE_LIST (c) = tile;
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
}

/* OpenACC:
   wait [( int-expr-list )] */

ایستا درخت
c_parser_oacc_clause_wait (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  اگر (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  وگرنه
    {
      درخت c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_گره, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  بازگشت list;
}

/* OpenACC 2.7:
   self [( expression )] */

ایستا درخت
c_parser_oacc_compute_clause_self (c_parser *parser, درخت list)
{
  درخت t;
  location_t location = c_parser_peek_token (parser)->location;
  اگر (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (loc, عبارت, درست, درست);
      t = c_objc_common_truthvalue_conversion (loc, عبارت.مقدار);
      t = c_fully_fold (t, نادرست, پوچ);
      parens.skip_until_found_close (parser);
    }
  وگرنه
    t = truthvalue_true_گره;

  برای (درخت c = list; c; c = OMP_CLAUSE_CHAIN (c))
    اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	بازگشت list;
      }

  درخت c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
}

/* OpenMP 5.0:
   order ( concurrent )

   OpenMP 5.1:
   order ( order-modifier : concurrent )

   order-modifier:
     reproducible
     unconstrained  */

ایستا درخت
c_parser_omp_clause_order (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت c;
  ثابت نویسه *p;
  منطقی unconstrained = نادرست;
  منطقی reproducible = نادرست;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;
  اگر (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp (p, "unconstrained") == 0)
	unconstrained = درست;
      وگرنه اگر (strcmp (p, "reproducible") == 0)
	reproducible = درست;
      وگرنه
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  برو out_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  اگر (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      برو out_err;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
  اگر (strcmp (p, "concurrent") != 0)
    {
      c_parser_error (parser, "expected %<concurrent%>");
      برو out_err;
    }
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDER, "order");
  c = build_omp_clause (loc, OMP_CLAUSE_ORDER);
  OMP_CLAUSE_ORDER_UNCONSTRAINED (c) = unconstrained;
  OMP_CLAUSE_ORDER_REPRODUCIBLE (c) = reproducible;
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;

 out_err:
  parens.skip_until_found_close (parser);
  بازگشت list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

ایستا درخت
c_parser_omp_clause_bind (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت c;
  ثابت نویسه *p;
  شمارش omp_clause_bind_kind kind = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;
  اگر (!c_parser_next_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_found_close (parser);
      بازگشت list;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
  اگر (strcmp (p, "teams") == 0)
    kind = OMP_CLAUSE_BIND_TEAMS;
  وگرنه اگر (strcmp (p, "parallel") == 0)
    kind = OMP_CLAUSE_BIND_PARALLEL;
  وگرنه اگر (strcmp (p, "thread") != 0)
    برو invalid;
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

ایستا درخت
c_parser_omp_clause_ordered (c_parser *parser, درخت list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  درخت c, رقم = NULL_درخت;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      رقم = c_parser_عبارت_no_commas (parser, پوچ).مقدار;
      parens.skip_until_found_close (parser);
    }
  اگر (رقم == error_mark_گره)
    بازگشت list;
  اگر (رقم)
    {
      mark_exp_read (رقم);
      رقم = c_fully_fold (رقم, نادرست, پوچ);
      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (رقم))
	  || !درخت_fits_shwi_p (رقم)
	  || (n = درخت_to_shwi (رقم)) <= 0
	  || (صحیح) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  بازگشت list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_عبارت (c) = رقم;
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

ایستا درخت
c_parser_omp_clause_private (c_parser *parser, درخت list)
{
  بازگشت c_parser_omp_var_list_parens (parser, OMP_CLAUSE_PRIVATE, list);
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

ایستا درخت
c_parser_omp_clause_reduction (c_parser *parser, شمارش omp_clause_code kind,
			       منطقی is_omp, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      منطقی task = نادرست;
      منطقی inscan = نادرست;
      شمارش درخت_code code = ERROR_MARK;
      درخت reduc_id = NULL_درخت;

      اگر (kind == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  اگر (c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  وگرنه اگر (c_parser_next_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      ثابت نویسه *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
	      اگر (strcmp (p, "task") == 0)
		task = درست;
	      وگرنه اگر (strcmp (p, "inscan") == 0)
		inscan = درست;
	      اگر (task || inscan)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		}
	    }
	}

      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_PLUS:
	  code = PLUS_عبارت;
	  بشکن;
	حالت CPP_MULT:
	  code = MULT_عبارت;
	  بشکن;
	حالت CPP_MINUS:
	  اگر (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.add_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  code = MINUS_عبارت;
	  بشکن;
	حالت CPP_AND:
	  code = BIT_AND_عبارت;
	  بشکن;
	حالت CPP_XOR:
	  code = BIT_XOR_عبارت;
	  بشکن;
	حالت CPP_OR:
	  code = BIT_IOR_عبارت;
	  بشکن;
	حالت CPP_AND_AND:
	  code = TRUTH_ANDIF_عبارت;
	  بشکن;
	حالت CPP_OR_OR:
	  code = TRUTH_ORIF_عبارت;
	  بشکن;
        حالت CPP_NAME:
	  {
	    ثابت نویسه *p
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
	    اگر (strcmp (p, "min") == 0)
	      {
		code = MIN_عبارت;
		بشکن;
	      }
	    اگر (strcmp (p, "max") == 0)
	      {
		code = MAX_عبارت;
		بشکن;
	      }
	    reduc_id = c_parser_peek_token (parser)->مقدار;
	    بشکن;
	  }
	پیشفرض:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
	  بازگشت list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (code, reduc_id);
      اگر (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  درخت nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, kind, list);
	  برای (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      درخت d = OMP_CLAUSE_DECL (c), type;
	      اگر (درخت_CODE (d) != OMP_ARRAY_SECTION)
		type = درخت_TYPE (d);
	      وگرنه
		{
		  صحیح cnt = 0;
		  درخت t;
		  برای (t = d;
		      درخت_CODE (t) == OMP_ARRAY_SECTION;
		      t = درخت_OPERAND (t, 0))
		    cnt++;
		  type = درخت_TYPE (t);
		  وقتی (cnt > 0)
		    {
		      اگر (درخت_CODE (type) != POINTER_TYPE
			  && درخت_CODE (type) != ARRAY_TYPE)
			بشکن;
		      type = درخت_TYPE (type);
		      cnt--;
		    }
		}
	      وقتی (درخت_CODE (type) == ARRAY_TYPE)
		type = درخت_TYPE (type);
	      OMP_CLAUSE_REDUCTION_CODE (c) = code;
	      اگر (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      وگرنه اگر (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      اگر (code == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || درخت_CODE (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_found_close (parser);
    }
  بازگشت list;
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

ایستا درخت
c_parser_omp_clause_schedule (c_parser *parser, درخت list)
{
  درخت c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  صحیح modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  c = build_omp_clause (loc, OMP_CLAUSE_SCHEDULE);

  location_t comma = UNKNOWN_LOCATION;
  وقتی (c_parser_next_token_is (parser, CPP_NAME))
    {
      درخت kind = c_parser_peek_token (parser)->مقدار;
      ثابت نویسه *p = IDENTIFIER_POINTER (kind);
      اگر (strcmp ("simd", p) == 0)
	OMP_CLAUSE_SCHEDULE_SIMD (c) = 1;
      وگرنه اگر (strcmp ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_MONOTONIC;
      وگرنه اگر (strcmp ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_NONMONOTONIC;
      وگرنه
	بشکن;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      اگر (nmodifiers++ == 0
	  && c_parser_next_token_is (parser, CPP_COMMA))
	{
	  comma = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	}
      وگرنه
	{
	  c_parser_require (parser, CPP_COLON, "expected %<:%>");
	  بشکن;
	}
    }
  اگر (comma != UNKNOWN_LOCATION)
    error_at (comma, "expected %<:%>");

  اگر ((modifiers & (OMP_CLAUSE_SCHEDULE_MONOTONIC
		    | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
      == (OMP_CLAUSE_SCHEDULE_MONOTONIC
	  | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      درخت kind = c_parser_peek_token (parser)->مقدار;
      ثابت نویسه *p = IDENTIFIER_POINTER (kind);

      انتخاب (p[0])
	{
	حالت 'd':
	  اگر (strcmp ("dynamic", p) != 0)
	    برو invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_DYNAMIC;
	  بشکن;

        حالت 'g':
	  اگر (strcmp ("guided", p) != 0)
	    برو invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_GUIDED;
	  بشکن;

	حالت 'r':
	  اگر (strcmp ("runtime", p) != 0)
	    برو invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_RUNTIME;
	  بشکن;

	پیشفرض:
	  برو invalid_kind;
	}
    }
  وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_STATIC;
  وگرنه اگر (c_parser_next_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_AUTO;
  وگرنه
    برو invalid_kind;

  c_parser_consume_token (parser);
  اگر (c_parser_next_token_is (parser, CPP_COMMA))
    {
      location_t here;
      c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (here, عبارت, نادرست, درست);
      t = عبارت.مقدار;
      t = c_fully_fold (t, نادرست, پوچ);

      اگر (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_RUNTIME)
	error_at (here, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      وگرنه اگر (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_AUTO)
	error_at (here,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      وگرنه اگر (درخت_CODE (درخت_TYPE (t)) == INTEGER_TYPE
	       || درخت_CODE (درخت_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  درخت s = fold_build2_loc (loc, LE_عبارت, boolean_type_گره, t,
				    build_int_cst (درخت_TYPE (t), 0));
	  protected_set_عبارت_location (s, loc);
	  اگر (s == boolean_true_گره)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_گره;
	    }
	  OMP_CLAUSE_SCHEDULE_CHUNK_عبارت (c) = t;
	}
      وگرنه
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_found_close (parser);
    }
  وگرنه
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_SCHEDULE_KIND (c)
    = (شمارش omp_clause_schedule_kind)
      (OMP_CLAUSE_SCHEDULE_KIND (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_SCHEDULE, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;

 invalid_kind:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  بازگشت list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

ایستا درخت
c_parser_omp_clause_shared (c_parser *parser, درخت list)
{
  بازگشت c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

ایستا درخت
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_UNUSED, درخت list)
{
  درخت c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_UNTIED, "untied");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_UNTIED);
  OMP_CLAUSE_CHAIN (c) = list;

  بازگشت c;
}

/* OpenMP 4.0:
   inbranch
   notinbranch */

ایستا درخت
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_UNUSED,
			    شمارش omp_clause_code code, درخت list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  درخت c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  بازگشت c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

ایستا درخت
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_UNUSED,
				شمارش omp_clause_code code, درخت list)
{
  درخت c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  بازگشت c;
}

/* OpenMP 4.5:
   nogroup */

ایستا درخت
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_UNUSED, درخت list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  درخت c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
}

/* OpenMP 4.5:
   simd
   threads */

ایستا درخت
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_UNUSED,
				 شمارش omp_clause_code code, درخت list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);
  درخت c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

ایستا درخت
c_parser_omp_clause_رقم_teams (c_parser *parser, درخت list)
{
  location_t رقم_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      location_t upper_loc = c_parser_peek_token (parser)->location;
      location_t lower_loc = UNKNOWN_LOCATION;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (upper_loc, عبارت, نادرست, درست);
      درخت c, upper = عبارت.مقدار, lower = NULL_درخت;
      upper = c_fully_fold (upper, نادرست, پوچ);

      اگر (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  lower_loc = upper_loc;
	  lower = upper;
	  upper_loc = c_parser_peek_token (parser)->location;
	  عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	  عبارت = convert_lvalue_to_rvalue (upper_loc, عبارت, نادرست, درست);
	  upper = عبارت.مقدار;
	  upper = c_fully_fold (upper, نادرست, پوچ);
	}

      parens.skip_until_found_close (parser);

      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (upper))
	  || (lower && !INTEGRAL_TYPE_P (درخت_TYPE (lower))))
	{
	  c_parser_error (parser, "expected integer expression");
	  بازگشت list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (upper_loc, LE_عبارت, boolean_type_گره, upper,
			   build_int_cst (درخت_TYPE (upper), 0));
      protected_set_عبارت_location (c, upper_loc);
      اگر (c == boolean_true_گره)
	{
	  warning_at (upper_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  upper = integer_one_گره;
	}
      اگر (lower)
	{
	  c = fold_build2_loc (lower_loc, LE_عبارت, boolean_type_گره, lower,
			       build_int_cst (درخت_TYPE (lower), 0));
	  protected_set_عبارت_location (c, lower_loc);
	  اگر (c == boolean_true_گره)
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      lower = NULL_درخت;
	    }
	  وگرنه اگر (درخت_CODE (lower) == INTEGER_CST
		   && درخت_CODE (upper) == INTEGER_CST
		   && درخت_int_cst_lt (upper, lower))
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", lower, upper);
	      lower = NULL_درخت;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_رقم_TEAMS, "num_teams");

      c = build_omp_clause (رقم_teams_loc, OMP_CLAUSE_رقم_TEAMS);
      OMP_CLAUSE_رقم_TEAMS_UPPER_عبارت (c) = upper;
      OMP_CLAUSE_رقم_TEAMS_LOWER_عبارت (c) = lower;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  بازگشت list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

ایستا درخت
c_parser_omp_clause_thread_limit (c_parser *parser, درخت list)
{
  location_t رقم_thread_limit_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
      درخت c, t = عبارت.مقدار;
      t = c_fully_fold (t, نادرست, پوچ);

      parens.skip_until_found_close (parser);

      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  بازگشت list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (عبارت_loc, LE_عبارت, boolean_type_گره, t,
			   build_int_cst (درخت_TYPE (t), 0));
      protected_set_عبارت_location (c, عبارت_loc);
      اگر (c == boolean_true_گره)
	{
	  warning_at (عبارت_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_گره;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_LIMIT,
				 "thread_limit");

      c = build_omp_clause (رقم_thread_limit_loc, OMP_CLAUSE_THREAD_LIMIT);
      OMP_CLAUSE_THREAD_LIMIT_عبارت (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  بازگشت list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

ایستا درخت
c_parser_omp_clause_aligned (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl, c;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  اگر (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
      درخت alignment = عبارت.مقدار;
      alignment = c_fully_fold (alignment, نادرست, پوچ);
      اگر (درخت_CODE (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (درخت_TYPE (alignment))
	  || درخت_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_درخت;
	}

      برای (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_found_close (parser);
  بازگشت nl;
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

ایستا درخت
c_parser_omp_clause_allocate (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl, c;
  درخت allocator = NULL_درخت;
  درخت align = NULL_درخت;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  اگر ((c_parser_next_token_is_not (parser, CPP_NAME)
       && c_parser_next_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      منطقی has_modifiers = نادرست;
      درخت orig_type = NULL_درخت;
      اگر (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  unsigned صحیح n = 3;
	  ثابت نویسه *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
	  اگر ((strcmp (p, "allocator") == 0 || strcmp (p, "align") == 0)
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      اگر (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = درست;
	      وگرنه اگر (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  ثابت نویسه *q = IDENTIFIER_POINTER (tok->مقدار);
		  n += 4;
		  اگر ((strcmp (q, "allocator") == 0
		       || strcmp (q, "align") == 0)
		      && c_parser_check_balanced_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = درست;
		}
	    }
	  اگر (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t عبارت_loc = c_parser_peek_token (parser)->location;
	      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
	      اگر (عبارت.مقدار == error_mark_گره)
		;
	      وگرنه اگر (strcmp (p, "allocator") == 0)
		{
		  allocator = عبارت.مقدار;
		  allocator = c_fully_fold (allocator, نادرست, پوچ);
		  orig_type = عبارت.original_type
			      ? عبارت.original_type : درخت_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      وگرنه
		{
		  align = عبارت.مقدار;
		  align = c_fully_fold (align, نادرست, پوچ);
		}
	      parens2.skip_until_found_close (parser);
	      اگر (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  ثابت نویسه *q = "";
		  اگر (c_parser_next_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_POINTER (tok->مقدار);
		  اگر (strcmp (q, "allocator") != 0 && strcmp (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_found_close (parser);
		      بازگشت list;
		    }
		  وگرنه اگر (strcmp (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_found_close (parser);
		      بازگشت list;
		    }
		  c_parser_consume_token (parser);
		  اگر (!parens2.require_open (parser))
		    {
		      parens.skip_until_found_close (parser);
		      بازگشت list;
		    }
		  عبارت_loc = c_parser_peek_token (parser)->location;
		  عبارت = c_parser_عبارت_no_commas (parser, پوچ);
		  عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست,
						   درست);
		  اگر (strcmp (q, "allocator") == 0)
		    {
		      allocator = عبارت.مقدار;
		      allocator = c_fully_fold (allocator, نادرست, پوچ);
		      orig_type = عبارت.original_type
				  ? عبارت.original_type : درخت_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  وگرنه
		    {
		      align = عبارت.مقدار;
		      align = c_fully_fold (align, نادرست, پوچ);
		    }
		  parens2.skip_until_found_close (parser);
		}
	    }
	}
      اگر (!has_modifiers)
	{
	  location_t عبارت_loc = c_parser_peek_token (parser)->location;
	  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	  عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
	  اگر (عبارت.مقدار != error_mark_گره)
	    {
	      allocator = عبارت.مقدار;
	      allocator = c_fully_fold (allocator, نادرست, پوچ);
	      orig_type = عبارت.original_type
			  ? عبارت.original_type : درخت_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      اگر (allocator
	  && (!INTEGRAL_TYPE_P (درخت_TYPE (allocator))
	      || درخت_CODE (orig_type) != ENUMERAL_TYPE
	      || (TYPE_NAME (orig_type)
		  != get_identifier ("omp_allocator_handle_t"))))
        {
          error_at (clause_loc, "%<allocate%> clause allocator expression "
				"has type %qT rather than "
				"%<omp_allocator_handle_t%>",
				درخت_TYPE (allocator));
          allocator = NULL_درخت;
        }
      اگر (align
	  && (!INTEGRAL_TYPE_P (درخت_TYPE (align))
	      || !درخت_fits_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_درخت;
	}
      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_found_close (parser);
	  بازگشت list;
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALLOCATE, list);

  اگر (allocator || align)
    برای (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      {
	OMP_CLAUSE_ALLOCATE_ALLOCATOR (c) = allocator;
	OMP_CLAUSE_ALLOCATE_ALIGN (c) = align;
      }

  parens.skip_until_found_close (parser);
  بازگشت nl;
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

ایستا درخت
c_parser_omp_clause_uses_allocators (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl = list;
  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

parse_next:

  منطقی has_modifiers = نادرست;
  منطقی seen_allocators = نادرست;
  درخت memspace_عبارت = NULL_درخت;
  درخت traits_var = NULL_درخت;

  اگر (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      unsigned صحیح n = 3;
      ثابت نویسه *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر ((strcmp (p, "traits") == 0 || strcmp (p, "memspace") == 0)
	  && c_parser_check_balanced_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  اگر (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = درست;
	  وگرنه اگر (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      ثابت نویسه *q = IDENTIFIER_POINTER (tok->مقدار);
	      n += 4;
	      اگر ((strcmp (q, "traits") == 0
		   || strcmp (q, "memspace") == 0)
		  && c_parser_check_balanced_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  اگر (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = درست;
		  اگر ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      ثابت نویسه *m = IDENTIFIER_POINTER (tok->مقدار);
		      اگر (strcmp (p, m) == 0 || strcmp (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  برو end;
			}
		    }
		}
	    }
	}
      اگر (has_modifiers)
	{
	  c_parser_consume_token (parser);
	  matching_parens parens2;
	  parens2.require_open (parser);
	  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	  اگر (عبارت.مقدار == error_mark_گره)
	    ;
	  وگرنه اگر (strcmp (p, "traits") == 0)
	    {
	      traits_var = عبارت.مقدار;
	      traits_var = c_fully_fold (traits_var, نادرست, پوچ);
	      mark_exp_read (traits_var);
	    }
	  وگرنه
	    {
	      memspace_عبارت = عبارت.مقدار;
	      memspace_عبارت = c_fully_fold (memspace_عبارت, نادرست, پوچ);
	    }
	  parens2.skip_until_found_close (parser);
	  اگر (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      ثابت نویسه *q = "";
	      اگر (c_parser_next_token_is (parser, CPP_NAME))
		q = IDENTIFIER_POINTER (tok->مقدار);
	      اگر (strcmp (q, "traits") != 0 && strcmp (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_found_close (parser);
		  بازگشت list;
		}
	      وگرنه اگر (strcmp (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_found_close (parser);
		  بازگشت list;
		}
	      c_parser_consume_token (parser);
	      اگر (!parens2.require_open (parser))
		{
		  parens.skip_until_found_close (parser);
		  بازگشت list;
		}
	      عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	      اگر (strcmp (q, "traits") == 0)
		{
		  traits_var = عبارت.مقدار;
		  traits_var = c_fully_fold (traits_var, نادرست, پوچ);
		  mark_exp_read (traits_var);
		}
	      وگرنه
		{
		  memspace_عبارت = عبارت.مقدار;
		  memspace_عبارت = c_fully_fold (memspace_عبارت, نادرست, پوچ);
		}
	      parens2.skip_until_found_close (parser);
	    }
	  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    برو end;
	}
    }

  وقتی (c_parser_next_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      ثابت نویسه *tok_s = IDENTIFIER_POINTER (tok->مقدار);
      درخت t = lookup_name (tok->مقدار);
      اگر (t == NULL_درخت)
	{
	  undeclared_variable (tok->location, tok->مقدار);
	  t = error_mark_گره;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      درخت legacy_traits = NULL_درخت;
      اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  ثابت نویسه *tok_a
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
	  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_found_close (parser);

	  اگر (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      برو end;
	    }
	  legacy_traits = c_fully_fold (عبارت.مقدار, نادرست, پوچ);
	  اگر (legacy_traits == error_mark_گره)
	    برو end;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  اگر (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.add_fixit_replace (alloc_loc, "traits");
	      richloc.add_fixit_درج_after (close_loc, ": ");
	      richloc.add_fixit_درج_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      اگر (seen_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  برو end;
	}
      seen_allocators = درست;

      درخت c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_USES_ALLOCATORS);
      OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c) = memspace_عبارت;
      OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      اگر (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وگرنه
	بشکن;
    }

  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      برو parse_next;
    }

 end:
  parens.skip_until_found_close (parser);
  بازگشت nl;
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

ایستا درخت
c_parser_omp_clause_linear (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  درخت nl, c, step;
  شمارش omp_clause_linear_kind kind = OMP_CLAUSE_LINEAR_DEFAULT;
  منطقی old_linear_modifier = نادرست;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      ثابت نویسه *p = IDENTIFIER_POINTER (tok->مقدار);
      اگر (strcmp ("val", p) == 0)
	kind = OMP_CLAUSE_LINEAR_VAL;
      اگر (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	kind = OMP_CLAUSE_LINEAR_DEFAULT;
      اگر (kind != OMP_CLAUSE_LINEAR_DEFAULT)
	{
	  old_linear_modifier = درست;
	  rm1_loc = make_location (tok->location, tok->location,
				   c_parser_peek_2nd_token (parser)->location);
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_LINEAR, list);

  اگر (kind != OMP_CLAUSE_LINEAR_DEFAULT)
    {
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
    }

  اگر (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = عبارت_loc;
      منطقی has_modifiers = نادرست;
      اگر (kind == OMP_CLAUSE_LINEAR_DEFAULT
	  && c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  ثابت نویسه *p = IDENTIFIER_POINTER (tok->مقدار);
	  unsigned صحیح pos = 0;
	  اگر (strcmp ("val", p) == 0)
	    pos = 2;
	  وگرنه اگر (strcmp ("step", p) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      pos = 3;
	      اگر (c_parser_check_balanced_raw_token_sequence (parser, &pos)
		  && (c_parser_peek_nth_token_raw (parser, pos)->type
		      == CPP_CLOSE_PAREN))
		++pos;
	      وگرنه
		pos = 0;
	    }
	  اگر (pos)
	    {
	      tok = c_parser_peek_nth_token_raw (parser, pos);
	      اگر (tok->type == CPP_COMMA || tok->type == CPP_CLOSE_PAREN)
		has_modifiers = درست;
	    }
	}
      اگر (has_modifiers)
	{
	  step = NULL_درخت;
	  وقتی (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      ثابت نویسه *p = IDENTIFIER_POINTER (tok->مقدار);
	      اگر (strcmp ("val", p) == 0)
		{
		  اگر (kind != OMP_CLAUSE_LINEAR_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  kind = OMP_CLAUSE_LINEAR_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      وگرنه اگر (strcmp ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  اگر (parens2.require_open (parser))
		    {
		      اگر (step)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      عبارت_loc = c_parser_peek_token (parser)->location;
		      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
		      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست,
						       درست);
		      step = c_fully_fold (عبارت.مقدار, نادرست, پوچ);
		      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (step)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  step = integer_one_گره;
			}
		      parens2.skip_until_found_close (parser);
		    }
		  وگرنه
		    بشکن;
		}
	      وگرنه
		بشکن;
	      اگر (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ادامه;
		}
	      بشکن;
	    }
	  اگر (!step)
	    step = integer_one_گره;
	}
      وگرنه
	{
	  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	  عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
	  step = c_fully_fold (عبارت.مقدار, نادرست, پوچ);
	  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (step)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      step = integer_one_گره;
	    }
	}

    }
  وگرنه
    step = integer_one_گره;

  برای (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_LINEAR_STEP (c) = step;
      OMP_CLAUSE_LINEAR_KIND (c) = kind;
      OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c) = old_linear_modifier;
    }

  اگر (old_linear_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      اگر (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_remove (rm1_loc);
	  اگر (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.add_fixit_remove (rm2_loc);
	      richloc.add_fixit_درج_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.add_fixit_درج_before (close_loc, ")");
	    }
	  وگرنه
	    richloc.add_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_found_close (parser);
  بازگشت nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

ایستا درخت
c_parser_omp_clause_nontemporal (c_parser *parser, درخت list)
{
  بازگشت c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

ایستا درخت
c_parser_omp_clause_safelen (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت c, t;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  location_t عبارت_loc = c_parser_peek_token (parser)->location;
  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
  عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
  t = عبارت.مقدار;
  t = c_fully_fold (t, نادرست, پوچ);
  اگر (درخت_CODE (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (درخت_TYPE (t))
      || درخت_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_درخت;
    }

  parens.skip_until_found_close (parser);
  اگر (t == NULL_درخت || t == error_mark_گره)
    بازگشت list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

ایستا درخت
c_parser_omp_clause_simdlen (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت c, t = NULL_درخت, type = NULL_درخت, مقسوم_علیه = NULL_درخت;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  unsigned pos = 3;
  اگر (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار),
		 "scaled") == 0
      && c_parser_check_balanced_raw_token_sequence (parser, &pos)
      && c_parser_peek_nth_token_raw (parser, ++pos)->type == CPP_COLON)
    {
      c_parser_consume_token (parser);
      matching_parens parens2;
      parens2.require_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      ساختار c_type_name *ctype = c_parser_type_name (parser);
      اگر (ctype == پوچ
	  || (type = groktypename (ctype, پوچ, پوچ)) == پوچ
	  || (!INTEGRAL_TYPE_P (type)
	      && !SCALAR_FLOAT_TYPE_P (type)
	      && درخت_CODE (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_گره;
	}
      وگرنه اگر (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	  عبارت = convert_lvalue_to_rvalue (loc, عبارت, نادرست, درست);
	  مقسوم_علیه = عبارت.مقدار;
	  مقسوم_علیه = c_fully_fold (مقسوم_علیه, نادرست, پوچ);
	  اگر (درخت_CODE (مقسوم_علیه) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (درخت_TYPE (مقسوم_علیه))
	      || درخت_int_cst_sgn (مقسوم_علیه) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_گره;
	    }
	}
      parens2.skip_until_found_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  اگر (type != error_mark_گره)
    {
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
      t = عبارت.مقدار;
      t = c_fully_fold (t, نادرست, پوچ);
      اگر (درخت_CODE (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (درخت_TYPE (t))
	  || درخت_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_درخت;
	}
    }

  parens.skip_until_found_close (parser);
  اگر (type == error_mark_گره || t == NULL_درخت || t == error_mark_گره)
    بازگشت list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_عبارت (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_مقسوم_علیه (c) = مقسوم_علیه;
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

ایستا درخت
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   درخت list, منطقی depend_p)
{
  درخت vec = پوچ;
  اگر (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      بازگشت list;
    }

  اگر (!depend_p)
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_عدد
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  درخت val = c_parser_peek_nth_token (parser, 3)->مقدار;
	  اگر (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      درخت u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      بازگشت u;
	    }
	}
    }



  وقتی (c_parser_next_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_kind == C_ID_ID)
    {
      درخت t = lookup_name (c_parser_peek_token (parser)->مقدار);
      درخت addend = پوچ;

      اگر (t == NULL_درخت)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->مقدار);
	  t = error_mark_گره;
	}

      c_parser_consume_token (parser);

      منطقی neg = نادرست;
      اگر (c_parser_next_token_is (parser, CPP_MINUS))
	neg = درست;
      وگرنه اگر (!c_parser_next_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_گره;
	  neg = نادرست;
	  برو add_to_vector;
	}
      c_parser_consume_token (parser);

      اگر (c_parser_next_token_is_not (parser, CPP_عدد))
	{
	  c_parser_error (parser, "expected integer");
	  بازگشت list;
	}

      addend = c_parser_peek_token (parser)->مقدار;
      اگر (درخت_CODE (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  بازگشت list;
	}
      c_parser_consume_token (parser);

    add_to_vector:
      اگر (t != error_mark_گره)
	{
	  vec = درخت_cons (addend, t, vec);
	  اگر (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      اگر (c_parser_next_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_kind != C_ID_ID)
	بشکن;

      c_parser_consume_token (parser);
    }

  اگر (vec == NULL_درخت)
    بازگشت list;

  درخت u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
  OMP_CLAUSE_DOACROSS_DEPEND (u) = depend_p;
  OMP_CLAUSE_DECL (u) = nreverse (vec);
  OMP_CLAUSE_CHAIN (u) = list;
  بازگشت u;
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

ایستا درخت
c_parser_omp_iterators (c_parser *parser)
{
  درخت ret = NULL_درخت, *last = &ret;
  c_parser_consume_token (parser);

  افزودن_scope ();

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت error_mark_گره;

  انجامبده
    {
      درخت iter_type = NULL_درخت, type_عبارت = NULL_درخت;
      اگر (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
	{
	  ساختار c_type_name *type = c_parser_type_name (parser);
	  اگر (type != پوچ)
	    iter_type = groktypename (type, &type_عبارت, پوچ);
	}
      اگر (iter_type == NULL_درخت)
	iter_type = integer_type_گره;

      location_t loc = c_parser_peek_token (parser)->location;
      اگر (!c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  بشکن;
	}

      درخت id = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);

      اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	بشکن;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (eloc, عبارت, درست, نادرست);
      درخت begin = عبارت.مقدار;

      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	بشکن;

      eloc = c_parser_peek_token (parser)->location;
      عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (eloc, عبارت, درست, نادرست);
      درخت end = عبارت.مقدار;

      درخت step = integer_one_گره;
      اگر (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	  عبارت = convert_lvalue_to_rvalue (eloc, عبارت, درست, نادرست);
	  step = عبارت.مقدار;
	}

      درخت iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *last = make_omp_iterator ();
      OMP_ITERATOR_VAR (*last) = iter_var;
      OMP_ITERATOR_BEGIN (*last) = begin;
      OMP_ITERATOR_END (*last) = end;
      OMP_ITERATOR_STEP (*last) = step;
      last = &درخت_CHAIN (*last);

      اگر (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  ادامه;
	}
      بشکن;
    }
  وقتی (1);

  parens.skip_until_found_close (parser);
  بازگشت ret ? ret : error_mark_گره;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

ایستا درخت
c_parser_omp_clause_affinity (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl, iterators = NULL_درخت;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      منطقی parse_iter = ((strcmp ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      اگر (parse_iter)
	{
	  unsigned n = 3;
	  parse_iter = (c_parser_check_balanced_raw_token_sequence (parser, &n)
			&& (c_parser_peek_nth_token_raw (parser, n)->type
			    == CPP_CLOSE_PAREN)
			&& (c_parser_peek_nth_token_raw (parser, n + 1)->type
			    == CPP_COLON));
	}
      اگر (parse_iter)
	{
	  iterators = c_parser_omp_iterators (parser);
	  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    {
	      اگر (iterators)
		برداشت_scope ();
	      parens.skip_until_found_close (parser);
	      بازگشت list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  اگر (iterators)
    {
      درخت block = برداشت_scope ();
      اگر (iterators != error_mark_گره)
	{
	  OMP_ITERATOR_BLOCK (iterators) = block;
	  برای (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_درخت_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  بازگشت nl;
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

ایستا درخت
c_parser_omp_clause_depend (c_parser *parser, درخت list, location_t here)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  شمارش omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_LAST;
  شمارش omp_clause_doacross_kind dkind = OMP_CLAUSE_DOACROSS_LAST;
  درخت nl, c, iterators = NULL_درخت;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  انجامبده
    {
      اگر (c_parser_next_token_is_not (parser, CPP_NAME))
	برو invalid_kind;

      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp ("iterator", p) == 0 && iterators == NULL_درخت)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  ادامه;
	}
      اگر (strcmp ("in", p) == 0)
	kind = OMP_CLAUSE_DEPEND_IN;
      وگرنه اگر (strcmp ("inout", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUT;
      وگرنه اگر (strcmp ("inoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUTSET;
      وگرنه اگر (strcmp ("mutexinoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      وگرنه اگر (strcmp ("out", p) == 0)
	kind = OMP_CLAUSE_DEPEND_OUT;
      وگرنه اگر (strcmp ("depobj", p) == 0)
	kind = OMP_CLAUSE_DEPEND_DEPOBJ;
      وگرنه اگر (strcmp ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      وگرنه اگر (strcmp ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SOURCE;
	}
      وگرنه
	برو invalid_kind;
      بشکن;
    }
  وقتی (1);

  c_parser_consume_token (parser);

  اگر (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_SOURCE
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      برداشت_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_SOURCE ? "source" : "sink");
      iterators = NULL_درخت;
    }

  اگر (dkind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_درخت;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_found_close (parser);
      بازگشت c;
    }

  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    برو resync_fail;

  اگر (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, درست);
  وگرنه
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      اگر (iterators)
	{
	  درخت block = برداشت_scope ();
	  اگر (iterators == error_mark_گره)
	    iterators = NULL_درخت;
	  وگرنه
	    OMP_ITERATOR_BLOCK (iterators) = block;
	}

      برای (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_KIND (c) = kind;
	  اگر (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_درخت_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  بازگشت nl;

 invalid_kind:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  اگر (iterators)
    برداشت_scope ();
  بازگشت list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

ایستا درخت
c_parser_omp_clause_doacross (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  شمارش omp_clause_doacross_kind kind = OMP_CLAUSE_DOACROSS_LAST;
  درخت nl;
  ثابت نویسه *p;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  اگر (c_parser_next_token_is_not (parser, CPP_NAME))
    برو invalid_kind;

  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
  اگر (strcmp ("sink", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SINK;
  وگرنه اگر (strcmp ("source", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SOURCE;
  وگرنه
    برو invalid_kind;

  c_parser_consume_token (parser);

  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    برو resync_fail;

  اگر (kind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      اگر (c_parser_next_token_is (parser, CPP_NAME)
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (nl) = OMP_CLAUSE_DOACROSS_SOURCE;
      OMP_CLAUSE_DECL (nl) = NULL_درخت;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  وگرنه
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, نادرست);

  parens.skip_until_found_close (parser);
  بازگشت nl;

 invalid_kind:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  بازگشت list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

ایستا درخت
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  شمارش omp_clause_fallback_kind kind = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  unsigned n = 3;
  اگر (c_parser_next_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  بازگشت list;
	}
      c_parser_consume_token (parser);
      اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	بازگشت list;
      p = "";
      اگر (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp (p, "abort") == 0)
	kind = OMP_CLAUSE_FALLBACK_ABORT;
      وگرنه اگر (strcmp (p, "default_mem") == 0)
	kind = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      وگرنه اگر (strcmp (p, "null") == 0)
	kind = OMP_CLAUSE_FALLBACK_NULL;
      وگرنه
	{
	  c_parser_error (parser, "expected %<abort%>, %<default_mem%>, or "
				  "%<null%> as fallback mode");
	  بازگشت list;
	}
      c_parser_consume_token (parser);
      اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	بازگشت list;
      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	بازگشت list;
    }
  location_t عبارت_loc = c_parser_peek_token (parser)->location;
  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
  عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
  درخت size = c_fully_fold (عبارت.مقدار, نادرست, پوچ);
  parens.skip_until_found_close (parser);

  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (size)))
    {
      error_at (عبارت_loc, "expected integer expression");
      بازگشت list;
    }

  /* Attempt to statically determine when the number is negative.  */
  درخت c = fold_build2_loc (عبارت_loc, LT_عبارت, boolean_type_گره, size,
			    build_int_cst (درخت_TYPE (size), 0));
  protected_set_عبارت_location (c, عبارت_loc);
  اگر (c == boolean_true_گره)
    {
      warning_at (عبارت_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      size = integer_zero_گره;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_KIND (c) = kind;
  OMP_CLAUSE_DYN_GROUPPRIVATE_عبارت (c) = size;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  بازگشت list;
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

ایستا درخت
c_parser_omp_clause_map (c_parser *parser, درخت list, منطقی declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl, c;
  شمارش gomp_map_kind kind = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  صحیح pos = 1;
  صحیح map_kind_pos = 0;
  صحیح iterator_length = 0;
  برای (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      اگر (tok->type != CPP_NAME)
	بشکن;

      ثابت نویسه *p = IDENTIFIER_POINTER (tok->مقدار);
      c_token *next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      اگر (strcmp (p, "iterator") == 0 && next_tok->type == CPP_OPEN_PAREN)
	{
	  unsigned n = pos + 2;
	  اگر (c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_length = n - pos + 1;
	      pos = n;
	      next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      اگر (next_tok->type == CPP_COLON)
	{
	  map_kind_pos = pos;
	  بشکن;
	}

      اگر (next_tok->type == CPP_COMMA)
	pos++;
      وگرنه اگر (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  unsigned صحیح npos = pos + 2;
	  اگر (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, npos + 1)->type
		  == CPP_COMMA))
	    pos = npos + 1;
	}

      pos++;
    }

  صحیح always_modifier = 0;
  صحیح close_modifier = 0;
  صحیح present_modifier = 0;
  صحیح mapper_modifier = 0;
  صحیح رقم_commas = 0;
  صحیح رقم_identifiers = 0;
  درخت mapper_name = NULL_درخت;
  درخت iterators = NULL_درخت;
  برای (صحیح pos = 1; pos < map_kind_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      اگر (tok->type == CPP_COMMA)
	{
	  ++رقم_commas;
	  اگر (رقم_commas > رقم_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  ادامه;
	}

      ثابت نویسه *p = IDENTIFIER_POINTER (tok->مقدار);
      اگر (strcmp ("always", p) == 0)
	{
	  اگر (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_found_close (parser);
	      بازگشت list;
	    }
	  always_modifier++;
	  c_parser_consume_token (parser);
	}
      وگرنه اگر (strcmp ("close", p) == 0)
	{
	  اگر (close_modifier)
	    {
	      c_parser_error (parser, "too many %<close%> modifiers");
	      parens.skip_until_found_close (parser);
	      بازگشت list;
	    }
	  close_modifier++;
	  c_parser_consume_token (parser);
	}
      وگرنه اگر (strcmp ("iterator", p) == 0)
	{
	  اگر (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      بازگشت list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      وگرنه اگر (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  اگر (mparens.require_open (parser))
	    {
	      اگر (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  بازگشت list;
		}

	      tok = c_parser_peek_token (parser);

	      انتخاب (tok->type)
		{
		حالت CPP_NAME:
		  {
		    mapper_name = tok->مقدار;
		    c_parser_consume_token (parser);
		    اگر (declare_mapper_p)
		      {
			error_at (tok->location,
				  "in %<declare mapper%> directives, parameter "
				  "to %<mapper%> modifier must be %<default%>");
		      }
		  }
		  بشکن;

		حالت CPP_KEYWORD:
		  اگر (tok->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      بشکن;
		    }
		  /* Fallthrough.  */

		پیشفرض:
		  error_at (tok->location,
			    "expected identifier or %<default%>");
		  بازگشت list;
		}

	      اگر (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  بازگشت list;
		}

	      mapper_modifier++;
	      pos += 3;
	    }
	}
      وگرنه اگر (strcmp ("present", p) == 0)
	{
	  اگر (present_modifier)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      بازگشت list;
	    }
	  present_modifier++;
	  c_parser_consume_token (parser);
	}
      وگرنه
	{
	  c_parser_error (parser, "%<map%> clause with map-type modifier other "
				  "than %<always%>, %<close%>, %<iterator%>, "
				  "%<mapper%> or %<present%>");
	  parens.skip_until_found_close (parser);
	  بازگشت list;
	}
      ++رقم_identifiers;
      اگر (رقم_identifiers - 1 > رقم_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_درج_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      رقم_commas = رقم_identifiers - 1;
    }

  اگر (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      صحیح always_present_modifier = always_modifier && present_modifier;

      اگر (strcmp ("alloc", p) == 0)
	kind = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      وگرنه اگر (strcmp ("to", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TO
		: present_modifier ? GOMP_MAP_PRESENT_TO
		: always_modifier ? GOMP_MAP_ALWAYS_TO
		: GOMP_MAP_TO);
      وگرنه اگر (strcmp ("from", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      وگرنه اگر (strcmp ("tofrom", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      وگرنه اگر (strcmp ("release", p) == 0)
	kind = GOMP_MAP_RELEASE;
      وگرنه اگر (strcmp ("delete", p) == 0)
	kind = GOMP_MAP_DELETE;
      وگرنه
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  بازگشت list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   درست);

  درخت last_new = NULL_درخت;

  اگر (iterators)
    {
      درخت block = برداشت_scope ();
      اگر (iterators == error_mark_گره)
	iterators = NULL_درخت;
      وگرنه
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  برای (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      last_new = c;
    }

  اگر (mapper_name)
    {
      درخت name = build_omp_clause (درون_داد_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_افزودن_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (درون_داد_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_برداشت_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_گره;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  parens.skip_until_found_close (parser);
  بازگشت nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

ایستا درخت
c_parser_omp_clause_device (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t عبارت_loc;
  c_عبارت عبارت;
  درخت c, t;
  منطقی ancestor = نادرست;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  اگر (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      ثابت نویسه *p = IDENTIFIER_POINTER (tok->مقدار);
      اگر (strcmp ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  اگر ((omp_requires_mask & OMP_REQUIRES_REVERSE_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_found_close (parser);
	      بازگشت list;
	    }
	  ancestor = درست;
	}
      وگرنه اگر (strcmp ("device_num", p) == 0)
	;
      وگرنه
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_found_close (parser);
	  بازگشت list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  عبارت_loc = c_parser_peek_token (parser)->location;
  عبارت = c_parser_عبارت_no_commas (parser, پوچ);
  عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
  t = عبارت.مقدار;
  t = c_fully_fold (t, نادرست, پوچ);

  parens.skip_until_found_close (parser);

  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      بازگشت list;
    }
  اگر (ancestor && درخت_CODE (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (عبارت_loc, "the %<device%> clause expression must evaluate to "
			  "%<1%>");
      بازگشت list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE, "device");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE);

  OMP_CLAUSE_DEVICE_ID (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEVICE_ANCESTOR (c) = ancestor;

  list = c;
  بازگشت list;
}

/* OpenMP 4.0:
   dist_schedule ( static )
   dist_schedule ( static , expression ) */

ایستا درخت
c_parser_omp_clause_dist_schedule (c_parser *parser, درخت list)
{
  درخت c, t = NULL_درخت;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  اگر (!c_parser_next_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      بازگشت list;
    }

  c_parser_consume_token (parser);
  اگر (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
      t = عبارت.مقدار;
      t = c_fully_fold (t, نادرست, پوچ);
      parens.skip_until_found_close (parser);
    }
  وگرنه
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  اگر (omp_find_clause (list, OMP_CLAUSE_DIST_SCHEDULE))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  اگر (t == error_mark_گره)
    بازگشت list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_SCHEDULE);
  OMP_CLAUSE_DIST_SCHEDULE_CHUNK_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

ایستا درخت
c_parser_omp_clause_proc_bind (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  شمارش omp_clause_proc_bind_kind kind;
  درخت c;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp ("primary", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_PRIMARY;
      وگرنه اگر (strcmp ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  kind = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      وگرنه اگر (strcmp ("close", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_CLOSE;
      وگرنه اگر (strcmp ("spread", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_SPREAD;
      وگرنه
	برو invalid_kind;
    }
  وگرنه
    برو invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;

 invalid_kind:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_found_close (parser);
  بازگشت list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

ایستا درخت
c_parser_omp_clause_device_type (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  شمارش omp_clause_device_type_kind kind;
  درخت c;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp ("host", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_HOST;
      وگرنه اگر (strcmp ("nohost", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      وگرنه اگر (strcmp ("any", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_ANY;
      وگرنه
	برو invalid_kind;
    }
  وگرنه
    برو invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;

 invalid_kind:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_found_close (parser);
  بازگشت list;
}

/* OpenMP 4.0:
   from ( variable-list )
   to ( variable-list )

   OpenMP 5.1:
   from ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )
   to ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )

   motion-modifier:
     present | iterator (iterators-definition) | mapper (id)  */

ایستا درخت
c_parser_omp_clause_from_to (c_parser *parser, شمارش omp_clause_code kind,
			     درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  صحیح pos = 1, colon_pos = 0;
  صحیح iterator_length = 0;

  وقتی (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      ثابت نویسه *identifier =
	IDENTIFIER_POINTER (c_parser_peek_nth_token_raw (parser, pos)->مقدار);
      اگر (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  unsigned صحیح npos = pos + 2;
	  اگر (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      اگر (strcmp (identifier, "iterator") == 0)
		iterator_length = npos - pos + 1;
	      pos = npos;
	    }
	}
      اگر (c_parser_peek_nth_token_raw (parser, pos + 1)->type == CPP_COMMA)
	pos += 2;
      وگرنه
	pos++;
      اگر (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_COLON)
	{
	  colon_pos = pos;
	  بشکن;
	}
    }

  منطقی present = نادرست, mapper_modifier = نادرست;
  درخت iterators = NULL_درخت;
  درخت mapper_name = NULL_درخت;

  برای (صحیح pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ادامه;
	}
      ثابت نویسه *p = IDENTIFIER_POINTER (token->مقدار);
      اگر (strcmp ("present", p) == 0)
	{
	  اگر (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      بازگشت list;
	    }
	  present = درست;
	  c_parser_consume_token (parser);
	}
      وگرنه اگر (strcmp ("iterator", p) == 0)
	{
	  اگر (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      بازگشت list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      وگرنه اگر (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  اگر (mparens.require_open (parser))
	    {
	      اگر (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  بازگشت list;
		}

	      token = c_parser_peek_token (parser);
	      انتخاب (token->type)
		{
		حالت CPP_NAME:
		  {
		    mapper_name = token->مقدار;
		    c_parser_consume_token (parser);
		  }
		  بشکن;
		حالت CPP_KEYWORD:
		  اگر (token->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      بشکن;
		    }
		  /* FALLTHROUGH  */
		پیشفرض:
		  error_at (token->location,
			    "expected identifier or %<default%>");
		  بازگشت list;
		}
	      اگر (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  بازگشت list;
		}
	      mapper_modifier = درست;
	      pos += 3;
	    }
	}
      وگرنه
	{
	  error_at (token->location,
		    "%qs clause with modifier other than %<iterator%>, "
		    "%<mapper%>, or %<present%>",
		    kind == OMP_CLAUSE_TO ? "to" : "from");
	  parens.skip_until_found_close (parser);
	  بازگشت list;
	}
    }

  اگر (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  درخت nl = c_parser_omp_variable_list (parser, loc, kind, list);
  parens.skip_until_found_close (parser);

  اگر (present)
    برای (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  اگر (iterators)
    {
      درخت block = برداشت_scope ();
      اگر (iterators == error_mark_گره)
	iterators = NULL_درخت;
      وگرنه
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  اگر (iterators)
    برای (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  اگر (mapper_name)
    {
      درخت last_new = NULL_درخت;
      برای (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	last_new = c;

      درخت name = build_omp_clause (درون_داد_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_افزودن_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (درون_داد_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_برداشت_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_گره;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  بازگشت nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

ایستا درخت
c_parser_omp_clause_uniform (c_parser *parser, درخت list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_UNIFORM,
					 list);
      parens.skip_until_found_close (parser);
    }
  بازگشت list;
}

/* OpenMP 5.1
   full */

ایستا درخت
c_parser_omp_clause_full (c_parser *parser, درخت list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_FULL, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  درخت c = build_omp_clause (loc, OMP_CLAUSE_FULL);
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

ایستا درخت
c_parser_omp_clause_partial (c_parser *parser, درخت list)
{
  درخت رقم = NULL_درخت;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      رقم = c_parser_عبارت_no_commas (parser, پوچ).مقدار;
      parens.skip_until_found_close (parser);

      اگر (رقم == error_mark_گره)
	بازگشت list;

      mark_exp_read (رقم);
      رقم = c_fully_fold (رقم, نادرست, پوچ);
      HOST_WIDE_INT n;
      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (رقم))
	  || !درخت_fits_shwi_p (رقم)
	  || (n = درخت_to_shwi (رقم)) <= 0
	  || (صحیح) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  بازگشت list;
	}
    }

  درخت c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_عبارت (c) = رقم;
  OMP_CLAUSE_CHAIN (c) = list;
  بازگشت c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

ایستا درخت
c_parser_omp_clause_novariants (c_parser *parser, درخت list)
{
  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
  درخت t = convert_lvalue_to_rvalue (loc, عبارت, درست, درست).مقدار;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, نادرست, پوچ);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  درخت c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  بازگشت list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

ایستا درخت
c_parser_omp_clause_nocontext (c_parser *parser, درخت list)
{
  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
  درخت t = convert_lvalue_to_rvalue (loc, عبارت, درست, درست).مقدار;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, نادرست, پوچ);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  درخت c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  بازگشت list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

ایستا درخت
c_parser_omp_clause_detach (c_parser *parser, درخت list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  اگر (!parens.require_open (parser))
    بازگشت list;

  اگر (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_found_close (parser);
      بازگشت list;
    }

  درخت t = lookup_name (c_parser_peek_token (parser)->مقدار);
  اگر (t == NULL_درخت)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->مقدار);
      parens.skip_until_found_close (parser);
      بازگشت list;
    }
  c_parser_consume_token (parser);

  درخت type = TYPE_MAIN_VARIANT (درخت_TYPE (t));
  اگر (!INTEGRAL_TYPE_P (type)
      || درخت_CODE (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_found_close (parser);
      بازگشت list;
    }

  درخت u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_found_close (parser);
  بازگشت u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

ایستا درخت
c_parser_omp_clause_destroy (c_parser *parser, درخت list)
{
  درخت nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  برای (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    درخت_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
  بازگشت nl;
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

ایستا درخت
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    بازگشت error_mark_گره;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  اگر (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    وقتی (درست)
      {
	str += (نویسه) GOMP_INTEROP_IFR_SEPARATOR;
	اگر (c_parser_next_token_is (parser, CPP_STRING))
	  {
	    c_عبارت cval = c_parser_string_literal (parser, نادرست, نادرست);
	    اگر (cval.مقدار == error_mark_گره)
	      بازگشت error_mark_گره;
	    اگر ((size_t) درخت_STRING_LENGTH (cval.مقدار)
		!= strlen (درخت_STRING_POINTER (cval.مقدار)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = درست;
		بازگشت error_mark_گره;
	      }

	    نویسه c = omp_get_fr_id_from_name (درخت_STRING_POINTER (cval.مقدار));
	    اگر (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  درخت_STRING_POINTER (cval.مقدار));
	    str += c;
	  }
	وگرنه
	  {
	    c_عبارت cval = c_parser_عبارت_no_commas (parser, پوچ);
	    درخت مقدار = c_fully_fold (cval.مقدار, نادرست, پوچ);
	    اگر (INTEGRAL_TYPE_P (درخت_TYPE (مقدار))
		&& درخت_CODE (مقدار) != INTEGER_CST)
	      مقدار = convert_lvalue_to_rvalue (cval.get_start (), cval,
						نادرست, درست).مقدار;
	    اگر (درخت_CODE (مقدار) != INTEGER_CST
		|| !درخت_fits_shwi_p (مقدار))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		بازگشت error_mark_گره;
	      }
	    HOST_WIDE_INT n = درخت_to_shwi (مقدار);
	    اگر (n < 1 || n > GOMP_INTEROP_IFR_LAST)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (نویسه) n;
	  }
	str += (نویسه) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	اگر (c_parser_next_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    ادامه;
	  }
	اگر (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  بازگشت error_mark_گره;
	str += '\0';
	درخت res = build_string (str.length (), str.data ());
	درخت_TYPE (res) = build_array_type_nelts (unsigned_char_type_گره,
						  str.length ());
	بازگشت res;
      }

  /* New format. */
  std::string str2;
  وقتی (درست)
    {
      اگر (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	بازگشت error_mark_گره;
      str += (نویسه) GOMP_INTEROP_IFR_SEPARATOR;
      str2.clear ();
      منطقی has_fr = نادرست;
      وقتی (درست)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  اگر (tok->type != CPP_NAME
	      || (strcmp("fr", IDENTIFIER_POINTER (tok->مقدار)) != 0
		  && strcmp("attr", IDENTIFIER_POINTER (tok->مقدار)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      بازگشت error_mark_گره;
	    }
	  c_parser_consume_token (parser);
	  منطقی is_fr = IDENTIFIER_POINTER (tok->مقدار)[0] == 'f';
	  اگر (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      بازگشت error_mark_گره;
	    }
	  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    بازگشت error_mark_گره;
	  وقتی (درست)
	    {
	      اگر (c_parser_next_token_is (parser, CPP_STRING))
		{
		  c_عبارت cval = c_parser_string_literal (parser, نادرست, نادرست);
		  درخت مقدار = cval.مقدار;
		  اگر (مقدار == error_mark_گره)
		    بازگشت error_mark_گره;
		  اگر ((size_t) درخت_STRING_LENGTH (مقدار)
		      != strlen (درخت_STRING_POINTER (مقدار)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = درست;
		      بازگشت error_mark_گره;
		    }
		  اگر (!is_fr)
		    {
		      اگر (!startswith (درخت_STRING_POINTER (مقدار), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = درست;
			  بازگشت error_mark_گره;
			}
		      اگر (strchr (درخت_STRING_POINTER (مقدار), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = درست;
			  بازگشت error_mark_گره;
			}
		      str2 += درخت_STRING_POINTER (مقدار);
		      str2 += '\0';
		    }
		  وگرنه
		    {
		      اگر (*درخت_STRING_POINTER (مقدار) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  بازگشت error_mark_گره;
			}
		      نویسه c = omp_get_fr_id_from_name (درخت_STRING_POINTER (مقدار));
		      اگر (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    درخت_STRING_POINTER (مقدار));
		     str += c;
		     has_fr = درست;
		    }
		}
	      وگرنه اگر (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  بازگشت error_mark_گره;
		}
	      وگرنه
		{
		  c_عبارت cval = c_parser_عبارت_no_commas (parser, پوچ);
		  درخت مقدار = c_fully_fold (cval.مقدار, نادرست, پوچ);
		  اگر (INTEGRAL_TYPE_P (درخت_TYPE (مقدار))
		      && درخت_CODE (مقدار) != INTEGER_CST)
		    مقدار = convert_lvalue_to_rvalue (cval.get_start (), cval,
						      نادرست, درست).مقدار;

		  اگر (درخت_CODE (مقدار) != INTEGER_CST
		      || !درخت_fits_shwi_p (مقدار))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      بازگشت error_mark_گره;
		    }
		  HOST_WIDE_INT n = درخت_to_shwi (مقدار);
		  اگر (n < 1 || n > GOMP_INTEROP_IFR_LAST)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (نویسه) n;
		  has_fr = درست;
		}
	      اگر (!is_fr
		  && c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ادامه;
		}
	      اگر (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		بازگشت error_mark_گره;
	      بشکن;
	    }
	  اگر (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ادامه;
	    }
	  اگر (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    بشکن;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  بازگشت error_mark_گره;
	}
      str += (نویسه) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	بشکن;
      اگر (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	بازگشت error_mark_گره;
    }
  c_parser_consume_token (parser);
  str += '\0';
  درخت res = build_string (str.length (), str.data ());
  درخت_TYPE (res) = build_array_type_nelts (unsigned_char_type_گره,
						  str.length ());
  بازگشت res;
}

/* OpenMP 5.1
     modifiers of the 'init' clause, used by the 'init' and the
     'append_args' clauses.

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification)

  Returns 'false' if an error has been issued.  */

ایستا منطقی
c_parser_omp_clause_init_modifiers (c_parser *parser, منطقی *target,
				    منطقی *targetsync, درخت *prefer_type_درخت)
{
  *target = نادرست;
  *targetsync = نادرست;
  *prefer_type_درخت = NULL_درخت;

  انجامبده
    {
      c_token *tok = c_parser_peek_token (parser);
      اگر (tok->type != CPP_NAME)
	برو fail;
      ثابت نویسه *p = IDENTIFIER_POINTER (tok->مقدار);
      اگر (strcmp ("targetsync", p) == 0)
	{
	  اگر (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = درست;
	  c_parser_consume_token (parser);
	}
      وگرنه اگر (strcmp ("target", p) == 0)
	{
	  اگر (*target)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *target = درست;
	  c_parser_consume_token (parser);
	}
      وگرنه اگر (strcmp ("prefer_type", p) == 0)
	{
	  اگر (*prefer_type_درخت != NULL_درخت)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_درخت = c_parser_omp_modifier_prefer_type (parser);
	  اگر (*prefer_type_درخت == error_mark_گره)
	    بازگشت نادرست;
	}
      وگرنه
	برو fail;
      tok = c_parser_peek_token (parser);
      اگر (tok->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ادامه;
	}
      /* Unknown token - either done or an error; handle it in the caller.  */
      بازگشت درست;
    }
  وقتی (درست);

fail:
  c_parser_error (parser,
		  "expected %<prefer_type%>, %<target%>, or %<targetsync%>");
  بازگشت نادرست;
}

/* OpenMP 5.1:
   init ( [init-modifier-list : ] variable-list )

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification) */

ایستا درخت
c_parser_omp_clause_init (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت list;

  منطقی target = نادرست;
  منطقی targetsync = نادرست;
  درخت prefer_type_درخت = NULL_درخت;

  اگر (!c_parser_omp_clause_init_modifiers (parser, &target, &targetsync,
					   &prefer_type_درخت)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      اگر (prefer_type_درخت != error_mark_گره)
	parens.skip_until_found_close (parser);
      بازگشت list;
    }

  اگر (!target && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  درخت nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					نادرست);
  parens.skip_until_found_close (parser);

  برای (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      درخت_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      اگر (target)
	OMP_CLAUSE_INIT_TARGET (c) = 1;
      اگر (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      اگر (prefer_type_درخت)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_درخت;
    }
  بازگشت nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

ایستا درخت
c_parser_omp_clause_use (c_parser *parser, درخت list)
{
  بازگشت c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

ایستا درخت
c_parser_omp_clause_interop (c_parser *parser, درخت list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  درخت nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  برای (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      درخت_USED (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  بازگشت nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

ایستا درخت
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_mask mask,
			   ثابت نویسه *where, منطقی finish_p = درست,
			   منطقی target_p = نادرست)
{
  درخت clauses = پوچ;
  منطقی first = درست;

  وقتی (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      ثابت نویسه *c_name;
      درخت prev = clauses;

      اگر (!first && c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      انتخاب (c_kind)
	{
	حالت PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "attach";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copy";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyin";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyout";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "create";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "delete";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, درست);
	  c_name = "default";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "detach";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_data_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device_resident";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_GANG,
						c_name, clauses);
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "host";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, نادرست);
	  c_name = "if";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "link";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "no_create";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_رقم_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_رقم_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_رقم_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_رقم_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "present";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     نادرست, clauses);
	  c_name = "reduction";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_SELF:
	  اگر ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  وگرنه
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "self";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_SEQ,
						 clauses);
	  c_name = "seq";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_TILE:
	  clauses = c_parser_oacc_clause_tile (parser, clauses);
	  c_name = "tile";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_USE_DEVICE:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_VECTOR:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_VECTOR,
						c_name,	clauses);
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_VECTOR_LENGTH:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_VECTOR_LENGTH,
						     clauses);
	  c_name = "vector_length";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  بشکن;
	حالت PRAGMA_OACC_CLAUSE_WORKER:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_WORKER,
						c_name, clauses);
	  بشکن;
	پیشفرض:
	  c_parser_error (parser, "expected an OpenACC clause");
	  برو saw_error;
	}

      first = نادرست;

      اگر (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_to_pragma_eol (parser);

  اگر (finish_p)
    بازگشت c_finish_omp_clauses (clauses, target_p ? C_ORT_ACC_TARGET
						   : C_ORT_ACC);

  بازگشت clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

ایستا درخت
c_parser_omp_all_clauses (c_parser *parser, omp_clause_mask mask,
			  ثابت نویسه *where, منطقی finish_p = درست,
			  صحیح nested = 0)
{
  درخت clauses = پوچ;
  منطقی first = درست;

  وقتی (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      ثابت نویسه *c_name;
      درخت prev = clauses;

      اگر (nested && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	بشکن;

      اگر (!first || nested != 2)
	{
	  اگر (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وگرنه اگر (nested == 2)
	    error_at (c_parser_peek_token (parser)->location,
		      "clauses in %<simd%> trait should be separated "
		      "by %<,%>");
	}

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      انتخاب (c_kind)
	{
	حالت PRAGMA_OMP_CLAUSE_BIND:
	  clauses = c_parser_omp_clause_bind (parser, clauses);
	  c_name = "bind";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, نادرست);
	  c_name = "default";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_DETACH:
	  clauses = c_parser_omp_clause_detach (parser, clauses);
	  c_name = "detach";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_FILTER:
	  clauses = c_parser_omp_clause_filter (parser, clauses);
	  c_name = "filter";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_FINAL:
	  clauses = c_parser_omp_clause_final (parser, clauses);
	  c_name = "final";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_GRAINSIZE:
	  clauses = c_parser_omp_clause_grainsize (parser, clauses);
	  c_name = "grainsize";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_HINT:
	  clauses = c_parser_omp_clause_hint (parser, clauses);
	  c_name = "hint";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_DEFAULTMAP:
	  clauses = c_parser_omp_clause_defaultmap (parser, clauses);
	  c_name = "defaultmap";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, درست);
	  c_name = "if";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_IN_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_IN_REDUCTION,
					     درست, clauses);
	  c_name = "in_reduction";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_INDIRECT:
	  clauses = c_parser_omp_clause_indirect (parser, clauses);
	  c_name = "indirect";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_MERGEABLE:
	  clauses = c_parser_omp_clause_mergeable (parser, clauses);
	  c_name = "mergeable";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_رقم_TASKS:
	  clauses = c_parser_omp_clause_رقم_tasks (parser, clauses);
	  c_name = "num_tasks";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_رقم_THREADS:
	  clauses = c_parser_omp_clause_رقم_threads (parser, clauses);
	  c_name = "num_threads";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_ORDER:
	  clauses = c_parser_omp_clause_order (parser, clauses);
	  c_name = "order";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_PRIORITY:
	  clauses = c_parser_omp_clause_priority (parser, clauses);
	  c_name = "priority";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     درست, clauses);
	  c_name = "reduction";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_SCHEDULE:
	  clauses = c_parser_omp_clause_schedule (parser, clauses);
	  c_name = "schedule";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     درست, clauses);
	  c_name = "task_reduction";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_UNTIED:
	  clauses = c_parser_omp_clause_untied (parser, clauses);
	  c_name = "untied";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_INBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_INBRANCH,
						clauses);
	  c_name = "inbranch";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_NONTEMPORAL:
	  clauses = c_parser_omp_clause_nontemporal (parser, clauses);
	  c_name = "nontemporal";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_NOTINBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_NOTINBRANCH,
						clauses);
	  c_name = "notinbranch";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_PARALLEL:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_PARALLEL,
					      clauses);
	  c_name = "parallel";
	  اگر (!first)
	    {
	     clause_not_first:
	      error_at (here, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = prev;
	    }
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  اگر (!first)
	    برو clause_not_first;
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  اگر (!first)
	    برو clause_not_first;
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  اگر (!first)
	    برو clause_not_first;
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_LINK:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LINK, clauses);
	  c_name = "link";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_LOCAL:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LOCAL, clauses);
	  c_name = "local";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_TO:
	  اگر ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (here);
	      richloc.add_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      درخت nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      برای (درخت c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_TO (c) = 1;
	      clauses = nl;
	    }
	  وگرنه
	    clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_TO,
						   clauses);
	  c_name = "to";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_UNIFORM:
	  clauses = c_parser_omp_clause_uniform (parser, clauses);
	  c_name = "uniform";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_رقم_TEAMS:
	  clauses = c_parser_omp_clause_رقم_teams (parser, clauses);
	  c_name = "num_teams";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_THREAD_LIMIT:
	  clauses = c_parser_omp_clause_thread_limit (parser, clauses);
	  c_name = "thread_limit";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_ALIGNED:
	  clauses = c_parser_omp_clause_aligned (parser, clauses);
	  c_name = "aligned";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_ALLOCATE:
	  clauses = c_parser_omp_clause_allocate (parser, clauses);
	  c_name = "allocate";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_LINEAR:
	  clauses = c_parser_omp_clause_linear (parser, clauses);
	  c_name = "linear";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_USES_ALLOCATORS:
	  clauses = c_parser_omp_clause_uses_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, here);
	  c_name = "depend";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_DOACROSS:
	  clauses = c_parser_omp_clause_doacross (parser, clauses);
	  c_name = "doacross";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_DESTROY:
	  clauses = c_parser_omp_clause_destroy (parser, clauses);
	  c_name = "destroy";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE:
	  clauses = c_parser_omp_clause_dyn_groupprivate (parser, clauses);
	  c_name = "dyn_groupprivate";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_INIT:
	  clauses = c_parser_omp_clause_init (parser, clauses);
	  c_name = "init";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_USE:
	  clauses = c_parser_omp_clause_use (parser, clauses);
	  c_name = "use";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_INTEROP:
	  clauses = c_parser_omp_clause_interop (parser, clauses);
	  c_name = "interop";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_MAP:
	  clauses = c_parser_omp_clause_map (parser, clauses, نادرست);
	  c_name = "map";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device_ptr";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_use_device_addr (parser, clauses);
	  c_name = "use_device_addr";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_has_device_addr (parser, clauses);
	  c_name = "has_device_addr";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR:
	  clauses = c_parser_omp_clause_is_device_ptr (parser, clauses);
	  c_name = "is_device_ptr";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_DEVICE:
	  clauses = c_parser_omp_clause_device (parser, clauses);
	  c_name = "device";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_DIST_SCHEDULE:
	  clauses = c_parser_omp_clause_dist_schedule (parser, clauses);
	  c_name = "dist_schedule";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_PROC_BIND:
	  clauses = c_parser_omp_clause_proc_bind (parser, clauses);
	  c_name = "proc_bind";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_DEVICE_TYPE:
	  clauses = c_parser_omp_clause_device_type (parser, clauses);
	  c_name = "device_type";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_SAFELEN:
	  clauses = c_parser_omp_clause_safelen (parser, clauses);
	  c_name = "safelen";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_SIMDLEN:
	  clauses = c_parser_omp_clause_simdlen (parser, clauses);
	  c_name = "simdlen";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_NOGROUP:
	  clauses = c_parser_omp_clause_nogroup (parser, clauses);
	  c_name = "nogroup";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_THREADS:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_THREADS,
					       clauses);
	  c_name = "threads";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_SIMD:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_SIMD,
					       clauses);
	  c_name = "simd";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_ENTER:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					    clauses);
	  c_name = "enter";
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_FULL:
	  c_name = "full";
	  clauses = c_parser_omp_clause_full (parser, clauses);
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_PARTIAL:
	  c_name = "partial";
	  clauses = c_parser_omp_clause_partial (parser, clauses);
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_NOVARIANTS:
	  c_name = "novariants";
	  clauses = c_parser_omp_clause_novariants (parser, clauses);
	  بشکن;
	حالت PRAGMA_OMP_CLAUSE_NOCONTEXT:
	  c_name = "nocontext";
	  clauses = c_parser_omp_clause_nocontext (parser, clauses);
	  بشکن;
	پیشفرض:
	  c_parser_error (parser, "expected an OpenMP clause");
	  برو saw_error;
	}

      first = نادرست;

      اگر (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  اگر (!nested)
    c_parser_skip_to_pragma_eol (parser);

  اگر (finish_p)
    {
      اگر ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_UNIFORM)) != 0)
	بازگشت c_finish_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      اگر ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	بازگشت c_finish_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      بازگشت c_finish_omp_clauses (clauses, C_ORT_OMP);
    }

  بازگشت clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

ایستا درخت
c_parser_omp_structured_block (c_parser *parser, منطقی *if_p)
{
  درخت stmt = افزودن_stmt_list ();
  parser->omp_attrs_forbidden_p = درست;
  c_parser_statement (parser, if_p);
  بازگشت برداشت_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

ایستا درخت
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  درخت stmt, clauses = NULL_درخت;
  منطقی readonly = نادرست;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (token->type == CPP_NAME
	  && !strcmp (IDENTIFIER_POINTER (token->مقدار), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = درست;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_درخت);
      parens.skip_until_found_close (parser);
    }

  اگر (readonly)
    برای (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_to_pragma_eol (parser);

  stmt = make_گره (OACC_CACHE);
  درخت_TYPE (stmt) = void_type_گره;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  SET_عبارت_LOCATION (stmt, loc);
  add_stmt (stmt);

  بازگشت stmt;
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

ایستا درخت
c_parser_oacc_data (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_DATA_CLAUSE_MASK,
				       "#pragma acc data");

  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  stmt = c_finish_oacc_data (loc, clauses, block);

  بازگشت stmt;
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

ایستا تهی
c_parser_oacc_declare (c_parser *parser)
{
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  درخت clauses, stmt, t, decl;

  منطقی error = نادرست;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_MASK,
				       "#pragma acc declare");
  اگر (!clauses)
    {
      error_at (pragma_loc,
		"no valid clauses specified in %<#pragma acc declare%>");
      بازگشت;
    }

  برای (t = clauses; t; t = OMP_CLAUSE_CHAIN (t))
    {
      location_t loc = OMP_CLAUSE_LOCATION (t);
      decl = OMP_CLAUSE_DECL (t);
      اگر (!DECL_P (decl))
	{
	  error_at (loc, "array section in %<#pragma acc declare%>");
	  error = درست;
	  ادامه;
	}

      انتخاب (OMP_CLAUSE_MAP_KIND (t))
	{
	حالت GOMP_MAP_FIRSTPRIVATE_POINTER:
	حالت GOMP_MAP_ALLOC:
	حالت GOMP_MAP_TO:
	حالت GOMP_MAP_FORCE_DEVICEPTR:
	حالت GOMP_MAP_DEVICE_RESIDENT:
	  بشکن;

	حالت GOMP_MAP_LINK:
	  اگر (!global_bindings_p ()
	      && (درخت_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = درست;
	      ادامه;
	    }
	  بشکن;

	پیشفرض:
	  اگر (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = درست;
	      ادامه;
	    }
	  اگر (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = درست;
	      ادامه;
	    }
	  وگرنه اگر (درخت_PUBLIC (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = درست;
	      ادامه;
	    }
	  بشکن;
	}

      اگر (!c_check_in_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = درست;
	  ادامه;
	}

      اگر (lookup_attribute ("omp declare target", DECL_ATTRIBUTES (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_ATTRIBUTES (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = درست;
	  ادامه;
	}

      اگر (!error)
	{
	  درخت id;

	  اگر (OMP_CLAUSE_MAP_KIND (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  وگرنه
	    id = get_identifier ("omp declare target");

	  DECL_ATTRIBUTES (decl)
			   = درخت_cons (id, NULL_درخت, DECL_ATTRIBUTES (decl));

	  اگر (global_bindings_p ())
	    {
	      symtab_گره *گره = symtab_گره::get (decl);
	      اگر (گره != پوچ)
		{
		  گره->offloadable = 1;
		  اگر (ENABLE_OFFLOADING)
		    {
		      g->have_offload = درست;
		      اگر (is_a <varpool_گره *> (گره))
			vec_safe_افزودن (offload_vars, decl);
		    }
		}
	    }
	}
    }

  اگر (error || global_bindings_p ())
    بازگشت;

  stmt = make_گره (OACC_DECLARE);
  درخت_TYPE (stmt) = void_type_گره;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  SET_عبارت_LOCATION (stmt, pragma_loc);

  add_stmt (stmt);

  بازگشت;
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

ایستا تهی
c_parser_oacc_enter_exit_data (c_parser *parser, منطقی enter)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت clauses, stmt;
  ثابت نویسه *p = "";

  c_parser_consume_pragma (parser);

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      c_parser_consume_token (parser);
    }

  اگر (strcmp (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = درست;
      c_parser_skip_to_pragma_eol (parser);
      بازگشت;
    }

  اگر (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_DATA_CLAUSE_MASK,
					 "#pragma acc enter data");
  وگرنه
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_DATA_CLAUSE_MASK,
					 "#pragma acc exit data");

  اگر (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_درخت)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      بازگشت;
    }

  stmt = enter ? make_گره (OACC_ENTER_DATA) : make_گره (OACC_EXIT_DATA);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  SET_عبارت_LOCATION (stmt, loc);
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

ایستا درخت
c_parser_oacc_host_data (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_DATA_CLAUSE_MASK,
				       "#pragma acc host_data", نادرست);
  اگر (!omp_find_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      بازگشت error_mark_گره;
    }
  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  stmt = c_finish_oacc_host_data (loc, clauses, block);
  بازگشت stmt;
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
ایستا درخت
c_parser_oacc_loop (location_t loc, c_parser *parser, نویسه *p_name,
		    omp_clause_mask mask, درخت *cclauses, منطقی *if_p)
{
  منطقی is_parallel = ((mask >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  strcat (p_name, " loop");
  mask |= OACC_LOOP_CLAUSE_MASK;

  درخت clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/cclauses == پوچ,
					    /*target=*/is_parallel);
  اگر (cclauses)
    {
      clauses = c_oacc_split_loop_clauses (clauses, cclauses, is_parallel);
      اگر (*cclauses)
	*cclauses = c_finish_omp_clauses (*cclauses, C_ORT_ACC_TARGET);
      اگر (clauses)
	clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
    }

  درخت block = c_begin_compound_stmt (درست);
  درخت stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, پوچ,
				     if_p);
  block = c_end_compound_stmt (loc, block, درست);
  add_stmt (block);

  بازگشت stmt;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_رقم_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_رقم_WORKERS)		\
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_رقم_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_رقم_WORKERS)		\
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

ایستا درخت
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       شمارش pragma_kind p_kind, نویسه *p_name, منطقی *if_p)
{
  omp_clause_mask mask;
  شمارش درخت_code code;
  انتخاب (p_kind)
    {
    حالت PRAGMA_OACC_KERNELS:
      strcat (p_name, " kernels");
      mask = OACC_KERNELS_CLAUSE_MASK;
      code = OACC_KERNELS;
      بشکن;
    حالت PRAGMA_OACC_PARALLEL:
      strcat (p_name, " parallel");
      mask = OACC_PARALLEL_CLAUSE_MASK;
      code = OACC_PARALLEL;
      بشکن;
    حالت PRAGMA_OACC_SERIAL:
      strcat (p_name, " serial");
      mask = OACC_SERIAL_CLAUSE_MASK;
      code = OACC_SERIAL;
      بشکن;
    پیشفرض:
      gcc_unreachable ();
    }

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  درخت block = c_begin_omp_parallel ();
	  درخت clauses;
	  c_parser_oacc_loop (loc, parser, p_name, mask, &clauses, if_p);
	  بازگشت c_finish_omp_construct (loc, code, block, clauses);
	}
    }

  درخت clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/درست,
					    /*target=*/درست);

  درخت block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  بازگشت c_finish_omp_construct (loc, code, block, clauses);
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

ایستا تهی
c_parser_oacc_routine (c_parser *parser, شمارش pragma_context context)
{
  gcc_checking_assert (context == pragma_external);

  oacc_routine_data data;
  data.error_seen = نادرست;
  data.fndecl_seen = نادرست;
  data.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      درخت decl = NULL_درخت;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      اگر (name_token->type == CPP_NAME
	  && (name_token->id_kind == C_ID_ID
	      || name_token->id_kind == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->مقدار);
	  اگر (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->مقدار);
	  c_parser_consume_token (parser);
	}
      وگرنه
	c_parser_error (parser, "expected function name");

      اگر (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_to_pragma_eol (parser, نادرست);
	  بازگشت;
	}

      data.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_MASK,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      data.clauses = nreverse (data.clauses);

      اگر (درخت_CODE (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  بازگشت;
	}

      c_finish_oacc_routine (&data, decl, نادرست);
    }
  وگرنه /* No optional '( name )'.  */
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
      اگر (c_parser_next_token_is (parser, CPP_PRAGMA)
	  || c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (data.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  بازگشت;
	}

      /* We only have to consider the pragma_external case here.  */
      اگر (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحیح ext = disable_extension_diagnostics ();
	  انجامبده
	    c_parser_consume_token (parser);
	  وقتی (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, درست, درست, درست, نادرست, درست,
					 نادرست, پوچ, پوچ, نادرست, پوچ, &data);
	  restore_extension_diagnostics (ext);
	}
      وگرنه
	c_parser_declaration_or_fndef (parser, درست, درست, درست, نادرست, درست,
				       نادرست, پوچ, پوچ, نادرست, پوچ, &data);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

ایستا تهی
c_finish_oacc_routine (ساختار oacc_routine_data *data, درخت fndecl,
		       منطقی is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  اگر (data->error_seen
      || fndecl == error_mark_گره)
    بازگشت;

  اگر (data->fndecl_seen)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      data->error_seen = درست;
      بازگشت;
    }
  اگر (fndecl == NULL_درخت || درخت_CODE (fndecl) != FUNCTION_DECL)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      data->error_seen = درست;
      بازگشت;
    }

  صحیح compatible
    = oacc_verify_routine_clauses (fndecl, &data->clauses, data->loc,
				   "#pragma acc routine");
  اگر (compatible < 0)
    {
      data->error_seen = درست;
      بازگشت;
    }
  اگر (compatible > 0)
    {
    }
  وگرنه
    {
      اگر (درخت_USED (fndecl) || (!is_defn && DECL_SAVED_درخت (fndecl)))
	{
	  error_at (data->loc,
		    درخت_USED (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  data->error_seen = درست;
	  بازگشت;
	}

      /* Set the routine's level of parallelism.  */
      درخت dims = oacc_build_routine_dims (data->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_ATTRIBUTES (fndecl)
	= درخت_cons (get_identifier ("omp declare target"),
		     data->clauses, DECL_ATTRIBUTES (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  data->fndecl_seen = درست;
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

ایستا تهی
c_parser_oacc_update (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  درخت clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_MASK,
					    "#pragma acc update");
  اگر (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_درخت)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      بازگشت;
    }

  اگر (parser->error)
    بازگشت;

  درخت stmt = make_گره (OACC_UPDATE);
  درخت_TYPE (stmt) = void_type_گره;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  SET_عبارت_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#define OACC_WAIT_CLAUSE_MASK						\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF) )

ایستا درخت
c_parser_oacc_wait (location_t loc, c_parser *parser, نویسه *p_name)
{
  درخت clauses, list = NULL_درخت, stmt = NULL_درخت;

  اگر (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  strcpy (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_MASK, p_name);
  stmt = c_finish_oacc_wait (loc, list, clauses);
  add_stmt (stmt);

  بازگشت stmt;
}

ساختار c_omp_loc_درخت
{
  location_t loc;
  درخت var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
ایستا درخت
c_check_omp_allocate_allocator_r (درخت *tp, صحیح *, تهی *data)
{
  درخت var = ((ساختار c_omp_loc_درخت *) data)->var;
  location_t loc = ((ساختار c_omp_loc_درخت *) data)->loc;
  اگر (درخت_CODE (*tp) == VAR_DECL && c_check_in_current_scope (*tp))
    {
      اگر (linemap_location_before_p (سطر_table, DECL_SOURCE_LOCATION (var),
				     DECL_SOURCE_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_SOURCE_LOCATION (*tp), "declared here");
	  inform (DECL_SOURCE_LOCATION (var),
		  "to be allocated variable declared here");
	  بازگشت *tp;
	}
      وگرنه
	{
	  gcc_assert (cur_stmt_list
		      && درخت_CODE (cur_stmt_list) == STATEMENT_LIST);

	  درخت_stmt_iterator l = tsi_last (cur_stmt_list);
	  وقتی (!tsi_end_p (l))
	    {
	      اگر (linemap_location_before_p (سطر_table, عبارت_LOCATION (*l),
					     DECL_SOURCE_LOCATION (var)))
		  بشکن;
	      اگر (درخت_CODE (*l) == MODIFY_عبارت
		  && درخت_OPERAND (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (عبارت_LOCATION (*l), "modified here");
		  inform (DECL_SOURCE_LOCATION (var),
			  "to be allocated variable declared here");
		  بازگشت *tp;
		}
	      --l;
	    }
	}
    }
  بازگشت NULL_درخت;
}

/* OpenMP 5.x:
   # pragma omp allocate (list)  clauses

   OpenMP 5.0 clause:
   allocator (omp_allocator_handle_t expression)

   OpenMP 5.1 additional clause:
   align (constant-expression)]  */

ایستا تهی
c_parser_omp_allocate (c_parser *parser)
{
  درخت alignment = NULL_درخت;
  درخت allocator = NULL_درخت;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  درخت nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_درخت);
  انجامبده
    {
      اگر (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      اگر (!c_parser_next_token_is (parser, CPP_NAME))
	بشکن;
      matching_parens parens;
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      c_parser_consume_token (parser);
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      اگر (strcmp ("align", p) != 0 && strcmp ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  بشکن;
	}
      اگر (!parens.require_open (parser))
	بشکن;

      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, نادرست, درست);
      عبارت_loc = c_parser_peek_token (parser)->location;
      اگر (عبارت.مقدار == error_mark_گره)
	;
      وگرنه اگر (p[2] == 'i' && alignment)
	{
	  error_at (عبارت_loc, "too many %qs clauses", "align");
	  بشکن;
	}
      وگرنه اگر (p[2] == 'i')
	{
	  alignment = c_fully_fold (عبارت.مقدار, نادرست, پوچ);
	  اگر (درخت_CODE (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (درخت_TYPE (alignment))
	      || درخت_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (عبارت_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_درخت;
	    }
	}
      وگرنه اگر (allocator)
	{
	  error_at (عبارت_loc, "too many %qs clauses", "allocator");
	  بشکن;
	}
      وگرنه
	{
	  allocator = c_fully_fold (عبارت.مقدار, نادرست, پوچ);
	  allocator_loc = عبارت_loc;
	  درخت orig_type
	    = عبارت.original_type ? عبارت.original_type : درخت_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (allocator))
	      || درخت_CODE (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (عبارت_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			درخت_TYPE (allocator));
	      allocator = NULL_درخت;
	    }
	}
      parens.skip_until_found_close (parser);
    } وقتی (درست);
  c_parser_skip_to_pragma_eol (parser);

  c_mark_decl_jump_unsafe_in_current_scope ();
  برای (درخت c = nl; c != NULL_درخت; c = OMP_CLAUSE_CHAIN (c))
    {
      درخت var = OMP_CLAUSE_DECL (c);
      اگر (درخت_CODE (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  ادامه;
	}
      اگر (!parser->in_omp_decl_attribute && !c_check_in_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_SOURCE_LOCATION (var), "declared here");
	  ادامه;
	}
      اگر (lookup_attribute ("omp allocate", DECL_ATTRIBUTES (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  ادامه;
	}
      اگر (درخت_STATIC (var))
	{
	  اگر (allocator == NULL_درخت && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      ادامه;
	    }
	  وگرنه اگر (allocator
		   && (wi::to_widest (allocator) < 1
		       || wi::to_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::to_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::to_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  وگرنه اگر (allocator
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
      اگر (allocator)
	{
	  ساختار c_omp_loc_درخت data
	    = {عبارت_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_درخت (&allocator, c_check_omp_allocate_allocator_r, &data, پوچ);
	}
      DECL_ATTRIBUTES (var) = درخت_cons (get_identifier ("omp allocate"),
					 build_درخت_list (allocator, alignment),
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

ایستا تهی
c_parser_omp_atomic (location_t loc, c_parser *parser, منطقی openacc)
{
  درخت lhs = NULL_درخت, rhs = NULL_درخت, v = NULL_درخت, r = NULL_درخت;
  درخت lhs1 = NULL_درخت, rhs1 = NULL_درخت;
  درخت stmt, orig_lhs, unfolded_lhs = NULL_درخت, unfolded_lhs1 = NULL_درخت;
  شمارش درخت_code code = ERROR_MARK, opcode = NOP_عبارت;
  شمارش omp_memory_order memory_order = OMP_MEMORY_ORDER_UNSPECIFIED;
  ساختار c_عبارت عبارت;
  location_t eloc;
  منطقی structured_block = نادرست;
  منطقی swapped = نادرست;
  منطقی non_lvalue_p;
  درخت clauses = NULL_درخت;
  منطقی capture = نادرست;
  منطقی compare = نادرست;
  منطقی weak = نادرست;
  شمارش omp_memory_order fail = OMP_MEMORY_ORDER_UNSPECIFIED;
  منطقی no_semicolon = نادرست;
  منطقی extra_scope = نادرست;

  وقتی (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      اگر (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      اگر (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ثابت نویسه *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  شمارش درخت_code new_code = ERROR_MARK;
	  شمارش omp_memory_order new_memory_order
	    = OMP_MEMORY_ORDER_UNSPECIFIED;
	  منطقی new_capture = نادرست;
	  منطقی new_compare = نادرست;
	  منطقی new_weak = نادرست;
	  شمارش omp_memory_order new_fail = OMP_MEMORY_ORDER_UNSPECIFIED;

	  اگر (!strcmp (p, "read"))
	    new_code = OMP_ATOMIC_READ;
	  وگرنه اگر (!strcmp (p, "write"))
	    new_code = NOP_عبارت;
	  وگرنه اگر (!strcmp (p, "update"))
	    new_code = OMP_ATOMIC;
	  وگرنه اگر (openacc && !strcmp (p, "capture"))
	    new_code = OMP_ATOMIC_CAPTURE_NEW;
	  وگرنه اگر (openacc)
	    {
	      p = پوچ;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  وگرنه اگر (!strcmp (p, "capture"))
	    new_capture = درست;
	  وگرنه اگر (!strcmp (p, "compare"))
	    new_compare = درست;
	  وگرنه اگر (!strcmp (p, "weak"))
	    new_weak = درست;
	  وگرنه اگر (!strcmp (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      اگر (!parens.require_open (parser))
		ادامه;

	      اگر (c_parser_next_token_is (parser, CPP_NAME))
		{
		  ثابت نویسه *q
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);

		  اگر (!strcmp (q, "seq_cst"))
		    new_fail = OMP_MEMORY_ORDER_SEQ_CST;
		  وگرنه اگر (!strcmp (q, "acquire"))
		    new_fail = OMP_MEMORY_ORDER_ACQUIRE;
		  وگرنه اگر (!strcmp (q, "relaxed"))
		    new_fail = OMP_MEMORY_ORDER_RELAXED;
		}

	      اگر (new_fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  اگر (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  وگرنه
		    fail = new_fail;
		}
	      وگرنه
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_found_close (parser);
	      ادامه;
	    }
	  وگرنه اگر (!strcmp (p, "seq_cst"))
	    new_memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  وگرنه اگر (!strcmp (p, "acq_rel"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	  وگرنه اگر (!strcmp (p, "release"))
	    new_memory_order = OMP_MEMORY_ORDER_RELEASE;
	  وگرنه اگر (!strcmp (p, "acquire"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  وگرنه اگر (!strcmp (p, "relaxed"))
	    new_memory_order = OMP_MEMORY_ORDER_RELAXED;
	  وگرنه اگر (!strcmp (p, "hint"))
	    {
	      c_parser_consume_token (parser);
	      clauses = c_parser_omp_clause_hint (parser, clauses);
	      ادامه;
	    }
	  وگرنه
	    {
	      p = پوچ;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "%<capture%>, %<compare%>, %<weak%>, %<fail%>, "
			      "%<seq_cst%>, %<acq_rel%>, %<release%>, "
			      "%<relaxed%> or %<hint%> clause");
	    }
	  اگر (p)
	    {
	      اگر (new_code != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  اگر (openacc
		      && code == OMP_ATOMIC
		      && new_code == OMP_ATOMIC_CAPTURE_NEW)
		    code = new_code;
		  وگرنه اگر (code != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  وگرنه
		    code = new_code;
		}
	      وگرنه اگر (new_memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  اگر (memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  وگرنه
		    memory_order = new_memory_order;
		}
	      وگرنه اگر (new_capture)
		{
		  اگر (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  وگرنه
		    capture = درست;
		}
	      وگرنه اگر (new_compare)
		{
		  اگر (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  وگرنه
		    compare = درست;
		}
	      وگرنه اگر (new_weak)
		{
		  اگر (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  وگرنه
		    weak = درست;
		}
	      c_parser_consume_token (parser);
	      ادامه;
	    }
	}
      بشکن;
    }
  c_parser_skip_to_pragma_eol (parser);

  اگر (code == ERROR_MARK)
    code = OMP_ATOMIC;
  اگر (capture)
    {
      اگر (code != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      وگرنه
	code = OMP_ATOMIC_CAPTURE_NEW;
    }
  اگر (compare && code != OMP_ATOMIC && code != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = نادرست;
    }
  اگر (fail != OMP_MEMORY_ORDER_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      fail = OMP_MEMORY_ORDER_UNSPECIFIED;
    }
  اگر (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = نادرست;
    }
  اگر (openacc)
    memory_order = OMP_MEMORY_ORDER_RELAXED;
  وگرنه اگر (memory_order == OMP_MEMORY_ORDER_UNSPECIFIED)
    {
      omp_requires_mask
	= (شمارش omp_requires) (omp_requires_mask
			       | OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED);
      انتخاب ((شمارش omp_memory_order)
	      (omp_requires_mask & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER))
	{
	حالت OMP_MEMORY_ORDER_UNSPECIFIED:
	حالت OMP_MEMORY_ORDER_RELAXED:
	  memory_order = OMP_MEMORY_ORDER_RELAXED;
	  بشکن;
	حالت OMP_MEMORY_ORDER_SEQ_CST:
	  memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  بشکن;
	حالت OMP_MEMORY_ORDER_ACQUIRE:
	  اگر (code == NOP_عبارت)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  وگرنه
	    memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  بشکن;
	حالت OMP_MEMORY_ORDER_RELEASE:
	  اگر (code == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  وگرنه
	    memory_order = OMP_MEMORY_ORDER_RELEASE;
	  بشکن;
	حالت OMP_MEMORY_ORDER_ACQ_REL:
	  انتخاب (code)
	    {
	    حالت OMP_ATOMIC_READ:
	      memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	      بشکن;
	    حالت NOP_عبارت: /* atomic write */
	      memory_order = OMP_MEMORY_ORDER_RELEASE;
	      بشکن;
	    پیشفرض:
	      memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	      بشکن;
	    }
	  بشکن;
	پیشفرض:
	  gcc_unreachable ();
	}
    }
  وگرنه
    انتخاب (code)
      {
      حالت OMP_ATOMIC_READ:
	اگر (memory_order == OMP_MEMORY_ORDER_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	وگرنه اگر (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	بشکن;
      حالت NOP_عبارت: /* atomic write */
	اگر (memory_order == OMP_MEMORY_ORDER_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	وگرنه اگر (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_RELEASE;
	بشکن;
      پیشفرض:
	بشکن;
      }
  اگر (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
    memory_order
      = (شمارش omp_memory_order) (memory_order
				 | (fail << OMP_FAIL_MEMORY_ORDER_SHIFT));

  انتخاب (code)
    {
    حالت OMP_ATOMIC_READ:
    حالت NOP_عبارت: /* atomic write */
      v = c_parser_cast_expression (parser, پوچ).مقدار;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, نادرست, پوچ, درست);
      اگر (v == error_mark_گره)
	برو saw_error;
      اگر (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	برو saw_error;
      اگر (code == NOP_عبارت)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  عبارت = c_parser_expression (parser);
	  عبارت = default_function_array_read_conversion (eloc, عبارت);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  code = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_درخت;
	  rhs = c_fully_fold (عبارت.مقدار, نادرست, پوچ);
	  اگر (rhs == error_mark_گره)
	    برو saw_error;
	}
      وگرنه
	{
	  lhs = c_parser_cast_expression (parser, پوچ).مقدار;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, نادرست, پوچ, درست);
	  اگر (lhs == error_mark_گره)
	    برو saw_error;
	  اگر (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      برو done;
    حالت OMP_ATOMIC_CAPTURE_NEW:
      اگر (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_block = درست;
	}
      وگرنه اگر (compare
	       && c_parser_next_token_is_keyword (parser, RID_IF))
	بشکن;
      وگرنه
	{
	  v = c_parser_cast_expression (parser, پوچ).مقدار;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, نادرست, پوچ, درست);
	  اگر (v == error_mark_گره)
	    برو saw_error;
	  اگر (non_lvalue_p)
	    v = non_lvalue (v);
	  اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    برو saw_error;
	  اگر (compare && c_parser_next_token_is_keyword (parser, RID_IF))
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "expected expression");
	      برو saw_error;
	    }
	}
      بشکن;
    پیشفرض:
      بشکن;
    }

  /* For structured_block case we don't know yet whether
     old or new x should be captured.  */
restart:
  اگر (compare && c_parser_next_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      اگر (!parens.require_open (parser))
	برو saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_عبارت cmp_عبارت;
      اگر (r)
	{
	  cmp_عبارت = c_parser_cast_expression (parser, پوچ);
	  cmp_عبارت = default_function_array_conversion (eloc, cmp_عبارت);
	}
      وگرنه
	cmp_عبارت = c_parser_دودویی_expression (parser, پوچ, void_list_گره);
      parens.skip_until_found_close (parser);
      اگر (cmp_عبارت.مقدار == error_mark_گره)
	برو saw_error;
      اگر (r)
	{
	  اگر (!c_درخت_equal (cmp_عبارت.مقدار, unfolded_lhs))
	    برو bad_if;
	  cmp_عبارت.مقدار = rhs1;
	  rhs1 = NULL_درخت;
	  gcc_assert (درخت_CODE (cmp_عبارت.مقدار) == EQ_عبارت);
	}
      اگر (درخت_CODE (cmp_عبارت.مقدار) == EQ_عبارت)
	;
      وگرنه اگر (!structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (عبارت_LOC_OR_LOC (cmp_عبارت.مقدار, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  برو saw_error;
	}
      وگرنه اگر (درخت_CODE (cmp_عبارت.مقدار) != GT_عبارت
	       && درخت_CODE (cmp_عبارت.مقدار) != LT_عبارت)
	{
	  error_at (عبارت_LOC_OR_LOC (cmp_عبارت.مقدار, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  برو saw_error;
	}
      اگر (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	برو saw_error;

      extra_scope = درست;
      eloc = c_parser_peek_token (parser)->location;
      عبارت = c_parser_cast_expression (parser, پوچ);
      lhs = عبارت.مقدار;
      عبارت = default_function_array_conversion (eloc, عبارت);
      unfolded_lhs = عبارت.مقدار;
      lhs = c_fully_fold (lhs, نادرست, پوچ, درست);
      orig_lhs = lhs;
      اگر (lhs == error_mark_گره)
	برو saw_error;
      اگر (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      اگر (!c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  برو saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      عبارت = c_parser_عبارت_no_commas (parser, پوچ);
      rhs1 = عبارت.مقدار;

      اگر (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	برو saw_error;

      اگر (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	برو saw_error;

      extra_scope = نادرست;
      no_semicolon = درست;

      اگر (c_درخت_equal (درخت_OPERAND (cmp_عبارت.مقدار, 0), unfolded_lhs))
	{
	  اگر (درخت_CODE (cmp_عبارت.مقدار) == EQ_عبارت)
	    {
	      opcode = COND_عبارت;
	      rhs = c_fully_fold (درخت_OPERAND (cmp_عبارت.مقدار, 1),
				  نادرست, پوچ, درست);
	      rhs1 = c_fully_fold (rhs1, نادرست, پوچ, درست);
	    }
	  وگرنه اگر (c_درخت_equal (درخت_OPERAND (cmp_عبارت.مقدار, 1), rhs1))
	    {
	      opcode = (درخت_CODE (cmp_عبارت.مقدار) == GT_عبارت
			? MIN_عبارت : MAX_عبارت);
	      rhs = c_fully_fold (rhs1, نادرست, پوچ, درست);
	      rhs1 = c_fully_fold (درخت_OPERAND (cmp_عبارت.مقدار, 0),
				   نادرست, پوچ, درست);
	    }
	  وگرنه
	    برو bad_if;
	}
      وگرنه اگر (درخت_CODE (cmp_عبارت.مقدار) == EQ_عبارت)
	برو bad_if;
      وگرنه اگر (c_درخت_equal (درخت_OPERAND (cmp_عبارت.مقدار, 1), unfolded_lhs)
	       && c_درخت_equal (درخت_OPERAND (cmp_عبارت.مقدار, 0), rhs1))
	{
	  opcode = (درخت_CODE (cmp_عبارت.مقدار) == GT_عبارت
		    ? MAX_عبارت : MIN_عبارت);
	  rhs = c_fully_fold (rhs1, نادرست, پوچ, درست);
	  rhs1 = c_fully_fold (درخت_OPERAND (cmp_عبارت.مقدار, 1),
			       نادرست, پوچ, درست);
	}
      وگرنه
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  برو saw_error;
	}

      اگر (c_parser_next_token_is_keyword (parser, RID_ELSE))
	{
	  اگر (code != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_block && r == NULL_درخت)
	      || درخت_CODE (cmp_عبارت.مقدار) != EQ_عبارت)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      برو saw_error;
	    }

	  c_parser_consume_token (parser);

	  اگر (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    برو saw_error;

	  extra_scope = درست;
	  v = c_parser_cast_expression (parser, پوچ).مقدار;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, نادرست, پوچ, درست);
	  اگر (v == error_mark_گره)
	    برو saw_error;
	  اگر (non_lvalue_p)
	    v = non_lvalue (v);
	  اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    برو saw_error;

	  عبارت = c_parser_عبارت_no_commas (parser, پوچ);

	  اگر (!c_درخت_equal (عبارت.مقدار, unfolded_lhs))
	    برو bad_if;

	  اگر (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    برو saw_error;

	  اگر (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    برو saw_error;

	  extra_scope = نادرست;
	  code = OMP_ATOMIC_CAPTURE_OLD;
	  اگر (r == NULL_درخت)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_گره;
	}
      وگرنه اگر (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  برو saw_error;
	}
      وگرنه اگر (code == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_درخت
	       && v == NULL_درخت)
	code = OMP_ATOMIC;
      برو stmt_done;
    }
  eloc = c_parser_peek_token (parser)->location;
  عبارت = c_parser_cast_expression (parser, پوچ);
  lhs = عبارت.مقدار;
  عبارت = default_function_array_conversion (eloc, عبارت);
  unfolded_lhs = عبارت.مقدار;
  lhs = c_fully_fold (lhs, نادرست, پوچ, درست);
  orig_lhs = lhs;
  انتخاب (درخت_CODE (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    حالت ERROR_MARK:
    saw_error:
      c_parser_skip_to_end_of_block_or_statement (parser);
      اگر (extra_scope && c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      اگر (structured_block)
	{
	  اگر (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  وگرنه اگر (code == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      اگر (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      بازگشت;

    حالت POSTINCREMENT_عبارت:
      اگر (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    حالت PREINCREMENT_عبارت:
      lhs = درخت_OPERAND (lhs, 0);
      unfolded_lhs = NULL_درخت;
      opcode = PLUS_عبارت;
      rhs = integer_one_گره;
      اگر (compare)
	برو invalid_compare;
      بشکن;

    حالت POSTDECREMENT_عبارت:
      اگر (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    حالت PREDECREMENT_عبارت:
      lhs = درخت_OPERAND (lhs, 0);
      unfolded_lhs = NULL_درخت;
      opcode = MINUS_عبارت;
      rhs = integer_one_گره;
      اگر (compare)
	برو invalid_compare;
      بشکن;

    حالت COMPOUND_عبارت:
      اگر (درخت_CODE (درخت_OPERAND (lhs, 0)) == SAVE_عبارت
	  && درخت_CODE (درخت_OPERAND (lhs, 1)) == COMPOUND_عبارت
	  && درخت_CODE (درخت_OPERAND (درخت_OPERAND (lhs, 1), 0)) == MODIFY_عبارت
	  && درخت_OPERAND (درخت_OPERAND (lhs, 1), 1) == درخت_OPERAND (lhs, 0)
	  && C_BOOLEAN_TYPE_P (درخت_TYPE (درخت_OPERAND (درخت_OPERAND
					      (درخت_OPERAND (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = درخت_OPERAND (درخت_OPERAND (lhs, 1), 0);
      /* FALLTHRU */
    حالت MODIFY_عبارت:
      اگر (درخت_CODE (lhs) == MODIFY_عبارت
	  && C_BOOLEAN_TYPE_P (درخت_TYPE (درخت_OPERAND (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  اگر (integer_onep (درخت_OPERAND (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = درخت_OPERAND (lhs, 1);
	      lhs = درخت_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_درخت;
	      opcode = NOP_عبارت;
	      اگر (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && درخت_CODE (orig_lhs) == COMPOUND_عبارت)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      اگر (compare)
		برو invalid_compare;
	      بشکن;
	    }
	  اگر (درخت_CODE (درخت_OPERAND (lhs, 1)) == TRUTH_NOT_عبارت
	      && درخت_OPERAND (lhs, 0)
		 == درخت_OPERAND (درخت_OPERAND (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = درخت_OPERAND (lhs, 1);
	      lhs = درخت_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_درخت;
	      opcode = NOP_عبارت;
	      اگر (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && درخت_CODE (orig_lhs) == COMPOUND_عبارت)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      اگر (compare)
		برو invalid_compare;
	      بشکن;
	    }
	}
      /* FALLTHRU */
    پیشفرض:
      اگر (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      اگر (compare && !c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  برو saw_error;
	}
      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_MULT_EQ:
	  opcode = MULT_عبارت;
	  بشکن;
	حالت CPP_DIV_EQ:
	  opcode = TRUNC_DIV_عبارت;
	  بشکن;
	حالت CPP_PLUS_EQ:
	  opcode = PLUS_عبارت;
	  بشکن;
	حالت CPP_MINUS_EQ:
	  opcode = MINUS_عبارت;
	  بشکن;
	حالت CPP_LSHIFT_EQ:
	  opcode = LSHIFT_عبارت;
	  بشکن;
	حالت CPP_RSHIFT_EQ:
	  opcode = RSHIFT_عبارت;
	  بشکن;
	حالت CPP_AND_EQ:
	  opcode = BIT_AND_عبارت;
	  بشکن;
	حالت CPP_OR_EQ:
	  opcode = BIT_IOR_عبارت;
	  بشکن;
	حالت CPP_XOR_EQ:
	  opcode = BIT_XOR_عبارت;
	  بشکن;
	حالت CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  عبارت = c_parser_عبارت_no_commas (parser, پوچ, unfolded_lhs);
	  rhs1 = عبارت.مقدار;
	  انتخاب (درخت_CODE (rhs1))
	    {
	    حالت MULT_عبارت:
	    حالت TRUNC_DIV_عبارت:
	    حالت RDIV_عبارت:
	    حالت PLUS_عبارت:
	    حالت MINUS_عبارت:
	    حالت LSHIFT_عبارت:
	    حالت RSHIFT_عبارت:
	    حالت BIT_AND_عبارت:
	    حالت BIT_IOR_عبارت:
	    حالت BIT_XOR_عبارت:
	      اگر (compare)
		بشکن;
	      اگر (c_درخت_equal (درخت_OPERAND (rhs1, 0), unfolded_lhs))
		{
		  opcode = درخت_CODE (rhs1);
		  rhs = c_fully_fold (درخت_OPERAND (rhs1, 1), نادرست, پوچ,
				      درست);
		  rhs1 = c_fully_fold (درخت_OPERAND (rhs1, 0), نادرست, پوچ,
				       درست);
		  برو stmt_done;
		}
	      اگر (c_درخت_equal (درخت_OPERAND (rhs1, 1), unfolded_lhs))
		{
		  opcode = درخت_CODE (rhs1);
		  rhs = c_fully_fold (درخت_OPERAND (rhs1, 0), نادرست, پوچ,
				      درست);
		  rhs1 = c_fully_fold (درخت_OPERAND (rhs1, 1), نادرست, پوچ,
				       درست);
		  swapped = !commutative_درخت_code (opcode);
		  برو stmt_done;
		}
	      بشکن;
	    حالت COND_عبارت:
	      اگر (!compare)
		بشکن;
	      اگر (درخت_CODE (درخت_OPERAND (rhs1, 0)) != GT_عبارت
		  && درخت_CODE (درخت_OPERAND (rhs1, 0)) != LT_عبارت
		  && درخت_CODE (درخت_OPERAND (rhs1, 0)) != EQ_عبارت)
		بشکن;
	      اگر (!درخت_OPERAND (rhs1, 1))
		بشکن;
	      اگر (!c_درخت_equal (درخت_OPERAND (rhs1, 2), unfolded_lhs))
		بشکن;
	      اگر (c_درخت_equal (درخت_OPERAND (درخت_OPERAND (rhs1, 0), 0),
				unfolded_lhs))
		{
		  اگر (درخت_CODE (درخت_OPERAND (rhs1, 0)) == EQ_عبارت)
		    {
		      opcode = COND_عبارت;
		      rhs = c_fully_fold (درخت_OPERAND (درخت_OPERAND (rhs1,
								      0), 1),
					  نادرست, پوچ, درست);
		      rhs1 = c_fully_fold (درخت_OPERAND (rhs1, 1), نادرست,
					   پوچ, درست);
		      برو stmt_done;
		    }
		  اگر (c_درخت_equal (درخت_OPERAND (درخت_OPERAND (rhs1, 0), 1),
				    درخت_OPERAND (rhs1, 1)))
		    {
		      opcode = (درخت_CODE (درخت_OPERAND (rhs1, 0)) == GT_عبارت
				? MIN_عبارت : MAX_عبارت);
		      rhs = c_fully_fold (درخت_OPERAND (rhs1, 1), نادرست, پوچ,
					  درست);
		      rhs1 = c_fully_fold (درخت_OPERAND (درخت_OPERAND (rhs1,
								       0), 0),
					   نادرست, پوچ, درست);
		      برو stmt_done;
		    }
		}
	      وگرنه اگر (درخت_CODE (درخت_OPERAND (rhs1, 0)) == EQ_عبارت)
		بشکن;
	      وگرنه اگر (c_درخت_equal (درخت_OPERAND (درخت_OPERAND (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  اگر (c_درخت_equal (درخت_OPERAND (درخت_OPERAND (rhs1, 0), 0),
				    درخت_OPERAND (rhs1, 1)))
		    {
		      opcode = (درخت_CODE (درخت_OPERAND (rhs1, 0)) == GT_عبارت
				? MAX_عبارت : MIN_عبارت);
		      rhs = c_fully_fold (درخت_OPERAND (rhs1, 1), نادرست, پوچ,
					  درست);
		      rhs1 = c_fully_fold (درخت_OPERAND (درخت_OPERAND (rhs1,
								       0), 1),
					   نادرست, پوچ, درست);
		      برو stmt_done;
		    }
		}
	      بشکن;
	    حالت EQ_عبارت:
	      اگر (!compare
		  || code != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_block
		  || v
		  || r)
		بشکن;
	      اگر (c_parser_next_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_درخت;
		  c_parser_consume_token (parser);
		  برو restart;
		}
	      بشکن;
	    حالت ERROR_MARK:
	      برو saw_error;
	    پیشفرض:
	      بشکن;
	    }
	  اگر (c_parser_peek_token (parser)->type == CPP_SEMICOLON)
	    {
	      اگر (structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
		{
		  code = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_درخت;
		  عبارت = default_function_array_read_conversion (eloc, عبارت);
		  unfolded_lhs1 = عبارت.مقدار;
		  lhs1 = c_fully_fold (unfolded_lhs1, نادرست, پوچ, درست);
		  rhs1 = NULL_درخت;
		  c_parser_consume_token (parser);
		  برو restart;
		}
	      اگر (structured_block && !compare)
		{
		  opcode = NOP_عبارت;
		  عبارت = default_function_array_read_conversion (eloc, عبارت);
		  rhs = c_fully_fold (عبارت.مقدار, نادرست, پوچ, درست);
		  rhs1 = NULL_درخت;
		  برو stmt_done;
		}
	    }
	  c_parser_error (parser, "invalid form of %<#pragma omp atomic%>");
	  برو saw_error;
	پیشفرض:
	  c_parser_error (parser,
			  "invalid operator for %<#pragma omp atomic%>");
	  برو saw_error;
	}

      /* Arrange to pass the location of the assignment operator to
	 c_finish_omp_atomic.  */
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      عبارت = c_parser_expression (parser);
      عبارت = default_function_array_read_conversion (eloc, عبارت);
      rhs = عبارت.مقدار;
      rhs = c_fully_fold (rhs, نادرست, پوچ, درست);
      بشکن;
    }
stmt_done:
  اگر (structured_block && code == OMP_ATOMIC_CAPTURE_NEW && r == NULL_درخت)
    {
      اگر (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	برو saw_error;
      no_semicolon = نادرست;
      v = c_parser_cast_expression (parser, پوچ).مقدار;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, نادرست, پوچ, درست);
      اگر (v == error_mark_گره)
	برو saw_error;
      اگر (non_lvalue_p)
	v = non_lvalue (v);
      اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	برو saw_error;
      eloc = c_parser_peek_token (parser)->location;
      عبارت = c_parser_cast_expression (parser, پوچ);
      lhs1 = عبارت.مقدار;
      عبارت = default_function_array_read_conversion (eloc, عبارت);
      unfolded_lhs1 = عبارت.مقدار;
      lhs1 = c_fully_fold (lhs1, نادرست, پوچ, درست);
      اگر (lhs1 == error_mark_گره)
	برو saw_error;
      اگر (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  اگر (structured_block)
    {
      اگر (!no_semicolon)
	c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
done:
  اگر (weak && opcode != COND_عبارت)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = نادرست;
    }
  اگر (unfolded_lhs && unfolded_lhs1
      && !c_درخت_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_گره;
    }
  وگرنه
    stmt = c_finish_omp_atomic (loc, code, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, memory_order, weak);
  اگر (stmt != error_mark_گره)
    add_stmt (stmt);

  اگر (!structured_block && !no_semicolon)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}


/* OpenMP 2.5:
   # pragma omp barrier new-line
*/

ایستا تهی
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

ایستا درخت
c_parser_omp_critical (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت stmt, name = NULL_درخت, clauses = NULL_درخت;

  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      اگر (c_parser_next_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->مقدار;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      وگرنه
	c_parser_error (parser, "expected identifier");

      اگر (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_MASK,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_block (parser, if_p);
  بازگشت c_finish_omp_critical (loc, stmt, name, clauses);
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

ایستا تهی
c_parser_omp_depobj (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  matching_parens parens;
  اگر (!parens.require_open (parser))
    {
      c_parser_skip_to_pragma_eol (parser);
      بازگشت;
    }

  درخت depobj = c_parser_عبارت_no_commas (parser, پوچ).مقدار;
  اگر (depobj != error_mark_گره)
    {
      اگر (!lvalue_p (depobj))
	{
	  error_at (عبارت_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_گره;
	}
      وگرنه
	{
	  درخت addr = build_unary_op (عبارت_LOC_OR_LOC (depobj, loc), ADDR_عبارت,
				      depobj, نادرست);
	  اگر (addr == error_mark_گره)
	    depobj = error_mark_گره;
	  وگرنه
	    depobj = build_indirect_ref (عبارت_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_STAR);
	}
    }

  parens.skip_until_found_close (parser);
  درخت clause = NULL_درخت;
  شمارش omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_INVALID;
  اگر (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);

      c_parser_consume_token (parser);
      اگر (!strcmp ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_درخت, c_loc);
	  clause = c_finish_omp_clauses (clause, C_ORT_OMP);
	  اگر (!clause)
	    clause = error_mark_گره;
	}
      وگرنه اگر (!strcmp ("destroy", p))
	{
	  matching_parens c_parens;
	  kind = OMP_CLAUSE_DEPEND_LAST;
	  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      درخت destobj = c_parser_عبارت_no_commas (parser, پوچ).مقدار;
	      اگر (!lvalue_p (destobj))
		error_at (عبارت_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      وگرنه اگر (depobj != error_mark_گره
		       && !operand_equal_p (destobj, depobj,
					    OEP_MATCH_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (عبارت_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_found_close (parser);
	    }
	}
      وگرنه اگر (!strcmp ("update", p))
	{
	  matching_parens c_parens;
	  اگر (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      اگر (c_parser_next_token_is (parser, CPP_NAME))
		{
		  ثابت نویسه *p2
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);

		  c_parser_consume_token (parser);
		  اگر (!strcmp ("in", p2))
		    kind = OMP_CLAUSE_DEPEND_IN;
		  وگرنه اگر (!strcmp ("out", p2))
		    kind = OMP_CLAUSE_DEPEND_OUT;
		  وگرنه اگر (!strcmp ("inout", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUT;
		  وگرنه اگر (!strcmp ("mutexinoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  وگرنه اگر (!strcmp ("inoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      اگر (kind == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_گره;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_found_close (parser);
	    }
	  وگرنه
	    clause = error_mark_گره;
	}
    }
  اگر (!clause && kind == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_گره;
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

ایستا تهی
c_parser_omp_flush (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  شمارش memmodel mo = MEMMODEL_LAST;
  اگر (c_parser_next_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);

      اگر (!strcmp (p, "seq_cst"))
	mo = MEMMODEL_SEQ_CST;
      وگرنه اگر (!strcmp (p, "acq_rel"))
	mo = MEMMODEL_ACQ_REL;
      وگرنه اگر (!strcmp (p, "release"))
	mo = MEMMODEL_RELEASE;
      وگرنه اگر (!strcmp (p, "acquire"))
	mo = MEMMODEL_ACQUIRE;
      وگرنه
	error_at (c_parser_peek_token (parser)->location,
		  "expected %<seq_cst%>, %<acq_rel%>, %<release%> or "
		  "%<acquire%>");
      c_parser_consume_token (parser);
    }
  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      اگر (mo != MEMMODEL_LAST)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, پوچ);
    }
  وگرنه اگر (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_to_pragma_eol (parser);

  c_finish_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

ایستا منطقی
c_parser_omp_section_scan (c_parser *parser, ثابت نویسه *directive,
			   منطقی tentative)
{
  اگر (!c_parser_nth_token_starts_std_attributes (parser, 1))
    بازگشت نادرست;
  unsigned صحیح n = 3;
  اگر (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    بازگشت نادرست;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  اگر (token->type != CPP_CLOSE_SQUARE)
    بازگشت نادرست;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  اگر (token->type != CPP_CLOSE_SQUARE)
    بازگشت نادرست;
  اگر (n < 9)
    بازگشت نادرست;
  اگر (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      درخت first = c_parser_peek_nth_token_raw (parser, 3)->مقدار;
      درخت second = c_parser_peek_nth_token_raw (parser, 5)->مقدار;
      اگر (strcmp (IDENTIFIER_POINTER (first), "directive")
	  && strcmp (IDENTIFIER_POINTER (first), "__directive__"))
	بازگشت نادرست;
      اگر (strcmp (IDENTIFIER_POINTER (second), directive))
	بازگشت نادرست;
    }
  اگر (tentative)
    بازگشت درست;
  location_t first_loc = c_parser_peek_token (parser)->location;
  location_t last_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t میانه_loc = UNKNOWN_LOCATION;
  درخت std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  منطقی seen = نادرست;
  صحیح cnt = 0;
  برای (درخت attr = std_attrs; attr; attr = درخت_CHAIN (attr))
    اگر (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	برای (درخت a = درخت_مقدار (attr); a; a = درخت_CHAIN (a))
	  {
	    درخت d = درخت_مقدار (a);
	    gcc_assert (درخت_CODE (d) == C_TOKEN_VEC);
	    c_token *first = C_TOKEN_VEC_TOKENS (d)->address ();
	    cnt++;
	    اگر (first->type == CPP_NAME
		&& strcmp (IDENTIFIER_POINTER (first->مقدار),
			   directive) == 0)
	      {
		seen = درست;
		اگر (میانه_loc == UNKNOWN_LOCATION)
		  میانه_loc = first->location;
	      }
	  }
      }
  اگر (!seen)
    بازگشت نادرست;
  اگر (cnt != 1 || درخت_CHAIN (std_attrs))
    {
      error_at (make_location (first_loc, last_loc, میانه_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      بازگشت نادرست;
    }
  c_parser_handle_statement_omp_attributes (parser, std_attrs, پوچ);
  بازگشت درست;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

ایستا درخت
c_parser_omp_structured_block_sequence (c_parser *parser,
					شمارش pragma_kind kind)
{
  درخت stmt = افزودن_stmt_list ();
  c_parser_statement (parser, پوچ);
  انجامبده
    {
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	بشکن;
      اگر (c_parser_next_token_is (parser, CPP_EOF))
	بشکن;

      اگر (kind != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_kind == kind)
	بشکن;

      اگر (kind != PRAGMA_NONE
	  && c_parser_omp_section_scan (parser,
					kind == PRAGMA_OMP_SCAN
					? "scan" : "section", نادرست))
	بشکن;

      c_parser_statement (parser, پوچ);
    }
  وقتی (1);
  بازگشت برداشت_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

ایستا تهی
c_parser_omp_scan_loop_body (c_parser *parser, منطقی open_brace_parsed)
{
  درخت substmt;
  location_t loc;
  درخت clauses = NULL_درخت;
  منطقی found_scan = نادرست;

  loc = c_parser_peek_token (parser)->location;
  اگر (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = نادرست;
      بازگشت;
    }

  اگر (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SCAN)
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_OMP_SCAN);
  وگرنه
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_گره, substmt, NULL_درخت);
  SET_عبارت_LOCATION (substmt, loc);
  add_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  اگر (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SCAN)
    {
      شمارش omp_clause_code clause = OMP_CLAUSE_ERROR;
      found_scan = درست;

      c_parser_consume_pragma (parser);

      اگر (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      اگر (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ثابت نویسه *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
	  اگر (strcmp (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  وگرنه اگر (strcmp (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      اگر (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_درخت);
	}
      وگرنه
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_to_pragma_eol (parser);
    }
  وگرنه
    error ("expected %<#pragma omp scan%>");

  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  اگر (!c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_NONE);
  وگرنه
    {
      اگر (found_scan)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_گره, substmt, clauses);
  SET_عبارت_LOCATION (substmt, loc);
  add_stmt (substmt);

  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
ایستا منطقی
c_parser_omp_next_tokens_can_be_canon_loop (c_parser *parser,
					    شمارش درخت_code code,
					    منطقی error_p)
{
  اگر (code == OACC_LOOP)
    {
      اگر (c_parser_next_token_is_keyword (parser, RID_FOR))
	بازگشت درست;
      اگر (error_p)
	c_parser_error (parser, "for statement expected");
    }
  وگرنه
    {
      اگر (c_parser_next_token_is_keyword (parser, RID_FOR))
	بازگشت درست;

      اگر (c_parser_next_token_is (parser, CPP_PRAGMA))
	انتخاب (c_parser_peek_token (parser)->pragma_kind)
	  {
	  حالت PRAGMA_OMP_UNROLL:
	  حالت PRAGMA_OMP_TILE:
	    بازگشت درست;
	  پیشفرض:
	    بشکن;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      size_t n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      اگر (token->type == CPP_NAME
	  && C_IS_RESERVED_WORD (token->مقدار)
	  && C_RID_CODE (token->مقدار) == RID_FOR)
	بازگشت درست;
      اگر (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  بازگشت نادرست;
}

ایستا درخت c_parser_omp_tile (location_t, c_parser *, منطقی *);
ایستا درخت c_parser_omp_unroll (location_t, c_parser *, منطقی *);

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

ایستا درخت
c_parser_omp_loop_nest (c_parser *parser, منطقی *if_p)
{
  درخت decl = NULL_درخت, cond = NULL_درخت, incr = NULL_درخت, init = NULL_درخت;
  درخت body = NULL_درخت;
  matching_parens parens;
  منطقی moreloops;
  unsigned نویسه save_in_statement;
  درخت loop_scope;
  location_t loc;
  ساختار omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  صحیح depth = omp_for_parse_state->depth;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  اگر (c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      درخت std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_attributes (parser, std_attrs, پوچ);
      اگر (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  اگر (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      درخت transform = NULL_درخت, sizes, body = NULL_درخت;
      صحیح شمار = 0;
      انتخاب (c_parser_peek_token (parser)->pragma_kind)
	{
	حالت PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = افزودن_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = برداشت_stmt_list (body);
	  اگر (transform == NULL_درخت || transform == error_mark_گره)
	    {
	      transform = error_mark_گره;
	      بشکن;
	    }
	  gcc_assert (درخت_CODE (transform) == OMP_UNROLL);
	  اگر (omp_find_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      اگر (omp_for_parse_state->شمار - depth > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->شمار - depth);
		  transform = error_mark_گره;
		}
	      وگرنه
		شمار = 1;
	    }
	  وگرنه
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_گره;
	    }
	  بشکن;
	حالت PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = افزودن_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = برداشت_stmt_list (body);
	  اگر (transform == NULL_درخت || transform == error_mark_گره)
	    {
	      transform = error_mark_گره;
	      بشکن;
	    }
	  gcc_assert (درخت_CODE (transform) == OMP_TILE);
	  sizes = omp_find_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  شمار = list_length (OMP_CLAUSE_SIZES_LIST (sizes));
	  اگر (depth + شمار < omp_for_parse_state->شمار)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			شمار, omp_for_parse_state->شمار - depth);
	      transform = error_mark_گره;
	    }
	  بشکن;
	پیشفرض:
	  c_parser_pragma (parser, pragma_stmt, پوچ, void_list_گره);
	  بشکن;
	}
      اگر (transform == NULL_درخت)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      اگر (transform == NULL_درخت || transform == error_mark_گره)
	{
	  omp_for_parse_state->fail = درست;
	  بازگشت NULL_درخت;
	}
      برای (شمار = omp_for_parse_state->شمار; depth < شمار; ++depth)
	{
	  درخت_VEC_ELT (omp_for_parse_state->declv, depth) = NULL_درخت;
	  درخت_VEC_ELT (omp_for_parse_state->initv, depth) = NULL_درخت;
	  درخت_VEC_ELT (omp_for_parse_state->condv, depth) = NULL_درخت;
	  درخت_VEC_ELT (omp_for_parse_state->incrv, depth) = NULL_درخت;
	}
      omp_for_parse_state->want_nested_loop = نادرست;
      بازگشت body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_in_statement = in_statement;
  in_statement = IN_OMP_BLOCK;

  /* We are not in intervening code now.  */
  omp_for_parse_state->in_intervening_code = نادرست;

  اگر (!parens.require_open (parser))
    {
      omp_for_parse_state->fail = درست;
      بازگشت NULL_درخت;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (درست);

  /* Parse the initialization declaration or expression.  */
  اگر (c_parser_next_tokens_start_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      درخت this_pre_body = افزودن_stmt_list ();
      c_in_omp_for = درست;
      c_parser_declaration_or_fndef (parser, درست, درست, درست, درست, درست,
				     نادرست);
      c_in_omp_for = نادرست;
      this_pre_body = برداشت_stmt_list (this_pre_body);
      append_to_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      اگر (decl == پوچ)
	برو error_init;
      اگر (DECL_INITIAL (decl) == error_mark_گره)
	decl = error_mark_گره;
      init = decl;
    }
  وگرنه اگر (c_parser_next_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      ساختار c_عبارت decl_exp;
      ساختار c_عبارت init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_expression (parser);
      decl = decl_exp.مقدار;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_عبارت_no_commas (parser, پوچ);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_in_omp_for = درست;
      init = build_modify_عبارت (init_loc, decl, decl_exp.original_type,
				NOP_عبارت, init_loc, init_exp.مقدار,
				init_exp.original_type);
      c_in_omp_for = نادرست;
      init = c_process_عبارت_stmt (init_loc, init);

      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  وگرنه
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->fail = درست;
      برو parse_next;
    }

  /* Parse the loop condition.  */
  اگر (c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_in_omp_for = درست;
      ساختار c_عبارت cond_عبارت
	= c_parser_دودویی_expression (parser, پوچ, NULL_درخت);
      c_in_omp_for = نادرست;

      cond = cond_عبارت.مقدار;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      انتخاب (cond_عبارت.original_code)
	{
	حالت GT_عبارت:
	حالت GE_عبارت:
	حالت LT_عبارت:
	حالت LE_عبارت:
	  بشکن;
	حالت NE_عبارت:
	  اگر (omp_for_parse_state->code != OACC_LOOP)
	    بشکن;
	  /* FALLTHRU.  */
	پیشفرض:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_عبارت, boolean_type_گره, error_mark_گره);
	  بشکن;
	}
      protected_set_عبارت_location (cond, cond_loc);
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  اگر (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_عبارت_stmt (incr_loc,
				  c_parser_expression (parser).مقدار);
    }
  parens.skip_until_found_close (parser);

  اگر (decl == پوچ || decl == error_mark_گره || init == error_mark_گره)
    omp_for_parse_state->fail = درست;
  وگرنه
    {
      درخت_VEC_ELT (omp_for_parse_state->declv, depth) = decl;
      درخت_VEC_ELT (omp_for_parse_state->initv, depth) = init;
      درخت_VEC_ELT (omp_for_parse_state->condv, depth) = cond;
      درخت_VEC_ELT (omp_for_parse_state->incrv, depth) = incr;
    }

parse_next:
  moreloops = depth < omp_for_parse_state->شمار - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  اگر (moreloops
      && c_parser_omp_next_tokens_can_be_canon_loop (parser,
						     omp_for_parse_state->code,
						     نادرست))
    {
      omp_for_parse_state->depth++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->depth--;
    }
  وگرنه اگر (moreloops && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* This is the open brace in the loop-body grammar production.  Rather
	 than trying to special-case braces, just parse it as a compound
	 statement and handle the nested loop-body case there.  Note that
	 when we see a further open brace inside the compound statement
	 loop-body, we don't know whether it is the start of intervening
	 code that is a compound statement, or a level of braces
	 surrounding a nested loop-body.  Use the WANT_NESTED_LOOP state
	 bit to ensure we have only one nested loop at each level.  */
      omp_for_parse_state->in_intervening_code = درست;
      body = c_parser_compound_statement (parser, پوچ);
      omp_for_parse_state->in_intervening_code = نادرست;
      اگر (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = درست;
	}
      if_p = پوچ;
    }
  وگرنه
    {
      /* This is the final-loop-body case in the grammar: we have
	 something that is not a FOR and not an open brace.  */
      اگر (moreloops)
	{
	  /* If we were expecting a nested loop, give an error and mark
	     that parsing has failed, and try to recover by parsing the
	     body as regular code without further collapsing.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = درست;
	}
      in_statement = IN_OMP_FOR;
      parser->omp_for_parse_state = پوچ;
      body = افزودن_stmt_list ();
      اگر (omp_for_parse_state->inscan)
	c_parser_omp_scan_loop_body (parser, نادرست);
      وگرنه
	add_stmt (c_parser_c99_block_statement (parser, if_p));
      body = برداشت_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  in_statement = save_in_statement;
  omp_for_parse_state->want_nested_loop = نادرست;
  omp_for_parse_state->in_intervening_code = درست;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  اگر (body)
    add_stmt (body);
  body = c_end_compound_stmt (loc, loop_scope, درست);
  اگر (decl && درخت_CODE (body) == BIND_عبارت)
    {
      درخت t = BIND_عبارت_VARS (body);
      درخت prev = NULL_درخت, next = NULL_درخت;
      وقتی (t)
	{
	  next = DECL_CHAIN (t);
	  اگر (t == decl)
	    {
	      اگر (prev)
		DECL_CHAIN (prev) = next;
	      وگرنه
		{
		  BIND_عبارت_VARS (body) = next;
		  BLOCK_VARS (BIND_عبارت_BLOCK (body)) = next;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      بشکن;
	    }
	  وگرنه
	    {
	      prev = t;
	      t = next;
	    }
	}
      اگر (BIND_عبارت_VARS (body) == NULL_درخت)
	body = BIND_عبارت_BODY (body);
    }

  بازگشت body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

ایستا درخت
c_parser_omp_for_loop (location_t loc, c_parser *parser, شمارش درخت_code code,
		       درخت clauses, درخت *cclauses, منطقی *if_p)
{
  درخت body, stmt, cl;
  درخت ret = NULL_درخت;
  درخت ordered_cl = NULL_درخت;
  صحیح i, collapse = 1, ordered = 0, شمار;
  منطقی oacc_tiling = نادرست;
  منطقی inscan = نادرست;
  ساختار omp_for_parse_data data;
  ساختار omp_for_parse_data *save_data = parser->omp_for_parse_state;

  برای (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    اگر (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = درخت_to_shwi (OMP_CLAUSE_COLLAPSE_عبارت (cl));
    وگرنه اگر (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = درست;
	collapse = list_length (OMP_CLAUSE_TILE_LIST (cl));
      }
    وگرنه اگر (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_SIZES)
      collapse = list_length (OMP_CLAUSE_SIZES_LIST (cl));
    وگرنه اگر (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_عبارت (cl))
      {
	ordered_cl = cl;
	ordered = درخت_to_shwi (OMP_CLAUSE_ORDERED_عبارت (cl));
      }
    وگرنه اگر (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (code == OMP_SIMD || code == OMP_FOR))
      inscan = درست;

  اگر (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_عبارت (ordered_cl)
	= build_int_cst (integer_type_گره, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  شمار = ordered ? ordered : collapse;

  اگر (!c_parser_omp_next_tokens_can_be_canon_loop (parser, code, درست))
    بازگشت پوچ;

  /* Initialize parse state for recursive descent.  */
  data.declv = make_درخت_vec (شمار);
  data.initv = make_درخت_vec (شمار);
  data.condv = make_درخت_vec (شمار);
  data.incrv = make_درخت_vec (شمار);
  data.pre_body = NULL_درخت;
  data.bindings = NULL_درخت;
  data.for_loc = c_parser_peek_token (parser)->location;
  data.شمار = شمار;
  data.depth = 0;
  data.want_nested_loop = درست;
  data.ordered = ordered > 0;
  data.in_intervening_code = نادرست;
  data.perfect_nesting_fail = نادرست;
  data.fail = نادرست;
  data.inscan = inscan;
  data.saw_intervening_code = نادرست;
  data.code = code;
  parser->omp_for_parse_state = &data;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  برای (درخت t = data.bindings; t; )
    {
      درخت n = درخت_CHAIN (t);
      درخت_CHAIN (t) = NULL_درخت;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  اگر (!data.fail)
    {
      c_in_omp_for = درست;
      stmt = c_finish_omp_for (loc, code, data.declv, پوچ, data.initv,
			       data.condv, data.incrv,
			       body, data.pre_body, درست);
      c_in_omp_for = نادرست;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      اگر (stmt && !c_omp_check_loop_iv (stmt, data.declv, پوچ))
	stmt = NULL_درخت;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      اگر (data.saw_intervening_code
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, پوچ))
	stmt = NULL_درخت;

      اگر (stmt)
	{
	  add_stmt (stmt);

	  برای (i = 0; i < درخت_VEC_LENGTH (OMP_FOR_INIT (stmt)); i++)
	    {
	      درخت init = درخت_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      اگر (init == NULL_درخت)
		بشکن;
	      gcc_assert (درخت_CODE (init) == MODIFY_عبارت);
	      درخت decl = درخت_OPERAND (init, 0);
	      درخت cond = درخت_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (درخت_OPERAND (cond, 0) == decl);

	      درخت op0 = درخت_OPERAND (init, 1);
	      اگر (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || درخت_CODE (op0) != درخت_VEC)
		درخت_OPERAND (init, 1) = c_fully_fold (op0, نادرست, پوچ);
	      وگرنه
		{
		  درخت_VEC_ELT (op0, 1)
		    = c_fully_fold (درخت_VEC_ELT (op0, 1), نادرست, پوچ);
		  درخت_VEC_ELT (op0, 2)
		    = c_fully_fold (درخت_VEC_ELT (op0, 2), نادرست, پوچ);
		}

	      درخت op1 = درخت_OPERAND (cond, 1);
	      اگر (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || درخت_CODE (op1) != درخت_VEC)
		درخت_OPERAND (cond, 1) = c_fully_fold (op1, نادرست, پوچ);
	      وگرنه
		{
		  درخت_VEC_ELT (op1, 1)
		    = c_fully_fold (درخت_VEC_ELT (op1, 1), نادرست, پوچ);
		  درخت_VEC_ELT (op1, 2)
		    = c_fully_fold (درخت_VEC_ELT (op1, 2), نادرست, پوچ);
		}
	    }

	  اگر (cclauses != پوچ
	      && cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL] != پوچ)
	    {
	      درخت *c;
	      برای (c = &cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL]; *c ; )
		اگر (OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		وگرنه
		  {
		    برای (i = 0; i < شمار; i++)
		      اگر (درخت_VEC_ELT (data.declv, i) == OMP_CLAUSE_DECL (*c))
			بشکن;
		    اگر (i == شمار)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    وگرنه اگر (OMP_CLAUSE_CODE (*c) == OMP_CLAUSE_FIRSTPRIVATE)
		      {
			error_at (loc,
				  "iteration variable %qD should not be firstprivate",
				  OMP_CLAUSE_DECL (*c));
			*c = OMP_CLAUSE_CHAIN (*c);
		      }
		    وگرنه
		      {
			/* Move lastprivate (decl) clause to
			   OMP_FOR_CLAUSES.  */
			درخت l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			اگر (code == OMP_SIMD)
			  {
			    OMP_CLAUSE_CHAIN (l)
			      = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
			    cclauses[C_OMP_CLAUSE_SPLIT_FOR] = l;
			  }
			وگرنه
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
  بازگشت ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

ایستا تهی
omp_split_clauses (location_t loc, شمارش درخت_code code,
		   omp_clause_mask mask, درخت clauses, درخت *cclauses)
{
  صحیح i;
  c_omp_split_clauses (loc, code, mask, clauses, cclauses);
  برای (i = 0; i < C_OMP_CLAUSE_SPLIT_شمار; i++)
    اگر (cclauses[i])
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

ایستا درخت
c_parser_omp_loop (location_t loc, c_parser *parser,
		   نویسه *p_name, omp_clause_mask mask, درخت *cclauses,
		   منطقی *if_p)
{
  درخت block, clauses, ret;

  strcat (p_name, " loop");
  mask |= OMP_LOOP_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == پوچ);
  اگر (cclauses)
    {
      omp_split_clauses (loc, OMP_LOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_LOOP];
    }

  block = c_begin_compound_stmt (درست);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, درست);
  add_stmt (block);

  بازگشت ret;
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

ایستا درخت
c_parser_omp_simd (location_t loc, c_parser *parser,
		   نویسه *p_name, omp_clause_mask mask, درخت *cclauses,
		   منطقی *if_p)
{
  درخت block, clauses, ret;

  strcat (p_name, " simd");
  mask |= OMP_SIMD_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == پوچ);
  اگر (cclauses)
    {
      omp_split_clauses (loc, OMP_SIMD, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SIMD];
    }

  block = c_begin_compound_stmt (درست);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, درست);
  add_stmt (block);

  بازگشت ret;
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

ایستا درخت
c_parser_omp_for (location_t loc, c_parser *parser,
		  نویسه *p_name, omp_clause_mask mask, درخت *cclauses,
		  منطقی *if_p)
{
  درخت block, clauses, ret;

  strcat (p_name, " for");
  mask |= OMP_FOR_CLAUSE_MASK;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  اگر (cclauses && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  اگر ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);

      اگر (strcmp (p, "simd") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_SPLIT_شمار];
	  اگر (cclauses == پوچ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    بازگشت c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (درست);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, درست);
	  اگر (ret == NULL_درخت)
	    بازگشت ret;
	  ret = make_گره (OMP_FOR);
	  درخت_TYPE (ret) = void_type_گره;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
	  SET_عبارت_LOCATION (ret, loc);
	  add_stmt (ret);
	  بازگشت ret;
	}
    }
  اگر (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, نادرست);
      بازگشت NULL_درخت;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  اگر ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINEAR);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == پوچ);
  اگر (cclauses)
    {
      omp_split_clauses (loc, OMP_FOR, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
    }

  block = c_begin_compound_stmt (درست);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, درست);
  add_stmt (block);

  بازگشت ret;
}

ایستا درخت c_parser_omp_taskloop (location_t, c_parser *, نویسه *,
				   omp_clause_mask, درخت *, منطقی *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

ایستا درخت
c_parser_omp_master (location_t loc, c_parser *parser,
		     نویسه *p_name, omp_clause_mask mask, درخت *cclauses,
		     منطقی *if_p, location_t master_loc)
{
  درخت block, clauses, ret;
  gcc_rich_location richloc (loc);
  اگر (master_loc != UNKNOWN_LOCATION)
    richloc.add_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  strcat (p_name, " master");

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);

      اگر (strcmp (p, "taskloop") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_SPLIT_شمار];
	  اگر (cclauses == پوچ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    بازگشت c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (درست);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, درست);
	  اگر (ret == NULL_درخت)
	    بازگشت ret;
	  ret = c_finish_omp_master (loc, block);
	  OMP_MASTER_COMBINED (ret) = 1;
	  بازگشت ret;
	}
    }
  اگر (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, نادرست);
      بازگشت NULL_درخت;
    }

  اگر (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, mask, p_name, نادرست);
      omp_split_clauses (loc, OMP_MASTER, mask, clauses, cclauses);
    }
  وگرنه
    c_parser_skip_to_pragma_eol (parser);

  بازگشت c_finish_omp_master (loc, c_parser_omp_structured_block (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#define OMP_MASKED_CLAUSE_MASK					\
	(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FILTER)

ایستا درخت
c_parser_omp_masked (location_t loc, c_parser *parser,
		     نویسه *p_name, omp_clause_mask mask, درخت *cclauses,
		     منطقی *if_p)
{
  درخت block, clauses, ret;

  strcat (p_name, " masked");
  mask |= OMP_MASKED_CLAUSE_MASK;

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);

      اگر (strcmp (p, "taskloop") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_SPLIT_شمار];
	  اگر (cclauses == پوچ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    بازگشت c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (درست);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, درست);
	  اگر (ret == NULL_درخت)
	    بازگشت ret;
	  ret = c_finish_omp_masked (loc, block,
				     cclauses[C_OMP_CLAUSE_SPLIT_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  بازگشت ret;
	}
    }
  اگر (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, نادرست);
      بازگشت NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == پوچ);
  اگر (cclauses)
    {
      omp_split_clauses (loc, OMP_MASKED, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_MASKED];
    }

  بازگشت c_finish_omp_masked (loc, c_parser_omp_structured_block (parser,
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

ایستا تهی
c_parser_omp_interop (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  درخت clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_MASK,
					   "#pragma omp interop");
  درخت stmt = make_گره (OMP_INTEROP);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  SET_عبارت_LOCATION (stmt, loc);
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

ایستا منطقی
c_parser_omp_ordered (c_parser *parser, شمارش pragma_context context,
		      منطقی *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  اگر (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, نادرست);
      بازگشت نادرست;
    }

  صحیح n = 1;
  اگر (c_parser_next_token_is (parser, CPP_COMMA))
    n = 2;

  اگر (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      ثابت نویسه *p
	= IDENTIFIER_POINTER (c_parser_peek_nth_token (parser, n)->مقدار);

      اگر (!strcmp ("depend", p) || !strcmp ("doacross", p))
	{
	  اگر (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_to_pragma_eol (parser, نادرست);
	      بازگشت نادرست;
	    }
	  اگر (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_to_pragma_eol (parser, نادرست);
	      بازگشت درست;
	    }

	  درخت clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_MASK,
					"#pragma omp ordered");
	  c_finish_omp_ordered (loc, clauses, NULL_درخت);
	  بازگشت نادرست;
	}
    }

  درخت clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_MASK,
					   "#pragma omp ordered");

  اگر (!flag_openmp	/* flag_openmp_simd  */
      && omp_find_clause (clauses, OMP_CLAUSE_SIMD) == NULL_درخت)
    بازگشت نادرست;

  c_finish_omp_ordered (loc, clauses,
			c_parser_omp_structured_block (parser, if_p));
  بازگشت درست;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

ایستا درخت
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  درخت stmt, substmt;
  منطقی error_suppress = نادرست;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  اگر (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = نادرست;
      بازگشت NULL_درخت;
    }

  stmt = افزودن_stmt_list ();

  اگر (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_scan (parser, "section", درست))
    {
      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_گره, substmt);
      SET_عبارت_LOCATION (substmt, loc);
      add_stmt (substmt);
    }

  وقتی (1)
    {
      اگر (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	بشکن;
      اگر (c_parser_next_token_is (parser, CPP_EOF))
	بشکن;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_scan (parser, "section", نادرست);
      اگر (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser);
	  error_suppress = نادرست;
	}
      وگرنه اگر (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = درست;
	}

      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_گره, substmt);
      SET_عبارت_LOCATION (substmt, loc);
      add_stmt (substmt);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = برداشت_stmt_list (stmt);

  stmt = make_گره (OMP_SECTIONS);
  SET_عبارت_LOCATION (stmt, sections_loc);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_SECTIONS_BODY (stmt) = substmt;

  بازگشت add_stmt (stmt);
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

ایستا درخت
c_parser_omp_sections (location_t loc, c_parser *parser,
		       نویسه *p_name, omp_clause_mask mask, درخت *cclauses)
{
  درخت block, clauses, ret;

  strcat (p_name, " sections");
  mask |= OMP_SECTIONS_CLAUSE_MASK;
  اگر (cclauses)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == پوچ);
  اگر (cclauses)
    {
      omp_split_clauses (loc, OMP_SECTIONS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SECTIONS];
    }

  block = c_begin_compound_stmt (درست);
  ret = c_parser_omp_sections_scope (loc, parser);
  اگر (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  block = c_end_compound_stmt (loc, block, درست);
  add_stmt (block);

  بازگشت ret;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_رقم_THREADS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

ایستا درخت
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       نویسه *p_name, omp_clause_mask mask, درخت *cclauses,
		       منطقی *if_p)
{
  درخت stmt, clauses, block;

  strcat (p_name, " parallel");
  mask |= OMP_PARALLEL_CLAUSE_MASK;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  اگر ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  اگر (c_parser_next_token_is_keyword (parser, RID_FOR))
    {
      درخت cclauses_buf[C_OMP_CLAUSE_SPLIT_شمار];
      اگر (cclauses == پوچ)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      اگر (!flag_openmp)  /* flag_openmp_simd  */
	بازگشت c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      block = c_begin_omp_parallel ();
      درخت ret = c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      stmt
	= c_finish_omp_parallel (loc, cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				 block);
      اگر (ret == NULL_درخت)
	بازگشت ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      بازگشت stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  وگرنه اگر (cclauses
	   && (mask & (OMP_CLAUSE_MASK_1
		       << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_to_pragma_eol (parser);
      بازگشت NULL_درخت;
    }
  وگرنه اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      location_t ploc = c_parser_peek_token (parser)->location;
      اگر (cclauses == پوچ && strcmp (p, "masked") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_SPLIT_شمار];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    بازگشت c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					if_p);
	  block = c_begin_omp_parallel ();
	  درخت ret = c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					  if_p);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  اگر (ret == پوچ)
	    بازگشت ret;
	  /* masked does have just filter clause, but during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel masked don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel masked
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel masked taskloop simd lastprivate (x)  */
	  اگر (OMP_MASKED_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  بازگشت stmt;
	}
      وگرنه اگر (cclauses == پوچ && strcmp (p, "master") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_SPLIT_شمار];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    بازگشت c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					if_p, ploc);
	  block = c_begin_omp_parallel ();
	  درخت ret = c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					  if_p, ploc);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  اگر (ret == پوچ)
	    بازگشت ret;
	  /* master doesn't have any clauses and during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel master don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel master
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel master taskloop simd lastprivate (x)  */
	  اگر (OMP_MASTER_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  بازگشت stmt;
	}
      وگرنه اگر (strcmp (p, "loop") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_SPLIT_شمار];
	  اگر (cclauses == پوچ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    بازگشت c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  درخت ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
					if_p);
	  stmt
	    = c_finish_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				     block);
	  اگر (ret == NULL_درخت)
	    بازگشت ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  بازگشت stmt;
	}
      وگرنه اگر (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, نادرست);
	  بازگشت NULL_درخت;
	}
      وگرنه اگر (cclauses == پوچ && strcmp (p, "sections") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_SPLIT_شمار];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  block = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, mask, cclauses);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  بازگشت stmt;
	}
    }
  وگرنه اگر (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, نادرست);
      بازگشت NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == پوچ);
  اگر (cclauses)
    {
      omp_split_clauses (loc, OMP_PARALLEL, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL];
    }

  block = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = درست;
  c_parser_statement (parser, if_p);
  stmt = c_finish_omp_parallel (loc, clauses, block);

  بازگشت stmt;
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

ایستا درخت
c_parser_omp_single (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت stmt = make_گره (OMP_SINGLE);
  SET_عبارت_LOCATION (stmt, loc);
  درخت_TYPE (stmt) = void_type_گره;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_MASK,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  بازگشت add_stmt (stmt);
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

ایستا درخت
c_parser_omp_scope (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت stmt = make_گره (OMP_SCOPE);
  SET_عبارت_LOCATION (stmt, loc);
  درخت_TYPE (stmt) = void_type_گره;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_MASK,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  بازگشت add_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
ایستا درخت
c_parser_omp_dispatch_body (c_parser *parser)
{
  ساختار c_عبارت lhs, rhs, ret;
  location_t عبارت_loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_expression (parser, پوچ, پوچ);
  اگر (درخت_CODE (lhs.مقدار) == CALL_عبارت)
    بازگشت lhs.مقدار;

  location_t op_location = c_parser_peek_token (parser)->location;
  اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    بازگشت error_mark_گره;

  /* Parse function name.  */
  اگر (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      بازگشت error_mark_گره;
    }
  عبارت_loc = c_parser_peek_token (parser)->location;
  درخت id = c_parser_peek_token (parser)->مقدار;
  c_parser_consume_token (parser);
  اگر (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      بازگشت error_mark_گره;
    }

  rhs.مقدار = build_external_ref (عبارت_loc, id, درست, &rhs.original_type);
  set_c_عبارت_source_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_expression_after_primary (
    parser, عبارت_LOC_OR_LOC (rhs.مقدار, عبارت_loc), rhs);
  اگر (درخت_CODE (rhs.مقدار) != CALL_عبارت)
    {
      error_at (عبارت_LOC_OR_LOC (rhs.مقدار, عبارت_loc),
		"expected target-function call");
      بازگشت error_mark_گره;
    }

  /* Build assignment. */
  rhs = convert_lvalue_to_rvalue (عبارت_loc, rhs, درست, درست);
  ret.مقدار
    = build_modify_عبارت (op_location, lhs.مقدار, lhs.original_type, NOP_عبارت,
			 عبارت_loc, rhs.مقدار, rhs.original_type);
  ret.m_decimal = 0;
  set_c_عبارت_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  ret.original_code = MODIFY_عبارت;
  ret.original_type = پوچ;
  بازگشت ret.مقدار;
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

ایستا درخت
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  درخت stmt = make_گره (OMP_DISPATCH);
  SET_عبارت_LOCATION (stmt, loc);
  درخت_TYPE (stmt) = void_type_گره;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_MASK,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  درخت depend_clauses = NULL_درخت;
  درخت *depend_clauses_ptr = &depend_clauses;
  برای (درخت c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  اگر (depend_clauses != NULL_درخت)
    {
      درخت stmt = make_گره (OMP_TASK);
      درخت_TYPE (stmt) = void_گره;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_درخت;
      SET_عبارت_LOCATION (stmt, loc);
      add_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  درخت dispatch_body = c_parser_omp_dispatch_body (parser);
  اگر (dispatch_body == error_mark_گره)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_to_end_of_block_or_statement (parser);
      بازگشت NULL_درخت;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (درخت_CODE (dispatch_body) == CALL_عبارت
	      || درخت_CODE (dispatch_body) == MODIFY_عبارت);
  درخت *dispatch_call = درخت_CODE (dispatch_body) == MODIFY_عبارت
			  ? &درخت_OPERAND (dispatch_body, 1)
			  : &dispatch_body;
  وقتی (درخت_CODE (*dispatch_call) == FLOAT_عبارت
	 || درخت_CODE (*dispatch_call) == CONVERT_عبارت
	 || درخت_CODE (*dispatch_call) == NOP_عبارت)
    dispatch_call = &درخت_OPERAND (*dispatch_call, 0);
  *dispatch_call = build_call_عبارت_internal_loc (
    loc, IFN_GOMP_DISPATCH,
    درخت_TYPE (درخت_TYPE (CALL_عبارت_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  بازگشت add_stmt (stmt);
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

ایستا درخت
c_parser_omp_task (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت clauses, block;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_MASK,
				      "#pragma omp task");

  block = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = درست;
  c_parser_statement (parser, if_p);
  بازگشت c_finish_omp_task (loc, clauses, block);
}

/* OpenMP 3.0:
   # pragma omp taskwait new-line

   OpenMP 5.0:
   # pragma omp taskwait taskwait-clause[optseq] new-line
*/

#define OMP_TASKWAIT_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ایستا تهی
c_parser_omp_taskwait (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_MASK,
				"#pragma omp taskwait");

  اگر (clauses)
    {
      درخت stmt = make_گره (OMP_TASK);
      درخت_TYPE (stmt) = void_گره;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_درخت;
      SET_عبارت_LOCATION (stmt, loc);
      add_stmt (stmt);
    }
  وگرنه
    c_finish_omp_taskwait (loc);
}

/* OpenMP 3.1:
   # pragma omp taskyield new-line
*/

ایستا تهی
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

ایستا درخت
c_parser_omp_taskgroup (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_MASK,
					   "#pragma omp taskgroup");

  درخت body = c_parser_omp_structured_block (parser, if_p);
  بازگشت c_finish_omp_taskgroup (loc, body, clauses);
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

ایستا تهی
c_parser_omp_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);
  درخت clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_MASK,
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

ایستا منطقی
c_parser_omp_cancellation_point (c_parser *parser, شمارش pragma_context context)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت clauses;
  منطقی point_seen = نادرست;

  c_parser_consume_pragma (parser);
  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  point_seen = درست;
	}
    }
  اگر (!point_seen)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_to_pragma_eol (parser);
      بازگشت نادرست;
    }

  اگر (context != pragma_compound)
    {
      اگر (context == pragma_stmt)
	error_at (loc,
		  "%<#pragma %s%> may only be used in compound statements",
		  "omp cancellation point");
      وگرنه
	c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, نادرست);
      بازگشت درست;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_POINT_CLAUSE_MASK,
				"#pragma omp cancellation point");

  c_finish_omp_cancellation_point (loc, clauses);
  بازگشت درست;
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

ایستا درخت
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 نویسه *p_name, omp_clause_mask mask, درخت *cclauses,
			 منطقی *if_p)
{
  درخت clauses, block, ret;

  strcat (p_name, " distribute");
  mask |= OMP_DISTRIBUTE_CLAUSE_MASK;

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      منطقی simd = نادرست;
      منطقی parallel = نادرست;

      اگر (strcmp (p, "simd") == 0)
	simd = درست;
      وگرنه
	parallel = strcmp (p, "parallel") == 0;
      اگر (parallel || simd)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_SPLIT_شمار];
	  اگر (cclauses == پوچ)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      اگر (simd)
		بازگشت c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
					  if_p);
	      وگرنه
		بازگشت c_parser_omp_parallel (loc, parser, p_name, mask,
					      cclauses, if_p);
	    }
	  block = c_begin_compound_stmt (درست);
	  اگر (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				     if_p);
	  وگرنه
	    ret = c_parser_omp_parallel (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, درست);
	  اگر (ret == پوچ)
	    بازگشت ret;
	  ret = make_گره (OMP_DISTRIBUTE);
	  درخت_TYPE (ret) = void_type_گره;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
	  SET_عبارت_LOCATION (ret, loc);
	  add_stmt (ret);
	  بازگشت ret;
	}
    }
  اگر (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, نادرست);
      بازگشت NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == پوچ);
  اگر (cclauses)
    {
      omp_split_clauses (loc, OMP_DISTRIBUTE, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
    }

  block = c_begin_compound_stmt (درست);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, پوچ,
			       if_p);
  block = c_end_compound_stmt (loc, block, درست);
  add_stmt (block);

  بازگشت ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#define OMP_TEAMS_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_رقم_TEAMS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_THREAD_LIMIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

ایستا درخت
c_parser_omp_teams (location_t loc, c_parser *parser,
		    نویسه *p_name, omp_clause_mask mask, درخت *cclauses,
		    منطقی *if_p)
{
  درخت clauses, block, ret;

  strcat (p_name, " teams");
  mask |= OMP_TEAMS_CLAUSE_MASK;

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp (p, "distribute") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_SPLIT_شمار];
	  اگر (cclauses == پوچ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    بازگشت c_parser_omp_distribute (loc, parser, p_name, mask,
					    cclauses, if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, درست);
	  اگر (ret == پوچ)
	    بازگشت ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_گره (OMP_TEAMS);
	  درخت_TYPE (ret) = void_type_گره;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_عبارت_LOCATION (ret, loc);
	  بازگشت add_stmt (ret);
	}
      وگرنه اگر (strcmp (p, "loop") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_SPLIT_شمار];
	  اگر (cclauses == پوچ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    بازگشت c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, درست);
	  اگر (ret == پوچ)
	    بازگشت ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_گره (OMP_TEAMS);
	  درخت_TYPE (ret) = void_type_گره;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_عبارت_LOCATION (ret, loc);
	  بازگشت add_stmt (ret);
	}
    }
  اگر (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, نادرست);
      بازگشت NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == پوچ);
  اگر (cclauses)
    {
      omp_split_clauses (loc, OMP_TEAMS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
    }

  درخت stmt = make_گره (OMP_TEAMS);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_end_compound_stmt (loc, block, درست);
  SET_عبارت_LOCATION (stmt, loc);

  بازگشت add_stmt (stmt);
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

ایستا درخت
c_parser_omp_target_data (location_t loc, c_parser *parser, منطقی *if_p)
{
  اگر (flag_openmp)
    omp_requires_mask
      = (شمارش omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_DATA_CLAUSE_MASK,
				"#pragma omp target data", نادرست);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, نادرست);
  صحیح map_seen = 0;
  برای (درخت *pc = &clauses; *pc;)
    {
      اگر (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	انتخاب (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  حالت GOMP_MAP_TO:
	  حالت GOMP_MAP_ALWAYS_TO:
	  حالت GOMP_MAP_PRESENT_TO:
	  حالت GOMP_MAP_ALWAYS_PRESENT_TO:
	  حالت GOMP_MAP_FROM:
	  حالت GOMP_MAP_ALWAYS_FROM:
	  حالت GOMP_MAP_PRESENT_FROM:
	  حالت GOMP_MAP_ALWAYS_PRESENT_FROM:
	  حالت GOMP_MAP_TOFROM:
	  حالت GOMP_MAP_ALWAYS_TOFROM:
	  حالت GOMP_MAP_PRESENT_TOFROM:
	  حالت GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  حالت GOMP_MAP_ALLOC:
	  حالت GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    بشکن;
	  حالت GOMP_MAP_FIRSTPRIVATE_POINTER:
	  حالت GOMP_MAP_ALWAYS_POINTER:
	  حالت GOMP_MAP_ATTACH_DETACH:
	  حالت GOMP_MAP_ATTACH:
	    بشکن;
	  پیشفرض:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ادامه;
	  }
      وگرنه اگر (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_seen = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  اگر (map_seen != 3)
    {
      اگر (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      بازگشت NULL_درخت;
    }

  درخت stmt = make_گره (OMP_TARGET_DATA);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_TARGET_DATA_CLAUSES (stmt) = clauses;
  keep_next_level ();
  درخت block = c_begin_compound_stmt (درست);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TARGET_DATA_BODY (stmt) = c_end_compound_stmt (loc, block, درست);

  SET_عبارت_LOCATION (stmt, loc);
  بازگشت add_stmt (stmt);
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

ایستا منطقی
c_parser_omp_target_update (location_t loc, c_parser *parser,
			    شمارش pragma_context context)
{
  اگر (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_to_pragma_eol (parser, نادرست);
      بازگشت درست;
    }

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_UPDATE_CLAUSE_MASK,
				"#pragma omp target update",
				/* finish_p = */ نادرست);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  اگر (omp_find_clause (clauses, OMP_CLAUSE_TO) == NULL_درخت
      && omp_find_clause (clauses, OMP_CLAUSE_FROM) == NULL_درخت)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      بازگشت نادرست;
    }

  اگر (flag_openmp)
    omp_requires_mask
      = (شمارش omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  درخت stmt = make_گره (OMP_TARGET_UPDATE);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_TARGET_UPDATE_CLAUSES (stmt) = clauses;
  SET_عبارت_LOCATION (stmt, loc);
  add_stmt (stmt);
  بازگشت نادرست;
}

/* OpenMP 4.5:
   # pragma omp target enter data target-data-clause[optseq] new-line  */

#define OMP_TARGET_ENTER_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ایستا منطقی
c_parser_omp_target_enter_data (location_t loc, c_parser *parser,
				شمارش pragma_context context)
{
  منطقی data_seen = نادرست;
  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = درست;
	}
    }
  اگر (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      بازگشت نادرست;
    }

  اگر (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_to_pragma_eol (parser, نادرست);
      بازگشت درست;
    }

  اگر (flag_openmp)
    omp_requires_mask
      = (شمارش omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_ENTER_DATA_CLAUSE_MASK,
				"#pragma omp target enter data", نادرست);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, نادرست);
  صحیح map_seen = 0;
  برای (درخت *pc = &clauses; *pc;)
    {
      اگر (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	انتخاب (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  حالت GOMP_MAP_TO:
	  حالت GOMP_MAP_ALWAYS_TO:
	  حالت GOMP_MAP_PRESENT_TO:
	  حالت GOMP_MAP_ALWAYS_PRESENT_TO:
	  حالت GOMP_MAP_ALLOC:
	  حالت GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    بشکن;
	  حالت GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_TO);
	    map_seen = 3;
	    بشکن;
	  حالت GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_TO);
	    map_seen = 3;
	    بشکن;
	  حالت GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_TO);
	    map_seen = 3;
	    بشکن;
	  حالت GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_TO);
	    map_seen = 3;
	    بشکن;
	  حالت GOMP_MAP_FIRSTPRIVATE_POINTER:
	  حالت GOMP_MAP_ALWAYS_POINTER:
	  حالت GOMP_MAP_ATTACH_DETACH:
	  حالت GOMP_MAP_ATTACH:
	    بشکن;
	  پیشفرض:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ادامه;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  اگر (map_seen != 3)
    {
      اگر (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      بازگشت درست;
    }

  درخت stmt = make_گره (OMP_TARGET_ENTER_DATA);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_TARGET_ENTER_DATA_CLAUSES (stmt) = clauses;
  SET_عبارت_LOCATION (stmt, loc);
  add_stmt (stmt);
  بازگشت درست;
}

/* OpenMP 4.5:
   # pragma omp target exit data target-data-clause[optseq] new-line  */

#define OMP_TARGET_EXIT_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ایستا منطقی
c_parser_omp_target_exit_data (location_t loc, c_parser *parser,
			       شمارش pragma_context context)
{
  منطقی data_seen = نادرست;
  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = درست;
	}
    }
  اگر (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      بازگشت نادرست;
    }

  اگر (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_to_pragma_eol (parser, نادرست);
      بازگشت درست;
    }

  اگر (flag_openmp)
    omp_requires_mask
      = (شمارش omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_EXIT_DATA_CLAUSE_MASK,
				"#pragma omp target exit data", نادرست);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_DATA);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_EXIT_DATA);
  c_omp_adjust_map_clauses (clauses, نادرست);
  صحیح map_seen = 0;
  برای (درخت *pc = &clauses; *pc;)
    {
      اگر (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	انتخاب (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  حالت GOMP_MAP_FROM:
	  حالت GOMP_MAP_ALWAYS_FROM:
	  حالت GOMP_MAP_PRESENT_FROM:
	  حالت GOMP_MAP_ALWAYS_PRESENT_FROM:
	  حالت GOMP_MAP_RELEASE:
	  حالت GOMP_MAP_DELETE:
	    map_seen = 3;
	    بشکن;
	  حالت GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_FROM);
	    map_seen = 3;
	    بشکن;
	  حالت GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_seen = 3;
	    بشکن;
	  حالت GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_FROM);
	    map_seen = 3;
	    بشکن;
	  حالت GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_seen = 3;
	    بشکن;
	  حالت GOMP_MAP_FIRSTPRIVATE_POINTER:
	  حالت GOMP_MAP_ALWAYS_POINTER:
	  حالت GOMP_MAP_ATTACH_DETACH:
	  حالت GOMP_MAP_DETACH:
	    بشکن;
	  پیشفرض:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target exit data%> with map-type other "
		      "than %<from%>, %<tofrom%>, %<release%> or %<delete%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ادامه;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  اگر (map_seen != 3)
    {
      اگر (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      بازگشت درست;
    }

  درخت stmt = make_گره (OMP_TARGET_EXIT_DATA);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_TARGET_EXIT_DATA_CLAUSES (stmt) = clauses;
  SET_عبارت_LOCATION (stmt, loc);
  add_stmt (stmt);
  بازگشت درست;
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

ایستا منطقی
c_parser_omp_target (c_parser *parser, شمارش pragma_context context, منطقی *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  درخت *pc = پوچ, stmt, block, body, clauses;

  اگر (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser);
      بازگشت نادرست;
    }

  اگر (flag_openmp)
    omp_requires_mask
      = (شمارش omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      شمارش درخت_code ccode = ERROR_MARK;

      اگر (strcmp (p, "teams") == 0)
	ccode = OMP_TEAMS;
      وگرنه اگر (strcmp (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      وگرنه اگر (strcmp (p, "simd") == 0)
	ccode = OMP_SIMD;
      اگر (ccode != ERROR_MARK)
	{
	  درخت cclauses[C_OMP_CLAUSE_SPLIT_شمار];
	  نویسه p_name[اندازه ("#pragma omp target teams distribute "
			      "parallel for simd")];

	  c_parser_consume_token (parser);
	  strcpy (p_name, "#pragma omp target");
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      درخت stmt;
	      انتخاب (ccode)
		{
		حالت OMP_TEAMS:
		  stmt = c_parser_omp_teams (loc, parser, p_name,
					     OMP_TARGET_CLAUSE_MASK,
					     cclauses, if_p);
		  بشکن;
		حالت OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_TARGET_CLAUSE_MASK,
						cclauses, if_p);
		  بشکن;
		حالت OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_TARGET_CLAUSE_MASK,
					    cclauses, if_p);
		  بشکن;
		پیشفرض:
		  gcc_unreachable ();
		}
	      بازگشت stmt != NULL_درخت;
	    }
	  keep_next_level ();
	  درخت block = c_begin_compound_stmt (درست), ret;
	  انتخاب (ccode)
	    {
	    حالت OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_TARGET_CLAUSE_MASK, cclauses,
					if_p);
	      بشکن;
	    حالت OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_TARGET_CLAUSE_MASK, cclauses,
					   if_p);
	      بشکن;
	    حالت OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_TARGET_CLAUSE_MASK, cclauses,
				       if_p);
	      بشکن;
	    پیشفرض:
	      gcc_unreachable ();
	    }
	  block = c_end_compound_stmt (loc, block, درست);
	  اگر (ret == NULL_درخت)
	    بازگشت نادرست;
	  اگر (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    برای (درخت c = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_رقم_TEAMS
		  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_THREAD_LIMIT)
		برای (صحیح i = 0;
		     i <= (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_رقم_TEAMS); ++i)
		  اگر (OMP_CLAUSE_OPERAND (c, i)
		      && درخت_CODE (OMP_CLAUSE_OPERAND (c, i)) != INTEGER_CST)
		    {
		      درخت عبارت = OMP_CLAUSE_OPERAND (c, i);
		      درخت tmp = create_tmp_var_raw (درخت_TYPE (عبارت));
		      عبارت = build4 (TARGET_عبارت, درخت_TYPE (عبارت), tmp,
				     عبارت, NULL_درخت, NULL_درخت);
		      add_stmt (عبارت);
		      OMP_CLAUSE_OPERAND (c, i) = عبارت;
		      درخت tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
		      cclauses[C_OMP_CLAUSE_SPLIT_TARGET] = tc;
		    }
	  درخت stmt = make_گره (OMP_TARGET);
	  درخت_TYPE (stmt) = void_type_گره;
	  OMP_TARGET_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
	  c_omp_adjust_map_clauses (OMP_TARGET_CLAUSES (stmt), درست);
	  OMP_TARGET_BODY (stmt) = block;
	  OMP_TARGET_COMBINED (stmt) = 1;
	  SET_عبارت_LOCATION (stmt, loc);
	  add_stmt (stmt);
	  pc = &OMP_TARGET_CLAUSES (stmt);
	  برو check_clauses;
	}
      وگرنه اگر (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, نادرست);
	  بازگشت نادرست;
	}
      وگرنه اگر (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_target_data (loc, parser, if_p);
	  بازگشت درست;
	}
      وگرنه اگر (strcmp (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  بازگشت c_parser_omp_target_enter_data (loc, parser, context);
	}
      وگرنه اگر (strcmp (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  بازگشت c_parser_omp_target_exit_data (loc, parser, context);
	}
      وگرنه اگر (strcmp (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  بازگشت c_parser_omp_target_update (loc, parser, context);
	}
    }
  اگر (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, نادرست);
      بازگشت نادرست;
    }

  stmt = make_گره (OMP_TARGET);
  درخت_TYPE (stmt) = void_type_گره;

  clauses = c_parser_omp_all_clauses (parser, OMP_TARGET_CLAUSE_MASK,
				      "#pragma omp target", نادرست);
  برای (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
      {
	درخت nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_SET_MAP_KIND (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_TARGET);
  clauses  = c_finish_omp_clauses (clauses, C_ORT_OMP_TARGET);
  c_omp_adjust_map_clauses (clauses, درست);

  keep_next_level ();
  block = c_begin_compound_stmt (درست);
  body = c_parser_omp_structured_block (parser, if_p);

  c_omp_scan_mapper_bindings (loc, &clauses, body);

  add_stmt (body);
  OMP_TARGET_CLAUSES (stmt) = clauses;
  pc = &OMP_TARGET_CLAUSES (stmt);
  OMP_TARGET_BODY (stmt) = c_end_compound_stmt (loc, block, درست);

  SET_عبارت_LOCATION (stmt, loc);
  add_stmt (stmt);

check_clauses:
  وقتی (*pc)
    {
      اگر (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	انتخاب (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  حالت GOMP_MAP_TO:
	  حالت GOMP_MAP_ALWAYS_TO:
	  حالت GOMP_MAP_PRESENT_TO:
	  حالت GOMP_MAP_ALWAYS_PRESENT_TO:
	  حالت GOMP_MAP_FROM:
	  حالت GOMP_MAP_ALWAYS_FROM:
	  حالت GOMP_MAP_PRESENT_FROM:
	  حالت GOMP_MAP_ALWAYS_PRESENT_FROM:
	  حالت GOMP_MAP_TOFROM:
	  حالت GOMP_MAP_ALWAYS_TOFROM:
	  حالت GOMP_MAP_PRESENT_TOFROM:
	  حالت GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  حالت GOMP_MAP_ALLOC:
	  حالت GOMP_MAP_PRESENT_ALLOC:
	  حالت GOMP_MAP_FIRSTPRIVATE_POINTER:
	  حالت GOMP_MAP_ALWAYS_POINTER:
	  حالت GOMP_MAP_POINTER:
	  حالت GOMP_MAP_ATTACH_DETACH:
	  حالت GOMP_MAP_ATTACH:
	    بشکن;
	  پیشفرض:
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ادامه;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }
  cfun->has_omp_target = درست;
  بازگشت درست;
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

ایستا تهی
c_parser_omp_declare_simd (c_parser *parser, شمارش pragma_context context)
{
  c_token *token = c_parser_peek_token (parser);
  gcc_assert (token->type == CPP_NAME);
  درخت kind = token->مقدار;
  gcc_assert (strcmp (IDENTIFIER_POINTER (kind), "simd") == 0
	      || strcmp (IDENTIFIER_POINTER (kind), "variant") == 0);

  auto_vec<c_token> clauses;
  وقتی (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (token->type == CPP_EOF)
	{
	  c_parser_skip_to_pragma_eol (parser);
	  بازگشت;
	}
      clauses.safe_افزودن (*token);
      c_parser_consume_token (parser);
    }
  clauses.safe_افزودن (*c_parser_peek_token (parser));
  c_parser_skip_to_pragma_eol (parser);

  وقتی (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      اگر (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->مقدار != kind)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_POINTER (kind), IDENTIFIER_POINTER (kind));
	  بازگشت;
	}
      c_parser_consume_pragma (parser);
      وقتی (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  اگر (token->type == CPP_EOF)
	    {
	      c_parser_skip_to_pragma_eol (parser);
	      بازگشت;
	    }
	  clauses.safe_افزودن (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_افزودن (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  memset (&eof_token, 0, اندازه (eof_token));
  eof_token.type = CPP_EOF;
  clauses.safe_افزودن (eof_token);
  clauses.safe_افزودن (eof_token);

  انتخاب (context)
    {
    حالت pragma_external:
      اگر (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحیح ext = disable_extension_diagnostics ();
	  انجامبده
	    c_parser_consume_token (parser);
	  وقتی (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, درست, درست, درست, نادرست, درست,
					 نادرست, پوچ, &clauses);
	  restore_extension_diagnostics (ext);
	}
      وگرنه
	c_parser_declaration_or_fndef (parser, درست, درست, درست, نادرست, درست,
				       نادرست, پوچ, &clauses);
      بشکن;
    حالت pragma_struct:
    حالت pragma_param:
    حالت pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      بشکن;
    حالت pragma_compound:
      منطقی have_std_attrs;
      درخت std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
      اگر (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      وگرنه
	std_attrs = NULL_درخت;
      اگر (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحیح ext = disable_extension_diagnostics ();
	  انجامبده
	    c_parser_consume_token (parser);
	  وقتی (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  اگر (c_parser_next_tokens_start_declaration (parser)
	      || c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, درست, درست, درست, درست,
					     درست, نادرست, پوچ, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      بشکن;
	    }
	  restore_extension_diagnostics (ext);
	}
      وگرنه اگر (c_parser_next_tokens_start_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, درست, درست, درست, درست, درست,
					 نادرست, پوچ, &clauses, have_std_attrs,
					 std_attrs);
	  بشکن;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      بشکن;
    پیشفرض:
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

ایستا درخت
c_parser_omp_context_selector (c_parser *parser, شمارش omp_tss_code set,
			       درخت parms)
{
  درخت ret = NULL_درخت;
  انجامبده
    {
      درخت selector;
      اگر (c_parser_next_token_is (parser, CPP_KEYWORD)
	  || c_parser_next_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->مقدار;
      وگرنه
	{
	  c_parser_error (parser, "expected trait selector name");
	  بازگشت error_mark_گره;
	}
      شمارش omp_ts_code sel
	= omp_lookup_ts_code (set, IDENTIFIER_POINTER (selector));

      اگر (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_POINTER (selector),  omp_tss_map[set]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_درخت, NULL_درخت, ret);
	  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_balanced_token_sequence (parser);
	  اگر (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ادامه;
	    }
	  وگرنه
	    بشکن;
	}

      c_parser_consume_token (parser);

      درخت properties = NULL_درخت;
      درخت scoreval = NULL_درخت;
      شمارش omp_tp_type property_kind = omp_ts_map[sel].tp_type;
      منطقی allow_score = omp_ts_map[sel].allow_score;
      درخت t;

      اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  اگر (property_kind == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_POINTER (selector));
	      بازگشت error_mark_گره;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  اگر (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER (token->مقدار), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      درخت score = c_parser_عبارت_no_commas (parser, پوچ).مقدار;
	      parens2.skip_until_found_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      اگر (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[set]);
	      وگرنه اگر (score != error_mark_گره)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, نادرست, پوچ);
		  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (score))
		      || درخت_CODE (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  وگرنه اگر (درخت_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  وگرنه
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  انتخاب (property_kind)
	    {
	    حالت OMP_TRAIT_PROPERTY_ID:
	      اگر (c_parser_next_token_is (parser, CPP_KEYWORD)
		  || c_parser_next_token_is (parser, CPP_NAME))
		{
		  درخت prop = c_parser_peek_token (parser)->مقدار;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_درخت,
						    properties);
		}
	      وگرنه
		{
		  c_parser_error (parser, "expected identifier");
		  بازگشت error_mark_گره;
		}
	      بشکن;
	    حالت OMP_TRAIT_PROPERTY_NAME_LIST:
	      انجامبده
		{
		  درخت prop = OMP_TP_NAMELIST_گره;
		  درخت مقدار = NULL_درخت;
		  اگر (c_parser_next_token_is (parser, CPP_KEYWORD)
		      || c_parser_next_token_is (parser, CPP_NAME))
		    {
		      مقدار = c_parser_peek_token (parser)->مقدار;
		      c_parser_consume_token (parser);
		    }
		  وگرنه اگر (c_parser_next_token_is (parser, CPP_STRING))
		    مقدار = c_parser_string_literal (parser, نادرست,
						     نادرست).مقدار;
		  وگرنه
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      بازگشت error_mark_گره;
		    }

		  properties = make_trait_property (prop, مقدار, properties);

		  اگر (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  وگرنه
		    بشکن;
		}
	      وقتی (1);
	      بشکن;
	    حالت OMP_TRAIT_PROPERTY_DEV_رقم_عبارت:
	    حالت OMP_TRAIT_PROPERTY_BOOL_عبارت:
	      {
		c_عبارت texpr = c_parser_عبارت_no_commas (parser, پوچ);
		texpr = convert_lvalue_to_rvalue (token->location, texpr,
						  درست, درست);
		t = texpr.مقدار;
	      }
	      اگر (t == error_mark_گره)
		بازگشت error_mark_گره;
	      mark_exp_read (t);
	      اگر (property_kind == OMP_TRAIT_PROPERTY_BOOL_عبارت)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_گره);
		  اگر (t == error_mark_گره)
		    بازگشت error_mark_گره;
		}
	      وگرنه اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  بازگشت error_mark_گره;
		}
	      t = c_fully_fold (t, نادرست, پوچ);
	      properties = make_trait_property (NULL_درخت, t, properties);
	      بشکن;
	    حالت OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      اگر (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  اگر (parms == NULL_درخت)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      بازگشت error_mark_گره;
		    }
		  درخت c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_MASK,
						"simd", درست, 2);
		  c = c_omp_declare_simd_clauses_to_numbers (parms
							     == error_mark_گره
							     ? NULL_درخت : parms,
							     c);
		  properties = c;
		}
	      وگرنه اگر (sel == OMP_TRAIT_IMPLEMENTATION_REQUIRES)
		{
		  /* FIXME: The "requires" selector was added in OpenMP 5.1.
		     Currently only the now-deprecated syntax
		     from OpenMP 5.0 is supported.  */
		  sorry_at (token->location,
			    "%<requires%> selector is not supported yet");
		  بازگشت error_mark_گره;
		}
	      وگرنه
		gcc_unreachable ();
	      بشکن;
	    پیشفرض:
	      gcc_unreachable ();
	    }

	  parens.skip_until_found_close (parser);
	  properties = nreverse (properties);
	}
      وگرنه اگر (property_kind != OMP_TRAIT_PROPERTY_NONE
	       && property_kind != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_kind != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  بازگشت error_mark_گره;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      اگر (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وگرنه
	بشکن;
    }
  وقتی (1);

  بازگشت nreverse (ret);
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

ایستا درخت
c_parser_omp_context_selector_specification (c_parser *parser, درخت parms)
{
  درخت ret = NULL_درخت;
  انجامبده
    {
      ثابت نویسه *setp = "";
      اگر (c_parser_next_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      شمارش omp_tss_code set = omp_lookup_tss_code (setp);

      اگر (set == OMP_TRAIT_SET_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  بازگشت error_mark_گره;
	}

      c_parser_consume_token (parser);

      اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	بازگشت error_mark_گره;

      matching_braces braces;
      اگر (!braces.require_open (parser))
	بازگشت error_mark_گره;

      درخت selectors = c_parser_omp_context_selector (parser, set, parms);
      اگر (selectors == error_mark_گره)
	{
	  c_parser_skip_to_closing_brace (parser);
	  ret = error_mark_گره;
	}
      وگرنه اگر (ret != error_mark_گره)
	ret = make_trait_set_selector (set, selectors, ret);

      braces.require_close (parser);

      اگر (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وگرنه
	بشکن;
    }
  وقتی (1);

  اگر (ret == error_mark_گره)
    بازگشت ret;
  بازگشت nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

ایستا تهی
c_finish_omp_declare_variant (c_parser *parser, درخت fndecl, درخت parms)
{
  matching_parens parens;
  اگر (!parens.require_open (parser))
    {
     fail:
      c_parser_skip_to_pragma_eol (parser, نادرست);
      بازگشت;
    }

  اگر (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      برو fail;
    }

  c_token *token = c_parser_peek_token (parser);
  درخت variant = lookup_name (token->مقدار);

  اگر (variant == NULL_درخت)
    {
      undeclared_variable (token->location, token->مقدار);
      variant = error_mark_گره;
    }
  وگرنه اگر (درخت_CODE (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_گره;
    }
  وگرنه اگر (fndecl_built_in_p (variant)
	   && (strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			"__builtin_", strlen ("__builtin_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__sync_", strlen ("__sync_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__atomic_", strlen ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_گره;
    }
  وگرنه اگر (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_گره;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  درخت append_args_درخت = NULL_درخت;
  درخت append_args_last;
  vec<درخت> adjust_args_list = vNULL;
  منطقی has_match = نادرست, has_adjust_args = نادرست;
  location_t adjust_args_loc = UNKNOWN_LOCATION;
  location_t append_args_loc = UNKNOWN_LOCATION;
  location_t match_loc = UNKNOWN_LOCATION;
  درخت need_device_ptr_list = NULL_درخت;
  درخت ctx = error_mark_گره;

  انجامبده
    {
      اگر (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ثابت نویسه *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      اگر (c_parser_next_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);

      شمارش clause
      {
	match,
	adjust_args,
	append_args
      } ccode;

      اگر (strcmp (clause, "match") == 0)
	{
	  ccode = match;
	  match_loc = loc;
	}
      وگرنه اگر (strcmp (clause, "adjust_args") == 0)
	{
	  ccode = adjust_args;
	  adjust_args_loc = loc;
	}
      وگرنه اگر (strcmp (clause, "append_args") == 0)
	{
	  ccode = append_args;
	  append_args_loc = loc;
	}
      وگرنه
	{
	  c_parser_error (parser, "expected %<match%>, %<adjust_args%> or "
				  "%<append_args%> clause");
	  برو fail;
	}

      c_parser_consume_token (parser);

      اگر (!parens.require_open (parser))
	برو fail;

      اگر (parms == NULL_درخت)
	parms = error_mark_گره;

      اگر (ccode == match)
	{
	  اگر (has_match)
	    error_at (match_loc, "too many %<match%> clauses");
	  has_match = درست;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  اگر (ctx == error_mark_گره)
	    برو fail;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  اگر (ctx != error_mark_گره
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      درخت outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      وگرنه اگر (ccode == adjust_args)
	{
	  has_adjust_args = درست;
	  اگر (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      ثابت نویسه *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
	      اگر (strcmp (p, "need_device_ptr") == 0
		  || strcmp (p, "nothing") == 0)
		{
		  c_parser_consume_token (parser); // need_device_ptr
		  c_parser_consume_token (parser); // :

		  loc = c_parser_peek_token (parser)->location;
		  درخت list
		    = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ERROR,
						  NULL_درخت);

		  درخت arg;
		  اگر (variant != error_mark_گره)
		    برای (درخت c = list; c != NULL_درخت; c = درخت_CHAIN (c))
		      {
			درخت decl = درخت_PURPOSE (c);
			location_t arg_loc = عبارت_LOCATION (درخت_مقدار (c));
			صحیح idx;
			برای (arg = parms, idx = 0; arg != پوچ;
			     arg = درخت_CHAIN (arg), idx++)
			  اگر (arg == decl)
			    بشکن;
			اگر (arg == NULL_درخت)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    برو fail;
			  }
			اگر (adjust_args_list.contains (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    برو fail;
			  }
			اگر (strcmp (p, "need_device_ptr") == 0
			    && درخت_CODE (درخت_TYPE (arg)) != POINTER_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    برو fail;
			  }
			adjust_args_list.safe_افزودن (arg);
			اگر (strcmp (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_درخت_list (
				NULL_درخت,
				build_int_cst (
				  integer_type_گره,
				  idx))); // Store 0-based argument index,
					  // as in gimplify_call_expr
			  }
		      }
		}
	      وگرنه
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %<nothing%> or %<need_device_ptr%>");
		  اگر (strcmp (p, "need_device_addr") == 0)
		    inform (c_parser_peek_token (parser)->location,
			    "%<need_device_addr%> is not valid for C");
		  برو fail;
		}
	    }
	  وگرنه
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected %<nothing%> or %<need_device_ptr%> "
			"followed by %<:%>");
	      برو fail;
	    }
	}
      وگرنه اگر (ccode == append_args)
	{
	  اگر (append_args_درخت)
	    {
	      error_at (append_args_loc, "too many %qs clauses", "append_args");
	      append_args_درخت = NULL_درخت;
	    }
	  انجامبده
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      اگر (!c_parser_next_token_is (parser, CPP_NAME)
		  || strcmp ("interop",
			     IDENTIFIER_POINTER (
			       c_parser_peek_token (parser)->مقدار)))
		{
		  error_at (loc, "expected %<interop%>");
		  برو fail;
		}
	      c_parser_consume_token (parser);

	      اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		برو fail;
	      منطقی target = نادرست;
	      منطقی targetsync = نادرست;
	      درخت prefer_type_درخت = NULL_درخت;
	      اگر (!c_parser_omp_clause_init_modifiers (parser, &target,
						       &targetsync,
						       &prefer_type_درخت)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		برو fail;
	      اگر (!target && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      درخت t = build_درخت_list (target ? boolean_true_گره
					       : boolean_false_گره,
					targetsync ? boolean_true_گره
						   : boolean_false_گره);
	      t = build1_loc (loc, NOP_عبارت, void_type_گره, t);
	      t = build_درخت_list (t, prefer_type_درخت);
	      اگر (append_args_درخت)
		{
		  درخت_CHAIN (append_args_last) = t;
		  append_args_last = t;
		}
	      وگرنه
		append_args_درخت = append_args_last = t;
	      اگر (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		بشکن;
	      اگر (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		برو fail;
	    }
	  وقتی (درست);
	}

      parens.require_close (parser);
  } وقتی (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL));
  اگر (variant != error_mark_گره && !has_match)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_گره;
    }
  c_parser_skip_to_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  اگر (variant == error_mark_گره || ctx == error_mark_گره)
    /* Previously diagnosed error.  */
    بازگشت;

  اگر ((has_adjust_args || append_args_درخت)
      && !omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_args ? adjust_args_loc : append_args_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_args ? "adjust_args" : "append_args");
      بازگشت;
    }

  اگر (!omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      درخت base_type = درخت_TYPE (fndecl);
      درخت variant_type = درخت_TYPE (variant);
      منطقی unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_درخت
	   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type));

      اگر (append_args_درخت
	  && TYPE_ARG_TYPES (base_type) == NULL_درخت
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
	  بازگشت;
	}
      وگرنه اگر (append_args_درخت)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  صحیح nappend_args = 0;
	  صحیح nbase_args = 0;
	  برای (درخت t = TYPE_ARG_TYPES (base_type);
	       t && درخت_مقدار (t) != void_type_گره; t = درخت_CHAIN (t))
	    nbase_args++;
	  برای (درخت t = append_args_درخت; t; t = درخت_CHAIN (t))
	    nappend_args++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_args_درخت = build_درخت_list (build_int_cst (integer_type_گره,
							     nbase_args),
					      append_args_درخت);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  اگر (!unprototyped_variant)
	    {
	      درخت args = TYPE_ARG_TYPES (variant_type);
	      برای (صحیح i = 0; args && i < nbase_args;
		   i++, args = درخت_CHAIN (args))
		;
	      برای (صحیح i = 0; i < nappend_args; i++, args = درخت_CHAIN (args))
		اگر (!args || !c_omp_interop_t_p (درخت_مقدار (args)))
		  {
		    error_at (DECL_SOURCE_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_args + i + 1, variant);
		    inform (append_args_loc,
			    "%<append_args%> specified here");
		    بازگشت;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  درخت args = TYPE_ARG_TYPES (base_type);
	  درخت newargs = NULL_درخت;
	  درخت lastarg = NULL_درخت;
	  برای (صحیح j = 0; j < nbase_args; j++, args = درخت_CHAIN (args))
	    {
	      درخت t = درخت_cons (درخت_PURPOSE (args),
				  درخت_مقدار (args), NULL_درخت);
	      اگر (lastarg)
		درخت_CHAIN (lastarg) = t;
	      وگرنه
		newargs = t;
	      lastarg = t;
	    }
	  درخت type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? درخت_TYPE (type) : pointer_sized_int_گره;
	  برای (صحیح j = 0; j < nappend_args; j++)
	    {
	      درخت t = درخت_cons (NULL_درخت, type, NULL_درخت);
	      اگر (lastarg)
		درخت_CHAIN (lastarg) = t;
	      وگرنه
		newargs = t;
	      lastarg = t;
	    }
	  درخت_CHAIN (lastarg) = args;

	  /* Temporarily stuff newargs into the original base_type.  */
	  درخت saveargs = TYPE_ARG_TYPES (base_type);
	  TYPE_ARG_TYPES (base_type) = newargs;
	  منطقی fail = !comptypes (base_type, variant_type);
	  TYPE_ARG_TYPES (base_type) = saveargs;

	  اگر (fail)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      بازگشت;
	    }
	  وگرنه اگر (unprototyped_variant)
	    /* If we've got an unprototyped variant, copy the transformed
	       base arg types to the variant.  This is needed later by
	       modify_call_for_omp_dispatch.  */
	    TYPE_ARG_TYPES (variant_type) = newargs;
	}
      وگرنه  /* No append_args present.  */
	{
	  اگر (!comptypes (base_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      بازگشت;
	    }
	  وگرنه اگر (TYPE_ARG_TYPES (variant_type) == NULL_درخت
		   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (base_type) != NULL_درخت)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (base_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_USED (variant) = 1;
  درخت construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (match_loc, variant, construct);
  اگر (omp_context_selector_matches (ctx, NULL_درخت, نادرست))
    {
      درخت attr = درخت_cons (get_identifier ("omp declare variant base"),
			     build_درخت_list (variant, ctx),
			     DECL_ATTRIBUTES (fndecl));
      DECL_ATTRIBUTES (fndecl) = attr;
    }

  اگر (need_device_ptr_list || append_args_درخت)
    {
      درخت variant_decl = درخت_strip_nop_conversions (variant);
      درخت t = build_درخت_list (need_device_ptr_list,
				NULL_درخت /* need_device_addr */);
      درخت_CHAIN (t) = append_args_درخت;
      DECL_ATTRIBUTES (variant_decl)
	= درخت_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_ATTRIBUTES (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

ایستا تهی
c_finish_omp_declare_simd (c_parser *parser, درخت fndecl, درخت parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  اگر (clauses.exists () && clauses[0].type == CPP_EOF)
    بازگشت;
  ثابت نویسه *kind = "simd";
  اگر (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    kind = IDENTIFIER_POINTER (clauses[0].مقدار);
  gcc_assert (strcmp (kind, "simd") == 0 || strcmp (kind, "variant") == 0);
  اگر (fndecl == NULL_درخت || درخت_CODE (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      بازگشت;
    }
  اگر (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      بازگشت;
    }
  اگر (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", kind);
      بازگشت;
    }

  اگر (parms == NULL_درخت)
    parms = DECL_ARGUMENTS (fndecl);

  unsigned صحیح tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);

  parser->tokens = clauses.address ();
  parser->tokens_avail = clauses.length ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  وقتی (parser->tokens_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      kind = IDENTIFIER_POINTER (token->مقدار);
      c_parser_consume_token (parser);
      parser->in_pragma = درست;

      اگر (strcmp (kind, "simd") == 0)
	{
	  درخت c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_MASK,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_to_numbers (parms, c);
	  اگر (c != NULL_درخت)
	    c = درخت_cons (NULL_درخت, c, NULL_درخت);
	  c = build_درخت_list (get_identifier ("omp declare simd"), c);
	  درخت_CHAIN (c) = DECL_ATTRIBUTES (fndecl);
	  DECL_ATTRIBUTES (fndecl) = c;
	}
      وگرنه
	{
	  gcc_assert (strcmp (kind, "variant") == 0);
	  c_finish_omp_declare_variant (parser, fndecl, parms);
	}
    }

  parser->tokens = &parser->tokens_buf[0];
  parser->tokens_avail = tokens_avail;
  اگر (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#اگر !defined (NO_DOT_IN_LABEL)
#define JOIN_STR "."
#وگرنهاگر !defined (NO_DOLLAR_IN_LABEL)
#define JOIN_STR "$"
#وگرنه
#define JOIN_STR "_"
#endif

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
ایستا درخت
omp_start_variant_function (c_declarator *declarator, درخت ctx)
{
  c_declarator *id = declarator;
  وقتی (id->kind != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  درخت name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  بازگشت name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
ایستا تهی
omp_finish_variant_function (درخت decl, درخت base_name, درخت ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  درخت base_decl = lookup_name (base_name);
  اگر (base_decl == error_mark_گره)
    base_decl = NULL_درخت;
  اگر (!base_decl)
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_POINTER (base_name));
      بازگشت;
    }

  اگر (!comptypes (درخت_TYPE (decl), درخت_TYPE (base_decl)))
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", base_decl);
      inform (DECL_SOURCE_LOCATION (base_decl),
	      "%qE declared here", base_decl);
      بازگشت;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_SOURCE_LOCATION (decl),
				   base_decl, ctx);
  درخت construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (DECL_SOURCE_LOCATION (decl), decl, construct);
  درخت attrs = DECL_ATTRIBUTES (base_decl);
  درخت match_loc_گره
    = maybe_wrap_with_location (integer_zero_گره,
				DECL_SOURCE_LOCATION (base_decl));
  درخت loc_گره = درخت_cons (match_loc_گره, integer_zero_گره,
			     build_درخت_list (match_loc_گره,
					      integer_zero_گره));
  attrs = درخت_cons (get_identifier ("omp declare variant base"),
		     درخت_cons (decl, ctx, loc_گره), attrs);
  DECL_ATTRIBUTES (base_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  درخت_PUBLIC (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

منطقی
c_maybe_parse_omp_decl (درخت decl, درخت d)
{
  gcc_assert (درخت_CODE (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
  c_token *first = toks->address ();
  c_token *last = first + toks->length ();
  ثابت نویسه *directive[3] = {};
  برای (صحیح j = 0; j < 3; j++)
    {
      درخت id = NULL_درخت;
      اگر (first + j == last)
	بشکن;
      اگر (first[j].type == CPP_NAME)
	id = first[j].مقدار;
      وگرنه اگر (first[j].type == CPP_KEYWORD)
	id = ridpointers[(صحیح) first[j].keyword];
      وگرنه
	بشکن;
      directive[j] = IDENTIFIER_POINTER (id);
    }
  ثابت c_omp_directive *dir = پوچ;
  اگر (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  اگر (dir == پوچ)
    {
      error_at (first->location,
		"unknown OpenMP directive name in "
		"%qs attribute argument", "omp::decl");
      بازگشت نادرست;
    }
  اگر (dir->id != PRAGMA_OMP_THREADPRIVATE
      && dir->id != PRAGMA_OMP_GROUPPRIVATE
      && dir->id != PRAGMA_OMP_ALLOCATE
      && (dir->id != PRAGMA_OMP_DECLARE
	  || strcmp (directive[1], "target") != 0))
    بازگشت نادرست;

  اگر (!flag_openmp && !dir->simd)
    بازگشت درست;

  c_parser *parser = the_parser;
  unsigned صحیح tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);
  toks = پوچ;
  vec_safe_reserve (toks, last - first + 2, درست);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_kind = pragma_kind (dir->id);
  tok.location = first->location;
  toks->quick_افزودن (tok);
  وقتی (++first < last)
    toks->quick_افزودن (*first);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_افزودن (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_افزودن (tok);
  parser->in_omp_decl_attribute = decl;
  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = toks->length ();
  c_parser_pragma (parser, pragma_external, پوچ, NULL_درخت);
  parser->in_omp_decl_attribute = NULL_درخت;
  بازگشت درست;
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

ایستا تهی
c_parser_omp_declare_target (c_parser *parser)
{
  درخت clauses = NULL_درخت;
  صحیح device_type = 0;
  منطقی indirect = نادرست;
  منطقی only_device_type_or_indirect = درست;
  اگر (flag_openmp)
    omp_requires_mask
      = (شمارش omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);
  اگر (c_parser_next_token_is (parser, CPP_NAME)
      || (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp declare target");
  وگرنه اگر (parser->in_omp_decl_attribute
	   || c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      clauses = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					      clauses);
      clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
      c_parser_skip_to_pragma_eol (parser);
    }
  وگرنه
    {
      warning_at (c_parser_peek_token (parser)->location,
		  OPT_Wdeprecated_openmp,
		  "use of %<omp declare target%> as a synonym for "
		  "%<omp begin declare target%> has been deprecated since "
		  "OpenMP 5.2");
      منطقی attr_syntax = parser->in_omp_attribute_pragma != پوچ;
      c_parser_skip_to_pragma_eol (parser);
      c_omp_declare_target_attr attr = { attr_syntax, -1, 0 };
      vec_safe_افزودن (current_omp_declare_target_attribute, attr);
      بازگشت;
    }
  برای (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_عبارت (c));
    }
  برای (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	ادامه;
      درخت t = OMP_CLAUSE_DECL (c), id;
      درخت at1 = lookup_attribute ("omp declare target", DECL_ATTRIBUTES (t));
      درخت at2 = lookup_attribute ("omp declare target link",
				   DECL_ATTRIBUTES (t));
      only_device_type_or_indirect = نادرست;
      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::swap (at1, at2);
	}
      وگرنه
	id = get_identifier ("omp declare target");
      اگر (at2)
	{
	  اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	  وگرنه اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL
		   || مقدار_member (get_identifier ("local"), درخت_مقدار (at2)))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<local%> clauses", t);
	  وگرنه
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<to%> or %<enter%> clauses", t);
	  ادامه;
	}
      اگر (!at1)
	{
	  DECL_ATTRIBUTES (t) = درخت_cons (id, NULL_درخت, DECL_ATTRIBUTES (t));
	  اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    درخت_مقدار (DECL_ATTRIBUTES (t))
	      = درخت_cons (NULL_درخت, get_identifier ("local"),
			   درخت_مقدار (DECL_ATTRIBUTES (t)));

	  اگر (درخت_CODE (t) != FUNCTION_DECL && !is_global_var (t))
	    ادامه;

	  symtab_گره *گره = symtab_گره::get (t);
	  اگر (گره != پوچ)
	    {
	      گره->offloadable = 1;
	      اگر (ENABLE_OFFLOADING)
		{
		  g->have_offload = درست;
		  اگر (is_a <varpool_گره *> (گره)
		      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_LOCAL)
		    vec_safe_افزودن (offload_vars, t);
		}
	    }
	}
      وگرنه
	{
	  منطقی saw_local = مقدار_member (get_identifier ("local"),
					 درخت_مقدار (at1));
	  اگر (saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	      ادامه;
	    }
	  وگرنه اگر (!saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      ادامه;
	    }
	}
      اگر (درخت_CODE (t) != FUNCTION_DECL)
	ادامه;
      اگر ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  درخت at3 = lookup_attribute ("omp declare target host",
				       DECL_ATTRIBUTES (t));
	  اگر (at3 == NULL_درخت)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_ATTRIBUTES (t)
		= درخت_cons (id, NULL_درخت, DECL_ATTRIBUTES (t));
	    }
	}
      اگر ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  درخت at3 = lookup_attribute ("omp declare target nohost",
				       DECL_ATTRIBUTES (t));
	  اگر (at3 == NULL_درخت)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_ATTRIBUTES (t)
		= درخت_cons (id, NULL_درخت, DECL_ATTRIBUTES (t));
	    }
	}
      اگر (indirect)
	{
	  درخت at4 = lookup_attribute ("omp declare target indirect",
				       DECL_ATTRIBUTES (t));
	  اگر (at4 == NULL_درخت)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_ATTRIBUTES (t)
		= درخت_cons (id, NULL_درخت, DECL_ATTRIBUTES (t));
	    }
	}
    }
  اگر ((device_type || indirect) && only_device_type_or_indirect)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  اگر (indirect && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
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

ایستا تهی
c_parser_omp_begin (c_parser *parser)
{
  ثابت نویسه *p = "";
  c_parser_consume_pragma (parser);
  اگر (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
  اگر (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      اگر (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  منطقی attr_syntax = parser->in_omp_attribute_pragma != پوچ;
	  درخت clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp begin declare target");
	  صحیح device_type = 0;
	  صحیح indirect = 0;
	  برای (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
	      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
		indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_عبارت (c));
	    }
	  c_omp_declare_target_attr attr = { attr_syntax, device_type,
					     indirect };
	  vec_safe_افزودن (current_omp_declare_target_attribute, attr);
	}
      وگرنه اگر (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  ثابت نویسه *clause = "";
	  matching_parens parens;
	  location_t match_loc = c_parser_peek_token (parser)->location;
	  اگر (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  اگر (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      درخت id = c_parser_peek_token (parser)->مقدار;
	      clause = IDENTIFIER_POINTER (id);
	    }
	  اگر (strcmp (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_to_pragma_eol (parser);
	      بازگشت;
	    }

	  c_parser_consume_token (parser);

	  اگر (!parens.require_open (parser))
	    {
	      c_parser_skip_to_pragma_eol (parser, نادرست);
	      بازگشت;
	    }

	  درخت ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_درخت);
	  اگر (ctx != error_mark_گره)
	    ctx = omp_check_context_selector (match_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  اگر (ctx != error_mark_گره
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      درخت outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  اگر (ctx == error_mark_گره
	      || !omp_context_selector_matches (ctx, NULL_درخت, نادرست, درست))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_to_pragma_eol (parser, نادرست);
	      c_parser_skip_to_pragma_omp_end_declare_variant (parser);
	      بازگشت;
	    }
	  وگرنه
	    {
	      منطقی attr_syntax = parser->in_omp_attribute_pragma != پوچ;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_safe_افزودن (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_to_pragma_eol (parser);
	}
      وگرنه
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser, نادرست);
	}
    }
  وگرنه اگر (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      منطقی attr_syntax = parser->in_omp_attribute_pragma != پوچ;
      c_parser_omp_assumption_clauses (parser, نادرست);
      ساختار c_omp_begin_assumes_data a = { attr_syntax };
      vec_safe_افزودن (current_omp_begin_assumes, a);
    }
  وگرنه
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

ایستا تهی
c_parser_omp_end (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ثابت نویسه *p = "";
  c_parser_consume_pragma (parser);
  اگر (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
  اگر (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      اگر (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  منطقی attr_syntax = parser->in_omp_attribute_pragma != پوچ;
	  c_parser_skip_to_pragma_eol (parser);
	  اگر (!vec_safe_length (current_omp_declare_target_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  وگرنه
	    {
	      c_omp_declare_target_attr
		a = current_omp_declare_target_attribute->برداشت ();
	      اگر (a.attr_syntax != attr_syntax)
		{
		  اگر (a.attr_syntax)
		    error_at (loc,
			      "%qs in attribute syntax terminated "
			      "with %qs in pragma syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		  وگرنه
		    error_at (loc,
			      "%qs in pragma syntax terminated "
			      "with %qs in attribute syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		}
	    }
	}
      وگرنه اگر (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  منطقی attr_syntax = parser->in_omp_attribute_pragma != پوچ;
	  c_parser_skip_to_pragma_eol (parser);
	  اگر (!vec_safe_length (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  وگرنه
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->برداشت ();
	      اگر (a.attr_syntax != attr_syntax)
		{
		  اگر (a.attr_syntax)
		    error_at (loc,
			      "%<begin declare variant%> in attribute syntax "
			      "terminated with "
			      "%<end declare variant%> in pragma syntax");
		  وگرنه
		    error_at (loc,
			      "%<begin declare variant%> in pragma syntax "
			      "terminated with "
			      "%<end declare variant%> in attribute syntax");
		}
	    }
	}
      وگرنه
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser);
	  بازگشت;
	}
    }
  وگرنه اگر (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      منطقی attr_syntax = parser->in_omp_attribute_pragma != پوچ;
      c_parser_skip_to_pragma_eol (parser);
      اگر (!vec_safe_length (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      وگرنه
	{
	  c_omp_begin_assumes_data
	    a = current_omp_begin_assumes->برداشت ();
	  اگر (a.attr_syntax != attr_syntax)
	    {
	      اگر (a.attr_syntax)
		error_at (loc,
			  "%qs in attribute syntax terminated "
			  "with %qs in pragma syntax",
			  "begin assumes", "end assumes");
	      وگرنه
		error_at (loc,
			  "%qs in pragma syntax terminated "
			  "with %qs in attribute syntax",
			  "begin assumes", "end assumes");
	    }
	}
    }
  وگرنه
    {
      c_parser_error (parser, "expected %<declare%> or %<assumes%>");
      c_parser_skip_to_pragma_eol (parser);
    }
}

/* OpenMP 5.0
   #pragma omp declare mapper ([mapper-identifier :] type var) \
			      [clause [ [,] clause ] ... ] new-line  */

ایستا تهی
c_parser_omp_declare_mapper (c_parser *parser, شمارش pragma_context context)
{
  درخت type, mapper_name = NULL_درخت, var = NULL_درخت, stmt, stmtlist;
  درخت maplist = NULL_درخت, mapper_id, mapper_decl, t;
  c_token *token;

  اگر (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare mapper%> not at file or block scope");
      برو fail;
    }

  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    برو fail;

  token = c_parser_peek_token (parser);

  اگر (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      انتخاب (token->type)
	{
	حالت CPP_NAME:
	  mapper_name = token->مقدار;
	  c_parser_consume_token (parser);
	  بشکن;
	حالت CPP_KEYWORD:
	  اگر (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_درخت;
	      c_parser_consume_token (parser);
	      بشکن;
	    }
	  /* Fallthrough.  */
	پیشفرض:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_to_pragma_eol (parser, نادرست);
	  بازگشت;
	}

      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	برو fail;
    }

  mapper_id = c_omp_mapper_id (mapper_name);
  mapper_decl = c_omp_mapper_decl (mapper_id);

  {
    location_t loc = c_parser_peek_token (parser)->location;
    ساختار c_type_name *ctype = c_parser_type_name (parser);
    type = groktypename (ctype, پوچ, پوچ);
    اگر (type == error_mark_گره)
      برو fail;
    اگر (!RECORD_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_to_pragma_eol (parser, نادرست);
	بازگشت;
      }
    برای (درخت t = DECL_INITIAL (mapper_decl); t; t = درخت_CHAIN (t))
      اگر (comptypes (درخت_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_POINTER (mapper_id)
		      + اندازه ("omp declare mapper ") - 1,
		    type);
	  درخت prevmapper = درخت_مقدار (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_SOURCE_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_to_pragma_eol (parser, نادرست);
	  بازگشت;
	}
  }

  token = c_parser_peek_token (parser);
  اگر (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->مقدار, type);
      c_parser_consume_token (parser);
      DECL_ARTIFICIAL (var) = 1;
    }
  وگرنه
    {
      error_at (token->location, "expected identifier");
      برو fail;
    }

  اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    برو fail;

  افزودن_scope ();
  stmtlist = افزودن_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  وقتی (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);
      اگر (c_kind != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (here, "unexpected clause");
	  برو fail;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, درست);
    }

  اگر (maplist == NULL_درخت)
    {
      error_at (درون_داد_location, "missing %<map%> clause");
      برو fail;
    }
  درخت list;
  برای (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      درخت dvar = OMP_CLAUSE_DECL (list);
      وقتی (!DECL_P (dvar) && درخت_OPERAND_LENGTH (dvar))
	dvar = درخت_OPERAND (dvar, 0);
      اگر (dvar == var)
	بشکن;
    }
  اگر (!list)
    error_at (درون_داد_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_گره (OMP_DECLARE_MAPPER);
  درخت_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  add_stmt (stmt);

  برداشت_stmt_list (stmtlist);
  برداشت_scope ();

  c_parser_skip_to_pragma_eol (parser);

  t = درخت_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  بازگشت;

 fail:
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 4.0
   #pragma omp declare reduction (reduction-id : typename-list : expression) \
      initializer-clause[opt] new-line

   initializer-clause:
      initializer (omp_priv = initializer)
      initializer (function-name (argument-list))  */

ایستا تهی
c_parser_omp_declare_reduction (c_parser *parser, شمارش pragma_context context)
{
  unsigned صحیح tokens_avail = 0, i;
  c_token *saved_tokens = پوچ;
  vec<درخت> types = vNULL;
  vec<c_token> clauses = vNULL;
  شمارش درخت_code reduc_code = ERROR_MARK;
  درخت reduc_id = NULL_درخت;
  درخت type;
  location_t rloc = c_parser_peek_token (parser)->location;

  اگر (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare reduction%> not at file or block scope");
      برو fail;
    }

  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    برو fail;

  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_PLUS:
      reduc_code = PLUS_عبارت;
      بشکن;
    حالت CPP_MULT:
      reduc_code = MULT_عبارت;
      بشکن;
    حالت CPP_MINUS:
      reduc_code = MINUS_عبارت;
      بشکن;
    حالت CPP_AND:
      reduc_code = BIT_AND_عبارت;
      بشکن;
    حالت CPP_XOR:
      reduc_code = BIT_XOR_عبارت;
      بشکن;
    حالت CPP_OR:
      reduc_code = BIT_IOR_عبارت;
      بشکن;
    حالت CPP_AND_AND:
      reduc_code = TRUTH_ANDIF_عبارت;
      بشکن;
    حالت CPP_OR_OR:
      reduc_code = TRUTH_ORIF_عبارت;
      بشکن;
    حالت CPP_NAME:
      ثابت نویسه *p;
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp (p, "min") == 0)
	{
	  reduc_code = MIN_عبارت;
	  بشکن;
	}
      اگر (strcmp (p, "max") == 0)
	{
	  reduc_code = MAX_عبارت;
	  بشکن;
	}
      reduc_id = c_parser_peek_token (parser)->مقدار;
      بشکن;
    پیشفرض:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      برو fail;
    }

  درخت orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_code, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    برو fail;

  وقتی (درست)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      ساختار c_type_name *ctype = c_parser_type_name (parser);
      اگر (ctype != پوچ)
	{
	  type = groktypename (ctype, پوچ, پوچ);
	  اگر (type == error_mark_گره)
	    ;
	  وگرنه اگر ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || درخت_CODE (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_درخت)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  وگرنه اگر (درخت_CODE (type) == FUNCTION_TYPE
		   || درخت_CODE (type) == ARRAY_TYPE)
	    error_at (loc, "function or array type in "
		      "%<#pragma omp declare reduction%>");
	  وگرنه اگر (TYPE_ATOMIC (type))
	    error_at (loc, "%<_Atomic%> qualified type in "
			   "%<#pragma omp declare reduction%>");
	  وگرنه اگر (TYPE_QUALS_NO_ADDR_SPACE (type))
	    error_at (loc, "const, volatile or restrict qualified type in "
			   "%<#pragma omp declare reduction%>");
	  وگرنه
	    {
	      درخت t;
	      برای (t = DECL_INITIAL (reduc_decl); t; t = درخت_CHAIN (t))
		اگر (comptypes (درخت_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_POINTER (reduc_id)
				   + اندازه ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_SOURCE_LOCATION (درخت_VEC_ELT (درخت_مقدار (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    بشکن;
		  }
	      اگر (t == NULL_درخت)
		types.safe_افزودن (type);
	    }
	  اگر (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وگرنه
	    بشکن;
	}
      وگرنه
	بشکن;
    }

  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_empty ())
    {
     fail:
      clauses.release ();
      types.release ();
      وقتی (درست)
	{
	  c_token *token = c_parser_peek_token (parser);
	  اگر (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    بشکن;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_to_pragma_eol (parser);
      بازگشت;
    }

  اگر (types.length () > 1)
    {
      وقتی (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  اگر (token->type == CPP_EOF)
	    برو fail;
	  clauses.safe_افزودن (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_افزودن (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, اندازه (eof_token));
      eof_token.type = CPP_EOF;
      clauses.safe_افزودن (eof_token);
      clauses.safe_افزودن (eof_token);
    }

  صحیح errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_tokens = parser->tokens;
      tokens_avail = parser->tokens_avail;
      اگر (!clauses.is_empty ())
	{
	  parser->tokens = clauses.address ();
	  parser->tokens_avail = clauses.length ();
	  parser->in_pragma = درست;
	}

      منطقی nested = current_function_decl != NULL_درخت;
      اگر (nested)
	c_افزودن_function_context ();
      درخت fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, درست);
      افزودن_scope ();
      درخت stmt = افزودن_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      درخت omp_out = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_out) = 1;
      DECL_CONTEXT (omp_out) = fndecl;
      pushdecl (omp_out);
      درخت omp_in = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_in) = 1;
      DECL_CONTEXT (omp_in) = fndecl;
      pushdecl (omp_in);
      ساختار c_عبارت combiner = c_parser_expression (parser);
      ساختار c_عبارت initializer;
      درخت omp_priv = NULL_درخت, omp_orig = NULL_درخت;
      منطقی bad = نادرست;
      initializer.set_error ();
      اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	bad = درست;
      وگرنه اگر (c_parser_next_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      اگر (!bad
	  && (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->مقدار),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  برداشت_scope ();
	  افزودن_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_گره;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    bad = درست;
	  وگرنه اگر (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      bad = درست;
	    }
	  وگرنه اگر (strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->مقدار),
			   "omp_priv") != 0)
	    {
	      اگر (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_kind != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  bad = درست;
		}
	      وگرنه
		initializer = c_parser_postfix_expression (parser);
	      اگر (initializer.مقدار
		  && درخت_CODE (initializer.مقدار) == CALL_عبارت)
		{
		  صحیح j;
		  درخت c = initializer.مقدار;
		  برای (j = 0; j < call_عبارت_nargs (c); j++)
		    {
		      درخت a = CALL_عبارت_ARG (c, j);
		      STRIP_NOPS (a);
		      اگر (درخت_CODE (a) == ADDR_عبارت
			  && درخت_OPERAND (a, 0) == omp_priv)
			بشکن;
		    }
		  اگر (j == call_عبارت_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  وگرنه
	    {
	      c_parser_consume_token (parser);
	      اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		bad = درست;
	      وگرنه
		{
		  درخت st = افزودن_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (سطر_table, loc);
		  start_init (omp_priv, NULL_درخت, نادرست, نادرست, &richloc);
		  ساختار c_عبارت init = c_parser_initializer (parser, omp_priv);
		  finish_init ();
		  finish_decl (omp_priv, loc, init.مقدار,
		      	       init.original_type, NULL_درخت);
		  برداشت_stmt_list (st);
		}
	    }
	  اگر (!bad
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    bad = درست;
	}

      اگر (!bad)
	{
	  c_parser_skip_to_pragma_eol (parser);

	  درخت t = درخت_cons (type, make_درخت_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_SOURCE_LOCATION (omp_out) = rloc;
	  درخت_VEC_ELT (درخت_مقدار (t), 0) = omp_out;
	  درخت_VEC_ELT (درخت_مقدار (t), 1) = omp_in;
	  درخت_VEC_ELT (درخت_مقدار (t), 2) = combiner.مقدار;
	  walk_درخت (&combiner.مقدار, c_check_omp_declare_reduction_r,
		     &درخت_VEC_ELT (درخت_مقدار (t), 0), پوچ);
	  اگر (omp_priv)
	    {
	      DECL_SOURCE_LOCATION (omp_priv) = rloc;
	      درخت_VEC_ELT (درخت_مقدار (t), 3) = omp_priv;
	      درخت_VEC_ELT (درخت_مقدار (t), 4) = omp_orig;
	      درخت_VEC_ELT (درخت_مقدار (t), 5) = initializer.مقدار;
	      walk_درخت (&initializer.مقدار, c_check_omp_declare_reduction_r,
			 &درخت_VEC_ELT (درخت_مقدار (t), 3), پوچ);
	      walk_درخت (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &درخت_VEC_ELT (درخت_مقدار (t), 3), پوچ);
	    }
	}

      برداشت_stmt_list (stmt);
      برداشت_scope ();
      اگر (cfun->language != پوچ)
	{
	  ggc_free (cfun->language);
	  cfun->language = پوچ;
	}
      set_cfun (پوچ);
      current_function_decl = NULL_درخت;
      اگر (nested)
	c_برداشت_function_context ();

      اگر (!clauses.is_empty ())
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}
      اگر (bad)
	برو fail;
      اگر (errs != errorcount)
	بشکن;
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

ایستا منطقی
c_parser_omp_declare (c_parser *parser, شمارش pragma_context context)
{
  c_parser_consume_pragma (parser);
  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  بازگشت درست;
	}
      اگر (strcmp (p, "reduction") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_reduction (parser, context);
	  بازگشت نادرست;
	}
      اگر (strcmp (p, "mapper") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_mapper (parser, context);
	  بازگشت نادرست;
	}
      اگر (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, نادرست);
	  بازگشت نادرست;
	}
      اگر (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_target (parser);
	  بازگشت نادرست;
	}
      اگر (strcmp (p, "variant") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  بازگشت درست;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_to_pragma_eol (parser);
  بازگشت نادرست;
}

/* OpenMP 5.0
   #pragma omp requires clauses[optseq] new-line  */

ایستا تهی
c_parser_omp_requires (c_parser *parser)
{
  شمارش omp_requires new_req = (شمارش omp_requires) 0;

  c_parser_consume_pragma (parser);

  location_t loc = c_parser_peek_token (parser)->location;
  وقتی (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      اگر (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      اگر (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ثابت نویسه *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  شمارش omp_requires this_req = (شمارش omp_requires) 0;

	  اگر (!strcmp (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_ADDRESS;
	  وگرنه اگر (!strcmp (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_MEMORY;
	  وگرنه اگر (!strcmp (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  وگرنه اگر (!strcmp (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  وگرنه اگر (!strcmp (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_REVERSE_OFFLOAD;
	  وگرنه اگر (!strcmp (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      اگر (parens.require_open (parser))
		{
		  اگر (c_parser_next_token_is (parser, CPP_NAME))
		    {
		      درخت v = c_parser_peek_token (parser)->مقدار;
		      p = IDENTIFIER_POINTER (v);

		      اگر (!strcmp (p, "seq_cst"))
			this_req
			  = (شمارش omp_requires) OMP_MEMORY_ORDER_SEQ_CST;
		      وگرنه اگر (!strcmp (p, "relaxed"))
			this_req
			  = (شمارش omp_requires) OMP_MEMORY_ORDER_RELAXED;
		      وگرنه اگر (!strcmp (p, "release"))
			this_req
			  = (شمارش omp_requires) OMP_MEMORY_ORDER_RELEASE;
		      وگرنه اگر (!strcmp (p, "acq_rel"))
			this_req
			  = (شمارش omp_requires) OMP_MEMORY_ORDER_ACQ_REL;
		      وگرنه اگر (!strcmp (p, "acquire"))
			this_req
			  = (شمارش omp_requires) OMP_MEMORY_ORDER_ACQUIRE;
		    }
		  اگر (this_req == 0)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<acq_rel%>, %<acquire%>, "
				"%<relaxed%>, %<release%> or %<seq_cst%>");
		      انتخاب (c_parser_peek_token (parser)->type)
			{
			حالت CPP_EOF:
			حالت CPP_PRAGMA_EOL:
			حالت CPP_CLOSE_PAREN:
			  بشکن;
			پیشفرض:
			  اگر (c_parser_peek_2nd_token (parser)->type
			      == CPP_CLOSE_PAREN)
			    c_parser_consume_token (parser);
			  بشکن;
			}
		    }
		  وگرنه
		    c_parser_consume_token (parser);

		  parens.skip_until_found_close (parser);
		  اگر (this_req == 0)
		    {
		      c_parser_skip_to_pragma_eol (parser, نادرست);
		      بازگشت;
		    }
		}
	      p = پوچ;
	    }
	  وگرنه
	    {
	      error_at (cloc, "expected %<unified_address%>, "
			      "%<unified_shared_memory%>, "
			      "%<self_maps%>, "
			      "%<dynamic_allocators%>, "
			       "%<reverse_offload%> "
			       "or %<atomic_default_mem_order%> clause");
	      c_parser_skip_to_pragma_eol (parser, نادرست);
	      بازگشت;
	    }
	  اگر (p)
	    c_parser_consume_token (parser);
	  اگر (this_req)
	    {
	      اگر ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  اگر ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  اگر (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_mask & OMP_REQUIRES_TARGET_USED) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      وگرنه اگر ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (شمارش omp_requires) 0;
		}
	      وگرنه اگر ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (شمارش omp_requires)
		       (omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER);
		}
	      وگرنه اگر ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (شمارش omp_requires) (new_req | this_req);
	      omp_requires_mask
		= (شمارش omp_requires) (omp_requires_mask | this_req);
	      ادامه;
	    }
	}
      بشکن;
    }
  c_parser_skip_to_pragma_eol (parser);

  اگر (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

ایستا درخت
c_finish_taskloop_clauses (درخت clauses)
{
  درخت *pc = &clauses;
  برای (درخت c = clauses; c; c = *pc)
    {
      منطقی remove = نادرست;
      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
	{
	  درخت type = strip_array_types (درخت_TYPE (OMP_CLAUSE_DECL (c)));
	  اگر (integer_zerop (TYPE_SIZE_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      remove = درست;
	    }
	  وگرنه اگر (درخت_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      remove = درست;
	    }
	}
      اگر (remove)
	*pc = OMP_CLAUSE_CHAIN (c);
      وگرنه
	pc = &OMP_CLAUSE_CHAIN (c);
    }
  بازگشت clauses;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_رقم_TASKS)	\
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

ایستا درخت
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       نویسه *p_name, omp_clause_mask mask, درخت *cclauses,
		       منطقی *if_p)
{
  درخت clauses, block, ret;

  strcat (p_name, " taskloop");
  mask |= OMP_TASKLOOP_CLAUSE_MASK;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  اگر ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_رقم_THREADS)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IN_REDUCTION);

  اگر (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);

      اگر (strcmp (p, "simd") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_SPLIT_شمار];
	  اگر (cclauses == پوچ)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    بازگشت c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (درست);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, درست);
	  اگر (ret == پوچ)
	    بازگشت ret;
	  ret = make_گره (OMP_TASKLOOP);
	  درخت_TYPE (ret) = void_type_گره;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_finish_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  SET_عبارت_LOCATION (ret, loc);
	  add_stmt (ret);
	  بازگشت ret;
	}
    }
  اگر (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, نادرست);
      بازگشت NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == پوچ);
  اگر (cclauses)
    {
      omp_split_clauses (loc, OMP_TASKLOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
    }

  clauses = c_finish_taskloop_clauses (clauses);
  block = c_begin_compound_stmt (درست);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, پوچ, if_p);
  block = c_end_compound_stmt (loc, block, درست);
  add_stmt (block);

  بازگشت ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
ایستا درخت
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  درخت sizes = NULL_درخت;

  اگر (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  اگر (tok->type != CPP_NAME
      || strcmp ("sizes", IDENTIFIER_POINTER (tok->مقدار)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      بازگشت error_mark_گره;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  اگر (!parens.require_open (parser))
    بازگشت error_mark_گره;

  vec<درخت, va_gc> *sizes_vec
    = c_parser_عبارت_list (parser, درست, درست, پوچ, پوچ, پوچ, پوچ);
  sizes = build_درخت_list_vec (sizes_vec);
  release_درخت_vector (sizes_vec);

  برای (درخت s = sizes; s; s = درخت_CHAIN (s))
    {
      درخت عبارت = درخت_مقدار (s);
      اگر (عبارت == error_mark_گره)
	{
	  parens.skip_until_found_close (parser);
	  بازگشت error_mark_گره;
	}

      HOST_WIDE_INT n;
      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (عبارت))
	  || !درخت_fits_shwi_p (عبارت)
	  || (n = درخت_to_shwi (عبارت)) <= 0
	  || (صحیح) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  درخت_مقدار (s) = integer_one_گره;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  درخت c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  بازگشت c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

ایستا درخت
c_parser_omp_tile (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_to_pragma_eol (parser);

  اگر (!clauses || clauses == error_mark_گره)
    بازگشت error_mark_گره;

  درخت block = c_begin_compound_stmt (درست);
  درخت ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    پوچ, if_p);
  block = c_end_compound_stmt (loc, block, درست);
  add_stmt (block);

  بازگشت ret;
}

#define OMP_UNROLL_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FULL))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

ایستا درخت
c_parser_omp_unroll (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_MASK,
					   "#pragma omp unroll", درست);

  درخت block = c_begin_compound_stmt (درست);
  درخت ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    پوچ, if_p);
  block = c_end_compound_stmt (loc, block, درست);
  add_stmt (block);

  بازگشت ret;
}

/* OpenMP 5.1
   #pragma omp nothing new-line  */

ایستا تهی
c_parser_omp_nothing (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp error clauses[optseq] new-line  */

ایستا منطقی
c_parser_omp_error (c_parser *parser, شمارش pragma_context context)
{
  صحیح at_compilation = -1;
  صحیح severity_fatal = -1;
  درخت message = NULL_درخت;
  منطقی bad = نادرست;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  وقتی (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      اگر (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      اگر (!c_parser_next_token_is (parser, CPP_NAME))
	بشکن;

      ثابت نویسه *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      location_t cloc = c_parser_peek_token (parser)->location;
      ایستا ثابت نویسه *args[] = {
	"execution", "compilation", "warning", "fatal"
      };
      صحیح *v = پوچ;
      صحیح idx = 0, n = -1;
      درخت m = NULL_درخت;

      اگر (!strcmp (p, "at"))
	v = &at_compilation;
      وگرنه اگر (!strcmp (p, "severity"))
	{
	  v = &severity_fatal;
	  idx += 2;
	}
      وگرنه اگر (strcmp (p, "message"))
	{
	  error_at (cloc,
		    "expected %<at%>, %<severity%> or %<message%> clause");
	  c_parser_skip_to_pragma_eol (parser, نادرست);
	  بازگشت نادرست;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      اگر (parens.require_open (parser))
	{
	  اگر (v == پوچ)
	    {
	      location_t عبارت_loc = c_parser_peek_token (parser)->location;
	      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	      عبارت = convert_lvalue_to_rvalue (عبارت_loc, عبارت, درست, درست);
	      m = convert (const_string_type_گره, عبارت.مقدار);
	      m = c_fully_fold (m, نادرست, پوچ);
	    }
	  وگرنه
	    {
	      اگر (c_parser_next_token_is (parser, CPP_NAME))
		{
		  درخت val = c_parser_peek_token (parser)->مقدار;
		  ثابت نویسه *q = IDENTIFIER_POINTER (val);

		  اگر (!strcmp (q, args[idx]))
		    n = 0;
		  وگرنه اگر (!strcmp (q, args[idx + 1]))
		    n = 1;
		}
	      اگر (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", args[idx], args[idx + 1]);
		  bad = درست;
		  انتخاب (c_parser_peek_token (parser)->type)
		    {
		    حالت CPP_EOF:
		    حالت CPP_PRAGMA_EOL:
		    حالت CPP_CLOSE_PAREN:
		      بشکن;
		    پیشفرض:
		      اگر (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)
			c_parser_consume_token (parser);
		      بشکن;
		    }
		}
	      وگرنه
		c_parser_consume_token (parser);
	    }

	  parens.skip_until_found_close (parser);

	  اگر (v == پوچ)
	    {
	      اگر (message)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = درست;
		}
	      وگرنه
		message = m;
	    }
	  وگرنه اگر (n != -1)
	    {
	      اگر (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = درست;
		}
	      وگرنه
		*v = n;
	    }
	}
      وگرنه
	bad = درست;
    }
  c_parser_skip_to_pragma_eol (parser);
  اگر (bad)
    بازگشت درست;

  اگر (at_compilation == -1)
    at_compilation = 1;
  اگر (severity_fatal == -1)
    severity_fatal = 1;
  اگر (!at_compilation)
    {
      اگر (context != pragma_compound)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may only be used in compound statements");
	  بازگشت درست;
	}
      اگر (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->in_intervening_code)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->fail = درست;
	  بازگشت درست;
	}
      درخت fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_IN_GOMP_ERROR
						: BUILT_IN_GOMP_WARNING);
      اگر (!message)
	message = build_zero_cst (const_string_type_گره);
      درخت stmt = build_call_عبارت_loc (loc, fndecl, 2, message,
				       build_all_ones_cst (size_type_گره));
      add_stmt (stmt);
      بازگشت درست;
    }
  ثابت نویسه *پیام = پوچ;
  اگر (message)
    {
      پیام = c_getstr (message);
      اگر (پیام == پوچ)
	پیام = _("<message unknown at compile time>");
    }
  ثابت شمارش diagnostics::kind diag_kind = (severity_fatal
					    ? diagnostics::kind::error
					    : diagnostics::kind::warning);
  اگر (پیام)
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered: %s", پیام);
  وگرنه
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered");
  بازگشت نادرست;
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

ایستا تهی
c_parser_omp_assumption_clauses (c_parser *parser, منطقی is_assume)
{
  منطقی no_openmp = نادرست;
  منطقی no_openmp_constructs = نادرست;
  منطقی no_openmp_routines = نادرست;
  منطقی no_parallelism = نادرست;
  bitmap_head absent_head, contains_head;

  bitmap_obstack_initialize (پوچ);
  bitmap_initialize (&absent_head, &bitmap_default_obstack);
  bitmap_initialize (&contains_head, &bitmap_default_obstack);

  اگر (c_parser_next_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  وقتی (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      اگر (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      اگر (!c_parser_next_token_is (parser, CPP_NAME))
	بشکن;

      ثابت نویسه *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      location_t cloc = c_parser_peek_token (parser)->location;

      اگر (!strcmp (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  اگر (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = درست;
	}
      وگرنه اگر (!strcmp (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  اگر (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = درست;
	}
      وگرنه اگر (!strcmp (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  اگر (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = درست;
	}
      وگرنه اگر (!strcmp (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  اگر (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = درست;
	}
      وگرنه اگر (!strcmp (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  اگر (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, پوچ);
	      درخت t = convert_lvalue_to_rvalue (eloc, عبارت, درست, درست).مقدار;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, نادرست, پوچ);
	      اگر (is_assume && t != error_mark_گره)
		{
		  درخت fn = build_call_عبارت_internal_loc (eloc, IFN_ASSUME,
							  void_type_گره, 1,
							  t);
		  add_stmt (fn);
		}
	      parens.skip_until_found_close (parser);
	    }
	}
      وگرنه اگر (!strcmp (p, "absent") || !strcmp (p, "contains"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  اگر (parens.require_open (parser))
	    {
	      انجامبده
		{
		  ثابت نویسه *directive[3] = {};
		  صحیح i;
		  location_t dloc = c_parser_peek_token (parser)->location;
		  برای (i = 0; i < 3; i++)
		    {
		      درخت id;
		      اگر (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->مقدار;
		      وگرنه اگر (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  شمارش rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      وگرنه
			بشکن;
		      directive[i] = IDENTIFIER_POINTER (id);
		    }
		  اگر (i == 0)
		    error_at (dloc, "expected directive name");
		  وگرنه
		    {
		      ثابت ساختار c_omp_directive *dir
			= c_omp_categorize_directive (directive[0],
						      directive[1],
						      directive[2]);
		      اگر (dir
			  && dir->id != PRAGMA_OMP_END
			  && (dir->kind == C_OMP_DIR_DECLARATIVE
			      || dir->kind == C_OMP_DIR_INFORMATIONAL
			      || dir->kind == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      وگرنه اگر (dir == پوچ
			       || dir->id == PRAGMA_OMP_END
			       || (!dir->second && directive[1])
			       || (!dir->third && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      وگرنه
			{
			  صحیح id = dir - c_omp_directives;
			  اگر (bitmap_bit_p (p[0] == 'a' ? &contains_head
							: &absent_head, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  وگرنه اگر (!bitmap_set_bit (p[0] == 'a'
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
		      برای (; i; --i)
			c_parser_consume_token (parser);
		    }
		  اگر (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  وگرنه
		    بشکن;
		}
	      وقتی (1);
	      parens.skip_until_found_close (parser);
	    }
	}
      وگرنه اگر (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      matching_parens parens;
	      parens.consume_open (parser);
	      c_parser_balanced_token_sequence (parser);
	      parens.require_close (parser);
	    }
	}
      وگرنه
	{
	  c_parser_consume_token (parser);
	  error_at (cloc, "expected assumption clause");
	  بشکن;
	}
    }
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

ایستا تهی
c_parser_omp_assume (c_parser *parser, منطقی *if_p)
{
  c_parser_omp_assumption_clauses (parser, درست);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
}

/* OpenMP 5.1
   #pragma omp assumes clauses[optseq] new-line  */

ایستا تهی
c_parser_omp_assumes (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_omp_assumption_clauses (parser, نادرست);
}

/* Helper function for c_parser_omp_metadirective.  */

ایستا تهی
analyze_metadirective_body (c_parser *parser,
			    vec<c_token> &tokens,
			    vec<درخت> &labels)
{
  صحیح nesting_depth = 0;
  صحیح bracket_depth = 0;
  منطقی ignore_label = نادرست;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  وقتی (1)
    {
      c_token *token = c_parser_peek_token (parser);
      منطقی stop = نادرست;

      اگر (c_parser_next_token_is_keyword (parser, RID_CASE))
	ignore_label = درست;

      انتخاب (token->type)
	{
	حالت CPP_EOF:
	  بشکن;
	حالت CPP_NAME:
	  اگر (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.safe_افزودن (token->مقدار);
	  برو add;
	حالت CPP_OPEN_BRACE:
	  ++nesting_depth;
	  برو add;
	حالت CPP_CLOSE_BRACE:
	  اگر (--nesting_depth == 0 && bracket_depth == 0)
	    stop = درست;
	  برو add;
	حالت CPP_OPEN_PAREN:
	  ++bracket_depth;
	  برو add;
	حالت CPP_CLOSE_PAREN:
	  --bracket_depth;
	  برو add;
	حالت CPP_COLON:
	  ignore_label = نادرست;
	  برو add;
	حالت CPP_SEMICOLON:
	  اگر (nesting_depth == 0 && bracket_depth == 0)
	    stop = درست;
	  برو add;
	پیشفرض:
	add:
	  tokens.safe_افزودن (*token);
	  اگر (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  وگرنه اگر (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_to_pragma_eol (parser);
	  وگرنه
	    c_parser_consume_token (parser);
	  اگر (stop)
	    بشکن;
	  ادامه;
	}
      بشکن;
    }
}

/* OpenMP 5.0:

  # pragma omp metadirective [clause[, clause]]
*/

ایستا تهی
c_parser_omp_metadirective (c_parser *parser, منطقی *if_p)
{
  ایستا unsigned صحیح metadirective_region_شمار = 0;

  درخت ret;
  auto_vec<c_token> directive_tokens;
  auto_vec<c_token> body_tokens;
  auto_vec<درخت> body_labels;
  auto_vec<ثابت ساختار c_omp_directive *> directives;
  auto_vec<درخت> ctxs;
  vec<ساختار omp_variant> candidates;
  منطقی default_seen = نادرست;
  صحیح directive_token_idx = 0;
  درخت standalone_body = NULL_درخت;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  منطقی requires_body = نادرست;

  ret = make_گره (OMP_METADIRECTIVE);
  SET_عبارت_LOCATION (ret, pragma_loc);
  درخت_TYPE (ret) = void_type_گره;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_درخت;

  c_parser_consume_pragma (parser);
  وقتی (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      اگر (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      اگر (c_parser_next_token_is_not (parser, CPP_NAME)
	  && c_parser_next_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  برو error;
	}

      location_t match_loc = c_parser_peek_token (parser)->location;
      ثابت نویسه *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      اگر (strcmp (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.add_fixit_replace (match_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      منطقی default_p
	= strcmp (p, "default") == 0 || strcmp (p, "otherwise") == 0;
      اگر (default_p)
	{
	  اگر (default_seen)
	    {
	      error_at (match_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      برو error;
	    }
	  default_seen = درست;
	}
      وگرنه اگر (default_seen)
	{
	  error_at (match_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  برو error;
	}
      اگر (!default_p && strcmp (p, "when") != 0)
	{
	  error_at (match_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  برو error;
	}

      matching_parens parens;
      درخت ctx = NULL_درخت;
      منطقی skip = نادرست;

      اگر (!parens.require_open (parser))
	برو error;

      اگر (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_درخت);
	  اگر (ctx == error_mark_گره)
	    برو error;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  اگر (ctx == error_mark_گره)
	    برو error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_درخت, نادرست) == 0);

	  اگر (c_parser_next_token_is_not (parser, CPP_COLON))
	    {
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      برو error;
	    }
	  c_parser_consume_token (parser);
	}

      /* Read in the directive type and create a dummy pragma token for
	 it.  */
      location_t loc = c_parser_peek_token (parser)->location;

      ثابت نویسه *directive[3] = {};
      صحیح i;
      برای (i = 0; i < 3; i++)
	{
	  درخت id;
	  اگر (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      اگر (i == 0)
		directive[i++] = "nothing";
	      بشکن;
	    }
	  وگرنه اگر (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->مقدار;
	  وگرنه اگر (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      شمارش rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  وگرنه
	    بشکن;

	  directive[i] = IDENTIFIER_POINTER (id);
	}
      اگر (i == 0)
	{
	  error_at (loc, "expected directive name");
	  برو error;
	}

      ثابت ساختار c_omp_directive *omp_directive
	= c_omp_categorize_directive (directive[0],
				      directive[1],
				      directive[2]);

      اگر (omp_directive == پوچ)
	{
	  برای (صحیح j = 0; j < i; j++)
	    c_parser_consume_token (parser);
	  c_parser_error (parser, "unknown directive name");
	  برو error;
	}
      وگرنه
	{
	  صحیح token_شمار = 0;
	  اگر (omp_directive->first) token_شمار++;
	  اگر (omp_directive->second) token_شمار++;
	  اگر (omp_directive->third) token_شمار++;
	  برای (صحیح j = 0; j < token_شمار; j++)
	    c_parser_consume_token (parser);
	}
      اگر (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  برو error;
	}
      اگر (omp_directive->kind == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  برو error;
	}
      اگر (omp_directive->kind == C_OMP_DIR_CONSTRUCT)
	requires_body = درست;

      اگر (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_kind = (شمارش pragma_kind) omp_directive->id;

	  directives.safe_افزودن (omp_directive);
	  directive_tokens.safe_افزودن (pragma_token);
	  ctxs.safe_افزودن (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      صحیح nesting_depth = 0;
      وقتی (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  انتخاب (token->type)
	    {
	    حالت CPP_EOF:
	    حالت CPP_PRAGMA_EOL:
	      بشکن;
	    حالت CPP_OPEN_PAREN:
	      ++nesting_depth;
	      برو add;
	    حالت CPP_CLOSE_PAREN:
	      اگر (nesting_depth-- == 0)
		{
		  c_parser_consume_token (parser);
		  بشکن;
		}
	      برو add;
	    پیشفرض:
	    add:
	      اگر (!skip)
		directive_tokens.safe_افزودن (*token);
	      c_parser_consume_token (parser);
	      ادامه;
	    }
	  بشکن;
	}

      اگر (!skip)
	{
	  c_token eol_token;
	  memset (&eol_token, 0, اندازه (eol_token));
	  eol_token.type = CPP_PRAGMA_EOL;
	  directive_tokens.safe_افزودن (eol_token);
	}
    }
  c_parser_skip_to_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  اگر (ctxs.length () == 1)
    {
      درخت ctx = ctxs[0];
      اگر (ctx == NULL_درخت
	  || (omp_context_selector_matches (ctx, NULL_درخت, نادرست) == 1
	      && directive_tokens[0].pragma_kind == PRAGMA_OMP_NOTHING))
	بازگشت;
    }

  اگر (!default_seen)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      ثابت ساختار c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", پوچ, پوچ);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_kind = PRAGMA_OMP_NOTHING;

      directives.safe_افزودن (omp_directive);
      directive_tokens.safe_افزودن (pragma_token);
      ctxs.safe_افزودن (NULL_درخت);

      c_token eol_token;
      memset (&eol_token, 0, اندازه (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_tokens.safe_افزودن (eol_token);
    }

  اگر (requires_body)
    analyze_metadirective_body (parser, body_tokens, body_labels);

  /* Process each candidate directive.  */
  unsigned i;
  درخت ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> tokens;

      /* Add the directive tokens.  */
      انجامبده
	tokens.safe_افزودن (directive_tokens [directive_token_idx++]);
      وقتی (tokens.last ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_tokens.is_empty ());
      برای (unsigned j = 0; j < body_tokens.length (); j++)
	tokens.safe_افزودن (body_tokens[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, اندازه (eof_token));
      eof_token.type = CPP_EOF;
      tokens.safe_افزودن (eof_token);
      tokens.safe_افزودن (eof_token);

      unsigned صحیح old_tokens_avail = parser->tokens_avail;
      c_token *old_tokens = parser->tokens;
      ساختار omp_attribute_pragma_state *old_in_omp_attribute_pragma
	= parser->in_omp_attribute_pragma;
      ساختار omp_metadirective_parse_data *old_state
	= parser->omp_metadirective_state;

      ساختار omp_metadirective_parse_data new_state;
      new_state.body_labels = &body_labels;
      new_state.region_رقم = ++metadirective_region_شمار;

      parser->tokens = tokens.address ();
      parser->tokens_avail = tokens.length ();
      parser->in_omp_attribute_pragma = پوچ;
      parser->omp_metadirective_state = &new_state;

      صحیح prev_errorcount = errorcount;
      درخت directive = c_begin_compound_stmt (درست);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_درخت);
      directive = c_end_compound_stmt (pragma_loc, directive, درست);
      منطقی standalone_p
	= directives[i]->kind == C_OMP_DIR_STANDALONE
	  || directives[i]->kind == C_OMP_DIR_UTILITY;
      اگر (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  اگر (standalone_body == NULL_درخت)
	    {
	      standalone_body = افزودن_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = برداشت_stmt_list (standalone_body);
	    }
	  وگرنه
	    c_parser_skip_to_end_of_block_or_statement (parser, درست);
	}

      درخت body = standalone_p ? standalone_body : NULL_درخت;
      درخت variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      اگر (errorcount == prev_errorcount)
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
  اگر (!candidates.is_empty ())
    ret = c_omp_expand_variant_construct (candidates);

  add_stmt (ret);
  بازگشت;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  اگر (parser->in_pragma)
    c_parser_skip_to_pragma_eol (parser, نادرست);
}

/* Main entry point to parsing most OpenMP pragmas.  */

ایستا تهی
c_parser_omp_construct (c_parser *parser, منطقی *if_p)
{
  شمارش pragma_kind p_kind;
  location_t loc;
  درخت stmt;
  نویسه p_name[اندازه "#pragma omp teams distribute parallel for simd"];
  omp_clause_mask mask (0);

  loc = c_parser_peek_token (parser)->location;
  p_kind = c_parser_peek_token (parser)->pragma_kind;
  c_parser_consume_pragma (parser);

  انتخاب (p_kind)
    {
    حالت PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, درست);
      بازگشت;
    حالت PRAGMA_OACC_CACHE:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      بشکن;
    حالت PRAGMA_OACC_DATA:
      stmt = c_parser_oacc_data (loc, parser, if_p);
      بشکن;
    حالت PRAGMA_OACC_HOST_DATA:
      stmt = c_parser_oacc_host_data (loc, parser, if_p);
      بشکن;
    حالت PRAGMA_OACC_KERNELS:
    حالت PRAGMA_OACC_PARALLEL:
    حالت PRAGMA_OACC_SERIAL:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_kind, p_name, if_p);
      بشکن;
    حالت PRAGMA_OACC_LOOP:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, mask, پوچ, if_p);
      بشکن;
    حالت PRAGMA_OACC_WAIT:
      strcpy (p_name, "#pragma wait");
      stmt = c_parser_oacc_wait (loc, parser, p_name);
      بشکن;
    حالت PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (loc, parser, نادرست);
      بازگشت;
    حالت PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (loc, parser, if_p);
      بشکن;
    حالت PRAGMA_OMP_DISTRIBUTE:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_distribute (loc, parser, p_name, mask, پوچ, if_p);
      بشکن;
    حالت PRAGMA_OMP_FOR:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, mask, پوچ, if_p);
      بشکن;
    حالت PRAGMA_OMP_LOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, mask, پوچ, if_p);
      بشکن;
    حالت PRAGMA_OMP_MASKED:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, mask, پوچ, if_p);
      بشکن;
    حالت PRAGMA_OMP_MASTER:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, mask, پوچ, if_p,
				  UNKNOWN_LOCATION);
      بشکن;
    حالت PRAGMA_OMP_PARALLEL:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, mask, پوچ, if_p);
      بشکن;
    حالت PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      بشکن;
    حالت PRAGMA_OMP_SECTIONS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, mask, پوچ);
      بشکن;
    حالت PRAGMA_OMP_SIMD:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, mask, پوچ, if_p);
      بشکن;
    حالت PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (loc, parser, if_p);
      بشکن;
    حالت PRAGMA_OMP_TASK:
      stmt = c_parser_omp_task (loc, parser, if_p);
      بشکن;
    حالت PRAGMA_OMP_TASKGROUP:
      stmt = c_parser_omp_taskgroup (loc, parser, if_p);
      بشکن;
    حالت PRAGMA_OMP_TASKLOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_taskloop (loc, parser, p_name, mask, پوچ, if_p);
      بشکن;
    حالت PRAGMA_OMP_TEAMS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, mask, پوچ, if_p);
      بشکن;
    حالت PRAGMA_OMP_ASSUME:
      c_parser_omp_assume (parser, if_p);
      بازگشت;
    حالت PRAGMA_OMP_TILE:
      stmt = c_parser_omp_tile (loc, parser, if_p);
      بشکن;
    حالت PRAGMA_OMP_UNROLL:
      stmt = c_parser_omp_unroll (loc, parser, if_p);
      بشکن;
    حالت PRAGMA_OMP_DISPATCH:
      stmt = c_parser_omp_dispatch (loc, parser);
      بشکن;
    پیشفرض:
      gcc_unreachable ();
    }

  اگر (stmt && stmt != error_mark_گره)
    gcc_assert (عبارت_LOCATION (stmt) != UNKNOWN_LOCATION);
}

/* OpenMP 6.0:
   # pragma omp groupprivate (variable-list) [device_type(...)]  */

#define OMP_GROUPPRIVATE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE) )

ایستا تهی
c_parser_omp_groupprivate (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  درخت vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, پوچ);
  درخت clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_MASK,
					   "#pragma omp groupprivate");
  /* TODO: Implies 'declare target local' with specified device_type, check for
     conflicts.  Check for other restrictions.  */
  (تهی) vars;
  (تهی) clauses;
  sorry_at (loc, "%<omp groupprivate%>");
}

/* OpenMP 2.5:
   # pragma omp threadprivate (variable-list) */

ایستا تهی
c_parser_omp_threadprivate (c_parser *parser)
{
  درخت vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, پوچ);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  برای (t = vars; t; t = درخت_CHAIN (t))
    {
      درخت v = درخت_PURPOSE (t);
      loc = عبارت_LOCATION (درخت_مقدار (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      اگر (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      وگرنه اگر (درخت_USED (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      وگرنه اگر (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      وگرنه اگر (درخت_TYPE (v) == error_mark_گره)
	;
      وگرنه اگر (! COMPLETE_TYPE_P (درخت_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      وگرنه
	{
	  اگر (! DECL_THREAD_LOCAL_P (v))
	    {
	      set_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      اگر (DECL_RTL_SET_P (v))
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

ایستا درخت
c_parser_transaction_attributes (c_parser *parser)
{
  اگر (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    بازگشت c_parser_gnu_attributes (parser);

  اگر (!c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
    بازگشت NULL_درخت;
  بازگشت c_parser_std_attribute_specifier (parser, درست);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

ایستا درخت
c_parser_transaction (c_parser *parser, شمارش rid keyword)
{
  unsigned صحیح old_in = parser->in_transaction;
  unsigned صحیح this_in = 1, new_in;
  location_t loc = c_parser_peek_token (parser)->location;
  درخت stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  اگر (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  وگرنه
    {
      attrs = c_parser_transaction_attributes (parser);
      اگر (attrs)
	this_in |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_in = this_in | (old_in & TM_STMT_ATTR_OUTER);

  parser->in_transaction = new_in;
  stmt = c_parser_compound_statement (parser);
  parser->in_transaction = old_in;

  اگر (flag_tm)
    stmt = c_finish_transaction (loc, stmt, this_in);
  وگرنه
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  بازگشت stmt;
}

/* Parse a __transaction_atomic or __transaction_relaxed expression
   (GCC Extension).

   transaction-expression:
     __transaction_atomic ( expression )
     __transaction_relaxed ( expression )
*/

ایستا ساختار c_عبارت
c_parser_transaction_expression (c_parser *parser, شمارش rid keyword)
{
  ساختار c_عبارت ret;
  unsigned صحیح old_in = parser->in_transaction;
  unsigned صحیح this_in = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  درخت attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  اگر (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  وگرنه
    {
      attrs = c_parser_transaction_attributes (parser);
      اگر (attrs)
	this_in |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->in_transaction = this_in;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      درخت عبارت = c_parser_expression (parser).مقدار;
      ret.original_type = درخت_TYPE (عبارت);
      ret.مقدار = build1 (TRANSACTION_عبارت, ret.original_type, عبارت);
      اگر (this_in & TM_STMT_ATTR_RELAXED)
	TRANSACTION_عبارت_RELAXED (ret.مقدار) = 1;
      SET_عبارت_LOCATION (ret.مقدار, loc);
      ret.original_code = TRANSACTION_عبارت;
      ret.m_decimal = 0;
      اگر (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, پوچ);
	  برو error;
	}
    }
  وگرنه
    {
     error:
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = پوچ;
    }
  parser->in_transaction = old_in;

  اگر (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  set_c_عبارت_source_range (&ret, loc, loc);

  بازگشت ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

ایستا درخت
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت attrs;
  منطقی is_outer = نادرست;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_attributes (parser);
  اگر (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  اگر (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      برو ret_error;
    }
  وگرنه اگر (parser->in_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      برو ret_error;
    }
  وگرنه اگر (is_outer)
    {
      اگر ((parser->in_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  برو ret_error;
	}
    }
  وگرنه اگر (parser->in_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      برو ret_error;
    }

  بازگشت add_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  بازگشت build1 (NOP_عبارت, void_type_گره, error_mark_گره);
}

/* Parse a single source file.  */

تهی
c_parse_file (تهی)
{
  /* Use local storage to begin.  If the first token is a pragma, parse it.
     If it is #pragma GCC pch_preprocess, then this will load a PCH file
     which will cause garbage collection.  */
  c_parser tparser;

  memset (&tparser, 0, اندازه tparser);
  tparser.translate_strings_p = درست;
  tparser.tokens = &tparser.tokens_buf[0];
  the_parser = &tparser;

  اگر (c_parser_peek_token (&tparser)->pragma_kind == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  وگرنه
    c_common_no_more_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  اگر (tparser.tokens == &tparser.tokens_buf[0])
    the_parser->tokens = &the_parser->tokens_buf[0];

  /* Initialize EH, if we've been told to do so.  */
  اگر (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = پوچ;
}

تهی
c_init_preprocess (تهی)
{
  /* Create a parser for use by pragma_lex during preprocessing.  */
  the_parser = ggc_alloc<c_parser> ();
  memset (the_parser, 0, اندازه (c_parser));
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
c_parser_parse_rtl_body (c_parser *parser, نویسه *start_with_pass)
{
  اگر (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      آزاد (start_with_pass);
      بازگشت c_parser_peek_token (parser)->location;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  صحیح رقم_open_braces = 1;
  وقتی (1)
    {
      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_OPEN_BRACE:
	  رقم_open_braces++;
	  بشکن;
	حالت CPP_CLOSE_BRACE:
	  اگر (--رقم_open_braces == 0)
	    برو found_closing_brace;
	  بشکن;
	حالت CPP_EOF:
	  error_at (start_loc, "no closing brace");
	  آزاد (start_with_pass);
	  بازگشت c_parser_peek_token (parser)->location;
	پیشفرض:
	  بشکن;
	}
      c_parser_consume_token (parser);
    }

 found_closing_brace:
  /* At the closing brace; record its location.  */
  location_t end_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  اگر (!read_rtl_function_body_from_file_range (start_loc, end_loc))
    {
      آزاد (start_with_pass);
      بازگشت end_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  run_rtl_passes (start_with_pass);
  بازگشت end_loc;
}

#شامل "gt-c-c-parser.h"
