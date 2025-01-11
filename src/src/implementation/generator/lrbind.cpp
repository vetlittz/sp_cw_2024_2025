#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lrbind codegen                    *
*                         file: lrbind.cpp                  *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"

unsigned char* makeLeftToRightBindCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_LRBIND);
	if (multitokenSize) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_LRBIND][0]);
#endif

		const unsigned char code__mov_ebx_stackTopByECX[]       = { 0x8B, 0x19 };
		const unsigned char code__mov_eax_stackTopByECXMinus4[] = { 0x8B, 0x41, 0xFC };
		const unsigned char code__sub_ecx_8[]                   = { 0x83, 0xE9, 0x08 };
		const unsigned char code__add_ebx_edi[]                 = { 0x03, 0xDF };
		const unsigned char code__mov_addrFromEBX_eax[]         = { 0x89, 0x03 };
		const unsigned char code__mov_ecx_edi[]                 = { 0x8B, 0xCF };                        	
		const unsigned char code__add_ecx_512[]                 = { 0x81, 0xC1, 0x00, 0x02, 0x00, 0x00 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_ebx_stackTopByECX, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECXMinus4, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_ecx_8, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_ebx_edi, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_addrFromEBX_eax, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_ecx_edi, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__add_ecx_512, 6);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    mov ebx, dword ptr[ecx]\r\n");
		printf("    mov eax, dword ptr[ecx - 4]\r\n");
		printf("    sub ecx, 8\r\n");
		printf("    add ebx, edi\r\n");
		printf("    mov dword ptr [ebx], eax\r\n");
		printf("    mov ecx, edi ; reset second stack\r\n");
		printf("    add ecx, 512 ; reset second stack\r\n");
#endif

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}