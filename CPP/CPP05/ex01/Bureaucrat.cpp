/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:00:23 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 20:02:20 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("Default"), grade(150)
{
	std::cout << "Created Bureaucrat default!" << std::endl;
}

Bureaucrat::Bureaucrat( const std::string &name, int grade ) : name(name), grade(grade)
{
	if (this->grade < 1)
    	throw Bureaucrat::GradeTooHighException();
	if (this->grade > 150)
    	throw Bureaucrat::GradeTooLowException();
	std::cout << "Created Bureaucrat " << this->name << std::endl;
}

Bureaucrat::Bureaucrat( const Bureaucrat &b ) : name(b.getName()), grade(b.getGrade())
{
	std::cout << "Created copy Bureaucrat " << this->name << std::endl;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Destroyed Bureaucrat " << this->name << std::endl;
}

Bureaucrat &Bureaucrat::operator=( const Bureaucrat &b )
{
	if (this != &b)
	{
		(std::string) this->name = b.getName();
		this->grade = b.getGrade();
	}
	std::cout << "Created (by =) Bureaucrat " << this->name << std::endl;
	return (*this);
}

std::string	Bureaucrat::getName() const
{
	return (this->name);
}

int			Bureaucrat::getGrade() const
{
	return (this->grade);
}

void        Bureaucrat::incrementGrade()
{
	if (this->grade - 1 < 1)
		throw Bureaucrat::GradeTooHighException();
	this->grade -= 1;
}

void        Bureaucrat::decrementGrade()
{
	if (this->grade + 1 > 150)
		throw Bureaucrat::GradeTooLowException();
	this->grade += 1;
}

void		Bureaucrat::signForm( Form &f )
{
	try
	{
		f.beSigned(*this);
		std::cout << *this << " signed " << f << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << *this << " couldn't sign " << f << " beacuse " << e.what() << std::endl;
	}
	
}

std::ostream	&operator<<( std::ostream &out, const Bureaucrat &b )
{
	out << b.getName() << ", bureaucrat grade " << b.getGrade();
	return out; 
}