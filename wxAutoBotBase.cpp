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
	
	m_statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	m_menubar = new wxMenuBar( 0 );
	m_menu_file = new wxMenu();
	wxMenuItem* m_menuItemExit;
	m_menuItemExit = new wxMenuItem( m_menu_file, wxID_Menu_Exit, wxString( _("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_file->Append( m_menuItemExit );
	
	m_menubar->Append( m_menu_file, _("File") ); 
	
	m_menu_task = new wxMenu();
	wxMenuItem* m_menuItem_addtask;
	m_menuItem_addtask = new wxMenuItem( m_menu_task, wxID_Menu_AddTask, wxString( _("Add Task") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_task->Append( m_menuItem_addtask );
	
	wxMenuItem* m_menuItem_edittask;
	m_menuItem_edittask = new wxMenuItem( m_menu_task, wxID_Menu_EditTask, wxString( _("Edit Task") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_task->Append( m_menuItem_edittask );
	m_menuItem_edittask->Enable( false );
	
	wxMenuItem* m_menuItem_deletetask;
	m_menuItem_deletetask = new wxMenuItem( m_menu_task, wxID_Menu_DeleteTask, wxString( _("Delete Task") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_task->Append( m_menuItem_deletetask );
	m_menuItem_deletetask->Enable( false );
	
	m_menubar->Append( m_menu_task, _("Task") ); 
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_listCtrl = new TaskListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_VIRTUAL );
	bSizer1->Add( m_listCtrl, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxID_Menu_Exit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::ExitProgram ) );
	this->Connect( wxID_Menu_AddTask, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnAddTask ) );
	this->Connect( wxID_Menu_EditTask, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnEditTask ) );
	this->Connect( wxID_Menu_EditTask, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::OnMenuClick ) );
	this->Connect( wxID_Menu_DeleteTask, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDeleteTask ) );
	this->Connect( wxID_Menu_DeleteTask, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::OnMenuClick ) );
	m_listCtrl->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( MainFrameBase::OnListItemActivated ), NULL, this );
	m_listCtrl->Connect( wxEVT_SIZE, wxSizeEventHandler( MainFrameBase::ListSizeChange ), NULL, this );
}

MainFrameBase::~MainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxID_Menu_Exit, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::ExitProgram ) );
	this->Disconnect( wxID_Menu_AddTask, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnAddTask ) );
	this->Disconnect( wxID_Menu_EditTask, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnEditTask ) );
	this->Disconnect( wxID_Menu_EditTask, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::OnMenuClick ) );
	this->Disconnect( wxID_Menu_DeleteTask, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnDeleteTask ) );
	this->Disconnect( wxID_Menu_DeleteTask, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::OnMenuClick ) );
	m_listCtrl->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( MainFrameBase::OnListItemActivated ), NULL, this );
	m_listCtrl->Disconnect( wxEVT_SIZE, wxSizeEventHandler( MainFrameBase::ListSizeChange ), NULL, this );
	
}

