/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:32:27 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 19:59:25 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

#include "Bureaucrat.hpp"
#include <iostream>

class Bureaucrat;

class AForm
{
	private:
		const std::string	name;
		bool				sign;
		const int			gradeSign;
		const int			gradeExec;
	public:
		AForm();
		AForm( const std::string &name, const int gradeSign, const int gradeExec );
		AForm( const AForm &f );
		virtual ~AForm();
		AForm &operator=( const AForm &f );

		//Getters
		std::string	getName() const;
		bool		getSign() const;
		int			getGradeSign() const;
		int			getGradeExec() const;

		void			beSigned( const Bureaucrat &b );
		virtual void	execute( Bureaucrat const &executor ) const = 0;

		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw() { return "Grade too high"; }
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw() { return "Grade too low"; }
		};
		class NotSignedException : public std::exception {
			public:
				virtual const char* what() const throw() { return "Form not signed"; }
		};
};

std::ostream	&operator<<( std::ostream &out, const AForm &f );

#endif
