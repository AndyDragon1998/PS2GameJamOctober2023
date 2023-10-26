#include "include/level1State.h"
#include "include/level2State.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/gameState.h"
#include "include/introState.h"
#include "include/pad.h"
#include "include/musicManager.h"


extern StateMachine GameMachineState;

/****** User External Files ********/
#include "extern/level1State.ext"

/****** User Table Files ***********/


/****** User Define Files ***********/
#include "define/level1State.def"
#include "define/backgroundMusic.def"


GSTEXTURE Change;
GSTEXTURE kA;
GSTEXTURE kC;
int part1;

BGM Men;

void level1Start(GSGLOBAL* gsGlobal)
{
	initMusicFormat();
	char temp[4096];
	strcpy(temp, relativePath);
	strcat(temp, PickMusic(3));
	Men.fileName = temp;
	LoadMusic(&Men);
	

	char temp1[4096];
	strcpy(temp1, relativePath);
	strcat(temp1, CHANGEWINDOW);
	gsKit_texture_png(gsGlobal, &Change,temp1);
	
	char tempk1[4096];
	strcpy(tempk1, relativePath);
	strcat(tempk1, A);
	gsKit_texture_png(gsGlobal, &kA,tempk1);
	
	char tempk3[4096];
	strcpy(tempk3, relativePath);
	strcat(tempk3, C);
	gsKit_texture_png(gsGlobal, &kC,tempk3);
	
	
	SetUpFont(gsGlobal);
	part1 = 1;
}

void level1Update(GSGLOBAL* gsGlobal)
{
		PlayMusic(&Men);
    		if(PlaystationGamePad.UP_KEY_TAP)
    		{
    					if (part1!=1 && part1!=8 && part1!= 11 && part1!=14)  part1--; 
    		}
    		else if(PlaystationGamePad.DOWN_KEY_TAP )
    		{
    					if(part1!=7 && part1!= 10 && part1!=13 && part1!=14)part1++;
    		}
    		if(PlaystationGamePad.BUTTON_X_KEY_TAP)
    		{	
			switch(part1)
			{
				// CHANGE PART
				case 5:
					part1=8;
				break;

				case 6:
					part1=11;
				break;
				case 7:
					part1=14;
				break;
				
				default:
			
			}
		}
		if(PlaystationGamePad.START_KEY_TAP){
			switch(part1){
					case 10:
						StateMachineChange(&GameMachineState, &level2State, gsGlobal);
					break;
					case 13:
						StateMachineChange(&GameMachineState, &OverState, gsGlobal);
					break;
					case 14:
					StateMachineChange(&GameMachineState, &OverState, gsGlobal);
					break;
			}
	}
}

