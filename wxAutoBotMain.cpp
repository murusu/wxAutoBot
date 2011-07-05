#include "wxAutoBotMain.h"

IMPLEMENT_APP(wxAutoBotApp)

bool wxAutoBotApp::OnInit(void)
{
    m_checker       = NULL;
    m_locale        = NULL;
    m_mainframe     = NULL;

    const wxString name = wxString::Format(_("wxAutoBotApp-%s"), wxGetUserId().c_str());
    m_checker = new wxSingleInstanceChecker(name);

    if( m_checker->IsAnotherRunning() )
    {
        wxLogError(_("Another program instance is already running, aborting."));
        return false;
    }

    SetupLocale();

    m_mainframe = new MainFrame(NULL);
    m_mainframe->Show(true);

    m_taskManager = new TaskManager();

    if( !m_taskManager->initTaskManager() )
    {
        wxLogError(_("Initialization fail, aborting."));
        return false;
    }

    //TaskManager*  task_manager = wxGetApp().getTaskManager();
    m_mainframe->m_listCtrl->SetItemCount(m_taskManager->GetTaskNum());
    m_mainframe->m_listCtrl->Refresh();
    m_mainframe->DoListSize();

    return true;
}

int wxAutoBotApp::OnExit()
{
    if(m_checker)   delete m_checker;
    if(m_locale)    delete m_locale;
    return 0;
}

void wxAutoBotApp::SetupLocale()
{
    m_locale = new wxLocale();
    m_locale->Init();

    m_locale->AddCatalogLookupPathPrefix(wxT("./lng"));
    m_locale->AddCatalog(m_locale->GetCanonicalName());
}

TaskManager* wxAutoBotApp::getTaskManager()
{
    return m_taskManager;
}
