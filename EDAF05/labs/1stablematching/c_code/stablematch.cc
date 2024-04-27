#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<chrono>

#include"opinionList.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::endl;

// void printVector(vector<int> v){
//     int size = v.size();
//     for(int i = 0; i < size; i++){
//         cout << v.at(i) << " ";
//     }
//     cout << std::endl;
// }

int main(){
    int N;
    cin >> N;
    
    vector<OpinionList> companies(N);
    vector<OpinionList> students(N);
    vector<int> studIndex;
    vector<int> studCompPair(N);
    vector<int> list(N);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < (N*2); i++){
        int index;
        cin >> index;
        list.clear();
        list.reserve(N);
        for (int j = 0; j < N; j++){
            int input;
            cin >> input;
            list.push_back(input);
        }
        OpinionList op(index,N);
        op.setPref(list);

        //printVector(list);

        if(companies[index - 1].getIndex() == 0){
            op.invertPref();
            //cout << companies.size() << " comp size pre" << std::endl;
            companies[index - 1] = std::move(op);
            //cout << companies.size() << " comp size past" << std::endl;
        }else{
            //cout << students.size() << " stud size pre" << std::endl;
            students[index - 1] = std::move(op);
            studIndex.push_back(index);
            //cout << students.size() << " stud size past" << std::endl;
            //printVector(students.at(0).getPrefVector());
        }
    }
    //cout << students.size() << " stud size after loop" << std::endl;
    //cout << students.at(0).getIndex();

    //cout << "hejsan" << std::endl;
    //std::sort(companies.begin(),companies.end());

    auto endOfInput = std::chrono::high_resolution_clock::now();

    while(studIndex.size() != 0){
        //cout << "hejsan1" << std::endl;
        OpinionList& stud = students.at(studIndex.back() - 1);
        studIndex.pop_back();
        //cout << stud.getNextPref() << " " << stud.getCount() << std::endl;
        OpinionList& comp = companies.at(stud.getNextPref() - 1);
        //cout << "hejsan3" << std::endl;
        stud.addCount();

        if(comp.getPair() == 0){
            comp.setPair(stud.getIndex());
            studCompPair.at(comp.getIndex() - 1) = stud.getIndex();
        }else{
            OpinionList& otherStud = students.at(comp.getPair() - 1);

            if(comp.getPref(stud.getIndex()) < comp.getPref(otherStud.getIndex())){
                comp.setPair(stud.getIndex());
                studCompPair.at(comp.getIndex() - 1) = stud.getIndex();
                studIndex.push_back(otherStud.getIndex());
                //cout << "hej1" << std::endl;
            }else{
                studIndex.push_back(stud.getIndex());
                //cout << "hej2" << std::endl;
            }
        }
    }

    auto endOfAlgorithm = std::chrono::high_resolution_clock::now();

    // for(OpinionList o : companies){
    //     cout << (o.getPair())->getIndex() << std::endl;
    //     //cout << o.getIndex() << std::endl;
    // }

    auto timeOfInput = std::chrono::duration_cast<std::chrono::milliseconds>(endOfInput - start);
    auto timeOfAlgoithm = std::chrono::duration_cast<std::chrono::milliseconds>(endOfAlgorithm - endOfInput);

    //cout << "Input time: " << timeOfInput.count() << " ms" << endl;
    

    for(int o : studCompPair){
        cout << o << std::endl;
        //cout << o.getIndex() << std::endl;
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