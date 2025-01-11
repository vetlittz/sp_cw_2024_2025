#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: sub.hxx                     *
*                                                  (draft!) *
*************************************************************/

#define SUB_CODER(A, B, C, M, R)\
if (A ==* B) C = makeSubCode(B, C, M);

unsigned char* makeSubCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);