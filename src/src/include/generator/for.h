#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: for.h                       *
*                                                  (draft!) *
*************************************************************/

#define FOR_CODER(A, B, C, M, R)\
if (A ==* B) C = makeForCycleCode(B, C, M);\
if (A ==* B) C = makeToOrDowntoCycleCode(B, C, M);\
if (A ==* B) C = makeDoCycleCode(B, C, M);\
if (A ==* B) C = makeSemicolonAfterForCycleCode(B, C, M);

unsigned char* makeForCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeToOrDowntoCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeDoCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeSemicolonAfterForCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);