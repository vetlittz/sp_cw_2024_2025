#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: mul.hxx                     *
*                                                  (draft!) *
*************************************************************/

#define MUL_CODER(A, B, C, M, R)\
if (A ==* B) C = makeMulCode(B, C, M);

unsigned char* makeMulCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);