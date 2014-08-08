#include "atm.h"

using namespace std;

/** Driver function */
int main()
{
    ATM myObj;
    Menu myMenu(myObj);

    myMenu.Display(Menu::Lang);
    return 0;
}

/** Uses switch to navigate from the CurrentPage used to the end */
bool Menu::Display(const MenuType& CurrentPage)
{
    bool _continue = false;

    switch (CurrentPage) {
/////////////////////////////////////////////////////////////////////
    case Lang:
        while(!_continue) {
            wcout << LocalizeString(Lang) << endl;

            int UserInput;
            cin >> UserInput;
            wcout << endl;

            if(cin.fail()) {
                cin.clear();
                cin.ignore();
                continue;
            }

            switch (UserInput) {
            case 1:
                m_ATM.SetLanguage(ATM::English);
                _continue = true;
                break;
            case 2:
                m_ATM.SetLanguage(ATM::Spanish);
                _continue = true;
                break;
            default:
                cout << endl;
            }
        };

/////////////////////////////////////////////////////////////////////
    case PIN:
        int UserPIN;
        while(!m_ATM.IsPinCorrect(UserPIN)) {
            wcout << LocalizeString(PIN) << endl;
            cin >> UserPIN;
            wcout << endl;

            if(cin.fail()) {
                cin.clear();
                cin.ignore();
                continue;
            }

            if(UserPIN == 0) {
                return Cancel();
            }
        };

        wcout << LocalizeString(ShowBalance) << endl;

/////////////////////////////////////////////////////////////////////
    case CreditDebit:
        _continue = false;

        while(!_continue) {
            wcout << LocalizeString(CreditDebit) << endl;

            int UserInput;
            cin >> UserInput;
            cout << endl;

            if(cin.fail()) {
                cin.clear();
                cin.ignore();
                continue;
            }

            switch (UserInput) {
            case 0:
                return Cancel();
            case 1:
                m_ATM.SetCreditDebit(ATM::Checking);
                _continue = true;
                break;
            case 2:
                m_ATM.SetCreditDebit(ATM::Savings);
                _continue = true;
                break;
            default:
                cout << endl;
            }
        };

/////////////////////////////////////////////////////////////////////
    case AddOrSub:
        _continue = false;

        while(!_continue) {
            wcout << LocalizeString(AddOrSub) << endl;

            int UserInput;
            cin >> UserInput;
            cout << endl;

            if(cin.fail()) {
                cin.clear();
                cin.ignore();
                continue;
            }

            switch (UserInput) {
            case 0:
                return Cancel();
            case 1:
                m_ATM.SetTransType(ATM::Deposit);
                _continue = true;
                break;
            case 2:
                m_ATM.SetTransType(ATM::Withdraw);
                _continue = true;
                break;
            default:
                break;
            }
        };

/////////////////////////////////////////////////////////////////////
    case Amount:
        _continue = false;

        while(!_continue) {
            wcout << LocalizeString(Amount) << endl;

            int UserInput;
            cin >> UserInput;
            wcout << endl;

            if(cin.fail()) {
                cin.clear();
                cin.ignore();
                continue;
            }

            Money UserAmount;
            switch (UserInput) {
            case 0: //< Cancel
                return Cancel();
            case 1: //< $10
                UserAmount = 10.00;
                break;
            case 2: //< $20
                UserAmount = 20.00;
                break;
            case 3: //< $50
                UserAmount = 50.00;
                break;
            case 4: //< $100
                UserAmount = 100.00;
                break;
            case 5: //< Custom
                while(true) {
                    wcout << "$";
                    cin >> UserAmount;

                    if(cin.fail()) {
                        cin.clear();
                        cin.ignore();
                        continue;
                    }

                    if(UserAmount == 0) {
                        wcout << endl;
                        return Display(Amount);
                    } else {
                        break;
                    }
                };

                break;
            }

            unsigned int TransValid;
            TransValid = m_ATM.ValidateTransaction(UserAmount);
            switch (TransValid) {
            case -1:
                if(GetLang() == ATM::English) {
                    wcout << "Transaction Error: You may only withdraw up to $500 per day! Please try again or press 0 to go back" << endl << endl;
                }
                if(GetLang() == ATM::Spanish) {
                    wcout << "Error Transacción: Usted sólo puede retirar hasta $ 500 por día! Por favor inténtelo de nuevo o pulse 0 para volver" << endl << endl;
                }
                break;

            case -2:
                if(GetLang() == ATM::English) {
                    wcout << "Insufficient funds" << endl << endl;
                }
                if(GetLang() == ATM::Spanish) {
                    wcout << "La insuficiencia de fondos" << endl << endl;
                }
                break;

            case -3:
                if(GetLang() == ATM::English) {
                    wcout << "Value must be at least $0.01" << endl << endl;
                }
                if(GetLang() == ATM::Spanish) {
                    wcout << "El valor debe ser de al menos $0.01" << endl << endl;
                }
                break;
            }

            if(TransValid == 0) {
                m_ATM.DoTransaction(UserAmount);
                break;
            }
        };

/////////////////////////////////////////////////////////////////////
    case ShowBalance:
        wcout << LocalizeString(ShowBalance) << endl;

/////////////////////////////////////////////////////////////////////
    case Retry:
        while(true) {
            wcout << LocalizeString(Retry) << endl;

            int UserInput;
            cin >> UserInput;
            cout << endl;

            if(cin.fail()) {
                cin.clear();
                cin.ignore();
                continue;
            }

            switch (UserInput) {
            case 1:
                return Display(CreditDebit);
            case 0:
                return Display(End);
            }
        };

/////////////////////////////////////////////////////////////////////
    case End:
        wcout << LocalizeString(End) << endl;
        break;
    }

    return true;
}

