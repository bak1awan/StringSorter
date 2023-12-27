#include "String.h"
#include <cstring>

using namespace StringContainers;

String::String() : data_(new char[1]), allocated_(1)
{
    SetNullTerminator();
}

String::String(std::size_t size) : data_(size == 0 ? nullptr : new char[size + 1]), allocated_(size == 0 ? size : (size + 1))
{
    SetNullTerminator();
}

String::String(std::size_t size, char ch) : String(size)
{
    for (std::size_t i = 0; i < size; ++i, ++used_)
    {
        data_[i] = ch;
    }
    SetNullTerminator();
}

String::String(const String& rhs) : data_(new char[rhs.allocated_]), allocated_(rhs.allocated_)
{
    Copy(rhs.data_, rhs.used_);
}

String& String::operator=(const String& rhs)
{
    /*
     * Здесь отсутствует проверка на самоприсваивание, так как у нас есть выбор из двух зол:
     * 1. Постоянно выполнять какую-то маленькую работу (проверку на самоприсваивание)
     * 2. В редких случаях выополнять ненужную большую работу (выделение памяти и копирование с самого себя)
     * Так как во втором случае без проверки на самоприсваивание оператор все равно корректно отработает,
     * я решил не делать проверку на самоприсваивание, то есть выбрать второй вариант.
     */
    String tmp = rhs;
    std::swap(*this, tmp);
    return *this;
}

void String::Swap(String&& rhs) noexcept
{
    std::swap(data_, rhs.data_);
    std::swap(used_, rhs.used_);
    std::swap(allocated_, rhs.allocated_);
}

String::String(String&& rhs) noexcept
{
    Swap(std::forward<String>(rhs));
}

String& String::operator=(String&& rhs) noexcept
{
    Swap(std::forward<String>(rhs));
    return *this;
}

String::~String()
{
    delete data_;
}

String::String(const char* c_str) : String(strlen(c_str))
{
    used_ = allocated_ - 1;
    memcpy(data_, c_str, used_ * sizeof(char));
    // No need to cal SetNullTerminator() because it is already set in String(strlen(c_str)) ctor
}

String::operator char*()
{
    return data_;
}

char& String::operator[](std::size_t i) noexcept
{
    return data_[i];
}

const char& String::operator[](std::size_t i) const noexcept
{
    return data_[i];
}

String& String::operator+=(const String& rhs)
{
    if (allocated_ - used_ > rhs.used_)
    {
        Copy(rhs.data_, rhs.used_, used_);
    }
    else
    {
        String tmp((rhs.used_ + used_) * REALLOC_MULT);
        tmp.Copy(data_, used_);
        tmp.Copy(rhs.data_, rhs.used_, tmp.used_);
        std::swap(*this, tmp);
    }
    return *this;
}

bool String::LessThan(const String& rhs, bool bCaseSensetive) const noexcept
{
    if (used_ < rhs.Size())
    {
        return true;
    }
    else if (used_ > rhs.Size())
    {
        return false;
    }
    else
    {
        return InnerStringLessThan(rhs.data_, bCaseSensetive);
    }
}

bool String::InnerStringLessThan(const char* rhs, bool bCaseSensitive) const noexcept
{
    for (std::size_t i = 0; i < used_; ++i)
    {
        char ch1 = bCaseSensitive ? data_[i] : tolower(data_[i]);
        char ch2 = bCaseSensitive ? rhs[i] : tolower(rhs[i]);
        if (ch1 > ch2)
        {
            return false;
        }
        if (ch1 < ch2)
        {
            return true;
        }
    }
    return false;
}

// Не успел для данной функции предусмотреть аналог работы с memcpy,
// так как очень нетривиальным становится определение количества использованных символов после операции копирования
std::size_t String::Copy(const char* from, std::size_t count, std::size_t dest_pos) noexcept
{
    std::size_t i = 0;

    for (; i < count; ++i)
    {
        /*
         * Данная проверка нужна для того, чтобы не выбежать за границы выделенной памяти.
         * Данная функция не подразумевает реаллокацию в случае, если копируемая строка превышает выделенную память.
         */
        if ((i + dest_pos) >= (allocated_ - 1))
        {
            std::cout << "Overwritting prevented!\n";
            break;
        }

        data_[i + dest_pos] = from[i];

        /*
         * Данная проверка нужна для того, чтобы инкрементировать размер строки только в том случае,
         * если копирование использует аллоцированную память. То есть если перезаписывается существующие символы, размер строки не должен
         * расти.
         */
        if (i + dest_pos == used_) ++used_;
    }
    SetNullTerminator();
    return i;
}

void String::Dump(std::ostream& out) const noexcept
{
    if (!data_)
    {
        return;
    }

    auto i = 0;
    while (data_[i])
    {
        out << data_[i];
        ++i;
    }
    out << '\n';
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
    str.Dump(out);
    return out;
}

StringContainers::String operator+(const StringContainers::String& lhs, const StringContainers::String& rhs)
{
    String tmp(lhs.Size() + rhs.Size());
    tmp += lhs;
    tmp += rhs;
    return tmp;
}

std::istream& String::GetLine(std::istream& in, char delimeter)
{
    std::size_t i = 0;
    while (true)
    {
        auto ch = in.get();
        if (ch == delimeter) break;
        // если мы дошли до конца выделенной памяти, выделяем новую и копируем в нее уже имеющиеся символы
        if (i == allocated_ - 1)
        {
            String tmp(allocated_ * REALLOC_MULT);
            tmp.Copy(data_, used_);
            std::swap(*this, tmp);
        }
        data_[i] = ch;

        if (used_ == i)
        {
            ++used_;
        }

        ++i;
    }

    if (i < used_)
    {
        used_ = i - 1;
    }

    SetNullTerminator();
    return in;
}

bool operator==(const StringContainers::String& lhs, const StringContainers::String& rhs)
{
    /*
     * Capacity, то есть количество аллоцированной памяти, не участвует в сравнении,
     * так как если строки имеют одинаковый размер и одинаковые символы в массиве - этого достаточно,
     * чтобы сказать, что они равны (из-за различных аллокаций может расходиться allocated_, но это не
     * критично)
     */
    return lhs.Size() == rhs.Size() && (strcmp(lhs.Data(), rhs.Data()) == 0);
}

bool operator!=(const StringContainers::String& lhs, const StringContainers::String& rhs)
{
    return !(lhs == rhs);
}

void String::SetNullTerminator()
{
    if (!data_) return;
    // Если у нас есть использованные символы в строке, нам нужно завершить их нуль-терминатором
    if (used_ > 0)
    {
        data_[used_] = NCHAR;
    }
    /*
     * если символов нет, то тогда нужно завершить всю строку нуль-терминатором,
     * чтобы не выбежать за границы массива даже на неинициализированной строке
     */
    else
    {
        data_[allocated_ - 1] = NCHAR;
    }
}