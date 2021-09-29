#include "pch.h"
#include "pch.h"
#include <sstream>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <string>

using namespace std;


template <bool b, typename T>
struct KSelectValue;

template <typename T>
struct KSelectValue<true, T>
{
	static T GetValue(T v) { return v; }
};
template <typename T>
struct KSelectValue<false, T>
{
	static int GetValue(T v) { return 1; }
};

template <typename T>
decltype(auto) FMult2(T x) { return KSelectValue<is_integral<T>::value, T>::GetValue(x); }
template <typename С, typename T, typename... Args>
decltype(auto) FMult2(С composition, T x, Args... args)
{
	auto xSum = composition * KSelectValue<is_integral<T>::value, T>::GetValue(x);
	//cout << composition << "  " << KSelectValue<is_integral<T>::value, T>::GetValue(x) << " = " << xSum << endl;
	return FMult2(xSum, args...);
}


/*is_arithmetic<Ty>::value
Экземпляр предиката типа имеет значение true, если тип Ty является арифметическим,
то есть целочисленным типом, типом с плавающей запятой или формой cv-qualified одного из них.
В противном случае — значение false.
is_fundamental<Ty>::value
Экземпляр предиката типа содержит значение true, если тип Ty — фундаментальный тип,
т. е., void, целочисленный тип, тип с плавающей запятой или форма cv-qualified
одного из них. В противном случае он содержит значение false.
is_integral<T>::value
Целочисленный тип — один из типов bool, char, unsigned char, signed char, wchar_t,
short, unsigned short, int, unsigned int, long и unsigned long.
Кроме того, целочисленный тип может быть одним из long long, unsigned long long,
__int64 и unsigned __int64 при использовании компиляторов, поддерживающих такие типы.
is_floating_point<T>::value
Тип с плавающей запятой является одним из следующих типов: float, double или long double.
*/


int main()
{
	setlocale(LC_ALL, "Russian");
	auto result = FMult2(2, 3.5, 4, 'a', 32, string("abc"), (short)12);
	cout << "Произведение значений аргументов целого типа : " << result << endl;
	system("pause");
	return 0;
}