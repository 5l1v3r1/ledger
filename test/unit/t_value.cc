#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include <system.hh>

#include "value.h"

using namespace ledger;

struct value_fixture {
  value_fixture() {
  times_initialize();
  amount_t::initialize();
  value_t::initialize();


  // Cause the display precision for dollars to be initialized to 2.
  amount_t x1("$1.00");
  BOOST_CHECK(x1);

  amount_t::stream_fullstrings = true; // make reports from UnitTests accurate
  }

  ~value_fixture()
  {
  amount_t::stream_fullstrings = false;
  amount_t::shutdown();
  times_shutdown();
  value_t::shutdown();
  }
};

BOOST_FIXTURE_TEST_SUITE(value, value_fixture)

BOOST_AUTO_TEST_CASE(testConstructors)
{
  value_t v1;
  value_t v2(true);
  value_t v3(boost::posix_time::from_time_t(time_t(NULL)));
  value_t v4(date_t(parse_date("2014/08/14")));
  value_t v5(2L);
  value_t v6(4UL);
  value_t v7(1.00);
  value_t v8(amount_t("4 GBP"));
  value_t v9(balance_t("3 EUR"));
  value_t v10(mask_t("regex"));
  value_t v11(new value_t::sequence_t());
  value_t v12(string("$1"));
  value_t v13("2 CAD");
  value_t v14("comment", true);
  value_t v15(string("tag"), true);

  BOOST_CHECK(v1.valid());
  BOOST_CHECK(v2.valid());
  BOOST_CHECK(v3.valid());
  BOOST_CHECK(v4.valid());
  BOOST_CHECK(v5.valid());
  BOOST_CHECK(v6.valid());
  BOOST_CHECK(v7.valid());
  BOOST_CHECK(v8.valid());
  BOOST_CHECK(v9.valid());
  BOOST_CHECK(v10.valid());
  BOOST_CHECK(v11.valid());
  BOOST_CHECK(v12.valid());
  BOOST_CHECK(v13.valid());
  BOOST_CHECK(v14.valid());
  BOOST_CHECK(v15.valid());
}

BOOST_AUTO_TEST_CASE(testAssignment)
{
  value_t v1;
  value_t v2 = true;
  value_t v3 = boost::posix_time::from_time_t(time_t(NULL));
  value_t v4 = date_t(parse_date("2014/08/14"));
  value_t v5 = -2L;
  value_t v6 = 4UL;
  value_t v7 = 1.00;
  value_t v8 = amount_t("4 GBP");
  value_t v9 = balance_t("3 EUR");
  value_t v10 = mask_t("regex");
  value_t v11 = new value_t::sequence_t();
  value_t v12 = new value_t(string("$1"));
  value_t v13 = new value_t("2 CAD");
  value_t v14 = new value_t("comment",true);
  value_t v15 = new value_t(string("tag"),true);

  BOOST_CHECK(v1.valid());
  BOOST_CHECK(v2.valid());
  BOOST_CHECK(v3.valid());
  BOOST_CHECK(v4.valid());
  BOOST_CHECK(v5.valid());
  BOOST_CHECK(v6.valid());
  BOOST_CHECK(v7.valid());
  BOOST_CHECK(v8.valid());
  BOOST_CHECK(v9.valid());
  BOOST_CHECK(v10.valid());
  BOOST_CHECK(v11.valid());
  BOOST_CHECK(v12.valid());
  BOOST_CHECK(v13.valid());
  BOOST_CHECK(v14.valid());
  BOOST_CHECK(v15.valid());
}

