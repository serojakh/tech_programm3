#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

class Ruble 
{
private:
    double EURRate;
    double USDRate;
    double GBPRate;
    double JPYRate;
public:
    Ruble() : EURRate(0), USDRate(0), GBPRate(0), JPYRate(0) {}

    Ruble(double EURRate, double USDRate, double GBPRate, double JPYRate)
    : EURRate(EURRate), USDRate(USDRate), GBPRate(GBPRate), JPYRate(JPYRate) {}

    Ruble(const Ruble& other)
        : EURRate(other.EURRate), USDRate(other.USDRate), GBPRate(other.GBPRate), JPYRate(other.JPYRate) {}

    void setEURRate(double EURRate)
    {
        this->EURRate = EURRate;
    }
    double getEURRate()
    {
        return EURRate;
    }

    void setUSDRate(double USDRate)
    {
        this->USDRate = USDRate;
    }
    double getUSDRate()
    {
        return USDRate;
    }

    void setGBPRate(double GBPRate)
    {
        this->GBPRate = GBPRate;
    }
    double getGBPRate()
    {
        return GBPRate;
    }

    void setJPYRate(double JPYRate)
    {
        this->JPYRate = JPYRate;
    }
    double getJPYRate()
    {
        return JPYRate;
    }

    virtual double toRUB(double amount) = 0;
    virtual double toEUR(double amount) = 0;
    virtual double toUSD(double amount) = 0;
    virtual double toGBP(double amount) = 0;
    virtual double toJPY(double amount) = 0;

    virtual ~Ruble()
    {

    }

};

class Euro : public Ruble 
{
public:
    Euro() : Ruble() {}
    Euro(double EURRate, double USDRate, double GBPRate, double JPYRate)
    : Ruble(EURRate, USDRate, GBPRate, JPYRate) {}

    double toRUB(double amount) override 
    {
        return amount * getEURRate();
    }

    double toEUR(double amount) override // из рублей в евро
    {
        return amount / getEURRate();
    }

    double toUSD(double amount) override 
    {
        return amount * getEURRate() / getUSDRate();
    }

    double toGBP(double amount) override
    {
        return amount * getEURRate() / getGBPRate();
    }

    double toJPY(double amount) override
    {
        return amount * getEURRate() / getJPYRate();
    }

    virtual ~Euro()
    {

    }
};

class Dollar : public Ruble
{
public:
    Dollar() : Ruble() {}

    Dollar(double EURRate, double USDRate, double GBPRate, double JPYRate)
    : Ruble(EURRate, USDRate, GBPRate, JPYRate) {}

    Dollar(const Dollar& other) : Ruble(other) {}

    double toRUB(double amount) override 
    {
        return amount * getUSDRate();
    }

    double toEUR(double amount) override 
    {
        return amount * getUSDRate() / getEURRate();
    }

    double toUSD(double amount) override // из рублей в доллары
    {
        return amount / getUSDRate();
    }
    
    double toGBP(double amount) override
    {
        return amount * getUSDRate() / getGBPRate();
    }

    double toJPY(double amount) override
    {
        return amount * getUSDRate() / getJPYRate();
    }

    virtual ~Dollar()
    {

    }
};

class Pound : public Ruble
{
public:
    Pound() : Ruble() {}

    Pound(double EURRate, double USDRate, double GBPRate, double JPYRate)
    : Ruble(EURRate, USDRate, GBPRate, JPYRate) {}

    Pound(const Pound& other) : Ruble(other) {}

    double toRUB(double amount) override 
    {
        return amount * getGBPRate();
    }

    double toEUR(double amount) override 
    {
        return amount * getGBPRate() / getEURRate();
    }

    double toUSD(double amount) override 
    {
        return amount * getGBPRate() / getUSDRate();
    }
    
    double toGBP(double amount) override // из рублей в фунты
    {
        return amount / getGBPRate();
    }

    double toJPY(double amount) override
    {
        return amount * getGBPRate() / getJPYRate();
    }

    virtual ~Pound()
    {

    }
};

class Yen : public Ruble
{
public:
    Yen() : Ruble() {}

    Yen(double EURRate, double USDRate, double GBPRate, double JPYRate)
    : Ruble(EURRate, USDRate, GBPRate, JPYRate) {}

    Yen(const Yen& other) : Ruble(other) {}

    double toRUB(double amount) override 
    {
        return amount * getJPYRate();
    }

    double toEUR(double amount) override 
    {
        return amount * getJPYRate() / getEURRate();
    }

    double toUSD(double amount) override 
    {
        return amount * getJPYRate() / getUSDRate();
    }
    
    double toGBP(double amount) override
    {
        return amount * getJPYRate() / getGBPRate();
    }

    double toJPY(double amount) override // из рублей в йены
    {
        return amount / getJPYRate();
    }

