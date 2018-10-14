/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SIMPLE_TAB_H_INCLUDED
# define YY_YY_SIMPLE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    IDENTIFIER = 259,
    IF = 260,
    WHILE = 261,
    SWITCH = 262,
    FOR = 263,
    DO = 264,
    SKIP = 265,
    THEN = 266,
    ELSE = 267,
    FI = 268,
    END = 269,
    VAR = 270,
    VAL = 271,
    FUNCTION = 272,
    NAN = 273,
    INFINITY = 274,
    _NULL = 275,
    _TRUE = 276,
    _FALSE = 277,
    RETURN = 278,
    YIELD = 279,
    CONTINUE = 280,
    BREAK = 281,
    _GOTO = 282,
    CASE = 283,
    DEFAULT = 284,
    CATCH = 285,
    TRY = 286,
    FINALLY = 287,
    THROW = 288,
    PACKAGE = 289,
    IMPORT = 290,
    SUPER = 291,
    THIS = 292,
    NEW = 293,
    INTERFACE = 294,
    IMPLEMENTS = 295,
    PUBLIC = 296,
    PRIVATE = 297,
    PROTECTED = 298,
    CONSOLE = 299,
    INTEGER = 300,
    READ = 301,
    WRITE = 302,
    LET = 303,
    IN = 304,
    ASSGNOP = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
#line 56 "Simple.y" /* yacc.c:1909  */
union semrec
{
#line 57 "Simple.y" /* yacc.c:1909  */

int  intval;                 /* Integer values      */
char *id;                    /* Identifiers         */
struct lbs *lbls;            /* For backpatching    */

#line 111 "Simple.tab.h" /* yacc.c:1909  */
};
#line 56 "Simple.y" /* yacc.c:1909  */
typedef union semrec YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SIMPLE_TAB_H_INCLUDED  */
