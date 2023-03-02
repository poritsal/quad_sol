#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <cstdlib>
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

void quad_out(int r, double a, double b, double c)
{
	std::fstream file;
	safe_out(file);
	switch (r)
	{
	case 3:
		file << "the equation has infinitely many roots;\n";
		break;
	case 0:
		file << "the equation has no real roots;\n";
		break;
	case 4:
		file << "the equation has one real root: " << (-c) / (b) << '\n';
		break;
	case 5:
		file << "the equation has one real root: " << (-b) / (2 * a) << '\n';
		break;
	case 2:
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

	if (coef.size() % 3 != 0)
	{
		safe_out(file);
		file << "Input Error";
		file.close();
		exit(2);
	}

	for (int i = 0; i < coef.size(); i = i + 3)
	{
		double a = coef[i], b = coef[i + 1], c = coef[i + 2], d = b * b - 4 * a * c;

		if (a == 0 && b == 0 && c == 0)
		{
			quad_out(3, a, b, c);
		}
		else if (a == 0 && b == 0 && c != 0)
		{
			quad_out(0, a, b, c);
		}
		else if (a == 0 && b != 0)
		{
			quad_out(4, a, b, c);
		}
		else if (d < 0)
		{
			quad_out(0, a, b, c);
		}
		else if (d == 0)
		{
			quad_out(5, a, b, c);
		}
		else if (d > 0)
		{
			quad_out(2, a, b, c);
		}
	}
}