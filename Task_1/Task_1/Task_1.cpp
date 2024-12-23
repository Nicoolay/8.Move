#include <iostream>
#include <vector>

template <typename T>
void move_vectors(std::vector<T>& one, std::vector<T>& two) {
    std::vector <T> tmp = std::move(one);
    one = std::move(two);
    two = std::move(tmp);
}

template <typename T>
void print_vector(std::vector<T> vec) {
    for (T itr : vec) {
        std::cout << itr << " ";
    }
    std::cout << std::endl;
}
int main()
{
    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;
    std::cout << "vec one: ";
    print_vector(one);
    std::cout << "vec two: ";
    print_vector(two);
    move_vectors(one, two);
    std::cout << "after move_vectors: \n";
    std::cout << "vec one: ";
    print_vector(one);
    std::cout << "vec two: ";
    print_vector(two);
} 


