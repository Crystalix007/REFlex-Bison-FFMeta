/* Parses an argument specification */
%skeleton "lalr1.cc"
%require "3.2"
%debug
%defines
%define api.namespace {Grammar}
%define api.parser.class {Parser}

%code requires{
	namespace Grammar {
		class Driver;
		class Scanner;
	}

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif
}

%parse-param { Scanner& scanner  }
%parse-param { Driver& driver }

%code {
	#include <string>
	#include <map>
	#include <utility>

	#include "driver.hpp"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token							 ASSIGN
%token 							 BACKSLASH
%token 							 COMMENT
%token 							 NEWLINE
%token <std::string> AL_WORD
%token <std::string> WORD
%token <std::string> SPACE
%token <std::string> CHARACTER

%type <std::string> TEXT

%start TAGS

%%

TEXT
	: %empty {
			$$ = std::string{};
		}
	| BACKSLASH TEXT {
			$$ = std::string{ "<br />" } + $2;
		}
	| AL_WORD TEXT {
			$$ = $1 + $2;
		}
	| SPACE TEXT {
			$$ = $1 + $2;
		}
	| CHARACTER TEXT {
			$$ = $1 + $2;
		}
	;

TAG
	: AL_WORD ASSIGN TEXT { driver.addTag($1, $3); }
	;

TAGS
	: %empty
	| TAG NEWLINE TAGS
	| COMMENT NEWLINE TAGS
	;

%%

void Grammar::Parser::error(const std::string& err_message)
{
	std::cerr << "Error: " << err_message << '\n';
}
