/* Declarations for the parser for C and Objective-C.
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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GCC_C_PARSER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GCC_C_PARSER_H

/* The C lexer intermediates between the lexer in cpplib and c-lex.cc
   and the C parser.  Unlike the C++ lexer, the parser structure
   stores the lexer information instead of using a separate structure.
   Identifiers are separated into ordinary identifiers, type names,
   keywords and some other Objective-C types of identifiers, and some
   look-ahead is maintained.

   ??? It might be a good idea to lex the whole file up front (as for
   C++).  It would then be possible to share more of the C and C++
   lexer code, if desired.  */

/* More information about the type of a CPP_NAME token.  */
ਗਿਣਤੀ c_id_ਕਿਸਮ {
  /* An ordinary identifier.  */
  C_ID_ID,
  /* An identifier declared as a typedef name.  */
  C_ID_TYPENAME,
  /* An identifier declared as an Objective-C class name.  */
  C_ID_CLASSNAME,
  /* An address space identifier.  */
  C_ID_ADDRSPACE,
  /* Not an identifier.  */
  C_ID_NONE
};

/* A single C token after string literal concatenation and conversion
   of preprocessing tokens to tokens.  */
ਬਣਤਰ GTY (()) c_token {
  /* The kind of token.  */
  ਗਿਣਤੀ cpp_ttype type : 8;
  /* If this token is a CPP_NAME, this value indicates whether also
     declared as some kind of type.  Otherwise, it is C_ID_NONE.  */
  ਗਿਣਤੀ c_id_ਕਿਸਮ id_ਕਿਸਮ : 8;
  /* If this token is a keyword, this value indicates which keyword.
     Otherwise, this value is RID_MAX.  */
  ਗਿਣਤੀ rid keyword : 8;
  /* If this token is a CPP_PRAGMA, this indicates the pragma that
     was seen.  Otherwise it is PRAGMA_NONE.  */
  ਗਿਣਤੀ pragma_ਕਿਸਮ pragma_ਕਿਸਮ : 8;
  /* The location at which this token was found.  */
  location_t location;
  /* The value associated with this token, if any.  */
  ਰੁੱਖ ਮੁੱਲ;
  /* Token flags.  */
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ flags;

  ਸਰੋਤ_range get_range () ਅਚਲ
  {
    ਵਾਪਸ get_range_from_loc (ਸਤਰ_ਸਾਰਣੀ, location);
  }

  location_t get_ਅੰਤ () ਅਚਲ
  {
    ਵਾਪਸ get_range ().m_ਅੰਤ;
  }
};

/* This should have the same layout as c_tree_token_vec
   in c-decl.cc, but for GTY reasons with ObjC can't be
   GTY itself.  */
ਬਣਤਰ c_ਰੁੱਖ_token_vec_struct {
  ਬਣਤਰ ਰੁੱਖ_ਅਧਾਰ ਅਧਾਰ;
  vec<c_token, va_gc> *ਟੋਕਨ;
};

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ C_TOKEN_VEC_ਟੋਕਨ(ਗੰਢ_2) \
  (((ਬਣਤਰ c_ਰੁੱਖ_token_vec_struct *) ਰੁੱਖ_CHECK (ਗੰਢ_2, C_TOKEN_VEC))->ਟੋਕਨ)

/* The parser.  */
ਬਣਤਰ c_parser;

/* Possibly kinds of declarator to parse.  */
ਗਿਣਤੀ c_dtr_syn {
  /* A normal declarator with an identifier.  */
  C_DTR_ਸਾਧਾਰਨ,
  /* An abstract declarator (maybe empty).  */
  C_DTR_ABSTRACT,
  /* A parameter declarator: may be either, but after a type name does
     not redeclare a typedef name as an identifier if it can
     alternatively be interpreted as a typedef name; see DR#009,
     applied in C90 TC1, omitted from C99 and reapplied in C99 TC2
     following DR#249.  For example, given a typedef T, "int T" and
     "int *T" are valid parameter declarations redeclaring T, while
     "int (T)" and "int * (T)" and "int (T[])" and "int (T (int))" are
     abstract declarators rather than involving redundant parentheses;
     the same applies with attributes inside the parentheses before
     "T".  */
  C_DTR_PARM
};

/* The binary operation precedence levels, where 0 is a dummy lowest level
   used for the bottom of the stack.  */
ਗਿਣਤੀ c_parser_prec {
  PREC_NONE,
  PREC_LOGOR,
  PREC_LOGAND,
  PREC_BITOR,
  PREC_BITXOR,
  PREC_BITAND,
  PREC_EQ,
  PREC_REL,
  PREC_ਖਿਸਕਾਓ,
  PREC_ਜੋੜੋ,
  PREC_MULT,
  ਅੰਕ_PRECS
};

