class Point {                     /* a class definition */
 public:
    Point(int x, int y, int z);    /* a constructor declaration */
    int distance(Point other);     /* a function declaration */
    double norm() const {          /* declaration and definition */         
        return distance(Point(0,0,0));
    } 
 private:
    int m_Xcoord, m_Ycoord, m_Zcoord; /* data member declaration */
};

