/*

Usage:


TextureManager* m_pTextureManager; 

m_pTextureManager->AddTexture(strFilename,Pool,dwFilter,iMipMap)) 

//Bsp 
m_lpD3DDevice->SetTexture(0, m_pTextureManager->GetTexture(m_strTextureName.c_str()) 


*/



//texture_manager.cpp:


//******************************* FOR MORE SEE THE .h file ********************************// 
/*
#include "beispiel.h" 

//Constructor 
bn_Core::bn_TextureManager::bn_TextureManager() 
{ 
        //Sets it 0 
        m_lpD3DDevice   = NULL; 
        m_bInitialised  = false; 
} 

//Destructor 
bn_Core::bn_TextureManager::~bn_TextureManager() 
{ 
        std::map<ucs::string,TexturePackage>::iterator Iterator; 

        for(Iterator = m_mapTexture.begin(); Iterator != m_mapTexture.end();Iterator++) 
        { 
                if (Iterator->second.Texture != NULL) 
                { 
                        //Sets it 0 
                        (Iterator->second).Texture->Release(); 
                        (Iterator->second.Texture) = NULL; 
                } 
        } 

        //Sets it false 
        m_bInitialised = false; 
} 

//Initialise the class 
void bn_Core::bn_TextureManager::Initialise(LPDIRECT3DDEVICE9 lpD3DDevice) 
{ 
        //Sets the device 
        m_lpD3DDevice = lpD3DDevice; 

        //Sets it true 
        m_bInitialised = true; 
} 

//Call it OnLostDevice 
void bn_Core::bn_TextureManager::OnLostDevice() 
{ 
        std::map<ucs::string,TexturePackage>::iterator Iterator; 

        for(Iterator = m_mapTexture.begin(); Iterator != m_mapTexture.end();Iterator++) 
        { 
                if (Iterator->second.Pool != D3DPOOL_MANAGED) 
                { 
                        //Sets it 0 
                        (Iterator->second).Texture->Release(); 
                        (Iterator->second.Texture) = NULL; 
                } 
        } 
} 

//If the device has been reseted 
void bn_Core::bn_TextureManager::OnResetDevice() 
{ 
        std::map<ucs::string,TexturePackage>::iterator Iterator; 

        for(Iterator = m_mapTexture.begin(); Iterator != m_mapTexture.end();Iterator++) 
        { 
                if (Iterator->second.Pool != D3DPOOL_MANAGED) 
                        this->AddTexture(Iterator->second.strFilename.c_str(),Iterator->second.Pool,Iterator->second.dwFilter,Iterator->second.iNumberOfLevels,Iterator-$ 
        } 
} 

//Adds a texture 
int bn_Core::bn_TextureManager::AddTexture(ucs::string strFileName,D3DPOOL Pool,DWORD dwFilter,UINT iNumberOfLevels,D3DCOLOR ColorKey) 
{ 
        //If there isn't a texture with the same name 
        if (this->GetTexture(strFileName) == NULL) 
        { 
                //The image 
                LPDIRECT3DTEXTURE9 lpImage; 

                //Gets the information about the struct 
                D3DXIMAGE_INFO ImageInfo; 
                D3DXGetImageInfoFromFile(strFileName.c_str(),&ImageInfo); 

                ucs::string strBuffer = "Error, can't create a texture " + strFileName; 
                ucs::string strFilename = "..\\objects\\textures\\" + strFileName; 

                //Loads the sprite from the file 
                if (DXTestForError(D3DXCreateTextureFromFileEx(m_lpD3DDevice,strFilename.c_str(),ImageInfo.Width,ImageInfo.Height, 
                                                                iNumberOfLevels,0,D3DFMT_UNKNOWN,Pool,dwFilter, 
                                                                ColorKey,0,0,0,&lpImage),strBuffer,19,0)) 
                { 
                        m_mapTexture[strFileName].Texture = NULL; 
                        return 0; 
                } 

                //Sets the member var 
                m_mapTexture[strFileName].Texture                       = lpImage; 
                m_mapTexture[strFileName].Pool                          = Pool; 
                m_mapTexture[strFileName].strFilename           = strFileName; 
                m_mapTexture[strFileName].dwFilter                      = dwFilter; 
                m_mapTexture[strFileName].iNumberOfLevels       = iNumberOfLevels; 
                m_mapTexture[strFileName].ColorKey                      = ColorKey; 
        } 
        else m_mapTexture[strFileName].iMapTextureUser++; 

        return 1; 
} 

//Deletes a texture 
void bn_Core::bn_TextureManager::DeleteTexture(ucs::string strFilename) 
{ 
        //If the class lives 
        if (m_bInitialised) 
        { 
                //Creates the iterator 
                std::map<ucs::string,TexturePackage>::iterator Iterator; 

                //Finds the right iterator 
                Iterator = m_mapTexture.find(strFilename); 

                //Release it 
                (Iterator->second).Texture->Release(); 
                (Iterator->second).Texture = NULL; 
        } 
} 

//Returns a texture 
LPDIRECT3DTEXTURE9 bn_Core::bn_TextureManager::GetTexture(ucs::string strFileName) 
{ 
        //If there isn't a texture 
        if (strFileName == "") 
                return NULL; 

        //Creates an iterator 
        std::map<ucs::string,TexturePackage>::iterator result; 

        //Search it 
        result = m_mapTexture.find(strFileName); 

        //It it doesn't exist 
        if (result == m_mapTexture.end()) 
        { 
                return NULL; 
        } 

        if (result->second.Texture == NULL) 
                return NULL; 

        //Return pointer 
        return result->second.Texture; 
} 
*/
