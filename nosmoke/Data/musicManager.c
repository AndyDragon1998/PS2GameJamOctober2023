/*****************************************************************************/
/*  Author        : Дракончик												 */
/*  Machine       : Sony PlayStation 2										 */
/*  OS		  	  : OSDSYS													 */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : INGAME MUSIC MANAGER AND PLAYER						     */
/*  File Attribute: SOURCE                                                   */
/*  File Name     : musicManager.c                                           */
/*                                                                           */
/*****************************************************************************/

#include "include/musicManager.h"
#include "define/backgroundMusic.def"

extern unsigned int size_audsrv_irx;
extern unsigned char audsrv_irx[];

char loopChunk[2048];

int LoopingPart;

struct audsrv_fmt_t musicFormat;

void initMusicFormat()
{
	musicFormat.bits = 16;
	musicFormat.freq = 44100;
	musicFormat.channels = 2;
}

void LoadMusic(BGM *bgm)
{	
	bgm->ret = audsrv_init();
	
	char temp[4096];
	strcpy(temp, bgm->fileName);
	strcat(temp, "_Intro.wav");
	
	if (bgm->ret != 0)
	{
		printf("sample: failed to initialize audsrv\n");
		printf("audsrv returned error string: %s\n", audsrv_get_error_string());
		return 1;
	}

	audsrv_set_volume(MAX_VOLUME);
	LoopingPart = 0;
	
	if(!(bgm->wav = fopen(temp, "rb")))
	{
		char tempt[4096];
		strcpy(tempt, bgm->fileName);
		strcat(tempt, "_Loop.wav");
		LoopingPart = 1;
	}
	
	if (bgm->wav == NULL)
	{
		printf("failed to open wav file\n");
		audsrv_quit();
		return 1;
	}

	fseek(bgm->wav, 22, SEEK_SET);
    fread(&musicFormat.channels, 2, 1, bgm->wav);
    rewind(bgm->wav);

    fseek(bgm->wav, 24, SEEK_SET);
    fread(&musicFormat.freq, 4, 1, bgm->wav);
    rewind(bgm->wav);

    fseek(bgm->wav, 34, SEEK_SET);
    fread(&musicFormat.bits, 2, 1, bgm->wav);
    rewind(bgm->wav);
	
	fseek(bgm->wav, 0x30, SEEK_SET);
	
	bgm->err = audsrv_set_format(&musicFormat);
	
}
	
void PlayMusic(BGM *bgm)
{
	bgm->ret = fread(bgm->chunk, 1, sizeof(bgm->chunk), bgm->wav);

	if(LoopingPart == 0 && feof(bgm->wav))
	{
		bgm->ret = 0;
		char temp[4096];
		strcpy(temp, bgm->fileName);
		strcat(temp, "_Loop.wav");
	
		if (bgm->ret != 0)
		{
			printf("sample: failed to initialize audsrv\n");
			printf("audsrv returned error string: %s\n", audsrv_get_error_string());
			return 1;
		}

		audsrv_set_volume(MAX_VOLUME);

		bgm->wav = fopen(temp, "rb");
		
		bgm->ret = fread(bgm->chunk, 1, sizeof(bgm->chunk), bgm->wav);
		LoopingPart = 1;
	}
	
	if(LoopingPart == 1 && feof(bgm->wav))
	{
		fseek(bgm->wav, 0, SEEK_SET);
	}
	if (bgm->ret > 0)
	{
		audsrv_wait_audio(bgm->ret);
		audsrv_play_audio(bgm->chunk, bgm->ret);
	}
	
}

void UnloadMusic(BGM *bgm)
{
	fclose(bgm->wav);

	printf("sample: stopping audsrv\n");
	//audsrv_quit();

	printf("sample: ended\n");

}

char* PickMusic(int BGMTrack)
{
	switch(BGMTrack)
	{
		case 0:
			return "";
		break;
		case 1:
			return BGM001;
		break;
		case 2:
			return BGM002;
		break;
		case 3:
			return BGM003;
		break;
		case 4:
			return BGM004;
		break;
		case 5:
			return BGM005;
		break;
		case 6:
			return BGM006;
		break;
		case 7:
			return BGM007;
		break;
		case 8:
			return BGM008;
		break;
		case 9:
			return BGM009;
		break;
		case 10:
			return BGM010;
		break;
		case 11:
			return BGM011;
		break;
		case 12:
			return BGM012;
		break;
		case 13:
			return BGM013;
		break;
		case 14:
			return BGM014;
		break;
		case 15:
			return BGM015;
		break;
		case 16:
			return BGM016;
		break;
		case 17:
			return BGM017;
		break;
		case 18:
			return BGM018;
		break;
		case 19:
			return BGM019;
		break;

	}
}


