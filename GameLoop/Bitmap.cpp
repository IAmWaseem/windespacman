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

#include "Bitmap.h"

namespace dotnetguy
{

    // **************************************************************************
    //  Bitmap constructor

    Bitmap::Bitmap()
    {
        m_bIsFileDIB = false;
        m_hPalette   = NULL;
        m_hDIB       = NULL;
        m_hResource  = NULL;
    }

    // **************************************************************************
    //  Bitmap destructor

    Bitmap::~Bitmap()
    {
        DeleteObject();
    }

    // **************************************************************************
    //  Bitmap::LoadHelper()     [ IMPLEMENTATION ]
    //    Assumes m_hDIB is valid, does all the additional load work

    void
    Bitmap::LoadHelper()
    {
        //  Create the palette for the bitmap, if necessary

        if( ColorDepth() <= 8 )
        {
            //  Create a LOGPALETTE to fill in with the DIB palette

            int MaxColors = Colors();
            bool bWin3DIB = IsWin3DIB();
            DWORD dwPalEntries[ 257 ];
            LPLOGPALETTE lpLogPal = (LPLOGPALETTE) dwPalEntries;

            lpLogPal -> palVersion = 0x300;
            lpLogPal -> palNumEntries = WORD( MaxColors );
            BITMAPINFO* lpBmp = GetDIBHeader();
            BITMAPCOREINFO* lpCore = GetCoreHeader();

            //  Loop over the color entries in the DIB header

            for( int i = 0; i < MaxColors; i++ )
            {
                PALETTEENTRY* pEntry = &( lpLogPal -> palPalEntry[ i ]);
                pEntry -> peFlags = PC_NOCOLLAPSE;

                //  For Win3 DIBs, extract RGBQUADs ...

                if( bWin3DIB )
                {
                    RGBQUAD* pQuad = &( lpBmp -> bmiColors[ i ]);

                    pEntry -> peRed   = pQuad -> rgbRed;
                    pEntry -> peGreen = pQuad -> rgbGreen;
                    pEntry -> peBlue  = pQuad -> rgbBlue;
                }

                //  ... for Win1.x and OS/2 DIBs, extract RGBTRIPLEs

                else
                {
                    RGBTRIPLE* pTriple = &( lpCore -> bmciColors[ i ]);

                    pEntry -> peRed   = pTriple -> rgbtRed;
                    pEntry -> peGreen = pTriple -> rgbtGreen;
                    pEntry -> peBlue  = pTriple -> rgbtBlue;
                }
            }

            //  Create a new CPalette from the LOGPALETTE

            m_hPalette = CreatePalette( lpLogPal );
            m_cPaletteEntries = lpLogPal -> palNumEntries;
        }
    }



    // **************************************************************************
    //  Bitmap::LoadDIBitmap(UINT)
    //    Loads a device independent bitmap from a resource (integer)

    bool
    Bitmap::LoadDIBitmap( UINT nResourceId, HMODULE hMod )
    {
        return LoadDIBitmap( MAKEINTRESOURCE( nResourceId ), hMod );
    }

    // **************************************************************************
    //  Bitmap::LoadDIBitmap(LPCTSTR)
    //    Loads a device independent bitmap from a resource (string)

    bool
    Bitmap::LoadDIBitmap( LPCTSTR lpszResourceName, HMODULE hMod )
    {
        //  Make sure we don't have one loaded already

        if( IsValid())
            return false;

        //  Find the resource

        m_hResource = FindResource( hMod, lpszResourceName, RT_BITMAP );

        if( m_hResource == NULL )
            return false;

        //  Load the resource

        m_hDIB = LoadResource( hMod, m_hResource );

        if( m_hDIB == NULL )
            return false;

        //  Call the load helper to do the rest of the work

        m_bIsFileDIB = false;
        LoadHelper();
        return true;
    }

    // **************************************************************************
    //  Bitmap::LoadDIBFile()
    //    Loads the bitmap from a .DIB or .BMP file on disk

