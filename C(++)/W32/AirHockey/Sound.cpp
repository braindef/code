#include "GDef.h"
#include "Utilities.h"
#include "Sound.h"


LPDIRECTSOUND8				Ds;


int g_InitDs(void)
{
	int r = 0;	

	r = DirectSoundCreate8(NULL ,&Ds ,NULL);	
		if(FAILED(r)) g_FailBox(1,"Failed to create Direct Sound Object!");	

	r = Ds->SetCooperativeLevel(Hwnd ,DSSCL_EXCLUSIVE); 
		if(FAILED(r)) g_FailBox(1,"Failed to set Direct Sound Cooperative Level!");
	
	return OK;
}


int g_GetWaveInfo(HMMIO mfile ,WAVEFORMATEX* wavf ,int* size)
{
	MMCKINFO mck;	
	PCMWAVEFORMAT pcwavf;

	mck.ckid = mmioFOURCC('W' ,'A' ,'V' ,'E');
	mmioDescend(mfile ,&mck ,NULL ,0);	
	*size = mck.cksize;	
	mck.ckid = mmioFOURCC('f' ,'m' ,'t' ,' ');
	mmioDescend(mfile ,&mck ,NULL ,MMIO_FINDCHUNK);	
	mmioRead(mfile ,(char*)&pcwavf ,sizeof(PCMWAVEFORMAT));	
	mmioSeek(mfile ,0 ,SEEK_SET);	

	wavf->wFormatTag = pcwavf.wf.wFormatTag;			
    wavf->nChannels = pcwavf.wf.nChannels;				
    wavf->nSamplesPerSec = pcwavf.wf.nSamplesPerSec;	
    wavf->nAvgBytesPerSec = pcwavf.wf.nAvgBytesPerSec;	
    wavf->nBlockAlign = pcwavf.wf.nBlockAlign;			 
    wavf->wBitsPerSample = pcwavf.wBitsPerSample;		 
    wavf->cbSize = 0;									

	return OK;
}


int g_ReadWaveData(HMMIO mfile ,void* buffer)
{
	MMCKINFO mcks,mck;	
	MMIOINFO minf;		

	mcks.ckid = mmioFOURCC('W' ,'A' ,'V' ,'E');	
	mmioDescend(mfile ,&mcks ,NULL ,0);	
	mck.ckid = mmioFOURCC('d' ,'a' ,'t' ,'a');	
	mmioDescend(mfile ,&mck ,NULL ,MMIO_FINDCHUNK);	
	mmioGetInfo(mfile ,&minf ,0);	

	for(unsigned int i = 0; i < mcks.cksize; i++)
	{
		if(minf.pchNext == minf.pchEndRead) mmioAdvance(mfile ,&minf ,MMIO_READ);
		*((char*)buffer+i) = *((char*)minf.pchNext);
		minf.pchNext++;	
	}
	mmioSetInfo(mfile ,&minf ,0);

	return OK;
}


LPDIRECTSOUNDBUFFER g_CreateBufferFromFile(char* file)
{
	HMMIO mfile;	
	LPDIRECTSOUNDBUFFER sbuf;	
	WAVEFORMATEX wavf;	
	DSBUFFERDESC desc;	
	int size = 0;
	void* b1 = NULL;	
	unsigned long s1;
	int r = 0;	

	mfile = mmioOpen(file ,NULL ,MMIO_READ | MMIO_ALLOCBUF);
	g_GetWaveInfo(mfile ,&wavf ,&size);
	ZeroMemory(&desc ,sizeof(DSBUFFERDESC));
	desc.dwSize = sizeof(desc);	
	desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC;	
	desc.dwBufferBytes = size;
	desc.lpwfxFormat = &wavf;
	desc.guid3DAlgorithm = DS3DALG_DEFAULT;	
	r = Ds->CreateSoundBuffer(&desc ,&sbuf ,NULL);
		if (FAILED(r)) g_FailBox(1,"Failed to create Direct Sound Buffer!");
	sbuf->Restore();	
	sbuf->Lock(0 ,size ,&b1 ,&s1 ,NULL ,NULL ,DSBLOCK_ENTIREBUFFER);
	g_ReadWaveData(mfile ,b1); 
	sbuf->Unlock(b1 ,size ,NULL ,0);
	sbuf->Restore();	
	mmioClose(mfile ,0);	

	return sbuf;
}


int g_NSound::InitNSound(char* file)
{
	buffer = NULL;
	buffer = g_CreateBufferFromFile(file);

	if(buffer == NULL) g_FailBox(0,"Failed to load SoundBuffer from file %s",file);

	return OK;
}


void g_NSound::PlaySound(void)
{
	buffer->Play(0,0,0);
}







