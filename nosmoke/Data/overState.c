/*****************************************************************************/
/*  Автор         		: Дракончик				                             */
/*  Приставка     		: Sony PlayStation 2					             */
/*  ОС			  		: OSDSYS											 */
/*  Язык	      		: GNU C                                              */
/*                                                                           */
/*  Содержимое файла	: Стадия завершение Игри	                         */
/*  Атрибут файла		: SOURCE                                             */
/*  Имя файла     		: overState.c	                                     */
/*                                                                           */
/*****************************************************************************/

#include "include/gameState.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/introState.h"

extern StateMachine GameMachineState;

void OverStart(GSGLOBAL* gsGlobal)
{

}

void OverUpdate(GSGLOBAL* gsGlobal)
{

}

void OverDraw(GSGLOBAL* gsGlobal, u64 colour)
{

}

void OverEnd(GSGLOBAL* gsGlobal)
{

}

StateManager OverState =
{
	OverStart,
	OverUpdate,
	OverDraw,
	OverEnd
};
