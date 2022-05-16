#include <bits/stdc++.h>
using namespace std;
class Exchange;

class ExchangeListNode{
    //Implements Node of exchange list

    public:
        Exchange* e;
        ExchangeListNode* next;
        
        ExchangeListNode(Exchange* ex){
            e = ex;
            next = NULL;
        }
   
};
