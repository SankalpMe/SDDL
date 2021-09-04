//
// Created by Sankalp Bhamare on 04/09/21.
//

#include "IO.h"


void SignalMesh::generateMapping(const vector<string> &signalNames) {
    signals.clear();
    portMap.clear();
    signals.resize(signalNames.size());
    int j = 0;
    for(auto &i: signalNames){
        portMap[i] = j;
        j++;
    }
}

int SignalMesh::get_raw_port(const string &signalName) {
    return portMap[signalName];
}

vector<int> SignalMesh::get_raw_ports(const vector<string> &signalName) {
    vector<int> ports(signalName.size());
    for(int i = 0 ; i < ports.size();i++){
        ports[i] = get_raw_port(signalName[i]);
    }
    return ports;
}

bool SignalMesh::get_signal(int raw_port) {
    return signals[raw_port];
}

bool SignalMesh::set_signal(int raw_port, bool value) {
    if(signals[raw_port] != value){
        signals[raw_port] = value;
        return true;
    }else{
        return false;
    }
}

bool SignalMesh::set_signal(const string &signalName, const bool value) {
    int raw_port = get_raw_port(signalName);
    if(signals[raw_port] != value){
        signals[raw_port] = value;
        return true;
    }else{
        return false;
    }
}

vector<bool> SignalMesh::get_signals(const vector<int> &raw_ports) {
    vector<bool> signals_(raw_ports.size());
    for(int i = 0 ; i < raw_ports.size();i++){
        signals_[i] = get_signal(raw_ports[i]);
    }
    return signals_;
}

bool SignalMesh::set_signals(const vector<int> &raw_ports, const vector<bool> &values) {
    bool sigChanged = false;
    for(int i = 0 ; i < raw_ports.size();i++){
        if(set_signal(raw_ports[i],values[i])){
            sigChanged = true;
        }
    }
    return sigChanged;
}

vector<bool> SignalMesh::get_signals(const vector<string> &signalNames){
    vector<bool> signals_(signalNames.size());
    for(int i = 0 ; i < signalNames.size();i++){
        signals_[i] = get_signal(signalNames[i]);
    }
    return signals_;
}

bool SignalMesh::set_signals(const vector<string> &signalNames, const vector<bool> &values) {
    auto raw_ports = get_raw_ports(signalNames);
    bool sigChanged = false;
    for(int i = 0 ; i < raw_ports.size();i++){
        if(set_signal(raw_ports[i],values[i])){
            sigChanged = true;
        }
    }
    return sigChanged;
}

bool SignalMesh::get_signal(const string &signalName) {
    return signals[get_raw_port(signalName)];
}
