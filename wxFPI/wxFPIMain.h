/***************************************************************
 * Name:      wxFPIMain.h
 * Purpose:   Defines Application Frame
 * Author:    Steve Nail (snail71@gmail.com)
 * Created:   2016-08-15
 * Copyright: Steve Nail ()
 * License:
 **************************************************************/

#ifndef WXFPIMAIN_H
#define WXFPIMAIN_H



#include "wxFPIApp.h"


#include "GUIFrame.h"
#include <wx/timer.h>


class wxFPIFrame: public GUIFrame
{
    public:
        wxFPIFrame(wxFrame *frame);
        ~wxFPIFrame();
    protected:
        void OnTimer(wxTimerEvent& event);
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void fpiScrollChanged( wxScrollEvent& event );

        float translateScrollPosition(int scrollPos);
        wxTimer *m_timer;
        int m_timecount;
};

#endif // WXFPIMAIN_H
