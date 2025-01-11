#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: add.cpp                     *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"

unsigned char* makeAddCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_ADD);
	if (multitokenSize) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_ADD][0]);
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

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}