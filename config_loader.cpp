#include <bits/stdc++.h>
#include "config_loader.h"
using namespace std;
ConfigLoader::ConfigLoader(const string &filename) : filename(filename) {}
void ConfigLoader::loadConfig()
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not open config file!" << endl;
        return;
    }
    processes.clear();
    string line, currentSection;
    ProcessConfig tempProcess;

    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        if (line[0] == '[')
        {
            if (!currentSection.empty())
            {
                processes[currentSection] = tempProcess;
            }
            currentSection = line.substr(1, line.size() - 2);
            tempProcess = ProcessConfig();
        }
        else
        {
            istringstream iss(line);
            string key, value;
            if (getline(iss, key, '=') && getline(iss, value))
            {
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));

                if (key == "name")
                    tempProcess.name = value;
                else if (key == "path")
                    tempProcess.path = value;
                else if (key == "params")
                    tempProcess.params = value;
                else if (key == "monitor")
                    tempProcess.monitor = (value == "true");
                else if (key == "restart_on_failure")
                    tempProcess.restart_on_failure = (value == "true");
            }
        }
    }
    if (!currentSection.empty())
    {
        processes[currentSection] = tempProcess;
    }
    file.close();
}
map<string, ProcessConfig> ConfigLoader::getProcesses() const
{
    return processes;
}
