#include <Arduino.h>
#include <math.h>
#include "myVector.h"

myVector::myVector() {
  x = 0.0; y = 0.0; z = 0.0;
}

myVector myVector::operator + (myVector const &obj) {
  myVector res;
  res.x = x + obj.x;
  res.y = y + obj.y;
  res.z = z + obj.z;
  return res;
}
myVector myVector::operator + (double a) {
  myVector res;
  res.x = x + a;
  res.y = y + a;
  res.z = z + a;
  return res;
}

myVector myVector::operator - (myVector const &obj) {
  myVector res;
  res.x = x - obj.x;
  res.y = y - obj.y;
  res.z = z - obj.z;
  return res;
}
myVector myVector::operator - (double a) {
  myVector res;
  res.x = x - a;
  res.y = y - a;
  res.z = z - a;
  return res;
}

myVector myVector::operator * (myVector const &obj) {
  myVector res;
  res.x = x * obj.x;
  res.y = y * obj.y;
  res.z = z * obj.z;
  return res;
}
myVector myVector::operator * (double a) {
  myVector res;
  res.x = x * a;
  res.y = y * a;
  res.z = z * a;
  return res;
}

myVector myVector::operator / (double a) {
  myVector res;
  res.x = x / a;
  res.y = y / a;
  res.z = z / a;
  return res;
}

double myVector::dot(myVector const &obj) {
  double dot_product = x * obj.x + y * obj.y + z * obj.z;
  return dot_product;
}

double myVector::norm() {
  double normal = sqrt(x * x + y * y + z * z);
  return normal;
}

void myVector::print() {
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print(" ");
  Serial.print(z);
  Serial.print(" ");
}
