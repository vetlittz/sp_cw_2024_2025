#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: input.h                     *
*                                                  (draft!) *
*************************************************************/

#define INPUT_CODER(A, B, C, M, R)\
if (A ==* B) C = makeGetCode(B, C, M);

unsigned char* makeGetCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);