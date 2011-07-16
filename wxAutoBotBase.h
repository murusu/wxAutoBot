///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May  4 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __wxAutoBotBase__
#define __wxAutoBotBase__

#include <wx/intl.h>

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
#include <wx/calctrl.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_Menu_Exit 1000
#define wxID_Menu_AddTask 1001

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxStatusBar* m_statusBar1;
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		wxMenu* m_menu2;
		TaskListCtrl* m_listCtrl;
		
		// Virtual event handlers, overide them in your derived class
		virtual void ExitProgram( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddTask( wxCommandEvent& event ) { event.Skip(); }
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
		wxCalendarCtrl* m_calendar_once;
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
		wxCheckBox* m_checkBox_sunday;
		wxCheckBox* m_checkBox_monday;
		wxCheckBox* m_checkBox_tuesday;
		wxCheckBox* m_checkBox_wednesday;
		wxCheckBox* m_checkBox_thursday;
		wxCheckBox* m_checkBox_friday;
		wxCheckBox* m_checkBox_saturday;
		wxStaticText* m_staticText611;
		wxSpinCtrl* m_spinCtrl_weekly_hour;
		wxStaticText* m_staticText711;
		wxSpinCtrl* m_spinCtrl_weekly_minute;
		wxStaticText* m_staticText811;
		wxSpinCtrl* m_spinCtrl_weekly_second;
		wxPanel* m_panel_basemonthly;
		wxStaticText* m_staticText151;
		wxCheckBox* m_checkBox_1;
		wxCheckBox* m_checkBox_2;
		wxCheckBox* m_checkBox_3;
		wxCheckBox* m_checkBox_4;
		wxCheckBox* m_checkBox_5;
		wxCheckBox* m_checkBox_6;
		wxCheckBox* m_checkBox_7;
		wxCheckBox* m_checkBox_8;
		wxCheckBox* m_checkBox_9;
		wxCheckBox* m_checkBox_10;
		wxCheckBox* m_checkBox_11;
		wxCheckBox* m_checkBox_12;
		wxCheckBox* m_checkBox_13;
		wxCheckBox* m_checkBox_14;
		wxCheckBox* m_checkBox_15;
		wxCheckBox* m_checkBox_16;
		wxCheckBox* m_checkBox_17;
		wxCheckBox* m_checkBox_18;
		wxCheckBox* m_checkBox_19;
		wxCheckBox* m_checkBox_20;
		wxCheckBox* m_checkBox_21;
		wxCheckBox* m_checkBox_22;
		wxCheckBox* m_checkBox_23;
		wxCheckBox* m_checkBox_24;
		wxCheckBox* m_checkBox_25;
		wxCheckBox* m_checkBox_26;
		wxCheckBox* m_checkBox_27;
		wxCheckBox* m_checkBox_28;
		wxCheckBox* m_checkBox_29;
		wxCheckBox* m_checkBox_30;
		wxCheckBox* m_checkBox_31;
		wxStaticText* m_staticText6111;
		wxSpinCtrl* m_spinCtrl_monthly_hour;
		wxStaticText* m_staticText7111;
		wxSpinCtrl* m_spinCtrl_monthly_minute;
		wxStaticText* m_staticText8111;
		wxSpinCtrl* m_spinCtrl_monthly_second;
		wxPanel* m_panel_taskaction;
		wxPanel* m_panel_taskother;
		wxButton* m_button_tasksave;
		wxButton* m_button_taskcancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnChangeTimeType( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCloseTaskDialog( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		TaskDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Task Setting"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 511,456 ), long style = wxDEFAULT_DIALOG_STYLE );
		~TaskDialogBase();
	
};

#endif //__wxAutoBotBase__