TaskDialogBase::TaskDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook_taskconfig = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel_taskbase = new wxPanel( m_notebook_taskconfig, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( m_panel_taskbase, wxID_ANY, _("Task Name:"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText1->Wrap( -1 );
	bSizer8->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_textCtrl_taskname = new wxTextCtrl( m_panel_taskbase, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 120,-1 ), 0 );
	bSizer8->Add( m_textCtrl_taskname, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizer6->Add( bSizer8, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( m_panel_taskbase, wxID_ANY, _("Task Type:"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText2->Wrap( -1 );
	bSizer9->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxString m_choice_tasktypeChoices[] = { _("Interval"), _("One Time"), _("Daily"), _("Weekly"), _("Monthly") };
	int m_choice_tasktypeNChoices = sizeof( m_choice_tasktypeChoices ) / sizeof( wxString );
	m_choice_tasktype = new wxChoice( m_panel_taskbase, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_tasktypeNChoices, m_choice_tasktypeChoices, 0 );
	m_choice_tasktype->SetSelection( 0 );
	bSizer9->Add( m_choice_tasktype, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizer6->Add( bSizer9, 1, wxEXPAND, 5 );
	
	bSizer5->Add( bSizer6, 3, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	m_panel4 = new wxPanel( m_panel_taskbase, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_panel_baseinterval = new wxPanel( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText3 = new wxStaticText( m_panel_baseinterval, wxID_ANY, _("Interval:"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText3->Wrap( -1 );
	bSizer11->Add( m_staticText3, 0, wxALL, 5 );
	
	m_textCtrl_interval = new wxTextCtrl( m_panel_baseinterval, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 120,-1 ), 0 );
	bSizer11->Add( m_textCtrl_interval, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( m_panel_baseinterval, wxID_ANY, _("Seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer11->Add( m_staticText4, 0, wxALL, 5 );
	
	m_panel_baseinterval->SetSizer( bSizer11 );
	m_panel_baseinterval->Layout();
	bSizer11->Fit( m_panel_baseinterval );
	bSizer10->Add( m_panel_baseinterval, 1, wxEXPAND, 5 );
	
	m_panel_baseonce = new wxPanel( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel_baseonce->Hide();
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( m_panel_baseonce, wxID_ANY, _("Date:"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText5->Wrap( -1 );
	bSizer13->Add( m_staticText5, 0, wxALL, 5 );
	
	m_datePicker_once = new wxDatePickerCtrl( m_panel_baseonce, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN );
	bSizer13->Add( m_datePicker_once, 0, wxALL, 5 );
	
	bSizer12->Add( bSizer13, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText6 = new wxStaticText( m_panel_baseonce, wxID_ANY, _("Time:"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText6->Wrap( -1 );
	bSizer14->Add( m_staticText6, 0, wxALL, 5 );
	
	m_spinCtrl_once_hour = new wxSpinCtrl( m_panel_baseonce, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 23, 0 );
	bSizer14->Add( m_spinCtrl_once_hour, 0, wxALL, 5 );
	
	m_staticText7 = new wxStaticText( m_panel_baseonce, wxID_ANY, _(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer14->Add( m_staticText7, 0, wxALL, 5 );
	
	m_spinCtrl_once_minute = new wxSpinCtrl( m_panel_baseonce, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	bSizer14->Add( m_spinCtrl_once_minute, 0, wxALL, 5 );
	
	m_staticText8 = new wxStaticText( m_panel_baseonce, wxID_ANY, _(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer14->Add( m_staticText8, 0, wxALL, 5 );
	
	m_spinCtrl_once_second = new wxSpinCtrl( m_panel_baseonce, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	bSizer14->Add( m_spinCtrl_once_second, 0, wxALL, 5 );
	
	bSizer12->Add( bSizer14, 0, wxEXPAND, 5 );
	
	m_panel_baseonce->SetSizer( bSizer12 );
	m_panel_baseonce->Layout();
	bSizer12->Fit( m_panel_baseonce );
	bSizer10->Add( m_panel_baseonce, 1, wxEXPAND, 5 );
	
	m_panel_basedaliy = new wxPanel( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel_basedaliy->Hide();
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText61 = new wxStaticText( m_panel_basedaliy, wxID_ANY, _("Time:"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText61->Wrap( -1 );
	bSizer15->Add( m_staticText61, 0, wxALL, 5 );
	
	m_spinCtrl_daliy_hour = new wxSpinCtrl( m_panel_basedaliy, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 23, 0 );
	bSizer15->Add( m_spinCtrl_daliy_hour, 0, wxALL, 5 );
	
	m_staticText71 = new wxStaticText( m_panel_basedaliy, wxID_ANY, _(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	bSizer15->Add( m_staticText71, 0, wxALL, 5 );
	
	m_spinCtrl_daliy_minute = new wxSpinCtrl( m_panel_basedaliy, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	bSizer15->Add( m_spinCtrl_daliy_minute, 0, wxALL, 5 );
	
	m_staticText81 = new wxStaticText( m_panel_basedaliy, wxID_ANY, _(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	bSizer15->Add( m_staticText81, 0, wxALL, 5 );
	
	m_spinCtrl_daliy_second = new wxSpinCtrl( m_panel_basedaliy, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	bSizer15->Add( m_spinCtrl_daliy_second, 0, wxALL, 5 );
	
	m_panel_basedaliy->SetSizer( bSizer15 );
	m_panel_basedaliy->Layout();
	bSizer15->Fit( m_panel_basedaliy );
	bSizer10->Add( m_panel_basedaliy, 1, wxEXPAND, 5 );
	
	m_panel_baseweekly = new wxPanel( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel_baseweekly->Hide();
	
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText15 = new wxStaticText( m_panel_baseweekly, wxID_ANY, _("Week Day:"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText15->Wrap( -1 );
	bSizer29->Add( m_staticText15, 0, wxALL, 5 );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 2, 2, 0, 0 );
	
	m_checkBox_week_0 = new wxCheckBox( m_panel_baseweekly, wxID_ANY, _("SunDay"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_week_0") );
	gSizer1->Add( m_checkBox_week_0, 0, wxALL, 5 );
	
	m_checkBox_week_1 = new wxCheckBox( m_panel_baseweekly, wxID_ANY, _("Monday"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_week_1") );
	gSizer1->Add( m_checkBox_week_1, 0, wxALL, 5 );
	
	m_checkBox_week_2 = new wxCheckBox( m_panel_baseweekly, wxID_ANY, _("Tuesday"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_week_2") );
	gSizer1->Add( m_checkBox_week_2, 0, wxALL, 5 );
	
	m_checkBox_week_3 = new wxCheckBox( m_panel_baseweekly, wxID_ANY, _("Wednesday"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_week_3") );
	gSizer1->Add( m_checkBox_week_3, 0, wxALL, 5 );
	
	m_checkBox_week_4 = new wxCheckBox( m_panel_baseweekly, wxID_ANY, _("Thursday"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_week_4") );
	gSizer1->Add( m_checkBox_week_4, 0, wxALL, 5 );
	
	m_checkBox_week_5 = new wxCheckBox( m_panel_baseweekly, wxID_ANY, _("Friday"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_week_5") );
	gSizer1->Add( m_checkBox_week_5, 0, wxALL, 5 );
	
	m_checkBox_week_6 = new wxCheckBox( m_panel_baseweekly, wxID_ANY, _("Saturday"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_week_6") );
	gSizer1->Add( m_checkBox_week_6, 0, wxALL, 5 );
	
	bSizer29->Add( gSizer1, 1, wxEXPAND, 5 );
	
	bSizer24->Add( bSizer29, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer151;
	bSizer151 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText611 = new wxStaticText( m_panel_baseweekly, wxID_ANY, _("Time:"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText611->Wrap( -1 );
	bSizer151->Add( m_staticText611, 0, wxALL, 5 );
	
	m_spinCtrl_weekly_hour = new wxSpinCtrl( m_panel_baseweekly, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 23, 0 );
	bSizer151->Add( m_spinCtrl_weekly_hour, 0, wxALL, 5 );
	
	m_staticText711 = new wxStaticText( m_panel_baseweekly, wxID_ANY, _(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText711->Wrap( -1 );
	bSizer151->Add( m_staticText711, 0, wxALL, 5 );
	
	m_spinCtrl_weekly_minute = new wxSpinCtrl( m_panel_baseweekly, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	bSizer151->Add( m_spinCtrl_weekly_minute, 0, wxALL, 5 );
	
	m_staticText811 = new wxStaticText( m_panel_baseweekly, wxID_ANY, _(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText811->Wrap( -1 );
	bSizer151->Add( m_staticText811, 0, wxALL, 5 );
	
	m_spinCtrl_weekly_second = new wxSpinCtrl( m_panel_baseweekly, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	bSizer151->Add( m_spinCtrl_weekly_second, 0, wxALL, 5 );
	
	bSizer24->Add( bSizer151, 0, wxEXPAND, 5 );
	
	m_panel_baseweekly->SetSizer( bSizer24 );
	m_panel_baseweekly->Layout();
	bSizer24->Fit( m_panel_baseweekly );
	bSizer10->Add( m_panel_baseweekly, 1, wxEXPAND, 5 );
	
	m_panel_basemonthly = new wxPanel( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel_basemonthly->Hide();
	
	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer291;
	bSizer291 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText151 = new wxStaticText( m_panel_basemonthly, wxID_ANY, _("Month Day:"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText151->Wrap( -1 );
	bSizer291->Add( m_staticText151, 0, wxALL, 5 );
	
	wxGridSizer* gSizer11;
	gSizer11 = new wxGridSizer( 6, 6, 0, 0 );
	
	m_checkBox_month_1 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_1") );
	gSizer11->Add( m_checkBox_month_1, 0, wxALL, 5 );
	
	m_checkBox_month_2 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_2") );
	gSizer11->Add( m_checkBox_month_2, 0, wxALL, 5 );
	
	m_checkBox_month_3 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_3") );
	gSizer11->Add( m_checkBox_month_3, 0, wxALL, 5 );
	
	m_checkBox_month_4 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("4"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_4") );
	gSizer11->Add( m_checkBox_month_4, 0, wxALL, 5 );
	
	m_checkBox_month_5 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("5"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_5") );
	gSizer11->Add( m_checkBox_month_5, 0, wxALL, 5 );
	
	m_checkBox_month_6 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("6"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_6") );
	gSizer11->Add( m_checkBox_month_6, 0, wxALL, 5 );
	
	m_checkBox_month_7 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("7"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_7") );
	gSizer11->Add( m_checkBox_month_7, 0, wxALL, 5 );
	
	m_checkBox_month_8 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("8"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_8") );
	gSizer11->Add( m_checkBox_month_8, 0, wxALL, 5 );
	
	m_checkBox_month_9 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("9"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_9") );
	gSizer11->Add( m_checkBox_month_9, 0, wxALL, 5 );
	
	m_checkBox_month_10 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_10") );
	gSizer11->Add( m_checkBox_month_10, 0, wxALL, 5 );
	
	m_checkBox_month_11 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("11"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_11") );
	gSizer11->Add( m_checkBox_month_11, 0, wxALL, 5 );
	
	m_checkBox_month_12 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("12"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_12") );
	gSizer11->Add( m_checkBox_month_12, 0, wxALL, 5 );
	
	m_checkBox_month_13 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("13"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_13") );
	gSizer11->Add( m_checkBox_month_13, 0, wxALL, 5 );
	
	m_checkBox_month_14 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("14"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_14") );
	gSizer11->Add( m_checkBox_month_14, 0, wxALL, 5 );
	
	m_checkBox_month_15 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("15"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_15") );
	gSizer11->Add( m_checkBox_month_15, 0, wxALL, 5 );
	
	m_checkBox_month_16 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("16"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_16") );
	gSizer11->Add( m_checkBox_month_16, 0, wxALL, 5 );
	
	m_checkBox_month_17 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("17"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_17") );
	gSizer11->Add( m_checkBox_month_17, 0, wxALL, 5 );
	
	m_checkBox_month_18 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("18"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_18") );
	gSizer11->Add( m_checkBox_month_18, 0, wxALL, 5 );
	
	m_checkBox_month_19 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("19"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_19") );
	gSizer11->Add( m_checkBox_month_19, 0, wxALL, 5 );
	
	m_checkBox_month_20 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("20"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_20") );
	gSizer11->Add( m_checkBox_month_20, 0, wxALL, 5 );
	
	m_checkBox_month_21 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("21"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_21") );
	gSizer11->Add( m_checkBox_month_21, 0, wxALL, 5 );
	
	m_checkBox_month_22 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("22"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_22") );
	gSizer11->Add( m_checkBox_month_22, 0, wxALL, 5 );
	
	m_checkBox_month_23 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("23"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_23") );
	gSizer11->Add( m_checkBox_month_23, 0, wxALL, 5 );
	
	m_checkBox_month_24 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("24"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_24") );
	gSizer11->Add( m_checkBox_month_24, 0, wxALL, 5 );
	
	m_checkBox_month_25 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("25"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_25") );
	gSizer11->Add( m_checkBox_month_25, 0, wxALL, 5 );
	
	m_checkBox_month_26 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("26"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_26") );
	gSizer11->Add( m_checkBox_month_26, 0, wxALL, 5 );
	
	m_checkBox_month_27 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("27"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_27") );
	gSizer11->Add( m_checkBox_month_27, 0, wxALL, 5 );
	
	m_checkBox_month_28 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("28"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_28") );
	gSizer11->Add( m_checkBox_month_28, 0, wxALL, 5 );
	
	m_checkBox_month_29 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("29"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_29") );
	gSizer11->Add( m_checkBox_month_29, 0, wxALL, 5 );
	
	m_checkBox_month_30 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("30"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_30") );
	gSizer11->Add( m_checkBox_month_30, 0, wxALL, 5 );
	
	m_checkBox_month_31 = new wxCheckBox( m_panel_basemonthly, wxID_ANY, _("31"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("m_checkBox_month_31") );
	gSizer11->Add( m_checkBox_month_31, 0, wxALL, 5 );
	
	bSizer291->Add( gSizer11, 1, wxEXPAND, 5 );
	
	bSizer34->Add( bSizer291, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1511;
	bSizer1511 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText6111 = new wxStaticText( m_panel_basemonthly, wxID_ANY, _("Time:"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText6111->Wrap( -1 );
	bSizer1511->Add( m_staticText6111, 0, wxALL, 5 );
	
	m_spinCtrl_monthly_hour = new wxSpinCtrl( m_panel_basemonthly, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 23, 0 );
	bSizer1511->Add( m_spinCtrl_monthly_hour, 0, wxALL, 5 );
	
	m_staticText7111 = new wxStaticText( m_panel_basemonthly, wxID_ANY, _(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7111->Wrap( -1 );
	bSizer1511->Add( m_staticText7111, 0, wxALL, 5 );
	
	m_spinCtrl_monthly_minute = new wxSpinCtrl( m_panel_basemonthly, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	bSizer1511->Add( m_spinCtrl_monthly_minute, 0, wxALL, 5 );
	
	m_staticText8111 = new wxStaticText( m_panel_basemonthly, wxID_ANY, _(":"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8111->Wrap( -1 );
	bSizer1511->Add( m_staticText8111, 0, wxALL, 5 );
	
	m_spinCtrl_monthly_second = new wxSpinCtrl( m_panel_basemonthly, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 59, 0 );
	bSizer1511->Add( m_spinCtrl_monthly_second, 0, wxALL, 5 );
	
	bSizer34->Add( bSizer1511, 0, wxEXPAND, 5 );
	
	m_panel_basemonthly->SetSizer( bSizer34 );
	m_panel_basemonthly->Layout();
	bSizer34->Fit( m_panel_basemonthly );
	bSizer10->Add( m_panel_basemonthly, 1, wxEXPAND, 5 );
	
	m_panel4->SetSizer( bSizer10 );
	m_panel4->Layout();
	bSizer10->Fit( m_panel4 );
	bSizer7->Add( m_panel4, 1, wxEXPAND, 5 );
	
	bSizer5->Add( bSizer7, 18, wxEXPAND, 5 );
	
	m_panel_taskbase->SetSizer( bSizer5 );
	m_panel_taskbase->Layout();
	bSizer5->Fit( m_panel_taskbase );
	m_notebook_taskconfig->AddPage( m_panel_taskbase, _("Base Setting"), true );
	m_panel_taskaction = new wxPanel( m_notebook_taskconfig, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook_taskconfig->AddPage( m_panel_taskaction, _("Actions"), false );
	m_panel_taskother = new wxPanel( m_notebook_taskconfig, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook_taskconfig->AddPage( m_panel_taskother, _("Others Setting"), false );
	
	bSizer3->Add( m_notebook_taskconfig, 1, wxEXPAND | wxALL, 5 );
	
	bSizer2->Add( bSizer3, 10, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button_tasksave = new wxButton( this, wxID_ANY, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button_tasksave, 0, wxALL, 5 );
	
	m_button_taskcancel = new wxButton( this, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button_taskcancel, 0, wxALL, 5 );
	
	bSizer2->Add( bSizer4, 1, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_choice_tasktype->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( TaskDialogBase::OnChangeTaskType ), NULL, this );
	m_button_tasksave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TaskDialogBase::OnSaveTaskDialog ), NULL, this );
	m_button_taskcancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TaskDialogBase::OnCloseTaskDialog ), NULL, this );
}

TaskDialogBase::~TaskDialogBase()
{
	// Disconnect Events
	m_choice_tasktype->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( TaskDialogBase::OnChangeTaskType ), NULL, this );
	m_button_tasksave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TaskDialogBase::OnSaveTaskDialog ), NULL, this );
	m_button_taskcancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TaskDialogBase::OnCloseTaskDialog ), NULL, this );
	
}
