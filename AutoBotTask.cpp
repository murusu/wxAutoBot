#include "AutoBotTask.h"

WX_DEFINE_OBJARRAY(TaskArray);

TaskManager::TaskManager()
{
     m_taskarray = NULL;
}

TaskManager::~TaskManager()
{
    if(m_taskarray)
    {
        size_t tasknum = m_taskarray->GetCount();

        for(size_t index = 0; index < tasknum; index++)
        {
            m_taskarray->RemoveAt(index);
        }

        delete m_taskarray;
        m_taskarray = NULL;
    }
}

bool TaskManager::initTaskManager()
{
    m_taskarray = new TaskArray();

    if(!wxDirExists(wxString(XMLTASK_PATH, wxConvUTF8)))
    {
        if(!wxMkdir(wxString(XMLTASK_PATH, wxConvUTF8))) return false;
    }

    if(!wxDirExists(wxString(XMLLOG_PATH, wxConvUTF8)))
    {
        if(!wxMkdir(wxString(XMLLOG_PATH, wxConvUTF8))) return false;
    }

    wxDir dir(wxString(XMLTASK_PATH, wxConvUTF8));
    if(!dir.IsOpened())  return false;

    wxString filename;
    bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);

    while (cont)
    {
        BotTask *ptaskitem = new BotTask();
        ptaskitem->ReadConfigData(filename);
        m_taskarray->Add(ptaskitem);

        //BotTask *ptaskitem = new BotTask();
        //ptaskitem->initBotTask(filename.Mid(TASK_XML_PREFIX_LEN, TASK_XML_NAME_LEN).mb_str(wxConvUTF8));
        //m_taskarray->Add(ptaskitem);

        cont = dir.GetNext(&filename);
    }

    return true;
}

/*
void TaskManager::updateTaskList()
{
    wxListCtrl* ptasklist = NULL;
    ptasklist = wxGetApp().getMainUI()->getTaskListCtrl();

    if(m_taskarray)
    {
        size_t tasknum = m_taskarray->GetCount();

        for(size_t index = 0; index < tasknum; index++)
        {
            ptasklist->InsertItem(index, wxString(m_taskarray->Item(index)->getTaskName(), wxConvUTF8));
            ptasklist->SetItem(index, 1, wxDateTime(m_taskarray->Item(index)->getNextRunDate()).Format());

            switch(m_taskarray->Item(index)->getTaskStatus())
            {
                case TASK_WAITFORRUNING:
                    ptasklist->SetItem(index, 2, _("waiting"));
                    break;

                case TASK_RUNNING:
                    ptasklist->SetItem(index, 2, _("running"));
                    break;

                case TASK_STOP:
                    ptasklist->SetItem(index, 2, _("stop"));
                    break;

                case TASK_WAITFORRETRY:
                    ptasklist->SetItem(index, 2, _("waiting for retry"));
                    break;

                default:
                    ptasklist->SetItem(index, 2, _("unknown"));
                    break;
            }
        }
    }
}
*/

BotTask::BotTask()
{
    m_tasktimmertype    = TASK_INTERVAL;
    m_taskstatus        = TASKSTATUS_STOP;
    m_lastexecutetime   = wxDateTime::Now().GetTicks();
    m_configfilename    = wxT("");
    m_taskname          = wxT("");
}

BotTask::~BotTask()
{
}

bool BotTask::ReadConfigData(wxString filename)
{
    m_configfilename = filename;
    XmlHandler *xmltask = new XmlHandler();
    if(!xmltask->Init(m_configfilename.mb_str(wxConvUTF8), XMLTASK_ROOTNAME)) return false;

    m_taskname  = wxString(xmltask->GetElementText(xmltask->GetElement(XMLTASK_NAME, 0, true)), wxConvUTF8);
    return true;
}

bool BotTask::WriteConfigData()
{
    return true;
}