    bool
    Bitmap::LoadDIBFile( LPCTSTR lpszFilename )
    {
        //  Make sure we don't have one loaded already

        if( IsValid())
            return false;

        //  Locals to be cleaned up later

        HANDLE hFile = INVALID_HANDLE_VALUE;
        BITMAPFILEHEADER bmfh;
        DWORD dwRead;
        DWORD dwDataSize;

        //  Open the bitmap file in question

        try
        {
            hFile = CreateFile( lpszFilename, GENERIC_READ, FILE_SHARE_READ,
                    0, OPEN_EXISTING, 0, 0 );

            if( hFile == INVALID_HANDLE_VALUE )
                throw 0;

            //  Read the BITMAPFILEHEADER first and validate it

            if( ReadFile( hFile, &bmfh, sizeof( BITMAPFILEHEADER ), &dwRead, 0 ) == false )
                throw 0;

            if( dwRead != sizeof( BITMAPFILEHEADER ))
                throw 0;

            if( bmfh.bfType != 0x4D42 )       //  'BM' header
                throw 0;

            if( bmfh.bfReserved1 != 0 )
                throw 0;

            if( bmfh.bfReserved2 != 0 )
                throw 0;

            //  Allocate the memory for the bitmap

            dwDataSize = bmfh.bfSize - sizeof( BITMAPFILEHEADER );
            m_hDIB = GlobalAlloc( GPTR, dwDataSize );

            if( m_hDIB == NULL )
                throw 0;

            //  Load the data from the file

            if( ReadFile( hFile, (LPVOID) m_hDIB, dwDataSize, &dwRead, 0 ) == false )
                throw 0;

            if( dwRead != dwDataSize )
                throw 0;

            //  Close the data file since we're done with it

            CloseHandle( hFile );

            //  Everything is kosher, finish the job

            m_bIsFileDIB = true;
            LoadHelper();
            return true;
        }
        catch(...)
        {
            //  Clean up anything that's outstanding

            if( hFile != INVALID_HANDLE_VALUE )
                CloseHandle( hFile );

            if( m_hDIB != NULL )
            {
                GlobalFree( m_hDIB );
                m_hDIB = NULL;
            }

            return false;
        }
    }

    // **************************************************************************
    //  Bitmap::SaveDIBFile()
    //    Saves the bitmap to a .DIB or .BMP file on disk

    bool
    Bitmap::SaveDIBFile( LPCTSTR lpszFilename )
    {
        //  Locals

        DWORD            dwDataSize;
        DWORD            dwWritten;
        HANDLE           hFile = INVALID_HANDLE_VALUE;
        BITMAPFILEHEADER bmfh = { 0 };

        //  Get the size of the resource data

        if( m_bIsFileDIB )
            dwDataSize = GlobalSize( m_hDIB );
        else
            dwDataSize = SizeofResource( 0, m_hResource );

        //  Create the file

        try
        {
            hFile = CreateFile( lpszFilename, GENERIC_WRITE, 0, 0,
                    CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );

            if( hFile == INVALID_HANDLE_VALUE )
                throw 0;

            //  Create a header to be filled with good little toys

            bmfh.bfType = 0x4D42;
            bmfh.bfSize = dwDataSize + sizeof( BITMAPFILEHEADER );
            bmfh.bfOffBits = sizeof( BITMAPFILEHEADER );

            if( IsWin3DIB())
            {
                bmfh.bfOffBits += sizeof( BITMAPINFOHEADER );

                if( ColorDepth() <= 8 )
                    bmfh.bfOffBits += Colors() * sizeof( RGBQUAD );
            }
            else
            {
                bmfh.bfOffBits += sizeof( BITMAPCOREHEADER );

                if( ColorDepth() <= 8 )
                    bmfh.bfOffBits += Colors() * sizeof( RGBTRIPLE );
            }

            //  Write the header to the datafile

            if( !WriteFile( hFile, &bmfh, sizeof( BITMAPFILEHEADER ), &dwWritten, 0 ))
                throw 0;

            if( dwWritten != sizeof( BITMAPFILEHEADER ))
                throw 0;

            //  Write the data to the datafile

            if( !WriteFile( hFile, (LPVOID) m_hDIB, dwDataSize, &dwWritten, 0 ))
                throw 0;

            if( dwWritten != dwDataSize )
                throw 0;

            //  Close the data file ... things are good and done

            CloseHandle( hFile );
            return true;
        }
        catch(...)
        {
            //  Clean up anything that's outstanding

            if( hFile != INVALID_HANDLE_VALUE )
                CloseHandle( hFile );

            return false;
        }
    }

