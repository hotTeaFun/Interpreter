/***************************************************************************
Scanner for the Simple language
***************************************************************************/
%{
/*=========================================================================
C-libraries and Token definitions
=========================================================================*/
#include <string.h>        /* for strdup                       */
/*#include <stdlib.h> */   /* for atoi                         */
#include "Simple.tab.h"    /* for token definitions and yylval */
%}
/*=========================================================================
Token definitions
=========================================================================*/
decimal_constant   [[:digit:]]*
hexadecimal_constant [Oo][xX][[:xdigit:]]+
octal_constant [Oo][0-7]*
dseq      ([[:digit:]]+)
dseq_opt  ([[:digit:]]*)
frac      (({dseq_opt}"."{dseq})|{dseq}".")
_exp       ([eE][+-]?{dseq})
exp_opt   ({_exp}?)
fsuff     [flFL]
fsuff_opt ({fsuff}?)
hpref     (0[xX])
hdseq     ([[:xdigit:]]+)
hdseq_opt ([[:xdigit:]]*)
hfrac     (({hdseq_opt}"."{hdseq})|({hdseq}"."))
bexp      ([pP][+-]?{dseq})
dfc       (({frac}{exp_opt}{fsuff_opt})|({dseq}{exp}{fsuff_opt}))
hfc       (({hpref}{hfrac}{bexp}{fsuff_opt})|({hpref}{hdseq}{bexp}{fsuff_opt}))
c99_floating_point_constant  ({dfc}|{hfc})
ucn        ((\\u([[:xdigit:]]{4}))|(\\U([[:xdigit:]]{8})))
nondigit    [_[:alpha:]]
c99_id     ([_[:alpha:]]|{ucn})([_[:alnum:]]|{ucn})*
ID      [a-z][a-z0-9]*
%x COMMENT
/*=========================================================================
REGULAR EXPRESSIONS defining the tokens for the Simple language
=========================================================================*/
%%
do       { return(DO);      }
else     { return(ELSE);    }
if       { return(IF);      }
var      { return(VAR);     }
val      { return(VAl);     }
console  { return(CONSOLE); }
switch   { return(SWITCH);  }
case     { return(case);    }
default  { return(DEFALUT); }
continue { return(CONTINUE);}
break    { return(BREAK);   }
while    { return(WHILE);   }
for      { return(FOR);     }
function { return(FUNCTION);}
NAN      { return(NAN);     }
return   { return(RETURN);  }
yield    { return(YIELD);   }
true     { return(_TRUE);   }
false    { return(_FALSE);  }
NULL     { return(_NULL);   }
INFINITY { return(INFINITY);}
try      { return(TRY);     }
catch    { return(CATCH);   }
throw    { return(THROW);   }
finally  { return(FINALLY); }
import   { return(IMPORT);  }
package  { return(PACKAGE); }
super    { return(SUPER);   }
this     { return(THIS);    }
new      { return(NEW);     }
interface { return(INTERFACE); }
implement { return(IMPLEMENT); }
public    { return(PUBLIC);    }
private   { return(PRIVATE);   }
protected { return(PROTECTED); }
{DIGIT}+ { (*yylval.litreal).flag=_int; (*yylval.litreal).string_value =(char *) strdup(yytext);
           return(LITERAL);  }
{c99_id}     { yylval.id = (char *) strdup(yytext);
               return(IDENTIFIER);    }
[ \t\n]+ /* eat up whitespace */
"\""   
"/*"  { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>([^*]|\n)+|.
<COMMENT><<EOF>> { printf("%d: Unterminated comment\n",yylineno); return 0; }
"//".*\n /* ignore comment */

.        { return(yytext[0]);     }
%%
int yywrap(void){}
/************************** End Scanner File *****************************/
