#include <bits/stdc++.h>
using namespace std;
bool running = true;
void signalHandler(int signum)
{
    cout << "Interrupt signal (" << signum << ") received.\n";
    running = false;
}
void reloadConfig(ConfigLoader &configLoader)
{
    while (running)
    {
        configLoader.loadConfig();
        this_thread::sleep_for(chrono::seconds(30));
    }
}
int main()
{
    signal(SIGINT, signalHandler);
    ConfigLoader configLoader("watchdog_config.ini");
    ProcessMonitor processMonitor;
    configLoader.loadConfig();
    processMonitor.updateConfig(configLoader.getProcesses());
    thread configThread(reloadConfig, ref(configLoader));
    while (running)
    {
        processMonitor.monitorProcesses();
        this_thread::sleep_for(chrono::seconds(5));
    }
    configThread.join();
    cout << "Watchdog stopped." << endl;
    return 0;
}