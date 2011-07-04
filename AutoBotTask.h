#ifndef AUTOBOTTASK_H_INCLUDED
#define AUTOBOTTASK_H_INCLUDED

#include <wx/dir.h>
#include <wx/dynarray.h>
#include <wx/arrimpl.cpp>
#include <wx/filefn.h>
#include <wx/filename.h>

#include "GlobalValue.h"
#include "XmlHandler.h"
#include "wxAutoBotMain.h"

class BotTask;
WX_DECLARE_OBJARRAY(BotTask *, TaskArray);

class TaskManager
{
    private:
        TaskArray* m_taskarray;

    public:
        TaskManager();
        ~TaskManager();

        bool initTaskManager();
};

class BotTask
{
    private:
        size_t      m_taskstatus;
        size_t      m_tasktimmertype;
        time_t      m_lastexecutetime;
        wxString    m_configfilename;
        wxString    m_taskname;

    public:
        BotTask();
        ~BotTask();

        bool ReadConfigData(wxString filename);
        bool WriteConfigData();
};

#endif // AUTOBOTTASK_H_INCLUDED
