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

void MainFrame::OnMenuClick( wxUpdateUIEvent& event )
{
    if(m_listCtrl->GetSelectedItemCount())
    {
        m_menu_task->FindItem(wxID_Menu_EditTask)->Enable(true);
        m_menu_task->FindItem(wxID_Menu_DeleteTask)->Enable(true);
    }
    else
    {
        m_menu_task->FindItem(wxID_Menu_EditTask)->Enable(false);
        m_menu_task->FindItem(wxID_Menu_DeleteTask)->Enable(false);
    }
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

void MainFrame::OnEditTask( wxCommandEvent& event )
{
    EditSelectedItem();
}

void MainFrame::OnDeleteTask( wxCommandEvent& event )
{

}

void MainFrame::OnListItemActivated( wxListEvent& event )
{
    EditSelectedItem();
}

void MainFrame::EditSelectedItem()
{
    long item_index = -1;
    item_index      = m_listCtrl->GetNextItem(item_index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    TaskDialog  *task_dlg = new TaskDialog(this, item_index);
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

TaskDialog::TaskDialog(wxFrame* frame, size_t item_index) : TaskDialogBase(frame)
{

}

TaskDialog::~TaskDialog()
{
}

void TaskDialog::OnChangeTaskType(wxCommandEvent& event)
{
    m_panel_baseinterval->Show(false);
    m_panel_baseonce->Show(false);
    m_panel_basedaliy->Show(false);
    m_panel_baseweekly->Show(false);
    m_panel_basemonthly->Show(false);

    size_t choice_selection = m_choice_tasktype->GetCurrentSelection() + 1;

    switch(choice_selection)
    {
        case TASK_INTERVAL:
            m_panel_baseinterval->Show(true);

            break;

        case TASK_SPECIFY:
            m_panel_baseonce->Show(true);
            break;

        case TASK_DAILY_INTERVAL:
            m_panel_basedaliy->Show(true);
            break;

        case TASK_WEEKLY_INTERVAL:
            m_panel_baseweekly->Show(true);
            break;

        case TASK_MONTHLY_INTERVAL:
            m_panel_basemonthly->Show(true);
            break;

        default:
            m_panel_baseinterval->Show(true);
            break;
    }
}

void TaskDialog::OnCloseTaskDialog(wxCommandEvent& event)
{
    this->Close();
}

void TaskDialog::OnSaveTask(wxCommandEvent& event)
{
    this->Close();
}
