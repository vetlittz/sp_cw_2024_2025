#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: add.hxx                     *
*                                                  (draft!) *
*************************************************************/

#define ADD_CODER(A, B, C, M, R)\
if (A ==* B) C = makeAddCode(B, C, M);

unsigned char* makeAddCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);