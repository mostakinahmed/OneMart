#include<bits/stdc++.h>
using namespace std;
int main(){
int q;
cin>>q;
queue<string>qu;
while(q--){
    int cmd;
    cin>>cmd;
if(cmd==0){
    string name;
    cin>>name;
    qu.push(name);
}
else if(cmd==1){
    if(qu.empty()){cout<<"Invalid"<<endl;} 
    else {cout << qu.front()<<endl;qu.pop();}
}

}




    return 0;
}