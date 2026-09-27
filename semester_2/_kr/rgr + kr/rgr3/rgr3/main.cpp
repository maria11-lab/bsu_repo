#include <iostream>
#include "KSet.h"
#include "KSetIter.h"

using namespace std;

bool equal(const KSet& s1, const KSet& s2) {
    if (s1.Size() != s2.Size()) return false;

    KSetIter it(s1);
    for (it.first(); it(); ++it) {
        if (!s2.Contains(*it)) return false;
    }
    return true;
}

int main() {
    KSet s1, s2;

    s1 >> 10 >> 20 >> 30 >> 40;
    s2 >> 30 >> 40 >> 50 >> 60;

    cout << "Set 1: " << s1 << endl;
    cout << "Set 2: " << s2 << endl;

    cout << "\n--- Iterator: Methods (GoF) ---" << endl;
    KSetIter* itPtr = s1.createIterator();
    cout << "s1 elements: ";
    for (itPtr->first(); !itPtr->isDone(); itPtr->next()) {
        cout << itPtr->currentItem() << " ";
    }
    delete itPtr;
    cout << endl;

    cout << "\n--- Iterator: Operators ---" << endl;
    KSetIter itOps(s2);
    cout << "s2 elements: ";
    for (itOps.first(); itOps(); ++itOps) {
        cout << *itOps << " ";
    }
    cout << endl;

    cout << "\n--- Set Operations ---" << endl;
    cout << "Union (s1 | s2): " << (s1 | s2) << endl;
    cout << "Intersection (s1 & s2): " << (s1 & s2) << endl;
    cout << "Difference (s1 / s2): " << (s1 / s2) << endl;

    KSet s3 = s1;
    cout << "\n--- External Function ---" << endl;
    cout << "equal(s1, s3): " << (equal(s1, s3) ? "True" : "False") << endl;
    cout << "equal(s1, s2): " << (equal(s1, s2) ? "True" : "False") << endl;

    return 0;
}