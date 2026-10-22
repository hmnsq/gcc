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

#ضمن "config.h"
#define INCLUDE_STRING
#ضمن "system.h"
#ضمن "coretypes.h"
#ضمن "target.h"
#ضمن "function.h"
#ضمن "c-tree.h"
#ضمن "timevar.h"
#ضمن "stringpool.h"
#ضمن "cgraph.h"
#ضمن "attribs.h"
#ضمن "stor-layout.h"
#ضمن "varasm.h"
#ضمن "trans-mem.h"
#ضمن "c-family/c-pragma.h"
#ضمن "c-lang.h"
#ضمن "c-family/c-objc.h"
#ضمن "plugin.h"
#ضمن "omp-general.h"
#ضمن "omp-offload.h"
#ضمن "builtins.h"
#ضمن "gomp-constants.h"
#ضمن "c-family/c-indentation.h"
#ضمن "gimple-expr.h"
#ضمن "context.h"
#ضمن "gcc-rich-location.h"
#ضمن "c-parser.h"
#ضمن "gimple-parser.h"
#ضمن "read-rtl-function.h"
#ضمن "run-rtl-passes.h"
#ضمن "intl.h"
#ضمن "c-family/name-hint.h"
#ضمن "tree-iterator.h"
#ضمن "tree-pretty-print.h"
#ضمن "memmodel.h"
#ضمن "c-family/known-headers.h"
#ضمن "bitmap.h"
#ضمن "analyzer/analyzer-language.h"
#ضمن "toplev.h"
#ضمن "asan.h"
#ضمن "c-family/c-ubsan.h"
#ضمن "gcc-urlifier.h"

/* We need to walk over decls with incomplete struct/union/enum types
   after parsing the whole translation unit.
   In finish_decl(), if the decl is static, has incomplete
   struct/union/enum type, it is appended to incomplete_record_decls.
   In c_parser_translation_unit(), we iterate over incomplete_record_decls
   and report error if any of the decls are still incomplete.  */

vec<بشيا> incomplete_record_decls;

فراغ
set_c_فرچ_source_range (c_فرچ *فرچ,
			 location_t start, location_t finish)
{
  فرچ->src_range.m_start = start;
  فرچ->src_range.m_finish = finish;
  إذا (فرچ->درج)
    set_source_range (فرچ->درج, start, finish);
}

فراغ
set_c_فرچ_source_range (c_فرچ *فرچ,
			 source_range src_range)
{
  فرچ->src_range = src_range;
  إذا (فرچ->درج)
    set_source_range (فرچ->درج, src_range);
}


/* Initialization routine for this file.  */

فراغ
c_parse_init (فراغ)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  unsigned صحيح i;
  بشيا id;
  صحيح mask = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  mask |= D_CXXONLY;
  إذا (!flag_isoc99)
    mask |= D_C99;
  إذا (!flag_isoc23)
    mask |= D_C23;
  إذا (flag_no_asm)
    {
      mask |= D_ASM | D_EXT;
      إذا (!flag_isoc99)
	mask |= D_EXT89;
      إذا (!flag_isoc23)
	mask |= D_EXT11;
    }
  إذا (!c_dialect_objc ())
    mask |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<بشيا> ((صحيح) RID_MAX);
  لكل (i = 0; i < لمب_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      إذا (c_common_reswords[i].disable & mask)
	{
	  إذا (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].word);
	      C_SET_RID_CODE (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_WORD (id) = 1;
	    }
	  استمر;
	}

      id = get_identifier (c_common_reswords[i].word);
      C_SET_RID_CODE (id, c_common_reswords[i].rid);
      C_IS_RESERVED_WORD (id) = 1;
      ridpointers [(صحيح) c_common_reswords[i].rid] = id;
    }

  لكل (i = 0; i < لمب_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      حرف name[50];
      sprintf (name, "__int%d", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;

      sprintf (name, "__int%d__", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;
    }

  إذا (flag_openmp)
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
بنية GTY(()) c_parser {
  /* The look-ahead tokens.  */
  c_token * GTY((skip)) tokens;
  /* Buffer for look-ahead tokens.  */
  c_token tokens_buf[4];
  /* How many look-ahead tokens are available (0 - 4, or
     more if parsing from pre-lexed tokens).  */
  unsigned صحيح tokens_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_tokens;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  unsigned صحيح raw_tokens_used;
  /* True if a syntax error is being recovered from; false otherwise.
     c_parser_error sets this flag.  It should clear this flag when
     enough tokens have been consumed to recover from the error.  */
  منطقي error : 1;
  /* True if we're processing a pragma, and shouldn't automatically
     consume CPP_PRAGMA_EOL.  */
  منطقي in_pragma : 1;
  /* True if we're parsing the outermost block of an if statement.  */
  منطقي in_if_block : 1;
  /* True if we want to lex a translated, joined string (for an
     initial #pragma pch_preprocess).  Otherwise the parser is
     responsible for concatenating strings and translating to the
     execution character set as needed.  */
  منطقي lex_joined_string : 1;
  /* True if, when the parser is concatenating string literals, it
     should translate them to the execution character set (false
     inside attributes).  */
  منطقي translate_strings_p : 1;

  /* Objective-C specific parser/lexer information.  */

  /* True if we are in a context where the Objective-C "PQ" keywords
     are considered keywords.  */
  منطقي objc_pq_context : 1;
  /* True if we are parsing a (potential) Objective-C foreach
     statement.  This is set to true after we parsed 'for (' and while
     we wait for 'in' or ';' to decide if it's a standard C for loop or an
     Objective-C foreach loop.  */
  منطقي objc_could_be_foreach_context : 1;
  /* The following flag is needed to contextualize Objective-C lexical
     analysis.  In some cases (e.g., 'int NSObject;'), it is
     undesirable to bind an identifier to an Objective-C class, even
     if a class with that name exists.  */
  منطقي objc_need_raw_identifier : 1;
  /* Nonzero if we're processing a __transaction statement.  The value
     is 1 | TM_STMT_ATTR_*.  */
  unsigned صحيح in_transaction : 4;
  /* True if we are in a context where the Objective-C "Property attribute"
     keywords are valid.  */
  منطقي objc_property_attr_context : 1;

  /* Whether we have just seen/constructed a string-literal.  Set when
     returning a string-literal from c_parser_string_literal.  Reset
     in consume_token.  Useful when we get a parse error and see an
     unknown token, which could have been a string-literal constant
     macro.  */
  منطقي seen_string_literal : 1;

  /* TRUE if omp::directive, omp::decl or omp::sequence attributes may not
     appear.  */
  منطقي omp_attrs_forbidden_p : 1;

  /* Location of the last consumed token.  */
  location_t last_token_location;

  /* Holds state for parsing collapsed OMP_FOR loops.  Managed by
     c_parser_omp_for_loop.  */
  بنية omp_for_parse_data * GTY((skip)) omp_for_parse_state;

  /* If we're in the context of OpenMP directives written as C23
     attributes turned into pragma, the tokens field is temporarily
     redirected.  This holds data needed to restore state afterwards.
     It's NULL otherwise.  */
  بنية omp_attribute_pragma_state *in_omp_attribute_pragma;

  /* Set for omp::decl attribute parsing to the decl to which it
     appertains.  */
  بشيا in_omp_decl_attribute;

  /* Non-null only when parsing the body of an OpenMP metadirective.
     Managed by c_parser_omp_metadirective.  */
  بنية omp_metadirective_parse_data * GTY((skip))
    omp_metadirective_state;
};

/* Holds data needed to restore the token stream to its previous state
   after parsing an OpenMP attribute-syntax pragma.  */
بنية GTY(()) omp_attribute_pragma_state
{
  vec<c_token, va_gc> *token_vec;
  c_token * GTY((skip)) save_tokens;
  unsigned صحيح save_tokens_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
بنية GTY(()) omp_begin_declare_variant_map_entry {
  بشيا variant;		/* The variant decl.  */
  بشيا id;		/* Name of base function.  */
  بشيا ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_entry, va_gc> *omp_begin_declare_variant_map;

ساكن بشيا omp_start_variant_function (c_declarator *, بشيا);
ساكن فراغ omp_finish_variant_function (بشيا, بشيا, بشيا);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_tokens_buf (c_parser *parser, unsigned n)
{
  أرجع &parser->tokens_buf[n];
}

/* Return the error state of PARSER.  */

منطقي
c_parser_error (c_parser *parser)
{
  أرجع parser->error;
}

/* Set the error state of PARSER to ERR.  */

فراغ
c_parser_set_error (c_parser *parser, منطقي err)
{
  parser->error = err;
}


/* The actual parser and external interface.  ??? Does this need to be
   garbage-collected?  */

ساكن GTY (()) c_parser *the_parser;

/* Read in and lex a single token, storing it in *TOKEN.  If RAW,
   context-sensitive postprocessing of the token is not done.  */

ساكن فراغ
c_lex_one_token (c_parser *parser, c_token *token, منطقي raw = خطأ)
{
  timevar_تور (TV_LEX);

  إذا (raw || vec_safe_length (parser->raw_tokens) == 0)
    {
      token->type = c_lex_with_flags (&token->درج, &token->location,
				      &token->flags,
				      (parser->lex_joined_string
				       ? 0 : C_LEX_STRING_NO_JOIN));
      token->id_kind = C_ID_NONE;
      token->keyword = RID_MAX;
      token->pragma_kind = PRAGMA_NONE;
    }
  وإلا
    {
      /* Use a token previously lexed as a raw look-ahead token, and
	 complete the processing on it.  */
      *token = (*parser->raw_tokens)[parser->raw_tokens_used];
      ++parser->raw_tokens_used;
      إذا (parser->raw_tokens_used == vec_safe_length (parser->raw_tokens))
	{
	  vec_free (parser->raw_tokens);
	  parser->raw_tokens_used = 0;
	}
    }

  إذا (raw)
    اذهب out;

  بدل (token->type)
    {
    حالة CPP_NAME:
      {
	بشيا decl;

	منطقي objc_force_identifier = parser->objc_need_raw_identifier;
	إذا (c_dialect_objc ())
	  parser->objc_need_raw_identifier = خطأ;

	إذا (C_IS_RESERVED_WORD (token->درج))
	  {
	    تعداد rid rid_code = C_RID_CODE (token->درج);

	    إذا (rid_code == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->درج);
	      }
	    وإلا إذا (rid_code >= RID_FIRST_ADDR_SPACE
		     && rid_code <= RID_LAST_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_code - RID_FIRST_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_kind = C_ID_ADDRSPACE;
		token->keyword = rid_code;
		اكسر;
	      }
	    وإلا إذا (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		إذا (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    اكسر;
		  }
		وإلا إذا (parser->objc_could_be_foreach_context
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
		    اكسر;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    وإلا إذا (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		إذا (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    اكسر;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    وإلا إذا (c_dialect_objc ()
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
	    وإلا
	      {
		token->type = CPP_KEYWORD;
		token->keyword = rid_code;
		اكسر;
	      }
	  }

	decl = lookup_name (token->درج);
	إذا (decl)
	  {
	    إذا (بشيا_CODE (decl) == TYPE_DECL)
	      {
		token->id_kind = C_ID_TYPENAME;
		اكسر;
	      }
	  }
	وإلا إذا (c_dialect_objc ())
	  {
	    بشيا objc_interface_decl = objc_is_class_name (token->درج);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    إذا (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->درج = objc_interface_decl;
		token->id_kind = C_ID_CLASSNAME;
		اكسر;
	      }
	  }
        token->id_kind = C_ID_ID;
      }
      اكسر;
    حالة CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      بدل (C_RID_CODE (token->درج))
	{
	  /* Replace 'class' with '@class', 'private' with '@private',
	     etc.  This prevents confusion with the C++ keyword
	     'class', and makes the tokens consistent with other
	     Objective-C 'AT' keywords.  For example '@class' is
	     reported as RID_AT_CLASS which is consistent with
	     '@synchronized', which is reported as
	     RID_AT_SYNCHRONIZED.
	  */
	حالة RID_CLASS:     token->keyword = RID_AT_CLASS; اكسر;
	حالة RID_PRIVATE:   token->keyword = RID_AT_PRIVATE; اكسر;
	حالة RID_PROTECTED: token->keyword = RID_AT_PROTECTED; اكسر;
	حالة RID_PUBLIC:    token->keyword = RID_AT_PUBLIC; اكسر;
	حالة RID_THROW:     token->keyword = RID_AT_THROW; اكسر;
	حالة RID_TRY:       token->keyword = RID_AT_TRY; اكسر;
	حالة RID_CATCH:     token->keyword = RID_AT_CATCH; اكسر;
	حالة RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; اكسر;
	افتراضي:            token->keyword = C_RID_CODE (token->درج);
	}
      اكسر;
    حالة CPP_COLON:
    حالة CPP_COMMA:
    حالة CPP_CLOSE_PAREN:
    حالة CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      إذا (c_dialect_objc ())
	parser->objc_need_raw_identifier = خطأ;
      اكسر;
    حالة CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_kind = (تعداد pragma_kind) بشيا_INT_CST_كس (token->درج);
      token->درج = عدم;
      اكسر;
    افتراضي:
      اكسر;
    }
 out:
  timevar_چرو (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  إذا (parser->tokens_avail == 0)
    {
      c_lex_one_token (parser, &parser->tokens[0]);
      parser->tokens_avail = 1;
    }
  أرجع &parser->tokens[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  إذا (parser->tokens_avail >= 2)
    أرجع &parser->tokens[1];
  gcc_assert (parser->tokens_avail == 1);
  gcc_assert (parser->tokens[0].type != CPP_EOF);
  gcc_assert (parser->tokens[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->tokens[1]);
  parser->tokens_avail = 2;
  أرجع &parser->tokens[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, unsigned صحيح n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  إذا (parser->tokens_avail >= n)
    أرجع &parser->tokens[n - 1];
  gcc_assert (parser->tokens_avail == n - 1);
  c_lex_one_token (parser, &parser->tokens[n - 1]);
  parser->tokens_avail = n;
  أرجع &parser->tokens[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, unsigned صحيح n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  إذا (parser->tokens_avail >= n)
    أرجع &parser->tokens[n - 1];
  unsigned صحيح raw_len = vec_safe_length (parser->raw_tokens);
  unsigned صحيح raw_avail
    = parser->tokens_avail + raw_len - parser->raw_tokens_used;
  gcc_assert (raw_avail >= n - 1);
  إذا (raw_avail >= n)
    أرجع &(*parser->raw_tokens)[parser->raw_tokens_used
				  + n - 1 - parser->tokens_avail];
  vec_safe_reserve (parser->raw_tokens, 1);
  parser->raw_tokens->quick_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_tokens)[raw_len], true);
  أرجع &(*parser->raw_tokens)[raw_len];
}

منطقي
c_keyword_starts_typename (تعداد rid keyword)
{
  بدل (keyword)
    {
    حالة RID_UNSIGNED:
    حالة RID_LONG:
    حالة RID_SHORT:
    حالة RID_SIGNED:
    حالة RID_COMPLEX:
    حالة RID_INT:
    حالة RID_CHAR:
    حالة RID_FLOAT:
    حالة RID_DOUBLE:
    حالة RID_VOID:
    حالة RID_DFLOAT32:
    حالة RID_DFLOAT64:
    حالة RID_DFLOAT128:
    حالة RID_DFLOAT64X:
    CASE_RID_FLOATN_NX:
    حالة RID_BOOL:
    حالة RID_BITINT:
    حالة RID_ENUM:
    حالة RID_STRUCT:
    حالة RID_UNION:
    حالة RID_TYPEOF:
    حالة RID_TYPEOF_UNQUAL:
    حالة RID_CONST:
    حالة RID_ATOMIC:
    حالة RID_VOLATILE:
    حالة RID_RESTRICT:
    حالة RID_ATTRIBUTE:
    حالة RID_FRACT:
    حالة RID_ACCUM:
    حالة RID_SAT:
    حالة RID_AUTO_TYPE:
    حالة RID_ALIGNAS:
      أرجع true;
    افتراضي:
      إذا (keyword >= RID_FIRST_INT_N
	  && keyword < RID_FIRST_INT_N + لمب_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_FIRST_INT_N])
	أرجع true;
      أرجع خطأ;
    }
}

/* Return true if TOKEN can start a type name,
   false otherwise.  */
منطقي
c_token_starts_typename (c_token *token)
{
  بدل (token->type)
    {
    حالة CPP_NAME:
      بدل (token->id_kind)
	{
	حالة C_ID_ID:
	  أرجع خطأ;
	حالة C_ID_ADDRSPACE:
	  أرجع true;
	حالة C_ID_TYPENAME:
	  أرجع true;
	حالة C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  أرجع true;
	افتراضي:
	  gcc_unreachable ();
	}
    حالة CPP_KEYWORD:
      أرجع c_keyword_starts_typename (token->keyword);
    حالة CPP_LESS:
      إذا (c_dialect_objc ())
	أرجع true;
      أرجع خطأ;
    افتراضي:
      أرجع خطأ;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

ساكن مضمن منطقي
c_parser_next_tokens_start_typename (c_parser *parser, تعداد c_lookahead_kind la,
				     unsigned صحيح n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  إذا (c_token_starts_typename (token))
    أرجع true;

  /* Try a bit harder to detect an unknown typename.  */
  إذا (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_kind == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->درج))
    أرجع true;

  أرجع خطأ;
}

/* Return true if TOKEN, after an open parenthesis, can start a
   compound literal (either a storage class specifier allowed in that
   context, or a type name), false otherwise.  */
ساكن منطقي
c_token_starts_compound_literal (c_token *token)
{
  بدل (token->type)
    {
    حالة CPP_KEYWORD:
      بدل (token->keyword)
	{
	حالة RID_CONSTEXPR:
	حالة RID_REGISTER:
	حالة RID_STATIC:
	حالة RID_THREAD:
	  أرجع true;
	افتراضي:
	  اكسر;
	}
      /* Fall through.  */
    افتراضي:
      أرجع c_token_starts_typename (token);
    }
}

/* Return true if TOKEN is a type qualifier, false otherwise.  */
ساكن منطقي
c_token_is_qualifier (c_token *token)
{
  بدل (token->type)
    {
    حالة CPP_NAME:
      بدل (token->id_kind)
	{
	حالة C_ID_ADDRSPACE:
	  أرجع true;
	افتراضي:
	  أرجع خطأ;
	}
    حالة CPP_KEYWORD:
      بدل (token->keyword)
	{
	حالة RID_CONST:
	حالة RID_VOLATILE:
	حالة RID_RESTRICT:
	حالة RID_ATTRIBUTE:
	حالة RID_ATOMIC:
	  أرجع true;
	افتراضي:
	  أرجع خطأ;
	}
    حالة CPP_LESS:
      أرجع خطأ;
    افتراضي:
      gcc_unreachable ();
    }
}

/* Return true if the next token from PARSER is a type qualifier,
   false otherwise.  */
ساكن مضمن منطقي
c_parser_next_token_is_qualifier (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  أرجع c_token_is_qualifier (token);
}

/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes), false otherwise.  */
ساكن منطقي
c_token_starts_declspecs (c_token *token)
{
  بدل (token->type)
    {
    حالة CPP_NAME:
      بدل (token->id_kind)
	{
	حالة C_ID_ID:
	  أرجع خطأ;
	حالة C_ID_ADDRSPACE:
	  أرجع true;
	حالة C_ID_TYPENAME:
	  أرجع true;
	حالة C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  أرجع true;
	افتراضي:
	  gcc_unreachable ();
	}
    حالة CPP_KEYWORD:
      بدل (token->keyword)
	{
	حالة RID_STATIC:
	حالة RID_EXTERN:
	حالة RID_REGISTER:
	حالة RID_TYPEDEF:
	حالة RID_INLINE:
	حالة RID_NORETURN:
	حالة RID_AUTO:
	حالة RID_THREAD:
	حالة RID_UNSIGNED:
	حالة RID_LONG:
	حالة RID_SHORT:
	حالة RID_SIGNED:
	حالة RID_COMPLEX:
	حالة RID_INT:
	حالة RID_CHAR:
	حالة RID_FLOAT:
	حالة RID_DOUBLE:
	حالة RID_VOID:
	حالة RID_DFLOAT32:
	حالة RID_DFLOAT64:
	حالة RID_DFLOAT128:
	حالة RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	حالة RID_BOOL:
	حالة RID_BITINT:
	حالة RID_ENUM:
	حالة RID_STRUCT:
	حالة RID_UNION:
	حالة RID_TYPEOF:
	حالة RID_TYPEOF_UNQUAL:
	حالة RID_CONST:
	حالة RID_VOLATILE:
	حالة RID_RESTRICT:
	حالة RID_ATTRIBUTE:
	حالة RID_FRACT:
	حالة RID_ACCUM:
	حالة RID_SAT:
	حالة RID_ALIGNAS:
	حالة RID_ATOMIC:
	حالة RID_AUTO_TYPE:
	حالة RID_CONSTEXPR:
	  أرجع true;
	افتراضي:
	  إذا (token->keyword >= RID_FIRST_INT_N
	      && token->keyword < RID_FIRST_INT_N + لمب_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_FIRST_INT_N])
	    أرجع true;
	  أرجع خطأ;
	}
    حالة CPP_LESS:
      إذا (c_dialect_objc ())
	أرجع true;
      أرجع خطأ;
    افتراضي:
      أرجع خطأ;
    }
}


/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes) or a static assertion, false
   otherwise.  */
ساكن منطقي
c_token_starts_declaration (c_token *token)
{
  إذا (c_token_starts_declspecs (token)
      || token->keyword == RID_STATIC_ASSERT)
    أرجع true;
  وإلا
    أرجع خطأ;
}

/* Return true if the next token from PARSER can start declaration
   specifiers (not including standard attributes), false
   otherwise.  */
منطقي
c_parser_next_token_starts_declspecs (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);

  /* In Objective-C, a classname normally starts a declspecs unless it
     is immediately followed by a dot.  In that case, it is the
     Objective-C 2.0 "dot-syntax" for class objects, ie, calls the
     setter/getter on the class.  c_token_starts_declspecs() can't
     differentiate between the two cases because it only checks the
     current token, so we have a special check here.  */
  إذا (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    أرجع خطأ;

  أرجع c_token_starts_declspecs (token);
}

ساكن منطقي c_parser_check_balanced_raw_token_sequence (c_parser *,
							unsigned صحيح *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
منطقي
c_parser_next_tokens_start_declaration (c_parser *parser, unsigned صحيح n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  إذا (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_DOT)
    أرجع خطأ;

  /* Labels do not start declarations.  */
  إذا (token->type == CPP_NAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_COLON)
    أرجع خطأ;

  /* A static assertion is only a declaration if followed by a semicolon;
     otherwise, it may be an expression in C2Y.  */
  إذا (token->keyword == RID_STATIC_ASSERT
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_PAREN)
    {
      n += 2;
      إذا (!c_parser_check_balanced_raw_token_sequence (parser, &n)
	  || c_parser_peek_nth_token_raw (parser, n)->type != CPP_CLOSE_PAREN)
	/* Invalid static assertion syntax; treat as a declaration and report a
	   syntax error there.  */
	أرجع true;
      أرجع c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  إذا (c_token_starts_declaration (token))
    أرجع true;

  إذا (c_parser_next_tokens_start_typename (parser, cla_nonabstract_decl, n))
    أرجع true;

  أرجع خطأ;
}

/* Consume the next token from PARSER.  */

فراغ
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
  إذا (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  وإلا إذا (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      إذا (parser->tokens_avail >= 3)
        {
          parser->tokens[1] = parser->tokens[2];
          إذا (parser->tokens_avail >= 4)
            parser->tokens[2] = parser->tokens[3];
        }
    }
  parser->tokens_avail--;
  parser->seen_string_literal = خطأ;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

ساكن فراغ
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->in_pragma);
  gcc_assert (parser->tokens_avail >= 1);
  gcc_assert (parser->tokens[0].type == CPP_PRAGMA);
  إذا (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  وإلا إذا (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      إذا (parser->tokens_avail >= 3)
	parser->tokens[1] = parser->tokens[2];
    }
  parser->tokens_avail--;
  parser->in_pragma = true;
}

/* Update the global input_location from TOKEN.  */
ساكن مضمن فراغ
c_parser_set_source_position_from_token (c_token *token)
{
  إذا (token->type != CPP_EOF)
    {
      شغرو_location = token->location;
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

ساكن منطقي
c_parser_peek_conflict_marker (c_parser *parser, تعداد cpp_ttype tok1_kind,
			       location_t *out_loc)
{
  c_token *token2 = c_parser_peek_2nd_token (parser);
  إذا (token2->type != tok1_kind)
    أرجع خطأ;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  إذا (token3->type != tok1_kind)
    أرجع خطأ;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  إذا (token4->type != conflict_marker_get_final_tok_kind (tok1_kind))
    أرجع خطأ;

  /* It must be at the start of the line.  */
  location_t start_loc = c_parser_peek_token (parser)->location;
  إذا (LOCATION_COLUMN (start_loc) != 1)
    أرجع خطأ;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t finish_loc = get_finish (token4->location);
  *out_loc = make_location (start_loc, start_loc, finish_loc);

  أرجع true;
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

ساكن منطقي
c_parser_error_richloc (c_parser *parser, ثابت حرف *gmsgid,
			rich_location *richloc)
{
  c_token *token = c_parser_peek_token (parser);
  إذا (parser->error)
    أرجع خطأ;
  parser->error = true;
  إذا (!gmsgid)
    أرجع خطأ;

  /* If this is actually a conflict marker, report it as such.  */
  إذا (token->type == CPP_LSHIFT
      || token->type == CPP_RSHIFT
      || token->type == CPP_EQ_EQ)
    {
      location_t loc;
      إذا (c_parser_peek_conflict_marker (parser, token->type, &loc))
	{
	  error_at (loc, "version control conflict marker in file");
	  أرجع true;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_group d;
  name_hint h;
  إذا (parser->seen_string_literal && token->type == CPP_NAME)
    {
      بشيا name = token->درج;
      ثابت حرف *token_name = IDENTIFIER_POINTER (name);
      ثابت حرف *header_hint
	= get_c_stdlib_header_for_string_macro_name (token_name);
      إذا (header_hint != عدم)
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
		 token->درج, /*flags=*/0, richloc);
  أرجع true;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

منطقي
c_parser_error (c_parser *parser, ثابت حرف *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_set_source_position_from_token (token);
  rich_location richloc (لي_table, شغرو_location);
  أرجع c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

template <typename traits_t>
صنف token_pair
{
 عام:
  /* token_pair's ctor.  */
  token_pair () : m_open_loc (UNKNOWN_LOCATION) {}

  /* If the next token is the opening symbol for this pair, consume it and
     return true.
     Otherwise, issue an error and return false.
     In either case, record the location of the opening token.  */

  منطقي require_open (c_parser *parser)
  {
    c_token *token = c_parser_peek_token (parser);
    إذا (token)
      m_open_loc = token->location;

    أرجع c_parser_require (parser, traits_t::open_token_type,
			     traits_t::open_gmsgid);
  }

  /* Consume the next token from PARSER, recording its location as
     that of the opening token within the pair.  */

  فراغ consume_open (c_parser *parser)
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

  منطقي require_close (c_parser *parser) ثابت
  {
    أرجع c_parser_require (parser, traits_t::close_token_type,
			     traits_t::close_gmsgid, m_open_loc);
  }

  /* Like token_pair::require_close, except that tokens will be skipped
     until the desired token is found.  An error message is still produced
     if the next token is not as expected.  */

  فراغ skip_until_found_close (c_parser *parser) ثابت
  {
    c_parser_skip_until_found (parser, traits_t::close_token_type,
			       traits_t::close_gmsgid, m_open_loc);
  }

 خاص:
  location_t m_open_loc;
};

/* Traits for token_pair<T> for tracking matching pairs of parentheses.  */

بنية matching_paren_traits
{
  ساكن ثابت تعداد cpp_ttype open_token_type = CPP_OPEN_PAREN;
  ساكن ثابت حرف * ثابت open_gmsgid;
  ساكن ثابت تعداد cpp_ttype close_token_type = CPP_CLOSE_PAREN;
  ساكن ثابت حرف * ثابت close_gmsgid;
};

ثابت حرف * ثابت matching_paren_traits::open_gmsgid = "expected %<(%>";
ثابت حرف * ثابت matching_paren_traits::close_gmsgid = "expected %<)%>";

/* "matching_parens" is a token_pair<T> class for tracking matching
   pairs of parentheses.  */

تعريفنوع token_pair<matching_paren_traits> matching_parens;

/* Traits for token_pair<T> for tracking matching pairs of braces.  */

بنية matching_brace_traits
{
  ساكن ثابت تعداد cpp_ttype open_token_type = CPP_OPEN_BRACE;
  ساكن ثابت حرف * ثابت open_gmsgid;
  ساكن ثابت تعداد cpp_ttype close_token_type = CPP_CLOSE_BRACE;
  ساكن ثابت حرف * ثابت close_gmsgid;
};

ثابت حرف * ثابت matching_brace_traits::open_gmsgid = "expected %<{%>";
ثابت حرف * ثابت matching_brace_traits::close_gmsgid = "expected %<}%>";

/* "matching_braces" is a token_pair<T> class for tracking matching
   pairs of braces.  */

تعريفنوع token_pair<matching_brace_traits> matching_braces;

/* Get a description of the matching symbol to TYPE e.g. "(" for
   CPP_CLOSE_PAREN.  */

ساكن ثابت حرف *
get_matching_علام (تعداد cpp_ttype type)
{
  بدل (type)
    {
    افتراضي:
      gcc_unreachable ();
    حالة CPP_CLOSE_PAREN:
      أرجع "(";
    حالة CPP_CLOSE_BRACE:
      أرجع "{";
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

منطقي
c_parser_require (c_parser *parser,
		  تعداد cpp_ttype type,
		  ثابت حرف *msgid,
		  location_t matching_location,
		  منطقي type_is_unique)
{
  إذا (c_parser_next_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      أرجع true;
    }
  وإلا
    {
      location_t next_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (next_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      إذا (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->last_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      منطقي added_matching_location = خطأ;
      إذا (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.add_location_if_nearby (*global_dc, matching_location);

      إذا (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	إذا (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_علام (type));

      أرجع خطأ;
    }
}

/* If the next token is the indicated keyword, consume it.  Otherwise,
   issue the error MSGID.  Returns true if found, false otherwise.  */

ساكن منطقي
c_parser_require_keyword (c_parser *parser,
			  تعداد rid keyword,
			  ثابت حرف *msgid)
{
  إذا (c_parser_next_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      أرجع true;
    }
  وإلا
    {
      c_parser_error (parser, msgid);
      أرجع خطأ;
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

فراغ
c_parser_skip_until_found (c_parser *parser,
			   تعداد cpp_ttype type,
			   ثابت حرف *msgid,
			   location_t matching_location)
{
  unsigned nesting_depth = 0;

  إذا (c_parser_require (parser, type, msgid, matching_location))
    {
      إذا (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->in_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_EOF)
	    {
	      parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	      parser->tokens_avail
		= parser->in_omp_attribute_pragma->save_tokens_avail;
	      parser->in_omp_attribute_pragma = عدم;
	    }
	}
      أرجع;
    }

  /* Skip tokens until the desired token is found.  */
  طالما (true)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      إذا (token->type == type && !nesting_depth)
	{
	  c_parser_consume_token (parser);
	  إذا (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->in_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      إذا (token->type == CPP_EOF)
		{
		  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
		  parser->tokens_avail
		    = parser->in_omp_attribute_pragma->save_tokens_avail;
		  parser->in_omp_attribute_pragma = عدم;
		}
	    }
	  اكسر;
	}

      /* If we've run out of tokens, stop.  */
      إذا (token->type == CPP_EOF)
	أرجع;
      إذا (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	أرجع;
      إذا (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      وإلا إذا (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  إذا (nesting_depth-- == 0)
	    اكسر;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = خطأ;
}

/* Skip tokens until the end of a parameter is found, but do not
   consume the comma, semicolon or closing delimiter.  */

ساكن فراغ
c_parser_skip_to_end_of_parameter (c_parser *parser)
{
  unsigned nesting_depth = 0;

  طالما (true)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_depth)
	اكسر;
      /* If we've run out of tokens, stop.  */
      إذا (token->type == CPP_EOF)
	أرجع;
      إذا (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	أرجع;
      إذا (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      وإلا إذا (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  إذا (nesting_depth-- == 0)
	    اكسر;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = خطأ;
}

/* Skip tokens until a non-nested closing curly brace is the next
   token, or there are no more tokens. Return true in the first case,
   false otherwise.  */

ساكن منطقي
c_parser_skip_to_closing_brace (c_parser *parser)
{
  unsigned nesting_depth = 0;

  طالما (true)
    {
      c_token *token = c_parser_peek_token (parser);

      بدل (token->type)
	{
	حالة CPP_PRAGMA_EOL:
	  إذا (!parser->in_pragma)
	    اكسر;
	  /* FALLTHRU */
	حالة CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  أرجع خطأ;

	حالة CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  إذا (nesting_depth-- == 0)
	    أرجع true;
	  اكسر;

	حالة CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  اكسر;

	افتراضي:
	  اكسر;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Expect to be at the end of the pragma directive and consume an
   end of line marker.  */

ساكن فراغ
c_parser_skip_to_pragma_eol (c_parser *parser, منطقي error_if_not_eol = true)
{
  gcc_assert (parser->in_pragma);
  parser->in_pragma = خطأ;

  إذا (error_if_not_eol && c_parser_peek_token (parser)->type != CPP_PRAGMA_EOL)
    c_parser_error (parser, "expected end of line");

  cpp_ttype token_type;
  افعل
    {
      c_token *token = c_parser_peek_token (parser);
      token_type = token->type;
      إذا (token_type == CPP_EOF)
	اكسر;
      c_parser_consume_token (parser);
    }
  طالما (token_type != CPP_PRAGMA_EOL);

  إذا (parser->in_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_EOF)
	{
	  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	  parser->tokens_avail
	    = parser->in_omp_attribute_pragma->save_tokens_avail;
	  parser->in_omp_attribute_pragma = عدم;
	}
    }

  parser->error = خطأ;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
ساكن فراغ
c_parser_skip_to_pragma_omp_end_declare_variant (c_parser *parser)
{
  لكل (صحيح depth = 0; depth >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      بدل (token->type)
	{
	حالة CPP_PRAGMA_EOL:
	  إذا (!parser->in_pragma)
	    اكسر;
	  /* FALLTHRU */
	حالة CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  أرجع;

	حالة CPP_PRAGMA:
	  إذا ((token->pragma_kind == PRAGMA_OMP_BEGIN
	       || token->pragma_kind == PRAGMA_OMP_END)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      بشيا id1 = c_parser_peek_nth_token (parser, 2)->درج;
	      بشيا id2 = c_parser_peek_nth_token (parser, 3)->درج;
	      إذا (strcmp (IDENTIFIER_POINTER (id1), "declare") == 0
		  && strcmp (IDENTIFIER_POINTER (id2), "variant") == 0)
		{
		  إذا (token->pragma_kind == PRAGMA_OMP_BEGIN)
		    depth++;
		  وإلا
		    depth--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, خطأ);
	  استمر;

	افتراضي:
	  اكسر;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Skip tokens until we have consumed an entire block, or until we
   have consumed a non-nested ';'.  */

ساكن فراغ
c_parser_skip_to_end_of_block_or_statement (c_parser *parser,
					    منطقي metadirective_p = خطأ)
{
  unsigned nesting_depth = 0;
  صحيح bracket_depth = 0;
  منطقي save_error = parser->error;

  طالما (true)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      بدل (token->type)
	{
	حالة CPP_EOF:
	  أرجع;

	حالة CPP_PRAGMA_EOL:
	  إذا (parser->in_pragma)
	    أرجع;
	  اكسر;

	حالة CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  إذا (!nesting_depth && (!metadirective_p || bracket_depth <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      اذهب finished;
	    }
	  اكسر;

	حالة CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  إذا ((nesting_depth == 0 || --nesting_depth == 0)
	      && (!metadirective_p || bracket_depth <= 0))
	    {
	      c_parser_consume_token (parser);
	      اذهب finished;
	    }
	  اكسر;

	حالة CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  اكسر;

	حالة CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  إذا (metadirective_p && nesting_depth == 0)
	    ++bracket_depth;
	  اكسر;

	حالة CPP_CLOSE_PAREN:
	  إذا (metadirective_p && nesting_depth == 0)
	    --bracket_depth;
	  اكسر;

	حالة CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, خطأ);
	  parser->error = save_error;
	  استمر;

	افتراضي:
	  اكسر;
	}

      c_parser_consume_token (parser);
    }

 finished:
  parser->error = خطأ;
}

/* CPP's options (initialized by c-opts.cc).  */
خارجي cpp_options *cpp_opts;

/* Save the warning flags which are controlled by __extension__.  */

ساكن مضمن صحيح
disable_extension_diagnostics (فراغ)
{
  صحيح ret = (pedantic
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
  أرجع ret;
}

/* Restore the warning flags which are controlled by __extension__.
   FLAGS is the return value from disable_extension_diagnostics.  */

ساكن مضمن فراغ
restore_extension_diagnostics (صحيح flags)
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
بنية oacc_routine_data {
  منطقي error_seen; /* Set if error has been reported.  */
  منطقي fndecl_seen; /* Set if one fn decl/definition has been seen already.  */
  بشيا clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
ساكن بشيا objc_foreach_break_label, objc_foreach_continue_label;

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
بنية omp_for_parse_data {
  تعداد بشيا_code code;
  بشيا declv, condv, incrv, initv;
  بشيا pre_body;
  بشيا bindings;
  صحيح كدي;	/* Expected nesting depth.  */
  صحيح depth;	/* Current nesting depth.  */
  location_t for_loc;
  منطقي ordered : 1;
  منطقي inscan : 1;
  منطقي want_nested_loop : 1;
  منطقي in_intervening_code : 1;
  منطقي saw_intervening_code: 1;
  منطقي perfect_nesting_fail : 1;
  منطقي fail : 1;
};

بنية attr_state
{
  /* True if we parsed a musttail attribute for return.  */
  منطقي musttail_p;

  فراغ reset () { musttail_p = خطأ; }
};

ساكن منطقي c_parser_nth_token_starts_std_attributes (c_parser *,
						      unsigned صحيح);
ساكن بشيا c_parser_std_attribute_specifier_sequence (c_parser *);
ساكن فراغ c_parser_external_declaration (c_parser *);
ساكن فراغ c_parser_asm_definition (c_parser *);
ساكن بشيا c_parser_declaration_or_fndef (c_parser *, منطقي, منطقي, منطقي,
					   منطقي, منطقي, منطقي, بشيا * = عدم,
					   vec<c_token> * = عدم,
					   منطقي have_attrs = خطأ,
					   بشيا attrs = عدم,
					   بنية oacc_routine_data * = عدم,
					   منطقي * = عدم);
ساكن منطقي c_parser_handle_statement_omp_attributes (c_parser *, بشيا &,
						      منطقي *);
ساكن فراغ c_parser_static_assert_declaration_no_semi (c_parser *);
ساكن فراغ c_parser_static_assert_declaration (c_parser *);
ساكن بنية c_typespec c_parser_enum_specifier (c_parser *);
ساكن بنية c_typespec c_parser_struct_or_union_specifier (c_parser *);
ساكن بشيا c_parser_struct_declaration (c_parser *, بشيا *);
ساكن بنية c_typespec c_parser_typeof_specifier (c_parser *);
ساكن بشيا c_parser_alignas_specifier (c_parser *);
ساكن بنية c_declarator *c_parser_direct_declarator (c_parser *, منطقي,
							c_dtr_syn, منطقي *);
ساكن بنية c_declarator *c_parser_direct_declarator_inner (c_parser *,
							      منطقي,
							      بنية c_declarator *);
ساكن بنية c_arg_info *c_parser_parms_declarator (c_parser *, منطقي, بشيا,
						     منطقي);
ساكن بنية c_arg_info *c_parser_parms_list_declarator (c_parser *, بشيا,
							  بشيا, منطقي);
ساكن بنية c_parm *c_parser_parameter_declaration (c_parser *, بشيا, منطقي);
ساكن بشيا c_parser_asm_string_literal (c_parser *);
ساكن بشيا c_parser_simple_asm_فرچ (c_parser *);
ساكن بشيا c_parser_gnu_attributes (c_parser *);
ساكن بنية c_فرچ c_parser_initializer (c_parser *, بشيا);
ساكن بنية c_فرچ c_parser_braced_init (c_parser *, بشيا, منطقي,
					   بنية obstack *, منطقي);
ساكن فراغ c_parser_initelt (c_parser *, بنية obstack *);
ساكن فراغ c_parser_initval (c_parser *, بنية c_فرچ *,
			      بنية obstack *);
ساكن بشيا c_parser_compound_statement (c_parser *, location_t * = عدم);
ساكن location_t c_parser_compound_statement_nostart (c_parser *);
ساكن فراغ c_parser_label (c_parser *, بشيا);
ساكن فراغ c_parser_statement (c_parser *, منطقي *, location_t * = عدم);
ساكن فراغ c_parser_statement_after_labels (c_parser *, منطقي *, بشيا,
					     vec<بشيا> * = عدم,
					     attr_state = {});
ساكن بشيا c_parser_c99_block_statement (c_parser *, منطقي *,
					  location_t * = عدم);
ساكن فراغ c_parser_if_statement (c_parser *, منطقي *, vec<بشيا> *);
ساكن فراغ c_parser_switch_statement (c_parser *, منطقي *, بشيا);
ساكن فراغ c_parser_while_statement (c_parser *, منطقي, unsigned short, منطقي,
				      منطقي *, بشيا);
ساكن فراغ c_parser_do_statement (c_parser *, منطقي, unsigned short, منطقي,
				   بشيا);
ساكن فراغ c_parser_for_statement (c_parser *, منطقي, unsigned short, منطقي,
				    منطقي *, بشيا);
ساكن بشيا c_parser_asm_statement (c_parser *);
ساكن بشيا c_parser_asm_operands (c_parser *);
ساكن بشيا c_parser_asm_goto_operands (c_parser *);
ساكن بشيا c_parser_asm_clobbers (c_parser *);
ساكن بنية c_فرچ c_parser_فرچ_no_commas (c_parser *, بنية c_فرچ *,
					      بشيا = NULL_بشيا);
ساكن بنية c_فرچ c_parser_conditional_expression (c_parser *,
						      بنية c_فرچ *, بشيا);
ساكن بنية c_فرچ c_parser_نبيو_expression (c_parser *, بنية c_فرچ *,
						 بشيا);
ساكن بنية c_فرچ c_parser_cast_expression (c_parser *, بنية c_فرچ *);
ساكن بنية c_فرچ c_parser_unary_expression (c_parser *);
ساكن بنية c_فرچ c_parser_sizeof_or_countof_expression (c_parser *,
							    تعداد rid);
ساكن بنية c_فرچ c_parser_alignof_expression (c_parser *);
ساكن بنية c_فرچ c_parser_maxof_or_minof_expression (c_parser *, تعداد rid);
ساكن بنية c_فرچ c_parser_postfix_expression (c_parser *);
ساكن بنية c_فرچ c_parser_postfix_expression_after_paren_type (c_parser *,
								   بنية c_declspecs *,
								   بنية c_type_name *,
								   location_t);
ساكن بنية c_فرچ c_parser_postfix_expression_after_primary (c_parser *,
								location_t loc,
								بنية c_فرچ);
ساكن بشيا c_parser_transaction (c_parser *, تعداد rid);
ساكن بنية c_فرچ c_parser_transaction_expression (c_parser *, تعداد rid);
ساكن بشيا c_parser_transaction_cancel (c_parser *);
ساكن بنية c_فرچ c_parser_expression (c_parser *);
ساكن بنية c_فرچ c_parser_expression_conv (c_parser *);
ساكن vec<بشيا, va_gc> *c_parser_فرچ_list (c_parser *, منطقي, منطقي,
					     vec<بشيا, va_gc> **, location_t *,
					     بشيا *, vec<location_t> *,
					     unsigned صحيح * = عدم);
ساكن بنية c_فرچ c_parser_has_attribute_expression (c_parser *);

ساكن فراغ c_parser_oacc_declare (c_parser *);
ساكن فراغ c_parser_oacc_enter_exit_data (c_parser *, منطقي);
ساكن فراغ c_parser_oacc_update (c_parser *);
ساكن فراغ c_parser_omp_construct (c_parser *, منطقي *);
ساكن فراغ c_parser_omp_groupprivate (c_parser *);
ساكن فراغ c_parser_omp_threadprivate (c_parser *);
ساكن فراغ c_parser_omp_barrier (c_parser *);
ساكن فراغ c_parser_omp_depobj (c_parser *);
ساكن فراغ c_parser_omp_flush (c_parser *);
ساكن منطقي c_parser_omp_next_tokens_can_be_canon_loop (c_parser *,
							تعداد بشيا_code, منطقي);
ساكن بشيا c_parser_omp_loop_nest (c_parser *, منطقي *);
ساكن بشيا c_parser_omp_for_loop (location_t, c_parser *, تعداد بشيا_code,
				   بشيا, بشيا *, منطقي *);
ساكن فراغ c_parser_omp_taskwait (c_parser *);
ساكن فراغ c_parser_omp_taskyield (c_parser *);
ساكن فراغ c_parser_omp_cancel (c_parser *);
ساكن فراغ c_parser_omp_nothing (c_parser *);
ساكن فراغ c_parser_omp_metadirective (c_parser *, منطقي *);

تعداد pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
ساكن منطقي c_parser_pragma (c_parser *, تعداد pragma_context, منطقي *, بشيا);
ساكن منطقي c_parser_omp_cancellation_point (c_parser *, تعداد pragma_context);
ساكن منطقي c_parser_omp_target (c_parser *, تعداد pragma_context, منطقي *);
ساكن فراغ c_parser_omp_begin (c_parser *);
ساكن فراغ c_parser_omp_end (c_parser *);
ساكن منطقي c_parser_omp_declare (c_parser *, تعداد pragma_context);
ساكن فراغ c_parser_omp_requires (c_parser *);
ساكن منطقي c_parser_omp_error (c_parser *, تعداد pragma_context);
ساكن فراغ c_parser_omp_assumption_clauses (c_parser *, منطقي);
ساكن فراغ c_parser_omp_allocate (c_parser *);
ساكن فراغ c_parser_omp_assumes (c_parser *);
ساكن منطقي c_parser_omp_ordered (c_parser *, تعداد pragma_context, منطقي *);
ساكن بشيا c_parser_omp_dispatch (location_t, c_parser *);
ساكن فراغ c_parser_omp_interop (c_parser *);
ساكن فراغ c_parser_oacc_routine (c_parser *, تعداد pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
ساكن فراغ c_parser_objc_class_definition (c_parser *, بشيا);
ساكن فراغ c_parser_objc_class_instance_variables (c_parser *);
ساكن فراغ c_parser_objc_class_declaration (c_parser *);
ساكن فراغ c_parser_objc_alias_declaration (c_parser *);
ساكن فراغ c_parser_objc_protocol_definition (c_parser *, بشيا);
ساكن منطقي c_parser_objc_method_type (c_parser *);
ساكن فراغ c_parser_objc_method_definition (c_parser *);
ساكن فراغ c_parser_objc_methodprotolist (c_parser *);
ساكن فراغ c_parser_objc_methodproto (c_parser *);
ساكن بشيا c_parser_objc_method_decl (c_parser *, منطقي, بشيا *, بشيا *);
ساكن بشيا c_parser_objc_type_name (c_parser *);
ساكن بشيا c_parser_objc_protocol_refs (c_parser *);
ساكن فراغ c_parser_objc_try_catch_finally_statement (c_parser *);
ساكن فراغ c_parser_objc_synchronized_statement (c_parser *);
ساكن بشيا c_parser_objc_selector (c_parser *);
ساكن بشيا c_parser_objc_selector_arg (c_parser *);
ساكن بشيا c_parser_objc_receiver (c_parser *);
ساكن بشيا c_parser_objc_message_حجوجي (c_parser *);
ساكن بشيا c_parser_objc_keywordexpr (c_parser *);
ساكن فراغ c_parser_objc_at_property_declaration (c_parser *);
ساكن فراغ c_parser_objc_at_synthesize_declaration (c_parser *);
ساكن فراغ c_parser_objc_at_dynamic_declaration (c_parser *);
ساكن منطقي c_parser_objc_diagnose_bad_element_prefix
  (c_parser *, بنية c_declspecs *);
ساكن location_t c_parser_parse_rtl_body (c_parser *, حرف *);
ساكن بشيا c_parser_handle_musttail (c_parser *, بشيا, attr_state &);

#إذا ENABLE_ANALYZER

نطاق ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

صنف c_translation_unit : عام translation_unit
{
عام:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  بشيا lookup_constant_by_id (بشيا id) ثابت final override
  {
    /* Consider decls.  */
    إذا (بشيا decl = lookup_name (id))
      إذا (بشيا_CODE (decl) == CONST_DECL)
	إذا (بشيا درج = DECL_INITIAL (decl))
	  إذا (بشيا_CODE (درج) == INTEGER_CST)
	    أرجع درج;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    إذا (cpp_macro_p (hashnode))
      إذا (بشيا درج = consider_macro (hashnode->درج.macro))
	أرجع درج;

    أرجع NULL_بشيا;
  }

  بشيا
  lookup_type_by_id (بشيا id) ثابت final override
  {
    إذا (بشيا type_decl = lookup_name (id))
	إذا (بشيا_CODE (type_decl) == TYPE_DECL)
	  {
	    بشيا record_type = بشيا_TYPE (type_decl);
	    إذا (بشيا_CODE (record_type) == RECORD_TYPE)
	      أرجع record_type;
	  }

    أرجع NULL_بشيا;
  }

  بشيا
  lookup_global_var_by_id (بشيا id) ثابت final override
  {
    إذا (بشيا var_decl = lookup_name (id))
      إذا (بشيا_CODE (var_decl) == VAR_DECL)
				أرجع var_decl;

    أرجع NULL_بشيا;
  }

خاص:
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
  بشيا consider_macro (cpp_macro *macro, صحيح depth = 0) ثابت
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (depth >= 0);

    إذا (macro->paramc > 0)
      أرجع NULL_بشيا;
    إذا (macro->kind != cmk_macro)
      أرجع NULL_بشيا;
    إذا (macro->كدي != 1)
      أرجع NULL_بشيا;
    ثابت cpp_token &tok = macro->exp.tokens[0];
    إذا (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	إذا (depth >= param_analyzer_max_macro_alias_depth)
	  أرجع NULL_بشيا;

	cpp_hashnode *alias = tok.val.كلي.كلي;
	إذا (cpp_macro_p (alias))
	  أرجع consider_macro (alias->درج.macro, depth + 1);

	/* Not a simple alias.  */
	أرجع NULL_بشيا;
      }
    وإلا إذا (tok.type != CPP_لمب)
      أرجع NULL_بشيا;

    cpp_reader *old_parse_in = parse_in;
    parse_in = cpp_create_reader (CLK_GNUC89, عدم, لي_table);

    pretty_printer pp;
    pp_string (&pp, (ثابت حرف *) tok.val.str.text);
    pp_newline (&pp);
    cpp_تور_buffer (parse_in,
		     (ثابت unsigned حرف *) pp_formatted_text (&pp),
		     strlen (pp_formatted_text (&pp)),
		     0);

    بشيا درج;
    location_t loc;
    unsigned حرف cpp_flags;
    c_lex_with_flags (&درج, &loc, &cpp_flags, 0);

    cpp_destroy (parse_in);
    parse_in = old_parse_in;

    إذا (درج && بشيا_CODE (درج) == INTEGER_CST)
      أرجع درج;

    أرجع NULL_بشيا;
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

ساكن فراغ
c_parser_translation_unit (c_parser *parser)
{
  إذا (c_parser_next_token_is (parser, CPP_EOF))
    {
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C forbids an empty translation unit");
    }
  وإلا
    {
      فراغ *obstack_position = obstack_alloc (&parser_obstack, 0);
      mark_valid_location_for_stdc_pragma (خطأ);
      افعل
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      طالما (c_parser_next_token_is_not (parser, CPP_EOF));
    }

  unsigned صحيح i;
  بشيا decl;
  FOR_EACH_VEC_ELT (incomplete_record_decls, i, decl)
    إذا (DECL_SIZE (decl) == NULL_بشيا && بشيا_TYPE (decl) != error_mark_كلي)
      error ("storage size of %q+D isn%'t known", decl);

  إذا (vec_safe_length (current_omp_declare_target_attribute))
    {
      c_omp_declare_target_attr
	a = current_omp_declare_target_attribute->چرو ();
      إذا (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_safe_truncate (current_omp_declare_target_attribute, 0);
    }
  إذا (vec_safe_length (current_omp_begin_assumes))
    {
      إذا (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_safe_truncate (current_omp_begin_assumes, 0);
    }
  إذا (vec_safe_length (current_omp_declare_variant_attribute))
    {
      إذا (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_safe_truncate (current_omp_declare_variant_attribute, 0);
    }
  إذا (vec_safe_length (omp_begin_declare_variant_map))
    {
      unsigned صحيح i;
      omp_begin_declare_variant_map_entry *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_finish_variant_function (e->variant, e->id, e->ctx);
      vec_safe_truncate (omp_begin_declare_variant_map, 0);
    }

#إذا ENABLE_ANALYZER
  إذا (flag_analyzer)
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

ساكن فراغ
c_parser_external_declaration (c_parser *parser)
{
  صحيح ext;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_KEYWORD:
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_EXTENSION:
	  ext = disable_extension_diagnostics ();
	  c_parser_consume_token (parser);
	  c_parser_external_declaration (parser);
	  restore_extension_diagnostics (ext);
	  اكسر;
	حالة RID_ASM:
	  c_parser_asm_definition (parser);
	  اكسر;
	حالة RID_AT_INTERFACE:
	حالة RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_definition (parser, NULL_بشيا);
	  اكسر;
	حالة RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  اكسر;
	حالة RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  اكسر;
	حالة RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_protocol_definition (parser, NULL_بشيا);
	  اكسر;
	حالة RID_AT_PROPERTY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_property_declaration (parser);
	  اكسر;
	حالة RID_AT_SYNTHESIZE:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_synthesize_declaration (parser);
	  اكسر;
	حالة RID_AT_DYNAMIC:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_dynamic_declaration (parser);
	  اكسر;
	حالة RID_AT_END:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_finish_implementation ();
	  اكسر;
	افتراضي:
	  اذهب decl_or_fndef;
	}
      اكسر;
    حالة CPP_SEMICOLON:
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_PRAGMA:
      mark_valid_location_for_stdc_pragma (true);
      c_parser_pragma (parser, pragma_external, عدم, NULL_بشيا);
      mark_valid_location_for_stdc_pragma (خطأ);
      اكسر;
    حالة CPP_PLUS:
    حالة CPP_MINUS:
      إذا (c_dialect_objc ())
	{
	  c_parser_objc_method_definition (parser);
	  اكسر;
	}
      /* Else fall through, and yield a syntax error trying to parse
	 as a declaration or function definition.  */
      /* FALLTHRU */
    افتراضي:
    decl_or_fndef:
      /* A declaration or a function definition (or, in Objective-C,
	 an @interface or @protocol with prefix attributes).  We can
	 only tell which after parsing the declaration specifiers, if
	 any, and the first declarator.  */
      c_parser_declaration_or_fndef (parser, true, true, true, خطأ, true,
				     خطأ);
      اكسر;
    }
}

ساكن فراغ c_parser_handle_directive_omp_attributes (بشيا &, vec<c_token> *&,
						      vec<c_token> *);
ساكن فراغ c_finish_omp_declare_simd (c_parser *, بشيا, بشيا, vec<c_token> *);
ساكن فراغ c_finish_oacc_routine (بنية oacc_routine_data *, بشيا, منطقي);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

ساكن فراغ
add_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  إذا (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    أرجع;

  بشيا stmt = build0 (DEBUG_BEGIN_STMT, void_type_كلي);
  SET_فرچ_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

ساكن بشيا
handle_assume_attribute (location_t here, بشيا attrs, منطقي nested)
{
  إذا (nested)
    لكل (بشيا attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", بشيا_CHAIN (attr)))
      {
	بشيا حجوجي = بشيا_درج (attr);
	صحيح nargs = list_length (حجوجي);
	إذا (nargs != 1)
	  {
	    error_at (here, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (here, "expected %i, found %i", 1, nargs);
	  }
	وإلا
	  {
	    بشيا arg = بشيا_درج (حجوجي);
	    arg = c_objc_common_truthvalue_conversion (here, arg);
	    arg = c_fully_fold (arg, خطأ, عدم);
	    إذا (arg != error_mark_كلي)
	      {
		بشيا fn = build_call_فرچ_internal_loc (here, IFN_ASSUME,
							void_type_كلي, 1,
							arg);
		add_stmt (fn);
	      }
	  }
      }
  وإلا
    pedwarn (here, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  أرجع remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

ساكن فراغ
c_parser_maybe_reclassify_token (c_parser *parser)
{
  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      إذا (token->id_kind == C_ID_ID || token->id_kind == C_ID_TYPENAME)
	{
	  بشيا decl = lookup_name (token->درج);

	  token->id_kind = C_ID_ID;
	  إذا (decl)
	    {
	      إذا (بشيا_CODE (decl) == TYPE_DECL)
		token->id_kind = C_ID_TYPENAME;
	    }
	  وإلا إذا (c_dialect_objc ())
	    {
	      بشيا objc_interface_decl = objc_is_class_name (token->درج);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      إذا (objc_interface_decl)
		{
		  token->درج = objc_interface_decl;
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

ساكن بشيا
c_parser_declaration_or_fndef (c_parser *parser, منطقي fndef_ok,
			       منطقي static_assert_ok, منطقي empty_ok,
			       منطقي nested, منطقي start_attr_ok,
			       منطقي simple_ok,
			       بشيا *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       منطقي have_attrs /* = false */,
			       بشيا attrs /* = NULL_TREE */,
			       بنية oacc_routine_data *oacc_routine_data
			       /* = NULL */,
			       منطقي *fallthru_attr_p /* = NULL */)
{
  بنية c_declspecs *specs;
  بشيا prefix_attrs;
  بشيا all_prefix_attrs;
  منطقي diagnosed_no_specs = خطأ;
  location_t here = c_parser_peek_token (parser)->location;
  بشيا result = NULL_بشيا;

  add_debug_begin_stmt (c_parser_peek_token (parser)->location);

  إذا (static_assert_ok
      && c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      أرجع result;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  إذا (have_attrs)
    {
      declspecs_add_attrs (here, specs, attrs);
      specs->non_std_attrs_seen_p = خطأ;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  إذا (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_kind == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->درج)))
    {
      بشيا name = c_parser_peek_token (parser)->درج;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (here);
      إذا (tag_exists_p (RECORD_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.add_fixit_سك_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      وإلا إذا (tag_exists_p (UNION_TYPE, name))
	{
	  richloc.add_fixit_سك_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      وإلا إذا (tag_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.add_fixit_سك_before ("enum ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<enum%> keyword to refer to the type",
		    name);
	}
      وإلا
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (name, FUZZY_LOOKUP_TYPENAME,
					      here);
	  إذا (ثابت حرف *suggestion = hint.suggestion ())
	    {
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			name, suggestion);
	    }
	  وإلا
	    error_at (here, "unknown type name %qE", name);
	}

      /* Parse declspecs normally to get a correct pointer type, but avoid
         a further "fails to be a type name" error.  Refuse nested functions
         since it is not how the user likely wants us to recover.  */
      c_parser_peek_token (parser)->type = CPP_KEYWORD;
      c_parser_peek_token (parser)->keyword = RID_VOID;
      c_parser_peek_token (parser)->درج = error_mark_كلي;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  إذا (c_parser_nth_token_starts_std_attributes (parser, 1))
    have_attrs = true;

  c_parser_declspecs (parser, specs, true, true, start_attr_ok,
		      true, true, start_attr_ok, true, cla_nonabstract_decl);
  إذا (parser->error)
    {
      c_parser_skip_to_end_of_block_or_statement (parser);
      أرجع result;
    }
  إذا (nested && !specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_end_of_block_or_statement (parser);
      أرجع result;
    }

  finish_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  إذا (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_كولي_anonymous_type (specs->type);

  منطقي gnu_auto_type_p = specs->typespec_word == cts_auto_type;
  منطقي std_auto_type_p = specs->c23_auto_p;
  منطقي any_auto_type_p = gnu_auto_type_p || std_auto_type_p;
  gcc_assert (!(gnu_auto_type_p && std_auto_type_p));
  ثابت حرف *auto_type_keyword = gnu_auto_type_p ? "__auto_type" : "auto";
  إذا (specs->constexpr_p)
    {
      /* An underspecified declaration may not declare tags or members
	 or structures or unions; it is undefined behavior to declare
	 the members of an enumeration.  Where the structure, union or
	 enumeration type is declared within an initializer, this is
	 diagnosed elsewhere.  Diagnose here the case of declaring
	 such a type in the type specifiers of a constexpr
	 declaration.  */
      بدل (specs->typespec_kind)
	{
	حالة ctsk_tagfirstref:
	حالة ctsk_tagfirstref_attrs:
	  error_at (here, "%qT declared in underspecified object declaration",
		    specs->type);
	  اكسر;

	حالة ctsk_tagdef:
	  error_at (here, "%qT defined in underspecified object declaration",
		    specs->type);
	  اكسر;

	افتراضي:
	  اكسر;
	}
    }

  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      منطقي handled_assume = خطأ;
      إذا (specs->attrs
	  && !nested
	  && specs->typespec_kind == ctsk_none
	  && c_parser_handle_statement_omp_attributes (parser, specs->attrs,
						       عدم))
	{
	  إذا (specs->attrs)
	    c_warn_unused_attributes (specs->attrs);
	  طالما (parser->in_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_next_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, عدم, NULL_بشيا);
	    }
	  c_parser_consume_token (parser);
	  أرجع result;
	}
      إذا (specs->typespec_kind == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = true;
	  specs->attrs
	    = handle_assume_attribute (here, specs->attrs, nested);
	}
      إذا (any_auto_type_p)
	error_at (here, "%qs in empty declaration", auto_type_keyword);
      وإلا إذا (specs->typespec_kind == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  إذا (fallthru_attr_p != عدم)
	    *fallthru_attr_p = true;
	  إذا (nested)
	    {
	      بشيا fn = build_call_فرچ_internal_loc (here, IFN_FALLTHROUGH,
						      void_type_كلي, 0);
	      add_stmt (fn);
	    }
	  وإلا
	    pedwarn (here, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      وإلا إذا (empty_ok
	       && !(have_attrs && specs->non_std_attrs_seen_p)
	       && !handled_assume)
	shadow_tag (specs);
      وإلا
	{
	  shadow_tag_warned (specs, 1);
	  إذا (!handled_assume)
	    pedwarn (here, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      إذا (specs->فرچ)
	add_stmt (fold_convert (void_type_كلي, specs->فرچ));
      c_parser_consume_token (parser);
      إذا (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, NULL_بشيا, خطأ);
      أرجع result;
    }
  وإلا إذا (specs->typespec_kind == ctsk_none
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
      إذا (astate.musttail_p)
	{
	  إذا (specs->attrs)
	    {
	      auto_urlify_attributes sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, عدم, NULL_بشيا, عدم,
					   astate);
	  أرجع result;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  إذا (empty_ok
      && specs->typespec_kind == ctsk_tagdef
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = خطأ;
      shadow_tag_warned (specs, 1);
      أرجع result;
    }
  وإلا إذا (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      بدل (c_parser_peek_token (parser)->type)
	{
	  حالة CPP_PLUS:
	  حالة CPP_MINUS:
	    إذا (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      أرجع result;
	    إذا (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_بشيا;
	      }
	    إذا (fndef_ok)
	      c_parser_objc_method_definition (parser);
	    وإلا
	      c_parser_objc_methodproto (parser);
	    أرجع result;
	    اكسر;
	  افتراضي:
	    اكسر;
	}
      /* This is where we parse 'attributes @interface ...',
	 'attributes @implementation ...', 'attributes @protocol ...'
	 (where attributes could be, for example, __attribute__
	 ((deprecated)).
      */
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_AT_INTERFACE:
	  {
	    إذا (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      أرجع result;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    أرجع result;
	  }
	  اكسر;
	حالة RID_AT_IMPLEMENTATION:
	  {
	    إذا (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      أرجع result;
	    إذا (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_بشيا;
	      }
	    c_parser_objc_class_definition (parser, NULL_بشيا);
	    أرجع result;
	  }
	  اكسر;
	حالة RID_AT_PROTOCOL:
	  {
	    إذا (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      أرجع result;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    أرجع result;
	  }
	  اكسر;
	حالة RID_AT_ALIAS:
	حالة RID_AT_CLASS:
	حالة RID_AT_END:
	حالة RID_AT_PROPERTY:
	  إذا (specs->attrs)
	    {
	      c_parser_error (parser, "unexpected attribute");
	      specs->attrs = عدم;
	    }
	  اكسر;
	افتراضي:
	  اكسر;
	}
    }
  وإلا إذا (attribute_fallthrough_p (specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  وإلا إذا (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_attributes (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_بشيا;
  منطقي more_than_one_decl = خطأ;
  طالما (true)
    {
      بنية c_declarator *declarator;
      منطقي dummy = خطأ;
      timevar_id_t tv;
      بشيا fnbody = NULL_بشيا;
      بشيا underspec_name = NULL_بشيا;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_kind != ctsk_none,
					C_DTR_NORMAL, &dummy);
      إذا (declarator == عدم)
	{
	  إذا (omp_declare_simd_clauses)
	    c_finish_omp_declare_simd (parser, NULL_بشيا, NULL_بشيا,
				       omp_declare_simd_clauses);
	  إذا (oacc_routine_data)
	    c_finish_oacc_routine (oacc_routine_data, NULL_بشيا, خطأ);
	  /* This check is here purely to improve the diagnostic.  */
	  إذا (!simple_ok)
	    c_parser_skip_to_end_of_block_or_statement (parser);
	  أرجع result;
	}
      إذا (flag_openmp || flag_openmp_simd)
	{
	  بنية c_declarator *d = declarator;
	  طالما (d->kind != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = عدم;
	  c_parser_handle_directive_omp_attributes (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      إذا (gnu_auto_type_p && declarator->kind != cdk_id)
	{
	  error_at (here,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  أرجع result;
	}
      إذا (std_auto_type_p)
	{
	  بنية c_declarator *d = declarator;
	  طالما (d->kind == cdk_attrs)
	    d = d->declarator;
	  إذا (d->kind != cdk_id)
	    {
	      error_at (here,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      أرجع result;
	    }
	  underspec_name = d->u.id.id;
	}
      وإلا إذا (specs->constexpr_p)
	{
	  بنية c_declarator *d = declarator;
	  طالما (d->kind != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      إذا (c_parser_next_token_is (parser, CPP_EQ)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is_keyword (parser, RID_ASM)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_next_token_is_keyword (parser, RID_IN))
	{
	  بشيا asm_name = NULL_بشيا;
	  بشيا postfix_attrs = NULL_بشيا;
	  إذا (!diagnosed_no_specs && !specs->declspecs_seen_p)
	    {
	      diagnosed_no_specs = true;
	      pedwarn (here, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = خطأ;
	  إذا (c_parser_next_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_فرچ (parser);
	  إذا (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_attributes (parser);
	      إذا (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (here, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  أرجع result;
		}
	    }
	  إذا (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      بشيا d;
	      بنية c_فرچ init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      إذا (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (لي_table, init_loc);
		  unsigned صحيح underspec_state = 0;
		  إذا (std_auto_type_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  start_init (NULL_بشيا, asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  إذا (nested && !empty_ok)
		    flag_sanitize = 0;
		  init = c_parser_فرچ_no_commas (parser, عدم);
		  إذا (std_auto_type_p)
		    finish_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  إذا (gnu_auto_type_p
		      && بشيا_CODE (init.درج) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (بشيا_OPERAND (init.درج, 1)))
		    error_at (here,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_to_rvalue (init_loc, init, true, true,
						   true);
		  بشيا init_type = بشيا_TYPE (init.درج);
		  منطقي vm_type = c_type_variably_modified_p (init_type);
		  إذا (vm_type)
		    init.درج = save_فرچ (init.درج);
		  finish_init ();
		  specs->typespec_kind = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = true;
		  specs->type = init_type;
		  إذا (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_attributes (specs->type,
						  specs->postfix_attrs);
		      decl_attributes (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_بشيا;
		    }
		  إذا (vm_type)
		    {
		      منطقي maybe_const = true;
		      بشيا type_فرچ = c_fully_fold (init.درج, خطأ,
						     &maybe_const);
		      specs->فرچ_const_operands &= maybe_const;
		      إذا (specs->فرچ)
			specs->فرچ = build2 (COMPOUND_فرچ,
					      بشيا_TYPE (type_فرچ),
					      specs->فرچ, type_فرچ);
		      وإلا
			specs->فرچ = type_فرچ;
		    }
		  d = start_decl (declarator, specs, true,
				  chainon (postfix_attrs, all_prefix_attrs));
		  إذا (!d)
		    d = error_mark_كلي;
		  إذا (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_بشيا,
					       omp_declare_simd_clauses);
		  إذا (!omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_بشيا,
					       &omp_dsimd_idattr_clauses);
		}
	      وإلا
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (لي_table, init_loc);
		  unsigned صحيح underspec_state = 0;
		  إذا (specs->constexpr_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  d = start_decl (declarator, specs, true,
				  chainon (postfix_attrs,
					   all_prefix_attrs),
				  !specs->constexpr_p);
		  إذا (!d)
		    d = error_mark_كلي;
		  إذا (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_بشيا,
					       omp_declare_simd_clauses);
		  إذا (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_بشيا,
					       &omp_dsimd_idattr_clauses);
		  start_init (d, asm_name,
			      بشيا_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  إذا (بشيا_CODE (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  إذا (specs->constexpr_p)
		    {
		      finish_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      إذا (omp_declare_simd_clauses)
			c_finish_omp_declare_simd (parser, d, NULL_بشيا,
						   omp_declare_simd_clauses);
		  إذا (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_بشيا,
					       &omp_dsimd_idattr_clauses);
		    }
		  finish_init ();
		}
	      إذا (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, خطأ);
	      إذا (d != error_mark_كلي)
		{
		  maybe_warn_string_init (init_loc, بشيا_TYPE (d), init);
		  finish_decl (d, init_loc, init.درج,
			       init.original_type, asm_name);
		  result = d;
		}
	    }
	  وإلا
	    {
	      إذا (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  أرجع result;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      بشيا attrs = chainon (postfix_attrs, all_prefix_attrs);
	      بشيا d = start_decl (declarator, specs, خطأ, attrs, true,
				   &lastloc);
	      إذا (d && بشيا_CODE (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  ثابت بنية c_declarator *decl = declarator;
		  ثابت بنية c_declarator *last_non_id_attrs = عدم;

		  طالما (decl)
		    بدل (decl->kind)
		      {
		      حالة cdk_array:
		      حالة cdk_function:
		      حالة cdk_pointer:
			last_non_id_attrs = decl;
			decl = decl->declarator;
			اكسر;

		      حالة cdk_attrs:
			decl = decl->declarator;
			اكسر;

		      حالة cdk_id:
			decl = 0;
			اكسر;

		      افتراضي:
			gcc_unreachable ();
		      }

		  /* If it exists and is cdk_function declaration whose
		     arguments have not been set yet, use its arguments.  */
		  إذا (last_non_id_attrs
		      && last_non_id_attrs->kind == cdk_function)
		    {
		      بشيا parms = last_non_id_attrs->u.arg_info->parms;
		      إذا (DECL_ARGUMENTS (d) == NULL_بشيا
			  && DECL_INITIAL (d) == NULL_بشيا)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      إذا (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_empty ())
		{
		  بشيا parms = NULL_بشيا;
		  إذا (d && بشيا_CODE (d) == FUNCTION_DECL)
		    {
		      بنية c_declarator *ce = declarator;
		      طالما (ce != عدم)
			إذا (ce->kind == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    اكسر;
			  }
			وإلا
			  ce = ce->declarator;
		    }
		  إذا (parms)
		    temp_store_parm_decls (d, parms);
		  إذا (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  إذا (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  إذا (parms)
		    temp_چرو_parm_decls ();
		}
	      إذا (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, خطأ);
	      إذا (d)
		finish_decl (d, UNKNOWN_LOCATION, NULL_بشيا,
			     NULL_بشيا, asm_name);

	      إذا (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  إذا (d)
		    *objc_foreach_object_declaration = d;
		  وإلا
		    *objc_foreach_object_declaration = error_mark_كلي;
		}
	    }
	  إذا (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      more_than_one_decl = true;
	      إذا (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  أرجع result;
		}
	      c_parser_consume_token (parser);
	      إذا (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
		all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					    prefix_attrs);
	      وإلا
		all_prefix_attrs = prefix_attrs;
	      استمر;
	    }
	  وإلا إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      إذا (!simple_ok)
		c_parser_consume_token (parser);
	      أرجع result;
	    }
	  وإلا إذا (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      أرجع result;
	    }
	  وإلا
	    {
	      إذا (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      وإلا إذا (more_than_one_decl)
		error_at (here, "declaration in condition can only declare "
			  "a single object");
	      أرجع result;
	    }
	}
      وإلا إذا (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (here,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  أرجع result;
	}
      وإلا إذا (!fndef_ok)
	{
	  إذا (simple_ok && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  وإلا
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	    }
	  أرجع result;
	}
      /* Function definition (nested or otherwise).  */
      إذا (nested)
	{
	  pedwarn (here, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_تور_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      بشيا dv_base = NULL_بشيا;
      بشيا dv_ctx = NULL_بشيا;
      إذا (!vec_safe_is_empty (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->last ();
	  dv_ctx = copy_list (a.selector);
	  dv_base = omp_start_variant_function (declarator, dv_ctx);
	}

      إذا (!start_function (specs, declarator, all_prefix_attrs))
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
	  إذا (c_parser_next_token_starts_declspecs (parser))
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
	      parser->error = خطأ;
	    }
	  وإلا
	    {
	      /* This can appear in many cases looking nothing like a
		 function definition, so we don't give a more specific
		 error suggesting there was one.  */
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			      "or %<__attribute__%>");
	    }
	  إذا (nested)
	    c_چرو_function_context ();
	  اكسر;
	}

      إذا (DECL_DECLARED_INLINE_P (current_function_decl))
        tv = TV_PARSE_INLINE;
      وإلا
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
      صحيح save_debug_nonbind_markers_p = debug_nonbind_markers_p;
      debug_nonbind_markers_p = 0;
      c_parser_maybe_reclassify_token (parser);
      طالما (c_parser_next_token_is_not (parser, CPP_EOF)
	     && c_parser_next_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, خطأ, خطأ, خطأ,
				       true, خطأ, خطأ);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      إذا (omp_declare_simd_clauses)
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_بشيا,
				   omp_declare_simd_clauses);
      إذا (!omp_dsimd_idattr_clauses.is_empty ())
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_بشيا,
				   &omp_dsimd_idattr_clauses);
      إذا (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, current_function_decl, true);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_start_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      إذا (dv_base && current_function_decl != error_mark_كلي)
	{
	  omp_begin_declare_variant_map_entry e
	    = { current_function_decl, dv_base, dv_ctx };
	  vec_safe_تور (omp_begin_declare_variant_map, e);
	}

      /* If the definition was marked with __RTL, use the RTL parser now,
	 consuming the function body.  */
      إذا (specs->declspec_il == cdil_rtl)
	{
	  endloc = c_parser_parse_rtl_body (parser, specs->gimple_or_rtl_pass);

	  /* Normally, store_parm_decls sets next_is_function_body,
	     anticipating a function body.  We need a push_scope/pop_scope
	     pair to flush out this state, or subsequent function parsing
	     will go wrong.  */
	  تور_scope ();
	  چرو_scope ();

	  finish_function (endloc);
	  أرجع result;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      وإلا إذا (specs->declspec_il != cdil_none)
	{
	  منطقي saved = in_late_نبيو_op;
	  in_late_نبيو_op = true;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->entry_bb_كدي);
	  in_late_نبيو_op = saved;
	}
      وإلا
	fnbody = c_parser_compound_statement (parser, &endloc);
      بشيا fndecl = current_function_decl;
      إذا (nested && specs->declspec_il == cdil_none)
	{
	  بشيا decl = current_function_decl;
	  /* Mark nested functions as needing static-chain initially.
	     lower_nested_functions will recompute it but the
	     DECL_STATIC_CHAIN flag is also used before that happens,
	     by initializer_constant_valid_p.  See gcc.dg/nested-fn-2.c.  */
	  DECL_STATIC_CHAIN (decl) = 1;
	  add_stmt (fnbody);
	  finish_function (endloc);
	  c_چرو_function_context ();
	  add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_فرچ, decl));
	}
      وإلا إذا (nested)
	{
	  إذا (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  وإلا
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  finish_function (endloc);
	  c_چرو_function_context ();
	}
      وإلا
	{
	  إذا (fnbody)
	    add_stmt (fnbody);
	  finish_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      إذا (specs->declspec_il != cdil_none)
	DECL_SAVED_بشيا (fndecl) = NULL_بشيا;

      اكسر;
    }

  أرجع result;
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

ساكن فراغ
c_parser_asm_definition (c_parser *parser)
{
  location_t asm_loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  بشيا asm_str = NULL_بشيا;
  بشيا outputs = NULL_بشيا, inputs = NULL_بشيا;
  إذا (!parens.require_open (parser))
    اذهب done;
  asm_str = c_parser_asm_string_literal (parser);
  إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      اذهب done;
    }
  لكل (صحيح section = 0; section < 2; ++section)
    {
      إذا (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  إذا (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
	      asm_str = NULL_بشيا;
	      اذهب done;
	    }
	  c_parser_consume_token (parser);
	}
      وإلا إذا (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, خطأ))
	اذهب error_close_paren;
      إذا (!c_parser_next_token_is (parser, CPP_COLON)
	  && !c_parser_next_token_is (parser, CPP_SCOPE)
	  && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  إذا (section)
	    inputs = c_parser_asm_operands (parser);
	  وإلا
	    outputs = c_parser_asm_operands (parser);
	}
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	اكسر;
    }

  إذا (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
      asm_str = NULL_بشيا;
    }

  إذا (asm_str)
    asm_str = build_asm_فرچ (asm_loc, asm_str, outputs, inputs,
			      NULL_بشيا, NULL_بشيا, خطأ, خطأ);
done:
  إذا (asm_str)
    symtab->finalize_toplevel_asm (asm_str);
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse a static assertion (C11 6.7.10).

   static_assert-declaration:
     static_assert-declaration-no-semi ;
*/

ساكن فراغ
c_parser_static_assert_declaration (c_parser *parser)
{
  c_parser_static_assert_declaration_no_semi (parser);
  إذا (parser->error
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

ساكن فراغ
c_parser_static_assert_declaration_no_semi (c_parser *parser)
{
  location_t assert_loc, درج_loc;
  بشيا درج;
  بشيا string = NULL_بشيا;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT));
  بشيا spelling = c_parser_peek_token (parser)->درج;
  assert_loc = c_parser_peek_token (parser)->location;
  إذا (flag_isoc99)
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  وإلا
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  c_parser_consume_token (parser);
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع;
  location_t درج_tok_loc = c_parser_peek_token (parser)->location;
  درج = convert_lvalue_to_rvalue (درج_tok_loc,
				    c_parser_فرچ_no_commas (parser, عدم),
				    true, true).درج;
  درج_loc = فرچ_LOC_OR_LOC (درج, درج_tok_loc);
  إذا (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_STRING:
	حالة CPP_STRING16:
	حالة CPP_STRING32:
	حالة CPP_WSTRING:
	حالة CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, خطأ, true).درج;
	  اكسر;
	افتراضي:
	  c_parser_error (parser, "expected string literal");
	  أرجع;
	}
    }
  وإلا إذا (flag_isoc11)
    /* If pedantic for pre-C11, the use of _Static_assert itself will
       have been diagnosed, so do not also diagnose the use of this
       new C23 feature of _Static_assert.  */
    pedwarn_c11 (assert_loc, OPT_Wpedantic,
		 "ISO C11 does not support omitting the string in "
		 "%qE", spelling);
  parens.require_close (parser);

  إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (درج)))
    {
      error_at (درج_loc, "expression in static assertion is not an integer");
      أرجع;
    }
  إذا (بشيا_CODE (درج) != INTEGER_CST)
    {
      درج = c_fully_fold (درج, خطأ, عدم);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (درج);
      إذا (بشيا_CODE (درج) == INTEGER_CST)
	pedwarn (درج_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  إذا (بشيا_CODE (درج) != INTEGER_CST)
    {
      error_at (درج_loc, "expression in static assertion is not constant");
      أرجع;
    }
  constant_expression_warning (درج);
  إذا (integer_zerop (درج))
    {
      إذا (string)
	error_at (assert_loc, "static assertion failed: %E", string);
      وإلا
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

فراغ
c_parser_declspecs (c_parser *parser, بنية c_declspecs *specs,
		    منطقي scspec_ok, منطقي typespec_ok, منطقي start_attr_ok,
		    منطقي alignspec_ok, منطقي auto_type_ok,
		    منطقي start_std_attr_ok, منطقي end_std_attr_ok,
		    تعداد c_lookahead_kind la)
{
  منطقي attrs_ok = start_attr_ok;
  منطقي seen_type = specs->typespec_kind != ctsk_none;

  إذا (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  إذا (start_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_seen_p);
      location_t loc = c_parser_peek_token (parser)->location;
      بشيا attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_add_attrs (loc, specs, attrs);
      specs->non_std_attrs_seen_p = خطأ;
    }

  طالما (c_parser_next_token_is (parser, CPP_NAME)
	 || c_parser_next_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_next_token_is (parser, CPP_LESS)))
    {
      بنية c_typespec t;
      بشيا attrs;
      بشيا align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      إذا ((!typespec_ok || specs->typespec_kind == ctsk_tagdef)
	  && c_parser_next_tokens_start_typename (parser, la)
	  && !c_parser_next_token_is_qualifier (parser)
	  && !c_parser_next_token_is_keyword (parser, RID_ALIGNAS))
	اكسر;

      إذا (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  بشيا درج = name_token->درج;
	  c_id_kind kind = name_token->id_kind;

	  إذا (kind == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_FIRST_ADDR_SPACE;
	      declspecs_add_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = true;
	      استمر;
	    }

	  gcc_assert (!c_parser_next_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  إذا (seen_type || !c_parser_next_tokens_start_typename (parser, la))
	    اكسر;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  seen_type = true;
	  attrs_ok = true;
	  إذا (kind == C_ID_ID)
	    {
	      auto_diagnostic_group d;
	      name_hint hint = lookup_name_fuzzy (درج, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      إذا (ثابت حرف *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.add_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    درج, suggestion);
		}
	      وإلا
		error_at (loc, "unknown type name %qE", درج);
	      t.kind = ctsk_typedef;
	      t.spec = error_mark_كلي;
	    }
	  وإلا إذا (kind == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_next_token_is_not (parser, CPP_LESS)))
	    {
	      t.kind = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (درج);
	    }
	  وإلا
	    {
	      بشيا proto = NULL_بشيا;
	      gcc_assert (c_dialect_objc ());
	      t.kind = ctsk_objc;
	      إذا (c_parser_next_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (درج, proto);
	    }
	  t.فرچ = NULL_بشيا;
	  t.فرچ_const_operands = true;
	  t.has_enum_type_specifier = خطأ;
	  declspecs_add_type (name_token->location, specs, t);
	  استمر;
	}
      إذا (c_parser_next_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  بشيا proto;
	  gcc_assert (c_dialect_objc ());
	  إذا (!typespec_ok || seen_type)
	    اكسر;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.kind = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_بشيا, proto);
	  t.فرچ = NULL_بشيا;
	  t.فرچ_const_operands = true;
	  t.has_enum_type_specifier = خطأ;
	  declspecs_add_type (loc, specs, t);
	  استمر;
	}
      gcc_assert (c_parser_next_token_is (parser, CPP_KEYWORD));
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_STATIC:
	حالة RID_EXTERN:
	حالة RID_REGISTER:
	حالة RID_TYPEDEF:
	حالة RID_INLINE:
	حالة RID_NORETURN:
	حالة RID_AUTO:
	حالة RID_THREAD:
	حالة RID_CONSTEXPR:
	  إذا (!scspec_ok)
	    اذهب out;
	  attrs_ok = true;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_add_scspec (loc, specs,
				c_parser_peek_token (parser)->درج);
	  c_parser_consume_token (parser);
	  اكسر;
	حالة RID_AUTO_TYPE:
	  إذا (!auto_type_ok)
	    اذهب out;
	  /* Fall through.  */
	حالة RID_UNSIGNED:
	حالة RID_LONG:
	حالة RID_SHORT:
	حالة RID_SIGNED:
	حالة RID_COMPLEX:
	حالة RID_INT:
	حالة RID_CHAR:
	حالة RID_FLOAT:
	حالة RID_DOUBLE:
	حالة RID_VOID:
	حالة RID_DFLOAT32:
	حالة RID_DFLOAT64:
	حالة RID_DFLOAT128:
	حالة RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	حالة RID_BOOL:
	حالة RID_FRACT:
	حالة RID_ACCUM:
	حالة RID_SAT:
	حالة RID_INT_N_0:
	حالة RID_INT_N_1:
	حالة RID_INT_N_2:
	حالة RID_INT_N_3:
	  إذا (!typespec_ok)
	    اذهب out;
	  attrs_ok = true;
	  seen_type = true;
	  إذا (c_dialect_objc ())
	    parser->objc_need_raw_identifier = true;
	  t.kind = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->درج;
	  t.فرچ = NULL_بشيا;
	  t.فرچ_const_operands = true;
	  t.has_enum_type_specifier = خطأ;
	  declspecs_add_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  اكسر;
	حالة RID_ENUM:
	  إذا (!typespec_ok)
	    اذهب out;
	  attrs_ok = true;
	  seen_type = true;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  اكسر;
	حالة RID_STRUCT:
	حالة RID_UNION:
	  إذا (!typespec_ok)
	    اذهب out;
	  attrs_ok = true;
	  seen_type = true;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  اكسر;
	حالة RID_TYPEOF:
	حالة RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  إذا (!typespec_ok || seen_type)
	    اذهب out;
	  attrs_ok = true;
	  seen_type = true;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_add_type (loc, specs, t);
	  اكسر;
	حالة RID_BITINT:
	  إذا (!typespec_ok)
	    اذهب out;
	  وإلا
	    {
	      attrs_ok = true;
	      seen_type = true;
	      t.kind = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->درج;
	      t.فرچ = error_mark_كلي;
	      t.فرچ_const_operands = true;
	      t.has_enum_type_specifier = خطأ;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      إذا (parens.require_open (parser))
		{
		  c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
		  t.فرچ = convert_lvalue_to_rvalue (loc, فرچ, true,
						     true).درج;
		  parens.skip_until_found_close (parser);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  اكسر;
	حالة RID_ATOMIC:
	  /* C parser handling of Objective-C constructs needs
	     checking for correct lvalue-to-rvalue conversions, and
	     the code in build_modify_expr handling various
	     Objective-C cases, and that in build_unary_op handling
	     Objective-C cases for increment / decrement, also needs
	     updating; uses of TYPE_MAIN_VARIANT in objc_compare_types
	     and objc_types_are_equivalent may also need updates.  */
	  إذا (c_dialect_objc ())
	    sorry ("%<_Atomic%> in Objective-C");
	  إذا (flag_isoc99)
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C99 does not support the %<_Atomic%> qualifier");
	  وإلا
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C90 does not support the %<_Atomic%> qualifier");
	  attrs_ok = true;
	  بشيا درج;
	  درج = c_parser_peek_token (parser)->درج;
	  c_parser_consume_token (parser);
	  إذا (typespec_ok && c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      seen_type = true;
	      c_parser_consume_token (parser);
	      بنية c_type_name *type = c_parser_type_name (parser);
	      t.kind = ctsk_typeof;
	      t.spec = error_mark_كلي;
	      t.فرچ = NULL_بشيا;
	      t.فرچ_const_operands = true;
	      t.has_enum_type_specifier = خطأ;
	      إذا (type != عدم)
		t.spec = groktypename (type, &t.فرچ,
				       &t.فرچ_const_operands);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      إذا (t.spec != error_mark_كلي)
		{
		  إذا (بشيا_CODE (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  وإلا إذا (بشيا_CODE (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  وإلا إذا (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  وإلا
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  وإلا
	    declspecs_add_qual (loc, specs, درج);
	  اكسر;
	حالة RID_CONST:
	حالة RID_VOLATILE:
	حالة RID_RESTRICT:
	  attrs_ok = true;
	  declspecs_add_qual (loc, specs, c_parser_peek_token (parser)->درج);
	  c_parser_consume_token (parser);
	  اكسر;
	حالة RID_ATTRIBUTE:
	  إذا (!attrs_ok)
	    اذهب out;
	  attrs = c_parser_gnu_attributes (parser);
	  declspecs_add_attrs (loc, specs, attrs);
	  اكسر;
	حالة RID_ALIGNAS:
	  إذا (!alignspec_ok)
	    اذهب out;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_add_alignas (loc, specs, align);
	  اكسر;
	حالة RID_GIMPLE:
	  إذا (! flag_gimple)
	    error_at (loc, "%<__GIMPLE%> only valid with %<-fgimple%>");
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_gimple;
	  specs->locations[cdw_gimple] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  اكسر;
	حالة RID_RTL:
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_rtl;
	  specs->locations[cdw_rtl] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  اكسر;
	افتراضي:
	  اذهب out;
	}
    }
 out:
  إذا (end_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    specs->postfix_attrs = c_parser_std_attribute_specifier_sequence (parser);
}

/* Complain about a non-CPP_NAME within an enumerator list.  */

ساكن فراغ
report_bad_enum_name (c_parser *parser)
{
  إذا (!parser->error)
    {
      c_token *token = c_parser_peek_token (parser);
      بدل (token->type)
	{
	افتراضي:
	  اكسر;
	حالة CPP_CLOSE_BRACE:
	  /* Give a nicer error for "enum {}".  */
	  error_at (token->location,
		    "empty enum is invalid");
	  parser->error = true;
	  أرجع;
	حالة CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  إذا (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_group d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_POINTER (token->درج));
	      add_note_about_new_keyword (token->location,
					  token->درج);
	      parser->error = true;
	      أرجع;
	    }
	  اكسر;
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

ساكن بنية c_typespec
c_parser_enum_specifier (c_parser *parser)
{
  بنية c_typespec ret;
  منطقي have_std_attrs;
  منطقي potential_nesting_p = خطأ;
  بشيا std_attrs = NULL_بشيا;
  بشيا attrs;
  بشيا ident = NULL_بشيا;
  بشيا fixed_underlying_type = NULL_بشيا;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  إذا (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));
  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->درج;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  إذا (c_parser_next_token_is (parser, CPP_COLON)
      /* Distinguish an enum-type-specifier from a bit-field
	 declaration of the form "enum e : constant-expression;".  */
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      pedwarn_c11 (enum_loc, OPT_Wpedantic,
		   "ISO C does not support specifying %<enum%> underlying "
		   "types before C23");
      إذا (ident)
	{
	  /* The tag is in scope during the enum-type-specifier (which
	     may refer to the tag inside typeof).  */
	  ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, true);
	  إذا (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_بشيا == TYPE_درجوجي (ret.spec);
	}
      وإلا
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_بشيا;
	  ret.kind = ctsk_tagdef;
	  ret.فرچ = NULL_بشيا;
	  ret.فرچ_const_operands = true;
	  ret.has_enum_type_specifier = true;
	}
      c_parser_consume_token (parser);
      بنية c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, خطأ, true, خطأ, خطأ, خطأ,
			  خطأ, true, cla_prefer_id);
      finish_declspecs (specs);
      إذا (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      وإلا إذا (بشيا_CODE (specs->type) != INTEGER_TYPE
	       && بشيا_CODE (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || بشيا_CODE (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_كلي;
	}
      وإلا إذا (specs->restrict_p)
	error_at (enum_loc, "invalid use of %<restrict%>");
      fixed_underlying_type = TYPE_MAIN_VARIANT (specs->type);
      إذا (ident)
	{
	  /* The type specified must be consistent with any previously
	     specified underlying type.  If this is a newly declared
	     type, it is now a complete type.  */
	  إذا (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
	      && ENUM_UNDERLYING_TYPE (ret.spec) == NULL_بشيا)
	    {
	      TYPE_MIN_درج (ret.spec) =
		TYPE_MIN_درج (fixed_underlying_type);
	      TYPE_MAX_درج (ret.spec) =
		TYPE_MAX_درج (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      SET_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_SIZE (ret.spec) = NULL_بشيا;
	      TYPE_PRECISION (ret.spec) =
		TYPE_PRECISION (fixed_underlying_type);
	      ENUM_UNDERLYING_TYPE (ret.spec) = fixed_underlying_type;
	      layout_type (ret.spec);
	    }
	  وإلا إذا (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
		   && !comptypes (fixed_underlying_type,
				  ENUM_UNDERLYING_TYPE (ret.spec)))
	    {
	      error_at (enum_loc, "%<enum%> underlying type incompatible with "
			"previous declaration");
	      fixed_underlying_type = ENUM_UNDERLYING_TYPE (ret.spec);
	    }
	}
    }
  إذا (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      بنية c_enum_contents the_enum;
      بشيا type;
      بشيا postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      بشيا درجوجي;
      timevar_تور (TV_PARSE_ENUM);
      type = start_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      درجوجي = NULL_بشيا;
      c_parser_consume_token (parser);
      طالما (true)
	{
	  بشيا enum_id;
	  بشيا enum_درج;
	  بشيا enum_decl;
	  منطقي seen_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, درج_loc;
	  إذا (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, عدم);
	      درجوجي = error_mark_كلي;
	      اكسر;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->درج;
	  /* Set the location in case we create a decl now.  */
	  c_parser_set_source_position_from_token (token);
	  decl_loc = درج_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  بشيا std_attrs = NULL_بشيا;
	  إذا (c_parser_nth_token_starts_std_attributes (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  بشيا enum_attrs = chainon (std_attrs,
				     c_parser_gnu_attributes (parser));
	  إذا (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      درج_loc = c_parser_peek_token (parser)->location;
	      enum_درج = convert_lvalue_to_rvalue (درج_loc,
						     (c_parser_فرچ_no_commas
						      (parser, عدم)),
						     true, true).درج;
	    }
	  وإلا
	    enum_درج = NULL_بشيا;
	  enum_decl = build_enumerator (decl_loc, درج_loc,
					&the_enum, enum_id, enum_درج);
	  إذا (enum_attrs)
	    decl_attributes (&بشيا_PURPOSE (enum_decl), enum_attrs, 0);
	  بشيا_CHAIN (enum_decl) = درجوجي;
	  درجوجي = enum_decl;
	  seen_comma = خطأ;
	  إذا (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      seen_comma = true;
	      c_parser_consume_token (parser);
	    }
	  إذا (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      إذا (seen_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      اكسر;
	    }
	  إذا (!seen_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, عدم);
	      درجوجي = error_mark_كلي;
	      اكسر;
	    }
	}
      postfix_attrs = c_parser_gnu_attributes (parser);
      ret.spec = finish_enum (type, nreverse (درجوجي),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.kind = ctsk_tagdef;
      ret.فرچ = NULL_بشيا;
      ret.فرچ_const_operands = true;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_بشيا;
      timevar_چرو (TV_PARSE_ENUM);
      أرجع ret;
    }
  وإلا إذا (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_كلي;
      ret.kind = ctsk_tagref;
      ret.فرچ = NULL_بشيا;
      ret.فرچ_const_operands = true;
      ret.has_enum_type_specifier = خطأ;
      أرجع ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  إذا (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  إذا (fixed_underlying_type == NULL_بشيا)
    {
      ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
			     std_attrs, خطأ);
      /* In ISO C, enumerated types without a fixed underlying type
	 can be referred to only if already defined.  */
      إذا (pedantic && !COMPLETE_TYPE_P (ret.spec))
	{
	  gcc_assert (ident);
	  pedwarn (enum_loc, OPT_Wpedantic,
		   "ISO C forbids forward references to %<enum%> types");
	}
    }
  أرجع ret;
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

ساكن بنية c_typespec
c_parser_struct_or_union_specifier (c_parser *parser)
{
  بنية c_typespec ret;
  منطقي have_std_attrs;
  بشيا std_attrs = NULL_بشيا;
  بشيا attrs;
  بشيا ident = NULL_بشيا;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  تعداد بشيا_code code;
  بدل (c_parser_peek_token (parser)->keyword)
    {
    حالة RID_STRUCT:
      code = RECORD_TYPE;
      اكسر;
    حالة RID_UNION:
      code = UNION_TYPE;
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  إذا (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->درج;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  إذا (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      صنف c_struct_parse_info *struct_info;
      بشيا type = start_struct (struct_loc, code, ident, &struct_info);
      بشيا postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      بشيا contents;
      بشيا فرچ = عدم;
      timevar_تور (TV_PARSE_STRUCT);
      contents = NULL_بشيا;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      إذا (c_parser_next_token_is_keyword (parser, RID_AT_DEFS))
	{
	  بشيا name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  إذا (!parens.require_open (parser))
	    اذهب end_at_defs;
	  إذا (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->درج;
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
	      اذهب end_at_defs;
	    }
	  parens.skip_until_found_close (parser);
	  contents = nreverse (objc_get_class_ivars (name));
	}
    end_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      طالما (true)
	{
	  بشيا decls;
	  /* Parse any stray semicolon.  */
	  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      location_t semicolon_loc
		= c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (semicolon_loc);
	      richloc.add_fixit_remove ();
	      pedwarn (&richloc, OPT_Wpedantic,
		       "extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      استمر;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  إذا (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      اكسر;
	    }
	  /* Accept #pragmas at struct scope.  */
	  إذا (c_parser_next_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, عدم, NULL_بشيا);
	      استمر;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &فرچ);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  وإلا
	    {
	      إذا (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      وإلا إذا (parser->error
		       || !c_parser_next_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, عدم);
		  اكسر;
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
				struct_info, &فرچ);
      ret.kind = ctsk_tagdef;
      ret.فرچ = فرچ;
      ret.فرچ_const_operands = true;
      ret.has_enum_type_specifier = خطأ;
      timevar_چرو (TV_PARSE_STRUCT);
      أرجع ret;
    }
  وإلا إذا (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_كلي;
      ret.kind = ctsk_tagref;
      ret.فرچ = NULL_بشيا;
      ret.فرچ_const_operands = true;
      ret.has_enum_type_specifier = خطأ;
      أرجع ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  إذا (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_tag (ident_loc, code, ident, have_std_attrs, std_attrs,
			 خطأ);
  أرجع ret;
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

ساكن بشيا
c_parser_struct_declaration (c_parser *parser, بشيا *فرچ)
{
  بنية c_declspecs *specs;
  بشيا prefix_attrs;
  بشيا all_prefix_attrs;
  بشيا decls;
  location_t decl_loc;
  إذا (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      صحيح ext;
      بشيا decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, فرچ);
      restore_extension_diagnostics (ext);
      أرجع decl;
    }
  إذا (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      أرجع NULL_بشيا;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, خطأ, true, true,
		      true, خطأ, true, true, cla_nonabstract_decl);
  إذا (parser->error)
    أرجع NULL_بشيا;
  إذا (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      أرجع NULL_بشيا;
    }
  finish_declspecs (specs);
  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      بشيا ret;
      إذا (specs->typespec_kind == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_tag_warned (specs, pedantic);
	  ret = NULL_بشيا;
	}
      وإلا
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  بشيا attrs = عدم;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_بشيا), specs,
			   NULL_بشيا, &attrs, فرچ);
	  إذا (ret)
	    decl_attributes (&ret, attrs, 0);
	}
      أرجع ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  إذا (specs->typespec_kind == ctsk_tagdef
      && بشيا_CODE (specs->type) != ENUMERAL_TYPE
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = خطأ;
      أرجع NULL_بشيا;
    }

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_بشيا;
  decls = NULL_بشيا;
  طالما (true)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      بنية c_declarator *declarator;
      منطقي dummy = خطأ;
      إذا (c_parser_next_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_بشيا);
      وإلا
	declarator = c_parser_declarator (parser,
					  specs->typespec_kind != ctsk_none,
					  C_DTR_NORMAL, &dummy);
      إذا (declarator == عدم)
	{
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  اكسر;
	}
      إذا (c_parser_next_token_is (parser, CPP_COLON)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  بشيا postfix_attrs = NULL_بشيا;
	  بشيا width = NULL_بشيا;
	  بشيا d;
	  إذا (c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      width = convert_lvalue_to_rvalue (loc,
						(c_parser_فرچ_no_commas
						 (parser, عدم)),
						true, true).درج;
	    }
	  إذا (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_attributes (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, width, &all_prefix_attrs, فرچ);
	  decl_attributes (&d, chainon (postfix_attrs,
					all_prefix_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  إذا (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					prefix_attrs);
	  وإلا
	    all_prefix_attrs = prefix_attrs;
	  إذا (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا إذا (c_parser_next_token_is (parser, CPP_SEMICOLON)
		   || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      /* Semicolon consumed in caller.  */
	      اكسر;
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected %<,%>, %<;%> or %<}%>");
	      اكسر;
	    }
	}
      وإلا
	{
	  c_parser_error (parser,
			  "expected %<:%>, %<,%>, %<;%>, %<}%> or "
			  "%<__attribute__%>");
	  اكسر;
	}
    }
  أرجع decls;
}

/* Parse a typeof specifier (a GNU extension adopted in C23).

   typeof-specifier:
     typeof ( expression )
     typeof ( type-name )
     typeof_unqual ( expression )
     typeof_unqual ( type-name )
*/

ساكن بنية c_typespec
c_parser_typeof_specifier (c_parser *parser)
{
  منطقي is_unqual;
  منطقي is_std;
  بنية c_typespec ret;
  ret.kind = ctsk_typeof;
  ret.spec = error_mark_كلي;
  ret.فرچ = NULL_بشيا;
  ret.فرچ_const_operands = true;
  ret.has_enum_type_specifier = خطأ;
  إذا (c_parser_next_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = خطأ;
      بشيا spelling = c_parser_peek_token (parser)->درج;
      is_std = (flag_isoc23
		&& strcmp (IDENTIFIER_POINTER (spelling), "typeof") == 0);
    }
  وإلا
    {
      gcc_assert (c_parser_next_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = true;
      بشيا spelling = c_parser_peek_token (parser)->درج;
      is_std = strcmp (IDENTIFIER_POINTER (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_typeof++;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      أرجع ret;
    }
  إذا (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      بنية c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      إذا (type != عدم)
	{
	  ret.spec = groktypename (type, &ret.فرچ, &ret.فرچ_const_operands);
	  چرو_maybe_used (c_type_variably_modified_p (ret.spec));
	}
    }
  وإلا
    {
      منطقي was_vm;
      location_t here = c_parser_peek_token (parser)->location;
      بنية c_فرچ فرچ = c_parser_expression (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      إذا (بشيا_CODE (فرچ.درج) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (بشيا_OPERAND (فرچ.درج, 1)))
	error_at (here, "%<typeof%> applied to a bit-field");
      mark_exp_read (فرچ.درج);
      ret.spec = بشيا_TYPE (فرچ.درج);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      إذا (was_vm)
	ret.فرچ = c_fully_fold (فرچ.درج, خطأ, &ret.فرچ_const_operands);
      چرو_maybe_used (was_vm);
    }
  parens.skip_until_found_close (parser);
  إذا (ret.spec != error_mark_كلي)
    {
      إذا (is_unqual)
	{
	  منطقي is_array = بشيا_CODE (ret.spec) == ARRAY_TYPE;
	  صحيح quals = TYPE_QUALS (strip_array_types (ret.spec));
	  إذا ((is_array ? quals & ~TYPE_QUAL_ATOMIC : quals)
	      != TYPE_UNQUALIFIED)
	    {
	      ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	      إذا (quals & TYPE_QUAL_ATOMIC && is_array)
		ret.spec = c_build_qualified_type (ret.spec,
						   TYPE_QUAL_ATOMIC);
	    }
	}
      إذا (is_std)
	{
	  /* In ISO C terms, _Noreturn is not part of the type of
	     expressions such as &abort, but in GCC it is represented
	     internally as a type qualifier.  */
	  إذا (بشيا_CODE (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  وإلا إذا (FUNCTION_POINTER_TYPE_P (ret.spec)
		   && TYPE_QUALS (بشيا_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_pointer_type (TYPE_MAIN_VARIANT (بشيا_TYPE (ret.spec)));
	}
    }
  أرجع ret;
}

/* Parse an alignment-specifier.

   C11 6.7.5:

   alignment-specifier:
     _Alignas ( type-name )
     _Alignas ( constant-expression )
*/

ساكن بشيا
c_parser_alignas_specifier (c_parser * parser)
{
  بشيا ret = error_mark_كلي;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNAS));
  بشيا spelling = c_parser_peek_token (parser)->درج;
  c_parser_consume_token (parser);
  إذا (flag_isoc99)
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  وإلا
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع ret;
  إذا (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      بنية c_type_name *type = c_parser_type_name (parser);
      إذا (type != عدم)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, عدم, عدم),
					خطأ, true, 1);
    }
  وإلا
    ret = convert_lvalue_to_rvalue (loc,
				    c_parser_فرچ_no_commas (parser, عدم),
				    true, true).درج;
  parens.skip_until_found_close (parser);
  أرجع ret;
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

بنية c_declarator *
c_parser_declarator (c_parser *parser, منطقي type_seen_p, c_dtr_syn kind,
		     منطقي *seen_id)
{
  /* Parse any initial pointer part.  */
  إذا (c_parser_next_token_is (parser, CPP_MULT))
    {
      بنية c_declspecs *quals_attrs = build_null_declspecs ();
      بنية c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, خطأ, خطأ, true,
			  خطأ, خطأ, true, خطأ, cla_prefer_id);
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      إذا (inner == عدم)
	أرجع عدم;
      وإلا
	أرجع make_pointer_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  أرجع c_parser_direct_declarator (parser, type_seen_p, kind, seen_id);
}

/* Parse a direct declarator or direct abstract declarator; arguments
   as c_parser_declarator.  */

ساكن بنية c_declarator *
c_parser_direct_declarator (c_parser *parser, منطقي type_seen_p, c_dtr_syn kind,
			    منطقي *seen_id)
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

  إذا (kind != C_DTR_ABSTRACT
      && c_parser_next_token_is (parser, CPP_NAME)
      && ((type_seen_p
	   && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_kind == C_ID_ID))
    {
      بنية c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->درج);
      *seen_id = true;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (c_parser_nth_token_starts_std_attributes (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      أرجع c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  إذا (kind != C_DTR_NORMAL
      && c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      بنية c_declarator *inner = build_id_declarator (NULL_بشيا);
      inner->id_loc = c_parser_peek_token (parser)->location;
      أرجع c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      بشيا attrs;
      بنية c_declarator *inner;
      c_parser_consume_token (parser);
      منطقي have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      إذا (kind != C_DTR_NORMAL
	  && (c_parser_next_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_attributes (parser, 1)
		      || c_parser_next_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  بنية c_arg_info *حجوجي
	    = c_parser_parms_declarator (parser, kind == C_DTR_NORMAL,
					 attrs, have_gnu_attrs);
	  إذا (حجوجي == عدم)
	    أرجع عدم;
	  وإلا
	    {
	      inner = build_id_declarator (NULL_بشيا);
	      إذا (!(حجوجي->types
		    && حجوجي->types != error_mark_كلي
		    && بشيا_CODE (بشيا_درج (حجوجي->types)) == IDENTIFIER_كلي)
		  && c_parser_nth_token_starts_std_attributes (parser, 1))
		{
		  بشيا std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  إذا (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (حجوجي, inner);
	      أرجع c_parser_direct_declarator_inner (parser, *seen_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      إذا (inner != عدم && attrs != عدم)
	inner = build_attrs_declarator (attrs, inner);
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  إذا (inner == عدم)
	    أرجع عدم;
	  وإلا
	    أرجع c_parser_direct_declarator_inner (parser, *seen_id, inner);
	}
      وإلا
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع عدم;
	}
    }
  وإلا
    {
      إذا (kind == C_DTR_NORMAL)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  أرجع عدم;
	}
      وإلا
	أرجع build_id_declarator (NULL_بشيا);
    }
}

/* Parse part of a direct declarator or direct abstract declarator,
   given that some (in INNER) has already been parsed; ID_PRESENT is
   true if an identifier is present, false for an abstract
   declarator.  */

ساكن بنية c_declarator *
c_parser_direct_declarator_inner (c_parser *parser, منطقي id_present,
				  بنية c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  إذا (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      بنية c_declarator *declarator;
      بنية c_declspecs *quals_attrs = build_null_declspecs ();
      بنية c_فرچ dimen;
      dimen.درج = NULL_بشيا;
      dimen.original_code = ERROR_MARK;
      dimen.original_type = NULL_بشيا;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, خطأ, خطأ, true,
			  خطأ, خطأ, خطأ, خطأ, cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      إذا (c_parser_next_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  إذا (!quals_attrs->declspecs_seen_p)
	    c_parser_declspecs (parser, quals_attrs, خطأ, خطأ, true,
				خطأ, خطأ, خطأ, خطأ, cla_prefer_id);
	}
      إذا (!quals_attrs->declspecs_seen_p)
	quals_attrs = عدم;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      ثابت منطقي static_seen = (static_loc != UNKNOWN_LOCATION);
      منطقي star_seen = خطأ;
      إذا (c_parser_next_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_SQUARE)
	{
	  star_seen = true;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	dimen = c_parser_فرچ_no_commas (parser, عدم);

      إذا (static_seen)
	{
	  إذا (star_seen)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      star_seen = خطأ;
	      dimen.درج = error_mark_كلي;
	    }
	  وإلا إذا (!dimen.درج)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      إذا (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	c_parser_consume_token (parser);
      وإلا
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  أرجع عدم;
	}
      إذا (dimen.درج)
	dimen = convert_lvalue_to_rvalue (brace_loc, dimen, true, true);
      declarator = build_array_declarator (brace_loc, dimen.درج, quals_attrs,
					   static_seen, star_seen);
      إذا (declarator == عدم)
	أرجع عدم;
      إذا (c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  بشيا std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  إذا (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = set_array_declarator_inner (declarator, inner);
      أرجع c_parser_direct_declarator_inner (parser, id_present, inner);
    }
  وإلا إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      بشيا attrs;
      بنية c_arg_info *حجوجي;
      c_parser_consume_token (parser);
      منطقي have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      حجوجي = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      إذا (حجوجي == عدم)
	أرجع عدم;
      وإلا
	{
	  إذا (!(حجوجي->types
		&& حجوجي->types != error_mark_كلي
		&& بشيا_CODE (بشيا_درج (حجوجي->types)) == IDENTIFIER_كلي)
	      && c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      بشيا std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      إذا (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (حجوجي, inner);
	  أرجع c_parser_direct_declarator_inner (parser, id_present, inner);
	}
    }
  أرجع inner;
}

/* Parse a parameter list or identifier list, including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list.  ID_LIST_OK is true if an identifier list
   is acceptable; such a list must not have attributes at the start.
   HAVE_GNU_ATTRS says whether any gnu-attributes (including empty
   attributes) were present (in which case standard attributes cannot
   occur).  */

ساكن بنية c_arg_info *
c_parser_parms_declarator (c_parser *parser, منطقي id_list_ok, بشيا attrs,
			   منطقي have_gnu_attrs)
{
  تور_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  إذا (id_list_ok
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
      بشيا list = NULL_بشيا, *nextp = &list;
      طالما (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  *nextp = build_بشيا_list (NULL_بشيا,
				    c_parser_peek_token (parser)->درج);
	  nextp = & بشيا_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  إذا (c_parser_next_token_is_not (parser, CPP_COMMA))
	    اكسر;
	  c_parser_consume_token (parser);
	  إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      اكسر;
	    }
	}
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  بنية c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  چرو_scope ();
	  أرجع ret;
	}
      وإلا
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  چرو_scope ();
	  أرجع عدم;
	}
    }
  وإلا
    {
      بنية c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, عدم, have_gnu_attrs);
      چرو_scope ();
      أرجع ret;
    }
}

/* Parse a parameter list (possibly empty), including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list; if HAVE_GNU_ATTRS, there were some such
   attributes (possibly empty, in which case ATTRS is NULL_TREE),
   which means standard attributes cannot start the list.  EXPR is
   NULL or an expression that needs to be evaluated for the side
   effects of array size expressions in the parameters.  */

ساكن بنية c_arg_info *
c_parser_parms_list_declarator (c_parser *parser, بشيا attrs, بشيا فرچ,
				منطقي have_gnu_attrs)
{
  منطقي bad_parm = خطأ;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      بنية c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      أرجع ret;
    }
  إذا (c_parser_next_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      بنية c_arg_info *ret = build_arg_info ();

      ret->types = NULL_بشيا;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_حجوجي_stdarg_p = true;
	  c_parser_consume_token (parser);
	  أرجع ret;
	}
      وإلا
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع عدم;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  طالما (true)
    {
      /* Parse a parameter.  */
      بنية c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_بشيا;
      have_gnu_attrs = خطأ;
      إذا (parm == عدم)
	bad_parm = true;
      وإلا
	تور_parm_decl (parm, &فرچ);
      إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  بشيا new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  منطقي new_have_gnu_attrs
	    = c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_attributes (parser);
	  أرجع c_parser_parms_list_declarator (parser, new_attrs, فرچ,
						 new_have_gnu_attrs);
	}
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  إذا (bad_parm)
	    أرجع عدم;
	  وإلا
	    أرجع get_parm_info (خطأ, فرچ);
	}
      إذا (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, خطأ))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع عدم;
	}
      إذا (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      إذا (bad_parm)
		أرجع عدم;
	      وإلا
		أرجع get_parm_info (true, فرچ);
	    }
	  وإلا
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      أرجع عدم;
	    }
	}
    }
}

/* Parse a parameter declaration.  ATTRS are the gnu-attributes at the
   start of the declaration if it is the first parameter;
   HAVE_GNU_ATTRS is true if there were any gnu-attributes there (even
   empty) there.  */

ساكن بنية c_parm *
c_parser_parameter_declaration (c_parser *parser, بشيا attrs,
				منطقي have_gnu_attrs)
{
  بنية c_declspecs *specs;
  بنية c_declarator *declarator;
  بشيا prefix_attrs;
  بشيا postfix_attrs = NULL_بشيا;
  منطقي dummy = خطأ;

  /* Accept #pragmas between parameter declarations.  */
  طالما (c_parser_next_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, عدم, NULL_بشيا);

  إذا (!c_parser_next_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (parser->error)
	أرجع عدم;
      c_parser_set_source_position_from_token (token);
      إذا (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (token->درج,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  إذا (ثابت حرف *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->درج, suggestion);
	    }
	  وإلا
	    error_at (token->location, "unknown type name %qE", token->درج);
	  parser->error = true;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      وإلا
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_to_end_of_parameter (parser);
      أرجع عدم;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  إذا (attrs)
    {
      declspecs_add_attrs (شغرو_location, specs, attrs);
      attrs = NULL_بشيا;
    }
  c_parser_declspecs (parser, specs, true, true, true, true, خطأ,
		      !have_gnu_attrs, true, cla_nonabstract_decl);
  finish_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  إذا (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_كولي_anonymous_type (specs->type);

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  specs->attrs = NULL_بشيا;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_PARM, &dummy);
  إذا (declarator == عدم)
    {
      c_parser_skip_until_found (parser, CPP_COMMA, عدم);
      أرجع عدم;
    }
  إذا (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
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
  طالما (id_declarator && id_declarator->kind != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : start_loc);
  location_t param_loc = make_location (caret_loc, start_loc, end_loc);

  أرجع build_c_parm (specs, chainon (postfix_attrs, prefix_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

ساكن بشيا
c_parser_asm_string_literal (c_parser *parser)
{
  بشيا str;
  صحيح save_flag = warn_overlength_strings;
  warn_overlength_strings = 0;
  str = c_parser_string_literal (parser, خطأ, خطأ).درج;
  warn_overlength_strings = save_flag;
  أرجع str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

ساكن بشيا
c_parser_simple_asm_فرچ (c_parser *parser)
{
  بشيا str;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع NULL_بشيا;
  str = c_parser_asm_string_literal (parser);
  إذا (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
      أرجع NULL_بشيا;
    }
  أرجع str;
}

ساكن بشيا
c_parser_gnu_attribute_any_word (c_parser *parser)
{
  بشيا attr_name = NULL_بشيا;

  إذا (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      /* ??? See comment above about what keywords are accepted here.  */
      منطقي ok;
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_STATIC:
	حالة RID_UNSIGNED:
	حالة RID_LONG:
	حالة RID_CONST:
	حالة RID_EXTERN:
	حالة RID_REGISTER:
	حالة RID_TYPEDEF:
	حالة RID_SHORT:
	حالة RID_INLINE:
	حالة RID_NORETURN:
	حالة RID_VOLATILE:
	حالة RID_SIGNED:
	حالة RID_AUTO:
	حالة RID_RESTRICT:
	حالة RID_COMPLEX:
	حالة RID_THREAD:
	حالة RID_INT:
	حالة RID_CHAR:
	حالة RID_FLOAT:
	حالة RID_DOUBLE:
	حالة RID_VOID:
	حالة RID_DFLOAT32:
	حالة RID_DFLOAT64:
	حالة RID_DFLOAT128:
	حالة RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	حالة RID_BOOL:
	حالة RID_BITINT:
	حالة RID_FRACT:
	حالة RID_ACCUM:
	حالة RID_SAT:
	حالة RID_TRANSACTION_ATOMIC:
	حالة RID_TRANSACTION_CANCEL:
	حالة RID_ATOMIC:
	حالة RID_AUTO_TYPE:
	حالة RID_CONSTEXPR:
	حالة RID_INT_N_0:
	حالة RID_INT_N_1:
	حالة RID_INT_N_2:
	حالة RID_INT_N_3:
	  ok = true;
	  اكسر;
	افتراضي:
	  ok = خطأ;
	  اكسر;
	}
      إذا (!ok)
	أرجع NULL_بشيا;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(صحيح) c_parser_peek_token (parser)->keyword];
    }
  وإلا إذا (c_parser_next_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->درج;

  أرجع attr_name;
}

/* Parse attribute arguments.  This is a common form of syntax
   covering all currently valid GNU and standard attributes.

   gnu-attribute-arguments:
     identifier
     identifier , nonempty-expr-list
     expr-list

   where the "identifier" must not be declared as a type.  ??? Why not
   allow identifiers declared as types to start the arguments?  */

ساكن بشيا
c_parser_attribute_arguments (c_parser *parser, منطقي takes_identifier,
			      منطقي require_string, منطقي assume_attr,
			      منطقي allow_empty_حجوجي)
{
  vec<بشيا, va_gc> *فرچ_list;
  بشيا attr_حجوجي;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  إذا (c_parser_next_token_is (parser, CPP_NAME)
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
      بشيا arg1 = c_parser_peek_token (parser)->درج;
      c_parser_consume_token (parser);
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	attr_حجوجي = build_بشيا_list (NULL_بشيا, arg1);
      وإلا
	{
	  بشيا بشيا_list;
	  c_parser_consume_token (parser);
	  فرچ_list = c_parser_فرچ_list (parser, خطأ, true,
					  عدم, عدم, عدم, عدم);
	  بشيا_list = build_بشيا_list_vec (فرچ_list);
	  attr_حجوجي = بشيا_cons (NULL_بشيا, arg1, بشيا_list);
	  release_بشيا_vector (فرچ_list);
	}
    }
  وإلا
    {
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  إذا (!allow_empty_حجوجي)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_حجوجي = NULL_بشيا;
	}
      وإلا إذا (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  بشيا string = c_parser_string_literal (parser, خطأ, true).درج;
	  attr_حجوجي = build_بشيا_list (NULL_بشيا, string);
	}
      وإلا إذا (assume_attr)
	{
	  بشيا cond
	    = c_parser_conditional_expression (parser, عدم, NULL_بشيا).درج;
	  إذا (!c_parser_next_token_is (parser, CPP_COMMA))
	    attr_حجوجي = build_بشيا_list (NULL_بشيا, cond);
	  وإلا
	    {
	      بشيا بشيا_list;
	      c_parser_consume_token (parser);
	      فرچ_list = c_parser_فرچ_list (parser, خطأ, true,
					      عدم, عدم, عدم, عدم);
	      بشيا_list = build_بشيا_list_vec (فرچ_list);
	      attr_حجوجي = بشيا_cons (NULL_بشيا, cond, بشيا_list);
	      release_بشيا_vector (فرچ_list);
	    }
	}
      وإلا
	{
	  فرچ_list = c_parser_فرچ_list (parser, خطأ, true,
					  عدم, عدم, عدم, عدم);
	  attr_حجوجي = build_بشيا_list_vec (فرچ_list);
	  release_بشيا_vector (فرچ_list);
	}
    }
  أرجع attr_حجوجي;
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

ساكن بشيا
c_parser_gnu_attribute (c_parser *parser, بشيا attrs,
			منطقي expect_comma = خطأ, منطقي empty_ok = true)
{
  منطقي comma_first = c_parser_next_token_is (parser, CPP_COMMA);
  إذا (!comma_first
      && !c_parser_next_token_is (parser, CPP_NAME)
      && !c_parser_next_token_is (parser, CPP_KEYWORD))
    أرجع NULL_بشيا;

  طالما (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      إذا (!empty_ok)
	أرجع attrs;
    }

  بشيا attr_name = c_parser_gnu_attribute_any_word (parser);
  إذا (attr_name == NULL_بشيا)
    أرجع NULL_بشيا;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  بشيا attr;
  إذا (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      إذا (expect_comma && !comma_first)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع error_mark_كلي;
	}
      attr = build_بشيا_list (attr_name, NULL_بشيا);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      أرجع attrs;
    }
  c_parser_consume_token (parser);

  بشيا attr_حجوجي
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    خطأ,
				    is_attribute_p ("assume", attr_name),
				    true);

  attr = build_بشيا_list (attr_name, attr_حجوجي);
  إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  وإلا
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      أرجع error_mark_كلي;
    }

  إذا (expect_comma && !comma_first)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      أرجع error_mark_كلي;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  أرجع attrs;
}

ساكن بشيا
c_parser_gnu_attributes (c_parser *parser)
{
  بشيا attrs = NULL_بشيا;
  طالما (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      منطقي save_translate_strings_p = parser->translate_strings_p;
      parser->translate_strings_p = خطأ;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  أرجع attrs;
	}
      إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      لكل (منطقي expect_comma = خطأ; ; expect_comma = true)
	{
	  /* Parse a single attribute.  */
	  بشيا attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  إذا (attr == error_mark_كلي)
	    أرجع attrs;
	  إذا (!attr)
	    اكسر;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      وإلا
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع attrs;
	}
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      وإلا
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع attrs;
	}
      parser->translate_strings_p = save_translate_strings_p;
    }

  أرجع attrs;
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

ساكن فراغ
c_parser_balanced_token_sequence (c_parser *parser)
{
  طالما (true)
    {
      c_token *token = c_parser_peek_token (parser);
      بدل (token->type)
	{
	حالة CPP_OPEN_BRACE:
	  {
	    matching_braces braces;
	    braces.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    braces.require_close (parser);
	    اكسر;
	  }

	حالة CPP_OPEN_PAREN:
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    parens.require_close (parser);
	    اكسر;
	  }

	حالة CPP_OPEN_SQUARE:
	  c_parser_consume_token (parser);
	  c_parser_balanced_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
	  اكسر;

	حالة CPP_CLOSE_BRACE:
	حالة CPP_CLOSE_PAREN:
	حالة CPP_CLOSE_SQUARE:
	حالة CPP_EOF:
	  أرجع;

	حالة CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, خطأ);
	  اكسر;

	افتراضي:
	  c_parser_consume_token (parser);
	  اكسر;
	}
    }
}

/* Parse arguments of omp::directive or omp::decl attribute.

   directive-name ,[opt] clause-list[opt]

   For directive just remember the tokens in a vector for subsequent
   parsing.  */

ساكن فراغ
c_parser_omp_directive_حجوجي (c_parser *parser, بشيا attribute, منطقي decl_p)
{
  unsigned صحيح n = 1;
  c_token *first = c_parser_peek_token (parser);
  إذا (!c_parser_check_balanced_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_balanced_token_sequence (parser);
      بشيا_درج (attribute) = NULL_بشيا;
      أرجع;
    }
  إذا (n == 1)
    {
      error_at (first->location, "expected OpenMP directive name");
      بشيا_درج (attribute) = NULL_بشيا;
      أرجع;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  لكل (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->quick_تور (*tok);
      c_parser_consume_token (parser);
    }
  بشيا arg = make_كلي (C_TOKEN_VEC);
  C_TOKEN_VEC_TOKENS (arg) = v;
  إذا (decl_p)
    بشيا_PUBLIC (arg) = 1;
  بشيا_درج (attribute) = بشيا_cons (NULL_بشيا, arg, بشيا_درج (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

ساكن فراغ
c_parser_omp_sequence_حجوجي (c_parser *parser, بشيا attribute)
{
  افعل
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_NAME
	  && strcmp (IDENTIFIER_POINTER (token->درج), "omp") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_SCOPE)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  token = c_parser_peek_token (parser);
	}
      منطقي directive = خطأ;
      ثابت حرف *p;
      إذا (token->type != CPP_NAME)
	p = "";
      وإلا
	p = IDENTIFIER_POINTER (token->درج);
      إذا (strcmp (p, "directive") == 0)
	directive = true;
      وإلا إذا (strcmp (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  unsigned nesting_depth = 0;

	  طالما (true)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      إذا ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_depth)
		اكسر;
	      /* If we've run out of tokens, stop.  */
	      إذا (token->type == CPP_EOF)
		اكسر;
	      إذا (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
		اكسر;
	      إذا (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_SQUARE)
		++nesting_depth;
	      وإلا إذا (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_SQUARE)
		{
		  إذا (nesting_depth-- == 0)
		    اكسر;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  إذا (c_parser_next_token_is_not (parser, CPP_COMMA))
	    اكسر;
	  c_parser_consume_token (parser);
	  استمر;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      إذا (parens.require_open (parser))
	{
	  إذا (directive)
	    c_parser_omp_directive_حجوجي (parser, attribute, خطأ);
	  وإلا
	    c_parser_omp_sequence_حجوجي (parser, attribute);
	  parens.skip_until_found_close (parser);
	  إذا (c_parser_next_token_is_not (parser, CPP_COMMA))
	    اكسر;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (c_parser_next_token_is_not (parser, CPP_COMMA))
	اكسر;
      وإلا
	c_parser_consume_token (parser);
    }
  طالما (1);
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

ساكن بشيا
c_parser_std_attribute (c_parser *parser, منطقي for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  بشيا ns, name, attribute;

  /* Parse the attribute-token.  */
  إذا (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      أرجع error_mark_كلي;
    }
  name = canonicalize_attr_name (token->درج);
  c_parser_consume_token (parser);
  إذا (c_parser_next_token_is (parser, CPP_SCOPE)
      || (c_parser_next_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      إذا (c_parser_next_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      إذا (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  أرجع error_mark_كلي;
	}
      name = canonicalize_attr_name (token->درج);
      c_parser_consume_token (parser);
    }
  وإلا
    ns = NULL_بشيا;
  attribute = build_بشيا_list (build_بشيا_list (ns, name), NULL_بشيا);

  /* Parse the arguments, if any.  */
  ثابت attribute_spec *as = lookup_attribute_spec (بشيا_PURPOSE (attribute));
  إذا (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      إذا ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  أرجع error_mark_كلي;
	}
      اذهب out;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    إذا ((as && as->max_length == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_found_close (parser);
	أرجع error_mark_كلي;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    إذا (as && !attribute_ignored_p (as))
      {
	منطقي takes_identifier
	  = (ns != NULL_بشيا
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	منطقي require_string
	  = (ns == NULL_بشيا
	     && (strcmp (IDENTIFIER_POINTER (name), "deprecated") == 0
		 || strcmp (IDENTIFIER_POINTER (name), "nodiscard") == 0));
	منطقي assume_attr
	  = (ns != NULL_بشيا
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && strcmp (IDENTIFIER_POINTER (name), "assume") == 0);
	بشيا_درج (attribute)
	  = c_parser_attribute_arguments (parser, takes_identifier,
					  require_string, assume_attr, خطأ);
      }
    وإلا
      {
	إذا ((flag_openmp || flag_openmp_simd)
	    && ns
	    && is_attribute_p ("omp", ns))
	  {
	    إذا (is_attribute_p ("directive", name))
	      {
		c_parser_omp_directive_حجوجي (parser, attribute, خطأ);
		parens.skip_until_found_close (parser);
		أرجع attribute;
	      }
	    وإلا إذا (is_attribute_p ("decl", name))
	      {
		بشيا_درج (بشيا_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_حجوجي (parser, attribute, true);
		parens.skip_until_found_close (parser);
		أرجع attribute;
	      }
	    وإلا إذا (is_attribute_p ("sequence", name))
	      {
		بشيا_درج (بشيا_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_حجوجي (parser, attribute);
		parens.skip_until_found_close (parser);
		بشيا_درج (attribute) = nreverse (بشيا_درج (attribute));
		أرجع attribute;
	      }
	  }
	c_parser_balanced_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 out:
  إذا (ns == NULL_بشيا && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (شغرو_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      أرجع error_mark_كلي;
    }
  أرجع attribute;
}

ساكن بشيا
c_parser_std_attribute_list (c_parser *parser, منطقي for_tm)
{
  بشيا attributes = NULL_بشيا;
  طالما (true)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_CLOSE_SQUARE)
	اكسر;
      إذا (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  استمر;
	}
      بشيا attribute = c_parser_std_attribute (parser, for_tm);
      إذا (attribute != error_mark_كلي)
	{
	  بشيا_CHAIN (attribute) = attributes;
	  attributes = attribute;
	}
      إذا (c_parser_next_token_is_not (parser, CPP_COMMA))
	اكسر;
    }
  أرجع attributes;
}

ساكن بشيا
c_parser_std_attribute_specifier (c_parser *parser, منطقي for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    أرجع NULL_بشيا;
  إذا (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
      أرجع NULL_بشيا;
    }
  بشيا attributes;
  إذا (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      auto ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      attributes = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  وإلا
    {
      إذا (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      attributes = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  أرجع nreverse (attributes);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

ساكن منطقي
c_parser_check_balanced_raw_token_sequence (c_parser *parser, unsigned صحيح *n)
{
  طالما (true)
    {
      c_token *token = c_parser_peek_nth_token_raw (parser, *n);
      بدل (token->type)
	{
	حالة CPP_OPEN_BRACE:
	  {
	    ++*n;
	    إذا (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		إذا (token->type == CPP_CLOSE_BRACE)
		  ++*n;
		وإلا
		  أرجع خطأ;
	      }
	    وإلا
	      أرجع خطأ;
	    اكسر;
	  }

	حالة CPP_OPEN_PAREN:
	  {
	    ++*n;
	    إذا (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		إذا (token->type == CPP_CLOSE_PAREN)
		  ++*n;
		وإلا
		  أرجع خطأ;
	      }
	    وإلا
	      أرجع خطأ;
	    اكسر;
	  }

	حالة CPP_OPEN_SQUARE:
	  {
	    ++*n;
	    إذا (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		إذا (token->type == CPP_CLOSE_SQUARE)
		  ++*n;
		وإلا
		  أرجع خطأ;
	      }
	    وإلا
	      أرجع خطأ;
	    اكسر;
	  }

	حالة CPP_CLOSE_BRACE:
	حالة CPP_CLOSE_PAREN:
	حالة CPP_CLOSE_SQUARE:
	حالة CPP_EOF:
	  أرجع true;

	افتراضي:
	  ++*n;
	  اكسر;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

ساكن منطقي
c_parser_nth_token_starts_std_attributes (c_parser *parser, unsigned صحيح n)
{
  إذا (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_SQUARE
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_SQUARE))
    أرجع خطأ;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  إذا (!c_dialect_objc ())
    أرجع true;
  n += 2;
  إذا (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    أرجع خطأ;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  إذا (token->type != CPP_CLOSE_SQUARE)
    أرجع خطأ;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  أرجع token->type == CPP_CLOSE_SQUARE;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

ساكن size_t
c_parser_skip_std_attribute_spec_seq (c_parser *parser, size_t n)
{
  size_t orig_n = n;
  طالما (true)
    {
      إذا (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_SQUARE
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_SQUARE))
	{
	  unsigned صحيح m = n + 2;
	  إذا (!c_parser_check_balanced_raw_token_sequence (parser, &m))
	    أرجع orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  إذا (token->type != CPP_CLOSE_SQUARE)
	    أرجع orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  إذا (token->type != CPP_CLOSE_SQUARE)
	    أرجع orig_n;
	  n = m + 2;
	}
      وإلا
	اكسر;
    }
  أرجع n;
}

ساكن بشيا
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  بشيا attributes = NULL_بشيا;
  افعل
    {
      بشيا attrs = c_parser_std_attribute_specifier (parser, خطأ);
      attributes = chainon (attributes, attrs);
    }
  طالما (c_parser_nth_token_starts_std_attributes (parser, 1));
  أرجع attributes;
}

/* Parse a type name (C90 6.5.5, C99 6.7.6, C11 6.7.7).  ALIGNAS_OK
   says whether alignment specifiers are OK (only in cases that might
   be the type name of a compound literal).

   type-name:
     specifier-qualifier-list abstract-declarator[opt]
*/

بنية c_type_name *
c_parser_type_name (c_parser *parser, منطقي alignas_ok)
{
  بنية c_declspecs *specs = build_null_declspecs ();
  بنية c_declarator *declarator;
  بنية c_type_name *ret;
  منطقي dummy = خطأ;
  c_parser_declspecs (parser, specs, خطأ, true, true, alignas_ok, خطأ,
		      خطأ, true, cla_prefer_type);
  إذا (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      أرجع عدم;
    }
  إذا (specs->type != error_mark_كلي)
    {
      pending_xref_error ();
      finish_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      إذا (specs->typespec_kind == ctsk_tagdef)
	verify_counted_by_for_كولي_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_ABSTRACT, &dummy);
  إذا (declarator == عدم)
    أرجع عدم;
  ret = XOBNEW (&parser_obstack, بنية c_type_name);
  ret->specs = specs;
  ret->declarator = declarator;
  أرجع ret;
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

ساكن بنية c_فرچ
c_parser_initializer (c_parser *parser, بشيا decl)
{
  إذا (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    أرجع c_parser_braced_init (parser, NULL_بشيا, خطأ, عدم,
				 decl != error_mark_كلي
				 && C_DECL_VARIABLE_SIZE (decl));
  وإلا
    {
      بنية c_فرچ ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_فرچ_no_commas (parser, عدم);
      إذا (decl != error_mark_كلي && C_DECL_VARIABLE_SIZE (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.set_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      إذا (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !بشيا_STATIC (decl)
	  && ret.درج == decl
	  && !warning_enabled_at (DECL_SOURCE_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      إذا (بشيا_CODE (ret.درج) != STRING_CST
	  && (بشيا_CODE (ret.درج) != COMPOUND_LITERAL_فرچ
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_فرچ_DECL
					    (ret.درج))))
	ret = convert_lvalue_to_rvalue (loc, ret, true, true, true);
      أرجع ret;
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

ساكن بنية c_فرچ
c_parser_braced_init (c_parser *parser, بشيا type, منطقي nested_p,
		      بنية obstack *outer_obstack, منطقي varsize_p)
{
  بنية c_فرچ ret;
  بنية obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  منطقي save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = خطأ;
  منطقي zero_init_padding_bits = خطأ;
  matching_braces braces;
  braces.consume_open (parser);
  إذا (nested_p)
    {
      finish_implicit_inits (brace_loc, outer_obstack);
      تور_init_level (brace_loc, 0, &braced_init_obstack);
    }
  وإلا
    really_start_incremental_init (type);
  إذا (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      إذا (flag_isoc23)
	zero_init_padding_bits = true;
    }
  وإلا
    {
      إذا (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      طالما (true)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  إذا (parser->error)
	    اكسر;
	  إذا (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      last_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      طالما (c_parser_next_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_فرچ embed_val;
		  embed_val.درج = embed->درج;
		  embed_val.original_code = RAW_DATA_CST;
		  embed_val.original_type = integer_type_كلي;
		  set_c_فرچ_source_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, خطأ,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_next_token_is (parser,
							       CPP_COMMA));
		  last_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  وإلا
	    اكسر;
	  إذا (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    اكسر;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *next_tok = c_parser_peek_token (parser);
  إذا (next_tok->type != CPP_CLOSE_BRACE)
    {
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = عدم;
      braces.skip_until_found_close (parser);
      چرو_init_level (brace_loc, 0, &braced_init_obstack, last_init_list_comma);
      obstack_free (&braced_init_obstack, عدم);
      أرجع ret;
    }
  location_t close_loc = next_tok->location;
  c_parser_consume_token (parser);
  ret = چرو_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  إذا (zero_init_padding_bits
      && ret.درج
      && بشيا_CODE (ret.درج) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_BITS (ret.درج) = 1;
  obstack_free (&braced_init_obstack, عدم);
  set_c_فرچ_source_range (&ret, brace_loc, close_loc);
  أرجع ret;
}

/* Parse a nested initializer, including designators.  */

ساكن فراغ
c_parser_initelt (c_parser *parser, بنية obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  إذا (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      set_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->درج,
		      c_parser_peek_token (parser)->location,
		      braced_init_obstack);
      /* Use the colon as the error location.  */
      pedwarn (c_parser_peek_2nd_token (parser)->location, OPT_Wpedantic,
	       "obsolete use of designated initializer with %<:%>");
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  وإلا
    {
      /* des_seen is 0 if there have been no designators, 1 if there
	 has been a single array designator and 2 otherwise.  */
      صحيح des_seen = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      طالما (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
	     || c_parser_next_token_is (parser, CPP_DOT))
	{
	  صحيح des_prev = des_seen;
	  إذا (!des_seen)
	    des_loc = c_parser_peek_token (parser)->location;
	  إذا (des_seen < 2)
	    des_seen++;
	  إذا (c_parser_next_token_is (parser, CPP_DOT))
	    {
	      des_seen = 2;
	      c_parser_consume_token (parser);
	      إذا (c_parser_next_token_is (parser, CPP_NAME))
		{
		  set_init_label (des_loc, c_parser_peek_token (parser)->درج,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      وإلا
		{
		  بنية c_فرچ init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = عدم;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_found (parser, CPP_COMMA, عدم);
		  process_init_element (شغرو_location, init, خطأ,
					braced_init_obstack);
		  أرجع;
		}
	    }
	  وإلا
	    {
	      بنية c_فرچ first_فرچ;
	      بشيا first, second;
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
	      إذا (des_prev == 1 && c_dialect_objc ())
		{
		  des_seen = des_prev;
		  اكسر;
		}
	      إذا (des_prev == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  بشيا rec, حجوجي;
		  بنية c_فرچ mexpr;
		  c_parser_consume_token (parser);
		  إذا (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_kind
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_kind
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      بشيا id = c_parser_peek_token (parser)->درج;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      اذهب parse_message_حجوجي;
		    }
		  array_index_loc = c_parser_peek_token (parser)->location;
		  first_فرچ = c_parser_فرچ_no_commas (parser, عدم);
		  mark_exp_read (first_فرچ.درج);
		  إذا (c_parser_next_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    اذهب array_desig_after_first;
		  first = first_فرچ.درج;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = first;
		  طالما (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      بنية c_فرچ next;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      next = c_parser_فرچ_no_commas (parser, عدم);
		      next = convert_lvalue_to_rvalue (exp_loc, next,
						       true, true);
		      rec = build_compound_فرچ (comma_loc, rec, next.درج);
		    }
		parse_message_حجوجي:
		  /* Now parse the objc-message-args.  */
		  حجوجي = c_parser_objc_message_حجوجي (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					     "expected %<]%>");
		  mexpr.درج
		    = objc_build_message_فرچ (rec, حجوجي);
		  mexpr.original_code = ERROR_MARK;
		  mexpr.original_type = عدم;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  أرجع;
		}
	      c_parser_consume_token (parser);
	      array_index_loc = c_parser_peek_token (parser)->location;
	      first_فرچ = c_parser_فرچ_no_commas (parser, عدم);
	      mark_exp_read (first_فرچ.درج);
	    array_desig_after_first:
	      first_فرچ = convert_lvalue_to_rvalue (array_index_loc,
						     first_فرچ,
						     true, true);
	      first = first_فرچ.درج;
	      إذا (c_parser_next_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  second = convert_lvalue_to_rvalue (ellipsis_loc,
						     (c_parser_فرچ_no_commas
						      (parser, عدم)),
						     true, true).درج;
		  mark_exp_read (second);
		}
	      وإلا
		second = NULL_بشيا;
	      إذا (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		{
		  c_parser_consume_token (parser);
		  set_init_index (array_index_loc, first, second,
				  braced_init_obstack);
		  إذا (second)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      وإلا
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					   "expected %<]%>");
	    }
	}
      إذا (des_seen >= 1)
	{
	  إذا (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    {
	      إذا (des_seen == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      وإلا
		{
		  بنية c_فرچ init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = عدم;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_found (parser, CPP_COMMA, عدم);
		  process_init_element (شغرو_location, init, خطأ,
					braced_init_obstack);
		  أرجع;
		}
	    }
	}
    }
  c_parser_initval (parser, عدم, braced_init_obstack);
}

/* Parse a nested initializer; as c_parser_initializer but parses
   initializers within braced lists, after any designators have been
   applied.  If AFTER is not NULL then it is an Objective-C message
   expression which is the primary-expression starting the
   initializer.  */

ساكن فراغ
c_parser_initval (c_parser *parser, بنية c_فرچ *after,
		  بنية obstack * braced_init_obstack)
{
  بنية c_فرچ init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  إذا (c_parser_next_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_بشيا, true,
				 braced_init_obstack, خطأ);
  وإلا
    {
      init = c_parser_فرچ_no_commas (parser, after);
      إذا (init.درج != NULL_بشيا
	  && بشيا_CODE (init.درج) != STRING_CST
	  && (بشيا_CODE (init.درج) != COMPOUND_LITERAL_فرچ
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_فرچ_DECL
					    (init.درج))))
	init = convert_lvalue_to_rvalue (loc, init, true, true, true);
    }
  بشيا val = init.درج;
  process_init_element (loc, init, خطأ, braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  ساكن unsigned vals_to_ignore;
  إذا (vals_to_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_to_ignore;
  وإلا إذا (val
	   && بشيا_CODE (val) == INTEGER_CST
	   && بشيا_TYPE (val) == integer_type_كلي
	   && c_parser_next_token_is (parser, CPP_COMMA))
    إذا (unsigned صحيح len = c_maybe_optimize_large_byte_initializer ())
      {
	حرف buf1[64];
	unsigned صحيح i;
	gcc_checking_assert (len >= 64);
	location_t last_loc = UNKNOWN_LOCATION;
	لكل (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    إذا (tok->type != CPP_COMMA)
	      اكسر;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    إذا (tok->type != CPP_لمب
		|| بشيا_CODE (tok->درج) != INTEGER_CST
		|| بشيا_TYPE (tok->درج) != integer_type_كلي
		|| wi::neg_p (wi::to_wide (tok->درج))
		|| wi::to_widest (tok->درج) > UCHAR_MAX)
	      اكسر;
	    buf1[i] = (حرف) بشيا_to_uhwi (tok->درج);
	    إذا (i == 0)
	      loc = tok->location;
	    last_loc = tok->location;
	  }
	إذا (i < 64)
	  {
	    vals_to_ignore = i;
	    أرجع;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	إذا (tok->type == CPP_CLOSE_BRACE && len != INT_MAX)
	  len = i;
	وإلا إذا (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_لمب))
	  {
	    vals_to_ignore = i;
	    أرجع;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	unsigned صحيح max_len = 131072 - offsetof (بنية بشيا_string, str) - 1;
	unsigned صحيح orig_len = len;
	unsigned صحيح off = 0, last = 0;
	إذا (!wi::neg_p (wi::to_wide (val)) && wi::to_widest (val) <= UCHAR_MAX)
	  off = 1;
	len = MIN (len, max_len - off);
	حرف *buf2 = XNEWVEC (حرف, len + off);
	إذا (off)
	  buf2[0] = (حرف) بشيا_to_uhwi (val);
	memcpy (buf2 + off, buf1, i);
	لكل (unsigned صحيح j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	لكل (; i < len; ++i)
	  {
	    إذا (!c_parser_next_token_is (parser, CPP_COMMA))
	      اكسر;
	    tok = c_parser_peek_2nd_token (parser);
	    إذا (tok->type != CPP_لمب
		|| بشيا_CODE (tok->درج) != INTEGER_CST
		|| بشيا_TYPE (tok->درج) != integer_type_كلي
		|| wi::neg_p (wi::to_wide (tok->درج))
		|| wi::to_widest (tok->درج) > UCHAR_MAX)
	      اكسر;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    إذا (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      اكسر;
	    buf2[i + off] = (حرف) بشيا_to_uhwi (tok->درج);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    إذا (orig_len == INT_MAX
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_لمب)))
	      {
		last = 1;
		اكسر;
	      }
	    last_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_كلي (RAW_DATA_CST);
	بشيا_TYPE (val) = integer_type_كلي;
	RAW_DATA_LENGTH (val) = i;
	بشيا owner = build_string (i + off + last, buf2);
	XDELETEVEC (buf2);
	بشيا_TYPE (owner) = build_array_type_nelts (unsigned_char_type_كلي,
						    i + off + last);
	RAW_DATA_OWNER (val) = owner;
	RAW_DATA_POINTER (val) = بشيا_STRING_POINTER (owner) + off;
	init.درج = val;
	set_c_فرچ_source_range (&init, loc, last_loc);
	init.original_code = RAW_DATA_CST;
	init.original_type = integer_type_كلي;
	init.m_decimal = 0;
	process_init_element (loc, init, خطأ, braced_init_obstack);
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

ساكن بشيا
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  بشيا stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (true);
      c_end_compound_stmt (brace_loc, stmt, true);
      أرجع error_mark_كلي;
    }
  stmt = c_begin_compound_stmt (true);
  location_t end_loc = c_parser_compound_statement_nostart (parser);
  إذا (endlocp)
    *endlocp = end_loc;

  أرجع c_end_compound_stmt (brace_loc, stmt, true);
}

/* Diagnose errors related to imperfectly nested loops in an OMP
   loop construct.  This function is called when such code is seen.
   Only issue one such diagnostic no matter how much invalid
   intervening code there is in the loop.
   FIXME: maybe the location associated with the diagnostic should
   be the current parser token instead of the location of the outer loop
   nest.  */

ساكن فراغ
check_omp_intervening_code (c_parser *parser)
{
  بنية omp_for_parse_data *omp_for_parse_state = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);

  إذا (!omp_for_parse_state->in_intervening_code)
    أرجع;
  omp_for_parse_state->saw_intervening_code = true;

  /* Only diagnose errors related to perfect nesting once.  */
  إذا (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      إذا (omp_for_parse_state->code == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = true;
	}
      وإلا إذا (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = true;
	}
      وإلا إذا (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = true;
	}
      وإلا إذا (omp_for_parse_state->code == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = true;
	}
      إذا (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->fail = true;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
ساكن فراغ
add_structured_block_stmt (بشيا sl)
{
  إذا (بشيا_CODE (sl) != STATEMENT_LIST
      || !tsi_end_p (tsi_start (sl)))
    add_stmt (build1 (OMP_STRUCTURED_BLOCK, void_type_كلي, sl));
}

بنية c_omp_attribute_data
{
  vec<c_token, va_gc> *tokens;
  ثابت c_omp_directive *dir;
  c_omp_directive_kind kind;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

ساكن منطقي
c_parser_handle_statement_omp_attributes (c_parser *parser, بشيا &attrs,
					  منطقي *have_std_attrs)
{
  إذا (!flag_openmp && !flag_openmp_simd)
    أرجع خطأ;

  auto_vec<c_omp_attribute_data, 16> vd;
  صحيح cnt = 0;
  صحيح tokens = 0;
  منطقي bad = خطأ;
  لكل (بشيا *pa = &attrs; *pa; )
    إذا (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	لكل (بشيا a = بشيا_درج (*pa); a; a = بشيا_CHAIN (a))
	  {
	    بشيا d = بشيا_درج (a);
	    gcc_assert (بشيا_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    إذا (parser->omp_attrs_forbidden_p)
	      {
		error_at (first->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = خطأ;
		bad = true;
	      }
	    وإلا إذا (بشيا_PUBLIC (d))
	      {
		error_at (first->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		bad = true;
	      }
	    ثابت حرف *directive[3] = {};
	    لكل (صحيح i = 0; i < 3; i++)
	      {
		بشيا id = NULL_بشيا;
		إذا (first + i == last)
		  اكسر;
		إذا (first[i].type == CPP_NAME)
		  id = first[i].درج;
		وإلا إذا (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(صحيح) first[i].keyword];
		وإلا
		  اكسر;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    ثابت c_omp_directive *dir = عدم;
	    إذا (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    إذا (dir == عدم)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  بشيا_PUBLIC (d) ? "omp::decl" : "omp::directive");
		استمر;
	      }
	    c_omp_directive_kind kind = dir->kind;
	    إذا (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		إذا (directive[1]
		    && (strcmp (directive[1], "depend") == 0
			|| strcmp (directive[1], "doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
		وإلا إذا (first + 2 < last
			 && first[1].type == CPP_COMMA
			 && first[2].type == CPP_NAME
			 && (strcmp (IDENTIFIER_POINTER (first[2].درج),
				     "depend") == 0
			     || strcmp (IDENTIFIER_POINTER (first[2].درج),
					"doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
	      }
	    وإلا إذا (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		صحيح paren_depth = 0;
		لكل (صحيح i = 1; first + i < last; i++)
		  إذا (first[i].type == CPP_OPEN_PAREN)
		    paren_depth++;
		  وإلا إذا (first[i].type == CPP_CLOSE_PAREN)
		    paren_depth--;
		  وإلا إذا (paren_depth == 0
			   && first + i + 2 < last
			   && first[i].type == CPP_NAME
			   && first[i + 1].type == CPP_OPEN_PAREN
			   && first[i + 2].type == CPP_NAME
			   && !strcmp (IDENTIFIER_POINTER (first[i].درج),
				       "at")
			   && !strcmp (IDENTIFIER_POINTER (first[i
								 + 2].درج),
				       "execution"))
		    {
		      kind = C_OMP_DIR_STANDALONE;
		      اكسر;
		    }
	      }
	    c_omp_attribute_data v = { toks, dir, kind };
	    vd.safe_تور (v);
	    إذا (flag_openmp || dir->simd)
	      tokens += (last - first) + 1;
	  }
	c_omp_attribute_data v = {};
	vd.safe_تور (v);
	*pa = بشيا_CHAIN (*pa);
      }
    وإلا
      pa = &بشيا_CHAIN (*pa);

  إذا (bad)
    {
    fail:
      إذا (have_std_attrs && attrs == عدم)
	*have_std_attrs = خطأ;
      أرجع خطأ;
    }

  unsigned صحيح i;
  c_omp_attribute_data *v;
  c_omp_attribute_data *construct_seen = nullptr;
  c_omp_attribute_data *standalone_seen = nullptr;
  c_omp_attribute_data *prev_standalone_seen = nullptr;
  FOR_EACH_VEC_ELT (vd, i, v)
    إذا (v->tokens)
      {
	إذا (v->kind == C_OMP_DIR_CONSTRUCT && !construct_seen)
	  construct_seen = v;
	وإلا إذا (v->kind == C_OMP_DIR_STANDALONE && !standalone_seen)
	  standalone_seen = v;
      }
    وإلا
      {
	إذا (standalone_seen && !prev_standalone_seen)
	  {
	    prev_standalone_seen = standalone_seen;
	    standalone_seen = nullptr;
	  }
      }

  إذا (cnt > 1 && construct_seen)
    {
      error_at ((*construct_seen->tokens)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      اذهب fail;
    }
  إذا (cnt > 1 && standalone_seen && prev_standalone_seen)
    {
      error_at ((*standalone_seen->tokens)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      اذهب fail;
    }

  إذا (prev_standalone_seen)
    standalone_seen = prev_standalone_seen;
  إذا (standalone_seen
      && !c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_seen->tokens->address ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      اذهب fail;
    }
  إذا (cnt && c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      تعداد pragma_kind kind = token->pragma_kind;
      إذا (kind >= PRAGMA_OMP__START_ && kind <= PRAGMA_OMP__LAST_)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  اذهب fail;
	}
    }

  إذا (!tokens)
    أرجع خطأ;

  unsigned صحيح tokens_avail = parser->tokens_avail;

  tokens++;
  vec<c_token, va_gc> *toks = عدم;
  vec_safe_reserve (toks, tokens, true);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      إذا (!v->tokens)
	استمر;
      إذا (!flag_openmp && !v->dir->simd)
	استمر;
      c_token *first = v->tokens->address ();
      c_token *last = first + v->tokens->length ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_kind = pragma_kind (v->dir->id);
      tok.location = first->location;
      toks->quick_تور (tok);
      طالما (++first < last)
	toks->quick_تور (*first);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = last[-1].location;
      toks->quick_تور (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->last ().location;
  toks->quick_تور (tok);

  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = tokens;
  أرجع true;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

ساكن فراغ
c_parser_handle_directive_omp_attributes (بشيا &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  إذا (!flag_openmp && !flag_openmp_simd)
    أرجع;

  لكل (بشيا *pa = &attrs; *pa; )
    إذا (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	صحيح cnt = 0;
	لكل (بشيا *pa2 = &بشيا_درج (*pa); *pa2; )
	  {
	    بشيا a = *pa2;
	    بشيا d = بشيا_درج (a);
	    gcc_assert (بشيا_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    ثابت حرف *directive[3] = {};
	    لكل (صحيح i = 0; i < 3; i++)
	      {
		بشيا id = NULL_بشيا;
		إذا (first + i == last)
		  اكسر;
		إذا (first[i].type == CPP_NAME)
		  id = first[i].درج;
		وإلا إذا (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(صحيح) first[i].keyword];
		وإلا
		  اكسر;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    ثابت c_omp_directive *dir = عدم;
	    إذا (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    إذا (dir == عدم)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  بشيا_PUBLIC (d) ? "omp::decl" : "omp::directive");
		*pa2 = بشيا_CHAIN (a);
	      }
	    وإلا إذا (dir->id == PRAGMA_OMP_DECLARE
		     && (strcmp (directive[1], "simd") == 0
			 || strcmp (directive[1], "variant") == 0))
	      {
		إذا (pragma_clauses)
		  {
		    error_at (first->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    لكل (pa = &attrs; *pa; )
		      إذا (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = بشيا_CHAIN (*pa);
		      وإلا
			pa = &بشيا_CHAIN (*pa);
		    أرجع;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->length ()
				       + toks->length () + 2);
		لكل (++first; first < last; ++first)
		  attr_clauses->quick_تور (*first);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = last[-1].location;
		attr_clauses->quick_تور (tok);
		*pa2 = بشيا_CHAIN (a);
	      }
	    وإلا
	      pa2 = &بشيا_CHAIN (a);
	  }
	إذا (cnt && بشيا_درج (*pa) == NULL_بشيا)
	  *pa = بشيا_CHAIN (*pa);
	وإلا
	  pa = &بشيا_CHAIN (*pa);
      }
    وإلا
      pa = &بشيا_CHAIN (*pa);
  إذا (attr_clauses->length ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->last ().location;
      attr_clauses->quick_تور (tok);
      attr_clauses->quick_تور (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

ساكن بشيا
c_parser_handle_musttail (c_parser *parser, بشيا std_attrs, attr_state &attr)
{
  إذا (c_parser_next_token_is_keyword (parser, RID_RETURN))
    {
      إذا (بشيا a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  لكل (; a; a = lookup_attribute ("gnu", "musttail", بشيا_CHAIN (a)))
	    إذا (بشيا_درج (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = true;
	}
      إذا (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = true;
	}
    }
  أرجع std_attrs;
}

/* Return a statement before optional series of LABEL_EXPR/CASE_LABEL_EXPRs.
   Instead of collecting vectors of labels before each stmt just in case
   the statement would be iteration or switch statement for named loops,
   we just remember last emitted statement and let the iteration/switch
   statement search backwards in cur_stmt_list until that stmt for loop
   names if any.  */

ساكن بشيا
get_before_labels ()
{
  إذا (!building_stmt_list_p ())
    أرجع NULL_بشيا;
  بشيا_stmt_iterator tsi = tsi_last (cur_stmt_list);
  إذا (tsi_end_p (tsi))
    أرجع NULL_بشيا;
  أرجع tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

ساكن location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  منطقي last_stmt = خطأ;
  منطقي last_label = خطأ;
  منطقي save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  بنية omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  منطقي in_omp_loop_block
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : خطأ;
  بشيا sl = NULL_بشيا;
  attr_state astate = {};

  إذا (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      add_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      أرجع endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  إذا (in_omp_loop_block)
    sl = تور_stmt_list ();

  mark_valid_location_for_stdc_pragma (true);
  إذا (c_parser_next_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (خطأ);
      إذا (in_omp_loop_block)
	check_omp_intervening_code (parser);
      طالما (c_parser_next_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  طالما (true)
	    {
	      بشيا label;
	      إذا (c_parser_next_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  اكسر;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->درج);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      add_stmt (build_stmt (label_loc, DECL_فرچ, label));
	      c_parser_consume_token (parser);
	      إذا (c_parser_next_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      وإلا
		اكسر;
	    }
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  إذا (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      أرجع endloc;
    }
  بشيا before_labels = get_before_labels ();
  طالما (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_point_location_if_in_system_header (loc);

      منطقي want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : خطأ);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      إذا (in_omp_loop_block && !last_label)
	{
	  بشيا_code code = omp_for_parse_state->code;
	  إذا (want_nested_loop
	      && c_parser_omp_next_tokens_can_be_canon_loop (parser, code,
							     خطأ))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      add_structured_block_stmt (چرو_stmt_list (sl));
	      omp_for_parse_state->depth++;
	      add_stmt (c_parser_omp_loop_nest (parser, عدم));
	      omp_for_parse_state->depth--;
	      sl = تور_stmt_list ();
	      parser->error = خطأ;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      استمر;
	    }
	  وإلا إذا (want_nested_loop
		   && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      بشيا pre_sl = چرو_stmt_list (sl);
	      بشيا nested_sl = تور_stmt_list ();
	      mark_valid_location_for_stdc_pragma (خطأ);
	      c_parser_statement_after_labels (parser, عدم, NULL_بشيا);
	      nested_sl = چرو_stmt_list (nested_sl);
	      إذا (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_code (parser);
		  sl = تور_stmt_list ();
		  add_stmt (pre_sl);
		  add_stmt (nested_sl);
		}
	      وإلا
		{
		  /* It contains the nested loop.  */
		  add_structured_block_stmt (pre_sl);
		  add_stmt (nested_sl);
		  sl = تور_stmt_list ();
		}
	      parser->error = خطأ;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      استمر;
	    }
	  وإلا إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      /* Prior to implementing the OpenMP 5.1 syntax for canonical
		 loop form, GCC used to accept an empty statements that
		 would now be flagged as intervening code.  Continue to
		 do that, as an extension.  */
	      /* FIXME:  Maybe issue a warning or something here?  */
	      c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
	      استمر;
	    }
	}

      /* Standard attributes may start a label, statement or declaration.  */
      منطقي have_std_attrs
	= c_parser_nth_token_starts_std_attributes (parser, 1);
      بشيا std_attrs = NULL_بشيا;
      إذا (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      إذا (c_parser_next_token_is_keyword (parser, RID_CASE)
	  || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  إذا (c_parser_next_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  وإلا
	    label_loc = c_parser_peek_token (parser)->location;
	  last_label = true;
	  last_stmt = خطأ;
	  mark_valid_location_for_stdc_pragma (خطأ);
	  إذا (in_omp_loop_block)
	    check_omp_intervening_code (parser);
	  c_parser_label (parser, std_attrs);
	}
      وإلا إذا (c_parser_next_tokens_start_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_attributes
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_next_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = true)))
	{
	  إذا (last_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  إذا (in_omp_loop_block)
	    {
	      check_omp_intervening_code (parser);
	      omp_for_parse_state->want_nested_loop = خطأ;
	    }
	  mark_valid_location_for_stdc_pragma (خطأ);
	  منطقي fallthru_attr_p = خطأ;
	  c_parser_declaration_or_fndef (parser, true, !have_std_attrs,
					 true, true, true, خطأ, عدم,
					 عدم, have_std_attrs, std_attrs,
					 عدم, &fallthru_attr_p);

	  إذا (in_omp_loop_block)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  إذا (last_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  last_stmt = fallthru_attr_p;
	  last_label = خطأ;
	  before_labels = get_before_labels ();
	}
      وإلا إذا (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  If standard attributes have already
	     been seen, it must start a statement, not a declaration,
	     but standard attributes starting a declaration may appear
	     after __extension__.  */
	  طالما (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  إذا (!have_std_attrs
	      && (c_parser_next_tokens_start_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_attributes (parser, 2)))
	    {
	      صحيح ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      last_label = خطأ;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      إذا (in_omp_loop_block)
		{
		  check_omp_intervening_code (parser);
		  omp_for_parse_state->want_nested_loop = خطأ;
		}
	      mark_valid_location_for_stdc_pragma (خطأ);
	      c_parser_declaration_or_fndef (parser, true, true, true, true,
					     true, خطأ);
	      إذا (in_omp_loop_block)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      إذا (last_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      last_stmt = خطأ;
	      before_labels = get_before_labels ();
	    }
	  وإلا
	    اذهب statement;
	}
      وإلا إذا (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  إذا (have_std_attrs && !parser->in_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  وإلا إذا (std_attrs)
	    c_warn_unused_attributes (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  إذا (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = خطأ;
	  إذا (c_parser_pragma (parser,
			       last_label ? pragma_stmt : pragma_compound,
			       عدم, before_labels))
	    {
	      last_label = خطأ;
	      last_stmt = true;
	      إذا (omp_for_parse_state)
		check_omp_intervening_code (parser);
	    }
	  إذا (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      وإلا إذا (c_parser_next_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  أرجع c_parser_peek_token (parser)->location;
	}
      وإلا إذا (c_parser_next_token_is_keyword (parser, RID_ELSE))
        {
          إذا (parser->in_if_block)
            {
	      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	      error_at (loc, "expected %<}%> before %<else%>");
	      أرجع c_parser_peek_token (parser)->location;
            }
          وإلا
            {
              error_at (loc, "%<else%> without a previous %<if%>");
              c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
              استمر;
            }
        }
      وإلا
	{
	statement:
	  c_warn_unused_attributes (std_attrs);
	  last_label = خطأ;
	  last_stmt = true;
	  mark_valid_location_for_stdc_pragma (خطأ);
	  إذا (!omp_for_parse_state)
	    c_parser_statement_after_labels (parser, عدم, before_labels,
					     عدم, astate);
	  وإلا
	    {
	      /* In canonical loop nest form, nested loops can only appear
		 directly, or in a directly nested compound statement.  We
		 already took care of those cases above, so now we have
		 something else.  This statement and everything inside
		 it must be intervening code.  */
	      omp_for_parse_state->want_nested_loop = خطأ;
	      check_omp_intervening_code (parser);
	      c_parser_statement_after_labels (parser, عدم, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = خطأ;
      astate.reset ();
    }
  إذا (last_label)
    pedwarn_c11 (label_loc, OPT_Wfree_labels,
		 "label at end of compound statement");
  location_t endloc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  /* Restore the value we started with.  */
  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);

  /* Package leftover intervening code, or the whole contents of the
     compound statement if we were looking for a nested loop in an OMP_FOR
     construct and didn't find one.  */
  إذا (sl)
    {
      sl = چرو_stmt_list (sl);
      إذا (omp_for_parse_state->want_nested_loop)
	add_stmt (sl);
      وإلا
	add_structured_block_stmt (sl);
    }
  أرجع endloc;
}

/* Parse all consecutive labels, possibly preceded by standard
   attributes.  In this context, a statement is required, not a
   declaration, so attributes must be followed by a statement that is
   not just a semicolon.  Returns an attr_state.  */

ساكن attr_state
c_parser_all_labels (c_parser *parser)
{
  attr_state attr = {};
  منطقي have_std_attrs;
  بشيا std_attrs = عدم;
  إذا ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  طالما (c_parser_next_token_is_keyword (parser, RID_CASE)
	 || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = عدم;
      إذا ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  إذا (std_attrs
      && (!c_parser_handle_statement_omp_attributes (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      إذا (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_unused_attributes (std_attrs);
    }
  وإلا إذا (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  أرجع attr;
}


/* Information used while parsing an OpenMP metadirective.  */
بنية omp_metadirective_parse_data {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<بشيا> * GTY((skip)) body_labels;
  unsigned صحيح region_لمب;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
ساكن بشيا
mangle_metadirective_region_label (c_parser *parser, بشيا name)
{
  إذا (parser->omp_metadirective_state->body_labels->contains (name))
    {
      ثابت حرف *old_name = IDENTIFIER_POINTER (name);
      حرف *new_name = (حرف *) XALLOCAVEC (حرف, strlen (old_name) + 32);
      sprintf (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_لمب);
      أرجع get_identifier (new_name);
    }
  أرجع name;
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
ساكن فراغ
c_parser_label (c_parser *parser, بشيا std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  بشيا label = NULL_بشيا;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  منطقي fallthrough_p = c_parser_peek_token (parser)->flags & PREV_FALLTHROUGH;

  إذا (c_parser_next_token_is_keyword (parser, RID_CASE))
    {
      بشيا exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_to_rvalue (loc1,
				       c_parser_فرچ_no_commas (parser, عدم),
				       true, true).درج;
      إذا (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_بشيا, std_attrs);
	}
      وإلا إذا (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_to_rvalue (loc1,
					   c_parser_فرچ_no_commas (parser,
								    عدم),
					   true, true).درج;
	  إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      وإلا
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  وإلا إذا (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_بشيا, NULL_بشيا, std_attrs);
    }
  وإلا
    {
      بشيا name = c_parser_peek_token (parser)->درج;
      بشيا tlab;
      بشيا attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_attributes (parser);
      إذا (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      إذا (tlab)
	{
	  decl_attributes (&tlab, attrs, 0);
	  decl_attributes (&tlab, std_attrs, 0);
	  label = add_stmt (build_stmt (loc1, LABEL_فرچ, tlab));
	}
      إذا (attrs
	  && c_parser_next_tokens_start_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  إذا (label)
    {
      إذا (بشيا_CODE (label) == LABEL_فرچ)
	FALLTHROUGH_LABEL_P (LABEL_فرچ_LABEL (label)) = fallthrough_p;
      وإلا
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

ساكن فراغ
c_parser_statement (c_parser *parser, منطقي *if_p, location_t *loc_after_labels)
{
  بشيا before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  إذا (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = خطأ;
  c_parser_statement_after_labels (parser, if_p, before_labels, عدم, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

ساكن بشيا
c_parser_bc_name (c_parser *parser, منطقي is_break)
{
  إذا (!c_parser_next_token_is (parser, CPP_NAME))
    أرجع NULL_بشيا;

  c_token *tok = c_parser_peek_token (parser);
  بشيا label = c_finish_bc_name (tok->location, tok->درج, is_break);
  c_parser_consume_token (parser);
  أرجع label;
}

/* Parse a statement, other than a labeled statement.  CHAIN is a vector
   of if-else-if conditions.  All labels and standard attributes have
   been parsed in the caller.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  ASTATE is an earlier parsed attribute state.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ساكن فراغ
c_parser_statement_after_labels (c_parser *parser, منطقي *if_p,
				 بشيا before_labels,
				 vec<بشيا> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  بشيا stmt = NULL_بشيا;
  منطقي in_if_block = parser->in_if_block;
  parser->in_if_block = خطأ;
  إذا (if_p != عدم)
    *if_p = خطأ;

  إذا (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    add_debug_begin_stmt (loc);

 restart:
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_OPEN_BRACE:
      add_stmt (c_parser_compound_statement (parser));
      اكسر;
    حالة CPP_KEYWORD:
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_IF:
	  c_parser_if_statement (parser, if_p, chain);
	  اكسر;
	حالة RID_SWITCH:
	  c_parser_switch_statement (parser, if_p, before_labels);
	  اكسر;
	حالة RID_WHILE:
	  c_parser_while_statement (parser, خطأ, 0, خطأ, if_p, before_labels);
	  اكسر;
	حالة RID_DO:
	  c_parser_do_statement (parser, خطأ, 0, خطأ, before_labels);
	  اكسر;
	حالة RID_FOR:
	  c_parser_for_statement (parser, خطأ, 0, خطأ, if_p, before_labels);
	  اكسر;
	حالة RID_GOTO:
	  c_parser_consume_token (parser);
	  إذا (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      بشيا name = c_parser_peek_token (parser)->درج;
	      إذا (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_finish_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  وإلا إذا (c_parser_next_token_is (parser, CPP_MULT))
	    {
	      بنية c_فرچ val;

	      c_parser_consume_token (parser);
	      val = c_parser_expression (parser);
	      val = convert_lvalue_to_rvalue (loc, val, خطأ, true);
	      stmt = c_finish_goto_ptr (loc, val);
	    }
	  وإلا
	    c_parser_error (parser, "expected identifier or %<*%>");
	  اذهب expect_semicolon;
	حالة RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_continue_label, خطأ,
				   c_parser_bc_name (parser, خطأ));
	  اذهب expect_semicolon;
	حالة RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_break_label, true,
				   c_parser_bc_name (parser, true));
	  اذهب expect_semicolon;
	حالة RID_RETURN:
	  c_parser_consume_token (parser);
	  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_finish_return (loc, NULL_بشيا, NULL_بشيا,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      بنية c_فرچ فرچ = c_parser_expression_conv (parser);
	      mark_exp_read (فرچ.درج);
	      stmt = c_finish_return (فرچ_LOC_OR_LOC (فرچ.درج, xloc),
				      فرچ.درج, فرچ.original_type,
				      astate.musttail_p);
	      اذهب expect_semicolon;
	    }
	  اكسر;
	حالة RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  اكسر;
	حالة RID_TRANSACTION_ATOMIC:
	حالة RID_TRANSACTION_RELAXED:
	  stmt = c_parser_transaction (parser,
	      c_parser_peek_token (parser)->keyword);
	  اكسر;
	حالة RID_TRANSACTION_CANCEL:
	  stmt = c_parser_transaction_cancel (parser);
	  اذهب expect_semicolon;
	حالة RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_بشيا);
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    {
	      بنية c_فرچ فرچ = c_parser_expression (parser);
	      فرچ = convert_lvalue_to_rvalue (loc, فرچ, خطأ, خطأ);
	      فرچ.درج = c_fully_fold (فرچ.درج, خطأ, عدم);
	      stmt = objc_build_throw_stmt (loc, فرچ.درج);
	      اذهب expect_semicolon;
	    }
	  اكسر;
	حالة RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_finally_statement (parser);
	  اكسر;
	حالة RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  اكسر;
	حالة RID_ATTRIBUTE:
	  {
	    /* Allow '__attribute__((fallthrough));' or
	       '__attribute__((assume(cond)));' or
	       '__attribute__((musttail))) return'.  */
	    بشيا attrs = c_parser_gnu_attributes (parser);
	    منطقي has_assume = lookup_attribute ("assume", attrs);
	    إذا (has_assume)
	      {
		إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, true);
		وإلا
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<assume%> attribute not followed by %<;%>");
		    has_assume = خطأ;
		  }
	      }
	    gcc_assert (!astate.musttail_p);
	    attrs = c_parser_handle_musttail (parser, attrs, astate);
	    إذا (astate.musttail_p)
	      {
		إذا (attrs)
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		اذهب restart;
	      }
	    إذا (attribute_fallthrough_p (attrs))
	      {
		إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  {
		    بشيا fn = build_call_فرچ_internal_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_كلي, 0);
		    add_stmt (fn);
		    /* Eat the ';'.  */
		    c_parser_consume_token (parser);
		  }
		وإلا
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<fallthrough%> attribute not followed "
				"by %<;%>");
		  }
	      }
	    وإلا إذا (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    وإلا إذا (attrs != NULL_بشيا)
	      {
		auto_urlify_attributes sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    اكسر;
	  }
	افتراضي:
	  اذهب فرچ_stmt;
	}
      اكسر;
    حالة CPP_SEMICOLON:
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_CLOSE_PAREN:
    حالة CPP_CLOSE_SQUARE:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_PRAGMA:
      إذا (!c_parser_pragma (parser, pragma_stmt, if_p, before_labels))
        اذهب restart;
      اكسر;
    افتراضي:
    فرچ_stmt:
      stmt = c_finish_فرچ_stmt (loc, c_parser_expression_conv (parser).درج);
    expect_semicolon:
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      اكسر;
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
  إذا (فرچ_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_set_فرچ_location (stmt, loc);

  parser->in_if_block = in_if_block;
}

/* Parse the condition from an if, do, while or for statements.  */

ساكن بشيا
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  بشيا cond;
  cond = c_parser_expression_conv (parser).درج;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, خطأ, عدم);
  إذا (warn_sequence_point)
    verify_sequence_points (cond);
  أرجع cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

ساكن بشيا
c_parser_paren_condition (c_parser *parser)
{
  بشيا cond;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع error_mark_كلي;
  cond = c_parser_condition (parser);
  parens.skip_until_found_close (parser);
  أرجع cond;
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

ساكن c_فرچ
c_parser_selection_header (c_parser *parser, منطقي switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_فرچ فرچ;
  منطقي parse_فرچ = true;
  بشيا std_attrs;
  منطقي have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  إذا (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  وإلا
    std_attrs = NULL_بشيا;
  إذا (c_parser_next_tokens_start_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      فرچ.درج
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/خطأ,
					 /*static_assert_ok=*/خطأ,
					 /*empty_ok=*/خطأ,
					 /*nested=*/true,
					 /*start_attr_ok=*/true,
					 /*simple_ok=*/true,
					 /*objc_foreach_object_decl=*/nullptr,
					 /*omp_declare_simd_clauses=*/nullptr,
					 have_std_attrs,
					 std_attrs);
      إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      وإلا
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  إذا (!فرچ.درج)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      فرچ.original_type = error_mark_كلي;
	      فرچ.set_error ();
	      أرجع فرچ;
	    }
	  parse_فرچ = خطأ;
	}
      إذا (فرچ.درج)
	{
	  فرچ.original_type = بشيا_TYPE (فرچ.درج);
	  فرچ = convert_lvalue_to_rvalue (loc, فرچ, /*convert_p=*/true,
					   /*read_p=*/true);
	}
    }
  وإلا إذا (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      فرچ.original_type = error_mark_كلي;
      فرچ.set_error ();
      أرجع فرچ;
    }

  إذا (parse_فرچ)
    فرچ = c_parser_expression_conv (parser);
  إذا (!switch_p)
    {
      فرچ.درج = c_objc_common_truthvalue_conversion (loc, فرچ.درج);
      فرچ.درج = c_fully_fold (فرچ.درج, خطأ, عدم);
      إذا (warn_sequence_point)
	verify_sequence_points (فرچ.درج);
    }
  أرجع فرچ;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

ساكن بشيا
c_parser_paren_selection_header (c_parser *parser)
{
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع error_mark_كلي;
  بشيا cond = c_parser_selection_header (parser, /*switch_p=*/خطأ).درج;
  parens.skip_until_found_close (parser);
  أرجع cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ساكن بشيا
c_parser_c99_block_statement (c_parser *parser, منطقي *if_p,
			      location_t *loc_after_labels)
{
  بشيا block = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  أرجع c_end_compound_stmt (loc, block, flag_isoc99);
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

ساكن بشيا
c_parser_if_body (c_parser *parser, منطقي *if_p,
		  ثابت token_indent_info &if_tinfo)
{
  بشيا block = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  بشيا before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
      إذا (!c_parser_next_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  وإلا إذا (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    add_stmt (c_parser_compound_statement (parser));
  وإلا
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, عدم, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, next_tinfo);
  إذا (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    if_tinfo.location, RID_IF);

  أرجع c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

ساكن بشيا
c_parser_else_body (c_parser *parser, ثابت token_indent_info &else_tinfo,
		    vec<بشيا> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  بشيا block = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  بشيا before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      warning_at (loc,
		  OPT_Wempty_body,
	         "suggest braces around empty body in an %<else%> statement");
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
    }
  وإلا
    {
      إذا (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, عدم, before_labels, chain, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, next_tinfo);
  إذا (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  أرجع c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse an if statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   if-statement:
     if ( selection-header ) statement
     if ( selection-header ) statement else statement

   CHAIN is a vector of if-else-if conditions.
   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ساكن فراغ
c_parser_if_statement (c_parser *parser, منطقي *if_p, vec<بشيا> *chain)
{
  بشيا block;
  location_t loc;
  بشيا cond;
  منطقي nested_if = خطأ;
  بشيا first_body, second_body;
  منطقي in_if_block;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_IF));
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

  إذا (warn_duplicated_cond)
    warn_duplicated_cond_add_or_warn (فرچ_LOCATION (cond), cond, &chain);

  إذا (c_parser_next_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      إذا (warn_duplicated_cond)
	{
	  إذا (c_parser_next_token_is_keyword (parser, RID_IF)
	      && chain == عدم)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = جديد vec<بشيا> ();
	      إذا (!CONSTANT_CLASS_P (cond) && !بشيا_SIDE_EFFECTS (cond))
		chain->safe_تور (cond);
	    }
	  وإلا إذا (!c_parser_next_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      second_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      إذا (if_p != عدم)
	*if_p = true;
    }
  وإلا
    {
      second_body = NULL_بشيا;

      /* Diagnose an ambiguous else if if-then-else is nested inside
	 if-then.  */
      إذا (nested_if)
	warning_at (loc, OPT_Wdangling_else,
		    "suggest explicit braces to avoid ambiguous %<else%>");

      إذا (warn_duplicated_cond)
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

ساكن فراغ
c_parser_switch_statement (c_parser *parser, منطقي *if_p, بشيا before_labels)
{
  بنية c_فرچ ce;
  بشيا block, فرچ, body;
  unsigned حرف save_in_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  بشيا switch_name;
  صحيح لمب_names = c_get_loop_names (before_labels, true, &switch_name);
  block = c_begin_compound_stmt (flag_isoc99);
  منطقي explicit_cast_p = خطأ;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = true;
      ce = c_parser_selection_header (parser, /*switch_p=*/true);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_to_rvalue (switch_cond_loc, ce, true, true);
      فرچ = ce.درج;
      /* ??? expr has no valid location?  */
      parens.skip_until_found_close (parser);
    }
  وإلا
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      فرچ = error_mark_كلي;
      ce.original_type = error_mark_كلي;
    }
  بشيا stmt
    = c_start_switch (switch_loc, switch_cond_loc, فرچ, explicit_cast_p,
		      switch_name);
  save_in_statement = in_statement;
  in_statement |= IN_SWITCH_STMT;
  إذا (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  وإلا
    in_statement &= ~IN_NAMED_STMT;
  location_t loc_after_labels;
  منطقي open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  location_t next_loc = c_parser_peek_token (parser)->location;
  إذا (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, next_loc, switch_loc,
				    RID_SWITCH);
  c_finish_switch (body, ce.original_type);
  in_statement = save_in_statement;
  إذا (لمب_names)
    {
      إذا (!C_DECL_LOOP_SWITCH_NAME_USED (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_بشيا;
      وإلا
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_names (لمب_names);
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

ساكن فراغ
c_parser_while_statement (c_parser *parser, منطقي ivdep, unsigned short unroll,
			  منطقي novector, منطقي *if_p, بشيا before_labels)
{
  بشيا block, cond, body;
  unsigned حرف save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  بشيا loop_name;
  صحيح لمب_names = c_get_loop_names (before_labels, خطأ, &loop_name);

  إذا (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = true;
    }

  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  إذا (ivdep && cond != error_mark_كلي)
    cond = build3 (ANNOTATE_فرچ, بشيا_TYPE (cond), cond,
		   build_int_cst (integer_type_كلي,
				  annot_فرچ_ivdep_kind),
		   integer_zero_كلي);
  إذا (unroll && cond != error_mark_كلي)
    cond = build3 (ANNOTATE_فرچ, بشيا_TYPE (cond), cond,
		   build_int_cst (integer_type_كلي,
				  annot_فرچ_unroll_kind),
		   build_int_cst (integer_type_كلي, unroll));
  إذا (novector && cond != error_mark_كلي)
    cond = build3 (ANNOTATE_فرچ, بشيا_TYPE (cond), cond,
		   build_int_cst (integer_type_كلي,
				  annot_فرچ_no_vector_kind),
		   integer_zero_كلي);
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  إذا (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  منطقي open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  إذا (loop_name && !C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
    loop_name = NULL_بشيا;
  add_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_بشيا,
			NULL_بشيا));
  add_stmt (c_end_compound_stmt (loc, block, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  إذا (لمب_names)
    c_release_loop_names (لمب_names);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, next_tinfo);

  إذا (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    while_tinfo.location, RID_WHILE);

  in_statement = save_in_statement;
}

/* Parse a do statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   do-statement:
     do statement while ( expression ) ;

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ساكن فراغ
c_parser_do_statement (c_parser *parser, منطقي ivdep, unsigned short unroll,
		       منطقي novector, بشيا before_labels)
{
  بشيا block, cond, body;
  unsigned حرف save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_DO));
  بشيا loop_name;
  صحيح لمب_names = c_get_loop_names (before_labels, خطأ, &loop_name);

  إذا (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = true;
    }

  c_parser_consume_token (parser);
  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  إذا (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  body = c_parser_c99_block_statement (parser, عدم);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  in_statement = save_in_statement;
  إذا (لمب_names)
    {
      إذا (!C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
	loop_name = NULL_بشيا;
      c_release_loop_names (لمب_names);
    }
  cond = c_parser_paren_condition (parser);
  إذا (ivdep && cond != error_mark_كلي)
    cond = build3 (ANNOTATE_فرچ, بشيا_TYPE (cond), cond,
		   build_int_cst (integer_type_كلي,
				  annot_فرچ_ivdep_kind),
		   integer_zero_كلي);
  إذا (unroll && cond != error_mark_كلي)
    cond = build3 (ANNOTATE_فرچ, بشيا_TYPE (cond), cond,
		   build_int_cst (integer_type_كلي,
				  annot_فرچ_unroll_kind),
 		   build_int_cst (integer_type_كلي, unroll));
  إذا (novector && cond != error_mark_كلي)
    cond = build3 (ANNOTATE_فرچ, بشيا_TYPE (cond), cond,
		   build_int_cst (integer_type_كلي,
				  annot_فرچ_no_vector_kind),
		   integer_zero_كلي);
  إذا (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
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

ساكن فراغ
c_parser_for_statement (c_parser *parser, منطقي ivdep, unsigned short unroll,
			منطقي novector, منطقي *if_p, بشيا before_labels)
{
  بشيا block, cond, incr, body;
  unsigned حرف save_in_statement;
  بشيا save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  بشيا object_expression;
  /* Silence the bogus uninitialized warning.  */
  بشيا collection_expression = عدم;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  منطقي is_foreach_statement = خطأ;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  بشيا loop_name;
  صحيح لمب_names = c_get_loop_names (before_labels, خطأ, &loop_name);

  إذا (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = true;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  block = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_كلي;
  incr = error_mark_كلي;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_expression = error_mark_كلي;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = خطأ;
	  c_parser_consume_token (parser);
	  c_finish_فرچ_stmt (loc, NULL_بشيا);
	}
      وإلا إذا (c_parser_next_tokens_start_declaration (parser)
	       || c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, true, true, true, true, true,
					 خطأ, &object_expression);
	  parser->objc_could_be_foreach_context = خطأ;

	  إذا (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = true;
	      إذا (check_for_loop_decls (for_loc, true) == NULL_بشيا)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  وإلا
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      وإلا إذا (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  طالما (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  إذا (c_parser_next_tokens_start_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_attributes (parser, 2))
	    {
	      صحيح ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, true, true, true, true,
					     true, خطأ, &object_expression);
	      parser->objc_could_be_foreach_context = خطأ;

	      restore_extension_diagnostics (ext);
	      إذا (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = true;
		  إذا (check_for_loop_decls (for_loc, true) == NULL_بشيا)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      وإلا
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  وإلا
	    اذهب init_فرچ;
	}
      وإلا
	{
	init_فرچ:
	  {
	    بنية c_فرچ ce;
	    بشيا init_expression;
	    ce = c_parser_expression (parser);
	    init_expression = ce.درج;
	    parser->objc_could_be_foreach_context = خطأ;
	    إذا (c_parser_next_token_is_keyword (parser, RID_IN))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = true;
		إذا (! lvalue_p (init_expression))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_expression
		  = c_fully_fold (init_expression, خطأ, عدم);
	      }
	    وإلا
	      {
		ce = convert_lvalue_to_rvalue (loc, ce, true, خطأ);
		init_expression = ce.درج;
		c_finish_فرچ_stmt (loc, init_expression);
		c_parser_skip_until_found (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      إذا (!is_foreach_statement)
	{
	  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      إذا (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_كلي;
		}
	      وإلا إذا (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_كلي;
		}
	      وإلا
		{
		  c_parser_consume_token (parser);
		  cond = NULL_بشيا;
		}
	    }
	  وإلا
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_found (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  إذا (ivdep && cond != error_mark_كلي)
	    cond = build3 (ANNOTATE_فرچ, بشيا_TYPE (cond), cond,
			   build_int_cst (integer_type_كلي,
					  annot_فرچ_ivdep_kind),
			   integer_zero_كلي);
	  إذا (unroll && cond != error_mark_كلي)
	    cond = build3 (ANNOTATE_فرچ, بشيا_TYPE (cond), cond,
 			   build_int_cst (integer_type_كلي,
					  annot_فرچ_unroll_kind),
			   build_int_cst (integer_type_كلي, unroll));
	  إذا (novector && cond && cond != error_mark_كلي)
	    cond = build3 (ANNOTATE_فرچ, بشيا_TYPE (cond), cond,
			   build_int_cst (integer_type_كلي,
					  annot_فرچ_no_vector_kind),
			   integer_zero_كلي);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  إذا (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_expression = error_mark_كلي;
	    }
	  وإلا
	    incr = c_process_فرچ_stmt (loc, NULL_بشيا);
	}
      وإلا
	{
	  إذا (is_foreach_statement)
	    collection_expression
	      = c_fully_fold (c_parser_expression (parser).درج, خطأ, عدم);
	  وإلا
	    {
	      بنية c_فرچ ce = c_parser_expression (parser);
	      ce = convert_lvalue_to_rvalue (loc, ce, true, خطأ);
	      incr = c_process_فرچ_stmt (loc, ce.درج);
	    }
	}
      parens.skip_until_found_close (parser);
    }
  save_in_statement = in_statement;
  إذا (is_foreach_statement)
    {
      in_statement = IN_OBJC_FOREACH;
      save_objc_foreach_break_label = objc_foreach_break_label;
      save_objc_foreach_continue_label = objc_foreach_continue_label;
      objc_foreach_break_label = create_artificial_label (loc);
      objc_foreach_continue_label = create_artificial_label (loc);
      إذا (loop_name)
	{
	  gcc_checking_assert (!DECL_CHAIN (loop_name)
			       && !DECL_CHAIN (objc_foreach_break_label));
	  C_DECL_SWITCH_NAME (loop_name) = 1;
	  DECL_CHAIN (loop_name) = objc_foreach_break_label;
	  DECL_CHAIN (objc_foreach_break_label) = objc_foreach_continue_label;
	}
    }
  وإلا
    in_statement = IN_ITERATION_STMT;
  إذا (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  منطقي open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);

  إذا (loop_name && is_foreach_statement)
    {
      gcc_checking_assert (DECL_CHAIN (loop_name) == objc_foreach_break_label
			   && (DECL_CHAIN (objc_foreach_break_label)
			       == objc_foreach_continue_label));
      C_DECL_SWITCH_NAME (loop_name) = 0;
      DECL_CHAIN (loop_name) = NULL_بشيا;
      DECL_CHAIN (objc_foreach_break_label) = NULL_بشيا;
    }

  إذا (is_foreach_statement)
    objc_finish_foreach_loop (for_loc, object_expression,
			      collection_expression, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  وإلا
    add_stmt (build_stmt (for_loc, FOR_STMT, NULL_بشيا, cond, incr,
			  body, NULL_بشيا,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_USED (loop_name)
			  ? loop_name : NULL_بشيا, NULL_بشيا, NULL_بشيا));
  add_stmt (c_end_compound_stmt (for_loc, block,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, next_tinfo);

  إذا (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    for_tinfo.location, RID_FOR);

  in_statement = save_in_statement;
  إذا (لمب_names)
    c_release_loop_names (لمب_names);
  إذا (is_foreach_statement)
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

ساكن بشيا
c_parser_asm_statement (c_parser *parser)
{
  بشيا str, outputs, inputs, clobbers, labels, ret;
  منطقي simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  صحيح section, nsections;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);

  /* Handle the asm-qualifier-list.  */
  location_t volatile_loc = UNKNOWN_LOCATION;
  location_t inline_loc = UNKNOWN_LOCATION;
  location_t goto_loc = UNKNOWN_LOCATION;
  لكل (;;)
    {
      c_token *token = c_parser_peek_token (parser);
      location_t loc = token->location;
      بدل (token->keyword)
	{
	حالة RID_VOLATILE:
	  إذا (volatile_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->درج);
	      inform (volatile_loc, "first seen here");
	    }
	  وإلا
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  استمر;

	حالة RID_INLINE:
	  إذا (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->درج);
	      inform (inline_loc, "first seen here");
	    }
	  وإلا
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  استمر;

	حالة RID_GOTO:
	  إذا (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->درج);
	      inform (goto_loc, "first seen here");
	    }
	  وإلا
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  استمر;

	حالة RID_CONST:
	حالة RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->درج);
	  c_parser_consume_token (parser);
	  استمر;

	افتراضي:
	  اكسر;
	}
      اكسر;
    }

  منطقي is_volatile = (volatile_loc != UNKNOWN_LOCATION);
  منطقي is_inline = (inline_loc != UNKNOWN_LOCATION);
  منطقي is_goto = (goto_loc != UNKNOWN_LOCATION);

  ret = عدم;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    اذهب error;

  str = c_parser_asm_string_literal (parser);
  إذا (str == NULL_بشيا)
    اذهب error_close_paren;

  simple = true;
  outputs = NULL_بشيا;
  inputs = NULL_بشيا;
  clobbers = NULL_بشيا;
  labels = NULL_بشيا;

  إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    اذهب done_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  لكل (section = 0; section < nsections; ++section)
    {
      إذا (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  إذا (section == nsections)
	    {
	      c_parser_error (parser, "expected %<)%>");
	      اذهب error_close_paren;
	    }
	  c_parser_consume_token (parser);
	}
      وإلا إذا (!c_parser_require (parser, CPP_COLON,
				  is_goto
				  ? G_("expected %<:%>")
				  : G_("expected %<:%> or %<)%>"),
				  UNKNOWN_LOCATION, is_goto))
	اذهب error_close_paren;

      /* Once past any colon, we're no longer a simple asm.  */
      simple = خطأ;

      إذا ((!c_parser_next_token_is (parser, CPP_COLON)
	   && !c_parser_next_token_is (parser, CPP_SCOPE)
	   && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	  || section == 3)
	بدل (section)
	  {
	  حالة 0:
	    outputs = c_parser_asm_operands (parser);
	    اكسر;
	  حالة 1:
	    inputs = c_parser_asm_operands (parser);
	    اكسر;
	  حالة 2:
	    clobbers = c_parser_asm_clobbers (parser);
	    اكسر;
	  حالة 3:
	    labels = c_parser_asm_goto_operands (parser);
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }

      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	اذهب done_asm;
    }

 done_asm:
  إذا (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
      اذهب error;
    }

  إذا (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_to_end_of_block_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_فرچ (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  أرجع ret;

 error_close_paren:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
  اذهب error;
}

/* Parse asm operands, a GNU extension.

   asm-operands:
     asm-operand
     asm-operands , asm-operand

   asm-operand:
     asm-string-literal ( expression )
     [ identifier ] asm-string-literal ( expression )
*/

ساكن بشيا
c_parser_asm_operands (c_parser *parser)
{
  بشيا list = NULL_بشيا;
  طالما (true)
    {
      بشيا name, str;
      بنية c_فرچ فرچ;
      إذا (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
	{
	  c_parser_consume_token (parser);
	  إذا (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      بشيا id = c_parser_peek_token (parser)->درج;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_LENGTH (id),
				   IDENTIFIER_POINTER (id));
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, عدم);
	      أرجع NULL_بشيا;
	    }
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	}
      وإلا
	name = NULL_بشيا;
      str = c_parser_asm_string_literal (parser);
      إذا (str == NULL_بشيا)
	أرجع NULL_بشيا;
      matching_parens parens;
      إذا (!parens.require_open (parser))
	أرجع NULL_بشيا;
      فرچ = c_parser_expression (parser);
      mark_exp_read (فرچ.درج);
      إذا (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع NULL_بشيا;
	}
      list = chainon (list, build_بشيا_list (build_بشيا_list (name, str),
					     فرچ.درج));
      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  أرجع list;
}

/* Parse asm clobbers, a GNU extension.

   asm-clobbers:
     asm-string-literal
     asm-clobbers , asm-string-literal
*/

ساكن بشيا
c_parser_asm_clobbers (c_parser *parser)
{
  بشيا list = NULL_بشيا;
  طالما (true)
    {
      بشيا str = c_parser_asm_string_literal (parser);
      إذا (str)
	list = بشيا_cons (NULL_بشيا, str, list);
      وإلا
	أرجع NULL_بشيا;
      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  أرجع list;
}

/* Parse asm goto labels, a GNU extension.

   asm-goto-operands:
     identifier
     asm-goto-operands , identifier
*/

ساكن بشيا
c_parser_asm_goto_operands (c_parser *parser)
{
  بشيا list = NULL_بشيا;
  طالما (true)
    {
      بشيا name, label;

      إذا (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->درج;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  بشيا_USED (label) = 1;
	}
      وإلا
	{
	  c_parser_error (parser, "expected identifier");
	  أرجع NULL_بشيا;
	}

      name = build_string (IDENTIFIER_LENGTH (name),
			   IDENTIFIER_POINTER (name));
      list = بشيا_cons (name, label, list);
      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	أرجع nreverse (list);
    }
}

/* Parse a possibly concatenated sequence of string literals.
   TRANSLATE says whether to translate them to the execution character
   set; WIDE_OK says whether any kind of prefixed string literal is
   permitted in this context.  This code is based on that in
   lex_string.  */

بنية c_فرچ
c_parser_string_literal (c_parser *parser, منطقي translate, منطقي wide_ok)
{
  بنية c_فرچ ret;
  size_t كدي;
  بنية obstack str_ob;
  بنية obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, last_tok_loc;
  تعداد cpp_ttype type;
  بشيا درج, string_بشيا;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  last_tok_loc = linemap_resolve_location (لي_table, loc,
					   LRK_MACRO_DEFINITION_LOCATION,
					   عدم);
  type = tok->type;
  بدل (type)
    {
    حالة CPP_STRING:
    حالة CPP_WSTRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_UTF8STRING:
      string_بشيا = tok->درج;
      اكسر;

    افتراضي:
      c_parser_error (parser, "expected string literal");
      ret.set_error ();
      ret.درج = NULL_بشيا;
      ret.original_code = ERROR_MARK;
      ret.original_type = NULL_بشيا;
      أرجع ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  بدل (c_parser_peek_2nd_token (parser)->type)
    {
    افتراضي:
      c_parser_consume_token (parser);
      str.text = (ثابت unsigned حرف *) بشيا_STRING_POINTER (string_بشيا);
      str.len = بشيا_STRING_LENGTH (string_بشيا);
      كدي = 1;
      strs = &str;
      اكسر;

    حالة CPP_STRING:
    حالة CPP_WSTRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      كدي = 0;
      افعل
	{
	  c_parser_consume_token (parser);
	  كدي++;
	  str.text = (ثابت unsigned حرف *) بشيا_STRING_POINTER (string_بشيا);
	  str.len = بشيا_STRING_LENGTH (string_بشيا);
	  إذا (type != tok->type)
	    {
	      إذا (type == CPP_STRING)
		type = tok->type;
	      وإلا إذا (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, حجم (cpp_string));
	  obstack_grow (&loc_ob, &last_tok_loc, حجم (location_t));
	  tok = c_parser_peek_token (parser);
	  string_بشيا = tok->درج;
	  last_tok_loc
	    = linemap_resolve_location (لي_table, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, عدم);
	}
      طالما (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_finish (&str_ob);
    }

  إذا (كدي > 1 && !in_system_header_at (شغرو_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  إذا ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_in, strs, كدي, &istr, type)))
    {
      درج = build_string (istr.len, (ثابت حرف *) istr.text);
      حرر (const_cast<unsigned حرف *> (istr.text));
      إذا (كدي > 1)
	{
	  location_t *locs = (location_t *) obstack_finish (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->record_string_concatenation (كدي, locs);
	}
    }
  وإلا
    {
      إذا (type != CPP_STRING && !wide_ok)
	{
	  error_at (loc, "a wide string is invalid in this context");
	  type = CPP_STRING;
	}
      /* Callers cannot generally handle error_mark_node in this
	 context, so return the empty string instead.  An error has
	 been issued, either above or from cpp_interpret_string.  */
      بدل (type)
	{
	افتراضي:
	حالة CPP_STRING:
	حالة CPP_UTF8STRING:
	  إذا (type == CPP_UTF8STRING && flag_char8_t)
	    {
	      درج = build_string (TYPE_PRECISION (char8_type_كلي)
				    / TYPE_PRECISION (char_type_كلي),
				    "");  /* char8_t is 8 bits */
	    }
	  وإلا
	    درج = build_string (1, "");
	  اكسر;
	حالة CPP_STRING16:
	  درج = build_string (TYPE_PRECISION (char16_type_كلي)
				/ TYPE_PRECISION (char_type_كلي),
				"\0");  /* char16_t is 16 bits */
	  اكسر;
	حالة CPP_STRING32:
	  درج = build_string (TYPE_PRECISION (char32_type_كلي)
				/ TYPE_PRECISION (char_type_كلي),
				"\0\0\0");  /* char32_t is 32 bits */
	  اكسر;
	حالة CPP_WSTRING:
	  درج = build_string (TYPE_PRECISION (wchar_type_كلي)
				/ TYPE_PRECISION (char_type_كلي),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  اكسر;
        }
    }

  بدل (type)
    {
    افتراضي:
    حالة CPP_STRING:
      بشيا_TYPE (درج) = char_array_type_كلي;
      اكسر;
    حالة CPP_UTF8STRING:
      إذا (flag_char8_t)
	بشيا_TYPE (درج) = char8_array_type_كلي;
      وإلا
	بشيا_TYPE (درج) = char_array_type_كلي;
      اكسر;
    حالة CPP_STRING16:
      بشيا_TYPE (درج) = char16_array_type_كلي;
      اكسر;
    حالة CPP_STRING32:
      بشيا_TYPE (درج) = char32_array_type_كلي;
      اكسر;
    حالة CPP_WSTRING:
      بشيا_TYPE (درج) = wchar_array_type_كلي;
    }
  درج = fix_string_type (درج);

  إذا (كدي > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.درج = درج;
  ret.original_code = STRING_CST;
  ret.original_type = NULL_بشيا;
  set_c_فرچ_source_range (&ret, get_range_from_loc (لي_table, loc));
  ret.m_decimal = 0;
  parser->seen_string_literal = true;
  أرجع ret;
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

ساكن بنية c_فرچ
c_parser_فرچ_no_commas (c_parser *parser, بنية c_فرچ *after,
			 بشيا omp_atomic_lhs)
{
  بنية c_فرچ lhs, rhs, ret;
  تعداد بشيا_code code;
  location_t op_location, exp_location;
  منطقي save_in_omp_for = c_in_omp_for;
  c_in_omp_for = خطأ;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_expression (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_EQ:
      code = NOP_فرچ;
      اكسر;
    حالة CPP_MULT_EQ:
      code = MULT_فرچ;
      اكسر;
    حالة CPP_DIV_EQ:
      code = TRUNC_DIV_فرچ;
      اكسر;
    حالة CPP_MOD_EQ:
      code = TRUNC_MOD_فرچ;
      اكسر;
    حالة CPP_PLUS_EQ:
      code = PLUS_فرچ;
      اكسر;
    حالة CPP_MINUS_EQ:
      code = MINUS_فرچ;
      اكسر;
    حالة CPP_LSHIFT_EQ:
      code = LSHIFT_فرچ;
      اكسر;
    حالة CPP_RSHIFT_EQ:
      code = RSHIFT_فرچ;
      اكسر;
    حالة CPP_AND_EQ:
      code = BIT_AND_فرچ;
      اكسر;
    حالة CPP_XOR_EQ:
      code = BIT_XOR_فرچ;
      اكسر;
    حالة CPP_OR_EQ:
      code = BIT_IOR_فرچ;
      اكسر;
    افتراضي:
      c_in_omp_for = save_in_omp_for;
      أرجع lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_فرچ_no_commas (parser, عدم);
  rhs = convert_lvalue_to_rvalue (exp_location, rhs, true, true);

  ret.درج = build_modify_فرچ (op_location, lhs.درج, lhs.original_type,
				 code, exp_location, rhs.درج,
				 rhs.original_type);
  ret.m_decimal = 0;
  set_c_فرچ_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  إذا (code == NOP_فرچ)
    ret.original_code = MODIFY_فرچ;
  وإلا
    {
      suppress_warning (ret.درج, OPT_Wparentheses);
      ret.original_code = ERROR_MARK;
    }
  ret.original_type = عدم;
  c_in_omp_for = save_in_omp_for;
  أرجع ret;
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

ساكن بنية c_فرچ
c_parser_conditional_expression (c_parser *parser, بنية c_فرچ *after,
				 بشيا omp_atomic_lhs)
{
  بنية c_فرچ cond, exp1, exp2, ret;
  location_t start, cond_loc, colon_loc;
  منطقي save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_نبيو_expression (parser, after, omp_atomic_lhs);

  إذا (c_parser_next_token_is_not (parser, CPP_QUERY))
    أرجع cond;
  c_omp_array_section_p = خطأ;
  إذا (cond.درج != error_mark_كلي)
    start = cond.get_start ();
  وإلا
    start = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_to_rvalue (cond_loc, cond, true, true);
  c_parser_consume_token (parser);
  إذا (c_parser_next_token_is (parser, CPP_COLON))
    {
      بشيا eptype = NULL_بشيا;

      location_t ڟكيا_loc = c_parser_peek_token (parser)->location;
      pedwarn (ڟكيا_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      إذا (بشيا_CODE (cond.درج) == EXCESS_PRECISION_فرچ)
	{
	  eptype = بشيا_TYPE (cond.درج);
	  cond.درج = بشيا_OPERAND (cond.درج, 0);
	}
      بشيا e = cond.درج;
      طالما (بشيا_CODE (e) == COMPOUND_فرچ)
	e = بشيا_OPERAND (e, 1);
      warn_for_omitted_condop (ڟكيا_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.درج = save_فرچ (default_conversion (cond.درج));
      إذا (eptype)
	exp1.درج = build1 (EXCESS_PRECISION_فرچ, eptype, exp1.درج);
      exp1.original_type = عدم;
      exp1.src_range = cond.src_range;
      cond.درج = c_objc_common_truthvalue_conversion (cond_loc, exp1.درج);
      c_inhibit_evaluation_warnings += cond.درج == truthvalue_true_كلي;
    }
  وإلا
    {
      cond.درج
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.درج));
      c_inhibit_evaluation_warnings += cond.درج == truthvalue_false_كلي;
      exp1 = c_parser_expression_conv (parser);
      mark_exp_read (exp1.درج);
      c_inhibit_evaluation_warnings +=
	((cond.درج == truthvalue_true_كلي)
	 - (cond.درج == truthvalue_false_كلي));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.درج == truthvalue_true_كلي;
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = عدم;
      c_omp_array_section_p = save_c_omp_array_section_p;
      أرجع ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_expression (parser, عدم, NULL_بشيا);
    exp2 = convert_lvalue_to_rvalue (exp2_loc, exp2, true, true);
  }
  c_inhibit_evaluation_warnings -= cond.درج == truthvalue_true_كلي;
  location_t loc1 = make_location (exp1.get_start (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_start (), exp2.src_range);
  إذا (UNLIKELY (omp_atomic_lhs != عدم)
      && (بشيا_CODE (cond.درج) == GT_فرچ
	  || بشيا_CODE (cond.درج) == LT_فرچ
	  || بشيا_CODE (cond.درج) == EQ_فرچ)
      && c_بشيا_equal (exp2.درج, omp_atomic_lhs)
      && (c_بشيا_equal (بشيا_OPERAND (cond.درج, 0), omp_atomic_lhs)
	  || c_بشيا_equal (بشيا_OPERAND (cond.درج, 1), omp_atomic_lhs)))
    ret.درج = build3_loc (colon_loc, COND_فرچ, بشيا_TYPE (omp_atomic_lhs),
			    cond.درج, exp1.درج, exp2.درج);
  وإلا
    ret.درج
      = build_conditional_فرچ (colon_loc, cond.درج,
				cond.original_code == C_MAYBE_CONST_فرچ,
				exp1.درج, exp1.original_type, loc1,
				exp2.درج, exp2.original_type, loc2);
  ret.original_code = ERROR_MARK;
  إذا (exp1.درج == error_mark_كلي || exp2.درج == error_mark_كلي)
    ret.original_type = عدم;
  وإلا
    {
      بشيا t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : بشيا_TYPE (exp1.درج);
      t2 = exp2.original_type ? exp2.original_type : بشيا_TYPE (exp2.درج);
      ret.original_type = ((t1 != error_mark_كلي
			    && t2 != error_mark_كلي
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : عدم);
    }
  set_c_فرچ_source_range (&ret, start, exp2.get_finish ());
  ret.m_decimal = 0;
  c_omp_array_section_p = save_c_omp_array_section_p;
  أرجع ret;
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

ساكن بنية c_فرچ
c_parser_نبيو_expression (c_parser *parser, بنية c_فرچ *after,
			    بشيا omp_atomic_lhs)
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

  بنية {
    /* The expression at this stack level.  */
    بنية c_فرچ فرچ;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    تعداد c_parser_prec prec;
    /* The operation on its left.  */
    تعداد بشيا_code op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    بشيا sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    بشيا orig_فرچ;
  } تر[لمب_PRECS];
  صحيح sp;
  /* Location of the binary operator.  */
  location_t نبيو_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#define چرو_2								      \
  افعل {									      \
    بدل (تر[sp].op)						      \
      {									      \
      حالة TRUTH_ANDIF_فرچ:						      \
	c_inhibit_evaluation_warnings -= (تر[sp - 1].فرچ.درج	      \
					  == truthvalue_false_كلي);	      \
	اكسر;								      \
      حالة TRUTH_ORIF_فرچ:						      \
	c_inhibit_evaluation_warnings -= (تر[sp - 1].فرچ.درج	      \
					  == truthvalue_true_كلي);	      \
	اكسر;								      \
      حالة TRUNC_DIV_فرچ:						      \
	إذا ((تر[sp - 1].فرچ.original_code == SIZEOF_فرچ		      \
	     || تر[sp - 1].فرچ.original_code == PAREN_SIZEOF_فرچ)	      \
	    && (تر[sp].فرچ.original_code == SIZEOF_فرچ		      \
		|| تر[sp].فرچ.original_code == PAREN_SIZEOF_فرچ))	      \
	  {								      \
	    بشيا type0 = تر[sp - 1].sizeof_arg;			      \
	    بشيا type1 = تر[sp].sizeof_arg;				      \
	    بشيا first_arg = type0;					      \
	    إذا (!TYPE_P (type0))					      \
	      type0 = بشيا_TYPE (type0);				      \
	    إذا (!TYPE_P (type1))					      \
	      type1 = بشيا_TYPE (type1);				      \
	    إذا (POINTER_TYPE_P (type0)					      \
		&& comptypes (بشيا_TYPE (type0), type1)			      \
		&& !(بشيا_CODE (first_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (first_arg)			      \
		     && warn_sizeof_array_argument))			      \
	      {								      \
		auto_diagnostic_group d;				      \
		إذا (warning_at (تر[sp].loc, OPT_Wsizeof_pointer_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  إذا (DECL_P (first_arg))				      \
		    inform (DECL_SOURCE_LOCATION (first_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    وإلا إذا (بشيا_CODE (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (بشيا_TYPE (type0)))  \
		     && تر[sp].فرچ.original_code != PAREN_SIZEOF_فرچ)    \
	      maybe_warn_sizeof_array_div (تر[sp].loc, first_arg, type0,   \
					   تر[sp].sizeof_arg, type1);      \
	  }								      \
	اكسر;								      \
      افتراضي:								      \
	اكسر;								      \
      }									      \
    تر[sp - 1].فرچ							      \
      = convert_lvalue_to_rvalue (تر[sp - 1].loc,			      \
				  تر[sp - 1].فرچ, true, true);	      \
    تر[sp].فرچ							      \
      = convert_lvalue_to_rvalue (تر[sp].loc,			      \
				  تر[sp].فرچ, true, true);		      \
    إذا (UNLIKELY (omp_atomic_lhs != NULL_بشيا) && sp == 1		      \
	&& ((c_parser_next_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << تر[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_SHIFT)		      \
		     | (1 << PREC_ADD) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_next_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_كلي			      \
		     && c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (تر[sp].prec == PREC_REL || تر[sp].prec == PREC_EQ)))\
	&& تر[sp].op != TRUNC_MOD_فرچ				      \
	&& تر[sp].op != GE_فرچ					      \
	&& تر[sp].op != LE_فرچ					      \
	&& تر[sp].op != NE_فرچ					      \
	&& تر[0].فرچ.درج != error_mark_كلي			      \
	&& تر[1].فرچ.درج != error_mark_كلي			      \
	&& (omp_atomic_lhs == void_list_كلي				      \
	    || c_بشيا_equal (تر[0].فرچ.درج, omp_atomic_lhs)	      \
	    || c_بشيا_equal (تر[1].فرچ.درج, omp_atomic_lhs)	      \
	    || (تر[sp].op == EQ_فرچ					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	بشيا t = make_كلي (تر[1].op);				      \
	بشيا_TYPE (t) = بشيا_TYPE (تر[0].فرچ.درج);		      \
	بشيا_OPERAND (t, 0) = تر[0].فرچ.درج;			      \
	بشيا_OPERAND (t, 1) = تر[1].فرچ.درج;			      \
	تر[0].فرچ.درج = t;					      \
	تر[0].فرچ.m_decimal = 0;					      \
      }									      \
    وإلا								      \
      تر[sp - 1].فرچ = parser_build_نبيو_op (تر[sp].loc,	      \
						   تر[sp].op,	      \
						   تر[sp - 1].فرچ,	      \
						   تر[sp].فرچ,	      \
						   تر[sp - 1].orig_فرچ);  \
    تر[sp - 1].orig_فرچ = NULL_بشيا;				      \
    sp--;								      \
  } طالما (0)
  gcc_assert (!after || c_dialect_objc ());
  تر[0].loc = c_parser_peek_token (parser)->location;
  تر[0].فرچ = c_parser_cast_expression (parser, after);
  تر[0].prec = PREC_NONE;
  تر[0].sizeof_arg = c_last_sizeof_arg;
  تر[0].orig_فرچ = NULL_بشيا;
  sp = 0;
  طالما (true)
    {
      تعداد c_parser_prec oprec;
      تعداد بشيا_code ocode;
      source_range src_range;
      إذا (parser->error)
	اذهب out;
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_فرچ;
	  اكسر;
	حالة CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_فرچ;
	  اكسر;
	حالة CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_فرچ;
	  اكسر;
	حالة CPP_PLUS:
	  oprec = PREC_ADD;
	  ocode = PLUS_فرچ;
	  اكسر;
	حالة CPP_MINUS:
	  oprec = PREC_ADD;
	  ocode = MINUS_فرچ;
	  اكسر;
	حالة CPP_LSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = LSHIFT_فرچ;
	  اكسر;
	حالة CPP_RSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = RSHIFT_فرچ;
	  اكسر;
	حالة CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_فرچ;
	  اكسر;
	حالة CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_فرچ;
	  اكسر;
	حالة CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_فرچ;
	  اكسر;
	حالة CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_فرچ;
	  اكسر;
	حالة CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_فرچ;
	  اكسر;
	حالة CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_فرچ;
	  اكسر;
	حالة CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = BIT_AND_فرچ;
	  اكسر;
	حالة CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = BIT_XOR_فرچ;
	  اكسر;
	حالة CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = BIT_IOR_فرچ;
	  اكسر;
	حالة CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_فرچ;
	  اكسر;
	حالة CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_فرچ;
	  اكسر;
	افتراضي:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  اذهب out;
	}
      نبيو_loc = c_parser_peek_token (parser)->location;
      طالما (oprec <= تر[sp].prec)
	چرو_2;
      c_parser_consume_token (parser);
      بدل (ocode)
	{
	حالة TRUTH_ANDIF_فرچ:
	  src_range = تر[sp].فرچ.src_range;
	  تر[sp].فرچ
	    = convert_lvalue_to_rvalue (تر[sp].loc,
					تر[sp].فرچ, true, true);
	  تر[sp].orig_فرچ = تر[sp].فرچ.درج;
	  تر[sp].فرچ.درج = c_objc_common_truthvalue_conversion
	    (تر[sp].loc, default_conversion (تر[sp].فرچ.درج));
	  c_inhibit_evaluation_warnings += (تر[sp].فرچ.درج
					    == truthvalue_false_كلي);
	  set_c_فرچ_source_range (&تر[sp].فرچ, src_range);
	  اكسر;
	حالة TRUTH_ORIF_فرچ:
	  src_range = تر[sp].فرچ.src_range;
	  تر[sp].فرچ
	    = convert_lvalue_to_rvalue (تر[sp].loc,
					تر[sp].فرچ, true, true);
	  تر[sp].orig_فرچ = تر[sp].فرچ.درج;
	  تر[sp].فرچ.درج = c_objc_common_truthvalue_conversion
	    (تر[sp].loc, default_conversion (تر[sp].فرچ.درج));
	  c_inhibit_evaluation_warnings += (تر[sp].فرچ.درج
					    == truthvalue_true_كلي);
	  set_c_فرچ_source_range (&تر[sp].فرچ, src_range);
	  اكسر;
	افتراضي:
	  اكسر;
	}
      sp++;
      تر[sp].loc = نبيو_loc;
      تر[sp].فرچ = c_parser_cast_expression (parser, عدم);
      تر[sp].prec = oprec;
      تر[sp].op = ocode;
      تر[sp].sizeof_arg = c_last_sizeof_arg;
      تر[sp].orig_فرچ = NULL_بشيا;
    }
 out:
  طالما (sp > 0)
    چرو_2;
  أرجع تر[0].فرچ;
#undef چرو_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

ساكن بنية c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  منطقي seen_scspec = خطأ;
  بنية c_declspecs *specs = build_null_declspecs ();
  طالما (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_CONSTEXPR:
	حالة RID_REGISTER:
	حالة RID_STATIC:
	حالة RID_THREAD:
	  seen_scspec = true;
	  declspecs_add_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->درج);
	  c_parser_consume_token (parser);
	  اكسر;
	افتراضي:
	  اذهب out;
	}
    }
 out:
  أرجع seen_scspec ? specs : عدم;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

ساكن بنية c_فرچ
c_parser_cast_expression (c_parser *parser, بنية c_فرچ *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  إذا (after)
    أرجع c_parser_postfix_expression_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      بنية c_declspecs *scspecs;
      بنية c_type_name *type_name;
      بنية c_فرچ ret;
      بنية c_فرچ فرچ;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, true);
      parens.skip_until_found_close (parser);
      إذا (type_name == عدم)
	{
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = عدم;
	  أرجع ret;
	}

      /* Save casted types in the function's used types hash table.  */
      used_types_سك (type_name->specs->type);

      إذا (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	أرجع c_parser_postfix_expression_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      إذا (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      إذا (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t فرچ_loc = c_parser_peek_token (parser)->location;
	فرچ = c_parser_cast_expression (parser, عدم);
	فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, true, true);
      }
      ret.درج = c_cast_فرچ (cast_loc, type_name, فرچ.درج);
      إذا (ret.درج && فرچ.درج)
	set_c_فرچ_source_range (&ret, cast_loc, فرچ.get_finish ());
      ret.original_code = ERROR_MARK;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      أرجع ret;
    }
  وإلا
    أرجع c_parser_unary_expression (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

ساكن فراغ
mark_exp_read_cond (بشيا exp)
{
  إذا ((VAR_P (exp) || بشيا_CODE (exp) == PARM_DECL)
      && (VAR_P (exp) ? warn_unused_but_set_variable
		      : warn_unused_but_set_parameter) > 1)
    أرجع;

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

ساكن بنية c_فرچ
c_parser_unary_expression (c_parser *parser)
{
  صحيح ext;
  بنية c_فرچ ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t exp_loc;
  location_t finish;
  ret.original_code = ERROR_MARK;
  ret.original_type = عدم;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, عدم);
      mark_exp_read_cond (op.درج);
      op = default_function_array_conversion (exp_loc, op);
      أرجع parser_build_unary_op (op_loc, PREINCREMENT_فرچ, op);
    حالة CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, عدم);
      mark_exp_read_cond (op.درج);
      op = default_function_array_conversion (exp_loc, op);
      أرجع parser_build_unary_op (op_loc, PREDECREMENT_فرچ, op);
    حالة CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, عدم);
      mark_exp_read (op.درج);
      أرجع parser_build_unary_op (op_loc, ADDR_فرچ, op);
    حالة CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_expression (parser, عدم);
	finish = op.get_finish ();
	op = convert_lvalue_to_rvalue (exp_loc, op, true, true);
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.درج = build_indirect_ref (combined_loc, op.درج, RO_UNARY_STAR);
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ret.m_decimal = 0;
	أرجع ret;
      }
    حالة CPP_PLUS:
      إذا (!c_dialect_objc () && !in_system_header_at (شغرو_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, عدم);
      op = convert_lvalue_to_rvalue (exp_loc, op, true, true);
      أرجع parser_build_unary_op (op_loc, CONVERT_فرچ, op);
    حالة CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, عدم);
      op = convert_lvalue_to_rvalue (exp_loc, op, true, true);
      أرجع parser_build_unary_op (op_loc, NEGATE_فرچ, op);
    حالة CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, عدم);
      op = convert_lvalue_to_rvalue (exp_loc, op, true, true);
      أرجع parser_build_unary_op (op_loc, BIT_NOT_فرچ, op);
    حالة CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, عدم);
      op = convert_lvalue_to_rvalue (exp_loc, op, true, true);
      أرجع parser_build_unary_op (op_loc, TRUTH_NOT_فرچ, op);
    حالة CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      إذا (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ret.درج = finish_label_address_فرچ
	    (c_parser_peek_token (parser)->درج, op_loc);
	  set_c_فرچ_source_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_finish ());
	  c_parser_consume_token (parser);
	}
      وإلا
	{
	  c_parser_error (parser, "expected identifier");
	  ret.set_error ();
	}
      أرجع ret;
    حالة CPP_KEYWORD:
      {
	تعداد rid rid = c_parser_peek_token (parser)->keyword;
	بدل (rid)
	  {
	  حالة RID_COUNTOF:
	  حالة RID_SIZEOF:
	    أرجع c_parser_sizeof_or_countof_expression (parser, rid);
	  حالة RID_ALIGNOF:
	    أرجع c_parser_alignof_expression (parser);
	  حالة RID_MAXOF:
	  حالة RID_MINOF:
	    أرجع c_parser_maxof_or_minof_expression (parser, rid);
	  حالة RID_BUILTIN_HAS_ATTRIBUTE:
	    أرجع c_parser_has_attribute_expression (parser);
	  حالة RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_expression (parser, عدم);
	    restore_extension_diagnostics (ext);
	    أرجع ret;
	  حالة RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, عدم);
	    op = default_function_array_conversion (exp_loc, op);
	    أرجع parser_build_unary_op (op_loc, REALPART_فرچ, op);
	  حالة RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, عدم);
	    op = default_function_array_conversion (exp_loc, op);
	    أرجع parser_build_unary_op (op_loc, IMAGPART_فرچ, op);
	  حالة RID_TRANSACTION_ATOMIC:
	  حالة RID_TRANSACTION_RELAXED:
	    أرجع c_parser_transaction_expression (parser, rid);
	  حالة RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.درج = void_كلي;
	    set_c_فرچ_source_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    أرجع ret;
	  افتراضي:
	    أرجع c_parser_postfix_expression (parser);
	  }
      }
    افتراضي:
      أرجع c_parser_postfix_expression (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

ساكن بنية c_فرچ
c_parser_sizeof_or_countof_expression (c_parser *parser, تعداد rid rid)
{
  ثابت حرف *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  بنية c_فرچ فرچ;
  بنية c_فرچ result;
  location_t فرچ_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  إذا (rid == RID_COUNTOF)
    pedwarn_c23 (start, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  إذا (rid == RID_COUNTOF)
    in_countof++;
  وإلا
    in_sizeof++;
  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      بنية c_declspecs *scspecs;
      بنية c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      فرچ_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, true);
      parens.skip_until_found_close (parser);
      finish = parser->tokens_buf[0].location;
      إذا (type_name == عدم)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  فرچ.set_error ();
	  اذهب Xof_فرچ;
	}
      إذا (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  فرچ = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       فرچ_loc);
	  finish = فرچ.get_finish ();
	  اذهب Xof_فرچ;
	}
      /* sizeof ( type-name ).  */
      إذا (scspecs)
	error_at (فرچ_loc, "storage class specifier in %qs", op_name);
      إذا (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      إذا (rid == RID_COUNTOF)
	{
	  in_countof--;
	  result = c_فرچ_countof_type (فرچ_loc, type_name);
	}
      وإلا
	{
	  in_sizeof--;
	  result = c_فرچ_sizeof_type (فرچ_loc, type_name);
	}
    }
  وإلا
    {
      فرچ_loc = c_parser_peek_token (parser)->location;
      فرچ = c_parser_unary_expression (parser);
      finish = فرچ.get_finish ();
    Xof_فرچ:
      c_inhibit_evaluation_warnings--;
      إذا (rid == RID_COUNTOF)
	in_countof--;
      وإلا
	in_sizeof--;
      mark_exp_read (فرچ.درج);
      إذا (بشيا_CODE (فرچ.درج) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (بشيا_OPERAND (فرچ.درج, 1)))
	error_at (فرچ_loc, "%qs applied to a bit-field", op_name);
      إذا (rid == RID_COUNTOF)
	result = c_فرچ_countof_فرچ (فرچ_loc, فرچ);
      وإلا
	result = c_فرچ_sizeof_فرچ (فرچ_loc, فرچ);
    }
  إذا (finish == UNKNOWN_LOCATION)
    finish = start;
  set_c_فرچ_source_range (&result, start, finish);
  أرجع result;
}

/* Parse an alignof expression.  */

ساكن بنية c_فرچ
c_parser_alignof_expression (c_parser *parser)
{
  بنية c_فرچ فرچ;
  location_t start_loc = c_parser_peek_token (parser)->location;
  location_t end_loc;
  بشيا alignof_spelling = c_parser_peek_token (parser)->درج;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNOF));
  منطقي is_c11_alignof = (strcmp (IDENTIFIER_POINTER (alignof_spelling),
				"_Alignof") == 0
			 || strcmp (IDENTIFIER_POINTER (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  إذا (is_c11_alignof)
    {
      إذا (flag_isoc99)
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      وإلا
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_alignof++;
  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      بنية c_declspecs *scspecs;
      بنية c_type_name *type_name;
      بنية c_فرچ ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, true);
      end_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
      إذا (type_name == عدم)
	{
	  بنية c_فرچ ret;
	  c_inhibit_evaluation_warnings--;
	  in_alignof--;
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = عدم;
	  أرجع ret;
	}
      إذا (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  فرچ = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  اذهب alignof_فرچ;
	}
      /* alignof ( type-name ).  */
      إذا (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      إذا (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      ret.درج = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       عدم, عدم),
					    خطأ, is_c11_alignof, 1);
      ret.original_code = ERROR_MARK;
      ret.original_type = عدم;
      set_c_فرچ_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      أرجع ret;
    }
  وإلا
    {
      بنية c_فرچ ret;
      فرچ = c_parser_unary_expression (parser);
      end_loc = فرچ.src_range.m_finish;
    alignof_فرچ:
      mark_exp_read (فرچ.درج);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      إذا (is_c11_alignof)
	pedwarn (start_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.درج = c_alignof_فرچ (start_loc, فرچ.درج);
      ret.original_code = ERROR_MARK;
      ret.original_type = عدم;
      set_c_فرچ_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      أرجع ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

ساكن بنية c_فرچ
c_parser_maxof_or_minof_expression (c_parser *parser, تعداد rid rid)
{
  ثابت حرف *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  بنية c_فرچ result;
  location_t فرچ_loc;
  بنية c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  pedwarn (start, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  إذا (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      اذهب fail;
    }
  parens.consume_open (parser);
  فرچ_loc = c_parser_peek_token (parser)->location;
  إذا (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (فرچ_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_found_close (parser);
      اذهب fail;
    }
  type_name = c_parser_type_name (parser, true);
  إذا (type_name == عدم)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_found_close (parser);
      اذهب fail;
    }
  parens.skip_until_found_close (parser);
  finish = parser->tokens_buf[0].location;
  إذا (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  إذا (rid == RID_MAXOF)
    result = c_فرچ_maxof_type (فرچ_loc, type_name);
  وإلا
    result = c_فرچ_minof_type (فرچ_loc, type_name);
  set_c_فرچ_source_range (&result, start, finish);
  أرجع result;
fail:
  c_inhibit_evaluation_warnings--;
  result.set_error ();
  result.original_code = ERROR_MARK;
  result.original_type = عدم;
  أرجع result;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

ساكن بنية c_فرچ
c_parser_has_attribute_expression (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t start = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;

      بنية c_فرچ result;
      result.set_error ();
      result.original_code = ERROR_MARK;
      result.original_type = عدم;
      أرجع result;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  in_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  بشيا oper = NULL_بشيا;
  إذا (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      بنية c_type_name *tname = c_parser_type_name (parser);
      in_typeof--;
      إذا (tname)
	{
	  oper = groktypename (tname, عدم, عدم);
	  چرو_maybe_used (c_type_variably_modified_p (oper));
	}
    }
  وإلا
    {
      بنية c_فرچ cexpr = c_parser_فرچ_no_commas (parser, عدم);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      إذا (cexpr.درج != error_mark_كلي)
	{
	  mark_exp_read (cexpr.درج);
	  oper = cexpr.درج;
	  بشيا etype = بشيا_TYPE (oper);
	  منطقي was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  إذا (was_vm)
	    oper = c_fully_fold (oper, خطأ, عدم);
	  چرو_maybe_used (was_vm);
	}
    }

  بنية c_فرچ result;
  result.original_code = ERROR_MARK;
  result.original_type = عدم;

  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      result.set_error ();
      أرجع result;
    }

  منطقي save_translate_strings_p = parser->translate_strings_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  بشيا attr = c_parser_gnu_attribute (parser, NULL_بشيا, خطأ, خطأ);

  parser->translate_strings_p = save_translate_strings_p;

  location_t finish = c_parser_peek_token (parser)->location;
  إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  وإلا
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);

      result.set_error ();
      أرجع result;
    }

  إذا (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      result.set_error ();
      أرجع result;
    }

  result.original_code = INTEGER_CST;
  result.original_type = boolean_type_كلي;

  إذا (has_attribute (atloc, oper, attr, default_conversion))
    result.درج = boolean_true_كلي;
  وإلا
    result.درج =  boolean_false_كلي;

  set_c_فرچ_source_range (&result, start, finish);
  result.m_decimal = 0;
  أرجع result;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
ساكن منطقي
c_parser_get_builtin_حجوجي (c_parser *parser, ثابت حرف *bname,
			   vec<c_فرچ_t, va_gc> **ret_cexpr_list,
			   منطقي choose_فرچ_p,
			   location_t *out_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_فرچ_t, va_gc> *cexpr_list;
  c_فرچ_t فرچ;
  منطقي saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = عدم;
  إذا (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      أرجع خطأ;
    }

  c_parser_consume_token (parser);

  إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      *out_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      أرجع true;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= choose_فرچ_p;
  فرچ = c_parser_فرچ_no_commas (parser, عدم);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_safe_تور (cexpr_list, فرچ);
  طالما (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  بشيا درج = embed->درج;
	  فرچ.original_code = INTEGER_CST;
	  فرچ.original_type = integer_type_كلي;
	  فرچ.درج = NULL_بشيا;
	  set_c_فرچ_source_range (&فرچ, embed->get_range ());
	  فرچ.m_decimal = 0;
	  لكل (unsigned صحيح i = 0; i < (unsigned) RAW_DATA_LENGTH (درج); i++)
	    {
	      فرچ.درج = build_int_cst (integer_type_كلي,
					  RAW_DATA_UCHAR_ELT (درج, i));
	      vec_safe_تور (cexpr_list, فرچ);
	    }
	  c_parser_consume_token (parser);
	  استمر;
	}
      فرچ = c_parser_فرچ_no_commas (parser, عدم);
      vec_safe_تور (cexpr_list, فرچ);
    }

  *out_close_paren_loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع خطأ;

  *ret_cexpr_list = cexpr_list;
  أرجع true;
}

/* This represents a single generic-association.  */

بنية c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  بشيا type;
  /* The association's expression.  */
  بنية c_فرچ expression;
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

ساكن بنية c_فرچ
c_parser_generic_selection (c_parser *parser)
{
  بنية c_فرچ selector, error_فرچ;
  بشيا selector_type;
  بنية c_generic_association matched_assoc;
  صحيح match_found = -1;
  location_t generic_loc, selector_loc;

  error_فرچ.original_code = ERROR_MARK;
  error_فرچ.original_type = عدم;
  error_فرچ.set_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_بشيا;
  matched_assoc.expression = error_فرچ;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_GENERIC));
  generic_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  إذا (flag_isoc99)
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C99 does not support %<_Generic%>");
  وإلا
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C90 does not support %<_Generic%>");

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع error_فرچ;

  selector_loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      c_inhibit_evaluation_warnings++;
      pedwarn_c23 (selector_loc, OPT_Wpedantic,
		   "ISO C does not support use of type name as %<_Generic%> "
		   "controlling operand before C2Y");
      بنية c_type_name *type = c_parser_type_name (parser);
      إذا (type)
	selector_type = groktypename (type, عدم, عدم);
      c_inhibit_evaluation_warnings--;
      إذا (!type)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع error_فرچ;
	}
    }
  وإلا
    {
      c_inhibit_evaluation_warnings++;
      in_generic++;
      selector = c_parser_فرچ_no_commas (parser, عدم);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      in_generic--;
      چرو_maybe_used (!flag_isoc23);

      إذا (selector.درج == error_mark_كلي)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع selector;
	}
      mark_exp_read (selector.درج);
      selector_type = بشيا_TYPE (selector.درج);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      إذا (بشيا_CODE (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      إذا (FUNCTION_POINTER_TYPE_P (selector_type)
	  && TYPE_QUALS (بشيا_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_pointer_type (TYPE_MAIN_VARIANT (بشيا_TYPE (selector_type)));
    }

  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
      أرجع error_فرچ;
    }

  auto_vec<c_generic_association> associations;
  بنية maybe_used_decl *maybe_used_default = عدم;
  طالما (1)
    {
      بنية c_generic_association assoc, *iter;
      unsigned صحيح ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      إذا (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_بشيا;
	}
      وإلا
	{
	  بنية c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  إذا (type_name == عدم)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
	      أرجع error_فرچ;
	    }
	  assoc.type = grokgenassoc (type_name);
	  إذا (assoc.type == error_mark_كلي)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
	      أرجع error_فرچ;
	    }

	  إذا (بشيا_CODE (assoc.type) == FUNCTION_TYPE)
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "function type before C2Y");
	  وإلا إذا (!COMPLETE_TYPE_P (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "incomplete type before C2Y");

	  إذا (c_type_variably_modified_p (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "variably-modified type before C2Y");
	}

      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع error_فرچ;
	}

      منطقي match = assoc.type == NULL_بشيا
		   || comptypes (assoc.type, selector_type);

      إذا (!match || matched_assoc.type != NULL_بشيا)
	c_inhibit_evaluation_warnings++;
      in_generic++;

      assoc.expression = c_parser_فرچ_no_commas (parser, عدم);

      إذا (!match || matched_assoc.type != NULL_بشيا)
	c_inhibit_evaluation_warnings--;
      in_generic--;
      إذا (!match)
	چرو_maybe_used (!flag_isoc23);
      وإلا إذا (assoc.type == NULL_بشيا)
	maybe_used_default = save_maybe_used ();
      وإلا
	چرو_maybe_used (true);

      إذا (assoc.expression.درج == error_mark_كلي)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع error_فرچ;
	}

      لكل (ix = 0; associations.iterate (ix, &iter); ++ix)
	{
	  إذا (assoc.type == NULL_بشيا)
	    {
	      إذا (iter->type == NULL_بشيا)
		{
		  error_at (assoc.type_location,
			    "duplicate %<default%> case in %<_Generic%>");
		  inform (iter->type_location, "original %<default%> is here");
		}
	    }
	  وإلا إذا (iter->type != NULL_بشيا)
	    {
	      إذا (comptypes (assoc.type, iter->type))
		{
		  error_at (assoc.type_location,
			    "%<_Generic%> specifies two compatible types");
		  inform (iter->type_location, "compatible type is here");
		}
	    }
	}

      إذا (assoc.type == NULL_بشيا)
	{
	  إذا (match_found < 0)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	}
      وإلا إذا (match)
	{
	  إذا (match_found < 0 || matched_assoc.type == NULL_بشيا)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	  وإلا
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.safe_تور (assoc);

      إذا (c_parser_peek_token (parser)->type != CPP_COMMA)
	اكسر;
      c_parser_consume_token (parser);
    }

  إذا (match_found >= 0 && matched_assoc.type == NULL_بشيا)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_used (maybe_used_default);
      چرو_maybe_used (true);
    }
  وإلا إذا (maybe_used_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_used (maybe_used_default);
      چرو_maybe_used (!flag_isoc23);
    }

  unsigned صحيح ix;
  بنية c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    إذا (ix != (unsigned) match_found)
      mark_exp_read (iter->expression.درج);

  إذا (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
      أرجع error_فرچ;
    }

  إذا (match_found < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      أرجع error_فرچ;
    }

  أرجع matched_assoc.expression;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

ساكن unsigned صحيح
check_tgmath_function (c_فرچ *فرچ, unsigned صحيح pos)
{
  بشيا type = بشيا_TYPE (فرچ->درج);
  إذا (!FUNCTION_POINTER_TYPE_P (type))
    {
      error_at (فرچ->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      أرجع 0;
    }
  type = بشيا_TYPE (type);
  إذا (!prototype_p (type))
    {
      error_at (فرچ->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      أرجع 0;
    }
  إذا (stdarg_p (type))
    {
      error_at (فرچ->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      أرجع 0;
    }
  unsigned صحيح nargs = 0;
  function_حجوجي_iterator iter;
  بشيا t;
  FOREACH_FUNCTION_حجوجي (type, t, iter)
    {
      إذا (t == void_type_كلي)
	اكسر;
      nargs++;
    }
  إذا (nargs == 0)
    {
      error_at (فرچ->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      أرجع 0;
    }
  أرجع nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
تعداد tgmath_parm_kind
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

ساكن بنية c_فرچ
c_parser_predefined_identifier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  بدل (c_parser_peek_token (parser)->keyword)
    {
    حالة RID_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__FUNCTION__");
      اكسر;
    حالة RID_PRETTY_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__PRETTY_FUNCTION__");
      اكسر;
    حالة RID_C99_FUNCTION_NAME:
      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support "
		   "%<__func__%> predefined identifier");
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }

  بنية c_فرچ فرچ;
  فرچ.original_code = ERROR_MARK;
  فرچ.original_type = عدم;
  فرچ.درج = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->درج);
  set_c_فرچ_source_range (&فرچ, loc, loc);
  فرچ.m_decimal = 0;
  c_parser_consume_token (parser);
  أرجع فرچ;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

ساكن منطقي
has_counted_by_object (بشيا ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  إذا ((بشيا_CODE (ref) == INDIRECT_REF
       && is_access_with_size_p (بشيا_OPERAND (ref, 0)))
      || is_access_with_size_p (ref))
    أرجع true;
  أرجع خطأ;
}

/* Get the reference to the counted-by object associated with the REF.  */

ساكن بشيا
get_counted_by_ref (بشيا ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  إذا (بشيا_CODE (ref) == INDIRECT_REF
      && is_access_with_size_p (بشيا_OPERAND (ref, 0)))
    أرجع CALL_فرچ_ARG (بشيا_OPERAND (ref, 0), 1);
  وإلا إذا (is_access_with_size_p (ref))
    أرجع CALL_فرچ_ARG (ref, 1);

  أرجع NULL_بشيا;
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

ساكن بنية c_فرچ
c_parser_postfix_expression (c_parser *parser)
{
  بنية c_فرچ فرچ, e1;
  بنية c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  فرچ.original_code = ERROR_MARK;
  فرچ.original_type = عدم;
  فرچ.m_decimal = 0;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_لمب:
      فرچ.درج = c_parser_peek_token (parser)->درج;
      set_c_فرچ_source_range (&فرچ, tok_range);
      loc = c_parser_peek_token (parser)->location;
      فرچ.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      إذا (بشيا_CODE (فرچ.درج) == FIXED_CST
	  && !targetm.fixed_point_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  فرچ.set_error ();
	}
      اكسر;
    حالة CPP_CHAR:
    حالة CPP_CHAR16:
    حالة CPP_CHAR32:
    حالة CPP_UTF8CHAR:
    حالة CPP_WCHAR:
      فرچ.درج = c_parser_peek_token (parser)->درج;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      فرچ.original_type = char_type_كلي;
      set_c_فرچ_source_range (&فرچ, tok_range);
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_STRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_WSTRING:
    حالة CPP_UTF8STRING:
      فرچ = c_parser_string_literal (parser, parser->translate_strings_p,
				      true);
      اكسر;
    حالة CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      فرچ.درج
	= objc_build_string_object (c_parser_peek_token (parser)->درج);
      set_c_فرچ_source_range (&فرچ, tok_range);
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_NAME:
      بدل (c_parser_peek_token (parser)->id_kind)
	{
	حالة C_ID_ID:
	  {
	    بشيا id = c_parser_peek_token (parser)->درج;
	    c_parser_consume_token (parser);
	    فرچ.درج = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &فرچ.original_type);
	    set_c_فرچ_source_range (&فرچ, tok_range);
	    اكسر;
	  }
	حالة C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    بشيا class_name = c_parser_peek_token (parser)->درج;
	    بشيا component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    إذا (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		فرچ.set_error ();
		اكسر;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->درج;
	    location_t end_loc = component_tok->get_finish ();
	    c_parser_consume_token (parser);
	    فرچ.درج = objc_build_class_component_ref (class_name,
							 component);
	    set_c_فرچ_source_range (&فرچ, loc, end_loc);
	    اكسر;
	  }
	افتراضي:
	  c_parser_error (parser, "expected expression");
	  فرچ.set_error ();
	  اكسر;
	}
      اكسر;
    حالة CPP_OPEN_PAREN:
      /* A parenthesized expression, statement expression or compound
	 literal.  */
      إذا (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_BRACE)
	{
	  /* A statement expression.  */
	  بشيا stmt;
	  location_t brace_loc;
	  منطقي save_c_omp_array_section_p = c_omp_array_section_p;
	  c_parser_consume_token (parser);
	  brace_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* If we've not yet started the current function's statement list,
	     or we're in the parameter scope of an old-style function
	     declaration, statement expressions are not allowed.  */
	  إذا (!building_stmt_list_p () || old_style_parameter_scope ())
	    {
	      error_at (loc, "braced-group within expression allowed "
			"only inside a function");
	      parser->error = true;
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, عدم);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
	      فرچ.set_error ();
	      اكسر;
	    }
	  c_omp_array_section_p = خطأ;
	  stmt = c_begin_stmt_فرچ ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  فرچ.درج = c_finish_stmt_فرچ (brace_loc, stmt);
	  set_c_فرچ_source_range (&فرچ, loc, close_loc);
	  mark_exp_read (فرچ.درج);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      وإلا
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  فرچ = c_parser_expression (parser);
	  إذا (بشيا_CODE (فرچ.درج) == MODIFY_فرچ)
	    suppress_warning (فرچ.درج, OPT_Wparentheses);
	  إذا (فرچ.original_code != C_MAYBE_CONST_فرچ
	      && فرچ.original_code != SIZEOF_فرچ)
	    فرچ.original_code = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  إذا (فرچ.original_code == SIZEOF_فرچ)
	    فرچ.original_code = PAREN_SIZEOF_فرچ;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  set_c_فرچ_source_range (&فرچ, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      اكسر;
    حالة CPP_KEYWORD:
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_FUNCTION_NAME:
	حالة RID_PRETTY_FUNCTION_NAME:
	حالة RID_C99_FUNCTION_NAME:
	  فرچ = c_parser_predefined_identifier (parser);
	  اكسر;
	حالة RID_VA_ARG:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    e1 = c_parser_فرچ_no_commas (parser, عدم);
	    mark_exp_read (e1.درج);
	    e1.درج = c_fully_fold (e1.درج, خطأ, عدم);
	    إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
		فرچ.set_error ();
		اكسر;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    إذا (t1 == عدم)
	      {
		فرچ.set_error ();
	      }
	    وإلا
	      {
		بشيا type_فرچ = NULL_بشيا;
		بشيا type = groktypename (t1, &type_فرچ, عدم);
		فرچ.درج = c_build_va_arg (start_loc, e1.درج, loc,
					     type, type_فرچ);
		set_c_فرچ_source_range (&فرچ, start_loc, end_loc);
	      }
	  }
	  اكسر;
	حالة RID_C23_VA_START:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    e1 = c_parser_فرچ_no_commas (parser, عدم);
	    e1 = convert_lvalue_to_rvalue (e1.get_location (), e1, true, true);
	    إذا (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
		    فرچ.set_error ();
		    اكسر;
		  }
		إذا (c_parser_next_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_kind == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    بشيا name = c_parser_peek_token (parser)->درج;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    بشيا decl = lookup_name (name);
		    بشيا last_parm
		      = بشيا_last (DECL_ARGUMENTS (current_function_decl));
		    إذا (!last_parm || decl != last_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    وإلا إذا (DECL_REGISTER (decl))
		      warning_at (nloc, OPT_Wvarargs,
				  "undefined behavior when second parameter "
				  "of %<va_start%> is declared with "
				  "%<register%> storage");
		    c_parser_consume_token (parser);
		  }
		وإلا
		  {
		    unsigned nesting_depth = 0;
		    location_t sloc = c_parser_peek_token (parser)->location;
		    location_t eloc = sloc;

		    /* For va_start (ap,) the ) comes from stdarg.h.
		       Use location of , in that case, otherwise without
		       -Wsystem-headers nothing is reported.  After all,
		       the problematic token is the comma in that case.  */
		    إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    طالما (true)
		      {
			c_token *token = c_parser_peek_token (parser);
			إذا (token->type == CPP_CLOSE_PAREN && !nesting_depth)
			  اكسر;

			إذا (token->type == CPP_EOF)
			  اكسر;
			إذا (token->type == CPP_OPEN_PAREN)
			  ++nesting_depth;
			وإلا إذا (token->type == CPP_CLOSE_PAREN)
			  --nesting_depth;
			eloc = token->location;
			c_parser_consume_token (parser);
		      }
		    إذا (sloc != eloc)
		      sloc = make_location (sloc, sloc, eloc);
		    warning_at (sloc, OPT_Wvarargs,
				"%<va_start%> macro used with additional "
				"arguments other than identifier of the "
				"last named argument");
		  }
	      }
	    parens.skip_until_found_close (parser);
	    بشيا fndecl = builtin_decl_explicit (BUILT_IN_VA_START);
	    vec<بشيا, va_gc> *params;
	    vec_alloc (params, 2);
	    params->quick_تور (e1.درج);
	    params->quick_تور (integer_zero_كلي);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.quick_تور (e1.get_location ());
	    arg_loc.quick_تور (UNKNOWN_LOCATION);
	    فرچ.درج = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, عدم);
	    set_c_فرچ_source_range (&فرچ, loc,
				     parser->tokens_buf[0].get_finish ());
	    فرچ.m_decimal = 0;
	    فرچ.original_code = ERROR_MARK;
	    فرچ.original_type = عدم;
	    release_بشيا_vector (params);
	    اكسر;
	  }
	حالة RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    t1 = c_parser_type_name (parser);
	    إذا (t1 == عدم)
	      parser->error = true;
	    إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    إذا (parser->error)
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
		فرچ.set_error ();
		اكسر;
	      }
	    بشيا type = groktypename (t1, عدم, عدم);
	    بشيا offsetof_ref;
	    إذا (type == error_mark_كلي)
	      offsetof_ref = error_mark_كلي;
	    وإلا
	      {
		offsetof_ref = build1 (INDIRECT_REF, type, null_pointer_كلي);
		SET_فرچ_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    إذا (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->درج,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		طالما (c_parser_next_token_is (parser, CPP_DOT)
		       || c_parser_next_token_is (parser,
						  CPP_OPEN_SQUARE)
		       || c_parser_next_token_is (parser,
						  CPP_DEREF))
		  {
		    إذا (c_parser_next_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_كلي);
			اذهب do_dot;
		      }
		    وإلا إذا (c_parser_next_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			إذا (c_parser_next_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    اكسر;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->درج,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    وإلا
		      {
			بنية c_فرچ ce;
			بشيا idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_expression (parser);
			ce = convert_lvalue_to_rvalue (loc, ce, خطأ, خطأ);
			idx = ce.درج;
			idx = c_fully_fold (idx, خطأ, عدم);
			c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
						   "expected %<]%>");
			offsetof_ref = build_array_ref (loc, offsetof_ref, idx);
		      }
		  }
	      }
	    وإلا
	      c_parser_error (parser, "expected identifier");
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    فرچ.درج = fold_offsetof (offsetof_ref);
	    set_c_فرچ_source_range (&فرچ, loc, end_loc);
	  }
	  اكسر;
	حالة RID_CHOOSE_فرچ:
	  {
	    vec<c_فرچ_t, va_gc> *cexpr_list;
	    c_فرچ_t *e1_p, *e2_p, *e3_p;
	    بشيا c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_حجوجي (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, true,
					    &close_paren_loc))
	      {
		فرچ.set_error ();
		اكسر;
	      }

	    إذا (vec_safe_length (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		فرچ.set_error ();
		اكسر;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->درج;
	    mark_exp_read (e2_p->درج);
	    mark_exp_read (e3_p->درج);
	    إذا (بشيا_CODE (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (بشيا_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_expression_warning (c);
	    فرچ = integer_zerop (c) ? *e3_p : *e2_p;
	    set_c_فرچ_source_range (&فرچ, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    t1 = c_parser_type_name (parser);
	    إذا (t1 == عدم)
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
		فرچ.set_error ();
		اكسر;
	      }
	    t2 = c_parser_type_name (parser);
	    إذا (t2 == عدم)
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    بشيا e1, e2;
	    e1 = groktypename (t1, عدم, عدم);
	    e2 = groktypename (t2, عدم, عدم);
	    إذا (e1 == error_mark_كلي || e2 == error_mark_كلي)
	      {
		فرچ.set_error ();
		اكسر;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    فرچ.درج
	      = comptypes (e1, e2) ? integer_one_كلي : integer_zero_كلي;
	    set_c_فرچ_source_range (&فرچ, loc, close_paren_loc);
	  }
	  اكسر;
	حالة RID_BUILTIN_TGMATH:
	  {
	    vec<c_فرچ_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_حجوجي (parser,
					    "__builtin_tgmath",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		فرچ.set_error ();
		اكسر;
	      }

	    إذا (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		فرچ.set_error ();
		اكسر;
	      }

	    unsigned صحيح i;
	    c_فرچ_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, true, true);
	    unsigned صحيح nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    إذا (nargs == 0)
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (vec_safe_length (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		فرچ.set_error ();
		اكسر;
	      }
	    unsigned صحيح لمب_functions = vec_safe_length (cexpr_list) - nargs;
	    إذا (لمب_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		فرچ.set_error ();
		اكسر;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    لكل (unsigned صحيح j = 1; j < لمب_functions; j++)
	      {
		unsigned صحيح this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		إذا (this_nargs == 0)
		  {
		    فرچ.set_error ();
		    اذهب out;
		  }
		إذا (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    فرچ.set_error ();
		    اذهب out;
		  }
	      }

	    /* The functions all have the same number of arguments.
	       Determine whether arguments and return types vary in
	       ways permitted for <tgmath.h> functions.  */
	    /* The first entry in each of these vectors is for the
	       return type, subsequent entries for parameter
	       types.  */
	    auto_vec<تعداد tgmath_parm_kind> parm_kind (nargs + 1);
	    auto_vec<بشيا> parm_first (nargs + 1);
	    auto_vec<منطقي> parm_complex (nargs + 1);
	    auto_vec<منطقي> parm_varies (nargs + 1);
	    بشيا first_type = بشيا_TYPE (بشيا_TYPE ((*cexpr_list)[0].درج));
	    بشيا first_ret = TYPE_MAIN_VARIANT (بشيا_TYPE (first_type));
	    parm_first.quick_تور (first_ret);
	    parm_complex.quick_تور (بشيا_CODE (first_ret) == COMPLEX_TYPE);
	    parm_varies.quick_تور (خطأ);
	    function_حجوجي_iterator iter;
	    بشيا t;
	    unsigned صحيح argpos;
	    FOREACH_FUNCTION_حجوجي (first_type, t, iter)
	      {
		إذا (t == void_type_كلي)
		  اكسر;
		parm_first.quick_تور (TYPE_MAIN_VARIANT (t));
		parm_complex.quick_تور (بشيا_CODE (t) == COMPLEX_TYPE);
		parm_varies.quick_تور (خطأ);
	      }
	    لكل (unsigned صحيح j = 1; j < لمب_functions; j++)
	      {
		بشيا type = بشيا_TYPE (بشيا_TYPE ((*cexpr_list)[j].درج));
		بشيا ret = TYPE_MAIN_VARIANT (بشيا_TYPE (type));
		إذا (ret != parm_first[0])
		  {
		    parm_varies[0] = true;
		    إذا (!SCALAR_FLOAT_TYPE_P (parm_first[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_first[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			فرچ.set_error ();
			اذهب out;
		      }
		    إذا (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			فرچ.set_error ();
			اذهب out;
		      }
		  }
		إذا (بشيا_CODE (ret) == COMPLEX_TYPE)
		  parm_complex[0] = true;
		argpos = 1;
		FOREACH_FUNCTION_حجوجي (type, t, iter)
		  {
		    إذا (t == void_type_كلي)
		      اكسر;
		    t = TYPE_MAIN_VARIANT (t);
		    إذا (t != parm_first[argpos])
		      {
			parm_varies[argpos] = true;
			إذا (!SCALAR_FLOAT_TYPE_P (parm_first[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_first[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    فرچ.set_error ();
			    اذهب out;
			  }
			إذا (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    فرچ.set_error ();
			    اذهب out;
			  }
		      }
		    إذا (بشيا_CODE (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = true;
		    argpos++;
		  }
	      }
	    تعداد tgmath_parm_kind max_variation = tgmath_fixed;
	    لكل (unsigned صحيح j = 0; j <= nargs; j++)
	      {
		تعداد tgmath_parm_kind this_kind;
		إذا (parm_varies[j])
		  {
		    إذا (parm_complex[j])
		      max_variation = this_kind = tgmath_complex;
		    وإلا
		      {
			this_kind = tgmath_real;
			إذا (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		وإلا
		  this_kind = tgmath_fixed;
		parm_kind.quick_تور (this_kind);
	      }
	    إذا (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		فرچ.set_error ();
		اكسر;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    unsigned صحيح tgarg = 0;
	    لكل (unsigned صحيح j = 1; j <= nargs; j++)
	      إذا (parm_kind[j] == max_variation)
		{
		  tgarg = j;
		  اكسر;
		}
	    إذا (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		فرچ.set_error ();
		اكسر;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<بشيا> tg_type (لمب_functions);
	    لكل (unsigned صحيح j = 0; j < لمب_functions; j++)
	      {
		بشيا type = بشيا_TYPE (بشيا_TYPE ((*cexpr_list)[j].درج));
		argpos = 1;
		FOREACH_FUNCTION_حجوجي (type, t, iter)
		  {
		    إذا (argpos == tgarg)
		      {
			tg_type.quick_تور (TYPE_MAIN_VARIANT (t));
			اكسر;
		      }
		    argpos++;
		  }
	      }

	    /* Verify that the corresponding types are different for
	       all the listed functions.  Also determine whether all
	       the types are complex, whether all the types are
	       standard or binary, and whether all the types are
	       decimal.  */
	    منطقي all_complex = true;
	    منطقي all_نبيو = true;
	    منطقي all_decimal = true;
	    hash_set<بشيا> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		إذا (بشيا_CODE (t) == COMPLEX_TYPE)
		  all_decimal = خطأ;
		وإلا
		  {
		    all_complex = خطأ;
		    إذا (DECIMAL_FLOAT_TYPE_P (t))
		      all_نبيو = خطأ;
		    وإلا
		      all_decimal = خطأ;
		  }
		إذا (tg_types.add (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    فرچ.set_error ();
		    اذهب out;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    لكل (unsigned صحيح j = 0; j < لمب_functions; j++)
	      {
		بشيا exp_type = tg_type[j];
		بشيا exp_real_type = exp_type;
		إذا (بشيا_CODE (exp_type) == COMPLEX_TYPE)
		  exp_real_type = بشيا_TYPE (exp_type);
		بشيا type = بشيا_TYPE (بشيا_TYPE ((*cexpr_list)[j].درج));
		بشيا ret = TYPE_MAIN_VARIANT (بشيا_TYPE (type));
		إذا ((parm_kind[0] == tgmath_complex && ret != exp_type)
		    || (parm_kind[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    فرچ.set_error ();
		    اذهب out;
		  }
		argpos = 1;
		FOREACH_FUNCTION_حجوجي (type, t, iter)
		  {
		    إذا (t == void_type_كلي)
		      اكسر;
		    t = TYPE_MAIN_VARIANT (t);
		    إذا ((parm_kind[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_kind[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			فرچ.set_error ();
			اذهب out;
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
	    منطقي arg_complex = all_complex;
	    منطقي arg_نبيو = all_نبيو;
	    منطقي arg_int_decimal = all_decimal;
	    منطقي arg_int_floatnx = خطأ;
	    منطقي arg_int_decimalx = خطأ;
	    لكل (unsigned صحيح j = 1; j <= nargs; j++)
	      {
		إذا (parm_kind[j] == tgmath_fixed)
		  استمر;
		c_فرچ_t *ce = &(*cexpr_list)[لمب_functions + j - 1];
		بشيا type = بشيا_TYPE (ce->درج);
		إذا (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && بشيا_CODE (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    فرچ.set_error ();
		    اذهب out;
		  }
		إذا (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = true;
		    إذا (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			فرچ.set_error ();
			اذهب out;
		      }
		    وإلا إذا (all_نبيو)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			فرچ.set_error ();
			اذهب out;
		      }
		    وإلا إذا (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			فرچ.set_error ();
			اذهب out;
		      }
		    وإلا إذا (arg_نبيو)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			فرچ.set_error ();
			اذهب out;
		      }
		  }
		وإلا إذا (بشيا_CODE (type) == COMPLEX_TYPE)
		  {
		    arg_complex = true;
		    إذا (COMPLEX_FLOAT_TYPE_P (type))
		      arg_نبيو = true;
		    إذا (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			فرچ.set_error ();
			اذهب out;
		      }
		    وإلا إذا (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			فرچ.set_error ();
			اذهب out;
		      }
		  }
		وإلا إذا (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_نبيو = true;
		    إذا (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			فرچ.set_error ();
			اذهب out;
		      }
		    وإلا إذا (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			فرچ.set_error ();
			اذهب out;
		      }
		  }
		بشيا rtype = TYPE_MAIN_VARIANT (type);
		إذا (بشيا_CODE (rtype) == COMPLEX_TYPE)
		  rtype = بشيا_TYPE (rtype);
		إذا (SCALAR_FLOAT_TYPE_P (rtype))
		  لكل (unsigned صحيح j = 0; j < لمب_FLOATNX_TYPES; j++)
		    إذا (rtype == FLOATNX_TYPE_كلي (j))
		      {
			arg_int_floatnx = true;
			اكسر;
		      }
		إذا (rtype == dfloat64x_type_كلي)
		  arg_int_decimalx = true;
	      }
	    بشيا arg_real = NULL_بشيا;
	    لكل (unsigned صحيح j = 1; j <= nargs; j++)
	      {
		إذا (parm_kind[j] == tgmath_fixed)
		  استمر;
		c_فرچ_t *ce = &(*cexpr_list)[لمب_functions + j - 1];
		بشيا type = TYPE_MAIN_VARIANT (بشيا_TYPE (ce->درج));
		إذا (بشيا_CODE (type) == COMPLEX_TYPE)
		  type = بشيا_TYPE (type);
		إذا (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_كلي
			  : arg_int_floatnx
			  ? float32x_type_كلي
			  : arg_int_decimal
			  ? dfloat64_type_كلي
			  : double_type_كلي);
		إذا (arg_real == NULL_بشيا)
		  arg_real = type;
		وإلا
		  arg_real = common_type (arg_real, type);
		إذا (arg_real == error_mark_كلي)
		  {
		    فرچ.set_error ();
		    اذهب out;
		  }
	      }
	    بشيا arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_فرچ_t *fn = عدم;
	    لكل (unsigned صحيح j = 0; j < لمب_functions; j++)
	      {
		إذا (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    اكسر;
		  }
	      }
	    إذا (fn == عدم
		&& parm_kind[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_first[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		لكل (unsigned صحيح j = 0; j < لمب_functions; j++)
		  {
		    إذا (arg_complex
			!= (بشيا_CODE (tg_type[j]) == COMPLEX_TYPE))
		      استمر;
		    بشيا real_tg_type = (arg_complex
					 ? بشيا_TYPE (tg_type[j])
					 : tg_type[j]);
		    إذا (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      استمر;
		    scalar_float_mode arg_mode
		      = SCALAR_FLOAT_TYPE_MODE (arg_real);
		    scalar_float_mode tg_mode
		      = SCALAR_FLOAT_TYPE_MODE (real_tg_type);
		    ثابت real_format *arg_fmt = REAL_MODE_FORMAT (arg_mode);
		    ثابت real_format *tg_fmt = REAL_MODE_FORMAT (tg_mode);
		    إذا (arg_fmt->b == tg_fmt->b
			&& arg_fmt->p <= tg_fmt->p
			&& arg_fmt->emax <= tg_fmt->emax
			&& (arg_fmt->emin - arg_fmt->p
			    >= tg_fmt->emin - tg_fmt->p))
		      {
			fn = &(*cexpr_list)[j];
			اكسر;
		      }
		  }
	      }
	    إذا (fn == عدم)
	      {
		error_at (loc, "no matching function for type-generic call");
		فرچ.set_error ();
		اكسر;
	      }

	    /* Construct a call to FN.  */
	    vec<بشيا, va_gc> *حجوجي;
	    vec_alloc (حجوجي, nargs);
	    vec<بشيا, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    لكل (unsigned صحيح j = 0; j < nargs; j++)
	      {
		c_فرچ_t *ce = &(*cexpr_list)[لمب_functions + j];
		حجوجي->quick_تور (ce->درج);
		arg_loc.quick_تور (ce->get_location ());
		origtypes->quick_تور (ce->original_type);
	      }
	    فرچ.درج = c_build_function_call_vec (loc, arg_loc, fn->درج,
						    حجوجي, origtypes);
	    set_c_فرچ_source_range (&فرچ, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_فرچ_t, va_gc> *cexpr_list;
	    c_فرچ_t *e2_p;
	    بشيا chain_درج;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_حجوجي (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		فرچ.set_error ();
		اكسر;
	      }

	    فرچ = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, true, true);
	    chain_درج = e2_p->درج;
	    mark_exp_read (chain_درج);

	    إذا (بشيا_CODE (فرچ.درج) != CALL_فرچ)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    وإلا إذا (بشيا_CODE (بشيا_TYPE (chain_درج)) != POINTER_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    وإلا
	      CALL_فرچ_STATIC_CHAIN (فرچ.درج) = chain_درج;
	    set_c_فرچ_source_range (&فرچ, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_COMPLEX:
	  {
	    vec<c_فرچ_t, va_gc> *cexpr_list;
	    c_فرچ_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_حجوجي (parser,
					    "__builtin_complex",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		فرچ.set_error ();
		اكسر;
	      }

	    إذا (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		فرچ.set_error ();
		اكسر;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_to_rvalue (loc, *e1_p, true, true);
	    إذا (بشيا_CODE (e1_p->درج) == EXCESS_PRECISION_فرچ)
	      e1_p->درج = convert (بشيا_TYPE (e1_p->درج),
				     بشيا_OPERAND (e1_p->درج, 0));
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, true, true);
	    إذا (بشيا_CODE (e2_p->درج) == EXCESS_PRECISION_فرچ)
	      e2_p->درج = convert (بشيا_TYPE (e2_p->درج),
				     بشيا_OPERAND (e2_p->درج, 0));
	    إذا (!SCALAR_FLOAT_TYPE_P (بشيا_TYPE (e1_p->درج))
		|| DECIMAL_FLOAT_TYPE_P (بشيا_TYPE (e1_p->درج))
		|| !SCALAR_FLOAT_TYPE_P (بشيا_TYPE (e2_p->درج))
		|| DECIMAL_FLOAT_TYPE_P (بشيا_TYPE (e2_p->درج)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (TYPE_MAIN_VARIANT (بشيا_TYPE (e1_p->درج))
		!= TYPE_MAIN_VARIANT (بشيا_TYPE (e2_p->درج)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		فرچ.set_error ();
		اكسر;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    فرچ.درج = build2_loc (loc, COMPLEX_فرچ,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (بشيا_TYPE (e1_p->درج))),
				     e1_p->درج, e2_p->درج);
	    set_c_فرچ_source_range (&فرچ, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_فرچ_t, va_gc> *cexpr_list;
	    c_فرچ_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_حجوجي (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		فرچ.set_error ();
		اكسر;
	      }

	    e_p = &(*cexpr_list)[0];
	    بشيا ref = e_p->درج;

	    إذا (بشيا_CODE (بشيا_TYPE (ref)) != ARRAY_TYPE
		 && بشيا_CODE (بشيا_TYPE (ref)) != POINTER_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		فرچ.set_error ();
		اكسر;
	      }

	    إذا (بشيا_CODE (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		فرچ.set_error ();
		اكسر;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    إذا (بشيا_CODE (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    إذا (has_counted_by_object (ref))
	      فرچ.درج = get_counted_by_ref (ref);
	    وإلا
	      فرچ.درج = null_pointer_كلي;

	    set_c_فرچ_source_range (&فرچ, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_فرچ_t, va_gc> *cexpr_list;
	    unsigned صحيح i;
	    c_فرچ_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_حجوجي (parser,
					    "__builtin_shuffle",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		فرچ.set_error ();
		اكسر;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, true, true);

	    إذا (vec_safe_length (cexpr_list) == 2)
	      فرچ.درج = c_build_vec_perm_فرچ (loc, (*cexpr_list)[0].درج,
						  NULL_بشيا,
						  (*cexpr_list)[1].درج);

	    وإلا إذا (vec_safe_length (cexpr_list) == 3)
	      فرچ.درج = c_build_vec_perm_فرچ (loc, (*cexpr_list)[0].درج,
						  (*cexpr_list)[1].درج,
						  (*cexpr_list)[2].درج);
	    وإلا
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		فرچ.set_error ();
	      }
	    set_c_فرچ_source_range (&فرچ, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_فرچ_t, va_gc> *cexpr_list;
	    unsigned صحيح i;
	    c_فرچ_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_حجوجي (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		فرچ.set_error ();
		اكسر;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, true, true);

	    إذا (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		فرچ.set_error ();
	      }
	    وإلا
	      {
		auto_vec<بشيا, 16> mask;
		لكل (i = 2; i < cexpr_list->length (); ++i)
		  mask.safe_تور ((*cexpr_list)[i].درج);
		فرچ.درج = c_build_shufflevector (loc, (*cexpr_list)[0].درج,
						    (*cexpr_list)[1].درج,
						    mask);
	      }
	    set_c_فرچ_source_range (&فرچ, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    e1 = c_parser_فرچ_no_commas (parser, عدم);
	    mark_exp_read (e1.درج);
	    إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
		فرچ.set_error ();
		اكسر;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    إذا (t1 == عدم)
	      فرچ.set_error ();
	    وإلا
	      {
		بشيا type_فرچ = NULL_بشيا;
		فرچ.درج = c_build_vec_convert (start_loc, e1.درج, loc,
						  groktypename (t1, &type_فرچ,
								عدم));
		set_c_فرچ_source_range (&فرچ, start_loc, end_loc);
	      }
	  }
	  اكسر;
	حالة RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    e1 = c_parser_فرچ_no_commas (parser, عدم);
	    mark_exp_read (e1.درج);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    parens.skip_until_found_close (parser);
	    فرچ = parser_build_unary_op (loc, PAREN_فرچ, e1);
	    set_c_فرچ_source_range (&فرچ, start_loc, end_loc);
	  }
	  اكسر;
	حالة RID_BUILTIN_STDC:
	  {
	    vec<c_فرچ_t, va_gc> *cexpr_list;
	    c_فرچ_t *arg_p;
	    location_t close_paren_loc;
	    تعداد c_builtin_stdc {
	      C_BUILTIN_STDC_BIT_CEIL,
	      C_BUILTIN_STDC_BIT_FLOOR,
	      C_BUILTIN_STDC_BIT_WIDTH,
	      C_BUILTIN_STDC_كدي_ONES,
	      C_BUILTIN_STDC_كدي_ZEROS,
	      C_BUILTIN_STDC_FIRST_LEADING_ONE,
	      C_BUILTIN_STDC_FIRST_LEADING_ZERO,
	      C_BUILTIN_STDC_FIRST_TRAILING_ONE,
	      C_BUILTIN_STDC_FIRST_TRAILING_ZERO,
	      C_BUILTIN_STDC_HAS_SINGLE_BIT,
	      C_BUILTIN_STDC_LEADING_ONES,
	      C_BUILTIN_STDC_LEADING_ZEROS,
	      C_BUILTIN_STDC_ROTATE_هغو,
	      C_BUILTIN_STDC_ROTATE_دام,
	      C_BUILTIN_STDC_TRAILING_ONES,
	      C_BUILTIN_STDC_TRAILING_ZEROS,
	      C_BUILTIN_STDC_MAX
	    } stdc_rid = C_BUILTIN_STDC_MAX;
	    ثابت حرف *name
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
	    unsigned لمب_حجوجي = 1;
	    بدل (name[حجم ("__builtin_stdc_") - 1])
	      {
	      حالة 'b':
		بدل (name[حجم ("__builtin_stdc_bit_") - 1])
		  {
		  حالة 'c':
		    stdc_rid = C_BUILTIN_STDC_BIT_CEIL;
		    اكسر;
		  حالة 'f':
		    stdc_rid = C_BUILTIN_STDC_BIT_FLOOR;
		    اكسر;
		  افتراضي:
		    stdc_rid = C_BUILTIN_STDC_BIT_WIDTH;
		    اكسر;
		  }
		اكسر;
	      حالة 'c':
		إذا (name[حجم ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_كدي_ONES;
		وإلا
		  stdc_rid = C_BUILTIN_STDC_كدي_ZEROS;
		اكسر;
	      حالة 'f':
		بدل (name[حجم ("__builtin_stdc_first_trailing_") - 1])
		  {
		  حالة 'n':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ONE;
		    اكسر;
		  حالة 'e':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ZERO;
		    اكسر;
		  حالة 'o':
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ONE;
		    اكسر;
		  افتراضي:
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ZERO;
		    اكسر;
		  }
		اكسر;
	      حالة 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_BIT;
		اكسر;
	      حالة 'l':
		إذا (name[حجم ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		وإلا
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		اكسر;
	      حالة 'r':
		إذا (name[حجم ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_هغو;
		وإلا
		  stdc_rid = C_BUILTIN_STDC_ROTATE_دام;
		لمب_حجوجي = 2;
		اكسر;
	      حالة 't':
		إذا (name[حجم ("__builtin_stdc_trailing_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ONES;
		وإلا
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ZEROS;
		اكسر;
	      }
	    gcc_checking_assert (stdc_rid != C_BUILTIN_STDC_MAX);

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_حجوجي (parser, name,
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		فرچ.set_error ();
		اكسر;
	      }

	    إذا (vec_safe_length (cexpr_list) != لمب_حجوجي)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		فرچ.set_error ();
		اكسر;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, true, true);
	    إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (arg_p->درج)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (بشيا_CODE (بشيا_TYPE (arg_p->درج)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (بشيا_CODE (بشيا_TYPE (arg_p->درج)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (!TYPE_UNSIGNED (بشيا_TYPE (arg_p->درج)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (TYPE_MAIN_VARIANT (بشيا_TYPE (arg_p->درج))
		== char_type_كلي)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		فرچ.set_error ();
		اكسر;
	      }
	    بشيا arg = arg_p->درج;
	    بشيا type = TYPE_MAIN_VARIANT (بشيا_TYPE (arg));
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
	    صحيح prec = TYPE_PRECISION (type);
	    إذا (لمب_حجوجي == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_to_rvalue (loc, *arg_p, true, true);
		إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (arg_p->درج)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    فرچ.set_error ();
		    اكسر;
		  }
		إذا (بشيا_CODE (بشيا_TYPE (arg_p->درج)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    فرچ.set_error ();
		    اكسر;
		  }
		بشيا arg1 = save_فرچ (arg);
		بشيا arg2 = save_فرچ (arg_p->درج);
		بشيا_code code;
		إذا (stdc_rid == C_BUILTIN_STDC_ROTATE_هغو)
		  code = LROTATE_فرچ;
		وإلا
		  code = RROTATE_فرچ;

		إذا (بشيا_CODE (arg2) == INTEGER_CST
		    && بشيا_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_كدي_negative,
			      "rotate count is negative");

		بشيا instrument_فرچ = NULL_بشيا;
		إذا (sanitize_flags_p (SANITIZE_SHIFT))
		  instrument_فرچ = ubsan_instrument_shift (loc, code,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		إذا (TYPE_PRECISION (بشيا_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_كلي))
		  arg2 = fold_convert (unsigned_type_كلي, arg2);

		إذا (TYPE_UNSIGNED (بشيا_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_فرچ, بشيا_TYPE (arg2),
				     arg2, build_int_cst (بشيا_TYPE (arg2),
							  prec));
		وإلا
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    بشيا utype = c_common_unsigned_type (بشيا_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_فرچ, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		إذا (type_has_mode_precision_p (بشيا_TYPE (arg1))
		    || (بشيا_CODE (بشيا_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_MODE_SIZE))
		  فرچ.درج = build2_loc (loc, code, بشيا_TYPE (arg1), arg1,
					   arg2);
		وإلا
		  {
		    arg2 = save_فرچ (arg2);
		    بشيا t1 = build2_loc (loc, (code == LROTATE_فرچ
						? LSHIFT_فرچ : RSHIFT_فرچ),
					  بشيا_TYPE (arg1), arg1, arg2);
		    بشيا t2 = build2_loc (loc, MINUS_فرچ,
					  بشيا_TYPE (arg2),
					  build_int_cst (بشيا_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (code == LROTATE_فرچ
					   ? RSHIFT_فرچ : LSHIFT_فرچ),
				     بشيا_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_كدي_overflow);
		    بشيا t3 = build2_loc (loc, BIT_IOR_فرچ,
					  بشيا_TYPE (arg1), t1, t2);
		    بشيا t4 = build2_loc (loc, NE_فرچ, boolean_type_كلي,
					  arg2,
					  build_zero_cst (بشيا_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_فرچ, boolean_type_كلي,
				     arg1, t4);
		    فرچ.درج = build3_loc (loc, COND_فرچ,
					     بشيا_TYPE (arg1), t4, t3, arg1);
		  }
		إذا (instrument_فرچ)
		  فرچ.درج = build2_loc (loc, COMPOUND_فرچ,
					   بشيا_TYPE (فرچ.درج),
					   instrument_فرچ, فرچ.درج);
		set_c_فرچ_source_range (&فرچ, loc, close_paren_loc);
		اكسر;
	      }
	    بشيا barg1 = arg;
	    بدل (stdc_rid)
	      {
	      حالة C_BUILTIN_STDC_BIT_CEIL:
		arg = save_فرچ (arg);
		barg1 = build2_loc (loc, PLUS_فرچ, type, arg,
				    build_int_cst (type, -1));
		اكسر;
	      حالة C_BUILTIN_STDC_BIT_FLOOR:
		barg1 = arg = save_فرچ (arg);
		اكسر;
	      حالة C_BUILTIN_STDC_كدي_ZEROS:
	      حالة C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      حالة C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      حالة C_BUILTIN_STDC_LEADING_ONES:
	      حالة C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, BIT_NOT_فرچ, type, arg);
		اكسر;
	      افتراضي:
		اكسر;
	      }
	    بشيا barg2 = NULL_بشيا;
	    بدل (stdc_rid)
	      {
	      حالة C_BUILTIN_STDC_BIT_WIDTH:
	      حالة C_BUILTIN_STDC_LEADING_ONES:
	      حالة C_BUILTIN_STDC_LEADING_ZEROS:
	      حالة C_BUILTIN_STDC_TRAILING_ONES:
	      حالة C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_كلي, prec);
		اكسر;
	      حالة C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      حالة C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      حالة C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      حالة C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		barg2 = integer_minus_one_كلي;
		اكسر;
	      افتراضي:
		اكسر;
	      }
	    بشيا fndecl = NULL_بشيا;
	    بدل (stdc_rid)
	      {
	      حالة C_BUILTIN_STDC_BIT_CEIL:
	      حالة C_BUILTIN_STDC_BIT_FLOOR:
	      حالة C_BUILTIN_STDC_BIT_WIDTH:
	      حالة C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      حالة C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      حالة C_BUILTIN_STDC_LEADING_ONES:
	      حالة C_BUILTIN_STDC_LEADING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CLZG);
		اكسر;
	      حالة C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      حالة C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      حالة C_BUILTIN_STDC_TRAILING_ONES:
	      حالة C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CTZG);
		اكسر;
	      حالة C_BUILTIN_STDC_كدي_ONES:
	      حالة C_BUILTIN_STDC_كدي_ZEROS:
	      حالة C_BUILTIN_STDC_HAS_SINGLE_BIT:
		fndecl = builtin_decl_explicit (BUILT_IN_POPCOUNTG);
		اكسر;
	      افتراضي:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    صحيح nargs = barg2 != NULL_بشيا ? 2 : 1;
	    vec<بشيا, va_gc> *حجوجي;
	    vec_alloc (حجوجي, nargs);
	    vec<بشيا, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    حجوجي->quick_تور (barg1);
	    arg_loc.quick_تور (arg_p->get_location ());
	    origtypes->quick_تور (arg_p->original_type);
	    إذا (nargs == 2)
	      {
		حجوجي->quick_تور (barg2);
		arg_loc.quick_تور (loc);
		origtypes->quick_تور (integer_type_كلي);
	      }
	    فرچ.درج = c_build_function_call_vec (loc, arg_loc, fndecl,
						    حجوجي, origtypes);
	    set_c_فرچ_source_range (&فرچ, loc, close_paren_loc);
	    إذا (فرچ.درج == error_mark_كلي)
	      اكسر;
	    بدل (stdc_rid)
	      {
	      حالة C_BUILTIN_STDC_BIT_CEIL:
	      حالة C_BUILTIN_STDC_BIT_FLOOR:
		--prec;
		/* FALLTHRU */
	      حالة C_BUILTIN_STDC_BIT_WIDTH:
		فرچ.درج = build2_loc (loc, MINUS_فرچ, integer_type_كلي,
					 build_int_cst (integer_type_كلي,
							prec), فرچ.درج);
		اكسر;
	      حالة C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      حالة C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      حالة C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      حالة C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		فرچ.درج = build2_loc (loc, PLUS_فرچ, integer_type_كلي,
					 فرچ.درج, integer_one_كلي);
		اكسر;
	      حالة C_BUILTIN_STDC_HAS_SINGLE_BIT:
		فرچ.درج = build2_loc (loc, EQ_فرچ, boolean_type_كلي,
					 فرچ.درج, integer_one_كلي);
		اكسر;
	      افتراضي:
		اكسر;
	      }

	    إذا (stdc_rid != C_BUILTIN_STDC_BIT_CEIL
		&& stdc_rid != C_BUILTIN_STDC_BIT_FLOOR)
	      {
		إذا (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_BIT)
		  فرچ.درج = fold_convert_loc (loc, unsigned_type_كلي,
						 فرچ.درج);
		اكسر;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    إذا (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_BIT_CEIL && integer_onep (arg)))
	      فرچ.درج = build_int_cst (type, 0);
	    وإلا
	      فرچ.درج
		= build2_loc (loc, LSHIFT_فرچ, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_BIT_CEIL
					      ? 2 : 1)), فرچ.درج);
	    إذا (stdc_rid == C_BUILTIN_STDC_BIT_CEIL)
	      فرچ.درج = build3_loc (loc, COND_فرچ, type,
				       build2_loc (loc, LE_فرچ,
						   boolean_type_كلي, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       فرچ.درج);
	    وإلا
	      فرچ.درج = build3_loc (loc, COND_فرچ, type,
				       build2_loc (loc, EQ_فرچ,
						   boolean_type_كلي, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       فرچ.درج);
	    اكسر;
	  }
	حالة RID_BUILTIN_BSWAPG:
	حالة RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_فرچ_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    internal_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    ثابت حرف *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_حجوجي (parser, name, &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		فرچ.set_error ();
		اكسر;
	      }

	    إذا (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		فرچ.set_error ();
		اكسر;
	      }

	    c_فرچ_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, true, true);
	    بشيا arg = arg_p->درج;
	    إذا (error_operand_p (arg))
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    بشيا type = TYPE_MAIN_VARIANT (بشيا_TYPE (arg));
	    إذا (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (بشيا_CODE (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (بشيا_CODE (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		فرچ.set_error ();
		اكسر;
	      }
	    arg = c_fully_fold (arg, خطأ, عدم);
	    فرچ.درج = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    set_c_فرچ_source_range (&فرچ, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    بشيا sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    فرچ.درج = objc_build_selector_فرچ (loc, sel);
	    set_c_فرچ_source_range (&فرچ, loc, close_loc);
	  }
	  اكسر;
	حالة RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    إذا (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
		فرچ.set_error ();
		اكسر;
	      }
	    بشيا id = c_parser_peek_token (parser)->درج;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    فرچ.درج = objc_build_protocol_فرچ (id);
	    set_c_فرچ_source_range (&فرچ, loc, close_loc);
	  }
	  اكسر;
	حالة RID_AT_ENCODE:
	  {
	    /* Extension to support C-structures in the archiver.  */
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		فرچ.set_error ();
		اكسر;
	      }
	    t1 = c_parser_type_name (parser);
	    إذا (t1 == عدم)
	      {
		فرچ.set_error ();
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
		اكسر;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    بشيا type = groktypename (t1, عدم, عدم);
	    فرچ.درج = objc_build_encode_فرچ (type);
	    set_c_فرچ_source_range (&فرچ, loc, close_loc);
	  }
	  اكسر;
	حالة RID_GENERIC:
	  فرچ = c_parser_generic_selection (parser);
	  اكسر;
	حالة RID_OMP_ALL_MEMORY:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  فرچ.set_error ();
	  اكسر;
	/* C23 'nullptr' literal.  */
	حالة RID_NULLPTR:
	  c_parser_consume_token (parser);
	  فرچ.درج = nullptr_كلي;
	  set_c_فرچ_source_range (&فرچ, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  اكسر;
	حالة RID_TRUE:
	  c_parser_consume_token (parser);
	  فرچ.درج = boolean_true_كلي;
	  set_c_فرچ_source_range (&فرچ, tok_range);
	  اكسر;
	حالة RID_FALSE:
	  c_parser_consume_token (parser);
	  فرچ.درج = boolean_false_كلي;
	  set_c_فرچ_source_range (&فرچ, tok_range);
	  اكسر;
	افتراضي:
	  c_parser_error (parser, "expected expression");
	  فرچ.set_error ();
	  اكسر;
	}
      اكسر;
    حالة CPP_OPEN_SQUARE:
      إذا (c_dialect_objc ())
	{
	  بشيا receiver, حجوجي;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  حجوجي = c_parser_objc_message_حجوجي (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  فرچ.درج = objc_build_message_فرچ (receiver, حجوجي);
	  set_c_فرچ_source_range (&فرچ, loc, close_loc);
	  اكسر;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    افتراضي:
      c_parser_error (parser, "expected expression");
      فرچ.set_error ();
      اكسر;
    }
 out:
  أرجع c_parser_postfix_expression_after_primary
    (parser, فرچ_LOC_OR_LOC (فرچ.درج, loc), فرچ);
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

ساكن بنية c_فرچ
c_parser_postfix_expression_after_paren_type (c_parser *parser,
					      بنية c_declspecs *scspecs,
					      بنية c_type_name *type_name,
					      location_t type_loc)
{
  بشيا type;
  بنية c_فرچ init;
  منطقي non_const;
  بنية c_فرچ فرچ;
  location_t start_loc;
  بشيا type_فرچ = NULL_بشيا;
  منطقي type_فرچ_const = true;
  منطقي constexpr_p = scspecs ? scspecs->constexpr_p : خطأ;
  unsigned صحيح underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (لي_table, type_loc);
  start_loc = c_parser_peek_token (parser)->location;
  إذا (constexpr_p)
    {
      underspec_state = start_underspecified_init (start_loc, NULL_بشيا);
      /* A constexpr compound literal is subject to the constraints on
	 underspecified declarations, which may not declare tags or
	 members or structures or unions; it is undefined behavior to
	 declare the members of an enumeration.  Where the structure,
	 union or enumeration type is declared within the compound
	 literal initializer, this is diagnosed elsewhere as a result
	 of the above call to start_underspecified_init.  Diagnose
	 here the case of declaring such a type in the type specifiers
	 of the compound literal.  */
      بدل (type_name->specs->typespec_kind)
	{
	حالة ctsk_tagfirstref:
	حالة ctsk_tagfirstref_attrs:
	  error_at (type_loc, "%qT declared in %<constexpr%> compound literal",
		    type_name->specs->type);
	  اكسر;

	حالة ctsk_tagdef:
	  error_at (type_loc, "%qT defined in %<constexpr%> compound literal",
		    type_name->specs->type);
	  اكسر;

	افتراضي:
	  اكسر;
	}
    }
  start_init (NULL_بشيا, عدم,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_فرچ, &type_فرچ_const);
  منطقي varsize_p = خطأ;
  إذا (type != error_mark_كلي && C_TYPE_VARIABLE_SIZE (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = true;
    }
  وإلا إذا (بشيا_CODE (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_كلي;
    }
  إذا (constexpr_p && type != error_mark_كلي)
    {
      بشيا type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      إذا (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      وإلا إذا (RECORD_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, خطأ, عدم, varsize_p);
  إذا (constexpr_p)
    finish_underspecified_init (NULL_بشيا, underspec_state);
  finish_init ();
  maybe_warn_string_init (type_loc, type, init);

  إذا (type != error_mark_كلي
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_كلي;
    }

  إذا (!pedwarn_c90 (start_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (start_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.درج && بشيا_CODE (init.درج) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.درج)
	       : init.original_code == C_MAYBE_CONST_فرچ);
  non_const |= !type_فرچ_const;
  unsigned صحيح alignas_align = 0;
  إذا (type != error_mark_كلي
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      إذا (alignas_align < min_align_of_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  فرچ.درج = build_compound_literal (start_loc, type, init.درج, non_const,
				       alignas_align, scspecs);
  set_c_فرچ_source_range (&فرچ, init.src_range);
  فرچ.m_decimal = 0;
  فرچ.original_code = ERROR_MARK;
  فرچ.original_type = عدم;
  إذا (type != error_mark_كلي
      && فرچ.درج != error_mark_كلي
      && type_فرچ)
    {
      إذا (بشيا_CODE (فرچ.درج) == C_MAYBE_CONST_فرچ)
	{
	  gcc_assert (C_MAYBE_CONST_فرچ_PRE (فرچ.درج) == NULL_بشيا);
	  C_MAYBE_CONST_فرچ_PRE (فرچ.درج) = type_فرچ;
	}
      وإلا
	{
	  gcc_assert (!non_const);
	  فرچ.درج = build2 (C_MAYBE_CONST_فرچ, type,
			       type_فرچ, فرچ.درج);
	}
    }
  أرجع c_parser_postfix_expression_after_primary (parser, start_loc, فرچ);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

ساكن منطقي
sizeof_ptr_memacc_comptypes (بشيا type1, بشيا type2)
{
  أرجع comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

ساكن فراغ
warn_for_abs (location_t loc, بشيا fndecl, بشيا arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  إذا (c_inhibit_evaluation_warnings)
    أرجع;

  بشيا atype = بشيا_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  إذا (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && بشيا_CODE (atype) != COMPLEX_TYPE)
    أرجع;

  تعداد built_in_function fcode = DECL_FUNCTION_CODE (fndecl);

  بدل (fcode)
    {
    حالة BUILT_IN_ABS:
    حالة BUILT_IN_LABS:
    حالة BUILT_IN_LLABS:
    حالة BUILT_IN_IMAXABS:
      إذا (!INTEGRAL_TYPE_P (atype))
	{
	  إذا (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_درج,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  وإلا إذا (بشيا_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_درج,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  وإلا
	    gcc_unreachable ();
	  أرجع;
	}
      إذا (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_درج,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      اكسر;

    CASE_FLT_FN (BUILT_IN_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FABS):
      إذا (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_MODE_P (TYPE_MODE (atype)))
	{
	  إذا (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_درج,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  وإلا إذا (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_درج,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  وإلا إذا (بشيا_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_درج,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  وإلا
	    gcc_unreachable ();
	  أرجع;
	}
      اكسر;

    CASE_FLT_FN (BUILT_IN_CABS):
      إذا (بشيا_CODE (atype) != COMPLEX_TYPE)
	{
	  إذا (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_درج,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  وإلا إذا (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_درج,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  وإلا
	    gcc_unreachable ();

	  أرجع;
	}
      اكسر;

    حالة BUILT_IN_FABSD32:
    حالة BUILT_IN_FABSD64:
    حالة BUILT_IN_FABSD128:
    حالة BUILT_IN_FABSD64X:
      إذا (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  إذا (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_درج,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  وإلا إذا (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_درج,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  وإلا إذا (بشيا_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_درج,
			"using decimal floating-point absolute value "
			"function %qD when argument is of complex type %qT",
			fndecl, atype);
	  وإلا
	    gcc_unreachable ();
	  أرجع;
	}
      اكسر;

    افتراضي:
      أرجع;
    }

  إذا (!TYPE_ARG_TYPES (بشيا_TYPE (fndecl)))
    أرجع;

  بشيا ftype = بشيا_درج (TYPE_ARG_TYPES (بشيا_TYPE (fndecl)));
  إذا (بشيا_CODE (atype) == COMPLEX_TYPE)
    {
      gcc_assert (بشيا_CODE (ftype) == COMPLEX_TYPE);
      atype = بشيا_TYPE (atype);
      ftype = بشيا_TYPE (ftype);
    }

  إذا (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_درج,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

ساكن بنية c_فرچ
c_parser_postfix_expression_after_primary (c_parser *parser,
					   location_t فرچ_loc,
					   بنية c_فرچ فرچ)
{
  بنية c_فرچ orig_فرچ;
  بشيا ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  بشيا sizeof_arg[6];
  unsigned صحيح literal_zero_mask;
  unsigned صحيح i;
  vec<بشيا, va_gc> *exprlist;
  vec<بشيا, va_gc> *origtypes = عدم;
  vec<location_t> arg_loc = vNULL;
  location_t start;
  location_t finish;

  طالما (true)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_OPEN_SQUARE:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_بشيا;
	  إذا (!c_omp_array_section_p
	      || c_parser_next_token_is_not (parser, CPP_COLON))
	    idx = c_parser_expression (parser).درج;

	  إذا (c_omp_array_section_p
	      && c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      إذا (c_parser_next_token_is_not (parser, CPP_CLOSE_SQUARE))
		len = c_parser_expression (parser).درج;

	      فرچ.درج = build_omp_array_section (op_loc, فرچ.درج, idx,
						    len);
	    }
	  وإلا
	    فرچ.درج = build_array_ref (op_loc, فرچ.درج, idx);

	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");

	  start = فرچ.get_start ();
	  finish = parser->tokens_buf[0].location;
	  set_c_فرچ_source_range (&فرچ, start, finish);
	  فرچ.original_code = ERROR_MARK;
	  فرچ.original_type = عدم;
	  فرچ.m_decimal = 0;
	  اكسر;
	حالة CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    لكل (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_بشيا;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_mask = 0;
	    إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = عدم;
	    وإلا إذا (بشيا_CODE (فرچ.درج) == FUNCTION_DECL
		     && fndecl_built_in_p (فرچ.درج, BUILT_IN_CLASSIFY_TYPE)
		     && c_parser_next_tokens_start_typename (parser,
							     cla_prefer_id))
	      {
		/* __builtin_classify_type (type)  */
		c_inhibit_evaluation_warnings++;
		in_alignof++;
		بنية c_type_name *type = c_parser_type_name (parser);
		c_inhibit_evaluation_warnings--;
		in_alignof--;
		بنية c_typespec ret;
		ret.فرچ = NULL_بشيا;
		ret.spec = error_mark_كلي;
		ret.فرچ_const_operands = خطأ;
		إذا (type != عدم)
		  ret.spec = groktypename (type, &ret.فرچ,
					   &ret.فرچ_const_operands);
		parens.skip_until_found_close (parser);
		فرچ.درج = build_int_cst (integer_type_كلي,
					    type_to_class (ret.spec));
		اكسر;
	      }
	    وإلا
	      exprlist = c_parser_فرچ_list (parser, true, خطأ, &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_mask);
	    parens.skip_until_found_close (parser);
	  }
	  orig_فرچ = فرچ;
	  mark_exp_read (فرچ.درج);
	  إذا (warn_sizeof_pointer_memaccess)
	    sizeof_pointer_memaccess_warning (sizeof_arg_loc,
					      فرچ.درج, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  إذا (بشيا_CODE (فرچ.درج) == FUNCTION_DECL)
	    {
	      إذا (fndecl_built_in_p (فرچ.درج, BUILT_IN_MEMSET)
		  && vec_safe_length (exprlist) == 3)
		{
		  بشيا arg0 = (*exprlist)[0];
		  بشيا arg2 = (*exprlist)[2];
		  warn_for_memset (فرچ_loc, arg0, arg2, literal_zero_mask);
		}
	      إذا (warn_absolute_درج
		  && fndecl_built_in_p (فرچ.درج, BUILT_IN_NORMAL)
		  && vec_safe_length (exprlist) == 1)
		warn_for_abs (فرچ_loc, فرچ.درج, (*exprlist)[0]);
	      إذا (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->in_intervening_code
		  && omp_runtime_api_call (فرچ.درج))
		{
		  error_at (فرچ_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->fail = true;
		}
	      إذا (warn_calloc_transposed_حجوجي)
		إذا (بشيا attr = lookup_attribute ("alloc_size",
						  TYPE_ATTRIBUTES
						    (بشيا_TYPE (فرچ.درج))))
		  إذا (بشيا_درج (attr) && بشيا_CHAIN (بشيا_درج (attr)))
		    warn_for_calloc (sizeof_arg_loc, فرچ.درج, exprlist,
				     sizeof_arg, attr);
	    }

	  start = فرچ.get_start ();
	  finish = parser->tokens_buf[0].get_finish ();
	  فرچ.درج
	    = c_build_function_call_vec (فرچ_loc, arg_loc, فرچ.درج,
					 exprlist, origtypes);
	  set_c_فرچ_source_range (&فرچ, start, finish);
	  فرچ.m_decimal = 0;

	  فرچ.original_code = ERROR_MARK;
	  إذا (بشيا_CODE (فرچ.درج) == INTEGER_CST
	      && بشيا_CODE (orig_فرچ.درج) == FUNCTION_DECL
	      && fndecl_built_in_p (orig_فرچ.درج, BUILT_IN_CONSTANT_P))
	    فرچ.original_code = C_MAYBE_CONST_فرچ;
	  فرچ.original_type = عدم;
	  إذا (exprlist)
	    {
	      release_بشيا_vector (exprlist);
	      release_بشيا_vector (origtypes);
	    }
	  arg_loc.release ();
	  اكسر;
	حالة CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  فرچ = default_function_array_conversion (فرچ_loc, فرچ);
	  إذا (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->درج;
	      comp_loc = comp_tok->location;
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected identifier");
	      فرچ.set_error ();
	      فرچ.original_code = ERROR_MARK;
              فرچ.original_type = عدم;
	      أرجع فرچ;
	    }
	  start = فرچ.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  فرچ.درج = build_component_ref (op_loc, فرچ.درج, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  set_c_فرچ_source_range (&فرچ, start, finish);
	  فرچ.original_code = ERROR_MARK;
	  إذا (بشيا_CODE (فرچ.درج) != COMPONENT_REF)
	    فرچ.original_type = عدم;
	  وإلا
	    {
	      /* Remember the original type of a bitfield.  */
	      بشيا field = بشيا_OPERAND (فرچ.درج, 1);
	      إذا (بشيا_CODE (field) != FIELD_DECL)
		فرچ.original_type = عدم;
	      وإلا
		فرچ.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  فرچ.m_decimal = 0;
	  اكسر;
	حالة CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, true, خطأ);
	  إذا (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->درج;
	      comp_loc = comp_tok->location;
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected identifier");
	      فرچ.set_error ();
	      فرچ.original_code = ERROR_MARK;
	      فرچ.original_type = عدم;
	      أرجع فرچ;
	    }
	  start = فرچ.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  فرچ.درج = build_component_ref (op_loc,
					    build_indirect_ref (op_loc,
								فرچ.درج,
								RO_ARROW),
					    ident, comp_loc,
					    فرچ.get_location ());
	  set_c_فرچ_source_range (&فرچ, start, finish);
	  فرچ.original_code = ERROR_MARK;
	  إذا (بشيا_CODE (فرچ.درج) != COMPONENT_REF)
	    فرچ.original_type = عدم;
	  وإلا
	    {
	      /* Remember the original type of a bitfield.  */
	      بشيا field = بشيا_OPERAND (فرچ.درج, 1);
	      إذا (بشيا_CODE (field) != FIELD_DECL)
		فرچ.original_type = عدم;
	      وإلا
		فرچ.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  فرچ.m_decimal = 0;
	  اكسر;
	حالة CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  start = فرچ.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (فرچ.درج);
	  فرچ = default_function_array_conversion (فرچ_loc, فرچ);
	  فرچ.درج = build_unary_op (op_loc, POSTINCREMENT_فرچ,
				       فرچ.درج, خطأ);
	  set_c_فرچ_source_range (&فرچ, start, finish);
	  فرچ.original_code = ERROR_MARK;
	  فرچ.original_type = عدم;
	  اكسر;
	حالة CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  start = فرچ.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (فرچ.درج);
	  فرچ = default_function_array_conversion (فرچ_loc, فرچ);
	  فرچ.درج = build_unary_op (op_loc, POSTDECREMENT_فرچ,
				       فرچ.درج, خطأ);
	  set_c_فرچ_source_range (&فرچ, start, finish);
	  فرچ.original_code = ERROR_MARK;
	  فرچ.original_type = عدم;
	  اكسر;
	افتراضي:
	  أرجع فرچ;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

ساكن بنية c_فرچ
c_parser_expression (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  بنية c_فرچ فرچ;
  فرچ = c_parser_فرچ_no_commas (parser, عدم);
  إذا (c_parser_next_token_is (parser, CPP_COMMA))
    فرچ = convert_lvalue_to_rvalue (tloc, فرچ, true, خطأ);
  طالما (c_parser_next_token_is (parser, CPP_COMMA))
    {
      بنية c_فرچ next;
      بشيا lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t فرچ_loc;
      c_parser_consume_token (parser);
      فرچ_loc = c_parser_peek_token (parser)->location;
      lhsval = فرچ.درج;
      طالما (بشيا_CODE (lhsval) == COMPOUND_فرچ
	     || بشيا_CODE (lhsval) == NOP_فرچ)
	{
	  إذا (بشيا_CODE (lhsval) == COMPOUND_فرچ)
	    lhsval = بشيا_OPERAND (lhsval, 1);
	  وإلا
	    lhsval = بشيا_OPERAND (lhsval, 0);
	}
      إذا (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      إذا (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  بشيا val = embed->درج;
	  unsigned last = RAW_DATA_LENGTH (val) - 1;
	  next.درج = build_int_cst (بشيا_TYPE (val),
				      RAW_DATA_UCHAR_ELT (val, last));
	  next.original_type = integer_type_كلي;
	  c_parser_consume_token (parser);
	}
      وإلا
	{
	  next = c_parser_فرچ_no_commas (parser, عدم);
	  next = convert_lvalue_to_rvalue (فرچ_loc, next, true, خطأ);
	}
      فرچ.درج = build_compound_فرچ (loc, فرچ.درج, next.درج);
      فرچ.original_code = COMPOUND_فرچ;
      فرچ.original_type = next.original_type;
      فرچ.m_decimal = 0;
    }
  أرجع فرچ;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

ساكن بنية c_فرچ
c_parser_expression_conv (c_parser *parser)
{
  بنية c_فرچ فرچ;
  location_t loc = c_parser_peek_token (parser)->location;
  فرچ = c_parser_expression (parser);
  فرچ = convert_lvalue_to_rvalue (loc, فرچ, true, خطأ);
  أرجع فرچ;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

ساكن مضمن فراغ
c_parser_check_literal_zero (c_parser *parser, unsigned *literal_zero_mask,
			     unsigned صحيح idx)
{
  إذا (idx >= HOST_BITS_PER_INT)
    أرجع;

  c_token *tok = c_parser_peek_token (parser);
  بدل (tok->type)
    {
    حالة CPP_لمب:
    حالة CPP_CHAR:
    حالة CPP_WCHAR:
    حالة CPP_CHAR16:
    حالة CPP_CHAR32:
    حالة CPP_UTF8CHAR:
      /* If a parameter is literal zero alone, remember it
	 for -Wmemset-transposed-args warning.  */
      إذا (integer_zerop (tok->درج)
	  && !بشيا_OVERFLOW (tok->درج)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_mask |= 1U << idx;
    افتراضي:
      اكسر;
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

ساكن vec<بشيا, va_gc> *
c_parser_فرچ_list (c_parser *parser, منطقي convert_p, منطقي fold_p,
		    vec<بشيا, va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, بشيا *sizeof_arg,
		    vec<location_t> *locations,
		    unsigned صحيح *literal_zero_mask)
{
  vec<بشيا, va_gc> *ret;
  vec<بشيا, va_gc> *orig_types;
  بنية c_فرچ فرچ;
  unsigned صحيح idx = 0;
  منطقي save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = خطأ;

  ret = make_بشيا_vector ();
  إذا (p_orig_types == عدم)
    orig_types = عدم;
  وإلا
    orig_types = make_بشيا_vector ();

  إذا (literal_zero_mask)
    c_parser_check_literal_zero (parser, literal_zero_mask, 0);
  فرچ = c_parser_فرچ_no_commas (parser, عدم);
  إذا (convert_p)
    فرچ = convert_lvalue_to_rvalue (فرچ.get_location (), فرچ, true, true);
  إذا (fold_p)
    فرچ.درج = c_fully_fold (فرچ.درج, خطأ, عدم);
  ret->quick_تور (فرچ.درج);
  إذا (orig_types)
    orig_types->quick_تور (فرچ.original_type);
  إذا (locations)
    locations->safe_تور (فرچ.get_location ());
  إذا (sizeof_arg != عدم
      && (فرچ.original_code == SIZEOF_فرچ
	  || فرچ.original_code == PAREN_SIZEOF_فرچ))
    {
      sizeof_arg[0] = c_last_sizeof_arg;
      sizeof_arg_loc[0] = c_last_sizeof_loc;
    }
  طالما (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  بشيا درج = embed->درج;
	  فرچ.original_code = INTEGER_CST;
	  فرچ.original_type = integer_type_كلي;
	  فرچ.درج = NULL_بشيا;
	  set_c_فرچ_source_range (&فرچ, embed->get_range ());
	  فرچ.m_decimal = 0;
	  لكل (unsigned صحيح i = 0; i < (unsigned) RAW_DATA_LENGTH (درج); i++)
	    {
	      إذا (literal_zero_mask
		  && idx + 1 < HOST_BITS_PER_INT
		  && RAW_DATA_POINTER (درج)[i] == 0)
		*literal_zero_mask |= 1U << (idx + 1);
	      فرچ.درج = build_int_cst (integer_type_كلي,
					  RAW_DATA_UCHAR_ELT (درج, i));
	      vec_safe_تور (ret, فرچ.درج);
	      إذا (orig_types)
		vec_safe_تور (orig_types, فرچ.original_type);
	      إذا (locations)
		locations->safe_تور (فرچ.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  استمر;
	}
      إذا (literal_zero_mask)
	c_parser_check_literal_zero (parser, literal_zero_mask, idx + 1);
      فرچ = c_parser_فرچ_no_commas (parser, عدم);
      إذا (convert_p)
	فرچ = convert_lvalue_to_rvalue (فرچ.get_location (), فرچ, true,
					 true);
      إذا (fold_p)
	فرچ.درج = c_fully_fold (فرچ.درج, خطأ, عدم);
      vec_safe_تور (ret, فرچ.درج);
      إذا (orig_types)
	vec_safe_تور (orig_types, فرچ.original_type);
      إذا (locations)
	locations->safe_تور (فرچ.get_location ());
      إذا (++idx < 6
	  && sizeof_arg != عدم
	  && (فرچ.original_code == SIZEOF_فرچ
	      || فرچ.original_code == PAREN_SIZEOF_فرچ))
	{
	  sizeof_arg[idx] = c_last_sizeof_arg;
	  sizeof_arg_loc[idx] = c_last_sizeof_loc;
	}
    }
  إذا (orig_types)
    *p_orig_types = orig_types;
  c_omp_array_section_p = save_c_omp_array_section_p;
  أرجع ret;
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

ساكن فراغ
c_parser_objc_class_definition (c_parser *parser, بشيا attributes)
{
  منطقي iface_p;
  بشيا id1;
  بشيا superclass;
  إذا (c_parser_next_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = true;
  وإلا إذا (c_parser_next_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = خطأ;
  وإلا
    gcc_unreachable ();

  c_parser_consume_token (parser);
  إذا (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      أرجع;
    }
  id1 = c_parser_peek_token (parser)->درج;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      بشيا id2;
      بشيا proto = NULL_بشيا;
      matching_parens parens;
      parens.consume_open (parser);
      إذا (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  إذا (iface_p && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_بشيا;
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
	      أرجع;
	    }
	}
      وإلا
	{
	  id2 = c_parser_peek_token (parser)->درج;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_found_close (parser);
      إذا (!iface_p)
	{
	  objc_start_category_implementation (id1, id2);
	  أرجع;
	}
      إذا (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_category_interface (id1, id2, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
      أرجع;
    }
  إذا (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  أرجع;
	}
      superclass = c_parser_peek_token (parser)->درج;
      c_parser_consume_token (parser);
    }
  وإلا
    superclass = NULL_بشيا;
  إذا (iface_p)
    {
      بشيا proto = NULL_بشيا;
      إذا (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_class_interface (id1, loc1, superclass, proto, attributes);
    }
  وإلا
    objc_start_class_implementation (id1, superclass);
  إذا (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  إذا (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
    }
  وإلا
    {
      objc_continue_implementation ();
      أرجع;
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

ساكن فراغ
c_parser_objc_class_instance_variables (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  طالما (c_parser_next_token_is_not (parser, CPP_EOF))
    {
      بشيا decls;
      /* Parse any stray semicolon.  */
      إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  استمر;
	}
      /* Stop if at the end of the instance variables.  */
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  اكسر;
	}
      /* Parse any objc-visibility-spec.  */
      إذا (c_parser_next_token_is_keyword (parser, RID_AT_PRIVATE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PRIVATE);
	  استمر;
	}
      وإلا إذا (c_parser_next_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PROTECTED);
	  استمر;
	}
      وإلا إذا (c_parser_next_token_is_keyword (parser, RID_AT_PUBLIC))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PUBLIC);
	  استمر;
	}
      وإلا إذا (c_parser_next_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PACKAGE);
	  استمر;
	}
      وإلا إذا (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, عدم, NULL_بشيا);
	  استمر;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser, عدم);
      إذا (decls == عدم)
	{
	  /* There is a syntax error.  We want to skip the offending
	     tokens up to the next ';' (included) or '}'
	     (excluded).  */

	  /* First, skip manually a ')' or ']'.  This is because they
	     reduce the nesting level, so c_parser_skip_until_found()
	     wouldn't be able to skip past them.  */
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_SQUARE)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, عدم);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = خطأ;
	  استمر;
	}
      وإلا
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  بشيا ivar = nreverse (decls);
	  لكل (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_add_instance_variable (copy_كلي (ivar));
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}

/* Parse an objc-class-declaration.

   objc-class-declaration:
     @class identifier-list ;
*/

ساكن فراغ
c_parser_objc_class_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_CLASS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  طالما (true)
    {
      بشيا id;
      إذا (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, عدم);
	  parser->error = خطأ;
	  أرجع;
	}
      id = c_parser_peek_token (parser)->درج;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse an objc-alias-declaration.

   objc-alias-declaration:
     @compatibility_alias identifier identifier ;
*/

ساكن فراغ
c_parser_objc_alias_declaration (c_parser *parser)
{
  بشيا id1, id2;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  إذا (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, عدم);
      أرجع;
    }
  id1 = c_parser_peek_token (parser)->درج;
  c_parser_consume_token (parser);
  إذا (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, عدم);
      أرجع;
    }
  id2 = c_parser_peek_token (parser)->درج;
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

ساكن فراغ
c_parser_objc_protocol_definition (c_parser *parser, بشيا attributes)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  إذا (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      أرجع;
    }
  إذا (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      طالما (true)
	{
	  بشيا id;
	  إذا (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      اكسر;
	    }
	  id = c_parser_peek_token (parser)->درج;
	  objc_declare_protocol (id, attributes);
	  c_parser_consume_token (parser);
	  إذا (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    اكسر;
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  وإلا
    {
      بشيا id = c_parser_peek_token (parser)->درج;
      بشيا proto = NULL_بشيا;
      c_parser_consume_token (parser);
      إذا (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = true;
      objc_start_protocol (id, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      parser->objc_pq_context = خطأ;
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
ساكن مضمن منطقي
c_parser_objc_method_type (c_parser *parser)
{
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_PLUS:
      c_parser_consume_token (parser);
      أرجع true;
    حالة CPP_MINUS:
      c_parser_consume_token (parser);
      أرجع خطأ;
    افتراضي:
      gcc_unreachable ();
    }
}

/* Parse an objc-method-definition.

   objc-method-definition:
     objc-method-type objc-method-decl ;[opt] compound-statement
*/

ساكن فراغ
c_parser_objc_method_definition (c_parser *parser)
{
  منطقي is_class_method = c_parser_objc_method_type (parser);
  بشيا decl, attributes = NULL_بشيا, فرچ = NULL_بشيا;
  parser->objc_pq_context = true;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    &فرچ);
  إذا (decl == error_mark_كلي)
    أرجع;  /* Bail here. */

  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  إذا (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      أرجع;
    }

  parser->objc_pq_context = خطأ;
  إذا (objc_start_method_definition (is_class_method, decl, attributes, فرچ))
    {
      add_stmt (c_parser_compound_statement (parser));
      objc_finish_method_definition (current_function_decl);
    }
  وإلا
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

ساكن فراغ
c_parser_objc_methodprotolist (c_parser *parser)
{
  طالما (true)
    {
      /* The list is terminated by @end.  */
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_SEMICOLON:
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  اكسر;
	حالة CPP_PLUS:
	حالة CPP_MINUS:
	  c_parser_objc_methodproto (parser);
	  اكسر;
	حالة CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external, عدم, NULL_بشيا);
	  اكسر;
	حالة CPP_EOF:
	  أرجع;
	افتراضي:
	  إذا (c_parser_next_token_is_keyword (parser, RID_AT_END))
	    أرجع;
	  وإلا إذا (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  وإلا إذا (c_parser_next_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_set_method_opt (true);
	      c_parser_consume_token (parser);
	    }
	  وإلا إذا (c_parser_next_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_set_method_opt (خطأ);
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    c_parser_declaration_or_fndef (parser, خطأ, خطأ, true,
					   خطأ, true, خطأ);
	  اكسر;
	}
    }
}

/* Parse an objc-methodproto.

   objc-methodproto:
     objc-method-type objc-method-decl ;
*/

ساكن فراغ
c_parser_objc_methodproto (c_parser *parser)
{
  منطقي is_class_method = c_parser_objc_method_type (parser);
  بشيا decl, attributes = NULL_بشيا;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = true;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    عدم);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = خطأ;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  إذا (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      أرجع;
    }

  إذا (decl != error_mark_كلي)
    objc_add_method_declaration (is_class_method, decl, attributes);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

ساكن منطقي
c_parser_objc_maybe_method_attributes (c_parser* parser, بشيا* attributes)
{
  منطقي bad = خطأ;
  إذا (*attributes)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *attributes = NULL_بشيا;
      bad = true;
    }

  إذا (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    *attributes = c_parser_gnu_attributes (parser);

  /* If there were no attributes here, just report any earlier error.  */
  إذا (*attributes == NULL_بشيا || bad)
    أرجع bad;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    أرجع bad;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  أرجع true;
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

ساكن بشيا
c_parser_objc_method_decl (c_parser *parser, منطقي is_class_method,
			   بشيا *attributes, بشيا *فرچ)
{
  بشيا type = NULL_بشيا;
  بشيا sel;
  بشيا parms = NULL_بشيا;
  منطقي ellipsis = خطأ;
  منطقي attr_err = خطأ;

  *attributes = NULL_بشيا;
  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
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
  إذا (!sel || c_parser_next_token_is (parser, CPP_COLON))
    {
      بشيا tsel = sel;
      بشيا list = NULL_بشيا;
      طالما (true)
	{
	  بشيا atype = NULL_بشيا, id, keyworddecl;
	  بشيا param_attr = NULL_بشيا;
	  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    اكسر;
	  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  إذا (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_attributes (parser);
	  إذا (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      أرجع error_mark_كلي;
	    }
	  id = c_parser_peek_token (parser)->درج;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  إذا (!tsel && c_parser_next_token_is_not (parser, CPP_COLON))
	    اكسر;
	}

      attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_كلي (بشيا_LIST);
      طالما (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  بنية c_parm *parm;
	  c_parser_consume_token (parser);
	  إذا (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = true;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_method_attributes
						(parser, attributes) ;
	      اكسر;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_بشيا, خطأ);
	  إذا (parm == عدم)
	    اكسر;
	  parms = chainon (parms,
			   build_بشيا_list (NULL_بشيا, grokparm (parm, فرچ)));
	}
      sel = list;
    }
  وإلا
    attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

  إذا (sel == عدم)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      أرجع error_mark_كلي;
    }

  إذا (attr_err)
    أرجع error_mark_كلي;

  أرجع objc_build_method_signature (is_class_method, type, sel, parms, ellipsis);
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

ساكن بشيا
c_parser_objc_type_name (c_parser *parser)
{
  بشيا quals = NULL_بشيا;
  بنية c_type_name *type_name = عدم;
  بشيا type = NULL_بشيا;
  طالما (true)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_KEYWORD
	  && (token->keyword == RID_IN
	      || token->keyword == RID_OUT
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_بشيا_list (NULL_بشيا, token->درج), quals);
	  c_parser_consume_token (parser);
	}
      وإلا
	اكسر;
    }
  إذا (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  إذا (type_name)
    type = groktypename (type_name, عدم, عدم);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  إذا (type == error_mark_كلي)
    type = NULL_بشيا;

  أرجع build_بشيا_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

ساكن بشيا
c_parser_objc_protocol_refs (c_parser *parser)
{
  بشيا list = NULL_بشيا;
  gcc_assert (c_parser_next_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  طالما (true)
    {
      بشيا id;
      إذا (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  اكسر;
	}
      id = c_parser_peek_token (parser)->درج;
      list = chainon (list, build_بشيا_list (NULL_بشيا, id));
      c_parser_consume_token (parser);
      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  أرجع list;
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

ساكن فراغ
c_parser_objc_try_catch_finally_statement (c_parser *parser)
{
  location_t location;
  بشيا stmt;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  طالما (c_parser_next_token_is_keyword (parser, RID_AT_CATCH))
    {
      بنية c_parm *parm;
      بشيا parameter_declaration = error_mark_كلي;
      منطقي seen_open_paren = خطأ;

      c_parser_consume_token (parser);
      matching_parens parens;
      إذا (!parens.require_open (parser))
	seen_open_paren = true;
      إذا (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_بشيا;
	}
      وإلا
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_بشيا, خطأ);
	  إذا (parm == عدم)
	    parameter_declaration = error_mark_كلي;
	  وإلا
	    parameter_declaration = grokparm (parm, عدم);
	}
      إذا (seen_open_paren)
	parens.require_close (parser);
      وإلا
	{
	  /* If there was no open parenthesis, we are recovering from
	     an error, and we are trying to figure out what mistake
	     the user has made.  */

	  /* If there is an immediate closing parenthesis, the user
	     probably forgot the opening one (ie, they typed "@catch
	     NSException *e)".  Parse the closing parenthesis and keep
	     going.  */
	  إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      إذا (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_finish_catch_clause ();
    }
  إذا (c_parser_next_token_is_keyword (parser, RID_AT_FINALLY))
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

ساكن فراغ
c_parser_objc_synchronized_statement (c_parser *parser)
{
  location_t loc;
  بشيا فرچ, stmt;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      بنية c_فرچ ce = c_parser_expression (parser);
      ce = convert_lvalue_to_rvalue (loc, ce, خطأ, خطأ);
      فرچ = ce.درج;
      فرچ = c_fully_fold (فرچ, خطأ, عدم);
      parens.skip_until_found_close (parser);
    }
  وإلا
    فرچ = error_mark_كلي;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, فرچ, stmt);
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

ساكن بشيا
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  بشيا درج = token->درج;
  إذا (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      أرجع درج;
    }
  إذا (token->type != CPP_KEYWORD)
    أرجع NULL_بشيا;
  بدل (token->keyword)
    {
    حالة RID_ENUM:
    حالة RID_STRUCT:
    حالة RID_UNION:
    حالة RID_IF:
    حالة RID_ELSE:
    حالة RID_WHILE:
    حالة RID_DO:
    حالة RID_FOR:
    حالة RID_SWITCH:
    حالة RID_CASE:
    حالة RID_DEFAULT:
    حالة RID_BREAK:
    حالة RID_CONTINUE:
    حالة RID_RETURN:
    حالة RID_GOTO:
    حالة RID_ASM:
    حالة RID_SIZEOF:
    حالة RID_TYPEOF:
    حالة RID_TYPEOF_UNQUAL:
    حالة RID_ALIGNOF:
    حالة RID_UNSIGNED:
    حالة RID_LONG:
    حالة RID_CONST:
    حالة RID_SHORT:
    حالة RID_VOLATILE:
    حالة RID_SIGNED:
    حالة RID_RESTRICT:
    حالة RID_COMPLEX:
    حالة RID_IN:
    حالة RID_OUT:
    حالة RID_INOUT:
    حالة RID_BYCOPY:
    حالة RID_BYREF:
    حالة RID_ONEWAY:
    حالة RID_INT:
    حالة RID_CHAR:
    حالة RID_FLOAT:
    حالة RID_DOUBLE:
    CASE_RID_FLOATN_NX:
    حالة RID_VOID:
    حالة RID_BOOL:
    حالة RID_ATOMIC:
    حالة RID_AUTO_TYPE:
    حالة RID_INT_N_0:
    حالة RID_INT_N_1:
    حالة RID_INT_N_2:
    حالة RID_INT_N_3:
      c_parser_consume_token (parser);
      أرجع درج;
    افتراضي:
      أرجع NULL_بشيا;
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

ساكن بشيا
c_parser_objc_selector_arg (c_parser *parser)
{
  بشيا sel = c_parser_objc_selector (parser);
  بشيا list = NULL_بشيا;
  إذا (sel
      && c_parser_next_token_is_not (parser, CPP_COLON)
      && c_parser_next_token_is_not (parser, CPP_SCOPE))
    أرجع sel;
  طالما (true)
    {
      إذا (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_بشيا_list (sel, NULL_بشيا));
	  list = chainon (list, build_بشيا_list (NULL_بشيا, NULL_بشيا));
	}
      وإلا
	{
	  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    أرجع list;
	  list = chainon (list, build_بشيا_list (sel, NULL_بشيا));
	}
      sel = c_parser_objc_selector (parser);
      إذا (!sel
	  && c_parser_next_token_is_not (parser, CPP_COLON)
	  && c_parser_next_token_is_not (parser, CPP_SCOPE))
	اكسر;
    }
  أرجع list;
}

/* Parse an objc-receiver.

   objc-receiver:
     expression
     class-name
     type-name
*/

ساكن بشيا
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  إذا (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
    {
      بشيا id = c_parser_peek_token (parser)->درج;
      c_parser_consume_token (parser);
      أرجع objc_get_class_reference (id);
    }
  بنية c_فرچ ce = c_parser_expression (parser);
  ce = convert_lvalue_to_rvalue (loc, ce, خطأ, خطأ);
  أرجع c_fully_fold (ce.درج, خطأ, عدم);
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

ساكن بشيا
c_parser_objc_message_حجوجي (c_parser *parser)
{
  بشيا sel = c_parser_objc_selector (parser);
  بشيا list = NULL_بشيا;
  إذا (sel && c_parser_next_token_is_not (parser, CPP_COLON))
    أرجع sel;
  طالما (true)
    {
      بشيا keywordexpr;
      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	أرجع error_mark_كلي;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_بشيا_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      إذا (!sel && c_parser_next_token_is_not (parser, CPP_COLON))
	اكسر;
    }
  أرجع list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

ساكن بشيا
c_parser_objc_keywordexpr (c_parser *parser)
{
  بشيا ret;
  vec<بشيا, va_gc> *فرچ_list = c_parser_فرچ_list (parser, true, true,
						عدم, عدم, عدم, عدم);
  إذا (vec_safe_length (فرچ_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*فرچ_list)[0];
    }
  وإلا
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_بشيا_list_vec (فرچ_list);
    }
  release_بشيا_vector (فرچ_list);
  أرجع ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
ساكن منطقي
c_parser_objc_diagnose_bad_element_prefix (c_parser *parser,
					   بنية c_declspecs *specs)
{
  إذا (!specs->declspecs_seen_p || specs->non_sc_seen_p
      || specs->typespec_kind != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_to_end_of_block_or_statement (parser);
      أرجع true;
    }
  أرجع خطأ;
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
ساكن فراغ
c_parser_objc_at_property_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY));
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);  /* Eat '@property'.  */

  /* Parse the optional attribute list.

     A list of parsed, but not verified, attributes.  */
  vec<property_attribute_info *> prop_attr_list = vNULL;

  منطقي syntax_error = خطأ;
  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_start = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = true;

      /* Allow @property (), with a warning.  */
      location_t attr_end = c_parser_peek_token (parser)->location;

      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_end, attr_start, attr_end);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      وإلا
	طالما (true)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_start = token->location;
	    attr_end = get_finish (token->location);
	    location_t attr_comb = make_location (attr_start, attr_start,
						  attr_end);

	    إذا (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		إذا (token->type == CPP_CLOSE_PAREN)
		  اكسر;
		c_parser_consume_token (parser);
		استمر;
	      }

	    بشيا attr_name = NULL_بشيا;
	    تعداد rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    منطقي add_at = خطأ;
	    إذا (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		إذا (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->درج;
		    add_at = true;
		  }
		وإلا
		  attr_name = ridpointers[(صحيح)keyword];
	      }
	    وإلا إذا (token->type == CPP_NAME)
	      attr_name = token->درج;
	    c_parser_consume_token (parser);

	    تعداد objc_property_attribute_kind prop_kind
	      = objc_prop_attr_kind_for_rid (keyword);
	    property_attribute_info *prop
	      = جديد property_attribute_info (attr_name, attr_comb, prop_kind);
	    prop_attr_list.safe_تور (prop);

	    بشيا meth_name;
	    بدل (prop->prop_kind)
	      {
	      افتراضي: اكسر;
	      حالة OBJC_PROPERTY_ATTR_UNKNOWN:
		إذا (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    add_at ? "@" : "", IDENTIFIER_POINTER (attr_name));
		وإلا
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = true;
		اكسر;

	      حالة OBJC_PROPERTY_ATTR_GETTER:
	      حالة OBJC_PROPERTY_ATTR_SETTER:
		إذا (c_parser_next_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = true;
		    اكسر;
		  }
		token = c_parser_peek_token (parser);
		attr_end = token->location;
		c_parser_consume_token (parser); /* eat the = */
		إذا (c_parser_next_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = true;
		    اكسر;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_end = get_finish (token->location);
		meth_name = token->درج;
		c_parser_consume_token (parser);
		إذا (prop->prop_kind == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    إذا (c_parser_next_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_end, attr_start,
						   attr_end);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = true;
		      }
		    وإلا
		      {
			attr_end = get_finish (c_parser_peek_token
					       (parser)->location);
			c_parser_consume_token (parser);
		      }
		    attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		  }
		وإلا
		  attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		prop->ident = meth_name;
		/* Updated location including all that was successfully
		   parsed.  */
		prop->prop_loc = attr_comb;
		اكسر;
	    }

	  /* If we see a comma here, then keep going - even if we already
	     saw a syntax error.  For simple mistakes e.g. (assign, getter=x)
	     this makes a more useful output and avoid spurious warnings about
	     missing attributes that are, in fact, specified after the one with
	     the syntax error.  */
	  إذا (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    اكسر;
	}
      parser->objc_property_attr_context = خطأ;

      إذا (syntax_error && c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      وإلا
	syntax_error = خطأ, parens.skip_until_found_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  بشيا properties = c_parser_struct_declaration (parser, عدم);

  إذا (properties == error_mark_كلي)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, عدم);
  وإلا
    {
      إذا (properties == NULL_بشيا)
	c_parser_error (parser, "expected identifier");
      وإلا
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  لكل (; properties; properties = بشيا_CHAIN (properties))
	    objc_add_property_declaration (loc, copy_كلي (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  طالما (!prop_attr_list.is_empty())
    delete prop_attr_list.چرو ();
  prop_attr_list.release ();
  parser->error = خطأ;
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
ساكن فراغ
c_parser_objc_at_synthesize_declaration (c_parser *parser)
{
  بشيا list = NULL_بشيا;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  طالما (true)
    {
      بشيا property, ivar;
      إذا (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, عدم);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = خطأ;
	  أرجع;
	}
      property = c_parser_peek_token (parser)->درج;
      c_parser_consume_token (parser);
      إذا (c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  إذا (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_SEMICOLON, عدم);
	      parser->error = خطأ;
	      أرجع;
	    }
	  ivar = c_parser_peek_token (parser)->درج;
	  c_parser_consume_token (parser);
	}
      وإلا
	ivar = NULL_بشيا;
      list = chainon (list, build_بشيا_list (ivar, property));
      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
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
ساكن فراغ
c_parser_objc_at_dynamic_declaration (c_parser *parser)
{
  بشيا list = NULL_بشيا;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  طالما (true)
    {
      بشيا property;
      إذا (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, عدم);
	  parser->error = خطأ;
	  أرجع;
	}
      property = c_parser_peek_token (parser)->درج;
      list = chainon (list, build_بشيا_list (NULL_بشيا, property));
      c_parser_consume_token (parser);
      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_add_dynamic_declaration (loc, list);
}


/* Parse a pragma GCC ivdep.  */

ساكن منطقي
c_parse_pragma_ivdep (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  أرجع true;
}

/* Parse a pragma GCC novector.  */

ساكن منطقي
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  أرجع true;
}

/* Parse a pragma GCC unroll.  */

ساكن unsigned short
c_parser_pragma_unroll (c_parser *parser)
{
  unsigned short unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  بشيا فرچ = c_parser_فرچ_no_commas (parser, عدم).درج;
  mark_exp_read (فرچ);
  فرچ = c_fully_fold (فرچ, خطأ, عدم);
  HOST_WIDE_INT lunroll = 0;
  إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (فرچ))
      || بشيا_CODE (فرچ) != INTEGER_CST
      || (lunroll = بشيا_to_shwi (فرچ)) < 0
      || lunroll >= USHRT_MAX)
    {
      error_at (location, "%<#pragma GCC unroll%> requires an"
		" assignment-expression that evaluates to a non-negative"
		" integral constant less than %u", USHRT_MAX);
      unroll = 0;
    }
  وإلا
    {
      unroll = (unsigned short)lunroll;
      إذا (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_to_pragma_eol (parser);
  أرجع unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

ساكن منطقي
c_parser_pragma (c_parser *parser, تعداد pragma_context context, منطقي *if_p,
		 بشيا before_labels)
{
  unsigned صحيح id;
  ثابت حرف *construct = عدم;

  شغرو_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_kind;
  gcc_assert (id != PRAGMA_NONE);
  إذا (parser->omp_for_parse_state
      && parser->omp_for_parse_state->in_intervening_code
      && id >= PRAGMA_OMP__START_ && id <= PRAGMA_OMP__LAST_
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	شغرو_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->fail = true;
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, عدم);
      أرجع خطأ;
    }

  بدل (id)
    {
    حالة PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      أرجع خطأ;

    حالة PRAGMA_OACC_ENTER_DATA:
      إذا (context != pragma_compound)
	{
	  construct = "acc enter data";
	in_compound:
	  إذا (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, عدم);
	      أرجع true;
	    }
	  اذهب bad_stmt;
	}
      c_parser_oacc_enter_exit_data (parser, true);
      أرجع خطأ;

    حالة PRAGMA_OACC_EXIT_DATA:
      إذا (context != pragma_compound)
	{
	  construct = "acc exit data";
	  اذهب in_compound;
	}
      c_parser_oacc_enter_exit_data (parser, خطأ);
      أرجع خطأ;

    حالة PRAGMA_OACC_ROUTINE:
      إذا (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, عدم);
	  أرجع خطأ;
	}
      c_parser_oacc_routine (parser, context);
      أرجع خطأ;

    حالة PRAGMA_OACC_UPDATE:
      إذا (context != pragma_compound)
	{
	  construct = "acc update";
	  اذهب in_compound;
	}
      c_parser_oacc_update (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_BARRIER:
      إذا (context != pragma_compound)
	{
	  construct = "omp barrier";
	  اذهب in_compound;
	}
      c_parser_omp_barrier (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_DEPOBJ:
      إذا (context != pragma_compound)
	{
	  construct = "omp depobj";
	  اذهب in_compound;
	}
      c_parser_omp_depobj (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_FLUSH:
      إذا (context != pragma_compound)
	{
	  construct = "omp flush";
	  اذهب in_compound;
	}
      c_parser_omp_flush (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_INTEROP:
      إذا (context != pragma_compound)
	{
	  construct = "omp interop";
	  اذهب in_compound;
	}
      c_parser_omp_interop (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_TASKWAIT:
      إذا (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  اذهب in_compound;
	}
      c_parser_omp_taskwait (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_TASKYIELD:
      إذا (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  اذهب in_compound;
	}
      c_parser_omp_taskyield (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_CANCEL:
      إذا (context != pragma_compound)
	{
	  construct = "omp cancel";
	  اذهب in_compound;
	}
      c_parser_omp_cancel (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_CANCELLATION_POINT:
      أرجع c_parser_omp_cancellation_point (parser, context);

    حالة PRAGMA_OMP_GROUPPRIVATE:
      c_parser_omp_groupprivate (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_THREADPRIVATE:
      c_parser_omp_threadprivate (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_TARGET:
      أرجع c_parser_omp_target (parser, context, if_p);

    حالة PRAGMA_OMP_BEGIN:
      c_parser_omp_begin (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_END:
      c_parser_omp_end (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_SCAN:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, عدم);
      أرجع خطأ;

    حالة PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, عدم);
      أرجع خطأ;

    حالة PRAGMA_OMP_DECLARE:
      أرجع c_parser_omp_declare (parser, context);

    حالة PRAGMA_OMP_REQUIRES:
      إذا (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, عدم);
	  أرجع خطأ;
	}
      c_parser_omp_requires (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_ALLOCATE:
      c_parser_omp_allocate (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_ASSUMES:
      إذا (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp assumes");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, عدم);
	  أرجع خطأ;
	}
      c_parser_omp_assumes (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      أرجع true;

    حالة PRAGMA_OMP_ERROR:
      أرجع c_parser_omp_error (parser, context);

    حالة PRAGMA_OMP_ORDERED:
      أرجع c_parser_omp_ordered (parser, context, if_p);

    حالة PRAGMA_NOVECTOR:
    حالة PRAGMA_UNROLL:
    حالة PRAGMA_IVDEP:
      {
	منطقي novector = خطأ;
	unsigned short unroll = 0;
	منطقي ivdep = خطأ;

	بدل (id)
	  {
	  حالة PRAGMA_NOVECTOR:
	    novector = c_parse_pragma_novector (parser);
	    اكسر;
	  حالة PRAGMA_UNROLL:
	    unroll = c_parser_pragma_unroll (parser);
	    اكسر;
	  حالة PRAGMA_IVDEP:
	    ivdep = c_parse_pragma_ivdep (parser);
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }

	c_token *tok = c_parser_peek_token (parser);
	منطقي has_more = tok->type == CPP_PRAGMA;
	طالما (has_more)
	  {
	    بدل (tok->pragma_kind)
	      {
	      حالة PRAGMA_IVDEP:
		ivdep = c_parse_pragma_ivdep (parser);
		اكسر;
	      حالة PRAGMA_UNROLL:
		unroll = c_parser_pragma_unroll (parser);
		اكسر;
	      حالة PRAGMA_NOVECTOR:
		novector = c_parse_pragma_novector (parser);
		اكسر;
	      افتراضي:
		has_more = خطأ;
		اكسر;
	      }
	    tok = c_parser_peek_token (parser);
	    has_more = has_more && tok->type == CPP_PRAGMA;
	  }
	إذا (!c_parser_next_token_is_keyword (parser, RID_FOR)
	    && !c_parser_next_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_next_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    أرجع خطأ;
	  }
	إذا (c_parser_next_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	وإلا إذا (c_parser_next_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	وإلا
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      أرجع true;

    حالة PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, عدم);
      أرجع خطأ;

    حالة PRAGMA_OACC_WAIT:
      إذا (context != pragma_compound)
	{
	  construct = "acc wait";
	  اذهب in_compound;
	}
	/* FALL THROUGH.  */

    افتراضي:
      إذا (id < PRAGMA_FIRST_EXTERNAL)
	{
	  إذا (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, عدم);
	      أرجع خطأ;
	    }
	  c_parser_omp_construct (parser, if_p);
	  أرجع true;
	}
      اكسر;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = true;
  c_parser_skip_to_pragma_eol (parser);

  أرجع خطأ;
}

/* The interface the pragma parsers have to the lexer.  */

تعداد cpp_ttype
pragma_lex (بشيا *درج, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  تعداد cpp_ttype ret = tok->type;

  *درج = tok->درج;
  إذا (loc)
    *loc = tok->location;

  إذا (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  وإلا إذا (ret == CPP_STRING)
    *درج = c_parser_string_literal (the_parser, خطأ, خطأ).درج;
  وإلا
    {
      إذا (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  أرجع ret;
}

فراغ
pragma_lex_discard_to_eol ()
{
  cpp_ttype type;
  افعل
    {
      type = c_parser_peek_token (the_parser)->type;
      gcc_assert (type != CPP_EOF);
      c_parser_consume_token (the_parser);
    } طالما (type != CPP_PRAGMA_EOL);
}

ساكن فراغ
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  بشيا name = عدم;

  parser->lex_joined_string = true;
  c_parser_consume_pragma (parser);
  إذا (c_parser_next_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->درج;
      c_parser_consume_token (parser);
    }
  وإلا
    c_parser_error (parser, "expected string literal");
  c_parser_skip_to_pragma_eol (parser);
  parser->lex_joined_string = خطأ;

  إذا (name)
    c_common_pch_pragma (parse_in, بشيا_STRING_POINTER (name));
}

/* OpenACC and OpenMP parsing routines.  */

/* Returns name of the next clause.
   If the clause is not recognized PRAGMA_OMP_CLAUSE_NONE is returned and
   the token is not consumed.  Otherwise appropriate pragma_omp_clause is
   returned and the token is consumed.  */

ساكن pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause result = PRAGMA_OMP_CLAUSE_NONE;

  إذا (c_parser_next_token_is_keyword (parser, RID_AUTO))
    result = PRAGMA_OACC_CLAUSE_AUTO;
  وإلا إذا (c_parser_next_token_is_keyword (parser, RID_IF))
    result = PRAGMA_OMP_CLAUSE_IF;
  وإلا إذا (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    result = PRAGMA_OMP_CLAUSE_DEFAULT;
  وإلا إذا (c_parser_next_token_is_keyword (parser, RID_FOR))
    result = PRAGMA_OMP_CLAUSE_FOR;
  وإلا إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);

      بدل (p[0])
	{
	حالة 'a':
	  إذا (!strcmp ("affinity", p))
	    result = PRAGMA_OMP_CLAUSE_AFFINITY;
	  وإلا إذا (!strcmp ("aligned", p))
	    result = PRAGMA_OMP_CLAUSE_ALIGNED;
	  وإلا إذا (!strcmp ("allocate", p))
	    result = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  وإلا إذا (!strcmp ("async", p))
	    result = PRAGMA_OACC_CLAUSE_ASYNC;
	  وإلا إذا (!strcmp ("attach", p))
	    result = PRAGMA_OACC_CLAUSE_ATTACH;
	  اكسر;
	حالة 'b':
	  إذا (!strcmp ("bind", p))
	    result = PRAGMA_OMP_CLAUSE_BIND;
	  اكسر;
	حالة 'c':
	  إذا (!strcmp ("collapse", p))
	    result = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  وإلا إذا (!strcmp ("copy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  وإلا إذا (!strcmp ("copyin", p))
	    result = PRAGMA_OMP_CLAUSE_COPYIN;
	  وإلا إذا (!strcmp ("copyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
          وإلا إذا (!strcmp ("copyprivate", p))
	    result = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  وإلا إذا (!strcmp ("create", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  اكسر;
	حالة 'd':
	  إذا (!strcmp ("defaultmap", p))
	    result = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  وإلا إذا (!strcmp ("delete", p))
	    result = PRAGMA_OACC_CLAUSE_DELETE;
	  وإلا إذا (!strcmp ("depend", p))
	    result = PRAGMA_OMP_CLAUSE_DEPEND;
	  وإلا إذا (!strcmp ("destroy", p))
	    result = PRAGMA_OMP_CLAUSE_DESTROY;
	  وإلا إذا (!strcmp ("detach", p))
	    result = PRAGMA_OACC_CLAUSE_DETACH;
	  وإلا إذا (!strcmp ("device", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE;
	  وإلا إذا (!strcmp ("deviceptr", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  وإلا إذا (!strcmp ("device_resident", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  وإلا إذا (!strcmp ("device_type", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  وإلا إذا (!strcmp ("dist_schedule", p))
	    result = PRAGMA_OMP_CLAUSE_DIST_SCHEDULE;
	  وإلا إذا (!strcmp ("doacross", p))
	    result = PRAGMA_OMP_CLAUSE_DOACROSS;
	  وإلا إذا (!strcmp ("dyn_groupprivate", p))
	    result = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  اكسر;
	حالة 'e':
	  إذا (!strcmp ("enter", p))
	    result = PRAGMA_OMP_CLAUSE_ENTER;
	  اكسر;
	حالة 'f':
	  إذا (!strcmp ("filter", p))
	    result = PRAGMA_OMP_CLAUSE_FILTER;
	  وإلا إذا (!strcmp ("final", p))
	    result = PRAGMA_OMP_CLAUSE_FINAL;
	  وإلا إذا (!strcmp ("finalize", p))
	    result = PRAGMA_OACC_CLAUSE_FINALIZE;
	  وإلا إذا (!strcmp ("firstprivate", p))
	    result = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  وإلا إذا (!strcmp ("from", p))
	    result = PRAGMA_OMP_CLAUSE_FROM;
	  وإلا إذا (!strcmp ("full", p))
	    result = PRAGMA_OMP_CLAUSE_FULL;
	  اكسر;
	حالة 'g':
	  إذا (!strcmp ("gang", p))
	    result = PRAGMA_OACC_CLAUSE_GANG;
	  وإلا إذا (!strcmp ("grainsize", p))
	    result = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  اكسر;
	حالة 'h':
	  إذا (!strcmp ("has_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  وإلا إذا (!strcmp ("hint", p))
	    result = PRAGMA_OMP_CLAUSE_HINT;
	  وإلا إذا (!strcmp ("host", p))
	    result = PRAGMA_OACC_CLAUSE_HOST;
	  اكسر;
	حالة 'i':
	  إذا (!strcmp ("if_present", p))
	    result = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  وإلا إذا (!strcmp ("in_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_IN_REDUCTION;
	  وإلا إذا (!strcmp ("inbranch", p))
	    result = PRAGMA_OMP_CLAUSE_INBRANCH;
	  وإلا إذا (!strcmp ("independent", p))
	    result = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  وإلا إذا (!strcmp ("indirect", p))
	    result = PRAGMA_OMP_CLAUSE_INDIRECT;
	  وإلا إذا (!strcmp ("init", p))
	    result = PRAGMA_OMP_CLAUSE_INIT;
	  وإلا إذا (!strcmp ("is_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  وإلا إذا (!strcmp ("interop", p))
	    result = PRAGMA_OMP_CLAUSE_INTEROP;
	  اكسر;
	حالة 'l':
	  إذا (!strcmp ("lastprivate", p))
	    result = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  وإلا إذا (!strcmp ("linear", p))
	    result = PRAGMA_OMP_CLAUSE_LINEAR;
	  وإلا إذا (!strcmp ("link", p))
	    result = PRAGMA_OMP_CLAUSE_LINK;
	  وإلا إذا (!strcmp ("local", p))
	    result = PRAGMA_OMP_CLAUSE_LOCAL;
	  اكسر;
	حالة 'm':
	  إذا (!strcmp ("map", p))
	    result = PRAGMA_OMP_CLAUSE_MAP;
	  وإلا إذا (!strcmp ("mergeable", p))
	    result = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  اكسر;
	حالة 'n':
	  إذا (!strcmp ("no_create", p))
	    result = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  وإلا إذا (!strcmp ("nocontext", p))
	    result = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  وإلا إذا (!strcmp ("nogroup", p))
	    result = PRAGMA_OMP_CLAUSE_NOGROUP;
	  وإلا إذا (!strcmp ("nohost", p))
	    result = PRAGMA_OACC_CLAUSE_NOHOST;
	  وإلا إذا (!strcmp ("nontemporal", p))
	    result = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  وإلا إذا (!strcmp ("notinbranch", p))
	    result = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  وإلا إذا (!strcmp ("novariants", p))
	    result = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  وإلا إذا (!strcmp ("nowait", p))
	    result = PRAGMA_OMP_CLAUSE_NOWAIT;
	  وإلا إذا (!strcmp ("num_gangs", p))
	    result = PRAGMA_OACC_CLAUSE_لمب_GANGS;
	  وإلا إذا (!strcmp ("num_tasks", p))
	    result = PRAGMA_OMP_CLAUSE_لمب_TASKS;
	  وإلا إذا (!strcmp ("num_teams", p))
	    result = PRAGMA_OMP_CLAUSE_لمب_TEAMS;
	  وإلا إذا (!strcmp ("num_threads", p))
	    result = PRAGMA_OMP_CLAUSE_لمب_THREADS;
	  وإلا إذا (!strcmp ("num_workers", p))
	    result = PRAGMA_OACC_CLAUSE_لمب_WORKERS;
	  اكسر;
	حالة 'o':
	  إذا (!strcmp ("ordered", p))
	    result = PRAGMA_OMP_CLAUSE_ORDERED;
	  وإلا إذا (!strcmp ("order", p))
	    result = PRAGMA_OMP_CLAUSE_ORDER;
	  اكسر;
	حالة 'p':
	  إذا (!strcmp ("parallel", p))
	    result = PRAGMA_OMP_CLAUSE_PARALLEL;
	  وإلا إذا (!strcmp ("partial", p))
	    result = PRAGMA_OMP_CLAUSE_PARTIAL;
	  وإلا إذا (!strcmp ("present", p))
	    result = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  وإلا إذا (!strcmp ("present_or_copy", p)
		   || !strcmp ("pcopy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  وإلا إذا (!strcmp ("present_or_copyin", p)
		   || !strcmp ("pcopyin", p))
	    result = PRAGMA_OACC_CLAUSE_COPYIN;
	  وإلا إذا (!strcmp ("present_or_copyout", p)
		   || !strcmp ("pcopyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
	  وإلا إذا (!strcmp ("present_or_create", p)
		   || !strcmp ("pcreate", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  وإلا إذا (!strcmp ("priority", p))
	    result = PRAGMA_OMP_CLAUSE_PRIORITY;
	  وإلا إذا (!strcmp ("private", p))
	    result = PRAGMA_OMP_CLAUSE_PRIVATE;
	  وإلا إذا (!strcmp ("proc_bind", p))
	    result = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  اكسر;
	حالة 'r':
	  إذا (!strcmp ("reduction", p))
	    result = PRAGMA_OMP_CLAUSE_REDUCTION;
	  اكسر;
	حالة 's':
	  إذا (!strcmp ("safelen", p))
	    result = PRAGMA_OMP_CLAUSE_SAFELEN;
	  وإلا إذا (!strcmp ("schedule", p))
	    result = PRAGMA_OMP_CLAUSE_SCHEDULE;
	  وإلا إذا (!strcmp ("sections", p))
	    result = PRAGMA_OMP_CLAUSE_SECTIONS;
	  وإلا إذا (!strcmp ("self", p))
	    result = PRAGMA_OACC_CLAUSE_SELF;
	  وإلا إذا (!strcmp ("seq", p))
	    result = PRAGMA_OACC_CLAUSE_SEQ;
	  وإلا إذا (!strcmp ("shared", p))
	    result = PRAGMA_OMP_CLAUSE_SHARED;
	  وإلا إذا (!strcmp ("simd", p))
	    result = PRAGMA_OMP_CLAUSE_SIMD;
	  وإلا إذا (!strcmp ("simdlen", p))
	    result = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  اكسر;
	حالة 't':
	  إذا (!strcmp ("task_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  وإلا إذا (!strcmp ("taskgroup", p))
	    result = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  وإلا إذا (!strcmp ("thread_limit", p))
	    result = PRAGMA_OMP_CLAUSE_THREAD_LIMIT;
	  وإلا إذا (!strcmp ("threads", p))
	    result = PRAGMA_OMP_CLAUSE_THREADS;
	  وإلا إذا (!strcmp ("tile", p))
	    result = PRAGMA_OACC_CLAUSE_TILE;
	  وإلا إذا (!strcmp ("to", p))
	    result = PRAGMA_OMP_CLAUSE_TO;
	  اكسر;
	حالة 'u':
	  إذا (!strcmp ("uniform", p))
	    result = PRAGMA_OMP_CLAUSE_UNIFORM;
	  وإلا إذا (!strcmp ("untied", p))
	    result = PRAGMA_OMP_CLAUSE_UNTIED;
	  وإلا إذا (!strcmp ("use", p))
	    result = PRAGMA_OMP_CLAUSE_USE;
	  وإلا إذا (!strcmp ("use_device", p))
	    result = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  وإلا إذا (!strcmp ("use_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  وإلا إذا (!strcmp ("use_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  وإلا إذا (!strcmp ("uses_allocators", p))
	    result = PRAGMA_OMP_CLAUSE_USES_ALLOCATORS;
	  اكسر;
	حالة 'v':
	  إذا (!strcmp ("vector", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR;
	  وإلا إذا (!strcmp ("vector_length", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR_LENGTH;
	  اكسر;
	حالة 'w':
	  إذا (!strcmp ("wait", p))
	    result = PRAGMA_OACC_CLAUSE_WAIT;
	  وإلا إذا (!strcmp ("worker", p))
	    result = PRAGMA_OACC_CLAUSE_WORKER;
	  اكسر;
	}
    }

  إذا (result != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  أرجع result;
}

/* Validate that a clause of the given type does not already exist.  */

ساكن فراغ
check_no_duplicate_clause (بشيا clauses, تعداد omp_clause_code code,
			   ثابت حرف *name)
{
  إذا (بشيا c = omp_find_clause (clauses, code))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

ساكن بشيا
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, بشيا list)
{
  vec<بشيا, va_gc> *حجوجي;
  بشيا t, حجوجي_بشيا;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  حجوجي = c_parser_فرچ_list (parser, خطأ, true, عدم, عدم, عدم, عدم);
  حجوجي_بشيا = build_بشيا_list_vec (حجوجي);

  لكل (t = حجوجي_بشيا; t; t = بشيا_CHAIN (t))
    {
      بشيا targ = بشيا_درج (t);

      إذا (targ != error_mark_كلي)
	{
	  إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_كلي;
	    }
	  وإلا
	    {
	      بشيا c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_بشيا_vector (حجوجي);
  parens.require_close (parser);
  أرجع list;
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

بنية omp_dim
{
  بشيا كس_bound, length;
  location_t loc;
  منطقي no_colon;
  omp_dim (بشيا lb, بشيا len, location_t lo, منطقي nc)
  : كس_bound (lb), length (len), loc (lo), no_colon (nc) {}
};

ساكن بشيا
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    تعداد omp_clause_code kind, بشيا list,
			    منطقي map_lvalue = خطأ)
{
  auto_vec<omp_dim> dims;
  منطقي array_section_p;
  auto_vec<c_token> tokens;
  unsigned صحيح tokens_avail = 0;
  c_token *saved_tokens = عدم;

  طالما (1)
    {
      بشيا t = NULL_بشيا;
      location_t tloc = c_parser_peek_token (parser)->location;

      إذا (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  إذا (c_parser_next_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
	    {
	      بنية c_فرچ فرچ;
	      إذا (kind == OMP_CLAUSE_DEPEND
		  && c_parser_next_token_is_keyword (parser,
						     RID_OMP_ALL_MEMORY)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  فرچ.درج = ridpointers[RID_OMP_ALL_MEMORY];
		  c_parser_consume_token (parser);
		}
	      وإلا
		فرچ = c_parser_فرچ_no_commas (parser, عدم);
	      إذا (فرچ.درج != error_mark_كلي)
		{
		  بشيا u = build_omp_clause (clause_loc, kind);
		  OMP_CLAUSE_DECL (u) = فرچ.درج;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      إذا (c_parser_next_token_is_not (parser, CPP_COMMA))
		اكسر;

	      c_parser_consume_token (parser);
	      استمر;
	    }

	  tokens.truncate (0);
	  unsigned صحيح nesting_depth = 0;
	  طالما (1)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      بدل (token->type)
		{
		حالة CPP_EOF:
		حالة CPP_PRAGMA_EOL:
		  اكسر;
		حالة CPP_OPEN_BRACE:
		حالة CPP_OPEN_PAREN:
		حالة CPP_OPEN_SQUARE:
		  ++nesting_depth;
		  اذهب add;
		حالة CPP_CLOSE_BRACE:
		حالة CPP_CLOSE_PAREN:
		حالة CPP_CLOSE_SQUARE:
		  إذا (nesting_depth-- == 0)
		    اكسر;
		  اذهب add;
		حالة CPP_COMMA:
		  إذا (nesting_depth == 0)
		    اكسر;
		  اذهب add;
		افتراضي:
		add:
		  tokens.safe_تور (*token);
		  c_parser_consume_token (parser);
		  استمر;
		}
	      اكسر;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  memset (&eof_token, 0, حجم (eof_token));
	  eof_token.type = CPP_EOF;
	  tokens.safe_تور (eof_token);
	  tokens.safe_تور (eof_token);

	  saved_tokens = parser->tokens;
	  tokens_avail = parser->tokens_avail;
	  parser->tokens = tokens.address ();
	  parser->tokens_avail = tokens.length ();
	}
      وإلا إذا (map_lvalue
	       && (kind == OMP_CLAUSE_MAP
		   || kind == OMP_CLAUSE_TO
		   || kind == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  منطقي save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = true;
	  c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
	  إذا (فرچ.درج != error_mark_كلي)
	    mark_exp_read (فرچ.درج);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  بشيا decl = فرچ.درج;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  إذا (بشيا_CODE (decl) == OMP_ARRAY_SECTION)
	    {
	      طالما (بشيا_CODE (decl) == OMP_ARRAY_SECTION)
		{
		  بشيا كس_bound = بشيا_OPERAND (decl, 1);
		  بشيا length = بشيا_OPERAND (decl, 2);
		  dims.safe_تور (omp_dim (كس_bound, length, loc, خطأ));
		  decl = بشيا_OPERAND (decl, 0);
		}

	      طالما (بشيا_CODE (decl) == ARRAY_REF
		     || بشيا_CODE (decl) == INDIRECT_REF
		     || بشيا_CODE (decl) == COMPOUND_فرچ)
		{
		  إذا (بشيا_CODE (decl) == COMPOUND_فرچ)
		    {
		      decl = بشيا_OPERAND (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  وإلا إذا (بشيا_CODE (decl) == INDIRECT_REF)
		    {
		      dims.safe_تور (omp_dim (integer_zero_كلي,
					       integer_one_كلي, loc, true));
		      decl = بشيا_OPERAND (decl, 0);
		    }
		  وإلا  /* ARRAY_REF. */
		    {
		      بشيا index = بشيا_OPERAND (decl, 1);
		      dims.safe_تور (omp_dim (index, integer_one_كلي, loc,
					       true));
		      decl = بشيا_OPERAND (decl, 0);
		    }
		}

	      لكل (صحيح i = dims.length () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].كس_bound,
						dims[i].length);
	    }
	  وإلا إذا (بشيا_CODE (decl) == INDIRECT_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = بشيا_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_كلي,
					      integer_one_كلي);
	    }
	  وإلا إذا (بشيا_CODE (decl) == ARRAY_REF)
	    {
	      بشيا idx = بشيا_OPERAND (decl, 1);

	      decl = بشيا_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_كلي);
	    }
	  وإلا إذا (بشيا_CODE (decl) == NON_LVALUE_فرچ
		   || CONVERT_فرچ_P (decl))
	    decl = بشيا_OPERAND (decl, 0);

	  بشيا u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  اذهب next_item;
	}

      إذا (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->درج);

	  إذا (t == NULL_بشيا)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->درج);
	      t = error_mark_كلي;
	    }

	  c_parser_consume_token (parser);
	}
      وإلا إذا (c_parser_next_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).درج;
      وإلا
	{
	  c_parser_error (parser, "expected identifier");
	  اكسر;
	}

      إذا (t == error_mark_كلي)
	;
      وإلا إذا (kind != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  بدل (kind)
	    {
	    حالة OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      إذا (c_parser_peek_token (parser)->type != CPP_OPEN_SQUARE)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_كلي;
		  اكسر;
		}
	      /* FALLTHROUGH  */
	    حالة OMP_CLAUSE_MAP:
	    حالة OMP_CLAUSE_FROM:
	    حالة OMP_CLAUSE_TO:
	    start_component_ref:
	      طالما (c_parser_next_token_is (parser, CPP_DOT)
		     || c_parser_next_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  إذا (c_parser_next_token_is (parser, CPP_DEREF))
		    {
		      c_فرچ t_فرچ;
		      t_فرچ.درج = t;
		      t_فرچ.original_code = ERROR_MARK;
		      t_فرچ.original_type = عدم;
		      set_c_فرچ_source_range (&t_فرچ, op_loc, op_loc);
		      t_فرچ.m_decimal = 0;
		      t_فرچ = convert_lvalue_to_rvalue (op_loc, t_فرچ,
							 true, خطأ);
		      t = build_indirect_ref (op_loc, t_فرچ.درج, RO_ARROW);
		      arrow_loc = t_فرچ.get_location ();
		    }
		  c_parser_consume_token (parser);
		  إذا (!c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_كلي;
		      اكسر;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  بشيا ident = comp_tok->درج;
		  location_t comp_loc = comp_tok->location;
		  c_parser_consume_token (parser);
		  t = build_component_ref (op_loc, t, ident, comp_loc,
					   arrow_loc);
		}
	      /* FALLTHROUGH  */
	    حالة OMP_CLAUSE_AFFINITY:
	    حالة OMP_CLAUSE_DEPEND:
	    حالة OMP_CLAUSE_REDUCTION:
	    حالة OMP_CLAUSE_IN_REDUCTION:
	    حالة OMP_CLAUSE_TASK_REDUCTION:
	    حالة OMP_CLAUSE_HAS_DEVICE_ADDR:
	      array_section_p = خطأ;
	      dims.truncate (0);
	      طالما (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  بشيا كس_bound = NULL_بشيا, length = NULL_بشيا;
		  منطقي no_colon = خطأ;

		  c_parser_consume_token (parser);
		  إذا (!c_parser_next_token_is (parser, CPP_COLON))
		    {
		      location_t فرچ_loc
			= c_parser_peek_token (parser)->location;
		      c_فرچ فرچ = c_parser_expression (parser);
		      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ,
						       خطأ, true);
		      كس_bound = فرچ.درج;
		      loc = فرچ_loc;
		    }
		  إذا (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    {
		      length = integer_one_كلي;
		      no_colon = true;
		    }
		  وإلا
		    {
		      /* Look for `:'.  */
		      إذا (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_كلي;
			  اكسر;
			}
		      array_section_p = true;
		      إذا (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
			{
			  location_t فرچ_loc
			    = c_parser_peek_token (parser)->location;
			  c_فرچ فرچ = c_parser_expression (parser);
			  فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ,
							   خطأ, true);
			  length = فرچ.درج;
			}
		    }
		  /* Look for the closing `]'.  */
		  إذا (!c_parser_require (parser, CPP_CLOSE_SQUARE,
					 "expected %<]%>"))
		    {
		      t = error_mark_كلي;
		      اكسر;
		    }

		  dims.safe_تور (omp_dim (كس_bound, length, loc, no_colon));
		}

	      إذا (t != error_mark_كلي)
		{
		  إذا ((kind == OMP_CLAUSE_MAP
		       || kind == OMP_CLAUSE_FROM
		       || kind == OMP_CLAUSE_TO)
		      && !array_section_p
		      && (c_parser_next_token_is (parser, CPP_DOT)
			  || c_parser_next_token_is (parser, CPP_DEREF)))
		    {
		      لكل (unsigned i = 0; i < dims.length (); i++)
			{
			  gcc_assert (dims[i].length == integer_one_كلي);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].كس_bound);
			}
		      اذهب start_component_ref;
		    }
		  وإلا
		    لكل (unsigned i = 0; i < dims.length (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].كس_bound,
						   dims[i].length);
		}

	      إذا ((kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_كلي
		  && parser->tokens_avail != 2)
		{
		  إذا (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_كلي;
		    }
		  وإلا
		    {
		      parser->tokens = tokens.address ();
		      parser->tokens_avail = tokens.length ();

		      t = c_parser_فرچ_no_commas (parser, عدم).درج;
		      إذا (t != error_mark_كلي && parser->tokens_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_كلي;
			}
		    }
		}
	      اكسر;
	    افتراضي:
	      اكسر;
	    }

	  إذا (t != error_mark_كلي)
	    {
	      بشيا u = build_omp_clause (clause_loc, kind);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      وإلا  /* kind == OMP_CLAUSE_ERROR */
	list = بشيا_cons (t, build_empty_stmt (tloc), list);

      إذا (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}

    next_item:
      إذا (c_parser_next_token_is_not (parser, CPP_COMMA))
	اكسر;

      c_parser_consume_token (parser);
    }

  أرجع list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

ساكن بشيا
c_parser_omp_var_list_parens (c_parser *parser, تعداد omp_clause_code kind,
			      بشيا list, منطقي map_lvalue = خطأ)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  إذا (parser->in_omp_decl_attribute)
    {
      إذا (kind)
	{
	  بشيا u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = parser->in_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  أرجع u;
	}
      وإلا
	أرجع بشيا_cons (parser->in_omp_decl_attribute, NULL_بشيا, list);
    }

  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, kind, list, map_lvalue);
      parens.skip_until_found_close (parser);
    }
  أرجع list;
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

ساكن بشيا
c_parser_oacc_data_clause (c_parser *parser, pragma_omp_clause c_kind,
			   بشيا list)
{
  تعداد gomp_map_kind kind;
  بدل (c_kind)
    {
    حالة PRAGMA_OACC_CLAUSE_ATTACH:
      kind = GOMP_MAP_ATTACH;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_COPY:
      kind = GOMP_MAP_TOFROM;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_COPYIN:
      kind = GOMP_MAP_TO;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_COPYOUT:
      kind = GOMP_MAP_FROM;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_CREATE:
      kind = GOMP_MAP_ALLOC;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_DELETE:
      kind = GOMP_MAP_RELEASE;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_DETACH:
      kind = GOMP_MAP_DETACH;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_DEVICE:
      kind = GOMP_MAP_FORCE_TO;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      kind = GOMP_MAP_DEVICE_RESIDENT;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_LINK:
      kind = GOMP_MAP_LINK;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_NO_CREATE:
      kind = GOMP_MAP_IF_PRESENT;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_PRESENT:
      kind = GOMP_MAP_FORCE_PRESENT;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    حالة PRAGMA_OACC_CLAUSE_HOST:
      kind = GOMP_MAP_FORCE_FROM;
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }

  بشيا nl = list;
  منطقي readonly = خطأ;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      إذا (c_kind == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_NAME
	      && !strcmp (IDENTIFIER_POINTER (token->درج), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = true;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       خطأ);
      parens.skip_until_found_close (parser);
    }

  لكل (بشيا c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      إذا (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  أرجع nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

ساكن بشيا
c_parser_oacc_data_clause_deviceptr (c_parser *parser, بشيا list)
{
  بشيا vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, عدم);
  لكل (t = vars; t && t; t = بشيا_CHAIN (t))
    {
      بشيا v = بشيا_PURPOSE (t);
      location_t loc = فرچ_LOCATION (بشيا_درج (t));

      إذا (!VAR_P (v) && بشيا_CODE (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      وإلا إذا (بشيا_TYPE (v) == error_mark_كلي)
	;
      وإلا إذا (!POINTER_TYPE_P (بشيا_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      بشيا u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  أرجع list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

ساكن بشيا
c_parser_omp_clause_collapse (c_parser *parser, بشيا list)
{
  بشيا c, لمب = error_mark_كلي;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      لمب = c_parser_فرچ_no_commas (parser, عدم).درج;
      parens.skip_until_found_close (parser);
    }
  إذا (لمب == error_mark_كلي)
    أرجع list;
  mark_exp_read (لمب);
  لمب = c_fully_fold (لمب, خطأ, عدم);
  إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (لمب))
      || !بشيا_fits_shwi_p (لمب)
      || (n = بشيا_to_shwi (لمب)) <= 0
      || (صحيح) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      أرجع list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_فرچ (c) = لمب;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

ساكن بشيا
c_parser_omp_clause_copyin (c_parser *parser, بشيا list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

ساكن بشيا
c_parser_omp_clause_copyprivate (c_parser *parser, بشيا list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

ساكن بشيا
c_parser_omp_clause_default (c_parser *parser, بشيا list, منطقي is_oacc)
{
  تعداد omp_clause_default_kind kind = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  بشيا c;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;
  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);

      بدل (p[0])
	{
	حالة 'n':
	  إذا (strcmp ("none", p) != 0)
	    اذهب invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_NONE;
	  اكسر;

	حالة 'p':
	  إذا (is_oacc)
	    {
	      إذا (strcmp ("present", p) != 0)
		اذهب invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  وإلا
	    {
	      إذا (strcmp ("private", p) != 0)
		اذهب invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRIVATE;
	    }
	  اكسر;

	حالة 'f':
	  إذا (strcmp ("firstprivate", p) != 0 || is_oacc)
	    اذهب invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  اكسر;

	حالة 's':
	  إذا (strcmp ("shared", p) != 0 || is_oacc)
	    اذهب invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_SHARED;
	  اكسر;

	افتراضي:
	  اذهب invalid_kind;
	}

      c_parser_consume_token (parser);
    }
  وإلا
    {
    invalid_kind:
      إذا (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      وإلا
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_found_close (parser);

  إذا (kind == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    أرجع list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_KIND (c) = kind;

  أرجع c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

ساكن بشيا
c_parser_omp_clause_firstprivate (c_parser *parser, بشيا list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

ساكن بشيا
c_parser_omp_clause_final (c_parser *parser, بشيا list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      بشيا t, c;
      إذا (!parens.require_open (parser))
	t = error_mark_كلي;
      وإلا
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
	  t = convert_lvalue_to_rvalue (eloc, فرچ, true, true).درج;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, خطأ, عدم);
	  parens.skip_until_found_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_فرچ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }
  وإلا
    c_parser_error (parser, "expected %<(%>");

  أرجع list;
}

/* OpenMP 5.1:
   indirect [( expression )]
*/

ساكن بشيا
c_parser_omp_clause_indirect (c_parser *parser, بشيا list)
{
  location_t location = c_parser_peek_token (parser)->location;
  بشيا t;

  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      إذا (!parens.require_open (parser))
	أرجع list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (loc, فرچ, true, true);
      t = c_objc_common_truthvalue_conversion (loc, فرچ.درج);
      t = c_fully_fold (t, خطأ, عدم);
      إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (t))
	  || بشيا_CODE (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  أرجع list;
	}
      parens.skip_until_found_close (parser);
    }
  وإلا
    t = integer_one_كلي;

  check_no_duplicate_clause (list, OMP_CLAUSE_INDIRECT, "indirect");

  بشيا c = build_omp_clause (location, OMP_CLAUSE_INDIRECT);
  OMP_CLAUSE_INDIRECT_فرچ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
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

ساكن بشيا
c_parser_omp_clause_if (c_parser *parser, بشيا list, منطقي is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  تعداد بشيا_code if_modifier = ERROR_MARK;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (is_omp && c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      صحيح n = 2;
      إذا (strcmp (p, "cancel") == 0)
	if_modifier = VOID_CST;
      وإلا إذا (strcmp (p, "parallel") == 0)
	if_modifier = OMP_PARALLEL;
      وإلا إذا (strcmp (p, "simd") == 0)
	if_modifier = OMP_SIMD;
      وإلا إذا (strcmp (p, "task") == 0)
	if_modifier = OMP_TASK;
      وإلا إذا (strcmp (p, "taskloop") == 0)
	if_modifier = OMP_TASKLOOP;
      وإلا إذا (strcmp (p, "target") == 0)
	{
	  if_modifier = OMP_TARGET;
	  إذا (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	    {
	      p = IDENTIFIER_POINTER (c_parser_peek_2nd_token (parser)->درج);
	      إذا (strcmp ("data", p) == 0)
		if_modifier = OMP_TARGET_DATA;
	      وإلا إذا (strcmp ("update", p) == 0)
		if_modifier = OMP_TARGET_UPDATE;
	      وإلا إذا (strcmp ("enter", p) == 0)
		if_modifier = OMP_TARGET_ENTER_DATA;
	      وإلا إذا (strcmp ("exit", p) == 0)
		if_modifier = OMP_TARGET_EXIT_DATA;
	      إذا (if_modifier != OMP_TARGET)
		{
		  n = 3;
		  c_parser_consume_token (parser);
		}
	      وإلا
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<data%>, %<update%>, %<enter%> "
				 "or %<exit%>");
		  if_modifier = ERROR_MARK;
		}
	      إذا (if_modifier == OMP_TARGET_ENTER_DATA
		  || if_modifier == OMP_TARGET_EXIT_DATA)
		{
		  إذا (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_POINTER
				(c_parser_peek_2nd_token (parser)->درج);
		      إذا (strcmp ("data", p) == 0)
			n = 4;
		    }
		  إذا (n == 4)
		    c_parser_consume_token (parser);
		  وإلا
		    {
		      location_t loc
			= c_parser_peek_2nd_token (parser)->location;
		      error_at (loc, "expected %<data%>");
		      if_modifier = ERROR_MARK;
		    }
		}
	    }
	}
      إذا (if_modifier != ERROR_MARK)
	{
	  إذا (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    {
	      إذا (n > 2)
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<:%>");
		}
	      if_modifier = ERROR_MARK;
	    }
	}
    }

  location_t loc = c_parser_peek_token (parser)->location;
  c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
  فرچ = convert_lvalue_to_rvalue (loc, فرچ, true, true);
  بشيا t = c_objc_common_truthvalue_conversion (loc, فرچ.درج), c;
  t = c_fully_fold (t, خطأ, عدم);
  parens.skip_until_found_close (parser);

  لكل (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IF)
      {
	إذا (if_modifier != ERROR_MARK
	    && OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    ثابت حرف *p = عدم;
	    بدل (if_modifier)
	      {
	      حالة VOID_CST: p = "cancel"; اكسر;
	      حالة OMP_PARALLEL: p = "parallel"; اكسر;
	      حالة OMP_SIMD: p = "simd"; اكسر;
	      حالة OMP_TASK: p = "task"; اكسر;
	      حالة OMP_TASKLOOP: p = "taskloop"; اكسر;
	      حالة OMP_TARGET_DATA: p = "target data"; اكسر;
	      حالة OMP_TARGET: p = "target"; اكسر;
	      حالة OMP_TARGET_UPDATE: p = "target update"; اكسر;
	      حالة OMP_TARGET_ENTER_DATA: p = "target enter data"; اكسر;
	      حالة OMP_TARGET_EXIT_DATA: p = "target exit data"; اكسر;
	      افتراضي: gcc_unreachable ();
	      }
	    error_at (location, "too many %<if%> clauses with %qs modifier",
		      p);
	    أرجع list;
	  }
	وإلا إذا (OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    إذا (!is_omp)
	      error_at (location, "too many %<if%> clauses");
	    وإلا
	      error_at (location, "too many %<if%> clauses without modifier");
	    أرجع list;
	  }
	وإلا إذا (if_modifier == ERROR_MARK
		 || OMP_CLAUSE_IF_MODIFIER (c) == ERROR_MARK)
	  {
	    error_at (location, "if any %<if%> clause has modifier, then all "
				"%<if%> clauses have to use modifier");
	    أرجع list;
	  }
      }

  c = build_omp_clause (location, OMP_CLAUSE_IF);
  OMP_CLAUSE_IF_MODIFIER (c) = if_modifier;
  OMP_CLAUSE_IF_فرچ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

ساكن بشيا
c_parser_omp_clause_lastprivate (c_parser *parser, بشيا list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      منطقي conditional = خطأ;
      إذا (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  ثابت حرف *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
	  إذا (strcmp (p, "conditional") == 0)
	    {
	      conditional = true;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      بشيا nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      إذا (conditional)
	لكل (بشيا c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      أرجع nlist;
    }
  أرجع list;
}

/* OpenMP 3.1:
   mergeable */

ساكن بشيا
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_UNUSED, بشيا list)
{
  بشيا c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenMP 2.5:
   nowait */

ساكن بشيا
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_UNUSED, بشيا list)
{
  بشيا c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

ساكن بشيا
c_parser_omp_clause_لمب_threads (c_parser *parser, بشيا list)
{
  location_t لمب_threads_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t فرچ_loc = c_parser_peek_token (parser)->location;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
      بشيا c, t = فرچ.درج;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_found_close (parser);

      إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (فرچ_loc, LE_فرچ, boolean_type_كلي, t,
		       build_int_cst (بشيا_TYPE (t), 0));
      protected_set_فرچ_location (c, فرچ_loc);
      إذا (c == boolean_true_كلي)
	{
	  warning_at (فرچ_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_كلي;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_لمب_THREADS, "num_threads");

      c = build_omp_clause (لمب_threads_loc, OMP_CLAUSE_لمب_THREADS);
      OMP_CLAUSE_لمب_THREADS_فرچ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

ساكن بشيا
c_parser_omp_clause_لمب_tasks (c_parser *parser, بشيا list)
{
  location_t لمب_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      منطقي strict = خطأ;
      إذا (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج),
		     "strict") == 0)
	{
	  strict = true;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t فرچ_loc = c_parser_peek_token (parser)->location;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
      بشيا c, t = فرچ.درج;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_found_close (parser);

      إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (فرچ_loc, LE_فرچ, boolean_type_كلي, t,
			   build_int_cst (بشيا_TYPE (t), 0));
      إذا (CAN_HAVE_LOCATION_P (c))
	SET_فرچ_LOCATION (c, فرچ_loc);
      إذا (c == boolean_true_كلي)
	{
	  warning_at (فرچ_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_كلي;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_لمب_TASKS, "num_tasks");

      c = build_omp_clause (لمب_tasks_loc, OMP_CLAUSE_لمب_TASKS);
      OMP_CLAUSE_لمب_TASKS_فرچ (c) = t;
      OMP_CLAUSE_لمب_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

ساكن بشيا
c_parser_omp_clause_grainsize (c_parser *parser, بشيا list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      منطقي strict = خطأ;
      إذا (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج),
		     "strict") == 0)
	{
	  strict = true;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t فرچ_loc = c_parser_peek_token (parser)->location;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
      بشيا c, t = فرچ.درج;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_found_close (parser);

      إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (فرچ_loc, LE_فرچ, boolean_type_كلي, t,
			   build_int_cst (بشيا_TYPE (t), 0));
      إذا (CAN_HAVE_LOCATION_P (c))
	SET_فرچ_LOCATION (c, فرچ_loc);
      إذا (c == boolean_true_كلي)
	{
	  warning_at (فرچ_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_كلي;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_فرچ (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   priority ( expression ) */

ساكن بشيا
c_parser_omp_clause_priority (c_parser *parser, بشيا list)
{
  location_t priority_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t فرچ_loc = c_parser_peek_token (parser)->location;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
      بشيا c, t = فرچ.درج;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_found_close (parser);

      إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (فرچ_loc, LT_فرچ, boolean_type_كلي, t,
			   build_int_cst (بشيا_TYPE (t), 0));
      إذا (CAN_HAVE_LOCATION_P (c))
	SET_فرچ_LOCATION (c, فرچ_loc);
      إذا (c == boolean_true_كلي)
	{
	  warning_at (فرچ_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_كلي;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_PRIORITY, "priority");

      c = build_omp_clause (priority_loc, OMP_CLAUSE_PRIORITY);
      OMP_CLAUSE_PRIORITY_فرچ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   hint ( expression ) */

ساكن بشيا
c_parser_omp_clause_hint (c_parser *parser, بشيا list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t فرچ_loc = c_parser_peek_token (parser)->location;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
      بشيا c, t = فرچ.درج;
      t = c_fully_fold (t, خطأ, عدم);
      إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (t))
	  || بشيا_CODE (t) != INTEGER_CST
	  || بشيا_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  أرجع list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_فرچ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

ساكن بشيا
c_parser_omp_clause_filter (c_parser *parser, بشيا list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t فرچ_loc = c_parser_peek_token (parser)->location;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
      بشيا c, t = فرچ.درج;
      t = c_fully_fold (t, خطأ, عدم);
      إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_فرچ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

ساكن بشيا
c_parser_omp_clause_defaultmap (c_parser *parser, بشيا list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  بشيا c;
  ثابت حرف *p;
  تعداد omp_clause_defaultmap_kind behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  تعداد omp_clause_defaultmap_kind category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;
  إذا (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  وإلا إذا (!c_parser_next_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      اذهب out_err;
    }
  وإلا
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);

  بدل (p[0])
    {
    حالة 'a':
      إذا (strcmp ("alloc", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ALLOC;
      وإلا
	اذهب invalid_behavior;
      اكسر;

    حالة 'd':
      إذا (strcmp ("default", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
      وإلا
	اذهب invalid_behavior;
      اكسر;

    حالة 'f':
      إذا (strcmp ("firstprivate", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FIRSTPRIVATE;
      وإلا إذا (strcmp ("from", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FROM;
      وإلا
	اذهب invalid_behavior;
      اكسر;

    حالة 'n':
      إذا (strcmp ("none", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_NONE;
      وإلا
	اذهب invalid_behavior;
      اكسر;

    حالة 'p':
      إذا (strcmp ("present", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_PRESENT;
      وإلا
	اذهب invalid_behavior;
      اكسر;

    حالة 't':
      إذا (strcmp ("tofrom", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TOFROM;
      وإلا إذا (strcmp ("to", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TO;
      وإلا
	اذهب invalid_behavior;
      اكسر;

    افتراضي:
      اذهب invalid_behavior;
    }
  c_parser_consume_token (parser);

  إذا (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	اذهب out_err;
      إذا (!c_parser_next_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  اذهب out_err;
	}
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      بدل (p[0])
	{
	حالة 'a':
	  إذا (strcmp ("aggregate", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE;
	  وإلا إذا (strcmp ("all", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL;
	  وإلا
	    اذهب invalid_category;
	  اكسر;

	حالة 'p':
	  إذا (strcmp ("pointer", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER;
	  وإلا
	    اذهب invalid_category;
	  اكسر;

	حالة 's':
	  إذا (strcmp ("scalar", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR;
	  وإلا
	    اذهب invalid_category;
	  اكسر;

	افتراضي:
	  اذهب invalid_category;
	}

      c_parser_consume_token (parser);
    }
  parens.skip_until_found_close (parser);

  لكل (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEFAULTMAP
	&& (category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
	    || OMP_CLAUSE_DEFAULTMAP_CATEGORY (c) == category
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL)))
      {
	تعداد omp_clause_defaultmap_kind cat = category;
	location_t loc = OMP_CLAUSE_LOCATION (c);
	إذا (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
		&& (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		    != OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)))
	  cat = OMP_CLAUSE_DEFAULTMAP_CATEGORY (c);
	p = عدم;
	بدل (cat)
	  {
	  حالة OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED:
	    p = عدم;
	    اكسر;
	  حالة OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL:
	    p = "all";
	    اكسر;
	  حالة OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE:
	    p = "aggregate";
	    اكسر;
	  حالة OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER:
	    p = "pointer";
	    اكسر;
	  حالة OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR:
	    p = "scalar";
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }
	إذا (p)
	  error_at (loc, "too many %<defaultmap%> clauses with %qs category",
		    p);
	وإلا
	  error_at (loc, "too many %<defaultmap%> clauses with unspecified "
			 "category");
	اكسر;
      }

  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULTMAP);
  OMP_CLAUSE_DEFAULTMAP_SET_KIND (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 out_err:
  parens.skip_until_found_close (parser);
  أرجع list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

ساكن بشيا
c_parser_omp_clause_use_device_ptr (c_parser *parser, بشيا list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

ساكن بشيا
c_parser_omp_clause_use_device_addr (c_parser *parser, بشيا list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

ساكن بشيا
c_parser_omp_clause_has_device_addr (c_parser *parser, بشيا list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

ساكن بشيا
c_parser_omp_clause_is_device_ptr (c_parser *parser, بشيا list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

ساكن بشيا
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_code code,
				 بشيا list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  location_t فرچ_loc = c_parser_peek_token (parser)->location;
  c_فرچ فرچ = c_parser_expression (parser);
  فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
  بشيا c, t = فرچ.درج;
  t = c_fully_fold (t, خطأ, عدم);

  parens.skip_until_found_close (parser);

  إذا (t == error_mark_كلي)
    أرجع list;
  وإلا إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (t)))
    {
      error_at (فرچ_loc, "%qs expression must be integral",
		omp_clause_code_name[code]);
      أرجع list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (فرچ_loc, LE_فرچ, boolean_type_كلي, t,
		       build_int_cst (بشيا_TYPE (t), 0));
  protected_set_فرچ_location (c, فرچ_loc);
  إذا (c == boolean_true_كلي)
    {
      warning_at (فرچ_loc, 0,
		  "%qs value must be positive",
		  omp_clause_code_name[code]);
      t = integer_one_كلي;
    }

  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  c = build_omp_clause (loc, code);
  OMP_CLAUSE_OPERAND (c, 0) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
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

ساكن بشيا
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_code kind,
			    ثابت حرف *str, بشيا list)
{
  ثابت حرف *id = "num";
  بشيا ops[2] = { NULL_بشيا, NULL_بشيا }, c;

  إذا (kind == OMP_CLAUSE_VECTOR)
    id = "length";

  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      افعل
	{
	  c_token *next = c_parser_peek_token (parser);
	  صحيح idx = 0;

	  /* Gang static argument.  */
	  إذا (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		اذهب cleanup_error;

	      idx = 1;
	      إذا (ops[idx] != NULL_بشيا)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  اذهب cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      إذا (c_parser_next_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_كلي;

		  إذا (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      استمر;
		    }
		  وإلا
		    اكسر;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  وإلا إذا (c_parser_next_token_is (parser, CPP_NAME)
		   && strcmp (id, IDENTIFIER_POINTER (next->درج)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  إذا (ops[idx] != NULL_بشيا)
	    {
	      c_parser_error (parser, "unexpected argument");
	      اذهب cleanup_error;
	    }

	  location_t فرچ_loc = c_parser_peek_token (parser)->location;
	  c_فرچ cexpr = c_parser_فرچ_no_commas (parser, عدم);
	  cexpr = convert_lvalue_to_rvalue (فرچ_loc, cexpr, خطأ, true);
	  بشيا فرچ = cexpr.درج;
	  إذا (فرچ == error_mark_كلي)
	    اذهب cleanup_error;

	  فرچ = c_fully_fold (فرچ, خطأ, عدم);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (فرچ)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      أرجع list;
	    }

	  بشيا c = fold_build2_loc (فرچ_loc, LE_فرچ, boolean_type_كلي, فرچ,
				    build_int_cst (بشيا_TYPE (فرچ), 0));
	  إذا (c == boolean_true_كلي)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      فرچ = integer_one_كلي;
	    }

	  ops[idx] = فرچ;

	  إذا (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      استمر;
	    }
	  اكسر;
	}
      طالما (1);

      إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	اذهب cleanup_error;
    }

  check_no_duplicate_clause (list, kind, str);

  c = build_omp_clause (loc, kind);

  إذا (ops[1])
    OMP_CLAUSE_OPERAND (c, 1) = ops[1];

  OMP_CLAUSE_OPERAND (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;

 cleanup_error:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  أرجع list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

ساكن بشيا
c_parser_oacc_simple_clause (location_t loc, تعداد omp_clause_code code,
			     بشيا list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  بشيا c = build_omp_clause (loc, code);
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenACC:
   async [( int-expr )] */

ساكن بشيا
c_parser_oacc_clause_async (c_parser *parser, بشيا list)
{
  بشيا c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_كلي, GOMP_ASYNC_NOVAL);

  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_فرچ_no_commas (parser, عدم).درج;
      إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      وإلا إذا (t == error_mark_كلي
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	أرجع list;
    }
  وإلا
    t = c_fully_fold (t, خطأ, عدم);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_فرچ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  أرجع list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

ساكن بشيا
c_parser_oacc_clause_tile (c_parser *parser, بشيا list)
{
  بشيا c, فرچ = error_mark_كلي;
  location_t loc;
  بشيا tile = NULL_بشيا;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع list;

  افعل
    {
      إذا (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	أرجع list;

      إذا (c_parser_next_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  فرچ = integer_zero_كلي;
	}
      وإلا
	{
	  location_t فرچ_loc = c_parser_peek_token (parser)->location;
	  c_فرچ cexpr = c_parser_فرچ_no_commas (parser, عدم);
	  cexpr = convert_lvalue_to_rvalue (فرچ_loc, cexpr, خطأ, true);
	  فرچ = cexpr.درج;

	  إذا (فرچ == error_mark_كلي)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      أرجع list;
	    }

	  فرچ = c_fully_fold (فرچ, خطأ, عدم);

	  إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (فرچ))
	      || !بشيا_fits_shwi_p (فرچ)
	      || بشيا_to_shwi (فرچ) <= 0)
	    {
	      error_at (فرچ_loc, "%<tile%> argument needs positive"
			" integral constant");
	      فرچ = integer_zero_كلي;
	    }
	}

      tile = بشيا_cons (NULL_بشيا, فرچ, tile);
    }
  طالما (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN));

  /* Consume the trailing ')'.  */
  c_parser_consume_token (parser);

  c = build_omp_clause (loc, OMP_CLAUSE_TILE);
  tile = nreverse (tile);
  OMP_CLAUSE_TILE_LIST (c) = tile;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenACC:
   wait [( int-expr-list )] */

ساكن بشيا
c_parser_oacc_clause_wait (c_parser *parser, بشيا list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  وإلا
    {
      بشيا c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_كلي, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenACC 2.7:
   self [( expression )] */

ساكن بشيا
c_parser_oacc_compute_clause_self (c_parser *parser, بشيا list)
{
  بشيا t;
  location_t location = c_parser_peek_token (parser)->location;
  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (loc, فرچ, true, true);
      t = c_objc_common_truthvalue_conversion (loc, فرچ.درج);
      t = c_fully_fold (t, خطأ, عدم);
      parens.skip_until_found_close (parser);
    }
  وإلا
    t = truthvalue_true_كلي;

  لكل (بشيا c = list; c; c = OMP_CLAUSE_CHAIN (c))
    إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	أرجع list;
      }

  بشيا c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_فرچ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 5.0:
   order ( concurrent )

   OpenMP 5.1:
   order ( order-modifier : concurrent )

   order-modifier:
     reproducible
     unconstrained  */

ساكن بشيا
c_parser_omp_clause_order (c_parser *parser, بشيا list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  بشيا c;
  ثابت حرف *p;
  منطقي unconstrained = خطأ;
  منطقي reproducible = خطأ;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;
  إذا (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp (p, "unconstrained") == 0)
	unconstrained = true;
      وإلا إذا (strcmp (p, "reproducible") == 0)
	reproducible = true;
      وإلا
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  اذهب out_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  إذا (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      اذهب out_err;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
  إذا (strcmp (p, "concurrent") != 0)
    {
      c_parser_error (parser, "expected %<concurrent%>");
      اذهب out_err;
    }
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDER, "order");
  c = build_omp_clause (loc, OMP_CLAUSE_ORDER);
  OMP_CLAUSE_ORDER_UNCONSTRAINED (c) = unconstrained;
  OMP_CLAUSE_ORDER_REPRODUCIBLE (c) = reproducible;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 out_err:
  parens.skip_until_found_close (parser);
  أرجع list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

ساكن بشيا
c_parser_omp_clause_bind (c_parser *parser, بشيا list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  بشيا c;
  ثابت حرف *p;
  تعداد omp_clause_bind_kind kind = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;
  إذا (!c_parser_next_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_found_close (parser);
      أرجع list;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
  إذا (strcmp (p, "teams") == 0)
    kind = OMP_CLAUSE_BIND_TEAMS;
  وإلا إذا (strcmp (p, "parallel") == 0)
    kind = OMP_CLAUSE_BIND_PARALLEL;
  وإلا إذا (strcmp (p, "thread") != 0)
    اذهب invalid;
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

ساكن بشيا
c_parser_omp_clause_ordered (c_parser *parser, بشيا list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  بشيا c, لمب = NULL_بشيا;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      لمب = c_parser_فرچ_no_commas (parser, عدم).درج;
      parens.skip_until_found_close (parser);
    }
  إذا (لمب == error_mark_كلي)
    أرجع list;
  إذا (لمب)
    {
      mark_exp_read (لمب);
      لمب = c_fully_fold (لمب, خطأ, عدم);
      إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (لمب))
	  || !بشيا_fits_shwi_p (لمب)
	  || (n = بشيا_to_shwi (لمب)) <= 0
	  || (صحيح) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  أرجع list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_فرچ (c) = لمب;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

ساكن بشيا
c_parser_omp_clause_private (c_parser *parser, بشيا list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_PRIVATE, list);
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

ساكن بشيا
c_parser_omp_clause_reduction (c_parser *parser, تعداد omp_clause_code kind,
			       منطقي is_omp, بشيا list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      منطقي task = خطأ;
      منطقي inscan = خطأ;
      تعداد بشيا_code code = ERROR_MARK;
      بشيا reduc_id = NULL_بشيا;

      إذا (kind == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  إذا (c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  وإلا إذا (c_parser_next_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      ثابت حرف *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
	      إذا (strcmp (p, "task") == 0)
		task = true;
	      وإلا إذا (strcmp (p, "inscan") == 0)
		inscan = true;
	      إذا (task || inscan)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		}
	    }
	}

      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_PLUS:
	  code = PLUS_فرچ;
	  اكسر;
	حالة CPP_MULT:
	  code = MULT_فرچ;
	  اكسر;
	حالة CPP_MINUS:
	  إذا (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.add_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  code = MINUS_فرچ;
	  اكسر;
	حالة CPP_AND:
	  code = BIT_AND_فرچ;
	  اكسر;
	حالة CPP_XOR:
	  code = BIT_XOR_فرچ;
	  اكسر;
	حالة CPP_OR:
	  code = BIT_IOR_فرچ;
	  اكسر;
	حالة CPP_AND_AND:
	  code = TRUTH_ANDIF_فرچ;
	  اكسر;
	حالة CPP_OR_OR:
	  code = TRUTH_ORIF_فرچ;
	  اكسر;
        حالة CPP_NAME:
	  {
	    ثابت حرف *p
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
	    إذا (strcmp (p, "min") == 0)
	      {
		code = MIN_فرچ;
		اكسر;
	      }
	    إذا (strcmp (p, "max") == 0)
	      {
		code = MAX_فرچ;
		اكسر;
	      }
	    reduc_id = c_parser_peek_token (parser)->درج;
	    اكسر;
	  }
	افتراضي:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
	  أرجع list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (code, reduc_id);
      إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  بشيا nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, kind, list);
	  لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      بشيا d = OMP_CLAUSE_DECL (c), type;
	      إذا (بشيا_CODE (d) != OMP_ARRAY_SECTION)
		type = بشيا_TYPE (d);
	      وإلا
		{
		  صحيح cnt = 0;
		  بشيا t;
		  لكل (t = d;
		      بشيا_CODE (t) == OMP_ARRAY_SECTION;
		      t = بشيا_OPERAND (t, 0))
		    cnt++;
		  type = بشيا_TYPE (t);
		  طالما (cnt > 0)
		    {
		      إذا (بشيا_CODE (type) != POINTER_TYPE
			  && بشيا_CODE (type) != ARRAY_TYPE)
			اكسر;
		      type = بشيا_TYPE (type);
		      cnt--;
		    }
		}
	      طالما (بشيا_CODE (type) == ARRAY_TYPE)
		type = بشيا_TYPE (type);
	      OMP_CLAUSE_REDUCTION_CODE (c) = code;
	      إذا (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      وإلا إذا (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      إذا (code == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || بشيا_CODE (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_found_close (parser);
    }
  أرجع list;
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

ساكن بشيا
c_parser_omp_clause_schedule (c_parser *parser, بشيا list)
{
  بشيا c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  صحيح modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  c = build_omp_clause (loc, OMP_CLAUSE_SCHEDULE);

  location_t comma = UNKNOWN_LOCATION;
  طالما (c_parser_next_token_is (parser, CPP_NAME))
    {
      بشيا kind = c_parser_peek_token (parser)->درج;
      ثابت حرف *p = IDENTIFIER_POINTER (kind);
      إذا (strcmp ("simd", p) == 0)
	OMP_CLAUSE_SCHEDULE_SIMD (c) = 1;
      وإلا إذا (strcmp ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_MONOTONIC;
      وإلا إذا (strcmp ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_NONMONOTONIC;
      وإلا
	اكسر;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      إذا (nmodifiers++ == 0
	  && c_parser_next_token_is (parser, CPP_COMMA))
	{
	  comma = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	}
      وإلا
	{
	  c_parser_require (parser, CPP_COLON, "expected %<:%>");
	  اكسر;
	}
    }
  إذا (comma != UNKNOWN_LOCATION)
    error_at (comma, "expected %<:%>");

  إذا ((modifiers & (OMP_CLAUSE_SCHEDULE_MONOTONIC
		    | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
      == (OMP_CLAUSE_SCHEDULE_MONOTONIC
	  | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      بشيا kind = c_parser_peek_token (parser)->درج;
      ثابت حرف *p = IDENTIFIER_POINTER (kind);

      بدل (p[0])
	{
	حالة 'd':
	  إذا (strcmp ("dynamic", p) != 0)
	    اذهب invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_DYNAMIC;
	  اكسر;

        حالة 'g':
	  إذا (strcmp ("guided", p) != 0)
	    اذهب invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_GUIDED;
	  اكسر;

	حالة 'r':
	  إذا (strcmp ("runtime", p) != 0)
	    اذهب invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_RUNTIME;
	  اكسر;

	افتراضي:
	  اذهب invalid_kind;
	}
    }
  وإلا إذا (c_parser_next_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_STATIC;
  وإلا إذا (c_parser_next_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_AUTO;
  وإلا
    اذهب invalid_kind;

  c_parser_consume_token (parser);
  إذا (c_parser_next_token_is (parser, CPP_COMMA))
    {
      location_t here;
      c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (here, فرچ, خطأ, true);
      t = فرچ.درج;
      t = c_fully_fold (t, خطأ, عدم);

      إذا (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_RUNTIME)
	error_at (here, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      وإلا إذا (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_AUTO)
	error_at (here,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      وإلا إذا (بشيا_CODE (بشيا_TYPE (t)) == INTEGER_TYPE
	       || بشيا_CODE (بشيا_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  بشيا s = fold_build2_loc (loc, LE_فرچ, boolean_type_كلي, t,
				    build_int_cst (بشيا_TYPE (t), 0));
	  protected_set_فرچ_location (s, loc);
	  إذا (s == boolean_true_كلي)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_كلي;
	    }
	  OMP_CLAUSE_SCHEDULE_CHUNK_فرچ (c) = t;
	}
      وإلا
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_found_close (parser);
    }
  وإلا
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_SCHEDULE_KIND (c)
    = (تعداد omp_clause_schedule_kind)
      (OMP_CLAUSE_SCHEDULE_KIND (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_SCHEDULE, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 invalid_kind:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  أرجع list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

ساكن بشيا
c_parser_omp_clause_shared (c_parser *parser, بشيا list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

ساكن بشيا
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_UNUSED, بشيا list)
{
  بشيا c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_UNTIED, "untied");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_UNTIED);
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenMP 4.0:
   inbranch
   notinbranch */

ساكن بشيا
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_UNUSED,
			    تعداد omp_clause_code code, بشيا list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  بشيا c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

ساكن بشيا
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_UNUSED,
				تعداد omp_clause_code code, بشيا list)
{
  بشيا c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenMP 4.5:
   nogroup */

ساكن بشيا
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_UNUSED, بشيا list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  بشيا c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.5:
   simd
   threads */

ساكن بشيا
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_UNUSED,
				 تعداد omp_clause_code code, بشيا list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);
  بشيا c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

ساكن بشيا
c_parser_omp_clause_لمب_teams (c_parser *parser, بشيا list)
{
  location_t لمب_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t upper_loc = c_parser_peek_token (parser)->location;
      location_t lower_loc = UNKNOWN_LOCATION;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (upper_loc, فرچ, خطأ, true);
      بشيا c, upper = فرچ.درج, lower = NULL_بشيا;
      upper = c_fully_fold (upper, خطأ, عدم);

      إذا (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  lower_loc = upper_loc;
	  lower = upper;
	  upper_loc = c_parser_peek_token (parser)->location;
	  فرچ = c_parser_فرچ_no_commas (parser, عدم);
	  فرچ = convert_lvalue_to_rvalue (upper_loc, فرچ, خطأ, true);
	  upper = فرچ.درج;
	  upper = c_fully_fold (upper, خطأ, عدم);
	}

      parens.skip_until_found_close (parser);

      إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (upper))
	  || (lower && !INTEGRAL_TYPE_P (بشيا_TYPE (lower))))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (upper_loc, LE_فرچ, boolean_type_كلي, upper,
			   build_int_cst (بشيا_TYPE (upper), 0));
      protected_set_فرچ_location (c, upper_loc);
      إذا (c == boolean_true_كلي)
	{
	  warning_at (upper_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  upper = integer_one_كلي;
	}
      إذا (lower)
	{
	  c = fold_build2_loc (lower_loc, LE_فرچ, boolean_type_كلي, lower,
			       build_int_cst (بشيا_TYPE (lower), 0));
	  protected_set_فرچ_location (c, lower_loc);
	  إذا (c == boolean_true_كلي)
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      lower = NULL_بشيا;
	    }
	  وإلا إذا (بشيا_CODE (lower) == INTEGER_CST
		   && بشيا_CODE (upper) == INTEGER_CST
		   && بشيا_int_cst_lt (upper, lower))
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", lower, upper);
	      lower = NULL_بشيا;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_لمب_TEAMS, "num_teams");

      c = build_omp_clause (لمب_teams_loc, OMP_CLAUSE_لمب_TEAMS);
      OMP_CLAUSE_لمب_TEAMS_UPPER_فرچ (c) = upper;
      OMP_CLAUSE_لمب_TEAMS_LOWER_فرچ (c) = lower;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

ساكن بشيا
c_parser_omp_clause_thread_limit (c_parser *parser, بشيا list)
{
  location_t لمب_thread_limit_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t فرچ_loc = c_parser_peek_token (parser)->location;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
      بشيا c, t = فرچ.درج;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_found_close (parser);

      إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (فرچ_loc, LE_فرچ, boolean_type_كلي, t,
			   build_int_cst (بشيا_TYPE (t), 0));
      protected_set_فرچ_location (c, فرچ_loc);
      إذا (c == boolean_true_كلي)
	{
	  warning_at (فرچ_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_كلي;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_LIMIT,
				 "thread_limit");

      c = build_omp_clause (لمب_thread_limit_loc, OMP_CLAUSE_THREAD_LIMIT);
      OMP_CLAUSE_THREAD_LIMIT_فرچ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

ساكن بشيا
c_parser_omp_clause_aligned (c_parser *parser, بشيا list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  بشيا nl, c;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  إذا (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t فرچ_loc = c_parser_peek_token (parser)->location;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
      بشيا alignment = فرچ.درج;
      alignment = c_fully_fold (alignment, خطأ, عدم);
      إذا (بشيا_CODE (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (بشيا_TYPE (alignment))
	  || بشيا_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_بشيا;
	}

      لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_found_close (parser);
  أرجع nl;
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

ساكن بشيا
c_parser_omp_clause_allocate (c_parser *parser, بشيا list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  بشيا nl, c;
  بشيا allocator = NULL_بشيا;
  بشيا align = NULL_بشيا;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا ((c_parser_next_token_is_not (parser, CPP_NAME)
       && c_parser_next_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      منطقي has_modifiers = خطأ;
      بشيا orig_type = NULL_بشيا;
      إذا (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  unsigned صحيح n = 3;
	  ثابت حرف *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
	  إذا ((strcmp (p, "allocator") == 0 || strcmp (p, "align") == 0)
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = true;
	      وإلا إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  ثابت حرف *q = IDENTIFIER_POINTER (tok->درج);
		  n += 4;
		  إذا ((strcmp (q, "allocator") == 0
		       || strcmp (q, "align") == 0)
		      && c_parser_check_balanced_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = true;
		}
	    }
	  إذا (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t فرچ_loc = c_parser_peek_token (parser)->location;
	      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
	      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
	      إذا (فرچ.درج == error_mark_كلي)
		;
	      وإلا إذا (strcmp (p, "allocator") == 0)
		{
		  allocator = فرچ.درج;
		  allocator = c_fully_fold (allocator, خطأ, عدم);
		  orig_type = فرچ.original_type
			      ? فرچ.original_type : بشيا_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      وإلا
		{
		  align = فرچ.درج;
		  align = c_fully_fold (align, خطأ, عدم);
		}
	      parens2.skip_until_found_close (parser);
	      إذا (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  ثابت حرف *q = "";
		  إذا (c_parser_next_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_POINTER (tok->درج);
		  إذا (strcmp (q, "allocator") != 0 && strcmp (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_found_close (parser);
		      أرجع list;
		    }
		  وإلا إذا (strcmp (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_found_close (parser);
		      أرجع list;
		    }
		  c_parser_consume_token (parser);
		  إذا (!parens2.require_open (parser))
		    {
		      parens.skip_until_found_close (parser);
		      أرجع list;
		    }
		  فرچ_loc = c_parser_peek_token (parser)->location;
		  فرچ = c_parser_فرچ_no_commas (parser, عدم);
		  فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ,
						   true);
		  إذا (strcmp (q, "allocator") == 0)
		    {
		      allocator = فرچ.درج;
		      allocator = c_fully_fold (allocator, خطأ, عدم);
		      orig_type = فرچ.original_type
				  ? فرچ.original_type : بشيا_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  وإلا
		    {
		      align = فرچ.درج;
		      align = c_fully_fold (align, خطأ, عدم);
		    }
		  parens2.skip_until_found_close (parser);
		}
	    }
	}
      إذا (!has_modifiers)
	{
	  location_t فرچ_loc = c_parser_peek_token (parser)->location;
	  c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
	  فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
	  إذا (فرچ.درج != error_mark_كلي)
	    {
	      allocator = فرچ.درج;
	      allocator = c_fully_fold (allocator, خطأ, عدم);
	      orig_type = فرچ.original_type
			  ? فرچ.original_type : بشيا_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      إذا (allocator
	  && (!INTEGRAL_TYPE_P (بشيا_TYPE (allocator))
	      || بشيا_CODE (orig_type) != ENUMERAL_TYPE
	      || (TYPE_NAME (orig_type)
		  != get_identifier ("omp_allocator_handle_t"))))
        {
          error_at (clause_loc, "%<allocate%> clause allocator expression "
				"has type %qT rather than "
				"%<omp_allocator_handle_t%>",
				بشيا_TYPE (allocator));
          allocator = NULL_بشيا;
        }
      إذا (align
	  && (!INTEGRAL_TYPE_P (بشيا_TYPE (align))
	      || !بشيا_fits_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_بشيا;
	}
      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_found_close (parser);
	  أرجع list;
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALLOCATE, list);

  إذا (allocator || align)
    لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      {
	OMP_CLAUSE_ALLOCATE_ALLOCATOR (c) = allocator;
	OMP_CLAUSE_ALLOCATE_ALIGN (c) = align;
      }

  parens.skip_until_found_close (parser);
  أرجع nl;
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

ساكن بشيا
c_parser_omp_clause_uses_allocators (c_parser *parser, بشيا list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  بشيا nl = list;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

parse_next:

  منطقي has_modifiers = خطأ;
  منطقي seen_allocators = خطأ;
  بشيا memspace_فرچ = NULL_بشيا;
  بشيا traits_var = NULL_بشيا;

  إذا (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      unsigned صحيح n = 3;
      ثابت حرف *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا ((strcmp (p, "traits") == 0 || strcmp (p, "memspace") == 0)
	  && c_parser_check_balanced_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = true;
	  وإلا إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      ثابت حرف *q = IDENTIFIER_POINTER (tok->درج);
	      n += 4;
	      إذا ((strcmp (q, "traits") == 0
		   || strcmp (q, "memspace") == 0)
		  && c_parser_check_balanced_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = true;
		  إذا ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      ثابت حرف *m = IDENTIFIER_POINTER (tok->درج);
		      إذا (strcmp (p, m) == 0 || strcmp (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  اذهب end;
			}
		    }
		}
	    }
	}
      إذا (has_modifiers)
	{
	  c_parser_consume_token (parser);
	  matching_parens parens2;
	  parens2.require_open (parser);
	  c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
	  إذا (فرچ.درج == error_mark_كلي)
	    ;
	  وإلا إذا (strcmp (p, "traits") == 0)
	    {
	      traits_var = فرچ.درج;
	      traits_var = c_fully_fold (traits_var, خطأ, عدم);
	      mark_exp_read (traits_var);
	    }
	  وإلا
	    {
	      memspace_فرچ = فرچ.درج;
	      memspace_فرچ = c_fully_fold (memspace_فرچ, خطأ, عدم);
	    }
	  parens2.skip_until_found_close (parser);
	  إذا (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      ثابت حرف *q = "";
	      إذا (c_parser_next_token_is (parser, CPP_NAME))
		q = IDENTIFIER_POINTER (tok->درج);
	      إذا (strcmp (q, "traits") != 0 && strcmp (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_found_close (parser);
		  أرجع list;
		}
	      وإلا إذا (strcmp (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_found_close (parser);
		  أرجع list;
		}
	      c_parser_consume_token (parser);
	      إذا (!parens2.require_open (parser))
		{
		  parens.skip_until_found_close (parser);
		  أرجع list;
		}
	      فرچ = c_parser_فرچ_no_commas (parser, عدم);
	      إذا (strcmp (q, "traits") == 0)
		{
		  traits_var = فرچ.درج;
		  traits_var = c_fully_fold (traits_var, خطأ, عدم);
		  mark_exp_read (traits_var);
		}
	      وإلا
		{
		  memspace_فرچ = فرچ.درج;
		  memspace_فرچ = c_fully_fold (memspace_فرچ, خطأ, عدم);
		}
	      parens2.skip_until_found_close (parser);
	    }
	  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    اذهب end;
	}
    }

  طالما (c_parser_next_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      ثابت حرف *tok_s = IDENTIFIER_POINTER (tok->درج);
      بشيا t = lookup_name (tok->درج);
      إذا (t == NULL_بشيا)
	{
	  undeclared_variable (tok->location, tok->درج);
	  t = error_mark_كلي;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      بشيا legacy_traits = NULL_بشيا;
      إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  ثابت حرف *tok_a
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
	  c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_found_close (parser);

	  إذا (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      اذهب end;
	    }
	  legacy_traits = c_fully_fold (فرچ.درج, خطأ, عدم);
	  إذا (legacy_traits == error_mark_كلي)
	    اذهب end;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  إذا (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.add_fixit_replace (alloc_loc, "traits");
	      richloc.add_fixit_سك_after (close_loc, ": ");
	      richloc.add_fixit_سك_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      إذا (seen_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  اذهب end;
	}
      seen_allocators = true;

      بشيا c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_USES_ALLOCATORS);
      OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c) = memspace_فرچ;
      OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }

  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      اذهب parse_next;
    }

 end:
  parens.skip_until_found_close (parser);
  أرجع nl;
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

ساكن بشيا
c_parser_omp_clause_linear (c_parser *parser, بشيا list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  بشيا nl, c, step;
  تعداد omp_clause_linear_kind kind = OMP_CLAUSE_LINEAR_DEFAULT;
  منطقي old_linear_modifier = خطأ;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      ثابت حرف *p = IDENTIFIER_POINTER (tok->درج);
      إذا (strcmp ("val", p) == 0)
	kind = OMP_CLAUSE_LINEAR_VAL;
      إذا (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	kind = OMP_CLAUSE_LINEAR_DEFAULT;
      إذا (kind != OMP_CLAUSE_LINEAR_DEFAULT)
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

  إذا (kind != OMP_CLAUSE_LINEAR_DEFAULT)
    {
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
    }

  إذا (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t فرچ_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = فرچ_loc;
      منطقي has_modifiers = خطأ;
      إذا (kind == OMP_CLAUSE_LINEAR_DEFAULT
	  && c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  ثابت حرف *p = IDENTIFIER_POINTER (tok->درج);
	  unsigned صحيح pos = 0;
	  إذا (strcmp ("val", p) == 0)
	    pos = 2;
	  وإلا إذا (strcmp ("step", p) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      pos = 3;
	      إذا (c_parser_check_balanced_raw_token_sequence (parser, &pos)
		  && (c_parser_peek_nth_token_raw (parser, pos)->type
		      == CPP_CLOSE_PAREN))
		++pos;
	      وإلا
		pos = 0;
	    }
	  إذا (pos)
	    {
	      tok = c_parser_peek_nth_token_raw (parser, pos);
	      إذا (tok->type == CPP_COMMA || tok->type == CPP_CLOSE_PAREN)
		has_modifiers = true;
	    }
	}
      إذا (has_modifiers)
	{
	  step = NULL_بشيا;
	  طالما (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      ثابت حرف *p = IDENTIFIER_POINTER (tok->درج);
	      إذا (strcmp ("val", p) == 0)
		{
		  إذا (kind != OMP_CLAUSE_LINEAR_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  kind = OMP_CLAUSE_LINEAR_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      وإلا إذا (strcmp ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  إذا (parens2.require_open (parser))
		    {
		      إذا (step)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      فرچ_loc = c_parser_peek_token (parser)->location;
		      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
		      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ,
						       true);
		      step = c_fully_fold (فرچ.درج, خطأ, عدم);
		      إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (step)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  step = integer_one_كلي;
			}
		      parens2.skip_until_found_close (parser);
		    }
		  وإلا
		    اكسر;
		}
	      وإلا
		اكسر;
	      إذا (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  استمر;
		}
	      اكسر;
	    }
	  إذا (!step)
	    step = integer_one_كلي;
	}
      وإلا
	{
	  c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
	  فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
	  step = c_fully_fold (فرچ.درج, خطأ, عدم);
	  إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (step)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      step = integer_one_كلي;
	    }
	}

    }
  وإلا
    step = integer_one_كلي;

  لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_LINEAR_STEP (c) = step;
      OMP_CLAUSE_LINEAR_KIND (c) = kind;
      OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c) = old_linear_modifier;
    }

  إذا (old_linear_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      إذا (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_remove (rm1_loc);
	  إذا (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.add_fixit_remove (rm2_loc);
	      richloc.add_fixit_سك_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.add_fixit_سك_before (close_loc, ")");
	    }
	  وإلا
	    richloc.add_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_found_close (parser);
  أرجع nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

ساكن بشيا
c_parser_omp_clause_nontemporal (c_parser *parser, بشيا list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

ساكن بشيا
c_parser_omp_clause_safelen (c_parser *parser, بشيا list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  بشيا c, t;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  location_t فرچ_loc = c_parser_peek_token (parser)->location;
  c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
  فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
  t = فرچ.درج;
  t = c_fully_fold (t, خطأ, عدم);
  إذا (بشيا_CODE (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (بشيا_TYPE (t))
      || بشيا_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_بشيا;
    }

  parens.skip_until_found_close (parser);
  إذا (t == NULL_بشيا || t == error_mark_كلي)
    أرجع list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_فرچ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

ساكن بشيا
c_parser_omp_clause_simdlen (c_parser *parser, بشيا list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  بشيا c, t = NULL_بشيا, type = NULL_بشيا, مي_ربو = NULL_بشيا;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  unsigned pos = 3;
  إذا (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج),
		 "scaled") == 0
      && c_parser_check_balanced_raw_token_sequence (parser, &pos)
      && c_parser_peek_nth_token_raw (parser, ++pos)->type == CPP_COLON)
    {
      c_parser_consume_token (parser);
      matching_parens parens2;
      parens2.require_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      بنية c_type_name *ctype = c_parser_type_name (parser);
      إذا (ctype == عدم
	  || (type = groktypename (ctype, عدم, عدم)) == عدم
	  || (!INTEGRAL_TYPE_P (type)
	      && !SCALAR_FLOAT_TYPE_P (type)
	      && بشيا_CODE (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_كلي;
	}
      وإلا إذا (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
	  فرچ = convert_lvalue_to_rvalue (loc, فرچ, خطأ, true);
	  مي_ربو = فرچ.درج;
	  مي_ربو = c_fully_fold (مي_ربو, خطأ, عدم);
	  إذا (بشيا_CODE (مي_ربو) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (بشيا_TYPE (مي_ربو))
	      || بشيا_int_cst_sgn (مي_ربو) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_كلي;
	    }
	}
      parens2.skip_until_found_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  إذا (type != error_mark_كلي)
    {
      location_t فرچ_loc = c_parser_peek_token (parser)->location;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
      t = فرچ.درج;
      t = c_fully_fold (t, خطأ, عدم);
      إذا (بشيا_CODE (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (بشيا_TYPE (t))
	  || بشيا_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_بشيا;
	}
    }

  parens.skip_until_found_close (parser);
  إذا (type == error_mark_كلي || t == NULL_بشيا || t == error_mark_كلي)
    أرجع list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_فرچ (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_مي_ربو (c) = مي_ربو;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

ساكن بشيا
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   بشيا list, منطقي depend_p)
{
  بشيا vec = عدم;
  إذا (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      أرجع list;
    }

  إذا (!depend_p)
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_لمب
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  بشيا val = c_parser_peek_nth_token (parser, 3)->درج;
	  إذا (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      بشيا u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      أرجع u;
	    }
	}
    }



  طالما (c_parser_next_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_kind == C_ID_ID)
    {
      بشيا t = lookup_name (c_parser_peek_token (parser)->درج);
      بشيا addend = عدم;

      إذا (t == NULL_بشيا)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->درج);
	  t = error_mark_كلي;
	}

      c_parser_consume_token (parser);

      منطقي neg = خطأ;
      إذا (c_parser_next_token_is (parser, CPP_MINUS))
	neg = true;
      وإلا إذا (!c_parser_next_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_كلي;
	  neg = خطأ;
	  اذهب add_to_vector;
	}
      c_parser_consume_token (parser);

      إذا (c_parser_next_token_is_not (parser, CPP_لمب))
	{
	  c_parser_error (parser, "expected integer");
	  أرجع list;
	}

      addend = c_parser_peek_token (parser)->درج;
      إذا (بشيا_CODE (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  أرجع list;
	}
      c_parser_consume_token (parser);

    add_to_vector:
      إذا (t != error_mark_كلي)
	{
	  vec = بشيا_cons (addend, t, vec);
	  إذا (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      إذا (c_parser_next_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_kind != C_ID_ID)
	اكسر;

      c_parser_consume_token (parser);
    }

  إذا (vec == NULL_بشيا)
    أرجع list;

  بشيا u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
  OMP_CLAUSE_DOACROSS_DEPEND (u) = depend_p;
  OMP_CLAUSE_DECL (u) = nreverse (vec);
  OMP_CLAUSE_CHAIN (u) = list;
  أرجع u;
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

ساكن بشيا
c_parser_omp_iterators (c_parser *parser)
{
  بشيا ret = NULL_بشيا, *last = &ret;
  c_parser_consume_token (parser);

  تور_scope ();

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع error_mark_كلي;

  افعل
    {
      بشيا iter_type = NULL_بشيا, type_فرچ = NULL_بشيا;
      إذا (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
	{
	  بنية c_type_name *type = c_parser_type_name (parser);
	  إذا (type != عدم)
	    iter_type = groktypename (type, &type_فرچ, عدم);
	}
      إذا (iter_type == NULL_بشيا)
	iter_type = integer_type_كلي;

      location_t loc = c_parser_peek_token (parser)->location;
      إذا (!c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  اكسر;
	}

      بشيا id = c_parser_peek_token (parser)->درج;
      c_parser_consume_token (parser);

      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	اكسر;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (eloc, فرچ, true, خطأ);
      بشيا begin = فرچ.درج;

      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	اكسر;

      eloc = c_parser_peek_token (parser)->location;
      فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (eloc, فرچ, true, خطأ);
      بشيا end = فرچ.درج;

      بشيا step = integer_one_كلي;
      إذا (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  فرچ = c_parser_فرچ_no_commas (parser, عدم);
	  فرچ = convert_lvalue_to_rvalue (eloc, فرچ, true, خطأ);
	  step = فرچ.درج;
	}

      بشيا iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *last = make_omp_iterator ();
      OMP_ITERATOR_VAR (*last) = iter_var;
      OMP_ITERATOR_BEGIN (*last) = begin;
      OMP_ITERATOR_END (*last) = end;
      OMP_ITERATOR_STEP (*last) = step;
      last = &بشيا_CHAIN (*last);

      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  استمر;
	}
      اكسر;
    }
  طالما (1);

  parens.skip_until_found_close (parser);
  أرجع ret ? ret : error_mark_كلي;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

ساكن بشيا
c_parser_omp_clause_affinity (c_parser *parser, بشيا list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  بشيا nl, iterators = NULL_بشيا;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      منطقي parse_iter = ((strcmp ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      إذا (parse_iter)
	{
	  unsigned n = 3;
	  parse_iter = (c_parser_check_balanced_raw_token_sequence (parser, &n)
			&& (c_parser_peek_nth_token_raw (parser, n)->type
			    == CPP_CLOSE_PAREN)
			&& (c_parser_peek_nth_token_raw (parser, n + 1)->type
			    == CPP_COLON));
	}
      إذا (parse_iter)
	{
	  iterators = c_parser_omp_iterators (parser);
	  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    {
	      إذا (iterators)
		چرو_scope ();
	      parens.skip_until_found_close (parser);
	      أرجع list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  إذا (iterators)
    {
      بشيا block = چرو_scope ();
      إذا (iterators != error_mark_كلي)
	{
	  OMP_ITERATOR_BLOCK (iterators) = block;
	  لكل (بشيا c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_بشيا_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  أرجع nl;
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

ساكن بشيا
c_parser_omp_clause_depend (c_parser *parser, بشيا list, location_t here)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  تعداد omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_LAST;
  تعداد omp_clause_doacross_kind dkind = OMP_CLAUSE_DOACROSS_LAST;
  بشيا nl, c, iterators = NULL_بشيا;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  افعل
    {
      إذا (c_parser_next_token_is_not (parser, CPP_NAME))
	اذهب invalid_kind;

      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp ("iterator", p) == 0 && iterators == NULL_بشيا)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  استمر;
	}
      إذا (strcmp ("in", p) == 0)
	kind = OMP_CLAUSE_DEPEND_IN;
      وإلا إذا (strcmp ("inout", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUT;
      وإلا إذا (strcmp ("inoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUTSET;
      وإلا إذا (strcmp ("mutexinoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      وإلا إذا (strcmp ("out", p) == 0)
	kind = OMP_CLAUSE_DEPEND_OUT;
      وإلا إذا (strcmp ("depobj", p) == 0)
	kind = OMP_CLAUSE_DEPEND_DEPOBJ;
      وإلا إذا (strcmp ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      وإلا إذا (strcmp ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SOURCE;
	}
      وإلا
	اذهب invalid_kind;
      اكسر;
    }
  طالما (1);

  c_parser_consume_token (parser);

  إذا (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_SOURCE
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      چرو_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_SOURCE ? "source" : "sink");
      iterators = NULL_بشيا;
    }

  إذا (dkind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_بشيا;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_found_close (parser);
      أرجع c;
    }

  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    اذهب resync_fail;

  إذا (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, true);
  وإلا
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      إذا (iterators)
	{
	  بشيا block = چرو_scope ();
	  إذا (iterators == error_mark_كلي)
	    iterators = NULL_بشيا;
	  وإلا
	    OMP_ITERATOR_BLOCK (iterators) = block;
	}

      لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_KIND (c) = kind;
	  إذا (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_بشيا_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  أرجع nl;

 invalid_kind:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  إذا (iterators)
    چرو_scope ();
  أرجع list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

ساكن بشيا
c_parser_omp_clause_doacross (c_parser *parser, بشيا list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  تعداد omp_clause_doacross_kind kind = OMP_CLAUSE_DOACROSS_LAST;
  بشيا nl;
  ثابت حرف *p;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_next_token_is_not (parser, CPP_NAME))
    اذهب invalid_kind;

  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
  إذا (strcmp ("sink", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SINK;
  وإلا إذا (strcmp ("source", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SOURCE;
  وإلا
    اذهب invalid_kind;

  c_parser_consume_token (parser);

  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    اذهب resync_fail;

  إذا (kind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      إذا (c_parser_next_token_is (parser, CPP_NAME)
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (nl) = OMP_CLAUSE_DOACROSS_SOURCE;
      OMP_CLAUSE_DECL (nl) = NULL_بشيا;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  وإلا
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, خطأ);

  parens.skip_until_found_close (parser);
  أرجع nl;

 invalid_kind:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  أرجع list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

ساكن بشيا
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, بشيا list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  تعداد omp_clause_fallback_kind kind = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  unsigned n = 3;
  إذا (c_parser_next_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  أرجع list;
	}
      c_parser_consume_token (parser);
      إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	أرجع list;
      p = "";
      إذا (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp (p, "abort") == 0)
	kind = OMP_CLAUSE_FALLBACK_ABORT;
      وإلا إذا (strcmp (p, "default_mem") == 0)
	kind = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      وإلا إذا (strcmp (p, "null") == 0)
	kind = OMP_CLAUSE_FALLBACK_NULL;
      وإلا
	{
	  c_parser_error (parser, "expected %<abort%>, %<default_mem%>, or "
				  "%<null%> as fallback mode");
	  أرجع list;
	}
      c_parser_consume_token (parser);
      إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	أرجع list;
      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	أرجع list;
    }
  location_t فرچ_loc = c_parser_peek_token (parser)->location;
  c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
  فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
  بشيا size = c_fully_fold (فرچ.درج, خطأ, عدم);
  parens.skip_until_found_close (parser);

  إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (size)))
    {
      error_at (فرچ_loc, "expected integer expression");
      أرجع list;
    }

  /* Attempt to statically determine when the number is negative.  */
  بشيا c = fold_build2_loc (فرچ_loc, LT_فرچ, boolean_type_كلي, size,
			    build_int_cst (بشيا_TYPE (size), 0));
  protected_set_فرچ_location (c, فرچ_loc);
  إذا (c == boolean_true_كلي)
    {
      warning_at (فرچ_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      size = integer_zero_كلي;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_KIND (c) = kind;
  OMP_CLAUSE_DYN_GROUPPRIVATE_فرچ (c) = size;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  أرجع list;
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

ساكن بشيا
c_parser_omp_clause_map (c_parser *parser, بشيا list, منطقي declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  بشيا nl, c;
  تعداد gomp_map_kind kind = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  صحيح pos = 1;
  صحيح map_kind_pos = 0;
  صحيح iterator_length = 0;
  لكل (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      إذا (tok->type != CPP_NAME)
	اكسر;

      ثابت حرف *p = IDENTIFIER_POINTER (tok->درج);
      c_token *next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      إذا (strcmp (p, "iterator") == 0 && next_tok->type == CPP_OPEN_PAREN)
	{
	  unsigned n = pos + 2;
	  إذا (c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_length = n - pos + 1;
	      pos = n;
	      next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      إذا (next_tok->type == CPP_COLON)
	{
	  map_kind_pos = pos;
	  اكسر;
	}

      إذا (next_tok->type == CPP_COMMA)
	pos++;
      وإلا إذا (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  unsigned صحيح npos = pos + 2;
	  إذا (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, npos + 1)->type
		  == CPP_COMMA))
	    pos = npos + 1;
	}

      pos++;
    }

  صحيح always_modifier = 0;
  صحيح close_modifier = 0;
  صحيح present_modifier = 0;
  صحيح mapper_modifier = 0;
  صحيح لمب_commas = 0;
  صحيح لمب_identifiers = 0;
  بشيا mapper_name = NULL_بشيا;
  بشيا iterators = NULL_بشيا;
  لكل (صحيح pos = 1; pos < map_kind_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      إذا (tok->type == CPP_COMMA)
	{
	  ++لمب_commas;
	  إذا (لمب_commas > لمب_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  استمر;
	}

      ثابت حرف *p = IDENTIFIER_POINTER (tok->درج);
      إذا (strcmp ("always", p) == 0)
	{
	  إذا (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_found_close (parser);
	      أرجع list;
	    }
	  always_modifier++;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (strcmp ("close", p) == 0)
	{
	  إذا (close_modifier)
	    {
	      c_parser_error (parser, "too many %<close%> modifiers");
	      parens.skip_until_found_close (parser);
	      أرجع list;
	    }
	  close_modifier++;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (strcmp ("iterator", p) == 0)
	{
	  إذا (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      أرجع list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      وإلا إذا (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  إذا (mparens.require_open (parser))
	    {
	      إذا (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  أرجع list;
		}

	      tok = c_parser_peek_token (parser);

	      بدل (tok->type)
		{
		حالة CPP_NAME:
		  {
		    mapper_name = tok->درج;
		    c_parser_consume_token (parser);
		    إذا (declare_mapper_p)
		      {
			error_at (tok->location,
				  "in %<declare mapper%> directives, parameter "
				  "to %<mapper%> modifier must be %<default%>");
		      }
		  }
		  اكسر;

		حالة CPP_KEYWORD:
		  إذا (tok->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      اكسر;
		    }
		  /* Fallthrough.  */

		افتراضي:
		  error_at (tok->location,
			    "expected identifier or %<default%>");
		  أرجع list;
		}

	      إذا (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  أرجع list;
		}

	      mapper_modifier++;
	      pos += 3;
	    }
	}
      وإلا إذا (strcmp ("present", p) == 0)
	{
	  إذا (present_modifier)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      أرجع list;
	    }
	  present_modifier++;
	  c_parser_consume_token (parser);
	}
      وإلا
	{
	  c_parser_error (parser, "%<map%> clause with map-type modifier other "
				  "than %<always%>, %<close%>, %<iterator%>, "
				  "%<mapper%> or %<present%>");
	  parens.skip_until_found_close (parser);
	  أرجع list;
	}
      ++لمب_identifiers;
      إذا (لمب_identifiers - 1 > لمب_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_سك_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      لمب_commas = لمب_identifiers - 1;
    }

  إذا (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      صحيح always_present_modifier = always_modifier && present_modifier;

      إذا (strcmp ("alloc", p) == 0)
	kind = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      وإلا إذا (strcmp ("to", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TO
		: present_modifier ? GOMP_MAP_PRESENT_TO
		: always_modifier ? GOMP_MAP_ALWAYS_TO
		: GOMP_MAP_TO);
      وإلا إذا (strcmp ("from", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      وإلا إذا (strcmp ("tofrom", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      وإلا إذا (strcmp ("release", p) == 0)
	kind = GOMP_MAP_RELEASE;
      وإلا إذا (strcmp ("delete", p) == 0)
	kind = GOMP_MAP_DELETE;
      وإلا
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   true);

  بشيا last_new = NULL_بشيا;

  إذا (iterators)
    {
      بشيا block = چرو_scope ();
      إذا (iterators == error_mark_كلي)
	iterators = NULL_بشيا;
      وإلا
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      last_new = c;
    }

  إذا (mapper_name)
    {
      بشيا name = build_omp_clause (شغرو_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_تور_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (شغرو_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_چرو_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_كلي;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  parens.skip_until_found_close (parser);
  أرجع nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

ساكن بشيا
c_parser_omp_clause_device (c_parser *parser, بشيا list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t فرچ_loc;
  c_فرچ فرچ;
  بشيا c, t;
  منطقي ancestor = خطأ;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      ثابت حرف *p = IDENTIFIER_POINTER (tok->درج);
      إذا (strcmp ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  إذا ((omp_requires_mask & OMP_REQUIRES_REVERSE_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_found_close (parser);
	      أرجع list;
	    }
	  ancestor = true;
	}
      وإلا إذا (strcmp ("device_num", p) == 0)
	;
      وإلا
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_found_close (parser);
	  أرجع list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  فرچ_loc = c_parser_peek_token (parser)->location;
  فرچ = c_parser_فرچ_no_commas (parser, عدم);
  فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
  t = فرچ.درج;
  t = c_fully_fold (t, خطأ, عدم);

  parens.skip_until_found_close (parser);

  إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      أرجع list;
    }
  إذا (ancestor && بشيا_CODE (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (فرچ_loc, "the %<device%> clause expression must evaluate to "
			  "%<1%>");
      أرجع list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE, "device");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE);

  OMP_CLAUSE_DEVICE_ID (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEVICE_ANCESTOR (c) = ancestor;

  list = c;
  أرجع list;
}

/* OpenMP 4.0:
   dist_schedule ( static )
   dist_schedule ( static , expression ) */

ساكن بشيا
c_parser_omp_clause_dist_schedule (c_parser *parser, بشيا list)
{
  بشيا c, t = NULL_بشيا;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (!c_parser_next_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      أرجع list;
    }

  c_parser_consume_token (parser);
  إذا (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t فرچ_loc = c_parser_peek_token (parser)->location;
      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
      t = فرچ.درج;
      t = c_fully_fold (t, خطأ, عدم);
      parens.skip_until_found_close (parser);
    }
  وإلا
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  إذا (omp_find_clause (list, OMP_CLAUSE_DIST_SCHEDULE))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  إذا (t == error_mark_كلي)
    أرجع list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_SCHEDULE);
  OMP_CLAUSE_DIST_SCHEDULE_CHUNK_فرچ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

ساكن بشيا
c_parser_omp_clause_proc_bind (c_parser *parser, بشيا list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  تعداد omp_clause_proc_bind_kind kind;
  بشيا c;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp ("primary", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_PRIMARY;
      وإلا إذا (strcmp ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  kind = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      وإلا إذا (strcmp ("close", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_CLOSE;
      وإلا إذا (strcmp ("spread", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_SPREAD;
      وإلا
	اذهب invalid_kind;
    }
  وإلا
    اذهب invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 invalid_kind:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_found_close (parser);
  أرجع list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

ساكن بشيا
c_parser_omp_clause_device_type (c_parser *parser, بشيا list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  تعداد omp_clause_device_type_kind kind;
  بشيا c;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp ("host", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_HOST;
      وإلا إذا (strcmp ("nohost", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      وإلا إذا (strcmp ("any", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_ANY;
      وإلا
	اذهب invalid_kind;
    }
  وإلا
    اذهب invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 invalid_kind:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_found_close (parser);
  أرجع list;
}

/* OpenMP 4.0:
   from ( variable-list )
   to ( variable-list )

   OpenMP 5.1:
   from ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )
   to ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )

   motion-modifier:
     present | iterator (iterators-definition) | mapper (id)  */

ساكن بشيا
c_parser_omp_clause_from_to (c_parser *parser, تعداد omp_clause_code kind,
			     بشيا list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  صحيح pos = 1, colon_pos = 0;
  صحيح iterator_length = 0;

  طالما (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      ثابت حرف *identifier =
	IDENTIFIER_POINTER (c_parser_peek_nth_token_raw (parser, pos)->درج);
      إذا (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  unsigned صحيح npos = pos + 2;
	  إذا (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      إذا (strcmp (identifier, "iterator") == 0)
		iterator_length = npos - pos + 1;
	      pos = npos;
	    }
	}
      إذا (c_parser_peek_nth_token_raw (parser, pos + 1)->type == CPP_COMMA)
	pos += 2;
      وإلا
	pos++;
      إذا (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_COLON)
	{
	  colon_pos = pos;
	  اكسر;
	}
    }

  منطقي present = خطأ, mapper_modifier = خطأ;
  بشيا iterators = NULL_بشيا;
  بشيا mapper_name = NULL_بشيا;

  لكل (صحيح pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  استمر;
	}
      ثابت حرف *p = IDENTIFIER_POINTER (token->درج);
      إذا (strcmp ("present", p) == 0)
	{
	  إذا (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      أرجع list;
	    }
	  present = true;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (strcmp ("iterator", p) == 0)
	{
	  إذا (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      أرجع list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      وإلا إذا (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  إذا (mparens.require_open (parser))
	    {
	      إذا (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  أرجع list;
		}

	      token = c_parser_peek_token (parser);
	      بدل (token->type)
		{
		حالة CPP_NAME:
		  {
		    mapper_name = token->درج;
		    c_parser_consume_token (parser);
		  }
		  اكسر;
		حالة CPP_KEYWORD:
		  إذا (token->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      اكسر;
		    }
		  /* FALLTHROUGH  */
		افتراضي:
		  error_at (token->location,
			    "expected identifier or %<default%>");
		  أرجع list;
		}
	      إذا (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  أرجع list;
		}
	      mapper_modifier = true;
	      pos += 3;
	    }
	}
      وإلا
	{
	  error_at (token->location,
		    "%qs clause with modifier other than %<iterator%>, "
		    "%<mapper%>, or %<present%>",
		    kind == OMP_CLAUSE_TO ? "to" : "from");
	  parens.skip_until_found_close (parser);
	  أرجع list;
	}
    }

  إذا (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  بشيا nl = c_parser_omp_variable_list (parser, loc, kind, list);
  parens.skip_until_found_close (parser);

  إذا (present)
    لكل (بشيا c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  إذا (iterators)
    {
      بشيا block = چرو_scope ();
      إذا (iterators == error_mark_كلي)
	iterators = NULL_بشيا;
      وإلا
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  إذا (iterators)
    لكل (بشيا c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  إذا (mapper_name)
    {
      بشيا last_new = NULL_بشيا;
      لكل (بشيا c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	last_new = c;

      بشيا name = build_omp_clause (شغرو_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_تور_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (شغرو_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_چرو_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_كلي;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  أرجع nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

ساكن بشيا
c_parser_omp_clause_uniform (c_parser *parser, بشيا list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_UNIFORM,
					 list);
      parens.skip_until_found_close (parser);
    }
  أرجع list;
}

/* OpenMP 5.1
   full */

ساكن بشيا
c_parser_omp_clause_full (c_parser *parser, بشيا list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_FULL, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  بشيا c = build_omp_clause (loc, OMP_CLAUSE_FULL);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

ساكن بشيا
c_parser_omp_clause_partial (c_parser *parser, بشيا list)
{
  بشيا لمب = NULL_بشيا;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      لمب = c_parser_فرچ_no_commas (parser, عدم).درج;
      parens.skip_until_found_close (parser);

      إذا (لمب == error_mark_كلي)
	أرجع list;

      mark_exp_read (لمب);
      لمب = c_fully_fold (لمب, خطأ, عدم);
      HOST_WIDE_INT n;
      إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (لمب))
	  || !بشيا_fits_shwi_p (لمب)
	  || (n = بشيا_to_shwi (لمب)) <= 0
	  || (صحيح) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  أرجع list;
	}
    }

  بشيا c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_فرچ (c) = لمب;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

ساكن بشيا
c_parser_omp_clause_novariants (c_parser *parser, بشيا list)
{
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
  بشيا t = convert_lvalue_to_rvalue (loc, فرچ, true, true).درج;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, خطأ, عدم);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  بشيا c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_فرچ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  أرجع list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

ساكن بشيا
c_parser_omp_clause_nocontext (c_parser *parser, بشيا list)
{
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
  بشيا t = convert_lvalue_to_rvalue (loc, فرچ, true, true).درج;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, خطأ, عدم);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  بشيا c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_فرچ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  أرجع list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

ساكن بشيا
c_parser_omp_clause_detach (c_parser *parser, بشيا list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_found_close (parser);
      أرجع list;
    }

  بشيا t = lookup_name (c_parser_peek_token (parser)->درج);
  إذا (t == NULL_بشيا)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->درج);
      parens.skip_until_found_close (parser);
      أرجع list;
    }
  c_parser_consume_token (parser);

  بشيا type = TYPE_MAIN_VARIANT (بشيا_TYPE (t));
  إذا (!INTEGRAL_TYPE_P (type)
      || بشيا_CODE (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_found_close (parser);
      أرجع list;
    }

  بشيا u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_found_close (parser);
  أرجع u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

ساكن بشيا
c_parser_omp_clause_destroy (c_parser *parser, بشيا list)
{
  بشيا nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  لكل (بشيا c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    بشيا_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
  أرجع nl;
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

ساكن بشيا
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع error_mark_كلي;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  إذا (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    طالما (true)
      {
	str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
	إذا (c_parser_next_token_is (parser, CPP_STRING))
	  {
	    c_فرچ cval = c_parser_string_literal (parser, خطأ, خطأ);
	    إذا (cval.درج == error_mark_كلي)
	      أرجع error_mark_كلي;
	    إذا ((size_t) بشيا_STRING_LENGTH (cval.درج)
		!= strlen (بشيا_STRING_POINTER (cval.درج)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = true;
		أرجع error_mark_كلي;
	      }

	    حرف c = omp_get_fr_id_from_name (بشيا_STRING_POINTER (cval.درج));
	    إذا (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  بشيا_STRING_POINTER (cval.درج));
	    str += c;
	  }
	وإلا
	  {
	    c_فرچ cval = c_parser_فرچ_no_commas (parser, عدم);
	    بشيا درج = c_fully_fold (cval.درج, خطأ, عدم);
	    إذا (INTEGRAL_TYPE_P (بشيا_TYPE (درج))
		&& بشيا_CODE (درج) != INTEGER_CST)
	      درج = convert_lvalue_to_rvalue (cval.get_start (), cval,
						خطأ, true).درج;
	    إذا (بشيا_CODE (درج) != INTEGER_CST
		|| !بشيا_fits_shwi_p (درج))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		أرجع error_mark_كلي;
	      }
	    HOST_WIDE_INT n = بشيا_to_shwi (درج);
	    إذا (n < 1 || n > GOMP_INTEROP_IFR_LAST)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (حرف) n;
	  }
	str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	إذا (c_parser_next_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    استمر;
	  }
	إذا (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  أرجع error_mark_كلي;
	str += '\0';
	بشيا res = build_string (str.length (), str.data ());
	بشيا_TYPE (res) = build_array_type_nelts (unsigned_char_type_كلي,
						  str.length ());
	أرجع res;
      }

  /* New format. */
  std::string str2;
  طالما (true)
    {
      إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	أرجع error_mark_كلي;
      str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
      str2.clear ();
      منطقي has_fr = خطأ;
      طالما (true)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  إذا (tok->type != CPP_NAME
	      || (strcmp("fr", IDENTIFIER_POINTER (tok->درج)) != 0
		  && strcmp("attr", IDENTIFIER_POINTER (tok->درج)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      أرجع error_mark_كلي;
	    }
	  c_parser_consume_token (parser);
	  منطقي is_fr = IDENTIFIER_POINTER (tok->درج)[0] == 'f';
	  إذا (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      أرجع error_mark_كلي;
	    }
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع error_mark_كلي;
	  طالما (true)
	    {
	      إذا (c_parser_next_token_is (parser, CPP_STRING))
		{
		  c_فرچ cval = c_parser_string_literal (parser, خطأ, خطأ);
		  بشيا درج = cval.درج;
		  إذا (درج == error_mark_كلي)
		    أرجع error_mark_كلي;
		  إذا ((size_t) بشيا_STRING_LENGTH (درج)
		      != strlen (بشيا_STRING_POINTER (درج)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = true;
		      أرجع error_mark_كلي;
		    }
		  إذا (!is_fr)
		    {
		      إذا (!startswith (بشيا_STRING_POINTER (درج), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = true;
			  أرجع error_mark_كلي;
			}
		      إذا (strchr (بشيا_STRING_POINTER (درج), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = true;
			  أرجع error_mark_كلي;
			}
		      str2 += بشيا_STRING_POINTER (درج);
		      str2 += '\0';
		    }
		  وإلا
		    {
		      إذا (*بشيا_STRING_POINTER (درج) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  أرجع error_mark_كلي;
			}
		      حرف c = omp_get_fr_id_from_name (بشيا_STRING_POINTER (درج));
		      إذا (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    بشيا_STRING_POINTER (درج));
		     str += c;
		     has_fr = true;
		    }
		}
	      وإلا إذا (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  أرجع error_mark_كلي;
		}
	      وإلا
		{
		  c_فرچ cval = c_parser_فرچ_no_commas (parser, عدم);
		  بشيا درج = c_fully_fold (cval.درج, خطأ, عدم);
		  إذا (INTEGRAL_TYPE_P (بشيا_TYPE (درج))
		      && بشيا_CODE (درج) != INTEGER_CST)
		    درج = convert_lvalue_to_rvalue (cval.get_start (), cval,
						      خطأ, true).درج;

		  إذا (بشيا_CODE (درج) != INTEGER_CST
		      || !بشيا_fits_shwi_p (درج))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      أرجع error_mark_كلي;
		    }
		  HOST_WIDE_INT n = بشيا_to_shwi (درج);
		  إذا (n < 1 || n > GOMP_INTEROP_IFR_LAST)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (حرف) n;
		  has_fr = true;
		}
	      إذا (!is_fr
		  && c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  استمر;
		}
	      إذا (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		أرجع error_mark_كلي;
	      اكسر;
	    }
	  إذا (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      استمر;
	    }
	  إذا (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    اكسر;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  أرجع error_mark_كلي;
	}
      str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	اكسر;
      إذا (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	أرجع error_mark_كلي;
    }
  c_parser_consume_token (parser);
  str += '\0';
  بشيا res = build_string (str.length (), str.data ());
  بشيا_TYPE (res) = build_array_type_nelts (unsigned_char_type_كلي,
						  str.length ());
  أرجع res;
}

/* OpenMP 5.1
     modifiers of the 'init' clause, used by the 'init' and the
     'append_args' clauses.

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification)

  Returns 'false' if an error has been issued.  */

ساكن منطقي
c_parser_omp_clause_init_modifiers (c_parser *parser, منطقي *target,
				    منطقي *targetsync, بشيا *prefer_type_بشيا)
{
  *target = خطأ;
  *targetsync = خطأ;
  *prefer_type_بشيا = NULL_بشيا;

  افعل
    {
      c_token *tok = c_parser_peek_token (parser);
      إذا (tok->type != CPP_NAME)
	اذهب fail;
      ثابت حرف *p = IDENTIFIER_POINTER (tok->درج);
      إذا (strcmp ("targetsync", p) == 0)
	{
	  إذا (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = true;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (strcmp ("target", p) == 0)
	{
	  إذا (*target)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *target = true;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (strcmp ("prefer_type", p) == 0)
	{
	  إذا (*prefer_type_بشيا != NULL_بشيا)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_بشيا = c_parser_omp_modifier_prefer_type (parser);
	  إذا (*prefer_type_بشيا == error_mark_كلي)
	    أرجع خطأ;
	}
      وإلا
	اذهب fail;
      tok = c_parser_peek_token (parser);
      إذا (tok->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  استمر;
	}
      /* Unknown token - either done or an error; handle it in the caller.  */
      أرجع true;
    }
  طالما (true);

fail:
  c_parser_error (parser,
		  "expected %<prefer_type%>, %<target%>, or %<targetsync%>");
  أرجع خطأ;
}

/* OpenMP 5.1:
   init ( [init-modifier-list : ] variable-list )

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification) */

ساكن بشيا
c_parser_omp_clause_init (c_parser *parser, بشيا list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  منطقي target = خطأ;
  منطقي targetsync = خطأ;
  بشيا prefer_type_بشيا = NULL_بشيا;

  إذا (!c_parser_omp_clause_init_modifiers (parser, &target, &targetsync,
					   &prefer_type_بشيا)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      إذا (prefer_type_بشيا != error_mark_كلي)
	parens.skip_until_found_close (parser);
      أرجع list;
    }

  إذا (!target && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  بشيا nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					خطأ);
  parens.skip_until_found_close (parser);

  لكل (بشيا c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      بشيا_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      إذا (target)
	OMP_CLAUSE_INIT_TARGET (c) = 1;
      إذا (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      إذا (prefer_type_بشيا)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_بشيا;
    }
  أرجع nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

ساكن بشيا
c_parser_omp_clause_use (c_parser *parser, بشيا list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

ساكن بشيا
c_parser_omp_clause_interop (c_parser *parser, بشيا list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  بشيا nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  لكل (بشيا c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      بشيا_USED (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  أرجع nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

ساكن بشيا
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_mask mask,
			   ثابت حرف *where, منطقي finish_p = true,
			   منطقي target_p = خطأ)
{
  بشيا clauses = عدم;
  منطقي first = true;

  طالما (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      ثابت حرف *c_name;
      بشيا prev = clauses;

      إذا (!first && c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      بدل (c_kind)
	{
	حالة PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "attach";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copy";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyin";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyout";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "create";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "delete";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, true);
	  c_name = "default";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "detach";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_data_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device_resident";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_GANG,
						c_name, clauses);
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "host";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, خطأ);
	  c_name = "if";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "link";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "no_create";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_لمب_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_لمب_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_لمب_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_لمب_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "present";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     خطأ, clauses);
	  c_name = "reduction";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_SELF:
	  إذا ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  وإلا
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "self";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_SEQ,
						 clauses);
	  c_name = "seq";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_TILE:
	  clauses = c_parser_oacc_clause_tile (parser, clauses);
	  c_name = "tile";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_USE_DEVICE:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_VECTOR:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_VECTOR,
						c_name,	clauses);
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_VECTOR_LENGTH:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_VECTOR_LENGTH,
						     clauses);
	  c_name = "vector_length";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_WORKER:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_WORKER,
						c_name, clauses);
	  اكسر;
	افتراضي:
	  c_parser_error (parser, "expected an OpenACC clause");
	  اذهب saw_error;
	}

      first = خطأ;

      إذا (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_to_pragma_eol (parser);

  إذا (finish_p)
    أرجع c_finish_omp_clauses (clauses, target_p ? C_ORT_ACC_TARGET
						   : C_ORT_ACC);

  أرجع clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

ساكن بشيا
c_parser_omp_all_clauses (c_parser *parser, omp_clause_mask mask,
			  ثابت حرف *where, منطقي finish_p = true,
			  صحيح nested = 0)
{
  بشيا clauses = عدم;
  منطقي first = true;

  طالما (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      ثابت حرف *c_name;
      بشيا prev = clauses;

      إذا (nested && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	اكسر;

      إذا (!first || nested != 2)
	{
	  إذا (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا إذا (nested == 2)
	    error_at (c_parser_peek_token (parser)->location,
		      "clauses in %<simd%> trait should be separated "
		      "by %<,%>");
	}

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      بدل (c_kind)
	{
	حالة PRAGMA_OMP_CLAUSE_BIND:
	  clauses = c_parser_omp_clause_bind (parser, clauses);
	  c_name = "bind";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, خطأ);
	  c_name = "default";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DETACH:
	  clauses = c_parser_omp_clause_detach (parser, clauses);
	  c_name = "detach";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_FILTER:
	  clauses = c_parser_omp_clause_filter (parser, clauses);
	  c_name = "filter";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_FINAL:
	  clauses = c_parser_omp_clause_final (parser, clauses);
	  c_name = "final";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_GRAINSIZE:
	  clauses = c_parser_omp_clause_grainsize (parser, clauses);
	  c_name = "grainsize";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_HINT:
	  clauses = c_parser_omp_clause_hint (parser, clauses);
	  c_name = "hint";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DEFAULTMAP:
	  clauses = c_parser_omp_clause_defaultmap (parser, clauses);
	  c_name = "defaultmap";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, true);
	  c_name = "if";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_IN_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_IN_REDUCTION,
					     true, clauses);
	  c_name = "in_reduction";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_INDIRECT:
	  clauses = c_parser_omp_clause_indirect (parser, clauses);
	  c_name = "indirect";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_MERGEABLE:
	  clauses = c_parser_omp_clause_mergeable (parser, clauses);
	  c_name = "mergeable";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_لمب_TASKS:
	  clauses = c_parser_omp_clause_لمب_tasks (parser, clauses);
	  c_name = "num_tasks";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_لمب_THREADS:
	  clauses = c_parser_omp_clause_لمب_threads (parser, clauses);
	  c_name = "num_threads";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_ORDER:
	  clauses = c_parser_omp_clause_order (parser, clauses);
	  c_name = "order";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_PRIORITY:
	  clauses = c_parser_omp_clause_priority (parser, clauses);
	  c_name = "priority";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     true, clauses);
	  c_name = "reduction";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_SCHEDULE:
	  clauses = c_parser_omp_clause_schedule (parser, clauses);
	  c_name = "schedule";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     true, clauses);
	  c_name = "task_reduction";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_UNTIED:
	  clauses = c_parser_omp_clause_untied (parser, clauses);
	  c_name = "untied";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_INBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_INBRANCH,
						clauses);
	  c_name = "inbranch";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_NONTEMPORAL:
	  clauses = c_parser_omp_clause_nontemporal (parser, clauses);
	  c_name = "nontemporal";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_NOTINBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_NOTINBRANCH,
						clauses);
	  c_name = "notinbranch";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_PARALLEL:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_PARALLEL,
					      clauses);
	  c_name = "parallel";
	  إذا (!first)
	    {
	     clause_not_first:
	      error_at (here, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = prev;
	    }
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  إذا (!first)
	    اذهب clause_not_first;
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  إذا (!first)
	    اذهب clause_not_first;
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  إذا (!first)
	    اذهب clause_not_first;
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_LINK:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LINK, clauses);
	  c_name = "link";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_LOCAL:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LOCAL, clauses);
	  c_name = "local";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_TO:
	  إذا ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (here);
	      richloc.add_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      بشيا nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      لكل (بشيا c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_TO (c) = 1;
	      clauses = nl;
	    }
	  وإلا
	    clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_TO,
						   clauses);
	  c_name = "to";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_UNIFORM:
	  clauses = c_parser_omp_clause_uniform (parser, clauses);
	  c_name = "uniform";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_لمب_TEAMS:
	  clauses = c_parser_omp_clause_لمب_teams (parser, clauses);
	  c_name = "num_teams";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_THREAD_LIMIT:
	  clauses = c_parser_omp_clause_thread_limit (parser, clauses);
	  c_name = "thread_limit";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_ALIGNED:
	  clauses = c_parser_omp_clause_aligned (parser, clauses);
	  c_name = "aligned";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_ALLOCATE:
	  clauses = c_parser_omp_clause_allocate (parser, clauses);
	  c_name = "allocate";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_LINEAR:
	  clauses = c_parser_omp_clause_linear (parser, clauses);
	  c_name = "linear";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_USES_ALLOCATORS:
	  clauses = c_parser_omp_clause_uses_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, here);
	  c_name = "depend";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DOACROSS:
	  clauses = c_parser_omp_clause_doacross (parser, clauses);
	  c_name = "doacross";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DESTROY:
	  clauses = c_parser_omp_clause_destroy (parser, clauses);
	  c_name = "destroy";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE:
	  clauses = c_parser_omp_clause_dyn_groupprivate (parser, clauses);
	  c_name = "dyn_groupprivate";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_INIT:
	  clauses = c_parser_omp_clause_init (parser, clauses);
	  c_name = "init";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_USE:
	  clauses = c_parser_omp_clause_use (parser, clauses);
	  c_name = "use";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_INTEROP:
	  clauses = c_parser_omp_clause_interop (parser, clauses);
	  c_name = "interop";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_MAP:
	  clauses = c_parser_omp_clause_map (parser, clauses, خطأ);
	  c_name = "map";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device_ptr";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_use_device_addr (parser, clauses);
	  c_name = "use_device_addr";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_has_device_addr (parser, clauses);
	  c_name = "has_device_addr";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR:
	  clauses = c_parser_omp_clause_is_device_ptr (parser, clauses);
	  c_name = "is_device_ptr";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DEVICE:
	  clauses = c_parser_omp_clause_device (parser, clauses);
	  c_name = "device";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DIST_SCHEDULE:
	  clauses = c_parser_omp_clause_dist_schedule (parser, clauses);
	  c_name = "dist_schedule";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_PROC_BIND:
	  clauses = c_parser_omp_clause_proc_bind (parser, clauses);
	  c_name = "proc_bind";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DEVICE_TYPE:
	  clauses = c_parser_omp_clause_device_type (parser, clauses);
	  c_name = "device_type";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_SAFELEN:
	  clauses = c_parser_omp_clause_safelen (parser, clauses);
	  c_name = "safelen";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_SIMDLEN:
	  clauses = c_parser_omp_clause_simdlen (parser, clauses);
	  c_name = "simdlen";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_NOGROUP:
	  clauses = c_parser_omp_clause_nogroup (parser, clauses);
	  c_name = "nogroup";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_THREADS:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_THREADS,
					       clauses);
	  c_name = "threads";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_SIMD:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_SIMD,
					       clauses);
	  c_name = "simd";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_ENTER:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					    clauses);
	  c_name = "enter";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_FULL:
	  c_name = "full";
	  clauses = c_parser_omp_clause_full (parser, clauses);
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_PARTIAL:
	  c_name = "partial";
	  clauses = c_parser_omp_clause_partial (parser, clauses);
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_NOVARIANTS:
	  c_name = "novariants";
	  clauses = c_parser_omp_clause_novariants (parser, clauses);
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_NOCONTEXT:
	  c_name = "nocontext";
	  clauses = c_parser_omp_clause_nocontext (parser, clauses);
	  اكسر;
	افتراضي:
	  c_parser_error (parser, "expected an OpenMP clause");
	  اذهب saw_error;
	}

      first = خطأ;

      إذا (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  إذا (!nested)
    c_parser_skip_to_pragma_eol (parser);

  إذا (finish_p)
    {
      إذا ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_UNIFORM)) != 0)
	أرجع c_finish_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      إذا ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	أرجع c_finish_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      أرجع c_finish_omp_clauses (clauses, C_ORT_OMP);
    }

  أرجع clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

ساكن بشيا
c_parser_omp_structured_block (c_parser *parser, منطقي *if_p)
{
  بشيا stmt = تور_stmt_list ();
  parser->omp_attrs_forbidden_p = true;
  c_parser_statement (parser, if_p);
  أرجع چرو_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

ساكن بشيا
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  بشيا stmt, clauses = NULL_بشيا;
  منطقي readonly = خطأ;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_NAME
	  && !strcmp (IDENTIFIER_POINTER (token->درج), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = true;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_بشيا);
      parens.skip_until_found_close (parser);
    }

  إذا (readonly)
    لكل (بشيا c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_to_pragma_eol (parser);

  stmt = make_كلي (OACC_CACHE);
  بشيا_TYPE (stmt) = void_type_كلي;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  SET_فرچ_LOCATION (stmt, loc);
  add_stmt (stmt);

  أرجع stmt;
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

ساكن بشيا
c_parser_oacc_data (location_t loc, c_parser *parser, منطقي *if_p)
{
  بشيا stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_DATA_CLAUSE_MASK,
				       "#pragma acc data");

  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  stmt = c_finish_oacc_data (loc, clauses, block);

  أرجع stmt;
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

ساكن فراغ
c_parser_oacc_declare (c_parser *parser)
{
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  بشيا clauses, stmt, t, decl;

  منطقي error = خطأ;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_MASK,
				       "#pragma acc declare");
  إذا (!clauses)
    {
      error_at (pragma_loc,
		"no valid clauses specified in %<#pragma acc declare%>");
      أرجع;
    }

  لكل (t = clauses; t; t = OMP_CLAUSE_CHAIN (t))
    {
      location_t loc = OMP_CLAUSE_LOCATION (t);
      decl = OMP_CLAUSE_DECL (t);
      إذا (!DECL_P (decl))
	{
	  error_at (loc, "array section in %<#pragma acc declare%>");
	  error = true;
	  استمر;
	}

      بدل (OMP_CLAUSE_MAP_KIND (t))
	{
	حالة GOMP_MAP_FIRSTPRIVATE_POINTER:
	حالة GOMP_MAP_ALLOC:
	حالة GOMP_MAP_TO:
	حالة GOMP_MAP_FORCE_DEVICEPTR:
	حالة GOMP_MAP_DEVICE_RESIDENT:
	  اكسر;

	حالة GOMP_MAP_LINK:
	  إذا (!global_bindings_p ()
	      && (بشيا_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = true;
	      استمر;
	    }
	  اكسر;

	افتراضي:
	  إذا (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = true;
	      استمر;
	    }
	  إذا (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = true;
	      استمر;
	    }
	  وإلا إذا (بشيا_PUBLIC (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = true;
	      استمر;
	    }
	  اكسر;
	}

      إذا (!c_check_in_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = true;
	  استمر;
	}

      إذا (lookup_attribute ("omp declare target", DECL_ATTRIBUTES (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_ATTRIBUTES (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = true;
	  استمر;
	}

      إذا (!error)
	{
	  بشيا id;

	  إذا (OMP_CLAUSE_MAP_KIND (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  وإلا
	    id = get_identifier ("omp declare target");

	  DECL_ATTRIBUTES (decl)
			   = بشيا_cons (id, NULL_بشيا, DECL_ATTRIBUTES (decl));

	  إذا (global_bindings_p ())
	    {
	      symtab_كلي *كلي = symtab_كلي::get (decl);
	      إذا (كلي != عدم)
		{
		  كلي->offloadable = 1;
		  إذا (ENABLE_OFFLOADING)
		    {
		      g->have_offload = true;
		      إذا (is_a <varpool_كلي *> (كلي))
			vec_safe_تور (offload_vars, decl);
		    }
		}
	    }
	}
    }

  إذا (error || global_bindings_p ())
    أرجع;

  stmt = make_كلي (OACC_DECLARE);
  بشيا_TYPE (stmt) = void_type_كلي;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  SET_فرچ_LOCATION (stmt, pragma_loc);

  add_stmt (stmt);

  أرجع;
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

ساكن فراغ
c_parser_oacc_enter_exit_data (c_parser *parser, منطقي enter)
{
  location_t loc = c_parser_peek_token (parser)->location;
  بشيا clauses, stmt;
  ثابت حرف *p = "";

  c_parser_consume_pragma (parser);

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      c_parser_consume_token (parser);
    }

  إذا (strcmp (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = true;
      c_parser_skip_to_pragma_eol (parser);
      أرجع;
    }

  إذا (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_DATA_CLAUSE_MASK,
					 "#pragma acc enter data");
  وإلا
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_DATA_CLAUSE_MASK,
					 "#pragma acc exit data");

  إذا (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_بشيا)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      أرجع;
    }

  stmt = enter ? make_كلي (OACC_ENTER_DATA) : make_كلي (OACC_EXIT_DATA);
  بشيا_TYPE (stmt) = void_type_كلي;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  SET_فرچ_LOCATION (stmt, loc);
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

ساكن بشيا
c_parser_oacc_host_data (location_t loc, c_parser *parser, منطقي *if_p)
{
  بشيا stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_DATA_CLAUSE_MASK,
				       "#pragma acc host_data", خطأ);
  إذا (!omp_find_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      أرجع error_mark_كلي;
    }
  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  stmt = c_finish_oacc_host_data (loc, clauses, block);
  أرجع stmt;
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
ساكن بشيا
c_parser_oacc_loop (location_t loc, c_parser *parser, حرف *p_name,
		    omp_clause_mask mask, بشيا *cclauses, منطقي *if_p)
{
  منطقي is_parallel = ((mask >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  strcat (p_name, " loop");
  mask |= OACC_LOOP_CLAUSE_MASK;

  بشيا clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/cclauses == عدم,
					    /*target=*/is_parallel);
  إذا (cclauses)
    {
      clauses = c_oacc_split_loop_clauses (clauses, cclauses, is_parallel);
      إذا (*cclauses)
	*cclauses = c_finish_omp_clauses (*cclauses, C_ORT_ACC_TARGET);
      إذا (clauses)
	clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
    }

  بشيا block = c_begin_compound_stmt (true);
  بشيا stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, عدم,
				     if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  أرجع stmt;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_لمب_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_لمب_WORKERS)		\
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_لمب_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_لمب_WORKERS)		\
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

ساكن بشيا
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       تعداد pragma_kind p_kind, حرف *p_name, منطقي *if_p)
{
  omp_clause_mask mask;
  تعداد بشيا_code code;
  بدل (p_kind)
    {
    حالة PRAGMA_OACC_KERNELS:
      strcat (p_name, " kernels");
      mask = OACC_KERNELS_CLAUSE_MASK;
      code = OACC_KERNELS;
      اكسر;
    حالة PRAGMA_OACC_PARALLEL:
      strcat (p_name, " parallel");
      mask = OACC_PARALLEL_CLAUSE_MASK;
      code = OACC_PARALLEL;
      اكسر;
    حالة PRAGMA_OACC_SERIAL:
      strcat (p_name, " serial");
      mask = OACC_SERIAL_CLAUSE_MASK;
      code = OACC_SERIAL;
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  بشيا block = c_begin_omp_parallel ();
	  بشيا clauses;
	  c_parser_oacc_loop (loc, parser, p_name, mask, &clauses, if_p);
	  أرجع c_finish_omp_construct (loc, code, block, clauses);
	}
    }

  بشيا clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/true,
					    /*target=*/true);

  بشيا block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  أرجع c_finish_omp_construct (loc, code, block, clauses);
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

ساكن فراغ
c_parser_oacc_routine (c_parser *parser, تعداد pragma_context context)
{
  gcc_checking_assert (context == pragma_external);

  oacc_routine_data data;
  data.error_seen = خطأ;
  data.fndecl_seen = خطأ;
  data.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      بشيا decl = NULL_بشيا;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      إذا (name_token->type == CPP_NAME
	  && (name_token->id_kind == C_ID_ID
	      || name_token->id_kind == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->درج);
	  إذا (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->درج);
	  c_parser_consume_token (parser);
	}
      وإلا
	c_parser_error (parser, "expected function name");

      إذا (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_to_pragma_eol (parser, خطأ);
	  أرجع;
	}

      data.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_MASK,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      data.clauses = nreverse (data.clauses);

      إذا (بشيا_CODE (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  أرجع;
	}

      c_finish_oacc_routine (&data, decl, خطأ);
    }
  وإلا /* No optional '( name )'.  */
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
      إذا (c_parser_next_token_is (parser, CPP_PRAGMA)
	  || c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (data.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  أرجع;
	}

      /* We only have to consider the pragma_external case here.  */
      إذا (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحيح ext = disable_extension_diagnostics ();
	  افعل
	    c_parser_consume_token (parser);
	  طالما (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, true, true, true, خطأ, true,
					 خطأ, عدم, عدم, خطأ, عدم, &data);
	  restore_extension_diagnostics (ext);
	}
      وإلا
	c_parser_declaration_or_fndef (parser, true, true, true, خطأ, true,
				       خطأ, عدم, عدم, خطأ, عدم, &data);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

ساكن فراغ
c_finish_oacc_routine (بنية oacc_routine_data *data, بشيا fndecl,
		       منطقي is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  إذا (data->error_seen
      || fndecl == error_mark_كلي)
    أرجع;

  إذا (data->fndecl_seen)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      data->error_seen = true;
      أرجع;
    }
  إذا (fndecl == NULL_بشيا || بشيا_CODE (fndecl) != FUNCTION_DECL)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      data->error_seen = true;
      أرجع;
    }

  صحيح compatible
    = oacc_verify_routine_clauses (fndecl, &data->clauses, data->loc,
				   "#pragma acc routine");
  إذا (compatible < 0)
    {
      data->error_seen = true;
      أرجع;
    }
  إذا (compatible > 0)
    {
    }
  وإلا
    {
      إذا (بشيا_USED (fndecl) || (!is_defn && DECL_SAVED_بشيا (fndecl)))
	{
	  error_at (data->loc,
		    بشيا_USED (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  data->error_seen = true;
	  أرجع;
	}

      /* Set the routine's level of parallelism.  */
      بشيا dims = oacc_build_routine_dims (data->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_ATTRIBUTES (fndecl)
	= بشيا_cons (get_identifier ("omp declare target"),
		     data->clauses, DECL_ATTRIBUTES (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  data->fndecl_seen = true;
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

ساكن فراغ
c_parser_oacc_update (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  بشيا clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_MASK,
					    "#pragma acc update");
  إذا (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_بشيا)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      أرجع;
    }

  إذا (parser->error)
    أرجع;

  بشيا stmt = make_كلي (OACC_UPDATE);
  بشيا_TYPE (stmt) = void_type_كلي;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  SET_فرچ_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#define OACC_WAIT_CLAUSE_MASK						\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF) )

ساكن بشيا
c_parser_oacc_wait (location_t loc, c_parser *parser, حرف *p_name)
{
  بشيا clauses, list = NULL_بشيا, stmt = NULL_بشيا;

  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  strcpy (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_MASK, p_name);
  stmt = c_finish_oacc_wait (loc, list, clauses);
  add_stmt (stmt);

  أرجع stmt;
}

بنية c_omp_loc_بشيا
{
  location_t loc;
  بشيا var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
ساكن بشيا
c_check_omp_allocate_allocator_r (بشيا *tp, صحيح *, فراغ *data)
{
  بشيا var = ((بنية c_omp_loc_بشيا *) data)->var;
  location_t loc = ((بنية c_omp_loc_بشيا *) data)->loc;
  إذا (بشيا_CODE (*tp) == VAR_DECL && c_check_in_current_scope (*tp))
    {
      إذا (linemap_location_before_p (لي_table, DECL_SOURCE_LOCATION (var),
				     DECL_SOURCE_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_SOURCE_LOCATION (*tp), "declared here");
	  inform (DECL_SOURCE_LOCATION (var),
		  "to be allocated variable declared here");
	  أرجع *tp;
	}
      وإلا
	{
	  gcc_assert (cur_stmt_list
		      && بشيا_CODE (cur_stmt_list) == STATEMENT_LIST);

	  بشيا_stmt_iterator l = tsi_last (cur_stmt_list);
	  طالما (!tsi_end_p (l))
	    {
	      إذا (linemap_location_before_p (لي_table, فرچ_LOCATION (*l),
					     DECL_SOURCE_LOCATION (var)))
		  اكسر;
	      إذا (بشيا_CODE (*l) == MODIFY_فرچ
		  && بشيا_OPERAND (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (فرچ_LOCATION (*l), "modified here");
		  inform (DECL_SOURCE_LOCATION (var),
			  "to be allocated variable declared here");
		  أرجع *tp;
		}
	      --l;
	    }
	}
    }
  أرجع NULL_بشيا;
}

/* OpenMP 5.x:
   # pragma omp allocate (list)  clauses

   OpenMP 5.0 clause:
   allocator (omp_allocator_handle_t expression)

   OpenMP 5.1 additional clause:
   align (constant-expression)]  */

ساكن فراغ
c_parser_omp_allocate (c_parser *parser)
{
  بشيا alignment = NULL_بشيا;
  بشيا allocator = NULL_بشيا;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  بشيا nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_بشيا);
  افعل
    {
      إذا (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      إذا (!c_parser_next_token_is (parser, CPP_NAME))
	اكسر;
      matching_parens parens;
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      c_parser_consume_token (parser);
      location_t فرچ_loc = c_parser_peek_token (parser)->location;
      إذا (strcmp ("align", p) != 0 && strcmp ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  اكسر;
	}
      إذا (!parens.require_open (parser))
	اكسر;

      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, خطأ, true);
      فرچ_loc = c_parser_peek_token (parser)->location;
      إذا (فرچ.درج == error_mark_كلي)
	;
      وإلا إذا (p[2] == 'i' && alignment)
	{
	  error_at (فرچ_loc, "too many %qs clauses", "align");
	  اكسر;
	}
      وإلا إذا (p[2] == 'i')
	{
	  alignment = c_fully_fold (فرچ.درج, خطأ, عدم);
	  إذا (بشيا_CODE (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (بشيا_TYPE (alignment))
	      || بشيا_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (فرچ_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_بشيا;
	    }
	}
      وإلا إذا (allocator)
	{
	  error_at (فرچ_loc, "too many %qs clauses", "allocator");
	  اكسر;
	}
      وإلا
	{
	  allocator = c_fully_fold (فرچ.درج, خطأ, عدم);
	  allocator_loc = فرچ_loc;
	  بشيا orig_type
	    = فرچ.original_type ? فرچ.original_type : بشيا_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (allocator))
	      || بشيا_CODE (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (فرچ_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			بشيا_TYPE (allocator));
	      allocator = NULL_بشيا;
	    }
	}
      parens.skip_until_found_close (parser);
    } طالما (true);
  c_parser_skip_to_pragma_eol (parser);

  c_mark_decl_jump_unsafe_in_current_scope ();
  لكل (بشيا c = nl; c != NULL_بشيا; c = OMP_CLAUSE_CHAIN (c))
    {
      بشيا var = OMP_CLAUSE_DECL (c);
      إذا (بشيا_CODE (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  استمر;
	}
      إذا (!parser->in_omp_decl_attribute && !c_check_in_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_SOURCE_LOCATION (var), "declared here");
	  استمر;
	}
      إذا (lookup_attribute ("omp allocate", DECL_ATTRIBUTES (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  استمر;
	}
      إذا (بشيا_STATIC (var))
	{
	  إذا (allocator == NULL_بشيا && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      استمر;
	    }
	  وإلا إذا (allocator
		   && (wi::to_widest (allocator) < 1
		       || wi::to_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::to_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::to_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  وإلا إذا (allocator
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
      إذا (allocator)
	{
	  بنية c_omp_loc_بشيا data
	    = {فرچ_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_بشيا (&allocator, c_check_omp_allocate_allocator_r, &data, عدم);
	}
      DECL_ATTRIBUTES (var) = بشيا_cons (get_identifier ("omp allocate"),
					 build_بشيا_list (allocator, alignment),
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

ساكن فراغ
c_parser_omp_atomic (location_t loc, c_parser *parser, منطقي openacc)
{
  بشيا lhs = NULL_بشيا, rhs = NULL_بشيا, v = NULL_بشيا, r = NULL_بشيا;
  بشيا lhs1 = NULL_بشيا, rhs1 = NULL_بشيا;
  بشيا stmt, orig_lhs, unfolded_lhs = NULL_بشيا, unfolded_lhs1 = NULL_بشيا;
  تعداد بشيا_code code = ERROR_MARK, opcode = NOP_فرچ;
  تعداد omp_memory_order memory_order = OMP_MEMORY_ORDER_UNSPECIFIED;
  بنية c_فرچ فرچ;
  location_t eloc;
  منطقي structured_block = خطأ;
  منطقي swapped = خطأ;
  منطقي non_lvalue_p;
  بشيا clauses = NULL_بشيا;
  منطقي capture = خطأ;
  منطقي compare = خطأ;
  منطقي weak = خطأ;
  تعداد omp_memory_order fail = OMP_MEMORY_ORDER_UNSPECIFIED;
  منطقي no_semicolon = خطأ;
  منطقي extra_scope = خطأ;

  طالما (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      إذا (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ثابت حرف *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  تعداد بشيا_code new_code = ERROR_MARK;
	  تعداد omp_memory_order new_memory_order
	    = OMP_MEMORY_ORDER_UNSPECIFIED;
	  منطقي new_capture = خطأ;
	  منطقي new_compare = خطأ;
	  منطقي new_weak = خطأ;
	  تعداد omp_memory_order new_fail = OMP_MEMORY_ORDER_UNSPECIFIED;

	  إذا (!strcmp (p, "read"))
	    new_code = OMP_ATOMIC_READ;
	  وإلا إذا (!strcmp (p, "write"))
	    new_code = NOP_فرچ;
	  وإلا إذا (!strcmp (p, "update"))
	    new_code = OMP_ATOMIC;
	  وإلا إذا (openacc && !strcmp (p, "capture"))
	    new_code = OMP_ATOMIC_CAPTURE_NEW;
	  وإلا إذا (openacc)
	    {
	      p = عدم;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  وإلا إذا (!strcmp (p, "capture"))
	    new_capture = true;
	  وإلا إذا (!strcmp (p, "compare"))
	    new_compare = true;
	  وإلا إذا (!strcmp (p, "weak"))
	    new_weak = true;
	  وإلا إذا (!strcmp (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      إذا (!parens.require_open (parser))
		استمر;

	      إذا (c_parser_next_token_is (parser, CPP_NAME))
		{
		  ثابت حرف *q
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);

		  إذا (!strcmp (q, "seq_cst"))
		    new_fail = OMP_MEMORY_ORDER_SEQ_CST;
		  وإلا إذا (!strcmp (q, "acquire"))
		    new_fail = OMP_MEMORY_ORDER_ACQUIRE;
		  وإلا إذا (!strcmp (q, "relaxed"))
		    new_fail = OMP_MEMORY_ORDER_RELAXED;
		}

	      إذا (new_fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  إذا (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  وإلا
		    fail = new_fail;
		}
	      وإلا
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_found_close (parser);
	      استمر;
	    }
	  وإلا إذا (!strcmp (p, "seq_cst"))
	    new_memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  وإلا إذا (!strcmp (p, "acq_rel"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	  وإلا إذا (!strcmp (p, "release"))
	    new_memory_order = OMP_MEMORY_ORDER_RELEASE;
	  وإلا إذا (!strcmp (p, "acquire"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  وإلا إذا (!strcmp (p, "relaxed"))
	    new_memory_order = OMP_MEMORY_ORDER_RELAXED;
	  وإلا إذا (!strcmp (p, "hint"))
	    {
	      c_parser_consume_token (parser);
	      clauses = c_parser_omp_clause_hint (parser, clauses);
	      استمر;
	    }
	  وإلا
	    {
	      p = عدم;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "%<capture%>, %<compare%>, %<weak%>, %<fail%>, "
			      "%<seq_cst%>, %<acq_rel%>, %<release%>, "
			      "%<relaxed%> or %<hint%> clause");
	    }
	  إذا (p)
	    {
	      إذا (new_code != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  إذا (openacc
		      && code == OMP_ATOMIC
		      && new_code == OMP_ATOMIC_CAPTURE_NEW)
		    code = new_code;
		  وإلا إذا (code != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  وإلا
		    code = new_code;
		}
	      وإلا إذا (new_memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  إذا (memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  وإلا
		    memory_order = new_memory_order;
		}
	      وإلا إذا (new_capture)
		{
		  إذا (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  وإلا
		    capture = true;
		}
	      وإلا إذا (new_compare)
		{
		  إذا (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  وإلا
		    compare = true;
		}
	      وإلا إذا (new_weak)
		{
		  إذا (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  وإلا
		    weak = true;
		}
	      c_parser_consume_token (parser);
	      استمر;
	    }
	}
      اكسر;
    }
  c_parser_skip_to_pragma_eol (parser);

  إذا (code == ERROR_MARK)
    code = OMP_ATOMIC;
  إذا (capture)
    {
      إذا (code != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      وإلا
	code = OMP_ATOMIC_CAPTURE_NEW;
    }
  إذا (compare && code != OMP_ATOMIC && code != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = خطأ;
    }
  إذا (fail != OMP_MEMORY_ORDER_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      fail = OMP_MEMORY_ORDER_UNSPECIFIED;
    }
  إذا (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = خطأ;
    }
  إذا (openacc)
    memory_order = OMP_MEMORY_ORDER_RELAXED;
  وإلا إذا (memory_order == OMP_MEMORY_ORDER_UNSPECIFIED)
    {
      omp_requires_mask
	= (تعداد omp_requires) (omp_requires_mask
			       | OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED);
      بدل ((تعداد omp_memory_order)
	      (omp_requires_mask & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER))
	{
	حالة OMP_MEMORY_ORDER_UNSPECIFIED:
	حالة OMP_MEMORY_ORDER_RELAXED:
	  memory_order = OMP_MEMORY_ORDER_RELAXED;
	  اكسر;
	حالة OMP_MEMORY_ORDER_SEQ_CST:
	  memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  اكسر;
	حالة OMP_MEMORY_ORDER_ACQUIRE:
	  إذا (code == NOP_فرچ)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  وإلا
	    memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  اكسر;
	حالة OMP_MEMORY_ORDER_RELEASE:
	  إذا (code == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  وإلا
	    memory_order = OMP_MEMORY_ORDER_RELEASE;
	  اكسر;
	حالة OMP_MEMORY_ORDER_ACQ_REL:
	  بدل (code)
	    {
	    حالة OMP_ATOMIC_READ:
	      memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	      اكسر;
	    حالة NOP_فرچ: /* atomic write */
	      memory_order = OMP_MEMORY_ORDER_RELEASE;
	      اكسر;
	    افتراضي:
	      memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	      اكسر;
	    }
	  اكسر;
	افتراضي:
	  gcc_unreachable ();
	}
    }
  وإلا
    بدل (code)
      {
      حالة OMP_ATOMIC_READ:
	إذا (memory_order == OMP_MEMORY_ORDER_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	وإلا إذا (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	اكسر;
      حالة NOP_فرچ: /* atomic write */
	إذا (memory_order == OMP_MEMORY_ORDER_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	وإلا إذا (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_RELEASE;
	اكسر;
      افتراضي:
	اكسر;
      }
  إذا (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
    memory_order
      = (تعداد omp_memory_order) (memory_order
				 | (fail << OMP_FAIL_MEMORY_ORDER_SHIFT));

  بدل (code)
    {
    حالة OMP_ATOMIC_READ:
    حالة NOP_فرچ: /* atomic write */
      v = c_parser_cast_expression (parser, عدم).درج;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, خطأ, عدم, true);
      إذا (v == error_mark_كلي)
	اذهب saw_error;
      إذا (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	اذهب saw_error;
      إذا (code == NOP_فرچ)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  فرچ = c_parser_expression (parser);
	  فرچ = default_function_array_read_conversion (eloc, فرچ);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  code = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_بشيا;
	  rhs = c_fully_fold (فرچ.درج, خطأ, عدم);
	  إذا (rhs == error_mark_كلي)
	    اذهب saw_error;
	}
      وإلا
	{
	  lhs = c_parser_cast_expression (parser, عدم).درج;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, خطأ, عدم, true);
	  إذا (lhs == error_mark_كلي)
	    اذهب saw_error;
	  إذا (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      اذهب done;
    حالة OMP_ATOMIC_CAPTURE_NEW:
      إذا (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_block = true;
	}
      وإلا إذا (compare
	       && c_parser_next_token_is_keyword (parser, RID_IF))
	اكسر;
      وإلا
	{
	  v = c_parser_cast_expression (parser, عدم).درج;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, خطأ, عدم, true);
	  إذا (v == error_mark_كلي)
	    اذهب saw_error;
	  إذا (non_lvalue_p)
	    v = non_lvalue (v);
	  إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    اذهب saw_error;
	  إذا (compare && c_parser_next_token_is_keyword (parser, RID_IF))
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "expected expression");
	      اذهب saw_error;
	    }
	}
      اكسر;
    افتراضي:
      اكسر;
    }

  /* For structured_block case we don't know yet whether
     old or new x should be captured.  */
restart:
  إذا (compare && c_parser_next_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      إذا (!parens.require_open (parser))
	اذهب saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_فرچ cmp_فرچ;
      إذا (r)
	{
	  cmp_فرچ = c_parser_cast_expression (parser, عدم);
	  cmp_فرچ = default_function_array_conversion (eloc, cmp_فرچ);
	}
      وإلا
	cmp_فرچ = c_parser_نبيو_expression (parser, عدم, void_list_كلي);
      parens.skip_until_found_close (parser);
      إذا (cmp_فرچ.درج == error_mark_كلي)
	اذهب saw_error;
      إذا (r)
	{
	  إذا (!c_بشيا_equal (cmp_فرچ.درج, unfolded_lhs))
	    اذهب bad_if;
	  cmp_فرچ.درج = rhs1;
	  rhs1 = NULL_بشيا;
	  gcc_assert (بشيا_CODE (cmp_فرچ.درج) == EQ_فرچ);
	}
      إذا (بشيا_CODE (cmp_فرچ.درج) == EQ_فرچ)
	;
      وإلا إذا (!structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (فرچ_LOC_OR_LOC (cmp_فرچ.درج, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  اذهب saw_error;
	}
      وإلا إذا (بشيا_CODE (cmp_فرچ.درج) != GT_فرچ
	       && بشيا_CODE (cmp_فرچ.درج) != LT_فرچ)
	{
	  error_at (فرچ_LOC_OR_LOC (cmp_فرچ.درج, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  اذهب saw_error;
	}
      إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	اذهب saw_error;

      extra_scope = true;
      eloc = c_parser_peek_token (parser)->location;
      فرچ = c_parser_cast_expression (parser, عدم);
      lhs = فرچ.درج;
      فرچ = default_function_array_conversion (eloc, فرچ);
      unfolded_lhs = فرچ.درج;
      lhs = c_fully_fold (lhs, خطأ, عدم, true);
      orig_lhs = lhs;
      إذا (lhs == error_mark_كلي)
	اذهب saw_error;
      إذا (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      إذا (!c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  اذهب saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      فرچ = c_parser_فرچ_no_commas (parser, عدم);
      rhs1 = فرچ.درج;

      إذا (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	اذهب saw_error;

      إذا (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	اذهب saw_error;

      extra_scope = خطأ;
      no_semicolon = true;

      إذا (c_بشيا_equal (بشيا_OPERAND (cmp_فرچ.درج, 0), unfolded_lhs))
	{
	  إذا (بشيا_CODE (cmp_فرچ.درج) == EQ_فرچ)
	    {
	      opcode = COND_فرچ;
	      rhs = c_fully_fold (بشيا_OPERAND (cmp_فرچ.درج, 1),
				  خطأ, عدم, true);
	      rhs1 = c_fully_fold (rhs1, خطأ, عدم, true);
	    }
	  وإلا إذا (c_بشيا_equal (بشيا_OPERAND (cmp_فرچ.درج, 1), rhs1))
	    {
	      opcode = (بشيا_CODE (cmp_فرچ.درج) == GT_فرچ
			? MIN_فرچ : MAX_فرچ);
	      rhs = c_fully_fold (rhs1, خطأ, عدم, true);
	      rhs1 = c_fully_fold (بشيا_OPERAND (cmp_فرچ.درج, 0),
				   خطأ, عدم, true);
	    }
	  وإلا
	    اذهب bad_if;
	}
      وإلا إذا (بشيا_CODE (cmp_فرچ.درج) == EQ_فرچ)
	اذهب bad_if;
      وإلا إذا (c_بشيا_equal (بشيا_OPERAND (cmp_فرچ.درج, 1), unfolded_lhs)
	       && c_بشيا_equal (بشيا_OPERAND (cmp_فرچ.درج, 0), rhs1))
	{
	  opcode = (بشيا_CODE (cmp_فرچ.درج) == GT_فرچ
		    ? MAX_فرچ : MIN_فرچ);
	  rhs = c_fully_fold (rhs1, خطأ, عدم, true);
	  rhs1 = c_fully_fold (بشيا_OPERAND (cmp_فرچ.درج, 1),
			       خطأ, عدم, true);
	}
      وإلا
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  اذهب saw_error;
	}

      إذا (c_parser_next_token_is_keyword (parser, RID_ELSE))
	{
	  إذا (code != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_block && r == NULL_بشيا)
	      || بشيا_CODE (cmp_فرچ.درج) != EQ_فرچ)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      اذهب saw_error;
	    }

	  c_parser_consume_token (parser);

	  إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    اذهب saw_error;

	  extra_scope = true;
	  v = c_parser_cast_expression (parser, عدم).درج;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, خطأ, عدم, true);
	  إذا (v == error_mark_كلي)
	    اذهب saw_error;
	  إذا (non_lvalue_p)
	    v = non_lvalue (v);
	  إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    اذهب saw_error;

	  فرچ = c_parser_فرچ_no_commas (parser, عدم);

	  إذا (!c_بشيا_equal (فرچ.درج, unfolded_lhs))
	    اذهب bad_if;

	  إذا (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    اذهب saw_error;

	  إذا (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    اذهب saw_error;

	  extra_scope = خطأ;
	  code = OMP_ATOMIC_CAPTURE_OLD;
	  إذا (r == NULL_بشيا)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_كلي;
	}
      وإلا إذا (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  اذهب saw_error;
	}
      وإلا إذا (code == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_بشيا
	       && v == NULL_بشيا)
	code = OMP_ATOMIC;
      اذهب stmt_done;
    }
  eloc = c_parser_peek_token (parser)->location;
  فرچ = c_parser_cast_expression (parser, عدم);
  lhs = فرچ.درج;
  فرچ = default_function_array_conversion (eloc, فرچ);
  unfolded_lhs = فرچ.درج;
  lhs = c_fully_fold (lhs, خطأ, عدم, true);
  orig_lhs = lhs;
  بدل (بشيا_CODE (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    حالة ERROR_MARK:
    saw_error:
      c_parser_skip_to_end_of_block_or_statement (parser);
      إذا (extra_scope && c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      إذا (structured_block)
	{
	  إذا (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  وإلا إذا (code == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      إذا (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      أرجع;

    حالة POSTINCREMENT_فرچ:
      إذا (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    حالة PREINCREMENT_فرچ:
      lhs = بشيا_OPERAND (lhs, 0);
      unfolded_lhs = NULL_بشيا;
      opcode = PLUS_فرچ;
      rhs = integer_one_كلي;
      إذا (compare)
	اذهب invalid_compare;
      اكسر;

    حالة POSTDECREMENT_فرچ:
      إذا (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    حالة PREDECREMENT_فرچ:
      lhs = بشيا_OPERAND (lhs, 0);
      unfolded_lhs = NULL_بشيا;
      opcode = MINUS_فرچ;
      rhs = integer_one_كلي;
      إذا (compare)
	اذهب invalid_compare;
      اكسر;

    حالة COMPOUND_فرچ:
      إذا (بشيا_CODE (بشيا_OPERAND (lhs, 0)) == SAVE_فرچ
	  && بشيا_CODE (بشيا_OPERAND (lhs, 1)) == COMPOUND_فرچ
	  && بشيا_CODE (بشيا_OPERAND (بشيا_OPERAND (lhs, 1), 0)) == MODIFY_فرچ
	  && بشيا_OPERAND (بشيا_OPERAND (lhs, 1), 1) == بشيا_OPERAND (lhs, 0)
	  && C_BOOLEAN_TYPE_P (بشيا_TYPE (بشيا_OPERAND (بشيا_OPERAND
					      (بشيا_OPERAND (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = بشيا_OPERAND (بشيا_OPERAND (lhs, 1), 0);
      /* FALLTHRU */
    حالة MODIFY_فرچ:
      إذا (بشيا_CODE (lhs) == MODIFY_فرچ
	  && C_BOOLEAN_TYPE_P (بشيا_TYPE (بشيا_OPERAND (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  إذا (integer_onep (بشيا_OPERAND (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = بشيا_OPERAND (lhs, 1);
	      lhs = بشيا_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_بشيا;
	      opcode = NOP_فرچ;
	      إذا (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && بشيا_CODE (orig_lhs) == COMPOUND_فرچ)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      إذا (compare)
		اذهب invalid_compare;
	      اكسر;
	    }
	  إذا (بشيا_CODE (بشيا_OPERAND (lhs, 1)) == TRUTH_NOT_فرچ
	      && بشيا_OPERAND (lhs, 0)
		 == بشيا_OPERAND (بشيا_OPERAND (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = بشيا_OPERAND (lhs, 1);
	      lhs = بشيا_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_بشيا;
	      opcode = NOP_فرچ;
	      إذا (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && بشيا_CODE (orig_lhs) == COMPOUND_فرچ)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      إذا (compare)
		اذهب invalid_compare;
	      اكسر;
	    }
	}
      /* FALLTHRU */
    افتراضي:
      إذا (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      إذا (compare && !c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  اذهب saw_error;
	}
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_MULT_EQ:
	  opcode = MULT_فرچ;
	  اكسر;
	حالة CPP_DIV_EQ:
	  opcode = TRUNC_DIV_فرچ;
	  اكسر;
	حالة CPP_PLUS_EQ:
	  opcode = PLUS_فرچ;
	  اكسر;
	حالة CPP_MINUS_EQ:
	  opcode = MINUS_فرچ;
	  اكسر;
	حالة CPP_LSHIFT_EQ:
	  opcode = LSHIFT_فرچ;
	  اكسر;
	حالة CPP_RSHIFT_EQ:
	  opcode = RSHIFT_فرچ;
	  اكسر;
	حالة CPP_AND_EQ:
	  opcode = BIT_AND_فرچ;
	  اكسر;
	حالة CPP_OR_EQ:
	  opcode = BIT_IOR_فرچ;
	  اكسر;
	حالة CPP_XOR_EQ:
	  opcode = BIT_XOR_فرچ;
	  اكسر;
	حالة CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  فرچ = c_parser_فرچ_no_commas (parser, عدم, unfolded_lhs);
	  rhs1 = فرچ.درج;
	  بدل (بشيا_CODE (rhs1))
	    {
	    حالة MULT_فرچ:
	    حالة TRUNC_DIV_فرچ:
	    حالة RDIV_فرچ:
	    حالة PLUS_فرچ:
	    حالة MINUS_فرچ:
	    حالة LSHIFT_فرچ:
	    حالة RSHIFT_فرچ:
	    حالة BIT_AND_فرچ:
	    حالة BIT_IOR_فرچ:
	    حالة BIT_XOR_فرچ:
	      إذا (compare)
		اكسر;
	      إذا (c_بشيا_equal (بشيا_OPERAND (rhs1, 0), unfolded_lhs))
		{
		  opcode = بشيا_CODE (rhs1);
		  rhs = c_fully_fold (بشيا_OPERAND (rhs1, 1), خطأ, عدم,
				      true);
		  rhs1 = c_fully_fold (بشيا_OPERAND (rhs1, 0), خطأ, عدم,
				       true);
		  اذهب stmt_done;
		}
	      إذا (c_بشيا_equal (بشيا_OPERAND (rhs1, 1), unfolded_lhs))
		{
		  opcode = بشيا_CODE (rhs1);
		  rhs = c_fully_fold (بشيا_OPERAND (rhs1, 0), خطأ, عدم,
				      true);
		  rhs1 = c_fully_fold (بشيا_OPERAND (rhs1, 1), خطأ, عدم,
				       true);
		  swapped = !commutative_بشيا_code (opcode);
		  اذهب stmt_done;
		}
	      اكسر;
	    حالة COND_فرچ:
	      إذا (!compare)
		اكسر;
	      إذا (بشيا_CODE (بشيا_OPERAND (rhs1, 0)) != GT_فرچ
		  && بشيا_CODE (بشيا_OPERAND (rhs1, 0)) != LT_فرچ
		  && بشيا_CODE (بشيا_OPERAND (rhs1, 0)) != EQ_فرچ)
		اكسر;
	      إذا (!بشيا_OPERAND (rhs1, 1))
		اكسر;
	      إذا (!c_بشيا_equal (بشيا_OPERAND (rhs1, 2), unfolded_lhs))
		اكسر;
	      إذا (c_بشيا_equal (بشيا_OPERAND (بشيا_OPERAND (rhs1, 0), 0),
				unfolded_lhs))
		{
		  إذا (بشيا_CODE (بشيا_OPERAND (rhs1, 0)) == EQ_فرچ)
		    {
		      opcode = COND_فرچ;
		      rhs = c_fully_fold (بشيا_OPERAND (بشيا_OPERAND (rhs1,
								      0), 1),
					  خطأ, عدم, true);
		      rhs1 = c_fully_fold (بشيا_OPERAND (rhs1, 1), خطأ,
					   عدم, true);
		      اذهب stmt_done;
		    }
		  إذا (c_بشيا_equal (بشيا_OPERAND (بشيا_OPERAND (rhs1, 0), 1),
				    بشيا_OPERAND (rhs1, 1)))
		    {
		      opcode = (بشيا_CODE (بشيا_OPERAND (rhs1, 0)) == GT_فرچ
				? MIN_فرچ : MAX_فرچ);
		      rhs = c_fully_fold (بشيا_OPERAND (rhs1, 1), خطأ, عدم,
					  true);
		      rhs1 = c_fully_fold (بشيا_OPERAND (بشيا_OPERAND (rhs1,
								       0), 0),
					   خطأ, عدم, true);
		      اذهب stmt_done;
		    }
		}
	      وإلا إذا (بشيا_CODE (بشيا_OPERAND (rhs1, 0)) == EQ_فرچ)
		اكسر;
	      وإلا إذا (c_بشيا_equal (بشيا_OPERAND (بشيا_OPERAND (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  إذا (c_بشيا_equal (بشيا_OPERAND (بشيا_OPERAND (rhs1, 0), 0),
				    بشيا_OPERAND (rhs1, 1)))
		    {
		      opcode = (بشيا_CODE (بشيا_OPERAND (rhs1, 0)) == GT_فرچ
				? MAX_فرچ : MIN_فرچ);
		      rhs = c_fully_fold (بشيا_OPERAND (rhs1, 1), خطأ, عدم,
					  true);
		      rhs1 = c_fully_fold (بشيا_OPERAND (بشيا_OPERAND (rhs1,
								       0), 1),
					   خطأ, عدم, true);
		      اذهب stmt_done;
		    }
		}
	      اكسر;
	    حالة EQ_فرچ:
	      إذا (!compare
		  || code != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_block
		  || v
		  || r)
		اكسر;
	      إذا (c_parser_next_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_بشيا;
		  c_parser_consume_token (parser);
		  اذهب restart;
		}
	      اكسر;
	    حالة ERROR_MARK:
	      اذهب saw_error;
	    افتراضي:
	      اكسر;
	    }
	  إذا (c_parser_peek_token (parser)->type == CPP_SEMICOLON)
	    {
	      إذا (structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
		{
		  code = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_بشيا;
		  فرچ = default_function_array_read_conversion (eloc, فرچ);
		  unfolded_lhs1 = فرچ.درج;
		  lhs1 = c_fully_fold (unfolded_lhs1, خطأ, عدم, true);
		  rhs1 = NULL_بشيا;
		  c_parser_consume_token (parser);
		  اذهب restart;
		}
	      إذا (structured_block && !compare)
		{
		  opcode = NOP_فرچ;
		  فرچ = default_function_array_read_conversion (eloc, فرچ);
		  rhs = c_fully_fold (فرچ.درج, خطأ, عدم, true);
		  rhs1 = NULL_بشيا;
		  اذهب stmt_done;
		}
	    }
	  c_parser_error (parser, "invalid form of %<#pragma omp atomic%>");
	  اذهب saw_error;
	افتراضي:
	  c_parser_error (parser,
			  "invalid operator for %<#pragma omp atomic%>");
	  اذهب saw_error;
	}

      /* Arrange to pass the location of the assignment operator to
	 c_finish_omp_atomic.  */
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      فرچ = c_parser_expression (parser);
      فرچ = default_function_array_read_conversion (eloc, فرچ);
      rhs = فرچ.درج;
      rhs = c_fully_fold (rhs, خطأ, عدم, true);
      اكسر;
    }
stmt_done:
  إذا (structured_block && code == OMP_ATOMIC_CAPTURE_NEW && r == NULL_بشيا)
    {
      إذا (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	اذهب saw_error;
      no_semicolon = خطأ;
      v = c_parser_cast_expression (parser, عدم).درج;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, خطأ, عدم, true);
      إذا (v == error_mark_كلي)
	اذهب saw_error;
      إذا (non_lvalue_p)
	v = non_lvalue (v);
      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	اذهب saw_error;
      eloc = c_parser_peek_token (parser)->location;
      فرچ = c_parser_cast_expression (parser, عدم);
      lhs1 = فرچ.درج;
      فرچ = default_function_array_read_conversion (eloc, فرچ);
      unfolded_lhs1 = فرچ.درج;
      lhs1 = c_fully_fold (lhs1, خطأ, عدم, true);
      إذا (lhs1 == error_mark_كلي)
	اذهب saw_error;
      إذا (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  إذا (structured_block)
    {
      إذا (!no_semicolon)
	c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
done:
  إذا (weak && opcode != COND_فرچ)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = خطأ;
    }
  إذا (unfolded_lhs && unfolded_lhs1
      && !c_بشيا_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_كلي;
    }
  وإلا
    stmt = c_finish_omp_atomic (loc, code, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, memory_order, weak);
  إذا (stmt != error_mark_كلي)
    add_stmt (stmt);

  إذا (!structured_block && !no_semicolon)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}


/* OpenMP 2.5:
   # pragma omp barrier new-line
*/

ساكن فراغ
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

ساكن بشيا
c_parser_omp_critical (location_t loc, c_parser *parser, منطقي *if_p)
{
  بشيا stmt, name = NULL_بشيا, clauses = NULL_بشيا;

  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_next_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->درج;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      وإلا
	c_parser_error (parser, "expected identifier");

      إذا (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_MASK,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_block (parser, if_p);
  أرجع c_finish_omp_critical (loc, stmt, name, clauses);
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

ساكن فراغ
c_parser_omp_depobj (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  matching_parens parens;
  إذا (!parens.require_open (parser))
    {
      c_parser_skip_to_pragma_eol (parser);
      أرجع;
    }

  بشيا depobj = c_parser_فرچ_no_commas (parser, عدم).درج;
  إذا (depobj != error_mark_كلي)
    {
      إذا (!lvalue_p (depobj))
	{
	  error_at (فرچ_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_كلي;
	}
      وإلا
	{
	  بشيا addr = build_unary_op (فرچ_LOC_OR_LOC (depobj, loc), ADDR_فرچ,
				      depobj, خطأ);
	  إذا (addr == error_mark_كلي)
	    depobj = error_mark_كلي;
	  وإلا
	    depobj = build_indirect_ref (فرچ_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_STAR);
	}
    }

  parens.skip_until_found_close (parser);
  بشيا clause = NULL_بشيا;
  تعداد omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_INVALID;
  إذا (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);

      c_parser_consume_token (parser);
      إذا (!strcmp ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_بشيا, c_loc);
	  clause = c_finish_omp_clauses (clause, C_ORT_OMP);
	  إذا (!clause)
	    clause = error_mark_كلي;
	}
      وإلا إذا (!strcmp ("destroy", p))
	{
	  matching_parens c_parens;
	  kind = OMP_CLAUSE_DEPEND_LAST;
	  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      بشيا destobj = c_parser_فرچ_no_commas (parser, عدم).درج;
	      إذا (!lvalue_p (destobj))
		error_at (فرچ_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      وإلا إذا (depobj != error_mark_كلي
		       && !operand_equal_p (destobj, depobj,
					    OEP_MATCH_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (فرچ_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_found_close (parser);
	    }
	}
      وإلا إذا (!strcmp ("update", p))
	{
	  matching_parens c_parens;
	  إذا (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      إذا (c_parser_next_token_is (parser, CPP_NAME))
		{
		  ثابت حرف *p2
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);

		  c_parser_consume_token (parser);
		  إذا (!strcmp ("in", p2))
		    kind = OMP_CLAUSE_DEPEND_IN;
		  وإلا إذا (!strcmp ("out", p2))
		    kind = OMP_CLAUSE_DEPEND_OUT;
		  وإلا إذا (!strcmp ("inout", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUT;
		  وإلا إذا (!strcmp ("mutexinoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  وإلا إذا (!strcmp ("inoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      إذا (kind == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_كلي;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_found_close (parser);
	    }
	  وإلا
	    clause = error_mark_كلي;
	}
    }
  إذا (!clause && kind == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_كلي;
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

ساكن فراغ
c_parser_omp_flush (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  تعداد memmodel mo = MEMMODEL_LAST;
  إذا (c_parser_next_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);

      إذا (!strcmp (p, "seq_cst"))
	mo = MEMMODEL_SEQ_CST;
      وإلا إذا (!strcmp (p, "acq_rel"))
	mo = MEMMODEL_ACQ_REL;
      وإلا إذا (!strcmp (p, "release"))
	mo = MEMMODEL_RELEASE;
      وإلا إذا (!strcmp (p, "acquire"))
	mo = MEMMODEL_ACQUIRE;
      وإلا
	error_at (c_parser_peek_token (parser)->location,
		  "expected %<seq_cst%>, %<acq_rel%>, %<release%> or "
		  "%<acquire%>");
      c_parser_consume_token (parser);
    }
  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      إذا (mo != MEMMODEL_LAST)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, عدم);
    }
  وإلا إذا (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_to_pragma_eol (parser);

  c_finish_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

ساكن منطقي
c_parser_omp_section_scan (c_parser *parser, ثابت حرف *directive,
			   منطقي tentative)
{
  إذا (!c_parser_nth_token_starts_std_attributes (parser, 1))
    أرجع خطأ;
  unsigned صحيح n = 3;
  إذا (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    أرجع خطأ;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  إذا (token->type != CPP_CLOSE_SQUARE)
    أرجع خطأ;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  إذا (token->type != CPP_CLOSE_SQUARE)
    أرجع خطأ;
  إذا (n < 9)
    أرجع خطأ;
  إذا (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      بشيا first = c_parser_peek_nth_token_raw (parser, 3)->درج;
      بشيا second = c_parser_peek_nth_token_raw (parser, 5)->درج;
      إذا (strcmp (IDENTIFIER_POINTER (first), "directive")
	  && strcmp (IDENTIFIER_POINTER (first), "__directive__"))
	أرجع خطأ;
      إذا (strcmp (IDENTIFIER_POINTER (second), directive))
	أرجع خطأ;
    }
  إذا (tentative)
    أرجع true;
  location_t first_loc = c_parser_peek_token (parser)->location;
  location_t last_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t ڟكيا_loc = UNKNOWN_LOCATION;
  بشيا std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  منطقي seen = خطأ;
  صحيح cnt = 0;
  لكل (بشيا attr = std_attrs; attr; attr = بشيا_CHAIN (attr))
    إذا (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	لكل (بشيا a = بشيا_درج (attr); a; a = بشيا_CHAIN (a))
	  {
	    بشيا d = بشيا_درج (a);
	    gcc_assert (بشيا_CODE (d) == C_TOKEN_VEC);
	    c_token *first = C_TOKEN_VEC_TOKENS (d)->address ();
	    cnt++;
	    إذا (first->type == CPP_NAME
		&& strcmp (IDENTIFIER_POINTER (first->درج),
			   directive) == 0)
	      {
		seen = true;
		إذا (ڟكيا_loc == UNKNOWN_LOCATION)
		  ڟكيا_loc = first->location;
	      }
	  }
      }
  إذا (!seen)
    أرجع خطأ;
  إذا (cnt != 1 || بشيا_CHAIN (std_attrs))
    {
      error_at (make_location (first_loc, last_loc, ڟكيا_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      أرجع خطأ;
    }
  c_parser_handle_statement_omp_attributes (parser, std_attrs, عدم);
  أرجع true;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

ساكن بشيا
c_parser_omp_structured_block_sequence (c_parser *parser,
					تعداد pragma_kind kind)
{
  بشيا stmt = تور_stmt_list ();
  c_parser_statement (parser, عدم);
  افعل
    {
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	اكسر;
      إذا (c_parser_next_token_is (parser, CPP_EOF))
	اكسر;

      إذا (kind != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_kind == kind)
	اكسر;

      إذا (kind != PRAGMA_NONE
	  && c_parser_omp_section_scan (parser,
					kind == PRAGMA_OMP_SCAN
					? "scan" : "section", خطأ))
	اكسر;

      c_parser_statement (parser, عدم);
    }
  طالما (1);
  أرجع چرو_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

ساكن فراغ
c_parser_omp_scan_loop_body (c_parser *parser, منطقي open_brace_parsed)
{
  بشيا substmt;
  location_t loc;
  بشيا clauses = NULL_بشيا;
  منطقي found_scan = خطأ;

  loc = c_parser_peek_token (parser)->location;
  إذا (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = خطأ;
      أرجع;
    }

  إذا (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SCAN)
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_OMP_SCAN);
  وإلا
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_كلي, substmt, NULL_بشيا);
  SET_فرچ_LOCATION (substmt, loc);
  add_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SCAN)
    {
      تعداد omp_clause_code clause = OMP_CLAUSE_ERROR;
      found_scan = true;

      c_parser_consume_pragma (parser);

      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      إذا (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ثابت حرف *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
	  إذا (strcmp (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  وإلا إذا (strcmp (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      إذا (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_بشيا);
	}
      وإلا
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_to_pragma_eol (parser);
    }
  وإلا
    error ("expected %<#pragma omp scan%>");

  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  إذا (!c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_NONE);
  وإلا
    {
      إذا (found_scan)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_كلي, substmt, clauses);
  SET_فرچ_LOCATION (substmt, loc);
  add_stmt (substmt);

  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
ساكن منطقي
c_parser_omp_next_tokens_can_be_canon_loop (c_parser *parser,
					    تعداد بشيا_code code,
					    منطقي error_p)
{
  إذا (code == OACC_LOOP)
    {
      إذا (c_parser_next_token_is_keyword (parser, RID_FOR))
	أرجع true;
      إذا (error_p)
	c_parser_error (parser, "for statement expected");
    }
  وإلا
    {
      إذا (c_parser_next_token_is_keyword (parser, RID_FOR))
	أرجع true;

      إذا (c_parser_next_token_is (parser, CPP_PRAGMA))
	بدل (c_parser_peek_token (parser)->pragma_kind)
	  {
	  حالة PRAGMA_OMP_UNROLL:
	  حالة PRAGMA_OMP_TILE:
	    أرجع true;
	  افتراضي:
	    اكسر;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      size_t n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      إذا (token->type == CPP_NAME
	  && C_IS_RESERVED_WORD (token->درج)
	  && C_RID_CODE (token->درج) == RID_FOR)
	أرجع true;
      إذا (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  أرجع خطأ;
}

ساكن بشيا c_parser_omp_tile (location_t, c_parser *, منطقي *);
ساكن بشيا c_parser_omp_unroll (location_t, c_parser *, منطقي *);

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

ساكن بشيا
c_parser_omp_loop_nest (c_parser *parser, منطقي *if_p)
{
  بشيا decl = NULL_بشيا, cond = NULL_بشيا, incr = NULL_بشيا, init = NULL_بشيا;
  بشيا body = NULL_بشيا;
  matching_parens parens;
  منطقي moreloops;
  unsigned حرف save_in_statement;
  بشيا loop_scope;
  location_t loc;
  بنية omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  صحيح depth = omp_for_parse_state->depth;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  إذا (c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      بشيا std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_attributes (parser, std_attrs, عدم);
      إذا (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  إذا (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      بشيا transform = NULL_بشيا, sizes, body = NULL_بشيا;
      صحيح كدي = 0;
      بدل (c_parser_peek_token (parser)->pragma_kind)
	{
	حالة PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = تور_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = چرو_stmt_list (body);
	  إذا (transform == NULL_بشيا || transform == error_mark_كلي)
	    {
	      transform = error_mark_كلي;
	      اكسر;
	    }
	  gcc_assert (بشيا_CODE (transform) == OMP_UNROLL);
	  إذا (omp_find_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      إذا (omp_for_parse_state->كدي - depth > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->كدي - depth);
		  transform = error_mark_كلي;
		}
	      وإلا
		كدي = 1;
	    }
	  وإلا
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_كلي;
	    }
	  اكسر;
	حالة PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = تور_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = چرو_stmt_list (body);
	  إذا (transform == NULL_بشيا || transform == error_mark_كلي)
	    {
	      transform = error_mark_كلي;
	      اكسر;
	    }
	  gcc_assert (بشيا_CODE (transform) == OMP_TILE);
	  sizes = omp_find_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  كدي = list_length (OMP_CLAUSE_SIZES_LIST (sizes));
	  إذا (depth + كدي < omp_for_parse_state->كدي)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			كدي, omp_for_parse_state->كدي - depth);
	      transform = error_mark_كلي;
	    }
	  اكسر;
	افتراضي:
	  c_parser_pragma (parser, pragma_stmt, عدم, void_list_كلي);
	  اكسر;
	}
      إذا (transform == NULL_بشيا)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      إذا (transform == NULL_بشيا || transform == error_mark_كلي)
	{
	  omp_for_parse_state->fail = true;
	  أرجع NULL_بشيا;
	}
      لكل (كدي = omp_for_parse_state->كدي; depth < كدي; ++depth)
	{
	  بشيا_VEC_ELT (omp_for_parse_state->declv, depth) = NULL_بشيا;
	  بشيا_VEC_ELT (omp_for_parse_state->initv, depth) = NULL_بشيا;
	  بشيا_VEC_ELT (omp_for_parse_state->condv, depth) = NULL_بشيا;
	  بشيا_VEC_ELT (omp_for_parse_state->incrv, depth) = NULL_بشيا;
	}
      omp_for_parse_state->want_nested_loop = خطأ;
      أرجع body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_in_statement = in_statement;
  in_statement = IN_OMP_BLOCK;

  /* We are not in intervening code now.  */
  omp_for_parse_state->in_intervening_code = خطأ;

  إذا (!parens.require_open (parser))
    {
      omp_for_parse_state->fail = true;
      أرجع NULL_بشيا;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (true);

  /* Parse the initialization declaration or expression.  */
  إذا (c_parser_next_tokens_start_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      بشيا this_pre_body = تور_stmt_list ();
      c_in_omp_for = true;
      c_parser_declaration_or_fndef (parser, true, true, true, true, true,
				     خطأ);
      c_in_omp_for = خطأ;
      this_pre_body = چرو_stmt_list (this_pre_body);
      append_to_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      إذا (decl == عدم)
	اذهب error_init;
      إذا (DECL_INITIAL (decl) == error_mark_كلي)
	decl = error_mark_كلي;
      init = decl;
    }
  وإلا إذا (c_parser_next_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      بنية c_فرچ decl_exp;
      بنية c_فرچ init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_expression (parser);
      decl = decl_exp.درج;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_فرچ_no_commas (parser, عدم);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_in_omp_for = true;
      init = build_modify_فرچ (init_loc, decl, decl_exp.original_type,
				NOP_فرچ, init_loc, init_exp.درج,
				init_exp.original_type);
      c_in_omp_for = خطأ;
      init = c_process_فرچ_stmt (init_loc, init);

      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  وإلا
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->fail = true;
      اذهب parse_next;
    }

  /* Parse the loop condition.  */
  إذا (c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_in_omp_for = true;
      بنية c_فرچ cond_فرچ
	= c_parser_نبيو_expression (parser, عدم, NULL_بشيا);
      c_in_omp_for = خطأ;

      cond = cond_فرچ.درج;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      بدل (cond_فرچ.original_code)
	{
	حالة GT_فرچ:
	حالة GE_فرچ:
	حالة LT_فرچ:
	حالة LE_فرچ:
	  اكسر;
	حالة NE_فرچ:
	  إذا (omp_for_parse_state->code != OACC_LOOP)
	    اكسر;
	  /* FALLTHRU.  */
	افتراضي:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_فرچ, boolean_type_كلي, error_mark_كلي);
	  اكسر;
	}
      protected_set_فرچ_location (cond, cond_loc);
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  إذا (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_فرچ_stmt (incr_loc,
				  c_parser_expression (parser).درج);
    }
  parens.skip_until_found_close (parser);

  إذا (decl == عدم || decl == error_mark_كلي || init == error_mark_كلي)
    omp_for_parse_state->fail = true;
  وإلا
    {
      بشيا_VEC_ELT (omp_for_parse_state->declv, depth) = decl;
      بشيا_VEC_ELT (omp_for_parse_state->initv, depth) = init;
      بشيا_VEC_ELT (omp_for_parse_state->condv, depth) = cond;
      بشيا_VEC_ELT (omp_for_parse_state->incrv, depth) = incr;
    }

parse_next:
  moreloops = depth < omp_for_parse_state->كدي - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  إذا (moreloops
      && c_parser_omp_next_tokens_can_be_canon_loop (parser,
						     omp_for_parse_state->code,
						     خطأ))
    {
      omp_for_parse_state->depth++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->depth--;
    }
  وإلا إذا (moreloops && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
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
      body = c_parser_compound_statement (parser, عدم);
      omp_for_parse_state->in_intervening_code = خطأ;
      إذا (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = true;
	}
      if_p = عدم;
    }
  وإلا
    {
      /* This is the final-loop-body case in the grammar: we have
	 something that is not a FOR and not an open brace.  */
      إذا (moreloops)
	{
	  /* If we were expecting a nested loop, give an error and mark
	     that parsing has failed, and try to recover by parsing the
	     body as regular code without further collapsing.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = true;
	}
      in_statement = IN_OMP_FOR;
      parser->omp_for_parse_state = عدم;
      body = تور_stmt_list ();
      إذا (omp_for_parse_state->inscan)
	c_parser_omp_scan_loop_body (parser, خطأ);
      وإلا
	add_stmt (c_parser_c99_block_statement (parser, if_p));
      body = چرو_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  in_statement = save_in_statement;
  omp_for_parse_state->want_nested_loop = خطأ;
  omp_for_parse_state->in_intervening_code = true;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  إذا (body)
    add_stmt (body);
  body = c_end_compound_stmt (loc, loop_scope, true);
  إذا (decl && بشيا_CODE (body) == BIND_فرچ)
    {
      بشيا t = BIND_فرچ_VARS (body);
      بشيا prev = NULL_بشيا, next = NULL_بشيا;
      طالما (t)
	{
	  next = DECL_CHAIN (t);
	  إذا (t == decl)
	    {
	      إذا (prev)
		DECL_CHAIN (prev) = next;
	      وإلا
		{
		  BIND_فرچ_VARS (body) = next;
		  BLOCK_VARS (BIND_فرچ_BLOCK (body)) = next;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      اكسر;
	    }
	  وإلا
	    {
	      prev = t;
	      t = next;
	    }
	}
      إذا (BIND_فرچ_VARS (body) == NULL_بشيا)
	body = BIND_فرچ_BODY (body);
    }

  أرجع body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

ساكن بشيا
c_parser_omp_for_loop (location_t loc, c_parser *parser, تعداد بشيا_code code,
		       بشيا clauses, بشيا *cclauses, منطقي *if_p)
{
  بشيا body, stmt, cl;
  بشيا ret = NULL_بشيا;
  بشيا ordered_cl = NULL_بشيا;
  صحيح i, collapse = 1, ordered = 0, كدي;
  منطقي oacc_tiling = خطأ;
  منطقي inscan = خطأ;
  بنية omp_for_parse_data data;
  بنية omp_for_parse_data *save_data = parser->omp_for_parse_state;

  لكل (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    إذا (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = بشيا_to_shwi (OMP_CLAUSE_COLLAPSE_فرچ (cl));
    وإلا إذا (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = true;
	collapse = list_length (OMP_CLAUSE_TILE_LIST (cl));
      }
    وإلا إذا (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_SIZES)
      collapse = list_length (OMP_CLAUSE_SIZES_LIST (cl));
    وإلا إذا (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_فرچ (cl))
      {
	ordered_cl = cl;
	ordered = بشيا_to_shwi (OMP_CLAUSE_ORDERED_فرچ (cl));
      }
    وإلا إذا (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (code == OMP_SIMD || code == OMP_FOR))
      inscan = true;

  إذا (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_فرچ (ordered_cl)
	= build_int_cst (integer_type_كلي, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  كدي = ordered ? ordered : collapse;

  إذا (!c_parser_omp_next_tokens_can_be_canon_loop (parser, code, true))
    أرجع عدم;

  /* Initialize parse state for recursive descent.  */
  data.declv = make_بشيا_vec (كدي);
  data.initv = make_بشيا_vec (كدي);
  data.condv = make_بشيا_vec (كدي);
  data.incrv = make_بشيا_vec (كدي);
  data.pre_body = NULL_بشيا;
  data.bindings = NULL_بشيا;
  data.for_loc = c_parser_peek_token (parser)->location;
  data.كدي = كدي;
  data.depth = 0;
  data.want_nested_loop = true;
  data.ordered = ordered > 0;
  data.in_intervening_code = خطأ;
  data.perfect_nesting_fail = خطأ;
  data.fail = خطأ;
  data.inscan = inscan;
  data.saw_intervening_code = خطأ;
  data.code = code;
  parser->omp_for_parse_state = &data;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  لكل (بشيا t = data.bindings; t; )
    {
      بشيا n = بشيا_CHAIN (t);
      بشيا_CHAIN (t) = NULL_بشيا;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  إذا (!data.fail)
    {
      c_in_omp_for = true;
      stmt = c_finish_omp_for (loc, code, data.declv, عدم, data.initv,
			       data.condv, data.incrv,
			       body, data.pre_body, true);
      c_in_omp_for = خطأ;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      إذا (stmt && !c_omp_check_loop_iv (stmt, data.declv, عدم))
	stmt = NULL_بشيا;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      إذا (data.saw_intervening_code
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, عدم))
	stmt = NULL_بشيا;

      إذا (stmt)
	{
	  add_stmt (stmt);

	  لكل (i = 0; i < بشيا_VEC_LENGTH (OMP_FOR_INIT (stmt)); i++)
	    {
	      بشيا init = بشيا_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      إذا (init == NULL_بشيا)
		اكسر;
	      gcc_assert (بشيا_CODE (init) == MODIFY_فرچ);
	      بشيا decl = بشيا_OPERAND (init, 0);
	      بشيا cond = بشيا_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (بشيا_OPERAND (cond, 0) == decl);

	      بشيا op0 = بشيا_OPERAND (init, 1);
	      إذا (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || بشيا_CODE (op0) != بشيا_VEC)
		بشيا_OPERAND (init, 1) = c_fully_fold (op0, خطأ, عدم);
	      وإلا
		{
		  بشيا_VEC_ELT (op0, 1)
		    = c_fully_fold (بشيا_VEC_ELT (op0, 1), خطأ, عدم);
		  بشيا_VEC_ELT (op0, 2)
		    = c_fully_fold (بشيا_VEC_ELT (op0, 2), خطأ, عدم);
		}

	      بشيا op1 = بشيا_OPERAND (cond, 1);
	      إذا (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || بشيا_CODE (op1) != بشيا_VEC)
		بشيا_OPERAND (cond, 1) = c_fully_fold (op1, خطأ, عدم);
	      وإلا
		{
		  بشيا_VEC_ELT (op1, 1)
		    = c_fully_fold (بشيا_VEC_ELT (op1, 1), خطأ, عدم);
		  بشيا_VEC_ELT (op1, 2)
		    = c_fully_fold (بشيا_VEC_ELT (op1, 2), خطأ, عدم);
		}
	    }

	  إذا (cclauses != عدم
	      && cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL] != عدم)
	    {
	      بشيا *c;
	      لكل (c = &cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL]; *c ; )
		إذا (OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		وإلا
		  {
		    لكل (i = 0; i < كدي; i++)
		      إذا (بشيا_VEC_ELT (data.declv, i) == OMP_CLAUSE_DECL (*c))
			اكسر;
		    إذا (i == كدي)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    وإلا إذا (OMP_CLAUSE_CODE (*c) == OMP_CLAUSE_FIRSTPRIVATE)
		      {
			error_at (loc,
				  "iteration variable %qD should not be firstprivate",
				  OMP_CLAUSE_DECL (*c));
			*c = OMP_CLAUSE_CHAIN (*c);
		      }
		    وإلا
		      {
			/* Move lastprivate (decl) clause to
			   OMP_FOR_CLAUSES.  */
			بشيا l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			إذا (code == OMP_SIMD)
			  {
			    OMP_CLAUSE_CHAIN (l)
			      = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
			    cclauses[C_OMP_CLAUSE_SPLIT_FOR] = l;
			  }
			وإلا
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
  أرجع ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

ساكن فراغ
omp_split_clauses (location_t loc, تعداد بشيا_code code,
		   omp_clause_mask mask, بشيا clauses, بشيا *cclauses)
{
  صحيح i;
  c_omp_split_clauses (loc, code, mask, clauses, cclauses);
  لكل (i = 0; i < C_OMP_CLAUSE_SPLIT_كدي; i++)
    إذا (cclauses[i])
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

ساكن بشيا
c_parser_omp_loop (location_t loc, c_parser *parser,
		   حرف *p_name, omp_clause_mask mask, بشيا *cclauses,
		   منطقي *if_p)
{
  بشيا block, clauses, ret;

  strcat (p_name, " loop");
  mask |= OMP_LOOP_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_split_clauses (loc, OMP_LOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_LOOP];
    }

  block = c_begin_compound_stmt (true);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  أرجع ret;
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

ساكن بشيا
c_parser_omp_simd (location_t loc, c_parser *parser,
		   حرف *p_name, omp_clause_mask mask, بشيا *cclauses,
		   منطقي *if_p)
{
  بشيا block, clauses, ret;

  strcat (p_name, " simd");
  mask |= OMP_SIMD_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_split_clauses (loc, OMP_SIMD, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SIMD];
    }

  block = c_begin_compound_stmt (true);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  أرجع ret;
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

ساكن بشيا
c_parser_omp_for (location_t loc, c_parser *parser,
		  حرف *p_name, omp_clause_mask mask, بشيا *cclauses,
		  منطقي *if_p)
{
  بشيا block, clauses, ret;

  strcat (p_name, " for");
  mask |= OMP_FOR_CLAUSE_MASK;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  إذا (cclauses && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  إذا ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);

      إذا (strcmp (p, "simd") == 0)
	{
	  بشيا cclauses_buf[C_OMP_CLAUSE_SPLIT_كدي];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (true);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, true);
	  إذا (ret == NULL_بشيا)
	    أرجع ret;
	  ret = make_كلي (OMP_FOR);
	  بشيا_TYPE (ret) = void_type_كلي;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
	  SET_فرچ_LOCATION (ret, loc);
	  add_stmt (ret);
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, خطأ);
      أرجع NULL_بشيا;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  إذا ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINEAR);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_split_clauses (loc, OMP_FOR, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
    }

  block = c_begin_compound_stmt (true);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  أرجع ret;
}

ساكن بشيا c_parser_omp_taskloop (location_t, c_parser *, حرف *,
				   omp_clause_mask, بشيا *, منطقي *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

ساكن بشيا
c_parser_omp_master (location_t loc, c_parser *parser,
		     حرف *p_name, omp_clause_mask mask, بشيا *cclauses,
		     منطقي *if_p, location_t master_loc)
{
  بشيا block, clauses, ret;
  gcc_rich_location richloc (loc);
  إذا (master_loc != UNKNOWN_LOCATION)
    richloc.add_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  strcat (p_name, " master");

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);

      إذا (strcmp (p, "taskloop") == 0)
	{
	  بشيا cclauses_buf[C_OMP_CLAUSE_SPLIT_كدي];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (true);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, true);
	  إذا (ret == NULL_بشيا)
	    أرجع ret;
	  ret = c_finish_omp_master (loc, block);
	  OMP_MASTER_COMBINED (ret) = 1;
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, خطأ);
      أرجع NULL_بشيا;
    }

  إذا (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, mask, p_name, خطأ);
      omp_split_clauses (loc, OMP_MASTER, mask, clauses, cclauses);
    }
  وإلا
    c_parser_skip_to_pragma_eol (parser);

  أرجع c_finish_omp_master (loc, c_parser_omp_structured_block (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#define OMP_MASKED_CLAUSE_MASK					\
	(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FILTER)

ساكن بشيا
c_parser_omp_masked (location_t loc, c_parser *parser,
		     حرف *p_name, omp_clause_mask mask, بشيا *cclauses,
		     منطقي *if_p)
{
  بشيا block, clauses, ret;

  strcat (p_name, " masked");
  mask |= OMP_MASKED_CLAUSE_MASK;

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);

      إذا (strcmp (p, "taskloop") == 0)
	{
	  بشيا cclauses_buf[C_OMP_CLAUSE_SPLIT_كدي];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (true);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, true);
	  إذا (ret == NULL_بشيا)
	    أرجع ret;
	  ret = c_finish_omp_masked (loc, block,
				     cclauses[C_OMP_CLAUSE_SPLIT_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, خطأ);
      أرجع NULL_بشيا;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_split_clauses (loc, OMP_MASKED, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_MASKED];
    }

  أرجع c_finish_omp_masked (loc, c_parser_omp_structured_block (parser,
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

ساكن فراغ
c_parser_omp_interop (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  بشيا clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_MASK,
					   "#pragma omp interop");
  بشيا stmt = make_كلي (OMP_INTEROP);
  بشيا_TYPE (stmt) = void_type_كلي;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  SET_فرچ_LOCATION (stmt, loc);
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

ساكن منطقي
c_parser_omp_ordered (c_parser *parser, تعداد pragma_context context,
		      منطقي *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  إذا (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, خطأ);
      أرجع خطأ;
    }

  صحيح n = 1;
  إذا (c_parser_next_token_is (parser, CPP_COMMA))
    n = 2;

  إذا (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      ثابت حرف *p
	= IDENTIFIER_POINTER (c_parser_peek_nth_token (parser, n)->درج);

      إذا (!strcmp ("depend", p) || !strcmp ("doacross", p))
	{
	  إذا (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_to_pragma_eol (parser, خطأ);
	      أرجع خطأ;
	    }
	  إذا (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_to_pragma_eol (parser, خطأ);
	      أرجع true;
	    }

	  بشيا clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_MASK,
					"#pragma omp ordered");
	  c_finish_omp_ordered (loc, clauses, NULL_بشيا);
	  أرجع خطأ;
	}
    }

  بشيا clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_MASK,
					   "#pragma omp ordered");

  إذا (!flag_openmp	/* flag_openmp_simd  */
      && omp_find_clause (clauses, OMP_CLAUSE_SIMD) == NULL_بشيا)
    أرجع خطأ;

  c_finish_omp_ordered (loc, clauses,
			c_parser_omp_structured_block (parser, if_p));
  أرجع true;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

ساكن بشيا
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  بشيا stmt, substmt;
  منطقي error_suppress = خطأ;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = خطأ;
      أرجع NULL_بشيا;
    }

  stmt = تور_stmt_list ();

  إذا (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_scan (parser, "section", true))
    {
      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_كلي, substmt);
      SET_فرچ_LOCATION (substmt, loc);
      add_stmt (substmt);
    }

  طالما (1)
    {
      إذا (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	اكسر;
      إذا (c_parser_next_token_is (parser, CPP_EOF))
	اكسر;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_scan (parser, "section", خطأ);
      إذا (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser);
	  error_suppress = خطأ;
	}
      وإلا إذا (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = true;
	}

      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_كلي, substmt);
      SET_فرچ_LOCATION (substmt, loc);
      add_stmt (substmt);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = چرو_stmt_list (stmt);

  stmt = make_كلي (OMP_SECTIONS);
  SET_فرچ_LOCATION (stmt, sections_loc);
  بشيا_TYPE (stmt) = void_type_كلي;
  OMP_SECTIONS_BODY (stmt) = substmt;

  أرجع add_stmt (stmt);
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

ساكن بشيا
c_parser_omp_sections (location_t loc, c_parser *parser,
		       حرف *p_name, omp_clause_mask mask, بشيا *cclauses)
{
  بشيا block, clauses, ret;

  strcat (p_name, " sections");
  mask |= OMP_SECTIONS_CLAUSE_MASK;
  إذا (cclauses)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_split_clauses (loc, OMP_SECTIONS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SECTIONS];
    }

  block = c_begin_compound_stmt (true);
  ret = c_parser_omp_sections_scope (loc, parser);
  إذا (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  أرجع ret;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_لمب_THREADS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

ساكن بشيا
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       حرف *p_name, omp_clause_mask mask, بشيا *cclauses,
		       منطقي *if_p)
{
  بشيا stmt, clauses, block;

  strcat (p_name, " parallel");
  mask |= OMP_PARALLEL_CLAUSE_MASK;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  إذا ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  إذا (c_parser_next_token_is_keyword (parser, RID_FOR))
    {
      بشيا cclauses_buf[C_OMP_CLAUSE_SPLIT_كدي];
      إذا (cclauses == عدم)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      إذا (!flag_openmp)  /* flag_openmp_simd  */
	أرجع c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      block = c_begin_omp_parallel ();
      بشيا ret = c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      stmt
	= c_finish_omp_parallel (loc, cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				 block);
      إذا (ret == NULL_بشيا)
	أرجع ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      أرجع stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  وإلا إذا (cclauses
	   && (mask & (OMP_CLAUSE_MASK_1
		       << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_to_pragma_eol (parser);
      أرجع NULL_بشيا;
    }
  وإلا إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      location_t ploc = c_parser_peek_token (parser)->location;
      إذا (cclauses == عدم && strcmp (p, "masked") == 0)
	{
	  بشيا cclauses_buf[C_OMP_CLAUSE_SPLIT_كدي];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					if_p);
	  block = c_begin_omp_parallel ();
	  بشيا ret = c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					  if_p);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  إذا (ret == عدم)
	    أرجع ret;
	  /* masked does have just filter clause, but during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel masked don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel masked
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel masked taskloop simd lastprivate (x)  */
	  إذا (OMP_MASKED_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  أرجع stmt;
	}
      وإلا إذا (cclauses == عدم && strcmp (p, "master") == 0)
	{
	  بشيا cclauses_buf[C_OMP_CLAUSE_SPLIT_كدي];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					if_p, ploc);
	  block = c_begin_omp_parallel ();
	  بشيا ret = c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					  if_p, ploc);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  إذا (ret == عدم)
	    أرجع ret;
	  /* master doesn't have any clauses and during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel master don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel master
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel master taskloop simd lastprivate (x)  */
	  إذا (OMP_MASTER_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  أرجع stmt;
	}
      وإلا إذا (strcmp (p, "loop") == 0)
	{
	  بشيا cclauses_buf[C_OMP_CLAUSE_SPLIT_كدي];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  بشيا ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
					if_p);
	  stmt
	    = c_finish_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				     block);
	  إذا (ret == NULL_بشيا)
	    أرجع ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  أرجع stmt;
	}
      وإلا إذا (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, خطأ);
	  أرجع NULL_بشيا;
	}
      وإلا إذا (cclauses == عدم && strcmp (p, "sections") == 0)
	{
	  بشيا cclauses_buf[C_OMP_CLAUSE_SPLIT_كدي];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  block = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, mask, cclauses);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  أرجع stmt;
	}
    }
  وإلا إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, خطأ);
      أرجع NULL_بشيا;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_split_clauses (loc, OMP_PARALLEL, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL];
    }

  block = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = true;
  c_parser_statement (parser, if_p);
  stmt = c_finish_omp_parallel (loc, clauses, block);

  أرجع stmt;
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

ساكن بشيا
c_parser_omp_single (location_t loc, c_parser *parser, منطقي *if_p)
{
  بشيا stmt = make_كلي (OMP_SINGLE);
  SET_فرچ_LOCATION (stmt, loc);
  بشيا_TYPE (stmt) = void_type_كلي;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_MASK,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  أرجع add_stmt (stmt);
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

ساكن بشيا
c_parser_omp_scope (location_t loc, c_parser *parser, منطقي *if_p)
{
  بشيا stmt = make_كلي (OMP_SCOPE);
  SET_فرچ_LOCATION (stmt, loc);
  بشيا_TYPE (stmt) = void_type_كلي;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_MASK,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  أرجع add_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
ساكن بشيا
c_parser_omp_dispatch_body (c_parser *parser)
{
  بنية c_فرچ lhs, rhs, ret;
  location_t فرچ_loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_expression (parser, عدم, عدم);
  إذا (بشيا_CODE (lhs.درج) == CALL_فرچ)
    أرجع lhs.درج;

  location_t op_location = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    أرجع error_mark_كلي;

  /* Parse function name.  */
  إذا (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      أرجع error_mark_كلي;
    }
  فرچ_loc = c_parser_peek_token (parser)->location;
  بشيا id = c_parser_peek_token (parser)->درج;
  c_parser_consume_token (parser);
  إذا (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      أرجع error_mark_كلي;
    }

  rhs.درج = build_external_ref (فرچ_loc, id, true, &rhs.original_type);
  set_c_فرچ_source_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_expression_after_primary (
    parser, فرچ_LOC_OR_LOC (rhs.درج, فرچ_loc), rhs);
  إذا (بشيا_CODE (rhs.درج) != CALL_فرچ)
    {
      error_at (فرچ_LOC_OR_LOC (rhs.درج, فرچ_loc),
		"expected target-function call");
      أرجع error_mark_كلي;
    }

  /* Build assignment. */
  rhs = convert_lvalue_to_rvalue (فرچ_loc, rhs, true, true);
  ret.درج
    = build_modify_فرچ (op_location, lhs.درج, lhs.original_type, NOP_فرچ,
			 فرچ_loc, rhs.درج, rhs.original_type);
  ret.m_decimal = 0;
  set_c_فرچ_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  ret.original_code = MODIFY_فرچ;
  ret.original_type = عدم;
  أرجع ret.درج;
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

ساكن بشيا
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  بشيا stmt = make_كلي (OMP_DISPATCH);
  SET_فرچ_LOCATION (stmt, loc);
  بشيا_TYPE (stmt) = void_type_كلي;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_MASK,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  بشيا depend_clauses = NULL_بشيا;
  بشيا *depend_clauses_ptr = &depend_clauses;
  لكل (بشيا c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  إذا (depend_clauses != NULL_بشيا)
    {
      بشيا stmt = make_كلي (OMP_TASK);
      بشيا_TYPE (stmt) = void_كلي;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_بشيا;
      SET_فرچ_LOCATION (stmt, loc);
      add_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  بشيا dispatch_body = c_parser_omp_dispatch_body (parser);
  إذا (dispatch_body == error_mark_كلي)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_to_end_of_block_or_statement (parser);
      أرجع NULL_بشيا;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (بشيا_CODE (dispatch_body) == CALL_فرچ
	      || بشيا_CODE (dispatch_body) == MODIFY_فرچ);
  بشيا *dispatch_call = بشيا_CODE (dispatch_body) == MODIFY_فرچ
			  ? &بشيا_OPERAND (dispatch_body, 1)
			  : &dispatch_body;
  طالما (بشيا_CODE (*dispatch_call) == FLOAT_فرچ
	 || بشيا_CODE (*dispatch_call) == CONVERT_فرچ
	 || بشيا_CODE (*dispatch_call) == NOP_فرچ)
    dispatch_call = &بشيا_OPERAND (*dispatch_call, 0);
  *dispatch_call = build_call_فرچ_internal_loc (
    loc, IFN_GOMP_DISPATCH,
    بشيا_TYPE (بشيا_TYPE (CALL_فرچ_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  أرجع add_stmt (stmt);
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

ساكن بشيا
c_parser_omp_task (location_t loc, c_parser *parser, منطقي *if_p)
{
  بشيا clauses, block;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_MASK,
				      "#pragma omp task");

  block = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = true;
  c_parser_statement (parser, if_p);
  أرجع c_finish_omp_task (loc, clauses, block);
}

/* OpenMP 3.0:
   # pragma omp taskwait new-line

   OpenMP 5.0:
   # pragma omp taskwait taskwait-clause[optseq] new-line
*/

#define OMP_TASKWAIT_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن فراغ
c_parser_omp_taskwait (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  بشيا clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_MASK,
				"#pragma omp taskwait");

  إذا (clauses)
    {
      بشيا stmt = make_كلي (OMP_TASK);
      بشيا_TYPE (stmt) = void_كلي;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_بشيا;
      SET_فرچ_LOCATION (stmt, loc);
      add_stmt (stmt);
    }
  وإلا
    c_finish_omp_taskwait (loc);
}

/* OpenMP 3.1:
   # pragma omp taskyield new-line
*/

ساكن فراغ
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

ساكن بشيا
c_parser_omp_taskgroup (location_t loc, c_parser *parser, منطقي *if_p)
{
  بشيا clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_MASK,
					   "#pragma omp taskgroup");

  بشيا body = c_parser_omp_structured_block (parser, if_p);
  أرجع c_finish_omp_taskgroup (loc, body, clauses);
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

ساكن فراغ
c_parser_omp_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);
  بشيا clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_MASK,
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

ساكن منطقي
c_parser_omp_cancellation_point (c_parser *parser, تعداد pragma_context context)
{
  location_t loc = c_parser_peek_token (parser)->location;
  بشيا clauses;
  منطقي point_seen = خطأ;

  c_parser_consume_pragma (parser);
  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  point_seen = true;
	}
    }
  إذا (!point_seen)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_to_pragma_eol (parser);
      أرجع خطأ;
    }

  إذا (context != pragma_compound)
    {
      إذا (context == pragma_stmt)
	error_at (loc,
		  "%<#pragma %s%> may only be used in compound statements",
		  "omp cancellation point");
      وإلا
	c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, خطأ);
      أرجع true;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_POINT_CLAUSE_MASK,
				"#pragma omp cancellation point");

  c_finish_omp_cancellation_point (loc, clauses);
  أرجع true;
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

ساكن بشيا
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 حرف *p_name, omp_clause_mask mask, بشيا *cclauses,
			 منطقي *if_p)
{
  بشيا clauses, block, ret;

  strcat (p_name, " distribute");
  mask |= OMP_DISTRIBUTE_CLAUSE_MASK;

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      منطقي simd = خطأ;
      منطقي parallel = خطأ;

      إذا (strcmp (p, "simd") == 0)
	simd = true;
      وإلا
	parallel = strcmp (p, "parallel") == 0;
      إذا (parallel || simd)
	{
	  بشيا cclauses_buf[C_OMP_CLAUSE_SPLIT_كدي];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      إذا (simd)
		أرجع c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
					  if_p);
	      وإلا
		أرجع c_parser_omp_parallel (loc, parser, p_name, mask,
					      cclauses, if_p);
	    }
	  block = c_begin_compound_stmt (true);
	  إذا (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				     if_p);
	  وإلا
	    ret = c_parser_omp_parallel (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, true);
	  إذا (ret == عدم)
	    أرجع ret;
	  ret = make_كلي (OMP_DISTRIBUTE);
	  بشيا_TYPE (ret) = void_type_كلي;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
	  SET_فرچ_LOCATION (ret, loc);
	  add_stmt (ret);
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, خطأ);
      أرجع NULL_بشيا;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_split_clauses (loc, OMP_DISTRIBUTE, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
    }

  block = c_begin_compound_stmt (true);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, عدم,
			       if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  أرجع ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#define OMP_TEAMS_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_لمب_TEAMS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_THREAD_LIMIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

ساكن بشيا
c_parser_omp_teams (location_t loc, c_parser *parser,
		    حرف *p_name, omp_clause_mask mask, بشيا *cclauses,
		    منطقي *if_p)
{
  بشيا clauses, block, ret;

  strcat (p_name, " teams");
  mask |= OMP_TEAMS_CLAUSE_MASK;

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp (p, "distribute") == 0)
	{
	  بشيا cclauses_buf[C_OMP_CLAUSE_SPLIT_كدي];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_distribute (loc, parser, p_name, mask,
					    cclauses, if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, true);
	  إذا (ret == عدم)
	    أرجع ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_كلي (OMP_TEAMS);
	  بشيا_TYPE (ret) = void_type_كلي;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_فرچ_LOCATION (ret, loc);
	  أرجع add_stmt (ret);
	}
      وإلا إذا (strcmp (p, "loop") == 0)
	{
	  بشيا cclauses_buf[C_OMP_CLAUSE_SPLIT_كدي];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, true);
	  إذا (ret == عدم)
	    أرجع ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_كلي (OMP_TEAMS);
	  بشيا_TYPE (ret) = void_type_كلي;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_فرچ_LOCATION (ret, loc);
	  أرجع add_stmt (ret);
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, خطأ);
      أرجع NULL_بشيا;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_split_clauses (loc, OMP_TEAMS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
    }

  بشيا stmt = make_كلي (OMP_TEAMS);
  بشيا_TYPE (stmt) = void_type_كلي;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_end_compound_stmt (loc, block, true);
  SET_فرچ_LOCATION (stmt, loc);

  أرجع add_stmt (stmt);
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

ساكن بشيا
c_parser_omp_target_data (location_t loc, c_parser *parser, منطقي *if_p)
{
  إذا (flag_openmp)
    omp_requires_mask
      = (تعداد omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  بشيا clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_DATA_CLAUSE_MASK,
				"#pragma omp target data", خطأ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, خطأ);
  صحيح map_seen = 0;
  لكل (بشيا *pc = &clauses; *pc;)
    {
      إذا (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	بدل (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  حالة GOMP_MAP_TO:
	  حالة GOMP_MAP_ALWAYS_TO:
	  حالة GOMP_MAP_PRESENT_TO:
	  حالة GOMP_MAP_ALWAYS_PRESENT_TO:
	  حالة GOMP_MAP_FROM:
	  حالة GOMP_MAP_ALWAYS_FROM:
	  حالة GOMP_MAP_PRESENT_FROM:
	  حالة GOMP_MAP_ALWAYS_PRESENT_FROM:
	  حالة GOMP_MAP_TOFROM:
	  حالة GOMP_MAP_ALWAYS_TOFROM:
	  حالة GOMP_MAP_PRESENT_TOFROM:
	  حالة GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  حالة GOMP_MAP_ALLOC:
	  حالة GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    اكسر;
	  حالة GOMP_MAP_FIRSTPRIVATE_POINTER:
	  حالة GOMP_MAP_ALWAYS_POINTER:
	  حالة GOMP_MAP_ATTACH_DETACH:
	  حالة GOMP_MAP_ATTACH:
	    اكسر;
	  افتراضي:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    استمر;
	  }
      وإلا إذا (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_seen = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  إذا (map_seen != 3)
    {
      إذا (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      أرجع NULL_بشيا;
    }

  بشيا stmt = make_كلي (OMP_TARGET_DATA);
  بشيا_TYPE (stmt) = void_type_كلي;
  OMP_TARGET_DATA_CLAUSES (stmt) = clauses;
  keep_next_level ();
  بشيا block = c_begin_compound_stmt (true);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TARGET_DATA_BODY (stmt) = c_end_compound_stmt (loc, block, true);

  SET_فرچ_LOCATION (stmt, loc);
  أرجع add_stmt (stmt);
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

ساكن منطقي
c_parser_omp_target_update (location_t loc, c_parser *parser,
			    تعداد pragma_context context)
{
  إذا (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_to_pragma_eol (parser, خطأ);
      أرجع true;
    }

  بشيا clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_UPDATE_CLAUSE_MASK,
				"#pragma omp target update",
				/* finish_p = */ خطأ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  إذا (omp_find_clause (clauses, OMP_CLAUSE_TO) == NULL_بشيا
      && omp_find_clause (clauses, OMP_CLAUSE_FROM) == NULL_بشيا)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      أرجع خطأ;
    }

  إذا (flag_openmp)
    omp_requires_mask
      = (تعداد omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  بشيا stmt = make_كلي (OMP_TARGET_UPDATE);
  بشيا_TYPE (stmt) = void_type_كلي;
  OMP_TARGET_UPDATE_CLAUSES (stmt) = clauses;
  SET_فرچ_LOCATION (stmt, loc);
  add_stmt (stmt);
  أرجع خطأ;
}

/* OpenMP 4.5:
   # pragma omp target enter data target-data-clause[optseq] new-line  */

#define OMP_TARGET_ENTER_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن منطقي
c_parser_omp_target_enter_data (location_t loc, c_parser *parser,
				تعداد pragma_context context)
{
  منطقي data_seen = خطأ;
  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = true;
	}
    }
  إذا (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      أرجع خطأ;
    }

  إذا (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_to_pragma_eol (parser, خطأ);
      أرجع true;
    }

  إذا (flag_openmp)
    omp_requires_mask
      = (تعداد omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  بشيا clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_ENTER_DATA_CLAUSE_MASK,
				"#pragma omp target enter data", خطأ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, خطأ);
  صحيح map_seen = 0;
  لكل (بشيا *pc = &clauses; *pc;)
    {
      إذا (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	بدل (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  حالة GOMP_MAP_TO:
	  حالة GOMP_MAP_ALWAYS_TO:
	  حالة GOMP_MAP_PRESENT_TO:
	  حالة GOMP_MAP_ALWAYS_PRESENT_TO:
	  حالة GOMP_MAP_ALLOC:
	  حالة GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    اكسر;
	  حالة GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_TO);
	    map_seen = 3;
	    اكسر;
	  حالة GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_TO);
	    map_seen = 3;
	    اكسر;
	  حالة GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_TO);
	    map_seen = 3;
	    اكسر;
	  حالة GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_TO);
	    map_seen = 3;
	    اكسر;
	  حالة GOMP_MAP_FIRSTPRIVATE_POINTER:
	  حالة GOMP_MAP_ALWAYS_POINTER:
	  حالة GOMP_MAP_ATTACH_DETACH:
	  حالة GOMP_MAP_ATTACH:
	    اكسر;
	  افتراضي:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    استمر;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  إذا (map_seen != 3)
    {
      إذا (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      أرجع true;
    }

  بشيا stmt = make_كلي (OMP_TARGET_ENTER_DATA);
  بشيا_TYPE (stmt) = void_type_كلي;
  OMP_TARGET_ENTER_DATA_CLAUSES (stmt) = clauses;
  SET_فرچ_LOCATION (stmt, loc);
  add_stmt (stmt);
  أرجع true;
}

/* OpenMP 4.5:
   # pragma omp target exit data target-data-clause[optseq] new-line  */

#define OMP_TARGET_EXIT_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن منطقي
c_parser_omp_target_exit_data (location_t loc, c_parser *parser,
			       تعداد pragma_context context)
{
  منطقي data_seen = خطأ;
  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = true;
	}
    }
  إذا (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      أرجع خطأ;
    }

  إذا (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_to_pragma_eol (parser, خطأ);
      أرجع true;
    }

  إذا (flag_openmp)
    omp_requires_mask
      = (تعداد omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  بشيا clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_EXIT_DATA_CLAUSE_MASK,
				"#pragma omp target exit data", خطأ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_DATA);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_EXIT_DATA);
  c_omp_adjust_map_clauses (clauses, خطأ);
  صحيح map_seen = 0;
  لكل (بشيا *pc = &clauses; *pc;)
    {
      إذا (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	بدل (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  حالة GOMP_MAP_FROM:
	  حالة GOMP_MAP_ALWAYS_FROM:
	  حالة GOMP_MAP_PRESENT_FROM:
	  حالة GOMP_MAP_ALWAYS_PRESENT_FROM:
	  حالة GOMP_MAP_RELEASE:
	  حالة GOMP_MAP_DELETE:
	    map_seen = 3;
	    اكسر;
	  حالة GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_FROM);
	    map_seen = 3;
	    اكسر;
	  حالة GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_seen = 3;
	    اكسر;
	  حالة GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_FROM);
	    map_seen = 3;
	    اكسر;
	  حالة GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_seen = 3;
	    اكسر;
	  حالة GOMP_MAP_FIRSTPRIVATE_POINTER:
	  حالة GOMP_MAP_ALWAYS_POINTER:
	  حالة GOMP_MAP_ATTACH_DETACH:
	  حالة GOMP_MAP_DETACH:
	    اكسر;
	  افتراضي:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target exit data%> with map-type other "
		      "than %<from%>, %<tofrom%>, %<release%> or %<delete%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    استمر;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  إذا (map_seen != 3)
    {
      إذا (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      أرجع true;
    }

  بشيا stmt = make_كلي (OMP_TARGET_EXIT_DATA);
  بشيا_TYPE (stmt) = void_type_كلي;
  OMP_TARGET_EXIT_DATA_CLAUSES (stmt) = clauses;
  SET_فرچ_LOCATION (stmt, loc);
  add_stmt (stmt);
  أرجع true;
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

ساكن منطقي
c_parser_omp_target (c_parser *parser, تعداد pragma_context context, منطقي *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  بشيا *pc = عدم, stmt, block, body, clauses;

  إذا (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser);
      أرجع خطأ;
    }

  إذا (flag_openmp)
    omp_requires_mask
      = (تعداد omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      تعداد بشيا_code ccode = ERROR_MARK;

      إذا (strcmp (p, "teams") == 0)
	ccode = OMP_TEAMS;
      وإلا إذا (strcmp (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      وإلا إذا (strcmp (p, "simd") == 0)
	ccode = OMP_SIMD;
      إذا (ccode != ERROR_MARK)
	{
	  بشيا cclauses[C_OMP_CLAUSE_SPLIT_كدي];
	  حرف p_name[حجم ("#pragma omp target teams distribute "
			      "parallel for simd")];

	  c_parser_consume_token (parser);
	  strcpy (p_name, "#pragma omp target");
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      بشيا stmt;
	      بدل (ccode)
		{
		حالة OMP_TEAMS:
		  stmt = c_parser_omp_teams (loc, parser, p_name,
					     OMP_TARGET_CLAUSE_MASK,
					     cclauses, if_p);
		  اكسر;
		حالة OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_TARGET_CLAUSE_MASK,
						cclauses, if_p);
		  اكسر;
		حالة OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_TARGET_CLAUSE_MASK,
					    cclauses, if_p);
		  اكسر;
		افتراضي:
		  gcc_unreachable ();
		}
	      أرجع stmt != NULL_بشيا;
	    }
	  keep_next_level ();
	  بشيا block = c_begin_compound_stmt (true), ret;
	  بدل (ccode)
	    {
	    حالة OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_TARGET_CLAUSE_MASK, cclauses,
					if_p);
	      اكسر;
	    حالة OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_TARGET_CLAUSE_MASK, cclauses,
					   if_p);
	      اكسر;
	    حالة OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_TARGET_CLAUSE_MASK, cclauses,
				       if_p);
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }
	  block = c_end_compound_stmt (loc, block, true);
	  إذا (ret == NULL_بشيا)
	    أرجع خطأ;
	  إذا (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    لكل (بشيا c = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_لمب_TEAMS
		  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_THREAD_LIMIT)
		لكل (صحيح i = 0;
		     i <= (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_لمب_TEAMS); ++i)
		  إذا (OMP_CLAUSE_OPERAND (c, i)
		      && بشيا_CODE (OMP_CLAUSE_OPERAND (c, i)) != INTEGER_CST)
		    {
		      بشيا فرچ = OMP_CLAUSE_OPERAND (c, i);
		      بشيا tmp = create_tmp_var_raw (بشيا_TYPE (فرچ));
		      فرچ = build4 (TARGET_فرچ, بشيا_TYPE (فرچ), tmp,
				     فرچ, NULL_بشيا, NULL_بشيا);
		      add_stmt (فرچ);
		      OMP_CLAUSE_OPERAND (c, i) = فرچ;
		      بشيا tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
		      cclauses[C_OMP_CLAUSE_SPLIT_TARGET] = tc;
		    }
	  بشيا stmt = make_كلي (OMP_TARGET);
	  بشيا_TYPE (stmt) = void_type_كلي;
	  OMP_TARGET_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
	  c_omp_adjust_map_clauses (OMP_TARGET_CLAUSES (stmt), true);
	  OMP_TARGET_BODY (stmt) = block;
	  OMP_TARGET_COMBINED (stmt) = 1;
	  SET_فرچ_LOCATION (stmt, loc);
	  add_stmt (stmt);
	  pc = &OMP_TARGET_CLAUSES (stmt);
	  اذهب check_clauses;
	}
      وإلا إذا (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, خطأ);
	  أرجع خطأ;
	}
      وإلا إذا (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_target_data (loc, parser, if_p);
	  أرجع true;
	}
      وإلا إذا (strcmp (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  أرجع c_parser_omp_target_enter_data (loc, parser, context);
	}
      وإلا إذا (strcmp (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  أرجع c_parser_omp_target_exit_data (loc, parser, context);
	}
      وإلا إذا (strcmp (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  أرجع c_parser_omp_target_update (loc, parser, context);
	}
    }
  إذا (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, خطأ);
      أرجع خطأ;
    }

  stmt = make_كلي (OMP_TARGET);
  بشيا_TYPE (stmt) = void_type_كلي;

  clauses = c_parser_omp_all_clauses (parser, OMP_TARGET_CLAUSE_MASK,
				      "#pragma omp target", خطأ);
  لكل (بشيا c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
      {
	بشيا nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_SET_MAP_KIND (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_TARGET);
  clauses  = c_finish_omp_clauses (clauses, C_ORT_OMP_TARGET);
  c_omp_adjust_map_clauses (clauses, true);

  keep_next_level ();
  block = c_begin_compound_stmt (true);
  body = c_parser_omp_structured_block (parser, if_p);

  c_omp_scan_mapper_bindings (loc, &clauses, body);

  add_stmt (body);
  OMP_TARGET_CLAUSES (stmt) = clauses;
  pc = &OMP_TARGET_CLAUSES (stmt);
  OMP_TARGET_BODY (stmt) = c_end_compound_stmt (loc, block, true);

  SET_فرچ_LOCATION (stmt, loc);
  add_stmt (stmt);

check_clauses:
  طالما (*pc)
    {
      إذا (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	بدل (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  حالة GOMP_MAP_TO:
	  حالة GOMP_MAP_ALWAYS_TO:
	  حالة GOMP_MAP_PRESENT_TO:
	  حالة GOMP_MAP_ALWAYS_PRESENT_TO:
	  حالة GOMP_MAP_FROM:
	  حالة GOMP_MAP_ALWAYS_FROM:
	  حالة GOMP_MAP_PRESENT_FROM:
	  حالة GOMP_MAP_ALWAYS_PRESENT_FROM:
	  حالة GOMP_MAP_TOFROM:
	  حالة GOMP_MAP_ALWAYS_TOFROM:
	  حالة GOMP_MAP_PRESENT_TOFROM:
	  حالة GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  حالة GOMP_MAP_ALLOC:
	  حالة GOMP_MAP_PRESENT_ALLOC:
	  حالة GOMP_MAP_FIRSTPRIVATE_POINTER:
	  حالة GOMP_MAP_ALWAYS_POINTER:
	  حالة GOMP_MAP_POINTER:
	  حالة GOMP_MAP_ATTACH_DETACH:
	  حالة GOMP_MAP_ATTACH:
	    اكسر;
	  افتراضي:
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    استمر;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }
  cfun->has_omp_target = true;
  أرجع true;
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

ساكن فراغ
c_parser_omp_declare_simd (c_parser *parser, تعداد pragma_context context)
{
  c_token *token = c_parser_peek_token (parser);
  gcc_assert (token->type == CPP_NAME);
  بشيا kind = token->درج;
  gcc_assert (strcmp (IDENTIFIER_POINTER (kind), "simd") == 0
	      || strcmp (IDENTIFIER_POINTER (kind), "variant") == 0);

  auto_vec<c_token> clauses;
  طالما (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_EOF)
	{
	  c_parser_skip_to_pragma_eol (parser);
	  أرجع;
	}
      clauses.safe_تور (*token);
      c_parser_consume_token (parser);
    }
  clauses.safe_تور (*c_parser_peek_token (parser));
  c_parser_skip_to_pragma_eol (parser);

  طالما (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      إذا (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->درج != kind)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_POINTER (kind), IDENTIFIER_POINTER (kind));
	  أرجع;
	}
      c_parser_consume_pragma (parser);
      طالما (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_EOF)
	    {
	      c_parser_skip_to_pragma_eol (parser);
	      أرجع;
	    }
	  clauses.safe_تور (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_تور (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  memset (&eof_token, 0, حجم (eof_token));
  eof_token.type = CPP_EOF;
  clauses.safe_تور (eof_token);
  clauses.safe_تور (eof_token);

  بدل (context)
    {
    حالة pragma_external:
      إذا (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحيح ext = disable_extension_diagnostics ();
	  افعل
	    c_parser_consume_token (parser);
	  طالما (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, true, true, true, خطأ, true,
					 خطأ, عدم, &clauses);
	  restore_extension_diagnostics (ext);
	}
      وإلا
	c_parser_declaration_or_fndef (parser, true, true, true, خطأ, true,
				       خطأ, عدم, &clauses);
      اكسر;
    حالة pragma_struct:
    حالة pragma_param:
    حالة pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      اكسر;
    حالة pragma_compound:
      منطقي have_std_attrs;
      بشيا std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
      إذا (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      وإلا
	std_attrs = NULL_بشيا;
      إذا (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحيح ext = disable_extension_diagnostics ();
	  افعل
	    c_parser_consume_token (parser);
	  طالما (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  إذا (c_parser_next_tokens_start_declaration (parser)
	      || c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, true, true, true, true,
					     true, خطأ, عدم, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      اكسر;
	    }
	  restore_extension_diagnostics (ext);
	}
      وإلا إذا (c_parser_next_tokens_start_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, true, true, true, true, true,
					 خطأ, عدم, &clauses, have_std_attrs,
					 std_attrs);
	  اكسر;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      اكسر;
    افتراضي:
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

ساكن بشيا
c_parser_omp_context_selector (c_parser *parser, تعداد omp_tss_code set,
			       بشيا parms)
{
  بشيا ret = NULL_بشيا;
  افعل
    {
      بشيا selector;
      إذا (c_parser_next_token_is (parser, CPP_KEYWORD)
	  || c_parser_next_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->درج;
      وإلا
	{
	  c_parser_error (parser, "expected trait selector name");
	  أرجع error_mark_كلي;
	}
      تعداد omp_ts_code sel
	= omp_lookup_ts_code (set, IDENTIFIER_POINTER (selector));

      إذا (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_POINTER (selector),  omp_tss_map[set]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_بشيا, NULL_بشيا, ret);
	  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_balanced_token_sequence (parser);
	  إذا (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      استمر;
	    }
	  وإلا
	    اكسر;
	}

      c_parser_consume_token (parser);

      بشيا properties = NULL_بشيا;
      بشيا scoreval = NULL_بشيا;
      تعداد omp_tp_type property_kind = omp_ts_map[sel].tp_type;
      منطقي allow_score = omp_ts_map[sel].allow_score;
      بشيا t;

      إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  إذا (property_kind == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_POINTER (selector));
	      أرجع error_mark_كلي;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  إذا (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER (token->درج), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      بشيا score = c_parser_فرچ_no_commas (parser, عدم).درج;
	      parens2.skip_until_found_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      إذا (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[set]);
	      وإلا إذا (score != error_mark_كلي)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, خطأ, عدم);
		  إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (score))
		      || بشيا_CODE (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  وإلا إذا (بشيا_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  وإلا
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  بدل (property_kind)
	    {
	    حالة OMP_TRAIT_PROPERTY_ID:
	      إذا (c_parser_next_token_is (parser, CPP_KEYWORD)
		  || c_parser_next_token_is (parser, CPP_NAME))
		{
		  بشيا prop = c_parser_peek_token (parser)->درج;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_بشيا,
						    properties);
		}
	      وإلا
		{
		  c_parser_error (parser, "expected identifier");
		  أرجع error_mark_كلي;
		}
	      اكسر;
	    حالة OMP_TRAIT_PROPERTY_NAME_LIST:
	      افعل
		{
		  بشيا prop = OMP_TP_NAMELIST_كلي;
		  بشيا درج = NULL_بشيا;
		  إذا (c_parser_next_token_is (parser, CPP_KEYWORD)
		      || c_parser_next_token_is (parser, CPP_NAME))
		    {
		      درج = c_parser_peek_token (parser)->درج;
		      c_parser_consume_token (parser);
		    }
		  وإلا إذا (c_parser_next_token_is (parser, CPP_STRING))
		    درج = c_parser_string_literal (parser, خطأ,
						     خطأ).درج;
		  وإلا
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      أرجع error_mark_كلي;
		    }

		  properties = make_trait_property (prop, درج, properties);

		  إذا (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  وإلا
		    اكسر;
		}
	      طالما (1);
	      اكسر;
	    حالة OMP_TRAIT_PROPERTY_DEV_لمب_فرچ:
	    حالة OMP_TRAIT_PROPERTY_BOOL_فرچ:
	      {
		c_فرچ texpr = c_parser_فرچ_no_commas (parser, عدم);
		texpr = convert_lvalue_to_rvalue (token->location, texpr,
						  true, true);
		t = texpr.درج;
	      }
	      إذا (t == error_mark_كلي)
		أرجع error_mark_كلي;
	      mark_exp_read (t);
	      إذا (property_kind == OMP_TRAIT_PROPERTY_BOOL_فرچ)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_كلي);
		  إذا (t == error_mark_كلي)
		    أرجع error_mark_كلي;
		}
	      وإلا إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  أرجع error_mark_كلي;
		}
	      t = c_fully_fold (t, خطأ, عدم);
	      properties = make_trait_property (NULL_بشيا, t, properties);
	      اكسر;
	    حالة OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      إذا (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  إذا (parms == NULL_بشيا)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      أرجع error_mark_كلي;
		    }
		  بشيا c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_MASK,
						"simd", true, 2);
		  c = c_omp_declare_simd_clauses_to_numbers (parms
							     == error_mark_كلي
							     ? NULL_بشيا : parms,
							     c);
		  properties = c;
		}
	      وإلا إذا (sel == OMP_TRAIT_IMPLEMENTATION_REQUIRES)
		{
		  /* FIXME: The "requires" selector was added in OpenMP 5.1.
		     Currently only the now-deprecated syntax
		     from OpenMP 5.0 is supported.  */
		  sorry_at (token->location,
			    "%<requires%> selector is not supported yet");
		  أرجع error_mark_كلي;
		}
	      وإلا
		gcc_unreachable ();
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }

	  parens.skip_until_found_close (parser);
	  properties = nreverse (properties);
	}
      وإلا إذا (property_kind != OMP_TRAIT_PROPERTY_NONE
	       && property_kind != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_kind != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  أرجع error_mark_كلي;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  طالما (1);

  أرجع nreverse (ret);
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

ساكن بشيا
c_parser_omp_context_selector_specification (c_parser *parser, بشيا parms)
{
  بشيا ret = NULL_بشيا;
  افعل
    {
      ثابت حرف *setp = "";
      إذا (c_parser_next_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      تعداد omp_tss_code set = omp_lookup_tss_code (setp);

      إذا (set == OMP_TRAIT_SET_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  أرجع error_mark_كلي;
	}

      c_parser_consume_token (parser);

      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	أرجع error_mark_كلي;

      matching_braces braces;
      إذا (!braces.require_open (parser))
	أرجع error_mark_كلي;

      بشيا selectors = c_parser_omp_context_selector (parser, set, parms);
      إذا (selectors == error_mark_كلي)
	{
	  c_parser_skip_to_closing_brace (parser);
	  ret = error_mark_كلي;
	}
      وإلا إذا (ret != error_mark_كلي)
	ret = make_trait_set_selector (set, selectors, ret);

      braces.require_close (parser);

      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  طالما (1);

  إذا (ret == error_mark_كلي)
    أرجع ret;
  أرجع nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

ساكن فراغ
c_finish_omp_declare_variant (c_parser *parser, بشيا fndecl, بشيا parms)
{
  matching_parens parens;
  إذا (!parens.require_open (parser))
    {
     fail:
      c_parser_skip_to_pragma_eol (parser, خطأ);
      أرجع;
    }

  إذا (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      اذهب fail;
    }

  c_token *token = c_parser_peek_token (parser);
  بشيا variant = lookup_name (token->درج);

  إذا (variant == NULL_بشيا)
    {
      undeclared_variable (token->location, token->درج);
      variant = error_mark_كلي;
    }
  وإلا إذا (بشيا_CODE (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_كلي;
    }
  وإلا إذا (fndecl_built_in_p (variant)
	   && (strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			"__builtin_", strlen ("__builtin_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__sync_", strlen ("__sync_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__atomic_", strlen ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_كلي;
    }
  وإلا إذا (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_كلي;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  بشيا append_حجوجي_بشيا = NULL_بشيا;
  بشيا append_حجوجي_last;
  vec<بشيا> adjust_حجوجي_list = vNULL;
  منطقي has_match = خطأ, has_adjust_حجوجي = خطأ;
  location_t adjust_حجوجي_loc = UNKNOWN_LOCATION;
  location_t append_حجوجي_loc = UNKNOWN_LOCATION;
  location_t match_loc = UNKNOWN_LOCATION;
  بشيا need_device_ptr_list = NULL_بشيا;
  بشيا ctx = error_mark_كلي;

  افعل
    {
      إذا (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ثابت حرف *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      إذا (c_parser_next_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);

      تعداد clause
      {
	match,
	adjust_حجوجي,
	append_حجوجي
      } ccode;

      إذا (strcmp (clause, "match") == 0)
	{
	  ccode = match;
	  match_loc = loc;
	}
      وإلا إذا (strcmp (clause, "adjust_args") == 0)
	{
	  ccode = adjust_حجوجي;
	  adjust_حجوجي_loc = loc;
	}
      وإلا إذا (strcmp (clause, "append_args") == 0)
	{
	  ccode = append_حجوجي;
	  append_حجوجي_loc = loc;
	}
      وإلا
	{
	  c_parser_error (parser, "expected %<match%>, %<adjust_args%> or "
				  "%<append_args%> clause");
	  اذهب fail;
	}

      c_parser_consume_token (parser);

      إذا (!parens.require_open (parser))
	اذهب fail;

      إذا (parms == NULL_بشيا)
	parms = error_mark_كلي;

      إذا (ccode == match)
	{
	  إذا (has_match)
	    error_at (match_loc, "too many %<match%> clauses");
	  has_match = true;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  إذا (ctx == error_mark_كلي)
	    اذهب fail;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  إذا (ctx != error_mark_كلي
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      بشيا outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      وإلا إذا (ccode == adjust_حجوجي)
	{
	  has_adjust_حجوجي = true;
	  إذا (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      ثابت حرف *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
	      إذا (strcmp (p, "need_device_ptr") == 0
		  || strcmp (p, "nothing") == 0)
		{
		  c_parser_consume_token (parser); // need_device_ptr
		  c_parser_consume_token (parser); // :

		  loc = c_parser_peek_token (parser)->location;
		  بشيا list
		    = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ERROR,
						  NULL_بشيا);

		  بشيا arg;
		  إذا (variant != error_mark_كلي)
		    لكل (بشيا c = list; c != NULL_بشيا; c = بشيا_CHAIN (c))
		      {
			بشيا decl = بشيا_PURPOSE (c);
			location_t arg_loc = فرچ_LOCATION (بشيا_درج (c));
			صحيح idx;
			لكل (arg = parms, idx = 0; arg != عدم;
			     arg = بشيا_CHAIN (arg), idx++)
			  إذا (arg == decl)
			    اكسر;
			إذا (arg == NULL_بشيا)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    اذهب fail;
			  }
			إذا (adjust_حجوجي_list.contains (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    اذهب fail;
			  }
			إذا (strcmp (p, "need_device_ptr") == 0
			    && بشيا_CODE (بشيا_TYPE (arg)) != POINTER_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    اذهب fail;
			  }
			adjust_حجوجي_list.safe_تور (arg);
			إذا (strcmp (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_بشيا_list (
				NULL_بشيا,
				build_int_cst (
				  integer_type_كلي,
				  idx))); // Store 0-based argument index,
					  // as in gimplify_call_expr
			  }
		      }
		}
	      وإلا
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %<nothing%> or %<need_device_ptr%>");
		  إذا (strcmp (p, "need_device_addr") == 0)
		    inform (c_parser_peek_token (parser)->location,
			    "%<need_device_addr%> is not valid for C");
		  اذهب fail;
		}
	    }
	  وإلا
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected %<nothing%> or %<need_device_ptr%> "
			"followed by %<:%>");
	      اذهب fail;
	    }
	}
      وإلا إذا (ccode == append_حجوجي)
	{
	  إذا (append_حجوجي_بشيا)
	    {
	      error_at (append_حجوجي_loc, "too many %qs clauses", "append_args");
	      append_حجوجي_بشيا = NULL_بشيا;
	    }
	  افعل
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      إذا (!c_parser_next_token_is (parser, CPP_NAME)
		  || strcmp ("interop",
			     IDENTIFIER_POINTER (
			       c_parser_peek_token (parser)->درج)))
		{
		  error_at (loc, "expected %<interop%>");
		  اذهب fail;
		}
	      c_parser_consume_token (parser);

	      إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		اذهب fail;
	      منطقي target = خطأ;
	      منطقي targetsync = خطأ;
	      بشيا prefer_type_بشيا = NULL_بشيا;
	      إذا (!c_parser_omp_clause_init_modifiers (parser, &target,
						       &targetsync,
						       &prefer_type_بشيا)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		اذهب fail;
	      إذا (!target && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      بشيا t = build_بشيا_list (target ? boolean_true_كلي
					       : boolean_false_كلي,
					targetsync ? boolean_true_كلي
						   : boolean_false_كلي);
	      t = build1_loc (loc, NOP_فرچ, void_type_كلي, t);
	      t = build_بشيا_list (t, prefer_type_بشيا);
	      إذا (append_حجوجي_بشيا)
		{
		  بشيا_CHAIN (append_حجوجي_last) = t;
		  append_حجوجي_last = t;
		}
	      وإلا
		append_حجوجي_بشيا = append_حجوجي_last = t;
	      إذا (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		اكسر;
	      إذا (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		اذهب fail;
	    }
	  طالما (true);
	}

      parens.require_close (parser);
  } طالما (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL));
  إذا (variant != error_mark_كلي && !has_match)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_كلي;
    }
  c_parser_skip_to_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  إذا (variant == error_mark_كلي || ctx == error_mark_كلي)
    /* Previously diagnosed error.  */
    أرجع;

  إذا ((has_adjust_حجوجي || append_حجوجي_بشيا)
      && !omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_حجوجي ? adjust_حجوجي_loc : append_حجوجي_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_حجوجي ? "adjust_args" : "append_args");
      أرجع;
    }

  إذا (!omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      بشيا base_type = بشيا_TYPE (fndecl);
      بشيا variant_type = بشيا_TYPE (variant);
      منطقي unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_بشيا
	   && !TYPE_NO_NAMED_حجوجي_STDARG_P (variant_type));

      إذا (append_حجوجي_بشيا
	  && TYPE_ARG_TYPES (base_type) == NULL_بشيا
	  && !TYPE_NO_NAMED_حجوجي_STDARG_P (base_type))
	{
	  /* The base function is a pre-C23 unprototyped function.  Without
	     a prototype, we don't know the offset where the append_args go.
	     That offset needs to be stored with the append_args in the
	     variant function attributes, so we cannot presently handle
	     this case.  */
	  sorry_at (append_حجوجي_loc,
		    "%<append_args%> with unprototyped base function "
		    "is not supported yet");
	  inform (DECL_SOURCE_LOCATION (fndecl),
		  "base function %qD declared here", fndecl);
	  أرجع;
	}
      وإلا إذا (append_حجوجي_بشيا)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  صحيح nappend_حجوجي = 0;
	  صحيح nbase_حجوجي = 0;
	  لكل (بشيا t = TYPE_ARG_TYPES (base_type);
	       t && بشيا_درج (t) != void_type_كلي; t = بشيا_CHAIN (t))
	    nbase_حجوجي++;
	  لكل (بشيا t = append_حجوجي_بشيا; t; t = بشيا_CHAIN (t))
	    nappend_حجوجي++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_حجوجي_بشيا = build_بشيا_list (build_int_cst (integer_type_كلي,
							     nbase_حجوجي),
					      append_حجوجي_بشيا);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  إذا (!unprototyped_variant)
	    {
	      بشيا حجوجي = TYPE_ARG_TYPES (variant_type);
	      لكل (صحيح i = 0; حجوجي && i < nbase_حجوجي;
		   i++, حجوجي = بشيا_CHAIN (حجوجي))
		;
	      لكل (صحيح i = 0; i < nappend_حجوجي; i++, حجوجي = بشيا_CHAIN (حجوجي))
		إذا (!حجوجي || !c_omp_interop_t_p (بشيا_درج (حجوجي)))
		  {
		    error_at (DECL_SOURCE_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_حجوجي + i + 1, variant);
		    inform (append_حجوجي_loc,
			    "%<append_args%> specified here");
		    أرجع;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  بشيا حجوجي = TYPE_ARG_TYPES (base_type);
	  بشيا newargs = NULL_بشيا;
	  بشيا lastarg = NULL_بشيا;
	  لكل (صحيح j = 0; j < nbase_حجوجي; j++, حجوجي = بشيا_CHAIN (حجوجي))
	    {
	      بشيا t = بشيا_cons (بشيا_PURPOSE (حجوجي),
				  بشيا_درج (حجوجي), NULL_بشيا);
	      إذا (lastarg)
		بشيا_CHAIN (lastarg) = t;
	      وإلا
		newargs = t;
	      lastarg = t;
	    }
	  بشيا type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? بشيا_TYPE (type) : pointer_sized_int_كلي;
	  لكل (صحيح j = 0; j < nappend_حجوجي; j++)
	    {
	      بشيا t = بشيا_cons (NULL_بشيا, type, NULL_بشيا);
	      إذا (lastarg)
		بشيا_CHAIN (lastarg) = t;
	      وإلا
		newargs = t;
	      lastarg = t;
	    }
	  بشيا_CHAIN (lastarg) = حجوجي;

	  /* Temporarily stuff newargs into the original base_type.  */
	  بشيا saveargs = TYPE_ARG_TYPES (base_type);
	  TYPE_ARG_TYPES (base_type) = newargs;
	  منطقي fail = !comptypes (base_type, variant_type);
	  TYPE_ARG_TYPES (base_type) = saveargs;

	  إذا (fail)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      أرجع;
	    }
	  وإلا إذا (unprototyped_variant)
	    /* If we've got an unprototyped variant, copy the transformed
	       base arg types to the variant.  This is needed later by
	       modify_call_for_omp_dispatch.  */
	    TYPE_ARG_TYPES (variant_type) = newargs;
	}
      وإلا  /* No append_args present.  */
	{
	  إذا (!comptypes (base_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      أرجع;
	    }
	  وإلا إذا (TYPE_ARG_TYPES (variant_type) == NULL_بشيا
		   && !TYPE_NO_NAMED_حجوجي_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (base_type) != NULL_بشيا)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (base_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_USED (variant) = 1;
  بشيا construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (match_loc, variant, construct);
  إذا (omp_context_selector_matches (ctx, NULL_بشيا, خطأ))
    {
      بشيا attr = بشيا_cons (get_identifier ("omp declare variant base"),
			     build_بشيا_list (variant, ctx),
			     DECL_ATTRIBUTES (fndecl));
      DECL_ATTRIBUTES (fndecl) = attr;
    }

  إذا (need_device_ptr_list || append_حجوجي_بشيا)
    {
      بشيا variant_decl = بشيا_strip_nop_conversions (variant);
      بشيا t = build_بشيا_list (need_device_ptr_list,
				NULL_بشيا /* need_device_addr */);
      بشيا_CHAIN (t) = append_حجوجي_بشيا;
      DECL_ATTRIBUTES (variant_decl)
	= بشيا_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_ATTRIBUTES (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

ساكن فراغ
c_finish_omp_declare_simd (c_parser *parser, بشيا fndecl, بشيا parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  إذا (clauses.exists () && clauses[0].type == CPP_EOF)
    أرجع;
  ثابت حرف *kind = "simd";
  إذا (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    kind = IDENTIFIER_POINTER (clauses[0].درج);
  gcc_assert (strcmp (kind, "simd") == 0 || strcmp (kind, "variant") == 0);
  إذا (fndecl == NULL_بشيا || بشيا_CODE (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      أرجع;
    }
  إذا (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      أرجع;
    }
  إذا (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", kind);
      أرجع;
    }

  إذا (parms == NULL_بشيا)
    parms = DECL_ARGUMENTS (fndecl);

  unsigned صحيح tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);

  parser->tokens = clauses.address ();
  parser->tokens_avail = clauses.length ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  طالما (parser->tokens_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      kind = IDENTIFIER_POINTER (token->درج);
      c_parser_consume_token (parser);
      parser->in_pragma = true;

      إذا (strcmp (kind, "simd") == 0)
	{
	  بشيا c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_MASK,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_to_numbers (parms, c);
	  إذا (c != NULL_بشيا)
	    c = بشيا_cons (NULL_بشيا, c, NULL_بشيا);
	  c = build_بشيا_list (get_identifier ("omp declare simd"), c);
	  بشيا_CHAIN (c) = DECL_ATTRIBUTES (fndecl);
	  DECL_ATTRIBUTES (fndecl) = c;
	}
      وإلا
	{
	  gcc_assert (strcmp (kind, "variant") == 0);
	  c_finish_omp_declare_variant (parser, fndecl, parms);
	}
    }

  parser->tokens = &parser->tokens_buf[0];
  parser->tokens_avail = tokens_avail;
  إذا (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#إذا !defined (NO_DOT_IN_LABEL)
#define JOIN_STR "."
#وإلاإذا !defined (NO_DOLLAR_IN_LABEL)
#define JOIN_STR "$"
#وإلا
#define JOIN_STR "_"
#endif

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
ساكن بشيا
omp_start_variant_function (c_declarator *declarator, بشيا ctx)
{
  c_declarator *id = declarator;
  طالما (id->kind != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  بشيا name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  أرجع name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
ساكن فراغ
omp_finish_variant_function (بشيا decl, بشيا base_name, بشيا ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  بشيا base_decl = lookup_name (base_name);
  إذا (base_decl == error_mark_كلي)
    base_decl = NULL_بشيا;
  إذا (!base_decl)
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_POINTER (base_name));
      أرجع;
    }

  إذا (!comptypes (بشيا_TYPE (decl), بشيا_TYPE (base_decl)))
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", base_decl);
      inform (DECL_SOURCE_LOCATION (base_decl),
	      "%qE declared here", base_decl);
      أرجع;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_SOURCE_LOCATION (decl),
				   base_decl, ctx);
  بشيا construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (DECL_SOURCE_LOCATION (decl), decl, construct);
  بشيا attrs = DECL_ATTRIBUTES (base_decl);
  بشيا match_loc_كلي
    = maybe_wrap_with_location (integer_zero_كلي,
				DECL_SOURCE_LOCATION (base_decl));
  بشيا loc_كلي = بشيا_cons (match_loc_كلي, integer_zero_كلي,
			     build_بشيا_list (match_loc_كلي,
					      integer_zero_كلي));
  attrs = بشيا_cons (get_identifier ("omp declare variant base"),
		     بشيا_cons (decl, ctx, loc_كلي), attrs);
  DECL_ATTRIBUTES (base_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  بشيا_PUBLIC (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

منطقي
c_maybe_parse_omp_decl (بشيا decl, بشيا d)
{
  gcc_assert (بشيا_CODE (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
  c_token *first = toks->address ();
  c_token *last = first + toks->length ();
  ثابت حرف *directive[3] = {};
  لكل (صحيح j = 0; j < 3; j++)
    {
      بشيا id = NULL_بشيا;
      إذا (first + j == last)
	اكسر;
      إذا (first[j].type == CPP_NAME)
	id = first[j].درج;
      وإلا إذا (first[j].type == CPP_KEYWORD)
	id = ridpointers[(صحيح) first[j].keyword];
      وإلا
	اكسر;
      directive[j] = IDENTIFIER_POINTER (id);
    }
  ثابت c_omp_directive *dir = عدم;
  إذا (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  إذا (dir == عدم)
    {
      error_at (first->location,
		"unknown OpenMP directive name in "
		"%qs attribute argument", "omp::decl");
      أرجع خطأ;
    }
  إذا (dir->id != PRAGMA_OMP_THREADPRIVATE
      && dir->id != PRAGMA_OMP_GROUPPRIVATE
      && dir->id != PRAGMA_OMP_ALLOCATE
      && (dir->id != PRAGMA_OMP_DECLARE
	  || strcmp (directive[1], "target") != 0))
    أرجع خطأ;

  إذا (!flag_openmp && !dir->simd)
    أرجع true;

  c_parser *parser = the_parser;
  unsigned صحيح tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);
  toks = عدم;
  vec_safe_reserve (toks, last - first + 2, true);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_kind = pragma_kind (dir->id);
  tok.location = first->location;
  toks->quick_تور (tok);
  طالما (++first < last)
    toks->quick_تور (*first);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_تور (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_تور (tok);
  parser->in_omp_decl_attribute = decl;
  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = toks->length ();
  c_parser_pragma (parser, pragma_external, عدم, NULL_بشيا);
  parser->in_omp_decl_attribute = NULL_بشيا;
  أرجع true;
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

ساكن فراغ
c_parser_omp_declare_target (c_parser *parser)
{
  بشيا clauses = NULL_بشيا;
  صحيح device_type = 0;
  منطقي indirect = خطأ;
  منطقي only_device_type_or_indirect = true;
  إذا (flag_openmp)
    omp_requires_mask
      = (تعداد omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);
  إذا (c_parser_next_token_is (parser, CPP_NAME)
      || (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp declare target");
  وإلا إذا (parser->in_omp_decl_attribute
	   || c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      clauses = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					      clauses);
      clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
      c_parser_skip_to_pragma_eol (parser);
    }
  وإلا
    {
      warning_at (c_parser_peek_token (parser)->location,
		  OPT_Wdeprecated_openmp,
		  "use of %<omp declare target%> as a synonym for "
		  "%<omp begin declare target%> has been deprecated since "
		  "OpenMP 5.2");
      منطقي attr_syntax = parser->in_omp_attribute_pragma != عدم;
      c_parser_skip_to_pragma_eol (parser);
      c_omp_declare_target_attr attr = { attr_syntax, -1, 0 };
      vec_safe_تور (current_omp_declare_target_attribute, attr);
      أرجع;
    }
  لكل (بشيا c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_فرچ (c));
    }
  لكل (بشيا c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	استمر;
      بشيا t = OMP_CLAUSE_DECL (c), id;
      بشيا at1 = lookup_attribute ("omp declare target", DECL_ATTRIBUTES (t));
      بشيا at2 = lookup_attribute ("omp declare target link",
				   DECL_ATTRIBUTES (t));
      only_device_type_or_indirect = خطأ;
      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::swap (at1, at2);
	}
      وإلا
	id = get_identifier ("omp declare target");
      إذا (at2)
	{
	  إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	  وإلا إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL
		   || درج_member (get_identifier ("local"), بشيا_درج (at2)))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<local%> clauses", t);
	  وإلا
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<to%> or %<enter%> clauses", t);
	  استمر;
	}
      إذا (!at1)
	{
	  DECL_ATTRIBUTES (t) = بشيا_cons (id, NULL_بشيا, DECL_ATTRIBUTES (t));
	  إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    بشيا_درج (DECL_ATTRIBUTES (t))
	      = بشيا_cons (NULL_بشيا, get_identifier ("local"),
			   بشيا_درج (DECL_ATTRIBUTES (t)));

	  إذا (بشيا_CODE (t) != FUNCTION_DECL && !is_global_var (t))
	    استمر;

	  symtab_كلي *كلي = symtab_كلي::get (t);
	  إذا (كلي != عدم)
	    {
	      كلي->offloadable = 1;
	      إذا (ENABLE_OFFLOADING)
		{
		  g->have_offload = true;
		  إذا (is_a <varpool_كلي *> (كلي)
		      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_LOCAL)
		    vec_safe_تور (offload_vars, t);
		}
	    }
	}
      وإلا
	{
	  منطقي saw_local = درج_member (get_identifier ("local"),
					 بشيا_درج (at1));
	  إذا (saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	      استمر;
	    }
	  وإلا إذا (!saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      استمر;
	    }
	}
      إذا (بشيا_CODE (t) != FUNCTION_DECL)
	استمر;
      إذا ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  بشيا at3 = lookup_attribute ("omp declare target host",
				       DECL_ATTRIBUTES (t));
	  إذا (at3 == NULL_بشيا)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_ATTRIBUTES (t)
		= بشيا_cons (id, NULL_بشيا, DECL_ATTRIBUTES (t));
	    }
	}
      إذا ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  بشيا at3 = lookup_attribute ("omp declare target nohost",
				       DECL_ATTRIBUTES (t));
	  إذا (at3 == NULL_بشيا)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_ATTRIBUTES (t)
		= بشيا_cons (id, NULL_بشيا, DECL_ATTRIBUTES (t));
	    }
	}
      إذا (indirect)
	{
	  بشيا at4 = lookup_attribute ("omp declare target indirect",
				       DECL_ATTRIBUTES (t));
	  إذا (at4 == NULL_بشيا)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_ATTRIBUTES (t)
		= بشيا_cons (id, NULL_بشيا, DECL_ATTRIBUTES (t));
	    }
	}
    }
  إذا ((device_type || indirect) && only_device_type_or_indirect)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  إذا (indirect && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
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

ساكن فراغ
c_parser_omp_begin (c_parser *parser)
{
  ثابت حرف *p = "";
  c_parser_consume_pragma (parser);
  إذا (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
  إذا (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      إذا (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  منطقي attr_syntax = parser->in_omp_attribute_pragma != عدم;
	  بشيا clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp begin declare target");
	  صحيح device_type = 0;
	  صحيح indirect = 0;
	  لكل (بشيا c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
	      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
		indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_فرچ (c));
	    }
	  c_omp_declare_target_attr attr = { attr_syntax, device_type,
					     indirect };
	  vec_safe_تور (current_omp_declare_target_attribute, attr);
	}
      وإلا إذا (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  ثابت حرف *clause = "";
	  matching_parens parens;
	  location_t match_loc = c_parser_peek_token (parser)->location;
	  إذا (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  إذا (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      بشيا id = c_parser_peek_token (parser)->درج;
	      clause = IDENTIFIER_POINTER (id);
	    }
	  إذا (strcmp (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_to_pragma_eol (parser);
	      أرجع;
	    }

	  c_parser_consume_token (parser);

	  إذا (!parens.require_open (parser))
	    {
	      c_parser_skip_to_pragma_eol (parser, خطأ);
	      أرجع;
	    }

	  بشيا ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_بشيا);
	  إذا (ctx != error_mark_كلي)
	    ctx = omp_check_context_selector (match_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  إذا (ctx != error_mark_كلي
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      بشيا outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  إذا (ctx == error_mark_كلي
	      || !omp_context_selector_matches (ctx, NULL_بشيا, خطأ, true))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_to_pragma_eol (parser, خطأ);
	      c_parser_skip_to_pragma_omp_end_declare_variant (parser);
	      أرجع;
	    }
	  وإلا
	    {
	      منطقي attr_syntax = parser->in_omp_attribute_pragma != عدم;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_safe_تور (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_to_pragma_eol (parser);
	}
      وإلا
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser, خطأ);
	}
    }
  وإلا إذا (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      منطقي attr_syntax = parser->in_omp_attribute_pragma != عدم;
      c_parser_omp_assumption_clauses (parser, خطأ);
      بنية c_omp_begin_assumes_data a = { attr_syntax };
      vec_safe_تور (current_omp_begin_assumes, a);
    }
  وإلا
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

ساكن فراغ
c_parser_omp_end (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ثابت حرف *p = "";
  c_parser_consume_pragma (parser);
  إذا (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
  إذا (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      إذا (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  منطقي attr_syntax = parser->in_omp_attribute_pragma != عدم;
	  c_parser_skip_to_pragma_eol (parser);
	  إذا (!vec_safe_length (current_omp_declare_target_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  وإلا
	    {
	      c_omp_declare_target_attr
		a = current_omp_declare_target_attribute->چرو ();
	      إذا (a.attr_syntax != attr_syntax)
		{
		  إذا (a.attr_syntax)
		    error_at (loc,
			      "%qs in attribute syntax terminated "
			      "with %qs in pragma syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		  وإلا
		    error_at (loc,
			      "%qs in pragma syntax terminated "
			      "with %qs in attribute syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		}
	    }
	}
      وإلا إذا (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  منطقي attr_syntax = parser->in_omp_attribute_pragma != عدم;
	  c_parser_skip_to_pragma_eol (parser);
	  إذا (!vec_safe_length (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  وإلا
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->چرو ();
	      إذا (a.attr_syntax != attr_syntax)
		{
		  إذا (a.attr_syntax)
		    error_at (loc,
			      "%<begin declare variant%> in attribute syntax "
			      "terminated with "
			      "%<end declare variant%> in pragma syntax");
		  وإلا
		    error_at (loc,
			      "%<begin declare variant%> in pragma syntax "
			      "terminated with "
			      "%<end declare variant%> in attribute syntax");
		}
	    }
	}
      وإلا
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser);
	  أرجع;
	}
    }
  وإلا إذا (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      منطقي attr_syntax = parser->in_omp_attribute_pragma != عدم;
      c_parser_skip_to_pragma_eol (parser);
      إذا (!vec_safe_length (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      وإلا
	{
	  c_omp_begin_assumes_data
	    a = current_omp_begin_assumes->چرو ();
	  إذا (a.attr_syntax != attr_syntax)
	    {
	      إذا (a.attr_syntax)
		error_at (loc,
			  "%qs in attribute syntax terminated "
			  "with %qs in pragma syntax",
			  "begin assumes", "end assumes");
	      وإلا
		error_at (loc,
			  "%qs in pragma syntax terminated "
			  "with %qs in attribute syntax",
			  "begin assumes", "end assumes");
	    }
	}
    }
  وإلا
    {
      c_parser_error (parser, "expected %<declare%> or %<assumes%>");
      c_parser_skip_to_pragma_eol (parser);
    }
}

/* OpenMP 5.0
   #pragma omp declare mapper ([mapper-identifier :] type var) \
			      [clause [ [,] clause ] ... ] new-line  */

ساكن فراغ
c_parser_omp_declare_mapper (c_parser *parser, تعداد pragma_context context)
{
  بشيا type, mapper_name = NULL_بشيا, var = NULL_بشيا, stmt, stmtlist;
  بشيا maplist = NULL_بشيا, mapper_id, mapper_decl, t;
  c_token *token;

  إذا (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare mapper%> not at file or block scope");
      اذهب fail;
    }

  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    اذهب fail;

  token = c_parser_peek_token (parser);

  إذا (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      بدل (token->type)
	{
	حالة CPP_NAME:
	  mapper_name = token->درج;
	  c_parser_consume_token (parser);
	  اكسر;
	حالة CPP_KEYWORD:
	  إذا (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_بشيا;
	      c_parser_consume_token (parser);
	      اكسر;
	    }
	  /* Fallthrough.  */
	افتراضي:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_to_pragma_eol (parser, خطأ);
	  أرجع;
	}

      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	اذهب fail;
    }

  mapper_id = c_omp_mapper_id (mapper_name);
  mapper_decl = c_omp_mapper_decl (mapper_id);

  {
    location_t loc = c_parser_peek_token (parser)->location;
    بنية c_type_name *ctype = c_parser_type_name (parser);
    type = groktypename (ctype, عدم, عدم);
    إذا (type == error_mark_كلي)
      اذهب fail;
    إذا (!RECORD_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_to_pragma_eol (parser, خطأ);
	أرجع;
      }
    لكل (بشيا t = DECL_INITIAL (mapper_decl); t; t = بشيا_CHAIN (t))
      إذا (comptypes (بشيا_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_POINTER (mapper_id)
		      + حجم ("omp declare mapper ") - 1,
		    type);
	  بشيا prevmapper = بشيا_درج (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_SOURCE_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_to_pragma_eol (parser, خطأ);
	  أرجع;
	}
  }

  token = c_parser_peek_token (parser);
  إذا (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->درج, type);
      c_parser_consume_token (parser);
      DECL_ARTIFICIAL (var) = 1;
    }
  وإلا
    {
      error_at (token->location, "expected identifier");
      اذهب fail;
    }

  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    اذهب fail;

  تور_scope ();
  stmtlist = تور_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  طالما (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);
      إذا (c_kind != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (here, "unexpected clause");
	  اذهب fail;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, true);
    }

  إذا (maplist == NULL_بشيا)
    {
      error_at (شغرو_location, "missing %<map%> clause");
      اذهب fail;
    }
  بشيا list;
  لكل (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      بشيا dvar = OMP_CLAUSE_DECL (list);
      طالما (!DECL_P (dvar) && بشيا_OPERAND_LENGTH (dvar))
	dvar = بشيا_OPERAND (dvar, 0);
      إذا (dvar == var)
	اكسر;
    }
  إذا (!list)
    error_at (شغرو_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_كلي (OMP_DECLARE_MAPPER);
  بشيا_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  add_stmt (stmt);

  چرو_stmt_list (stmtlist);
  چرو_scope ();

  c_parser_skip_to_pragma_eol (parser);

  t = بشيا_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  أرجع;

 fail:
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 4.0
   #pragma omp declare reduction (reduction-id : typename-list : expression) \
      initializer-clause[opt] new-line

   initializer-clause:
      initializer (omp_priv = initializer)
      initializer (function-name (argument-list))  */

ساكن فراغ
c_parser_omp_declare_reduction (c_parser *parser, تعداد pragma_context context)
{
  unsigned صحيح tokens_avail = 0, i;
  c_token *saved_tokens = عدم;
  vec<بشيا> types = vNULL;
  vec<c_token> clauses = vNULL;
  تعداد بشيا_code reduc_code = ERROR_MARK;
  بشيا reduc_id = NULL_بشيا;
  بشيا type;
  location_t rloc = c_parser_peek_token (parser)->location;

  إذا (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare reduction%> not at file or block scope");
      اذهب fail;
    }

  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    اذهب fail;

  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_PLUS:
      reduc_code = PLUS_فرچ;
      اكسر;
    حالة CPP_MULT:
      reduc_code = MULT_فرچ;
      اكسر;
    حالة CPP_MINUS:
      reduc_code = MINUS_فرچ;
      اكسر;
    حالة CPP_AND:
      reduc_code = BIT_AND_فرچ;
      اكسر;
    حالة CPP_XOR:
      reduc_code = BIT_XOR_فرچ;
      اكسر;
    حالة CPP_OR:
      reduc_code = BIT_IOR_فرچ;
      اكسر;
    حالة CPP_AND_AND:
      reduc_code = TRUTH_ANDIF_فرچ;
      اكسر;
    حالة CPP_OR_OR:
      reduc_code = TRUTH_ORIF_فرچ;
      اكسر;
    حالة CPP_NAME:
      ثابت حرف *p;
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp (p, "min") == 0)
	{
	  reduc_code = MIN_فرچ;
	  اكسر;
	}
      إذا (strcmp (p, "max") == 0)
	{
	  reduc_code = MAX_فرچ;
	  اكسر;
	}
      reduc_id = c_parser_peek_token (parser)->درج;
      اكسر;
    افتراضي:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      اذهب fail;
    }

  بشيا orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_code, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    اذهب fail;

  طالما (true)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      بنية c_type_name *ctype = c_parser_type_name (parser);
      إذا (ctype != عدم)
	{
	  type = groktypename (ctype, عدم, عدم);
	  إذا (type == error_mark_كلي)
	    ;
	  وإلا إذا ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || بشيا_CODE (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_بشيا)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  وإلا إذا (بشيا_CODE (type) == FUNCTION_TYPE
		   || بشيا_CODE (type) == ARRAY_TYPE)
	    error_at (loc, "function or array type in "
		      "%<#pragma omp declare reduction%>");
	  وإلا إذا (TYPE_ATOMIC (type))
	    error_at (loc, "%<_Atomic%> qualified type in "
			   "%<#pragma omp declare reduction%>");
	  وإلا إذا (TYPE_QUALS_NO_ADDR_SPACE (type))
	    error_at (loc, "const, volatile or restrict qualified type in "
			   "%<#pragma omp declare reduction%>");
	  وإلا
	    {
	      بشيا t;
	      لكل (t = DECL_INITIAL (reduc_decl); t; t = بشيا_CHAIN (t))
		إذا (comptypes (بشيا_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_POINTER (reduc_id)
				   + حجم ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_SOURCE_LOCATION (بشيا_VEC_ELT (بشيا_درج (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    اكسر;
		  }
	      إذا (t == NULL_بشيا)
		types.safe_تور (type);
	    }
	  إذا (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    اكسر;
	}
      وإلا
	اكسر;
    }

  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_empty ())
    {
     fail:
      clauses.release ();
      types.release ();
      طالما (true)
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    اكسر;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_to_pragma_eol (parser);
      أرجع;
    }

  إذا (types.length () > 1)
    {
      طالما (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_EOF)
	    اذهب fail;
	  clauses.safe_تور (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_تور (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, حجم (eof_token));
      eof_token.type = CPP_EOF;
      clauses.safe_تور (eof_token);
      clauses.safe_تور (eof_token);
    }

  صحيح errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_tokens = parser->tokens;
      tokens_avail = parser->tokens_avail;
      إذا (!clauses.is_empty ())
	{
	  parser->tokens = clauses.address ();
	  parser->tokens_avail = clauses.length ();
	  parser->in_pragma = true;
	}

      منطقي nested = current_function_decl != NULL_بشيا;
      إذا (nested)
	c_تور_function_context ();
      بشيا fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, true);
      تور_scope ();
      بشيا stmt = تور_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      بشيا omp_out = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_out) = 1;
      DECL_CONTEXT (omp_out) = fndecl;
      pushdecl (omp_out);
      بشيا omp_in = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_in) = 1;
      DECL_CONTEXT (omp_in) = fndecl;
      pushdecl (omp_in);
      بنية c_فرچ combiner = c_parser_expression (parser);
      بنية c_فرچ initializer;
      بشيا omp_priv = NULL_بشيا, omp_orig = NULL_بشيا;
      منطقي bad = خطأ;
      initializer.set_error ();
      إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	bad = true;
      وإلا إذا (c_parser_next_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      إذا (!bad
	  && (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->درج),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  چرو_scope ();
	  تور_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_كلي;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    bad = true;
	  وإلا إذا (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      bad = true;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->درج),
			   "omp_priv") != 0)
	    {
	      إذا (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_kind != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  bad = true;
		}
	      وإلا
		initializer = c_parser_postfix_expression (parser);
	      إذا (initializer.درج
		  && بشيا_CODE (initializer.درج) == CALL_فرچ)
		{
		  صحيح j;
		  بشيا c = initializer.درج;
		  لكل (j = 0; j < call_فرچ_nargs (c); j++)
		    {
		      بشيا a = CALL_فرچ_ARG (c, j);
		      STRIP_NOPS (a);
		      إذا (بشيا_CODE (a) == ADDR_فرچ
			  && بشيا_OPERAND (a, 0) == omp_priv)
			اكسر;
		    }
		  إذا (j == call_فرچ_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  وإلا
	    {
	      c_parser_consume_token (parser);
	      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		bad = true;
	      وإلا
		{
		  بشيا st = تور_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (لي_table, loc);
		  start_init (omp_priv, NULL_بشيا, خطأ, خطأ, &richloc);
		  بنية c_فرچ init = c_parser_initializer (parser, omp_priv);
		  finish_init ();
		  finish_decl (omp_priv, loc, init.درج,
		      	       init.original_type, NULL_بشيا);
		  چرو_stmt_list (st);
		}
	    }
	  إذا (!bad
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    bad = true;
	}

      إذا (!bad)
	{
	  c_parser_skip_to_pragma_eol (parser);

	  بشيا t = بشيا_cons (type, make_بشيا_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_SOURCE_LOCATION (omp_out) = rloc;
	  بشيا_VEC_ELT (بشيا_درج (t), 0) = omp_out;
	  بشيا_VEC_ELT (بشيا_درج (t), 1) = omp_in;
	  بشيا_VEC_ELT (بشيا_درج (t), 2) = combiner.درج;
	  walk_بشيا (&combiner.درج, c_check_omp_declare_reduction_r,
		     &بشيا_VEC_ELT (بشيا_درج (t), 0), عدم);
	  إذا (omp_priv)
	    {
	      DECL_SOURCE_LOCATION (omp_priv) = rloc;
	      بشيا_VEC_ELT (بشيا_درج (t), 3) = omp_priv;
	      بشيا_VEC_ELT (بشيا_درج (t), 4) = omp_orig;
	      بشيا_VEC_ELT (بشيا_درج (t), 5) = initializer.درج;
	      walk_بشيا (&initializer.درج, c_check_omp_declare_reduction_r,
			 &بشيا_VEC_ELT (بشيا_درج (t), 3), عدم);
	      walk_بشيا (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &بشيا_VEC_ELT (بشيا_درج (t), 3), عدم);
	    }
	}

      چرو_stmt_list (stmt);
      چرو_scope ();
      إذا (cfun->language != عدم)
	{
	  ggc_free (cfun->language);
	  cfun->language = عدم;
	}
      set_cfun (عدم);
      current_function_decl = NULL_بشيا;
      إذا (nested)
	c_چرو_function_context ();

      إذا (!clauses.is_empty ())
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}
      إذا (bad)
	اذهب fail;
      إذا (errs != errorcount)
	اكسر;
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

ساكن منطقي
c_parser_omp_declare (c_parser *parser, تعداد pragma_context context)
{
  c_parser_consume_pragma (parser);
  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  أرجع true;
	}
      إذا (strcmp (p, "reduction") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_reduction (parser, context);
	  أرجع خطأ;
	}
      إذا (strcmp (p, "mapper") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_mapper (parser, context);
	  أرجع خطأ;
	}
      إذا (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, خطأ);
	  أرجع خطأ;
	}
      إذا (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_target (parser);
	  أرجع خطأ;
	}
      إذا (strcmp (p, "variant") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  أرجع true;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_to_pragma_eol (parser);
  أرجع خطأ;
}

/* OpenMP 5.0
   #pragma omp requires clauses[optseq] new-line  */

ساكن فراغ
c_parser_omp_requires (c_parser *parser)
{
  تعداد omp_requires new_req = (تعداد omp_requires) 0;

  c_parser_consume_pragma (parser);

  location_t loc = c_parser_peek_token (parser)->location;
  طالما (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      إذا (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ثابت حرف *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  تعداد omp_requires this_req = (تعداد omp_requires) 0;

	  إذا (!strcmp (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_ADDRESS;
	  وإلا إذا (!strcmp (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_MEMORY;
	  وإلا إذا (!strcmp (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  وإلا إذا (!strcmp (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  وإلا إذا (!strcmp (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_REVERSE_OFFLOAD;
	  وإلا إذا (!strcmp (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      إذا (parens.require_open (parser))
		{
		  إذا (c_parser_next_token_is (parser, CPP_NAME))
		    {
		      بشيا v = c_parser_peek_token (parser)->درج;
		      p = IDENTIFIER_POINTER (v);

		      إذا (!strcmp (p, "seq_cst"))
			this_req
			  = (تعداد omp_requires) OMP_MEMORY_ORDER_SEQ_CST;
		      وإلا إذا (!strcmp (p, "relaxed"))
			this_req
			  = (تعداد omp_requires) OMP_MEMORY_ORDER_RELAXED;
		      وإلا إذا (!strcmp (p, "release"))
			this_req
			  = (تعداد omp_requires) OMP_MEMORY_ORDER_RELEASE;
		      وإلا إذا (!strcmp (p, "acq_rel"))
			this_req
			  = (تعداد omp_requires) OMP_MEMORY_ORDER_ACQ_REL;
		      وإلا إذا (!strcmp (p, "acquire"))
			this_req
			  = (تعداد omp_requires) OMP_MEMORY_ORDER_ACQUIRE;
		    }
		  إذا (this_req == 0)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<acq_rel%>, %<acquire%>, "
				"%<relaxed%>, %<release%> or %<seq_cst%>");
		      بدل (c_parser_peek_token (parser)->type)
			{
			حالة CPP_EOF:
			حالة CPP_PRAGMA_EOL:
			حالة CPP_CLOSE_PAREN:
			  اكسر;
			افتراضي:
			  إذا (c_parser_peek_2nd_token (parser)->type
			      == CPP_CLOSE_PAREN)
			    c_parser_consume_token (parser);
			  اكسر;
			}
		    }
		  وإلا
		    c_parser_consume_token (parser);

		  parens.skip_until_found_close (parser);
		  إذا (this_req == 0)
		    {
		      c_parser_skip_to_pragma_eol (parser, خطأ);
		      أرجع;
		    }
		}
	      p = عدم;
	    }
	  وإلا
	    {
	      error_at (cloc, "expected %<unified_address%>, "
			      "%<unified_shared_memory%>, "
			      "%<self_maps%>, "
			      "%<dynamic_allocators%>, "
			       "%<reverse_offload%> "
			       "or %<atomic_default_mem_order%> clause");
	      c_parser_skip_to_pragma_eol (parser, خطأ);
	      أرجع;
	    }
	  إذا (p)
	    c_parser_consume_token (parser);
	  إذا (this_req)
	    {
	      إذا ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  إذا ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  إذا (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_mask & OMP_REQUIRES_TARGET_USED) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      وإلا إذا ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (تعداد omp_requires) 0;
		}
	      وإلا إذا ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (تعداد omp_requires)
		       (omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER);
		}
	      وإلا إذا ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (تعداد omp_requires) (new_req | this_req);
	      omp_requires_mask
		= (تعداد omp_requires) (omp_requires_mask | this_req);
	      استمر;
	    }
	}
      اكسر;
    }
  c_parser_skip_to_pragma_eol (parser);

  إذا (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

ساكن بشيا
c_finish_taskloop_clauses (بشيا clauses)
{
  بشيا *pc = &clauses;
  لكل (بشيا c = clauses; c; c = *pc)
    {
      منطقي remove = خطأ;
      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
	{
	  بشيا type = strip_array_types (بشيا_TYPE (OMP_CLAUSE_DECL (c)));
	  إذا (integer_zerop (TYPE_SIZE_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      remove = true;
	    }
	  وإلا إذا (بشيا_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      remove = true;
	    }
	}
      إذا (remove)
	*pc = OMP_CLAUSE_CHAIN (c);
      وإلا
	pc = &OMP_CLAUSE_CHAIN (c);
    }
  أرجع clauses;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_لمب_TASKS)	\
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

ساكن بشيا
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       حرف *p_name, omp_clause_mask mask, بشيا *cclauses,
		       منطقي *if_p)
{
  بشيا clauses, block, ret;

  strcat (p_name, " taskloop");
  mask |= OMP_TASKLOOP_CLAUSE_MASK;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  إذا ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_لمب_THREADS)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IN_REDUCTION);

  إذا (c_parser_next_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);

      إذا (strcmp (p, "simd") == 0)
	{
	  بشيا cclauses_buf[C_OMP_CLAUSE_SPLIT_كدي];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (true);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, true);
	  إذا (ret == عدم)
	    أرجع ret;
	  ret = make_كلي (OMP_TASKLOOP);
	  بشيا_TYPE (ret) = void_type_كلي;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_finish_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  SET_فرچ_LOCATION (ret, loc);
	  add_stmt (ret);
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, خطأ);
      أرجع NULL_بشيا;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_split_clauses (loc, OMP_TASKLOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
    }

  clauses = c_finish_taskloop_clauses (clauses);
  block = c_begin_compound_stmt (true);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, عدم, if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  أرجع ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
ساكن بشيا
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  بشيا sizes = NULL_بشيا;

  إذا (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  إذا (tok->type != CPP_NAME
      || strcmp ("sizes", IDENTIFIER_POINTER (tok->درج)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      أرجع error_mark_كلي;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع error_mark_كلي;

  vec<بشيا, va_gc> *sizes_vec
    = c_parser_فرچ_list (parser, true, true, عدم, عدم, عدم, عدم);
  sizes = build_بشيا_list_vec (sizes_vec);
  release_بشيا_vector (sizes_vec);

  لكل (بشيا s = sizes; s; s = بشيا_CHAIN (s))
    {
      بشيا فرچ = بشيا_درج (s);
      إذا (فرچ == error_mark_كلي)
	{
	  parens.skip_until_found_close (parser);
	  أرجع error_mark_كلي;
	}

      HOST_WIDE_INT n;
      إذا (!INTEGRAL_TYPE_P (بشيا_TYPE (فرچ))
	  || !بشيا_fits_shwi_p (فرچ)
	  || (n = بشيا_to_shwi (فرچ)) <= 0
	  || (صحيح) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  بشيا_درج (s) = integer_one_كلي;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  بشيا c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  أرجع c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

ساكن بشيا
c_parser_omp_tile (location_t loc, c_parser *parser, منطقي *if_p)
{
  بشيا clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_to_pragma_eol (parser);

  إذا (!clauses || clauses == error_mark_كلي)
    أرجع error_mark_كلي;

  بشيا block = c_begin_compound_stmt (true);
  بشيا ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    عدم, if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  أرجع ret;
}

#define OMP_UNROLL_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FULL))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

ساكن بشيا
c_parser_omp_unroll (location_t loc, c_parser *parser, منطقي *if_p)
{
  بشيا clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_MASK,
					   "#pragma omp unroll", true);

  بشيا block = c_begin_compound_stmt (true);
  بشيا ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    عدم, if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  أرجع ret;
}

/* OpenMP 5.1
   #pragma omp nothing new-line  */

ساكن فراغ
c_parser_omp_nothing (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp error clauses[optseq] new-line  */

ساكن منطقي
c_parser_omp_error (c_parser *parser, تعداد pragma_context context)
{
  صحيح at_compilation = -1;
  صحيح severity_fatal = -1;
  بشيا message = NULL_بشيا;
  منطقي bad = خطأ;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  طالما (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      إذا (!c_parser_next_token_is (parser, CPP_NAME))
	اكسر;

      ثابت حرف *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      location_t cloc = c_parser_peek_token (parser)->location;
      ساكن ثابت حرف *حجوجي[] = {
	"execution", "compilation", "warning", "fatal"
      };
      صحيح *v = عدم;
      صحيح idx = 0, n = -1;
      بشيا m = NULL_بشيا;

      إذا (!strcmp (p, "at"))
	v = &at_compilation;
      وإلا إذا (!strcmp (p, "severity"))
	{
	  v = &severity_fatal;
	  idx += 2;
	}
      وإلا إذا (strcmp (p, "message"))
	{
	  error_at (cloc,
		    "expected %<at%>, %<severity%> or %<message%> clause");
	  c_parser_skip_to_pragma_eol (parser, خطأ);
	  أرجع خطأ;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      إذا (parens.require_open (parser))
	{
	  إذا (v == عدم)
	    {
	      location_t فرچ_loc = c_parser_peek_token (parser)->location;
	      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
	      فرچ = convert_lvalue_to_rvalue (فرچ_loc, فرچ, true, true);
	      m = convert (const_string_type_كلي, فرچ.درج);
	      m = c_fully_fold (m, خطأ, عدم);
	    }
	  وإلا
	    {
	      إذا (c_parser_next_token_is (parser, CPP_NAME))
		{
		  بشيا val = c_parser_peek_token (parser)->درج;
		  ثابت حرف *q = IDENTIFIER_POINTER (val);

		  إذا (!strcmp (q, حجوجي[idx]))
		    n = 0;
		  وإلا إذا (!strcmp (q, حجوجي[idx + 1]))
		    n = 1;
		}
	      إذا (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", حجوجي[idx], حجوجي[idx + 1]);
		  bad = true;
		  بدل (c_parser_peek_token (parser)->type)
		    {
		    حالة CPP_EOF:
		    حالة CPP_PRAGMA_EOL:
		    حالة CPP_CLOSE_PAREN:
		      اكسر;
		    افتراضي:
		      إذا (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)
			c_parser_consume_token (parser);
		      اكسر;
		    }
		}
	      وإلا
		c_parser_consume_token (parser);
	    }

	  parens.skip_until_found_close (parser);

	  إذا (v == عدم)
	    {
	      إذا (message)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = true;
		}
	      وإلا
		message = m;
	    }
	  وإلا إذا (n != -1)
	    {
	      إذا (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = true;
		}
	      وإلا
		*v = n;
	    }
	}
      وإلا
	bad = true;
    }
  c_parser_skip_to_pragma_eol (parser);
  إذا (bad)
    أرجع true;

  إذا (at_compilation == -1)
    at_compilation = 1;
  إذا (severity_fatal == -1)
    severity_fatal = 1;
  إذا (!at_compilation)
    {
      إذا (context != pragma_compound)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may only be used in compound statements");
	  أرجع true;
	}
      إذا (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->in_intervening_code)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->fail = true;
	  أرجع true;
	}
      بشيا fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_IN_GOMP_ERROR
						: BUILT_IN_GOMP_WARNING);
      إذا (!message)
	message = build_zero_cst (const_string_type_كلي);
      بشيا stmt = build_call_فرچ_loc (loc, fndecl, 2, message,
				       build_all_ones_cst (size_type_كلي));
      add_stmt (stmt);
      أرجع true;
    }
  ثابت حرف *سكو = عدم;
  إذا (message)
    {
      سكو = c_getstr (message);
      إذا (سكو == عدم)
	سكو = _("<message unknown at compile time>");
    }
  ثابت تعداد diagnostics::kind diag_kind = (severity_fatal
					    ? diagnostics::kind::error
					    : diagnostics::kind::warning);
  إذا (سكو)
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered: %s", سكو);
  وإلا
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered");
  أرجع خطأ;
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

ساكن فراغ
c_parser_omp_assumption_clauses (c_parser *parser, منطقي is_assume)
{
  منطقي no_openmp = خطأ;
  منطقي no_openmp_constructs = خطأ;
  منطقي no_openmp_routines = خطأ;
  منطقي no_parallelism = خطأ;
  bitmap_head absent_head, contains_head;

  bitmap_obstack_initialize (عدم);
  bitmap_initialize (&absent_head, &bitmap_default_obstack);
  bitmap_initialize (&contains_head, &bitmap_default_obstack);

  إذا (c_parser_next_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  طالما (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      إذا (!c_parser_next_token_is (parser, CPP_NAME))
	اكسر;

      ثابت حرف *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      location_t cloc = c_parser_peek_token (parser)->location;

      إذا (!strcmp (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  إذا (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = true;
	}
      وإلا إذا (!strcmp (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  إذا (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = true;
	}
      وإلا إذا (!strcmp (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  إذا (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = true;
	}
      وإلا إذا (!strcmp (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  إذا (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = true;
	}
      وإلا إذا (!strcmp (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  إذا (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_فرچ فرچ = c_parser_فرچ_no_commas (parser, عدم);
	      بشيا t = convert_lvalue_to_rvalue (eloc, فرچ, true, true).درج;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, خطأ, عدم);
	      إذا (is_assume && t != error_mark_كلي)
		{
		  بشيا fn = build_call_فرچ_internal_loc (eloc, IFN_ASSUME,
							  void_type_كلي, 1,
							  t);
		  add_stmt (fn);
		}
	      parens.skip_until_found_close (parser);
	    }
	}
      وإلا إذا (!strcmp (p, "absent") || !strcmp (p, "contains"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  إذا (parens.require_open (parser))
	    {
	      افعل
		{
		  ثابت حرف *directive[3] = {};
		  صحيح i;
		  location_t dloc = c_parser_peek_token (parser)->location;
		  لكل (i = 0; i < 3; i++)
		    {
		      بشيا id;
		      إذا (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->درج;
		      وإلا إذا (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  تعداد rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      وإلا
			اكسر;
		      directive[i] = IDENTIFIER_POINTER (id);
		    }
		  إذا (i == 0)
		    error_at (dloc, "expected directive name");
		  وإلا
		    {
		      ثابت بنية c_omp_directive *dir
			= c_omp_categorize_directive (directive[0],
						      directive[1],
						      directive[2]);
		      إذا (dir
			  && dir->id != PRAGMA_OMP_END
			  && (dir->kind == C_OMP_DIR_DECLARATIVE
			      || dir->kind == C_OMP_DIR_INFORMATIONAL
			      || dir->kind == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      وإلا إذا (dir == عدم
			       || dir->id == PRAGMA_OMP_END
			       || (!dir->second && directive[1])
			       || (!dir->third && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      وإلا
			{
			  صحيح id = dir - c_omp_directives;
			  إذا (bitmap_bit_p (p[0] == 'a' ? &contains_head
							: &absent_head, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  وإلا إذا (!bitmap_set_bit (p[0] == 'a'
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
		      لكل (; i; --i)
			c_parser_consume_token (parser);
		    }
		  إذا (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  وإلا
		    اكسر;
		}
	      طالما (1);
	      parens.skip_until_found_close (parser);
	    }
	}
      وإلا إذا (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      matching_parens parens;
	      parens.consume_open (parser);
	      c_parser_balanced_token_sequence (parser);
	      parens.require_close (parser);
	    }
	}
      وإلا
	{
	  c_parser_consume_token (parser);
	  error_at (cloc, "expected assumption clause");
	  اكسر;
	}
    }
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

ساكن فراغ
c_parser_omp_assume (c_parser *parser, منطقي *if_p)
{
  c_parser_omp_assumption_clauses (parser, true);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
}

/* OpenMP 5.1
   #pragma omp assumes clauses[optseq] new-line  */

ساكن فراغ
c_parser_omp_assumes (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_omp_assumption_clauses (parser, خطأ);
}

/* Helper function for c_parser_omp_metadirective.  */

ساكن فراغ
analyze_metadirective_body (c_parser *parser,
			    vec<c_token> &tokens,
			    vec<بشيا> &labels)
{
  صحيح nesting_depth = 0;
  صحيح bracket_depth = 0;
  منطقي ignore_label = خطأ;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  طالما (1)
    {
      c_token *token = c_parser_peek_token (parser);
      منطقي stop = خطأ;

      إذا (c_parser_next_token_is_keyword (parser, RID_CASE))
	ignore_label = true;

      بدل (token->type)
	{
	حالة CPP_EOF:
	  اكسر;
	حالة CPP_NAME:
	  إذا (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.safe_تور (token->درج);
	  اذهب add;
	حالة CPP_OPEN_BRACE:
	  ++nesting_depth;
	  اذهب add;
	حالة CPP_CLOSE_BRACE:
	  إذا (--nesting_depth == 0 && bracket_depth == 0)
	    stop = true;
	  اذهب add;
	حالة CPP_OPEN_PAREN:
	  ++bracket_depth;
	  اذهب add;
	حالة CPP_CLOSE_PAREN:
	  --bracket_depth;
	  اذهب add;
	حالة CPP_COLON:
	  ignore_label = خطأ;
	  اذهب add;
	حالة CPP_SEMICOLON:
	  إذا (nesting_depth == 0 && bracket_depth == 0)
	    stop = true;
	  اذهب add;
	افتراضي:
	add:
	  tokens.safe_تور (*token);
	  إذا (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  وإلا إذا (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_to_pragma_eol (parser);
	  وإلا
	    c_parser_consume_token (parser);
	  إذا (stop)
	    اكسر;
	  استمر;
	}
      اكسر;
    }
}

/* OpenMP 5.0:

  # pragma omp metadirective [clause[, clause]]
*/

ساكن فراغ
c_parser_omp_metadirective (c_parser *parser, منطقي *if_p)
{
  ساكن unsigned صحيح metadirective_region_كدي = 0;

  بشيا ret;
  auto_vec<c_token> directive_tokens;
  auto_vec<c_token> body_tokens;
  auto_vec<بشيا> body_labels;
  auto_vec<ثابت بنية c_omp_directive *> directives;
  auto_vec<بشيا> ctxs;
  vec<بنية omp_variant> candidates;
  منطقي default_seen = خطأ;
  صحيح directive_token_idx = 0;
  بشيا standalone_body = NULL_بشيا;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  منطقي requires_body = خطأ;

  ret = make_كلي (OMP_METADIRECTIVE);
  SET_فرچ_LOCATION (ret, pragma_loc);
  بشيا_TYPE (ret) = void_type_كلي;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_بشيا;

  c_parser_consume_pragma (parser);
  طالما (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      إذا (c_parser_next_token_is_not (parser, CPP_NAME)
	  && c_parser_next_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  اذهب error;
	}

      location_t match_loc = c_parser_peek_token (parser)->location;
      ثابت حرف *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->درج);
      إذا (strcmp (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.add_fixit_replace (match_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      منطقي default_p
	= strcmp (p, "default") == 0 || strcmp (p, "otherwise") == 0;
      إذا (default_p)
	{
	  إذا (default_seen)
	    {
	      error_at (match_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      اذهب error;
	    }
	  default_seen = true;
	}
      وإلا إذا (default_seen)
	{
	  error_at (match_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  اذهب error;
	}
      إذا (!default_p && strcmp (p, "when") != 0)
	{
	  error_at (match_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  اذهب error;
	}

      matching_parens parens;
      بشيا ctx = NULL_بشيا;
      منطقي skip = خطأ;

      إذا (!parens.require_open (parser))
	اذهب error;

      إذا (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_بشيا);
	  إذا (ctx == error_mark_كلي)
	    اذهب error;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  إذا (ctx == error_mark_كلي)
	    اذهب error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_بشيا, خطأ) == 0);

	  إذا (c_parser_next_token_is_not (parser, CPP_COLON))
	    {
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      اذهب error;
	    }
	  c_parser_consume_token (parser);
	}

      /* Read in the directive type and create a dummy pragma token for
	 it.  */
      location_t loc = c_parser_peek_token (parser)->location;

      ثابت حرف *directive[3] = {};
      صحيح i;
      لكل (i = 0; i < 3; i++)
	{
	  بشيا id;
	  إذا (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      إذا (i == 0)
		directive[i++] = "nothing";
	      اكسر;
	    }
	  وإلا إذا (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->درج;
	  وإلا إذا (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      تعداد rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  وإلا
	    اكسر;

	  directive[i] = IDENTIFIER_POINTER (id);
	}
      إذا (i == 0)
	{
	  error_at (loc, "expected directive name");
	  اذهب error;
	}

      ثابت بنية c_omp_directive *omp_directive
	= c_omp_categorize_directive (directive[0],
				      directive[1],
				      directive[2]);

      إذا (omp_directive == عدم)
	{
	  لكل (صحيح j = 0; j < i; j++)
	    c_parser_consume_token (parser);
	  c_parser_error (parser, "unknown directive name");
	  اذهب error;
	}
      وإلا
	{
	  صحيح token_كدي = 0;
	  إذا (omp_directive->first) token_كدي++;
	  إذا (omp_directive->second) token_كدي++;
	  إذا (omp_directive->third) token_كدي++;
	  لكل (صحيح j = 0; j < token_كدي; j++)
	    c_parser_consume_token (parser);
	}
      إذا (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  اذهب error;
	}
      إذا (omp_directive->kind == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  اذهب error;
	}
      إذا (omp_directive->kind == C_OMP_DIR_CONSTRUCT)
	requires_body = true;

      إذا (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_kind = (تعداد pragma_kind) omp_directive->id;

	  directives.safe_تور (omp_directive);
	  directive_tokens.safe_تور (pragma_token);
	  ctxs.safe_تور (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      صحيح nesting_depth = 0;
      طالما (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  بدل (token->type)
	    {
	    حالة CPP_EOF:
	    حالة CPP_PRAGMA_EOL:
	      اكسر;
	    حالة CPP_OPEN_PAREN:
	      ++nesting_depth;
	      اذهب add;
	    حالة CPP_CLOSE_PAREN:
	      إذا (nesting_depth-- == 0)
		{
		  c_parser_consume_token (parser);
		  اكسر;
		}
	      اذهب add;
	    افتراضي:
	    add:
	      إذا (!skip)
		directive_tokens.safe_تور (*token);
	      c_parser_consume_token (parser);
	      استمر;
	    }
	  اكسر;
	}

      إذا (!skip)
	{
	  c_token eol_token;
	  memset (&eol_token, 0, حجم (eol_token));
	  eol_token.type = CPP_PRAGMA_EOL;
	  directive_tokens.safe_تور (eol_token);
	}
    }
  c_parser_skip_to_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  إذا (ctxs.length () == 1)
    {
      بشيا ctx = ctxs[0];
      إذا (ctx == NULL_بشيا
	  || (omp_context_selector_matches (ctx, NULL_بشيا, خطأ) == 1
	      && directive_tokens[0].pragma_kind == PRAGMA_OMP_NOTHING))
	أرجع;
    }

  إذا (!default_seen)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      ثابت بنية c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", عدم, عدم);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_kind = PRAGMA_OMP_NOTHING;

      directives.safe_تور (omp_directive);
      directive_tokens.safe_تور (pragma_token);
      ctxs.safe_تور (NULL_بشيا);

      c_token eol_token;
      memset (&eol_token, 0, حجم (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_tokens.safe_تور (eol_token);
    }

  إذا (requires_body)
    analyze_metadirective_body (parser, body_tokens, body_labels);

  /* Process each candidate directive.  */
  unsigned i;
  بشيا ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> tokens;

      /* Add the directive tokens.  */
      افعل
	tokens.safe_تور (directive_tokens [directive_token_idx++]);
      طالما (tokens.last ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_tokens.is_empty ());
      لكل (unsigned j = 0; j < body_tokens.length (); j++)
	tokens.safe_تور (body_tokens[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, حجم (eof_token));
      eof_token.type = CPP_EOF;
      tokens.safe_تور (eof_token);
      tokens.safe_تور (eof_token);

      unsigned صحيح old_tokens_avail = parser->tokens_avail;
      c_token *old_tokens = parser->tokens;
      بنية omp_attribute_pragma_state *old_in_omp_attribute_pragma
	= parser->in_omp_attribute_pragma;
      بنية omp_metadirective_parse_data *old_state
	= parser->omp_metadirective_state;

      بنية omp_metadirective_parse_data new_state;
      new_state.body_labels = &body_labels;
      new_state.region_لمب = ++metadirective_region_كدي;

      parser->tokens = tokens.address ();
      parser->tokens_avail = tokens.length ();
      parser->in_omp_attribute_pragma = عدم;
      parser->omp_metadirective_state = &new_state;

      صحيح prev_errorcount = errorcount;
      بشيا directive = c_begin_compound_stmt (true);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_بشيا);
      directive = c_end_compound_stmt (pragma_loc, directive, true);
      منطقي standalone_p
	= directives[i]->kind == C_OMP_DIR_STANDALONE
	  || directives[i]->kind == C_OMP_DIR_UTILITY;
      إذا (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  إذا (standalone_body == NULL_بشيا)
	    {
	      standalone_body = تور_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = چرو_stmt_list (standalone_body);
	    }
	  وإلا
	    c_parser_skip_to_end_of_block_or_statement (parser, true);
	}

      بشيا body = standalone_p ? standalone_body : NULL_بشيا;
      بشيا variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      إذا (errorcount == prev_errorcount)
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
  إذا (!candidates.is_empty ())
    ret = c_omp_expand_variant_construct (candidates);

  add_stmt (ret);
  أرجع;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  إذا (parser->in_pragma)
    c_parser_skip_to_pragma_eol (parser, خطأ);
}

/* Main entry point to parsing most OpenMP pragmas.  */

ساكن فراغ
c_parser_omp_construct (c_parser *parser, منطقي *if_p)
{
  تعداد pragma_kind p_kind;
  location_t loc;
  بشيا stmt;
  حرف p_name[حجم "#pragma omp teams distribute parallel for simd"];
  omp_clause_mask mask (0);

  loc = c_parser_peek_token (parser)->location;
  p_kind = c_parser_peek_token (parser)->pragma_kind;
  c_parser_consume_pragma (parser);

  بدل (p_kind)
    {
    حالة PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, true);
      أرجع;
    حالة PRAGMA_OACC_CACHE:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      اكسر;
    حالة PRAGMA_OACC_DATA:
      stmt = c_parser_oacc_data (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OACC_HOST_DATA:
      stmt = c_parser_oacc_host_data (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OACC_KERNELS:
    حالة PRAGMA_OACC_PARALLEL:
    حالة PRAGMA_OACC_SERIAL:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_kind, p_name, if_p);
      اكسر;
    حالة PRAGMA_OACC_LOOP:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, mask, عدم, if_p);
      اكسر;
    حالة PRAGMA_OACC_WAIT:
      strcpy (p_name, "#pragma wait");
      stmt = c_parser_oacc_wait (loc, parser, p_name);
      اكسر;
    حالة PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (loc, parser, خطأ);
      أرجع;
    حالة PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_DISTRIBUTE:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_distribute (loc, parser, p_name, mask, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_FOR:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, mask, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_LOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, mask, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_MASKED:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, mask, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_MASTER:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, mask, عدم, if_p,
				  UNKNOWN_LOCATION);
      اكسر;
    حالة PRAGMA_OMP_PARALLEL:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, mask, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_SECTIONS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, mask, عدم);
      اكسر;
    حالة PRAGMA_OMP_SIMD:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, mask, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_TASK:
      stmt = c_parser_omp_task (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_TASKGROUP:
      stmt = c_parser_omp_taskgroup (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_TASKLOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_taskloop (loc, parser, p_name, mask, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_TEAMS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, mask, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_ASSUME:
      c_parser_omp_assume (parser, if_p);
      أرجع;
    حالة PRAGMA_OMP_TILE:
      stmt = c_parser_omp_tile (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_UNROLL:
      stmt = c_parser_omp_unroll (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_DISPATCH:
      stmt = c_parser_omp_dispatch (loc, parser);
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }

  إذا (stmt && stmt != error_mark_كلي)
    gcc_assert (فرچ_LOCATION (stmt) != UNKNOWN_LOCATION);
}

/* OpenMP 6.0:
   # pragma omp groupprivate (variable-list) [device_type(...)]  */

#define OMP_GROUPPRIVATE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE) )

ساكن فراغ
c_parser_omp_groupprivate (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  بشيا vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, عدم);
  بشيا clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_MASK,
					   "#pragma omp groupprivate");
  /* TODO: Implies 'declare target local' with specified device_type, check for
     conflicts.  Check for other restrictions.  */
  (فراغ) vars;
  (فراغ) clauses;
  sorry_at (loc, "%<omp groupprivate%>");
}

/* OpenMP 2.5:
   # pragma omp threadprivate (variable-list) */

ساكن فراغ
c_parser_omp_threadprivate (c_parser *parser)
{
  بشيا vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, عدم);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  لكل (t = vars; t; t = بشيا_CHAIN (t))
    {
      بشيا v = بشيا_PURPOSE (t);
      loc = فرچ_LOCATION (بشيا_درج (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      إذا (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      وإلا إذا (بشيا_USED (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      وإلا إذا (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      وإلا إذا (بشيا_TYPE (v) == error_mark_كلي)
	;
      وإلا إذا (! COMPLETE_TYPE_P (بشيا_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      وإلا
	{
	  إذا (! DECL_THREAD_LOCAL_P (v))
	    {
	      set_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      إذا (DECL_RTL_SET_P (v))
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

ساكن بشيا
c_parser_transaction_attributes (c_parser *parser)
{
  إذا (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    أرجع c_parser_gnu_attributes (parser);

  إذا (!c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
    أرجع NULL_بشيا;
  أرجع c_parser_std_attribute_specifier (parser, true);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

ساكن بشيا
c_parser_transaction (c_parser *parser, تعداد rid keyword)
{
  unsigned صحيح old_in = parser->in_transaction;
  unsigned صحيح this_in = 1, new_in;
  location_t loc = c_parser_peek_token (parser)->location;
  بشيا stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  إذا (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  وإلا
    {
      attrs = c_parser_transaction_attributes (parser);
      إذا (attrs)
	this_in |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_in = this_in | (old_in & TM_STMT_ATTR_OUTER);

  parser->in_transaction = new_in;
  stmt = c_parser_compound_statement (parser);
  parser->in_transaction = old_in;

  إذا (flag_tm)
    stmt = c_finish_transaction (loc, stmt, this_in);
  وإلا
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  أرجع stmt;
}

/* Parse a __transaction_atomic or __transaction_relaxed expression
   (GCC Extension).

   transaction-expression:
     __transaction_atomic ( expression )
     __transaction_relaxed ( expression )
*/

ساكن بنية c_فرچ
c_parser_transaction_expression (c_parser *parser, تعداد rid keyword)
{
  بنية c_فرچ ret;
  unsigned صحيح old_in = parser->in_transaction;
  unsigned صحيح this_in = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  بشيا attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  إذا (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  وإلا
    {
      attrs = c_parser_transaction_attributes (parser);
      إذا (attrs)
	this_in |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->in_transaction = this_in;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      بشيا فرچ = c_parser_expression (parser).درج;
      ret.original_type = بشيا_TYPE (فرچ);
      ret.درج = build1 (TRANSACTION_فرچ, ret.original_type, فرچ);
      إذا (this_in & TM_STMT_ATTR_RELAXED)
	TRANSACTION_فرچ_RELAXED (ret.درج) = 1;
      SET_فرچ_LOCATION (ret.درج, loc);
      ret.original_code = TRANSACTION_فرچ;
      ret.m_decimal = 0;
      إذا (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, عدم);
	  اذهب error;
	}
    }
  وإلا
    {
     error:
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = عدم;
    }
  parser->in_transaction = old_in;

  إذا (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  set_c_فرچ_source_range (&ret, loc, loc);

  أرجع ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

ساكن بشيا
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  بشيا attrs;
  منطقي is_outer = خطأ;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_attributes (parser);
  إذا (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  إذا (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      اذهب ret_error;
    }
  وإلا إذا (parser->in_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      اذهب ret_error;
    }
  وإلا إذا (is_outer)
    {
      إذا ((parser->in_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  اذهب ret_error;
	}
    }
  وإلا إذا (parser->in_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      اذهب ret_error;
    }

  أرجع add_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  أرجع build1 (NOP_فرچ, void_type_كلي, error_mark_كلي);
}

/* Parse a single source file.  */

فراغ
c_parse_file (فراغ)
{
  /* Use local storage to begin.  If the first token is a pragma, parse it.
     If it is #pragma GCC pch_preprocess, then this will load a PCH file
     which will cause garbage collection.  */
  c_parser tparser;

  memset (&tparser, 0, حجم tparser);
  tparser.translate_strings_p = true;
  tparser.tokens = &tparser.tokens_buf[0];
  the_parser = &tparser;

  إذا (c_parser_peek_token (&tparser)->pragma_kind == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  وإلا
    c_common_no_more_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  إذا (tparser.tokens == &tparser.tokens_buf[0])
    the_parser->tokens = &the_parser->tokens_buf[0];

  /* Initialize EH, if we've been told to do so.  */
  إذا (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = عدم;
}

فراغ
c_init_preprocess (فراغ)
{
  /* Create a parser for use by pragma_lex during preprocessing.  */
  the_parser = ggc_alloc<c_parser> ();
  memset (the_parser, 0, حجم (c_parser));
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
c_parser_parse_rtl_body (c_parser *parser, حرف *start_with_pass)
{
  إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      حرر (start_with_pass);
      أرجع c_parser_peek_token (parser)->location;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  صحيح لمب_open_braces = 1;
  طالما (1)
    {
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_OPEN_BRACE:
	  لمب_open_braces++;
	  اكسر;
	حالة CPP_CLOSE_BRACE:
	  إذا (--لمب_open_braces == 0)
	    اذهب found_closing_brace;
	  اكسر;
	حالة CPP_EOF:
	  error_at (start_loc, "no closing brace");
	  حرر (start_with_pass);
	  أرجع c_parser_peek_token (parser)->location;
	افتراضي:
	  اكسر;
	}
      c_parser_consume_token (parser);
    }

 found_closing_brace:
  /* At the closing brace; record its location.  */
  location_t end_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  إذا (!read_rtl_function_body_from_file_range (start_loc, end_loc))
    {
      حرر (start_with_pass);
      أرجع end_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  run_rtl_passes (start_with_pass);
  أرجع end_loc;
}

#ضمن "gt-c-c-parser.h"
