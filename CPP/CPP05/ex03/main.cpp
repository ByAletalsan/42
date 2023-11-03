/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:16:34 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/03 19:00:50 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main( void )
{
    {
        Intern someRandomIntern;
        AForm* rrf;
        rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        delete rrf;
    }
    std::cout << std::endl;
    try {
        Bureaucrat bureaucrat("ash", 2);
        ShrubberyCreationForm form1("prueba");
        RobotomyRequestForm form2("robot");
        PresidentialPardonForm form3("president");

        std::cout << "\n--------------- Form 1 ( Shrubbery ) ---------------" << std::endl;
        bureaucrat.signForm(form1);
        bureaucrat.executeForm(form1);
        
        std::cout << "\n--------------- Form 2 ( Robotomy ) ---------------" << std::endl;
        bureaucrat.signForm(form2);
        bureaucrat.executeForm(form2);
        bureaucrat.executeForm(form2);
        bureaucrat.executeForm(form2);
        bureaucrat.executeForm(form2);

        std::cout << "\n--------------- Form 3 ( President ) ---------------" << std::endl;
        bureaucrat.signForm(form3);
        bureaucrat.executeForm(form3);

        std::cout << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return (0);
}