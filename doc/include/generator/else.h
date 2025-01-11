#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: else.hxx                    *
*                                                  (draft!) *
*************************************************************/

#define ELSE_CODER(A, B, C, M, R)\
if (A ==* B) C = makeElseCode(B, C, M);\
if (A ==* B) C = makeSemicolonAfterElseCode(B, C, M);

unsigned char* makeElseCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);
unsigned char* makeSemicolonAfterElseCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);