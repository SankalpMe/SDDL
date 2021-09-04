//
// Created by Sankalp Bhamare on 04/09/21.
//

#ifndef BISIM_IO_H
#define BISIM_IO_H
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class SignalMesh{
    vector<bool> signals;
    unordered_map<string, int> portMap;
public:
    void generateMapping(const vector<string>& signalNames);
    int get_raw_port(const string& signalName);
    vector<int> get_raw_ports(const vector<string>& signalName);
    bool get_signal(int raw_port);
    bool set_signal(int raw_port,bool value);
    bool get_signal(const string &signalName);
    bool set_signal(const string &signalName,const bool value);
    vector<bool> get_signals(const vector<int>& raw_ports);
    bool set_signals(const vector<int>& raw_ports,const vector<bool> &values);
    vector<bool> get_signals(const vector<string>& signalNames);
    bool set_signals(const vector<string>& signalNames, const vector<bool> &values);
};

class IOPortBus {

public:
    size_t size;
    vector<string> ports;
    IOPortBus(){
        size = 0;
        ports.resize(0);
    }
    IOPortBus(const vector<string> &signalNames){
        size = signalNames.size();
        ports = signalNames;
    }

    IOPortBus(initializer_list<string> signalNames){
        size = signalNames.size();
        ports = signalNames;
    }
};
class IOPort{
public:
    std::shared_ptr<SignalMesh> signalMesh;
    IOPortBus ioPortBus;
    IOPort(const IOPort& other){
        ioPortBus = other.ioPortBus;
        signalMesh = other.signalMesh;
    }
    IOPort(){
        signalMesh = nullptr;
    }
    vector<bool> deserialize() const{
        return signalMesh->get_signals(ioPortBus.ports);
    }
    bool serialize(const vector<bool> &values) const{
        return signalMesh->set_signals(ioPortBus.ports, values);
    }
};


#endif //BISIM_IO_H
