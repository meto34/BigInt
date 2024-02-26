
#include <iostream>

const unsigned int MaxUn = 4294967295;
const int MaxIntSize = 10;


class BigInteger {
private:
    unsigned int* data_;
    long long size_;
    bool isPositive_ = true;

public:

    BigInteger();  // инициализация по умолчанию 0
    ~BigInteger();
    BigInteger(const std::string& str);
    BigInteger(const char*);
    BigInteger(int num);
    BigInteger(const BigInteger& num);
    BigInteger(unsigned int num);
    BigInteger(unsigned long int num);
    BigInteger(long int num);
    BigInteger(long long int num);
    BigInteger(unsigned long long int num);
    BigInteger(BigInteger& copy);  // Конструктор копирования
    BigInteger(BigInteger&& moved) noexcept;  // конструктор перемещения

    BigInteger& operator=(
        const BigInteger& copy);  // оператор присваивания копированием
    BigInteger operator=(
        BigInteger&& moved) noexcept;  // оператор присваивания перемещением
    bool operator==(const BigInteger& num) const;
    bool operator!=(const BigInteger& num) const;
    bool operator>(const BigInteger& num) const;
    bool operator<=(const BigInteger& num) const;
    bool operator>=(const BigInteger& num) const;
    bool operator<(const BigInteger& num) const;

    BigInteger& sum(const BigInteger& num);
    BigInteger& dif(const BigInteger& num);  // Функция подразумевает num >= *this
    void DelZeros();
    void AddZeros(long long);
    BigInteger& operator+=(const BigInteger& num);
    BigInteger operator+(const BigInteger& num);
    BigInteger& operator-=(const BigInteger& num);
    BigInteger operator-(const BigInteger& num);
    BigInteger operator-();  // унарный минус
    BigInteger operator+();  // унарный плюс
    BigInteger& operator--();
    BigInteger& operator++();
    BigInteger abs() const;
    long long GetSize() const;
    bool GetSign() const;
    unsigned int GetData(long long i) const;
    BigInteger& operator*=(const BigInteger&);
    BigInteger& operator/=(const BigInteger&);
    BigInteger operator*(const BigInteger& num);
    BigInteger operator/(const BigInteger& num);
    BigInteger& operator%=(const BigInteger& num);
    BigInteger operator%(const BigInteger& num);
    BigInteger operator--(int);
    BigInteger operator++(int);
};

bool isNumber(char num);
unsigned int StrDiv(std::string& str);
std::string to_string(const BigInteger& num);
std::string SumStr(const std::string&, const std::string&);
std::string MultyStr(const std::string&, const std::string&);
std::string ZeroErase(std::string result);
unsigned long long ProcessingLongStr(unsigned long long& num,
    std::string& str);
unsigned long long str2num(std::string& str, long long i);

BigInteger operator+(int, const BigInteger&);
BigInteger operator-(int, const BigInteger&);
BigInteger operator*(int, const BigInteger&);
BigInteger operator/(int, const BigInteger&);
bool operator==(int, const BigInteger&);

bool IsInt(char ch);
std::string implementationOfSum(std::string& min, std::string& max, std::string& tmp);
std::string reverse(std::string& tmp);
