/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:16:34 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 19:24:00 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main()
{
	try
	{
		Bureaucrat paco = Bureaucrat("PACO", 2);
		std::cout << paco << std::endl;
		paco.incrementGrade();
		std::cout << paco << std::endl;
		paco.incrementGrade();
		std::cout << paco << std::endl;
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		Bureaucrat paco = Bureaucrat("PACO", 151);
		std::cout << paco << std::endl;
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		Bureaucrat paco = Bureaucrat();
		paco.decrementGrade();
		std::cout << paco << std::endl;
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}