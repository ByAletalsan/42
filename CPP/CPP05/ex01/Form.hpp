/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:32:27 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 19:59:25 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"
#include <iostream>

class Bureaucrat;

class Form
{
	private:
		const std::string	name;
		bool				sign;
		const int			gradeSign;
		const int			gradeExec;
	public:
		Form();
		Form( const std::string &name, const int gradeSign, const int gradeExec );
		Form( const Form &f );
		~Form();
		Form &operator=( const Form &f );

		//Getters
		std::string	getName() const;
		bool		getSign() const;
		int			getGradeSign() const;
		int			getGradeExec() const;

		void	beSigned( const Bureaucrat &b );

		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw() { return "Grade too high"; }
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw() { return "Grade too low"; }
		};
};

std::ostream	&operator<<( std::ostream &out, const Form &f );

#endif
