// TODO: CHANGE BY fRESET() TO END
#define DEBUG_MODE_BY_ASSEMBLY
#define C_CODER_MODE                   0x01
#define ASSEMBLY_X86_WIN32_CODER_MODE  0x02
#define OBJECT_X86_WIN32_CODER_MODE    0x04
#define MACHINE_CODER_MODE             0x08

extern unsigned char generatorMode;

#define MAX_TOKEN_STRUCT_ELEMENT_COUNT 64
#define MAX_TOKEN_STRUCT_ELEMENT_PART_COUNT 4

#define CODEGEN_DATA_TYPE int

#define START_DATA_OFFSET 512
#define OUT_DATA_OFFSET (START_DATA_OFFSET + 512)

#define M1 1024
#define M2 1024

//unsigned long long int dataOffsetMinusCodeOffset = 0x00003000;
#define dataOffsetMinusCodeOffset 0x00004000ull

//unsigned long long int codeOffset = 0x000004AF;
//unsigned long long int baseOperationOffset = codeOffset + 49;// 0x00000031;
#define baseOperationOffset 0x000004AFull
#define putProcOffset 0x0000001Bull
#define getProcOffset 0x00000044ull

//unsigned long long int startCodeSize = 64 - 14; // 50 // -1

#ifndef TOKEN_STRUCT_NAME_
#define TOKEN_STRUCT_NAME_
enum TokenStructName {
	MULTI_TOKEN_BITWISE_NOT,
	MULTI_TOKEN_BITWISE_AND,
	MULTI_TOKEN_BITWISE_OR,
	MULTI_TOKEN_NOT,
	MULTI_TOKEN_AND,
	MULTI_TOKEN_OR,

	MULTI_TOKEN_EQUAL,
	MULTI_TOKEN_NOT_EQUAL,
	MULTI_TOKEN_LESS,
	MULTI_TOKEN_GREATER,
	MULTI_TOKEN_LESS_OR_EQUAL,
	MULTI_TOKEN_GREATER_OR_EQUAL,

	MULTI_TOKEN_ADD,
	MULTI_TOKEN_SUB,
	MULTI_TOKEN_MUL,
	MULTI_TOKEN_DIV,
	MULTI_TOKEN_MOD,

	MULTI_TOKEN_BIND_RIGHT_TO_LEFT,
	MULTI_TOKEN_BIND_LEFT_TO_RIGHT,

	MULTI_TOKEN_COLON,
	MULTI_TOKEN_GOTO,

	MULTI_TOKEN_IF,
	//	MULTI_TOKEN_IF_, // don't change this!
	MULTI_TOKEN_THEN,
	//	MULTI_TOKEN_THEN_, // don't change this!
	MULTI_TOKEN_ELSE,

	MULTI_TOKEN_FOR,
	MULTI_TOKEN_TO,
	MULTI_TOKEN_DOWNTO,
	MULTI_TOKEN_DO,

	//
	MULTI_TOKEN_WHILE,
	/*while special statement*/MULTI_TOKEN_CONTINUE_WHILE,
	/*while special statement*/MULTI_TOKEN_EXIT_WHILE,
	MULTI_TOKEN_END_WHILE,
	//

	//
	MULTI_TOKEN_REPEAT,
	MULTI_TOKEN_UNTIL,
	//

	//
	MULTI_TOKEN_INPUT,
	MULTI_TOKEN_OUTPUT,
	//

	//
	MULTI_TOKEN_RLBIND,
	MULTI_TOKEN_LRBIND,
	//

	MULTI_TOKEN_SEMICOLON,

	MULTI_TOKEN_BEGIN,
	MULTI_TOKEN_END,

	//

	MULTI_TOKEN_NULL_STATEMENT
};
#endif

extern char* tokenStruct[MAX_TOKEN_STRUCT_ELEMENT_COUNT][MAX_TOKEN_STRUCT_ELEMENT_PART_COUNT];

unsigned char detectMultiToken(struct LexemInfo* lexemInfoTable, enum TokenStructName tokenStructName);
unsigned char createMultiToken(struct LexemInfo** lexemInfoTable, enum TokenStructName tokenStructName);
#define MAX_ACCESSORY_STACK_SIZE 128
extern struct NonContainedLexemInfo lexemInfoTransformationTempStack[MAX_ACCESSORY_STACK_SIZE];
extern unsigned long long int lexemInfoTransformationTempStackSize;
unsigned char* outBytes2Code(unsigned char* currBytePtr, unsigned char* fragmentFirstBytePtr, unsigned long long int bytesCout);

#if 1
unsigned char* getCodeBytePtr(unsigned char* baseBytePtr);
void makeCode(struct LexemInfo** lastLexemInfoInTable/*TODO:...*/, unsigned char* currBytePtr);

#endif