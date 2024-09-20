#ifndef PROCESS_MONITOR_H
#define PROCESS_MONITOR_H
#include "config_loader.h"
#include <map>
class ProcessMonitor
{
public:
    void updateConfig(const map<string>, ProcessConfig> &newProcesses);
    void monitorProcesses();

private:
    map<string, pid_t> runningProcesses;
    map<string, ProcessConfig> processes;
    void startProcess(const ProcessConfig &process);
    void stopProcess(const string &name);
    void checkProcess(const string &name, const ProcessConfig &process);
};
#endif