    virtual ~Yen()
    {

    }
};

void saveToFile(const string& filename, double amount, double euroRate, double dollarRate, double poundRate, double yenRate, string currencyto, string currencyfrom, double res) 
{
    ofstream outFile(filename);
    if (!outFile.is_open()) 
    {
        cout << "Ошибка, невозможно открыть файл " << filename << " для записи" << endl;
    }


    outFile << "Введенная сумма: " << amount << " " << currencyto << endl;
    outFile << "Введенные Вами соотношения валют: " << endl;
    outFile << "1 EUR = " << euroRate << " RUB" << endl;
    outFile << "1 USD = " << dollarRate << " RUB" << endl;
    outFile << "1 GBP = " << poundRate << " RUB" << endl;
    outFile << "1 JPY = " << yenRate << " RUB" << endl;
    outFile << "Результат работы программы: ";
    outFile << amount << " " << currencyto << " = " << res << " "<< currencyfrom;

    outFile.close();
    cout << "Данные записаны в файл " << filename << endl;
}

void loadFromFile(const string& filename, double& amount, double& EURRate, double& USDRate, double& GBPRate, double& JPYRate) 
{
    ifstream inFile(filename);
    if (!inFile.is_open()) 
    {
        cout << "Ошибка, невозможно открыть файл " << filename << " для чтения" << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) 
    {
        if (line.find("Сумма для перевода:") != string::npos)
            amount = stod(line.substr(line.find(":") + 2));
        else if (line.find("Курс Евро к Рублю:") != string::npos)
            EURRate = stod(line.substr(line.find(":") + 2));
        else if (line.find("Курс Доллара к Рублю:") != string::npos)
            USDRate = stod(line.substr(line.find(":") + 2));
        else if (line.find("Курс Фунта к Рублю:") != string::npos)
            GBPRate = stod(line.substr(line.find(":") + 2));
        else if (line.find("Курс Йены к Рублю:") != string::npos)
            JPYRate = stod(line.substr(line.find(":") + 2));
    }

    inFile.close();
    cout << "Данные были загружены из файла " << filename << endl;
}

