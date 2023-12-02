/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 21:48:14 by atalaver          #+#    #+#             */
/*   Updated: 2023/12/02 23:32:03 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : N(0)
{
}

PmergeMe::PmergeMe( char **argv ) : N(0)
{
    for (int i = 1; argv[i]; i++)
    {
        this->vec.push_back(atoi(argv[i]));
        this->lst.push_back(atoi(argv[i]));
		this->N++;
    }
}

PmergeMe::PmergeMe( const PmergeMe &p ) : vec(p.vec), lst(p.lst), N(p.N)
{
}

const PmergeMe &PmergeMe::operator=( const PmergeMe &p )
{
	if (this != &p)
	{
		this->vec = p.vec;
		this->lst = p.lst;
		this->N = p.N;
	}
    return *this;
}

PmergeMe::~PmergeMe()
{
}

int PmergeMe::get_N()
{
    return this->N;
}

void PmergeMe::print_data()
{
    std::vector<int> sorted_vec = vec;

	std::cout << "Before:";
	for (unsigned i = 0; i < this->N; i++)
	{
		std::cout << " " << sorted_vec[i];
	}
	std::cout << std::endl;
}

//Vector sort

static std::vector<int> mergeVecs(std::vector<int>& left, std::vector<int>& right)
{
    std::vector<int> result;

    // Comparamos el primero del left con el del right hasta que quede alguno vacio
    while (!left.empty() && !right.empty())
	{
        if (left.front() <= right.front())
		{
            result.push_back(left.front());
            left.erase(left.begin());
        }
		else
		{
            result.push_back(right.front());
            right.erase(right.begin());
        }
    }

    // Completamos con los que hayan quedado
    while (!left.empty())
	{
        result.push_back(left.front());
        left.erase(left.begin());
    }

    while (!right.empty())
	{
        result.push_back(right.front());
        right.erase(right.begin());
    }
    return result;
}

static std::vector<int> mergeInsertVec(std::vector<int> vec) {
    if (vec.size() <= 1) {
        return vec;
    }

    // Dividimos en 2 de manera recursiva
    int mid = vec.size() / 2;
    std::vector<int> left(vec.begin(), vec.begin() + mid);
    std::vector<int> right(vec.begin() + mid, vec.end());

    left = mergeInsertVec(left);
    right = mergeInsertVec(right);

    // Unimos las 2 mitades y aprovechamos la union para ordenar
    return mergeVecs(left, right);
}

void    PmergeMe::vector_algorithm()
{
	this->vec = mergeInsertVec(this->vec);
	std::cout << "After std::vector : ";
    for (unsigned i = 0; i < this->N; i++)
	{
		std::cout << " " << this->vec[i];
	}
	std::cout << std::endl;
}

// List sort

static std::list<int> mergeLists(std::list<int>& left, std::list<int>& right)
{
    std::list<int> result;

    // Comparamos el primero del left con el del right hasta que quede alguno vacio
    while (!left.empty() && !right.empty())
	{
        if (left.front() <= right.front())
		{
            result.push_back(left.front());
            left.erase(left.begin());
        }
		else
		{
            result.push_back(right.front());
            right.erase(right.begin());
        }
    }

  	// Completamos con los que hayan quedado
    while (!left.empty())
	{
        result.push_back(left.front());
        left.erase(left.begin());
    }

    while (!right.empty())
	{
        result.push_back(right.front());
        right.erase(right.begin());
    }
    return result;
}

static std::list<int> mergeInsertList(std::list<int> lst) {
    if (lst.size() <= 1) {
        return lst;
    }

    // Dividimos en 2 de forma recursiva
    int mid = lst.size() / 2;
	std::list<int> left;
	std::list<int> right;

    for (int i = 0; i < mid; i++) {
        left.push_back(lst.front());
        lst.pop_front();
    }
    right = lst;

    left = mergeInsertList(left);
    right = mergeInsertList(right);

	// Unimos las 2 mitades y aprovechamos la union para ordenar
    return mergeLists(left, right);
}

void    PmergeMe::list_algorithm()
{
	this->lst = mergeInsertList(this->lst);
	std::cout << "After std::list : ";
    for (std::list<int>::iterator it = this->lst.begin(); it != this->lst.end(); it++)
	{
		std::cout << " " << *it;
	}
	std::cout << std::endl;
}