BOOST_AUTO_TEST_CASE(testEquality)
{
  struct tm localtime;
  strptime("10 February 2010", "%d %b %Y", &localtime);
  time_t time_var = mktime(&localtime);

  value_t v1;
  value_t v2(true);
  value_t v3(boost::posix_time::from_time_t(time_var));
  value_t v4(date_t(parse_date("2014/08/14")));
  value_t v5(2L);
  value_t v6(2UL);
  value_t v7(1.00);
  value_t v8(amount_t("4 GBP"));
  value_t v9(balance_t("4 GBP"));
  value_t v10(mask_t("regex"));
  value_t v11(new value_t::sequence_t());
  value_t v12(string("$1"));
  value_t v13("2 CAD");
  value_t v14("comment", true);
  value_t v15(string("comment"), true);
  value_t v16;

  BOOST_CHECK_EQUAL(v1, value_t());
  BOOST_CHECK_EQUAL(v2, value_t(true));
  BOOST_CHECK_EQUAL(v3, value_t(boost::posix_time::from_time_t(time_var)));
  BOOST_CHECK(!(v4 == value_t(date_t(parse_date("2014/08/15")))));

  value_t v19(amount_t("2"));
  value_t v20(balance_t("2"));
  BOOST_CHECK_EQUAL(v5, v6);
  BOOST_CHECK_EQUAL(v5, v19);
  BOOST_CHECK_EQUAL(v5, v20);
  BOOST_CHECK(v19 == v5);
  BOOST_CHECK(v19 == v20);
  BOOST_CHECK(v19 == value_t(amount_t("2")));
  BOOST_CHECK(v20 == v5);
  BOOST_CHECK(v20 == v19);
  BOOST_CHECK(v20 == value_t(balance_t(2L)));
  BOOST_CHECK(v14 == v15);
  BOOST_CHECK(v10 == value_t(mask_t("regex")));
  BOOST_CHECK(v11 == value_t(new value_t::sequence_t()));

  BOOST_CHECK_THROW(v8 == v10, value_error);

  BOOST_CHECK(v1.valid());
  BOOST_CHECK(v2.valid());
  BOOST_CHECK(v3.valid());
  BOOST_CHECK(v4.valid());
  BOOST_CHECK(v5.valid());
  BOOST_CHECK(v6.valid());
  BOOST_CHECK(v7.valid());
  BOOST_CHECK(v8.valid());
  BOOST_CHECK(v9.valid());
  BOOST_CHECK(v10.valid());
  BOOST_CHECK(v11.valid());
  BOOST_CHECK(v12.valid());
  BOOST_CHECK(v13.valid());
  BOOST_CHECK(v14.valid());
  BOOST_CHECK(v15.valid());
  BOOST_CHECK(v19.valid());
  BOOST_CHECK(v20.valid());
}

BOOST_AUTO_TEST_CASE(testAddition)
{
  struct tm localtime;
  strptime("10 February 2010 00:00:00", "%d %b %Y %H:%M:%S", &localtime);
  time_t time_var = mktime(&localtime);

  value_t v1;
  value_t v2(true);
  value_t v3(boost::posix_time::from_time_t(time_var));
  value_t v4(date_t(parse_date("2014/08/14")));
  value_t v5(2L);
  value_t v6(2UL);
  value_t v7(1.00);
  value_t v8(amount_t("4 GBP"));
  value_t v9(balance_t("4 GBP"));
  value_t v10(mask_t("regex"));
  value_t v11(new value_t::sequence_t());
  value_t v12(string("$1"));
  value_t v13("2 CAD");
  value_t v14("comment", true);
  value_t v15(string("comment"), true);
  value_t v16(amount_t("2"));

  v14 += v15;
  BOOST_CHECK_EQUAL(v14, value_t(string("commentcomment"), true));
  v14 += v12;
  BOOST_CHECK_EQUAL(v14, value_t(string("commentcomment$1.00"), true));

  v3 += value_t(2L);
  strptime("10 February 2010 00:00:02", "%d %b %Y %H:%M:%S", &localtime);
  BOOST_CHECK_EQUAL(v3, value_t(boost::posix_time::from_time_t(mktime(&localtime))));
  v3 += value_t(amount_t("2"));
  strptime("10 February 2010 00:00:04", "%d %b %Y %H:%M:%S", &localtime);
  BOOST_CHECK_EQUAL(v3, value_t(boost::posix_time::from_time_t(mktime(&localtime))));

  v4 += value_t(2L);
  BOOST_CHECK_EQUAL(v4, value_t(date_t(parse_date("2014/08/16"))));
  v4 += value_t(amount_t("2"));
  BOOST_CHECK_EQUAL(v4, value_t(date_t(parse_date("2014/08/18"))));

  v5 += value_t(2L);
  BOOST_CHECK_EQUAL(v5, value_t(4L));
  v5 += value_t(amount_t("2"));
  BOOST_CHECK_EQUAL(v5, value_t(amount_t("6")));
  v5 += v8;

  v16 += value_t(2L);
  v16 += value_t(amount_t("2"));
  v16 += v8;
  BOOST_CHECK_EQUAL(v5, v16);

  v8 += value_t("6");
  BOOST_CHECK_EQUAL(v8, v16);

  value_t v17(6L);
  v17 += value_t(amount_t("4 GBP"));
  BOOST_CHECK_EQUAL(v8, v17);

  value_t v18(6L);
  v18 += v9;
  value_t v19(amount_t("6"));
  v19 += v9;
  BOOST_CHECK_EQUAL(v18, v19);

  v9 += value_t(2L);
  v9 += value_t(amount_t("4"));
  v9 += v19;
  v18 += v19;
  BOOST_CHECK_EQUAL(v9, v18);

  value_t v20(new value_t::sequence_t());
  v11.push_back(value_t(2L));
  v11.push_back(value_t("4 GBP"));
  v20.push_back(value_t(2L));
  BOOST_CHECK_THROW(v11 += v20,value_error);
  BOOST_CHECK_THROW(v10 += v8, value_error);

  v20 += value_t("4 GBP");
  BOOST_CHECK_EQUAL(v11, v20);

  BOOST_CHECK(v1.valid());
  BOOST_CHECK(v2.valid());
  BOOST_CHECK(v3.valid());
  BOOST_CHECK(v4.valid());
  BOOST_CHECK(v5.valid());
  BOOST_CHECK(v6.valid());
  BOOST_CHECK(v7.valid());
  BOOST_CHECK(v8.valid());
  BOOST_CHECK(v9.valid());
  BOOST_CHECK(v10.valid());
  BOOST_CHECK(v11.valid());
  BOOST_CHECK(v12.valid());
  BOOST_CHECK(v13.valid());
  BOOST_CHECK(v14.valid());
  BOOST_CHECK(v15.valid());
  BOOST_CHECK(v16.valid());
  BOOST_CHECK(v17.valid());
  BOOST_CHECK(v18.valid());
  BOOST_CHECK(v19.valid());
  BOOST_CHECK(v20.valid());
}

