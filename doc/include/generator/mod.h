#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: mod.hxx                     *
*                                                  (draft!) *
*************************************************************/

#define MOD_CODER(A, B, C, M, R)\
if (A ==* B) C = makeModCode(B, C, M);

unsigned char* makeModCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);