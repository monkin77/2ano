#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    /*
    list<int> l1 = {1,2,3};
    l1.insert(l1.end(), 4);
    for(auto it = l1.begin(); it != l1.end(); it++)
        cout << *it << endl;
    auto it = find(l1.begin(), l1.end(), 3);
    cout << *it << endl;
    */
    /*
    stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.pop();
    cout << s1.top() << endl;

    queue<int> s2;
    s2.push(1);
    s2.push(2);
    s2.push(3);
    cout << "front: " << s2.front() << " back: " << s2.back() << endl;
    s2.pop();                   // pops the first element in (1)
    cout << "front: " << s2.front() << " back: " << s2.back() << endl;
    */
    /*
    vector<int> v1 = {4,3,2,1,6,7,8};
    sort(v1.begin(), v1.end(), [](int i1, int i2){
        return i1 < i2;
    });
    for(auto elem : v1)
        cout << elem << " ";
    cout << endl;
    */
    int max = 10;
    int i;
    for(i = 0; i < max; i++){
        max--;
        cout << i << endl;
    }

    return 0;
}
