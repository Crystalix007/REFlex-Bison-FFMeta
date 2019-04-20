/* Simply lexes arguments */
%top{
#include <stdexcept>
#include "parser.tab.hh"

using token = Grammar::Parser::token;
%}

%option debug
%option nodefault
%option noyywrap
%option c++
%option unicode
%option namespace="Grammar"
%option lexer="Scanner"
%option bison-cc-namespace="Grammar"
%option bison-cc-parser="Parser"
%option reentrant

%%

= {
	return token::ASSIGN;
}

^[\t ]*;[^\n]* {
	return token::COMMENT;
}

[\\]\n {
	return token::BACKSLASH;
}

[A-Za-z_]+ {
	yylval.build<std::string>(yytext);
	return token::AL_WORD;
}

[\t ]+ {
	yylval.build<std::string>(yytext);
	return token::SPACE;
}

\n {
	return token::NEWLINE;
}

. {
	yylval.build<std::string>(yytext);
	return token::CHARACTER;
}

%%
