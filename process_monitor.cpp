#include "process_monitor.h"
#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
using namespace std;
void ProcessMonitor::updateConfig(const map<string, ProcessConfig> &newProcesses)
{
    processes = newProcesses;
}
void ProcessMonitor::monitorProcesses()
{
    for (const auto &[name, process] : processes)
    {
        checkProcess(name, process);
    }
}
void ProcessMonitor::startProcess(const ProcessConfig &process)
{
    pid_t pid = fork();
    if (pid == 0)
    {

        execl(process.path.c_str(), process.name.c_str(), process.params.c_str(), NULL);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        runningProcesses[process.name] = pid;
        cout << "Started process: " << process.name << " with PID: " << pid << endl;
    }
}
void ProcessMonitor::stopProcess(const string &name)
{
    if (runningProcesses.count(name))
    {
        kill(runningProcesses[name], SIGTERM);
        waitpid(runningProcesses[name], nullptr, 0);
        runningProcesses.erase(name);
        cout << "Stopped process: " << name << endl;
    }
}
void ProcessMonitor::checkProcess(const string &name, const ProcessConfig &process)
{
    if (runningProcesses.find(name) == runningProcesses.end())
    {
        if (process.monitor)
        {
            startProcess(process);
        }
    }
    else
    {
        // Check if process is running
        pid_t result = waitpid(runningProcesses[name], nullptr, WNOHANG);
        if (result == 0)
        {
        }
        else
        {
            cout << "Process " << name << " has stopped. Restarting..." << endl;
            startProcess(process);
        }
    }
}