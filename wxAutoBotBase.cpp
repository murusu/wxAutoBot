///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May  4 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wxAutoBot.h"

#include "wxAutoBotBase.h"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItemExit;
	m_menuItemExit = new wxMenuItem( m_menu1, wxID_Menu_Exit, wxString( _("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItemExit );
	
	m_menubar1->Append( m_menu1, _("File") ); 
	
	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem_addtask;
	m_menuItem_addtask = new wxMenuItem( m_menu2, wxID_Menu_AddTask, wxString( _("Add Task") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem_addtask );
	
	m_menubar1->Append( m_menu2, _("Task") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_listCtrl = new TaskListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VIRTUAL );
	bSizer1->Add( m_listCtrl, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxID_Menu_Exit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::ExitProgram ) );
	m_listCtrl->Connect( wxEVT_SIZE, wxSizeEventHandler( MainFrameBase::ListSizeChange ), NULL, this );
}

MainFrameBase::~MainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxID_Menu_Exit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::ExitProgram ) );
	m_listCtrl->Disconnect( wxEVT_SIZE, wxSizeEventHandler( MainFrameBase::ListSizeChange ), NULL, this );
	
}
