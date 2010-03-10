/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 1995-2002 Brad Wilson
//
//  This material is provided "as is", with absolutely no warranty
//  expressed or implied. Any use is at your own risk. Permission to
//  use or copy this software for any purpose is hereby granted without
//  fee, provided the above notices are retained on all copies.
//  Permission to modify the code and to distribute modified code is
//  granted, provided the above notices are retained, and a notice that
//  the code was modified is included with the above copyright notice.
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _WINDOWS_
#include <windows.h>
#endif

namespace dotnetguy
{

    class Bitmap
    {
    //  Interface

    public:
        Bitmap();
        ~Bitmap();

        bool     IsValid();
        bool     LoadDIBitmap( UINT nResourceId, HMODULE hMod = NULL );
        bool     LoadDIBitmap( LPCTSTR lpszResourceName, HMODULE hMod = NULL );
        bool     LoadDIBFile( LPCTSTR lpszFilename );
        bool     SaveDIBFile( LPCTSTR lpszFilename );
        void     DeleteObject();
        HRGN     GenerateWindowRegion
                     ( COLORREF clrTransparent, int x = 0, int y = 0,
                       int cx = -1, int cy = -1 );
        DWORD    Width();
        DWORD    Height();
        int      ColorDepth();
        int      Colors();
        HPALETTE GetPalette();
        bool     CopyPalette( HPALETTE* pPalette );

    //  Implementation

    protected:
        bool     m_bIsFileDIB;
        HPALETTE m_hPalette;
        int      m_cPaletteEntries;
        HGLOBAL  m_hDIB;
        HRSRC    m_hResource;

        BITMAPINFO *     GetDIBHeader();
        BITMAPCOREINFO * GetCoreHeader();
        bool             IsWin3DIB();
        void *           FindDIBBits();
        void             LoadHelper();
    };

}   //  End of namespace
