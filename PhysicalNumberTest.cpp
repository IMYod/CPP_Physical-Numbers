/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>

using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main() {
  badkan::TestCase testcase;
  int grade=0;
  int signal = setjmp(badkan::longjmp_buffer);
  if (signal == 0) {

    // BASIC TESTS - DO NOT CHANGE
    PhysicalNumber a(2, Unit::KM);
    PhysicalNumber b(300, Unit::M);
    PhysicalNumber c(2, Unit::HOUR);
    PhysicalNumber d(30, Unit::MIN);

    PhysicalNumber lengthDimTest (1 ,Unit::CM);
    PhysicalNumber lengthDimTest2 (2 ,Unit::M);
    
	PhysicalNumber timeDimTest (1 ,Unit::SEC);
	PhysicalNumber timeDimTest2 (1 ,Unit::MIN);
	
	PhysicalNumber massDimTest (1 ,Unit::G);
    PhysicalNumber massDimTest2 (1 ,Unit::KG);
	bool tempB;



    testcase
    .setname("Basic output")
    .CHECK_OUTPUT(a, "2[km]")
    .CHECK_OUTPUT(b, "300[m]")

    .setname("Compatible dimensions")
    .CHECK_OUTPUT(b+a, "2300[m]")
    .CHECK_OUTPUT((a+=b), "2.3[km]")
    .CHECK_OUTPUT(a, "2.3[km]")
    .CHECK_OUTPUT(a+a, "4.6[km]")
    .CHECK_OUTPUT(b-b, "0[m]")
    .CHECK_OUTPUT(c, "2[hour]")
    .CHECK_OUTPUT(d, "30[min]")
    .CHECK_OUTPUT(d+c, "150[min]")

    .setname("Incompatible dimensions")
    .CHECK_THROWS(a+c)
    .CHECK_THROWS(a+d)
    .CHECK_THROWS(b+c)
    .CHECK_THROWS(b+d)

    .setname("Basic input")
    .CHECK_OK(istringstream("700[kg]") >> a)
    .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")

    /*OUR TESTS*/
    
    //*****Test the LENGTH dimenstion*******//
    
    .setname("Test the lenght dimenstion")
    //CM
    .CHECK_OUTPUT(lengthDimTest, "1[cm]") 
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::CM)), "2[cm]") // cm + cm
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::CM)), "1[cm]") //cm - cm
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::M)), "101[cm]") // cm +m
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::KM)), "100101[cm]") // cm + km 
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::M)), "100001[cm]") // cm - m 
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::KM)), "1[cm]") // cm- km 
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(0, Unit::CM)), "1[cm]") // cm - 0cm
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(0, Unit::M)), "1[cm]") // cm + 0m
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(0, Unit::KM)), "1[cm]") // cm + 0km
    //M
    .CHECK_OK(istringstream("1[m]") >> lengthDimTest)
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::M)), "2[m]") // m + m
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::M)), "1[m]")// m - m
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::CM)), "1.01[m]") // m + cm
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::KM)), "1001.01[m]") // m + km
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::CM)), "1001[m]") // m - cm
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::KM)), "1[m]") // m - km
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(0, Unit::M)), "1[m]") // m - 0m
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(0, Unit::CM)), "1[m]")// m - 0cm
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(0, Unit::KM)), "1[m]")// m + 0km
    //KM
    .CHECK_OK(istringstream("1[km]") >> lengthDimTest)
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::KM)), "2[km]") // km + km
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::KM)), "1[km]")// km - km
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::CM)), "1.00001[km]") // km + cm
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::M)), "1.00101[km]") // km + m
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::CM)), "1.001[km]") // km - cm
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::M)), "1[km]") // km - m
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(0, Unit::KM)), "1[km]") // km - 0km
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(0, Unit::CM)), "1[km]")// km - 0cm
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(0, Unit::M)), "1[km]")// km + 0km
    //check Incompatible dimensions
    .CHECK_THROWS(lengthDimTest + timeDimTest)
    .CHECK_THROWS(lengthDimTest + massDimTest)
    .CHECK_THROWS(lengthDimTest - timeDimTest)
    .CHECK_THROWS(lengthDimTest - massDimTest)
    //check Comparison
    .CHECK_EQUAL (lengthDimTest > lengthDimTest2 ,true)
    .CHECK_EQUAL (lengthDimTest < lengthDimTest2 ,false)
    .CHECK_EQUAL (lengthDimTest >= lengthDimTest2 ,true)
    .CHECK_EQUAL (lengthDimTest <= lengthDimTest2 ,false)
    .CHECK_EQUAL (lengthDimTest == lengthDimTest2 ,false)
    .CHECK_EQUAL (lengthDimTest != lengthDimTest2 ,true) 
    .CHECK_THROWS (tempB = lengthDimTest < timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest > timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest <= timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest >= massDimTest)
    .CHECK_THROWS (tempB = lengthDimTest == massDimTest)
    .CHECK_THROWS (tempB = lengthDimTest != massDimTest)
    .CHECK_OK( lengthDimTest2++)
    .CHECK_OUTPUT(lengthDimTest2, "3[m]")
    .CHECK_OUTPUT(-a, "-1700[kg]") // -a
    .CHECK_OUTPUT(+a, "1700[kg]") // +a
    .CHECK_OUTPUT(+-a, "1700[kg]") // +a

      
 //*****Test the TIME dimenstion*******//
    
    .setname("Test the TIME dimenstion")
    //SEC
    .CHECK_OUTPUT(timeDimTest, "1[sec]") 
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(1, Unit::SEC)), "2[sec]") // sec + sec
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(1, Unit::SEC)), "1[sec]") //sec - sec
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(1, Unit::MIN)), "61[sec]") // sec + min
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(1, Unit::HOUR)), "3661[sec]") // sec + hour 
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(1, Unit::MIN)), "3601[sec]") // sec - min 
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(1, Unit::HOUR)), "1[sec]") // sec - hour 
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(0, Unit::SEC)), "1[sec]") // sec - 0sec
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(0, Unit::MIN)), "1[sec]") // sec + 0min
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(0, Unit::HOUR)), "1[sec]") // sec + 0hour
    //MIN
    .CHECK_OK(istringstream("1[min]") >> timeDimTest)
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(1, Unit::MIN)), "2[min]") // min + min
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(1, Unit::MIN)), "1[min]")// min - min
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(3, Unit::SEC)), "1.05[min]") // min + sec
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(1, Unit::HOUR)), "61.05[min]") // min + hour
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(3, Unit::SEC)), "61[min]") // min - sec
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(1, Unit::HOUR)), "1[min]") // min - hour
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(0, Unit::MIN)), "1[min]") // min - 0min
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(0, Unit::SEC)), "1[min]")// min - 0sec
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(0, Unit::HOUR)), "1[min]")// min + 0hour
    //HOUR
    .CHECK_OK(istringstream("1[hour]") >> timeDimTest)
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(1, Unit::HOUR)), "2[hour]") // hour + hour
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(1, Unit::HOUR)), "1[hour]")// hour - hour
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(90, Unit::SEC)), "1.025[hour]") // hour + sec
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(6, Unit::MIN)), "1.125[hour]") // hour + min
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(90, Unit::SEC)), "1.1[hour]") // hour - sec
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(6, Unit::MIN)), "1[hour]") // hour - min
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(0, Unit::HOUR)), "1[hour]") // hour - 0hour
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(0, Unit::SEC)), "1[hour]")// hour - 0sec
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(0, Unit::MIN)), "1[hour]")// hour + 0min
    //check Incompatible dimensions
    .CHECK_THROWS(timeDimTest + lengthDimTest)
    .CHECK_THROWS(timeDimTest + massDimTest)
    .CHECK_THROWS(timeDimTest - massDimTest)
    .CHECK_THROWS(timeDimTest - lengthDimTest)
    //check Comparison
    .CHECK_EQUAL (timeDimTest > timeDimTest2 ,true)
    .CHECK_EQUAL (timeDimTest < timeDimTest2 ,false)
    .CHECK_EQUAL (timeDimTest >= timeDimTest2 ,true)
    .CHECK_EQUAL (timeDimTest <= timeDimTest2 ,false)
    .CHECK_EQUAL (timeDimTest == timeDimTest2 ,false)
    .CHECK_EQUAL (timeDimTest != timeDimTest2 ,true) 
    .CHECK_THROWS (tempB = lengthDimTest < timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest > timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest <= timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest >= massDimTest)
    .CHECK_THROWS (tempB = lengthDimTest == massDimTest)
    .CHECK_THROWS (tempB = lengthDimTest != massDimTest)
     .CHECK_OK( timeDimTest++) 
    .CHECK_OUTPUT(timeDimTest, "2[hour]")
    .CHECK_OUTPUT(-timeDimTest, "-2[hour]") // -a
    .CHECK_OUTPUT(+timeDimTest, "2[hour]") // +a      
      
	//*****Test the MASS dimenstion*******//
	
	    .setname("Test the MASS dimenstion")
    //G
    .CHECK_OUTPUT(massDimTest, "1[g]") 
    .CHECK_OUTPUT((massDimTest += PhysicalNumber(1, Unit::G)), "2[g]") // g + g
    .CHECK_OUTPUT((massDimTest -= PhysicalNumber(1, Unit::G)), "1[g]") //g - g
    .CHECK_OUTPUT((massDimTest += PhysicalNumber(1, Unit::KG)), "1001[g]") // g + kg
    .CHECK_OUTPUT((massDimTest += PhysicalNumber(0.1, Unit::TON)), "101001[g]") // g + ton 
    .CHECK_OUTPUT((massDimTest -= PhysicalNumber(1, Unit::KG)), "100001[g]") // g - kg 
    .CHECK_OUTPUT((massDimTest -= PhysicalNumber(0.1, Unit::TON)), "1[g]") // g - ton 
    .CHECK_OUTPUT((massDimTest -= PhysicalNumber(0, Unit::G)), "1[g]") // g - 0g
    .CHECK_OUTPUT((massDimTest += PhysicalNumber(0, Unit::KG)), "1[g]") // g + 0kg 
    .CHECK_OUTPUT((massDimTest += PhysicalNumber(0, Unit::TON)), "1[g]") // g + 0ton 
    //KG
    .CHECK_OK(istringstream("1[kg]") >> massDimTest)
    .CHECK_OUTPUT((massDimTest += PhysicalNumber(1, Unit::KG)), "2[kg]") // kg + kg
    .CHECK_OUTPUT((massDimTest -= PhysicalNumber(1, Unit::KG)), "1[kg]")// kg - kg
    .CHECK_OUTPUT((massDimTest += PhysicalNumber(10, Unit::G)), "1.01[kg]") // kg + g
    .CHECK_OUTPUT((massDimTest += PhysicalNumber(1, Unit::TON)), "1001.01[kg]") // kg + ton
    .CHECK_OUTPUT((massDimTest -= PhysicalNumber(10, Unit::G)), "1001[kg]") // kg - g
    .CHECK_OUTPUT((massDimTest -= PhysicalNumber(1, Unit::TON)), "1[kg]") // kg - ton
    .CHECK_OUTPUT((massDimTest -= PhysicalNumber(0, Unit::KG)), "1[kg]") // kg - 0kg
    .CHECK_OUTPUT((massDimTest += PhysicalNumber(0, Unit::G)), "1[kg]")// kg - 0g
    .CHECK_OUTPUT((massDimTest += PhysicalNumber(0, Unit::TON)), "1[kg]")// kg + 0ton
    //TON
    .CHECK_OK(istringstream("1[ton]") >> massDimTest)
    .CHECK_OUTPUT((massDimTest += PhysicalNumber(1, Unit::TON)), "2[ton]") // ton + ton
    .CHECK_OUTPUT((massDimTest -= PhysicalNumber(1, Unit::TON)), "1[ton]")// ton - ton
    .CHECK_OUTPUT((massDimTest += PhysicalNumber(10, Unit::G)), "1.00001[ton]") // ton + g
    .CHECK_OUTPUT((massDimTest += PhysicalNumber(1, Unit::KG)), "1.00101[ton]") // ton + kg
    .CHECK_OUTPUT((massDimTest -= PhysicalNumber(10, Unit::G)), "1.001[ton]") // ton - g
    .CHECK_OUTPUT((massDimTest -= PhysicalNumber(1, Unit::KG)), "1[ton]") // ton - kg
    .CHECK_OUTPUT((massDimTest -= PhysicalNumber(0, Unit::TON)), "1[ton]") // ton - 0ton
    .CHECK_OUTPUT((massDimTest += PhysicalNumber(0, Unit::G)), "1[ton]")// ton - 0g
    .CHECK_OUTPUT((massDimTest), "1[ton]")// ton + 0kg
    //check Incompatible dimensions
    .CHECK_THROWS(massDimTest + lengthDimTest)
    .CHECK_THROWS(massDimTest + timeDimTest)
    .CHECK_THROWS(massDimTest - timeDimTest)
    .CHECK_THROWS(massDimTest - lengthDimTest)
    //check Comparison
    .CHECK_EQUAL (massDimTest > massDimTest2 ,true)
    .CHECK_EQUAL (massDimTest < massDimTest2 ,false)
    .CHECK_EQUAL (massDimTest >= massDimTest2 ,true)
    .CHECK_EQUAL (massDimTest <= massDimTest2 ,false)
    .CHECK_EQUAL (massDimTest == massDimTest2 ,false)
    .CHECK_EQUAL (massDimTest != massDimTest2 ,true) 
    .CHECK_THROWS (tempB = lengthDimTest < timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest > timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest <= timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest >= massDimTest)
    .CHECK_THROWS (tempB = lengthDimTest == massDimTest)
    .CHECK_THROWS (tempB = lengthDimTest != massDimTest)
     .CHECK_OK(massDimTest2++)
    .CHECK_OUTPUT(massDimTest2, "2[kg]")
    .CHECK_OUTPUT(-massDimTest2, "-2[kg]") // -a
    .CHECK_OUTPUT(+massDimTest2, "2[kg]") // +a  
      
      .setname("...")

      .print(cout, /*show_grade=*/false);
      grade = testcase.grade();
    } else {
      testcase.print_signal(signal);
      grade = 0;
    }
    cout <<  "*** Grade: " << grade << " ***" << endl;
    return grade;
}
