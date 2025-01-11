#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: bitwise_or.hxx              *
*                                                  (draft!) *
*************************************************************/

#define BITWISE_OR_CODER(A, B, C, M, R)\
if (A ==* B) C = makeBitwiseOrCode(B, C, M);

unsigned char* makeBitwiseOrCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);