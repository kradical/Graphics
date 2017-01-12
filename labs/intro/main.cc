#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "intro.h"
#include "concreteThing.h"
#include "listNode.h"
#include "vector3.h"

int main() {
    Intro myIntro(0.0);
    ConcreteThing myConcrete;
    LinkedListNode<int> myList;
    myList.value = 2;

    cout << myIntro.getA() << endl;
    cout << myConcrete.af() << endl;
    cout << myList.value << endl;

    string s1 = "TOP";
    string s2 = "KEK";

    cout << s1 + s2 << endl;

    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    cout << "[" << endl;
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << *it << endl;
    }
    cout << ']' << endl;

    map<string, int> m;
    m.insert(pair<string, int>("one", 1));
    m.insert(pair<string, int>("two", 2));
    m.insert(pair<string, int>("three", 3));
    
    cout << "{" << endl;
    for (map<string, int>::iterator it = m.begin(); it != m.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }
    cout << "}" << endl;

    Vector3 vec1;
    vec1.x = 1;
    vec1.y = 1;
    vec1.z = 1;

    Vector3 vec2;
    vec2.x = 1;
    vec2.y = 1;
    vec2.z = 1;

    Vector3 vec3 = vec1 + vec2;
    vec3 += vec3;

    cout << "vec: " << vec3.x << " " << vec3.y << " " << vec3.z << endl;

    return 0;
}
