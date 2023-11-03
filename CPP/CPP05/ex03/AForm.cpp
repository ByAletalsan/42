/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:40:29 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 20:09:09 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm() : name("Default"), sign(false), gradeSign(150), gradeExec(150)
{
	std::cout << "Created AForm default!" << std::endl;
}

AForm::AForm( const std::string &name, const int gradeSign, const int gradeExec ) : name(name), sign(false), gradeSign(gradeSign), gradeExec(gradeExec)
{
	if (this->gradeSign < 1)
		throw AForm::GradeTooHighException();
	if (this->gradeSign > 150)
    	throw AForm::GradeTooLowException();
	if (this->gradeExec < 1)
		throw AForm::GradeTooHighException();
	if (this->gradeExec > 150)
    	throw AForm::GradeTooLowException();
	std::cout << "Created AForm " << this->name << std::endl;
}

AForm::AForm( const AForm &f ) : name(f.getName()), sign(f.getSign()), gradeSign(f.getGradeSign()), gradeExec(f.getGradeExec())
{
	std::cout << "Created copy AForm " << this->name << std::endl;
}

AForm::~AForm()
{
	std::cout << "Destroyed AForm " << this->name << std::endl;
}

AForm &AForm::operator=( const AForm &f )
{
	if (this != &f)
	{
		(std::string) this->name = f.getName();
		this->sign = f.getSign();
	}
	std::cout << "Created (by =) AForm " << this->name << std::endl;
	return (*this);
}


//Getters
std::string	AForm::getName() const
{
	return (this->name);
}

bool		AForm::getSign() const
{
	return (this->sign);
}

int			AForm::getGradeSign() const
{
	return (this->gradeSign);
}

int			AForm::getGradeExec() const
{
	return (this->gradeExec);
}


void	AForm::beSigned( const Bureaucrat &b )
{
	if (b.getGrade() > this->gradeSign)
		throw AForm::GradeTooLowException();
	this->sign = true;
}

std::ostream	&operator<<( std::ostream &out, const AForm &f )
{
	out << "[ AForm Name: " << f.getName() << std::flush;
	out << " ; Signed: " << f.getSign() << std::flush;
	out << " ; Grade to sign: " << f.getGradeSign() << std::flush;
	out << " ; Grade to execute: " << f.getGradeExec() << " ]";
	return (out);
}
