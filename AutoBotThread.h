#ifndef AUTOBOTTHREAD_H_INCLUDED
#define AUTOBOTTHREAD_H_INCLUDED

#include <wx/event.h>
#include <wx/thread.h>

#include "wxAutoBotMain.h"

class BotTask;

class wxTaskProcessEvent : public wxNotifyEvent
{
    public:
        wxTaskProcessEvent(wxEventType commandType = wxEVT_NULL, int id = 0):
            wxNotifyEvent(commandType, id) {}
        wxTaskProcessEvent(const wxTaskProcessEvent& event):
            wxNotifyEvent(event) {}
        virtual wxEvent *Clone() const {
            return new wxTaskProcessEvent(*this);
        }

    DECLARE_DYNAMIC_CLASS(wxTaskProcessEvent);
};

typedef void (wxEvtHandler::*wxTaskProcessEventFunction) (wxTaskProcessEvent&);

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(wxEVT_TASKPROCESS_SUCCESS, 101)
    DECLARE_EVENT_TYPE(wxEVT_TASKPROCESS_FAIL, 102)
END_DECLARE_EVENT_TYPES()

#define EVT_TASKPROCESS_SUCCESS(fn) DECLARE_EVENT_TABLE_ENTRY( \
    wxEVT_TASKPROCESS_SUCCESS, 0, -1, (wxObjectEventFunction) \
    (wxEventFunction) (wxTaskProcessEventFunction) & fn, \
    (wxObject *) NULL ),
#define EVT_TASKPROCESS_FAIL(fn) DECLARE_EVENT_TABLE_ENTRY( \
    wxEVT_TASKPROCESS_ERROR, 0, -1, (wxObjectEventFunction) \
    (wxEventFunction) (wxTaskProcessEventFunction) & fn, \
    (wxObject *) NULL ),

#define wxTaskProcessEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxTaskProcessEventFunction, &func)


class TaskProcessThread : public wxThread
{
    protected:
        BotTask *m_bottask;

    public:
        TaskProcessThread(BotTask *bot_task);

        void *Entry();
        void OnExit();
};


#endif // AUTOBOTTHREAD_H_INCLUDED
