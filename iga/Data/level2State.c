#include "include/level2State.h"
#include "include/menuState.h"
#include "include/overState.h"
#include "include/gameState.h"
#include "include/introState.h"
#include "include/pad.h"
#include "include/musicManager.h"


extern StateMachine GameMachineState;

/****** User External Files ********/
#include "extern/level2State.ext"

/****** User Table Files ***********/


/****** User Define Files ***********/
#include "define/level2State.def"


GSTEXTURE l2back;
int part2;
GSTEXTURE k1;
GSTEXTURE k2;
GSTEXTURE k3;

BGM Me;


void level2Start(GSGLOBAL* gsGlobal)
{
	initMusicFormat();
	char temp[4096];
	strcpy(temp, relativePath);
	strcat(temp, PickMusic(3));
	Me.fileName = temp;
	LoadMusic(&Me);

	char temp2[4096];
	strcpy(temp2, relativePath);
	strcat(temp2, L2BACKGR);
	gsKit_texture_png(gsGlobal, &l2back,temp2);
	
	char tempk1[4096];
	strcpy(tempk1, relativePath);
	strcat(tempk1, A);
	gsKit_texture_png(gsGlobal, &k1,tempk1);
	
	char tempk2[4096];
	strcpy(tempk2, relativePath);
	strcat(tempk2, B);
	gsKit_texture_png(gsGlobal, &k2,tempk2);
	
	SetUpFont(gsGlobal);

	part2 = 1;
}

void level2Update(GSGLOBAL* gsGlobal)
{
    		PlayMusic(&Me);
		if(PlaystationGamePad.UP_KEY_TAP)
    		{
    		if(part2 != 0 && part2 != 10 && part2 != 12 && part2 != 16)	part2--;
    		}
    		else if(PlaystationGamePad.DOWN_KEY_TAP)
    		{
    		if(part2!= 15 && part2 != 11 && part2 != 17)	part2++;
    		}
    		if(PlaystationGamePad.BUTTON_X_KEY_TAP)
    		{	
			switch(part2)
			{
				// CHANGE PART
				case 7:
					part2=10;
				break;
				case 8:
					part2 = 12;
				break;
				case 9:
					part2 = 16;
				break;
				
			}
		}
		if(PlaystationGamePad.START_KEY_TAP){
			switch(part2){
				case 11:
					StateMachineChange(&GameMachineState, &MenuState, gsGlobal);
				break;
				case 15:
					StateMachineChange(&GameMachineState, &OverState, gsGlobal);
				break;
				case 17:
					StateMachineChange(&GameMachineState, &MenuState, gsGlobal);
				break;
			}
	}
}

