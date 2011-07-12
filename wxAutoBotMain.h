#ifndef WXAUTOBOTMAIN_H_INCLUDED
#define WXAUTOBOTMAIN_H_INCLUDED

#include <wx/wx.h>
#include <wx/snglinst.h>

#include "wxAutoBot.h"
#include "AutoBotTask.h"

class MainFrame;
class TaskManager;

class wxAutoBotApp: public wxApp
{
    private:
        wxSingleInstanceChecker *m_checker;
        wxLocale                *m_locale;
        MainFrame               *m_mainframe;
        TaskManager             *m_taskManager;

    public:
        bool    OnInit(void);
        int     OnExit(void);
        void    SetupLocale();

        TaskManager* getTaskManager();
        MainFrame*   getMainFrame();
};

DECLARE_APP(wxAutoBotApp)

#endif // WXAUTOBOTMAIN_H_INCLUDED
