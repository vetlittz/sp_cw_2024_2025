#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // lex + rpn + MACHINECODEGEN!  *
*                         file: if_then.h                   *
*                                                  (draft!) *
*************************************************************/

#define IF_THEN_CODER(A, B, C, M, R)\
if (A ==* B) C = makeIfCode(B, C, M);\
if (A ==* B) C = makeThenCode(B, C, M);\
if (A ==* B) C = makeSemicolonAfterThenCode(B, C, M);

unsigned char* makeIfCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeThenCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeSemicolonAfterThenCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);