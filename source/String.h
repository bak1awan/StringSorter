#pragma once

#include <iostream>

namespace StringContainers
{
    /*
     * Класс динамических строк String, инкапсулирует в себе указатель и охраняет два инварианта:
     * 1. Размер строки
     * 2. Строка обязана заканчиваться нуль-терминатором
     * Все функции и конструкторы являются безопасными относительно исключений, так как выделение памяти всегда
     * происходит для временных объектов, с которыми потом после всех операций мы обмениваемся состоянием,
     * поэтому инварианты класса не будут нарушены. Если же исключение возникнет при выделение память на саму динамическую строку
     * которую хранит наш класс, new[] прибьет ту память, которую успел выделить, а объект не создастся.
     */
    class String final
    {
    public:
        String();
        /*
         * Правило пяти, так как наш класс выделяет некоторый ресурс (строку) в конструкторе и управляет им (RAII),
         * а затем должен освободить ее в дестркуторе
         */
        String(const String& rhs);
        String& operator=(const String& rhs);
        String(String&& rhs) noexcept;
        String& operator=(String&& rhs) noexcept;
        ~String();

        // Удобные конструкторы для быстрого тестирования
        String(std::size_t size);
        String(std::size_t size, char ch);

        String& operator+=(const String& rhs);

        // Конструктор из char* для преобразования и обратной совместимости
        String(const char* c_str);

        // Оператор для преобразования к char* так же для обратной совместимости
        operator char*();

        // Метод для копирования в данную строку
        std::size_t Copy(const char* from, std::size_t count, std::size_t dest_pos = 0) noexcept;

        char& operator[](std::size_t i) noexcept;
        const char& operator[](std::size_t i) const noexcept;

        // Метод для вывода строки в поток вывода (чтобы не делать operator<< другом)
        void Dump(std::ostream& out) const noexcept;

        // noexcept метод для реализации move-семантики
        void Swap(String&& rhs) noexcept;

    public:
        // Function for reading lines from input buffer
        std::istream& GetLine(std::istream& in, char delimeter = '\n');

        // Function that simulates operator< for String
        bool LessThan(const String& rhs, bool bCaseSensetive = true) const noexcept;

    public:
        // Геттеры для полей класса
        char* Data() & noexcept { return data_; }
        const char* Data() const& noexcept { return data_; }
        std::size_t Size() const& noexcept { return used_; }
        std::size_t Capacity() const& noexcept { return allocated_; }

    private:
        // Метод для установки завершающего символа, детали реализации строки, поэтому private метод
        void SetNullTerminator();
        // Custom function for comparing c-strings with case-sensitive flag
        bool InnerStringLessThan(const char* rhs, bool bCaseSensitive = true) const noexcept;

    private:
        char* data_ = nullptr;
        std::size_t used_ = 0;       // количество использованных символов
        std::size_t allocated_ = 0;  // количество аллоцированной памяти под символы
        static const std::size_t REALLOC_MULT = 2;  // константа, которая описывает стратегию реаллокации памяти для строки
    };
    static const char NCHAR = '\0';  // удобная статическая константа в пространстве имен StringContainers для завершающего символа

}  // namespace StringContainers

std::ostream& operator<<(std::ostream& out, const StringContainers::String& str);
StringContainers::String operator+(const StringContainers::String& lhs, const StringContainers::String& rhs);
bool operator==(const StringContainers::String& lhs, const StringContainers::String& rhs);
bool operator!=(const StringContainers::String& lhs, const StringContainers::String& rhs);
