#ifndef WXAUTOBOT_H_INCLUDED
#define WXAUTOBOT_H_INCLUDED

#include "wxAutoBotBase.h"
#include "GlobalValue.h"

class TaskListCtrl : public wxListCtrl
{
    public:
        TaskListCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style);
        ~TaskListCtrl();

        wxString OnGetItemText(long item, long column) const;
};

class MainFrame : public MainFrameBase
{
	protected:
		void ExitProgram( wxCommandEvent& event );
		void ListSizeChange( wxSizeEvent& event );

		void DoListSize();

	public:
		MainFrame(wxFrame *frame);
		~MainFrame();
};

#endif // WXAUTOBOT_H_INCLUDED