#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lrbind codegen                    *
*                         file: rlbind.hxx                  *
*                                                  (draft!) *
*************************************************************/

#define RLBIND_CODER(A, B, C, M, R)\
if (A ==* B) C = makeRightToLeftBindCode(B, C, M);

unsigned char* makeRightToLeftBindCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);