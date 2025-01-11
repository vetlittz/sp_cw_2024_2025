#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: and.cpp                     *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"

unsigned char* makeAndCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_AND);
	if (multitokenSize) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_AND][0]);
#endif

		const unsigned char code__mov_eax_stackTopByECX[] = { 0x8B, 0x01 };
		const unsigned char code__cmp_eax_0[] = { 0x83, 0xF8, 0x00 };
		const unsigned char code__setne_al[] = { 0x0F, 0x95, 0xC0 };
		const unsigned char code__and_eax_1[] = { 0x83, 0xE0, 0x01 };
		const unsigned char code__sub_ecx_4[] = { 0x83, 0xE9, 0x04 };
		//
		const unsigned char code__cmp_stackTopByECX_0[] = { 0x83, 0x39, 0x00 };
		const unsigned char code__setne_dl[] = { 0x0F, 0x95, 0xC2 };
		const unsigned char code__and_edx_1[] = { 0x83, 0xE2, 0x01 };
		//
		const unsigned char code__and_eax_edx[] = { 0x23, 0xC2 };
		//
		const unsigned char code__mov_stackTopByECX_eax[] = { 0x89, 0x01 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECX, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cmp_eax_0, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__setne_al, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__and_eax_1, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_ecx_4, 3);
		//
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cmp_stackTopByECX_0, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__setne_dl, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__and_edx_1, 3);
		//
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__and_eax_edx, 2);
		//
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_stackTopByECX_eax, 2);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    mov eax, dword ptr[ecx]\r\n");
		printf("    cmp eax, 0\r\n");
		printf("    setne al\r\n");
		printf("    and eax, 1\r\n");
		printf("    sub ecx, 4\r\n");
		//
		printf("    cmp dword ptr[ecx], 0\r\n");
		printf("    setne dl\r\n");
		printf("    and edx, 1\r\n");
		//
		printf("    and eax, edx\r\n");
		//
		printf("    mov dword ptr[ecx], eax\r\n");
#endif

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}