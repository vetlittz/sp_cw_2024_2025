#include <iostream>
//#include <vector>
#include <map>
//#include <unordered_map>
#include <string>
#include <set>

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

Grammar grammar = {
    {
        {"labeled_point", 2, {"ident", "tokenCOLON"}}, // !!!!!
        {"goto_label", 2, {"tokenGOTO","ident"}},      // !!!!!
        {"program_name", 1, {"ident_terminal"}},
        {"value_type", 1, {"INTEGER16"}},
        {"other_declaration_ident", 2, {"tokenCOMMA", "ident"}},
        {"other_declaration_ident____iteration_after_one", 2, {"other_declaration_ident","other_declaration_ident____iteration_after_one", }},
        {"other_declaration_ident____iteration_after_one", 2, {"tokenCOMMA", "ident"}},
        {"value_type__ident", 2, {"value_type", "ident"}},
        {"declaration", 2, {"value_type__ident", "other_declaration_ident____iteration_after_one"}},
        {"declaration", 2, {"value_type", "ident"}},
        //
        {"unary_operator", 1, {"NOT"}},
        {"unary_operator", 1, {"-"}},
        {"unary_operator", 1, {"+"}},
        {"binary_operator", 1, {"AND"}},
        {"binary_operator", 1, {"OR"}},
        {"binary_operator", 1, {"=="}},
        {"binary_operator", 1, {"!="}},
        {"binary_operator", 1, {"<="}},
        {"binary_operator", 1, {">="}},
        {"binary_operator", 1, {"+"}},
        {"binary_operator", 1, {"-"}},
        {"binary_operator", 1, {"*"}},
        {"binary_operator", 1, {"DIV"}},
        {"binary_operator", 1, {"MOD"}},
        {"binary_action", 2, {"binary_operator","expression"}},
        //
        {"left_expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},
        {"left_expression", 2, {"unary_operator","expression"}},
        {"left_expression", 1, {"ident_terminal"}},
        {"left_expression", 1, {"value_terminal"}},
        {"binary_action____iteration_after_two", 2, {"binary_action","binary_action____iteration_after_two"}},
        {"binary_action____iteration_after_two", 2, {"binary_action","binary_action"}},
        {"expression", 2, {"left_expression","binary_action____iteration_after_two"}},
        {"expression", 2, {"left_expression","binary_action"}},
        {"expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},
        {"expression", 2, {"unary_operator","expression"}},
        {"expression", 1, {"ident_terminal"}},
        {"expression", 1, {"value_terminal"}},
        //
        {"tokenGROUPEXPRESSIONBEGIN__expression", 2, {"tokenGROUPEXPRESSIONBEGIN","expression"}},
        {"group_expression", 2, {"tokenGROUPEXPRESSIONBEGIN__expression","tokenGROUPEXPRESSIONEND"}},
        //
        {"bind_right_to_left", 2, {"ident","rl_expression"}},
        {"bind_left_to_right", 2, {"lr_expression","ident"}},
        //
        {"body_for_true", 2, {"statement____iteration_after_two","tokenSEMICOLON"}},
        {"body_for_true", 2, {"statement","tokenSEMICOLON"}},
        {"body_for_true", 1, {";"}},
        {"tokenELSE__statement", 2, {"tokenELSE","statement"}},
        {"tokenELSE__statement____iteration_after_two", 2, {"tokenELSE","statement____iteration_after_two"}},
        {"body_for_false", 2, {"tokenELSE__statement____iteration_after_two","tokenSEMICOLON"}},
        {"body_for_false", 2, {"tokenELSE__statement","tokenSEMICOLON"}},
        {"body_for_false", 2, {"tokenELSE","tokenSEMICOLON"}},
        {"tokenIF__tokenGROUPEXPRESSIONBEGIN", 2, {"tokenIF","tokenGROUPEXPRESSIONBEGIN"}},
        {"expression__tokenGROUPEXPRESSIONEND", 2, {"expression","tokenGROUPEXPRESSIONEND"}},
        {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN","expression__tokenGROUPEXPRESSIONEND"}},
        {"body_for_true__body_for_false", 2, {"body_for_true","body_for_false"}},
        {"cond_block", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"}},
        {"cond_block", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"}},
        //
        {"cycle_counter", 1, {"ident_terminal"}},
        {"rl_expression", 2, {"tokenRLBIND","expression"}},
        {"lr_expression", 2, {"expression","tokenLRBIND"}},
        {"cycle_counter_init", 2, {"cycle_counter","rl_expression"}},
        {"cycle_counter_init", 2, {"lr_expression","cycle_counter"}},
        {"cycle_counter_last_value", 1, {"value_terminal"}},
        {"cycle_body", 2, {"tokenDO","statement_in_while_body____iteration_after_two"}},
        {"cycle_body", 2, {"tokenDO","statement"}},
        {"tokenFOR__cycle_counter_init", 2, {"tokenFOR","cycle_counter_init"}},
        {"tokenTO__cycle_counter_last_value", 2, {"tokenTO","cycle_counter_last_value"}},
        {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value", 2, {"tokenFOR__cycle_counter_init","tokenTO__cycle_counter_last_value"}},
        {"cycle_body__tokenSEMICOLON", 2, {"cycle_body","tokenSEMICOLON"}},
        {"forto_cycle", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"}},
        //
        {"continue_while", 2, {"tokenCONTINUE","tokenWHILE"}},
        {"exit_while", 2, {"tokenEXIT","tokenWHILE"}},
        {"tokenWHILE__expression", 2, {"tokenWHILE","expression"}},
        {"tokenEND__tokenWHILE", 2, {"tokenEND","tokenWHILE"}},
        {"tokenWHILE__expression__statement_in_while_body", 2, {"tokenWHILE__expression","statement_in_while_body"}},
        {"tokenWHILE__expression__statement_in_while_body____iteration_after_two", 2, {"tokenWHILE__expression","statement_in_while_body____iteration_after_two"}},
        {"while_cycle", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE "}},
        {"while_cycle", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"}},
        {"while_cycle", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"}},
        //
        {"tokenUNTIL__group_expression", 2, {"tokenUNTIL","group_expression"}},
        {"tokenREPEAT__statement____iteration_after_two", 2, {"tokenREPEAT","statement____iteration_after_two"}},
        {"tokenREPEAT__statement", 2, {"tokenREPEAT","statement"}},
        {"repeat_until_cycle", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__group_expression"}},
        {"repeat_until_cycle", 2, {"tokenREPEAT__statement","tokenUNTIL__group_expression"}},
        {"repeat_until_cycle", 2, {"tokenREPEAT","tokenUNTIL__group_expression"}},
        //
        {"input__first_part", 2, {"tokenGET","tokenGROUPEXPRESSIONBEGIN"}},
        {"input__second_part", 2, {"ident","tokenGROUPEXPRESSIONEND"}},
        {"input", 2, {"input__first_part","input__second_part"}},
        //
        {"output__first_part", 2, {"tokenPUT","tokenGROUPEXPRESSIONBEGIN"}},
        {"output__second_part", 2, {"expression","tokenGROUPEXPRESSIONEND"}},
        {"output", 2, {"output__first_part","output__second_part"}},
        //
        {"statement", 2, {"ident","rl_expression"}},
        {"statement", 2, {"lr_expression","ident"}},
        {"statement", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"}},
        {"statement", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"}},
        {"statement", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"}},
        {"statement", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE"}},
        {"statement", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"}},
        {"statement", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"}},
        {"statement", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__group_expression"}},
        {"statement", 2, {"tokenREPEAT__statement","tokenUNTIL__group_expression"}},
        {"statement", 2, {"tokenREPEAT","tokenUNTIL__group_expression"}},
        {"statement", 2, {"label","tokenCOLON"}},
        {"statement", 2, {"tokenGOTO","label"}},
        {"statement", 2, {"input__first_part","input__second_part"}},
        {"statement", 2, {"output__first_part","output__second_part"}},
        {"statement____iteration_after_two", 2, {"statement","statement____iteration_after_two"}},
        {"statement____iteration_after_two", 2, {"statement","statement"}},
        //
        { "statement_in_while_body", 2, {"ident","rl_expression"} },
        { "statement_in_while_body", 2, {"lr_expression","ident"} },
        { "statement_in_while_body", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true__body_for_false"} },
        { "statement_in_while_body", 2, {"tokenIF__tokenGROUPEXPRESSIONBEGIN__expression__tokenGROUPEXPRESSIONEND","body_for_true"} },
        { "statement_in_while_body", 2, {"tokenFOR__cycle_counter_init__tokenTO__cycle_counter_last_value","cycle_body__tokenSEMICOLON"} },
        { "statement_in_while_body", 2, {"tokenWHILE__expression__statement_in_while_body____iteration_after_two","tokenEND__tokenWHILE"} },
        { "statement_in_while_body", 2, {"tokenWHILE__expression__statement_in_while_body","tokenEND__tokenWHILE"} },
        { "statement_in_while_body", 2, {"tokenWHILE__expression","tokenEND__tokenWHILE"} },
        { "statement_in_while_body", 2, {"tokenREPEAT__statement____iteration_after_two","tokenUNTIL__group_expression"} },
        { "statement_in_while_body", 2, {"tokenREPEAT__statement","tokenUNTIL__group_expression"} },
        { "statement_in_while_body", 2, {"tokenREPEAT","tokenUNTIL__group_expression"} },
        { "statement_in_while_body", 2, {"label","tokenCOLON"} },
        { "statement_in_while_body", 2, {"tokenGOTO","label"} },
        { "statement_in_while_body", 2, {"input__first_part","input__second_part"} },
        { "statement_in_while_body", 2, {"output__first_part","output__second_part"} },
        { "statement_in_while_body____iteration_after_two", 2, {"statement_in_while_body","statement_in_while_body____iteration_after_two"} },
        { "statement_in_while_body____iteration_after_two", 2, {"statement_in_while_body","statement_in_while_body"} },
        //
        {"tokenNAME__program_name", 2, {"tokenNAME","program_name"}},
        {"tokenSEMICOLON__tokenBODY", 2, {"tokenSEMICOLON","tokenBODY"}},
        {"tokenDATA__declaration", 2, {"tokenDATA","declaration"}},
        {"tokenNAME__program_name__tokenSEMICOLON__tokenBODY", 2, {"tokenNAME__program_name","tokenSEMICOLON__tokenBODY"}},
        {"program____part1", 2, {"tokenNAME__program_name__tokenSEMICOLON__tokenBODY","tokenDATA__declaration"}},
        {"program____part1", 2, {"tokenNAME__program_name__tokenSEMICOLON__tokenBODY","tokenDATA"}},
        {"statement__tokenEND", 2, {"statement","tokenEND"}},
        {"statement____iteration_after_two__tokenEND", 2, {"statement____iteration_after_two","tokenEND"}},
        {"program____part2", 2, {"tokenSEMICOLON","statement____iteration_after_two__tokenEND"}},
        {"program____part2", 2, {"tokenSEMICOLON","statement__tokenEND"}},
        {"program____part2", 2, {"tokenSEMICOLON","tokenEND"}},
        {"program", 2, {"program____part1","program____part2"}},
        //
        {"tokenCOLON", 1, {":"}},
        {"tokenGOTO", 1, {"GOTO"}},
        {"tokenINTEGER16", 1, {"INTEGER16"}},
        {"tokenCOMMA", 1, {","}},
        {"tokenNOT", 1, {"NOT"}},
        {"tokenAND", 1, {"AND"}},
        {"tokenOR", 1, {"OR"}},
        {"tokenEQUAL", 1, {"=="}},
        {"tokenNOTEQUAL", 1, {"!="}},
        {"tokenLESSOREQUAL", 1, {"<="}},
        {"tokenGREATEROREQUAL", 1, {">="}},
        {"tokenPLUS", 1, {"+"}},
        {"tokenMINUS", 1, {"-"}},
        {"tokenMUL", 1, {"*"}},
        {"tokenDIV", 1, {"DIV"}},
        {"tokenMOD", 1, {"MOD"}},
        {"tokenGROUPEXPRESSIONBEGIN", 1, {"("}},
        {"tokenGROUPEXPRESSIONEND", 1, {")"}},
        {"tokenRLBIND", 1, {"<<"}},
        {"tokenLRBIND", 1, {">>"}},
        {"tokenELSE", 1, {"ELSE"}},
        {"tokenIF", 1, {"IF"}},
        {"tokenDO", 1, {"DO"}},
        {"tokenFOR", 1, {"FOR"}},
        {"tokenTO", 1, {"TO"}},
        {"tokenWHILE", 1, {"WHILE"}},
        {"tokenCONTINUE", 1, {"CONTINUE"}},
        {"tokenEXIT", 1, {"EXIT"}},
        {"tokenREPEAT", 1, {"REPEAT"}},
        {"tokenUNTIL", 1, {"UNTIL"}},
        {"tokenGET", 1, {"GET"}},
        {"tokenPUT", 1, {"PUT"}},
        {"tokenNAME", 1, {"NAME"}},
        {"tokenBODY", 1, {"BODY"}},
        {"tokenDATA", 1, {"DATA"}},
        {"tokenEND", 1, {"END"}},
        {"tokenSEMICOLON", 1, {";"}},
        //
        { "value", 1, {"value_terminal"} },
        //
        { "ident", 1, {"ident_terminal"} },
        //
        { "label", 1, {"ident_terminal"} },
        //
        { "", 2, {"",""} }
    },
    176,
    "program"
};

#define DEBUG_STATES

bool cykAlgorithmImplementation(struct LexemInfo* lexemInfoTable, Grammar* grammar, int maxErrorToViewCount = 32) {
    if (lexemInfoTable == NULL || grammar == NULL) {
        return false;
    }

#ifndef DEBUG_STATES
    cout << "cykParse in progress.....[please wait]";
#else
    cout << "cykParse in progress.....[please wait]: ";
#endif

    map<int, map<int, set<string>>> parseInfoTable;

    int lexemIndex = 0;
    for (--lexemIndex; lexemInfoTable[++lexemIndex].lexemStr[0];) {
#ifdef DEBUG_STATES
        printf("\rcykParse in progress.....[please wait]: %02d %16s", lexemIndex, lexemInfoTable[lexemIndex].lexemStr);
#endif

        // Iterate over the rules
        for (int xIndex = 0; xIndex < grammar->rule_count; ++xIndex) {
            string&& lhs = grammar->rules[xIndex].lhs;
            Rule& rule = grammar->rules[xIndex];
            // If a terminal is found
            if (rule.rhs_count == 1 && (
                lexemInfoTable[lexemIndex].tokenType == IDENTIFIER_LEXEME_TYPE && !strcmp(rule.rhs[0], "ident_terminal")
                ||
                lexemInfoTable[lexemIndex].tokenType == VALUE_LEXEME_TYPE && !strcmp(rule.rhs[0], "value_terminal")
                ||
                !strncmp(rule.rhs[0], lexemInfoTable[lexemIndex].lexemStr, MAX_LEXEM_SIZE)
                )) {
                parseInfoTable[lexemIndex][lexemIndex].insert(lhs);
            }
        }
        for (int iIndex = lexemIndex; iIndex >= 0; --iIndex) {
            for (int kIndex = iIndex; kIndex <= lexemIndex; ++kIndex) {
                for (int xIndex = 0; xIndex < grammar->rule_count; ++xIndex) {
                    string&& lhs = grammar->rules[xIndex].lhs;
                    Rule& rule = grammar->rules[xIndex];
                    if (rule.rhs_count == 2
                        && parseInfoTable[iIndex][kIndex].find(rule.rhs[0]) != parseInfoTable[iIndex][kIndex].end()
                        && parseInfoTable[kIndex + 1][lexemIndex].find(rule.rhs[1]) != parseInfoTable[kIndex + 1][lexemIndex].end()
                        ) {
                        parseInfoTable[iIndex][lexemIndex].insert(lhs);
                    }
                }
            }
        }
    }

    cout << "\r" << "cykParse complete........[     ok    ]\n";

    return parseInfoTable[0][lexemIndex - 1].find(grammar->start_symbol) != parseInfoTable[0][lexemIndex - 1].end(); // return !!parseInfoTable[0][lexemIndex - 1].size();
}