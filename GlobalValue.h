#ifndef GLOBALVALUE_H_INCLUDED
#define GLOBALVALUE_H_INCLUDED

const size_t TASK_NAME          = 1;
const size_t TASK_TIME          = 2;
const size_t TASK_STATUS        = 3;

const char * const XMLTASK_PATH     = "tasks";
const char * const XMLTASK_ROOTNAME = "task";
const char * const XMLLOG_PATH      = "logs";
const char * const XMLLOG_ROOTNAME  = "log";

const size_t TASKSTATUS_STOP    = 1;
const size_t TASKSTATUS_WAITING = 2;
const size_t TASKSTATUS_RUNNING = 3;

const size_t TASK_INTERVAL          = 1;
const size_t TASK_SPECIFY           = 2;
const size_t TASK_DAILY_INTERVAL    = 3;
const size_t TASK_WEEKLY_INTERVAL   = 4;
const size_t TASK_MONTHLY_INTERVAL  = 5;

const char * const XMLTASK_NAME     = "name";

#endif // GLOBALVALUE_H_INCLUDED
