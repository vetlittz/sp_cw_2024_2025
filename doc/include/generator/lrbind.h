#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lrbind codegen                    *
*                         file: lrbind.hxx                  *
*                                                  (draft!) *
*************************************************************/

#define LRBIND_CODER(A, B, C, M, R)\
if (A ==* B) C = makeLeftToRightBindCode(B, C, M);

unsigned char* makeLeftToRightBindCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);