%{/*************************************************************************
Compiler for the Simple language
***************************************************************************/
/*=========================================================================
C Libraries, Symbol Table, Code Generator & other C code
=========================================================================*/
#include <stdio.h>  /* For I/O                             */
#include <stdlib.h> /* For malloc here and in symbol table */
#include <string.h> /* For strcmp in symbol table          */
#include "ST.h"     /* Symbol Table                        */
#define YYDEBUG 1   /* For Debugging                       */
int errors;         /* Error Count                         */
Env* current_Env = init_new_Env();
/*=========================================================================
SEMANTIC RECORDS
=========================================================================*/
%}
%union semrec                /* The Semantic Records*/
{                
char*  id;                    /* Identifiers         */
literal* literal_value;
}
/*=========================================================================
TOKENS
=========================================================================*/
%start program
%token <id>     IDENTIFIER   /* Simple identifier   */
%token <lbls>   IF WHILE SWITCH FOR DO    /* For backpatching labels*/
%token <literal> LITERAL //直接量
%token SKIP THEN ELSE FI END 
       VAR      //定义变量　var name={}|[]|
       VAL      //定义常量
       FUNCTION //定义函数
       NAN      //
       INFINITY //
       _NULL    //
       _TRUE    //
       _FALSE   //
       RETURN YIELD CONTINUE BREAK GOTO CASE DEFAULT //控制语句
       CATCH TRY FINALLY THROW //异常控制流
       PACKAGE IMPORT //包管理系统
       SUPER //基类构造函数
       THIS //对象本身引用
       NEW //
       INTERFACE IMPLEMENTS //接口
       PUBLIC PRIVATE PROTECTED //访问控制
       CONSOLE //控制台IO
%token INTEGER READ WRITE LET IN  
%token ASSGNOP
/*=========================================================================
OPERATOR PRECEDENCE
=========================================================================*/
%left '.' '[' ']' "new" '(' ')'
%left "++" "--"
%right '!' '~'
%nonassoc "typeof" "delete" 
%right "**"
%left '*' '/' '%'
%left '+' '-'
%left ">>" "<<" ">>>"
%nonassoc '>' '<' "<=" ">="
          "in" /*"instanceof"*/
%nonassoc "==" "===" "!=" "!=="
%left '&' '|' '^' "||" "&&"
%right  '?' ':'
%nonassoc '=' "+=" "-=" "*=" "/=" "%="
       "<<=" ">>=" ">>>="
       "&=" "^=" "|="
/*=========================================================================
GRAMMAR RULES for the Simple language
=========================================================================*/
%%
program :  stmts          
;
declaration : /* empty */
            | VAR  ID__or_assign ';' { install( $2 );               }
            | VAL ID__with_assign ';' {  }
            | function_declaration 
;
ID__or_assign : /* empty */
              | IDENTIFIER '=' right_value {   } 
              | IDENTIFIER { }
              | ID_or_assign ',' ID_or_assign {      }
;
ID__with_assign : IDENTIFIER '=' right_value { } 
                | ID_or_assign ',' ID_or_assign {       }
;
right_value : IDENTIFIER { }
            | '[' array ']'  { }
            | '{' object '}' { }
            | FUNCTION '(' function_params ')' '{' function_body '}'
            | LITERAL { } 
;
array : /* empty */
      | array_not_empty
;
array_not_empty : right_value { }
                | array ',' right_value { }
;
object : /* empty */
       | object_not_empty
;
object_not_empty : IDENTIFIER ':' right_value { }
                 | object ',' IDENTIFIER ':' right_value { }
function_params : /* empty */
                | function_params_not_empty
;
function_params_not_empty : IDENTIFIER
                function_params_not_empty ',' IDENTIFIER
                ;          | 
function_declaration : FUNCTION IDENTIFIER '(' function_params ')''{' function_body '}'
function_body : /* empty */
              | stmts 
              | stmts return_stmt ';'
;
return_stmt : "return;"
            |"return" exp ';'
;
not_if_stmt : /* empty */
            | declaration
            | while_stmt
            | do_stmt
            | for_stmt
            | switch_stmt
            | out_stmt
            | assign_stmt
            | function_call_stmt
;
out_stmt :  CONSOLE "<<" exp {  } ;

in_stmt  :  CONSOLE ">>" left_value  {  }

assign_stmt : /* empty */
            | left_value '=' exp {  }
            | in_stmt 
            | left_value "+=" exp
            | left_value "-=" exp
            | left_value "*=" exp
            | left_value "/=" exp
            | left_value "%=" exp
            | left_value ">>=" exp
            | left_value "<<=" exp
            | left_value ">>>=" exp
            | left_value "&=" exp
            | left_value "|=" exp
            | left_value "^=" exp
            | "++" left_value
            | "--" left_value
            | left_value "++"
            | left_value "--"
;
left_value : IDENTIFIER
           | left_value '[' exp ']'
           | left_value '.' IDENTIFIER
;
stmts : /* empty */
      | stmts stmt { }
;
stmt : 
     | '{' stmts '}'
     | if_matched_stmt 
     | if_open_stmt ;
if_open_stmt : IF '(' bool_exp ')' stmt
             | IF '(' bool_exp ')' if_matched_stmt  
               ELSE if_open_stmt ; 
if_matched_stmt : IF  '(' bool_exp ')' if_matched_stmt ELSE if_matched_stmt
                | not_if_stmt    ;
bool_exp: '!' bool_exp 
        | '(' boo_exp_or ')'
        | _TRUE
        | _FALSE
        | bool_stmt
;
boo_exp_or : boo_exp_or "||" bool_exp_and 
           | bool_exp_and ;
bool_exp_and : bool_exp_and "&&" 
             | bool_exp ;
bool_stmt : left_value  "<"   left_value
          | left_value  "<="  left_value
          | left_value  "=="  left_value
          | left_value  "!="  left_value
          | left_value  "===" left_value
          | left_value  "!==" left_value
          | left_value  ">"   left_value
          | left_value  ">="  left_value
          | IDENTIFIER   "in" left_value
exp : LITERAL             {      }
| IDENTIFIER              { }
| exp '+' exp             {          }
| exp '-' exp             {         }
| exp '*' exp             {      }
| exp '/' exp             {       }
| exp '^' exp             {                             }
| '(' exp ')'             { $$ = $2;                    }
| '-' exp %prec           { $$= -$2;                    }
| typeof_exp
;
typeof_exp : TYPEOF left_value
%%
/*=========================================================================
MAIN
=========================================================================*/
main( int argc, char *argv[] )
{ extern FILE *yyin;
++argv; --argc;
yyin = fopen( argv[0], "r" );
/*yydebug = 1;*/
errors = 0;
yyparse ();
printf ( "Parse Completed\n" );
if ( errors == 0 )
{ 
}
}
/*=========================================================================
YYERROR
=========================================================================*/
yyerror ( char *s ) /* Called by yyparse on error */
{
errors++;
printf ("%s\n", s);
}
/**************************** End Grammar File ***************************/
