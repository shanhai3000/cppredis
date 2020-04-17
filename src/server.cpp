//
// Created by shanhai on 2020/4/13.
//

#include <iostream>
#include "../include/server.h"
int main(){
    using namespace std;
    int i = 526;
    while(i){
        cout << i%2<<endl;
        i>>=1;
    }
    //0
    //1
    //1
    //1
    //0
    //0
    //0
    //0
    //0
    //1
    // 0000 0010   0000 1110
    return 0;
}