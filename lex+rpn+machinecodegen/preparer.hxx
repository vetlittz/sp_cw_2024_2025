#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: preparer.hxx                *
*                                                  (draft!) *
*************************************************************/

int precedenceLevel(char* lexemStr) {
	if (!strncmp(lexemStr, "NOT", MAX_LEXEM_SIZE)) {
		return 5;
	}

	else if (!strncmp(lexemStr, "*", MAX_LEXEM_SIZE)) {
		return 4;
	}
	else if (!strncmp(lexemStr, "DIV", MAX_LEXEM_SIZE)) {
		return 4;
	}
	else if (!strncmp(lexemStr, "MOD", MAX_LEXEM_SIZE)) {
		return 4;
	}

	else if (!strncmp(lexemStr, "+", MAX_LEXEM_SIZE)) {
		return 3;
	}
	else if (!strncmp(lexemStr, "-", MAX_LEXEM_SIZE)) {
		return 3;
	}

	else if (!strncmp(lexemStr, "<<", MAX_LEXEM_SIZE)) {
		return 2;
	}
	else if (!strncmp(lexemStr, ">>", MAX_LEXEM_SIZE)) {
		return 2;
	}

	else if (!strncmp(lexemStr, "GET", MAX_LEXEM_SIZE)) {
		return 1;
	}
	else if (!strncmp(lexemStr, "PUT", MAX_LEXEM_SIZE)) {
		return 1;
	}

	return 0;

}

bool isLeftAssociative(char* lexemStr) {
	if (!strncmp(lexemStr, "*", MAX_LEXEM_SIZE)) {
		return true;
	}
	else if (!strncmp(lexemStr, "DIV", MAX_LEXEM_SIZE)) {
		return true;
	}
	else if (!strncmp(lexemStr, "MOD", MAX_LEXEM_SIZE)) {
		return true;
	}
	else if (!strncmp(lexemStr, "+", MAX_LEXEM_SIZE)) {
		return true;
	}
	else if (!strncmp(lexemStr, "-", MAX_LEXEM_SIZE)) {
		return true;
	}
	else if (!strncmp(lexemStr, ">>", MAX_LEXEM_SIZE)) { // ! TODO: ...
		return false;
	}

	else if (!strncmp(lexemStr, "<<", MAX_LEXEM_SIZE)) {
		return false;
	}
	else if (!strncmp(lexemStr, "NOT", MAX_LEXEM_SIZE)) {
		return false;
	}
	else if (!strncmp(lexemStr, "GET", MAX_LEXEM_SIZE)) {
		return false;
	}
	else if (!strncmp(lexemStr, "PUT", MAX_LEXEM_SIZE)) {
		return false;
	}

	return false;
}

bool isSplittingOperator(char* lexemStr) {

	if (!strncmp(lexemStr, "GET", MAX_LEXEM_SIZE)) {
		return true;
	}
	else if (!strncmp(lexemStr, "PUT", MAX_LEXEM_SIZE)) {
		return true;
	}

	return false;
}

void makePrepare4IdentifierOrValue(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable) { // 
	if ((*lastLexemInfoInTable)->tokenType == IDENTIFIER_LEXEME_TYPE || (*lastLexemInfoInTable)->tokenType == VALUE_LEXEME_TYPE) {
		if (!strncmp((*lastLexemInfoInTable)[1].lexemStr, "<<", MAX_LEXEM_SIZE)
			||
			!strncmp((*lastLexemInfoInTable)[-1].lexemStr, ">>", MAX_LEXEM_SIZE)
			||
			!strncmp((*lastLexemInfoInTable)[-1].lexemStr, "GET", MAX_LEXEM_SIZE)
			||
			!strncmp((*lastLexemInfoInTable)[-2].lexemStr, "GET", MAX_LEXEM_SIZE)
			) {
			bool findComplete = false;
			for (unsigned long long int index = 0; identifierIdsTable[index][0] != '\0'; ++index) {
				if (!strncmp((*lastLexemInfoInTable)->lexemStr, identifierIdsTable[index], MAX_LEXEM_SIZE)) {
					findComplete = true;
					(*lastTempLexemInfoInTable)->ifvalue = /*dataOffset + */VALUE_SIZE * index;
					_itoa((*lastTempLexemInfoInTable)->ifvalue, (*lastTempLexemInfoInTable)->lexemStr, 10);
					((*lastTempLexemInfoInTable)++)->tokenType = VALUE_LEXEME_TYPE; // ADDRESS_LEXEME_TYPE
					++* lastLexemInfoInTable;
				}
			}
			if (!findComplete) {
				printf("\r\nError!\r\n");
				exit(0);
			}
		}
		else {
			*(*lastTempLexemInfoInTable)++ = *(*lastLexemInfoInTable)++;
		}
	}
}

