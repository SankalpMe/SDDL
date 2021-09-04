//
// Created by Sankalp Bhamare on 04/09/21.
//

#ifndef BISIM_GATES_H
#define BISIM_GATES_H

#include "IO.h"

class BasicGate {
public:
    short in_ports;
    short out_ports;
    IOPort inputPort;
    IOPort outputPort;
    virtual bool __eval__(){
        return outputPort.serialize(eval(inputPort.deserialize()));
    }
    virtual vector<bool> eval(const vector<bool> &i){
        return i;
    }
    virtual shared_ptr<BasicGate> copy(){
        return make_shared<BasicGate>(*this);
    }
    BasicGate(){

    }
    BasicGate(const BasicGate &b){
        in_ports = b.in_ports;
        out_ports = b.out_ports;
        inputPort = b.inputPort;
        outputPort = b.outputPort;
    }
    virtual void connect(IOPortBus inputBus, IOPortBus outputBus, std::shared_ptr<SignalMesh> sm);
};


#endif //BISIM_GATES_H
