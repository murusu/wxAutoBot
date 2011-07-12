#include "AutoBotThread.h"

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
