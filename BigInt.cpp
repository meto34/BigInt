#include "BigInt.h"

BigInteger::BigInteger(const std::string& st) {
    if (st.empty()) {
        throw std::invalid_argument("empty input");
    }
    std::string str = st;
    if (str[0] == '-') {
        isPositive_ = false;
        str.erase(0, 1);
    }
    if (str.empty()) {
        throw std::invalid_argument("empty input");
    }
    for (size_t i = 0; i < str.size(); ++i) {
        if (!isNumber(str[i])) {
            throw std::invalid_argument("Incorrect input: !isNumber");
        }
    }
    int ers = 0;
    while (str[0] == '0' && str.size() > 1) {
        ++ers;
    }
    str.erase(0, ers);
    if (str[0] == '0') {
        isPositive_ = true;
        size_ = 1;
        data_ = new unsigned int[size_];
        data_[0] = 0;
        return;
    }
    while (str != "0") {
        StrDiv(str);
        ++size_;
    }
    data_ = new unsigned int[size_];
    str = st;
    if (str[0] == '-') {
        str.erase(0, 1);
        isPositive_ = false;
    }
    for (long long i = 0; i < size_; ++i) {
        data_[i] = StrDiv(str);
    }
}
BigInteger::BigInteger(const char* num) {
    std::string result;
    result = num;

}

BigInteger::BigInteger() {
    size_ = 1;
    isPositive_ = true;
    data_ = new unsigned int[size_];
    data_[0] = 0;
}
BigInteger::~BigInteger() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    isPositive_ = true;
}
BigInteger::BigInteger(int num) {
    size_ = 1;
    data_ = new unsigned int[size_];
    if (num < 0) {
        isPositive_ = false;
        num = -(num);
    }
    else {
        isPositive_ = true;
    }
    data_[0] = num;
}
BigInteger::BigInteger(const BigInteger& num) {
    size_ = num.size_;
    isPositive_ = num.isPositive_;
    data_ = new unsigned int[size_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = num.data_[i];
    }
}

BigInteger::BigInteger(unsigned int num) {
    size_ = 1;
    data_ = new unsigned int[size_];
    data_[0] = num;
}

BigInteger::BigInteger(unsigned long num) {
    size_ = 1;
    data_ = new unsigned int[size_];
    data_[0] = num;
}

BigInteger::BigInteger(long num)
{
    if (num < 0) {
        isPositive_ = false;
        num *= -1;
    }
    size_ = 1;
    data_ = new unsigned int[size_];
    data_[0] = num;
}
BigInteger::BigInteger(long long int num) {
    if (num < 0) {
        isPositive_ = false;
        num = -(num);
    }

    if (num > MaxUn) {
        size_ = 2;
        data_ = new unsigned int[size_];
        data_[0] = num % MaxUn;
        data_[1] = (num / MaxUn);
    }
    else {
        size_ = 1;
        data_ = new unsigned int[size_];
        data_[0] = num;  // num % MaxUn
    }
}

BigInteger::BigInteger(unsigned long long int num) {
    if ((num / MaxUn) != 0) {
        size_ = 2;
    }
    else {
        size_ = 1;
    }
    data_ = new unsigned int[size_];
    data_[0] = num % MaxUn;
    if (size_ == 2) {
        data_[1] = (num / MaxUn);
    }
}

BigInteger::BigInteger(BigInteger& copy) {
    size_ = copy.size_;
    data_ = new unsigned int[size_];
    for (unsigned long long i = 0; i < size_; ++i) {
        data_[i] = copy.data_[i];
    }
}
BigInteger::BigInteger(BigInteger&& moved) noexcept {
    size_ = moved.size_;
    isPositive_ = moved.isPositive_;
    data_ = moved.data_;
    moved.data_ = nullptr;
    moved.size_ = 0;
    moved.isPositive_ = true;
}
BigInteger& BigInteger::operator=(const BigInteger& copy) {
    if (&copy != this) {  // избегаем самоприсваивания
        isPositive_ = copy.isPositive_;
        delete[] data_;
        size_ = copy.size_;
        data_ = new unsigned int[size_];
        for (long long i = 0; i < size_; ++i) {
            data_[i] = copy.data_[i];
        }
    }
    return *this;
}
BigInteger BigInteger::operator=(BigInteger&& moved) noexcept {
    if (&moved != this)  // избегаем самоприсваивания
    {
        delete[] data_;
        data_ = moved.data_;
        size_ = moved.size_;
        moved.data_ = nullptr;
        moved.size_ = 0;
        moved.isPositive_ = true;
    }
    return *this;
}
bool BigInteger::operator==(const BigInteger& num) const {
    if (isPositive_ != num.isPositive_) {
        return false;
    }
    if (size_ != num.size_) {
        return false;
    }
    for (unsigned long long i = 0; i < size_; ++i) {
        if (data_[i] != num.data_[i]) {
            return false;
        }
    }
    return true;
}
bool BigInteger::operator!=(const BigInteger& num) const {
    return !(*this == num);
}

