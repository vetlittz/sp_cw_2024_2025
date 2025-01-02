#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: for.hxx                     *
*                                                  (draft!) *
*************************************************************/

#define FOR_CODER(A, B, C)\
if (A ==* B) C = makeForCycleCode(B, C);\
if (A ==* B) C = makeToOrDowntoCycleCode(B, C);\
if (A ==* B) C = makeDoCycleCode(B, C);\
if (A ==* B) C = makeSemicolonAfterForCycleCode(B, C);

unsigned char* makeForCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_FOR);
	if (multitokenSize) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_FOR][0]);
#endif

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeToOrDowntoCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) { // TODO: add assemblyBytePtr
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_DOWNTO);
	bool toMode = false;
	if (!multitokenSize) {
		toMode = !!(multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_TO));
	}
	if (multitokenSize
		&&
		lexemInfoTransformationTempStackSize
		&&
		!strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_FOR][0], MAX_LEXEM_SIZE)
		) {
		if (toMode) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
			printf("\r\n");
			printf("    ;\"%s\" (after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_TO][0], tokenStruct[MULTI_TOKEN_FOR][0]);
#endif
		}
		else {
#ifdef DEBUG_MODE_BY_ASSEMBLY
			printf("\r\n");
			printf("    ;\"%s\" (after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_DOWNTO][0], tokenStruct[MULTI_TOKEN_FOR][0]);
#endif		
		}

		const unsigned char code__dec_addrFromEBX[] = { 0xFF, 0x0B }; // dec dword ptr [ebx] // init
		const unsigned char code__inc_addrFromEBX[] = { 0xFF, 0x03 }; // inc dword ptr [ebx] // init
		const unsigned char code__push_ebx[]        = { 0x53 };       // push ebx	

		if (toMode) {
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__dec_addrFromEBX, 2); // init
		}
		else {
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__inc_addrFromEBX, 2); // init
		}
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__push_ebx, 1);

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned long long int)currBytePtr;

#ifdef DEBUG_MODE_BY_ASSEMBLY
		if (toMode) {
			printf("    dec dword ptr [ebx]\r\n"); // start from (index - 1)
		}
		else {
			printf("    inc dword ptr [ebx]\r\n"); // start from (index + 1)
		}
		printf("    push ebx\r\n");
		if (toMode) {
			printf("    LABEL@AFTER_TO_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
		}
		else {
			printf("    LABEL@AFTER_DOWNTO_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
		}
#endif

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeDoCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_DO);
	if (multitokenSize) {
		bool toMode = false;
		if (lexemInfoTransformationTempStackSize && !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_TO][0], MAX_LEXEM_SIZE)) {
			toMode = true;
		}
		else if (lexemInfoTransformationTempStackSize < 2
			|| strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_DOWNTO][0], MAX_LEXEM_SIZE)
			|| strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_FOR][0], MAX_LEXEM_SIZE)
			) {
			return currBytePtr;
		}
		if (toMode) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
			printf("\r\n");
			printf("    ;\"%s\" (after \"%s\" after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_DO][0], tokenStruct[MULTI_TOKEN_TO][0], tokenStruct[MULTI_TOKEN_FOR][0]);
#endif	
		}
		else {
#ifdef DEBUG_MODE_BY_ASSEMBLY
			printf("\r\n");
			printf("    ;\"%s\" (after \"%s\" after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_DO][0], tokenStruct[MULTI_TOKEN_DOWNTO][0], tokenStruct[MULTI_TOKEN_FOR][0]);
#endif		
		}

		const unsigned char code__mov_ebx_addrFromESP[] = { 0x8B, 0x1C, 0x24 };                   // mov ebx, dword ptr [esp]
		const unsigned char code__cmp_addrFromEBX_eax[] = { 0x39, 0x03 };                         // cmp dword ptr [ebx], eax
		const unsigned char code__jge_offset[]          = { 0x0F, 0x8D, 0x00, 0x00, 0x00, 0x00 }; // jge ?? ?? ?? ??
		const unsigned char code__jle_offset[]          = { 0x0F, 0x8E, 0x00, 0x00, 0x00, 0x00 }; // jle ?? ?? ?? ??
		const unsigned char code__inc_addrFromEBX[]     = { 0xFF, 0x03 };                         // inc dword ptr [ebx]
		const unsigned char code__dec_addrFromEBX[]     = { 0xFF, 0x0B };                         // dec dword ptr [ebx]

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_ebx_addrFromESP, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cmp_addrFromEBX_eax, 2);
		if (toMode) {
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jge_offset, 6);
			lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned long long int)(currBytePtr - 4);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__inc_addrFromEBX, 2);
		}
		else {
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jle_offset, 6);
			lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned long long int)(currBytePtr - 4);
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__dec_addrFromEBX, 2);
		}

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    mov ebx, dword ptr [esp]\r\n");
		printf("    cmp dword ptr [ebx], eax\r\n");
		if (toMode) {
			printf("    jge LABEL@EXIT_FOR_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr);
			printf("    inc dword ptr [ebx]\r\n");
		}
		else {
			printf("    jle LABEL@EXIT_FOR_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr);
			printf("    dec dword ptr [ebx]\r\n");
		}
#endif

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makePostForCode_(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, bool toMode) {
	const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
	const unsigned char code__add_esp_4[] = { 0x83, 0xC4, 0x04 };

	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
	*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue - currBytePtr);
	*(unsigned int*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned int)(currBytePtr - (unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue - 4);
	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_esp_4, 3);

#ifdef DEBUG_MODE_BY_ASSEMBLY
	if (toMode) {
		printf("    jmp LABEL@AFTER_TO_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
	}
	else {
		printf("    jmp LABEL@AFTER_DOWNTO_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
	}
	printf("    LABEL@EXIT_FOR_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr);
	printf("    add esp, 4; add esp, 8\r\n");
#endif

	return currBytePtr;
}

unsigned char* makeSemicolonAfterForCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) { // Or Ender!
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_SEMICOLON);
	bool toMode = false;
	if (multitokenSize
		&&
		lexemInfoTransformationTempStackSize > 1
		&&
		!strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_FOR][0], MAX_LEXEM_SIZE)
		&& (
			!strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_DOWNTO][0], MAX_LEXEM_SIZE)
			||
			(toMode = !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_TO][0], MAX_LEXEM_SIZE))
			)
		) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\" (after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_SEMICOLON][0], tokenStruct[MULTI_TOKEN_FOR][0]);
#endif

		currBytePtr = makePostForCode_(lastLexemInfoInTable, currBytePtr, toMode);

		lexemInfoTransformationTempStackSize -= 2;
		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}