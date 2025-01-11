#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: mul.cpp                     *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"

unsigned char* makeMulCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_MUL);
	if (multitokenSize) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_MUL][0]);
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

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}