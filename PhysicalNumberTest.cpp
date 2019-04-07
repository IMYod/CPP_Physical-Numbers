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
    PhysicalNumber massDimTest (1 ,Unit::G);
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
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::KM)), "1101[cm]") // cm + km 
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::M)), "1001[cm]") // cm - m 
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::KM)), "100[cm]") // cm- km 
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(0, Unit::CM)), "100[cm]") // cm - 0cm
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(0, Unit::M)), "100[cm]") // cm + 0m
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(0, Unit::KM)), "100[cm]") // cm + 0km
    //M
    .CHECK_OK(istringstream("1[m]") >> lengthDimTest)
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::M)), "2[m]") // m + m
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::M)), "1[m]")// m - m
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::CM)), "1.01[m]") // m + cm
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::KM)), "1001.01[m]") // m + km
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::CM)), "1101[m]") // m - cm
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::KM)), "101[m]") // m - km
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(0, Unit::M)), "101[m]") // m - 0m
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(0, Unit::CM)), "101[m]")// m - 0cm
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(0, Unit::KM)), "101[m]")// m + 0km
    //KM
    .CHECK_OK(istringstream("1[km]") >> lengthDimTest)
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::KM)), "2[km]") // km + km
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::KM)), "1[km]")// km - km
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::CM)), "1.00001[km]") // km + cm
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(1, Unit::M)), "1.00101[km]") // km + m
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::CM)), "1.00100[km]") // km - cm
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(1, Unit::M)), "1[km]") // km - m
    .CHECK_OUTPUT((lengthDimTest -= PhysicalNumber(0, Unit::KM)), "101[km]") // km - 0km
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(0, Unit::CM)), "101[km]")// km - 0cm
    .CHECK_OUTPUT((lengthDimTest += PhysicalNumber(0, Unit::M)), "101[km]")// km + 0km
    //check Incompatible dimensions
    .CHECK_THROWS(lengthDimTest + timeDimTest)
    .CHECK_THROWS(lengthDimTest + massDimTest)
    .CHECK_THROWS(lengthDimTest - timeDimTest)
    .CHECK_THROWS(lengthDimTest - massDimTest)
    //check Comparison
/*    .CHECK_EQUAL (lengthDimTest < lengthDimTest2 ,TRUE)
    .CHECK_EQUAL (lengthDimTest > lengthDimTest2 ,FALSE)
    .CHECK_EQUAL (lengthDimTest <= lengthDimTest2 ,TRUE)
    .CHECK_EQUAL (lengthDimTest >= lengthDimTest2 ,FALSE)
    .CHECK_EQUAL (lengthDimTest == lengthDimTest2 ,FALSE)
    .CHECK_EQUAL (lengthDimTest != lengthDimTest2 ,TRUE) */
    .CHECK_THROWS (tempB = lengthDimTest < timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest > timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest <= timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest >= massDimTest)
    .CHECK_THROWS (tempB = lengthDimTest == massDimTest)
    .CHECK_THROWS (tempB = lengthDimTest != massDimTest)
//    .CHECK_OK( lengthDimTest2++) / ++ //????? not compiled
    .CHECK_OUTPUT(lengthDimTest2, "3[m]")
    .CHECK_OUTPUT(-a, "-3[m]") // -a
    .CHECK_OUTPUT(+a, "3[km]") // +a
    .CHECK_THROWS (-+a) //????? why not? mayne check if -(+a)==a
//    .CHECK_THROWS (+-----+a) //?????  not compiled
      
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
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(1, Unit::SEC)), "1.01666667[min]") // min + sec
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(1, Unit::HOUR)), "61.01666667[min]") // min + hour
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(1, Unit::SEC)), "61[min]") // min - sec
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(1, Unit::HOUR)), "1[min]") // min - hour
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(0, Unit::MIN)), "1[min]") // min - 0min
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(0, Unit::SEC)), "1[min]")// min - 0sec
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(0, Unit::HOUR)), "1[min]")// min + 0hour
    //HOUR
    .CHECK_OK(istringstream("1[hour]") >> timeDimTest)
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(1, Unit::HOUR)), "2[hour]") // hour + hour
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(1, Unit::HOUR)), "1[hour]")// hour - hour
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(1, Unit::SEC)), "1.000277777778[hour]") // hour + sec
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(1, Unit::MIN)), "1.016944444478[hour]") // hour + min
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(1, Unit::SEC)), "1.0166666667[hour]") // hour - sec
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(1, Unit::MIN)), "1[hour]") // hour - min
    .CHECK_OUTPUT((timeDimTest -= PhysicalNumber(0, Unit::HOUR)), "1[hour]") // hour - 0hour
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(0, Unit::SEC)), "1[hour]")// hour - 0sec
    .CHECK_OUTPUT((timeDimTest += PhysicalNumber(0, Unit::MIN)), "1[hour]")// hour + 0min
    //check Incompatible dimensions
    .CHECK_THROWS(timeDimTest + lengthDimTest)
    .CHECK_THROWS(timeDimTest + massDimTest)
    .CHECK_THROWS(timeDimTest - massDimTest)
    .CHECK_THROWS(timeDimTest - lengthDimTest)
    //check Comparison
    .CHECK_EQUAL (timeDimTest < timeDimTest2 ,TRUE)
    .CHECK_EQUAL (timeDimTest > timeDimTest2 ,FALSE)
    .CHECK_EQUAL (timeDimTest <= timeDimTest2 ,TRUE)
    .CHECK_EQUAL (timeDimTest >= timeDimTest2 ,FALSE)
    .CHECK_EQUAL (timeDimTest == timeDimTest2 ,FALSE)
    .CHECK_EQUAL (timeDimTest != timeDimTest2 ,TRUE) 
    /*.CHECK_THROWS (tempB = lengthDimTest < timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest > timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest <= timeDimTest)
    .CHECK_THROWS (tempB = lengthDimTest >= massDimTest)
    .CHECK_THROWS (tempB = lengthDimTest == massDimTest)
    .CHECK_THROWS (tempB = lengthDimTest != massDimTest)*/
     .CHECK_OK( timeDimTest++) / ++ //????? not compiled
    .CHECK_OUTPUT(timeDimTest, "3[min]")
    .CHECK_OUTPUT(-timeDimTest, "-3[min]") // -a
    .CHECK_OUTPUT(+timeDimTest, "3[nin]") // +a      
      
      
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
