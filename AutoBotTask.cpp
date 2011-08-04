#include "AutoBotTask.h"

WX_DEFINE_OBJARRAY(TaskArray);


int CompareDateData(int *first, int *second)
{
    return *first - *second;
}

TaskTimeData::TaskTimeData()
{
    m_specifieddate = new wxArrayInt();
    ResetData();
}

TaskTimeData::~TaskTimeData()
{
}

void TaskTimeData::ResetData()
{
    m_intervalseconds = 0;
    m_specifiedtime = 0;
    m_specifiedhours = 0;
    m_specifiedminutes = 0;
    m_specifiedseconds = 0;
    m_specifieddate->Clear();
}

void TaskTimeData::SetIntervalSeconds(size_t seconds)
{
    m_intervalseconds = seconds;
}

void TaskTimeData::SetSpecifiedTime(time_t time)
{
    m_specifiedtime = time;
}

void TaskTimeData::SetSpecifiedHours(size_t hours)
{
    m_specifiedhours = hours;
}

void TaskTimeData::SetSpecifiedMinutes(size_t minutes)
{
    m_specifiedminutes = minutes;
}

void TaskTimeData::SetSpecifiedSeconds(size_t seconds)
{
    m_specifiedseconds = seconds;
}

size_t TaskTimeData::GetIntervalSeconds()
{
    return m_intervalseconds;
}

time_t TaskTimeData::GetSpecifiedTime()
{
    return m_specifiedtime;
}

size_t TaskTimeData::GetSpecifiedHours()
{
    return m_specifiedhours;
}

size_t TaskTimeData::GetSpecifiedMinutes()
{
    return m_specifiedminutes;
}

size_t TaskTimeData::GetSpecifiedSeconds()
{
    return m_specifiedseconds;
}

wxArrayInt* TaskTimeData::GetSpecifiedDate()
{
    return m_specifieddate;
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
        ptaskitem->StartTask();
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

void TaskManager::AddTask(BotTask *bot_task)
{
    BotTask *ptaskitem = new BotTask();
    ptaskitem->CloneTask(bot_task);
    m_taskarray->Add(ptaskitem);
}

void TaskManager::DeleteTask(size_t index)
{
    BotTask *bot_task = NULL;
    bot_task = m_taskarray->Item(index);

    if(bot_task->GetTaskStatusType() == TASKSTATUS_STOP )
    {
        bot_task->DeleteConfigFile();
        delete bot_task;
        m_taskarray->RemoveAt(index);

        RefreshList();
    }
}

BotTask::BotTask()
{
    m_tasktimmertype    = TASK_INTERVAL;
    m_taskstatus        = TASKSTATUS_STOP;
    m_lastexecutetime   = wxDateTime::Now().GetTicks();
    m_configfilename    = wxT("");
    m_taskname          = wxT("New Task");
    m_timer             = new wxTimer(this);
    m_tasktimedata      = new TaskTimeData();

    m_timer->SetOwner(this);
    this->Connect(wxEVT_TIMER, wxTimerEventHandler(BotTask::OnTimer));

    this->Connect(wxEVT_TASKPROCESS_SUCCESS, wxTaskProcessEventHandler(BotTask::OnTaskProcessDone));
    this->Connect(wxEVT_TASKPROCESS_FAIL, wxTaskProcessEventHandler(BotTask::OnTaskProcessDone));

    //ResetTimeData();
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

    m_tasktimedata->SetIntervalSeconds(atoi(xmltask->GetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_INTERVAL)));
    m_tasktimedata->SetSpecifiedTime(atoi(xmltask->GetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_TIME)));
    m_tasktimedata->SetSpecifiedHours(atoi(xmltask->GetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_HOURS)));
    m_tasktimedata->SetSpecifiedMinutes(atoi(xmltask->GetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_MINUTES)));
    m_tasktimedata->SetSpecifiedSeconds(atoi(xmltask->GetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_SECONDS)));

    size_t element_num  = xmltask->GetElementNum(XMLTASK_TIMEDATA_DATA);
    size_t element_data = 0;
    for(size_t index = 0; index < element_num; index++)
    {
        element_data = atoi(xmltask->GetElementText(xmltask->GetElement(XMLTASK_TIMEDATA_DATA, index)));
        m_tasktimedata->GetSpecifiedDate()->Add(element_data);
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

    xmltask->SetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_INTERVAL, m_tasktimedata->GetIntervalSeconds());
    xmltask->SetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_TIME, m_tasktimedata->GetSpecifiedTime());
    xmltask->SetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_HOURS, m_tasktimedata->GetSpecifiedHours());
    xmltask->SetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_MINUTES, m_tasktimedata->GetSpecifiedMinutes());
    xmltask->SetElementAttribute(xmltask->GetElement(XMLTASK_TIMEDATA, 0, true), XMLTASK_TIMEDATA_SECONDS, m_tasktimedata->GetSpecifiedSeconds());

    size_t element_num  = m_tasktimedata->GetSpecifiedDate()->GetCount();
    size_t element_data = 0;
    for(size_t index = 0; index < element_num; index++)
    {
        element_data = m_tasktimedata->GetSpecifiedDate()->Item(index);
        xmltask->SetElementText(xmltask->GetElement(XMLTASK_TIMEDATA_DATA, index, true), wxString::Format(wxT("%i"), element_data).mb_str(wxConvUTF8));
    }

    xmltask->SaveXmlFile();
    return true;
}

