#ifndef Sound_h


extern LPDIRECTSOUND8 Ds;


int g_InitDs(void);
int g_GetWaveInfo(HMMIO mfile ,WAVEFORMATEX* wavf ,int* size);
int g_ReadWaveData(HMMIO mfile ,void* buffer);
LPDIRECTSOUNDBUFFER g_CreateBufferFromFileA(char* file);


class g_NSound
{
private:
	LPDIRECTSOUNDBUFFER buffer;

public:
	void PlaySound(void);
	int InitNSound(char* file);
};


#endif
#define Sound_h