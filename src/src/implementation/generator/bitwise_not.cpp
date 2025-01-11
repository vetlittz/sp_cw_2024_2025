#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: bitwise_not.cpp             *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"

unsigned char* makeBitwiseNotCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_BITWISE_NOT);
	if (multitokenSize) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_BITWISE_NOT][0]);
#endif

		const unsigned char code__not_stackTopByECX[] = { 0xF7, 0x11 };
		const unsigned char code__mov_eax_stackTopByECX[] = { 0x8B, 0x01 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__not_stackTopByECX, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECX, 3);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    not dword ptr[ecx]\r\n");
		printf("    mov eax, dword ptr[ecx]\r\n");
#endif

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}