#ifndef WXAUTOBOT_H_INCLUDED
#define WXAUTOBOT_H_INCLUDED

#include "wxAutoBotBase.h"
#include "GlobalValue.h"
#include "wxAutoBotMain.h"
#include "AutoBotTask.h"

class BotTask;

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
		void OnAddTask( wxCommandEvent& event );
		void OnEditTask( wxCommandEvent& event );
		void OnMenuClick( wxUpdateUIEvent& event );
		void OnDeleteTask( wxCommandEvent& event );
		void OnListItemActivated( wxListEvent& event );
		void ListSizeChange( wxSizeEvent& event );

		void EditSelectedItem();

	public:
		MainFrame(wxFrame *frame);
		~MainFrame();

		TaskListCtrl* GetTaskListCtrl();

		void DoListSize();
};

class TaskDialog : public TaskDialogBase
{
    private:
        BotTask* m_bottask;
        size_t  m_index;

    protected:
		void OnChangeTaskType(wxCommandEvent& event);
		void OnCloseTaskDialog(wxCommandEvent& event);
		void OnSaveTaskDialog(wxCommandEvent& event);

		void GetDialogData();
		void InitTaskDialog();

	public:
		TaskDialog(wxFrame* frame);
		TaskDialog(wxFrame* frame, size_t item_index);
		~TaskDialog();
};

#endif // WXAUTOBOT_H_INCLUDED