void makePrepare4Operators(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable) {
	if (precedenceLevel((*lastLexemInfoInTable)->lexemStr)) {
		while (lexemInfoTransformationTempStackSize > 0) {
			struct LexemInfo& currLexemInfo = lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1];
			if (precedenceLevel(currLexemInfo.lexemStr) && (
				(isLeftAssociative((*lastLexemInfoInTable)->lexemStr) && (precedenceLevel((*lastLexemInfoInTable)->lexemStr) <= precedenceLevel(currLexemInfo.lexemStr)))
				||
				(!isLeftAssociative((*lastLexemInfoInTable)->lexemStr) && (precedenceLevel((*lastLexemInfoInTable)->lexemStr) < precedenceLevel(currLexemInfo.lexemStr)))
				)) {

				**lastTempLexemInfoInTable = currLexemInfo; ++* lastTempLexemInfoInTable;
				--lexemInfoTransformationTempStackSize;
			}
			else {
				break;
			}
		}

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = *((*lastLexemInfoInTable)++);
	}
}

void makePrepare4LeftParenthesis(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable) {
	if ((*lastLexemInfoInTable)->lexemStr[0] == '(') {
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = *((*lastLexemInfoInTable)++);
	}
}

void makePrepare4RightParenthesis(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable) {
	if ((*lastLexemInfoInTable)->lexemStr[0] == ')') {
		bool findLeftParenthesis = false;
		while (lexemInfoTransformationTempStackSize > 0) {
			struct LexemInfo& currLexemInfo = lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1];
			if (currLexemInfo.lexemStr[0] == '(') {
				findLeftParenthesis = true;
				break;
			}
			else {
				**lastTempLexemInfoInTable = currLexemInfo; ++* lastTempLexemInfoInTable;
				lexemInfoTransformationTempStackSize--;
			}
		}
		if (!findLeftParenthesis) {
			printf("Warning: parentheses mismatched\n");

			**lastTempLexemInfoInTable = **lastLexemInfoInTable; ++* lastTempLexemInfoInTable;
		}
		else {
			--lexemInfoTransformationTempStackSize;
		}

		++* lastLexemInfoInTable;
	}
}

unsigned int makePrepareEnder(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable) {
	unsigned int addedLexemCount = lexemInfoTransformationTempStackSize;
	while (lexemInfoTransformationTempStackSize > 0) {
		struct LexemInfo& currLexemInfo = lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1];
		if (currLexemInfo.lexemStr[0] == '(' || currLexemInfo.lexemStr[0] == ')') {
			printf("Error: parentheses mismatched\n");
			exit(0);
		}

		**lastTempLexemInfoInTable = currLexemInfo, ++(*lastTempLexemInfoInTable); // *(*lastTempLexemInfoInTable)++ = currLexemInfo;
		--lexemInfoTransformationTempStackSize;
	}

	(*lastTempLexemInfoInTable)->lexemStr[0] = '\0';
	return addedLexemCount;
}

long long int getPrevNonParenthesesIndex(struct LexemInfo* lexemInfoInTable, unsigned long long currIndex) {
	if (!currIndex) {
		return currIndex;
	}

	long long int index = currIndex - 1;
	for (; index != ~0 && (
		lexemInfoInTable[index].lexemStr[0] == '('
		|| lexemInfoInTable[index].lexemStr[0] == ')'
		);
		--index);

	return index;
}

long long int getEndOfNewPrevExpressioIndex(struct LexemInfo* lexemInfoInTable, unsigned long long currIndex) {
	if (!currIndex) { //  || lexemInfoInTable[currIndex - 1].lexemStr[0] != '('
		return currIndex;
	}

	long long int index = currIndex - 1;
	for (; index != ~0 && lexemInfoInTable[index].lexemStr[0] == '(';
		--index);

	return index;
}

