#pragma once
// MyEnumeration.h

////////////////////////////////////////////////////////////////////////
/// TOKEN ENUMERATIONS
enum TOKENID
{
	// NULL token
	TOKEN_NULL = 0,
	// Logical Expression
	TOKEN_BREAK,
	TOKEN_CONTINUE,
	TOKEN_PRINT,
	TOKEN_LIST,
	TOKEN_APPE,
	// Loop tokens
	TOKEN_IF,
	TOKEN_ELIF,
	TOKEN_ELSE,
	TOKEN_WHILE,
	// Function calls
	TOKEN_INDENT,
	TOKEN_DEDENT,
	TOKEN_NEWLINE,
	TOKEN_EOF,
	// Logical expressions
	TOKEN_NOT,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_CHECKEQUAL,
	TOKEN_NCHECKEQUAL,
	TOKEN_BIGGER,
	TOKEN_BIGGEREQUAL,
	TOKEN_LOWER,
	TOKEN_LOWEREQUAL,
	// Immediate types
	TOKEN_IDENTIFIER,
	TOKEN_NUMBER,
	TOKEN_KEYWORD,
	TOKEN_TRUE,
	TOKEN_FALSE,
	TOKEN_STRING,
	TOKEN_CHAR,
	// Delimiters
	TOKEN_OPENPARAN,
	TOKEN_CLOSEPARAN,
	TOKEN_OPENCURBARAC,
	TOKEN_CLOSECURBARAC,
	TOKEN_OPENBARAC,
	TOKEN_CLOSEBARAC,
	// Opeartors
	TOKEN_EQUAL,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULTIPLICATION,
	TOKEN_DEVISION,
	TOKEN_MODULE,
	TOKEN_DOUBLE,
	TOKEN_EXPONENTIAL,
	TOKEN_FLOORDIVISION,
	// punctuationToks
	TOKEN_SEMICOLON,
	TOKON_DOUBLECOLON,
	TOKEN_COMMA,
	TOKEN_DOT,
};


////////////////////////////////////////////////////////////////////////
/// EXPRESSION ENUMERATION
enum
{
	// NULL Expression
	EXP_NUL,
	// Logical Expressions
	EXP_OR,
	EXP_AND,
	EXP_NOT,
	// Relation Expression
	EXP_EQU,
	EXP_NEQ,
	EXP_GRE,
	EXP_GEQ,
	EXP_LES,
	EXP_LEE,
	// Numerical Expression
	EXP_NEG,
	EXP_PLU,
	EXP_MIN,
	EXP_DIV,
	EXP_MUL,
	EXP_MOD,
	EXP_EPN,
	EXP_FLD,
	// Factor Expressions
	EXP_VAL,
	EXP_LOC
};


////////////////////////////////////////////////////////////////////////
/// VALUE EXPRESSION ENUMERATION
enum
{
	// Null value expression
	VAL_NDE,
	// Bool value expresssion
	VAL_BOO,
	// Integer value expression
	VAL_INT,
	// String value expression
	VAL_STR
};


////////////////////////////////////////////////////////////////////////
/// STATEMENT TYPE ENUMERATION
enum
{
	// Null Statement
	STA_NUL,
	// General Statements
	STA_BLO,
	STA_STA,
	// Simple Statements
	STA_SIM,
	STA_ASS,
	STA_LIS,
	STA_APP,
	STA_BRE,
	STA_CON,
	STA_PRI,
	// Compound Statements
	STA_COM,
	STA_IFF,
	STA_ELS,
	STA_WHI
};