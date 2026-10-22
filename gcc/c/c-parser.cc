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
#تعریف_کرو INCLUDE_STRING
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

vec<درخت> incomplete_ریکارڈ_decls;

خالی
سیٹ_c_اظہاریہ_ماخذ_range (c_اظہاریہ *اظہاریہ,
			 location_t آغاز, location_t اختتام)
{
  اظہاریہ->src_range.m_آغاز = آغاز;
  اظہاریہ->src_range.m_اختتام = اختتام;
  اگر (اظہاریہ->قدر)
    سیٹ_ماخذ_range (اظہاریہ->قدر, آغاز, اختتام);
}

خالی
سیٹ_c_اظہاریہ_ماخذ_range (c_اظہاریہ *اظہاریہ,
			 ماخذ_range src_range)
{
  اظہاریہ->src_range = src_range;
  اگر (اظہاریہ->قدر)
    سیٹ_ماخذ_range (اظہاریہ->قدر, src_range);
}


/* Initialization routine for this file.  */

خالی
c_parse_init (خالی)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  غیرعلامتی صحیح i;
  درخت id;
  صحیح نقاب = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  نقاب |= D_CXXONLY;
  اگر (!flag_isoc99)
    نقاب |= D_C99;
  اگر (!flag_isoc23)
    نقاب |= D_C23;
  اگر (flag_no_asm)
    {
      نقاب |= D_ASM | D_EXT;
      اگر (!flag_isoc99)
	نقاب |= D_EXT89;
      اگر (!flag_isoc23)
	نقاب |= D_EXT11;
    }
  اگر (!c_dialect_objc ())
    نقاب |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<درخت> ((صحیح) RID_MAX);
  برائے (i = 0; i < عدد_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      اگر (c_common_reswords[i].disable & نقاب)
	{
	  اگر (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].لفظ);
	      C_سیٹ_RID_رمز (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_لفظ (id) = 1;
	    }
	  جاری;
	}

      id = get_identifier (c_common_reswords[i].لفظ);
      C_سیٹ_RID_رمز (id, c_common_reswords[i].rid);
      C_IS_RESERVED_لفظ (id) = 1;
      ridpointers [(صحیح) c_common_reswords[i].rid] = id;
    }

  برائے (i = 0; i < عدد_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      حرف name[50];
      sprintf (name, "__int%d", int_n_ڈیٹا[i].bitsize);
      id = get_identifier (name);
      C_سیٹ_RID_رمز (id, RID_پہلا_INT_N + i);
      C_IS_RESERVED_لفظ (id) = 1;

      sprintf (name, "__int%d__", int_n_ڈیٹا[i].bitsize);
      id = get_identifier (name);
      C_سیٹ_RID_رمز (id, RID_پہلا_INT_N + i);
      C_IS_RESERVED_لفظ (id) = 1;
    }

  اگر (flag_openmp)
    {
      id = get_identifier ("omp_all_memory");
      C_سیٹ_RID_رمز (id, RID_OMP_ALL_حافظہ);
      C_IS_RESERVED_لفظ (id) = 1;
      ridpointers [RID_OMP_ALL_حافظہ] = id;
    }
}

/* A parser structure recording information about the state and
   context of parsing.  Includes lexer information with up to two
   tokens of look-ahead; more are not needed for C.  */
ساخت GTY(()) c_parser {
  /* The look-ahead tokens.  */
  c_token * GTY((skip)) علامات;
  /* Buffer for look-ahead tokens.  */
  c_token علامات_buf[4];
  /* How many look-ahead tokens are available (0 - 4, or
     more if parsing from pre-lexed tokens).  */
  غیرعلامتی صحیح علامات_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_علامات;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  غیرعلامتی صحیح raw_علامات_مستعمل;
  /* True if a syntax error is being recovered from; false otherwise.
     c_parser_error sets this flag.  It should clear this flag when
     enough tokens have been consumed to recover from the error.  */
  منطقی error : 1;
  /* True if we're processing a pragma, and shouldn't automatically
     consume CPP_PRAGMA_EOL.  */
  منطقی اندر_pragma : 1;
  /* True if we're parsing the outermost block of an if statement.  */
  منطقی اندر_if_بلاک : 1;
  /* True if we want to lex a translated, joined string (for an
     initial #pragma pch_preprocess).  Otherwise the parser is
     responsible for concatenating strings and translating to the
     execution character set as needed.  */
  منطقی lex_joined_string : 1;
  /* True if, when the parser is concatenating string literals, it
     should translate them to the execution character set (false
     inside attributes).  */
  منطقی translate_لڑیاں_p : 1;

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
  غیرعلامتی صحیح اندر_transaction : 4;
  /* True if we are in a context where the Objective-C "Property attribute"
     keywords are valid.  */
  منطقی objc_property_attr_context : 1;

  /* Whether we have just seen/constructed a string-literal.  Set when
     returning a string-literal from c_parser_string_literal.  Reset
     in consume_token.  Useful when we get a parse error and see an
     unknown token, which could have been a string-literal constant
     macro.  */
  منطقی نظر_آیا_string_literal : 1;

  /* TRUE if omp::directive, omp::decl or omp::sequence attributes may not
     appear.  */
  منطقی omp_attrs_forbidden_p : 1;

  /* Location of the last consumed token.  */
  location_t آخری_token_location;

  /* Holds state for parsing collapsed OMP_FOR loops.  Managed by
     c_parser_omp_for_loop.  */
  ساخت omp_for_parse_ڈیٹا * GTY((skip)) omp_for_parse_state;

  /* If we're in the context of OpenMP directives written as C23
     attributes turned into pragma, the tokens field is temporarily
     redirected.  This holds data needed to restore state afterwards.
     It's NULL otherwise.  */
  ساخت omp_attribute_pragma_state *اندر_omp_attribute_pragma;

  /* Set for omp::decl attribute parsing to the decl to which it
     appertains.  */
  درخت اندر_omp_decl_attribute;

  /* Non-null only when parsing the body of an OpenMP metadirective.
     Managed by c_parser_omp_metadirective.  */
  ساخت omp_metadirective_parse_ڈیٹا * GTY((skip))
    omp_metadirective_state;
};

/* Holds data needed to restore the token stream to its previous state
   after parsing an OpenMP attribute-syntax pragma.  */
ساخت GTY(()) omp_attribute_pragma_state
{
  vec<c_token, va_gc> *token_vec;
  c_token * GTY((skip)) save_علامات;
  غیرعلامتی صحیح save_علامات_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
ساخت GTY(()) omp_begin_declare_variant_map_اندراج {
  درخت variant;		/* The variant decl.  */
  درخت id;		/* Name of base function.  */
  درخت ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_اندراج, va_gc> *omp_begin_declare_variant_map;

ساکن درخت omp_آغاز_variant_function (c_declarator *, درخت);
ساکن خالی omp_اختتام_variant_function (درخت, درخت, درخت);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_علامات_buf (c_parser *parser, غیرعلامتی n)
{
  واپس &parser->علامات_buf[n];
}

/* Return the error state of PARSER.  */

منطقی
c_parser_error (c_parser *parser)
{
  واپس parser->error;
}

/* Set the error state of PARSER to ERR.  */

خالی
c_parser_سیٹ_error (c_parser *parser, منطقی err)
{
  parser->error = err;
}


/* The actual parser and external interface.  ??? Does this need to be
   garbage-collected?  */

ساکن GTY (()) c_parser *the_parser;

/* Read in and lex a single token, storing it in *TOKEN.  If RAW,
   context-sensitive postprocessing of the token is not done.  */

ساکن خالی
c_lex_one_token (c_parser *parser, c_token *token, منطقی raw = جھوٹ)
{
  timevar_ڈالو (TV_LEX);

  اگر (raw || vec_محفوظ_لمبائی (parser->raw_علامات) == 0)
    {
      token->type = c_lex_with_flags (&token->قدر, &token->location,
				      &token->flags,
				      (parser->lex_joined_string
				       ? 0 : C_LEX_STRING_NO_JOIN));
      token->id_قسم = C_ID_NONE;
      token->keyword = RID_MAX;
      token->pragma_قسم = PRAGMA_NONE;
    }
  ورنہ
    {
      /* Use a token previously lexed as a raw look-ahead token, and
	 complete the processing on it.  */
      *token = (*parser->raw_علامات)[parser->raw_علامات_مستعمل];
      ++parser->raw_علامات_مستعمل;
      اگر (parser->raw_علامات_مستعمل == vec_محفوظ_لمبائی (parser->raw_علامات))
	{
	  vec_free (parser->raw_علامات);
	  parser->raw_علامات_مستعمل = 0;
	}
    }

  اگر (raw)
    جاؤ برآمد;

  انتخاب (token->type)
    {
    حالت CPP_NAME:
      {
	درخت decl;

	منطقی objc_force_identifier = parser->objc_need_raw_identifier;
	اگر (c_dialect_objc ())
	  parser->objc_need_raw_identifier = جھوٹ;

	اگر (C_IS_RESERVED_لفظ (token->قدر))
	  {
	    شمار rid rid_رمز = C_RID_رمز (token->قدر);

	    اگر (rid_رمز == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->قدر);
	      }
	    ورنہ اگر (rid_رمز >= RID_پہلا_ADDR_SPACE
		     && rid_رمز <= RID_آخری_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_رمز - RID_پہلا_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_قسم = C_ID_ADDRSPACE;
		token->keyword = rid_رمز;
		توڑو;
	      }
	    ورنہ اگر (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_رمز))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		اگر (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_رمز;
		    توڑو;
		  }
		ورنہ اگر (parser->objc_could_be_foreach_context
			 && rid_رمز == RID_اندر)
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
		    token->keyword = rid_رمز;
		    توڑو;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    ورنہ اگر (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_رمز))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		اگر (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_رمز;
		    توڑو;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    ورنہ اگر (c_dialect_objc ()
		     && (OBJC_IS_AT_KEYWORD (rid_رمز)
			 || OBJC_IS_CXX_KEYWORD (rid_رمز)))
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
	    ورنہ
	      {
		token->type = CPP_KEYWORD;
		token->keyword = rid_رمز;
		توڑو;
	      }
	  }

	decl = lookup_name (token->قدر);
	اگر (decl)
	  {
	    اگر (درخت_رمز (decl) == TYPE_DECL)
	      {
		token->id_قسم = C_ID_TYPENAME;
		توڑو;
	      }
	  }
	ورنہ اگر (c_dialect_objc ())
	  {
	    درخت objc_interface_decl = objc_is_class_name (token->قدر);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    اگر (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->قدر = objc_interface_decl;
		token->id_قسم = C_ID_CLASSNAME;
		توڑو;
	      }
	  }
        token->id_قسم = C_ID_ID;
      }
      توڑو;
    حالت CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      انتخاب (C_RID_رمز (token->قدر))
	{
	  /* Replace 'class' with '@class', 'private' with '@private',
	     etc.  This prevents confusion with the C++ keyword
	     'class', and makes the tokens consistent with other
	     Objective-C 'AT' keywords.  For example '@class' is
	     reported as RID_AT_CLASS which is consistent with
	     '@synchronized', which is reported as
	     RID_AT_SYNCHRONIZED.
	  */
	حالت RID_CLASS:     token->keyword = RID_AT_CLASS; توڑو;
	حالت RID_نجی:   token->keyword = RID_AT_نجی; توڑو;
	حالت RID_PROTECTED: token->keyword = RID_AT_PROTECTED; توڑو;
	حالت RID_عوامی:    token->keyword = RID_AT_عوامی; توڑو;
	حالت RID_THROW:     token->keyword = RID_AT_THROW; توڑو;
	حالت RID_TRY:       token->keyword = RID_AT_TRY; توڑو;
	حالت RID_CATCH:     token->keyword = RID_AT_CATCH; توڑو;
	حالت RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; توڑو;
	طےشدہ:            token->keyword = C_RID_رمز (token->قدر);
	}
      توڑو;
    حالت CPP_COLON:
    حالت CPP_COMMA:
    حالت CPP_CLOSE_PAREN:
    حالت CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      اگر (c_dialect_objc ())
	parser->objc_need_raw_identifier = جھوٹ;
      توڑو;
    حالت CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_قسم = (شمار pragma_قسم) درخت_INT_CST_کم (token->قدر);
      token->قدر = تہی;
      توڑو;
    طےشدہ:
      توڑو;
    }
 برآمد:
  timevar_نکالو (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  اگر (parser->علامات_avail == 0)
    {
      c_lex_one_token (parser, &parser->علامات[0]);
      parser->علامات_avail = 1;
    }
  واپس &parser->علامات[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  اگر (parser->علامات_avail >= 2)
    واپس &parser->علامات[1];
  gcc_assert (parser->علامات_avail == 1);
  gcc_assert (parser->علامات[0].type != CPP_EOF);
  gcc_assert (parser->علامات[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->علامات[1]);
  parser->علامات_avail = 2;
  واپس &parser->علامات[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, غیرعلامتی صحیح n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  اگر (parser->علامات_avail >= n)
    واپس &parser->علامات[n - 1];
  gcc_assert (parser->علامات_avail == n - 1);
  c_lex_one_token (parser, &parser->علامات[n - 1]);
  parser->علامات_avail = n;
  واپس &parser->علامات[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, غیرعلامتی صحیح n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  اگر (parser->علامات_avail >= n)
    واپس &parser->علامات[n - 1];
  غیرعلامتی صحیح raw_len = vec_محفوظ_لمبائی (parser->raw_علامات);
  غیرعلامتی صحیح raw_avail
    = parser->علامات_avail + raw_len - parser->raw_علامات_مستعمل;
  gcc_assert (raw_avail >= n - 1);
  اگر (raw_avail >= n)
    واپس &(*parser->raw_علامات)[parser->raw_علامات_مستعمل
				  + n - 1 - parser->علامات_avail];
  vec_محفوظ_reserve (parser->raw_علامات, 1);
  parser->raw_علامات->تیز_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_علامات)[raw_len], سچ);
  واپس &(*parser->raw_علامات)[raw_len];
}

منطقی
c_keyword_starts_typename (شمار rid keyword)
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
      واپس سچ;
    طےشدہ:
      اگر (keyword >= RID_پہلا_INT_N
	  && keyword < RID_پہلا_INT_N + عدد_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_پہلا_INT_N])
	واپس سچ;
      واپس جھوٹ;
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
      انتخاب (token->id_قسم)
	{
	حالت C_ID_ID:
	  واپس جھوٹ;
	حالت C_ID_ADDRSPACE:
	  واپس سچ;
	حالت C_ID_TYPENAME:
	  واپس سچ;
	حالت C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  واپس سچ;
	طےشدہ:
	  gcc_unreachable ();
	}
    حالت CPP_KEYWORD:
      واپس c_keyword_starts_typename (token->keyword);
    حالت CPP_LESS:
      اگر (c_dialect_objc ())
	واپس سچ;
      واپس جھوٹ;
    طےشدہ:
      واپس جھوٹ;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

ساکن اندرونی منطقی
c_parser_اگلا_علامات_آغاز_typename (c_parser *parser, شمار c_lookahead_قسم la,
				     غیرعلامتی صحیح n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  اگر (c_token_starts_typename (token))
    واپس سچ;

  /* Try a bit harder to detect an unknown typename.  */
  اگر (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_قسم == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->قدر))
    واپس سچ;

  واپس جھوٹ;
}

/* Return true if TOKEN, after an open parenthesis, can start a
   compound literal (either a storage class specifier allowed in that
   context, or a type name), false otherwise.  */
ساکن منطقی
c_token_starts_compound_literal (c_token *token)
{
  انتخاب (token->type)
    {
    حالت CPP_KEYWORD:
      انتخاب (token->keyword)
	{
	حالت RID_CONSTEXPR:
	حالت RID_رجسٹر:
	حالت RID_STATIC:
	حالت RID_THREAD:
	  واپس سچ;
	طےشدہ:
	  توڑو;
	}
      /* Fall through.  */
    طےشدہ:
      واپس c_token_starts_typename (token);
    }
}

/* Return true if TOKEN is a type qualifier, false otherwise.  */
ساکن منطقی
c_token_is_qualifier (c_token *token)
{
  انتخاب (token->type)
    {
    حالت CPP_NAME:
      انتخاب (token->id_قسم)
	{
	حالت C_ID_ADDRSPACE:
	  واپس سچ;
	طےشدہ:
	  واپس جھوٹ;
	}
    حالت CPP_KEYWORD:
      انتخاب (token->keyword)
	{
	حالت RID_CONST:
	حالت RID_VOLATILE:
	حالت RID_RESTRICT:
	حالت RID_ATTRIBUTE:
	حالت RID_ATOMIC:
	  واپس سچ;
	طےشدہ:
	  واپس جھوٹ;
	}
    حالت CPP_LESS:
      واپس جھوٹ;
    طےشدہ:
      gcc_unreachable ();
    }
}

/* Return true if the next token from PARSER is a type qualifier,
   false otherwise.  */
ساکن اندرونی منطقی
c_parser_اگلا_token_is_qualifier (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  واپس c_token_is_qualifier (token);
}

/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes), false otherwise.  */
ساکن منطقی
c_token_starts_declspecs (c_token *token)
{
  انتخاب (token->type)
    {
    حالت CPP_NAME:
      انتخاب (token->id_قسم)
	{
	حالت C_ID_ID:
	  واپس جھوٹ;
	حالت C_ID_ADDRSPACE:
	  واپس سچ;
	حالت C_ID_TYPENAME:
	  واپس سچ;
	حالت C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  واپس سچ;
	طےشدہ:
	  gcc_unreachable ();
	}
    حالت CPP_KEYWORD:
      انتخاب (token->keyword)
	{
	حالت RID_STATIC:
	حالت RID_EXTERN:
	حالت RID_رجسٹر:
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
	  واپس سچ;
	طےشدہ:
	  اگر (token->keyword >= RID_پہلا_INT_N
	      && token->keyword < RID_پہلا_INT_N + عدد_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_پہلا_INT_N])
	    واپس سچ;
	  واپس جھوٹ;
	}
    حالت CPP_LESS:
      اگر (c_dialect_objc ())
	واپس سچ;
      واپس جھوٹ;
    طےشدہ:
      واپس جھوٹ;
    }
}


/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes) or a static assertion, false
   otherwise.  */
ساکن منطقی
c_token_starts_declaration (c_token *token)
{
  اگر (c_token_starts_declspecs (token)
      || token->keyword == RID_STATIC_ASSERT)
    واپس سچ;
  ورنہ
    واپس جھوٹ;
}

/* Return true if the next token from PARSER can start declaration
   specifiers (not including standard attributes), false
   otherwise.  */
منطقی
c_parser_اگلا_token_starts_declspecs (c_parser *parser)
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
      && token->id_قسم == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    واپس جھوٹ;

  واپس c_token_starts_declspecs (token);
}

ساکن منطقی c_parser_check_متوازن_raw_token_sequence (c_parser *,
							غیرعلامتی صحیح *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
منطقی
c_parser_اگلا_علامات_آغاز_declaration (c_parser *parser, غیرعلامتی صحیح n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  اگر (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_قسم == C_ID_CLASSNAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_DOT)
    واپس جھوٹ;

  /* Labels do not start declarations.  */
  اگر (token->type == CPP_NAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_COLON)
    واپس جھوٹ;

  /* A static assertion is only a declaration if followed by a semicolon;
     otherwise, it may be an expression in C2Y.  */
  اگر (token->keyword == RID_STATIC_ASSERT
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_PAREN)
    {
      n += 2;
      اگر (!c_parser_check_متوازن_raw_token_sequence (parser, &n)
	  || c_parser_peek_nth_token_raw (parser, n)->type != CPP_CLOSE_PAREN)
	/* Invalid static assertion syntax; treat as a declaration and report a
	   syntax error there.  */
	واپس سچ;
      واپس c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  اگر (c_token_starts_declaration (token))
    واپس سچ;

  اگر (c_parser_اگلا_علامات_آغاز_typename (parser, cla_nonabstract_decl, n))
    واپس سچ;

  واپس جھوٹ;
}

/* Consume the next token from PARSER.  */

خالی
c_parser_consume_token (c_parser *parser)
{
  gcc_assert (parser->علامات_avail >= 1);
  gcc_assert (parser->علامات[0].type != CPP_EOF);
  gcc_assert (!parser->اندر_pragma || parser->علامات[0].type != CPP_PRAGMA_EOL);
  /* CPP_PRAGMA should not show up here except if there was an error or inside
     another pragma.  */
  gcc_assert (parser->اندر_pragma
	      || parser->error
	      || parser->علامات[0].type != CPP_PRAGMA);
  parser->آخری_token_location = parser->علامات[0].location;
  اگر (parser->علامات != &parser->علامات_buf[0])
    parser->علامات++;
  ورنہ اگر (parser->علامات_avail >= 2)
    {
      parser->علامات[0] = parser->علامات[1];
      اگر (parser->علامات_avail >= 3)
        {
          parser->علامات[1] = parser->علامات[2];
          اگر (parser->علامات_avail >= 4)
            parser->علامات[2] = parser->علامات[3];
        }
    }
  parser->علامات_avail--;
  parser->نظر_آیا_string_literal = جھوٹ;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

ساکن خالی
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->اندر_pragma);
  gcc_assert (parser->علامات_avail >= 1);
  gcc_assert (parser->علامات[0].type == CPP_PRAGMA);
  اگر (parser->علامات != &parser->علامات_buf[0])
    parser->علامات++;
  ورنہ اگر (parser->علامات_avail >= 2)
    {
      parser->علامات[0] = parser->علامات[1];
      اگر (parser->علامات_avail >= 3)
	parser->علامات[1] = parser->علامات[2];
    }
  parser->علامات_avail--;
  parser->اندر_pragma = سچ;
}

/* Update the global input_location from TOKEN.  */
ساکن اندرونی خالی
c_parser_سیٹ_ماخذ_position_from_token (c_token *token)
{
  اگر (token->type != CPP_EOF)
    {
      داخلہ_location = token->location;
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

ساکن منطقی
c_parser_peek_conflict_marker (c_parser *parser, شمار cpp_ttype tok1_قسم,
			       location_t *برآمد_loc)
{
  c_token *token2 = c_parser_peek_2nd_token (parser);
  اگر (token2->type != tok1_قسم)
    واپس جھوٹ;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  اگر (token3->type != tok1_قسم)
    واپس جھوٹ;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  اگر (token4->type != conflict_marker_get_final_tok_قسم (tok1_قسم))
    واپس جھوٹ;

  /* It must be at the start of the line.  */
  location_t آغاز_loc = c_parser_peek_token (parser)->location;
  اگر (LOCATION_عمود (آغاز_loc) != 1)
    واپس جھوٹ;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t اختتام_loc = get_اختتام (token4->location);
  *برآمد_loc = make_location (آغاز_loc, آغاز_loc, اختتام_loc);

  واپس سچ;
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

ساکن منطقی
c_parser_error_richloc (c_parser *parser, ثابت حرف *gmsgid,
			rich_location *richloc)
{
  c_token *token = c_parser_peek_token (parser);
  اگر (parser->error)
    واپس جھوٹ;
  parser->error = سچ;
  اگر (!gmsgid)
    واپس جھوٹ;

  /* If this is actually a conflict marker, report it as such.  */
  اگر (token->type == CPP_LSHIFT
      || token->type == CPP_RSHIFT
      || token->type == CPP_EQ_EQ)
    {
      location_t loc;
      اگر (c_parser_peek_conflict_marker (parser, token->type, &loc))
	{
	  error_at (loc, "version control conflict marker in file");
	  واپس سچ;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_گروہ d;
  name_hint h;
  اگر (parser->نظر_آیا_string_literal && token->type == CPP_NAME)
    {
      درخت name = token->قدر;
      ثابت حرف *token_name = IDENTIFIER_اشارہ_گر (name);
      ثابت حرف *سرخی_hint
	= get_c_stdlib_سرخی_for_string_macro_name (token_name);
      اگر (سرخی_hint != تہی)
	h = name_hint (خالی_اشاریہ,
		       std::make_unique<suggest_missing_سرخی>
			 (token->location,
			  token_name,
			  سرخی_hint));
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
		 token->قدر, /*flags=*/0, richloc);
  واپس سچ;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

منطقی
c_parser_error (c_parser *parser, ثابت حرف *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_سیٹ_ماخذ_position_from_token (token);
  rich_location richloc (سطر_جدول, داخلہ_location);
  واپس c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

سانچہ <قسم_نام traits_t>
جماعت token_pair
{
 عوامی:
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

    واپس c_parser_require (parser, traits_t::open_token_type,
			     traits_t::open_gmsgid);
  }

  /* Consume the next token from PARSER, recording its location as
     that of the opening token within the pair.  */

  خالی consume_open (c_parser *parser)
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
    واپس c_parser_require (parser, traits_t::close_token_type,
			     traits_t::close_gmsgid, m_open_loc);
  }

  /* Like token_pair::require_close, except that tokens will be skipped
     until the desired token is found.  An error message is still produced
     if the next token is not as expected.  */

  خالی skip_until_ملا_close (c_parser *parser) ثابت
  {
    c_parser_skip_until_ملا (parser, traits_t::close_token_type,
			       traits_t::close_gmsgid, m_open_loc);
  }

 نجی:
  location_t m_open_loc;
};

/* Traits for token_pair<T> for tracking matching pairs of parentheses.  */

ساخت matching_paren_traits
{
  ساکن ثابت شمار cpp_ttype open_token_type = CPP_OPEN_PAREN;
  ساکن ثابت حرف * ثابت open_gmsgid;
  ساکن ثابت شمار cpp_ttype close_token_type = CPP_CLOSE_PAREN;
  ساکن ثابت حرف * ثابت close_gmsgid;
};

ثابت حرف * ثابت matching_paren_traits::open_gmsgid = "expected %<(%>";
ثابت حرف * ثابت matching_paren_traits::close_gmsgid = "expected %<)%>";

/* "matching_parens" is a token_pair<T> class for tracking matching
   pairs of parentheses.  */

قسمتعریف token_pair<matching_paren_traits> matching_parens;

/* Traits for token_pair<T> for tracking matching pairs of braces.  */

ساخت matching_brace_traits
{
  ساکن ثابت شمار cpp_ttype open_token_type = CPP_OPEN_BRACE;
  ساکن ثابت حرف * ثابت open_gmsgid;
  ساکن ثابت شمار cpp_ttype close_token_type = CPP_CLOSE_BRACE;
  ساکن ثابت حرف * ثابت close_gmsgid;
};

ثابت حرف * ثابت matching_brace_traits::open_gmsgid = "expected %<{%>";
ثابت حرف * ثابت matching_brace_traits::close_gmsgid = "expected %<}%>";

/* "matching_braces" is a token_pair<T> class for tracking matching
   pairs of braces.  */

قسمتعریف token_pair<matching_brace_traits> matching_braces;

/* Get a description of the matching symbol to TYPE e.g. "(" for
   CPP_CLOSE_PAREN.  */

ساکن ثابت حرف *
get_matching_علامت (شمار cpp_ttype type)
{
  انتخاب (type)
    {
    طےشدہ:
      gcc_unreachable ();
    حالت CPP_CLOSE_PAREN:
      واپس "(";
    حالت CPP_CLOSE_BRACE:
      واپس "{";
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
		  شمار cpp_ttype type,
		  ثابت حرف *msgid,
		  location_t matching_location,
		  منطقی type_is_unique)
{
  اگر (c_parser_اگلا_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      واپس سچ;
    }
  ورنہ
    {
      location_t اگلا_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (اگلا_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      اگر (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->آخری_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      منطقی added_matching_location = جھوٹ;
      اگر (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.جوڑو_location_if_nearby (*global_dc, matching_location);

      اگر (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	اگر (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_علامت (type));

      واپس جھوٹ;
    }
}

/* If the next token is the indicated keyword, consume it.  Otherwise,
   issue the error MSGID.  Returns true if found, false otherwise.  */

ساکن منطقی
c_parser_require_keyword (c_parser *parser,
			  شمار rid keyword,
			  ثابت حرف *msgid)
{
  اگر (c_parser_اگلا_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      واپس سچ;
    }
  ورنہ
    {
      c_parser_error (parser, msgid);
      واپس جھوٹ;
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

خالی
c_parser_skip_until_ملا (c_parser *parser,
			   شمار cpp_ttype type,
			   ثابت حرف *msgid,
			   location_t matching_location)
{
  غیرعلامتی nesting_گہرائی = 0;

  اگر (c_parser_require (parser, type, msgid, matching_location))
    {
      اگر (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->اندر_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  اگر (token->type == CPP_EOF)
	    {
	      parser->علامات = parser->اندر_omp_attribute_pragma->save_علامات;
	      parser->علامات_avail
		= parser->اندر_omp_attribute_pragma->save_علامات_avail;
	      parser->اندر_omp_attribute_pragma = تہی;
	    }
	}
      واپس;
    }

  /* Skip tokens until the desired token is found.  */
  جب (سچ)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      اگر (token->type == type && !nesting_گہرائی)
	{
	  c_parser_consume_token (parser);
	  اگر (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->اندر_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      اگر (token->type == CPP_EOF)
		{
		  parser->علامات = parser->اندر_omp_attribute_pragma->save_علامات;
		  parser->علامات_avail
		    = parser->اندر_omp_attribute_pragma->save_علامات_avail;
		  parser->اندر_omp_attribute_pragma = تہی;
		}
	    }
	  توڑو;
	}

      /* If we've run out of tokens, stop.  */
      اگر (token->type == CPP_EOF)
	واپس;
      اگر (token->type == CPP_PRAGMA_EOL && parser->اندر_pragma)
	واپس;
      اگر (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_مربع)
	++nesting_گہرائی;
      ورنہ اگر (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_مربع)
	{
	  اگر (nesting_گہرائی-- == 0)
	    توڑو;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = جھوٹ;
}

/* Skip tokens until the end of a parameter is found, but do not
   consume the comma, semicolon or closing delimiter.  */

ساکن خالی
c_parser_skip_مقصد_انتہا_کا_parameter (c_parser *parser)
{
  غیرعلامتی nesting_گہرائی = 0;

  جب (سچ)
    {
      c_token *token = c_parser_peek_token (parser);
      اگر ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_گہرائی)
	توڑو;
      /* If we've run out of tokens, stop.  */
      اگر (token->type == CPP_EOF)
	واپس;
      اگر (token->type == CPP_PRAGMA_EOL && parser->اندر_pragma)
	واپس;
      اگر (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_مربع)
	++nesting_گہرائی;
      ورنہ اگر (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_مربع)
	{
	  اگر (nesting_گہرائی-- == 0)
	    توڑو;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = جھوٹ;
}

/* Skip tokens until a non-nested closing curly brace is the next
   token, or there are no more tokens. Return true in the first case,
   false otherwise.  */

ساکن منطقی
c_parser_skip_مقصد_closing_brace (c_parser *parser)
{
  غیرعلامتی nesting_گہرائی = 0;

  جب (سچ)
    {
      c_token *token = c_parser_peek_token (parser);

      انتخاب (token->type)
	{
	حالت CPP_PRAGMA_EOL:
	  اگر (!parser->اندر_pragma)
	    توڑو;
	  /* FALLTHRU */
	حالت CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  واپس جھوٹ;

	حالت CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  اگر (nesting_گہرائی-- == 0)
	    واپس سچ;
	  توڑو;

	حالت CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_گہرائی;
	  توڑو;

	طےشدہ:
	  توڑو;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Expect to be at the end of the pragma directive and consume an
   end of line marker.  */

ساکن خالی
c_parser_skip_مقصد_pragma_eol (c_parser *parser, منطقی error_if_not_eol = سچ)
{
  gcc_assert (parser->اندر_pragma);
  parser->اندر_pragma = جھوٹ;

  اگر (error_if_not_eol && c_parser_peek_token (parser)->type != CPP_PRAGMA_EOL)
    c_parser_error (parser, "expected end of line");

  cpp_ttype token_type;
  کرو
    {
      c_token *token = c_parser_peek_token (parser);
      token_type = token->type;
      اگر (token_type == CPP_EOF)
	توڑو;
      c_parser_consume_token (parser);
    }
  جب (token_type != CPP_PRAGMA_EOL);

  اگر (parser->اندر_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (token->type == CPP_EOF)
	{
	  parser->علامات = parser->اندر_omp_attribute_pragma->save_علامات;
	  parser->علامات_avail
	    = parser->اندر_omp_attribute_pragma->save_علامات_avail;
	  parser->اندر_omp_attribute_pragma = تہی;
	}
    }

  parser->error = جھوٹ;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
ساکن خالی
c_parser_skip_مقصد_pragma_omp_انتہا_declare_variant (c_parser *parser)
{
  برائے (صحیح گہرائی = 0; گہرائی >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      انتخاب (token->type)
	{
	حالت CPP_PRAGMA_EOL:
	  اگر (!parser->اندر_pragma)
	    توڑو;
	  /* FALLTHRU */
	حالت CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  واپس;

	حالت CPP_PRAGMA:
	  اگر ((token->pragma_قسم == PRAGMA_OMP_BEGIN
	       || token->pragma_قسم == PRAGMA_OMP_انتہا)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      درخت id1 = c_parser_peek_nth_token (parser, 2)->قدر;
	      درخت id2 = c_parser_peek_nth_token (parser, 3)->قدر;
	      اگر (strcmp (IDENTIFIER_اشارہ_گر (id1), "declare") == 0
		  && strcmp (IDENTIFIER_اشارہ_گر (id2), "variant") == 0)
		{
		  اگر (token->pragma_قسم == PRAGMA_OMP_BEGIN)
		    گہرائی++;
		  ورنہ
		    گہرائی--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	  جاری;

	طےشدہ:
	  توڑو;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Skip tokens until we have consumed an entire block, or until we
   have consumed a non-nested ';'.  */

ساکن خالی
c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (c_parser *parser,
					    منطقی metadirective_p = جھوٹ)
{
  غیرعلامتی nesting_گہرائی = 0;
  صحیح bracket_گہرائی = 0;
  منطقی save_error = parser->error;

  جب (سچ)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      انتخاب (token->type)
	{
	حالت CPP_EOF:
	  واپس;

	حالت CPP_PRAGMA_EOL:
	  اگر (parser->اندر_pragma)
	    واپس;
	  توڑو;

	حالت CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  اگر (!nesting_گہرائی && (!metadirective_p || bracket_گہرائی <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      جاؤ ختم_شدہ;
	    }
	  توڑو;

	حالت CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  اگر ((nesting_گہرائی == 0 || --nesting_گہرائی == 0)
	      && (!metadirective_p || bracket_گہرائی <= 0))
	    {
	      c_parser_consume_token (parser);
	      جاؤ ختم_شدہ;
	    }
	  توڑو;

	حالت CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_گہرائی;
	  توڑو;

	حالت CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  اگر (metadirective_p && nesting_گہرائی == 0)
	    ++bracket_گہرائی;
	  توڑو;

	حالت CPP_CLOSE_PAREN:
	  اگر (metadirective_p && nesting_گہرائی == 0)
	    --bracket_گہرائی;
	  توڑو;

	حالت CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	  parser->error = save_error;
	  جاری;

	طےشدہ:
	  توڑو;
	}

      c_parser_consume_token (parser);
    }

 ختم_شدہ:
  parser->error = جھوٹ;
}

/* CPP's options (initialized by c-opts.cc).  */
خارجی cpp_options *cpp_opts;

/* Save the warning flags which are controlled by __extension__.  */

ساکن اندرونی صحیح
disable_extension_diagnostics (خالی)
{
  صحیح ret = (pedantic
	     | (warn_اشارہ_گر_arith << 1)
	     | (warn_traditional << 2)
	     | (flag_iso << 3)
	     | (warn_long_long << 4)
	     | (warn_cxx_compat << 5)
	     | (warn_overlength_لڑیاں << 6)
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
  warn_اشارہ_گر_arith = 0;
  cpp_opts->cpp_warn_traditional = warn_traditional = 0;
  flag_iso = 0;
  cpp_opts->cpp_warn_long_long = warn_long_long = 0;
  warn_cxx_compat = 0;
  warn_overlength_لڑیاں = 0;
  warn_c90_c99_compat = 0;
  warn_c99_c11_compat = 0;
  warn_c11_c23_compat = 0;
  warn_c23_c2y_compat = 0;
  واپس ret;
}

/* Restore the warning flags which are controlled by __extension__.
   FLAGS is the return value from disable_extension_diagnostics.  */

ساکن اندرونی خالی
restore_extension_diagnostics (صحیح flags)
{
  cpp_opts->cpp_pedantic = pedantic = flags & 1;
  warn_اشارہ_گر_arith = (flags >> 1) & 1;
  cpp_opts->cpp_warn_traditional = warn_traditional = (flags >> 2) & 1;
  flag_iso = (flags >> 3) & 1;
  cpp_opts->cpp_warn_long_long = warn_long_long = (flags >> 4) & 1;
  warn_cxx_compat = (flags >> 5) & 1;
  warn_overlength_لڑیاں = (flags >> 6) & 1;
  /* See above for why is this needed.  */
  warn_c90_c99_compat = (flags >> 7) & 1 ? 1 : ((flags >> 8) & 1 ? -1 : 0);
  warn_c99_c11_compat = (flags >> 9) & 1 ? 1 : ((flags >> 10) & 1 ? -1 : 0);
  warn_c11_c23_compat = (flags >> 11) & 1 ? 1 : ((flags >> 12) & 1 ? -1 : 0);
  warn_c23_c2y_compat = (flags >> 13) & 1 ? 1 : ((flags >> 14) & 1 ? -1 : 0);
}

/* Helper data structure for parsing #pragma acc routine.  */
ساخت oacc_routine_ڈیٹا {
  منطقی error_نظر_آیا; /* Set if error has been reported.  */
  منطقی fndecl_نظر_آیا; /* Set if one fn decl/definition has been seen already.  */
  درخت clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
ساکن درخت objc_foreach_break_label, objc_foreach_continue_label;

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
ساخت omp_for_parse_ڈیٹا {
  شمار درخت_رمز_2 رمز;
  درخت declv, condv, incrv, initv;
  درخت pre_body;
  درخت bindings;
  صحیح گنتی;	/* Expected nesting depth.  */
  صحیح گہرائی;	/* Current nesting depth.  */
  location_t for_loc;
  منطقی ordered : 1;
  منطقی inscan : 1;
  منطقی want_nested_loop : 1;
  منطقی اندر_intervening_رمز : 1;
  منطقی saw_intervening_رمز: 1;
  منطقی perfect_nesting_fail : 1;
  منطقی fail : 1;
};

ساخت attr_state
{
  /* True if we parsed a musttail attribute for return.  */
  منطقی musttail_p;

  خالی reset () { musttail_p = جھوٹ; }
};

ساکن منطقی c_parser_nth_token_starts_std_اوصاف (c_parser *,
						      غیرعلامتی صحیح);
ساکن درخت c_parser_std_attribute_specifier_sequence (c_parser *);
ساکن خالی c_parser_external_declaration (c_parser *);
ساکن خالی c_parser_asm_definition (c_parser *);
ساکن درخت c_parser_declaration_or_fndef (c_parser *, منطقی, منطقی, منطقی,
					   منطقی, منطقی, منطقی, درخت * = تہی,
					   vec<c_token> * = تہی,
					   منطقی have_attrs = جھوٹ,
					   درخت attrs = تہی,
					   ساخت oacc_routine_ڈیٹا * = تہی,
					   منطقی * = تہی);
ساکن منطقی c_parser_handle_statement_omp_اوصاف (c_parser *, درخت &,
						      منطقی *);
ساکن خالی c_parser_static_assert_declaration_no_semi (c_parser *);
ساکن خالی c_parser_static_assert_declaration (c_parser *);
ساکن ساخت c_typespec c_parser_enum_specifier (c_parser *);
ساکن ساخت c_typespec c_parser_struct_or_union_specifier (c_parser *);
ساکن درخت c_parser_struct_declaration (c_parser *, درخت *);
ساکن ساخت c_typespec c_parser_typeof_specifier (c_parser *);
ساکن درخت c_parser_alignas_specifier (c_parser *);
ساکن ساخت c_declarator *c_parser_براہ_راست_declarator (c_parser *, منطقی,
							c_dtr_syn, منطقی *);
ساکن ساخت c_declarator *c_parser_براہ_راست_declarator_inner (c_parser *,
							      منطقی,
							      ساخت c_declarator *);
ساکن ساخت c_arg_info *c_parser_parms_declarator (c_parser *, منطقی, درخت,
						     منطقی);
ساکن ساخت c_arg_info *c_parser_parms_list_declarator (c_parser *, درخت,
							  درخت, منطقی);
ساکن ساخت c_parm *c_parser_parameter_declaration (c_parser *, درخت, منطقی);
ساکن درخت c_parser_asm_string_literal (c_parser *);
ساکن درخت c_parser_simple_asm_اظہاریہ (c_parser *);
ساکن درخت c_parser_gnu_اوصاف (c_parser *);
ساکن ساخت c_اظہاریہ c_parser_initializer (c_parser *, درخت);
ساکن ساخت c_اظہاریہ c_parser_braced_init (c_parser *, درخت, منطقی,
					   ساخت obstack *, منطقی);
ساکن خالی c_parser_initelt (c_parser *, ساخت obstack *);
ساکن خالی c_parser_initval (c_parser *, ساخت c_اظہاریہ *,
			      ساخت obstack *);
ساکن درخت c_parser_compound_statement (c_parser *, location_t * = تہی);
ساکن location_t c_parser_compound_statement_nostart (c_parser *);
ساکن خالی c_parser_label (c_parser *, درخت);
ساکن خالی c_parser_statement (c_parser *, منطقی *, location_t * = تہی);
ساکن خالی c_parser_statement_after_labels (c_parser *, منطقی *, درخت,
					     vec<درخت> * = تہی,
					     attr_state = {});
ساکن درخت c_parser_c99_بلاک_statement (c_parser *, منطقی *,
					  location_t * = تہی);
ساکن خالی c_parser_if_statement (c_parser *, منطقی *, vec<درخت> *);
ساکن خالی c_parser_switch_statement (c_parser *, منطقی *, درخت);
ساکن خالی c_parser_while_statement (c_parser *, منطقی, غیرعلامتی مختصر, منطقی,
				      منطقی *, درخت);
ساکن خالی c_parser_do_statement (c_parser *, منطقی, غیرعلامتی مختصر, منطقی,
				   درخت);
ساکن خالی c_parser_for_statement (c_parser *, منطقی, غیرعلامتی مختصر, منطقی,
				    منطقی *, درخت);
ساکن درخت c_parser_asm_statement (c_parser *);
ساکن درخت c_parser_asm_operands (c_parser *);
ساکن درخت c_parser_asm_goto_operands (c_parser *);
ساکن درخت c_parser_asm_clobbers (c_parser *);
ساکن ساخت c_اظہاریہ c_parser_اظہاریہ_no_commas (c_parser *, ساخت c_اظہاریہ *,
					      درخت = NULL_درخت);
ساکن ساخت c_اظہاریہ c_parser_conditional_عبارت (c_parser *,
						      ساخت c_اظہاریہ *, درخت);
ساکن ساخت c_اظہاریہ c_parser_ثنائی_عبارت (c_parser *, ساخت c_اظہاریہ *,
						 درخت);
ساکن ساخت c_اظہاریہ c_parser_cast_عبارت (c_parser *, ساخت c_اظہاریہ *);
ساکن ساخت c_اظہاریہ c_parser_unary_عبارت (c_parser *);
ساکن ساخت c_اظہاریہ c_parser_sizeof_or_countof_عبارت (c_parser *,
							    شمار rid);
ساکن ساخت c_اظہاریہ c_parser_alignof_عبارت (c_parser *);
ساکن ساخت c_اظہاریہ c_parser_maxof_or_minof_عبارت (c_parser *, شمار rid);
ساکن ساخت c_اظہاریہ c_parser_postfix_عبارت (c_parser *);
ساکن ساخت c_اظہاریہ c_parser_postfix_عبارت_after_paren_type (c_parser *,
								   ساخت c_declspecs *,
								   ساخت c_type_name *,
								   location_t);
ساکن ساخت c_اظہاریہ c_parser_postfix_عبارت_after_primary (c_parser *,
								location_t loc,
								ساخت c_اظہاریہ);
ساکن درخت c_parser_transaction (c_parser *, شمار rid);
ساکن ساخت c_اظہاریہ c_parser_transaction_عبارت (c_parser *, شمار rid);
ساکن درخت c_parser_transaction_cancel (c_parser *);
ساکن ساخت c_اظہاریہ c_parser_عبارت (c_parser *);
ساکن ساخت c_اظہاریہ c_parser_عبارت_conv (c_parser *);
ساکن vec<درخت, va_gc> *c_parser_اظہاریہ_list (c_parser *, منطقی, منطقی,
					     vec<درخت, va_gc> **, location_t *,
					     درخت *, vec<location_t> *,
					     غیرعلامتی صحیح * = تہی);
ساکن ساخت c_اظہاریہ c_parser_has_attribute_عبارت (c_parser *);

ساکن خالی c_parser_oacc_declare (c_parser *);
ساکن خالی c_parser_oacc_enter_exit_ڈیٹا (c_parser *, منطقی);
ساکن خالی c_parser_oacc_update (c_parser *);
ساکن خالی c_parser_omp_construct (c_parser *, منطقی *);
ساکن خالی c_parser_omp_groupprivate (c_parser *);
ساکن خالی c_parser_omp_threadprivate (c_parser *);
ساکن خالی c_parser_omp_barrier (c_parser *);
ساکن خالی c_parser_omp_depobj (c_parser *);
ساکن خالی c_parser_omp_flush (c_parser *);
ساکن منطقی c_parser_omp_اگلا_علامات_can_be_canon_loop (c_parser *,
							شمار درخت_رمز_2, منطقی);
ساکن درخت c_parser_omp_loop_nest (c_parser *, منطقی *);
ساکن درخت c_parser_omp_for_loop (location_t, c_parser *, شمار درخت_رمز_2,
				   درخت, درخت *, منطقی *);
ساکن خالی c_parser_omp_taskwait (c_parser *);
ساکن خالی c_parser_omp_taskyield (c_parser *);
ساکن خالی c_parser_omp_cancel (c_parser *);
ساکن خالی c_parser_omp_nothing (c_parser *);
ساکن خالی c_parser_omp_metadirective (c_parser *, منطقی *);

شمار pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
ساکن منطقی c_parser_pragma (c_parser *, شمار pragma_context, منطقی *, درخت);
ساکن منطقی c_parser_omp_cancellation_نقطہ (c_parser *, شمار pragma_context);
ساکن منطقی c_parser_omp_ہدف (c_parser *, شمار pragma_context, منطقی *);
ساکن خالی c_parser_omp_begin (c_parser *);
ساکن خالی c_parser_omp_انتہا (c_parser *);
ساکن منطقی c_parser_omp_declare (c_parser *, شمار pragma_context);
ساکن خالی c_parser_omp_requires (c_parser *);
ساکن منطقی c_parser_omp_error (c_parser *, شمار pragma_context);
ساکن خالی c_parser_omp_assumption_clauses (c_parser *, منطقی);
ساکن خالی c_parser_omp_allocate (c_parser *);
ساکن خالی c_parser_omp_assumes (c_parser *);
ساکن منطقی c_parser_omp_ordered (c_parser *, شمار pragma_context, منطقی *);
ساکن درخت c_parser_omp_dispatch (location_t, c_parser *);
ساکن خالی c_parser_omp_interop (c_parser *);
ساکن خالی c_parser_oacc_routine (c_parser *, شمار pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
ساکن خالی c_parser_objc_class_definition (c_parser *, درخت);
ساکن خالی c_parser_objc_class_instance_variables (c_parser *);
ساکن خالی c_parser_objc_class_declaration (c_parser *);
ساکن خالی c_parser_objc_alias_declaration (c_parser *);
ساکن خالی c_parser_objc_protocol_definition (c_parser *, درخت);
ساکن منطقی c_parser_objc_طریقہ_type (c_parser *);
ساکن خالی c_parser_objc_طریقہ_definition (c_parser *);
ساکن خالی c_parser_objc_methodprotolist (c_parser *);
ساکن خالی c_parser_objc_methodproto (c_parser *);
ساکن درخت c_parser_objc_طریقہ_decl (c_parser *, منطقی, درخت *, درخت *);
ساکن درخت c_parser_objc_type_name (c_parser *);
ساکن درخت c_parser_objc_protocol_refs (c_parser *);
ساکن خالی c_parser_objc_try_catch_finally_statement (c_parser *);
ساکن خالی c_parser_objc_synchronized_statement (c_parser *);
ساکن درخت c_parser_objc_selector (c_parser *);
ساکن درخت c_parser_objc_selector_arg (c_parser *);
ساکن درخت c_parser_objc_receiver (c_parser *);
ساکن درخت c_parser_objc_پیغام_دلائل (c_parser *);
ساکن درخت c_parser_objc_keywordexpr (c_parser *);
ساکن خالی c_parser_objc_at_property_declaration (c_parser *);
ساکن خالی c_parser_objc_at_synthesize_declaration (c_parser *);
ساکن خالی c_parser_objc_at_dynamic_declaration (c_parser *);
ساکن منطقی c_parser_objc_diagnose_bad_element_سابقہ
  (c_parser *, ساخت c_declspecs *);
ساکن location_t c_parser_parse_rtl_body (c_parser *, حرف *);
ساکن درخت c_parser_handle_musttail (c_parser *, درخت, attr_state &);

#اگر ENABLE_ANALYZER

نامخلا ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

جماعت c_translation_unit : عوامی translation_unit
{
عوامی:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  درخت lookup_constant_by_id (درخت id) ثابت final override
  {
    /* Consider decls.  */
    اگر (درخت decl = lookup_name (id))
      اگر (درخت_رمز (decl) == CONST_DECL)
	اگر (درخت قدر = DECL_INITIAL (decl))
	  اگر (درخت_رمز (قدر) == INTEGER_CST)
	    واپس قدر;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    اگر (cpp_macro_p (hashnode))
      اگر (درخت قدر = consider_macro (hashnode->قدر.macro))
	واپس قدر;

    واپس NULL_درخت;
  }

  درخت
  lookup_type_by_id (درخت id) ثابت final override
  {
    اگر (درخت type_decl = lookup_name (id))
	اگر (درخت_رمز (type_decl) == TYPE_DECL)
	  {
	    درخت ریکارڈ_type = درخت_TYPE (type_decl);
	    اگر (درخت_رمز (ریکارڈ_type) == ریکارڈ_TYPE)
	      واپس ریکارڈ_type;
	  }

    واپس NULL_درخت;
  }

  درخت
  lookup_global_var_by_id (درخت id) ثابت final override
  {
    اگر (درخت var_decl = lookup_name (id))
      اگر (درخت_رمز (var_decl) == VAR_DECL)
				واپس var_decl;

    واپس NULL_درخت;
  }

نجی:
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
  درخت consider_macro (cpp_macro *macro, صحیح گہرائی = 0) ثابت
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (گہرائی >= 0);

    اگر (macro->paramc > 0)
      واپس NULL_درخت;
    اگر (macro->قسم != cmk_macro)
      واپس NULL_درخت;
    اگر (macro->گنتی != 1)
      واپس NULL_درخت;
    ثابت cpp_token &tok = macro->قوت_نما.علامات[0];
    اگر (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	اگر (گہرائی >= param_analyzer_max_macro_alias_گہرائی)
	  واپس NULL_درخت;

	cpp_hashnode *alias = tok.val.گرہ.گرہ;
	اگر (cpp_macro_p (alias))
	  واپس consider_macro (alias->قدر.macro, گہرائی + 1);

	/* Not a simple alias.  */
	واپس NULL_درخت;
      }
    ورنہ اگر (tok.type != CPP_نمبر)
      واپس NULL_درخت;

    cpp_reader *old_parse_اندر = parse_اندر;
    parse_اندر = cpp_create_reader (CLK_GNUC89, تہی, سطر_جدول);

    pretty_printer pp;
    pp_string (&pp, (ثابت حرف *) tok.val.str.متن);
    pp_newline (&pp);
    cpp_ڈالو_بفر (parse_اندر,
		     (ثابت غیرعلامتی حرف *) pp_formatted_متن (&pp),
		     لڑی_لمبائی (pp_formatted_متن (&pp)),
		     0);

    درخت قدر;
    location_t loc;
    غیرعلامتی حرف cpp_flags;
    c_lex_with_flags (&قدر, &loc, &cpp_flags, 0);

    cpp_destroy (parse_اندر);
    parse_اندر = old_parse_اندر;

    اگر (قدر && درخت_رمز (قدر) == INTEGER_CST)
      واپس قدر;

    واپس NULL_درخت;
  }
};

} // namespace ana

#اگر_ختم /* #if ENABLE_ANALYZER */

/* Parse a translation unit (C90 6.7, C99 6.9, C11 6.9).

   translation-unit:
     external-declarations

   external-declarations:
     external-declaration
     external-declarations external-declaration

   GNU extensions:

   translation-unit:
خالی_خانے
*/

ساکن خالی
c_parser_translation_unit (c_parser *parser)
{
  اگر (c_parser_اگلا_token_is (parser, CPP_EOF))
    {
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C forbids an empty translation unit");
    }
  ورنہ
    {
      خالی *obstack_position = obstack_alloc (&parser_obstack, 0);
      mark_valid_location_for_stdc_pragma (جھوٹ);
      کرو
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      جب (c_parser_اگلا_token_is_not (parser, CPP_EOF));
    }

  غیرعلامتی صحیح i;
  درخت decl;
  FOR_EACH_VEC_ELT (incomplete_ریکارڈ_decls, i, decl)
    اگر (DECL_سائز (decl) == NULL_درخت && درخت_TYPE (decl) != error_mark_گرہ)
      error ("storage size of %q+D isn%'t known", decl);

  اگر (vec_محفوظ_لمبائی (current_omp_declare_ہدف_attribute))
    {
      c_omp_declare_ہدف_attr
	a = current_omp_declare_ہدف_attribute->نکالو ();
      اگر (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_محفوظ_truncate (current_omp_declare_ہدف_attribute, 0);
    }
  اگر (vec_محفوظ_لمبائی (current_omp_begin_assumes))
    {
      اگر (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_محفوظ_truncate (current_omp_begin_assumes, 0);
    }
  اگر (vec_محفوظ_لمبائی (current_omp_declare_variant_attribute))
    {
      اگر (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_محفوظ_truncate (current_omp_declare_variant_attribute, 0);
    }
  اگر (vec_محفوظ_لمبائی (omp_begin_declare_variant_map))
    {
      غیرعلامتی صحیح i;
      omp_begin_declare_variant_map_اندراج *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_اختتام_variant_function (e->variant, e->id, e->ctx);
      vec_محفوظ_truncate (omp_begin_declare_variant_map, 0);
    }

#اگر ENABLE_ANALYZER
  اگر (flag_analyzer)
    {
      ana::c_translation_unit tu;
      ana::on_اختتام_translation_unit (tu);
    }
#اگر_ختم
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

ساکن خالی
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
	  توڑو;
	حالت RID_ASM:
	  c_parser_asm_definition (parser);
	  توڑو;
	حالت RID_AT_INTERFACE:
	حالت RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_definition (parser, NULL_درخت);
	  توڑو;
	حالت RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  توڑو;
	حالت RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  توڑو;
	حالت RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_protocol_definition (parser, NULL_درخت);
	  توڑو;
	حالت RID_AT_PROPERTY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_property_declaration (parser);
	  توڑو;
	حالت RID_AT_SYNTHESIZE:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_synthesize_declaration (parser);
	  توڑو;
	حالت RID_AT_DYNAMIC:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_dynamic_declaration (parser);
	  توڑو;
	حالت RID_AT_انتہا:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_اختتام_implementation ();
	  توڑو;
	طےشدہ:
	  جاؤ decl_or_fndef;
	}
      توڑو;
    حالت CPP_SEMICOLON:
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      توڑو;
    حالت CPP_PRAGMA:
      mark_valid_location_for_stdc_pragma (سچ);
      c_parser_pragma (parser, pragma_external, تہی, NULL_درخت);
      mark_valid_location_for_stdc_pragma (جھوٹ);
      توڑو;
    حالت CPP_PLUS:
    حالت CPP_MINUS:
      اگر (c_dialect_objc ())
	{
	  c_parser_objc_طریقہ_definition (parser);
	  توڑو;
	}
      /* Else fall through, and yield a syntax error trying to parse
	 as a declaration or function definition.  */
      /* FALLTHRU */
    طےشدہ:
    decl_or_fndef:
      /* A declaration or a function definition (or, in Objective-C,
	 an @interface or @protocol with prefix attributes).  We can
	 only tell which after parsing the declaration specifiers, if
	 any, and the first declarator.  */
      c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, جھوٹ, سچ,
				     جھوٹ);
      توڑو;
    }
}

ساکن خالی c_parser_handle_directive_omp_اوصاف (درخت &, vec<c_token> *&,
						      vec<c_token> *);
ساکن خالی c_اختتام_omp_declare_simd (c_parser *, درخت, درخت, vec<c_token> *);
ساکن خالی c_اختتام_oacc_routine (ساخت oacc_routine_ڈیٹا *, درخت, منطقی);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

ساکن خالی
جوڑو_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  اگر (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    واپس;

  درخت stmt = build0 (DEBUG_BEGIN_STMT, void_type_گرہ);
  سیٹ_اظہاریہ_LOCATION (stmt, loc);
  جوڑو_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

ساکن درخت
handle_assume_attribute (location_t یہاں, درخت attrs, منطقی nested)
{
  اگر (nested)
    برائے (درخت attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", درخت_CHAIN (attr)))
      {
	درخت دلائل = درخت_قدر (attr);
	صحیح nargs = list_لمبائی (دلائل);
	اگر (nargs != 1)
	  {
	    error_at (یہاں, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (یہاں, "expected %i, found %i", 1, nargs);
	  }
	ورنہ
	  {
	    درخت arg = درخت_قدر (دلائل);
	    arg = c_objc_common_truthvalue_conversion (یہاں, arg);
	    arg = c_fully_fold (arg, جھوٹ, تہی);
	    اگر (arg != error_mark_گرہ)
	      {
		درخت fn = build_call_اظہاریہ_اندرونی_loc (یہاں, IFN_ASSUME,
							void_type_گرہ, 1,
							arg);
		جوڑو_stmt (fn);
	      }
	  }
      }
  ورنہ
    pedwarn (یہاں, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  واپس remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

ساکن خالی
c_parser_maybe_reclassify_token (c_parser *parser)
{
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      اگر (token->id_قسم == C_ID_ID || token->id_قسم == C_ID_TYPENAME)
	{
	  درخت decl = lookup_name (token->قدر);

	  token->id_قسم = C_ID_ID;
	  اگر (decl)
	    {
	      اگر (درخت_رمز (decl) == TYPE_DECL)
		token->id_قسم = C_ID_TYPENAME;
	    }
	  ورنہ اگر (c_dialect_objc ())
	    {
	      درخت objc_interface_decl = objc_is_class_name (token->قدر);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      اگر (objc_interface_decl)
		{
		  token->قدر = objc_interface_decl;
		  token->id_قسم = C_ID_CLASSNAME;
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

ساکن درخت
c_parser_declaration_or_fndef (c_parser *parser, منطقی fndef_ok,
			       منطقی static_assert_ok, منطقی خالی_خانے_ok,
			       منطقی nested, منطقی آغاز_attr_ok,
			       منطقی simple_ok,
			       درخت *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       منطقی have_attrs /* = false */,
			       درخت attrs /* = NULL_TREE */,
			       ساخت oacc_routine_ڈیٹا *oacc_routine_ڈیٹا
			       /* = NULL */,
			       منطقی *fallthru_attr_p /* = NULL */)
{
  ساخت c_declspecs *specs;
  درخت سابقہ_attrs;
  درخت all_سابقہ_attrs;
  منطقی diagnosed_no_specs = جھوٹ;
  location_t یہاں = c_parser_peek_token (parser)->location;
  درخت نتیجہ = NULL_درخت;

  جوڑو_debug_begin_stmt (c_parser_peek_token (parser)->location);

  اگر (static_assert_ok
      && c_parser_اگلا_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      واپس نتیجہ;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  اگر (have_attrs)
    {
      declspecs_جوڑو_attrs (یہاں, specs, attrs);
      specs->non_std_attrs_نظر_آیا_p = جھوٹ;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  اگر (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_قسم == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->قدر)))
    {
      درخت name = c_parser_peek_token (parser)->قدر;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (یہاں);
      اگر (لیبل_exists_p (ریکارڈ_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.جوڑو_fixit_داخل_کرو_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      ورنہ اگر (لیبل_exists_p (UNION_TYPE, name))
	{
	  richloc.جوڑو_fixit_داخل_کرو_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      ورنہ اگر (لیبل_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.جوڑو_fixit_داخل_کرو_before ("enum ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<enum%> keyword to refer to the type",
		    name);
	}
      ورنہ
	{
	  auto_diagnostic_گروہ d;
	  name_hint hint = lookup_name_fuzzy (name, FUZZY_LOOKUP_TYPENAME,
					      یہاں);
	  اگر (ثابت حرف *suggestion = hint.suggestion ())
	    {
	      richloc.جوڑو_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			name, suggestion);
	    }
	  ورنہ
	    error_at (یہاں, "unknown type name %qE", name);
	}

      /* Parse declspecs normally to get a correct pointer type, but avoid
         a further "fails to be a type name" error.  Refuse nested functions
         since it is not how the user likely wants us to recover.  */
      c_parser_peek_token (parser)->type = CPP_KEYWORD;
      c_parser_peek_token (parser)->keyword = RID_VOID;
      c_parser_peek_token (parser)->قدر = error_mark_گرہ;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  اگر (c_parser_nth_token_starts_std_اوصاف (parser, 1))
    have_attrs = سچ;

  c_parser_declspecs (parser, specs, سچ, سچ, آغاز_attr_ok,
		      سچ, سچ, آغاز_attr_ok, سچ, cla_nonabstract_decl);
  اگر (parser->error)
    {
      c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
      واپس نتیجہ;
    }
  اگر (nested && !specs->declspecs_نظر_آیا_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
      واپس نتیجہ;
    }

  اختتام_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  اگر (specs->typespec_قسم == ctsk_tagdef)
    verify_counted_by_for_چوٹی_anonymous_type (specs->type);

  منطقی gnu_auto_type_p = specs->typespec_لفظ == cts_auto_type;
  منطقی std_auto_type_p = specs->c23_auto_p;
  منطقی any_auto_type_p = gnu_auto_type_p || std_auto_type_p;
  gcc_assert (!(gnu_auto_type_p && std_auto_type_p));
  ثابت حرف *auto_type_keyword = gnu_auto_type_p ? "__auto_type" : "auto";
  اگر (specs->constexpr_p)
    {
      /* An underspecified declaration may not declare tags or members
	 or structures or unions; it is undefined behavior to declare
	 the members of an enumeration.  Where the structure, union or
	 enumeration type is declared within an initializer, this is
	 diagnosed elsewhere.  Diagnose here the case of declaring
	 such a type in the type specifiers of a constexpr
	 declaration.  */
      انتخاب (specs->typespec_قسم)
	{
	حالت ctsk_tagfirstref:
	حالت ctsk_tagfirstref_attrs:
	  error_at (یہاں, "%qT declared in underspecified object declaration",
		    specs->type);
	  توڑو;

	حالت ctsk_tagdef:
	  error_at (یہاں, "%qT defined in underspecified object declaration",
		    specs->type);
	  توڑو;

	طےشدہ:
	  توڑو;
	}
    }

  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
    {
      منطقی handled_assume = جھوٹ;
      اگر (specs->attrs
	  && !nested
	  && specs->typespec_قسم == ctsk_none
	  && c_parser_handle_statement_omp_اوصاف (parser, specs->attrs,
						       تہی))
	{
	  اگر (specs->attrs)
	    c_warn_غیر_مستعمل_اوصاف (specs->attrs);
	  جب (parser->اندر_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_اگلا_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, تہی, NULL_درخت);
	    }
	  c_parser_consume_token (parser);
	  واپس نتیجہ;
	}
      اگر (specs->typespec_قسم == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = سچ;
	  specs->attrs
	    = handle_assume_attribute (یہاں, specs->attrs, nested);
	}
      اگر (any_auto_type_p)
	error_at (یہاں, "%qs in empty declaration", auto_type_keyword);
      ورنہ اگر (specs->typespec_قسم == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  اگر (fallthru_attr_p != تہی)
	    *fallthru_attr_p = سچ;
	  اگر (nested)
	    {
	      درخت fn = build_call_اظہاریہ_اندرونی_loc (یہاں, IFN_FALLTHROUGH,
						      void_type_گرہ, 0);
	      جوڑو_stmt (fn);
	    }
	  ورنہ
	    pedwarn (یہاں, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      ورنہ اگر (خالی_خانے_ok
	       && !(have_attrs && specs->non_std_attrs_نظر_آیا_p)
	       && !handled_assume)
	shadow_لیبل (specs);
      ورنہ
	{
	  shadow_لیبل_warned (specs, 1);
	  اگر (!handled_assume)
	    pedwarn (یہاں, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      اگر (specs->اظہاریہ)
	جوڑو_stmt (fold_convert (void_type_گرہ, specs->اظہاریہ));
      c_parser_consume_token (parser);
      اگر (oacc_routine_ڈیٹا)
	c_اختتام_oacc_routine (oacc_routine_ڈیٹا, NULL_درخت, جھوٹ);
      واپس نتیجہ;
    }
  ورنہ اگر (specs->typespec_قسم == ctsk_none
	   && nested
	   /* Only parse __attribute__((musttail)) when called from
	      c_parser_compound_statement_nostart.  This certainly isn't
	      a declaration in that case, but we don't do tentative parsing
	      of GNU attributes right now.  */
	   && fallthru_attr_p
	   && c_parser_اگلا_token_is_keyword (parser, RID_RETURN))
    {
      attr_state astate = {};
      specs->attrs = c_parser_handle_musttail (parser, specs->attrs, astate);
      اگر (astate.musttail_p)
	{
	  اگر (specs->attrs)
	    {
	      auto_urlify_اوصاف sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, تہی, NULL_درخت, تہی,
					   astate);
	  واپس نتیجہ;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  اگر (خالی_خانے_ok
      && specs->typespec_قسم == ctsk_tagdef
      && c_parser_اگلا_token_starts_declspecs (parser)
      && !c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = جھوٹ;
      shadow_لیبل_warned (specs, 1);
      واپس نتیجہ;
    }
  ورنہ اگر (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      انتخاب (c_parser_peek_token (parser)->type)
	{
	  حالت CPP_PLUS:
	  حالت CPP_MINUS:
	    اگر (c_parser_objc_diagnose_bad_element_سابقہ (parser, specs))
	      واپس نتیجہ;
	    اگر (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_درخت;
	      }
	    اگر (fndef_ok)
	      c_parser_objc_طریقہ_definition (parser);
	    ورنہ
	      c_parser_objc_methodproto (parser);
	    واپس نتیجہ;
	    توڑو;
	  طےشدہ:
	    توڑو;
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
	    اگر (c_parser_objc_diagnose_bad_element_سابقہ (parser, specs))
	      واپس نتیجہ;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    واپس نتیجہ;
	  }
	  توڑو;
	حالت RID_AT_IMPLEMENTATION:
	  {
	    اگر (c_parser_objc_diagnose_bad_element_سابقہ (parser, specs))
	      واپس نتیجہ;
	    اگر (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_درخت;
	      }
	    c_parser_objc_class_definition (parser, NULL_درخت);
	    واپس نتیجہ;
	  }
	  توڑو;
	حالت RID_AT_PROTOCOL:
	  {
	    اگر (c_parser_objc_diagnose_bad_element_سابقہ (parser, specs))
	      واپس نتیجہ;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    واپس نتیجہ;
	  }
	  توڑو;
	حالت RID_AT_ALIAS:
	حالت RID_AT_CLASS:
	حالت RID_AT_انتہا:
	حالت RID_AT_PROPERTY:
	  اگر (specs->attrs)
	    {
	      c_parser_error (parser, "unexpected attribute");
	      specs->attrs = تہی;
	    }
	  توڑو;
	طےشدہ:
	  توڑو;
	}
    }
  ورنہ اگر (attribute_fallthrough_p (specs->attrs))
    warning_at (یہاں, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  ورنہ اگر (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (یہاں, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_اوصاف (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  سابقہ_attrs = specs->attrs;
  all_سابقہ_attrs = سابقہ_attrs;
  specs->attrs = NULL_درخت;
  منطقی مزید_than_one_decl = جھوٹ;
  جب (سچ)
    {
      ساخت c_declarator *declarator;
      منطقی dummy = جھوٹ;
      timevar_id_t tv;
      درخت fnbody = NULL_درخت;
      درخت underspec_name = NULL_درخت;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_قسم != ctsk_none,
					C_DTR_معمول, &dummy);
      اگر (declarator == تہی)
	{
	  اگر (omp_declare_simd_clauses)
	    c_اختتام_omp_declare_simd (parser, NULL_درخت, NULL_درخت,
				       omp_declare_simd_clauses);
	  اگر (oacc_routine_ڈیٹا)
	    c_اختتام_oacc_routine (oacc_routine_ڈیٹا, NULL_درخت, جھوٹ);
	  /* This check is here purely to improve the diagnostic.  */
	  اگر (!simple_ok)
	    c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
	  واپس نتیجہ;
	}
      اگر (flag_openmp || flag_openmp_simd)
	{
	  ساخت c_declarator *d = declarator;
	  جب (d->قسم != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = تہی;
	  c_parser_handle_directive_omp_اوصاف (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      اگر (gnu_auto_type_p && declarator->قسم != cdk_id)
	{
	  error_at (یہاں,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
	  واپس نتیجہ;
	}
      اگر (std_auto_type_p)
	{
	  ساخت c_declarator *d = declarator;
	  جب (d->قسم == cdk_attrs)
	    d = d->declarator;
	  اگر (d->قسم != cdk_id)
	    {
	      error_at (یہاں,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
	      واپس نتیجہ;
	    }
	  underspec_name = d->u.id.id;
	}
      ورنہ اگر (specs->constexpr_p)
	{
	  ساخت c_declarator *d = declarator;
	  جب (d->قسم != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      اگر (c_parser_اگلا_token_is (parser, CPP_EQ)
	  || c_parser_اگلا_token_is (parser, CPP_COMMA)
	  || c_parser_اگلا_token_is (parser, CPP_SEMICOLON)
	  || c_parser_اگلا_token_is_keyword (parser, RID_ASM)
	  || c_parser_اگلا_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_اگلا_token_is_keyword (parser, RID_اندر))
	{
	  درخت asm_name = NULL_درخت;
	  درخت postfix_attrs = NULL_درخت;
	  اگر (!diagnosed_no_specs && !specs->declspecs_نظر_آیا_p)
	    {
	      diagnosed_no_specs = سچ;
	      pedwarn (یہاں, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = جھوٹ;
	  اگر (c_parser_اگلا_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_اظہاریہ (parser);
	  اگر (c_parser_اگلا_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_اوصاف (parser);
	      اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (یہاں, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
		  واپس نتیجہ;
		}
	    }
	  اگر (c_parser_اگلا_token_is (parser, CPP_EQ))
	    {
	      درخت d;
	      ساخت c_اظہاریہ init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      اگر (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (سطر_جدول, init_loc);
		  غیرعلامتی صحیح underspec_state = 0;
		  اگر (std_auto_type_p)
		    underspec_state =
		      آغاز_underspecified_init (init_loc, underspec_name);
		  آغاز_init (NULL_درخت, asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_رمز_type flag_sanitize_save = flag_sanitize;
		  اگر (nested && !خالی_خانے_ok)
		    flag_sanitize = 0;
		  init = c_parser_اظہاریہ_no_commas (parser, تہی);
		  اگر (std_auto_type_p)
		    اختتام_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  اگر (gnu_auto_type_p
		      && درخت_رمز (init.قدر) == COMPONENT_REF
		      && DECL_C_ثنائی_ہندسہ_میدان (درخت_عملیہ (init.قدر, 1)))
		    error_at (یہاں,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_مقصد_rvalue (init_loc, init, سچ, سچ,
						   سچ);
		  درخت init_type = درخت_TYPE (init.قدر);
		  منطقی vm_type = c_type_variably_modified_p (init_type);
		  اگر (vm_type)
		    init.قدر = save_اظہاریہ (init.قدر);
		  اختتام_init ();
		  specs->typespec_قسم = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = سچ;
		  specs->type = init_type;
		  اگر (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_اوصاف (specs->type,
						  specs->postfix_attrs);
		      decl_اوصاف (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_درخت;
		    }
		  اگر (vm_type)
		    {
		      منطقی maybe_const = سچ;
		      درخت type_اظہاریہ = c_fully_fold (init.قدر, جھوٹ,
						     &maybe_const);
		      specs->اظہاریہ_const_operands &= maybe_const;
		      اگر (specs->اظہاریہ)
			specs->اظہاریہ = build2 (COMPOUND_اظہاریہ,
					      درخت_TYPE (type_اظہاریہ),
					      specs->اظہاریہ, type_اظہاریہ);
		      ورنہ
			specs->اظہاریہ = type_اظہاریہ;
		    }
		  d = آغاز_decl (declarator, specs, سچ,
				  chainon (postfix_attrs, all_سابقہ_attrs));
		  اگر (!d)
		    d = error_mark_گرہ;
		  اگر (omp_declare_simd_clauses)
		    c_اختتام_omp_declare_simd (parser, d, NULL_درخت,
					       omp_declare_simd_clauses);
		  اگر (!omp_dsimd_idattr_clauses.is_خالی_خانے ())
		    c_اختتام_omp_declare_simd (parser, d, NULL_درخت,
					       &omp_dsimd_idattr_clauses);
		}
	      ورنہ
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (سطر_جدول, init_loc);
		  غیرعلامتی صحیح underspec_state = 0;
		  اگر (specs->constexpr_p)
		    underspec_state =
		      آغاز_underspecified_init (init_loc, underspec_name);
		  d = آغاز_decl (declarator, specs, سچ,
				  chainon (postfix_attrs,
					   all_سابقہ_attrs),
				  !specs->constexpr_p);
		  اگر (!d)
		    d = error_mark_گرہ;
		  اگر (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_اختتام_omp_declare_simd (parser, d, NULL_درخت,
					       omp_declare_simd_clauses);
		  اگر (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_خالی_خانے ())
		    c_اختتام_omp_declare_simd (parser, d, NULL_درخت,
					       &omp_dsimd_idattr_clauses);
		  آغاز_init (d, asm_name,
			      درخت_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_رمز_type flag_sanitize_save = flag_sanitize;
		  اگر (درخت_رمز (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  اگر (specs->constexpr_p)
		    {
		      اختتام_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      اگر (omp_declare_simd_clauses)
			c_اختتام_omp_declare_simd (parser, d, NULL_درخت,
						   omp_declare_simd_clauses);
		  اگر (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_خالی_خانے ())
		    c_اختتام_omp_declare_simd (parser, d, NULL_درخت,
					       &omp_dsimd_idattr_clauses);
		    }
		  اختتام_init ();
		}
	      اگر (oacc_routine_ڈیٹا)
		c_اختتام_oacc_routine (oacc_routine_ڈیٹا, d, جھوٹ);
	      اگر (d != error_mark_گرہ)
		{
		  maybe_warn_string_init (init_loc, درخت_TYPE (d), init);
		  اختتام_decl (d, init_loc, init.قدر,
			       init.original_type, asm_name);
		  نتیجہ = d;
		}
	    }
	  ورنہ
	    {
	      اگر (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (یہاں,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
		  واپس نتیجہ;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      درخت attrs = chainon (postfix_attrs, all_سابقہ_attrs);
	      درخت d = آغاز_decl (declarator, specs, جھوٹ, attrs, سچ,
				   &lastloc);
	      اگر (d && درخت_رمز (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  ثابت ساخت c_declarator *decl = declarator;
		  ثابت ساخت c_declarator *آخری_non_id_attrs = تہی;

		  جب (decl)
		    انتخاب (decl->قسم)
		      {
		      حالت cdk_array:
		      حالت cdk_function:
		      حالت cdk_اشارہ_گر:
			آخری_non_id_attrs = decl;
			decl = decl->declarator;
			توڑو;

		      حالت cdk_attrs:
			decl = decl->declarator;
			توڑو;

		      حالت cdk_id:
			decl = 0;
			توڑو;

		      طےشدہ:
			gcc_unreachable ();
		      }

		  /* If it exists and is cdk_function declaration whose
		     arguments have not been set yet, use its arguments.  */
		  اگر (آخری_non_id_attrs
		      && آخری_non_id_attrs->قسم == cdk_function)
		    {
		      درخت parms = آخری_non_id_attrs->u.arg_info->parms;
		      اگر (DECL_ARGUMENTS (d) == NULL_درخت
			  && DECL_INITIAL (d) == NULL_درخت)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      اگر (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_خالی_خانے ())
		{
		  درخت parms = NULL_درخت;
		  اگر (d && درخت_رمز (d) == FUNCTION_DECL)
		    {
		      ساخت c_declarator *ce = declarator;
		      جب (ce != تہی)
			اگر (ce->قسم == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    توڑو;
			  }
			ورنہ
			  ce = ce->declarator;
		    }
		  اگر (parms)
		    عارضی_store_parm_decls (d, parms);
		  اگر (omp_declare_simd_clauses)
		    c_اختتام_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  اگر (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_خالی_خانے ())
		    c_اختتام_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  اگر (parms)
		    عارضی_نکالو_parm_decls ();
		}
	      اگر (oacc_routine_ڈیٹا)
		c_اختتام_oacc_routine (oacc_routine_ڈیٹا, d, جھوٹ);
	      اگر (d)
		اختتام_decl (d, UNKNOWN_LOCATION, NULL_درخت,
			     NULL_درخت, asm_name);

	      اگر (c_parser_اگلا_token_is_keyword (parser, RID_اندر))
		{
		  اگر (d)
		    *objc_foreach_object_declaration = d;
		  ورنہ
		    *objc_foreach_object_declaration = error_mark_گرہ;
		}
	    }
	  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	    {
	      مزید_than_one_decl = سچ;
	      اگر (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (یہاں,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
		  واپس نتیجہ;
		}
	      c_parser_consume_token (parser);
	      اگر (c_parser_اگلا_token_is_keyword (parser, RID_ATTRIBUTE))
		all_سابقہ_attrs = chainon (c_parser_gnu_اوصاف (parser),
					    سابقہ_attrs);
	      ورنہ
		all_سابقہ_attrs = سابقہ_attrs;
	      جاری;
	    }
	  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
	    {
	      اگر (!simple_ok)
		c_parser_consume_token (parser);
	      واپس نتیجہ;
	    }
	  ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_اندر))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      واپس نتیجہ;
	    }
	  ورنہ
	    {
	      اگر (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      ورنہ اگر (مزید_than_one_decl)
		error_at (یہاں, "declaration in condition can only declare "
			  "a single object");
	      واپس نتیجہ;
	    }
	}
      ورنہ اگر (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (یہاں,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
	  واپس نتیجہ;
	}
      ورنہ اگر (!fndef_ok)
	{
	  اگر (simple_ok && c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  ورنہ
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
	    }
	  واپس نتیجہ;
	}
      /* Function definition (nested or otherwise).  */
      اگر (nested)
	{
	  pedwarn (یہاں, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_ڈالو_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      درخت dv_بنیاد = NULL_درخت;
      درخت dv_ctx = NULL_درخت;
      اگر (!vec_محفوظ_is_خالی_خانے (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->آخری ();
	  dv_ctx = copy_list (a.selector);
	  dv_بنیاد = omp_آغاز_variant_function (declarator, dv_ctx);
	}

      اگر (!آغاز_function (specs, declarator, all_سابقہ_attrs))
	{
	  /* At this point we've consumed:
	       declaration-specifiers declarator
	     and the next token isn't CPP_EQ, CPP_COMMA, CPP_SEMICOLON,
	     RID_ASM, RID_ATTRIBUTE, or RID_IN,
	     but the
	       declaration-specifiers declarator
	     aren't grokkable as a function definition, so we have
	     an error.  */
	  gcc_assert (!c_parser_اگلا_token_is (parser, CPP_SEMICOLON));
	  اگر (c_parser_اگلا_token_starts_declspecs (parser))
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
	      parser->error = جھوٹ;
	    }
	  ورنہ
	    {
	      /* This can appear in many cases looking nothing like a
		 function definition, so we don't give a more specific
		 error suggesting there was one.  */
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			      "or %<__attribute__%>");
	    }
	  اگر (nested)
	    c_نکالو_function_context ();
	  توڑو;
	}

      اگر (DECL_DECLARED_INLINE_P (current_function_decl))
        tv = TV_PARSE_INLINE;
      ورنہ
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
      جب (c_parser_اگلا_token_is_not (parser, CPP_EOF)
	     && c_parser_اگلا_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, جھوٹ, جھوٹ, جھوٹ,
				       سچ, جھوٹ, جھوٹ);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      اگر (omp_declare_simd_clauses)
	c_اختتام_omp_declare_simd (parser, current_function_decl, NULL_درخت,
				   omp_declare_simd_clauses);
      اگر (!omp_dsimd_idattr_clauses.is_خالی_خانے ())
	c_اختتام_omp_declare_simd (parser, current_function_decl, NULL_درخت,
				   &omp_dsimd_idattr_clauses);
      اگر (oacc_routine_ڈیٹا)
	c_اختتام_oacc_routine (oacc_routine_ڈیٹا, current_function_decl, سچ);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_آغاز_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      اگر (dv_بنیاد && current_function_decl != error_mark_گرہ)
	{
	  omp_begin_declare_variant_map_اندراج e
	    = { current_function_decl, dv_بنیاد, dv_ctx };
	  vec_محفوظ_ڈالو (omp_begin_declare_variant_map, e);
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
	  ڈالو_scope ();
	  نکالو_scope ();

	  اختتام_function (endloc);
	  واپس نتیجہ;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      ورنہ اگر (specs->declspec_il != cdil_none)
	{
	  منطقی saved = اندر_late_ثنائی_op;
	  اندر_late_ثنائی_op = سچ;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->اندراج_bb_گنتی);
	  اندر_late_ثنائی_op = saved;
	}
      ورنہ
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
	  جوڑو_stmt (fnbody);
	  اختتام_function (endloc);
	  c_نکالو_function_context ();
	  جوڑو_stmt (build_stmt (DECL_ماخذ_LOCATION (decl), DECL_اظہاریہ, decl));
	}
      ورنہ اگر (nested)
	{
	  اگر (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  ورنہ
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  اختتام_function (endloc);
	  c_نکالو_function_context ();
	}
      ورنہ
	{
	  اگر (fnbody)
	    جوڑو_stmt (fnbody);
	  اختتام_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      اگر (specs->declspec_il != cdil_none)
	DECL_SAVED_درخت (fndecl) = NULL_درخت;

      توڑو;
    }

  واپس نتیجہ;
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

ساکن خالی
c_parser_asm_definition (c_parser *parser)
{
  location_t asm_loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  درخت asm_str = NULL_درخت;
  درخت outputs = NULL_درخت, inputs = NULL_درخت;
  اگر (!parens.require_open (parser))
    جاؤ مکمل;
  asm_str = c_parser_asm_string_literal (parser);
  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      جاؤ مکمل;
    }
  برائے (صحیح section = 0; section < 2; ++section)
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  اگر (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
	      asm_str = NULL_درخت;
	      جاؤ مکمل;
	    }
	  c_parser_consume_token (parser);
	}
      ورنہ اگر (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, جھوٹ))
	جاؤ error_close_paren;
      اگر (!c_parser_اگلا_token_is (parser, CPP_COLON)
	  && !c_parser_اگلا_token_is (parser, CPP_SCOPE)
	  && !c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	{
	  اگر (section)
	    inputs = c_parser_asm_operands (parser);
	  ورنہ
	    outputs = c_parser_asm_operands (parser);
	}
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	توڑو;
    }

  اگر (!parens.require_close (parser))
    {
      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
      asm_str = NULL_درخت;
    }

  اگر (asm_str)
    asm_str = build_asm_اظہاریہ (asm_loc, asm_str, outputs, inputs,
			      NULL_درخت, NULL_درخت, جھوٹ, جھوٹ);
مکمل:
  اگر (asm_str)
    symtab->finalize_toplevel_asm (asm_str);
  c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse a static assertion (C11 6.7.10).

   static_assert-declaration:
     static_assert-declaration-no-semi ;
*/

ساکن خالی
c_parser_static_assert_declaration (c_parser *parser)
{
  c_parser_static_assert_declaration_no_semi (parser);
  اگر (parser->error
      || !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
}

/* Parse a static assertion (C11 6.7.10), without the trailing
   semicolon.

   static_assert-declaration-no-semi:
     _Static_assert ( constant-expression , string-literal )

   C23:
   static_assert-declaration-no-semi:
     _Static_assert ( constant-expression )
*/

ساکن خالی
c_parser_static_assert_declaration_no_semi (c_parser *parser)
{
  location_t assert_loc, قدر_loc;
  درخت قدر;
  درخت string = NULL_درخت;

  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_STATIC_ASSERT));
  درخت spelling = c_parser_peek_token (parser)->قدر;
  assert_loc = c_parser_peek_token (parser)->location;
  اگر (flag_isoc99)
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  ورنہ
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  c_parser_consume_token (parser);
  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس;
  location_t قدر_tok_loc = c_parser_peek_token (parser)->location;
  قدر = convert_lvalue_مقصد_rvalue (قدر_tok_loc,
				    c_parser_اظہاریہ_no_commas (parser, تہی),
				    سچ, سچ).قدر;
  قدر_loc = اظہاریہ_LOC_OR_LOC (قدر, قدر_tok_loc);
  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_STRING:
	حالت CPP_STRING16:
	حالت CPP_STRING32:
	حالت CPP_WSTRING:
	حالت CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, جھوٹ, سچ).قدر;
	  توڑو;
	طےشدہ:
	  c_parser_error (parser, "expected string literal");
	  واپس;
	}
    }
  ورنہ اگر (flag_isoc11)
    /* If pedantic for pre-C11, the use of _Static_assert itself will
       have been diagnosed, so do not also diagnose the use of this
       new C23 feature of _Static_assert.  */
    pedwarn_c11 (assert_loc, OPT_Wpedantic,
		 "ISO C11 does not support omitting the string in "
		 "%qE", spelling);
  parens.require_close (parser);

  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (قدر)))
    {
      error_at (قدر_loc, "expression in static assertion is not an integer");
      واپس;
    }
  اگر (درخت_رمز (قدر) != INTEGER_CST)
    {
      قدر = c_fully_fold (قدر, جھوٹ, تہی);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (قدر);
      اگر (درخت_رمز (قدر) == INTEGER_CST)
	pedwarn (قدر_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  اگر (درخت_رمز (قدر) != INTEGER_CST)
    {
      error_at (قدر_loc, "expression in static assertion is not constant");
      واپس;
    }
  constant_عبارت_warning (قدر);
  اگر (integer_zerop (قدر))
    {
      اگر (string)
	error_at (assert_loc, "static assertion failed: %E", string);
      ورنہ
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
رجسٹر
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

خالی
c_parser_declspecs (c_parser *parser, ساخت c_declspecs *specs,
		    منطقی scspec_ok, منطقی typespec_ok, منطقی آغاز_attr_ok,
		    منطقی alignspec_ok, منطقی auto_type_ok,
		    منطقی آغاز_std_attr_ok, منطقی انتہا_std_attr_ok,
		    شمار c_lookahead_قسم la)
{
  منطقی attrs_ok = آغاز_attr_ok;
  منطقی نظر_آیا_type = specs->typespec_قسم != ctsk_none;

  اگر (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  اگر (آغاز_std_attr_ok
      && c_parser_nth_token_starts_std_اوصاف (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_نظر_آیا_p);
      location_t loc = c_parser_peek_token (parser)->location;
      درخت attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_جوڑو_attrs (loc, specs, attrs);
      specs->non_std_attrs_نظر_آیا_p = جھوٹ;
    }

  جب (c_parser_اگلا_token_is (parser, CPP_NAME)
	 || c_parser_اگلا_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_اگلا_token_is (parser, CPP_LESS)))
    {
      ساخت c_typespec t;
      درخت attrs;
      درخت align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      اگر ((!typespec_ok || specs->typespec_قسم == ctsk_tagdef)
	  && c_parser_اگلا_علامات_آغاز_typename (parser, la)
	  && !c_parser_اگلا_token_is_qualifier (parser)
	  && !c_parser_اگلا_token_is_keyword (parser, RID_ALIGNAS))
	توڑو;

      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  درخت قدر = name_token->قدر;
	  c_id_قسم قسم = name_token->id_قسم;

	  اگر (قسم == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_پہلا_ADDR_SPACE;
	      declspecs_جوڑو_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = سچ;
	      جاری;
	    }

	  gcc_assert (!c_parser_اگلا_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  اگر (نظر_آیا_type || !c_parser_اگلا_علامات_آغاز_typename (parser, la))
	    توڑو;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  نظر_آیا_type = سچ;
	  attrs_ok = سچ;
	  اگر (قسم == C_ID_ID)
	    {
	      auto_diagnostic_گروہ d;
	      name_hint hint = lookup_name_fuzzy (قدر, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      اگر (ثابت حرف *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.جوڑو_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    قدر, suggestion);
		}
	      ورنہ
		error_at (loc, "unknown type name %qE", قدر);
	      t.قسم = ctsk_typedef;
	      t.spec = error_mark_گرہ;
	    }
	  ورنہ اگر (قسم == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_اگلا_token_is_not (parser, CPP_LESS)))
	    {
	      t.قسم = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (قدر);
	    }
	  ورنہ
	    {
	      درخت proto = NULL_درخت;
	      gcc_assert (c_dialect_objc ());
	      t.قسم = ctsk_objc;
	      اگر (c_parser_اگلا_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (قدر, proto);
	    }
	  t.اظہاریہ = NULL_درخت;
	  t.اظہاریہ_const_operands = سچ;
	  t.has_enum_type_specifier = جھوٹ;
	  declspecs_جوڑو_type (name_token->location, specs, t);
	  جاری;
	}
      اگر (c_parser_اگلا_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  درخت proto;
	  gcc_assert (c_dialect_objc ());
	  اگر (!typespec_ok || نظر_آیا_type)
	    توڑو;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.قسم = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_درخت, proto);
	  t.اظہاریہ = NULL_درخت;
	  t.اظہاریہ_const_operands = سچ;
	  t.has_enum_type_specifier = جھوٹ;
	  declspecs_جوڑو_type (loc, specs, t);
	  جاری;
	}
      gcc_assert (c_parser_اگلا_token_is (parser, CPP_KEYWORD));
      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_STATIC:
	حالت RID_EXTERN:
	حالت RID_رجسٹر:
	حالت RID_TYPEDEF:
	حالت RID_INLINE:
	حالت RID_NORETURN:
	حالت RID_AUTO:
	حالت RID_THREAD:
	حالت RID_CONSTEXPR:
	  اگر (!scspec_ok)
	    جاؤ برآمد;
	  attrs_ok = سچ;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_جوڑو_scspec (loc, specs,
				c_parser_peek_token (parser)->قدر);
	  c_parser_consume_token (parser);
	  توڑو;
	حالت RID_AUTO_TYPE:
	  اگر (!auto_type_ok)
	    جاؤ برآمد;
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
	    جاؤ برآمد;
	  attrs_ok = سچ;
	  نظر_آیا_type = سچ;
	  اگر (c_dialect_objc ())
	    parser->objc_need_raw_identifier = سچ;
	  t.قسم = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->قدر;
	  t.اظہاریہ = NULL_درخت;
	  t.اظہاریہ_const_operands = سچ;
	  t.has_enum_type_specifier = جھوٹ;
	  declspecs_جوڑو_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  توڑو;
	حالت RID_ENUM:
	  اگر (!typespec_ok)
	    جاؤ برآمد;
	  attrs_ok = سچ;
	  نظر_آیا_type = سچ;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_اختتام_TYPE, t.spec);
	  declspecs_جوڑو_type (loc, specs, t);
	  توڑو;
	حالت RID_STRUCT:
	حالت RID_UNION:
	  اگر (!typespec_ok)
	    جاؤ برآمد;
	  attrs_ok = سچ;
	  نظر_آیا_type = سچ;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_اختتام_TYPE, t.spec);
	  declspecs_جوڑو_type (loc, specs, t);
	  توڑو;
	حالت RID_TYPEOF:
	حالت RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  اگر (!typespec_ok || نظر_آیا_type)
	    جاؤ برآمد;
	  attrs_ok = سچ;
	  نظر_آیا_type = سچ;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_جوڑو_type (loc, specs, t);
	  توڑو;
	حالت RID_BITINT:
	  اگر (!typespec_ok)
	    جاؤ برآمد;
	  ورنہ
	    {
	      attrs_ok = سچ;
	      نظر_آیا_type = سچ;
	      t.قسم = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->قدر;
	      t.اظہاریہ = error_mark_گرہ;
	      t.اظہاریہ_const_operands = سچ;
	      t.has_enum_type_specifier = جھوٹ;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      اگر (parens.require_open (parser))
		{
		  c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
		  t.اظہاریہ = convert_lvalue_مقصد_rvalue (loc, اظہاریہ, سچ,
						     سچ).قدر;
		  parens.skip_until_ملا_close (parser);
		}
	      declspecs_جوڑو_type (loc, specs, t);
	    }
	  توڑو;
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
	  ورنہ
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C90 does not support the %<_Atomic%> qualifier");
	  attrs_ok = سچ;
	  درخت قدر;
	  قدر = c_parser_peek_token (parser)->قدر;
	  c_parser_consume_token (parser);
	  اگر (typespec_ok && c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      نظر_آیا_type = سچ;
	      c_parser_consume_token (parser);
	      ساخت c_type_name *type = c_parser_type_name (parser);
	      t.قسم = ctsk_typeof;
	      t.spec = error_mark_گرہ;
	      t.اظہاریہ = NULL_درخت;
	      t.اظہاریہ_const_operands = سچ;
	      t.has_enum_type_specifier = جھوٹ;
	      اگر (type != تہی)
		t.spec = groktypename (type, &t.اظہاریہ,
				       &t.اظہاریہ_const_operands);
	      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      اگر (t.spec != error_mark_گرہ)
		{
		  اگر (درخت_رمز (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  ورنہ اگر (درخت_رمز (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  ورنہ اگر (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  ورنہ
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_جوڑو_type (loc, specs, t);
	    }
	  ورنہ
	    declspecs_جوڑو_qual (loc, specs, قدر);
	  توڑو;
	حالت RID_CONST:
	حالت RID_VOLATILE:
	حالت RID_RESTRICT:
	  attrs_ok = سچ;
	  declspecs_جوڑو_qual (loc, specs, c_parser_peek_token (parser)->قدر);
	  c_parser_consume_token (parser);
	  توڑو;
	حالت RID_ATTRIBUTE:
	  اگر (!attrs_ok)
	    جاؤ برآمد;
	  attrs = c_parser_gnu_اوصاف (parser);
	  declspecs_جوڑو_attrs (loc, specs, attrs);
	  توڑو;
	حالت RID_ALIGNAS:
	  اگر (!alignspec_ok)
	    جاؤ برآمد;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_جوڑو_alignas (loc, specs, align);
	  توڑو;
	حالت RID_GIMPLE:
	  اگر (! flag_gimple)
	    error_at (loc, "%<__GIMPLE%> only valid with %<-fgimple%>");
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_gimple;
	  specs->locations[cdw_gimple] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  توڑو;
	حالت RID_RTL:
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_rtl;
	  specs->locations[cdw_rtl] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  توڑو;
	طےشدہ:
	  جاؤ برآمد;
	}
    }
 برآمد:
  اگر (انتہا_std_attr_ok
      && c_parser_nth_token_starts_std_اوصاف (parser, 1))
    specs->postfix_attrs = c_parser_std_attribute_specifier_sequence (parser);
}

/* Complain about a non-CPP_NAME within an enumerator list.  */

ساکن خالی
report_bad_enum_name (c_parser *parser)
{
  اگر (!parser->error)
    {
      c_token *token = c_parser_peek_token (parser);
      انتخاب (token->type)
	{
	طےشدہ:
	  توڑو;
	حالت CPP_CLOSE_BRACE:
	  /* Give a nicer error for "enum {}".  */
	  error_at (token->location,
		    "empty enum is invalid");
	  parser->error = سچ;
	  واپس;
	حالت CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  اگر (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_گروہ d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_اشارہ_گر (token->قدر));
	      جوڑو_note_about_new_keyword (token->location,
					  token->قدر);
	      parser->error = سچ;
	      واپس;
	    }
	  توڑو;
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

ساکن ساخت c_typespec
c_parser_enum_specifier (c_parser *parser)
{
  ساخت c_typespec ret;
  منطقی have_std_attrs;
  منطقی potential_nesting_p = جھوٹ;
  درخت std_attrs = NULL_درخت;
  درخت attrs;
  درخت ident = NULL_درخت;
  درخت fixed_underlying_type = NULL_درخت;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_اوصاف (parser, 1);
  اگر (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_اوصاف (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_سیٹ_ماخذ_position_from_token (c_parser_peek_token (parser));
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->قدر;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  اگر (c_parser_اگلا_token_is (parser, CPP_COLON)
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
	  ret = parser_xref_لیبل (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, سچ);
	  اگر (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_درخت == TYPE_اقدار (ret.spec);
	}
      ورنہ
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_درخت;
	  ret.قسم = ctsk_tagdef;
	  ret.اظہاریہ = NULL_درخت;
	  ret.اظہاریہ_const_operands = سچ;
	  ret.has_enum_type_specifier = سچ;
	}
      c_parser_consume_token (parser);
      ساخت c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, جھوٹ, سچ, جھوٹ, جھوٹ, جھوٹ,
			  جھوٹ, سچ, cla_prefer_id);
      اختتام_declspecs (specs);
      اگر (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      ورنہ اگر (درخت_رمز (specs->type) != INTEGER_TYPE
	       && درخت_رمز (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || درخت_رمز (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_گرہ;
	}
      ورنہ اگر (specs->restrict_p)
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
	      TYPE_MIN_قدر (ret.spec) =
		TYPE_MIN_قدر (fixed_underlying_type);
	      TYPE_MAX_قدر (ret.spec) =
		TYPE_MAX_قدر (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      سیٹ_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_سائز (ret.spec) = NULL_درخت;
	      TYPE_PRECISION (ret.spec) =
		TYPE_PRECISION (fixed_underlying_type);
	      ENUM_UNDERLYING_TYPE (ret.spec) = fixed_underlying_type;
	      layout_type (ret.spec);
	    }
	  ورنہ اگر (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
		   && !comptypes (fixed_underlying_type,
				  ENUM_UNDERLYING_TYPE (ret.spec)))
	    {
	      error_at (enum_loc, "%<enum%> underlying type incompatible with "
			"previous declaration");
	      fixed_underlying_type = ENUM_UNDERLYING_TYPE (ret.spec);
	    }
	}
    }
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      ساخت c_enum_contents the_enum;
      درخت type;
      درخت postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      درخت اقدار;
      timevar_ڈالو (TV_PARSE_ENUM);
      type = آغاز_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      اقدار = NULL_درخت;
      c_parser_consume_token (parser);
      جب (سچ)
	{
	  درخت enum_id;
	  درخت enum_قدر;
	  درخت enum_decl;
	  منطقی نظر_آیا_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, قدر_loc;
	  اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_ملا (parser, CPP_CLOSE_BRACE, تہی);
	      اقدار = error_mark_گرہ;
	      توڑو;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->قدر;
	  /* Set the location in case we create a decl now.  */
	  c_parser_سیٹ_ماخذ_position_from_token (token);
	  decl_loc = قدر_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  درخت std_attrs = NULL_درخت;
	  اگر (c_parser_nth_token_starts_std_اوصاف (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  درخت enum_attrs = chainon (std_attrs,
				     c_parser_gnu_اوصاف (parser));
	  اگر (c_parser_اگلا_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      قدر_loc = c_parser_peek_token (parser)->location;
	      enum_قدر = convert_lvalue_مقصد_rvalue (قدر_loc,
						     (c_parser_اظہاریہ_no_commas
						      (parser, تہی)),
						     سچ, سچ).قدر;
	    }
	  ورنہ
	    enum_قدر = NULL_درخت;
	  enum_decl = build_enumerator (decl_loc, قدر_loc,
					&the_enum, enum_id, enum_قدر);
	  اگر (enum_attrs)
	    decl_اوصاف (&درخت_PURPOSE (enum_decl), enum_attrs, 0);
	  درخت_CHAIN (enum_decl) = اقدار;
	  اقدار = enum_decl;
	  نظر_آیا_comma = جھوٹ;
	  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      نظر_آیا_comma = سچ;
	      c_parser_consume_token (parser);
	    }
	  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      اگر (نظر_آیا_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      توڑو;
	    }
	  اگر (!نظر_آیا_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_ملا (parser, CPP_CLOSE_BRACE, تہی);
	      اقدار = error_mark_گرہ;
	      توڑو;
	    }
	}
      postfix_attrs = c_parser_gnu_اوصاف (parser);
      ret.spec = اختتام_enum (type, nreverse (اقدار),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.قسم = ctsk_tagdef;
      ret.اظہاریہ = NULL_درخت;
      ret.اظہاریہ_const_operands = سچ;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_درخت;
      timevar_نکالو (TV_PARSE_ENUM);
      واپس ret;
    }
  ورنہ اگر (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_گرہ;
      ret.قسم = ctsk_tagref;
      ret.اظہاریہ = NULL_درخت;
      ret.اظہاریہ_const_operands = سچ;
      ret.has_enum_type_specifier = جھوٹ;
      واپس ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  اگر (have_std_attrs && c_parser_اگلا_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  اگر (fixed_underlying_type == NULL_درخت)
    {
      ret = parser_xref_لیبل (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
			     std_attrs, جھوٹ);
      /* In ISO C, enumerated types without a fixed underlying type
	 can be referred to only if already defined.  */
      اگر (pedantic && !COMPLETE_TYPE_P (ret.spec))
	{
	  gcc_assert (ident);
	  pedwarn (enum_loc, OPT_Wpedantic,
		   "ISO C forbids forward references to %<enum%> types");
	}
    }
  واپس ret;
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
خالی_خانے
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

ساکن ساخت c_typespec
c_parser_struct_or_union_specifier (c_parser *parser)
{
  ساخت c_typespec ret;
  منطقی have_std_attrs;
  درخت std_attrs = NULL_درخت;
  درخت attrs;
  درخت ident = NULL_درخت;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  شمار درخت_رمز_2 رمز;
  انتخاب (c_parser_peek_token (parser)->keyword)
    {
    حالت RID_STRUCT:
      رمز = ریکارڈ_TYPE;
      توڑو;
    حالت RID_UNION:
      رمز = UNION_TYPE;
      توڑو;
    طےشدہ:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_اوصاف (parser, 1);
  اگر (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_اوصاف (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_سیٹ_ماخذ_position_from_token (c_parser_peek_token (parser));

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->قدر;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      جماعت c_struct_parse_info *struct_info;
      درخت type = آغاز_struct (struct_loc, رمز, ident, &struct_info);
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
      درخت اظہاریہ = تہی;
      timevar_ڈالو (TV_PARSE_STRUCT);
      contents = NULL_درخت;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      اگر (c_parser_اگلا_token_is_keyword (parser, RID_AT_DEFS))
	{
	  درخت name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  اگر (!parens.require_open (parser))
	    جاؤ انتہا_at_defs;
	  اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_قسم == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->قدر;
	      c_parser_consume_token (parser);
	    }
	  ورنہ
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
	      جاؤ انتہا_at_defs;
	    }
	  parens.skip_until_ملا_close (parser);
	  contents = nreverse (objc_get_class_ivars (name));
	}
    انتہا_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      جب (سچ)
	{
	  درخت decls;
	  /* Parse any stray semicolon.  */
	  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
	    {
	      location_t semicolon_loc
		= c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (semicolon_loc);
	      richloc.جوڑو_fixit_remove ();
	      pedwarn (&richloc, OPT_Wpedantic,
		       "extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      جاری;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      توڑو;
	    }
	  /* Accept #pragmas at struct scope.  */
	  اگر (c_parser_اگلا_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, تہی, NULL_درخت);
	      جاری;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &اظہاریہ);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  ورنہ
	    {
	      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      ورنہ اگر (parser->error
		       || !c_parser_اگلا_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_ملا (parser, CPP_CLOSE_BRACE, تہی);
		  توڑو;
		}

	      /* If we come here, we have already emitted an error
		 for an expected `;', identifier or `(', and we also
	         recovered already.  Go on with the next field. */
	    }
	}
      postfix_attrs = c_parser_gnu_اوصاف (parser);
      ret.spec = اختتام_struct (struct_loc, type, nreverse (contents),
				chainon (std_attrs,
					 chainon (attrs, postfix_attrs)),
				struct_info, &اظہاریہ);
      ret.قسم = ctsk_tagdef;
      ret.اظہاریہ = اظہاریہ;
      ret.اظہاریہ_const_operands = سچ;
      ret.has_enum_type_specifier = جھوٹ;
      timevar_نکالو (TV_PARSE_STRUCT);
      واپس ret;
    }
  ورنہ اگر (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_گرہ;
      ret.قسم = ctsk_tagref;
      ret.اظہاریہ = NULL_درخت;
      ret.اظہاریہ_const_operands = سچ;
      ret.has_enum_type_specifier = جھوٹ;
      واپس ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  اگر (have_std_attrs && c_parser_اگلا_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_لیبل (ident_loc, رمز, ident, have_std_attrs, std_attrs,
			 جھوٹ);
  واپس ret;
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

ساکن درخت
c_parser_struct_declaration (c_parser *parser, درخت *اظہاریہ)
{
  ساخت c_declspecs *specs;
  درخت سابقہ_attrs;
  درخت all_سابقہ_attrs;
  درخت decls;
  location_t decl_loc;
  اگر (c_parser_اگلا_token_is_keyword (parser, RID_EXTENSION))
    {
      صحیح ext;
      درخت decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, اظہاریہ);
      restore_extension_diagnostics (ext);
      واپس decl;
    }
  اگر (c_parser_اگلا_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      واپس NULL_درخت;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, جھوٹ, سچ, سچ,
		      سچ, جھوٹ, سچ, سچ, cla_nonabstract_decl);
  اگر (parser->error)
    واپس NULL_درخت;
  اگر (!specs->declspecs_نظر_آیا_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      واپس NULL_درخت;
    }
  اختتام_declspecs (specs);
  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON)
      || c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
    {
      درخت ret;
      اگر (specs->typespec_قسم == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_لیبل_warned (specs, pedantic);
	  ret = NULL_درخت;
	}
      ورنہ
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  درخت attrs = تہی;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_درخت), specs,
			   NULL_درخت, &attrs, اظہاریہ);
	  اگر (ret)
	    decl_اوصاف (&ret, attrs, 0);
	}
      واپس ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  اگر (specs->typespec_قسم == ctsk_tagdef
      && درخت_رمز (specs->type) != ENUMERAL_TYPE
      && c_parser_اگلا_token_starts_declspecs (parser)
      && !c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = جھوٹ;
      واپس NULL_درخت;
    }

  pending_xref_error ();
  سابقہ_attrs = specs->attrs;
  all_سابقہ_attrs = سابقہ_attrs;
  specs->attrs = NULL_درخت;
  decls = NULL_درخت;
  جب (سچ)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      ساخت c_declarator *declarator;
      منطقی dummy = جھوٹ;
      اگر (c_parser_اگلا_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_درخت);
      ورنہ
	declarator = c_parser_declarator (parser,
					  specs->typespec_قسم != ctsk_none,
					  C_DTR_معمول, &dummy);
      اگر (declarator == تہی)
	{
	  c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
	  توڑو;
	}
      اگر (c_parser_اگلا_token_is (parser, CPP_COLON)
	  || c_parser_اگلا_token_is (parser, CPP_COMMA)
	  || c_parser_اگلا_token_is (parser, CPP_SEMICOLON)
	  || c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_اگلا_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  درخت postfix_attrs = NULL_درخت;
	  درخت چوڑائی = NULL_درخت;
	  درخت d;
	  اگر (c_parser_اگلا_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      چوڑائی = convert_lvalue_مقصد_rvalue (loc,
						(c_parser_اظہاریہ_no_commas
						 (parser, تہی)),
						سچ, سچ).قدر;
	    }
	  اگر (c_parser_اگلا_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_اوصاف (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, چوڑائی, &all_سابقہ_attrs, اظہاریہ);
	  decl_اوصاف (&d, chainon (postfix_attrs,
					all_سابقہ_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  اگر (c_parser_اگلا_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_سابقہ_attrs = chainon (c_parser_gnu_اوصاف (parser),
					سابقہ_attrs);
	  ورنہ
	    all_سابقہ_attrs = سابقہ_attrs;
	  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON)
		   || c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      /* Semicolon consumed in caller.  */
	      توڑو;
	    }
	  ورنہ
	    {
	      c_parser_error (parser, "expected %<,%>, %<;%> or %<}%>");
	      توڑو;
	    }
	}
      ورنہ
	{
	  c_parser_error (parser,
			  "expected %<:%>, %<,%>, %<;%>, %<}%> or "
			  "%<__attribute__%>");
	  توڑو;
	}
    }
  واپس decls;
}

/* Parse a typeof specifier (a GNU extension adopted in C23).

   typeof-specifier:
     typeof ( expression )
     typeof ( type-name )
     typeof_unqual ( expression )
     typeof_unqual ( type-name )
*/

ساکن ساخت c_typespec
c_parser_typeof_specifier (c_parser *parser)
{
  منطقی is_unqual;
  منطقی is_std;
  ساخت c_typespec ret;
  ret.قسم = ctsk_typeof;
  ret.spec = error_mark_گرہ;
  ret.اظہاریہ = NULL_درخت;
  ret.اظہاریہ_const_operands = سچ;
  ret.has_enum_type_specifier = جھوٹ;
  اگر (c_parser_اگلا_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = جھوٹ;
      درخت spelling = c_parser_peek_token (parser)->قدر;
      is_std = (flag_isoc23
		&& strcmp (IDENTIFIER_اشارہ_گر (spelling), "typeof") == 0);
    }
  ورنہ
    {
      gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = سچ;
      درخت spelling = c_parser_peek_token (parser)->قدر;
      is_std = strcmp (IDENTIFIER_اشارہ_گر (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  اندر_typeof++;
  matching_parens parens;
  اگر (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      اندر_typeof--;
      واپس ret;
    }
  اگر (c_parser_اگلا_علامات_آغاز_typename (parser, cla_prefer_id))
    {
      ساخت c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      اندر_typeof--;
      اگر (type != تہی)
	{
	  ret.spec = groktypename (type, &ret.اظہاریہ, &ret.اظہاریہ_const_operands);
	  نکالو_maybe_مستعمل (c_type_variably_modified_p (ret.spec));
	}
    }
  ورنہ
    {
      منطقی was_vm;
      location_t یہاں = c_parser_peek_token (parser)->location;
      ساخت c_اظہاریہ اظہاریہ = c_parser_عبارت (parser);
      c_inhibit_evaluation_warnings--;
      اندر_typeof--;
      اگر (درخت_رمز (اظہاریہ.قدر) == COMPONENT_REF
	  && DECL_C_ثنائی_ہندسہ_میدان (درخت_عملیہ (اظہاریہ.قدر, 1)))
	error_at (یہاں, "%<typeof%> applied to a bit-field");
      mark_exp_read (اظہاریہ.قدر);
      ret.spec = درخت_TYPE (اظہاریہ.قدر);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      اگر (was_vm)
	ret.اظہاریہ = c_fully_fold (اظہاریہ.قدر, جھوٹ, &ret.اظہاریہ_const_operands);
      نکالو_maybe_مستعمل (was_vm);
    }
  parens.skip_until_ملا_close (parser);
  اگر (ret.spec != error_mark_گرہ)
    {
      اگر (is_unqual)
	{
	  منطقی is_array = درخت_رمز (ret.spec) == ARRAY_TYPE;
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
	  اگر (درخت_رمز (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  ورنہ اگر (FUNCTION_اشارہ_گر_TYPE_P (ret.spec)
		   && TYPE_QUALS (درخت_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_اشارہ_گر_type (TYPE_MAIN_VARIANT (درخت_TYPE (ret.spec)));
	}
    }
  واپس ret;
}

/* Parse an alignment-specifier.

   C11 6.7.5:

   alignment-specifier:
     _Alignas ( type-name )
     _Alignas ( constant-expression )
*/

ساکن درخت
c_parser_alignas_specifier (c_parser * parser)
{
  درخت ret = error_mark_گرہ;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_ALIGNAS));
  درخت spelling = c_parser_peek_token (parser)->قدر;
  c_parser_consume_token (parser);
  اگر (flag_isoc99)
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  ورنہ
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس ret;
  اگر (c_parser_اگلا_علامات_آغاز_typename (parser, cla_prefer_id))
    {
      ساخت c_type_name *type = c_parser_type_name (parser);
      اگر (type != تہی)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, تہی, تہی),
					جھوٹ, سچ, 1);
    }
  ورنہ
    ret = convert_lvalue_مقصد_rvalue (loc,
				    c_parser_اظہاریہ_no_commas (parser, تہی),
				    سچ, سچ).قدر;
  parens.skip_until_ملا_close (parser);
  واپس ret;
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
اشارہ_گر
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

ساخت c_declarator *
c_parser_declarator (c_parser *parser, منطقی type_نظر_آیا_p, c_dtr_syn قسم,
		     منطقی *نظر_آیا_id)
{
  /* Parse any initial pointer part.  */
  اگر (c_parser_اگلا_token_is (parser, CPP_MULT))
    {
      ساخت c_declspecs *quals_attrs = build_null_declspecs ();
      ساخت c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, جھوٹ, جھوٹ, سچ,
			  جھوٹ, جھوٹ, سچ, جھوٹ, cla_prefer_id);
      inner = c_parser_declarator (parser, type_نظر_آیا_p, قسم, نظر_آیا_id);
      اگر (inner == تہی)
	واپس تہی;
      ورنہ
	واپس make_اشارہ_گر_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  واپس c_parser_براہ_راست_declarator (parser, type_نظر_آیا_p, قسم, نظر_آیا_id);
}

/* Parse a direct declarator or direct abstract declarator; arguments
   as c_parser_declarator.  */

ساکن ساخت c_declarator *
c_parser_براہ_راست_declarator (c_parser *parser, منطقی type_نظر_آیا_p, c_dtr_syn قسم,
			    منطقی *نظر_آیا_id)
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

  اگر (قسم != C_DTR_ABSTRACT
      && c_parser_اگلا_token_is (parser, CPP_NAME)
      && ((type_نظر_آیا_p
	   && (c_parser_peek_token (parser)->id_قسم == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_قسم == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_قسم == C_ID_ID))
    {
      ساخت c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->قدر);
      *نظر_آیا_id = سچ;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      اگر (c_parser_nth_token_starts_std_اوصاف (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      واپس c_parser_براہ_راست_declarator_inner (parser, *نظر_آیا_id, inner);
    }

  اگر (قسم != C_DTR_معمول
      && c_parser_اگلا_token_is (parser, CPP_OPEN_مربع)
      && !c_parser_nth_token_starts_std_اوصاف (parser, 1))
    {
      ساخت c_declarator *inner = build_id_declarator (NULL_درخت);
      inner->id_loc = c_parser_peek_token (parser)->location;
      واپس c_parser_براہ_راست_declarator_inner (parser, *نظر_آیا_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      درخت attrs;
      ساخت c_declarator *inner;
      c_parser_consume_token (parser);
      منطقی have_gnu_attrs = c_parser_اگلا_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_اوصاف (parser);
      اگر (قسم != C_DTR_معمول
	  && (c_parser_اگلا_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_اوصاف (parser, 1)
		      || c_parser_اگلا_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  ساخت c_arg_info *دلائل
	    = c_parser_parms_declarator (parser, قسم == C_DTR_معمول,
					 attrs, have_gnu_attrs);
	  اگر (دلائل == تہی)
	    واپس تہی;
	  ورنہ
	    {
	      inner = build_id_declarator (NULL_درخت);
	      اگر (!(دلائل->types
		    && دلائل->types != error_mark_گرہ
		    && درخت_رمز (درخت_قدر (دلائل->types)) == IDENTIFIER_گرہ)
		  && c_parser_nth_token_starts_std_اوصاف (parser, 1))
		{
		  درخت std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  اگر (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (دلائل, inner);
	      واپس c_parser_براہ_راست_declarator_inner (parser, *نظر_آیا_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_نظر_آیا_p, قسم, نظر_آیا_id);
      اگر (inner != تہی && attrs != تہی)
	inner = build_attrs_declarator (attrs, inner);
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  اگر (inner == تہی)
	    واپس تہی;
	  ورنہ
	    واپس c_parser_براہ_راست_declarator_inner (parser, *نظر_آیا_id, inner);
	}
      ورنہ
	{
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  واپس تہی;
	}
    }
  ورنہ
    {
      اگر (قسم == C_DTR_معمول)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  واپس تہی;
	}
      ورنہ
	واپس build_id_declarator (NULL_درخت);
    }
}

/* Parse part of a direct declarator or direct abstract declarator,
   given that some (in INNER) has already been parsed; ID_PRESENT is
   true if an identifier is present, false for an abstract
   declarator.  */

ساکن ساخت c_declarator *
c_parser_براہ_راست_declarator_inner (c_parser *parser, منطقی id_present,
				  ساخت c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_مربع)
      && !c_parser_nth_token_starts_std_اوصاف (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      ساخت c_declarator *declarator;
      ساخت c_declspecs *quals_attrs = build_null_declspecs ();
      ساخت c_اظہاریہ dimen;
      dimen.قدر = NULL_درخت;
      dimen.original_رمز = ERROR_MARK;
      dimen.original_type = NULL_درخت;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, جھوٹ, جھوٹ, سچ,
			  جھوٹ, جھوٹ, جھوٹ, جھوٹ, cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      اگر (c_parser_اگلا_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  اگر (!quals_attrs->declspecs_نظر_آیا_p)
	    c_parser_declspecs (parser, quals_attrs, جھوٹ, جھوٹ, سچ,
				جھوٹ, جھوٹ, جھوٹ, جھوٹ, cla_prefer_id);
	}
      اگر (!quals_attrs->declspecs_نظر_آیا_p)
	quals_attrs = تہی;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      ثابت منطقی static_نظر_آیا = (static_loc != UNKNOWN_LOCATION);
      منطقی ستارہ_نظر_آیا = جھوٹ;
      اگر (c_parser_اگلا_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_مربع)
	{
	  ستارہ_نظر_آیا = سچ;
	  c_parser_consume_token (parser);
	}
      ورنہ اگر (!c_parser_اگلا_token_is (parser, CPP_CLOSE_مربع))
	dimen = c_parser_اظہاریہ_no_commas (parser, تہی);

      اگر (static_نظر_آیا)
	{
	  اگر (ستارہ_نظر_آیا)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      ستارہ_نظر_آیا = جھوٹ;
	      dimen.قدر = error_mark_گرہ;
	    }
	  ورنہ اگر (!dimen.قدر)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_مربع))
	c_parser_consume_token (parser);
      ورنہ
	{
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_مربع,
				     "expected %<]%>");
	  واپس تہی;
	}
      اگر (dimen.قدر)
	dimen = convert_lvalue_مقصد_rvalue (brace_loc, dimen, سچ, سچ);
      declarator = build_array_declarator (brace_loc, dimen.قدر, quals_attrs,
					   static_نظر_آیا, ستارہ_نظر_آیا);
      اگر (declarator == تہی)
	واپس تہی;
      اگر (c_parser_nth_token_starts_std_اوصاف (parser, 1))
	{
	  درخت std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  اگر (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = سیٹ_array_declarator_inner (declarator, inner);
      واپس c_parser_براہ_راست_declarator_inner (parser, id_present, inner);
    }
  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      درخت attrs;
      ساخت c_arg_info *دلائل;
      c_parser_consume_token (parser);
      منطقی have_gnu_attrs = c_parser_اگلا_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_اوصاف (parser);
      دلائل = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      اگر (دلائل == تہی)
	واپس تہی;
      ورنہ
	{
	  اگر (!(دلائل->types
		&& دلائل->types != error_mark_گرہ
		&& درخت_رمز (درخت_قدر (دلائل->types)) == IDENTIFIER_گرہ)
	      && c_parser_nth_token_starts_std_اوصاف (parser, 1))
	    {
	      درخت std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      اگر (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (دلائل, inner);
	  واپس c_parser_براہ_راست_declarator_inner (parser, id_present, inner);
	}
    }
  واپس inner;
}

/* Parse a parameter list or identifier list, including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list.  ID_LIST_OK is true if an identifier list
   is acceptable; such a list must not have attributes at the start.
   HAVE_GNU_ATTRS says whether any gnu-attributes (including empty
   attributes) were present (in which case standard attributes cannot
   occur).  */

ساکن ساخت c_arg_info *
c_parser_parms_declarator (c_parser *parser, منطقی id_list_ok, درخت attrs,
			   منطقی have_gnu_attrs)
{
  ڈالو_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  اگر (id_list_ok
      && !attrs
      && c_parser_اگلا_token_is (parser, CPP_NAME)
      && c_parser_peek_token (parser)->id_قسم == C_ID_ID

      /* Look ahead to detect typos in type names.  */
      && c_parser_peek_2nd_token (parser)->type != CPP_NAME
      && c_parser_peek_2nd_token (parser)->type != CPP_MULT
      && c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
      && c_parser_peek_2nd_token (parser)->type != CPP_OPEN_مربع
      && c_parser_peek_2nd_token (parser)->type != CPP_KEYWORD)
    {
      درخت list = NULL_درخت, *nextp = &list;
      جب (c_parser_اگلا_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_قسم == C_ID_ID)
	{
	  *nextp = build_درخت_list (NULL_درخت,
				    c_parser_peek_token (parser)->قدر);
	  nextp = & درخت_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  اگر (c_parser_اگلا_token_is_not (parser, CPP_COMMA))
	    توڑو;
	  c_parser_consume_token (parser);
	  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      توڑو;
	    }
	}
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ساخت c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  نکالو_scope ();
	  واپس ret;
	}
      ورنہ
	{
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  نکالو_scope ();
	  واپس تہی;
	}
    }
  ورنہ
    {
      ساخت c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, تہی, have_gnu_attrs);
      نکالو_scope ();
      واپس ret;
    }
}

/* Parse a parameter list (possibly empty), including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list; if HAVE_GNU_ATTRS, there were some such
   attributes (possibly empty, in which case ATTRS is NULL_TREE),
   which means standard attributes cannot start the list.  EXPR is
   NULL or an expression that needs to be evaluated for the side
   effects of array size expressions in the parameters.  */

ساکن ساخت c_arg_info *
c_parser_parms_list_declarator (c_parser *parser, درخت attrs, درخت اظہاریہ,
				منطقی have_gnu_attrs)
{
  منطقی bad_parm = جھوٹ;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
    {
      ساخت c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      واپس ret;
    }
  اگر (c_parser_اگلا_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      ساخت c_arg_info *ret = build_arg_info ();

      ret->types = NULL_درخت;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_دلائل_stdarg_p = سچ;
	  c_parser_consume_token (parser);
	  واپس ret;
	}
      ورنہ
	{
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  واپس تہی;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  جب (سچ)
    {
      /* Parse a parameter.  */
      ساخت c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_درخت;
      have_gnu_attrs = جھوٹ;
      اگر (parm == تہی)
	bad_parm = سچ;
      ورنہ
	ڈالو_parm_decl (parm, &اظہاریہ);
      اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
	{
	  درخت new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  منطقی new_have_gnu_attrs
	    = c_parser_اگلا_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_اوصاف (parser);
	  واپس c_parser_parms_list_declarator (parser, new_attrs, اظہاریہ,
						 new_have_gnu_attrs);
	}
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  اگر (bad_parm)
	    واپس تہی;
	  ورنہ
	    واپس get_parm_info (جھوٹ, اظہاریہ);
	}
      اگر (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, جھوٹ))
	{
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
	  واپس تہی;
	}
      اگر (c_parser_اگلا_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      اگر (bad_parm)
		واپس تہی;
	      ورنہ
		واپس get_parm_info (سچ, اظہاریہ);
	    }
	  ورنہ
	    {
	      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      واپس تہی;
	    }
	}
    }
}

/* Parse a parameter declaration.  ATTRS are the gnu-attributes at the
   start of the declaration if it is the first parameter;
   HAVE_GNU_ATTRS is true if there were any gnu-attributes there (even
   empty) there.  */

ساکن ساخت c_parm *
c_parser_parameter_declaration (c_parser *parser, درخت attrs,
				منطقی have_gnu_attrs)
{
  ساخت c_declspecs *specs;
  ساخت c_declarator *declarator;
  درخت سابقہ_attrs;
  درخت postfix_attrs = NULL_درخت;
  منطقی dummy = جھوٹ;

  /* Accept #pragmas between parameter declarations.  */
  جب (c_parser_اگلا_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, تہی, NULL_درخت);

  اگر (!c_parser_اگلا_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_اوصاف (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (parser->error)
	واپس تہی;
      c_parser_سیٹ_ماخذ_position_from_token (token);
      اگر (c_parser_اگلا_علامات_آغاز_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_گروہ d;
	  name_hint hint = lookup_name_fuzzy (token->قدر,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  اگر (ثابت حرف *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.جوڑو_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->قدر, suggestion);
	    }
	  ورنہ
	    error_at (token->location, "unknown type name %qE", token->قدر);
	  parser->error = سچ;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      ورنہ
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_مقصد_انتہا_کا_parameter (parser);
      واپس تہی;
    }

  location_t آغاز_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  اگر (attrs)
    {
      declspecs_جوڑو_attrs (داخلہ_location, specs, attrs);
      attrs = NULL_درخت;
    }
  c_parser_declspecs (parser, specs, سچ, سچ, سچ, سچ, جھوٹ,
		      !have_gnu_attrs, سچ, cla_nonabstract_decl);
  اختتام_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  اگر (specs->typespec_قسم == ctsk_tagdef)
    verify_counted_by_for_چوٹی_anonymous_type (specs->type);

  pending_xref_error ();
  سابقہ_attrs = specs->attrs;
  specs->attrs = NULL_درخت;
  declarator = c_parser_declarator (parser,
				    specs->typespec_قسم != ctsk_none,
				    C_DTR_PARM, &dummy);
  اگر (declarator == تہی)
    {
      c_parser_skip_until_ملا (parser, CPP_COMMA, تہی);
      واپس تہی;
    }
  اگر (c_parser_اگلا_token_is_keyword (parser, RID_ATTRIBUTE))
    postfix_attrs = c_parser_gnu_اوصاف (parser);

  /* Generate a location for the parameter, ranging from the start of the
     initial token to the end of the final token.

     If we have a identifier, then use it for the caret location, e.g.

       extern int callee (int one, int (*two)(int, int), float three);
                                   ~~~~~~^~~~~~~~~~~~~~

     otherwise, reuse the start location for the caret location e.g.:

       extern int callee (int one, int (*)(int, int), float three);
                                   ^~~~~~~~~~~~~~~~~
  */
  location_t انتہا_loc = parser->آخری_token_location;

  /* Find any cdk_id declarator; determine if we have an identifier.  */
  c_declarator *id_declarator = declarator;
  جب (id_declarator && id_declarator->قسم != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : آغاز_loc);
  location_t param_loc = make_location (caret_loc, آغاز_loc, انتہا_loc);

  واپس build_c_parm (specs, chainon (postfix_attrs, سابقہ_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

ساکن درخت
c_parser_asm_string_literal (c_parser *parser)
{
  درخت str;
  صحیح save_flag = warn_overlength_لڑیاں;
  warn_overlength_لڑیاں = 0;
  str = c_parser_string_literal (parser, جھوٹ, جھوٹ).قدر;
  warn_overlength_لڑیاں = save_flag;
  واپس str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

ساکن درخت
c_parser_simple_asm_اظہاریہ (c_parser *parser)
{
  درخت str;
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس NULL_درخت;
  str = c_parser_asm_string_literal (parser);
  اگر (!parens.require_close (parser))
    {
      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
      واپس NULL_درخت;
    }
  واپس str;
}

ساکن درخت
c_parser_gnu_attribute_any_لفظ (c_parser *parser)
{
  درخت attr_name = NULL_درخت;

  اگر (c_parser_اگلا_token_is (parser, CPP_KEYWORD))
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
	حالت RID_رجسٹر:
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
	  ok = سچ;
	  توڑو;
	طےشدہ:
	  ok = جھوٹ;
	  توڑو;
	}
      اگر (!ok)
	واپس NULL_درخت;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(صحیح) c_parser_peek_token (parser)->keyword];
    }
  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->قدر;

  واپس attr_name;
}

/* Parse attribute arguments.  This is a common form of syntax
   covering all currently valid GNU and standard attributes.

   gnu-attribute-arguments:
     identifier
     identifier , nonempty-expr-list
     expr-list

   where the "identifier" must not be declared as a type.  ??? Why not
   allow identifiers declared as types to start the arguments?  */

ساکن درخت
c_parser_attribute_arguments (c_parser *parser, منطقی takes_identifier,
			      منطقی require_string, منطقی assume_attr,
			      منطقی allow_خالی_خانے_دلائل)
{
  vec<درخت, va_gc> *اظہاریہ_list;
  درخت attr_دلائل;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
      && (c_parser_peek_token (parser)->id_قسم == C_ID_ID
	  || (c_dialect_objc ()
	      && c_parser_peek_token (parser)->id_قسم
	      == C_ID_CLASSNAME))
      && ((c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	  || (c_parser_peek_2nd_token (parser)->type
	      == CPP_CLOSE_PAREN))
      && (takes_identifier
	  || (c_dialect_objc ()
	      && !assume_attr
	      && c_parser_peek_token (parser)->id_قسم
	      == C_ID_CLASSNAME)))
    {
      درخت arg1 = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	attr_دلائل = build_درخت_list (NULL_درخت, arg1);
      ورنہ
	{
	  درخت درخت_list;
	  c_parser_consume_token (parser);
	  اظہاریہ_list = c_parser_اظہاریہ_list (parser, جھوٹ, سچ,
					  تہی, تہی, تہی, تہی);
	  درخت_list = build_درخت_list_vec (اظہاریہ_list);
	  attr_دلائل = درخت_cons (NULL_درخت, arg1, درخت_list);
	  release_درخت_سمتیہ (اظہاریہ_list);
	}
    }
  ورنہ
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	{
	  اگر (!allow_خالی_خانے_دلائل)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_دلائل = NULL_درخت;
	}
      ورنہ اگر (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  درخت string = c_parser_string_literal (parser, جھوٹ, سچ).قدر;
	  attr_دلائل = build_درخت_list (NULL_درخت, string);
	}
      ورنہ اگر (assume_attr)
	{
	  درخت cond
	    = c_parser_conditional_عبارت (parser, تہی, NULL_درخت).قدر;
	  اگر (!c_parser_اگلا_token_is (parser, CPP_COMMA))
	    attr_دلائل = build_درخت_list (NULL_درخت, cond);
	  ورنہ
	    {
	      درخت درخت_list;
	      c_parser_consume_token (parser);
	      اظہاریہ_list = c_parser_اظہاریہ_list (parser, جھوٹ, سچ,
					      تہی, تہی, تہی, تہی);
	      درخت_list = build_درخت_list_vec (اظہاریہ_list);
	      attr_دلائل = درخت_cons (NULL_درخت, cond, درخت_list);
	      release_درخت_سمتیہ (اظہاریہ_list);
	    }
	}
      ورنہ
	{
	  اظہاریہ_list = c_parser_اظہاریہ_list (parser, جھوٹ, سچ,
					  تہی, تہی, تہی, تہی);
	  attr_دلائل = build_درخت_list_vec (اظہاریہ_list);
	  release_درخت_سمتیہ (اظہاریہ_list);
	}
    }
  واپس attr_دلائل;
}

/* Parse (possibly empty) gnu-attributes.  This is a GNU extension.

   gnu-attributes:
خالی_خانے
     gnu-attributes gnu-attribute

   gnu-attribute:
     __attribute__ ( ( gnu-attribute-list ) )

   gnu-attribute-list:
     gnu-attrib
     gnu-attribute_list , gnu-attrib

   gnu-attrib:
خالی_خانے
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

ساکن درخت
c_parser_gnu_attribute (c_parser *parser, درخت attrs,
			منطقی expect_comma = جھوٹ, منطقی خالی_خانے_ok = سچ)
{
  منطقی comma_پہلا = c_parser_اگلا_token_is (parser, CPP_COMMA);
  اگر (!comma_پہلا
      && !c_parser_اگلا_token_is (parser, CPP_NAME)
      && !c_parser_اگلا_token_is (parser, CPP_KEYWORD))
    واپس NULL_درخت;

  جب (c_parser_اگلا_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      اگر (!خالی_خانے_ok)
	واپس attrs;
    }

  درخت attr_name = c_parser_gnu_attribute_any_لفظ (parser);
  اگر (attr_name == NULL_درخت)
    واپس NULL_درخت;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  درخت attr;
  اگر (c_parser_اگلا_token_is_not (parser, CPP_OPEN_PAREN))
    {
      اگر (expect_comma && !comma_پہلا)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  واپس error_mark_گرہ;
	}
      attr = build_درخت_list (attr_name, NULL_درخت);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      واپس attrs;
    }
  c_parser_consume_token (parser);

  درخت attr_دلائل
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    جھوٹ,
				    is_attribute_p ("assume", attr_name),
				    سچ);

  attr = build_درخت_list (attr_name, attr_دلائل);
  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  ورنہ
    {
      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      واپس error_mark_گرہ;
    }

  اگر (expect_comma && !comma_پہلا)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      واپس error_mark_گرہ;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  واپس attrs;
}

ساکن درخت
c_parser_gnu_اوصاف (c_parser *parser)
{
  درخت attrs = NULL_درخت;
  جب (c_parser_اگلا_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      منطقی save_translate_لڑیاں_p = parser->translate_لڑیاں_p;
      parser->translate_لڑیاں_p = جھوٹ;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_لڑیاں_p = save_translate_لڑیاں_p;
	  واپس attrs;
	}
      اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_لڑیاں_p = save_translate_لڑیاں_p;
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
	  واپس attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      برائے (منطقی expect_comma = جھوٹ; ; expect_comma = سچ)
	{
	  /* Parse a single attribute.  */
	  درخت attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  اگر (attr == error_mark_گرہ)
	    واپس attrs;
	  اگر (!attr)
	    توڑو;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      ورنہ
	{
	  parser->translate_لڑیاں_p = save_translate_لڑیاں_p;
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  واپس attrs;
	}
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      ورنہ
	{
	  parser->translate_لڑیاں_p = save_translate_لڑیاں_p;
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  واپس attrs;
	}
      parser->translate_لڑیاں_p = save_translate_لڑیاں_p;
    }

  واپس attrs;
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

ساکن خالی
c_parser_متوازن_token_sequence (c_parser *parser)
{
  جب (سچ)
    {
      c_token *token = c_parser_peek_token (parser);
      انتخاب (token->type)
	{
	حالت CPP_OPEN_BRACE:
	  {
	    matching_braces braces;
	    braces.consume_open (parser);
	    c_parser_متوازن_token_sequence (parser);
	    braces.require_close (parser);
	    توڑو;
	  }

	حالت CPP_OPEN_PAREN:
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    c_parser_متوازن_token_sequence (parser);
	    parens.require_close (parser);
	    توڑو;
	  }

	حالت CPP_OPEN_مربع:
	  c_parser_consume_token (parser);
	  c_parser_متوازن_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_مربع, "expected %<]%>");
	  توڑو;

	حالت CPP_CLOSE_BRACE:
	حالت CPP_CLOSE_PAREN:
	حالت CPP_CLOSE_مربع:
	حالت CPP_EOF:
	  واپس;

	حالت CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	  توڑو;

	طےشدہ:
	  c_parser_consume_token (parser);
	  توڑو;
	}
    }
}

/* Parse arguments of omp::directive or omp::decl attribute.

   directive-name ,[opt] clause-list[opt]

   For directive just remember the tokens in a vector for subsequent
   parsing.  */

ساکن خالی
c_parser_omp_directive_دلائل (c_parser *parser, درخت attribute, منطقی decl_p)
{
  غیرعلامتی صحیح n = 1;
  c_token *پہلا = c_parser_peek_token (parser);
  اگر (!c_parser_check_متوازن_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_متوازن_token_sequence (parser);
      درخت_قدر (attribute) = NULL_درخت;
      واپس;
    }
  اگر (n == 1)
    {
      error_at (پہلا->location, "expected OpenMP directive name");
      درخت_قدر (attribute) = NULL_درخت;
      واپس;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  برائے (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->تیز_ڈالو (*tok);
      c_parser_consume_token (parser);
    }
  درخت arg = make_گرہ (C_TOKEN_VEC);
  C_TOKEN_VEC_علامات (arg) = v;
  اگر (decl_p)
    درخت_عوامی (arg) = 1;
  درخت_قدر (attribute) = درخت_cons (NULL_درخت, arg, درخت_قدر (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

ساکن خالی
c_parser_omp_sequence_دلائل (c_parser *parser, درخت attribute)
{
  کرو
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (token->type == CPP_NAME
	  && strcmp (IDENTIFIER_اشارہ_گر (token->قدر), "omp") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_SCOPE)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  token = c_parser_peek_token (parser);
	}
      منطقی directive = جھوٹ;
      ثابت حرف *p;
      اگر (token->type != CPP_NAME)
	p = "";
      ورنہ
	p = IDENTIFIER_اشارہ_گر (token->قدر);
      اگر (strcmp (p, "directive") == 0)
	directive = سچ;
      ورنہ اگر (strcmp (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  غیرعلامتی nesting_گہرائی = 0;

	  جب (سچ)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      اگر ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_گہرائی)
		توڑو;
	      /* If we've run out of tokens, stop.  */
	      اگر (token->type == CPP_EOF)
		توڑو;
	      اگر (token->type == CPP_PRAGMA_EOL && parser->اندر_pragma)
		توڑو;
	      اگر (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_مربع)
		++nesting_گہرائی;
	      ورنہ اگر (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_مربع)
		{
		  اگر (nesting_گہرائی-- == 0)
		    توڑو;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  اگر (c_parser_اگلا_token_is_not (parser, CPP_COMMA))
	    توڑو;
	  c_parser_consume_token (parser);
	  جاری;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      اگر (parens.require_open (parser))
	{
	  اگر (directive)
	    c_parser_omp_directive_دلائل (parser, attribute, جھوٹ);
	  ورنہ
	    c_parser_omp_sequence_دلائل (parser, attribute);
	  parens.skip_until_ملا_close (parser);
	  اگر (c_parser_اگلا_token_is_not (parser, CPP_COMMA))
	    توڑو;
	  c_parser_consume_token (parser);
	}
      ورنہ اگر (c_parser_اگلا_token_is_not (parser, CPP_COMMA))
	توڑو;
      ورنہ
	c_parser_consume_token (parser);
    }
  جب (1);
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

ساکن درخت
c_parser_std_attribute (c_parser *parser, منطقی for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  درخت ns, name, attribute;

  /* Parse the attribute-token.  */
  اگر (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      واپس error_mark_گرہ;
    }
  name = canonicalize_attr_name (token->قدر);
  c_parser_consume_token (parser);
  اگر (c_parser_اگلا_token_is (parser, CPP_SCOPE)
      || (c_parser_اگلا_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      اگر (c_parser_اگلا_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      اگر (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  واپس error_mark_گرہ;
	}
      name = canonicalize_attr_name (token->قدر);
      c_parser_consume_token (parser);
    }
  ورنہ
    ns = NULL_درخت;
  attribute = build_درخت_list (build_درخت_list (ns, name), NULL_درخت);

  /* Parse the arguments, if any.  */
  ثابت attribute_spec *as = lookup_attribute_spec (درخت_PURPOSE (attribute));
  اگر (c_parser_اگلا_token_is_not (parser, CPP_OPEN_PAREN))
    {
      اگر ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  واپس error_mark_گرہ;
	}
      جاؤ برآمد;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    اگر ((as && as->max_لمبائی == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_ملا_close (parser);
	واپس error_mark_گرہ;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    اگر (as && !attribute_ignored_p (as))
      {
	منطقی takes_identifier
	  = (ns != NULL_درخت
	     && strcmp (IDENTIFIER_اشارہ_گر (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	منطقی require_string
	  = (ns == NULL_درخت
	     && (strcmp (IDENTIFIER_اشارہ_گر (name), "deprecated") == 0
		 || strcmp (IDENTIFIER_اشارہ_گر (name), "nodiscard") == 0));
	منطقی assume_attr
	  = (ns != NULL_درخت
	     && strcmp (IDENTIFIER_اشارہ_گر (ns), "gnu") == 0
	     && strcmp (IDENTIFIER_اشارہ_گر (name), "assume") == 0);
	درخت_قدر (attribute)
	  = c_parser_attribute_arguments (parser, takes_identifier,
					  require_string, assume_attr, جھوٹ);
      }
    ورنہ
      {
	اگر ((flag_openmp || flag_openmp_simd)
	    && ns
	    && is_attribute_p ("omp", ns))
	  {
	    اگر (is_attribute_p ("directive", name))
	      {
		c_parser_omp_directive_دلائل (parser, attribute, جھوٹ);
		parens.skip_until_ملا_close (parser);
		واپس attribute;
	      }
	    ورنہ اگر (is_attribute_p ("decl", name))
	      {
		درخت_قدر (درخت_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_دلائل (parser, attribute, سچ);
		parens.skip_until_ملا_close (parser);
		واپس attribute;
	      }
	    ورنہ اگر (is_attribute_p ("sequence", name))
	      {
		درخت_قدر (درخت_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_دلائل (parser, attribute);
		parens.skip_until_ملا_close (parser);
		درخت_قدر (attribute) = nreverse (درخت_قدر (attribute));
		واپس attribute;
	      }
	  }
	c_parser_متوازن_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 برآمد:
  اگر (ns == NULL_درخت && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (داخلہ_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      واپس error_mark_گرہ;
    }
  واپس attribute;
}

ساکن درخت
c_parser_std_attribute_list (c_parser *parser, منطقی for_tm)
{
  درخت اوصاف = NULL_درخت;
  جب (سچ)
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (token->type == CPP_CLOSE_مربع)
	توڑو;
      اگر (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  جاری;
	}
      درخت attribute = c_parser_std_attribute (parser, for_tm);
      اگر (attribute != error_mark_گرہ)
	{
	  درخت_CHAIN (attribute) = اوصاف;
	  اوصاف = attribute;
	}
      اگر (c_parser_اگلا_token_is_not (parser, CPP_COMMA))
	توڑو;
    }
  واپس اوصاف;
}

ساکن درخت
c_parser_std_attribute_specifier (c_parser *parser, منطقی for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  اگر (!c_parser_require (parser, CPP_OPEN_مربع, "expected %<[%>"))
    واپس NULL_درخت;
  اگر (!c_parser_require (parser, CPP_OPEN_مربع, "expected %<[%>"))
    {
      c_parser_skip_until_ملا (parser, CPP_CLOSE_مربع, "expected %<]%>");
      واپس NULL_درخت;
    }
  درخت اوصاف;
  اگر (c_parser_اگلا_token_is_keyword (parser, RID_EXTENSION))
    {
      خودکار ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      اوصاف = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  ورنہ
    {
      اگر (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      اوصاف = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_ملا (parser, CPP_CLOSE_مربع, "expected %<]%>");
  c_parser_skip_until_ملا (parser, CPP_CLOSE_مربع, "expected %<]%>");
  واپس nreverse (اوصاف);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

ساکن منطقی
c_parser_check_متوازن_raw_token_sequence (c_parser *parser, غیرعلامتی صحیح *n)
{
  جب (سچ)
    {
      c_token *token = c_parser_peek_nth_token_raw (parser, *n);
      انتخاب (token->type)
	{
	حالت CPP_OPEN_BRACE:
	  {
	    ++*n;
	    اگر (c_parser_check_متوازن_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		اگر (token->type == CPP_CLOSE_BRACE)
		  ++*n;
		ورنہ
		  واپس جھوٹ;
	      }
	    ورنہ
	      واپس جھوٹ;
	    توڑو;
	  }

	حالت CPP_OPEN_PAREN:
	  {
	    ++*n;
	    اگر (c_parser_check_متوازن_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		اگر (token->type == CPP_CLOSE_PAREN)
		  ++*n;
		ورنہ
		  واپس جھوٹ;
	      }
	    ورنہ
	      واپس جھوٹ;
	    توڑو;
	  }

	حالت CPP_OPEN_مربع:
	  {
	    ++*n;
	    اگر (c_parser_check_متوازن_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		اگر (token->type == CPP_CLOSE_مربع)
		  ++*n;
		ورنہ
		  واپس جھوٹ;
	      }
	    ورنہ
	      واپس جھوٹ;
	    توڑو;
	  }

	حالت CPP_CLOSE_BRACE:
	حالت CPP_CLOSE_PAREN:
	حالت CPP_CLOSE_مربع:
	حالت CPP_EOF:
	  واپس سچ;

	طےشدہ:
	  ++*n;
	  توڑو;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

ساکن منطقی
c_parser_nth_token_starts_std_اوصاف (c_parser *parser, غیرعلامتی صحیح n)
{
  اگر (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_مربع
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_مربع))
    واپس جھوٹ;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  اگر (!c_dialect_objc ())
    واپس سچ;
  n += 2;
  اگر (!c_parser_check_متوازن_raw_token_sequence (parser, &n))
    واپس جھوٹ;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  اگر (token->type != CPP_CLOSE_مربع)
    واپس جھوٹ;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  واپس token->type == CPP_CLOSE_مربع;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

ساکن سائز_t
c_parser_skip_std_attribute_spec_seq (c_parser *parser, سائز_t n)
{
  سائز_t orig_n = n;
  جب (سچ)
    {
      اگر (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_مربع
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_مربع))
	{
	  غیرعلامتی صحیح m = n + 2;
	  اگر (!c_parser_check_متوازن_raw_token_sequence (parser, &m))
	    واپس orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  اگر (token->type != CPP_CLOSE_مربع)
	    واپس orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  اگر (token->type != CPP_CLOSE_مربع)
	    واپس orig_n;
	  n = m + 2;
	}
      ورنہ
	توڑو;
    }
  واپس n;
}

ساکن درخت
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  درخت اوصاف = NULL_درخت;
  کرو
    {
      درخت attrs = c_parser_std_attribute_specifier (parser, جھوٹ);
      اوصاف = chainon (اوصاف, attrs);
    }
  جب (c_parser_nth_token_starts_std_اوصاف (parser, 1));
  واپس اوصاف;
}

/* Parse a type name (C90 6.5.5, C99 6.7.6, C11 6.7.7).  ALIGNAS_OK
   says whether alignment specifiers are OK (only in cases that might
   be the type name of a compound literal).

   type-name:
     specifier-qualifier-list abstract-declarator[opt]
*/

ساخت c_type_name *
c_parser_type_name (c_parser *parser, منطقی alignas_ok)
{
  ساخت c_declspecs *specs = build_null_declspecs ();
  ساخت c_declarator *declarator;
  ساخت c_type_name *ret;
  منطقی dummy = جھوٹ;
  c_parser_declspecs (parser, specs, جھوٹ, سچ, سچ, alignas_ok, جھوٹ,
		      جھوٹ, سچ, cla_prefer_type);
  اگر (!specs->declspecs_نظر_آیا_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      واپس تہی;
    }
  اگر (specs->type != error_mark_گرہ)
    {
      pending_xref_error ();
      اختتام_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      اگر (specs->typespec_قسم == ctsk_tagdef)
	verify_counted_by_for_چوٹی_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_قسم != ctsk_none,
				    C_DTR_ABSTRACT, &dummy);
  اگر (declarator == تہی)
    واپس تہی;
  ret = XOBNEW (&parser_obstack, ساخت c_type_name);
  ret->specs = specs;
  ret->declarator = declarator;
  واپس ret;
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

ساکن ساخت c_اظہاریہ
c_parser_initializer (c_parser *parser, درخت decl)
{
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
    واپس c_parser_braced_init (parser, NULL_درخت, جھوٹ, تہی,
				 decl != error_mark_گرہ
				 && C_DECL_VARIABLE_سائز (decl));
  ورنہ
    {
      ساخت c_اظہاریہ ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_اظہاریہ_no_commas (parser, تہی);
      اگر (decl != error_mark_گرہ && C_DECL_VARIABLE_سائز (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.سیٹ_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      اگر (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !درخت_STATIC (decl)
	  && ret.قدر == decl
	  && !warning_enabled_at (DECL_ماخذ_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      اگر (درخت_رمز (ret.قدر) != STRING_CST
	  && (درخت_رمز (ret.قدر) != COMPOUND_LITERAL_اظہاریہ
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_اظہاریہ_DECL
					    (ret.قدر))))
	ret = convert_lvalue_مقصد_rvalue (loc, ret, سچ, سچ, سچ);
      واپس ret;
    }
}

/* The location of the last comma within the current initializer list,
   or UNKNOWN_LOCATION if not within one.  */

location_t آخری_init_list_comma;

/* Parse a braced initializer list.  TYPE is the type specified for a
   compound literal, and NULL_TREE for other initializers and for
   nested braced lists.  NESTED_P is true for nested braced lists,
   false for the list of a compound literal or the list that is the
   top-level initializer in a declaration.  VARSIZE_P indicates
   whether the object to be initialized has a variable size.  */

ساکن ساخت c_اظہاریہ
c_parser_braced_init (c_parser *parser, درخت type, منطقی nested_p,
		      ساخت obstack *outer_obstack, منطقی varsize_p)
{
  ساخت c_اظہاریہ ret;
  ساخت obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE));
  منطقی save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = جھوٹ;
  منطقی zero_init_padding_بٹ = جھوٹ;
  matching_braces braces;
  braces.consume_open (parser);
  اگر (nested_p)
    {
      اختتام_implicit_inits (brace_loc, outer_obstack);
      ڈالو_init_level (brace_loc, 0, &braced_init_obstack);
    }
  ورنہ
    really_آغاز_incremental_init (type);
  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      اگر (flag_isoc23)
	zero_init_padding_بٹ = سچ;
    }
  ورنہ
    {
      اگر (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      جب (سچ)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  اگر (parser->error)
	    توڑو;
	  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	    {
	      آخری_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      جب (c_parser_اگلا_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_اظہاریہ embed_val;
		  embed_val.قدر = embed->قدر;
		  embed_val.original_رمز = RAW_ڈیٹا_CST;
		  embed_val.original_type = integer_type_گرہ;
		  سیٹ_c_اظہاریہ_ماخذ_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, جھوٹ,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_اگلا_token_is (parser,
							       CPP_COMMA));
		  آخری_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  ورنہ
	    توڑو;
	  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
	    توڑو;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *اگلا_tok = c_parser_peek_token (parser);
  اگر (اگلا_tok->type != CPP_CLOSE_BRACE)
    {
      ret.سیٹ_error ();
      ret.original_رمز = ERROR_MARK;
      ret.original_type = تہی;
      braces.skip_until_ملا_close (parser);
      نکالو_init_level (brace_loc, 0, &braced_init_obstack, آخری_init_list_comma);
      obstack_free (&braced_init_obstack, تہی);
      واپس ret;
    }
  location_t close_loc = اگلا_tok->location;
  c_parser_consume_token (parser);
  ret = نکالو_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  اگر (zero_init_padding_بٹ
      && ret.قدر
      && درخت_رمز (ret.قدر) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_بٹ (ret.قدر) = 1;
  obstack_free (&braced_init_obstack, تہی);
  سیٹ_c_اظہاریہ_ماخذ_range (&ret, brace_loc, close_loc);
  واپس ret;
}

/* Parse a nested initializer, including designators.  */

ساکن خالی
c_parser_initelt (c_parser *parser, ساخت obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      سیٹ_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->قدر,
		      c_parser_peek_token (parser)->location,
		      braced_init_obstack);
      /* Use the colon as the error location.  */
      pedwarn (c_parser_peek_2nd_token (parser)->location, OPT_Wpedantic,
	       "obsolete use of designated initializer with %<:%>");
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  ورنہ
    {
      /* des_seen is 0 if there have been no designators, 1 if there
	 has been a single array designator and 2 otherwise.  */
      صحیح des_نظر_آیا = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      جب (c_parser_اگلا_token_is (parser, CPP_OPEN_مربع)
	     || c_parser_اگلا_token_is (parser, CPP_DOT))
	{
	  صحیح des_پچھلا = des_نظر_آیا;
	  اگر (!des_نظر_آیا)
	    des_loc = c_parser_peek_token (parser)->location;
	  اگر (des_نظر_آیا < 2)
	    des_نظر_آیا++;
	  اگر (c_parser_اگلا_token_is (parser, CPP_DOT))
	    {
	      des_نظر_آیا = 2;
	      c_parser_consume_token (parser);
	      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
		{
		  سیٹ_init_label (des_loc, c_parser_peek_token (parser)->قدر,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      ورنہ
		{
		  ساخت c_اظہاریہ init;
		  init.سیٹ_error ();
		  init.original_رمز = ERROR_MARK;
		  init.original_type = تہی;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_ملا (parser, CPP_COMMA, تہی);
		  process_init_element (داخلہ_location, init, جھوٹ,
					braced_init_obstack);
		  واپس;
		}
	    }
	  ورنہ
	    {
	      ساخت c_اظہاریہ پہلا_اظہاریہ;
	      درخت پہلا, دوسرا;
	      location_t ellipsis_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	      location_t array_اشاریہ_loc = UNKNOWN_LOCATION;
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
	      اگر (des_پچھلا == 1 && c_dialect_objc ())
		{
		  des_نظر_آیا = des_پچھلا;
		  توڑو;
		}
	      اگر (des_پچھلا == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  درخت rec, دلائل;
		  ساخت c_اظہاریہ mexpr;
		  c_parser_consume_token (parser);
		  اگر (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_قسم
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_قسم
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      درخت id = c_parser_peek_token (parser)->قدر;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      جاؤ parse_پیغام_دلائل;
		    }
		  array_اشاریہ_loc = c_parser_peek_token (parser)->location;
		  پہلا_اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
		  mark_exp_read (پہلا_اظہاریہ.قدر);
		  اگر (c_parser_اگلا_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_اگلا_token_is (parser, CPP_CLOSE_مربع))
		    جاؤ array_desig_after_پہلا;
		  پہلا = پہلا_اظہاریہ.قدر;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = پہلا;
		  جب (c_parser_اگلا_token_is (parser, CPP_COMMA))
		    {
		      ساخت c_اظہاریہ اگلا;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      اگلا = c_parser_اظہاریہ_no_commas (parser, تہی);
		      اگلا = convert_lvalue_مقصد_rvalue (exp_loc, اگلا,
						       سچ, سچ);
		      rec = build_compound_اظہاریہ (comma_loc, rec, اگلا.قدر);
		    }
		parse_پیغام_دلائل:
		  /* Now parse the objc-message-args.  */
		  دلائل = c_parser_objc_پیغام_دلائل (parser);
		  c_parser_skip_until_ملا (parser, CPP_CLOSE_مربع,
					     "expected %<]%>");
		  mexpr.قدر
		    = objc_build_پیغام_اظہاریہ (rec, دلائل);
		  mexpr.original_رمز = ERROR_MARK;
		  mexpr.original_type = تہی;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  واپس;
		}
	      c_parser_consume_token (parser);
	      array_اشاریہ_loc = c_parser_peek_token (parser)->location;
	      پہلا_اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	      mark_exp_read (پہلا_اظہاریہ.قدر);
	    array_desig_after_پہلا:
	      پہلا_اظہاریہ = convert_lvalue_مقصد_rvalue (array_اشاریہ_loc,
						     پہلا_اظہاریہ,
						     سچ, سچ);
	      پہلا = پہلا_اظہاریہ.قدر;
	      اگر (c_parser_اگلا_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  دوسرا = convert_lvalue_مقصد_rvalue (ellipsis_loc,
						     (c_parser_اظہاریہ_no_commas
						      (parser, تہی)),
						     سچ, سچ).قدر;
		  mark_exp_read (دوسرا);
		}
	      ورنہ
		دوسرا = NULL_درخت;
	      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_مربع))
		{
		  c_parser_consume_token (parser);
		  سیٹ_init_اشاریہ (array_اشاریہ_loc, پہلا, دوسرا,
				  braced_init_obstack);
		  اگر (دوسرا)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      ورنہ
		c_parser_skip_until_ملا (parser, CPP_CLOSE_مربع,
					   "expected %<]%>");
	    }
	}
      اگر (des_نظر_آیا >= 1)
	{
	  اگر (c_parser_اگلا_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  ورنہ
	    {
	      اگر (des_نظر_آیا == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      ورنہ
		{
		  ساخت c_اظہاریہ init;
		  init.سیٹ_error ();
		  init.original_رمز = ERROR_MARK;
		  init.original_type = تہی;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_ملا (parser, CPP_COMMA, تہی);
		  process_init_element (داخلہ_location, init, جھوٹ,
					braced_init_obstack);
		  واپس;
		}
	    }
	}
    }
  c_parser_initval (parser, تہی, braced_init_obstack);
}

/* Parse a nested initializer; as c_parser_initializer but parses
   initializers within braced lists, after any designators have been
   applied.  If AFTER is not NULL then it is an Objective-C message
   expression which is the primary-expression starting the
   initializer.  */

ساکن خالی
c_parser_initval (c_parser *parser, ساخت c_اظہاریہ *after,
		  ساخت obstack * braced_init_obstack)
{
  ساخت c_اظہاریہ init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_درخت, سچ,
				 braced_init_obstack, جھوٹ);
  ورنہ
    {
      init = c_parser_اظہاریہ_no_commas (parser, after);
      اگر (init.قدر != NULL_درخت
	  && درخت_رمز (init.قدر) != STRING_CST
	  && (درخت_رمز (init.قدر) != COMPOUND_LITERAL_اظہاریہ
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_اظہاریہ_DECL
					    (init.قدر))))
	init = convert_lvalue_مقصد_rvalue (loc, init, سچ, سچ, سچ);
    }
  درخت val = init.قدر;
  process_init_element (loc, init, جھوٹ, braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  ساکن غیرعلامتی vals_مقصد_ignore;
  اگر (vals_مقصد_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_مقصد_ignore;
  ورنہ اگر (val
	   && درخت_رمز (val) == INTEGER_CST
	   && درخت_TYPE (val) == integer_type_گرہ
	   && c_parser_اگلا_token_is (parser, CPP_COMMA))
    اگر (غیرعلامتی صحیح len = c_maybe_optimize_large_byte_initializer ())
      {
	حرف buf1[64];
	غیرعلامتی صحیح i;
	gcc_checking_assert (len >= 64);
	location_t آخری_loc = UNKNOWN_LOCATION;
	برائے (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    اگر (tok->type != CPP_COMMA)
	      توڑو;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    اگر (tok->type != CPP_نمبر
		|| درخت_رمز (tok->قدر) != INTEGER_CST
		|| درخت_TYPE (tok->قدر) != integer_type_گرہ
		|| wi::neg_p (wi::مقصد_wide (tok->قدر))
		|| wi::مقصد_widest (tok->قدر) > UCHAR_MAX)
	      توڑو;
	    buf1[i] = (حرف) درخت_مقصد_uhwi (tok->قدر);
	    اگر (i == 0)
	      loc = tok->location;
	    آخری_loc = tok->location;
	  }
	اگر (i < 64)
	  {
	    vals_مقصد_ignore = i;
	    واپس;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	اگر (tok->type == CPP_CLOSE_BRACE && len != زیادہ_سے_زیادہ_عدد)
	  len = i;
	ورنہ اگر (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_نمبر))
	  {
	    vals_مقصد_ignore = i;
	    واپس;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	غیرعلامتی صحیح max_len = 131072 - offsetof (ساخت درخت_string, str) - 1;
	غیرعلامتی صحیح orig_len = len;
	غیرعلامتی صحیح off = 0, آخری = 0;
	اگر (!wi::neg_p (wi::مقصد_wide (val)) && wi::مقصد_widest (val) <= UCHAR_MAX)
	  off = 1;
	len = MIN (len, max_len - off);
	حرف *buf2 = XNEWVEC (حرف, len + off);
	اگر (off)
	  buf2[0] = (حرف) درخت_مقصد_uhwi (val);
	حافظہ_نقل (buf2 + off, buf1, i);
	برائے (غیرعلامتی صحیح j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	برائے (; i < len; ++i)
	  {
	    اگر (!c_parser_اگلا_token_is (parser, CPP_COMMA))
	      توڑو;
	    tok = c_parser_peek_2nd_token (parser);
	    اگر (tok->type != CPP_نمبر
		|| درخت_رمز (tok->قدر) != INTEGER_CST
		|| درخت_TYPE (tok->قدر) != integer_type_گرہ
		|| wi::neg_p (wi::مقصد_wide (tok->قدر))
		|| wi::مقصد_widest (tok->قدر) > UCHAR_MAX)
	      توڑو;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    اگر (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      توڑو;
	    buf2[i + off] = (حرف) درخت_مقصد_uhwi (tok->قدر);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    اگر (orig_len == زیادہ_سے_زیادہ_عدد
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_نمبر)))
	      {
		آخری = 1;
		توڑو;
	      }
	    آخری_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_گرہ (RAW_ڈیٹا_CST);
	درخت_TYPE (val) = integer_type_گرہ;
	RAW_ڈیٹا_لمبائی (val) = i;
	درخت owner = build_string (i + off + آخری, buf2);
	XDELETEVEC (buf2);
	درخت_TYPE (owner) = build_array_type_nelts (unsigned_char_type_گرہ,
						    i + off + آخری);
	RAW_ڈیٹا_OWNER (val) = owner;
	RAW_ڈیٹا_اشارہ_گر (val) = درخت_STRING_اشارہ_گر (owner) + off;
	init.قدر = val;
	سیٹ_c_اظہاریہ_ماخذ_range (&init, loc, آخری_loc);
	init.original_رمز = RAW_ڈیٹا_CST;
	init.original_type = integer_type_گرہ;
	init.m_decimal = 0;
	process_init_element (loc, init, جھوٹ, braced_init_obstack);
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

ساکن درخت
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  درخت stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  اگر (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (سچ);
      c_انتہا_compound_stmt (brace_loc, stmt, سچ);
      واپس error_mark_گرہ;
    }
  stmt = c_begin_compound_stmt (سچ);
  location_t انتہا_loc = c_parser_compound_statement_nostart (parser);
  اگر (endlocp)
    *endlocp = انتہا_loc;

  واپس c_انتہا_compound_stmt (brace_loc, stmt, سچ);
}

/* Diagnose errors related to imperfectly nested loops in an OMP
   loop construct.  This function is called when such code is seen.
   Only issue one such diagnostic no matter how much invalid
   intervening code there is in the loop.
   FIXME: maybe the location associated with the diagnostic should
   be the current parser token instead of the location of the outer loop
   nest.  */

ساکن خالی
check_omp_intervening_رمز (c_parser *parser)
{
  ساخت omp_for_parse_ڈیٹا *omp_for_parse_state = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);

  اگر (!omp_for_parse_state->اندر_intervening_رمز)
    واپس;
  omp_for_parse_state->saw_intervening_رمز = سچ;

  /* Only diagnose errors related to perfect nesting once.  */
  اگر (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      اگر (omp_for_parse_state->رمز == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = سچ;
	}
      ورنہ اگر (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = سچ;
	}
      ورنہ اگر (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = سچ;
	}
      ورنہ اگر (omp_for_parse_state->رمز == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = سچ;
	}
      اگر (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->fail = سچ;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
ساکن خالی
جوڑو_structured_بلاک_stmt (درخت sl)
{
  اگر (درخت_رمز (sl) != STATEMENT_LIST
      || !tsi_انتہا_p (tsi_آغاز (sl)))
    جوڑو_stmt (build1 (OMP_STRUCTURED_بلاک, void_type_گرہ, sl));
}

ساخت c_omp_attribute_ڈیٹا
{
  vec<c_token, va_gc> *علامات;
  ثابت c_omp_directive *dir;
  c_omp_directive_قسم قسم;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

ساکن منطقی
c_parser_handle_statement_omp_اوصاف (c_parser *parser, درخت &attrs,
					  منطقی *have_std_attrs)
{
  اگر (!flag_openmp && !flag_openmp_simd)
    واپس جھوٹ;

  auto_vec<c_omp_attribute_ڈیٹا, 16> vd;
  صحیح cnt = 0;
  صحیح علامات = 0;
  منطقی bad = جھوٹ;
  برائے (درخت *pa = &attrs; *pa; )
    اگر (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	برائے (درخت a = درخت_قدر (*pa); a; a = درخت_CHAIN (a))
	  {
	    درخت d = درخت_قدر (a);
	    gcc_assert (درخت_رمز (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_علامات (d);
	    c_token *پہلا = toks->پتہ ();
	    c_token *آخری = پہلا + toks->لمبائی ();
	    اگر (parser->omp_attrs_forbidden_p)
	      {
		error_at (پہلا->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = جھوٹ;
		bad = سچ;
	      }
	    ورنہ اگر (درخت_عوامی (d))
	      {
		error_at (پہلا->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		bad = سچ;
	      }
	    ثابت حرف *directive[3] = {};
	    برائے (صحیح i = 0; i < 3; i++)
	      {
		درخت id = NULL_درخت;
		اگر (پہلا + i == آخری)
		  توڑو;
		اگر (پہلا[i].type == CPP_NAME)
		  id = پہلا[i].قدر;
		ورنہ اگر (پہلا[i].type == CPP_KEYWORD)
		  id = ridpointers[(صحیح) پہلا[i].keyword];
		ورنہ
		  توڑو;
		directive[i] = IDENTIFIER_اشارہ_گر (id);
	      }
	    ثابت c_omp_directive *dir = تہی;
	    اگر (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    اگر (dir == تہی)
	      {
		error_at (پہلا->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  درخت_عوامی (d) ? "omp::decl" : "omp::directive");
		جاری;
	      }
	    c_omp_directive_قسم قسم = dir->قسم;
	    اگر (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		اگر (directive[1]
		    && (strcmp (directive[1], "depend") == 0
			|| strcmp (directive[1], "doacross") == 0))
		  قسم = C_OMP_DIR_STANDALONE;
		ورنہ اگر (پہلا + 2 < آخری
			 && پہلا[1].type == CPP_COMMA
			 && پہلا[2].type == CPP_NAME
			 && (strcmp (IDENTIFIER_اشارہ_گر (پہلا[2].قدر),
				     "depend") == 0
			     || strcmp (IDENTIFIER_اشارہ_گر (پہلا[2].قدر),
					"doacross") == 0))
		  قسم = C_OMP_DIR_STANDALONE;
	      }
	    ورنہ اگر (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		صحیح paren_گہرائی = 0;
		برائے (صحیح i = 1; پہلا + i < آخری; i++)
		  اگر (پہلا[i].type == CPP_OPEN_PAREN)
		    paren_گہرائی++;
		  ورنہ اگر (پہلا[i].type == CPP_CLOSE_PAREN)
		    paren_گہرائی--;
		  ورنہ اگر (paren_گہرائی == 0
			   && پہلا + i + 2 < آخری
			   && پہلا[i].type == CPP_NAME
			   && پہلا[i + 1].type == CPP_OPEN_PAREN
			   && پہلا[i + 2].type == CPP_NAME
			   && !strcmp (IDENTIFIER_اشارہ_گر (پہلا[i].قدر),
				       "at")
			   && !strcmp (IDENTIFIER_اشارہ_گر (پہلا[i
								 + 2].قدر),
				       "execution"))
		    {
		      قسم = C_OMP_DIR_STANDALONE;
		      توڑو;
		    }
	      }
	    c_omp_attribute_ڈیٹا v = { toks, dir, قسم };
	    vd.محفوظ_ڈالو (v);
	    اگر (flag_openmp || dir->simd)
	      علامات += (آخری - پہلا) + 1;
	  }
	c_omp_attribute_ڈیٹا v = {};
	vd.محفوظ_ڈالو (v);
	*pa = درخت_CHAIN (*pa);
      }
    ورنہ
      pa = &درخت_CHAIN (*pa);

  اگر (bad)
    {
    fail:
      اگر (have_std_attrs && attrs == تہی)
	*have_std_attrs = جھوٹ;
      واپس جھوٹ;
    }

  غیرعلامتی صحیح i;
  c_omp_attribute_ڈیٹا *v;
  c_omp_attribute_ڈیٹا *construct_نظر_آیا = خالی_اشاریہ;
  c_omp_attribute_ڈیٹا *standalone_نظر_آیا = خالی_اشاریہ;
  c_omp_attribute_ڈیٹا *پچھلا_standalone_نظر_آیا = خالی_اشاریہ;
  FOR_EACH_VEC_ELT (vd, i, v)
    اگر (v->علامات)
      {
	اگر (v->قسم == C_OMP_DIR_CONSTRUCT && !construct_نظر_آیا)
	  construct_نظر_آیا = v;
	ورنہ اگر (v->قسم == C_OMP_DIR_STANDALONE && !standalone_نظر_آیا)
	  standalone_نظر_آیا = v;
      }
    ورنہ
      {
	اگر (standalone_نظر_آیا && !پچھلا_standalone_نظر_آیا)
	  {
	    پچھلا_standalone_نظر_آیا = standalone_نظر_آیا;
	    standalone_نظر_آیا = خالی_اشاریہ;
	  }
      }

  اگر (cnt > 1 && construct_نظر_آیا)
    {
      error_at ((*construct_نظر_آیا->علامات)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      جاؤ fail;
    }
  اگر (cnt > 1 && standalone_نظر_آیا && پچھلا_standalone_نظر_آیا)
    {
      error_at ((*standalone_نظر_آیا->علامات)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      جاؤ fail;
    }

  اگر (پچھلا_standalone_نظر_آیا)
    standalone_نظر_آیا = پچھلا_standalone_نظر_آیا;
  اگر (standalone_نظر_آیا
      && !c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_نظر_آیا->علامات->پتہ ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      جاؤ fail;
    }
  اگر (cnt && c_parser_اگلا_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      شمار pragma_قسم قسم = token->pragma_قسم;
      اگر (قسم >= PRAGMA_OMP_آغاز && قسم <= PRAGMA_OMP_آخری)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  جاؤ fail;
	}
    }

  اگر (!علامات)
    واپس جھوٹ;

  غیرعلامتی صحیح علامات_avail = parser->علامات_avail;

  علامات++;
  vec<c_token, va_gc> *toks = تہی;
  vec_محفوظ_reserve (toks, علامات, سچ);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      اگر (!v->علامات)
	جاری;
      اگر (!flag_openmp && !v->dir->simd)
	جاری;
      c_token *پہلا = v->علامات->پتہ ();
      c_token *آخری = پہلا + v->علامات->لمبائی ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_قسم = pragma_قسم (v->dir->id);
      tok.location = پہلا->location;
      toks->تیز_ڈالو (tok);
      جب (++پہلا < آخری)
	toks->تیز_ڈالو (*پہلا);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = آخری[-1].location;
      toks->تیز_ڈالو (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->آخری ().location;
  toks->تیز_ڈالو (tok);

  gcc_assert (!parser->اندر_omp_attribute_pragma);
  parser->اندر_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->اندر_omp_attribute_pragma->token_vec = toks;
  parser->اندر_omp_attribute_pragma->save_علامات = parser->علامات;
  parser->اندر_omp_attribute_pragma->save_علامات_avail = علامات_avail;
  parser->علامات = toks->پتہ ();
  parser->علامات_avail = علامات;
  واپس سچ;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

ساکن خالی
c_parser_handle_directive_omp_اوصاف (درخت &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  اگر (!flag_openmp && !flag_openmp_simd)
    واپس;

  برائے (درخت *pa = &attrs; *pa; )
    اگر (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	صحیح cnt = 0;
	برائے (درخت *pa2 = &درخت_قدر (*pa); *pa2; )
	  {
	    درخت a = *pa2;
	    درخت d = درخت_قدر (a);
	    gcc_assert (درخت_رمز (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_علامات (d);
	    c_token *پہلا = toks->پتہ ();
	    c_token *آخری = پہلا + toks->لمبائی ();
	    ثابت حرف *directive[3] = {};
	    برائے (صحیح i = 0; i < 3; i++)
	      {
		درخت id = NULL_درخت;
		اگر (پہلا + i == آخری)
		  توڑو;
		اگر (پہلا[i].type == CPP_NAME)
		  id = پہلا[i].قدر;
		ورنہ اگر (پہلا[i].type == CPP_KEYWORD)
		  id = ridpointers[(صحیح) پہلا[i].keyword];
		ورنہ
		  توڑو;
		directive[i] = IDENTIFIER_اشارہ_گر (id);
	      }
	    ثابت c_omp_directive *dir = تہی;
	    اگر (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    اگر (dir == تہی)
	      {
		error_at (پہلا->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  درخت_عوامی (d) ? "omp::decl" : "omp::directive");
		*pa2 = درخت_CHAIN (a);
	      }
	    ورنہ اگر (dir->id == PRAGMA_OMP_DECLARE
		     && (strcmp (directive[1], "simd") == 0
			 || strcmp (directive[1], "variant") == 0))
	      {
		اگر (pragma_clauses)
		  {
		    error_at (پہلا->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    برائے (pa = &attrs; *pa; )
		      اگر (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = درخت_CHAIN (*pa);
		      ورنہ
			pa = &درخت_CHAIN (*pa);
		    واپس;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->لمبائی ()
				       + toks->لمبائی () + 2);
		برائے (++پہلا; پہلا < آخری; ++پہلا)
		  attr_clauses->تیز_ڈالو (*پہلا);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = آخری[-1].location;
		attr_clauses->تیز_ڈالو (tok);
		*pa2 = درخت_CHAIN (a);
	      }
	    ورنہ
	      pa2 = &درخت_CHAIN (a);
	  }
	اگر (cnt && درخت_قدر (*pa) == NULL_درخت)
	  *pa = درخت_CHAIN (*pa);
	ورنہ
	  pa = &درخت_CHAIN (*pa);
      }
    ورنہ
      pa = &درخت_CHAIN (*pa);
  اگر (attr_clauses->لمبائی ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->آخری ().location;
      attr_clauses->تیز_ڈالو (tok);
      attr_clauses->تیز_ڈالو (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

ساکن درخت
c_parser_handle_musttail (c_parser *parser, درخت std_attrs, attr_state &attr)
{
  اگر (c_parser_اگلا_token_is_keyword (parser, RID_RETURN))
    {
      اگر (درخت a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  برائے (; a; a = lookup_attribute ("gnu", "musttail", درخت_CHAIN (a)))
	    اگر (درخت_قدر (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = سچ;
	}
      اگر (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = سچ;
	}
    }
  واپس std_attrs;
}

/* Return a statement before optional series of LABEL_EXPR/CASE_LABEL_EXPRs.
   Instead of collecting vectors of labels before each stmt just in case
   the statement would be iteration or switch statement for named loops,
   we just remember last emitted statement and let the iteration/switch
   statement search backwards in cur_stmt_list until that stmt for loop
   names if any.  */

ساکن درخت
get_before_labels ()
{
  اگر (!building_stmt_list_p ())
    واپس NULL_درخت;
  درخت_stmt_iterator tsi = tsi_آخری (cur_stmt_list);
  اگر (tsi_انتہا_p (tsi))
    واپس NULL_درخت;
  واپس tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

ساکن location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  منطقی آخری_stmt = جھوٹ;
  منطقی آخری_label = جھوٹ;
  منطقی save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  ساخت omp_for_parse_ڈیٹا *omp_for_parse_state
    = parser->omp_for_parse_state;
  منطقی اندر_omp_loop_بلاک
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : جھوٹ;
  درخت sl = NULL_درخت;
  attr_state astate = {};

  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      جوڑو_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      واپس endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  اگر (اندر_omp_loop_بلاک)
    sl = ڈالو_stmt_list ();

  mark_valid_location_for_stdc_pragma (سچ);
  اگر (c_parser_اگلا_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (جھوٹ);
      اگر (اندر_omp_loop_بلاک)
	check_omp_intervening_رمز (parser);
      جب (c_parser_اگلا_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  جب (سچ)
	    {
	      درخت label;
	      اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  توڑو;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->قدر);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      جوڑو_stmt (build_stmt (label_loc, DECL_اظہاریہ, label));
	      c_parser_consume_token (parser);
	      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      ورنہ
		توڑو;
	    }
	  c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      واپس endloc;
    }
  درخت before_labels = get_before_labels ();
  جب (c_parser_اگلا_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_نقطہ_location_if_اندر_system_سرخی (loc);

      منطقی want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : جھوٹ);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      اگر (اندر_omp_loop_بلاک && !آخری_label)
	{
	  درخت_رمز_2 رمز = omp_for_parse_state->رمز;
	  اگر (want_nested_loop
	      && c_parser_omp_اگلا_علامات_can_be_canon_loop (parser, رمز,
							     جھوٹ))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      جوڑو_structured_بلاک_stmt (نکالو_stmt_list (sl));
	      omp_for_parse_state->گہرائی++;
	      جوڑو_stmt (c_parser_omp_loop_nest (parser, تہی));
	      omp_for_parse_state->گہرائی--;
	      sl = ڈالو_stmt_list ();
	      parser->error = جھوٹ;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      جاری;
	    }
	  ورنہ اگر (want_nested_loop
		   && c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      درخت pre_sl = نکالو_stmt_list (sl);
	      درخت nested_sl = ڈالو_stmt_list ();
	      mark_valid_location_for_stdc_pragma (جھوٹ);
	      c_parser_statement_after_labels (parser, تہی, NULL_درخت);
	      nested_sl = نکالو_stmt_list (nested_sl);
	      اگر (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_رمز (parser);
		  sl = ڈالو_stmt_list ();
		  جوڑو_stmt (pre_sl);
		  جوڑو_stmt (nested_sl);
		}
	      ورنہ
		{
		  /* It contains the nested loop.  */
		  جوڑو_structured_بلاک_stmt (pre_sl);
		  جوڑو_stmt (nested_sl);
		  sl = ڈالو_stmt_list ();
		}
	      parser->error = جھوٹ;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      جاری;
	    }
	  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
	    {
	      /* Prior to implementing the OpenMP 5.1 syntax for canonical
		 loop form, GCC used to accept an empty statements that
		 would now be flagged as intervening code.  Continue to
		 do that, as an extension.  */
	      /* FIXME:  Maybe issue a warning or something here?  */
	      c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
	      جاری;
	    }
	}

      /* Standard attributes may start a label, statement or declaration.  */
      منطقی have_std_attrs
	= c_parser_nth_token_starts_std_اوصاف (parser, 1);
      درخت std_attrs = NULL_درخت;
      اگر (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      اگر (c_parser_اگلا_token_is_keyword (parser, RID_CASE)
	  || c_parser_اگلا_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_اگلا_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  اگر (c_parser_اگلا_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  ورنہ
	    label_loc = c_parser_peek_token (parser)->location;
	  آخری_label = سچ;
	  آخری_stmt = جھوٹ;
	  mark_valid_location_for_stdc_pragma (جھوٹ);
	  اگر (اندر_omp_loop_بلاک)
	    check_omp_intervening_رمز (parser);
	  c_parser_label (parser, std_attrs);
	}
      ورنہ اگر (c_parser_اگلا_علامات_آغاز_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_اوصاف
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_اگلا_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = سچ)))
	{
	  اگر (آخری_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  اگر (اندر_omp_loop_بلاک)
	    {
	      check_omp_intervening_رمز (parser);
	      omp_for_parse_state->want_nested_loop = جھوٹ;
	    }
	  mark_valid_location_for_stdc_pragma (جھوٹ);
	  منطقی fallthru_attr_p = جھوٹ;
	  c_parser_declaration_or_fndef (parser, سچ, !have_std_attrs,
					 سچ, سچ, سچ, جھوٹ, تہی,
					 تہی, have_std_attrs, std_attrs,
					 تہی, &fallthru_attr_p);

	  اگر (اندر_omp_loop_بلاک)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  اگر (آخری_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  آخری_stmt = fallthru_attr_p;
	  آخری_label = جھوٹ;
	  before_labels = get_before_labels ();
	}
      ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  If standard attributes have already
	     been seen, it must start a statement, not a declaration,
	     but standard attributes starting a declaration may appear
	     after __extension__.  */
	  جب (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  اگر (!have_std_attrs
	      && (c_parser_اگلا_علامات_آغاز_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_اوصاف (parser, 2)))
	    {
	      صحیح ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      آخری_label = جھوٹ;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      اگر (اندر_omp_loop_بلاک)
		{
		  check_omp_intervening_رمز (parser);
		  omp_for_parse_state->want_nested_loop = جھوٹ;
		}
	      mark_valid_location_for_stdc_pragma (جھوٹ);
	      c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, سچ,
					     سچ, جھوٹ);
	      اگر (اندر_omp_loop_بلاک)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      اگر (آخری_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      آخری_stmt = جھوٹ;
	      before_labels = get_before_labels ();
	    }
	  ورنہ
	    جاؤ statement;
	}
      ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_PRAGMA))
	{
	  اگر (have_std_attrs && !parser->اندر_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  ورنہ اگر (std_attrs)
	    c_warn_غیر_مستعمل_اوصاف (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  اگر (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = جھوٹ;
	  اگر (c_parser_pragma (parser,
			       آخری_label ? pragma_stmt : pragma_compound,
			       تہی, before_labels))
	    {
	      آخری_label = جھوٹ;
	      آخری_stmt = سچ;
	      اگر (omp_for_parse_state)
		check_omp_intervening_رمز (parser);
	    }
	  اگر (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  واپس c_parser_peek_token (parser)->location;
	}
      ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_ELSE))
        {
          اگر (parser->اندر_if_بلاک)
            {
	      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	      error_at (loc, "expected %<}%> before %<else%>");
	      واپس c_parser_peek_token (parser)->location;
            }
          ورنہ
            {
              error_at (loc, "%<else%> without a previous %<if%>");
              c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
              جاری;
            }
        }
      ورنہ
	{
	statement:
	  c_warn_غیر_مستعمل_اوصاف (std_attrs);
	  آخری_label = جھوٹ;
	  آخری_stmt = سچ;
	  mark_valid_location_for_stdc_pragma (جھوٹ);
	  اگر (!omp_for_parse_state)
	    c_parser_statement_after_labels (parser, تہی, before_labels,
					     تہی, astate);
	  ورنہ
	    {
	      /* In canonical loop nest form, nested loops can only appear
		 directly, or in a directly nested compound statement.  We
		 already took care of those cases above, so now we have
		 something else.  This statement and everything inside
		 it must be intervening code.  */
	      omp_for_parse_state->want_nested_loop = جھوٹ;
	      check_omp_intervening_رمز (parser);
	      c_parser_statement_after_labels (parser, تہی, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = جھوٹ;
      astate.reset ();
    }
  اگر (آخری_label)
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
      sl = نکالو_stmt_list (sl);
      اگر (omp_for_parse_state->want_nested_loop)
	جوڑو_stmt (sl);
      ورنہ
	جوڑو_structured_بلاک_stmt (sl);
    }
  واپس endloc;
}

/* Parse all consecutive labels, possibly preceded by standard
   attributes.  In this context, a statement is required, not a
   declaration, so attributes must be followed by a statement that is
   not just a semicolon.  Returns an attr_state.  */

ساکن attr_state
c_parser_all_labels (c_parser *parser)
{
  attr_state attr = {};
  منطقی have_std_attrs;
  درخت std_attrs = تہی;
  اگر ((have_std_attrs = c_parser_nth_token_starts_std_اوصاف (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  جب (c_parser_اگلا_token_is_keyword (parser, RID_CASE)
	 || c_parser_اگلا_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_اگلا_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = تہی;
      اگر ((have_std_attrs = c_parser_nth_token_starts_std_اوصاف (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  اگر (std_attrs
      && (!c_parser_handle_statement_omp_اوصاف (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      اگر (have_std_attrs && c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_غیر_مستعمل_اوصاف (std_attrs);
    }
  ورنہ اگر (have_std_attrs && c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  واپس attr;
}


/* Information used while parsing an OpenMP metadirective.  */
ساخت omp_metadirective_parse_ڈیٹا {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<درخت> * GTY((skip)) body_labels;
  غیرعلامتی صحیح region_عدد;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
ساکن درخت
mangle_metadirective_region_label (c_parser *parser, درخت name)
{
  اگر (parser->omp_metadirective_state->body_labels->شامل_ہے (name))
    {
      ثابت حرف *old_name = IDENTIFIER_اشارہ_گر (name);
      حرف *new_name = (حرف *) XALLOCAVEC (حرف, لڑی_لمبائی (old_name) + 32);
      sprintf (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_عدد);
      واپس get_identifier (new_name);
    }
  واپس name;
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
ساکن خالی
c_parser_label (c_parser *parser, درخت std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  درخت label = NULL_درخت;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  منطقی fallthrough_p = c_parser_peek_token (parser)->flags & پچھلا_FALLTHROUGH;

  اگر (c_parser_اگلا_token_is_keyword (parser, RID_CASE))
    {
      درخت exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_مقصد_rvalue (loc1,
				       c_parser_اظہاریہ_no_commas (parser, تہی),
				       سچ, سچ).قدر;
      اگر (c_parser_اگلا_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_درخت, std_attrs);
	}
      ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_مقصد_rvalue (loc1,
					   c_parser_اظہاریہ_no_commas (parser,
								    تہی),
					   سچ, سچ).قدر;
	  اگر (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      ورنہ
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      اگر (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_درخت, NULL_درخت, std_attrs);
    }
  ورنہ
    {
      درخت name = c_parser_peek_token (parser)->قدر;
      درخت tlab;
      درخت attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_اگلا_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_اگلا_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_اوصاف (parser);
      اگر (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      اگر (tlab)
	{
	  decl_اوصاف (&tlab, attrs, 0);
	  decl_اوصاف (&tlab, std_attrs, 0);
	  label = جوڑو_stmt (build_stmt (loc1, LABEL_اظہاریہ, tlab));
	}
      اگر (attrs
	  && c_parser_اگلا_علامات_آغاز_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  اگر (label)
    {
      اگر (درخت_رمز (label) == LABEL_اظہاریہ)
	FALLTHROUGH_LABEL_P (LABEL_اظہاریہ_LABEL (label)) = fallthrough_p;
      ورنہ
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

ساکن خالی
c_parser_statement (c_parser *parser, منطقی *if_p, location_t *loc_after_labels)
{
  درخت before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  اگر (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = جھوٹ;
  c_parser_statement_after_labels (parser, if_p, before_labels, تہی, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

ساکن درخت
c_parser_bc_name (c_parser *parser, منطقی is_break)
{
  اگر (!c_parser_اگلا_token_is (parser, CPP_NAME))
    واپس NULL_درخت;

  c_token *tok = c_parser_peek_token (parser);
  درخت label = c_اختتام_bc_name (tok->location, tok->قدر, is_break);
  c_parser_consume_token (parser);
  واپس label;
}

/* Parse a statement, other than a labeled statement.  CHAIN is a vector
   of if-else-if conditions.  All labels and standard attributes have
   been parsed in the caller.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  ASTATE is an earlier parsed attribute state.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ساکن خالی
c_parser_statement_after_labels (c_parser *parser, منطقی *if_p,
				 درخت before_labels,
				 vec<درخت> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت stmt = NULL_درخت;
  منطقی اندر_if_بلاک = parser->اندر_if_بلاک;
  parser->اندر_if_بلاک = جھوٹ;
  اگر (if_p != تہی)
    *if_p = جھوٹ;

  اگر (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    جوڑو_debug_begin_stmt (loc);

 restart:
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_OPEN_BRACE:
      جوڑو_stmt (c_parser_compound_statement (parser));
      توڑو;
    حالت CPP_KEYWORD:
      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_IF:
	  c_parser_if_statement (parser, if_p, chain);
	  توڑو;
	حالت RID_SWITCH:
	  c_parser_switch_statement (parser, if_p, before_labels);
	  توڑو;
	حالت RID_WHILE:
	  c_parser_while_statement (parser, جھوٹ, 0, جھوٹ, if_p, before_labels);
	  توڑو;
	حالت RID_DO:
	  c_parser_do_statement (parser, جھوٹ, 0, جھوٹ, before_labels);
	  توڑو;
	حالت RID_FOR:
	  c_parser_for_statement (parser, جھوٹ, 0, جھوٹ, if_p, before_labels);
	  توڑو;
	حالت RID_GOTO:
	  c_parser_consume_token (parser);
	  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	    {
	      درخت name = c_parser_peek_token (parser)->قدر;
	      اگر (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_اختتام_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_MULT))
	    {
	      ساخت c_اظہاریہ val;

	      c_parser_consume_token (parser);
	      val = c_parser_عبارت (parser);
	      val = convert_lvalue_مقصد_rvalue (loc, val, جھوٹ, سچ);
	      stmt = c_اختتام_goto_ptr (loc, val);
	    }
	  ورنہ
	    c_parser_error (parser, "expected identifier or %<*%>");
	  جاؤ expect_semicolon;
	حالت RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_اختتام_bc_stmt (loc, objc_foreach_continue_label, جھوٹ,
				   c_parser_bc_name (parser, جھوٹ));
	  جاؤ expect_semicolon;
	حالت RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_اختتام_bc_stmt (loc, objc_foreach_break_label, سچ,
				   c_parser_bc_name (parser, سچ));
	  جاؤ expect_semicolon;
	حالت RID_RETURN:
	  c_parser_consume_token (parser);
	  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_اختتام_return (loc, NULL_درخت, NULL_درخت,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  ورنہ
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      ساخت c_اظہاریہ اظہاریہ = c_parser_عبارت_conv (parser);
	      mark_exp_read (اظہاریہ.قدر);
	      stmt = c_اختتام_return (اظہاریہ_LOC_OR_LOC (اظہاریہ.قدر, xloc),
				      اظہاریہ.قدر, اظہاریہ.original_type,
				      astate.musttail_p);
	      جاؤ expect_semicolon;
	    }
	  توڑو;
	حالت RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  توڑو;
	حالت RID_TRANSACTION_ATOMIC:
	حالت RID_TRANSACTION_RELAXED:
	  stmt = c_parser_transaction (parser,
	      c_parser_peek_token (parser)->keyword);
	  توڑو;
	حالت RID_TRANSACTION_CANCEL:
	  stmt = c_parser_transaction_cancel (parser);
	  جاؤ expect_semicolon;
	حالت RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_درخت);
	      c_parser_consume_token (parser);
	    }
	  ورنہ
	    {
	      ساخت c_اظہاریہ اظہاریہ = c_parser_عبارت (parser);
	      اظہاریہ = convert_lvalue_مقصد_rvalue (loc, اظہاریہ, جھوٹ, جھوٹ);
	      اظہاریہ.قدر = c_fully_fold (اظہاریہ.قدر, جھوٹ, تہی);
	      stmt = objc_build_throw_stmt (loc, اظہاریہ.قدر);
	      جاؤ expect_semicolon;
	    }
	  توڑو;
	حالت RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_finally_statement (parser);
	  توڑو;
	حالت RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  توڑو;
	حالت RID_ATTRIBUTE:
	  {
	    /* Allow '__attribute__((fallthrough));' or
	       '__attribute__((assume(cond)));' or
	       '__attribute__((musttail))) return'.  */
	    درخت attrs = c_parser_gnu_اوصاف (parser);
	    منطقی has_assume = lookup_attribute ("assume", attrs);
	    اگر (has_assume)
	      {
		اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, سچ);
		ورنہ
		  {
		    auto_urlify_اوصاف sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<assume%> attribute not followed by %<;%>");
		    has_assume = جھوٹ;
		  }
	      }
	    gcc_assert (!astate.musttail_p);
	    attrs = c_parser_handle_musttail (parser, attrs, astate);
	    اگر (astate.musttail_p)
	      {
		اگر (attrs)
		  {
		    auto_urlify_اوصاف sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		جاؤ restart;
	      }
	    اگر (attribute_fallthrough_p (attrs))
	      {
		اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
		  {
		    درخت fn = build_call_اظہاریہ_اندرونی_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_گرہ, 0);
		    جوڑو_stmt (fn);
		    /* Eat the ';'.  */
		    c_parser_consume_token (parser);
		  }
		ورنہ
		  {
		    auto_urlify_اوصاف sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<fallthrough%> attribute not followed "
				"by %<;%>");
		  }
	      }
	    ورنہ اگر (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    ورنہ اگر (attrs != NULL_درخت)
	      {
		auto_urlify_اوصاف sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    توڑو;
	  }
	طےشدہ:
	  جاؤ اظہاریہ_stmt;
	}
      توڑو;
    حالت CPP_SEMICOLON:
      c_parser_consume_token (parser);
      توڑو;
    حالت CPP_CLOSE_PAREN:
    حالت CPP_CLOSE_مربع:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      توڑو;
    حالت CPP_PRAGMA:
      اگر (!c_parser_pragma (parser, pragma_stmt, if_p, before_labels))
        جاؤ restart;
      توڑو;
    طےشدہ:
    اظہاریہ_stmt:
      stmt = c_اختتام_اظہاریہ_stmt (loc, c_parser_عبارت_conv (parser).قدر);
    expect_semicolon:
      c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
      توڑو;
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
  اگر (اظہاریہ_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_سیٹ_اظہاریہ_location (stmt, loc);

  parser->اندر_if_بلاک = اندر_if_بلاک;
}

/* Parse the condition from an if, do, while or for statements.  */

ساکن درخت
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت cond;
  cond = c_parser_عبارت_conv (parser).قدر;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, جھوٹ, تہی);
  اگر (warn_sequence_نقطہ)
    verify_sequence_points (cond);
  واپس cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

ساکن درخت
c_parser_paren_condition (c_parser *parser)
{
  درخت cond;
  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس error_mark_گرہ;
  cond = c_parser_condition (parser);
  parens.skip_until_ملا_close (parser);
  واپس cond;
}

/* Parse a selection-header:

   selection-header:
عبارت
     declaration expression
     simple-declaration

   simple-declaration:
     attribute-specifier-sequence[opt] declaration-specifiers declarator
       = initializer

  SWITCH_P is true if we are called from c_parser_switch_statement; in
  that case, don't perform the truthvalue conversion.  */

ساکن c_اظہاریہ
c_parser_selection_سرخی (c_parser *parser, منطقی switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_اظہاریہ اظہاریہ;
  منطقی parse_اظہاریہ = سچ;
  درخت std_attrs;
  منطقی have_std_attrs = c_parser_nth_token_starts_std_اوصاف (parser, 1);
  اگر (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  ورنہ
    std_attrs = NULL_درخت;
  اگر (c_parser_اگلا_علامات_آغاز_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      اظہاریہ.قدر
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/جھوٹ,
					 /*static_assert_ok=*/جھوٹ,
					 /*empty_ok=*/جھوٹ,
					 /*nested=*/سچ,
					 /*start_attr_ok=*/سچ,
					 /*simple_ok=*/سچ,
					 /*objc_foreach_object_decl=*/خالی_اشاریہ,
					 /*omp_declare_simd_clauses=*/خالی_اشاریہ,
					 have_std_attrs,
					 std_attrs);
      اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      ورنہ
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  اگر (!اظہاریہ.قدر)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      اظہاریہ.original_type = error_mark_گرہ;
	      اظہاریہ.سیٹ_error ();
	      واپس اظہاریہ;
	    }
	  parse_اظہاریہ = جھوٹ;
	}
      اگر (اظہاریہ.قدر)
	{
	  اظہاریہ.original_type = درخت_TYPE (اظہاریہ.قدر);
	  اظہاریہ = convert_lvalue_مقصد_rvalue (loc, اظہاریہ, /*convert_p=*/سچ,
					   /*read_p=*/سچ);
	}
    }
  ورنہ اگر (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      اظہاریہ.original_type = error_mark_گرہ;
      اظہاریہ.سیٹ_error ();
      واپس اظہاریہ;
    }

  اگر (parse_اظہاریہ)
    اظہاریہ = c_parser_عبارت_conv (parser);
  اگر (!switch_p)
    {
      اظہاریہ.قدر = c_objc_common_truthvalue_conversion (loc, اظہاریہ.قدر);
      اظہاریہ.قدر = c_fully_fold (اظہاریہ.قدر, جھوٹ, تہی);
      اگر (warn_sequence_نقطہ)
	verify_sequence_points (اظہاریہ.قدر);
    }
  واپس اظہاریہ;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

ساکن درخت
c_parser_paren_selection_سرخی (c_parser *parser)
{
  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس error_mark_گرہ;
  درخت cond = c_parser_selection_سرخی (parser, /*switch_p=*/جھوٹ).قدر;
  parens.skip_until_ملا_close (parser);
  واپس cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ساکن درخت
c_parser_c99_بلاک_statement (c_parser *parser, منطقی *if_p,
			      location_t *loc_after_labels)
{
  درخت بلاک = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  واپس c_انتہا_compound_stmt (loc, بلاک, flag_isoc99);
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

ساکن درخت
c_parser_if_body (c_parser *parser, منطقی *if_p,
		  ثابت token_indent_info &if_tinfo)
{
  درخت بلاک = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  درخت before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      جوڑو_stmt (build_خالی_خانے_stmt (loc));
      c_parser_consume_token (parser);
      اگر (!c_parser_اگلا_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
    جوڑو_stmt (c_parser_compound_statement (parser));
  ورنہ
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, تہی, a);
    }

  token_indent_info اگلا_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, اگلا_tinfo);
  اگر (body_loc_after_labels != UNKNOWN_LOCATION
      && اگلا_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, اگلا_tinfo.location,
				    if_tinfo.location, RID_IF);

  واپس c_انتہا_compound_stmt (body_loc, بلاک, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

ساکن درخت
c_parser_else_body (c_parser *parser, ثابت token_indent_info &else_tinfo,
		    vec<درخت> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  درخت بلاک = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  درخت before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      warning_at (loc,
		  OPT_Wempty_body,
	         "suggest braces around empty body in an %<else%> statement");
      جوڑو_stmt (build_خالی_خانے_stmt (loc));
      c_parser_consume_token (parser);
    }
  ورنہ
    {
      اگر (!c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, تہی, before_labels, chain, a);
    }

  token_indent_info اگلا_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, اگلا_tinfo);
  اگر (body_loc_after_labels != UNKNOWN_LOCATION
      && اگلا_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, اگلا_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  واپس c_انتہا_compound_stmt (body_loc, بلاک, flag_isoc99);
}

/* Parse an if statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   if-statement:
     if ( selection-header ) statement
     if ( selection-header ) statement else statement

   CHAIN is a vector of if-else-if conditions.
   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ساکن خالی
c_parser_if_statement (c_parser *parser, منطقی *if_p, vec<درخت> *chain)
{
  درخت بلاک;
  location_t loc;
  درخت cond;
  منطقی nested_if = جھوٹ;
  درخت پہلا_body, دوسرا_body;
  منطقی اندر_if_بلاک;

  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_IF));
  token_indent_info if_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  c_parser_consume_token (parser);
  بلاک = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_selection_سرخی (parser);
  اندر_if_بلاک = parser->اندر_if_بلاک;
  parser->اندر_if_بلاک = سچ;
  پہلا_body = c_parser_if_body (parser, &nested_if, if_tinfo);
  parser->اندر_if_بلاک = اندر_if_بلاک;

  اگر (warn_duplicated_cond)
    warn_duplicated_cond_جوڑو_or_warn (اظہاریہ_LOCATION (cond), cond, &chain);

  اگر (c_parser_اگلا_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      اگر (warn_duplicated_cond)
	{
	  اگر (c_parser_اگلا_token_is_keyword (parser, RID_IF)
	      && chain == تہی)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = نیا vec<درخت> ();
	      اگر (!CONSTANT_CLASS_P (cond) && !درخت_SIDE_EFFECTS (cond))
		chain->محفوظ_ڈالو (cond);
	    }
	  ورنہ اگر (!c_parser_اگلا_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      دوسرا_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      اگر (if_p != تہی)
	*if_p = سچ;
    }
  ورنہ
    {
      دوسرا_body = NULL_درخت;

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
  c_اختتام_if_stmt (loc, cond, پہلا_body, دوسرا_body);
  جوڑو_stmt (c_انتہا_compound_stmt (loc, بلاک, flag_isoc99));

  c_parser_maybe_reclassify_token (parser);
}

/* Parse a switch statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   switch-statement:
     switch (expression) statement

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ساکن خالی
c_parser_switch_statement (c_parser *parser, منطقی *if_p, درخت before_labels)
{
  ساخت c_اظہاریہ ce;
  درخت بلاک, اظہاریہ, body;
  غیرعلامتی حرف save_اندر_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  درخت switch_name;
  صحیح عدد_نام = c_get_loop_نام (before_labels, سچ, &switch_name);
  بلاک = c_begin_compound_stmt (flag_isoc99);
  منطقی explicit_cast_p = جھوٹ;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = سچ;
      ce = c_parser_selection_سرخی (parser, /*switch_p=*/سچ);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_مقصد_rvalue (switch_cond_loc, ce, سچ, سچ);
      اظہاریہ = ce.قدر;
      /* ??? expr has no valid location?  */
      parens.skip_until_ملا_close (parser);
    }
  ورنہ
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      اظہاریہ = error_mark_گرہ;
      ce.original_type = error_mark_گرہ;
    }
  درخت stmt
    = c_آغاز_switch (switch_loc, switch_cond_loc, اظہاریہ, explicit_cast_p,
		      switch_name);
  save_اندر_statement = اندر_statement;
  اندر_statement |= اندر_SWITCH_STMT;
  اگر (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      اندر_statement |= اندر_NAMED_STMT;
    }
  ورنہ
    اندر_statement &= ~اندر_NAMED_STMT;
  location_t loc_after_labels;
  منطقی open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_بلاک_statement (parser, if_p, &loc_after_labels);
  location_t اگلا_loc = c_parser_peek_token (parser)->location;
  اگر (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, اگلا_loc, switch_loc,
				    RID_SWITCH);
  c_اختتام_switch (body, ce.original_type);
  اندر_statement = save_اندر_statement;
  اگر (عدد_نام)
    {
      اگر (!C_DECL_LOOP_SWITCH_NAME_مستعمل (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_درخت;
      ورنہ
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_نام (عدد_نام);
    }
  جوڑو_stmt (c_انتہا_compound_stmt (switch_loc, بلاک, flag_isoc99));
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

ساکن خالی
c_parser_while_statement (c_parser *parser, منطقی ivdep, غیرعلامتی مختصر unroll,
			  منطقی novector, منطقی *if_p, درخت before_labels)
{
  درخت بلاک, cond, body;
  غیرعلامتی حرف save_اندر_statement;
  location_t loc;
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  درخت loop_name;
  صحیح عدد_نام = c_get_loop_نام (before_labels, جھوٹ, &loop_name);

  اگر (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = سچ;
    }

  c_parser_consume_token (parser);
  بلاک = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  اگر (ivdep && cond != error_mark_گرہ)
    cond = build3 (ANNOTATE_اظہاریہ, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گرہ,
				  annot_اظہاریہ_ivdep_قسم),
		   integer_zero_گرہ);
  اگر (unroll && cond != error_mark_گرہ)
    cond = build3 (ANNOTATE_اظہاریہ, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گرہ,
				  annot_اظہاریہ_unroll_قسم),
		   build_int_cst (integer_type_گرہ, unroll));
  اگر (novector && cond != error_mark_گرہ)
    cond = build3 (ANNOTATE_اظہاریہ, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گرہ,
				  annot_اظہاریہ_no_سمتیہ_قسم),
		   integer_zero_گرہ);
  save_اندر_statement = اندر_statement;
  اندر_statement = اندر_ITERATION_STMT;
  اگر (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      اندر_statement |= اندر_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  منطقی open_brace = c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_بلاک_statement (parser, if_p, &loc_after_labels);
  اگر (loop_name && !C_DECL_LOOP_SWITCH_NAME_مستعمل (loop_name))
    loop_name = NULL_درخت;
  جوڑو_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_درخت,
			NULL_درخت));
  جوڑو_stmt (c_انتہا_compound_stmt (loc, بلاک, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  اگر (عدد_نام)
    c_release_loop_نام (عدد_نام);

  token_indent_info اگلا_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, اگلا_tinfo);

  اگر (اگلا_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, اگلا_tinfo.location,
				    while_tinfo.location, RID_WHILE);

  اندر_statement = save_اندر_statement;
}

/* Parse a do statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   do-statement:
     do statement while ( expression ) ;

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ساکن خالی
c_parser_do_statement (c_parser *parser, منطقی ivdep, غیرعلامتی مختصر unroll,
		       منطقی novector, درخت before_labels)
{
  درخت بلاک, cond, body;
  غیرعلامتی حرف save_اندر_statement;
  location_t loc;
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_DO));
  درخت loop_name;
  صحیح عدد_نام = c_get_loop_نام (before_labels, جھوٹ, &loop_name);

  اگر (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = سچ;
    }

  c_parser_consume_token (parser);
  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  بلاک = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_اندر_statement = اندر_statement;
  اندر_statement = اندر_ITERATION_STMT;
  اگر (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      اندر_statement |= اندر_NAMED_STMT;
    }
  body = c_parser_c99_بلاک_statement (parser, تہی);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  اندر_statement = save_اندر_statement;
  اگر (عدد_نام)
    {
      اگر (!C_DECL_LOOP_SWITCH_NAME_مستعمل (loop_name))
	loop_name = NULL_درخت;
      c_release_loop_نام (عدد_نام);
    }
  cond = c_parser_paren_condition (parser);
  اگر (ivdep && cond != error_mark_گرہ)
    cond = build3 (ANNOTATE_اظہاریہ, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گرہ,
				  annot_اظہاریہ_ivdep_قسم),
		   integer_zero_گرہ);
  اگر (unroll && cond != error_mark_گرہ)
    cond = build3 (ANNOTATE_اظہاریہ, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گرہ,
				  annot_اظہاریہ_unroll_قسم),
 		   build_int_cst (integer_type_گرہ, unroll));
  اگر (novector && cond != error_mark_گرہ)
    cond = build3 (ANNOTATE_اظہاریہ, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گرہ,
				  annot_اظہاریہ_no_سمتیہ_قسم),
		   integer_zero_گرہ);
  اگر (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);

  جوڑو_stmt (build_stmt (loc, DO_STMT, cond, body, loop_name));
  جوڑو_stmt (c_انتہا_compound_stmt (loc, بلاک, flag_isoc99));
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

ساکن خالی
c_parser_for_statement (c_parser *parser, منطقی ivdep, غیرعلامتی مختصر unroll,
			منطقی novector, منطقی *if_p, درخت before_labels)
{
  درخت بلاک, cond, incr, body;
  غیرعلامتی حرف save_اندر_statement;
  درخت save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  درخت object_عبارت;
  /* Silence the bogus uninitialized warning.  */
  درخت collection_عبارت = تہی;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  منطقی is_foreach_statement = جھوٹ;
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  درخت loop_name;
  صحیح عدد_نام = c_get_loop_نام (before_labels, جھوٹ, &loop_name);

  اگر (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = سچ;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  بلاک = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_گرہ;
  incr = error_mark_گرہ;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_عبارت = error_mark_گرہ;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = جھوٹ;
	  c_parser_consume_token (parser);
	  c_اختتام_اظہاریہ_stmt (loc, NULL_درخت);
	}
      ورنہ اگر (c_parser_اگلا_علامات_آغاز_declaration (parser)
	       || c_parser_nth_token_starts_std_اوصاف (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, سچ, سچ,
					 جھوٹ, &object_عبارت);
	  parser->objc_could_be_foreach_context = جھوٹ;

	  اگر (c_parser_اگلا_token_is_keyword (parser, RID_اندر))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = سچ;
	      اگر (check_for_loop_decls (for_loc, سچ) == NULL_درخت)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  ورنہ
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  جب (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  اگر (c_parser_اگلا_علامات_آغاز_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_اوصاف (parser, 2))
	    {
	      صحیح ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, سچ,
					     سچ, جھوٹ, &object_عبارت);
	      parser->objc_could_be_foreach_context = جھوٹ;

	      restore_extension_diagnostics (ext);
	      اگر (c_parser_اگلا_token_is_keyword (parser, RID_اندر))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = سچ;
		  اگر (check_for_loop_decls (for_loc, سچ) == NULL_درخت)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      ورنہ
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  ورنہ
	    جاؤ init_اظہاریہ;
	}
      ورنہ
	{
	init_اظہاریہ:
	  {
	    ساخت c_اظہاریہ ce;
	    درخت init_عبارت;
	    ce = c_parser_عبارت (parser);
	    init_عبارت = ce.قدر;
	    parser->objc_could_be_foreach_context = جھوٹ;
	    اگر (c_parser_اگلا_token_is_keyword (parser, RID_اندر))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = سچ;
		اگر (! lvalue_p (init_عبارت))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_عبارت
		  = c_fully_fold (init_عبارت, جھوٹ, تہی);
	      }
	    ورنہ
	      {
		ce = convert_lvalue_مقصد_rvalue (loc, ce, سچ, جھوٹ);
		init_عبارت = ce.قدر;
		c_اختتام_اظہاریہ_stmt (loc, init_عبارت);
		c_parser_skip_until_ملا (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      اگر (!is_foreach_statement)
	{
	  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
	    {
	      اگر (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_گرہ;
		}
	      ورنہ اگر (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_گرہ;
		}
	      ورنہ
		{
		  c_parser_consume_token (parser);
		  cond = NULL_درخت;
		}
	    }
	  ورنہ
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_ملا (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  اگر (ivdep && cond != error_mark_گرہ)
	    cond = build3 (ANNOTATE_اظہاریہ, درخت_TYPE (cond), cond,
			   build_int_cst (integer_type_گرہ,
					  annot_اظہاریہ_ivdep_قسم),
			   integer_zero_گرہ);
	  اگر (unroll && cond != error_mark_گرہ)
	    cond = build3 (ANNOTATE_اظہاریہ, درخت_TYPE (cond), cond,
 			   build_int_cst (integer_type_گرہ,
					  annot_اظہاریہ_unroll_قسم),
			   build_int_cst (integer_type_گرہ, unroll));
	  اگر (novector && cond && cond != error_mark_گرہ)
	    cond = build3 (ANNOTATE_اظہاریہ, درخت_TYPE (cond), cond,
			   build_int_cst (integer_type_گرہ,
					  annot_اظہاریہ_no_سمتیہ_قسم),
			   integer_zero_گرہ);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	{
	  اگر (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_عبارت = error_mark_گرہ;
	    }
	  ورنہ
	    incr = c_process_اظہاریہ_stmt (loc, NULL_درخت);
	}
      ورنہ
	{
	  اگر (is_foreach_statement)
	    collection_عبارت
	      = c_fully_fold (c_parser_عبارت (parser).قدر, جھوٹ, تہی);
	  ورنہ
	    {
	      ساخت c_اظہاریہ ce = c_parser_عبارت (parser);
	      ce = convert_lvalue_مقصد_rvalue (loc, ce, سچ, جھوٹ);
	      incr = c_process_اظہاریہ_stmt (loc, ce.قدر);
	    }
	}
      parens.skip_until_ملا_close (parser);
    }
  save_اندر_statement = اندر_statement;
  اگر (is_foreach_statement)
    {
      اندر_statement = اندر_OBJC_FOREACH;
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
  ورنہ
    اندر_statement = اندر_ITERATION_STMT;
  اگر (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      اندر_statement |= اندر_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  منطقی open_brace = c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_بلاک_statement (parser, if_p, &loc_after_labels);

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
    objc_اختتام_foreach_loop (for_loc, object_عبارت,
			      collection_عبارت, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  ورنہ
    جوڑو_stmt (build_stmt (for_loc, FOR_STMT, NULL_درخت, cond, incr,
			  body, NULL_درخت,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_مستعمل (loop_name)
			  ? loop_name : NULL_درخت, NULL_درخت, NULL_درخت));
  جوڑو_stmt (c_انتہا_compound_stmt (for_loc, بلاک,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info اگلا_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, اگلا_tinfo);

  اگر (اگلا_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, اگلا_tinfo.location,
				    for_tinfo.location, RID_FOR);

  اندر_statement = save_اندر_statement;
  اگر (عدد_نام)
    c_release_loop_نام (عدد_نام);
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

ساکن درخت
c_parser_asm_statement (c_parser *parser)
{
  درخت str, outputs, inputs, clobbers, labels, ret;
  منطقی simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  صحیح section, nsections;

  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);

  /* Handle the asm-qualifier-list.  */
  location_t volatile_loc = UNKNOWN_LOCATION;
  location_t inline_loc = UNKNOWN_LOCATION;
  location_t goto_loc = UNKNOWN_LOCATION;
  برائے (;;)
    {
      c_token *token = c_parser_peek_token (parser);
      location_t loc = token->location;
      انتخاب (token->keyword)
	{
	حالت RID_VOLATILE:
	  اگر (volatile_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->قدر);
	      inform (volatile_loc, "first seen here");
	    }
	  ورنہ
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  جاری;

	حالت RID_INLINE:
	  اگر (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->قدر);
	      inform (inline_loc, "first seen here");
	    }
	  ورنہ
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  جاری;

	حالت RID_GOTO:
	  اگر (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->قدر);
	      inform (goto_loc, "first seen here");
	    }
	  ورنہ
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  جاری;

	حالت RID_CONST:
	حالت RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->قدر);
	  c_parser_consume_token (parser);
	  جاری;

	طےشدہ:
	  توڑو;
	}
      توڑو;
    }

  منطقی is_volatile = (volatile_loc != UNKNOWN_LOCATION);
  منطقی is_inline = (inline_loc != UNKNOWN_LOCATION);
  منطقی is_goto = (goto_loc != UNKNOWN_LOCATION);

  ret = تہی;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    جاؤ error;

  str = c_parser_asm_string_literal (parser);
  اگر (str == NULL_درخت)
    جاؤ error_close_paren;

  simple = سچ;
  outputs = NULL_درخت;
  inputs = NULL_درخت;
  clobbers = NULL_درخت;
  labels = NULL_درخت;

  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    جاؤ مکمل_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  برائے (section = 0; section < nsections; ++section)
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  اگر (section == nsections)
	    {
	      c_parser_error (parser, "expected %<)%>");
	      جاؤ error_close_paren;
	    }
	  c_parser_consume_token (parser);
	}
      ورنہ اگر (!c_parser_require (parser, CPP_COLON,
				  is_goto
				  ? G_("expected %<:%>")
				  : G_("expected %<:%> or %<)%>"),
				  UNKNOWN_LOCATION, is_goto))
	جاؤ error_close_paren;

      /* Once past any colon, we're no longer a simple asm.  */
      simple = جھوٹ;

      اگر ((!c_parser_اگلا_token_is (parser, CPP_COLON)
	   && !c_parser_اگلا_token_is (parser, CPP_SCOPE)
	   && !c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	  || section == 3)
	انتخاب (section)
	  {
	  حالت 0:
	    outputs = c_parser_asm_operands (parser);
	    توڑو;
	  حالت 1:
	    inputs = c_parser_asm_operands (parser);
	    توڑو;
	  حالت 2:
	    clobbers = c_parser_asm_clobbers (parser);
	    توڑو;
	  حالت 3:
	    labels = c_parser_asm_goto_operands (parser);
	    توڑو;
	  طےشدہ:
	    gcc_unreachable ();
	  }

      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	جاؤ مکمل_asm;
    }

 مکمل_asm:
  اگر (!parens.require_close (parser))
    {
      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
      جاؤ error;
    }

  اگر (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_اظہاریہ (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  واپس ret;

 error_close_paren:
  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
  جاؤ error;
}

/* Parse asm operands, a GNU extension.

   asm-operands:
     asm-operand
     asm-operands , asm-operand

   asm-operand:
     asm-string-literal ( expression )
     [ identifier ] asm-string-literal ( expression )
*/

ساکن درخت
c_parser_asm_operands (c_parser *parser)
{
  درخت list = NULL_درخت;
  جب (سچ)
    {
      درخت name, str;
      ساخت c_اظہاریہ اظہاریہ;
      اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_مربع))
	{
	  c_parser_consume_token (parser);
	  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	    {
	      درخت id = c_parser_peek_token (parser)->قدر;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_لمبائی (id),
				   IDENTIFIER_اشارہ_گر (id));
	    }
	  ورنہ
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_ملا (parser, CPP_CLOSE_مربع, تہی);
	      واپس NULL_درخت;
	    }
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_مربع,
				     "expected %<]%>");
	}
      ورنہ
	name = NULL_درخت;
      str = c_parser_asm_string_literal (parser);
      اگر (str == NULL_درخت)
	واپس NULL_درخت;
      matching_parens parens;
      اگر (!parens.require_open (parser))
	واپس NULL_درخت;
      اظہاریہ = c_parser_عبارت (parser);
      mark_exp_read (اظہاریہ.قدر);
      اگر (!parens.require_close (parser))
	{
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
	  واپس NULL_درخت;
	}
      list = chainon (list, build_درخت_list (build_درخت_list (name, str),
					     اظہاریہ.قدر));
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ورنہ
	توڑو;
    }
  واپس list;
}

/* Parse asm clobbers, a GNU extension.

   asm-clobbers:
     asm-string-literal
     asm-clobbers , asm-string-literal
*/

ساکن درخت
c_parser_asm_clobbers (c_parser *parser)
{
  درخت list = NULL_درخت;
  جب (سچ)
    {
      درخت str = c_parser_asm_string_literal (parser);
      اگر (str)
	list = درخت_cons (NULL_درخت, str, list);
      ورنہ
	واپس NULL_درخت;
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ورنہ
	توڑو;
    }
  واپس list;
}

/* Parse asm goto labels, a GNU extension.

   asm-goto-operands:
     identifier
     asm-goto-operands , identifier
*/

ساکن درخت
c_parser_asm_goto_operands (c_parser *parser)
{
  درخت list = NULL_درخت;
  جب (سچ)
    {
      درخت name, label;

      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->قدر;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  درخت_مستعمل (label) = 1;
	}
      ورنہ
	{
	  c_parser_error (parser, "expected identifier");
	  واپس NULL_درخت;
	}

      name = build_string (IDENTIFIER_لمبائی (name),
			   IDENTIFIER_اشارہ_گر (name));
      list = درخت_cons (name, label, list);
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ورنہ
	واپس nreverse (list);
    }
}

/* Parse a possibly concatenated sequence of string literals.
   TRANSLATE says whether to translate them to the execution character
   set; WIDE_OK says whether any kind of prefixed string literal is
   permitted in this context.  This code is based on that in
   lex_string.  */

ساخت c_اظہاریہ
c_parser_string_literal (c_parser *parser, منطقی translate, منطقی wide_ok)
{
  ساخت c_اظہاریہ ret;
  سائز_t گنتی;
  ساخت obstack str_ob;
  ساخت obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, آخری_tok_loc;
  شمار cpp_ttype type;
  درخت قدر, string_درخت;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  آخری_tok_loc = linemap_resolve_location (سطر_جدول, loc,
					   LRK_MACRO_DEFINITION_LOCATION,
					   تہی);
  type = tok->type;
  انتخاب (type)
    {
    حالت CPP_STRING:
    حالت CPP_WSTRING:
    حالت CPP_STRING16:
    حالت CPP_STRING32:
    حالت CPP_UTF8STRING:
      string_درخت = tok->قدر;
      توڑو;

    طےشدہ:
      c_parser_error (parser, "expected string literal");
      ret.سیٹ_error ();
      ret.قدر = NULL_درخت;
      ret.original_رمز = ERROR_MARK;
      ret.original_type = NULL_درخت;
      واپس ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  انتخاب (c_parser_peek_2nd_token (parser)->type)
    {
    طےشدہ:
      c_parser_consume_token (parser);
      str.متن = (ثابت غیرعلامتی حرف *) درخت_STRING_اشارہ_گر (string_درخت);
      str.len = درخت_STRING_لمبائی (string_درخت);
      گنتی = 1;
      strs = &str;
      توڑو;

    حالت CPP_STRING:
    حالت CPP_WSTRING:
    حالت CPP_STRING16:
    حالت CPP_STRING32:
    حالت CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      گنتی = 0;
      کرو
	{
	  c_parser_consume_token (parser);
	  گنتی++;
	  str.متن = (ثابت غیرعلامتی حرف *) درخت_STRING_اشارہ_گر (string_درخت);
	  str.len = درخت_STRING_لمبائی (string_درخت);
	  اگر (type != tok->type)
	    {
	      اگر (type == CPP_STRING)
		type = tok->type;
	      ورنہ اگر (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, حجم (cpp_string));
	  obstack_grow (&loc_ob, &آخری_tok_loc, حجم (location_t));
	  tok = c_parser_peek_token (parser);
	  string_درخت = tok->قدر;
	  آخری_tok_loc
	    = linemap_resolve_location (سطر_جدول, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, تہی);
	}
      جب (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_اختتام (&str_ob);
    }

  اگر (گنتی > 1 && !اندر_system_سرخی_at (داخلہ_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  اگر ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_اندر, strs, گنتی, &istr, type)))
    {
      قدر = build_string (istr.len, (ثابت حرف *) istr.متن);
      آزاد (const_cast<غیرعلامتی حرف *> (istr.متن));
      اگر (گنتی > 1)
	{
	  location_t *locs = (location_t *) obstack_اختتام (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->ریکارڈ_string_concatenation (گنتی, locs);
	}
    }
  ورنہ
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
	طےشدہ:
	حالت CPP_STRING:
	حالت CPP_UTF8STRING:
	  اگر (type == CPP_UTF8STRING && flag_char8_t)
	    {
	      قدر = build_string (TYPE_PRECISION (char8_type_گرہ)
				    / TYPE_PRECISION (char_type_گرہ),
				    "");  /* char8_t is 8 bits */
	    }
	  ورنہ
	    قدر = build_string (1, "");
	  توڑو;
	حالت CPP_STRING16:
	  قدر = build_string (TYPE_PRECISION (char16_type_گرہ)
				/ TYPE_PRECISION (char_type_گرہ),
				"\0");  /* char16_t is 16 bits */
	  توڑو;
	حالت CPP_STRING32:
	  قدر = build_string (TYPE_PRECISION (char32_type_گرہ)
				/ TYPE_PRECISION (char_type_گرہ),
				"\0\0\0");  /* char32_t is 32 bits */
	  توڑو;
	حالت CPP_WSTRING:
	  قدر = build_string (TYPE_PRECISION (wchar_type_گرہ)
				/ TYPE_PRECISION (char_type_گرہ),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  توڑو;
        }
    }

  انتخاب (type)
    {
    طےشدہ:
    حالت CPP_STRING:
      درخت_TYPE (قدر) = char_array_type_گرہ;
      توڑو;
    حالت CPP_UTF8STRING:
      اگر (flag_char8_t)
	درخت_TYPE (قدر) = char8_array_type_گرہ;
      ورنہ
	درخت_TYPE (قدر) = char_array_type_گرہ;
      توڑو;
    حالت CPP_STRING16:
      درخت_TYPE (قدر) = char16_array_type_گرہ;
      توڑو;
    حالت CPP_STRING32:
      درخت_TYPE (قدر) = char32_array_type_گرہ;
      توڑو;
    حالت CPP_WSTRING:
      درخت_TYPE (قدر) = wchar_array_type_گرہ;
    }
  قدر = fix_string_type (قدر);

  اگر (گنتی > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.قدر = قدر;
  ret.original_رمز = STRING_CST;
  ret.original_type = NULL_درخت;
  سیٹ_c_اظہاریہ_ماخذ_range (&ret, get_range_from_loc (سطر_جدول, loc));
  ret.m_decimal = 0;
  parser->نظر_آیا_string_literal = سچ;
  واپس ret;
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

ساکن ساخت c_اظہاریہ
c_parser_اظہاریہ_no_commas (c_parser *parser, ساخت c_اظہاریہ *after,
			 درخت omp_atomic_lhs)
{
  ساخت c_اظہاریہ lhs, rhs, ret;
  شمار درخت_رمز_2 رمز;
  location_t op_location, exp_location;
  منطقی save_اندر_omp_for = c_اندر_omp_for;
  c_اندر_omp_for = جھوٹ;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_عبارت (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_EQ:
      رمز = NOP_اظہاریہ;
      توڑو;
    حالت CPP_MULT_EQ:
      رمز = MULT_اظہاریہ;
      توڑو;
    حالت CPP_DIV_EQ:
      رمز = TRUNC_DIV_اظہاریہ;
      توڑو;
    حالت CPP_MOD_EQ:
      رمز = TRUNC_MOD_اظہاریہ;
      توڑو;
    حالت CPP_PLUS_EQ:
      رمز = PLUS_اظہاریہ;
      توڑو;
    حالت CPP_MINUS_EQ:
      رمز = MINUS_اظہاریہ;
      توڑو;
    حالت CPP_LSHIFT_EQ:
      رمز = LSHIFT_اظہاریہ;
      توڑو;
    حالت CPP_RSHIFT_EQ:
      رمز = RSHIFT_اظہاریہ;
      توڑو;
    حالت CPP_AND_EQ:
      رمز = ثنائی_ہندسہ_AND_اظہاریہ;
      توڑو;
    حالت CPP_XOR_EQ:
      رمز = ثنائی_ہندسہ_XOR_اظہاریہ;
      توڑو;
    حالت CPP_OR_EQ:
      رمز = ثنائی_ہندسہ_IOR_اظہاریہ;
      توڑو;
    طےشدہ:
      c_اندر_omp_for = save_اندر_omp_for;
      واپس lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_اظہاریہ_no_commas (parser, تہی);
  rhs = convert_lvalue_مقصد_rvalue (exp_location, rhs, سچ, سچ);

  ret.قدر = build_modify_اظہاریہ (op_location, lhs.قدر, lhs.original_type,
				 رمز, exp_location, rhs.قدر,
				 rhs.original_type);
  ret.m_decimal = 0;
  سیٹ_c_اظہاریہ_ماخذ_range (&ret, lhs.get_آغاز (), rhs.get_اختتام ());
  اگر (رمز == NOP_اظہاریہ)
    ret.original_رمز = MODIFY_اظہاریہ;
  ورنہ
    {
      suppress_warning (ret.قدر, OPT_Wparentheses);
      ret.original_رمز = ERROR_MARK;
    }
  ret.original_type = تہی;
  c_اندر_omp_for = save_اندر_omp_for;
  واپس ret;
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

ساکن ساخت c_اظہاریہ
c_parser_conditional_عبارت (c_parser *parser, ساخت c_اظہاریہ *after,
				 درخت omp_atomic_lhs)
{
  ساخت c_اظہاریہ cond, exp1, exp2, ret;
  location_t آغاز, cond_loc, colon_loc;
  منطقی save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_ثنائی_عبارت (parser, after, omp_atomic_lhs);

  اگر (c_parser_اگلا_token_is_not (parser, CPP_QUERY))
    واپس cond;
  c_omp_array_section_p = جھوٹ;
  اگر (cond.قدر != error_mark_گرہ)
    آغاز = cond.get_آغاز ();
  ورنہ
    آغاز = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_مقصد_rvalue (cond_loc, cond, سچ, سچ);
  c_parser_consume_token (parser);
  اگر (c_parser_اگلا_token_is (parser, CPP_COLON))
    {
      درخت eptype = NULL_درخت;

      location_t درمیان_loc = c_parser_peek_token (parser)->location;
      pedwarn (درمیان_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      اگر (درخت_رمز (cond.قدر) == EXCESS_PRECISION_اظہاریہ)
	{
	  eptype = درخت_TYPE (cond.قدر);
	  cond.قدر = درخت_عملیہ (cond.قدر, 0);
	}
      درخت e = cond.قدر;
      جب (درخت_رمز (e) == COMPOUND_اظہاریہ)
	e = درخت_عملیہ (e, 1);
      warn_for_omitted_condop (درمیان_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.قدر = save_اظہاریہ (default_conversion (cond.قدر));
      اگر (eptype)
	exp1.قدر = build1 (EXCESS_PRECISION_اظہاریہ, eptype, exp1.قدر);
      exp1.original_type = تہی;
      exp1.src_range = cond.src_range;
      cond.قدر = c_objc_common_truthvalue_conversion (cond_loc, exp1.قدر);
      c_inhibit_evaluation_warnings += cond.قدر == truthvalue_true_گرہ;
    }
  ورنہ
    {
      cond.قدر
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.قدر));
      c_inhibit_evaluation_warnings += cond.قدر == truthvalue_false_گرہ;
      exp1 = c_parser_عبارت_conv (parser);
      mark_exp_read (exp1.قدر);
      c_inhibit_evaluation_warnings +=
	((cond.قدر == truthvalue_true_گرہ)
	 - (cond.قدر == truthvalue_false_گرہ));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.قدر == truthvalue_true_گرہ;
      ret.سیٹ_error ();
      ret.original_رمز = ERROR_MARK;
      ret.original_type = تہی;
      c_omp_array_section_p = save_c_omp_array_section_p;
      واپس ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_عبارت (parser, تہی, NULL_درخت);
    exp2 = convert_lvalue_مقصد_rvalue (exp2_loc, exp2, سچ, سچ);
  }
  c_inhibit_evaluation_warnings -= cond.قدر == truthvalue_true_گرہ;
  location_t loc1 = make_location (exp1.get_آغاز (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_آغاز (), exp2.src_range);
  اگر (UNLIKELY (omp_atomic_lhs != تہی)
      && (درخت_رمز (cond.قدر) == GT_اظہاریہ
	  || درخت_رمز (cond.قدر) == LT_اظہاریہ
	  || درخت_رمز (cond.قدر) == EQ_اظہاریہ)
      && c_درخت_equal (exp2.قدر, omp_atomic_lhs)
      && (c_درخت_equal (درخت_عملیہ (cond.قدر, 0), omp_atomic_lhs)
	  || c_درخت_equal (درخت_عملیہ (cond.قدر, 1), omp_atomic_lhs)))
    ret.قدر = build3_loc (colon_loc, COND_اظہاریہ, درخت_TYPE (omp_atomic_lhs),
			    cond.قدر, exp1.قدر, exp2.قدر);
  ورنہ
    ret.قدر
      = build_conditional_اظہاریہ (colon_loc, cond.قدر,
				cond.original_رمز == C_MAYBE_CONST_اظہاریہ,
				exp1.قدر, exp1.original_type, loc1,
				exp2.قدر, exp2.original_type, loc2);
  ret.original_رمز = ERROR_MARK;
  اگر (exp1.قدر == error_mark_گرہ || exp2.قدر == error_mark_گرہ)
    ret.original_type = تہی;
  ورنہ
    {
      درخت t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : درخت_TYPE (exp1.قدر);
      t2 = exp2.original_type ? exp2.original_type : درخت_TYPE (exp2.قدر);
      ret.original_type = ((t1 != error_mark_گرہ
			    && t2 != error_mark_گرہ
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : تہی);
    }
  سیٹ_c_اظہاریہ_ماخذ_range (&ret, آغاز, exp2.get_اختتام ());
  ret.m_decimal = 0;
  c_omp_array_section_p = save_c_omp_array_section_p;
  واپس ret;
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

ساکن ساخت c_اظہاریہ
c_parser_ثنائی_عبارت (c_parser *parser, ساخت c_اظہاریہ *after,
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

  ساخت {
    /* The expression at this stack level.  */
    ساخت c_اظہاریہ اظہاریہ;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    شمار c_parser_prec prec;
    /* The operation on its left.  */
    شمار درخت_رمز_2 op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    درخت sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    درخت orig_اظہاریہ;
  } ڈھیر[عدد_PRECS];
  صحیح sp;
  /* Location of the binary operator.  */
  location_t ثنائی_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#تعریف_کرو نکالو_2								      \
  کرو {									      \
    انتخاب (ڈھیر[sp].op)						      \
      {									      \
      حالت TRUTH_ANDIF_اظہاریہ:						      \
	c_inhibit_evaluation_warnings -= (ڈھیر[sp - 1].اظہاریہ.قدر	      \
					  == truthvalue_false_گرہ);	      \
	توڑو;								      \
      حالت TRUTH_ORIF_اظہاریہ:						      \
	c_inhibit_evaluation_warnings -= (ڈھیر[sp - 1].اظہاریہ.قدر	      \
					  == truthvalue_true_گرہ);	      \
	توڑو;								      \
      حالت TRUNC_DIV_اظہاریہ:						      \
	اگر ((ڈھیر[sp - 1].اظہاریہ.original_رمز == SIZEOF_اظہاریہ		      \
	     || ڈھیر[sp - 1].اظہاریہ.original_رمز == PAREN_SIZEOF_اظہاریہ)	      \
	    && (ڈھیر[sp].اظہاریہ.original_رمز == SIZEOF_اظہاریہ		      \
		|| ڈھیر[sp].اظہاریہ.original_رمز == PAREN_SIZEOF_اظہاریہ))	      \
	  {								      \
	    درخت type0 = ڈھیر[sp - 1].sizeof_arg;			      \
	    درخت type1 = ڈھیر[sp].sizeof_arg;				      \
	    درخت پہلا_arg = type0;					      \
	    اگر (!TYPE_P (type0))					      \
	      type0 = درخت_TYPE (type0);				      \
	    اگر (!TYPE_P (type1))					      \
	      type1 = درخت_TYPE (type1);				      \
	    اگر (اشارہ_گر_TYPE_P (type0)					      \
		&& comptypes (درخت_TYPE (type0), type1)			      \
		&& !(درخت_رمز (پہلا_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (پہلا_arg)			      \
		     && warn_sizeof_array_دلیل))			      \
	      {								      \
		auto_diagnostic_گروہ d;				      \
		اگر (warning_at (ڈھیر[sp].loc, OPT_Wsizeof_اشارہ_گر_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  اگر (DECL_P (پہلا_arg))				      \
		    inform (DECL_ماخذ_LOCATION (پہلا_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    ورنہ اگر (درخت_رمز (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (درخت_TYPE (type0)))  \
		     && ڈھیر[sp].اظہاریہ.original_رمز != PAREN_SIZEOF_اظہاریہ)    \
	      maybe_warn_sizeof_array_div (ڈھیر[sp].loc, پہلا_arg, type0,   \
					   ڈھیر[sp].sizeof_arg, type1);      \
	  }								      \
	توڑو;								      \
      طےشدہ:								      \
	توڑو;								      \
      }									      \
    ڈھیر[sp - 1].اظہاریہ							      \
      = convert_lvalue_مقصد_rvalue (ڈھیر[sp - 1].loc,			      \
				  ڈھیر[sp - 1].اظہاریہ, سچ, سچ);	      \
    ڈھیر[sp].اظہاریہ							      \
      = convert_lvalue_مقصد_rvalue (ڈھیر[sp].loc,			      \
				  ڈھیر[sp].اظہاریہ, سچ, سچ);		      \
    اگر (UNLIKELY (omp_atomic_lhs != NULL_درخت) && sp == 1		      \
	&& ((c_parser_اگلا_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << ڈھیر[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_سرکاؤ)		      \
		     | (1 << PREC_جوڑو) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_اگلا_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_گرہ			      \
		     && c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (ڈھیر[sp].prec == PREC_REL || ڈھیر[sp].prec == PREC_EQ)))\
	&& ڈھیر[sp].op != TRUNC_MOD_اظہاریہ				      \
	&& ڈھیر[sp].op != GE_اظہاریہ					      \
	&& ڈھیر[sp].op != LE_اظہاریہ					      \
	&& ڈھیر[sp].op != NE_اظہاریہ					      \
	&& ڈھیر[0].اظہاریہ.قدر != error_mark_گرہ			      \
	&& ڈھیر[1].اظہاریہ.قدر != error_mark_گرہ			      \
	&& (omp_atomic_lhs == void_list_گرہ				      \
	    || c_درخت_equal (ڈھیر[0].اظہاریہ.قدر, omp_atomic_lhs)	      \
	    || c_درخت_equal (ڈھیر[1].اظہاریہ.قدر, omp_atomic_lhs)	      \
	    || (ڈھیر[sp].op == EQ_اظہاریہ					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	درخت t = make_گرہ (ڈھیر[1].op);				      \
	درخت_TYPE (t) = درخت_TYPE (ڈھیر[0].اظہاریہ.قدر);		      \
	درخت_عملیہ (t, 0) = ڈھیر[0].اظہاریہ.قدر;			      \
	درخت_عملیہ (t, 1) = ڈھیر[1].اظہاریہ.قدر;			      \
	ڈھیر[0].اظہاریہ.قدر = t;					      \
	ڈھیر[0].اظہاریہ.m_decimal = 0;					      \
      }									      \
    ورنہ								      \
      ڈھیر[sp - 1].اظہاریہ = parser_build_ثنائی_op (ڈھیر[sp].loc,	      \
						   ڈھیر[sp].op,	      \
						   ڈھیر[sp - 1].اظہاریہ,	      \
						   ڈھیر[sp].اظہاریہ,	      \
						   ڈھیر[sp - 1].orig_اظہاریہ);  \
    ڈھیر[sp - 1].orig_اظہاریہ = NULL_درخت;				      \
    sp--;								      \
  } جب (0)
  gcc_assert (!after || c_dialect_objc ());
  ڈھیر[0].loc = c_parser_peek_token (parser)->location;
  ڈھیر[0].اظہاریہ = c_parser_cast_عبارت (parser, after);
  ڈھیر[0].prec = PREC_NONE;
  ڈھیر[0].sizeof_arg = c_آخری_sizeof_arg;
  ڈھیر[0].orig_اظہاریہ = NULL_درخت;
  sp = 0;
  جب (سچ)
    {
      شمار c_parser_prec oprec;
      شمار درخت_رمز_2 ocode;
      ماخذ_range src_range;
      اگر (parser->error)
	جاؤ برآمد;
      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_اظہاریہ;
	  توڑو;
	حالت CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_اظہاریہ;
	  توڑو;
	حالت CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_اظہاریہ;
	  توڑو;
	حالت CPP_PLUS:
	  oprec = PREC_جوڑو;
	  ocode = PLUS_اظہاریہ;
	  توڑو;
	حالت CPP_MINUS:
	  oprec = PREC_جوڑو;
	  ocode = MINUS_اظہاریہ;
	  توڑو;
	حالت CPP_LSHIFT:
	  oprec = PREC_سرکاؤ;
	  ocode = LSHIFT_اظہاریہ;
	  توڑو;
	حالت CPP_RSHIFT:
	  oprec = PREC_سرکاؤ;
	  ocode = RSHIFT_اظہاریہ;
	  توڑو;
	حالت CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_اظہاریہ;
	  توڑو;
	حالت CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_اظہاریہ;
	  توڑو;
	حالت CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_اظہاریہ;
	  توڑو;
	حالت CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_اظہاریہ;
	  توڑو;
	حالت CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_اظہاریہ;
	  توڑو;
	حالت CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_اظہاریہ;
	  توڑو;
	حالت CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = ثنائی_ہندسہ_AND_اظہاریہ;
	  توڑو;
	حالت CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = ثنائی_ہندسہ_XOR_اظہاریہ;
	  توڑو;
	حالت CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = ثنائی_ہندسہ_IOR_اظہاریہ;
	  توڑو;
	حالت CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_اظہاریہ;
	  توڑو;
	حالت CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_اظہاریہ;
	  توڑو;
	طےشدہ:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  جاؤ برآمد;
	}
      ثنائی_loc = c_parser_peek_token (parser)->location;
      جب (oprec <= ڈھیر[sp].prec)
	نکالو_2;
      c_parser_consume_token (parser);
      انتخاب (ocode)
	{
	حالت TRUTH_ANDIF_اظہاریہ:
	  src_range = ڈھیر[sp].اظہاریہ.src_range;
	  ڈھیر[sp].اظہاریہ
	    = convert_lvalue_مقصد_rvalue (ڈھیر[sp].loc,
					ڈھیر[sp].اظہاریہ, سچ, سچ);
	  ڈھیر[sp].orig_اظہاریہ = ڈھیر[sp].اظہاریہ.قدر;
	  ڈھیر[sp].اظہاریہ.قدر = c_objc_common_truthvalue_conversion
	    (ڈھیر[sp].loc, default_conversion (ڈھیر[sp].اظہاریہ.قدر));
	  c_inhibit_evaluation_warnings += (ڈھیر[sp].اظہاریہ.قدر
					    == truthvalue_false_گرہ);
	  سیٹ_c_اظہاریہ_ماخذ_range (&ڈھیر[sp].اظہاریہ, src_range);
	  توڑو;
	حالت TRUTH_ORIF_اظہاریہ:
	  src_range = ڈھیر[sp].اظہاریہ.src_range;
	  ڈھیر[sp].اظہاریہ
	    = convert_lvalue_مقصد_rvalue (ڈھیر[sp].loc,
					ڈھیر[sp].اظہاریہ, سچ, سچ);
	  ڈھیر[sp].orig_اظہاریہ = ڈھیر[sp].اظہاریہ.قدر;
	  ڈھیر[sp].اظہاریہ.قدر = c_objc_common_truthvalue_conversion
	    (ڈھیر[sp].loc, default_conversion (ڈھیر[sp].اظہاریہ.قدر));
	  c_inhibit_evaluation_warnings += (ڈھیر[sp].اظہاریہ.قدر
					    == truthvalue_true_گرہ);
	  سیٹ_c_اظہاریہ_ماخذ_range (&ڈھیر[sp].اظہاریہ, src_range);
	  توڑو;
	طےشدہ:
	  توڑو;
	}
      sp++;
      ڈھیر[sp].loc = ثنائی_loc;
      ڈھیر[sp].اظہاریہ = c_parser_cast_عبارت (parser, تہی);
      ڈھیر[sp].prec = oprec;
      ڈھیر[sp].op = ocode;
      ڈھیر[sp].sizeof_arg = c_آخری_sizeof_arg;
      ڈھیر[sp].orig_اظہاریہ = NULL_درخت;
    }
 برآمد:
  جب (sp > 0)
    نکالو_2;
  واپس ڈھیر[0].اظہاریہ;
#تعریف_منسوخ نکالو_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

ساکن ساخت c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  منطقی نظر_آیا_scspec = جھوٹ;
  ساخت c_declspecs *specs = build_null_declspecs ();
  جب (c_parser_اگلا_token_is (parser, CPP_KEYWORD))
    {
      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_CONSTEXPR:
	حالت RID_رجسٹر:
	حالت RID_STATIC:
	حالت RID_THREAD:
	  نظر_آیا_scspec = سچ;
	  declspecs_جوڑو_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->قدر);
	  c_parser_consume_token (parser);
	  توڑو;
	طےشدہ:
	  جاؤ برآمد;
	}
    }
 برآمد:
  واپس نظر_آیا_scspec ? specs : تہی;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

ساکن ساخت c_اظہاریہ
c_parser_cast_عبارت (c_parser *parser, ساخت c_اظہاریہ *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  اگر (after)
    واپس c_parser_postfix_عبارت_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      ساخت c_declspecs *scspecs;
      ساخت c_type_name *type_name;
      ساخت c_اظہاریہ ret;
      ساخت c_اظہاریہ اظہاریہ;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, سچ);
      parens.skip_until_ملا_close (parser);
      اگر (type_name == تہی)
	{
	  ret.سیٹ_error ();
	  ret.original_رمز = ERROR_MARK;
	  ret.original_type = تہی;
	  واپس ret;
	}

      /* Save casted types in the function's used types hash table.  */
      مستعمل_types_داخل_کرو (type_name->specs->type);

      اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
	واپس c_parser_postfix_عبارت_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      اگر (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      اگر (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
	اظہاریہ = c_parser_cast_عبارت (parser, تہی);
	اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, سچ, سچ);
      }
      ret.قدر = c_cast_اظہاریہ (cast_loc, type_name, اظہاریہ.قدر);
      اگر (ret.قدر && اظہاریہ.قدر)
	سیٹ_c_اظہاریہ_ماخذ_range (&ret, cast_loc, اظہاریہ.get_اختتام ());
      ret.original_رمز = ERROR_MARK;
      ret.original_type = تہی;
      ret.m_decimal = 0;
      واپس ret;
    }
  ورنہ
    واپس c_parser_unary_عبارت (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

ساکن خالی
mark_exp_read_cond (درخت قوت_نما)
{
  اگر ((VAR_P (قوت_نما) || درخت_رمز (قوت_نما) == PARM_DECL)
      && (VAR_P (قوت_نما) ? warn_غیر_مستعمل_but_سیٹ_variable
		      : warn_غیر_مستعمل_but_سیٹ_parameter) > 1)
    واپس;

  mark_exp_read (قوت_نما);
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

ساکن ساخت c_اظہاریہ
c_parser_unary_عبارت (c_parser *parser)
{
  صحیح ext;
  ساخت c_اظہاریہ ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t exp_loc;
  location_t اختتام;
  ret.original_رمز = ERROR_MARK;
  ret.original_type = تہی;
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_عبارت (parser, تہی);
      mark_exp_read_cond (op.قدر);
      op = default_function_array_conversion (exp_loc, op);
      واپس parser_build_unary_op (op_loc, PREINCREMENT_اظہاریہ, op);
    حالت CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_عبارت (parser, تہی);
      mark_exp_read_cond (op.قدر);
      op = default_function_array_conversion (exp_loc, op);
      واپس parser_build_unary_op (op_loc, PREDECREMENT_اظہاریہ, op);
    حالت CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_عبارت (parser, تہی);
      mark_exp_read (op.قدر);
      واپس parser_build_unary_op (op_loc, ADDR_اظہاریہ, op);
    حالت CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_عبارت (parser, تہی);
	اختتام = op.get_اختتام ();
	op = convert_lvalue_مقصد_rvalue (exp_loc, op, سچ, سچ);
	location_t combined_loc = make_location (op_loc, op_loc, اختتام);
	ret.قدر = build_بالواسطہ_ref (combined_loc, op.قدر, RO_UNARY_ستارہ);
	ret.src_range.m_آغاز = op_loc;
	ret.src_range.m_اختتام = اختتام;
	ret.m_decimal = 0;
	واپس ret;
      }
    حالت CPP_PLUS:
      اگر (!c_dialect_objc () && !اندر_system_سرخی_at (داخلہ_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_عبارت (parser, تہی);
      op = convert_lvalue_مقصد_rvalue (exp_loc, op, سچ, سچ);
      واپس parser_build_unary_op (op_loc, CONVERT_اظہاریہ, op);
    حالت CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_عبارت (parser, تہی);
      op = convert_lvalue_مقصد_rvalue (exp_loc, op, سچ, سچ);
      واپس parser_build_unary_op (op_loc, NEGATE_اظہاریہ, op);
    حالت CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_عبارت (parser, تہی);
      op = convert_lvalue_مقصد_rvalue (exp_loc, op, سچ, سچ);
      واپس parser_build_unary_op (op_loc, ثنائی_ہندسہ_NOT_اظہاریہ, op);
    حالت CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_عبارت (parser, تہی);
      op = convert_lvalue_مقصد_rvalue (exp_loc, op, سچ, سچ);
      واپس parser_build_unary_op (op_loc, TRUTH_NOT_اظہاریہ, op);
    حالت CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	{
	  ret.قدر = اختتام_label_پتہ_اظہاریہ
	    (c_parser_peek_token (parser)->قدر, op_loc);
	  سیٹ_c_اظہاریہ_ماخذ_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_اختتام ());
	  c_parser_consume_token (parser);
	}
      ورنہ
	{
	  c_parser_error (parser, "expected identifier");
	  ret.سیٹ_error ();
	}
      واپس ret;
    حالت CPP_KEYWORD:
      {
	شمار rid rid = c_parser_peek_token (parser)->keyword;
	انتخاب (rid)
	  {
	  حالت RID_COUNTOF:
	  حالت RID_SIZEOF:
	    واپس c_parser_sizeof_or_countof_عبارت (parser, rid);
	  حالت RID_ALIGNOF:
	    واپس c_parser_alignof_عبارت (parser);
	  حالت RID_MAXOF:
	  حالت RID_MINOF:
	    واپس c_parser_maxof_or_minof_عبارت (parser, rid);
	  حالت RID_BUILTIN_HAS_ATTRIBUTE:
	    واپس c_parser_has_attribute_عبارت (parser);
	  حالت RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_عبارت (parser, تہی);
	    restore_extension_diagnostics (ext);
	    واپس ret;
	  حالت RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_عبارت (parser, تہی);
	    op = default_function_array_conversion (exp_loc, op);
	    واپس parser_build_unary_op (op_loc, REALPART_اظہاریہ, op);
	  حالت RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_عبارت (parser, تہی);
	    op = default_function_array_conversion (exp_loc, op);
	    واپس parser_build_unary_op (op_loc, IMAGPART_اظہاریہ, op);
	  حالت RID_TRANSACTION_ATOMIC:
	  حالت RID_TRANSACTION_RELAXED:
	    واپس c_parser_transaction_عبارت (parser, rid);
	  حالت RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.قدر = void_گرہ;
	    سیٹ_c_اظہاریہ_ماخذ_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    واپس ret;
	  طےشدہ:
	    واپس c_parser_postfix_عبارت (parser);
	  }
      }
    طےشدہ:
      واپس c_parser_postfix_عبارت (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

ساکن ساخت c_اظہاریہ
c_parser_sizeof_or_countof_عبارت (c_parser *parser, شمار rid rid)
{
  ثابت حرف *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  ساخت c_اظہاریہ اظہاریہ;
  ساخت c_اظہاریہ نتیجہ;
  location_t اظہاریہ_loc;
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, rid));

  location_t آغاز;
  location_t اختتام = UNKNOWN_LOCATION;

  آغاز = c_parser_peek_token (parser)->location;

  اگر (rid == RID_COUNTOF)
    pedwarn_c23 (آغاز, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  اگر (rid == RID_COUNTOF)
    اندر_countof++;
  ورنہ
    اندر_sizeof++;
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      ساخت c_declspecs *scspecs;
      ساخت c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      اظہاریہ_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, سچ);
      parens.skip_until_ملا_close (parser);
      اختتام = parser->علامات_buf[0].location;
      اگر (type_name == تہی)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  اظہاریہ.سیٹ_error ();
	  جاؤ Xof_اظہاریہ;
	}
      اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
	{
	  اظہاریہ = c_parser_postfix_عبارت_after_paren_type (parser, scspecs,
							       type_name,
							       اظہاریہ_loc);
	  اختتام = اظہاریہ.get_اختتام ();
	  جاؤ Xof_اظہاریہ;
	}
      /* sizeof ( type-name ).  */
      اگر (scspecs)
	error_at (اظہاریہ_loc, "storage class specifier in %qs", op_name);
      اگر (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      اگر (rid == RID_COUNTOF)
	{
	  اندر_countof--;
	  نتیجہ = c_اظہاریہ_countof_type (اظہاریہ_loc, type_name);
	}
      ورنہ
	{
	  اندر_sizeof--;
	  نتیجہ = c_اظہاریہ_sizeof_type (اظہاریہ_loc, type_name);
	}
    }
  ورنہ
    {
      اظہاریہ_loc = c_parser_peek_token (parser)->location;
      اظہاریہ = c_parser_unary_عبارت (parser);
      اختتام = اظہاریہ.get_اختتام ();
    Xof_اظہاریہ:
      c_inhibit_evaluation_warnings--;
      اگر (rid == RID_COUNTOF)
	اندر_countof--;
      ورنہ
	اندر_sizeof--;
      mark_exp_read (اظہاریہ.قدر);
      اگر (درخت_رمز (اظہاریہ.قدر) == COMPONENT_REF
	  && DECL_C_ثنائی_ہندسہ_میدان (درخت_عملیہ (اظہاریہ.قدر, 1)))
	error_at (اظہاریہ_loc, "%qs applied to a bit-field", op_name);
      اگر (rid == RID_COUNTOF)
	نتیجہ = c_اظہاریہ_countof_اظہاریہ (اظہاریہ_loc, اظہاریہ);
      ورنہ
	نتیجہ = c_اظہاریہ_sizeof_اظہاریہ (اظہاریہ_loc, اظہاریہ);
    }
  اگر (اختتام == UNKNOWN_LOCATION)
    اختتام = آغاز;
  سیٹ_c_اظہاریہ_ماخذ_range (&نتیجہ, آغاز, اختتام);
  واپس نتیجہ;
}

/* Parse an alignof expression.  */

ساکن ساخت c_اظہاریہ
c_parser_alignof_عبارت (c_parser *parser)
{
  ساخت c_اظہاریہ اظہاریہ;
  location_t آغاز_loc = c_parser_peek_token (parser)->location;
  location_t انتہا_loc;
  درخت alignof_spelling = c_parser_peek_token (parser)->قدر;
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_ALIGNOF));
  منطقی is_c11_alignof = (strcmp (IDENTIFIER_اشارہ_گر (alignof_spelling),
				"_Alignof") == 0
			 || strcmp (IDENTIFIER_اشارہ_گر (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  اگر (is_c11_alignof)
    {
      اگر (flag_isoc99)
	pedwarn_c99 (آغاز_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      ورنہ
	pedwarn_c99 (آغاز_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  اندر_alignof++;
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      ساخت c_declspecs *scspecs;
      ساخت c_type_name *type_name;
      ساخت c_اظہاریہ ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, سچ);
      انتہا_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_ملا_close (parser);
      اگر (type_name == تہی)
	{
	  ساخت c_اظہاریہ ret;
	  c_inhibit_evaluation_warnings--;
	  اندر_alignof--;
	  ret.سیٹ_error ();
	  ret.original_رمز = ERROR_MARK;
	  ret.original_type = تہی;
	  واپس ret;
	}
      اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
	{
	  اظہاریہ = c_parser_postfix_عبارت_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  جاؤ alignof_اظہاریہ;
	}
      /* alignof ( type-name ).  */
      اگر (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      اگر (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      اندر_alignof--;
      ret.قدر = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       تہی, تہی),
					    جھوٹ, is_c11_alignof, 1);
      ret.original_رمز = ERROR_MARK;
      ret.original_type = تہی;
      سیٹ_c_اظہاریہ_ماخذ_range (&ret, آغاز_loc, انتہا_loc);
      ret.m_decimal = 0;
      واپس ret;
    }
  ورنہ
    {
      ساخت c_اظہاریہ ret;
      اظہاریہ = c_parser_unary_عبارت (parser);
      انتہا_loc = اظہاریہ.src_range.m_اختتام;
    alignof_اظہاریہ:
      mark_exp_read (اظہاریہ.قدر);
      c_inhibit_evaluation_warnings--;
      اندر_alignof--;
      اگر (is_c11_alignof)
	pedwarn (آغاز_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.قدر = c_alignof_اظہاریہ (آغاز_loc, اظہاریہ.قدر);
      ret.original_رمز = ERROR_MARK;
      ret.original_type = تہی;
      سیٹ_c_اظہاریہ_ماخذ_range (&ret, آغاز_loc, انتہا_loc);
      ret.m_decimal = 0;
      واپس ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

ساکن ساخت c_اظہاریہ
c_parser_maxof_or_minof_عبارت (c_parser *parser, شمار rid rid)
{
  ثابت حرف *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  ساخت c_اظہاریہ نتیجہ;
  location_t اظہاریہ_loc;
  ساخت c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, rid));

  location_t آغاز;
  location_t اختتام = UNKNOWN_LOCATION;

  آغاز = c_parser_peek_token (parser)->location;

  pedwarn (آغاز, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  اگر (!c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      جاؤ fail;
    }
  parens.consume_open (parser);
  اظہاریہ_loc = c_parser_peek_token (parser)->location;
  اگر (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (اظہاریہ_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_ملا_close (parser);
      جاؤ fail;
    }
  type_name = c_parser_type_name (parser, سچ);
  اگر (type_name == تہی)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_ملا_close (parser);
      جاؤ fail;
    }
  parens.skip_until_ملا_close (parser);
  اختتام = parser->علامات_buf[0].location;
  اگر (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  اگر (rid == RID_MAXOF)
    نتیجہ = c_اظہاریہ_maxof_type (اظہاریہ_loc, type_name);
  ورنہ
    نتیجہ = c_اظہاریہ_minof_type (اظہاریہ_loc, type_name);
  سیٹ_c_اظہاریہ_ماخذ_range (&نتیجہ, آغاز, اختتام);
  واپس نتیجہ;
fail:
  c_inhibit_evaluation_warnings--;
  نتیجہ.سیٹ_error ();
  نتیجہ.original_رمز = ERROR_MARK;
  نتیجہ.original_type = تہی;
  واپس نتیجہ;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

ساکن ساخت c_اظہاریہ
c_parser_has_attribute_عبارت (c_parser *parser)
{
  gcc_assert (c_parser_اگلا_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t آغاز = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      اندر_typeof--;

      ساخت c_اظہاریہ نتیجہ;
      نتیجہ.سیٹ_error ();
      نتیجہ.original_رمز = ERROR_MARK;
      نتیجہ.original_type = تہی;
      واپس نتیجہ;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  اندر_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  درخت oper = NULL_درخت;
  اگر (c_parser_اگلا_علامات_آغاز_typename (parser, cla_prefer_id))
    {
      ساخت c_type_name *tname = c_parser_type_name (parser);
      اندر_typeof--;
      اگر (tname)
	{
	  oper = groktypename (tname, تہی, تہی);
	  نکالو_maybe_مستعمل (c_type_variably_modified_p (oper));
	}
    }
  ورنہ
    {
      ساخت c_اظہاریہ cexpr = c_parser_اظہاریہ_no_commas (parser, تہی);
      c_inhibit_evaluation_warnings--;
      اندر_typeof--;
      اگر (cexpr.قدر != error_mark_گرہ)
	{
	  mark_exp_read (cexpr.قدر);
	  oper = cexpr.قدر;
	  درخت etype = درخت_TYPE (oper);
	  منطقی was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  اگر (was_vm)
	    oper = c_fully_fold (oper, جھوٹ, تہی);
	  نکالو_maybe_مستعمل (was_vm);
	}
    }

  ساخت c_اظہاریہ نتیجہ;
  نتیجہ.original_رمز = ERROR_MARK;
  نتیجہ.original_type = تہی;

  اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      نتیجہ.سیٹ_error ();
      واپس نتیجہ;
    }

  منطقی save_translate_لڑیاں_p = parser->translate_لڑیاں_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  درخت attr = c_parser_gnu_attribute (parser, NULL_درخت, جھوٹ, جھوٹ);

  parser->translate_لڑیاں_p = save_translate_لڑیاں_p;

  location_t اختتام = c_parser_peek_token (parser)->location;
  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  ورنہ
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);

      نتیجہ.سیٹ_error ();
      واپس نتیجہ;
    }

  اگر (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      نتیجہ.سیٹ_error ();
      واپس نتیجہ;
    }

  نتیجہ.original_رمز = INTEGER_CST;
  نتیجہ.original_type = boolean_type_گرہ;

  اگر (has_attribute (atloc, oper, attr, default_conversion))
    نتیجہ.قدر = boolean_true_گرہ;
  ورنہ
    نتیجہ.قدر =  boolean_false_گرہ;

  سیٹ_c_اظہاریہ_ماخذ_range (&نتیجہ, آغاز, اختتام);
  نتیجہ.m_decimal = 0;
  واپس نتیجہ;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
ساکن منطقی
c_parser_get_builtin_دلائل (c_parser *parser, ثابت حرف *bname,
			   vec<c_اظہاریہ_t, va_gc> **ret_cexpr_list,
			   منطقی انتخاب_اظہاریہ_p,
			   location_t *برآمد_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_اظہاریہ_t, va_gc> *cexpr_list;
  c_اظہاریہ_t اظہاریہ;
  منطقی saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = تہی;
  اگر (c_parser_اگلا_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      واپس جھوٹ;
    }

  c_parser_consume_token (parser);

  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
    {
      *برآمد_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      واپس سچ;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= انتخاب_اظہاریہ_p;
  اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_محفوظ_ڈالو (cexpr_list, اظہاریہ);
  جب (c_parser_اگلا_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      اگر (c_parser_اگلا_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  درخت قدر = embed->قدر;
	  اظہاریہ.original_رمز = INTEGER_CST;
	  اظہاریہ.original_type = integer_type_گرہ;
	  اظہاریہ.قدر = NULL_درخت;
	  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, embed->get_range ());
	  اظہاریہ.m_decimal = 0;
	  برائے (غیرعلامتی صحیح i = 0; i < (غیرعلامتی) RAW_ڈیٹا_لمبائی (قدر); i++)
	    {
	      اظہاریہ.قدر = build_int_cst (integer_type_گرہ,
					  RAW_ڈیٹا_UCHAR_ELT (قدر, i));
	      vec_محفوظ_ڈالو (cexpr_list, اظہاریہ);
	    }
	  c_parser_consume_token (parser);
	  جاری;
	}
      اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      vec_محفوظ_ڈالو (cexpr_list, اظہاریہ);
    }

  *برآمد_close_paren_loc = c_parser_peek_token (parser)->location;
  اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    واپس جھوٹ;

  *ret_cexpr_list = cexpr_list;
  واپس سچ;
}

/* This represents a single generic-association.  */

ساخت c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  درخت type;
  /* The association's expression.  */
  ساخت c_اظہاریہ عبارت;
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

ساکن ساخت c_اظہاریہ
c_parser_generic_selection (c_parser *parser)
{
  ساخت c_اظہاریہ selector, error_اظہاریہ;
  درخت selector_type;
  ساخت c_generic_association matched_assoc;
  صحیح مطابقت_ملا = -1;
  location_t generic_loc, selector_loc;

  error_اظہاریہ.original_رمز = ERROR_MARK;
  error_اظہاریہ.original_type = تہی;
  error_اظہاریہ.سیٹ_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_درخت;
  matched_assoc.عبارت = error_اظہاریہ;

  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_GENERIC));
  generic_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  اگر (flag_isoc99)
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C99 does not support %<_Generic%>");
  ورنہ
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C90 does not support %<_Generic%>");

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس error_اظہاریہ;

  selector_loc = c_parser_peek_token (parser)->location;
  اگر (c_parser_اگلا_علامات_آغاز_typename (parser, cla_prefer_id))
    {
      c_inhibit_evaluation_warnings++;
      pedwarn_c23 (selector_loc, OPT_Wpedantic,
		   "ISO C does not support use of type name as %<_Generic%> "
		   "controlling operand before C2Y");
      ساخت c_type_name *type = c_parser_type_name (parser);
      اگر (type)
	selector_type = groktypename (type, تہی, تہی);
      c_inhibit_evaluation_warnings--;
      اگر (!type)
	{
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
	  واپس error_اظہاریہ;
	}
    }
  ورنہ
    {
      c_inhibit_evaluation_warnings++;
      اندر_generic++;
      selector = c_parser_اظہاریہ_no_commas (parser, تہی);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      اندر_generic--;
      نکالو_maybe_مستعمل (!flag_isoc23);

      اگر (selector.قدر == error_mark_گرہ)
	{
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
	  واپس selector;
	}
      mark_exp_read (selector.قدر);
      selector_type = درخت_TYPE (selector.قدر);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      اگر (درخت_رمز (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      اگر (FUNCTION_اشارہ_گر_TYPE_P (selector_type)
	  && TYPE_QUALS (درخت_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_اشارہ_گر_type (TYPE_MAIN_VARIANT (درخت_TYPE (selector_type)));
    }

  اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
      واپس error_اظہاریہ;
    }

  auto_vec<c_generic_association> associations;
  ساخت maybe_مستعمل_decl *maybe_مستعمل_default = تہی;
  جب (1)
    {
      ساخت c_generic_association assoc, *iter;
      غیرعلامتی صحیح ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      اگر (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_درخت;
	}
      ورنہ
	{
	  ساخت c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  اگر (type_name == تہی)
	    {
	      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
	      واپس error_اظہاریہ;
	    }
	  assoc.type = grokgenassoc (type_name);
	  اگر (assoc.type == error_mark_گرہ)
	    {
	      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
	      واپس error_اظہاریہ;
	    }

	  اگر (درخت_رمز (assoc.type) == FUNCTION_TYPE)
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "function type before C2Y");
	  ورنہ اگر (!COMPLETE_TYPE_P (assoc.type))
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
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
	  واپس error_اظہاریہ;
	}

      منطقی مطابقت = assoc.type == NULL_درخت
		   || comptypes (assoc.type, selector_type);

      اگر (!مطابقت || matched_assoc.type != NULL_درخت)
	c_inhibit_evaluation_warnings++;
      اندر_generic++;

      assoc.عبارت = c_parser_اظہاریہ_no_commas (parser, تہی);

      اگر (!مطابقت || matched_assoc.type != NULL_درخت)
	c_inhibit_evaluation_warnings--;
      اندر_generic--;
      اگر (!مطابقت)
	نکالو_maybe_مستعمل (!flag_isoc23);
      ورنہ اگر (assoc.type == NULL_درخت)
	maybe_مستعمل_default = save_maybe_مستعمل ();
      ورنہ
	نکالو_maybe_مستعمل (سچ);

      اگر (assoc.عبارت.قدر == error_mark_گرہ)
	{
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
	  واپس error_اظہاریہ;
	}

      برائے (ix = 0; associations.iterate (ix, &iter); ++ix)
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
	  ورنہ اگر (iter->type != NULL_درخت)
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
	  اگر (مطابقت_ملا < 0)
	    {
	      matched_assoc = assoc;
	      مطابقت_ملا = associations.لمبائی ();
	    }
	}
      ورنہ اگر (مطابقت)
	{
	  اگر (مطابقت_ملا < 0 || matched_assoc.type == NULL_درخت)
	    {
	      matched_assoc = assoc;
	      مطابقت_ملا = associations.لمبائی ();
	    }
	  ورنہ
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.محفوظ_ڈالو (assoc);

      اگر (c_parser_peek_token (parser)->type != CPP_COMMA)
	توڑو;
      c_parser_consume_token (parser);
    }

  اگر (مطابقت_ملا >= 0 && matched_assoc.type == NULL_درخت)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_مستعمل (maybe_مستعمل_default);
      نکالو_maybe_مستعمل (سچ);
    }
  ورنہ اگر (maybe_مستعمل_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_مستعمل (maybe_مستعمل_default);
      نکالو_maybe_مستعمل (!flag_isoc23);
    }

  غیرعلامتی صحیح ix;
  ساخت c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    اگر (ix != (غیرعلامتی) مطابقت_ملا)
      mark_exp_read (iter->عبارت.قدر);

  اگر (!parens.require_close (parser))
    {
      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
      واپس error_اظہاریہ;
    }

  اگر (مطابقت_ملا < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      واپس error_اظہاریہ;
    }

  واپس matched_assoc.عبارت;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

ساکن غیرعلامتی صحیح
check_tgmath_function (c_اظہاریہ *اظہاریہ, غیرعلامتی صحیح pos)
{
  درخت type = درخت_TYPE (اظہاریہ->قدر);
  اگر (!FUNCTION_اشارہ_گر_TYPE_P (type))
    {
      error_at (اظہاریہ->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      واپس 0;
    }
  type = درخت_TYPE (type);
  اگر (!prototype_p (type))
    {
      error_at (اظہاریہ->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      واپس 0;
    }
  اگر (stdarg_p (type))
    {
      error_at (اظہاریہ->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      واپس 0;
    }
  غیرعلامتی صحیح nargs = 0;
  function_دلائل_iterator iter;
  درخت t;
  FOREACH_FUNCTION_دلائل (type, t, iter)
    {
      اگر (t == void_type_گرہ)
	توڑو;
      nargs++;
    }
  اگر (nargs == 0)
    {
      error_at (اظہاریہ->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      واپس 0;
    }
  واپس nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
شمار tgmath_parm_قسم
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

ساکن ساخت c_اظہاریہ
c_parser_predefined_identifier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  انتخاب (c_parser_peek_token (parser)->keyword)
    {
    حالت RID_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__FUNCTION__");
      توڑو;
    حالت RID_PRETTY_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__PRETTY_FUNCTION__");
      توڑو;
    حالت RID_C99_FUNCTION_NAME:
      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support "
		   "%<__func__%> predefined identifier");
      توڑو;
    طےشدہ:
      gcc_unreachable ();
    }

  ساخت c_اظہاریہ اظہاریہ;
  اظہاریہ.original_رمز = ERROR_MARK;
  اظہاریہ.original_type = تہی;
  اظہاریہ.قدر = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->قدر);
  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, loc);
  اظہاریہ.m_decimal = 0;
  c_parser_consume_token (parser);
  واپس اظہاریہ;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

ساکن منطقی
has_counted_by_object (درخت ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  اگر ((درخت_رمز (ref) == بالواسطہ_REF
       && is_access_with_سائز_p (درخت_عملیہ (ref, 0)))
      || is_access_with_سائز_p (ref))
    واپس سچ;
  واپس جھوٹ;
}

/* Get the reference to the counted-by object associated with the REF.  */

ساکن درخت
get_counted_by_ref (درخت ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  اگر (درخت_رمز (ref) == بالواسطہ_REF
      && is_access_with_سائز_p (درخت_عملیہ (ref, 0)))
    واپس CALL_اظہاریہ_ARG (درخت_عملیہ (ref, 0), 1);
  ورنہ اگر (is_access_with_سائز_p (ref))
    واپس CALL_اظہاریہ_ARG (ref, 1);

  واپس NULL_درخت;
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

ساکن ساخت c_اظہاریہ
c_parser_postfix_عبارت (c_parser *parser)
{
  ساخت c_اظہاریہ اظہاریہ, e1;
  ساخت c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  ماخذ_range tok_range = c_parser_peek_token (parser)->get_range ();
  اظہاریہ.original_رمز = ERROR_MARK;
  اظہاریہ.original_type = تہی;
  اظہاریہ.m_decimal = 0;
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_نمبر:
      اظہاریہ.قدر = c_parser_peek_token (parser)->قدر;
      سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, tok_range);
      loc = c_parser_peek_token (parser)->location;
      اظہاریہ.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      اگر (درخت_رمز (اظہاریہ.قدر) == FIXED_CST
	  && !targetm.fixed_نقطہ_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  اظہاریہ.سیٹ_error ();
	}
      توڑو;
    حالت CPP_CHAR:
    حالت CPP_CHAR16:
    حالت CPP_CHAR32:
    حالت CPP_UTF8CHAR:
    حالت CPP_WCHAR:
      اظہاریہ.قدر = c_parser_peek_token (parser)->قدر;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      اظہاریہ.original_type = char_type_گرہ;
      سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, tok_range);
      c_parser_consume_token (parser);
      توڑو;
    حالت CPP_STRING:
    حالت CPP_STRING16:
    حالت CPP_STRING32:
    حالت CPP_WSTRING:
    حالت CPP_UTF8STRING:
      اظہاریہ = c_parser_string_literal (parser, parser->translate_لڑیاں_p,
				      سچ);
      توڑو;
    حالت CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      اظہاریہ.قدر
	= objc_build_string_object (c_parser_peek_token (parser)->قدر);
      سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, tok_range);
      c_parser_consume_token (parser);
      توڑو;
    حالت CPP_NAME:
      انتخاب (c_parser_peek_token (parser)->id_قسم)
	{
	حالت C_ID_ID:
	  {
	    درخت id = c_parser_peek_token (parser)->قدر;
	    c_parser_consume_token (parser);
	    اظہاریہ.قدر = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &اظہاریہ.original_type);
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, tok_range);
	    توڑو;
	  }
	حالت C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    درخت class_name = c_parser_peek_token (parser)->قدر;
	    درخت component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    اگر (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->قدر;
	    location_t انتہا_loc = component_tok->get_اختتام ();
	    c_parser_consume_token (parser);
	    اظہاریہ.قدر = objc_build_class_component_ref (class_name,
							 component);
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, انتہا_loc);
	    توڑو;
	  }
	طےشدہ:
	  c_parser_error (parser, "expected expression");
	  اظہاریہ.سیٹ_error ();
	  توڑو;
	}
      توڑو;
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
	      parser->error = سچ;
	      c_parser_skip_until_ملا (parser, CPP_CLOSE_BRACE, تہی);
	      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
	      اظہاریہ.سیٹ_error ();
	      توڑو;
	    }
	  c_omp_array_section_p = جھوٹ;
	  stmt = c_begin_stmt_اظہاریہ ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  اظہاریہ.قدر = c_اختتام_stmt_اظہاریہ (brace_loc, stmt);
	  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_loc);
	  mark_exp_read (اظہاریہ.قدر);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      ورنہ
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  اظہاریہ = c_parser_عبارت (parser);
	  اگر (درخت_رمز (اظہاریہ.قدر) == MODIFY_اظہاریہ)
	    suppress_warning (اظہاریہ.قدر, OPT_Wparentheses);
	  اگر (اظہاریہ.original_رمز != C_MAYBE_CONST_اظہاریہ
	      && اظہاریہ.original_رمز != SIZEOF_اظہاریہ)
	    اظہاریہ.original_رمز = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  اگر (اظہاریہ.original_رمز == SIZEOF_اظہاریہ)
	    اظہاریہ.original_رمز = PAREN_SIZEOF_اظہاریہ;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      توڑو;
    حالت CPP_KEYWORD:
      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_FUNCTION_NAME:
	حالت RID_PRETTY_FUNCTION_NAME:
	حالت RID_C99_FUNCTION_NAME:
	  اظہاریہ = c_parser_predefined_identifier (parser);
	  توڑو;
	حالت RID_VA_ARG:
	  {
	    location_t آغاز_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    e1 = c_parser_اظہاریہ_no_commas (parser, تہی);
	    mark_exp_read (e1.قدر);
	    e1.قدر = c_fully_fold (e1.قدر, جھوٹ, تہی);
	    اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t انتہا_loc = c_parser_peek_token (parser)->get_اختتام ();
	    c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    اگر (t1 == تہی)
	      {
		اظہاریہ.سیٹ_error ();
	      }
	    ورنہ
	      {
		درخت type_اظہاریہ = NULL_درخت;
		درخت type = groktypename (t1, &type_اظہاریہ, تہی);
		اظہاریہ.قدر = c_build_va_arg (آغاز_loc, e1.قدر, loc,
					     type, type_اظہاریہ);
		سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, آغاز_loc, انتہا_loc);
	      }
	  }
	  توڑو;
	حالت RID_C23_VA_آغاز:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    e1 = c_parser_اظہاریہ_no_commas (parser, تہی);
	    e1 = convert_lvalue_مقصد_rvalue (e1.get_location (), e1, سچ, سچ);
	    اگر (!c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
		    اظہاریہ.سیٹ_error ();
		    توڑو;
		  }
		اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_قسم == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    درخت name = c_parser_peek_token (parser)->قدر;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    درخت decl = lookup_name (name);
		    درخت آخری_parm
		      = درخت_آخری (DECL_ARGUMENTS (current_function_decl));
		    اگر (!آخری_parm || decl != آخری_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    ورنہ اگر (DECL_رجسٹر (decl))
		      warning_at (nloc, OPT_Wvarargs,
				  "undefined behavior when second parameter "
				  "of %<va_start%> is declared with "
				  "%<register%> storage");
		    c_parser_consume_token (parser);
		  }
		ورنہ
		  {
		    غیرعلامتی nesting_گہرائی = 0;
		    location_t sloc = c_parser_peek_token (parser)->location;
		    location_t eloc = sloc;

		    /* For va_start (ap,) the ) comes from stdarg.h.
		       Use location of , in that case, otherwise without
		       -Wsystem-headers nothing is reported.  After all,
		       the problematic token is the comma in that case.  */
		    اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    جب (سچ)
		      {
			c_token *token = c_parser_peek_token (parser);
			اگر (token->type == CPP_CLOSE_PAREN && !nesting_گہرائی)
			  توڑو;

			اگر (token->type == CPP_EOF)
			  توڑو;
			اگر (token->type == CPP_OPEN_PAREN)
			  ++nesting_گہرائی;
			ورنہ اگر (token->type == CPP_CLOSE_PAREN)
			  --nesting_گہرائی;
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
	    parens.skip_until_ملا_close (parser);
	    درخت fndecl = builtin_decl_explicit (BUILT_اندر_VA_آغاز);
	    vec<درخت, va_gc> *params;
	    vec_alloc (params, 2);
	    params->تیز_ڈالو (e1.قدر);
	    params->تیز_ڈالو (integer_zero_گرہ);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.تیز_ڈالو (e1.get_location ());
	    arg_loc.تیز_ڈالو (UNKNOWN_LOCATION);
	    اظہاریہ.قدر = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, تہی);
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc,
				     parser->علامات_buf[0].get_اختتام ());
	    اظہاریہ.m_decimal = 0;
	    اظہاریہ.original_رمز = ERROR_MARK;
	    اظہاریہ.original_type = تہی;
	    release_درخت_سمتیہ (params);
	    توڑو;
	  }
	حالت RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    t1 = c_parser_type_name (parser);
	    اگر (t1 == تہی)
	      parser->error = سچ;
	    اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    اگر (parser->error)
	      {
		c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    درخت type = groktypename (t1, تہی, تہی);
	    درخت offsetof_ref;
	    اگر (type == error_mark_گرہ)
	      offsetof_ref = error_mark_گرہ;
	    ورنہ
	      {
		offsetof_ref = build1 (بالواسطہ_REF, type, null_اشارہ_گر_گرہ);
		سیٹ_اظہاریہ_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->قدر,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		جب (c_parser_اگلا_token_is (parser, CPP_DOT)
		       || c_parser_اگلا_token_is (parser,
						  CPP_OPEN_مربع)
		       || c_parser_اگلا_token_is (parser,
						  CPP_DEREF))
		  {
		    اگر (c_parser_اگلا_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_گرہ);
			جاؤ do_dot;
		      }
		    ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			اگر (c_parser_اگلا_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    توڑو;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->قدر,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    ورنہ
		      {
			ساخت c_اظہاریہ ce;
			درخت idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_عبارت (parser);
			ce = convert_lvalue_مقصد_rvalue (loc, ce, جھوٹ, جھوٹ);
			idx = ce.قدر;
			idx = c_fully_fold (idx, جھوٹ, تہی);
			c_parser_skip_until_ملا (parser, CPP_CLOSE_مربع,
						   "expected %<]%>");
			offsetof_ref = build_array_ref (loc, offsetof_ref, idx);
		      }
		  }
	      }
	    ورنہ
	      c_parser_error (parser, "expected identifier");
	    location_t انتہا_loc = c_parser_peek_token (parser)->get_اختتام ();
	    c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    اظہاریہ.قدر = fold_offsetof (offsetof_ref);
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, انتہا_loc);
	  }
	  توڑو;
	حالت RID_انتخاب_اظہاریہ:
	  {
	    vec<c_اظہاریہ_t, va_gc> *cexpr_list;
	    c_اظہاریہ_t *e1_p, *e2_p, *e3_p;
	    درخت c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_دلائل (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, سچ,
					    &close_paren_loc))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    اگر (vec_محفوظ_لمبائی (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->قدر;
	    mark_exp_read (e2_p->قدر);
	    mark_exp_read (e3_p->قدر);
	    اگر (درخت_رمز (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (درخت_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_عبارت_warning (c);
	    اظہاریہ = integer_zerop (c) ? *e3_p : *e2_p;
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_paren_loc);
	    توڑو;
	  }
	حالت RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    t1 = c_parser_type_name (parser);
	    اگر (t1 == تہی)
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    t2 = c_parser_type_name (parser);
	    اگر (t2 == تہی)
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_ملا_close (parser);
	    درخت e1, e2;
	    e1 = groktypename (t1, تہی, تہی);
	    e2 = groktypename (t2, تہی, تہی);
	    اگر (e1 == error_mark_گرہ || e2 == error_mark_گرہ)
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    اظہاریہ.قدر
	      = comptypes (e1, e2) ? integer_one_گرہ : integer_zero_گرہ;
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_paren_loc);
	  }
	  توڑو;
	حالت RID_BUILTIN_TGMATH:
	  {
	    vec<c_اظہاریہ_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_دلائل (parser,
					    "__builtin_tgmath",
					    &cexpr_list, جھوٹ,
					    &close_paren_loc))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    اگر (vec_محفوظ_لمبائی (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    غیرعلامتی صحیح i;
	    c_اظہاریہ_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_مقصد_rvalue (loc, *p, سچ, سچ);
	    غیرعلامتی صحیح nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    اگر (nargs == 0)
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (vec_محفوظ_لمبائی (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    غیرعلامتی صحیح عدد_functions = vec_محفوظ_لمبائی (cexpr_list) - nargs;
	    اگر (عدد_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    برائے (غیرعلامتی صحیح j = 1; j < عدد_functions; j++)
	      {
		غیرعلامتی صحیح this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		اگر (this_nargs == 0)
		  {
		    اظہاریہ.سیٹ_error ();
		    جاؤ برآمد;
		  }
		اگر (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    اظہاریہ.سیٹ_error ();
		    جاؤ برآمد;
		  }
	      }

	    /* The functions all have the same number of arguments.
	       Determine whether arguments and return types vary in
	       ways permitted for <tgmath.h> functions.  */
	    /* The first entry in each of these vectors is for the
	       return type, subsequent entries for parameter
	       types.  */
	    auto_vec<شمار tgmath_parm_قسم> parm_قسم (nargs + 1);
	    auto_vec<درخت> parm_پہلا (nargs + 1);
	    auto_vec<منطقی> parm_complex (nargs + 1);
	    auto_vec<منطقی> parm_varies (nargs + 1);
	    درخت پہلا_type = درخت_TYPE (درخت_TYPE ((*cexpr_list)[0].قدر));
	    درخت پہلا_ret = TYPE_MAIN_VARIANT (درخت_TYPE (پہلا_type));
	    parm_پہلا.تیز_ڈالو (پہلا_ret);
	    parm_complex.تیز_ڈالو (درخت_رمز (پہلا_ret) == COMPLEX_TYPE);
	    parm_varies.تیز_ڈالو (جھوٹ);
	    function_دلائل_iterator iter;
	    درخت t;
	    غیرعلامتی صحیح argpos;
	    FOREACH_FUNCTION_دلائل (پہلا_type, t, iter)
	      {
		اگر (t == void_type_گرہ)
		  توڑو;
		parm_پہلا.تیز_ڈالو (TYPE_MAIN_VARIANT (t));
		parm_complex.تیز_ڈالو (درخت_رمز (t) == COMPLEX_TYPE);
		parm_varies.تیز_ڈالو (جھوٹ);
	      }
	    برائے (غیرعلامتی صحیح j = 1; j < عدد_functions; j++)
	      {
		درخت type = درخت_TYPE (درخت_TYPE ((*cexpr_list)[j].قدر));
		درخت ret = TYPE_MAIN_VARIANT (درخت_TYPE (type));
		اگر (ret != parm_پہلا[0])
		  {
		    parm_varies[0] = سچ;
		    اگر (!SCALAR_FLOAT_TYPE_P (parm_پہلا[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_پہلا[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			اظہاریہ.سیٹ_error ();
			جاؤ برآمد;
		      }
		    اگر (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			اظہاریہ.سیٹ_error ();
			جاؤ برآمد;
		      }
		  }
		اگر (درخت_رمز (ret) == COMPLEX_TYPE)
		  parm_complex[0] = سچ;
		argpos = 1;
		FOREACH_FUNCTION_دلائل (type, t, iter)
		  {
		    اگر (t == void_type_گرہ)
		      توڑو;
		    t = TYPE_MAIN_VARIANT (t);
		    اگر (t != parm_پہلا[argpos])
		      {
			parm_varies[argpos] = سچ;
			اگر (!SCALAR_FLOAT_TYPE_P (parm_پہلا[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_پہلا[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    اظہاریہ.سیٹ_error ();
			    جاؤ برآمد;
			  }
			اگر (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    اظہاریہ.سیٹ_error ();
			    جاؤ برآمد;
			  }
		      }
		    اگر (درخت_رمز (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = سچ;
		    argpos++;
		  }
	      }
	    شمار tgmath_parm_قسم max_variation = tgmath_fixed;
	    برائے (غیرعلامتی صحیح j = 0; j <= nargs; j++)
	      {
		شمار tgmath_parm_قسم this_قسم;
		اگر (parm_varies[j])
		  {
		    اگر (parm_complex[j])
		      max_variation = this_قسم = tgmath_complex;
		    ورنہ
		      {
			this_قسم = tgmath_real;
			اگر (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		ورنہ
		  this_قسم = tgmath_fixed;
		parm_قسم.تیز_ڈالو (this_قسم);
	      }
	    اگر (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    غیرعلامتی صحیح tgarg = 0;
	    برائے (غیرعلامتی صحیح j = 1; j <= nargs; j++)
	      اگر (parm_قسم[j] == max_variation)
		{
		  tgarg = j;
		  توڑو;
		}
	    اگر (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<درخت> tg_type (عدد_functions);
	    برائے (غیرعلامتی صحیح j = 0; j < عدد_functions; j++)
	      {
		درخت type = درخت_TYPE (درخت_TYPE ((*cexpr_list)[j].قدر));
		argpos = 1;
		FOREACH_FUNCTION_دلائل (type, t, iter)
		  {
		    اگر (argpos == tgarg)
		      {
			tg_type.تیز_ڈالو (TYPE_MAIN_VARIANT (t));
			توڑو;
		      }
		    argpos++;
		  }
	      }

	    /* Verify that the corresponding types are different for
	       all the listed functions.  Also determine whether all
	       the types are complex, whether all the types are
	       standard or binary, and whether all the types are
	       decimal.  */
	    منطقی all_complex = سچ;
	    منطقی all_ثنائی = سچ;
	    منطقی all_decimal = سچ;
	    hash_سیٹ<درخت> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		اگر (درخت_رمز (t) == COMPLEX_TYPE)
		  all_decimal = جھوٹ;
		ورنہ
		  {
		    all_complex = جھوٹ;
		    اگر (DECIMAL_FLOAT_TYPE_P (t))
		      all_ثنائی = جھوٹ;
		    ورنہ
		      all_decimal = جھوٹ;
		  }
		اگر (tg_types.جوڑو (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    اظہاریہ.سیٹ_error ();
		    جاؤ برآمد;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    برائے (غیرعلامتی صحیح j = 0; j < عدد_functions; j++)
	      {
		درخت exp_type = tg_type[j];
		درخت exp_real_type = exp_type;
		اگر (درخت_رمز (exp_type) == COMPLEX_TYPE)
		  exp_real_type = درخت_TYPE (exp_type);
		درخت type = درخت_TYPE (درخت_TYPE ((*cexpr_list)[j].قدر));
		درخت ret = TYPE_MAIN_VARIANT (درخت_TYPE (type));
		اگر ((parm_قسم[0] == tgmath_complex && ret != exp_type)
		    || (parm_قسم[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    اظہاریہ.سیٹ_error ();
		    جاؤ برآمد;
		  }
		argpos = 1;
		FOREACH_FUNCTION_دلائل (type, t, iter)
		  {
		    اگر (t == void_type_گرہ)
		      توڑو;
		    t = TYPE_MAIN_VARIANT (t);
		    اگر ((parm_قسم[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_قسم[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			اظہاریہ.سیٹ_error ();
			جاؤ برآمد;
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
	    منطقی arg_ثنائی = all_ثنائی;
	    منطقی arg_int_decimal = all_decimal;
	    منطقی arg_int_floatnx = جھوٹ;
	    منطقی arg_int_decimalx = جھوٹ;
	    برائے (غیرعلامتی صحیح j = 1; j <= nargs; j++)
	      {
		اگر (parm_قسم[j] == tgmath_fixed)
		  جاری;
		c_اظہاریہ_t *ce = &(*cexpr_list)[عدد_functions + j - 1];
		درخت type = درخت_TYPE (ce->قدر);
		اگر (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && درخت_رمز (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    اظہاریہ.سیٹ_error ();
		    جاؤ برآمد;
		  }
		اگر (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = سچ;
		    اگر (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			اظہاریہ.سیٹ_error ();
			جاؤ برآمد;
		      }
		    ورنہ اگر (all_ثنائی)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			اظہاریہ.سیٹ_error ();
			جاؤ برآمد;
		      }
		    ورنہ اگر (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			اظہاریہ.سیٹ_error ();
			جاؤ برآمد;
		      }
		    ورنہ اگر (arg_ثنائی)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			اظہاریہ.سیٹ_error ();
			جاؤ برآمد;
		      }
		  }
		ورنہ اگر (درخت_رمز (type) == COMPLEX_TYPE)
		  {
		    arg_complex = سچ;
		    اگر (COMPLEX_FLOAT_TYPE_P (type))
		      arg_ثنائی = سچ;
		    اگر (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			اظہاریہ.سیٹ_error ();
			جاؤ برآمد;
		      }
		    ورنہ اگر (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			اظہاریہ.سیٹ_error ();
			جاؤ برآمد;
		      }
		  }
		ورنہ اگر (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_ثنائی = سچ;
		    اگر (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			اظہاریہ.سیٹ_error ();
			جاؤ برآمد;
		      }
		    ورنہ اگر (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			اظہاریہ.سیٹ_error ();
			جاؤ برآمد;
		      }
		  }
		درخت rtype = TYPE_MAIN_VARIANT (type);
		اگر (درخت_رمز (rtype) == COMPLEX_TYPE)
		  rtype = درخت_TYPE (rtype);
		اگر (SCALAR_FLOAT_TYPE_P (rtype))
		  برائے (غیرعلامتی صحیح j = 0; j < عدد_FLOATNX_TYPES; j++)
		    اگر (rtype == FLOATNX_TYPE_گرہ (j))
		      {
			arg_int_floatnx = سچ;
			توڑو;
		      }
		اگر (rtype == dfloat64x_type_گرہ)
		  arg_int_decimalx = سچ;
	      }
	    درخت arg_real = NULL_درخت;
	    برائے (غیرعلامتی صحیح j = 1; j <= nargs; j++)
	      {
		اگر (parm_قسم[j] == tgmath_fixed)
		  جاری;
		c_اظہاریہ_t *ce = &(*cexpr_list)[عدد_functions + j - 1];
		درخت type = TYPE_MAIN_VARIANT (درخت_TYPE (ce->قدر));
		اگر (درخت_رمز (type) == COMPLEX_TYPE)
		  type = درخت_TYPE (type);
		اگر (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_گرہ
			  : arg_int_floatnx
			  ? float32x_type_گرہ
			  : arg_int_decimal
			  ? dfloat64_type_گرہ
			  : double_type_گرہ);
		اگر (arg_real == NULL_درخت)
		  arg_real = type;
		ورنہ
		  arg_real = common_type (arg_real, type);
		اگر (arg_real == error_mark_گرہ)
		  {
		    اظہاریہ.سیٹ_error ();
		    جاؤ برآمد;
		  }
	      }
	    درخت arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_اظہاریہ_t *fn = تہی;
	    برائے (غیرعلامتی صحیح j = 0; j < عدد_functions; j++)
	      {
		اگر (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    توڑو;
		  }
	      }
	    اگر (fn == تہی
		&& parm_قسم[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_پہلا[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		برائے (غیرعلامتی صحیح j = 0; j < عدد_functions; j++)
		  {
		    اگر (arg_complex
			!= (درخت_رمز (tg_type[j]) == COMPLEX_TYPE))
		      جاری;
		    درخت real_tg_type = (arg_complex
					 ? درخت_TYPE (tg_type[j])
					 : tg_type[j]);
		    اگر (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      جاری;
		    scalar_float_منوال arg_منوال
		      = SCALAR_FLOAT_TYPE_منوال (arg_real);
		    scalar_float_منوال tg_منوال
		      = SCALAR_FLOAT_TYPE_منوال (real_tg_type);
		    ثابت real_format *arg_fmt = REAL_منوال_FORMAT (arg_منوال);
		    ثابت real_format *tg_fmt = REAL_منوال_FORMAT (tg_منوال);
		    اگر (arg_fmt->b == tg_fmt->b
			&& arg_fmt->p <= tg_fmt->p
			&& arg_fmt->emax <= tg_fmt->emax
			&& (arg_fmt->emin - arg_fmt->p
			    >= tg_fmt->emin - tg_fmt->p))
		      {
			fn = &(*cexpr_list)[j];
			توڑو;
		      }
		  }
	      }
	    اگر (fn == تہی)
	      {
		error_at (loc, "no matching function for type-generic call");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    /* Construct a call to FN.  */
	    vec<درخت, va_gc> *دلائل;
	    vec_alloc (دلائل, nargs);
	    vec<درخت, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    برائے (غیرعلامتی صحیح j = 0; j < nargs; j++)
	      {
		c_اظہاریہ_t *ce = &(*cexpr_list)[عدد_functions + j];
		دلائل->تیز_ڈالو (ce->قدر);
		arg_loc.تیز_ڈالو (ce->get_location ());
		origtypes->تیز_ڈالو (ce->original_type);
	      }
	    اظہاریہ.قدر = c_build_function_call_vec (loc, arg_loc, fn->قدر,
						    دلائل, origtypes);
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_paren_loc);
	    توڑو;
	  }
	حالت RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_اظہاریہ_t, va_gc> *cexpr_list;
	    c_اظہاریہ_t *e2_p;
	    درخت chain_قدر;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_دلائل (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, جھوٹ,
					    &close_paren_loc))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (vec_محفوظ_لمبائی (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    اظہاریہ = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_مقصد_rvalue (loc, *e2_p, سچ, سچ);
	    chain_قدر = e2_p->قدر;
	    mark_exp_read (chain_قدر);

	    اگر (درخت_رمز (اظہاریہ.قدر) != CALL_اظہاریہ)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    ورنہ اگر (درخت_رمز (درخت_TYPE (chain_قدر)) != اشارہ_گر_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    ورنہ
	      CALL_اظہاریہ_STATIC_CHAIN (اظہاریہ.قدر) = chain_قدر;
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_paren_loc);
	    توڑو;
	  }
	حالت RID_BUILTIN_COMPLEX:
	  {
	    vec<c_اظہاریہ_t, va_gc> *cexpr_list;
	    c_اظہاریہ_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_دلائل (parser,
					    "__builtin_complex",
					    &cexpr_list, جھوٹ,
					    &close_paren_loc))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    اگر (vec_محفوظ_لمبائی (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_مقصد_rvalue (loc, *e1_p, سچ, سچ);
	    اگر (درخت_رمز (e1_p->قدر) == EXCESS_PRECISION_اظہاریہ)
	      e1_p->قدر = convert (درخت_TYPE (e1_p->قدر),
				     درخت_عملیہ (e1_p->قدر, 0));
	    *e2_p = convert_lvalue_مقصد_rvalue (loc, *e2_p, سچ, سچ);
	    اگر (درخت_رمز (e2_p->قدر) == EXCESS_PRECISION_اظہاریہ)
	      e2_p->قدر = convert (درخت_TYPE (e2_p->قدر),
				     درخت_عملیہ (e2_p->قدر, 0));
	    اگر (!SCALAR_FLOAT_TYPE_P (درخت_TYPE (e1_p->قدر))
		|| DECIMAL_FLOAT_TYPE_P (درخت_TYPE (e1_p->قدر))
		|| !SCALAR_FLOAT_TYPE_P (درخت_TYPE (e2_p->قدر))
		|| DECIMAL_FLOAT_TYPE_P (درخت_TYPE (e2_p->قدر)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (TYPE_MAIN_VARIANT (درخت_TYPE (e1_p->قدر))
		!= TYPE_MAIN_VARIANT (درخت_TYPE (e2_p->قدر)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    اظہاریہ.قدر = build2_loc (loc, COMPLEX_اظہاریہ,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (درخت_TYPE (e1_p->قدر))),
				     e1_p->قدر, e2_p->قدر);
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_paren_loc);
	    توڑو;
	  }
	حالت RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_اظہاریہ_t, va_gc> *cexpr_list;
	    c_اظہاریہ_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_دلائل (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, جھوٹ,
					    &close_paren_loc))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (vec_محفوظ_لمبائی (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    e_p = &(*cexpr_list)[0];
	    درخت ref = e_p->قدر;

	    اگر (درخت_رمز (درخت_TYPE (ref)) != ARRAY_TYPE
		 && درخت_رمز (درخت_TYPE (ref)) != اشارہ_گر_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    اگر (درخت_رمز (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    اگر (درخت_رمز (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    اگر (has_counted_by_object (ref))
	      اظہاریہ.قدر = get_counted_by_ref (ref);
	    ورنہ
	      اظہاریہ.قدر = null_اشارہ_گر_گرہ;

	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_paren_loc);
	    توڑو;
	  }
	حالت RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_اظہاریہ_t, va_gc> *cexpr_list;
	    غیرعلامتی صحیح i;
	    c_اظہاریہ_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_دلائل (parser,
					    "__builtin_shuffle",
					    &cexpr_list, جھوٹ,
					    &close_paren_loc))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    FOR_EACH_VEC_محفوظ_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_مقصد_rvalue (loc, *p, سچ, سچ);

	    اگر (vec_محفوظ_لمبائی (cexpr_list) == 2)
	      اظہاریہ.قدر = c_build_vec_perm_اظہاریہ (loc, (*cexpr_list)[0].قدر,
						  NULL_درخت,
						  (*cexpr_list)[1].قدر);

	    ورنہ اگر (vec_محفوظ_لمبائی (cexpr_list) == 3)
	      اظہاریہ.قدر = c_build_vec_perm_اظہاریہ (loc, (*cexpr_list)[0].قدر,
						  (*cexpr_list)[1].قدر,
						  (*cexpr_list)[2].قدر);
	    ورنہ
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		اظہاریہ.سیٹ_error ();
	      }
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_paren_loc);
	    توڑو;
	  }
	حالت RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_اظہاریہ_t, va_gc> *cexpr_list;
	    غیرعلامتی صحیح i;
	    c_اظہاریہ_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_دلائل (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, جھوٹ,
					    &close_paren_loc))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    FOR_EACH_VEC_محفوظ_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_مقصد_rvalue (loc, *p, سچ, سچ);

	    اگر (vec_محفوظ_لمبائی (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		اظہاریہ.سیٹ_error ();
	      }
	    ورنہ
	      {
		auto_vec<درخت, 16> نقاب;
		برائے (i = 2; i < cexpr_list->لمبائی (); ++i)
		  نقاب.محفوظ_ڈالو ((*cexpr_list)[i].قدر);
		اظہاریہ.قدر = c_build_shufflevector (loc, (*cexpr_list)[0].قدر,
						    (*cexpr_list)[1].قدر,
						    نقاب);
	      }
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_paren_loc);
	    توڑو;
	  }
	حالت RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t آغاز_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    e1 = c_parser_اظہاریہ_no_commas (parser, تہی);
	    mark_exp_read (e1.قدر);
	    اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t انتہا_loc = c_parser_peek_token (parser)->get_اختتام ();
	    c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    اگر (t1 == تہی)
	      اظہاریہ.سیٹ_error ();
	    ورنہ
	      {
		درخت type_اظہاریہ = NULL_درخت;
		اظہاریہ.قدر = c_build_vec_convert (آغاز_loc, e1.قدر, loc,
						  groktypename (t1, &type_اظہاریہ,
								تہی));
		سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, آغاز_loc, انتہا_loc);
	      }
	  }
	  توڑو;
	حالت RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t آغاز_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    e1 = c_parser_اظہاریہ_no_commas (parser, تہی);
	    mark_exp_read (e1.قدر);
	    location_t انتہا_loc = c_parser_peek_token (parser)->get_اختتام ();
	    parens.skip_until_ملا_close (parser);
	    اظہاریہ = parser_build_unary_op (loc, PAREN_اظہاریہ, e1);
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, آغاز_loc, انتہا_loc);
	  }
	  توڑو;
	حالت RID_BUILTIN_STDC:
	  {
	    vec<c_اظہاریہ_t, va_gc> *cexpr_list;
	    c_اظہاریہ_t *arg_p;
	    location_t close_paren_loc;
	    شمار c_builtin_stdc {
	      C_BUILTIN_STDC_ثنائی_ہندسہ_CEIL,
	      C_BUILTIN_STDC_ثنائی_ہندسہ_FLOOR,
	      C_BUILTIN_STDC_ثنائی_ہندسہ_چوڑائی,
	      C_BUILTIN_STDC_گنتی_ONES,
	      C_BUILTIN_STDC_گنتی_ZEROS,
	      C_BUILTIN_STDC_پہلا_LEADING_ONE,
	      C_BUILTIN_STDC_پہلا_LEADING_ZERO,
	      C_BUILTIN_STDC_پہلا_TRAILING_ONE,
	      C_BUILTIN_STDC_پہلا_TRAILING_ZERO,
	      C_BUILTIN_STDC_HAS_SINGLE_ثنائی_ہندسہ,
	      C_BUILTIN_STDC_LEADING_ONES,
	      C_BUILTIN_STDC_LEADING_ZEROS,
	      C_BUILTIN_STDC_ROTATE_بایاں,
	      C_BUILTIN_STDC_ROTATE_دایاں,
	      C_BUILTIN_STDC_TRAILING_ONES,
	      C_BUILTIN_STDC_TRAILING_ZEROS,
	      C_BUILTIN_STDC_MAX
	    } stdc_rid = C_BUILTIN_STDC_MAX;
	    ثابت حرف *name
	      = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
	    غیرعلامتی عدد_دلائل = 1;
	    انتخاب (name[حجم ("__builtin_stdc_") - 1])
	      {
	      حالت 'b':
		انتخاب (name[حجم ("__builtin_stdc_bit_") - 1])
		  {
		  حالت 'c':
		    stdc_rid = C_BUILTIN_STDC_ثنائی_ہندسہ_CEIL;
		    توڑو;
		  حالت 'f':
		    stdc_rid = C_BUILTIN_STDC_ثنائی_ہندسہ_FLOOR;
		    توڑو;
		  طےشدہ:
		    stdc_rid = C_BUILTIN_STDC_ثنائی_ہندسہ_چوڑائی;
		    توڑو;
		  }
		توڑو;
	      حالت 'c':
		اگر (name[حجم ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_گنتی_ONES;
		ورنہ
		  stdc_rid = C_BUILTIN_STDC_گنتی_ZEROS;
		توڑو;
	      حالت 'f':
		انتخاب (name[حجم ("__builtin_stdc_first_trailing_") - 1])
		  {
		  حالت 'n':
		    stdc_rid = C_BUILTIN_STDC_پہلا_LEADING_ONE;
		    توڑو;
		  حالت 'e':
		    stdc_rid = C_BUILTIN_STDC_پہلا_LEADING_ZERO;
		    توڑو;
		  حالت 'o':
		    stdc_rid = C_BUILTIN_STDC_پہلا_TRAILING_ONE;
		    توڑو;
		  طےشدہ:
		    stdc_rid = C_BUILTIN_STDC_پہلا_TRAILING_ZERO;
		    توڑو;
		  }
		توڑو;
	      حالت 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_ثنائی_ہندسہ;
		توڑو;
	      حالت 'l':
		اگر (name[حجم ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		ورنہ
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		توڑو;
	      حالت 'r':
		اگر (name[حجم ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_بایاں;
		ورنہ
		  stdc_rid = C_BUILTIN_STDC_ROTATE_دایاں;
		عدد_دلائل = 2;
		توڑو;
	      حالت 't':
		اگر (name[حجم ("__builtin_stdc_trailing_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ONES;
		ورنہ
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ZEROS;
		توڑو;
	      }
	    gcc_checking_assert (stdc_rid != C_BUILTIN_STDC_MAX);

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_دلائل (parser, name,
					    &cexpr_list, جھوٹ,
					    &close_paren_loc))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    اگر (vec_محفوظ_لمبائی (cexpr_list) != عدد_دلائل)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_مقصد_rvalue (loc, *arg_p, سچ, سچ);
	    اگر (!INTEGRAL_TYPE_P (درخت_TYPE (arg_p->قدر)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (درخت_رمز (درخت_TYPE (arg_p->قدر)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (درخت_رمز (درخت_TYPE (arg_p->قدر)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (!TYPE_UNSIGNED (درخت_TYPE (arg_p->قدر)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (TYPE_MAIN_VARIANT (درخت_TYPE (arg_p->قدر))
		== char_type_گرہ)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    درخت arg = arg_p->قدر;
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
	    اگر (عدد_دلائل == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_مقصد_rvalue (loc, *arg_p, سچ, سچ);
		اگر (!INTEGRAL_TYPE_P (درخت_TYPE (arg_p->قدر)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    اظہاریہ.سیٹ_error ();
		    توڑو;
		  }
		اگر (درخت_رمز (درخت_TYPE (arg_p->قدر)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    اظہاریہ.سیٹ_error ();
		    توڑو;
		  }
		درخت arg1 = save_اظہاریہ (arg);
		درخت arg2 = save_اظہاریہ (arg_p->قدر);
		درخت_رمز_2 رمز;
		اگر (stdc_rid == C_BUILTIN_STDC_ROTATE_بایاں)
		  رمز = LROTATE_اظہاریہ;
		ورنہ
		  رمز = RROTATE_اظہاریہ;

		اگر (درخت_رمز (arg2) == INTEGER_CST
		    && درخت_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_گنتی_negative,
			      "rotate count is negative");

		درخت instrument_اظہاریہ = NULL_درخت;
		اگر (sanitize_flags_p (SANITIZE_سرکاؤ))
		  instrument_اظہاریہ = ubsan_instrument_سرکاؤ (loc, رمز,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		اگر (TYPE_PRECISION (درخت_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_گرہ))
		  arg2 = fold_convert (unsigned_type_گرہ, arg2);

		اگر (TYPE_UNSIGNED (درخت_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_اظہاریہ, درخت_TYPE (arg2),
				     arg2, build_int_cst (درخت_TYPE (arg2),
							  prec));
		ورنہ
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    درخت utype = c_common_unsigned_type (درخت_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_اظہاریہ, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		اگر (type_has_منوال_precision_p (درخت_TYPE (arg1))
		    || (درخت_رمز (درخت_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_منوال_سائز))
		  اظہاریہ.قدر = build2_loc (loc, رمز, درخت_TYPE (arg1), arg1,
					   arg2);
		ورنہ
		  {
		    arg2 = save_اظہاریہ (arg2);
		    درخت t1 = build2_loc (loc, (رمز == LROTATE_اظہاریہ
						? LSHIFT_اظہاریہ : RSHIFT_اظہاریہ),
					  درخت_TYPE (arg1), arg1, arg2);
		    درخت t2 = build2_loc (loc, MINUS_اظہاریہ,
					  درخت_TYPE (arg2),
					  build_int_cst (درخت_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (رمز == LROTATE_اظہاریہ
					   ? RSHIFT_اظہاریہ : LSHIFT_اظہاریہ),
				     درخت_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_گنتی_حد_سے_تجاوز);
		    درخت t3 = build2_loc (loc, ثنائی_ہندسہ_IOR_اظہاریہ,
					  درخت_TYPE (arg1), t1, t2);
		    درخت t4 = build2_loc (loc, NE_اظہاریہ, boolean_type_گرہ,
					  arg2,
					  build_zero_cst (درخت_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_اظہاریہ, boolean_type_گرہ,
				     arg1, t4);
		    اظہاریہ.قدر = build3_loc (loc, COND_اظہاریہ,
					     درخت_TYPE (arg1), t4, t3, arg1);
		  }
		اگر (instrument_اظہاریہ)
		  اظہاریہ.قدر = build2_loc (loc, COMPOUND_اظہاریہ,
					   درخت_TYPE (اظہاریہ.قدر),
					   instrument_اظہاریہ, اظہاریہ.قدر);
		سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_paren_loc);
		توڑو;
	      }
	    درخت barg1 = arg;
	    انتخاب (stdc_rid)
	      {
	      حالت C_BUILTIN_STDC_ثنائی_ہندسہ_CEIL:
		arg = save_اظہاریہ (arg);
		barg1 = build2_loc (loc, PLUS_اظہاریہ, type, arg,
				    build_int_cst (type, -1));
		توڑو;
	      حالت C_BUILTIN_STDC_ثنائی_ہندسہ_FLOOR:
		barg1 = arg = save_اظہاریہ (arg);
		توڑو;
	      حالت C_BUILTIN_STDC_گنتی_ZEROS:
	      حالت C_BUILTIN_STDC_پہلا_LEADING_ZERO:
	      حالت C_BUILTIN_STDC_پہلا_TRAILING_ZERO:
	      حالت C_BUILTIN_STDC_LEADING_ONES:
	      حالت C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, ثنائی_ہندسہ_NOT_اظہاریہ, type, arg);
		توڑو;
	      طےشدہ:
		توڑو;
	      }
	    درخت barg2 = NULL_درخت;
	    انتخاب (stdc_rid)
	      {
	      حالت C_BUILTIN_STDC_ثنائی_ہندسہ_چوڑائی:
	      حالت C_BUILTIN_STDC_LEADING_ONES:
	      حالت C_BUILTIN_STDC_LEADING_ZEROS:
	      حالت C_BUILTIN_STDC_TRAILING_ONES:
	      حالت C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_گرہ, prec);
		توڑو;
	      حالت C_BUILTIN_STDC_پہلا_LEADING_ONE:
	      حالت C_BUILTIN_STDC_پہلا_LEADING_ZERO:
	      حالت C_BUILTIN_STDC_پہلا_TRAILING_ONE:
	      حالت C_BUILTIN_STDC_پہلا_TRAILING_ZERO:
		barg2 = integer_minus_one_گرہ;
		توڑو;
	      طےشدہ:
		توڑو;
	      }
	    درخت fndecl = NULL_درخت;
	    انتخاب (stdc_rid)
	      {
	      حالت C_BUILTIN_STDC_ثنائی_ہندسہ_CEIL:
	      حالت C_BUILTIN_STDC_ثنائی_ہندسہ_FLOOR:
	      حالت C_BUILTIN_STDC_ثنائی_ہندسہ_چوڑائی:
	      حالت C_BUILTIN_STDC_پہلا_LEADING_ONE:
	      حالت C_BUILTIN_STDC_پہلا_LEADING_ZERO:
	      حالت C_BUILTIN_STDC_LEADING_ONES:
	      حالت C_BUILTIN_STDC_LEADING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_اندر_CLZG);
		توڑو;
	      حالت C_BUILTIN_STDC_پہلا_TRAILING_ONE:
	      حالت C_BUILTIN_STDC_پہلا_TRAILING_ZERO:
	      حالت C_BUILTIN_STDC_TRAILING_ONES:
	      حالت C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_اندر_CTZG);
		توڑو;
	      حالت C_BUILTIN_STDC_گنتی_ONES:
	      حالت C_BUILTIN_STDC_گنتی_ZEROS:
	      حالت C_BUILTIN_STDC_HAS_SINGLE_ثنائی_ہندسہ:
		fndecl = builtin_decl_explicit (BUILT_اندر_POPCOUNTG);
		توڑو;
	      طےشدہ:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    صحیح nargs = barg2 != NULL_درخت ? 2 : 1;
	    vec<درخت, va_gc> *دلائل;
	    vec_alloc (دلائل, nargs);
	    vec<درخت, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    دلائل->تیز_ڈالو (barg1);
	    arg_loc.تیز_ڈالو (arg_p->get_location ());
	    origtypes->تیز_ڈالو (arg_p->original_type);
	    اگر (nargs == 2)
	      {
		دلائل->تیز_ڈالو (barg2);
		arg_loc.تیز_ڈالو (loc);
		origtypes->تیز_ڈالو (integer_type_گرہ);
	      }
	    اظہاریہ.قدر = c_build_function_call_vec (loc, arg_loc, fndecl,
						    دلائل, origtypes);
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_paren_loc);
	    اگر (اظہاریہ.قدر == error_mark_گرہ)
	      توڑو;
	    انتخاب (stdc_rid)
	      {
	      حالت C_BUILTIN_STDC_ثنائی_ہندسہ_CEIL:
	      حالت C_BUILTIN_STDC_ثنائی_ہندسہ_FLOOR:
		--prec;
		/* FALLTHRU */
	      حالت C_BUILTIN_STDC_ثنائی_ہندسہ_چوڑائی:
		اظہاریہ.قدر = build2_loc (loc, MINUS_اظہاریہ, integer_type_گرہ,
					 build_int_cst (integer_type_گرہ,
							prec), اظہاریہ.قدر);
		توڑو;
	      حالت C_BUILTIN_STDC_پہلا_LEADING_ONE:
	      حالت C_BUILTIN_STDC_پہلا_LEADING_ZERO:
	      حالت C_BUILTIN_STDC_پہلا_TRAILING_ONE:
	      حالت C_BUILTIN_STDC_پہلا_TRAILING_ZERO:
		اظہاریہ.قدر = build2_loc (loc, PLUS_اظہاریہ, integer_type_گرہ,
					 اظہاریہ.قدر, integer_one_گرہ);
		توڑو;
	      حالت C_BUILTIN_STDC_HAS_SINGLE_ثنائی_ہندسہ:
		اظہاریہ.قدر = build2_loc (loc, EQ_اظہاریہ, boolean_type_گرہ,
					 اظہاریہ.قدر, integer_one_گرہ);
		توڑو;
	      طےشدہ:
		توڑو;
	      }

	    اگر (stdc_rid != C_BUILTIN_STDC_ثنائی_ہندسہ_CEIL
		&& stdc_rid != C_BUILTIN_STDC_ثنائی_ہندسہ_FLOOR)
	      {
		اگر (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_ثنائی_ہندسہ)
		  اظہاریہ.قدر = fold_convert_loc (loc, unsigned_type_گرہ,
						 اظہاریہ.قدر);
		توڑو;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    اگر (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_ثنائی_ہندسہ_CEIL && integer_onep (arg)))
	      اظہاریہ.قدر = build_int_cst (type, 0);
	    ورنہ
	      اظہاریہ.قدر
		= build2_loc (loc, LSHIFT_اظہاریہ, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_ثنائی_ہندسہ_CEIL
					      ? 2 : 1)), اظہاریہ.قدر);
	    اگر (stdc_rid == C_BUILTIN_STDC_ثنائی_ہندسہ_CEIL)
	      اظہاریہ.قدر = build3_loc (loc, COND_اظہاریہ, type,
				       build2_loc (loc, LE_اظہاریہ,
						   boolean_type_گرہ, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       اظہاریہ.قدر);
	    ورنہ
	      اظہاریہ.قدر = build3_loc (loc, COND_اظہاریہ, type,
				       build2_loc (loc, EQ_اظہاریہ,
						   boolean_type_گرہ, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       اظہاریہ.قدر);
	    توڑو;
	  }
	حالت RID_BUILTIN_BSWAPG:
	حالت RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_اظہاریہ_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    اندرونی_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    ثابت حرف *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    اگر (!c_parser_get_builtin_دلائل (parser, name, &cexpr_list, جھوٹ,
					    &close_paren_loc))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    اگر (vec_محفوظ_لمبائی (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }

	    c_اظہاریہ_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_مقصد_rvalue (loc, *arg_p, سچ, سچ);
	    درخت arg = arg_p->قدر;
	    اگر (error_عملیہ_p (arg))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    درخت type = TYPE_MAIN_VARIANT (درخت_TYPE (arg));
	    اگر (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (درخت_رمز (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (درخت_رمز (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    arg = c_fully_fold (arg, جھوٹ, تہی);
	    اظہاریہ.قدر = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_paren_loc);
	    توڑو;
	  }
	حالت RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    درخت sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_ملا_close (parser);
	    اظہاریہ.قدر = objc_build_selector_اظہاریہ (loc, sel);
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_loc);
	  }
	  توڑو;
	حالت RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    درخت id = c_parser_peek_token (parser)->قدر;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_ملا_close (parser);
	    اظہاریہ.قدر = objc_build_protocol_اظہاریہ (id);
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_loc);
	  }
	  توڑو;
	حالت RID_AT_ENCODE:
	  {
	    /* Extension to support C-structures in the archiver.  */
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    اگر (!parens.require_open (parser))
	      {
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    t1 = c_parser_type_name (parser);
	    اگر (t1 == تہی)
	      {
		اظہاریہ.سیٹ_error ();
		c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
		توڑو;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_ملا_close (parser);
	    درخت type = groktypename (t1, تہی, تہی);
	    اظہاریہ.قدر = objc_build_encode_اظہاریہ (type);
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_loc);
	  }
	  توڑو;
	حالت RID_GENERIC:
	  اظہاریہ = c_parser_generic_selection (parser);
	  توڑو;
	حالت RID_OMP_ALL_حافظہ:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  اظہاریہ.سیٹ_error ();
	  توڑو;
	/* C23 'nullptr' literal.  */
	حالت RID_NULLPTR:
	  c_parser_consume_token (parser);
	  اظہاریہ.قدر = nullptr_گرہ;
	  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  توڑو;
	حالت RID_TRUE:
	  c_parser_consume_token (parser);
	  اظہاریہ.قدر = boolean_true_گرہ;
	  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, tok_range);
	  توڑو;
	حالت RID_FALSE:
	  c_parser_consume_token (parser);
	  اظہاریہ.قدر = boolean_false_گرہ;
	  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, tok_range);
	  توڑو;
	طےشدہ:
	  c_parser_error (parser, "expected expression");
	  اظہاریہ.سیٹ_error ();
	  توڑو;
	}
      توڑو;
    حالت CPP_OPEN_مربع:
      اگر (c_dialect_objc ())
	{
	  درخت receiver, دلائل;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  دلائل = c_parser_objc_پیغام_دلائل (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_مربع,
				     "expected %<]%>");
	  اظہاریہ.قدر = objc_build_پیغام_اظہاریہ (receiver, دلائل);
	  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, loc, close_loc);
	  توڑو;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    طےشدہ:
      c_parser_error (parser, "expected expression");
      اظہاریہ.سیٹ_error ();
      توڑو;
    }
 برآمد:
  واپس c_parser_postfix_عبارت_after_primary
    (parser, اظہاریہ_LOC_OR_LOC (اظہاریہ.قدر, loc), اظہاریہ);
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

ساکن ساخت c_اظہاریہ
c_parser_postfix_عبارت_after_paren_type (c_parser *parser,
					      ساخت c_declspecs *scspecs,
					      ساخت c_type_name *type_name,
					      location_t type_loc)
{
  درخت type;
  ساخت c_اظہاریہ init;
  منطقی non_const;
  ساخت c_اظہاریہ اظہاریہ;
  location_t آغاز_loc;
  درخت type_اظہاریہ = NULL_درخت;
  منطقی type_اظہاریہ_const = سچ;
  منطقی constexpr_p = scspecs ? scspecs->constexpr_p : جھوٹ;
  غیرعلامتی صحیح underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (سطر_جدول, type_loc);
  آغاز_loc = c_parser_peek_token (parser)->location;
  اگر (constexpr_p)
    {
      underspec_state = آغاز_underspecified_init (آغاز_loc, NULL_درخت);
      /* A constexpr compound literal is subject to the constraints on
	 underspecified declarations, which may not declare tags or
	 members or structures or unions; it is undefined behavior to
	 declare the members of an enumeration.  Where the structure,
	 union or enumeration type is declared within the compound
	 literal initializer, this is diagnosed elsewhere as a result
	 of the above call to start_underspecified_init.  Diagnose
	 here the case of declaring such a type in the type specifiers
	 of the compound literal.  */
      انتخاب (type_name->specs->typespec_قسم)
	{
	حالت ctsk_tagfirstref:
	حالت ctsk_tagfirstref_attrs:
	  error_at (type_loc, "%qT declared in %<constexpr%> compound literal",
		    type_name->specs->type);
	  توڑو;

	حالت ctsk_tagdef:
	  error_at (type_loc, "%qT defined in %<constexpr%> compound literal",
		    type_name->specs->type);
	  توڑو;

	طےشدہ:
	  توڑو;
	}
    }
  آغاز_init (NULL_درخت, تہی,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_اظہاریہ, &type_اظہاریہ_const);
  منطقی varsize_p = جھوٹ;
  اگر (type != error_mark_گرہ && C_TYPE_VARIABLE_سائز (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = سچ;
    }
  ورنہ اگر (درخت_رمز (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_گرہ;
    }
  اگر (constexpr_p && type != error_mark_گرہ)
    {
      درخت type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      اگر (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      ورنہ اگر (ریکارڈ_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, جھوٹ, تہی, varsize_p);
  اگر (constexpr_p)
    اختتام_underspecified_init (NULL_درخت, underspec_state);
  اختتام_init ();
  maybe_warn_string_init (type_loc, type, init);

  اگر (type != error_mark_گرہ
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_گرہ;
    }

  اگر (!pedwarn_c90 (آغاز_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (آغاز_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.قدر && درخت_رمز (init.قدر) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.قدر)
	       : init.original_رمز == C_MAYBE_CONST_اظہاریہ);
  non_const |= !type_اظہاریہ_const;
  غیرعلامتی صحیح alignas_align = 0;
  اگر (type != error_mark_گرہ
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      اگر (alignas_align < min_align_کا_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  اظہاریہ.قدر = build_compound_literal (آغاز_loc, type, init.قدر, non_const,
				       alignas_align, scspecs);
  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, init.src_range);
  اظہاریہ.m_decimal = 0;
  اظہاریہ.original_رمز = ERROR_MARK;
  اظہاریہ.original_type = تہی;
  اگر (type != error_mark_گرہ
      && اظہاریہ.قدر != error_mark_گرہ
      && type_اظہاریہ)
    {
      اگر (درخت_رمز (اظہاریہ.قدر) == C_MAYBE_CONST_اظہاریہ)
	{
	  gcc_assert (C_MAYBE_CONST_اظہاریہ_PRE (اظہاریہ.قدر) == NULL_درخت);
	  C_MAYBE_CONST_اظہاریہ_PRE (اظہاریہ.قدر) = type_اظہاریہ;
	}
      ورنہ
	{
	  gcc_assert (!non_const);
	  اظہاریہ.قدر = build2 (C_MAYBE_CONST_اظہاریہ, type,
			       type_اظہاریہ, اظہاریہ.قدر);
	}
    }
  واپس c_parser_postfix_عبارت_after_primary (parser, آغاز_loc, اظہاریہ);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

ساکن منطقی
sizeof_ptr_memacc_comptypes (درخت type1, درخت type2)
{
  واپس comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

ساکن خالی
warn_for_abs (location_t loc, درخت fndecl, درخت arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  اگر (c_inhibit_evaluation_warnings)
    واپس;

  درخت atype = درخت_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  اگر (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && درخت_رمز (atype) != COMPLEX_TYPE)
    واپس;

  شمار built_اندر_function fcode = DECL_FUNCTION_رمز (fndecl);

  انتخاب (fcode)
    {
    حالت BUILT_اندر_ABS:
    حالت BUILT_اندر_LABS:
    حالت BUILT_اندر_LLABS:
    حالت BUILT_اندر_IMAXABS:
      اگر (!INTEGRAL_TYPE_P (atype))
	{
	  اگر (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  ورنہ اگر (درخت_رمز (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  ورنہ
	    gcc_unreachable ();
	  واپس;
	}
      اگر (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_قدر,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      توڑو;

    CASE_FLT_FN (BUILT_اندر_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندر_FABS):
      اگر (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_منوال_P (TYPE_منوال (atype)))
	{
	  اگر (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  ورنہ اگر (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  ورنہ اگر (درخت_رمز (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  ورنہ
	    gcc_unreachable ();
	  واپس;
	}
      توڑو;

    CASE_FLT_FN (BUILT_اندر_CABS):
      اگر (درخت_رمز (atype) != COMPLEX_TYPE)
	{
	  اگر (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  ورنہ اگر (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  ورنہ
	    gcc_unreachable ();

	  واپس;
	}
      توڑو;

    حالت BUILT_اندر_FABSD32:
    حالت BUILT_اندر_FABSD64:
    حالت BUILT_اندر_FABSD128:
    حالت BUILT_اندر_FABSD64_X:
      اگر (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  اگر (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  ورنہ اگر (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  ورنہ اگر (درخت_رمز (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using decimal floating-point absolute value "
			"function %qD when argument is of complex type %qT",
			fndecl, atype);
	  ورنہ
	    gcc_unreachable ();
	  واپس;
	}
      توڑو;

    طےشدہ:
      واپس;
    }

  اگر (!TYPE_ARG_TYPES (درخت_TYPE (fndecl)))
    واپس;

  درخت ftype = درخت_قدر (TYPE_ARG_TYPES (درخت_TYPE (fndecl)));
  اگر (درخت_رمز (atype) == COMPLEX_TYPE)
    {
      gcc_assert (درخت_رمز (ftype) == COMPLEX_TYPE);
      atype = درخت_TYPE (atype);
      ftype = درخت_TYPE (ftype);
    }

  اگر (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_قدر,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

ساکن ساخت c_اظہاریہ
c_parser_postfix_عبارت_after_primary (c_parser *parser,
					   location_t اظہاریہ_loc,
					   ساخت c_اظہاریہ اظہاریہ)
{
  ساخت c_اظہاریہ orig_اظہاریہ;
  درخت ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  درخت sizeof_arg[6];
  غیرعلامتی صحیح literal_zero_نقاب;
  غیرعلامتی صحیح i;
  vec<درخت, va_gc> *exprlist;
  vec<درخت, va_gc> *origtypes = تہی;
  vec<location_t> arg_loc = vNULL;
  location_t آغاز;
  location_t اختتام;

  جب (سچ)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_OPEN_مربع:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_درخت;
	  اگر (!c_omp_array_section_p
	      || c_parser_اگلا_token_is_not (parser, CPP_COLON))
	    idx = c_parser_عبارت (parser).قدر;

	  اگر (c_omp_array_section_p
	      && c_parser_اگلا_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      اگر (c_parser_اگلا_token_is_not (parser, CPP_CLOSE_مربع))
		len = c_parser_عبارت (parser).قدر;

	      اظہاریہ.قدر = build_omp_array_section (op_loc, اظہاریہ.قدر, idx,
						    len);
	    }
	  ورنہ
	    اظہاریہ.قدر = build_array_ref (op_loc, اظہاریہ.قدر, idx);

	  c_parser_skip_until_ملا (parser, CPP_CLOSE_مربع,
				     "expected %<]%>");

	  آغاز = اظہاریہ.get_آغاز ();
	  اختتام = parser->علامات_buf[0].location;
	  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, آغاز, اختتام);
	  اظہاریہ.original_رمز = ERROR_MARK;
	  اظہاریہ.original_type = تہی;
	  اظہاریہ.m_decimal = 0;
	  توڑو;
	حالت CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    برائے (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_درخت;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_نقاب = 0;
	    اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = تہی;
	    ورنہ اگر (درخت_رمز (اظہاریہ.قدر) == FUNCTION_DECL
		     && fndecl_built_اندر_p (اظہاریہ.قدر, BUILT_اندر_CLASSIFY_TYPE)
		     && c_parser_اگلا_علامات_آغاز_typename (parser,
							     cla_prefer_id))
	      {
		/* __builtin_classify_type (type)  */
		c_inhibit_evaluation_warnings++;
		اندر_alignof++;
		ساخت c_type_name *type = c_parser_type_name (parser);
		c_inhibit_evaluation_warnings--;
		اندر_alignof--;
		ساخت c_typespec ret;
		ret.اظہاریہ = NULL_درخت;
		ret.spec = error_mark_گرہ;
		ret.اظہاریہ_const_operands = جھوٹ;
		اگر (type != تہی)
		  ret.spec = groktypename (type, &ret.اظہاریہ,
					   &ret.اظہاریہ_const_operands);
		parens.skip_until_ملا_close (parser);
		اظہاریہ.قدر = build_int_cst (integer_type_گرہ,
					    type_مقصد_class (ret.spec));
		توڑو;
	      }
	    ورنہ
	      exprlist = c_parser_اظہاریہ_list (parser, سچ, جھوٹ, &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_نقاب);
	    parens.skip_until_ملا_close (parser);
	  }
	  orig_اظہاریہ = اظہاریہ;
	  mark_exp_read (اظہاریہ.قدر);
	  اگر (warn_sizeof_اشارہ_گر_memaccess)
	    sizeof_اشارہ_گر_memaccess_warning (sizeof_arg_loc,
					      اظہاریہ.قدر, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  اگر (درخت_رمز (اظہاریہ.قدر) == FUNCTION_DECL)
	    {
	      اگر (fndecl_built_اندر_p (اظہاریہ.قدر, BUILT_اندر_MEMSET)
		  && vec_محفوظ_لمبائی (exprlist) == 3)
		{
		  درخت arg0 = (*exprlist)[0];
		  درخت arg2 = (*exprlist)[2];
		  warn_for_memset (اظہاریہ_loc, arg0, arg2, literal_zero_نقاب);
		}
	      اگر (warn_absolute_قدر
		  && fndecl_built_اندر_p (اظہاریہ.قدر, BUILT_اندر_معمول)
		  && vec_محفوظ_لمبائی (exprlist) == 1)
		warn_for_abs (اظہاریہ_loc, اظہاریہ.قدر, (*exprlist)[0]);
	      اگر (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->اندر_intervening_رمز
		  && omp_runtime_api_call (اظہاریہ.قدر))
		{
		  error_at (اظہاریہ_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->fail = سچ;
		}
	      اگر (warn_calloc_transposed_دلائل)
		اگر (درخت attr = lookup_attribute ("alloc_size",
						  TYPE_اوصاف
						    (درخت_TYPE (اظہاریہ.قدر))))
		  اگر (درخت_قدر (attr) && درخت_CHAIN (درخت_قدر (attr)))
		    warn_for_calloc (sizeof_arg_loc, اظہاریہ.قدر, exprlist,
				     sizeof_arg, attr);
	    }

	  آغاز = اظہاریہ.get_آغاز ();
	  اختتام = parser->علامات_buf[0].get_اختتام ();
	  اظہاریہ.قدر
	    = c_build_function_call_vec (اظہاریہ_loc, arg_loc, اظہاریہ.قدر,
					 exprlist, origtypes);
	  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, آغاز, اختتام);
	  اظہاریہ.m_decimal = 0;

	  اظہاریہ.original_رمز = ERROR_MARK;
	  اگر (درخت_رمز (اظہاریہ.قدر) == INTEGER_CST
	      && درخت_رمز (orig_اظہاریہ.قدر) == FUNCTION_DECL
	      && fndecl_built_اندر_p (orig_اظہاریہ.قدر, BUILT_اندر_CONSTANT_P))
	    اظہاریہ.original_رمز = C_MAYBE_CONST_اظہاریہ;
	  اظہاریہ.original_type = تہی;
	  اگر (exprlist)
	    {
	      release_درخت_سمتیہ (exprlist);
	      release_درخت_سمتیہ (origtypes);
	    }
	  arg_loc.release ();
	  توڑو;
	حالت CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  اظہاریہ = default_function_array_conversion (اظہاریہ_loc, اظہاریہ);
	  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->قدر;
	      comp_loc = comp_tok->location;
	    }
	  ورنہ
	    {
	      c_parser_error (parser, "expected identifier");
	      اظہاریہ.سیٹ_error ();
	      اظہاریہ.original_رمز = ERROR_MARK;
              اظہاریہ.original_type = تہی;
	      واپس اظہاریہ;
	    }
	  آغاز = اظہاریہ.get_آغاز ();
	  اختتام = c_parser_peek_token (parser)->get_اختتام ();
	  c_parser_consume_token (parser);
	  اظہاریہ.قدر = build_component_ref (op_loc, اظہاریہ.قدر, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, آغاز, اختتام);
	  اظہاریہ.original_رمز = ERROR_MARK;
	  اگر (درخت_رمز (اظہاریہ.قدر) != COMPONENT_REF)
	    اظہاریہ.original_type = تہی;
	  ورنہ
	    {
	      /* Remember the original type of a bitfield.  */
	      درخت میدان_2 = درخت_عملیہ (اظہاریہ.قدر, 1);
	      اگر (درخت_رمز (میدان_2) != میدان_DECL)
		اظہاریہ.original_type = تہی;
	      ورنہ
		اظہاریہ.original_type = DECL_ثنائی_ہندسہ_میدان_TYPE (میدان_2);
	    }
	  اظہاریہ.m_decimal = 0;
	  توڑو;
	حالت CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, سچ, جھوٹ);
	  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->قدر;
	      comp_loc = comp_tok->location;
	    }
	  ورنہ
	    {
	      c_parser_error (parser, "expected identifier");
	      اظہاریہ.سیٹ_error ();
	      اظہاریہ.original_رمز = ERROR_MARK;
	      اظہاریہ.original_type = تہی;
	      واپس اظہاریہ;
	    }
	  آغاز = اظہاریہ.get_آغاز ();
	  اختتام = c_parser_peek_token (parser)->get_اختتام ();
	  c_parser_consume_token (parser);
	  اظہاریہ.قدر = build_component_ref (op_loc,
					    build_بالواسطہ_ref (op_loc,
								اظہاریہ.قدر,
								RO_ARROW),
					    ident, comp_loc,
					    اظہاریہ.get_location ());
	  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, آغاز, اختتام);
	  اظہاریہ.original_رمز = ERROR_MARK;
	  اگر (درخت_رمز (اظہاریہ.قدر) != COMPONENT_REF)
	    اظہاریہ.original_type = تہی;
	  ورنہ
	    {
	      /* Remember the original type of a bitfield.  */
	      درخت میدان_2 = درخت_عملیہ (اظہاریہ.قدر, 1);
	      اگر (درخت_رمز (میدان_2) != میدان_DECL)
		اظہاریہ.original_type = تہی;
	      ورنہ
		اظہاریہ.original_type = DECL_ثنائی_ہندسہ_میدان_TYPE (میدان_2);
	    }
	  اظہاریہ.m_decimal = 0;
	  توڑو;
	حالت CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  آغاز = اظہاریہ.get_آغاز ();
	  اختتام = c_parser_peek_token (parser)->get_اختتام ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (اظہاریہ.قدر);
	  اظہاریہ = default_function_array_conversion (اظہاریہ_loc, اظہاریہ);
	  اظہاریہ.قدر = build_unary_op (op_loc, POSTINCREMENT_اظہاریہ,
				       اظہاریہ.قدر, جھوٹ);
	  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, آغاز, اختتام);
	  اظہاریہ.original_رمز = ERROR_MARK;
	  اظہاریہ.original_type = تہی;
	  توڑو;
	حالت CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  آغاز = اظہاریہ.get_آغاز ();
	  اختتام = c_parser_peek_token (parser)->get_اختتام ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (اظہاریہ.قدر);
	  اظہاریہ = default_function_array_conversion (اظہاریہ_loc, اظہاریہ);
	  اظہاریہ.قدر = build_unary_op (op_loc, POSTDECREMENT_اظہاریہ,
				       اظہاریہ.قدر, جھوٹ);
	  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, آغاز, اختتام);
	  اظہاریہ.original_رمز = ERROR_MARK;
	  اظہاریہ.original_type = تہی;
	  توڑو;
	طےشدہ:
	  واپس اظہاریہ;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

ساکن ساخت c_اظہاریہ
c_parser_عبارت (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  ساخت c_اظہاریہ اظہاریہ;
  اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
    اظہاریہ = convert_lvalue_مقصد_rvalue (tloc, اظہاریہ, سچ, جھوٹ);
  جب (c_parser_اگلا_token_is (parser, CPP_COMMA))
    {
      ساخت c_اظہاریہ اگلا;
      درخت lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t اظہاریہ_loc;
      c_parser_consume_token (parser);
      اظہاریہ_loc = c_parser_peek_token (parser)->location;
      lhsval = اظہاریہ.قدر;
      جب (درخت_رمز (lhsval) == COMPOUND_اظہاریہ
	     || درخت_رمز (lhsval) == NOP_اظہاریہ)
	{
	  اگر (درخت_رمز (lhsval) == COMPOUND_اظہاریہ)
	    lhsval = درخت_عملیہ (lhsval, 1);
	  ورنہ
	    lhsval = درخت_عملیہ (lhsval, 0);
	}
      اگر (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      اگر (c_parser_اگلا_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  درخت val = embed->قدر;
	  غیرعلامتی آخری = RAW_ڈیٹا_لمبائی (val) - 1;
	  اگلا.قدر = build_int_cst (درخت_TYPE (val),
				      RAW_ڈیٹا_UCHAR_ELT (val, آخری));
	  اگلا.original_type = integer_type_گرہ;
	  c_parser_consume_token (parser);
	}
      ورنہ
	{
	  اگلا = c_parser_اظہاریہ_no_commas (parser, تہی);
	  اگلا = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اگلا, سچ, جھوٹ);
	}
      اظہاریہ.قدر = build_compound_اظہاریہ (loc, اظہاریہ.قدر, اگلا.قدر);
      اظہاریہ.original_رمز = COMPOUND_اظہاریہ;
      اظہاریہ.original_type = اگلا.original_type;
      اظہاریہ.m_decimal = 0;
    }
  واپس اظہاریہ;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

ساکن ساخت c_اظہاریہ
c_parser_عبارت_conv (c_parser *parser)
{
  ساخت c_اظہاریہ اظہاریہ;
  location_t loc = c_parser_peek_token (parser)->location;
  اظہاریہ = c_parser_عبارت (parser);
  اظہاریہ = convert_lvalue_مقصد_rvalue (loc, اظہاریہ, سچ, جھوٹ);
  واپس اظہاریہ;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

ساکن اندرونی خالی
c_parser_check_literal_zero (c_parser *parser, غیرعلامتی *literal_zero_نقاب,
			     غیرعلامتی صحیح idx)
{
  اگر (idx >= HOST_بٹ_فی_INT)
    واپس;

  c_token *tok = c_parser_peek_token (parser);
  انتخاب (tok->type)
    {
    حالت CPP_نمبر:
    حالت CPP_CHAR:
    حالت CPP_WCHAR:
    حالت CPP_CHAR16:
    حالت CPP_CHAR32:
    حالت CPP_UTF8CHAR:
      /* If a parameter is literal zero alone, remember it
	 for -Wmemset-transposed-args warning.  */
      اگر (integer_zerop (tok->قدر)
	  && !درخت_حد_سے_تجاوز (tok->قدر)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_نقاب |= 1U << idx;
    طےشدہ:
      توڑو;
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

ساکن vec<درخت, va_gc> *
c_parser_اظہاریہ_list (c_parser *parser, منطقی convert_p, منطقی fold_p,
		    vec<درخت, va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, درخت *sizeof_arg,
		    vec<location_t> *locations,
		    غیرعلامتی صحیح *literal_zero_نقاب)
{
  vec<درخت, va_gc> *ret;
  vec<درخت, va_gc> *orig_types;
  ساخت c_اظہاریہ اظہاریہ;
  غیرعلامتی صحیح idx = 0;
  منطقی save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = جھوٹ;

  ret = make_درخت_سمتیہ ();
  اگر (p_orig_types == تہی)
    orig_types = تہی;
  ورنہ
    orig_types = make_درخت_سمتیہ ();

  اگر (literal_zero_نقاب)
    c_parser_check_literal_zero (parser, literal_zero_نقاب, 0);
  اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
  اگر (convert_p)
    اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ.get_location (), اظہاریہ, سچ, سچ);
  اگر (fold_p)
    اظہاریہ.قدر = c_fully_fold (اظہاریہ.قدر, جھوٹ, تہی);
  ret->تیز_ڈالو (اظہاریہ.قدر);
  اگر (orig_types)
    orig_types->تیز_ڈالو (اظہاریہ.original_type);
  اگر (locations)
    locations->محفوظ_ڈالو (اظہاریہ.get_location ());
  اگر (sizeof_arg != تہی
      && (اظہاریہ.original_رمز == SIZEOF_اظہاریہ
	  || اظہاریہ.original_رمز == PAREN_SIZEOF_اظہاریہ))
    {
      sizeof_arg[0] = c_آخری_sizeof_arg;
      sizeof_arg_loc[0] = c_آخری_sizeof_loc;
    }
  جب (c_parser_اگلا_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      اگر (c_parser_اگلا_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  درخت قدر = embed->قدر;
	  اظہاریہ.original_رمز = INTEGER_CST;
	  اظہاریہ.original_type = integer_type_گرہ;
	  اظہاریہ.قدر = NULL_درخت;
	  سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, embed->get_range ());
	  اظہاریہ.m_decimal = 0;
	  برائے (غیرعلامتی صحیح i = 0; i < (غیرعلامتی) RAW_ڈیٹا_لمبائی (قدر); i++)
	    {
	      اگر (literal_zero_نقاب
		  && idx + 1 < HOST_بٹ_فی_INT
		  && RAW_ڈیٹا_اشارہ_گر (قدر)[i] == 0)
		*literal_zero_نقاب |= 1U << (idx + 1);
	      اظہاریہ.قدر = build_int_cst (integer_type_گرہ,
					  RAW_ڈیٹا_UCHAR_ELT (قدر, i));
	      vec_محفوظ_ڈالو (ret, اظہاریہ.قدر);
	      اگر (orig_types)
		vec_محفوظ_ڈالو (orig_types, اظہاریہ.original_type);
	      اگر (locations)
		locations->محفوظ_ڈالو (اظہاریہ.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  جاری;
	}
      اگر (literal_zero_نقاب)
	c_parser_check_literal_zero (parser, literal_zero_نقاب, idx + 1);
      اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اگر (convert_p)
	اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ.get_location (), اظہاریہ, سچ,
					 سچ);
      اگر (fold_p)
	اظہاریہ.قدر = c_fully_fold (اظہاریہ.قدر, جھوٹ, تہی);
      vec_محفوظ_ڈالو (ret, اظہاریہ.قدر);
      اگر (orig_types)
	vec_محفوظ_ڈالو (orig_types, اظہاریہ.original_type);
      اگر (locations)
	locations->محفوظ_ڈالو (اظہاریہ.get_location ());
      اگر (++idx < 6
	  && sizeof_arg != تہی
	  && (اظہاریہ.original_رمز == SIZEOF_اظہاریہ
	      || اظہاریہ.original_رمز == PAREN_SIZEOF_اظہاریہ))
	{
	  sizeof_arg[idx] = c_آخری_sizeof_arg;
	  sizeof_arg_loc[idx] = c_آخری_sizeof_loc;
	}
    }
  اگر (orig_types)
    *p_orig_types = orig_types;
  c_omp_array_section_p = save_c_omp_array_section_p;
  واپس ret;
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

ساکن خالی
c_parser_objc_class_definition (c_parser *parser, درخت اوصاف)
{
  منطقی iface_p;
  درخت id1;
  درخت superclass;
  اگر (c_parser_اگلا_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = سچ;
  ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = جھوٹ;
  ورنہ
    gcc_unreachable ();

  c_parser_consume_token (parser);
  اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      واپس;
    }
  id1 = c_parser_peek_token (parser)->قدر;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      درخت id2;
      درخت proto = NULL_درخت;
      matching_parens parens;
      parens.consume_open (parser);
      اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
	{
	  اگر (iface_p && c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_درخت;
	    }
	  ورنہ
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
	      واپس;
	    }
	}
      ورنہ
	{
	  id2 = c_parser_peek_token (parser)->قدر;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_ملا_close (parser);
      اگر (!iface_p)
	{
	  objc_آغاز_category_implementation (id1, id2);
	  واپس;
	}
      اگر (c_parser_اگلا_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_آغاز_category_interface (id1, id2, proto, اوصاف);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_انتہا, "expected %<@end%>");
      objc_اختتام_interface ();
      واپس;
    }
  اگر (c_parser_اگلا_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  واپس;
	}
      superclass = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
    }
  ورنہ
    superclass = NULL_درخت;
  اگر (iface_p)
    {
      درخت proto = NULL_درخت;
      اگر (c_parser_اگلا_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_آغاز_class_interface (id1, loc1, superclass, proto, اوصاف);
    }
  ورنہ
    objc_آغاز_class_implementation (id1, superclass);
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  اگر (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_انتہا, "expected %<@end%>");
      objc_اختتام_interface ();
    }
  ورنہ
    {
      objc_continue_implementation ();
      واپس;
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

ساکن خالی
c_parser_objc_class_instance_variables (c_parser *parser)
{
  gcc_assert (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  جب (c_parser_اگلا_token_is_not (parser, CPP_EOF))
    {
      درخت decls;
      /* Parse any stray semicolon.  */
      اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  جاری;
	}
      /* Stop if at the end of the instance variables.  */
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  توڑو;
	}
      /* Parse any objc-visibility-spec.  */
      اگر (c_parser_اگلا_token_is_keyword (parser, RID_AT_نجی))
	{
	  c_parser_consume_token (parser);
	  objc_سیٹ_visibility (OBJC_IVAR_VIS_نجی);
	  جاری;
	}
      ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_سیٹ_visibility (OBJC_IVAR_VIS_PROTECTED);
	  جاری;
	}
      ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_AT_عوامی))
	{
	  c_parser_consume_token (parser);
	  objc_سیٹ_visibility (OBJC_IVAR_VIS_عوامی);
	  جاری;
	}
      ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_سیٹ_visibility (OBJC_IVAR_VIS_PACKAGE);
	  جاری;
	}
      ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, تہی, NULL_درخت);
	  جاری;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser, تہی);
      اگر (decls == تہی)
	{
	  /* There is a syntax error.  We want to skip the offending
	     tokens up to the next ';' (included) or '}'
	     (excluded).  */

	  /* First, skip manually a ')' or ']'.  This is because they
	     reduce the nesting level, so c_parser_skip_until_found()
	     wouldn't be able to skip past them.  */
	  c_token *token = c_parser_peek_token (parser);
	  اگر (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_مربع)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_ملا (parser, CPP_SEMICOLON, تہی);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = جھوٹ;
	  جاری;
	}
      ورنہ
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  درخت ivar = nreverse (decls);
	  برائے (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_جوڑو_instance_variable (copy_گرہ (ivar));
	}
      c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}

/* Parse an objc-class-declaration.

   objc-class-declaration:
     @class identifier-list ;
*/

ساکن خالی
c_parser_objc_class_declaration (c_parser *parser)
{
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_AT_CLASS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  جب (سچ)
    {
      درخت id;
      اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_ملا (parser, CPP_SEMICOLON, تہی);
	  parser->error = جھوٹ;
	  واپس;
	}
      id = c_parser_peek_token (parser)->قدر;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ورنہ
	توڑو;
    }
  c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse an objc-alias-declaration.

   objc-alias-declaration:
     @compatibility_alias identifier identifier ;
*/

ساکن خالی
c_parser_objc_alias_declaration (c_parser *parser)
{
  درخت id1, id2;
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_ملا (parser, CPP_SEMICOLON, تہی);
      واپس;
    }
  id1 = c_parser_peek_token (parser)->قدر;
  c_parser_consume_token (parser);
  اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_ملا (parser, CPP_SEMICOLON, تہی);
      واپس;
    }
  id2 = c_parser_peek_token (parser)->قدر;
  c_parser_consume_token (parser);
  c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
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

ساکن خالی
c_parser_objc_protocol_definition (c_parser *parser, درخت اوصاف)
{
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      واپس;
    }
  اگر (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      جب (سچ)
	{
	  درخت id;
	  اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      توڑو;
	    }
	  id = c_parser_peek_token (parser)->قدر;
	  objc_declare_protocol (id, اوصاف);
	  c_parser_consume_token (parser);
	  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ورنہ
	    توڑو;
	}
      c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  ورنہ
    {
      درخت id = c_parser_peek_token (parser)->قدر;
      درخت proto = NULL_درخت;
      c_parser_consume_token (parser);
      اگر (c_parser_اگلا_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = سچ;
      objc_آغاز_protocol (id, proto, اوصاف);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_انتہا, "expected %<@end%>");
      parser->objc_pq_context = جھوٹ;
      objc_اختتام_interface ();
    }
}

/* Parse an objc-method-type.

   objc-method-type:
     +
     -

   Return true if it is a class method (+) and false if it is
   an instance method (-).
*/
ساکن اندرونی منطقی
c_parser_objc_طریقہ_type (c_parser *parser)
{
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_PLUS:
      c_parser_consume_token (parser);
      واپس سچ;
    حالت CPP_MINUS:
      c_parser_consume_token (parser);
      واپس جھوٹ;
    طےشدہ:
      gcc_unreachable ();
    }
}

/* Parse an objc-method-definition.

   objc-method-definition:
     objc-method-type objc-method-decl ;[opt] compound-statement
*/

ساکن خالی
c_parser_objc_طریقہ_definition (c_parser *parser)
{
  منطقی is_class_طریقہ = c_parser_objc_طریقہ_type (parser);
  درخت decl, اوصاف = NULL_درخت, اظہاریہ = NULL_درخت;
  parser->objc_pq_context = سچ;
  decl = c_parser_objc_طریقہ_decl (parser, is_class_طریقہ, &اوصاف,
				    &اظہاریہ);
  اگر (decl == error_mark_گرہ)
    واپس;  /* Bail here. */

  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  اگر (!c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      واپس;
    }

  parser->objc_pq_context = جھوٹ;
  اگر (objc_آغاز_طریقہ_definition (is_class_طریقہ, decl, اوصاف, اظہاریہ))
    {
      جوڑو_stmt (c_parser_compound_statement (parser));
      objc_اختتام_طریقہ_definition (current_function_decl);
    }
  ورنہ
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
خالی_خانے
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

ساکن خالی
c_parser_objc_methodprotolist (c_parser *parser)
{
  جب (سچ)
    {
      /* The list is terminated by @end.  */
      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_SEMICOLON:
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  توڑو;
	حالت CPP_PLUS:
	حالت CPP_MINUS:
	  c_parser_objc_methodproto (parser);
	  توڑو;
	حالت CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external, تہی, NULL_درخت);
	  توڑو;
	حالت CPP_EOF:
	  واپس;
	طےشدہ:
	  اگر (c_parser_اگلا_token_is_keyword (parser, RID_AT_انتہا))
	    واپس;
	  ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_سیٹ_طریقہ_opt (سچ);
	      c_parser_consume_token (parser);
	    }
	  ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_سیٹ_طریقہ_opt (جھوٹ);
	      c_parser_consume_token (parser);
	    }
	  ورنہ
	    c_parser_declaration_or_fndef (parser, جھوٹ, جھوٹ, سچ,
					   جھوٹ, سچ, جھوٹ);
	  توڑو;
	}
    }
}

/* Parse an objc-methodproto.

   objc-methodproto:
     objc-method-type objc-method-decl ;
*/

ساکن خالی
c_parser_objc_methodproto (c_parser *parser)
{
  منطقی is_class_طریقہ = c_parser_objc_طریقہ_type (parser);
  درخت decl, اوصاف = NULL_درخت;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = سچ;
  decl = c_parser_objc_طریقہ_decl (parser, is_class_طریقہ, &اوصاف,
				    تہی);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = جھوٹ;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  اگر (!c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      واپس;
    }

  اگر (decl != error_mark_گرہ)
    objc_جوڑو_طریقہ_declaration (is_class_طریقہ, decl, اوصاف);

  c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

ساکن منطقی
c_parser_objc_maybe_طریقہ_اوصاف (c_parser* parser, درخت* اوصاف)
{
  منطقی bad = جھوٹ;
  اگر (*اوصاف)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *اوصاف = NULL_درخت;
      bad = سچ;
    }

  اگر (c_parser_اگلا_token_is_keyword (parser, RID_ATTRIBUTE))
    *اوصاف = c_parser_gnu_اوصاف (parser);

  /* If there were no attributes here, just report any earlier error.  */
  اگر (*اوصاف == NULL_درخت || bad)
    واپس bad;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON)
      || c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
    واپس bad;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  واپس سچ;
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
خالی_خانے
     objc-opt-parms , parameter-declaration

   objc-optellipsis:
خالی_خانے
     , ...
*/

ساکن درخت
c_parser_objc_طریقہ_decl (c_parser *parser, منطقی is_class_طریقہ,
			   درخت *اوصاف, درخت *اظہاریہ)
{
  درخت type = NULL_درخت;
  درخت sel;
  درخت parms = NULL_درخت;
  منطقی ellipsis = جھوٹ;
  منطقی attr_err = جھوٹ;

  *اوصاف = NULL_درخت;
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      type = c_parser_objc_type_name (parser);
      parens.skip_until_ملا_close (parser);
    }
  sel = c_parser_objc_selector (parser);
  /* If there is no selector, or a colon follows, we have an
     objc-keyword-selector.  If there is a selector, and a colon does
     not follow, that selector ends the objc-method-decl.  */
  اگر (!sel || c_parser_اگلا_token_is (parser, CPP_COLON))
    {
      درخت tsel = sel;
      درخت list = NULL_درخت;
      جب (سچ)
	{
	  درخت atype = NULL_درخت, id, keyworddecl;
	  درخت param_attr = NULL_درخت;
	  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    توڑو;
	  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  اگر (c_parser_اگلا_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_اوصاف (parser);
	  اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      واپس error_mark_گرہ;
	    }
	  id = c_parser_peek_token (parser)->قدر;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  اگر (!tsel && c_parser_اگلا_token_is_not (parser, CPP_COLON))
	    توڑو;
	}

      attr_err |= c_parser_objc_maybe_طریقہ_اوصاف (parser, اوصاف) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_گرہ (درخت_LIST);
      جب (c_parser_اگلا_token_is (parser, CPP_COMMA))
	{
	  ساخت c_parm *parm;
	  c_parser_consume_token (parser);
	  اگر (c_parser_اگلا_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = سچ;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_طریقہ_اوصاف
						(parser, اوصاف) ;
	      توڑو;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_درخت, جھوٹ);
	  اگر (parm == تہی)
	    توڑو;
	  parms = chainon (parms,
			   build_درخت_list (NULL_درخت, grokparm (parm, اظہاریہ)));
	}
      sel = list;
    }
  ورنہ
    attr_err |= c_parser_objc_maybe_طریقہ_اوصاف (parser, اوصاف) ;

  اگر (sel == تہی)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      واپس error_mark_گرہ;
    }

  اگر (attr_err)
    واپس error_mark_گرہ;

  واپس objc_build_طریقہ_signature (is_class_طریقہ, type, sel, parms, ellipsis);
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

ساکن درخت
c_parser_objc_type_name (c_parser *parser)
{
  درخت quals = NULL_درخت;
  ساخت c_type_name *type_name = تہی;
  درخت type = NULL_درخت;
  جب (سچ)
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (token->type == CPP_KEYWORD
	  && (token->keyword == RID_اندر
	      || token->keyword == RID_برآمد
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_درخت_list (NULL_درخت, token->قدر), quals);
	  c_parser_consume_token (parser);
	}
      ورنہ
	توڑو;
    }
  اگر (c_parser_اگلا_علامات_آغاز_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  اگر (type_name)
    type = groktypename (type_name, تہی, تہی);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  اگر (type == error_mark_گرہ)
    type = NULL_درخت;

  واپس build_درخت_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

ساکن درخت
c_parser_objc_protocol_refs (c_parser *parser)
{
  درخت list = NULL_درخت;
  gcc_assert (c_parser_اگلا_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  جب (سچ)
    {
      درخت id;
      اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  توڑو;
	}
      id = c_parser_peek_token (parser)->قدر;
      list = chainon (list, build_درخت_list (NULL_درخت, id));
      c_parser_consume_token (parser);
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ورنہ
	توڑو;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  واپس list;
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

ساکن خالی
c_parser_objc_try_catch_finally_statement (c_parser *parser)
{
  location_t location;
  درخت stmt;

  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  جب (c_parser_اگلا_token_is_keyword (parser, RID_AT_CATCH))
    {
      ساخت c_parm *parm;
      درخت parameter_declaration = error_mark_گرہ;
      منطقی نظر_آیا_open_paren = جھوٹ;

      c_parser_consume_token (parser);
      matching_parens parens;
      اگر (!parens.require_open (parser))
	نظر_آیا_open_paren = سچ;
      اگر (c_parser_اگلا_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_درخت;
	}
      ورنہ
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_درخت, جھوٹ);
	  اگر (parm == تہی)
	    parameter_declaration = error_mark_گرہ;
	  ورنہ
	    parameter_declaration = grokparm (parm, تہی);
	}
      اگر (نظر_آیا_open_paren)
	parens.require_close (parser);
      ورنہ
	{
	  /* If there was no open parenthesis, we are recovering from
	     an error, and we are trying to figure out what mistake
	     the user has made.  */

	  /* If there is an immediate closing parenthesis, the user
	     probably forgot the opening one (ie, they typed "@catch
	     NSException *e)".  Parse the closing parenthesis and keep
	     going.  */
	  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      اگر (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_اختتام_catch_clause ();
    }
  اگر (c_parser_اگلا_token_is_keyword (parser, RID_AT_FINALLY))
    {
      c_parser_consume_token (parser);
      location = c_parser_peek_token (parser)->location;
      stmt = c_parser_compound_statement (parser);
      objc_build_finally_clause (location, stmt);
    }
  objc_اختتام_try_stmt ();
}

/* Parse an objc-synchronized-statement.

   objc-synchronized-statement:
     @synchronized ( expression ) compound-statement
*/

ساکن خالی
c_parser_objc_synchronized_statement (c_parser *parser)
{
  location_t loc;
  درخت اظہاریہ, stmt;
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      ساخت c_اظہاریہ ce = c_parser_عبارت (parser);
      ce = convert_lvalue_مقصد_rvalue (loc, ce, جھوٹ, جھوٹ);
      اظہاریہ = ce.قدر;
      اظہاریہ = c_fully_fold (اظہاریہ, جھوٹ, تہی);
      parens.skip_until_ملا_close (parser);
    }
  ورنہ
    اظہاریہ = error_mark_گرہ;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, اظہاریہ, stmt);
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

ساکن درخت
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  درخت قدر = token->قدر;
  اگر (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      واپس قدر;
    }
  اگر (token->type != CPP_KEYWORD)
    واپس NULL_درخت;
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
    حالت RID_اندر:
    حالت RID_برآمد:
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
      واپس قدر;
    طےشدہ:
      واپس NULL_درخت;
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

ساکن درخت
c_parser_objc_selector_arg (c_parser *parser)
{
  درخت sel = c_parser_objc_selector (parser);
  درخت list = NULL_درخت;
  اگر (sel
      && c_parser_اگلا_token_is_not (parser, CPP_COLON)
      && c_parser_اگلا_token_is_not (parser, CPP_SCOPE))
    واپس sel;
  جب (سچ)
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_درخت_list (sel, NULL_درخت));
	  list = chainon (list, build_درخت_list (NULL_درخت, NULL_درخت));
	}
      ورنہ
	{
	  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    واپس list;
	  list = chainon (list, build_درخت_list (sel, NULL_درخت));
	}
      sel = c_parser_objc_selector (parser);
      اگر (!sel
	  && c_parser_اگلا_token_is_not (parser, CPP_COLON)
	  && c_parser_اگلا_token_is_not (parser, CPP_SCOPE))
	توڑو;
    }
  واپس list;
}

/* Parse an objc-receiver.

   objc-receiver:
عبارت
     class-name
     type-name
*/

ساکن درخت
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  اگر (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_قسم == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_قسم == C_ID_CLASSNAME))
    {
      درخت id = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
      واپس objc_get_class_reference (id);
    }
  ساخت c_اظہاریہ ce = c_parser_عبارت (parser);
  ce = convert_lvalue_مقصد_rvalue (loc, ce, جھوٹ, جھوٹ);
  واپس c_fully_fold (ce.قدر, جھوٹ, تہی);
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

ساکن درخت
c_parser_objc_پیغام_دلائل (c_parser *parser)
{
  درخت sel = c_parser_objc_selector (parser);
  درخت list = NULL_درخت;
  اگر (sel && c_parser_اگلا_token_is_not (parser, CPP_COLON))
    واپس sel;
  جب (سچ)
    {
      درخت keywordexpr;
      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	واپس error_mark_گرہ;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_درخت_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      اگر (!sel && c_parser_اگلا_token_is_not (parser, CPP_COLON))
	توڑو;
    }
  واپس list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

ساکن درخت
c_parser_objc_keywordexpr (c_parser *parser)
{
  درخت ret;
  vec<درخت, va_gc> *اظہاریہ_list = c_parser_اظہاریہ_list (parser, سچ, سچ,
						تہی, تہی, تہی, تہی);
  اگر (vec_محفوظ_لمبائی (اظہاریہ_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*اظہاریہ_list)[0];
    }
  ورنہ
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_درخت_list_vec (اظہاریہ_list);
    }
  release_درخت_سمتیہ (اظہاریہ_list);
  واپس ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
ساکن منطقی
c_parser_objc_diagnose_bad_element_سابقہ (c_parser *parser,
					   ساخت c_declspecs *specs)
{
  اگر (!specs->declspecs_نظر_آیا_p || specs->non_sc_نظر_آیا_p
      || specs->typespec_قسم != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
      واپس سچ;
    }
  واپس جھوٹ;
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
ساکن خالی
c_parser_objc_at_property_declaration (c_parser *parser)
{
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_AT_PROPERTY));
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);  /* Eat '@property'.  */

  /* Parse the optional attribute list.

     A list of parsed, but not verified, attributes.  */
  vec<property_attribute_info *> prop_attr_list = vNULL;

  منطقی syntax_error = جھوٹ;
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_آغاز = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = سچ;

      /* Allow @property (), with a warning.  */
      location_t attr_انتہا = c_parser_peek_token (parser)->location;

      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_انتہا, attr_آغاز, attr_انتہا);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      ورنہ
	جب (سچ)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_آغاز = token->location;
	    attr_انتہا = get_اختتام (token->location);
	    location_t attr_comb = make_location (attr_آغاز, attr_آغاز,
						  attr_انتہا);

	    اگر (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		اگر (token->type == CPP_CLOSE_PAREN)
		  توڑو;
		c_parser_consume_token (parser);
		جاری;
	      }

	    درخت attr_name = NULL_درخت;
	    شمار rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    منطقی جوڑو_at = جھوٹ;
	    اگر (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		اگر (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->قدر;
		    جوڑو_at = سچ;
		  }
		ورنہ
		  attr_name = ridpointers[(صحیح)keyword];
	      }
	    ورنہ اگر (token->type == CPP_NAME)
	      attr_name = token->قدر;
	    c_parser_consume_token (parser);

	    شمار objc_property_attribute_قسم prop_قسم
	      = objc_prop_attr_قسم_for_rid (keyword);
	    property_attribute_info *prop
	      = نیا property_attribute_info (attr_name, attr_comb, prop_قسم);
	    prop_attr_list.محفوظ_ڈالو (prop);

	    درخت meth_name;
	    انتخاب (prop->prop_قسم)
	      {
	      طےشدہ: توڑو;
	      حالت OBJC_PROPERTY_ATTR_UNKNOWN:
		اگر (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    جوڑو_at ? "@" : "", IDENTIFIER_اشارہ_گر (attr_name));
		ورنہ
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = سچ;
		توڑو;

	      حالت OBJC_PROPERTY_ATTR_GETTER:
	      حالت OBJC_PROPERTY_ATTR_SETTER:
		اگر (c_parser_اگلا_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_انتہا, attr_آغاز, attr_انتہا);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = سچ;
		    توڑو;
		  }
		token = c_parser_peek_token (parser);
		attr_انتہا = token->location;
		c_parser_consume_token (parser); /* eat the = */
		اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_انتہا, attr_آغاز, attr_انتہا);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = سچ;
		    توڑو;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_انتہا = get_اختتام (token->location);
		meth_name = token->قدر;
		c_parser_consume_token (parser);
		اگر (prop->prop_قسم == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    اگر (c_parser_اگلا_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_انتہا, attr_آغاز,
						   attr_انتہا);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = سچ;
		      }
		    ورنہ
		      {
			attr_انتہا = get_اختتام (c_parser_peek_token
					       (parser)->location);
			c_parser_consume_token (parser);
		      }
		    attr_comb = make_location (attr_آغاز, attr_آغاز,
					       attr_انتہا);
		  }
		ورنہ
		  attr_comb = make_location (attr_آغاز, attr_آغاز,
					       attr_انتہا);
		prop->ident = meth_name;
		/* Updated location including all that was successfully
		   parsed.  */
		prop->prop_loc = attr_comb;
		توڑو;
	    }

	  /* If we see a comma here, then keep going - even if we already
	     saw a syntax error.  For simple mistakes e.g. (assign, getter=x)
	     this makes a more useful output and avoid spurious warnings about
	     missing attributes that are, in fact, specified after the one with
	     the syntax error.  */
	  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ورنہ
	    توڑو;
	}
      parser->objc_property_attr_context = جھوٹ;

      اگر (syntax_error && c_parser_اگلا_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      ورنہ
	syntax_error = جھوٹ, parens.skip_until_ملا_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  درخت properties = c_parser_struct_declaration (parser, تہی);

  اگر (properties == error_mark_گرہ)
    c_parser_skip_until_ملا (parser, CPP_SEMICOLON, تہی);
  ورنہ
    {
      اگر (properties == NULL_درخت)
	c_parser_error (parser, "expected identifier");
      ورنہ
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  برائے (; properties; properties = درخت_CHAIN (properties))
	    objc_جوڑو_property_declaration (loc, copy_گرہ (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  جب (!prop_attr_list.is_خالی_خانے())
    حذف prop_attr_list.نکالو ();
  prop_attr_list.release ();
  parser->error = جھوٹ;
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
ساکن خالی
c_parser_objc_at_synthesize_declaration (c_parser *parser)
{
  درخت list = NULL_درخت;
  location_t loc;
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  جب (سچ)
    {
      درخت property, ivar;
      اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_ملا (parser, CPP_SEMICOLON, تہی);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = جھوٹ;
	  واپس;
	}
      property = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
      اگر (c_parser_اگلا_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_ملا (parser, CPP_SEMICOLON, تہی);
	      parser->error = جھوٹ;
	      واپس;
	    }
	  ivar = c_parser_peek_token (parser)->قدر;
	  c_parser_consume_token (parser);
	}
      ورنہ
	ivar = NULL_درخت;
      list = chainon (list, build_درخت_list (ivar, property));
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ورنہ
	توڑو;
    }
  c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_جوڑو_synthesize_declaration (loc, list);
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
ساکن خالی
c_parser_objc_at_dynamic_declaration (c_parser *parser)
{
  درخت list = NULL_درخت;
  location_t loc;
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  جب (سچ)
    {
      درخت property;
      اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_ملا (parser, CPP_SEMICOLON, تہی);
	  parser->error = جھوٹ;
	  واپس;
	}
      property = c_parser_peek_token (parser)->قدر;
      list = chainon (list, build_درخت_list (NULL_درخت, property));
      c_parser_consume_token (parser);
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ورنہ
	توڑو;
    }
  c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_جوڑو_dynamic_declaration (loc, list);
}


/* Parse a pragma GCC ivdep.  */

ساکن منطقی
c_parse_pragma_ivdep (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_مقصد_pragma_eol (parser);
  واپس سچ;
}

/* Parse a pragma GCC novector.  */

ساکن منطقی
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_مقصد_pragma_eol (parser);
  واپس سچ;
}

/* Parse a pragma GCC unroll.  */

ساکن غیرعلامتی مختصر
c_parser_pragma_unroll (c_parser *parser)
{
  غیرعلامتی مختصر unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  درخت اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی).قدر;
  mark_exp_read (اظہاریہ);
  اظہاریہ = c_fully_fold (اظہاریہ, جھوٹ, تہی);
  HOST_WIDE_INT lunroll = 0;
  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (اظہاریہ))
      || درخت_رمز (اظہاریہ) != INTEGER_CST
      || (lunroll = درخت_مقصد_shwi (اظہاریہ)) < 0
      || lunroll >= USHRT_MAX)
    {
      error_at (location, "%<#pragma GCC unroll%> requires an"
		" assignment-expression that evaluates to a non-negative"
		" integral constant less than %u", USHRT_MAX);
      unroll = 0;
    }
  ورنہ
    {
      unroll = (غیرعلامتی مختصر)lunroll;
      اگر (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_مقصد_pragma_eol (parser);
  واپس unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

ساکن منطقی
c_parser_pragma (c_parser *parser, شمار pragma_context context, منطقی *if_p,
		 درخت before_labels)
{
  غیرعلامتی صحیح id;
  ثابت حرف *construct = تہی;

  داخلہ_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_قسم;
  gcc_assert (id != PRAGMA_NONE);
  اگر (parser->omp_for_parse_state
      && parser->omp_for_parse_state->اندر_intervening_رمز
      && id >= PRAGMA_OMP_آغاز && id <= PRAGMA_OMP_آخری
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	داخلہ_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->fail = سچ;
      c_parser_skip_until_ملا (parser, CPP_PRAGMA_EOL, تہی);
      واپس جھوٹ;
    }

  انتخاب (id)
    {
    حالت PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      واپس جھوٹ;

    حالت PRAGMA_OACC_ENTER_ڈیٹا:
      اگر (context != pragma_compound)
	{
	  construct = "acc enter data";
	اندر_compound:
	  اگر (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_ملا (parser, CPP_PRAGMA_EOL, تہی);
	      واپس سچ;
	    }
	  جاؤ bad_stmt;
	}
      c_parser_oacc_enter_exit_ڈیٹا (parser, سچ);
      واپس جھوٹ;

    حالت PRAGMA_OACC_EXIT_ڈیٹا:
      اگر (context != pragma_compound)
	{
	  construct = "acc exit data";
	  جاؤ اندر_compound;
	}
      c_parser_oacc_enter_exit_ڈیٹا (parser, جھوٹ);
      واپس جھوٹ;

    حالت PRAGMA_OACC_ROUTINE:
      اگر (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_ملا (parser, CPP_PRAGMA_EOL, تہی);
	  واپس جھوٹ;
	}
      c_parser_oacc_routine (parser, context);
      واپس جھوٹ;

    حالت PRAGMA_OACC_UPDATE:
      اگر (context != pragma_compound)
	{
	  construct = "acc update";
	  جاؤ اندر_compound;
	}
      c_parser_oacc_update (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_BARRIER:
      اگر (context != pragma_compound)
	{
	  construct = "omp barrier";
	  جاؤ اندر_compound;
	}
      c_parser_omp_barrier (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_DEPOBJ:
      اگر (context != pragma_compound)
	{
	  construct = "omp depobj";
	  جاؤ اندر_compound;
	}
      c_parser_omp_depobj (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_FLUSH:
      اگر (context != pragma_compound)
	{
	  construct = "omp flush";
	  جاؤ اندر_compound;
	}
      c_parser_omp_flush (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_INTEROP:
      اگر (context != pragma_compound)
	{
	  construct = "omp interop";
	  جاؤ اندر_compound;
	}
      c_parser_omp_interop (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_TASKWAIT:
      اگر (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  جاؤ اندر_compound;
	}
      c_parser_omp_taskwait (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_TASKYIELD:
      اگر (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  جاؤ اندر_compound;
	}
      c_parser_omp_taskyield (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_CANCEL:
      اگر (context != pragma_compound)
	{
	  construct = "omp cancel";
	  جاؤ اندر_compound;
	}
      c_parser_omp_cancel (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_CANCELLATION_نقطہ:
      واپس c_parser_omp_cancellation_نقطہ (parser, context);

    حالت PRAGMA_OMP_GROUPPRIVATE:
      c_parser_omp_groupprivate (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_THREADPRIVATE:
      c_parser_omp_threadprivate (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_ہدف:
      واپس c_parser_omp_ہدف (parser, context, if_p);

    حالت PRAGMA_OMP_BEGIN:
      c_parser_omp_begin (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_انتہا:
      c_parser_omp_انتہا (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_جائزہ:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_ملا (parser, CPP_PRAGMA_EOL, تہی);
      واپس جھوٹ;

    حالت PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_ملا (parser, CPP_PRAGMA_EOL, تہی);
      واپس جھوٹ;

    حالت PRAGMA_OMP_DECLARE:
      واپس c_parser_omp_declare (parser, context);

    حالت PRAGMA_OMP_REQUIRES:
      اگر (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_ملا (parser, CPP_PRAGMA_EOL, تہی);
	  واپس جھوٹ;
	}
      c_parser_omp_requires (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_ALLOCATE:
      c_parser_omp_allocate (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_ASSUMES:
      اگر (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp assumes");
	  c_parser_skip_until_ملا (parser, CPP_PRAGMA_EOL, تہی);
	  واپس جھوٹ;
	}
      c_parser_omp_assumes (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      واپس جھوٹ;

    حالت PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      واپس سچ;

    حالت PRAGMA_OMP_ERROR:
      واپس c_parser_omp_error (parser, context);

    حالت PRAGMA_OMP_ORDERED:
      واپس c_parser_omp_ordered (parser, context, if_p);

    حالت PRAGMA_NOVECTOR:
    حالت PRAGMA_UNROLL:
    حالت PRAGMA_IVDEP:
      {
	منطقی novector = جھوٹ;
	غیرعلامتی مختصر unroll = 0;
	منطقی ivdep = جھوٹ;

	انتخاب (id)
	  {
	  حالت PRAGMA_NOVECTOR:
	    novector = c_parse_pragma_novector (parser);
	    توڑو;
	  حالت PRAGMA_UNROLL:
	    unroll = c_parser_pragma_unroll (parser);
	    توڑو;
	  حالت PRAGMA_IVDEP:
	    ivdep = c_parse_pragma_ivdep (parser);
	    توڑو;
	  طےشدہ:
	    gcc_unreachable ();
	  }

	c_token *tok = c_parser_peek_token (parser);
	منطقی has_مزید = tok->type == CPP_PRAGMA;
	جب (has_مزید)
	  {
	    انتخاب (tok->pragma_قسم)
	      {
	      حالت PRAGMA_IVDEP:
		ivdep = c_parse_pragma_ivdep (parser);
		توڑو;
	      حالت PRAGMA_UNROLL:
		unroll = c_parser_pragma_unroll (parser);
		توڑو;
	      حالت PRAGMA_NOVECTOR:
		novector = c_parse_pragma_novector (parser);
		توڑو;
	      طےشدہ:
		has_مزید = جھوٹ;
		توڑو;
	      }
	    tok = c_parser_peek_token (parser);
	    has_مزید = has_مزید && tok->type == CPP_PRAGMA;
	  }
	اگر (!c_parser_اگلا_token_is_keyword (parser, RID_FOR)
	    && !c_parser_اگلا_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_اگلا_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    واپس جھوٹ;
	  }
	اگر (c_parser_اگلا_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	ورنہ
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      واپس سچ;

    حالت PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_ملا (parser, CPP_PRAGMA_EOL, تہی);
      واپس جھوٹ;

    حالت PRAGMA_OACC_WAIT:
      اگر (context != pragma_compound)
	{
	  construct = "acc wait";
	  جاؤ اندر_compound;
	}
	/* FALL THROUGH.  */

    طےشدہ:
      اگر (id < PRAGMA_پہلا_EXTERNAL)
	{
	  اگر (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_ملا (parser, CPP_PRAGMA_EOL, تہی);
	      واپس جھوٹ;
	    }
	  c_parser_omp_construct (parser, if_p);
	  واپس سچ;
	}
      توڑو;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = سچ;
  c_parser_skip_مقصد_pragma_eol (parser);

  واپس جھوٹ;
}

/* The interface the pragma parsers have to the lexer.  */

شمار cpp_ttype
pragma_lex (درخت *قدر, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  شمار cpp_ttype ret = tok->type;

  *قدر = tok->قدر;
  اگر (loc)
    *loc = tok->location;

  اگر (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  ورنہ اگر (ret == CPP_STRING)
    *قدر = c_parser_string_literal (the_parser, جھوٹ, جھوٹ).قدر;
  ورنہ
    {
      اگر (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  واپس ret;
}

خالی
pragma_lex_discard_مقصد_eol ()
{
  cpp_ttype type;
  کرو
    {
      type = c_parser_peek_token (the_parser)->type;
      gcc_assert (type != CPP_EOF);
      c_parser_consume_token (the_parser);
    } جب (type != CPP_PRAGMA_EOL);
}

ساکن خالی
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  درخت name = تہی;

  parser->lex_joined_string = سچ;
  c_parser_consume_pragma (parser);
  اگر (c_parser_اگلا_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
    }
  ورنہ
    c_parser_error (parser, "expected string literal");
  c_parser_skip_مقصد_pragma_eol (parser);
  parser->lex_joined_string = جھوٹ;

  اگر (name)
    c_common_pch_pragma (parse_اندر, درخت_STRING_اشارہ_گر (name));
}

/* OpenACC and OpenMP parsing routines.  */

/* Returns name of the next clause.
   If the clause is not recognized PRAGMA_OMP_CLAUSE_NONE is returned and
   the token is not consumed.  Otherwise appropriate pragma_omp_clause is
   returned and the token is consumed.  */

ساکن pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause نتیجہ = PRAGMA_OMP_CLAUSE_NONE;

  اگر (c_parser_اگلا_token_is_keyword (parser, RID_AUTO))
    نتیجہ = PRAGMA_OACC_CLAUSE_AUTO;
  ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_IF))
    نتیجہ = PRAGMA_OMP_CLAUSE_IF;
  ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_DEFAULT))
    نتیجہ = PRAGMA_OMP_CLAUSE_DEFAULT;
  ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_FOR))
    نتیجہ = PRAGMA_OMP_CLAUSE_FOR;
  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);

      انتخاب (p[0])
	{
	حالت 'a':
	  اگر (!strcmp ("affinity", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_AFFINITY;
	  ورنہ اگر (!strcmp ("aligned", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_ALIGNED;
	  ورنہ اگر (!strcmp ("allocate", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  ورنہ اگر (!strcmp ("async", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_ASYNC;
	  ورنہ اگر (!strcmp ("attach", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_ATTACH;
	  توڑو;
	حالت 'b':
	  اگر (!strcmp ("bind", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_BIND;
	  توڑو;
	حالت 'c':
	  اگر (!strcmp ("collapse", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  ورنہ اگر (!strcmp ("copy", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_COPY;
	  ورنہ اگر (!strcmp ("copyin", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_COPYIN;
	  ورنہ اگر (!strcmp ("copyout", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_COPYOUT;
          ورنہ اگر (!strcmp ("copyprivate", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  ورنہ اگر (!strcmp ("create", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_CREATE;
	  توڑو;
	حالت 'd':
	  اگر (!strcmp ("defaultmap", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  ورنہ اگر (!strcmp ("delete", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_DELETE;
	  ورنہ اگر (!strcmp ("depend", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_DEPEND;
	  ورنہ اگر (!strcmp ("destroy", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_DESTROY;
	  ورنہ اگر (!strcmp ("detach", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_DETACH;
	  ورنہ اگر (!strcmp ("device", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_DEVICE;
	  ورنہ اگر (!strcmp ("deviceptr", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  ورنہ اگر (!strcmp ("device_resident", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  ورنہ اگر (!strcmp ("device_type", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  ورنہ اگر (!strcmp ("dist_schedule", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_DIST_جدول_وقت;
	  ورنہ اگر (!strcmp ("doacross", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_DOACROSS;
	  ورنہ اگر (!strcmp ("dyn_groupprivate", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  توڑو;
	حالت 'e':
	  اگر (!strcmp ("enter", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_ENTER;
	  توڑو;
	حالت 'f':
	  اگر (!strcmp ("filter", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_FILTER;
	  ورنہ اگر (!strcmp ("final", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_FINAL;
	  ورنہ اگر (!strcmp ("finalize", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_FINALIZE;
	  ورنہ اگر (!strcmp ("firstprivate", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  ورنہ اگر (!strcmp ("from", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_FROM;
	  ورنہ اگر (!strcmp ("full", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_بھرا;
	  توڑو;
	حالت 'g':
	  اگر (!strcmp ("gang", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_GANG;
	  ورنہ اگر (!strcmp ("grainsize", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  توڑو;
	حالت 'h':
	  اگر (!strcmp ("has_device_addr", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  ورنہ اگر (!strcmp ("hint", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_HINT;
	  ورنہ اگر (!strcmp ("host", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_HOST;
	  توڑو;
	حالت 'i':
	  اگر (!strcmp ("if_present", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  ورنہ اگر (!strcmp ("in_reduction", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_اندر_REDUCTION;
	  ورنہ اگر (!strcmp ("inbranch", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_INBRANCH;
	  ورنہ اگر (!strcmp ("independent", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  ورنہ اگر (!strcmp ("indirect", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_بالواسطہ;
	  ورنہ اگر (!strcmp ("init", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_INIT;
	  ورنہ اگر (!strcmp ("is_device_ptr", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  ورنہ اگر (!strcmp ("interop", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_INTEROP;
	  توڑو;
	حالت 'l':
	  اگر (!strcmp ("lastprivate", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  ورنہ اگر (!strcmp ("linear", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_خطی;
	  ورنہ اگر (!strcmp ("link", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_LINK;
	  ورنہ اگر (!strcmp ("local", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_LOCAL;
	  توڑو;
	حالت 'm':
	  اگر (!strcmp ("map", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_MAP;
	  ورنہ اگر (!strcmp ("mergeable", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  توڑو;
	حالت 'n':
	  اگر (!strcmp ("no_create", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  ورنہ اگر (!strcmp ("nocontext", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  ورنہ اگر (!strcmp ("nogroup", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_NOGROUP;
	  ورنہ اگر (!strcmp ("nohost", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_NOHOST;
	  ورنہ اگر (!strcmp ("nontemporal", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  ورنہ اگر (!strcmp ("notinbranch", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  ورنہ اگر (!strcmp ("novariants", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  ورنہ اگر (!strcmp ("nowait", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_NOWAIT;
	  ورنہ اگر (!strcmp ("num_gangs", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_عدد_GANGS;
	  ورنہ اگر (!strcmp ("num_tasks", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_عدد_TASKS;
	  ورنہ اگر (!strcmp ("num_teams", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_عدد_TEAMS;
	  ورنہ اگر (!strcmp ("num_threads", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_عدد_دھاگے;
	  ورنہ اگر (!strcmp ("num_workers", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_عدد_WORKERS;
	  توڑو;
	حالت 'o':
	  اگر (!strcmp ("ordered", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_ORDERED;
	  ورنہ اگر (!strcmp ("order", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_ترتیب;
	  توڑو;
	حالت 'p':
	  اگر (!strcmp ("parallel", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_PARALLEL;
	  ورنہ اگر (!strcmp ("partial", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_PARTIAL;
	  ورنہ اگر (!strcmp ("present", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  ورنہ اگر (!strcmp ("present_or_copy", p)
		   || !strcmp ("pcopy", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_COPY;
	  ورنہ اگر (!strcmp ("present_or_copyin", p)
		   || !strcmp ("pcopyin", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_COPYIN;
	  ورنہ اگر (!strcmp ("present_or_copyout", p)
		   || !strcmp ("pcopyout", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_COPYOUT;
	  ورنہ اگر (!strcmp ("present_or_create", p)
		   || !strcmp ("pcreate", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_CREATE;
	  ورنہ اگر (!strcmp ("priority", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_ترجیح;
	  ورنہ اگر (!strcmp ("private", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_نجی;
	  ورنہ اگر (!strcmp ("proc_bind", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  توڑو;
	حالت 'r':
	  اگر (!strcmp ("reduction", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_REDUCTION;
	  توڑو;
	حالت 's':
	  اگر (!strcmp ("safelen", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_SAFELEN;
	  ورنہ اگر (!strcmp ("schedule", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_جدول_وقت;
	  ورنہ اگر (!strcmp ("sections", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_SECTIONS;
	  ورنہ اگر (!strcmp ("self", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_SELF;
	  ورنہ اگر (!strcmp ("seq", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_SEQ;
	  ورنہ اگر (!strcmp ("shared", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_SHARED;
	  ورنہ اگر (!strcmp ("simd", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_SIMD;
	  ورنہ اگر (!strcmp ("simdlen", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  توڑو;
	حالت 't':
	  اگر (!strcmp ("task_reduction", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  ورنہ اگر (!strcmp ("taskgroup", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  ورنہ اگر (!strcmp ("thread_limit", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_THREAD_حد_بندی;
	  ورنہ اگر (!strcmp ("threads", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_دھاگے;
	  ورنہ اگر (!strcmp ("tile", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_TILE;
	  ورنہ اگر (!strcmp ("to", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_مقصد;
	  توڑو;
	حالت 'u':
	  اگر (!strcmp ("uniform", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_یکساں;
	  ورنہ اگر (!strcmp ("untied", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_UNTIED;
	  ورنہ اگر (!strcmp ("use", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_USE;
	  ورنہ اگر (!strcmp ("use_device", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  ورنہ اگر (!strcmp ("use_device_addr", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  ورنہ اگر (!strcmp ("use_device_ptr", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  ورنہ اگر (!strcmp ("uses_allocators", p))
	    نتیجہ = PRAGMA_OMP_CLAUSE_استعمال_کرتا_ALLOCATORS;
	  توڑو;
	حالت 'v':
	  اگر (!strcmp ("vector", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_سمتیہ;
	  ورنہ اگر (!strcmp ("vector_length", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_سمتیہ_لمبائی;
	  توڑو;
	حالت 'w':
	  اگر (!strcmp ("wait", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_WAIT;
	  ورنہ اگر (!strcmp ("worker", p))
	    نتیجہ = PRAGMA_OACC_CLAUSE_کارکن;
	  توڑو;
	}
    }

  اگر (نتیجہ != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  واپس نتیجہ;
}

/* Validate that a clause of the given type does not already exist.  */

ساکن خالی
check_no_duplicate_clause (درخت clauses, شمار omp_clause_رمز رمز,
			   ثابت حرف *name)
{
  اگر (درخت c = omp_ڈھونڈو_clause (clauses, رمز))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

ساکن درخت
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, درخت list)
{
  vec<درخت, va_gc> *دلائل;
  درخت t, دلائل_درخت;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  دلائل = c_parser_اظہاریہ_list (parser, جھوٹ, سچ, تہی, تہی, تہی, تہی);
  دلائل_درخت = build_درخت_list_vec (دلائل);

  برائے (t = دلائل_درخت; t; t = درخت_CHAIN (t))
    {
      درخت targ = درخت_قدر (t);

      اگر (targ != error_mark_گرہ)
	{
	  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_گرہ;
	    }
	  ورنہ
	    {
	      درخت c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_درخت_سمتیہ (دلائل);
  parens.require_close (parser);
  واپس list;
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

ساخت omp_dim
{
  درخت کم_bound, لمبائی;
  location_t loc;
  منطقی no_colon;
  omp_dim (درخت lb, درخت len, location_t lo, منطقی nc)
  : کم_bound (lb), لمبائی (len), loc (lo), no_colon (nc) {}
};

ساکن درخت
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    شمار omp_clause_رمز قسم, درخت list,
			    منطقی map_lvalue = جھوٹ)
{
  auto_vec<omp_dim> dims;
  منطقی array_section_p;
  auto_vec<c_token> علامات;
  غیرعلامتی صحیح علامات_avail = 0;
  c_token *saved_علامات = تہی;

  جب (1)
    {
      درخت t = NULL_درخت;
      location_t tloc = c_parser_peek_token (parser)->location;

      اگر (قسم == OMP_CLAUSE_DEPEND || قسم == OMP_CLAUSE_AFFINITY)
	{
	  اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_قسم != C_ID_ID)
	    {
	      ساخت c_اظہاریہ اظہاریہ;
	      اگر (قسم == OMP_CLAUSE_DEPEND
		  && c_parser_اگلا_token_is_keyword (parser,
						     RID_OMP_ALL_حافظہ)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  اظہاریہ.قدر = ridpointers[RID_OMP_ALL_حافظہ];
		  c_parser_consume_token (parser);
		}
	      ورنہ
		اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	      اگر (اظہاریہ.قدر != error_mark_گرہ)
		{
		  درخت u = build_omp_clause (clause_loc, قسم);
		  OMP_CLAUSE_DECL (u) = اظہاریہ.قدر;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      اگر (c_parser_اگلا_token_is_not (parser, CPP_COMMA))
		توڑو;

	      c_parser_consume_token (parser);
	      جاری;
	    }

	  علامات.truncate (0);
	  غیرعلامتی صحیح nesting_گہرائی = 0;
	  جب (1)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      انتخاب (token->type)
		{
		حالت CPP_EOF:
		حالت CPP_PRAGMA_EOL:
		  توڑو;
		حالت CPP_OPEN_BRACE:
		حالت CPP_OPEN_PAREN:
		حالت CPP_OPEN_مربع:
		  ++nesting_گہرائی;
		  جاؤ جوڑو;
		حالت CPP_CLOSE_BRACE:
		حالت CPP_CLOSE_PAREN:
		حالت CPP_CLOSE_مربع:
		  اگر (nesting_گہرائی-- == 0)
		    توڑو;
		  جاؤ جوڑو;
		حالت CPP_COMMA:
		  اگر (nesting_گہرائی == 0)
		    توڑو;
		  جاؤ جوڑو;
		طےشدہ:
		جوڑو:
		  علامات.محفوظ_ڈالو (*token);
		  c_parser_consume_token (parser);
		  جاری;
		}
	      توڑو;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  memset (&eof_token, 0, حجم (eof_token));
	  eof_token.type = CPP_EOF;
	  علامات.محفوظ_ڈالو (eof_token);
	  علامات.محفوظ_ڈالو (eof_token);

	  saved_علامات = parser->علامات;
	  علامات_avail = parser->علامات_avail;
	  parser->علامات = علامات.پتہ ();
	  parser->علامات_avail = علامات.لمبائی ();
	}
      ورنہ اگر (map_lvalue
	       && (قسم == OMP_CLAUSE_MAP
		   || قسم == OMP_CLAUSE_مقصد
		   || قسم == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  منطقی save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = سچ;
	  c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	  اگر (اظہاریہ.قدر != error_mark_گرہ)
	    mark_exp_read (اظہاریہ.قدر);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  درخت decl = اظہاریہ.قدر;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  اگر (درخت_رمز (decl) == OMP_ARRAY_SECTION)
	    {
	      جب (درخت_رمز (decl) == OMP_ARRAY_SECTION)
		{
		  درخت کم_bound = درخت_عملیہ (decl, 1);
		  درخت لمبائی = درخت_عملیہ (decl, 2);
		  dims.محفوظ_ڈالو (omp_dim (کم_bound, لمبائی, loc, جھوٹ));
		  decl = درخت_عملیہ (decl, 0);
		}

	      جب (درخت_رمز (decl) == ARRAY_REF
		     || درخت_رمز (decl) == بالواسطہ_REF
		     || درخت_رمز (decl) == COMPOUND_اظہاریہ)
		{
		  اگر (درخت_رمز (decl) == COMPOUND_اظہاریہ)
		    {
		      decl = درخت_عملیہ (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  ورنہ اگر (درخت_رمز (decl) == بالواسطہ_REF)
		    {
		      dims.محفوظ_ڈالو (omp_dim (integer_zero_گرہ,
					       integer_one_گرہ, loc, سچ));
		      decl = درخت_عملیہ (decl, 0);
		    }
		  ورنہ  /* ARRAY_REF. */
		    {
		      درخت اشاریہ = درخت_عملیہ (decl, 1);
		      dims.محفوظ_ڈالو (omp_dim (اشاریہ, integer_one_گرہ, loc,
					       سچ));
		      decl = درخت_عملیہ (decl, 0);
		    }
		}

	      برائے (صحیح i = dims.لمبائی () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].کم_bound,
						dims[i].لمبائی);
	    }
	  ورنہ اگر (درخت_رمز (decl) == بالواسطہ_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = درخت_عملیہ (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_گرہ,
					      integer_one_گرہ);
	    }
	  ورنہ اگر (درخت_رمز (decl) == ARRAY_REF)
	    {
	      درخت idx = درخت_عملیہ (decl, 1);

	      decl = درخت_عملیہ (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_گرہ);
	    }
	  ورنہ اگر (درخت_رمز (decl) == NON_LVALUE_اظہاریہ
		   || CONVERT_اظہاریہ_P (decl))
	    decl = درخت_عملیہ (decl, 0);

	  درخت u = build_omp_clause (loc, قسم);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  جاؤ اگلا_شے;
	}

      اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_قسم == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->قدر);

	  اگر (t == NULL_درخت)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->قدر);
	      t = error_mark_گرہ;
	    }

	  c_parser_consume_token (parser);
	}
      ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).قدر;
      ورنہ
	{
	  c_parser_error (parser, "expected identifier");
	  توڑو;
	}

      اگر (t == error_mark_گرہ)
	;
      ورنہ اگر (قسم != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  انتخاب (قسم)
	    {
	    حالت OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      اگر (c_parser_peek_token (parser)->type != CPP_OPEN_مربع)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_گرہ;
		  توڑو;
		}
	      /* FALLTHROUGH  */
	    حالت OMP_CLAUSE_MAP:
	    حالت OMP_CLAUSE_FROM:
	    حالت OMP_CLAUSE_مقصد:
	    آغاز_component_ref:
	      جب (c_parser_اگلا_token_is (parser, CPP_DOT)
		     || c_parser_اگلا_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  اگر (c_parser_اگلا_token_is (parser, CPP_DEREF))
		    {
		      c_اظہاریہ t_اظہاریہ;
		      t_اظہاریہ.قدر = t;
		      t_اظہاریہ.original_رمز = ERROR_MARK;
		      t_اظہاریہ.original_type = تہی;
		      سیٹ_c_اظہاریہ_ماخذ_range (&t_اظہاریہ, op_loc, op_loc);
		      t_اظہاریہ.m_decimal = 0;
		      t_اظہاریہ = convert_lvalue_مقصد_rvalue (op_loc, t_اظہاریہ,
							 سچ, جھوٹ);
		      t = build_بالواسطہ_ref (op_loc, t_اظہاریہ.قدر, RO_ARROW);
		      arrow_loc = t_اظہاریہ.get_location ();
		    }
		  c_parser_consume_token (parser);
		  اگر (!c_parser_اگلا_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_گرہ;
		      توڑو;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  درخت ident = comp_tok->قدر;
		  location_t comp_loc = comp_tok->location;
		  c_parser_consume_token (parser);
		  t = build_component_ref (op_loc, t, ident, comp_loc,
					   arrow_loc);
		}
	      /* FALLTHROUGH  */
	    حالت OMP_CLAUSE_AFFINITY:
	    حالت OMP_CLAUSE_DEPEND:
	    حالت OMP_CLAUSE_REDUCTION:
	    حالت OMP_CLAUSE_اندر_REDUCTION:
	    حالت OMP_CLAUSE_TASK_REDUCTION:
	    حالت OMP_CLAUSE_HAS_DEVICE_ADDR:
	      array_section_p = جھوٹ;
	      dims.truncate (0);
	      جب (c_parser_اگلا_token_is (parser, CPP_OPEN_مربع))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  درخت کم_bound = NULL_درخت, لمبائی = NULL_درخت;
		  منطقی no_colon = جھوٹ;

		  c_parser_consume_token (parser);
		  اگر (!c_parser_اگلا_token_is (parser, CPP_COLON))
		    {
		      location_t اظہاریہ_loc
			= c_parser_peek_token (parser)->location;
		      c_اظہاریہ اظہاریہ = c_parser_عبارت (parser);
		      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ,
						       جھوٹ, سچ);
		      کم_bound = اظہاریہ.قدر;
		      loc = اظہاریہ_loc;
		    }
		  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_مربع))
		    {
		      لمبائی = integer_one_گرہ;
		      no_colon = سچ;
		    }
		  ورنہ
		    {
		      /* Look for `:'.  */
		      اگر (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_گرہ;
			  توڑو;
			}
		      array_section_p = سچ;
		      اگر (!c_parser_اگلا_token_is (parser, CPP_CLOSE_مربع))
			{
			  location_t اظہاریہ_loc
			    = c_parser_peek_token (parser)->location;
			  c_اظہاریہ اظہاریہ = c_parser_عبارت (parser);
			  اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ,
							   جھوٹ, سچ);
			  لمبائی = اظہاریہ.قدر;
			}
		    }
		  /* Look for the closing `]'.  */
		  اگر (!c_parser_require (parser, CPP_CLOSE_مربع,
					 "expected %<]%>"))
		    {
		      t = error_mark_گرہ;
		      توڑو;
		    }

		  dims.محفوظ_ڈالو (omp_dim (کم_bound, لمبائی, loc, no_colon));
		}

	      اگر (t != error_mark_گرہ)
		{
		  اگر ((قسم == OMP_CLAUSE_MAP
		       || قسم == OMP_CLAUSE_FROM
		       || قسم == OMP_CLAUSE_مقصد)
		      && !array_section_p
		      && (c_parser_اگلا_token_is (parser, CPP_DOT)
			  || c_parser_اگلا_token_is (parser, CPP_DEREF)))
		    {
		      برائے (غیرعلامتی i = 0; i < dims.لمبائی (); i++)
			{
			  gcc_assert (dims[i].لمبائی == integer_one_گرہ);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].کم_bound);
			}
		      جاؤ آغاز_component_ref;
		    }
		  ورنہ
		    برائے (غیرعلامتی i = 0; i < dims.لمبائی (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].کم_bound,
						   dims[i].لمبائی);
		}

	      اگر ((قسم == OMP_CLAUSE_DEPEND || قسم == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_گرہ
		  && parser->علامات_avail != 2)
		{
		  اگر (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_گرہ;
		    }
		  ورنہ
		    {
		      parser->علامات = علامات.پتہ ();
		      parser->علامات_avail = علامات.لمبائی ();

		      t = c_parser_اظہاریہ_no_commas (parser, تہی).قدر;
		      اگر (t != error_mark_گرہ && parser->علامات_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_گرہ;
			}
		    }
		}
	      توڑو;
	    طےشدہ:
	      توڑو;
	    }

	  اگر (t != error_mark_گرہ)
	    {
	      درخت u = build_omp_clause (clause_loc, قسم);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      ورنہ  /* kind == OMP_CLAUSE_ERROR */
	list = درخت_cons (t, build_خالی_خانے_stmt (tloc), list);

      اگر (قسم == OMP_CLAUSE_DEPEND || قسم == OMP_CLAUSE_AFFINITY)
	{
	  parser->علامات = saved_علامات;
	  parser->علامات_avail = علامات_avail;
	}

    اگلا_شے:
      اگر (c_parser_اگلا_token_is_not (parser, CPP_COMMA))
	توڑو;

      c_parser_consume_token (parser);
    }

  واپس list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

ساکن درخت
c_parser_omp_var_list_parens (c_parser *parser, شمار omp_clause_رمز قسم,
			      درخت list, منطقی map_lvalue = جھوٹ)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  اگر (parser->اندر_omp_decl_attribute)
    {
      اگر (قسم)
	{
	  درخت u = build_omp_clause (loc, قسم);
	  OMP_CLAUSE_DECL (u) = parser->اندر_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  واپس u;
	}
      ورنہ
	واپس درخت_cons (parser->اندر_omp_decl_attribute, NULL_درخت, list);
    }

  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, قسم, list, map_lvalue);
      parens.skip_until_ملا_close (parser);
    }
  واپس list;
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

ساکن درخت
c_parser_oacc_ڈیٹا_clause (c_parser *parser, pragma_omp_clause c_قسم,
			   درخت list)
{
  شمار gomp_map_قسم قسم;
  انتخاب (c_قسم)
    {
    حالت PRAGMA_OACC_CLAUSE_ATTACH:
      قسم = GOMP_MAP_ATTACH;
      توڑو;
    حالت PRAGMA_OACC_CLAUSE_COPY:
      قسم = GOMP_MAP_TOFROM;
      توڑو;
    حالت PRAGMA_OACC_CLAUSE_COPYIN:
      قسم = GOMP_MAP_مقصد;
      توڑو;
    حالت PRAGMA_OACC_CLAUSE_COPYOUT:
      قسم = GOMP_MAP_FROM;
      توڑو;
    حالت PRAGMA_OACC_CLAUSE_CREATE:
      قسم = GOMP_MAP_ALLOC;
      توڑو;
    حالت PRAGMA_OACC_CLAUSE_DELETE:
      قسم = GOMP_MAP_RELEASE;
      توڑو;
    حالت PRAGMA_OACC_CLAUSE_DETACH:
      قسم = GOMP_MAP_DETACH;
      توڑو;
    حالت PRAGMA_OACC_CLAUSE_DEVICE:
      قسم = GOMP_MAP_FORCE_مقصد;
      توڑو;
    حالت PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      قسم = GOMP_MAP_DEVICE_RESIDENT;
      توڑو;
    حالت PRAGMA_OACC_CLAUSE_LINK:
      قسم = GOMP_MAP_LINK;
      توڑو;
    حالت PRAGMA_OACC_CLAUSE_NO_CREATE:
      قسم = GOMP_MAP_IF_PRESENT;
      توڑو;
    حالت PRAGMA_OACC_CLAUSE_PRESENT:
      قسم = GOMP_MAP_FORCE_PRESENT;
      توڑو;
    حالت PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    حالت PRAGMA_OACC_CLAUSE_HOST:
      قسم = GOMP_MAP_FORCE_FROM;
      توڑو;
    طےشدہ:
      gcc_unreachable ();
    }

  درخت nl = list;
  منطقی readonly = جھوٹ;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      اگر (c_قسم == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  اگر (token->type == CPP_NAME
	      && !strcmp (IDENTIFIER_اشارہ_گر (token->قدر), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = سچ;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       جھوٹ);
      parens.skip_until_ملا_close (parser);
    }

  برائے (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_سیٹ_MAP_قسم (c, قسم);
      اگر (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  واپس nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

ساکن درخت
c_parser_oacc_ڈیٹا_clause_deviceptr (c_parser *parser, درخت list)
{
  درخت vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, تہی);
  برائے (t = vars; t && t; t = درخت_CHAIN (t))
    {
      درخت v = درخت_PURPOSE (t);
      location_t loc = اظہاریہ_LOCATION (درخت_قدر (t));

      اگر (!VAR_P (v) && درخت_رمز (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      ورنہ اگر (درخت_TYPE (v) == error_mark_گرہ)
	;
      ورنہ اگر (!اشارہ_گر_TYPE_P (درخت_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      درخت u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_سیٹ_MAP_قسم (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  واپس list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

ساکن درخت
c_parser_omp_clause_collapse (c_parser *parser, درخت list)
{
  درخت c, عدد = error_mark_گرہ;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      عدد = c_parser_اظہاریہ_no_commas (parser, تہی).قدر;
      parens.skip_until_ملا_close (parser);
    }
  اگر (عدد == error_mark_گرہ)
    واپس list;
  mark_exp_read (عدد);
  عدد = c_fully_fold (عدد, جھوٹ, تہی);
  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (عدد))
      || !درخت_سماتا_shwi_p (عدد)
      || (n = درخت_مقصد_shwi (عدد)) <= 0
      || (صحیح) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      واپس list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_اظہاریہ (c) = عدد;
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

ساکن درخت
c_parser_omp_clause_copyin (c_parser *parser, درخت list)
{
  واپس c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

ساکن درخت
c_parser_omp_clause_copyprivate (c_parser *parser, درخت list)
{
  واپس c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

ساکن درخت
c_parser_omp_clause_default (c_parser *parser, درخت list, منطقی is_oacc)
{
  شمار omp_clause_default_قسم قسم = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  درخت c;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);

      انتخاب (p[0])
	{
	حالت 'n':
	  اگر (strcmp ("none", p) != 0)
	    جاؤ invalid_قسم;
	  قسم = OMP_CLAUSE_DEFAULT_NONE;
	  توڑو;

	حالت 'p':
	  اگر (is_oacc)
	    {
	      اگر (strcmp ("present", p) != 0)
		جاؤ invalid_قسم;
	      قسم = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  ورنہ
	    {
	      اگر (strcmp ("private", p) != 0)
		جاؤ invalid_قسم;
	      قسم = OMP_CLAUSE_DEFAULT_نجی;
	    }
	  توڑو;

	حالت 'f':
	  اگر (strcmp ("firstprivate", p) != 0 || is_oacc)
	    جاؤ invalid_قسم;
	  قسم = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  توڑو;

	حالت 's':
	  اگر (strcmp ("shared", p) != 0 || is_oacc)
	    جاؤ invalid_قسم;
	  قسم = OMP_CLAUSE_DEFAULT_SHARED;
	  توڑو;

	طےشدہ:
	  جاؤ invalid_قسم;
	}

      c_parser_consume_token (parser);
    }
  ورنہ
    {
    invalid_قسم:
      اگر (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      ورنہ
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_ملا_close (parser);

  اگر (قسم == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    واپس list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_قسم (c) = قسم;

  واپس c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

ساکن درخت
c_parser_omp_clause_firstprivate (c_parser *parser, درخت list)
{
  واپس c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

ساکن درخت
c_parser_omp_clause_final (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      درخت t, c;
      اگر (!parens.require_open (parser))
	t = error_mark_گرہ;
      ورنہ
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	  t = convert_lvalue_مقصد_rvalue (eloc, اظہاریہ, سچ, سچ).قدر;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, جھوٹ, تہی);
	  parens.skip_until_ملا_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_اظہاریہ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }
  ورنہ
    c_parser_error (parser, "expected %<(%>");

  واپس list;
}

/* OpenMP 5.1:
   indirect [( expression )]
*/

ساکن درخت
c_parser_omp_clause_بالواسطہ (c_parser *parser, درخت list)
{
  location_t location = c_parser_peek_token (parser)->location;
  درخت t;

  اگر (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      اگر (!parens.require_open (parser))
	واپس list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (loc, اظہاریہ, سچ, سچ);
      t = c_objc_common_truthvalue_conversion (loc, اظہاریہ.قدر);
      t = c_fully_fold (t, جھوٹ, تہی);
      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t))
	  || درخت_رمز (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  واپس list;
	}
      parens.skip_until_ملا_close (parser);
    }
  ورنہ
    t = integer_one_گرہ;

  check_no_duplicate_clause (list, OMP_CLAUSE_بالواسطہ, "indirect");

  درخت c = build_omp_clause (location, OMP_CLAUSE_بالواسطہ);
  OMP_CLAUSE_بالواسطہ_اظہاریہ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;

  واپس c;
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

ساکن درخت
c_parser_omp_clause_if (c_parser *parser, درخت list, منطقی is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  شمار درخت_رمز_2 if_modifier = ERROR_MARK;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  اگر (is_omp && c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      صحیح n = 2;
      اگر (strcmp (p, "cancel") == 0)
	if_modifier = VOID_CST;
      ورنہ اگر (strcmp (p, "parallel") == 0)
	if_modifier = OMP_PARALLEL;
      ورنہ اگر (strcmp (p, "simd") == 0)
	if_modifier = OMP_SIMD;
      ورنہ اگر (strcmp (p, "task") == 0)
	if_modifier = OMP_TASK;
      ورنہ اگر (strcmp (p, "taskloop") == 0)
	if_modifier = OMP_TASKLOOP;
      ورنہ اگر (strcmp (p, "target") == 0)
	{
	  if_modifier = OMP_ہدف;
	  اگر (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	    {
	      p = IDENTIFIER_اشارہ_گر (c_parser_peek_2nd_token (parser)->قدر);
	      اگر (strcmp ("data", p) == 0)
		if_modifier = OMP_ہدف_ڈیٹا;
	      ورنہ اگر (strcmp ("update", p) == 0)
		if_modifier = OMP_ہدف_UPDATE;
	      ورنہ اگر (strcmp ("enter", p) == 0)
		if_modifier = OMP_ہدف_ENTER_ڈیٹا;
	      ورنہ اگر (strcmp ("exit", p) == 0)
		if_modifier = OMP_ہدف_EXIT_ڈیٹا;
	      اگر (if_modifier != OMP_ہدف)
		{
		  n = 3;
		  c_parser_consume_token (parser);
		}
	      ورنہ
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<data%>, %<update%>, %<enter%> "
				 "or %<exit%>");
		  if_modifier = ERROR_MARK;
		}
	      اگر (if_modifier == OMP_ہدف_ENTER_ڈیٹا
		  || if_modifier == OMP_ہدف_EXIT_ڈیٹا)
		{
		  اگر (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_اشارہ_گر
				(c_parser_peek_2nd_token (parser)->قدر);
		      اگر (strcmp ("data", p) == 0)
			n = 4;
		    }
		  اگر (n == 4)
		    c_parser_consume_token (parser);
		  ورنہ
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
	  ورنہ
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
  c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
  اظہاریہ = convert_lvalue_مقصد_rvalue (loc, اظہاریہ, سچ, سچ);
  درخت t = c_objc_common_truthvalue_conversion (loc, اظہاریہ.قدر), c;
  t = c_fully_fold (t, جھوٹ, تہی);
  parens.skip_until_ملا_close (parser);

  برائے (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_IF)
      {
	اگر (if_modifier != ERROR_MARK
	    && OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    ثابت حرف *p = تہی;
	    انتخاب (if_modifier)
	      {
	      حالت VOID_CST: p = "cancel"; توڑو;
	      حالت OMP_PARALLEL: p = "parallel"; توڑو;
	      حالت OMP_SIMD: p = "simd"; توڑو;
	      حالت OMP_TASK: p = "task"; توڑو;
	      حالت OMP_TASKLOOP: p = "taskloop"; توڑو;
	      حالت OMP_ہدف_ڈیٹا: p = "target data"; توڑو;
	      حالت OMP_ہدف: p = "target"; توڑو;
	      حالت OMP_ہدف_UPDATE: p = "target update"; توڑو;
	      حالت OMP_ہدف_ENTER_ڈیٹا: p = "target enter data"; توڑو;
	      حالت OMP_ہدف_EXIT_ڈیٹا: p = "target exit data"; توڑو;
	      طےشدہ: gcc_unreachable ();
	      }
	    error_at (location, "too many %<if%> clauses with %qs modifier",
		      p);
	    واپس list;
	  }
	ورنہ اگر (OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    اگر (!is_omp)
	      error_at (location, "too many %<if%> clauses");
	    ورنہ
	      error_at (location, "too many %<if%> clauses without modifier");
	    واپس list;
	  }
	ورنہ اگر (if_modifier == ERROR_MARK
		 || OMP_CLAUSE_IF_MODIFIER (c) == ERROR_MARK)
	  {
	    error_at (location, "if any %<if%> clause has modifier, then all "
				"%<if%> clauses have to use modifier");
	    واپس list;
	  }
      }

  c = build_omp_clause (location, OMP_CLAUSE_IF);
  OMP_CLAUSE_IF_MODIFIER (c) = if_modifier;
  OMP_CLAUSE_IF_اظہاریہ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

ساکن درخت
c_parser_omp_clause_lastprivate (c_parser *parser, درخت list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  اگر (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      منطقی conditional = جھوٹ;
      اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  ثابت حرف *p
	    = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
	  اگر (strcmp (p, "conditional") == 0)
	    {
	      conditional = سچ;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      درخت nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      اگر (conditional)
	برائے (درخت c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      واپس nlist;
    }
  واپس list;
}

/* OpenMP 3.1:
   mergeable */

ساکن درخت
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_غیر_مستعمل, درخت list)
{
  درخت c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  واپس c;
}

/* OpenMP 2.5:
   nowait */

ساکن درخت
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_غیر_مستعمل, درخت list)
{
  درخت c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

ساکن درخت
c_parser_omp_clause_عدد_دھاگے (c_parser *parser, درخت list)
{
  location_t عدد_دھاگے_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
      درخت c, t = اظہاریہ.قدر;
      t = c_fully_fold (t, جھوٹ, تہی);

      parens.skip_until_ملا_close (parser);

      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  واپس list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (اظہاریہ_loc, LE_اظہاریہ, boolean_type_گرہ, t,
		       build_int_cst (درخت_TYPE (t), 0));
      protected_سیٹ_اظہاریہ_location (c, اظہاریہ_loc);
      اگر (c == boolean_true_گرہ)
	{
	  warning_at (اظہاریہ_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_گرہ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_عدد_دھاگے, "num_threads");

      c = build_omp_clause (عدد_دھاگے_loc, OMP_CLAUSE_عدد_دھاگے);
      OMP_CLAUSE_عدد_دھاگے_اظہاریہ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  واپس list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

ساکن درخت
c_parser_omp_clause_عدد_tasks (c_parser *parser, درخت list)
{
  location_t عدد_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      منطقی strict = جھوٹ;
      اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر),
		     "strict") == 0)
	{
	  strict = سچ;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
      درخت c, t = اظہاریہ.قدر;
      t = c_fully_fold (t, جھوٹ, تہی);

      parens.skip_until_ملا_close (parser);

      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  واپس list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (اظہاریہ_loc, LE_اظہاریہ, boolean_type_گرہ, t,
			   build_int_cst (درخت_TYPE (t), 0));
      اگر (CAN_HAVE_LOCATION_P (c))
	سیٹ_اظہاریہ_LOCATION (c, اظہاریہ_loc);
      اگر (c == boolean_true_گرہ)
	{
	  warning_at (اظہاریہ_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_گرہ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_عدد_TASKS, "num_tasks");

      c = build_omp_clause (عدد_tasks_loc, OMP_CLAUSE_عدد_TASKS);
      OMP_CLAUSE_عدد_TASKS_اظہاریہ (c) = t;
      OMP_CLAUSE_عدد_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  واپس list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

ساکن درخت
c_parser_omp_clause_grainsize (c_parser *parser, درخت list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      منطقی strict = جھوٹ;
      اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر),
		     "strict") == 0)
	{
	  strict = سچ;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
      درخت c, t = اظہاریہ.قدر;
      t = c_fully_fold (t, جھوٹ, تہی);

      parens.skip_until_ملا_close (parser);

      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  واپس list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (اظہاریہ_loc, LE_اظہاریہ, boolean_type_گرہ, t,
			   build_int_cst (درخت_TYPE (t), 0));
      اگر (CAN_HAVE_LOCATION_P (c))
	سیٹ_اظہاریہ_LOCATION (c, اظہاریہ_loc);
      اگر (c == boolean_true_گرہ)
	{
	  warning_at (اظہاریہ_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_گرہ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_اظہاریہ (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  واپس list;
}

/* OpenMP 4.5:
   priority ( expression ) */

ساکن درخت
c_parser_omp_clause_ترجیح (c_parser *parser, درخت list)
{
  location_t ترجیح_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
      درخت c, t = اظہاریہ.قدر;
      t = c_fully_fold (t, جھوٹ, تہی);

      parens.skip_until_ملا_close (parser);

      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  واپس list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (اظہاریہ_loc, LT_اظہاریہ, boolean_type_گرہ, t,
			   build_int_cst (درخت_TYPE (t), 0));
      اگر (CAN_HAVE_LOCATION_P (c))
	سیٹ_اظہاریہ_LOCATION (c, اظہاریہ_loc);
      اگر (c == boolean_true_گرہ)
	{
	  warning_at (اظہاریہ_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_گرہ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_ترجیح, "priority");

      c = build_omp_clause (ترجیح_loc, OMP_CLAUSE_ترجیح);
      OMP_CLAUSE_ترجیح_اظہاریہ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  واپس list;
}

/* OpenMP 4.5:
   hint ( expression ) */

ساکن درخت
c_parser_omp_clause_hint (c_parser *parser, درخت list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
      درخت c, t = اظہاریہ.قدر;
      t = c_fully_fold (t, جھوٹ, تہی);
      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t))
	  || درخت_رمز (t) != INTEGER_CST
	  || درخت_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  واپس list;
	}
      parens.skip_until_ملا_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_اظہاریہ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  واپس list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

ساکن درخت
c_parser_omp_clause_filter (c_parser *parser, درخت list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
      درخت c, t = اظہاریہ.قدر;
      t = c_fully_fold (t, جھوٹ, تہی);
      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  واپس list;
	}
      parens.skip_until_ملا_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_اظہاریہ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  واپس list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

ساکن درخت
c_parser_omp_clause_defaultmap (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت c;
  ثابت حرف *p;
  شمار omp_clause_defaultmap_قسم behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  شمار omp_clause_defaultmap_قسم category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;
  اگر (c_parser_اگلا_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  ورنہ اگر (!c_parser_اگلا_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      جاؤ برآمد_err;
    }
  ورنہ
    p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);

  انتخاب (p[0])
    {
    حالت 'a':
      اگر (strcmp ("alloc", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ALLOC;
      ورنہ
	جاؤ invalid_behavior;
      توڑو;

    حالت 'd':
      اگر (strcmp ("default", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
      ورنہ
	جاؤ invalid_behavior;
      توڑو;

    حالت 'f':
      اگر (strcmp ("firstprivate", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FIRSTPRIVATE;
      ورنہ اگر (strcmp ("from", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FROM;
      ورنہ
	جاؤ invalid_behavior;
      توڑو;

    حالت 'n':
      اگر (strcmp ("none", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_NONE;
      ورنہ
	جاؤ invalid_behavior;
      توڑو;

    حالت 'p':
      اگر (strcmp ("present", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_PRESENT;
      ورنہ
	جاؤ invalid_behavior;
      توڑو;

    حالت 't':
      اگر (strcmp ("tofrom", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TOFROM;
      ورنہ اگر (strcmp ("to", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_مقصد;
      ورنہ
	جاؤ invalid_behavior;
      توڑو;

    طےشدہ:
      جاؤ invalid_behavior;
    }
  c_parser_consume_token (parser);

  اگر (!c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
    {
      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	جاؤ برآمد_err;
      اگر (!c_parser_اگلا_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  جاؤ برآمد_err;
	}
      p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      انتخاب (p[0])
	{
	حالت 'a':
	  اگر (strcmp ("aggregate", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE;
	  ورنہ اگر (strcmp ("all", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL;
	  ورنہ
	    جاؤ invalid_category;
	  توڑو;

	حالت 'p':
	  اگر (strcmp ("pointer", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_اشارہ_گر;
	  ورنہ
	    جاؤ invalid_category;
	  توڑو;

	حالت 's':
	  اگر (strcmp ("scalar", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR;
	  ورنہ
	    جاؤ invalid_category;
	  توڑو;

	طےشدہ:
	  جاؤ invalid_category;
	}

      c_parser_consume_token (parser);
    }
  parens.skip_until_ملا_close (parser);

  برائے (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEFAULTMAP
	&& (category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
	    || OMP_CLAUSE_DEFAULTMAP_CATEGORY (c) == category
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL)))
      {
	شمار omp_clause_defaultmap_قسم cat = category;
	location_t loc = OMP_CLAUSE_LOCATION (c);
	اگر (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
		&& (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		    != OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)))
	  cat = OMP_CLAUSE_DEFAULTMAP_CATEGORY (c);
	p = تہی;
	انتخاب (cat)
	  {
	  حالت OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED:
	    p = تہی;
	    توڑو;
	  حالت OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL:
	    p = "all";
	    توڑو;
	  حالت OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE:
	    p = "aggregate";
	    توڑو;
	  حالت OMP_CLAUSE_DEFAULTMAP_CATEGORY_اشارہ_گر:
	    p = "pointer";
	    توڑو;
	  حالت OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR:
	    p = "scalar";
	    توڑو;
	  طےشدہ:
	    gcc_unreachable ();
	  }
	اگر (p)
	  error_at (loc, "too many %<defaultmap%> clauses with %qs category",
		    p);
	ورنہ
	  error_at (loc, "too many %<defaultmap%> clauses with unspecified "
			 "category");
	توڑو;
      }

  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULTMAP);
  OMP_CLAUSE_DEFAULTMAP_سیٹ_قسم (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;

 برآمد_err:
  parens.skip_until_ملا_close (parser);
  واپس list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

ساکن درخت
c_parser_omp_clause_use_device_ptr (c_parser *parser, درخت list)
{
  واپس c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

ساکن درخت
c_parser_omp_clause_use_device_addr (c_parser *parser, درخت list)
{
  واپس c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

ساکن درخت
c_parser_omp_clause_has_device_addr (c_parser *parser, درخت list)
{
  واپس c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

ساکن درخت
c_parser_omp_clause_is_device_ptr (c_parser *parser, درخت list)
{
  واپس c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

ساکن درخت
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_رمز رمز,
				 درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
  c_اظہاریہ اظہاریہ = c_parser_عبارت (parser);
  اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
  درخت c, t = اظہاریہ.قدر;
  t = c_fully_fold (t, جھوٹ, تہی);

  parens.skip_until_ملا_close (parser);

  اگر (t == error_mark_گرہ)
    واپس list;
  ورنہ اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
    {
      error_at (اظہاریہ_loc, "%qs expression must be integral",
		omp_clause_رمز_name[رمز]);
      واپس list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (اظہاریہ_loc, LE_اظہاریہ, boolean_type_گرہ, t,
		       build_int_cst (درخت_TYPE (t), 0));
  protected_سیٹ_اظہاریہ_location (c, اظہاریہ_loc);
  اگر (c == boolean_true_گرہ)
    {
      warning_at (اظہاریہ_loc, 0,
		  "%qs value must be positive",
		  omp_clause_رمز_name[رمز]);
      t = integer_one_گرہ;
    }

  check_no_duplicate_clause (list, رمز, omp_clause_رمز_name[رمز]);

  c = build_omp_clause (loc, رمز);
  OMP_CLAUSE_عملیہ (c, 0) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
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

ساکن درخت
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_رمز قسم,
			    ثابت حرف *str, درخت list)
{
  ثابت حرف *id = "num";
  درخت ops[2] = { NULL_درخت, NULL_درخت }, c;

  اگر (قسم == OMP_CLAUSE_سمتیہ)
    id = "length";

  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      کرو
	{
	  c_token *اگلا = c_parser_peek_token (parser);
	  صحیح idx = 0;

	  /* Gang static argument.  */
	  اگر (قسم == OMP_CLAUSE_GANG
	      && c_parser_اگلا_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		جاؤ cleanup_error;

	      idx = 1;
	      اگر (ops[idx] != NULL_درخت)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  جاؤ cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      اگر (c_parser_اگلا_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_گرہ;

		  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      جاری;
		    }
		  ورنہ
		    توڑو;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
		   && strcmp (id, IDENTIFIER_اشارہ_گر (اگلا->قدر)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  اگر (ops[idx] != NULL_درخت)
	    {
	      c_parser_error (parser, "unexpected argument");
	      جاؤ cleanup_error;
	    }

	  location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
	  c_اظہاریہ cexpr = c_parser_اظہاریہ_no_commas (parser, تہی);
	  cexpr = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, cexpr, جھوٹ, سچ);
	  درخت اظہاریہ = cexpr.قدر;
	  اگر (اظہاریہ == error_mark_گرہ)
	    جاؤ cleanup_error;

	  اظہاریہ = c_fully_fold (اظہاریہ, جھوٹ, تہی);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (اظہاریہ)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      واپس list;
	    }

	  درخت c = fold_build2_loc (اظہاریہ_loc, LE_اظہاریہ, boolean_type_گرہ, اظہاریہ,
				    build_int_cst (درخت_TYPE (اظہاریہ), 0));
	  اگر (c == boolean_true_گرہ)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      اظہاریہ = integer_one_گرہ;
	    }

	  ops[idx] = اظہاریہ;

	  اگر (قسم == OMP_CLAUSE_GANG
	      && c_parser_اگلا_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      جاری;
	    }
	  توڑو;
	}
      جب (1);

      اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	جاؤ cleanup_error;
    }

  check_no_duplicate_clause (list, قسم, str);

  c = build_omp_clause (loc, قسم);

  اگر (ops[1])
    OMP_CLAUSE_عملیہ (c, 1) = ops[1];

  OMP_CLAUSE_عملیہ (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  واپس c;

 cleanup_error:
  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, 0);
  واپس list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

ساکن درخت
c_parser_oacc_simple_clause (location_t loc, شمار omp_clause_رمز رمز,
			     درخت list)
{
  check_no_duplicate_clause (list, رمز, omp_clause_رمز_name[رمز]);

  درخت c = build_omp_clause (loc, رمز);
  OMP_CLAUSE_CHAIN (c) = list;

  واپس c;
}

/* OpenACC:
   async [( int-expr )] */

ساکن درخت
c_parser_oacc_clause_async (c_parser *parser, درخت list)
{
  درخت c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_گرہ, GOMP_ASYNC_NOVAL);

  اگر (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_اظہاریہ_no_commas (parser, تہی).قدر;
      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      ورنہ اگر (t == error_mark_گرہ
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	واپس list;
    }
  ورنہ
    t = c_fully_fold (t, جھوٹ, تہی);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_اظہاریہ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  واپس list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

ساکن درخت
c_parser_oacc_clause_tile (c_parser *parser, درخت list)
{
  درخت c, اظہاریہ = error_mark_گرہ;
  location_t loc;
  درخت tile = NULL_درخت;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    واپس list;

  کرو
    {
      اگر (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	واپس list;

      اگر (c_parser_اگلا_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  اظہاریہ = integer_zero_گرہ;
	}
      ورنہ
	{
	  location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
	  c_اظہاریہ cexpr = c_parser_اظہاریہ_no_commas (parser, تہی);
	  cexpr = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, cexpr, جھوٹ, سچ);
	  اظہاریہ = cexpr.قدر;

	  اگر (اظہاریہ == error_mark_گرہ)
	    {
	      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      واپس list;
	    }

	  اظہاریہ = c_fully_fold (اظہاریہ, جھوٹ, تہی);

	  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (اظہاریہ))
	      || !درخت_سماتا_shwi_p (اظہاریہ)
	      || درخت_مقصد_shwi (اظہاریہ) <= 0)
	    {
	      error_at (اظہاریہ_loc, "%<tile%> argument needs positive"
			" integral constant");
	      اظہاریہ = integer_zero_گرہ;
	    }
	}

      tile = درخت_cons (NULL_درخت, اظہاریہ, tile);
    }
  جب (c_parser_اگلا_token_is_not (parser, CPP_CLOSE_PAREN));

  /* Consume the trailing ')'.  */
  c_parser_consume_token (parser);

  c = build_omp_clause (loc, OMP_CLAUSE_TILE);
  tile = nreverse (tile);
  OMP_CLAUSE_TILE_LIST (c) = tile;
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
}

/* OpenACC:
   wait [( int-expr-list )] */

ساکن درخت
c_parser_oacc_clause_wait (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  اگر (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  ورنہ
    {
      درخت c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_گرہ, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  واپس list;
}

/* OpenACC 2.7:
   self [( expression )] */

ساکن درخت
c_parser_oacc_compute_clause_self (c_parser *parser, درخت list)
{
  درخت t;
  location_t location = c_parser_peek_token (parser)->location;
  اگر (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (loc, اظہاریہ, سچ, سچ);
      t = c_objc_common_truthvalue_conversion (loc, اظہاریہ.قدر);
      t = c_fully_fold (t, جھوٹ, تہی);
      parens.skip_until_ملا_close (parser);
    }
  ورنہ
    t = truthvalue_true_گرہ;

  برائے (درخت c = list; c; c = OMP_CLAUSE_CHAIN (c))
    اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	واپس list;
      }

  درخت c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_اظہاریہ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
}

/* OpenMP 5.0:
   order ( concurrent )

   OpenMP 5.1:
   order ( order-modifier : concurrent )

   order-modifier:
     reproducible
     unconstrained  */

ساکن درخت
c_parser_omp_clause_ترتیب (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت c;
  ثابت حرف *p;
  منطقی unconstrained = جھوٹ;
  منطقی reproducible = جھوٹ;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp (p, "unconstrained") == 0)
	unconstrained = سچ;
      ورنہ اگر (strcmp (p, "reproducible") == 0)
	reproducible = سچ;
      ورنہ
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  جاؤ برآمد_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  اگر (!c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      جاؤ برآمد_err;
    }
  p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
  اگر (strcmp (p, "concurrent") != 0)
    {
      c_parser_error (parser, "expected %<concurrent%>");
      جاؤ برآمد_err;
    }
  c_parser_consume_token (parser);
  parens.skip_until_ملا_close (parser);
  check_no_duplicate_clause (list, OMP_CLAUSE_ترتیب, "order");
  c = build_omp_clause (loc, OMP_CLAUSE_ترتیب);
  OMP_CLAUSE_ترتیب_UNCONSTRAINED (c) = unconstrained;
  OMP_CLAUSE_ترتیب_REPRODUCIBLE (c) = reproducible;
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;

 برآمد_err:
  parens.skip_until_ملا_close (parser);
  واپس list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

ساکن درخت
c_parser_omp_clause_bind (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت c;
  ثابت حرف *p;
  شمار omp_clause_bind_قسم قسم = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;
  اگر (!c_parser_اگلا_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_ملا_close (parser);
      واپس list;
    }
  p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
  اگر (strcmp (p, "teams") == 0)
    قسم = OMP_CLAUSE_BIND_TEAMS;
  ورنہ اگر (strcmp (p, "parallel") == 0)
    قسم = OMP_CLAUSE_BIND_PARALLEL;
  ورنہ اگر (strcmp (p, "thread") != 0)
    جاؤ invalid;
  c_parser_consume_token (parser);
  parens.skip_until_ملا_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_قسم (c) = قسم;
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

ساکن درخت
c_parser_omp_clause_ordered (c_parser *parser, درخت list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  درخت c, عدد = NULL_درخت;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      عدد = c_parser_اظہاریہ_no_commas (parser, تہی).قدر;
      parens.skip_until_ملا_close (parser);
    }
  اگر (عدد == error_mark_گرہ)
    واپس list;
  اگر (عدد)
    {
      mark_exp_read (عدد);
      عدد = c_fully_fold (عدد, جھوٹ, تہی);
      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (عدد))
	  || !درخت_سماتا_shwi_p (عدد)
	  || (n = درخت_مقصد_shwi (عدد)) <= 0
	  || (صحیح) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  واپس list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_اظہاریہ (c) = عدد;
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

ساکن درخت
c_parser_omp_clause_نجی (c_parser *parser, درخت list)
{
  واپس c_parser_omp_var_list_parens (parser, OMP_CLAUSE_نجی, list);
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

ساکن درخت
c_parser_omp_clause_reduction (c_parser *parser, شمار omp_clause_رمز قسم,
			       منطقی is_omp, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      منطقی task = جھوٹ;
      منطقی inscan = جھوٹ;
      شمار درخت_رمز_2 رمز = ERROR_MARK;
      درخت reduc_id = NULL_درخت;

      اگر (قسم == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  اگر (c_parser_اگلا_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      ثابت حرف *p
		= IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
	      اگر (strcmp (p, "task") == 0)
		task = سچ;
	      ورنہ اگر (strcmp (p, "inscan") == 0)
		inscan = سچ;
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
	  رمز = PLUS_اظہاریہ;
	  توڑو;
	حالت CPP_MULT:
	  رمز = MULT_اظہاریہ;
	  توڑو;
	حالت CPP_MINUS:
	  اگر (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.جوڑو_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  رمز = MINUS_اظہاریہ;
	  توڑو;
	حالت CPP_AND:
	  رمز = ثنائی_ہندسہ_AND_اظہاریہ;
	  توڑو;
	حالت CPP_XOR:
	  رمز = ثنائی_ہندسہ_XOR_اظہاریہ;
	  توڑو;
	حالت CPP_OR:
	  رمز = ثنائی_ہندسہ_IOR_اظہاریہ;
	  توڑو;
	حالت CPP_AND_AND:
	  رمز = TRUTH_ANDIF_اظہاریہ;
	  توڑو;
	حالت CPP_OR_OR:
	  رمز = TRUTH_ORIF_اظہاریہ;
	  توڑو;
        حالت CPP_NAME:
	  {
	    ثابت حرف *p
	      = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
	    اگر (strcmp (p, "min") == 0)
	      {
		رمز = MIN_اظہاریہ;
		توڑو;
	      }
	    اگر (strcmp (p, "max") == 0)
	      {
		رمز = MAX_اظہاریہ;
		توڑو;
	      }
	    reduc_id = c_parser_peek_token (parser)->قدر;
	    توڑو;
	  }
	طےشدہ:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, 0);
	  واپس list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (رمز, reduc_id);
      اگر (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  درخت nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, قسم, list);
	  برائے (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      درخت d = OMP_CLAUSE_DECL (c), type;
	      اگر (درخت_رمز (d) != OMP_ARRAY_SECTION)
		type = درخت_TYPE (d);
	      ورنہ
		{
		  صحیح cnt = 0;
		  درخت t;
		  برائے (t = d;
		      درخت_رمز (t) == OMP_ARRAY_SECTION;
		      t = درخت_عملیہ (t, 0))
		    cnt++;
		  type = درخت_TYPE (t);
		  جب (cnt > 0)
		    {
		      اگر (درخت_رمز (type) != اشارہ_گر_TYPE
			  && درخت_رمز (type) != ARRAY_TYPE)
			توڑو;
		      type = درخت_TYPE (type);
		      cnt--;
		    }
		}
	      جب (درخت_رمز (type) == ARRAY_TYPE)
		type = درخت_TYPE (type);
	      OMP_CLAUSE_REDUCTION_رمز (c) = رمز;
	      اگر (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      ورنہ اگر (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      اگر (رمز == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || درخت_رمز (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_ملا_close (parser);
    }
  واپس list;
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

ساکن درخت
c_parser_omp_clause_جدول_وقت (c_parser *parser, درخت list)
{
  درخت c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  صحیح modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  c = build_omp_clause (loc, OMP_CLAUSE_جدول_وقت);

  location_t comma = UNKNOWN_LOCATION;
  جب (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      درخت قسم = c_parser_peek_token (parser)->قدر;
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (قسم);
      اگر (strcmp ("simd", p) == 0)
	OMP_CLAUSE_جدول_وقت_SIMD (c) = 1;
      ورنہ اگر (strcmp ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_جدول_وقت_MONOTONIC;
      ورنہ اگر (strcmp ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_جدول_وقت_NONMONOTONIC;
      ورنہ
	توڑو;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      اگر (nmodifiers++ == 0
	  && c_parser_اگلا_token_is (parser, CPP_COMMA))
	{
	  comma = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	}
      ورنہ
	{
	  c_parser_require (parser, CPP_COLON, "expected %<:%>");
	  توڑو;
	}
    }
  اگر (comma != UNKNOWN_LOCATION)
    error_at (comma, "expected %<:%>");

  اگر ((modifiers & (OMP_CLAUSE_جدول_وقت_MONOTONIC
		    | OMP_CLAUSE_جدول_وقت_NONMONOTONIC))
      == (OMP_CLAUSE_جدول_وقت_MONOTONIC
	  | OMP_CLAUSE_جدول_وقت_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      درخت قسم = c_parser_peek_token (parser)->قدر;
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (قسم);

      انتخاب (p[0])
	{
	حالت 'd':
	  اگر (strcmp ("dynamic", p) != 0)
	    جاؤ invalid_قسم;
	  OMP_CLAUSE_جدول_وقت_قسم (c) = OMP_CLAUSE_جدول_وقت_DYNAMIC;
	  توڑو;

        حالت 'g':
	  اگر (strcmp ("guided", p) != 0)
	    جاؤ invalid_قسم;
	  OMP_CLAUSE_جدول_وقت_قسم (c) = OMP_CLAUSE_جدول_وقت_GUIDED;
	  توڑو;

	حالت 'r':
	  اگر (strcmp ("runtime", p) != 0)
	    جاؤ invalid_قسم;
	  OMP_CLAUSE_جدول_وقت_قسم (c) = OMP_CLAUSE_جدول_وقت_RUNTIME;
	  توڑو;

	طےشدہ:
	  جاؤ invalid_قسم;
	}
    }
  ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_جدول_وقت_قسم (c) = OMP_CLAUSE_جدول_وقت_STATIC;
  ورنہ اگر (c_parser_اگلا_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_جدول_وقت_قسم (c) = OMP_CLAUSE_جدول_وقت_AUTO;
  ورنہ
    جاؤ invalid_قسم;

  c_parser_consume_token (parser);
  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
    {
      location_t یہاں;
      c_parser_consume_token (parser);

      یہاں = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (یہاں, اظہاریہ, جھوٹ, سچ);
      t = اظہاریہ.قدر;
      t = c_fully_fold (t, جھوٹ, تہی);

      اگر (OMP_CLAUSE_جدول_وقت_قسم (c) == OMP_CLAUSE_جدول_وقت_RUNTIME)
	error_at (یہاں, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      ورنہ اگر (OMP_CLAUSE_جدول_وقت_قسم (c) == OMP_CLAUSE_جدول_وقت_AUTO)
	error_at (یہاں,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      ورنہ اگر (درخت_رمز (درخت_TYPE (t)) == INTEGER_TYPE
	       || درخت_رمز (درخت_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  درخت s = fold_build2_loc (loc, LE_اظہاریہ, boolean_type_گرہ, t,
				    build_int_cst (درخت_TYPE (t), 0));
	  protected_سیٹ_اظہاریہ_location (s, loc);
	  اگر (s == boolean_true_گرہ)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_گرہ;
	    }
	  OMP_CLAUSE_جدول_وقت_CHUNK_اظہاریہ (c) = t;
	}
      ورنہ
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_ملا_close (parser);
    }
  ورنہ
    c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_جدول_وقت_قسم (c)
    = (شمار omp_clause_جدول_وقت_قسم)
      (OMP_CLAUSE_جدول_وقت_قسم (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_جدول_وقت, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;

 invalid_قسم:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, 0);
  واپس list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

ساکن درخت
c_parser_omp_clause_shared (c_parser *parser, درخت list)
{
  واپس c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

ساکن درخت
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_غیر_مستعمل, درخت list)
{
  درخت c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_UNTIED, "untied");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_UNTIED);
  OMP_CLAUSE_CHAIN (c) = list;

  واپس c;
}

/* OpenMP 4.0:
   inbranch
   notinbranch */

ساکن درخت
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_غیر_مستعمل,
			    شمار omp_clause_رمز رمز, درخت list)
{
  check_no_duplicate_clause (list, رمز, omp_clause_رمز_name[رمز]);

  درخت c = build_omp_clause (c_parser_peek_token (parser)->location, رمز);
  OMP_CLAUSE_CHAIN (c) = list;

  واپس c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

ساکن درخت
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_غیر_مستعمل,
				شمار omp_clause_رمز رمز, درخت list)
{
  درخت c = build_omp_clause (c_parser_peek_token (parser)->location, رمز);
  OMP_CLAUSE_CHAIN (c) = list;

  واپس c;
}

/* OpenMP 4.5:
   nogroup */

ساکن درخت
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_غیر_مستعمل, درخت list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  درخت c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
}

/* OpenMP 4.5:
   simd
دھاگے*/

ساکن درخت
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_غیر_مستعمل,
				 شمار omp_clause_رمز رمز, درخت list)
{
  check_no_duplicate_clause (list, رمز, omp_clause_رمز_name[رمز]);
  درخت c = build_omp_clause (c_parser_peek_token (parser)->location, رمز);
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

ساکن درخت
c_parser_omp_clause_عدد_teams (c_parser *parser, درخت list)
{
  location_t عدد_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      location_t بالائی_loc = c_parser_peek_token (parser)->location;
      location_t زیریں_loc = UNKNOWN_LOCATION;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (بالائی_loc, اظہاریہ, جھوٹ, سچ);
      درخت c, بالائی = اظہاریہ.قدر, زیریں = NULL_درخت;
      بالائی = c_fully_fold (بالائی, جھوٹ, تہی);

      اگر (c_parser_اگلا_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  زیریں_loc = بالائی_loc;
	  زیریں = بالائی;
	  بالائی_loc = c_parser_peek_token (parser)->location;
	  اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	  اظہاریہ = convert_lvalue_مقصد_rvalue (بالائی_loc, اظہاریہ, جھوٹ, سچ);
	  بالائی = اظہاریہ.قدر;
	  بالائی = c_fully_fold (بالائی, جھوٹ, تہی);
	}

      parens.skip_until_ملا_close (parser);

      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (بالائی))
	  || (زیریں && !INTEGRAL_TYPE_P (درخت_TYPE (زیریں))))
	{
	  c_parser_error (parser, "expected integer expression");
	  واپس list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (بالائی_loc, LE_اظہاریہ, boolean_type_گرہ, بالائی,
			   build_int_cst (درخت_TYPE (بالائی), 0));
      protected_سیٹ_اظہاریہ_location (c, بالائی_loc);
      اگر (c == boolean_true_گرہ)
	{
	  warning_at (بالائی_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  بالائی = integer_one_گرہ;
	}
      اگر (زیریں)
	{
	  c = fold_build2_loc (زیریں_loc, LE_اظہاریہ, boolean_type_گرہ, زیریں,
			       build_int_cst (درخت_TYPE (زیریں), 0));
	  protected_سیٹ_اظہاریہ_location (c, زیریں_loc);
	  اگر (c == boolean_true_گرہ)
	    {
	      warning_at (زیریں_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      زیریں = NULL_درخت;
	    }
	  ورنہ اگر (درخت_رمز (زیریں) == INTEGER_CST
		   && درخت_رمز (بالائی) == INTEGER_CST
		   && درخت_int_cst_lt (بالائی, زیریں))
	    {
	      warning_at (زیریں_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", زیریں, بالائی);
	      زیریں = NULL_درخت;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_عدد_TEAMS, "num_teams");

      c = build_omp_clause (عدد_teams_loc, OMP_CLAUSE_عدد_TEAMS);
      OMP_CLAUSE_عدد_TEAMS_بالائی_اظہاریہ (c) = بالائی;
      OMP_CLAUSE_عدد_TEAMS_زیریں_اظہاریہ (c) = زیریں;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  واپس list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

ساکن درخت
c_parser_omp_clause_thread_حد_بندی (c_parser *parser, درخت list)
{
  location_t عدد_thread_حد_بندی_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
      درخت c, t = اظہاریہ.قدر;
      t = c_fully_fold (t, جھوٹ, تہی);

      parens.skip_until_ملا_close (parser);

      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  واپس list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (اظہاریہ_loc, LE_اظہاریہ, boolean_type_گرہ, t,
			   build_int_cst (درخت_TYPE (t), 0));
      protected_سیٹ_اظہاریہ_location (c, اظہاریہ_loc);
      اگر (c == boolean_true_گرہ)
	{
	  warning_at (اظہاریہ_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_گرہ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_حد_بندی,
				 "thread_limit");

      c = build_omp_clause (عدد_thread_حد_بندی_loc, OMP_CLAUSE_THREAD_حد_بندی);
      OMP_CLAUSE_THREAD_حد_بندی_اظہاریہ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  واپس list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

ساکن درخت
c_parser_omp_clause_aligned (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl, c;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  اگر (c_parser_اگلا_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
      درخت alignment = اظہاریہ.قدر;
      alignment = c_fully_fold (alignment, جھوٹ, تہی);
      اگر (درخت_رمز (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (درخت_TYPE (alignment))
	  || درخت_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_درخت;
	}

      برائے (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_ملا_close (parser);
  واپس nl;
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

ساکن درخت
c_parser_omp_clause_allocate (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl, c;
  درخت allocator = NULL_درخت;
  درخت align = NULL_درخت;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  اگر ((c_parser_اگلا_token_is_not (parser, CPP_NAME)
       && c_parser_اگلا_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      منطقی has_modifiers = جھوٹ;
      درخت orig_type = NULL_درخت;
      اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  غیرعلامتی صحیح n = 3;
	  ثابت حرف *p
	    = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
	  اگر ((strcmp (p, "allocator") == 0 || strcmp (p, "align") == 0)
	      && c_parser_check_متوازن_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      اگر (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = سچ;
	      ورنہ اگر (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  ثابت حرف *q = IDENTIFIER_اشارہ_گر (tok->قدر);
		  n += 4;
		  اگر ((strcmp (q, "allocator") == 0
		       || strcmp (q, "align") == 0)
		      && c_parser_check_متوازن_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = سچ;
		}
	    }
	  اگر (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
	      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
	      اگر (اظہاریہ.قدر == error_mark_گرہ)
		;
	      ورنہ اگر (strcmp (p, "allocator") == 0)
		{
		  allocator = اظہاریہ.قدر;
		  allocator = c_fully_fold (allocator, جھوٹ, تہی);
		  orig_type = اظہاریہ.original_type
			      ? اظہاریہ.original_type : درخت_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      ورنہ
		{
		  align = اظہاریہ.قدر;
		  align = c_fully_fold (align, جھوٹ, تہی);
		}
	      parens2.skip_until_ملا_close (parser);
	      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  ثابت حرف *q = "";
		  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_اشارہ_گر (tok->قدر);
		  اگر (strcmp (q, "allocator") != 0 && strcmp (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_ملا_close (parser);
		      واپس list;
		    }
		  ورنہ اگر (strcmp (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_ملا_close (parser);
		      واپس list;
		    }
		  c_parser_consume_token (parser);
		  اگر (!parens2.require_open (parser))
		    {
		      parens.skip_until_ملا_close (parser);
		      واپس list;
		    }
		  اظہاریہ_loc = c_parser_peek_token (parser)->location;
		  اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
		  اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ,
						   سچ);
		  اگر (strcmp (q, "allocator") == 0)
		    {
		      allocator = اظہاریہ.قدر;
		      allocator = c_fully_fold (allocator, جھوٹ, تہی);
		      orig_type = اظہاریہ.original_type
				  ? اظہاریہ.original_type : درخت_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  ورنہ
		    {
		      align = اظہاریہ.قدر;
		      align = c_fully_fold (align, جھوٹ, تہی);
		    }
		  parens2.skip_until_ملا_close (parser);
		}
	    }
	}
      اگر (!has_modifiers)
	{
	  location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
	  c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	  اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
	  اگر (اظہاریہ.قدر != error_mark_گرہ)
	    {
	      allocator = اظہاریہ.قدر;
	      allocator = c_fully_fold (allocator, جھوٹ, تہی);
	      orig_type = اظہاریہ.original_type
			  ? اظہاریہ.original_type : درخت_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      اگر (allocator
	  && (!INTEGRAL_TYPE_P (درخت_TYPE (allocator))
	      || درخت_رمز (orig_type) != ENUMERAL_TYPE
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
	      || !درخت_سماتا_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_درخت;
	}
      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_ملا_close (parser);
	  واپس list;
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALLOCATE, list);

  اگر (allocator || align)
    برائے (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      {
	OMP_CLAUSE_ALLOCATE_ALLOCATOR (c) = allocator;
	OMP_CLAUSE_ALLOCATE_ALIGN (c) = align;
      }

  parens.skip_until_ملا_close (parser);
  واپس nl;
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

ساکن درخت
c_parser_omp_clause_استعمال_کرتا_allocators (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl = list;
  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

parse_اگلا:

  منطقی has_modifiers = جھوٹ;
  منطقی نظر_آیا_allocators = جھوٹ;
  درخت memspace_اظہاریہ = NULL_درخت;
  درخت traits_var = NULL_درخت;

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      غیرعلامتی صحیح n = 3;
      ثابت حرف *p
	= IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر ((strcmp (p, "traits") == 0 || strcmp (p, "memspace") == 0)
	  && c_parser_check_متوازن_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  اگر (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = سچ;
	  ورنہ اگر (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      ثابت حرف *q = IDENTIFIER_اشارہ_گر (tok->قدر);
	      n += 4;
	      اگر ((strcmp (q, "traits") == 0
		   || strcmp (q, "memspace") == 0)
		  && c_parser_check_متوازن_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  اگر (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = سچ;
		  اگر ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      ثابت حرف *m = IDENTIFIER_اشارہ_گر (tok->قدر);
		      اگر (strcmp (p, m) == 0 || strcmp (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  جاؤ انتہا;
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
	  c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	  اگر (اظہاریہ.قدر == error_mark_گرہ)
	    ;
	  ورنہ اگر (strcmp (p, "traits") == 0)
	    {
	      traits_var = اظہاریہ.قدر;
	      traits_var = c_fully_fold (traits_var, جھوٹ, تہی);
	      mark_exp_read (traits_var);
	    }
	  ورنہ
	    {
	      memspace_اظہاریہ = اظہاریہ.قدر;
	      memspace_اظہاریہ = c_fully_fold (memspace_اظہاریہ, جھوٹ, تہی);
	    }
	  parens2.skip_until_ملا_close (parser);
	  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      ثابت حرف *q = "";
	      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
		q = IDENTIFIER_اشارہ_گر (tok->قدر);
	      اگر (strcmp (q, "traits") != 0 && strcmp (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_ملا_close (parser);
		  واپس list;
		}
	      ورنہ اگر (strcmp (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_ملا_close (parser);
		  واپس list;
		}
	      c_parser_consume_token (parser);
	      اگر (!parens2.require_open (parser))
		{
		  parens.skip_until_ملا_close (parser);
		  واپس list;
		}
	      اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	      اگر (strcmp (q, "traits") == 0)
		{
		  traits_var = اظہاریہ.قدر;
		  traits_var = c_fully_fold (traits_var, جھوٹ, تہی);
		  mark_exp_read (traits_var);
		}
	      ورنہ
		{
		  memspace_اظہاریہ = اظہاریہ.قدر;
		  memspace_اظہاریہ = c_fully_fold (memspace_اظہاریہ, جھوٹ, تہی);
		}
	      parens2.skip_until_ملا_close (parser);
	    }
	  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    جاؤ انتہا;
	}
    }

  جب (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      ثابت حرف *tok_s = IDENTIFIER_اشارہ_گر (tok->قدر);
      درخت t = lookup_name (tok->قدر);
      اگر (t == NULL_درخت)
	{
	  undeclared_variable (tok->location, tok->قدر);
	  t = error_mark_گرہ;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      درخت legacy_traits = NULL_درخت;
      اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  ثابت حرف *tok_a
	    = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
	  c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_ملا_close (parser);

	  اگر (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      جاؤ انتہا;
	    }
	  legacy_traits = c_fully_fold (اظہاریہ.قدر, جھوٹ, تہی);
	  اگر (legacy_traits == error_mark_گرہ)
	    جاؤ انتہا;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  اگر (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.جوڑو_fixit_replace (alloc_loc, "traits");
	      richloc.جوڑو_fixit_داخل_کرو_after (close_loc, ": ");
	      richloc.جوڑو_fixit_داخل_کرو_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      اگر (نظر_آیا_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  جاؤ انتہا;
	}
      نظر_آیا_allocators = سچ;

      درخت c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_استعمال_کرتا_ALLOCATORS);
      OMP_CLAUSE_استعمال_کرتا_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_استعمال_کرتا_ALLOCATORS_MEMSPACE (c) = memspace_اظہاریہ;
      OMP_CLAUSE_استعمال_کرتا_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ورنہ
	توڑو;
    }

  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      جاؤ parse_اگلا;
    }

 انتہا:
  parens.skip_until_ملا_close (parser);
  واپس nl;
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

ساکن درخت
c_parser_omp_clause_خطی (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  درخت nl, c, قدم;
  شمار omp_clause_خطی_قسم قسم = OMP_CLAUSE_خطی_DEFAULT;
  منطقی old_خطی_modifier = جھوٹ;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (tok->قدر);
      اگر (strcmp ("val", p) == 0)
	قسم = OMP_CLAUSE_خطی_VAL;
      اگر (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	قسم = OMP_CLAUSE_خطی_DEFAULT;
      اگر (قسم != OMP_CLAUSE_خطی_DEFAULT)
	{
	  old_خطی_modifier = سچ;
	  rm1_loc = make_location (tok->location, tok->location,
				   c_parser_peek_2nd_token (parser)->location);
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_خطی, list);

  اگر (قسم != OMP_CLAUSE_خطی_DEFAULT)
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_ملا_close (parser);
    }

  اگر (c_parser_اگلا_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = اظہاریہ_loc;
      منطقی has_modifiers = جھوٹ;
      اگر (قسم == OMP_CLAUSE_خطی_DEFAULT
	  && c_parser_اگلا_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  ثابت حرف *p = IDENTIFIER_اشارہ_گر (tok->قدر);
	  غیرعلامتی صحیح pos = 0;
	  اگر (strcmp ("val", p) == 0)
	    pos = 2;
	  ورنہ اگر (strcmp ("step", p) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      pos = 3;
	      اگر (c_parser_check_متوازن_raw_token_sequence (parser, &pos)
		  && (c_parser_peek_nth_token_raw (parser, pos)->type
		      == CPP_CLOSE_PAREN))
		++pos;
	      ورنہ
		pos = 0;
	    }
	  اگر (pos)
	    {
	      tok = c_parser_peek_nth_token_raw (parser, pos);
	      اگر (tok->type == CPP_COMMA || tok->type == CPP_CLOSE_PAREN)
		has_modifiers = سچ;
	    }
	}
      اگر (has_modifiers)
	{
	  قدم = NULL_درخت;
	  جب (c_parser_اگلا_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      ثابت حرف *p = IDENTIFIER_اشارہ_گر (tok->قدر);
	      اگر (strcmp ("val", p) == 0)
		{
		  اگر (قسم != OMP_CLAUSE_خطی_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  قسم = OMP_CLAUSE_خطی_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      ورنہ اگر (strcmp ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  اگر (parens2.require_open (parser))
		    {
		      اگر (قدم)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      اظہاریہ_loc = c_parser_peek_token (parser)->location;
		      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
		      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ,
						       سچ);
		      قدم = c_fully_fold (اظہاریہ.قدر, جھوٹ, تہی);
		      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (قدم)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  قدم = integer_one_گرہ;
			}
		      parens2.skip_until_ملا_close (parser);
		    }
		  ورنہ
		    توڑو;
		}
	      ورنہ
		توڑو;
	      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  جاری;
		}
	      توڑو;
	    }
	  اگر (!قدم)
	    قدم = integer_one_گرہ;
	}
      ورنہ
	{
	  c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	  اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
	  قدم = c_fully_fold (اظہاریہ.قدر, جھوٹ, تہی);
	  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (قدم)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      قدم = integer_one_گرہ;
	    }
	}

    }
  ورنہ
    قدم = integer_one_گرہ;

  برائے (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_خطی_قدم (c) = قدم;
      OMP_CLAUSE_خطی_قسم (c) = قسم;
      OMP_CLAUSE_خطی_OLD_خطی_MODIFIER (c) = old_خطی_modifier;
    }

  اگر (old_خطی_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      اگر (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.جوڑو_fixit_remove (rm1_loc);
	  اگر (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.جوڑو_fixit_remove (rm2_loc);
	      richloc.جوڑو_fixit_داخل_کرو_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.جوڑو_fixit_داخل_کرو_before (close_loc, ")");
	    }
	  ورنہ
	    richloc.جوڑو_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_ملا_close (parser);
  واپس nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

ساکن درخت
c_parser_omp_clause_nontemporal (c_parser *parser, درخت list)
{
  واپس c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

ساکن درخت
c_parser_omp_clause_safelen (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت c, t;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
  c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
  اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
  t = اظہاریہ.قدر;
  t = c_fully_fold (t, جھوٹ, تہی);
  اگر (درخت_رمز (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (درخت_TYPE (t))
      || درخت_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_درخت;
    }

  parens.skip_until_ملا_close (parser);
  اگر (t == NULL_درخت || t == error_mark_گرہ)
    واپس list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_اظہاریہ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

ساکن درخت
c_parser_omp_clause_simdlen (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت c, t = NULL_درخت, type = NULL_درخت, مقسوم_علیہ = NULL_درخت;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  غیرعلامتی pos = 3;
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && strcmp (IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر),
		 "scaled") == 0
      && c_parser_check_متوازن_raw_token_sequence (parser, &pos)
      && c_parser_peek_nth_token_raw (parser, ++pos)->type == CPP_COLON)
    {
      c_parser_consume_token (parser);
      matching_parens parens2;
      parens2.require_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      ساخت c_type_name *ctype = c_parser_type_name (parser);
      اگر (ctype == تہی
	  || (type = groktypename (ctype, تہی, تہی)) == تہی
	  || (!INTEGRAL_TYPE_P (type)
	      && !SCALAR_FLOAT_TYPE_P (type)
	      && درخت_رمز (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_گرہ;
	}
      ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	  اظہاریہ = convert_lvalue_مقصد_rvalue (loc, اظہاریہ, جھوٹ, سچ);
	  مقسوم_علیہ = اظہاریہ.قدر;
	  مقسوم_علیہ = c_fully_fold (مقسوم_علیہ, جھوٹ, تہی);
	  اگر (درخت_رمز (مقسوم_علیہ) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (درخت_TYPE (مقسوم_علیہ))
	      || درخت_int_cst_sgn (مقسوم_علیہ) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_گرہ;
	    }
	}
      parens2.skip_until_ملا_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  اگر (type != error_mark_گرہ)
    {
      location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
      t = اظہاریہ.قدر;
      t = c_fully_fold (t, جھوٹ, تہی);
      اگر (درخت_رمز (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (درخت_TYPE (t))
	  || درخت_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_درخت;
	}
    }

  parens.skip_until_ملا_close (parser);
  اگر (type == error_mark_گرہ || t == NULL_درخت || t == error_mark_گرہ)
    واپس list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_اظہاریہ (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_مقسوم_علیہ (c) = مقسوم_علیہ;
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

ساکن درخت
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   درخت list, منطقی depend_p)
{
  درخت vec = تہی;
  اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_قسم != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      واپس list;
    }

  اگر (!depend_p)
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_نمبر
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  درخت val = c_parser_peek_nth_token (parser, 3)->قدر;
	  اگر (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      درخت u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_قسم (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      واپس u;
	    }
	}
    }



  جب (c_parser_اگلا_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_قسم == C_ID_ID)
    {
      درخت t = lookup_name (c_parser_peek_token (parser)->قدر);
      درخت addend = تہی;

      اگر (t == NULL_درخت)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->قدر);
	  t = error_mark_گرہ;
	}

      c_parser_consume_token (parser);

      منطقی neg = جھوٹ;
      اگر (c_parser_اگلا_token_is (parser, CPP_MINUS))
	neg = سچ;
      ورنہ اگر (!c_parser_اگلا_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_گرہ;
	  neg = جھوٹ;
	  جاؤ جوڑو_مقصد_سمتیہ;
	}
      c_parser_consume_token (parser);

      اگر (c_parser_اگلا_token_is_not (parser, CPP_نمبر))
	{
	  c_parser_error (parser, "expected integer");
	  واپس list;
	}

      addend = c_parser_peek_token (parser)->قدر;
      اگر (درخت_رمز (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  واپس list;
	}
      c_parser_consume_token (parser);

    جوڑو_مقصد_سمتیہ:
      اگر (t != error_mark_گرہ)
	{
	  vec = درخت_cons (addend, t, vec);
	  اگر (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      اگر (c_parser_اگلا_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_قسم != C_ID_ID)
	توڑو;

      c_parser_consume_token (parser);
    }

  اگر (vec == NULL_درخت)
    واپس list;

  درخت u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_قسم (u) = OMP_CLAUSE_DOACROSS_SINK;
  OMP_CLAUSE_DOACROSS_DEPEND (u) = depend_p;
  OMP_CLAUSE_DECL (u) = nreverse (vec);
  OMP_CLAUSE_CHAIN (u) = list;
  واپس u;
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

ساکن درخت
c_parser_omp_iterators (c_parser *parser)
{
  درخت ret = NULL_درخت, *آخری = &ret;
  c_parser_consume_token (parser);

  ڈالو_scope ();

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس error_mark_گرہ;

  کرو
    {
      درخت iter_type = NULL_درخت, type_اظہاریہ = NULL_درخت;
      اگر (c_parser_اگلا_علامات_آغاز_typename (parser, cla_prefer_id))
	{
	  ساخت c_type_name *type = c_parser_type_name (parser);
	  اگر (type != تہی)
	    iter_type = groktypename (type, &type_اظہاریہ, تہی);
	}
      اگر (iter_type == NULL_درخت)
	iter_type = integer_type_گرہ;

      location_t loc = c_parser_peek_token (parser)->location;
      اگر (!c_parser_اگلا_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  توڑو;
	}

      درخت id = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);

      اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	توڑو;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (eloc, اظہاریہ, سچ, جھوٹ);
      درخت begin = اظہاریہ.قدر;

      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	توڑو;

      eloc = c_parser_peek_token (parser)->location;
      اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (eloc, اظہاریہ, سچ, جھوٹ);
      درخت انتہا = اظہاریہ.قدر;

      درخت قدم = integer_one_گرہ;
      اگر (c_parser_اگلا_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	  اظہاریہ = convert_lvalue_مقصد_rvalue (eloc, اظہاریہ, سچ, جھوٹ);
	  قدم = اظہاریہ.قدر;
	}

      درخت iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *آخری = make_omp_iterator ();
      OMP_ITERATOR_VAR (*آخری) = iter_var;
      OMP_ITERATOR_BEGIN (*آخری) = begin;
      OMP_ITERATOR_انتہا (*آخری) = انتہا;
      OMP_ITERATOR_قدم (*آخری) = قدم;
      آخری = &درخت_CHAIN (*آخری);

      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  جاری;
	}
      توڑو;
    }
  جب (1);

  parens.skip_until_ملا_close (parser);
  واپس ret ? ret : error_mark_گرہ;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

ساکن درخت
c_parser_omp_clause_affinity (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl, iterators = NULL_درخت;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      منطقی parse_iter = ((strcmp ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      اگر (parse_iter)
	{
	  غیرعلامتی n = 3;
	  parse_iter = (c_parser_check_متوازن_raw_token_sequence (parser, &n)
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
		نکالو_scope ();
	      parens.skip_until_ملا_close (parser);
	      واپس list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  اگر (iterators)
    {
      درخت بلاک = نکالو_scope ();
      اگر (iterators != error_mark_گرہ)
	{
	  OMP_ITERATOR_بلاک (iterators) = بلاک;
	  برائے (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_درخت_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_ملا_close (parser);
  واپس nl;
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

ساکن درخت
c_parser_omp_clause_depend (c_parser *parser, درخت list, location_t یہاں)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  شمار omp_clause_depend_قسم قسم = OMP_CLAUSE_DEPEND_آخری;
  شمار omp_clause_doacross_قسم dkind = OMP_CLAUSE_DOACROSS_آخری;
  درخت nl, c, iterators = NULL_درخت;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  کرو
    {
      اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
	جاؤ invalid_قسم;

      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp ("iterator", p) == 0 && iterators == NULL_درخت)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  جاری;
	}
      اگر (strcmp ("in", p) == 0)
	قسم = OMP_CLAUSE_DEPEND_اندر;
      ورنہ اگر (strcmp ("inout", p) == 0)
	قسم = OMP_CLAUSE_DEPEND_INOUT;
      ورنہ اگر (strcmp ("inoutset", p) == 0)
	قسم = OMP_CLAUSE_DEPEND_INOUTSET;
      ورنہ اگر (strcmp ("mutexinoutset", p) == 0)
	قسم = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      ورنہ اگر (strcmp ("out", p) == 0)
	قسم = OMP_CLAUSE_DEPEND_برآمد;
      ورنہ اگر (strcmp ("depobj", p) == 0)
	قسم = OMP_CLAUSE_DEPEND_DEPOBJ;
      ورنہ اگر (strcmp ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.جوڑو_fixit_replace (یہاں, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      ورنہ اگر (strcmp ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.جوڑو_fixit_replace (یہاں, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_ماخذ;
	}
      ورنہ
	جاؤ invalid_قسم;
      توڑو;
    }
  جب (1);

  c_parser_consume_token (parser);

  اگر (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_ماخذ
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      نکالو_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_ماخذ ? "source" : "sink");
      iterators = NULL_درخت;
    }

  اگر (dkind == OMP_CLAUSE_DOACROSS_ماخذ)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_قسم (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_درخت;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_ملا_close (parser);
      واپس c;
    }

  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    جاؤ resync_fail;

  اگر (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, سچ);
  ورنہ
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      اگر (iterators)
	{
	  درخت بلاک = نکالو_scope ();
	  اگر (iterators == error_mark_گرہ)
	    iterators = NULL_درخت;
	  ورنہ
	    OMP_ITERATOR_بلاک (iterators) = بلاک;
	}

      برائے (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_قسم (c) = قسم;
	  اگر (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_درخت_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_ملا_close (parser);
  واپس nl;

 invalid_قسم:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_ملا_close (parser);
  اگر (iterators)
    نکالو_scope ();
  واپس list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

ساکن درخت
c_parser_omp_clause_doacross (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  شمار omp_clause_doacross_قسم قسم = OMP_CLAUSE_DOACROSS_آخری;
  درخت nl;
  ثابت حرف *p;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME))
    جاؤ invalid_قسم;

  p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
  اگر (strcmp ("sink", p) == 0)
    قسم = OMP_CLAUSE_DOACROSS_SINK;
  ورنہ اگر (strcmp ("source", p) == 0)
    قسم = OMP_CLAUSE_DOACROSS_ماخذ;
  ورنہ
    جاؤ invalid_قسم;

  c_parser_consume_token (parser);

  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    جاؤ resync_fail;

  اگر (قسم == OMP_CLAUSE_DOACROSS_ماخذ)
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
	  && strcmp (IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_قسم (nl) = OMP_CLAUSE_DOACROSS_ماخذ;
      OMP_CLAUSE_DECL (nl) = NULL_درخت;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  ورنہ
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, جھوٹ);

  parens.skip_until_ملا_close (parser);
  واپس nl;

 invalid_قسم:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_ملا_close (parser);
  واپس list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

ساکن درخت
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  شمار omp_clause_fallback_قسم قسم = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  غیرعلامتی n = 3;
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_متوازن_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  واپس list;
	}
      c_parser_consume_token (parser);
      اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	واپس list;
      p = "";
      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp (p, "abort") == 0)
	قسم = OMP_CLAUSE_FALLBACK_ABORT;
      ورنہ اگر (strcmp (p, "default_mem") == 0)
	قسم = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      ورنہ اگر (strcmp (p, "null") == 0)
	قسم = OMP_CLAUSE_FALLBACK_NULL;
      ورنہ
	{
	  c_parser_error (parser, "expected %<abort%>, %<default_mem%>, or "
				  "%<null%> as fallback mode");
	  واپس list;
	}
      c_parser_consume_token (parser);
      اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	واپس list;
      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	واپس list;
    }
  location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
  c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
  اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
  درخت سائز = c_fully_fold (اظہاریہ.قدر, جھوٹ, تہی);
  parens.skip_until_ملا_close (parser);

  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (سائز)))
    {
      error_at (اظہاریہ_loc, "expected integer expression");
      واپس list;
    }

  /* Attempt to statically determine when the number is negative.  */
  درخت c = fold_build2_loc (اظہاریہ_loc, LT_اظہاریہ, boolean_type_گرہ, سائز,
			    build_int_cst (درخت_TYPE (سائز), 0));
  protected_سیٹ_اظہاریہ_location (c, اظہاریہ_loc);
  اگر (c == boolean_true_گرہ)
    {
      warning_at (اظہاریہ_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      سائز = integer_zero_گرہ;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_قسم (c) = قسم;
  OMP_CLAUSE_DYN_GROUPPRIVATE_اظہاریہ (c) = سائز;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  واپس list;
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

ساکن درخت
c_parser_omp_clause_map (c_parser *parser, درخت list, منطقی declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl, c;
  شمار gomp_map_قسم قسم = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  صحیح pos = 1;
  صحیح map_قسم_pos = 0;
  صحیح iterator_لمبائی = 0;
  برائے (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      اگر (tok->type != CPP_NAME)
	توڑو;

      ثابت حرف *p = IDENTIFIER_اشارہ_گر (tok->قدر);
      c_token *اگلا_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      اگر (strcmp (p, "iterator") == 0 && اگلا_tok->type == CPP_OPEN_PAREN)
	{
	  غیرعلامتی n = pos + 2;
	  اگر (c_parser_check_متوازن_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_لمبائی = n - pos + 1;
	      pos = n;
	      اگلا_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      اگر (اگلا_tok->type == CPP_COLON)
	{
	  map_قسم_pos = pos;
	  توڑو;
	}

      اگر (اگلا_tok->type == CPP_COMMA)
	pos++;
      ورنہ اگر (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  غیرعلامتی صحیح npos = pos + 2;
	  اگر (c_parser_check_متوازن_raw_token_sequence (parser, &npos)
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
  صحیح عدد_commas = 0;
  صحیح عدد_identifiers = 0;
  درخت mapper_name = NULL_درخت;
  درخت iterators = NULL_درخت;
  برائے (صحیح pos = 1; pos < map_قسم_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      اگر (tok->type == CPP_COMMA)
	{
	  ++عدد_commas;
	  اگر (عدد_commas > عدد_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  جاری;
	}

      ثابت حرف *p = IDENTIFIER_اشارہ_گر (tok->قدر);
      اگر (strcmp ("always", p) == 0)
	{
	  اگر (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_ملا_close (parser);
	      واپس list;
	    }
	  always_modifier++;
	  c_parser_consume_token (parser);
	}
      ورنہ اگر (strcmp ("close", p) == 0)
	{
	  اگر (close_modifier)
	    {
	      c_parser_error (parser, "too many %<close%> modifiers");
	      parens.skip_until_ملا_close (parser);
	      واپس list;
	    }
	  close_modifier++;
	  c_parser_consume_token (parser);
	}
      ورنہ اگر (strcmp ("iterator", p) == 0)
	{
	  اگر (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_ملا_close (parser);
	      واپس list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_لمبائی - 1;
	}
      ورنہ اگر (strcmp ("mapper", p) == 0)
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
		  parens.skip_until_ملا_close (parser);
		  واپس list;
		}

	      tok = c_parser_peek_token (parser);

	      انتخاب (tok->type)
		{
		حالت CPP_NAME:
		  {
		    mapper_name = tok->قدر;
		    c_parser_consume_token (parser);
		    اگر (declare_mapper_p)
		      {
			error_at (tok->location,
				  "in %<declare mapper%> directives, parameter "
				  "to %<mapper%> modifier must be %<default%>");
		      }
		  }
		  توڑو;

		حالت CPP_KEYWORD:
		  اگر (tok->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      توڑو;
		    }
		  /* Fallthrough.  */

		طےشدہ:
		  error_at (tok->location,
			    "expected identifier or %<default%>");
		  واپس list;
		}

	      اگر (!mparens.require_close (parser))
		{
		  parens.skip_until_ملا_close (parser);
		  واپس list;
		}

	      mapper_modifier++;
	      pos += 3;
	    }
	}
      ورنہ اگر (strcmp ("present", p) == 0)
	{
	  اگر (present_modifier)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_ملا_close (parser);
	      واپس list;
	    }
	  present_modifier++;
	  c_parser_consume_token (parser);
	}
      ورنہ
	{
	  c_parser_error (parser, "%<map%> clause with map-type modifier other "
				  "than %<always%>, %<close%>, %<iterator%>, "
				  "%<mapper%> or %<present%>");
	  parens.skip_until_ملا_close (parser);
	  واپس list;
	}
      ++عدد_identifiers;
      اگر (عدد_identifiers - 1 > عدد_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.جوڑو_fixit_داخل_کرو_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      عدد_commas = عدد_identifiers - 1;
    }

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      صحیح always_present_modifier = always_modifier && present_modifier;

      اگر (strcmp ("alloc", p) == 0)
	قسم = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      ورنہ اگر (strcmp ("to", p) == 0)
	قسم = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_مقصد
		: present_modifier ? GOMP_MAP_PRESENT_مقصد
		: always_modifier ? GOMP_MAP_ALWAYS_مقصد
		: GOMP_MAP_مقصد);
      ورنہ اگر (strcmp ("from", p) == 0)
	قسم = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      ورنہ اگر (strcmp ("tofrom", p) == 0)
	قسم = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      ورنہ اگر (strcmp ("release", p) == 0)
	قسم = GOMP_MAP_RELEASE;
      ورنہ اگر (strcmp ("delete", p) == 0)
	قسم = GOMP_MAP_DELETE;
      ورنہ
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  واپس list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   سچ);

  درخت آخری_new = NULL_درخت;

  اگر (iterators)
    {
      درخت بلاک = نکالو_scope ();
      اگر (iterators == error_mark_گرہ)
	iterators = NULL_درخت;
      ورنہ
	OMP_ITERATOR_بلاک (iterators) = بلاک;
    }

  برائے (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_سیٹ_MAP_قسم (c, قسم);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      آخری_new = c;
    }

  اگر (mapper_name)
    {
      درخت name = build_omp_clause (داخلہ_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_سیٹ_MAP_قسم (name, GOMP_MAP_ڈالو_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (آخری_new);

      name = build_omp_clause (داخلہ_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_سیٹ_MAP_قسم (name, GOMP_MAP_نکالو_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_اشارہ_گر_گرہ;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (آخری_new);
      OMP_CLAUSE_CHAIN (آخری_new) = name;
    }

  parens.skip_until_ملا_close (parser);
  واپس nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

ساکن درخت
c_parser_omp_clause_device (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t اظہاریہ_loc;
  c_اظہاریہ اظہاریہ;
  درخت c, t;
  منطقی ancestor = جھوٹ;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (tok->قدر);
      اگر (strcmp ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  اگر ((omp_requires_نقاب & OMP_REQUIRES_الٹ_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_ملا_close (parser);
	      واپس list;
	    }
	  ancestor = سچ;
	}
      ورنہ اگر (strcmp ("device_num", p) == 0)
	;
      ورنہ
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_ملا_close (parser);
	  واپس list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  اظہاریہ_loc = c_parser_peek_token (parser)->location;
  اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
  اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
  t = اظہاریہ.قدر;
  t = c_fully_fold (t, جھوٹ, تہی);

  parens.skip_until_ملا_close (parser);

  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      واپس list;
    }
  اگر (ancestor && درخت_رمز (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (اظہاریہ_loc, "the %<device%> clause expression must evaluate to "
			  "%<1%>");
      واپس list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE, "device");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE);

  OMP_CLAUSE_DEVICE_ID (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEVICE_ANCESTOR (c) = ancestor;

  list = c;
  واپس list;
}

/* OpenMP 4.0:
   dist_schedule ( static )
   dist_schedule ( static , expression ) */

ساکن درخت
c_parser_omp_clause_dist_جدول_وقت (c_parser *parser, درخت list)
{
  درخت c, t = NULL_درخت;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  اگر (!c_parser_اگلا_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      واپس list;
    }

  c_parser_consume_token (parser);
  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
      t = اظہاریہ.قدر;
      t = c_fully_fold (t, جھوٹ, تہی);
      parens.skip_until_ملا_close (parser);
    }
  ورنہ
    c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  اگر (omp_ڈھونڈو_clause (list, OMP_CLAUSE_DIST_جدول_وقت))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  اگر (t == error_mark_گرہ)
    واپس list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_جدول_وقت);
  OMP_CLAUSE_DIST_جدول_وقت_CHUNK_اظہاریہ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

ساکن درخت
c_parser_omp_clause_proc_bind (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  شمار omp_clause_proc_bind_قسم قسم;
  درخت c;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp ("primary", p) == 0)
	قسم = OMP_CLAUSE_PROC_BIND_PRIMARY;
      ورنہ اگر (strcmp ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.جوڑو_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  قسم = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      ورنہ اگر (strcmp ("close", p) == 0)
	قسم = OMP_CLAUSE_PROC_BIND_CLOSE;
      ورنہ اگر (strcmp ("spread", p) == 0)
	قسم = OMP_CLAUSE_PROC_BIND_پھیلاؤ;
      ورنہ
	جاؤ invalid_قسم;
    }
  ورنہ
    جاؤ invalid_قسم;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_ملا_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_قسم (c) = قسم;
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;

 invalid_قسم:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_ملا_close (parser);
  واپس list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

ساکن درخت
c_parser_omp_clause_device_type (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  شمار omp_clause_device_type_قسم قسم;
  درخت c;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp ("host", p) == 0)
	قسم = OMP_CLAUSE_DEVICE_TYPE_HOST;
      ورنہ اگر (strcmp ("nohost", p) == 0)
	قسم = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      ورنہ اگر (strcmp ("any", p) == 0)
	قسم = OMP_CLAUSE_DEVICE_TYPE_ANY;
      ورنہ
	جاؤ invalid_قسم;
    }
  ورنہ
    جاؤ invalid_قسم;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_ملا_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_قسم (c) = قسم;
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;

 invalid_قسم:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_ملا_close (parser);
  واپس list;
}

/* OpenMP 4.0:
   from ( variable-list )
   to ( variable-list )

   OpenMP 5.1:
   from ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )
   to ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )

   motion-modifier:
     present | iterator (iterators-definition) | mapper (id)  */

ساکن درخت
c_parser_omp_clause_from_مقصد (c_parser *parser, شمار omp_clause_رمز قسم,
			     درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  صحیح pos = 1, colon_pos = 0;
  صحیح iterator_لمبائی = 0;

  جب (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      ثابت حرف *identifier =
	IDENTIFIER_اشارہ_گر (c_parser_peek_nth_token_raw (parser, pos)->قدر);
      اگر (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  غیرعلامتی صحیح npos = pos + 2;
	  اگر (c_parser_check_متوازن_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      اگر (strcmp (identifier, "iterator") == 0)
		iterator_لمبائی = npos - pos + 1;
	      pos = npos;
	    }
	}
      اگر (c_parser_peek_nth_token_raw (parser, pos + 1)->type == CPP_COMMA)
	pos += 2;
      ورنہ
	pos++;
      اگر (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_COLON)
	{
	  colon_pos = pos;
	  توڑو;
	}
    }

  منطقی present = جھوٹ, mapper_modifier = جھوٹ;
  درخت iterators = NULL_درخت;
  درخت mapper_name = NULL_درخت;

  برائے (صحیح pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  جاری;
	}
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (token->قدر);
      اگر (strcmp ("present", p) == 0)
	{
	  اگر (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_ملا_close (parser);
	      واپس list;
	    }
	  present = سچ;
	  c_parser_consume_token (parser);
	}
      ورنہ اگر (strcmp ("iterator", p) == 0)
	{
	  اگر (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_ملا_close (parser);
	      واپس list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_لمبائی - 1;
	}
      ورنہ اگر (strcmp ("mapper", p) == 0)
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
		  parens.skip_until_ملا_close (parser);
		  واپس list;
		}

	      token = c_parser_peek_token (parser);
	      انتخاب (token->type)
		{
		حالت CPP_NAME:
		  {
		    mapper_name = token->قدر;
		    c_parser_consume_token (parser);
		  }
		  توڑو;
		حالت CPP_KEYWORD:
		  اگر (token->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      توڑو;
		    }
		  /* FALLTHROUGH  */
		طےشدہ:
		  error_at (token->location,
			    "expected identifier or %<default%>");
		  واپس list;
		}
	      اگر (!mparens.require_close (parser))
		{
		  parens.skip_until_ملا_close (parser);
		  واپس list;
		}
	      mapper_modifier = سچ;
	      pos += 3;
	    }
	}
      ورنہ
	{
	  error_at (token->location,
		    "%qs clause with modifier other than %<iterator%>, "
		    "%<mapper%>, or %<present%>",
		    قسم == OMP_CLAUSE_مقصد ? "to" : "from");
	  parens.skip_until_ملا_close (parser);
	  واپس list;
	}
    }

  اگر (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  درخت nl = c_parser_omp_variable_list (parser, loc, قسم, list);
  parens.skip_until_ملا_close (parser);

  اگر (present)
    برائے (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  اگر (iterators)
    {
      درخت بلاک = نکالو_scope ();
      اگر (iterators == error_mark_گرہ)
	iterators = NULL_درخت;
      ورنہ
	OMP_ITERATOR_بلاک (iterators) = بلاک;
    }

  اگر (iterators)
    برائے (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  اگر (mapper_name)
    {
      درخت آخری_new = NULL_درخت;
      برائے (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	آخری_new = c;

      درخت name = build_omp_clause (داخلہ_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_سیٹ_MAP_قسم (name, GOMP_MAP_ڈالو_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (آخری_new);

      name = build_omp_clause (داخلہ_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_سیٹ_MAP_قسم (name, GOMP_MAP_نکالو_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_اشارہ_گر_گرہ;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (آخری_new);
      OMP_CLAUSE_CHAIN (آخری_new) = name;
    }

  واپس nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

ساکن درخت
c_parser_omp_clause_یکساں (c_parser *parser, درخت list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_یکساں,
					 list);
      parens.skip_until_ملا_close (parser);
    }
  واپس list;
}

/* OpenMP 5.1
بھرا*/

ساکن درخت
c_parser_omp_clause_بھرا (c_parser *parser, درخت list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_بھرا, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  درخت c = build_omp_clause (loc, OMP_CLAUSE_بھرا);
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

ساکن درخت
c_parser_omp_clause_partial (c_parser *parser, درخت list)
{
  درخت عدد = NULL_درخت;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      عدد = c_parser_اظہاریہ_no_commas (parser, تہی).قدر;
      parens.skip_until_ملا_close (parser);

      اگر (عدد == error_mark_گرہ)
	واپس list;

      mark_exp_read (عدد);
      عدد = c_fully_fold (عدد, جھوٹ, تہی);
      HOST_WIDE_INT n;
      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (عدد))
	  || !درخت_سماتا_shwi_p (عدد)
	  || (n = درخت_مقصد_shwi (عدد)) <= 0
	  || (صحیح) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  واپس list;
	}
    }

  درخت c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_اظہاریہ (c) = عدد;
  OMP_CLAUSE_CHAIN (c) = list;
  واپس c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

ساکن درخت
c_parser_omp_clause_novariants (c_parser *parser, درخت list)
{
  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
  درخت t = convert_lvalue_مقصد_rvalue (loc, اظہاریہ, سچ, سچ).قدر;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, جھوٹ, تہی);
  parens.skip_until_ملا_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  درخت c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_اظہاریہ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  واپس list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

ساکن درخت
c_parser_omp_clause_nocontext (c_parser *parser, درخت list)
{
  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
  درخت t = convert_lvalue_مقصد_rvalue (loc, اظہاریہ, سچ, سچ).قدر;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, جھوٹ, تہی);
  parens.skip_until_ملا_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  درخت c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_اظہاریہ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  واپس list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

ساکن درخت
c_parser_omp_clause_detach (c_parser *parser, درخت list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  اگر (!parens.require_open (parser))
    واپس list;

  اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_قسم != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_ملا_close (parser);
      واپس list;
    }

  درخت t = lookup_name (c_parser_peek_token (parser)->قدر);
  اگر (t == NULL_درخت)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->قدر);
      parens.skip_until_ملا_close (parser);
      واپس list;
    }
  c_parser_consume_token (parser);

  درخت type = TYPE_MAIN_VARIANT (درخت_TYPE (t));
  اگر (!INTEGRAL_TYPE_P (type)
      || درخت_رمز (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_ملا_close (parser);
      واپس list;
    }

  درخت u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_ملا_close (parser);
  واپس u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

ساکن درخت
c_parser_omp_clause_destroy (c_parser *parser, درخت list)
{
  درخت nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  برائے (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    درخت_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
  واپس nl;
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

ساکن درخت
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    واپس error_mark_گرہ;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  اگر (!c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
    جب (سچ)
      {
	str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
	اگر (c_parser_اگلا_token_is (parser, CPP_STRING))
	  {
	    c_اظہاریہ cval = c_parser_string_literal (parser, جھوٹ, جھوٹ);
	    اگر (cval.قدر == error_mark_گرہ)
	      واپس error_mark_گرہ;
	    اگر ((سائز_t) درخت_STRING_لمبائی (cval.قدر)
		!= لڑی_لمبائی (درخت_STRING_اشارہ_گر (cval.قدر)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = سچ;
		واپس error_mark_گرہ;
	      }

	    حرف c = omp_get_fr_id_from_name (درخت_STRING_اشارہ_گر (cval.قدر));
	    اگر (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  درخت_STRING_اشارہ_گر (cval.قدر));
	    str += c;
	  }
	ورنہ
	  {
	    c_اظہاریہ cval = c_parser_اظہاریہ_no_commas (parser, تہی);
	    درخت قدر = c_fully_fold (cval.قدر, جھوٹ, تہی);
	    اگر (INTEGRAL_TYPE_P (درخت_TYPE (قدر))
		&& درخت_رمز (قدر) != INTEGER_CST)
	      قدر = convert_lvalue_مقصد_rvalue (cval.get_آغاز (), cval,
						جھوٹ, سچ).قدر;
	    اگر (درخت_رمز (قدر) != INTEGER_CST
		|| !درخت_سماتا_shwi_p (قدر))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		واپس error_mark_گرہ;
	      }
	    HOST_WIDE_INT n = درخت_مقصد_shwi (قدر);
	    اگر (n < 1 || n > GOMP_INTEROP_IFR_آخری)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (حرف) n;
	  }
	str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    جاری;
	  }
	اگر (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  واپس error_mark_گرہ;
	str += '\0';
	درخت res = build_string (str.لمبائی (), str.ڈیٹا ());
	درخت_TYPE (res) = build_array_type_nelts (unsigned_char_type_گرہ,
						  str.لمبائی ());
	واپس res;
      }

  /* New format. */
  std::string str2;
  جب (سچ)
    {
      اگر (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	واپس error_mark_گرہ;
      str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
      str2.clear ();
      منطقی has_fr = جھوٹ;
      جب (سچ)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  اگر (tok->type != CPP_NAME
	      || (strcmp("fr", IDENTIFIER_اشارہ_گر (tok->قدر)) != 0
		  && strcmp("attr", IDENTIFIER_اشارہ_گر (tok->قدر)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      واپس error_mark_گرہ;
	    }
	  c_parser_consume_token (parser);
	  منطقی is_fr = IDENTIFIER_اشارہ_گر (tok->قدر)[0] == 'f';
	  اگر (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      واپس error_mark_گرہ;
	    }
	  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    واپس error_mark_گرہ;
	  جب (سچ)
	    {
	      اگر (c_parser_اگلا_token_is (parser, CPP_STRING))
		{
		  c_اظہاریہ cval = c_parser_string_literal (parser, جھوٹ, جھوٹ);
		  درخت قدر = cval.قدر;
		  اگر (قدر == error_mark_گرہ)
		    واپس error_mark_گرہ;
		  اگر ((سائز_t) درخت_STRING_لمبائی (قدر)
		      != لڑی_لمبائی (درخت_STRING_اشارہ_گر (قدر)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = سچ;
		      واپس error_mark_گرہ;
		    }
		  اگر (!is_fr)
		    {
		      اگر (!startswith (درخت_STRING_اشارہ_گر (قدر), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = سچ;
			  واپس error_mark_گرہ;
			}
		      اگر (strchr (درخت_STRING_اشارہ_گر (قدر), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = سچ;
			  واپس error_mark_گرہ;
			}
		      str2 += درخت_STRING_اشارہ_گر (قدر);
		      str2 += '\0';
		    }
		  ورنہ
		    {
		      اگر (*درخت_STRING_اشارہ_گر (قدر) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  واپس error_mark_گرہ;
			}
		      حرف c = omp_get_fr_id_from_name (درخت_STRING_اشارہ_گر (قدر));
		      اگر (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    درخت_STRING_اشارہ_گر (قدر));
		     str += c;
		     has_fr = سچ;
		    }
		}
	      ورنہ اگر (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  واپس error_mark_گرہ;
		}
	      ورنہ
		{
		  c_اظہاریہ cval = c_parser_اظہاریہ_no_commas (parser, تہی);
		  درخت قدر = c_fully_fold (cval.قدر, جھوٹ, تہی);
		  اگر (INTEGRAL_TYPE_P (درخت_TYPE (قدر))
		      && درخت_رمز (قدر) != INTEGER_CST)
		    قدر = convert_lvalue_مقصد_rvalue (cval.get_آغاز (), cval,
						      جھوٹ, سچ).قدر;

		  اگر (درخت_رمز (قدر) != INTEGER_CST
		      || !درخت_سماتا_shwi_p (قدر))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      واپس error_mark_گرہ;
		    }
		  HOST_WIDE_INT n = درخت_مقصد_shwi (قدر);
		  اگر (n < 1 || n > GOMP_INTEROP_IFR_آخری)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (حرف) n;
		  has_fr = سچ;
		}
	      اگر (!is_fr
		  && c_parser_اگلا_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  جاری;
		}
	      اگر (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		واپس error_mark_گرہ;
	      توڑو;
	    }
	  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      جاری;
	    }
	  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
	    توڑو;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  واپس error_mark_گرہ;
	}
      str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	توڑو;
      اگر (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	واپس error_mark_گرہ;
    }
  c_parser_consume_token (parser);
  str += '\0';
  درخت res = build_string (str.لمبائی (), str.ڈیٹا ());
  درخت_TYPE (res) = build_array_type_nelts (unsigned_char_type_گرہ,
						  str.لمبائی ());
  واپس res;
}

/* OpenMP 5.1
     modifiers of the 'init' clause, used by the 'init' and the
     'append_args' clauses.

   Modifiers:
ہدف
     targetsync
     prefer_type (preference-specification)

  Returns 'false' if an error has been issued.  */

ساکن منطقی
c_parser_omp_clause_init_modifiers (c_parser *parser, منطقی *ہدف,
				    منطقی *targetsync, درخت *prefer_type_درخت)
{
  *ہدف = جھوٹ;
  *targetsync = جھوٹ;
  *prefer_type_درخت = NULL_درخت;

  کرو
    {
      c_token *tok = c_parser_peek_token (parser);
      اگر (tok->type != CPP_NAME)
	جاؤ fail;
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (tok->قدر);
      اگر (strcmp ("targetsync", p) == 0)
	{
	  اگر (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = سچ;
	  c_parser_consume_token (parser);
	}
      ورنہ اگر (strcmp ("target", p) == 0)
	{
	  اگر (*ہدف)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *ہدف = سچ;
	  c_parser_consume_token (parser);
	}
      ورنہ اگر (strcmp ("prefer_type", p) == 0)
	{
	  اگر (*prefer_type_درخت != NULL_درخت)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_درخت = c_parser_omp_modifier_prefer_type (parser);
	  اگر (*prefer_type_درخت == error_mark_گرہ)
	    واپس جھوٹ;
	}
      ورنہ
	جاؤ fail;
      tok = c_parser_peek_token (parser);
      اگر (tok->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  جاری;
	}
      /* Unknown token - either done or an error; handle it in the caller.  */
      واپس سچ;
    }
  جب (سچ);

fail:
  c_parser_error (parser,
		  "expected %<prefer_type%>, %<target%>, or %<targetsync%>");
  واپس جھوٹ;
}

/* OpenMP 5.1:
   init ( [init-modifier-list : ] variable-list )

   Modifiers:
ہدف
     targetsync
     prefer_type (preference-specification) */

ساکن درخت
c_parser_omp_clause_init (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس list;

  منطقی ہدف = جھوٹ;
  منطقی targetsync = جھوٹ;
  درخت prefer_type_درخت = NULL_درخت;

  اگر (!c_parser_omp_clause_init_modifiers (parser, &ہدف, &targetsync,
					   &prefer_type_درخت)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      اگر (prefer_type_درخت != error_mark_گرہ)
	parens.skip_until_ملا_close (parser);
      واپس list;
    }

  اگر (!ہدف && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  درخت nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					جھوٹ);
  parens.skip_until_ملا_close (parser);

  برائے (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      درخت_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      اگر (ہدف)
	OMP_CLAUSE_INIT_ہدف (c) = 1;
      اگر (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      اگر (prefer_type_درخت)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_درخت;
    }
  واپس nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

ساکن درخت
c_parser_omp_clause_use (c_parser *parser, درخت list)
{
  واپس c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

ساکن درخت
c_parser_omp_clause_interop (c_parser *parser, درخت list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  درخت nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  برائے (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      درخت_مستعمل (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  واپس nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

ساکن درخت
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_نقاب نقاب,
			   ثابت حرف *where, منطقی اختتام_p = سچ,
			   منطقی ہدف_p = جھوٹ)
{
  درخت clauses = تہی;
  منطقی پہلا = سچ;

  جب (c_parser_اگلا_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t یہاں;
      pragma_omp_clause c_قسم;
      ثابت حرف *c_name;
      درخت پچھلا = clauses;

      اگر (!پہلا && c_parser_اگلا_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      یہاں = c_parser_peek_token (parser)->location;
      c_قسم = c_parser_omp_clause_name (parser);

      انتخاب (c_قسم)
	{
	حالت PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (یہاں, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_ڈیٹا_clause (parser, c_قسم, clauses);
	  c_name = "attach";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_ڈیٹا_clause (parser, c_قسم, clauses);
	  c_name = "copy";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_ڈیٹا_clause (parser, c_قسم, clauses);
	  c_name = "copyin";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_ڈیٹا_clause (parser, c_قسم, clauses);
	  c_name = "copyout";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_ڈیٹا_clause (parser, c_قسم, clauses);
	  c_name = "create";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_ڈیٹا_clause (parser, c_قسم, clauses);
	  c_name = "delete";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, سچ);
	  c_name = "default";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_ڈیٹا_clause (parser, c_قسم, clauses);
	  c_name = "detach";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_ڈیٹا_clause (parser, c_قسم, clauses);
	  c_name = "device";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_ڈیٹا_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_ڈیٹا_clause (parser, c_قسم, clauses);
	  c_name = "device_resident";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (یہاں, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, یہاں, OMP_CLAUSE_GANG,
						c_name, clauses);
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_ڈیٹا_clause (parser, c_قسم, clauses);
	  c_name = "host";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, جھوٹ);
	  c_name = "if";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (یہاں, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (یہاں, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_ڈیٹا_clause (parser, c_قسم, clauses);
	  c_name = "link";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_ڈیٹا_clause (parser, c_قسم, clauses);
	  c_name = "no_create";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (یہاں, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_عدد_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_عدد_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_عدد_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_عدد_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_ڈیٹا_clause (parser, c_قسم, clauses);
	  c_name = "present";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_نجی:
	  clauses = c_parser_omp_clause_نجی (parser, clauses);
	  c_name = "private";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     جھوٹ, clauses);
	  c_name = "reduction";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_SELF:
	  اگر ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  ورنہ
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_ڈیٹا_clause (parser, c_قسم, clauses);
	  c_name = "self";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (یہاں, OMP_CLAUSE_SEQ,
						 clauses);
	  c_name = "seq";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_TILE:
	  clauses = c_parser_oacc_clause_tile (parser, clauses);
	  c_name = "tile";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_USE_DEVICE:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_سمتیہ:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, یہاں, OMP_CLAUSE_سمتیہ,
						c_name,	clauses);
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_سمتیہ_لمبائی:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_سمتیہ_لمبائی,
						     clauses);
	  c_name = "vector_length";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  توڑو;
	حالت PRAGMA_OACC_CLAUSE_کارکن:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, یہاں, OMP_CLAUSE_کارکن,
						c_name, clauses);
	  توڑو;
	طےشدہ:
	  c_parser_error (parser, "expected an OpenACC clause");
	  جاؤ saw_error;
	}

      پہلا = جھوٹ;

      اگر (((نقاب >> c_قسم) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = پچھلا;
	  error_at (یہاں, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_مقصد_pragma_eol (parser);

  اگر (اختتام_p)
    واپس c_اختتام_omp_clauses (clauses, ہدف_p ? C_ORT_ACC_ہدف
						   : C_ORT_ACC);

  واپس clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

ساکن درخت
c_parser_omp_all_clauses (c_parser *parser, omp_clause_نقاب نقاب,
			  ثابت حرف *where, منطقی اختتام_p = سچ,
			  صحیح nested = 0)
{
  درخت clauses = تہی;
  منطقی پہلا = سچ;

  جب (c_parser_اگلا_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t یہاں;
      pragma_omp_clause c_قسم;
      ثابت حرف *c_name;
      درخت پچھلا = clauses;

      اگر (nested && c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	توڑو;

      اگر (!پہلا || nested != 2)
	{
	  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ورنہ اگر (nested == 2)
	    error_at (c_parser_peek_token (parser)->location,
		      "clauses in %<simd%> trait should be separated "
		      "by %<,%>");
	}

      یہاں = c_parser_peek_token (parser)->location;
      c_قسم = c_parser_omp_clause_name (parser);

      انتخاب (c_قسم)
	{
	حالت PRAGMA_OMP_CLAUSE_BIND:
	  clauses = c_parser_omp_clause_bind (parser, clauses);
	  c_name = "bind";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, جھوٹ);
	  c_name = "default";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_DETACH:
	  clauses = c_parser_omp_clause_detach (parser, clauses);
	  c_name = "detach";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_FILTER:
	  clauses = c_parser_omp_clause_filter (parser, clauses);
	  c_name = "filter";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_FINAL:
	  clauses = c_parser_omp_clause_final (parser, clauses);
	  c_name = "final";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_GRAINSIZE:
	  clauses = c_parser_omp_clause_grainsize (parser, clauses);
	  c_name = "grainsize";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_HINT:
	  clauses = c_parser_omp_clause_hint (parser, clauses);
	  c_name = "hint";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_DEFAULTMAP:
	  clauses = c_parser_omp_clause_defaultmap (parser, clauses);
	  c_name = "defaultmap";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, سچ);
	  c_name = "if";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_اندر_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_اندر_REDUCTION,
					     سچ, clauses);
	  c_name = "in_reduction";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_بالواسطہ:
	  clauses = c_parser_omp_clause_بالواسطہ (parser, clauses);
	  c_name = "indirect";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_MERGEABLE:
	  clauses = c_parser_omp_clause_mergeable (parser, clauses);
	  c_name = "mergeable";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_عدد_TASKS:
	  clauses = c_parser_omp_clause_عدد_tasks (parser, clauses);
	  c_name = "num_tasks";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_عدد_دھاگے:
	  clauses = c_parser_omp_clause_عدد_دھاگے (parser, clauses);
	  c_name = "num_threads";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_ترتیب:
	  clauses = c_parser_omp_clause_ترتیب (parser, clauses);
	  c_name = "order";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_ترجیح:
	  clauses = c_parser_omp_clause_ترجیح (parser, clauses);
	  c_name = "priority";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_نجی:
	  clauses = c_parser_omp_clause_نجی (parser, clauses);
	  c_name = "private";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     سچ, clauses);
	  c_name = "reduction";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_جدول_وقت:
	  clauses = c_parser_omp_clause_جدول_وقت (parser, clauses);
	  c_name = "schedule";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     سچ, clauses);
	  c_name = "task_reduction";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_UNTIED:
	  clauses = c_parser_omp_clause_untied (parser, clauses);
	  c_name = "untied";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_INBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_INBRANCH,
						clauses);
	  c_name = "inbranch";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_NONTEMPORAL:
	  clauses = c_parser_omp_clause_nontemporal (parser, clauses);
	  c_name = "nontemporal";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_NOTINBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_NOTINBRANCH,
						clauses);
	  c_name = "notinbranch";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_PARALLEL:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_PARALLEL,
					      clauses);
	  c_name = "parallel";
	  اگر (!پہلا)
	    {
	     clause_not_پہلا:
	      error_at (یہاں, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = پچھلا;
	    }
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  اگر (!پہلا)
	    جاؤ clause_not_پہلا;
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  اگر (!پہلا)
	    جاؤ clause_not_پہلا;
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  اگر (!پہلا)
	    جاؤ clause_not_پہلا;
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_LINK:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LINK, clauses);
	  c_name = "link";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_LOCAL:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LOCAL, clauses);
	  c_name = "local";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_مقصد:
	  اگر ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (یہاں);
	      richloc.جوڑو_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      درخت nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      برائے (درخت c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_مقصد (c) = 1;
	      clauses = nl;
	    }
	  ورنہ
	    clauses = c_parser_omp_clause_from_مقصد (parser, OMP_CLAUSE_مقصد,
						   clauses);
	  c_name = "to";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_مقصد (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_یکساں:
	  clauses = c_parser_omp_clause_یکساں (parser, clauses);
	  c_name = "uniform";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_عدد_TEAMS:
	  clauses = c_parser_omp_clause_عدد_teams (parser, clauses);
	  c_name = "num_teams";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_THREAD_حد_بندی:
	  clauses = c_parser_omp_clause_thread_حد_بندی (parser, clauses);
	  c_name = "thread_limit";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_ALIGNED:
	  clauses = c_parser_omp_clause_aligned (parser, clauses);
	  c_name = "aligned";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_ALLOCATE:
	  clauses = c_parser_omp_clause_allocate (parser, clauses);
	  c_name = "allocate";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_خطی:
	  clauses = c_parser_omp_clause_خطی (parser, clauses);
	  c_name = "linear";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_استعمال_کرتا_ALLOCATORS:
	  clauses = c_parser_omp_clause_استعمال_کرتا_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, یہاں);
	  c_name = "depend";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_DOACROSS:
	  clauses = c_parser_omp_clause_doacross (parser, clauses);
	  c_name = "doacross";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_DESTROY:
	  clauses = c_parser_omp_clause_destroy (parser, clauses);
	  c_name = "destroy";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE:
	  clauses = c_parser_omp_clause_dyn_groupprivate (parser, clauses);
	  c_name = "dyn_groupprivate";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_INIT:
	  clauses = c_parser_omp_clause_init (parser, clauses);
	  c_name = "init";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_USE:
	  clauses = c_parser_omp_clause_use (parser, clauses);
	  c_name = "use";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_INTEROP:
	  clauses = c_parser_omp_clause_interop (parser, clauses);
	  c_name = "interop";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_MAP:
	  clauses = c_parser_omp_clause_map (parser, clauses, جھوٹ);
	  c_name = "map";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device_ptr";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_use_device_addr (parser, clauses);
	  c_name = "use_device_addr";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_has_device_addr (parser, clauses);
	  c_name = "has_device_addr";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR:
	  clauses = c_parser_omp_clause_is_device_ptr (parser, clauses);
	  c_name = "is_device_ptr";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_DEVICE:
	  clauses = c_parser_omp_clause_device (parser, clauses);
	  c_name = "device";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_DIST_جدول_وقت:
	  clauses = c_parser_omp_clause_dist_جدول_وقت (parser, clauses);
	  c_name = "dist_schedule";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_PROC_BIND:
	  clauses = c_parser_omp_clause_proc_bind (parser, clauses);
	  c_name = "proc_bind";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_DEVICE_TYPE:
	  clauses = c_parser_omp_clause_device_type (parser, clauses);
	  c_name = "device_type";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_SAFELEN:
	  clauses = c_parser_omp_clause_safelen (parser, clauses);
	  c_name = "safelen";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_SIMDLEN:
	  clauses = c_parser_omp_clause_simdlen (parser, clauses);
	  c_name = "simdlen";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_NOGROUP:
	  clauses = c_parser_omp_clause_nogroup (parser, clauses);
	  c_name = "nogroup";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_دھاگے:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_دھاگے,
					       clauses);
	  c_name = "threads";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_SIMD:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_SIMD,
					       clauses);
	  c_name = "simd";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_ENTER:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					    clauses);
	  c_name = "enter";
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_بھرا:
	  c_name = "full";
	  clauses = c_parser_omp_clause_بھرا (parser, clauses);
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_PARTIAL:
	  c_name = "partial";
	  clauses = c_parser_omp_clause_partial (parser, clauses);
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_NOVARIANTS:
	  c_name = "novariants";
	  clauses = c_parser_omp_clause_novariants (parser, clauses);
	  توڑو;
	حالت PRAGMA_OMP_CLAUSE_NOCONTEXT:
	  c_name = "nocontext";
	  clauses = c_parser_omp_clause_nocontext (parser, clauses);
	  توڑو;
	طےشدہ:
	  c_parser_error (parser, "expected an OpenMP clause");
	  جاؤ saw_error;
	}

      پہلا = جھوٹ;

      اگر (((نقاب >> c_قسم) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = پچھلا;
	  error_at (یہاں, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  اگر (!nested)
    c_parser_skip_مقصد_pragma_eol (parser);

  اگر (اختتام_p)
    {
      اگر ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_یکساں)) != 0)
	واپس c_اختتام_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      اگر ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	واپس c_اختتام_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      واپس c_اختتام_omp_clauses (clauses, C_ORT_OMP);
    }

  واپس clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

ساکن درخت
c_parser_omp_structured_بلاک (c_parser *parser, منطقی *if_p)
{
  درخت stmt = ڈالو_stmt_list ();
  parser->omp_attrs_forbidden_p = سچ;
  c_parser_statement (parser, if_p);
  واپس نکالو_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

ساکن درخت
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  درخت stmt, clauses = NULL_درخت;
  منطقی readonly = جھوٹ;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (token->type == CPP_NAME
	  && !strcmp (IDENTIFIER_اشارہ_گر (token->قدر), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = سچ;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_درخت);
      parens.skip_until_ملا_close (parser);
    }

  اگر (readonly)
    برائے (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_اختتام_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_مقصد_pragma_eol (parser);

  stmt = make_گرہ (OACC_CACHE);
  درخت_TYPE (stmt) = void_type_گرہ;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  سیٹ_اظہاریہ_LOCATION (stmt, loc);
  جوڑو_stmt (stmt);

  واپس stmt;
}

/* OpenACC 2.0:
   # pragma acc data oacc-data-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#تعریف_کرو OACC_ڈیٹا_CLAUSE_نقاب						\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_PRESENT))

ساکن درخت
c_parser_oacc_ڈیٹا (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت stmt, clauses, بلاک;

  clauses = c_parser_oacc_all_clauses (parser, OACC_ڈیٹا_CLAUSE_نقاب,
				       "#pragma acc data");

  بلاک = c_begin_omp_parallel ();
  جوڑو_stmt (c_parser_omp_structured_بلاک (parser, if_p));

  stmt = c_اختتام_oacc_ڈیٹا (loc, clauses, بلاک);

  واپس stmt;
}

/* OpenACC 2.0:
   # pragma acc declare oacc-data-clause[optseq] new-line
*/

#تعریف_کرو OACC_DECLARE_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_LINK)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_PRESENT))

ساکن خالی
c_parser_oacc_declare (c_parser *parser)
{
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  درخت clauses, stmt, t, decl;

  منطقی error = جھوٹ;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_نقاب,
				       "#pragma acc declare");
  اگر (!clauses)
    {
      error_at (pragma_loc,
		"no valid clauses specified in %<#pragma acc declare%>");
      واپس;
    }

  برائے (t = clauses; t; t = OMP_CLAUSE_CHAIN (t))
    {
      location_t loc = OMP_CLAUSE_LOCATION (t);
      decl = OMP_CLAUSE_DECL (t);
      اگر (!DECL_P (decl))
	{
	  error_at (loc, "array section in %<#pragma acc declare%>");
	  error = سچ;
	  جاری;
	}

      انتخاب (OMP_CLAUSE_MAP_قسم (t))
	{
	حالت GOMP_MAP_FIRSTPRIVATE_اشارہ_گر:
	حالت GOMP_MAP_ALLOC:
	حالت GOMP_MAP_مقصد:
	حالت GOMP_MAP_FORCE_DEVICEPTR:
	حالت GOMP_MAP_DEVICE_RESIDENT:
	  توڑو;

	حالت GOMP_MAP_LINK:
	  اگر (!global_bindings_p ()
	      && (درخت_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = سچ;
	      جاری;
	    }
	  توڑو;

	طےشدہ:
	  اگر (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = سچ;
	      جاری;
	    }
	  اگر (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = سچ;
	      جاری;
	    }
	  ورنہ اگر (درخت_عوامی (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = سچ;
	      جاری;
	    }
	  توڑو;
	}

      اگر (!c_check_اندر_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = سچ;
	  جاری;
	}

      اگر (lookup_attribute ("omp declare target", DECL_اوصاف (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_اوصاف (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = سچ;
	  جاری;
	}

      اگر (!error)
	{
	  درخت id;

	  اگر (OMP_CLAUSE_MAP_قسم (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  ورنہ
	    id = get_identifier ("omp declare target");

	  DECL_اوصاف (decl)
			   = درخت_cons (id, NULL_درخت, DECL_اوصاف (decl));

	  اگر (global_bindings_p ())
	    {
	      symtab_گرہ *گرہ = symtab_گرہ::get (decl);
	      اگر (گرہ != تہی)
		{
		  گرہ->offloadable = 1;
		  اگر (ENABLE_OFFLOADING)
		    {
		      g->have_offload = سچ;
		      اگر (is_a <varpool_گرہ *> (گرہ))
			vec_محفوظ_ڈالو (offload_vars, decl);
		    }
		}
	    }
	}
    }

  اگر (error || global_bindings_p ())
    واپس;

  stmt = make_گرہ (OACC_DECLARE);
  درخت_TYPE (stmt) = void_type_گرہ;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  سیٹ_اظہاریہ_LOCATION (stmt, pragma_loc);

  جوڑو_stmt (stmt);

  واپس;
}

/* OpenACC 2.0:
   # pragma acc enter data oacc-enter-data-clause[optseq] new-line

   or

   # pragma acc exit data oacc-exit-data-clause[optseq] new-line


   LOC is the location of the #pragma token.
*/

#تعریف_کرو OACC_ENTER_ڈیٹا_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#تعریف_کرو OACC_EXIT_ڈیٹا_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DELETE) 		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DETACH) 		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_FINALIZE) 		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_WAIT) )

ساکن خالی
c_parser_oacc_enter_exit_ڈیٹا (c_parser *parser, منطقی enter)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت clauses, stmt;
  ثابت حرف *p = "";

  c_parser_consume_pragma (parser);

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      c_parser_consume_token (parser);
    }

  اگر (strcmp (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = سچ;
      c_parser_skip_مقصد_pragma_eol (parser);
      واپس;
    }

  اگر (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_ڈیٹا_CLAUSE_نقاب,
					 "#pragma acc enter data");
  ورنہ
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_ڈیٹا_CLAUSE_نقاب,
					 "#pragma acc exit data");

  اگر (omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_MAP) == NULL_درخت)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      واپس;
    }

  stmt = enter ? make_گرہ (OACC_ENTER_ڈیٹا) : make_گرہ (OACC_EXIT_ڈیٹا);
  درخت_TYPE (stmt) = void_type_گرہ;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  سیٹ_اظہاریہ_LOCATION (stmt, loc);
  جوڑو_stmt (stmt);
}


/* OpenACC 2.0:
   # pragma acc host_data oacc-data-clause[optseq] new-line
     structured-block
*/

#تعریف_کرو OACC_HOST_ڈیٹا_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_USE_DEVICE)          \
	 | (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)                  \
	 | (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF_PRESENT) )

ساکن درخت
c_parser_oacc_host_ڈیٹا (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت stmt, clauses, بلاک;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_ڈیٹا_CLAUSE_نقاب,
				       "#pragma acc host_data", جھوٹ);
  اگر (!omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      واپس error_mark_گرہ;
    }
  clauses = c_اختتام_omp_clauses (clauses, C_ORT_ACC);
  بلاک = c_begin_omp_parallel ();
  جوڑو_stmt (c_parser_omp_structured_بلاک (parser, if_p));
  stmt = c_اختتام_oacc_host_ڈیٹا (loc, clauses, بلاک);
  واپس stmt;
}


/* OpenACC 2.0:

   # pragma acc loop oacc-loop-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#تعریف_کرو OACC_LOOP_CLAUSE_نقاب						\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COLLAPSE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_نجی)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_GANG)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_کارکن)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_سمتیہ)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_AUTO)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_INDEPENDENT) 	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_SEQ)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_TILE) )
ساکن درخت
c_parser_oacc_loop (location_t loc, c_parser *parser, حرف *p_name,
		    omp_clause_نقاب نقاب, درخت *cclauses, منطقی *if_p)
{
  منطقی is_parallel = ((نقاب >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  strcat (p_name, " loop");
  نقاب |= OACC_LOOP_CLAUSE_نقاب;

  درخت clauses = c_parser_oacc_all_clauses (parser, نقاب, p_name,
					    /*finish_p=*/cclauses == تہی,
					    /*target=*/is_parallel);
  اگر (cclauses)
    {
      clauses = c_oacc_بانٹو_loop_clauses (clauses, cclauses, is_parallel);
      اگر (*cclauses)
	*cclauses = c_اختتام_omp_clauses (*cclauses, C_ORT_ACC_ہدف);
      اگر (clauses)
	clauses = c_اختتام_omp_clauses (clauses, C_ORT_ACC);
    }

  درخت بلاک = c_begin_compound_stmt (سچ);
  درخت stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, تہی,
				     if_p);
  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
  جوڑو_stmt (بلاک);

  واپس stmt;
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

#تعریف_کرو OACC_KERNELS_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_عدد_GANGS)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_عدد_WORKERS)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_سمتیہ_لمبائی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#تعریف_کرو OACC_PARALLEL_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_نجی)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_عدد_GANGS)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_عدد_WORKERS)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_سمتیہ_لمبائی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#تعریف_کرو OACC_SERIAL_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_نجی)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_WAIT) )

ساکن درخت
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       شمار pragma_قسم p_قسم, حرف *p_name, منطقی *if_p)
{
  omp_clause_نقاب نقاب;
  شمار درخت_رمز_2 رمز;
  انتخاب (p_قسم)
    {
    حالت PRAGMA_OACC_KERNELS:
      strcat (p_name, " kernels");
      نقاب = OACC_KERNELS_CLAUSE_نقاب;
      رمز = OACC_KERNELS;
      توڑو;
    حالت PRAGMA_OACC_PARALLEL:
      strcat (p_name, " parallel");
      نقاب = OACC_PARALLEL_CLAUSE_نقاب;
      رمز = OACC_PARALLEL;
      توڑو;
    حالت PRAGMA_OACC_SERIAL:
      strcat (p_name, " serial");
      نقاب = OACC_SERIAL_CLAUSE_نقاب;
      رمز = OACC_SERIAL;
      توڑو;
    طےشدہ:
      gcc_unreachable ();
    }

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  درخت بلاک = c_begin_omp_parallel ();
	  درخت clauses;
	  c_parser_oacc_loop (loc, parser, p_name, نقاب, &clauses, if_p);
	  واپس c_اختتام_omp_construct (loc, رمز, بلاک, clauses);
	}
    }

  درخت clauses = c_parser_oacc_all_clauses (parser, نقاب, p_name,
					    /*finish_p=*/سچ,
					    /*target=*/سچ);

  درخت بلاک = c_begin_omp_parallel ();
  جوڑو_stmt (c_parser_omp_structured_بلاک (parser, if_p));

  واپس c_اختتام_omp_construct (loc, رمز, بلاک, clauses);
}

/* OpenACC 2.0:
   # pragma acc routine oacc-routine-clause[optseq] new-line
     function-definition

   # pragma acc routine ( name ) oacc-routine-clause[optseq] new-line
*/

#تعریف_کرو OACC_ROUTINE_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_GANG)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_کارکن)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_سمتیہ)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_SEQ)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_NOHOST) )

/* Parse an OpenACC routine directive.  For named directives, we apply
   immediately to the named function.  For unnamed ones we then parse
   a declaration or definition, which must be for a function.  */

ساکن خالی
c_parser_oacc_routine (c_parser *parser, شمار pragma_context context)
{
  gcc_checking_assert (context == pragma_external);

  oacc_routine_ڈیٹا ڈیٹا;
  ڈیٹا.error_نظر_آیا = جھوٹ;
  ڈیٹا.fndecl_نظر_آیا = جھوٹ;
  ڈیٹا.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      درخت decl = NULL_درخت;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      اگر (name_token->type == CPP_NAME
	  && (name_token->id_قسم == C_ID_ID
	      || name_token->id_قسم == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->قدر);
	  اگر (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->قدر);
	  c_parser_consume_token (parser);
	}
      ورنہ
	c_parser_error (parser, "expected function name");

      اگر (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	  واپس;
	}

      ڈیٹا.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_نقاب,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      ڈیٹا.clauses = nreverse (ڈیٹا.clauses);

      اگر (درخت_رمز (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  واپس;
	}

      c_اختتام_oacc_routine (&ڈیٹا, decl, جھوٹ);
    }
  ورنہ /* No optional '( name )'.  */
    {
      ڈیٹا.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_نقاب,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      ڈیٹا.clauses = nreverse (ڈیٹا.clauses);

      /* Emit a helpful diagnostic if there's another pragma following this
	 one.  Also don't allow a static assertion declaration, as in the
	 following we'll just parse a *single* "declaration or function
	 definition", and the static assertion counts an one.  */
      اگر (c_parser_اگلا_token_is (parser, CPP_PRAGMA)
	  || c_parser_اگلا_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (ڈیٹا.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  واپس;
	}

      /* We only have to consider the pragma_external case here.  */
      اگر (c_parser_اگلا_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحیح ext = disable_extension_diagnostics ();
	  کرو
	    c_parser_consume_token (parser);
	  جب (c_parser_اگلا_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, جھوٹ, سچ,
					 جھوٹ, تہی, تہی, جھوٹ, تہی, &ڈیٹا);
	  restore_extension_diagnostics (ext);
	}
      ورنہ
	c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, جھوٹ, سچ,
				       جھوٹ, تہی, تہی, جھوٹ, تہی, &ڈیٹا);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

ساکن خالی
c_اختتام_oacc_routine (ساخت oacc_routine_ڈیٹا *ڈیٹا, درخت fndecl,
		       منطقی is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  اگر (ڈیٹا->error_نظر_آیا
      || fndecl == error_mark_گرہ)
    واپس;

  اگر (ڈیٹا->fndecl_نظر_آیا)
    {
      error_at (ڈیٹا->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      ڈیٹا->error_نظر_آیا = سچ;
      واپس;
    }
  اگر (fndecl == NULL_درخت || درخت_رمز (fndecl) != FUNCTION_DECL)
    {
      error_at (ڈیٹا->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      ڈیٹا->error_نظر_آیا = سچ;
      واپس;
    }

  صحیح compatible
    = oacc_verify_routine_clauses (fndecl, &ڈیٹا->clauses, ڈیٹا->loc,
				   "#pragma acc routine");
  اگر (compatible < 0)
    {
      ڈیٹا->error_نظر_آیا = سچ;
      واپس;
    }
  اگر (compatible > 0)
    {
    }
  ورنہ
    {
      اگر (درخت_مستعمل (fndecl) || (!is_defn && DECL_SAVED_درخت (fndecl)))
	{
	  error_at (ڈیٹا->loc,
		    درخت_مستعمل (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  ڈیٹا->error_نظر_آیا = سچ;
	  واپس;
	}

      /* Set the routine's level of parallelism.  */
      درخت dims = oacc_build_routine_dims (ڈیٹا->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_اوصاف (fndecl)
	= درخت_cons (get_identifier ("omp declare target"),
		     ڈیٹا->clauses, DECL_اوصاف (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  ڈیٹا->fndecl_نظر_آیا = سچ;
}

/* OpenACC 2.0:
   # pragma acc update oacc-update-clause[optseq] new-line
*/

#تعریف_کرو OACC_UPDATE_CLAUSE_نقاب						\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEVICE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_HOST)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF_PRESENT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_WAIT) )

ساکن خالی
c_parser_oacc_update (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  درخت clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_نقاب,
					    "#pragma acc update");
  اگر (omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_MAP) == NULL_درخت)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      واپس;
    }

  اگر (parser->error)
    واپس;

  درخت stmt = make_گرہ (OACC_UPDATE);
  درخت_TYPE (stmt) = void_type_گرہ;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  سیٹ_اظہاریہ_LOCATION (stmt, loc);
  جوڑو_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#تعریف_کرو OACC_WAIT_CLAUSE_نقاب						\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF) )

ساکن درخت
c_parser_oacc_wait (location_t loc, c_parser *parser, حرف *p_name)
{
  درخت clauses, list = NULL_درخت, stmt = NULL_درخت;

  اگر (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  strcpy (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_نقاب, p_name);
  stmt = c_اختتام_oacc_wait (loc, list, clauses);
  جوڑو_stmt (stmt);

  واپس stmt;
}

ساخت c_omp_loc_درخت
{
  location_t loc;
  درخت var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
ساکن درخت
c_check_omp_allocate_allocator_r (درخت *tp, صحیح *, خالی *ڈیٹا)
{
  درخت var = ((ساخت c_omp_loc_درخت *) ڈیٹا)->var;
  location_t loc = ((ساخت c_omp_loc_درخت *) ڈیٹا)->loc;
  اگر (درخت_رمز (*tp) == VAR_DECL && c_check_اندر_current_scope (*tp))
    {
      اگر (linemap_location_before_p (سطر_جدول, DECL_ماخذ_LOCATION (var),
				     DECL_ماخذ_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_ماخذ_LOCATION (*tp), "declared here");
	  inform (DECL_ماخذ_LOCATION (var),
		  "to be allocated variable declared here");
	  واپس *tp;
	}
      ورنہ
	{
	  gcc_assert (cur_stmt_list
		      && درخت_رمز (cur_stmt_list) == STATEMENT_LIST);

	  درخت_stmt_iterator l = tsi_آخری (cur_stmt_list);
	  جب (!tsi_انتہا_p (l))
	    {
	      اگر (linemap_location_before_p (سطر_جدول, اظہاریہ_LOCATION (*l),
					     DECL_ماخذ_LOCATION (var)))
		  توڑو;
	      اگر (درخت_رمز (*l) == MODIFY_اظہاریہ
		  && درخت_عملیہ (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (اظہاریہ_LOCATION (*l), "modified here");
		  inform (DECL_ماخذ_LOCATION (var),
			  "to be allocated variable declared here");
		  واپس *tp;
		}
	      --l;
	    }
	}
    }
  واپس NULL_درخت;
}

/* OpenMP 5.x:
   # pragma omp allocate (list)  clauses

   OpenMP 5.0 clause:
   allocator (omp_allocator_handle_t expression)

   OpenMP 5.1 additional clause:
   align (constant-expression)]  */

ساکن خالی
c_parser_omp_allocate (c_parser *parser)
{
  درخت alignment = NULL_درخت;
  درخت allocator = NULL_درخت;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  درخت nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_درخت);
  کرو
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      اگر (!c_parser_اگلا_token_is (parser, CPP_NAME))
	توڑو;
      matching_parens parens;
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      c_parser_consume_token (parser);
      location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
      اگر (strcmp ("align", p) != 0 && strcmp ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  توڑو;
	}
      اگر (!parens.require_open (parser))
	توڑو;

      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, جھوٹ, سچ);
      اظہاریہ_loc = c_parser_peek_token (parser)->location;
      اگر (اظہاریہ.قدر == error_mark_گرہ)
	;
      ورنہ اگر (p[2] == 'i' && alignment)
	{
	  error_at (اظہاریہ_loc, "too many %qs clauses", "align");
	  توڑو;
	}
      ورنہ اگر (p[2] == 'i')
	{
	  alignment = c_fully_fold (اظہاریہ.قدر, جھوٹ, تہی);
	  اگر (درخت_رمز (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (درخت_TYPE (alignment))
	      || درخت_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (اظہاریہ_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_درخت;
	    }
	}
      ورنہ اگر (allocator)
	{
	  error_at (اظہاریہ_loc, "too many %qs clauses", "allocator");
	  توڑو;
	}
      ورنہ
	{
	  allocator = c_fully_fold (اظہاریہ.قدر, جھوٹ, تہی);
	  allocator_loc = اظہاریہ_loc;
	  درخت orig_type
	    = اظہاریہ.original_type ? اظہاریہ.original_type : درخت_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (allocator))
	      || درخت_رمز (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (اظہاریہ_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			درخت_TYPE (allocator));
	      allocator = NULL_درخت;
	    }
	}
      parens.skip_until_ملا_close (parser);
    } جب (سچ);
  c_parser_skip_مقصد_pragma_eol (parser);

  c_mark_decl_jump_unsafe_اندر_current_scope ();
  برائے (درخت c = nl; c != NULL_درخت; c = OMP_CLAUSE_CHAIN (c))
    {
      درخت var = OMP_CLAUSE_DECL (c);
      اگر (درخت_رمز (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  جاری;
	}
      اگر (!parser->اندر_omp_decl_attribute && !c_check_اندر_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_ماخذ_LOCATION (var), "declared here");
	  جاری;
	}
      اگر (lookup_attribute ("omp allocate", DECL_اوصاف (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  جاری;
	}
      اگر (درخت_STATIC (var))
	{
	  اگر (allocator == NULL_درخت && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      جاری;
	    }
	  ورنہ اگر (allocator
		   && (wi::مقصد_widest (allocator) < 1
		       || wi::مقصد_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::مقصد_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::مقصد_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  ورنہ اگر (allocator
		   && (wi::eq_p (wi::مقصد_widest (allocator),
				 GOMP_OMP_PREDEF_ALLOC_CGROUP)
		       || wi::eq_p (wi::مقصد_widest (allocator),
				    GOMP_OMP_PREDEF_ALLOC_PTEAM)
		       || wi::eq_p (wi::مقصد_widest (allocator),
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
	  ساخت c_omp_loc_درخت ڈیٹا
	    = {اظہاریہ_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_درخت (&allocator, c_check_omp_allocate_allocator_r, &ڈیٹا, تہی);
	}
      DECL_اوصاف (var) = درخت_cons (get_identifier ("omp allocate"),
					 build_درخت_list (allocator, alignment),
					 DECL_اوصاف (var));
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

ساکن خالی
c_parser_omp_atomic (location_t loc, c_parser *parser, منطقی openacc)
{
  درخت lhs = NULL_درخت, rhs = NULL_درخت, v = NULL_درخت, r = NULL_درخت;
  درخت lhs1 = NULL_درخت, rhs1 = NULL_درخت;
  درخت stmt, orig_lhs, unfolded_lhs = NULL_درخت, unfolded_lhs1 = NULL_درخت;
  شمار درخت_رمز_2 رمز = ERROR_MARK, opcode = NOP_اظہاریہ;
  شمار omp_حافظہ_ترتیب حافظہ_ترتیب = OMP_حافظہ_ترتیب_UNSPECIFIED;
  ساخت c_اظہاریہ اظہاریہ;
  location_t eloc;
  منطقی structured_بلاک = جھوٹ;
  منطقی swapped = جھوٹ;
  منطقی non_lvalue_p;
  درخت clauses = NULL_درخت;
  منطقی capture = جھوٹ;
  منطقی compare = جھوٹ;
  منطقی weak = جھوٹ;
  شمار omp_حافظہ_ترتیب fail = OMP_حافظہ_ترتیب_UNSPECIFIED;
  منطقی no_semicolon = جھوٹ;
  منطقی extra_scope = جھوٹ;

  جب (c_parser_اگلا_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	{
	  ثابت حرف *p
	    = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  شمار درخت_رمز_2 new_رمز = ERROR_MARK;
	  شمار omp_حافظہ_ترتیب new_حافظہ_ترتیب
	    = OMP_حافظہ_ترتیب_UNSPECIFIED;
	  منطقی new_capture = جھوٹ;
	  منطقی new_compare = جھوٹ;
	  منطقی new_weak = جھوٹ;
	  شمار omp_حافظہ_ترتیب new_fail = OMP_حافظہ_ترتیب_UNSPECIFIED;

	  اگر (!strcmp (p, "read"))
	    new_رمز = OMP_ATOMIC_READ;
	  ورنہ اگر (!strcmp (p, "write"))
	    new_رمز = NOP_اظہاریہ;
	  ورنہ اگر (!strcmp (p, "update"))
	    new_رمز = OMP_ATOMIC;
	  ورنہ اگر (openacc && !strcmp (p, "capture"))
	    new_رمز = OMP_ATOMIC_CAPTURE_NEW;
	  ورنہ اگر (openacc)
	    {
	      p = تہی;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  ورنہ اگر (!strcmp (p, "capture"))
	    new_capture = سچ;
	  ورنہ اگر (!strcmp (p, "compare"))
	    new_compare = سچ;
	  ورنہ اگر (!strcmp (p, "weak"))
	    new_weak = سچ;
	  ورنہ اگر (!strcmp (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      اگر (!parens.require_open (parser))
		جاری;

	      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
		{
		  ثابت حرف *q
		    = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);

		  اگر (!strcmp (q, "seq_cst"))
		    new_fail = OMP_حافظہ_ترتیب_SEQ_CST;
		  ورنہ اگر (!strcmp (q, "acquire"))
		    new_fail = OMP_حافظہ_ترتیب_ACQUIRE;
		  ورنہ اگر (!strcmp (q, "relaxed"))
		    new_fail = OMP_حافظہ_ترتیب_RELAXED;
		}

	      اگر (new_fail != OMP_حافظہ_ترتیب_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  اگر (fail != OMP_حافظہ_ترتیب_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  ورنہ
		    fail = new_fail;
		}
	      ورنہ
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_ملا_close (parser);
	      جاری;
	    }
	  ورنہ اگر (!strcmp (p, "seq_cst"))
	    new_حافظہ_ترتیب = OMP_حافظہ_ترتیب_SEQ_CST;
	  ورنہ اگر (!strcmp (p, "acq_rel"))
	    new_حافظہ_ترتیب = OMP_حافظہ_ترتیب_ACQ_REL;
	  ورنہ اگر (!strcmp (p, "release"))
	    new_حافظہ_ترتیب = OMP_حافظہ_ترتیب_RELEASE;
	  ورنہ اگر (!strcmp (p, "acquire"))
	    new_حافظہ_ترتیب = OMP_حافظہ_ترتیب_ACQUIRE;
	  ورنہ اگر (!strcmp (p, "relaxed"))
	    new_حافظہ_ترتیب = OMP_حافظہ_ترتیب_RELAXED;
	  ورنہ اگر (!strcmp (p, "hint"))
	    {
	      c_parser_consume_token (parser);
	      clauses = c_parser_omp_clause_hint (parser, clauses);
	      جاری;
	    }
	  ورنہ
	    {
	      p = تہی;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "%<capture%>, %<compare%>, %<weak%>, %<fail%>, "
			      "%<seq_cst%>, %<acq_rel%>, %<release%>, "
			      "%<relaxed%> or %<hint%> clause");
	    }
	  اگر (p)
	    {
	      اگر (new_رمز != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  اگر (openacc
		      && رمز == OMP_ATOMIC
		      && new_رمز == OMP_ATOMIC_CAPTURE_NEW)
		    رمز = new_رمز;
		  ورنہ اگر (رمز != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  ورنہ
		    رمز = new_رمز;
		}
	      ورنہ اگر (new_حافظہ_ترتیب != OMP_حافظہ_ترتیب_UNSPECIFIED)
		{
		  اگر (حافظہ_ترتیب != OMP_حافظہ_ترتیب_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  ورنہ
		    حافظہ_ترتیب = new_حافظہ_ترتیب;
		}
	      ورنہ اگر (new_capture)
		{
		  اگر (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  ورنہ
		    capture = سچ;
		}
	      ورنہ اگر (new_compare)
		{
		  اگر (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  ورنہ
		    compare = سچ;
		}
	      ورنہ اگر (new_weak)
		{
		  اگر (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  ورنہ
		    weak = سچ;
		}
	      c_parser_consume_token (parser);
	      جاری;
	    }
	}
      توڑو;
    }
  c_parser_skip_مقصد_pragma_eol (parser);

  اگر (رمز == ERROR_MARK)
    رمز = OMP_ATOMIC;
  اگر (capture)
    {
      اگر (رمز != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      ورنہ
	رمز = OMP_ATOMIC_CAPTURE_NEW;
    }
  اگر (compare && رمز != OMP_ATOMIC && رمز != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = جھوٹ;
    }
  اگر (fail != OMP_حافظہ_ترتیب_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      fail = OMP_حافظہ_ترتیب_UNSPECIFIED;
    }
  اگر (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = جھوٹ;
    }
  اگر (openacc)
    حافظہ_ترتیب = OMP_حافظہ_ترتیب_RELAXED;
  ورنہ اگر (حافظہ_ترتیب == OMP_حافظہ_ترتیب_UNSPECIFIED)
    {
      omp_requires_نقاب
	= (شمار omp_requires) (omp_requires_نقاب
			       | OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتیب_مستعمل);
      انتخاب ((شمار omp_حافظہ_ترتیب)
	      (omp_requires_نقاب & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتیب))
	{
	حالت OMP_حافظہ_ترتیب_UNSPECIFIED:
	حالت OMP_حافظہ_ترتیب_RELAXED:
	  حافظہ_ترتیب = OMP_حافظہ_ترتیب_RELAXED;
	  توڑو;
	حالت OMP_حافظہ_ترتیب_SEQ_CST:
	  حافظہ_ترتیب = OMP_حافظہ_ترتیب_SEQ_CST;
	  توڑو;
	حالت OMP_حافظہ_ترتیب_ACQUIRE:
	  اگر (رمز == NOP_اظہاریہ)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      حافظہ_ترتیب = OMP_حافظہ_ترتیب_SEQ_CST;
	    }
	  ورنہ
	    حافظہ_ترتیب = OMP_حافظہ_ترتیب_ACQUIRE;
	  توڑو;
	حالت OMP_حافظہ_ترتیب_RELEASE:
	  اگر (رمز == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      حافظہ_ترتیب = OMP_حافظہ_ترتیب_SEQ_CST;
	    }
	  ورنہ
	    حافظہ_ترتیب = OMP_حافظہ_ترتیب_RELEASE;
	  توڑو;
	حالت OMP_حافظہ_ترتیب_ACQ_REL:
	  انتخاب (رمز)
	    {
	    حالت OMP_ATOMIC_READ:
	      حافظہ_ترتیب = OMP_حافظہ_ترتیب_ACQUIRE;
	      توڑو;
	    حالت NOP_اظہاریہ: /* atomic write */
	      حافظہ_ترتیب = OMP_حافظہ_ترتیب_RELEASE;
	      توڑو;
	    طےشدہ:
	      حافظہ_ترتیب = OMP_حافظہ_ترتیب_ACQ_REL;
	      توڑو;
	    }
	  توڑو;
	طےشدہ:
	  gcc_unreachable ();
	}
    }
  ورنہ
    انتخاب (رمز)
      {
      حالت OMP_ATOMIC_READ:
	اگر (حافظہ_ترتیب == OMP_حافظہ_ترتیب_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    حافظہ_ترتیب = OMP_حافظہ_ترتیب_SEQ_CST;
	  }
	ورنہ اگر (حافظہ_ترتیب == OMP_حافظہ_ترتیب_ACQ_REL)
	  حافظہ_ترتیب = OMP_حافظہ_ترتیب_ACQUIRE;
	توڑو;
      حالت NOP_اظہاریہ: /* atomic write */
	اگر (حافظہ_ترتیب == OMP_حافظہ_ترتیب_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    حافظہ_ترتیب = OMP_حافظہ_ترتیب_SEQ_CST;
	  }
	ورنہ اگر (حافظہ_ترتیب == OMP_حافظہ_ترتیب_ACQ_REL)
	  حافظہ_ترتیب = OMP_حافظہ_ترتیب_RELEASE;
	توڑو;
      طےشدہ:
	توڑو;
      }
  اگر (fail != OMP_حافظہ_ترتیب_UNSPECIFIED)
    حافظہ_ترتیب
      = (شمار omp_حافظہ_ترتیب) (حافظہ_ترتیب
				 | (fail << OMP_FAIL_حافظہ_ترتیب_سرکاؤ));

  انتخاب (رمز)
    {
    حالت OMP_ATOMIC_READ:
    حالت NOP_اظہاریہ: /* atomic write */
      v = c_parser_cast_عبارت (parser, تہی).قدر;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, جھوٹ, تہی, سچ);
      اگر (v == error_mark_گرہ)
	جاؤ saw_error;
      اگر (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	جاؤ saw_error;
      اگر (رمز == NOP_اظہاریہ)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  اظہاریہ = c_parser_عبارت (parser);
	  اظہاریہ = default_function_array_read_conversion (eloc, اظہاریہ);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  رمز = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_درخت;
	  rhs = c_fully_fold (اظہاریہ.قدر, جھوٹ, تہی);
	  اگر (rhs == error_mark_گرہ)
	    جاؤ saw_error;
	}
      ورنہ
	{
	  lhs = c_parser_cast_عبارت (parser, تہی).قدر;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, جھوٹ, تہی, سچ);
	  اگر (lhs == error_mark_گرہ)
	    جاؤ saw_error;
	  اگر (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      جاؤ مکمل;
    حالت OMP_ATOMIC_CAPTURE_NEW:
      اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_بلاک = سچ;
	}
      ورنہ اگر (compare
	       && c_parser_اگلا_token_is_keyword (parser, RID_IF))
	توڑو;
      ورنہ
	{
	  v = c_parser_cast_عبارت (parser, تہی).قدر;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, جھوٹ, تہی, سچ);
	  اگر (v == error_mark_گرہ)
	    جاؤ saw_error;
	  اگر (non_lvalue_p)
	    v = non_lvalue (v);
	  اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    جاؤ saw_error;
	  اگر (compare && c_parser_اگلا_token_is_keyword (parser, RID_IF))
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "expected expression");
	      جاؤ saw_error;
	    }
	}
      توڑو;
    طےشدہ:
      توڑو;
    }

  /* For structured_block case we don't know yet whether
     old or new x should be captured.  */
restart:
  اگر (compare && c_parser_اگلا_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      اگر (!parens.require_open (parser))
	جاؤ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_اظہاریہ cmp_اظہاریہ;
      اگر (r)
	{
	  cmp_اظہاریہ = c_parser_cast_عبارت (parser, تہی);
	  cmp_اظہاریہ = default_function_array_conversion (eloc, cmp_اظہاریہ);
	}
      ورنہ
	cmp_اظہاریہ = c_parser_ثنائی_عبارت (parser, تہی, void_list_گرہ);
      parens.skip_until_ملا_close (parser);
      اگر (cmp_اظہاریہ.قدر == error_mark_گرہ)
	جاؤ saw_error;
      اگر (r)
	{
	  اگر (!c_درخت_equal (cmp_اظہاریہ.قدر, unfolded_lhs))
	    جاؤ bad_if;
	  cmp_اظہاریہ.قدر = rhs1;
	  rhs1 = NULL_درخت;
	  gcc_assert (درخت_رمز (cmp_اظہاریہ.قدر) == EQ_اظہاریہ);
	}
      اگر (درخت_رمز (cmp_اظہاریہ.قدر) == EQ_اظہاریہ)
	;
      ورنہ اگر (!structured_بلاک && رمز == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (اظہاریہ_LOC_OR_LOC (cmp_اظہاریہ.قدر, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  جاؤ saw_error;
	}
      ورنہ اگر (درخت_رمز (cmp_اظہاریہ.قدر) != GT_اظہاریہ
	       && درخت_رمز (cmp_اظہاریہ.قدر) != LT_اظہاریہ)
	{
	  error_at (اظہاریہ_LOC_OR_LOC (cmp_اظہاریہ.قدر, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  جاؤ saw_error;
	}
      اگر (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	جاؤ saw_error;

      extra_scope = سچ;
      eloc = c_parser_peek_token (parser)->location;
      اظہاریہ = c_parser_cast_عبارت (parser, تہی);
      lhs = اظہاریہ.قدر;
      اظہاریہ = default_function_array_conversion (eloc, اظہاریہ);
      unfolded_lhs = اظہاریہ.قدر;
      lhs = c_fully_fold (lhs, جھوٹ, تہی, سچ);
      orig_lhs = lhs;
      اگر (lhs == error_mark_گرہ)
	جاؤ saw_error;
      اگر (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      اگر (!c_parser_اگلا_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  جاؤ saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
      rhs1 = اظہاریہ.قدر;

      اگر (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	جاؤ saw_error;

      اگر (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	جاؤ saw_error;

      extra_scope = جھوٹ;
      no_semicolon = سچ;

      اگر (c_درخت_equal (درخت_عملیہ (cmp_اظہاریہ.قدر, 0), unfolded_lhs))
	{
	  اگر (درخت_رمز (cmp_اظہاریہ.قدر) == EQ_اظہاریہ)
	    {
	      opcode = COND_اظہاریہ;
	      rhs = c_fully_fold (درخت_عملیہ (cmp_اظہاریہ.قدر, 1),
				  جھوٹ, تہی, سچ);
	      rhs1 = c_fully_fold (rhs1, جھوٹ, تہی, سچ);
	    }
	  ورنہ اگر (c_درخت_equal (درخت_عملیہ (cmp_اظہاریہ.قدر, 1), rhs1))
	    {
	      opcode = (درخت_رمز (cmp_اظہاریہ.قدر) == GT_اظہاریہ
			? MIN_اظہاریہ : MAX_اظہاریہ);
	      rhs = c_fully_fold (rhs1, جھوٹ, تہی, سچ);
	      rhs1 = c_fully_fold (درخت_عملیہ (cmp_اظہاریہ.قدر, 0),
				   جھوٹ, تہی, سچ);
	    }
	  ورنہ
	    جاؤ bad_if;
	}
      ورنہ اگر (درخت_رمز (cmp_اظہاریہ.قدر) == EQ_اظہاریہ)
	جاؤ bad_if;
      ورنہ اگر (c_درخت_equal (درخت_عملیہ (cmp_اظہاریہ.قدر, 1), unfolded_lhs)
	       && c_درخت_equal (درخت_عملیہ (cmp_اظہاریہ.قدر, 0), rhs1))
	{
	  opcode = (درخت_رمز (cmp_اظہاریہ.قدر) == GT_اظہاریہ
		    ? MAX_اظہاریہ : MIN_اظہاریہ);
	  rhs = c_fully_fold (rhs1, جھوٹ, تہی, سچ);
	  rhs1 = c_fully_fold (درخت_عملیہ (cmp_اظہاریہ.قدر, 1),
			       جھوٹ, تہی, سچ);
	}
      ورنہ
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  جاؤ saw_error;
	}

      اگر (c_parser_اگلا_token_is_keyword (parser, RID_ELSE))
	{
	  اگر (رمز != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_بلاک && r == NULL_درخت)
	      || درخت_رمز (cmp_اظہاریہ.قدر) != EQ_اظہاریہ)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      جاؤ saw_error;
	    }

	  c_parser_consume_token (parser);

	  اگر (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    جاؤ saw_error;

	  extra_scope = سچ;
	  v = c_parser_cast_عبارت (parser, تہی).قدر;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, جھوٹ, تہی, سچ);
	  اگر (v == error_mark_گرہ)
	    جاؤ saw_error;
	  اگر (non_lvalue_p)
	    v = non_lvalue (v);
	  اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    جاؤ saw_error;

	  اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);

	  اگر (!c_درخت_equal (اظہاریہ.قدر, unfolded_lhs))
	    جاؤ bad_if;

	  اگر (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    جاؤ saw_error;

	  اگر (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    جاؤ saw_error;

	  extra_scope = جھوٹ;
	  رمز = OMP_ATOMIC_CAPTURE_OLD;
	  اگر (r == NULL_درخت)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_گرہ;
	}
      ورنہ اگر (رمز == OMP_ATOMIC_CAPTURE_NEW && !structured_بلاک)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  جاؤ saw_error;
	}
      ورنہ اگر (رمز == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_درخت
	       && v == NULL_درخت)
	رمز = OMP_ATOMIC;
      جاؤ stmt_مکمل;
    }
  eloc = c_parser_peek_token (parser)->location;
  اظہاریہ = c_parser_cast_عبارت (parser, تہی);
  lhs = اظہاریہ.قدر;
  اظہاریہ = default_function_array_conversion (eloc, اظہاریہ);
  unfolded_lhs = اظہاریہ.قدر;
  lhs = c_fully_fold (lhs, جھوٹ, تہی, سچ);
  orig_lhs = lhs;
  انتخاب (درخت_رمز (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    حالت ERROR_MARK:
    saw_error:
      c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
      اگر (extra_scope && c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      اگر (structured_بلاک)
	{
	  اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  ورنہ اگر (رمز == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
	      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      واپس;

    حالت POSTINCREMENT_اظہاریہ:
      اگر (رمز == OMP_ATOMIC_CAPTURE_NEW && !structured_بلاک)
	رمز = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    حالت PREINCREMENT_اظہاریہ:
      lhs = درخت_عملیہ (lhs, 0);
      unfolded_lhs = NULL_درخت;
      opcode = PLUS_اظہاریہ;
      rhs = integer_one_گرہ;
      اگر (compare)
	جاؤ invalid_compare;
      توڑو;

    حالت POSTDECREMENT_اظہاریہ:
      اگر (رمز == OMP_ATOMIC_CAPTURE_NEW && !structured_بلاک)
	رمز = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    حالت PREDECREMENT_اظہاریہ:
      lhs = درخت_عملیہ (lhs, 0);
      unfolded_lhs = NULL_درخت;
      opcode = MINUS_اظہاریہ;
      rhs = integer_one_گرہ;
      اگر (compare)
	جاؤ invalid_compare;
      توڑو;

    حالت COMPOUND_اظہاریہ:
      اگر (درخت_رمز (درخت_عملیہ (lhs, 0)) == SAVE_اظہاریہ
	  && درخت_رمز (درخت_عملیہ (lhs, 1)) == COMPOUND_اظہاریہ
	  && درخت_رمز (درخت_عملیہ (درخت_عملیہ (lhs, 1), 0)) == MODIFY_اظہاریہ
	  && درخت_عملیہ (درخت_عملیہ (lhs, 1), 1) == درخت_عملیہ (lhs, 0)
	  && C_BOOLEAN_TYPE_P (درخت_TYPE (درخت_عملیہ (درخت_عملیہ
					      (درخت_عملیہ (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = درخت_عملیہ (درخت_عملیہ (lhs, 1), 0);
      /* FALLTHRU */
    حالت MODIFY_اظہاریہ:
      اگر (درخت_رمز (lhs) == MODIFY_اظہاریہ
	  && C_BOOLEAN_TYPE_P (درخت_TYPE (درخت_عملیہ (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  اگر (integer_onep (درخت_عملیہ (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = درخت_عملیہ (lhs, 1);
	      lhs = درخت_عملیہ (lhs, 0);
	      unfolded_lhs = NULL_درخت;
	      opcode = NOP_اظہاریہ;
	      اگر (رمز == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_بلاک
		  && درخت_رمز (orig_lhs) == COMPOUND_اظہاریہ)
		رمز = OMP_ATOMIC_CAPTURE_OLD;
	      اگر (compare)
		جاؤ invalid_compare;
	      توڑو;
	    }
	  اگر (درخت_رمز (درخت_عملیہ (lhs, 1)) == TRUTH_NOT_اظہاریہ
	      && درخت_عملیہ (lhs, 0)
		 == درخت_عملیہ (درخت_عملیہ (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = درخت_عملیہ (lhs, 1);
	      lhs = درخت_عملیہ (lhs, 0);
	      unfolded_lhs = NULL_درخت;
	      opcode = NOP_اظہاریہ;
	      اگر (رمز == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_بلاک
		  && درخت_رمز (orig_lhs) == COMPOUND_اظہاریہ)
		رمز = OMP_ATOMIC_CAPTURE_OLD;
	      اگر (compare)
		جاؤ invalid_compare;
	      توڑو;
	    }
	}
      /* FALLTHRU */
    طےشدہ:
      اگر (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      اگر (compare && !c_parser_اگلا_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  جاؤ saw_error;
	}
      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_MULT_EQ:
	  opcode = MULT_اظہاریہ;
	  توڑو;
	حالت CPP_DIV_EQ:
	  opcode = TRUNC_DIV_اظہاریہ;
	  توڑو;
	حالت CPP_PLUS_EQ:
	  opcode = PLUS_اظہاریہ;
	  توڑو;
	حالت CPP_MINUS_EQ:
	  opcode = MINUS_اظہاریہ;
	  توڑو;
	حالت CPP_LSHIFT_EQ:
	  opcode = LSHIFT_اظہاریہ;
	  توڑو;
	حالت CPP_RSHIFT_EQ:
	  opcode = RSHIFT_اظہاریہ;
	  توڑو;
	حالت CPP_AND_EQ:
	  opcode = ثنائی_ہندسہ_AND_اظہاریہ;
	  توڑو;
	حالت CPP_OR_EQ:
	  opcode = ثنائی_ہندسہ_IOR_اظہاریہ;
	  توڑو;
	حالت CPP_XOR_EQ:
	  opcode = ثنائی_ہندسہ_XOR_اظہاریہ;
	  توڑو;
	حالت CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی, unfolded_lhs);
	  rhs1 = اظہاریہ.قدر;
	  انتخاب (درخت_رمز (rhs1))
	    {
	    حالت MULT_اظہاریہ:
	    حالت TRUNC_DIV_اظہاریہ:
	    حالت RDIV_اظہاریہ:
	    حالت PLUS_اظہاریہ:
	    حالت MINUS_اظہاریہ:
	    حالت LSHIFT_اظہاریہ:
	    حالت RSHIFT_اظہاریہ:
	    حالت ثنائی_ہندسہ_AND_اظہاریہ:
	    حالت ثنائی_ہندسہ_IOR_اظہاریہ:
	    حالت ثنائی_ہندسہ_XOR_اظہاریہ:
	      اگر (compare)
		توڑو;
	      اگر (c_درخت_equal (درخت_عملیہ (rhs1, 0), unfolded_lhs))
		{
		  opcode = درخت_رمز (rhs1);
		  rhs = c_fully_fold (درخت_عملیہ (rhs1, 1), جھوٹ, تہی,
				      سچ);
		  rhs1 = c_fully_fold (درخت_عملیہ (rhs1, 0), جھوٹ, تہی,
				       سچ);
		  جاؤ stmt_مکمل;
		}
	      اگر (c_درخت_equal (درخت_عملیہ (rhs1, 1), unfolded_lhs))
		{
		  opcode = درخت_رمز (rhs1);
		  rhs = c_fully_fold (درخت_عملیہ (rhs1, 0), جھوٹ, تہی,
				      سچ);
		  rhs1 = c_fully_fold (درخت_عملیہ (rhs1, 1), جھوٹ, تہی,
				       سچ);
		  swapped = !commutative_درخت_رمز (opcode);
		  جاؤ stmt_مکمل;
		}
	      توڑو;
	    حالت COND_اظہاریہ:
	      اگر (!compare)
		توڑو;
	      اگر (درخت_رمز (درخت_عملیہ (rhs1, 0)) != GT_اظہاریہ
		  && درخت_رمز (درخت_عملیہ (rhs1, 0)) != LT_اظہاریہ
		  && درخت_رمز (درخت_عملیہ (rhs1, 0)) != EQ_اظہاریہ)
		توڑو;
	      اگر (!درخت_عملیہ (rhs1, 1))
		توڑو;
	      اگر (!c_درخت_equal (درخت_عملیہ (rhs1, 2), unfolded_lhs))
		توڑو;
	      اگر (c_درخت_equal (درخت_عملیہ (درخت_عملیہ (rhs1, 0), 0),
				unfolded_lhs))
		{
		  اگر (درخت_رمز (درخت_عملیہ (rhs1, 0)) == EQ_اظہاریہ)
		    {
		      opcode = COND_اظہاریہ;
		      rhs = c_fully_fold (درخت_عملیہ (درخت_عملیہ (rhs1,
								      0), 1),
					  جھوٹ, تہی, سچ);
		      rhs1 = c_fully_fold (درخت_عملیہ (rhs1, 1), جھوٹ,
					   تہی, سچ);
		      جاؤ stmt_مکمل;
		    }
		  اگر (c_درخت_equal (درخت_عملیہ (درخت_عملیہ (rhs1, 0), 1),
				    درخت_عملیہ (rhs1, 1)))
		    {
		      opcode = (درخت_رمز (درخت_عملیہ (rhs1, 0)) == GT_اظہاریہ
				? MIN_اظہاریہ : MAX_اظہاریہ);
		      rhs = c_fully_fold (درخت_عملیہ (rhs1, 1), جھوٹ, تہی,
					  سچ);
		      rhs1 = c_fully_fold (درخت_عملیہ (درخت_عملیہ (rhs1,
								       0), 0),
					   جھوٹ, تہی, سچ);
		      جاؤ stmt_مکمل;
		    }
		}
	      ورنہ اگر (درخت_رمز (درخت_عملیہ (rhs1, 0)) == EQ_اظہاریہ)
		توڑو;
	      ورنہ اگر (c_درخت_equal (درخت_عملیہ (درخت_عملیہ (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  اگر (c_درخت_equal (درخت_عملیہ (درخت_عملیہ (rhs1, 0), 0),
				    درخت_عملیہ (rhs1, 1)))
		    {
		      opcode = (درخت_رمز (درخت_عملیہ (rhs1, 0)) == GT_اظہاریہ
				? MAX_اظہاریہ : MIN_اظہاریہ);
		      rhs = c_fully_fold (درخت_عملیہ (rhs1, 1), جھوٹ, تہی,
					  سچ);
		      rhs1 = c_fully_fold (درخت_عملیہ (درخت_عملیہ (rhs1,
								       0), 1),
					   جھوٹ, تہی, سچ);
		      جاؤ stmt_مکمل;
		    }
		}
	      توڑو;
	    حالت EQ_اظہاریہ:
	      اگر (!compare
		  || رمز != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_بلاک
		  || v
		  || r)
		توڑو;
	      اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_درخت;
		  c_parser_consume_token (parser);
		  جاؤ restart;
		}
	      توڑو;
	    حالت ERROR_MARK:
	      جاؤ saw_error;
	    طےشدہ:
	      توڑو;
	    }
	  اگر (c_parser_peek_token (parser)->type == CPP_SEMICOLON)
	    {
	      اگر (structured_بلاک && رمز == OMP_ATOMIC_CAPTURE_NEW)
		{
		  رمز = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_درخت;
		  اظہاریہ = default_function_array_read_conversion (eloc, اظہاریہ);
		  unfolded_lhs1 = اظہاریہ.قدر;
		  lhs1 = c_fully_fold (unfolded_lhs1, جھوٹ, تہی, سچ);
		  rhs1 = NULL_درخت;
		  c_parser_consume_token (parser);
		  جاؤ restart;
		}
	      اگر (structured_بلاک && !compare)
		{
		  opcode = NOP_اظہاریہ;
		  اظہاریہ = default_function_array_read_conversion (eloc, اظہاریہ);
		  rhs = c_fully_fold (اظہاریہ.قدر, جھوٹ, تہی, سچ);
		  rhs1 = NULL_درخت;
		  جاؤ stmt_مکمل;
		}
	    }
	  c_parser_error (parser, "invalid form of %<#pragma omp atomic%>");
	  جاؤ saw_error;
	طےشدہ:
	  c_parser_error (parser,
			  "invalid operator for %<#pragma omp atomic%>");
	  جاؤ saw_error;
	}

      /* Arrange to pass the location of the assignment operator to
	 c_finish_omp_atomic.  */
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      اظہاریہ = c_parser_عبارت (parser);
      اظہاریہ = default_function_array_read_conversion (eloc, اظہاریہ);
      rhs = اظہاریہ.قدر;
      rhs = c_fully_fold (rhs, جھوٹ, تہی, سچ);
      توڑو;
    }
stmt_مکمل:
  اگر (structured_بلاک && رمز == OMP_ATOMIC_CAPTURE_NEW && r == NULL_درخت)
    {
      اگر (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	جاؤ saw_error;
      no_semicolon = جھوٹ;
      v = c_parser_cast_عبارت (parser, تہی).قدر;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, جھوٹ, تہی, سچ);
      اگر (v == error_mark_گرہ)
	جاؤ saw_error;
      اگر (non_lvalue_p)
	v = non_lvalue (v);
      اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	جاؤ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      اظہاریہ = c_parser_cast_عبارت (parser, تہی);
      lhs1 = اظہاریہ.قدر;
      اظہاریہ = default_function_array_read_conversion (eloc, اظہاریہ);
      unfolded_lhs1 = اظہاریہ.قدر;
      lhs1 = c_fully_fold (lhs1, جھوٹ, تہی, سچ);
      اگر (lhs1 == error_mark_گرہ)
	جاؤ saw_error;
      اگر (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  اگر (structured_بلاک)
    {
      اگر (!no_semicolon)
	c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
مکمل:
  اگر (weak && opcode != COND_اظہاریہ)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = جھوٹ;
    }
  اگر (unfolded_lhs && unfolded_lhs1
      && !c_درخت_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_گرہ;
    }
  ورنہ
    stmt = c_اختتام_omp_atomic (loc, رمز, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, حافظہ_ترتیب, weak);
  اگر (stmt != error_mark_گرہ)
    جوڑو_stmt (stmt);

  اگر (!structured_بلاک && !no_semicolon)
    c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
}


/* OpenMP 2.5:
   # pragma omp barrier new-line
*/

ساکن خالی
c_parser_omp_barrier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  c_parser_skip_مقصد_pragma_eol (parser);

  c_اختتام_omp_barrier (loc);
}

/* OpenMP 2.5:
   # pragma omp critical [(name)] new-line
     structured-block

   OpenMP 4.5:
   # pragma omp critical [(name) [hint(expression)]] new-line

  LOC is the location of the #pragma itself.  */

#تعریف_کرو OMP_CRITICAL_CLAUSE_نقاب		\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_HINT) )

ساکن درخت
c_parser_omp_critical (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت stmt, name = NULL_درخت, clauses = NULL_درخت;

  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->قدر;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      ورنہ
	c_parser_error (parser, "expected identifier");

      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_نقاب,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_بلاک (parser, if_p);
  واپس c_اختتام_omp_critical (loc, stmt, name, clauses);
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
اندر
برآمد
     inout
     mutexinout  */

ساکن خالی
c_parser_omp_depobj (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  matching_parens parens;
  اگر (!parens.require_open (parser))
    {
      c_parser_skip_مقصد_pragma_eol (parser);
      واپس;
    }

  درخت depobj = c_parser_اظہاریہ_no_commas (parser, تہی).قدر;
  اگر (depobj != error_mark_گرہ)
    {
      اگر (!lvalue_p (depobj))
	{
	  error_at (اظہاریہ_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_گرہ;
	}
      ورنہ
	{
	  درخت addr = build_unary_op (اظہاریہ_LOC_OR_LOC (depobj, loc), ADDR_اظہاریہ,
				      depobj, جھوٹ);
	  اگر (addr == error_mark_گرہ)
	    depobj = error_mark_گرہ;
	  ورنہ
	    depobj = build_بالواسطہ_ref (اظہاریہ_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_ستارہ);
	}
    }

  parens.skip_until_ملا_close (parser);
  درخت clause = NULL_درخت;
  شمار omp_clause_depend_قسم قسم = OMP_CLAUSE_DEPEND_INVALID;
  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);

      c_parser_consume_token (parser);
      اگر (!strcmp ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_درخت, c_loc);
	  clause = c_اختتام_omp_clauses (clause, C_ORT_OMP);
	  اگر (!clause)
	    clause = error_mark_گرہ;
	}
      ورنہ اگر (!strcmp ("destroy", p))
	{
	  matching_parens c_parens;
	  قسم = OMP_CLAUSE_DEPEND_آخری;
	  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      درخت destobj = c_parser_اظہاریہ_no_commas (parser, تہی).قدر;
	      اگر (!lvalue_p (destobj))
		error_at (اظہاریہ_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      ورنہ اگر (depobj != error_mark_گرہ
		       && !عملیہ_equal_p (destobj, depobj,
					    OEP_مطابقت_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (اظہاریہ_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_ملا_close (parser);
	    }
	}
      ورنہ اگر (!strcmp ("update", p))
	{
	  matching_parens c_parens;
	  اگر (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
		{
		  ثابت حرف *p2
		    = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);

		  c_parser_consume_token (parser);
		  اگر (!strcmp ("in", p2))
		    قسم = OMP_CLAUSE_DEPEND_اندر;
		  ورنہ اگر (!strcmp ("out", p2))
		    قسم = OMP_CLAUSE_DEPEND_برآمد;
		  ورنہ اگر (!strcmp ("inout", p2))
		    قسم = OMP_CLAUSE_DEPEND_INOUT;
		  ورنہ اگر (!strcmp ("mutexinoutset", p2))
		    قسم = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  ورنہ اگر (!strcmp ("inoutset", p2))
		    قسم = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      اگر (قسم == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_گرہ;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_ملا_close (parser);
	    }
	  ورنہ
	    clause = error_mark_گرہ;
	}
    }
  اگر (!clause && قسم == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_گرہ;
      error_at (c_loc, "expected %<depend%>, %<destroy%> or %<update%> clause");
    }
  c_parser_skip_مقصد_pragma_eol (parser);

  c_اختتام_omp_depobj (loc, depobj, قسم, clause);
}


/* OpenMP 2.5:
   # pragma omp flush flush-vars[opt] new-line

   flush-vars:
     ( variable-list )

   OpenMP 5.0:
   # pragma omp flush memory-order-clause new-line  */

ساکن خالی
c_parser_omp_flush (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  شمار memmodel mo = MEMMODEL_آخری;
  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p
	= IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);

      اگر (!strcmp (p, "seq_cst"))
	mo = MEMMODEL_SEQ_CST;
      ورنہ اگر (!strcmp (p, "acq_rel"))
	mo = MEMMODEL_ACQ_REL;
      ورنہ اگر (!strcmp (p, "release"))
	mo = MEMMODEL_RELEASE;
      ورنہ اگر (!strcmp (p, "acquire"))
	mo = MEMMODEL_ACQUIRE;
      ورنہ
	error_at (c_parser_peek_token (parser)->location,
		  "expected %<seq_cst%>, %<acq_rel%>, %<release%> or "
		  "%<acquire%>");
      c_parser_consume_token (parser);
    }
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      اگر (mo != MEMMODEL_آخری)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, تہی);
    }
  ورنہ اگر (c_parser_اگلا_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_مقصد_pragma_eol (parser);

  c_اختتام_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

ساکن منطقی
c_parser_omp_section_جائزہ (c_parser *parser, ثابت حرف *directive,
			   منطقی tentative)
{
  اگر (!c_parser_nth_token_starts_std_اوصاف (parser, 1))
    واپس جھوٹ;
  غیرعلامتی صحیح n = 3;
  اگر (!c_parser_check_متوازن_raw_token_sequence (parser, &n))
    واپس جھوٹ;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  اگر (token->type != CPP_CLOSE_مربع)
    واپس جھوٹ;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  اگر (token->type != CPP_CLOSE_مربع)
    واپس جھوٹ;
  اگر (n < 9)
    واپس جھوٹ;
  اگر (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      درخت پہلا = c_parser_peek_nth_token_raw (parser, 3)->قدر;
      درخت دوسرا = c_parser_peek_nth_token_raw (parser, 5)->قدر;
      اگر (strcmp (IDENTIFIER_اشارہ_گر (پہلا), "directive")
	  && strcmp (IDENTIFIER_اشارہ_گر (پہلا), "__directive__"))
	واپس جھوٹ;
      اگر (strcmp (IDENTIFIER_اشارہ_گر (دوسرا), directive))
	واپس جھوٹ;
    }
  اگر (tentative)
    واپس سچ;
  location_t پہلا_loc = c_parser_peek_token (parser)->location;
  location_t آخری_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t درمیان_loc = UNKNOWN_LOCATION;
  درخت std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  منطقی نظر_آیا = جھوٹ;
  صحیح cnt = 0;
  برائے (درخت attr = std_attrs; attr; attr = درخت_CHAIN (attr))
    اگر (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	برائے (درخت a = درخت_قدر (attr); a; a = درخت_CHAIN (a))
	  {
	    درخت d = درخت_قدر (a);
	    gcc_assert (درخت_رمز (d) == C_TOKEN_VEC);
	    c_token *پہلا = C_TOKEN_VEC_علامات (d)->پتہ ();
	    cnt++;
	    اگر (پہلا->type == CPP_NAME
		&& strcmp (IDENTIFIER_اشارہ_گر (پہلا->قدر),
			   directive) == 0)
	      {
		نظر_آیا = سچ;
		اگر (درمیان_loc == UNKNOWN_LOCATION)
		  درمیان_loc = پہلا->location;
	      }
	  }
      }
  اگر (!نظر_آیا)
    واپس جھوٹ;
  اگر (cnt != 1 || درخت_CHAIN (std_attrs))
    {
      error_at (make_location (پہلا_loc, آخری_loc, درمیان_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      واپس جھوٹ;
    }
  c_parser_handle_statement_omp_اوصاف (parser, std_attrs, تہی);
  واپس سچ;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

ساکن درخت
c_parser_omp_structured_بلاک_sequence (c_parser *parser,
					شمار pragma_قسم قسم)
{
  درخت stmt = ڈالو_stmt_list ();
  c_parser_statement (parser, تہی);
  کرو
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
	توڑو;
      اگر (c_parser_اگلا_token_is (parser, CPP_EOF))
	توڑو;

      اگر (قسم != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_قسم == قسم)
	توڑو;

      اگر (قسم != PRAGMA_NONE
	  && c_parser_omp_section_جائزہ (parser,
					قسم == PRAGMA_OMP_جائزہ
					? "scan" : "section", جھوٹ))
	توڑو;

      c_parser_statement (parser, تہی);
    }
  جب (1);
  واپس نکالو_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

ساکن خالی
c_parser_omp_جائزہ_loop_body (c_parser *parser, منطقی open_brace_parsed)
{
  درخت substmt;
  location_t loc;
  درخت clauses = NULL_درخت;
  منطقی ملا_جائزہ = جھوٹ;

  loc = c_parser_peek_token (parser)->location;
  اگر (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = جھوٹ;
      واپس;
    }

  اگر (c_parser_peek_token (parser)->pragma_قسم != PRAGMA_OMP_جائزہ)
    substmt = c_parser_omp_structured_بلاک_sequence (parser, PRAGMA_OMP_جائزہ);
  ورنہ
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_خالی_خانے_stmt (loc);
    }
  substmt = build2 (OMP_جائزہ, void_type_گرہ, substmt, NULL_درخت);
  سیٹ_اظہاریہ_LOCATION (substmt, loc);
  جوڑو_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  اگر (c_parser_peek_token (parser)->pragma_قسم == PRAGMA_OMP_جائزہ)
    {
      شمار omp_clause_رمز clause = OMP_CLAUSE_ERROR;
      ملا_جائزہ = سچ;

      c_parser_consume_pragma (parser);

      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	{
	  ثابت حرف *p
	    = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
	  اگر (strcmp (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  ورنہ اگر (strcmp (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      اگر (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_درخت);
	}
      ورنہ
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_مقصد_pragma_eol (parser);
    }
  ورنہ
    error ("expected %<#pragma omp scan%>");

  clauses = c_اختتام_omp_clauses (clauses, C_ORT_OMP);
  اگر (!c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_بلاک_sequence (parser, PRAGMA_NONE);
  ورنہ
    {
      اگر (ملا_جائزہ)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_خالی_خانے_stmt (loc);
    }
  substmt = build2 (OMP_جائزہ, void_type_گرہ, substmt, clauses);
  سیٹ_اظہاریہ_LOCATION (substmt, loc);
  جوڑو_stmt (substmt);

  c_parser_skip_until_ملا (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
ساکن منطقی
c_parser_omp_اگلا_علامات_can_be_canon_loop (c_parser *parser,
					    شمار درخت_رمز_2 رمز,
					    منطقی error_p)
{
  اگر (رمز == OACC_LOOP)
    {
      اگر (c_parser_اگلا_token_is_keyword (parser, RID_FOR))
	واپس سچ;
      اگر (error_p)
	c_parser_error (parser, "for statement expected");
    }
  ورنہ
    {
      اگر (c_parser_اگلا_token_is_keyword (parser, RID_FOR))
	واپس سچ;

      اگر (c_parser_اگلا_token_is (parser, CPP_PRAGMA))
	انتخاب (c_parser_peek_token (parser)->pragma_قسم)
	  {
	  حالت PRAGMA_OMP_UNROLL:
	  حالت PRAGMA_OMP_TILE:
	    واپس سچ;
	  طےشدہ:
	    توڑو;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      سائز_t n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      اگر (token->type == CPP_NAME
	  && C_IS_RESERVED_لفظ (token->قدر)
	  && C_RID_رمز (token->قدر) == RID_FOR)
	واپس سچ;
      اگر (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  واپس جھوٹ;
}

ساکن درخت c_parser_omp_tile (location_t, c_parser *, منطقی *);
ساکن درخت c_parser_omp_unroll (location_t, c_parser *, منطقی *);

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

ساکن درخت
c_parser_omp_loop_nest (c_parser *parser, منطقی *if_p)
{
  درخت decl = NULL_درخت, cond = NULL_درخت, incr = NULL_درخت, init = NULL_درخت;
  درخت body = NULL_درخت;
  matching_parens parens;
  منطقی moreloops;
  غیرعلامتی حرف save_اندر_statement;
  درخت loop_scope;
  location_t loc;
  ساخت omp_for_parse_ڈیٹا *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  صحیح گہرائی = omp_for_parse_state->گہرائی;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  اگر (c_parser_nth_token_starts_std_اوصاف (parser, 1))
    {
      درخت std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_اوصاف (parser, std_attrs, تہی);
      اگر (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  اگر (c_parser_اگلا_token_is (parser, CPP_PRAGMA))
    {
      درخت transform = NULL_درخت, sizes, body = NULL_درخت;
      صحیح گنتی = 0;
      انتخاب (c_parser_peek_token (parser)->pragma_قسم)
	{
	حالت PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = ڈالو_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = نکالو_stmt_list (body);
	  اگر (transform == NULL_درخت || transform == error_mark_گرہ)
	    {
	      transform = error_mark_گرہ;
	      توڑو;
	    }
	  gcc_assert (درخت_رمز (transform) == OMP_UNROLL);
	  اگر (omp_ڈھونڈو_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      اگر (omp_for_parse_state->گنتی - گہرائی > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->گنتی - گہرائی);
		  transform = error_mark_گرہ;
		}
	      ورنہ
		گنتی = 1;
	    }
	  ورنہ
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_گرہ;
	    }
	  توڑو;
	حالت PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = ڈالو_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = نکالو_stmt_list (body);
	  اگر (transform == NULL_درخت || transform == error_mark_گرہ)
	    {
	      transform = error_mark_گرہ;
	      توڑو;
	    }
	  gcc_assert (درخت_رمز (transform) == OMP_TILE);
	  sizes = omp_ڈھونڈو_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  گنتی = list_لمبائی (OMP_CLAUSE_SIZES_LIST (sizes));
	  اگر (گہرائی + گنتی < omp_for_parse_state->گنتی)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			گنتی, omp_for_parse_state->گنتی - گہرائی);
	      transform = error_mark_گرہ;
	    }
	  توڑو;
	طےشدہ:
	  c_parser_pragma (parser, pragma_stmt, تہی, void_list_گرہ);
	  توڑو;
	}
      اگر (transform == NULL_درخت)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      اگر (transform == NULL_درخت || transform == error_mark_گرہ)
	{
	  omp_for_parse_state->fail = سچ;
	  واپس NULL_درخت;
	}
      برائے (گنتی = omp_for_parse_state->گنتی; گہرائی < گنتی; ++گہرائی)
	{
	  درخت_VEC_ELT (omp_for_parse_state->declv, گہرائی) = NULL_درخت;
	  درخت_VEC_ELT (omp_for_parse_state->initv, گہرائی) = NULL_درخت;
	  درخت_VEC_ELT (omp_for_parse_state->condv, گہرائی) = NULL_درخت;
	  درخت_VEC_ELT (omp_for_parse_state->incrv, گہرائی) = NULL_درخت;
	}
      omp_for_parse_state->want_nested_loop = جھوٹ;
      واپس body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_اندر_statement = اندر_statement;
  اندر_statement = اندر_OMP_بلاک;

  /* We are not in intervening code now.  */
  omp_for_parse_state->اندر_intervening_رمز = جھوٹ;

  اگر (!parens.require_open (parser))
    {
      omp_for_parse_state->fail = سچ;
      واپس NULL_درخت;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (سچ);

  /* Parse the initialization declaration or expression.  */
  اگر (c_parser_اگلا_علامات_آغاز_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      درخت this_pre_body = ڈالو_stmt_list ();
      c_اندر_omp_for = سچ;
      c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, سچ, سچ,
				     جھوٹ);
      c_اندر_omp_for = جھوٹ;
      this_pre_body = نکالو_stmt_list (this_pre_body);
      append_مقصد_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      اگر (decl == تہی)
	جاؤ error_init;
      اگر (DECL_INITIAL (decl) == error_mark_گرہ)
	decl = error_mark_گرہ;
      init = decl;
    }
  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      ساخت c_اظہاریہ decl_exp;
      ساخت c_اظہاریہ init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_عبارت (parser);
      decl = decl_exp.قدر;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_اظہاریہ_no_commas (parser, تہی);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_اندر_omp_for = سچ;
      init = build_modify_اظہاریہ (init_loc, decl, decl_exp.original_type,
				NOP_اظہاریہ, init_loc, init_exp.قدر,
				init_exp.original_type);
      c_اندر_omp_for = جھوٹ;
      init = c_process_اظہاریہ_stmt (init_loc, init);

      c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  ورنہ
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->fail = سچ;
      جاؤ parse_اگلا;
    }

  /* Parse the loop condition.  */
  اگر (c_parser_اگلا_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_اندر_omp_for = سچ;
      ساخت c_اظہاریہ cond_اظہاریہ
	= c_parser_ثنائی_عبارت (parser, تہی, NULL_درخت);
      c_اندر_omp_for = جھوٹ;

      cond = cond_اظہاریہ.قدر;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      انتخاب (cond_اظہاریہ.original_رمز)
	{
	حالت GT_اظہاریہ:
	حالت GE_اظہاریہ:
	حالت LT_اظہاریہ:
	حالت LE_اظہاریہ:
	  توڑو;
	حالت NE_اظہاریہ:
	  اگر (omp_for_parse_state->رمز != OACC_LOOP)
	    توڑو;
	  /* FALLTHRU.  */
	طےشدہ:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_اظہاریہ, boolean_type_گرہ, error_mark_گرہ);
	  توڑو;
	}
      protected_سیٹ_اظہاریہ_location (cond, cond_loc);
    }
  c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  اگر (c_parser_اگلا_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_اظہاریہ_stmt (incr_loc,
				  c_parser_عبارت (parser).قدر);
    }
  parens.skip_until_ملا_close (parser);

  اگر (decl == تہی || decl == error_mark_گرہ || init == error_mark_گرہ)
    omp_for_parse_state->fail = سچ;
  ورنہ
    {
      درخت_VEC_ELT (omp_for_parse_state->declv, گہرائی) = decl;
      درخت_VEC_ELT (omp_for_parse_state->initv, گہرائی) = init;
      درخت_VEC_ELT (omp_for_parse_state->condv, گہرائی) = cond;
      درخت_VEC_ELT (omp_for_parse_state->incrv, گہرائی) = incr;
    }

parse_اگلا:
  moreloops = گہرائی < omp_for_parse_state->گنتی - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  اگر (moreloops
      && c_parser_omp_اگلا_علامات_can_be_canon_loop (parser,
						     omp_for_parse_state->رمز,
						     جھوٹ))
    {
      omp_for_parse_state->گہرائی++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->گہرائی--;
    }
  ورنہ اگر (moreloops && c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
    {
      /* This is the open brace in the loop-body grammar production.  Rather
	 than trying to special-case braces, just parse it as a compound
	 statement and handle the nested loop-body case there.  Note that
	 when we see a further open brace inside the compound statement
	 loop-body, we don't know whether it is the start of intervening
	 code that is a compound statement, or a level of braces
	 surrounding a nested loop-body.  Use the WANT_NESTED_LOOP state
	 bit to ensure we have only one nested loop at each level.  */
      omp_for_parse_state->اندر_intervening_رمز = سچ;
      body = c_parser_compound_statement (parser, تہی);
      omp_for_parse_state->اندر_intervening_رمز = جھوٹ;
      اگر (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = سچ;
	}
      if_p = تہی;
    }
  ورنہ
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
	  omp_for_parse_state->fail = سچ;
	}
      اندر_statement = اندر_OMP_FOR;
      parser->omp_for_parse_state = تہی;
      body = ڈالو_stmt_list ();
      اگر (omp_for_parse_state->inscan)
	c_parser_omp_جائزہ_loop_body (parser, جھوٹ);
      ورنہ
	جوڑو_stmt (c_parser_c99_بلاک_statement (parser, if_p));
      body = نکالو_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  اندر_statement = save_اندر_statement;
  omp_for_parse_state->want_nested_loop = جھوٹ;
  omp_for_parse_state->اندر_intervening_رمز = سچ;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  اگر (body)
    جوڑو_stmt (body);
  body = c_انتہا_compound_stmt (loc, loop_scope, سچ);
  اگر (decl && درخت_رمز (body) == BIND_اظہاریہ)
    {
      درخت t = BIND_اظہاریہ_VARS (body);
      درخت پچھلا = NULL_درخت, اگلا = NULL_درخت;
      جب (t)
	{
	  اگلا = DECL_CHAIN (t);
	  اگر (t == decl)
	    {
	      اگر (پچھلا)
		DECL_CHAIN (پچھلا) = اگلا;
	      ورنہ
		{
		  BIND_اظہاریہ_VARS (body) = اگلا;
		  بلاک_VARS (BIND_اظہاریہ_بلاک (body)) = اگلا;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      توڑو;
	    }
	  ورنہ
	    {
	      پچھلا = t;
	      t = اگلا;
	    }
	}
      اگر (BIND_اظہاریہ_VARS (body) == NULL_درخت)
	body = BIND_اظہاریہ_BODY (body);
    }

  واپس body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

ساکن درخت
c_parser_omp_for_loop (location_t loc, c_parser *parser, شمار درخت_رمز_2 رمز,
		       درخت clauses, درخت *cclauses, منطقی *if_p)
{
  درخت body, stmt, cl;
  درخت ret = NULL_درخت;
  درخت ordered_cl = NULL_درخت;
  صحیح i, collapse = 1, ordered = 0, گنتی;
  منطقی oacc_tiling = جھوٹ;
  منطقی inscan = جھوٹ;
  ساخت omp_for_parse_ڈیٹا ڈیٹا;
  ساخت omp_for_parse_ڈیٹا *save_ڈیٹا = parser->omp_for_parse_state;

  برائے (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    اگر (OMP_CLAUSE_رمز (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = درخت_مقصد_shwi (OMP_CLAUSE_COLLAPSE_اظہاریہ (cl));
    ورنہ اگر (OMP_CLAUSE_رمز (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = سچ;
	collapse = list_لمبائی (OMP_CLAUSE_TILE_LIST (cl));
      }
    ورنہ اگر (OMP_CLAUSE_رمز (cl) == OMP_CLAUSE_SIZES)
      collapse = list_لمبائی (OMP_CLAUSE_SIZES_LIST (cl));
    ورنہ اگر (OMP_CLAUSE_رمز (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_اظہاریہ (cl))
      {
	ordered_cl = cl;
	ordered = درخت_مقصد_shwi (OMP_CLAUSE_ORDERED_اظہاریہ (cl));
      }
    ورنہ اگر (OMP_CLAUSE_رمز (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (رمز == OMP_SIMD || رمز == OMP_FOR))
      inscan = سچ;

  اگر (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_اظہاریہ (ordered_cl)
	= build_int_cst (integer_type_گرہ, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  گنتی = ordered ? ordered : collapse;

  اگر (!c_parser_omp_اگلا_علامات_can_be_canon_loop (parser, رمز, سچ))
    واپس تہی;

  /* Initialize parse state for recursive descent.  */
  ڈیٹا.declv = make_درخت_vec (گنتی);
  ڈیٹا.initv = make_درخت_vec (گنتی);
  ڈیٹا.condv = make_درخت_vec (گنتی);
  ڈیٹا.incrv = make_درخت_vec (گنتی);
  ڈیٹا.pre_body = NULL_درخت;
  ڈیٹا.bindings = NULL_درخت;
  ڈیٹا.for_loc = c_parser_peek_token (parser)->location;
  ڈیٹا.گنتی = گنتی;
  ڈیٹا.گہرائی = 0;
  ڈیٹا.want_nested_loop = سچ;
  ڈیٹا.ordered = ordered > 0;
  ڈیٹا.اندر_intervening_رمز = جھوٹ;
  ڈیٹا.perfect_nesting_fail = جھوٹ;
  ڈیٹا.fail = جھوٹ;
  ڈیٹا.inscan = inscan;
  ڈیٹا.saw_intervening_رمز = جھوٹ;
  ڈیٹا.رمز = رمز;
  parser->omp_for_parse_state = &ڈیٹا;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  برائے (درخت t = ڈیٹا.bindings; t; )
    {
      درخت n = درخت_CHAIN (t);
      درخت_CHAIN (t) = NULL_درخت;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  اگر (!ڈیٹا.fail)
    {
      c_اندر_omp_for = سچ;
      stmt = c_اختتام_omp_for (loc, رمز, ڈیٹا.declv, تہی, ڈیٹا.initv,
			       ڈیٹا.condv, ڈیٹا.incrv,
			       body, ڈیٹا.pre_body, سچ);
      c_اندر_omp_for = جھوٹ;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      اگر (stmt && !c_omp_check_loop_iv (stmt, ڈیٹا.declv, تہی))
	stmt = NULL_درخت;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      اگر (ڈیٹا.saw_intervening_رمز
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, تہی))
	stmt = NULL_درخت;

      اگر (stmt)
	{
	  جوڑو_stmt (stmt);

	  برائے (i = 0; i < درخت_VEC_لمبائی (OMP_FOR_INIT (stmt)); i++)
	    {
	      درخت init = درخت_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      اگر (init == NULL_درخت)
		توڑو;
	      gcc_assert (درخت_رمز (init) == MODIFY_اظہاریہ);
	      درخت decl = درخت_عملیہ (init, 0);
	      درخت cond = درخت_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (درخت_عملیہ (cond, 0) == decl);

	      درخت op0 = درخت_عملیہ (init, 1);
	      اگر (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || درخت_رمز (op0) != درخت_VEC)
		درخت_عملیہ (init, 1) = c_fully_fold (op0, جھوٹ, تہی);
	      ورنہ
		{
		  درخت_VEC_ELT (op0, 1)
		    = c_fully_fold (درخت_VEC_ELT (op0, 1), جھوٹ, تہی);
		  درخت_VEC_ELT (op0, 2)
		    = c_fully_fold (درخت_VEC_ELT (op0, 2), جھوٹ, تہی);
		}

	      درخت op1 = درخت_عملیہ (cond, 1);
	      اگر (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || درخت_رمز (op1) != درخت_VEC)
		درخت_عملیہ (cond, 1) = c_fully_fold (op1, جھوٹ, تہی);
	      ورنہ
		{
		  درخت_VEC_ELT (op1, 1)
		    = c_fully_fold (درخت_VEC_ELT (op1, 1), جھوٹ, تہی);
		  درخت_VEC_ELT (op1, 2)
		    = c_fully_fold (درخت_VEC_ELT (op1, 2), جھوٹ, تہی);
		}
	    }

	  اگر (cclauses != تہی
	      && cclauses[C_OMP_CLAUSE_بانٹو_PARALLEL] != تہی)
	    {
	      درخت *c;
	      برائے (c = &cclauses[C_OMP_CLAUSE_بانٹو_PARALLEL]; *c ; )
		اگر (OMP_CLAUSE_رمز (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_رمز (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		ورنہ
		  {
		    برائے (i = 0; i < گنتی; i++)
		      اگر (درخت_VEC_ELT (ڈیٹا.declv, i) == OMP_CLAUSE_DECL (*c))
			توڑو;
		    اگر (i == گنتی)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    ورنہ اگر (OMP_CLAUSE_رمز (*c) == OMP_CLAUSE_FIRSTPRIVATE)
		      {
			error_at (loc,
				  "iteration variable %qD should not be firstprivate",
				  OMP_CLAUSE_DECL (*c));
			*c = OMP_CLAUSE_CHAIN (*c);
		      }
		    ورنہ
		      {
			/* Move lastprivate (decl) clause to
			   OMP_FOR_CLAUSES.  */
			درخت l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			اگر (رمز == OMP_SIMD)
			  {
			    OMP_CLAUSE_CHAIN (l)
			      = cclauses[C_OMP_CLAUSE_بانٹو_FOR];
			    cclauses[C_OMP_CLAUSE_بانٹو_FOR] = l;
			  }
			ورنہ
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

  parser->omp_for_parse_state = save_ڈیٹا;
  واپس ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

ساکن خالی
omp_بانٹو_clauses (location_t loc, شمار درخت_رمز_2 رمز,
		   omp_clause_نقاب نقاب, درخت clauses, درخت *cclauses)
{
  صحیح i;
  c_omp_بانٹو_clauses (loc, رمز, نقاب, clauses, cclauses);
  برائے (i = 0; i < C_OMP_CLAUSE_بانٹو_گنتی; i++)
    اگر (cclauses[i])
      cclauses[i] = c_اختتام_omp_clauses (cclauses[i],
					  i == C_OMP_CLAUSE_بانٹو_ہدف
					  ? C_ORT_OMP_ہدف : C_ORT_OMP);
}

/* OpenMP 5.0:
   #pragma omp loop loop-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#تعریف_کرو OMP_LOOP_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_نجی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_BIND)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ترتیب))

ساکن درخت
c_parser_omp_loop (location_t loc, c_parser *parser,
		   حرف *p_name, omp_clause_نقاب نقاب, درخت *cclauses,
		   منطقی *if_p)
{
  درخت بلاک, clauses, ret;

  strcat (p_name, " loop");
  نقاب |= OMP_LOOP_CLAUSE_نقاب;

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == تہی);
  اگر (cclauses)
    {
      omp_بانٹو_clauses (loc, OMP_LOOP, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_بانٹو_LOOP];
    }

  بلاک = c_begin_compound_stmt (سچ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
  جوڑو_stmt (بلاک);

  واپس ret;
}

/* OpenMP 4.0:
   #pragma omp simd simd-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#تعریف_کرو OMP_SIMD_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SAFELEN)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SIMDLEN)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_خطی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALIGNED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_نجی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NONTEMPORAL)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ترتیب))

ساکن درخت
c_parser_omp_simd (location_t loc, c_parser *parser,
		   حرف *p_name, omp_clause_نقاب نقاب, درخت *cclauses,
		   منطقی *if_p)
{
  درخت بلاک, clauses, ret;

  strcat (p_name, " simd");
  نقاب |= OMP_SIMD_CLAUSE_نقاب;

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == تہی);
  اگر (cclauses)
    {
      omp_بانٹو_clauses (loc, OMP_SIMD, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_بانٹو_SIMD];
    }

  بلاک = c_begin_compound_stmt (سچ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
  جوڑو_stmt (بلاک);

  واپس ret;
}

/* OpenMP 2.5:
   #pragma omp for for-clause[optseq] new-line
     for-loop

   OpenMP 4.0:
   #pragma omp for simd for-simd-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#تعریف_کرو OMP_FOR_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_نجی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_خطی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ORDERED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_جدول_وقت)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ترتیب))

ساکن درخت
c_parser_omp_for (location_t loc, c_parser *parser,
		  حرف *p_name, omp_clause_نقاب نقاب, درخت *cclauses,
		  منطقی *if_p)
{
  درخت بلاک, clauses, ret;

  strcat (p_name, " for");
  نقاب |= OMP_FOR_CLAUSE_نقاب;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  اگر (cclauses && (نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    نقاب &= ~(OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  اگر ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DIST_جدول_وقت)) != 0)
    نقاب &= ~(OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);

      اگر (strcmp (p, "simd") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_بانٹو_گنتی];
	  اگر (cclauses == تہی)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    واپس c_parser_omp_simd (loc, parser, p_name, نقاب, cclauses,
				      if_p);
	  بلاک = c_begin_compound_stmt (سچ);
	  ret = c_parser_omp_simd (loc, parser, p_name, نقاب, cclauses, if_p);
	  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
	  اگر (ret == NULL_درخت)
	    واپس ret;
	  ret = make_گرہ (OMP_FOR);
	  درخت_TYPE (ret) = void_type_گرہ;
	  OMP_FOR_BODY (ret) = بلاک;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_بانٹو_FOR];
	  سیٹ_اظہاریہ_LOCATION (ret, loc);
	  جوڑو_stmt (ret);
	  واپس ret;
	}
    }
  اگر (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
      واپس NULL_درخت;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  اگر ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DIST_جدول_وقت)) != 0)
    نقاب &= ~(OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_خطی);

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == تہی);
  اگر (cclauses)
    {
      omp_بانٹو_clauses (loc, OMP_FOR, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_بانٹو_FOR];
    }

  بلاک = c_begin_compound_stmt (سچ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
  جوڑو_stmt (بلاک);

  واپس ret;
}

ساکن درخت c_parser_omp_taskloop (location_t, c_parser *, حرف *,
				   omp_clause_نقاب, درخت *, منطقی *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

ساکن درخت
c_parser_omp_master (location_t loc, c_parser *parser,
		     حرف *p_name, omp_clause_نقاب نقاب, درخت *cclauses,
		     منطقی *if_p, location_t master_loc)
{
  درخت بلاک, clauses, ret;
  gcc_rich_location richloc (loc);
  اگر (master_loc != UNKNOWN_LOCATION)
    richloc.جوڑو_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  strcat (p_name, " master");

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);

      اگر (strcmp (p, "taskloop") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_بانٹو_گنتی];
	  اگر (cclauses == تہی)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    واپس c_parser_omp_taskloop (loc, parser, p_name, نقاب, cclauses,
					  if_p);
	  بلاک = c_begin_compound_stmt (سچ);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, نقاب, cclauses,
				       if_p);
	  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
	  اگر (ret == NULL_درخت)
	    واپس ret;
	  ret = c_اختتام_omp_master (loc, بلاک);
	  OMP_MASTER_COMBINED (ret) = 1;
	  واپس ret;
	}
    }
  اگر (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
      واپس NULL_درخت;
    }

  اگر (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, جھوٹ);
      omp_بانٹو_clauses (loc, OMP_MASTER, نقاب, clauses, cclauses);
    }
  ورنہ
    c_parser_skip_مقصد_pragma_eol (parser);

  واپس c_اختتام_omp_master (loc, c_parser_omp_structured_بلاک (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#تعریف_کرو OMP_MASKED_CLAUSE_نقاب					\
	(OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FILTER)

ساکن درخت
c_parser_omp_masked (location_t loc, c_parser *parser,
		     حرف *p_name, omp_clause_نقاب نقاب, درخت *cclauses,
		     منطقی *if_p)
{
  درخت بلاک, clauses, ret;

  strcat (p_name, " masked");
  نقاب |= OMP_MASKED_CLAUSE_نقاب;

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);

      اگر (strcmp (p, "taskloop") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_بانٹو_گنتی];
	  اگر (cclauses == تہی)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    واپس c_parser_omp_taskloop (loc, parser, p_name, نقاب, cclauses,
					  if_p);
	  بلاک = c_begin_compound_stmt (سچ);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, نقاب, cclauses,
				       if_p);
	  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
	  اگر (ret == NULL_درخت)
	    واپس ret;
	  ret = c_اختتام_omp_masked (loc, بلاک,
				     cclauses[C_OMP_CLAUSE_بانٹو_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  واپس ret;
	}
    }
  اگر (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
      واپس NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == تہی);
  اگر (cclauses)
    {
      omp_بانٹو_clauses (loc, OMP_MASKED, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_بانٹو_MASKED];
    }

  واپس c_اختتام_omp_masked (loc, c_parser_omp_structured_بلاک (parser,
								  if_p),
			      clauses);
}

/* OpenMP 5.1:
   # pragma omp interop clauses[opt] new-line */

#تعریف_کرو OMP_INTEROP_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DESTROY)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_INIT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_USE))

ساکن خالی
c_parser_omp_interop (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  درخت clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_نقاب,
					   "#pragma omp interop");
  درخت stmt = make_گرہ (OMP_INTEROP);
  درخت_TYPE (stmt) = void_type_گرہ;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  سیٹ_اظہاریہ_LOCATION (stmt, loc);
  جوڑو_stmt (stmt);
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

#تعریف_کرو OMP_ORDERED_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_دھاگے)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SIMD))

#تعریف_کرو OMP_ORDERED_DEPEND_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DOACROSS))

ساکن منطقی
c_parser_omp_ordered (c_parser *parser, شمار pragma_context context,
		      منطقی *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  اگر (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
      واپس جھوٹ;
    }

  صحیح n = 1;
  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
    n = 2;

  اگر (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      ثابت حرف *p
	= IDENTIFIER_اشارہ_گر (c_parser_peek_nth_token (parser, n)->قدر);

      اگر (!strcmp ("depend", p) || !strcmp ("doacross", p))
	{
	  اگر (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	      واپس جھوٹ;
	    }
	  اگر (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	      واپس سچ;
	    }

	  درخت clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_نقاب,
					"#pragma omp ordered");
	  c_اختتام_omp_ordered (loc, clauses, NULL_درخت);
	  واپس جھوٹ;
	}
    }

  درخت clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_نقاب,
					   "#pragma omp ordered");

  اگر (!flag_openmp	/* flag_openmp_simd  */
      && omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_SIMD) == NULL_درخت)
    واپس جھوٹ;

  c_اختتام_omp_ordered (loc, clauses,
			c_parser_omp_structured_بلاک (parser, if_p));
  واپس سچ;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

ساکن درخت
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  درخت stmt, substmt;
  منطقی error_suppress = جھوٹ;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  اگر (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = جھوٹ;
      واپس NULL_درخت;
    }

  stmt = ڈالو_stmt_list ();

  اگر (c_parser_peek_token (parser)->pragma_قسم != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_جائزہ (parser, "section", سچ))
    {
      substmt = c_parser_omp_structured_بلاک_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_گرہ, substmt);
      سیٹ_اظہاریہ_LOCATION (substmt, loc);
      جوڑو_stmt (substmt);
    }

  جب (1)
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
	توڑو;
      اگر (c_parser_اگلا_token_is (parser, CPP_EOF))
	توڑو;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_جائزہ (parser, "section", جھوٹ);
      اگر (c_parser_peek_token (parser)->pragma_قسم == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_مقصد_pragma_eol (parser);
	  error_suppress = جھوٹ;
	}
      ورنہ اگر (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = سچ;
	}

      substmt = c_parser_omp_structured_بلاک_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_گرہ, substmt);
      سیٹ_اظہاریہ_LOCATION (substmt, loc);
      جوڑو_stmt (substmt);
    }
  c_parser_skip_until_ملا (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = نکالو_stmt_list (stmt);

  stmt = make_گرہ (OMP_SECTIONS);
  سیٹ_اظہاریہ_LOCATION (stmt, sections_loc);
  درخت_TYPE (stmt) = void_type_گرہ;
  OMP_SECTIONS_BODY (stmt) = substmt;

  واپس جوڑو_stmt (stmt);
}

/* OpenMP 2.5:
   # pragma omp sections sections-clause[optseq] newline
     sections-scope

   LOC is the location of the #pragma token.
*/

#تعریف_کرو OMP_SECTIONS_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_نجی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساکن درخت
c_parser_omp_sections (location_t loc, c_parser *parser,
		       حرف *p_name, omp_clause_نقاب نقاب, درخت *cclauses)
{
  درخت بلاک, clauses, ret;

  strcat (p_name, " sections");
  نقاب |= OMP_SECTIONS_CLAUSE_نقاب;
  اگر (cclauses)
    نقاب &= ~(OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == تہی);
  اگر (cclauses)
    {
      omp_بانٹو_clauses (loc, OMP_SECTIONS, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_بانٹو_SECTIONS];
    }

  بلاک = c_begin_compound_stmt (سچ);
  ret = c_parser_omp_sections_scope (loc, parser);
  اگر (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
  جوڑو_stmt (بلاک);

  واپس ret;
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

#تعریف_کرو OMP_PARALLEL_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_نجی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COPYIN)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_عدد_دھاگے)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

ساکن درخت
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       حرف *p_name, omp_clause_نقاب نقاب, درخت *cclauses,
		       منطقی *if_p)
{
  درخت stmt, clauses, بلاک;

  strcat (p_name, " parallel");
  نقاب |= OMP_PARALLEL_CLAUSE_نقاب;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  اگر ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DIST_جدول_وقت)) == 0)
    نقاب &= ~(OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  اگر (c_parser_اگلا_token_is_keyword (parser, RID_FOR))
    {
      درخت cclauses_buf[C_OMP_CLAUSE_بانٹو_گنتی];
      اگر (cclauses == تہی)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      اگر (!flag_openmp)  /* flag_openmp_simd  */
	واپس c_parser_omp_for (loc, parser, p_name, نقاب, cclauses, if_p);
      بلاک = c_begin_omp_parallel ();
      درخت ret = c_parser_omp_for (loc, parser, p_name, نقاب, cclauses, if_p);
      stmt
	= c_اختتام_omp_parallel (loc, cclauses[C_OMP_CLAUSE_بانٹو_PARALLEL],
				 بلاک);
      اگر (ret == NULL_درخت)
	واپس ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      واپس stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  ورنہ اگر (cclauses
	   && (نقاب & (OMP_CLAUSE_نقاب_1
		       << PRAGMA_OMP_CLAUSE_DIST_جدول_وقت)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_مقصد_pragma_eol (parser);
      واپس NULL_درخت;
    }
  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      location_t ploc = c_parser_peek_token (parser)->location;
      اگر (cclauses == تہی && strcmp (p, "masked") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_بانٹو_گنتی];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    واپس c_parser_omp_masked (loc, parser, p_name, نقاب, cclauses,
					if_p);
	  بلاک = c_begin_omp_parallel ();
	  درخت ret = c_parser_omp_masked (loc, parser, p_name, نقاب, cclauses,
					  if_p);
	  stmt = c_اختتام_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_بانٹو_PARALLEL],
					بلاک);
	  اگر (ret == تہی)
	    واپس ret;
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
	  واپس stmt;
	}
      ورنہ اگر (cclauses == تہی && strcmp (p, "master") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_بانٹو_گنتی];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    واپس c_parser_omp_master (loc, parser, p_name, نقاب, cclauses,
					if_p, ploc);
	  بلاک = c_begin_omp_parallel ();
	  درخت ret = c_parser_omp_master (loc, parser, p_name, نقاب, cclauses,
					  if_p, ploc);
	  stmt = c_اختتام_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_بانٹو_PARALLEL],
					بلاک);
	  اگر (ret == تہی)
	    واپس ret;
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
	  واپس stmt;
	}
      ورنہ اگر (strcmp (p, "loop") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_بانٹو_گنتی];
	  اگر (cclauses == تہی)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    واپس c_parser_omp_loop (loc, parser, p_name, نقاب, cclauses,
				      if_p);
	  بلاک = c_begin_omp_parallel ();
	  درخت ret = c_parser_omp_loop (loc, parser, p_name, نقاب, cclauses,
					if_p);
	  stmt
	    = c_اختتام_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_بانٹو_PARALLEL],
				     بلاک);
	  اگر (ret == NULL_درخت)
	    واپس ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  واپس stmt;
	}
      ورنہ اگر (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	  واپس NULL_درخت;
	}
      ورنہ اگر (cclauses == تہی && strcmp (p, "sections") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_بانٹو_گنتی];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  بلاک = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, نقاب, cclauses);
	  stmt = c_اختتام_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_بانٹو_PARALLEL],
					بلاک);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  واپس stmt;
	}
    }
  ورنہ اگر (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
      واپس NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == تہی);
  اگر (cclauses)
    {
      omp_بانٹو_clauses (loc, OMP_PARALLEL, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_بانٹو_PARALLEL];
    }

  بلاک = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = سچ;
  c_parser_statement (parser, if_p);
  stmt = c_اختتام_omp_parallel (loc, clauses, بلاک);

  واپس stmt;
}

/* OpenMP 2.5:
   # pragma omp single single-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma.
*/

#تعریف_کرو OMP_SINGLE_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_نجی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COPYPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساکن درخت
c_parser_omp_single (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت stmt = make_گرہ (OMP_SINGLE);
  سیٹ_اظہاریہ_LOCATION (stmt, loc);
  درخت_TYPE (stmt) = void_type_گرہ;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_نقاب,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_بلاک (parser, if_p);

  واپس جوڑو_stmt (stmt);
}

/* OpenMP 5.1:
   # pragma omp scope scope-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma.
*/

#تعریف_کرو OMP_SCOPE_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_نجی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساکن درخت
c_parser_omp_scope (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت stmt = make_گرہ (OMP_SCOPE);
  سیٹ_اظہاریہ_LOCATION (stmt, loc);
  درخت_TYPE (stmt) = void_type_گرہ;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_نقاب,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_بلاک (parser, if_p);

  واپس جوڑو_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
ساکن درخت
c_parser_omp_dispatch_body (c_parser *parser)
{
  ساخت c_اظہاریہ lhs, rhs, ret;
  location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
  ماخذ_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_عبارت (parser, تہی, تہی);
  اگر (درخت_رمز (lhs.قدر) == CALL_اظہاریہ)
    واپس lhs.قدر;

  location_t op_location = c_parser_peek_token (parser)->location;
  اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    واپس error_mark_گرہ;

  /* Parse function name.  */
  اگر (!c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      واپس error_mark_گرہ;
    }
  اظہاریہ_loc = c_parser_peek_token (parser)->location;
  درخت id = c_parser_peek_token (parser)->قدر;
  c_parser_consume_token (parser);
  اگر (!c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      واپس error_mark_گرہ;
    }

  rhs.قدر = build_external_ref (اظہاریہ_loc, id, سچ, &rhs.original_type);
  سیٹ_c_اظہاریہ_ماخذ_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_عبارت_after_primary (
    parser, اظہاریہ_LOC_OR_LOC (rhs.قدر, اظہاریہ_loc), rhs);
  اگر (درخت_رمز (rhs.قدر) != CALL_اظہاریہ)
    {
      error_at (اظہاریہ_LOC_OR_LOC (rhs.قدر, اظہاریہ_loc),
		"expected target-function call");
      واپس error_mark_گرہ;
    }

  /* Build assignment. */
  rhs = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, rhs, سچ, سچ);
  ret.قدر
    = build_modify_اظہاریہ (op_location, lhs.قدر, lhs.original_type, NOP_اظہاریہ,
			 اظہاریہ_loc, rhs.قدر, rhs.original_type);
  ret.m_decimal = 0;
  سیٹ_c_اظہاریہ_ماخذ_range (&ret, lhs.get_آغاز (), rhs.get_اختتام ());
  ret.original_رمز = MODIFY_اظہاریہ;
  ret.original_type = تہی;
  واپس ret.قدر;
}

/* OpenMP 5.1:
   # pragma omp dispatch dispatch-clause[optseq] new-line
     expression-stmt

   LOC is the location of the #pragma.
*/

#تعریف_کرو OMP_DISPATCH_CLAUSE_نقاب                                               \
  ((OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE)                             \
   | (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)                           \
   | (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOVARIANTS)                       \
   | (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOCONTEXT)                        \
   | (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR)                  \
   | (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_INTEROP)                          \
   | (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR)                    \
   | (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساکن درخت
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  درخت stmt = make_گرہ (OMP_DISPATCH);
  سیٹ_اظہاریہ_LOCATION (stmt, loc);
  درخت_TYPE (stmt) = void_type_گرہ;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_نقاب,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  درخت depend_clauses = NULL_درخت;
  درخت *depend_clauses_ptr = &depend_clauses;
  برائے (درخت c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  اگر (depend_clauses != NULL_درخت)
    {
      درخت stmt = make_گرہ (OMP_TASK);
      درخت_TYPE (stmt) = void_گرہ;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_درخت;
      سیٹ_اظہاریہ_LOCATION (stmt, loc);
      جوڑو_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  درخت dispatch_body = c_parser_omp_dispatch_body (parser);
  اگر (dispatch_body == error_mark_گرہ)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser);
      واپس NULL_درخت;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (درخت_رمز (dispatch_body) == CALL_اظہاریہ
	      || درخت_رمز (dispatch_body) == MODIFY_اظہاریہ);
  درخت *dispatch_call = درخت_رمز (dispatch_body) == MODIFY_اظہاریہ
			  ? &درخت_عملیہ (dispatch_body, 1)
			  : &dispatch_body;
  جب (درخت_رمز (*dispatch_call) == FLOAT_اظہاریہ
	 || درخت_رمز (*dispatch_call) == CONVERT_اظہاریہ
	 || درخت_رمز (*dispatch_call) == NOP_اظہاریہ)
    dispatch_call = &درخت_عملیہ (*dispatch_call, 0);
  *dispatch_call = build_call_اظہاریہ_اندرونی_loc (
    loc, IFN_GOMP_DISPATCH,
    درخت_TYPE (درخت_TYPE (CALL_اظہاریہ_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_ملا (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  واپس جوڑو_stmt (stmt);
}

/* OpenMP 3.0:
   # pragma omp task task-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#تعریف_کرو OMP_TASK_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_UNTIED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_نجی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FINAL)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MERGEABLE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ترجیح)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_اندر_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DETACH)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_AFFINITY))

ساکن درخت
c_parser_omp_task (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت clauses, بلاک;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_نقاب,
				      "#pragma omp task");

  بلاک = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = سچ;
  c_parser_statement (parser, if_p);
  واپس c_اختتام_omp_task (loc, clauses, بلاک);
}

/* OpenMP 3.0:
   # pragma omp taskwait new-line

   OpenMP 5.0:
   # pragma omp taskwait taskwait-clause[optseq] new-line
*/

#تعریف_کرو OMP_TASKWAIT_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساکن خالی
c_parser_omp_taskwait (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_نقاب,
				"#pragma omp taskwait");

  اگر (clauses)
    {
      درخت stmt = make_گرہ (OMP_TASK);
      درخت_TYPE (stmt) = void_گرہ;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_درخت;
      سیٹ_اظہاریہ_LOCATION (stmt, loc);
      جوڑو_stmt (stmt);
    }
  ورنہ
    c_اختتام_omp_taskwait (loc);
}

/* OpenMP 3.1:
   # pragma omp taskyield new-line
*/

ساکن خالی
c_parser_omp_taskyield (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  c_parser_skip_مقصد_pragma_eol (parser);

  c_اختتام_omp_taskyield (loc);
}

/* OpenMP 4.0:
   # pragma omp taskgroup new-line

   OpenMP 5.0:
   # pragma omp taskgroup taskgroup-clause[optseq] new-line
*/

#تعریف_کرو OMP_TASKGROUP_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_TASK_REDUCTION))

ساکن درخت
c_parser_omp_taskgroup (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_نقاب,
					   "#pragma omp taskgroup");

  درخت body = c_parser_omp_structured_بلاک (parser, if_p);
  واپس c_اختتام_omp_taskgroup (loc, body, clauses);
}

/* OpenMP 4.0:
   # pragma omp cancel cancel-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#تعریف_کرو OMP_CANCEL_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_PARALLEL)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FOR)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SECTIONS)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_TASKGROUP)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF))

ساکن خالی
c_parser_omp_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);
  درخت clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_نقاب,
					   "#pragma omp cancel");

  c_اختتام_omp_cancel (loc, clauses);
}

/* OpenMP 4.0:
   # pragma omp cancellation point cancelpt-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#تعریف_کرو OMP_CANCELLATION_نقطہ_CLAUSE_نقاب			\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_PARALLEL)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FOR)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SECTIONS)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_TASKGROUP))

ساکن منطقی
c_parser_omp_cancellation_نقطہ (c_parser *parser, شمار pragma_context context)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت clauses;
  منطقی نقطہ_نظر_آیا = جھوٹ;

  c_parser_consume_pragma (parser);
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  نقطہ_نظر_آیا = سچ;
	}
    }
  اگر (!نقطہ_نظر_آیا)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_مقصد_pragma_eol (parser);
      واپس جھوٹ;
    }

  اگر (context != pragma_compound)
    {
      اگر (context == pragma_stmt)
	error_at (loc,
		  "%<#pragma %s%> may only be used in compound statements",
		  "omp cancellation point");
      ورنہ
	c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
      واپس سچ;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_نقطہ_CLAUSE_نقاب,
				"#pragma omp cancellation point");

  c_اختتام_omp_cancellation_نقطہ (loc, clauses);
  واپس سچ;
}

/* OpenMP 4.0:
   #pragma omp distribute distribute-clause[optseq] new-line
     for-loop  */

#تعریف_کرو OMP_DISTRIBUTE_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_نجی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DIST_جدول_وقت)\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ترتیب))

ساکن درخت
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 حرف *p_name, omp_clause_نقاب نقاب, درخت *cclauses,
			 منطقی *if_p)
{
  درخت clauses, بلاک, ret;

  strcat (p_name, " distribute");
  نقاب |= OMP_DISTRIBUTE_CLAUSE_نقاب;

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      منطقی simd = جھوٹ;
      منطقی parallel = جھوٹ;

      اگر (strcmp (p, "simd") == 0)
	simd = سچ;
      ورنہ
	parallel = strcmp (p, "parallel") == 0;
      اگر (parallel || simd)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_بانٹو_گنتی];
	  اگر (cclauses == تہی)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      اگر (simd)
		واپس c_parser_omp_simd (loc, parser, p_name, نقاب, cclauses,
					  if_p);
	      ورنہ
		واپس c_parser_omp_parallel (loc, parser, p_name, نقاب,
					      cclauses, if_p);
	    }
	  بلاک = c_begin_compound_stmt (سچ);
	  اگر (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, نقاب, cclauses,
				     if_p);
	  ورنہ
	    ret = c_parser_omp_parallel (loc, parser, p_name, نقاب, cclauses,
					 if_p);
	  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
	  اگر (ret == تہی)
	    واپس ret;
	  ret = make_گرہ (OMP_DISTRIBUTE);
	  درخت_TYPE (ret) = void_type_گرہ;
	  OMP_FOR_BODY (ret) = بلاک;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_بانٹو_DISTRIBUTE];
	  سیٹ_اظہاریہ_LOCATION (ret, loc);
	  جوڑو_stmt (ret);
	  واپس ret;
	}
    }
  اگر (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
      واپس NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == تہی);
  اگر (cclauses)
    {
      omp_بانٹو_clauses (loc, OMP_DISTRIBUTE, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_بانٹو_DISTRIBUTE];
    }

  بلاک = c_begin_compound_stmt (سچ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, تہی,
			       if_p);
  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
  جوڑو_stmt (بلاک);

  واپس ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#تعریف_کرو OMP_TEAMS_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_نجی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_عدد_TEAMS)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_THREAD_حد_بندی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

ساکن درخت
c_parser_omp_teams (location_t loc, c_parser *parser,
		    حرف *p_name, omp_clause_نقاب نقاب, درخت *cclauses,
		    منطقی *if_p)
{
  درخت clauses, بلاک, ret;

  strcat (p_name, " teams");
  نقاب |= OMP_TEAMS_CLAUSE_نقاب;

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp (p, "distribute") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_بانٹو_گنتی];
	  اگر (cclauses == تہی)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    واپس c_parser_omp_distribute (loc, parser, p_name, نقاب,
					    cclauses, if_p);
	  بلاک = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, نقاب, cclauses,
					 if_p);
	  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
	  اگر (ret == تہی)
	    واپس ret;
	  clauses = cclauses[C_OMP_CLAUSE_بانٹو_TEAMS];
	  ret = make_گرہ (OMP_TEAMS);
	  درخت_TYPE (ret) = void_type_گرہ;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = بلاک;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  سیٹ_اظہاریہ_LOCATION (ret, loc);
	  واپس جوڑو_stmt (ret);
	}
      ورنہ اگر (strcmp (p, "loop") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_بانٹو_گنتی];
	  اگر (cclauses == تہی)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    واپس c_parser_omp_loop (loc, parser, p_name, نقاب, cclauses,
				      if_p);
	  بلاک = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, نقاب, cclauses, if_p);
	  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
	  اگر (ret == تہی)
	    واپس ret;
	  clauses = cclauses[C_OMP_CLAUSE_بانٹو_TEAMS];
	  ret = make_گرہ (OMP_TEAMS);
	  درخت_TYPE (ret) = void_type_گرہ;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = بلاک;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  سیٹ_اظہاریہ_LOCATION (ret, loc);
	  واپس جوڑو_stmt (ret);
	}
    }
  اگر (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
      واپس NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == تہی);
  اگر (cclauses)
    {
      omp_بانٹو_clauses (loc, OMP_TEAMS, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_بانٹو_TEAMS];
    }

  درخت stmt = make_گرہ (OMP_TEAMS);
  درخت_TYPE (stmt) = void_type_گرہ;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  بلاک = c_begin_omp_parallel ();
  جوڑو_stmt (c_parser_omp_structured_بلاک (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_انتہا_compound_stmt (loc, بلاک, سچ);
  سیٹ_اظہاریہ_LOCATION (stmt, loc);

  واپس جوڑو_stmt (stmt);
}

/* OpenMP 4.0:
   # pragma omp target data target-data-clause[optseq] new-line
     structured-block  */

#تعریف_کرو OMP_ہدف_ڈیٹا_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR) \
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR))

ساکن درخت
c_parser_omp_ہدف_ڈیٹا (location_t loc, c_parser *parser, منطقی *if_p)
{
  اگر (flag_openmp)
    omp_requires_نقاب
      = (شمار omp_requires) (omp_requires_نقاب | OMP_REQUIRES_ہدف_مستعمل);

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_ہدف_ڈیٹا_CLAUSE_نقاب,
				"#pragma omp target data", جھوٹ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_اختتام_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, جھوٹ);
  صحیح map_نظر_آیا = 0;
  برائے (درخت *pc = &clauses; *pc;)
    {
      اگر (OMP_CLAUSE_رمز (*pc) == OMP_CLAUSE_MAP)
	انتخاب (OMP_CLAUSE_MAP_قسم (*pc))
	  {
	  حالت GOMP_MAP_مقصد:
	  حالت GOMP_MAP_ALWAYS_مقصد:
	  حالت GOMP_MAP_PRESENT_مقصد:
	  حالت GOMP_MAP_ALWAYS_PRESENT_مقصد:
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
	    map_نظر_آیا = 3;
	    توڑو;
	  حالت GOMP_MAP_FIRSTPRIVATE_اشارہ_گر:
	  حالت GOMP_MAP_ALWAYS_اشارہ_گر:
	  حالت GOMP_MAP_ATTACH_DETACH:
	  حالت GOMP_MAP_ATTACH:
	    توڑو;
	  طےشدہ:
	    map_نظر_آیا |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    جاری;
	  }
      ورنہ اگر (OMP_CLAUSE_رمز (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_رمز (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_نظر_آیا = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  اگر (map_نظر_آیا != 3)
    {
      اگر (map_نظر_آیا == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      واپس NULL_درخت;
    }

  درخت stmt = make_گرہ (OMP_ہدف_ڈیٹا);
  درخت_TYPE (stmt) = void_type_گرہ;
  OMP_ہدف_ڈیٹا_CLAUSES (stmt) = clauses;
  keep_اگلا_level ();
  درخت بلاک = c_begin_compound_stmt (سچ);
  جوڑو_stmt (c_parser_omp_structured_بلاک (parser, if_p));
  OMP_ہدف_ڈیٹا_BODY (stmt) = c_انتہا_compound_stmt (loc, بلاک, سچ);

  سیٹ_اظہاریہ_LOCATION (stmt, loc);
  واپس جوڑو_stmt (stmt);
}

/* OpenMP 4.0:
   # pragma omp target update target-update-clause[optseq] new-line */

#تعریف_کرو OMP_ہدف_UPDATE_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FROM)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_مقصد)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساکن منطقی
c_parser_omp_ہدف_update (location_t loc, c_parser *parser,
			    شمار pragma_context context)
{
  اگر (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
      واپس سچ;
    }

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_ہدف_UPDATE_CLAUSE_نقاب,
				"#pragma omp target update",
				/* finish_p = */ جھوٹ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_اختتام_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  اگر (omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_مقصد) == NULL_درخت
      && omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_FROM) == NULL_درخت)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      واپس جھوٹ;
    }

  اگر (flag_openmp)
    omp_requires_نقاب
      = (شمار omp_requires) (omp_requires_نقاب | OMP_REQUIRES_ہدف_مستعمل);

  درخت stmt = make_گرہ (OMP_ہدف_UPDATE);
  درخت_TYPE (stmt) = void_type_گرہ;
  OMP_ہدف_UPDATE_CLAUSES (stmt) = clauses;
  سیٹ_اظہاریہ_LOCATION (stmt, loc);
  جوڑو_stmt (stmt);
  واپس جھوٹ;
}

/* OpenMP 4.5:
   # pragma omp target enter data target-data-clause[optseq] new-line  */

#تعریف_کرو OMP_ہدف_ENTER_ڈیٹا_CLAUSE_نقاب			\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساکن منطقی
c_parser_omp_ہدف_enter_ڈیٹا (location_t loc, c_parser *parser,
				شمار pragma_context context)
{
  منطقی ڈیٹا_نظر_آیا = جھوٹ;
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  ڈیٹا_نظر_آیا = سچ;
	}
    }
  اگر (!ڈیٹا_نظر_آیا)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_مقصد_pragma_eol (parser);
      واپس جھوٹ;
    }

  اگر (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
      واپس سچ;
    }

  اگر (flag_openmp)
    omp_requires_نقاب
      = (شمار omp_requires) (omp_requires_نقاب | OMP_REQUIRES_ہدف_مستعمل);

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_ہدف_ENTER_ڈیٹا_CLAUSE_نقاب,
				"#pragma omp target enter data", جھوٹ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_اختتام_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, جھوٹ);
  صحیح map_نظر_آیا = 0;
  برائے (درخت *pc = &clauses; *pc;)
    {
      اگر (OMP_CLAUSE_رمز (*pc) == OMP_CLAUSE_MAP)
	انتخاب (OMP_CLAUSE_MAP_قسم (*pc))
	  {
	  حالت GOMP_MAP_مقصد:
	  حالت GOMP_MAP_ALWAYS_مقصد:
	  حالت GOMP_MAP_PRESENT_مقصد:
	  حالت GOMP_MAP_ALWAYS_PRESENT_مقصد:
	  حالت GOMP_MAP_ALLOC:
	  حالت GOMP_MAP_PRESENT_ALLOC:
	    map_نظر_آیا = 3;
	    توڑو;
	  حالت GOMP_MAP_TOFROM:
	    OMP_CLAUSE_سیٹ_MAP_قسم (*pc, GOMP_MAP_مقصد);
	    map_نظر_آیا = 3;
	    توڑو;
	  حالت GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_سیٹ_MAP_قسم (*pc, GOMP_MAP_ALWAYS_مقصد);
	    map_نظر_آیا = 3;
	    توڑو;
	  حالت GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_سیٹ_MAP_قسم (*pc, GOMP_MAP_PRESENT_مقصد);
	    map_نظر_آیا = 3;
	    توڑو;
	  حالت GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_سیٹ_MAP_قسم (*pc, GOMP_MAP_ALWAYS_PRESENT_مقصد);
	    map_نظر_آیا = 3;
	    توڑو;
	  حالت GOMP_MAP_FIRSTPRIVATE_اشارہ_گر:
	  حالت GOMP_MAP_ALWAYS_اشارہ_گر:
	  حالت GOMP_MAP_ATTACH_DETACH:
	  حالت GOMP_MAP_ATTACH:
	    توڑو;
	  طےشدہ:
	    map_نظر_آیا |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    جاری;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  اگر (map_نظر_آیا != 3)
    {
      اگر (map_نظر_آیا == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      واپس سچ;
    }

  درخت stmt = make_گرہ (OMP_ہدف_ENTER_ڈیٹا);
  درخت_TYPE (stmt) = void_type_گرہ;
  OMP_ہدف_ENTER_ڈیٹا_CLAUSES (stmt) = clauses;
  سیٹ_اظہاریہ_LOCATION (stmt, loc);
  جوڑو_stmt (stmt);
  واپس سچ;
}

/* OpenMP 4.5:
   # pragma omp target exit data target-data-clause[optseq] new-line  */

#تعریف_کرو OMP_ہدف_EXIT_ڈیٹا_CLAUSE_نقاب			\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساکن منطقی
c_parser_omp_ہدف_exit_ڈیٹا (location_t loc, c_parser *parser,
			       شمار pragma_context context)
{
  منطقی ڈیٹا_نظر_آیا = جھوٹ;
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  ڈیٹا_نظر_آیا = سچ;
	}
    }
  اگر (!ڈیٹا_نظر_آیا)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_مقصد_pragma_eol (parser);
      واپس جھوٹ;
    }

  اگر (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
      واپس سچ;
    }

  اگر (flag_openmp)
    omp_requires_نقاب
      = (شمار omp_requires) (omp_requires_نقاب | OMP_REQUIRES_ہدف_مستعمل);

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_ہدف_EXIT_ڈیٹا_CLAUSE_نقاب,
				"#pragma omp target exit data", جھوٹ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_ڈیٹا);
  clauses = c_اختتام_omp_clauses (clauses, C_ORT_OMP_EXIT_ڈیٹا);
  c_omp_adjust_map_clauses (clauses, جھوٹ);
  صحیح map_نظر_آیا = 0;
  برائے (درخت *pc = &clauses; *pc;)
    {
      اگر (OMP_CLAUSE_رمز (*pc) == OMP_CLAUSE_MAP)
	انتخاب (OMP_CLAUSE_MAP_قسم (*pc))
	  {
	  حالت GOMP_MAP_FROM:
	  حالت GOMP_MAP_ALWAYS_FROM:
	  حالت GOMP_MAP_PRESENT_FROM:
	  حالت GOMP_MAP_ALWAYS_PRESENT_FROM:
	  حالت GOMP_MAP_RELEASE:
	  حالت GOMP_MAP_DELETE:
	    map_نظر_آیا = 3;
	    توڑو;
	  حالت GOMP_MAP_TOFROM:
	    OMP_CLAUSE_سیٹ_MAP_قسم (*pc, GOMP_MAP_FROM);
	    map_نظر_آیا = 3;
	    توڑو;
	  حالت GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_سیٹ_MAP_قسم (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_نظر_آیا = 3;
	    توڑو;
	  حالت GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_سیٹ_MAP_قسم (*pc, GOMP_MAP_PRESENT_FROM);
	    map_نظر_آیا = 3;
	    توڑو;
	  حالت GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_سیٹ_MAP_قسم (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_نظر_آیا = 3;
	    توڑو;
	  حالت GOMP_MAP_FIRSTPRIVATE_اشارہ_گر:
	  حالت GOMP_MAP_ALWAYS_اشارہ_گر:
	  حالت GOMP_MAP_ATTACH_DETACH:
	  حالت GOMP_MAP_DETACH:
	    توڑو;
	  طےشدہ:
	    map_نظر_آیا |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target exit data%> with map-type other "
		      "than %<from%>, %<tofrom%>, %<release%> or %<delete%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    جاری;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  اگر (map_نظر_آیا != 3)
    {
      اگر (map_نظر_آیا == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      واپس سچ;
    }

  درخت stmt = make_گرہ (OMP_ہدف_EXIT_ڈیٹا);
  درخت_TYPE (stmt) = void_type_گرہ;
  OMP_ہدف_EXIT_ڈیٹا_CLAUSES (stmt) = clauses;
  سیٹ_اظہاریہ_LOCATION (stmt, loc);
  جوڑو_stmt (stmt);
  واپس سچ;
}

/* OpenMP 4.0:
   # pragma omp target target-clause[optseq] new-line
     structured-block  */

#تعریف_کرو OMP_ہدف_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEFAULTMAP)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE) \
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR) \
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_اندر_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR)\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_نجی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_THREAD_حد_بندی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_استعمال_کرتا_ALLOCATORS))

ساکن منطقی
c_parser_omp_ہدف (c_parser *parser, شمار pragma_context context, منطقی *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  درخت *pc = تہی, stmt, بلاک, body, clauses;

  اگر (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_مقصد_pragma_eol (parser);
      واپس جھوٹ;
    }

  اگر (flag_openmp)
    omp_requires_نقاب
      = (شمار omp_requires) (omp_requires_نقاب | OMP_REQUIRES_ہدف_مستعمل);

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      شمار درخت_رمز_2 ccode = ERROR_MARK;

      اگر (strcmp (p, "teams") == 0)
	ccode = OMP_TEAMS;
      ورنہ اگر (strcmp (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      ورنہ اگر (strcmp (p, "simd") == 0)
	ccode = OMP_SIMD;
      اگر (ccode != ERROR_MARK)
	{
	  درخت cclauses[C_OMP_CLAUSE_بانٹو_گنتی];
	  حرف p_name[حجم ("#pragma omp target teams distribute "
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
					     OMP_ہدف_CLAUSE_نقاب,
					     cclauses, if_p);
		  توڑو;
		حالت OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_ہدف_CLAUSE_نقاب,
						cclauses, if_p);
		  توڑو;
		حالت OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_ہدف_CLAUSE_نقاب,
					    cclauses, if_p);
		  توڑو;
		طےشدہ:
		  gcc_unreachable ();
		}
	      واپس stmt != NULL_درخت;
	    }
	  keep_اگلا_level ();
	  درخت بلاک = c_begin_compound_stmt (سچ), ret;
	  انتخاب (ccode)
	    {
	    حالت OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_ہدف_CLAUSE_نقاب, cclauses,
					if_p);
	      توڑو;
	    حالت OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_ہدف_CLAUSE_نقاب, cclauses,
					   if_p);
	      توڑو;
	    حالت OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_ہدف_CLAUSE_نقاب, cclauses,
				       if_p);
	      توڑو;
	    طےشدہ:
	      gcc_unreachable ();
	    }
	  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
	  اگر (ret == NULL_درخت)
	    واپس جھوٹ;
	  اگر (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    برائے (درخت c = cclauses[C_OMP_CLAUSE_بانٹو_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_عدد_TEAMS
		  || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_THREAD_حد_بندی)
		برائے (صحیح i = 0;
		     i <= (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_عدد_TEAMS); ++i)
		  اگر (OMP_CLAUSE_عملیہ (c, i)
		      && درخت_رمز (OMP_CLAUSE_عملیہ (c, i)) != INTEGER_CST)
		    {
		      درخت اظہاریہ = OMP_CLAUSE_عملیہ (c, i);
		      درخت tmp = create_tmp_var_raw (درخت_TYPE (اظہاریہ));
		      اظہاریہ = build4 (ہدف_اظہاریہ, درخت_TYPE (اظہاریہ), tmp,
				     اظہاریہ, NULL_درخت, NULL_درخت);
		      جوڑو_stmt (اظہاریہ);
		      OMP_CLAUSE_عملیہ (c, i) = اظہاریہ;
		      درخت tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_بانٹو_ہدف];
		      cclauses[C_OMP_CLAUSE_بانٹو_ہدف] = tc;
		    }
	  درخت stmt = make_گرہ (OMP_ہدف);
	  درخت_TYPE (stmt) = void_type_گرہ;
	  OMP_ہدف_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_بانٹو_ہدف];
	  c_omp_adjust_map_clauses (OMP_ہدف_CLAUSES (stmt), سچ);
	  OMP_ہدف_BODY (stmt) = بلاک;
	  OMP_ہدف_COMBINED (stmt) = 1;
	  سیٹ_اظہاریہ_LOCATION (stmt, loc);
	  جوڑو_stmt (stmt);
	  pc = &OMP_ہدف_CLAUSES (stmt);
	  جاؤ check_clauses;
	}
      ورنہ اگر (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	  واپس جھوٹ;
	}
      ورنہ اگر (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_ہدف_ڈیٹا (loc, parser, if_p);
	  واپس سچ;
	}
      ورنہ اگر (strcmp (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  واپس c_parser_omp_ہدف_enter_ڈیٹا (loc, parser, context);
	}
      ورنہ اگر (strcmp (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  واپس c_parser_omp_ہدف_exit_ڈیٹا (loc, parser, context);
	}
      ورنہ اگر (strcmp (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  واپس c_parser_omp_ہدف_update (loc, parser, context);
	}
    }
  اگر (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
      واپس جھوٹ;
    }

  stmt = make_گرہ (OMP_ہدف);
  درخت_TYPE (stmt) = void_type_گرہ;

  clauses = c_parser_omp_all_clauses (parser, OMP_ہدف_CLAUSE_نقاب,
				      "#pragma omp target", جھوٹ);
  برائے (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_اندر_REDUCTION)
      {
	درخت nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_سیٹ_MAP_قسم (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_ہدف);
  clauses  = c_اختتام_omp_clauses (clauses, C_ORT_OMP_ہدف);
  c_omp_adjust_map_clauses (clauses, سچ);

  keep_اگلا_level ();
  بلاک = c_begin_compound_stmt (سچ);
  body = c_parser_omp_structured_بلاک (parser, if_p);

  c_omp_جائزہ_mapper_bindings (loc, &clauses, body);

  جوڑو_stmt (body);
  OMP_ہدف_CLAUSES (stmt) = clauses;
  pc = &OMP_ہدف_CLAUSES (stmt);
  OMP_ہدف_BODY (stmt) = c_انتہا_compound_stmt (loc, بلاک, سچ);

  سیٹ_اظہاریہ_LOCATION (stmt, loc);
  جوڑو_stmt (stmt);

check_clauses:
  جب (*pc)
    {
      اگر (OMP_CLAUSE_رمز (*pc) == OMP_CLAUSE_MAP)
	انتخاب (OMP_CLAUSE_MAP_قسم (*pc))
	  {
	  حالت GOMP_MAP_مقصد:
	  حالت GOMP_MAP_ALWAYS_مقصد:
	  حالت GOMP_MAP_PRESENT_مقصد:
	  حالت GOMP_MAP_ALWAYS_PRESENT_مقصد:
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
	  حالت GOMP_MAP_FIRSTPRIVATE_اشارہ_گر:
	  حالت GOMP_MAP_ALWAYS_اشارہ_گر:
	  حالت GOMP_MAP_اشارہ_گر:
	  حالت GOMP_MAP_ATTACH_DETACH:
	  حالت GOMP_MAP_ATTACH:
	    توڑو;
	  طےشدہ:
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    جاری;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }
  cfun->has_omp_ہدف = سچ;
  واپس سچ;
}

/* OpenMP 4.0:
   # pragma omp declare simd declare-simd-clauses[optseq] new-line

   OpenMP 5.0:
   # pragma omp declare variant (identifier) match(context-selector) new-line

   OpenMP 5.1
   # pragma omp declare variant (identifier) match(context-selector) \
      adjust_args(adjust-op:argument-list) append_args(interop-list) new-line
   */

#تعریف_کرو OMP_DECLARE_SIMD_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SIMDLEN)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_خطی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALIGNED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_یکساں)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_INBRANCH)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOTINBRANCH))

ساکن خالی
c_parser_omp_declare_simd (c_parser *parser, شمار pragma_context context)
{
  c_token *token = c_parser_peek_token (parser);
  gcc_assert (token->type == CPP_NAME);
  درخت قسم = token->قدر;
  gcc_assert (strcmp (IDENTIFIER_اشارہ_گر (قسم), "simd") == 0
	      || strcmp (IDENTIFIER_اشارہ_گر (قسم), "variant") == 0);

  auto_vec<c_token> clauses;
  جب (c_parser_اگلا_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      اگر (token->type == CPP_EOF)
	{
	  c_parser_skip_مقصد_pragma_eol (parser);
	  واپس;
	}
      clauses.محفوظ_ڈالو (*token);
      c_parser_consume_token (parser);
    }
  clauses.محفوظ_ڈالو (*c_parser_peek_token (parser));
  c_parser_skip_مقصد_pragma_eol (parser);

  جب (c_parser_اگلا_token_is (parser, CPP_PRAGMA))
    {
      اگر (c_parser_peek_token (parser)->pragma_قسم != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->قدر != قسم)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_اشارہ_گر (قسم), IDENTIFIER_اشارہ_گر (قسم));
	  واپس;
	}
      c_parser_consume_pragma (parser);
      جب (c_parser_اگلا_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  اگر (token->type == CPP_EOF)
	    {
	      c_parser_skip_مقصد_pragma_eol (parser);
	      واپس;
	    }
	  clauses.محفوظ_ڈالو (*token);
	  c_parser_consume_token (parser);
	}
      clauses.محفوظ_ڈالو (*c_parser_peek_token (parser));
      c_parser_skip_مقصد_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  memset (&eof_token, 0, حجم (eof_token));
  eof_token.type = CPP_EOF;
  clauses.محفوظ_ڈالو (eof_token);
  clauses.محفوظ_ڈالو (eof_token);

  انتخاب (context)
    {
    حالت pragma_external:
      اگر (c_parser_اگلا_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحیح ext = disable_extension_diagnostics ();
	  کرو
	    c_parser_consume_token (parser);
	  جب (c_parser_اگلا_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, جھوٹ, سچ,
					 جھوٹ, تہی, &clauses);
	  restore_extension_diagnostics (ext);
	}
      ورنہ
	c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, جھوٹ, سچ,
				       جھوٹ, تہی, &clauses);
      توڑو;
    حالت pragma_struct:
    حالت pragma_param:
    حالت pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_اشارہ_گر (قسم));
      توڑو;
    حالت pragma_compound:
      منطقی have_std_attrs;
      درخت std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_اوصاف (parser, 1);
      اگر (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      ورنہ
	std_attrs = NULL_درخت;
      اگر (c_parser_اگلا_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحیح ext = disable_extension_diagnostics ();
	  کرو
	    c_parser_consume_token (parser);
	  جب (c_parser_اگلا_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  اگر (c_parser_اگلا_علامات_آغاز_declaration (parser)
	      || c_parser_nth_token_starts_std_اوصاف (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, سچ,
					     سچ, جھوٹ, تہی, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      توڑو;
	    }
	  restore_extension_diagnostics (ext);
	}
      ورنہ اگر (c_parser_اگلا_علامات_آغاز_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, سچ, سچ,
					 جھوٹ, تہی, &clauses, have_std_attrs,
					 std_attrs);
	  توڑو;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_اشارہ_گر (قسم));
      توڑو;
    طےشدہ:
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

ساکن درخت
c_parser_omp_context_selector (c_parser *parser, شمار omp_tss_رمز سیٹ,
			       درخت parms)
{
  درخت ret = NULL_درخت;
  کرو
    {
      درخت selector;
      اگر (c_parser_اگلا_token_is (parser, CPP_KEYWORD)
	  || c_parser_اگلا_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->قدر;
      ورنہ
	{
	  c_parser_error (parser, "expected trait selector name");
	  واپس error_mark_گرہ;
	}
      شمار omp_ts_رمز sel
	= omp_lookup_ts_رمز (سیٹ, IDENTIFIER_اشارہ_گر (selector));

      اگر (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_اشارہ_گر (selector),  omp_tss_map[سیٹ]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_درخت, NULL_درخت, ret);
	  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_متوازن_token_sequence (parser);
	  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      جاری;
	    }
	  ورنہ
	    توڑو;
	}

      c_parser_consume_token (parser);

      درخت properties = NULL_درخت;
      درخت scoreval = NULL_درخت;
      شمار omp_tp_type property_قسم = omp_ts_map[sel].tp_type;
      منطقی allow_score = omp_ts_map[sel].allow_score;
      درخت t;

      اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
	{
	  اگر (property_قسم == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_اشارہ_گر (selector));
	      واپس error_mark_گرہ;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_اشارہ_گر (token->قدر), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      درخت score = c_parser_اظہاریہ_no_commas (parser, تہی).قدر;
	      parens2.skip_until_ملا_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      اگر (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[سیٹ]);
	      ورنہ اگر (score != error_mark_گرہ)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, جھوٹ, تہی);
		  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (score))
		      || درخت_رمز (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  ورنہ اگر (درخت_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  ورنہ
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  انتخاب (property_قسم)
	    {
	    حالت OMP_TRAIT_PROPERTY_ID:
	      اگر (c_parser_اگلا_token_is (parser, CPP_KEYWORD)
		  || c_parser_اگلا_token_is (parser, CPP_NAME))
		{
		  درخت prop = c_parser_peek_token (parser)->قدر;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_درخت,
						    properties);
		}
	      ورنہ
		{
		  c_parser_error (parser, "expected identifier");
		  واپس error_mark_گرہ;
		}
	      توڑو;
	    حالت OMP_TRAIT_PROPERTY_NAME_LIST:
	      کرو
		{
		  درخت prop = OMP_TP_NAMELIST_گرہ;
		  درخت قدر = NULL_درخت;
		  اگر (c_parser_اگلا_token_is (parser, CPP_KEYWORD)
		      || c_parser_اگلا_token_is (parser, CPP_NAME))
		    {
		      قدر = c_parser_peek_token (parser)->قدر;
		      c_parser_consume_token (parser);
		    }
		  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_STRING))
		    قدر = c_parser_string_literal (parser, جھوٹ,
						     جھوٹ).قدر;
		  ورنہ
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      واپس error_mark_گرہ;
		    }

		  properties = make_trait_property (prop, قدر, properties);

		  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  ورنہ
		    توڑو;
		}
	      جب (1);
	      توڑو;
	    حالت OMP_TRAIT_PROPERTY_DEV_عدد_اظہاریہ:
	    حالت OMP_TRAIT_PROPERTY_BOOL_اظہاریہ:
	      {
		c_اظہاریہ texpr = c_parser_اظہاریہ_no_commas (parser, تہی);
		texpr = convert_lvalue_مقصد_rvalue (token->location, texpr,
						  سچ, سچ);
		t = texpr.قدر;
	      }
	      اگر (t == error_mark_گرہ)
		واپس error_mark_گرہ;
	      mark_exp_read (t);
	      اگر (property_قسم == OMP_TRAIT_PROPERTY_BOOL_اظہاریہ)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_گرہ);
		  اگر (t == error_mark_گرہ)
		    واپس error_mark_گرہ;
		}
	      ورنہ اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  واپس error_mark_گرہ;
		}
	      t = c_fully_fold (t, جھوٹ, تہی);
	      properties = make_trait_property (NULL_درخت, t, properties);
	      توڑو;
	    حالت OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      اگر (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  اگر (parms == NULL_درخت)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      واپس error_mark_گرہ;
		    }
		  درخت c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_نقاب,
						"simd", سچ, 2);
		  c = c_omp_declare_simd_clauses_مقصد_numbers (parms
							     == error_mark_گرہ
							     ? NULL_درخت : parms,
							     c);
		  properties = c;
		}
	      ورنہ اگر (sel == OMP_TRAIT_IMPLEMENTATION_REQUIRES)
		{
		  /* FIXME: The "requires" selector was added in OpenMP 5.1.
		     Currently only the now-deprecated syntax
		     from OpenMP 5.0 is supported.  */
		  sorry_at (token->location,
			    "%<requires%> selector is not supported yet");
		  واپس error_mark_گرہ;
		}
	      ورنہ
		gcc_unreachable ();
	      توڑو;
	    طےشدہ:
	      gcc_unreachable ();
	    }

	  parens.skip_until_ملا_close (parser);
	  properties = nreverse (properties);
	}
      ورنہ اگر (property_قسم != OMP_TRAIT_PROPERTY_NONE
	       && property_قسم != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_قسم != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  واپس error_mark_گرہ;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ورنہ
	توڑو;
    }
  جب (1);

  واپس nreverse (ret);
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

ساکن درخت
c_parser_omp_context_selector_specification (c_parser *parser, درخت parms)
{
  درخت ret = NULL_درخت;
  کرو
    {
      ثابت حرف *setp = "";
      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      شمار omp_tss_رمز سیٹ = omp_lookup_tss_رمز (setp);

      اگر (سیٹ == OMP_TRAIT_سیٹ_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  واپس error_mark_گرہ;
	}

      c_parser_consume_token (parser);

      اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	واپس error_mark_گرہ;

      matching_braces braces;
      اگر (!braces.require_open (parser))
	واپس error_mark_گرہ;

      درخت selectors = c_parser_omp_context_selector (parser, سیٹ, parms);
      اگر (selectors == error_mark_گرہ)
	{
	  c_parser_skip_مقصد_closing_brace (parser);
	  ret = error_mark_گرہ;
	}
      ورنہ اگر (ret != error_mark_گرہ)
	ret = make_trait_سیٹ_selector (سیٹ, selectors, ret);

      braces.require_close (parser);

      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ورنہ
	توڑو;
    }
  جب (1);

  اگر (ret == error_mark_گرہ)
    واپس ret;
  واپس nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

ساکن خالی
c_اختتام_omp_declare_variant (c_parser *parser, درخت fndecl, درخت parms)
{
  matching_parens parens;
  اگر (!parens.require_open (parser))
    {
     fail:
      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
      واپس;
    }

  اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_قسم != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      جاؤ fail;
    }

  c_token *token = c_parser_peek_token (parser);
  درخت variant = lookup_name (token->قدر);

  اگر (variant == NULL_درخت)
    {
      undeclared_variable (token->location, token->قدر);
      variant = error_mark_گرہ;
    }
  ورنہ اگر (درخت_رمز (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_گرہ;
    }
  ورنہ اگر (fndecl_built_اندر_p (variant)
	   && (لڑی_موازنہ (IDENTIFIER_اشارہ_گر (DECL_NAME (variant)),
			"__builtin_", لڑی_لمبائی ("__builtin_")) == 0
	       || لڑی_موازنہ (IDENTIFIER_اشارہ_گر (DECL_NAME (variant)),
			   "__sync_", لڑی_لمبائی ("__sync_")) == 0
	       || لڑی_موازنہ (IDENTIFIER_اشارہ_گر (DECL_NAME (variant)),
			   "__atomic_", لڑی_لمبائی ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_گرہ;
    }
  ورنہ اگر (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_گرہ;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  درخت append_دلائل_درخت = NULL_درخت;
  درخت append_دلائل_آخری;
  vec<درخت> adjust_دلائل_list = vNULL;
  منطقی has_مطابقت = جھوٹ, has_adjust_دلائل = جھوٹ;
  location_t adjust_دلائل_loc = UNKNOWN_LOCATION;
  location_t append_دلائل_loc = UNKNOWN_LOCATION;
  location_t مطابقت_loc = UNKNOWN_LOCATION;
  درخت need_device_ptr_list = NULL_درخت;
  درخت ctx = error_mark_گرہ;

  کرو
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ثابت حرف *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);

      شمار clause
      {
	مطابقت,
	adjust_دلائل,
	append_دلائل
      } ccode;

      اگر (strcmp (clause, "match") == 0)
	{
	  ccode = مطابقت;
	  مطابقت_loc = loc;
	}
      ورنہ اگر (strcmp (clause, "adjust_args") == 0)
	{
	  ccode = adjust_دلائل;
	  adjust_دلائل_loc = loc;
	}
      ورنہ اگر (strcmp (clause, "append_args") == 0)
	{
	  ccode = append_دلائل;
	  append_دلائل_loc = loc;
	}
      ورنہ
	{
	  c_parser_error (parser, "expected %<match%>, %<adjust_args%> or "
				  "%<append_args%> clause");
	  جاؤ fail;
	}

      c_parser_consume_token (parser);

      اگر (!parens.require_open (parser))
	جاؤ fail;

      اگر (parms == NULL_درخت)
	parms = error_mark_گرہ;

      اگر (ccode == مطابقت)
	{
	  اگر (has_مطابقت)
	    error_at (مطابقت_loc, "too many %<match%> clauses");
	  has_مطابقت = سچ;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  اگر (ctx == error_mark_گرہ)
	    جاؤ fail;
	  ctx = omp_check_context_selector (مطابقت_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  اگر (ctx != error_mark_گرہ
	      && !vec_محفوظ_is_خالی_خانے (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->آخری ();
	      درخت outer_ctx = a.selector;
	      ctx = omp_ملاؤ_context_selectors (مطابقت_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      ورنہ اگر (ccode == adjust_دلائل)
	{
	  has_adjust_دلائل = سچ;
	  اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      ثابت حرف *p
		= IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
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
		  اگر (variant != error_mark_گرہ)
		    برائے (درخت c = list; c != NULL_درخت; c = درخت_CHAIN (c))
		      {
			درخت decl = درخت_PURPOSE (c);
			location_t arg_loc = اظہاریہ_LOCATION (درخت_قدر (c));
			صحیح idx;
			برائے (arg = parms, idx = 0; arg != تہی;
			     arg = درخت_CHAIN (arg), idx++)
			  اگر (arg == decl)
			    توڑو;
			اگر (arg == NULL_درخت)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    جاؤ fail;
			  }
			اگر (adjust_دلائل_list.شامل_ہے (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    جاؤ fail;
			  }
			اگر (strcmp (p, "need_device_ptr") == 0
			    && درخت_رمز (درخت_TYPE (arg)) != اشارہ_گر_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    جاؤ fail;
			  }
			adjust_دلائل_list.محفوظ_ڈالو (arg);
			اگر (strcmp (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_درخت_list (
				NULL_درخت,
				build_int_cst (
				  integer_type_گرہ,
				  idx))); // Store 0-based argument index,
					  // as in gimplify_call_expr
			  }
		      }
		}
	      ورنہ
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %<nothing%> or %<need_device_ptr%>");
		  اگر (strcmp (p, "need_device_addr") == 0)
		    inform (c_parser_peek_token (parser)->location,
			    "%<need_device_addr%> is not valid for C");
		  جاؤ fail;
		}
	    }
	  ورنہ
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected %<nothing%> or %<need_device_ptr%> "
			"followed by %<:%>");
	      جاؤ fail;
	    }
	}
      ورنہ اگر (ccode == append_دلائل)
	{
	  اگر (append_دلائل_درخت)
	    {
	      error_at (append_دلائل_loc, "too many %qs clauses", "append_args");
	      append_دلائل_درخت = NULL_درخت;
	    }
	  کرو
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      اگر (!c_parser_اگلا_token_is (parser, CPP_NAME)
		  || strcmp ("interop",
			     IDENTIFIER_اشارہ_گر (
			       c_parser_peek_token (parser)->قدر)))
		{
		  error_at (loc, "expected %<interop%>");
		  جاؤ fail;
		}
	      c_parser_consume_token (parser);

	      اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		جاؤ fail;
	      منطقی ہدف = جھوٹ;
	      منطقی targetsync = جھوٹ;
	      درخت prefer_type_درخت = NULL_درخت;
	      اگر (!c_parser_omp_clause_init_modifiers (parser, &ہدف,
						       &targetsync,
						       &prefer_type_درخت)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		جاؤ fail;
	      اگر (!ہدف && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      درخت t = build_درخت_list (ہدف ? boolean_true_گرہ
					       : boolean_false_گرہ,
					targetsync ? boolean_true_گرہ
						   : boolean_false_گرہ);
	      t = build1_loc (loc, NOP_اظہاریہ, void_type_گرہ, t);
	      t = build_درخت_list (t, prefer_type_درخت);
	      اگر (append_دلائل_درخت)
		{
		  درخت_CHAIN (append_دلائل_آخری) = t;
		  append_دلائل_آخری = t;
		}
	      ورنہ
		append_دلائل_درخت = append_دلائل_آخری = t;
	      اگر (c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
		توڑو;
	      اگر (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		جاؤ fail;
	    }
	  جب (سچ);
	}

      parens.require_close (parser);
  } جب (c_parser_اگلا_token_is_not (parser, CPP_PRAGMA_EOL));
  اگر (variant != error_mark_گرہ && !has_مطابقت)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_گرہ;
    }
  c_parser_skip_مقصد_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  اگر (variant == error_mark_گرہ || ctx == error_mark_گرہ)
    /* Previously diagnosed error.  */
    واپس;

  اگر ((has_adjust_دلائل || append_دلائل_درخت)
      && !omp_get_context_selector (ctx, OMP_TRAIT_سیٹ_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_دلائل ? adjust_دلائل_loc : append_دلائل_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_دلائل ? "adjust_args" : "append_args");
      واپس;
    }

  اگر (!omp_get_context_selector (ctx, OMP_TRAIT_سیٹ_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      درخت بنیاد_type = درخت_TYPE (fndecl);
      درخت variant_type = درخت_TYPE (variant);
      منطقی unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_درخت
	   && !TYPE_NO_NAMED_دلائل_STDARG_P (variant_type));

      اگر (append_دلائل_درخت
	  && TYPE_ARG_TYPES (بنیاد_type) == NULL_درخت
	  && !TYPE_NO_NAMED_دلائل_STDARG_P (بنیاد_type))
	{
	  /* The base function is a pre-C23 unprototyped function.  Without
	     a prototype, we don't know the offset where the append_args go.
	     That offset needs to be stored with the append_args in the
	     variant function attributes, so we cannot presently handle
	     this case.  */
	  sorry_at (append_دلائل_loc,
		    "%<append_args%> with unprototyped base function "
		    "is not supported yet");
	  inform (DECL_ماخذ_LOCATION (fndecl),
		  "base function %qD declared here", fndecl);
	  واپس;
	}
      ورنہ اگر (append_دلائل_درخت)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  صحیح nappend_دلائل = 0;
	  صحیح nbase_دلائل = 0;
	  برائے (درخت t = TYPE_ARG_TYPES (بنیاد_type);
	       t && درخت_قدر (t) != void_type_گرہ; t = درخت_CHAIN (t))
	    nbase_دلائل++;
	  برائے (درخت t = append_دلائل_درخت; t; t = درخت_CHAIN (t))
	    nappend_دلائل++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_دلائل_درخت = build_درخت_list (build_int_cst (integer_type_گرہ,
							     nbase_دلائل),
					      append_دلائل_درخت);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  اگر (!unprototyped_variant)
	    {
	      درخت دلائل = TYPE_ARG_TYPES (variant_type);
	      برائے (صحیح i = 0; دلائل && i < nbase_دلائل;
		   i++, دلائل = درخت_CHAIN (دلائل))
		;
	      برائے (صحیح i = 0; i < nappend_دلائل; i++, دلائل = درخت_CHAIN (دلائل))
		اگر (!دلائل || !c_omp_interop_t_p (درخت_قدر (دلائل)))
		  {
		    error_at (DECL_ماخذ_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_دلائل + i + 1, variant);
		    inform (append_دلائل_loc,
			    "%<append_args%> specified here");
		    واپس;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  درخت دلائل = TYPE_ARG_TYPES (بنیاد_type);
	  درخت newargs = NULL_درخت;
	  درخت lastarg = NULL_درخت;
	  برائے (صحیح j = 0; j < nbase_دلائل; j++, دلائل = درخت_CHAIN (دلائل))
	    {
	      درخت t = درخت_cons (درخت_PURPOSE (دلائل),
				  درخت_قدر (دلائل), NULL_درخت);
	      اگر (lastarg)
		درخت_CHAIN (lastarg) = t;
	      ورنہ
		newargs = t;
	      lastarg = t;
	    }
	  درخت type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? درخت_TYPE (type) : اشارہ_گر_sized_int_گرہ;
	  برائے (صحیح j = 0; j < nappend_دلائل; j++)
	    {
	      درخت t = درخت_cons (NULL_درخت, type, NULL_درخت);
	      اگر (lastarg)
		درخت_CHAIN (lastarg) = t;
	      ورنہ
		newargs = t;
	      lastarg = t;
	    }
	  درخت_CHAIN (lastarg) = دلائل;

	  /* Temporarily stuff newargs into the original base_type.  */
	  درخت saveargs = TYPE_ARG_TYPES (بنیاد_type);
	  TYPE_ARG_TYPES (بنیاد_type) = newargs;
	  منطقی fail = !comptypes (بنیاد_type, variant_type);
	  TYPE_ARG_TYPES (بنیاد_type) = saveargs;

	  اگر (fail)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_ماخذ_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      واپس;
	    }
	  ورنہ اگر (unprototyped_variant)
	    /* If we've got an unprototyped variant, copy the transformed
	       base arg types to the variant.  This is needed later by
	       modify_call_for_omp_dispatch.  */
	    TYPE_ARG_TYPES (variant_type) = newargs;
	}
      ورنہ  /* No append_args present.  */
	{
	  اگر (!comptypes (بنیاد_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_ماخذ_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      واپس;
	    }
	  ورنہ اگر (TYPE_ARG_TYPES (variant_type) == NULL_درخت
		   && !TYPE_NO_NAMED_دلائل_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (بنیاد_type) != NULL_درخت)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (بنیاد_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_مستعمل (variant) = 1;
  درخت construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_سیٹ_CONSTRUCT);
  omp_mark_declare_variant (مطابقت_loc, variant, construct);
  اگر (omp_context_selector_matches (ctx, NULL_درخت, جھوٹ))
    {
      درخت attr = درخت_cons (get_identifier ("omp declare variant base"),
			     build_درخت_list (variant, ctx),
			     DECL_اوصاف (fndecl));
      DECL_اوصاف (fndecl) = attr;
    }

  اگر (need_device_ptr_list || append_دلائل_درخت)
    {
      درخت variant_decl = درخت_strip_nop_conversions (variant);
      درخت t = build_درخت_list (need_device_ptr_list,
				NULL_درخت /* need_device_addr */);
      درخت_CHAIN (t) = append_دلائل_درخت;
      DECL_اوصاف (variant_decl)
	= درخت_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_اوصاف (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

ساکن خالی
c_اختتام_omp_declare_simd (c_parser *parser, درخت fndecl, درخت parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  اگر (clauses.exists () && clauses[0].type == CPP_EOF)
    واپس;
  ثابت حرف *قسم = "simd";
  اگر (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    قسم = IDENTIFIER_اشارہ_گر (clauses[0].قدر);
  gcc_assert (strcmp (قسم, "simd") == 0 || strcmp (قسم, "variant") == 0);
  اگر (fndecl == NULL_درخت || درخت_رمز (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", قسم);
      clauses[0].type = CPP_EOF;
      واپس;
    }
  اگر (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_ماخذ_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", قسم);
      clauses[0].type = CPP_EOF;
      واپس;
    }
  اگر (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_ماخذ_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", قسم);
      واپس;
    }

  اگر (parms == NULL_درخت)
    parms = DECL_ARGUMENTS (fndecl);

  غیرعلامتی صحیح علامات_avail = parser->علامات_avail;
  gcc_assert (parser->علامات == &parser->علامات_buf[0]);

  parser->علامات = clauses.پتہ ();
  parser->علامات_avail = clauses.لمبائی ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  جب (parser->علامات_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      قسم = IDENTIFIER_اشارہ_گر (token->قدر);
      c_parser_consume_token (parser);
      parser->اندر_pragma = سچ;

      اگر (strcmp (قسم, "simd") == 0)
	{
	  درخت c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_نقاب,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_مقصد_numbers (parms, c);
	  اگر (c != NULL_درخت)
	    c = درخت_cons (NULL_درخت, c, NULL_درخت);
	  c = build_درخت_list (get_identifier ("omp declare simd"), c);
	  درخت_CHAIN (c) = DECL_اوصاف (fndecl);
	  DECL_اوصاف (fndecl) = c;
	}
      ورنہ
	{
	  gcc_assert (strcmp (قسم, "variant") == 0);
	  c_اختتام_omp_declare_variant (parser, fndecl, parms);
	}
    }

  parser->علامات = &parser->علامات_buf[0];
  parser->علامات_avail = علامات_avail;
  اگر (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#اگر !defined (NO_DOT_اندر_LABEL)
#تعریف_کرو JOIN_STR "."
#وگرنہ_اگر !defined (NO_DOLLAR_اندر_LABEL)
#تعریف_کرو JOIN_STR "$"
#ورنہ
#تعریف_کرو JOIN_STR "_"
#اگر_ختم

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
ساکن درخت
omp_آغاز_variant_function (c_declarator *declarator, درخت ctx)
{
  c_declarator *id = declarator;
  جب (id->قسم != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  درخت name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  واپس name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
ساکن خالی
omp_اختتام_variant_function (درخت decl, درخت بنیاد_name, درخت ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  درخت بنیاد_decl = lookup_name (بنیاد_name);
  اگر (بنیاد_decl == error_mark_گرہ)
    بنیاد_decl = NULL_درخت;
  اگر (!بنیاد_decl)
    {
      error_at (DECL_ماخذ_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_اشارہ_گر (بنیاد_name));
      واپس;
    }

  اگر (!comptypes (درخت_TYPE (decl), درخت_TYPE (بنیاد_decl)))
    {
      error_at (DECL_ماخذ_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", بنیاد_decl);
      inform (DECL_ماخذ_LOCATION (بنیاد_decl),
	      "%qE declared here", بنیاد_decl);
      واپس;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_ماخذ_LOCATION (decl),
				   بنیاد_decl, ctx);
  درخت construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_سیٹ_CONSTRUCT);
  omp_mark_declare_variant (DECL_ماخذ_LOCATION (decl), decl, construct);
  درخت attrs = DECL_اوصاف (بنیاد_decl);
  درخت مطابقت_loc_گرہ
    = maybe_wrap_with_location (integer_zero_گرہ,
				DECL_ماخذ_LOCATION (بنیاد_decl));
  درخت loc_گرہ = درخت_cons (مطابقت_loc_گرہ, integer_zero_گرہ,
			     build_درخت_list (مطابقت_loc_گرہ,
					      integer_zero_گرہ));
  attrs = درخت_cons (get_identifier ("omp declare variant base"),
		     درخت_cons (decl, ctx, loc_گرہ), attrs);
  DECL_اوصاف (بنیاد_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  درخت_عوامی (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

منطقی
c_maybe_parse_omp_decl (درخت decl, درخت d)
{
  gcc_assert (درخت_رمز (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_علامات (d);
  c_token *پہلا = toks->پتہ ();
  c_token *آخری = پہلا + toks->لمبائی ();
  ثابت حرف *directive[3] = {};
  برائے (صحیح j = 0; j < 3; j++)
    {
      درخت id = NULL_درخت;
      اگر (پہلا + j == آخری)
	توڑو;
      اگر (پہلا[j].type == CPP_NAME)
	id = پہلا[j].قدر;
      ورنہ اگر (پہلا[j].type == CPP_KEYWORD)
	id = ridpointers[(صحیح) پہلا[j].keyword];
      ورنہ
	توڑو;
      directive[j] = IDENTIFIER_اشارہ_گر (id);
    }
  ثابت c_omp_directive *dir = تہی;
  اگر (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  اگر (dir == تہی)
    {
      error_at (پہلا->location,
		"unknown OpenMP directive name in "
		"%qs attribute argument", "omp::decl");
      واپس جھوٹ;
    }
  اگر (dir->id != PRAGMA_OMP_THREADPRIVATE
      && dir->id != PRAGMA_OMP_GROUPPRIVATE
      && dir->id != PRAGMA_OMP_ALLOCATE
      && (dir->id != PRAGMA_OMP_DECLARE
	  || strcmp (directive[1], "target") != 0))
    واپس جھوٹ;

  اگر (!flag_openmp && !dir->simd)
    واپس سچ;

  c_parser *parser = the_parser;
  غیرعلامتی صحیح علامات_avail = parser->علامات_avail;
  gcc_assert (parser->علامات == &parser->علامات_buf[0]);
  toks = تہی;
  vec_محفوظ_reserve (toks, آخری - پہلا + 2, سچ);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_قسم = pragma_قسم (dir->id);
  tok.location = پہلا->location;
  toks->تیز_ڈالو (tok);
  جب (++پہلا < آخری)
    toks->تیز_ڈالو (*پہلا);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = آخری[-1].location;
  toks->تیز_ڈالو (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = آخری[-1].location;
  toks->تیز_ڈالو (tok);
  parser->اندر_omp_decl_attribute = decl;
  gcc_assert (!parser->اندر_omp_attribute_pragma);
  parser->اندر_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->اندر_omp_attribute_pragma->token_vec = toks;
  parser->اندر_omp_attribute_pragma->save_علامات = parser->علامات;
  parser->اندر_omp_attribute_pragma->save_علامات_avail = علامات_avail;
  parser->علامات = toks->پتہ ();
  parser->علامات_avail = toks->لمبائی ();
  c_parser_pragma (parser, pragma_external, تہی, NULL_درخت);
  parser->اندر_omp_decl_attribute = NULL_درخت;
  واپس سچ;
}

/* OpenMP 4.0:
   # pragma omp declare target new-line
   declarations and definitions
   # pragma omp end declare target new-line

   OpenMP 4.5:
   # pragma omp declare target ( extended-list ) new-line

   # pragma omp declare target declare-target-clauses[seq] new-line  */

#تعریف_کرو OMP_DECLARE_ہدف_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_مقصد)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ENTER)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LINK)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LOCAL)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_بالواسطہ))

ساکن خالی
c_parser_omp_declare_ہدف (c_parser *parser)
{
  درخت clauses = NULL_درخت;
  صحیح device_type = 0;
  منطقی بالواسطہ = جھوٹ;
  منطقی only_device_type_or_بالواسطہ = سچ;
  اگر (flag_openmp)
    omp_requires_نقاب
      = (شمار omp_requires) (omp_requires_نقاب | OMP_REQUIRES_ہدف_مستعمل);
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
      || (c_parser_اگلا_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_ہدف_CLAUSE_نقاب,
					"#pragma omp declare target");
  ورنہ اگر (parser->اندر_omp_decl_attribute
	   || c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
    {
      clauses = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					      clauses);
      clauses = c_اختتام_omp_clauses (clauses, C_ORT_OMP);
      c_parser_skip_مقصد_pragma_eol (parser);
    }
  ورنہ
    {
      warning_at (c_parser_peek_token (parser)->location,
		  OPT_Wdeprecated_openmp,
		  "use of %<omp declare target%> as a synonym for "
		  "%<omp begin declare target%> has been deprecated since "
		  "OpenMP 5.2");
      منطقی attr_syntax = parser->اندر_omp_attribute_pragma != تہی;
      c_parser_skip_مقصد_pragma_eol (parser);
      c_omp_declare_ہدف_attr attr = { attr_syntax, -1, 0 };
      vec_محفوظ_ڈالو (current_omp_declare_ہدف_attribute, attr);
      واپس;
    }
  برائے (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_قسم (c);
      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_بالواسطہ)
	بالواسطہ |= !integer_zerop (OMP_CLAUSE_بالواسطہ_اظہاریہ (c));
    }
  برائے (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_بالواسطہ)
	جاری;
      درخت t = OMP_CLAUSE_DECL (c), id;
      درخت at1 = lookup_attribute ("omp declare target", DECL_اوصاف (t));
      درخت at2 = lookup_attribute ("omp declare target link",
				   DECL_اوصاف (t));
      only_device_type_or_بالواسطہ = جھوٹ;
      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::تبادلہ (at1, at2);
	}
      ورنہ
	id = get_identifier ("omp declare target");
      اگر (at2)
	{
	  اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_مقصد (c) ? "to" : "enter");
	  ورنہ اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_LOCAL
		   || قدر_member (get_identifier ("local"), درخت_قدر (at2)))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<local%> clauses", t);
	  ورنہ
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<to%> or %<enter%> clauses", t);
	  جاری;
	}
      اگر (!at1)
	{
	  DECL_اوصاف (t) = درخت_cons (id, NULL_درخت, DECL_اوصاف (t));
	  اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_LOCAL)
	    درخت_قدر (DECL_اوصاف (t))
	      = درخت_cons (NULL_درخت, get_identifier ("local"),
			   درخت_قدر (DECL_اوصاف (t)));

	  اگر (درخت_رمز (t) != FUNCTION_DECL && !is_global_var (t))
	    جاری;

	  symtab_گرہ *گرہ = symtab_گرہ::get (t);
	  اگر (گرہ != تہی)
	    {
	      گرہ->offloadable = 1;
	      اگر (ENABLE_OFFLOADING)
		{
		  g->have_offload = سچ;
		  اگر (is_a <varpool_گرہ *> (گرہ)
		      && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_LOCAL)
		    vec_محفوظ_ڈالو (offload_vars, t);
		}
	    }
	}
      ورنہ
	{
	  منطقی saw_local = قدر_member (get_identifier ("local"),
					 درخت_قدر (at1));
	  اگر (saw_local && OMP_CLAUSE_رمز (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_مقصد (c) ? "to" : "enter");
	      جاری;
	    }
	  ورنہ اگر (!saw_local && OMP_CLAUSE_رمز (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      جاری;
	    }
	}
      اگر (درخت_رمز (t) != FUNCTION_DECL)
	جاری;
      اگر ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  درخت at3 = lookup_attribute ("omp declare target host",
				       DECL_اوصاف (t));
	  اگر (at3 == NULL_درخت)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_اوصاف (t)
		= درخت_cons (id, NULL_درخت, DECL_اوصاف (t));
	    }
	}
      اگر ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  درخت at3 = lookup_attribute ("omp declare target nohost",
				       DECL_اوصاف (t));
	  اگر (at3 == NULL_درخت)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_اوصاف (t)
		= درخت_cons (id, NULL_درخت, DECL_اوصاف (t));
	    }
	}
      اگر (بالواسطہ)
	{
	  درخت at4 = lookup_attribute ("omp declare target indirect",
				       DECL_اوصاف (t));
	  اگر (at4 == NULL_درخت)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_اوصاف (t)
		= درخت_cons (id, NULL_درخت, DECL_اوصاف (t));
	    }
	}
    }
  اگر ((device_type || بالواسطہ) && only_device_type_or_بالواسطہ)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  اگر (بالواسطہ && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "%<device_type%> clause must specify 'any' when used with "
	      "an %<indirect%> clause");
}

/* OpenMP 5.1
   #pragma omp begin assumes clauses[optseq] new-line

   #pragma omp begin declare target clauses[optseq] new-line

   #pragma omp begin declare variant match (context-selector) new-line  */

#تعریف_کرو OMP_BEGIN_DECLARE_ہدف_CLAUSE_نقاب			\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_بالواسطہ))

ساکن خالی
c_parser_omp_begin (c_parser *parser)
{
  ثابت حرف *p = "";
  c_parser_consume_pragma (parser);
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
  اگر (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  منطقی attr_syntax = parser->اندر_omp_attribute_pragma != تہی;
	  درخت clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_ہدف_CLAUSE_نقاب,
					"#pragma omp begin declare target");
	  صحیح device_type = 0;
	  صحیح بالواسطہ = 0;
	  برائے (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_قسم (c);
	      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_بالواسطہ)
		بالواسطہ |= !integer_zerop (OMP_CLAUSE_بالواسطہ_اظہاریہ (c));
	    }
	  c_omp_declare_ہدف_attr attr = { attr_syntax, device_type,
					     بالواسطہ };
	  vec_محفوظ_ڈالو (current_omp_declare_ہدف_attribute, attr);
	}
      ورنہ اگر (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  ثابت حرف *clause = "";
	  matching_parens parens;
	  location_t مطابقت_loc = c_parser_peek_token (parser)->location;
	  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	    {
	      درخت id = c_parser_peek_token (parser)->قدر;
	      clause = IDENTIFIER_اشارہ_گر (id);
	    }
	  اگر (strcmp (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_مقصد_pragma_eol (parser);
	      واپس;
	    }

	  c_parser_consume_token (parser);

	  اگر (!parens.require_open (parser))
	    {
	      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	      واپس;
	    }

	  درخت ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_درخت);
	  اگر (ctx != error_mark_گرہ)
	    ctx = omp_check_context_selector (مطابقت_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  اگر (ctx != error_mark_گرہ
	      && !vec_محفوظ_is_خالی_خانے (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->آخری ();
	      درخت outer_ctx = a.selector;
	      ctx = omp_ملاؤ_context_selectors (مطابقت_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  اگر (ctx == error_mark_گرہ
	      || !omp_context_selector_matches (ctx, NULL_درخت, جھوٹ, سچ))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	      c_parser_skip_مقصد_pragma_omp_انتہا_declare_variant (parser);
	      واپس;
	    }
	  ورنہ
	    {
	      منطقی attr_syntax = parser->اندر_omp_attribute_pragma != تہی;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_محفوظ_ڈالو (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_مقصد_pragma_eol (parser);
	}
      ورنہ
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	}
    }
  ورنہ اگر (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      منطقی attr_syntax = parser->اندر_omp_attribute_pragma != تہی;
      c_parser_omp_assumption_clauses (parser, جھوٹ);
      ساخت c_omp_begin_assumes_ڈیٹا a = { attr_syntax };
      vec_محفوظ_ڈالو (current_omp_begin_assumes, a);
    }
  ورنہ
    {
      c_parser_error (parser, "expected %<declare target%>, "
		      "%<declare variant%>, or %<assumes%>");
      c_parser_skip_مقصد_pragma_eol (parser);
    }
}

/* OpenMP 4.0
   #pragma omp end declare target

   OpenMP 5.1
   #pragma omp end assumes
   #pragma omp end declare variant  */

ساکن خالی
c_parser_omp_انتہا (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ثابت حرف *p = "";
  c_parser_consume_pragma (parser);
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
  اگر (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  منطقی attr_syntax = parser->اندر_omp_attribute_pragma != تہی;
	  c_parser_skip_مقصد_pragma_eol (parser);
	  اگر (!vec_محفوظ_لمبائی (current_omp_declare_ہدف_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  ورنہ
	    {
	      c_omp_declare_ہدف_attr
		a = current_omp_declare_ہدف_attribute->نکالو ();
	      اگر (a.attr_syntax != attr_syntax)
		{
		  اگر (a.attr_syntax)
		    error_at (loc,
			      "%qs in attribute syntax terminated "
			      "with %qs in pragma syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		  ورنہ
		    error_at (loc,
			      "%qs in pragma syntax terminated "
			      "with %qs in attribute syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		}
	    }
	}
      ورنہ اگر (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  منطقی attr_syntax = parser->اندر_omp_attribute_pragma != تہی;
	  c_parser_skip_مقصد_pragma_eol (parser);
	  اگر (!vec_محفوظ_لمبائی (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  ورنہ
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->نکالو ();
	      اگر (a.attr_syntax != attr_syntax)
		{
		  اگر (a.attr_syntax)
		    error_at (loc,
			      "%<begin declare variant%> in attribute syntax "
			      "terminated with "
			      "%<end declare variant%> in pragma syntax");
		  ورنہ
		    error_at (loc,
			      "%<begin declare variant%> in pragma syntax "
			      "terminated with "
			      "%<end declare variant%> in attribute syntax");
		}
	    }
	}
      ورنہ
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_مقصد_pragma_eol (parser);
	  واپس;
	}
    }
  ورنہ اگر (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      منطقی attr_syntax = parser->اندر_omp_attribute_pragma != تہی;
      c_parser_skip_مقصد_pragma_eol (parser);
      اگر (!vec_محفوظ_لمبائی (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      ورنہ
	{
	  c_omp_begin_assumes_ڈیٹا
	    a = current_omp_begin_assumes->نکالو ();
	  اگر (a.attr_syntax != attr_syntax)
	    {
	      اگر (a.attr_syntax)
		error_at (loc,
			  "%qs in attribute syntax terminated "
			  "with %qs in pragma syntax",
			  "begin assumes", "end assumes");
	      ورنہ
		error_at (loc,
			  "%qs in pragma syntax terminated "
			  "with %qs in attribute syntax",
			  "begin assumes", "end assumes");
	    }
	}
    }
  ورنہ
    {
      c_parser_error (parser, "expected %<declare%> or %<assumes%>");
      c_parser_skip_مقصد_pragma_eol (parser);
    }
}

/* OpenMP 5.0
   #pragma omp declare mapper ([mapper-identifier :] type var) \
			      [clause [ [,] clause ] ... ] new-line  */

ساکن خالی
c_parser_omp_declare_mapper (c_parser *parser, شمار pragma_context context)
{
  درخت type, mapper_name = NULL_درخت, var = NULL_درخت, stmt, stmtlist;
  درخت maplist = NULL_درخت, mapper_id, mapper_decl, t;
  c_token *token;

  اگر (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare mapper%> not at file or block scope");
      جاؤ fail;
    }

  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    جاؤ fail;

  token = c_parser_peek_token (parser);

  اگر (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      انتخاب (token->type)
	{
	حالت CPP_NAME:
	  mapper_name = token->قدر;
	  c_parser_consume_token (parser);
	  توڑو;
	حالت CPP_KEYWORD:
	  اگر (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_درخت;
	      c_parser_consume_token (parser);
	      توڑو;
	    }
	  /* Fallthrough.  */
	طےشدہ:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	  واپس;
	}

      اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	جاؤ fail;
    }

  mapper_id = c_omp_mapper_id (mapper_name);
  mapper_decl = c_omp_mapper_decl (mapper_id);

  {
    location_t loc = c_parser_peek_token (parser)->location;
    ساخت c_type_name *ctype = c_parser_type_name (parser);
    type = groktypename (ctype, تہی, تہی);
    اگر (type == error_mark_گرہ)
      جاؤ fail;
    اگر (!ریکارڈ_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	واپس;
      }
    برائے (درخت t = DECL_INITIAL (mapper_decl); t; t = درخت_CHAIN (t))
      اگر (comptypes (درخت_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_اشارہ_گر (mapper_id)
		      + حجم ("omp declare mapper ") - 1,
		    type);
	  درخت prevmapper = درخت_قدر (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_ماخذ_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	  واپس;
	}
  }

  token = c_parser_peek_token (parser);
  اگر (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->قدر, type);
      c_parser_consume_token (parser);
      DECL_ARTIFICIAL (var) = 1;
    }
  ورنہ
    {
      error_at (token->location, "expected identifier");
      جاؤ fail;
    }

  اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    جاؤ fail;

  ڈالو_scope ();
  stmtlist = ڈالو_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  جب (c_parser_اگلا_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t یہاں;
      pragma_omp_clause c_قسم;
      یہاں = c_parser_peek_token (parser)->location;
      c_قسم = c_parser_omp_clause_name (parser);
      اگر (c_قسم != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (یہاں, "unexpected clause");
	  جاؤ fail;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, سچ);
    }

  اگر (maplist == NULL_درخت)
    {
      error_at (داخلہ_location, "missing %<map%> clause");
      جاؤ fail;
    }
  درخت list;
  برائے (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      درخت dvar = OMP_CLAUSE_DECL (list);
      جب (!DECL_P (dvar) && درخت_عملیہ_لمبائی (dvar))
	dvar = درخت_عملیہ (dvar, 0);
      اگر (dvar == var)
	توڑو;
    }
  اگر (!list)
    error_at (داخلہ_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_گرہ (OMP_DECLARE_MAPPER);
  درخت_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  جوڑو_stmt (stmt);

  نکالو_stmt_list (stmtlist);
  نکالو_scope ();

  c_parser_skip_مقصد_pragma_eol (parser);

  t = درخت_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  واپس;

 fail:
  c_parser_skip_مقصد_pragma_eol (parser);
}

/* OpenMP 4.0
   #pragma omp declare reduction (reduction-id : typename-list : expression) \
      initializer-clause[opt] new-line

   initializer-clause:
      initializer (omp_priv = initializer)
      initializer (function-name (argument-list))  */

ساکن خالی
c_parser_omp_declare_reduction (c_parser *parser, شمار pragma_context context)
{
  غیرعلامتی صحیح علامات_avail = 0, i;
  c_token *saved_علامات = تہی;
  vec<درخت> types = vNULL;
  vec<c_token> clauses = vNULL;
  شمار درخت_رمز_2 reduc_رمز = ERROR_MARK;
  درخت reduc_id = NULL_درخت;
  درخت type;
  location_t rloc = c_parser_peek_token (parser)->location;

  اگر (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare reduction%> not at file or block scope");
      جاؤ fail;
    }

  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    جاؤ fail;

  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_PLUS:
      reduc_رمز = PLUS_اظہاریہ;
      توڑو;
    حالت CPP_MULT:
      reduc_رمز = MULT_اظہاریہ;
      توڑو;
    حالت CPP_MINUS:
      reduc_رمز = MINUS_اظہاریہ;
      توڑو;
    حالت CPP_AND:
      reduc_رمز = ثنائی_ہندسہ_AND_اظہاریہ;
      توڑو;
    حالت CPP_XOR:
      reduc_رمز = ثنائی_ہندسہ_XOR_اظہاریہ;
      توڑو;
    حالت CPP_OR:
      reduc_رمز = ثنائی_ہندسہ_IOR_اظہاریہ;
      توڑو;
    حالت CPP_AND_AND:
      reduc_رمز = TRUTH_ANDIF_اظہاریہ;
      توڑو;
    حالت CPP_OR_OR:
      reduc_رمز = TRUTH_ORIF_اظہاریہ;
      توڑو;
    حالت CPP_NAME:
      ثابت حرف *p;
      p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp (p, "min") == 0)
	{
	  reduc_رمز = MIN_اظہاریہ;
	  توڑو;
	}
      اگر (strcmp (p, "max") == 0)
	{
	  reduc_رمز = MAX_اظہاریہ;
	  توڑو;
	}
      reduc_id = c_parser_peek_token (parser)->قدر;
      توڑو;
    طےشدہ:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      جاؤ fail;
    }

  درخت orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_رمز, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    جاؤ fail;

  جب (سچ)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      ساخت c_type_name *ctype = c_parser_type_name (parser);
      اگر (ctype != تہی)
	{
	  type = groktypename (ctype, تہی, تہی);
	  اگر (type == error_mark_گرہ)
	    ;
	  ورنہ اگر ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || درخت_رمز (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_درخت)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  ورنہ اگر (درخت_رمز (type) == FUNCTION_TYPE
		   || درخت_رمز (type) == ARRAY_TYPE)
	    error_at (loc, "function or array type in "
		      "%<#pragma omp declare reduction%>");
	  ورنہ اگر (TYPE_ATOMIC (type))
	    error_at (loc, "%<_Atomic%> qualified type in "
			   "%<#pragma omp declare reduction%>");
	  ورنہ اگر (TYPE_QUALS_NO_ADDR_SPACE (type))
	    error_at (loc, "const, volatile or restrict qualified type in "
			   "%<#pragma omp declare reduction%>");
	  ورنہ
	    {
	      درخت t;
	      برائے (t = DECL_INITIAL (reduc_decl); t; t = درخت_CHAIN (t))
		اگر (comptypes (درخت_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_اشارہ_گر (reduc_id)
				   + حجم ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_ماخذ_LOCATION (درخت_VEC_ELT (درخت_قدر (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    توڑو;
		  }
	      اگر (t == NULL_درخت)
		types.محفوظ_ڈالو (type);
	    }
	  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ورنہ
	    توڑو;
	}
      ورنہ
	توڑو;
    }

  اگر (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_خالی_خانے ())
    {
     fail:
      clauses.release ();
      types.release ();
      جب (سچ)
	{
	  c_token *token = c_parser_peek_token (parser);
	  اگر (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    توڑو;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_مقصد_pragma_eol (parser);
      واپس;
    }

  اگر (types.لمبائی () > 1)
    {
      جب (c_parser_اگلا_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  اگر (token->type == CPP_EOF)
	    جاؤ fail;
	  clauses.محفوظ_ڈالو (*token);
	  c_parser_consume_token (parser);
	}
      clauses.محفوظ_ڈالو (*c_parser_peek_token (parser));
      c_parser_skip_مقصد_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, حجم (eof_token));
      eof_token.type = CPP_EOF;
      clauses.محفوظ_ڈالو (eof_token);
      clauses.محفوظ_ڈالو (eof_token);
    }

  صحیح errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_علامات = parser->علامات;
      علامات_avail = parser->علامات_avail;
      اگر (!clauses.is_خالی_خانے ())
	{
	  parser->علامات = clauses.پتہ ();
	  parser->علامات_avail = clauses.لمبائی ();
	  parser->اندر_pragma = سچ;
	}

      منطقی nested = current_function_decl != NULL_درخت;
      اگر (nested)
	c_ڈالو_function_context ();
      درخت fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, سچ);
      ڈالو_scope ();
      درخت stmt = ڈالو_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      درخت omp_برآمد = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_برآمد) = 1;
      DECL_CONTEXT (omp_برآمد) = fndecl;
      pushdecl (omp_برآمد);
      درخت omp_اندر = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_اندر) = 1;
      DECL_CONTEXT (omp_اندر) = fndecl;
      pushdecl (omp_اندر);
      ساخت c_اظہاریہ combiner = c_parser_عبارت (parser);
      ساخت c_اظہاریہ initializer;
      درخت omp_priv = NULL_درخت, omp_orig = NULL_درخت;
      منطقی bad = جھوٹ;
      initializer.سیٹ_error ();
      اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	bad = سچ;
      ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      اگر (!bad
	  && (c_parser_اگلا_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_اشارہ_گر
				(c_parser_peek_token (parser)->قدر),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  نکالو_scope ();
	  ڈالو_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_گرہ;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    bad = سچ;
	  ورنہ اگر (!c_parser_اگلا_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      bad = سچ;
	    }
	  ورنہ اگر (strcmp (IDENTIFIER_اشارہ_گر
				(c_parser_peek_token (parser)->قدر),
			   "omp_priv") != 0)
	    {
	      اگر (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_قسم != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  bad = سچ;
		}
	      ورنہ
		initializer = c_parser_postfix_عبارت (parser);
	      اگر (initializer.قدر
		  && درخت_رمز (initializer.قدر) == CALL_اظہاریہ)
		{
		  صحیح j;
		  درخت c = initializer.قدر;
		  برائے (j = 0; j < call_اظہاریہ_nargs (c); j++)
		    {
		      درخت a = CALL_اظہاریہ_ARG (c, j);
		      STRIP_NOPS (a);
		      اگر (درخت_رمز (a) == ADDR_اظہاریہ
			  && درخت_عملیہ (a, 0) == omp_priv)
			توڑو;
		    }
		  اگر (j == call_اظہاریہ_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  ورنہ
	    {
	      c_parser_consume_token (parser);
	      اگر (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		bad = سچ;
	      ورنہ
		{
		  درخت st = ڈالو_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (سطر_جدول, loc);
		  آغاز_init (omp_priv, NULL_درخت, جھوٹ, جھوٹ, &richloc);
		  ساخت c_اظہاریہ init = c_parser_initializer (parser, omp_priv);
		  اختتام_init ();
		  اختتام_decl (omp_priv, loc, init.قدر,
		      	       init.original_type, NULL_درخت);
		  نکالو_stmt_list (st);
		}
	    }
	  اگر (!bad
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    bad = سچ;
	}

      اگر (!bad)
	{
	  c_parser_skip_مقصد_pragma_eol (parser);

	  درخت t = درخت_cons (type, make_درخت_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_ماخذ_LOCATION (omp_برآمد) = rloc;
	  درخت_VEC_ELT (درخت_قدر (t), 0) = omp_برآمد;
	  درخت_VEC_ELT (درخت_قدر (t), 1) = omp_اندر;
	  درخت_VEC_ELT (درخت_قدر (t), 2) = combiner.قدر;
	  walk_درخت (&combiner.قدر, c_check_omp_declare_reduction_r,
		     &درخت_VEC_ELT (درخت_قدر (t), 0), تہی);
	  اگر (omp_priv)
	    {
	      DECL_ماخذ_LOCATION (omp_priv) = rloc;
	      درخت_VEC_ELT (درخت_قدر (t), 3) = omp_priv;
	      درخت_VEC_ELT (درخت_قدر (t), 4) = omp_orig;
	      درخت_VEC_ELT (درخت_قدر (t), 5) = initializer.قدر;
	      walk_درخت (&initializer.قدر, c_check_omp_declare_reduction_r,
			 &درخت_VEC_ELT (درخت_قدر (t), 3), تہی);
	      walk_درخت (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &درخت_VEC_ELT (درخت_قدر (t), 3), تہی);
	    }
	}

      نکالو_stmt_list (stmt);
      نکالو_scope ();
      اگر (cfun->language != تہی)
	{
	  ggc_free (cfun->language);
	  cfun->language = تہی;
	}
      سیٹ_cfun (تہی);
      current_function_decl = NULL_درخت;
      اگر (nested)
	c_نکالو_function_context ();

      اگر (!clauses.is_خالی_خانے ())
	{
	  parser->علامات = saved_علامات;
	  parser->علامات_avail = علامات_avail;
	}
      اگر (bad)
	جاؤ fail;
      اگر (errs != errorcount)
	توڑو;
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

ساکن منطقی
c_parser_omp_declare (c_parser *parser, شمار pragma_context context)
{
  c_parser_consume_pragma (parser);
  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  واپس سچ;
	}
      اگر (strcmp (p, "reduction") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_reduction (parser, context);
	  واپس جھوٹ;
	}
      اگر (strcmp (p, "mapper") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_mapper (parser, context);
	  واپس جھوٹ;
	}
      اگر (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	  واپس جھوٹ;
	}
      اگر (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_ہدف (parser);
	  واپس جھوٹ;
	}
      اگر (strcmp (p, "variant") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  واپس سچ;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_مقصد_pragma_eol (parser);
  واپس جھوٹ;
}

/* OpenMP 5.0
   #pragma omp requires clauses[optseq] new-line  */

ساکن خالی
c_parser_omp_requires (c_parser *parser)
{
  شمار omp_requires new_req = (شمار omp_requires) 0;

  c_parser_consume_pragma (parser);

  location_t loc = c_parser_peek_token (parser)->location;
  جب (c_parser_اگلا_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	{
	  ثابت حرف *p
	    = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  شمار omp_requires this_req = (شمار omp_requires) 0;

	  اگر (!strcmp (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_پتہ;
	  ورنہ اگر (!strcmp (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_حافظہ;
	  ورنہ اگر (!strcmp (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  ورنہ اگر (!strcmp (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  ورنہ اگر (!strcmp (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_الٹ_OFFLOAD;
	  ورنہ اگر (!strcmp (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      اگر (parens.require_open (parser))
		{
		  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
		    {
		      درخت v = c_parser_peek_token (parser)->قدر;
		      p = IDENTIFIER_اشارہ_گر (v);

		      اگر (!strcmp (p, "seq_cst"))
			this_req
			  = (شمار omp_requires) OMP_حافظہ_ترتیب_SEQ_CST;
		      ورنہ اگر (!strcmp (p, "relaxed"))
			this_req
			  = (شمار omp_requires) OMP_حافظہ_ترتیب_RELAXED;
		      ورنہ اگر (!strcmp (p, "release"))
			this_req
			  = (شمار omp_requires) OMP_حافظہ_ترتیب_RELEASE;
		      ورنہ اگر (!strcmp (p, "acq_rel"))
			this_req
			  = (شمار omp_requires) OMP_حافظہ_ترتیب_ACQ_REL;
		      ورنہ اگر (!strcmp (p, "acquire"))
			this_req
			  = (شمار omp_requires) OMP_حافظہ_ترتیب_ACQUIRE;
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
			  توڑو;
			طےشدہ:
			  اگر (c_parser_peek_2nd_token (parser)->type
			      == CPP_CLOSE_PAREN)
			    c_parser_consume_token (parser);
			  توڑو;
			}
		    }
		  ورنہ
		    c_parser_consume_token (parser);

		  parens.skip_until_ملا_close (parser);
		  اگر (this_req == 0)
		    {
		      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
		      واپس;
		    }
		}
	      p = تہی;
	    }
	  ورنہ
	    {
	      error_at (cloc, "expected %<unified_address%>, "
			      "%<unified_shared_memory%>, "
			      "%<self_maps%>, "
			      "%<dynamic_allocators%>, "
			       "%<reverse_offload%> "
			       "or %<atomic_default_mem_order%> clause");
	      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	      واپس;
	    }
	  اگر (p)
	    c_parser_consume_token (parser);
	  اگر (this_req)
	    {
	      اگر ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتیب) != 0)
		{
		  اگر ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  اگر (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_نقاب & OMP_REQUIRES_ہدف_مستعمل) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      ورنہ اگر ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتیب) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (شمار omp_requires) 0;
		}
	      ورنہ اگر ((omp_requires_نقاب
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتیب) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (شمار omp_requires)
		       (omp_requires_نقاب
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتیب);
		}
	      ورنہ اگر ((omp_requires_نقاب
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتیب_مستعمل) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (شمار omp_requires) (new_req | this_req);
	      omp_requires_نقاب
		= (شمار omp_requires) (omp_requires_نقاب | this_req);
	      جاری;
	    }
	}
      توڑو;
    }
  c_parser_skip_مقصد_pragma_eol (parser);

  اگر (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

ساکن درخت
c_اختتام_taskloop_clauses (درخت clauses)
{
  درخت *pc = &clauses;
  برائے (درخت c = clauses; c; c = *pc)
    {
      منطقی remove = جھوٹ;
      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_REDUCTION)
	{
	  درخت type = strip_array_types (درخت_TYPE (OMP_CLAUSE_DECL (c)));
	  اگر (integer_zerop (TYPE_سائز_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      remove = سچ;
	    }
	  ورنہ اگر (درخت_رمز (TYPE_سائز_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      remove = سچ;
	    }
	}
      اگر (remove)
	*pc = OMP_CLAUSE_CHAIN (c);
      ورنہ
	pc = &OMP_CLAUSE_CHAIN (c);
    }
  واپس clauses;
}

/* OpenMP 4.5:
   #pragma omp taskloop taskloop-clause[optseq] new-line
     for-loop

   #pragma omp taskloop simd taskloop-simd-clause[optseq] new-line
     for-loop  */

#تعریف_کرو OMP_TASKLOOP_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_نجی)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_GRAINSIZE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_عدد_TASKS)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_UNTIED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FINAL)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MERGEABLE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOGROUP)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ترجیح)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_اندر_REDUCTION))

ساکن درخت
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       حرف *p_name, omp_clause_نقاب نقاب, درخت *cclauses,
		       منطقی *if_p)
{
  درخت clauses, بلاک, ret;

  strcat (p_name, " taskloop");
  نقاب |= OMP_TASKLOOP_CLAUSE_نقاب;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  اگر ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_عدد_دھاگے)) != 0)
    نقاب &= ~(OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_اندر_REDUCTION);

  اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);

      اگر (strcmp (p, "simd") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_بانٹو_گنتی];
	  اگر (cclauses == تہی)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  اگر (!flag_openmp)  /* flag_openmp_simd  */
	    واپس c_parser_omp_simd (loc, parser, p_name, نقاب, cclauses,
				      if_p);
	  بلاک = c_begin_compound_stmt (سچ);
	  ret = c_parser_omp_simd (loc, parser, p_name, نقاب, cclauses, if_p);
	  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
	  اگر (ret == تہی)
	    واپس ret;
	  ret = make_گرہ (OMP_TASKLOOP);
	  درخت_TYPE (ret) = void_type_گرہ;
	  OMP_FOR_BODY (ret) = بلاک;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_بانٹو_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_اختتام_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  سیٹ_اظہاریہ_LOCATION (ret, loc);
	  جوڑو_stmt (ret);
	  واپس ret;
	}
    }
  اگر (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
      واپس NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == تہی);
  اگر (cclauses)
    {
      omp_بانٹو_clauses (loc, OMP_TASKLOOP, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_بانٹو_TASKLOOP];
    }

  clauses = c_اختتام_taskloop_clauses (clauses);
  بلاک = c_begin_compound_stmt (سچ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, تہی, if_p);
  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
  جوڑو_stmt (بلاک);

  واپس ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
ساکن درخت
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  درخت sizes = NULL_درخت;

  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  اگر (tok->type != CPP_NAME
      || strcmp ("sizes", IDENTIFIER_اشارہ_گر (tok->قدر)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      واپس error_mark_گرہ;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  اگر (!parens.require_open (parser))
    واپس error_mark_گرہ;

  vec<درخت, va_gc> *sizes_vec
    = c_parser_اظہاریہ_list (parser, سچ, سچ, تہی, تہی, تہی, تہی);
  sizes = build_درخت_list_vec (sizes_vec);
  release_درخت_سمتیہ (sizes_vec);

  برائے (درخت s = sizes; s; s = درخت_CHAIN (s))
    {
      درخت اظہاریہ = درخت_قدر (s);
      اگر (اظہاریہ == error_mark_گرہ)
	{
	  parens.skip_until_ملا_close (parser);
	  واپس error_mark_گرہ;
	}

      HOST_WIDE_INT n;
      اگر (!INTEGRAL_TYPE_P (درخت_TYPE (اظہاریہ))
	  || !درخت_سماتا_shwi_p (اظہاریہ)
	  || (n = درخت_مقصد_shwi (اظہاریہ)) <= 0
	  || (صحیح) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  درخت_قدر (s) = integer_one_گرہ;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  درخت c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  واپس c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

ساکن درخت
c_parser_omp_tile (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_مقصد_pragma_eol (parser);

  اگر (!clauses || clauses == error_mark_گرہ)
    واپس error_mark_گرہ;

  درخت بلاک = c_begin_compound_stmt (سچ);
  درخت ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    تہی, if_p);
  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
  جوڑو_stmt (بلاک);

  واپس ret;
}

#تعریف_کرو OMP_UNROLL_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_بھرا))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

ساکن درخت
c_parser_omp_unroll (location_t loc, c_parser *parser, منطقی *if_p)
{
  درخت clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_نقاب,
					   "#pragma omp unroll", سچ);

  درخت بلاک = c_begin_compound_stmt (سچ);
  درخت ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    تہی, if_p);
  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);
  جوڑو_stmt (بلاک);

  واپس ret;
}

/* OpenMP 5.1
   #pragma omp nothing new-line  */

ساکن خالی
c_parser_omp_nothing (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_مقصد_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp error clauses[optseq] new-line  */

ساکن منطقی
c_parser_omp_error (c_parser *parser, شمار pragma_context context)
{
  صحیح at_compilation = -1;
  صحیح severity_fatal = -1;
  درخت پیغام = NULL_درخت;
  منطقی bad = جھوٹ;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  جب (c_parser_اگلا_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      اگر (!c_parser_اگلا_token_is (parser, CPP_NAME))
	توڑو;

      ثابت حرف *p
	= IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      location_t cloc = c_parser_peek_token (parser)->location;
      ساکن ثابت حرف *دلائل[] = {
	"execution", "compilation", "warning", "fatal"
      };
      صحیح *v = تہی;
      صحیح idx = 0, n = -1;
      درخت m = NULL_درخت;

      اگر (!strcmp (p, "at"))
	v = &at_compilation;
      ورنہ اگر (!strcmp (p, "severity"))
	{
	  v = &severity_fatal;
	  idx += 2;
	}
      ورنہ اگر (strcmp (p, "message"))
	{
	  error_at (cloc,
		    "expected %<at%>, %<severity%> or %<message%> clause");
	  c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
	  واپس جھوٹ;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      اگر (parens.require_open (parser))
	{
	  اگر (v == تہی)
	    {
	      location_t اظہاریہ_loc = c_parser_peek_token (parser)->location;
	      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	      اظہاریہ = convert_lvalue_مقصد_rvalue (اظہاریہ_loc, اظہاریہ, سچ, سچ);
	      m = convert (const_string_type_گرہ, اظہاریہ.قدر);
	      m = c_fully_fold (m, جھوٹ, تہی);
	    }
	  ورنہ
	    {
	      اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
		{
		  درخت val = c_parser_peek_token (parser)->قدر;
		  ثابت حرف *q = IDENTIFIER_اشارہ_گر (val);

		  اگر (!strcmp (q, دلائل[idx]))
		    n = 0;
		  ورنہ اگر (!strcmp (q, دلائل[idx + 1]))
		    n = 1;
		}
	      اگر (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", دلائل[idx], دلائل[idx + 1]);
		  bad = سچ;
		  انتخاب (c_parser_peek_token (parser)->type)
		    {
		    حالت CPP_EOF:
		    حالت CPP_PRAGMA_EOL:
		    حالت CPP_CLOSE_PAREN:
		      توڑو;
		    طےشدہ:
		      اگر (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)
			c_parser_consume_token (parser);
		      توڑو;
		    }
		}
	      ورنہ
		c_parser_consume_token (parser);
	    }

	  parens.skip_until_ملا_close (parser);

	  اگر (v == تہی)
	    {
	      اگر (پیغام)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = سچ;
		}
	      ورنہ
		پیغام = m;
	    }
	  ورنہ اگر (n != -1)
	    {
	      اگر (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = سچ;
		}
	      ورنہ
		*v = n;
	    }
	}
      ورنہ
	bad = سچ;
    }
  c_parser_skip_مقصد_pragma_eol (parser);
  اگر (bad)
    واپس سچ;

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
	  واپس سچ;
	}
      اگر (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->اندر_intervening_رمز)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->fail = سچ;
	  واپس سچ;
	}
      درخت fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_اندر_GOMP_ERROR
						: BUILT_اندر_GOMP_WARNING);
      اگر (!پیغام)
	پیغام = build_zero_cst (const_string_type_گرہ);
      درخت stmt = build_call_اظہاریہ_loc (loc, fndecl, 2, پیغام,
				       build_all_ones_cst (سائز_type_گرہ));
      جوڑو_stmt (stmt);
      واپس سچ;
    }
  ثابت حرف *پیغام_2 = تہی;
  اگر (پیغام)
    {
      پیغام_2 = c_getstr (پیغام);
      اگر (پیغام_2 == تہی)
	پیغام_2 = _("<message unknown at compile time>");
    }
  ثابت شمار diagnostics::قسم diag_قسم = (severity_fatal
					    ? diagnostics::قسم::error
					    : diagnostics::قسم::warning);
  اگر (پیغام_2)
    emit_diagnostic (diag_قسم, loc, 0,
		     "%<pragma omp error%> encountered: %s", پیغام_2);
  ورنہ
    emit_diagnostic (diag_قسم, loc, 0,
		     "%<pragma omp error%> encountered");
  واپس جھوٹ;
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

ساکن خالی
c_parser_omp_assumption_clauses (c_parser *parser, منطقی is_assume)
{
  منطقی no_openmp = جھوٹ;
  منطقی no_openmp_constructs = جھوٹ;
  منطقی no_openmp_routines = جھوٹ;
  منطقی no_parallelism = جھوٹ;
  bitmap_سر absent_سر, شامل_ہے_سر;

  bitmap_obstack_initialize (تہی);
  bitmap_initialize (&absent_سر, &bitmap_default_obstack);
  bitmap_initialize (&شامل_ہے_سر, &bitmap_default_obstack);

  اگر (c_parser_اگلا_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  جب (c_parser_اگلا_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      اگر (!c_parser_اگلا_token_is (parser, CPP_NAME))
	توڑو;

      ثابت حرف *p
	= IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      location_t cloc = c_parser_peek_token (parser)->location;

      اگر (!strcmp (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  اگر (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = سچ;
	}
      ورنہ اگر (!strcmp (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  اگر (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = سچ;
	}
      ورنہ اگر (!strcmp (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  اگر (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = سچ;
	}
      ورنہ اگر (!strcmp (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  اگر (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = سچ;
	}
      ورنہ اگر (!strcmp (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  اگر (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_اظہاریہ اظہاریہ = c_parser_اظہاریہ_no_commas (parser, تہی);
	      درخت t = convert_lvalue_مقصد_rvalue (eloc, اظہاریہ, سچ, سچ).قدر;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, جھوٹ, تہی);
	      اگر (is_assume && t != error_mark_گرہ)
		{
		  درخت fn = build_call_اظہاریہ_اندرونی_loc (eloc, IFN_ASSUME,
							  void_type_گرہ, 1,
							  t);
		  جوڑو_stmt (fn);
		}
	      parens.skip_until_ملا_close (parser);
	    }
	}
      ورنہ اگر (!strcmp (p, "absent") || !strcmp (p, "contains"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  اگر (parens.require_open (parser))
	    {
	      کرو
		{
		  ثابت حرف *directive[3] = {};
		  صحیح i;
		  location_t dloc = c_parser_peek_token (parser)->location;
		  برائے (i = 0; i < 3; i++)
		    {
		      درخت id;
		      اگر (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->قدر;
		      ورنہ اگر (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  شمار rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      ورنہ
			توڑو;
		      directive[i] = IDENTIFIER_اشارہ_گر (id);
		    }
		  اگر (i == 0)
		    error_at (dloc, "expected directive name");
		  ورنہ
		    {
		      ثابت ساخت c_omp_directive *dir
			= c_omp_categorize_directive (directive[0],
						      directive[1],
						      directive[2]);
		      اگر (dir
			  && dir->id != PRAGMA_OMP_انتہا
			  && (dir->قسم == C_OMP_DIR_DECLARATIVE
			      || dir->قسم == C_OMP_DIR_INFORMATIONAL
			      || dir->قسم == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      ورنہ اگر (dir == تہی
			       || dir->id == PRAGMA_OMP_انتہا
			       || (!dir->دوسرا && directive[1])
			       || (!dir->تیسرا && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      ورنہ
			{
			  صحیح id = dir - c_omp_directives;
			  اگر (bitmap_ثنائی_ہندسہ_p (p[0] == 'a' ? &شامل_ہے_سر
							: &absent_سر, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  ورنہ اگر (!bitmap_سیٹ_ثنائی_ہندسہ (p[0] == 'a'
						    ? &absent_سر
						    : &شامل_ہے_سر, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned multiple times in %qs "
					    "clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "", p);
			}
		      برائے (; i; --i)
			c_parser_consume_token (parser);
		    }
		  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  ورنہ
		    توڑو;
		}
	      جب (1);
	      parens.skip_until_ملا_close (parser);
	    }
	}
      ورنہ اگر (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
	    {
	      matching_parens parens;
	      parens.consume_open (parser);
	      c_parser_متوازن_token_sequence (parser);
	      parens.require_close (parser);
	    }
	}
      ورنہ
	{
	  c_parser_consume_token (parser);
	  error_at (cloc, "expected assumption clause");
	  توڑو;
	}
    }
  c_parser_skip_مقصد_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

ساکن خالی
c_parser_omp_assume (c_parser *parser, منطقی *if_p)
{
  c_parser_omp_assumption_clauses (parser, سچ);
  جوڑو_stmt (c_parser_omp_structured_بلاک (parser, if_p));
}

/* OpenMP 5.1
   #pragma omp assumes clauses[optseq] new-line  */

ساکن خالی
c_parser_omp_assumes (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_omp_assumption_clauses (parser, جھوٹ);
}

/* Helper function for c_parser_omp_metadirective.  */

ساکن خالی
analyze_metadirective_body (c_parser *parser,
			    vec<c_token> &علامات,
			    vec<درخت> &labels)
{
  صحیح nesting_گہرائی = 0;
  صحیح bracket_گہرائی = 0;
  منطقی ignore_label = جھوٹ;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  جب (1)
    {
      c_token *token = c_parser_peek_token (parser);
      منطقی stop = جھوٹ;

      اگر (c_parser_اگلا_token_is_keyword (parser, RID_CASE))
	ignore_label = سچ;

      انتخاب (token->type)
	{
	حالت CPP_EOF:
	  توڑو;
	حالت CPP_NAME:
	  اگر (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.محفوظ_ڈالو (token->قدر);
	  جاؤ جوڑو;
	حالت CPP_OPEN_BRACE:
	  ++nesting_گہرائی;
	  جاؤ جوڑو;
	حالت CPP_CLOSE_BRACE:
	  اگر (--nesting_گہرائی == 0 && bracket_گہرائی == 0)
	    stop = سچ;
	  جاؤ جوڑو;
	حالت CPP_OPEN_PAREN:
	  ++bracket_گہرائی;
	  جاؤ جوڑو;
	حالت CPP_CLOSE_PAREN:
	  --bracket_گہرائی;
	  جاؤ جوڑو;
	حالت CPP_COLON:
	  ignore_label = جھوٹ;
	  جاؤ جوڑو;
	حالت CPP_SEMICOLON:
	  اگر (nesting_گہرائی == 0 && bracket_گہرائی == 0)
	    stop = سچ;
	  جاؤ جوڑو;
	طےشدہ:
	جوڑو:
	  علامات.محفوظ_ڈالو (*token);
	  اگر (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  ورنہ اگر (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_مقصد_pragma_eol (parser);
	  ورنہ
	    c_parser_consume_token (parser);
	  اگر (stop)
	    توڑو;
	  جاری;
	}
      توڑو;
    }
}

/* OpenMP 5.0:

  # pragma omp metadirective [clause[, clause]]
*/

ساکن خالی
c_parser_omp_metadirective (c_parser *parser, منطقی *if_p)
{
  ساکن غیرعلامتی صحیح metadirective_region_گنتی = 0;

  درخت ret;
  auto_vec<c_token> directive_علامات;
  auto_vec<c_token> body_علامات;
  auto_vec<درخت> body_labels;
  auto_vec<ثابت ساخت c_omp_directive *> directives;
  auto_vec<درخت> ctxs;
  vec<ساخت omp_variant> candidates;
  منطقی default_نظر_آیا = جھوٹ;
  صحیح directive_token_idx = 0;
  درخت standalone_body = NULL_درخت;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  منطقی requires_body = جھوٹ;

  ret = make_گرہ (OMP_METADIRECTIVE);
  سیٹ_اظہاریہ_LOCATION (ret, pragma_loc);
  درخت_TYPE (ret) = void_type_گرہ;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_درخت;

  c_parser_consume_pragma (parser);
  جب (c_parser_اگلا_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      اگر (c_parser_اگلا_token_is_not (parser, CPP_NAME)
	  && c_parser_اگلا_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  جاؤ error;
	}

      location_t مطابقت_loc = c_parser_peek_token (parser)->location;
      ثابت حرف *p = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      اگر (strcmp (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.جوڑو_fixit_replace (مطابقت_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      منطقی default_p
	= strcmp (p, "default") == 0 || strcmp (p, "otherwise") == 0;
      اگر (default_p)
	{
	  اگر (default_نظر_آیا)
	    {
	      error_at (مطابقت_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      جاؤ error;
	    }
	  default_نظر_آیا = سچ;
	}
      ورنہ اگر (default_نظر_آیا)
	{
	  error_at (مطابقت_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  جاؤ error;
	}
      اگر (!default_p && strcmp (p, "when") != 0)
	{
	  error_at (مطابقت_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  جاؤ error;
	}

      matching_parens parens;
      درخت ctx = NULL_درخت;
      منطقی skip = جھوٹ;

      اگر (!parens.require_open (parser))
	جاؤ error;

      اگر (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_درخت);
	  اگر (ctx == error_mark_گرہ)
	    جاؤ error;
	  ctx = omp_check_context_selector (مطابقت_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  اگر (ctx == error_mark_گرہ)
	    جاؤ error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_درخت, جھوٹ) == 0);

	  اگر (c_parser_اگلا_token_is_not (parser, CPP_COLON))
	    {
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      جاؤ error;
	    }
	  c_parser_consume_token (parser);
	}

      /* Read in the directive type and create a dummy pragma token for
	 it.  */
      location_t loc = c_parser_peek_token (parser)->location;

      ثابت حرف *directive[3] = {};
      صحیح i;
      برائے (i = 0; i < 3; i++)
	{
	  درخت id;
	  اگر (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      اگر (i == 0)
		directive[i++] = "nothing";
	      توڑو;
	    }
	  ورنہ اگر (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->قدر;
	  ورنہ اگر (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      شمار rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  ورنہ
	    توڑو;

	  directive[i] = IDENTIFIER_اشارہ_گر (id);
	}
      اگر (i == 0)
	{
	  error_at (loc, "expected directive name");
	  جاؤ error;
	}

      ثابت ساخت c_omp_directive *omp_directive
	= c_omp_categorize_directive (directive[0],
				      directive[1],
				      directive[2]);

      اگر (omp_directive == تہی)
	{
	  برائے (صحیح j = 0; j < i; j++)
	    c_parser_consume_token (parser);
	  c_parser_error (parser, "unknown directive name");
	  جاؤ error;
	}
      ورنہ
	{
	  صحیح token_گنتی = 0;
	  اگر (omp_directive->پہلا) token_گنتی++;
	  اگر (omp_directive->دوسرا) token_گنتی++;
	  اگر (omp_directive->تیسرا) token_گنتی++;
	  برائے (صحیح j = 0; j < token_گنتی; j++)
	    c_parser_consume_token (parser);
	}
      اگر (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  جاؤ error;
	}
      اگر (omp_directive->قسم == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  جاؤ error;
	}
      اگر (omp_directive->قسم == C_OMP_DIR_CONSTRUCT)
	requires_body = سچ;

      اگر (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_قسم = (شمار pragma_قسم) omp_directive->id;

	  directives.محفوظ_ڈالو (omp_directive);
	  directive_علامات.محفوظ_ڈالو (pragma_token);
	  ctxs.محفوظ_ڈالو (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      صحیح nesting_گہرائی = 0;
      جب (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  انتخاب (token->type)
	    {
	    حالت CPP_EOF:
	    حالت CPP_PRAGMA_EOL:
	      توڑو;
	    حالت CPP_OPEN_PAREN:
	      ++nesting_گہرائی;
	      جاؤ جوڑو;
	    حالت CPP_CLOSE_PAREN:
	      اگر (nesting_گہرائی-- == 0)
		{
		  c_parser_consume_token (parser);
		  توڑو;
		}
	      جاؤ جوڑو;
	    طےشدہ:
	    جوڑو:
	      اگر (!skip)
		directive_علامات.محفوظ_ڈالو (*token);
	      c_parser_consume_token (parser);
	      جاری;
	    }
	  توڑو;
	}

      اگر (!skip)
	{
	  c_token eol_token;
	  memset (&eol_token, 0, حجم (eol_token));
	  eol_token.type = CPP_PRAGMA_EOL;
	  directive_علامات.محفوظ_ڈالو (eol_token);
	}
    }
  c_parser_skip_مقصد_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  اگر (ctxs.لمبائی () == 1)
    {
      درخت ctx = ctxs[0];
      اگر (ctx == NULL_درخت
	  || (omp_context_selector_matches (ctx, NULL_درخت, جھوٹ) == 1
	      && directive_علامات[0].pragma_قسم == PRAGMA_OMP_NOTHING))
	واپس;
    }

  اگر (!default_نظر_آیا)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      ثابت ساخت c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", تہی, تہی);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_قسم = PRAGMA_OMP_NOTHING;

      directives.محفوظ_ڈالو (omp_directive);
      directive_علامات.محفوظ_ڈالو (pragma_token);
      ctxs.محفوظ_ڈالو (NULL_درخت);

      c_token eol_token;
      memset (&eol_token, 0, حجم (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_علامات.محفوظ_ڈالو (eol_token);
    }

  اگر (requires_body)
    analyze_metadirective_body (parser, body_علامات, body_labels);

  /* Process each candidate directive.  */
  غیرعلامتی i;
  درخت ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> علامات;

      /* Add the directive tokens.  */
      کرو
	علامات.محفوظ_ڈالو (directive_علامات [directive_token_idx++]);
      جب (علامات.آخری ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_علامات.is_خالی_خانے ());
      برائے (غیرعلامتی j = 0; j < body_علامات.لمبائی (); j++)
	علامات.محفوظ_ڈالو (body_علامات[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, حجم (eof_token));
      eof_token.type = CPP_EOF;
      علامات.محفوظ_ڈالو (eof_token);
      علامات.محفوظ_ڈالو (eof_token);

      غیرعلامتی صحیح old_علامات_avail = parser->علامات_avail;
      c_token *old_علامات = parser->علامات;
      ساخت omp_attribute_pragma_state *old_اندر_omp_attribute_pragma
	= parser->اندر_omp_attribute_pragma;
      ساخت omp_metadirective_parse_ڈیٹا *old_state
	= parser->omp_metadirective_state;

      ساخت omp_metadirective_parse_ڈیٹا new_state;
      new_state.body_labels = &body_labels;
      new_state.region_عدد = ++metadirective_region_گنتی;

      parser->علامات = علامات.پتہ ();
      parser->علامات_avail = علامات.لمبائی ();
      parser->اندر_omp_attribute_pragma = تہی;
      parser->omp_metadirective_state = &new_state;

      صحیح پچھلا_errorcount = errorcount;
      درخت directive = c_begin_compound_stmt (سچ);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_درخت);
      directive = c_انتہا_compound_stmt (pragma_loc, directive, سچ);
      منطقی standalone_p
	= directives[i]->قسم == C_OMP_DIR_STANDALONE
	  || directives[i]->قسم == C_OMP_DIR_UTILITY;
      اگر (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  اگر (standalone_body == NULL_درخت)
	    {
	      standalone_body = ڈالو_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = نکالو_stmt_list (standalone_body);
	    }
	  ورنہ
	    c_parser_skip_مقصد_انتہا_کا_بلاک_or_statement (parser, سچ);
	}

      درخت body = standalone_p ? standalone_body : NULL_درخت;
      درخت variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      اگر (errorcount == پچھلا_errorcount)
	{
	  gcc_assert (parser->علامات_avail == 2);
	  gcc_assert (c_parser_اگلا_token_is (parser, CPP_EOF));
	  gcc_assert (c_parser_peek_2nd_token (parser)->type == CPP_EOF);
	}

      parser->علامات = old_علامات;
      parser->علامات_avail = old_علامات_avail;
      parser->اندر_omp_attribute_pragma = old_اندر_omp_attribute_pragma;
      parser->omp_metadirective_state = old_state;
    }

  /* Try to resolve the metadirective early.  */
  candidates = omp_early_resolve_metadirective (ret);
  اگر (!candidates.is_خالی_خانے ())
    ret = c_omp_expand_variant_construct (candidates);

  جوڑو_stmt (ret);
  واپس;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  اگر (parser->اندر_pragma)
    c_parser_skip_مقصد_pragma_eol (parser, جھوٹ);
}

/* Main entry point to parsing most OpenMP pragmas.  */

ساکن خالی
c_parser_omp_construct (c_parser *parser, منطقی *if_p)
{
  شمار pragma_قسم p_قسم;
  location_t loc;
  درخت stmt;
  حرف p_name[حجم "#pragma omp teams distribute parallel for simd"];
  omp_clause_نقاب نقاب (0);

  loc = c_parser_peek_token (parser)->location;
  p_قسم = c_parser_peek_token (parser)->pragma_قسم;
  c_parser_consume_pragma (parser);

  انتخاب (p_قسم)
    {
    حالت PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, سچ);
      واپس;
    حالت PRAGMA_OACC_CACHE:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      توڑو;
    حالت PRAGMA_OACC_ڈیٹا:
      stmt = c_parser_oacc_ڈیٹا (loc, parser, if_p);
      توڑو;
    حالت PRAGMA_OACC_HOST_ڈیٹا:
      stmt = c_parser_oacc_host_ڈیٹا (loc, parser, if_p);
      توڑو;
    حالت PRAGMA_OACC_KERNELS:
    حالت PRAGMA_OACC_PARALLEL:
    حالت PRAGMA_OACC_SERIAL:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_قسم, p_name, if_p);
      توڑو;
    حالت PRAGMA_OACC_LOOP:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, نقاب, تہی, if_p);
      توڑو;
    حالت PRAGMA_OACC_WAIT:
      strcpy (p_name, "#pragma wait");
      stmt = c_parser_oacc_wait (loc, parser, p_name);
      توڑو;
    حالت PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (loc, parser, جھوٹ);
      واپس;
    حالت PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (loc, parser, if_p);
      توڑو;
    حالت PRAGMA_OMP_DISTRIBUTE:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_distribute (loc, parser, p_name, نقاب, تہی, if_p);
      توڑو;
    حالت PRAGMA_OMP_FOR:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, نقاب, تہی, if_p);
      توڑو;
    حالت PRAGMA_OMP_LOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, نقاب, تہی, if_p);
      توڑو;
    حالت PRAGMA_OMP_MASKED:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, نقاب, تہی, if_p);
      توڑو;
    حالت PRAGMA_OMP_MASTER:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, نقاب, تہی, if_p,
				  UNKNOWN_LOCATION);
      توڑو;
    حالت PRAGMA_OMP_PARALLEL:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, نقاب, تہی, if_p);
      توڑو;
    حالت PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      توڑو;
    حالت PRAGMA_OMP_SECTIONS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, نقاب, تہی);
      توڑو;
    حالت PRAGMA_OMP_SIMD:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, نقاب, تہی, if_p);
      توڑو;
    حالت PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (loc, parser, if_p);
      توڑو;
    حالت PRAGMA_OMP_TASK:
      stmt = c_parser_omp_task (loc, parser, if_p);
      توڑو;
    حالت PRAGMA_OMP_TASKGROUP:
      stmt = c_parser_omp_taskgroup (loc, parser, if_p);
      توڑو;
    حالت PRAGMA_OMP_TASKLOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_taskloop (loc, parser, p_name, نقاب, تہی, if_p);
      توڑو;
    حالت PRAGMA_OMP_TEAMS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, نقاب, تہی, if_p);
      توڑو;
    حالت PRAGMA_OMP_ASSUME:
      c_parser_omp_assume (parser, if_p);
      واپس;
    حالت PRAGMA_OMP_TILE:
      stmt = c_parser_omp_tile (loc, parser, if_p);
      توڑو;
    حالت PRAGMA_OMP_UNROLL:
      stmt = c_parser_omp_unroll (loc, parser, if_p);
      توڑو;
    حالت PRAGMA_OMP_DISPATCH:
      stmt = c_parser_omp_dispatch (loc, parser);
      توڑو;
    طےشدہ:
      gcc_unreachable ();
    }

  اگر (stmt && stmt != error_mark_گرہ)
    gcc_assert (اظہاریہ_LOCATION (stmt) != UNKNOWN_LOCATION);
}

/* OpenMP 6.0:
   # pragma omp groupprivate (variable-list) [device_type(...)]  */

#تعریف_کرو OMP_GROUPPRIVATE_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE) )

ساکن خالی
c_parser_omp_groupprivate (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  درخت vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, تہی);
  درخت clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_نقاب,
					   "#pragma omp groupprivate");
  /* TODO: Implies 'declare target local' with specified device_type, check for
     conflicts.  Check for other restrictions.  */
  (خالی) vars;
  (خالی) clauses;
  sorry_at (loc, "%<omp groupprivate%>");
}

/* OpenMP 2.5:
   # pragma omp threadprivate (variable-list) */

ساکن خالی
c_parser_omp_threadprivate (c_parser *parser)
{
  درخت vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, تہی);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  برائے (t = vars; t; t = درخت_CHAIN (t))
    {
      درخت v = درخت_PURPOSE (t);
      loc = اظہاریہ_LOCATION (درخت_قدر (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      اگر (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      ورنہ اگر (درخت_مستعمل (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      ورنہ اگر (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      ورنہ اگر (درخت_TYPE (v) == error_mark_گرہ)
	;
      ورنہ اگر (! COMPLETE_TYPE_P (درخت_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      ورنہ
	{
	  اگر (! DECL_THREAD_LOCAL_P (v))
	    {
	      سیٹ_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      اگر (DECL_RTL_سیٹ_P (v))
		make_decl_rtl (v);
	    }
	  C_DECL_THREADPRIVATE_P (v) = 1;
	}
    }

  c_parser_skip_مقصد_pragma_eol (parser);
}

/* Parse a transaction attribute (GCC Extension).

   transaction-attribute:
     gnu-attributes
     attribute-specifier
*/

ساکن درخت
c_parser_transaction_اوصاف (c_parser *parser)
{
  اگر (c_parser_اگلا_token_is_keyword (parser, RID_ATTRIBUTE))
    واپس c_parser_gnu_اوصاف (parser);

  اگر (!c_parser_اگلا_token_is (parser, CPP_OPEN_مربع))
    واپس NULL_درخت;
  واپس c_parser_std_attribute_specifier (parser, سچ);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

ساکن درخت
c_parser_transaction (c_parser *parser, شمار rid keyword)
{
  غیرعلامتی صحیح old_اندر = parser->اندر_transaction;
  غیرعلامتی صحیح this_اندر = 1, new_اندر;
  location_t loc = c_parser_peek_token (parser)->location;
  درخت stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_اگلا_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  اگر (keyword == RID_TRANSACTION_RELAXED)
    this_اندر |= TM_STMT_ATTR_RELAXED;
  ورنہ
    {
      attrs = c_parser_transaction_اوصاف (parser);
      اگر (attrs)
	this_اندر |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_اندر = this_اندر | (old_اندر & TM_STMT_ATTR_OUTER);

  parser->اندر_transaction = new_اندر;
  stmt = c_parser_compound_statement (parser);
  parser->اندر_transaction = old_اندر;

  اگر (flag_tm)
    stmt = c_اختتام_transaction (loc, stmt, this_اندر);
  ورنہ
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  واپس stmt;
}

/* Parse a __transaction_atomic or __transaction_relaxed expression
   (GCC Extension).

   transaction-expression:
     __transaction_atomic ( expression )
     __transaction_relaxed ( expression )
*/

ساکن ساخت c_اظہاریہ
c_parser_transaction_عبارت (c_parser *parser, شمار rid keyword)
{
  ساخت c_اظہاریہ ret;
  غیرعلامتی صحیح old_اندر = parser->اندر_transaction;
  غیرعلامتی صحیح this_اندر = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  درخت attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_اگلا_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  اگر (keyword == RID_TRANSACTION_RELAXED)
    this_اندر |= TM_STMT_ATTR_RELAXED;
  ورنہ
    {
      attrs = c_parser_transaction_اوصاف (parser);
      اگر (attrs)
	this_اندر |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->اندر_transaction = this_اندر;
  matching_parens parens;
  اگر (parens.require_open (parser))
    {
      درخت اظہاریہ = c_parser_عبارت (parser).قدر;
      ret.original_type = درخت_TYPE (اظہاریہ);
      ret.قدر = build1 (TRANSACTION_اظہاریہ, ret.original_type, اظہاریہ);
      اگر (this_اندر & TM_STMT_ATTR_RELAXED)
	TRANSACTION_اظہاریہ_RELAXED (ret.قدر) = 1;
      سیٹ_اظہاریہ_LOCATION (ret.قدر, loc);
      ret.original_رمز = TRANSACTION_اظہاریہ;
      ret.m_decimal = 0;
      اگر (!parens.require_close (parser))
	{
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, تہی);
	  جاؤ error;
	}
    }
  ورنہ
    {
     error:
      ret.سیٹ_error ();
      ret.original_رمز = ERROR_MARK;
      ret.original_type = تہی;
    }
  parser->اندر_transaction = old_اندر;

  اگر (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  سیٹ_c_اظہاریہ_ماخذ_range (&ret, loc, loc);

  واپس ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

ساکن درخت
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت attrs;
  منطقی is_outer = جھوٹ;

  gcc_assert (c_parser_اگلا_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_اوصاف (parser);
  اگر (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  اگر (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      جاؤ ret_error;
    }
  ورنہ اگر (parser->اندر_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      جاؤ ret_error;
    }
  ورنہ اگر (is_outer)
    {
      اگر ((parser->اندر_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  جاؤ ret_error;
	}
    }
  ورنہ اگر (parser->اندر_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      جاؤ ret_error;
    }

  واپس جوڑو_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  واپس build1 (NOP_اظہاریہ, void_type_گرہ, error_mark_گرہ);
}

/* Parse a single source file.  */

خالی
c_parse_file (خالی)
{
  /* Use local storage to begin.  If the first token is a pragma, parse it.
     If it is #pragma GCC pch_preprocess, then this will load a PCH file
     which will cause garbage collection.  */
  c_parser tparser;

  memset (&tparser, 0, حجم tparser);
  tparser.translate_لڑیاں_p = سچ;
  tparser.علامات = &tparser.علامات_buf[0];
  the_parser = &tparser;

  اگر (c_parser_peek_token (&tparser)->pragma_قسم == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  ورنہ
    c_common_no_مزید_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  اگر (tparser.علامات == &tparser.علامات_buf[0])
    the_parser->علامات = &the_parser->علامات_buf[0];

  /* Initialize EH, if we've been told to do so.  */
  اگر (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = تہی;
}

خالی
c_init_preprocess (خالی)
{
  /* Create a parser for use by pragma_lex during preprocessing.  */
  the_parser = ggc_alloc<c_parser> ();
  memset (the_parser, 0, حجم (c_parser));
  the_parser->علامات = &the_parser->علامات_buf[0];
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
c_parser_parse_rtl_body (c_parser *parser, حرف *آغاز_with_pass)
{
  اگر (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      آزاد (آغاز_with_pass);
      واپس c_parser_peek_token (parser)->location;
    }

  location_t آغاز_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  صحیح عدد_open_braces = 1;
  جب (1)
    {
      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_OPEN_BRACE:
	  عدد_open_braces++;
	  توڑو;
	حالت CPP_CLOSE_BRACE:
	  اگر (--عدد_open_braces == 0)
	    جاؤ ملا_closing_brace;
	  توڑو;
	حالت CPP_EOF:
	  error_at (آغاز_loc, "no closing brace");
	  آزاد (آغاز_with_pass);
	  واپس c_parser_peek_token (parser)->location;
	طےشدہ:
	  توڑو;
	}
      c_parser_consume_token (parser);
    }

 ملا_closing_brace:
  /* At the closing brace; record its location.  */
  location_t انتہا_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  اگر (!read_rtl_function_body_from_file_range (آغاز_loc, انتہا_loc))
    {
      آزاد (آغاز_with_pass);
      واپس انتہا_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  تسلسل_rtl_passes (آغاز_with_pass);
  واپس انتہا_loc;
}

#شامل "gt-c-c-parser.h"
