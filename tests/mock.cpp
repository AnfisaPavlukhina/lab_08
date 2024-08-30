#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>
#include "Account.h"
#include "Transaction.h"

class MockAccount : public Account {
private:
  int id;
  int balance;
public:
  MockAccount(int id, int balance) : Account(id, balance) {}
  MOCK_METHOD(int, GetBalance, (), (const, override));
  MOCK_METHOD(void, ChangeBalance, (int), (override));
  MOCK_METHOD(void, Lock, (), (override));
  MOCK_METHOD(void, Unlock, (), (override));
};

class MockTransaction : public Transaction {
public:
  MockTransaction() : Transaction() {}
  MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};