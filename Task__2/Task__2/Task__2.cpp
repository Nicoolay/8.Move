#include <string>
#include <iostream>
#include <algorithm>

class big_integer
{
private:
	std::string number;
	//сложенние
	static std::string add_strings(const std::string& num1, const std::string& num2) {// нах static?
		std::string result;
		int carry{};
		int i = num1.size() - 1;
		int j = num2.size() - 1;
		while (i >= 0 || j >= 0 || carry != 0) {
			int digit1 = (i >= 0) ? (num1[i] - '0') : 0;//? как к обычному виду привести
			int digit2 = (j >= 0) ? (num2[j] - '0') : 0;
			int sum = digit1 + digit2 + carry;
			carry = sum / 10;
			result.push_back((sum % 10) + '0');
			--i; 
			--j;

		}
		std::reverse(result.begin(), result.end());
		return result;
	}
	//умножение на цифру
	static std::string multiply_by_digit(const std::string& num, int digit) {
		if (digit == 0) return "0"; 
		std::string result;
		int carry{};
		for (int i = num.size() - 1; i >= 0; --i) {
			int product = (num[i] - '0') * digit + carry; 
			result.push_back((product % 10) + '0');
			carry = product / 10;
		}
		if (carry > 0) result.push_back(carry + '0');
		std::reverse(result.begin(), result.end());
		return result;
	}
	//умножение строки на строку
	static std::string multiply_strings(const std::string& num1, const std::string& num2) {
		std::string result="0";
		int num2_size = num2.size();
		for (int i = num2_size - 1; i >= 0; --i) {
			int digit = num2[i] - '0';
			std::string partial_result = multiply_by_digit(num1, digit);
			partial_result.append(num2_size - 1 - i, '0');
			result = add_strings(result, partial_result);
		}



		return result;
	}
public:
	explicit big_integer(const std::string& num) :number(num) { // тут подробней остановиться erase, std::min, find_first вот это всё посмотреть как работает
		number.erase(0, std::min(number.find_first_not_of('0'), number.size() - 1));
		if (number.empty()) number = "0";
	}
	//перемещающий конструктор
	big_integer(big_integer&&other):number(std::move(other.number)){}

	
	//оператор сложения
	big_integer operator+(const big_integer& other) const {
		return big_integer(add_strings(this->number, other.number));
	}
	// уммножение на число
	big_integer operator* (int num) const {
		return big_integer(multiply_by_digit(this->number, num));
	}
	//умножение 2х больших чисел
	big_integer operator*(const big_integer& other) const {
		return big_integer(multiply_strings(this->number, other.number));
	}
	//оператор вывода <<
	friend std::ostream& operator<<(std::ostream& os, const big_integer& bigInt) {
		os << bigInt.number;
		return os;
		}
	//копирующий оператор присваивания
	big_integer& operator=(const big_integer& other) {
		if (this != &other) {
			number = other.number;
		}
		return *this;

	}
	//оператор перемещения
	big_integer& operator=(big_integer&& other) noexcept {
		if (this != &other) {
			number = std::move(other.number);
		}
		return *this;
	}
	//копирующий конструктор
	big_integer(const big_integer& other):number(other.number){}
};



int main()
{
	auto number1 = big_integer("114575");
	auto number2 = big_integer("78524");
	auto result = number1 + number2;
	std::cout <<"add:" << result<<std::endl; // 193099
	auto result_with_int = number1 * 23;
	std::cout << "product with int: " << result_with_int<<std::endl;
	auto result_big_integers = number1 * number2;
	std::cout << "big integers product: " << result_big_integers<<std::endl;
	
}
