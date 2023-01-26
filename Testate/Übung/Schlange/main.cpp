//
// Created by Julius on 10.01.2023.
//
#include <iostream>
class Schlange{

private:
    int* Array;
    size_t length;
    size_t contentLength;
    int head;
    int tail;

    int CalcPosition(int pos){
        if(pos < length){
            pos++;
        }else{
            pos = 0;
        }
        return pos;
    }


public:

    size_t getLength(){return contentLength;}
    size_t getCapacity(){return length;}

    Schlange(size_t length): contentLength(0),length(length),head(0), tail(0){
        Array = new int[length];
    }
    ~Schlange(){
        delete[] Array;
    }
    void append(int item){
        if(head-1 == tail || (head == 0 && tail == length-1) || (tail == length && head == 1)){
            //creating longer array
            int* newArray = new int[length*2];
            for(int i = 0; i < tail; ++i ){
                newArray[i] = Array[i+head];
            }
            length = length*2;
            delete[] Array;
            Array = newArray;

            //resetting head and tail
            head = 0;
            tail = contentLength+1;
            //inserting new item into array
            Array[tail] = item;
            tail = CalcPosition(tail);
            contentLength++;

        }else{
            Array[tail] = item;
            tail = CalcPosition(tail);
            contentLength++;
        }
    }

    int pop(){
        head = CalcPosition(head);
        int outPutValue = Array[head-1];
        Array[head-1] = 0;
        contentLength--;
        return outPutValue;
    }

    int& operator[](size_t index){
        if(head+index > tail){
            std::runtime_error("index out of bounds");
        }
        return Array[head+index];
    }

    void output(){
        std::cout << "|";
        for(int i = 0; i < length; ++i){
            if(Array[i] == 0){
                std::cout << "  |";
            }else{
                std::cout << " " << Array[i] << " |" ;
            }
        }
        std::cout <<  " " << head << " " << tail <<std::endl;
    }

};



int main(){
    Schlange Queue(2);
    Queue.append(3);
    Queue.output();
    Queue.append(4);
    Queue.pop();
    Queue.append(5);
    Queue.append(6);
    Queue.output();
    Queue.pop();
    Queue.append(7);
    Queue.append(8);
    Queue.append(9);
    Queue.append(10);
    Queue.append(11);
    Queue.output();
    Queue.pop();
    Queue.append(12);
    Queue.output();

    std::cout << Queue[Queue.getLength()] << std::endl;

};