bool BigInteger::operator>(const BigInteger& num) const {
    if (isPositive_ != num.isPositive_) {
        return isPositive_;
    }
    if (isPositive_) {
        if (size_ > num.size_) {
            return true;
        }
        if (size_ < num.size_) {
            return false;
        }
        for (unsigned long long i = size_; i > 0; --i) {  // положительные
                                                          // числа
            if (data_[i - 1] < num.data_[i - 1]) {
                return false;
            }
            if (data_[i - 1] > num.data_[i - 1]) {
                return true;
            }
        }
    }
    else {  // сравнение отрицательных
        if (size_ > num.size_) {
            return false;
        }
        if (size_ < num.size_) {
            return true;
        }
        for (unsigned long long i = size_ - 1; i > 0; --i) {
            if (data_[i - 1] > num.data_[i - 1]) {
                return false;
            }
            if (data_[i - 1] < num.data_[i - 1]) {
                return true;
            }
        }
    }
    return false;  // числа равны
}
bool BigInteger::operator<=(const BigInteger& num) const {
    return !(*this > num);
}
bool BigInteger::operator>=(const BigInteger& num) const {
    return (*this > num || *this == num);
}
bool BigInteger::operator<(const BigInteger& num) const {
    return !(*this > num || *this == num);
}

BigInteger& BigInteger::sum(const BigInteger& num) {
    long long ts;
    if (size_ > num.size_) {
        ts = size_ + 1;
    }
    else {
        ts = num.size_ + 1;
    }
    BigInteger copy(num);
    unsigned int* tmp = new unsigned int[ts];
    unsigned long long remains = 0;
    if (copy.size_ > size_) {
        AddZeros(copy.size_ - size_ + 1);
        copy.AddZeros(1);
    }
    else {
        copy.AddZeros(size_ - copy.size_ + 1);
        AddZeros(1);
    }
    for (long long i = 0; i < ts; ++i) {
        tmp[i] = 0;
    }
    for (long long i = 0; i < ts; ++i) {
        remains += (unsigned long long)data_[i] + copy.data_[i];
        tmp[i] = remains % MaxUn;
        remains /= MaxUn;
    }
    size_ = ts;
    delete[] data_;
    data_ = new unsigned int[size_];
    for (long long i = 0; i < size_; ++i) {
        data_[i] = tmp[i];
    }
    delete[] tmp;
    DelZeros();
    return *this;
}

BigInteger& BigInteger::dif(const BigInteger& num) {
    unsigned int* tmp = new unsigned int[num.size_];
    long long buf = 0;
    AddZeros(num.size_ - size_);
    for (long long i = 0; i < num.size_; ++i) {
        tmp[i] = 0;
    }
    for (long long i = 0; i < num.size_; ++i) {
        buf = (long long)num.data_[i] - data_[i] - buf;
        if (buf < 0) {
            tmp[i] = (buf + MaxUn);
        }
        else {
            tmp[i] = buf;
        }
        if (buf > 0) {
            buf = 0;
        }
        else {
            buf = 1;
        }
    }
    size_ = num.size_;
    for (long long i = 0; i < size_; ++i) {
        data_[i] = tmp[i];
    }
    DelZeros();
    delete[] tmp;
    return *this;
}

bool isNumber(char num) { return ((num <= '9') && (num >= '0')); }
void BigInteger::DelZeros() {
    long long i = size_ - 1;
    while (data_[i] == 0) {
        --i;
    }
    if (i < size_ - 1) {
        unsigned int* tmp = new unsigned int[++i];
        for (long long j = 0; j < i; ++j) {
            tmp[j] = data_[j];
        }
        delete[] data_;
        size_ = i;
        data_ = new unsigned int[size_];
        for (long long j = 0; j < size_; ++j) {
            data_[j] = tmp[j];
        }
        delete[] tmp;
    }
}

