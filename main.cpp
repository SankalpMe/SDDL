#include <iostream>
#include <vector>
#include <map>

#include "LogicBoard.h"
#include "SDDLParser.h"
#include "Greetor.h"
using namespace std;


int main(int argc,char **argv){
    printTitle();
    SDDLParser sp;
    sp.readFile("order.txt");

    LogicBoard &lb = sp.lb;

    auto ip = lb.getPort(sp.ip);
    auto op = lb.getPort(sp.op);
    vector<bool> tip(ip.ioPortBus.size);
    vector<bool> top(op.ioPortBus.size);
    while (true){
        string s;
        for(auto i : sp.ip)
            cout << "<" << i << ">";
        cout << endl;
        cout << "input:";
        cin >> s;
        if(s == "-1"){
            break;
        }
        int j = 0;
        for(auto c : s){
            tip[j] = c == '1';
            j++;
        }
        ip.serialize(tip);
        lb.simulate();
        top = op.deserialize();
        for(int i = 0; i < top.size();i++){
            cout << op.ioPortBus.ports[i] << ": " << top[i] << endl;
        }
        cout << endl << endl;
    }
}

