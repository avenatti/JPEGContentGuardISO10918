


/// @file Guard_test.h
///
/// @brief Unit test file for the Guard class.
///
/// @author Michael W. Benson
/// 
/// History: 
///    M. Benson        2/8/2020        Initial version.


#include <cxxtest/TestSuite.h>


// Name spaces.
using namespace std;


class TestGuard : public CxxTest::TestSuite
{
public:

   void setUp ()
   {

   }


   void tearDown ()
   {

   }


   void TestOne ()
   {
      TS_ASSERT_EQUALS (true, true);
   }
};
