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

#که_نه_تعریف_شوی GCC_C_PARSER_H
#تعریف_کړه GCC_C_PARSER_H

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
تعداد c_id_ډول {
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
بنية GTY (()) c_token {
  /* The kind of token.  */
  تعداد cpp_ttype type : 8;
  /* If this token is a CPP_NAME, this value indicates whether also
     declared as some kind of type.  Otherwise, it is C_ID_NONE.  */
  تعداد c_id_ډول id_ډول : 8;
  /* If this token is a keyword, this value indicates which keyword.
     Otherwise, this value is RID_MAX.  */
  تعداد rid keyword : 8;
  /* If this token is a CPP_PRAGMA, this indicates the pragma that
     was seen.  Otherwise it is PRAGMA_NONE.  */
  تعداد pragma_ډول pragma_ډول : 8;
  /* The location at which this token was found.  */
  location_t location;
  /* The value associated with this token, if any.  */
  ونه ارزښت;
  /* Token flags.  */
  بینښه حرف flags;

  سرچینه_range get_range () ثابت
  {
    أرجع get_range_from_loc (کرښه_جدول, location);
  }

  location_t get_پای () ثابت
  {
    أرجع get_range ().m_پای;
  }
};

/* This should have the same layout as c_tree_token_vec
   in c-decl.cc, but for GTY reasons with ObjC can't be
   GTY itself.  */
بنية c_ونه_token_vec_struct {
  بنية ونه_بنسټ بنسټ;
  vec<c_token, va_gc> *نښې;
};

#تعریف_کړه C_TOKEN_VEC_نښې(غوټه_2) \
  (((بنية c_ونه_token_vec_struct *) ونه_CHECK (غوټه_2, C_TOKEN_VEC))->نښې)

/* The parser.  */
بنية c_parser;

/* Possibly kinds of declarator to parse.  */
تعداد c_dtr_syn {
  /* A normal declarator with an identifier.  */
  C_DTR_نورمال,
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
تعداد c_parser_prec {
  PREC_NONE,
  PREC_LOGOR,
  PREC_LOGAND,
  PREC_BITOR,
  PREC_BITXOR,
  PREC_BITAND,
  PREC_EQ,
  PREC_REL,
  PREC_ښويدنه,
  PREC_جمع_کړه,
  PREC_MULT,
  عدد_PRECS
};

تعداد c_lookahead_ډول {
  /* Always treat unknown identifiers as typenames.  */
  cla_prefer_type,

  /* Could be parsing a nonabstract declarator.  Only treat an identifier
     as a typename if followed by another identifier or a star.  */
  cla_nonabstract_decl,

  /* Never treat identifiers as typenames.  */
  cla_prefer_id
};


خارجي c_token * c_parser_peek_token (c_parser *parser);
خارجي c_token * c_parser_peek_2nd_token (c_parser *parser);
خارجي c_token * c_parser_peek_nth_token (c_parser *parser, بینښه صحيح n);
خارجي bool c_parser_require (c_parser *parser, تعداد cpp_ttype type,
			      ثابت حرف *msgid,
			      location_t matching_location = UNKNOWN_LOCATION,
			      bool type_is_unique=true);
خارجي bool c_parser_error (c_parser *parser, ثابت حرف *gmsgid);
خارجي فراغ c_parser_consume_token (c_parser *parser);
خارجي فراغ c_parser_skip_until_وموندل (c_parser *parser, تعداد cpp_ttype type,
				       ثابت حرف *msgid,
				       location_t = UNKNOWN_LOCATION);
خارجي bool c_parser_بل_token_starts_declspecs (c_parser *parser);
bool c_parser_بل_نښې_پیل_declaration (c_parser *parser,
					     بینښه صحيح n = 1);
bool c_token_starts_typename (c_token *token);

/* Abstraction to avoid defining c_parser here which messes up gengtype
   output wrt ObjC due to vec<c_token> routines being put in gtype-c.h
   but not gtype-objc.h.  */
خارجي c_token * c_parser_نښې_buf (c_parser *parser, بینښه n);
خارجي bool c_parser_error (c_parser *parser);
خارجي فراغ c_parser_سېټ_error (c_parser *parser, bool);

/* A bit of a hack to have this here.  It would be better in a c-decl.h.  */
خارجي bool old_style_parameter_scope (فراغ);

/* Return true if the next token from PARSER has the indicated
   TYPE.  */

مضمن bool
c_parser_بل_token_is (c_parser *parser, تعداد cpp_ttype type)
{
  أرجع c_parser_peek_token (parser)->type == type;
}

/* Return true if the next token from PARSER does not have the
   indicated TYPE.  */

مضمن bool
c_parser_بل_token_is_not (c_parser *parser, تعداد cpp_ttype type)
{
  أرجع !c_parser_بل_token_is (parser, type);
}

/* Return true if the next token from PARSER is the indicated
   KEYWORD.  */

مضمن bool
c_parser_بل_token_is_keyword (c_parser *parser, تعداد rid keyword)
{
  أرجع c_parser_peek_token (parser)->keyword == keyword;
}

بنية c_بیان c_parser_string_literal (c_parser *, bool, bool);
خارجي بنية c_declarator *
c_parser_declarator (c_parser *parser, bool type_کتل_شوی_p, c_dtr_syn ډول,
		     bool *کتل_شوی_id);
خارجي فراغ c_parser_declspecs (c_parser *, بنية c_declspecs *, bool, bool,
				bool, bool, bool, bool, bool,
				تعداد c_lookahead_ډول);
خارجي بنية c_type_name *c_parser_type_name (c_parser *, bool = false);
خارجي bool c_maybe_parse_omp_decl (ونه, ونه);

#د_که_پای
