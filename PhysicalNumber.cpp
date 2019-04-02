#include "PhysicalNumber.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

using std::istream, std::ostream, std::endl, std::istream, std::ostream;
using namespace ariel;


PhysicalNumber(double size, Unit unit);

PhysicalNumber operator +(const PhysicalNumber& a, const PhysicalNumber& b) {return a;}
PhysicalNumber operator -(const PhysicalNumber& a, const PhysicalNumber& b) {return a;}

bool operator >(const PhysicalNumber& a, const PhysicalNumber& b) {return true;}
bool operator >=(const PhysicalNumber& a, const PhysicalNumber& b) {return true;}
bool operator <(const PhysicalNumber& a, const PhysicalNumber& b) {return true;}
bool operator <=(const PhysicalNumber& a, const PhysicalNumber& b) {return true;}
bool operator ==(const PhysicalNumber& a, const PhysicalNumber& b) {return true;}
bool operator !=(const PhysicalNumber& a, const PhysicalNumber& b) {return true;}

PhysicalNumber& operator++();
PhysicalNumber& operator++(int dummy_flag);

ostream& operator <<(ostream& os, const PhysicalNumber& num) {return *ostream;}
istream& operator >>(istream& is, const PhysicalNumber& num) {return *istream;}
