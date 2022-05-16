#include <bits/stdc++.h>
using namespace std;
#include"bloomFilter.cpp"

class Myset{
public:
    //set<pair<int, MobilePhone*>> st; //phone number, MobilePhone object
    bloomFilter* bf; //bloom filter to store mobilephone numbers

    Myset(){
        bf = new bloomFilter(997);
    }

    bool IsEmpty(){
        return bf->getSize() == 0;
        //return st.size() == 0;
    }

    bool IsMember(int pnum){
        
        return bf->isMember(pnum);
        //return st.find({m->pnum, m}) != st.end();
    }

    void Insert(int pnum){
        
        bf->insert_val(pnum);

        /*if (IsMember(m)) {
            cout<<"Mobile: "<<m->pnum<<" is already in this set\n";
            return;
        }
        m->on_off = true;
        st.insert({m->pnum, m});
        */
    }

    void Delete(int pnum){
        
        bf->delete_val(pnum);

        /*if (!IsMember(m)) {
            cout<<"Mobile: "<<m->pnum<<" does not exist in this set\n";
            return;
        }

        st.erase({m->pnum, m});
        */
    }

    //TBDL
    /*void printAll(){
        for (auto i = st.begin(); i!=st.end(); i++){

            cout<<((*i).second->pnum)<<" ";
        }
        cout<<"\n";

    }
    */
};