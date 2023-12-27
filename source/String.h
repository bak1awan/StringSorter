#pragma once

#include <iostream>

namespace StringContainers
{
    /*
     * ����� ������������ ����� String, ������������� � ���� ��������� � �������� ��� ����������:
     * 1. ������ ������
     * 2. ������ ������� ������������� ����-������������
     * ��� ������� � ������������ �������� ����������� ������������ ����������, ��� ��� ��������� ������ ������
     * ���������� ��� ��������� ��������, � �������� ����� ����� ���� �������� �� ������������ ����������,
     * ������� ���������� ������ �� ����� ��������. ���� �� ���������� ��������� ��� ��������� ������ �� ���� ������������ ������
     * ������� ������ ��� �����, new[] ������� �� ������, ������� ����� ��������, � ������ �� ���������.
     */
    class String final
    {
    public:
        String();
        /*
         * ������� ����, ��� ��� ��� ����� �������� ��������� ������ (������) � ������������ � ��������� �� (RAII),
         * � ����� ������ ���������� �� � �����������
         */
        String(const String& rhs);
        String& operator=(const String& rhs);
        String(String&& rhs) noexcept;
        String& operator=(String&& rhs) noexcept;
        ~String();

        // ������� ������������ ��� �������� ������������
        String(std::size_t size);
        String(std::size_t size, char ch);

        String& operator+=(const String& rhs);

        // ����������� �� char* ��� �������������� � �������� �������������
        String(const char* c_str);

        // �������� ��� �������������� � char* ��� �� ��� �������� �������������
        operator char*();

        // ����� ��� ����������� � ������ ������
        std::size_t Copy(const char* from, std::size_t count, std::size_t dest_pos = 0) noexcept;

        char& operator[](std::size_t i) noexcept;
        const char& operator[](std::size_t i) const noexcept;

        // ����� ��� ������ ������ � ����� ������ (����� �� ������ operator<< ������)
        void Dump(std::ostream& out) const noexcept;

        // noexcept ����� ��� ���������� move-���������
        void Swap(String&& rhs) noexcept;

    public:
        // Function for reading lines from input buffer
        std::istream& GetLine(std::istream& in, char delimeter = '\n');

        // Function that simulates operator< for String
        bool LessThan(const String& rhs, bool bCaseSensetive = true) const noexcept;

    public:
        // ������� ��� ����� ������
        char* Data() & noexcept { return data_; }
        const char* Data() const& noexcept { return data_; }
        std::size_t Size() const& noexcept { return used_; }
        std::size_t Capacity() const& noexcept { return allocated_; }

    private:
        // ����� ��� ��������� ������������ �������, ������ ���������� ������, ������� private �����
        void SetNullTerminator();
        // Custom function for comparing c-strings with case-sensitive flag
        bool InnerStringLessThan(const char* rhs, bool bCaseSensitive = true) const noexcept;

    private:
        char* data_ = nullptr;
        std::size_t used_ = 0;       // ���������� �������������� ��������
        std::size_t allocated_ = 0;  // ���������� �������������� ������ ��� �������
        static const std::size_t REALLOC_MULT = 2;  // ���������, ������� ��������� ��������� ����������� ������ ��� ������
    };
    static const char NCHAR = '\0';  // ������� ����������� ��������� � ������������ ���� StringContainers ��� ������������ �������

}  // namespace StringContainers

std::ostream& operator<<(std::ostream& out, const StringContainers::String& str);
StringContainers::String operator+(const StringContainers::String& lhs, const StringContainers::String& rhs);
bool operator==(const StringContainers::String& lhs, const StringContainers::String& rhs);
bool operator!=(const StringContainers::String& lhs, const StringContainers::String& rhs);