void BotTask::ResetTimeData()
{
    m_tasktimedata->ResetData();
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

        case TASKSTATUS_ERROR:
            task_status = _("Error");
            break;
    }

    return task_status;
}

size_t BotTask::GetTaskType()
{
    return m_tasktimmertype;
}

TaskTimeData* BotTask::GetTaskTimeData()
{
    return m_tasktimedata;
}

wxString BotTask::GetTaskTime()
{
    if(m_taskstatus != TASKSTATUS_WAITING) return _("Unknown");

    wxString lefttime_str;
    time_t ticks_left = GetNextTicks();

    if(ticks_left/86400) //return wxString::Format(_("%i days later"), ticks_left/86400);
    {
        if((ticks_left%86400)/43200)
        {
            return wxString::Format(_("%i days later"), ticks_left/86400 + 1);
        }
        else
        {
            return wxString::Format(_("%i days later"), ticks_left/86400);
        }
    }
    if(ticks_left/3600) //return wxString::Format(_("%i hours later"), ticks_left/3600);
    {
        if((ticks_left%3600)/1800)
        {
            return wxString::Format(_("%i hours later"), ticks_left/3600 + 1);
        }
        else
        {
            return wxString::Format(_("%i hours later"), ticks_left/3600);
        }
    }

    if(ticks_left/60) lefttime_str = wxString::Format(_("%i minutes"), ticks_left/60);

    if(ticks_left%60)
    {
        lefttime_str += wxString::Format(_(" %i seconds later"), ticks_left%60);
    }
    else
    {
        if(ticks_left/60) lefttime_str += _(" later");
    }

    return lefttime_str;
}

size_t BotTask::GetNextTicks()
{
    time_t ticks_left       = 0;
    time_t next_ticks       = 0;
    time_t current_ticks    = wxDateTime::Now().GetTicks();
    size_t datedata_num     = m_tasktimedata->GetSpecifiedDate()->GetCount();
    size_t target_day       = 0;


    wxDateTime current_datetime = wxDateTime::Now();
    time_t weeks_of_month       = current_datetime.GetWeekOfMonth();

    switch(m_tasktimmertype)
    {
        case TASK_INTERVAL:
            ticks_left = m_lastexecutetime + m_tasktimedata->GetIntervalSeconds() - current_ticks;
            if(ticks_left < 0) ticks_left = 0;
            break;

        case TASK_SPECIFY:
            ticks_left = m_tasktimedata->GetSpecifiedTime() + m_tasktimedata->GetSpecifiedHours() * 3600 + m_tasktimedata->GetSpecifiedMinutes() * 60 + m_tasktimedata->GetSpecifiedSeconds() - current_ticks;
            break;

        case TASK_DAILY_INTERVAL:
            next_ticks = wxDateTime::Now().ResetTime().GetTicks() + 3600*m_tasktimedata->GetSpecifiedHours() + 60*m_tasktimedata->GetSpecifiedMinutes() + m_tasktimedata->GetSpecifiedSeconds();
            if(next_ticks < current_ticks) next_ticks = next_ticks + 86400; // 86400 seconds per day
            ticks_left = next_ticks - current_ticks;
            break;

        case TASK_WEEKLY_INTERVAL:
            m_tasktimedata->GetSpecifiedDate()->Sort(CompareDateData);

            for(size_t index = 0; index < datedata_num; index++)
            {
                target_day = m_tasktimedata->GetSpecifiedDate()->Item(index);
                current_datetime.SetToWeekDay((wxDateTime::WeekDay)target_day, weeks_of_month);

                current_datetime.SetHour(m_tasktimedata->GetSpecifiedHours());
                current_datetime.SetMinute(m_tasktimedata->GetSpecifiedMinutes());
                current_datetime.SetSecond(m_tasktimedata->GetSpecifiedSeconds());
                next_ticks = current_datetime.GetTicks();

                if((next_ticks > current_ticks) && !ticks_left) ticks_left = next_ticks - current_ticks;
            }

            if(!ticks_left)
            {
                target_day = m_tasktimedata->GetSpecifiedDate()->Item(0);

                current_datetime.SetToWeekDay((wxDateTime::WeekDay)target_day, weeks_of_month + 1);
                current_datetime.SetHour(m_tasktimedata->GetSpecifiedHours());
                current_datetime.SetMinute(m_tasktimedata->GetSpecifiedMinutes());
                current_datetime.SetSecond(m_tasktimedata->GetSpecifiedSeconds());
                next_ticks = current_datetime.GetTicks();

                ticks_left = next_ticks - current_ticks;
            }
            break;

        case TASK_MONTHLY_INTERVAL:
            m_tasktimedata->GetSpecifiedDate()->Sort(CompareDateData);

            for(size_t index = 0; index < datedata_num; index++)
            {
                target_day = m_tasktimedata->GetSpecifiedDate()->Item(index);

                current_datetime.SetDay(target_day);
                current_datetime.SetHour(m_tasktimedata->GetSpecifiedHours());
                current_datetime.SetMinute(m_tasktimedata->GetSpecifiedMinutes());
                current_datetime.SetSecond(m_tasktimedata->GetSpecifiedSeconds());
                next_ticks = current_datetime.GetTicks();

                if((next_ticks > current_ticks) && !ticks_left) ticks_left = next_ticks - current_ticks;
            }

            if(!ticks_left)
            {
                target_day = m_tasktimedata->GetSpecifiedDate()->Item(0);

                size_t next_month = (size_t)current_datetime.GetMonth() + 1;

                current_datetime.SetMonth((wxDateTime::Month)next_month);
                current_datetime.SetDay(target_day);
                current_datetime.SetHour(m_tasktimedata->GetSpecifiedHours());
                current_datetime.SetMinute(m_tasktimedata->GetSpecifiedMinutes());
                current_datetime.SetSecond(m_tasktimedata->GetSpecifiedSeconds());
                next_ticks = current_datetime.GetTicks();

                ticks_left = next_ticks - current_ticks;
            }
            break;
    }

    return ticks_left;
}

