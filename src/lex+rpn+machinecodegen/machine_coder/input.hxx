#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: input.hxx                   *
*                                                  (draft!) *
*************************************************************/

unsigned char* makeGetCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	if (!strncmp((*lastLexemInfoInTable)->lexemStr, "GET", MAX_LEXEM_SIZE)) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", "GET");
#endif

		const unsigned char code__mov_eax_stackTopByECX[] = { 0x8B, 0x01 };
		const unsigned char code__mov_edx_address[] = { 0xBA, 0x00, 0x00, 0x00, 0x00 };
		const unsigned char code__add_edx_esi[] = { 0x03, 0xD6 };
		const unsigned char code__push_ecx[] = { 0x51 };
		//const unsigned char code__push_ebx[] = { 0x53 };
		const unsigned char code__push_esi[] = { 0x56 };
		const unsigned char code__push_edi[] = { 0x57 };
		const unsigned char code__call_edx[] = { 0xFF, 0xD2 };
		const unsigned char code__pop_edi[] = { 0x5F };
		const unsigned char code__pop_esi[] = { 0x5E };
		//const unsigned char code__pop_ebx[] = { 0x5B };
		const unsigned char code__pop_ecx[] = { 0x59 };
		const unsigned char code__mov_ebx_valueByAdrressInECX[] = { 0x8B, 0x19 };
		const unsigned char code__sub_ecx_4[] = { 0x83, 0xE9, 0x04 };
		const unsigned char code__add_ebx_edi[] = { 0x33, 0xDF };
		const unsigned char code__mov_stackTopByEBX_eax[] = { 0x89, 0x03 };
		const unsigned char code__mov_ecx_edi[] = { 0x8B, 0xCF };
		const unsigned char code__add_ecx_512[] = { 0x81, 0xC1, 0x00, 0x02, 0x00, 0x00 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECX, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_edx_address, 5);
		*(unsigned int*)&(currBytePtr[-4]) = (unsigned int)getProcOffset;
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_edx_esi, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__push_ecx, 1);
		//currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__push_ebx, 1);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__push_esi, 1);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__push_edi, 1);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__call_edx, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__pop_edi, 1);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__pop_esi, 1);
		//currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__pop_ebx, 1);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__pop_ecx, 1);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_ebx_valueByAdrressInECX, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_ecx_4, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_ebx_edi, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_stackTopByEBX_eax, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_ecx_edi, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_ecx_512, 6);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    mov eax, dword ptr[ecx]\r\n");
		printf("    mov edx, 0%08Xh\r\n", (unsigned int)getProcOffset);
		printf("    add edx, esi\r\n");
		printf("    push ecx\r\n");
		printf("    ;push ebx\r\n");
		printf("    push esi\r\n");
		printf("    push edi\r\n");
		printf("    call edx\r\n");
		printf("    pop edi\r\n");
		printf("    pop esi\r\n");
		printf("    ;pop ebx\r\n");
		printf("    pop ecx\r\n");
		printf("    mov ebx, dword ptr[ecx]\r\n");
		printf("    sub ecx, 4\r\n");
		printf("    add ebx, edi\r\n");
		printf("    mov dword ptr [ebx], eax\r\n");
		printf("    mov ecx, edi ; reset second stack\r\n");
		printf("    add ecx, 512 ; reset second stack\r\n");
#endif

		return ++ * lastLexemInfoInTable, currBytePtr;
	}

	return currBytePtr;
}