void BigInteger::AddZeros(long long count) {
    if (count > 0) {
        unsigned int* tmp = new unsigned int[size_ + count];
        for (long long i = 0; i < size_; ++i) {
            tmp[i] = data_[i];
        }
        for (size_t i = size_; i < size_ + count; ++i) {
            tmp[i] = 0;
        }
        size_ += count;
        delete[] data_;
        data_ = new unsigned int[size_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = tmp[i];
        }
        delete[] tmp;
    }
}

BigInteger& BigInteger::operator+=(const BigInteger& num) {
    if (isPositive_ == num.isPositive_) {
        sum(num);
    }
    else if (-*this == num) {
        *this = 0;
    }
    else {
        BigInteger copy(num);
        if (isPositive_) {
            if (*this < -copy) {
                dif(copy);
                isPositive_ = false;
            }
            else {
                copy.dif(*this);
                copy.isPositive_ = true;
                *this = copy;
            }
        }
        else {
            if (-*this <= num) {
                dif(num);
                isPositive_ = true;
            }
            else {
                copy.dif(*this);
                copy.isPositive_ = false;
                *this = copy;
            }
        }
    }
    return *this;
}
BigInteger BigInteger::operator+(const BigInteger& num) {
    BigInteger tmp(*this);
    tmp += num;
    return tmp;
}

BigInteger& BigInteger::operator-=(const BigInteger& num) {
    if (*this == num) {
        *this = BigInteger(0);
    }
    else if (isPositive_ != num.isPositive_) {
        sum(num);
    }
    else {
        BigInteger copy(num);
        if (isPositive_) {
            if (*this < copy) {
                dif(copy);
                isPositive_ = false;
            }
            else {
                copy.dif(*this);
                copy.isPositive_ = true;
                *this = copy;
            }
        }
        else {
            if (*this > copy) {  // знак в другую сторону, так как сравниваем два
                                 // отрицательных числа
                dif(copy);
                isPositive_ = true;
            }
            else {
                copy.dif(*this);
                copy.isPositive_ = false;
                *this = copy;
            }
        }
    }
    return *this;
}

BigInteger BigInteger::operator-(const BigInteger& num) {
    BigInteger tmp(*this);
    tmp -= num;
    return tmp;
}
BigInteger BigInteger::operator+() { return *this; }

BigInteger BigInteger::operator-() {
    if (*this == 0) {
        return *this;
    }
    isPositive_ = !(isPositive_);
    return *this;
}

BigInteger& BigInteger::operator--() { return (*this -= 1); }
BigInteger& BigInteger::operator++() { return (*this += 1); }

BigInteger BigInteger::abs() const {
    BigInteger num(*this);
    num.isPositive_ = true;
    return num;
}

unsigned int StrDiv(std::string& str) {
    if (str.empty() || str == "0") {
        str = "0";
        return 0;
    }
    unsigned long long num = 0;
    int length = 0;
    if (str.size() > MaxIntSize) {
        length = MaxIntSize;
    }
    else {
        length = (int)str.size();
    }
    num = str2num(str, length);
    bool flag = false;
    if ((str.size() < MaxIntSize) ||
        ((str.size() == MaxIntSize) && (num < MaxUn))) {
        str = "0";
    }
    else if (str.size() == MaxIntSize) {
        str = std::to_string(num / MaxUn);
        flag = true;
    }
    else {
        ProcessingLongStr(num, str);
    }
    if (flag) {
        return (unsigned int)(num % MaxUn);
    }
    return (unsigned int)(num);
}

unsigned long long ProcessingLongStr(unsigned long long& num,
    std::string& str) {
    std::string result;
    unsigned long long remains = num / MaxUn;
    if (remains != 0) {
        result.push_back(char(remains + '0'));
    }
    num = (num % MaxUn) * 10 + (str[MaxIntSize]) - '0';
    for (size_t i = MaxIntSize + 1; i < str.size(); ++i) {
        remains = num / MaxUn;
        result.push_back(char(remains + '0'));
        num = (num % MaxUn) * 10 + (str[i] - '0');
    }
    remains = num / MaxUn;
    result.push_back(char(remains + '0'));
    str = result;
    num %= MaxUn;
    return num;
}

unsigned long long str2num(std::string& str, long long i) {
    unsigned long long digit = 0;
    unsigned int index = 0;
    while (str[index] != 0 && index < i) {
        digit = digit * 10 + (unsigned long long)(str[index] - '0');
        ++index;
    }
    return digit;
}

long long BigInteger::GetSize() const { return size_; }

bool BigInteger::GetSign() const { return isPositive_; }

