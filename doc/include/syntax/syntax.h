#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"

using namespace std;

#define MAX_RULES 356

#define MAX_TOKEN_SIZE 128
#define MAX_RTOKEN_COUNT 2 // 3

typedef struct {
	char lhs[MAX_TOKEN_SIZE];
	int rhs_count;
	char rhs[MAX_RTOKEN_COUNT][MAX_TOKEN_SIZE];
} Rule;

typedef struct {
	Rule rules[MAX_RULES];
	int rule_count;
	char start_symbol[MAX_TOKEN_SIZE] ;
} Grammar;

extern Grammar grammar;

#define DEBUG_STATES

bool cykAlgorithmImplementation(struct LexemInfo* lexemInfoTable, Grammar* grammar, int maxErrorToViewCount/* = 32*/);