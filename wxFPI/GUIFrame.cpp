///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 29 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_gauge1 = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( 303,-1 ), wxGA_HORIZONTAL );
	m_gauge1->SetValue( 50 ); 
	m_gauge1->SetBackgroundColour( wxColour( 238, 18, 28 ) );
	
	bSizer1->Add( m_gauge1, 0, wxALL, 5 );
	
	m_slider1 = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( 303,-1 ), wxSL_HORIZONTAL );
	bSizer1->Add( m_slider1, 0, wxALL, 5 );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 2, 2, 0, 0 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("SETTING:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	m_staticText3->SetFont( wxFont( 16, 70, 90, 92, false, wxEmptyString ) );
	m_staticText3->SetForegroundColour( wxColour( 64, 64, 64 ) );
	
	gSizer1->Add( m_staticText3, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("CURRENT:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	m_staticText4->SetFont( wxFont( 16, 70, 90, 92, false, wxEmptyString ) );
	m_staticText4->SetForegroundColour( wxColour( 64, 64, 64 ) );
	
	gSizer1->Add( m_staticText4, 0, wxALL, 5 );
	
	m_lblSetting = new wxStaticText( this, wxID_ANY, wxT("64.0 F"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblSetting->Wrap( -1 );
	m_lblSetting->SetFont( wxFont( 22, 70, 90, 92, false, wxEmptyString ) );
	m_lblSetting->SetForegroundColour( wxColour( 222, 74, 15 ) );
	
	gSizer1->Add( m_lblSetting, 0, wxALL, 5 );
	
	m_lblCurrentTemp = new wxStaticText( this, wxID_ANY, wxT("-.- F"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblCurrentTemp->Wrap( -1 );
	m_lblCurrentTemp->SetFont( wxFont( 22, 70, 90, 92, false, wxEmptyString ) );
	m_lblCurrentTemp->SetForegroundColour( wxColour( 224, 74, 15 ) );
	
	gSizer1->Add( m_lblCurrentTemp, 0, wxALL, 5 );
	
	bSizer1->Add( gSizer1, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	m_slider1->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrame::fpiScrollChanged ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	m_slider1->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIFrame::fpiScrollChanged ), NULL, this );
}
