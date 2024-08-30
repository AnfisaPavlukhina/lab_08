#include "mock.cpp"

using ::testing::AtLeast;
TEST(acc, mock) {
  MockAccount dt(1, 100);
  EXPECT_CALL(dt, GetBalance()).Times(AtLeast(1));
  std::cout <<  dt.GetBalance() << std::endl;
  EXPECT_CALL(dt, Lock()).Times(AtLeast(1));
  dt.Lock();
  EXPECT_CALL(dt, Unlock()).Times(AtLeast(1));
  dt.Unlock();
  EXPECT_CALL(dt, ChangeBalance(100)).Times(AtLeast(1));
  dt.ChangeBalance(100);
  
}

TEST(acc, test) {
  Account qt(1, 100);
  EXPECT_EQ(100, qt.GetBalance());
  qt.Lock();
  qt.ChangeBalance(900);
  qt.Unlock();
  EXPECT_EQ(1000, qt.GetBalance());
  try {
    qt.ChangeBalance(1);
  } catch (std::runtime_error& er) {}
  EXPECT_EQ(1000, qt.GetBalance());
}

TEST(tr, mock) {
  Account dt(1, 10000);
  Account rt(2, 10000);
  MockTransaction bank;
  EXPECT_CALL(bank, SaveToDataBase(dt, rt, 1999)).Times(AtLeast(1));
  bank.Make(dt, rt, 1999);  
}

TEST(tr, test) {
  Account qt(1, 10000);
  Account rt(2, 10000);
  Transaction bank1;
  Transaction bank2;
  bank2.set_fee(500);
  try {
  bank1.Make(qt, rt, -100);

  } catch (std::invalid_argument& er) {}

  try {
  bank1.Make(qt, rt, 0);

  } catch (std::logic_error& er) {}

  EXPECT_EQ(false, bank2.Make(qt, rt, 200));
  bank1.Make(qt, rt, 1999);

  EXPECT_EQ(qt.GetBalance(), 10000);
  EXPECT_EQ(rt.GetBalance(), 9999);
}