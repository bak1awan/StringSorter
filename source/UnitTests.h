#pragma once
#include "String.h"
#include <cassert>

namespace Tests
{
    void CopyCtorTest()
    {
        StringContainers::String str1(10, 'a');
        StringContainers::String str2(str1);
        printf("Copy ctor:\nstr1: %s, str2(str1): %s.\n\n", str1.Data(), str2.Data());
        assert(str1 == str2);
    }
    void CopyAssignTest()
    {
        StringContainers::String str1(10, 'a');
        StringContainers::String str2;
        str2 = str1;
        printf("Copy assign:\nstr1: %s, str2 = str1: %s.\n\n", str1.Data(), str2.Data());
        assert(str1 == str2);
    }
    void SizeCtorTest()
    {
        StringContainers::String str1(10);
        printf("Size ctor:\nstr1(10): %s.\n\n", str1.Data());
        assert(str1.Size() == 0 && str1.Capacity() == 11);
    }
    void SizeAndCharCtorTest()
    {
        StringContainers::String str1(10, 'a');
        printf("Size and char ctor:\nstr1(10, 'a'): %s.\n\n", str1.Data());
        assert(str1.Size() == 10 && str1.Capacity() == 11);
    }
    void MoveCtorTest()
    {
        StringContainers::String str1(10, 'a');
        StringContainers::String str1_before_move(str1);
        StringContainers::String str2(std::move(str1));
        printf("Move ctor:\nstr1 before move: %s, str1 after move: %s, str2(std::move(str1)): %s.\n\n", str1_before_move.Data(),
            str1.Data(), str2.Data());
        assert(str2 == str1_before_move);
    }
    void MoveAssignTest()
    {
        StringContainers::String str1(10, 'a');
        StringContainers::String str1_before_move(str1);
        StringContainers::String str2;
        str2 = std::move(str1);
        printf("Move assign:\nstr1 before move: %s, str1 after move: %s, str2 = std::move(str1): %s.\n\n", str1_before_move.Data(),
            str1.Data(), str2.Data());
        assert(str2 == str1_before_move);
    }
    void ExternPlusOperatorTest()
    {
        StringContainers::String str1(3, 'a');
        StringContainers::String str2(3, 'b');
        StringContainers::String str3;
        str3 = str1 + str2;
        printf("Extern operator +:\nstr1: %s, str2: %s, str1 + str2: %s.\n\n", str1.Data(), str2.Data(), str3.Data());
        assert(str3.Capacity() == ((str1.Size() + str2.Size()) + 1) && str3.Size() == (str1.Size() + str2.Size()));
    }
    void PlusEqualOperatorTest()
    {
        StringContainers::String str1(3, 'a');
        StringContainers::String str1_before_Copy(str1);
        StringContainers::String str2(3, 'b');
        str1 += str2;
        printf("operator+= test on initialized string:\nstr1: %s, str2: %s, str1 += str2: %s.\n\n", str1_before_Copy.Data(), str2.Data(),
            str1.Data());
        StringContainers::String str3;
        StringContainers::String str4;
        str3 += str2;
        printf("operator+= test on default string:\nstr2: %s, str3: %s, str3 += str2: %s.\n\n", str2.Data(), str4.Data(), str3.Data());
    }
    void CopyMethodTest()
    {
        StringContainers::String str1(3, 'a');
        StringContainers::String str1_before_Copy(str1);
        StringContainers::String str2(3, 'b');
        str1.Copy(str2.Data(), str2.Size());
        printf("Copy method test:\nstr1: %s, str2: %s, str1.Copy(str2.Data(), str2.Size()): %s.\n\n", str1_before_Copy.Data(), str2.Data(),
            str1.Data());

        StringContainers::String str3(3, 'a');
        StringContainers::String str3_before_Copy(str3);
        StringContainers::String str4(3, 'b');
        printf("Copy method test with overwritting:\n");
        str3.Copy(str4.Data(), str4.Size(), 1);
        printf("str3: %s, str4: %s, str3.Copy(str4.Data(), str4.Size(), 1): %s.\n\n", str3_before_Copy.Data(), str4.Data(), str3.Data());

        StringContainers::String str5(3, 'a');
        StringContainers::String str5_before_Copy(str5);
        StringContainers::String str6(3, 'b');
        printf("Copy method test with big start index:\n");
        str5.Copy(str6.Data(), str6.Size(), 100);
        printf("str5: %s, str6: %s, str5.Copy(str6.Data(), str6.Size(), 100): %s.\n\n", str5_before_Copy.Data(), str6.Data(), str5.Data());

        StringContainers::String str7(5);
        StringContainers::String str8(5, 'a');
        printf("Copy method with Size initializied string:\n");
        str7.Copy(str8.Data(), str8.Size(), 3);
        printf("str7.Copy(str8.Data(), str8.Size(), 3): %s.\n\n", str7.Data());
    }

    void ImplicitCastFromCStrTest()
    {
        char c_str[] = "Hello";
        StringContainers::String str("Hello");
        std::cout << str;
        printf("Implicit ctor from c-style string:\nc-style string: %s, str(c-style string): %s.\n\n", c_str, str.Data());
    }

    void ImplicitCastToCStrTest()
    {
        StringContainers::String str(3, 'a');
        char* ptr = str;
        printf("Implicit ctor to c-style string:\nstr: %s, char* ptr = str: %s.\n\n", str.Data(), ptr);
    }

    void RunTests()
    {
        CopyCtorTest();
        CopyAssignTest();
        SizeCtorTest();
        SizeAndCharCtorTest();
        MoveCtorTest();
        MoveAssignTest();
        ExternPlusOperatorTest();
        PlusEqualOperatorTest();
        CopyMethodTest();
        ImplicitCastFromCStrTest();
        ImplicitCastToCStrTest();
    }

}  // namespace Tests
