/***************************************************************
 * Name:      wxFPIApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Steve Nail (snail71@gmail.com)
 * Created:   2016-08-15
 * Copyright: Steve Nail ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "wxFPIApp.h"
#include "wxFPIMain.h"

IMPLEMENT_APP(wxFPIApp);

bool wxFPIApp::OnInit()
{
    wxFPIFrame* frame = new wxFPIFrame(0L);
    
    frame->Show();
    
    return true;
}