    // **************************************************************************
    //  Bitmap::DeleteObject()
    //    Works like CGdiObject::DeleteObject(); deletes associated data
    //
    //  You must call this function is you intend to reuse the class to hold
    //  another bitmap; you should call this before calling LoadBitmap() again

    void
    Bitmap::DeleteObject()
    {
        //  Make sure we have valid data

        if( !IsValid())
            return;
    
        //  Clean up anything that was loaded/allocated

        if( m_bIsFileDIB )
        {
            //  Clean up the allocations

            GlobalFree( m_hDIB );
            m_hDIB = NULL;
        }
        else
        {
            //  Free the resource handle

            FreeResource( m_hDIB );
            m_hDIB = NULL;
        }

        //  Free the palette if there is one

        if( m_hPalette )
        {
            ::DeleteObject( m_hPalette );
            m_hPalette = NULL;
        }
    }

    // **************************************************************************
    //  Bitmap::Width()
    //    Returns the width of the bitmap; 0 if an error occurs

    DWORD
    Bitmap::Width()
    {
        if( !IsValid())
            return 0;

        if( IsWin3DIB())
        {
            BITMAPINFO* bmi = GetDIBHeader();
            return( bmi -> bmiHeader.biWidth );
        }
        else
        {
            BITMAPCOREINFO* bmci = GetCoreHeader();
            return( bmci -> bmciHeader.bcWidth );
        }
    }

    // **************************************************************************
    //  Bitmap::Height()
    //    Returns the height of the bitmap; 0 if an error occurs

    DWORD
    Bitmap::Height()
    {
        if( !IsValid())
            return 0;

        if( IsWin3DIB())
        {
            BITMAPINFO* bmi = GetDIBHeader();
            return( bmi -> bmiHeader.biHeight );
        }
        else
        {
            BITMAPCOREINFO* bmci = GetCoreHeader();
            return( bmci -> bmciHeader.bcHeight );
        }
    }

    // **************************************************************************
    //  Bitmap::ColorDepth()
    //    Returns the color depth (in bits) of the bitmap

    int
    Bitmap::ColorDepth()
    {
        if( !IsValid())
            return -1;

        if( IsWin3DIB())
        {
            BITMAPINFO* bmi = GetDIBHeader();
            return( bmi -> bmiHeader.biBitCount );
        }
        else
        {
            BITMAPCOREINFO* bmci = GetCoreHeader();
            return( bmci -> bmciHeader.bcBitCount );
        }
    }

    // **************************************************************************
    //  Bitmap::Color()
    //    Returns the number of colors in the bitmap; -1 if an error occurs
    //
    //  KNOWN PROBLEMS:
    //    32-bit bitmaps (rare) will return 0 because the number of colors
    //    overflows the size of an integer.  You can check the color depth
    //    in bits using ColorDepth() instead in this case.

    int
    Bitmap::Colors()
    {
        if( !IsValid())
            return -1;

        //  Start by assuming standard number of colors

        int NumColors = ( 1 << ColorDepth());

        //  Win3.x DIBs with pallettes can use a specific # of colors

        if( IsWin3DIB())
        {
            BITMAPINFO* bmi = GetDIBHeader();

            if( bmi -> bmiHeader.biClrUsed != 0 )
                NumColors = bmi -> bmiHeader.biClrUsed;
        }

        //  Return the result

        return( NumColors );
        }

