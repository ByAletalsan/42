/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:03:03 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/03 17:51:12 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm
{
	private:
		const std::string	target;
	public:
		ShrubberyCreationForm();
		ShrubberyCreationForm( const std::string target );
		ShrubberyCreationForm( const ShrubberyCreationForm &s );
		~ShrubberyCreationForm();

		ShrubberyCreationForm &operator=( const ShrubberyCreationForm &s );

		void	execute( Bureaucrat const &executor ) const;
};

#endif
