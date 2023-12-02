/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 19:59:50 by atalaver          #+#    #+#             */
/*   Updated: 2023/12/02 20:20:25 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static int	suma( int n1, int n2)
{
	return n1 + n2;
}

static int	resta( int n1, int n2)
{
	return n1 - n2;
}

static int	mult( int n1, int n2)
{
	return n1 * n2;
}

static int	divi( int n1, int n2)
{
	if (n2 == 0)
		throw std::invalid_argument("Division by zero");
	return n1 / n2;
}

RPN::RPN()
{
	this->_oper[0].op = "+";
	this->_oper[0].func = &suma;
	this->_oper[1].op = "-";
	this->_oper[1].func = &resta;
	this->_oper[2].op = "*";
	this->_oper[2].func = &mult;
	this->_oper[3].op = "/";
	this->_oper[3].func = &divi;
}

RPN::RPN( const RPN &r ) : nums(r.nums)
{
}

const RPN &RPN::operator=( const RPN &r )
{
	if (this != &r)
		this->nums = r.nums;
	return *this;
}

RPN::~RPN()
{
}

static int	find_index_operation( const std::string &word )
{
	std::string operations[] = {"+", "-", "*", "/"};
	for (int i = 0; i < 4; i++)
    {
        if (word == operations[i])
            return i;
    }
    return -1;
}

static int	ft_stoi( const std::string &number )
{
    std::stringstream ss(number);
    int result;

    ss >> result;

    if (ss.fail())
        throw std::invalid_argument("conversion failed");

    return result;
}

static std::string	ft_all_of( const std::string &str, int (*isDigit)(int) )
{
    bool valid = true;
    size_t i = 0;

    if (str.length() == 1 && (str[0] == '+' || str[0] == '-'))
        valid = false;

    if (str.length() == 0)
        valid = false;

    if (str[0] == '+' || str[0] == '-')
        i = 1;

    for (; i < str.length(); i++) {
        if (!isDigit(str[i]))
            valid = false;
    }

    if (!valid)
		throw std::invalid_argument("not a number");

    return str;
}

void	RPN::run( const std::string &numbers )
{
	std::stringstream ss(numbers);
	std::string	word;

    try {
        while (ss >> word)
        {
            int index = find_index_operation(word);
            if (index != -1) // Es un operador
            {
                if (this->nums.size() < 2)
                    throw std::invalid_argument("Not enough operands");

				int a = this->nums.top();
				this->nums.pop();
				int b = this->nums.top();
				this->nums.pop();

				this->nums.push((this->_oper[index].func)(b, a)); // Operamos y añadimos resultado al stack
            }
            else // Vemos si es un numero y si lo es lo ponemos en el stack
                this->nums.push(ft_stoi(ft_all_of(word, &std::isdigit)));
        }

        if (this->nums.size() != 1) // Solo debe quedar 1 numero al final
            throw std::invalid_argument("too many operands");

        std::cout << this->nums.top() << std::endl;

    } catch (std::exception& e) {
        std::cout << "Error" << std::endl;
    }

    ss.clear();
}
