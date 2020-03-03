#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;
int main(){
    vector<int> hash(26,0);
    string str;
    cin>>str;
    set<int> onecharacter;
    int n=str.length();
    for(int i=0;i<n;i++){
        hash[str[i]-'a']++;
    }
    for(int i=0;i<26;i++){
        if(hash[i]==1) onecharacter.insert(i);
    }
    if(onecharacter.size()==0) cout<<"#"<<endl;
    for(int i=0;i<n;i++){
        if(onecharacter.find(str[i]-'a') != onecharacter.end()) {
            cout<<str[i]<<endl;break;
        }
    }
    return 0;
}
