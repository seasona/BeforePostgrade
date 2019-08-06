#include <iostream>
using namespace std;

class CppObj {
public:
    CppObj() { cout << "ctor\n"; }
    CppObj(const CppObj& c) { cout << "copy ctor\n"; }
    CppObj& operator=(const CppObj& chs) {
        cout << "operator=\n";
        return *this;
    }
    ~CppObj() { cout << "dtor\n"; }
};

CppObj return_test() {
    CppObj b;
    cout << "before return\n";
    return b;
}

int main() {
    CppObj n;
    n = return_test();
    return 0;
}