BigInteger& BigInteger::operator*=(const BigInteger& num) {
    long long ts = num.size_ + size_;
    unsigned int* tmp = new unsigned int[ts];
    unsigned long long buf = 0;
    for (long long i = 0; i < ts; ++i) {
        tmp[i] = 0;
    }
    for (long long i = 0; i < num.size_; ++i) {
        if (num.data_[i] != 0) {
            buf = 0;
            for (long long j = 0; j < size_; ++j) {
                buf += (unsigned long long)data_[j] * num.data_[i] +
                    (unsigned long long)tmp[i + j];
                tmp[i + j] = buf % MaxUn;
                buf /= MaxUn;
            }
            tmp[i + size_] = (unsigned int)buf;
        }
    }
    size_ = ts;
    delete[] data_;
    data_ = new unsigned int[size_];
    for (long long i = 0; i < size_; ++i) {
        data_[i] = tmp[i];
    }
    DelZeros();
    isPositive_ = ((isPositive_ xor num.isPositive_) == 0);
    delete[] tmp;
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& num) {
    if (BigInteger(0) == num) {
        throw std::invalid_argument("Error: Divide by zero");
    }
    isPositive_ = ((isPositive_ xor num.isPositive_) == 0);
    if (abs() < num.abs()) {
        *this = BigInteger(0);
        return *this;
    }
    if (abs() == num.abs()) {
        *this = BigInteger(1);
        return *this;
    }
    if (num.size_ == 1) {
        unsigned int* tmp = new unsigned int[size_];
        for (size_t i = 0; i < size_; ++i) {
            tmp[i] = 0;
        }
        unsigned long long buf = 0;
        unsigned long long lt = num.data_[0];
        for (long long j = size_ - 1; j >= 0; --j) {
            tmp[j] = ((buf * MaxUn + data_[(size_t)j]) / lt);
            buf = (buf * MaxUn + data_[(size_t)j]) % lt;
        }
        for (long long i = 0; i < size_; ++i) {
            data_[i] = tmp[i];
        }
        DelZeros();
        delete[] tmp;
        return *this;
    }

    long long rs = size_ - num.size_ + 1;
    unsigned int* result = new unsigned int[rs];
    BigInteger copy(num);

    long long d = MaxUn / (copy.data_[copy.size_ - 1] + 1);
    *this *= d;
    AddZeros(1);
    copy *= d;

    unsigned long long qHat = 0;
    unsigned long long rHat = 0;
    unsigned long long tmp2 = 0;
    unsigned long long smth = 0;
    int remains = 0;

    for (long long j = rs - 1; j >= 0; --j) {
        qHat = ((unsigned long long)data_[j + num.size_] * MaxUn +
            (unsigned long long)data_[j + num.size_ - 1]) /
            (unsigned long long)copy.data_[num.size_ - 1];
        rHat = ((unsigned long long)data_[j + num.size_] * MaxUn +
            (unsigned long long)data_[j + num.size_ - 1]) %
            (unsigned long long)copy.data_[num.size_ - 1];
        do {
            if (qHat == MaxUn ||
                (qHat * ((unsigned long long)copy.data_[num.size_ - 2]) >
                    (MaxUn * rHat + (unsigned long long)data_[j + num.size_ - 2]))) {
                --qHat;
                rHat += (unsigned long long)copy.data_[num.size_ - 1];
            }
            else {
                break;
            }
        } while (rHat < MaxUn);

        remains = 0;
        for (size_t i = 0; i < num.size_; ++i) {
            smth = qHat * copy.data_[i];
            tmp2 = (unsigned long long)data_[i + j] - (smth % MaxUn) - remains;
            data_[i + j] = (unsigned int)tmp2;
            remains = int((smth / MaxUn) - (tmp2 / MaxUn));
        }

        tmp2 = (unsigned long long)data_[j + num.size_] - remains;
        data_[j + num.size_] = (unsigned int)tmp2;
        result[j] = (unsigned int)qHat;
        if (tmp2 < 0) {
            --result[j];
            remains = 0;
            for (size_t i = 0; i < num.size_; ++i) {
                tmp2 = (unsigned long long)data_[i + j] + copy.data_[i] + remains;
                remains = int(tmp2 / MaxUn);
                data_[i + j] = (unsigned int)tmp2;
            }
            data_[j + num.size_] += remains;
        }
    }
    size_ = rs;
    delete[] data_;
    data_ = new unsigned int[size_];
    for (long long i = 0; i < size_; ++i) {
        data_[i] = result[i];
    }
    delete[] result;
    DelZeros();
    return *this;
}
BigInteger BigInteger::operator*(const BigInteger& num) {
    BigInteger tmp(*this);
    tmp *= num;
    return tmp;
    ;
}

