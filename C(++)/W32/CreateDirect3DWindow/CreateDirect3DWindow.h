#pragma once

#include "resource.h"

#include <windows.h>
#include <assert.h>
#include <wchar.h>
#include <mmsystem.h>
#include <commctrl.h> // for InitCommonControls() 
#include <shellapi.h> // for ExtractIcon()
#include <new.h>      // for placement new
#include <math.h>      
#include <limits.h>

// Direct3D includes
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr9.h>

// DirectSound includes
#include <mmsystem.h>
#include <mmreg.h>
#include <dsound.h>   


// LIBS: dxerr9.lib dxguid.lib d3dx9dt.lib d3d9.lib winmm.lib comctl32.lib