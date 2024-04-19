#include<iostream>
#include<sstream>
#include<vector>

using std::cout;
using std::cin;
using std::string;
using std::vector;

int main(){
    int N;
    cin >> N;
    
    vector<OpinionList> companies[N];
    vector<OpinionList> students[N];

    for (int i = 0; i < N * 2; i++){
        int index;
        cin >> index;
        for (int j = 0; j < N; j++){
            
        }
    }
}

class OpinionList{
    public:
    OpinionList(const int n, const int vSize): index(n), pref(vSize), pair(nullptr), count(0) {}

    int getIndex(){ return index; }

    void setPref(const vector<int> list){ pref = list; }

    int getPref(const int n){ return pref[n-1]; }

    void invertPref(){
        vector<int> temp(pref.size(),0);
        int n = 1;
        for(int opt : pref){
            temp.at(opt-1) = n++;
        }
    }

    void setPair(OpinionList* o){ pair = o; }

    OpinionList getPari(){ return *pair; }
    
    void addCount(){ count++; }

    int getNextPref(){ return pref.at(count); }


    private:
    int index;
    vector<int> pref;
    int count;
    OpinionList* pair;
};