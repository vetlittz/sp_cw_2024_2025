#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: null_statement.hxx          *
*                                                  (draft!) *
*************************************************************/

#define NON_CONTEXT_NULL_STATEMENT(A, B, C, M, R)\
if (A ==* B) C = makeNullStatementAfterNonContextCode(B, C, M);

unsigned char* makeNullStatementAfterNonContextCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);