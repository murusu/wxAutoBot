#ifndef AUTOBOTTASK_H_INCLUDED
#define AUTOBOTTASK_H_INCLUDED

#include <wx/dir.h>
#include <wx/dynarray.h>
#include <wx/arrimpl.cpp>
#include <wx/filefn.h>
#include <wx/filename.h>

#include "GlobalValue.h"
#include "XmlData.h"
#include "wxAutoBotMain.h"

class BotTask;
WX_DECLARE_OBJARRAY(BotTask *, TaskArray);

struct TimeData
{
    size_t interval_seconds;
    time_t specified_time;
    size_t specified_hours;
    size_t specified_minutes;
    size_t specified_seconds;
    wxArrayInt specified_date;
};

class TaskManager
{
    private:
        TaskArray* m_taskarray;

    public:
        TaskManager();
        ~TaskManager();

        bool initTaskManager();
        size_t GetTaskNum();

        wxString GetTaskName(long index);
        wxString GetTaskTime(long index);
        wxString GetTaskStatus(long index);
};

class BotTask
{
    private:
        size_t      m_taskstatus;
        size_t      m_tasktimmertype;
        time_t      m_lastexecutetime;
        wxString    m_configfilename;
        wxString    m_taskname;
        TimeData    m_timedata;

    public:
        BotTask();
        ~BotTask();

        bool ReadConfigData(wxString filename);
        bool WriteConfigData();
        void ResetTimeData();

        wxString GetTaskName();
        wxString GetTaskStatus();
        wxString GetTaskTime();
};

#endif // AUTOBOTTASK_H_INCLUDED
