/** This example is not supposed to compile!! */
#include <iostream>

class Point {
  public:
  Point(int px, int py) 
       : m_X(px), m_Y(py) {}
       
    void set(int nx, int ny) {  /* C version: _Point_set_int_int(Point* this, int nx, int ny) */
        m_X = nx;
        m_Y = ny;
    }
    void print() const {  /* C version: _Point_print_void_const(const Point* this) */
        using namespace std;
        cout << "[" << m_X << "," << m_Y << "]";
        m_X = 5;  /* error: this->m_X = 5, *this is const */
    }
  private:
    int m_X, m_Y;
};

int main() {
    Point p(1,1);
    const Point q(2,2);
    p.set(4,4);  /* okay to reassign p */
    p.print();
    q.set(4,4);  /* Error! const object cannot 
          call non-const methods */
    return 0;
}

