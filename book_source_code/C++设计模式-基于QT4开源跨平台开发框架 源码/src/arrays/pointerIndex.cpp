#include <iostream>
using namespace std;

int main()  {
    int x = 23;
    int* px = &x;
    cout << "px[0] = " << px[0] << endl;
    cout << "px[1] = " << px[1] << endl;
    cout << "px[-1] = " << px[-1] << endl;
    return 0;
}
/*OUT
src/arays> g++ pointerIndex.cc  // compile & run on a Sun station
src/arays> a.out
px[0] = 23
px[1] = 5
px[-1] = -268437516
 
src/arays> g++ pointerIndex.cc  // compile & run on a Linux box
src/arays> ./a.out
px[0] = 23
px[1] = -1073743784
px[-1] = -1073743852
src/arays>
*/
