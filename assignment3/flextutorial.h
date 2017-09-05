/*
 * A header file containing an enum. yylex() returns an integer,
 * this enum allows the source code to have descriptive names
 * for tokens instead of numbers.
 *     Author: Boris Gorshenev <bgorshen@ucsc.edu>
 */


# ifndef FLEXTUTORIAL_H
# define FLEXTUTORIAL_H
enum tokens {TOKEN_INVALID, TOKEN_WORD, TOKEN_NUMBER, TOKEN_SPACE, TOKEN_NEWLINE, TOKEN_PUNCTUATION, TOKEN_EOF};
# endif

# define YY_NO_INPUT
