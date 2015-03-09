#include "PoundDefs.h"

#ifdef WINDOWS
#include <iostream>
#include "dsutil.h"
#include "dxaudio.h"
#include "dxutil.h"
using namespace std;

#endif

#ifdef SDL
#include "SDL/SDL_mixer.h"
#endif

class SpecSound
{
private: 
#ifdef WINDOWS
	CSound *junk[6];
#endif
#ifdef SDL
	Mix_Chunk *junk[6];
#endif
public:
	SpecSound();
	void Init();
	void PlaySpecSound(int x);
};