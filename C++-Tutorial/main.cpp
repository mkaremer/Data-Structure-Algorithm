#include<iostream>
#include <string>


using namespace std;

int main(){
    string str1 = ("hello world with ()");
    // cout << str1.size() << endl;
    // cout << str1.length() << endl;

    //C iterator
    // for(int i = 0; i < str1.size(); i++){
    //     cout << str1[i] << endl;;
    // }

    //C++ iterator
    // for(string::iterator it=str1.begin(); it != str1.end(); ++it){
    //     cout << *it << endl;
    // }
    // cout << '\n';

    // for(auto it=str1.begin(); it != str1.end(); ++it){
    //     cout << *it << endl;
    // }
    // cout << '\n';

    // for(string::reverse_iterator it=str1.rbegin(); it != str1.rend(); ++it){
    //     cout << *it << endl;
    // }
    // cout << '\n';

    cout << "max size of str " + str1.max_size()<< endl;
    cout << str1.at(0)<< endl;
    cout << str1.back() << endl;
    cout << str1.front() << endl;


    return 0;
}