    // **************************************************************************
    //  Bitmap::GetPalette()
    //    Retrieves the CPalette that applies to this bitmap; NULL if error

    HPALETTE
    Bitmap::GetPalette()
    {
        if( !IsValid())
            return NULL;

        return m_hPalette;
    }

    // **************************************************************************
    //  Bitmap::CopyPalette()
    //    Copies the active palette into your own CPalette object; returns true
    //    on success, false on error

    bool
    Bitmap::CopyPalette( HPALETTE* pPalette )
    {
        if( !IsValid())
            return false;

        //  Is this a palettized bitmap?

        if( m_hPalette == NULL )
            return false;

        //  Create a new palette from the data

        DWORD dwPalEntries[ 257 ];
        LPLOGPALETTE lpLogPal = (LPLOGPALETTE) dwPalEntries;

        lpLogPal -> palVersion = 0x300;
        lpLogPal -> palNumEntries = WORD( m_cPaletteEntries );

        if( 0 == GetPaletteEntries( m_hPalette, 0, lpLogPal -> palNumEntries,
                lpLogPal -> palPalEntry ))
            return false;

        *pPalette = CreatePalette( lpLogPal );
        return ( *pPalette != NULL );
    }

    // **************************************************************************
    //  Bitmap::IsWin3DIB()    [ IMPLEMENTATION ]
    //    Returns true if a Win 3.x style DIB; false is Win 1.x or OS/2 style

    bool
    Bitmap::IsWin3DIB()
    {
        //  Check the header for the size

        BITMAPCOREINFO* pHdr = GetCoreHeader();
		return( pHdr -> bmciHeader.bcSize == sizeof( BITMAPINFOHEADER ));
    }

    // **************************************************************************
    //  Bitmap::GetCoreHeader()    [ IMPLEMENTATION ]
    //    Returns a BITMAPCOREINFO for use with Win 1.x style DIBs

    BITMAPCOREINFO*
    Bitmap::GetCoreHeader()
    {
        return (BITMAPCOREINFO*) m_hDIB;
    }

    // **************************************************************************
    //  Bitmap::GetDIBHeader()     [ IMPLEMENTATION ]
    //    Returns a BITMAPINFO for use with Win 3.x style DIBs

    BITMAPINFO*
    Bitmap::GetDIBHeader()
    {
        return (BITMAPINFO*) m_hDIB;
    }

    // **************************************************************************
    //  Bitmap::FindDIBBits()     [ IMPLEMENTATION ]
    //    Returns a point to the beginning of the bitmap's bits (for painting)

    void*
    Bitmap::FindDIBBits()
    {
        //  Ensure we have a DIB

        if( !IsValid())
            return NULL;

        //  Locate the bits in the bitmap

        BYTE* pBits;
        BITMAPCOREINFO* pBmp = GetCoreHeader();
        pBits = (BYTE*)( pBmp ) + pBmp -> bmciHeader.bcSize;
        int nColorDepth = ColorDepth();

        //  Skip over palette information, if any

        if( nColorDepth <= 8 )
        {
            if( IsWin3DIB())
                pBits += ( Colors() * sizeof( RGBQUAD ));
            else
                pBits += ( Colors() * sizeof( RGBTRIPLE ));
        }

        //  Done!

        return (void*) pBits;
    }

    // **************************************************************************
    //  Bitmap::PaintDIB()
    //    Paints the DIB on the screen using SetDIBitsToDevice()

