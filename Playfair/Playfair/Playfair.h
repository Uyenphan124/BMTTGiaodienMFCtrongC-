#pragma once

#ifndef __AFXWIN_H__
#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include <string>           // Include the <string> header file

// CPlayfairApp:
// See Playfair.cpp for the implementation of this class
//

class CPlayfairApp : public CWinApp
{
public:
    CPlayfairApp();

    // Overrides
public:
    virtual BOOL InitInstance();

    // Implementation

    DECLARE_MESSAGE_MAP()
};

extern CPlayfairApp theApp;

class playfair
{
public:
    // Decrypts the ciphertext using the Playfair decryption algorithm
    static std::string DECRYPTION(const std::string& Ciphertext, const std::string& k);
};
