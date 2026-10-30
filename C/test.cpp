#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std;

vector<int>
move (vector<int> v)
{
    while (!v.empty () && v.back () % 2 == 0)
        v.pop_back ();
    return v;
}

int
main ()
{
    int ival = 42;
    int *ref = &ival;
    int *pi = ref;

    cout << *pi << "\n";

    vector<string> v = { "Hello", "world!" };
    cout << v[0] << v[1] << "\n";

    cout << "This is a c++ file for practice.\n";
    return 0;
}