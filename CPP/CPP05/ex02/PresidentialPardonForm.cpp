/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:20:46 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/03 18:25:02 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardonForm", 25, 5), target("")
{
	std::cout << "Created PresidentialPardonForm default! -> target = ''" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm( const std::string target ) : AForm("PresidentialPardonForm", 25, 5), target(target)
{
	std::cout << "Created PresidentialPardonForm! -> target = " << this->target << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm( const PresidentialPardonForm &s ) : AForm(s), target(s.target)
{
	std::cout << "Created copy PresidentialPardonForm! -> target = " << this->target << std::endl;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << "Destroyed PresidentialPardonForm! -> target = " << this->target << std::endl;
}


PresidentialPardonForm &PresidentialPardonForm::operator=( const PresidentialPardonForm &s )
{
	if (this != &s)
		(std::string) this->target = s.target;
	return (*this);
}

void	PresidentialPardonForm::execute( Bureaucrat const &executor ) const
{
	if (!this->getSign())
		throw AForm::NotSignedException();
	if (executor.getGrade() > this->getGradeExec())
		throw AForm::GradeTooLowException();
	std::cout << this->target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}
