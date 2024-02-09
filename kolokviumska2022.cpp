#include <iostream>
#include <cstring>
using namespace std;
class InvalidOperation{
private:
    char *msg;
public:
    InvalidOperation(char *msg){
        this->msg= new char[strlen(msg)+1];
        strcpy(this->msg,msg);
    }
    void showMessage(){
        cout<<msg<<endl;
    }
};
class Event{
private:
    char *ime;
    int gosti;
    int month;
    bool aktiven;
    static int CAPACITY;
public:
    Event(){
        ime = new char[0];
        aktiven=true;
    }
    int getMonth(){
        return month;
    }
    Event(const char *ime, int gosti,int month, bool aktiven){
        this->ime=new char [strlen(ime)+1];
        strcpy(this->ime,ime);
        this->gosti=gosti;
        this->month=month;
        this->aktiven=aktiven;
    }
    Event(char *ime, int gosti, int month){
        this->ime = new char [strlen(ime)+1];
        strcpy(this->ime,ime);
        this->gosti=gosti;
        this->month=month;
    }
    int getGosti(){
        return gosti;
    }
    char *getIme(){
        return ime;
    }
    Event(const Event&e){
        this->ime=new char [strlen(e.ime)+1];
        strcpy(this->ime,e.ime);
        this->gosti=e.gosti;
        this->month=e.month;
        this->aktiven=e.aktiven;
    }
    Event&operator=(const Event&e){
        if(this!=&e){
            this->ime=new char [strlen(e.ime)+1];
            strcpy(this->ime,e.ime);
            this->gosti=e.gosti;
            this->month=e.month;
            this->aktiven=e.aktiven;
        }
        return *this;
    }
    Event operator+(Event &nov){
        if(this->month!=nov.getMonth()) throw InvalidOperation("Can't merge events from different months.");
        int zainteresirani=gosti+nov.getGosti();
            if(zainteresirani>CAPACITY) throw InvalidOperation("Can't merge events which have more guests than the capacity.");
                char *nova = new char [strlen(this->ime)+strlen(nov.getIme())+2];
        strcpy(nova, ime);
        strcat(nova,"&");
        strcat(nova,nov.getIme());
        int vkGosti= this->gosti+nov.getGosti();
        int mesec=nov.getMonth();
        Event temp(nova,vkGosti,mesec,aktiven);
        return temp;
    }
    friend ostream &operator<<(ostream&out, const Event &ev){
        out<<ev.ime<<" "<<ev.month<<" "<<ev.gosti<<endl;
        return out;
    }
    ~Event(){
        delete[]ime;
    }
};
int Event::CAPACITY=1000;
class EventCalendar{
private:
    int year;
    Event *events;
    int n;
public:
    EventCalendar(){
        n=0;
        events = new Event[0];
    }
    EventCalendar(int year){
        this->year=year;
        n=0;
        events = new Event[0];
    }
    EventCalendar(const EventCalendar &ec){
        this->year=ec.year;
        this->n=ec.n;
        this->events= new Event[ec.n];
        for(int i=0; i<n; i++){
            this->events[i]=ec.events[i];
        }
    }
    EventCalendar& operator=(const EventCalendar &ec){
        if(this!=&ec){
            this->year=ec.year;
            this->n=ec.n;
            this->events= new Event[ec.n];
            for(int i=0; i<n; i++){
                this->events[i]=ec.events[i];
            }
        }
        return *this;
    }
    friend ostream &operator<<(ostream&out, EventCalendar&ec){
        out<<ec.year<<endl;
        for(int i=0; i<ec.n; i++){
            out<<ec.events[i];
        }
        return out;
    }
    EventCalendar&operator+=(Event &nov){
        Event *temp = new Event[n+1];
        for(int i=0; i<n; i++){
            temp[i] = events[i];
        }
        temp[n] = nov;
        delete[]events;
        events = temp;
        n++;
        return *this;
    }
};
int main() {
    int testCase;
    cin >> testCase;

    if (testCase == 0) {
        cout << "Event constructor" << endl;
        Event e1("Wedding", 25, 4);
        Event e2("Graduation", 50, 5, false);
        cout << "TEST PASSED" << endl;
    } else if (testCase == 1) {
        cout << "Event copy-constructor and operator =" << endl;
        Event e2("Wedding", 25, 4);
        Event e1 = e2;
        Event e3("Graduation", 50, 5, false);
        e3 = e2;
        cout << "TEST PASSED" << endl;
    } else if (testCase == 2) {
        cout << "Event operator <<" << endl;
        Event e1("Wedding", 25, 4);
        Event e2("Graduation", 50, 5, false);
        cout << e1;
        cout << e2;
    } else if (testCase == 3) {
        cout << "Event operator + (normal behavior)" << endl;
        Event e1("Wedding", 25, 4);
        Event e2("Graduation", 50, 4, false);
        cout<<e1<<"+"<<endl<<e2<<"-->"<<endl;
        cout << (e1 + e2);
    } else if (testCase == 4) {
        cout << "Event operator + (abnormal behavior)" << endl;
        char name[50];
        int number_guests, month;
        bool active;
        cin >> name >> number_guests >> month >> active;
        Event e1(name, number_guests, month, active);
        cin >> name >> number_guests >> month >> active;
        Event e2(name, number_guests, month, active);
        try {
            cout<<e1<<"+"<<endl<<e2<<"-->"<<endl;
            cout << (e1 + e2);
        } catch (InvalidOperation &e) {
            e.showMessage();
        }
    } else if (testCase == 5) {
        cout << "EventCalendar constructors" << endl;
        EventCalendar ec1(2020);
        EventCalendar ec2(2021);
        cout << "TEST PASSED" << endl;
    } else if (testCase == 6) {
        cout << "EventCalendar copy-constructor and operator =" << endl;
        EventCalendar ec1(2020);
        EventCalendar ec2(2021);
        EventCalendar ec3 = ec1; //copy constructor;
        ec2 = ec1; //operator =
        cout << "TEST PASSED" << endl;
    } else if (testCase == 7) {
        cout << "EventCalendar operator << (empty)" << endl;
        EventCalendar ec1(2021);
        cout << ec1;
    } else if (testCase == 8) {
        cout << "EventCalendar += and <<" << endl;
        EventCalendar ec(2021);
        int n;
        cin >> n;
        char name[50];
        int number_guests, month;
        bool active;

        for (int i = 0; i < n; i++) {
            cin >> name >> number_guests >> month >> active;
            Event e(name, number_guests, month, active);
            ec += e;
        }
        cout << ec;
    }
    return 0;
}
