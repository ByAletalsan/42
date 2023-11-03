/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inter.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:42:51 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/03 18:59:43 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern()
{
	std::cout << "Default Intern created!" << std::endl;
}

Intern::Intern( const Intern &i )
{
	(void)i;
	std::cout << "Copy Intern created!" << std::endl;
}

Intern::~Intern()
{
	std::cout << "Destroy Intern!" << std::endl;
}


Intern &Intern::operator=( const Intern &i )
{
	(void)i;
	return (*this);
}

static AForm	*makePresident(const std::string target)
{
	return (new PresidentialPardonForm(target));
}

static AForm	*makeRobot(const std::string target)
{
	return (new RobotomyRequestForm(target));
}

static AForm	*makeShrubbery(const std::string target)
{
	return (new ShrubberyCreationForm(target));
}

AForm	*Intern::makeForm( const std::string name, const std::string target )
{
	std::string	formNames[] = {
        "robotomy request",
        "presidential pardon",
        "shrubbery creation"
    };
    AForm*	(*forms[])(const std::string) = {
        &makeRobot,
        &makePresident,
        &makeShrubbery
    };
    for ( int i = 0; i < 3; i++ ) {
        if ( name == formNames[i] ) {
            std::cout << "Intern creates " << name << std::endl;
			return (forms[i](target));
        }
    }
    std::cout << "Intern cannot create " << name << " form" << std::endl;
    return (NULL);
}
