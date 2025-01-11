#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: else.cpp                    *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"
#include "string.h"

unsigned char* makeElseCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_ELSE);
	if (multitokenSize) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_ELSE][0]);
#endif

		const unsigned char code__cmp_eax_0[] = { 0x83, 0xF8, 0x00 };
		const unsigned char code__jnz_offset[] = { 0x0F, 0x85, 0x00, 0x00, 0x00, 0x00 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cmp_eax_0, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jnz_offset, 6);

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = **lastLexemInfoInTable;
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned long long int)(currBytePtr - 4);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    cmp eax, 0\r\n");
		printf("    jnz LABEL@AFTER_ELSE_%016llX\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
#endif

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makePostElseCode_(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	*(unsigned int*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue = (unsigned int)(currBytePtr - (unsigned char*)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].ifvalue - 4);

#ifdef DEBUG_MODE_BY_ASSEMBLY
	printf("    LABEL@AFTER_ELSE_%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
#endif

	return currBytePtr;
}

unsigned char* makeSemicolonAfterElseCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) { // Or Ender!
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_SEMICOLON);
	if (multitokenSize
		&&
		lexemInfoTransformationTempStackSize
		&&
		!strncmp(lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr, tokenStruct[MULTI_TOKEN_ELSE][0], MAX_LEXEM_SIZE)
		) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\" (after \"%s\")\r\n", tokenStruct[MULTI_TOKEN_SEMICOLON][0], tokenStruct[MULTI_TOKEN_ELSE][0]);
#endif

		currBytePtr = makePostElseCode_(lastLexemInfoInTable, currBytePtr, generatorMode);

		--lexemInfoTransformationTempStackSize;
		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}