int main() 
{
    double amount = 0;
    double EURRate, USDRate, GBPRate, JPYRate;
    int choice;
    double res;
    string currencyfrom, currencyto, filename;

    while (true)
    {
       cout << "--Меню--" << endl;
        cout << "1. Ввести данные вручную" << endl;
        cout << "2. Загрузить данные из файла" << endl;
        cout << "3. Конвертировать валюту" << endl;
        cout << "4. Сохранить данные в файл" << endl;
        cout << "5. Выход" << endl;
        cout << "Введите номер желаемого действия: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Введите сумму: ";
            cin >> amount;
            cout << "Введите курс Евро к Рублю: ";
            cin >> EURRate;
            cout << "Введите курс Доллара к Рублю: ";
            cin >> USDRate;
            cout << "Введите курс Фунта к Рублю: ";
            cin >> GBPRate;
            cout << "Введите курс Йены к Рублю: ";
            cin >> JPYRate;
            cout << "Данные успешно сохранены" << endl;
        }

        else if (choice == 2)
        {
            cout << "Введите имя файла для загрузки: ";
            cin >> filename;
            loadFromFile(filename, amount, EURRate, USDRate, GBPRate, JPYRate);
            cout << "Данные, полученные из файла:" << endl;
            cout << "Сумма: " << amount << endl;
            cout << "Курс Евро к Рублю: " << EURRate << endl;
            cout << "Курс Доллара к Рублю: " << USDRate << endl;
            cout << "Курс Фунта к Рублю: " << GBPRate << endl;
            cout << "Курс Йены к Рублю: " << JPYRate << endl;
        }

        else if (choice == 3)
        {
            string from;
            cout << "---Конвертировать из---" << endl;
            cout << "RUB - Рублей" << endl;
            cout << "EUR - Евро" << endl;
            cout << "USD - Долларов" << endl;
            cout << "GBP - Фунтов" << endl;
            cout << "JPY - Йен" << endl;
            cin >> from;

            string to;
            cout << "---В---" << endl;
            cout << "RUB - Рубли" << endl;
            cout << "EUR - Евро" << endl;
            cout << "USD - Доллары" << endl;
            cout << "GBP - Фунты" << endl;
            cout << "JPY - Йены" << endl;
            cin >> to;
            
            
            if (from == "RUB") 
            {
                currencyfrom = "RUB";
                if (to == "EUR")
                {
                    currencyto = "EUR";
                    Euro re(EURRate, USDRate, GBPRate, JPYRate);
                    res = re.toEUR(amount);
                    cout << amount << " RUB = " << res << " EUR" << endl;
                }

                else if (to == "USD") 
                {
                    currencyto = "USD";
                    Dollar rd(EURRate, USDRate, GBPRate, JPYRate);
                    res = rd.toUSD(amount);
                    cout << amount << " RUB = " << res << " USD" << endl;
                }

                else if (to == "GBP") 
                {
                    currencyto = "GBP";
                    Pound rp(EURRate, USDRate, GBPRate, JPYRate);
                    res = rp.toGBP(amount);
                    cout << amount << " RUB = " << res << " GBP" << endl;
                }

                else if (to == "JPY") 
                {
                    currencyto = "JPY";
                    Yen ry(EURRate, USDRate, GBPRate, JPYRate);
                    res = ry.toJPY(amount);
                    cout << amount << " RUB = " << res << " JPY" << endl;
                }
            }

            else if (from == "EUR") 
            {
                currencyfrom = "EUR";
                Euro e(EURRate, USDRate, GBPRate, JPYRate);
                if (to == "RUB")
                {
                    currencyto = "RUB";
                    res = e.toRUB(amount);
                    cout << amount << " EUR = " << res << " RUB" << endl;
                }

                else if (to == "USD")
                {
                    currencyto = "USD";
                    res = e.toUSD(amount);
                    cout << amount << " EUR = " << res << " USD" << endl;
                }

                else if (to == "GBP") 
                {
                    currencyto = "GBP";
                    res = e.toGBP(amount);
                    cout << amount << " EUR = " << res << " GBP" << endl;
                }

                else if (to == "JPY") 
                {
                    currencyto = "JPY";
                    res = e.toJPY(amount);
                    cout << amount << " EUR = " << res << " JPY" << endl;
                }
            }

            else if (from == "USD") 
            {
                currencyfrom = "USD";
                Dollar d(EURRate, USDRate, GBPRate, JPYRate);
                if (to == "RUB")
                {
                    currencyto = "RUB";
                    res = d.toRUB(amount);
                    cout << amount << " USD = " << res << " RUB" << endl;
                }

                else if (to == "EUR") 
                {
                    currencyto = "EUR";
                    res = d.toEUR(amount);
                    cout << amount << " USD = " << res << " EUR" << endl;
                }

                else if (to == "GBP") 
                {
                    currencyto = "GBP";
                    res = d.toGBP(amount);
                    cout << amount << " USD = " << res << " GBP" << endl;
                }

                else if (to == "JPY") 
                {
                    currencyto = "JPY";
                    res = d.toJPY(amount);
                    cout << amount << " USD = " << res << " JPY" << endl;
                }
            }

            else if (from == "GBP") 
            {
                currencyfrom = "GBP";
                Pound p(EURRate, USDRate, GBPRate, JPYRate);
                if (to == "RUB")
                {
                    currencyto = "RUB";
                    res = p.toRUB(amount);
                    cout << amount << " GBP = " << res << " RUB" << endl;
                }

                else if (to == "EUR") 
                {
                    currencyto = "EUR";
                    res = p.toEUR(amount);
                    cout << amount << " GBP = " << res << " EUR" << endl;
                }

                else if (to == "USD") 
                {
                    currencyto = "USD";
                    res = p.toUSD(amount);
                    cout << amount << " GBP = " << res << " USD" << endl;
                }

                else if (to == "JPY") 
                {
                    currencyto = "JPY";
                    res = p.toJPY(amount);
                    cout << amount << " GBP = " << res << " JPY" << endl;
                }
            }

            else if (from == "JPY") 
            {
                currencyfrom = "JPY";
                Yen y(EURRate, USDRate, GBPRate, JPYRate);
                if (to == "RUB")
                {
                    currencyto = "RUB";
                    res = y.toRUB(amount);
                    cout << amount << " JPY = " << res << " RUB" << endl;
                }

                else if (to == "EUR") 
                {
                    currencyto = "EUR";
                    res = y.toEUR(amount);
                    cout << amount << " JPY = " << res << " EUR" << endl;
                }

                else if (to == "USD") 
                {
                    currencyto = "USD";
                    res = y.toUSD(amount);
                    cout << amount << " JPY = " << res << " USD";
                }

                else if (to == "GBP") 
                {
                    currencyto = "GBP";
                    res = y.toJPY(amount);
                    cout << amount << " JPY = " << res << " GBP";
                }
            }
        }

        else if (choice == 4)
        {
            cout << "Введите имя файла для сохранения: ";
            cin >> filename;
            saveToFile(filename, amount, EURRate, USDRate, GBPRate, JPYRate, currencyfrom, currencyto, res);
        }
        

        else if (choice == 5)
        {
            cout << "Выход из программы" << endl;
            break;
        }
            
        else if ((choice < 1) || (choice > 5))
        {
            cout << "Такого действия нет, попробуйте еще раз" << endl;
            continue;
        }   
    }
    return 0;
}