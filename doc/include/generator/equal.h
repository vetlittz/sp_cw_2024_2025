#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // lex + rpn + MACHINECODEGEN!  *
*                         file: equal.h                     *
*                                                  (draft!) *
*************************************************************/

#define EQUAL_CODER(A, B, C, M, R)\
if (A ==* B) C = makeIsEqualCode(B, C, M);

unsigned char* makeIsEqualCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);