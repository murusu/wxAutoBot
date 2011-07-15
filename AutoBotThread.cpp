#include "AutoBotThread.h"

DEFINE_EVENT_TYPE(wxEVT_TASKPROCESS_SUCCESS)
DEFINE_EVENT_TYPE(wxEVT_TASKPROCESS_FAIL)
IMPLEMENT_DYNAMIC_CLASS(wxTaskProcessEvent, wxNotifyEvent)

TaskProcessThread::TaskProcessThread(BotTask *bot_task) : wxThread()
{
    m_bottask = bot_task;
}

void TaskProcessThread::OnExit()
{
}

void *TaskProcessThread::Entry()
{
    Sleep(10*1000);
    wxTaskProcessEvent event(wxEVT_TASKPROCESS_SUCCESS);
    m_bottask->AddPendingEvent(event);

    return NULL;
}
