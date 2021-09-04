//
// Created by Sankalp Bhamare on 04/09/21.
//

#ifndef BISIM_CUSTOMGATES_H
#define BISIM_CUSTOMGATES_H
#include "Gates.h"
#define CustomGate(NAME,IN,OUT) \
class Gate ##NAME : public BasicGate { \
    public:                            \
    Gate ##NAME() : BasicGate() {                       \
        in_ports = IN;              \
        out_ports = OUT;            \
    }                           \
    shared_ptr<BasicGate> copy(){         \
        return make_shared<Gate ##NAME>(*this);                            \
    }                            \
    vector<bool> eval(const vector<bool> &i){ \
    vector<bool> o(out_ports);      \

#define  EndGate return  o; }};


CustomGate(AND,2,1)
        o[0] = i[1] && i[0];
EndGate

CustomGate(OR,2,1)
        o[0] = i[1] || i[0];
EndGate

CustomGate(NOR,2,1)
        o[0] = !(i[1] || i[0]);
EndGate

CustomGate(NOT,1,1)
        o[0] = !i[0];
EndGate

CustomGate(NAND,2,1)
        o[0] = !(i[0] && i[1]);
EndGate

CustomGate(XOR,2,1)
        o[0] = (i[0] && !i[1]) || (!i[0] && i[1]);
EndGate

#endif //BISIM_CUSTOMGATES_H
