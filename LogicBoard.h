//
// Created by Sankalp Bhamare on 04/09/21.
//

#ifndef BISIM_LOGICBOARD_H
#define BISIM_LOGICBOARD_H

#include <vector>
#include <unordered_map>
#include "Primitive/CustomGates.h"

class Component : public BasicGate {
public:
    string name;
    shared_ptr<SignalMesh> internalSignalMesh;

    IOPort internalInputPort, internalOutputPort;
    vector<shared_ptr<BasicGate>> gates;

    Component() {
        internalSignalMesh = make_shared<SignalMesh>();
    }
    Component(const Component &c2);

    void generateSignalMesh(const vector<string> &signalNames) {
        internalSignalMesh->generateMapping(signalNames);
    }

    void clearGates() {
        gates.clear();
    }

    void connect(const IOPortBus &inputBus, const IOPortBus &outputBus, std::shared_ptr<SignalMesh> signalMesh);

    bool __eval__() {
        internalInputPort.serialize(inputPort.deserialize());
        simulate();
        return outputPort.serialize(internalOutputPort.deserialize());
    }

    template<typename t>
    void insertGate(const IOPortBus &inputBus, const IOPortBus &outputBus) {
        auto gate = std::make_shared<t>();
        gate->connect(inputBus, outputBus, internalSignalMesh);
        gates.push_back(gate);
    }

    void insertComponent(const Component &cp, const IOPortBus &input, const IOPortBus &output) {
        auto component = std::make_shared<Component>(cp);
        component->connect(input, output, internalSignalMesh);
        gates.push_back(component);
    }

    void simulate() {
        while (iterate());
    }

    bool iterate();

    virtual shared_ptr<BasicGate> copy(){
        return make_shared<Component>(*this);
    }
};

class LogicBoard {
    std::shared_ptr<SignalMesh> sm;
    Component dut;
    vector<string> inputPorts;
    vector<string> outputPorts;
public:
    LogicBoard() {
        sm = std::make_shared<SignalMesh>();
    }

    void loadDUT(const Component &cp) {
        dut = Component(cp);
        mapDUTSignals();
        dut.connect(inputPorts,outputPorts,sm);
    }
    void mapDUTSignals();

    void simulate() {
        while (iterate());
    }

    bool iterate() {
        bool sigChange = false;
        sigChange = dut.__eval__();
        return sigChange;
    }

    IOPort getPort(const IOPortBus &bus) {
        IOPort pp;
        pp.signalMesh = sm;
        pp.ioPortBus = bus;
        return pp;
    }
};


#endif //BISIM_LOGICBOARD_H
