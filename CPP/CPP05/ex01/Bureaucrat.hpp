/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:48:43 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 20:00:23 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include "Form.hpp"

class Form;

class Bureaucrat
{
	private:
		const std::string	name;
		int					grade;
	public:
		Bureaucrat();
		Bureaucrat( const std::string &name, int grade );
		Bureaucrat( const Bureaucrat &b );
		~Bureaucrat();
		Bureaucrat &operator=( const Bureaucrat &b );

		std::string	getName() const;
		int			getGrade() const;

		void        incrementGrade();
    	void        decrementGrade();

		void		signForm( Form &f );

		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw() { return "Grade too high"; }
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw() { return "Grade too low"; }
		};
};

std::ostream	&operator<<( std::ostream &out, const Bureaucrat &b );

#endif
