/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "MooseEnumTest.h"
#include "MooseEnum.h"
#include "MultiMooseEnum.h"

CPPUNIT_TEST_SUITE_REGISTRATION( MooseEnumTest );

void
MooseEnumTest::multiTestOne()
{
  MultiMooseEnum mme("one two three four", "two");

  CPPUNIT_ASSERT( mme.contains("one") == false );
  CPPUNIT_ASSERT( mme.contains("two") == true );
  CPPUNIT_ASSERT( mme.contains("three") == false );
  CPPUNIT_ASSERT( mme.contains("four") == false );

  mme.insert("four");
  CPPUNIT_ASSERT( mme.contains("one") == false );
  CPPUNIT_ASSERT( mme.contains("two") == true );
  CPPUNIT_ASSERT( mme.contains("three") == false );
  CPPUNIT_ASSERT( mme.contains("four") == true );

  // isValid
  CPPUNIT_ASSERT ( mme.isValid() == true );

  mme.clear();
  CPPUNIT_ASSERT ( mme.isValid() == false );

  mme.insert("one three");
  CPPUNIT_ASSERT( mme.contains("one") == true );
  CPPUNIT_ASSERT( mme.contains("two") == false );
  CPPUNIT_ASSERT( mme.contains("three") == true );
  CPPUNIT_ASSERT( mme.contains("four") == false );

  std::vector<std::string> mvec(2);
  mvec[0] = "one";
  mvec[1] = "two";

  std::set<std::string> mset;
  mset.insert("two");
  mset.insert("three");

  // Assign
  mme = mvec;
  CPPUNIT_ASSERT( mme.contains("one") == true );
  CPPUNIT_ASSERT( mme.contains("two") == true );
  CPPUNIT_ASSERT( mme.contains("three") == false );
  CPPUNIT_ASSERT( mme.contains("four") == false );

  mme = mset;
  CPPUNIT_ASSERT( mme.contains("one") == false );
  CPPUNIT_ASSERT( mme.contains("two") == true );
  CPPUNIT_ASSERT( mme.contains("three") == true );
  CPPUNIT_ASSERT( mme.contains("four") == false );

  // Insert
  mme.insert(mvec);
  CPPUNIT_ASSERT( mme.contains("one") == true );
  CPPUNIT_ASSERT( mme.contains("two") == true );
  CPPUNIT_ASSERT( mme.contains("three") == true );
  CPPUNIT_ASSERT( mme.contains("four") == false );

  mme.clear();
  mme = "one four";
  CPPUNIT_ASSERT( mme.contains("one") == true );
  CPPUNIT_ASSERT( mme.contains("two") == false );
  CPPUNIT_ASSERT( mme.contains("three") == false );
  CPPUNIT_ASSERT( mme.contains("four") == true );

  mme.insert("three four");
  CPPUNIT_ASSERT( mme.contains("one") == true );
  CPPUNIT_ASSERT( mme.contains("two") == false );
  CPPUNIT_ASSERT( mme.contains("three") == true );
  CPPUNIT_ASSERT( mme.contains("four") == true );

  // Size
  CPPUNIT_ASSERT( mme.size() == 3 );

  // All but "two" should be in the Enum
  std::set<std::string> compare_set, return_set, difference;
  for (MooseEnumIterator it = mme.begin(); it != mme.end(); ++it)
    return_set.insert(*it);

  compare_set.insert("ONE");
  compare_set.insert("THREE");
  compare_set.insert("FOUR");

  std::set_symmetric_difference(return_set.begin(), return_set.end(),
                                compare_set.begin(), compare_set.end(),
                                std::inserter(difference, difference.end()));
  CPPUNIT_ASSERT( difference.size() == 0 );
}
