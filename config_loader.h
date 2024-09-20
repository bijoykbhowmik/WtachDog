#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H
#include <string>
#include <map>
struct ProcessConfig {
 string name;
 string path;
 string params;
 bool monitor;
 bool restart_on_failure;
};
class ConfigLoader {
public:
 ConfigLoader(const string& filename);
 void loadConfig();
 map<string, ProcessConfig> getProcesses() const;
private:
 string filename;
 map<string, ProcessConfig> processes;
};
#endif 