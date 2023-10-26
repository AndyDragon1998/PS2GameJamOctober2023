/*****************************************************************************/
/*  Автор         		: Дракончик				        					 */
/*  Приставка     		: Sony PlayStation 2								 */
/*  ОС			  		: OSDSYS				        					 */
/*  Язык	      		: GNU C                                       		 */
/*                                                                           */
/*  Содержимое файла	: Главний пкрсонаж	                       			 */
/*  Атрибут файла		: SOURCE                                      		 */
/*  Имя файла     		: player.c	                               			 */
/*                                                                           */
/*****************************************************************************/

#include "include/player.h"
#include "include/pad.h"
#include "include/overState.h"
#include "extern/player.ext"
#include <stdio.h>
#include <gsKit.h>
#include <dmaKit.h>
#include <gsToolkit.h>
#include "define/gameState.def"

#define PERSONFRONT "/Graphics/Characters/2.2.png"

extern StateMachine GameMachineState;
GSTEXTURE PlayerTexture;
GSTEXTURE playerImage;

void InitializePlayer(Player* player, GSGLOBAL* gsGlobal,struct Body* playerBody)
{
    player->X = 0;
	player->Y = 440;
    player->X2 = 20;
	player->Y2 = 480;
    player->U = 0.0f;
    player->isAlive;
    player->mass = playerBody->mass = 10;

	char tempu[4096];
	strcpy(tempu, relativePath);
	strcat(tempu, PERSONFRONT);
	gsKit_texture_png(gsGlobal, &playerImage,tempu);
}

void UpdatePlayer(Player* player, GSGLOBAL* gsGlobal, struct Body* playerBody)
{   
    if(PlaystationGamePad.LEFT_KEY_DOWN && player->X > 30 && player->X < 60){
         player->X -= playerBody->force.x = 5.0f;
         player->X2 -= playerBody->force.x = 5.0f;
	}else if( PlaystationGamePad.LEFT_KEY_DOWN && player->X >95 && player->X < 130){
            player->X -= playerBody->force.x = 5.0f;
            player->X2 -= playerBody->force.x = 5.0f;
    }else if( PlaystationGamePad.LEFT_KEY_DOWN && player->X >128 && player->X < 510 && player->Y > 430){
            player->X -= playerBody->force.x = 5.0f;
            player->X2 -= playerBody->force.x = 5.0f;
    }
    // else if(PlaystationGamePad.LEFT_KEY_DOWN && player->X > 30){
    //     player->X -= playerBody->force.x = 5.0f;
    //     player->X2 -= playerBody->force.x = 5.0f;
    // }

    // if(PlaystationGamePad.RIGHT_KEY_DOWN && player->X < 55 && player->X < 90 || player->X < 90 && player-> Y < 450){
    //         player->X += playerBody->force.x = 5.0f;
    //         player->X2 += playerBody->force.x = 5.0f;
	// }

     if(PlaystationGamePad.RIGHT_KEY_DOWN && player->X < 55 && player-> Y > 60){
            player->X += playerBody->force.x = 5.0f;
            player->X2 += playerBody->force.x = 5.0f;
	 }else if(PlaystationGamePad.RIGHT_KEY_DOWN && player->X > 10 && player-> Y < 60 && player->X < 120){
            player->X += playerBody->force.x = 5.0f;
            player->X2 += playerBody->force.x = 5.0f;
     }else if(PlaystationGamePad.RIGHT_KEY_DOWN && player->X > 90 && player-> Y > 60 && player->X < 120){
            player->X += playerBody->force.x = 5.0f;
            player->X2 += playerBody->force.x = 5.0f;
     }else if(PlaystationGamePad.RIGHT_KEY_DOWN && player->X > 110 && player->Y >430 && player->X < 500){
            player->X += playerBody->force.x = 5.0f;
            player->X2 += playerBody->force.x = 5.0f;
     }else if(PlaystationGamePad.RIGHT_KEY_DOWN && player->X2 > 180 && player->Y >130 && player->X2 < 210){
            player->X += playerBody->force.x = 5.0f;
            player->X2 += playerBody->force.x = 5.0f;
     }else if(PlaystationGamePad.RIGHT_KEY_DOWN && player->X2 > 180 && player->Y >110 && player->X2 < 300){
            player->X += playerBody->force.x = 5.0f;
            player->X2 += playerBody->force.x = 5.0f;
     }else if(PlaystationGamePad.RIGHT_KEY_DOWN && player->X2 > 280 && player->Y >70 && player->X2 < 500){
            player->X += playerBody->force.x = 5.0f;
            player->X2 += playerBody->force.x = 5.0f;
     }else if(PlaystationGamePad.RIGHT_KEY_DOWN && player->X2 > 500 ){
            player->X += playerBody->force.x = 5.0f;
            player->X2 += playerBody->force.x = 5.0f;
     }
    //  else if(){

    //  }

    // && player->X < 55 && player->X < 90 && player-> Y < 450
    // else if(PlaystationGamePad.RIGHT_KEY_DOWN && player->X < 135 && player-> Y < 60){
    //     player->X += playerBody->force.x = 5.0f;
    //     player->X2 += playerBody->force.x = 5.0f;
    // }
	if( PlaystationGamePad.UP_KEY_DOWN && player->X2 > 30 && player->Y > 30 &  player->X2 < 80){
        player->Y -= playerBody->force.y = 2.0f;
         player->Y2 -= playerBody->force.y = 2.0f;
    }else if( PlaystationGamePad.UP_KEY_DOWN && player->X2 > 180 && player->Y > 130 &&  player->X2 < 300){
        player->Y -= playerBody->force.y = 2.0f;
         player->Y2 -= playerBody->force.y = 2.0f;
    }else if( PlaystationGamePad.UP_KEY_DOWN && player->X2 > 280 && player->Y >70 &&  player->X2 < 300){
        player->Y -= playerBody->force.y = 2.0f;
         player->Y2 -= playerBody->force.y = 2.0f;
    }

    if(PlaystationGamePad.DOWN_KEY_DOWN && player->Y2 < 480){
         player->Y += playerBody->force.y = 2.0f;
         player->Y2 += playerBody->force.y = 2.0f;
	}else if(PlaystationGamePad.DOWN_KEY_DOWN && player->Y2 < 440){
         player->Y += playerBody->force.y = 2.0f;
         player->Y2 += playerBody->force.y = 2.0f;
	}
    if(player->X2 > 600 && player->Y2 > 470){
        StateMachineChange(&GameMachineState, &OverState, gsGlobal);
    }

}

void DrawPlayer(Player* player, GSGLOBAL* gsGlobal, u64 colour,struct Body* playerBody)
{
    gsKit_prim_sprite_texture(gsGlobal, &playerImage, player->X ,  // X1
						player->Y,  // Y2
						0.0f,  // U1
						0.0f,  // V1
						player->X2, // X2
						player->Y2, // Y2
						playerImage.Width * 2, // U2
						playerImage.Height * 2, // V2
						2,
						colour);
}
