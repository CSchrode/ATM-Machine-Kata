#ifdef DEBUG
#include <string>
#include <iostream>
#include <iomanip>
#include "include/atm.h"

using namespace std;
#include <unit++.h>
using namespace unitpp;

ATM TestATM;
namespace
{
class UnitTest : public suite
{
    void LanguageIsNoneByDefault() {
        assert_true("Language is NONE by default", TestATM.GetLanguage() == ATM::NoLanguage);
    }

    void EnglishSpanishSupport() {
        assert_true("Set Language: English", TestATM.SetLanguage(ATM::English)); //< English and Spanish support only
        assert_eq("Language is English CHECK", ATM::English, TestATM.GetLanguage());

        assert_true("Set Language: Spanish", TestATM.SetLanguage(ATM::Spanish));
        assert_eq("Language is Spanish CHECK", ATM::Spanish, TestATM.GetLanguage());
    }

    void PinNumberValid() {
        assert_true("Pin is valid", TestATM.IsPinCorrect(1010));
        assert_false("Pin is NOT valid", TestATM.IsPinCorrect(0));
    }

    void TransTypeIsNoneByDefault() {
        assert_true("TransType defaults to None", TestATM.GetTransType() == ATM::NoTransType);
    }

    void TransactionSupport() {
        assert_true("Set TransType: Deposit", TestATM.SetTransType(ATM::Deposit)); //< Deposit and Withdraw support only
        assert_eq("TransType is Deposit CHECK", ATM::Deposit, TestATM.GetTransType());

        assert_true("Set TransType: Withdraw", TestATM.SetTransType(ATM::Withdraw));
        assert_eq("TransType is Withdraw CHECK", ATM::Withdraw, TestATM.GetTransType());
    }

    void CreditDebitIsNoneByDefault() {
        assert_true("CreditDebit defaults to None", TestATM.GetCreditDebit() == ATM::NoCreditDebit);
    }

    void CreditDebitSupport() {
        assert_true("Set CreditDebit: Checking", TestATM.SetCreditDebit(ATM::Checking)); //< Debit and Credit support only
        assert_eq("CreditDebit is Checking CHECK", ATM::Checking, TestATM.GetCreditDebit());

        assert_true("Set CreditDebit: Savings", TestATM.SetCreditDebit(ATM::Savings));
        assert_eq("CreditDebit is Savings CHECK", ATM::Savings, TestATM.GetCreditDebit());
    }

public:
    UnitTest() : suite("UnitTest") {
        add("PINNumber", testcase(this, "TestPIN", &UnitTest::PinNumberValid));

        add("LanguageDefault", testcase(this, "TestLanguage", &UnitTest::LanguageIsNoneByDefault));
        add("LanguageChanged", testcase(this, "TestLanguage", &UnitTest::EnglishSpanishSupport));

        add("TransDefault", testcase(this, "TestTransaction", &UnitTest::TransTypeIsNoneByDefault));
        add("TransChanged", testcase(this, "TestTransaction", &UnitTest::TransactionSupport));

        add("CDDefault", testcase(this, "TestCD", &UnitTest::CreditDebitIsNoneByDefault));
        add("CDChanged", testcase(this, "TestCD", &UnitTest::CreditDebitSupport));
        suite::main().add("UnitTest", this);
    }
};
UnitTest* TestCase = new UnitTest();
}
#endif
