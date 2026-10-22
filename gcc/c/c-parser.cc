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

#అన్తర్భావ "config.h"
#నిర్వచించు INCLUDE_STRING
#అన్తర్భావ "system.h"
#అన్తర్భావ "coretypes.h"
#అన్తర్భావ "target.h"
#అన్తర్భావ "function.h"
#అన్తర్భావ "c-tree.h"
#అన్తర్భావ "timevar.h"
#అన్తర్భావ "stringpool.h"
#అన్తర్భావ "cgraph.h"
#అన్తర్భావ "attribs.h"
#అన్తర్భావ "stor-layout.h"
#అన్తర్భావ "varasm.h"
#అన్తర్భావ "trans-mem.h"
#అన్తర్భావ "c-family/c-pragma.h"
#అన్తర్భావ "c-lang.h"
#అన్తర్భావ "c-family/c-objc.h"
#అన్తర్భావ "plugin.h"
#అన్తర్భావ "omp-general.h"
#అన్తర్భావ "omp-offload.h"
#అన్తర్భావ "builtins.h"
#అన్తర్భావ "gomp-constants.h"
#అన్తర్భావ "c-family/c-indentation.h"
#అన్తర్భావ "gimple-expr.h"
#అన్తర్భావ "context.h"
#అన్తర్భావ "gcc-rich-location.h"
#అన్తర్భావ "c-parser.h"
#అన్తర్భావ "gimple-parser.h"
#అన్తర్భావ "read-rtl-function.h"
#అన్తర్భావ "run-rtl-passes.h"
#అన్తర్భావ "intl.h"
#అన్తర్భావ "c-family/name-hint.h"
#అన్తర్భావ "tree-iterator.h"
#అన్తర్భావ "tree-pretty-print.h"
#అన్తర్భావ "memmodel.h"
#అన్తర్భావ "c-family/known-headers.h"
#అన్తర్భావ "bitmap.h"
#అన్తర్భావ "analyzer/analyzer-language.h"
#అన్తర్భావ "toplev.h"
#అన్తర్భావ "asan.h"
#అన్తర్భావ "c-family/c-ubsan.h"
#అన్తర్భావ "gcc-urlifier.h"

/* We need to walk over decls with incomplete struct/union/enum types
   after parsing the whole translation unit.
   In finish_decl(), if the decl is static, has incomplete
   struct/union/enum type, it is appended to incomplete_record_decls.
   In c_parser_translation_unit(), we iterate over incomplete_record_decls
   and report error if any of the decls are still incomplete.  */

vec<వృక్షం> incomplete_రికార్డు_decls;

శూన్య
సమితి_c_సమాసం_ఆధారం_range (c_సమాసం *సమాసం,
			 location_t ప్రారంభం, location_t ముగింపు)
{
  సమాసం->src_range.m_ప్రారంభం = ప్రారంభం;
  సమాసం->src_range.m_ముగింపు = ముగింపు;
  ఒకవేళ (సమాసం->విలువ)
    సమితి_ఆధారం_range (సమాసం->విలువ, ప్రారంభం, ముగింపు);
}

శూన్య
సమితి_c_సమాసం_ఆధారం_range (c_సమాసం *సమాసం,
			 ఆధారం_range src_range)
{
  సమాసం->src_range = src_range;
  ఒకవేళ (సమాసం->విలువ)
    సమితి_ఆధారం_range (సమాసం->విలువ, src_range);
}


/* Initialization routine for this file.  */

శూన్య
c_parse_init (శూన్య)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  గుర్తులేని పూర్ణాంకం i;
  వృక్షం id;
  పూర్ణాంకం ముసుగు = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  ముసుగు |= D_CXXONLY;
  ఒకవేళ (!flag_isoc99)
    ముసుగు |= D_C99;
  ఒకవేళ (!flag_isoc23)
    ముసుగు |= D_C23;
  ఒకవేళ (flag_no_asm)
    {
      ముసుగు |= D_ASM | D_EXT;
      ఒకవేళ (!flag_isoc99)
	ముసుగు |= D_EXT89;
      ఒకవేళ (!flag_isoc23)
	ముసుగు |= D_EXT11;
    }
  ఒకవేళ (!c_dialect_objc ())
    ముసుగు |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<వృక్షం> ((పూర్ణాంకం) RID_MAX);
  కొరకు (i = 0; i < అంకె_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      ఒకవేళ (c_common_reswords[i].disable & ముసుగు)
	{
	  ఒకవేళ (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].మాట);
	      C_సమితి_RID_సంకేతం (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_మాట (id) = 1;
	    }
	  కొనసాగు;
	}

      id = get_identifier (c_common_reswords[i].మాట);
      C_సమితి_RID_సంకేతం (id, c_common_reswords[i].rid);
      C_IS_RESERVED_మాట (id) = 1;
      ridpointers [(పూర్ణాంకం) c_common_reswords[i].rid] = id;
    }

  కొరకు (i = 0; i < అంకె_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      అక్షరం name[50];
      sprintf (name, "__int%d", int_n_దత్తాంశం[i].bitsize);
      id = get_identifier (name);
      C_సమితి_RID_సంకేతం (id, RID_మొదటి_INT_N + i);
      C_IS_RESERVED_మాట (id) = 1;

      sprintf (name, "__int%d__", int_n_దత్తాంశం[i].bitsize);
      id = get_identifier (name);
      C_సమితి_RID_సంకేతం (id, RID_మొదటి_INT_N + i);
      C_IS_RESERVED_మాట (id) = 1;
    }

  ఒకవేళ (flag_openmp)
    {
      id = get_identifier ("omp_all_memory");
      C_సమితి_RID_సంకేతం (id, RID_OMP_ALL_జ్ఞాపకం);
      C_IS_RESERVED_మాట (id) = 1;
      ridpointers [RID_OMP_ALL_జ్ఞాపకం] = id;
    }
}

/* A parser structure recording information about the state and
   context of parsing.  Includes lexer information with up to two
   tokens of look-ahead; more are not needed for C.  */
నిర్మాణం GTY(()) c_parser {
  /* The look-ahead tokens.  */
  c_token * GTY((skip)) టోకెన్లు;
  /* Buffer for look-ahead tokens.  */
  c_token టోకెన్లు_buf[4];
  /* How many look-ahead tokens are available (0 - 4, or
     more if parsing from pre-lexed tokens).  */
  గుర్తులేని పూర్ణాంకం టోకెన్లు_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_టోకెన్లు;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  గుర్తులేని పూర్ణాంకం raw_టోకెన్లు_వాడిన;
  /* True if a syntax error is being recovered from; false otherwise.
     c_parser_error sets this flag.  It should clear this flag when
     enough tokens have been consumed to recover from the error.  */
  తార్కిక error : 1;
  /* True if we're processing a pragma, and shouldn't automatically
     consume CPP_PRAGMA_EOL.  */
  తార్కిక లోపల_pragma : 1;
  /* True if we're parsing the outermost block of an if statement.  */
  తార్కిక లోపల_if_ఖండం : 1;
  /* True if we want to lex a translated, joined string (for an
     initial #pragma pch_preprocess).  Otherwise the parser is
     responsible for concatenating strings and translating to the
     execution character set as needed.  */
  తార్కిక lex_joined_string : 1;
  /* True if, when the parser is concatenating string literals, it
     should translate them to the execution character set (false
     inside attributes).  */
  తార్కిక translate_అక్షరశ్రేణులు_p : 1;

  /* Objective-C specific parser/lexer information.  */

  /* True if we are in a context where the Objective-C "PQ" keywords
     are considered keywords.  */
  తార్కిక objc_pq_context : 1;
  /* True if we are parsing a (potential) Objective-C foreach
     statement.  This is set to true after we parsed 'for (' and while
     we wait for 'in' or ';' to decide if it's a standard C for loop or an
     Objective-C foreach loop.  */
  తార్కిక objc_could_be_foreach_context : 1;
  /* The following flag is needed to contextualize Objective-C lexical
     analysis.  In some cases (e.g., 'int NSObject;'), it is
     undesirable to bind an identifier to an Objective-C class, even
     if a class with that name exists.  */
  తార్కిక objc_need_raw_identifier : 1;
  /* Nonzero if we're processing a __transaction statement.  The value
     is 1 | TM_STMT_ATTR_*.  */
  గుర్తులేని పూర్ణాంకం లోపల_transaction : 4;
  /* True if we are in a context where the Objective-C "Property attribute"
     keywords are valid.  */
  తార్కిక objc_property_attr_context : 1;

  /* Whether we have just seen/constructed a string-literal.  Set when
     returning a string-literal from c_parser_string_literal.  Reset
     in consume_token.  Useful when we get a parse error and see an
     unknown token, which could have been a string-literal constant
     macro.  */
  తార్కిక చూసిన_string_literal : 1;

  /* TRUE if omp::directive, omp::decl or omp::sequence attributes may not
     appear.  */
  తార్కిక omp_attrs_forbidden_p : 1;

  /* Location of the last consumed token.  */
  location_t చివరి_token_location;

  /* Holds state for parsing collapsed OMP_FOR loops.  Managed by
     c_parser_omp_for_loop.  */
  నిర్మాణం omp_for_parse_దత్తాంశం * GTY((skip)) omp_for_parse_state;

  /* If we're in the context of OpenMP directives written as C23
     attributes turned into pragma, the tokens field is temporarily
     redirected.  This holds data needed to restore state afterwards.
     It's NULL otherwise.  */
  నిర్మాణం omp_attribute_pragma_state *లోపల_omp_attribute_pragma;

  /* Set for omp::decl attribute parsing to the decl to which it
     appertains.  */
  వృక్షం లోపల_omp_decl_attribute;

  /* Non-null only when parsing the body of an OpenMP metadirective.
     Managed by c_parser_omp_metadirective.  */
  నిర్మాణం omp_metadirective_parse_దత్తాంశం * GTY((skip))
    omp_metadirective_state;
};

/* Holds data needed to restore the token stream to its previous state
   after parsing an OpenMP attribute-syntax pragma.  */
నిర్మాణం GTY(()) omp_attribute_pragma_state
{
  vec<c_token, va_gc> *token_vec;
  c_token * GTY((skip)) save_టోకెన్లు;
  గుర్తులేని పూర్ణాంకం save_టోకెన్లు_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
నిర్మాణం GTY(()) omp_begin_declare_variant_map_నమోదు {
  వృక్షం variant;		/* The variant decl.  */
  వృక్షం id;		/* Name of base function.  */
  వృక్షం ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_నమోదు, va_gc> *omp_begin_declare_variant_map;

స్థిర వృక్షం omp_ప్రారంభం_variant_function (c_declarator *, వృక్షం);
స్థిర శూన్య omp_ముగింపు_variant_function (వృక్షం, వృక్షం, వృక్షం);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_టోకెన్లు_buf (c_parser *parser, గుర్తులేని n)
{
  తిరిగి &parser->టోకెన్లు_buf[n];
}

/* Return the error state of PARSER.  */

తార్కిక
c_parser_error (c_parser *parser)
{
  తిరిగి parser->error;
}

/* Set the error state of PARSER to ERR.  */

శూన్య
c_parser_సమితి_error (c_parser *parser, తార్కిక err)
{
  parser->error = err;
}


/* The actual parser and external interface.  ??? Does this need to be
   garbage-collected?  */

స్థిర GTY (()) c_parser *the_parser;

/* Read in and lex a single token, storing it in *TOKEN.  If RAW,
   context-sensitive postprocessing of the token is not done.  */

స్థిర శూన్య
c_lex_one_token (c_parser *parser, c_token *token, తార్కిక raw = అబద్ధం)
{
  timevar_నెట్టు (TV_LEX);

  ఒకవేళ (raw || vec_సురక్షిత_నిడివి (parser->raw_టోకెన్లు) == 0)
    {
      token->type = c_lex_with_flags (&token->విలువ, &token->location,
				      &token->flags,
				      (parser->lex_joined_string
				       ? 0 : C_LEX_STRING_NO_JOIN));
      token->id_రకం = C_ID_NONE;
      token->keyword = RID_MAX;
      token->pragma_రకం = PRAGMA_NONE;
    }
  లేకపోతే
    {
      /* Use a token previously lexed as a raw look-ahead token, and
	 complete the processing on it.  */
      *token = (*parser->raw_టోకెన్లు)[parser->raw_టోకెన్లు_వాడిన];
      ++parser->raw_టోకెన్లు_వాడిన;
      ఒకవేళ (parser->raw_టోకెన్లు_వాడిన == vec_సురక్షిత_నిడివి (parser->raw_టోకెన్లు))
	{
	  vec_free (parser->raw_టోకెన్లు);
	  parser->raw_టోకెన్లు_వాడిన = 0;
	}
    }

  ఒకవేళ (raw)
    వెళ్ళు బహిర్గతం;

  ఎంపిక (token->type)
    {
    స్థితి CPP_NAME:
      {
	వృక్షం decl;

	తార్కిక objc_force_identifier = parser->objc_need_raw_identifier;
	ఒకవేళ (c_dialect_objc ())
	  parser->objc_need_raw_identifier = అబద్ధం;

	ఒకవేళ (C_IS_RESERVED_మాట (token->విలువ))
	  {
	    గణన rid rid_సంకేతం = C_RID_సంకేతం (token->విలువ);

	    ఒకవేళ (rid_సంకేతం == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->విలువ);
	      }
	    లేకపోతే ఒకవేళ (rid_సంకేతం >= RID_మొదటి_ADDR_SPACE
		     && rid_సంకేతం <= RID_చివరి_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_సంకేతం - RID_మొదటి_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_రకం = C_ID_ADDRSPACE;
		token->keyword = rid_సంకేతం;
		ఆపు;
	      }
	    లేకపోతే ఒకవేళ (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_సంకేతం))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		ఒకవేళ (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_సంకేతం;
		    ఆపు;
		  }
		లేకపోతే ఒకవేళ (parser->objc_could_be_foreach_context
			 && rid_సంకేతం == RID_లోపల)
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
		    token->keyword = rid_సంకేతం;
		    ఆపు;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    లేకపోతే ఒకవేళ (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_సంకేతం))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		ఒకవేళ (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_సంకేతం;
		    ఆపు;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    లేకపోతే ఒకవేళ (c_dialect_objc ()
		     && (OBJC_IS_AT_KEYWORD (rid_సంకేతం)
			 || OBJC_IS_CXX_KEYWORD (rid_సంకేతం)))
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
	    లేకపోతే
	      {
		token->type = CPP_KEYWORD;
		token->keyword = rid_సంకేతం;
		ఆపు;
	      }
	  }

	decl = lookup_name (token->విలువ);
	ఒకవేళ (decl)
	  {
	    ఒకవేళ (వృక్షం_సంకేతం (decl) == TYPE_DECL)
	      {
		token->id_రకం = C_ID_TYPENAME;
		ఆపు;
	      }
	  }
	లేకపోతే ఒకవేళ (c_dialect_objc ())
	  {
	    వృక్షం objc_interface_decl = objc_is_class_name (token->విలువ);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    ఒకవేళ (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->విలువ = objc_interface_decl;
		token->id_రకం = C_ID_CLASSNAME;
		ఆపు;
	      }
	  }
        token->id_రకం = C_ID_ID;
      }
      ఆపు;
    స్థితి CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      ఎంపిక (C_RID_సంకేతం (token->విలువ))
	{
	  /* Replace 'class' with '@class', 'private' with '@private',
	     etc.  This prevents confusion with the C++ keyword
	     'class', and makes the tokens consistent with other
	     Objective-C 'AT' keywords.  For example '@class' is
	     reported as RID_AT_CLASS which is consistent with
	     '@synchronized', which is reported as
	     RID_AT_SYNCHRONIZED.
	  */
	స్థితి RID_CLASS:     token->keyword = RID_AT_CLASS; ఆపు;
	స్థితి RID_వ్యక్తిగత:   token->keyword = RID_AT_వ్యక్తిగత; ఆపు;
	స్థితి RID_PROTECTED: token->keyword = RID_AT_PROTECTED; ఆపు;
	స్థితి RID_ప్రజా:    token->keyword = RID_AT_ప్రజా; ఆపు;
	స్థితి RID_THROW:     token->keyword = RID_AT_THROW; ఆపు;
	స్థితి RID_TRY:       token->keyword = RID_AT_TRY; ఆపు;
	స్థితి RID_CATCH:     token->keyword = RID_AT_CATCH; ఆపు;
	స్థితి RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; ఆపు;
	అప్రమేయ:            token->keyword = C_RID_సంకేతం (token->విలువ);
	}
      ఆపు;
    స్థితి CPP_COLON:
    స్థితి CPP_COMMA:
    స్థితి CPP_CLOSE_PAREN:
    స్థితి CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      ఒకవేళ (c_dialect_objc ())
	parser->objc_need_raw_identifier = అబద్ధం;
      ఆపు;
    స్థితి CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_రకం = (గణన pragma_రకం) వృక్షం_INT_CST_దిగువ (token->విలువ);
      token->విలువ = ఖాళీ;
      ఆపు;
    అప్రమేయ:
      ఆపు;
    }
 బహిర్గతం:
  timevar_తీయి (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  ఒకవేళ (parser->టోకెన్లు_avail == 0)
    {
      c_lex_one_token (parser, &parser->టోకెన్లు[0]);
      parser->టోకెన్లు_avail = 1;
    }
  తిరిగి &parser->టోకెన్లు[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  ఒకవేళ (parser->టోకెన్లు_avail >= 2)
    తిరిగి &parser->టోకెన్లు[1];
  gcc_assert (parser->టోకెన్లు_avail == 1);
  gcc_assert (parser->టోకెన్లు[0].type != CPP_EOF);
  gcc_assert (parser->టోకెన్లు[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->టోకెన్లు[1]);
  parser->టోకెన్లు_avail = 2;
  తిరిగి &parser->టోకెన్లు[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, గుర్తులేని పూర్ణాంకం n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  ఒకవేళ (parser->టోకెన్లు_avail >= n)
    తిరిగి &parser->టోకెన్లు[n - 1];
  gcc_assert (parser->టోకెన్లు_avail == n - 1);
  c_lex_one_token (parser, &parser->టోకెన్లు[n - 1]);
  parser->టోకెన్లు_avail = n;
  తిరిగి &parser->టోకెన్లు[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, గుర్తులేని పూర్ణాంకం n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  ఒకవేళ (parser->టోకెన్లు_avail >= n)
    తిరిగి &parser->టోకెన్లు[n - 1];
  గుర్తులేని పూర్ణాంకం raw_len = vec_సురక్షిత_నిడివి (parser->raw_టోకెన్లు);
  గుర్తులేని పూర్ణాంకం raw_avail
    = parser->టోకెన్లు_avail + raw_len - parser->raw_టోకెన్లు_వాడిన;
  gcc_assert (raw_avail >= n - 1);
  ఒకవేళ (raw_avail >= n)
    తిరిగి &(*parser->raw_టోకెన్లు)[parser->raw_టోకెన్లు_వాడిన
				  + n - 1 - parser->టోకెన్లు_avail];
  vec_సురక్షిత_reserve (parser->raw_టోకెన్లు, 1);
  parser->raw_టోకెన్లు->శీఘ్ర_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_టోకెన్లు)[raw_len], నిజం);
  తిరిగి &(*parser->raw_టోకెన్లు)[raw_len];
}

తార్కిక
c_keyword_starts_typename (గణన rid keyword)
{
  ఎంపిక (keyword)
    {
    స్థితి RID_UNSIGNED:
    స్థితి RID_LONG:
    స్థితి RID_SHORT:
    స్థితి RID_SIGNED:
    స్థితి RID_COMPLEX:
    స్థితి RID_INT:
    స్థితి RID_CHAR:
    స్థితి RID_FLOAT:
    స్థితి RID_DOUBLE:
    స్థితి RID_VOID:
    స్థితి RID_DFLOAT32:
    స్థితి RID_DFLOAT64:
    స్థితి RID_DFLOAT128:
    స్థితి RID_DFLOAT64X:
    CASE_RID_FLOATN_NX:
    స్థితి RID_BOOL:
    స్థితి RID_BITINT:
    స్థితి RID_ENUM:
    స్థితి RID_STRUCT:
    స్థితి RID_UNION:
    స్థితి RID_TYPEOF:
    స్థితి RID_TYPEOF_UNQUAL:
    స్థితి RID_CONST:
    స్థితి RID_ATOMIC:
    స్థితి RID_VOLATILE:
    స్థితి RID_RESTRICT:
    స్థితి RID_ATTRIBUTE:
    స్థితి RID_FRACT:
    స్థితి RID_ACCUM:
    స్థితి RID_SAT:
    స్థితి RID_AUTO_TYPE:
    స్థితి RID_ALIGNAS:
      తిరిగి నిజం;
    అప్రమేయ:
      ఒకవేళ (keyword >= RID_మొదటి_INT_N
	  && keyword < RID_మొదటి_INT_N + అంకె_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_మొదటి_INT_N])
	తిరిగి నిజం;
      తిరిగి అబద్ధం;
    }
}

/* Return true if TOKEN can start a type name,
   false otherwise.  */
తార్కిక
c_token_starts_typename (c_token *token)
{
  ఎంపిక (token->type)
    {
    స్థితి CPP_NAME:
      ఎంపిక (token->id_రకం)
	{
	స్థితి C_ID_ID:
	  తిరిగి అబద్ధం;
	స్థితి C_ID_ADDRSPACE:
	  తిరిగి నిజం;
	స్థితి C_ID_TYPENAME:
	  తిరిగి నిజం;
	స్థితి C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  తిరిగి నిజం;
	అప్రమేయ:
	  gcc_unreachable ();
	}
    స్థితి CPP_KEYWORD:
      తిరిగి c_keyword_starts_typename (token->keyword);
    స్థితి CPP_LESS:
      ఒకవేళ (c_dialect_objc ())
	తిరిగి నిజం;
      తిరిగి అబద్ధం;
    అప్రమేయ:
      తిరిగి అబద్ధం;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

స్థిర అంతఃవరుస తార్కిక
c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_typename (c_parser *parser, గణన c_lookahead_రకం la,
				     గుర్తులేని పూర్ణాంకం n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  ఒకవేళ (c_token_starts_typename (token))
    తిరిగి నిజం;

  /* Try a bit harder to detect an unknown typename.  */
  ఒకవేళ (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_రకం == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->విలువ))
    తిరిగి నిజం;

  తిరిగి అబద్ధం;
}

/* Return true if TOKEN, after an open parenthesis, can start a
   compound literal (either a storage class specifier allowed in that
   context, or a type name), false otherwise.  */
స్థిర తార్కిక
c_token_starts_compound_literal (c_token *token)
{
  ఎంపిక (token->type)
    {
    స్థితి CPP_KEYWORD:
      ఎంపిక (token->keyword)
	{
	స్థితి RID_CONSTEXPR:
	స్థితి RID_రిజిస్టరు:
	స్థితి RID_STATIC:
	స్థితి RID_THREAD:
	  తిరిగి నిజం;
	అప్రమేయ:
	  ఆపు;
	}
      /* Fall through.  */
    అప్రమేయ:
      తిరిగి c_token_starts_typename (token);
    }
}

/* Return true if TOKEN is a type qualifier, false otherwise.  */
స్థిర తార్కిక
c_token_is_qualifier (c_token *token)
{
  ఎంపిక (token->type)
    {
    స్థితి CPP_NAME:
      ఎంపిక (token->id_రకం)
	{
	స్థితి C_ID_ADDRSPACE:
	  తిరిగి నిజం;
	అప్రమేయ:
	  తిరిగి అబద్ధం;
	}
    స్థితి CPP_KEYWORD:
      ఎంపిక (token->keyword)
	{
	స్థితి RID_CONST:
	స్థితి RID_VOLATILE:
	స్థితి RID_RESTRICT:
	స్థితి RID_ATTRIBUTE:
	స్థితి RID_ATOMIC:
	  తిరిగి నిజం;
	అప్రమేయ:
	  తిరిగి అబద్ధం;
	}
    స్థితి CPP_LESS:
      తిరిగి అబద్ధం;
    అప్రమేయ:
      gcc_unreachable ();
    }
}

/* Return true if the next token from PARSER is a type qualifier,
   false otherwise.  */
స్థిర అంతఃవరుస తార్కిక
c_parser_తదుపరి_token_is_qualifier (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  తిరిగి c_token_is_qualifier (token);
}

/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes), false otherwise.  */
స్థిర తార్కిక
c_token_starts_declspecs (c_token *token)
{
  ఎంపిక (token->type)
    {
    స్థితి CPP_NAME:
      ఎంపిక (token->id_రకం)
	{
	స్థితి C_ID_ID:
	  తిరిగి అబద్ధం;
	స్థితి C_ID_ADDRSPACE:
	  తిరిగి నిజం;
	స్థితి C_ID_TYPENAME:
	  తిరిగి నిజం;
	స్థితి C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  తిరిగి నిజం;
	అప్రమేయ:
	  gcc_unreachable ();
	}
    స్థితి CPP_KEYWORD:
      ఎంపిక (token->keyword)
	{
	స్థితి RID_STATIC:
	స్థితి RID_EXTERN:
	స్థితి RID_రిజిస్టరు:
	స్థితి RID_TYPEDEF:
	స్థితి RID_INLINE:
	స్థితి RID_NORETURN:
	స్థితి RID_AUTO:
	స్థితి RID_THREAD:
	స్థితి RID_UNSIGNED:
	స్థితి RID_LONG:
	స్థితి RID_SHORT:
	స్థితి RID_SIGNED:
	స్థితి RID_COMPLEX:
	స్థితి RID_INT:
	స్థితి RID_CHAR:
	స్థితి RID_FLOAT:
	స్థితి RID_DOUBLE:
	స్థితి RID_VOID:
	స్థితి RID_DFLOAT32:
	స్థితి RID_DFLOAT64:
	స్థితి RID_DFLOAT128:
	స్థితి RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	స్థితి RID_BOOL:
	స్థితి RID_BITINT:
	స్థితి RID_ENUM:
	స్థితి RID_STRUCT:
	స్థితి RID_UNION:
	స్థితి RID_TYPEOF:
	స్థితి RID_TYPEOF_UNQUAL:
	స్థితి RID_CONST:
	స్థితి RID_VOLATILE:
	స్థితి RID_RESTRICT:
	స్థితి RID_ATTRIBUTE:
	స్థితి RID_FRACT:
	స్థితి RID_ACCUM:
	స్థితి RID_SAT:
	స్థితి RID_ALIGNAS:
	స్థితి RID_ATOMIC:
	స్థితి RID_AUTO_TYPE:
	స్థితి RID_CONSTEXPR:
	  తిరిగి నిజం;
	అప్రమేయ:
	  ఒకవేళ (token->keyword >= RID_మొదటి_INT_N
	      && token->keyword < RID_మొదటి_INT_N + అంకె_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_మొదటి_INT_N])
	    తిరిగి నిజం;
	  తిరిగి అబద్ధం;
	}
    స్థితి CPP_LESS:
      ఒకవేళ (c_dialect_objc ())
	తిరిగి నిజం;
      తిరిగి అబద్ధం;
    అప్రమేయ:
      తిరిగి అబద్ధం;
    }
}


/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes) or a static assertion, false
   otherwise.  */
స్థిర తార్కిక
c_token_starts_declaration (c_token *token)
{
  ఒకవేళ (c_token_starts_declspecs (token)
      || token->keyword == RID_STATIC_ASSERT)
    తిరిగి నిజం;
  లేకపోతే
    తిరిగి అబద్ధం;
}

/* Return true if the next token from PARSER can start declaration
   specifiers (not including standard attributes), false
   otherwise.  */
తార్కిక
c_parser_తదుపరి_token_starts_declspecs (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);

  /* In Objective-C, a classname normally starts a declspecs unless it
     is immediately followed by a dot.  In that case, it is the
     Objective-C 2.0 "dot-syntax" for class objects, ie, calls the
     setter/getter on the class.  c_token_starts_declspecs() can't
     differentiate between the two cases because it only checks the
     current token, so we have a special check here.  */
  ఒకవేళ (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_రకం == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    తిరిగి అబద్ధం;

  తిరిగి c_token_starts_declspecs (token);
}

స్థిర తార్కిక c_parser_check_సమతుల్య_raw_token_sequence (c_parser *,
							గుర్తులేని పూర్ణాంకం *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
తార్కిక
c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_declaration (c_parser *parser, గుర్తులేని పూర్ణాంకం n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  ఒకవేళ (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_రకం == C_ID_CLASSNAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_DOT)
    తిరిగి అబద్ధం;

  /* Labels do not start declarations.  */
  ఒకవేళ (token->type == CPP_NAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_COLON)
    తిరిగి అబద్ధం;

  /* A static assertion is only a declaration if followed by a semicolon;
     otherwise, it may be an expression in C2Y.  */
  ఒకవేళ (token->keyword == RID_STATIC_ASSERT
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_PAREN)
    {
      n += 2;
      ఒకవేళ (!c_parser_check_సమతుల్య_raw_token_sequence (parser, &n)
	  || c_parser_peek_nth_token_raw (parser, n)->type != CPP_CLOSE_PAREN)
	/* Invalid static assertion syntax; treat as a declaration and report a
	   syntax error there.  */
	తిరిగి నిజం;
      తిరిగి c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  ఒకవేళ (c_token_starts_declaration (token))
    తిరిగి నిజం;

  ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_typename (parser, cla_nonabstract_decl, n))
    తిరిగి నిజం;

  తిరిగి అబద్ధం;
}

/* Consume the next token from PARSER.  */

శూన్య
c_parser_consume_token (c_parser *parser)
{
  gcc_assert (parser->టోకెన్లు_avail >= 1);
  gcc_assert (parser->టోకెన్లు[0].type != CPP_EOF);
  gcc_assert (!parser->లోపల_pragma || parser->టోకెన్లు[0].type != CPP_PRAGMA_EOL);
  /* CPP_PRAGMA should not show up here except if there was an error or inside
     another pragma.  */
  gcc_assert (parser->లోపల_pragma
	      || parser->error
	      || parser->టోకెన్లు[0].type != CPP_PRAGMA);
  parser->చివరి_token_location = parser->టోకెన్లు[0].location;
  ఒకవేళ (parser->టోకెన్లు != &parser->టోకెన్లు_buf[0])
    parser->టోకెన్లు++;
  లేకపోతే ఒకవేళ (parser->టోకెన్లు_avail >= 2)
    {
      parser->టోకెన్లు[0] = parser->టోకెన్లు[1];
      ఒకవేళ (parser->టోకెన్లు_avail >= 3)
        {
          parser->టోకెన్లు[1] = parser->టోకెన్లు[2];
          ఒకవేళ (parser->టోకెన్లు_avail >= 4)
            parser->టోకెన్లు[2] = parser->టోకెన్లు[3];
        }
    }
  parser->టోకెన్లు_avail--;
  parser->చూసిన_string_literal = అబద్ధం;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

స్థిర శూన్య
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->లోపల_pragma);
  gcc_assert (parser->టోకెన్లు_avail >= 1);
  gcc_assert (parser->టోకెన్లు[0].type == CPP_PRAGMA);
  ఒకవేళ (parser->టోకెన్లు != &parser->టోకెన్లు_buf[0])
    parser->టోకెన్లు++;
  లేకపోతే ఒకవేళ (parser->టోకెన్లు_avail >= 2)
    {
      parser->టోకెన్లు[0] = parser->టోకెన్లు[1];
      ఒకవేళ (parser->టోకెన్లు_avail >= 3)
	parser->టోకెన్లు[1] = parser->టోకెన్లు[2];
    }
  parser->టోకెన్లు_avail--;
  parser->లోపల_pragma = నిజం;
}

/* Update the global input_location from TOKEN.  */
స్థిర అంతఃవరుస శూన్య
c_parser_సమితి_ఆధారం_position_from_token (c_token *token)
{
  ఒకవేళ (token->type != CPP_EOF)
    {
      ఆదానం_location = token->location;
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

స్థిర తార్కిక
c_parser_peek_conflict_marker (c_parser *parser, గణన cpp_ttype tok1_రకం,
			       location_t *బహిర్గతం_loc)
{
  c_token *token2 = c_parser_peek_2nd_token (parser);
  ఒకవేళ (token2->type != tok1_రకం)
    తిరిగి అబద్ధం;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  ఒకవేళ (token3->type != tok1_రకం)
    తిరిగి అబద్ధం;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  ఒకవేళ (token4->type != conflict_marker_get_final_tok_రకం (tok1_రకం))
    తిరిగి అబద్ధం;

  /* It must be at the start of the line.  */
  location_t ప్రారంభం_loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (LOCATION_స్తంభం (ప్రారంభం_loc) != 1)
    తిరిగి అబద్ధం;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t ముగింపు_loc = get_ముగింపు (token4->location);
  *బహిర్గతం_loc = make_location (ప్రారంభం_loc, ప్రారంభం_loc, ముగింపు_loc);

  తిరిగి నిజం;
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

స్థిర తార్కిక
c_parser_error_richloc (c_parser *parser, స్థిరరాశి అక్షరం *gmsgid,
			rich_location *richloc)
{
  c_token *token = c_parser_peek_token (parser);
  ఒకవేళ (parser->error)
    తిరిగి అబద్ధం;
  parser->error = నిజం;
  ఒకవేళ (!gmsgid)
    తిరిగి అబద్ధం;

  /* If this is actually a conflict marker, report it as such.  */
  ఒకవేళ (token->type == CPP_LSHIFT
      || token->type == CPP_RSHIFT
      || token->type == CPP_EQ_EQ)
    {
      location_t loc;
      ఒకవేళ (c_parser_peek_conflict_marker (parser, token->type, &loc))
	{
	  error_at (loc, "version control conflict marker in file");
	  తిరిగి నిజం;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_సమూహం d;
  name_hint h;
  ఒకవేళ (parser->చూసిన_string_literal && token->type == CPP_NAME)
    {
      వృక్షం name = token->విలువ;
      స్థిరరాశి అక్షరం *token_name = IDENTIFIER_సూచిక (name);
      స్థిరరాశి అక్షరం *శీర్షిక_hint
	= get_c_stdlib_శీర్షిక_for_string_macro_name (token_name);
      ఒకవేళ (శీర్షిక_hint != ఖాళీ)
	h = name_hint (శూన్యసూచిక,
		       std::make_unique<suggest_missing_శీర్షిక>
			 (token->location,
			  token_name,
			  శీర్షిక_hint));
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
		 token->విలువ, /*flags=*/0, richloc);
  తిరిగి నిజం;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

తార్కిక
c_parser_error (c_parser *parser, స్థిరరాశి అక్షరం *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_సమితి_ఆధారం_position_from_token (token);
  rich_location richloc (పంక్తి_పట్టిక, ఆదానం_location);
  తిరిగి c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

మూస <రకం_పేరు traits_t>
తరగతి token_pair
{
 బహిరంగ:
  /* token_pair's ctor.  */
  token_pair () : m_open_loc (UNKNOWN_LOCATION) {}

  /* If the next token is the opening symbol for this pair, consume it and
     return true.
     Otherwise, issue an error and return false.
     In either case, record the location of the opening token.  */

  తార్కిక require_open (c_parser *parser)
  {
    c_token *token = c_parser_peek_token (parser);
    ఒకవేళ (token)
      m_open_loc = token->location;

    తిరిగి c_parser_require (parser, traits_t::open_token_type,
			     traits_t::open_gmsgid);
  }

  /* Consume the next token from PARSER, recording its location as
     that of the opening token within the pair.  */

  శూన్య consume_open (c_parser *parser)
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

  తార్కిక require_close (c_parser *parser) స్థిరరాశి
  {
    తిరిగి c_parser_require (parser, traits_t::close_token_type,
			     traits_t::close_gmsgid, m_open_loc);
  }

  /* Like token_pair::require_close, except that tokens will be skipped
     until the desired token is found.  An error message is still produced
     if the next token is not as expected.  */

  శూన్య skip_until_దొరికింది_close (c_parser *parser) స్థిరరాశి
  {
    c_parser_skip_until_దొరికింది (parser, traits_t::close_token_type,
			       traits_t::close_gmsgid, m_open_loc);
  }

 అంతరంగ:
  location_t m_open_loc;
};

/* Traits for token_pair<T> for tracking matching pairs of parentheses.  */

నిర్మాణం matching_paren_traits
{
  స్థిర స్థిరరాశి గణన cpp_ttype open_token_type = CPP_OPEN_PAREN;
  స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి open_gmsgid;
  స్థిర స్థిరరాశి గణన cpp_ttype close_token_type = CPP_CLOSE_PAREN;
  స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి close_gmsgid;
};

స్థిరరాశి అక్షరం * స్థిరరాశి matching_paren_traits::open_gmsgid = "expected %<(%>";
స్థిరరాశి అక్షరం * స్థిరరాశి matching_paren_traits::close_gmsgid = "expected %<)%>";

/* "matching_parens" is a token_pair<T> class for tracking matching
   pairs of parentheses.  */

రకనిర్వచనం token_pair<matching_paren_traits> matching_parens;

/* Traits for token_pair<T> for tracking matching pairs of braces.  */

నిర్మాణం matching_brace_traits
{
  స్థిర స్థిరరాశి గణన cpp_ttype open_token_type = CPP_OPEN_BRACE;
  స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి open_gmsgid;
  స్థిర స్థిరరాశి గణన cpp_ttype close_token_type = CPP_CLOSE_BRACE;
  స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి close_gmsgid;
};

స్థిరరాశి అక్షరం * స్థిరరాశి matching_brace_traits::open_gmsgid = "expected %<{%>";
స్థిరరాశి అక్షరం * స్థిరరాశి matching_brace_traits::close_gmsgid = "expected %<}%>";

/* "matching_braces" is a token_pair<T> class for tracking matching
   pairs of braces.  */

రకనిర్వచనం token_pair<matching_brace_traits> matching_braces;

/* Get a description of the matching symbol to TYPE e.g. "(" for
   CPP_CLOSE_PAREN.  */

స్థిర స్థిరరాశి అక్షరం *
get_matching_చిహ్నం (గణన cpp_ttype type)
{
  ఎంపిక (type)
    {
    అప్రమేయ:
      gcc_unreachable ();
    స్థితి CPP_CLOSE_PAREN:
      తిరిగి "(";
    స్థితి CPP_CLOSE_BRACE:
      తిరిగి "{";
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

తార్కిక
c_parser_require (c_parser *parser,
		  గణన cpp_ttype type,
		  స్థిరరాశి అక్షరం *msgid,
		  location_t matching_location,
		  తార్కిక type_is_unique)
{
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      తిరిగి నిజం;
    }
  లేకపోతే
    {
      location_t తదుపరి_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (తదుపరి_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      ఒకవేళ (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->చివరి_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      తార్కిక added_matching_location = అబద్ధం;
      ఒకవేళ (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.కూడు_location_if_nearby (*global_dc, matching_location);

      ఒకవేళ (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	ఒకవేళ (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_చిహ్నం (type));

      తిరిగి అబద్ధం;
    }
}

/* If the next token is the indicated keyword, consume it.  Otherwise,
   issue the error MSGID.  Returns true if found, false otherwise.  */

స్థిర తార్కిక
c_parser_require_keyword (c_parser *parser,
			  గణన rid keyword,
			  స్థిరరాశి అక్షరం *msgid)
{
  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      తిరిగి నిజం;
    }
  లేకపోతే
    {
      c_parser_error (parser, msgid);
      తిరిగి అబద్ధం;
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

శూన్య
c_parser_skip_until_దొరికింది (c_parser *parser,
			   గణన cpp_ttype type,
			   స్థిరరాశి అక్షరం *msgid,
			   location_t matching_location)
{
  గుర్తులేని nesting_లోతు = 0;

  ఒకవేళ (c_parser_require (parser, type, msgid, matching_location))
    {
      ఒకవేళ (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->లోపల_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ఒకవేళ (token->type == CPP_EOF)
	    {
	      parser->టోకెన్లు = parser->లోపల_omp_attribute_pragma->save_టోకెన్లు;
	      parser->టోకెన్లు_avail
		= parser->లోపల_omp_attribute_pragma->save_టోకెన్లు_avail;
	      parser->లోపల_omp_attribute_pragma = ఖాళీ;
	    }
	}
      తిరిగి;
    }

  /* Skip tokens until the desired token is found.  */
  అయితే (నిజం)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      ఒకవేళ (token->type == type && !nesting_లోతు)
	{
	  c_parser_consume_token (parser);
	  ఒకవేళ (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->లోపల_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      ఒకవేళ (token->type == CPP_EOF)
		{
		  parser->టోకెన్లు = parser->లోపల_omp_attribute_pragma->save_టోకెన్లు;
		  parser->టోకెన్లు_avail
		    = parser->లోపల_omp_attribute_pragma->save_టోకెన్లు_avail;
		  parser->లోపల_omp_attribute_pragma = ఖాళీ;
		}
	    }
	  ఆపు;
	}

      /* If we've run out of tokens, stop.  */
      ఒకవేళ (token->type == CPP_EOF)
	తిరిగి;
      ఒకవేళ (token->type == CPP_PRAGMA_EOL && parser->లోపల_pragma)
	తిరిగి;
      ఒకవేళ (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_వర్గం)
	++nesting_లోతు;
      లేకపోతే ఒకవేళ (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_వర్గం)
	{
	  ఒకవేళ (nesting_లోతు-- == 0)
	    ఆపు;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = అబద్ధం;
}

/* Skip tokens until the end of a parameter is found, but do not
   consume the comma, semicolon or closing delimiter.  */

స్థిర శూన్య
c_parser_skip_గమ్యం_చివర_యొక్క_parameter (c_parser *parser)
{
  గుర్తులేని nesting_లోతు = 0;

  అయితే (నిజం)
    {
      c_token *token = c_parser_peek_token (parser);
      ఒకవేళ ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_లోతు)
	ఆపు;
      /* If we've run out of tokens, stop.  */
      ఒకవేళ (token->type == CPP_EOF)
	తిరిగి;
      ఒకవేళ (token->type == CPP_PRAGMA_EOL && parser->లోపల_pragma)
	తిరిగి;
      ఒకవేళ (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_వర్గం)
	++nesting_లోతు;
      లేకపోతే ఒకవేళ (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_వర్గం)
	{
	  ఒకవేళ (nesting_లోతు-- == 0)
	    ఆపు;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = అబద్ధం;
}

/* Skip tokens until a non-nested closing curly brace is the next
   token, or there are no more tokens. Return true in the first case,
   false otherwise.  */

స్థిర తార్కిక
c_parser_skip_గమ్యం_closing_brace (c_parser *parser)
{
  గుర్తులేని nesting_లోతు = 0;

  అయితే (నిజం)
    {
      c_token *token = c_parser_peek_token (parser);

      ఎంపిక (token->type)
	{
	స్థితి CPP_PRAGMA_EOL:
	  ఒకవేళ (!parser->లోపల_pragma)
	    ఆపు;
	  /* FALLTHRU */
	స్థితి CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  తిరిగి అబద్ధం;

	స్థితి CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  ఒకవేళ (nesting_లోతు-- == 0)
	    తిరిగి నిజం;
	  ఆపు;

	స్థితి CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_లోతు;
	  ఆపు;

	అప్రమేయ:
	  ఆపు;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Expect to be at the end of the pragma directive and consume an
   end of line marker.  */

స్థిర శూన్య
c_parser_skip_గమ్యం_pragma_eol (c_parser *parser, తార్కిక error_if_not_eol = నిజం)
{
  gcc_assert (parser->లోపల_pragma);
  parser->లోపల_pragma = అబద్ధం;

  ఒకవేళ (error_if_not_eol && c_parser_peek_token (parser)->type != CPP_PRAGMA_EOL)
    c_parser_error (parser, "expected end of line");

  cpp_ttype token_type;
  చేయి
    {
      c_token *token = c_parser_peek_token (parser);
      token_type = token->type;
      ఒకవేళ (token_type == CPP_EOF)
	ఆపు;
      c_parser_consume_token (parser);
    }
  అయితే (token_type != CPP_PRAGMA_EOL);

  ఒకవేళ (parser->లోపల_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      ఒకవేళ (token->type == CPP_EOF)
	{
	  parser->టోకెన్లు = parser->లోపల_omp_attribute_pragma->save_టోకెన్లు;
	  parser->టోకెన్లు_avail
	    = parser->లోపల_omp_attribute_pragma->save_టోకెన్లు_avail;
	  parser->లోపల_omp_attribute_pragma = ఖాళీ;
	}
    }

  parser->error = అబద్ధం;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
స్థిర శూన్య
c_parser_skip_గమ్యం_pragma_omp_చివర_declare_variant (c_parser *parser)
{
  కొరకు (పూర్ణాంకం లోతు = 0; లోతు >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      ఎంపిక (token->type)
	{
	స్థితి CPP_PRAGMA_EOL:
	  ఒకవేళ (!parser->లోపల_pragma)
	    ఆపు;
	  /* FALLTHRU */
	స్థితి CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  తిరిగి;

	స్థితి CPP_PRAGMA:
	  ఒకవేళ ((token->pragma_రకం == PRAGMA_OMP_BEGIN
	       || token->pragma_రకం == PRAGMA_OMP_చివర)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      వృక్షం id1 = c_parser_peek_nth_token (parser, 2)->విలువ;
	      వృక్షం id2 = c_parser_peek_nth_token (parser, 3)->విలువ;
	      ఒకవేళ (strcmp (IDENTIFIER_సూచిక (id1), "declare") == 0
		  && strcmp (IDENTIFIER_సూచిక (id2), "variant") == 0)
		{
		  ఒకవేళ (token->pragma_రకం == PRAGMA_OMP_BEGIN)
		    లోతు++;
		  లేకపోతే
		    లోతు--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	  కొనసాగు;

	అప్రమేయ:
	  ఆపు;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Skip tokens until we have consumed an entire block, or until we
   have consumed a non-nested ';'.  */

స్థిర శూన్య
c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (c_parser *parser,
					    తార్కిక metadirective_p = అబద్ధం)
{
  గుర్తులేని nesting_లోతు = 0;
  పూర్ణాంకం bracket_లోతు = 0;
  తార్కిక save_error = parser->error;

  అయితే (నిజం)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      ఎంపిక (token->type)
	{
	స్థితి CPP_EOF:
	  తిరిగి;

	స్థితి CPP_PRAGMA_EOL:
	  ఒకవేళ (parser->లోపల_pragma)
	    తిరిగి;
	  ఆపు;

	స్థితి CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  ఒకవేళ (!nesting_లోతు && (!metadirective_p || bracket_లోతు <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      వెళ్ళు ముగిసిన;
	    }
	  ఆపు;

	స్థితి CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  ఒకవేళ ((nesting_లోతు == 0 || --nesting_లోతు == 0)
	      && (!metadirective_p || bracket_లోతు <= 0))
	    {
	      c_parser_consume_token (parser);
	      వెళ్ళు ముగిసిన;
	    }
	  ఆపు;

	స్థితి CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_లోతు;
	  ఆపు;

	స్థితి CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  ఒకవేళ (metadirective_p && nesting_లోతు == 0)
	    ++bracket_లోతు;
	  ఆపు;

	స్థితి CPP_CLOSE_PAREN:
	  ఒకవేళ (metadirective_p && nesting_లోతు == 0)
	    --bracket_లోతు;
	  ఆపు;

	స్థితి CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	  parser->error = save_error;
	  కొనసాగు;

	అప్రమేయ:
	  ఆపు;
	}

      c_parser_consume_token (parser);
    }

 ముగిసిన:
  parser->error = అబద్ధం;
}

/* CPP's options (initialized by c-opts.cc).  */
బాహ్య cpp_options *cpp_opts;

/* Save the warning flags which are controlled by __extension__.  */

స్థిర అంతఃవరుస పూర్ణాంకం
disable_extension_diagnostics (శూన్య)
{
  పూర్ణాంకం ret = (pedantic
	     | (warn_సూచిక_arith << 1)
	     | (warn_traditional << 2)
	     | (flag_iso << 3)
	     | (warn_long_long << 4)
	     | (warn_cxx_compat << 5)
	     | (warn_overlength_అక్షరశ్రేణులు << 6)
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
  warn_సూచిక_arith = 0;
  cpp_opts->cpp_warn_traditional = warn_traditional = 0;
  flag_iso = 0;
  cpp_opts->cpp_warn_long_long = warn_long_long = 0;
  warn_cxx_compat = 0;
  warn_overlength_అక్షరశ్రేణులు = 0;
  warn_c90_c99_compat = 0;
  warn_c99_c11_compat = 0;
  warn_c11_c23_compat = 0;
  warn_c23_c2y_compat = 0;
  తిరిగి ret;
}

/* Restore the warning flags which are controlled by __extension__.
   FLAGS is the return value from disable_extension_diagnostics.  */

స్థిర అంతఃవరుస శూన్య
restore_extension_diagnostics (పూర్ణాంకం flags)
{
  cpp_opts->cpp_pedantic = pedantic = flags & 1;
  warn_సూచిక_arith = (flags >> 1) & 1;
  cpp_opts->cpp_warn_traditional = warn_traditional = (flags >> 2) & 1;
  flag_iso = (flags >> 3) & 1;
  cpp_opts->cpp_warn_long_long = warn_long_long = (flags >> 4) & 1;
  warn_cxx_compat = (flags >> 5) & 1;
  warn_overlength_అక్షరశ్రేణులు = (flags >> 6) & 1;
  /* See above for why is this needed.  */
  warn_c90_c99_compat = (flags >> 7) & 1 ? 1 : ((flags >> 8) & 1 ? -1 : 0);
  warn_c99_c11_compat = (flags >> 9) & 1 ? 1 : ((flags >> 10) & 1 ? -1 : 0);
  warn_c11_c23_compat = (flags >> 11) & 1 ? 1 : ((flags >> 12) & 1 ? -1 : 0);
  warn_c23_c2y_compat = (flags >> 13) & 1 ? 1 : ((flags >> 14) & 1 ? -1 : 0);
}

/* Helper data structure for parsing #pragma acc routine.  */
నిర్మాణం oacc_routine_దత్తాంశం {
  తార్కిక error_చూసిన; /* Set if error has been reported.  */
  తార్కిక fndecl_చూసిన; /* Set if one fn decl/definition has been seen already.  */
  వృక్షం clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
స్థిర వృక్షం objc_foreach_break_label, objc_foreach_continue_label;

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
నిర్మాణం omp_for_parse_దత్తాంశం {
  గణన వృక్షం_సంకేతం_2 సంకేతం_2;
  వృక్షం declv, condv, incrv, initv;
  వృక్షం pre_body;
  వృక్షం bindings;
  పూర్ణాంకం లెక్క;	/* Expected nesting depth.  */
  పూర్ణాంకం లోతు;	/* Current nesting depth.  */
  location_t for_loc;
  తార్కిక ordered : 1;
  తార్కిక inscan : 1;
  తార్కిక want_nested_loop : 1;
  తార్కిక లోపల_intervening_సంకేతం : 1;
  తార్కిక saw_intervening_సంకేతం: 1;
  తార్కిక perfect_nesting_fail : 1;
  తార్కిక fail : 1;
};

నిర్మాణం attr_state
{
  /* True if we parsed a musttail attribute for return.  */
  తార్కిక musttail_p;

  శూన్య reset () { musttail_p = అబద్ధం; }
};

స్థిర తార్కిక c_parser_nth_token_starts_std_లక్షణాలు (c_parser *,
						      గుర్తులేని పూర్ణాంకం);
స్థిర వృక్షం c_parser_std_attribute_specifier_sequence (c_parser *);
స్థిర శూన్య c_parser_external_declaration (c_parser *);
స్థిర శూన్య c_parser_asm_definition (c_parser *);
స్థిర వృక్షం c_parser_declaration_or_fndef (c_parser *, తార్కిక, తార్కిక, తార్కిక,
					   తార్కిక, తార్కిక, తార్కిక, వృక్షం * = ఖాళీ,
					   vec<c_token> * = ఖాళీ,
					   తార్కిక have_attrs = అబద్ధం,
					   వృక్షం attrs = ఖాళీ,
					   నిర్మాణం oacc_routine_దత్తాంశం * = ఖాళీ,
					   తార్కిక * = ఖాళీ);
స్థిర తార్కిక c_parser_handle_statement_omp_లక్షణాలు (c_parser *, వృక్షం &,
						      తార్కిక *);
స్థిర శూన్య c_parser_static_assert_declaration_no_semi (c_parser *);
స్థిర శూన్య c_parser_static_assert_declaration (c_parser *);
స్థిర నిర్మాణం c_typespec c_parser_enum_specifier (c_parser *);
స్థిర నిర్మాణం c_typespec c_parser_struct_or_union_specifier (c_parser *);
స్థిర వృక్షం c_parser_struct_declaration (c_parser *, వృక్షం *);
స్థిర నిర్మాణం c_typespec c_parser_typeof_specifier (c_parser *);
స్థిర వృక్షం c_parser_alignas_specifier (c_parser *);
స్థిర నిర్మాణం c_declarator *c_parser_ప్రత్యక్ష_declarator (c_parser *, తార్కిక,
							c_dtr_syn, తార్కిక *);
స్థిర నిర్మాణం c_declarator *c_parser_ప్రత్యక్ష_declarator_inner (c_parser *,
							      తార్కిక,
							      నిర్మాణం c_declarator *);
స్థిర నిర్మాణం c_arg_info *c_parser_parms_declarator (c_parser *, తార్కిక, వృక్షం,
						     తార్కిక);
స్థిర నిర్మాణం c_arg_info *c_parser_parms_list_declarator (c_parser *, వృక్షం,
							  వృక్షం, తార్కిక);
స్థిర నిర్మాణం c_parm *c_parser_parameter_declaration (c_parser *, వృక్షం, తార్కిక);
స్థిర వృక్షం c_parser_asm_string_literal (c_parser *);
స్థిర వృక్షం c_parser_simple_asm_సమాసం (c_parser *);
స్థిర వృక్షం c_parser_gnu_లక్షణాలు (c_parser *);
స్థిర నిర్మాణం c_సమాసం c_parser_initializer (c_parser *, వృక్షం);
స్థిర నిర్మాణం c_సమాసం c_parser_braced_init (c_parser *, వృక్షం, తార్కిక,
					   నిర్మాణం obstack *, తార్కిక);
స్థిర శూన్య c_parser_initelt (c_parser *, నిర్మాణం obstack *);
స్థిర శూన్య c_parser_initval (c_parser *, నిర్మాణం c_సమాసం *,
			      నిర్మాణం obstack *);
స్థిర వృక్షం c_parser_compound_statement (c_parser *, location_t * = ఖాళీ);
స్థిర location_t c_parser_compound_statement_nostart (c_parser *);
స్థిర శూన్య c_parser_label (c_parser *, వృక్షం);
స్థిర శూన్య c_parser_statement (c_parser *, తార్కిక *, location_t * = ఖాళీ);
స్థిర శూన్య c_parser_statement_after_labels (c_parser *, తార్కిక *, వృక్షం,
					     vec<వృక్షం> * = ఖాళీ,
					     attr_state = {});
స్థిర వృక్షం c_parser_c99_ఖండం_statement (c_parser *, తార్కిక *,
					  location_t * = ఖాళీ);
స్థిర శూన్య c_parser_if_statement (c_parser *, తార్కిక *, vec<వృక్షం> *);
స్థిర శూన్య c_parser_switch_statement (c_parser *, తార్కిక *, వృక్షం);
స్థిర శూన్య c_parser_while_statement (c_parser *, తార్కిక, గుర్తులేని పొట్టి, తార్కిక,
				      తార్కిక *, వృక్షం);
స్థిర శూన్య c_parser_do_statement (c_parser *, తార్కిక, గుర్తులేని పొట్టి, తార్కిక,
				   వృక్షం);
స్థిర శూన్య c_parser_for_statement (c_parser *, తార్కిక, గుర్తులేని పొట్టి, తార్కిక,
				    తార్కిక *, వృక్షం);
స్థిర వృక్షం c_parser_asm_statement (c_parser *);
స్థిర వృక్షం c_parser_asm_operands (c_parser *);
స్థిర వృక్షం c_parser_asm_goto_operands (c_parser *);
స్థిర వృక్షం c_parser_asm_clobbers (c_parser *);
స్థిర నిర్మాణం c_సమాసం c_parser_సమాసం_no_commas (c_parser *, నిర్మాణం c_సమాసం *,
					      వృక్షం = NULL_వృక్షం);
స్థిర నిర్మాణం c_సమాసం c_parser_conditional_వ్యక్తీకరణ (c_parser *,
						      నిర్మాణం c_సమాసం *, వృక్షం);
స్థిర నిర్మాణం c_సమాసం c_parser_ద్విమాన_వ్యక్తీకరణ (c_parser *, నిర్మాణం c_సమాసం *,
						 వృక్షం);
స్థిర నిర్మాణం c_సమాసం c_parser_cast_వ్యక్తీకరణ (c_parser *, నిర్మాణం c_సమాసం *);
స్థిర నిర్మాణం c_సమాసం c_parser_unary_వ్యక్తీకరణ (c_parser *);
స్థిర నిర్మాణం c_సమాసం c_parser_sizeof_or_countof_వ్యక్తీకరణ (c_parser *,
							    గణన rid);
స్థిర నిర్మాణం c_సమాసం c_parser_alignof_వ్యక్తీకరణ (c_parser *);
స్థిర నిర్మాణం c_సమాసం c_parser_maxof_or_minof_వ్యక్తీకరణ (c_parser *, గణన rid);
స్థిర నిర్మాణం c_సమాసం c_parser_postfix_వ్యక్తీకరణ (c_parser *);
స్థిర నిర్మాణం c_సమాసం c_parser_postfix_వ్యక్తీకరణ_after_paren_type (c_parser *,
								   నిర్మాణం c_declspecs *,
								   నిర్మాణం c_type_name *,
								   location_t);
స్థిర నిర్మాణం c_సమాసం c_parser_postfix_వ్యక్తీకరణ_after_primary (c_parser *,
								location_t loc,
								నిర్మాణం c_సమాసం);
స్థిర వృక్షం c_parser_transaction (c_parser *, గణన rid);
స్థిర నిర్మాణం c_సమాసం c_parser_transaction_వ్యక్తీకరణ (c_parser *, గణన rid);
స్థిర వృక్షం c_parser_transaction_cancel (c_parser *);
స్థిర నిర్మాణం c_సమాసం c_parser_వ్యక్తీకరణ (c_parser *);
స్థిర నిర్మాణం c_సమాసం c_parser_వ్యక్తీకరణ_conv (c_parser *);
స్థిర vec<వృక్షం, va_gc> *c_parser_సమాసం_list (c_parser *, తార్కిక, తార్కిక,
					     vec<వృక్షం, va_gc> **, location_t *,
					     వృక్షం *, vec<location_t> *,
					     గుర్తులేని పూర్ణాంకం * = ఖాళీ);
స్థిర నిర్మాణం c_సమాసం c_parser_has_attribute_వ్యక్తీకరణ (c_parser *);

స్థిర శూన్య c_parser_oacc_declare (c_parser *);
స్థిర శూన్య c_parser_oacc_enter_exit_దత్తాంశం (c_parser *, తార్కిక);
స్థిర శూన్య c_parser_oacc_update (c_parser *);
స్థిర శూన్య c_parser_omp_construct (c_parser *, తార్కిక *);
స్థిర శూన్య c_parser_omp_groupprivate (c_parser *);
స్థిర శూన్య c_parser_omp_threadprivate (c_parser *);
స్థిర శూన్య c_parser_omp_barrier (c_parser *);
స్థిర శూన్య c_parser_omp_depobj (c_parser *);
స్థిర శూన్య c_parser_omp_flush (c_parser *);
స్థిర తార్కిక c_parser_omp_తదుపరి_టోకెన్లు_can_be_canon_loop (c_parser *,
							గణన వృక్షం_సంకేతం_2, తార్కిక);
స్థిర వృక్షం c_parser_omp_loop_nest (c_parser *, తార్కిక *);
స్థిర వృక్షం c_parser_omp_for_loop (location_t, c_parser *, గణన వృక్షం_సంకేతం_2,
				   వృక్షం, వృక్షం *, తార్కిక *);
స్థిర శూన్య c_parser_omp_taskwait (c_parser *);
స్థిర శూన్య c_parser_omp_taskyield (c_parser *);
స్థిర శూన్య c_parser_omp_cancel (c_parser *);
స్థిర శూన్య c_parser_omp_nothing (c_parser *);
స్థిర శూన్య c_parser_omp_metadirective (c_parser *, తార్కిక *);

గణన pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
స్థిర తార్కిక c_parser_pragma (c_parser *, గణన pragma_context, తార్కిక *, వృక్షం);
స్థిర తార్కిక c_parser_omp_cancellation_బిందువు (c_parser *, గణన pragma_context);
స్థిర తార్కిక c_parser_omp_లక్ష్యం (c_parser *, గణన pragma_context, తార్కిక *);
స్థిర శూన్య c_parser_omp_begin (c_parser *);
స్థిర శూన్య c_parser_omp_చివర (c_parser *);
స్థిర తార్కిక c_parser_omp_declare (c_parser *, గణన pragma_context);
స్థిర శూన్య c_parser_omp_requires (c_parser *);
స్థిర తార్కిక c_parser_omp_error (c_parser *, గణన pragma_context);
స్థిర శూన్య c_parser_omp_assumption_clauses (c_parser *, తార్కిక);
స్థిర శూన్య c_parser_omp_allocate (c_parser *);
స్థిర శూన్య c_parser_omp_assumes (c_parser *);
స్థిర తార్కిక c_parser_omp_ordered (c_parser *, గణన pragma_context, తార్కిక *);
స్థిర వృక్షం c_parser_omp_dispatch (location_t, c_parser *);
స్థిర శూన్య c_parser_omp_interop (c_parser *);
స్థిర శూన్య c_parser_oacc_routine (c_parser *, గణన pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
స్థిర శూన్య c_parser_objc_class_definition (c_parser *, వృక్షం);
స్థిర శూన్య c_parser_objc_class_instance_variables (c_parser *);
స్థిర శూన్య c_parser_objc_class_declaration (c_parser *);
స్థిర శూన్య c_parser_objc_alias_declaration (c_parser *);
స్థిర శూన్య c_parser_objc_protocol_definition (c_parser *, వృక్షం);
స్థిర తార్కిక c_parser_objc_పద్ధతి_type (c_parser *);
స్థిర శూన్య c_parser_objc_పద్ధతి_definition (c_parser *);
స్థిర శూన్య c_parser_objc_methodprotolist (c_parser *);
స్థిర శూన్య c_parser_objc_methodproto (c_parser *);
స్థిర వృక్షం c_parser_objc_పద్ధతి_decl (c_parser *, తార్కిక, వృక్షం *, వృక్షం *);
స్థిర వృక్షం c_parser_objc_type_name (c_parser *);
స్థిర వృక్షం c_parser_objc_protocol_refs (c_parser *);
స్థిర శూన్య c_parser_objc_try_catch_finally_statement (c_parser *);
స్థిర శూన్య c_parser_objc_synchronized_statement (c_parser *);
స్థిర వృక్షం c_parser_objc_selector (c_parser *);
స్థిర వృక్షం c_parser_objc_selector_arg (c_parser *);
స్థిర వృక్షం c_parser_objc_receiver (c_parser *);
స్థిర వృక్షం c_parser_objc_సందేశం_వాదనలు (c_parser *);
స్థిర వృక్షం c_parser_objc_keywordexpr (c_parser *);
స్థిర శూన్య c_parser_objc_at_property_declaration (c_parser *);
స్థిర శూన్య c_parser_objc_at_synthesize_declaration (c_parser *);
స్థిర శూన్య c_parser_objc_at_dynamic_declaration (c_parser *);
స్థిర తార్కిక c_parser_objc_diagnose_bad_element_ఉపసర్గ
  (c_parser *, నిర్మాణం c_declspecs *);
స్థిర location_t c_parser_parse_rtl_body (c_parser *, అక్షరం *);
స్థిర వృక్షం c_parser_handle_musttail (c_parser *, వృక్షం, attr_state &);

#ఒకవేళ ENABLE_ANALYZER

నామాకాశ ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

తరగతి c_translation_unit : బహిరంగ translation_unit
{
బహిరంగ:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  వృక్షం lookup_constant_by_id (వృక్షం id) స్థిరరాశి final override
  {
    /* Consider decls.  */
    ఒకవేళ (వృక్షం decl = lookup_name (id))
      ఒకవేళ (వృక్షం_సంకేతం (decl) == CONST_DECL)
	ఒకవేళ (వృక్షం విలువ = DECL_INITIAL (decl))
	  ఒకవేళ (వృక్షం_సంకేతం (విలువ) == INTEGER_CST)
	    తిరిగి విలువ;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    ఒకవేళ (cpp_macro_p (hashnode))
      ఒకవేళ (వృక్షం విలువ = consider_macro (hashnode->విలువ.macro))
	తిరిగి విలువ;

    తిరిగి NULL_వృక్షం;
  }

  వృక్షం
  lookup_type_by_id (వృక్షం id) స్థిరరాశి final override
  {
    ఒకవేళ (వృక్షం type_decl = lookup_name (id))
	ఒకవేళ (వృక్షం_సంకేతం (type_decl) == TYPE_DECL)
	  {
	    వృక్షం రికార్డు_type = వృక్షం_TYPE (type_decl);
	    ఒకవేళ (వృక్షం_సంకేతం (రికార్డు_type) == రికార్డు_TYPE)
	      తిరిగి రికార్డు_type;
	  }

    తిరిగి NULL_వృక్షం;
  }

  వృక్షం
  lookup_global_var_by_id (వృక్షం id) స్థిరరాశి final override
  {
    ఒకవేళ (వృక్షం var_decl = lookup_name (id))
      ఒకవేళ (వృక్షం_సంకేతం (var_decl) == VAR_DECL)
				తిరిగి var_decl;

    తిరిగి NULL_వృక్షం;
  }

అంతరంగ:
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
  వృక్షం consider_macro (cpp_macro *macro, పూర్ణాంకం లోతు = 0) స్థిరరాశి
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (లోతు >= 0);

    ఒకవేళ (macro->paramc > 0)
      తిరిగి NULL_వృక్షం;
    ఒకవేళ (macro->రకం != cmk_macro)
      తిరిగి NULL_వృక్షం;
    ఒకవేళ (macro->లెక్క != 1)
      తిరిగి NULL_వృక్షం;
    స్థిరరాశి cpp_token &tok = macro->ఘాతాంకం.టోకెన్లు[0];
    ఒకవేళ (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	ఒకవేళ (లోతు >= param_analyzer_max_macro_alias_లోతు)
	  తిరిగి NULL_వృక్షం;

	cpp_hashnode *alias = tok.val.కణుపు.కణుపు;
	ఒకవేళ (cpp_macro_p (alias))
	  తిరిగి consider_macro (alias->విలువ.macro, లోతు + 1);

	/* Not a simple alias.  */
	తిరిగి NULL_వృక్షం;
      }
    లేకపోతే ఒకవేళ (tok.type != CPP_సంఖ్య)
      తిరిగి NULL_వృక్షం;

    cpp_reader *old_parse_లోపల = parse_లోపల;
    parse_లోపల = cpp_create_reader (CLK_GNUC89, ఖాళీ, పంక్తి_పట్టిక);

    pretty_printer pp;
    pp_string (&pp, (స్థిరరాశి అక్షరం *) tok.val.str.పాఠ్యం);
    pp_newline (&pp);
    cpp_నెట్టు_బఫరు (parse_లోపల,
		     (స్థిరరాశి గుర్తులేని అక్షరం *) pp_formatted_పాఠ్యం (&pp),
		     అక్షరశ్రేణి_పొడవు (pp_formatted_పాఠ్యం (&pp)),
		     0);

    వృక్షం విలువ;
    location_t loc;
    గుర్తులేని అక్షరం cpp_flags;
    c_lex_with_flags (&విలువ, &loc, &cpp_flags, 0);

    cpp_destroy (parse_లోపల);
    parse_లోపల = old_parse_లోపల;

    ఒకవేళ (విలువ && వృక్షం_సంకేతం (విలువ) == INTEGER_CST)
      తిరిగి విలువ;

    తిరిగి NULL_వృక్షం;
  }
};

} // namespace ana

#అయితే_ముగింపు /* #if ENABLE_ANALYZER */

/* Parse a translation unit (C90 6.7, C99 6.9, C11 6.9).

   translation-unit:
     external-declarations

   external-declarations:
     external-declaration
     external-declarations external-declaration

   GNU extensions:

   translation-unit:
ఖాళీలు
*/

స్థిర శూన్య
c_parser_translation_unit (c_parser *parser)
{
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_EOF))
    {
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C forbids an empty translation unit");
    }
  లేకపోతే
    {
      శూన్య *obstack_position = obstack_alloc (&parser_obstack, 0);
      mark_valid_location_for_stdc_pragma (అబద్ధం);
      చేయి
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_EOF));
    }

  గుర్తులేని పూర్ణాంకం i;
  వృక్షం decl;
  FOR_EACH_VEC_ELT (incomplete_రికార్డు_decls, i, decl)
    ఒకవేళ (DECL_కొలత (decl) == NULL_వృక్షం && వృక్షం_TYPE (decl) != error_mark_కణుపు)
      error ("storage size of %q+D isn%'t known", decl);

  ఒకవేళ (vec_సురక్షిత_నిడివి (current_omp_declare_లక్ష్యం_attribute))
    {
      c_omp_declare_లక్ష్యం_attr
	a = current_omp_declare_లక్ష్యం_attribute->తీయి ();
      ఒకవేళ (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_సురక్షిత_truncate (current_omp_declare_లక్ష్యం_attribute, 0);
    }
  ఒకవేళ (vec_సురక్షిత_నిడివి (current_omp_begin_assumes))
    {
      ఒకవేళ (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_సురక్షిత_truncate (current_omp_begin_assumes, 0);
    }
  ఒకవేళ (vec_సురక్షిత_నిడివి (current_omp_declare_variant_attribute))
    {
      ఒకవేళ (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_సురక్షిత_truncate (current_omp_declare_variant_attribute, 0);
    }
  ఒకవేళ (vec_సురక్షిత_నిడివి (omp_begin_declare_variant_map))
    {
      గుర్తులేని పూర్ణాంకం i;
      omp_begin_declare_variant_map_నమోదు *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_ముగింపు_variant_function (e->variant, e->id, e->ctx);
      vec_సురక్షిత_truncate (omp_begin_declare_variant_map, 0);
    }

#ఒకవేళ ENABLE_ANALYZER
  ఒకవేళ (flag_analyzer)
    {
      ana::c_translation_unit tu;
      ana::on_ముగింపు_translation_unit (tu);
    }
#అయితే_ముగింపు
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

స్థిర శూన్య
c_parser_external_declaration (c_parser *parser)
{
  పూర్ణాంకం ext;
  ఎంపిక (c_parser_peek_token (parser)->type)
    {
    స్థితి CPP_KEYWORD:
      ఎంపిక (c_parser_peek_token (parser)->keyword)
	{
	స్థితి RID_EXTENSION:
	  ext = disable_extension_diagnostics ();
	  c_parser_consume_token (parser);
	  c_parser_external_declaration (parser);
	  restore_extension_diagnostics (ext);
	  ఆపు;
	స్థితి RID_ASM:
	  c_parser_asm_definition (parser);
	  ఆపు;
	స్థితి RID_AT_INTERFACE:
	స్థితి RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_definition (parser, NULL_వృక్షం);
	  ఆపు;
	స్థితి RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  ఆపు;
	స్థితి RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  ఆపు;
	స్థితి RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_protocol_definition (parser, NULL_వృక్షం);
	  ఆపు;
	స్థితి RID_AT_PROPERTY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_property_declaration (parser);
	  ఆపు;
	స్థితి RID_AT_SYNTHESIZE:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_synthesize_declaration (parser);
	  ఆపు;
	స్థితి RID_AT_DYNAMIC:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_dynamic_declaration (parser);
	  ఆపు;
	స్థితి RID_AT_చివర:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_ముగింపు_implementation ();
	  ఆపు;
	అప్రమేయ:
	  వెళ్ళు decl_or_fndef;
	}
      ఆపు;
    స్థితి CPP_SEMICOLON:
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      ఆపు;
    స్థితి CPP_PRAGMA:
      mark_valid_location_for_stdc_pragma (నిజం);
      c_parser_pragma (parser, pragma_external, ఖాళీ, NULL_వృక్షం);
      mark_valid_location_for_stdc_pragma (అబద్ధం);
      ఆపు;
    స్థితి CPP_PLUS:
    స్థితి CPP_MINUS:
      ఒకవేళ (c_dialect_objc ())
	{
	  c_parser_objc_పద్ధతి_definition (parser);
	  ఆపు;
	}
      /* Else fall through, and yield a syntax error trying to parse
	 as a declaration or function definition.  */
      /* FALLTHRU */
    అప్రమేయ:
    decl_or_fndef:
      /* A declaration or a function definition (or, in Objective-C,
	 an @interface or @protocol with prefix attributes).  We can
	 only tell which after parsing the declaration specifiers, if
	 any, and the first declarator.  */
      c_parser_declaration_or_fndef (parser, నిజం, నిజం, నిజం, అబద్ధం, నిజం,
				     అబద్ధం);
      ఆపు;
    }
}

స్థిర శూన్య c_parser_handle_directive_omp_లక్షణాలు (వృక్షం &, vec<c_token> *&,
						      vec<c_token> *);
స్థిర శూన్య c_ముగింపు_omp_declare_simd (c_parser *, వృక్షం, వృక్షం, vec<c_token> *);
స్థిర శూన్య c_ముగింపు_oacc_routine (నిర్మాణం oacc_routine_దత్తాంశం *, వృక్షం, తార్కిక);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

స్థిర శూన్య
కూడు_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  ఒకవేళ (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    తిరిగి;

  వృక్షం stmt = build0 (DEBUG_BEGIN_STMT, void_type_కణుపు);
  సమితి_సమాసం_LOCATION (stmt, loc);
  కూడు_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

స్థిర వృక్షం
handle_assume_attribute (location_t ఇక్కడ, వృక్షం attrs, తార్కిక nested)
{
  ఒకవేళ (nested)
    కొరకు (వృక్షం attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", వృక్షం_CHAIN (attr)))
      {
	వృక్షం వాదనలు = వృక్షం_విలువ (attr);
	పూర్ణాంకం nargs = list_నిడివి (వాదనలు);
	ఒకవేళ (nargs != 1)
	  {
	    error_at (ఇక్కడ, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (ఇక్కడ, "expected %i, found %i", 1, nargs);
	  }
	లేకపోతే
	  {
	    వృక్షం arg = వృక్షం_విలువ (వాదనలు);
	    arg = c_objc_common_truthvalue_conversion (ఇక్కడ, arg);
	    arg = c_fully_fold (arg, అబద్ధం, ఖాళీ);
	    ఒకవేళ (arg != error_mark_కణుపు)
	      {
		వృక్షం fn = build_call_సమాసం_అంతర్గత_loc (ఇక్కడ, IFN_ASSUME,
							void_type_కణుపు, 1,
							arg);
		కూడు_stmt (fn);
	      }
	  }
      }
  లేకపోతే
    pedwarn (ఇక్కడ, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  తిరిగి remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

స్థిర శూన్య
c_parser_maybe_reclassify_token (c_parser *parser)
{
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      ఒకవేళ (token->id_రకం == C_ID_ID || token->id_రకం == C_ID_TYPENAME)
	{
	  వృక్షం decl = lookup_name (token->విలువ);

	  token->id_రకం = C_ID_ID;
	  ఒకవేళ (decl)
	    {
	      ఒకవేళ (వృక్షం_సంకేతం (decl) == TYPE_DECL)
		token->id_రకం = C_ID_TYPENAME;
	    }
	  లేకపోతే ఒకవేళ (c_dialect_objc ())
	    {
	      వృక్షం objc_interface_decl = objc_is_class_name (token->విలువ);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      ఒకవేళ (objc_interface_decl)
		{
		  token->విలువ = objc_interface_decl;
		  token->id_రకం = C_ID_CLASSNAME;
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

స్థిర వృక్షం
c_parser_declaration_or_fndef (c_parser *parser, తార్కిక fndef_ok,
			       తార్కిక static_assert_ok, తార్కిక ఖాళీలు_ok,
			       తార్కిక nested, తార్కిక ప్రారంభం_attr_ok,
			       తార్కిక simple_ok,
			       వృక్షం *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       తార్కిక have_attrs /* = false */,
			       వృక్షం attrs /* = NULL_TREE */,
			       నిర్మాణం oacc_routine_దత్తాంశం *oacc_routine_దత్తాంశం
			       /* = NULL */,
			       తార్కిక *fallthru_attr_p /* = NULL */)
{
  నిర్మాణం c_declspecs *specs;
  వృక్షం ఉపసర్గ_attrs;
  వృక్షం all_ఉపసర్గ_attrs;
  తార్కిక diagnosed_no_specs = అబద్ధం;
  location_t ఇక్కడ = c_parser_peek_token (parser)->location;
  వృక్షం ఫలితం = NULL_వృక్షం;

  కూడు_debug_begin_stmt (c_parser_peek_token (parser)->location);

  ఒకవేళ (static_assert_ok
      && c_parser_తదుపరి_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      తిరిగి ఫలితం;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  ఒకవేళ (have_attrs)
    {
      declspecs_కూడు_attrs (ఇక్కడ, specs, attrs);
      specs->non_std_attrs_చూసిన_p = అబద్ధం;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  ఒకవేళ (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_రకం == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->విలువ)))
    {
      వృక్షం name = c_parser_peek_token (parser)->విలువ;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (ఇక్కడ);
      ఒకవేళ (ట్యాగ్_exists_p (రికార్డు_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.కూడు_fixit_చొప్పించు_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      లేకపోతే ఒకవేళ (ట్యాగ్_exists_p (UNION_TYPE, name))
	{
	  richloc.కూడు_fixit_చొప్పించు_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      లేకపోతే ఒకవేళ (ట్యాగ్_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.కూడు_fixit_చొప్పించు_before ("enum ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<enum%> keyword to refer to the type",
		    name);
	}
      లేకపోతే
	{
	  auto_diagnostic_సమూహం d;
	  name_hint hint = lookup_name_fuzzy (name, FUZZY_LOOKUP_TYPENAME,
					      ఇక్కడ);
	  ఒకవేళ (స్థిరరాశి అక్షరం *suggestion = hint.suggestion ())
	    {
	      richloc.కూడు_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			name, suggestion);
	    }
	  లేకపోతే
	    error_at (ఇక్కడ, "unknown type name %qE", name);
	}

      /* Parse declspecs normally to get a correct pointer type, but avoid
         a further "fails to be a type name" error.  Refuse nested functions
         since it is not how the user likely wants us to recover.  */
      c_parser_peek_token (parser)->type = CPP_KEYWORD;
      c_parser_peek_token (parser)->keyword = RID_VOID;
      c_parser_peek_token (parser)->విలువ = error_mark_కణుపు;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  ఒకవేళ (c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
    have_attrs = నిజం;

  c_parser_declspecs (parser, specs, నిజం, నిజం, ప్రారంభం_attr_ok,
		      నిజం, నిజం, ప్రారంభం_attr_ok, నిజం, cla_nonabstract_decl);
  ఒకవేళ (parser->error)
    {
      c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
      తిరిగి ఫలితం;
    }
  ఒకవేళ (nested && !specs->declspecs_చూసిన_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
      తిరిగి ఫలితం;
    }

  ముగింపు_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  ఒకవేళ (specs->typespec_రకం == ctsk_tagdef)
    verify_counted_by_for_శిఖరం_anonymous_type (specs->type);

  తార్కిక gnu_auto_type_p = specs->typespec_మాట == cts_auto_type;
  తార్కిక std_auto_type_p = specs->c23_auto_p;
  తార్కిక any_auto_type_p = gnu_auto_type_p || std_auto_type_p;
  gcc_assert (!(gnu_auto_type_p && std_auto_type_p));
  స్థిరరాశి అక్షరం *auto_type_keyword = gnu_auto_type_p ? "__auto_type" : "auto";
  ఒకవేళ (specs->constexpr_p)
    {
      /* An underspecified declaration may not declare tags or members
	 or structures or unions; it is undefined behavior to declare
	 the members of an enumeration.  Where the structure, union or
	 enumeration type is declared within an initializer, this is
	 diagnosed elsewhere.  Diagnose here the case of declaring
	 such a type in the type specifiers of a constexpr
	 declaration.  */
      ఎంపిక (specs->typespec_రకం)
	{
	స్థితి ctsk_tagfirstref:
	స్థితి ctsk_tagfirstref_attrs:
	  error_at (ఇక్కడ, "%qT declared in underspecified object declaration",
		    specs->type);
	  ఆపు;

	స్థితి ctsk_tagdef:
	  error_at (ఇక్కడ, "%qT defined in underspecified object declaration",
		    specs->type);
	  ఆపు;

	అప్రమేయ:
	  ఆపు;
	}
    }

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
    {
      తార్కిక handled_assume = అబద్ధం;
      ఒకవేళ (specs->attrs
	  && !nested
	  && specs->typespec_రకం == ctsk_none
	  && c_parser_handle_statement_omp_లక్షణాలు (parser, specs->attrs,
						       ఖాళీ))
	{
	  ఒకవేళ (specs->attrs)
	    c_warn_వాడని_లక్షణాలు (specs->attrs);
	  అయితే (parser->లోపల_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_తదుపరి_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, ఖాళీ, NULL_వృక్షం);
	    }
	  c_parser_consume_token (parser);
	  తిరిగి ఫలితం;
	}
      ఒకవేళ (specs->typespec_రకం == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = నిజం;
	  specs->attrs
	    = handle_assume_attribute (ఇక్కడ, specs->attrs, nested);
	}
      ఒకవేళ (any_auto_type_p)
	error_at (ఇక్కడ, "%qs in empty declaration", auto_type_keyword);
      లేకపోతే ఒకవేళ (specs->typespec_రకం == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  ఒకవేళ (fallthru_attr_p != ఖాళీ)
	    *fallthru_attr_p = నిజం;
	  ఒకవేళ (nested)
	    {
	      వృక్షం fn = build_call_సమాసం_అంతర్గత_loc (ఇక్కడ, IFN_FALLTHROUGH,
						      void_type_కణుపు, 0);
	      కూడు_stmt (fn);
	    }
	  లేకపోతే
	    pedwarn (ఇక్కడ, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      లేకపోతే ఒకవేళ (ఖాళీలు_ok
	       && !(have_attrs && specs->non_std_attrs_చూసిన_p)
	       && !handled_assume)
	shadow_ట్యాగ్ (specs);
      లేకపోతే
	{
	  shadow_ట్యాగ్_warned (specs, 1);
	  ఒకవేళ (!handled_assume)
	    pedwarn (ఇక్కడ, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      ఒకవేళ (specs->సమాసం)
	కూడు_stmt (fold_convert (void_type_కణుపు, specs->సమాసం));
      c_parser_consume_token (parser);
      ఒకవేళ (oacc_routine_దత్తాంశం)
	c_ముగింపు_oacc_routine (oacc_routine_దత్తాంశం, NULL_వృక్షం, అబద్ధం);
      తిరిగి ఫలితం;
    }
  లేకపోతే ఒకవేళ (specs->typespec_రకం == ctsk_none
	   && nested
	   /* Only parse __attribute__((musttail)) when called from
	      c_parser_compound_statement_nostart.  This certainly isn't
	      a declaration in that case, but we don't do tentative parsing
	      of GNU attributes right now.  */
	   && fallthru_attr_p
	   && c_parser_తదుపరి_token_is_keyword (parser, RID_RETURN))
    {
      attr_state astate = {};
      specs->attrs = c_parser_handle_musttail (parser, specs->attrs, astate);
      ఒకవేళ (astate.musttail_p)
	{
	  ఒకవేళ (specs->attrs)
	    {
	      auto_urlify_లక్షణాలు sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, ఖాళీ, NULL_వృక్షం, ఖాళీ,
					   astate);
	  తిరిగి ఫలితం;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  ఒకవేళ (ఖాళీలు_ok
      && specs->typespec_రకం == ctsk_tagdef
      && c_parser_తదుపరి_token_starts_declspecs (parser)
      && !c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = అబద్ధం;
      shadow_ట్యాగ్_warned (specs, 1);
      తిరిగి ఫలితం;
    }
  లేకపోతే ఒకవేళ (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      ఎంపిక (c_parser_peek_token (parser)->type)
	{
	  స్థితి CPP_PLUS:
	  స్థితి CPP_MINUS:
	    ఒకవేళ (c_parser_objc_diagnose_bad_element_ఉపసర్గ (parser, specs))
	      తిరిగి ఫలితం;
	    ఒకవేళ (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_వృక్షం;
	      }
	    ఒకవేళ (fndef_ok)
	      c_parser_objc_పద్ధతి_definition (parser);
	    లేకపోతే
	      c_parser_objc_methodproto (parser);
	    తిరిగి ఫలితం;
	    ఆపు;
	  అప్రమేయ:
	    ఆపు;
	}
      /* This is where we parse 'attributes @interface ...',
	 'attributes @implementation ...', 'attributes @protocol ...'
	 (where attributes could be, for example, __attribute__
	 ((deprecated)).
      */
      ఎంపిక (c_parser_peek_token (parser)->keyword)
	{
	స్థితి RID_AT_INTERFACE:
	  {
	    ఒకవేళ (c_parser_objc_diagnose_bad_element_ఉపసర్గ (parser, specs))
	      తిరిగి ఫలితం;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    తిరిగి ఫలితం;
	  }
	  ఆపు;
	స్థితి RID_AT_IMPLEMENTATION:
	  {
	    ఒకవేళ (c_parser_objc_diagnose_bad_element_ఉపసర్గ (parser, specs))
	      తిరిగి ఫలితం;
	    ఒకవేళ (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_వృక్షం;
	      }
	    c_parser_objc_class_definition (parser, NULL_వృక్షం);
	    తిరిగి ఫలితం;
	  }
	  ఆపు;
	స్థితి RID_AT_PROTOCOL:
	  {
	    ఒకవేళ (c_parser_objc_diagnose_bad_element_ఉపసర్గ (parser, specs))
	      తిరిగి ఫలితం;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    తిరిగి ఫలితం;
	  }
	  ఆపు;
	స్థితి RID_AT_ALIAS:
	స్థితి RID_AT_CLASS:
	స్థితి RID_AT_చివర:
	స్థితి RID_AT_PROPERTY:
	  ఒకవేళ (specs->attrs)
	    {
	      c_parser_error (parser, "unexpected attribute");
	      specs->attrs = ఖాళీ;
	    }
	  ఆపు;
	అప్రమేయ:
	  ఆపు;
	}
    }
  లేకపోతే ఒకవేళ (attribute_fallthrough_p (specs->attrs))
    warning_at (ఇక్కడ, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  లేకపోతే ఒకవేళ (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (ఇక్కడ, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_లక్షణాలు (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  ఉపసర్గ_attrs = specs->attrs;
  all_ఉపసర్గ_attrs = ఉపసర్గ_attrs;
  specs->attrs = NULL_వృక్షం;
  తార్కిక మరిన్ని_than_one_decl = అబద్ధం;
  అయితే (నిజం)
    {
      నిర్మాణం c_declarator *declarator;
      తార్కిక dummy = అబద్ధం;
      timevar_id_t tv;
      వృక్షం fnbody = NULL_వృక్షం;
      వృక్షం underspec_name = NULL_వృక్షం;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_రకం != ctsk_none,
					C_DTR_సాధారణ, &dummy);
      ఒకవేళ (declarator == ఖాళీ)
	{
	  ఒకవేళ (omp_declare_simd_clauses)
	    c_ముగింపు_omp_declare_simd (parser, NULL_వృక్షం, NULL_వృక్షం,
				       omp_declare_simd_clauses);
	  ఒకవేళ (oacc_routine_దత్తాంశం)
	    c_ముగింపు_oacc_routine (oacc_routine_దత్తాంశం, NULL_వృక్షం, అబద్ధం);
	  /* This check is here purely to improve the diagnostic.  */
	  ఒకవేళ (!simple_ok)
	    c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
	  తిరిగి ఫలితం;
	}
      ఒకవేళ (flag_openmp || flag_openmp_simd)
	{
	  నిర్మాణం c_declarator *d = declarator;
	  అయితే (d->రకం != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = ఖాళీ;
	  c_parser_handle_directive_omp_లక్షణాలు (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      ఒకవేళ (gnu_auto_type_p && declarator->రకం != cdk_id)
	{
	  error_at (ఇక్కడ,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
	  తిరిగి ఫలితం;
	}
      ఒకవేళ (std_auto_type_p)
	{
	  నిర్మాణం c_declarator *d = declarator;
	  అయితే (d->రకం == cdk_attrs)
	    d = d->declarator;
	  ఒకవేళ (d->రకం != cdk_id)
	    {
	      error_at (ఇక్కడ,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
	      తిరిగి ఫలితం;
	    }
	  underspec_name = d->u.id.id;
	}
      లేకపోతే ఒకవేళ (specs->constexpr_p)
	{
	  నిర్మాణం c_declarator *d = declarator;
	  అయితే (d->రకం != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_EQ)
	  || c_parser_తదుపరి_token_is (parser, CPP_COMMA)
	  || c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON)
	  || c_parser_తదుపరి_token_is_keyword (parser, RID_ASM)
	  || c_parser_తదుపరి_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_తదుపరి_token_is_keyword (parser, RID_లోపల))
	{
	  వృక్షం asm_name = NULL_వృక్షం;
	  వృక్షం postfix_attrs = NULL_వృక్షం;
	  ఒకవేళ (!diagnosed_no_specs && !specs->declspecs_చూసిన_p)
	    {
	      diagnosed_no_specs = నిజం;
	      pedwarn (ఇక్కడ, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = అబద్ధం;
	  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_సమాసం (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_లక్షణాలు (parser);
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (ఇక్కడ, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
		  తిరిగి ఫలితం;
		}
	    }
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_EQ))
	    {
	      వృక్షం d;
	      నిర్మాణం c_సమాసం init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      ఒకవేళ (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (పంక్తి_పట్టిక, init_loc);
		  గుర్తులేని పూర్ణాంకం underspec_state = 0;
		  ఒకవేళ (std_auto_type_p)
		    underspec_state =
		      ప్రారంభం_underspecified_init (init_loc, underspec_name);
		  ప్రారంభం_init (NULL_వృక్షం, asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_సంకేతం_type flag_sanitize_save = flag_sanitize;
		  ఒకవేళ (nested && !ఖాళీలు_ok)
		    flag_sanitize = 0;
		  init = c_parser_సమాసం_no_commas (parser, ఖాళీ);
		  ఒకవేళ (std_auto_type_p)
		    ముగింపు_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  ఒకవేళ (gnu_auto_type_p
		      && వృక్షం_సంకేతం (init.విలువ) == COMPONENT_REF
		      && DECL_C_బిట్టు_క్షేత్రం (వృక్షం_నిర్వాహ్యం (init.విలువ, 1)))
		    error_at (ఇక్కడ,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_గమ్యం_rvalue (init_loc, init, నిజం, నిజం,
						   నిజం);
		  వృక్షం init_type = వృక్షం_TYPE (init.విలువ);
		  తార్కిక vm_type = c_type_variably_modified_p (init_type);
		  ఒకవేళ (vm_type)
		    init.విలువ = save_సమాసం (init.విలువ);
		  ముగింపు_init ();
		  specs->typespec_రకం = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = నిజం;
		  specs->type = init_type;
		  ఒకవేళ (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_లక్షణాలు (specs->type,
						  specs->postfix_attrs);
		      decl_లక్షణాలు (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_వృక్షం;
		    }
		  ఒకవేళ (vm_type)
		    {
		      తార్కిక maybe_const = నిజం;
		      వృక్షం type_సమాసం = c_fully_fold (init.విలువ, అబద్ధం,
						     &maybe_const);
		      specs->సమాసం_const_operands &= maybe_const;
		      ఒకవేళ (specs->సమాసం)
			specs->సమాసం = build2 (COMPOUND_సమాసం,
					      వృక్షం_TYPE (type_సమాసం),
					      specs->సమాసం, type_సమాసం);
		      లేకపోతే
			specs->సమాసం = type_సమాసం;
		    }
		  d = ప్రారంభం_decl (declarator, specs, నిజం,
				  chainon (postfix_attrs, all_ఉపసర్గ_attrs));
		  ఒకవేళ (!d)
		    d = error_mark_కణుపు;
		  ఒకవేళ (omp_declare_simd_clauses)
		    c_ముగింపు_omp_declare_simd (parser, d, NULL_వృక్షం,
					       omp_declare_simd_clauses);
		  ఒకవేళ (!omp_dsimd_idattr_clauses.is_ఖాళీలు ())
		    c_ముగింపు_omp_declare_simd (parser, d, NULL_వృక్షం,
					       &omp_dsimd_idattr_clauses);
		}
	      లేకపోతే
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (పంక్తి_పట్టిక, init_loc);
		  గుర్తులేని పూర్ణాంకం underspec_state = 0;
		  ఒకవేళ (specs->constexpr_p)
		    underspec_state =
		      ప్రారంభం_underspecified_init (init_loc, underspec_name);
		  d = ప్రారంభం_decl (declarator, specs, నిజం,
				  chainon (postfix_attrs,
					   all_ఉపసర్గ_attrs),
				  !specs->constexpr_p);
		  ఒకవేళ (!d)
		    d = error_mark_కణుపు;
		  ఒకవేళ (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_ముగింపు_omp_declare_simd (parser, d, NULL_వృక్షం,
					       omp_declare_simd_clauses);
		  ఒకవేళ (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_ఖాళీలు ())
		    c_ముగింపు_omp_declare_simd (parser, d, NULL_వృక్షం,
					       &omp_dsimd_idattr_clauses);
		  ప్రారంభం_init (d, asm_name,
			      వృక్షం_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_సంకేతం_type flag_sanitize_save = flag_sanitize;
		  ఒకవేళ (వృక్షం_సంకేతం (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  ఒకవేళ (specs->constexpr_p)
		    {
		      ముగింపు_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      ఒకవేళ (omp_declare_simd_clauses)
			c_ముగింపు_omp_declare_simd (parser, d, NULL_వృక్షం,
						   omp_declare_simd_clauses);
		  ఒకవేళ (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_ఖాళీలు ())
		    c_ముగింపు_omp_declare_simd (parser, d, NULL_వృక్షం,
					       &omp_dsimd_idattr_clauses);
		    }
		  ముగింపు_init ();
		}
	      ఒకవేళ (oacc_routine_దత్తాంశం)
		c_ముగింపు_oacc_routine (oacc_routine_దత్తాంశం, d, అబద్ధం);
	      ఒకవేళ (d != error_mark_కణుపు)
		{
		  maybe_warn_string_init (init_loc, వృక్షం_TYPE (d), init);
		  ముగింపు_decl (d, init_loc, init.విలువ,
			       init.original_type, asm_name);
		  ఫలితం = d;
		}
	    }
	  లేకపోతే
	    {
	      ఒకవేళ (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (ఇక్కడ,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
		  తిరిగి ఫలితం;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      వృక్షం attrs = chainon (postfix_attrs, all_ఉపసర్గ_attrs);
	      వృక్షం d = ప్రారంభం_decl (declarator, specs, అబద్ధం, attrs, నిజం,
				   &lastloc);
	      ఒకవేళ (d && వృక్షం_సంకేతం (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  స్థిరరాశి నిర్మాణం c_declarator *decl = declarator;
		  స్థిరరాశి నిర్మాణం c_declarator *చివరి_non_id_attrs = ఖాళీ;

		  అయితే (decl)
		    ఎంపిక (decl->రకం)
		      {
		      స్థితి cdk_array:
		      స్థితి cdk_function:
		      స్థితి cdk_సూచిక:
			చివరి_non_id_attrs = decl;
			decl = decl->declarator;
			ఆపు;

		      స్థితి cdk_attrs:
			decl = decl->declarator;
			ఆపు;

		      స్థితి cdk_id:
			decl = 0;
			ఆపు;

		      అప్రమేయ:
			gcc_unreachable ();
		      }

		  /* If it exists and is cdk_function declaration whose
		     arguments have not been set yet, use its arguments.  */
		  ఒకవేళ (చివరి_non_id_attrs
		      && చివరి_non_id_attrs->రకం == cdk_function)
		    {
		      వృక్షం parms = చివరి_non_id_attrs->u.arg_info->parms;
		      ఒకవేళ (DECL_ARGUMENTS (d) == NULL_వృక్షం
			  && DECL_INITIAL (d) == NULL_వృక్షం)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      ఒకవేళ (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_ఖాళీలు ())
		{
		  వృక్షం parms = NULL_వృక్షం;
		  ఒకవేళ (d && వృక్షం_సంకేతం (d) == FUNCTION_DECL)
		    {
		      నిర్మాణం c_declarator *ce = declarator;
		      అయితే (ce != ఖాళీ)
			ఒకవేళ (ce->రకం == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    ఆపు;
			  }
			లేకపోతే
			  ce = ce->declarator;
		    }
		  ఒకవేళ (parms)
		    తాత్కాలిక_store_parm_decls (d, parms);
		  ఒకవేళ (omp_declare_simd_clauses)
		    c_ముగింపు_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  ఒకవేళ (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_ఖాళీలు ())
		    c_ముగింపు_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  ఒకవేళ (parms)
		    తాత్కాలిక_తీయి_parm_decls ();
		}
	      ఒకవేళ (oacc_routine_దత్తాంశం)
		c_ముగింపు_oacc_routine (oacc_routine_దత్తాంశం, d, అబద్ధం);
	      ఒకవేళ (d)
		ముగింపు_decl (d, UNKNOWN_LOCATION, NULL_వృక్షం,
			     NULL_వృక్షం, asm_name);

	      ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_లోపల))
		{
		  ఒకవేళ (d)
		    *objc_foreach_object_declaration = d;
		  లేకపోతే
		    *objc_foreach_object_declaration = error_mark_కణుపు;
		}
	    }
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    {
	      మరిన్ని_than_one_decl = నిజం;
	      ఒకవేళ (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (ఇక్కడ,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
		  తిరిగి ఫలితం;
		}
	      c_parser_consume_token (parser);
	      ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_ATTRIBUTE))
		all_ఉపసర్గ_attrs = chainon (c_parser_gnu_లక్షణాలు (parser),
					    ఉపసర్గ_attrs);
	      లేకపోతే
		all_ఉపసర్గ_attrs = ఉపసర్గ_attrs;
	      కొనసాగు;
	    }
	  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
	    {
	      ఒకవేళ (!simple_ok)
		c_parser_consume_token (parser);
	      తిరిగి ఫలితం;
	    }
	  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_లోపల))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      తిరిగి ఫలితం;
	    }
	  లేకపోతే
	    {
	      ఒకవేళ (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      లేకపోతే ఒకవేళ (మరిన్ని_than_one_decl)
		error_at (ఇక్కడ, "declaration in condition can only declare "
			  "a single object");
	      తిరిగి ఫలితం;
	    }
	}
      లేకపోతే ఒకవేళ (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (ఇక్కడ,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
	  తిరిగి ఫలితం;
	}
      లేకపోతే ఒకవేళ (!fndef_ok)
	{
	  ఒకవేళ (simple_ok && c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  లేకపోతే
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
	    }
	  తిరిగి ఫలితం;
	}
      /* Function definition (nested or otherwise).  */
      ఒకవేళ (nested)
	{
	  pedwarn (ఇక్కడ, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_నెట్టు_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      వృక్షం dv_పునాది = NULL_వృక్షం;
      వృక్షం dv_ctx = NULL_వృక్షం;
      ఒకవేళ (!vec_సురక్షిత_is_ఖాళీలు (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->చివరి ();
	  dv_ctx = copy_list (a.selector);
	  dv_పునాది = omp_ప్రారంభం_variant_function (declarator, dv_ctx);
	}

      ఒకవేళ (!ప్రారంభం_function (specs, declarator, all_ఉపసర్గ_attrs))
	{
	  /* At this point we've consumed:
	       declaration-specifiers declarator
	     and the next token isn't CPP_EQ, CPP_COMMA, CPP_SEMICOLON,
	     RID_ASM, RID_ATTRIBUTE, or RID_IN,
	     but the
	       declaration-specifiers declarator
	     aren't grokkable as a function definition, so we have
	     an error.  */
	  gcc_assert (!c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON));
	  ఒకవేళ (c_parser_తదుపరి_token_starts_declspecs (parser))
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
	      parser->error = అబద్ధం;
	    }
	  లేకపోతే
	    {
	      /* This can appear in many cases looking nothing like a
		 function definition, so we don't give a more specific
		 error suggesting there was one.  */
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			      "or %<__attribute__%>");
	    }
	  ఒకవేళ (nested)
	    c_తీయి_function_context ();
	  ఆపు;
	}

      ఒకవేళ (DECL_DECLARED_INLINE_P (current_function_decl))
        tv = TV_PARSE_INLINE;
      లేకపోతే
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
      పూర్ణాంకం save_debug_nonbind_markers_p = debug_nonbind_markers_p;
      debug_nonbind_markers_p = 0;
      c_parser_maybe_reclassify_token (parser);
      అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_EOF)
	     && c_parser_తదుపరి_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, అబద్ధం, అబద్ధం, అబద్ధం,
				       నిజం, అబద్ధం, అబద్ధం);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      ఒకవేళ (omp_declare_simd_clauses)
	c_ముగింపు_omp_declare_simd (parser, current_function_decl, NULL_వృక్షం,
				   omp_declare_simd_clauses);
      ఒకవేళ (!omp_dsimd_idattr_clauses.is_ఖాళీలు ())
	c_ముగింపు_omp_declare_simd (parser, current_function_decl, NULL_వృక్షం,
				   &omp_dsimd_idattr_clauses);
      ఒకవేళ (oacc_routine_దత్తాంశం)
	c_ముగింపు_oacc_routine (oacc_routine_దత్తాంశం, current_function_decl, నిజం);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_ప్రారంభం_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      ఒకవేళ (dv_పునాది && current_function_decl != error_mark_కణుపు)
	{
	  omp_begin_declare_variant_map_నమోదు e
	    = { current_function_decl, dv_పునాది, dv_ctx };
	  vec_సురక్షిత_నెట్టు (omp_begin_declare_variant_map, e);
	}

      /* If the definition was marked with __RTL, use the RTL parser now,
	 consuming the function body.  */
      ఒకవేళ (specs->declspec_il == cdil_rtl)
	{
	  endloc = c_parser_parse_rtl_body (parser, specs->gimple_or_rtl_pass);

	  /* Normally, store_parm_decls sets next_is_function_body,
	     anticipating a function body.  We need a push_scope/pop_scope
	     pair to flush out this state, or subsequent function parsing
	     will go wrong.  */
	  నెట్టు_scope ();
	  తీయి_scope ();

	  ముగింపు_function (endloc);
	  తిరిగి ఫలితం;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      లేకపోతే ఒకవేళ (specs->declspec_il != cdil_none)
	{
	  తార్కిక saved = లోపల_late_ద్విమాన_op;
	  లోపల_late_ద్విమాన_op = నిజం;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->నమోదు_bb_లెక్క);
	  లోపల_late_ద్విమాన_op = saved;
	}
      లేకపోతే
	fnbody = c_parser_compound_statement (parser, &endloc);
      వృక్షం fndecl = current_function_decl;
      ఒకవేళ (nested && specs->declspec_il == cdil_none)
	{
	  వృక్షం decl = current_function_decl;
	  /* Mark nested functions as needing static-chain initially.
	     lower_nested_functions will recompute it but the
	     DECL_STATIC_CHAIN flag is also used before that happens,
	     by initializer_constant_valid_p.  See gcc.dg/nested-fn-2.c.  */
	  DECL_STATIC_CHAIN (decl) = 1;
	  కూడు_stmt (fnbody);
	  ముగింపు_function (endloc);
	  c_తీయి_function_context ();
	  కూడు_stmt (build_stmt (DECL_ఆధారం_LOCATION (decl), DECL_సమాసం, decl));
	}
      లేకపోతే ఒకవేళ (nested)
	{
	  ఒకవేళ (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  లేకపోతే
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  ముగింపు_function (endloc);
	  c_తీయి_function_context ();
	}
      లేకపోతే
	{
	  ఒకవేళ (fnbody)
	    కూడు_stmt (fnbody);
	  ముగింపు_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      ఒకవేళ (specs->declspec_il != cdil_none)
	DECL_SAVED_వృక్షం (fndecl) = NULL_వృక్షం;

      ఆపు;
    }

  తిరిగి ఫలితం;
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

స్థిర శూన్య
c_parser_asm_definition (c_parser *parser)
{
  location_t asm_loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  వృక్షం asm_str = NULL_వృక్షం;
  వృక్షం outputs = NULL_వృక్షం, inputs = NULL_వృక్షం;
  ఒకవేళ (!parens.require_open (parser))
    వెళ్ళు పూర్తి;
  asm_str = c_parser_asm_string_literal (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      వెళ్ళు పూర్తి;
    }
  కొరకు (పూర్ణాంకం section = 0; section < 2; ++section)
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  ఒకవేళ (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
	      asm_str = NULL_వృక్షం;
	      వెళ్ళు పూర్తి;
	    }
	  c_parser_consume_token (parser);
	}
      లేకపోతే ఒకవేళ (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, అబద్ధం))
	వెళ్ళు error_close_paren;
      ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_COLON)
	  && !c_parser_తదుపరి_token_is (parser, CPP_SCOPE)
	  && !c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ఒకవేళ (section)
	    inputs = c_parser_asm_operands (parser);
	  లేకపోతే
	    outputs = c_parser_asm_operands (parser);
	}
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	ఆపు;
    }

  ఒకవేళ (!parens.require_close (parser))
    {
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
      asm_str = NULL_వృక్షం;
    }

  ఒకవేళ (asm_str)
    asm_str = build_asm_సమాసం (asm_loc, asm_str, outputs, inputs,
			      NULL_వృక్షం, NULL_వృక్షం, అబద్ధం, అబద్ధం);
పూర్తి:
  ఒకవేళ (asm_str)
    symtab->finalize_toplevel_asm (asm_str);
  c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse a static assertion (C11 6.7.10).

   static_assert-declaration:
     static_assert-declaration-no-semi ;
*/

స్థిర శూన్య
c_parser_static_assert_declaration (c_parser *parser)
{
  c_parser_static_assert_declaration_no_semi (parser);
  ఒకవేళ (parser->error
      || !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
}

/* Parse a static assertion (C11 6.7.10), without the trailing
   semicolon.

   static_assert-declaration-no-semi:
     _Static_assert ( constant-expression , string-literal )

   C23:
   static_assert-declaration-no-semi:
     _Static_assert ( constant-expression )
*/

స్థిర శూన్య
c_parser_static_assert_declaration_no_semi (c_parser *parser)
{
  location_t assert_loc, విలువ_loc;
  వృక్షం విలువ;
  వృక్షం string = NULL_వృక్షం;

  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_STATIC_ASSERT));
  వృక్షం spelling = c_parser_peek_token (parser)->విలువ;
  assert_loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (flag_isoc99)
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  లేకపోతే
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  c_parser_consume_token (parser);
  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి;
  location_t విలువ_tok_loc = c_parser_peek_token (parser)->location;
  విలువ = convert_lvalue_గమ్యం_rvalue (విలువ_tok_loc,
				    c_parser_సమాసం_no_commas (parser, ఖాళీ),
				    నిజం, నిజం).విలువ;
  విలువ_loc = సమాసం_LOC_OR_LOC (విలువ, విలువ_tok_loc);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ఎంపిక (c_parser_peek_token (parser)->type)
	{
	స్థితి CPP_STRING:
	స్థితి CPP_STRING16:
	స్థితి CPP_STRING32:
	స్థితి CPP_WSTRING:
	స్థితి CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, అబద్ధం, నిజం).విలువ;
	  ఆపు;
	అప్రమేయ:
	  c_parser_error (parser, "expected string literal");
	  తిరిగి;
	}
    }
  లేకపోతే ఒకవేళ (flag_isoc11)
    /* If pedantic for pre-C11, the use of _Static_assert itself will
       have been diagnosed, so do not also diagnose the use of this
       new C23 feature of _Static_assert.  */
    pedwarn_c11 (assert_loc, OPT_Wpedantic,
		 "ISO C11 does not support omitting the string in "
		 "%qE", spelling);
  parens.require_close (parser);

  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (విలువ)))
    {
      error_at (విలువ_loc, "expression in static assertion is not an integer");
      తిరిగి;
    }
  ఒకవేళ (వృక్షం_సంకేతం (విలువ) != INTEGER_CST)
    {
      విలువ = c_fully_fold (విలువ, అబద్ధం, ఖాళీ);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (విలువ);
      ఒకవేళ (వృక్షం_సంకేతం (విలువ) == INTEGER_CST)
	pedwarn (విలువ_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  ఒకవేళ (వృక్షం_సంకేతం (విలువ) != INTEGER_CST)
    {
      error_at (విలువ_loc, "expression in static assertion is not constant");
      తిరిగి;
    }
  constant_వ్యక్తీకరణ_warning (విలువ);
  ఒకవేళ (integer_zerop (విలువ))
    {
      ఒకవేళ (string)
	error_at (assert_loc, "static assertion failed: %E", string);
      లేకపోతే
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
రిజిస్టరు
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

శూన్య
c_parser_declspecs (c_parser *parser, నిర్మాణం c_declspecs *specs,
		    తార్కిక scspec_ok, తార్కిక typespec_ok, తార్కిక ప్రారంభం_attr_ok,
		    తార్కిక alignspec_ok, తార్కిక auto_type_ok,
		    తార్కిక ప్రారంభం_std_attr_ok, తార్కిక చివర_std_attr_ok,
		    గణన c_lookahead_రకం la)
{
  తార్కిక attrs_ok = ప్రారంభం_attr_ok;
  తార్కిక చూసిన_type = specs->typespec_రకం != ctsk_none;

  ఒకవేళ (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  ఒకవేళ (ప్రారంభం_std_attr_ok
      && c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_చూసిన_p);
      location_t loc = c_parser_peek_token (parser)->location;
      వృక్షం attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_కూడు_attrs (loc, specs, attrs);
      specs->non_std_attrs_చూసిన_p = అబద్ధం;
    }

  అయితే (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	 || c_parser_తదుపరి_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_తదుపరి_token_is (parser, CPP_LESS)))
    {
      నిర్మాణం c_typespec t;
      వృక్షం attrs;
      వృక్షం align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      ఒకవేళ ((!typespec_ok || specs->typespec_రకం == ctsk_tagdef)
	  && c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_typename (parser, la)
	  && !c_parser_తదుపరి_token_is_qualifier (parser)
	  && !c_parser_తదుపరి_token_is_keyword (parser, RID_ALIGNAS))
	ఆపు;

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  వృక్షం విలువ = name_token->విలువ;
	  c_id_రకం రకం = name_token->id_రకం;

	  ఒకవేళ (రకం == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_మొదటి_ADDR_SPACE;
	      declspecs_కూడు_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = నిజం;
	      కొనసాగు;
	    }

	  gcc_assert (!c_parser_తదుపరి_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  ఒకవేళ (చూసిన_type || !c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_typename (parser, la))
	    ఆపు;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  చూసిన_type = నిజం;
	  attrs_ok = నిజం;
	  ఒకవేళ (రకం == C_ID_ID)
	    {
	      auto_diagnostic_సమూహం d;
	      name_hint hint = lookup_name_fuzzy (విలువ, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      ఒకవేళ (స్థిరరాశి అక్షరం *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.కూడు_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    విలువ, suggestion);
		}
	      లేకపోతే
		error_at (loc, "unknown type name %qE", విలువ);
	      t.రకం = ctsk_typedef;
	      t.spec = error_mark_కణుపు;
	    }
	  లేకపోతే ఒకవేళ (రకం == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_తదుపరి_token_is_not (parser, CPP_LESS)))
	    {
	      t.రకం = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (విలువ);
	    }
	  లేకపోతే
	    {
	      వృక్షం proto = NULL_వృక్షం;
	      gcc_assert (c_dialect_objc ());
	      t.రకం = ctsk_objc;
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (విలువ, proto);
	    }
	  t.సమాసం = NULL_వృక్షం;
	  t.సమాసం_const_operands = నిజం;
	  t.has_enum_type_specifier = అబద్ధం;
	  declspecs_కూడు_type (name_token->location, specs, t);
	  కొనసాగు;
	}
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  వృక్షం proto;
	  gcc_assert (c_dialect_objc ());
	  ఒకవేళ (!typespec_ok || చూసిన_type)
	    ఆపు;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.రకం = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_వృక్షం, proto);
	  t.సమాసం = NULL_వృక్షం;
	  t.సమాసం_const_operands = నిజం;
	  t.has_enum_type_specifier = అబద్ధం;
	  declspecs_కూడు_type (loc, specs, t);
	  కొనసాగు;
	}
      gcc_assert (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD));
      ఎంపిక (c_parser_peek_token (parser)->keyword)
	{
	స్థితి RID_STATIC:
	స్థితి RID_EXTERN:
	స్థితి RID_రిజిస్టరు:
	స్థితి RID_TYPEDEF:
	స్థితి RID_INLINE:
	స్థితి RID_NORETURN:
	స్థితి RID_AUTO:
	స్థితి RID_THREAD:
	స్థితి RID_CONSTEXPR:
	  ఒకవేళ (!scspec_ok)
	    వెళ్ళు బహిర్గతం;
	  attrs_ok = నిజం;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_కూడు_scspec (loc, specs,
				c_parser_peek_token (parser)->విలువ);
	  c_parser_consume_token (parser);
	  ఆపు;
	స్థితి RID_AUTO_TYPE:
	  ఒకవేళ (!auto_type_ok)
	    వెళ్ళు బహిర్గతం;
	  /* Fall through.  */
	స్థితి RID_UNSIGNED:
	స్థితి RID_LONG:
	స్థితి RID_SHORT:
	స్థితి RID_SIGNED:
	స్థితి RID_COMPLEX:
	స్థితి RID_INT:
	స్థితి RID_CHAR:
	స్థితి RID_FLOAT:
	స్థితి RID_DOUBLE:
	స్థితి RID_VOID:
	స్థితి RID_DFLOAT32:
	స్థితి RID_DFLOAT64:
	స్థితి RID_DFLOAT128:
	స్థితి RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	స్థితి RID_BOOL:
	స్థితి RID_FRACT:
	స్థితి RID_ACCUM:
	స్థితి RID_SAT:
	స్థితి RID_INT_N_0:
	స్థితి RID_INT_N_1:
	స్థితి RID_INT_N_2:
	స్థితి RID_INT_N_3:
	  ఒకవేళ (!typespec_ok)
	    వెళ్ళు బహిర్గతం;
	  attrs_ok = నిజం;
	  చూసిన_type = నిజం;
	  ఒకవేళ (c_dialect_objc ())
	    parser->objc_need_raw_identifier = నిజం;
	  t.రకం = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->విలువ;
	  t.సమాసం = NULL_వృక్షం;
	  t.సమాసం_const_operands = నిజం;
	  t.has_enum_type_specifier = అబద్ధం;
	  declspecs_కూడు_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  ఆపు;
	స్థితి RID_ENUM:
	  ఒకవేళ (!typespec_ok)
	    వెళ్ళు బహిర్గతం;
	  attrs_ok = నిజం;
	  చూసిన_type = నిజం;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_ముగింపు_TYPE, t.spec);
	  declspecs_కూడు_type (loc, specs, t);
	  ఆపు;
	స్థితి RID_STRUCT:
	స్థితి RID_UNION:
	  ఒకవేళ (!typespec_ok)
	    వెళ్ళు బహిర్గతం;
	  attrs_ok = నిజం;
	  చూసిన_type = నిజం;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_ముగింపు_TYPE, t.spec);
	  declspecs_కూడు_type (loc, specs, t);
	  ఆపు;
	స్థితి RID_TYPEOF:
	స్థితి RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  ఒకవేళ (!typespec_ok || చూసిన_type)
	    వెళ్ళు బహిర్గతం;
	  attrs_ok = నిజం;
	  చూసిన_type = నిజం;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_కూడు_type (loc, specs, t);
	  ఆపు;
	స్థితి RID_BITINT:
	  ఒకవేళ (!typespec_ok)
	    వెళ్ళు బహిర్గతం;
	  లేకపోతే
	    {
	      attrs_ok = నిజం;
	      చూసిన_type = నిజం;
	      t.రకం = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->విలువ;
	      t.సమాసం = error_mark_కణుపు;
	      t.సమాసం_const_operands = నిజం;
	      t.has_enum_type_specifier = అబద్ధం;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      ఒకవేళ (parens.require_open (parser))
		{
		  c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
		  t.సమాసం = convert_lvalue_గమ్యం_rvalue (loc, సమాసం, నిజం,
						     నిజం).విలువ;
		  parens.skip_until_దొరికింది_close (parser);
		}
	      declspecs_కూడు_type (loc, specs, t);
	    }
	  ఆపు;
	స్థితి RID_ATOMIC:
	  /* C parser handling of Objective-C constructs needs
	     checking for correct lvalue-to-rvalue conversions, and
	     the code in build_modify_expr handling various
	     Objective-C cases, and that in build_unary_op handling
	     Objective-C cases for increment / decrement, also needs
	     updating; uses of TYPE_MAIN_VARIANT in objc_compare_types
	     and objc_types_are_equivalent may also need updates.  */
	  ఒకవేళ (c_dialect_objc ())
	    sorry ("%<_Atomic%> in Objective-C");
	  ఒకవేళ (flag_isoc99)
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C99 does not support the %<_Atomic%> qualifier");
	  లేకపోతే
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C90 does not support the %<_Atomic%> qualifier");
	  attrs_ok = నిజం;
	  వృక్షం విలువ;
	  విలువ = c_parser_peek_token (parser)->విలువ;
	  c_parser_consume_token (parser);
	  ఒకవేళ (typespec_ok && c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      చూసిన_type = నిజం;
	      c_parser_consume_token (parser);
	      నిర్మాణం c_type_name *type = c_parser_type_name (parser);
	      t.రకం = ctsk_typeof;
	      t.spec = error_mark_కణుపు;
	      t.సమాసం = NULL_వృక్షం;
	      t.సమాసం_const_operands = నిజం;
	      t.has_enum_type_specifier = అబద్ధం;
	      ఒకవేళ (type != ఖాళీ)
		t.spec = groktypename (type, &t.సమాసం,
				       &t.సమాసం_const_operands);
	      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      ఒకవేళ (t.spec != error_mark_కణుపు)
		{
		  ఒకవేళ (వృక్షం_సంకేతం (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  లేకపోతే ఒకవేళ (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  లేకపోతే
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_కూడు_type (loc, specs, t);
	    }
	  లేకపోతే
	    declspecs_కూడు_qual (loc, specs, విలువ);
	  ఆపు;
	స్థితి RID_CONST:
	స్థితి RID_VOLATILE:
	స్థితి RID_RESTRICT:
	  attrs_ok = నిజం;
	  declspecs_కూడు_qual (loc, specs, c_parser_peek_token (parser)->విలువ);
	  c_parser_consume_token (parser);
	  ఆపు;
	స్థితి RID_ATTRIBUTE:
	  ఒకవేళ (!attrs_ok)
	    వెళ్ళు బహిర్గతం;
	  attrs = c_parser_gnu_లక్షణాలు (parser);
	  declspecs_కూడు_attrs (loc, specs, attrs);
	  ఆపు;
	స్థితి RID_ALIGNAS:
	  ఒకవేళ (!alignspec_ok)
	    వెళ్ళు బహిర్గతం;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_కూడు_alignas (loc, specs, align);
	  ఆపు;
	స్థితి RID_GIMPLE:
	  ఒకవేళ (! flag_gimple)
	    error_at (loc, "%<__GIMPLE%> only valid with %<-fgimple%>");
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_gimple;
	  specs->locations[cdw_gimple] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  ఆపు;
	స్థితి RID_RTL:
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_rtl;
	  specs->locations[cdw_rtl] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  ఆపు;
	అప్రమేయ:
	  వెళ్ళు బహిర్గతం;
	}
    }
 బహిర్గతం:
  ఒకవేళ (చివర_std_attr_ok
      && c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
    specs->postfix_attrs = c_parser_std_attribute_specifier_sequence (parser);
}

/* Complain about a non-CPP_NAME within an enumerator list.  */

స్థిర శూన్య
report_bad_enum_name (c_parser *parser)
{
  ఒకవేళ (!parser->error)
    {
      c_token *token = c_parser_peek_token (parser);
      ఎంపిక (token->type)
	{
	అప్రమేయ:
	  ఆపు;
	స్థితి CPP_CLOSE_BRACE:
	  /* Give a nicer error for "enum {}".  */
	  error_at (token->location,
		    "empty enum is invalid");
	  parser->error = నిజం;
	  తిరిగి;
	స్థితి CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  ఒకవేళ (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_సమూహం d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_సూచిక (token->విలువ));
	      కూడు_note_about_new_keyword (token->location,
					  token->విలువ);
	      parser->error = నిజం;
	      తిరిగి;
	    }
	  ఆపు;
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

స్థిర నిర్మాణం c_typespec
c_parser_enum_specifier (c_parser *parser)
{
  నిర్మాణం c_typespec ret;
  తార్కిక have_std_attrs;
  తార్కిక potential_nesting_p = అబద్ధం;
  వృక్షం std_attrs = NULL_వృక్షం;
  వృక్షం attrs;
  వృక్షం ident = NULL_వృక్షం;
  వృక్షం fixed_underlying_type = NULL_వృక్షం;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_లక్షణాలు (parser, 1);
  ఒకవేళ (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_లక్షణాలు (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_సమితి_ఆధారం_position_from_token (c_parser_peek_token (parser));
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->విలువ;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON)
      /* Distinguish an enum-type-specifier from a bit-field
	 declaration of the form "enum e : constant-expression;".  */
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      pedwarn_c11 (enum_loc, OPT_Wpedantic,
		   "ISO C does not support specifying %<enum%> underlying "
		   "types before C23");
      ఒకవేళ (ident)
	{
	  /* The tag is in scope during the enum-type-specifier (which
	     may refer to the tag inside typeof).  */
	  ret = parser_xref_ట్యాగ్ (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, నిజం);
	  ఒకవేళ (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_వృక్షం == TYPE_విలువలు (ret.spec);
	}
      లేకపోతే
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_వృక్షం;
	  ret.రకం = ctsk_tagdef;
	  ret.సమాసం = NULL_వృక్షం;
	  ret.సమాసం_const_operands = నిజం;
	  ret.has_enum_type_specifier = నిజం;
	}
      c_parser_consume_token (parser);
      నిర్మాణం c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, అబద్ధం, నిజం, అబద్ధం, అబద్ధం, అబద్ధం,
			  అబద్ధం, నిజం, cla_prefer_id);
      ముగింపు_declspecs (specs);
      ఒకవేళ (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (specs->type) != INTEGER_TYPE
	       && వృక్షం_సంకేతం (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || వృక్షం_సంకేతం (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_కణుపు;
	}
      లేకపోతే ఒకవేళ (specs->restrict_p)
	error_at (enum_loc, "invalid use of %<restrict%>");
      fixed_underlying_type = TYPE_MAIN_VARIANT (specs->type);
      ఒకవేళ (ident)
	{
	  /* The type specified must be consistent with any previously
	     specified underlying type.  If this is a newly declared
	     type, it is now a complete type.  */
	  ఒకవేళ (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
	      && ENUM_UNDERLYING_TYPE (ret.spec) == NULL_వృక్షం)
	    {
	      TYPE_MIN_విలువ (ret.spec) =
		TYPE_MIN_విలువ (fixed_underlying_type);
	      TYPE_MAX_విలువ (ret.spec) =
		TYPE_MAX_విలువ (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      సమితి_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_కొలత (ret.spec) = NULL_వృక్షం;
	      TYPE_PRECISION (ret.spec) =
		TYPE_PRECISION (fixed_underlying_type);
	      ENUM_UNDERLYING_TYPE (ret.spec) = fixed_underlying_type;
	      layout_type (ret.spec);
	    }
	  లేకపోతే ఒకవేళ (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
		   && !comptypes (fixed_underlying_type,
				  ENUM_UNDERLYING_TYPE (ret.spec)))
	    {
	      error_at (enum_loc, "%<enum%> underlying type incompatible with "
			"previous declaration");
	      fixed_underlying_type = ENUM_UNDERLYING_TYPE (ret.spec);
	    }
	}
    }
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      నిర్మాణం c_enum_contents the_enum;
      వృక్షం type;
      వృక్షం postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      వృక్షం విలువలు;
      timevar_నెట్టు (TV_PARSE_ENUM);
      type = ప్రారంభం_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      విలువలు = NULL_వృక్షం;
      c_parser_consume_token (parser);
      అయితే (నిజం)
	{
	  వృక్షం enum_id;
	  వృక్షం enum_విలువ;
	  వృక్షం enum_decl;
	  తార్కిక చూసిన_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, విలువ_loc;
	  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_BRACE, ఖాళీ);
	      విలువలు = error_mark_కణుపు;
	      ఆపు;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->విలువ;
	  /* Set the location in case we create a decl now.  */
	  c_parser_సమితి_ఆధారం_position_from_token (token);
	  decl_loc = విలువ_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  వృక్షం std_attrs = NULL_వృక్షం;
	  ఒకవేళ (c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  వృక్షం enum_attrs = chainon (std_attrs,
				     c_parser_gnu_లక్షణాలు (parser));
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      విలువ_loc = c_parser_peek_token (parser)->location;
	      enum_విలువ = convert_lvalue_గమ్యం_rvalue (విలువ_loc,
						     (c_parser_సమాసం_no_commas
						      (parser, ఖాళీ)),
						     నిజం, నిజం).విలువ;
	    }
	  లేకపోతే
	    enum_విలువ = NULL_వృక్షం;
	  enum_decl = build_enumerator (decl_loc, విలువ_loc,
					&the_enum, enum_id, enum_విలువ);
	  ఒకవేళ (enum_attrs)
	    decl_లక్షణాలు (&వృక్షం_PURPOSE (enum_decl), enum_attrs, 0);
	  వృక్షం_CHAIN (enum_decl) = విలువలు;
	  విలువలు = enum_decl;
	  చూసిన_comma = అబద్ధం;
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      చూసిన_comma = నిజం;
	      c_parser_consume_token (parser);
	    }
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      ఒకవేళ (చూసిన_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      ఆపు;
	    }
	  ఒకవేళ (!చూసిన_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_BRACE, ఖాళీ);
	      విలువలు = error_mark_కణుపు;
	      ఆపు;
	    }
	}
      postfix_attrs = c_parser_gnu_లక్షణాలు (parser);
      ret.spec = ముగింపు_enum (type, nreverse (విలువలు),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.రకం = ctsk_tagdef;
      ret.సమాసం = NULL_వృక్షం;
      ret.సమాసం_const_operands = నిజం;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_వృక్షం;
      timevar_తీయి (TV_PARSE_ENUM);
      తిరిగి ret;
    }
  లేకపోతే ఒకవేళ (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_కణుపు;
      ret.రకం = ctsk_tagref;
      ret.సమాసం = NULL_వృక్షం;
      ret.సమాసం_const_operands = నిజం;
      ret.has_enum_type_specifier = అబద్ధం;
      తిరిగి ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  ఒకవేళ (have_std_attrs && c_parser_తదుపరి_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  ఒకవేళ (fixed_underlying_type == NULL_వృక్షం)
    {
      ret = parser_xref_ట్యాగ్ (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
			     std_attrs, అబద్ధం);
      /* In ISO C, enumerated types without a fixed underlying type
	 can be referred to only if already defined.  */
      ఒకవేళ (pedantic && !COMPLETE_TYPE_P (ret.spec))
	{
	  gcc_assert (ident);
	  pedwarn (enum_loc, OPT_Wpedantic,
		   "ISO C forbids forward references to %<enum%> types");
	}
    }
  తిరిగి ret;
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
ఖాళీలు
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

స్థిర నిర్మాణం c_typespec
c_parser_struct_or_union_specifier (c_parser *parser)
{
  నిర్మాణం c_typespec ret;
  తార్కిక have_std_attrs;
  వృక్షం std_attrs = NULL_వృక్షం;
  వృక్షం attrs;
  వృక్షం ident = NULL_వృక్షం;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  గణన వృక్షం_సంకేతం_2 సంకేతం_2;
  ఎంపిక (c_parser_peek_token (parser)->keyword)
    {
    స్థితి RID_STRUCT:
      సంకేతం_2 = రికార్డు_TYPE;
      ఆపు;
    స్థితి RID_UNION:
      సంకేతం_2 = UNION_TYPE;
      ఆపు;
    అప్రమేయ:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_లక్షణాలు (parser, 1);
  ఒకవేళ (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_లక్షణాలు (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_సమితి_ఆధారం_position_from_token (c_parser_peek_token (parser));

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->విలువ;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      తరగతి c_struct_parse_info *struct_info;
      వృక్షం type = ప్రారంభం_struct (struct_loc, సంకేతం_2, ident, &struct_info);
      వృక్షం postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      వృక్షం contents;
      వృక్షం సమాసం = ఖాళీ;
      timevar_నెట్టు (TV_PARSE_STRUCT);
      contents = NULL_వృక్షం;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_DEFS))
	{
	  వృక్షం name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  ఒకవేళ (!parens.require_open (parser))
	    వెళ్ళు చివర_at_defs;
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_రకం == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->విలువ;
	      c_parser_consume_token (parser);
	    }
	  లేకపోతే
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
	      వెళ్ళు చివర_at_defs;
	    }
	  parens.skip_until_దొరికింది_close (parser);
	  contents = nreverse (objc_get_class_ivars (name));
	}
    చివర_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      అయితే (నిజం)
	{
	  వృక్షం decls;
	  /* Parse any stray semicolon.  */
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
	    {
	      location_t semicolon_loc
		= c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (semicolon_loc);
	      richloc.కూడు_fixit_remove ();
	      pedwarn (&richloc, OPT_Wpedantic,
		       "extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      కొనసాగు;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      ఆపు;
	    }
	  /* Accept #pragmas at struct scope.  */
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, ఖాళీ, NULL_వృక్షం);
	      కొనసాగు;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &సమాసం);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  లేకపోతే
	    {
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      లేకపోతే ఒకవేళ (parser->error
		       || !c_parser_తదుపరి_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_BRACE, ఖాళీ);
		  ఆపు;
		}

	      /* If we come here, we have already emitted an error
		 for an expected `;', identifier or `(', and we also
	         recovered already.  Go on with the next field. */
	    }
	}
      postfix_attrs = c_parser_gnu_లక్షణాలు (parser);
      ret.spec = ముగింపు_struct (struct_loc, type, nreverse (contents),
				chainon (std_attrs,
					 chainon (attrs, postfix_attrs)),
				struct_info, &సమాసం);
      ret.రకం = ctsk_tagdef;
      ret.సమాసం = సమాసం;
      ret.సమాసం_const_operands = నిజం;
      ret.has_enum_type_specifier = అబద్ధం;
      timevar_తీయి (TV_PARSE_STRUCT);
      తిరిగి ret;
    }
  లేకపోతే ఒకవేళ (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_కణుపు;
      ret.రకం = ctsk_tagref;
      ret.సమాసం = NULL_వృక్షం;
      ret.సమాసం_const_operands = నిజం;
      ret.has_enum_type_specifier = అబద్ధం;
      తిరిగి ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  ఒకవేళ (have_std_attrs && c_parser_తదుపరి_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_ట్యాగ్ (ident_loc, సంకేతం_2, ident, have_std_attrs, std_attrs,
			 అబద్ధం);
  తిరిగి ret;
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

స్థిర వృక్షం
c_parser_struct_declaration (c_parser *parser, వృక్షం *సమాసం)
{
  నిర్మాణం c_declspecs *specs;
  వృక్షం ఉపసర్గ_attrs;
  వృక్షం all_ఉపసర్గ_attrs;
  వృక్షం decls;
  location_t decl_loc;
  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_EXTENSION))
    {
      పూర్ణాంకం ext;
      వృక్షం decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, సమాసం);
      restore_extension_diagnostics (ext);
      తిరిగి decl;
    }
  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      తిరిగి NULL_వృక్షం;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, అబద్ధం, నిజం, నిజం,
		      నిజం, అబద్ధం, నిజం, నిజం, cla_nonabstract_decl);
  ఒకవేళ (parser->error)
    తిరిగి NULL_వృక్షం;
  ఒకవేళ (!specs->declspecs_చూసిన_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      తిరిగి NULL_వృక్షం;
    }
  ముగింపు_declspecs (specs);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON)
      || c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
    {
      వృక్షం ret;
      ఒకవేళ (specs->typespec_రకం == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_ట్యాగ్_warned (specs, pedantic);
	  ret = NULL_వృక్షం;
	}
      లేకపోతే
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  వృక్షం attrs = ఖాళీ;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_వృక్షం), specs,
			   NULL_వృక్షం, &attrs, సమాసం);
	  ఒకవేళ (ret)
	    decl_లక్షణాలు (&ret, attrs, 0);
	}
      తిరిగి ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  ఒకవేళ (specs->typespec_రకం == ctsk_tagdef
      && వృక్షం_సంకేతం (specs->type) != ENUMERAL_TYPE
      && c_parser_తదుపరి_token_starts_declspecs (parser)
      && !c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = అబద్ధం;
      తిరిగి NULL_వృక్షం;
    }

  pending_xref_error ();
  ఉపసర్గ_attrs = specs->attrs;
  all_ఉపసర్గ_attrs = ఉపసర్గ_attrs;
  specs->attrs = NULL_వృక్షం;
  decls = NULL_వృక్షం;
  అయితే (నిజం)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      నిర్మాణం c_declarator *declarator;
      తార్కిక dummy = అబద్ధం;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_వృక్షం);
      లేకపోతే
	declarator = c_parser_declarator (parser,
					  specs->typespec_రకం != ctsk_none,
					  C_DTR_సాధారణ, &dummy);
      ఒకవేళ (declarator == ఖాళీ)
	{
	  c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
	  ఆపు;
	}
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON)
	  || c_parser_తదుపరి_token_is (parser, CPP_COMMA)
	  || c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON)
	  || c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_తదుపరి_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  వృక్షం postfix_attrs = NULL_వృక్షం;
	  వృక్షం వెడల్పు = NULL_వృక్షం;
	  వృక్షం d;
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      వెడల్పు = convert_lvalue_గమ్యం_rvalue (loc,
						(c_parser_సమాసం_no_commas
						 (parser, ఖాళీ)),
						నిజం, నిజం).విలువ;
	    }
	  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_లక్షణాలు (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, వెడల్పు, &all_ఉపసర్గ_attrs, సమాసం);
	  decl_లక్షణాలు (&d, chainon (postfix_attrs,
					all_ఉపసర్గ_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_ఉపసర్గ_attrs = chainon (c_parser_gnu_లక్షణాలు (parser),
					ఉపసర్గ_attrs);
	  లేకపోతే
	    all_ఉపసర్గ_attrs = ఉపసర్గ_attrs;
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON)
		   || c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      /* Semicolon consumed in caller.  */
	      ఆపు;
	    }
	  లేకపోతే
	    {
	      c_parser_error (parser, "expected %<,%>, %<;%> or %<}%>");
	      ఆపు;
	    }
	}
      లేకపోతే
	{
	  c_parser_error (parser,
			  "expected %<:%>, %<,%>, %<;%>, %<}%> or "
			  "%<__attribute__%>");
	  ఆపు;
	}
    }
  తిరిగి decls;
}

/* Parse a typeof specifier (a GNU extension adopted in C23).

   typeof-specifier:
     typeof ( expression )
     typeof ( type-name )
     typeof_unqual ( expression )
     typeof_unqual ( type-name )
*/

స్థిర నిర్మాణం c_typespec
c_parser_typeof_specifier (c_parser *parser)
{
  తార్కిక is_unqual;
  తార్కిక is_std;
  నిర్మాణం c_typespec ret;
  ret.రకం = ctsk_typeof;
  ret.spec = error_mark_కణుపు;
  ret.సమాసం = NULL_వృక్షం;
  ret.సమాసం_const_operands = నిజం;
  ret.has_enum_type_specifier = అబద్ధం;
  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = అబద్ధం;
      వృక్షం spelling = c_parser_peek_token (parser)->విలువ;
      is_std = (flag_isoc23
		&& strcmp (IDENTIFIER_సూచిక (spelling), "typeof") == 0);
    }
  లేకపోతే
    {
      gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = నిజం;
      వృక్షం spelling = c_parser_peek_token (parser)->విలువ;
      is_std = strcmp (IDENTIFIER_సూచిక (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  లోపల_typeof++;
  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      లోపల_typeof--;
      తిరిగి ret;
    }
  ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_typename (parser, cla_prefer_id))
    {
      నిర్మాణం c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      లోపల_typeof--;
      ఒకవేళ (type != ఖాళీ)
	{
	  ret.spec = groktypename (type, &ret.సమాసం, &ret.సమాసం_const_operands);
	  తీయి_maybe_వాడిన (c_type_variably_modified_p (ret.spec));
	}
    }
  లేకపోతే
    {
      తార్కిక was_vm;
      location_t ఇక్కడ = c_parser_peek_token (parser)->location;
      నిర్మాణం c_సమాసం సమాసం = c_parser_వ్యక్తీకరణ (parser);
      c_inhibit_evaluation_warnings--;
      లోపల_typeof--;
      ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) == COMPONENT_REF
	  && DECL_C_బిట్టు_క్షేత్రం (వృక్షం_నిర్వాహ్యం (సమాసం.విలువ, 1)))
	error_at (ఇక్కడ, "%<typeof%> applied to a bit-field");
      mark_exp_read (సమాసం.విలువ);
      ret.spec = వృక్షం_TYPE (సమాసం.విలువ);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      ఒకవేళ (was_vm)
	ret.సమాసం = c_fully_fold (సమాసం.విలువ, అబద్ధం, &ret.సమాసం_const_operands);
      తీయి_maybe_వాడిన (was_vm);
    }
  parens.skip_until_దొరికింది_close (parser);
  ఒకవేళ (ret.spec != error_mark_కణుపు)
    {
      ఒకవేళ (is_unqual)
	{
	  తార్కిక is_array = వృక్షం_సంకేతం (ret.spec) == ARRAY_TYPE;
	  పూర్ణాంకం quals = TYPE_QUALS (strip_array_types (ret.spec));
	  ఒకవేళ ((is_array ? quals & ~TYPE_QUAL_ATOMIC : quals)
	      != TYPE_UNQUALIFIED)
	    {
	      ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	      ఒకవేళ (quals & TYPE_QUAL_ATOMIC && is_array)
		ret.spec = c_build_qualified_type (ret.spec,
						   TYPE_QUAL_ATOMIC);
	    }
	}
      ఒకవేళ (is_std)
	{
	  /* In ISO C terms, _Noreturn is not part of the type of
	     expressions such as &abort, but in GCC it is represented
	     internally as a type qualifier.  */
	  ఒకవేళ (వృక్షం_సంకేతం (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  లేకపోతే ఒకవేళ (FUNCTION_సూచిక_TYPE_P (ret.spec)
		   && TYPE_QUALS (వృక్షం_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_సూచిక_type (TYPE_MAIN_VARIANT (వృక్షం_TYPE (ret.spec)));
	}
    }
  తిరిగి ret;
}

/* Parse an alignment-specifier.

   C11 6.7.5:

   alignment-specifier:
     _Alignas ( type-name )
     _Alignas ( constant-expression )
*/

స్థిర వృక్షం
c_parser_alignas_specifier (c_parser * parser)
{
  వృక్షం ret = error_mark_కణుపు;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_ALIGNAS));
  వృక్షం spelling = c_parser_peek_token (parser)->విలువ;
  c_parser_consume_token (parser);
  ఒకవేళ (flag_isoc99)
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  లేకపోతే
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి ret;
  ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_typename (parser, cla_prefer_id))
    {
      నిర్మాణం c_type_name *type = c_parser_type_name (parser);
      ఒకవేళ (type != ఖాళీ)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, ఖాళీ, ఖాళీ),
					అబద్ధం, నిజం, 1);
    }
  లేకపోతే
    ret = convert_lvalue_గమ్యం_rvalue (loc,
				    c_parser_సమాసం_no_commas (parser, ఖాళీ),
				    నిజం, నిజం).విలువ;
  parens.skip_until_దొరికింది_close (parser);
  తిరిగి ret;
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
సూచిక
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

నిర్మాణం c_declarator *
c_parser_declarator (c_parser *parser, తార్కిక type_చూసిన_p, c_dtr_syn రకం,
		     తార్కిక *చూసిన_id)
{
  /* Parse any initial pointer part.  */
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_MULT))
    {
      నిర్మాణం c_declspecs *quals_attrs = build_null_declspecs ();
      నిర్మాణం c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, అబద్ధం, అబద్ధం, నిజం,
			  అబద్ధం, అబద్ధం, నిజం, అబద్ధం, cla_prefer_id);
      inner = c_parser_declarator (parser, type_చూసిన_p, రకం, చూసిన_id);
      ఒకవేళ (inner == ఖాళీ)
	తిరిగి ఖాళీ;
      లేకపోతే
	తిరిగి make_సూచిక_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  తిరిగి c_parser_ప్రత్యక్ష_declarator (parser, type_చూసిన_p, రకం, చూసిన_id);
}

/* Parse a direct declarator or direct abstract declarator; arguments
   as c_parser_declarator.  */

స్థిర నిర్మాణం c_declarator *
c_parser_ప్రత్యక్ష_declarator (c_parser *parser, తార్కిక type_చూసిన_p, c_dtr_syn రకం,
			    తార్కిక *చూసిన_id)
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

  ఒకవేళ (రకం != C_DTR_ABSTRACT
      && c_parser_తదుపరి_token_is (parser, CPP_NAME)
      && ((type_చూసిన_p
	   && (c_parser_peek_token (parser)->id_రకం == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_రకం == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_రకం == C_ID_ID))
    {
      నిర్మాణం c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->విలువ);
      *చూసిన_id = నిజం;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      తిరిగి c_parser_ప్రత్యక్ష_declarator_inner (parser, *చూసిన_id, inner);
    }

  ఒకవేళ (రకం != C_DTR_సాధారణ
      && c_parser_తదుపరి_token_is (parser, CPP_OPEN_వర్గం)
      && !c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
    {
      నిర్మాణం c_declarator *inner = build_id_declarator (NULL_వృక్షం);
      inner->id_loc = c_parser_peek_token (parser)->location;
      తిరిగి c_parser_ప్రత్యక్ష_declarator_inner (parser, *చూసిన_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      వృక్షం attrs;
      నిర్మాణం c_declarator *inner;
      c_parser_consume_token (parser);
      తార్కిక have_gnu_attrs = c_parser_తదుపరి_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_లక్షణాలు (parser);
      ఒకవేళ (రకం != C_DTR_సాధారణ
	  && (c_parser_తదుపరి_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_లక్షణాలు (parser, 1)
		      || c_parser_తదుపరి_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  నిర్మాణం c_arg_info *వాదనలు
	    = c_parser_parms_declarator (parser, రకం == C_DTR_సాధారణ,
					 attrs, have_gnu_attrs);
	  ఒకవేళ (వాదనలు == ఖాళీ)
	    తిరిగి ఖాళీ;
	  లేకపోతే
	    {
	      inner = build_id_declarator (NULL_వృక్షం);
	      ఒకవేళ (!(వాదనలు->types
		    && వాదనలు->types != error_mark_కణుపు
		    && వృక్షం_సంకేతం (వృక్షం_విలువ (వాదనలు->types)) == IDENTIFIER_కణుపు)
		  && c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
		{
		  వృక్షం std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  ఒకవేళ (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (వాదనలు, inner);
	      తిరిగి c_parser_ప్రత్యక్ష_declarator_inner (parser, *చూసిన_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_చూసిన_p, రకం, చూసిన_id);
      ఒకవేళ (inner != ఖాళీ && attrs != ఖాళీ)
	inner = build_attrs_declarator (attrs, inner);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  ఒకవేళ (inner == ఖాళీ)
	    తిరిగి ఖాళీ;
	  లేకపోతే
	    తిరిగి c_parser_ప్రత్యక్ష_declarator_inner (parser, *చూసిన_id, inner);
	}
      లేకపోతే
	{
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  తిరిగి ఖాళీ;
	}
    }
  లేకపోతే
    {
      ఒకవేళ (రకం == C_DTR_సాధారణ)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  తిరిగి ఖాళీ;
	}
      లేకపోతే
	తిరిగి build_id_declarator (NULL_వృక్షం);
    }
}

/* Parse part of a direct declarator or direct abstract declarator,
   given that some (in INNER) has already been parsed; ID_PRESENT is
   true if an identifier is present, false for an abstract
   declarator.  */

స్థిర నిర్మాణం c_declarator *
c_parser_ప్రత్యక్ష_declarator_inner (c_parser *parser, తార్కిక id_present,
				  నిర్మాణం c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_వర్గం)
      && !c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      నిర్మాణం c_declarator *declarator;
      నిర్మాణం c_declspecs *quals_attrs = build_null_declspecs ();
      నిర్మాణం c_సమాసం dimen;
      dimen.విలువ = NULL_వృక్షం;
      dimen.original_సంకేతం = ERROR_MARK;
      dimen.original_type = NULL_వృక్షం;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, అబద్ధం, అబద్ధం, నిజం,
			  అబద్ధం, అబద్ధం, అబద్ధం, అబద్ధం, cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  ఒకవేళ (!quals_attrs->declspecs_చూసిన_p)
	    c_parser_declspecs (parser, quals_attrs, అబద్ధం, అబద్ధం, నిజం,
				అబద్ధం, అబద్ధం, అబద్ధం, అబద్ధం, cla_prefer_id);
	}
      ఒకవేళ (!quals_attrs->declspecs_చూసిన_p)
	quals_attrs = ఖాళీ;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      స్థిరరాశి తార్కిక static_చూసిన = (static_loc != UNKNOWN_LOCATION);
      తార్కిక నక్షత్రం_చూసిన = అబద్ధం;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_వర్గం)
	{
	  నక్షత్రం_చూసిన = నిజం;
	  c_parser_consume_token (parser);
	}
      లేకపోతే ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_CLOSE_వర్గం))
	dimen = c_parser_సమాసం_no_commas (parser, ఖాళీ);

      ఒకవేళ (static_చూసిన)
	{
	  ఒకవేళ (నక్షత్రం_చూసిన)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      నక్షత్రం_చూసిన = అబద్ధం;
	      dimen.విలువ = error_mark_కణుపు;
	    }
	  లేకపోతే ఒకవేళ (!dimen.విలువ)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_వర్గం))
	c_parser_consume_token (parser);
      లేకపోతే
	{
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_వర్గం,
				     "expected %<]%>");
	  తిరిగి ఖాళీ;
	}
      ఒకవేళ (dimen.విలువ)
	dimen = convert_lvalue_గమ్యం_rvalue (brace_loc, dimen, నిజం, నిజం);
      declarator = build_array_declarator (brace_loc, dimen.విలువ, quals_attrs,
					   static_చూసిన, నక్షత్రం_చూసిన);
      ఒకవేళ (declarator == ఖాళీ)
	తిరిగి ఖాళీ;
      ఒకవేళ (c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
	{
	  వృక్షం std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  ఒకవేళ (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = సమితి_array_declarator_inner (declarator, inner);
      తిరిగి c_parser_ప్రత్యక్ష_declarator_inner (parser, id_present, inner);
    }
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      వృక్షం attrs;
      నిర్మాణం c_arg_info *వాదనలు;
      c_parser_consume_token (parser);
      తార్కిక have_gnu_attrs = c_parser_తదుపరి_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_లక్షణాలు (parser);
      వాదనలు = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      ఒకవేళ (వాదనలు == ఖాళీ)
	తిరిగి ఖాళీ;
      లేకపోతే
	{
	  ఒకవేళ (!(వాదనలు->types
		&& వాదనలు->types != error_mark_కణుపు
		&& వృక్షం_సంకేతం (వృక్షం_విలువ (వాదనలు->types)) == IDENTIFIER_కణుపు)
	      && c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
	    {
	      వృక్షం std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      ఒకవేళ (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (వాదనలు, inner);
	  తిరిగి c_parser_ప్రత్యక్ష_declarator_inner (parser, id_present, inner);
	}
    }
  తిరిగి inner;
}

/* Parse a parameter list or identifier list, including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list.  ID_LIST_OK is true if an identifier list
   is acceptable; such a list must not have attributes at the start.
   HAVE_GNU_ATTRS says whether any gnu-attributes (including empty
   attributes) were present (in which case standard attributes cannot
   occur).  */

స్థిర నిర్మాణం c_arg_info *
c_parser_parms_declarator (c_parser *parser, తార్కిక id_list_ok, వృక్షం attrs,
			   తార్కిక have_gnu_attrs)
{
  నెట్టు_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  ఒకవేళ (id_list_ok
      && !attrs
      && c_parser_తదుపరి_token_is (parser, CPP_NAME)
      && c_parser_peek_token (parser)->id_రకం == C_ID_ID

      /* Look ahead to detect typos in type names.  */
      && c_parser_peek_2nd_token (parser)->type != CPP_NAME
      && c_parser_peek_2nd_token (parser)->type != CPP_MULT
      && c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
      && c_parser_peek_2nd_token (parser)->type != CPP_OPEN_వర్గం
      && c_parser_peek_2nd_token (parser)->type != CPP_KEYWORD)
    {
      వృక్షం list = NULL_వృక్షం, *nextp = &list;
      అయితే (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_రకం == C_ID_ID)
	{
	  *nextp = build_వృక్షం_list (NULL_వృక్షం,
				    c_parser_peek_token (parser)->విలువ);
	  nextp = & వృక్షం_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_COMMA))
	    ఆపు;
	  c_parser_consume_token (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      ఆపు;
	    }
	}
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	{
	  నిర్మాణం c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  తీయి_scope ();
	  తిరిగి ret;
	}
      లేకపోతే
	{
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  తీయి_scope ();
	  తిరిగి ఖాళీ;
	}
    }
  లేకపోతే
    {
      నిర్మాణం c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, ఖాళీ, have_gnu_attrs);
      తీయి_scope ();
      తిరిగి ret;
    }
}

/* Parse a parameter list (possibly empty), including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list; if HAVE_GNU_ATTRS, there were some such
   attributes (possibly empty, in which case ATTRS is NULL_TREE),
   which means standard attributes cannot start the list.  EXPR is
   NULL or an expression that needs to be evaluated for the side
   effects of array size expressions in the parameters.  */

స్థిర నిర్మాణం c_arg_info *
c_parser_parms_list_declarator (c_parser *parser, వృక్షం attrs, వృక్షం సమాసం,
				తార్కిక have_gnu_attrs)
{
  తార్కిక bad_parm = అబద్ధం;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
    {
      నిర్మాణం c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      తిరిగి ret;
    }
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      నిర్మాణం c_arg_info *ret = build_arg_info ();

      ret->types = NULL_వృక్షం;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_వాదనలు_stdarg_p = నిజం;
	  c_parser_consume_token (parser);
	  తిరిగి ret;
	}
      లేకపోతే
	{
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  తిరిగి ఖాళీ;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  అయితే (నిజం)
    {
      /* Parse a parameter.  */
      నిర్మాణం c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_వృక్షం;
      have_gnu_attrs = అబద్ధం;
      ఒకవేళ (parm == ఖాళీ)
	bad_parm = నిజం;
      లేకపోతే
	నెట్టు_parm_decl (parm, &సమాసం);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
	{
	  వృక్షం new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  తార్కిక new_have_gnu_attrs
	    = c_parser_తదుపరి_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_లక్షణాలు (parser);
	  తిరిగి c_parser_parms_list_declarator (parser, new_attrs, సమాసం,
						 new_have_gnu_attrs);
	}
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  ఒకవేళ (bad_parm)
	    తిరిగి ఖాళీ;
	  లేకపోతే
	    తిరిగి get_parm_info (అబద్ధం, సమాసం);
	}
      ఒకవేళ (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, అబద్ధం))
	{
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
	  తిరిగి ఖాళీ;
	}
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      ఒకవేళ (bad_parm)
		తిరిగి ఖాళీ;
	      లేకపోతే
		తిరిగి get_parm_info (నిజం, సమాసం);
	    }
	  లేకపోతే
	    {
	      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      తిరిగి ఖాళీ;
	    }
	}
    }
}

/* Parse a parameter declaration.  ATTRS are the gnu-attributes at the
   start of the declaration if it is the first parameter;
   HAVE_GNU_ATTRS is true if there were any gnu-attributes there (even
   empty) there.  */

స్థిర నిర్మాణం c_parm *
c_parser_parameter_declaration (c_parser *parser, వృక్షం attrs,
				తార్కిక have_gnu_attrs)
{
  నిర్మాణం c_declspecs *specs;
  నిర్మాణం c_declarator *declarator;
  వృక్షం ఉపసర్గ_attrs;
  వృక్షం postfix_attrs = NULL_వృక్షం;
  తార్కిక dummy = అబద్ధం;

  /* Accept #pragmas between parameter declarations.  */
  అయితే (c_parser_తదుపరి_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, ఖాళీ, NULL_వృక్షం);

  ఒకవేళ (!c_parser_తదుపరి_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      ఒకవేళ (parser->error)
	తిరిగి ఖాళీ;
      c_parser_సమితి_ఆధారం_position_from_token (token);
      ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_సమూహం d;
	  name_hint hint = lookup_name_fuzzy (token->విలువ,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  ఒకవేళ (స్థిరరాశి అక్షరం *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.కూడు_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->విలువ, suggestion);
	    }
	  లేకపోతే
	    error_at (token->location, "unknown type name %qE", token->విలువ);
	  parser->error = నిజం;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      లేకపోతే
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_గమ్యం_చివర_యొక్క_parameter (parser);
      తిరిగి ఖాళీ;
    }

  location_t ప్రారంభం_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  ఒకవేళ (attrs)
    {
      declspecs_కూడు_attrs (ఆదానం_location, specs, attrs);
      attrs = NULL_వృక్షం;
    }
  c_parser_declspecs (parser, specs, నిజం, నిజం, నిజం, నిజం, అబద్ధం,
		      !have_gnu_attrs, నిజం, cla_nonabstract_decl);
  ముగింపు_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  ఒకవేళ (specs->typespec_రకం == ctsk_tagdef)
    verify_counted_by_for_శిఖరం_anonymous_type (specs->type);

  pending_xref_error ();
  ఉపసర్గ_attrs = specs->attrs;
  specs->attrs = NULL_వృక్షం;
  declarator = c_parser_declarator (parser,
				    specs->typespec_రకం != ctsk_none,
				    C_DTR_PARM, &dummy);
  ఒకవేళ (declarator == ఖాళీ)
    {
      c_parser_skip_until_దొరికింది (parser, CPP_COMMA, ఖాళీ);
      తిరిగి ఖాళీ;
    }
  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_ATTRIBUTE))
    postfix_attrs = c_parser_gnu_లక్షణాలు (parser);

  /* Generate a location for the parameter, ranging from the start of the
     initial token to the end of the final token.

     If we have a identifier, then use it for the caret location, e.g.

       extern int callee (int one, int (*two)(int, int), float three);
                                   ~~~~~~^~~~~~~~~~~~~~

     otherwise, reuse the start location for the caret location e.g.:

       extern int callee (int one, int (*)(int, int), float three);
                                   ^~~~~~~~~~~~~~~~~
  */
  location_t చివర_loc = parser->చివరి_token_location;

  /* Find any cdk_id declarator; determine if we have an identifier.  */
  c_declarator *id_declarator = declarator;
  అయితే (id_declarator && id_declarator->రకం != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : ప్రారంభం_loc);
  location_t param_loc = make_location (caret_loc, ప్రారంభం_loc, చివర_loc);

  తిరిగి build_c_parm (specs, chainon (postfix_attrs, ఉపసర్గ_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

స్థిర వృక్షం
c_parser_asm_string_literal (c_parser *parser)
{
  వృక్షం str;
  పూర్ణాంకం save_flag = warn_overlength_అక్షరశ్రేణులు;
  warn_overlength_అక్షరశ్రేణులు = 0;
  str = c_parser_string_literal (parser, అబద్ధం, అబద్ధం).విలువ;
  warn_overlength_అక్షరశ్రేణులు = save_flag;
  తిరిగి str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

స్థిర వృక్షం
c_parser_simple_asm_సమాసం (c_parser *parser)
{
  వృక్షం str;
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి NULL_వృక్షం;
  str = c_parser_asm_string_literal (parser);
  ఒకవేళ (!parens.require_close (parser))
    {
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
      తిరిగి NULL_వృక్షం;
    }
  తిరిగి str;
}

స్థిర వృక్షం
c_parser_gnu_attribute_any_మాట (c_parser *parser)
{
  వృక్షం attr_name = NULL_వృక్షం;

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD))
    {
      /* ??? See comment above about what keywords are accepted here.  */
      తార్కిక ok;
      ఎంపిక (c_parser_peek_token (parser)->keyword)
	{
	స్థితి RID_STATIC:
	స్థితి RID_UNSIGNED:
	స్థితి RID_LONG:
	స్థితి RID_CONST:
	స్థితి RID_EXTERN:
	స్థితి RID_రిజిస్టరు:
	స్థితి RID_TYPEDEF:
	స్థితి RID_SHORT:
	స్థితి RID_INLINE:
	స్థితి RID_NORETURN:
	స్థితి RID_VOLATILE:
	స్థితి RID_SIGNED:
	స్థితి RID_AUTO:
	స్థితి RID_RESTRICT:
	స్థితి RID_COMPLEX:
	స్థితి RID_THREAD:
	స్థితి RID_INT:
	స్థితి RID_CHAR:
	స్థితి RID_FLOAT:
	స్థితి RID_DOUBLE:
	స్థితి RID_VOID:
	స్థితి RID_DFLOAT32:
	స్థితి RID_DFLOAT64:
	స్థితి RID_DFLOAT128:
	స్థితి RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	స్థితి RID_BOOL:
	స్థితి RID_BITINT:
	స్థితి RID_FRACT:
	స్థితి RID_ACCUM:
	స్థితి RID_SAT:
	స్థితి RID_TRANSACTION_ATOMIC:
	స్థితి RID_TRANSACTION_CANCEL:
	స్థితి RID_ATOMIC:
	స్థితి RID_AUTO_TYPE:
	స్థితి RID_CONSTEXPR:
	స్థితి RID_INT_N_0:
	స్థితి RID_INT_N_1:
	స్థితి RID_INT_N_2:
	స్థితి RID_INT_N_3:
	  ok = నిజం;
	  ఆపు;
	అప్రమేయ:
	  ok = అబద్ధం;
	  ఆపు;
	}
      ఒకవేళ (!ok)
	తిరిగి NULL_వృక్షం;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(పూర్ణాంకం) c_parser_peek_token (parser)->keyword];
    }
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->విలువ;

  తిరిగి attr_name;
}

/* Parse attribute arguments.  This is a common form of syntax
   covering all currently valid GNU and standard attributes.

   gnu-attribute-arguments:
     identifier
     identifier , nonempty-expr-list
     expr-list

   where the "identifier" must not be declared as a type.  ??? Why not
   allow identifiers declared as types to start the arguments?  */

స్థిర వృక్షం
c_parser_attribute_arguments (c_parser *parser, తార్కిక takes_identifier,
			      తార్కిక require_string, తార్కిక assume_attr,
			      తార్కిక allow_ఖాళీలు_వాదనలు)
{
  vec<వృక్షం, va_gc> *సమాసం_list;
  వృక్షం attr_వాదనలు;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
      && (c_parser_peek_token (parser)->id_రకం == C_ID_ID
	  || (c_dialect_objc ()
	      && c_parser_peek_token (parser)->id_రకం
	      == C_ID_CLASSNAME))
      && ((c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	  || (c_parser_peek_2nd_token (parser)->type
	      == CPP_CLOSE_PAREN))
      && (takes_identifier
	  || (c_dialect_objc ()
	      && !assume_attr
	      && c_parser_peek_token (parser)->id_రకం
	      == C_ID_CLASSNAME)))
    {
      వృక్షం arg1 = c_parser_peek_token (parser)->విలువ;
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	attr_వాదనలు = build_వృక్షం_list (NULL_వృక్షం, arg1);
      లేకపోతే
	{
	  వృక్షం వృక్షం_list;
	  c_parser_consume_token (parser);
	  సమాసం_list = c_parser_సమాసం_list (parser, అబద్ధం, నిజం,
					  ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ);
	  వృక్షం_list = build_వృక్షం_list_vec (సమాసం_list);
	  attr_వాదనలు = వృక్షం_cons (NULL_వృక్షం, arg1, వృక్షం_list);
	  release_వృక్షం_సదిశ (సమాసం_list);
	}
    }
  లేకపోతే
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ఒకవేళ (!allow_ఖాళీలు_వాదనలు)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_వాదనలు = NULL_వృక్షం;
	}
      లేకపోతే ఒకవేళ (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  వృక్షం string = c_parser_string_literal (parser, అబద్ధం, నిజం).విలువ;
	  attr_వాదనలు = build_వృక్షం_list (NULL_వృక్షం, string);
	}
      లేకపోతే ఒకవేళ (assume_attr)
	{
	  వృక్షం cond
	    = c_parser_conditional_వ్యక్తీకరణ (parser, ఖాళీ, NULL_వృక్షం).విలువ;
	  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    attr_వాదనలు = build_వృక్షం_list (NULL_వృక్షం, cond);
	  లేకపోతే
	    {
	      వృక్షం వృక్షం_list;
	      c_parser_consume_token (parser);
	      సమాసం_list = c_parser_సమాసం_list (parser, అబద్ధం, నిజం,
					      ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ);
	      వృక్షం_list = build_వృక్షం_list_vec (సమాసం_list);
	      attr_వాదనలు = వృక్షం_cons (NULL_వృక్షం, cond, వృక్షం_list);
	      release_వృక్షం_సదిశ (సమాసం_list);
	    }
	}
      లేకపోతే
	{
	  సమాసం_list = c_parser_సమాసం_list (parser, అబద్ధం, నిజం,
					  ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ);
	  attr_వాదనలు = build_వృక్షం_list_vec (సమాసం_list);
	  release_వృక్షం_సదిశ (సమాసం_list);
	}
    }
  తిరిగి attr_వాదనలు;
}

/* Parse (possibly empty) gnu-attributes.  This is a GNU extension.

   gnu-attributes:
ఖాళీలు
     gnu-attributes gnu-attribute

   gnu-attribute:
     __attribute__ ( ( gnu-attribute-list ) )

   gnu-attribute-list:
     gnu-attrib
     gnu-attribute_list , gnu-attrib

   gnu-attrib:
ఖాళీలు
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

స్థిర వృక్షం
c_parser_gnu_attribute (c_parser *parser, వృక్షం attrs,
			తార్కిక expect_comma = అబద్ధం, తార్కిక ఖాళీలు_ok = నిజం)
{
  తార్కిక comma_మొదటి = c_parser_తదుపరి_token_is (parser, CPP_COMMA);
  ఒకవేళ (!comma_మొదటి
      && !c_parser_తదుపరి_token_is (parser, CPP_NAME)
      && !c_parser_తదుపరి_token_is (parser, CPP_KEYWORD))
    తిరిగి NULL_వృక్షం;

  అయితే (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ఒకవేళ (!ఖాళీలు_ok)
	తిరిగి attrs;
    }

  వృక్షం attr_name = c_parser_gnu_attribute_any_మాట (parser);
  ఒకవేళ (attr_name == NULL_వృక్షం)
    తిరిగి NULL_వృక్షం;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  వృక్షం attr;
  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_OPEN_PAREN))
    {
      ఒకవేళ (expect_comma && !comma_మొదటి)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  తిరిగి error_mark_కణుపు;
	}
      attr = build_వృక్షం_list (attr_name, NULL_వృక్షం);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      తిరిగి attrs;
    }
  c_parser_consume_token (parser);

  వృక్షం attr_వాదనలు
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    అబద్ధం,
				    is_attribute_p ("assume", attr_name),
				    నిజం);

  attr = build_వృక్షం_list (attr_name, attr_వాదనలు);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  లేకపోతే
    {
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      తిరిగి error_mark_కణుపు;
    }

  ఒకవేళ (expect_comma && !comma_మొదటి)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      తిరిగి error_mark_కణుపు;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  తిరిగి attrs;
}

స్థిర వృక్షం
c_parser_gnu_లక్షణాలు (c_parser *parser)
{
  వృక్షం attrs = NULL_వృక్షం;
  అయితే (c_parser_తదుపరి_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      తార్కిక save_translate_అక్షరశ్రేణులు_p = parser->translate_అక్షరశ్రేణులు_p;
      parser->translate_అక్షరశ్రేణులు_p = అబద్ధం;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_అక్షరశ్రేణులు_p = save_translate_అక్షరశ్రేణులు_p;
	  తిరిగి attrs;
	}
      ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_అక్షరశ్రేణులు_p = save_translate_అక్షరశ్రేణులు_p;
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
	  తిరిగి attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      కొరకు (తార్కిక expect_comma = అబద్ధం; ; expect_comma = నిజం)
	{
	  /* Parse a single attribute.  */
	  వృక్షం attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  ఒకవేళ (attr == error_mark_కణుపు)
	    తిరిగి attrs;
	  ఒకవేళ (!attr)
	    ఆపు;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      లేకపోతే
	{
	  parser->translate_అక్షరశ్రేణులు_p = save_translate_అక్షరశ్రేణులు_p;
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  తిరిగి attrs;
	}
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      లేకపోతే
	{
	  parser->translate_అక్షరశ్రేణులు_p = save_translate_అక్షరశ్రేణులు_p;
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  తిరిగి attrs;
	}
      parser->translate_అక్షరశ్రేణులు_p = save_translate_అక్షరశ్రేణులు_p;
    }

  తిరిగి attrs;
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

స్థిర శూన్య
c_parser_సమతుల్య_token_sequence (c_parser *parser)
{
  అయితే (నిజం)
    {
      c_token *token = c_parser_peek_token (parser);
      ఎంపిక (token->type)
	{
	స్థితి CPP_OPEN_BRACE:
	  {
	    matching_braces braces;
	    braces.consume_open (parser);
	    c_parser_సమతుల్య_token_sequence (parser);
	    braces.require_close (parser);
	    ఆపు;
	  }

	స్థితి CPP_OPEN_PAREN:
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    c_parser_సమతుల్య_token_sequence (parser);
	    parens.require_close (parser);
	    ఆపు;
	  }

	స్థితి CPP_OPEN_వర్గం:
	  c_parser_consume_token (parser);
	  c_parser_సమతుల్య_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_వర్గం, "expected %<]%>");
	  ఆపు;

	స్థితి CPP_CLOSE_BRACE:
	స్థితి CPP_CLOSE_PAREN:
	స్థితి CPP_CLOSE_వర్గం:
	స్థితి CPP_EOF:
	  తిరిగి;

	స్థితి CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	  ఆపు;

	అప్రమేయ:
	  c_parser_consume_token (parser);
	  ఆపు;
	}
    }
}

/* Parse arguments of omp::directive or omp::decl attribute.

   directive-name ,[opt] clause-list[opt]

   For directive just remember the tokens in a vector for subsequent
   parsing.  */

స్థిర శూన్య
c_parser_omp_directive_వాదనలు (c_parser *parser, వృక్షం attribute, తార్కిక decl_p)
{
  గుర్తులేని పూర్ణాంకం n = 1;
  c_token *మొదటి = c_parser_peek_token (parser);
  ఒకవేళ (!c_parser_check_సమతుల్య_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_సమతుల్య_token_sequence (parser);
      వృక్షం_విలువ (attribute) = NULL_వృక్షం;
      తిరిగి;
    }
  ఒకవేళ (n == 1)
    {
      error_at (మొదటి->location, "expected OpenMP directive name");
      వృక్షం_విలువ (attribute) = NULL_వృక్షం;
      తిరిగి;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  కొరకు (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->శీఘ్ర_నెట్టు (*tok);
      c_parser_consume_token (parser);
    }
  వృక్షం arg = make_కణుపు (C_TOKEN_VEC);
  C_TOKEN_VEC_టోకెన్లు (arg) = v;
  ఒకవేళ (decl_p)
    వృక్షం_ప్రజా (arg) = 1;
  వృక్షం_విలువ (attribute) = వృక్షం_cons (NULL_వృక్షం, arg, వృక్షం_విలువ (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

స్థిర శూన్య
c_parser_omp_sequence_వాదనలు (c_parser *parser, వృక్షం attribute)
{
  చేయి
    {
      c_token *token = c_parser_peek_token (parser);
      ఒకవేళ (token->type == CPP_NAME
	  && strcmp (IDENTIFIER_సూచిక (token->విలువ), "omp") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_SCOPE)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  token = c_parser_peek_token (parser);
	}
      తార్కిక directive = అబద్ధం;
      స్థిరరాశి అక్షరం *p;
      ఒకవేళ (token->type != CPP_NAME)
	p = "";
      లేకపోతే
	p = IDENTIFIER_సూచిక (token->విలువ);
      ఒకవేళ (strcmp (p, "directive") == 0)
	directive = నిజం;
      లేకపోతే ఒకవేళ (strcmp (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  గుర్తులేని nesting_లోతు = 0;

	  అయితే (నిజం)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      ఒకవేళ ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_లోతు)
		ఆపు;
	      /* If we've run out of tokens, stop.  */
	      ఒకవేళ (token->type == CPP_EOF)
		ఆపు;
	      ఒకవేళ (token->type == CPP_PRAGMA_EOL && parser->లోపల_pragma)
		ఆపు;
	      ఒకవేళ (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_వర్గం)
		++nesting_లోతు;
	      లేకపోతే ఒకవేళ (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_వర్గం)
		{
		  ఒకవేళ (nesting_లోతు-- == 0)
		    ఆపు;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_COMMA))
	    ఆపు;
	  c_parser_consume_token (parser);
	  కొనసాగు;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      ఒకవేళ (parens.require_open (parser))
	{
	  ఒకవేళ (directive)
	    c_parser_omp_directive_వాదనలు (parser, attribute, అబద్ధం);
	  లేకపోతే
	    c_parser_omp_sequence_వాదనలు (parser, attribute);
	  parens.skip_until_దొరికింది_close (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_COMMA))
	    ఆపు;
	  c_parser_consume_token (parser);
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_COMMA))
	ఆపు;
      లేకపోతే
	c_parser_consume_token (parser);
    }
  అయితే (1);
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

స్థిర వృక్షం
c_parser_std_attribute (c_parser *parser, తార్కిక for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  వృక్షం ns, name, attribute;

  /* Parse the attribute-token.  */
  ఒకవేళ (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      తిరిగి error_mark_కణుపు;
    }
  name = canonicalize_attr_name (token->విలువ);
  c_parser_consume_token (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SCOPE)
      || (c_parser_తదుపరి_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      ఒకవేళ (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  తిరిగి error_mark_కణుపు;
	}
      name = canonicalize_attr_name (token->విలువ);
      c_parser_consume_token (parser);
    }
  లేకపోతే
    ns = NULL_వృక్షం;
  attribute = build_వృక్షం_list (build_వృక్షం_list (ns, name), NULL_వృక్షం);

  /* Parse the arguments, if any.  */
  స్థిరరాశి attribute_spec *as = lookup_attribute_spec (వృక్షం_PURPOSE (attribute));
  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_OPEN_PAREN))
    {
      ఒకవేళ ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  తిరిగి error_mark_కణుపు;
	}
      వెళ్ళు బహిర్గతం;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    ఒకవేళ ((as && as->max_నిడివి == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_దొరికింది_close (parser);
	తిరిగి error_mark_కణుపు;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    ఒకవేళ (as && !attribute_ignored_p (as))
      {
	తార్కిక takes_identifier
	  = (ns != NULL_వృక్షం
	     && strcmp (IDENTIFIER_సూచిక (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	తార్కిక require_string
	  = (ns == NULL_వృక్షం
	     && (strcmp (IDENTIFIER_సూచిక (name), "deprecated") == 0
		 || strcmp (IDENTIFIER_సూచిక (name), "nodiscard") == 0));
	తార్కిక assume_attr
	  = (ns != NULL_వృక్షం
	     && strcmp (IDENTIFIER_సూచిక (ns), "gnu") == 0
	     && strcmp (IDENTIFIER_సూచిక (name), "assume") == 0);
	వృక్షం_విలువ (attribute)
	  = c_parser_attribute_arguments (parser, takes_identifier,
					  require_string, assume_attr, అబద్ధం);
      }
    లేకపోతే
      {
	ఒకవేళ ((flag_openmp || flag_openmp_simd)
	    && ns
	    && is_attribute_p ("omp", ns))
	  {
	    ఒకవేళ (is_attribute_p ("directive", name))
	      {
		c_parser_omp_directive_వాదనలు (parser, attribute, అబద్ధం);
		parens.skip_until_దొరికింది_close (parser);
		తిరిగి attribute;
	      }
	    లేకపోతే ఒకవేళ (is_attribute_p ("decl", name))
	      {
		వృక్షం_విలువ (వృక్షం_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_వాదనలు (parser, attribute, నిజం);
		parens.skip_until_దొరికింది_close (parser);
		తిరిగి attribute;
	      }
	    లేకపోతే ఒకవేళ (is_attribute_p ("sequence", name))
	      {
		వృక్షం_విలువ (వృక్షం_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_వాదనలు (parser, attribute);
		parens.skip_until_దొరికింది_close (parser);
		వృక్షం_విలువ (attribute) = nreverse (వృక్షం_విలువ (attribute));
		తిరిగి attribute;
	      }
	  }
	c_parser_సమతుల్య_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 బహిర్గతం:
  ఒకవేళ (ns == NULL_వృక్షం && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (ఆదానం_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      తిరిగి error_mark_కణుపు;
    }
  తిరిగి attribute;
}

స్థిర వృక్షం
c_parser_std_attribute_list (c_parser *parser, తార్కిక for_tm)
{
  వృక్షం లక్షణాలు = NULL_వృక్షం;
  అయితే (నిజం)
    {
      c_token *token = c_parser_peek_token (parser);
      ఒకవేళ (token->type == CPP_CLOSE_వర్గం)
	ఆపు;
      ఒకవేళ (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  కొనసాగు;
	}
      వృక్షం attribute = c_parser_std_attribute (parser, for_tm);
      ఒకవేళ (attribute != error_mark_కణుపు)
	{
	  వృక్షం_CHAIN (attribute) = లక్షణాలు;
	  లక్షణాలు = attribute;
	}
      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_COMMA))
	ఆపు;
    }
  తిరిగి లక్షణాలు;
}

స్థిర వృక్షం
c_parser_std_attribute_specifier (c_parser *parser, తార్కిక for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_వర్గం, "expected %<[%>"))
    తిరిగి NULL_వృక్షం;
  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_వర్గం, "expected %<[%>"))
    {
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_వర్గం, "expected %<]%>");
      తిరిగి NULL_వృక్షం;
    }
  వృక్షం లక్షణాలు;
  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_EXTENSION))
    {
      స్వయంచాలక ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      లక్షణాలు = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  లేకపోతే
    {
      ఒకవేళ (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      లక్షణాలు = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_వర్గం, "expected %<]%>");
  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_వర్గం, "expected %<]%>");
  తిరిగి nreverse (లక్షణాలు);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

స్థిర తార్కిక
c_parser_check_సమతుల్య_raw_token_sequence (c_parser *parser, గుర్తులేని పూర్ణాంకం *n)
{
  అయితే (నిజం)
    {
      c_token *token = c_parser_peek_nth_token_raw (parser, *n);
      ఎంపిక (token->type)
	{
	స్థితి CPP_OPEN_BRACE:
	  {
	    ++*n;
	    ఒకవేళ (c_parser_check_సమతుల్య_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		ఒకవేళ (token->type == CPP_CLOSE_BRACE)
		  ++*n;
		లేకపోతే
		  తిరిగి అబద్ధం;
	      }
	    లేకపోతే
	      తిరిగి అబద్ధం;
	    ఆపు;
	  }

	స్థితి CPP_OPEN_PAREN:
	  {
	    ++*n;
	    ఒకవేళ (c_parser_check_సమతుల్య_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		ఒకవేళ (token->type == CPP_CLOSE_PAREN)
		  ++*n;
		లేకపోతే
		  తిరిగి అబద్ధం;
	      }
	    లేకపోతే
	      తిరిగి అబద్ధం;
	    ఆపు;
	  }

	స్థితి CPP_OPEN_వర్గం:
	  {
	    ++*n;
	    ఒకవేళ (c_parser_check_సమతుల్య_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		ఒకవేళ (token->type == CPP_CLOSE_వర్గం)
		  ++*n;
		లేకపోతే
		  తిరిగి అబద్ధం;
	      }
	    లేకపోతే
	      తిరిగి అబద్ధం;
	    ఆపు;
	  }

	స్థితి CPP_CLOSE_BRACE:
	స్థితి CPP_CLOSE_PAREN:
	స్థితి CPP_CLOSE_వర్గం:
	స్థితి CPP_EOF:
	  తిరిగి నిజం;

	అప్రమేయ:
	  ++*n;
	  ఆపు;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

స్థిర తార్కిక
c_parser_nth_token_starts_std_లక్షణాలు (c_parser *parser, గుర్తులేని పూర్ణాంకం n)
{
  ఒకవేళ (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_వర్గం
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_వర్గం))
    తిరిగి అబద్ధం;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  ఒకవేళ (!c_dialect_objc ())
    తిరిగి నిజం;
  n += 2;
  ఒకవేళ (!c_parser_check_సమతుల్య_raw_token_sequence (parser, &n))
    తిరిగి అబద్ధం;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  ఒకవేళ (token->type != CPP_CLOSE_వర్గం)
    తిరిగి అబద్ధం;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  తిరిగి token->type == CPP_CLOSE_వర్గం;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

స్థిర కొలత_t
c_parser_skip_std_attribute_spec_seq (c_parser *parser, కొలత_t n)
{
  కొలత_t orig_n = n;
  అయితే (నిజం)
    {
      ఒకవేళ (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_వర్గం
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_వర్గం))
	{
	  గుర్తులేని పూర్ణాంకం m = n + 2;
	  ఒకవేళ (!c_parser_check_సమతుల్య_raw_token_sequence (parser, &m))
	    తిరిగి orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  ఒకవేళ (token->type != CPP_CLOSE_వర్గం)
	    తిరిగి orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  ఒకవేళ (token->type != CPP_CLOSE_వర్గం)
	    తిరిగి orig_n;
	  n = m + 2;
	}
      లేకపోతే
	ఆపు;
    }
  తిరిగి n;
}

స్థిర వృక్షం
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  వృక్షం లక్షణాలు = NULL_వృక్షం;
  చేయి
    {
      వృక్షం attrs = c_parser_std_attribute_specifier (parser, అబద్ధం);
      లక్షణాలు = chainon (లక్షణాలు, attrs);
    }
  అయితే (c_parser_nth_token_starts_std_లక్షణాలు (parser, 1));
  తిరిగి లక్షణాలు;
}

/* Parse a type name (C90 6.5.5, C99 6.7.6, C11 6.7.7).  ALIGNAS_OK
   says whether alignment specifiers are OK (only in cases that might
   be the type name of a compound literal).

   type-name:
     specifier-qualifier-list abstract-declarator[opt]
*/

నిర్మాణం c_type_name *
c_parser_type_name (c_parser *parser, తార్కిక alignas_ok)
{
  నిర్మాణం c_declspecs *specs = build_null_declspecs ();
  నిర్మాణం c_declarator *declarator;
  నిర్మాణం c_type_name *ret;
  తార్కిక dummy = అబద్ధం;
  c_parser_declspecs (parser, specs, అబద్ధం, నిజం, నిజం, alignas_ok, అబద్ధం,
		      అబద్ధం, నిజం, cla_prefer_type);
  ఒకవేళ (!specs->declspecs_చూసిన_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      తిరిగి ఖాళీ;
    }
  ఒకవేళ (specs->type != error_mark_కణుపు)
    {
      pending_xref_error ();
      ముగింపు_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      ఒకవేళ (specs->typespec_రకం == ctsk_tagdef)
	verify_counted_by_for_శిఖరం_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_రకం != ctsk_none,
				    C_DTR_ABSTRACT, &dummy);
  ఒకవేళ (declarator == ఖాళీ)
    తిరిగి ఖాళీ;
  ret = XOBNEW (&parser_obstack, నిర్మాణం c_type_name);
  ret->specs = specs;
  ret->declarator = declarator;
  తిరిగి ret;
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

స్థిర నిర్మాణం c_సమాసం
c_parser_initializer (c_parser *parser, వృక్షం decl)
{
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
    తిరిగి c_parser_braced_init (parser, NULL_వృక్షం, అబద్ధం, ఖాళీ,
				 decl != error_mark_కణుపు
				 && C_DECL_VARIABLE_కొలత (decl));
  లేకపోతే
    {
      నిర్మాణం c_సమాసం ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      ఒకవేళ (decl != error_mark_కణుపు && C_DECL_VARIABLE_కొలత (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.సమితి_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      ఒకవేళ (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !వృక్షం_STATIC (decl)
	  && ret.విలువ == decl
	  && !warning_enabled_at (DECL_ఆధారం_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      ఒకవేళ (వృక్షం_సంకేతం (ret.విలువ) != STRING_CST
	  && (వృక్షం_సంకేతం (ret.విలువ) != COMPOUND_LITERAL_సమాసం
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_సమాసం_DECL
					    (ret.విలువ))))
	ret = convert_lvalue_గమ్యం_rvalue (loc, ret, నిజం, నిజం, నిజం);
      తిరిగి ret;
    }
}

/* The location of the last comma within the current initializer list,
   or UNKNOWN_LOCATION if not within one.  */

location_t చివరి_init_list_comma;

/* Parse a braced initializer list.  TYPE is the type specified for a
   compound literal, and NULL_TREE for other initializers and for
   nested braced lists.  NESTED_P is true for nested braced lists,
   false for the list of a compound literal or the list that is the
   top-level initializer in a declaration.  VARSIZE_P indicates
   whether the object to be initialized has a variable size.  */

స్థిర నిర్మాణం c_సమాసం
c_parser_braced_init (c_parser *parser, వృక్షం type, తార్కిక nested_p,
		      నిర్మాణం obstack *outer_obstack, తార్కిక varsize_p)
{
  నిర్మాణం c_సమాసం ret;
  నిర్మాణం obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE));
  తార్కిక save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = అబద్ధం;
  తార్కిక zero_init_padding_బిట్లు = అబద్ధం;
  matching_braces braces;
  braces.consume_open (parser);
  ఒకవేళ (nested_p)
    {
      ముగింపు_implicit_inits (brace_loc, outer_obstack);
      నెట్టు_init_level (brace_loc, 0, &braced_init_obstack);
    }
  లేకపోతే
    really_ప్రారంభం_incremental_init (type);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      ఒకవేళ (flag_isoc23)
	zero_init_padding_బిట్లు = నిజం;
    }
  లేకపోతే
    {
      ఒకవేళ (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      అయితే (నిజం)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  ఒకవేళ (parser->error)
	    ఆపు;
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    {
	      చివరి_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      అయితే (c_parser_తదుపరి_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_సమాసం embed_val;
		  embed_val.విలువ = embed->విలువ;
		  embed_val.original_సంకేతం = RAW_దత్తాంశం_CST;
		  embed_val.original_type = integer_type_కణుపు;
		  సమితి_c_సమాసం_ఆధారం_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, అబద్ధం,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_తదుపరి_token_is (parser,
							       CPP_COMMA));
		  చివరి_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  లేకపోతే
	    ఆపు;
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
	    ఆపు;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *తదుపరి_tok = c_parser_peek_token (parser);
  ఒకవేళ (తదుపరి_tok->type != CPP_CLOSE_BRACE)
    {
      ret.సమితి_error ();
      ret.original_సంకేతం = ERROR_MARK;
      ret.original_type = ఖాళీ;
      braces.skip_until_దొరికింది_close (parser);
      తీయి_init_level (brace_loc, 0, &braced_init_obstack, చివరి_init_list_comma);
      obstack_free (&braced_init_obstack, ఖాళీ);
      తిరిగి ret;
    }
  location_t close_loc = తదుపరి_tok->location;
  c_parser_consume_token (parser);
  ret = తీయి_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  ఒకవేళ (zero_init_padding_బిట్లు
      && ret.విలువ
      && వృక్షం_సంకేతం (ret.విలువ) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_బిట్లు (ret.విలువ) = 1;
  obstack_free (&braced_init_obstack, ఖాళీ);
  సమితి_c_సమాసం_ఆధారం_range (&ret, brace_loc, close_loc);
  తిరిగి ret;
}

/* Parse a nested initializer, including designators.  */

స్థిర శూన్య
c_parser_initelt (c_parser *parser, నిర్మాణం obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      సమితి_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->విలువ,
		      c_parser_peek_token (parser)->location,
		      braced_init_obstack);
      /* Use the colon as the error location.  */
      pedwarn (c_parser_peek_2nd_token (parser)->location, OPT_Wpedantic,
	       "obsolete use of designated initializer with %<:%>");
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  లేకపోతే
    {
      /* des_seen is 0 if there have been no designators, 1 if there
	 has been a single array designator and 2 otherwise.  */
      పూర్ణాంకం des_చూసిన = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      అయితే (c_parser_తదుపరి_token_is (parser, CPP_OPEN_వర్గం)
	     || c_parser_తదుపరి_token_is (parser, CPP_DOT))
	{
	  పూర్ణాంకం des_prev = des_చూసిన;
	  ఒకవేళ (!des_చూసిన)
	    des_loc = c_parser_peek_token (parser)->location;
	  ఒకవేళ (des_చూసిన < 2)
	    des_చూసిన++;
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_DOT))
	    {
	      des_చూసిన = 2;
	      c_parser_consume_token (parser);
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
		{
		  సమితి_init_label (des_loc, c_parser_peek_token (parser)->విలువ,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      లేకపోతే
		{
		  నిర్మాణం c_సమాసం init;
		  init.సమితి_error ();
		  init.original_సంకేతం = ERROR_MARK;
		  init.original_type = ఖాళీ;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_దొరికింది (parser, CPP_COMMA, ఖాళీ);
		  process_init_element (ఆదానం_location, init, అబద్ధం,
					braced_init_obstack);
		  తిరిగి;
		}
	    }
	  లేకపోతే
	    {
	      నిర్మాణం c_సమాసం మొదటి_సమాసం;
	      వృక్షం మొదటి, రెండవ;
	      location_t ellipsis_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	      location_t array_సూచీ_loc = UNKNOWN_LOCATION;
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
	      ఒకవేళ (des_prev == 1 && c_dialect_objc ())
		{
		  des_చూసిన = des_prev;
		  ఆపు;
		}
	      ఒకవేళ (des_prev == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  వృక్షం rec, వాదనలు;
		  నిర్మాణం c_సమాసం mexpr;
		  c_parser_consume_token (parser);
		  ఒకవేళ (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_రకం
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_రకం
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      వృక్షం id = c_parser_peek_token (parser)->విలువ;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      వెళ్ళు parse_సందేశం_వాదనలు;
		    }
		  array_సూచీ_loc = c_parser_peek_token (parser)->location;
		  మొదటి_సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
		  mark_exp_read (మొదటి_సమాసం.విలువ);
		  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_తదుపరి_token_is (parser, CPP_CLOSE_వర్గం))
		    వెళ్ళు array_desig_after_మొదటి;
		  మొదటి = మొదటి_సమాసం.విలువ;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = మొదటి;
		  అయితే (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
		    {
		      నిర్మాణం c_సమాసం తదుపరి;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      తదుపరి = c_parser_సమాసం_no_commas (parser, ఖాళీ);
		      తదుపరి = convert_lvalue_గమ్యం_rvalue (exp_loc, తదుపరి,
						       నిజం, నిజం);
		      rec = build_compound_సమాసం (comma_loc, rec, తదుపరి.విలువ);
		    }
		parse_సందేశం_వాదనలు:
		  /* Now parse the objc-message-args.  */
		  వాదనలు = c_parser_objc_సందేశం_వాదనలు (parser);
		  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_వర్గం,
					     "expected %<]%>");
		  mexpr.విలువ
		    = objc_build_సందేశం_సమాసం (rec, వాదనలు);
		  mexpr.original_సంకేతం = ERROR_MARK;
		  mexpr.original_type = ఖాళీ;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  తిరిగి;
		}
	      c_parser_consume_token (parser);
	      array_సూచీ_loc = c_parser_peek_token (parser)->location;
	      మొదటి_సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	      mark_exp_read (మొదటి_సమాసం.విలువ);
	    array_desig_after_మొదటి:
	      మొదటి_సమాసం = convert_lvalue_గమ్యం_rvalue (array_సూచీ_loc,
						     మొదటి_సమాసం,
						     నిజం, నిజం);
	      మొదటి = మొదటి_సమాసం.విలువ;
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  రెండవ = convert_lvalue_గమ్యం_rvalue (ellipsis_loc,
						     (c_parser_సమాసం_no_commas
						      (parser, ఖాళీ)),
						     నిజం, నిజం).విలువ;
		  mark_exp_read (రెండవ);
		}
	      లేకపోతే
		రెండవ = NULL_వృక్షం;
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_వర్గం))
		{
		  c_parser_consume_token (parser);
		  సమితి_init_సూచీ (array_సూచీ_loc, మొదటి, రెండవ,
				  braced_init_obstack);
		  ఒకవేళ (రెండవ)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      లేకపోతే
		c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_వర్గం,
					   "expected %<]%>");
	    }
	}
      ఒకవేళ (des_చూసిన >= 1)
	{
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  లేకపోతే
	    {
	      ఒకవేళ (des_చూసిన == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      లేకపోతే
		{
		  నిర్మాణం c_సమాసం init;
		  init.సమితి_error ();
		  init.original_సంకేతం = ERROR_MARK;
		  init.original_type = ఖాళీ;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_దొరికింది (parser, CPP_COMMA, ఖాళీ);
		  process_init_element (ఆదానం_location, init, అబద్ధం,
					braced_init_obstack);
		  తిరిగి;
		}
	    }
	}
    }
  c_parser_initval (parser, ఖాళీ, braced_init_obstack);
}

/* Parse a nested initializer; as c_parser_initializer but parses
   initializers within braced lists, after any designators have been
   applied.  If AFTER is not NULL then it is an Objective-C message
   expression which is the primary-expression starting the
   initializer.  */

స్థిర శూన్య
c_parser_initval (c_parser *parser, నిర్మాణం c_సమాసం *after,
		  నిర్మాణం obstack * braced_init_obstack)
{
  నిర్మాణం c_సమాసం init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_వృక్షం, నిజం,
				 braced_init_obstack, అబద్ధం);
  లేకపోతే
    {
      init = c_parser_సమాసం_no_commas (parser, after);
      ఒకవేళ (init.విలువ != NULL_వృక్షం
	  && వృక్షం_సంకేతం (init.విలువ) != STRING_CST
	  && (వృక్షం_సంకేతం (init.విలువ) != COMPOUND_LITERAL_సమాసం
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_సమాసం_DECL
					    (init.విలువ))))
	init = convert_lvalue_గమ్యం_rvalue (loc, init, నిజం, నిజం, నిజం);
    }
  వృక్షం val = init.విలువ;
  process_init_element (loc, init, అబద్ధం, braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  స్థిర గుర్తులేని vals_గమ్యం_ignore;
  ఒకవేళ (vals_గమ్యం_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_గమ్యం_ignore;
  లేకపోతే ఒకవేళ (val
	   && వృక్షం_సంకేతం (val) == INTEGER_CST
	   && వృక్షం_TYPE (val) == integer_type_కణుపు
	   && c_parser_తదుపరి_token_is (parser, CPP_COMMA))
    ఒకవేళ (గుర్తులేని పూర్ణాంకం len = c_maybe_optimize_large_byte_initializer ())
      {
	అక్షరం buf1[64];
	గుర్తులేని పూర్ణాంకం i;
	gcc_checking_assert (len >= 64);
	location_t చివరి_loc = UNKNOWN_LOCATION;
	కొరకు (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    ఒకవేళ (tok->type != CPP_COMMA)
	      ఆపు;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    ఒకవేళ (tok->type != CPP_సంఖ్య
		|| వృక్షం_సంకేతం (tok->విలువ) != INTEGER_CST
		|| వృక్షం_TYPE (tok->విలువ) != integer_type_కణుపు
		|| wi::neg_p (wi::గమ్యం_wide (tok->విలువ))
		|| wi::గమ్యం_widest (tok->విలువ) > UCHAR_MAX)
	      ఆపు;
	    buf1[i] = (అక్షరం) వృక్షం_గమ్యం_uhwi (tok->విలువ);
	    ఒకవేళ (i == 0)
	      loc = tok->location;
	    చివరి_loc = tok->location;
	  }
	ఒకవేళ (i < 64)
	  {
	    vals_గమ్యం_ignore = i;
	    తిరిగి;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	ఒకవేళ (tok->type == CPP_CLOSE_BRACE && len != గరిష్ఠ_పూర్ణాంకం)
	  len = i;
	లేకపోతే ఒకవేళ (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_సంఖ్య))
	  {
	    vals_గమ్యం_ignore = i;
	    తిరిగి;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	గుర్తులేని పూర్ణాంకం max_len = 131072 - offsetof (నిర్మాణం వృక్షం_string, str) - 1;
	గుర్తులేని పూర్ణాంకం orig_len = len;
	గుర్తులేని పూర్ణాంకం off = 0, చివరి = 0;
	ఒకవేళ (!wi::neg_p (wi::గమ్యం_wide (val)) && wi::గమ్యం_widest (val) <= UCHAR_MAX)
	  off = 1;
	len = MIN (len, max_len - off);
	అక్షరం *buf2 = XNEWVEC (అక్షరం, len + off);
	ఒకవేళ (off)
	  buf2[0] = (అక్షరం) వృక్షం_గమ్యం_uhwi (val);
	జ్ఞాపకం_నకలు (buf2 + off, buf1, i);
	కొరకు (గుర్తులేని పూర్ణాంకం j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	కొరకు (; i < len; ++i)
	  {
	    ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	      ఆపు;
	    tok = c_parser_peek_2nd_token (parser);
	    ఒకవేళ (tok->type != CPP_సంఖ్య
		|| వృక్షం_సంకేతం (tok->విలువ) != INTEGER_CST
		|| వృక్షం_TYPE (tok->విలువ) != integer_type_కణుపు
		|| wi::neg_p (wi::గమ్యం_wide (tok->విలువ))
		|| wi::గమ్యం_widest (tok->విలువ) > UCHAR_MAX)
	      ఆపు;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    ఒకవేళ (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      ఆపు;
	    buf2[i + off] = (అక్షరం) వృక్షం_గమ్యం_uhwi (tok->విలువ);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    ఒకవేళ (orig_len == గరిష్ఠ_పూర్ణాంకం
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_సంఖ్య)))
	      {
		చివరి = 1;
		ఆపు;
	      }
	    చివరి_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_కణుపు (RAW_దత్తాంశం_CST);
	వృక్షం_TYPE (val) = integer_type_కణుపు;
	RAW_దత్తాంశం_నిడివి (val) = i;
	వృక్షం owner = build_string (i + off + చివరి, buf2);
	XDELETEVEC (buf2);
	వృక్షం_TYPE (owner) = build_array_type_nelts (unsigned_char_type_కణుపు,
						    i + off + చివరి);
	RAW_దత్తాంశం_OWNER (val) = owner;
	RAW_దత్తాంశం_సూచిక (val) = వృక్షం_STRING_సూచిక (owner) + off;
	init.విలువ = val;
	సమితి_c_సమాసం_ఆధారం_range (&init, loc, చివరి_loc);
	init.original_సంకేతం = RAW_దత్తాంశం_CST;
	init.original_type = integer_type_కణుపు;
	init.m_decimal = 0;
	process_init_element (loc, init, అబద్ధం, braced_init_obstack);
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

స్థిర వృక్షం
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  వృక్షం stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (నిజం);
      c_చివర_compound_stmt (brace_loc, stmt, నిజం);
      తిరిగి error_mark_కణుపు;
    }
  stmt = c_begin_compound_stmt (నిజం);
  location_t చివర_loc = c_parser_compound_statement_nostart (parser);
  ఒకవేళ (endlocp)
    *endlocp = చివర_loc;

  తిరిగి c_చివర_compound_stmt (brace_loc, stmt, నిజం);
}

/* Diagnose errors related to imperfectly nested loops in an OMP
   loop construct.  This function is called when such code is seen.
   Only issue one such diagnostic no matter how much invalid
   intervening code there is in the loop.
   FIXME: maybe the location associated with the diagnostic should
   be the current parser token instead of the location of the outer loop
   nest.  */

స్థిర శూన్య
check_omp_intervening_సంకేతం (c_parser *parser)
{
  నిర్మాణం omp_for_parse_దత్తాంశం *omp_for_parse_state = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);

  ఒకవేళ (!omp_for_parse_state->లోపల_intervening_సంకేతం)
    తిరిగి;
  omp_for_parse_state->saw_intervening_సంకేతం = నిజం;

  /* Only diagnose errors related to perfect nesting once.  */
  ఒకవేళ (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      ఒకవేళ (omp_for_parse_state->సంకేతం_2 == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = నిజం;
	}
      లేకపోతే ఒకవేళ (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = నిజం;
	}
      లేకపోతే ఒకవేళ (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = నిజం;
	}
      లేకపోతే ఒకవేళ (omp_for_parse_state->సంకేతం_2 == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = నిజం;
	}
      ఒకవేళ (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->fail = నిజం;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
స్థిర శూన్య
కూడు_structured_ఖండం_stmt (వృక్షం sl)
{
  ఒకవేళ (వృక్షం_సంకేతం (sl) != STATEMENT_LIST
      || !tsi_చివర_p (tsi_ప్రారంభం (sl)))
    కూడు_stmt (build1 (OMP_STRUCTURED_ఖండం, void_type_కణుపు, sl));
}

నిర్మాణం c_omp_attribute_దత్తాంశం
{
  vec<c_token, va_gc> *టోకెన్లు;
  స్థిరరాశి c_omp_directive *dir;
  c_omp_directive_రకం రకం;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

స్థిర తార్కిక
c_parser_handle_statement_omp_లక్షణాలు (c_parser *parser, వృక్షం &attrs,
					  తార్కిక *have_std_attrs)
{
  ఒకవేళ (!flag_openmp && !flag_openmp_simd)
    తిరిగి అబద్ధం;

  auto_vec<c_omp_attribute_దత్తాంశం, 16> vd;
  పూర్ణాంకం cnt = 0;
  పూర్ణాంకం టోకెన్లు = 0;
  తార్కిక bad = అబద్ధం;
  కొరకు (వృక్షం *pa = &attrs; *pa; )
    ఒకవేళ (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	కొరకు (వృక్షం a = వృక్షం_విలువ (*pa); a; a = వృక్షం_CHAIN (a))
	  {
	    వృక్షం d = వృక్షం_విలువ (a);
	    gcc_assert (వృక్షం_సంకేతం (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_టోకెన్లు (d);
	    c_token *మొదటి = toks->చిరునామా ();
	    c_token *చివరి = మొదటి + toks->నిడివి ();
	    ఒకవేళ (parser->omp_attrs_forbidden_p)
	      {
		error_at (మొదటి->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = అబద్ధం;
		bad = నిజం;
	      }
	    లేకపోతే ఒకవేళ (వృక్షం_ప్రజా (d))
	      {
		error_at (మొదటి->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		bad = నిజం;
	      }
	    స్థిరరాశి అక్షరం *directive[3] = {};
	    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
	      {
		వృక్షం id = NULL_వృక్షం;
		ఒకవేళ (మొదటి + i == చివరి)
		  ఆపు;
		ఒకవేళ (మొదటి[i].type == CPP_NAME)
		  id = మొదటి[i].విలువ;
		లేకపోతే ఒకవేళ (మొదటి[i].type == CPP_KEYWORD)
		  id = ridpointers[(పూర్ణాంకం) మొదటి[i].keyword];
		లేకపోతే
		  ఆపు;
		directive[i] = IDENTIFIER_సూచిక (id);
	      }
	    స్థిరరాశి c_omp_directive *dir = ఖాళీ;
	    ఒకవేళ (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    ఒకవేళ (dir == ఖాళీ)
	      {
		error_at (మొదటి->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  వృక్షం_ప్రజా (d) ? "omp::decl" : "omp::directive");
		కొనసాగు;
	      }
	    c_omp_directive_రకం రకం = dir->రకం;
	    ఒకవేళ (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		ఒకవేళ (directive[1]
		    && (strcmp (directive[1], "depend") == 0
			|| strcmp (directive[1], "doacross") == 0))
		  రకం = C_OMP_DIR_STANDALONE;
		లేకపోతే ఒకవేళ (మొదటి + 2 < చివరి
			 && మొదటి[1].type == CPP_COMMA
			 && మొదటి[2].type == CPP_NAME
			 && (strcmp (IDENTIFIER_సూచిక (మొదటి[2].విలువ),
				     "depend") == 0
			     || strcmp (IDENTIFIER_సూచిక (మొదటి[2].విలువ),
					"doacross") == 0))
		  రకం = C_OMP_DIR_STANDALONE;
	      }
	    లేకపోతే ఒకవేళ (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		పూర్ణాంకం paren_లోతు = 0;
		కొరకు (పూర్ణాంకం i = 1; మొదటి + i < చివరి; i++)
		  ఒకవేళ (మొదటి[i].type == CPP_OPEN_PAREN)
		    paren_లోతు++;
		  లేకపోతే ఒకవేళ (మొదటి[i].type == CPP_CLOSE_PAREN)
		    paren_లోతు--;
		  లేకపోతే ఒకవేళ (paren_లోతు == 0
			   && మొదటి + i + 2 < చివరి
			   && మొదటి[i].type == CPP_NAME
			   && మొదటి[i + 1].type == CPP_OPEN_PAREN
			   && మొదటి[i + 2].type == CPP_NAME
			   && !strcmp (IDENTIFIER_సూచిక (మొదటి[i].విలువ),
				       "at")
			   && !strcmp (IDENTIFIER_సూచిక (మొదటి[i
								 + 2].విలువ),
				       "execution"))
		    {
		      రకం = C_OMP_DIR_STANDALONE;
		      ఆపు;
		    }
	      }
	    c_omp_attribute_దత్తాంశం v = { toks, dir, రకం };
	    vd.సురక్షిత_నెట్టు (v);
	    ఒకవేళ (flag_openmp || dir->simd)
	      టోకెన్లు += (చివరి - మొదటి) + 1;
	  }
	c_omp_attribute_దత్తాంశం v = {};
	vd.సురక్షిత_నెట్టు (v);
	*pa = వృక్షం_CHAIN (*pa);
      }
    లేకపోతే
      pa = &వృక్షం_CHAIN (*pa);

  ఒకవేళ (bad)
    {
    fail:
      ఒకవేళ (have_std_attrs && attrs == ఖాళీ)
	*have_std_attrs = అబద్ధం;
      తిరిగి అబద్ధం;
    }

  గుర్తులేని పూర్ణాంకం i;
  c_omp_attribute_దత్తాంశం *v;
  c_omp_attribute_దత్తాంశం *construct_చూసిన = శూన్యసూచిక;
  c_omp_attribute_దత్తాంశం *standalone_చూసిన = శూన్యసూచిక;
  c_omp_attribute_దత్తాంశం *prev_standalone_చూసిన = శూన్యసూచిక;
  FOR_EACH_VEC_ELT (vd, i, v)
    ఒకవేళ (v->టోకెన్లు)
      {
	ఒకవేళ (v->రకం == C_OMP_DIR_CONSTRUCT && !construct_చూసిన)
	  construct_చూసిన = v;
	లేకపోతే ఒకవేళ (v->రకం == C_OMP_DIR_STANDALONE && !standalone_చూసిన)
	  standalone_చూసిన = v;
      }
    లేకపోతే
      {
	ఒకవేళ (standalone_చూసిన && !prev_standalone_చూసిన)
	  {
	    prev_standalone_చూసిన = standalone_చూసిన;
	    standalone_చూసిన = శూన్యసూచిక;
	  }
      }

  ఒకవేళ (cnt > 1 && construct_చూసిన)
    {
      error_at ((*construct_చూసిన->టోకెన్లు)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      వెళ్ళు fail;
    }
  ఒకవేళ (cnt > 1 && standalone_చూసిన && prev_standalone_చూసిన)
    {
      error_at ((*standalone_చూసిన->టోకెన్లు)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      వెళ్ళు fail;
    }

  ఒకవేళ (prev_standalone_చూసిన)
    standalone_చూసిన = prev_standalone_చూసిన;
  ఒకవేళ (standalone_చూసిన
      && !c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_చూసిన->టోకెన్లు->చిరునామా ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      వెళ్ళు fail;
    }
  ఒకవేళ (cnt && c_parser_తదుపరి_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      గణన pragma_రకం రకం = token->pragma_రకం;
      ఒకవేళ (రకం >= PRAGMA_OMP_ప్రారంభం && రకం <= PRAGMA_OMP_చివరి)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  వెళ్ళు fail;
	}
    }

  ఒకవేళ (!టోకెన్లు)
    తిరిగి అబద్ధం;

  గుర్తులేని పూర్ణాంకం టోకెన్లు_avail = parser->టోకెన్లు_avail;

  టోకెన్లు++;
  vec<c_token, va_gc> *toks = ఖాళీ;
  vec_సురక్షిత_reserve (toks, టోకెన్లు, నిజం);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      ఒకవేళ (!v->టోకెన్లు)
	కొనసాగు;
      ఒకవేళ (!flag_openmp && !v->dir->simd)
	కొనసాగు;
      c_token *మొదటి = v->టోకెన్లు->చిరునామా ();
      c_token *చివరి = మొదటి + v->టోకెన్లు->నిడివి ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_రకం = pragma_రకం (v->dir->id);
      tok.location = మొదటి->location;
      toks->శీఘ్ర_నెట్టు (tok);
      అయితే (++మొదటి < చివరి)
	toks->శీఘ్ర_నెట్టు (*మొదటి);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = చివరి[-1].location;
      toks->శీఘ్ర_నెట్టు (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->చివరి ().location;
  toks->శీఘ్ర_నెట్టు (tok);

  gcc_assert (!parser->లోపల_omp_attribute_pragma);
  parser->లోపల_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->లోపల_omp_attribute_pragma->token_vec = toks;
  parser->లోపల_omp_attribute_pragma->save_టోకెన్లు = parser->టోకెన్లు;
  parser->లోపల_omp_attribute_pragma->save_టోకెన్లు_avail = టోకెన్లు_avail;
  parser->టోకెన్లు = toks->చిరునామా ();
  parser->టోకెన్లు_avail = టోకెన్లు;
  తిరిగి నిజం;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

స్థిర శూన్య
c_parser_handle_directive_omp_లక్షణాలు (వృక్షం &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  ఒకవేళ (!flag_openmp && !flag_openmp_simd)
    తిరిగి;

  కొరకు (వృక్షం *pa = &attrs; *pa; )
    ఒకవేళ (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	పూర్ణాంకం cnt = 0;
	కొరకు (వృక్షం *pa2 = &వృక్షం_విలువ (*pa); *pa2; )
	  {
	    వృక్షం a = *pa2;
	    వృక్షం d = వృక్షం_విలువ (a);
	    gcc_assert (వృక్షం_సంకేతం (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_టోకెన్లు (d);
	    c_token *మొదటి = toks->చిరునామా ();
	    c_token *చివరి = మొదటి + toks->నిడివి ();
	    స్థిరరాశి అక్షరం *directive[3] = {};
	    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
	      {
		వృక్షం id = NULL_వృక్షం;
		ఒకవేళ (మొదటి + i == చివరి)
		  ఆపు;
		ఒకవేళ (మొదటి[i].type == CPP_NAME)
		  id = మొదటి[i].విలువ;
		లేకపోతే ఒకవేళ (మొదటి[i].type == CPP_KEYWORD)
		  id = ridpointers[(పూర్ణాంకం) మొదటి[i].keyword];
		లేకపోతే
		  ఆపు;
		directive[i] = IDENTIFIER_సూచిక (id);
	      }
	    స్థిరరాశి c_omp_directive *dir = ఖాళీ;
	    ఒకవేళ (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    ఒకవేళ (dir == ఖాళీ)
	      {
		error_at (మొదటి->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  వృక్షం_ప్రజా (d) ? "omp::decl" : "omp::directive");
		*pa2 = వృక్షం_CHAIN (a);
	      }
	    లేకపోతే ఒకవేళ (dir->id == PRAGMA_OMP_DECLARE
		     && (strcmp (directive[1], "simd") == 0
			 || strcmp (directive[1], "variant") == 0))
	      {
		ఒకవేళ (pragma_clauses)
		  {
		    error_at (మొదటి->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    కొరకు (pa = &attrs; *pa; )
		      ఒకవేళ (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = వృక్షం_CHAIN (*pa);
		      లేకపోతే
			pa = &వృక్షం_CHAIN (*pa);
		    తిరిగి;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->నిడివి ()
				       + toks->నిడివి () + 2);
		కొరకు (++మొదటి; మొదటి < చివరి; ++మొదటి)
		  attr_clauses->శీఘ్ర_నెట్టు (*మొదటి);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = చివరి[-1].location;
		attr_clauses->శీఘ్ర_నెట్టు (tok);
		*pa2 = వృక్షం_CHAIN (a);
	      }
	    లేకపోతే
	      pa2 = &వృక్షం_CHAIN (a);
	  }
	ఒకవేళ (cnt && వృక్షం_విలువ (*pa) == NULL_వృక్షం)
	  *pa = వృక్షం_CHAIN (*pa);
	లేకపోతే
	  pa = &వృక్షం_CHAIN (*pa);
      }
    లేకపోతే
      pa = &వృక్షం_CHAIN (*pa);
  ఒకవేళ (attr_clauses->నిడివి ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->చివరి ().location;
      attr_clauses->శీఘ్ర_నెట్టు (tok);
      attr_clauses->శీఘ్ర_నెట్టు (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

స్థిర వృక్షం
c_parser_handle_musttail (c_parser *parser, వృక్షం std_attrs, attr_state &attr)
{
  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_RETURN))
    {
      ఒకవేళ (వృక్షం a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  కొరకు (; a; a = lookup_attribute ("gnu", "musttail", వృక్షం_CHAIN (a)))
	    ఒకవేళ (వృక్షం_విలువ (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = నిజం;
	}
      ఒకవేళ (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = నిజం;
	}
    }
  తిరిగి std_attrs;
}

/* Return a statement before optional series of LABEL_EXPR/CASE_LABEL_EXPRs.
   Instead of collecting vectors of labels before each stmt just in case
   the statement would be iteration or switch statement for named loops,
   we just remember last emitted statement and let the iteration/switch
   statement search backwards in cur_stmt_list until that stmt for loop
   names if any.  */

స్థిర వృక్షం
get_before_labels ()
{
  ఒకవేళ (!building_stmt_list_p ())
    తిరిగి NULL_వృక్షం;
  వృక్షం_stmt_iterator tsi = tsi_చివరి (cur_stmt_list);
  ఒకవేళ (tsi_చివర_p (tsi))
    తిరిగి NULL_వృక్షం;
  తిరిగి tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

స్థిర location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  తార్కిక చివరి_stmt = అబద్ధం;
  తార్కిక చివరి_label = అబద్ధం;
  తార్కిక save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  నిర్మాణం omp_for_parse_దత్తాంశం *omp_for_parse_state
    = parser->omp_for_parse_state;
  తార్కిక లోపల_omp_loop_ఖండం
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : అబద్ధం;
  వృక్షం sl = NULL_వృక్షం;
  attr_state astate = {};

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      కూడు_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      తిరిగి endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  ఒకవేళ (లోపల_omp_loop_ఖండం)
    sl = నెట్టు_stmt_list ();

  mark_valid_location_for_stdc_pragma (నిజం);
  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (అబద్ధం);
      ఒకవేళ (లోపల_omp_loop_ఖండం)
	check_omp_intervening_సంకేతం (parser);
      అయితే (c_parser_తదుపరి_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  అయితే (నిజం)
	    {
	      వృక్షం label;
	      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  ఆపు;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->విలువ);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      కూడు_stmt (build_stmt (label_loc, DECL_సమాసం, label));
	      c_parser_consume_token (parser);
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      లేకపోతే
		ఆపు;
	    }
	  c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      తిరిగి endloc;
    }
  వృక్షం before_labels = get_before_labels ();
  అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_బిందువు_location_if_లోపల_system_శీర్షిక (loc);

      తార్కిక want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : అబద్ధం);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      ఒకవేళ (లోపల_omp_loop_ఖండం && !చివరి_label)
	{
	  వృక్షం_సంకేతం_2 సంకేతం_2 = omp_for_parse_state->సంకేతం_2;
	  ఒకవేళ (want_nested_loop
	      && c_parser_omp_తదుపరి_టోకెన్లు_can_be_canon_loop (parser, సంకేతం_2,
							     అబద్ధం))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      కూడు_structured_ఖండం_stmt (తీయి_stmt_list (sl));
	      omp_for_parse_state->లోతు++;
	      కూడు_stmt (c_parser_omp_loop_nest (parser, ఖాళీ));
	      omp_for_parse_state->లోతు--;
	      sl = నెట్టు_stmt_list ();
	      parser->error = అబద్ధం;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      కొనసాగు;
	    }
	  లేకపోతే ఒకవేళ (want_nested_loop
		   && c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      వృక్షం pre_sl = తీయి_stmt_list (sl);
	      వృక్షం nested_sl = నెట్టు_stmt_list ();
	      mark_valid_location_for_stdc_pragma (అబద్ధం);
	      c_parser_statement_after_labels (parser, ఖాళీ, NULL_వృక్షం);
	      nested_sl = తీయి_stmt_list (nested_sl);
	      ఒకవేళ (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_సంకేతం (parser);
		  sl = నెట్టు_stmt_list ();
		  కూడు_stmt (pre_sl);
		  కూడు_stmt (nested_sl);
		}
	      లేకపోతే
		{
		  /* It contains the nested loop.  */
		  కూడు_structured_ఖండం_stmt (pre_sl);
		  కూడు_stmt (nested_sl);
		  sl = నెట్టు_stmt_list ();
		}
	      parser->error = అబద్ధం;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      కొనసాగు;
	    }
	  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
	    {
	      /* Prior to implementing the OpenMP 5.1 syntax for canonical
		 loop form, GCC used to accept an empty statements that
		 would now be flagged as intervening code.  Continue to
		 do that, as an extension.  */
	      /* FIXME:  Maybe issue a warning or something here?  */
	      c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
	      కొనసాగు;
	    }
	}

      /* Standard attributes may start a label, statement or declaration.  */
      తార్కిక have_std_attrs
	= c_parser_nth_token_starts_std_లక్షణాలు (parser, 1);
      వృక్షం std_attrs = NULL_వృక్షం;
      ఒకవేళ (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_CASE)
	  || c_parser_తదుపరి_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  లేకపోతే
	    label_loc = c_parser_peek_token (parser)->location;
	  చివరి_label = నిజం;
	  చివరి_stmt = అబద్ధం;
	  mark_valid_location_for_stdc_pragma (అబద్ధం);
	  ఒకవేళ (లోపల_omp_loop_ఖండం)
	    check_omp_intervening_సంకేతం (parser);
	  c_parser_label (parser, std_attrs);
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_లక్షణాలు
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = నిజం)))
	{
	  ఒకవేళ (చివరి_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  ఒకవేళ (లోపల_omp_loop_ఖండం)
	    {
	      check_omp_intervening_సంకేతం (parser);
	      omp_for_parse_state->want_nested_loop = అబద్ధం;
	    }
	  mark_valid_location_for_stdc_pragma (అబద్ధం);
	  తార్కిక fallthru_attr_p = అబద్ధం;
	  c_parser_declaration_or_fndef (parser, నిజం, !have_std_attrs,
					 నిజం, నిజం, నిజం, అబద్ధం, ఖాళీ,
					 ఖాళీ, have_std_attrs, std_attrs,
					 ఖాళీ, &fallthru_attr_p);

	  ఒకవేళ (లోపల_omp_loop_ఖండం)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  ఒకవేళ (చివరి_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  చివరి_stmt = fallthru_attr_p;
	  చివరి_label = అబద్ధం;
	  before_labels = get_before_labels ();
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  If standard attributes have already
	     been seen, it must start a statement, not a declaration,
	     but standard attributes starting a declaration may appear
	     after __extension__.  */
	  అయితే (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  ఒకవేళ (!have_std_attrs
	      && (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_లక్షణాలు (parser, 2)))
	    {
	      పూర్ణాంకం ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      చివరి_label = అబద్ధం;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      ఒకవేళ (లోపల_omp_loop_ఖండం)
		{
		  check_omp_intervening_సంకేతం (parser);
		  omp_for_parse_state->want_nested_loop = అబద్ధం;
		}
	      mark_valid_location_for_stdc_pragma (అబద్ధం);
	      c_parser_declaration_or_fndef (parser, నిజం, నిజం, నిజం, నిజం,
					     నిజం, అబద్ధం);
	      ఒకవేళ (లోపల_omp_loop_ఖండం)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      ఒకవేళ (చివరి_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      చివరి_stmt = అబద్ధం;
	      before_labels = get_before_labels ();
	    }
	  లేకపోతే
	    వెళ్ళు statement;
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_PRAGMA))
	{
	  ఒకవేళ (have_std_attrs && !parser->లోపల_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  లేకపోతే ఒకవేళ (std_attrs)
	    c_warn_వాడని_లక్షణాలు (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  ఒకవేళ (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = అబద్ధం;
	  ఒకవేళ (c_parser_pragma (parser,
			       చివరి_label ? pragma_stmt : pragma_compound,
			       ఖాళీ, before_labels))
	    {
	      చివరి_label = అబద్ధం;
	      చివరి_stmt = నిజం;
	      ఒకవేళ (omp_for_parse_state)
		check_omp_intervening_సంకేతం (parser);
	    }
	  ఒకవేళ (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  తిరిగి c_parser_peek_token (parser)->location;
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_ELSE))
        {
          ఒకవేళ (parser->లోపల_if_ఖండం)
            {
	      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	      error_at (loc, "expected %<}%> before %<else%>");
	      తిరిగి c_parser_peek_token (parser)->location;
            }
          లేకపోతే
            {
              error_at (loc, "%<else%> without a previous %<if%>");
              c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
              కొనసాగు;
            }
        }
      లేకపోతే
	{
	statement:
	  c_warn_వాడని_లక్షణాలు (std_attrs);
	  చివరి_label = అబద్ధం;
	  చివరి_stmt = నిజం;
	  mark_valid_location_for_stdc_pragma (అబద్ధం);
	  ఒకవేళ (!omp_for_parse_state)
	    c_parser_statement_after_labels (parser, ఖాళీ, before_labels,
					     ఖాళీ, astate);
	  లేకపోతే
	    {
	      /* In canonical loop nest form, nested loops can only appear
		 directly, or in a directly nested compound statement.  We
		 already took care of those cases above, so now we have
		 something else.  This statement and everything inside
		 it must be intervening code.  */
	      omp_for_parse_state->want_nested_loop = అబద్ధం;
	      check_omp_intervening_సంకేతం (parser);
	      c_parser_statement_after_labels (parser, ఖాళీ, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = అబద్ధం;
      astate.reset ();
    }
  ఒకవేళ (చివరి_label)
    pedwarn_c11 (label_loc, OPT_Wfree_labels,
		 "label at end of compound statement");
  location_t endloc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  /* Restore the value we started with.  */
  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);

  /* Package leftover intervening code, or the whole contents of the
     compound statement if we were looking for a nested loop in an OMP_FOR
     construct and didn't find one.  */
  ఒకవేళ (sl)
    {
      sl = తీయి_stmt_list (sl);
      ఒకవేళ (omp_for_parse_state->want_nested_loop)
	కూడు_stmt (sl);
      లేకపోతే
	కూడు_structured_ఖండం_stmt (sl);
    }
  తిరిగి endloc;
}

/* Parse all consecutive labels, possibly preceded by standard
   attributes.  In this context, a statement is required, not a
   declaration, so attributes must be followed by a statement that is
   not just a semicolon.  Returns an attr_state.  */

స్థిర attr_state
c_parser_all_labels (c_parser *parser)
{
  attr_state attr = {};
  తార్కిక have_std_attrs;
  వృక్షం std_attrs = ఖాళీ;
  ఒకవేళ ((have_std_attrs = c_parser_nth_token_starts_std_లక్షణాలు (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  అయితే (c_parser_తదుపరి_token_is_keyword (parser, RID_CASE)
	 || c_parser_తదుపరి_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = ఖాళీ;
      ఒకవేళ ((have_std_attrs = c_parser_nth_token_starts_std_లక్షణాలు (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  ఒకవేళ (std_attrs
      && (!c_parser_handle_statement_omp_లక్షణాలు (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      ఒకవేళ (have_std_attrs && c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_వాడని_లక్షణాలు (std_attrs);
    }
  లేకపోతే ఒకవేళ (have_std_attrs && c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  తిరిగి attr;
}


/* Information used while parsing an OpenMP metadirective.  */
నిర్మాణం omp_metadirective_parse_దత్తాంశం {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<వృక్షం> * GTY((skip)) body_labels;
  గుర్తులేని పూర్ణాంకం region_అంకె;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
స్థిర వృక్షం
mangle_metadirective_region_label (c_parser *parser, వృక్షం name)
{
  ఒకవేళ (parser->omp_metadirective_state->body_labels->కలిగియుంది (name))
    {
      స్థిరరాశి అక్షరం *old_name = IDENTIFIER_సూచిక (name);
      అక్షరం *new_name = (అక్షరం *) XALLOCAVEC (అక్షరం, అక్షరశ్రేణి_పొడవు (old_name) + 32);
      sprintf (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_అంకె);
      తిరిగి get_identifier (new_name);
    }
  తిరిగి name;
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
స్థిర శూన్య
c_parser_label (c_parser *parser, వృక్షం std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  వృక్షం label = NULL_వృక్షం;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  తార్కిక fallthrough_p = c_parser_peek_token (parser)->flags & PREV_FALLTHROUGH;

  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_CASE))
    {
      వృక్షం exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_గమ్యం_rvalue (loc1,
				       c_parser_సమాసం_no_commas (parser, ఖాళీ),
				       నిజం, నిజం).విలువ;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_వృక్షం, std_attrs);
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_గమ్యం_rvalue (loc1,
					   c_parser_సమాసం_no_commas (parser,
								    ఖాళీ),
					   నిజం, నిజం).విలువ;
	  ఒకవేళ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      లేకపోతే
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_వృక్షం, NULL_వృక్షం, std_attrs);
    }
  లేకపోతే
    {
      వృక్షం name = c_parser_peek_token (parser)->విలువ;
      వృక్షం tlab;
      వృక్షం attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_తదుపరి_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_తదుపరి_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_లక్షణాలు (parser);
      ఒకవేళ (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      ఒకవేళ (tlab)
	{
	  decl_లక్షణాలు (&tlab, attrs, 0);
	  decl_లక్షణాలు (&tlab, std_attrs, 0);
	  label = కూడు_stmt (build_stmt (loc1, LABEL_సమాసం, tlab));
	}
      ఒకవేళ (attrs
	  && c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  ఒకవేళ (label)
    {
      ఒకవేళ (వృక్షం_సంకేతం (label) == LABEL_సమాసం)
	FALLTHROUGH_LABEL_P (LABEL_సమాసం_LABEL (label)) = fallthrough_p;
      లేకపోతే
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

స్థిర శూన్య
c_parser_statement (c_parser *parser, తార్కిక *if_p, location_t *loc_after_labels)
{
  వృక్షం before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  ఒకవేళ (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = అబద్ధం;
  c_parser_statement_after_labels (parser, if_p, before_labels, ఖాళీ, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

స్థిర వృక్షం
c_parser_bc_name (c_parser *parser, తార్కిక is_break)
{
  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME))
    తిరిగి NULL_వృక్షం;

  c_token *tok = c_parser_peek_token (parser);
  వృక్షం label = c_ముగింపు_bc_name (tok->location, tok->విలువ, is_break);
  c_parser_consume_token (parser);
  తిరిగి label;
}

/* Parse a statement, other than a labeled statement.  CHAIN is a vector
   of if-else-if conditions.  All labels and standard attributes have
   been parsed in the caller.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  ASTATE is an earlier parsed attribute state.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

స్థిర శూన్య
c_parser_statement_after_labels (c_parser *parser, తార్కిక *if_p,
				 వృక్షం before_labels,
				 vec<వృక్షం> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  వృక్షం stmt = NULL_వృక్షం;
  తార్కిక లోపల_if_ఖండం = parser->లోపల_if_ఖండం;
  parser->లోపల_if_ఖండం = అబద్ధం;
  ఒకవేళ (if_p != ఖాళీ)
    *if_p = అబద్ధం;

  ఒకవేళ (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    కూడు_debug_begin_stmt (loc);

 restart:
  ఎంపిక (c_parser_peek_token (parser)->type)
    {
    స్థితి CPP_OPEN_BRACE:
      కూడు_stmt (c_parser_compound_statement (parser));
      ఆపు;
    స్థితి CPP_KEYWORD:
      ఎంపిక (c_parser_peek_token (parser)->keyword)
	{
	స్థితి RID_IF:
	  c_parser_if_statement (parser, if_p, chain);
	  ఆపు;
	స్థితి RID_SWITCH:
	  c_parser_switch_statement (parser, if_p, before_labels);
	  ఆపు;
	స్థితి RID_WHILE:
	  c_parser_while_statement (parser, అబద్ధం, 0, అబద్ధం, if_p, before_labels);
	  ఆపు;
	స్థితి RID_DO:
	  c_parser_do_statement (parser, అబద్ధం, 0, అబద్ధం, before_labels);
	  ఆపు;
	స్థితి RID_FOR:
	  c_parser_for_statement (parser, అబద్ధం, 0, అబద్ధం, if_p, before_labels);
	  ఆపు;
	స్థితి RID_GOTO:
	  c_parser_consume_token (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	    {
	      వృక్షం name = c_parser_peek_token (parser)->విలువ;
	      ఒకవేళ (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_ముగింపు_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_MULT))
	    {
	      నిర్మాణం c_సమాసం val;

	      c_parser_consume_token (parser);
	      val = c_parser_వ్యక్తీకరణ (parser);
	      val = convert_lvalue_గమ్యం_rvalue (loc, val, అబద్ధం, నిజం);
	      stmt = c_ముగింపు_goto_ptr (loc, val);
	    }
	  లేకపోతే
	    c_parser_error (parser, "expected identifier or %<*%>");
	  వెళ్ళు expect_semicolon;
	స్థితి RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_ముగింపు_bc_stmt (loc, objc_foreach_continue_label, అబద్ధం,
				   c_parser_bc_name (parser, అబద్ధం));
	  వెళ్ళు expect_semicolon;
	స్థితి RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_ముగింపు_bc_stmt (loc, objc_foreach_break_label, నిజం,
				   c_parser_bc_name (parser, నిజం));
	  వెళ్ళు expect_semicolon;
	స్థితి RID_RETURN:
	  c_parser_consume_token (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_ముగింపు_return (loc, NULL_వృక్షం, NULL_వృక్షం,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  లేకపోతే
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      నిర్మాణం c_సమాసం సమాసం = c_parser_వ్యక్తీకరణ_conv (parser);
	      mark_exp_read (సమాసం.విలువ);
	      stmt = c_ముగింపు_return (సమాసం_LOC_OR_LOC (సమాసం.విలువ, xloc),
				      సమాసం.విలువ, సమాసం.original_type,
				      astate.musttail_p);
	      వెళ్ళు expect_semicolon;
	    }
	  ఆపు;
	స్థితి RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  ఆపు;
	స్థితి RID_TRANSACTION_ATOMIC:
	స్థితి RID_TRANSACTION_RELAXED:
	  stmt = c_parser_transaction (parser,
	      c_parser_peek_token (parser)->keyword);
	  ఆపు;
	స్థితి RID_TRANSACTION_CANCEL:
	  stmt = c_parser_transaction_cancel (parser);
	  వెళ్ళు expect_semicolon;
	స్థితి RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_వృక్షం);
	      c_parser_consume_token (parser);
	    }
	  లేకపోతే
	    {
	      నిర్మాణం c_సమాసం సమాసం = c_parser_వ్యక్తీకరణ (parser);
	      సమాసం = convert_lvalue_గమ్యం_rvalue (loc, సమాసం, అబద్ధం, అబద్ధం);
	      సమాసం.విలువ = c_fully_fold (సమాసం.విలువ, అబద్ధం, ఖాళీ);
	      stmt = objc_build_throw_stmt (loc, సమాసం.విలువ);
	      వెళ్ళు expect_semicolon;
	    }
	  ఆపు;
	స్థితి RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_finally_statement (parser);
	  ఆపు;
	స్థితి RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  ఆపు;
	స్థితి RID_ATTRIBUTE:
	  {
	    /* Allow '__attribute__((fallthrough));' or
	       '__attribute__((assume(cond)));' or
	       '__attribute__((musttail))) return'.  */
	    వృక్షం attrs = c_parser_gnu_లక్షణాలు (parser);
	    తార్కిక has_assume = lookup_attribute ("assume", attrs);
	    ఒకవేళ (has_assume)
	      {
		ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, నిజం);
		లేకపోతే
		  {
		    auto_urlify_లక్షణాలు sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<assume%> attribute not followed by %<;%>");
		    has_assume = అబద్ధం;
		  }
	      }
	    gcc_assert (!astate.musttail_p);
	    attrs = c_parser_handle_musttail (parser, attrs, astate);
	    ఒకవేళ (astate.musttail_p)
	      {
		ఒకవేళ (attrs)
		  {
		    auto_urlify_లక్షణాలు sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		వెళ్ళు restart;
	      }
	    ఒకవేళ (attribute_fallthrough_p (attrs))
	      {
		ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
		  {
		    వృక్షం fn = build_call_సమాసం_అంతర్గత_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_కణుపు, 0);
		    కూడు_stmt (fn);
		    /* Eat the ';'.  */
		    c_parser_consume_token (parser);
		  }
		లేకపోతే
		  {
		    auto_urlify_లక్షణాలు sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<fallthrough%> attribute not followed "
				"by %<;%>");
		  }
	      }
	    లేకపోతే ఒకవేళ (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    లేకపోతే ఒకవేళ (attrs != NULL_వృక్షం)
	      {
		auto_urlify_లక్షణాలు sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    ఆపు;
	  }
	అప్రమేయ:
	  వెళ్ళు సమాసం_stmt;
	}
      ఆపు;
    స్థితి CPP_SEMICOLON:
      c_parser_consume_token (parser);
      ఆపు;
    స్థితి CPP_CLOSE_PAREN:
    స్థితి CPP_CLOSE_వర్గం:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      ఆపు;
    స్థితి CPP_PRAGMA:
      ఒకవేళ (!c_parser_pragma (parser, pragma_stmt, if_p, before_labels))
        వెళ్ళు restart;
      ఆపు;
    అప్రమేయ:
    సమాసం_stmt:
      stmt = c_ముగింపు_సమాసం_stmt (loc, c_parser_వ్యక్తీకరణ_conv (parser).విలువ);
    expect_semicolon:
      c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
      ఆపు;
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
  ఒకవేళ (సమాసం_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_సమితి_సమాసం_location (stmt, loc);

  parser->లోపల_if_ఖండం = లోపల_if_ఖండం;
}

/* Parse the condition from an if, do, while or for statements.  */

స్థిర వృక్షం
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  వృక్షం cond;
  cond = c_parser_వ్యక్తీకరణ_conv (parser).విలువ;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, అబద్ధం, ఖాళీ);
  ఒకవేళ (warn_sequence_బిందువు)
    verify_sequence_points (cond);
  తిరిగి cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

స్థిర వృక్షం
c_parser_paren_condition (c_parser *parser)
{
  వృక్షం cond;
  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి error_mark_కణుపు;
  cond = c_parser_condition (parser);
  parens.skip_until_దొరికింది_close (parser);
  తిరిగి cond;
}

/* Parse a selection-header:

   selection-header:
వ్యక్తీకరణ
     declaration expression
     simple-declaration

   simple-declaration:
     attribute-specifier-sequence[opt] declaration-specifiers declarator
       = initializer

  SWITCH_P is true if we are called from c_parser_switch_statement; in
  that case, don't perform the truthvalue conversion.  */

స్థిర c_సమాసం
c_parser_selection_శీర్షిక (c_parser *parser, తార్కిక switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_సమాసం సమాసం;
  తార్కిక parse_సమాసం = నిజం;
  వృక్షం std_attrs;
  తార్కిక have_std_attrs = c_parser_nth_token_starts_std_లక్షణాలు (parser, 1);
  ఒకవేళ (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  లేకపోతే
    std_attrs = NULL_వృక్షం;
  ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      సమాసం.విలువ
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/అబద్ధం,
					 /*static_assert_ok=*/అబద్ధం,
					 /*empty_ok=*/అబద్ధం,
					 /*nested=*/నిజం,
					 /*start_attr_ok=*/నిజం,
					 /*simple_ok=*/నిజం,
					 /*objc_foreach_object_decl=*/శూన్యసూచిక,
					 /*omp_declare_simd_clauses=*/శూన్యసూచిక,
					 have_std_attrs,
					 std_attrs);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      లేకపోతే
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  ఒకవేళ (!సమాసం.విలువ)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      సమాసం.original_type = error_mark_కణుపు;
	      సమాసం.సమితి_error ();
	      తిరిగి సమాసం;
	    }
	  parse_సమాసం = అబద్ధం;
	}
      ఒకవేళ (సమాసం.విలువ)
	{
	  సమాసం.original_type = వృక్షం_TYPE (సమాసం.విలువ);
	  సమాసం = convert_lvalue_గమ్యం_rvalue (loc, సమాసం, /*convert_p=*/నిజం,
					   /*read_p=*/నిజం);
	}
    }
  లేకపోతే ఒకవేళ (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      సమాసం.original_type = error_mark_కణుపు;
      సమాసం.సమితి_error ();
      తిరిగి సమాసం;
    }

  ఒకవేళ (parse_సమాసం)
    సమాసం = c_parser_వ్యక్తీకరణ_conv (parser);
  ఒకవేళ (!switch_p)
    {
      సమాసం.విలువ = c_objc_common_truthvalue_conversion (loc, సమాసం.విలువ);
      సమాసం.విలువ = c_fully_fold (సమాసం.విలువ, అబద్ధం, ఖాళీ);
      ఒకవేళ (warn_sequence_బిందువు)
	verify_sequence_points (సమాసం.విలువ);
    }
  తిరిగి సమాసం;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

స్థిర వృక్షం
c_parser_paren_selection_శీర్షిక (c_parser *parser)
{
  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి error_mark_కణుపు;
  వృక్షం cond = c_parser_selection_శీర్షిక (parser, /*switch_p=*/అబద్ధం).విలువ;
  parens.skip_until_దొరికింది_close (parser);
  తిరిగి cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

స్థిర వృక్షం
c_parser_c99_ఖండం_statement (c_parser *parser, తార్కిక *if_p,
			      location_t *loc_after_labels)
{
  వృక్షం ఖండం = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  తిరిగి c_చివర_compound_stmt (loc, ఖండం, flag_isoc99);
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

స్థిర వృక్షం
c_parser_if_body (c_parser *parser, తార్కిక *if_p,
		  స్థిరరాశి token_indent_info &if_tinfo)
{
  వృక్షం ఖండం = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  వృక్షం before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      కూడు_stmt (build_ఖాళీలు_stmt (loc));
      c_parser_consume_token (parser);
      ఒకవేళ (!c_parser_తదుపరి_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
    కూడు_stmt (c_parser_compound_statement (parser));
  లేకపోతే
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, ఖాళీ, a);
    }

  token_indent_info తదుపరి_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, తదుపరి_tinfo);
  ఒకవేళ (body_loc_after_labels != UNKNOWN_LOCATION
      && తదుపరి_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, తదుపరి_tinfo.location,
				    if_tinfo.location, RID_IF);

  తిరిగి c_చివర_compound_stmt (body_loc, ఖండం, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

స్థిర వృక్షం
c_parser_else_body (c_parser *parser, స్థిరరాశి token_indent_info &else_tinfo,
		    vec<వృక్షం> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  వృక్షం ఖండం = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  వృక్షం before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      warning_at (loc,
		  OPT_Wempty_body,
	         "suggest braces around empty body in an %<else%> statement");
      కూడు_stmt (build_ఖాళీలు_stmt (loc));
      c_parser_consume_token (parser);
    }
  లేకపోతే
    {
      ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, ఖాళీ, before_labels, chain, a);
    }

  token_indent_info తదుపరి_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, తదుపరి_tinfo);
  ఒకవేళ (body_loc_after_labels != UNKNOWN_LOCATION
      && తదుపరి_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, తదుపరి_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  తిరిగి c_చివర_compound_stmt (body_loc, ఖండం, flag_isoc99);
}

/* Parse an if statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   if-statement:
     if ( selection-header ) statement
     if ( selection-header ) statement else statement

   CHAIN is a vector of if-else-if conditions.
   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

స్థిర శూన్య
c_parser_if_statement (c_parser *parser, తార్కిక *if_p, vec<వృక్షం> *chain)
{
  వృక్షం ఖండం;
  location_t loc;
  వృక్షం cond;
  తార్కిక nested_if = అబద్ధం;
  వృక్షం మొదటి_body, రెండవ_body;
  తార్కిక లోపల_if_ఖండం;

  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_IF));
  token_indent_info if_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  c_parser_consume_token (parser);
  ఖండం = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_selection_శీర్షిక (parser);
  లోపల_if_ఖండం = parser->లోపల_if_ఖండం;
  parser->లోపల_if_ఖండం = నిజం;
  మొదటి_body = c_parser_if_body (parser, &nested_if, if_tinfo);
  parser->లోపల_if_ఖండం = లోపల_if_ఖండం;

  ఒకవేళ (warn_duplicated_cond)
    warn_duplicated_cond_కూడు_or_warn (సమాసం_LOCATION (cond), cond, &chain);

  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      ఒకవేళ (warn_duplicated_cond)
	{
	  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_IF)
	      && chain == ఖాళీ)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = కొత్త vec<వృక్షం> ();
	      ఒకవేళ (!CONSTANT_CLASS_P (cond) && !వృక్షం_SIDE_EFFECTS (cond))
		chain->సురక్షిత_నెట్టు (cond);
	    }
	  లేకపోతే ఒకవేళ (!c_parser_తదుపరి_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      రెండవ_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      ఒకవేళ (if_p != ఖాళీ)
	*if_p = నిజం;
    }
  లేకపోతే
    {
      రెండవ_body = NULL_వృక్షం;

      /* Diagnose an ambiguous else if if-then-else is nested inside
	 if-then.  */
      ఒకవేళ (nested_if)
	warning_at (loc, OPT_Wdangling_else,
		    "suggest explicit braces to avoid ambiguous %<else%>");

      ఒకవేళ (warn_duplicated_cond)
	/* This if statement does not have an else clause.  We don't
	   need the condition chain anymore.  */
	vec_free (chain);
    }
  c_ముగింపు_if_stmt (loc, cond, మొదటి_body, రెండవ_body);
  కూడు_stmt (c_చివర_compound_stmt (loc, ఖండం, flag_isoc99));

  c_parser_maybe_reclassify_token (parser);
}

/* Parse a switch statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   switch-statement:
     switch (expression) statement

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

స్థిర శూన్య
c_parser_switch_statement (c_parser *parser, తార్కిక *if_p, వృక్షం before_labels)
{
  నిర్మాణం c_సమాసం ce;
  వృక్షం ఖండం, సమాసం, body;
  గుర్తులేని అక్షరం save_లోపల_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  వృక్షం switch_name;
  పూర్ణాంకం అంకె_పేర్లు = c_get_loop_పేర్లు (before_labels, నిజం, &switch_name);
  ఖండం = c_begin_compound_stmt (flag_isoc99);
  తార్కిక explicit_cast_p = అబద్ధం;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = నిజం;
      ce = c_parser_selection_శీర్షిక (parser, /*switch_p=*/నిజం);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_గమ్యం_rvalue (switch_cond_loc, ce, నిజం, నిజం);
      సమాసం = ce.విలువ;
      /* ??? expr has no valid location?  */
      parens.skip_until_దొరికింది_close (parser);
    }
  లేకపోతే
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      సమాసం = error_mark_కణుపు;
      ce.original_type = error_mark_కణుపు;
    }
  వృక్షం stmt
    = c_ప్రారంభం_switch (switch_loc, switch_cond_loc, సమాసం, explicit_cast_p,
		      switch_name);
  save_లోపల_statement = లోపల_statement;
  లోపల_statement |= లోపల_SWITCH_STMT;
  ఒకవేళ (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      లోపల_statement |= లోపల_NAMED_STMT;
    }
  లేకపోతే
    లోపల_statement &= ~లోపల_NAMED_STMT;
  location_t loc_after_labels;
  తార్కిక open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_ఖండం_statement (parser, if_p, &loc_after_labels);
  location_t తదుపరి_loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, తదుపరి_loc, switch_loc,
				    RID_SWITCH);
  c_ముగింపు_switch (body, ce.original_type);
  లోపల_statement = save_లోపల_statement;
  ఒకవేళ (అంకె_పేర్లు)
    {
      ఒకవేళ (!C_DECL_LOOP_SWITCH_NAME_వాడిన (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_వృక్షం;
      లేకపోతే
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_పేర్లు (అంకె_పేర్లు);
    }
  కూడు_stmt (c_చివర_compound_stmt (switch_loc, ఖండం, flag_isoc99));
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

స్థిర శూన్య
c_parser_while_statement (c_parser *parser, తార్కిక ivdep, గుర్తులేని పొట్టి unroll,
			  తార్కిక novector, తార్కిక *if_p, వృక్షం before_labels)
{
  వృక్షం ఖండం, cond, body;
  గుర్తులేని అక్షరం save_లోపల_statement;
  location_t loc;
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  వృక్షం loop_name;
  పూర్ణాంకం అంకె_పేర్లు = c_get_loop_పేర్లు (before_labels, అబద్ధం, &loop_name);

  ఒకవేళ (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = నిజం;
    }

  c_parser_consume_token (parser);
  ఖండం = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  ఒకవేళ (ivdep && cond != error_mark_కణుపు)
    cond = build3 (ANNOTATE_సమాసం, వృక్షం_TYPE (cond), cond,
		   build_int_cst (integer_type_కణుపు,
				  annot_సమాసం_ivdep_రకం),
		   integer_zero_కణుపు);
  ఒకవేళ (unroll && cond != error_mark_కణుపు)
    cond = build3 (ANNOTATE_సమాసం, వృక్షం_TYPE (cond), cond,
		   build_int_cst (integer_type_కణుపు,
				  annot_సమాసం_unroll_రకం),
		   build_int_cst (integer_type_కణుపు, unroll));
  ఒకవేళ (novector && cond != error_mark_కణుపు)
    cond = build3 (ANNOTATE_సమాసం, వృక్షం_TYPE (cond), cond,
		   build_int_cst (integer_type_కణుపు,
				  annot_సమాసం_no_సదిశ_రకం),
		   integer_zero_కణుపు);
  save_లోపల_statement = లోపల_statement;
  లోపల_statement = లోపల_ITERATION_STMT;
  ఒకవేళ (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      లోపల_statement |= లోపల_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  తార్కిక open_brace = c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_ఖండం_statement (parser, if_p, &loc_after_labels);
  ఒకవేళ (loop_name && !C_DECL_LOOP_SWITCH_NAME_వాడిన (loop_name))
    loop_name = NULL_వృక్షం;
  కూడు_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_వృక్షం,
			NULL_వృక్షం));
  కూడు_stmt (c_చివర_compound_stmt (loc, ఖండం, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  ఒకవేళ (అంకె_పేర్లు)
    c_release_loop_పేర్లు (అంకె_పేర్లు);

  token_indent_info తదుపరి_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, తదుపరి_tinfo);

  ఒకవేళ (తదుపరి_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, తదుపరి_tinfo.location,
				    while_tinfo.location, RID_WHILE);

  లోపల_statement = save_లోపల_statement;
}

/* Parse a do statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   do-statement:
     do statement while ( expression ) ;

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

స్థిర శూన్య
c_parser_do_statement (c_parser *parser, తార్కిక ivdep, గుర్తులేని పొట్టి unroll,
		       తార్కిక novector, వృక్షం before_labels)
{
  వృక్షం ఖండం, cond, body;
  గుర్తులేని అక్షరం save_లోపల_statement;
  location_t loc;
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_DO));
  వృక్షం loop_name;
  పూర్ణాంకం అంకె_పేర్లు = c_get_loop_పేర్లు (before_labels, అబద్ధం, &loop_name);

  ఒకవేళ (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = నిజం;
    }

  c_parser_consume_token (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  ఖండం = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_లోపల_statement = లోపల_statement;
  లోపల_statement = లోపల_ITERATION_STMT;
  ఒకవేళ (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      లోపల_statement |= లోపల_NAMED_STMT;
    }
  body = c_parser_c99_ఖండం_statement (parser, ఖాళీ);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  లోపల_statement = save_లోపల_statement;
  ఒకవేళ (అంకె_పేర్లు)
    {
      ఒకవేళ (!C_DECL_LOOP_SWITCH_NAME_వాడిన (loop_name))
	loop_name = NULL_వృక్షం;
      c_release_loop_పేర్లు (అంకె_పేర్లు);
    }
  cond = c_parser_paren_condition (parser);
  ఒకవేళ (ivdep && cond != error_mark_కణుపు)
    cond = build3 (ANNOTATE_సమాసం, వృక్షం_TYPE (cond), cond,
		   build_int_cst (integer_type_కణుపు,
				  annot_సమాసం_ivdep_రకం),
		   integer_zero_కణుపు);
  ఒకవేళ (unroll && cond != error_mark_కణుపు)
    cond = build3 (ANNOTATE_సమాసం, వృక్షం_TYPE (cond), cond,
		   build_int_cst (integer_type_కణుపు,
				  annot_సమాసం_unroll_రకం),
 		   build_int_cst (integer_type_కణుపు, unroll));
  ఒకవేళ (novector && cond != error_mark_కణుపు)
    cond = build3 (ANNOTATE_సమాసం, వృక్షం_TYPE (cond), cond,
		   build_int_cst (integer_type_కణుపు,
				  annot_సమాసం_no_సదిశ_రకం),
		   integer_zero_కణుపు);
  ఒకవేళ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);

  కూడు_stmt (build_stmt (loc, DO_STMT, cond, body, loop_name));
  కూడు_stmt (c_చివర_compound_stmt (loc, ఖండం, flag_isoc99));
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

స్థిర శూన్య
c_parser_for_statement (c_parser *parser, తార్కిక ivdep, గుర్తులేని పొట్టి unroll,
			తార్కిక novector, తార్కిక *if_p, వృక్షం before_labels)
{
  వృక్షం ఖండం, cond, incr, body;
  గుర్తులేని అక్షరం save_లోపల_statement;
  వృక్షం save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  వృక్షం object_వ్యక్తీకరణ;
  /* Silence the bogus uninitialized warning.  */
  వృక్షం collection_వ్యక్తీకరణ = ఖాళీ;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  తార్కిక is_foreach_statement = అబద్ధం;
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  వృక్షం loop_name;
  పూర్ణాంకం అంకె_పేర్లు = c_get_loop_పేర్లు (before_labels, అబద్ధం, &loop_name);

  ఒకవేళ (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = నిజం;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  ఖండం = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_కణుపు;
  incr = error_mark_కణుపు;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_వ్యక్తీకరణ = error_mark_కణుపు;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = అబద్ధం;
	  c_parser_consume_token (parser);
	  c_ముగింపు_సమాసం_stmt (loc, NULL_వృక్షం);
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_declaration (parser)
	       || c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, నిజం, నిజం, నిజం, నిజం, నిజం,
					 అబద్ధం, &object_వ్యక్తీకరణ);
	  parser->objc_could_be_foreach_context = అబద్ధం;

	  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_లోపల))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = నిజం;
	      ఒకవేళ (check_for_loop_decls (for_loc, నిజం) == NULL_వృక్షం)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  లేకపోతే
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  అయితే (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_లక్షణాలు (parser, 2))
	    {
	      పూర్ణాంకం ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, నిజం, నిజం, నిజం, నిజం,
					     నిజం, అబద్ధం, &object_వ్యక్తీకరణ);
	      parser->objc_could_be_foreach_context = అబద్ధం;

	      restore_extension_diagnostics (ext);
	      ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_లోపల))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = నిజం;
		  ఒకవేళ (check_for_loop_decls (for_loc, నిజం) == NULL_వృక్షం)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      లేకపోతే
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  లేకపోతే
	    వెళ్ళు init_సమాసం;
	}
      లేకపోతే
	{
	init_సమాసం:
	  {
	    నిర్మాణం c_సమాసం ce;
	    వృక్షం init_వ్యక్తీకరణ;
	    ce = c_parser_వ్యక్తీకరణ (parser);
	    init_వ్యక్తీకరణ = ce.విలువ;
	    parser->objc_could_be_foreach_context = అబద్ధం;
	    ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_లోపల))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = నిజం;
		ఒకవేళ (! lvalue_p (init_వ్యక్తీకరణ))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_వ్యక్తీకరణ
		  = c_fully_fold (init_వ్యక్తీకరణ, అబద్ధం, ఖాళీ);
	      }
	    లేకపోతే
	      {
		ce = convert_lvalue_గమ్యం_rvalue (loc, ce, నిజం, అబద్ధం);
		init_వ్యక్తీకరణ = ce.విలువ;
		c_ముగింపు_సమాసం_stmt (loc, init_వ్యక్తీకరణ);
		c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      ఒకవేళ (!is_foreach_statement)
	{
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
	    {
	      ఒకవేళ (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_కణుపు;
		}
	      లేకపోతే ఒకవేళ (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_కణుపు;
		}
	      లేకపోతే
		{
		  c_parser_consume_token (parser);
		  cond = NULL_వృక్షం;
		}
	    }
	  లేకపోతే
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  ఒకవేళ (ivdep && cond != error_mark_కణుపు)
	    cond = build3 (ANNOTATE_సమాసం, వృక్షం_TYPE (cond), cond,
			   build_int_cst (integer_type_కణుపు,
					  annot_సమాసం_ivdep_రకం),
			   integer_zero_కణుపు);
	  ఒకవేళ (unroll && cond != error_mark_కణుపు)
	    cond = build3 (ANNOTATE_సమాసం, వృక్షం_TYPE (cond), cond,
 			   build_int_cst (integer_type_కణుపు,
					  annot_సమాసం_unroll_రకం),
			   build_int_cst (integer_type_కణుపు, unroll));
	  ఒకవేళ (novector && cond && cond != error_mark_కణుపు)
	    cond = build3 (ANNOTATE_సమాసం, వృక్షం_TYPE (cond), cond,
			   build_int_cst (integer_type_కణుపు,
					  annot_సమాసం_no_సదిశ_రకం),
			   integer_zero_కణుపు);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ఒకవేళ (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_వ్యక్తీకరణ = error_mark_కణుపు;
	    }
	  లేకపోతే
	    incr = c_process_సమాసం_stmt (loc, NULL_వృక్షం);
	}
      లేకపోతే
	{
	  ఒకవేళ (is_foreach_statement)
	    collection_వ్యక్తీకరణ
	      = c_fully_fold (c_parser_వ్యక్తీకరణ (parser).విలువ, అబద్ధం, ఖాళీ);
	  లేకపోతే
	    {
	      నిర్మాణం c_సమాసం ce = c_parser_వ్యక్తీకరణ (parser);
	      ce = convert_lvalue_గమ్యం_rvalue (loc, ce, నిజం, అబద్ధం);
	      incr = c_process_సమాసం_stmt (loc, ce.విలువ);
	    }
	}
      parens.skip_until_దొరికింది_close (parser);
    }
  save_లోపల_statement = లోపల_statement;
  ఒకవేళ (is_foreach_statement)
    {
      లోపల_statement = లోపల_OBJC_FOREACH;
      save_objc_foreach_break_label = objc_foreach_break_label;
      save_objc_foreach_continue_label = objc_foreach_continue_label;
      objc_foreach_break_label = create_artificial_label (loc);
      objc_foreach_continue_label = create_artificial_label (loc);
      ఒకవేళ (loop_name)
	{
	  gcc_checking_assert (!DECL_CHAIN (loop_name)
			       && !DECL_CHAIN (objc_foreach_break_label));
	  C_DECL_SWITCH_NAME (loop_name) = 1;
	  DECL_CHAIN (loop_name) = objc_foreach_break_label;
	  DECL_CHAIN (objc_foreach_break_label) = objc_foreach_continue_label;
	}
    }
  లేకపోతే
    లోపల_statement = లోపల_ITERATION_STMT;
  ఒకవేళ (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      లోపల_statement |= లోపల_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  తార్కిక open_brace = c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_ఖండం_statement (parser, if_p, &loc_after_labels);

  ఒకవేళ (loop_name && is_foreach_statement)
    {
      gcc_checking_assert (DECL_CHAIN (loop_name) == objc_foreach_break_label
			   && (DECL_CHAIN (objc_foreach_break_label)
			       == objc_foreach_continue_label));
      C_DECL_SWITCH_NAME (loop_name) = 0;
      DECL_CHAIN (loop_name) = NULL_వృక్షం;
      DECL_CHAIN (objc_foreach_break_label) = NULL_వృక్షం;
    }

  ఒకవేళ (is_foreach_statement)
    objc_ముగింపు_foreach_loop (for_loc, object_వ్యక్తీకరణ,
			      collection_వ్యక్తీకరణ, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  లేకపోతే
    కూడు_stmt (build_stmt (for_loc, FOR_STMT, NULL_వృక్షం, cond, incr,
			  body, NULL_వృక్షం,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_వాడిన (loop_name)
			  ? loop_name : NULL_వృక్షం, NULL_వృక్షం, NULL_వృక్షం));
  కూడు_stmt (c_చివర_compound_stmt (for_loc, ఖండం,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info తదుపరి_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, తదుపరి_tinfo);

  ఒకవేళ (తదుపరి_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, తదుపరి_tinfo.location,
				    for_tinfo.location, RID_FOR);

  లోపల_statement = save_లోపల_statement;
  ఒకవేళ (అంకె_పేర్లు)
    c_release_loop_పేర్లు (అంకె_పేర్లు);
  ఒకవేళ (is_foreach_statement)
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

స్థిర వృక్షం
c_parser_asm_statement (c_parser *parser)
{
  వృక్షం str, outputs, inputs, clobbers, labels, ret;
  తార్కిక simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  పూర్ణాంకం section, nsections;

  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);

  /* Handle the asm-qualifier-list.  */
  location_t volatile_loc = UNKNOWN_LOCATION;
  location_t inline_loc = UNKNOWN_LOCATION;
  location_t goto_loc = UNKNOWN_LOCATION;
  కొరకు (;;)
    {
      c_token *token = c_parser_peek_token (parser);
      location_t loc = token->location;
      ఎంపిక (token->keyword)
	{
	స్థితి RID_VOLATILE:
	  ఒకవేళ (volatile_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->విలువ);
	      inform (volatile_loc, "first seen here");
	    }
	  లేకపోతే
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  కొనసాగు;

	స్థితి RID_INLINE:
	  ఒకవేళ (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->విలువ);
	      inform (inline_loc, "first seen here");
	    }
	  లేకపోతే
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  కొనసాగు;

	స్థితి RID_GOTO:
	  ఒకవేళ (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->విలువ);
	      inform (goto_loc, "first seen here");
	    }
	  లేకపోతే
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  కొనసాగు;

	స్థితి RID_CONST:
	స్థితి RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->విలువ);
	  c_parser_consume_token (parser);
	  కొనసాగు;

	అప్రమేయ:
	  ఆపు;
	}
      ఆపు;
    }

  తార్కిక is_volatile = (volatile_loc != UNKNOWN_LOCATION);
  తార్కిక is_inline = (inline_loc != UNKNOWN_LOCATION);
  తార్కిక is_goto = (goto_loc != UNKNOWN_LOCATION);

  ret = ఖాళీ;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    వెళ్ళు error;

  str = c_parser_asm_string_literal (parser);
  ఒకవేళ (str == NULL_వృక్షం)
    వెళ్ళు error_close_paren;

  simple = నిజం;
  outputs = NULL_వృక్షం;
  inputs = NULL_వృక్షం;
  clobbers = NULL_వృక్షం;
  labels = NULL_వృక్షం;

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    వెళ్ళు పూర్తి_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  కొరకు (section = 0; section < nsections; ++section)
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  ఒకవేళ (section == nsections)
	    {
	      c_parser_error (parser, "expected %<)%>");
	      వెళ్ళు error_close_paren;
	    }
	  c_parser_consume_token (parser);
	}
      లేకపోతే ఒకవేళ (!c_parser_require (parser, CPP_COLON,
				  is_goto
				  ? G_("expected %<:%>")
				  : G_("expected %<:%> or %<)%>"),
				  UNKNOWN_LOCATION, is_goto))
	వెళ్ళు error_close_paren;

      /* Once past any colon, we're no longer a simple asm.  */
      simple = అబద్ధం;

      ఒకవేళ ((!c_parser_తదుపరి_token_is (parser, CPP_COLON)
	   && !c_parser_తదుపరి_token_is (parser, CPP_SCOPE)
	   && !c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	  || section == 3)
	ఎంపిక (section)
	  {
	  స్థితి 0:
	    outputs = c_parser_asm_operands (parser);
	    ఆపు;
	  స్థితి 1:
	    inputs = c_parser_asm_operands (parser);
	    ఆపు;
	  స్థితి 2:
	    clobbers = c_parser_asm_clobbers (parser);
	    ఆపు;
	  స్థితి 3:
	    labels = c_parser_asm_goto_operands (parser);
	    ఆపు;
	  అప్రమేయ:
	    gcc_unreachable ();
	  }

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	వెళ్ళు పూర్తి_asm;
    }

 పూర్తి_asm:
  ఒకవేళ (!parens.require_close (parser))
    {
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
      వెళ్ళు error;
    }

  ఒకవేళ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_సమాసం (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  తిరిగి ret;

 error_close_paren:
  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
  వెళ్ళు error;
}

/* Parse asm operands, a GNU extension.

   asm-operands:
     asm-operand
     asm-operands , asm-operand

   asm-operand:
     asm-string-literal ( expression )
     [ identifier ] asm-string-literal ( expression )
*/

స్థిర వృక్షం
c_parser_asm_operands (c_parser *parser)
{
  వృక్షం list = NULL_వృక్షం;
  అయితే (నిజం)
    {
      వృక్షం name, str;
      నిర్మాణం c_సమాసం సమాసం;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_వర్గం))
	{
	  c_parser_consume_token (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	    {
	      వృక్షం id = c_parser_peek_token (parser)->విలువ;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_నిడివి (id),
				   IDENTIFIER_సూచిక (id));
	    }
	  లేకపోతే
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_వర్గం, ఖాళీ);
	      తిరిగి NULL_వృక్షం;
	    }
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_వర్గం,
				     "expected %<]%>");
	}
      లేకపోతే
	name = NULL_వృక్షం;
      str = c_parser_asm_string_literal (parser);
      ఒకవేళ (str == NULL_వృక్షం)
	తిరిగి NULL_వృక్షం;
      matching_parens parens;
      ఒకవేళ (!parens.require_open (parser))
	తిరిగి NULL_వృక్షం;
      సమాసం = c_parser_వ్యక్తీకరణ (parser);
      mark_exp_read (సమాసం.విలువ);
      ఒకవేళ (!parens.require_close (parser))
	{
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
	  తిరిగి NULL_వృక్షం;
	}
      list = chainon (list, build_వృక్షం_list (build_వృక్షం_list (name, str),
					     సమాసం.విలువ));
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      లేకపోతే
	ఆపు;
    }
  తిరిగి list;
}

/* Parse asm clobbers, a GNU extension.

   asm-clobbers:
     asm-string-literal
     asm-clobbers , asm-string-literal
*/

స్థిర వృక్షం
c_parser_asm_clobbers (c_parser *parser)
{
  వృక్షం list = NULL_వృక్షం;
  అయితే (నిజం)
    {
      వృక్షం str = c_parser_asm_string_literal (parser);
      ఒకవేళ (str)
	list = వృక్షం_cons (NULL_వృక్షం, str, list);
      లేకపోతే
	తిరిగి NULL_వృక్షం;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      లేకపోతే
	ఆపు;
    }
  తిరిగి list;
}

/* Parse asm goto labels, a GNU extension.

   asm-goto-operands:
     identifier
     asm-goto-operands , identifier
*/

స్థిర వృక్షం
c_parser_asm_goto_operands (c_parser *parser)
{
  వృక్షం list = NULL_వృక్షం;
  అయితే (నిజం)
    {
      వృక్షం name, label;

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->విలువ;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  వృక్షం_వాడిన (label) = 1;
	}
      లేకపోతే
	{
	  c_parser_error (parser, "expected identifier");
	  తిరిగి NULL_వృక్షం;
	}

      name = build_string (IDENTIFIER_నిడివి (name),
			   IDENTIFIER_సూచిక (name));
      list = వృక్షం_cons (name, label, list);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      లేకపోతే
	తిరిగి nreverse (list);
    }
}

/* Parse a possibly concatenated sequence of string literals.
   TRANSLATE says whether to translate them to the execution character
   set; WIDE_OK says whether any kind of prefixed string literal is
   permitted in this context.  This code is based on that in
   lex_string.  */

నిర్మాణం c_సమాసం
c_parser_string_literal (c_parser *parser, తార్కిక translate, తార్కిక wide_ok)
{
  నిర్మాణం c_సమాసం ret;
  కొలత_t లెక్క;
  నిర్మాణం obstack str_ob;
  నిర్మాణం obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, చివరి_tok_loc;
  గణన cpp_ttype type;
  వృక్షం విలువ, string_వృక్షం;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  చివరి_tok_loc = linemap_resolve_location (పంక్తి_పట్టిక, loc,
					   LRK_MACRO_DEFINITION_LOCATION,
					   ఖాళీ);
  type = tok->type;
  ఎంపిక (type)
    {
    స్థితి CPP_STRING:
    స్థితి CPP_WSTRING:
    స్థితి CPP_STRING16:
    స్థితి CPP_STRING32:
    స్థితి CPP_UTF8STRING:
      string_వృక్షం = tok->విలువ;
      ఆపు;

    అప్రమేయ:
      c_parser_error (parser, "expected string literal");
      ret.సమితి_error ();
      ret.విలువ = NULL_వృక్షం;
      ret.original_సంకేతం = ERROR_MARK;
      ret.original_type = NULL_వృక్షం;
      తిరిగి ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  ఎంపిక (c_parser_peek_2nd_token (parser)->type)
    {
    అప్రమేయ:
      c_parser_consume_token (parser);
      str.పాఠ్యం = (స్థిరరాశి గుర్తులేని అక్షరం *) వృక్షం_STRING_సూచిక (string_వృక్షం);
      str.len = వృక్షం_STRING_నిడివి (string_వృక్షం);
      లెక్క = 1;
      strs = &str;
      ఆపు;

    స్థితి CPP_STRING:
    స్థితి CPP_WSTRING:
    స్థితి CPP_STRING16:
    స్థితి CPP_STRING32:
    స్థితి CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      లెక్క = 0;
      చేయి
	{
	  c_parser_consume_token (parser);
	  లెక్క++;
	  str.పాఠ్యం = (స్థిరరాశి గుర్తులేని అక్షరం *) వృక్షం_STRING_సూచిక (string_వృక్షం);
	  str.len = వృక్షం_STRING_నిడివి (string_వృక్షం);
	  ఒకవేళ (type != tok->type)
	    {
	      ఒకవేళ (type == CPP_STRING)
		type = tok->type;
	      లేకపోతే ఒకవేళ (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, పరిమాణం (cpp_string));
	  obstack_grow (&loc_ob, &చివరి_tok_loc, పరిమాణం (location_t));
	  tok = c_parser_peek_token (parser);
	  string_వృక్షం = tok->విలువ;
	  చివరి_tok_loc
	    = linemap_resolve_location (పంక్తి_పట్టిక, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, ఖాళీ);
	}
      అయితే (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_ముగింపు (&str_ob);
    }

  ఒకవేళ (లెక్క > 1 && !లోపల_system_శీర్షిక_at (ఆదానం_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  ఒకవేళ ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_లోపల, strs, లెక్క, &istr, type)))
    {
      విలువ = build_string (istr.len, (స్థిరరాశి అక్షరం *) istr.పాఠ్యం);
      విడుదల (const_cast<గుర్తులేని అక్షరం *> (istr.పాఠ్యం));
      ఒకవేళ (లెక్క > 1)
	{
	  location_t *locs = (location_t *) obstack_ముగింపు (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->రికార్డు_string_concatenation (లెక్క, locs);
	}
    }
  లేకపోతే
    {
      ఒకవేళ (type != CPP_STRING && !wide_ok)
	{
	  error_at (loc, "a wide string is invalid in this context");
	  type = CPP_STRING;
	}
      /* Callers cannot generally handle error_mark_node in this
	 context, so return the empty string instead.  An error has
	 been issued, either above or from cpp_interpret_string.  */
      ఎంపిక (type)
	{
	అప్రమేయ:
	స్థితి CPP_STRING:
	స్థితి CPP_UTF8STRING:
	  ఒకవేళ (type == CPP_UTF8STRING && flag_char8_t)
	    {
	      విలువ = build_string (TYPE_PRECISION (char8_type_కణుపు)
				    / TYPE_PRECISION (char_type_కణుపు),
				    "");  /* char8_t is 8 bits */
	    }
	  లేకపోతే
	    విలువ = build_string (1, "");
	  ఆపు;
	స్థితి CPP_STRING16:
	  విలువ = build_string (TYPE_PRECISION (char16_type_కణుపు)
				/ TYPE_PRECISION (char_type_కణుపు),
				"\0");  /* char16_t is 16 bits */
	  ఆపు;
	స్థితి CPP_STRING32:
	  విలువ = build_string (TYPE_PRECISION (char32_type_కణుపు)
				/ TYPE_PRECISION (char_type_కణుపు),
				"\0\0\0");  /* char32_t is 32 bits */
	  ఆపు;
	స్థితి CPP_WSTRING:
	  విలువ = build_string (TYPE_PRECISION (wchar_type_కణుపు)
				/ TYPE_PRECISION (char_type_కణుపు),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  ఆపు;
        }
    }

  ఎంపిక (type)
    {
    అప్రమేయ:
    స్థితి CPP_STRING:
      వృక్షం_TYPE (విలువ) = char_array_type_కణుపు;
      ఆపు;
    స్థితి CPP_UTF8STRING:
      ఒకవేళ (flag_char8_t)
	వృక్షం_TYPE (విలువ) = char8_array_type_కణుపు;
      లేకపోతే
	వృక్షం_TYPE (విలువ) = char_array_type_కణుపు;
      ఆపు;
    స్థితి CPP_STRING16:
      వృక్షం_TYPE (విలువ) = char16_array_type_కణుపు;
      ఆపు;
    స్థితి CPP_STRING32:
      వృక్షం_TYPE (విలువ) = char32_array_type_కణుపు;
      ఆపు;
    స్థితి CPP_WSTRING:
      వృక్షం_TYPE (విలువ) = wchar_array_type_కణుపు;
    }
  విలువ = fix_string_type (విలువ);

  ఒకవేళ (లెక్క > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.విలువ = విలువ;
  ret.original_సంకేతం = STRING_CST;
  ret.original_type = NULL_వృక్షం;
  సమితి_c_సమాసం_ఆధారం_range (&ret, get_range_from_loc (పంక్తి_పట్టిక, loc));
  ret.m_decimal = 0;
  parser->చూసిన_string_literal = నిజం;
  తిరిగి ret;
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

స్థిర నిర్మాణం c_సమాసం
c_parser_సమాసం_no_commas (c_parser *parser, నిర్మాణం c_సమాసం *after,
			 వృక్షం omp_atomic_lhs)
{
  నిర్మాణం c_సమాసం lhs, rhs, ret;
  గణన వృక్షం_సంకేతం_2 సంకేతం_2;
  location_t op_location, exp_location;
  తార్కిక save_లోపల_omp_for = c_లోపల_omp_for;
  c_లోపల_omp_for = అబద్ధం;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_వ్యక్తీకరణ (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  ఎంపిక (c_parser_peek_token (parser)->type)
    {
    స్థితి CPP_EQ:
      సంకేతం_2 = NOP_సమాసం;
      ఆపు;
    స్థితి CPP_MULT_EQ:
      సంకేతం_2 = MULT_సమాసం;
      ఆపు;
    స్థితి CPP_DIV_EQ:
      సంకేతం_2 = TRUNC_DIV_సమాసం;
      ఆపు;
    స్థితి CPP_MOD_EQ:
      సంకేతం_2 = TRUNC_MOD_సమాసం;
      ఆపు;
    స్థితి CPP_PLUS_EQ:
      సంకేతం_2 = PLUS_సమాసం;
      ఆపు;
    స్థితి CPP_MINUS_EQ:
      సంకేతం_2 = MINUS_సమాసం;
      ఆపు;
    స్థితి CPP_LSHIFT_EQ:
      సంకేతం_2 = LSHIFT_సమాసం;
      ఆపు;
    స్థితి CPP_RSHIFT_EQ:
      సంకేతం_2 = RSHIFT_సమాసం;
      ఆపు;
    స్థితి CPP_AND_EQ:
      సంకేతం_2 = బిట్టు_AND_సమాసం;
      ఆపు;
    స్థితి CPP_XOR_EQ:
      సంకేతం_2 = బిట్టు_XOR_సమాసం;
      ఆపు;
    స్థితి CPP_OR_EQ:
      సంకేతం_2 = బిట్టు_IOR_సమాసం;
      ఆపు;
    అప్రమేయ:
      c_లోపల_omp_for = save_లోపల_omp_for;
      తిరిగి lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_సమాసం_no_commas (parser, ఖాళీ);
  rhs = convert_lvalue_గమ్యం_rvalue (exp_location, rhs, నిజం, నిజం);

  ret.విలువ = build_modify_సమాసం (op_location, lhs.విలువ, lhs.original_type,
				 సంకేతం_2, exp_location, rhs.విలువ,
				 rhs.original_type);
  ret.m_decimal = 0;
  సమితి_c_సమాసం_ఆధారం_range (&ret, lhs.get_ప్రారంభం (), rhs.get_ముగింపు ());
  ఒకవేళ (సంకేతం_2 == NOP_సమాసం)
    ret.original_సంకేతం = MODIFY_సమాసం;
  లేకపోతే
    {
      suppress_warning (ret.విలువ, OPT_Wparentheses);
      ret.original_సంకేతం = ERROR_MARK;
    }
  ret.original_type = ఖాళీ;
  c_లోపల_omp_for = save_లోపల_omp_for;
  తిరిగి ret;
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

స్థిర నిర్మాణం c_సమాసం
c_parser_conditional_వ్యక్తీకరణ (c_parser *parser, నిర్మాణం c_సమాసం *after,
				 వృక్షం omp_atomic_lhs)
{
  నిర్మాణం c_సమాసం cond, exp1, exp2, ret;
  location_t ప్రారంభం, cond_loc, colon_loc;
  తార్కిక save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_ద్విమాన_వ్యక్తీకరణ (parser, after, omp_atomic_lhs);

  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_QUERY))
    తిరిగి cond;
  c_omp_array_section_p = అబద్ధం;
  ఒకవేళ (cond.విలువ != error_mark_కణుపు)
    ప్రారంభం = cond.get_ప్రారంభం ();
  లేకపోతే
    ప్రారంభం = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_గమ్యం_rvalue (cond_loc, cond, నిజం, నిజం);
  c_parser_consume_token (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON))
    {
      వృక్షం eptype = NULL_వృక్షం;

      location_t మధ్య_loc = c_parser_peek_token (parser)->location;
      pedwarn (మధ్య_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      ఒకవేళ (వృక్షం_సంకేతం (cond.విలువ) == EXCESS_PRECISION_సమాసం)
	{
	  eptype = వృక్షం_TYPE (cond.విలువ);
	  cond.విలువ = వృక్షం_నిర్వాహ్యం (cond.విలువ, 0);
	}
      వృక్షం e = cond.విలువ;
      అయితే (వృక్షం_సంకేతం (e) == COMPOUND_సమాసం)
	e = వృక్షం_నిర్వాహ్యం (e, 1);
      warn_for_omitted_condop (మధ్య_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.విలువ = save_సమాసం (default_conversion (cond.విలువ));
      ఒకవేళ (eptype)
	exp1.విలువ = build1 (EXCESS_PRECISION_సమాసం, eptype, exp1.విలువ);
      exp1.original_type = ఖాళీ;
      exp1.src_range = cond.src_range;
      cond.విలువ = c_objc_common_truthvalue_conversion (cond_loc, exp1.విలువ);
      c_inhibit_evaluation_warnings += cond.విలువ == truthvalue_true_కణుపు;
    }
  లేకపోతే
    {
      cond.విలువ
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.విలువ));
      c_inhibit_evaluation_warnings += cond.విలువ == truthvalue_false_కణుపు;
      exp1 = c_parser_వ్యక్తీకరణ_conv (parser);
      mark_exp_read (exp1.విలువ);
      c_inhibit_evaluation_warnings +=
	((cond.విలువ == truthvalue_true_కణుపు)
	 - (cond.విలువ == truthvalue_false_కణుపు));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.విలువ == truthvalue_true_కణుపు;
      ret.సమితి_error ();
      ret.original_సంకేతం = ERROR_MARK;
      ret.original_type = ఖాళీ;
      c_omp_array_section_p = save_c_omp_array_section_p;
      తిరిగి ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_వ్యక్తీకరణ (parser, ఖాళీ, NULL_వృక్షం);
    exp2 = convert_lvalue_గమ్యం_rvalue (exp2_loc, exp2, నిజం, నిజం);
  }
  c_inhibit_evaluation_warnings -= cond.విలువ == truthvalue_true_కణుపు;
  location_t loc1 = make_location (exp1.get_ప్రారంభం (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_ప్రారంభం (), exp2.src_range);
  ఒకవేళ (UNLIKELY (omp_atomic_lhs != ఖాళీ)
      && (వృక్షం_సంకేతం (cond.విలువ) == GT_సమాసం
	  || వృక్షం_సంకేతం (cond.విలువ) == LT_సమాసం
	  || వృక్షం_సంకేతం (cond.విలువ) == EQ_సమాసం)
      && c_వృక్షం_equal (exp2.విలువ, omp_atomic_lhs)
      && (c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (cond.విలువ, 0), omp_atomic_lhs)
	  || c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (cond.విలువ, 1), omp_atomic_lhs)))
    ret.విలువ = build3_loc (colon_loc, COND_సమాసం, వృక్షం_TYPE (omp_atomic_lhs),
			    cond.విలువ, exp1.విలువ, exp2.విలువ);
  లేకపోతే
    ret.విలువ
      = build_conditional_సమాసం (colon_loc, cond.విలువ,
				cond.original_సంకేతం == C_MAYBE_CONST_సమాసం,
				exp1.విలువ, exp1.original_type, loc1,
				exp2.విలువ, exp2.original_type, loc2);
  ret.original_సంకేతం = ERROR_MARK;
  ఒకవేళ (exp1.విలువ == error_mark_కణుపు || exp2.విలువ == error_mark_కణుపు)
    ret.original_type = ఖాళీ;
  లేకపోతే
    {
      వృక్షం t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : వృక్షం_TYPE (exp1.విలువ);
      t2 = exp2.original_type ? exp2.original_type : వృక్షం_TYPE (exp2.విలువ);
      ret.original_type = ((t1 != error_mark_కణుపు
			    && t2 != error_mark_కణుపు
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : ఖాళీ);
    }
  సమితి_c_సమాసం_ఆధారం_range (&ret, ప్రారంభం, exp2.get_ముగింపు ());
  ret.m_decimal = 0;
  c_omp_array_section_p = save_c_omp_array_section_p;
  తిరిగి ret;
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

స్థిర నిర్మాణం c_సమాసం
c_parser_ద్విమాన_వ్యక్తీకరణ (c_parser *parser, నిర్మాణం c_సమాసం *after,
			    వృక్షం omp_atomic_lhs)
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

  నిర్మాణం {
    /* The expression at this stack level.  */
    నిర్మాణం c_సమాసం సమాసం;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    గణన c_parser_prec prec;
    /* The operation on its left.  */
    గణన వృక్షం_సంకేతం_2 op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    వృక్షం sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    వృక్షం orig_సమాసం;
  } దొంతర[అంకె_PRECS];
  పూర్ణాంకం sp;
  /* Location of the binary operator.  */
  location_t ద్విమాన_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#నిర్వచించు తీయి_2								      \
  చేయి {									      \
    ఎంపిక (దొంతర[sp].op)						      \
      {									      \
      స్థితి TRUTH_ANDIF_సమాసం:						      \
	c_inhibit_evaluation_warnings -= (దొంతర[sp - 1].సమాసం.విలువ	      \
					  == truthvalue_false_కణుపు);	      \
	ఆపు;								      \
      స్థితి TRUTH_ORIF_సమాసం:						      \
	c_inhibit_evaluation_warnings -= (దొంతర[sp - 1].సమాసం.విలువ	      \
					  == truthvalue_true_కణుపు);	      \
	ఆపు;								      \
      స్థితి TRUNC_DIV_సమాసం:						      \
	ఒకవేళ ((దొంతర[sp - 1].సమాసం.original_సంకేతం == SIZEOF_సమాసం		      \
	     || దొంతర[sp - 1].సమాసం.original_సంకేతం == PAREN_SIZEOF_సమాసం)	      \
	    && (దొంతర[sp].సమాసం.original_సంకేతం == SIZEOF_సమాసం		      \
		|| దొంతర[sp].సమాసం.original_సంకేతం == PAREN_SIZEOF_సమాసం))	      \
	  {								      \
	    వృక్షం type0 = దొంతర[sp - 1].sizeof_arg;			      \
	    వృక్షం type1 = దొంతర[sp].sizeof_arg;				      \
	    వృక్షం మొదటి_arg = type0;					      \
	    ఒకవేళ (!TYPE_P (type0))					      \
	      type0 = వృక్షం_TYPE (type0);				      \
	    ఒకవేళ (!TYPE_P (type1))					      \
	      type1 = వృక్షం_TYPE (type1);				      \
	    ఒకవేళ (సూచిక_TYPE_P (type0)					      \
		&& comptypes (వృక్షం_TYPE (type0), type1)			      \
		&& !(వృక్షం_సంకేతం (మొదటి_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (మొదటి_arg)			      \
		     && warn_sizeof_array_వాదం))			      \
	      {								      \
		auto_diagnostic_సమూహం d;				      \
		ఒకవేళ (warning_at (దొంతర[sp].loc, OPT_Wsizeof_సూచిక_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  ఒకవేళ (DECL_P (మొదటి_arg))				      \
		    inform (DECL_ఆధారం_LOCATION (మొదటి_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (వృక్షం_TYPE (type0)))  \
		     && దొంతర[sp].సమాసం.original_సంకేతం != PAREN_SIZEOF_సమాసం)    \
	      maybe_warn_sizeof_array_div (దొంతర[sp].loc, మొదటి_arg, type0,   \
					   దొంతర[sp].sizeof_arg, type1);      \
	  }								      \
	ఆపు;								      \
      అప్రమేయ:								      \
	ఆపు;								      \
      }									      \
    దొంతర[sp - 1].సమాసం							      \
      = convert_lvalue_గమ్యం_rvalue (దొంతర[sp - 1].loc,			      \
				  దొంతర[sp - 1].సమాసం, నిజం, నిజం);	      \
    దొంతర[sp].సమాసం							      \
      = convert_lvalue_గమ్యం_rvalue (దొంతర[sp].loc,			      \
				  దొంతర[sp].సమాసం, నిజం, నిజం);		      \
    ఒకవేళ (UNLIKELY (omp_atomic_lhs != NULL_వృక్షం) && sp == 1		      \
	&& ((c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << దొంతర[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_జరుపు)		      \
		     | (1 << PREC_కూడు) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_తదుపరి_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_కణుపు			      \
		     && c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (దొంతర[sp].prec == PREC_REL || దొంతర[sp].prec == PREC_EQ)))\
	&& దొంతర[sp].op != TRUNC_MOD_సమాసం				      \
	&& దొంతర[sp].op != GE_సమాసం					      \
	&& దొంతర[sp].op != LE_సమాసం					      \
	&& దొంతర[sp].op != NE_సమాసం					      \
	&& దొంతర[0].సమాసం.విలువ != error_mark_కణుపు			      \
	&& దొంతర[1].సమాసం.విలువ != error_mark_కణుపు			      \
	&& (omp_atomic_lhs == void_list_కణుపు				      \
	    || c_వృక్షం_equal (దొంతర[0].సమాసం.విలువ, omp_atomic_lhs)	      \
	    || c_వృక్షం_equal (దొంతర[1].సమాసం.విలువ, omp_atomic_lhs)	      \
	    || (దొంతర[sp].op == EQ_సమాసం					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	వృక్షం t = make_కణుపు (దొంతర[1].op);				      \
	వృక్షం_TYPE (t) = వృక్షం_TYPE (దొంతర[0].సమాసం.విలువ);		      \
	వృక్షం_నిర్వాహ్యం (t, 0) = దొంతర[0].సమాసం.విలువ;			      \
	వృక్షం_నిర్వాహ్యం (t, 1) = దొంతర[1].సమాసం.విలువ;			      \
	దొంతర[0].సమాసం.విలువ = t;					      \
	దొంతర[0].సమాసం.m_decimal = 0;					      \
      }									      \
    లేకపోతే								      \
      దొంతర[sp - 1].సమాసం = parser_build_ద్విమాన_op (దొంతర[sp].loc,	      \
						   దొంతర[sp].op,	      \
						   దొంతర[sp - 1].సమాసం,	      \
						   దొంతర[sp].సమాసం,	      \
						   దొంతర[sp - 1].orig_సమాసం);  \
    దొంతర[sp - 1].orig_సమాసం = NULL_వృక్షం;				      \
    sp--;								      \
  } అయితే (0)
  gcc_assert (!after || c_dialect_objc ());
  దొంతర[0].loc = c_parser_peek_token (parser)->location;
  దొంతర[0].సమాసం = c_parser_cast_వ్యక్తీకరణ (parser, after);
  దొంతర[0].prec = PREC_NONE;
  దొంతర[0].sizeof_arg = c_చివరి_sizeof_arg;
  దొంతర[0].orig_సమాసం = NULL_వృక్షం;
  sp = 0;
  అయితే (నిజం)
    {
      గణన c_parser_prec oprec;
      గణన వృక్షం_సంకేతం_2 ocode;
      ఆధారం_range src_range;
      ఒకవేళ (parser->error)
	వెళ్ళు బహిర్గతం;
      ఎంపిక (c_parser_peek_token (parser)->type)
	{
	స్థితి CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_సమాసం;
	  ఆపు;
	స్థితి CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_సమాసం;
	  ఆపు;
	స్థితి CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_సమాసం;
	  ఆపు;
	స్థితి CPP_PLUS:
	  oprec = PREC_కూడు;
	  ocode = PLUS_సమాసం;
	  ఆపు;
	స్థితి CPP_MINUS:
	  oprec = PREC_కూడు;
	  ocode = MINUS_సమాసం;
	  ఆపు;
	స్థితి CPP_LSHIFT:
	  oprec = PREC_జరుపు;
	  ocode = LSHIFT_సమాసం;
	  ఆపు;
	స్థితి CPP_RSHIFT:
	  oprec = PREC_జరుపు;
	  ocode = RSHIFT_సమాసం;
	  ఆపు;
	స్థితి CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_సమాసం;
	  ఆపు;
	స్థితి CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_సమాసం;
	  ఆపు;
	స్థితి CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_సమాసం;
	  ఆపు;
	స్థితి CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_సమాసం;
	  ఆపు;
	స్థితి CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_సమాసం;
	  ఆపు;
	స్థితి CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_సమాసం;
	  ఆపు;
	స్థితి CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = బిట్టు_AND_సమాసం;
	  ఆపు;
	స్థితి CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = బిట్టు_XOR_సమాసం;
	  ఆపు;
	స్థితి CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = బిట్టు_IOR_సమాసం;
	  ఆపు;
	స్థితి CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_సమాసం;
	  ఆపు;
	స్థితి CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_సమాసం;
	  ఆపు;
	అప్రమేయ:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  వెళ్ళు బహిర్గతం;
	}
      ద్విమాన_loc = c_parser_peek_token (parser)->location;
      అయితే (oprec <= దొంతర[sp].prec)
	తీయి_2;
      c_parser_consume_token (parser);
      ఎంపిక (ocode)
	{
	స్థితి TRUTH_ANDIF_సమాసం:
	  src_range = దొంతర[sp].సమాసం.src_range;
	  దొంతర[sp].సమాసం
	    = convert_lvalue_గమ్యం_rvalue (దొంతర[sp].loc,
					దొంతర[sp].సమాసం, నిజం, నిజం);
	  దొంతర[sp].orig_సమాసం = దొంతర[sp].సమాసం.విలువ;
	  దొంతర[sp].సమాసం.విలువ = c_objc_common_truthvalue_conversion
	    (దొంతర[sp].loc, default_conversion (దొంతర[sp].సమాసం.విలువ));
	  c_inhibit_evaluation_warnings += (దొంతర[sp].సమాసం.విలువ
					    == truthvalue_false_కణుపు);
	  సమితి_c_సమాసం_ఆధారం_range (&దొంతర[sp].సమాసం, src_range);
	  ఆపు;
	స్థితి TRUTH_ORIF_సమాసం:
	  src_range = దొంతర[sp].సమాసం.src_range;
	  దొంతర[sp].సమాసం
	    = convert_lvalue_గమ్యం_rvalue (దొంతర[sp].loc,
					దొంతర[sp].సమాసం, నిజం, నిజం);
	  దొంతర[sp].orig_సమాసం = దొంతర[sp].సమాసం.విలువ;
	  దొంతర[sp].సమాసం.విలువ = c_objc_common_truthvalue_conversion
	    (దొంతర[sp].loc, default_conversion (దొంతర[sp].సమాసం.విలువ));
	  c_inhibit_evaluation_warnings += (దొంతర[sp].సమాసం.విలువ
					    == truthvalue_true_కణుపు);
	  సమితి_c_సమాసం_ఆధారం_range (&దొంతర[sp].సమాసం, src_range);
	  ఆపు;
	అప్రమేయ:
	  ఆపు;
	}
      sp++;
      దొంతర[sp].loc = ద్విమాన_loc;
      దొంతర[sp].సమాసం = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
      దొంతర[sp].prec = oprec;
      దొంతర[sp].op = ocode;
      దొంతర[sp].sizeof_arg = c_చివరి_sizeof_arg;
      దొంతర[sp].orig_సమాసం = NULL_వృక్షం;
    }
 బహిర్గతం:
  అయితే (sp > 0)
    తీయి_2;
  తిరిగి దొంతర[0].సమాసం;
#నిర్వచనం_రద్దు తీయి_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

స్థిర నిర్మాణం c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  తార్కిక చూసిన_scspec = అబద్ధం;
  నిర్మాణం c_declspecs *specs = build_null_declspecs ();
  అయితే (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD))
    {
      ఎంపిక (c_parser_peek_token (parser)->keyword)
	{
	స్థితి RID_CONSTEXPR:
	స్థితి RID_రిజిస్టరు:
	స్థితి RID_STATIC:
	స్థితి RID_THREAD:
	  చూసిన_scspec = నిజం;
	  declspecs_కూడు_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->విలువ);
	  c_parser_consume_token (parser);
	  ఆపు;
	అప్రమేయ:
	  వెళ్ళు బహిర్గతం;
	}
    }
 బహిర్గతం:
  తిరిగి చూసిన_scspec ? specs : ఖాళీ;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

స్థిర నిర్మాణం c_సమాసం
c_parser_cast_వ్యక్తీకరణ (c_parser *parser, నిర్మాణం c_సమాసం *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  ఒకవేళ (after)
    తిరిగి c_parser_postfix_వ్యక్తీకరణ_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      నిర్మాణం c_declspecs *scspecs;
      నిర్మాణం c_type_name *type_name;
      నిర్మాణం c_సమాసం ret;
      నిర్మాణం c_సమాసం సమాసం;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, నిజం);
      parens.skip_until_దొరికింది_close (parser);
      ఒకవేళ (type_name == ఖాళీ)
	{
	  ret.సమితి_error ();
	  ret.original_సంకేతం = ERROR_MARK;
	  ret.original_type = ఖాళీ;
	  తిరిగి ret;
	}

      /* Save casted types in the function's used types hash table.  */
      వాడిన_types_చొప్పించు (type_name->specs->type);

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
	తిరిగి c_parser_postfix_వ్యక్తీకరణ_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      ఒకవేళ (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      ఒకవేళ (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t సమాసం_loc = c_parser_peek_token (parser)->location;
	సమాసం = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
	సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, నిజం, నిజం);
      }
      ret.విలువ = c_cast_సమాసం (cast_loc, type_name, సమాసం.విలువ);
      ఒకవేళ (ret.విలువ && సమాసం.విలువ)
	సమితి_c_సమాసం_ఆధారం_range (&ret, cast_loc, సమాసం.get_ముగింపు ());
      ret.original_సంకేతం = ERROR_MARK;
      ret.original_type = ఖాళీ;
      ret.m_decimal = 0;
      తిరిగి ret;
    }
  లేకపోతే
    తిరిగి c_parser_unary_వ్యక్తీకరణ (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

స్థిర శూన్య
mark_exp_read_cond (వృక్షం ఘాతాంకం)
{
  ఒకవేళ ((VAR_P (ఘాతాంకం) || వృక్షం_సంకేతం (ఘాతాంకం) == PARM_DECL)
      && (VAR_P (ఘాతాంకం) ? warn_వాడని_but_సమితి_variable
		      : warn_వాడని_but_సమితి_parameter) > 1)
    తిరిగి;

  mark_exp_read (ఘాతాంకం);
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

స్థిర నిర్మాణం c_సమాసం
c_parser_unary_వ్యక్తీకరణ (c_parser *parser)
{
  పూర్ణాంకం ext;
  నిర్మాణం c_సమాసం ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t exp_loc;
  location_t ముగింపు;
  ret.original_సంకేతం = ERROR_MARK;
  ret.original_type = ఖాళీ;
  ఎంపిక (c_parser_peek_token (parser)->type)
    {
    స్థితి CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
      mark_exp_read_cond (op.విలువ);
      op = default_function_array_conversion (exp_loc, op);
      తిరిగి parser_build_unary_op (op_loc, PREINCREMENT_సమాసం, op);
    స్థితి CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
      mark_exp_read_cond (op.విలువ);
      op = default_function_array_conversion (exp_loc, op);
      తిరిగి parser_build_unary_op (op_loc, PREDECREMENT_సమాసం, op);
    స్థితి CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
      mark_exp_read (op.విలువ);
      తిరిగి parser_build_unary_op (op_loc, ADDR_సమాసం, op);
    స్థితి CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
	ముగింపు = op.get_ముగింపు ();
	op = convert_lvalue_గమ్యం_rvalue (exp_loc, op, నిజం, నిజం);
	location_t combined_loc = make_location (op_loc, op_loc, ముగింపు);
	ret.విలువ = build_పరోక్ష_ref (combined_loc, op.విలువ, RO_UNARY_నక్షత్రం);
	ret.src_range.m_ప్రారంభం = op_loc;
	ret.src_range.m_ముగింపు = ముగింపు;
	ret.m_decimal = 0;
	తిరిగి ret;
      }
    స్థితి CPP_PLUS:
      ఒకవేళ (!c_dialect_objc () && !లోపల_system_శీర్షిక_at (ఆదానం_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
      op = convert_lvalue_గమ్యం_rvalue (exp_loc, op, నిజం, నిజం);
      తిరిగి parser_build_unary_op (op_loc, CONVERT_సమాసం, op);
    స్థితి CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
      op = convert_lvalue_గమ్యం_rvalue (exp_loc, op, నిజం, నిజం);
      తిరిగి parser_build_unary_op (op_loc, NEGATE_సమాసం, op);
    స్థితి CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
      op = convert_lvalue_గమ్యం_rvalue (exp_loc, op, నిజం, నిజం);
      తిరిగి parser_build_unary_op (op_loc, బిట్టు_NOT_సమాసం, op);
    స్థితి CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
      op = convert_lvalue_గమ్యం_rvalue (exp_loc, op, నిజం, నిజం);
      తిరిగి parser_build_unary_op (op_loc, TRUTH_NOT_సమాసం, op);
    స్థితి CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	{
	  ret.విలువ = ముగింపు_label_చిరునామా_సమాసం
	    (c_parser_peek_token (parser)->విలువ, op_loc);
	  సమితి_c_సమాసం_ఆధారం_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_ముగింపు ());
	  c_parser_consume_token (parser);
	}
      లేకపోతే
	{
	  c_parser_error (parser, "expected identifier");
	  ret.సమితి_error ();
	}
      తిరిగి ret;
    స్థితి CPP_KEYWORD:
      {
	గణన rid rid = c_parser_peek_token (parser)->keyword;
	ఎంపిక (rid)
	  {
	  స్థితి RID_COUNTOF:
	  స్థితి RID_SIZEOF:
	    తిరిగి c_parser_sizeof_or_countof_వ్యక్తీకరణ (parser, rid);
	  స్థితి RID_ALIGNOF:
	    తిరిగి c_parser_alignof_వ్యక్తీకరణ (parser);
	  స్థితి RID_MAXOF:
	  స్థితి RID_MINOF:
	    తిరిగి c_parser_maxof_or_minof_వ్యక్తీకరణ (parser, rid);
	  స్థితి RID_BUILTIN_HAS_ATTRIBUTE:
	    తిరిగి c_parser_has_attribute_వ్యక్తీకరణ (parser);
	  స్థితి RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
	    restore_extension_diagnostics (ext);
	    తిరిగి ret;
	  స్థితి RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
	    op = default_function_array_conversion (exp_loc, op);
	    తిరిగి parser_build_unary_op (op_loc, REALPART_సమాసం, op);
	  స్థితి RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
	    op = default_function_array_conversion (exp_loc, op);
	    తిరిగి parser_build_unary_op (op_loc, IMAGPART_సమాసం, op);
	  స్థితి RID_TRANSACTION_ATOMIC:
	  స్థితి RID_TRANSACTION_RELAXED:
	    తిరిగి c_parser_transaction_వ్యక్తీకరణ (parser, rid);
	  స్థితి RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.విలువ = void_కణుపు;
	    సమితి_c_సమాసం_ఆధారం_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    తిరిగి ret;
	  అప్రమేయ:
	    తిరిగి c_parser_postfix_వ్యక్తీకరణ (parser);
	  }
      }
    అప్రమేయ:
      తిరిగి c_parser_postfix_వ్యక్తీకరణ (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

స్థిర నిర్మాణం c_సమాసం
c_parser_sizeof_or_countof_వ్యక్తీకరణ (c_parser *parser, గణన rid rid)
{
  స్థిరరాశి అక్షరం *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  నిర్మాణం c_సమాసం సమాసం;
  నిర్మాణం c_సమాసం ఫలితం;
  location_t సమాసం_loc;
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, rid));

  location_t ప్రారంభం;
  location_t ముగింపు = UNKNOWN_LOCATION;

  ప్రారంభం = c_parser_peek_token (parser)->location;

  ఒకవేళ (rid == RID_COUNTOF)
    pedwarn_c23 (ప్రారంభం, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  ఒకవేళ (rid == RID_COUNTOF)
    లోపల_countof++;
  లేకపోతే
    లోపల_sizeof++;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      నిర్మాణం c_declspecs *scspecs;
      నిర్మాణం c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      సమాసం_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, నిజం);
      parens.skip_until_దొరికింది_close (parser);
      ముగింపు = parser->టోకెన్లు_buf[0].location;
      ఒకవేళ (type_name == ఖాళీ)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  సమాసం.సమితి_error ();
	  వెళ్ళు Xof_సమాసం;
	}
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
	{
	  సమాసం = c_parser_postfix_వ్యక్తీకరణ_after_paren_type (parser, scspecs,
							       type_name,
							       సమాసం_loc);
	  ముగింపు = సమాసం.get_ముగింపు ();
	  వెళ్ళు Xof_సమాసం;
	}
      /* sizeof ( type-name ).  */
      ఒకవేళ (scspecs)
	error_at (సమాసం_loc, "storage class specifier in %qs", op_name);
      ఒకవేళ (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      ఒకవేళ (rid == RID_COUNTOF)
	{
	  లోపల_countof--;
	  ఫలితం = c_సమాసం_countof_type (సమాసం_loc, type_name);
	}
      లేకపోతే
	{
	  లోపల_sizeof--;
	  ఫలితం = c_సమాసం_sizeof_type (సమాసం_loc, type_name);
	}
    }
  లేకపోతే
    {
      సమాసం_loc = c_parser_peek_token (parser)->location;
      సమాసం = c_parser_unary_వ్యక్తీకరణ (parser);
      ముగింపు = సమాసం.get_ముగింపు ();
    Xof_సమాసం:
      c_inhibit_evaluation_warnings--;
      ఒకవేళ (rid == RID_COUNTOF)
	లోపల_countof--;
      లేకపోతే
	లోపల_sizeof--;
      mark_exp_read (సమాసం.విలువ);
      ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) == COMPONENT_REF
	  && DECL_C_బిట్టు_క్షేత్రం (వృక్షం_నిర్వాహ్యం (సమాసం.విలువ, 1)))
	error_at (సమాసం_loc, "%qs applied to a bit-field", op_name);
      ఒకవేళ (rid == RID_COUNTOF)
	ఫలితం = c_సమాసం_countof_సమాసం (సమాసం_loc, సమాసం);
      లేకపోతే
	ఫలితం = c_సమాసం_sizeof_సమాసం (సమాసం_loc, సమాసం);
    }
  ఒకవేళ (ముగింపు == UNKNOWN_LOCATION)
    ముగింపు = ప్రారంభం;
  సమితి_c_సమాసం_ఆధారం_range (&ఫలితం, ప్రారంభం, ముగింపు);
  తిరిగి ఫలితం;
}

/* Parse an alignof expression.  */

స్థిర నిర్మాణం c_సమాసం
c_parser_alignof_వ్యక్తీకరణ (c_parser *parser)
{
  నిర్మాణం c_సమాసం సమాసం;
  location_t ప్రారంభం_loc = c_parser_peek_token (parser)->location;
  location_t చివర_loc;
  వృక్షం alignof_spelling = c_parser_peek_token (parser)->విలువ;
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_ALIGNOF));
  తార్కిక is_c11_alignof = (strcmp (IDENTIFIER_సూచిక (alignof_spelling),
				"_Alignof") == 0
			 || strcmp (IDENTIFIER_సూచిక (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  ఒకవేళ (is_c11_alignof)
    {
      ఒకవేళ (flag_isoc99)
	pedwarn_c99 (ప్రారంభం_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      లేకపోతే
	pedwarn_c99 (ప్రారంభం_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  లోపల_alignof++;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      నిర్మాణం c_declspecs *scspecs;
      నిర్మాణం c_type_name *type_name;
      నిర్మాణం c_సమాసం ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, నిజం);
      చివర_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_దొరికింది_close (parser);
      ఒకవేళ (type_name == ఖాళీ)
	{
	  నిర్మాణం c_సమాసం ret;
	  c_inhibit_evaluation_warnings--;
	  లోపల_alignof--;
	  ret.సమితి_error ();
	  ret.original_సంకేతం = ERROR_MARK;
	  ret.original_type = ఖాళీ;
	  తిరిగి ret;
	}
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
	{
	  సమాసం = c_parser_postfix_వ్యక్తీకరణ_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  వెళ్ళు alignof_సమాసం;
	}
      /* alignof ( type-name ).  */
      ఒకవేళ (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      ఒకవేళ (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      లోపల_alignof--;
      ret.విలువ = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       ఖాళీ, ఖాళీ),
					    అబద్ధం, is_c11_alignof, 1);
      ret.original_సంకేతం = ERROR_MARK;
      ret.original_type = ఖాళీ;
      సమితి_c_సమాసం_ఆధారం_range (&ret, ప్రారంభం_loc, చివర_loc);
      ret.m_decimal = 0;
      తిరిగి ret;
    }
  లేకపోతే
    {
      నిర్మాణం c_సమాసం ret;
      సమాసం = c_parser_unary_వ్యక్తీకరణ (parser);
      చివర_loc = సమాసం.src_range.m_ముగింపు;
    alignof_సమాసం:
      mark_exp_read (సమాసం.విలువ);
      c_inhibit_evaluation_warnings--;
      లోపల_alignof--;
      ఒకవేళ (is_c11_alignof)
	pedwarn (ప్రారంభం_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.విలువ = c_alignof_సమాసం (ప్రారంభం_loc, సమాసం.విలువ);
      ret.original_సంకేతం = ERROR_MARK;
      ret.original_type = ఖాళీ;
      సమితి_c_సమాసం_ఆధారం_range (&ret, ప్రారంభం_loc, చివర_loc);
      ret.m_decimal = 0;
      తిరిగి ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

స్థిర నిర్మాణం c_సమాసం
c_parser_maxof_or_minof_వ్యక్తీకరణ (c_parser *parser, గణన rid rid)
{
  స్థిరరాశి అక్షరం *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  నిర్మాణం c_సమాసం ఫలితం;
  location_t సమాసం_loc;
  నిర్మాణం c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, rid));

  location_t ప్రారంభం;
  location_t ముగింపు = UNKNOWN_LOCATION;

  ప్రారంభం = c_parser_peek_token (parser)->location;

  pedwarn (ప్రారంభం, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      వెళ్ళు fail;
    }
  parens.consume_open (parser);
  సమాసం_loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (సమాసం_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_దొరికింది_close (parser);
      వెళ్ళు fail;
    }
  type_name = c_parser_type_name (parser, నిజం);
  ఒకవేళ (type_name == ఖాళీ)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_దొరికింది_close (parser);
      వెళ్ళు fail;
    }
  parens.skip_until_దొరికింది_close (parser);
  ముగింపు = parser->టోకెన్లు_buf[0].location;
  ఒకవేళ (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  ఒకవేళ (rid == RID_MAXOF)
    ఫలితం = c_సమాసం_maxof_type (సమాసం_loc, type_name);
  లేకపోతే
    ఫలితం = c_సమాసం_minof_type (సమాసం_loc, type_name);
  సమితి_c_సమాసం_ఆధారం_range (&ఫలితం, ప్రారంభం, ముగింపు);
  తిరిగి ఫలితం;
fail:
  c_inhibit_evaluation_warnings--;
  ఫలితం.సమితి_error ();
  ఫలితం.original_సంకేతం = ERROR_MARK;
  ఫలితం.original_type = ఖాళీ;
  తిరిగి ఫలితం;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

స్థిర నిర్మాణం c_సమాసం
c_parser_has_attribute_వ్యక్తీకరణ (c_parser *parser)
{
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t ప్రారంభం = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      లోపల_typeof--;

      నిర్మాణం c_సమాసం ఫలితం;
      ఫలితం.సమితి_error ();
      ఫలితం.original_సంకేతం = ERROR_MARK;
      ఫలితం.original_type = ఖాళీ;
      తిరిగి ఫలితం;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  లోపల_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  వృక్షం oper = NULL_వృక్షం;
  ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_typename (parser, cla_prefer_id))
    {
      నిర్మాణం c_type_name *tname = c_parser_type_name (parser);
      లోపల_typeof--;
      ఒకవేళ (tname)
	{
	  oper = groktypename (tname, ఖాళీ, ఖాళీ);
	  తీయి_maybe_వాడిన (c_type_variably_modified_p (oper));
	}
    }
  లేకపోతే
    {
      నిర్మాణం c_సమాసం cexpr = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      c_inhibit_evaluation_warnings--;
      లోపల_typeof--;
      ఒకవేళ (cexpr.విలువ != error_mark_కణుపు)
	{
	  mark_exp_read (cexpr.విలువ);
	  oper = cexpr.విలువ;
	  వృక్షం etype = వృక్షం_TYPE (oper);
	  తార్కిక was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  ఒకవేళ (was_vm)
	    oper = c_fully_fold (oper, అబద్ధం, ఖాళీ);
	  తీయి_maybe_వాడిన (was_vm);
	}
    }

  నిర్మాణం c_సమాసం ఫలితం;
  ఫలితం.original_సంకేతం = ERROR_MARK;
  ఫలితం.original_type = ఖాళీ;

  ఒకవేళ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      ఫలితం.సమితి_error ();
      తిరిగి ఫలితం;
    }

  తార్కిక save_translate_అక్షరశ్రేణులు_p = parser->translate_అక్షరశ్రేణులు_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  వృక్షం attr = c_parser_gnu_attribute (parser, NULL_వృక్షం, అబద్ధం, అబద్ధం);

  parser->translate_అక్షరశ్రేణులు_p = save_translate_అక్షరశ్రేణులు_p;

  location_t ముగింపు = c_parser_peek_token (parser)->location;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  లేకపోతే
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);

      ఫలితం.సమితి_error ();
      తిరిగి ఫలితం;
    }

  ఒకవేళ (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      ఫలితం.సమితి_error ();
      తిరిగి ఫలితం;
    }

  ఫలితం.original_సంకేతం = INTEGER_CST;
  ఫలితం.original_type = boolean_type_కణుపు;

  ఒకవేళ (has_attribute (atloc, oper, attr, default_conversion))
    ఫలితం.విలువ = boolean_true_కణుపు;
  లేకపోతే
    ఫలితం.విలువ =  boolean_false_కణుపు;

  సమితి_c_సమాసం_ఆధారం_range (&ఫలితం, ప్రారంభం, ముగింపు);
  ఫలితం.m_decimal = 0;
  తిరిగి ఫలితం;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
స్థిర తార్కిక
c_parser_get_builtin_వాదనలు (c_parser *parser, స్థిరరాశి అక్షరం *bname,
			   vec<c_సమాసం_t, va_gc> **ret_cexpr_list,
			   తార్కిక ఎంచుకో_సమాసం_p,
			   location_t *బహిర్గతం_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_సమాసం_t, va_gc> *cexpr_list;
  c_సమాసం_t సమాసం;
  తార్కిక saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = ఖాళీ;
  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      తిరిగి అబద్ధం;
    }

  c_parser_consume_token (parser);

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
    {
      *బహిర్గతం_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      తిరిగి నిజం;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= ఎంచుకో_సమాసం_p;
  సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_సురక్షిత_నెట్టు (cexpr_list, సమాసం);
  అయితే (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  వృక్షం విలువ = embed->విలువ;
	  సమాసం.original_సంకేతం = INTEGER_CST;
	  సమాసం.original_type = integer_type_కణుపు;
	  సమాసం.విలువ = NULL_వృక్షం;
	  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, embed->get_range ());
	  సమాసం.m_decimal = 0;
	  కొరకు (గుర్తులేని పూర్ణాంకం i = 0; i < (గుర్తులేని) RAW_దత్తాంశం_నిడివి (విలువ); i++)
	    {
	      సమాసం.విలువ = build_int_cst (integer_type_కణుపు,
					  RAW_దత్తాంశం_UCHAR_ELT (విలువ, i));
	      vec_సురక్షిత_నెట్టు (cexpr_list, సమాసం);
	    }
	  c_parser_consume_token (parser);
	  కొనసాగు;
	}
      సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      vec_సురక్షిత_నెట్టు (cexpr_list, సమాసం);
    }

  *బహిర్గతం_close_paren_loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    తిరిగి అబద్ధం;

  *ret_cexpr_list = cexpr_list;
  తిరిగి నిజం;
}

/* This represents a single generic-association.  */

నిర్మాణం c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  వృక్షం type;
  /* The association's expression.  */
  నిర్మాణం c_సమాసం వ్యక్తీకరణ;
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

స్థిర నిర్మాణం c_సమాసం
c_parser_generic_selection (c_parser *parser)
{
  నిర్మాణం c_సమాసం selector, error_సమాసం;
  వృక్షం selector_type;
  నిర్మాణం c_generic_association matched_assoc;
  పూర్ణాంకం సరిపోలిక_దొరికింది = -1;
  location_t generic_loc, selector_loc;

  error_సమాసం.original_సంకేతం = ERROR_MARK;
  error_సమాసం.original_type = ఖాళీ;
  error_సమాసం.సమితి_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_వృక్షం;
  matched_assoc.వ్యక్తీకరణ = error_సమాసం;

  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_GENERIC));
  generic_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  ఒకవేళ (flag_isoc99)
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C99 does not support %<_Generic%>");
  లేకపోతే
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C90 does not support %<_Generic%>");

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి error_సమాసం;

  selector_loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_typename (parser, cla_prefer_id))
    {
      c_inhibit_evaluation_warnings++;
      pedwarn_c23 (selector_loc, OPT_Wpedantic,
		   "ISO C does not support use of type name as %<_Generic%> "
		   "controlling operand before C2Y");
      నిర్మాణం c_type_name *type = c_parser_type_name (parser);
      ఒకవేళ (type)
	selector_type = groktypename (type, ఖాళీ, ఖాళీ);
      c_inhibit_evaluation_warnings--;
      ఒకవేళ (!type)
	{
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
	  తిరిగి error_సమాసం;
	}
    }
  లేకపోతే
    {
      c_inhibit_evaluation_warnings++;
      లోపల_generic++;
      selector = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      లోపల_generic--;
      తీయి_maybe_వాడిన (!flag_isoc23);

      ఒకవేళ (selector.విలువ == error_mark_కణుపు)
	{
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
	  తిరిగి selector;
	}
      mark_exp_read (selector.విలువ);
      selector_type = వృక్షం_TYPE (selector.విలువ);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      ఒకవేళ (వృక్షం_సంకేతం (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      ఒకవేళ (FUNCTION_సూచిక_TYPE_P (selector_type)
	  && TYPE_QUALS (వృక్షం_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_సూచిక_type (TYPE_MAIN_VARIANT (వృక్షం_TYPE (selector_type)));
    }

  ఒకవేళ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
      తిరిగి error_సమాసం;
    }

  auto_vec<c_generic_association> associations;
  నిర్మాణం maybe_వాడిన_decl *maybe_వాడిన_default = ఖాళీ;
  అయితే (1)
    {
      నిర్మాణం c_generic_association assoc, *iter;
      గుర్తులేని పూర్ణాంకం ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      ఒకవేళ (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_వృక్షం;
	}
      లేకపోతే
	{
	  నిర్మాణం c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  ఒకవేళ (type_name == ఖాళీ)
	    {
	      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
	      తిరిగి error_సమాసం;
	    }
	  assoc.type = grokgenassoc (type_name);
	  ఒకవేళ (assoc.type == error_mark_కణుపు)
	    {
	      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
	      తిరిగి error_సమాసం;
	    }

	  ఒకవేళ (వృక్షం_సంకేతం (assoc.type) == FUNCTION_TYPE)
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "function type before C2Y");
	  లేకపోతే ఒకవేళ (!COMPLETE_TYPE_P (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "incomplete type before C2Y");

	  ఒకవేళ (c_type_variably_modified_p (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "variably-modified type before C2Y");
	}

      ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
	  తిరిగి error_సమాసం;
	}

      తార్కిక సరిపోలిక = assoc.type == NULL_వృక్షం
		   || comptypes (assoc.type, selector_type);

      ఒకవేళ (!సరిపోలిక || matched_assoc.type != NULL_వృక్షం)
	c_inhibit_evaluation_warnings++;
      లోపల_generic++;

      assoc.వ్యక్తీకరణ = c_parser_సమాసం_no_commas (parser, ఖాళీ);

      ఒకవేళ (!సరిపోలిక || matched_assoc.type != NULL_వృక్షం)
	c_inhibit_evaluation_warnings--;
      లోపల_generic--;
      ఒకవేళ (!సరిపోలిక)
	తీయి_maybe_వాడిన (!flag_isoc23);
      లేకపోతే ఒకవేళ (assoc.type == NULL_వృక్షం)
	maybe_వాడిన_default = save_maybe_వాడిన ();
      లేకపోతే
	తీయి_maybe_వాడిన (నిజం);

      ఒకవేళ (assoc.వ్యక్తీకరణ.విలువ == error_mark_కణుపు)
	{
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
	  తిరిగి error_సమాసం;
	}

      కొరకు (ix = 0; associations.iterate (ix, &iter); ++ix)
	{
	  ఒకవేళ (assoc.type == NULL_వృక్షం)
	    {
	      ఒకవేళ (iter->type == NULL_వృక్షం)
		{
		  error_at (assoc.type_location,
			    "duplicate %<default%> case in %<_Generic%>");
		  inform (iter->type_location, "original %<default%> is here");
		}
	    }
	  లేకపోతే ఒకవేళ (iter->type != NULL_వృక్షం)
	    {
	      ఒకవేళ (comptypes (assoc.type, iter->type))
		{
		  error_at (assoc.type_location,
			    "%<_Generic%> specifies two compatible types");
		  inform (iter->type_location, "compatible type is here");
		}
	    }
	}

      ఒకవేళ (assoc.type == NULL_వృక్షం)
	{
	  ఒకవేళ (సరిపోలిక_దొరికింది < 0)
	    {
	      matched_assoc = assoc;
	      సరిపోలిక_దొరికింది = associations.నిడివి ();
	    }
	}
      లేకపోతే ఒకవేళ (సరిపోలిక)
	{
	  ఒకవేళ (సరిపోలిక_దొరికింది < 0 || matched_assoc.type == NULL_వృక్షం)
	    {
	      matched_assoc = assoc;
	      సరిపోలిక_దొరికింది = associations.నిడివి ();
	    }
	  లేకపోతే
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.సురక్షిత_నెట్టు (assoc);

      ఒకవేళ (c_parser_peek_token (parser)->type != CPP_COMMA)
	ఆపు;
      c_parser_consume_token (parser);
    }

  ఒకవేళ (సరిపోలిక_దొరికింది >= 0 && matched_assoc.type == NULL_వృక్షం)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_వాడిన (maybe_వాడిన_default);
      తీయి_maybe_వాడిన (నిజం);
    }
  లేకపోతే ఒకవేళ (maybe_వాడిన_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_వాడిన (maybe_వాడిన_default);
      తీయి_maybe_వాడిన (!flag_isoc23);
    }

  గుర్తులేని పూర్ణాంకం ix;
  నిర్మాణం c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    ఒకవేళ (ix != (గుర్తులేని) సరిపోలిక_దొరికింది)
      mark_exp_read (iter->వ్యక్తీకరణ.విలువ);

  ఒకవేళ (!parens.require_close (parser))
    {
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
      తిరిగి error_సమాసం;
    }

  ఒకవేళ (సరిపోలిక_దొరికింది < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      తిరిగి error_సమాసం;
    }

  తిరిగి matched_assoc.వ్యక్తీకరణ;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

స్థిర గుర్తులేని పూర్ణాంకం
check_tgmath_function (c_సమాసం *సమాసం, గుర్తులేని పూర్ణాంకం pos)
{
  వృక్షం type = వృక్షం_TYPE (సమాసం->విలువ);
  ఒకవేళ (!FUNCTION_సూచిక_TYPE_P (type))
    {
      error_at (సమాసం->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      తిరిగి 0;
    }
  type = వృక్షం_TYPE (type);
  ఒకవేళ (!prototype_p (type))
    {
      error_at (సమాసం->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      తిరిగి 0;
    }
  ఒకవేళ (stdarg_p (type))
    {
      error_at (సమాసం->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      తిరిగి 0;
    }
  గుర్తులేని పూర్ణాంకం nargs = 0;
  function_వాదనలు_iterator iter;
  వృక్షం t;
  FOREACH_FUNCTION_వాదనలు (type, t, iter)
    {
      ఒకవేళ (t == void_type_కణుపు)
	ఆపు;
      nargs++;
    }
  ఒకవేళ (nargs == 0)
    {
      error_at (సమాసం->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      తిరిగి 0;
    }
  తిరిగి nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
గణన tgmath_parm_రకం
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

స్థిర నిర్మాణం c_సమాసం
c_parser_predefined_identifier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ఎంపిక (c_parser_peek_token (parser)->keyword)
    {
    స్థితి RID_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__FUNCTION__");
      ఆపు;
    స్థితి RID_PRETTY_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__PRETTY_FUNCTION__");
      ఆపు;
    స్థితి RID_C99_FUNCTION_NAME:
      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support "
		   "%<__func__%> predefined identifier");
      ఆపు;
    అప్రమేయ:
      gcc_unreachable ();
    }

  నిర్మాణం c_సమాసం సమాసం;
  సమాసం.original_సంకేతం = ERROR_MARK;
  సమాసం.original_type = ఖాళీ;
  సమాసం.విలువ = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->విలువ);
  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, loc);
  సమాసం.m_decimal = 0;
  c_parser_consume_token (parser);
  తిరిగి సమాసం;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

స్థిర తార్కిక
has_counted_by_object (వృక్షం ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  ఒకవేళ ((వృక్షం_సంకేతం (ref) == పరోక్ష_REF
       && is_access_with_కొలత_p (వృక్షం_నిర్వాహ్యం (ref, 0)))
      || is_access_with_కొలత_p (ref))
    తిరిగి నిజం;
  తిరిగి అబద్ధం;
}

/* Get the reference to the counted-by object associated with the REF.  */

స్థిర వృక్షం
get_counted_by_ref (వృక్షం ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  ఒకవేళ (వృక్షం_సంకేతం (ref) == పరోక్ష_REF
      && is_access_with_కొలత_p (వృక్షం_నిర్వాహ్యం (ref, 0)))
    తిరిగి CALL_సమాసం_ARG (వృక్షం_నిర్వాహ్యం (ref, 0), 1);
  లేకపోతే ఒకవేళ (is_access_with_కొలత_p (ref))
    తిరిగి CALL_సమాసం_ARG (ref, 1);

  తిరిగి NULL_వృక్షం;
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

స్థిర నిర్మాణం c_సమాసం
c_parser_postfix_వ్యక్తీకరణ (c_parser *parser)
{
  నిర్మాణం c_సమాసం సమాసం, e1;
  నిర్మాణం c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  ఆధారం_range tok_range = c_parser_peek_token (parser)->get_range ();
  సమాసం.original_సంకేతం = ERROR_MARK;
  సమాసం.original_type = ఖాళీ;
  సమాసం.m_decimal = 0;
  ఎంపిక (c_parser_peek_token (parser)->type)
    {
    స్థితి CPP_సంఖ్య:
      సమాసం.విలువ = c_parser_peek_token (parser)->విలువ;
      సమితి_c_సమాసం_ఆధారం_range (&సమాసం, tok_range);
      loc = c_parser_peek_token (parser)->location;
      సమాసం.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) == FIXED_CST
	  && !targetm.fixed_బిందువు_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  సమాసం.సమితి_error ();
	}
      ఆపు;
    స్థితి CPP_CHAR:
    స్థితి CPP_CHAR16:
    స్థితి CPP_CHAR32:
    స్థితి CPP_UTF8CHAR:
    స్థితి CPP_WCHAR:
      సమాసం.విలువ = c_parser_peek_token (parser)->విలువ;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      సమాసం.original_type = char_type_కణుపు;
      సమితి_c_సమాసం_ఆధారం_range (&సమాసం, tok_range);
      c_parser_consume_token (parser);
      ఆపు;
    స్థితి CPP_STRING:
    స్థితి CPP_STRING16:
    స్థితి CPP_STRING32:
    స్థితి CPP_WSTRING:
    స్థితి CPP_UTF8STRING:
      సమాసం = c_parser_string_literal (parser, parser->translate_అక్షరశ్రేణులు_p,
				      నిజం);
      ఆపు;
    స్థితి CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      సమాసం.విలువ
	= objc_build_string_object (c_parser_peek_token (parser)->విలువ);
      సమితి_c_సమాసం_ఆధారం_range (&సమాసం, tok_range);
      c_parser_consume_token (parser);
      ఆపు;
    స్థితి CPP_NAME:
      ఎంపిక (c_parser_peek_token (parser)->id_రకం)
	{
	స్థితి C_ID_ID:
	  {
	    వృక్షం id = c_parser_peek_token (parser)->విలువ;
	    c_parser_consume_token (parser);
	    సమాసం.విలువ = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &సమాసం.original_type);
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, tok_range);
	    ఆపు;
	  }
	స్థితి C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    వృక్షం class_name = c_parser_peek_token (parser)->విలువ;
	    వృక్షం component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    ఒకవేళ (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->విలువ;
	    location_t చివర_loc = component_tok->get_ముగింపు ();
	    c_parser_consume_token (parser);
	    సమాసం.విలువ = objc_build_class_component_ref (class_name,
							 component);
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, చివర_loc);
	    ఆపు;
	  }
	అప్రమేయ:
	  c_parser_error (parser, "expected expression");
	  సమాసం.సమితి_error ();
	  ఆపు;
	}
      ఆపు;
    స్థితి CPP_OPEN_PAREN:
      /* A parenthesized expression, statement expression or compound
	 literal.  */
      ఒకవేళ (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_BRACE)
	{
	  /* A statement expression.  */
	  వృక్షం stmt;
	  location_t brace_loc;
	  తార్కిక save_c_omp_array_section_p = c_omp_array_section_p;
	  c_parser_consume_token (parser);
	  brace_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* If we've not yet started the current function's statement list,
	     or we're in the parameter scope of an old-style function
	     declaration, statement expressions are not allowed.  */
	  ఒకవేళ (!building_stmt_list_p () || old_style_parameter_scope ())
	    {
	      error_at (loc, "braced-group within expression allowed "
			"only inside a function");
	      parser->error = నిజం;
	      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_BRACE, ఖాళీ);
	      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
	      సమాసం.సమితి_error ();
	      ఆపు;
	    }
	  c_omp_array_section_p = అబద్ధం;
	  stmt = c_begin_stmt_సమాసం ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  సమాసం.విలువ = c_ముగింపు_stmt_సమాసం (brace_loc, stmt);
	  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_loc);
	  mark_exp_read (సమాసం.విలువ);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      లేకపోతే
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  సమాసం = c_parser_వ్యక్తీకరణ (parser);
	  ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) == MODIFY_సమాసం)
	    suppress_warning (సమాసం.విలువ, OPT_Wparentheses);
	  ఒకవేళ (సమాసం.original_సంకేతం != C_MAYBE_CONST_సమాసం
	      && సమాసం.original_సంకేతం != SIZEOF_సమాసం)
	    సమాసం.original_సంకేతం = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  ఒకవేళ (సమాసం.original_సంకేతం == SIZEOF_సమాసం)
	    సమాసం.original_సంకేతం = PAREN_SIZEOF_సమాసం;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      ఆపు;
    స్థితి CPP_KEYWORD:
      ఎంపిక (c_parser_peek_token (parser)->keyword)
	{
	స్థితి RID_FUNCTION_NAME:
	స్థితి RID_PRETTY_FUNCTION_NAME:
	స్థితి RID_C99_FUNCTION_NAME:
	  సమాసం = c_parser_predefined_identifier (parser);
	  ఆపు;
	స్థితి RID_VA_ARG:
	  {
	    location_t ప్రారంభం_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ఒకవేళ (!parens.require_open (parser))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    e1 = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	    mark_exp_read (e1.విలువ);
	    e1.విలువ = c_fully_fold (e1.విలువ, అబద్ధం, ఖాళీ);
	    ఒకవేళ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t చివర_loc = c_parser_peek_token (parser)->get_ముగింపు ();
	    c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ఒకవేళ (t1 == ఖాళీ)
	      {
		సమాసం.సమితి_error ();
	      }
	    లేకపోతే
	      {
		వృక్షం type_సమాసం = NULL_వృక్షం;
		వృక్షం type = groktypename (t1, &type_సమాసం, ఖాళీ);
		సమాసం.విలువ = c_build_va_arg (ప్రారంభం_loc, e1.విలువ, loc,
					     type, type_సమాసం);
		సమితి_c_సమాసం_ఆధారం_range (&సమాసం, ప్రారంభం_loc, చివర_loc);
	      }
	  }
	  ఆపు;
	స్థితి RID_C23_VA_ప్రారంభం:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ఒకవేళ (!parens.require_open (parser))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    e1 = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	    e1 = convert_lvalue_గమ్యం_rvalue (e1.get_location (), e1, నిజం, నిజం);
	    ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		ఒకవేళ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
		    సమాసం.సమితి_error ();
		    ఆపు;
		  }
		ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_రకం == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    వృక్షం name = c_parser_peek_token (parser)->విలువ;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    వృక్షం decl = lookup_name (name);
		    వృక్షం చివరి_parm
		      = వృక్షం_చివరి (DECL_ARGUMENTS (current_function_decl));
		    ఒకవేళ (!చివరి_parm || decl != చివరి_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    లేకపోతే ఒకవేళ (DECL_రిజిస్టరు (decl))
		      warning_at (nloc, OPT_Wvarargs,
				  "undefined behavior when second parameter "
				  "of %<va_start%> is declared with "
				  "%<register%> storage");
		    c_parser_consume_token (parser);
		  }
		లేకపోతే
		  {
		    గుర్తులేని nesting_లోతు = 0;
		    location_t sloc = c_parser_peek_token (parser)->location;
		    location_t eloc = sloc;

		    /* For va_start (ap,) the ) comes from stdarg.h.
		       Use location of , in that case, otherwise without
		       -Wsystem-headers nothing is reported.  After all,
		       the problematic token is the comma in that case.  */
		    ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    అయితే (నిజం)
		      {
			c_token *token = c_parser_peek_token (parser);
			ఒకవేళ (token->type == CPP_CLOSE_PAREN && !nesting_లోతు)
			  ఆపు;

			ఒకవేళ (token->type == CPP_EOF)
			  ఆపు;
			ఒకవేళ (token->type == CPP_OPEN_PAREN)
			  ++nesting_లోతు;
			లేకపోతే ఒకవేళ (token->type == CPP_CLOSE_PAREN)
			  --nesting_లోతు;
			eloc = token->location;
			c_parser_consume_token (parser);
		      }
		    ఒకవేళ (sloc != eloc)
		      sloc = make_location (sloc, sloc, eloc);
		    warning_at (sloc, OPT_Wvarargs,
				"%<va_start%> macro used with additional "
				"arguments other than identifier of the "
				"last named argument");
		  }
	      }
	    parens.skip_until_దొరికింది_close (parser);
	    వృక్షం fndecl = builtin_decl_explicit (BUILT_లోపల_VA_ప్రారంభం);
	    vec<వృక్షం, va_gc> *params;
	    vec_alloc (params, 2);
	    params->శీఘ్ర_నెట్టు (e1.విలువ);
	    params->శీఘ్ర_నెట్టు (integer_zero_కణుపు);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.శీఘ్ర_నెట్టు (e1.get_location ());
	    arg_loc.శీఘ్ర_నెట్టు (UNKNOWN_LOCATION);
	    సమాసం.విలువ = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, ఖాళీ);
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc,
				     parser->టోకెన్లు_buf[0].get_ముగింపు ());
	    సమాసం.m_decimal = 0;
	    సమాసం.original_సంకేతం = ERROR_MARK;
	    సమాసం.original_type = ఖాళీ;
	    release_వృక్షం_సదిశ (params);
	    ఆపు;
	  }
	స్థితి RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ఒకవేళ (!parens.require_open (parser))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    t1 = c_parser_type_name (parser);
	    ఒకవేళ (t1 == ఖాళీ)
	      parser->error = నిజం;
	    ఒకవేళ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    ఒకవేళ (parser->error)
	      {
		c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    వృక్షం type = groktypename (t1, ఖాళీ, ఖాళీ);
	    వృక్షం offsetof_ref;
	    ఒకవేళ (type == error_mark_కణుపు)
	      offsetof_ref = error_mark_కణుపు;
	    లేకపోతే
	      {
		offsetof_ref = build1 (పరోక్ష_REF, type, null_సూచిక_కణుపు);
		సమితి_సమాసం_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->విలువ,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		అయితే (c_parser_తదుపరి_token_is (parser, CPP_DOT)
		       || c_parser_తదుపరి_token_is (parser,
						  CPP_OPEN_వర్గం)
		       || c_parser_తదుపరి_token_is (parser,
						  CPP_DEREF))
		  {
		    ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_కణుపు);
			వెళ్ళు do_dot;
		      }
		    లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			ఒకవేళ (c_parser_తదుపరి_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    ఆపు;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->విలువ,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    లేకపోతే
		      {
			నిర్మాణం c_సమాసం ce;
			వృక్షం idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_వ్యక్తీకరణ (parser);
			ce = convert_lvalue_గమ్యం_rvalue (loc, ce, అబద్ధం, అబద్ధం);
			idx = ce.విలువ;
			idx = c_fully_fold (idx, అబద్ధం, ఖాళీ);
			c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_వర్గం,
						   "expected %<]%>");
			offsetof_ref = build_array_ref (loc, offsetof_ref, idx);
		      }
		  }
	      }
	    లేకపోతే
	      c_parser_error (parser, "expected identifier");
	    location_t చివర_loc = c_parser_peek_token (parser)->get_ముగింపు ();
	    c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    సమాసం.విలువ = fold_offsetof (offsetof_ref);
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, చివర_loc);
	  }
	  ఆపు;
	స్థితి RID_ఎంచుకో_సమాసం:
	  {
	    vec<c_సమాసం_t, va_gc> *cexpr_list;
	    c_సమాసం_t *e1_p, *e2_p, *e3_p;
	    వృక్షం c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ఒకవేళ (!c_parser_get_builtin_వాదనలు (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, నిజం,
					    &close_paren_loc))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    ఒకవేళ (vec_సురక్షిత_నిడివి (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->విలువ;
	    mark_exp_read (e2_p->విలువ);
	    mark_exp_read (e3_p->విలువ);
	    ఒకవేళ (వృక్షం_సంకేతం (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (వృక్షం_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_వ్యక్తీకరణ_warning (c);
	    సమాసం = integer_zerop (c) ? *e3_p : *e2_p;
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_paren_loc);
	    ఆపు;
	  }
	స్థితి RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ఒకవేళ (!parens.require_open (parser))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    t1 = c_parser_type_name (parser);
	    ఒకవేళ (t1 == ఖాళీ)
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    t2 = c_parser_type_name (parser);
	    ఒకవేళ (t2 == ఖాళీ)
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_దొరికింది_close (parser);
	    వృక్షం e1, e2;
	    e1 = groktypename (t1, ఖాళీ, ఖాళీ);
	    e2 = groktypename (t2, ఖాళీ, ఖాళీ);
	    ఒకవేళ (e1 == error_mark_కణుపు || e2 == error_mark_కణుపు)
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    సమాసం.విలువ
	      = comptypes (e1, e2) ? integer_one_కణుపు : integer_zero_కణుపు;
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_paren_loc);
	  }
	  ఆపు;
	స్థితి RID_BUILTIN_TGMATH:
	  {
	    vec<c_సమాసం_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ఒకవేళ (!c_parser_get_builtin_వాదనలు (parser,
					    "__builtin_tgmath",
					    &cexpr_list, అబద్ధం,
					    &close_paren_loc))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    ఒకవేళ (vec_సురక్షిత_నిడివి (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    గుర్తులేని పూర్ణాంకం i;
	    c_సమాసం_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_గమ్యం_rvalue (loc, *p, నిజం, నిజం);
	    గుర్తులేని పూర్ణాంకం nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    ఒకవేళ (nargs == 0)
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (vec_సురక్షిత_నిడివి (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    గుర్తులేని పూర్ణాంకం అంకె_functions = vec_సురక్షిత_నిడివి (cexpr_list) - nargs;
	    ఒకవేళ (అంకె_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    కొరకు (గుర్తులేని పూర్ణాంకం j = 1; j < అంకె_functions; j++)
	      {
		గుర్తులేని పూర్ణాంకం this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		ఒకవేళ (this_nargs == 0)
		  {
		    సమాసం.సమితి_error ();
		    వెళ్ళు బహిర్గతం;
		  }
		ఒకవేళ (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    సమాసం.సమితి_error ();
		    వెళ్ళు బహిర్గతం;
		  }
	      }

	    /* The functions all have the same number of arguments.
	       Determine whether arguments and return types vary in
	       ways permitted for <tgmath.h> functions.  */
	    /* The first entry in each of these vectors is for the
	       return type, subsequent entries for parameter
	       types.  */
	    auto_vec<గణన tgmath_parm_రకం> parm_రకం (nargs + 1);
	    auto_vec<వృక్షం> parm_మొదటి (nargs + 1);
	    auto_vec<తార్కిక> parm_complex (nargs + 1);
	    auto_vec<తార్కిక> parm_varies (nargs + 1);
	    వృక్షం మొదటి_type = వృక్షం_TYPE (వృక్షం_TYPE ((*cexpr_list)[0].విలువ));
	    వృక్షం మొదటి_ret = TYPE_MAIN_VARIANT (వృక్షం_TYPE (మొదటి_type));
	    parm_మొదటి.శీఘ్ర_నెట్టు (మొదటి_ret);
	    parm_complex.శీఘ్ర_నెట్టు (వృక్షం_సంకేతం (మొదటి_ret) == COMPLEX_TYPE);
	    parm_varies.శీఘ్ర_నెట్టు (అబద్ధం);
	    function_వాదనలు_iterator iter;
	    వృక్షం t;
	    గుర్తులేని పూర్ణాంకం argpos;
	    FOREACH_FUNCTION_వాదనలు (మొదటి_type, t, iter)
	      {
		ఒకవేళ (t == void_type_కణుపు)
		  ఆపు;
		parm_మొదటి.శీఘ్ర_నెట్టు (TYPE_MAIN_VARIANT (t));
		parm_complex.శీఘ్ర_నెట్టు (వృక్షం_సంకేతం (t) == COMPLEX_TYPE);
		parm_varies.శీఘ్ర_నెట్టు (అబద్ధం);
	      }
	    కొరకు (గుర్తులేని పూర్ణాంకం j = 1; j < అంకె_functions; j++)
	      {
		వృక్షం type = వృక్షం_TYPE (వృక్షం_TYPE ((*cexpr_list)[j].విలువ));
		వృక్షం ret = TYPE_MAIN_VARIANT (వృక్షం_TYPE (type));
		ఒకవేళ (ret != parm_మొదటి[0])
		  {
		    parm_varies[0] = నిజం;
		    ఒకవేళ (!SCALAR_FLOAT_TYPE_P (parm_మొదటి[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_మొదటి[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			సమాసం.సమితి_error ();
			వెళ్ళు బహిర్గతం;
		      }
		    ఒకవేళ (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			సమాసం.సమితి_error ();
			వెళ్ళు బహిర్గతం;
		      }
		  }
		ఒకవేళ (వృక్షం_సంకేతం (ret) == COMPLEX_TYPE)
		  parm_complex[0] = నిజం;
		argpos = 1;
		FOREACH_FUNCTION_వాదనలు (type, t, iter)
		  {
		    ఒకవేళ (t == void_type_కణుపు)
		      ఆపు;
		    t = TYPE_MAIN_VARIANT (t);
		    ఒకవేళ (t != parm_మొదటి[argpos])
		      {
			parm_varies[argpos] = నిజం;
			ఒకవేళ (!SCALAR_FLOAT_TYPE_P (parm_మొదటి[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_మొదటి[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    సమాసం.సమితి_error ();
			    వెళ్ళు బహిర్గతం;
			  }
			ఒకవేళ (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    సమాసం.సమితి_error ();
			    వెళ్ళు బహిర్గతం;
			  }
		      }
		    ఒకవేళ (వృక్షం_సంకేతం (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = నిజం;
		    argpos++;
		  }
	      }
	    గణన tgmath_parm_రకం max_variation = tgmath_fixed;
	    కొరకు (గుర్తులేని పూర్ణాంకం j = 0; j <= nargs; j++)
	      {
		గణన tgmath_parm_రకం this_రకం;
		ఒకవేళ (parm_varies[j])
		  {
		    ఒకవేళ (parm_complex[j])
		      max_variation = this_రకం = tgmath_complex;
		    లేకపోతే
		      {
			this_రకం = tgmath_real;
			ఒకవేళ (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		లేకపోతే
		  this_రకం = tgmath_fixed;
		parm_రకం.శీఘ్ర_నెట్టు (this_రకం);
	      }
	    ఒకవేళ (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    గుర్తులేని పూర్ణాంకం tgarg = 0;
	    కొరకు (గుర్తులేని పూర్ణాంకం j = 1; j <= nargs; j++)
	      ఒకవేళ (parm_రకం[j] == max_variation)
		{
		  tgarg = j;
		  ఆపు;
		}
	    ఒకవేళ (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<వృక్షం> tg_type (అంకె_functions);
	    కొరకు (గుర్తులేని పూర్ణాంకం j = 0; j < అంకె_functions; j++)
	      {
		వృక్షం type = వృక్షం_TYPE (వృక్షం_TYPE ((*cexpr_list)[j].విలువ));
		argpos = 1;
		FOREACH_FUNCTION_వాదనలు (type, t, iter)
		  {
		    ఒకవేళ (argpos == tgarg)
		      {
			tg_type.శీఘ్ర_నెట్టు (TYPE_MAIN_VARIANT (t));
			ఆపు;
		      }
		    argpos++;
		  }
	      }

	    /* Verify that the corresponding types are different for
	       all the listed functions.  Also determine whether all
	       the types are complex, whether all the types are
	       standard or binary, and whether all the types are
	       decimal.  */
	    తార్కిక all_complex = నిజం;
	    తార్కిక all_ద్విమాన = నిజం;
	    తార్కిక all_decimal = నిజం;
	    hash_సమితి<వృక్షం> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		ఒకవేళ (వృక్షం_సంకేతం (t) == COMPLEX_TYPE)
		  all_decimal = అబద్ధం;
		లేకపోతే
		  {
		    all_complex = అబద్ధం;
		    ఒకవేళ (DECIMAL_FLOAT_TYPE_P (t))
		      all_ద్విమాన = అబద్ధం;
		    లేకపోతే
		      all_decimal = అబద్ధం;
		  }
		ఒకవేళ (tg_types.కూడు (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    సమాసం.సమితి_error ();
		    వెళ్ళు బహిర్గతం;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    కొరకు (గుర్తులేని పూర్ణాంకం j = 0; j < అంకె_functions; j++)
	      {
		వృక్షం exp_type = tg_type[j];
		వృక్షం exp_real_type = exp_type;
		ఒకవేళ (వృక్షం_సంకేతం (exp_type) == COMPLEX_TYPE)
		  exp_real_type = వృక్షం_TYPE (exp_type);
		వృక్షం type = వృక్షం_TYPE (వృక్షం_TYPE ((*cexpr_list)[j].విలువ));
		వృక్షం ret = TYPE_MAIN_VARIANT (వృక్షం_TYPE (type));
		ఒకవేళ ((parm_రకం[0] == tgmath_complex && ret != exp_type)
		    || (parm_రకం[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    సమాసం.సమితి_error ();
		    వెళ్ళు బహిర్గతం;
		  }
		argpos = 1;
		FOREACH_FUNCTION_వాదనలు (type, t, iter)
		  {
		    ఒకవేళ (t == void_type_కణుపు)
		      ఆపు;
		    t = TYPE_MAIN_VARIANT (t);
		    ఒకవేళ ((parm_రకం[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_రకం[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			సమాసం.సమితి_error ();
			వెళ్ళు బహిర్గతం;
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
	    తార్కిక arg_complex = all_complex;
	    తార్కిక arg_ద్విమాన = all_ద్విమాన;
	    తార్కిక arg_int_decimal = all_decimal;
	    తార్కిక arg_int_floatnx = అబద్ధం;
	    తార్కిక arg_int_decimalx = అబద్ధం;
	    కొరకు (గుర్తులేని పూర్ణాంకం j = 1; j <= nargs; j++)
	      {
		ఒకవేళ (parm_రకం[j] == tgmath_fixed)
		  కొనసాగు;
		c_సమాసం_t *ce = &(*cexpr_list)[అంకె_functions + j - 1];
		వృక్షం type = వృక్షం_TYPE (ce->విలువ);
		ఒకవేళ (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && వృక్షం_సంకేతం (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    సమాసం.సమితి_error ();
		    వెళ్ళు బహిర్గతం;
		  }
		ఒకవేళ (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = నిజం;
		    ఒకవేళ (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			సమాసం.సమితి_error ();
			వెళ్ళు బహిర్గతం;
		      }
		    లేకపోతే ఒకవేళ (all_ద్విమాన)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			సమాసం.సమితి_error ();
			వెళ్ళు బహిర్గతం;
		      }
		    లేకపోతే ఒకవేళ (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			సమాసం.సమితి_error ();
			వెళ్ళు బహిర్గతం;
		      }
		    లేకపోతే ఒకవేళ (arg_ద్విమాన)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			సమాసం.సమితి_error ();
			వెళ్ళు బహిర్గతం;
		      }
		  }
		లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == COMPLEX_TYPE)
		  {
		    arg_complex = నిజం;
		    ఒకవేళ (COMPLEX_FLOAT_TYPE_P (type))
		      arg_ద్విమాన = నిజం;
		    ఒకవేళ (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			సమాసం.సమితి_error ();
			వెళ్ళు బహిర్గతం;
		      }
		    లేకపోతే ఒకవేళ (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			సమాసం.సమితి_error ();
			వెళ్ళు బహిర్గతం;
		      }
		  }
		లేకపోతే ఒకవేళ (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_ద్విమాన = నిజం;
		    ఒకవేళ (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			సమాసం.సమితి_error ();
			వెళ్ళు బహిర్గతం;
		      }
		    లేకపోతే ఒకవేళ (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			సమాసం.సమితి_error ();
			వెళ్ళు బహిర్గతం;
		      }
		  }
		వృక్షం rtype = TYPE_MAIN_VARIANT (type);
		ఒకవేళ (వృక్షం_సంకేతం (rtype) == COMPLEX_TYPE)
		  rtype = వృక్షం_TYPE (rtype);
		ఒకవేళ (SCALAR_FLOAT_TYPE_P (rtype))
		  కొరకు (గుర్తులేని పూర్ణాంకం j = 0; j < అంకె_FLOATNX_TYPES; j++)
		    ఒకవేళ (rtype == FLOATNX_TYPE_కణుపు (j))
		      {
			arg_int_floatnx = నిజం;
			ఆపు;
		      }
		ఒకవేళ (rtype == dfloat64x_type_కణుపు)
		  arg_int_decimalx = నిజం;
	      }
	    వృక్షం arg_real = NULL_వృక్షం;
	    కొరకు (గుర్తులేని పూర్ణాంకం j = 1; j <= nargs; j++)
	      {
		ఒకవేళ (parm_రకం[j] == tgmath_fixed)
		  కొనసాగు;
		c_సమాసం_t *ce = &(*cexpr_list)[అంకె_functions + j - 1];
		వృక్షం type = TYPE_MAIN_VARIANT (వృక్షం_TYPE (ce->విలువ));
		ఒకవేళ (వృక్షం_సంకేతం (type) == COMPLEX_TYPE)
		  type = వృక్షం_TYPE (type);
		ఒకవేళ (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_కణుపు
			  : arg_int_floatnx
			  ? float32x_type_కణుపు
			  : arg_int_decimal
			  ? dfloat64_type_కణుపు
			  : double_type_కణుపు);
		ఒకవేళ (arg_real == NULL_వృక్షం)
		  arg_real = type;
		లేకపోతే
		  arg_real = common_type (arg_real, type);
		ఒకవేళ (arg_real == error_mark_కణుపు)
		  {
		    సమాసం.సమితి_error ();
		    వెళ్ళు బహిర్గతం;
		  }
	      }
	    వృక్షం arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_సమాసం_t *fn = ఖాళీ;
	    కొరకు (గుర్తులేని పూర్ణాంకం j = 0; j < అంకె_functions; j++)
	      {
		ఒకవేళ (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    ఆపు;
		  }
	      }
	    ఒకవేళ (fn == ఖాళీ
		&& parm_రకం[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_మొదటి[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		కొరకు (గుర్తులేని పూర్ణాంకం j = 0; j < అంకె_functions; j++)
		  {
		    ఒకవేళ (arg_complex
			!= (వృక్షం_సంకేతం (tg_type[j]) == COMPLEX_TYPE))
		      కొనసాగు;
		    వృక్షం real_tg_type = (arg_complex
					 ? వృక్షం_TYPE (tg_type[j])
					 : tg_type[j]);
		    ఒకవేళ (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      కొనసాగు;
		    scalar_float_బహుళకం arg_బహుళకం
		      = SCALAR_FLOAT_TYPE_బహుళకం (arg_real);
		    scalar_float_బహుళకం tg_బహుళకం
		      = SCALAR_FLOAT_TYPE_బహుళకం (real_tg_type);
		    స్థిరరాశి real_format *arg_fmt = REAL_బహుళకం_FORMAT (arg_బహుళకం);
		    స్థిరరాశి real_format *tg_fmt = REAL_బహుళకం_FORMAT (tg_బహుళకం);
		    ఒకవేళ (arg_fmt->b == tg_fmt->b
			&& arg_fmt->p <= tg_fmt->p
			&& arg_fmt->emax <= tg_fmt->emax
			&& (arg_fmt->emin - arg_fmt->p
			    >= tg_fmt->emin - tg_fmt->p))
		      {
			fn = &(*cexpr_list)[j];
			ఆపు;
		      }
		  }
	      }
	    ఒకవేళ (fn == ఖాళీ)
	      {
		error_at (loc, "no matching function for type-generic call");
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    /* Construct a call to FN.  */
	    vec<వృక్షం, va_gc> *వాదనలు;
	    vec_alloc (వాదనలు, nargs);
	    vec<వృక్షం, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    కొరకు (గుర్తులేని పూర్ణాంకం j = 0; j < nargs; j++)
	      {
		c_సమాసం_t *ce = &(*cexpr_list)[అంకె_functions + j];
		వాదనలు->శీఘ్ర_నెట్టు (ce->విలువ);
		arg_loc.శీఘ్ర_నెట్టు (ce->get_location ());
		origtypes->శీఘ్ర_నెట్టు (ce->original_type);
	      }
	    సమాసం.విలువ = c_build_function_call_vec (loc, arg_loc, fn->విలువ,
						    వాదనలు, origtypes);
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_paren_loc);
	    ఆపు;
	  }
	స్థితి RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_సమాసం_t, va_gc> *cexpr_list;
	    c_సమాసం_t *e2_p;
	    వృక్షం chain_విలువ;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ఒకవేళ (!c_parser_get_builtin_వాదనలు (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, అబద్ధం,
					    &close_paren_loc))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (vec_సురక్షిత_నిడివి (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    సమాసం = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_గమ్యం_rvalue (loc, *e2_p, నిజం, నిజం);
	    chain_విలువ = e2_p->విలువ;
	    mark_exp_read (chain_విలువ);

	    ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) != CALL_సమాసం)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (chain_విలువ)) != సూచిక_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    లేకపోతే
	      CALL_సమాసం_STATIC_CHAIN (సమాసం.విలువ) = chain_విలువ;
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_paren_loc);
	    ఆపు;
	  }
	స్థితి RID_BUILTIN_COMPLEX:
	  {
	    vec<c_సమాసం_t, va_gc> *cexpr_list;
	    c_సమాసం_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ఒకవేళ (!c_parser_get_builtin_వాదనలు (parser,
					    "__builtin_complex",
					    &cexpr_list, అబద్ధం,
					    &close_paren_loc))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    ఒకవేళ (vec_సురక్షిత_నిడివి (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_గమ్యం_rvalue (loc, *e1_p, నిజం, నిజం);
	    ఒకవేళ (వృక్షం_సంకేతం (e1_p->విలువ) == EXCESS_PRECISION_సమాసం)
	      e1_p->విలువ = convert (వృక్షం_TYPE (e1_p->విలువ),
				     వృక్షం_నిర్వాహ్యం (e1_p->విలువ, 0));
	    *e2_p = convert_lvalue_గమ్యం_rvalue (loc, *e2_p, నిజం, నిజం);
	    ఒకవేళ (వృక్షం_సంకేతం (e2_p->విలువ) == EXCESS_PRECISION_సమాసం)
	      e2_p->విలువ = convert (వృక్షం_TYPE (e2_p->విలువ),
				     వృక్షం_నిర్వాహ్యం (e2_p->విలువ, 0));
	    ఒకవేళ (!SCALAR_FLOAT_TYPE_P (వృక్షం_TYPE (e1_p->విలువ))
		|| DECIMAL_FLOAT_TYPE_P (వృక్షం_TYPE (e1_p->విలువ))
		|| !SCALAR_FLOAT_TYPE_P (వృక్షం_TYPE (e2_p->విలువ))
		|| DECIMAL_FLOAT_TYPE_P (వృక్షం_TYPE (e2_p->విలువ)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (TYPE_MAIN_VARIANT (వృక్షం_TYPE (e1_p->విలువ))
		!= TYPE_MAIN_VARIANT (వృక్షం_TYPE (e2_p->విలువ)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    సమాసం.విలువ = build2_loc (loc, COMPLEX_సమాసం,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (వృక్షం_TYPE (e1_p->విలువ))),
				     e1_p->విలువ, e2_p->విలువ);
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_paren_loc);
	    ఆపు;
	  }
	స్థితి RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_సమాసం_t, va_gc> *cexpr_list;
	    c_సమాసం_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ఒకవేళ (!c_parser_get_builtin_వాదనలు (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, అబద్ధం,
					    &close_paren_loc))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (vec_సురక్షిత_నిడివి (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    e_p = &(*cexpr_list)[0];
	    వృక్షం ref = e_p->విలువ;

	    ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (ref)) != ARRAY_TYPE
		 && వృక్షం_సంకేతం (వృక్షం_TYPE (ref)) != సూచిక_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    ఒకవేళ (వృక్షం_సంకేతం (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    ఒకవేళ (వృక్షం_సంకేతం (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    ఒకవేళ (has_counted_by_object (ref))
	      సమాసం.విలువ = get_counted_by_ref (ref);
	    లేకపోతే
	      సమాసం.విలువ = null_సూచిక_కణుపు;

	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_paren_loc);
	    ఆపు;
	  }
	స్థితి RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_సమాసం_t, va_gc> *cexpr_list;
	    గుర్తులేని పూర్ణాంకం i;
	    c_సమాసం_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ఒకవేళ (!c_parser_get_builtin_వాదనలు (parser,
					    "__builtin_shuffle",
					    &cexpr_list, అబద్ధం,
					    &close_paren_loc))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    FOR_EACH_VEC_సురక్షిత_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_గమ్యం_rvalue (loc, *p, నిజం, నిజం);

	    ఒకవేళ (vec_సురక్షిత_నిడివి (cexpr_list) == 2)
	      సమాసం.విలువ = c_build_vec_perm_సమాసం (loc, (*cexpr_list)[0].విలువ,
						  NULL_వృక్షం,
						  (*cexpr_list)[1].విలువ);

	    లేకపోతే ఒకవేళ (vec_సురక్షిత_నిడివి (cexpr_list) == 3)
	      సమాసం.విలువ = c_build_vec_perm_సమాసం (loc, (*cexpr_list)[0].విలువ,
						  (*cexpr_list)[1].విలువ,
						  (*cexpr_list)[2].విలువ);
	    లేకపోతే
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		సమాసం.సమితి_error ();
	      }
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_paren_loc);
	    ఆపు;
	  }
	స్థితి RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_సమాసం_t, va_gc> *cexpr_list;
	    గుర్తులేని పూర్ణాంకం i;
	    c_సమాసం_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ఒకవేళ (!c_parser_get_builtin_వాదనలు (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, అబద్ధం,
					    &close_paren_loc))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    FOR_EACH_VEC_సురక్షిత_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_గమ్యం_rvalue (loc, *p, నిజం, నిజం);

	    ఒకవేళ (vec_సురక్షిత_నిడివి (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		సమాసం.సమితి_error ();
	      }
	    లేకపోతే
	      {
		auto_vec<వృక్షం, 16> ముసుగు;
		కొరకు (i = 2; i < cexpr_list->నిడివి (); ++i)
		  ముసుగు.సురక్షిత_నెట్టు ((*cexpr_list)[i].విలువ);
		సమాసం.విలువ = c_build_shufflevector (loc, (*cexpr_list)[0].విలువ,
						    (*cexpr_list)[1].విలువ,
						    ముసుగు);
	      }
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_paren_loc);
	    ఆపు;
	  }
	స్థితి RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t ప్రారంభం_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ఒకవేళ (!parens.require_open (parser))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    e1 = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	    mark_exp_read (e1.విలువ);
	    ఒకవేళ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t చివర_loc = c_parser_peek_token (parser)->get_ముగింపు ();
	    c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ఒకవేళ (t1 == ఖాళీ)
	      సమాసం.సమితి_error ();
	    లేకపోతే
	      {
		వృక్షం type_సమాసం = NULL_వృక్షం;
		సమాసం.విలువ = c_build_vec_convert (ప్రారంభం_loc, e1.విలువ, loc,
						  groktypename (t1, &type_సమాసం,
								ఖాళీ));
		సమితి_c_సమాసం_ఆధారం_range (&సమాసం, ప్రారంభం_loc, చివర_loc);
	      }
	  }
	  ఆపు;
	స్థితి RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t ప్రారంభం_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ఒకవేళ (!parens.require_open (parser))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    e1 = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	    mark_exp_read (e1.విలువ);
	    location_t చివర_loc = c_parser_peek_token (parser)->get_ముగింపు ();
	    parens.skip_until_దొరికింది_close (parser);
	    సమాసం = parser_build_unary_op (loc, PAREN_సమాసం, e1);
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, ప్రారంభం_loc, చివర_loc);
	  }
	  ఆపు;
	స్థితి RID_BUILTIN_STDC:
	  {
	    vec<c_సమాసం_t, va_gc> *cexpr_list;
	    c_సమాసం_t *arg_p;
	    location_t close_paren_loc;
	    గణన c_builtin_stdc {
	      C_BUILTIN_STDC_బిట్టు_CEIL,
	      C_BUILTIN_STDC_బిట్టు_FLOOR,
	      C_BUILTIN_STDC_బిట్టు_వెడల్పు,
	      C_BUILTIN_STDC_లెక్క_ONES,
	      C_BUILTIN_STDC_లెక్క_ZEROS,
	      C_BUILTIN_STDC_మొదటి_LEADING_ONE,
	      C_BUILTIN_STDC_మొదటి_LEADING_ZERO,
	      C_BUILTIN_STDC_మొదటి_TRAILING_ONE,
	      C_BUILTIN_STDC_మొదటి_TRAILING_ZERO,
	      C_BUILTIN_STDC_HAS_SINGLE_బిట్టు,
	      C_BUILTIN_STDC_LEADING_ONES,
	      C_BUILTIN_STDC_LEADING_ZEROS,
	      C_BUILTIN_STDC_ROTATE_ఎడమ,
	      C_BUILTIN_STDC_ROTATE_కుడి,
	      C_BUILTIN_STDC_TRAILING_ONES,
	      C_BUILTIN_STDC_TRAILING_ZEROS,
	      C_BUILTIN_STDC_MAX
	    } stdc_rid = C_BUILTIN_STDC_MAX;
	    స్థిరరాశి అక్షరం *name
	      = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
	    గుర్తులేని అంకె_వాదనలు = 1;
	    ఎంపిక (name[పరిమాణం ("__builtin_stdc_") - 1])
	      {
	      స్థితి 'b':
		ఎంపిక (name[పరిమాణం ("__builtin_stdc_bit_") - 1])
		  {
		  స్థితి 'c':
		    stdc_rid = C_BUILTIN_STDC_బిట్టు_CEIL;
		    ఆపు;
		  స్థితి 'f':
		    stdc_rid = C_BUILTIN_STDC_బిట్టు_FLOOR;
		    ఆపు;
		  అప్రమేయ:
		    stdc_rid = C_BUILTIN_STDC_బిట్టు_వెడల్పు;
		    ఆపు;
		  }
		ఆపు;
	      స్థితి 'c':
		ఒకవేళ (name[పరిమాణం ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_లెక్క_ONES;
		లేకపోతే
		  stdc_rid = C_BUILTIN_STDC_లెక్క_ZEROS;
		ఆపు;
	      స్థితి 'f':
		ఎంపిక (name[పరిమాణం ("__builtin_stdc_first_trailing_") - 1])
		  {
		  స్థితి 'n':
		    stdc_rid = C_BUILTIN_STDC_మొదటి_LEADING_ONE;
		    ఆపు;
		  స్థితి 'e':
		    stdc_rid = C_BUILTIN_STDC_మొదటి_LEADING_ZERO;
		    ఆపు;
		  స్థితి 'o':
		    stdc_rid = C_BUILTIN_STDC_మొదటి_TRAILING_ONE;
		    ఆపు;
		  అప్రమేయ:
		    stdc_rid = C_BUILTIN_STDC_మొదటి_TRAILING_ZERO;
		    ఆపు;
		  }
		ఆపు;
	      స్థితి 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_బిట్టు;
		ఆపు;
	      స్థితి 'l':
		ఒకవేళ (name[పరిమాణం ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		లేకపోతే
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		ఆపు;
	      స్థితి 'r':
		ఒకవేళ (name[పరిమాణం ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_ఎడమ;
		లేకపోతే
		  stdc_rid = C_BUILTIN_STDC_ROTATE_కుడి;
		అంకె_వాదనలు = 2;
		ఆపు;
	      స్థితి 't':
		ఒకవేళ (name[పరిమాణం ("__builtin_stdc_trailing_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ONES;
		లేకపోతే
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ZEROS;
		ఆపు;
	      }
	    gcc_checking_assert (stdc_rid != C_BUILTIN_STDC_MAX);

	    c_parser_consume_token (parser);
	    ఒకవేళ (!c_parser_get_builtin_వాదనలు (parser, name,
					    &cexpr_list, అబద్ధం,
					    &close_paren_loc))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    ఒకవేళ (vec_సురక్షిత_నిడివి (cexpr_list) != అంకె_వాదనలు)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_గమ్యం_rvalue (loc, *arg_p, నిజం, నిజం);
	    ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (arg_p->విలువ)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (arg_p->విలువ)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (arg_p->విలువ)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (!TYPE_UNSIGNED (వృక్షం_TYPE (arg_p->విలువ)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (TYPE_MAIN_VARIANT (వృక్షం_TYPE (arg_p->విలువ))
		== char_type_కణుపు)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    వృక్షం arg = arg_p->విలువ;
	    వృక్షం type = TYPE_MAIN_VARIANT (వృక్షం_TYPE (arg));
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
	    పూర్ణాంకం prec = TYPE_PRECISION (type);
	    ఒకవేళ (అంకె_వాదనలు == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_గమ్యం_rvalue (loc, *arg_p, నిజం, నిజం);
		ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (arg_p->విలువ)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    సమాసం.సమితి_error ();
		    ఆపు;
		  }
		ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (arg_p->విలువ)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    సమాసం.సమితి_error ();
		    ఆపు;
		  }
		వృక్షం arg1 = save_సమాసం (arg);
		వృక్షం arg2 = save_సమాసం (arg_p->విలువ);
		వృక్షం_సంకేతం_2 సంకేతం_2;
		ఒకవేళ (stdc_rid == C_BUILTIN_STDC_ROTATE_ఎడమ)
		  సంకేతం_2 = LROTATE_సమాసం;
		లేకపోతే
		  సంకేతం_2 = RROTATE_సమాసం;

		ఒకవేళ (వృక్షం_సంకేతం (arg2) == INTEGER_CST
		    && వృక్షం_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_లెక్క_negative,
			      "rotate count is negative");

		వృక్షం instrument_సమాసం = NULL_వృక్షం;
		ఒకవేళ (sanitize_flags_p (SANITIZE_జరుపు))
		  instrument_సమాసం = ubsan_instrument_జరుపు (loc, సంకేతం_2,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		ఒకవేళ (TYPE_PRECISION (వృక్షం_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_కణుపు))
		  arg2 = fold_convert (unsigned_type_కణుపు, arg2);

		ఒకవేళ (TYPE_UNSIGNED (వృక్షం_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_సమాసం, వృక్షం_TYPE (arg2),
				     arg2, build_int_cst (వృక్షం_TYPE (arg2),
							  prec));
		లేకపోతే
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    వృక్షం utype = c_common_unsigned_type (వృక్షం_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_సమాసం, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		ఒకవేళ (type_has_బహుళకం_precision_p (వృక్షం_TYPE (arg1))
		    || (వృక్షం_సంకేతం (వృక్షం_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_బహుళకం_కొలత))
		  సమాసం.విలువ = build2_loc (loc, సంకేతం_2, వృక్షం_TYPE (arg1), arg1,
					   arg2);
		లేకపోతే
		  {
		    arg2 = save_సమాసం (arg2);
		    వృక్షం t1 = build2_loc (loc, (సంకేతం_2 == LROTATE_సమాసం
						? LSHIFT_సమాసం : RSHIFT_సమాసం),
					  వృక్షం_TYPE (arg1), arg1, arg2);
		    వృక్షం t2 = build2_loc (loc, MINUS_సమాసం,
					  వృక్షం_TYPE (arg2),
					  build_int_cst (వృక్షం_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (సంకేతం_2 == LROTATE_సమాసం
					   ? RSHIFT_సమాసం : LSHIFT_సమాసం),
				     వృక్షం_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_లెక్క_అధికప్రవాహం);
		    వృక్షం t3 = build2_loc (loc, బిట్టు_IOR_సమాసం,
					  వృక్షం_TYPE (arg1), t1, t2);
		    వృక్షం t4 = build2_loc (loc, NE_సమాసం, boolean_type_కణుపు,
					  arg2,
					  build_zero_cst (వృక్షం_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_సమాసం, boolean_type_కణుపు,
				     arg1, t4);
		    సమాసం.విలువ = build3_loc (loc, COND_సమాసం,
					     వృక్షం_TYPE (arg1), t4, t3, arg1);
		  }
		ఒకవేళ (instrument_సమాసం)
		  సమాసం.విలువ = build2_loc (loc, COMPOUND_సమాసం,
					   వృక్షం_TYPE (సమాసం.విలువ),
					   instrument_సమాసం, సమాసం.విలువ);
		సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_paren_loc);
		ఆపు;
	      }
	    వృక్షం barg1 = arg;
	    ఎంపిక (stdc_rid)
	      {
	      స్థితి C_BUILTIN_STDC_బిట్టు_CEIL:
		arg = save_సమాసం (arg);
		barg1 = build2_loc (loc, PLUS_సమాసం, type, arg,
				    build_int_cst (type, -1));
		ఆపు;
	      స్థితి C_BUILTIN_STDC_బిట్టు_FLOOR:
		barg1 = arg = save_సమాసం (arg);
		ఆపు;
	      స్థితి C_BUILTIN_STDC_లెక్క_ZEROS:
	      స్థితి C_BUILTIN_STDC_మొదటి_LEADING_ZERO:
	      స్థితి C_BUILTIN_STDC_మొదటి_TRAILING_ZERO:
	      స్థితి C_BUILTIN_STDC_LEADING_ONES:
	      స్థితి C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, బిట్టు_NOT_సమాసం, type, arg);
		ఆపు;
	      అప్రమేయ:
		ఆపు;
	      }
	    వృక్షం barg2 = NULL_వృక్షం;
	    ఎంపిక (stdc_rid)
	      {
	      స్థితి C_BUILTIN_STDC_బిట్టు_వెడల్పు:
	      స్థితి C_BUILTIN_STDC_LEADING_ONES:
	      స్థితి C_BUILTIN_STDC_LEADING_ZEROS:
	      స్థితి C_BUILTIN_STDC_TRAILING_ONES:
	      స్థితి C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_కణుపు, prec);
		ఆపు;
	      స్థితి C_BUILTIN_STDC_మొదటి_LEADING_ONE:
	      స్థితి C_BUILTIN_STDC_మొదటి_LEADING_ZERO:
	      స్థితి C_BUILTIN_STDC_మొదటి_TRAILING_ONE:
	      స్థితి C_BUILTIN_STDC_మొదటి_TRAILING_ZERO:
		barg2 = integer_minus_one_కణుపు;
		ఆపు;
	      అప్రమేయ:
		ఆపు;
	      }
	    వృక్షం fndecl = NULL_వృక్షం;
	    ఎంపిక (stdc_rid)
	      {
	      స్థితి C_BUILTIN_STDC_బిట్టు_CEIL:
	      స్థితి C_BUILTIN_STDC_బిట్టు_FLOOR:
	      స్థితి C_BUILTIN_STDC_బిట్టు_వెడల్పు:
	      స్థితి C_BUILTIN_STDC_మొదటి_LEADING_ONE:
	      స్థితి C_BUILTIN_STDC_మొదటి_LEADING_ZERO:
	      స్థితి C_BUILTIN_STDC_LEADING_ONES:
	      స్థితి C_BUILTIN_STDC_LEADING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_లోపల_CLZG);
		ఆపు;
	      స్థితి C_BUILTIN_STDC_మొదటి_TRAILING_ONE:
	      స్థితి C_BUILTIN_STDC_మొదటి_TRAILING_ZERO:
	      స్థితి C_BUILTIN_STDC_TRAILING_ONES:
	      స్థితి C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_లోపల_CTZG);
		ఆపు;
	      స్థితి C_BUILTIN_STDC_లెక్క_ONES:
	      స్థితి C_BUILTIN_STDC_లెక్క_ZEROS:
	      స్థితి C_BUILTIN_STDC_HAS_SINGLE_బిట్టు:
		fndecl = builtin_decl_explicit (BUILT_లోపల_POPCOUNTG);
		ఆపు;
	      అప్రమేయ:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    పూర్ణాంకం nargs = barg2 != NULL_వృక్షం ? 2 : 1;
	    vec<వృక్షం, va_gc> *వాదనలు;
	    vec_alloc (వాదనలు, nargs);
	    vec<వృక్షం, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    వాదనలు->శీఘ్ర_నెట్టు (barg1);
	    arg_loc.శీఘ్ర_నెట్టు (arg_p->get_location ());
	    origtypes->శీఘ్ర_నెట్టు (arg_p->original_type);
	    ఒకవేళ (nargs == 2)
	      {
		వాదనలు->శీఘ్ర_నెట్టు (barg2);
		arg_loc.శీఘ్ర_నెట్టు (loc);
		origtypes->శీఘ్ర_నెట్టు (integer_type_కణుపు);
	      }
	    సమాసం.విలువ = c_build_function_call_vec (loc, arg_loc, fndecl,
						    వాదనలు, origtypes);
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_paren_loc);
	    ఒకవేళ (సమాసం.విలువ == error_mark_కణుపు)
	      ఆపు;
	    ఎంపిక (stdc_rid)
	      {
	      స్థితి C_BUILTIN_STDC_బిట్టు_CEIL:
	      స్థితి C_BUILTIN_STDC_బిట్టు_FLOOR:
		--prec;
		/* FALLTHRU */
	      స్థితి C_BUILTIN_STDC_బిట్టు_వెడల్పు:
		సమాసం.విలువ = build2_loc (loc, MINUS_సమాసం, integer_type_కణుపు,
					 build_int_cst (integer_type_కణుపు,
							prec), సమాసం.విలువ);
		ఆపు;
	      స్థితి C_BUILTIN_STDC_మొదటి_LEADING_ONE:
	      స్థితి C_BUILTIN_STDC_మొదటి_LEADING_ZERO:
	      స్థితి C_BUILTIN_STDC_మొదటి_TRAILING_ONE:
	      స్థితి C_BUILTIN_STDC_మొదటి_TRAILING_ZERO:
		సమాసం.విలువ = build2_loc (loc, PLUS_సమాసం, integer_type_కణుపు,
					 సమాసం.విలువ, integer_one_కణుపు);
		ఆపు;
	      స్థితి C_BUILTIN_STDC_HAS_SINGLE_బిట్టు:
		సమాసం.విలువ = build2_loc (loc, EQ_సమాసం, boolean_type_కణుపు,
					 సమాసం.విలువ, integer_one_కణుపు);
		ఆపు;
	      అప్రమేయ:
		ఆపు;
	      }

	    ఒకవేళ (stdc_rid != C_BUILTIN_STDC_బిట్టు_CEIL
		&& stdc_rid != C_BUILTIN_STDC_బిట్టు_FLOOR)
	      {
		ఒకవేళ (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_బిట్టు)
		  సమాసం.విలువ = fold_convert_loc (loc, unsigned_type_కణుపు,
						 సమాసం.విలువ);
		ఆపు;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    ఒకవేళ (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_బిట్టు_CEIL && integer_onep (arg)))
	      సమాసం.విలువ = build_int_cst (type, 0);
	    లేకపోతే
	      సమాసం.విలువ
		= build2_loc (loc, LSHIFT_సమాసం, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_బిట్టు_CEIL
					      ? 2 : 1)), సమాసం.విలువ);
	    ఒకవేళ (stdc_rid == C_BUILTIN_STDC_బిట్టు_CEIL)
	      సమాసం.విలువ = build3_loc (loc, COND_సమాసం, type,
				       build2_loc (loc, LE_సమాసం,
						   boolean_type_కణుపు, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       సమాసం.విలువ);
	    లేకపోతే
	      సమాసం.విలువ = build3_loc (loc, COND_సమాసం, type,
				       build2_loc (loc, EQ_సమాసం,
						   boolean_type_కణుపు, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       సమాసం.విలువ);
	    ఆపు;
	  }
	స్థితి RID_BUILTIN_BSWAPG:
	స్థితి RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_సమాసం_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    అంతర్గత_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    స్థిరరాశి అక్షరం *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    ఒకవేళ (!c_parser_get_builtin_వాదనలు (parser, name, &cexpr_list, అబద్ధం,
					    &close_paren_loc))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    ఒకవేళ (vec_సురక్షిత_నిడివి (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		సమాసం.సమితి_error ();
		ఆపు;
	      }

	    c_సమాసం_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_గమ్యం_rvalue (loc, *arg_p, నిజం, నిజం);
	    వృక్షం arg = arg_p->విలువ;
	    ఒకవేళ (error_నిర్వాహ్యం_p (arg))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    వృక్షం type = TYPE_MAIN_VARIANT (వృక్షం_TYPE (arg));
	    ఒకవేళ (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (వృక్షం_సంకేతం (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (వృక్షం_సంకేతం (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    arg = c_fully_fold (arg, అబద్ధం, ఖాళీ);
	    సమాసం.విలువ = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_paren_loc);
	    ఆపు;
	  }
	స్థితి RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ఒకవేళ (!parens.require_open (parser))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    వృక్షం sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_దొరికింది_close (parser);
	    సమాసం.విలువ = objc_build_selector_సమాసం (loc, sel);
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_loc);
	  }
	  ఆపు;
	స్థితి RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ఒకవేళ (!parens.require_open (parser))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    వృక్షం id = c_parser_peek_token (parser)->విలువ;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_దొరికింది_close (parser);
	    సమాసం.విలువ = objc_build_protocol_సమాసం (id);
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_loc);
	  }
	  ఆపు;
	స్థితి RID_AT_ENCODE:
	  {
	    /* Extension to support C-structures in the archiver.  */
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ఒకవేళ (!parens.require_open (parser))
	      {
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    t1 = c_parser_type_name (parser);
	    ఒకవేళ (t1 == ఖాళీ)
	      {
		సమాసం.సమితి_error ();
		c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
		ఆపు;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_దొరికింది_close (parser);
	    వృక్షం type = groktypename (t1, ఖాళీ, ఖాళీ);
	    సమాసం.విలువ = objc_build_encode_సమాసం (type);
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_loc);
	  }
	  ఆపు;
	స్థితి RID_GENERIC:
	  సమాసం = c_parser_generic_selection (parser);
	  ఆపు;
	స్థితి RID_OMP_ALL_జ్ఞాపకం:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  సమాసం.సమితి_error ();
	  ఆపు;
	/* C23 'nullptr' literal.  */
	స్థితి RID_NULLPTR:
	  c_parser_consume_token (parser);
	  సమాసం.విలువ = nullptr_కణుపు;
	  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  ఆపు;
	స్థితి RID_TRUE:
	  c_parser_consume_token (parser);
	  సమాసం.విలువ = boolean_true_కణుపు;
	  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, tok_range);
	  ఆపు;
	స్థితి RID_FALSE:
	  c_parser_consume_token (parser);
	  సమాసం.విలువ = boolean_false_కణుపు;
	  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, tok_range);
	  ఆపు;
	అప్రమేయ:
	  c_parser_error (parser, "expected expression");
	  సమాసం.సమితి_error ();
	  ఆపు;
	}
      ఆపు;
    స్థితి CPP_OPEN_వర్గం:
      ఒకవేళ (c_dialect_objc ())
	{
	  వృక్షం receiver, వాదనలు;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  వాదనలు = c_parser_objc_సందేశం_వాదనలు (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_వర్గం,
				     "expected %<]%>");
	  సమాసం.విలువ = objc_build_సందేశం_సమాసం (receiver, వాదనలు);
	  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, loc, close_loc);
	  ఆపు;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    అప్రమేయ:
      c_parser_error (parser, "expected expression");
      సమాసం.సమితి_error ();
      ఆపు;
    }
 బహిర్గతం:
  తిరిగి c_parser_postfix_వ్యక్తీకరణ_after_primary
    (parser, సమాసం_LOC_OR_LOC (సమాసం.విలువ, loc), సమాసం);
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

స్థిర నిర్మాణం c_సమాసం
c_parser_postfix_వ్యక్తీకరణ_after_paren_type (c_parser *parser,
					      నిర్మాణం c_declspecs *scspecs,
					      నిర్మాణం c_type_name *type_name,
					      location_t type_loc)
{
  వృక్షం type;
  నిర్మాణం c_సమాసం init;
  తార్కిక non_const;
  నిర్మాణం c_సమాసం సమాసం;
  location_t ప్రారంభం_loc;
  వృక్షం type_సమాసం = NULL_వృక్షం;
  తార్కిక type_సమాసం_const = నిజం;
  తార్కిక constexpr_p = scspecs ? scspecs->constexpr_p : అబద్ధం;
  గుర్తులేని పూర్ణాంకం underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (పంక్తి_పట్టిక, type_loc);
  ప్రారంభం_loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (constexpr_p)
    {
      underspec_state = ప్రారంభం_underspecified_init (ప్రారంభం_loc, NULL_వృక్షం);
      /* A constexpr compound literal is subject to the constraints on
	 underspecified declarations, which may not declare tags or
	 members or structures or unions; it is undefined behavior to
	 declare the members of an enumeration.  Where the structure,
	 union or enumeration type is declared within the compound
	 literal initializer, this is diagnosed elsewhere as a result
	 of the above call to start_underspecified_init.  Diagnose
	 here the case of declaring such a type in the type specifiers
	 of the compound literal.  */
      ఎంపిక (type_name->specs->typespec_రకం)
	{
	స్థితి ctsk_tagfirstref:
	స్థితి ctsk_tagfirstref_attrs:
	  error_at (type_loc, "%qT declared in %<constexpr%> compound literal",
		    type_name->specs->type);
	  ఆపు;

	స్థితి ctsk_tagdef:
	  error_at (type_loc, "%qT defined in %<constexpr%> compound literal",
		    type_name->specs->type);
	  ఆపు;

	అప్రమేయ:
	  ఆపు;
	}
    }
  ప్రారంభం_init (NULL_వృక్షం, ఖాళీ,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_సమాసం, &type_సమాసం_const);
  తార్కిక varsize_p = అబద్ధం;
  ఒకవేళ (type != error_mark_కణుపు && C_TYPE_VARIABLE_కొలత (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = నిజం;
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_కణుపు;
    }
  ఒకవేళ (constexpr_p && type != error_mark_కణుపు)
    {
      వృక్షం type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      ఒకవేళ (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      లేకపోతే ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, అబద్ధం, ఖాళీ, varsize_p);
  ఒకవేళ (constexpr_p)
    ముగింపు_underspecified_init (NULL_వృక్షం, underspec_state);
  ముగింపు_init ();
  maybe_warn_string_init (type_loc, type, init);

  ఒకవేళ (type != error_mark_కణుపు
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_కణుపు;
    }

  ఒకవేళ (!pedwarn_c90 (ప్రారంభం_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (ప్రారంభం_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.విలువ && వృక్షం_సంకేతం (init.విలువ) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.విలువ)
	       : init.original_సంకేతం == C_MAYBE_CONST_సమాసం);
  non_const |= !type_సమాసం_const;
  గుర్తులేని పూర్ణాంకం alignas_align = 0;
  ఒకవేళ (type != error_mark_కణుపు
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      ఒకవేళ (alignas_align < min_align_యొక్క_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  సమాసం.విలువ = build_compound_literal (ప్రారంభం_loc, type, init.విలువ, non_const,
				       alignas_align, scspecs);
  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, init.src_range);
  సమాసం.m_decimal = 0;
  సమాసం.original_సంకేతం = ERROR_MARK;
  సమాసం.original_type = ఖాళీ;
  ఒకవేళ (type != error_mark_కణుపు
      && సమాసం.విలువ != error_mark_కణుపు
      && type_సమాసం)
    {
      ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) == C_MAYBE_CONST_సమాసం)
	{
	  gcc_assert (C_MAYBE_CONST_సమాసం_PRE (సమాసం.విలువ) == NULL_వృక్షం);
	  C_MAYBE_CONST_సమాసం_PRE (సమాసం.విలువ) = type_సమాసం;
	}
      లేకపోతే
	{
	  gcc_assert (!non_const);
	  సమాసం.విలువ = build2 (C_MAYBE_CONST_సమాసం, type,
			       type_సమాసం, సమాసం.విలువ);
	}
    }
  తిరిగి c_parser_postfix_వ్యక్తీకరణ_after_primary (parser, ప్రారంభం_loc, సమాసం);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

స్థిర తార్కిక
sizeof_ptr_memacc_comptypes (వృక్షం type1, వృక్షం type2)
{
  తిరిగి comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

స్థిర శూన్య
warn_for_abs (location_t loc, వృక్షం fndecl, వృక్షం arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  ఒకవేళ (c_inhibit_evaluation_warnings)
    తిరిగి;

  వృక్షం atype = వృక్షం_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  ఒకవేళ (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && వృక్షం_సంకేతం (atype) != COMPLEX_TYPE)
    తిరిగి;

  గణన built_లోపల_function fcode = DECL_FUNCTION_సంకేతం (fndecl);

  ఎంపిక (fcode)
    {
    స్థితి BUILT_లోపల_ABS:
    స్థితి BUILT_లోపల_LABS:
    స్థితి BUILT_లోపల_LLABS:
    స్థితి BUILT_లోపల_IMAXABS:
      ఒకవేళ (!INTEGRAL_TYPE_P (atype))
	{
	  ఒకవేళ (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_విలువ,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_విలువ,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  లేకపోతే
	    gcc_unreachable ();
	  తిరిగి;
	}
      ఒకవేళ (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_విలువ,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      ఆపు;

    CASE_FLT_FN (BUILT_లోపల_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_లోపల_FABS):
      ఒకవేళ (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_బహుళకం_P (TYPE_బహుళకం (atype)))
	{
	  ఒకవేళ (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_విలువ,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  లేకపోతే ఒకవేళ (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_విలువ,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_విలువ,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  లేకపోతే
	    gcc_unreachable ();
	  తిరిగి;
	}
      ఆపు;

    CASE_FLT_FN (BUILT_లోపల_CABS):
      ఒకవేళ (వృక్షం_సంకేతం (atype) != COMPLEX_TYPE)
	{
	  ఒకవేళ (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_విలువ,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  లేకపోతే ఒకవేళ (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_విలువ,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  లేకపోతే
	    gcc_unreachable ();

	  తిరిగి;
	}
      ఆపు;

    స్థితి BUILT_లోపల_FABSD32:
    స్థితి BUILT_లోపల_FABSD64:
    స్థితి BUILT_లోపల_FABSD128:
    స్థితి BUILT_లోపల_FABSD64_X:
      ఒకవేళ (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  ఒకవేళ (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_విలువ,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  లేకపోతే ఒకవేళ (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_విలువ,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_విలువ,
			"using decimal floating-point absolute value "
			"function %qD when argument is of complex type %qT",
			fndecl, atype);
	  లేకపోతే
	    gcc_unreachable ();
	  తిరిగి;
	}
      ఆపు;

    అప్రమేయ:
      తిరిగి;
    }

  ఒకవేళ (!TYPE_ARG_TYPES (వృక్షం_TYPE (fndecl)))
    తిరిగి;

  వృక్షం ftype = వృక్షం_విలువ (TYPE_ARG_TYPES (వృక్షం_TYPE (fndecl)));
  ఒకవేళ (వృక్షం_సంకేతం (atype) == COMPLEX_TYPE)
    {
      gcc_assert (వృక్షం_సంకేతం (ftype) == COMPLEX_TYPE);
      atype = వృక్షం_TYPE (atype);
      ftype = వృక్షం_TYPE (ftype);
    }

  ఒకవేళ (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_విలువ,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

స్థిర నిర్మాణం c_సమాసం
c_parser_postfix_వ్యక్తీకరణ_after_primary (c_parser *parser,
					   location_t సమాసం_loc,
					   నిర్మాణం c_సమాసం సమాసం)
{
  నిర్మాణం c_సమాసం orig_సమాసం;
  వృక్షం ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  వృక్షం sizeof_arg[6];
  గుర్తులేని పూర్ణాంకం literal_zero_ముసుగు;
  గుర్తులేని పూర్ణాంకం i;
  vec<వృక్షం, va_gc> *exprlist;
  vec<వృక్షం, va_gc> *origtypes = ఖాళీ;
  vec<location_t> arg_loc = vNULL;
  location_t ప్రారంభం;
  location_t ముగింపు;

  అయితే (నిజం)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      ఎంపిక (c_parser_peek_token (parser)->type)
	{
	స్థితి CPP_OPEN_వర్గం:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_వృక్షం;
	  ఒకవేళ (!c_omp_array_section_p
	      || c_parser_తదుపరి_token_is_not (parser, CPP_COLON))
	    idx = c_parser_వ్యక్తీకరణ (parser).విలువ;

	  ఒకవేళ (c_omp_array_section_p
	      && c_parser_తదుపరి_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_CLOSE_వర్గం))
		len = c_parser_వ్యక్తీకరణ (parser).విలువ;

	      సమాసం.విలువ = build_omp_array_section (op_loc, సమాసం.విలువ, idx,
						    len);
	    }
	  లేకపోతే
	    సమాసం.విలువ = build_array_ref (op_loc, సమాసం.విలువ, idx);

	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_వర్గం,
				     "expected %<]%>");

	  ప్రారంభం = సమాసం.get_ప్రారంభం ();
	  ముగింపు = parser->టోకెన్లు_buf[0].location;
	  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, ప్రారంభం, ముగింపు);
	  సమాసం.original_సంకేతం = ERROR_MARK;
	  సమాసం.original_type = ఖాళీ;
	  సమాసం.m_decimal = 0;
	  ఆపు;
	స్థితి CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    కొరకు (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_వృక్షం;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_ముసుగు = 0;
	    ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = ఖాళీ;
	    లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) == FUNCTION_DECL
		     && fndecl_built_లోపల_p (సమాసం.విలువ, BUILT_లోపల_CLASSIFY_TYPE)
		     && c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_typename (parser,
							     cla_prefer_id))
	      {
		/* __builtin_classify_type (type)  */
		c_inhibit_evaluation_warnings++;
		లోపల_alignof++;
		నిర్మాణం c_type_name *type = c_parser_type_name (parser);
		c_inhibit_evaluation_warnings--;
		లోపల_alignof--;
		నిర్మాణం c_typespec ret;
		ret.సమాసం = NULL_వృక్షం;
		ret.spec = error_mark_కణుపు;
		ret.సమాసం_const_operands = అబద్ధం;
		ఒకవేళ (type != ఖాళీ)
		  ret.spec = groktypename (type, &ret.సమాసం,
					   &ret.సమాసం_const_operands);
		parens.skip_until_దొరికింది_close (parser);
		సమాసం.విలువ = build_int_cst (integer_type_కణుపు,
					    type_గమ్యం_class (ret.spec));
		ఆపు;
	      }
	    లేకపోతే
	      exprlist = c_parser_సమాసం_list (parser, నిజం, అబద్ధం, &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_ముసుగు);
	    parens.skip_until_దొరికింది_close (parser);
	  }
	  orig_సమాసం = సమాసం;
	  mark_exp_read (సమాసం.విలువ);
	  ఒకవేళ (warn_sizeof_సూచిక_memaccess)
	    sizeof_సూచిక_memaccess_warning (sizeof_arg_loc,
					      సమాసం.విలువ, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) == FUNCTION_DECL)
	    {
	      ఒకవేళ (fndecl_built_లోపల_p (సమాసం.విలువ, BUILT_లోపల_MEMSET)
		  && vec_సురక్షిత_నిడివి (exprlist) == 3)
		{
		  వృక్షం arg0 = (*exprlist)[0];
		  వృక్షం arg2 = (*exprlist)[2];
		  warn_for_memset (సమాసం_loc, arg0, arg2, literal_zero_ముసుగు);
		}
	      ఒకవేళ (warn_absolute_విలువ
		  && fndecl_built_లోపల_p (సమాసం.విలువ, BUILT_లోపల_సాధారణ)
		  && vec_సురక్షిత_నిడివి (exprlist) == 1)
		warn_for_abs (సమాసం_loc, సమాసం.విలువ, (*exprlist)[0]);
	      ఒకవేళ (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->లోపల_intervening_సంకేతం
		  && omp_runtime_api_call (సమాసం.విలువ))
		{
		  error_at (సమాసం_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->fail = నిజం;
		}
	      ఒకవేళ (warn_calloc_transposed_వాదనలు)
		ఒకవేళ (వృక్షం attr = lookup_attribute ("alloc_size",
						  TYPE_లక్షణాలు
						    (వృక్షం_TYPE (సమాసం.విలువ))))
		  ఒకవేళ (వృక్షం_విలువ (attr) && వృక్షం_CHAIN (వృక్షం_విలువ (attr)))
		    warn_for_calloc (sizeof_arg_loc, సమాసం.విలువ, exprlist,
				     sizeof_arg, attr);
	    }

	  ప్రారంభం = సమాసం.get_ప్రారంభం ();
	  ముగింపు = parser->టోకెన్లు_buf[0].get_ముగింపు ();
	  సమాసం.విలువ
	    = c_build_function_call_vec (సమాసం_loc, arg_loc, సమాసం.విలువ,
					 exprlist, origtypes);
	  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, ప్రారంభం, ముగింపు);
	  సమాసం.m_decimal = 0;

	  సమాసం.original_సంకేతం = ERROR_MARK;
	  ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) == INTEGER_CST
	      && వృక్షం_సంకేతం (orig_సమాసం.విలువ) == FUNCTION_DECL
	      && fndecl_built_లోపల_p (orig_సమాసం.విలువ, BUILT_లోపల_CONSTANT_P))
	    సమాసం.original_సంకేతం = C_MAYBE_CONST_సమాసం;
	  సమాసం.original_type = ఖాళీ;
	  ఒకవేళ (exprlist)
	    {
	      release_వృక్షం_సదిశ (exprlist);
	      release_వృక్షం_సదిశ (origtypes);
	    }
	  arg_loc.release ();
	  ఆపు;
	స్థితి CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  సమాసం = default_function_array_conversion (సమాసం_loc, సమాసం);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->విలువ;
	      comp_loc = comp_tok->location;
	    }
	  లేకపోతే
	    {
	      c_parser_error (parser, "expected identifier");
	      సమాసం.సమితి_error ();
	      సమాసం.original_సంకేతం = ERROR_MARK;
              సమాసం.original_type = ఖాళీ;
	      తిరిగి సమాసం;
	    }
	  ప్రారంభం = సమాసం.get_ప్రారంభం ();
	  ముగింపు = c_parser_peek_token (parser)->get_ముగింపు ();
	  c_parser_consume_token (parser);
	  సమాసం.విలువ = build_component_ref (op_loc, సమాసం.విలువ, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, ప్రారంభం, ముగింపు);
	  సమాసం.original_సంకేతం = ERROR_MARK;
	  ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) != COMPONENT_REF)
	    సమాసం.original_type = ఖాళీ;
	  లేకపోతే
	    {
	      /* Remember the original type of a bitfield.  */
	      వృక్షం క్షేత్రం_2 = వృక్షం_నిర్వాహ్యం (సమాసం.విలువ, 1);
	      ఒకవేళ (వృక్షం_సంకేతం (క్షేత్రం_2) != క్షేత్రం_DECL)
		సమాసం.original_type = ఖాళీ;
	      లేకపోతే
		సమాసం.original_type = DECL_బిట్టు_క్షేత్రం_TYPE (క్షేత్రం_2);
	    }
	  సమాసం.m_decimal = 0;
	  ఆపు;
	స్థితి CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, నిజం, అబద్ధం);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->విలువ;
	      comp_loc = comp_tok->location;
	    }
	  లేకపోతే
	    {
	      c_parser_error (parser, "expected identifier");
	      సమాసం.సమితి_error ();
	      సమాసం.original_సంకేతం = ERROR_MARK;
	      సమాసం.original_type = ఖాళీ;
	      తిరిగి సమాసం;
	    }
	  ప్రారంభం = సమాసం.get_ప్రారంభం ();
	  ముగింపు = c_parser_peek_token (parser)->get_ముగింపు ();
	  c_parser_consume_token (parser);
	  సమాసం.విలువ = build_component_ref (op_loc,
					    build_పరోక్ష_ref (op_loc,
								సమాసం.విలువ,
								RO_ARROW),
					    ident, comp_loc,
					    సమాసం.get_location ());
	  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, ప్రారంభం, ముగింపు);
	  సమాసం.original_సంకేతం = ERROR_MARK;
	  ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) != COMPONENT_REF)
	    సమాసం.original_type = ఖాళీ;
	  లేకపోతే
	    {
	      /* Remember the original type of a bitfield.  */
	      వృక్షం క్షేత్రం_2 = వృక్షం_నిర్వాహ్యం (సమాసం.విలువ, 1);
	      ఒకవేళ (వృక్షం_సంకేతం (క్షేత్రం_2) != క్షేత్రం_DECL)
		సమాసం.original_type = ఖాళీ;
	      లేకపోతే
		సమాసం.original_type = DECL_బిట్టు_క్షేత్రం_TYPE (క్షేత్రం_2);
	    }
	  సమాసం.m_decimal = 0;
	  ఆపు;
	స్థితి CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  ప్రారంభం = సమాసం.get_ప్రారంభం ();
	  ముగింపు = c_parser_peek_token (parser)->get_ముగింపు ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (సమాసం.విలువ);
	  సమాసం = default_function_array_conversion (సమాసం_loc, సమాసం);
	  సమాసం.విలువ = build_unary_op (op_loc, POSTINCREMENT_సమాసం,
				       సమాసం.విలువ, అబద్ధం);
	  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, ప్రారంభం, ముగింపు);
	  సమాసం.original_సంకేతం = ERROR_MARK;
	  సమాసం.original_type = ఖాళీ;
	  ఆపు;
	స్థితి CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  ప్రారంభం = సమాసం.get_ప్రారంభం ();
	  ముగింపు = c_parser_peek_token (parser)->get_ముగింపు ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (సమాసం.విలువ);
	  సమాసం = default_function_array_conversion (సమాసం_loc, సమాసం);
	  సమాసం.విలువ = build_unary_op (op_loc, POSTDECREMENT_సమాసం,
				       సమాసం.విలువ, అబద్ధం);
	  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, ప్రారంభం, ముగింపు);
	  సమాసం.original_సంకేతం = ERROR_MARK;
	  సమాసం.original_type = ఖాళీ;
	  ఆపు;
	అప్రమేయ:
	  తిరిగి సమాసం;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

స్థిర నిర్మాణం c_సమాసం
c_parser_వ్యక్తీకరణ (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  నిర్మాణం c_సమాసం సమాసం;
  సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
    సమాసం = convert_lvalue_గమ్యం_rvalue (tloc, సమాసం, నిజం, అబద్ధం);
  అయితే (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
    {
      నిర్మాణం c_సమాసం తదుపరి;
      వృక్షం lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t సమాసం_loc;
      c_parser_consume_token (parser);
      సమాసం_loc = c_parser_peek_token (parser)->location;
      lhsval = సమాసం.విలువ;
      అయితే (వృక్షం_సంకేతం (lhsval) == COMPOUND_సమాసం
	     || వృక్షం_సంకేతం (lhsval) == NOP_సమాసం)
	{
	  ఒకవేళ (వృక్షం_సంకేతం (lhsval) == COMPOUND_సమాసం)
	    lhsval = వృక్షం_నిర్వాహ్యం (lhsval, 1);
	  లేకపోతే
	    lhsval = వృక్షం_నిర్వాహ్యం (lhsval, 0);
	}
      ఒకవేళ (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  వృక్షం val = embed->విలువ;
	  గుర్తులేని చివరి = RAW_దత్తాంశం_నిడివి (val) - 1;
	  తదుపరి.విలువ = build_int_cst (వృక్షం_TYPE (val),
				      RAW_దత్తాంశం_UCHAR_ELT (val, చివరి));
	  తదుపరి.original_type = integer_type_కణుపు;
	  c_parser_consume_token (parser);
	}
      లేకపోతే
	{
	  తదుపరి = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	  తదుపరి = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, తదుపరి, నిజం, అబద్ధం);
	}
      సమాసం.విలువ = build_compound_సమాసం (loc, సమాసం.విలువ, తదుపరి.విలువ);
      సమాసం.original_సంకేతం = COMPOUND_సమాసం;
      సమాసం.original_type = తదుపరి.original_type;
      సమాసం.m_decimal = 0;
    }
  తిరిగి సమాసం;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

స్థిర నిర్మాణం c_సమాసం
c_parser_వ్యక్తీకరణ_conv (c_parser *parser)
{
  నిర్మాణం c_సమాసం సమాసం;
  location_t loc = c_parser_peek_token (parser)->location;
  సమాసం = c_parser_వ్యక్తీకరణ (parser);
  సమాసం = convert_lvalue_గమ్యం_rvalue (loc, సమాసం, నిజం, అబద్ధం);
  తిరిగి సమాసం;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

స్థిర అంతఃవరుస శూన్య
c_parser_check_literal_zero (c_parser *parser, గుర్తులేని *literal_zero_ముసుగు,
			     గుర్తులేని పూర్ణాంకం idx)
{
  ఒకవేళ (idx >= HOST_బిట్లు_చొప్పున_INT)
    తిరిగి;

  c_token *tok = c_parser_peek_token (parser);
  ఎంపిక (tok->type)
    {
    స్థితి CPP_సంఖ్య:
    స్థితి CPP_CHAR:
    స్థితి CPP_WCHAR:
    స్థితి CPP_CHAR16:
    స్థితి CPP_CHAR32:
    స్థితి CPP_UTF8CHAR:
      /* If a parameter is literal zero alone, remember it
	 for -Wmemset-transposed-args warning.  */
      ఒకవేళ (integer_zerop (tok->విలువ)
	  && !వృక్షం_అధికప్రవాహం (tok->విలువ)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_ముసుగు |= 1U << idx;
    అప్రమేయ:
      ఆపు;
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

స్థిర vec<వృక్షం, va_gc> *
c_parser_సమాసం_list (c_parser *parser, తార్కిక convert_p, తార్కిక fold_p,
		    vec<వృక్షం, va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, వృక్షం *sizeof_arg,
		    vec<location_t> *locations,
		    గుర్తులేని పూర్ణాంకం *literal_zero_ముసుగు)
{
  vec<వృక్షం, va_gc> *ret;
  vec<వృక్షం, va_gc> *orig_types;
  నిర్మాణం c_సమాసం సమాసం;
  గుర్తులేని పూర్ణాంకం idx = 0;
  తార్కిక save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = అబద్ధం;

  ret = make_వృక్షం_సదిశ ();
  ఒకవేళ (p_orig_types == ఖాళీ)
    orig_types = ఖాళీ;
  లేకపోతే
    orig_types = make_వృక్షం_సదిశ ();

  ఒకవేళ (literal_zero_ముసుగు)
    c_parser_check_literal_zero (parser, literal_zero_ముసుగు, 0);
  సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
  ఒకవేళ (convert_p)
    సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం.get_location (), సమాసం, నిజం, నిజం);
  ఒకవేళ (fold_p)
    సమాసం.విలువ = c_fully_fold (సమాసం.విలువ, అబద్ధం, ఖాళీ);
  ret->శీఘ్ర_నెట్టు (సమాసం.విలువ);
  ఒకవేళ (orig_types)
    orig_types->శీఘ్ర_నెట్టు (సమాసం.original_type);
  ఒకవేళ (locations)
    locations->సురక్షిత_నెట్టు (సమాసం.get_location ());
  ఒకవేళ (sizeof_arg != ఖాళీ
      && (సమాసం.original_సంకేతం == SIZEOF_సమాసం
	  || సమాసం.original_సంకేతం == PAREN_SIZEOF_సమాసం))
    {
      sizeof_arg[0] = c_చివరి_sizeof_arg;
      sizeof_arg_loc[0] = c_చివరి_sizeof_loc;
    }
  అయితే (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  వృక్షం విలువ = embed->విలువ;
	  సమాసం.original_సంకేతం = INTEGER_CST;
	  సమాసం.original_type = integer_type_కణుపు;
	  సమాసం.విలువ = NULL_వృక్షం;
	  సమితి_c_సమాసం_ఆధారం_range (&సమాసం, embed->get_range ());
	  సమాసం.m_decimal = 0;
	  కొరకు (గుర్తులేని పూర్ణాంకం i = 0; i < (గుర్తులేని) RAW_దత్తాంశం_నిడివి (విలువ); i++)
	    {
	      ఒకవేళ (literal_zero_ముసుగు
		  && idx + 1 < HOST_బిట్లు_చొప్పున_INT
		  && RAW_దత్తాంశం_సూచిక (విలువ)[i] == 0)
		*literal_zero_ముసుగు |= 1U << (idx + 1);
	      సమాసం.విలువ = build_int_cst (integer_type_కణుపు,
					  RAW_దత్తాంశం_UCHAR_ELT (విలువ, i));
	      vec_సురక్షిత_నెట్టు (ret, సమాసం.విలువ);
	      ఒకవేళ (orig_types)
		vec_సురక్షిత_నెట్టు (orig_types, సమాసం.original_type);
	      ఒకవేళ (locations)
		locations->సురక్షిత_నెట్టు (సమాసం.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  కొనసాగు;
	}
      ఒకవేళ (literal_zero_ముసుగు)
	c_parser_check_literal_zero (parser, literal_zero_ముసుగు, idx + 1);
      సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      ఒకవేళ (convert_p)
	సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం.get_location (), సమాసం, నిజం,
					 నిజం);
      ఒకవేళ (fold_p)
	సమాసం.విలువ = c_fully_fold (సమాసం.విలువ, అబద్ధం, ఖాళీ);
      vec_సురక్షిత_నెట్టు (ret, సమాసం.విలువ);
      ఒకవేళ (orig_types)
	vec_సురక్షిత_నెట్టు (orig_types, సమాసం.original_type);
      ఒకవేళ (locations)
	locations->సురక్షిత_నెట్టు (సమాసం.get_location ());
      ఒకవేళ (++idx < 6
	  && sizeof_arg != ఖాళీ
	  && (సమాసం.original_సంకేతం == SIZEOF_సమాసం
	      || సమాసం.original_సంకేతం == PAREN_SIZEOF_సమాసం))
	{
	  sizeof_arg[idx] = c_చివరి_sizeof_arg;
	  sizeof_arg_loc[idx] = c_చివరి_sizeof_loc;
	}
    }
  ఒకవేళ (orig_types)
    *p_orig_types = orig_types;
  c_omp_array_section_p = save_c_omp_array_section_p;
  తిరిగి ret;
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

స్థిర శూన్య
c_parser_objc_class_definition (c_parser *parser, వృక్షం లక్షణాలు)
{
  తార్కిక iface_p;
  వృక్షం id1;
  వృక్షం superclass;
  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = నిజం;
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = అబద్ధం;
  లేకపోతే
    gcc_unreachable ();

  c_parser_consume_token (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      తిరిగి;
    }
  id1 = c_parser_peek_token (parser)->విలువ;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      వృక్షం id2;
      వృక్షం proto = NULL_వృక్షం;
      matching_parens parens;
      parens.consume_open (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
	{
	  ఒకవేళ (iface_p && c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_వృక్షం;
	    }
	  లేకపోతే
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
	      తిరిగి;
	    }
	}
      లేకపోతే
	{
	  id2 = c_parser_peek_token (parser)->విలువ;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_దొరికింది_close (parser);
      ఒకవేళ (!iface_p)
	{
	  objc_ప్రారంభం_category_implementation (id1, id2);
	  తిరిగి;
	}
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_ప్రారంభం_category_interface (id1, id2, proto, లక్షణాలు);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_చివర, "expected %<@end%>");
      objc_ముగింపు_interface ();
      తిరిగి;
    }
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  తిరిగి;
	}
      superclass = c_parser_peek_token (parser)->విలువ;
      c_parser_consume_token (parser);
    }
  లేకపోతే
    superclass = NULL_వృక్షం;
  ఒకవేళ (iface_p)
    {
      వృక్షం proto = NULL_వృక్షం;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_ప్రారంభం_class_interface (id1, loc1, superclass, proto, లక్షణాలు);
    }
  లేకపోతే
    objc_ప్రారంభం_class_implementation (id1, superclass);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  ఒకవేళ (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_చివర, "expected %<@end%>");
      objc_ముగింపు_interface ();
    }
  లేకపోతే
    {
      objc_continue_implementation ();
      తిరిగి;
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

స్థిర శూన్య
c_parser_objc_class_instance_variables (c_parser *parser)
{
  gcc_assert (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_EOF))
    {
      వృక్షం decls;
      /* Parse any stray semicolon.  */
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  కొనసాగు;
	}
      /* Stop if at the end of the instance variables.  */
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  ఆపు;
	}
      /* Parse any objc-visibility-spec.  */
      ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_వ్యక్తిగత))
	{
	  c_parser_consume_token (parser);
	  objc_సమితి_visibility (OBJC_IVAR_VIS_వ్యక్తిగత);
	  కొనసాగు;
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_సమితి_visibility (OBJC_IVAR_VIS_PROTECTED);
	  కొనసాగు;
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_ప్రజా))
	{
	  c_parser_consume_token (parser);
	  objc_సమితి_visibility (OBJC_IVAR_VIS_ప్రజా);
	  కొనసాగు;
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_సమితి_visibility (OBJC_IVAR_VIS_PACKAGE);
	  కొనసాగు;
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, ఖాళీ, NULL_వృక్షం);
	  కొనసాగు;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser, ఖాళీ);
      ఒకవేళ (decls == ఖాళీ)
	{
	  /* There is a syntax error.  We want to skip the offending
	     tokens up to the next ';' (included) or '}'
	     (excluded).  */

	  /* First, skip manually a ')' or ']'.  This is because they
	     reduce the nesting level, so c_parser_skip_until_found()
	     wouldn't be able to skip past them.  */
	  c_token *token = c_parser_peek_token (parser);
	  ఒకవేళ (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_వర్గం)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, ఖాళీ);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = అబద్ధం;
	  కొనసాగు;
	}
      లేకపోతే
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  వృక్షం ivar = nreverse (decls);
	  కొరకు (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_కూడు_instance_variable (copy_కణుపు (ivar));
	}
      c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}

/* Parse an objc-class-declaration.

   objc-class-declaration:
     @class identifier-list ;
*/

స్థిర శూన్య
c_parser_objc_class_declaration (c_parser *parser)
{
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_CLASS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  అయితే (నిజం)
    {
      వృక్షం id;
      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, ఖాళీ);
	  parser->error = అబద్ధం;
	  తిరిగి;
	}
      id = c_parser_peek_token (parser)->విలువ;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      లేకపోతే
	ఆపు;
    }
  c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse an objc-alias-declaration.

   objc-alias-declaration:
     @compatibility_alias identifier identifier ;
*/

స్థిర శూన్య
c_parser_objc_alias_declaration (c_parser *parser)
{
  వృక్షం id1, id2;
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, ఖాళీ);
      తిరిగి;
    }
  id1 = c_parser_peek_token (parser)->విలువ;
  c_parser_consume_token (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, ఖాళీ);
      తిరిగి;
    }
  id2 = c_parser_peek_token (parser)->విలువ;
  c_parser_consume_token (parser);
  c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
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

స్థిర శూన్య
c_parser_objc_protocol_definition (c_parser *parser, వృక్షం లక్షణాలు)
{
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      తిరిగి;
    }
  ఒకవేళ (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      అయితే (నిజం)
	{
	  వృక్షం id;
	  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      ఆపు;
	    }
	  id = c_parser_peek_token (parser)->విలువ;
	  objc_declare_protocol (id, లక్షణాలు);
	  c_parser_consume_token (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  లేకపోతే
	    ఆపు;
	}
      c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  లేకపోతే
    {
      వృక్షం id = c_parser_peek_token (parser)->విలువ;
      వృక్షం proto = NULL_వృక్షం;
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = నిజం;
      objc_ప్రారంభం_protocol (id, proto, లక్షణాలు);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_చివర, "expected %<@end%>");
      parser->objc_pq_context = అబద్ధం;
      objc_ముగింపు_interface ();
    }
}

/* Parse an objc-method-type.

   objc-method-type:
     +
     -

   Return true if it is a class method (+) and false if it is
   an instance method (-).
*/
స్థిర అంతఃవరుస తార్కిక
c_parser_objc_పద్ధతి_type (c_parser *parser)
{
  ఎంపిక (c_parser_peek_token (parser)->type)
    {
    స్థితి CPP_PLUS:
      c_parser_consume_token (parser);
      తిరిగి నిజం;
    స్థితి CPP_MINUS:
      c_parser_consume_token (parser);
      తిరిగి అబద్ధం;
    అప్రమేయ:
      gcc_unreachable ();
    }
}

/* Parse an objc-method-definition.

   objc-method-definition:
     objc-method-type objc-method-decl ;[opt] compound-statement
*/

స్థిర శూన్య
c_parser_objc_పద్ధతి_definition (c_parser *parser)
{
  తార్కిక is_class_పద్ధతి = c_parser_objc_పద్ధతి_type (parser);
  వృక్షం decl, లక్షణాలు = NULL_వృక్షం, సమాసం = NULL_వృక్షం;
  parser->objc_pq_context = నిజం;
  decl = c_parser_objc_పద్ధతి_decl (parser, is_class_పద్ధతి, &లక్షణాలు,
				    &సమాసం);
  ఒకవేళ (decl == error_mark_కణుపు)
    తిరిగి;  /* Bail here. */

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      తిరిగి;
    }

  parser->objc_pq_context = అబద్ధం;
  ఒకవేళ (objc_ప్రారంభం_పద్ధతి_definition (is_class_పద్ధతి, decl, లక్షణాలు, సమాసం))
    {
      కూడు_stmt (c_parser_compound_statement (parser));
      objc_ముగింపు_పద్ధతి_definition (current_function_decl);
    }
  లేకపోతే
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
ఖాళీలు
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

స్థిర శూన్య
c_parser_objc_methodprotolist (c_parser *parser)
{
  అయితే (నిజం)
    {
      /* The list is terminated by @end.  */
      ఎంపిక (c_parser_peek_token (parser)->type)
	{
	స్థితి CPP_SEMICOLON:
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  ఆపు;
	స్థితి CPP_PLUS:
	స్థితి CPP_MINUS:
	  c_parser_objc_methodproto (parser);
	  ఆపు;
	స్థితి CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external, ఖాళీ, NULL_వృక్షం);
	  ఆపు;
	స్థితి CPP_EOF:
	  తిరిగి;
	అప్రమేయ:
	  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_చివర))
	    తిరిగి;
	  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_సమితి_పద్ధతి_opt (నిజం);
	      c_parser_consume_token (parser);
	    }
	  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_సమితి_పద్ధతి_opt (అబద్ధం);
	      c_parser_consume_token (parser);
	    }
	  లేకపోతే
	    c_parser_declaration_or_fndef (parser, అబద్ధం, అబద్ధం, నిజం,
					   అబద్ధం, నిజం, అబద్ధం);
	  ఆపు;
	}
    }
}

/* Parse an objc-methodproto.

   objc-methodproto:
     objc-method-type objc-method-decl ;
*/

స్థిర శూన్య
c_parser_objc_methodproto (c_parser *parser)
{
  తార్కిక is_class_పద్ధతి = c_parser_objc_పద్ధతి_type (parser);
  వృక్షం decl, లక్షణాలు = NULL_వృక్షం;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = నిజం;
  decl = c_parser_objc_పద్ధతి_decl (parser, is_class_పద్ధతి, &లక్షణాలు,
				    ఖాళీ);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = అబద్ధం;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      తిరిగి;
    }

  ఒకవేళ (decl != error_mark_కణుపు)
    objc_కూడు_పద్ధతి_declaration (is_class_పద్ధతి, decl, లక్షణాలు);

  c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

స్థిర తార్కిక
c_parser_objc_maybe_పద్ధతి_లక్షణాలు (c_parser* parser, వృక్షం* లక్షణాలు)
{
  తార్కిక bad = అబద్ధం;
  ఒకవేళ (*లక్షణాలు)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *లక్షణాలు = NULL_వృక్షం;
      bad = నిజం;
    }

  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_ATTRIBUTE))
    *లక్షణాలు = c_parser_gnu_లక్షణాలు (parser);

  /* If there were no attributes here, just report any earlier error.  */
  ఒకవేళ (*లక్షణాలు == NULL_వృక్షం || bad)
    తిరిగి bad;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON)
      || c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
    తిరిగి bad;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  తిరిగి నిజం;
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
ఖాళీలు
     objc-opt-parms , parameter-declaration

   objc-optellipsis:
ఖాళీలు
     , ...
*/

స్థిర వృక్షం
c_parser_objc_పద్ధతి_decl (c_parser *parser, తార్కిక is_class_పద్ధతి,
			   వృక్షం *లక్షణాలు, వృక్షం *సమాసం)
{
  వృక్షం type = NULL_వృక్షం;
  వృక్షం sel;
  వృక్షం parms = NULL_వృక్షం;
  తార్కిక ellipsis = అబద్ధం;
  తార్కిక attr_err = అబద్ధం;

  *లక్షణాలు = NULL_వృక్షం;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      type = c_parser_objc_type_name (parser);
      parens.skip_until_దొరికింది_close (parser);
    }
  sel = c_parser_objc_selector (parser);
  /* If there is no selector, or a colon follows, we have an
     objc-keyword-selector.  If there is a selector, and a colon does
     not follow, that selector ends the objc-method-decl.  */
  ఒకవేళ (!sel || c_parser_తదుపరి_token_is (parser, CPP_COLON))
    {
      వృక్షం tsel = sel;
      వృక్షం list = NULL_వృక్షం;
      అయితే (నిజం)
	{
	  వృక్షం atype = NULL_వృక్షం, id, keyworddecl;
	  వృక్షం param_attr = NULL_వృక్షం;
	  ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    ఆపు;
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_లక్షణాలు (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      తిరిగి error_mark_కణుపు;
	    }
	  id = c_parser_peek_token (parser)->విలువ;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  ఒకవేళ (!tsel && c_parser_తదుపరి_token_is_not (parser, CPP_COLON))
	    ఆపు;
	}

      attr_err |= c_parser_objc_maybe_పద్ధతి_లక్షణాలు (parser, లక్షణాలు) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_కణుపు (వృక్షం_LIST);
      అయితే (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	{
	  నిర్మాణం c_parm *parm;
	  c_parser_consume_token (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = నిజం;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_పద్ధతి_లక్షణాలు
						(parser, లక్షణాలు) ;
	      ఆపు;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_వృక్షం, అబద్ధం);
	  ఒకవేళ (parm == ఖాళీ)
	    ఆపు;
	  parms = chainon (parms,
			   build_వృక్షం_list (NULL_వృక్షం, grokparm (parm, సమాసం)));
	}
      sel = list;
    }
  లేకపోతే
    attr_err |= c_parser_objc_maybe_పద్ధతి_లక్షణాలు (parser, లక్షణాలు) ;

  ఒకవేళ (sel == ఖాళీ)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      తిరిగి error_mark_కణుపు;
    }

  ఒకవేళ (attr_err)
    తిరిగి error_mark_కణుపు;

  తిరిగి objc_build_పద్ధతి_signature (is_class_పద్ధతి, type, sel, parms, ellipsis);
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

స్థిర వృక్షం
c_parser_objc_type_name (c_parser *parser)
{
  వృక్షం quals = NULL_వృక్షం;
  నిర్మాణం c_type_name *type_name = ఖాళీ;
  వృక్షం type = NULL_వృక్షం;
  అయితే (నిజం)
    {
      c_token *token = c_parser_peek_token (parser);
      ఒకవేళ (token->type == CPP_KEYWORD
	  && (token->keyword == RID_లోపల
	      || token->keyword == RID_బహిర్గతం
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_వృక్షం_list (NULL_వృక్షం, token->విలువ), quals);
	  c_parser_consume_token (parser);
	}
      లేకపోతే
	ఆపు;
    }
  ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  ఒకవేళ (type_name)
    type = groktypename (type_name, ఖాళీ, ఖాళీ);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  ఒకవేళ (type == error_mark_కణుపు)
    type = NULL_వృక్షం;

  తిరిగి build_వృక్షం_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

స్థిర వృక్షం
c_parser_objc_protocol_refs (c_parser *parser)
{
  వృక్షం list = NULL_వృక్షం;
  gcc_assert (c_parser_తదుపరి_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  అయితే (నిజం)
    {
      వృక్షం id;
      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  ఆపు;
	}
      id = c_parser_peek_token (parser)->విలువ;
      list = chainon (list, build_వృక్షం_list (NULL_వృక్షం, id));
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      లేకపోతే
	ఆపు;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  తిరిగి list;
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

స్థిర శూన్య
c_parser_objc_try_catch_finally_statement (c_parser *parser)
{
  location_t location;
  వృక్షం stmt;

  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  అయితే (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_CATCH))
    {
      నిర్మాణం c_parm *parm;
      వృక్షం parameter_declaration = error_mark_కణుపు;
      తార్కిక చూసిన_open_paren = అబద్ధం;

      c_parser_consume_token (parser);
      matching_parens parens;
      ఒకవేళ (!parens.require_open (parser))
	చూసిన_open_paren = నిజం;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_వృక్షం;
	}
      లేకపోతే
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_వృక్షం, అబద్ధం);
	  ఒకవేళ (parm == ఖాళీ)
	    parameter_declaration = error_mark_కణుపు;
	  లేకపోతే
	    parameter_declaration = grokparm (parm, ఖాళీ);
	}
      ఒకవేళ (చూసిన_open_paren)
	parens.require_close (parser);
      లేకపోతే
	{
	  /* If there was no open parenthesis, we are recovering from
	     an error, and we are trying to figure out what mistake
	     the user has made.  */

	  /* If there is an immediate closing parenthesis, the user
	     probably forgot the opening one (ie, they typed "@catch
	     NSException *e)".  Parse the closing parenthesis and keep
	     going.  */
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      ఒకవేళ (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_ముగింపు_catch_clause ();
    }
  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_FINALLY))
    {
      c_parser_consume_token (parser);
      location = c_parser_peek_token (parser)->location;
      stmt = c_parser_compound_statement (parser);
      objc_build_finally_clause (location, stmt);
    }
  objc_ముగింపు_try_stmt ();
}

/* Parse an objc-synchronized-statement.

   objc-synchronized-statement:
     @synchronized ( expression ) compound-statement
*/

స్థిర శూన్య
c_parser_objc_synchronized_statement (c_parser *parser)
{
  location_t loc;
  వృక్షం సమాసం, stmt;
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      నిర్మాణం c_సమాసం ce = c_parser_వ్యక్తీకరణ (parser);
      ce = convert_lvalue_గమ్యం_rvalue (loc, ce, అబద్ధం, అబద్ధం);
      సమాసం = ce.విలువ;
      సమాసం = c_fully_fold (సమాసం, అబద్ధం, ఖాళీ);
      parens.skip_until_దొరికింది_close (parser);
    }
  లేకపోతే
    సమాసం = error_mark_కణుపు;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, సమాసం, stmt);
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

స్థిర వృక్షం
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  వృక్షం విలువ = token->విలువ;
  ఒకవేళ (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      తిరిగి విలువ;
    }
  ఒకవేళ (token->type != CPP_KEYWORD)
    తిరిగి NULL_వృక్షం;
  ఎంపిక (token->keyword)
    {
    స్థితి RID_ENUM:
    స్థితి RID_STRUCT:
    స్థితి RID_UNION:
    స్థితి RID_IF:
    స్థితి RID_ELSE:
    స్థితి RID_WHILE:
    స్థితి RID_DO:
    స్థితి RID_FOR:
    స్థితి RID_SWITCH:
    స్థితి RID_CASE:
    స్థితి RID_DEFAULT:
    స్థితి RID_BREAK:
    స్థితి RID_CONTINUE:
    స్థితి RID_RETURN:
    స్థితి RID_GOTO:
    స్థితి RID_ASM:
    స్థితి RID_SIZEOF:
    స్థితి RID_TYPEOF:
    స్థితి RID_TYPEOF_UNQUAL:
    స్థితి RID_ALIGNOF:
    స్థితి RID_UNSIGNED:
    స్థితి RID_LONG:
    స్థితి RID_CONST:
    స్థితి RID_SHORT:
    స్థితి RID_VOLATILE:
    స్థితి RID_SIGNED:
    స్థితి RID_RESTRICT:
    స్థితి RID_COMPLEX:
    స్థితి RID_లోపల:
    స్థితి RID_బహిర్గతం:
    స్థితి RID_INOUT:
    స్థితి RID_BYCOPY:
    స్థితి RID_BYREF:
    స్థితి RID_ONEWAY:
    స్థితి RID_INT:
    స్థితి RID_CHAR:
    స్థితి RID_FLOAT:
    స్థితి RID_DOUBLE:
    CASE_RID_FLOATN_NX:
    స్థితి RID_VOID:
    స్థితి RID_BOOL:
    స్థితి RID_ATOMIC:
    స్థితి RID_AUTO_TYPE:
    స్థితి RID_INT_N_0:
    స్థితి RID_INT_N_1:
    స్థితి RID_INT_N_2:
    స్థితి RID_INT_N_3:
      c_parser_consume_token (parser);
      తిరిగి విలువ;
    అప్రమేయ:
      తిరిగి NULL_వృక్షం;
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

స్థిర వృక్షం
c_parser_objc_selector_arg (c_parser *parser)
{
  వృక్షం sel = c_parser_objc_selector (parser);
  వృక్షం list = NULL_వృక్షం;
  ఒకవేళ (sel
      && c_parser_తదుపరి_token_is_not (parser, CPP_COLON)
      && c_parser_తదుపరి_token_is_not (parser, CPP_SCOPE))
    తిరిగి sel;
  అయితే (నిజం)
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_వృక్షం_list (sel, NULL_వృక్షం));
	  list = chainon (list, build_వృక్షం_list (NULL_వృక్షం, NULL_వృక్షం));
	}
      లేకపోతే
	{
	  ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    తిరిగి list;
	  list = chainon (list, build_వృక్షం_list (sel, NULL_వృక్షం));
	}
      sel = c_parser_objc_selector (parser);
      ఒకవేళ (!sel
	  && c_parser_తదుపరి_token_is_not (parser, CPP_COLON)
	  && c_parser_తదుపరి_token_is_not (parser, CPP_SCOPE))
	ఆపు;
    }
  తిరిగి list;
}

/* Parse an objc-receiver.

   objc-receiver:
వ్యక్తీకరణ
     class-name
     type-name
*/

స్థిర వృక్షం
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  ఒకవేళ (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_రకం == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_రకం == C_ID_CLASSNAME))
    {
      వృక్షం id = c_parser_peek_token (parser)->విలువ;
      c_parser_consume_token (parser);
      తిరిగి objc_get_class_reference (id);
    }
  నిర్మాణం c_సమాసం ce = c_parser_వ్యక్తీకరణ (parser);
  ce = convert_lvalue_గమ్యం_rvalue (loc, ce, అబద్ధం, అబద్ధం);
  తిరిగి c_fully_fold (ce.విలువ, అబద్ధం, ఖాళీ);
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

స్థిర వృక్షం
c_parser_objc_సందేశం_వాదనలు (c_parser *parser)
{
  వృక్షం sel = c_parser_objc_selector (parser);
  వృక్షం list = NULL_వృక్షం;
  ఒకవేళ (sel && c_parser_తదుపరి_token_is_not (parser, CPP_COLON))
    తిరిగి sel;
  అయితే (నిజం)
    {
      వృక్షం keywordexpr;
      ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	తిరిగి error_mark_కణుపు;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_వృక్షం_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      ఒకవేళ (!sel && c_parser_తదుపరి_token_is_not (parser, CPP_COLON))
	ఆపు;
    }
  తిరిగి list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

స్థిర వృక్షం
c_parser_objc_keywordexpr (c_parser *parser)
{
  వృక్షం ret;
  vec<వృక్షం, va_gc> *సమాసం_list = c_parser_సమాసం_list (parser, నిజం, నిజం,
						ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ);
  ఒకవేళ (vec_సురక్షిత_నిడివి (సమాసం_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*సమాసం_list)[0];
    }
  లేకపోతే
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_వృక్షం_list_vec (సమాసం_list);
    }
  release_వృక్షం_సదిశ (సమాసం_list);
  తిరిగి ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
స్థిర తార్కిక
c_parser_objc_diagnose_bad_element_ఉపసర్గ (c_parser *parser,
					   నిర్మాణం c_declspecs *specs)
{
  ఒకవేళ (!specs->declspecs_చూసిన_p || specs->non_sc_చూసిన_p
      || specs->typespec_రకం != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
      తిరిగి నిజం;
    }
  తిరిగి అబద్ధం;
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
స్థిర శూన్య
c_parser_objc_at_property_declaration (c_parser *parser)
{
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_PROPERTY));
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);  /* Eat '@property'.  */

  /* Parse the optional attribute list.

     A list of parsed, but not verified, attributes.  */
  vec<property_attribute_info *> prop_attr_list = vNULL;

  తార్కిక syntax_error = అబద్ధం;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_ప్రారంభం = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = నిజం;

      /* Allow @property (), with a warning.  */
      location_t attr_చివర = c_parser_peek_token (parser)->location;

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_చివర, attr_ప్రారంభం, attr_చివర);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      లేకపోతే
	అయితే (నిజం)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_ప్రారంభం = token->location;
	    attr_చివర = get_ముగింపు (token->location);
	    location_t attr_comb = make_location (attr_ప్రారంభం, attr_ప్రారంభం,
						  attr_చివర);

	    ఒకవేళ (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		ఒకవేళ (token->type == CPP_CLOSE_PAREN)
		  ఆపు;
		c_parser_consume_token (parser);
		కొనసాగు;
	      }

	    వృక్షం attr_name = NULL_వృక్షం;
	    గణన rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    తార్కిక కూడు_at = అబద్ధం;
	    ఒకవేళ (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		ఒకవేళ (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->విలువ;
		    కూడు_at = నిజం;
		  }
		లేకపోతే
		  attr_name = ridpointers[(పూర్ణాంకం)keyword];
	      }
	    లేకపోతే ఒకవేళ (token->type == CPP_NAME)
	      attr_name = token->విలువ;
	    c_parser_consume_token (parser);

	    గణన objc_property_attribute_రకం prop_రకం
	      = objc_prop_attr_రకం_for_rid (keyword);
	    property_attribute_info *prop
	      = కొత్త property_attribute_info (attr_name, attr_comb, prop_రకం);
	    prop_attr_list.సురక్షిత_నెట్టు (prop);

	    వృక్షం meth_name;
	    ఎంపిక (prop->prop_రకం)
	      {
	      అప్రమేయ: ఆపు;
	      స్థితి OBJC_PROPERTY_ATTR_UNKNOWN:
		ఒకవేళ (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    కూడు_at ? "@" : "", IDENTIFIER_సూచిక (attr_name));
		లేకపోతే
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = నిజం;
		ఆపు;

	      స్థితి OBJC_PROPERTY_ATTR_GETTER:
	      స్థితి OBJC_PROPERTY_ATTR_SETTER:
		ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_చివర, attr_ప్రారంభం, attr_చివర);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = నిజం;
		    ఆపు;
		  }
		token = c_parser_peek_token (parser);
		attr_చివర = token->location;
		c_parser_consume_token (parser); /* eat the = */
		ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_చివర, attr_ప్రారంభం, attr_చివర);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = నిజం;
		    ఆపు;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_చివర = get_ముగింపు (token->location);
		meth_name = token->విలువ;
		c_parser_consume_token (parser);
		ఒకవేళ (prop->prop_రకం == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_చివర, attr_ప్రారంభం,
						   attr_చివర);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = నిజం;
		      }
		    లేకపోతే
		      {
			attr_చివర = get_ముగింపు (c_parser_peek_token
					       (parser)->location);
			c_parser_consume_token (parser);
		      }
		    attr_comb = make_location (attr_ప్రారంభం, attr_ప్రారంభం,
					       attr_చివర);
		  }
		లేకపోతే
		  attr_comb = make_location (attr_ప్రారంభం, attr_ప్రారంభం,
					       attr_చివర);
		prop->ident = meth_name;
		/* Updated location including all that was successfully
		   parsed.  */
		prop->prop_loc = attr_comb;
		ఆపు;
	    }

	  /* If we see a comma here, then keep going - even if we already
	     saw a syntax error.  For simple mistakes e.g. (assign, getter=x)
	     this makes a more useful output and avoid spurious warnings about
	     missing attributes that are, in fact, specified after the one with
	     the syntax error.  */
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  లేకపోతే
	    ఆపు;
	}
      parser->objc_property_attr_context = అబద్ధం;

      ఒకవేళ (syntax_error && c_parser_తదుపరి_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      లేకపోతే
	syntax_error = అబద్ధం, parens.skip_until_దొరికింది_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  వృక్షం properties = c_parser_struct_declaration (parser, ఖాళీ);

  ఒకవేళ (properties == error_mark_కణుపు)
    c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, ఖాళీ);
  లేకపోతే
    {
      ఒకవేళ (properties == NULL_వృక్షం)
	c_parser_error (parser, "expected identifier");
      లేకపోతే
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  కొరకు (; properties; properties = వృక్షం_CHAIN (properties))
	    objc_కూడు_property_declaration (loc, copy_కణుపు (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  అయితే (!prop_attr_list.is_ఖాళీలు())
    తొలగించు prop_attr_list.తీయి ();
  prop_attr_list.release ();
  parser->error = అబద్ధం;
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
స్థిర శూన్య
c_parser_objc_at_synthesize_declaration (c_parser *parser)
{
  వృక్షం list = NULL_వృక్షం;
  location_t loc;
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  అయితే (నిజం)
    {
      వృక్షం property, ivar;
      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, ఖాళీ);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = అబద్ధం;
	  తిరిగి;
	}
      property = c_parser_peek_token (parser)->విలువ;
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, ఖాళీ);
	      parser->error = అబద్ధం;
	      తిరిగి;
	    }
	  ivar = c_parser_peek_token (parser)->విలువ;
	  c_parser_consume_token (parser);
	}
      లేకపోతే
	ivar = NULL_వృక్షం;
      list = chainon (list, build_వృక్షం_list (ivar, property));
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      లేకపోతే
	ఆపు;
    }
  c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_కూడు_synthesize_declaration (loc, list);
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
స్థిర శూన్య
c_parser_objc_at_dynamic_declaration (c_parser *parser)
{
  వృక్షం list = NULL_వృక్షం;
  location_t loc;
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  అయితే (నిజం)
    {
      వృక్షం property;
      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, ఖాళీ);
	  parser->error = అబద్ధం;
	  తిరిగి;
	}
      property = c_parser_peek_token (parser)->విలువ;
      list = chainon (list, build_వృక్షం_list (NULL_వృక్షం, property));
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      లేకపోతే
	ఆపు;
    }
  c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_కూడు_dynamic_declaration (loc, list);
}


/* Parse a pragma GCC ivdep.  */

స్థిర తార్కిక
c_parse_pragma_ivdep (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_గమ్యం_pragma_eol (parser);
  తిరిగి నిజం;
}

/* Parse a pragma GCC novector.  */

స్థిర తార్కిక
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_గమ్యం_pragma_eol (parser);
  తిరిగి నిజం;
}

/* Parse a pragma GCC unroll.  */

స్థిర గుర్తులేని పొట్టి
c_parser_pragma_unroll (c_parser *parser)
{
  గుర్తులేని పొట్టి unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  వృక్షం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ).విలువ;
  mark_exp_read (సమాసం);
  సమాసం = c_fully_fold (సమాసం, అబద్ధం, ఖాళీ);
  HOST_WIDE_INT lunroll = 0;
  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (సమాసం))
      || వృక్షం_సంకేతం (సమాసం) != INTEGER_CST
      || (lunroll = వృక్షం_గమ్యం_shwi (సమాసం)) < 0
      || lunroll >= USHRT_MAX)
    {
      error_at (location, "%<#pragma GCC unroll%> requires an"
		" assignment-expression that evaluates to a non-negative"
		" integral constant less than %u", USHRT_MAX);
      unroll = 0;
    }
  లేకపోతే
    {
      unroll = (గుర్తులేని పొట్టి)lunroll;
      ఒకవేళ (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_గమ్యం_pragma_eol (parser);
  తిరిగి unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

స్థిర తార్కిక
c_parser_pragma (c_parser *parser, గణన pragma_context context, తార్కిక *if_p,
		 వృక్షం before_labels)
{
  గుర్తులేని పూర్ణాంకం id;
  స్థిరరాశి అక్షరం *construct = ఖాళీ;

  ఆదానం_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_రకం;
  gcc_assert (id != PRAGMA_NONE);
  ఒకవేళ (parser->omp_for_parse_state
      && parser->omp_for_parse_state->లోపల_intervening_సంకేతం
      && id >= PRAGMA_OMP_ప్రారంభం && id <= PRAGMA_OMP_చివరి
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	ఆదానం_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->fail = నిజం;
      c_parser_skip_until_దొరికింది (parser, CPP_PRAGMA_EOL, ఖాళీ);
      తిరిగి అబద్ధం;
    }

  ఎంపిక (id)
    {
    స్థితి PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OACC_ENTER_దత్తాంశం:
      ఒకవేళ (context != pragma_compound)
	{
	  construct = "acc enter data";
	లోపల_compound:
	  ఒకవేళ (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_దొరికింది (parser, CPP_PRAGMA_EOL, ఖాళీ);
	      తిరిగి నిజం;
	    }
	  వెళ్ళు bad_stmt;
	}
      c_parser_oacc_enter_exit_దత్తాంశం (parser, నిజం);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OACC_EXIT_దత్తాంశం:
      ఒకవేళ (context != pragma_compound)
	{
	  construct = "acc exit data";
	  వెళ్ళు లోపల_compound;
	}
      c_parser_oacc_enter_exit_దత్తాంశం (parser, అబద్ధం);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OACC_ROUTINE:
      ఒకవేళ (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_దొరికింది (parser, CPP_PRAGMA_EOL, ఖాళీ);
	  తిరిగి అబద్ధం;
	}
      c_parser_oacc_routine (parser, context);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OACC_UPDATE:
      ఒకవేళ (context != pragma_compound)
	{
	  construct = "acc update";
	  వెళ్ళు లోపల_compound;
	}
      c_parser_oacc_update (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_BARRIER:
      ఒకవేళ (context != pragma_compound)
	{
	  construct = "omp barrier";
	  వెళ్ళు లోపల_compound;
	}
      c_parser_omp_barrier (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_DEPOBJ:
      ఒకవేళ (context != pragma_compound)
	{
	  construct = "omp depobj";
	  వెళ్ళు లోపల_compound;
	}
      c_parser_omp_depobj (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_FLUSH:
      ఒకవేళ (context != pragma_compound)
	{
	  construct = "omp flush";
	  వెళ్ళు లోపల_compound;
	}
      c_parser_omp_flush (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_INTEROP:
      ఒకవేళ (context != pragma_compound)
	{
	  construct = "omp interop";
	  వెళ్ళు లోపల_compound;
	}
      c_parser_omp_interop (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_TASKWAIT:
      ఒకవేళ (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  వెళ్ళు లోపల_compound;
	}
      c_parser_omp_taskwait (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_TASKYIELD:
      ఒకవేళ (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  వెళ్ళు లోపల_compound;
	}
      c_parser_omp_taskyield (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_CANCEL:
      ఒకవేళ (context != pragma_compound)
	{
	  construct = "omp cancel";
	  వెళ్ళు లోపల_compound;
	}
      c_parser_omp_cancel (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_CANCELLATION_బిందువు:
      తిరిగి c_parser_omp_cancellation_బిందువు (parser, context);

    స్థితి PRAGMA_OMP_GROUPPRIVATE:
      c_parser_omp_groupprivate (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_THREADPRIVATE:
      c_parser_omp_threadprivate (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_లక్ష్యం:
      తిరిగి c_parser_omp_లక్ష్యం (parser, context, if_p);

    స్థితి PRAGMA_OMP_BEGIN:
      c_parser_omp_begin (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_చివర:
      c_parser_omp_చివర (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_పరిశీలన:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_దొరికింది (parser, CPP_PRAGMA_EOL, ఖాళీ);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_దొరికింది (parser, CPP_PRAGMA_EOL, ఖాళీ);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_DECLARE:
      తిరిగి c_parser_omp_declare (parser, context);

    స్థితి PRAGMA_OMP_REQUIRES:
      ఒకవేళ (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_దొరికింది (parser, CPP_PRAGMA_EOL, ఖాళీ);
	  తిరిగి అబద్ధం;
	}
      c_parser_omp_requires (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_ALLOCATE:
      c_parser_omp_allocate (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_ASSUMES:
      ఒకవేళ (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp assumes");
	  c_parser_skip_until_దొరికింది (parser, CPP_PRAGMA_EOL, ఖాళీ);
	  తిరిగి అబద్ధం;
	}
      c_parser_omp_assumes (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      తిరిగి నిజం;

    స్థితి PRAGMA_OMP_ERROR:
      తిరిగి c_parser_omp_error (parser, context);

    స్థితి PRAGMA_OMP_ORDERED:
      తిరిగి c_parser_omp_ordered (parser, context, if_p);

    స్థితి PRAGMA_NOVECTOR:
    స్థితి PRAGMA_UNROLL:
    స్థితి PRAGMA_IVDEP:
      {
	తార్కిక novector = అబద్ధం;
	గుర్తులేని పొట్టి unroll = 0;
	తార్కిక ivdep = అబద్ధం;

	ఎంపిక (id)
	  {
	  స్థితి PRAGMA_NOVECTOR:
	    novector = c_parse_pragma_novector (parser);
	    ఆపు;
	  స్థితి PRAGMA_UNROLL:
	    unroll = c_parser_pragma_unroll (parser);
	    ఆపు;
	  స్థితి PRAGMA_IVDEP:
	    ivdep = c_parse_pragma_ivdep (parser);
	    ఆపు;
	  అప్రమేయ:
	    gcc_unreachable ();
	  }

	c_token *tok = c_parser_peek_token (parser);
	తార్కిక has_మరిన్ని = tok->type == CPP_PRAGMA;
	అయితే (has_మరిన్ని)
	  {
	    ఎంపిక (tok->pragma_రకం)
	      {
	      స్థితి PRAGMA_IVDEP:
		ivdep = c_parse_pragma_ivdep (parser);
		ఆపు;
	      స్థితి PRAGMA_UNROLL:
		unroll = c_parser_pragma_unroll (parser);
		ఆపు;
	      స్థితి PRAGMA_NOVECTOR:
		novector = c_parse_pragma_novector (parser);
		ఆపు;
	      అప్రమేయ:
		has_మరిన్ని = అబద్ధం;
		ఆపు;
	      }
	    tok = c_parser_peek_token (parser);
	    has_మరిన్ని = has_మరిన్ని && tok->type == CPP_PRAGMA;
	  }
	ఒకవేళ (!c_parser_తదుపరి_token_is_keyword (parser, RID_FOR)
	    && !c_parser_తదుపరి_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_తదుపరి_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    తిరిగి అబద్ధం;
	  }
	ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	లేకపోతే
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      తిరిగి నిజం;

    స్థితి PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_దొరికింది (parser, CPP_PRAGMA_EOL, ఖాళీ);
      తిరిగి అబద్ధం;

    స్థితి PRAGMA_OACC_WAIT:
      ఒకవేళ (context != pragma_compound)
	{
	  construct = "acc wait";
	  వెళ్ళు లోపల_compound;
	}
	/* FALL THROUGH.  */

    అప్రమేయ:
      ఒకవేళ (id < PRAGMA_మొదటి_EXTERNAL)
	{
	  ఒకవేళ (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_దొరికింది (parser, CPP_PRAGMA_EOL, ఖాళీ);
	      తిరిగి అబద్ధం;
	    }
	  c_parser_omp_construct (parser, if_p);
	  తిరిగి నిజం;
	}
      ఆపు;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = నిజం;
  c_parser_skip_గమ్యం_pragma_eol (parser);

  తిరిగి అబద్ధం;
}

/* The interface the pragma parsers have to the lexer.  */

గణన cpp_ttype
pragma_lex (వృక్షం *విలువ, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  గణన cpp_ttype ret = tok->type;

  *విలువ = tok->విలువ;
  ఒకవేళ (loc)
    *loc = tok->location;

  ఒకవేళ (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  లేకపోతే ఒకవేళ (ret == CPP_STRING)
    *విలువ = c_parser_string_literal (the_parser, అబద్ధం, అబద్ధం).విలువ;
  లేకపోతే
    {
      ఒకవేళ (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  తిరిగి ret;
}

శూన్య
pragma_lex_discard_గమ్యం_eol ()
{
  cpp_ttype type;
  చేయి
    {
      type = c_parser_peek_token (the_parser)->type;
      gcc_assert (type != CPP_EOF);
      c_parser_consume_token (the_parser);
    } అయితే (type != CPP_PRAGMA_EOL);
}

స్థిర శూన్య
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  వృక్షం name = ఖాళీ;

  parser->lex_joined_string = నిజం;
  c_parser_consume_pragma (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->విలువ;
      c_parser_consume_token (parser);
    }
  లేకపోతే
    c_parser_error (parser, "expected string literal");
  c_parser_skip_గమ్యం_pragma_eol (parser);
  parser->lex_joined_string = అబద్ధం;

  ఒకవేళ (name)
    c_common_pch_pragma (parse_లోపల, వృక్షం_STRING_సూచిక (name));
}

/* OpenACC and OpenMP parsing routines.  */

/* Returns name of the next clause.
   If the clause is not recognized PRAGMA_OMP_CLAUSE_NONE is returned and
   the token is not consumed.  Otherwise appropriate pragma_omp_clause is
   returned and the token is consumed.  */

స్థిర pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause ఫలితం = PRAGMA_OMP_CLAUSE_NONE;

  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_AUTO))
    ఫలితం = PRAGMA_OACC_CLAUSE_AUTO;
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_IF))
    ఫలితం = PRAGMA_OMP_CLAUSE_IF;
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_DEFAULT))
    ఫలితం = PRAGMA_OMP_CLAUSE_DEFAULT;
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_FOR))
    ఫలితం = PRAGMA_OMP_CLAUSE_FOR;
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);

      ఎంపిక (p[0])
	{
	స్థితి 'a':
	  ఒకవేళ (!strcmp ("affinity", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_AFFINITY;
	  లేకపోతే ఒకవేళ (!strcmp ("aligned", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_ALIGNED;
	  లేకపోతే ఒకవేళ (!strcmp ("allocate", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  లేకపోతే ఒకవేళ (!strcmp ("async", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_ASYNC;
	  లేకపోతే ఒకవేళ (!strcmp ("attach", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_ATTACH;
	  ఆపు;
	స్థితి 'b':
	  ఒకవేళ (!strcmp ("bind", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_BIND;
	  ఆపు;
	స్థితి 'c':
	  ఒకవేళ (!strcmp ("collapse", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  లేకపోతే ఒకవేళ (!strcmp ("copy", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_COPY;
	  లేకపోతే ఒకవేళ (!strcmp ("copyin", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_COPYIN;
	  లేకపోతే ఒకవేళ (!strcmp ("copyout", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_COPYOUT;
          లేకపోతే ఒకవేళ (!strcmp ("copyprivate", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  లేకపోతే ఒకవేళ (!strcmp ("create", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_CREATE;
	  ఆపు;
	స్థితి 'd':
	  ఒకవేళ (!strcmp ("defaultmap", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  లేకపోతే ఒకవేళ (!strcmp ("delete", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_DELETE;
	  లేకపోతే ఒకవేళ (!strcmp ("depend", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_DEPEND;
	  లేకపోతే ఒకవేళ (!strcmp ("destroy", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_DESTROY;
	  లేకపోతే ఒకవేళ (!strcmp ("detach", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_DETACH;
	  లేకపోతే ఒకవేళ (!strcmp ("device", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_DEVICE;
	  లేకపోతే ఒకవేళ (!strcmp ("deviceptr", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  లేకపోతే ఒకవేళ (!strcmp ("device_resident", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  లేకపోతే ఒకవేళ (!strcmp ("device_type", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  లేకపోతే ఒకవేళ (!strcmp ("dist_schedule", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_DIST_కాలపట్టిక;
	  లేకపోతే ఒకవేళ (!strcmp ("doacross", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_DOACROSS;
	  లేకపోతే ఒకవేళ (!strcmp ("dyn_groupprivate", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  ఆపు;
	స్థితి 'e':
	  ఒకవేళ (!strcmp ("enter", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_ENTER;
	  ఆపు;
	స్థితి 'f':
	  ఒకవేళ (!strcmp ("filter", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_FILTER;
	  లేకపోతే ఒకవేళ (!strcmp ("final", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_FINAL;
	  లేకపోతే ఒకవేళ (!strcmp ("finalize", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_FINALIZE;
	  లేకపోతే ఒకవేళ (!strcmp ("firstprivate", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  లేకపోతే ఒకవేళ (!strcmp ("from", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_FROM;
	  లేకపోతే ఒకవేళ (!strcmp ("full", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_నిండిన;
	  ఆపు;
	స్థితి 'g':
	  ఒకవేళ (!strcmp ("gang", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_GANG;
	  లేకపోతే ఒకవేళ (!strcmp ("grainsize", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  ఆపు;
	స్థితి 'h':
	  ఒకవేళ (!strcmp ("has_device_addr", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  లేకపోతే ఒకవేళ (!strcmp ("hint", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_HINT;
	  లేకపోతే ఒకవేళ (!strcmp ("host", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_HOST;
	  ఆపు;
	స్థితి 'i':
	  ఒకవేళ (!strcmp ("if_present", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  లేకపోతే ఒకవేళ (!strcmp ("in_reduction", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_లోపల_REDUCTION;
	  లేకపోతే ఒకవేళ (!strcmp ("inbranch", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_INBRANCH;
	  లేకపోతే ఒకవేళ (!strcmp ("independent", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  లేకపోతే ఒకవేళ (!strcmp ("indirect", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_పరోక్ష;
	  లేకపోతే ఒకవేళ (!strcmp ("init", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_INIT;
	  లేకపోతే ఒకవేళ (!strcmp ("is_device_ptr", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  లేకపోతే ఒకవేళ (!strcmp ("interop", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_INTEROP;
	  ఆపు;
	స్థితి 'l':
	  ఒకవేళ (!strcmp ("lastprivate", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  లేకపోతే ఒకవేళ (!strcmp ("linear", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_రేఖీయ;
	  లేకపోతే ఒకవేళ (!strcmp ("link", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_LINK;
	  లేకపోతే ఒకవేళ (!strcmp ("local", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_LOCAL;
	  ఆపు;
	స్థితి 'm':
	  ఒకవేళ (!strcmp ("map", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_MAP;
	  లేకపోతే ఒకవేళ (!strcmp ("mergeable", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  ఆపు;
	స్థితి 'n':
	  ఒకవేళ (!strcmp ("no_create", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  లేకపోతే ఒకవేళ (!strcmp ("nocontext", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  లేకపోతే ఒకవేళ (!strcmp ("nogroup", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_NOGROUP;
	  లేకపోతే ఒకవేళ (!strcmp ("nohost", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_NOHOST;
	  లేకపోతే ఒకవేళ (!strcmp ("nontemporal", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  లేకపోతే ఒకవేళ (!strcmp ("notinbranch", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  లేకపోతే ఒకవేళ (!strcmp ("novariants", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  లేకపోతే ఒకవేళ (!strcmp ("nowait", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_NOWAIT;
	  లేకపోతే ఒకవేళ (!strcmp ("num_gangs", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_అంకె_GANGS;
	  లేకపోతే ఒకవేళ (!strcmp ("num_tasks", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_అంకె_TASKS;
	  లేకపోతే ఒకవేళ (!strcmp ("num_teams", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_అంకె_TEAMS;
	  లేకపోతే ఒకవేళ (!strcmp ("num_threads", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_అంకె_దారాలు;
	  లేకపోతే ఒకవేళ (!strcmp ("num_workers", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_అంకె_WORKERS;
	  ఆపు;
	స్థితి 'o':
	  ఒకవేళ (!strcmp ("ordered", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_ORDERED;
	  లేకపోతే ఒకవేళ (!strcmp ("order", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_క్రమం;
	  ఆపు;
	స్థితి 'p':
	  ఒకవేళ (!strcmp ("parallel", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_PARALLEL;
	  లేకపోతే ఒకవేళ (!strcmp ("partial", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_PARTIAL;
	  లేకపోతే ఒకవేళ (!strcmp ("present", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  లేకపోతే ఒకవేళ (!strcmp ("present_or_copy", p)
		   || !strcmp ("pcopy", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_COPY;
	  లేకపోతే ఒకవేళ (!strcmp ("present_or_copyin", p)
		   || !strcmp ("pcopyin", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_COPYIN;
	  లేకపోతే ఒకవేళ (!strcmp ("present_or_copyout", p)
		   || !strcmp ("pcopyout", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_COPYOUT;
	  లేకపోతే ఒకవేళ (!strcmp ("present_or_create", p)
		   || !strcmp ("pcreate", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_CREATE;
	  లేకపోతే ఒకవేళ (!strcmp ("priority", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_ప్రాధాన్యత;
	  లేకపోతే ఒకవేళ (!strcmp ("private", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_వ్యక్తిగత;
	  లేకపోతే ఒకవేళ (!strcmp ("proc_bind", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  ఆపు;
	స్థితి 'r':
	  ఒకవేళ (!strcmp ("reduction", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_REDUCTION;
	  ఆపు;
	స్థితి 's':
	  ఒకవేళ (!strcmp ("safelen", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_SAFELEN;
	  లేకపోతే ఒకవేళ (!strcmp ("schedule", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_కాలపట్టిక;
	  లేకపోతే ఒకవేళ (!strcmp ("sections", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_SECTIONS;
	  లేకపోతే ఒకవేళ (!strcmp ("self", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_SELF;
	  లేకపోతే ఒకవేళ (!strcmp ("seq", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_SEQ;
	  లేకపోతే ఒకవేళ (!strcmp ("shared", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_SHARED;
	  లేకపోతే ఒకవేళ (!strcmp ("simd", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_SIMD;
	  లేకపోతే ఒకవేళ (!strcmp ("simdlen", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  ఆపు;
	స్థితి 't':
	  ఒకవేళ (!strcmp ("task_reduction", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  లేకపోతే ఒకవేళ (!strcmp ("taskgroup", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  లేకపోతే ఒకవేళ (!strcmp ("thread_limit", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_THREAD_హద్దు;
	  లేకపోతే ఒకవేళ (!strcmp ("threads", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_దారాలు;
	  లేకపోతే ఒకవేళ (!strcmp ("tile", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_TILE;
	  లేకపోతే ఒకవేళ (!strcmp ("to", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_గమ్యం;
	  ఆపు;
	స్థితి 'u':
	  ఒకవేళ (!strcmp ("uniform", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_ఏకరీతి;
	  లేకపోతే ఒకవేళ (!strcmp ("untied", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_UNTIED;
	  లేకపోతే ఒకవేళ (!strcmp ("use", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_USE;
	  లేకపోతే ఒకవేళ (!strcmp ("use_device", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  లేకపోతే ఒకవేళ (!strcmp ("use_device_addr", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  లేకపోతే ఒకవేళ (!strcmp ("use_device_ptr", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  లేకపోతే ఒకవేళ (!strcmp ("uses_allocators", p))
	    ఫలితం = PRAGMA_OMP_CLAUSE_ఉపయోగిస్తుంది_ALLOCATORS;
	  ఆపు;
	స్థితి 'v':
	  ఒకవేళ (!strcmp ("vector", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_సదిశ;
	  లేకపోతే ఒకవేళ (!strcmp ("vector_length", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_సదిశ_నిడివి;
	  ఆపు;
	స్థితి 'w':
	  ఒకవేళ (!strcmp ("wait", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_WAIT;
	  లేకపోతే ఒకవేళ (!strcmp ("worker", p))
	    ఫలితం = PRAGMA_OACC_CLAUSE_కార్మికుడు;
	  ఆపు;
	}
    }

  ఒకవేళ (ఫలితం != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  తిరిగి ఫలితం;
}

/* Validate that a clause of the given type does not already exist.  */

స్థిర శూన్య
check_no_duplicate_clause (వృక్షం clauses, గణన omp_clause_సంకేతం సంకేతం_2,
			   స్థిరరాశి అక్షరం *name)
{
  ఒకవేళ (వృక్షం c = omp_కనుగొను_clause (clauses, సంకేతం_2))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

స్థిర వృక్షం
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, వృక్షం list)
{
  vec<వృక్షం, va_gc> *వాదనలు;
  వృక్షం t, వాదనలు_వృక్షం;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  వాదనలు = c_parser_సమాసం_list (parser, అబద్ధం, నిజం, ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ);
  వాదనలు_వృక్షం = build_వృక్షం_list_vec (వాదనలు);

  కొరకు (t = వాదనలు_వృక్షం; t; t = వృక్షం_CHAIN (t))
    {
      వృక్షం targ = వృక్షం_విలువ (t);

      ఒకవేళ (targ != error_mark_కణుపు)
	{
	  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_కణుపు;
	    }
	  లేకపోతే
	    {
	      వృక్షం c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_వృక్షం_సదిశ (వాదనలు);
  parens.require_close (parser);
  తిరిగి list;
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

నిర్మాణం omp_dim
{
  వృక్షం దిగువ_bound, నిడివి;
  location_t loc;
  తార్కిక no_colon;
  omp_dim (వృక్షం lb, వృక్షం len, location_t lo, తార్కిక nc)
  : దిగువ_bound (lb), నిడివి (len), loc (lo), no_colon (nc) {}
};

స్థిర వృక్షం
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    గణన omp_clause_సంకేతం రకం, వృక్షం list,
			    తార్కిక map_lvalue = అబద్ధం)
{
  auto_vec<omp_dim> dims;
  తార్కిక array_section_p;
  auto_vec<c_token> టోకెన్లు;
  గుర్తులేని పూర్ణాంకం టోకెన్లు_avail = 0;
  c_token *saved_టోకెన్లు = ఖాళీ;

  అయితే (1)
    {
      వృక్షం t = NULL_వృక్షం;
      location_t tloc = c_parser_peek_token (parser)->location;

      ఒకవేళ (రకం == OMP_CLAUSE_DEPEND || రకం == OMP_CLAUSE_AFFINITY)
	{
	  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_రకం != C_ID_ID)
	    {
	      నిర్మాణం c_సమాసం సమాసం;
	      ఒకవేళ (రకం == OMP_CLAUSE_DEPEND
		  && c_parser_తదుపరి_token_is_keyword (parser,
						     RID_OMP_ALL_జ్ఞాపకం)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  సమాసం.విలువ = ridpointers[RID_OMP_ALL_జ్ఞాపకం];
		  c_parser_consume_token (parser);
		}
	      లేకపోతే
		సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	      ఒకవేళ (సమాసం.విలువ != error_mark_కణుపు)
		{
		  వృక్షం u = build_omp_clause (clause_loc, రకం);
		  OMP_CLAUSE_DECL (u) = సమాసం.విలువ;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_COMMA))
		ఆపు;

	      c_parser_consume_token (parser);
	      కొనసాగు;
	    }

	  టోకెన్లు.truncate (0);
	  గుర్తులేని పూర్ణాంకం nesting_లోతు = 0;
	  అయితే (1)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      ఎంపిక (token->type)
		{
		స్థితి CPP_EOF:
		స్థితి CPP_PRAGMA_EOL:
		  ఆపు;
		స్థితి CPP_OPEN_BRACE:
		స్థితి CPP_OPEN_PAREN:
		స్థితి CPP_OPEN_వర్గం:
		  ++nesting_లోతు;
		  వెళ్ళు కూడు;
		స్థితి CPP_CLOSE_BRACE:
		స్థితి CPP_CLOSE_PAREN:
		స్థితి CPP_CLOSE_వర్గం:
		  ఒకవేళ (nesting_లోతు-- == 0)
		    ఆపు;
		  వెళ్ళు కూడు;
		స్థితి CPP_COMMA:
		  ఒకవేళ (nesting_లోతు == 0)
		    ఆపు;
		  వెళ్ళు కూడు;
		అప్రమేయ:
		కూడు:
		  టోకెన్లు.సురక్షిత_నెట్టు (*token);
		  c_parser_consume_token (parser);
		  కొనసాగు;
		}
	      ఆపు;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  memset (&eof_token, 0, పరిమాణం (eof_token));
	  eof_token.type = CPP_EOF;
	  టోకెన్లు.సురక్షిత_నెట్టు (eof_token);
	  టోకెన్లు.సురక్షిత_నెట్టు (eof_token);

	  saved_టోకెన్లు = parser->టోకెన్లు;
	  టోకెన్లు_avail = parser->టోకెన్లు_avail;
	  parser->టోకెన్లు = టోకెన్లు.చిరునామా ();
	  parser->టోకెన్లు_avail = టోకెన్లు.నిడివి ();
	}
      లేకపోతే ఒకవేళ (map_lvalue
	       && (రకం == OMP_CLAUSE_MAP
		   || రకం == OMP_CLAUSE_గమ్యం
		   || రకం == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  తార్కిక save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = నిజం;
	  c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	  ఒకవేళ (సమాసం.విలువ != error_mark_కణుపు)
	    mark_exp_read (సమాసం.విలువ);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  వృక్షం decl = సమాసం.విలువ;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  ఒకవేళ (వృక్షం_సంకేతం (decl) == OMP_ARRAY_SECTION)
	    {
	      అయితే (వృక్షం_సంకేతం (decl) == OMP_ARRAY_SECTION)
		{
		  వృక్షం దిగువ_bound = వృక్షం_నిర్వాహ్యం (decl, 1);
		  వృక్షం నిడివి = వృక్షం_నిర్వాహ్యం (decl, 2);
		  dims.సురక్షిత_నెట్టు (omp_dim (దిగువ_bound, నిడివి, loc, అబద్ధం));
		  decl = వృక్షం_నిర్వాహ్యం (decl, 0);
		}

	      అయితే (వృక్షం_సంకేతం (decl) == ARRAY_REF
		     || వృక్షం_సంకేతం (decl) == పరోక్ష_REF
		     || వృక్షం_సంకేతం (decl) == COMPOUND_సమాసం)
		{
		  ఒకవేళ (వృక్షం_సంకేతం (decl) == COMPOUND_సమాసం)
		    {
		      decl = వృక్షం_నిర్వాహ్యం (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (decl) == పరోక్ష_REF)
		    {
		      dims.సురక్షిత_నెట్టు (omp_dim (integer_zero_కణుపు,
					       integer_one_కణుపు, loc, నిజం));
		      decl = వృక్షం_నిర్వాహ్యం (decl, 0);
		    }
		  లేకపోతే  /* ARRAY_REF. */
		    {
		      వృక్షం సూచీ = వృక్షం_నిర్వాహ్యం (decl, 1);
		      dims.సురక్షిత_నెట్టు (omp_dim (సూచీ, integer_one_కణుపు, loc,
					       నిజం));
		      decl = వృక్షం_నిర్వాహ్యం (decl, 0);
		    }
		}

	      కొరకు (పూర్ణాంకం i = dims.నిడివి () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].దిగువ_bound,
						dims[i].నిడివి);
	    }
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (decl) == పరోక్ష_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = వృక్షం_నిర్వాహ్యం (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_కణుపు,
					      integer_one_కణుపు);
	    }
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (decl) == ARRAY_REF)
	    {
	      వృక్షం idx = వృక్షం_నిర్వాహ్యం (decl, 1);

	      decl = వృక్షం_నిర్వాహ్యం (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_కణుపు);
	    }
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (decl) == NON_LVALUE_సమాసం
		   || CONVERT_సమాసం_P (decl))
	    decl = వృక్షం_నిర్వాహ్యం (decl, 0);

	  వృక్షం u = build_omp_clause (loc, రకం);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  వెళ్ళు తదుపరి_అంశం;
	}

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_రకం == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->విలువ);

	  ఒకవేళ (t == NULL_వృక్షం)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->విలువ);
	      t = error_mark_కణుపు;
	    }

	  c_parser_consume_token (parser);
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).విలువ;
      లేకపోతే
	{
	  c_parser_error (parser, "expected identifier");
	  ఆపు;
	}

      ఒకవేళ (t == error_mark_కణుపు)
	;
      లేకపోతే ఒకవేళ (రకం != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  ఎంపిక (రకం)
	    {
	    స్థితి OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      ఒకవేళ (c_parser_peek_token (parser)->type != CPP_OPEN_వర్గం)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_కణుపు;
		  ఆపు;
		}
	      /* FALLTHROUGH  */
	    స్థితి OMP_CLAUSE_MAP:
	    స్థితి OMP_CLAUSE_FROM:
	    స్థితి OMP_CLAUSE_గమ్యం:
	    ప్రారంభం_component_ref:
	      అయితే (c_parser_తదుపరి_token_is (parser, CPP_DOT)
		     || c_parser_తదుపరి_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_DEREF))
		    {
		      c_సమాసం t_సమాసం;
		      t_సమాసం.విలువ = t;
		      t_సమాసం.original_సంకేతం = ERROR_MARK;
		      t_సమాసం.original_type = ఖాళీ;
		      సమితి_c_సమాసం_ఆధారం_range (&t_సమాసం, op_loc, op_loc);
		      t_సమాసం.m_decimal = 0;
		      t_సమాసం = convert_lvalue_గమ్యం_rvalue (op_loc, t_సమాసం,
							 నిజం, అబద్ధం);
		      t = build_పరోక్ష_ref (op_loc, t_సమాసం.విలువ, RO_ARROW);
		      arrow_loc = t_సమాసం.get_location ();
		    }
		  c_parser_consume_token (parser);
		  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_కణుపు;
		      ఆపు;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  వృక్షం ident = comp_tok->విలువ;
		  location_t comp_loc = comp_tok->location;
		  c_parser_consume_token (parser);
		  t = build_component_ref (op_loc, t, ident, comp_loc,
					   arrow_loc);
		}
	      /* FALLTHROUGH  */
	    స్థితి OMP_CLAUSE_AFFINITY:
	    స్థితి OMP_CLAUSE_DEPEND:
	    స్థితి OMP_CLAUSE_REDUCTION:
	    స్థితి OMP_CLAUSE_లోపల_REDUCTION:
	    స్థితి OMP_CLAUSE_TASK_REDUCTION:
	    స్థితి OMP_CLAUSE_HAS_DEVICE_ADDR:
	      array_section_p = అబద్ధం;
	      dims.truncate (0);
	      అయితే (c_parser_తదుపరి_token_is (parser, CPP_OPEN_వర్గం))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  వృక్షం దిగువ_bound = NULL_వృక్షం, నిడివి = NULL_వృక్షం;
		  తార్కిక no_colon = అబద్ధం;

		  c_parser_consume_token (parser);
		  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_COLON))
		    {
		      location_t సమాసం_loc
			= c_parser_peek_token (parser)->location;
		      c_సమాసం సమాసం = c_parser_వ్యక్తీకరణ (parser);
		      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం,
						       అబద్ధం, నిజం);
		      దిగువ_bound = సమాసం.విలువ;
		      loc = సమాసం_loc;
		    }
		  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_వర్గం))
		    {
		      నిడివి = integer_one_కణుపు;
		      no_colon = నిజం;
		    }
		  లేకపోతే
		    {
		      /* Look for `:'.  */
		      ఒకవేళ (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_కణుపు;
			  ఆపు;
			}
		      array_section_p = నిజం;
		      ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_CLOSE_వర్గం))
			{
			  location_t సమాసం_loc
			    = c_parser_peek_token (parser)->location;
			  c_సమాసం సమాసం = c_parser_వ్యక్తీకరణ (parser);
			  సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం,
							   అబద్ధం, నిజం);
			  నిడివి = సమాసం.విలువ;
			}
		    }
		  /* Look for the closing `]'.  */
		  ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_వర్గం,
					 "expected %<]%>"))
		    {
		      t = error_mark_కణుపు;
		      ఆపు;
		    }

		  dims.సురక్షిత_నెట్టు (omp_dim (దిగువ_bound, నిడివి, loc, no_colon));
		}

	      ఒకవేళ (t != error_mark_కణుపు)
		{
		  ఒకవేళ ((రకం == OMP_CLAUSE_MAP
		       || రకం == OMP_CLAUSE_FROM
		       || రకం == OMP_CLAUSE_గమ్యం)
		      && !array_section_p
		      && (c_parser_తదుపరి_token_is (parser, CPP_DOT)
			  || c_parser_తదుపరి_token_is (parser, CPP_DEREF)))
		    {
		      కొరకు (గుర్తులేని i = 0; i < dims.నిడివి (); i++)
			{
			  gcc_assert (dims[i].నిడివి == integer_one_కణుపు);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].దిగువ_bound);
			}
		      వెళ్ళు ప్రారంభం_component_ref;
		    }
		  లేకపోతే
		    కొరకు (గుర్తులేని i = 0; i < dims.నిడివి (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].దిగువ_bound,
						   dims[i].నిడివి);
		}

	      ఒకవేళ ((రకం == OMP_CLAUSE_DEPEND || రకం == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_కణుపు
		  && parser->టోకెన్లు_avail != 2)
		{
		  ఒకవేళ (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_కణుపు;
		    }
		  లేకపోతే
		    {
		      parser->టోకెన్లు = టోకెన్లు.చిరునామా ();
		      parser->టోకెన్లు_avail = టోకెన్లు.నిడివి ();

		      t = c_parser_సమాసం_no_commas (parser, ఖాళీ).విలువ;
		      ఒకవేళ (t != error_mark_కణుపు && parser->టోకెన్లు_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_కణుపు;
			}
		    }
		}
	      ఆపు;
	    అప్రమేయ:
	      ఆపు;
	    }

	  ఒకవేళ (t != error_mark_కణుపు)
	    {
	      వృక్షం u = build_omp_clause (clause_loc, రకం);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      లేకపోతే  /* kind == OMP_CLAUSE_ERROR */
	list = వృక్షం_cons (t, build_ఖాళీలు_stmt (tloc), list);

      ఒకవేళ (రకం == OMP_CLAUSE_DEPEND || రకం == OMP_CLAUSE_AFFINITY)
	{
	  parser->టోకెన్లు = saved_టోకెన్లు;
	  parser->టోకెన్లు_avail = టోకెన్లు_avail;
	}

    తదుపరి_అంశం:
      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_COMMA))
	ఆపు;

      c_parser_consume_token (parser);
    }

  తిరిగి list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

స్థిర వృక్షం
c_parser_omp_var_list_parens (c_parser *parser, గణన omp_clause_సంకేతం రకం,
			      వృక్షం list, తార్కిక map_lvalue = అబద్ధం)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  ఒకవేళ (parser->లోపల_omp_decl_attribute)
    {
      ఒకవేళ (రకం)
	{
	  వృక్షం u = build_omp_clause (loc, రకం);
	  OMP_CLAUSE_DECL (u) = parser->లోపల_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  తిరిగి u;
	}
      లేకపోతే
	తిరిగి వృక్షం_cons (parser->లోపల_omp_decl_attribute, NULL_వృక్షం, list);
    }

  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, రకం, list, map_lvalue);
      parens.skip_until_దొరికింది_close (parser);
    }
  తిరిగి list;
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

స్థిర వృక్షం
c_parser_oacc_దత్తాంశం_clause (c_parser *parser, pragma_omp_clause c_రకం,
			   వృక్షం list)
{
  గణన gomp_map_రకం రకం;
  ఎంపిక (c_రకం)
    {
    స్థితి PRAGMA_OACC_CLAUSE_ATTACH:
      రకం = GOMP_MAP_ATTACH;
      ఆపు;
    స్థితి PRAGMA_OACC_CLAUSE_COPY:
      రకం = GOMP_MAP_TOFROM;
      ఆపు;
    స్థితి PRAGMA_OACC_CLAUSE_COPYIN:
      రకం = GOMP_MAP_గమ్యం;
      ఆపు;
    స్థితి PRAGMA_OACC_CLAUSE_COPYOUT:
      రకం = GOMP_MAP_FROM;
      ఆపు;
    స్థితి PRAGMA_OACC_CLAUSE_CREATE:
      రకం = GOMP_MAP_ALLOC;
      ఆపు;
    స్థితి PRAGMA_OACC_CLAUSE_DELETE:
      రకం = GOMP_MAP_RELEASE;
      ఆపు;
    స్థితి PRAGMA_OACC_CLAUSE_DETACH:
      రకం = GOMP_MAP_DETACH;
      ఆపు;
    స్థితి PRAGMA_OACC_CLAUSE_DEVICE:
      రకం = GOMP_MAP_FORCE_గమ్యం;
      ఆపు;
    స్థితి PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      రకం = GOMP_MAP_DEVICE_RESIDENT;
      ఆపు;
    స్థితి PRAGMA_OACC_CLAUSE_LINK:
      రకం = GOMP_MAP_LINK;
      ఆపు;
    స్థితి PRAGMA_OACC_CLAUSE_NO_CREATE:
      రకం = GOMP_MAP_IF_PRESENT;
      ఆపు;
    స్థితి PRAGMA_OACC_CLAUSE_PRESENT:
      రకం = GOMP_MAP_FORCE_PRESENT;
      ఆపు;
    స్థితి PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    స్థితి PRAGMA_OACC_CLAUSE_HOST:
      రకం = GOMP_MAP_FORCE_FROM;
      ఆపు;
    అప్రమేయ:
      gcc_unreachable ();
    }

  వృక్షం nl = list;
  తార్కిక readonly = అబద్ధం;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      ఒకవేళ (c_రకం == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ఒకవేళ (token->type == CPP_NAME
	      && !strcmp (IDENTIFIER_సూచిక (token->విలువ), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = నిజం;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       అబద్ధం);
      parens.skip_until_దొరికింది_close (parser);
    }

  కొరకు (వృక్షం c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_సమితి_MAP_రకం (c, రకం);
      ఒకవేళ (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  తిరిగి nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

స్థిర వృక్షం
c_parser_oacc_దత్తాంశం_clause_deviceptr (c_parser *parser, వృక్షం list)
{
  వృక్షం vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ఖాళీ);
  కొరకు (t = vars; t && t; t = వృక్షం_CHAIN (t))
    {
      వృక్షం v = వృక్షం_PURPOSE (t);
      location_t loc = సమాసం_LOCATION (వృక్షం_విలువ (t));

      ఒకవేళ (!VAR_P (v) && వృక్షం_సంకేతం (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      లేకపోతే ఒకవేళ (వృక్షం_TYPE (v) == error_mark_కణుపు)
	;
      లేకపోతే ఒకవేళ (!సూచిక_TYPE_P (వృక్షం_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      వృక్షం u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_సమితి_MAP_రకం (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  తిరిగి list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

స్థిర వృక్షం
c_parser_omp_clause_collapse (c_parser *parser, వృక్షం list)
{
  వృక్షం c, అంకె = error_mark_కణుపు;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      అంకె = c_parser_సమాసం_no_commas (parser, ఖాళీ).విలువ;
      parens.skip_until_దొరికింది_close (parser);
    }
  ఒకవేళ (అంకె == error_mark_కణుపు)
    తిరిగి list;
  mark_exp_read (అంకె);
  అంకె = c_fully_fold (అంకె, అబద్ధం, ఖాళీ);
  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (అంకె))
      || !వృక్షం_సరిపోతుంది_shwi_p (అంకె)
      || (n = వృక్షం_గమ్యం_shwi (అంకె)) <= 0
      || (పూర్ణాంకం) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      తిరిగి list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_సమాసం (c) = అంకె;
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_copyin (c_parser *parser, వృక్షం list)
{
  తిరిగి c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_copyprivate (c_parser *parser, వృక్షం list)
{
  తిరిగి c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

స్థిర వృక్షం
c_parser_omp_clause_default (c_parser *parser, వృక్షం list, తార్కిక is_oacc)
{
  గణన omp_clause_default_రకం రకం = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  వృక్షం c;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);

      ఎంపిక (p[0])
	{
	స్థితి 'n':
	  ఒకవేళ (strcmp ("none", p) != 0)
	    వెళ్ళు invalid_రకం;
	  రకం = OMP_CLAUSE_DEFAULT_NONE;
	  ఆపు;

	స్థితి 'p':
	  ఒకవేళ (is_oacc)
	    {
	      ఒకవేళ (strcmp ("present", p) != 0)
		వెళ్ళు invalid_రకం;
	      రకం = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  లేకపోతే
	    {
	      ఒకవేళ (strcmp ("private", p) != 0)
		వెళ్ళు invalid_రకం;
	      రకం = OMP_CLAUSE_DEFAULT_వ్యక్తిగత;
	    }
	  ఆపు;

	స్థితి 'f':
	  ఒకవేళ (strcmp ("firstprivate", p) != 0 || is_oacc)
	    వెళ్ళు invalid_రకం;
	  రకం = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  ఆపు;

	స్థితి 's':
	  ఒకవేళ (strcmp ("shared", p) != 0 || is_oacc)
	    వెళ్ళు invalid_రకం;
	  రకం = OMP_CLAUSE_DEFAULT_SHARED;
	  ఆపు;

	అప్రమేయ:
	  వెళ్ళు invalid_రకం;
	}

      c_parser_consume_token (parser);
    }
  లేకపోతే
    {
    invalid_రకం:
      ఒకవేళ (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      లేకపోతే
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_దొరికింది_close (parser);

  ఒకవేళ (రకం == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    తిరిగి list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_రకం (c) = రకం;

  తిరిగి c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_firstprivate (c_parser *parser, వృక్షం list)
{
  తిరిగి c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

స్థిర వృక్షం
c_parser_omp_clause_final (c_parser *parser, వృక్షం list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      వృక్షం t, c;
      ఒకవేళ (!parens.require_open (parser))
	t = error_mark_కణుపు;
      లేకపోతే
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	  t = convert_lvalue_గమ్యం_rvalue (eloc, సమాసం, నిజం, నిజం).విలువ;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, అబద్ధం, ఖాళీ);
	  parens.skip_until_దొరికింది_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_సమాసం (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }
  లేకపోతే
    c_parser_error (parser, "expected %<(%>");

  తిరిగి list;
}

/* OpenMP 5.1:
   indirect [( expression )]
*/

స్థిర వృక్షం
c_parser_omp_clause_పరోక్ష (c_parser *parser, వృక్షం list)
{
  location_t location = c_parser_peek_token (parser)->location;
  వృక్షం t;

  ఒకవేళ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      ఒకవేళ (!parens.require_open (parser))
	తిరిగి list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (loc, సమాసం, నిజం, నిజం);
      t = c_objc_common_truthvalue_conversion (loc, సమాసం.విలువ);
      t = c_fully_fold (t, అబద్ధం, ఖాళీ);
      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (t))
	  || వృక్షం_సంకేతం (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  తిరిగి list;
	}
      parens.skip_until_దొరికింది_close (parser);
    }
  లేకపోతే
    t = integer_one_కణుపు;

  check_no_duplicate_clause (list, OMP_CLAUSE_పరోక్ష, "indirect");

  వృక్షం c = build_omp_clause (location, OMP_CLAUSE_పరోక్ష);
  OMP_CLAUSE_పరోక్ష_సమాసం (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;

  తిరిగి c;
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

స్థిర వృక్షం
c_parser_omp_clause_if (c_parser *parser, వృక్షం list, తార్కిక is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  గణన వృక్షం_సంకేతం_2 if_modifier = ERROR_MARK;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  ఒకవేళ (is_omp && c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      పూర్ణాంకం n = 2;
      ఒకవేళ (strcmp (p, "cancel") == 0)
	if_modifier = VOID_CST;
      లేకపోతే ఒకవేళ (strcmp (p, "parallel") == 0)
	if_modifier = OMP_PARALLEL;
      లేకపోతే ఒకవేళ (strcmp (p, "simd") == 0)
	if_modifier = OMP_SIMD;
      లేకపోతే ఒకవేళ (strcmp (p, "task") == 0)
	if_modifier = OMP_TASK;
      లేకపోతే ఒకవేళ (strcmp (p, "taskloop") == 0)
	if_modifier = OMP_TASKLOOP;
      లేకపోతే ఒకవేళ (strcmp (p, "target") == 0)
	{
	  if_modifier = OMP_లక్ష్యం;
	  ఒకవేళ (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	    {
	      p = IDENTIFIER_సూచిక (c_parser_peek_2nd_token (parser)->విలువ);
	      ఒకవేళ (strcmp ("data", p) == 0)
		if_modifier = OMP_లక్ష్యం_దత్తాంశం;
	      లేకపోతే ఒకవేళ (strcmp ("update", p) == 0)
		if_modifier = OMP_లక్ష్యం_UPDATE;
	      లేకపోతే ఒకవేళ (strcmp ("enter", p) == 0)
		if_modifier = OMP_లక్ష్యం_ENTER_దత్తాంశం;
	      లేకపోతే ఒకవేళ (strcmp ("exit", p) == 0)
		if_modifier = OMP_లక్ష్యం_EXIT_దత్తాంశం;
	      ఒకవేళ (if_modifier != OMP_లక్ష్యం)
		{
		  n = 3;
		  c_parser_consume_token (parser);
		}
	      లేకపోతే
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<data%>, %<update%>, %<enter%> "
				 "or %<exit%>");
		  if_modifier = ERROR_MARK;
		}
	      ఒకవేళ (if_modifier == OMP_లక్ష్యం_ENTER_దత్తాంశం
		  || if_modifier == OMP_లక్ష్యం_EXIT_దత్తాంశం)
		{
		  ఒకవేళ (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_సూచిక
				(c_parser_peek_2nd_token (parser)->విలువ);
		      ఒకవేళ (strcmp ("data", p) == 0)
			n = 4;
		    }
		  ఒకవేళ (n == 4)
		    c_parser_consume_token (parser);
		  లేకపోతే
		    {
		      location_t loc
			= c_parser_peek_2nd_token (parser)->location;
		      error_at (loc, "expected %<data%>");
		      if_modifier = ERROR_MARK;
		    }
		}
	    }
	}
      ఒకవేళ (if_modifier != ERROR_MARK)
	{
	  ఒకవేళ (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  లేకపోతే
	    {
	      ఒకవేళ (n > 2)
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<:%>");
		}
	      if_modifier = ERROR_MARK;
	    }
	}
    }

  location_t loc = c_parser_peek_token (parser)->location;
  c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
  సమాసం = convert_lvalue_గమ్యం_rvalue (loc, సమాసం, నిజం, నిజం);
  వృక్షం t = c_objc_common_truthvalue_conversion (loc, సమాసం.విలువ), c;
  t = c_fully_fold (t, అబద్ధం, ఖాళీ);
  parens.skip_until_దొరికింది_close (parser);

  కొరకు (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_IF)
      {
	ఒకవేళ (if_modifier != ERROR_MARK
	    && OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    స్థిరరాశి అక్షరం *p = ఖాళీ;
	    ఎంపిక (if_modifier)
	      {
	      స్థితి VOID_CST: p = "cancel"; ఆపు;
	      స్థితి OMP_PARALLEL: p = "parallel"; ఆపు;
	      స్థితి OMP_SIMD: p = "simd"; ఆపు;
	      స్థితి OMP_TASK: p = "task"; ఆపు;
	      స్థితి OMP_TASKLOOP: p = "taskloop"; ఆపు;
	      స్థితి OMP_లక్ష్యం_దత్తాంశం: p = "target data"; ఆపు;
	      స్థితి OMP_లక్ష్యం: p = "target"; ఆపు;
	      స్థితి OMP_లక్ష్యం_UPDATE: p = "target update"; ఆపు;
	      స్థితి OMP_లక్ష్యం_ENTER_దత్తాంశం: p = "target enter data"; ఆపు;
	      స్థితి OMP_లక్ష్యం_EXIT_దత్తాంశం: p = "target exit data"; ఆపు;
	      అప్రమేయ: gcc_unreachable ();
	      }
	    error_at (location, "too many %<if%> clauses with %qs modifier",
		      p);
	    తిరిగి list;
	  }
	లేకపోతే ఒకవేళ (OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    ఒకవేళ (!is_omp)
	      error_at (location, "too many %<if%> clauses");
	    లేకపోతే
	      error_at (location, "too many %<if%> clauses without modifier");
	    తిరిగి list;
	  }
	లేకపోతే ఒకవేళ (if_modifier == ERROR_MARK
		 || OMP_CLAUSE_IF_MODIFIER (c) == ERROR_MARK)
	  {
	    error_at (location, "if any %<if%> clause has modifier, then all "
				"%<if%> clauses have to use modifier");
	    తిరిగి list;
	  }
      }

  c = build_omp_clause (location, OMP_CLAUSE_IF);
  OMP_CLAUSE_IF_MODIFIER (c) = if_modifier;
  OMP_CLAUSE_IF_సమాసం (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_lastprivate (c_parser *parser, వృక్షం list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  ఒకవేళ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      తార్కిక conditional = అబద్ధం;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  స్థిరరాశి అక్షరం *p
	    = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
	  ఒకవేళ (strcmp (p, "conditional") == 0)
	    {
	      conditional = నిజం;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      వృక్షం nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ఒకవేళ (conditional)
	కొరకు (వృక్షం c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      తిరిగి nlist;
    }
  తిరిగి list;
}

/* OpenMP 3.1:
   mergeable */

స్థిర వృక్షం
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_వాడని, వృక్షం list)
{
  వృక్షం c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  తిరిగి c;
}

/* OpenMP 2.5:
   nowait */

స్థిర వృక్షం
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_వాడని, వృక్షం list)
{
  వృక్షం c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

స్థిర వృక్షం
c_parser_omp_clause_అంకె_దారాలు (c_parser *parser, వృక్షం list)
{
  location_t అంకె_దారాలు_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      location_t సమాసం_loc = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
      వృక్షం c, t = సమాసం.విలువ;
      t = c_fully_fold (t, అబద్ధం, ఖాళీ);

      parens.skip_until_దొరికింది_close (parser);

      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  తిరిగి list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (సమాసం_loc, LE_సమాసం, boolean_type_కణుపు, t,
		       build_int_cst (వృక్షం_TYPE (t), 0));
      protected_సమితి_సమాసం_location (c, సమాసం_loc);
      ఒకవేళ (c == boolean_true_కణుపు)
	{
	  warning_at (సమాసం_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_కణుపు;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_అంకె_దారాలు, "num_threads");

      c = build_omp_clause (అంకె_దారాలు_loc, OMP_CLAUSE_అంకె_దారాలు);
      OMP_CLAUSE_అంకె_దారాలు_సమాసం (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  తిరిగి list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

స్థిర వృక్షం
c_parser_omp_clause_అంకె_tasks (c_parser *parser, వృక్షం list)
{
  location_t అంకె_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      తార్కిక strict = అబద్ధం;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ),
		     "strict") == 0)
	{
	  strict = నిజం;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t సమాసం_loc = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
      వృక్షం c, t = సమాసం.విలువ;
      t = c_fully_fold (t, అబద్ధం, ఖాళీ);

      parens.skip_until_దొరికింది_close (parser);

      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  తిరిగి list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (సమాసం_loc, LE_సమాసం, boolean_type_కణుపు, t,
			   build_int_cst (వృక్షం_TYPE (t), 0));
      ఒకవేళ (CAN_HAVE_LOCATION_P (c))
	సమితి_సమాసం_LOCATION (c, సమాసం_loc);
      ఒకవేళ (c == boolean_true_కణుపు)
	{
	  warning_at (సమాసం_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_కణుపు;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_అంకె_TASKS, "num_tasks");

      c = build_omp_clause (అంకె_tasks_loc, OMP_CLAUSE_అంకె_TASKS);
      OMP_CLAUSE_అంకె_TASKS_సమాసం (c) = t;
      OMP_CLAUSE_అంకె_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  తిరిగి list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

స్థిర వృక్షం
c_parser_omp_clause_grainsize (c_parser *parser, వృక్షం list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      తార్కిక strict = అబద్ధం;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ),
		     "strict") == 0)
	{
	  strict = నిజం;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t సమాసం_loc = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
      వృక్షం c, t = సమాసం.విలువ;
      t = c_fully_fold (t, అబద్ధం, ఖాళీ);

      parens.skip_until_దొరికింది_close (parser);

      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  తిరిగి list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (సమాసం_loc, LE_సమాసం, boolean_type_కణుపు, t,
			   build_int_cst (వృక్షం_TYPE (t), 0));
      ఒకవేళ (CAN_HAVE_LOCATION_P (c))
	సమితి_సమాసం_LOCATION (c, సమాసం_loc);
      ఒకవేళ (c == boolean_true_కణుపు)
	{
	  warning_at (సమాసం_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_కణుపు;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_సమాసం (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  తిరిగి list;
}

/* OpenMP 4.5:
   priority ( expression ) */

స్థిర వృక్షం
c_parser_omp_clause_ప్రాధాన్యత (c_parser *parser, వృక్షం list)
{
  location_t ప్రాధాన్యత_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      location_t సమాసం_loc = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
      వృక్షం c, t = సమాసం.విలువ;
      t = c_fully_fold (t, అబద్ధం, ఖాళీ);

      parens.skip_until_దొరికింది_close (parser);

      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  తిరిగి list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (సమాసం_loc, LT_సమాసం, boolean_type_కణుపు, t,
			   build_int_cst (వృక్షం_TYPE (t), 0));
      ఒకవేళ (CAN_HAVE_LOCATION_P (c))
	సమితి_సమాసం_LOCATION (c, సమాసం_loc);
      ఒకవేళ (c == boolean_true_కణుపు)
	{
	  warning_at (సమాసం_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_కణుపు;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_ప్రాధాన్యత, "priority");

      c = build_omp_clause (ప్రాధాన్యత_loc, OMP_CLAUSE_ప్రాధాన్యత);
      OMP_CLAUSE_ప్రాధాన్యత_సమాసం (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  తిరిగి list;
}

/* OpenMP 4.5:
   hint ( expression ) */

స్థిర వృక్షం
c_parser_omp_clause_hint (c_parser *parser, వృక్షం list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      location_t సమాసం_loc = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
      వృక్షం c, t = సమాసం.విలువ;
      t = c_fully_fold (t, అబద్ధం, ఖాళీ);
      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (t))
	  || వృక్షం_సంకేతం (t) != INTEGER_CST
	  || వృక్షం_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  తిరిగి list;
	}
      parens.skip_until_దొరికింది_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_సమాసం (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  తిరిగి list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

స్థిర వృక్షం
c_parser_omp_clause_filter (c_parser *parser, వృక్షం list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      location_t సమాసం_loc = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
      వృక్షం c, t = సమాసం.విలువ;
      t = c_fully_fold (t, అబద్ధం, ఖాళీ);
      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  తిరిగి list;
	}
      parens.skip_until_దొరికింది_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_సమాసం (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  తిరిగి list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

స్థిర వృక్షం
c_parser_omp_clause_defaultmap (c_parser *parser, వృక్షం list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  వృక్షం c;
  స్థిరరాశి అక్షరం *p;
  గణన omp_clause_defaultmap_రకం behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  గణన omp_clause_defaultmap_రకం category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;
  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  లేకపోతే ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      వెళ్ళు బహిర్గతం_err;
    }
  లేకపోతే
    p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);

  ఎంపిక (p[0])
    {
    స్థితి 'a':
      ఒకవేళ (strcmp ("alloc", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ALLOC;
      లేకపోతే
	వెళ్ళు invalid_behavior;
      ఆపు;

    స్థితి 'd':
      ఒకవేళ (strcmp ("default", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
      లేకపోతే
	వెళ్ళు invalid_behavior;
      ఆపు;

    స్థితి 'f':
      ఒకవేళ (strcmp ("firstprivate", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FIRSTPRIVATE;
      లేకపోతే ఒకవేళ (strcmp ("from", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FROM;
      లేకపోతే
	వెళ్ళు invalid_behavior;
      ఆపు;

    స్థితి 'n':
      ఒకవేళ (strcmp ("none", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_NONE;
      లేకపోతే
	వెళ్ళు invalid_behavior;
      ఆపు;

    స్థితి 'p':
      ఒకవేళ (strcmp ("present", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_PRESENT;
      లేకపోతే
	వెళ్ళు invalid_behavior;
      ఆపు;

    స్థితి 't':
      ఒకవేళ (strcmp ("tofrom", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TOFROM;
      లేకపోతే ఒకవేళ (strcmp ("to", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_గమ్యం;
      లేకపోతే
	వెళ్ళు invalid_behavior;
      ఆపు;

    అప్రమేయ:
      వెళ్ళు invalid_behavior;
    }
  c_parser_consume_token (parser);

  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
    {
      ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	వెళ్ళు బహిర్గతం_err;
      ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  వెళ్ళు బహిర్గతం_err;
	}
      p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఎంపిక (p[0])
	{
	స్థితి 'a':
	  ఒకవేళ (strcmp ("aggregate", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE;
	  లేకపోతే ఒకవేళ (strcmp ("all", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL;
	  లేకపోతే
	    వెళ్ళు invalid_category;
	  ఆపు;

	స్థితి 'p':
	  ఒకవేళ (strcmp ("pointer", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_సూచిక;
	  లేకపోతే
	    వెళ్ళు invalid_category;
	  ఆపు;

	స్థితి 's':
	  ఒకవేళ (strcmp ("scalar", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR;
	  లేకపోతే
	    వెళ్ళు invalid_category;
	  ఆపు;

	అప్రమేయ:
	  వెళ్ళు invalid_category;
	}

      c_parser_consume_token (parser);
    }
  parens.skip_until_దొరికింది_close (parser);

  కొరకు (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEFAULTMAP
	&& (category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
	    || OMP_CLAUSE_DEFAULTMAP_CATEGORY (c) == category
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL)))
      {
	గణన omp_clause_defaultmap_రకం cat = category;
	location_t loc = OMP_CLAUSE_LOCATION (c);
	ఒకవేళ (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
		&& (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		    != OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)))
	  cat = OMP_CLAUSE_DEFAULTMAP_CATEGORY (c);
	p = ఖాళీ;
	ఎంపిక (cat)
	  {
	  స్థితి OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED:
	    p = ఖాళీ;
	    ఆపు;
	  స్థితి OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL:
	    p = "all";
	    ఆపు;
	  స్థితి OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE:
	    p = "aggregate";
	    ఆపు;
	  స్థితి OMP_CLAUSE_DEFAULTMAP_CATEGORY_సూచిక:
	    p = "pointer";
	    ఆపు;
	  స్థితి OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR:
	    p = "scalar";
	    ఆపు;
	  అప్రమేయ:
	    gcc_unreachable ();
	  }
	ఒకవేళ (p)
	  error_at (loc, "too many %<defaultmap%> clauses with %qs category",
		    p);
	లేకపోతే
	  error_at (loc, "too many %<defaultmap%> clauses with unspecified "
			 "category");
	ఆపు;
      }

  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULTMAP);
  OMP_CLAUSE_DEFAULTMAP_సమితి_రకం (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;

 బహిర్గతం_err:
  parens.skip_until_దొరికింది_close (parser);
  తిరిగి list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_use_device_ptr (c_parser *parser, వృక్షం list)
{
  తిరిగి c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_use_device_addr (c_parser *parser, వృక్షం list)
{
  తిరిగి c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_has_device_addr (c_parser *parser, వృక్షం list)
{
  తిరిగి c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_is_device_ptr (c_parser *parser, వృక్షం list)
{
  తిరిగి c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

స్థిర వృక్షం
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_సంకేతం సంకేతం_2,
				 వృక్షం list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  location_t సమాసం_loc = c_parser_peek_token (parser)->location;
  c_సమాసం సమాసం = c_parser_వ్యక్తీకరణ (parser);
  సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
  వృక్షం c, t = సమాసం.విలువ;
  t = c_fully_fold (t, అబద్ధం, ఖాళీ);

  parens.skip_until_దొరికింది_close (parser);

  ఒకవేళ (t == error_mark_కణుపు)
    తిరిగి list;
  లేకపోతే ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (t)))
    {
      error_at (సమాసం_loc, "%qs expression must be integral",
		omp_clause_సంకేతం_name[సంకేతం_2]);
      తిరిగి list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (సమాసం_loc, LE_సమాసం, boolean_type_కణుపు, t,
		       build_int_cst (వృక్షం_TYPE (t), 0));
  protected_సమితి_సమాసం_location (c, సమాసం_loc);
  ఒకవేళ (c == boolean_true_కణుపు)
    {
      warning_at (సమాసం_loc, 0,
		  "%qs value must be positive",
		  omp_clause_సంకేతం_name[సంకేతం_2]);
      t = integer_one_కణుపు;
    }

  check_no_duplicate_clause (list, సంకేతం_2, omp_clause_సంకేతం_name[సంకేతం_2]);

  c = build_omp_clause (loc, సంకేతం_2);
  OMP_CLAUSE_నిర్వాహ్యం (c, 0) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
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

స్థిర వృక్షం
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_సంకేతం రకం,
			    స్థిరరాశి అక్షరం *str, వృక్షం list)
{
  స్థిరరాశి అక్షరం *id = "num";
  వృక్షం ops[2] = { NULL_వృక్షం, NULL_వృక్షం }, c;

  ఒకవేళ (రకం == OMP_CLAUSE_సదిశ)
    id = "length";

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      చేయి
	{
	  c_token *తదుపరి = c_parser_peek_token (parser);
	  పూర్ణాంకం idx = 0;

	  /* Gang static argument.  */
	  ఒకవేళ (రకం == OMP_CLAUSE_GANG
	      && c_parser_తదుపరి_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		వెళ్ళు cleanup_error;

	      idx = 1;
	      ఒకవేళ (ops[idx] != NULL_వృక్షం)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  వెళ్ళు cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_కణుపు;

		  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      కొనసాగు;
		    }
		  లేకపోతే
		    ఆపు;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
		   && strcmp (id, IDENTIFIER_సూచిక (తదుపరి->విలువ)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  ఒకవేళ (ops[idx] != NULL_వృక్షం)
	    {
	      c_parser_error (parser, "unexpected argument");
	      వెళ్ళు cleanup_error;
	    }

	  location_t సమాసం_loc = c_parser_peek_token (parser)->location;
	  c_సమాసం cexpr = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	  cexpr = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, cexpr, అబద్ధం, నిజం);
	  వృక్షం సమాసం = cexpr.విలువ;
	  ఒకవేళ (సమాసం == error_mark_కణుపు)
	    వెళ్ళు cleanup_error;

	  సమాసం = c_fully_fold (సమాసం, అబద్ధం, ఖాళీ);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (సమాసం)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      తిరిగి list;
	    }

	  వృక్షం c = fold_build2_loc (సమాసం_loc, LE_సమాసం, boolean_type_కణుపు, సమాసం,
				    build_int_cst (వృక్షం_TYPE (సమాసం), 0));
	  ఒకవేళ (c == boolean_true_కణుపు)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      సమాసం = integer_one_కణుపు;
	    }

	  ops[idx] = సమాసం;

	  ఒకవేళ (రకం == OMP_CLAUSE_GANG
	      && c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      కొనసాగు;
	    }
	  ఆపు;
	}
      అయితే (1);

      ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	వెళ్ళు cleanup_error;
    }

  check_no_duplicate_clause (list, రకం, str);

  c = build_omp_clause (loc, రకం);

  ఒకవేళ (ops[1])
    OMP_CLAUSE_నిర్వాహ్యం (c, 1) = ops[1];

  OMP_CLAUSE_నిర్వాహ్యం (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  తిరిగి c;

 cleanup_error:
  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, 0);
  తిరిగి list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

స్థిర వృక్షం
c_parser_oacc_simple_clause (location_t loc, గణన omp_clause_సంకేతం సంకేతం_2,
			     వృక్షం list)
{
  check_no_duplicate_clause (list, సంకేతం_2, omp_clause_సంకేతం_name[సంకేతం_2]);

  వృక్షం c = build_omp_clause (loc, సంకేతం_2);
  OMP_CLAUSE_CHAIN (c) = list;

  తిరిగి c;
}

/* OpenACC:
   async [( int-expr )] */

స్థిర వృక్షం
c_parser_oacc_clause_async (c_parser *parser, వృక్షం list)
{
  వృక్షం c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_కణుపు, GOMP_ASYNC_NOVAL);

  ఒకవేళ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_సమాసం_no_commas (parser, ఖాళీ).విలువ;
      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      లేకపోతే ఒకవేళ (t == error_mark_కణుపు
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	తిరిగి list;
    }
  లేకపోతే
    t = c_fully_fold (t, అబద్ధం, ఖాళీ);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_సమాసం (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  తిరిగి list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

స్థిర వృక్షం
c_parser_oacc_clause_tile (c_parser *parser, వృక్షం list)
{
  వృక్షం c, సమాసం = error_mark_కణుపు;
  location_t loc;
  వృక్షం tile = NULL_వృక్షం;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    తిరిగి list;

  చేయి
    {
      ఒకవేళ (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	తిరిగి list;

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  సమాసం = integer_zero_కణుపు;
	}
      లేకపోతే
	{
	  location_t సమాసం_loc = c_parser_peek_token (parser)->location;
	  c_సమాసం cexpr = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	  cexpr = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, cexpr, అబద్ధం, నిజం);
	  సమాసం = cexpr.విలువ;

	  ఒకవేళ (సమాసం == error_mark_కణుపు)
	    {
	      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      తిరిగి list;
	    }

	  సమాసం = c_fully_fold (సమాసం, అబద్ధం, ఖాళీ);

	  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (సమాసం))
	      || !వృక్షం_సరిపోతుంది_shwi_p (సమాసం)
	      || వృక్షం_గమ్యం_shwi (సమాసం) <= 0)
	    {
	      error_at (సమాసం_loc, "%<tile%> argument needs positive"
			" integral constant");
	      సమాసం = integer_zero_కణుపు;
	    }
	}

      tile = వృక్షం_cons (NULL_వృక్షం, సమాసం, tile);
    }
  అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_CLOSE_PAREN));

  /* Consume the trailing ')'.  */
  c_parser_consume_token (parser);

  c = build_omp_clause (loc, OMP_CLAUSE_TILE);
  tile = nreverse (tile);
  OMP_CLAUSE_TILE_LIST (c) = tile;
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
}

/* OpenACC:
   wait [( int-expr-list )] */

స్థిర వృక్షం
c_parser_oacc_clause_wait (c_parser *parser, వృక్షం list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  ఒకవేళ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  లేకపోతే
    {
      వృక్షం c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_కణుపు, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  తిరిగి list;
}

/* OpenACC 2.7:
   self [( expression )] */

స్థిర వృక్షం
c_parser_oacc_compute_clause_self (c_parser *parser, వృక్షం list)
{
  వృక్షం t;
  location_t location = c_parser_peek_token (parser)->location;
  ఒకవేళ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (loc, సమాసం, నిజం, నిజం);
      t = c_objc_common_truthvalue_conversion (loc, సమాసం.విలువ);
      t = c_fully_fold (t, అబద్ధం, ఖాళీ);
      parens.skip_until_దొరికింది_close (parser);
    }
  లేకపోతే
    t = truthvalue_true_కణుపు;

  కొరకు (వృక్షం c = list; c; c = OMP_CLAUSE_CHAIN (c))
    ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	తిరిగి list;
      }

  వృక్షం c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_సమాసం (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
}

/* OpenMP 5.0:
   order ( concurrent )

   OpenMP 5.1:
   order ( order-modifier : concurrent )

   order-modifier:
     reproducible
     unconstrained  */

స్థిర వృక్షం
c_parser_omp_clause_క్రమం (c_parser *parser, వృక్షం list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  వృక్షం c;
  స్థిరరాశి అక్షరం *p;
  తార్కిక unconstrained = అబద్ధం;
  తార్కిక reproducible = అబద్ధం;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp (p, "unconstrained") == 0)
	unconstrained = నిజం;
      లేకపోతే ఒకవేళ (strcmp (p, "reproducible") == 0)
	reproducible = నిజం;
      లేకపోతే
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  వెళ్ళు బహిర్గతం_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      వెళ్ళు బహిర్గతం_err;
    }
  p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
  ఒకవేళ (strcmp (p, "concurrent") != 0)
    {
      c_parser_error (parser, "expected %<concurrent%>");
      వెళ్ళు బహిర్గతం_err;
    }
  c_parser_consume_token (parser);
  parens.skip_until_దొరికింది_close (parser);
  check_no_duplicate_clause (list, OMP_CLAUSE_క్రమం, "order");
  c = build_omp_clause (loc, OMP_CLAUSE_క్రమం);
  OMP_CLAUSE_క్రమం_UNCONSTRAINED (c) = unconstrained;
  OMP_CLAUSE_క్రమం_REPRODUCIBLE (c) = reproducible;
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;

 బహిర్గతం_err:
  parens.skip_until_దొరికింది_close (parser);
  తిరిగి list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

స్థిర వృక్షం
c_parser_omp_clause_bind (c_parser *parser, వృక్షం list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  వృక్షం c;
  స్థిరరాశి అక్షరం *p;
  గణన omp_clause_bind_రకం రకం = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;
  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_దొరికింది_close (parser);
      తిరిగి list;
    }
  p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
  ఒకవేళ (strcmp (p, "teams") == 0)
    రకం = OMP_CLAUSE_BIND_TEAMS;
  లేకపోతే ఒకవేళ (strcmp (p, "parallel") == 0)
    రకం = OMP_CLAUSE_BIND_PARALLEL;
  లేకపోతే ఒకవేళ (strcmp (p, "thread") != 0)
    వెళ్ళు invalid;
  c_parser_consume_token (parser);
  parens.skip_until_దొరికింది_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_రకం (c) = రకం;
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

స్థిర వృక్షం
c_parser_omp_clause_ordered (c_parser *parser, వృక్షం list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  వృక్షం c, అంకె = NULL_వృక్షం;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      అంకె = c_parser_సమాసం_no_commas (parser, ఖాళీ).విలువ;
      parens.skip_until_దొరికింది_close (parser);
    }
  ఒకవేళ (అంకె == error_mark_కణుపు)
    తిరిగి list;
  ఒకవేళ (అంకె)
    {
      mark_exp_read (అంకె);
      అంకె = c_fully_fold (అంకె, అబద్ధం, ఖాళీ);
      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (అంకె))
	  || !వృక్షం_సరిపోతుంది_shwi_p (అంకె)
	  || (n = వృక్షం_గమ్యం_shwi (అంకె)) <= 0
	  || (పూర్ణాంకం) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  తిరిగి list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_సమాసం (c) = అంకె;
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_వ్యక్తిగత (c_parser *parser, వృక్షం list)
{
  తిరిగి c_parser_omp_var_list_parens (parser, OMP_CLAUSE_వ్యక్తిగత, list);
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

స్థిర వృక్షం
c_parser_omp_clause_reduction (c_parser *parser, గణన omp_clause_సంకేతం రకం,
			       తార్కిక is_omp, వృక్షం list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      తార్కిక task = అబద్ధం;
      తార్కిక inscan = అబద్ధం;
      గణన వృక్షం_సంకేతం_2 సంకేతం_2 = ERROR_MARK;
      వృక్షం reduc_id = NULL_వృక్షం;

      ఒకవేళ (రకం == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      స్థిరరాశి అక్షరం *p
		= IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
	      ఒకవేళ (strcmp (p, "task") == 0)
		task = నిజం;
	      లేకపోతే ఒకవేళ (strcmp (p, "inscan") == 0)
		inscan = నిజం;
	      ఒకవేళ (task || inscan)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		}
	    }
	}

      ఎంపిక (c_parser_peek_token (parser)->type)
	{
	స్థితి CPP_PLUS:
	  సంకేతం_2 = PLUS_సమాసం;
	  ఆపు;
	స్థితి CPP_MULT:
	  సంకేతం_2 = MULT_సమాసం;
	  ఆపు;
	స్థితి CPP_MINUS:
	  ఒకవేళ (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.కూడు_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  సంకేతం_2 = MINUS_సమాసం;
	  ఆపు;
	స్థితి CPP_AND:
	  సంకేతం_2 = బిట్టు_AND_సమాసం;
	  ఆపు;
	స్థితి CPP_XOR:
	  సంకేతం_2 = బిట్టు_XOR_సమాసం;
	  ఆపు;
	స్థితి CPP_OR:
	  సంకేతం_2 = బిట్టు_IOR_సమాసం;
	  ఆపు;
	స్థితి CPP_AND_AND:
	  సంకేతం_2 = TRUTH_ANDIF_సమాసం;
	  ఆపు;
	స్థితి CPP_OR_OR:
	  సంకేతం_2 = TRUTH_ORIF_సమాసం;
	  ఆపు;
        స్థితి CPP_NAME:
	  {
	    స్థిరరాశి అక్షరం *p
	      = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
	    ఒకవేళ (strcmp (p, "min") == 0)
	      {
		సంకేతం_2 = MIN_సమాసం;
		ఆపు;
	      }
	    ఒకవేళ (strcmp (p, "max") == 0)
	      {
		సంకేతం_2 = MAX_సమాసం;
		ఆపు;
	      }
	    reduc_id = c_parser_peek_token (parser)->విలువ;
	    ఆపు;
	  }
	అప్రమేయ:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, 0);
	  తిరిగి list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (సంకేతం_2, reduc_id);
      ఒకవేళ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  వృక్షం nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, రకం, list);
	  కొరకు (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      వృక్షం d = OMP_CLAUSE_DECL (c), type;
	      ఒకవేళ (వృక్షం_సంకేతం (d) != OMP_ARRAY_SECTION)
		type = వృక్షం_TYPE (d);
	      లేకపోతే
		{
		  పూర్ణాంకం cnt = 0;
		  వృక్షం t;
		  కొరకు (t = d;
		      వృక్షం_సంకేతం (t) == OMP_ARRAY_SECTION;
		      t = వృక్షం_నిర్వాహ్యం (t, 0))
		    cnt++;
		  type = వృక్షం_TYPE (t);
		  అయితే (cnt > 0)
		    {
		      ఒకవేళ (వృక్షం_సంకేతం (type) != సూచిక_TYPE
			  && వృక్షం_సంకేతం (type) != ARRAY_TYPE)
			ఆపు;
		      type = వృక్షం_TYPE (type);
		      cnt--;
		    }
		}
	      అయితే (వృక్షం_సంకేతం (type) == ARRAY_TYPE)
		type = వృక్షం_TYPE (type);
	      OMP_CLAUSE_REDUCTION_సంకేతం (c) = సంకేతం_2;
	      ఒకవేళ (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      లేకపోతే ఒకవేళ (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      ఒకవేళ (సంకేతం_2 == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || వృక్షం_సంకేతం (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_దొరికింది_close (parser);
    }
  తిరిగి list;
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

స్థిర వృక్షం
c_parser_omp_clause_కాలపట్టిక (c_parser *parser, వృక్షం list)
{
  వృక్షం c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  పూర్ణాంకం modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  c = build_omp_clause (loc, OMP_CLAUSE_కాలపట్టిక);

  location_t comma = UNKNOWN_LOCATION;
  అయితే (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      వృక్షం రకం = c_parser_peek_token (parser)->విలువ;
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (రకం);
      ఒకవేళ (strcmp ("simd", p) == 0)
	OMP_CLAUSE_కాలపట్టిక_SIMD (c) = 1;
      లేకపోతే ఒకవేళ (strcmp ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_కాలపట్టిక_MONOTONIC;
      లేకపోతే ఒకవేళ (strcmp ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_కాలపట్టిక_NONMONOTONIC;
      లేకపోతే
	ఆపు;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      ఒకవేళ (nmodifiers++ == 0
	  && c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	{
	  comma = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	}
      లేకపోతే
	{
	  c_parser_require (parser, CPP_COLON, "expected %<:%>");
	  ఆపు;
	}
    }
  ఒకవేళ (comma != UNKNOWN_LOCATION)
    error_at (comma, "expected %<:%>");

  ఒకవేళ ((modifiers & (OMP_CLAUSE_కాలపట్టిక_MONOTONIC
		    | OMP_CLAUSE_కాలపట్టిక_NONMONOTONIC))
      == (OMP_CLAUSE_కాలపట్టిక_MONOTONIC
	  | OMP_CLAUSE_కాలపట్టిక_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      వృక్షం రకం = c_parser_peek_token (parser)->విలువ;
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (రకం);

      ఎంపిక (p[0])
	{
	స్థితి 'd':
	  ఒకవేళ (strcmp ("dynamic", p) != 0)
	    వెళ్ళు invalid_రకం;
	  OMP_CLAUSE_కాలపట్టిక_రకం (c) = OMP_CLAUSE_కాలపట్టిక_DYNAMIC;
	  ఆపు;

        స్థితి 'g':
	  ఒకవేళ (strcmp ("guided", p) != 0)
	    వెళ్ళు invalid_రకం;
	  OMP_CLAUSE_కాలపట్టిక_రకం (c) = OMP_CLAUSE_కాలపట్టిక_GUIDED;
	  ఆపు;

	స్థితి 'r':
	  ఒకవేళ (strcmp ("runtime", p) != 0)
	    వెళ్ళు invalid_రకం;
	  OMP_CLAUSE_కాలపట్టిక_రకం (c) = OMP_CLAUSE_కాలపట్టిక_RUNTIME;
	  ఆపు;

	అప్రమేయ:
	  వెళ్ళు invalid_రకం;
	}
    }
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_కాలపట్టిక_రకం (c) = OMP_CLAUSE_కాలపట్టిక_STATIC;
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_కాలపట్టిక_రకం (c) = OMP_CLAUSE_కాలపట్టిక_AUTO;
  లేకపోతే
    వెళ్ళు invalid_రకం;

  c_parser_consume_token (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
    {
      location_t ఇక్కడ;
      c_parser_consume_token (parser);

      ఇక్కడ = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (ఇక్కడ, సమాసం, అబద్ధం, నిజం);
      t = సమాసం.విలువ;
      t = c_fully_fold (t, అబద్ధం, ఖాళీ);

      ఒకవేళ (OMP_CLAUSE_కాలపట్టిక_రకం (c) == OMP_CLAUSE_కాలపట్టిక_RUNTIME)
	error_at (ఇక్కడ, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      లేకపోతే ఒకవేళ (OMP_CLAUSE_కాలపట్టిక_రకం (c) == OMP_CLAUSE_కాలపట్టిక_AUTO)
	error_at (ఇక్కడ,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (t)) == INTEGER_TYPE
	       || వృక్షం_సంకేతం (వృక్షం_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  వృక్షం s = fold_build2_loc (loc, LE_సమాసం, boolean_type_కణుపు, t,
				    build_int_cst (వృక్షం_TYPE (t), 0));
	  protected_సమితి_సమాసం_location (s, loc);
	  ఒకవేళ (s == boolean_true_కణుపు)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_కణుపు;
	    }
	  OMP_CLAUSE_కాలపట్టిక_CHUNK_సమాసం (c) = t;
	}
      లేకపోతే
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_దొరికింది_close (parser);
    }
  లేకపోతే
    c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_కాలపట్టిక_రకం (c)
    = (గణన omp_clause_కాలపట్టిక_రకం)
      (OMP_CLAUSE_కాలపట్టిక_రకం (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_కాలపట్టిక, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;

 invalid_రకం:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, 0);
  తిరిగి list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_shared (c_parser *parser, వృక్షం list)
{
  తిరిగి c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

స్థిర వృక్షం
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_వాడని, వృక్షం list)
{
  వృక్షం c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_UNTIED, "untied");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_UNTIED);
  OMP_CLAUSE_CHAIN (c) = list;

  తిరిగి c;
}

/* OpenMP 4.0:
   inbranch
   notinbranch */

స్థిర వృక్షం
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_వాడని,
			    గణన omp_clause_సంకేతం సంకేతం_2, వృక్షం list)
{
  check_no_duplicate_clause (list, సంకేతం_2, omp_clause_సంకేతం_name[సంకేతం_2]);

  వృక్షం c = build_omp_clause (c_parser_peek_token (parser)->location, సంకేతం_2);
  OMP_CLAUSE_CHAIN (c) = list;

  తిరిగి c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

స్థిర వృక్షం
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_వాడని,
				గణన omp_clause_సంకేతం సంకేతం_2, వృక్షం list)
{
  వృక్షం c = build_omp_clause (c_parser_peek_token (parser)->location, సంకేతం_2);
  OMP_CLAUSE_CHAIN (c) = list;

  తిరిగి c;
}

/* OpenMP 4.5:
   nogroup */

స్థిర వృక్షం
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_వాడని, వృక్షం list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  వృక్షం c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
}

/* OpenMP 4.5:
   simd
దారాలు*/

స్థిర వృక్షం
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_వాడని,
				 గణన omp_clause_సంకేతం సంకేతం_2, వృక్షం list)
{
  check_no_duplicate_clause (list, సంకేతం_2, omp_clause_సంకేతం_name[సంకేతం_2]);
  వృక్షం c = build_omp_clause (c_parser_peek_token (parser)->location, సంకేతం_2);
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

స్థిర వృక్షం
c_parser_omp_clause_అంకె_teams (c_parser *parser, వృక్షం list)
{
  location_t అంకె_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      location_t పై_loc = c_parser_peek_token (parser)->location;
      location_t క్రింది_loc = UNKNOWN_LOCATION;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (పై_loc, సమాసం, అబద్ధం, నిజం);
      వృక్షం c, పై = సమాసం.విలువ, క్రింది = NULL_వృక్షం;
      పై = c_fully_fold (పై, అబద్ధం, ఖాళీ);

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  క్రింది_loc = పై_loc;
	  క్రింది = పై;
	  పై_loc = c_parser_peek_token (parser)->location;
	  సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	  సమాసం = convert_lvalue_గమ్యం_rvalue (పై_loc, సమాసం, అబద్ధం, నిజం);
	  పై = సమాసం.విలువ;
	  పై = c_fully_fold (పై, అబద్ధం, ఖాళీ);
	}

      parens.skip_until_దొరికింది_close (parser);

      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (పై))
	  || (క్రింది && !INTEGRAL_TYPE_P (వృక్షం_TYPE (క్రింది))))
	{
	  c_parser_error (parser, "expected integer expression");
	  తిరిగి list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (పై_loc, LE_సమాసం, boolean_type_కణుపు, పై,
			   build_int_cst (వృక్షం_TYPE (పై), 0));
      protected_సమితి_సమాసం_location (c, పై_loc);
      ఒకవేళ (c == boolean_true_కణుపు)
	{
	  warning_at (పై_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  పై = integer_one_కణుపు;
	}
      ఒకవేళ (క్రింది)
	{
	  c = fold_build2_loc (క్రింది_loc, LE_సమాసం, boolean_type_కణుపు, క్రింది,
			       build_int_cst (వృక్షం_TYPE (క్రింది), 0));
	  protected_సమితి_సమాసం_location (c, క్రింది_loc);
	  ఒకవేళ (c == boolean_true_కణుపు)
	    {
	      warning_at (క్రింది_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      క్రింది = NULL_వృక్షం;
	    }
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (క్రింది) == INTEGER_CST
		   && వృక్షం_సంకేతం (పై) == INTEGER_CST
		   && వృక్షం_int_cst_lt (పై, క్రింది))
	    {
	      warning_at (క్రింది_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", క్రింది, పై);
	      క్రింది = NULL_వృక్షం;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_అంకె_TEAMS, "num_teams");

      c = build_omp_clause (అంకె_teams_loc, OMP_CLAUSE_అంకె_TEAMS);
      OMP_CLAUSE_అంకె_TEAMS_పై_సమాసం (c) = పై;
      OMP_CLAUSE_అంకె_TEAMS_క్రింది_సమాసం (c) = క్రింది;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  తిరిగి list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

స్థిర వృక్షం
c_parser_omp_clause_thread_హద్దు (c_parser *parser, వృక్షం list)
{
  location_t అంకె_thread_హద్దు_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      location_t సమాసం_loc = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
      వృక్షం c, t = సమాసం.విలువ;
      t = c_fully_fold (t, అబద్ధం, ఖాళీ);

      parens.skip_until_దొరికింది_close (parser);

      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  తిరిగి list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (సమాసం_loc, LE_సమాసం, boolean_type_కణుపు, t,
			   build_int_cst (వృక్షం_TYPE (t), 0));
      protected_సమితి_సమాసం_location (c, సమాసం_loc);
      ఒకవేళ (c == boolean_true_కణుపు)
	{
	  warning_at (సమాసం_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_కణుపు;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_హద్దు,
				 "thread_limit");

      c = build_omp_clause (అంకె_thread_హద్దు_loc, OMP_CLAUSE_THREAD_హద్దు);
      OMP_CLAUSE_THREAD_హద్దు_సమాసం (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  తిరిగి list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

స్థిర వృక్షం
c_parser_omp_clause_aligned (c_parser *parser, వృక్షం list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  వృక్షం nl, c;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t సమాసం_loc = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
      వృక్షం alignment = సమాసం.విలువ;
      alignment = c_fully_fold (alignment, అబద్ధం, ఖాళీ);
      ఒకవేళ (వృక్షం_సంకేతం (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (వృక్షం_TYPE (alignment))
	  || వృక్షం_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_వృక్షం;
	}

      కొరకు (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_దొరికింది_close (parser);
  తిరిగి nl;
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

స్థిర వృక్షం
c_parser_omp_clause_allocate (c_parser *parser, వృక్షం list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  వృక్షం nl, c;
  వృక్షం allocator = NULL_వృక్షం;
  వృక్షం align = NULL_వృక్షం;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  ఒకవేళ ((c_parser_తదుపరి_token_is_not (parser, CPP_NAME)
       && c_parser_తదుపరి_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      తార్కిక has_modifiers = అబద్ధం;
      వృక్షం orig_type = NULL_వృక్షం;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  గుర్తులేని పూర్ణాంకం n = 3;
	  స్థిరరాశి అక్షరం *p
	    = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
	  ఒకవేళ ((strcmp (p, "allocator") == 0 || strcmp (p, "align") == 0)
	      && c_parser_check_సమతుల్య_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      ఒకవేళ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = నిజం;
	      లేకపోతే ఒకవేళ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  స్థిరరాశి అక్షరం *q = IDENTIFIER_సూచిక (tok->విలువ);
		  n += 4;
		  ఒకవేళ ((strcmp (q, "allocator") == 0
		       || strcmp (q, "align") == 0)
		      && c_parser_check_సమతుల్య_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = నిజం;
		}
	    }
	  ఒకవేళ (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t సమాసం_loc = c_parser_peek_token (parser)->location;
	      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
	      ఒకవేళ (సమాసం.విలువ == error_mark_కణుపు)
		;
	      లేకపోతే ఒకవేళ (strcmp (p, "allocator") == 0)
		{
		  allocator = సమాసం.విలువ;
		  allocator = c_fully_fold (allocator, అబద్ధం, ఖాళీ);
		  orig_type = సమాసం.original_type
			      ? సమాసం.original_type : వృక్షం_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      లేకపోతే
		{
		  align = సమాసం.విలువ;
		  align = c_fully_fold (align, అబద్ధం, ఖాళీ);
		}
	      parens2.skip_until_దొరికింది_close (parser);
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  స్థిరరాశి అక్షరం *q = "";
		  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_సూచిక (tok->విలువ);
		  ఒకవేళ (strcmp (q, "allocator") != 0 && strcmp (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_దొరికింది_close (parser);
		      తిరిగి list;
		    }
		  లేకపోతే ఒకవేళ (strcmp (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_దొరికింది_close (parser);
		      తిరిగి list;
		    }
		  c_parser_consume_token (parser);
		  ఒకవేళ (!parens2.require_open (parser))
		    {
		      parens.skip_until_దొరికింది_close (parser);
		      తిరిగి list;
		    }
		  సమాసం_loc = c_parser_peek_token (parser)->location;
		  సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
		  సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం,
						   నిజం);
		  ఒకవేళ (strcmp (q, "allocator") == 0)
		    {
		      allocator = సమాసం.విలువ;
		      allocator = c_fully_fold (allocator, అబద్ధం, ఖాళీ);
		      orig_type = సమాసం.original_type
				  ? సమాసం.original_type : వృక్షం_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  లేకపోతే
		    {
		      align = సమాసం.విలువ;
		      align = c_fully_fold (align, అబద్ధం, ఖాళీ);
		    }
		  parens2.skip_until_దొరికింది_close (parser);
		}
	    }
	}
      ఒకవేళ (!has_modifiers)
	{
	  location_t సమాసం_loc = c_parser_peek_token (parser)->location;
	  c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	  సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
	  ఒకవేళ (సమాసం.విలువ != error_mark_కణుపు)
	    {
	      allocator = సమాసం.విలువ;
	      allocator = c_fully_fold (allocator, అబద్ధం, ఖాళీ);
	      orig_type = సమాసం.original_type
			  ? సమాసం.original_type : వృక్షం_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      ఒకవేళ (allocator
	  && (!INTEGRAL_TYPE_P (వృక్షం_TYPE (allocator))
	      || వృక్షం_సంకేతం (orig_type) != ENUMERAL_TYPE
	      || (TYPE_NAME (orig_type)
		  != get_identifier ("omp_allocator_handle_t"))))
        {
          error_at (clause_loc, "%<allocate%> clause allocator expression "
				"has type %qT rather than "
				"%<omp_allocator_handle_t%>",
				వృక్షం_TYPE (allocator));
          allocator = NULL_వృక్షం;
        }
      ఒకవేళ (align
	  && (!INTEGRAL_TYPE_P (వృక్షం_TYPE (align))
	      || !వృక్షం_సరిపోతుంది_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_వృక్షం;
	}
      ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_దొరికింది_close (parser);
	  తిరిగి list;
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALLOCATE, list);

  ఒకవేళ (allocator || align)
    కొరకు (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      {
	OMP_CLAUSE_ALLOCATE_ALLOCATOR (c) = allocator;
	OMP_CLAUSE_ALLOCATE_ALIGN (c) = align;
      }

  parens.skip_until_దొరికింది_close (parser);
  తిరిగి nl;
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

స్థిర వృక్షం
c_parser_omp_clause_ఉపయోగిస్తుంది_allocators (c_parser *parser, వృక్షం list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  వృక్షం nl = list;
  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

parse_తదుపరి:

  తార్కిక has_modifiers = అబద్ధం;
  తార్కిక చూసిన_allocators = అబద్ధం;
  వృక్షం memspace_సమాసం = NULL_వృక్షం;
  వృక్షం traits_var = NULL_వృక్షం;

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      గుర్తులేని పూర్ణాంకం n = 3;
      స్థిరరాశి అక్షరం *p
	= IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ ((strcmp (p, "traits") == 0 || strcmp (p, "memspace") == 0)
	  && c_parser_check_సమతుల్య_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  ఒకవేళ (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = నిజం;
	  లేకపోతే ఒకవేళ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      స్థిరరాశి అక్షరం *q = IDENTIFIER_సూచిక (tok->విలువ);
	      n += 4;
	      ఒకవేళ ((strcmp (q, "traits") == 0
		   || strcmp (q, "memspace") == 0)
		  && c_parser_check_సమతుల్య_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  ఒకవేళ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = నిజం;
		  ఒకవేళ ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      స్థిరరాశి అక్షరం *m = IDENTIFIER_సూచిక (tok->విలువ);
		      ఒకవేళ (strcmp (p, m) == 0 || strcmp (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  వెళ్ళు చివర;
			}
		    }
		}
	    }
	}
      ఒకవేళ (has_modifiers)
	{
	  c_parser_consume_token (parser);
	  matching_parens parens2;
	  parens2.require_open (parser);
	  c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	  ఒకవేళ (సమాసం.విలువ == error_mark_కణుపు)
	    ;
	  లేకపోతే ఒకవేళ (strcmp (p, "traits") == 0)
	    {
	      traits_var = సమాసం.విలువ;
	      traits_var = c_fully_fold (traits_var, అబద్ధం, ఖాళీ);
	      mark_exp_read (traits_var);
	    }
	  లేకపోతే
	    {
	      memspace_సమాసం = సమాసం.విలువ;
	      memspace_సమాసం = c_fully_fold (memspace_సమాసం, అబద్ధం, ఖాళీ);
	    }
	  parens2.skip_until_దొరికింది_close (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      స్థిరరాశి అక్షరం *q = "";
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
		q = IDENTIFIER_సూచిక (tok->విలువ);
	      ఒకవేళ (strcmp (q, "traits") != 0 && strcmp (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_దొరికింది_close (parser);
		  తిరిగి list;
		}
	      లేకపోతే ఒకవేళ (strcmp (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_దొరికింది_close (parser);
		  తిరిగి list;
		}
	      c_parser_consume_token (parser);
	      ఒకవేళ (!parens2.require_open (parser))
		{
		  parens.skip_until_దొరికింది_close (parser);
		  తిరిగి list;
		}
	      సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	      ఒకవేళ (strcmp (q, "traits") == 0)
		{
		  traits_var = సమాసం.విలువ;
		  traits_var = c_fully_fold (traits_var, అబద్ధం, ఖాళీ);
		  mark_exp_read (traits_var);
		}
	      లేకపోతే
		{
		  memspace_సమాసం = సమాసం.విలువ;
		  memspace_సమాసం = c_fully_fold (memspace_సమాసం, అబద్ధం, ఖాళీ);
		}
	      parens2.skip_until_దొరికింది_close (parser);
	    }
	  ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    వెళ్ళు చివర;
	}
    }

  అయితే (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      స్థిరరాశి అక్షరం *tok_s = IDENTIFIER_సూచిక (tok->విలువ);
      వృక్షం t = lookup_name (tok->విలువ);
      ఒకవేళ (t == NULL_వృక్షం)
	{
	  undeclared_variable (tok->location, tok->విలువ);
	  t = error_mark_కణుపు;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      వృక్షం legacy_traits = NULL_వృక్షం;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  స్థిరరాశి అక్షరం *tok_a
	    = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
	  c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_దొరికింది_close (parser);

	  ఒకవేళ (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      వెళ్ళు చివర;
	    }
	  legacy_traits = c_fully_fold (సమాసం.విలువ, అబద్ధం, ఖాళీ);
	  ఒకవేళ (legacy_traits == error_mark_కణుపు)
	    వెళ్ళు చివర;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  ఒకవేళ (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.కూడు_fixit_replace (alloc_loc, "traits");
	      richloc.కూడు_fixit_చొప్పించు_after (close_loc, ": ");
	      richloc.కూడు_fixit_చొప్పించు_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      ఒకవేళ (చూసిన_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  వెళ్ళు చివర;
	}
      చూసిన_allocators = నిజం;

      వృక్షం c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_ఉపయోగిస్తుంది_ALLOCATORS);
      OMP_CLAUSE_ఉపయోగిస్తుంది_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_ఉపయోగిస్తుంది_ALLOCATORS_MEMSPACE (c) = memspace_సమాసం;
      OMP_CLAUSE_ఉపయోగిస్తుంది_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      లేకపోతే
	ఆపు;
    }

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      వెళ్ళు parse_తదుపరి;
    }

 చివర:
  parens.skip_until_దొరికింది_close (parser);
  తిరిగి nl;
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

స్థిర వృక్షం
c_parser_omp_clause_రేఖీయ (c_parser *parser, వృక్షం list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  వృక్షం nl, c, అడుగు;
  గణన omp_clause_రేఖీయ_రకం రకం = OMP_CLAUSE_రేఖీయ_DEFAULT;
  తార్కిక old_రేఖీయ_modifier = అబద్ధం;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (tok->విలువ);
      ఒకవేళ (strcmp ("val", p) == 0)
	రకం = OMP_CLAUSE_రేఖీయ_VAL;
      ఒకవేళ (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	రకం = OMP_CLAUSE_రేఖీయ_DEFAULT;
      ఒకవేళ (రకం != OMP_CLAUSE_రేఖీయ_DEFAULT)
	{
	  old_రేఖీయ_modifier = నిజం;
	  rm1_loc = make_location (tok->location, tok->location,
				   c_parser_peek_2nd_token (parser)->location);
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_రేఖీయ, list);

  ఒకవేళ (రకం != OMP_CLAUSE_రేఖీయ_DEFAULT)
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_దొరికింది_close (parser);
    }

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t సమాసం_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = సమాసం_loc;
      తార్కిక has_modifiers = అబద్ధం;
      ఒకవేళ (రకం == OMP_CLAUSE_రేఖీయ_DEFAULT
	  && c_parser_తదుపరి_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (tok->విలువ);
	  గుర్తులేని పూర్ణాంకం pos = 0;
	  ఒకవేళ (strcmp ("val", p) == 0)
	    pos = 2;
	  లేకపోతే ఒకవేళ (strcmp ("step", p) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      pos = 3;
	      ఒకవేళ (c_parser_check_సమతుల్య_raw_token_sequence (parser, &pos)
		  && (c_parser_peek_nth_token_raw (parser, pos)->type
		      == CPP_CLOSE_PAREN))
		++pos;
	      లేకపోతే
		pos = 0;
	    }
	  ఒకవేళ (pos)
	    {
	      tok = c_parser_peek_nth_token_raw (parser, pos);
	      ఒకవేళ (tok->type == CPP_COMMA || tok->type == CPP_CLOSE_PAREN)
		has_modifiers = నిజం;
	    }
	}
      ఒకవేళ (has_modifiers)
	{
	  అడుగు = NULL_వృక్షం;
	  అయితే (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (tok->విలువ);
	      ఒకవేళ (strcmp ("val", p) == 0)
		{
		  ఒకవేళ (రకం != OMP_CLAUSE_రేఖీయ_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  రకం = OMP_CLAUSE_రేఖీయ_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      లేకపోతే ఒకవేళ (strcmp ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  ఒకవేళ (parens2.require_open (parser))
		    {
		      ఒకవేళ (అడుగు)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      సమాసం_loc = c_parser_peek_token (parser)->location;
		      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
		      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం,
						       నిజం);
		      అడుగు = c_fully_fold (సమాసం.విలువ, అబద్ధం, ఖాళీ);
		      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (అడుగు)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  అడుగు = integer_one_కణుపు;
			}
		      parens2.skip_until_దొరికింది_close (parser);
		    }
		  లేకపోతే
		    ఆపు;
		}
	      లేకపోతే
		ఆపు;
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  కొనసాగు;
		}
	      ఆపు;
	    }
	  ఒకవేళ (!అడుగు)
	    అడుగు = integer_one_కణుపు;
	}
      లేకపోతే
	{
	  c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	  సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
	  అడుగు = c_fully_fold (సమాసం.విలువ, అబద్ధం, ఖాళీ);
	  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (అడుగు)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      అడుగు = integer_one_కణుపు;
	    }
	}

    }
  లేకపోతే
    అడుగు = integer_one_కణుపు;

  కొరకు (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_రేఖీయ_అడుగు (c) = అడుగు;
      OMP_CLAUSE_రేఖీయ_రకం (c) = రకం;
      OMP_CLAUSE_రేఖీయ_OLD_రేఖీయ_MODIFIER (c) = old_రేఖీయ_modifier;
    }

  ఒకవేళ (old_రేఖీయ_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      ఒకవేళ (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.కూడు_fixit_remove (rm1_loc);
	  ఒకవేళ (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.కూడు_fixit_remove (rm2_loc);
	      richloc.కూడు_fixit_చొప్పించు_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.కూడు_fixit_చొప్పించు_before (close_loc, ")");
	    }
	  లేకపోతే
	    richloc.కూడు_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_దొరికింది_close (parser);
  తిరిగి nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_nontemporal (c_parser *parser, వృక్షం list)
{
  తిరిగి c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

స్థిర వృక్షం
c_parser_omp_clause_safelen (c_parser *parser, వృక్షం list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  వృక్షం c, t;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  location_t సమాసం_loc = c_parser_peek_token (parser)->location;
  c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
  సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
  t = సమాసం.విలువ;
  t = c_fully_fold (t, అబద్ధం, ఖాళీ);
  ఒకవేళ (వృక్షం_సంకేతం (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (వృక్షం_TYPE (t))
      || వృక్షం_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_వృక్షం;
    }

  parens.skip_until_దొరికింది_close (parser);
  ఒకవేళ (t == NULL_వృక్షం || t == error_mark_కణుపు)
    తిరిగి list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_సమాసం (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

స్థిర వృక్షం
c_parser_omp_clause_simdlen (c_parser *parser, వృక్షం list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  వృక్షం c, t = NULL_వృక్షం, type = NULL_వృక్షం, భాజకం = NULL_వృక్షం;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  గుర్తులేని pos = 3;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && strcmp (IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ),
		 "scaled") == 0
      && c_parser_check_సమతుల్య_raw_token_sequence (parser, &pos)
      && c_parser_peek_nth_token_raw (parser, ++pos)->type == CPP_COLON)
    {
      c_parser_consume_token (parser);
      matching_parens parens2;
      parens2.require_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      నిర్మాణం c_type_name *ctype = c_parser_type_name (parser);
      ఒకవేళ (ctype == ఖాళీ
	  || (type = groktypename (ctype, ఖాళీ, ఖాళీ)) == ఖాళీ
	  || (!INTEGRAL_TYPE_P (type)
	      && !SCALAR_FLOAT_TYPE_P (type)
	      && వృక్షం_సంకేతం (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	  సమాసం = convert_lvalue_గమ్యం_rvalue (loc, సమాసం, అబద్ధం, నిజం);
	  భాజకం = సమాసం.విలువ;
	  భాజకం = c_fully_fold (భాజకం, అబద్ధం, ఖాళీ);
	  ఒకవేళ (వృక్షం_సంకేతం (భాజకం) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (వృక్షం_TYPE (భాజకం))
	      || వృక్షం_int_cst_sgn (భాజకం) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_కణుపు;
	    }
	}
      parens2.skip_until_దొరికింది_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  ఒకవేళ (type != error_mark_కణుపు)
    {
      location_t సమాసం_loc = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
      t = సమాసం.విలువ;
      t = c_fully_fold (t, అబద్ధం, ఖాళీ);
      ఒకవేళ (వృక్షం_సంకేతం (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (వృక్షం_TYPE (t))
	  || వృక్షం_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_వృక్షం;
	}
    }

  parens.skip_until_దొరికింది_close (parser);
  ఒకవేళ (type == error_mark_కణుపు || t == NULL_వృక్షం || t == error_mark_కణుపు)
    తిరిగి list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_సమాసం (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_భాజకం (c) = భాజకం;
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

స్థిర వృక్షం
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   వృక్షం list, తార్కిక depend_p)
{
  వృక్షం vec = ఖాళీ;
  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_రకం != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      తిరిగి list;
    }

  ఒకవేళ (!depend_p)
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_సంఖ్య
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  వృక్షం val = c_parser_peek_nth_token (parser, 3)->విలువ;
	  ఒకవేళ (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      వృక్షం u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_రకం (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      తిరిగి u;
	    }
	}
    }



  అయితే (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_రకం == C_ID_ID)
    {
      వృక్షం t = lookup_name (c_parser_peek_token (parser)->విలువ);
      వృక్షం addend = ఖాళీ;

      ఒకవేళ (t == NULL_వృక్షం)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->విలువ);
	  t = error_mark_కణుపు;
	}

      c_parser_consume_token (parser);

      తార్కిక neg = అబద్ధం;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_MINUS))
	neg = నిజం;
      లేకపోతే ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_కణుపు;
	  neg = అబద్ధం;
	  వెళ్ళు కూడు_గమ్యం_సదిశ;
	}
      c_parser_consume_token (parser);

      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_సంఖ్య))
	{
	  c_parser_error (parser, "expected integer");
	  తిరిగి list;
	}

      addend = c_parser_peek_token (parser)->విలువ;
      ఒకవేళ (వృక్షం_సంకేతం (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  తిరిగి list;
	}
      c_parser_consume_token (parser);

    కూడు_గమ్యం_సదిశ:
      ఒకవేళ (t != error_mark_కణుపు)
	{
	  vec = వృక్షం_cons (addend, t, vec);
	  ఒకవేళ (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_రకం != C_ID_ID)
	ఆపు;

      c_parser_consume_token (parser);
    }

  ఒకవేళ (vec == NULL_వృక్షం)
    తిరిగి list;

  వృక్షం u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_రకం (u) = OMP_CLAUSE_DOACROSS_SINK;
  OMP_CLAUSE_DOACROSS_DEPEND (u) = depend_p;
  OMP_CLAUSE_DECL (u) = nreverse (vec);
  OMP_CLAUSE_CHAIN (u) = list;
  తిరిగి u;
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

స్థిర వృక్షం
c_parser_omp_iterators (c_parser *parser)
{
  వృక్షం ret = NULL_వృక్షం, *చివరి = &ret;
  c_parser_consume_token (parser);

  నెట్టు_scope ();

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి error_mark_కణుపు;

  చేయి
    {
      వృక్షం iter_type = NULL_వృక్షం, type_సమాసం = NULL_వృక్షం;
      ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_typename (parser, cla_prefer_id))
	{
	  నిర్మాణం c_type_name *type = c_parser_type_name (parser);
	  ఒకవేళ (type != ఖాళీ)
	    iter_type = groktypename (type, &type_సమాసం, ఖాళీ);
	}
      ఒకవేళ (iter_type == NULL_వృక్షం)
	iter_type = integer_type_కణుపు;

      location_t loc = c_parser_peek_token (parser)->location;
      ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  ఆపు;
	}

      వృక్షం id = c_parser_peek_token (parser)->విలువ;
      c_parser_consume_token (parser);

      ఒకవేళ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	ఆపు;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (eloc, సమాసం, నిజం, అబద్ధం);
      వృక్షం begin = సమాసం.విలువ;

      ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ఆపు;

      eloc = c_parser_peek_token (parser)->location;
      సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (eloc, సమాసం, నిజం, అబద్ధం);
      వృక్షం చివర = సమాసం.విలువ;

      వృక్షం అడుగు = integer_one_కణుపు;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	  సమాసం = convert_lvalue_గమ్యం_rvalue (eloc, సమాసం, నిజం, అబద్ధం);
	  అడుగు = సమాసం.విలువ;
	}

      వృక్షం iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *చివరి = make_omp_iterator ();
      OMP_ITERATOR_VAR (*చివరి) = iter_var;
      OMP_ITERATOR_BEGIN (*చివరి) = begin;
      OMP_ITERATOR_చివర (*చివరి) = చివర;
      OMP_ITERATOR_అడుగు (*చివరి) = అడుగు;
      చివరి = &వృక్షం_CHAIN (*చివరి);

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  కొనసాగు;
	}
      ఆపు;
    }
  అయితే (1);

  parens.skip_until_దొరికింది_close (parser);
  తిరిగి ret ? ret : error_mark_కణుపు;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

స్థిర వృక్షం
c_parser_omp_clause_affinity (c_parser *parser, వృక్షం list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  వృక్షం nl, iterators = NULL_వృక్షం;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      తార్కిక parse_iter = ((strcmp ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      ఒకవేళ (parse_iter)
	{
	  గుర్తులేని n = 3;
	  parse_iter = (c_parser_check_సమతుల్య_raw_token_sequence (parser, &n)
			&& (c_parser_peek_nth_token_raw (parser, n)->type
			    == CPP_CLOSE_PAREN)
			&& (c_parser_peek_nth_token_raw (parser, n + 1)->type
			    == CPP_COLON));
	}
      ఒకవేళ (parse_iter)
	{
	  iterators = c_parser_omp_iterators (parser);
	  ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    {
	      ఒకవేళ (iterators)
		తీయి_scope ();
	      parens.skip_until_దొరికింది_close (parser);
	      తిరిగి list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  ఒకవేళ (iterators)
    {
      వృక్షం ఖండం = తీయి_scope ();
      ఒకవేళ (iterators != error_mark_కణుపు)
	{
	  OMP_ITERATOR_ఖండం (iterators) = ఖండం;
	  కొరకు (వృక్షం c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_వృక్షం_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_దొరికింది_close (parser);
  తిరిగి nl;
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

స్థిర వృక్షం
c_parser_omp_clause_depend (c_parser *parser, వృక్షం list, location_t ఇక్కడ)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  గణన omp_clause_depend_రకం రకం = OMP_CLAUSE_DEPEND_చివరి;
  గణన omp_clause_doacross_రకం dkind = OMP_CLAUSE_DOACROSS_చివరి;
  వృక్షం nl, c, iterators = NULL_వృక్షం;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  చేయి
    {
      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
	వెళ్ళు invalid_రకం;

      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp ("iterator", p) == 0 && iterators == NULL_వృక్షం)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  కొనసాగు;
	}
      ఒకవేళ (strcmp ("in", p) == 0)
	రకం = OMP_CLAUSE_DEPEND_లోపల;
      లేకపోతే ఒకవేళ (strcmp ("inout", p) == 0)
	రకం = OMP_CLAUSE_DEPEND_INOUT;
      లేకపోతే ఒకవేళ (strcmp ("inoutset", p) == 0)
	రకం = OMP_CLAUSE_DEPEND_INOUTSET;
      లేకపోతే ఒకవేళ (strcmp ("mutexinoutset", p) == 0)
	రకం = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      లేకపోతే ఒకవేళ (strcmp ("out", p) == 0)
	రకం = OMP_CLAUSE_DEPEND_బహిర్గతం;
      లేకపోతే ఒకవేళ (strcmp ("depobj", p) == 0)
	రకం = OMP_CLAUSE_DEPEND_DEPOBJ;
      లేకపోతే ఒకవేళ (strcmp ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.కూడు_fixit_replace (ఇక్కడ, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      లేకపోతే ఒకవేళ (strcmp ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.కూడు_fixit_replace (ఇక్కడ, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_ఆధారం;
	}
      లేకపోతే
	వెళ్ళు invalid_రకం;
      ఆపు;
    }
  అయితే (1);

  c_parser_consume_token (parser);

  ఒకవేళ (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_ఆధారం
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      తీయి_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_ఆధారం ? "source" : "sink");
      iterators = NULL_వృక్షం;
    }

  ఒకవేళ (dkind == OMP_CLAUSE_DOACROSS_ఆధారం)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_రకం (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_వృక్షం;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_దొరికింది_close (parser);
      తిరిగి c;
    }

  ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    వెళ్ళు resync_fail;

  ఒకవేళ (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, నిజం);
  లేకపోతే
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      ఒకవేళ (iterators)
	{
	  వృక్షం ఖండం = తీయి_scope ();
	  ఒకవేళ (iterators == error_mark_కణుపు)
	    iterators = NULL_వృక్షం;
	  లేకపోతే
	    OMP_ITERATOR_ఖండం (iterators) = ఖండం;
	}

      కొరకు (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_రకం (c) = రకం;
	  ఒకవేళ (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_వృక్షం_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_దొరికింది_close (parser);
  తిరిగి nl;

 invalid_రకం:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_దొరికింది_close (parser);
  ఒకవేళ (iterators)
    తీయి_scope ();
  తిరిగి list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

స్థిర వృక్షం
c_parser_omp_clause_doacross (c_parser *parser, వృక్షం list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  గణన omp_clause_doacross_రకం రకం = OMP_CLAUSE_DOACROSS_చివరి;
  వృక్షం nl;
  స్థిరరాశి అక్షరం *p;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME))
    వెళ్ళు invalid_రకం;

  p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
  ఒకవేళ (strcmp ("sink", p) == 0)
    రకం = OMP_CLAUSE_DOACROSS_SINK;
  లేకపోతే ఒకవేళ (strcmp ("source", p) == 0)
    రకం = OMP_CLAUSE_DOACROSS_ఆధారం;
  లేకపోతే
    వెళ్ళు invalid_రకం;

  c_parser_consume_token (parser);

  ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    వెళ్ళు resync_fail;

  ఒకవేళ (రకం == OMP_CLAUSE_DOACROSS_ఆధారం)
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	  && strcmp (IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_రకం (nl) = OMP_CLAUSE_DOACROSS_ఆధారం;
      OMP_CLAUSE_DECL (nl) = NULL_వృక్షం;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  లేకపోతే
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, అబద్ధం);

  parens.skip_until_దొరికింది_close (parser);
  తిరిగి nl;

 invalid_రకం:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_దొరికింది_close (parser);
  తిరిగి list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

స్థిర వృక్షం
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, వృక్షం list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  గణన omp_clause_fallback_రకం రకం = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  గుర్తులేని n = 3;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_సమతుల్య_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  తిరిగి list;
	}
      c_parser_consume_token (parser);
      ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	తిరిగి list;
      p = "";
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp (p, "abort") == 0)
	రకం = OMP_CLAUSE_FALLBACK_ABORT;
      లేకపోతే ఒకవేళ (strcmp (p, "default_mem") == 0)
	రకం = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      లేకపోతే ఒకవేళ (strcmp (p, "null") == 0)
	రకం = OMP_CLAUSE_FALLBACK_NULL;
      లేకపోతే
	{
	  c_parser_error (parser, "expected %<abort%>, %<default_mem%>, or "
				  "%<null%> as fallback mode");
	  తిరిగి list;
	}
      c_parser_consume_token (parser);
      ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	తిరిగి list;
      ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	తిరిగి list;
    }
  location_t సమాసం_loc = c_parser_peek_token (parser)->location;
  c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
  సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
  వృక్షం కొలత = c_fully_fold (సమాసం.విలువ, అబద్ధం, ఖాళీ);
  parens.skip_until_దొరికింది_close (parser);

  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (కొలత)))
    {
      error_at (సమాసం_loc, "expected integer expression");
      తిరిగి list;
    }

  /* Attempt to statically determine when the number is negative.  */
  వృక్షం c = fold_build2_loc (సమాసం_loc, LT_సమాసం, boolean_type_కణుపు, కొలత,
			    build_int_cst (వృక్షం_TYPE (కొలత), 0));
  protected_సమితి_సమాసం_location (c, సమాసం_loc);
  ఒకవేళ (c == boolean_true_కణుపు)
    {
      warning_at (సమాసం_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      కొలత = integer_zero_కణుపు;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_రకం (c) = రకం;
  OMP_CLAUSE_DYN_GROUPPRIVATE_సమాసం (c) = కొలత;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  తిరిగి list;
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

స్థిర వృక్షం
c_parser_omp_clause_map (c_parser *parser, వృక్షం list, తార్కిక declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  వృక్షం nl, c;
  గణన gomp_map_రకం రకం = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  పూర్ణాంకం pos = 1;
  పూర్ణాంకం map_రకం_pos = 0;
  పూర్ణాంకం iterator_నిడివి = 0;
  కొరకు (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      ఒకవేళ (tok->type != CPP_NAME)
	ఆపు;

      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (tok->విలువ);
      c_token *తదుపరి_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      ఒకవేళ (strcmp (p, "iterator") == 0 && తదుపరి_tok->type == CPP_OPEN_PAREN)
	{
	  గుర్తులేని n = pos + 2;
	  ఒకవేళ (c_parser_check_సమతుల్య_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_నిడివి = n - pos + 1;
	      pos = n;
	      తదుపరి_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      ఒకవేళ (తదుపరి_tok->type == CPP_COLON)
	{
	  map_రకం_pos = pos;
	  ఆపు;
	}

      ఒకవేళ (తదుపరి_tok->type == CPP_COMMA)
	pos++;
      లేకపోతే ఒకవేళ (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  గుర్తులేని పూర్ణాంకం npos = pos + 2;
	  ఒకవేళ (c_parser_check_సమతుల్య_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, npos + 1)->type
		  == CPP_COMMA))
	    pos = npos + 1;
	}

      pos++;
    }

  పూర్ణాంకం always_modifier = 0;
  పూర్ణాంకం close_modifier = 0;
  పూర్ణాంకం present_modifier = 0;
  పూర్ణాంకం mapper_modifier = 0;
  పూర్ణాంకం అంకె_commas = 0;
  పూర్ణాంకం అంకె_identifiers = 0;
  వృక్షం mapper_name = NULL_వృక్షం;
  వృక్షం iterators = NULL_వృక్షం;
  కొరకు (పూర్ణాంకం pos = 1; pos < map_రకం_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      ఒకవేళ (tok->type == CPP_COMMA)
	{
	  ++అంకె_commas;
	  ఒకవేళ (అంకె_commas > అంకె_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  కొనసాగు;
	}

      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (tok->విలువ);
      ఒకవేళ (strcmp ("always", p) == 0)
	{
	  ఒకవేళ (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_దొరికింది_close (parser);
	      తిరిగి list;
	    }
	  always_modifier++;
	  c_parser_consume_token (parser);
	}
      లేకపోతే ఒకవేళ (strcmp ("close", p) == 0)
	{
	  ఒకవేళ (close_modifier)
	    {
	      c_parser_error (parser, "too many %<close%> modifiers");
	      parens.skip_until_దొరికింది_close (parser);
	      తిరిగి list;
	    }
	  close_modifier++;
	  c_parser_consume_token (parser);
	}
      లేకపోతే ఒకవేళ (strcmp ("iterator", p) == 0)
	{
	  ఒకవేళ (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_దొరికింది_close (parser);
	      తిరిగి list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_నిడివి - 1;
	}
      లేకపోతే ఒకవేళ (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  ఒకవేళ (mparens.require_open (parser))
	    {
	      ఒకవేళ (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_దొరికింది_close (parser);
		  తిరిగి list;
		}

	      tok = c_parser_peek_token (parser);

	      ఎంపిక (tok->type)
		{
		స్థితి CPP_NAME:
		  {
		    mapper_name = tok->విలువ;
		    c_parser_consume_token (parser);
		    ఒకవేళ (declare_mapper_p)
		      {
			error_at (tok->location,
				  "in %<declare mapper%> directives, parameter "
				  "to %<mapper%> modifier must be %<default%>");
		      }
		  }
		  ఆపు;

		స్థితి CPP_KEYWORD:
		  ఒకవేళ (tok->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      ఆపు;
		    }
		  /* Fallthrough.  */

		అప్రమేయ:
		  error_at (tok->location,
			    "expected identifier or %<default%>");
		  తిరిగి list;
		}

	      ఒకవేళ (!mparens.require_close (parser))
		{
		  parens.skip_until_దొరికింది_close (parser);
		  తిరిగి list;
		}

	      mapper_modifier++;
	      pos += 3;
	    }
	}
      లేకపోతే ఒకవేళ (strcmp ("present", p) == 0)
	{
	  ఒకవేళ (present_modifier)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_దొరికింది_close (parser);
	      తిరిగి list;
	    }
	  present_modifier++;
	  c_parser_consume_token (parser);
	}
      లేకపోతే
	{
	  c_parser_error (parser, "%<map%> clause with map-type modifier other "
				  "than %<always%>, %<close%>, %<iterator%>, "
				  "%<mapper%> or %<present%>");
	  parens.skip_until_దొరికింది_close (parser);
	  తిరిగి list;
	}
      ++అంకె_identifiers;
      ఒకవేళ (అంకె_identifiers - 1 > అంకె_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.కూడు_fixit_చొప్పించు_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      అంకె_commas = అంకె_identifiers - 1;
    }

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      పూర్ణాంకం always_present_modifier = always_modifier && present_modifier;

      ఒకవేళ (strcmp ("alloc", p) == 0)
	రకం = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      లేకపోతే ఒకవేళ (strcmp ("to", p) == 0)
	రకం = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_గమ్యం
		: present_modifier ? GOMP_MAP_PRESENT_గమ్యం
		: always_modifier ? GOMP_MAP_ALWAYS_గమ్యం
		: GOMP_MAP_గమ్యం);
      లేకపోతే ఒకవేళ (strcmp ("from", p) == 0)
	రకం = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      లేకపోతే ఒకవేళ (strcmp ("tofrom", p) == 0)
	రకం = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      లేకపోతే ఒకవేళ (strcmp ("release", p) == 0)
	రకం = GOMP_MAP_RELEASE;
      లేకపోతే ఒకవేళ (strcmp ("delete", p) == 0)
	రకం = GOMP_MAP_DELETE;
      లేకపోతే
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  తిరిగి list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   నిజం);

  వృక్షం చివరి_new = NULL_వృక్షం;

  ఒకవేళ (iterators)
    {
      వృక్షం ఖండం = తీయి_scope ();
      ఒకవేళ (iterators == error_mark_కణుపు)
	iterators = NULL_వృక్షం;
      లేకపోతే
	OMP_ITERATOR_ఖండం (iterators) = ఖండం;
    }

  కొరకు (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_సమితి_MAP_రకం (c, రకం);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      చివరి_new = c;
    }

  ఒకవేళ (mapper_name)
    {
      వృక్షం name = build_omp_clause (ఆదానం_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_సమితి_MAP_రకం (name, GOMP_MAP_నెట్టు_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (చివరి_new);

      name = build_omp_clause (ఆదానం_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_సమితి_MAP_రకం (name, GOMP_MAP_తీయి_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_సూచిక_కణుపు;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (చివరి_new);
      OMP_CLAUSE_CHAIN (చివరి_new) = name;
    }

  parens.skip_until_దొరికింది_close (parser);
  తిరిగి nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

స్థిర వృక్షం
c_parser_omp_clause_device (c_parser *parser, వృక్షం list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t సమాసం_loc;
  c_సమాసం సమాసం;
  వృక్షం c, t;
  తార్కిక ancestor = అబద్ధం;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (tok->విలువ);
      ఒకవేళ (strcmp ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  ఒకవేళ ((omp_requires_ముసుగు & OMP_REQUIRES_తిరగేయి_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_దొరికింది_close (parser);
	      తిరిగి list;
	    }
	  ancestor = నిజం;
	}
      లేకపోతే ఒకవేళ (strcmp ("device_num", p) == 0)
	;
      లేకపోతే
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_దొరికింది_close (parser);
	  తిరిగి list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  సమాసం_loc = c_parser_peek_token (parser)->location;
  సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
  సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
  t = సమాసం.విలువ;
  t = c_fully_fold (t, అబద్ధం, ఖాళీ);

  parens.skip_until_దొరికింది_close (parser);

  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      తిరిగి list;
    }
  ఒకవేళ (ancestor && వృక్షం_సంకేతం (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (సమాసం_loc, "the %<device%> clause expression must evaluate to "
			  "%<1%>");
      తిరిగి list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE, "device");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE);

  OMP_CLAUSE_DEVICE_ID (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEVICE_ANCESTOR (c) = ancestor;

  list = c;
  తిరిగి list;
}

/* OpenMP 4.0:
   dist_schedule ( static )
   dist_schedule ( static , expression ) */

స్థిర వృక్షం
c_parser_omp_clause_dist_కాలపట్టిక (c_parser *parser, వృక్షం list)
{
  వృక్షం c, t = NULL_వృక్షం;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  ఒకవేళ (!c_parser_తదుపరి_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      తిరిగి list;
    }

  c_parser_consume_token (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t సమాసం_loc = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
      t = సమాసం.విలువ;
      t = c_fully_fold (t, అబద్ధం, ఖాళీ);
      parens.skip_until_దొరికింది_close (parser);
    }
  లేకపోతే
    c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  ఒకవేళ (omp_కనుగొను_clause (list, OMP_CLAUSE_DIST_కాలపట్టిక))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  ఒకవేళ (t == error_mark_కణుపు)
    తిరిగి list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_కాలపట్టిక);
  OMP_CLAUSE_DIST_కాలపట్టిక_CHUNK_సమాసం (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

స్థిర వృక్షం
c_parser_omp_clause_proc_bind (c_parser *parser, వృక్షం list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  గణన omp_clause_proc_bind_రకం రకం;
  వృక్షం c;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp ("primary", p) == 0)
	రకం = OMP_CLAUSE_PROC_BIND_PRIMARY;
      లేకపోతే ఒకవేళ (strcmp ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.కూడు_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  రకం = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      లేకపోతే ఒకవేళ (strcmp ("close", p) == 0)
	రకం = OMP_CLAUSE_PROC_BIND_CLOSE;
      లేకపోతే ఒకవేళ (strcmp ("spread", p) == 0)
	రకం = OMP_CLAUSE_PROC_BIND_విస్తరణ;
      లేకపోతే
	వెళ్ళు invalid_రకం;
    }
  లేకపోతే
    వెళ్ళు invalid_రకం;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_దొరికింది_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_రకం (c) = రకం;
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;

 invalid_రకం:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_దొరికింది_close (parser);
  తిరిగి list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

స్థిర వృక్షం
c_parser_omp_clause_device_type (c_parser *parser, వృక్షం list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  గణన omp_clause_device_type_రకం రకం;
  వృక్షం c;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp ("host", p) == 0)
	రకం = OMP_CLAUSE_DEVICE_TYPE_HOST;
      లేకపోతే ఒకవేళ (strcmp ("nohost", p) == 0)
	రకం = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      లేకపోతే ఒకవేళ (strcmp ("any", p) == 0)
	రకం = OMP_CLAUSE_DEVICE_TYPE_ANY;
      లేకపోతే
	వెళ్ళు invalid_రకం;
    }
  లేకపోతే
    వెళ్ళు invalid_రకం;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_దొరికింది_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_రకం (c) = రకం;
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;

 invalid_రకం:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_దొరికింది_close (parser);
  తిరిగి list;
}

/* OpenMP 4.0:
   from ( variable-list )
   to ( variable-list )

   OpenMP 5.1:
   from ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )
   to ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )

   motion-modifier:
     present | iterator (iterators-definition) | mapper (id)  */

స్థిర వృక్షం
c_parser_omp_clause_from_గమ్యం (c_parser *parser, గణన omp_clause_సంకేతం రకం,
			     వృక్షం list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  పూర్ణాంకం pos = 1, colon_pos = 0;
  పూర్ణాంకం iterator_నిడివి = 0;

  అయితే (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      స్థిరరాశి అక్షరం *identifier =
	IDENTIFIER_సూచిక (c_parser_peek_nth_token_raw (parser, pos)->విలువ);
      ఒకవేళ (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  గుర్తులేని పూర్ణాంకం npos = pos + 2;
	  ఒకవేళ (c_parser_check_సమతుల్య_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      ఒకవేళ (strcmp (identifier, "iterator") == 0)
		iterator_నిడివి = npos - pos + 1;
	      pos = npos;
	    }
	}
      ఒకవేళ (c_parser_peek_nth_token_raw (parser, pos + 1)->type == CPP_COMMA)
	pos += 2;
      లేకపోతే
	pos++;
      ఒకవేళ (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_COLON)
	{
	  colon_pos = pos;
	  ఆపు;
	}
    }

  తార్కిక present = అబద్ధం, mapper_modifier = అబద్ధం;
  వృక్షం iterators = NULL_వృక్షం;
  వృక్షం mapper_name = NULL_వృక్షం;

  కొరకు (పూర్ణాంకం pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      ఒకవేళ (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  కొనసాగు;
	}
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (token->విలువ);
      ఒకవేళ (strcmp ("present", p) == 0)
	{
	  ఒకవేళ (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_దొరికింది_close (parser);
	      తిరిగి list;
	    }
	  present = నిజం;
	  c_parser_consume_token (parser);
	}
      లేకపోతే ఒకవేళ (strcmp ("iterator", p) == 0)
	{
	  ఒకవేళ (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_దొరికింది_close (parser);
	      తిరిగి list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_నిడివి - 1;
	}
      లేకపోతే ఒకవేళ (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  ఒకవేళ (mparens.require_open (parser))
	    {
	      ఒకవేళ (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_దొరికింది_close (parser);
		  తిరిగి list;
		}

	      token = c_parser_peek_token (parser);
	      ఎంపిక (token->type)
		{
		స్థితి CPP_NAME:
		  {
		    mapper_name = token->విలువ;
		    c_parser_consume_token (parser);
		  }
		  ఆపు;
		స్థితి CPP_KEYWORD:
		  ఒకవేళ (token->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      ఆపు;
		    }
		  /* FALLTHROUGH  */
		అప్రమేయ:
		  error_at (token->location,
			    "expected identifier or %<default%>");
		  తిరిగి list;
		}
	      ఒకవేళ (!mparens.require_close (parser))
		{
		  parens.skip_until_దొరికింది_close (parser);
		  తిరిగి list;
		}
	      mapper_modifier = నిజం;
	      pos += 3;
	    }
	}
      లేకపోతే
	{
	  error_at (token->location,
		    "%qs clause with modifier other than %<iterator%>, "
		    "%<mapper%>, or %<present%>",
		    రకం == OMP_CLAUSE_గమ్యం ? "to" : "from");
	  parens.skip_until_దొరికింది_close (parser);
	  తిరిగి list;
	}
    }

  ఒకవేళ (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  వృక్షం nl = c_parser_omp_variable_list (parser, loc, రకం, list);
  parens.skip_until_దొరికింది_close (parser);

  ఒకవేళ (present)
    కొరకు (వృక్షం c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  ఒకవేళ (iterators)
    {
      వృక్షం ఖండం = తీయి_scope ();
      ఒకవేళ (iterators == error_mark_కణుపు)
	iterators = NULL_వృక్షం;
      లేకపోతే
	OMP_ITERATOR_ఖండం (iterators) = ఖండం;
    }

  ఒకవేళ (iterators)
    కొరకు (వృక్షం c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  ఒకవేళ (mapper_name)
    {
      వృక్షం చివరి_new = NULL_వృక్షం;
      కొరకు (వృక్షం c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	చివరి_new = c;

      వృక్షం name = build_omp_clause (ఆదానం_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_సమితి_MAP_రకం (name, GOMP_MAP_నెట్టు_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (చివరి_new);

      name = build_omp_clause (ఆదానం_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_సమితి_MAP_రకం (name, GOMP_MAP_తీయి_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_సూచిక_కణుపు;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (చివరి_new);
      OMP_CLAUSE_CHAIN (చివరి_new) = name;
    }

  తిరిగి nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_ఏకరీతి (c_parser *parser, వృక్షం list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ఏకరీతి,
					 list);
      parens.skip_until_దొరికింది_close (parser);
    }
  తిరిగి list;
}

/* OpenMP 5.1
నిండిన*/

స్థిర వృక్షం
c_parser_omp_clause_నిండిన (c_parser *parser, వృక్షం list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_నిండిన, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  వృక్షం c = build_omp_clause (loc, OMP_CLAUSE_నిండిన);
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

స్థిర వృక్షం
c_parser_omp_clause_partial (c_parser *parser, వృక్షం list)
{
  వృక్షం అంకె = NULL_వృక్షం;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      అంకె = c_parser_సమాసం_no_commas (parser, ఖాళీ).విలువ;
      parens.skip_until_దొరికింది_close (parser);

      ఒకవేళ (అంకె == error_mark_కణుపు)
	తిరిగి list;

      mark_exp_read (అంకె);
      అంకె = c_fully_fold (అంకె, అబద్ధం, ఖాళీ);
      HOST_WIDE_INT n;
      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (అంకె))
	  || !వృక్షం_సరిపోతుంది_shwi_p (అంకె)
	  || (n = వృక్షం_గమ్యం_shwi (అంకె)) <= 0
	  || (పూర్ణాంకం) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  తిరిగి list;
	}
    }

  వృక్షం c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_సమాసం (c) = అంకె;
  OMP_CLAUSE_CHAIN (c) = list;
  తిరిగి c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

స్థిర వృక్షం
c_parser_omp_clause_novariants (c_parser *parser, వృక్షం list)
{
  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
  వృక్షం t = convert_lvalue_గమ్యం_rvalue (loc, సమాసం, నిజం, నిజం).విలువ;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, అబద్ధం, ఖాళీ);
  parens.skip_until_దొరికింది_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  వృక్షం c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_సమాసం (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  తిరిగి list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

స్థిర వృక్షం
c_parser_omp_clause_nocontext (c_parser *parser, వృక్షం list)
{
  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
  వృక్షం t = convert_lvalue_గమ్యం_rvalue (loc, సమాసం, నిజం, నిజం).విలువ;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, అబద్ధం, ఖాళీ);
  parens.skip_until_దొరికింది_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  వృక్షం c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_సమాసం (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  తిరిగి list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

స్థిర వృక్షం
c_parser_omp_clause_detach (c_parser *parser, వృక్షం list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_రకం != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_దొరికింది_close (parser);
      తిరిగి list;
    }

  వృక్షం t = lookup_name (c_parser_peek_token (parser)->విలువ);
  ఒకవేళ (t == NULL_వృక్షం)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->విలువ);
      parens.skip_until_దొరికింది_close (parser);
      తిరిగి list;
    }
  c_parser_consume_token (parser);

  వృక్షం type = TYPE_MAIN_VARIANT (వృక్షం_TYPE (t));
  ఒకవేళ (!INTEGRAL_TYPE_P (type)
      || వృక్షం_సంకేతం (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_దొరికింది_close (parser);
      తిరిగి list;
    }

  వృక్షం u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_దొరికింది_close (parser);
  తిరిగి u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_destroy (c_parser *parser, వృక్షం list)
{
  వృక్షం nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  కొరకు (వృక్షం c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    వృక్షం_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
  తిరిగి nl;
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

స్థిర వృక్షం
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    తిరిగి error_mark_కణుపు;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
    అయితే (నిజం)
      {
	str += (అక్షరం) GOMP_INTEROP_IFR_SEPARATOR;
	ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_STRING))
	  {
	    c_సమాసం cval = c_parser_string_literal (parser, అబద్ధం, అబద్ధం);
	    ఒకవేళ (cval.విలువ == error_mark_కణుపు)
	      తిరిగి error_mark_కణుపు;
	    ఒకవేళ ((కొలత_t) వృక్షం_STRING_నిడివి (cval.విలువ)
		!= అక్షరశ్రేణి_పొడవు (వృక్షం_STRING_సూచిక (cval.విలువ)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = నిజం;
		తిరిగి error_mark_కణుపు;
	      }

	    అక్షరం c = omp_get_fr_id_from_name (వృక్షం_STRING_సూచిక (cval.విలువ));
	    ఒకవేళ (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  వృక్షం_STRING_సూచిక (cval.విలువ));
	    str += c;
	  }
	లేకపోతే
	  {
	    c_సమాసం cval = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	    వృక్షం విలువ = c_fully_fold (cval.విలువ, అబద్ధం, ఖాళీ);
	    ఒకవేళ (INTEGRAL_TYPE_P (వృక్షం_TYPE (విలువ))
		&& వృక్షం_సంకేతం (విలువ) != INTEGER_CST)
	      విలువ = convert_lvalue_గమ్యం_rvalue (cval.get_ప్రారంభం (), cval,
						అబద్ధం, నిజం).విలువ;
	    ఒకవేళ (వృక్షం_సంకేతం (విలువ) != INTEGER_CST
		|| !వృక్షం_సరిపోతుంది_shwi_p (విలువ))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		తిరిగి error_mark_కణుపు;
	      }
	    HOST_WIDE_INT n = వృక్షం_గమ్యం_shwi (విలువ);
	    ఒకవేళ (n < 1 || n > GOMP_INTEROP_IFR_చివరి)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (అక్షరం) n;
	  }
	str += (అక్షరం) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    కొనసాగు;
	  }
	ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  తిరిగి error_mark_కణుపు;
	str += '\0';
	వృక్షం res = build_string (str.నిడివి (), str.దత్తాంశం ());
	వృక్షం_TYPE (res) = build_array_type_nelts (unsigned_char_type_కణుపు,
						  str.నిడివి ());
	తిరిగి res;
      }

  /* New format. */
  std::string str2;
  అయితే (నిజం)
    {
      ఒకవేళ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	తిరిగి error_mark_కణుపు;
      str += (అక్షరం) GOMP_INTEROP_IFR_SEPARATOR;
      str2.clear ();
      తార్కిక has_fr = అబద్ధం;
      అయితే (నిజం)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  ఒకవేళ (tok->type != CPP_NAME
	      || (strcmp("fr", IDENTIFIER_సూచిక (tok->విలువ)) != 0
		  && strcmp("attr", IDENTIFIER_సూచిక (tok->విలువ)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      తిరిగి error_mark_కణుపు;
	    }
	  c_parser_consume_token (parser);
	  తార్కిక is_fr = IDENTIFIER_సూచిక (tok->విలువ)[0] == 'f';
	  ఒకవేళ (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      తిరిగి error_mark_కణుపు;
	    }
	  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    తిరిగి error_mark_కణుపు;
	  అయితే (నిజం)
	    {
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_STRING))
		{
		  c_సమాసం cval = c_parser_string_literal (parser, అబద్ధం, అబద్ధం);
		  వృక్షం విలువ = cval.విలువ;
		  ఒకవేళ (విలువ == error_mark_కణుపు)
		    తిరిగి error_mark_కణుపు;
		  ఒకవేళ ((కొలత_t) వృక్షం_STRING_నిడివి (విలువ)
		      != అక్షరశ్రేణి_పొడవు (వృక్షం_STRING_సూచిక (విలువ)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = నిజం;
		      తిరిగి error_mark_కణుపు;
		    }
		  ఒకవేళ (!is_fr)
		    {
		      ఒకవేళ (!startswith (వృక్షం_STRING_సూచిక (విలువ), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = నిజం;
			  తిరిగి error_mark_కణుపు;
			}
		      ఒకవేళ (strchr (వృక్షం_STRING_సూచిక (విలువ), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = నిజం;
			  తిరిగి error_mark_కణుపు;
			}
		      str2 += వృక్షం_STRING_సూచిక (విలువ);
		      str2 += '\0';
		    }
		  లేకపోతే
		    {
		      ఒకవేళ (*వృక్షం_STRING_సూచిక (విలువ) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  తిరిగి error_mark_కణుపు;
			}
		      అక్షరం c = omp_get_fr_id_from_name (వృక్షం_STRING_సూచిక (విలువ));
		      ఒకవేళ (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    వృక్షం_STRING_సూచిక (విలువ));
		     str += c;
		     has_fr = నిజం;
		    }
		}
	      లేకపోతే ఒకవేళ (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  తిరిగి error_mark_కణుపు;
		}
	      లేకపోతే
		{
		  c_సమాసం cval = c_parser_సమాసం_no_commas (parser, ఖాళీ);
		  వృక్షం విలువ = c_fully_fold (cval.విలువ, అబద్ధం, ఖాళీ);
		  ఒకవేళ (INTEGRAL_TYPE_P (వృక్షం_TYPE (విలువ))
		      && వృక్షం_సంకేతం (విలువ) != INTEGER_CST)
		    విలువ = convert_lvalue_గమ్యం_rvalue (cval.get_ప్రారంభం (), cval,
						      అబద్ధం, నిజం).విలువ;

		  ఒకవేళ (వృక్షం_సంకేతం (విలువ) != INTEGER_CST
		      || !వృక్షం_సరిపోతుంది_shwi_p (విలువ))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      తిరిగి error_mark_కణుపు;
		    }
		  HOST_WIDE_INT n = వృక్షం_గమ్యం_shwi (విలువ);
		  ఒకవేళ (n < 1 || n > GOMP_INTEROP_IFR_చివరి)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (అక్షరం) n;
		  has_fr = నిజం;
		}
	      ఒకవేళ (!is_fr
		  && c_parser_తదుపరి_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  కొనసాగు;
		}
	      ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		తిరిగి error_mark_కణుపు;
	      ఆపు;
	    }
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      కొనసాగు;
	    }
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
	    ఆపు;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  తిరిగి error_mark_కణుపు;
	}
      str += (అక్షరం) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	ఆపు;
      ఒకవేళ (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	తిరిగి error_mark_కణుపు;
    }
  c_parser_consume_token (parser);
  str += '\0';
  వృక్షం res = build_string (str.నిడివి (), str.దత్తాంశం ());
  వృక్షం_TYPE (res) = build_array_type_nelts (unsigned_char_type_కణుపు,
						  str.నిడివి ());
  తిరిగి res;
}

/* OpenMP 5.1
     modifiers of the 'init' clause, used by the 'init' and the
     'append_args' clauses.

   Modifiers:
లక్ష్యం
     targetsync
     prefer_type (preference-specification)

  Returns 'false' if an error has been issued.  */

స్థిర తార్కిక
c_parser_omp_clause_init_modifiers (c_parser *parser, తార్కిక *లక్ష్యం,
				    తార్కిక *targetsync, వృక్షం *prefer_type_వృక్షం)
{
  *లక్ష్యం = అబద్ధం;
  *targetsync = అబద్ధం;
  *prefer_type_వృక్షం = NULL_వృక్షం;

  చేయి
    {
      c_token *tok = c_parser_peek_token (parser);
      ఒకవేళ (tok->type != CPP_NAME)
	వెళ్ళు fail;
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (tok->విలువ);
      ఒకవేళ (strcmp ("targetsync", p) == 0)
	{
	  ఒకవేళ (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = నిజం;
	  c_parser_consume_token (parser);
	}
      లేకపోతే ఒకవేళ (strcmp ("target", p) == 0)
	{
	  ఒకవేళ (*లక్ష్యం)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *లక్ష్యం = నిజం;
	  c_parser_consume_token (parser);
	}
      లేకపోతే ఒకవేళ (strcmp ("prefer_type", p) == 0)
	{
	  ఒకవేళ (*prefer_type_వృక్షం != NULL_వృక్షం)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_వృక్షం = c_parser_omp_modifier_prefer_type (parser);
	  ఒకవేళ (*prefer_type_వృక్షం == error_mark_కణుపు)
	    తిరిగి అబద్ధం;
	}
      లేకపోతే
	వెళ్ళు fail;
      tok = c_parser_peek_token (parser);
      ఒకవేళ (tok->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  కొనసాగు;
	}
      /* Unknown token - either done or an error; handle it in the caller.  */
      తిరిగి నిజం;
    }
  అయితే (నిజం);

fail:
  c_parser_error (parser,
		  "expected %<prefer_type%>, %<target%>, or %<targetsync%>");
  తిరిగి అబద్ధం;
}

/* OpenMP 5.1:
   init ( [init-modifier-list : ] variable-list )

   Modifiers:
లక్ష్యం
     targetsync
     prefer_type (preference-specification) */

స్థిర వృక్షం
c_parser_omp_clause_init (c_parser *parser, వృక్షం list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి list;

  తార్కిక లక్ష్యం = అబద్ధం;
  తార్కిక targetsync = అబద్ధం;
  వృక్షం prefer_type_వృక్షం = NULL_వృక్షం;

  ఒకవేళ (!c_parser_omp_clause_init_modifiers (parser, &లక్ష్యం, &targetsync,
					   &prefer_type_వృక్షం)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      ఒకవేళ (prefer_type_వృక్షం != error_mark_కణుపు)
	parens.skip_until_దొరికింది_close (parser);
      తిరిగి list;
    }

  ఒకవేళ (!లక్ష్యం && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  వృక్షం nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					అబద్ధం);
  parens.skip_until_దొరికింది_close (parser);

  కొరకు (వృక్షం c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      వృక్షం_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      ఒకవేళ (లక్ష్యం)
	OMP_CLAUSE_INIT_లక్ష్యం (c) = 1;
      ఒకవేళ (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      ఒకవేళ (prefer_type_వృక్షం)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_వృక్షం;
    }
  తిరిగి nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_use (c_parser *parser, వృక్షం list)
{
  తిరిగి c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

స్థిర వృక్షం
c_parser_omp_clause_interop (c_parser *parser, వృక్షం list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  వృక్షం nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  కొరకు (వృక్షం c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      వృక్షం_వాడిన (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  తిరిగి nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

స్థిర వృక్షం
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_ముసుగు ముసుగు,
			   స్థిరరాశి అక్షరం *where, తార్కిక ముగింపు_p = నిజం,
			   తార్కిక లక్ష్యం_p = అబద్ధం)
{
  వృక్షం clauses = ఖాళీ;
  తార్కిక మొదటి = నిజం;

  అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t ఇక్కడ;
      pragma_omp_clause c_రకం;
      స్థిరరాశి అక్షరం *c_name;
      వృక్షం prev = clauses;

      ఒకవేళ (!మొదటి && c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      ఇక్కడ = c_parser_peek_token (parser)->location;
      c_రకం = c_parser_omp_clause_name (parser);

      ఎంపిక (c_రకం)
	{
	స్థితి PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (ఇక్కడ, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_దత్తాంశం_clause (parser, c_రకం, clauses);
	  c_name = "attach";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_దత్తాంశం_clause (parser, c_రకం, clauses);
	  c_name = "copy";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_దత్తాంశం_clause (parser, c_రకం, clauses);
	  c_name = "copyin";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_దత్తాంశం_clause (parser, c_రకం, clauses);
	  c_name = "copyout";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_దత్తాంశం_clause (parser, c_రకం, clauses);
	  c_name = "create";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_దత్తాంశం_clause (parser, c_రకం, clauses);
	  c_name = "delete";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, నిజం);
	  c_name = "default";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_దత్తాంశం_clause (parser, c_రకం, clauses);
	  c_name = "detach";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_దత్తాంశం_clause (parser, c_రకం, clauses);
	  c_name = "device";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_దత్తాంశం_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_దత్తాంశం_clause (parser, c_రకం, clauses);
	  c_name = "device_resident";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (ఇక్కడ, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, ఇక్కడ, OMP_CLAUSE_GANG,
						c_name, clauses);
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_దత్తాంశం_clause (parser, c_రకం, clauses);
	  c_name = "host";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, అబద్ధం);
	  c_name = "if";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (ఇక్కడ, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (ఇక్కడ, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_దత్తాంశం_clause (parser, c_రకం, clauses);
	  c_name = "link";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_దత్తాంశం_clause (parser, c_రకం, clauses);
	  c_name = "no_create";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (ఇక్కడ, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_అంకె_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_అంకె_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_అంకె_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_అంకె_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_దత్తాంశం_clause (parser, c_రకం, clauses);
	  c_name = "present";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_వ్యక్తిగత:
	  clauses = c_parser_omp_clause_వ్యక్తిగత (parser, clauses);
	  c_name = "private";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     అబద్ధం, clauses);
	  c_name = "reduction";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_SELF:
	  ఒకవేళ ((ముసుగు & (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  లేకపోతే
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_దత్తాంశం_clause (parser, c_రకం, clauses);
	  c_name = "self";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (ఇక్కడ, OMP_CLAUSE_SEQ,
						 clauses);
	  c_name = "seq";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_TILE:
	  clauses = c_parser_oacc_clause_tile (parser, clauses);
	  c_name = "tile";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_USE_DEVICE:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_సదిశ:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, ఇక్కడ, OMP_CLAUSE_సదిశ,
						c_name,	clauses);
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_సదిశ_నిడివి:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_సదిశ_నిడివి,
						     clauses);
	  c_name = "vector_length";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  ఆపు;
	స్థితి PRAGMA_OACC_CLAUSE_కార్మికుడు:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, ఇక్కడ, OMP_CLAUSE_కార్మికుడు,
						c_name, clauses);
	  ఆపు;
	అప్రమేయ:
	  c_parser_error (parser, "expected an OpenACC clause");
	  వెళ్ళు saw_error;
	}

      మొదటి = అబద్ధం;

      ఒకవేళ (((ముసుగు >> c_రకం) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (ఇక్కడ, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_గమ్యం_pragma_eol (parser);

  ఒకవేళ (ముగింపు_p)
    తిరిగి c_ముగింపు_omp_clauses (clauses, లక్ష్యం_p ? C_ORT_ACC_లక్ష్యం
						   : C_ORT_ACC);

  తిరిగి clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

స్థిర వృక్షం
c_parser_omp_all_clauses (c_parser *parser, omp_clause_ముసుగు ముసుగు,
			  స్థిరరాశి అక్షరం *where, తార్కిక ముగింపు_p = నిజం,
			  పూర్ణాంకం nested = 0)
{
  వృక్షం clauses = ఖాళీ;
  తార్కిక మొదటి = నిజం;

  అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t ఇక్కడ;
      pragma_omp_clause c_రకం;
      స్థిరరాశి అక్షరం *c_name;
      వృక్షం prev = clauses;

      ఒకవేళ (nested && c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	ఆపు;

      ఒకవేళ (!మొదటి || nested != 2)
	{
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  లేకపోతే ఒకవేళ (nested == 2)
	    error_at (c_parser_peek_token (parser)->location,
		      "clauses in %<simd%> trait should be separated "
		      "by %<,%>");
	}

      ఇక్కడ = c_parser_peek_token (parser)->location;
      c_రకం = c_parser_omp_clause_name (parser);

      ఎంపిక (c_రకం)
	{
	స్థితి PRAGMA_OMP_CLAUSE_BIND:
	  clauses = c_parser_omp_clause_bind (parser, clauses);
	  c_name = "bind";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, అబద్ధం);
	  c_name = "default";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_DETACH:
	  clauses = c_parser_omp_clause_detach (parser, clauses);
	  c_name = "detach";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_FILTER:
	  clauses = c_parser_omp_clause_filter (parser, clauses);
	  c_name = "filter";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_FINAL:
	  clauses = c_parser_omp_clause_final (parser, clauses);
	  c_name = "final";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_GRAINSIZE:
	  clauses = c_parser_omp_clause_grainsize (parser, clauses);
	  c_name = "grainsize";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_HINT:
	  clauses = c_parser_omp_clause_hint (parser, clauses);
	  c_name = "hint";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_DEFAULTMAP:
	  clauses = c_parser_omp_clause_defaultmap (parser, clauses);
	  c_name = "defaultmap";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, నిజం);
	  c_name = "if";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_లోపల_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_లోపల_REDUCTION,
					     నిజం, clauses);
	  c_name = "in_reduction";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_పరోక్ష:
	  clauses = c_parser_omp_clause_పరోక్ష (parser, clauses);
	  c_name = "indirect";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_MERGEABLE:
	  clauses = c_parser_omp_clause_mergeable (parser, clauses);
	  c_name = "mergeable";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_అంకె_TASKS:
	  clauses = c_parser_omp_clause_అంకె_tasks (parser, clauses);
	  c_name = "num_tasks";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_అంకె_దారాలు:
	  clauses = c_parser_omp_clause_అంకె_దారాలు (parser, clauses);
	  c_name = "num_threads";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_క్రమం:
	  clauses = c_parser_omp_clause_క్రమం (parser, clauses);
	  c_name = "order";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_ప్రాధాన్యత:
	  clauses = c_parser_omp_clause_ప్రాధాన్యత (parser, clauses);
	  c_name = "priority";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_వ్యక్తిగత:
	  clauses = c_parser_omp_clause_వ్యక్తిగత (parser, clauses);
	  c_name = "private";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     నిజం, clauses);
	  c_name = "reduction";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_కాలపట్టిక:
	  clauses = c_parser_omp_clause_కాలపట్టిక (parser, clauses);
	  c_name = "schedule";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     నిజం, clauses);
	  c_name = "task_reduction";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_UNTIED:
	  clauses = c_parser_omp_clause_untied (parser, clauses);
	  c_name = "untied";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_INBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_INBRANCH,
						clauses);
	  c_name = "inbranch";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_NONTEMPORAL:
	  clauses = c_parser_omp_clause_nontemporal (parser, clauses);
	  c_name = "nontemporal";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_NOTINBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_NOTINBRANCH,
						clauses);
	  c_name = "notinbranch";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_PARALLEL:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_PARALLEL,
					      clauses);
	  c_name = "parallel";
	  ఒకవేళ (!మొదటి)
	    {
	     clause_not_మొదటి:
	      error_at (ఇక్కడ, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = prev;
	    }
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  ఒకవేళ (!మొదటి)
	    వెళ్ళు clause_not_మొదటి;
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  ఒకవేళ (!మొదటి)
	    వెళ్ళు clause_not_మొదటి;
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  ఒకవేళ (!మొదటి)
	    వెళ్ళు clause_not_మొదటి;
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_LINK:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LINK, clauses);
	  c_name = "link";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_LOCAL:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LOCAL, clauses);
	  c_name = "local";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_గమ్యం:
	  ఒకవేళ ((ముసుగు & (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (ఇక్కడ);
	      richloc.కూడు_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      వృక్షం nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      కొరకు (వృక్షం c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_గమ్యం (c) = 1;
	      clauses = nl;
	    }
	  లేకపోతే
	    clauses = c_parser_omp_clause_from_గమ్యం (parser, OMP_CLAUSE_గమ్యం,
						   clauses);
	  c_name = "to";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_గమ్యం (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_ఏకరీతి:
	  clauses = c_parser_omp_clause_ఏకరీతి (parser, clauses);
	  c_name = "uniform";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_అంకె_TEAMS:
	  clauses = c_parser_omp_clause_అంకె_teams (parser, clauses);
	  c_name = "num_teams";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_THREAD_హద్దు:
	  clauses = c_parser_omp_clause_thread_హద్దు (parser, clauses);
	  c_name = "thread_limit";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_ALIGNED:
	  clauses = c_parser_omp_clause_aligned (parser, clauses);
	  c_name = "aligned";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_ALLOCATE:
	  clauses = c_parser_omp_clause_allocate (parser, clauses);
	  c_name = "allocate";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_రేఖీయ:
	  clauses = c_parser_omp_clause_రేఖీయ (parser, clauses);
	  c_name = "linear";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_ఉపయోగిస్తుంది_ALLOCATORS:
	  clauses = c_parser_omp_clause_ఉపయోగిస్తుంది_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, ఇక్కడ);
	  c_name = "depend";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_DOACROSS:
	  clauses = c_parser_omp_clause_doacross (parser, clauses);
	  c_name = "doacross";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_DESTROY:
	  clauses = c_parser_omp_clause_destroy (parser, clauses);
	  c_name = "destroy";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE:
	  clauses = c_parser_omp_clause_dyn_groupprivate (parser, clauses);
	  c_name = "dyn_groupprivate";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_INIT:
	  clauses = c_parser_omp_clause_init (parser, clauses);
	  c_name = "init";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_USE:
	  clauses = c_parser_omp_clause_use (parser, clauses);
	  c_name = "use";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_INTEROP:
	  clauses = c_parser_omp_clause_interop (parser, clauses);
	  c_name = "interop";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_MAP:
	  clauses = c_parser_omp_clause_map (parser, clauses, అబద్ధం);
	  c_name = "map";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device_ptr";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_use_device_addr (parser, clauses);
	  c_name = "use_device_addr";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_has_device_addr (parser, clauses);
	  c_name = "has_device_addr";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR:
	  clauses = c_parser_omp_clause_is_device_ptr (parser, clauses);
	  c_name = "is_device_ptr";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_DEVICE:
	  clauses = c_parser_omp_clause_device (parser, clauses);
	  c_name = "device";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_DIST_కాలపట్టిక:
	  clauses = c_parser_omp_clause_dist_కాలపట్టిక (parser, clauses);
	  c_name = "dist_schedule";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_PROC_BIND:
	  clauses = c_parser_omp_clause_proc_bind (parser, clauses);
	  c_name = "proc_bind";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_DEVICE_TYPE:
	  clauses = c_parser_omp_clause_device_type (parser, clauses);
	  c_name = "device_type";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_SAFELEN:
	  clauses = c_parser_omp_clause_safelen (parser, clauses);
	  c_name = "safelen";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_SIMDLEN:
	  clauses = c_parser_omp_clause_simdlen (parser, clauses);
	  c_name = "simdlen";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_NOGROUP:
	  clauses = c_parser_omp_clause_nogroup (parser, clauses);
	  c_name = "nogroup";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_దారాలు:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_దారాలు,
					       clauses);
	  c_name = "threads";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_SIMD:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_SIMD,
					       clauses);
	  c_name = "simd";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_ENTER:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					    clauses);
	  c_name = "enter";
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_నిండిన:
	  c_name = "full";
	  clauses = c_parser_omp_clause_నిండిన (parser, clauses);
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_PARTIAL:
	  c_name = "partial";
	  clauses = c_parser_omp_clause_partial (parser, clauses);
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_NOVARIANTS:
	  c_name = "novariants";
	  clauses = c_parser_omp_clause_novariants (parser, clauses);
	  ఆపు;
	స్థితి PRAGMA_OMP_CLAUSE_NOCONTEXT:
	  c_name = "nocontext";
	  clauses = c_parser_omp_clause_nocontext (parser, clauses);
	  ఆపు;
	అప్రమేయ:
	  c_parser_error (parser, "expected an OpenMP clause");
	  వెళ్ళు saw_error;
	}

      మొదటి = అబద్ధం;

      ఒకవేళ (((ముసుగు >> c_రకం) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (ఇక్కడ, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  ఒకవేళ (!nested)
    c_parser_skip_గమ్యం_pragma_eol (parser);

  ఒకవేళ (ముగింపు_p)
    {
      ఒకవేళ ((ముసుగు & (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ఏకరీతి)) != 0)
	తిరిగి c_ముగింపు_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      ఒకవేళ ((ముసుగు & (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	తిరిగి c_ముగింపు_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      తిరిగి c_ముగింపు_omp_clauses (clauses, C_ORT_OMP);
    }

  తిరిగి clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

స్థిర వృక్షం
c_parser_omp_structured_ఖండం (c_parser *parser, తార్కిక *if_p)
{
  వృక్షం stmt = నెట్టు_stmt_list ();
  parser->omp_attrs_forbidden_p = నిజం;
  c_parser_statement (parser, if_p);
  తిరిగి తీయి_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

స్థిర వృక్షం
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  వృక్షం stmt, clauses = NULL_వృక్షం;
  తార్కిక readonly = అబద్ధం;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      ఒకవేళ (token->type == CPP_NAME
	  && !strcmp (IDENTIFIER_సూచిక (token->విలువ), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = నిజం;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_వృక్షం);
      parens.skip_until_దొరికింది_close (parser);
    }

  ఒకవేళ (readonly)
    కొరకు (వృక్షం c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_ముగింపు_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_గమ్యం_pragma_eol (parser);

  stmt = make_కణుపు (OACC_CACHE);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  సమితి_సమాసం_LOCATION (stmt, loc);
  కూడు_stmt (stmt);

  తిరిగి stmt;
}

/* OpenACC 2.0:
   # pragma acc data oacc-data-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#నిర్వచించు OACC_దత్తాంశం_CLAUSE_ముసుగు						\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_PRESENT))

స్థిర వృక్షం
c_parser_oacc_దత్తాంశం (location_t loc, c_parser *parser, తార్కిక *if_p)
{
  వృక్షం stmt, clauses, ఖండం;

  clauses = c_parser_oacc_all_clauses (parser, OACC_దత్తాంశం_CLAUSE_ముసుగు,
				       "#pragma acc data");

  ఖండం = c_begin_omp_parallel ();
  కూడు_stmt (c_parser_omp_structured_ఖండం (parser, if_p));

  stmt = c_ముగింపు_oacc_దత్తాంశం (loc, clauses, ఖండం);

  తిరిగి stmt;
}

/* OpenACC 2.0:
   # pragma acc declare oacc-data-clause[optseq] new-line
*/

#నిర్వచించు OACC_DECLARE_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_LINK)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_PRESENT))

స్థిర శూన్య
c_parser_oacc_declare (c_parser *parser)
{
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  వృక్షం clauses, stmt, t, decl;

  తార్కిక error = అబద్ధం;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_ముసుగు,
				       "#pragma acc declare");
  ఒకవేళ (!clauses)
    {
      error_at (pragma_loc,
		"no valid clauses specified in %<#pragma acc declare%>");
      తిరిగి;
    }

  కొరకు (t = clauses; t; t = OMP_CLAUSE_CHAIN (t))
    {
      location_t loc = OMP_CLAUSE_LOCATION (t);
      decl = OMP_CLAUSE_DECL (t);
      ఒకవేళ (!DECL_P (decl))
	{
	  error_at (loc, "array section in %<#pragma acc declare%>");
	  error = నిజం;
	  కొనసాగు;
	}

      ఎంపిక (OMP_CLAUSE_MAP_రకం (t))
	{
	స్థితి GOMP_MAP_FIRSTPRIVATE_సూచిక:
	స్థితి GOMP_MAP_ALLOC:
	స్థితి GOMP_MAP_గమ్యం:
	స్థితి GOMP_MAP_FORCE_DEVICEPTR:
	స్థితి GOMP_MAP_DEVICE_RESIDENT:
	  ఆపు;

	స్థితి GOMP_MAP_LINK:
	  ఒకవేళ (!global_bindings_p ()
	      && (వృక్షం_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = నిజం;
	      కొనసాగు;
	    }
	  ఆపు;

	అప్రమేయ:
	  ఒకవేళ (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = నిజం;
	      కొనసాగు;
	    }
	  ఒకవేళ (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = నిజం;
	      కొనసాగు;
	    }
	  లేకపోతే ఒకవేళ (వృక్షం_ప్రజా (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = నిజం;
	      కొనసాగు;
	    }
	  ఆపు;
	}

      ఒకవేళ (!c_check_లోపల_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = నిజం;
	  కొనసాగు;
	}

      ఒకవేళ (lookup_attribute ("omp declare target", DECL_లక్షణాలు (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_లక్షణాలు (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = నిజం;
	  కొనసాగు;
	}

      ఒకవేళ (!error)
	{
	  వృక్షం id;

	  ఒకవేళ (OMP_CLAUSE_MAP_రకం (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  లేకపోతే
	    id = get_identifier ("omp declare target");

	  DECL_లక్షణాలు (decl)
			   = వృక్షం_cons (id, NULL_వృక్షం, DECL_లక్షణాలు (decl));

	  ఒకవేళ (global_bindings_p ())
	    {
	      symtab_కణుపు *కణుపు = symtab_కణుపు::get (decl);
	      ఒకవేళ (కణుపు != ఖాళీ)
		{
		  కణుపు->offloadable = 1;
		  ఒకవేళ (ENABLE_OFFLOADING)
		    {
		      g->have_offload = నిజం;
		      ఒకవేళ (is_a <varpool_కణుపు *> (కణుపు))
			vec_సురక్షిత_నెట్టు (offload_vars, decl);
		    }
		}
	    }
	}
    }

  ఒకవేళ (error || global_bindings_p ())
    తిరిగి;

  stmt = make_కణుపు (OACC_DECLARE);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  సమితి_సమాసం_LOCATION (stmt, pragma_loc);

  కూడు_stmt (stmt);

  తిరిగి;
}

/* OpenACC 2.0:
   # pragma acc enter data oacc-enter-data-clause[optseq] new-line

   or

   # pragma acc exit data oacc-exit-data-clause[optseq] new-line


   LOC is the location of the #pragma token.
*/

#నిర్వచించు OACC_ENTER_దత్తాంశం_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#నిర్వచించు OACC_EXIT_దత్తాంశం_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_DELETE) 		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_DETACH) 		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_FINALIZE) 		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_WAIT) )

స్థిర శూన్య
c_parser_oacc_enter_exit_దత్తాంశం (c_parser *parser, తార్కిక enter)
{
  location_t loc = c_parser_peek_token (parser)->location;
  వృక్షం clauses, stmt;
  స్థిరరాశి అక్షరం *p = "";

  c_parser_consume_pragma (parser);

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      c_parser_consume_token (parser);
    }

  ఒకవేళ (strcmp (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = నిజం;
      c_parser_skip_గమ్యం_pragma_eol (parser);
      తిరిగి;
    }

  ఒకవేళ (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_దత్తాంశం_CLAUSE_ముసుగు,
					 "#pragma acc enter data");
  లేకపోతే
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_దత్తాంశం_CLAUSE_ముసుగు,
					 "#pragma acc exit data");

  ఒకవేళ (omp_కనుగొను_clause (clauses, OMP_CLAUSE_MAP) == NULL_వృక్షం)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      తిరిగి;
    }

  stmt = enter ? make_కణుపు (OACC_ENTER_దత్తాంశం) : make_కణుపు (OACC_EXIT_దత్తాంశం);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  సమితి_సమాసం_LOCATION (stmt, loc);
  కూడు_stmt (stmt);
}


/* OpenACC 2.0:
   # pragma acc host_data oacc-data-clause[optseq] new-line
     structured-block
*/

#నిర్వచించు OACC_HOST_దత్తాంశం_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_USE_DEVICE)          \
	 | (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_IF)                  \
	 | (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_IF_PRESENT) )

స్థిర వృక్షం
c_parser_oacc_host_దత్తాంశం (location_t loc, c_parser *parser, తార్కిక *if_p)
{
  వృక్షం stmt, clauses, ఖండం;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_దత్తాంశం_CLAUSE_ముసుగు,
				       "#pragma acc host_data", అబద్ధం);
  ఒకవేళ (!omp_కనుగొను_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      తిరిగి error_mark_కణుపు;
    }
  clauses = c_ముగింపు_omp_clauses (clauses, C_ORT_ACC);
  ఖండం = c_begin_omp_parallel ();
  కూడు_stmt (c_parser_omp_structured_ఖండం (parser, if_p));
  stmt = c_ముగింపు_oacc_host_దత్తాంశం (loc, clauses, ఖండం);
  తిరిగి stmt;
}


/* OpenACC 2.0:

   # pragma acc loop oacc-loop-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#నిర్వచించు OACC_LOOP_CLAUSE_ముసుగు						\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COLLAPSE)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_వ్యక్తిగత)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_GANG)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_కార్మికుడు)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_సదిశ)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_AUTO)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_INDEPENDENT) 	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_SEQ)			\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_TILE) )
స్థిర వృక్షం
c_parser_oacc_loop (location_t loc, c_parser *parser, అక్షరం *p_name,
		    omp_clause_ముసుగు ముసుగు, వృక్షం *cclauses, తార్కిక *if_p)
{
  తార్కిక is_parallel = ((ముసుగు >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  strcat (p_name, " loop");
  ముసుగు |= OACC_LOOP_CLAUSE_ముసుగు;

  వృక్షం clauses = c_parser_oacc_all_clauses (parser, ముసుగు, p_name,
					    /*finish_p=*/cclauses == ఖాళీ,
					    /*target=*/is_parallel);
  ఒకవేళ (cclauses)
    {
      clauses = c_oacc_విభజించు_loop_clauses (clauses, cclauses, is_parallel);
      ఒకవేళ (*cclauses)
	*cclauses = c_ముగింపు_omp_clauses (*cclauses, C_ORT_ACC_లక్ష్యం);
      ఒకవేళ (clauses)
	clauses = c_ముగింపు_omp_clauses (clauses, C_ORT_ACC);
    }

  వృక్షం ఖండం = c_begin_compound_stmt (నిజం);
  వృక్షం stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, ఖాళీ,
				     if_p);
  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
  కూడు_stmt (ఖండం);

  తిరిగి stmt;
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

#నిర్వచించు OACC_KERNELS_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_అంకె_GANGS)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_అంకె_WORKERS)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_సదిశ_నిడివి)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#నిర్వచించు OACC_PARALLEL_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_వ్యక్తిగత)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_అంకె_GANGS)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_అంకె_WORKERS)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_సదిశ_నిడివి)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#నిర్వచించు OACC_SERIAL_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_వ్యక్తిగత)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_WAIT) )

స్థిర వృక్షం
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       గణన pragma_రకం p_రకం, అక్షరం *p_name, తార్కిక *if_p)
{
  omp_clause_ముసుగు ముసుగు;
  గణన వృక్షం_సంకేతం_2 సంకేతం_2;
  ఎంపిక (p_రకం)
    {
    స్థితి PRAGMA_OACC_KERNELS:
      strcat (p_name, " kernels");
      ముసుగు = OACC_KERNELS_CLAUSE_ముసుగు;
      సంకేతం_2 = OACC_KERNELS;
      ఆపు;
    స్థితి PRAGMA_OACC_PARALLEL:
      strcat (p_name, " parallel");
      ముసుగు = OACC_PARALLEL_CLAUSE_ముసుగు;
      సంకేతం_2 = OACC_PARALLEL;
      ఆపు;
    స్థితి PRAGMA_OACC_SERIAL:
      strcat (p_name, " serial");
      ముసుగు = OACC_SERIAL_CLAUSE_ముసుగు;
      సంకేతం_2 = OACC_SERIAL;
      ఆపు;
    అప్రమేయ:
      gcc_unreachable ();
    }

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  వృక్షం ఖండం = c_begin_omp_parallel ();
	  వృక్షం clauses;
	  c_parser_oacc_loop (loc, parser, p_name, ముసుగు, &clauses, if_p);
	  తిరిగి c_ముగింపు_omp_construct (loc, సంకేతం_2, ఖండం, clauses);
	}
    }

  వృక్షం clauses = c_parser_oacc_all_clauses (parser, ముసుగు, p_name,
					    /*finish_p=*/నిజం,
					    /*target=*/నిజం);

  వృక్షం ఖండం = c_begin_omp_parallel ();
  కూడు_stmt (c_parser_omp_structured_ఖండం (parser, if_p));

  తిరిగి c_ముగింపు_omp_construct (loc, సంకేతం_2, ఖండం, clauses);
}

/* OpenACC 2.0:
   # pragma acc routine oacc-routine-clause[optseq] new-line
     function-definition

   # pragma acc routine ( name ) oacc-routine-clause[optseq] new-line
*/

#నిర్వచించు OACC_ROUTINE_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_GANG)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_కార్మికుడు)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_సదిశ)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_SEQ)			\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_NOHOST) )

/* Parse an OpenACC routine directive.  For named directives, we apply
   immediately to the named function.  For unnamed ones we then parse
   a declaration or definition, which must be for a function.  */

స్థిర శూన్య
c_parser_oacc_routine (c_parser *parser, గణన pragma_context context)
{
  gcc_checking_assert (context == pragma_external);

  oacc_routine_దత్తాంశం దత్తాంశం;
  దత్తాంశం.error_చూసిన = అబద్ధం;
  దత్తాంశం.fndecl_చూసిన = అబద్ధం;
  దత్తాంశం.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      వృక్షం decl = NULL_వృక్షం;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      ఒకవేళ (name_token->type == CPP_NAME
	  && (name_token->id_రకం == C_ID_ID
	      || name_token->id_రకం == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->విలువ);
	  ఒకవేళ (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->విలువ);
	  c_parser_consume_token (parser);
	}
      లేకపోతే
	c_parser_error (parser, "expected function name");

      ఒకవేళ (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	  తిరిగి;
	}

      దత్తాంశం.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_ముసుగు,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      దత్తాంశం.clauses = nreverse (దత్తాంశం.clauses);

      ఒకవేళ (వృక్షం_సంకేతం (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  తిరిగి;
	}

      c_ముగింపు_oacc_routine (&దత్తాంశం, decl, అబద్ధం);
    }
  లేకపోతే /* No optional '( name )'.  */
    {
      దత్తాంశం.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_ముసుగు,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      దత్తాంశం.clauses = nreverse (దత్తాంశం.clauses);

      /* Emit a helpful diagnostic if there's another pragma following this
	 one.  Also don't allow a static assertion declaration, as in the
	 following we'll just parse a *single* "declaration or function
	 definition", and the static assertion counts an one.  */
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_PRAGMA)
	  || c_parser_తదుపరి_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (దత్తాంశం.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  తిరిగి;
	}

      /* We only have to consider the pragma_external case here.  */
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  పూర్ణాంకం ext = disable_extension_diagnostics ();
	  చేయి
	    c_parser_consume_token (parser);
	  అయితే (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, నిజం, నిజం, నిజం, అబద్ధం, నిజం,
					 అబద్ధం, ఖాళీ, ఖాళీ, అబద్ధం, ఖాళీ, &దత్తాంశం);
	  restore_extension_diagnostics (ext);
	}
      లేకపోతే
	c_parser_declaration_or_fndef (parser, నిజం, నిజం, నిజం, అబద్ధం, నిజం,
				       అబద్ధం, ఖాళీ, ఖాళీ, అబద్ధం, ఖాళీ, &దత్తాంశం);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

స్థిర శూన్య
c_ముగింపు_oacc_routine (నిర్మాణం oacc_routine_దత్తాంశం *దత్తాంశం, వృక్షం fndecl,
		       తార్కిక is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  ఒకవేళ (దత్తాంశం->error_చూసిన
      || fndecl == error_mark_కణుపు)
    తిరిగి;

  ఒకవేళ (దత్తాంశం->fndecl_చూసిన)
    {
      error_at (దత్తాంశం->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      దత్తాంశం->error_చూసిన = నిజం;
      తిరిగి;
    }
  ఒకవేళ (fndecl == NULL_వృక్షం || వృక్షం_సంకేతం (fndecl) != FUNCTION_DECL)
    {
      error_at (దత్తాంశం->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      దత్తాంశం->error_చూసిన = నిజం;
      తిరిగి;
    }

  పూర్ణాంకం compatible
    = oacc_verify_routine_clauses (fndecl, &దత్తాంశం->clauses, దత్తాంశం->loc,
				   "#pragma acc routine");
  ఒకవేళ (compatible < 0)
    {
      దత్తాంశం->error_చూసిన = నిజం;
      తిరిగి;
    }
  ఒకవేళ (compatible > 0)
    {
    }
  లేకపోతే
    {
      ఒకవేళ (వృక్షం_వాడిన (fndecl) || (!is_defn && DECL_SAVED_వృక్షం (fndecl)))
	{
	  error_at (దత్తాంశం->loc,
		    వృక్షం_వాడిన (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  దత్తాంశం->error_చూసిన = నిజం;
	  తిరిగి;
	}

      /* Set the routine's level of parallelism.  */
      వృక్షం dims = oacc_build_routine_dims (దత్తాంశం->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_లక్షణాలు (fndecl)
	= వృక్షం_cons (get_identifier ("omp declare target"),
		     దత్తాంశం->clauses, DECL_లక్షణాలు (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  దత్తాంశం->fndecl_చూసిన = నిజం;
}

/* OpenACC 2.0:
   # pragma acc update oacc-update-clause[optseq] new-line
*/

#నిర్వచించు OACC_UPDATE_CLAUSE_ముసుగు						\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_DEVICE)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_HOST)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_IF_PRESENT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_WAIT) )

స్థిర శూన్య
c_parser_oacc_update (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  వృక్షం clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_ముసుగు,
					    "#pragma acc update");
  ఒకవేళ (omp_కనుగొను_clause (clauses, OMP_CLAUSE_MAP) == NULL_వృక్షం)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      తిరిగి;
    }

  ఒకవేళ (parser->error)
    తిరిగి;

  వృక్షం stmt = make_కణుపు (OACC_UPDATE);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  సమితి_సమాసం_LOCATION (stmt, loc);
  కూడు_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#నిర్వచించు OACC_WAIT_CLAUSE_ముసుగు						\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OACC_CLAUSE_IF) )

స్థిర వృక్షం
c_parser_oacc_wait (location_t loc, c_parser *parser, అక్షరం *p_name)
{
  వృక్షం clauses, list = NULL_వృక్షం, stmt = NULL_వృక్షం;

  ఒకవేళ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  strcpy (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_ముసుగు, p_name);
  stmt = c_ముగింపు_oacc_wait (loc, list, clauses);
  కూడు_stmt (stmt);

  తిరిగి stmt;
}

నిర్మాణం c_omp_loc_వృక్షం
{
  location_t loc;
  వృక్షం var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
స్థిర వృక్షం
c_check_omp_allocate_allocator_r (వృక్షం *tp, పూర్ణాంకం *, శూన్య *దత్తాంశం)
{
  వృక్షం var = ((నిర్మాణం c_omp_loc_వృక్షం *) దత్తాంశం)->var;
  location_t loc = ((నిర్మాణం c_omp_loc_వృక్షం *) దత్తాంశం)->loc;
  ఒకవేళ (వృక్షం_సంకేతం (*tp) == VAR_DECL && c_check_లోపల_current_scope (*tp))
    {
      ఒకవేళ (linemap_location_before_p (పంక్తి_పట్టిక, DECL_ఆధారం_LOCATION (var),
				     DECL_ఆధారం_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_ఆధారం_LOCATION (*tp), "declared here");
	  inform (DECL_ఆధారం_LOCATION (var),
		  "to be allocated variable declared here");
	  తిరిగి *tp;
	}
      లేకపోతే
	{
	  gcc_assert (cur_stmt_list
		      && వృక్షం_సంకేతం (cur_stmt_list) == STATEMENT_LIST);

	  వృక్షం_stmt_iterator l = tsi_చివరి (cur_stmt_list);
	  అయితే (!tsi_చివర_p (l))
	    {
	      ఒకవేళ (linemap_location_before_p (పంక్తి_పట్టిక, సమాసం_LOCATION (*l),
					     DECL_ఆధారం_LOCATION (var)))
		  ఆపు;
	      ఒకవేళ (వృక్షం_సంకేతం (*l) == MODIFY_సమాసం
		  && వృక్షం_నిర్వాహ్యం (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (సమాసం_LOCATION (*l), "modified here");
		  inform (DECL_ఆధారం_LOCATION (var),
			  "to be allocated variable declared here");
		  తిరిగి *tp;
		}
	      --l;
	    }
	}
    }
  తిరిగి NULL_వృక్షం;
}

/* OpenMP 5.x:
   # pragma omp allocate (list)  clauses

   OpenMP 5.0 clause:
   allocator (omp_allocator_handle_t expression)

   OpenMP 5.1 additional clause:
   align (constant-expression)]  */

స్థిర శూన్య
c_parser_omp_allocate (c_parser *parser)
{
  వృక్షం alignment = NULL_వృక్షం;
  వృక్షం allocator = NULL_వృక్షం;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  వృక్షం nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_వృక్షం);
  చేయి
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME))
	ఆపు;
      matching_parens parens;
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      c_parser_consume_token (parser);
      location_t సమాసం_loc = c_parser_peek_token (parser)->location;
      ఒకవేళ (strcmp ("align", p) != 0 && strcmp ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  ఆపు;
	}
      ఒకవేళ (!parens.require_open (parser))
	ఆపు;

      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, అబద్ధం, నిజం);
      సమాసం_loc = c_parser_peek_token (parser)->location;
      ఒకవేళ (సమాసం.విలువ == error_mark_కణుపు)
	;
      లేకపోతే ఒకవేళ (p[2] == 'i' && alignment)
	{
	  error_at (సమాసం_loc, "too many %qs clauses", "align");
	  ఆపు;
	}
      లేకపోతే ఒకవేళ (p[2] == 'i')
	{
	  alignment = c_fully_fold (సమాసం.విలువ, అబద్ధం, ఖాళీ);
	  ఒకవేళ (వృక్షం_సంకేతం (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (వృక్షం_TYPE (alignment))
	      || వృక్షం_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (సమాసం_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_వృక్షం;
	    }
	}
      లేకపోతే ఒకవేళ (allocator)
	{
	  error_at (సమాసం_loc, "too many %qs clauses", "allocator");
	  ఆపు;
	}
      లేకపోతే
	{
	  allocator = c_fully_fold (సమాసం.విలువ, అబద్ధం, ఖాళీ);
	  allocator_loc = సమాసం_loc;
	  వృక్షం orig_type
	    = సమాసం.original_type ? సమాసం.original_type : వృక్షం_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (allocator))
	      || వృక్షం_సంకేతం (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (సమాసం_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			వృక్షం_TYPE (allocator));
	      allocator = NULL_వృక్షం;
	    }
	}
      parens.skip_until_దొరికింది_close (parser);
    } అయితే (నిజం);
  c_parser_skip_గమ్యం_pragma_eol (parser);

  c_mark_decl_jump_unsafe_లోపల_current_scope ();
  కొరకు (వృక్షం c = nl; c != NULL_వృక్షం; c = OMP_CLAUSE_CHAIN (c))
    {
      వృక్షం var = OMP_CLAUSE_DECL (c);
      ఒకవేళ (వృక్షం_సంకేతం (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  కొనసాగు;
	}
      ఒకవేళ (!parser->లోపల_omp_decl_attribute && !c_check_లోపల_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_ఆధారం_LOCATION (var), "declared here");
	  కొనసాగు;
	}
      ఒకవేళ (lookup_attribute ("omp allocate", DECL_లక్షణాలు (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  కొనసాగు;
	}
      ఒకవేళ (వృక్షం_STATIC (var))
	{
	  ఒకవేళ (allocator == NULL_వృక్షం && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      కొనసాగు;
	    }
	  లేకపోతే ఒకవేళ (allocator
		   && (wi::గమ్యం_widest (allocator) < 1
		       || wi::గమ్యం_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::గమ్యం_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::గమ్యం_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  లేకపోతే ఒకవేళ (allocator
		   && (wi::eq_p (wi::గమ్యం_widest (allocator),
				 GOMP_OMP_PREDEF_ALLOC_CGROUP)
		       || wi::eq_p (wi::గమ్యం_widest (allocator),
				    GOMP_OMP_PREDEF_ALLOC_PTEAM)
		       || wi::eq_p (wi::గమ్యం_widest (allocator),
				    GOMP_OMP_PREDEF_ALLOC_THREAD)))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause for static variable %qD must not "
			"be %<omp_cgroup_mem_alloc%>, %<omp_pteam_mem_alloc%>, "
			"or %<omp_thread_mem_alloc%>", var);
	    }
	}
      ఒకవేళ (allocator)
	{
	  నిర్మాణం c_omp_loc_వృక్షం దత్తాంశం
	    = {సమాసం_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_వృక్షం (&allocator, c_check_omp_allocate_allocator_r, &దత్తాంశం, ఖాళీ);
	}
      DECL_లక్షణాలు (var) = వృక్షం_cons (get_identifier ("omp allocate"),
					 build_వృక్షం_list (allocator, alignment),
					 DECL_లక్షణాలు (var));
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

స్థిర శూన్య
c_parser_omp_atomic (location_t loc, c_parser *parser, తార్కిక openacc)
{
  వృక్షం lhs = NULL_వృక్షం, rhs = NULL_వృక్షం, v = NULL_వృక్షం, r = NULL_వృక్షం;
  వృక్షం lhs1 = NULL_వృక్షం, rhs1 = NULL_వృక్షం;
  వృక్షం stmt, orig_lhs, unfolded_lhs = NULL_వృక్షం, unfolded_lhs1 = NULL_వృక్షం;
  గణన వృక్షం_సంకేతం_2 సంకేతం_2 = ERROR_MARK, opcode = NOP_సమాసం;
  గణన omp_జ్ఞాపకం_క్రమం జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_UNSPECIFIED;
  నిర్మాణం c_సమాసం సమాసం;
  location_t eloc;
  తార్కిక structured_ఖండం = అబద్ధం;
  తార్కిక swapped = అబద్ధం;
  తార్కిక non_lvalue_p;
  వృక్షం clauses = NULL_వృక్షం;
  తార్కిక capture = అబద్ధం;
  తార్కిక compare = అబద్ధం;
  తార్కిక weak = అబద్ధం;
  గణన omp_జ్ఞాపకం_క్రమం fail = OMP_జ్ఞాపకం_క్రమం_UNSPECIFIED;
  తార్కిక no_semicolon = అబద్ధం;
  తార్కిక extra_scope = అబద్ధం;

  అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	{
	  స్థిరరాశి అక్షరం *p
	    = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  గణన వృక్షం_సంకేతం_2 new_సంకేతం = ERROR_MARK;
	  గణన omp_జ్ఞాపకం_క్రమం new_జ్ఞాపకం_క్రమం
	    = OMP_జ్ఞాపకం_క్రమం_UNSPECIFIED;
	  తార్కిక new_capture = అబద్ధం;
	  తార్కిక new_compare = అబద్ధం;
	  తార్కిక new_weak = అబద్ధం;
	  గణన omp_జ్ఞాపకం_క్రమం new_fail = OMP_జ్ఞాపకం_క్రమం_UNSPECIFIED;

	  ఒకవేళ (!strcmp (p, "read"))
	    new_సంకేతం = OMP_ATOMIC_READ;
	  లేకపోతే ఒకవేళ (!strcmp (p, "write"))
	    new_సంకేతం = NOP_సమాసం;
	  లేకపోతే ఒకవేళ (!strcmp (p, "update"))
	    new_సంకేతం = OMP_ATOMIC;
	  లేకపోతే ఒకవేళ (openacc && !strcmp (p, "capture"))
	    new_సంకేతం = OMP_ATOMIC_CAPTURE_NEW;
	  లేకపోతే ఒకవేళ (openacc)
	    {
	      p = ఖాళీ;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  లేకపోతే ఒకవేళ (!strcmp (p, "capture"))
	    new_capture = నిజం;
	  లేకపోతే ఒకవేళ (!strcmp (p, "compare"))
	    new_compare = నిజం;
	  లేకపోతే ఒకవేళ (!strcmp (p, "weak"))
	    new_weak = నిజం;
	  లేకపోతే ఒకవేళ (!strcmp (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      ఒకవేళ (!parens.require_open (parser))
		కొనసాగు;

	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
		{
		  స్థిరరాశి అక్షరం *q
		    = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);

		  ఒకవేళ (!strcmp (q, "seq_cst"))
		    new_fail = OMP_జ్ఞాపకం_క్రమం_SEQ_CST;
		  లేకపోతే ఒకవేళ (!strcmp (q, "acquire"))
		    new_fail = OMP_జ్ఞాపకం_క్రమం_ACQUIRE;
		  లేకపోతే ఒకవేళ (!strcmp (q, "relaxed"))
		    new_fail = OMP_జ్ఞాపకం_క్రమం_RELAXED;
		}

	      ఒకవేళ (new_fail != OMP_జ్ఞాపకం_క్రమం_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  ఒకవేళ (fail != OMP_జ్ఞాపకం_క్రమం_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  లేకపోతే
		    fail = new_fail;
		}
	      లేకపోతే
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_దొరికింది_close (parser);
	      కొనసాగు;
	    }
	  లేకపోతే ఒకవేళ (!strcmp (p, "seq_cst"))
	    new_జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_SEQ_CST;
	  లేకపోతే ఒకవేళ (!strcmp (p, "acq_rel"))
	    new_జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_ACQ_REL;
	  లేకపోతే ఒకవేళ (!strcmp (p, "release"))
	    new_జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_RELEASE;
	  లేకపోతే ఒకవేళ (!strcmp (p, "acquire"))
	    new_జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_ACQUIRE;
	  లేకపోతే ఒకవేళ (!strcmp (p, "relaxed"))
	    new_జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_RELAXED;
	  లేకపోతే ఒకవేళ (!strcmp (p, "hint"))
	    {
	      c_parser_consume_token (parser);
	      clauses = c_parser_omp_clause_hint (parser, clauses);
	      కొనసాగు;
	    }
	  లేకపోతే
	    {
	      p = ఖాళీ;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "%<capture%>, %<compare%>, %<weak%>, %<fail%>, "
			      "%<seq_cst%>, %<acq_rel%>, %<release%>, "
			      "%<relaxed%> or %<hint%> clause");
	    }
	  ఒకవేళ (p)
	    {
	      ఒకవేళ (new_సంకేతం != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  ఒకవేళ (openacc
		      && సంకేతం_2 == OMP_ATOMIC
		      && new_సంకేతం == OMP_ATOMIC_CAPTURE_NEW)
		    సంకేతం_2 = new_సంకేతం;
		  లేకపోతే ఒకవేళ (సంకేతం_2 != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  లేకపోతే
		    సంకేతం_2 = new_సంకేతం;
		}
	      లేకపోతే ఒకవేళ (new_జ్ఞాపకం_క్రమం != OMP_జ్ఞాపకం_క్రమం_UNSPECIFIED)
		{
		  ఒకవేళ (జ్ఞాపకం_క్రమం != OMP_జ్ఞాపకం_క్రమం_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  లేకపోతే
		    జ్ఞాపకం_క్రమం = new_జ్ఞాపకం_క్రమం;
		}
	      లేకపోతే ఒకవేళ (new_capture)
		{
		  ఒకవేళ (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  లేకపోతే
		    capture = నిజం;
		}
	      లేకపోతే ఒకవేళ (new_compare)
		{
		  ఒకవేళ (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  లేకపోతే
		    compare = నిజం;
		}
	      లేకపోతే ఒకవేళ (new_weak)
		{
		  ఒకవేళ (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  లేకపోతే
		    weak = నిజం;
		}
	      c_parser_consume_token (parser);
	      కొనసాగు;
	    }
	}
      ఆపు;
    }
  c_parser_skip_గమ్యం_pragma_eol (parser);

  ఒకవేళ (సంకేతం_2 == ERROR_MARK)
    సంకేతం_2 = OMP_ATOMIC;
  ఒకవేళ (capture)
    {
      ఒకవేళ (సంకేతం_2 != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      లేకపోతే
	సంకేతం_2 = OMP_ATOMIC_CAPTURE_NEW;
    }
  ఒకవేళ (compare && సంకేతం_2 != OMP_ATOMIC && సంకేతం_2 != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = అబద్ధం;
    }
  ఒకవేళ (fail != OMP_జ్ఞాపకం_క్రమం_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      fail = OMP_జ్ఞాపకం_క్రమం_UNSPECIFIED;
    }
  ఒకవేళ (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = అబద్ధం;
    }
  ఒకవేళ (openacc)
    జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_RELAXED;
  లేకపోతే ఒకవేళ (జ్ఞాపకం_క్రమం == OMP_జ్ఞాపకం_క్రమం_UNSPECIFIED)
    {
      omp_requires_ముసుగు
	= (గణన omp_requires) (omp_requires_ముసుగు
			       | OMP_REQUIRES_ATOMIC_DEFAULT_MEM_క్రమం_వాడిన);
      ఎంపిక ((గణన omp_జ్ఞాపకం_క్రమం)
	      (omp_requires_ముసుగు & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_క్రమం))
	{
	స్థితి OMP_జ్ఞాపకం_క్రమం_UNSPECIFIED:
	స్థితి OMP_జ్ఞాపకం_క్రమం_RELAXED:
	  జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_RELAXED;
	  ఆపు;
	స్థితి OMP_జ్ఞాపకం_క్రమం_SEQ_CST:
	  జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_SEQ_CST;
	  ఆపు;
	స్థితి OMP_జ్ఞాపకం_క్రమం_ACQUIRE:
	  ఒకవేళ (సంకేతం_2 == NOP_సమాసం)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_SEQ_CST;
	    }
	  లేకపోతే
	    జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_ACQUIRE;
	  ఆపు;
	స్థితి OMP_జ్ఞాపకం_క్రమం_RELEASE:
	  ఒకవేళ (సంకేతం_2 == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_SEQ_CST;
	    }
	  లేకపోతే
	    జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_RELEASE;
	  ఆపు;
	స్థితి OMP_జ్ఞాపకం_క్రమం_ACQ_REL:
	  ఎంపిక (సంకేతం_2)
	    {
	    స్థితి OMP_ATOMIC_READ:
	      జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_ACQUIRE;
	      ఆపు;
	    స్థితి NOP_సమాసం: /* atomic write */
	      జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_RELEASE;
	      ఆపు;
	    అప్రమేయ:
	      జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_ACQ_REL;
	      ఆపు;
	    }
	  ఆపు;
	అప్రమేయ:
	  gcc_unreachable ();
	}
    }
  లేకపోతే
    ఎంపిక (సంకేతం_2)
      {
      స్థితి OMP_ATOMIC_READ:
	ఒకవేళ (జ్ఞాపకం_క్రమం == OMP_జ్ఞాపకం_క్రమం_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_SEQ_CST;
	  }
	లేకపోతే ఒకవేళ (జ్ఞాపకం_క్రమం == OMP_జ్ఞాపకం_క్రమం_ACQ_REL)
	  జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_ACQUIRE;
	ఆపు;
      స్థితి NOP_సమాసం: /* atomic write */
	ఒకవేళ (జ్ఞాపకం_క్రమం == OMP_జ్ఞాపకం_క్రమం_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_SEQ_CST;
	  }
	లేకపోతే ఒకవేళ (జ్ఞాపకం_క్రమం == OMP_జ్ఞాపకం_క్రమం_ACQ_REL)
	  జ్ఞాపకం_క్రమం = OMP_జ్ఞాపకం_క్రమం_RELEASE;
	ఆపు;
      అప్రమేయ:
	ఆపు;
      }
  ఒకవేళ (fail != OMP_జ్ఞాపకం_క్రమం_UNSPECIFIED)
    జ్ఞాపకం_క్రమం
      = (గణన omp_జ్ఞాపకం_క్రమం) (జ్ఞాపకం_క్రమం
				 | (fail << OMP_FAIL_జ్ఞాపకం_క్రమం_జరుపు));

  ఎంపిక (సంకేతం_2)
    {
    స్థితి OMP_ATOMIC_READ:
    స్థితి NOP_సమాసం: /* atomic write */
      v = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ).విలువ;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, అబద్ధం, ఖాళీ, నిజం);
      ఒకవేళ (v == error_mark_కణుపు)
	వెళ్ళు saw_error;
      ఒకవేళ (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      ఒకవేళ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	వెళ్ళు saw_error;
      ఒకవేళ (సంకేతం_2 == NOP_సమాసం)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  సమాసం = c_parser_వ్యక్తీకరణ (parser);
	  సమాసం = default_function_array_read_conversion (eloc, సమాసం);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  సంకేతం_2 = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_వృక్షం;
	  rhs = c_fully_fold (సమాసం.విలువ, అబద్ధం, ఖాళీ);
	  ఒకవేళ (rhs == error_mark_కణుపు)
	    వెళ్ళు saw_error;
	}
      లేకపోతే
	{
	  lhs = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ).విలువ;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, అబద్ధం, ఖాళీ, నిజం);
	  ఒకవేళ (lhs == error_mark_కణుపు)
	    వెళ్ళు saw_error;
	  ఒకవేళ (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      వెళ్ళు పూర్తి;
    స్థితి OMP_ATOMIC_CAPTURE_NEW:
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_ఖండం = నిజం;
	}
      లేకపోతే ఒకవేళ (compare
	       && c_parser_తదుపరి_token_is_keyword (parser, RID_IF))
	ఆపు;
      లేకపోతే
	{
	  v = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ).విలువ;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, అబద్ధం, ఖాళీ, నిజం);
	  ఒకవేళ (v == error_mark_కణుపు)
	    వెళ్ళు saw_error;
	  ఒకవేళ (non_lvalue_p)
	    v = non_lvalue (v);
	  ఒకవేళ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    వెళ్ళు saw_error;
	  ఒకవేళ (compare && c_parser_తదుపరి_token_is_keyword (parser, RID_IF))
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "expected expression");
	      వెళ్ళు saw_error;
	    }
	}
      ఆపు;
    అప్రమేయ:
      ఆపు;
    }

  /* For structured_block case we don't know yet whether
     old or new x should be captured.  */
restart:
  ఒకవేళ (compare && c_parser_తదుపరి_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      ఒకవేళ (!parens.require_open (parser))
	వెళ్ళు saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_సమాసం cmp_సమాసం;
      ఒకవేళ (r)
	{
	  cmp_సమాసం = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
	  cmp_సమాసం = default_function_array_conversion (eloc, cmp_సమాసం);
	}
      లేకపోతే
	cmp_సమాసం = c_parser_ద్విమాన_వ్యక్తీకరణ (parser, ఖాళీ, void_list_కణుపు);
      parens.skip_until_దొరికింది_close (parser);
      ఒకవేళ (cmp_సమాసం.విలువ == error_mark_కణుపు)
	వెళ్ళు saw_error;
      ఒకవేళ (r)
	{
	  ఒకవేళ (!c_వృక్షం_equal (cmp_సమాసం.విలువ, unfolded_lhs))
	    వెళ్ళు bad_if;
	  cmp_సమాసం.విలువ = rhs1;
	  rhs1 = NULL_వృక్షం;
	  gcc_assert (వృక్షం_సంకేతం (cmp_సమాసం.విలువ) == EQ_సమాసం);
	}
      ఒకవేళ (వృక్షం_సంకేతం (cmp_సమాసం.విలువ) == EQ_సమాసం)
	;
      లేకపోతే ఒకవేళ (!structured_ఖండం && సంకేతం_2 == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (సమాసం_LOC_OR_LOC (cmp_సమాసం.విలువ, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  వెళ్ళు saw_error;
	}
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (cmp_సమాసం.విలువ) != GT_సమాసం
	       && వృక్షం_సంకేతం (cmp_సమాసం.విలువ) != LT_సమాసం)
	{
	  error_at (సమాసం_LOC_OR_LOC (cmp_సమాసం.విలువ, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  వెళ్ళు saw_error;
	}
      ఒకవేళ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	వెళ్ళు saw_error;

      extra_scope = నిజం;
      eloc = c_parser_peek_token (parser)->location;
      సమాసం = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
      lhs = సమాసం.విలువ;
      సమాసం = default_function_array_conversion (eloc, సమాసం);
      unfolded_lhs = సమాసం.విలువ;
      lhs = c_fully_fold (lhs, అబద్ధం, ఖాళీ, నిజం);
      orig_lhs = lhs;
      ఒకవేళ (lhs == error_mark_కణుపు)
	వెళ్ళు saw_error;
      ఒకవేళ (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  వెళ్ళు saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      rhs1 = సమాసం.విలువ;

      ఒకవేళ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	వెళ్ళు saw_error;

      ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	వెళ్ళు saw_error;

      extra_scope = అబద్ధం;
      no_semicolon = నిజం;

      ఒకవేళ (c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (cmp_సమాసం.విలువ, 0), unfolded_lhs))
	{
	  ఒకవేళ (వృక్షం_సంకేతం (cmp_సమాసం.విలువ) == EQ_సమాసం)
	    {
	      opcode = COND_సమాసం;
	      rhs = c_fully_fold (వృక్షం_నిర్వాహ్యం (cmp_సమాసం.విలువ, 1),
				  అబద్ధం, ఖాళీ, నిజం);
	      rhs1 = c_fully_fold (rhs1, అబద్ధం, ఖాళీ, నిజం);
	    }
	  లేకపోతే ఒకవేళ (c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (cmp_సమాసం.విలువ, 1), rhs1))
	    {
	      opcode = (వృక్షం_సంకేతం (cmp_సమాసం.విలువ) == GT_సమాసం
			? MIN_సమాసం : MAX_సమాసం);
	      rhs = c_fully_fold (rhs1, అబద్ధం, ఖాళీ, నిజం);
	      rhs1 = c_fully_fold (వృక్షం_నిర్వాహ్యం (cmp_సమాసం.విలువ, 0),
				   అబద్ధం, ఖాళీ, నిజం);
	    }
	  లేకపోతే
	    వెళ్ళు bad_if;
	}
      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (cmp_సమాసం.విలువ) == EQ_సమాసం)
	వెళ్ళు bad_if;
      లేకపోతే ఒకవేళ (c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (cmp_సమాసం.విలువ, 1), unfolded_lhs)
	       && c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (cmp_సమాసం.విలువ, 0), rhs1))
	{
	  opcode = (వృక్షం_సంకేతం (cmp_సమాసం.విలువ) == GT_సమాసం
		    ? MAX_సమాసం : MIN_సమాసం);
	  rhs = c_fully_fold (rhs1, అబద్ధం, ఖాళీ, నిజం);
	  rhs1 = c_fully_fold (వృక్షం_నిర్వాహ్యం (cmp_సమాసం.విలువ, 1),
			       అబద్ధం, ఖాళీ, నిజం);
	}
      లేకపోతే
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  వెళ్ళు saw_error;
	}

      ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_ELSE))
	{
	  ఒకవేళ (సంకేతం_2 != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_ఖండం && r == NULL_వృక్షం)
	      || వృక్షం_సంకేతం (cmp_సమాసం.విలువ) != EQ_సమాసం)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      వెళ్ళు saw_error;
	    }

	  c_parser_consume_token (parser);

	  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    వెళ్ళు saw_error;

	  extra_scope = నిజం;
	  v = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ).విలువ;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, అబద్ధం, ఖాళీ, నిజం);
	  ఒకవేళ (v == error_mark_కణుపు)
	    వెళ్ళు saw_error;
	  ఒకవేళ (non_lvalue_p)
	    v = non_lvalue (v);
	  ఒకవేళ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    వెళ్ళు saw_error;

	  సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);

	  ఒకవేళ (!c_వృక్షం_equal (సమాసం.విలువ, unfolded_lhs))
	    వెళ్ళు bad_if;

	  ఒకవేళ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    వెళ్ళు saw_error;

	  ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    వెళ్ళు saw_error;

	  extra_scope = అబద్ధం;
	  సంకేతం_2 = OMP_ATOMIC_CAPTURE_OLD;
	  ఒకవేళ (r == NULL_వృక్షం)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_కణుపు;
	}
      లేకపోతే ఒకవేళ (సంకేతం_2 == OMP_ATOMIC_CAPTURE_NEW && !structured_ఖండం)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  వెళ్ళు saw_error;
	}
      లేకపోతే ఒకవేళ (సంకేతం_2 == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_వృక్షం
	       && v == NULL_వృక్షం)
	సంకేతం_2 = OMP_ATOMIC;
      వెళ్ళు stmt_పూర్తి;
    }
  eloc = c_parser_peek_token (parser)->location;
  సమాసం = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
  lhs = సమాసం.విలువ;
  సమాసం = default_function_array_conversion (eloc, సమాసం);
  unfolded_lhs = సమాసం.విలువ;
  lhs = c_fully_fold (lhs, అబద్ధం, ఖాళీ, నిజం);
  orig_lhs = lhs;
  ఎంపిక (వృక్షం_సంకేతం (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    స్థితి ERROR_MARK:
    saw_error:
      c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
      ఒకవేళ (extra_scope && c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      ఒకవేళ (structured_ఖండం)
	{
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  లేకపోతే ఒకవేళ (సంకేతం_2 == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      తిరిగి;

    స్థితి POSTINCREMENT_సమాసం:
      ఒకవేళ (సంకేతం_2 == OMP_ATOMIC_CAPTURE_NEW && !structured_ఖండం)
	సంకేతం_2 = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    స్థితి PREINCREMENT_సమాసం:
      lhs = వృక్షం_నిర్వాహ్యం (lhs, 0);
      unfolded_lhs = NULL_వృక్షం;
      opcode = PLUS_సమాసం;
      rhs = integer_one_కణుపు;
      ఒకవేళ (compare)
	వెళ్ళు invalid_compare;
      ఆపు;

    స్థితి POSTDECREMENT_సమాసం:
      ఒకవేళ (సంకేతం_2 == OMP_ATOMIC_CAPTURE_NEW && !structured_ఖండం)
	సంకేతం_2 = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    స్థితి PREDECREMENT_సమాసం:
      lhs = వృక్షం_నిర్వాహ్యం (lhs, 0);
      unfolded_lhs = NULL_వృక్షం;
      opcode = MINUS_సమాసం;
      rhs = integer_one_కణుపు;
      ఒకవేళ (compare)
	వెళ్ళు invalid_compare;
      ఆపు;

    స్థితి COMPOUND_సమాసం:
      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (lhs, 0)) == SAVE_సమాసం
	  && వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (lhs, 1)) == COMPOUND_సమాసం
	  && వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం (lhs, 1), 0)) == MODIFY_సమాసం
	  && వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం (lhs, 1), 1) == వృక్షం_నిర్వాహ్యం (lhs, 0)
	  && C_BOOLEAN_TYPE_P (వృక్షం_TYPE (వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం
					      (వృక్షం_నిర్వాహ్యం (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం (lhs, 1), 0);
      /* FALLTHRU */
    స్థితి MODIFY_సమాసం:
      ఒకవేళ (వృక్షం_సంకేతం (lhs) == MODIFY_సమాసం
	  && C_BOOLEAN_TYPE_P (వృక్షం_TYPE (వృక్షం_నిర్వాహ్యం (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  ఒకవేళ (integer_onep (వృక్షం_నిర్వాహ్యం (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = వృక్షం_నిర్వాహ్యం (lhs, 1);
	      lhs = వృక్షం_నిర్వాహ్యం (lhs, 0);
	      unfolded_lhs = NULL_వృక్షం;
	      opcode = NOP_సమాసం;
	      ఒకవేళ (సంకేతం_2 == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_ఖండం
		  && వృక్షం_సంకేతం (orig_lhs) == COMPOUND_సమాసం)
		సంకేతం_2 = OMP_ATOMIC_CAPTURE_OLD;
	      ఒకవేళ (compare)
		వెళ్ళు invalid_compare;
	      ఆపు;
	    }
	  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (lhs, 1)) == TRUTH_NOT_సమాసం
	      && వృక్షం_నిర్వాహ్యం (lhs, 0)
		 == వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = వృక్షం_నిర్వాహ్యం (lhs, 1);
	      lhs = వృక్షం_నిర్వాహ్యం (lhs, 0);
	      unfolded_lhs = NULL_వృక్షం;
	      opcode = NOP_సమాసం;
	      ఒకవేళ (సంకేతం_2 == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_ఖండం
		  && వృక్షం_సంకేతం (orig_lhs) == COMPOUND_సమాసం)
		సంకేతం_2 = OMP_ATOMIC_CAPTURE_OLD;
	      ఒకవేళ (compare)
		వెళ్ళు invalid_compare;
	      ఆపు;
	    }
	}
      /* FALLTHRU */
    అప్రమేయ:
      ఒకవేళ (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      ఒకవేళ (compare && !c_parser_తదుపరి_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  వెళ్ళు saw_error;
	}
      ఎంపిక (c_parser_peek_token (parser)->type)
	{
	స్థితి CPP_MULT_EQ:
	  opcode = MULT_సమాసం;
	  ఆపు;
	స్థితి CPP_DIV_EQ:
	  opcode = TRUNC_DIV_సమాసం;
	  ఆపు;
	స్థితి CPP_PLUS_EQ:
	  opcode = PLUS_సమాసం;
	  ఆపు;
	స్థితి CPP_MINUS_EQ:
	  opcode = MINUS_సమాసం;
	  ఆపు;
	స్థితి CPP_LSHIFT_EQ:
	  opcode = LSHIFT_సమాసం;
	  ఆపు;
	స్థితి CPP_RSHIFT_EQ:
	  opcode = RSHIFT_సమాసం;
	  ఆపు;
	స్థితి CPP_AND_EQ:
	  opcode = బిట్టు_AND_సమాసం;
	  ఆపు;
	స్థితి CPP_OR_EQ:
	  opcode = బిట్టు_IOR_సమాసం;
	  ఆపు;
	స్థితి CPP_XOR_EQ:
	  opcode = బిట్టు_XOR_సమాసం;
	  ఆపు;
	స్థితి CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ, unfolded_lhs);
	  rhs1 = సమాసం.విలువ;
	  ఎంపిక (వృక్షం_సంకేతం (rhs1))
	    {
	    స్థితి MULT_సమాసం:
	    స్థితి TRUNC_DIV_సమాసం:
	    స్థితి RDIV_సమాసం:
	    స్థితి PLUS_సమాసం:
	    స్థితి MINUS_సమాసం:
	    స్థితి LSHIFT_సమాసం:
	    స్థితి RSHIFT_సమాసం:
	    స్థితి బిట్టు_AND_సమాసం:
	    స్థితి బిట్టు_IOR_సమాసం:
	    స్థితి బిట్టు_XOR_సమాసం:
	      ఒకవేళ (compare)
		ఆపు;
	      ఒకవేళ (c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (rhs1, 0), unfolded_lhs))
		{
		  opcode = వృక్షం_సంకేతం (rhs1);
		  rhs = c_fully_fold (వృక్షం_నిర్వాహ్యం (rhs1, 1), అబద్ధం, ఖాళీ,
				      నిజం);
		  rhs1 = c_fully_fold (వృక్షం_నిర్వాహ్యం (rhs1, 0), అబద్ధం, ఖాళీ,
				       నిజం);
		  వెళ్ళు stmt_పూర్తి;
		}
	      ఒకవేళ (c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (rhs1, 1), unfolded_lhs))
		{
		  opcode = వృక్షం_సంకేతం (rhs1);
		  rhs = c_fully_fold (వృక్షం_నిర్వాహ్యం (rhs1, 0), అబద్ధం, ఖాళీ,
				      నిజం);
		  rhs1 = c_fully_fold (వృక్షం_నిర్వాహ్యం (rhs1, 1), అబద్ధం, ఖాళీ,
				       నిజం);
		  swapped = !commutative_వృక్షం_సంకేతం (opcode);
		  వెళ్ళు stmt_పూర్తి;
		}
	      ఆపు;
	    స్థితి COND_సమాసం:
	      ఒకవేళ (!compare)
		ఆపు;
	      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (rhs1, 0)) != GT_సమాసం
		  && వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (rhs1, 0)) != LT_సమాసం
		  && వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (rhs1, 0)) != EQ_సమాసం)
		ఆపు;
	      ఒకవేళ (!వృక్షం_నిర్వాహ్యం (rhs1, 1))
		ఆపు;
	      ఒకవేళ (!c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (rhs1, 2), unfolded_lhs))
		ఆపు;
	      ఒకవేళ (c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం (rhs1, 0), 0),
				unfolded_lhs))
		{
		  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (rhs1, 0)) == EQ_సమాసం)
		    {
		      opcode = COND_సమాసం;
		      rhs = c_fully_fold (వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం (rhs1,
								      0), 1),
					  అబద్ధం, ఖాళీ, నిజం);
		      rhs1 = c_fully_fold (వృక్షం_నిర్వాహ్యం (rhs1, 1), అబద్ధం,
					   ఖాళీ, నిజం);
		      వెళ్ళు stmt_పూర్తి;
		    }
		  ఒకవేళ (c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం (rhs1, 0), 1),
				    వృక్షం_నిర్వాహ్యం (rhs1, 1)))
		    {
		      opcode = (వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (rhs1, 0)) == GT_సమాసం
				? MIN_సమాసం : MAX_సమాసం);
		      rhs = c_fully_fold (వృక్షం_నిర్వాహ్యం (rhs1, 1), అబద్ధం, ఖాళీ,
					  నిజం);
		      rhs1 = c_fully_fold (వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం (rhs1,
								       0), 0),
					   అబద్ధం, ఖాళీ, నిజం);
		      వెళ్ళు stmt_పూర్తి;
		    }
		}
	      లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (rhs1, 0)) == EQ_సమాసం)
		ఆపు;
	      లేకపోతే ఒకవేళ (c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  ఒకవేళ (c_వృక్షం_equal (వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం (rhs1, 0), 0),
				    వృక్షం_నిర్వాహ్యం (rhs1, 1)))
		    {
		      opcode = (వృక్షం_సంకేతం (వృక్షం_నిర్వాహ్యం (rhs1, 0)) == GT_సమాసం
				? MAX_సమాసం : MIN_సమాసం);
		      rhs = c_fully_fold (వృక్షం_నిర్వాహ్యం (rhs1, 1), అబద్ధం, ఖాళీ,
					  నిజం);
		      rhs1 = c_fully_fold (వృక్షం_నిర్వాహ్యం (వృక్షం_నిర్వాహ్యం (rhs1,
								       0), 1),
					   అబద్ధం, ఖాళీ, నిజం);
		      వెళ్ళు stmt_పూర్తి;
		    }
		}
	      ఆపు;
	    స్థితి EQ_సమాసం:
	      ఒకవేళ (!compare
		  || సంకేతం_2 != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_ఖండం
		  || v
		  || r)
		ఆపు;
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_వృక్షం;
		  c_parser_consume_token (parser);
		  వెళ్ళు restart;
		}
	      ఆపు;
	    స్థితి ERROR_MARK:
	      వెళ్ళు saw_error;
	    అప్రమేయ:
	      ఆపు;
	    }
	  ఒకవేళ (c_parser_peek_token (parser)->type == CPP_SEMICOLON)
	    {
	      ఒకవేళ (structured_ఖండం && సంకేతం_2 == OMP_ATOMIC_CAPTURE_NEW)
		{
		  సంకేతం_2 = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_వృక్షం;
		  సమాసం = default_function_array_read_conversion (eloc, సమాసం);
		  unfolded_lhs1 = సమాసం.విలువ;
		  lhs1 = c_fully_fold (unfolded_lhs1, అబద్ధం, ఖాళీ, నిజం);
		  rhs1 = NULL_వృక్షం;
		  c_parser_consume_token (parser);
		  వెళ్ళు restart;
		}
	      ఒకవేళ (structured_ఖండం && !compare)
		{
		  opcode = NOP_సమాసం;
		  సమాసం = default_function_array_read_conversion (eloc, సమాసం);
		  rhs = c_fully_fold (సమాసం.విలువ, అబద్ధం, ఖాళీ, నిజం);
		  rhs1 = NULL_వృక్షం;
		  వెళ్ళు stmt_పూర్తి;
		}
	    }
	  c_parser_error (parser, "invalid form of %<#pragma omp atomic%>");
	  వెళ్ళు saw_error;
	అప్రమేయ:
	  c_parser_error (parser,
			  "invalid operator for %<#pragma omp atomic%>");
	  వెళ్ళు saw_error;
	}

      /* Arrange to pass the location of the assignment operator to
	 c_finish_omp_atomic.  */
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      సమాసం = c_parser_వ్యక్తీకరణ (parser);
      సమాసం = default_function_array_read_conversion (eloc, సమాసం);
      rhs = సమాసం.విలువ;
      rhs = c_fully_fold (rhs, అబద్ధం, ఖాళీ, నిజం);
      ఆపు;
    }
stmt_పూర్తి:
  ఒకవేళ (structured_ఖండం && సంకేతం_2 == OMP_ATOMIC_CAPTURE_NEW && r == NULL_వృక్షం)
    {
      ఒకవేళ (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	వెళ్ళు saw_error;
      no_semicolon = అబద్ధం;
      v = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ).విలువ;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, అబద్ధం, ఖాళీ, నిజం);
      ఒకవేళ (v == error_mark_కణుపు)
	వెళ్ళు saw_error;
      ఒకవేళ (non_lvalue_p)
	v = non_lvalue (v);
      ఒకవేళ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	వెళ్ళు saw_error;
      eloc = c_parser_peek_token (parser)->location;
      సమాసం = c_parser_cast_వ్యక్తీకరణ (parser, ఖాళీ);
      lhs1 = సమాసం.విలువ;
      సమాసం = default_function_array_read_conversion (eloc, సమాసం);
      unfolded_lhs1 = సమాసం.విలువ;
      lhs1 = c_fully_fold (lhs1, అబద్ధం, ఖాళీ, నిజం);
      ఒకవేళ (lhs1 == error_mark_కణుపు)
	వెళ్ళు saw_error;
      ఒకవేళ (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  ఒకవేళ (structured_ఖండం)
    {
      ఒకవేళ (!no_semicolon)
	c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
పూర్తి:
  ఒకవేళ (weak && opcode != COND_సమాసం)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = అబద్ధం;
    }
  ఒకవేళ (unfolded_lhs && unfolded_lhs1
      && !c_వృక్షం_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_కణుపు;
    }
  లేకపోతే
    stmt = c_ముగింపు_omp_atomic (loc, సంకేతం_2, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, జ్ఞాపకం_క్రమం, weak);
  ఒకవేళ (stmt != error_mark_కణుపు)
    కూడు_stmt (stmt);

  ఒకవేళ (!structured_ఖండం && !no_semicolon)
    c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
}


/* OpenMP 2.5:
   # pragma omp barrier new-line
*/

స్థిర శూన్య
c_parser_omp_barrier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  c_parser_skip_గమ్యం_pragma_eol (parser);

  c_ముగింపు_omp_barrier (loc);
}

/* OpenMP 2.5:
   # pragma omp critical [(name)] new-line
     structured-block

   OpenMP 4.5:
   # pragma omp critical [(name) [hint(expression)]] new-line

  LOC is the location of the #pragma itself.  */

#నిర్వచించు OMP_CRITICAL_CLAUSE_ముసుగు		\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_HINT) )

స్థిర వృక్షం
c_parser_omp_critical (location_t loc, c_parser *parser, తార్కిక *if_p)
{
  వృక్షం stmt, name = NULL_వృక్షం, clauses = NULL_వృక్షం;

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->విలువ;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      లేకపోతే
	c_parser_error (parser, "expected identifier");

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_ముసుగు,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_ఖండం (parser, if_p);
  తిరిగి c_ముగింపు_omp_critical (loc, stmt, name, clauses);
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
లోపల
బహిర్గతం
     inout
     mutexinout  */

స్థిర శూన్య
c_parser_omp_depobj (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    {
      c_parser_skip_గమ్యం_pragma_eol (parser);
      తిరిగి;
    }

  వృక్షం depobj = c_parser_సమాసం_no_commas (parser, ఖాళీ).విలువ;
  ఒకవేళ (depobj != error_mark_కణుపు)
    {
      ఒకవేళ (!lvalue_p (depobj))
	{
	  error_at (సమాసం_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_కణుపు;
	}
      లేకపోతే
	{
	  వృక్షం addr = build_unary_op (సమాసం_LOC_OR_LOC (depobj, loc), ADDR_సమాసం,
				      depobj, అబద్ధం);
	  ఒకవేళ (addr == error_mark_కణుపు)
	    depobj = error_mark_కణుపు;
	  లేకపోతే
	    depobj = build_పరోక్ష_ref (సమాసం_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_నక్షత్రం);
	}
    }

  parens.skip_until_దొరికింది_close (parser);
  వృక్షం clause = NULL_వృక్షం;
  గణన omp_clause_depend_రకం రకం = OMP_CLAUSE_DEPEND_INVALID;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);

      c_parser_consume_token (parser);
      ఒకవేళ (!strcmp ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_వృక్షం, c_loc);
	  clause = c_ముగింపు_omp_clauses (clause, C_ORT_OMP);
	  ఒకవేళ (!clause)
	    clause = error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (!strcmp ("destroy", p))
	{
	  matching_parens c_parens;
	  రకం = OMP_CLAUSE_DEPEND_చివరి;
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      వృక్షం destobj = c_parser_సమాసం_no_commas (parser, ఖాళీ).విలువ;
	      ఒకవేళ (!lvalue_p (destobj))
		error_at (సమాసం_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      లేకపోతే ఒకవేళ (depobj != error_mark_కణుపు
		       && !నిర్వాహ్యం_equal_p (destobj, depobj,
					    OEP_సరిపోలిక_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (సమాసం_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_దొరికింది_close (parser);
	    }
	}
      లేకపోతే ఒకవేళ (!strcmp ("update", p))
	{
	  matching_parens c_parens;
	  ఒకవేళ (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
		{
		  స్థిరరాశి అక్షరం *p2
		    = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);

		  c_parser_consume_token (parser);
		  ఒకవేళ (!strcmp ("in", p2))
		    రకం = OMP_CLAUSE_DEPEND_లోపల;
		  లేకపోతే ఒకవేళ (!strcmp ("out", p2))
		    రకం = OMP_CLAUSE_DEPEND_బహిర్గతం;
		  లేకపోతే ఒకవేళ (!strcmp ("inout", p2))
		    రకం = OMP_CLAUSE_DEPEND_INOUT;
		  లేకపోతే ఒకవేళ (!strcmp ("mutexinoutset", p2))
		    రకం = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  లేకపోతే ఒకవేళ (!strcmp ("inoutset", p2))
		    రకం = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      ఒకవేళ (రకం == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_కణుపు;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_దొరికింది_close (parser);
	    }
	  లేకపోతే
	    clause = error_mark_కణుపు;
	}
    }
  ఒకవేళ (!clause && రకం == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_కణుపు;
      error_at (c_loc, "expected %<depend%>, %<destroy%> or %<update%> clause");
    }
  c_parser_skip_గమ్యం_pragma_eol (parser);

  c_ముగింపు_omp_depobj (loc, depobj, రకం, clause);
}


/* OpenMP 2.5:
   # pragma omp flush flush-vars[opt] new-line

   flush-vars:
     ( variable-list )

   OpenMP 5.0:
   # pragma omp flush memory-order-clause new-line  */

స్థిర శూన్య
c_parser_omp_flush (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  గణన memmodel mo = MEMMODEL_చివరి;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p
	= IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);

      ఒకవేళ (!strcmp (p, "seq_cst"))
	mo = MEMMODEL_SEQ_CST;
      లేకపోతే ఒకవేళ (!strcmp (p, "acq_rel"))
	mo = MEMMODEL_ACQ_REL;
      లేకపోతే ఒకవేళ (!strcmp (p, "release"))
	mo = MEMMODEL_RELEASE;
      లేకపోతే ఒకవేళ (!strcmp (p, "acquire"))
	mo = MEMMODEL_ACQUIRE;
      లేకపోతే
	error_at (c_parser_peek_token (parser)->location,
		  "expected %<seq_cst%>, %<acq_rel%>, %<release%> or "
		  "%<acquire%>");
      c_parser_consume_token (parser);
    }
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      ఒకవేళ (mo != MEMMODEL_చివరి)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ఖాళీ);
    }
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_గమ్యం_pragma_eol (parser);

  c_ముగింపు_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

స్థిర తార్కిక
c_parser_omp_section_పరిశీలన (c_parser *parser, స్థిరరాశి అక్షరం *directive,
			   తార్కిక tentative)
{
  ఒకవేళ (!c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
    తిరిగి అబద్ధం;
  గుర్తులేని పూర్ణాంకం n = 3;
  ఒకవేళ (!c_parser_check_సమతుల్య_raw_token_sequence (parser, &n))
    తిరిగి అబద్ధం;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  ఒకవేళ (token->type != CPP_CLOSE_వర్గం)
    తిరిగి అబద్ధం;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  ఒకవేళ (token->type != CPP_CLOSE_వర్గం)
    తిరిగి అబద్ధం;
  ఒకవేళ (n < 9)
    తిరిగి అబద్ధం;
  ఒకవేళ (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      వృక్షం మొదటి = c_parser_peek_nth_token_raw (parser, 3)->విలువ;
      వృక్షం రెండవ = c_parser_peek_nth_token_raw (parser, 5)->విలువ;
      ఒకవేళ (strcmp (IDENTIFIER_సూచిక (మొదటి), "directive")
	  && strcmp (IDENTIFIER_సూచిక (మొదటి), "__directive__"))
	తిరిగి అబద్ధం;
      ఒకవేళ (strcmp (IDENTIFIER_సూచిక (రెండవ), directive))
	తిరిగి అబద్ధం;
    }
  ఒకవేళ (tentative)
    తిరిగి నిజం;
  location_t మొదటి_loc = c_parser_peek_token (parser)->location;
  location_t చివరి_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t మధ్య_loc = UNKNOWN_LOCATION;
  వృక్షం std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  తార్కిక చూసిన = అబద్ధం;
  పూర్ణాంకం cnt = 0;
  కొరకు (వృక్షం attr = std_attrs; attr; attr = వృక్షం_CHAIN (attr))
    ఒకవేళ (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	కొరకు (వృక్షం a = వృక్షం_విలువ (attr); a; a = వృక్షం_CHAIN (a))
	  {
	    వృక్షం d = వృక్షం_విలువ (a);
	    gcc_assert (వృక్షం_సంకేతం (d) == C_TOKEN_VEC);
	    c_token *మొదటి = C_TOKEN_VEC_టోకెన్లు (d)->చిరునామా ();
	    cnt++;
	    ఒకవేళ (మొదటి->type == CPP_NAME
		&& strcmp (IDENTIFIER_సూచిక (మొదటి->విలువ),
			   directive) == 0)
	      {
		చూసిన = నిజం;
		ఒకవేళ (మధ్య_loc == UNKNOWN_LOCATION)
		  మధ్య_loc = మొదటి->location;
	      }
	  }
      }
  ఒకవేళ (!చూసిన)
    తిరిగి అబద్ధం;
  ఒకవేళ (cnt != 1 || వృక్షం_CHAIN (std_attrs))
    {
      error_at (make_location (మొదటి_loc, చివరి_loc, మధ్య_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      తిరిగి అబద్ధం;
    }
  c_parser_handle_statement_omp_లక్షణాలు (parser, std_attrs, ఖాళీ);
  తిరిగి నిజం;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

స్థిర వృక్షం
c_parser_omp_structured_ఖండం_sequence (c_parser *parser,
					గణన pragma_రకం రకం)
{
  వృక్షం stmt = నెట్టు_stmt_list ();
  c_parser_statement (parser, ఖాళీ);
  చేయి
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
	ఆపు;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_EOF))
	ఆపు;

      ఒకవేళ (రకం != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_రకం == రకం)
	ఆపు;

      ఒకవేళ (రకం != PRAGMA_NONE
	  && c_parser_omp_section_పరిశీలన (parser,
					రకం == PRAGMA_OMP_పరిశీలన
					? "scan" : "section", అబద్ధం))
	ఆపు;

      c_parser_statement (parser, ఖాళీ);
    }
  అయితే (1);
  తిరిగి తీయి_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

స్థిర శూన్య
c_parser_omp_పరిశీలన_loop_body (c_parser *parser, తార్కిక open_brace_parsed)
{
  వృక్షం substmt;
  location_t loc;
  వృక్షం clauses = NULL_వృక్షం;
  తార్కిక దొరికింది_పరిశీలన = అబద్ధం;

  loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = అబద్ధం;
      తిరిగి;
    }

  ఒకవేళ (c_parser_peek_token (parser)->pragma_రకం != PRAGMA_OMP_పరిశీలన)
    substmt = c_parser_omp_structured_ఖండం_sequence (parser, PRAGMA_OMP_పరిశీలన);
  లేకపోతే
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_ఖాళీలు_stmt (loc);
    }
  substmt = build2 (OMP_పరిశీలన, void_type_కణుపు, substmt, NULL_వృక్షం);
  సమితి_సమాసం_LOCATION (substmt, loc);
  కూడు_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (c_parser_peek_token (parser)->pragma_రకం == PRAGMA_OMP_పరిశీలన)
    {
      గణన omp_clause_సంకేతం clause = OMP_CLAUSE_ERROR;
      దొరికింది_పరిశీలన = నిజం;

      c_parser_consume_pragma (parser);

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	{
	  స్థిరరాశి అక్షరం *p
	    = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
	  ఒకవేళ (strcmp (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  లేకపోతే ఒకవేళ (strcmp (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      ఒకవేళ (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_వృక్షం);
	}
      లేకపోతే
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_గమ్యం_pragma_eol (parser);
    }
  లేకపోతే
    error ("expected %<#pragma omp scan%>");

  clauses = c_ముగింపు_omp_clauses (clauses, C_ORT_OMP);
  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_ఖండం_sequence (parser, PRAGMA_NONE);
  లేకపోతే
    {
      ఒకవేళ (దొరికింది_పరిశీలన)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_ఖాళీలు_stmt (loc);
    }
  substmt = build2 (OMP_పరిశీలన, void_type_కణుపు, substmt, clauses);
  సమితి_సమాసం_LOCATION (substmt, loc);
  కూడు_stmt (substmt);

  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
స్థిర తార్కిక
c_parser_omp_తదుపరి_టోకెన్లు_can_be_canon_loop (c_parser *parser,
					    గణన వృక్షం_సంకేతం_2 సంకేతం_2,
					    తార్కిక error_p)
{
  ఒకవేళ (సంకేతం_2 == OACC_LOOP)
    {
      ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_FOR))
	తిరిగి నిజం;
      ఒకవేళ (error_p)
	c_parser_error (parser, "for statement expected");
    }
  లేకపోతే
    {
      ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_FOR))
	తిరిగి నిజం;

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_PRAGMA))
	ఎంపిక (c_parser_peek_token (parser)->pragma_రకం)
	  {
	  స్థితి PRAGMA_OMP_UNROLL:
	  స్థితి PRAGMA_OMP_TILE:
	    తిరిగి నిజం;
	  అప్రమేయ:
	    ఆపు;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      కొలత_t n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      ఒకవేళ (token->type == CPP_NAME
	  && C_IS_RESERVED_మాట (token->విలువ)
	  && C_RID_సంకేతం (token->విలువ) == RID_FOR)
	తిరిగి నిజం;
      ఒకవేళ (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  తిరిగి అబద్ధం;
}

స్థిర వృక్షం c_parser_omp_tile (location_t, c_parser *, తార్కిక *);
స్థిర వృక్షం c_parser_omp_unroll (location_t, c_parser *, తార్కిక *);

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

స్థిర వృక్షం
c_parser_omp_loop_nest (c_parser *parser, తార్కిక *if_p)
{
  వృక్షం decl = NULL_వృక్షం, cond = NULL_వృక్షం, incr = NULL_వృక్షం, init = NULL_వృక్షం;
  వృక్షం body = NULL_వృక్షం;
  matching_parens parens;
  తార్కిక moreloops;
  గుర్తులేని అక్షరం save_లోపల_statement;
  వృక్షం loop_scope;
  location_t loc;
  నిర్మాణం omp_for_parse_దత్తాంశం *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  పూర్ణాంకం లోతు = omp_for_parse_state->లోతు;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  ఒకవేళ (c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
    {
      వృక్షం std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_లక్షణాలు (parser, std_attrs, ఖాళీ);
      ఒకవేళ (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_PRAGMA))
    {
      వృక్షం transform = NULL_వృక్షం, sizes, body = NULL_వృక్షం;
      పూర్ణాంకం లెక్క = 0;
      ఎంపిక (c_parser_peek_token (parser)->pragma_రకం)
	{
	స్థితి PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = నెట్టు_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = తీయి_stmt_list (body);
	  ఒకవేళ (transform == NULL_వృక్షం || transform == error_mark_కణుపు)
	    {
	      transform = error_mark_కణుపు;
	      ఆపు;
	    }
	  gcc_assert (వృక్షం_సంకేతం (transform) == OMP_UNROLL);
	  ఒకవేళ (omp_కనుగొను_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      ఒకవేళ (omp_for_parse_state->లెక్క - లోతు > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->లెక్క - లోతు);
		  transform = error_mark_కణుపు;
		}
	      లేకపోతే
		లెక్క = 1;
	    }
	  లేకపోతే
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_కణుపు;
	    }
	  ఆపు;
	స్థితి PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = నెట్టు_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = తీయి_stmt_list (body);
	  ఒకవేళ (transform == NULL_వృక్షం || transform == error_mark_కణుపు)
	    {
	      transform = error_mark_కణుపు;
	      ఆపు;
	    }
	  gcc_assert (వృక్షం_సంకేతం (transform) == OMP_TILE);
	  sizes = omp_కనుగొను_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  లెక్క = list_నిడివి (OMP_CLAUSE_SIZES_LIST (sizes));
	  ఒకవేళ (లోతు + లెక్క < omp_for_parse_state->లెక్క)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			లెక్క, omp_for_parse_state->లెక్క - లోతు);
	      transform = error_mark_కణుపు;
	    }
	  ఆపు;
	అప్రమేయ:
	  c_parser_pragma (parser, pragma_stmt, ఖాళీ, void_list_కణుపు);
	  ఆపు;
	}
      ఒకవేళ (transform == NULL_వృక్షం)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      ఒకవేళ (transform == NULL_వృక్షం || transform == error_mark_కణుపు)
	{
	  omp_for_parse_state->fail = నిజం;
	  తిరిగి NULL_వృక్షం;
	}
      కొరకు (లెక్క = omp_for_parse_state->లెక్క; లోతు < లెక్క; ++లోతు)
	{
	  వృక్షం_VEC_ELT (omp_for_parse_state->declv, లోతు) = NULL_వృక్షం;
	  వృక్షం_VEC_ELT (omp_for_parse_state->initv, లోతు) = NULL_వృక్షం;
	  వృక్షం_VEC_ELT (omp_for_parse_state->condv, లోతు) = NULL_వృక్షం;
	  వృక్షం_VEC_ELT (omp_for_parse_state->incrv, లోతు) = NULL_వృక్షం;
	}
      omp_for_parse_state->want_nested_loop = అబద్ధం;
      తిరిగి body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_లోపల_statement = లోపల_statement;
  లోపల_statement = లోపల_OMP_ఖండం;

  /* We are not in intervening code now.  */
  omp_for_parse_state->లోపల_intervening_సంకేతం = అబద్ధం;

  ఒకవేళ (!parens.require_open (parser))
    {
      omp_for_parse_state->fail = నిజం;
      తిరిగి NULL_వృక్షం;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (నిజం);

  /* Parse the initialization declaration or expression.  */
  ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      వృక్షం this_pre_body = నెట్టు_stmt_list ();
      c_లోపల_omp_for = నిజం;
      c_parser_declaration_or_fndef (parser, నిజం, నిజం, నిజం, నిజం, నిజం,
				     అబద్ధం);
      c_లోపల_omp_for = అబద్ధం;
      this_pre_body = తీయి_stmt_list (this_pre_body);
      append_గమ్యం_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      ఒకవేళ (decl == ఖాళీ)
	వెళ్ళు error_init;
      ఒకవేళ (DECL_INITIAL (decl) == error_mark_కణుపు)
	decl = error_mark_కణుపు;
      init = decl;
    }
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      నిర్మాణం c_సమాసం decl_exp;
      నిర్మాణం c_సమాసం init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_వ్యక్తీకరణ (parser);
      decl = decl_exp.విలువ;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_సమాసం_no_commas (parser, ఖాళీ);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_లోపల_omp_for = నిజం;
      init = build_modify_సమాసం (init_loc, decl, decl_exp.original_type,
				NOP_సమాసం, init_loc, init_exp.విలువ,
				init_exp.original_type);
      c_లోపల_omp_for = అబద్ధం;
      init = c_process_సమాసం_stmt (init_loc, init);

      c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  లేకపోతే
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->fail = నిజం;
      వెళ్ళు parse_తదుపరి;
    }

  /* Parse the loop condition.  */
  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_లోపల_omp_for = నిజం;
      నిర్మాణం c_సమాసం cond_సమాసం
	= c_parser_ద్విమాన_వ్యక్తీకరణ (parser, ఖాళీ, NULL_వృక్షం);
      c_లోపల_omp_for = అబద్ధం;

      cond = cond_సమాసం.విలువ;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      ఎంపిక (cond_సమాసం.original_సంకేతం)
	{
	స్థితి GT_సమాసం:
	స్థితి GE_సమాసం:
	స్థితి LT_సమాసం:
	స్థితి LE_సమాసం:
	  ఆపు;
	స్థితి NE_సమాసం:
	  ఒకవేళ (omp_for_parse_state->సంకేతం_2 != OACC_LOOP)
	    ఆపు;
	  /* FALLTHRU.  */
	అప్రమేయ:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_సమాసం, boolean_type_కణుపు, error_mark_కణుపు);
	  ఆపు;
	}
      protected_సమితి_సమాసం_location (cond, cond_loc);
    }
  c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_సమాసం_stmt (incr_loc,
				  c_parser_వ్యక్తీకరణ (parser).విలువ);
    }
  parens.skip_until_దొరికింది_close (parser);

  ఒకవేళ (decl == ఖాళీ || decl == error_mark_కణుపు || init == error_mark_కణుపు)
    omp_for_parse_state->fail = నిజం;
  లేకపోతే
    {
      వృక్షం_VEC_ELT (omp_for_parse_state->declv, లోతు) = decl;
      వృక్షం_VEC_ELT (omp_for_parse_state->initv, లోతు) = init;
      వృక్షం_VEC_ELT (omp_for_parse_state->condv, లోతు) = cond;
      వృక్షం_VEC_ELT (omp_for_parse_state->incrv, లోతు) = incr;
    }

parse_తదుపరి:
  moreloops = లోతు < omp_for_parse_state->లెక్క - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  ఒకవేళ (moreloops
      && c_parser_omp_తదుపరి_టోకెన్లు_can_be_canon_loop (parser,
						     omp_for_parse_state->సంకేతం_2,
						     అబద్ధం))
    {
      omp_for_parse_state->లోతు++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->లోతు--;
    }
  లేకపోతే ఒకవేళ (moreloops && c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
    {
      /* This is the open brace in the loop-body grammar production.  Rather
	 than trying to special-case braces, just parse it as a compound
	 statement and handle the nested loop-body case there.  Note that
	 when we see a further open brace inside the compound statement
	 loop-body, we don't know whether it is the start of intervening
	 code that is a compound statement, or a level of braces
	 surrounding a nested loop-body.  Use the WANT_NESTED_LOOP state
	 bit to ensure we have only one nested loop at each level.  */
      omp_for_parse_state->లోపల_intervening_సంకేతం = నిజం;
      body = c_parser_compound_statement (parser, ఖాళీ);
      omp_for_parse_state->లోపల_intervening_సంకేతం = అబద్ధం;
      ఒకవేళ (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = నిజం;
	}
      if_p = ఖాళీ;
    }
  లేకపోతే
    {
      /* This is the final-loop-body case in the grammar: we have
	 something that is not a FOR and not an open brace.  */
      ఒకవేళ (moreloops)
	{
	  /* If we were expecting a nested loop, give an error and mark
	     that parsing has failed, and try to recover by parsing the
	     body as regular code without further collapsing.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = నిజం;
	}
      లోపల_statement = లోపల_OMP_FOR;
      parser->omp_for_parse_state = ఖాళీ;
      body = నెట్టు_stmt_list ();
      ఒకవేళ (omp_for_parse_state->inscan)
	c_parser_omp_పరిశీలన_loop_body (parser, అబద్ధం);
      లేకపోతే
	కూడు_stmt (c_parser_c99_ఖండం_statement (parser, if_p));
      body = తీయి_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  లోపల_statement = save_లోపల_statement;
  omp_for_parse_state->want_nested_loop = అబద్ధం;
  omp_for_parse_state->లోపల_intervening_సంకేతం = నిజం;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  ఒకవేళ (body)
    కూడు_stmt (body);
  body = c_చివర_compound_stmt (loc, loop_scope, నిజం);
  ఒకవేళ (decl && వృక్షం_సంకేతం (body) == BIND_సమాసం)
    {
      వృక్షం t = BIND_సమాసం_VARS (body);
      వృక్షం prev = NULL_వృక్షం, తదుపరి = NULL_వృక్షం;
      అయితే (t)
	{
	  తదుపరి = DECL_CHAIN (t);
	  ఒకవేళ (t == decl)
	    {
	      ఒకవేళ (prev)
		DECL_CHAIN (prev) = తదుపరి;
	      లేకపోతే
		{
		  BIND_సమాసం_VARS (body) = తదుపరి;
		  ఖండం_VARS (BIND_సమాసం_ఖండం (body)) = తదుపరి;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      ఆపు;
	    }
	  లేకపోతే
	    {
	      prev = t;
	      t = తదుపరి;
	    }
	}
      ఒకవేళ (BIND_సమాసం_VARS (body) == NULL_వృక్షం)
	body = BIND_సమాసం_BODY (body);
    }

  తిరిగి body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

స్థిర వృక్షం
c_parser_omp_for_loop (location_t loc, c_parser *parser, గణన వృక్షం_సంకేతం_2 సంకేతం_2,
		       వృక్షం clauses, వృక్షం *cclauses, తార్కిక *if_p)
{
  వృక్షం body, stmt, cl;
  వృక్షం ret = NULL_వృక్షం;
  వృక్షం ordered_cl = NULL_వృక్షం;
  పూర్ణాంకం i, collapse = 1, ordered = 0, లెక్క;
  తార్కిక oacc_tiling = అబద్ధం;
  తార్కిక inscan = అబద్ధం;
  నిర్మాణం omp_for_parse_దత్తాంశం దత్తాంశం;
  నిర్మాణం omp_for_parse_దత్తాంశం *save_దత్తాంశం = parser->omp_for_parse_state;

  కొరకు (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    ఒకవేళ (OMP_CLAUSE_సంకేతం (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = వృక్షం_గమ్యం_shwi (OMP_CLAUSE_COLLAPSE_సమాసం (cl));
    లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = నిజం;
	collapse = list_నిడివి (OMP_CLAUSE_TILE_LIST (cl));
      }
    లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (cl) == OMP_CLAUSE_SIZES)
      collapse = list_నిడివి (OMP_CLAUSE_SIZES_LIST (cl));
    లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_సమాసం (cl))
      {
	ordered_cl = cl;
	ordered = వృక్షం_గమ్యం_shwi (OMP_CLAUSE_ORDERED_సమాసం (cl));
      }
    లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (సంకేతం_2 == OMP_SIMD || సంకేతం_2 == OMP_FOR))
      inscan = నిజం;

  ఒకవేళ (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_సమాసం (ordered_cl)
	= build_int_cst (integer_type_కణుపు, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  లెక్క = ordered ? ordered : collapse;

  ఒకవేళ (!c_parser_omp_తదుపరి_టోకెన్లు_can_be_canon_loop (parser, సంకేతం_2, నిజం))
    తిరిగి ఖాళీ;

  /* Initialize parse state for recursive descent.  */
  దత్తాంశం.declv = make_వృక్షం_vec (లెక్క);
  దత్తాంశం.initv = make_వృక్షం_vec (లెక్క);
  దత్తాంశం.condv = make_వృక్షం_vec (లెక్క);
  దత్తాంశం.incrv = make_వృక్షం_vec (లెక్క);
  దత్తాంశం.pre_body = NULL_వృక్షం;
  దత్తాంశం.bindings = NULL_వృక్షం;
  దత్తాంశం.for_loc = c_parser_peek_token (parser)->location;
  దత్తాంశం.లెక్క = లెక్క;
  దత్తాంశం.లోతు = 0;
  దత్తాంశం.want_nested_loop = నిజం;
  దత్తాంశం.ordered = ordered > 0;
  దత్తాంశం.లోపల_intervening_సంకేతం = అబద్ధం;
  దత్తాంశం.perfect_nesting_fail = అబద్ధం;
  దత్తాంశం.fail = అబద్ధం;
  దత్తాంశం.inscan = inscan;
  దత్తాంశం.saw_intervening_సంకేతం = అబద్ధం;
  దత్తాంశం.సంకేతం_2 = సంకేతం_2;
  parser->omp_for_parse_state = &దత్తాంశం;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  కొరకు (వృక్షం t = దత్తాంశం.bindings; t; )
    {
      వృక్షం n = వృక్షం_CHAIN (t);
      వృక్షం_CHAIN (t) = NULL_వృక్షం;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  ఒకవేళ (!దత్తాంశం.fail)
    {
      c_లోపల_omp_for = నిజం;
      stmt = c_ముగింపు_omp_for (loc, సంకేతం_2, దత్తాంశం.declv, ఖాళీ, దత్తాంశం.initv,
			       దత్తాంశం.condv, దత్తాంశం.incrv,
			       body, దత్తాంశం.pre_body, నిజం);
      c_లోపల_omp_for = అబద్ధం;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      ఒకవేళ (stmt && !c_omp_check_loop_iv (stmt, దత్తాంశం.declv, ఖాళీ))
	stmt = NULL_వృక్షం;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      ఒకవేళ (దత్తాంశం.saw_intervening_సంకేతం
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, ఖాళీ))
	stmt = NULL_వృక్షం;

      ఒకవేళ (stmt)
	{
	  కూడు_stmt (stmt);

	  కొరకు (i = 0; i < వృక్షం_VEC_నిడివి (OMP_FOR_INIT (stmt)); i++)
	    {
	      వృక్షం init = వృక్షం_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      ఒకవేళ (init == NULL_వృక్షం)
		ఆపు;
	      gcc_assert (వృక్షం_సంకేతం (init) == MODIFY_సమాసం);
	      వృక్షం decl = వృక్షం_నిర్వాహ్యం (init, 0);
	      వృక్షం cond = వృక్షం_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (వృక్షం_నిర్వాహ్యం (cond, 0) == decl);

	      వృక్షం op0 = వృక్షం_నిర్వాహ్యం (init, 1);
	      ఒకవేళ (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || వృక్షం_సంకేతం (op0) != వృక్షం_VEC)
		వృక్షం_నిర్వాహ్యం (init, 1) = c_fully_fold (op0, అబద్ధం, ఖాళీ);
	      లేకపోతే
		{
		  వృక్షం_VEC_ELT (op0, 1)
		    = c_fully_fold (వృక్షం_VEC_ELT (op0, 1), అబద్ధం, ఖాళీ);
		  వృక్షం_VEC_ELT (op0, 2)
		    = c_fully_fold (వృక్షం_VEC_ELT (op0, 2), అబద్ధం, ఖాళీ);
		}

	      వృక్షం op1 = వృక్షం_నిర్వాహ్యం (cond, 1);
	      ఒకవేళ (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || వృక్షం_సంకేతం (op1) != వృక్షం_VEC)
		వృక్షం_నిర్వాహ్యం (cond, 1) = c_fully_fold (op1, అబద్ధం, ఖాళీ);
	      లేకపోతే
		{
		  వృక్షం_VEC_ELT (op1, 1)
		    = c_fully_fold (వృక్షం_VEC_ELT (op1, 1), అబద్ధం, ఖాళీ);
		  వృక్షం_VEC_ELT (op1, 2)
		    = c_fully_fold (వృక్షం_VEC_ELT (op1, 2), అబద్ధం, ఖాళీ);
		}
	    }

	  ఒకవేళ (cclauses != ఖాళీ
	      && cclauses[C_OMP_CLAUSE_విభజించు_PARALLEL] != ఖాళీ)
	    {
	      వృక్షం *c;
	      కొరకు (c = &cclauses[C_OMP_CLAUSE_విభజించు_PARALLEL]; *c ; )
		ఒకవేళ (OMP_CLAUSE_సంకేతం (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_సంకేతం (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		లేకపోతే
		  {
		    కొరకు (i = 0; i < లెక్క; i++)
		      ఒకవేళ (వృక్షం_VEC_ELT (దత్తాంశం.declv, i) == OMP_CLAUSE_DECL (*c))
			ఆపు;
		    ఒకవేళ (i == లెక్క)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (*c) == OMP_CLAUSE_FIRSTPRIVATE)
		      {
			error_at (loc,
				  "iteration variable %qD should not be firstprivate",
				  OMP_CLAUSE_DECL (*c));
			*c = OMP_CLAUSE_CHAIN (*c);
		      }
		    లేకపోతే
		      {
			/* Move lastprivate (decl) clause to
			   OMP_FOR_CLAUSES.  */
			వృక్షం l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			ఒకవేళ (సంకేతం_2 == OMP_SIMD)
			  {
			    OMP_CLAUSE_CHAIN (l)
			      = cclauses[C_OMP_CLAUSE_విభజించు_FOR];
			    cclauses[C_OMP_CLAUSE_విభజించు_FOR] = l;
			  }
			లేకపోతే
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

  parser->omp_for_parse_state = save_దత్తాంశం;
  తిరిగి ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

స్థిర శూన్య
omp_విభజించు_clauses (location_t loc, గణన వృక్షం_సంకేతం_2 సంకేతం_2,
		   omp_clause_ముసుగు ముసుగు, వృక్షం clauses, వృక్షం *cclauses)
{
  పూర్ణాంకం i;
  c_omp_విభజించు_clauses (loc, సంకేతం_2, ముసుగు, clauses, cclauses);
  కొరకు (i = 0; i < C_OMP_CLAUSE_విభజించు_లెక్క; i++)
    ఒకవేళ (cclauses[i])
      cclauses[i] = c_ముగింపు_omp_clauses (cclauses[i],
					  i == C_OMP_CLAUSE_విభజించు_లక్ష్యం
					  ? C_ORT_OMP_లక్ష్యం : C_ORT_OMP);
}

/* OpenMP 5.0:
   #pragma omp loop loop-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#నిర్వచించు OMP_LOOP_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_వ్యక్తిగత)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_BIND)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_క్రమం))

స్థిర వృక్షం
c_parser_omp_loop (location_t loc, c_parser *parser,
		   అక్షరం *p_name, omp_clause_ముసుగు ముసుగు, వృక్షం *cclauses,
		   తార్కిక *if_p)
{
  వృక్షం ఖండం, clauses, ret;

  strcat (p_name, " loop");
  ముసుగు |= OMP_LOOP_CLAUSE_ముసుగు;

  clauses = c_parser_omp_all_clauses (parser, ముసుగు, p_name, cclauses == ఖాళీ);
  ఒకవేళ (cclauses)
    {
      omp_విభజించు_clauses (loc, OMP_LOOP, ముసుగు, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_విభజించు_LOOP];
    }

  ఖండం = c_begin_compound_stmt (నిజం);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
  కూడు_stmt (ఖండం);

  తిరిగి ret;
}

/* OpenMP 4.0:
   #pragma omp simd simd-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#నిర్వచించు OMP_SIMD_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_SAFELEN)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_SIMDLEN)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_రేఖీయ)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ALIGNED)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_వ్యక్తిగత)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NONTEMPORAL)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_క్రమం))

స్థిర వృక్షం
c_parser_omp_simd (location_t loc, c_parser *parser,
		   అక్షరం *p_name, omp_clause_ముసుగు ముసుగు, వృక్షం *cclauses,
		   తార్కిక *if_p)
{
  వృక్షం ఖండం, clauses, ret;

  strcat (p_name, " simd");
  ముసుగు |= OMP_SIMD_CLAUSE_ముసుగు;

  clauses = c_parser_omp_all_clauses (parser, ముసుగు, p_name, cclauses == ఖాళీ);
  ఒకవేళ (cclauses)
    {
      omp_విభజించు_clauses (loc, OMP_SIMD, ముసుగు, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_విభజించు_SIMD];
    }

  ఖండం = c_begin_compound_stmt (నిజం);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
  కూడు_stmt (ఖండం);

  తిరిగి ret;
}

/* OpenMP 2.5:
   #pragma omp for for-clause[optseq] new-line
     for-loop

   OpenMP 4.0:
   #pragma omp for simd for-simd-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#నిర్వచించు OMP_FOR_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_వ్యక్తిగత)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_రేఖీయ)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ORDERED)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_కాలపట్టిక)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_క్రమం))

స్థిర వృక్షం
c_parser_omp_for (location_t loc, c_parser *parser,
		  అక్షరం *p_name, omp_clause_ముసుగు ముసుగు, వృక్షం *cclauses,
		  తార్కిక *if_p)
{
  వృక్షం ఖండం, clauses, ret;

  strcat (p_name, " for");
  ముసుగు |= OMP_FOR_CLAUSE_ముసుగు;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  ఒకవేళ (cclauses && (ముసుగు & (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    ముసుగు &= ~(OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  ఒకవేళ ((ముసుగు & (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DIST_కాలపట్టిక)) != 0)
    ముసుగు &= ~(OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);

      ఒకవేళ (strcmp (p, "simd") == 0)
	{
	  వృక్షం cclauses_buf[C_OMP_CLAUSE_విభజించు_లెక్క];
	  ఒకవేళ (cclauses == ఖాళీ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	    తిరిగి c_parser_omp_simd (loc, parser, p_name, ముసుగు, cclauses,
				      if_p);
	  ఖండం = c_begin_compound_stmt (నిజం);
	  ret = c_parser_omp_simd (loc, parser, p_name, ముసుగు, cclauses, if_p);
	  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
	  ఒకవేళ (ret == NULL_వృక్షం)
	    తిరిగి ret;
	  ret = make_కణుపు (OMP_FOR);
	  వృక్షం_TYPE (ret) = void_type_కణుపు;
	  OMP_FOR_BODY (ret) = ఖండం;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_విభజించు_FOR];
	  సమితి_సమాసం_LOCATION (ret, loc);
	  కూడు_stmt (ret);
	  తిరిగి ret;
	}
    }
  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
      తిరిగి NULL_వృక్షం;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  ఒకవేళ ((ముసుగు & (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DIST_కాలపట్టిక)) != 0)
    ముసుగు &= ~(OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_రేఖీయ);

  clauses = c_parser_omp_all_clauses (parser, ముసుగు, p_name, cclauses == ఖాళీ);
  ఒకవేళ (cclauses)
    {
      omp_విభజించు_clauses (loc, OMP_FOR, ముసుగు, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_విభజించు_FOR];
    }

  ఖండం = c_begin_compound_stmt (నిజం);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
  కూడు_stmt (ఖండం);

  తిరిగి ret;
}

స్థిర వృక్షం c_parser_omp_taskloop (location_t, c_parser *, అక్షరం *,
				   omp_clause_ముసుగు, వృక్షం *, తార్కిక *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

స్థిర వృక్షం
c_parser_omp_master (location_t loc, c_parser *parser,
		     అక్షరం *p_name, omp_clause_ముసుగు ముసుగు, వృక్షం *cclauses,
		     తార్కిక *if_p, location_t master_loc)
{
  వృక్షం ఖండం, clauses, ret;
  gcc_rich_location richloc (loc);
  ఒకవేళ (master_loc != UNKNOWN_LOCATION)
    richloc.కూడు_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  strcat (p_name, " master");

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);

      ఒకవేళ (strcmp (p, "taskloop") == 0)
	{
	  వృక్షం cclauses_buf[C_OMP_CLAUSE_విభజించు_లెక్క];
	  ఒకవేళ (cclauses == ఖాళీ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	    తిరిగి c_parser_omp_taskloop (loc, parser, p_name, ముసుగు, cclauses,
					  if_p);
	  ఖండం = c_begin_compound_stmt (నిజం);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, ముసుగు, cclauses,
				       if_p);
	  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
	  ఒకవేళ (ret == NULL_వృక్షం)
	    తిరిగి ret;
	  ret = c_ముగింపు_omp_master (loc, ఖండం);
	  OMP_MASTER_COMBINED (ret) = 1;
	  తిరిగి ret;
	}
    }
  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
      తిరిగి NULL_వృక్షం;
    }

  ఒకవేళ (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, ముసుగు, p_name, అబద్ధం);
      omp_విభజించు_clauses (loc, OMP_MASTER, ముసుగు, clauses, cclauses);
    }
  లేకపోతే
    c_parser_skip_గమ్యం_pragma_eol (parser);

  తిరిగి c_ముగింపు_omp_master (loc, c_parser_omp_structured_ఖండం (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#నిర్వచించు OMP_MASKED_CLAUSE_ముసుగు					\
	(OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FILTER)

స్థిర వృక్షం
c_parser_omp_masked (location_t loc, c_parser *parser,
		     అక్షరం *p_name, omp_clause_ముసుగు ముసుగు, వృక్షం *cclauses,
		     తార్కిక *if_p)
{
  వృక్షం ఖండం, clauses, ret;

  strcat (p_name, " masked");
  ముసుగు |= OMP_MASKED_CLAUSE_ముసుగు;

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);

      ఒకవేళ (strcmp (p, "taskloop") == 0)
	{
	  వృక్షం cclauses_buf[C_OMP_CLAUSE_విభజించు_లెక్క];
	  ఒకవేళ (cclauses == ఖాళీ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	    తిరిగి c_parser_omp_taskloop (loc, parser, p_name, ముసుగు, cclauses,
					  if_p);
	  ఖండం = c_begin_compound_stmt (నిజం);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, ముసుగు, cclauses,
				       if_p);
	  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
	  ఒకవేళ (ret == NULL_వృక్షం)
	    తిరిగి ret;
	  ret = c_ముగింపు_omp_masked (loc, ఖండం,
				     cclauses[C_OMP_CLAUSE_విభజించు_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  తిరిగి ret;
	}
    }
  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
      తిరిగి NULL_వృక్షం;
    }

  clauses = c_parser_omp_all_clauses (parser, ముసుగు, p_name, cclauses == ఖాళీ);
  ఒకవేళ (cclauses)
    {
      omp_విభజించు_clauses (loc, OMP_MASKED, ముసుగు, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_విభజించు_MASKED];
    }

  తిరిగి c_ముగింపు_omp_masked (loc, c_parser_omp_structured_ఖండం (parser,
								  if_p),
			      clauses);
}

/* OpenMP 5.1:
   # pragma omp interop clauses[opt] new-line */

#నిర్వచించు OMP_INTEROP_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DESTROY)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_INIT)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_USE))

స్థిర శూన్య
c_parser_omp_interop (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  వృక్షం clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_ముసుగు,
					   "#pragma omp interop");
  వృక్షం stmt = make_కణుపు (OMP_INTEROP);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  సమితి_సమాసం_LOCATION (stmt, loc);
  కూడు_stmt (stmt);
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

#నిర్వచించు OMP_ORDERED_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_దారాలు)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_SIMD))

#నిర్వచించు OMP_ORDERED_DEPEND_CLAUSE_ముసుగు				\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DOACROSS))

స్థిర తార్కిక
c_parser_omp_ordered (c_parser *parser, గణన pragma_context context,
		      తార్కిక *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  ఒకవేళ (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
      తిరిగి అబద్ధం;
    }

  పూర్ణాంకం n = 1;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
    n = 2;

  ఒకవేళ (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      స్థిరరాశి అక్షరం *p
	= IDENTIFIER_సూచిక (c_parser_peek_nth_token (parser, n)->విలువ);

      ఒకవేళ (!strcmp ("depend", p) || !strcmp ("doacross", p))
	{
	  ఒకవేళ (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	      తిరిగి అబద్ధం;
	    }
	  ఒకవేళ (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	      తిరిగి నిజం;
	    }

	  వృక్షం clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_ముసుగు,
					"#pragma omp ordered");
	  c_ముగింపు_omp_ordered (loc, clauses, NULL_వృక్షం);
	  తిరిగి అబద్ధం;
	}
    }

  వృక్షం clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_ముసుగు,
					   "#pragma omp ordered");

  ఒకవేళ (!flag_openmp	/* flag_openmp_simd  */
      && omp_కనుగొను_clause (clauses, OMP_CLAUSE_SIMD) == NULL_వృక్షం)
    తిరిగి అబద్ధం;

  c_ముగింపు_omp_ordered (loc, clauses,
			c_parser_omp_structured_ఖండం (parser, if_p));
  తిరిగి నిజం;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

స్థిర వృక్షం
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  వృక్షం stmt, substmt;
  తార్కిక error_suppress = అబద్ధం;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = అబద్ధం;
      తిరిగి NULL_వృక్షం;
    }

  stmt = నెట్టు_stmt_list ();

  ఒకవేళ (c_parser_peek_token (parser)->pragma_రకం != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_పరిశీలన (parser, "section", నిజం))
    {
      substmt = c_parser_omp_structured_ఖండం_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_కణుపు, substmt);
      సమితి_సమాసం_LOCATION (substmt, loc);
      కూడు_stmt (substmt);
    }

  అయితే (1)
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
	ఆపు;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_EOF))
	ఆపు;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_పరిశీలన (parser, "section", అబద్ధం);
      ఒకవేళ (c_parser_peek_token (parser)->pragma_రకం == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_గమ్యం_pragma_eol (parser);
	  error_suppress = అబద్ధం;
	}
      లేకపోతే ఒకవేళ (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = నిజం;
	}

      substmt = c_parser_omp_structured_ఖండం_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_కణుపు, substmt);
      సమితి_సమాసం_LOCATION (substmt, loc);
      కూడు_stmt (substmt);
    }
  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = తీయి_stmt_list (stmt);

  stmt = make_కణుపు (OMP_SECTIONS);
  సమితి_సమాసం_LOCATION (stmt, sections_loc);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OMP_SECTIONS_BODY (stmt) = substmt;

  తిరిగి కూడు_stmt (stmt);
}

/* OpenMP 2.5:
   # pragma omp sections sections-clause[optseq] newline
     sections-scope

   LOC is the location of the #pragma token.
*/

#నిర్వచించు OMP_SECTIONS_CLAUSE_ముసుగు				\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_వ్యక్తిగత)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

స్థిర వృక్షం
c_parser_omp_sections (location_t loc, c_parser *parser,
		       అక్షరం *p_name, omp_clause_ముసుగు ముసుగు, వృక్షం *cclauses)
{
  వృక్షం ఖండం, clauses, ret;

  strcat (p_name, " sections");
  ముసుగు |= OMP_SECTIONS_CLAUSE_ముసుగు;
  ఒకవేళ (cclauses)
    ముసుగు &= ~(OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, ముసుగు, p_name, cclauses == ఖాళీ);
  ఒకవేళ (cclauses)
    {
      omp_విభజించు_clauses (loc, OMP_SECTIONS, ముసుగు, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_విభజించు_SECTIONS];
    }

  ఖండం = c_begin_compound_stmt (నిజం);
  ret = c_parser_omp_sections_scope (loc, parser);
  ఒకవేళ (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
  కూడు_stmt (ఖండం);

  తిరిగి ret;
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

#నిర్వచించు OMP_PARALLEL_CLAUSE_ముసుగు				\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_వ్యక్తిగత)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_COPYIN)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_అంకె_దారాలు)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

స్థిర వృక్షం
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       అక్షరం *p_name, omp_clause_ముసుగు ముసుగు, వృక్షం *cclauses,
		       తార్కిక *if_p)
{
  వృక్షం stmt, clauses, ఖండం;

  strcat (p_name, " parallel");
  ముసుగు |= OMP_PARALLEL_CLAUSE_ముసుగు;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  ఒకవేళ ((ముసుగు & (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (ముసుగు & (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DIST_కాలపట్టిక)) == 0)
    ముసుగు &= ~(OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_FOR))
    {
      వృక్షం cclauses_buf[C_OMP_CLAUSE_విభజించు_లెక్క];
      ఒకవేళ (cclauses == ఖాళీ)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	తిరిగి c_parser_omp_for (loc, parser, p_name, ముసుగు, cclauses, if_p);
      ఖండం = c_begin_omp_parallel ();
      వృక్షం ret = c_parser_omp_for (loc, parser, p_name, ముసుగు, cclauses, if_p);
      stmt
	= c_ముగింపు_omp_parallel (loc, cclauses[C_OMP_CLAUSE_విభజించు_PARALLEL],
				 ఖండం);
      ఒకవేళ (ret == NULL_వృక్షం)
	తిరిగి ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      తిరిగి stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  లేకపోతే ఒకవేళ (cclauses
	   && (ముసుగు & (OMP_CLAUSE_ముసుగు_1
		       << PRAGMA_OMP_CLAUSE_DIST_కాలపట్టిక)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_గమ్యం_pragma_eol (parser);
      తిరిగి NULL_వృక్షం;
    }
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      location_t ploc = c_parser_peek_token (parser)->location;
      ఒకవేళ (cclauses == ఖాళీ && strcmp (p, "masked") == 0)
	{
	  వృక్షం cclauses_buf[C_OMP_CLAUSE_విభజించు_లెక్క];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	    తిరిగి c_parser_omp_masked (loc, parser, p_name, ముసుగు, cclauses,
					if_p);
	  ఖండం = c_begin_omp_parallel ();
	  వృక్షం ret = c_parser_omp_masked (loc, parser, p_name, ముసుగు, cclauses,
					  if_p);
	  stmt = c_ముగింపు_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_విభజించు_PARALLEL],
					ఖండం);
	  ఒకవేళ (ret == ఖాళీ)
	    తిరిగి ret;
	  /* masked does have just filter clause, but during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel masked don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel masked
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel masked taskloop simd lastprivate (x)  */
	  ఒకవేళ (OMP_MASKED_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  తిరిగి stmt;
	}
      లేకపోతే ఒకవేళ (cclauses == ఖాళీ && strcmp (p, "master") == 0)
	{
	  వృక్షం cclauses_buf[C_OMP_CLAUSE_విభజించు_లెక్క];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	    తిరిగి c_parser_omp_master (loc, parser, p_name, ముసుగు, cclauses,
					if_p, ploc);
	  ఖండం = c_begin_omp_parallel ();
	  వృక్షం ret = c_parser_omp_master (loc, parser, p_name, ముసుగు, cclauses,
					  if_p, ploc);
	  stmt = c_ముగింపు_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_విభజించు_PARALLEL],
					ఖండం);
	  ఒకవేళ (ret == ఖాళీ)
	    తిరిగి ret;
	  /* master doesn't have any clauses and during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel master don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel master
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel master taskloop simd lastprivate (x)  */
	  ఒకవేళ (OMP_MASTER_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  తిరిగి stmt;
	}
      లేకపోతే ఒకవేళ (strcmp (p, "loop") == 0)
	{
	  వృక్షం cclauses_buf[C_OMP_CLAUSE_విభజించు_లెక్క];
	  ఒకవేళ (cclauses == ఖాళీ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	    తిరిగి c_parser_omp_loop (loc, parser, p_name, ముసుగు, cclauses,
				      if_p);
	  ఖండం = c_begin_omp_parallel ();
	  వృక్షం ret = c_parser_omp_loop (loc, parser, p_name, ముసుగు, cclauses,
					if_p);
	  stmt
	    = c_ముగింపు_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_విభజించు_PARALLEL],
				     ఖండం);
	  ఒకవేళ (ret == NULL_వృక్షం)
	    తిరిగి ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  తిరిగి stmt;
	}
      లేకపోతే ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	  తిరిగి NULL_వృక్షం;
	}
      లేకపోతే ఒకవేళ (cclauses == ఖాళీ && strcmp (p, "sections") == 0)
	{
	  వృక్షం cclauses_buf[C_OMP_CLAUSE_విభజించు_లెక్క];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ఖండం = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, ముసుగు, cclauses);
	  stmt = c_ముగింపు_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_విభజించు_PARALLEL],
					ఖండం);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  తిరిగి stmt;
	}
    }
  లేకపోతే ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
      తిరిగి NULL_వృక్షం;
    }

  clauses = c_parser_omp_all_clauses (parser, ముసుగు, p_name, cclauses == ఖాళీ);
  ఒకవేళ (cclauses)
    {
      omp_విభజించు_clauses (loc, OMP_PARALLEL, ముసుగు, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_విభజించు_PARALLEL];
    }

  ఖండం = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = నిజం;
  c_parser_statement (parser, if_p);
  stmt = c_ముగింపు_omp_parallel (loc, clauses, ఖండం);

  తిరిగి stmt;
}

/* OpenMP 2.5:
   # pragma omp single single-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma.
*/

#నిర్వచించు OMP_SINGLE_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_వ్యక్తిగత)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_COPYPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

స్థిర వృక్షం
c_parser_omp_single (location_t loc, c_parser *parser, తార్కిక *if_p)
{
  వృక్షం stmt = make_కణుపు (OMP_SINGLE);
  సమితి_సమాసం_LOCATION (stmt, loc);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_ముసుగు,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_ఖండం (parser, if_p);

  తిరిగి కూడు_stmt (stmt);
}

/* OpenMP 5.1:
   # pragma omp scope scope-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma.
*/

#నిర్వచించు OMP_SCOPE_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_వ్యక్తిగత)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

స్థిర వృక్షం
c_parser_omp_scope (location_t loc, c_parser *parser, తార్కిక *if_p)
{
  వృక్షం stmt = make_కణుపు (OMP_SCOPE);
  సమితి_సమాసం_LOCATION (stmt, loc);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_ముసుగు,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_ఖండం (parser, if_p);

  తిరిగి కూడు_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
స్థిర వృక్షం
c_parser_omp_dispatch_body (c_parser *parser)
{
  నిర్మాణం c_సమాసం lhs, rhs, ret;
  location_t సమాసం_loc = c_parser_peek_token (parser)->location;
  ఆధారం_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_వ్యక్తీకరణ (parser, ఖాళీ, ఖాళీ);
  ఒకవేళ (వృక్షం_సంకేతం (lhs.విలువ) == CALL_సమాసం)
    తిరిగి lhs.విలువ;

  location_t op_location = c_parser_peek_token (parser)->location;
  ఒకవేళ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    తిరిగి error_mark_కణుపు;

  /* Parse function name.  */
  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      తిరిగి error_mark_కణుపు;
    }
  సమాసం_loc = c_parser_peek_token (parser)->location;
  వృక్షం id = c_parser_peek_token (parser)->విలువ;
  c_parser_consume_token (parser);
  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      తిరిగి error_mark_కణుపు;
    }

  rhs.విలువ = build_external_ref (సమాసం_loc, id, నిజం, &rhs.original_type);
  సమితి_c_సమాసం_ఆధారం_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_వ్యక్తీకరణ_after_primary (
    parser, సమాసం_LOC_OR_LOC (rhs.విలువ, సమాసం_loc), rhs);
  ఒకవేళ (వృక్షం_సంకేతం (rhs.విలువ) != CALL_సమాసం)
    {
      error_at (సమాసం_LOC_OR_LOC (rhs.విలువ, సమాసం_loc),
		"expected target-function call");
      తిరిగి error_mark_కణుపు;
    }

  /* Build assignment. */
  rhs = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, rhs, నిజం, నిజం);
  ret.విలువ
    = build_modify_సమాసం (op_location, lhs.విలువ, lhs.original_type, NOP_సమాసం,
			 సమాసం_loc, rhs.విలువ, rhs.original_type);
  ret.m_decimal = 0;
  సమితి_c_సమాసం_ఆధారం_range (&ret, lhs.get_ప్రారంభం (), rhs.get_ముగింపు ());
  ret.original_సంకేతం = MODIFY_సమాసం;
  ret.original_type = ఖాళీ;
  తిరిగి ret.విలువ;
}

/* OpenMP 5.1:
   # pragma omp dispatch dispatch-clause[optseq] new-line
     expression-stmt

   LOC is the location of the #pragma.
*/

#నిర్వచించు OMP_DISPATCH_CLAUSE_ముసుగు                                               \
  ((OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEVICE)                             \
   | (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEPEND)                           \
   | (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOVARIANTS)                       \
   | (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOCONTEXT)                        \
   | (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR)                  \
   | (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_INTEROP)                          \
   | (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR)                    \
   | (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

స్థిర వృక్షం
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  వృక్షం stmt = make_కణుపు (OMP_DISPATCH);
  సమితి_సమాసం_LOCATION (stmt, loc);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_ముసుగు,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  వృక్షం depend_clauses = NULL_వృక్షం;
  వృక్షం *depend_clauses_ptr = &depend_clauses;
  కొరకు (వృక్షం c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  ఒకవేళ (depend_clauses != NULL_వృక్షం)
    {
      వృక్షం stmt = make_కణుపు (OMP_TASK);
      వృక్షం_TYPE (stmt) = void_కణుపు;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_వృక్షం;
      సమితి_సమాసం_LOCATION (stmt, loc);
      కూడు_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  వృక్షం dispatch_body = c_parser_omp_dispatch_body (parser);
  ఒకవేళ (dispatch_body == error_mark_కణుపు)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser);
      తిరిగి NULL_వృక్షం;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (వృక్షం_సంకేతం (dispatch_body) == CALL_సమాసం
	      || వృక్షం_సంకేతం (dispatch_body) == MODIFY_సమాసం);
  వృక్షం *dispatch_call = వృక్షం_సంకేతం (dispatch_body) == MODIFY_సమాసం
			  ? &వృక్షం_నిర్వాహ్యం (dispatch_body, 1)
			  : &dispatch_body;
  అయితే (వృక్షం_సంకేతం (*dispatch_call) == FLOAT_సమాసం
	 || వృక్షం_సంకేతం (*dispatch_call) == CONVERT_సమాసం
	 || వృక్షం_సంకేతం (*dispatch_call) == NOP_సమాసం)
    dispatch_call = &వృక్షం_నిర్వాహ్యం (*dispatch_call, 0);
  *dispatch_call = build_call_సమాసం_అంతర్గత_loc (
    loc, IFN_GOMP_DISPATCH,
    వృక్షం_TYPE (వృక్షం_TYPE (CALL_సమాసం_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  తిరిగి కూడు_stmt (stmt);
}

/* OpenMP 3.0:
   # pragma omp task task-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#నిర్వచించు OMP_TASK_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_UNTIED)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_వ్యక్తిగత)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FINAL)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_MERGEABLE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ప్రాధాన్యత)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_లోపల_REDUCTION)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DETACH)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_AFFINITY))

స్థిర వృక్షం
c_parser_omp_task (location_t loc, c_parser *parser, తార్కిక *if_p)
{
  వృక్షం clauses, ఖండం;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_ముసుగు,
				      "#pragma omp task");

  ఖండం = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = నిజం;
  c_parser_statement (parser, if_p);
  తిరిగి c_ముగింపు_omp_task (loc, clauses, ఖండం);
}

/* OpenMP 3.0:
   # pragma omp taskwait new-line

   OpenMP 5.0:
   # pragma omp taskwait taskwait-clause[optseq] new-line
*/

#నిర్వచించు OMP_TASKWAIT_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEPEND)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

స్థిర శూన్య
c_parser_omp_taskwait (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  వృక్షం clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_ముసుగు,
				"#pragma omp taskwait");

  ఒకవేళ (clauses)
    {
      వృక్షం stmt = make_కణుపు (OMP_TASK);
      వృక్షం_TYPE (stmt) = void_కణుపు;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_వృక్షం;
      సమితి_సమాసం_LOCATION (stmt, loc);
      కూడు_stmt (stmt);
    }
  లేకపోతే
    c_ముగింపు_omp_taskwait (loc);
}

/* OpenMP 3.1:
   # pragma omp taskyield new-line
*/

స్థిర శూన్య
c_parser_omp_taskyield (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  c_parser_skip_గమ్యం_pragma_eol (parser);

  c_ముగింపు_omp_taskyield (loc);
}

/* OpenMP 4.0:
   # pragma omp taskgroup new-line

   OpenMP 5.0:
   # pragma omp taskgroup taskgroup-clause[optseq] new-line
*/

#నిర్వచించు OMP_TASKGROUP_CLAUSE_ముసుగు				\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_TASK_REDUCTION))

స్థిర వృక్షం
c_parser_omp_taskgroup (location_t loc, c_parser *parser, తార్కిక *if_p)
{
  వృక్షం clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_ముసుగు,
					   "#pragma omp taskgroup");

  వృక్షం body = c_parser_omp_structured_ఖండం (parser, if_p);
  తిరిగి c_ముగింపు_omp_taskgroup (loc, body, clauses);
}

/* OpenMP 4.0:
   # pragma omp cancel cancel-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#నిర్వచించు OMP_CANCEL_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_PARALLEL)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FOR)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_SECTIONS)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_TASKGROUP)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_IF))

స్థిర శూన్య
c_parser_omp_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);
  వృక్షం clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_ముసుగు,
					   "#pragma omp cancel");

  c_ముగింపు_omp_cancel (loc, clauses);
}

/* OpenMP 4.0:
   # pragma omp cancellation point cancelpt-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#నిర్వచించు OMP_CANCELLATION_బిందువు_CLAUSE_ముసుగు			\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_PARALLEL)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FOR)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_SECTIONS)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_TASKGROUP))

స్థిర తార్కిక
c_parser_omp_cancellation_బిందువు (c_parser *parser, గణన pragma_context context)
{
  location_t loc = c_parser_peek_token (parser)->location;
  వృక్షం clauses;
  తార్కిక బిందువు_చూసిన = అబద్ధం;

  c_parser_consume_pragma (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  బిందువు_చూసిన = నిజం;
	}
    }
  ఒకవేళ (!బిందువు_చూసిన)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_గమ్యం_pragma_eol (parser);
      తిరిగి అబద్ధం;
    }

  ఒకవేళ (context != pragma_compound)
    {
      ఒకవేళ (context == pragma_stmt)
	error_at (loc,
		  "%<#pragma %s%> may only be used in compound statements",
		  "omp cancellation point");
      లేకపోతే
	c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
      తిరిగి నిజం;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_బిందువు_CLAUSE_ముసుగు,
				"#pragma omp cancellation point");

  c_ముగింపు_omp_cancellation_బిందువు (loc, clauses);
  తిరిగి నిజం;
}

/* OpenMP 4.0:
   #pragma omp distribute distribute-clause[optseq] new-line
     for-loop  */

#నిర్వచించు OMP_DISTRIBUTE_CLAUSE_ముసుగు				\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_వ్యక్తిగత)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DIST_కాలపట్టిక)\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_క్రమం))

స్థిర వృక్షం
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 అక్షరం *p_name, omp_clause_ముసుగు ముసుగు, వృక్షం *cclauses,
			 తార్కిక *if_p)
{
  వృక్షం clauses, ఖండం, ret;

  strcat (p_name, " distribute");
  ముసుగు |= OMP_DISTRIBUTE_CLAUSE_ముసుగు;

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      తార్కిక simd = అబద్ధం;
      తార్కిక parallel = అబద్ధం;

      ఒకవేళ (strcmp (p, "simd") == 0)
	simd = నిజం;
      లేకపోతే
	parallel = strcmp (p, "parallel") == 0;
      ఒకవేళ (parallel || simd)
	{
	  వృక్షం cclauses_buf[C_OMP_CLAUSE_విభజించు_లెక్క];
	  ఒకవేళ (cclauses == ఖాళీ)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      ఒకవేళ (simd)
		తిరిగి c_parser_omp_simd (loc, parser, p_name, ముసుగు, cclauses,
					  if_p);
	      లేకపోతే
		తిరిగి c_parser_omp_parallel (loc, parser, p_name, ముసుగు,
					      cclauses, if_p);
	    }
	  ఖండం = c_begin_compound_stmt (నిజం);
	  ఒకవేళ (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, ముసుగు, cclauses,
				     if_p);
	  లేకపోతే
	    ret = c_parser_omp_parallel (loc, parser, p_name, ముసుగు, cclauses,
					 if_p);
	  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
	  ఒకవేళ (ret == ఖాళీ)
	    తిరిగి ret;
	  ret = make_కణుపు (OMP_DISTRIBUTE);
	  వృక్షం_TYPE (ret) = void_type_కణుపు;
	  OMP_FOR_BODY (ret) = ఖండం;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_విభజించు_DISTRIBUTE];
	  సమితి_సమాసం_LOCATION (ret, loc);
	  కూడు_stmt (ret);
	  తిరిగి ret;
	}
    }
  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
      తిరిగి NULL_వృక్షం;
    }

  clauses = c_parser_omp_all_clauses (parser, ముసుగు, p_name, cclauses == ఖాళీ);
  ఒకవేళ (cclauses)
    {
      omp_విభజించు_clauses (loc, OMP_DISTRIBUTE, ముసుగు, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_విభజించు_DISTRIBUTE];
    }

  ఖండం = c_begin_compound_stmt (నిజం);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, ఖాళీ,
			       if_p);
  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
  కూడు_stmt (ఖండం);

  తిరిగి ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#నిర్వచించు OMP_TEAMS_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_వ్యక్తిగత)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_అంకె_TEAMS)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_THREAD_హద్దు)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

స్థిర వృక్షం
c_parser_omp_teams (location_t loc, c_parser *parser,
		    అక్షరం *p_name, omp_clause_ముసుగు ముసుగు, వృక్షం *cclauses,
		    తార్కిక *if_p)
{
  వృక్షం clauses, ఖండం, ret;

  strcat (p_name, " teams");
  ముసుగు |= OMP_TEAMS_CLAUSE_ముసుగు;

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp (p, "distribute") == 0)
	{
	  వృక్షం cclauses_buf[C_OMP_CLAUSE_విభజించు_లెక్క];
	  ఒకవేళ (cclauses == ఖాళీ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	    తిరిగి c_parser_omp_distribute (loc, parser, p_name, ముసుగు,
					    cclauses, if_p);
	  ఖండం = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, ముసుగు, cclauses,
					 if_p);
	  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
	  ఒకవేళ (ret == ఖాళీ)
	    తిరిగి ret;
	  clauses = cclauses[C_OMP_CLAUSE_విభజించు_TEAMS];
	  ret = make_కణుపు (OMP_TEAMS);
	  వృక్షం_TYPE (ret) = void_type_కణుపు;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = ఖండం;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  సమితి_సమాసం_LOCATION (ret, loc);
	  తిరిగి కూడు_stmt (ret);
	}
      లేకపోతే ఒకవేళ (strcmp (p, "loop") == 0)
	{
	  వృక్షం cclauses_buf[C_OMP_CLAUSE_విభజించు_లెక్క];
	  ఒకవేళ (cclauses == ఖాళీ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	    తిరిగి c_parser_omp_loop (loc, parser, p_name, ముసుగు, cclauses,
				      if_p);
	  ఖండం = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, ముసుగు, cclauses, if_p);
	  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
	  ఒకవేళ (ret == ఖాళీ)
	    తిరిగి ret;
	  clauses = cclauses[C_OMP_CLAUSE_విభజించు_TEAMS];
	  ret = make_కణుపు (OMP_TEAMS);
	  వృక్షం_TYPE (ret) = void_type_కణుపు;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = ఖండం;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  సమితి_సమాసం_LOCATION (ret, loc);
	  తిరిగి కూడు_stmt (ret);
	}
    }
  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
      తిరిగి NULL_వృక్షం;
    }

  clauses = c_parser_omp_all_clauses (parser, ముసుగు, p_name, cclauses == ఖాళీ);
  ఒకవేళ (cclauses)
    {
      omp_విభజించు_clauses (loc, OMP_TEAMS, ముసుగు, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_విభజించు_TEAMS];
    }

  వృక్షం stmt = make_కణుపు (OMP_TEAMS);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  ఖండం = c_begin_omp_parallel ();
  కూడు_stmt (c_parser_omp_structured_ఖండం (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_చివర_compound_stmt (loc, ఖండం, నిజం);
  సమితి_సమాసం_LOCATION (stmt, loc);

  తిరిగి కూడు_stmt (stmt);
}

/* OpenMP 4.0:
   # pragma omp target data target-data-clause[optseq] new-line
     structured-block  */

#నిర్వచించు OMP_లక్ష్యం_దత్తాంశం_CLAUSE_ముసుగు				\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR) \
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR))

స్థిర వృక్షం
c_parser_omp_లక్ష్యం_దత్తాంశం (location_t loc, c_parser *parser, తార్కిక *if_p)
{
  ఒకవేళ (flag_openmp)
    omp_requires_ముసుగు
      = (గణన omp_requires) (omp_requires_ముసుగు | OMP_REQUIRES_లక్ష్యం_వాడిన);

  వృక్షం clauses
    = c_parser_omp_all_clauses (parser, OMP_లక్ష్యం_దత్తాంశం_CLAUSE_ముసుగు,
				"#pragma omp target data", అబద్ధం);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_ముగింపు_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, అబద్ధం);
  పూర్ణాంకం map_చూసిన = 0;
  కొరకు (వృక్షం *pc = &clauses; *pc;)
    {
      ఒకవేళ (OMP_CLAUSE_సంకేతం (*pc) == OMP_CLAUSE_MAP)
	ఎంపిక (OMP_CLAUSE_MAP_రకం (*pc))
	  {
	  స్థితి GOMP_MAP_గమ్యం:
	  స్థితి GOMP_MAP_ALWAYS_గమ్యం:
	  స్థితి GOMP_MAP_PRESENT_గమ్యం:
	  స్థితి GOMP_MAP_ALWAYS_PRESENT_గమ్యం:
	  స్థితి GOMP_MAP_FROM:
	  స్థితి GOMP_MAP_ALWAYS_FROM:
	  స్థితి GOMP_MAP_PRESENT_FROM:
	  స్థితి GOMP_MAP_ALWAYS_PRESENT_FROM:
	  స్థితి GOMP_MAP_TOFROM:
	  స్థితి GOMP_MAP_ALWAYS_TOFROM:
	  స్థితి GOMP_MAP_PRESENT_TOFROM:
	  స్థితి GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  స్థితి GOMP_MAP_ALLOC:
	  స్థితి GOMP_MAP_PRESENT_ALLOC:
	    map_చూసిన = 3;
	    ఆపు;
	  స్థితి GOMP_MAP_FIRSTPRIVATE_సూచిక:
	  స్థితి GOMP_MAP_ALWAYS_సూచిక:
	  స్థితి GOMP_MAP_ATTACH_DETACH:
	  స్థితి GOMP_MAP_ATTACH:
	    ఆపు;
	  అప్రమేయ:
	    map_చూసిన |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    కొనసాగు;
	  }
      లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_సంకేతం (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_చూసిన = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  ఒకవేళ (map_చూసిన != 3)
    {
      ఒకవేళ (map_చూసిన == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      తిరిగి NULL_వృక్షం;
    }

  వృక్షం stmt = make_కణుపు (OMP_లక్ష్యం_దత్తాంశం);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OMP_లక్ష్యం_దత్తాంశం_CLAUSES (stmt) = clauses;
  keep_తదుపరి_level ();
  వృక్షం ఖండం = c_begin_compound_stmt (నిజం);
  కూడు_stmt (c_parser_omp_structured_ఖండం (parser, if_p));
  OMP_లక్ష్యం_దత్తాంశం_BODY (stmt) = c_చివర_compound_stmt (loc, ఖండం, నిజం);

  సమితి_సమాసం_LOCATION (stmt, loc);
  తిరిగి కూడు_stmt (stmt);
}

/* OpenMP 4.0:
   # pragma omp target update target-update-clause[optseq] new-line */

#నిర్వచించు OMP_లక్ష్యం_UPDATE_CLAUSE_ముసుగు				\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FROM)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_గమ్యం)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

స్థిర తార్కిక
c_parser_omp_లక్ష్యం_update (location_t loc, c_parser *parser,
			    గణన pragma_context context)
{
  ఒకవేళ (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
      తిరిగి నిజం;
    }

  వృక్షం clauses
    = c_parser_omp_all_clauses (parser, OMP_లక్ష్యం_UPDATE_CLAUSE_ముసుగు,
				"#pragma omp target update",
				/* finish_p = */ అబద్ధం);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_ముగింపు_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  ఒకవేళ (omp_కనుగొను_clause (clauses, OMP_CLAUSE_గమ్యం) == NULL_వృక్షం
      && omp_కనుగొను_clause (clauses, OMP_CLAUSE_FROM) == NULL_వృక్షం)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      తిరిగి అబద్ధం;
    }

  ఒకవేళ (flag_openmp)
    omp_requires_ముసుగు
      = (గణన omp_requires) (omp_requires_ముసుగు | OMP_REQUIRES_లక్ష్యం_వాడిన);

  వృక్షం stmt = make_కణుపు (OMP_లక్ష్యం_UPDATE);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OMP_లక్ష్యం_UPDATE_CLAUSES (stmt) = clauses;
  సమితి_సమాసం_LOCATION (stmt, loc);
  కూడు_stmt (stmt);
  తిరిగి అబద్ధం;
}

/* OpenMP 4.5:
   # pragma omp target enter data target-data-clause[optseq] new-line  */

#నిర్వచించు OMP_లక్ష్యం_ENTER_దత్తాంశం_CLAUSE_ముసుగు			\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

స్థిర తార్కిక
c_parser_omp_లక్ష్యం_enter_దత్తాంశం (location_t loc, c_parser *parser,
				గణన pragma_context context)
{
  తార్కిక దత్తాంశం_చూసిన = అబద్ధం;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  దత్తాంశం_చూసిన = నిజం;
	}
    }
  ఒకవేళ (!దత్తాంశం_చూసిన)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_గమ్యం_pragma_eol (parser);
      తిరిగి అబద్ధం;
    }

  ఒకవేళ (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
      తిరిగి నిజం;
    }

  ఒకవేళ (flag_openmp)
    omp_requires_ముసుగు
      = (గణన omp_requires) (omp_requires_ముసుగు | OMP_REQUIRES_లక్ష్యం_వాడిన);

  వృక్షం clauses
    = c_parser_omp_all_clauses (parser, OMP_లక్ష్యం_ENTER_దత్తాంశం_CLAUSE_ముసుగు,
				"#pragma omp target enter data", అబద్ధం);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_ముగింపు_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, అబద్ధం);
  పూర్ణాంకం map_చూసిన = 0;
  కొరకు (వృక్షం *pc = &clauses; *pc;)
    {
      ఒకవేళ (OMP_CLAUSE_సంకేతం (*pc) == OMP_CLAUSE_MAP)
	ఎంపిక (OMP_CLAUSE_MAP_రకం (*pc))
	  {
	  స్థితి GOMP_MAP_గమ్యం:
	  స్థితి GOMP_MAP_ALWAYS_గమ్యం:
	  స్థితి GOMP_MAP_PRESENT_గమ్యం:
	  స్థితి GOMP_MAP_ALWAYS_PRESENT_గమ్యం:
	  స్థితి GOMP_MAP_ALLOC:
	  స్థితి GOMP_MAP_PRESENT_ALLOC:
	    map_చూసిన = 3;
	    ఆపు;
	  స్థితి GOMP_MAP_TOFROM:
	    OMP_CLAUSE_సమితి_MAP_రకం (*pc, GOMP_MAP_గమ్యం);
	    map_చూసిన = 3;
	    ఆపు;
	  స్థితి GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_సమితి_MAP_రకం (*pc, GOMP_MAP_ALWAYS_గమ్యం);
	    map_చూసిన = 3;
	    ఆపు;
	  స్థితి GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_సమితి_MAP_రకం (*pc, GOMP_MAP_PRESENT_గమ్యం);
	    map_చూసిన = 3;
	    ఆపు;
	  స్థితి GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_సమితి_MAP_రకం (*pc, GOMP_MAP_ALWAYS_PRESENT_గమ్యం);
	    map_చూసిన = 3;
	    ఆపు;
	  స్థితి GOMP_MAP_FIRSTPRIVATE_సూచిక:
	  స్థితి GOMP_MAP_ALWAYS_సూచిక:
	  స్థితి GOMP_MAP_ATTACH_DETACH:
	  స్థితి GOMP_MAP_ATTACH:
	    ఆపు;
	  అప్రమేయ:
	    map_చూసిన |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    కొనసాగు;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  ఒకవేళ (map_చూసిన != 3)
    {
      ఒకవేళ (map_చూసిన == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      తిరిగి నిజం;
    }

  వృక్షం stmt = make_కణుపు (OMP_లక్ష్యం_ENTER_దత్తాంశం);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OMP_లక్ష్యం_ENTER_దత్తాంశం_CLAUSES (stmt) = clauses;
  సమితి_సమాసం_LOCATION (stmt, loc);
  కూడు_stmt (stmt);
  తిరిగి నిజం;
}

/* OpenMP 4.5:
   # pragma omp target exit data target-data-clause[optseq] new-line  */

#నిర్వచించు OMP_లక్ష్యం_EXIT_దత్తాంశం_CLAUSE_ముసుగు			\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

స్థిర తార్కిక
c_parser_omp_లక్ష్యం_exit_దత్తాంశం (location_t loc, c_parser *parser,
			       గణన pragma_context context)
{
  తార్కిక దత్తాంశం_చూసిన = అబద్ధం;
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  దత్తాంశం_చూసిన = నిజం;
	}
    }
  ఒకవేళ (!దత్తాంశం_చూసిన)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_గమ్యం_pragma_eol (parser);
      తిరిగి అబద్ధం;
    }

  ఒకవేళ (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
      తిరిగి నిజం;
    }

  ఒకవేళ (flag_openmp)
    omp_requires_ముసుగు
      = (గణన omp_requires) (omp_requires_ముసుగు | OMP_REQUIRES_లక్ష్యం_వాడిన);

  వృక్షం clauses
    = c_parser_omp_all_clauses (parser, OMP_లక్ష్యం_EXIT_దత్తాంశం_CLAUSE_ముసుగు,
				"#pragma omp target exit data", అబద్ధం);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_దత్తాంశం);
  clauses = c_ముగింపు_omp_clauses (clauses, C_ORT_OMP_EXIT_దత్తాంశం);
  c_omp_adjust_map_clauses (clauses, అబద్ధం);
  పూర్ణాంకం map_చూసిన = 0;
  కొరకు (వృక్షం *pc = &clauses; *pc;)
    {
      ఒకవేళ (OMP_CLAUSE_సంకేతం (*pc) == OMP_CLAUSE_MAP)
	ఎంపిక (OMP_CLAUSE_MAP_రకం (*pc))
	  {
	  స్థితి GOMP_MAP_FROM:
	  స్థితి GOMP_MAP_ALWAYS_FROM:
	  స్థితి GOMP_MAP_PRESENT_FROM:
	  స్థితి GOMP_MAP_ALWAYS_PRESENT_FROM:
	  స్థితి GOMP_MAP_RELEASE:
	  స్థితి GOMP_MAP_DELETE:
	    map_చూసిన = 3;
	    ఆపు;
	  స్థితి GOMP_MAP_TOFROM:
	    OMP_CLAUSE_సమితి_MAP_రకం (*pc, GOMP_MAP_FROM);
	    map_చూసిన = 3;
	    ఆపు;
	  స్థితి GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_సమితి_MAP_రకం (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_చూసిన = 3;
	    ఆపు;
	  స్థితి GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_సమితి_MAP_రకం (*pc, GOMP_MAP_PRESENT_FROM);
	    map_చూసిన = 3;
	    ఆపు;
	  స్థితి GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_సమితి_MAP_రకం (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_చూసిన = 3;
	    ఆపు;
	  స్థితి GOMP_MAP_FIRSTPRIVATE_సూచిక:
	  స్థితి GOMP_MAP_ALWAYS_సూచిక:
	  స్థితి GOMP_MAP_ATTACH_DETACH:
	  స్థితి GOMP_MAP_DETACH:
	    ఆపు;
	  అప్రమేయ:
	    map_చూసిన |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target exit data%> with map-type other "
		      "than %<from%>, %<tofrom%>, %<release%> or %<delete%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    కొనసాగు;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  ఒకవేళ (map_చూసిన != 3)
    {
      ఒకవేళ (map_చూసిన == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      తిరిగి నిజం;
    }

  వృక్షం stmt = make_కణుపు (OMP_లక్ష్యం_EXIT_దత్తాంశం);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;
  OMP_లక్ష్యం_EXIT_దత్తాంశం_CLAUSES (stmt) = clauses;
  సమితి_సమాసం_LOCATION (stmt, loc);
  కూడు_stmt (stmt);
  తిరిగి నిజం;
}

/* OpenMP 4.0:
   # pragma omp target target-clause[optseq] new-line
     structured-block  */

#నిర్వచించు OMP_లక్ష్యం_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEFAULTMAP)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE) \
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR) \
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_లోపల_REDUCTION)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR)\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_వ్యక్తిగత)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_THREAD_హద్దు)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ఉపయోగిస్తుంది_ALLOCATORS))

స్థిర తార్కిక
c_parser_omp_లక్ష్యం (c_parser *parser, గణన pragma_context context, తార్కిక *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  వృక్షం *pc = ఖాళీ, stmt, ఖండం, body, clauses;

  ఒకవేళ (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_గమ్యం_pragma_eol (parser);
      తిరిగి అబద్ధం;
    }

  ఒకవేళ (flag_openmp)
    omp_requires_ముసుగు
      = (గణన omp_requires) (omp_requires_ముసుగు | OMP_REQUIRES_లక్ష్యం_వాడిన);

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      గణన వృక్షం_సంకేతం_2 ccode = ERROR_MARK;

      ఒకవేళ (strcmp (p, "teams") == 0)
	ccode = OMP_TEAMS;
      లేకపోతే ఒకవేళ (strcmp (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      లేకపోతే ఒకవేళ (strcmp (p, "simd") == 0)
	ccode = OMP_SIMD;
      ఒకవేళ (ccode != ERROR_MARK)
	{
	  వృక్షం cclauses[C_OMP_CLAUSE_విభజించు_లెక్క];
	  అక్షరం p_name[పరిమాణం ("#pragma omp target teams distribute "
			      "parallel for simd")];

	  c_parser_consume_token (parser);
	  strcpy (p_name, "#pragma omp target");
	  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      వృక్షం stmt;
	      ఎంపిక (ccode)
		{
		స్థితి OMP_TEAMS:
		  stmt = c_parser_omp_teams (loc, parser, p_name,
					     OMP_లక్ష్యం_CLAUSE_ముసుగు,
					     cclauses, if_p);
		  ఆపు;
		స్థితి OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_లక్ష్యం_CLAUSE_ముసుగు,
						cclauses, if_p);
		  ఆపు;
		స్థితి OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_లక్ష్యం_CLAUSE_ముసుగు,
					    cclauses, if_p);
		  ఆపు;
		అప్రమేయ:
		  gcc_unreachable ();
		}
	      తిరిగి stmt != NULL_వృక్షం;
	    }
	  keep_తదుపరి_level ();
	  వృక్షం ఖండం = c_begin_compound_stmt (నిజం), ret;
	  ఎంపిక (ccode)
	    {
	    స్థితి OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_లక్ష్యం_CLAUSE_ముసుగు, cclauses,
					if_p);
	      ఆపు;
	    స్థితి OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_లక్ష్యం_CLAUSE_ముసుగు, cclauses,
					   if_p);
	      ఆపు;
	    స్థితి OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_లక్ష్యం_CLAUSE_ముసుగు, cclauses,
				       if_p);
	      ఆపు;
	    అప్రమేయ:
	      gcc_unreachable ();
	    }
	  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
	  ఒకవేళ (ret == NULL_వృక్షం)
	    తిరిగి అబద్ధం;
	  ఒకవేళ (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    కొరకు (వృక్షం c = cclauses[C_OMP_CLAUSE_విభజించు_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_అంకె_TEAMS
		  || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_THREAD_హద్దు)
		కొరకు (పూర్ణాంకం i = 0;
		     i <= (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_అంకె_TEAMS); ++i)
		  ఒకవేళ (OMP_CLAUSE_నిర్వాహ్యం (c, i)
		      && వృక్షం_సంకేతం (OMP_CLAUSE_నిర్వాహ్యం (c, i)) != INTEGER_CST)
		    {
		      వృక్షం సమాసం = OMP_CLAUSE_నిర్వాహ్యం (c, i);
		      వృక్షం tmp = create_tmp_var_raw (వృక్షం_TYPE (సమాసం));
		      సమాసం = build4 (లక్ష్యం_సమాసం, వృక్షం_TYPE (సమాసం), tmp,
				     సమాసం, NULL_వృక్షం, NULL_వృక్షం);
		      కూడు_stmt (సమాసం);
		      OMP_CLAUSE_నిర్వాహ్యం (c, i) = సమాసం;
		      వృక్షం tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_విభజించు_లక్ష్యం];
		      cclauses[C_OMP_CLAUSE_విభజించు_లక్ష్యం] = tc;
		    }
	  వృక్షం stmt = make_కణుపు (OMP_లక్ష్యం);
	  వృక్షం_TYPE (stmt) = void_type_కణుపు;
	  OMP_లక్ష్యం_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_విభజించు_లక్ష్యం];
	  c_omp_adjust_map_clauses (OMP_లక్ష్యం_CLAUSES (stmt), నిజం);
	  OMP_లక్ష్యం_BODY (stmt) = ఖండం;
	  OMP_లక్ష్యం_COMBINED (stmt) = 1;
	  సమితి_సమాసం_LOCATION (stmt, loc);
	  కూడు_stmt (stmt);
	  pc = &OMP_లక్ష్యం_CLAUSES (stmt);
	  వెళ్ళు check_clauses;
	}
      లేకపోతే ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	  తిరిగి అబద్ధం;
	}
      లేకపోతే ఒకవేళ (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_లక్ష్యం_దత్తాంశం (loc, parser, if_p);
	  తిరిగి నిజం;
	}
      లేకపోతే ఒకవేళ (strcmp (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  తిరిగి c_parser_omp_లక్ష్యం_enter_దత్తాంశం (loc, parser, context);
	}
      లేకపోతే ఒకవేళ (strcmp (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  తిరిగి c_parser_omp_లక్ష్యం_exit_దత్తాంశం (loc, parser, context);
	}
      లేకపోతే ఒకవేళ (strcmp (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  తిరిగి c_parser_omp_లక్ష్యం_update (loc, parser, context);
	}
    }
  ఒకవేళ (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
      తిరిగి అబద్ధం;
    }

  stmt = make_కణుపు (OMP_లక్ష్యం);
  వృక్షం_TYPE (stmt) = void_type_కణుపు;

  clauses = c_parser_omp_all_clauses (parser, OMP_లక్ష్యం_CLAUSE_ముసుగు,
				      "#pragma omp target", అబద్ధం);
  కొరకు (వృక్షం c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_లోపల_REDUCTION)
      {
	వృక్షం nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_సమితి_MAP_రకం (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_లక్ష్యం);
  clauses  = c_ముగింపు_omp_clauses (clauses, C_ORT_OMP_లక్ష్యం);
  c_omp_adjust_map_clauses (clauses, నిజం);

  keep_తదుపరి_level ();
  ఖండం = c_begin_compound_stmt (నిజం);
  body = c_parser_omp_structured_ఖండం (parser, if_p);

  c_omp_పరిశీలన_mapper_bindings (loc, &clauses, body);

  కూడు_stmt (body);
  OMP_లక్ష్యం_CLAUSES (stmt) = clauses;
  pc = &OMP_లక్ష్యం_CLAUSES (stmt);
  OMP_లక్ష్యం_BODY (stmt) = c_చివర_compound_stmt (loc, ఖండం, నిజం);

  సమితి_సమాసం_LOCATION (stmt, loc);
  కూడు_stmt (stmt);

check_clauses:
  అయితే (*pc)
    {
      ఒకవేళ (OMP_CLAUSE_సంకేతం (*pc) == OMP_CLAUSE_MAP)
	ఎంపిక (OMP_CLAUSE_MAP_రకం (*pc))
	  {
	  స్థితి GOMP_MAP_గమ్యం:
	  స్థితి GOMP_MAP_ALWAYS_గమ్యం:
	  స్థితి GOMP_MAP_PRESENT_గమ్యం:
	  స్థితి GOMP_MAP_ALWAYS_PRESENT_గమ్యం:
	  స్థితి GOMP_MAP_FROM:
	  స్థితి GOMP_MAP_ALWAYS_FROM:
	  స్థితి GOMP_MAP_PRESENT_FROM:
	  స్థితి GOMP_MAP_ALWAYS_PRESENT_FROM:
	  స్థితి GOMP_MAP_TOFROM:
	  స్థితి GOMP_MAP_ALWAYS_TOFROM:
	  స్థితి GOMP_MAP_PRESENT_TOFROM:
	  స్థితి GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  స్థితి GOMP_MAP_ALLOC:
	  స్థితి GOMP_MAP_PRESENT_ALLOC:
	  స్థితి GOMP_MAP_FIRSTPRIVATE_సూచిక:
	  స్థితి GOMP_MAP_ALWAYS_సూచిక:
	  స్థితి GOMP_MAP_సూచిక:
	  స్థితి GOMP_MAP_ATTACH_DETACH:
	  స్థితి GOMP_MAP_ATTACH:
	    ఆపు;
	  అప్రమేయ:
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    కొనసాగు;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }
  cfun->has_omp_లక్ష్యం = నిజం;
  తిరిగి నిజం;
}

/* OpenMP 4.0:
   # pragma omp declare simd declare-simd-clauses[optseq] new-line

   OpenMP 5.0:
   # pragma omp declare variant (identifier) match(context-selector) new-line

   OpenMP 5.1
   # pragma omp declare variant (identifier) match(context-selector) \
      adjust_args(adjust-op:argument-list) append_args(interop-list) new-line
   */

#నిర్వచించు OMP_DECLARE_SIMD_CLAUSE_ముసుగు				\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_SIMDLEN)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_రేఖీయ)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ALIGNED)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ఏకరీతి)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_INBRANCH)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOTINBRANCH))

స్థిర శూన్య
c_parser_omp_declare_simd (c_parser *parser, గణన pragma_context context)
{
  c_token *token = c_parser_peek_token (parser);
  gcc_assert (token->type == CPP_NAME);
  వృక్షం రకం = token->విలువ;
  gcc_assert (strcmp (IDENTIFIER_సూచిక (రకం), "simd") == 0
	      || strcmp (IDENTIFIER_సూచిక (రకం), "variant") == 0);

  auto_vec<c_token> clauses;
  అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      ఒకవేళ (token->type == CPP_EOF)
	{
	  c_parser_skip_గమ్యం_pragma_eol (parser);
	  తిరిగి;
	}
      clauses.సురక్షిత_నెట్టు (*token);
      c_parser_consume_token (parser);
    }
  clauses.సురక్షిత_నెట్టు (*c_parser_peek_token (parser));
  c_parser_skip_గమ్యం_pragma_eol (parser);

  అయితే (c_parser_తదుపరి_token_is (parser, CPP_PRAGMA))
    {
      ఒకవేళ (c_parser_peek_token (parser)->pragma_రకం != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->విలువ != రకం)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_సూచిక (రకం), IDENTIFIER_సూచిక (రకం));
	  తిరిగి;
	}
      c_parser_consume_pragma (parser);
      అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  ఒకవేళ (token->type == CPP_EOF)
	    {
	      c_parser_skip_గమ్యం_pragma_eol (parser);
	      తిరిగి;
	    }
	  clauses.సురక్షిత_నెట్టు (*token);
	  c_parser_consume_token (parser);
	}
      clauses.సురక్షిత_నెట్టు (*c_parser_peek_token (parser));
      c_parser_skip_గమ్యం_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  memset (&eof_token, 0, పరిమాణం (eof_token));
  eof_token.type = CPP_EOF;
  clauses.సురక్షిత_నెట్టు (eof_token);
  clauses.సురక్షిత_నెట్టు (eof_token);

  ఎంపిక (context)
    {
    స్థితి pragma_external:
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  పూర్ణాంకం ext = disable_extension_diagnostics ();
	  చేయి
	    c_parser_consume_token (parser);
	  అయితే (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, నిజం, నిజం, నిజం, అబద్ధం, నిజం,
					 అబద్ధం, ఖాళీ, &clauses);
	  restore_extension_diagnostics (ext);
	}
      లేకపోతే
	c_parser_declaration_or_fndef (parser, నిజం, నిజం, నిజం, అబద్ధం, నిజం,
				       అబద్ధం, ఖాళీ, &clauses);
      ఆపు;
    స్థితి pragma_struct:
    స్థితి pragma_param:
    స్థితి pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_సూచిక (రకం));
      ఆపు;
    స్థితి pragma_compound:
      తార్కిక have_std_attrs;
      వృక్షం std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_లక్షణాలు (parser, 1);
      ఒకవేళ (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      లేకపోతే
	std_attrs = NULL_వృక్షం;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  పూర్ణాంకం ext = disable_extension_diagnostics ();
	  చేయి
	    c_parser_consume_token (parser);
	  అయితే (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_declaration (parser)
	      || c_parser_nth_token_starts_std_లక్షణాలు (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, నిజం, నిజం, నిజం, నిజం,
					     నిజం, అబద్ధం, ఖాళీ, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      ఆపు;
	    }
	  restore_extension_diagnostics (ext);
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, నిజం, నిజం, నిజం, నిజం, నిజం,
					 అబద్ధం, ఖాళీ, &clauses, have_std_attrs,
					 std_attrs);
	  ఆపు;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_సూచిక (రకం));
      ఆపు;
    అప్రమేయ:
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

స్థిర వృక్షం
c_parser_omp_context_selector (c_parser *parser, గణన omp_tss_సంకేతం సమితి,
			       వృక్షం parms)
{
  వృక్షం ret = NULL_వృక్షం;
  చేయి
    {
      వృక్షం selector;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD)
	  || c_parser_తదుపరి_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->విలువ;
      లేకపోతే
	{
	  c_parser_error (parser, "expected trait selector name");
	  తిరిగి error_mark_కణుపు;
	}
      గణన omp_ts_సంకేతం sel
	= omp_lookup_ts_సంకేతం (సమితి, IDENTIFIER_సూచిక (selector));

      ఒకవేళ (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_సూచిక (selector),  omp_tss_map[సమితి]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_వృక్షం, NULL_వృక్షం, ret);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_సమతుల్య_token_sequence (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      కొనసాగు;
	    }
	  లేకపోతే
	    ఆపు;
	}

      c_parser_consume_token (parser);

      వృక్షం properties = NULL_వృక్షం;
      వృక్షం scoreval = NULL_వృక్షం;
      గణన omp_tp_type property_రకం = omp_ts_map[sel].tp_type;
      తార్కిక allow_score = omp_ts_map[sel].allow_score;
      వృక్షం t;

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
	{
	  ఒకవేళ (property_రకం == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_సూచిక (selector));
	      తిరిగి error_mark_కణుపు;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_సూచిక (token->విలువ), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      వృక్షం score = c_parser_సమాసం_no_commas (parser, ఖాళీ).విలువ;
	      parens2.skip_until_దొరికింది_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      ఒకవేళ (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[సమితి]);
	      లేకపోతే ఒకవేళ (score != error_mark_కణుపు)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, అబద్ధం, ఖాళీ);
		  ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (score))
		      || వృక్షం_సంకేతం (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  లేకపోతే ఒకవేళ (వృక్షం_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  లేకపోతే
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  ఎంపిక (property_రకం)
	    {
	    స్థితి OMP_TRAIT_PROPERTY_ID:
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD)
		  || c_parser_తదుపరి_token_is (parser, CPP_NAME))
		{
		  వృక్షం prop = c_parser_peek_token (parser)->విలువ;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_వృక్షం,
						    properties);
		}
	      లేకపోతే
		{
		  c_parser_error (parser, "expected identifier");
		  తిరిగి error_mark_కణుపు;
		}
	      ఆపు;
	    స్థితి OMP_TRAIT_PROPERTY_NAME_LIST:
	      చేయి
		{
		  వృక్షం prop = OMP_TP_NAMELIST_కణుపు;
		  వృక్షం విలువ = NULL_వృక్షం;
		  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD)
		      || c_parser_తదుపరి_token_is (parser, CPP_NAME))
		    {
		      విలువ = c_parser_peek_token (parser)->విలువ;
		      c_parser_consume_token (parser);
		    }
		  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_STRING))
		    విలువ = c_parser_string_literal (parser, అబద్ధం,
						     అబద్ధం).విలువ;
		  లేకపోతే
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      తిరిగి error_mark_కణుపు;
		    }

		  properties = make_trait_property (prop, విలువ, properties);

		  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  లేకపోతే
		    ఆపు;
		}
	      అయితే (1);
	      ఆపు;
	    స్థితి OMP_TRAIT_PROPERTY_DEV_అంకె_సమాసం:
	    స్థితి OMP_TRAIT_PROPERTY_BOOL_సమాసం:
	      {
		c_సమాసం texpr = c_parser_సమాసం_no_commas (parser, ఖాళీ);
		texpr = convert_lvalue_గమ్యం_rvalue (token->location, texpr,
						  నిజం, నిజం);
		t = texpr.విలువ;
	      }
	      ఒకవేళ (t == error_mark_కణుపు)
		తిరిగి error_mark_కణుపు;
	      mark_exp_read (t);
	      ఒకవేళ (property_రకం == OMP_TRAIT_PROPERTY_BOOL_సమాసం)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_కణుపు);
		  ఒకవేళ (t == error_mark_కణుపు)
		    తిరిగి error_mark_కణుపు;
		}
	      లేకపోతే ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  తిరిగి error_mark_కణుపు;
		}
	      t = c_fully_fold (t, అబద్ధం, ఖాళీ);
	      properties = make_trait_property (NULL_వృక్షం, t, properties);
	      ఆపు;
	    స్థితి OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      ఒకవేళ (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  ఒకవేళ (parms == NULL_వృక్షం)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      తిరిగి error_mark_కణుపు;
		    }
		  వృక్షం c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_ముసుగు,
						"simd", నిజం, 2);
		  c = c_omp_declare_simd_clauses_గమ్యం_numbers (parms
							     == error_mark_కణుపు
							     ? NULL_వృక్షం : parms,
							     c);
		  properties = c;
		}
	      లేకపోతే ఒకవేళ (sel == OMP_TRAIT_IMPLEMENTATION_REQUIRES)
		{
		  /* FIXME: The "requires" selector was added in OpenMP 5.1.
		     Currently only the now-deprecated syntax
		     from OpenMP 5.0 is supported.  */
		  sorry_at (token->location,
			    "%<requires%> selector is not supported yet");
		  తిరిగి error_mark_కణుపు;
		}
	      లేకపోతే
		gcc_unreachable ();
	      ఆపు;
	    అప్రమేయ:
	      gcc_unreachable ();
	    }

	  parens.skip_until_దొరికింది_close (parser);
	  properties = nreverse (properties);
	}
      లేకపోతే ఒకవేళ (property_రకం != OMP_TRAIT_PROPERTY_NONE
	       && property_రకం != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_రకం != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  తిరిగి error_mark_కణుపు;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      లేకపోతే
	ఆపు;
    }
  అయితే (1);

  తిరిగి nreverse (ret);
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

స్థిర వృక్షం
c_parser_omp_context_selector_specification (c_parser *parser, వృక్షం parms)
{
  వృక్షం ret = NULL_వృక్షం;
  చేయి
    {
      స్థిరరాశి అక్షరం *setp = "";
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      గణన omp_tss_సంకేతం సమితి = omp_lookup_tss_సంకేతం (setp);

      ఒకవేళ (సమితి == OMP_TRAIT_సమితి_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  తిరిగి error_mark_కణుపు;
	}

      c_parser_consume_token (parser);

      ఒకవేళ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	తిరిగి error_mark_కణుపు;

      matching_braces braces;
      ఒకవేళ (!braces.require_open (parser))
	తిరిగి error_mark_కణుపు;

      వృక్షం selectors = c_parser_omp_context_selector (parser, సమితి, parms);
      ఒకవేళ (selectors == error_mark_కణుపు)
	{
	  c_parser_skip_గమ్యం_closing_brace (parser);
	  ret = error_mark_కణుపు;
	}
      లేకపోతే ఒకవేళ (ret != error_mark_కణుపు)
	ret = make_trait_సమితి_selector (సమితి, selectors, ret);

      braces.require_close (parser);

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      లేకపోతే
	ఆపు;
    }
  అయితే (1);

  ఒకవేళ (ret == error_mark_కణుపు)
    తిరిగి ret;
  తిరిగి nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

స్థిర శూన్య
c_ముగింపు_omp_declare_variant (c_parser *parser, వృక్షం fndecl, వృక్షం parms)
{
  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    {
     fail:
      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
      తిరిగి;
    }

  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_రకం != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      వెళ్ళు fail;
    }

  c_token *token = c_parser_peek_token (parser);
  వృక్షం variant = lookup_name (token->విలువ);

  ఒకవేళ (variant == NULL_వృక్షం)
    {
      undeclared_variable (token->location, token->విలువ);
      variant = error_mark_కణుపు;
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_కణుపు;
    }
  లేకపోతే ఒకవేళ (fndecl_built_లోపల_p (variant)
	   && (అక్షరశ్రేణి_పోలిక (IDENTIFIER_సూచిక (DECL_NAME (variant)),
			"__builtin_", అక్షరశ్రేణి_పొడవు ("__builtin_")) == 0
	       || అక్షరశ్రేణి_పోలిక (IDENTIFIER_సూచిక (DECL_NAME (variant)),
			   "__sync_", అక్షరశ్రేణి_పొడవు ("__sync_")) == 0
	       || అక్షరశ్రేణి_పోలిక (IDENTIFIER_సూచిక (DECL_NAME (variant)),
			   "__atomic_", అక్షరశ్రేణి_పొడవు ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_కణుపు;
    }
  లేకపోతే ఒకవేళ (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_కణుపు;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  వృక్షం append_వాదనలు_వృక్షం = NULL_వృక్షం;
  వృక్షం append_వాదనలు_చివరి;
  vec<వృక్షం> adjust_వాదనలు_list = vNULL;
  తార్కిక has_సరిపోలిక = అబద్ధం, has_adjust_వాదనలు = అబద్ధం;
  location_t adjust_వాదనలు_loc = UNKNOWN_LOCATION;
  location_t append_వాదనలు_loc = UNKNOWN_LOCATION;
  location_t సరిపోలిక_loc = UNKNOWN_LOCATION;
  వృక్షం need_device_ptr_list = NULL_వృక్షం;
  వృక్షం ctx = error_mark_కణుపు;

  చేయి
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      స్థిరరాశి అక్షరం *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);

      గణన clause
      {
	సరిపోలిక,
	adjust_వాదనలు,
	append_వాదనలు
      } ccode;

      ఒకవేళ (strcmp (clause, "match") == 0)
	{
	  ccode = సరిపోలిక;
	  సరిపోలిక_loc = loc;
	}
      లేకపోతే ఒకవేళ (strcmp (clause, "adjust_args") == 0)
	{
	  ccode = adjust_వాదనలు;
	  adjust_వాదనలు_loc = loc;
	}
      లేకపోతే ఒకవేళ (strcmp (clause, "append_args") == 0)
	{
	  ccode = append_వాదనలు;
	  append_వాదనలు_loc = loc;
	}
      లేకపోతే
	{
	  c_parser_error (parser, "expected %<match%>, %<adjust_args%> or "
				  "%<append_args%> clause");
	  వెళ్ళు fail;
	}

      c_parser_consume_token (parser);

      ఒకవేళ (!parens.require_open (parser))
	వెళ్ళు fail;

      ఒకవేళ (parms == NULL_వృక్షం)
	parms = error_mark_కణుపు;

      ఒకవేళ (ccode == సరిపోలిక)
	{
	  ఒకవేళ (has_సరిపోలిక)
	    error_at (సరిపోలిక_loc, "too many %<match%> clauses");
	  has_సరిపోలిక = నిజం;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  ఒకవేళ (ctx == error_mark_కణుపు)
	    వెళ్ళు fail;
	  ctx = omp_check_context_selector (సరిపోలిక_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  ఒకవేళ (ctx != error_mark_కణుపు
	      && !vec_సురక్షిత_is_ఖాళీలు (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->చివరి ();
	      వృక్షం outer_ctx = a.selector;
	      ctx = omp_విలీనం_context_selectors (సరిపోలిక_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      లేకపోతే ఒకవేళ (ccode == adjust_వాదనలు)
	{
	  has_adjust_వాదనలు = నిజం;
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      స్థిరరాశి అక్షరం *p
		= IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
	      ఒకవేళ (strcmp (p, "need_device_ptr") == 0
		  || strcmp (p, "nothing") == 0)
		{
		  c_parser_consume_token (parser); // need_device_ptr
		  c_parser_consume_token (parser); // :

		  loc = c_parser_peek_token (parser)->location;
		  వృక్షం list
		    = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ERROR,
						  NULL_వృక్షం);

		  వృక్షం arg;
		  ఒకవేళ (variant != error_mark_కణుపు)
		    కొరకు (వృక్షం c = list; c != NULL_వృక్షం; c = వృక్షం_CHAIN (c))
		      {
			వృక్షం decl = వృక్షం_PURPOSE (c);
			location_t arg_loc = సమాసం_LOCATION (వృక్షం_విలువ (c));
			పూర్ణాంకం idx;
			కొరకు (arg = parms, idx = 0; arg != ఖాళీ;
			     arg = వృక్షం_CHAIN (arg), idx++)
			  ఒకవేళ (arg == decl)
			    ఆపు;
			ఒకవేళ (arg == NULL_వృక్షం)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    వెళ్ళు fail;
			  }
			ఒకవేళ (adjust_వాదనలు_list.కలిగియుంది (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    వెళ్ళు fail;
			  }
			ఒకవేళ (strcmp (p, "need_device_ptr") == 0
			    && వృక్షం_సంకేతం (వృక్షం_TYPE (arg)) != సూచిక_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    వెళ్ళు fail;
			  }
			adjust_వాదనలు_list.సురక్షిత_నెట్టు (arg);
			ఒకవేళ (strcmp (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_వృక్షం_list (
				NULL_వృక్షం,
				build_int_cst (
				  integer_type_కణుపు,
				  idx))); // Store 0-based argument index,
					  // as in gimplify_call_expr
			  }
		      }
		}
	      లేకపోతే
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %<nothing%> or %<need_device_ptr%>");
		  ఒకవేళ (strcmp (p, "need_device_addr") == 0)
		    inform (c_parser_peek_token (parser)->location,
			    "%<need_device_addr%> is not valid for C");
		  వెళ్ళు fail;
		}
	    }
	  లేకపోతే
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected %<nothing%> or %<need_device_ptr%> "
			"followed by %<:%>");
	      వెళ్ళు fail;
	    }
	}
      లేకపోతే ఒకవేళ (ccode == append_వాదనలు)
	{
	  ఒకవేళ (append_వాదనలు_వృక్షం)
	    {
	      error_at (append_వాదనలు_loc, "too many %qs clauses", "append_args");
	      append_వాదనలు_వృక్షం = NULL_వృక్షం;
	    }
	  చేయి
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME)
		  || strcmp ("interop",
			     IDENTIFIER_సూచిక (
			       c_parser_peek_token (parser)->విలువ)))
		{
		  error_at (loc, "expected %<interop%>");
		  వెళ్ళు fail;
		}
	      c_parser_consume_token (parser);

	      ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		వెళ్ళు fail;
	      తార్కిక లక్ష్యం = అబద్ధం;
	      తార్కిక targetsync = అబద్ధం;
	      వృక్షం prefer_type_వృక్షం = NULL_వృక్షం;
	      ఒకవేళ (!c_parser_omp_clause_init_modifiers (parser, &లక్ష్యం,
						       &targetsync,
						       &prefer_type_వృక్షం)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		వెళ్ళు fail;
	      ఒకవేళ (!లక్ష్యం && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      వృక్షం t = build_వృక్షం_list (లక్ష్యం ? boolean_true_కణుపు
					       : boolean_false_కణుపు,
					targetsync ? boolean_true_కణుపు
						   : boolean_false_కణుపు);
	      t = build1_loc (loc, NOP_సమాసం, void_type_కణుపు, t);
	      t = build_వృక్షం_list (t, prefer_type_వృక్షం);
	      ఒకవేళ (append_వాదనలు_వృక్షం)
		{
		  వృక్షం_CHAIN (append_వాదనలు_చివరి) = t;
		  append_వాదనలు_చివరి = t;
		}
	      లేకపోతే
		append_వాదనలు_వృక్షం = append_వాదనలు_చివరి = t;
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
		ఆపు;
	      ఒకవేళ (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		వెళ్ళు fail;
	    }
	  అయితే (నిజం);
	}

      parens.require_close (parser);
  } అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_PRAGMA_EOL));
  ఒకవేళ (variant != error_mark_కణుపు && !has_సరిపోలిక)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_కణుపు;
    }
  c_parser_skip_గమ్యం_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  ఒకవేళ (variant == error_mark_కణుపు || ctx == error_mark_కణుపు)
    /* Previously diagnosed error.  */
    తిరిగి;

  ఒకవేళ ((has_adjust_వాదనలు || append_వాదనలు_వృక్షం)
      && !omp_get_context_selector (ctx, OMP_TRAIT_సమితి_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_వాదనలు ? adjust_వాదనలు_loc : append_వాదనలు_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_వాదనలు ? "adjust_args" : "append_args");
      తిరిగి;
    }

  ఒకవేళ (!omp_get_context_selector (ctx, OMP_TRAIT_సమితి_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      వృక్షం పునాది_type = వృక్షం_TYPE (fndecl);
      వృక్షం variant_type = వృక్షం_TYPE (variant);
      తార్కిక unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_వృక్షం
	   && !TYPE_NO_NAMED_వాదనలు_STDARG_P (variant_type));

      ఒకవేళ (append_వాదనలు_వృక్షం
	  && TYPE_ARG_TYPES (పునాది_type) == NULL_వృక్షం
	  && !TYPE_NO_NAMED_వాదనలు_STDARG_P (పునాది_type))
	{
	  /* The base function is a pre-C23 unprototyped function.  Without
	     a prototype, we don't know the offset where the append_args go.
	     That offset needs to be stored with the append_args in the
	     variant function attributes, so we cannot presently handle
	     this case.  */
	  sorry_at (append_వాదనలు_loc,
		    "%<append_args%> with unprototyped base function "
		    "is not supported yet");
	  inform (DECL_ఆధారం_LOCATION (fndecl),
		  "base function %qD declared here", fndecl);
	  తిరిగి;
	}
      లేకపోతే ఒకవేళ (append_వాదనలు_వృక్షం)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  పూర్ణాంకం nappend_వాదనలు = 0;
	  పూర్ణాంకం nbase_వాదనలు = 0;
	  కొరకు (వృక్షం t = TYPE_ARG_TYPES (పునాది_type);
	       t && వృక్షం_విలువ (t) != void_type_కణుపు; t = వృక్షం_CHAIN (t))
	    nbase_వాదనలు++;
	  కొరకు (వృక్షం t = append_వాదనలు_వృక్షం; t; t = వృక్షం_CHAIN (t))
	    nappend_వాదనలు++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_వాదనలు_వృక్షం = build_వృక్షం_list (build_int_cst (integer_type_కణుపు,
							     nbase_వాదనలు),
					      append_వాదనలు_వృక్షం);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  ఒకవేళ (!unprototyped_variant)
	    {
	      వృక్షం వాదనలు = TYPE_ARG_TYPES (variant_type);
	      కొరకు (పూర్ణాంకం i = 0; వాదనలు && i < nbase_వాదనలు;
		   i++, వాదనలు = వృక్షం_CHAIN (వాదనలు))
		;
	      కొరకు (పూర్ణాంకం i = 0; i < nappend_వాదనలు; i++, వాదనలు = వృక్షం_CHAIN (వాదనలు))
		ఒకవేళ (!వాదనలు || !c_omp_interop_t_p (వృక్షం_విలువ (వాదనలు)))
		  {
		    error_at (DECL_ఆధారం_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_వాదనలు + i + 1, variant);
		    inform (append_వాదనలు_loc,
			    "%<append_args%> specified here");
		    తిరిగి;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  వృక్షం వాదనలు = TYPE_ARG_TYPES (పునాది_type);
	  వృక్షం newargs = NULL_వృక్షం;
	  వృక్షం lastarg = NULL_వృక్షం;
	  కొరకు (పూర్ణాంకం j = 0; j < nbase_వాదనలు; j++, వాదనలు = వృక్షం_CHAIN (వాదనలు))
	    {
	      వృక్షం t = వృక్షం_cons (వృక్షం_PURPOSE (వాదనలు),
				  వృక్షం_విలువ (వాదనలు), NULL_వృక్షం);
	      ఒకవేళ (lastarg)
		వృక్షం_CHAIN (lastarg) = t;
	      లేకపోతే
		newargs = t;
	      lastarg = t;
	    }
	  వృక్షం type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? వృక్షం_TYPE (type) : సూచిక_sized_int_కణుపు;
	  కొరకు (పూర్ణాంకం j = 0; j < nappend_వాదనలు; j++)
	    {
	      వృక్షం t = వృక్షం_cons (NULL_వృక్షం, type, NULL_వృక్షం);
	      ఒకవేళ (lastarg)
		వృక్షం_CHAIN (lastarg) = t;
	      లేకపోతే
		newargs = t;
	      lastarg = t;
	    }
	  వృక్షం_CHAIN (lastarg) = వాదనలు;

	  /* Temporarily stuff newargs into the original base_type.  */
	  వృక్షం saveargs = TYPE_ARG_TYPES (పునాది_type);
	  TYPE_ARG_TYPES (పునాది_type) = newargs;
	  తార్కిక fail = !comptypes (పునాది_type, variant_type);
	  TYPE_ARG_TYPES (పునాది_type) = saveargs;

	  ఒకవేళ (fail)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_ఆధారం_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      తిరిగి;
	    }
	  లేకపోతే ఒకవేళ (unprototyped_variant)
	    /* If we've got an unprototyped variant, copy the transformed
	       base arg types to the variant.  This is needed later by
	       modify_call_for_omp_dispatch.  */
	    TYPE_ARG_TYPES (variant_type) = newargs;
	}
      లేకపోతే  /* No append_args present.  */
	{
	  ఒకవేళ (!comptypes (పునాది_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_ఆధారం_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      తిరిగి;
	    }
	  లేకపోతే ఒకవేళ (TYPE_ARG_TYPES (variant_type) == NULL_వృక్షం
		   && !TYPE_NO_NAMED_వాదనలు_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (పునాది_type) != NULL_వృక్షం)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (పునాది_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_వాడిన (variant) = 1;
  వృక్షం construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_సమితి_CONSTRUCT);
  omp_mark_declare_variant (సరిపోలిక_loc, variant, construct);
  ఒకవేళ (omp_context_selector_matches (ctx, NULL_వృక్షం, అబద్ధం))
    {
      వృక్షం attr = వృక్షం_cons (get_identifier ("omp declare variant base"),
			     build_వృక్షం_list (variant, ctx),
			     DECL_లక్షణాలు (fndecl));
      DECL_లక్షణాలు (fndecl) = attr;
    }

  ఒకవేళ (need_device_ptr_list || append_వాదనలు_వృక్షం)
    {
      వృక్షం variant_decl = వృక్షం_strip_nop_conversions (variant);
      వృక్షం t = build_వృక్షం_list (need_device_ptr_list,
				NULL_వృక్షం /* need_device_addr */);
      వృక్షం_CHAIN (t) = append_వాదనలు_వృక్షం;
      DECL_లక్షణాలు (variant_decl)
	= వృక్షం_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_లక్షణాలు (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

స్థిర శూన్య
c_ముగింపు_omp_declare_simd (c_parser *parser, వృక్షం fndecl, వృక్షం parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  ఒకవేళ (clauses.exists () && clauses[0].type == CPP_EOF)
    తిరిగి;
  స్థిరరాశి అక్షరం *రకం = "simd";
  ఒకవేళ (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    రకం = IDENTIFIER_సూచిక (clauses[0].విలువ);
  gcc_assert (strcmp (రకం, "simd") == 0 || strcmp (రకం, "variant") == 0);
  ఒకవేళ (fndecl == NULL_వృక్షం || వృక్షం_సంకేతం (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", రకం);
      clauses[0].type = CPP_EOF;
      తిరిగి;
    }
  ఒకవేళ (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_ఆధారం_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", రకం);
      clauses[0].type = CPP_EOF;
      తిరిగి;
    }
  ఒకవేళ (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_ఆధారం_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", రకం);
      తిరిగి;
    }

  ఒకవేళ (parms == NULL_వృక్షం)
    parms = DECL_ARGUMENTS (fndecl);

  గుర్తులేని పూర్ణాంకం టోకెన్లు_avail = parser->టోకెన్లు_avail;
  gcc_assert (parser->టోకెన్లు == &parser->టోకెన్లు_buf[0]);

  parser->టోకెన్లు = clauses.చిరునామా ();
  parser->టోకెన్లు_avail = clauses.నిడివి ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  అయితే (parser->టోకెన్లు_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      రకం = IDENTIFIER_సూచిక (token->విలువ);
      c_parser_consume_token (parser);
      parser->లోపల_pragma = నిజం;

      ఒకవేళ (strcmp (రకం, "simd") == 0)
	{
	  వృక్షం c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_ముసుగు,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_గమ్యం_numbers (parms, c);
	  ఒకవేళ (c != NULL_వృక్షం)
	    c = వృక్షం_cons (NULL_వృక్షం, c, NULL_వృక్షం);
	  c = build_వృక్షం_list (get_identifier ("omp declare simd"), c);
	  వృక్షం_CHAIN (c) = DECL_లక్షణాలు (fndecl);
	  DECL_లక్షణాలు (fndecl) = c;
	}
      లేకపోతే
	{
	  gcc_assert (strcmp (రకం, "variant") == 0);
	  c_ముగింపు_omp_declare_variant (parser, fndecl, parms);
	}
    }

  parser->టోకెన్లు = &parser->టోకెన్లు_buf[0];
  parser->టోకెన్లు_avail = టోకెన్లు_avail;
  ఒకవేళ (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#ఒకవేళ !defined (NO_DOT_లోపల_LABEL)
#నిర్వచించు JOIN_STR "."
#లేదావేళ !defined (NO_DOLLAR_లోపల_LABEL)
#నిర్వచించు JOIN_STR "$"
#లేకపోతే
#నిర్వచించు JOIN_STR "_"
#అయితే_ముగింపు

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
స్థిర వృక్షం
omp_ప్రారంభం_variant_function (c_declarator *declarator, వృక్షం ctx)
{
  c_declarator *id = declarator;
  అయితే (id->రకం != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  వృక్షం name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  తిరిగి name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
స్థిర శూన్య
omp_ముగింపు_variant_function (వృక్షం decl, వృక్షం పునాది_name, వృక్షం ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  వృక్షం పునాది_decl = lookup_name (పునాది_name);
  ఒకవేళ (పునాది_decl == error_mark_కణుపు)
    పునాది_decl = NULL_వృక్షం;
  ఒకవేళ (!పునాది_decl)
    {
      error_at (DECL_ఆధారం_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_సూచిక (పునాది_name));
      తిరిగి;
    }

  ఒకవేళ (!comptypes (వృక్షం_TYPE (decl), వృక్షం_TYPE (పునాది_decl)))
    {
      error_at (DECL_ఆధారం_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", పునాది_decl);
      inform (DECL_ఆధారం_LOCATION (పునాది_decl),
	      "%qE declared here", పునాది_decl);
      తిరిగి;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_ఆధారం_LOCATION (decl),
				   పునాది_decl, ctx);
  వృక్షం construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_సమితి_CONSTRUCT);
  omp_mark_declare_variant (DECL_ఆధారం_LOCATION (decl), decl, construct);
  వృక్షం attrs = DECL_లక్షణాలు (పునాది_decl);
  వృక్షం సరిపోలిక_loc_కణుపు
    = maybe_wrap_with_location (integer_zero_కణుపు,
				DECL_ఆధారం_LOCATION (పునాది_decl));
  వృక్షం loc_కణుపు = వృక్షం_cons (సరిపోలిక_loc_కణుపు, integer_zero_కణుపు,
			     build_వృక్షం_list (సరిపోలిక_loc_కణుపు,
					      integer_zero_కణుపు));
  attrs = వృక్షం_cons (get_identifier ("omp declare variant base"),
		     వృక్షం_cons (decl, ctx, loc_కణుపు), attrs);
  DECL_లక్షణాలు (పునాది_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  వృక్షం_ప్రజా (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

తార్కిక
c_maybe_parse_omp_decl (వృక్షం decl, వృక్షం d)
{
  gcc_assert (వృక్షం_సంకేతం (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_టోకెన్లు (d);
  c_token *మొదటి = toks->చిరునామా ();
  c_token *చివరి = మొదటి + toks->నిడివి ();
  స్థిరరాశి అక్షరం *directive[3] = {};
  కొరకు (పూర్ణాంకం j = 0; j < 3; j++)
    {
      వృక్షం id = NULL_వృక్షం;
      ఒకవేళ (మొదటి + j == చివరి)
	ఆపు;
      ఒకవేళ (మొదటి[j].type == CPP_NAME)
	id = మొదటి[j].విలువ;
      లేకపోతే ఒకవేళ (మొదటి[j].type == CPP_KEYWORD)
	id = ridpointers[(పూర్ణాంకం) మొదటి[j].keyword];
      లేకపోతే
	ఆపు;
      directive[j] = IDENTIFIER_సూచిక (id);
    }
  స్థిరరాశి c_omp_directive *dir = ఖాళీ;
  ఒకవేళ (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  ఒకవేళ (dir == ఖాళీ)
    {
      error_at (మొదటి->location,
		"unknown OpenMP directive name in "
		"%qs attribute argument", "omp::decl");
      తిరిగి అబద్ధం;
    }
  ఒకవేళ (dir->id != PRAGMA_OMP_THREADPRIVATE
      && dir->id != PRAGMA_OMP_GROUPPRIVATE
      && dir->id != PRAGMA_OMP_ALLOCATE
      && (dir->id != PRAGMA_OMP_DECLARE
	  || strcmp (directive[1], "target") != 0))
    తిరిగి అబద్ధం;

  ఒకవేళ (!flag_openmp && !dir->simd)
    తిరిగి నిజం;

  c_parser *parser = the_parser;
  గుర్తులేని పూర్ణాంకం టోకెన్లు_avail = parser->టోకెన్లు_avail;
  gcc_assert (parser->టోకెన్లు == &parser->టోకెన్లు_buf[0]);
  toks = ఖాళీ;
  vec_సురక్షిత_reserve (toks, చివరి - మొదటి + 2, నిజం);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_రకం = pragma_రకం (dir->id);
  tok.location = మొదటి->location;
  toks->శీఘ్ర_నెట్టు (tok);
  అయితే (++మొదటి < చివరి)
    toks->శీఘ్ర_నెట్టు (*మొదటి);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = చివరి[-1].location;
  toks->శీఘ్ర_నెట్టు (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = చివరి[-1].location;
  toks->శీఘ్ర_నెట్టు (tok);
  parser->లోపల_omp_decl_attribute = decl;
  gcc_assert (!parser->లోపల_omp_attribute_pragma);
  parser->లోపల_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->లోపల_omp_attribute_pragma->token_vec = toks;
  parser->లోపల_omp_attribute_pragma->save_టోకెన్లు = parser->టోకెన్లు;
  parser->లోపల_omp_attribute_pragma->save_టోకెన్లు_avail = టోకెన్లు_avail;
  parser->టోకెన్లు = toks->చిరునామా ();
  parser->టోకెన్లు_avail = toks->నిడివి ();
  c_parser_pragma (parser, pragma_external, ఖాళీ, NULL_వృక్షం);
  parser->లోపల_omp_decl_attribute = NULL_వృక్షం;
  తిరిగి నిజం;
}

/* OpenMP 4.0:
   # pragma omp declare target new-line
   declarations and definitions
   # pragma omp end declare target new-line

   OpenMP 4.5:
   # pragma omp declare target ( extended-list ) new-line

   # pragma omp declare target declare-target-clauses[seq] new-line  */

#నిర్వచించు OMP_DECLARE_లక్ష్యం_CLAUSE_ముసుగు				\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_గమ్యం)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ENTER)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_LINK)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_LOCAL)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_పరోక్ష))

స్థిర శూన్య
c_parser_omp_declare_లక్ష్యం (c_parser *parser)
{
  వృక్షం clauses = NULL_వృక్షం;
  పూర్ణాంకం device_type = 0;
  తార్కిక పరోక్ష = అబద్ధం;
  తార్కిక only_device_type_or_పరోక్ష = నిజం;
  ఒకవేళ (flag_openmp)
    omp_requires_ముసుగు
      = (గణన omp_requires) (omp_requires_ముసుగు | OMP_REQUIRES_లక్ష్యం_వాడిన);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
      || (c_parser_తదుపరి_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_లక్ష్యం_CLAUSE_ముసుగు,
					"#pragma omp declare target");
  లేకపోతే ఒకవేళ (parser->లోపల_omp_decl_attribute
	   || c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
    {
      clauses = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					      clauses);
      clauses = c_ముగింపు_omp_clauses (clauses, C_ORT_OMP);
      c_parser_skip_గమ్యం_pragma_eol (parser);
    }
  లేకపోతే
    {
      warning_at (c_parser_peek_token (parser)->location,
		  OPT_Wdeprecated_openmp,
		  "use of %<omp declare target%> as a synonym for "
		  "%<omp begin declare target%> has been deprecated since "
		  "OpenMP 5.2");
      తార్కిక attr_syntax = parser->లోపల_omp_attribute_pragma != ఖాళీ;
      c_parser_skip_గమ్యం_pragma_eol (parser);
      c_omp_declare_లక్ష్యం_attr attr = { attr_syntax, -1, 0 };
      vec_సురక్షిత_నెట్టు (current_omp_declare_లక్ష్యం_attribute, attr);
      తిరిగి;
    }
  కొరకు (వృక్షం c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_రకం (c);
      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_పరోక్ష)
	పరోక్ష |= !integer_zerop (OMP_CLAUSE_పరోక్ష_సమాసం (c));
    }
  కొరకు (వృక్షం c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_పరోక్ష)
	కొనసాగు;
      వృక్షం t = OMP_CLAUSE_DECL (c), id;
      వృక్షం at1 = lookup_attribute ("omp declare target", DECL_లక్షణాలు (t));
      వృక్షం at2 = lookup_attribute ("omp declare target link",
				   DECL_లక్షణాలు (t));
      only_device_type_or_పరోక్ష = అబద్ధం;
      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::మార్పిడి (at1, at2);
	}
      లేకపోతే
	id = get_identifier ("omp declare target");
      ఒకవేళ (at2)
	{
	  ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_గమ్యం (c) ? "to" : "enter");
	  లేకపోతే ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_LOCAL
		   || విలువ_member (get_identifier ("local"), వృక్షం_విలువ (at2)))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<local%> clauses", t);
	  లేకపోతే
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<to%> or %<enter%> clauses", t);
	  కొనసాగు;
	}
      ఒకవేళ (!at1)
	{
	  DECL_లక్షణాలు (t) = వృక్షం_cons (id, NULL_వృక్షం, DECL_లక్షణాలు (t));
	  ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_LOCAL)
	    వృక్షం_విలువ (DECL_లక్షణాలు (t))
	      = వృక్షం_cons (NULL_వృక్షం, get_identifier ("local"),
			   వృక్షం_విలువ (DECL_లక్షణాలు (t)));

	  ఒకవేళ (వృక్షం_సంకేతం (t) != FUNCTION_DECL && !is_global_var (t))
	    కొనసాగు;

	  symtab_కణుపు *కణుపు = symtab_కణుపు::get (t);
	  ఒకవేళ (కణుపు != ఖాళీ)
	    {
	      కణుపు->offloadable = 1;
	      ఒకవేళ (ENABLE_OFFLOADING)
		{
		  g->have_offload = నిజం;
		  ఒకవేళ (is_a <varpool_కణుపు *> (కణుపు)
		      && OMP_CLAUSE_సంకేతం (c) != OMP_CLAUSE_LOCAL)
		    vec_సురక్షిత_నెట్టు (offload_vars, t);
		}
	    }
	}
      లేకపోతే
	{
	  తార్కిక saw_local = విలువ_member (get_identifier ("local"),
					 వృక్షం_విలువ (at1));
	  ఒకవేళ (saw_local && OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_గమ్యం (c) ? "to" : "enter");
	      కొనసాగు;
	    }
	  లేకపోతే ఒకవేళ (!saw_local && OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      కొనసాగు;
	    }
	}
      ఒకవేళ (వృక్షం_సంకేతం (t) != FUNCTION_DECL)
	కొనసాగు;
      ఒకవేళ ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  వృక్షం at3 = lookup_attribute ("omp declare target host",
				       DECL_లక్షణాలు (t));
	  ఒకవేళ (at3 == NULL_వృక్షం)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_లక్షణాలు (t)
		= వృక్షం_cons (id, NULL_వృక్షం, DECL_లక్షణాలు (t));
	    }
	}
      ఒకవేళ ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  వృక్షం at3 = lookup_attribute ("omp declare target nohost",
				       DECL_లక్షణాలు (t));
	  ఒకవేళ (at3 == NULL_వృక్షం)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_లక్షణాలు (t)
		= వృక్షం_cons (id, NULL_వృక్షం, DECL_లక్షణాలు (t));
	    }
	}
      ఒకవేళ (పరోక్ష)
	{
	  వృక్షం at4 = lookup_attribute ("omp declare target indirect",
				       DECL_లక్షణాలు (t));
	  ఒకవేళ (at4 == NULL_వృక్షం)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_లక్షణాలు (t)
		= వృక్షం_cons (id, NULL_వృక్షం, DECL_లక్షణాలు (t));
	    }
	}
    }
  ఒకవేళ ((device_type || పరోక్ష) && only_device_type_or_పరోక్ష)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  ఒకవేళ (పరోక్ష && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "%<device_type%> clause must specify 'any' when used with "
	      "an %<indirect%> clause");
}

/* OpenMP 5.1
   #pragma omp begin assumes clauses[optseq] new-line

   #pragma omp begin declare target clauses[optseq] new-line

   #pragma omp begin declare variant match (context-selector) new-line  */

#నిర్వచించు OMP_BEGIN_DECLARE_లక్ష్యం_CLAUSE_ముసుగు			\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_పరోక్ష))

స్థిర శూన్య
c_parser_omp_begin (c_parser *parser)
{
  స్థిరరాశి అక్షరం *p = "";
  c_parser_consume_pragma (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
  ఒకవేళ (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  తార్కిక attr_syntax = parser->లోపల_omp_attribute_pragma != ఖాళీ;
	  వృక్షం clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_లక్ష్యం_CLAUSE_ముసుగు,
					"#pragma omp begin declare target");
	  పూర్ణాంకం device_type = 0;
	  పూర్ణాంకం పరోక్ష = 0;
	  కొరకు (వృక్షం c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_రకం (c);
	      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_పరోక్ష)
		పరోక్ష |= !integer_zerop (OMP_CLAUSE_పరోక్ష_సమాసం (c));
	    }
	  c_omp_declare_లక్ష్యం_attr attr = { attr_syntax, device_type,
					     పరోక్ష };
	  vec_సురక్షిత_నెట్టు (current_omp_declare_లక్ష్యం_attribute, attr);
	}
      లేకపోతే ఒకవేళ (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  స్థిరరాశి అక్షరం *clause = "";
	  matching_parens parens;
	  location_t సరిపోలిక_loc = c_parser_peek_token (parser)->location;
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	    {
	      వృక్షం id = c_parser_peek_token (parser)->విలువ;
	      clause = IDENTIFIER_సూచిక (id);
	    }
	  ఒకవేళ (strcmp (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_గమ్యం_pragma_eol (parser);
	      తిరిగి;
	    }

	  c_parser_consume_token (parser);

	  ఒకవేళ (!parens.require_open (parser))
	    {
	      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	      తిరిగి;
	    }

	  వృక్షం ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_వృక్షం);
	  ఒకవేళ (ctx != error_mark_కణుపు)
	    ctx = omp_check_context_selector (సరిపోలిక_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  ఒకవేళ (ctx != error_mark_కణుపు
	      && !vec_సురక్షిత_is_ఖాళీలు (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->చివరి ();
	      వృక్షం outer_ctx = a.selector;
	      ctx = omp_విలీనం_context_selectors (సరిపోలిక_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  ఒకవేళ (ctx == error_mark_కణుపు
	      || !omp_context_selector_matches (ctx, NULL_వృక్షం, అబద్ధం, నిజం))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	      c_parser_skip_గమ్యం_pragma_omp_చివర_declare_variant (parser);
	      తిరిగి;
	    }
	  లేకపోతే
	    {
	      తార్కిక attr_syntax = parser->లోపల_omp_attribute_pragma != ఖాళీ;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_సురక్షిత_నెట్టు (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_గమ్యం_pragma_eol (parser);
	}
      లేకపోతే
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	}
    }
  లేకపోతే ఒకవేళ (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      తార్కిక attr_syntax = parser->లోపల_omp_attribute_pragma != ఖాళీ;
      c_parser_omp_assumption_clauses (parser, అబద్ధం);
      నిర్మాణం c_omp_begin_assumes_దత్తాంశం a = { attr_syntax };
      vec_సురక్షిత_నెట్టు (current_omp_begin_assumes, a);
    }
  లేకపోతే
    {
      c_parser_error (parser, "expected %<declare target%>, "
		      "%<declare variant%>, or %<assumes%>");
      c_parser_skip_గమ్యం_pragma_eol (parser);
    }
}

/* OpenMP 4.0
   #pragma omp end declare target

   OpenMP 5.1
   #pragma omp end assumes
   #pragma omp end declare variant  */

స్థిర శూన్య
c_parser_omp_చివర (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  స్థిరరాశి అక్షరం *p = "";
  c_parser_consume_pragma (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
  ఒకవేళ (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  తార్కిక attr_syntax = parser->లోపల_omp_attribute_pragma != ఖాళీ;
	  c_parser_skip_గమ్యం_pragma_eol (parser);
	  ఒకవేళ (!vec_సురక్షిత_నిడివి (current_omp_declare_లక్ష్యం_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  లేకపోతే
	    {
	      c_omp_declare_లక్ష్యం_attr
		a = current_omp_declare_లక్ష్యం_attribute->తీయి ();
	      ఒకవేళ (a.attr_syntax != attr_syntax)
		{
		  ఒకవేళ (a.attr_syntax)
		    error_at (loc,
			      "%qs in attribute syntax terminated "
			      "with %qs in pragma syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		  లేకపోతే
		    error_at (loc,
			      "%qs in pragma syntax terminated "
			      "with %qs in attribute syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		}
	    }
	}
      లేకపోతే ఒకవేళ (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  తార్కిక attr_syntax = parser->లోపల_omp_attribute_pragma != ఖాళీ;
	  c_parser_skip_గమ్యం_pragma_eol (parser);
	  ఒకవేళ (!vec_సురక్షిత_నిడివి (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  లేకపోతే
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->తీయి ();
	      ఒకవేళ (a.attr_syntax != attr_syntax)
		{
		  ఒకవేళ (a.attr_syntax)
		    error_at (loc,
			      "%<begin declare variant%> in attribute syntax "
			      "terminated with "
			      "%<end declare variant%> in pragma syntax");
		  లేకపోతే
		    error_at (loc,
			      "%<begin declare variant%> in pragma syntax "
			      "terminated with "
			      "%<end declare variant%> in attribute syntax");
		}
	    }
	}
      లేకపోతే
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_గమ్యం_pragma_eol (parser);
	  తిరిగి;
	}
    }
  లేకపోతే ఒకవేళ (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      తార్కిక attr_syntax = parser->లోపల_omp_attribute_pragma != ఖాళీ;
      c_parser_skip_గమ్యం_pragma_eol (parser);
      ఒకవేళ (!vec_సురక్షిత_నిడివి (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      లేకపోతే
	{
	  c_omp_begin_assumes_దత్తాంశం
	    a = current_omp_begin_assumes->తీయి ();
	  ఒకవేళ (a.attr_syntax != attr_syntax)
	    {
	      ఒకవేళ (a.attr_syntax)
		error_at (loc,
			  "%qs in attribute syntax terminated "
			  "with %qs in pragma syntax",
			  "begin assumes", "end assumes");
	      లేకపోతే
		error_at (loc,
			  "%qs in pragma syntax terminated "
			  "with %qs in attribute syntax",
			  "begin assumes", "end assumes");
	    }
	}
    }
  లేకపోతే
    {
      c_parser_error (parser, "expected %<declare%> or %<assumes%>");
      c_parser_skip_గమ్యం_pragma_eol (parser);
    }
}

/* OpenMP 5.0
   #pragma omp declare mapper ([mapper-identifier :] type var) \
			      [clause [ [,] clause ] ... ] new-line  */

స్థిర శూన్య
c_parser_omp_declare_mapper (c_parser *parser, గణన pragma_context context)
{
  వృక్షం type, mapper_name = NULL_వృక్షం, var = NULL_వృక్షం, stmt, stmtlist;
  వృక్షం maplist = NULL_వృక్షం, mapper_id, mapper_decl, t;
  c_token *token;

  ఒకవేళ (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare mapper%> not at file or block scope");
      వెళ్ళు fail;
    }

  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    వెళ్ళు fail;

  token = c_parser_peek_token (parser);

  ఒకవేళ (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      ఎంపిక (token->type)
	{
	స్థితి CPP_NAME:
	  mapper_name = token->విలువ;
	  c_parser_consume_token (parser);
	  ఆపు;
	స్థితి CPP_KEYWORD:
	  ఒకవేళ (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_వృక్షం;
	      c_parser_consume_token (parser);
	      ఆపు;
	    }
	  /* Fallthrough.  */
	అప్రమేయ:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	  తిరిగి;
	}

      ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	వెళ్ళు fail;
    }

  mapper_id = c_omp_mapper_id (mapper_name);
  mapper_decl = c_omp_mapper_decl (mapper_id);

  {
    location_t loc = c_parser_peek_token (parser)->location;
    నిర్మాణం c_type_name *ctype = c_parser_type_name (parser);
    type = groktypename (ctype, ఖాళీ, ఖాళీ);
    ఒకవేళ (type == error_mark_కణుపు)
      వెళ్ళు fail;
    ఒకవేళ (!రికార్డు_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	తిరిగి;
      }
    కొరకు (వృక్షం t = DECL_INITIAL (mapper_decl); t; t = వృక్షం_CHAIN (t))
      ఒకవేళ (comptypes (వృక్షం_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_సూచిక (mapper_id)
		      + పరిమాణం ("omp declare mapper ") - 1,
		    type);
	  వృక్షం prevmapper = వృక్షం_విలువ (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_ఆధారం_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	  తిరిగి;
	}
  }

  token = c_parser_peek_token (parser);
  ఒకవేళ (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->విలువ, type);
      c_parser_consume_token (parser);
      DECL_ARTIFICIAL (var) = 1;
    }
  లేకపోతే
    {
      error_at (token->location, "expected identifier");
      వెళ్ళు fail;
    }

  ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    వెళ్ళు fail;

  నెట్టు_scope ();
  stmtlist = నెట్టు_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t ఇక్కడ;
      pragma_omp_clause c_రకం;
      ఇక్కడ = c_parser_peek_token (parser)->location;
      c_రకం = c_parser_omp_clause_name (parser);
      ఒకవేళ (c_రకం != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (ఇక్కడ, "unexpected clause");
	  వెళ్ళు fail;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, నిజం);
    }

  ఒకవేళ (maplist == NULL_వృక్షం)
    {
      error_at (ఆదానం_location, "missing %<map%> clause");
      వెళ్ళు fail;
    }
  వృక్షం list;
  కొరకు (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      వృక్షం dvar = OMP_CLAUSE_DECL (list);
      అయితే (!DECL_P (dvar) && వృక్షం_నిర్వాహ్యం_నిడివి (dvar))
	dvar = వృక్షం_నిర్వాహ్యం (dvar, 0);
      ఒకవేళ (dvar == var)
	ఆపు;
    }
  ఒకవేళ (!list)
    error_at (ఆదానం_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_కణుపు (OMP_DECLARE_MAPPER);
  వృక్షం_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  కూడు_stmt (stmt);

  తీయి_stmt_list (stmtlist);
  తీయి_scope ();

  c_parser_skip_గమ్యం_pragma_eol (parser);

  t = వృక్షం_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  తిరిగి;

 fail:
  c_parser_skip_గమ్యం_pragma_eol (parser);
}

/* OpenMP 4.0
   #pragma omp declare reduction (reduction-id : typename-list : expression) \
      initializer-clause[opt] new-line

   initializer-clause:
      initializer (omp_priv = initializer)
      initializer (function-name (argument-list))  */

స్థిర శూన్య
c_parser_omp_declare_reduction (c_parser *parser, గణన pragma_context context)
{
  గుర్తులేని పూర్ణాంకం టోకెన్లు_avail = 0, i;
  c_token *saved_టోకెన్లు = ఖాళీ;
  vec<వృక్షం> types = vNULL;
  vec<c_token> clauses = vNULL;
  గణన వృక్షం_సంకేతం_2 reduc_సంకేతం = ERROR_MARK;
  వృక్షం reduc_id = NULL_వృక్షం;
  వృక్షం type;
  location_t rloc = c_parser_peek_token (parser)->location;

  ఒకవేళ (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare reduction%> not at file or block scope");
      వెళ్ళు fail;
    }

  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    వెళ్ళు fail;

  ఎంపిక (c_parser_peek_token (parser)->type)
    {
    స్థితి CPP_PLUS:
      reduc_సంకేతం = PLUS_సమాసం;
      ఆపు;
    స్థితి CPP_MULT:
      reduc_సంకేతం = MULT_సమాసం;
      ఆపు;
    స్థితి CPP_MINUS:
      reduc_సంకేతం = MINUS_సమాసం;
      ఆపు;
    స్థితి CPP_AND:
      reduc_సంకేతం = బిట్టు_AND_సమాసం;
      ఆపు;
    స్థితి CPP_XOR:
      reduc_సంకేతం = బిట్టు_XOR_సమాసం;
      ఆపు;
    స్థితి CPP_OR:
      reduc_సంకేతం = బిట్టు_IOR_సమాసం;
      ఆపు;
    స్థితి CPP_AND_AND:
      reduc_సంకేతం = TRUTH_ANDIF_సమాసం;
      ఆపు;
    స్థితి CPP_OR_OR:
      reduc_సంకేతం = TRUTH_ORIF_సమాసం;
      ఆపు;
    స్థితి CPP_NAME:
      స్థిరరాశి అక్షరం *p;
      p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp (p, "min") == 0)
	{
	  reduc_సంకేతం = MIN_సమాసం;
	  ఆపు;
	}
      ఒకవేళ (strcmp (p, "max") == 0)
	{
	  reduc_సంకేతం = MAX_సమాసం;
	  ఆపు;
	}
      reduc_id = c_parser_peek_token (parser)->విలువ;
      ఆపు;
    అప్రమేయ:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      వెళ్ళు fail;
    }

  వృక్షం orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_సంకేతం, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    వెళ్ళు fail;

  అయితే (నిజం)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      నిర్మాణం c_type_name *ctype = c_parser_type_name (parser);
      ఒకవేళ (ctype != ఖాళీ)
	{
	  type = groktypename (ctype, ఖాళీ, ఖాళీ);
	  ఒకవేళ (type == error_mark_కణుపు)
	    ;
	  లేకపోతే ఒకవేళ ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || వృక్షం_సంకేతం (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_వృక్షం)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == FUNCTION_TYPE
		   || వృక్షం_సంకేతం (type) == ARRAY_TYPE)
	    error_at (loc, "function or array type in "
		      "%<#pragma omp declare reduction%>");
	  లేకపోతే ఒకవేళ (TYPE_ATOMIC (type))
	    error_at (loc, "%<_Atomic%> qualified type in "
			   "%<#pragma omp declare reduction%>");
	  లేకపోతే ఒకవేళ (TYPE_QUALS_NO_ADDR_SPACE (type))
	    error_at (loc, "const, volatile or restrict qualified type in "
			   "%<#pragma omp declare reduction%>");
	  లేకపోతే
	    {
	      వృక్షం t;
	      కొరకు (t = DECL_INITIAL (reduc_decl); t; t = వృక్షం_CHAIN (t))
		ఒకవేళ (comptypes (వృక్షం_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_సూచిక (reduc_id)
				   + పరిమాణం ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_ఆధారం_LOCATION (వృక్షం_VEC_ELT (వృక్షం_విలువ (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    ఆపు;
		  }
	      ఒకవేళ (t == NULL_వృక్షం)
		types.సురక్షిత_నెట్టు (type);
	    }
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  లేకపోతే
	    ఆపు;
	}
      లేకపోతే
	ఆపు;
    }

  ఒకవేళ (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_ఖాళీలు ())
    {
     fail:
      clauses.release ();
      types.release ();
      అయితే (నిజం)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ఒకవేళ (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    ఆపు;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_గమ్యం_pragma_eol (parser);
      తిరిగి;
    }

  ఒకవేళ (types.నిడివి () > 1)
    {
      అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  ఒకవేళ (token->type == CPP_EOF)
	    వెళ్ళు fail;
	  clauses.సురక్షిత_నెట్టు (*token);
	  c_parser_consume_token (parser);
	}
      clauses.సురక్షిత_నెట్టు (*c_parser_peek_token (parser));
      c_parser_skip_గమ్యం_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, పరిమాణం (eof_token));
      eof_token.type = CPP_EOF;
      clauses.సురక్షిత_నెట్టు (eof_token);
      clauses.సురక్షిత_నెట్టు (eof_token);
    }

  పూర్ణాంకం errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_టోకెన్లు = parser->టోకెన్లు;
      టోకెన్లు_avail = parser->టోకెన్లు_avail;
      ఒకవేళ (!clauses.is_ఖాళీలు ())
	{
	  parser->టోకెన్లు = clauses.చిరునామా ();
	  parser->టోకెన్లు_avail = clauses.నిడివి ();
	  parser->లోపల_pragma = నిజం;
	}

      తార్కిక nested = current_function_decl != NULL_వృక్షం;
      ఒకవేళ (nested)
	c_నెట్టు_function_context ();
      వృక్షం fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, నిజం);
      నెట్టు_scope ();
      వృక్షం stmt = నెట్టు_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      వృక్షం omp_బహిర్గతం = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_బహిర్గతం) = 1;
      DECL_CONTEXT (omp_బహిర్గతం) = fndecl;
      pushdecl (omp_బహిర్గతం);
      వృక్షం omp_లోపల = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_లోపల) = 1;
      DECL_CONTEXT (omp_లోపల) = fndecl;
      pushdecl (omp_లోపల);
      నిర్మాణం c_సమాసం combiner = c_parser_వ్యక్తీకరణ (parser);
      నిర్మాణం c_సమాసం initializer;
      వృక్షం omp_priv = NULL_వృక్షం, omp_orig = NULL_వృక్షం;
      తార్కిక bad = అబద్ధం;
      initializer.సమితి_error ();
      ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	bad = నిజం;
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      ఒకవేళ (!bad
	  && (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_సూచిక
				(c_parser_peek_token (parser)->విలువ),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  తీయి_scope ();
	  నెట్టు_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_కణుపు;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    bad = నిజం;
	  లేకపోతే ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      bad = నిజం;
	    }
	  లేకపోతే ఒకవేళ (strcmp (IDENTIFIER_సూచిక
				(c_parser_peek_token (parser)->విలువ),
			   "omp_priv") != 0)
	    {
	      ఒకవేళ (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_రకం != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  bad = నిజం;
		}
	      లేకపోతే
		initializer = c_parser_postfix_వ్యక్తీకరణ (parser);
	      ఒకవేళ (initializer.విలువ
		  && వృక్షం_సంకేతం (initializer.విలువ) == CALL_సమాసం)
		{
		  పూర్ణాంకం j;
		  వృక్షం c = initializer.విలువ;
		  కొరకు (j = 0; j < call_సమాసం_nargs (c); j++)
		    {
		      వృక్షం a = CALL_సమాసం_ARG (c, j);
		      STRIP_NOPS (a);
		      ఒకవేళ (వృక్షం_సంకేతం (a) == ADDR_సమాసం
			  && వృక్షం_నిర్వాహ్యం (a, 0) == omp_priv)
			ఆపు;
		    }
		  ఒకవేళ (j == call_సమాసం_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  లేకపోతే
	    {
	      c_parser_consume_token (parser);
	      ఒకవేళ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		bad = నిజం;
	      లేకపోతే
		{
		  వృక్షం st = నెట్టు_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (పంక్తి_పట్టిక, loc);
		  ప్రారంభం_init (omp_priv, NULL_వృక్షం, అబద్ధం, అబద్ధం, &richloc);
		  నిర్మాణం c_సమాసం init = c_parser_initializer (parser, omp_priv);
		  ముగింపు_init ();
		  ముగింపు_decl (omp_priv, loc, init.విలువ,
		      	       init.original_type, NULL_వృక్షం);
		  తీయి_stmt_list (st);
		}
	    }
	  ఒకవేళ (!bad
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    bad = నిజం;
	}

      ఒకవేళ (!bad)
	{
	  c_parser_skip_గమ్యం_pragma_eol (parser);

	  వృక్షం t = వృక్షం_cons (type, make_వృక్షం_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_ఆధారం_LOCATION (omp_బహిర్గతం) = rloc;
	  వృక్షం_VEC_ELT (వృక్షం_విలువ (t), 0) = omp_బహిర్గతం;
	  వృక్షం_VEC_ELT (వృక్షం_విలువ (t), 1) = omp_లోపల;
	  వృక్షం_VEC_ELT (వృక్షం_విలువ (t), 2) = combiner.విలువ;
	  walk_వృక్షం (&combiner.విలువ, c_check_omp_declare_reduction_r,
		     &వృక్షం_VEC_ELT (వృక్షం_విలువ (t), 0), ఖాళీ);
	  ఒకవేళ (omp_priv)
	    {
	      DECL_ఆధారం_LOCATION (omp_priv) = rloc;
	      వృక్షం_VEC_ELT (వృక్షం_విలువ (t), 3) = omp_priv;
	      వృక్షం_VEC_ELT (వృక్షం_విలువ (t), 4) = omp_orig;
	      వృక్షం_VEC_ELT (వృక్షం_విలువ (t), 5) = initializer.విలువ;
	      walk_వృక్షం (&initializer.విలువ, c_check_omp_declare_reduction_r,
			 &వృక్షం_VEC_ELT (వృక్షం_విలువ (t), 3), ఖాళీ);
	      walk_వృక్షం (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &వృక్షం_VEC_ELT (వృక్షం_విలువ (t), 3), ఖాళీ);
	    }
	}

      తీయి_stmt_list (stmt);
      తీయి_scope ();
      ఒకవేళ (cfun->language != ఖాళీ)
	{
	  ggc_free (cfun->language);
	  cfun->language = ఖాళీ;
	}
      సమితి_cfun (ఖాళీ);
      current_function_decl = NULL_వృక్షం;
      ఒకవేళ (nested)
	c_తీయి_function_context ();

      ఒకవేళ (!clauses.is_ఖాళీలు ())
	{
	  parser->టోకెన్లు = saved_టోకెన్లు;
	  parser->టోకెన్లు_avail = టోకెన్లు_avail;
	}
      ఒకవేళ (bad)
	వెళ్ళు fail;
      ఒకవేళ (errs != errorcount)
	ఆపు;
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

స్థిర తార్కిక
c_parser_omp_declare (c_parser *parser, గణన pragma_context context)
{
  c_parser_consume_pragma (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  తిరిగి నిజం;
	}
      ఒకవేళ (strcmp (p, "reduction") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_reduction (parser, context);
	  తిరిగి అబద్ధం;
	}
      ఒకవేళ (strcmp (p, "mapper") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_mapper (parser, context);
	  తిరిగి అబద్ధం;
	}
      ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	  తిరిగి అబద్ధం;
	}
      ఒకవేళ (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_లక్ష్యం (parser);
	  తిరిగి అబద్ధం;
	}
      ఒకవేళ (strcmp (p, "variant") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  తిరిగి నిజం;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_గమ్యం_pragma_eol (parser);
  తిరిగి అబద్ధం;
}

/* OpenMP 5.0
   #pragma omp requires clauses[optseq] new-line  */

స్థిర శూన్య
c_parser_omp_requires (c_parser *parser)
{
  గణన omp_requires new_req = (గణన omp_requires) 0;

  c_parser_consume_pragma (parser);

  location_t loc = c_parser_peek_token (parser)->location;
  అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	{
	  స్థిరరాశి అక్షరం *p
	    = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  గణన omp_requires this_req = (గణన omp_requires) 0;

	  ఒకవేళ (!strcmp (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_చిరునామా;
	  లేకపోతే ఒకవేళ (!strcmp (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_జ్ఞాపకం;
	  లేకపోతే ఒకవేళ (!strcmp (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  లేకపోతే ఒకవేళ (!strcmp (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  లేకపోతే ఒకవేళ (!strcmp (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_తిరగేయి_OFFLOAD;
	  లేకపోతే ఒకవేళ (!strcmp (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      ఒకవేళ (parens.require_open (parser))
		{
		  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
		    {
		      వృక్షం v = c_parser_peek_token (parser)->విలువ;
		      p = IDENTIFIER_సూచిక (v);

		      ఒకవేళ (!strcmp (p, "seq_cst"))
			this_req
			  = (గణన omp_requires) OMP_జ్ఞాపకం_క్రమం_SEQ_CST;
		      లేకపోతే ఒకవేళ (!strcmp (p, "relaxed"))
			this_req
			  = (గణన omp_requires) OMP_జ్ఞాపకం_క్రమం_RELAXED;
		      లేకపోతే ఒకవేళ (!strcmp (p, "release"))
			this_req
			  = (గణన omp_requires) OMP_జ్ఞాపకం_క్రమం_RELEASE;
		      లేకపోతే ఒకవేళ (!strcmp (p, "acq_rel"))
			this_req
			  = (గణన omp_requires) OMP_జ్ఞాపకం_క్రమం_ACQ_REL;
		      లేకపోతే ఒకవేళ (!strcmp (p, "acquire"))
			this_req
			  = (గణన omp_requires) OMP_జ్ఞాపకం_క్రమం_ACQUIRE;
		    }
		  ఒకవేళ (this_req == 0)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<acq_rel%>, %<acquire%>, "
				"%<relaxed%>, %<release%> or %<seq_cst%>");
		      ఎంపిక (c_parser_peek_token (parser)->type)
			{
			స్థితి CPP_EOF:
			స్థితి CPP_PRAGMA_EOL:
			స్థితి CPP_CLOSE_PAREN:
			  ఆపు;
			అప్రమేయ:
			  ఒకవేళ (c_parser_peek_2nd_token (parser)->type
			      == CPP_CLOSE_PAREN)
			    c_parser_consume_token (parser);
			  ఆపు;
			}
		    }
		  లేకపోతే
		    c_parser_consume_token (parser);

		  parens.skip_until_దొరికింది_close (parser);
		  ఒకవేళ (this_req == 0)
		    {
		      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
		      తిరిగి;
		    }
		}
	      p = ఖాళీ;
	    }
	  లేకపోతే
	    {
	      error_at (cloc, "expected %<unified_address%>, "
			      "%<unified_shared_memory%>, "
			      "%<self_maps%>, "
			      "%<dynamic_allocators%>, "
			       "%<reverse_offload%> "
			       "or %<atomic_default_mem_order%> clause");
	      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	      తిరిగి;
	    }
	  ఒకవేళ (p)
	    c_parser_consume_token (parser);
	  ఒకవేళ (this_req)
	    {
	      ఒకవేళ ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_క్రమం) != 0)
		{
		  ఒకవేళ ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  ఒకవేళ (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_ముసుగు & OMP_REQUIRES_లక్ష్యం_వాడిన) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      లేకపోతే ఒకవేళ ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_క్రమం) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (గణన omp_requires) 0;
		}
	      లేకపోతే ఒకవేళ ((omp_requires_ముసుగు
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_క్రమం) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (గణన omp_requires)
		       (omp_requires_ముసుగు
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_క్రమం);
		}
	      లేకపోతే ఒకవేళ ((omp_requires_ముసుగు
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_క్రమం_వాడిన) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (గణన omp_requires) (new_req | this_req);
	      omp_requires_ముసుగు
		= (గణన omp_requires) (omp_requires_ముసుగు | this_req);
	      కొనసాగు;
	    }
	}
      ఆపు;
    }
  c_parser_skip_గమ్యం_pragma_eol (parser);

  ఒకవేళ (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

స్థిర వృక్షం
c_ముగింపు_taskloop_clauses (వృక్షం clauses)
{
  వృక్షం *pc = &clauses;
  కొరకు (వృక్షం c = clauses; c; c = *pc)
    {
      తార్కిక remove = అబద్ధం;
      ఒకవేళ (OMP_CLAUSE_సంకేతం (c) == OMP_CLAUSE_REDUCTION)
	{
	  వృక్షం type = strip_array_types (వృక్షం_TYPE (OMP_CLAUSE_DECL (c)));
	  ఒకవేళ (integer_zerop (TYPE_కొలత_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      remove = నిజం;
	    }
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (TYPE_కొలత_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      remove = నిజం;
	    }
	}
      ఒకవేళ (remove)
	*pc = OMP_CLAUSE_CHAIN (c);
      లేకపోతే
	pc = &OMP_CLAUSE_CHAIN (c);
    }
  తిరిగి clauses;
}

/* OpenMP 4.5:
   #pragma omp taskloop taskloop-clause[optseq] new-line
     for-loop

   #pragma omp taskloop simd taskloop-simd-clause[optseq] new-line
     for-loop  */

#నిర్వచించు OMP_TASKLOOP_CLAUSE_ముసుగు				\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_వ్యక్తిగత)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_GRAINSIZE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_అంకె_TASKS)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_UNTIED)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_FINAL)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_MERGEABLE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_NOGROUP)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ప్రాధాన్యత)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_లోపల_REDUCTION))

స్థిర వృక్షం
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       అక్షరం *p_name, omp_clause_ముసుగు ముసుగు, వృక్షం *cclauses,
		       తార్కిక *if_p)
{
  వృక్షం clauses, ఖండం, ret;

  strcat (p_name, " taskloop");
  ముసుగు |= OMP_TASKLOOP_CLAUSE_ముసుగు;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  ఒకవేళ ((ముసుగు & (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_అంకె_దారాలు)) != 0)
    ముసుగు &= ~(OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_లోపల_REDUCTION);

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);

      ఒకవేళ (strcmp (p, "simd") == 0)
	{
	  వృక్షం cclauses_buf[C_OMP_CLAUSE_విభజించు_లెక్క];
	  ఒకవేళ (cclauses == ఖాళీ)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
	    తిరిగి c_parser_omp_simd (loc, parser, p_name, ముసుగు, cclauses,
				      if_p);
	  ఖండం = c_begin_compound_stmt (నిజం);
	  ret = c_parser_omp_simd (loc, parser, p_name, ముసుగు, cclauses, if_p);
	  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
	  ఒకవేళ (ret == ఖాళీ)
	    తిరిగి ret;
	  ret = make_కణుపు (OMP_TASKLOOP);
	  వృక్షం_TYPE (ret) = void_type_కణుపు;
	  OMP_FOR_BODY (ret) = ఖండం;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_విభజించు_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_ముగింపు_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  సమితి_సమాసం_LOCATION (ret, loc);
	  కూడు_stmt (ret);
	  తిరిగి ret;
	}
    }
  ఒకవేళ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
      తిరిగి NULL_వృక్షం;
    }

  clauses = c_parser_omp_all_clauses (parser, ముసుగు, p_name, cclauses == ఖాళీ);
  ఒకవేళ (cclauses)
    {
      omp_విభజించు_clauses (loc, OMP_TASKLOOP, ముసుగు, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_విభజించు_TASKLOOP];
    }

  clauses = c_ముగింపు_taskloop_clauses (clauses);
  ఖండం = c_begin_compound_stmt (నిజం);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, ఖాళీ, if_p);
  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
  కూడు_stmt (ఖండం);

  తిరిగి ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
స్థిర వృక్షం
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  వృక్షం sizes = NULL_వృక్షం;

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  ఒకవేళ (tok->type != CPP_NAME
      || strcmp ("sizes", IDENTIFIER_సూచిక (tok->విలువ)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      తిరిగి error_mark_కణుపు;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  ఒకవేళ (!parens.require_open (parser))
    తిరిగి error_mark_కణుపు;

  vec<వృక్షం, va_gc> *sizes_vec
    = c_parser_సమాసం_list (parser, నిజం, నిజం, ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ);
  sizes = build_వృక్షం_list_vec (sizes_vec);
  release_వృక్షం_సదిశ (sizes_vec);

  కొరకు (వృక్షం s = sizes; s; s = వృక్షం_CHAIN (s))
    {
      వృక్షం సమాసం = వృక్షం_విలువ (s);
      ఒకవేళ (సమాసం == error_mark_కణుపు)
	{
	  parens.skip_until_దొరికింది_close (parser);
	  తిరిగి error_mark_కణుపు;
	}

      HOST_WIDE_INT n;
      ఒకవేళ (!INTEGRAL_TYPE_P (వృక్షం_TYPE (సమాసం))
	  || !వృక్షం_సరిపోతుంది_shwi_p (సమాసం)
	  || (n = వృక్షం_గమ్యం_shwi (సమాసం)) <= 0
	  || (పూర్ణాంకం) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  వృక్షం_విలువ (s) = integer_one_కణుపు;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  వృక్షం c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  తిరిగి c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

స్థిర వృక్షం
c_parser_omp_tile (location_t loc, c_parser *parser, తార్కిక *if_p)
{
  వృక్షం clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_గమ్యం_pragma_eol (parser);

  ఒకవేళ (!clauses || clauses == error_mark_కణుపు)
    తిరిగి error_mark_కణుపు;

  వృక్షం ఖండం = c_begin_compound_stmt (నిజం);
  వృక్షం ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    ఖాళీ, if_p);
  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
  కూడు_stmt (ఖండం);

  తిరిగి ret;
}

#నిర్వచించు OMP_UNROLL_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_నిండిన))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

స్థిర వృక్షం
c_parser_omp_unroll (location_t loc, c_parser *parser, తార్కిక *if_p)
{
  వృక్షం clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_ముసుగు,
					   "#pragma omp unroll", నిజం);

  వృక్షం ఖండం = c_begin_compound_stmt (నిజం);
  వృక్షం ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    ఖాళీ, if_p);
  ఖండం = c_చివర_compound_stmt (loc, ఖండం, నిజం);
  కూడు_stmt (ఖండం);

  తిరిగి ret;
}

/* OpenMP 5.1
   #pragma omp nothing new-line  */

స్థిర శూన్య
c_parser_omp_nothing (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_గమ్యం_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp error clauses[optseq] new-line  */

స్థిర తార్కిక
c_parser_omp_error (c_parser *parser, గణన pragma_context context)
{
  పూర్ణాంకం at_compilation = -1;
  పూర్ణాంకం severity_fatal = -1;
  వృక్షం సందేశం = NULL_వృక్షం;
  తార్కిక bad = అబద్ధం;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME))
	ఆపు;

      స్థిరరాశి అక్షరం *p
	= IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      location_t cloc = c_parser_peek_token (parser)->location;
      స్థిర స్థిరరాశి అక్షరం *వాదనలు[] = {
	"execution", "compilation", "warning", "fatal"
      };
      పూర్ణాంకం *v = ఖాళీ;
      పూర్ణాంకం idx = 0, n = -1;
      వృక్షం m = NULL_వృక్షం;

      ఒకవేళ (!strcmp (p, "at"))
	v = &at_compilation;
      లేకపోతే ఒకవేళ (!strcmp (p, "severity"))
	{
	  v = &severity_fatal;
	  idx += 2;
	}
      లేకపోతే ఒకవేళ (strcmp (p, "message"))
	{
	  error_at (cloc,
		    "expected %<at%>, %<severity%> or %<message%> clause");
	  c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
	  తిరిగి అబద్ధం;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      ఒకవేళ (parens.require_open (parser))
	{
	  ఒకవేళ (v == ఖాళీ)
	    {
	      location_t సమాసం_loc = c_parser_peek_token (parser)->location;
	      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	      సమాసం = convert_lvalue_గమ్యం_rvalue (సమాసం_loc, సమాసం, నిజం, నిజం);
	      m = convert (const_string_type_కణుపు, సమాసం.విలువ);
	      m = c_fully_fold (m, అబద్ధం, ఖాళీ);
	    }
	  లేకపోతే
	    {
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
		{
		  వృక్షం val = c_parser_peek_token (parser)->విలువ;
		  స్థిరరాశి అక్షరం *q = IDENTIFIER_సూచిక (val);

		  ఒకవేళ (!strcmp (q, వాదనలు[idx]))
		    n = 0;
		  లేకపోతే ఒకవేళ (!strcmp (q, వాదనలు[idx + 1]))
		    n = 1;
		}
	      ఒకవేళ (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", వాదనలు[idx], వాదనలు[idx + 1]);
		  bad = నిజం;
		  ఎంపిక (c_parser_peek_token (parser)->type)
		    {
		    స్థితి CPP_EOF:
		    స్థితి CPP_PRAGMA_EOL:
		    స్థితి CPP_CLOSE_PAREN:
		      ఆపు;
		    అప్రమేయ:
		      ఒకవేళ (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)
			c_parser_consume_token (parser);
		      ఆపు;
		    }
		}
	      లేకపోతే
		c_parser_consume_token (parser);
	    }

	  parens.skip_until_దొరికింది_close (parser);

	  ఒకవేళ (v == ఖాళీ)
	    {
	      ఒకవేళ (సందేశం)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = నిజం;
		}
	      లేకపోతే
		సందేశం = m;
	    }
	  లేకపోతే ఒకవేళ (n != -1)
	    {
	      ఒకవేళ (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = నిజం;
		}
	      లేకపోతే
		*v = n;
	    }
	}
      లేకపోతే
	bad = నిజం;
    }
  c_parser_skip_గమ్యం_pragma_eol (parser);
  ఒకవేళ (bad)
    తిరిగి నిజం;

  ఒకవేళ (at_compilation == -1)
    at_compilation = 1;
  ఒకవేళ (severity_fatal == -1)
    severity_fatal = 1;
  ఒకవేళ (!at_compilation)
    {
      ఒకవేళ (context != pragma_compound)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may only be used in compound statements");
	  తిరిగి నిజం;
	}
      ఒకవేళ (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->లోపల_intervening_సంకేతం)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->fail = నిజం;
	  తిరిగి నిజం;
	}
      వృక్షం fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_లోపల_GOMP_ERROR
						: BUILT_లోపల_GOMP_WARNING);
      ఒకవేళ (!సందేశం)
	సందేశం = build_zero_cst (const_string_type_కణుపు);
      వృక్షం stmt = build_call_సమాసం_loc (loc, fndecl, 2, సందేశం,
				       build_all_ones_cst (కొలత_type_కణుపు));
      కూడు_stmt (stmt);
      తిరిగి నిజం;
    }
  స్థిరరాశి అక్షరం *సందేశం_2 = ఖాళీ;
  ఒకవేళ (సందేశం)
    {
      సందేశం_2 = c_getstr (సందేశం);
      ఒకవేళ (సందేశం_2 == ఖాళీ)
	సందేశం_2 = _("<message unknown at compile time>");
    }
  స్థిరరాశి గణన diagnostics::రకం diag_రకం = (severity_fatal
					    ? diagnostics::రకం::error
					    : diagnostics::రకం::warning);
  ఒకవేళ (సందేశం_2)
    emit_diagnostic (diag_రకం, loc, 0,
		     "%<pragma omp error%> encountered: %s", సందేశం_2);
  లేకపోతే
    emit_diagnostic (diag_రకం, loc, 0,
		     "%<pragma omp error%> encountered");
  తిరిగి అబద్ధం;
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

స్థిర శూన్య
c_parser_omp_assumption_clauses (c_parser *parser, తార్కిక is_assume)
{
  తార్కిక no_openmp = అబద్ధం;
  తార్కిక no_openmp_constructs = అబద్ధం;
  తార్కిక no_openmp_routines = అబద్ధం;
  తార్కిక no_parallelism = అబద్ధం;
  bitmap_తల absent_తల, కలిగియుంది_తల;

  bitmap_obstack_initialize (ఖాళీ);
  bitmap_initialize (&absent_తల, &bitmap_default_obstack);
  bitmap_initialize (&కలిగియుంది_తల, &bitmap_default_obstack);

  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME))
	ఆపు;

      స్థిరరాశి అక్షరం *p
	= IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      location_t cloc = c_parser_peek_token (parser)->location;

      ఒకవేళ (!strcmp (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  ఒకవేళ (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = నిజం;
	}
      లేకపోతే ఒకవేళ (!strcmp (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  ఒకవేళ (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = నిజం;
	}
      లేకపోతే ఒకవేళ (!strcmp (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  ఒకవేళ (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = నిజం;
	}
      లేకపోతే ఒకవేళ (!strcmp (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  ఒకవేళ (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = నిజం;
	}
      లేకపోతే ఒకవేళ (!strcmp (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  ఒకవేళ (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_సమాసం సమాసం = c_parser_సమాసం_no_commas (parser, ఖాళీ);
	      వృక్షం t = convert_lvalue_గమ్యం_rvalue (eloc, సమాసం, నిజం, నిజం).విలువ;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, అబద్ధం, ఖాళీ);
	      ఒకవేళ (is_assume && t != error_mark_కణుపు)
		{
		  వృక్షం fn = build_call_సమాసం_అంతర్గత_loc (eloc, IFN_ASSUME,
							  void_type_కణుపు, 1,
							  t);
		  కూడు_stmt (fn);
		}
	      parens.skip_until_దొరికింది_close (parser);
	    }
	}
      లేకపోతే ఒకవేళ (!strcmp (p, "absent") || !strcmp (p, "contains"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  ఒకవేళ (parens.require_open (parser))
	    {
	      చేయి
		{
		  స్థిరరాశి అక్షరం *directive[3] = {};
		  పూర్ణాంకం i;
		  location_t dloc = c_parser_peek_token (parser)->location;
		  కొరకు (i = 0; i < 3; i++)
		    {
		      వృక్షం id;
		      ఒకవేళ (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->విలువ;
		      లేకపోతే ఒకవేళ (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  గణన rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      లేకపోతే
			ఆపు;
		      directive[i] = IDENTIFIER_సూచిక (id);
		    }
		  ఒకవేళ (i == 0)
		    error_at (dloc, "expected directive name");
		  లేకపోతే
		    {
		      స్థిరరాశి నిర్మాణం c_omp_directive *dir
			= c_omp_categorize_directive (directive[0],
						      directive[1],
						      directive[2]);
		      ఒకవేళ (dir
			  && dir->id != PRAGMA_OMP_చివర
			  && (dir->రకం == C_OMP_DIR_DECLARATIVE
			      || dir->రకం == C_OMP_DIR_INFORMATIONAL
			      || dir->రకం == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      లేకపోతే ఒకవేళ (dir == ఖాళీ
			       || dir->id == PRAGMA_OMP_చివర
			       || (!dir->రెండవ && directive[1])
			       || (!dir->మూడవ && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      లేకపోతే
			{
			  పూర్ణాంకం id = dir - c_omp_directives;
			  ఒకవేళ (bitmap_బిట్టు_p (p[0] == 'a' ? &కలిగియుంది_తల
							: &absent_తల, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  లేకపోతే ఒకవేళ (!bitmap_సమితి_బిట్టు (p[0] == 'a'
						    ? &absent_తల
						    : &కలిగియుంది_తల, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned multiple times in %qs "
					    "clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "", p);
			}
		      కొరకు (; i; --i)
			c_parser_consume_token (parser);
		    }
		  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  లేకపోతే
		    ఆపు;
		}
	      అయితే (1);
	      parens.skip_until_దొరికింది_close (parser);
	    }
	}
      లేకపోతే ఒకవేళ (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
	    {
	      matching_parens parens;
	      parens.consume_open (parser);
	      c_parser_సమతుల్య_token_sequence (parser);
	      parens.require_close (parser);
	    }
	}
      లేకపోతే
	{
	  c_parser_consume_token (parser);
	  error_at (cloc, "expected assumption clause");
	  ఆపు;
	}
    }
  c_parser_skip_గమ్యం_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

స్థిర శూన్య
c_parser_omp_assume (c_parser *parser, తార్కిక *if_p)
{
  c_parser_omp_assumption_clauses (parser, నిజం);
  కూడు_stmt (c_parser_omp_structured_ఖండం (parser, if_p));
}

/* OpenMP 5.1
   #pragma omp assumes clauses[optseq] new-line  */

స్థిర శూన్య
c_parser_omp_assumes (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_omp_assumption_clauses (parser, అబద్ధం);
}

/* Helper function for c_parser_omp_metadirective.  */

స్థిర శూన్య
analyze_metadirective_body (c_parser *parser,
			    vec<c_token> &టోకెన్లు,
			    vec<వృక్షం> &labels)
{
  పూర్ణాంకం nesting_లోతు = 0;
  పూర్ణాంకం bracket_లోతు = 0;
  తార్కిక ignore_label = అబద్ధం;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  అయితే (1)
    {
      c_token *token = c_parser_peek_token (parser);
      తార్కిక stop = అబద్ధం;

      ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_CASE))
	ignore_label = నిజం;

      ఎంపిక (token->type)
	{
	స్థితి CPP_EOF:
	  ఆపు;
	స్థితి CPP_NAME:
	  ఒకవేళ (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.సురక్షిత_నెట్టు (token->విలువ);
	  వెళ్ళు కూడు;
	స్థితి CPP_OPEN_BRACE:
	  ++nesting_లోతు;
	  వెళ్ళు కూడు;
	స్థితి CPP_CLOSE_BRACE:
	  ఒకవేళ (--nesting_లోతు == 0 && bracket_లోతు == 0)
	    stop = నిజం;
	  వెళ్ళు కూడు;
	స్థితి CPP_OPEN_PAREN:
	  ++bracket_లోతు;
	  వెళ్ళు కూడు;
	స్థితి CPP_CLOSE_PAREN:
	  --bracket_లోతు;
	  వెళ్ళు కూడు;
	స్థితి CPP_COLON:
	  ignore_label = అబద్ధం;
	  వెళ్ళు కూడు;
	స్థితి CPP_SEMICOLON:
	  ఒకవేళ (nesting_లోతు == 0 && bracket_లోతు == 0)
	    stop = నిజం;
	  వెళ్ళు కూడు;
	అప్రమేయ:
	కూడు:
	  టోకెన్లు.సురక్షిత_నెట్టు (*token);
	  ఒకవేళ (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  లేకపోతే ఒకవేళ (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_గమ్యం_pragma_eol (parser);
	  లేకపోతే
	    c_parser_consume_token (parser);
	  ఒకవేళ (stop)
	    ఆపు;
	  కొనసాగు;
	}
      ఆపు;
    }
}

/* OpenMP 5.0:

  # pragma omp metadirective [clause[, clause]]
*/

స్థిర శూన్య
c_parser_omp_metadirective (c_parser *parser, తార్కిక *if_p)
{
  స్థిర గుర్తులేని పూర్ణాంకం metadirective_region_లెక్క = 0;

  వృక్షం ret;
  auto_vec<c_token> directive_టోకెన్లు;
  auto_vec<c_token> body_టోకెన్లు;
  auto_vec<వృక్షం> body_labels;
  auto_vec<స్థిరరాశి నిర్మాణం c_omp_directive *> directives;
  auto_vec<వృక్షం> ctxs;
  vec<నిర్మాణం omp_variant> candidates;
  తార్కిక default_చూసిన = అబద్ధం;
  పూర్ణాంకం directive_token_idx = 0;
  వృక్షం standalone_body = NULL_వృక్షం;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  తార్కిక requires_body = అబద్ధం;

  ret = make_కణుపు (OMP_METADIRECTIVE);
  సమితి_సమాసం_LOCATION (ret, pragma_loc);
  వృక్షం_TYPE (ret) = void_type_కణుపు;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_వృక్షం;

  c_parser_consume_pragma (parser);
  అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_NAME)
	  && c_parser_తదుపరి_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  వెళ్ళు error;
	}

      location_t సరిపోలిక_loc = c_parser_peek_token (parser)->location;
      స్థిరరాశి అక్షరం *p = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      ఒకవేళ (strcmp (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.కూడు_fixit_replace (సరిపోలిక_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      తార్కిక default_p
	= strcmp (p, "default") == 0 || strcmp (p, "otherwise") == 0;
      ఒకవేళ (default_p)
	{
	  ఒకవేళ (default_చూసిన)
	    {
	      error_at (సరిపోలిక_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      వెళ్ళు error;
	    }
	  default_చూసిన = నిజం;
	}
      లేకపోతే ఒకవేళ (default_చూసిన)
	{
	  error_at (సరిపోలిక_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  వెళ్ళు error;
	}
      ఒకవేళ (!default_p && strcmp (p, "when") != 0)
	{
	  error_at (సరిపోలిక_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  వెళ్ళు error;
	}

      matching_parens parens;
      వృక్షం ctx = NULL_వృక్షం;
      తార్కిక skip = అబద్ధం;

      ఒకవేళ (!parens.require_open (parser))
	వెళ్ళు error;

      ఒకవేళ (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_వృక్షం);
	  ఒకవేళ (ctx == error_mark_కణుపు)
	    వెళ్ళు error;
	  ctx = omp_check_context_selector (సరిపోలిక_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  ఒకవేళ (ctx == error_mark_కణుపు)
	    వెళ్ళు error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_వృక్షం, అబద్ధం) == 0);

	  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_COLON))
	    {
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      వెళ్ళు error;
	    }
	  c_parser_consume_token (parser);
	}

      /* Read in the directive type and create a dummy pragma token for
	 it.  */
      location_t loc = c_parser_peek_token (parser)->location;

      స్థిరరాశి అక్షరం *directive[3] = {};
      పూర్ణాంకం i;
      కొరకు (i = 0; i < 3; i++)
	{
	  వృక్షం id;
	  ఒకవేళ (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      ఒకవేళ (i == 0)
		directive[i++] = "nothing";
	      ఆపు;
	    }
	  లేకపోతే ఒకవేళ (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->విలువ;
	  లేకపోతే ఒకవేళ (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      గణన rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  లేకపోతే
	    ఆపు;

	  directive[i] = IDENTIFIER_సూచిక (id);
	}
      ఒకవేళ (i == 0)
	{
	  error_at (loc, "expected directive name");
	  వెళ్ళు error;
	}

      స్థిరరాశి నిర్మాణం c_omp_directive *omp_directive
	= c_omp_categorize_directive (directive[0],
				      directive[1],
				      directive[2]);

      ఒకవేళ (omp_directive == ఖాళీ)
	{
	  కొరకు (పూర్ణాంకం j = 0; j < i; j++)
	    c_parser_consume_token (parser);
	  c_parser_error (parser, "unknown directive name");
	  వెళ్ళు error;
	}
      లేకపోతే
	{
	  పూర్ణాంకం token_లెక్క = 0;
	  ఒకవేళ (omp_directive->మొదటి) token_లెక్క++;
	  ఒకవేళ (omp_directive->రెండవ) token_లెక్క++;
	  ఒకవేళ (omp_directive->మూడవ) token_లెక్క++;
	  కొరకు (పూర్ణాంకం j = 0; j < token_లెక్క; j++)
	    c_parser_consume_token (parser);
	}
      ఒకవేళ (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  వెళ్ళు error;
	}
      ఒకవేళ (omp_directive->రకం == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  వెళ్ళు error;
	}
      ఒకవేళ (omp_directive->రకం == C_OMP_DIR_CONSTRUCT)
	requires_body = నిజం;

      ఒకవేళ (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_రకం = (గణన pragma_రకం) omp_directive->id;

	  directives.సురక్షిత_నెట్టు (omp_directive);
	  directive_టోకెన్లు.సురక్షిత_నెట్టు (pragma_token);
	  ctxs.సురక్షిత_నెట్టు (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      పూర్ణాంకం nesting_లోతు = 0;
      అయితే (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ఎంపిక (token->type)
	    {
	    స్థితి CPP_EOF:
	    స్థితి CPP_PRAGMA_EOL:
	      ఆపు;
	    స్థితి CPP_OPEN_PAREN:
	      ++nesting_లోతు;
	      వెళ్ళు కూడు;
	    స్థితి CPP_CLOSE_PAREN:
	      ఒకవేళ (nesting_లోతు-- == 0)
		{
		  c_parser_consume_token (parser);
		  ఆపు;
		}
	      వెళ్ళు కూడు;
	    అప్రమేయ:
	    కూడు:
	      ఒకవేళ (!skip)
		directive_టోకెన్లు.సురక్షిత_నెట్టు (*token);
	      c_parser_consume_token (parser);
	      కొనసాగు;
	    }
	  ఆపు;
	}

      ఒకవేళ (!skip)
	{
	  c_token eol_token;
	  memset (&eol_token, 0, పరిమాణం (eol_token));
	  eol_token.type = CPP_PRAGMA_EOL;
	  directive_టోకెన్లు.సురక్షిత_నెట్టు (eol_token);
	}
    }
  c_parser_skip_గమ్యం_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  ఒకవేళ (ctxs.నిడివి () == 1)
    {
      వృక్షం ctx = ctxs[0];
      ఒకవేళ (ctx == NULL_వృక్షం
	  || (omp_context_selector_matches (ctx, NULL_వృక్షం, అబద్ధం) == 1
	      && directive_టోకెన్లు[0].pragma_రకం == PRAGMA_OMP_NOTHING))
	తిరిగి;
    }

  ఒకవేళ (!default_చూసిన)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      స్థిరరాశి నిర్మాణం c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", ఖాళీ, ఖాళీ);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_రకం = PRAGMA_OMP_NOTHING;

      directives.సురక్షిత_నెట్టు (omp_directive);
      directive_టోకెన్లు.సురక్షిత_నెట్టు (pragma_token);
      ctxs.సురక్షిత_నెట్టు (NULL_వృక్షం);

      c_token eol_token;
      memset (&eol_token, 0, పరిమాణం (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_టోకెన్లు.సురక్షిత_నెట్టు (eol_token);
    }

  ఒకవేళ (requires_body)
    analyze_metadirective_body (parser, body_టోకెన్లు, body_labels);

  /* Process each candidate directive.  */
  గుర్తులేని i;
  వృక్షం ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> టోకెన్లు;

      /* Add the directive tokens.  */
      చేయి
	టోకెన్లు.సురక్షిత_నెట్టు (directive_టోకెన్లు [directive_token_idx++]);
      అయితే (టోకెన్లు.చివరి ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_టోకెన్లు.is_ఖాళీలు ());
      కొరకు (గుర్తులేని j = 0; j < body_టోకెన్లు.నిడివి (); j++)
	టోకెన్లు.సురక్షిత_నెట్టు (body_టోకెన్లు[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, పరిమాణం (eof_token));
      eof_token.type = CPP_EOF;
      టోకెన్లు.సురక్షిత_నెట్టు (eof_token);
      టోకెన్లు.సురక్షిత_నెట్టు (eof_token);

      గుర్తులేని పూర్ణాంకం old_టోకెన్లు_avail = parser->టోకెన్లు_avail;
      c_token *old_టోకెన్లు = parser->టోకెన్లు;
      నిర్మాణం omp_attribute_pragma_state *old_లోపల_omp_attribute_pragma
	= parser->లోపల_omp_attribute_pragma;
      నిర్మాణం omp_metadirective_parse_దత్తాంశం *old_state
	= parser->omp_metadirective_state;

      నిర్మాణం omp_metadirective_parse_దత్తాంశం new_state;
      new_state.body_labels = &body_labels;
      new_state.region_అంకె = ++metadirective_region_లెక్క;

      parser->టోకెన్లు = టోకెన్లు.చిరునామా ();
      parser->టోకెన్లు_avail = టోకెన్లు.నిడివి ();
      parser->లోపల_omp_attribute_pragma = ఖాళీ;
      parser->omp_metadirective_state = &new_state;

      పూర్ణాంకం prev_errorcount = errorcount;
      వృక్షం directive = c_begin_compound_stmt (నిజం);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_వృక్షం);
      directive = c_చివర_compound_stmt (pragma_loc, directive, నిజం);
      తార్కిక standalone_p
	= directives[i]->రకం == C_OMP_DIR_STANDALONE
	  || directives[i]->రకం == C_OMP_DIR_UTILITY;
      ఒకవేళ (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  ఒకవేళ (standalone_body == NULL_వృక్షం)
	    {
	      standalone_body = నెట్టు_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = తీయి_stmt_list (standalone_body);
	    }
	  లేకపోతే
	    c_parser_skip_గమ్యం_చివర_యొక్క_ఖండం_or_statement (parser, నిజం);
	}

      వృక్షం body = standalone_p ? standalone_body : NULL_వృక్షం;
      వృక్షం variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      ఒకవేళ (errorcount == prev_errorcount)
	{
	  gcc_assert (parser->టోకెన్లు_avail == 2);
	  gcc_assert (c_parser_తదుపరి_token_is (parser, CPP_EOF));
	  gcc_assert (c_parser_peek_2nd_token (parser)->type == CPP_EOF);
	}

      parser->టోకెన్లు = old_టోకెన్లు;
      parser->టోకెన్లు_avail = old_టోకెన్లు_avail;
      parser->లోపల_omp_attribute_pragma = old_లోపల_omp_attribute_pragma;
      parser->omp_metadirective_state = old_state;
    }

  /* Try to resolve the metadirective early.  */
  candidates = omp_early_resolve_metadirective (ret);
  ఒకవేళ (!candidates.is_ఖాళీలు ())
    ret = c_omp_expand_variant_construct (candidates);

  కూడు_stmt (ret);
  తిరిగి;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  ఒకవేళ (parser->లోపల_pragma)
    c_parser_skip_గమ్యం_pragma_eol (parser, అబద్ధం);
}

/* Main entry point to parsing most OpenMP pragmas.  */

స్థిర శూన్య
c_parser_omp_construct (c_parser *parser, తార్కిక *if_p)
{
  గణన pragma_రకం p_రకం;
  location_t loc;
  వృక్షం stmt;
  అక్షరం p_name[పరిమాణం "#pragma omp teams distribute parallel for simd"];
  omp_clause_ముసుగు ముసుగు (0);

  loc = c_parser_peek_token (parser)->location;
  p_రకం = c_parser_peek_token (parser)->pragma_రకం;
  c_parser_consume_pragma (parser);

  ఎంపిక (p_రకం)
    {
    స్థితి PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, నిజం);
      తిరిగి;
    స్థితి PRAGMA_OACC_CACHE:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      ఆపు;
    స్థితి PRAGMA_OACC_దత్తాంశం:
      stmt = c_parser_oacc_దత్తాంశం (loc, parser, if_p);
      ఆపు;
    స్థితి PRAGMA_OACC_HOST_దత్తాంశం:
      stmt = c_parser_oacc_host_దత్తాంశం (loc, parser, if_p);
      ఆపు;
    స్థితి PRAGMA_OACC_KERNELS:
    స్థితి PRAGMA_OACC_PARALLEL:
    స్థితి PRAGMA_OACC_SERIAL:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_రకం, p_name, if_p);
      ఆపు;
    స్థితి PRAGMA_OACC_LOOP:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, ముసుగు, ఖాళీ, if_p);
      ఆపు;
    స్థితి PRAGMA_OACC_WAIT:
      strcpy (p_name, "#pragma wait");
      stmt = c_parser_oacc_wait (loc, parser, p_name);
      ఆపు;
    స్థితి PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (loc, parser, అబద్ధం);
      తిరిగి;
    స్థితి PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (loc, parser, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_DISTRIBUTE:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_distribute (loc, parser, p_name, ముసుగు, ఖాళీ, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_FOR:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, ముసుగు, ఖాళీ, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_LOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, ముసుగు, ఖాళీ, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_MASKED:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, ముసుగు, ఖాళీ, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_MASTER:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, ముసుగు, ఖాళీ, if_p,
				  UNKNOWN_LOCATION);
      ఆపు;
    స్థితి PRAGMA_OMP_PARALLEL:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, ముసుగు, ఖాళీ, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_SECTIONS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, ముసుగు, ఖాళీ);
      ఆపు;
    స్థితి PRAGMA_OMP_SIMD:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, ముసుగు, ఖాళీ, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (loc, parser, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_TASK:
      stmt = c_parser_omp_task (loc, parser, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_TASKGROUP:
      stmt = c_parser_omp_taskgroup (loc, parser, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_TASKLOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_taskloop (loc, parser, p_name, ముసుగు, ఖాళీ, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_TEAMS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, ముసుగు, ఖాళీ, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_ASSUME:
      c_parser_omp_assume (parser, if_p);
      తిరిగి;
    స్థితి PRAGMA_OMP_TILE:
      stmt = c_parser_omp_tile (loc, parser, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_UNROLL:
      stmt = c_parser_omp_unroll (loc, parser, if_p);
      ఆపు;
    స్థితి PRAGMA_OMP_DISPATCH:
      stmt = c_parser_omp_dispatch (loc, parser);
      ఆపు;
    అప్రమేయ:
      gcc_unreachable ();
    }

  ఒకవేళ (stmt && stmt != error_mark_కణుపు)
    gcc_assert (సమాసం_LOCATION (stmt) != UNKNOWN_LOCATION);
}

/* OpenMP 6.0:
   # pragma omp groupprivate (variable-list) [device_type(...)]  */

#నిర్వచించు OMP_GROUPPRIVATE_CLAUSE_ముసుగు					\
	( (OMP_CLAUSE_ముసుగు_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE) )

స్థిర శూన్య
c_parser_omp_groupprivate (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  వృక్షం vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ఖాళీ);
  వృక్షం clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_ముసుగు,
					   "#pragma omp groupprivate");
  /* TODO: Implies 'declare target local' with specified device_type, check for
     conflicts.  Check for other restrictions.  */
  (శూన్య) vars;
  (శూన్య) clauses;
  sorry_at (loc, "%<omp groupprivate%>");
}

/* OpenMP 2.5:
   # pragma omp threadprivate (variable-list) */

స్థిర శూన్య
c_parser_omp_threadprivate (c_parser *parser)
{
  వృక్షం vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ఖాళీ);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  కొరకు (t = vars; t; t = వృక్షం_CHAIN (t))
    {
      వృక్షం v = వృక్షం_PURPOSE (t);
      loc = సమాసం_LOCATION (వృక్షం_విలువ (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      ఒకవేళ (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      లేకపోతే ఒకవేళ (వృక్షం_వాడిన (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      లేకపోతే ఒకవేళ (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      లేకపోతే ఒకవేళ (వృక్షం_TYPE (v) == error_mark_కణుపు)
	;
      లేకపోతే ఒకవేళ (! COMPLETE_TYPE_P (వృక్షం_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      లేకపోతే
	{
	  ఒకవేళ (! DECL_THREAD_LOCAL_P (v))
	    {
	      సమితి_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      ఒకవేళ (DECL_RTL_సమితి_P (v))
		make_decl_rtl (v);
	    }
	  C_DECL_THREADPRIVATE_P (v) = 1;
	}
    }

  c_parser_skip_గమ్యం_pragma_eol (parser);
}

/* Parse a transaction attribute (GCC Extension).

   transaction-attribute:
     gnu-attributes
     attribute-specifier
*/

స్థిర వృక్షం
c_parser_transaction_లక్షణాలు (c_parser *parser)
{
  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_ATTRIBUTE))
    తిరిగి c_parser_gnu_లక్షణాలు (parser);

  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_OPEN_వర్గం))
    తిరిగి NULL_వృక్షం;
  తిరిగి c_parser_std_attribute_specifier (parser, నిజం);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

స్థిర వృక్షం
c_parser_transaction (c_parser *parser, గణన rid keyword)
{
  గుర్తులేని పూర్ణాంకం old_లోపల = parser->లోపల_transaction;
  గుర్తులేని పూర్ణాంకం this_లోపల = 1, new_లోపల;
  location_t loc = c_parser_peek_token (parser)->location;
  వృక్షం stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_తదుపరి_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  ఒకవేళ (keyword == RID_TRANSACTION_RELAXED)
    this_లోపల |= TM_STMT_ATTR_RELAXED;
  లేకపోతే
    {
      attrs = c_parser_transaction_లక్షణాలు (parser);
      ఒకవేళ (attrs)
	this_లోపల |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_లోపల = this_లోపల | (old_లోపల & TM_STMT_ATTR_OUTER);

  parser->లోపల_transaction = new_లోపల;
  stmt = c_parser_compound_statement (parser);
  parser->లోపల_transaction = old_లోపల;

  ఒకవేళ (flag_tm)
    stmt = c_ముగింపు_transaction (loc, stmt, this_లోపల);
  లేకపోతే
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  తిరిగి stmt;
}

/* Parse a __transaction_atomic or __transaction_relaxed expression
   (GCC Extension).

   transaction-expression:
     __transaction_atomic ( expression )
     __transaction_relaxed ( expression )
*/

స్థిర నిర్మాణం c_సమాసం
c_parser_transaction_వ్యక్తీకరణ (c_parser *parser, గణన rid keyword)
{
  నిర్మాణం c_సమాసం ret;
  గుర్తులేని పూర్ణాంకం old_లోపల = parser->లోపల_transaction;
  గుర్తులేని పూర్ణాంకం this_లోపల = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  వృక్షం attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_తదుపరి_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  ఒకవేళ (keyword == RID_TRANSACTION_RELAXED)
    this_లోపల |= TM_STMT_ATTR_RELAXED;
  లేకపోతే
    {
      attrs = c_parser_transaction_లక్షణాలు (parser);
      ఒకవేళ (attrs)
	this_లోపల |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->లోపల_transaction = this_లోపల;
  matching_parens parens;
  ఒకవేళ (parens.require_open (parser))
    {
      వృక్షం సమాసం = c_parser_వ్యక్తీకరణ (parser).విలువ;
      ret.original_type = వృక్షం_TYPE (సమాసం);
      ret.విలువ = build1 (TRANSACTION_సమాసం, ret.original_type, సమాసం);
      ఒకవేళ (this_లోపల & TM_STMT_ATTR_RELAXED)
	TRANSACTION_సమాసం_RELAXED (ret.విలువ) = 1;
      సమితి_సమాసం_LOCATION (ret.విలువ, loc);
      ret.original_సంకేతం = TRANSACTION_సమాసం;
      ret.m_decimal = 0;
      ఒకవేళ (!parens.require_close (parser))
	{
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, ఖాళీ);
	  వెళ్ళు error;
	}
    }
  లేకపోతే
    {
     error:
      ret.సమితి_error ();
      ret.original_సంకేతం = ERROR_MARK;
      ret.original_type = ఖాళీ;
    }
  parser->లోపల_transaction = old_లోపల;

  ఒకవేళ (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  సమితి_c_సమాసం_ఆధారం_range (&ret, loc, loc);

  తిరిగి ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

స్థిర వృక్షం
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  వృక్షం attrs;
  తార్కిక is_outer = అబద్ధం;

  gcc_assert (c_parser_తదుపరి_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_లక్షణాలు (parser);
  ఒకవేళ (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  ఒకవేళ (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      వెళ్ళు ret_error;
    }
  లేకపోతే ఒకవేళ (parser->లోపల_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      వెళ్ళు ret_error;
    }
  లేకపోతే ఒకవేళ (is_outer)
    {
      ఒకవేళ ((parser->లోపల_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  వెళ్ళు ret_error;
	}
    }
  లేకపోతే ఒకవేళ (parser->లోపల_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      వెళ్ళు ret_error;
    }

  తిరిగి కూడు_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  తిరిగి build1 (NOP_సమాసం, void_type_కణుపు, error_mark_కణుపు);
}

/* Parse a single source file.  */

శూన్య
c_parse_file (శూన్య)
{
  /* Use local storage to begin.  If the first token is a pragma, parse it.
     If it is #pragma GCC pch_preprocess, then this will load a PCH file
     which will cause garbage collection.  */
  c_parser tparser;

  memset (&tparser, 0, పరిమాణం tparser);
  tparser.translate_అక్షరశ్రేణులు_p = నిజం;
  tparser.టోకెన్లు = &tparser.టోకెన్లు_buf[0];
  the_parser = &tparser;

  ఒకవేళ (c_parser_peek_token (&tparser)->pragma_రకం == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  లేకపోతే
    c_common_no_మరిన్ని_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  ఒకవేళ (tparser.టోకెన్లు == &tparser.టోకెన్లు_buf[0])
    the_parser->టోకెన్లు = &the_parser->టోకెన్లు_buf[0];

  /* Initialize EH, if we've been told to do so.  */
  ఒకవేళ (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = ఖాళీ;
}

శూన్య
c_init_preprocess (శూన్య)
{
  /* Create a parser for use by pragma_lex during preprocessing.  */
  the_parser = ggc_alloc<c_parser> ();
  memset (the_parser, 0, పరిమాణం (c_parser));
  the_parser->టోకెన్లు = &the_parser->టోకెన్లు_buf[0];
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
c_parser_parse_rtl_body (c_parser *parser, అక్షరం *ప్రారంభం_with_pass)
{
  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      విడుదల (ప్రారంభం_with_pass);
      తిరిగి c_parser_peek_token (parser)->location;
    }

  location_t ప్రారంభం_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  పూర్ణాంకం అంకె_open_braces = 1;
  అయితే (1)
    {
      ఎంపిక (c_parser_peek_token (parser)->type)
	{
	స్థితి CPP_OPEN_BRACE:
	  అంకె_open_braces++;
	  ఆపు;
	స్థితి CPP_CLOSE_BRACE:
	  ఒకవేళ (--అంకె_open_braces == 0)
	    వెళ్ళు దొరికింది_closing_brace;
	  ఆపు;
	స్థితి CPP_EOF:
	  error_at (ప్రారంభం_loc, "no closing brace");
	  విడుదల (ప్రారంభం_with_pass);
	  తిరిగి c_parser_peek_token (parser)->location;
	అప్రమేయ:
	  ఆపు;
	}
      c_parser_consume_token (parser);
    }

 దొరికింది_closing_brace:
  /* At the closing brace; record its location.  */
  location_t చివర_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  ఒకవేళ (!read_rtl_function_body_from_file_range (ప్రారంభం_loc, చివర_loc))
    {
      విడుదల (ప్రారంభం_with_pass);
      తిరిగి చివర_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  నిరంతరం_rtl_passes (ప్రారంభం_with_pass);
  తిరిగి చివర_loc;
}

#అన్తర్భావ "gt-c-c-parser.h"
