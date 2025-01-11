#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: while.cpp                   *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"
#include "string.h"

unsigned char* makeWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_WHILE);
	if (multitokenSize) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
#endif

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned long long int)currBytePtr;

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    LABEL@WHILE_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr);
#endif

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeNullStatementWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_NULL_STATEMENT);
	if (multitokenSize) {
		if (lexemInfoTransformationTempStackSize < 2
			|| strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			|| strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			|| lexemInfoTransformationTempStackSize >= 4 && !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			|| lexemInfoTransformationTempStackSize >= 3 && !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {
			return currBytePtr;
		}
#ifdef DEBUG_MODE_BY_ASSEMBLY
			printf("\r\n");
			printf("    ;after cond expresion (after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
#endif	

		const unsigned char code__cmp_eax_0[] = { 0x83, 0xF8, 0x00 };      
		const unsigned char code__jz_offset[] = { 0x0F, 0x84, 0x00, 0x00, 0x00, 0x00 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cmp_eax_0, 3);			
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jz_offset, 6);			
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned long long int)(currBytePtr - 4);

		//lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1];
		strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++ - 1].lexemStr, MAX_LEXEM_SIZE);
		//lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1];
		strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++ - 1].lexemStr, MAX_LEXEM_SIZE);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    cmp eax, 0\r\n");
		printf("    jz LABEL@AFTER_WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
#endif

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeContinueWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_CONTINUE_WHILE);
	if (multitokenSize) {
		if (
			lexemInfoTransformationTempStackSize >= 6
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_THEN][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_IF][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 6].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {

#ifdef DEBUG_MODE_BY_ASSEMBLY		
			printf("\r\n");
			printf("    ;continue while (in \"then\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
#endif	

			const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 }; // jmp

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
			//lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].ifvalue = (unsigned long long int)(currBytePtr - 4);
			*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 6].ifvalue - currBytePtr);
			strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr, tokenStruct[MULTI_TOKEN_CONTINUE_WHILE][0], MAX_LEXEM_SIZE);

#ifdef DEBUG_MODE_BY_ASSEMBLY		
			printf("    jmp LABEL@WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 6].lexemStr);
#endif

			return *lastLexemInfoInTable += multitokenSize, currBytePtr;
		}
		else if (
			lexemInfoTransformationTempStackSize >= 5
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_ELSE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {

#ifdef DEBUG_MODE_BY_ASSEMBLY		
			printf("\r\n");
			printf("    ;continue while (in \"else\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
#endif	

			const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 }; // jmp

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
			//lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].ifvalue = (unsigned long long int)(currBytePtr - 4);
			*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].ifvalue - currBytePtr);			
			strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_CONTINUE_WHILE][0], MAX_LEXEM_SIZE);

#ifdef DEBUG_MODE_BY_ASSEMBLY	

			printf("    jmp LABEL@WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr);
#endif

			return *lastLexemInfoInTable += multitokenSize, currBytePtr;
		}
		else if (lexemInfoTransformationTempStackSize >= 4
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {

#ifdef DEBUG_MODE_BY_ASSEMBLY		
			printf("\r\n");
			printf("    ;continue while (in \"%s\")\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
#endif	

			const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 }; // jmp

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
			//lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned long long int)(currBytePtr - 4);
			*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].ifvalue - currBytePtr);
			strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_CONTINUE_WHILE][0], MAX_LEXEM_SIZE);

#ifdef DEBUG_MODE_BY_ASSEMBLY		
			printf("    jmp LABEL@WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr);
#endif

			return *lastLexemInfoInTable += multitokenSize, currBytePtr;
		}
	}

	return currBytePtr;
}

unsigned char* makeExitWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_EXIT_WHILE);
	if (multitokenSize) {
		if (
			lexemInfoTransformationTempStackSize >= 6
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_THEN][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_IF][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 6].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {

#ifdef DEBUG_MODE_BY_ASSEMBLY		
			printf("\r\n");
			printf("    ;exit while (in \"then\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
#endif	
	
			const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 }; // jmp
	
			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
			lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].ifvalue = (unsigned long long int)(currBytePtr - 4);
			strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_EXIT_WHILE][0], MAX_LEXEM_SIZE);

#ifdef DEBUG_MODE_BY_ASSEMBLY		
			printf("    jmp LABEL@AFTER_WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr);
#endif

			return *lastLexemInfoInTable += multitokenSize, currBytePtr;
		}
		else if (
			lexemInfoTransformationTempStackSize >= 5
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_ELSE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 5].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {

#ifdef DEBUG_MODE_BY_ASSEMBLY		
			printf("\r\n");
			printf("    ;exit while (in \"else\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
#endif	

			const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 }; // jmp

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
			lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned long long int)(currBytePtr - 4);
			strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_EXIT_WHILE][0], MAX_LEXEM_SIZE);

#ifdef DEBUG_MODE_BY_ASSEMBLY	
	
			printf("    jmp LABEL@AFTER_WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr);
#endif

			return *lastLexemInfoInTable += multitokenSize, currBytePtr;
		}
		else if (lexemInfoTransformationTempStackSize >= 4
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
			) {

#ifdef DEBUG_MODE_BY_ASSEMBLY		
			printf("\r\n");
			printf("    ;exit while (in \"%s\")\r\n", tokenStruct[MULTI_TOKEN_WHILE][0]);
#endif	

			const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 }; // jmp

			currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
			lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned long long int)(currBytePtr - 4);
			strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_EXIT_WHILE][0], MAX_LEXEM_SIZE);

#ifdef DEBUG_MODE_BY_ASSEMBLY		
			printf("    jmp LABEL@AFTER_WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
#endif

			return *lastLexemInfoInTable += multitokenSize, currBytePtr;
		}
	}

	return currBytePtr;
}

unsigned char* makePostWhileCode_(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode, unsigned char depthOfÑontext) {
	const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };

//	if (!strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_CONTINUE_WHILE][0], MAX_LEXEM_SIZE)) {
//		*(unsigned int*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].ifvalue - currBytePtr - 4);
//	}
	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
	*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].ifvalue - currBytePtr);
	*(unsigned int*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].ifvalue = (unsigned int)(currBytePtr - (unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].ifvalue - 4);
	if (!strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_EXIT_WHILE][0], MAX_LEXEM_SIZE)) {
		*(unsigned int*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned int)(currBytePtr - (unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue - 4);
	}

#ifdef DEBUG_MODE_BY_ASSEMBLY	
	printf("    jmp LABEL@WHILE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr);
	printf("    LABEL@AFTER_WHILE_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr);
#endif

	return currBytePtr;
}

unsigned char* makeEndWhileAfterWhileCycleCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) { // Or Ender!
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_END_WHILE);
	if (multitokenSize
		&& lexemInfoTransformationTempStackSize >= 4
		&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 3].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
		&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 4].lexemStr, tokenStruct[MULTI_TOKEN_WHILE][0], MAX_LEXEM_SIZE)
		) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;end of while\r\n");
#endif

		currBytePtr = makePostWhileCode_(lastLexemInfoInTable, currBytePtr, generatorMode, 0);

		lexemInfoTransformationTempStackSize -= 4;
		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}