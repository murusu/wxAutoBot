#ifndef GLOBALVALUE_H_INCLUDED
#define GLOBALVALUE_H_INCLUDED

const size_t TASK_NAME          = 0;
const size_t TASK_TIME          = 1;
const size_t TASK_STATUS        = 2;

const char * const XMLTASK_PATH     = "tasks";
const char * const XMLTASK_ROOTNAME = "task";
const char * const XMLLOG_PATH      = "logs";
const char * const XMLLOG_ROOTNAME  = "log";

const size_t TASKSTATUS_STOP    = 1;
const size_t TASKSTATUS_WAITING = 2;
const size_t TASKSTATUS_RUNNING = 3;

const size_t TASK_INTERVAL          = 0;
const size_t TASK_SPECIFY           = 1;
const size_t TASK_DAILY_INTERVAL    = 2;
const size_t TASK_WEEKLY_INTERVAL   = 3;
const size_t TASK_MONTHLY_INTERVAL  = 4;

const char * const XMLTASK_NAME             = "name";
const char * const XMLTASK_TIMERTYPE        = "timer_type";
const char * const XMLTASK_TIMERTYPE_ATT    = "type";
const char * const XMLTASK_TIMEDATA         = "time_data";
const char * const XMLTASK_TIMEDATA_INTERVAL= "interval";
const char * const XMLTASK_TIMEDATA_TIME    = "time";
const char * const XMLTASK_TIMEDATA_HOURS   = "hours";
const char * const XMLTASK_TIMEDATA_MINUTES = "minutes";
const char * const XMLTASK_TIMEDATA_SECONDS = "seconds";
const char * const XMLTASK_TIMEDATA_DATA    = "time_data/data";

#endif // GLOBALVALUE_H_INCLUDED
