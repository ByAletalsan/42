/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:58:02 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/03 18:16:07 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45), target("")
{
	std::cout << "Created RobotomyRequestForm default! -> target = ''" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm( const std::string target ) : AForm("RobotomyRequestForm", 72, 45), target(target)
{
	std::cout << "Created RobotomyRequestForm! -> target = " << this->target << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm( const RobotomyRequestForm &s ) : AForm(s), target(s.target)
{
	std::cout << "Created copy RobotomyRequestForm! -> target = " << this->target << std::endl;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << "Destroyed RobotomyRequestForm! -> target = " << this->target << std::endl;
}


RobotomyRequestForm &RobotomyRequestForm::operator=( const RobotomyRequestForm &s )
{
	if (this != &s)
		(std::string) this->target = s.target;
	return (*this);
}

void	RobotomyRequestForm::execute( Bureaucrat const &executor ) const
{
	if (!this->getSign())
		throw AForm::NotSignedException();
	if (executor.getGrade() > this->getGradeExec())
		throw AForm::GradeTooLowException();
	static int i = 0;
	if (i % 2)
		std::cout << "BZZZ!!! " << this->target << " has been robotomized!" << std::endl;
	else
		std::cout << "Robotimy failed!" << std::endl;
	i++;
	if (i > 99)
		i = 0;
}
