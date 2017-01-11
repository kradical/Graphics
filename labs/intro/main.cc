#include <iostream>
using namespace std;
#include <string>

#include "intro.h"
#include "concreteThing.h"
#include "listNode.h"

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

    return 0;
}