/** Outputs a localized string for the given page */
const wchar_t* Menu::LocalizeString(const MenuType &CurrentPage)
{
    wostringstream OutputBalance;

    switch (CurrentPage) {
    case Lang:
        return L"Press 1 for English\nPresione 2 para Español";
    case PIN:
        if(GetLang() == ATM::English) {
            return L"Please enter your PIN number";
        }
        if(GetLang() == ATM::Spanish) {
            return L"Por favor, introduzca su número de PIN";
        }
    case CreditDebit:
        if(GetLang() == ATM::English) {
            return L"Press 1 for Checking\nPress 2 for Savings\nPress 0 to Cancel";
        }
        if(GetLang() == ATM::Spanish) {
            return L"Presione 1 para su comprobación\nPresione 2 para el Ahorro\nPulse 0 para Cancelar.";
        }
    case AddOrSub:
        if(GetLang() == ATM::English) {
            return L"Press 1 for Deposit\nPress 2 for Withdraw\nPress 0 to Cancel";
        }
        if(GetLang() == ATM::Spanish) {
            return L"Presione 1 para el Depósito\nPresione 2 para el Retiro\nPulse 0 para Cancelar";
        }
    case Amount:
        if(GetLang() == ATM::English) {
            return L"Press 1 for $10\nPress 2 for $20\nPress 3 for $50\nPress 4 for $100\nPress 5 for custom amount\nPress 0 to Cancel";
        }
        if(GetLang() == ATM::Spanish) {
            return L"Pulse 1 por $10\nPulse 2 por $20\nPulse 3 por $50\nPulse 4 por $100\nPulse 5 para la cantidad medida\nPulse 0 para cancelar";
        }

    case ShowBalance:
        OutputBalance.str(L""); //< Clear balance before display

        if(GetLang() == ATM::English) {
            OutputBalance << "Account Details" << endl;
            OutputBalance << "Checking Account Balance: " << m_ATM.GetBalance(ATM::Checking) << endl;
            OutputBalance << "Savings Account Balance: " << m_ATM.GetBalance(ATM::Savings) << endl;
        }
        if(GetLang() == ATM::Spanish) {
            OutputBalance << "Detalles de la Cuenta" << endl;
            OutputBalance << "Controlar el balance de la cuenta: " << m_ATM.GetBalance(ATM::Checking) << endl;
            OutputBalance << "Ahorro Saldo de la cuenta: " << m_ATM.GetBalance(ATM::Savings) << endl;
        }
        return OutputBalance.str().c_str();
    case Retry:
        if(GetLang() == ATM::English) {
            return L"Press 1 to make another transaction\nPress 0 to Exit";
        }
        if(GetLang() == ATM::Spanish) {
            return L"Presione 1 para hacer otra transacción\nPulse 0 para la salida";
        }
    case End:
        if(GetLang() == ATM::English) {
            return L"Thank you, have a nice day!";
        }
        if(GetLang() == ATM::Spanish) {
            return L"Muchas gracias, tenga un buen día!";
        }
    }

    return L"";
}

