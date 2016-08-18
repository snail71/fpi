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
#include "PID.h"

#include "GUIFrame.h"
#include <wx/timer.h>
#include "W1Temp.h"
#include "GPIOClass.h"


class wxFPIFrame: public GUIFrame
{
    public:
        wxFPIFrame(wxFrame *frame);
        ~wxFPIFrame();
        //void SetupPID();
        //void ComputePID();
    protected:
        void OnTimer(wxTimerEvent& event);
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void fpiScrollChanged( wxScrollEvent& event );

        float translateScrollPosition(int scrollPos);
        int translateValueToScrollPosition(double temp);
        void DoControl();
        wxTimer *m_timer;
        int m_timecount;
        double m_FermTemp;
        double m_Deadzone;
        W1Temp *m_tempBus;
        double m_temp;
        unsigned long m_idleTimeSecs;
        int m_state;
        GPIOClass *m_HeatPin;
        GPIOClass *m_CoolPin;
        //PID *m_pid;


        //double m_pidSetpoint;
        //double m_pidInput;
        //double m_pidOutput;
        //float m_Kp;
        //float m_Ki;
        //float m_Kd;
};

#endif // WXFPIMAIN_H