BigInteger BigInteger::operator/(const BigInteger& num) {
    BigInteger tmp(*this);
    tmp /= num;
    return tmp;
}

BigInteger& BigInteger::operator%=(const BigInteger& num)
{
    BigInteger tmp = *this / num;
    *this -= tmp * num;
    return *this;
}

BigInteger BigInteger::operator%(const BigInteger& num)
{
    BigInteger result(*this);
    result %= num;
    return result;
}
BigInteger BigInteger::operator--(int)
{
    BigInteger Num(*this);
    *this -= 1;
    return Num;
}

BigInteger BigInteger::operator++(int)
{
    BigInteger Num(*this);
    *this += 1;
    return Num;
}


unsigned int BigInteger::GetData(long long i) const { return data_[i]; }

std::string to_string(const BigInteger& num) {
    const char* MAX_Un_CH = "4294967295";
    std::string result = "0";
    std::string factor = MAX_Un_CH;
    std::string tmp;
    result = std::to_string(num.GetData(0));
    for (int i = 1; i < num.GetSize(); ++i) {
        tmp = MultyStr(factor, std::to_string(num.GetData(i)));
        result = SumStr(result, tmp);
        factor = MultyStr(factor, (std::string)MAX_Un_CH);
    }
    if (result.empty()) {
        result = "0";
        return result;
    }
    if (!num.GetSign()) {
        std::string finish = "-";
        finish += result;
        return finish;
    }
    return result;
}

std::string SumStr(const std::string& L, const std::string& R) {
    std::string max;
    std::string min;
    if (L.length() >= R.length()) {
        max = L;
        min = R;
    }
    else {
        min = L;
        max = R;
    }
    std::string tmp;

    for (size_t i = 0; i < max.length() - min.length(); ++i) {
        tmp.push_back('0');
    }
    tmp = "";
    min = tmp + min;
    implementationOfSum(min, max, tmp);
    return tmp;
}

std::string MultyStr(const std::string& L, const std::string& R) {
    if (L == "0" || R == "0") {
        return "0";
    }
    if (L == "1") {
        return R;
    }
    if (R == "1") {
        return L;
    }

    std::string result;
    std::string temp;
    unsigned long int len = R.length();
    int num;
    long long coz = 0;
    for (unsigned long int i = len - 1; i >= 0; --i) {
        temp = "0";
        num = R[(unsigned int)i] - '0';
        for (int j = 0; j < num; ++j) {
            temp = SumStr(temp, L);
        }
        for (int k = 0; k < coz; ++k) {
            temp += "0";
        }
        ++coz;

        result = SumStr(result, temp);
    }
    ZeroErase(result);
    return result;
}

std::string ZeroErase(std::string result) {
    int ers = 0;
    while (result[0] == '0' && result.size() > 1) {
        ++ers;
    }
    result.erase(0, ers);
    return result;
}

BigInteger operator+(int num, const BigInteger& Num) {
    return BigInteger(num) + Num;
}
BigInteger operator-(int num, const BigInteger& Num) {
    return BigInteger(num) - Num;
}
BigInteger operator*(int num, const BigInteger& Num) {
    return BigInteger(num) * Num;
}
BigInteger operator/(int num, const BigInteger& Num) {
    return BigInteger(num) / Num;
}

bool operator==(int num, const BigInteger& Num) {
    return BigInteger(num) == Num;
}

bool IsInt(char ch) { return (ch >= '0') && (ch <= '9'); }

std::string implementationOfSum(std::string& min, std::string& max, std::string& tmp) {
    int remains = 0;
    for (size_t i = max.length() - 1; i > 0; --i) {
        tmp.push_back(char('0' + (max[i] + min[i] + remains - 2 * '0') % 10));
        remains = (max[i] + min[i] + remains - 2 * '0') / 10;
    }
    tmp.push_back(char('0' + (max[0] + min[0] + remains - 2 * '0') % 10));
    remains = (max[0] + min[0] + remains - 2 * '0') / 10;
    if (remains != 0) {
        tmp.push_back(char('0' + remains));
    }
    reverse(tmp);
    return tmp;
}
std::string reverse(std::string& tmp) {
    for (size_t i = 0, j = tmp.length() - 1; i < j; ++i, --j)
    {
        std::swap(tmp[i], tmp[j]);
    }
    return tmp;
}
int main() { return 0; }
