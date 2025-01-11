#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: less_or_equal.h             *
*                                                  (draft!) *
*************************************************************/

#define LESS_OR_EQUAL_CODER(A, B, C, M, R)\
if (A ==* B) C = makeIsLessOrEqualCode(B, C, M);

unsigned char* makeIsLessOrEqualCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);