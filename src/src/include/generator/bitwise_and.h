#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: bitwise_and.hxx             *
*                                                  (draft!) *
*************************************************************/

#define BITWISE_AND_CODER(A, B, C, M, R)\
if (A ==* B) C = makeBitwiseAndCode(B, C, M);

unsigned char* makeBitwiseAndCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);