#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: null_statement.hxx          *
*                                                  (draft!) *
*************************************************************/

#define NON_CONTEXT_NULL_STATEMENT(A, B, C)\
if (A ==* B) C = makeNullStatementAfterNonContextCode(B, C);

unsigned char* makeNullStatementAfterNonContextCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_NULL_STATEMENT);
	if (multitokenSize) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;null statement (non context)\r\n");
#endif

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}