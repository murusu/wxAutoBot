#include "AutoBotTask.h"

WX_DEFINE_OBJARRAY(TaskArray);


int CompareDateData(int *first, int *second)
{
    return *first - *second;
}

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

TaskArray* TaskManager::GetTaskArray()
{
    return m_taskarray;
}

size_t TaskManager::GetTaskNum()
{
    return m_taskarray->GetCount();
}

wxString TaskManager::GetTaskName(long index)
{
    return m_taskarray->Item(index)->GetTaskName();
}

wxString TaskManager::GetTaskTime(long index)
{
    return m_taskarray->Item(index)->GetTaskTime();
}

wxString TaskManager::GetTaskStatus(long index)
{
    return m_taskarray->Item(index)->GetTaskStatus();
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
        ptaskitem->UpdateTimer();
        m_taskarray->Add(ptaskitem);

        cont = dir.GetNext(&filename);
    }

    m_timer = new wxTimer(this);
    m_timer->SetOwner(this);

    this->Connect(wxEVT_TIMER, wxTimerEventHandler(TaskManager::OnTimer));

    m_timer->Start(1000);

    return true;
}

void TaskManager::OnTimer(wxTimerEvent& event)
{
    RefreshList();
}

void TaskManager::RefreshList()
{
    wxGetApp().getMainFrame()->GetTaskListCtrl()->SetItemCount(GetTaskNum());
    wxGetApp().getMainFrame()->GetTaskListCtrl()->Refresh();
    wxGetApp().getMainFrame()->DoListSize();
}

BotTask::BotTask()
{
    m_tasktimmertype    = TASK_INTERVAL;
    m_taskstatus        = TASKSTATUS_STOP;
    m_lastexecutetime   = wxDateTime::Now().GetTicks();
    m_configfilename    = wxT("");
    m_taskname          = wxT("New Task");
    m_timer             = new wxTimer(this);

    m_timer->SetOwner(this);
    this->Connect(wxEVT_TIMER, wxTimerEventHandler(BotTask::OnTimer));

    this->Connect(wxEVT_TASKPROCESS_SUCCESS, wxTaskProcessEventHandler(BotTask::OnTaskProcessDone));
    this->Connect(wxEVT_TASKPROCESS_FAIL, wxTaskProcessEventHandler(BotTask::OnTaskProcessDone));

    ResetTimeData();
}

BotTask::~BotTask()
{
}

bool BotTask::ReadConfigData(wxString filename)
{
    m_configfilename = filename;
    XmlTask *xmltask = new XmlTask();
    if(!xmltask->InitData(m_configfilename.mb_str(wxConvUTF8))) return false;

    m_taskname  = wxString(xmltask->GetElementText(xmltask->GetElement(XMLTASK_NAME, 0, true)), wxConvUTF8);
    m_tasktimmertype = atoi(xmltask->GetElementAttribute(xmltask->GetElement(XMLTASK_TIMERTYPE, 0, true), XMLTASK_TIMERTYPE_ATT));

    m_timedata.interval_seconds  = atoi(xmltask->GetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_INTERVAL));
    m_timedata.specified_time    = atoi(xmltask->GetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_TIME));
    m_timedata.specified_hours   = atoi(xmltask->GetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_HOURS));
    m_timedata.specified_minutes = atoi(xmltask->GetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_MINUTES));
    m_timedata.specified_seconds = atoi(xmltask->GetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_SECONDS));

    size_t element_num  = xmltask->GetElementNum(XMLTASK_TIMEDATA_DATA);
    size_t element_data = 0;
    for(size_t index = 0; index < element_num; index++)
    {
        element_data = atoi(xmltask->GetElementText(xmltask->GetElement(XMLTASK_TIMEDATA_DATA, index)));
        m_timedata.specified_date.Add(element_data);
    }

    return true;
}

