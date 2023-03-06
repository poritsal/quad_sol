#include <iostream>
#include <fstream>
#include <vector>
#include "quad.h"

void safe_open(std::fstream& file)
{
	file.open("input.txt");
	if (!file.is_open())
	{
		std::cout << "file open error";
		exit(1);
	}
}

void safe_out(std::fstream& file)
{
	file.open("output.txt", std::fstream::app);
	if (!file.is_open())
	{
		std::cout << "file open error";
		exit(1);
	}
}

void input_error(std::fstream& file, unsigned coef)
{
	if (coef % 3 != 0) {
		safe_out(file);
		file << "Input Error\n";
		file.close();
		exit(2);
	}
} 

std::vector <double> parser(std::fstream& file)
{
	safe_open(file);
	double d = 0;
	std::vector <double> a;
	while (!file.eof())
	{
		file >> d;
		a.push_back(d);
	}
	file.close();
	return a;
}

void quad_out(num_of_sol num, double a, double b, double c)
{
	std::fstream file;
	safe_out(file);
	switch (num)
	{
	case num_of_sol::INF:
		file << "the equation has infinitely many roots;\n";
		break;
	case num_of_sol::ZERO:
		file << "the equation has no real roots;\n";
		break;
	case num_of_sol::ONE_LINEAR:
		file << "the equation has one real root: " << (-c) / (b) << '\n';
		break;
	case num_of_sol::ONE_PARABOLIC:
		file << "the equation has one real root: " << (-b) / (2 * a) << '\n';
		break;
	case num_of_sol::TWO:
		file << "the equation has two real roots: ";
		if ((-b - sqrt(b * b - 4 * a * c)) / (2 * a) > (-b + sqrt(b * b - 4 * a * c)) / (2 * a))
		{
			file << (-b + sqrt(b * b - 4 * a * c)) / (2 * a) << ' ' << (-b - sqrt(b * b - 4 * a * c)) / (2 * a) << '\n';
		}
		else
		{
			file << (-b - sqrt(b * b - 4 * a * c)) / (2 * a) << ' ' << (-b + sqrt(b * b - 4 * a * c)) / (2 * a) << '\n';
		}
		break;
	}
	file.close();
}

void quad_sol()
{
	std::fstream file;
	std::vector <double> coef = parser(file);
	input_error(file, coef.size());
	for (int i = 0; i < coef.size(); i = i + 3) {
		if (coef[i] == 0)	{
			if (coef[i + 1] == 0)	{
				if (coef[i + 2] == 0)	{
					quad_out(num_of_sol::INF, coef[i], coef[i + 1], coef[i + 2]);
				}
				else {
					quad_out(num_of_sol::ZERO, coef[i], coef[i + 1], coef[i + 2]);
				}
			}
			else {
				quad_out(num_of_sol::ONE_LINEAR, coef[i], coef[i + 1], coef[i + 2]);
			}
		}
		else if (coef[i + 1] * coef[i + 1] - 4 * coef[i] * coef[i + 2] < 0)	{
			quad_out(num_of_sol::ZERO, coef[i], coef[i + 1], coef[i + 2]);
		}
		else if (coef[i + 1] * coef[i + 1] - 4 * coef[i] * coef[i + 2] > 0)	{
			quad_out(num_of_sol::TWO, coef[i], coef[i + 1], coef[i + 2]);
		}
		else if (coef[i + 1] * coef[i + 1] - 4 * coef[i] * coef[i + 2] == 0) {
			quad_out(num_of_sol::ONE_PARABOLIC, coef[i], coef[i + 1], coef[i + 2]);
		}
	}
}
