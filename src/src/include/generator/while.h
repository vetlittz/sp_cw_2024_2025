#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: while.hxx                   *
*                                                  (draft!) *
*************************************************************/

#define WHILE_CODER(A, B, C, M, R)\
if (A ==* B) C = makeWhileCycleCode(B, C, M);\
if (A ==* B) C = makeNullStatementWhileCycleCode(B, C, M);\
if (A ==* B) C = makeContinueWhileCycleCode(B, C, M);\
if (A ==* B) C = makeExitWhileCycleCode(B, C, M);\
if (A ==* B) C = makeEndWhileAfterWhileCycleCode(B, C, M);

unsigned char* makeWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeNullStatementWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeContinueWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeExitWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeEndWhileAfterWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);