    bool
    Bitmap::PaintDIB( HDC dc, LPRECT lpDCRect, LPRECT lpDIBRect )
    {
        //  Ensure we have a DIB

        if( !IsValid())
            return false;

        //  Did they provide the rectangle for the DIB?

        RECT rectDIBExtra;

		int width = Width();
		int height = Height();

        if( lpDIBRect == 0 )
        {
            rectDIBExtra.left = 0;
            rectDIBExtra.top = 0;
            rectDIBExtra.right = width;
            rectDIBExtra.bottom = height;

            lpDIBRect = &rectDIBExtra;
        }

        //  Did they provide the rectangle for the DC?

        RECT rectDCExtra;

        if( lpDCRect == 0 )
        {
            rectDCExtra.left = 0;
            rectDCExtra.top = 0;
            rectDCExtra.right = width;
            rectDCExtra.bottom = height;

            lpDCRect = &rectDCExtra;
        }

        //  Locals

        HPALETTE hOldPal;
        bool bSuccess = false;
        void* lpBits = FindDIBBits();

        //  Select our palette

        if( m_hPalette != NULL )
        {
            hOldPal = SelectPalette( dc, m_hPalette, true );
            RealizePalette( dc );
        }

        //  Use good stretching mode for color pictures

        SetStretchBltMode( dc, COLORONCOLOR );

        //  Check to see which function to use

        int dcHeight  = lpDCRect -> bottom  - lpDCRect -> top;
        int dcWidth   = lpDCRect -> right   - lpDCRect -> left;
        int dibHeight = lpDIBRect -> bottom - lpDIBRect -> top;
        int dibWidth  = lpDIBRect -> right  - lpDIBRect -> left;

        //  Use SetDIBBitsToDevice when we can for speed

        if(( dcWidth == dibWidth ) && ( dcHeight == dibHeight ))
            bSuccess = ::SetDIBitsToDevice( dc, lpDCRect -> left, lpDCRect -> top,
                    dcWidth, dcHeight, lpDIBRect -> left,
                    height - lpDIBRect -> top - dibHeight, 0, height,
                    lpBits, GetDIBHeader(), DIB_RGB_COLORS ) ? true : false;
        else
            bSuccess = ::StretchDIBits( dc, lpDCRect -> left, lpDCRect -> top,
                    dcWidth, dcHeight, lpDIBRect -> left,
                    height - lpDIBRect -> top - dibHeight, dibWidth, dibHeight,
                    lpBits, GetDIBHeader(), DIB_RGB_COLORS, SRCCOPY ) ? true : false;

        //  Restore the old palette

        if( m_hPalette != NULL )
            SelectPalette( dc, hOldPal, true );

        //  Done!

        return bSuccess;
    }

    // **************************************************************************
    //  Bitmap::TransparentPaint()
    //    Paints the bitmap using a transparency color

    bool
    Bitmap::TransparentPaint( HDC hdc, COLORREF clrTransparent, LPRECT lpDCRect,
            LPRECT lpDIBRect )
    {
        //  Ensure we have a DIB

        if( !IsValid())
            return false;

        //  Did they provide the rectangle for the DIB?

        RECT rectDIBExtra;

        if( lpDIBRect == 0 )
        {
            rectDIBExtra.left = 0;
            rectDIBExtra.top = 0;
            rectDIBExtra.right = Width();
            rectDIBExtra.bottom = Height();

            lpDIBRect = &rectDIBExtra;
        }

        //  Did they provide the rectangle for the DC?

        RECT rectDCExtra;

        if( lpDCRect == 0 )
        {
            rectDCExtra.left = 0;
            rectDCExtra.top = 0;
            rectDCExtra.right = Width();
            rectDCExtra.bottom = Height();

            lpDCRect = &rectDCExtra;
        }

        //  Create a memory DC for the original bitmap

        int width  = lpDCRect -> right - lpDCRect -> left;
        int height = lpDCRect -> bottom - lpDCRect -> top;

        RECT rectTemp = { 0, 0, width, height };

        HDC     hdcBmp  = CreateCompatibleDC( hdc );
        HBITMAP hbmpBmp = CreateCompatibleBitmap( hdc, width, height );
        HBITMAP hOldBmp = (HBITMAP) SelectObject( hdcBmp, hbmpBmp );

        PaintDIB( hdcBmp, &rectTemp, lpDIBRect );

        //  Create a monochrome memory DC for the mask

        HDC     hdcMask  = CreateCompatibleDC( hdc );
        HBITMAP hbmpMask = CreateCompatibleBitmap( hdcMask, width, height );
        HBITMAP hOldMask = (HBITMAP) SelectObject( hdcMask, hbmpMask );

        SetBkColor( hdcBmp, clrTransparent );
        BitBlt( hdcMask, 0, 0, width, height, hdcBmp, 0, 0, SRCCOPY );

        //  Three step paint

        SetBkColor( hdc, RGB( 255, 255, 255 ));
        SetTextColor( hdc, RGB( 0, 0, 0 ));

        int x = lpDCRect -> left;
        int y = lpDCRect -> top;

        BitBlt( hdc, x, y, width, height, hdcBmp,  0, 0, SRCINVERT );
        BitBlt( hdc, x, y, width, height, hdcMask, 0, 0, SRCAND );
        BitBlt( hdc, x, y, width, height, hdcBmp,  0, 0, SRCINVERT );

        //  Clean up

        SelectObject( hdcMask, hOldMask );
        SelectObject( hdcBmp, hOldBmp );
        ::DeleteObject( hbmpMask );
        ::DeleteObject( hbmpBmp );
        DeleteDC( hdcMask );
        DeleteDC( hdcBmp );
    
        return true;
    }

