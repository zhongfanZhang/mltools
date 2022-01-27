#include <fstream>
#include <chrono>
#include <iostream>
#include <vector>
#include <iterator>

int main()
{
	const auto start = std::chrono::high_resolution_clock::now();
	std::ifstream ifs("Phones_gyroscope.csv");
	const std::vector<std::string> parsed(std::istream_iterator<std::string>(ifs), {});
	ifs.close();
	const auto end = std::chrono::high_resolution_clock::now();
	const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << parsed[0] << '\n';
	std::cout << "time_elapsed: " << static_cast<double>(duration.count()) / 1000000 << '\n';
}