/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:16:34 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 20:10:28 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main()
{
	try {
        Bureaucrat bureaucrat("PACO",11);
        Form form("FORMULARIO_PEPE", 10, 10);
        bureaucrat.signForm(form);
        std::cout << form << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
	std::cout << std::endl;
	try {
        Bureaucrat bureaucrat("JUAN",9);
        Form form("FORMULARIO_PEPE", 10, 10);
        bureaucrat.signForm(form);
        std::cout << form << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
	std::cout << std::endl;
	try {
        Bureaucrat bureaucrat("JUAN",9);
        Form form("FORMULARIO_PEPE", 151, 10);
        bureaucrat.signForm(form);
        std::cout << form << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
	return 0;
}