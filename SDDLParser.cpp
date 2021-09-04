//
// Created by Sankalp Bhamare on 04/09/21.
//

#include "SDDLParser.h"

pair<vector<string>,vector<string>> breakPorts(const string &str){
    istringstream is(str+",");
    char c;
    string token = "";
    vector<string> inres;
    vector<string> ores;
    bool flip = false;
    while (is >> c){
        if(c == ',' || c == ' ' || c == '-'){
            if(!token.empty()){
                if(!flip)
                    inres.push_back(token);
                else
                    ores.push_back(token);
            }
            token ="";
        }else{
            token += c;
        }
        if(c == '-'){
            is >> c;
            if(c == '>'){
                flip = true;
            }
        }
    }

    return {inres,ores};
}