void level2Draw(GSGLOBAL* gsGlobal, u64 colour)
{
		gsKit_prim_sprite_texture(gsGlobal, &l2back,0,  // X1
						0,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						l2back.Width * 2, // X2
						l2back.Height * 2, // Y2
						l2back.Width * 2, // U2
						l2back.Height * 2, // V2
						2,
						colour);
		gsKit_prim_sprite_texture(gsGlobal, &k1,170,  // X1
						170,  // Y1
						0.0f,  // U1
						0.0f,  // V1
						k1.Width*4, // X2
						k1.Height*4, // Y2
						k1.Width*2, // U2
						k1.Height*2, // V2
						2,
						colour);
		
		gsKit_prim_sprite_texture(gsGlobal, &k2,150,  // X1
						100,  // Y1
						0.0f,  // U1
						0.0f,  // V1
						k2.Width*2, // X2
						k2.Height*2, // Y2
						k2.Width*2, // U2
						k2.Height*2, // V2
						2,
						colour);
		
						
		// Street				
		switch(part2){
		case 1:
		DrawText(0, 360, "GHBLZ D UJHJL RJNZNF EDBLTKB",2, gsGlobal, &colour,1);
		DrawText(0, 400, "GKFRFNS VZEWBCNJD",2, gsGlobal, &colour,1);
		DrawText(0, 440, "C GHTLDJHBNTKMCDJV RFNJKMAF UBNKTHF",2, gsGlobal, &colour,1);
		break;
		case 2:
		DrawText(0, 360, "RJNZNF HTIF>N GJCTNBNM LJV GFHNBB",2, gsGlobal, &colour,1);
		DrawText(0, 400, "GHBLZ R PLFYB> DS CKSIFNT",2, gsGlobal, &colour,1);
		DrawText(0, 440, "DJCNJH:FYSQ VZEWBCNJD",2, gsGlobal, &colour,1);
		break;
		case 3:
		DrawText(0, 360, "PBR VZJ",2, gsGlobal, &colour,0);
		DrawText(0, 400, "PFQLZ D PLFYBT",2, gsGlobal, &colour,1);
		DrawText(0, 440, "DS CKSIFNT DJCNJH:FYYE>",2, gsGlobal, &colour,1);
		DrawText(0, 480, "HTXM J DTKBXBB VZJWBCNRJQ GFHNBB",2, gsGlobal, &colour,1);
		break;
		case 4:
		DrawText(0, 360, "GFHNBZ GHBPTHFTN RJNJD CABYRCJD",2, gsGlobal, &colour,1);
		DrawText(0, 400, "JNCENCNDBT DJKJCZYJ GJRHJDF DSPDFKJ",2, gsGlobal, &colour,1);
		DrawText(0, 440, "J<BKMYE> YTYFDBCNM GHJXTUJ",2, gsGlobal, &colour,1);
		break;
		case 5:
		DrawText(0, 360, "RJIFXTUJ VBHF",2, gsGlobal, &colour,1);
		DrawText(0, 400, "<KFUJLFHZ XTVE VYJUBT GJLLTH:FKB",2, gsGlobal, &colour,1);
		DrawText(0, 440, "RJNCWSCNJD",2, gsGlobal, &colour,1);
		break;
		case 6:
		DrawText(0, 360, "GHJCKEIFD GKFVTYYE> HTXM",2, gsGlobal, &colour,1);
		DrawText(0, 400, "RJNZNF HTIF>N",2, gsGlobal, &colour,1);
		break;
		case 7:
		DrawText(50, 300, "RJNZNF HTIF>N",2, gsGlobal, &colour,1);
		DrawText(0, 360, "DCNEGBNM D GFHNB>",2, gsGlobal, &colour,1);
		DrawText(0, 400, "GJLLTH:FNM GFHNB> CABYRNTHJD",2, gsGlobal, &colour,0);
		DrawText(0, 440, "GTHT<BNM VZJWBCNJD",2, gsGlobal, &colour,0);
		break;
		case 8:
		DrawText(50, 300, "RJNZNF HTIF>N",2, gsGlobal, &colour,1);
		DrawText(0, 360, "DCNEGBNM D GFHNB>",2, gsGlobal, &colour,0);
		DrawText(0, 400, "GJLLTH:FNM GFHNB> CABYRNTHJD",2, gsGlobal, &colour,1);
		DrawText(0, 440, "GTHT<BNM VZJWBCNJD",2, gsGlobal, &colour,0);
		break;
		case 9:
		DrawText(50, 300, "RJNZNF HTIF>N",2, gsGlobal, &colour,1);
		DrawText(0, 360, "DCNEGBNM D GFHNB>",2, gsGlobal, &colour,0);
		DrawText(0, 400, "GJLLTH:FNM GFHNB> CABYRNTHJD",2, gsGlobal, &colour,0);
		DrawText(0, 440, "GTHT<BNM VZJWBCNJD",2, gsGlobal, &colour,1);
		break;
		case 10:
		DrawText(0, 360, "DCNEGBD D GFHNB>",2, gsGlobal, &colour,1);
		DrawText(0, 400, "JYB <SCNHJ LJ<BDF>NCZ DSCJN",2, gsGlobal, &colour,1);
		DrawText(0, 440, "DCRJHT RF:LJVE BP RJNJD",2, gsGlobal, &colour,1);
		break;
		case 11:
		DrawText(0, 0, "LKZ PFDTHITYBZX YF:VBNT CNFHN",2, gsGlobal, &colour,1);
		DrawText(0, 360, "DSLFTN VTLFKM KBXYJ RFNJKMA UBNKTH",2, gsGlobal, &colour,1);
		DrawText(0, 400, "PF NJ XJN JYB GHBLEVFKB",2, gsGlobal, &colour,1);
		DrawText(0, 440, "EKMNHFABJKTNJDST RFVTHS GHJNBD",2, gsGlobal, &colour,1);
		DrawText(0, 480, "DCTUJ CABYCRJUJ HJLF",2, gsGlobal, &colour,1);
		break;
		case 12:
		DrawText(0, 360, "JNRBYED CJVYTYBZ RJNZNF",2, gsGlobal, &colour,1);
		DrawText(0, 400, "JNGHFDBKBCM DCNEGFNM D",2, gsGlobal, &colour,1);
		DrawText(0, 440, "GFHNB> CABYRCJD",2, gsGlobal, &colour,1);
		break;
		case 13:
		DrawText(0, 360, "DCNEGFZ D GFHNB> JYB",2, gsGlobal, &colour,1);
		DrawText(0, 400, "GJ<HBKBCM YFKSCJ",2, gsGlobal, &colour,1);
		DrawText(0, 440, "B JNGHFDBKBCM YF",2, gsGlobal, &colour,1);
		break;
		case 14:
		DrawText(0, 360, "DJQYE C VZEWBCNFVB",2, gsGlobal, &colour,1);
		DrawText(0, 400, "GJ BNJUE JLYJQ BP DSKFPJR",2, gsGlobal, &colour,1);
		DrawText(0, 440, "CFYYB JNJHDFKJ YJUE",2, gsGlobal, &colour,1);
		break;
		case 15:
		DrawText(0, 0, "LKZ PFDTHITYBZX YF:VBNT CNFHN",2, gsGlobal, &colour,1);
		DrawText(0, 360, "CDTNKFZ GFVZNM CFYT",2, gsGlobal, &colour,1);
		DrawText(0, 400, "",2, gsGlobal, &colour,1);
		DrawText(0, 440, "GJKEXTYF JXBDRF CFYZ YT YFLJ",2, gsGlobal, &colour,1);
		break;
		case 16:
		DrawText(0, 360, "D :TCNJQ <JQYT",2, gsGlobal, &colour,1);
		DrawText(0, 400, "<SKB E<BNS DCT VZEWBCNS",2, gsGlobal, &colour,1);
		DrawText(0, 440, "NTGTHM RJNKFLBTIM GHFDBN",2, gsGlobal, &colour,1);
		break;
		case 17:
		DrawText(0, 0, "LKZ PFDTHITYBZX YF:VBNT CNFHN",2, gsGlobal, &colour,1);
		DrawText(0, 360, "NJKTHFYNYJCNM B KR<N",2, gsGlobal, &colour,1);
		DrawText(0, 400, "NTGTHM RJNZNFV HTUEKZHYJ",2, gsGlobal, &colour,1);
		DrawText(0, 440, "EDTKBXBDF>N HTPM<E",2, gsGlobal, &colour,1);
		DrawText(0, 480, "YJ JYB YT YE:LF>NCZ YB D XTV",2, gsGlobal, &colour,1);
		break;
		}
}


void level2End(GSGLOBAL* gsGlobal)
{
gsKit_vram_clear(gsGlobal);
UnloadMusic(&Me);
}

StateManager level2State =
{
	level2Start,
	level2Update,
	level2Draw,
	level2End
};
