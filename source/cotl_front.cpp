#include "../cotl"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace cotl;

    // TODO

    // for testing

    cout << sizeof(Val) << endl;
    cout << sizeof(Atom) << endl;
    cout << sizeof(Int) << endl;
    cout << sizeof(Real) << endl;
    cout << sizeof(Func) << endl;
    cout << sizeof(Ptr) << endl;
    cout << sizeof(Str) << endl;
    cout << sizeof(Arr) << endl;
    cout << sizeof(Pair) << endl;
    cout << sizeof(std::string) << endl;
    std::string s("aaahhhh");
    cout << sizeof(s) << endl;
    cout << sizeof(std::vector<PVal>) << endl;
    // cout << sizeof(std::map<int, PVal>) << endl;
    cout << sizeof(map_t) << endl;
    // cout << sizeof(std::unordered_map<int, PVal>) << endl;
    cout << sizeof(std::pair<PVal, PVal>) << endl;

    cout << _arr(1001,
        123, _atom(1002, func_t(0x12345678)),
        456, _str(1004, "xxx\n\t\r啊\x01\x7F"),
        789, _pair(1005,
            _int(1006, 123, autotype),
            _real(1007, 45.6)
        ),
        101112, _ptr(1009, _func(1008, autotype))
    ) << endl;

    for (int i = 0; i < 100000; ++i) {
        // memory leak test
        /*_arr(1001,
            123, _atom(1002, func_t(0x12345678)),
            456, _str(1004, "xxx\n\t\r啊\x01\x7F"),
            789, _pair(1005,
                _int(1006, 123, autotype),
                _real(1007, 45.6)
            ),
            101112, _ptr(1009, _func(1008, autotype))
        );*/

        Val *a1 = _atom(1002, autotype);
        Val *a2 = _int(1002, 1, autotype, a1);
        cout<<(a2 == a1)<<endl;
        cout<<a1<<endl;
    }

    // end

    return 0;
}