bool BotTask::WriteConfigData()
{
    if(m_configfilename.Len() == 0) m_configfilename = wxT("task_") + wxString::Format(wxT("%i"), wxDateTime::Now().GetTicks()) + wxT(".xml");

    XmlTask *xmltask = new XmlTask();
    if(!xmltask->InitData(m_configfilename.mb_str(wxConvUTF8))) return false;

    xmltask->SetElementText(xmltask->GetElement(XMLTASK_NAME, 0, true), m_taskname.mb_str(wxConvUTF8));
    xmltask->SetElementAttribute(xmltask->GetElement(XMLTASK_TIMERTYPE, 0, true), XMLTASK_TIMERTYPE_ATT, m_tasktimmertype);

    xmltask->SetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_INTERVAL, m_timedata.interval_seconds);
    xmltask->SetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_TIME, m_timedata.specified_time);
    xmltask->SetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_HOURS, m_timedata.specified_hours);
    xmltask->SetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_MINUTES, m_timedata.specified_minutes);
    xmltask->SetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_SECONDS, m_timedata.specified_seconds);

    size_t element_num  = m_timedata.specified_date.GetCount();
    size_t element_data = 0;
    for(size_t index = 0; index < element_num; index++)
    {
        element_data = m_timedata.specified_date.Item(index);
        xmltask->SetElementText(xmltask->GetElement(XMLTASK_TIMEDATA_DATA, index, true), wxString::Format(wxT("%i"), element_data).mb_str(wxConvUTF8));
    }

    xmltask->SaveXmlFile();
    return true;
}

void BotTask::ResetTimeData()
{
    m_timedata.interval_seconds = 0;
    m_timedata.specified_time   = 0;
    m_timedata.specified_hours  = 0;
    m_timedata.specified_minutes = 0;
    m_timedata.specified_seconds = 0;
    m_timedata.specified_date.Clear();
}

wxString BotTask::GetTaskName()
{
    return m_taskname;
}

wxString BotTask::GetTaskStatus()
{
    wxString task_status;

    switch(m_taskstatus)
    {
        case TASKSTATUS_STOP:
            task_status = _("Stoped");
            break;

        case TASKSTATUS_WAITING:
            task_status = _("Waiting");
            break;

        case TASKSTATUS_RUNNING:
            task_status = _("Running");
            break;
    }

    return task_status;
}

size_t BotTask::GetTaskType()
{
    return m_tasktimmertype;
}

TimeData BotTask::GetTaskTimeData()
{
    return m_timedata;
}

wxString BotTask::GetTaskTime()
{
    if(m_taskstatus != TASKSTATUS_WAITING) return _("Unknown");

    wxString lefttime_str;
    time_t ticks_left = GetNextTicks();

    if(ticks_left/86400) return wxString::Format(_("%i days later"), ticks_left/86400);
    if(ticks_left/3600) return wxString::Format(_("%i hours later"), ticks_left/3600);

    if(ticks_left/60) lefttime_str = wxString::Format(_("%i minutes"), ticks_left/60);

    if(ticks_left%60)
    {
        lefttime_str += wxString::Format(_(" %i seconds later"), ticks_left%60);
    }
    else
    {
        lefttime_str += _(" later");
    }

    return lefttime_str;
}

