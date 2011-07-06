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

		// Virtual event handlers, overide them in your derived class
		virtual void ExitProgram( wxCommandEvent& event ) { event.Skip(); }
		virtual void ListSizeChange( wxSizeEvent& event ) { event.Skip(); }

	public:
        TaskListCtrl* m_listCtrl;

		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("wxAutoBot"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,400 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~MainFrameBase();
};

#endif //__wxAutoBotBase__
