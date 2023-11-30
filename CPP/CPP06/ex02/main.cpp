/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:22:04 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/30 18:44:14 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime> 

Base*	generate()
{
    int n = std::rand() % 3;

    if (n == 0)
        return (new A());
    if (n == 1)
        return (new B());
    return (new C());
}

void	identify(Base* p)
{
	if (dynamic_cast<A*>(p) != NULL)
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p) != NULL)
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p) != NULL)
        std::cout << "C" << std::endl;
    else
        std::cout << "Couldn't identify any class!" << std::endl;
}

void	identify(Base& p)
{
	try
    {
        A& iA = dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        (void)iA;
		return ;
    }
    catch( std::exception& ex) {}
    try
    {
        B& iB = dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        (void)iB;
		return ;
    }
    catch( std::exception& ex) {}
    try
    {
        C& iC = dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        (void)iC;
		return ;
    }
    catch( std::exception& ex) {}
	std::cout << "Couldn't identify any class!" << std::endl;
}

int	main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL) + 42));

	Base* a = NULL;

	identify(a);
	identify(*a);

	Base* b = generate();

    //Passing pointer to identify
    identify(b);
	delete b;

	Base* c = generate();

    //Passing reference to identyfy
    identify(*c);
	delete c;

	return (0);
}