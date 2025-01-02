#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: goto_lable.hxx              *
*                                                  (draft!) *
*************************************************************/

#include <string>
#include <map>
std::map<std::string, unsigned long long int> labelInfoTable;

#define LABEL_GOTO_LABELE_CODER(A, B, C)\
if (A ==* B) C = makeLabelCode(B, C);\
if (A ==* B) C = makeGotoLabelCode(B, C);

unsigned char* makeLabelCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	if ((*lastLexemInfoInTable)->tokenType != IDENTIFIER_LEXEME_TYPE) {
		return currBytePtr;
	}
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable + 1, MULTI_TOKEN_COLON);
	if (multitokenSize) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\" after %s(as label)\r\n", tokenStruct[MULTI_TOKEN_COLON][0], (*lastLexemInfoInTable)->lexemStr);
#endif

		labelInfoTable[(*lastLexemInfoInTable)->lexemStr] = (unsigned long long int)currBytePtr;

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    LABEL@%016llX:\r\n", (unsigned long long int)lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1].lexemStr);
#endif

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}

unsigned char* makeGotoLabelCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_GOTO);
	if (multitokenSize) {
		if ((*lastLexemInfoInTable + 1)->tokenType != IDENTIFIER_LEXEME_TYPE) {
			return currBytePtr;
		}
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\" (after %s)\r\n", (*lastLexemInfoInTable)->lexemStr, tokenStruct[MULTI_TOKEN_GOTO][0]);
#endif

		const unsigned char code__jmp_offset[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__jmp_offset, 5);
		*(unsigned int*)(currBytePtr - 4) = (unsigned int)((unsigned char*)labelInfoTable[(*lastLexemInfoInTable)->lexemStr] - currBytePtr);

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}