#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>

#include"opinionList.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

void printVector(vector<int> v){
    int size = v.size();
    for(int i = 0; i < size; i++){
        cout << v.at(i) << " ";
    }
    cout << std::endl;
}

int main(){
    int N;
    cin >> N;
    
    vector<OpinionList> companies;
    vector<OpinionList> students;

    for (int i = 0; i < (N*2); i++){
        int index;
        cin >> index;
        vector<int> list;
        for (int j = 0; j < N; j++){
            int input;
            cin >> input;
            list.push_back(input);
        }
        OpinionList op(index,N);
        op.setPref(list);

        //printVector(list);

        if(std::find(companies.begin(),companies.end(),op) == companies.end()){
            op.invertPref();
            cout << companies.size() << " comp size pre" << std::endl;
            companies.push_back(op);
            cout << companies.size() << " comp size past" << std::endl;
        }else{
            cout << students.size() << " stud size pre" << std::endl;
            students.push_back(op);
            cout << students.size() << " stud size past" << std::endl;
        }
    }
    cout << "hejsan";
    //std::sort(companies.begin(),companies.end());

    while(students.size() != 0){
        OpinionList stud = *students.erase(students.begin());
        
        OpinionList comp = companies.at(stud.getNextPref() - 1);
        stud.addCount();

        if(comp.getPair() == nullptr){
            comp.setPair(&stud);
        }else{
            OpinionList otherStud = *comp.getPair();
            if(comp.getPref(stud.getIndex()) < comp.getPref(otherStud.getIndex())){
                comp.setPair(&stud);
                students.push_back(otherStud);
            }else{
                students.push_back(stud);
            }
        }
    }

    for(OpinionList o : companies){
        cout << (o.getPair())->getIndex() << std::endl;
    }

    // for(OpinionList o : *companies){
    //     cout << o.getIndex() << std::endl;
    //     for(int i = 1; i <= o.getSize(); i++){
    //         cout << o.getPref(i) << " ";
    //     }
    //     cout << std::endl;
    // }
    // cout << std::endl;
    // for(OpinionList o : *students){
    //     cout << o.getIndex() << std::endl;
    //     for(int i = 1; i <= o.getSize(); i++){
    //         cout << o.getPref(i) << " ";
    //     }
    //     cout << std::endl;
    // }
}