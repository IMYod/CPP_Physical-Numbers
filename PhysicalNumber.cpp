#include "Unit.h"
#include "PhysicalNumber.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

using std::istream, std::ostream, std::endl, std::istream, std::ostream, std::string,
std::cout, std::istringstream;
using namespace ariel;


PhysicalNumber::PhysicalNumber(double size, Unit unit): _size(size), _unit(unit) {;}

/*----------------------------------------------*/

const PhysicalNumber PhysicalNumber::operator +() const {
	if (this->size() >= 0)
		return PhysicalNumber(this->size(), this->unit());
	return PhysicalNumber(0-this->size(), this->unit());
}

const PhysicalNumber PhysicalNumber::operator -() const {
	if (this->size() <= 0)
		return PhysicalNumber(this->size(), this->unit());
	return PhysicalNumber(0-this->size(), this->unit());
}

/*----------------------------------------------*/

const PhysicalNumber ariel::operator +(const PhysicalNumber& a, const PhysicalNumber& b){
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return PhysicalNumber(a.size() + b.size()*ratio(b.unit())/ratio(a.unit()), a.unit());
}

const PhysicalNumber ariel::operator -(const PhysicalNumber& a, const PhysicalNumber& b){
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return PhysicalNumber(a.size() - b.size()*ratio(b.unit())/ratio(a.unit()), a.unit());
}

PhysicalNumber& PhysicalNumber::operator +=(const PhysicalNumber& b){
	if (!comparable(this->unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");	
	this->size() += b.size()*ratio(b.unit())/ratio(this->unit());
	return *this;
}

PhysicalNumber& PhysicalNumber::operator -=(const PhysicalNumber& b){
	if (!comparable(this->unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");	
	this->size() -= b.size()*ratio(b.unit())/ratio(this->unit());
	return *this;
}

/*-----------------------------------------------*/

bool ariel::operator >(const PhysicalNumber& a, const PhysicalNumber& b) {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() > ratio(b.unit())*b.size());
}

bool ariel::operator >=(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() >= ratio(b.unit())*b.size());
}

bool ariel::operator <(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() < ratio(b.unit())*b.size());
}

bool ariel::operator <=(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() <= ratio(b.unit())*b.size());
}

bool ariel::operator ==(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() == ratio(b.unit())*b.size());
}

bool ariel::operator !=(const PhysicalNumber& a, const PhysicalNumber& b)  {
	if (!comparable(a.unit(),b.unit()))
		throw std::string("The physical numbers are not comparable");
	return (ratio(a.unit())*a.size() != ratio(b.unit())*b.size());
}


/*-----------------------------------------------*/


ostream& ariel::operator <<(ostream& os, const PhysicalNumber& num) {
	return os << num.size() << "[" << num.unit() << "]";
}

static istream& getAndCheckIsToUnit(istream& input, Unit& new_unit) {
	string str;
	input >> str;
	if (!str.compare("cm]")) //the strings are equale
		new_unit = (Unit::CM);
	else if (!str.compare("m]"))	
		new_unit = (Unit::M);
	else if (!str.compare("km]"))	
		new_unit = (Unit::KM);
	else if (!str.compare("sec]"))	
		new_unit = (Unit::SEC);
	else if (!str.compare("min]"))	
		new_unit = (Unit::MIN);
	else if (!str.compare("hour]"))
		new_unit = (Unit::HOUR);
	else if (!str.compare("g]"))	
		new_unit = (Unit::G);
	else if (!str.compare("kg]"))	
		new_unit = (Unit::KG);
	else if (!str.compare("ton]"))
		new_unit = (Unit::TON);
	else input.setstate(std::ios::failbit);
	return input;
}

static istream& getAndCheckNextCharIs(istream& input, char expectedChar) {
    char actualChar;
    input >> actualChar;
    if (!input)
	return input;

    if (actualChar!=expectedChar) 
        // failbit is for format error
        input.setstate(std::ios::failbit);
    return input;
}

istream& ariel::operator>> (istream& input, PhysicalNumber& num) {
    //---------------------------------------------
    // Checks format, with rewind on failure.
    //---------------------------------------------

	double new_size;
	Unit new_unit;

	// remember place for rewinding
	std::ios::pos_type startPosition = input.tellg();

	if ( (!(input >> new_size))		||
	(!getAndCheckNextCharIs(input,'['))	||
	(!getAndCheckIsToUnit(input, new_unit)) )
	{

	        // rewind on error
	        auto errorState = input.rdstate(); // remember error state
	        input.clear(); // clear error so seekg will work
	        input.seekg(startPosition); // rewind
	        input.clear(errorState); // set back the error flag
	}
	else {
        	num.size() = new_size;
		num.unit() = new_unit;
	}

	return input;
}

/*-----------------------------------------------*/
/*unit functions*/

double ariel::ratio(const enum ariel::Unit type){
	switch (type){
		case Unit::CM: return 1;
		case Unit::M: return 100;
		case Unit::KM: return 100000;
		case Unit::SEC: return 1;
		case Unit::MIN: return 60;
		case Unit::HOUR: return 3600;
		case Unit::G: return 1;
		case Unit::KG: return 1000;
		case Unit::TON: return 1000000;
	}
}


int getUnitID(const enum Unit type){
	switch (type){
		case Unit::CM: return 1;
		case Unit::M: return 1;
		case Unit::KM: return 1;
		case Unit::SEC: return 2;
		case Unit::MIN: return 2;
		case Unit::HOUR: return 2;
		case Unit::G: return 3;
		case Unit::KG: return 3;
		case Unit::TON: return 3;
	}
}

bool ariel::comparable(const enum ariel::Unit a, const enum ariel::Unit b){
	return (getUnitID(a) == getUnitID(b));
}

inline std::ostream& operator << (std::ostream &os, const enum Unit u){
	switch (u){
		case Unit::CM: return os << "cm";
		case Unit::M: return os << "m";
		case Unit::KM: return os << "km";
		case Unit::SEC: return os << "sec";
		case Unit::MIN: return os << "min";
		case Unit::HOUR: return os << "hour";
		case Unit::G: return os << "g";
		case Unit::KG: return os << "kg";
		case Unit::TON: return os << "ton";
	}
}
