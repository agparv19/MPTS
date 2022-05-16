#include <bits/stdc++.h>
using namespace std;
#include "RoutingMapTree.cpp"

int main(){
    
    fstream actionFile;
    actionFile.open("actions2.txt", ios::in);

    RoutingMapTree* r = new RoutingMapTree(); 

    string action;

    while(getline(actionFile, action)){
        //cout<<action<<"\n";
        r->performAction(action);
    }

    actionFile.close();
}