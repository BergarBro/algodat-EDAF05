#ifndef OPTINIONLIST_H
#define OPTINIONLIST_H

#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>

using std::cout;
using std::cin;
using std::string;
using std::vector;

class OpinionList{
    public:
    OpinionList() = default;

    OpinionList(const int n, const int vSize): index(n), pref(vSize), prefSize(vSize), pair(0), count(0){}

    int getIndex(){ return index; }

    int getSize(){return prefSize;}

    void setPref(const vector<int> list){ pref = list; }

    int getPref(const int n){ return pref.at(n-1); }

    void invertPref(){
        vector<int> temp(pref.size(),0);
        int n = 1;
        for(int opt : pref){
            temp.at(opt-1) = n;
            n++;
        }
        pref = temp;
    }

    void setPair(int o){ pair = o; }

    int getPair(){ return pair; }
    
    void addCount(){ count++; }

    int getCount(){return count;}

    int getNextPref(){ return pref.at(count); }

    vector<int> getPrefVector(){return pref;}

    bool operator==(OpinionList o){
        return index == o.getIndex();
    }

    bool operator==(OpinionList* o){
        return index == o->getIndex();
    }

    bool operator<(OpinionList o){
        return index < o.getIndex();
    }


    private:
    int index;
    vector<int> pref;
    int prefSize;
    int count;
    int pair;
};

#endif