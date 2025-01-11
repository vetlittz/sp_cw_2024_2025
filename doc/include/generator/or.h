#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: or.hxx                      *
*                                                  (draft!) *
*************************************************************/

#define OR_CODER(A, B, C, M, R)\
if (A ==* B) C = makeOrCode(B, C, M);

unsigned char* makeOrCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);