#include"ExchangeListNode.cpp"
class Exchange;

class ExchangeList{
    //implements linked list of exchanges

    public:
        ExchangeListNode* head;
        int size;

        ExchangeList(){
            head = NULL;
            size = 0;
        }

        void insertFront(Exchange *e){
            if (head==NULL){
                head = new ExchangeListNode(e);
                size = 1;
                return;
            }

            ExchangeListNode* temp = new ExchangeListNode(e);

            temp->next = head;
            head = temp;
            size++;
        }

        ExchangeListNode* deleteFront(){
            if (head==NULL){
                std::cout<<"Exchange List Already Empty\n";
                return NULL;
            }
            ExchangeListNode* temp = head;
            head = head->next;
            size--;
            return temp;
        }

        bool isMember(Exchange* e){
            ExchangeListNode* itr = head;
            while(itr!=NULL){
                if (itr->e == e) return true;
                itr = itr->next;
            }
            return false;
        }

        int getSize(){
            return size;
        }

        Exchange* getChild(int i){
            //i is 0 indexed
            if (i < 0 || i>=size){
                cout<<i<<"th child does not exist\n";
                return NULL;
            } 

            ExchangeListNode* itr = head;

            int n = size - i;

            //nth child from the starting of the list is needed

            if (n==0) cout<<"Unable to get "<<i<<"th child, reached null\n";

            while(n>1){
                
                if (itr==NULL){
                    std::cout<<"Unable to get "<<i<<"th child, reached null\n";
                    return NULL;
                }

                itr = itr->next;
                n--;
            }

            return itr->e;

        }

};