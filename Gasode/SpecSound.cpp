#include "dsutil.h"
#include "dxaudio.h"
#include "dxutil.h"
#include "SpecSound.h"


extern HWND g_hWnd;
SpecSound::SpecSound()
{

}
void SpecSound::Init()
{
#ifdef WINDOWS
	if (!Init_DirectSound(g_hWnd))
	{
		MessageBox(g_hWnd, "Error initializing DirectSound", "Error", MB_OK);
		return;
	}
	// Load sound takes 2 arguments. First one is filename, second one is number of buffers free.
	junk[0] = LoadSound("Sound\\blaster.wav", 10);
	junk[1] = LoadSound("Sound\\battle003.wav", 5);
	junk[2] = LoadSound("Sound\\boom.wav",2);
	junk[3] = LoadSound("Sound\\SmallExplosion.wav", 5);
	junk[4] = LoadSound("Sound\\shot1.wav", 20);
#endif
#ifdef SDL             
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 500 ) == -1 )
	{
		/* return false; */   
	}
	for(int i = 0; i < 11; i++)
	{
		junk[0] = NULL;
	}
	junk[0] = Mix_LoadWAV("Sound\\blaster.wav");
	junk[1] = Mix_LoadWAV("Sound\\battle003.wav");
	junk[2] = Mix_LoadWAV("Sound\\boom.wav");;
	junk[3] = Mix_LoadWAV("Sound\\SmallExplosion.wav");
	junk[4] = Mix_LoadWAV("Sound\\shot1.wav");
#endif

}

void SpecSound::PlaySpecSound(int x)
{
#ifdef WINDOWS
	junk[x]->Play();
#endif
#ifdef SDL
	Mix_PlayChannel( -1, junk[x], 0 );
#endif
}
