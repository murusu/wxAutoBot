///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May  4 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __wxAutoBotBase__
#define __wxAutoBotBase__

#include <wx/intl.h>

class ActionListCtrl;
class TaskListCtrl;

#include <wx/statusbr.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/panel.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/statline.h>
#include <wx/notebook.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_Menu_Exit 1000
#define wxID_Menu_AddTask 1001
#define wxID_Menu_EditTask 1002
#define wxID_Menu_DeleteTask 1003
#define wxID_Menu_StartTask 1004
#define wxID_Menu_StopTask 1005

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxStatusBar* m_statusBar;
		wxMenuBar* m_menubar;
		wxMenu* m_menu_file;
		wxMenu* m_menu_task;
		TaskListCtrl* m_listCtrl_task;
		
		// Virtual event handlers, overide them in your derived class
		virtual void ExitProgram( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddTask( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditTask( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuClick( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnDeleteTask( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStartTask( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStopTask( wxCommandEvent& event ) { event.Skip(); }
		virtual void ShowPopupMenu( wxListEvent& event ) { event.Skip(); }
		virtual void OnListItemActivated( wxListEvent& event ) { event.Skip(); }
		virtual void ListSizeChange( wxSizeEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("wxAutoBot"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,400 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~MainFrameBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class TaskDialogBase
///////////////////////////////////////////////////////////////////////////////
class TaskDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* m_notebook_taskconfig;
		wxPanel* m_panel_taskbase;
		wxStaticText* m_staticText1;
		wxTextCtrl* m_textCtrl_taskname;
		wxStaticText* m_staticText2;
		wxChoice* m_choice_tasktype;
		wxPanel* m_panel4;
		wxPanel* m_panel_baseinterval;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textCtrl_interval;
		wxStaticText* m_staticText4;
		wxPanel* m_panel_baseonce;
		wxStaticText* m_staticText5;
		wxDatePickerCtrl* m_datePicker_once;
		wxStaticText* m_staticText6;
		wxSpinCtrl* m_spinCtrl_once_hour;
		wxStaticText* m_staticText7;
		wxSpinCtrl* m_spinCtrl_once_minute;
		wxStaticText* m_staticText8;
		wxSpinCtrl* m_spinCtrl_once_second;
		wxPanel* m_panel_basedaliy;
		wxStaticText* m_staticText61;
		wxSpinCtrl* m_spinCtrl_daliy_hour;
		wxStaticText* m_staticText71;
		wxSpinCtrl* m_spinCtrl_daliy_minute;
		wxStaticText* m_staticText81;
		wxSpinCtrl* m_spinCtrl_daliy_second;
		wxPanel* m_panel_baseweekly;
		wxStaticText* m_staticText15;
		wxCheckBox* m_checkBox_week_0;
		wxCheckBox* m_checkBox_week_1;
		wxCheckBox* m_checkBox_week_2;
		wxCheckBox* m_checkBox_week_3;
		wxCheckBox* m_checkBox_week_4;
		wxCheckBox* m_checkBox_week_5;
		wxCheckBox* m_checkBox_week_6;
		wxStaticText* m_staticText611;
		wxSpinCtrl* m_spinCtrl_weekly_hour;
		wxStaticText* m_staticText711;
		wxSpinCtrl* m_spinCtrl_weekly_minute;
		wxStaticText* m_staticText811;
		wxSpinCtrl* m_spinCtrl_weekly_second;
		wxPanel* m_panel_basemonthly;
		wxStaticText* m_staticText151;
		wxCheckBox* m_checkBox_month_1;
		wxCheckBox* m_checkBox_month_2;
		wxCheckBox* m_checkBox_month_3;
		wxCheckBox* m_checkBox_month_4;
		wxCheckBox* m_checkBox_month_5;
		wxCheckBox* m_checkBox_month_6;
		wxCheckBox* m_checkBox_month_7;
		wxCheckBox* m_checkBox_month_8;
		wxCheckBox* m_checkBox_month_9;
		wxCheckBox* m_checkBox_month_10;
		wxCheckBox* m_checkBox_month_11;
		wxCheckBox* m_checkBox_month_12;
		wxCheckBox* m_checkBox_month_13;
		wxCheckBox* m_checkBox_month_14;
		wxCheckBox* m_checkBox_month_15;
		wxCheckBox* m_checkBox_month_16;
		wxCheckBox* m_checkBox_month_17;
		wxCheckBox* m_checkBox_month_18;
		wxCheckBox* m_checkBox_month_19;
		wxCheckBox* m_checkBox_month_20;
		wxCheckBox* m_checkBox_month_21;
		wxCheckBox* m_checkBox_month_22;
		wxCheckBox* m_checkBox_month_23;
		wxCheckBox* m_checkBox_month_24;
		wxCheckBox* m_checkBox_month_25;
		wxCheckBox* m_checkBox_month_26;
		wxCheckBox* m_checkBox_month_27;
		wxCheckBox* m_checkBox_month_28;
		wxCheckBox* m_checkBox_month_29;
		wxCheckBox* m_checkBox_month_30;
		wxCheckBox* m_checkBox_month_31;
		wxStaticText* m_staticText6111;
		wxSpinCtrl* m_spinCtrl_monthly_hour;
		wxStaticText* m_staticText7111;
		wxSpinCtrl* m_spinCtrl_monthly_minute;
		wxStaticText* m_staticText8111;
		wxSpinCtrl* m_spinCtrl_monthly_second;
		wxPanel* m_panel_taskaction;
		wxButton* m_button_actionadd;
		wxButton* m_button_actiondel;
		wxButton* m_button_actionedit;
		wxStaticLine* m_staticline1;
		wxButton* m_button_actionup;
		wxButton* m_button_actiondown;
		ActionListCtrl* m_listCtrl_action;
		wxPanel* m_panel_taskother;
		wxButton* m_button_tasksave;
		wxButton* m_button_taskcancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnChangeTaskType( wxCommandEvent& event ) { event.Skip(); }
		virtual void ShowPopupMenu( wxListEvent& event ) { event.Skip(); }
		virtual void OnListItemActivated( wxListEvent& event ) { event.Skip(); }
		virtual void ListSizeChange( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnSaveTaskDialog( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCloseTaskDialog( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TaskDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Task Setting"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 511,456 ), long style = wxDEFAULT_DIALOG_STYLE );
		~TaskDialogBase();
	
};

#endif //__wxAutoBotBase__
