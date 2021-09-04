//
// Created by Sankalp Bhamare on 04/09/21.
//

#ifndef BISIM_SDDLPARSER_H
#define BISIM_SDDLPARSER_H
#include "LogicBoard.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
pair<vector<string>,vector<string>> breakPorts(const string &str);

class ComponentParser{
public:
    Component readFile(const string &fname,unordered_map<string,Component> cmp={}){
        Component cb;
        ifstream fin(fname);
        string s;
        vector<string> signals;
        vector<string> inputs;
        vector<string> outputs;
        cb.clearGates();
        while (getline(fin,s)){
            if(s.empty()) continue;

            istringstream is(s);
            string cmd;
            is >> cmd;
            string args;
            getline(is,args);

            auto argi = breakPorts(args);


            if(cmd == "component"){
                cb.name = argi.first[0];
            }else
            if(cmd == "signal"){
                for(auto &i : argi.first){
                    signals.push_back(i);
                }
                cb.generateSignalMesh(signals);
            }else
            if(cmd == "input"){
                for(auto &i : argi.first){
                    signals.push_back(i);
                    inputs.push_back(i);
                }
                cb.generateSignalMesh(signals);
            }else
            if(cmd == "output"){
                for(auto &i : argi.first){
                    signals.push_back(i);
                    outputs.push_back(i);
                }
                cb.generateSignalMesh(signals);
            }else{
                if(cmd == "and"){
                    cb.insertGate<GateAND>(argi.first, argi.second);
                }else
                if(cmd == "or"){
                    cb.insertGate<GateOR>(argi.first, argi.second);
                }else if(cmd == "not"){
                    cb.insertGate<GateNOT>(argi.first, argi.second);
                }else if(cmd == "nor"){
                    cb.insertGate<GateNOR>(argi.first, argi.second);
                }else if(cmd == "nand"){
                    cb.insertGate<GateNAND>(argi.first, argi.second);
                }else if(cmd == "xor"){
                    cb.insertGate<GateXOR>(argi.first, argi.second);
                }else if(cmp.find(cmd) != cmp.end()){
                    cb.insertComponent(cmp[cmd], argi.first, argi.second);
                }

            }

        }
        cb.internalOutputPort.ioPortBus = IOPortBus(outputs);
        cb.internalInputPort.ioPortBus = IOPortBus(inputs);
        cb.internalInputPort.signalMesh = cb.internalSignalMesh;
        cb.internalOutputPort.signalMesh = cb.internalSignalMesh;
        cb.in_ports = inputs.size();
        cb.out_ports = outputs.size();
        return cb;
    }
};
class SDDLParser {
public:
    LogicBoard lb;
    vector<string> ip;
    vector<string> op;
    unordered_map<string,Component> componentTable;
    void readComponents(const string &fname){
        ifstream fin(fname);
        string file;
        ComponentParser cp;

        cout << endl << endl;
        while(getline(fin,file)){
            if(file.empty()) continue;

            cout << "Compiling (" << file << ")" << endl;
                 auto component = cp.readFile(file,componentTable);
            componentTable[component.name] = component;

        }
        cout  << "\r"<< endl;
        cout << "Compiled All Files Loaded (order.txt)" << endl;
        cout << "Ready for IO!" << endl << endl;
    }
    void readFile(const string &fname) {
        readComponents(fname);
        lb.loadDUT(componentTable["dut"]);
        ip = componentTable["dut"].internalInputPort.ioPortBus.ports;
        op = componentTable["dut"].internalOutputPort.ioPortBus.ports;
    }
};


#endif //BISIM_SDDLPARSER_H
