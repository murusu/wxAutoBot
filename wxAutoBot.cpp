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

    switch(column)
    {
        case TASK_NAME:
            ItemText = wxT("test name");
            break;

        case TASK_TIME:
            ItemText = wxT("0 seconds");
            break;

        case TASK_STATUS:
            ItemText = wxT("running");
            break;
    }

    return ItemText;
}

MainFrame::MainFrame(wxFrame *frame) : MainFrameBase(frame)
{
    m_listCtrl->InsertColumn(0, _("Task Name"), wxLIST_FORMAT_CENTRE, 180);
    m_listCtrl->InsertColumn(1, _("Next Activity Time"), wxLIST_FORMAT_CENTRE, 270);
    m_listCtrl->InsertColumn(2, _("Status"), wxLIST_FORMAT_CENTRE, 100);

    m_listCtrl->SetItemCount(10);
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
