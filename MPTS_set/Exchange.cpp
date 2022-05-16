#include"ExchangeList.cpp"
#include"MobilePhoneSet.cpp"

class Exchange{
//forms nodes of routing map structure
public:
    int ex_id;
    Exchange* par;
    ExchangeList* ex_list;
    MobilePhoneSet* rset;//resident set, stores all mobile part of this exchange


    Exchange(int num){
        ex_id = num;
        par = NULL;
        ex_list = new ExchangeList();
        rset = new MobilePhoneSet();
    }

    Exchange* parent(){
        return par;
    }

    int numChildren(){
        return ex_list->getSize();
    }

    Exchange* child(int i){
        //returns ith child of this exchange
        return ex_list->getChild(i);
    }

    bool isRoot(){
        return par == NULL;
    }

    //RoutingMapTree* subtree(int i){}

    MobilePhoneSet* residentSet(){
        return rset;
    }

    void deleteMobile(MobilePhone* a){

        rset->myset->Delete(a);
        if (par != NULL) par->deleteMobile(a);
    }

    void addMobile(MobilePhone* a){
        rset->myset->Insert(a);
        if (par != NULL) par->addMobile(a);
    }

    void addExchange(Exchange* b){
        b->par = this;
        ex_list->insertFront(b);
    }

    void printMobiles(){
        rset->myset->printAll();
    }

    Exchange* find(MobilePhone* m){

        if (ex_list->getSize() == 0) return this; //exchange is a base station itself

        ExchangeListNode* itr = ex_list->head;

        while(!itr->e->rset->myset->IsMember(m)){
            itr = itr->next;
            if (itr == NULL) cout<<"Something is wrong :(\n";
        }

        return itr->e->find(m);
    }


};