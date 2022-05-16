#include "Exchange.cpp"

class RoutingMapTree{
    public:
        Exchange* root;
        unordered_map<int, Exchange*> ex_map; //exchange map
        unordered_map<int, MobilePhone*> mp_map; //mobilephone map

        RoutingMapTree(){
            root = new Exchange(0);
            ex_map[0] = root;
        }

        bool containsExchange(Exchange* e){
            return root->ex_list->isMember(e);
        }

        void switchOn(MobilePhone* a, Exchange* b){
            
            if (a->on_off) return; //return if phone is already on

            a->switchOn();
            a->set_base(b);
            b->addMobile(a);//update the RMT
        }

        void switchOff(MobilePhone* a){
            
            if (!a->on_off) return; //return if phone is off

            Exchange* temp = a->location();
            a->switchOff();
            a->set_base(NULL);
            temp->deleteMobile(a); //Recusrively delted a from base startion uptill root
        }

        Exchange* lowestRouter(Exchange* a, Exchange* b){
            if (a==b) return a;

            return lowestRouter(a->parent(), b->parent());
            
        }

        void movePhone(MobilePhone* a, Exchange* b){

            switchOff(a);
            switchOn(a, b);
        }

        Exchange* findPhone(MobilePhone* m){

            if (!root->rset->myset->IsMember(m)){
                cout<<"MobilePhone "<<m->pnum<<" is switched off\n";
                return NULL;
            }

            return root->find(m);

        }

        ExchangeList* routeCall(MobilePhone* a, MobilePhone* b){

            Exchange* base_a = findPhone(a);
            Exchange* base_b = findPhone(b);

            if (base_a == NULL || base_b == NULL){
                return NULL;
            }

            Exchange* router = lowestRouter(base_a, base_b);

            ExchangeList* route_to_b = new ExchangeList(); //route from router to exchange b
            ExchangeList* route_to_a = new ExchangeList(); //route from router to exchange a

            while(base_b != router){
                route_to_b->insertFront(base_b);
                base_b = base_b->parent();
            }
            
            //route_to_b =   .........parent(parent(base_b)) ,parent(base_b) ,base_b

            while(base_a != router){
                route_to_a->insertFront(base_a);
                base_a = base_a->parent();
            }

            //route_to_a =   .........parent(parent(base_a)) ,parent(base_a) ,base_a

            route_to_b->insertFront(router);

            //route_to_b =   router, ........., parent(parent(base_b)) ,parent(base_b) ,base_b

            while(route_to_a->getSize() > 0){
                route_to_b->insertFront(route_to_a->deleteFront()->e);
            }

            //route_to_b =   base_a, parent(base_a),.....router, ........parent(base_b) ,base_b

            return route_to_b;

        }

        void printList(ExchangeList* route){

            if (route == NULL) return;

            Exchange* temp = NULL;

            ExchangeListNode* itr = route->head;
            
            if (itr==NULL) return;

            while(itr->next != NULL){
                temp = itr->e;
                cout<<temp->ex_id<<", ";
                itr = itr->next;
            }
            temp = itr->e;
            cout<<temp->ex_id<<"\n";
        }

