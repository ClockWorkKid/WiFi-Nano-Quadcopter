#ifndef MYVECTOR_H
#define MYVECTOR_H

class myVector {
  public:
    double x, y, z;

    myVector();

    myVector operator + (myVector const &obj);
    myVector operator + (double a);
    myVector operator - (myVector const &obj);
    myVector operator - (double a);
    myVector operator * (myVector const &obj);
    myVector operator * (double a);
    myVector operator / (double a);

    double dot(myVector const &obj);
    double norm();

    void print();
};

#endif
