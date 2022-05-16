class Exchange; //Saying Exchange class exist

class MobilePhone{
    public:
        int pnum;   //phone number
        bool on_off;    //switch on or switch off
        Exchange* base;

        MobilePhone(){}

        MobilePhone(int num){
            pnum = num;
            on_off = false; //switch the mobile on
            base = NULL;
        }

        int number(){
            return pnum;
        }

        bool status(){
            return on_off;
        }

        void switchOn(){
            on_off = true;
        }

        void switchOff(){
            on_off = false;
        }

        bool operator==(const MobilePhone& m2) const{
            return pnum == m2.pnum && !(on_off^m2.on_off);
        }

        void set_base(Exchange* e){
            base = e;
        }

        Exchange* location(){

            if (on_off) return base;

            cout<<"This MobilePhone is switched off\n";

            return NULL;
  
        }

};