        void performAction(string& action){
            //every action string is read out from actions file (i.e. test file) and sent to this function
            string s1= "addExchange";
		    string s2= "switchOnMobile";
		    string s3= "switchOffMobile";
		    string s4= "queryNthChild";
		    string s5= "queryMobilePhoneSet";
            string s6= "findPhone";
            string s7= "lowestRouter";
            string s8= "findCallPath";
            string s9= "movePhone";

            if (action.substr(0, s1.size()) == s1){

                int a = getFirst(action, s1);
                int b = getSecond(action, s1);

                //add b to exchange list of a

                if (ex_map.find(a) == ex_map.end()){

                    cout<<"Exchange a does not exist\n";
                    return;
                }
                if (ex_map.find(b) != ex_map.end()){

                    cout<<"Exchange with id = "<<b<<" already exist\n";
                    return;
                }

                Exchange* newEx = new Exchange(b);
                ex_map[b] = newEx;
                ex_map[a]->addExchange(ex_map[b]);

                return;
            }
            if (action.substr(0, s2.size()) == s2){

                int a = getFirst(action, s2);
                int b = getSecond(action, s2);
            
                //switch on mobilephone a to exchange b

                if (ex_map.find(b) == ex_map.end()){
                    cout<<"No Exchange with id = "<<b<<" exists\n";
                    return;
                }
                if(mp_map.find(a) == mp_map.end()){
                    mp_map[a] = new MobilePhone(a);
                }

                switchOn(mp_map[a], ex_map[b]);

                return;
            }
            if (action.substr(0, s3.size()) == s3){

                int a = getFirst(action, s3);

                //switch off mobilephone a
                if(mp_map.find(a) == mp_map.end()){
                    cout<<"Mobile phone "<<a<<"does not exist\n";
                    return;
                }
                switchOff(mp_map[a]);

                return;
            }
            if (action.substr(0, s4.size()) == s4){
                
                int a = getFirst(action, s4);
                int b = getSecond(action, s4);

                cout<<action<<": ";
                //print id of bth child of Exchange a
                if (ex_map.find(a) == ex_map.end()){
                    cout<<"No Exchange with id = "<<a<<" exists\n";
                    return;
                }
                
                cout<<(ex_map[a]->child(b))->ex_id<<"\n";

                return;
            }
            if (action.substr(0, s5.size()) == s5){
                
                int a = getFirst(action, s5);
                
                cout<<action<<": ";
                //print all MobilePhones with exchange a
                if(ex_map.find(a) == ex_map.end()){
                    cout<<"Exchange "<<a<<"does not exist\n";
                    return;
                }
                
                ex_map[a]->printMobiles();

                return;
            }
            if (action.substr(0, s6.size()) == s6){

                int a = getFirst(action, s6);

                cout<<action<<": ";    
                //find the base station of MobilePhone a

                if (mp_map.find(a) == mp_map.end()){
                    cout<<"No MobilePhone "<<a<<" found\n";
                    return;
                }

                Exchange* e = findPhone(mp_map[a]);

                if (e==NULL) return;
                cout<<e->ex_id<<"\n";

                return;
            }
            if (action.substr(0, s7.size()) == s7){

                int a = getFirst(action, s7);
                int b = getSecond(action, s7);
                
                cout<<action<<": "; 
                //Find the lowest router (common parent) of exchange a and exchange b

                if (ex_map.find(a) == ex_map.end()){
                    cout<<"Exchange "<<a<<" does not exist!\n";
                    return;
                }
                if (ex_map.find(b) == ex_map.end()){
                    cout<<"Exchange "<<b<<" does not exist!\n";
                    return;
                }

                Exchange* e = lowestRouter(ex_map[a], ex_map[b]);

                cout<<e->ex_id<<"\n";

                return;
            }
            if (action.substr(0, s8.size()) == s8){
                
                int a = getFirst(action, s8);
                int b = getSecond(action, s8);

                cout<<action<<": "; 
                //find routing path from MobilePhone a to MobilePhone b

                if (mp_map.find(a) == mp_map.end()){
                    cout<<"MobilePhone "<<a<<" does not exist!\n";
                    return;
                }
                if (mp_map.find(b) == mp_map.end()){
                    cout<<"MobilePhone "<<b<<" does not exist!\n";
                    return;
                }

                ExchangeList* route = routeCall(mp_map[a], mp_map[b]);

                if (route == NULL) return;
                
                printList(route);
                return;

            }
            if (action.substr(0, s9.size()) == s9){

                int a = getFirst(action, s9);
                int b = getSecond(action, s9);

                //Move MobilePhone a to level 0 exchange b

                if (mp_map.find(a) == mp_map.end()){
                    cout<<"MobilePhone "<<a<<" does not exist!\n";
                    return;
                }
                if (ex_map.find(b) == ex_map.end()){
                    cout<<"Exchange "<<b<<" does not exist!\n";
                    return;
                }

                movePhone(mp_map[a], ex_map[b]);

                return;

            }

        }


        int getFirst(string& action, string& s){

            //Query: "findCallPath a b"
            //a is first number

            string sa = "";

            for (int i=s.size()+1; i<action.size(); i++){
                if (action[i]==' ') break;
                sa.push_back(action[i]);
            }

            return stoi(sa); 
        }

        int getSecond(string& action, string& s){

            //Query: "findCallPath a b"
            //b is second number

            string sb = "";

            int space = 0;

            for (int i=s.size()+1; i<action.size(); i++){

                if (action[i]==' ') {
                    space = 1;
                    continue;
                }
                if (space == 0) continue;
                sb.push_back(action[i]);
            }

            return stoi(sb); 
        }






};