void level1Draw(GSGLOBAL* gsGlobal, u64 colour)
{
		
		gsKit_prim_sprite_texture(gsGlobal, &Change,0,  // X1
						0,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						Change.Width * 2, // X2
						Change.Height * 2, // Y2
						Change.Width * 2, // U2
						Change.Height * 2, // V2
						2,
						colour);
		gsKit_prim_sprite_texture(gsGlobal, &kC,150,  // X1
						100,  // Y1
						0.0f,  // U1
						0.0f,  // V1
						kC.Width*2, // X2
						kC.Height*2, // Y2
						kC.Width*2, // U2
						kC.Height*2, // V2
						2,
						colour);
		gsKit_prim_sprite_texture(gsGlobal, &kA,170,  // X1
						170,  // Y1
						0.0f,  // U1
						0.0f,  // V1
						kA.Width*4, // X2
						kA.Height*4, // Y2
						kA.Width*2, // U2
						kA.Height*2, // V2
						2,
						colour);
		
		
		switch(part1){
		case 1:
		DrawText(0, 360, "GFHR <SK YFCNJZOBV HFTV",2, gsGlobal, &colour,1);
		DrawText(0, 400, "D YTV <SKF CJ<HFYF DCZ AKJHF",2, gsGlobal, &colour,1);
		break;
		case 2:
		DrawText(0, 360, "RJNZNF DTCTKBKBCM",2, gsGlobal, &colour,1);
		DrawText(0, 400, "CFYYB PFBUHFKFCM",2, gsGlobal, &colour,1);
		DrawText(0, 440, "B JNJIKF JN CDJB{ <HFNMTD",2, gsGlobal, &colour,1);
		break;
		case 3:
		DrawText(0, 360, "JYF ECKSIFKF JNLFKTYYSQ",2, gsGlobal, &colour,1);
		DrawText(0, 400, "GKFXM",2, gsGlobal, &colour,1);
		DrawText(0, 440, "GHJQLZ XENM LFKMIT",2, gsGlobal, &colour,1);
		break;
		case 4:
		DrawText(0, 360, "JYF EDBLTKF RFR PKST RJNS",2, gsGlobal, &colour,1);
		DrawText(0, 400, "BPLTDFKBCM YFL RJNTYRJV",2, gsGlobal, &colour,1);
		break;
		case 5:
		DrawText(50,320, "JYF HTIBKF",2, gsGlobal, &colour,1);
		DrawText(0, 360, "GJVJXM RJNTYRE",2, gsGlobal, &colour,1);
		DrawText(0, 400, "C<T:FNM",2, gsGlobal, &colour,0);
		DrawText(0, 440, "GHBCJTLTYBNCZ R YFRFPFYB>",2, gsGlobal, &colour,0);
		break;
		case 6:
		DrawText(50,320, "JYF HTIBKF",2, gsGlobal, &colour,1);
		DrawText(0, 360, "GJVJXM RJNTYRE",2, gsGlobal, &colour,0);
		DrawText(0, 400, "C<T:FNM",2, gsGlobal, &colour,1);
		DrawText(0, 440, "GHBCJTLTYBNCZ R YFRFPFYB>",2, gsGlobal, &colour,0);
		break;
		case 7:
		DrawText(50,320, "JYF HTIBKF",2, gsGlobal, &colour,1);
		DrawText(0, 360, "GJVJXM RJNTYRE",2, gsGlobal, &colour,0);
		DrawText(0, 400, "C<T:FNM",2, gsGlobal, &colour,0);
		DrawText(0, 440, "GHBCJTLTYBNCZ R YFRFPFYB>",2, gsGlobal, &colour,1);
		break;
		case 8:
		DrawText(0, 360, "DJ DHTVZ ZHJCNYJQ GJNFCJDRB",2, gsGlobal, &colour,1);
		DrawText(0, 400, "<SKB E<BNS XKTYS <FYLS",2, gsGlobal, &colour,1);
		DrawText(0, 440, "LBRJUJ RJUNZ",2, gsGlobal, &colour,1);
		break;
		case 9:
		DrawText(0, 360, "GHBXBYJQ CVTHNB CNFKB HDFYST",2, gsGlobal, &colour,1);
		DrawText(0, 400, "HFYS D  J<KFCNB CGBYS KBWF",2, gsGlobal, &colour,1);
		DrawText(0, 440, "B ZBW",2, gsGlobal, &colour,1);
		break;
		case 10:
		DrawText(0, 360, "VFKTYMRBQ RJNTYJR",2, gsGlobal, &colour,1);
		DrawText(0, 400, "GJ<KFUJLFHBK CFYYB B E<T:FK",2, gsGlobal, &colour,1);
		DrawText(0, 440, "F CFYYB DTHYEKFCM R <HFNMZV",2, gsGlobal, &colour,1);
		DrawText(0, 0, "GHJLJK:BNM CNFHN",2, gsGlobal, &colour,1);
		break;
		case 11:
		DrawText(0, 360, "DS C<TUFTNT RFR ",2, gsGlobal, &colour,1);
		DrawText(0, 400, "NHECKBDFZ NHZGRF",2, gsGlobal, &colour,1);
		DrawText(0, 440, "XBNFZ YJDJCNB DS EPYFTNT",2, gsGlobal, &colour,1);
		break;
		case 12:
		DrawText(0, 360, "XNJ VFKTYMRBQ RJNTYJR",2, gsGlobal, &colour,1);
		DrawText(0, 400, "<SK PF<BN LJ CVTHNB",2, gsGlobal, &colour,1);
		DrawText(0, 440, "CFYYB PFRHSDFTNCZ D CT<T",2, gsGlobal, &colour,1);
		break;
		case 13:
		DrawText(0, 360, "DCRJHT DS JCNFTNTCM CJDCTV JLBY",2, gsGlobal, &colour,1);
		DrawText(0, 440, "PFDTHIBNM BUHE YF RYJGRE CNFHN",2, gsGlobal, &colour,1);
		break;
		case 14:
		DrawText(0, 360, "E<BD RJNTYRF B YFLHEUFDIBCM",2, gsGlobal, &colour,1);
		DrawText(0, 400, "YFL TUJ NHEGJV",2, gsGlobal, &colour,1);
		DrawText(0, 440, "DCRJHT DFIB <HFNMZ DSUJYZ>N DFC",2, gsGlobal, &colour,1);
		DrawText(0, 0, "PFDTHIBNM BUHE YF RYJGRE CNFHN",2, gsGlobal, &colour,1);
		break;
		}
		
}

void level1End(GSGLOBAL* gsGlobal)
{
	gsKit_vram_clear(gsGlobal);
	UnloadMusic(&Men);
}

StateManager level1State =
{
	level1Start,
	level1Update,
	level1Draw,
	level1End
};
