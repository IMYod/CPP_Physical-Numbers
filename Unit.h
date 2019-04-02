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
	return 0;
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
