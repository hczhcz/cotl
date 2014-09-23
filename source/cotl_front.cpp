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
    cout << sizeof(Map) << endl;
    cout << sizeof(std::string) << endl;
    std::string s("aaahhhh");
    cout << sizeof(s) << endl;
    // cout << sizeof(std::vector<PVal>) << endl;
    // cout << sizeof(std::map<int, PVal>) << endl;
    cout << sizeof(arr_t) << endl;
    cout << sizeof(map_t) << endl;
    // cout << sizeof(std::unordered_map<int, PVal>) << endl;
    cout << sizeof(std::pair<PVal, PVal>) << endl;

    cout << PVal(_map(
        123, _atom(1002, func_t(0x12345678)),
        456, _str("xxx\n\t\r啊\x01\x7F", 1004),
        789, _pair(
            _int(123, 1006, stdAuto),
            _real(45.6, id_real),
        1005),
        101112, _arr(
            _ptr(_func(stdAuto, 1008)),
            _atom(),
            _atom(),
            1009
        ),
    1001)) << endl;

    cout << PVal(_pair(_arr(_map(123), _map(1, _ptr(_map())), _arr()), _atom())) << endl;

    for (int i = 0; i < 10000; ++i) {
        // memory leak test
        PVal(
            _map(
                123, _atom(1002, func_t(0x12345678)),
                456, _str("xxx\n\t\r啊\x01\x7F", 1004),
                789, _pair(
                    _int(123, 1006, stdAuto),
                    _real(45.6, id_real),
                1005),
                101112, _arr(
                    _ptr(_func(stdAuto, 1008)),
                    _atom(),
                    _atom(),
                    1009
                ),
            1001)
        );

        // correctness test
        PVal a1(_atom(1002, stdAuto));
        PVal a2(_int(1002, 123, stdAuto, a1.raw()));
        (void) a2;
        PMaybe a3(a2); //PMaybe a3 = a2;
        PVal a4(a3);
        PMaybe a5(a4); //PMaybe a5 = a3;
        PMaybe a6(_atom(1234));
        // cout << (a2 == a1) << endl;
        // cout << a1 << endl;
        // cout << a2.as<Int>()->get() << endl;

        PMaybe tunnel1(nullptr);

        boot(_atom(), tunnel1);

    }

    PMaybe tunnel1(nullptr);

    // boot(_ptr(_pair(_atom(), _int(233)), id_quote), tunnel1);
    boot(_pair(_int(233), _int(233), id_add), tunnel1);

    cout << tunnel1 << endl;

    // end

    return 0;
}
