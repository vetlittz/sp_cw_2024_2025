#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: goto_lable.h                *
*                                                  (draft!) *
*************************************************************/

#include <string>
#include <map>

extern std::map<std::string, unsigned long long int> labelInfoTable;

#define LABEL_GOTO_LABELE_CODER(A, B, C, M, R)\
if (A ==* B) C = makeLabelCode(B, C, M);\
if (A ==* B) C = makeGotoLabelCode(B, C, M);

unsigned char* makeLabelCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);

unsigned char* makeGotoLabelCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode);