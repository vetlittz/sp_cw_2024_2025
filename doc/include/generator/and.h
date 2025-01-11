#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: and.hxx                     *
*                                                  (draft!) *
*************************************************************/

#define AND_CODER(A, B, C, M, R)\
if (A ==* B) C = makeAndCode(B, C, M);

unsigned char* makeAndCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);