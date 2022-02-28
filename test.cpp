#include <algorithm>
#include <vector>
#include <cstdio>
#include <string>
#include <iostream>

int main(){
    std::vector<int> a;
    std::vector<std::vector<int> > b;
    for(int i = 0 ; i < 10; i ++ ){
        for(int j = 0; j < 11; j ++){
            a.push_back(i + j);
        }
        b.push_back(a);
        a.clear();
    }
    for(int i = 0 ; i < b.size(); i ++ ){
        for(int j = 0 ; j < b[i].size(); j ++ ){
            printf("%d " , b[i][j]);
        }
        printf("\n");
    }
    std::string z = "Helll word!";
    std::cout << z << std::endl;
    
}