ਗਿਣਤੀ c_lookahead_ਕਿਸਮ {
  /* Always treat unknown identifiers as typenames.  */
  cla_prefer_type,

  /* Could be parsing a nonabstract declarator.  Only treat an identifier
     as a typename if followed by another identifier or a star.  */
  cla_nonabstract_decl,

  /* Never treat identifiers as typenames.  */
  cla_prefer_id
};


ਬਾਹਰੀ c_token * c_parser_peek_token (c_parser *parser);
ਬਾਹਰੀ c_token * c_parser_peek_2nd_token (c_parser *parser);
ਬਾਹਰੀ c_token * c_parser_peek_nth_token (c_parser *parser, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ n);
ਬਾਹਰੀ bool c_parser_require (c_parser *parser, ਗਿਣਤੀ cpp_ttype type,
			      ਅਚਲ ਅੱਖਰ *msgid,
			      location_t matching_location = UNKNOWN_LOCATION,
			      bool type_is_unique=true);
ਬਾਹਰੀ bool c_parser_error (c_parser *parser, ਅਚਲ ਅੱਖਰ *gmsgid);
ਬਾਹਰੀ ਖਾਲੀ c_parser_consume_token (c_parser *parser);
ਬਾਹਰੀ ਖਾਲੀ c_parser_skip_until_ਮਿਲਿਆ (c_parser *parser, ਗਿਣਤੀ cpp_ttype type,
				       ਅਚਲ ਅੱਖਰ *msgid,
				       location_t = UNKNOWN_LOCATION);
ਬਾਹਰੀ bool c_parser_ਅਗਲਾ_token_starts_declspecs (c_parser *parser);
bool c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_declaration (c_parser *parser,
					     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ n = 1);
bool c_token_starts_typename (c_token *token);

/* Abstraction to avoid defining c_parser here which messes up gengtype
   output wrt ObjC due to vec<c_token> routines being put in gtype-c.h
   but not gtype-objc.h.  */
ਬਾਹਰੀ c_token * c_parser_ਟੋਕਨ_buf (c_parser *parser, ਬਿਨਾਨਿਸ਼ਾਨੀ n);
ਬਾਹਰੀ bool c_parser_error (c_parser *parser);
ਬਾਹਰੀ ਖਾਲੀ c_parser_ਸੈੱਟ_error (c_parser *parser, bool);

/* A bit of a hack to have this here.  It would be better in a c-decl.h.  */
ਬਾਹਰੀ bool old_style_parameter_scope (ਖਾਲੀ);

/* Return true if the next token from PARSER has the indicated
   TYPE.  */

ਸਤਰਅੰਦਰ bool
c_parser_ਅਗਲਾ_token_is (c_parser *parser, ਗਿਣਤੀ cpp_ttype type)
{
  ਵਾਪਸ c_parser_peek_token (parser)->type == type;
}

/* Return true if the next token from PARSER does not have the
   indicated TYPE.  */

ਸਤਰਅੰਦਰ bool
c_parser_ਅਗਲਾ_token_is_not (c_parser *parser, ਗਿਣਤੀ cpp_ttype type)
{
  ਵਾਪਸ !c_parser_ਅਗਲਾ_token_is (parser, type);
}

/* Return true if the next token from PARSER is the indicated
   KEYWORD.  */

ਸਤਰਅੰਦਰ bool
c_parser_ਅਗਲਾ_token_is_keyword (c_parser *parser, ਗਿਣਤੀ rid keyword)
{
  ਵਾਪਸ c_parser_peek_token (parser)->keyword == keyword;
}

ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_string_literal (c_parser *, bool, bool);
ਬਾਹਰੀ ਬਣਤਰ c_declarator *
c_parser_declarator (c_parser *parser, bool type_ਵੇਖਿਆ_p, c_dtr_syn ਕਿਸਮ,
		     bool *ਵੇਖਿਆ_id);
ਬਾਹਰੀ ਖਾਲੀ c_parser_declspecs (c_parser *, ਬਣਤਰ c_declspecs *, bool, bool,
				bool, bool, bool, bool, bool,
				ਗਿਣਤੀ c_lookahead_ਕਿਸਮ);
ਬਾਹਰੀ ਬਣਤਰ c_type_name *c_parser_type_name (c_parser *, bool = false);
ਬਾਹਰੀ bool c_maybe_parse_omp_decl (ਰੁੱਖ, ਰੁੱਖ);

#ਜੇ_ਅੰਤ
