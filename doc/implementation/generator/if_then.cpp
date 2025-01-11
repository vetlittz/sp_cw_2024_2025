#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // lex + rpn + MACHINECODEGEN!  *
*                         file: if_then.cpp                 *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"
#include "string.h"

unsigned char* makeIfCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_IF);
	if (!multitokenSize 
		&& tokenStruct[MULTI_TOKEN_IF][1][0] == '('
		&& !strncmp((*lastLexemInfoInTable)->lexemStr, tokenStruct[MULTI_TOKEN_IF][0], MAX_LEXEM_SIZE)) {
		multitokenSize = 1;
	}
	if (multitokenSize) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_IF][0]);
#endif

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeThenCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_THEN);
	if (!multitokenSize && tokenStruct[MULTI_TOKEN_IF][1][0] == '(') {
		multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_NULL_STATEMENT);
	}
	if (multitokenSize
		&& lexemInfoTransformationTempStackSize
		&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_IF][0], MAX_LEXEM_SIZE)
		) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
			printf("\r\n");
			printf("    ;after cond expresion (after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_IF][0]);
#endif	
  
		const unsigned char code__cmp_eax_0[] = { 0x83, 0xF8, 0x00 };
		const unsigned char code__jz_offset[] = { 0x0F, 0x84, 0x00, 0x00, 0x00, 0x00 };
			
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cmp_eax_0, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jz_offset, 6);

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;
		strncpy(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_THEN][0], MAX_LEXEM_SIZE);
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned long long int)(currBytePtr - 4);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    cmp eax, 0\r\n");
		printf("    jz LABEL@AFTER_THEN_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
#endif

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makePostThenCode_(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	const unsigned char code__mov_eax_1[]  = { 0xB8, 0x01, 0x00, 0x00, 0x00 };

	currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_1, 5);
	*(unsigned int*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned int)(currBytePtr - (unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue - 4);

#ifdef DEBUG_MODE_BY_ASSEMBLY
	printf("    mov eax, 1\r\n");
	printf("    LABEL@AFTER_THEN_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
#endif

	return currBytePtr;
}

unsigned char* makeSemicolonAfterThenCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) { // Or Ender!
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_SEMICOLON);
	if (multitokenSize
		&&
		lexemInfoTransformationTempStackSize >= 2
		&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 2].lexemStr, tokenStruct[MULTI_TOKEN_IF][0], MAX_LEXEM_SIZE)
		&& !strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_THEN][0], MAX_LEXEM_SIZE)
		) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\" (after \"then\"-part of %s-operator)\r\n", tokenStruct[MULTI_TOKEN_SEMICOLON][0], tokenStruct[MULTI_TOKEN_IF][0]);
#endif

		currBytePtr = makePostThenCode_(lastLexemInfoInTable, currBytePtr, generatorMode);

		lexemInfoTransformationTempStackSize -= 2;
		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}