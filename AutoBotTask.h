#ifndef AUTOBOTTASK_H_INCLUDED
#define AUTOBOTTASK_H_INCLUDED

#include <wx/dir.h>
#include <wx/dynarray.h>
#include <wx/arrimpl.cpp>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/timer.h>

#include "GlobalValue.h"
#include "XmlData.h"
#include "wxAutoBotMain.h"
#include "AutoBotThread.h"

class BotTask;
class wxTaskProcessEvent;

WX_DECLARE_OBJARRAY(BotTask *, TaskArray);
/*
struct TimeData
{
    size_t interval_seconds;
    time_t specified_time;
    size_t specified_hours;
    size_t specified_minutes;
    size_t specified_seconds;
    wxArrayInt specified_date;
};
*/
class TaskTimeData
{
    private:
        size_t m_intervalseconds;
        time_t m_specifiedtime;
        size_t m_specifiedhours;
        size_t m_specifiedminutes;
        size_t m_specifiedseconds;
        wxArrayInt* m_specifieddate;

    public:
        TaskTimeData();
        ~TaskTimeData();

        void ResetData();

        void SetIntervalSeconds(size_t seconds);
        void SetSpecifiedTime(time_t time);
        void SetSpecifiedHours(size_t hours);
        void SetSpecifiedMinutes(size_t minutes);
        void SetSpecifiedSeconds(size_t seconds);
        //void AddSpecifiedSDate(size_t date);

        size_t GetIntervalSeconds();
        time_t GetSpecifiedTime();
        size_t GetSpecifiedHours();
        size_t GetSpecifiedMinutes();
        size_t GetSpecifiedSeconds();
        wxArrayInt* GetSpecifiedDate();
};

class TaskManager : public wxEvtHandler
{
    private:
        TaskArray* m_taskarray;
        wxTimer*   m_timer;

    protected:
        void OnTimer(wxTimerEvent& event);

    public:
        TaskManager();
        ~TaskManager();

        bool initTaskManager();
        size_t GetTaskNum();
        TaskArray* GetTaskArray();

        wxString GetTaskName(long index);
        wxString GetTaskTime(long index);
        wxString GetTaskStatus(long index);

        void AddTask(BotTask *bot_task);
        void DeleteTask(size_t index);

        void RefreshList();
};

class BotTask : public wxEvtHandler
{
    private:
        size_t      m_taskstatus;
        size_t      m_tasktimmertype;
        time_t      m_lastexecutetime;
        wxString    m_configfilename;
        wxString    m_taskname;
        //TimeData    m_timedata;
        TaskTimeData* m_tasktimedata;
        wxTimer*    m_timer;

    protected:
        void OnTimer(wxTimerEvent& event);
        void OnTaskProcessDone( wxTaskProcessEvent& event );

    public:
        BotTask();
        ~BotTask();

        bool ReadConfigData(wxString filename);
        bool WriteConfigData();
        void ResetTimeData();

        wxString GetTaskName();
        wxString GetTaskStatus();
        wxString GetTaskTime();

        size_t GetTaskType();
        TaskTimeData* GetTaskTimeData();
        size_t GetNextTicks();
        time_t GetLastExecuteTime();
        size_t GetTaskStatusType();

        void StartTask();
        void StopTask();

        wxString GetConfigFileName();
        void SetConfigFileName(wxString config_file);
        bool DeleteConfigFile();

        void SetTaskName(wxString task_name);
        void SetTaskType(size_t task_type);
        void CloneTask(BotTask *bot_task);
};

#endif // AUTOBOTTASK_H_INCLUDED
