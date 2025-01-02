#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: repeat_until.hxx            *
*                                                  (draft!) *
*************************************************************/

#define REPEAT_UNTIL_CODER(A, B, C)\
if (A ==* B) C = makeRepeatCycleCode(B, C);\
if (A ==* B) C = makeUntileCode(B, C);\
if (A ==* B) C = makeNullStatementAfterUntilCycleCode(B, C);

unsigned char* makeRepeatCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_REPEAT);
	if (multitokenSize) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_REPEAT][0]);
#endif

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned long long int)currBytePtr;

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    LABEL@REPEAT_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
#endif

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeUntileCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) { // Or Ender!
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_UNTIL);
	if (multitokenSize
		&& lexemInfoTransformationTempStackSize
		&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_REPEAT][0], MAX_LEXEM_SIZE)
		) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;%s\r\n", tokenStruct[MULTI_TOKEN_UNTIL][0]);
#endif

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeNullStatementAfterUntilCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_NULL_STATEMENT);
	if (multitokenSize) {
		if (lexemInfoTransformationTempStackSize < 2
			|| strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_UNTIL][0], MAX_LEXEM_SIZE)
			|| strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_REPEAT][0], MAX_LEXEM_SIZE)
			) {
			return currBytePtr;
		}
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;after cond expresion (after \"%s\" after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_UNTIL][0], tokenStruct[MULTI_TOKEN_REPEAT][0]);
#endif	

		const unsigned char code__cmp_eax_0[]  = { 0x83, 0xF8, 0x00 };
		const unsigned char code__jnz_offset[] = { 0x0F, 0x85, 0x00, 0x00, 0x00, 0x00 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cmp_eax_0, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jnz_offset, 6);
		*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue - currBytePtr);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    cmp eax, 0\r\n");
		printf("    jnz LABEL@REPEAT_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr);
#endif

		lexemInfoTransformationTempStackSize -= 2;
		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}