	bool
    Bitmap::TransparentPaintTile( HDC hdc, COLORREF clrTransparent, int screenColX, int screenColY, int tileColX, int tileColY )
    {
		LPRECT lpDCRect = 0;
		LPRECT lpDIBRect = 0;

		int tileWidth = 32;
		int tileHeight = 32;

        //  Ensure we have a DIB

        if( !IsValid())
            return false;

        //  Did they provide the rectangle for the DIB?
        RECT rectDIBExtra;
        rectDIBExtra.left = 0;
        rectDIBExtra.top = 0;
        rectDIBExtra.right = Width();
        rectDIBExtra.bottom = Height();
        lpDIBRect = &rectDIBExtra;        

        //  Did they provide the rectangle for the DC?
        RECT rectDCExtra;
        rectDCExtra.left = lpDIBRect->left;
        rectDCExtra.top = lpDIBRect->top;
        rectDCExtra.right = lpDIBRect->right;
        rectDCExtra.bottom = lpDIBRect->bottom;
        lpDCRect = &rectDCExtra;
        
        //  Create a memory DC for the original bitmap

        int width  = lpDCRect -> right - lpDCRect -> left;
        int height = lpDCRect -> bottom - lpDCRect -> top;

        RECT rectTemp = { 0, 0, width, height };

        HDC     hdcBmp  = CreateCompatibleDC( hdc );
        HBITMAP hbmpBmp = CreateCompatibleBitmap( hdc, width, height );
        HBITMAP hOldBmp = (HBITMAP) SelectObject( hdcBmp, hbmpBmp );

        PaintDIB( hdcBmp, &rectTemp, lpDIBRect );

        //  Create a monochrome memory DC for the mask

        HDC     hdcMask  = CreateCompatibleDC( hdc );
        HBITMAP hbmpMask = CreateBitmap(width, height, 1, 1, 0);
        HBITMAP hOldMask = (HBITMAP) SelectObject( hdcMask, hbmpMask );

        SetBkColor( hdcBmp, clrTransparent );
        BitBlt( hdcMask, 0, 0, width, height, hdcBmp, 0, 0, SRCCOPY );

        //  Three step paint

        SetBkColor( hdc, RGB( 255, 255, 255 ));
        SetTextColor( hdc, RGB( 0, 0, 0 ));

        BitBlt( hdc, screenColX * tileWidth, screenColY * tileHeight, tileWidth, tileHeight, hdcBmp,  tileColX * tileWidth, tileColY * tileHeight, SRCINVERT );
        BitBlt( hdc, screenColX * tileWidth, screenColY * tileHeight, tileWidth, tileHeight, hdcMask, tileColX * tileWidth, tileColY * tileHeight, SRCAND );
        BitBlt( hdc, screenColX * tileWidth, screenColY * tileHeight, tileWidth, tileHeight, hdcBmp,  tileColX * tileWidth, tileColY * tileHeight, SRCINVERT );

        //  Clean up

        SelectObject( hdcMask, hOldMask );
        SelectObject( hdcBmp, hOldBmp );
        ::DeleteObject( hbmpMask );
        ::DeleteObject( hbmpBmp );
        DeleteDC( hdcMask );
        DeleteDC( hdcBmp );
    
        return true;
    }

