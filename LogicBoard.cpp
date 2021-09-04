//
// Created by Sankalp Bhamare on 04/09/21.
//

#include "LogicBoard.h"

void Component::connect(const IOPortBus &inputBus,const IOPortBus &outputBus, std::shared_ptr<SignalMesh> signalMesh) {
    inputPort.ioPortBus = inputBus;
    inputPort.signalMesh = signalMesh;
    outputPort.signalMesh = signalMesh;
    outputPort.ioPortBus = outputBus;
}

Component::Component(const Component &c2) {
    name = c2.name;
    in_ports = c2.in_ports;
    out_ports = c2.out_ports;

    internalSignalMesh = make_shared<SignalMesh>(*c2.internalSignalMesh);
    internalInputPort = c2.internalInputPort;
    internalOutputPort = c2.internalOutputPort;
    internalInputPort.signalMesh = internalSignalMesh;
    internalOutputPort.signalMesh = internalSignalMesh;

    gates.resize(c2.gates.size());
    for(int i = 0 ;i < c2.gates.size();i++){
        gates[i] = c2.gates[i]->copy();
        gates[i]->connect(c2.gates[i]->inputPort.ioPortBus,c2.gates[i]->outputPort.ioPortBus,internalSignalMesh);
    }
}

bool Component::iterate() {
    bool sigChange = false;
    for (auto &g: gates) {
        if (g->__eval__()) {
            sigChange = true;
        }
    }
    return sigChange;
}

void LogicBoard::mapDUTSignals() {
    inputPorts = dut.internalInputPort.ioPortBus.ports;
    outputPorts = dut.internalOutputPort.ioPortBus.ports;
    vector<string> signals;

    for(auto &i: inputPorts){
        signals.push_back(i);
    }
    for(auto &i: outputPorts){
        signals.push_back(i);
    }
    sm->generateMapping(signals);
}
