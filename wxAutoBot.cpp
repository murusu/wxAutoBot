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

ActionListCtrl::ActionListCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style): wxListCtrl(parent, id, pos, size, style)
{
}

ActionListCtrl::~ActionListCtrl()
{
}

wxString ActionListCtrl::OnGetItemText(long item, long column) const
{
    wxString ItemText;

    ItemText = wxT("testest");

    /*
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
    */

    return ItemText;
}

MainFrame::MainFrame(wxFrame *frame) : MainFrameBase(frame)
{
    m_popupmenu = NULL;

    m_listCtrl_task->InsertColumn(0, _("Task Name"), wxLIST_FORMAT_CENTRE, 180);
    m_listCtrl_task->InsertColumn(1, _("Next Activity Time"), wxLIST_FORMAT_CENTRE, 270);
    m_listCtrl_task->InsertColumn(2, _("Status"), wxLIST_FORMAT_CENTRE, 100);

    m_listCtrl_task->SetItemCount(0);
    m_listCtrl_task->Refresh();
    DoListSize();
}

MainFrame::~MainFrame()
{
}

void MainFrame::OnMenuClick( wxUpdateUIEvent& event )
{
    m_menu_task->FindItem(wxID_Menu_EditTask)->Enable(false);
    m_menu_task->FindItem(wxID_Menu_DeleteTask)->Enable(false);
    m_menu_task->FindItem(wxID_Menu_StartTask)->Enable(false);
    m_menu_task->FindItem(wxID_Menu_StopTask)->Enable(false);

    long item_index = -1;
    size_t task_type = 0;

    if(m_listCtrl_task->GetSelectedItemCount())
    {
        m_menu_task->FindItem(wxID_Menu_EditTask)->Enable(true);

        item_index = m_listCtrl_task->GetNextItem(item_index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        task_type  = wxGetApp().getTaskManager()->GetTaskArray()->Item(item_index)->GetTaskStatusType();

        switch(task_type)
        {
            case TASKSTATUS_STOP:
            case TASKSTATUS_ERROR:
                m_menu_task->FindItem(wxID_Menu_DeleteTask)->Enable(true);
                m_menu_task->FindItem(wxID_Menu_StartTask)->Enable(true);
                break;

            case TASKSTATUS_WAITING:
            case TASKSTATUS_RUNNING:
                m_menu_task->FindItem(wxID_Menu_StopTask)->Enable(true);
                break;
        }
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
    m_listCtrl_task->SetSize(0, 0, size.x, size.y);
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
    long item_index = -1;
    item_index      = m_listCtrl_task->GetNextItem(item_index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    wxGetApp().getTaskManager()->DeleteTask(item_index);
}

void MainFrame::OnStartTask( wxCommandEvent& event )
{
    long item_index = -1;
    item_index      = m_listCtrl_task->GetNextItem(item_index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    wxGetApp().getTaskManager()->GetTaskArray()->Item(item_index)->StartTask();
}

void MainFrame::OnStopTask( wxCommandEvent& event )
{
    long item_index = -1;
    item_index      = m_listCtrl_task->GetNextItem(item_index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    wxGetApp().getTaskManager()->GetTaskArray()->Item(item_index)->StopTask();
}

void MainFrame::ShowPopupMenu( wxListEvent& event )
{
    PopupMenu(GetPopupMenu(), event.GetPoint());
}

wxMenu* MainFrame::GetPopupMenu()
{
    if(m_popupmenu) return m_popupmenu;
    m_popupmenu = new wxMenu();

    wxMenuItem* m_menuItem_starttask;
	m_menuItem_starttask = new wxMenuItem( m_menu_task, wxID_Menu_StartTask, wxString( _("Start Task") ) , wxEmptyString, wxITEM_NORMAL );
	m_popupmenu->Append( m_menuItem_starttask );

	wxMenuItem* m_menuItem_stoptask;
	m_menuItem_stoptask = new wxMenuItem( m_menu_task, wxID_Menu_StopTask, wxString( _("Stop Task") ) , wxEmptyString, wxITEM_NORMAL );
	m_popupmenu->Append( m_menuItem_stoptask );

	m_popupmenu->AppendSeparator();

    wxMenuItem* m_menuItem_edittask;
	m_menuItem_edittask = new wxMenuItem( m_popupmenu, wxID_Menu_EditTask, wxString( _("Edit Task") ) , wxEmptyString, wxITEM_NORMAL );
	m_popupmenu->Append( m_menuItem_edittask );

	wxMenuItem* m_menuItem_deletetask;
	m_menuItem_deletetask = new wxMenuItem( m_popupmenu, wxID_Menu_DeleteTask, wxString( _("Delete Task") ) , wxEmptyString, wxITEM_NORMAL );
	m_popupmenu->Append( m_menuItem_deletetask );

    return m_popupmenu;
}

void MainFrame::OnListItemActivated( wxListEvent& event )
{
    EditSelectedItem();
}

void MainFrame::EditSelectedItem()
{
    long item_index = -1;
    item_index      = m_listCtrl_task->GetNextItem(item_index, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    wxGetApp().getTaskManager()->GetTaskArray()->Item(item_index)->StopTask();

    TaskDialog  *task_dlg = new TaskDialog(this, item_index);
    task_dlg->ShowModal();
    task_dlg->Destroy();
}

TaskListCtrl* MainFrame::GetTaskListCtrl()
{
    return m_listCtrl_task;
}

TaskDialog::TaskDialog(wxFrame *frame) : TaskDialogBase(frame)
{
    m_popupmenu = NULL;

    m_bottask = new BotTask();
    InitTaskDialog();

    SetupActionListCtrl();
}

TaskDialog::TaskDialog(wxFrame* frame, size_t item_index) : TaskDialogBase(frame)
{
    m_popupmenu = NULL;

    m_bottask = new BotTask();
    m_bottask->ReadConfigData(wxGetApp().getTaskManager()->GetTaskArray()->Item(item_index)->GetConfigFileName());
    InitTaskDialog();

    SetupActionListCtrl();
}

TaskDialog::~TaskDialog()
{
    if(m_bottask) delete m_bottask;
}

void TaskDialog::InitTaskDialog()
{
    if(!m_bottask->GetConfigFileName().Len())
    {
        m_bottask->SetConfigFileName(wxT("task_") + wxDateTime::Now().Format(wxT("%Y%m%d%H%M%S%l")) + wxT(".xml"));
    }

    wxCheckBox * target_checkbox = NULL;
    size_t task_type = m_bottask->GetTaskType();

    m_textCtrl_taskname->SetValue(m_bottask->GetTaskName());
    m_choice_tasktype->SetSelection(task_type);

    m_panel_baseinterval->Show(false);
    m_panel_baseonce->Show(false);
    m_panel_basedaliy->Show(false);
    m_panel_baseweekly->Show(false);
    m_panel_basemonthly->Show(false);

    size_t date_num = 0;
    size_t date_data = 0;

    switch(task_type)
    {
        case TASK_INTERVAL:
            m_panel_baseinterval->Show(true);
            m_spinCtrl_interval->SetValue(m_bottask->GetTaskTimeData()->GetIntervalSeconds());
            break;

        case TASK_SPECIFY:
            m_panel_baseonce->Show(true);
            m_datePicker_once->SetValue(wxDateTime(m_bottask->GetTaskTimeData()->GetSpecifiedTime()));
            m_spinCtrl_once_hour->SetValue(m_bottask->GetTaskTimeData()->GetSpecifiedHours());
            m_spinCtrl_once_minute->SetValue(m_bottask->GetTaskTimeData()->GetSpecifiedMinutes());
            m_spinCtrl_once_second->SetValue(m_bottask->GetTaskTimeData()->GetSpecifiedSeconds());
            break;

        case TASK_DAILY_INTERVAL:
            m_panel_basedaliy->Show(true);
            m_spinCtrl_daliy_hour->SetValue(m_bottask->GetTaskTimeData()->GetSpecifiedHours());
            m_spinCtrl_daliy_minute->SetValue(m_bottask->GetTaskTimeData()->GetSpecifiedMinutes());
            m_spinCtrl_daliy_second->SetValue(m_bottask->GetTaskTimeData()->GetSpecifiedSeconds());
            break;

        case TASK_WEEKLY_INTERVAL:
            m_panel_baseweekly->Show(true);
            m_spinCtrl_weekly_hour->SetValue(m_bottask->GetTaskTimeData()->GetSpecifiedHours());
            m_spinCtrl_weekly_minute->SetValue(m_bottask->GetTaskTimeData()->GetSpecifiedMinutes());
            m_spinCtrl_weekly_second->SetValue(m_bottask->GetTaskTimeData()->GetSpecifiedSeconds());

            date_num = m_bottask->GetTaskTimeData()->GetSpecifiedDate()->GetCount();
            for(size_t index = 0; index < date_num; index++)
            {
                date_data = m_bottask->GetTaskTimeData()->GetSpecifiedDate()->Item(index);
                //((wxCheckBox *)FindWindowByName(wxT("m_checkBox_week_") + wxString::Format(wxT("%i"), date_data)))->SetValue(true);
                target_checkbox = (wxCheckBox *)FindWindowByName(wxT("m_checkBox_week_") + wxString::Format(wxT("%i"), date_data));
                if(target_checkbox) target_checkbox->SetValue(true);
            }
            break;

        case TASK_MONTHLY_INTERVAL:
            m_panel_basemonthly->Show(true);
            m_spinCtrl_monthly_hour->SetValue(m_bottask->GetTaskTimeData()->GetSpecifiedHours());
            m_spinCtrl_monthly_minute->SetValue(m_bottask->GetTaskTimeData()->GetSpecifiedMinutes());
            m_spinCtrl_monthly_second->SetValue(m_bottask->GetTaskTimeData()->GetSpecifiedSeconds());

            date_num = m_bottask->GetTaskTimeData()->GetSpecifiedDate()->GetCount();
            for(size_t index = 0; index < date_num; index++)
            {
                date_data = m_bottask->GetTaskTimeData()->GetSpecifiedDate()->Item(index);
                //((wxCheckBox *)FindWindowByName(wxT("m_checkBox_month_") + wxString::Format(wxT("%i"), date_data)))->SetValue(true);
                target_checkbox = (wxCheckBox *)FindWindowByName(wxT("m_checkBox_month_") + wxString::Format(wxT("%i"), date_data));
                if(target_checkbox) target_checkbox->SetValue(true);
            }
            break;
    }
}

void TaskDialog::OnChangeTaskType(wxCommandEvent& event)
{
    m_panel_baseinterval->Show(false);
    m_panel_baseonce->Show(false);
    m_panel_basedaliy->Show(false);
    m_panel_baseweekly->Show(false);
    m_panel_basemonthly->Show(false);

    size_t choice_selection = m_choice_tasktype->GetCurrentSelection();

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

void TaskDialog::OnAddAction( wxCommandEvent& event )
{
    ActionDialog  *action_dlg = new ActionDialog(this, m_bottask);
    action_dlg->ShowModal();
    action_dlg->Destroy();
}

void TaskDialog::OnCloseTaskDialog(wxCommandEvent& event)
{
    this->Close();
}

void TaskDialog::OnSaveTaskDialog(wxCommandEvent& event)
{
    size_t  task_num = wxGetApp().getTaskManager()->GetTaskArray()->GetCount();
    bool    task_found = false;

    GetDialogData();

    for(size_t index = 0; index < task_num; index++)
    {
        BotTask* target_task = wxGetApp().getTaskManager()->GetTaskArray()->Item(index);

        if(target_task->GetConfigFileName() == m_bottask->GetConfigFileName())
        {
            task_found = true;

            m_bottask->WriteConfigData();
            target_task->CloneTask(m_bottask);

            wxGetApp().getTaskManager()->RefreshList();
        }
    }

    if(!task_found)
    {
        m_bottask->WriteConfigData();
        wxGetApp().getTaskManager()->AddTask(m_bottask);

        wxGetApp().getTaskManager()->RefreshList();
    }

    this->Close();
}

void TaskDialog::GetDialogData()
{
    m_bottask->ResetTimeData();
    m_bottask->SetTaskName(m_textCtrl_taskname->GetValue());
    m_bottask->SetTaskType(m_choice_tasktype->GetCurrentSelection());

    switch(m_choice_tasktype->GetCurrentSelection())
    {
        case TASK_INTERVAL:
            m_bottask->GetTaskTimeData()->SetIntervalSeconds(m_spinCtrl_interval->GetValue());
            break;

        case TASK_SPECIFY:
            m_bottask->GetTaskTimeData()->SetSpecifiedTime(m_datePicker_once->GetValue().GetTicks());//.SetHour(m_spinCtrl_once_hour->GetValue()).SetMinute(m_spinCtrl_once_minute->GetValue()).SetSecond(m_spinCtrl_once_second->GetValue()).GetTicks());
            m_bottask->GetTaskTimeData()->SetSpecifiedHours(m_spinCtrl_once_hour->GetValue());
            m_bottask->GetTaskTimeData()->SetSpecifiedMinutes(m_spinCtrl_once_minute->GetValue());
            m_bottask->GetTaskTimeData()->SetSpecifiedSeconds(m_spinCtrl_once_second->GetValue());
            break;

        case TASK_DAILY_INTERVAL:
            m_bottask->GetTaskTimeData()->SetSpecifiedHours(m_spinCtrl_daliy_hour->GetValue());
            m_bottask->GetTaskTimeData()->SetSpecifiedMinutes(m_spinCtrl_daliy_minute->GetValue());
            m_bottask->GetTaskTimeData()->SetSpecifiedSeconds(m_spinCtrl_daliy_second->GetValue());
            break;

        case TASK_WEEKLY_INTERVAL:
            m_bottask->GetTaskTimeData()->SetSpecifiedHours(m_spinCtrl_weekly_hour->GetValue());
            m_bottask->GetTaskTimeData()->SetSpecifiedMinutes(m_spinCtrl_weekly_minute->GetValue());
            m_bottask->GetTaskTimeData()->SetSpecifiedSeconds(m_spinCtrl_weekly_second->GetValue());

            m_bottask->GetTaskTimeData()->GetSpecifiedDate()->Clear();
            for(size_t index = 0; index < 7; index++)
            {
                if(((wxCheckBox *)FindWindowByName(wxT("m_checkBox_week_") + wxString::Format(wxT("%i"), index)))->GetValue()) m_bottask->GetTaskTimeData()->GetSpecifiedDate()->Add(index);
            }
            break;

        case TASK_MONTHLY_INTERVAL:
            m_bottask->GetTaskTimeData()->SetSpecifiedHours(m_spinCtrl_monthly_hour->GetValue());
            m_bottask->GetTaskTimeData()->SetSpecifiedMinutes(m_spinCtrl_monthly_minute->GetValue());
            m_bottask->GetTaskTimeData()->SetSpecifiedSeconds(m_spinCtrl_monthly_second->GetValue());

            m_bottask->GetTaskTimeData()->GetSpecifiedDate()->Clear();
            for(size_t index = 0; index < 31; index++)
            {
                if(((wxCheckBox *)FindWindowByName(wxT("m_checkBox_month_") + wxString::Format(wxT("%i"), index + 1)))->GetValue()) m_bottask->GetTaskTimeData()->GetSpecifiedDate()->Add(index + 1);
            }
            break;
    }
}

void TaskDialog::ShowPopupMenu( wxListEvent& event )
{

}

void TaskDialog::OnListItemActivated( wxListEvent& event )
{

}

void TaskDialog::ListSizeChange( wxSizeEvent& event )
{
    DoListSize();
    event.Skip();
}

void TaskDialog::DoListSize()
{
    wxSize size = m_panel_taskaction->GetClientSize();
    m_listCtrl_action->SetSize(0, size.y * 1/10, size.x, size.y * 9/10);
}

void TaskDialog::SetupActionListCtrl()
{
    m_listCtrl_action->InsertColumn(0, _("Action Name"), wxLIST_FORMAT_CENTRE, 100);
    m_listCtrl_action->InsertColumn(1, _("Condition"), wxLIST_FORMAT_CENTRE, 170);
    m_listCtrl_action->InsertColumn(2, _("Parameter"), wxLIST_FORMAT_CENTRE, 180);

    m_listCtrl_action->SetItemCount(100);
    m_listCtrl_action->Refresh();

    DoListSize();
}

ActionDialog::ActionDialog(wxDialog *dialog, BotTask* task):ActionDialogBase(dialog)
{
    InitActionDialog();
    m_bottask = task;
}

ActionDialog::~ActionDialog()
{

}

void ActionDialog::InitActionDialog()
{
    m_panel_httpget->Show(false);
    m_panel_execute->Show(false);

    m_panel_httpget->Show(true);
}

void ActionDialog::OnChangeActionType( wxCommandEvent& event )
{
    m_panel_httpget->Show(false);
    m_panel_execute->Show(false);

    size_t choice_selection = m_choice_actiontype->GetCurrentSelection();

    switch(choice_selection)
    {
        case ACTION_HTTPGET :
            m_panel_httpget->Show(true);
            break;

        case ACTION_EXECUTE:
            m_panel_execute->Show(true);
            break;

        default:
            m_panel_httpget->Show(true);
            break;
    }
}
