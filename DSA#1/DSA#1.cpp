/*DSA Programming Assignment #1*/
/*Grade: 95*/
/* This program utilizes singly linked list structure to implement stacks and queues. It reads in a text input and outputs the results from parsing and executing the commands in the text input. */

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <list>

using namespace std;

/*absract base class called SimpleList*/
/* provides functionality of singly-linked list*/
template <class T>
class SimpleList{
private:
    struct Node{     /* nested class containing node for data and to the next node*/
        T data;
        Node *next;
    };
    /*maintain pointers*/
    Node *head, *last, *tail;
protected:
    void front_insert(T x){          /*inserts a node after the head*/
        Node *first = new Node();
        first->data = x;
        first->next = head->next; /*creates a link to whatever is currently after head*/
        head->next = first; /*breaks link with whatever is currently after head and a link*/
     }                                          /*to this new Node is replaced*/

    void end_insert(T x){
        Node *lastNode = new Node();
        lastNode->data = x;
        lastNode->next = tail;

        last->next = lastNode;
        last = lastNode;
    }

    
    T front_remove(){               /*removes the node after the head, for popping*/
        Node *first = head->next;
        T val = first->data;
        head->next = head->next->next;
        delete first;
        if(head->next == tail){
            last = head;
        }
        return val;
    }

public:
    virtual void push(T x) = 0;  /* functions to be used in stack and queue classes*/
    virtual T pop() = 0;
    string name;

    SimpleList(string l){        /* constructor for simple list*/
        name = l;
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->next = NULL;
        last = head;
    }
    /*Checks to see if the SimpleList is empty, if yes, returns true*/
    bool isEmpty(){
        return (head->next == tail);
    }
};

/*Implementing stack using SimpleList*/
template <class T>
class Stack:public SimpleList<T>{
public:
    void push(T x){                 /*using one popping method (from the front) pushing */
        this->front_insert(x);          /* at the front allows LIFO ADT of stacks*/
    }
    T pop(){
        return this-> front_remove();     /* popping (removing and returning) value from*/
    }                                           /*front of the list*/
    Stack(string x);
};

/*Stack constructor*/
template <class T>
Stack<T>::Stack(string x):SimpleList<T>(x) {}


/*Implementing Queues using SimpleList*/
template <class T>
class Queue: public SimpleList<T>{
public:
    void push(T x){                 /*using one popping method (from the front) pushing */
        this->end_insert(x);        /* the end allows FIFO ADT of queues*/
    }
    /*Pop from the front*/
    T pop(){
        return this->front_remove();      /* popping (removing and returning) value from*/
    }                                          /*front of the list*/
    Queue(string x);
};

/*Queue constructor*/
template <class T>
Queue<T>::Queue(string x):SimpleList<T>(x){}

/*search for stack/queue within the list of stacks and queues*/
/* linearly checks through the list to find if there is a list with the same name*/
template <class T>
SimpleList<T> *search_list(list<SimpleList<T> *> l, string s) {
    for (typename list<SimpleList<T> *>::const_iterator it = l.begin(), end = l.end(); it != end; it++){
        if ((*it) -> name.compare(s) == 0){   /*if there is a list with the listname*/
            return *it;
            cout << *it;
        }
    }
    return 0;                                          /*no list within*/
}

template <class T>
void createStack (string name, string type, list<SimpleList<T> *> addlist, ofstream mystream){
    SimpleList<T> *List = search(addlist, name); /* search through the list with the name*/
    if (List != 0){                               /* if there is a stack/queue with same name*/
        mystream << "ERROR: This name already exists!" << endl;
    }
    else{
        SimpleList<T> *pSL = new Stack<T>(name);
        addlist.push_front(pSL);           /* adds listname to list of stacks and queues*/
    }

};

