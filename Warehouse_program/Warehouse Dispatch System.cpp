

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <list>
#include <queue>
using namespace std;

struct Order{
    int timeStep;
    char orderType;
    int processTime;
};

class OrderClass{
    Order obj1;
public:
    Order createOrder(char type, int time){
        Order obj1;
        obj1.timeStep = time;
        obj1.orderType = type;
        obj1.processTime = generateProcessTime();
        return obj1;
    }
    
    char setSymbol(char value){
            switch(value){
                case 'S':case 's':
                    value = 'S';
                break;
                case  'M':case 'm':
                    value= 'M';
                break;
                case 'B':case 'b':
                    value= 'B';
                break;
                default:
                    return ' ';
            }
            return value;
    }

    int generateProcessTime(){
        return (rand()% 4 + 1);
    }

};

class Stack{
    private:
        const int MAXLOAD = 5;
        stack<stack<Order>>Dispatch;
        stack<Order>TruckS;
        stack<Order>TruckM;
        stack<Order>TruckB;
        list<char>Truck1;

    
    public:
        void push(Order order){
            if(order.orderType == 'S')
                TruckS.push(order);
            if(order.orderType == 'M')
                TruckM.push(order);
            if(order.orderType == 'B')
                TruckB.push(order);
        }

        void dispatch(){
            if(TruckS.size() == 5){
                Dispatch.push(TruckS);
                Truck1.push_back('S');
            }if(TruckM.size() == 5){
                Dispatch.push(TruckM);
                Truck1.push_back('M');
            }if(TruckB.size() == 5){
                Dispatch.push(TruckB);
                Truck1.push_back('B');
            }

        }

        void loadList(){
            int count = 0;
            while(!Truck1.empty()){
                count++;
                cout<<"Truck"<<count<<"["<<Truck1.back()<<"]"<<endl;
                Truck1.pop_back();
            }
        }


};

class Queue{
    protected:
        queue<Order>package;
    public:
        void queuePopulate(Order order){
            package.push(order);
        }

        void display(){
            
            while(!package.empty()){
                cout<<package.front().timeStep<<", "<<package.front().orderType<<", "<<package.front().processTime<<endl;
                package.pop();
            }
            cout<<endl;
        }
        
};

const int SIZE = 3;

void answer(char value, int &count, OrderClass testObj1, Order orderObj, Queue queueObj, Stack stackObj){
    while(value == 'Y'){
        char type;
        count++;
        cout<<"Next Orders: ";
        for(int i = 0; i < SIZE;){
            cin>>type;
            type = testObj1.setSymbol(type);
            while(type == ' '){
                cout<<"Invalid input, please try again."<<endl;
                cout<<"Enter order S,M or B:"<<endl;
                cin>>type;
                type = testObj1.setSymbol(type);
            }
                    
            cout<<"Queue "<<type<<": ["<<type<<"("<<count<<")]"<<endl;
            queueObj.queuePopulate(testObj1.createOrder(type,count));
            stackObj.push(testObj1.createOrder(type,count));
            stackObj.dispatch();

            i++;
            if(i != SIZE){
                cout<<"Next: ";
            }
        }
        cout<<"Would you like to continue? Enter 'Y' to proceed or 'N' to quit: ";
        cin>>value;
        while((value != 'N' && value != 'n') && (value != 'y'&& value != 'Y')){
            cout<<"Invalid input, please try again."<<endl;
            cout<<"Enter 'Y' to proceed or 'N' to quit: "<<endl;
            cin>>value;
        }
        if(value == 'y' || value == 'Y')
            value = 'Y';
        else{
            value = 'N';
            cout<<"time_step type processing_time"<<endl;
            queueObj.display();
            cout<<endl;
            cout<<"Dispatched Trucks Stack:"<<endl;
            stackObj.loadList();
        }
    }
}

int main()
{
    OrderClass testObj1;
    Order orderObj;
    Queue queueObj;
    Stack stackObj;
    //queue<Order>q;
    
    int num = 0;
    char response = 'Y';
    answer(response, num, testObj1, orderObj, queueObj, stackObj);

    return 0;
}
