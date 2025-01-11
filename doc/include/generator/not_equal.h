#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // lex + rpn + MACHINECODEGEN!  *
*                         file: not_equal.hxx               *
*                                                  (draft!) *
*************************************************************/

#define NOT_EQUAL_CODER(A, B, C, M, R)\
if (A ==* B) C = makeIsNotEqualCode(B, C, M);

unsigned char* makeIsNotEqualCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);