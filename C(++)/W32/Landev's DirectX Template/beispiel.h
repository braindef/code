//texture_manager.h:


/**************************************************************************/ 
// /includes/ressource manager/texture_manager.h 
// 
// This file manages the textures, gives it free and loads it dynamic 
/**************************************************************************/ 

/**************************************************************************/ 
// Defines 
/**************************************************************************/ 
#ifndef FILE_4_TEXTURE_MANAGER 
#define FILE_4_TEXTURE_MANAGER 

/**************************************************************************/ 
// Header 
/**************************************************************************/ 
#include <d3d9.h> 
#include <d3dx9.h> 
//#include <errorfile.h>		//LAM DEAKTIVIERT
#include <map> 
#include <string> 
/*
namespace bn_Core 
{ 
        struct TexturePackage 
        { 
                LPDIRECT3DTEXTURE9 Texture; 
                D3DPOOL Pool; 
                int iMapTextureUser; 
                ucs::string strFilename; 
                DWORD dwFilter; 
                UINT iNumberOfLevels; 
                D3DCOLOR ColorKey; 
        }; 

        //The texture manager 
        class DLLEXPORT bn_TextureManager 
        { 
                public: 

                        //Constructor 
                        bn_TextureManager(); 

                        //Destructor 
                        ~bn_TextureManager(); 

                        //Initialise the class 
                        void Initialise(LPDIRECT3DDEVICE9 lpD3DDevice); 

                        //Adds a texture 
                        int AddTexture(ucs::string strFileName,D3DPOOL Pool = D3DPOOL_MANAGED,DWORD dwFilter = D3DX_FILTER_NONE,UINT iNumberOfLevels = 1,D3DCOLOR ColorK$ 

                        //Deletes a texture 
                        void DeleteTexture(ucs::string strFilename); 

                        //Gets a texture 
                        LPDIRECT3DTEXTURE9 GetTexture(ucs::string strFileName); 

                        //Call it OnLostDevice 
                        void OnLostDevice(); 

                        //If the device has been reseted 
                        void OnResetDevice(); 

                protected: 

                        //The device 
                        LPDIRECT3DDEVICE9 m_lpD3DDevice; 

                        //The texture map 
                        std::map<ucs::string,TexturePackage> m_mapTexture; 

                        //If it's intialized 
                        bool m_bInitialised; 
        }; 
} 

#endif 



