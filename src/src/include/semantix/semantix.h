#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024 // lex  +  rpn  +  MACHINECODEGEN!   *
*                         file: semantix.h                  *
*                                                  (draft!) *
*************************************************************/


#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"

#define COLLISION_II_STATE 128
#define COLLISION_LL_STATE 129
#define COLLISION_IL_STATE 130
#define COLLISION_I_STATE  132
#define COLLISION_L_STATE  133

#define NO_IMPLEMENT_CODE_STATE 256

int checkingInternalCollisionInDeclarations(/*TODO: add arg*/);
int checkingVariableInitialization(/*TODO: add args*/);
int checkingCollisionInDeclarationsByKeyWords(/*TODO: add args*/);