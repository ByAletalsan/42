/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:40:48 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/30 17:40:33 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter( const ScalarConverter &s )
{
	(void)s;
}

const ScalarConverter &ScalarConverter::operator=( const ScalarConverter &s )
{
	(void)s;
	return *this;
}

ScalarConverter::~ScalarConverter()
{
}

//Get Type
static bool	isChar( const std::string &s )
{
	if (s.length() != 1)
		return false;
	if (s[0] >= '0' && s[0] <= '9')
		return false;
	return true;
}

static bool isInt( const std::string &s )
{
	if (s.length() == 1 && (s[0] < '0' || s[0] > '9'))
		return false;
	if (s[0] != '-' && (s[0] < '0' || s[0] > '9'))
		return false;
	for (unsigned i = 1; i < s.length(); i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return false;
	}
	return true;
}

static bool isFloat( const std::string &s )
{
	if (s.length() == 1 && (s[0] < '0' || s[0] > '9'))
		return false;
	if (s[0] != '-' && (s[0] < '0' || s[0] > '9'))
		return false;
	size_t index;
	if ((index = s.find(".")) == std::string::npos)
		return false;
	if (s.substr(s.find(".") + 1, std::string::npos).length() <= 1)
		return false;
	for (unsigned i = 1; i < index; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return false;
	}
	for (unsigned i = index + 1; i < s.length() - 1; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return false;
	}
	if (s[s.length() - 1] != 'f')
		return false;
	return true;
}

static bool isDouble( const std::string &s )
{
	if (s.length() == 1 && (s[0] < '0' || s[0] > '9'))
		return false;
	if (s[0] != '-' && (s[0] < '0' || s[0] > '9'))
		return false;
	size_t index;
	if ((index = s.find(".")) == std::string::npos)
		return false;
	if (s.substr(s.find(".") + 1, std::string::npos).length() == 0)
		return false;
	for (unsigned i = 1; i < index; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return false;
	}
	for (unsigned i = index + 1; i < s.length(); i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return false;
	}
	return true;
}

//Prints
static void printChar( const std::string &s )
{
	char	c = s[0];

	if (static_cast<int>(c) < 32 || static_cast<int>(c) > 126)
        std::cout << "char : impossible" << std::endl;
    else
        std::cout << "char: " << "'" << c  << "'" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

static void printInt( const std::string &s )
{
	int c = atoi(s.c_str());
    if (c < 32 || c > 126)
        std::cout << "char : Non displayable" << std::endl;
    else
        std::cout << "char: " << "'" << static_cast<char>(c) << "'" << std::endl;
    
    long long k = atol(s.c_str());
    if (k > INT_MAX || k < INT_MIN)
        std::cout << "int: Impossible" << std::endl;
    else
        std::cout << "int: " << c << std::endl;
    if (k > INT_MAX || k < INT_MIN)
        std::cout << "float : Impossible" << std::endl;
    else
        std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
    if (k > INT_MAX || k < INT_MIN)
        std::cout << "double : Impossible" << std::endl;
    else
        std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

static void printFloat( const std::string &s )
{
	float c = atof(s.c_str());
    if (c < 32 || c > 126)
        std::cout << "char : Non displayable" << std::endl;
    else
        std::cout << "char: " << "'" << static_cast<char>(c) << "'" << std::endl;
    
    long long k = atol(s.c_str());
    if (k > INT_MAX || k < INT_MIN)
        std::cout << "int: Impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(c) << std::endl;
    if (k > INT_MAX || k < INT_MIN)
        std::cout << "float : Impossible" << std::endl;
    else
	{
        std::cout << "float: " << c;
		if (c - static_cast<int>(c) == 0)
			std::cout << ".0f" << std::endl;
		else
			std::cout << "f" << std::endl;
	}
    if (k > INT_MAX || k < INT_MIN)
        std::cout << "double : Impossible" << std::endl;
    else
        std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

static void printDouble( const std::string &s )
{
	double c = atof(s.c_str());
    if (c < 32 || c > 126)
        std::cout << "char : Non displayable" << std::endl;
    else
        std::cout << "char: " << "'" << static_cast<char>(c) << "'" << std::endl;
    
    long long k = atol(s.c_str());
    if (k > INT_MAX || k < INT_MIN)
        std::cout << "int: Impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(c) << std::endl;
    if (k > INT_MAX || k < INT_MIN)
        std::cout << "float : Impossible" << std::endl;
    else
	{
        std::cout << "float: " << c;
		if (c - static_cast<int>(c) == 0)
			std::cout << ".0f" << std::endl;
		else
			std::cout << "f" << std::endl;
	}
    if (k > INT_MAX || k < INT_MIN)
        std::cout << "double : Impossible" << std::endl;
    else
	{
        std::cout << "double: " << c;
		if (c - static_cast<int>(c) == 0)
			std::cout << ".0";
		std::cout << std::endl;
	}
}

static void	printInfMinus()
{
	std::cout << "char : impossible" << std::endl;
    std::cout << "int : impossible" << std::endl;
    std::cout << "float : -inff" << std::endl;
    std::cout << "double : -inf" << std::endl;
}

static void	printInfAdd()
{
	std::cout << "char : impossible" << std::endl;
    std::cout << "int : impossible" << std::endl;
    std::cout << "float : +inff" << std::endl;
    std::cout << "double : +inf" << std::endl;
}

static void	printNan()
{
	std::cout << "char : impossible" << std::endl;
    std::cout << "int : impossible" << std::endl;
    std::cout << "float : nanf" << std::endl;
    std::cout << "double : nan" << std::endl;
}

static void printOther( const std::string &s )
{
	std::string values[] = { "-inff", "+inff", "nanf", "-inf", "+inf", "nan" };
    void (*printValues[])(void)= { &printInfMinus, &printInfAdd, &printNan, &printInfMinus, &printInfAdd, &printNan };

    for (int i = 0; i < 6; i++)
    {
        if (s == values[i])
        {
            printValues[i]();
            return ;
        }
    }
    std::cout << "CONVERT ERROR" << std::endl;
}

void	ScalarConverter::convert( std::string s )
{
	bool (*isType[])( const std::string &s ) = { &isChar, &isInt, &isFloat, &isDouble };

    void (*printValues[])( const std::string &s ) = { &printChar, &printInt, &printFloat, &printDouble };

    for (unsigned i = 0; i < 4; i++)
    {
        if (isType[i](s))
        {
			printValues[i](s);
			return ;
		}
    }
	printOther(s);
}
