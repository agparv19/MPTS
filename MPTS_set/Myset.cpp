#include <bits/stdc++.h>
using namespace std;
#include"MobilePhone.cpp"

class Myset{
public:
    set<pair<int, MobilePhone*>> st; //phone number, MobilePhone object

    bool IsEmpty(){
        return st.size() == 0;
    }

    bool IsMember(MobilePhone* m){
        //O(logn)
        return st.find({m->pnum, m}) != st.end();
    }

    void Insert(MobilePhone* m){
        //O(logn)
        if (IsMember(m)) {
            cout<<"Mobile: "<<m->pnum<<" is already in this set\n";
            return;
        }
        m->on_off = true;
        st.insert({m->pnum, m});
    }

    void Delete(MobilePhone* m){
        //O(logn)
        if (!IsMember(m)) {
            cout<<"Mobile: "<<m->pnum<<" does not exist in this set\n";
            return;
        }

        st.erase({m->pnum, m});
    }

    Myset* Union(Myset* a){

        Myset* res = new Myset();

        for (auto i = a->st.begin(); i!= a->st.end(); i++){

            res->Insert((*i).second);
        }

        for (auto i = st.begin(); i!= st.end(); i++){

            res->Insert((*i).second);
        }

        return res;

    }

    Myset* Intersection(Myset* a){

        Myset* res = new Myset();

        for (auto i = a->st.begin(); i!= a->st.end(); i++){

            if (IsMember((*i).second)) res->Insert((*i).second);   
        }
        return res;
    }

    void printAll(){
        for (auto i = st.begin(); i!=st.end(); i++){

            cout<<((*i).second->pnum)<<" ";
        }
        cout<<"\n";

    }






};