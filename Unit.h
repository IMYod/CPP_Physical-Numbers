#pragma once

namespace ariel{

enum class Unit{CM, M, KM, SEC, MIN, HOUR, G, KG, TON};
enum class Dimenson{LENGTH, TIME, WEIGHT};

long double ratio(Unit type){
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

Unit unitByString(std::string str){
	if (!str.compare("cm")) //the strings are equale
		return (Unit::CM);
	if (!str.compare("m"))	
		return (Unit::M);
	if (!str.compare("km"))	
		return (Unit::KM);
	if (!str.compare("sec"))	
		return (Unit::SEC);
	if (!str.compare("min"))	
		return (Unit::MIN);
	if (!str.compare("hour"))
		return (Unit::HOUR);
	if (!str.compare("g"))	
		return (Unit::G);
	if (!str.compare("kg"))	
		return (Unit::KG);
	return Unit::TON;
}


Dimenson getDimenson(enum Unit a){
	if (a==Unit::CM || a==Unit::M || a==Unit::KM)
		return Dimenson::LENGTH;
	else if (a==Unit::SEC || a==Unit::MIN || a==Unit::HOUR)
		return Dimenson::TIME;
	return Dimenson::WEIGHT;
}

bool comparable(const enum Unit a, const enum Unit b){
	return (getDimenson(a) == getDimenson(b));
}

bool operator >(const enum Unit a, const enum Unit b){
	return (ratio(a) > ratio(b));
}
bool operator <(const enum Unit a, const enum Unit b){
	return (ratio(a) < ratio(b));
}

}