unsigned long long int getNextEndOfExpressionIndex(struct LexemInfo* lexemInfoInTable, unsigned long long prevEndOfExpressionIndex) {
	bool isPreviousExpressionComplete = false;

	for (unsigned long long int index = prevEndOfExpressionIndex + 2; lexemInfoInTable[index].lexemStr[0] != '\0'; ++index) {

		if (!strncmp(lexemInfoInTable[index].lexemStr, "(", MAX_LEXEM_SIZE) || !strncmp(lexemInfoInTable[index].lexemStr, ")", MAX_LEXEM_SIZE)) {
			continue;
		}

		long long int prevNonParenthesesIndex = getPrevNonParenthesesIndex(lexemInfoInTable, index);

		if (lexemInfoInTable[index].tokenType == IDENTIFIER_LEXEME_TYPE || lexemInfoInTable[index].tokenType == VALUE_LEXEME_TYPE) {
			if (lexemInfoInTable[prevNonParenthesesIndex].tokenType == IDENTIFIER_LEXEME_TYPE || lexemInfoInTable[prevNonParenthesesIndex].tokenType == VALUE_LEXEME_TYPE) {
				return getEndOfNewPrevExpressioIndex(lexemInfoInTable, index);
			}
		}
		else if (precedenceLevel(lexemInfoInTable[index].lexemStr) && isLeftAssociative(lexemInfoInTable[index].lexemStr)) {
			if (precedenceLevel(lexemInfoInTable[prevNonParenthesesIndex].lexemStr)) {
				return getEndOfNewPrevExpressioIndex(lexemInfoInTable, index);
			}
		}
		else if (isSplittingOperator(lexemInfoInTable[index].lexemStr)) {
			if (lexemInfoInTable[prevNonParenthesesIndex].tokenType == IDENTIFIER_LEXEME_TYPE || lexemInfoInTable[prevNonParenthesesIndex].tokenType == VALUE_LEXEME_TYPE) {
				return getEndOfNewPrevExpressioIndex(lexemInfoInTable, index);
			}
		}
		else if (lexemInfoInTable[index].tokenType != IDENTIFIER_LEXEME_TYPE && lexemInfoInTable[index].tokenType != VALUE_LEXEME_TYPE && !precedenceLevel(lexemInfoInTable[index].lexemStr)) {
			 if (lexemInfoInTable[prevNonParenthesesIndex].tokenType == IDENTIFIER_LEXEME_TYPE || lexemInfoInTable[prevNonParenthesesIndex].tokenType == VALUE_LEXEME_TYPE || precedenceLevel(lexemInfoInTable[prevNonParenthesesIndex].lexemStr)) {
				     return getEndOfNewPrevExpressioIndex(lexemInfoInTable, index);			
			 }
		}
	}

	return ~0;
}

void makePrepare(struct LexemInfo* lexemInfoInTable, struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable) {
	unsigned long long int nullStatementIndex = 0;

	lexemInfoTransformationTempStackSize = 0;
	for (; (*lastLexemInfoInTable)->lexemStr[0] != '\0'; *(*lastTempLexemInfoInTable)++ = *(*lastLexemInfoInTable)++) {
		for (struct LexemInfo* lastLexemInfoInTable_ = NULL; lastLexemInfoInTable_ != *lastLexemInfoInTable;) {

			lastLexemInfoInTable_ = *lastLexemInfoInTable;
			makePrepare4IdentifierOrValue(lastLexemInfoInTable, lastTempLexemInfoInTable);
			if (lastLexemInfoInTable_ == *lastLexemInfoInTable)
				makePrepare4Operators(lastLexemInfoInTable, lastTempLexemInfoInTable);

			if (lastLexemInfoInTable_ == *lastLexemInfoInTable)
				makePrepare4LeftParenthesis(lastLexemInfoInTable, lastTempLexemInfoInTable);

			if (lastLexemInfoInTable_ == *lastLexemInfoInTable)
				makePrepare4RightParenthesis(lastLexemInfoInTable, lastTempLexemInfoInTable);

			if (lastLexemInfoInTable_ != *lastLexemInfoInTable
				&& (!nullStatementIndex || (lexemInfoInTable + nullStatementIndex == lastLexemInfoInTable_))) {
				if (nullStatementIndex != ~0) {
					if (nullStatementIndex) {
						printf("Added null statement after %lld(lexem index)\r\n", nullStatementIndex);
						makePrepareEnder(lastLexemInfoInTable, lastTempLexemInfoInTable);
						(void)createMultiToken(lastTempLexemInfoInTable, MULTI_TOKEN_NULL_STATEMENT);
					}

					nullStatementIndex = getNextEndOfExpressionIndex(lexemInfoInTable, nullStatementIndex);
				}
			}

		}

		makePrepareEnder(lastLexemInfoInTable, lastTempLexemInfoInTable);

		if ((!nullStatementIndex || (lexemInfoInTable + nullStatementIndex == *lastLexemInfoInTable))) {
			if (nullStatementIndex != ~0) {
				if (nullStatementIndex) {
					printf("Added null statement after %lld(lexem index)\r\n", nullStatementIndex);
					makePrepareEnder(lastLexemInfoInTable, lastTempLexemInfoInTable);
					(void)createMultiToken(lastTempLexemInfoInTable, MULTI_TOKEN_NULL_STATEMENT);
				}

				nullStatementIndex = getNextEndOfExpressionIndex(lexemInfoInTable, nullStatementIndex);
			}
		}

	}
}