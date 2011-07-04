#ifndef XMLDATA_H_INCLUDED
#define XMLDATA_H_INCLUDED

#include "XmlHandler.h"
#include "GlobalValue.h"

class XmlTask : public XmlHandler
{
    public:
        XmlTask();
        ~XmlTask();

        bool InitData(const char * pfilename);
        //void setTaskId(const char * pid);

/*
        void addAction(const char * pcontent);
        void deleteAciton(size_t index);
        void modifyAction(size_t index, const char * pcontent);
        void commitData();

        const char* getTaskName();
        void setTaskName(const char* pname);
        //time_t      getLastRunDate();
        size_t getTaskTimerType();
        void setTaskTimerType(size_t ptimetype);

        size_t getTaskTimerTime();
        void setTaskTimerTime(const char* ptime);
        //void updateLastRunDate();
*/
};

#endif // XMLDATA_H_INCLUDED
