#include "../cotl"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace cotl::published;

    (void) argc;
    (void) argv;

    _COTL_MEMINIT();

    // TODO

    // for testing

    cout << sizeof(cotl::Val) << endl;
    cout << sizeof(Atom) << endl;
    cout << sizeof(Int) << endl;
    cout << sizeof(Real) << endl;
    cout << sizeof(Func) << endl;
    cout << sizeof(Ptr) << endl;
    cout << sizeof(Pair) << endl;
    cout << sizeof(Str) << endl;
    cout << sizeof(Arr) << endl;
    cout << sizeof(std::string) << endl;
    std::string s("aaahhhh");
    cout << sizeof(s) << endl;
    cout << sizeof(std::vector<PVal>) << endl;
    // cout << sizeof(std::map<int, PVal>) << endl;
    cout << sizeof(map_t) << endl;
    // cout << sizeof(std::unordered_map<int, PVal>) << endl;
    cout << sizeof(std::pair<PVal, PVal>) << endl;

    cout << PVal(_arr(
        123, _atom(1002, func_t(0x12345678)),
        456, _str("xxx\n\t\r啊\x01\x7F", 1004),
        789, _pair(
            _int(123, 1006, stdauto),
            _real(45.6, id_real),
        1005),
        101112, _ptr(_func(stdauto, 1008)),
    1001)) << endl;

    cout << PVal(_pair(_arr(1, _ptr(_arr())), _atom())) << endl;

    for (int i = 0; i < 100000; ++i) {
        // memory leak test
        PVal(
            _arr(
                123, _atom(1002, func_t(0x12345678)),
                456, _str("xxx\n\t\r啊\x01\x7F", 1004),
                789, _pair(
                    _int(123, 1006, stdauto),
                    _real(45.6, id_real),
                1005),
                101112, _ptr(_func(stdauto, 1008)),
            1001)
        );

        // correctness test
        PVal a1(_atom(1002, stdauto));
        PVal a2(_int(1002, 123, stdauto, a1.raw()));
        (void) a2;
        PMaybe a3 = a2;
        PVal a4(a3);
        PMaybe a5 = a3;
        PMaybe a6(_atom(1234));
        // cout << (a2 == a1) << endl;
        // cout << a1 << endl;
        // cout << a2.as<Int>()->get() << endl;
    }

    // end

    return 0;
}