size_t BotTask::GetNextTicks()
{
    time_t ticks_left       = 0;
    time_t next_ticks       = 0;
    time_t current_ticks    = wxDateTime::Now().GetTicks();
    size_t datedata_num     = m_timedata.specified_date.GetCount();
    //size_t current_day      = wxDateTime::Now().GetWeekDay();
    size_t target_day       = 0;

    wxDateTime current_datetime = wxDateTime::Now();
    time_t weeks_of_month       = current_datetime.GetWeekOfMonth();

    switch(m_tasktimmertype)
    {
        case TASK_INTERVAL:
            ticks_left = m_lastexecutetime + m_timedata.interval_seconds - current_ticks;
            break;

        case TASK_SPECIFY:
            ticks_left = m_timedata.specified_time - current_ticks;
            break;

        case TASK_DAILY_INTERVAL:
            next_ticks = wxDateTime::Now().ResetTime().GetTicks() + 3600*m_timedata.specified_hours + 60*m_timedata.specified_minutes + m_timedata.specified_seconds;
            if(next_ticks < current_ticks) next_ticks = next_ticks + 86400; // 86400 seconds per day
            ticks_left = next_ticks - current_ticks;
            break;

        case TASK_WEEKLY_INTERVAL:
            m_timedata.specified_date.Sort(CompareDateData);

            for(size_t index = 0; index < datedata_num; index++)
            {
                target_day = m_timedata.specified_date.Item(index);

                //if(target_day >= current_day)
                //{
                //    current_datetime.SetToNextWeekDay((wxDateTime::WeekDay)target_day);
                //}
                //else
                //{
                current_datetime.SetToWeekDay((wxDateTime::WeekDay)target_day, weeks_of_month);
                //}

                current_datetime.SetHour(m_timedata.specified_hours);
                current_datetime.SetMinute(m_timedata.specified_minutes);
                current_datetime.SetSecond(m_timedata.specified_seconds);
                next_ticks = current_datetime.GetTicks();

                if((next_ticks > current_ticks) && !ticks_left) ticks_left = next_ticks - current_ticks;
            }

            if(!ticks_left)
            {
                target_day = m_timedata.specified_date.Item(0);

                current_datetime.SetToWeekDay((wxDateTime::WeekDay)target_day, weeks_of_month + 1);
                current_datetime.SetHour(m_timedata.specified_hours);
                current_datetime.SetMinute(m_timedata.specified_minutes);
                current_datetime.SetSecond(m_timedata.specified_seconds);
                next_ticks = current_datetime.GetTicks();

                //if(target_day == current_day) next_ticks += 604800;

                ticks_left = next_ticks - current_ticks;
            }
            break;

        case TASK_MONTHLY_INTERVAL:
            m_timedata.specified_date.Sort(CompareDateData);

            for(size_t index = 0; index < datedata_num; index++)
            {
                target_day = m_timedata.specified_date.Item(index);

                current_datetime.SetDay(target_day);
                current_datetime.SetHour(m_timedata.specified_hours);
                current_datetime.SetMinute(m_timedata.specified_minutes);
                current_datetime.SetSecond(m_timedata.specified_seconds);
                next_ticks = current_datetime.GetTicks();

                if((next_ticks > current_ticks) && !ticks_left) ticks_left = next_ticks - current_ticks;
            }

            if(!ticks_left)
            {
                target_day = m_timedata.specified_date.Item(0);

                size_t next_month = (size_t)current_datetime.GetMonth() + 1;

                current_datetime.SetMonth((wxDateTime::Month)next_month);
                current_datetime.SetDay(target_day);
                current_datetime.SetHour(m_timedata.specified_hours);
                current_datetime.SetMinute(m_timedata.specified_minutes);
                current_datetime.SetSecond(m_timedata.specified_seconds);
                next_ticks = current_datetime.GetTicks();

                ticks_left = next_ticks - current_ticks;
            }
            break;
    }

    return ticks_left;
}

void BotTask::UpdateTimer()
{
    time_t next_ticks = GetNextTicks();

    if(m_timer)
    {
        m_timer->Stop();

        if(next_ticks < 0)
        {
            m_taskstatus = TASKSTATUS_STOP;
        }
        else
        {
            m_timer->Start(next_ticks * 1000, true);
            m_taskstatus = TASKSTATUS_WAITING;
        }
    }
}

void BotTask::OnTimer(wxTimerEvent& event)
{
    m_taskstatus = TASKSTATUS_RUNNING;

    TaskProcessThread *worker_thread = new TaskProcessThread(this);
    if ( worker_thread->Create() != wxTHREAD_NO_ERROR )
    {
    }
    else
    {
        worker_thread->Run();
    }
}

void BotTask::OnTaskProcessDone( wxTaskProcessEvent& event )
{
    m_lastexecutetime = wxDateTime::Now().GetTicks();
    UpdateTimer();
}

wxString BotTask::GetConfigFileName()
{
    return m_configfilename;
}

void BotTask::SetConfigFileName(wxString config_file)
{
    m_configfilename = config_file;
}
