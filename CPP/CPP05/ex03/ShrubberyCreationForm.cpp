/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationFormForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:07:34 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/03 17:24:24 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137), target("")
{
	std::cout << "Created ShrubberyCreationForm default! -> target = ''" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm( const std::string target ) : AForm("ShrubberyCreationForm", 145, 137), target(target)
{
	std::cout << "Created ShrubberyCreationForm! -> target = " << this->target << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm( const ShrubberyCreationForm &s ) : AForm(s), target(s.target)
{
	std::cout << "Created copy ShrubberyCreationForm! -> target = " << this->target << std::endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "Destroyed ShrubberyCreationForm! -> target = " << this->target << std::endl;
}


ShrubberyCreationForm &ShrubberyCreationForm::operator=( const ShrubberyCreationForm &s )
{
	if (this != &s)
		(std::string) this->target = s.target;
	return (*this);
}

void	ShrubberyCreationForm::execute( Bureaucrat const &executor ) const
{
	if (!this->getSign())
		throw AForm::NotSignedException();
	if (executor.getGrade() > this->getGradeExec())
		throw AForm::GradeTooLowException();
	std::ofstream	file((this->target + "_shrubbery").c_str());
	if (!file.good())
	{
		std::cout << "Error with target!" << std::endl;
		file.close();
		return ;
	}
	file << "───────────▄██▄" << std::endl;
	file << "───────────█▒▒█" << std::endl;
	file << "───────────▀██▀" << std::endl;
	file << "───────────████" << std::endl;
	file << "──────────██▓▓██" << std::endl;
	file << "─────────██▓▓▓▓██" << std::endl;
	file << "────────██▓▓O▓▓▓██" << std::endl;
	file << "───────██▓▓▓▓▓O▓▓██" << std::endl;
	file << "──────██▓▓▓O▓▓▓▓▓▓██" << std::endl;
	file << "─────██▓▓O▓▓▓▓▓▓O▓▓██" << std::endl;
	file << "────██▓▓▓▓▓▓▓O▓▓▓▓▓▓██" << std::endl;
	file << "───███████▓O▓▓▓▓▓██████" << std::endl;
	file << "───────██▓▓▓▓O▓▓▓▓██" << std::endl;
	file << "──────██▓▓▓O▓▓▓▓O▓▓██" << std::endl;
	file << "─────██▓▓O▓▓▓▓▓▓▓▓▓▓██" << std::endl;
	file << "────██▓▓▓▓▓▓O▓▓▓▓▓▓▓▓██" << std::endl;
	file << "───██▓▓O▓▓▓▓▓▓▓▓▓O▓▓▓▓██" << std::endl;
	file << "──███████████████████████" << std::endl;
	file << "─────██▓▓▓▓▓O▓▓▓O▓▓▓▓██" << std::endl;
	file << "────██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██" << std::endl;
	file << "───██▓▓▓▓O▓▓▓▓▓O▓▓▓▓▓▓▓██" << std::endl;
	file << "──██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██" << std::endl;
	file << "─██▓▓▓▓▓O▓▓▓▓O▓▓▓▓▓▓O▓▓▓▓██" << std::endl;
	file << "████████████████████████████" << std::endl;
	file << "───────────██████" << std::endl;
	file << "───────────██████" << std::endl;
	file << "───────────██████" << std::endl;
	file << "───────────██████" << std::endl;
	file << "───────────██████" << std::endl;
	file << "───────────██████" << std::endl;
	file << "───────────██████" << std::endl;
	file << "───────────██████" << std::endl;
	file << "───────────██████" << std::endl;
	file << "───────────██████" << std::endl;
	file << "───────────██████" << std::endl;
	file << "██████████████████████████████" << std::endl;
	file << "██████████████████████████████" << std::endl;
	file.close();
}
