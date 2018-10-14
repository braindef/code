// DlgBackgroundArtDeco.h : Haupt-Header-Datei für die Anwendung DLGBACKGROUNDARTDeco
//

#if !defined(AFX_DLGBACKGROUNDARTDeco_H__45663668_3A53_4037_8A80_69693D3BAA6D__INCLUDED_)
#define AFX_DLGBACKGROUNDARTDeco_H__45663668_3A53_4037_8A80_69693D3BAA6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CDlgBackgroundArtDecoApp:
// Siehe DlgBackgroundArtDeco.cpp für die Implementierung dieser Klasse
//

class CDlgBackgroundArtDecoApp : public CWinApp
{
public:
	CDlgBackgroundArtDecoApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CDlgBackgroundArtDecoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CDlgBackgroundArtDecoApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_DLGBACKGROUNDARTDeco_H__45663668_3A53_4037_8A80_69693D3BAA6D__INCLUDED_)