BOOST_AUTO_TEST_CASE(testSubtraction)
{
  struct tm localtime;
  strptime("10 February 2010 00:00:04", "%d %b %Y %H:%M:%S", &localtime);
  time_t time_var = mktime(&localtime);

  value_t v1;
  value_t v2(true);
  value_t v3(boost::posix_time::from_time_t(time_var));
  value_t v4(date_t(parse_date("2014/08/18")));
  value_t v5(6L);
  value_t v6(6UL);
  value_t v7(1.00);
  value_t v8(amount_t("4 GBP"));
  value_t v9(balance_t("4 GBP"));
  value_t v10(mask_t("regex"));
  value_t v11(new value_t::sequence_t());
  value_t v12(string("$1"));
  value_t v13("2 CAD");
  value_t v14("comment", true);
  value_t v15(string("comment"), true);
  value_t v16(amount_t("6"));

  v3 -= value_t(2L);
  strptime("10 February 2010 00:00:02", "%d %b %Y %H:%M:%S", &localtime);
  BOOST_CHECK_EQUAL(v3, value_t(boost::posix_time::from_time_t(mktime(&localtime))));
  v3 -= value_t(amount_t("2"));
  strptime("10 February 2010 00:00:00", "%d %b %Y %H:%M:%S", &localtime);
  BOOST_CHECK_EQUAL(v3, value_t(boost::posix_time::from_time_t(mktime(&localtime))));

  v4 -= value_t(2L);
  BOOST_CHECK_EQUAL(v4, value_t(date_t(parse_date("2014/08/16"))));
  v4 -= value_t(amount_t("2"));
  BOOST_CHECK_EQUAL(v4, value_t(date_t(parse_date("2014/08/14"))));

  v5 -= value_t(2L);
  BOOST_CHECK_EQUAL(v5, value_t(4L));
  v5 -= value_t(amount_t("2"));
  BOOST_CHECK_EQUAL(v5, value_t(amount_t("2")));
  v5 -= v8;

  v16 -= value_t(2L);
  v16 -= value_t(amount_t("2"));
  v16 -= v8;
  BOOST_CHECK_EQUAL(v5, v16);

  v8 -= value_t("2");
  BOOST_CHECK_EQUAL(-v8, v16);

  value_t v18(6L);
  v18 -= v9;
  value_t v19(amount_t("6"));
  v19 -= v9;
  BOOST_CHECK_EQUAL(v18, v19);

  v9 -= value_t(-2L);
  v9 -= value_t(amount_t("-10"));
  v9 -= value_t(amount_t("12 GBP"));
  v9 -= v19;
  BOOST_CHECK_EQUAL(v9, v18);
  v18 -=v19;
  BOOST_CHECK_EQUAL(v18, value_t("0"));

  value_t v20(new value_t::sequence_t());
  value_t v21(2L);
  value_t v22("4 GBP");
  v11.push_back(v21);
  v11.push_back(v22);
  v20.push_back(v21);
  BOOST_CHECK_THROW(v11 -= v20,value_error);
  BOOST_CHECK_THROW(v10 -= v8, value_error);

  BOOST_CHECK(v1.valid());
  BOOST_CHECK(v2.valid());
  BOOST_CHECK(v3.valid());
  BOOST_CHECK(v4.valid());
  BOOST_CHECK(v5.valid());
  BOOST_CHECK(v6.valid());
  BOOST_CHECK(v7.valid());
  BOOST_CHECK(v8.valid());
  BOOST_CHECK(v9.valid());
  BOOST_CHECK(v10.valid());
  BOOST_CHECK(v11.valid());
  BOOST_CHECK(v12.valid());
  BOOST_CHECK(v13.valid());
  BOOST_CHECK(v14.valid());
  BOOST_CHECK(v15.valid());
  BOOST_CHECK(v16.valid());
  BOOST_CHECK(v18.valid());
  BOOST_CHECK(v19.valid());
  BOOST_CHECK(v20.valid());
}

BOOST_AUTO_TEST_SUITE_END()

