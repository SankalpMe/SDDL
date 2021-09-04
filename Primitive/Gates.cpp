//
// Created by Sankalp Bhamare on 04/09/21.
//

#include "Gates.h"

void BasicGate::connect(IOPortBus inputBus, IOPortBus outputBus, std::shared_ptr<SignalMesh> sm){
    assert(in_ports == inputBus.size);
    assert(out_ports == outputBus.size);
    inputPort.ioPortBus = inputBus;
    outputPort.ioPortBus = outputBus;
    inputPort.signalMesh = sm;
    outputPort.signalMesh = sm;
}
