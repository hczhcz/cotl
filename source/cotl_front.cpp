#include "../cotl"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace cotl;

    // TODO

    // for testing

    cout << _arr(1001,
        123, _atom(1002, func_t(0x12345678)),
        456, _str(1004, "xxx\n\t\r啊\x01\x7F"),
        789, _pair(1005,
            _int(1006, 123, autotype),
            _real(1007, 45.6)
        ),
        101112, _ptr(1009, _func(1008, autotype))
    ) << endl;

    // end

    return 0;
}