void BotTask::StartTask()
{
    time_t next_ticks = GetNextTicks();

    if(m_timer)
    {
        m_timer->Stop();

        if(next_ticks < 0)
        {
            m_taskstatus = TASKSTATUS_ERROR;
        }
        else
        {
            m_taskstatus = TASKSTATUS_WAITING;
            m_timer->Start(next_ticks * 1000, true);
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
    StartTask();
}

wxString BotTask::GetConfigFileName()
{
    return m_configfilename;
}

void BotTask::SetConfigFileName(wxString config_file)
{
    m_configfilename = config_file;
}

bool BotTask::DeleteConfigFile()
{
    if(m_configfilename.Len())
    {
        wxRemoveFile(wxString(XMLTASK_PATH, wxConvUTF8) + wxT("/") + m_configfilename);
    }

    return true;
}

void BotTask::StopTask()
{
    m_timer->Stop();
    m_taskstatus = TASKSTATUS_STOP;
    //m_lastexecutetime = wxDateTime::Now().GetTicks();
}

time_t BotTask::GetLastExecuteTime()
{
    return m_lastexecutetime;
}

size_t BotTask::GetTaskStatusType()
{
    return m_taskstatus;
}

void BotTask::SetTaskName(wxString task_name)
{
    m_taskname = task_name;
}

void BotTask::SetTaskType(size_t task_type)
{
    m_tasktimmertype = task_type;
}

void BotTask::CloneTask(BotTask *bot_task)
{
    ResetTimeData();

    m_taskstatus = bot_task->GetTaskStatusType();
    m_tasktimmertype = bot_task->GetTaskType();
    m_lastexecutetime = bot_task->GetLastExecuteTime();
    m_configfilename = bot_task->GetConfigFileName();
    m_taskname = bot_task->GetTaskName();

    m_tasktimedata->SetIntervalSeconds(bot_task->GetTaskTimeData()->GetIntervalSeconds());
    m_tasktimedata->SetSpecifiedTime(bot_task->GetTaskTimeData()->GetSpecifiedTime());
    m_tasktimedata->SetSpecifiedHours(bot_task->GetTaskTimeData()->GetSpecifiedHours());
    m_tasktimedata->SetSpecifiedMinutes(bot_task->GetTaskTimeData()->GetSpecifiedMinutes());
    m_tasktimedata->SetSpecifiedSeconds(bot_task->GetTaskTimeData()->GetSpecifiedSeconds());

    size_t datedata_num = bot_task->GetTaskTimeData()->GetSpecifiedDate()->GetCount();
    m_tasktimedata->GetSpecifiedDate()->Clear();
    for(size_t index = 0; index < datedata_num; index++)
    {
        m_tasktimedata->GetSpecifiedDate()->Add(bot_task->GetTaskTimeData()->GetSpecifiedDate()->Item(index));
    }
}


