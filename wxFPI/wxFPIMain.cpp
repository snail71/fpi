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


#define FERM_STATE_IDLE         0
#define FERM_STATE_HEATING      1
#define FERM_STATE_COOLING      2

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
    statusBar->SetStatusText(_("NO TEMP"), 1);
    //statusBar->SetStatusText(wxbuildinfo(short_f), 1);
#endif


    m_HeatPin = new GPIOClass(wxT("5"));

    if(m_HeatPin->GetSystemAvailable()==FALSE)
    {
        statusBar->SetStatusText(_("NO GPIO SUPPORT"), 0);
        return;
    }

    m_HeatPin->Export();
    m_HeatPin->SetDir(wxT("out"));
    m_HeatPin->SetVal(wxT("0"));

    m_CoolPin = new GPIOClass(wxT("6"));
    m_CoolPin->Export();
    m_CoolPin->SetDir(wxT("out"));
    m_CoolPin->SetVal(wxT("0"));


    m_tempBus = new W1Temp();
    if(m_tempBus->GetSystemAvailable()==FALSE)
    {
        statusBar->SetStatusText(_("W1 ERR - No BUS"), 0);
    }
    else
    {
        if(m_tempBus->GetSensorCount() <= 0)
        {
            statusBar->SetStatusText(_("W1 ERR - No Sensor"), 0);
        }
        else
        {
            m_timer = new wxTimer();
            m_timer->SetOwner(this);
            this->Connect( wxEVT_TIMER, wxTimerEventHandler( wxFPIFrame::OnTimer ) );
            m_timer->Start(1000);
            m_timecount = 0;
            m_Deadzone = .75;
            m_state = FERM_STATE_IDLE;
            m_idleTimeSecs = 0;
        }
    }

    //GPIOClass gpio(wxT("6"));

    //m_lblCurrentTemp->SetLabel(gpio.GetNum());

    /*m_pidSetpoint = 64.5;
    m_Kp = 1;
    m_Ki = 0.14;
    m_Kd = 0.25;

    m_pid = new PID(&m_pidInput,&m_pidOutput,&m_pidSetpoint,m_Kp,m_Ki,m_Kd,DIRECT);

    SetupPID();
    */

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

/*void wxFPIFrame::SetupPID()
{
    m_pid->SetSampleTime(1000);
    m_pid->SetOutputLimits(0,255.0);
    m_pid->SetMode(MANUAL);
    m_pid->SetMode(AUTOMATIC);
}

void wxFPIFrame::ComputePID()
{
    if(m_pid->Compute() == TRUE)
    {
        statusBar->SetStatusText(wxString::Format(wxT("%3.1f"),m_pidOutput), 0);
    }

}
*/
void wxFPIFrame::fpiScrollChanged( wxScrollEvent& event )
{

    int x = m_slider1->GetValue();
    m_FermTemp = (double)translateScrollPosition(x);
    m_lblSetting->SetLabel(wxString::Format(wxT("%2.1f F"),m_FermTemp));
    //m_pidSetpoint = (double)translateScrollPosition(x); WILL NEED TO PUT THIS BACK
    //m_gauge1->SetValue(x);
    //wxString mystring = wxString::Format(wxT("%i"),x);
    //m_lblSetting->SetLabel(wxString::Format(wxT("%2.1f F"),m_pidSetpoint));
}

int wxFPIFrame::translateValueToScrollPosition(double temp)
{
    return (int)temp;
}

float wxFPIFrame::translateScrollPosition(int scrollPos)
{
    float resolution = (85.0 - 35.0) / 100.0;
    return (float)(scrollPos * resolution) + 35;
}

void wxFPIFrame::DoControl()
{
    m_temp = m_tempBus->ReadF(0);
    m_gauge1->SetValue(translateScrollPosition(m_temp));


    if(m_state == FERM_STATE_IDLE)
    {
        m_idleTimeSecs ++;
    }

    if(m_temp > (m_FermTemp + m_Deadzone))
    {
        m_gauge1->SetBackgroundColour( wxColour( 238, 18, 28 ) );
        if(m_state == FERM_STATE_IDLE && m_idleTimeSecs > 180)
        {
            m_CoolPin->SetVal(wxT("1"));
            statusBar->SetStatusText(_("COOL ON"), 1);
            m_state = FERM_STATE_COOLING;
        }
    }
    else if(m_temp < (m_FermTemp - m_Deadzone))
    {
        m_gauge1->SetBackgroundColour( wxColour( 18, 139, 238 ) );
        if(m_state == FERM_STATE_IDLE)
        {
            m_HeatPin->SetVal(wxT("1"));
            statusBar->SetStatusText(_("HEAT ON"), 1);
            m_state = FERM_STATE_HEATING;
        }
    }
    else
    {
        m_gauge1->SetBackgroundColour( wxColour( 53, 181, 48 ) );

        if(m_state != FERM_STATE_IDLE)
        {
            m_CoolPin->SetVal(wxT("0"));
            m_HeatPin->SetVal(wxT("0"));
            statusBar->SetStatusText(_("AT TEMP"), 1);
            m_state = FERM_STATE_IDLE;
            m_idleTimeSecs = 0;
        }
    }
}

void wxFPIFrame::OnTimer(wxTimerEvent& event)
{
    //ComputePID();
    DoControl();
}
