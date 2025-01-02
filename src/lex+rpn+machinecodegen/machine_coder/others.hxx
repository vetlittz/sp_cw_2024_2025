#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: others.cpp                  *
*                                                  (draft!) *
*************************************************************/

#define ________CODER(A, B, C)\
if (A ==* B) C = makeIfCode(B, C);\
if (A ==* B) C = makeThenCode(B, C);\
if (A ==* B) C = makeSemicolonAfterThenCode(B, C);

unsigned char* makeNotCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	if (!strncmp((*lastLexemInfoInTable)->lexemStr, "NOT", MAX_LEXEM_SIZE)) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", "NOT");
#endif

		const unsigned char code__not_stackTopByECX[] = { 0xF7, 0x11 };
		const unsigned char code__mov_eax_stackTopByECX[] = { 0x8B, 0x01 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__not_stackTopByECX, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECX, 3);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    not dword ptr[ecx]\r\n");
		printf("    mov eax, dword ptr[ecx]\r\n");
#endif

		return ++ * lastLexemInfoInTable, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeAddCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	if (!strncmp((*lastLexemInfoInTable)->lexemStr, "+", MAX_LEXEM_SIZE)) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", "+");
#endif

		const unsigned char code__mov_eax_stackTopByECX[] = { 0x8B, 0x01 };
		const unsigned char code__sub_ecx_4[] = { 0x83, 0xE9, 0x04 };
		const unsigned char code__add_stackTopByECX_eax[] = { 0x01, 0x01 };
		//const unsigned char code__mov_eax_stackTopByECX[] = { 0x8B, 0x01 };       

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECX, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_ecx_4, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_stackTopByECX_eax, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECX, 2);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    mov eax, dword ptr[ecx]\r\n");
		printf("    sub ecx, 4\r\n");
		printf("    add dword ptr[ecx], eax\r\n");
		printf("    mov eax, dword ptr[ecx]\r\n");
#endif

		return ++ * lastLexemInfoInTable, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeSubCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	if (!strncmp((*lastLexemInfoInTable)->lexemStr, "-", MAX_LEXEM_SIZE)) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", "-");
#endif

		const unsigned char code__mov_eax_stackTopByECX[] = { 0x8B, 0x01 };
		const unsigned char code__sub_ecx_4[] = { 0x83, 0xE9, 0x04 };
		const unsigned char code__sub_stackTopByECX_eax[] = { 0x29, 0x01 };
		//const unsigned char code__mov_eax_stackTopByECX[] = { 0x8B, 0x01 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECX, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_ecx_4, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_stackTopByECX_eax, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECX, 2);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    mov eax, dword ptr[ecx]\r\n");
		printf("    sub ecx, 4\r\n");
		printf("    sub dword ptr[ecx], eax\r\n");
		printf("    mov eax, dword ptr[ecx]\r\n");
#endif

		return ++ * lastLexemInfoInTable, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeMulCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	if (!strncmp((*lastLexemInfoInTable)->lexemStr, "*", MAX_LEXEM_SIZE)) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", "*");
#endif

		const unsigned char code__mov_eax_stackTopByECXMinus4[] = { 0x8B, 0x41, 0xFC };
		const unsigned char code__imul_stackTopByECX[] = { 0xF7, 0x29 };
		const unsigned char code__sub_ecx_4[] = { 0x83, 0xE9, 0x04 };
		const unsigned char code__mov_toAddrFromECX_eax[] = { 0x89, 0x01 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECXMinus4, 3);
		//currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cdq, 1);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__imul_stackTopByECX, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_ecx_4, 3);
		//currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__push_eax, 1);
		//currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__dec_ebp, 1);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_toAddrFromECX_eax, 2);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    mov eax, dword ptr[ecx - 4]\r\n");
		printf("    ;cdq\r\n");
		printf("    imul dword ptr [ecx]\r\n");
		printf("    sub ecx, 4\r\n");
		printf("    mov dword ptr [ecx], eax\r\n");
#endif

		return ++ * lastLexemInfoInTable, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeDivCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	if (!strncmp((*lastLexemInfoInTable)->lexemStr, "DIV", MAX_LEXEM_SIZE)) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", "DIV");
#endif

		const unsigned char code__mov_eax_stackTopByECXMinus4[] = { 0x8B, 0x41, 0xFC };
		const unsigned char code__cdq[] = { 0x99 };
		const unsigned char code__idiv_stackTopByECX[] = { 0xF7, 0x39 };
		const unsigned char code__sub_ecx_4[] = { 0x83, 0xE9, 0x04 };
		const unsigned char code__mov_toAddrFromECX_eax[] = { 0x89, 0x01 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECXMinus4, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cdq, 1);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__idiv_stackTopByECX, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_ecx_4, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_toAddrFromECX_eax, 2);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    mov eax, dword ptr[ecx - 4]\r\n");
		printf("    cdq\r\n");
		printf("    idiv dword ptr [ecx]\r\n");
		printf("    sub ecx, 4\r\n");
		printf("    mov dword ptr [ecx], eax\r\n");
#endif

		return ++ * lastLexemInfoInTable, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeModCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) { // task
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_MOD);
	if (multitokenSize) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_MOD][0]);
#endif

		const unsigned char code__mov_eax_stackTopByECXMinus4[] = { 0x8B, 0x41, 0xFC }; // mov eax, dword ptr[ecx - 4]
		const unsigned char code__cdq[] = { 0x99 };             // cdq
		const unsigned char code__idiv_stackTopByECX[] = { 0xF7, 0x39 };       // idiv dword ptr [ecx]
		const unsigned char code__sub_ecx_4[] = { 0x83, 0xE9, 0x04 }; // sub ecx, 4
		const unsigned char code__mov_eax_edx[] = { 0x8B, 0xC2 };       // mov eax, edx
		const unsigned char code__mov_toAddrFromECX_eax[] = { 0x89, 0x01 };       // mov dword ptr [ecx], eax

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECXMinus4, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cdq, 1);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__idiv_stackTopByECX, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_ecx_4, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_edx, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_toAddrFromECX_eax, 2);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    mov eax, dword ptr[ecx - 4]\r\n");
		printf("    cdq\r\n");
		printf("    idiv dword ptr [ecx]\r\n");
		printf("    sub ecx, 4\r\n");
		printf("    mov eax, edx\r\n");
		printf("    mov dword ptr [ecx], eax\r\n");
#endif

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeSemicolonAfterNonContextCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_SEMICOLON);
	if (multitokenSize
		&&
		!lexemInfoTransformationTempStackSize // !
		) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", ";");
#endif

		* lastLexemInfoInTable += multitokenSize;
	}

	return currBytePtr;
}