    // **************************************************************************
    //  Bitmap::IsValid()
    //    Returns true if the bitmap data is valid; false if not

    bool
    Bitmap::IsValid()
    {
        return( m_hDIB != NULL );
    }

    // **************************************************************************
    //  Bitmap::GenerateWindowRegion()
    //    Generates the HRGN for use for making non-rect windows

    void
    AddRectToRgn( HRGN & hrgn, int left, int top, int right, int bottom )
    {
        if( hrgn == NULL )
            hrgn = CreateRectRgn( left, top, right + 1, bottom + 1 );
        else
        {
            HRGN hrgn2 = CreateRectRgn( left, top, right + 1, bottom + 1 );
            CombineRgn( hrgn, hrgn, hrgn2, RGN_OR );
            DeleteObject( hrgn2 );
        }
    }

    HRGN
    Bitmap::GenerateWindowRegion( COLORREF clrTransparent, int x, int y,
            int cx, int cy )
    {
        //  Ensure we have a valid, 24-bit DIB

        if( !IsValid())
            return NULL;

        if( ColorDepth() != 24 )
            return NULL;

        //  Handle default values

        int width  = Width();
        int height = Height();

        if( cx < 0 ) cx = width;
        if( cy < 0 ) cy = height;

        int width2 = cx - x;
        int height2 = cy - y;

        if( x < 0 ) return NULL;
        if( y < 0 ) return NULL;
        if(( x + width2 ) > width ) return NULL;
        if(( y + height2 ) > height ) return NULL;

        //  The current region

        HRGN hrgnCurrent = NULL;
    
        //  Turn their colorref into an RGBTRIPLE

        RGBTRIPLE transColor = { GetBValue( clrTransparent ),
                GetGValue( clrTransparent ), GetRValue( clrTransparent ) };

        //  Get the DIB bits

        char * pDib = (char*) FindDIBBits();

        //  Get the length of a row
        //  (each row is padded out to the nearest 32-bit boundary)

        int rowLength = width * sizeof( RGBTRIPLE );
        rowLength = (( rowLength + 3 ) / 4 ) * 4;

        //  Loop over the rows

        int startIdx = ( height - y - 1 ) * rowLength;

        for( int row = 0; row < height2; row++, startIdx -= rowLength )
        {
            //  Reset the left pointer

            int left = -1;

            //  Loop over the columns

            char * pPixel = pDib + startIdx + ( x * sizeof( RGBTRIPLE ));

            for( int col = 0; col < width2; col++, pPixel += sizeof( RGBTRIPLE ))
            {
                //  Is this a solid box?

                if( memcmp( pPixel, &transColor, 3 ) != 0 )
                {
                    //  Is this the start of a section of solid pixels?

                    if( left == -1 )
                        left = col;
                }
                else
                {
                    //  Is this the end of a section of solid pixels?

                    if( left != -1 )
                    {
                        AddRectToRgn( hrgnCurrent, left, row, col - 1, row );
                        left = -1;
                    }
                }
            }

            //  See if there's a region ending at the end of the bitmap

            if( left != -1 )
			{
                //AddRectToRgn( hrgnCurrent, left, row, col - 1, row );
			}
        }

        return hrgnCurrent;
    }

}   //  End of namespace
