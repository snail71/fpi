/***************************************************************
 * Name:      wxFPIMain.cpp
 * Purpose:   Code for Application Frame
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

#include "wxFPIMain.h"
#include "GPIOClass.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


wxFPIFrame::wxFPIFrame(wxFrame *frame)
    : GUIFrame(frame)
{
#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_("FPI-1"), 0);
    statusBar->SetStatusText(wxbuildinfo(short_f), 1);
#endif
   m_timer = new wxTimer();
   m_timer->SetOwner(this);
   this->Connect( wxEVT_TIMER, wxTimerEventHandler( wxFPIFrame::OnTimer ) );
   m_timer->Start(1000);
   m_timecount = 0;

   GPIOClass gpio(wxT("6"));

   m_lblCurrentTemp->SetLabel(gpio.GetNum());

}

wxFPIFrame::~wxFPIFrame()
{
    this->Disconnect( wxEVT_TIMER, wxTimerEventHandler( wxFPIFrame::OnTimer ) );
}

void wxFPIFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void wxFPIFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void wxFPIFrame::OnAbout(wxCommandEvent &event)
{

}

void wxFPIFrame::fpiScrollChanged( wxScrollEvent& event )
{

    int x = m_slider1->GetValue();
    float setting = translateScrollPosition(x);
    //m_gauge1->SetValue(x);
    //wxString mystring = wxString::Format(wxT("%i"),x);
    m_lblSetting->SetLabel(wxString::Format(wxT("%2.1f F"),setting));
}

float wxFPIFrame::translateScrollPosition(int scrollPos)
{
    float resolution = (85.0 - 35.0) / 100.0;
    return (float)(scrollPos * resolution) + 35;
}

void wxFPIFrame::OnTimer(wxTimerEvent& event)
{
    //m_timecount ++;
    //m_lblCurrentTemp->SetLabel(wxString::Format(wxT("%i"),m_timecount));
}
