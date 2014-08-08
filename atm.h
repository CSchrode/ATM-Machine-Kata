#ifndef ATM_H
#define ATM_H
#include <iostream>
#include <sstream>

typedef double Money;

/** API used by the menu-system */
class ATM
{
public:
    /** Type definitions */
    enum Language {
        NoLanguage,
        English,
        Spanish
    };

    enum TransType {
        NoTransType,
        Deposit,
        Withdraw
    };

    enum CreditDebit {
        NoCreditDebit,
        Savings,
        Checking
    };

protected:
    /** Data members */
    Language m_LangUsed;
    TransType m_TransUsed;
    CreditDebit m_CreditDebit;
    Money m_CheckAccBalance;
    Money m_SavingsAccBalance;
    Money m_WithdrawTotal;

public:
    /** Default c-tor */
    ATM() : m_CheckAccBalance(3230.00), m_SavingsAccBalance(6000.00) {}

    /** Language getter */
    Language GetLanguage() {
        return m_LangUsed;
    }
    /** Language setter */
    inline bool SetLanguage(const Language &UserInput) {
        return (m_LangUsed = UserInput);
    }

    /** Returns balance */
    inline Money GetBalance(ATM::CreditDebit Transaction) {
        if(Transaction == Savings) {
            return m_SavingsAccBalance;
        }

        if(Transaction == Checking) {
            return m_CheckAccBalance;
        }

        return 0;
    }

    /** Pin Number == 1010 */
    inline bool IsPinCorrect(const int &UserInput) {
        return UserInput == 1010;
    }

    /** Transaction getter */
    TransType GetTransType() {
        return m_TransUsed;
    }
    /** Transaction setter */
    inline bool SetTransType(const TransType &UserInput) {
        return (m_TransUsed = UserInput);
    }

    /** Credit/Debit getter */
    CreditDebit GetCreditDebit() {
        return m_CreditDebit;
    }
    /** Credit/Debit setter */
    inline bool SetCreditDebit(const CreditDebit &UserInput) {
        return (m_CreditDebit = UserInput);
    }

    /** Validation of user input */
    unsigned int ValidateTransaction(const Money &UserInput) {

        if(GetTransType() == Withdraw) {
            //< Not enough in account
            if(UserInput > GetBalance(GetCreditDebit())) {
                return -2;
            }

            //< Over the daily withdraw limit
            if((m_WithdrawTotal + UserInput) > 500.00) {
                return -1;
            }
        }

        //< Negative input
        if(UserInput < 0.00) {
            return -3;
        }

        //< Successful
        return 0;
    }

    /** Performs the transaction which has been setup */
    bool DoTransaction(const Money &UserInput) {
        //< Handle deposit
        if(GetTransType() == Deposit) {
            if(GetCreditDebit() == Savings) {
                m_SavingsAccBalance += UserInput;
            }

            if(GetCreditDebit() == Checking) {
                m_CheckAccBalance += UserInput;
            }

            return true;
        }

        //< Handle Withdraw
        if(GetTransType() == Withdraw) {

            m_WithdrawTotal += UserInput;

            if(GetCreditDebit() == Savings) {
                m_SavingsAccBalance -= UserInput;
            }

            if(GetCreditDebit() == Checking) {
                m_CheckAccBalance -= UserInput;
            }

            return true;
        }

        return false;
    }
};

/** Menu System */
class Menu
{
public:
    /** Data Type: different phases of the menu's lifecycle */
    enum MenuType {
        Lang,
        PIN,
        CreditDebit,
        AddOrSub,
        Amount,
        ShowBalance,
        Retry,
        End
    };

protected:
    /** Data members, inherited by Menu additions */
    ATM m_ATM;

public:
    /** ATM has-a menu, using Composite pattern */
    Menu(ATM &AdaptedATM) : m_ATM(AdaptedATM) {}

    /** Language getter */
    ATM::Language GetLang() {
        return m_ATM.GetLanguage();
    }

    /** Menu Controller */
    bool Display(const MenuType& CurrentPage);

    /** Allows Cancel for each menu more easily */
    inline bool Cancel() {
        return Display(Retry);
    }

    /** Handles conversion of text from English to Spanish */
    const wchar_t* LocalizeString(const MenuType &CurrentPage);
};

#endif // ATM_H
