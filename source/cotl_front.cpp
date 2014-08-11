#include "../cotl"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace cotl;

    // TODO

    // for testing

    cout << _arr(1001, 3,
        123, _atom(1002),
        456, _str(1004, "xxx\n\t\r啊\x01\x7F"),
        789, _pair(1005,
            _int(1006, 123),
            _real(1007, 45.6)
        )
    ) << endl;

    // end

    return 0;
}
