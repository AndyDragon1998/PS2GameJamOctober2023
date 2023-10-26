/*****************************************************************************/
/*  Автор         		: Дракончик				                             */
/*  Приставка     		: Sony PlayStation 2		        	*/
/*  ОС			  		: OSDSYS											 */
/*  Язык	      		: GNU C                                      */
/*                                                                           */
/*  Содержимое файла	: Стадия игровой детельности                         */
/*  Атрибут файла		: SOURCE                                     */
/*  Имя файла     		: gameState.c	                             */
/*                                                                           */
/*****************************************************************************/

#include "include/gameState.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/level1State.h"
#include "include/introState.h"
#include "include/pad.h"
#include "include/musicManager.h"
#include "include/level2State.h"


extern StateMachine GameMachineState;

/****** User External Files ********/
#include "extern/gameState.ext"

/****** User Table Files ***********/


/****** User Define Files ***********/
#include "define/gameState.def"

int part;

GSTEXTURE GameBG;
BGM MikuSong;


void GameStart(GSGLOBAL* gsGlobal)
{
	initMusicFormat();
	char temp[4096];
	strcpy(temp, relativePath);
	strcat(temp, PickMusic(3));
	MikuSong.fileName = temp;
	
	LoadMusic(&MikuSong);

	
	char tempy[4096];
	strcpy(tempy, relativePath);
	strcat(tempy, GIRLBGIMAGE);
	gsKit_texture_png(gsGlobal, &GameBG,tempy);
	
	
	SetUpFont(gsGlobal);
	part = 1;
}

void GameUpdate(GSGLOBAL* gsGlobal)
{
	// This part here plays the music
		PlayMusic(&MikuSong);
		if(PlaystationGamePad.UP_KEY_TAP && part != 1)
    		{
    		part--;
    		}
    		else if(PlaystationGamePad.DOWN_KEY_TAP && part!= 10)
    		{
    		part++;
    		}
    		if(PlaystationGamePad.BUTTON_X_KEY_TAP)
    		{	
		switch(part)
		{
			// Start New Game
			case 9:
				StateMachineChange(&GameMachineState, &level1State, gsGlobal);
			break;

			case 10:
				StateMachineChange(&GameMachineState, &level2State, gsGlobal);
			break;
			
			default:
			
		}
	}
    		
	
    			
}

void GameDraw(GSGLOBAL* gsGlobal, u64 colour)
{
		
		gsKit_prim_sprite_texture(gsGlobal, &GameBG,0,  // X1
						0,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						GameBG.Width * 2, // X2
						GameBG.Height * 2, // Y2
						GameBG.Width * 2, // U2
						GameBG.Height * 2, // V2
						2,
						colour);	
						
		//Вступительный мнолог				
		switch(part){
		case 1: 
			DrawText(0, 360, "D E>NYJV LJVBRT YF JRHFQYT UJHJLF",2, gsGlobal, &colour,1);
			DrawText(0, 400, ":BKB NHB RJNTYRF",2, gsGlobal, &colour,1);
			
		break;
		case 2:
			DrawText(0, 360, "GTHDSQ AHTQ <SK YTVYJUJ GEUKBDSV",2, gsGlobal, &colour,1);
			DrawText(0, 400, "JY DCTULF CVJNHTK YF VBH <JKMIBVB",2, gsGlobal, &colour,1);
			DrawText(0, 440, "RHEUKSVB UFKPFVB",2, gsGlobal, &colour,1);
		break;
		case 3:
			DrawText(0, 360, "YT CVJNHZ YF CDJQ HJ<RBQ {FHFRNTH",2, gsGlobal, &colour,1);
			DrawText(0, 400, "JY K><BK GJBUHFNM CJ CDJBVB",2, gsGlobal, &colour,1);
			DrawText(0, 440, "BUHEIRFVB B GJUJYZNM <F<JXTR D CFLE",2, gsGlobal, &colour,1);
		break;
		case 4:
			DrawText(0, 360, "DNJHJQ CFNEHY <JKTT FRNBDYSQ",2, gsGlobal, &colour,1);
			DrawText(0, 400, "XTV LHEUBT RJNZNF",2, gsGlobal, &colour,1);
			DrawText(0, 440, "JY K><BK CCKTLJDFNM RF:LSQ EUJKJR",2, gsGlobal, &colour,1);
		break;
		case 5:
			DrawText(0, 360, "UJYZKCZ PF K><JQ BUHEIRJQ",2, gsGlobal, &colour,1);
			DrawText(0, 400, "GJGJLFDITQCZ YF TUJ GENB",2, gsGlobal, &colour,1);
		break;
		case 6:
			DrawText(0, 360, "NHTNMZ CFYYB <SK CFVSV CVTKSV",2, gsGlobal, &colour,1);
			DrawText(0, 400, "JYF DCTULF <SKF GTHDJQ",2, gsGlobal, &colour,1);
			DrawText(0, 440, "RNJ GHJ<ETN XNJNJ YJDJT",2, gsGlobal, &colour,1);
		break;
		case 7: 
			DrawText(0, 360, "<ELM NJ CGFQC",2, gsGlobal, &colour,1);
			DrawText(0, 400, "VTNFYABNFVB UFYL:E<FC",2, gsGlobal, &colour,1);
			DrawText(0, 440, "BKB LHEUBT YFHRJNBRB",2, gsGlobal, &colour,1);
		break;
		case 8: 
			DrawText(0, 360, "B JLYF:LS JYB HTIBKB",2, gsGlobal, &colour,1);
			DrawText(0, 400, "JNGHFDBNMCZ D GENTITCNDBT",2, gsGlobal, &colour,1);
		break;
		case 9: 
			DrawText(0, 360, "JNGHFDBNMCZ D GFHR",2, gsGlobal, &colour,1);
			DrawText(0, 400, "JNGHFDBNMCZ D UJHJL",2, gsGlobal, &colour,0);
		break;
		case 10: 
			DrawText(0, 360, "JNGHFDBNMCZ D GFHR",2, gsGlobal, &colour,0);
			DrawText(0, 400, "JNGHFDBNMCZ D UJHJL",2, gsGlobal, &colour,1);
		break;
		default:
		}
			
}


void GameEnd(GSGLOBAL* gsGlobal)
{
	printf("This should Run when MenuState is Gone.\n");
	// Clear VRAM after the Menu is done~
	gsKit_vram_clear(gsGlobal);
	UnloadMusic(&MikuSong);
}

StateManager GameState =
{
	GameStart,
	GameUpdate,
	GameDraw,
	GameEnd
};
