#include "wxAutoBot.h"

TaskListCtrl::TaskListCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style): wxListCtrl(parent, id, pos, size, style)
{
}

TaskListCtrl::~TaskListCtrl()
{
}

wxString TaskListCtrl::OnGetItemText(long item, long column) const
{
    wxString ItemText;

    TaskManager*  task_manager = wxGetApp().getTaskManager();

    switch(column)
    {
        case TASK_NAME:
            ItemText = task_manager->GetTaskName(item);
            break;

        case TASK_TIME:
            ItemText = task_manager->GetTaskTime(item);
            break;

        case TASK_STATUS:
            ItemText = task_manager->GetTaskStatus(item);
            break;
    }

    return ItemText;
}

MainFrame::MainFrame(wxFrame *frame) : MainFrameBase(frame)
{
    m_listCtrl->InsertColumn(0, _("Task Name"), wxLIST_FORMAT_CENTRE, 180);
    m_listCtrl->InsertColumn(1, _("Next Activity Time"), wxLIST_FORMAT_CENTRE, 270);
    m_listCtrl->InsertColumn(2, _("Status"), wxLIST_FORMAT_CENTRE, 100);

    //TaskManager*  task_manager = wxGetApp().getTaskManager();
    //m_listCtrl->SetItemCount(task_manager->GetTaskNum());
    m_listCtrl->SetItemCount(0);
    m_listCtrl->Refresh();
    DoListSize();
}

MainFrame::~MainFrame()
{
}

void MainFrame::ExitProgram( wxCommandEvent& event )
{
    this->Destroy();
}

void MainFrame::ListSizeChange( wxSizeEvent& event )
{
    DoListSize();
    event.Skip();
}

void MainFrame::DoListSize()
{
    wxSize size = GetClientSize();
    m_listCtrl->SetSize(0, 0, size.x, size.y);
}

void MainFrame::OnAddTask(wxCommandEvent& event)
{
    TaskDialog  *task_dlg = new TaskDialog(this);
    task_dlg->ShowModal();
    task_dlg->Destroy();
}

TaskListCtrl* MainFrame::GetTaskListCtrl()
{
    return m_listCtrl;
}

TaskDialog::TaskDialog(wxFrame *frame) : TaskDialogBase(frame)
{
}

TaskDialog::~TaskDialog()
{
}