/*Processes input text file of commands, parses and executes the commands, and outputs are shown in an output text file named by the user.*/
int main(int argc, const char * argv[]) {
    list<SimpleList<int> *> listSLi;           /* all integer stacks and queues*/
    list<SimpleList<double> *> listSLd;        /* all double stacks and queues*/
    list<SimpleList<string> *> listSLs;        /* all string stacks and queues*/

    cout << "Enter name of input file:\n";
    string readfile;
    cin >> readfile;
    cout << "Enter name of output file:\n";
    string writefile;
    cin >> writefile;

    string line;
    ifstream input(readfile.c_str());
    if (input.is_open())
    {
        ofstream output(writefile.c_str());
        while (getline (input,line))
        {   /* read text input line by line*/
            string space (" ");   /*whitespace to differentiate between elements*/
            size_t index1 = line.find(space);
            string action = line.substr(0, index1);

            size_t index2 = line.find(space,index1+1);
            size_t length = index2 - index1;
            string datatype = line.substr(index1+1,1);   //i,d, or s
            string listname = line.substr(index1+1,length-1);
            string thirdWord = "";
            if (action != "pop"){
                size_t end = line.find("\n");
                thirdWord = line.substr(index2+1, end);
            }

            output << "PROCESSING COMMAND: " << line << endl;
/* parses and executes text input commands line by line and prints output to output file*/
            if (action == "create"){
/*searches for stacks or queues with specified listname for each data type and if it does not exist program creates new stacks */
                    if (datatype == "i"){ /*integer type*/
                        SimpleList<int> *List = search_list(listSLi,listname);
                        if (List != 0){
                            output << "ERROR: This name already exists!" << endl;
                        }
                        else{
                             if (thirdWord == "stack"){ /* create new int stack*/
                                 SimpleList<int> *pSLi = new Stack<int>(listname);
                                 listSLi.push_front(pSLi);
                             }
                             else if (thirdWord == "queue"){ /* create new int queue*/
                                 SimpleList<int> *pSLi = new Queue<int>(listname);
                                 listSLi.push_front(pSLi);
                             }
                        }
                    }
                    if (datatype == "d"){ /* double type*/
                        SimpleList<double> *List = search_list(listSLd,listname);
                        if (List != 0){
                            output << "ERROR: This name already exists!" << endl;
                        }
                        else{
                            if (thirdWord == "stack"){ /* create new double stack*/
                                SimpleList<double> *pSLi = new Stack<double>(listname);
                                listSLd.push_front(pSLi);
                            }
                            else if (thirdWord == "queue"){ /* create new double queue*/
                                 SimpleList<double> *pSLi = new Queue<double>(listname);
                                 listSLd.push_front(pSLi);
                            }
                        }
                    }
                    if (datatype == "s"){ /*string type*/
                        SimpleList<string> *List = search_list(listSLs,listname);
                        if (List != 0){
                            output << "ERROR: This name already exists!" << endl;
                        }
                        else{
                            if (thirdWord == "stack"){ /* create new string stack*/
                                SimpleList<string> *pSLi = new Stack<string>(listname);
                                listSLs.push_front(pSLi);
                            }
                            else if (thirdWord == "queue"){ /* create new string queue */
                                SimpleList<string> *pSLi = new Queue<string>(listname);
                                listSLs.push_front(pSLi);
                            }
                        }
                    }
                }
            else if (action == "push"){
                if (datatype == "i"){
                    SimpleList<int> *List = search_list(listSLi,listname);
                    if (List == 0){
                        output << "ERROR: This name does not exist!" << endl;
                    }
                    else {
                        List->push(atoi(thirdWord.c_str()));/*converts string to integer and pushes the value*/
                    }
                }
                else if (datatype == "d"){
                    SimpleList<double> *List = search_list(listSLd,listname);
                    if (List == 0){
                        output << "ERROR: This name does not exist!" << endl;
                    }
                    else {
                        List->push(atof(thirdWord.c_str()));/* converts string to double and pushes the value*/
                    }

                }
                else if (datatype == "s"){
                    SimpleList<string> *List = search_list(listSLs,listname);
                    if (List == 0){
                        output << "ERROR: This name does not exist!" << endl;
                    }
                    else {
                        List->push(thirdWord);
                    }
                }
            }
            else if (action == "pop"){
                if (datatype == "i"){
                    SimpleList<int> *List = search_list(listSLi,listname);
                    if (List == 0){
                        output << "ERROR: This name does not exist!" << endl;
                    }
                    else {
                        if (List->isEmpty()){
                            output << "ERROR: This list is empty!" << endl;
                        }
                        else{
                            output << "Value popped: " << List->pop() << endl;
                        }
                    }

                }
                else if (datatype == "d"){
                    SimpleList<double> *List = search_list(listSLd,listname);
                    if (List == 0){
                        output << "ERROR: This name does not exist!" << endl;
                    }
                    else {
                        if (List->isEmpty()){
                            output << "ERROR: This list is empty!" << endl;
                        }
                        else{
                            output << "Value popped: " << List->pop() << endl;
                        }
                    }

                }
                else if (datatype == "s"){
                    SimpleList<string> *List = search_list(listSLs,listname);
                    if (List == 0){
                        output << "ERROR: This name does not exist!" << endl;
                    }
                    else {
                        if (List->isEmpty()){
                            output << "ERROR: This list is empty!" << endl;
                        }
                        else{
                            output << "Value popped: " << List->pop() << endl;}
                        }
                }

            }
        }
        input.close();
        output.close();
    }
    else cout << "File can not be opened.";
    return 0;
}
