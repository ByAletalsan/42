/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:40:29 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 20:09:09 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form() : name("Default"), sign(false), gradeSign(150), gradeExec(150)
{
	std::cout << "Created Form default!" << std::endl;
}

Form::Form( const std::string &name, const int gradeSign, const int gradeExec ) : name(name), sign(false), gradeSign(gradeSign), gradeExec(gradeExec)
{
	if (this->gradeSign < 1)
		throw Form::GradeTooHighException();
	if (this->gradeSign > 150)
    	throw Form::GradeTooLowException();
	if (this->gradeExec < 1)
		throw Form::GradeTooHighException();
	if (this->gradeExec > 150)
    	throw Form::GradeTooLowException();
	std::cout << "Created Form " << this->name << std::endl;
}

Form::Form( const Form &f ) : name(f.getName()), sign(f.getSign()), gradeSign(f.getGradeSign()), gradeExec(f.getGradeExec())
{
	std::cout << "Created copy Form " << this->name << std::endl;
}

Form::~Form()
{
	std::cout << "Destroyed Form " << this->name << std::endl;
}

Form &Form::operator=( const Form &f )
{
	if (this != &f)
	{
		(std::string) this->name = f.getName();
		this->sign = f.getSign();
	}
	std::cout << "Created (by =) Form " << this->name << std::endl;
	return (*this);
}


//Getters
std::string	Form::getName() const
{
	return (this->name);
}

bool		Form::getSign() const
{
	return (this->sign);
}

int			Form::getGradeSign() const
{
	return (this->gradeSign);
}

int			Form::getGradeExec() const
{
	return (this->gradeExec);
}


void	Form::beSigned( const Bureaucrat &b )
{
	if (b.getGrade() > this->gradeSign)
		throw Form::GradeTooLowException();
	this->sign = true;
}

std::ostream	&operator<<( std::ostream &out, const Form &f )
{
	out << "[ Form Name: " << f.getName() << std::flush;
	out << " ; Signed: " << f.getSign() << std::flush;
	out << " ; Grade to sign: " << f.getGradeSign() << std::flush;
	out << " ; Grade to execute: " << f.getGradeExec() << " ]";
	return (out);
}
