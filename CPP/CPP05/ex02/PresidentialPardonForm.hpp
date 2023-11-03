/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:20:44 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/03 18:21:59 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private:
		const std::string	target;
	public:
		PresidentialPardonForm();
		PresidentialPardonForm( const std::string target );
		PresidentialPardonForm( const PresidentialPardonForm &r );
		~PresidentialPardonForm();

		PresidentialPardonForm &operator=( const PresidentialPardonForm &r );

		void	execute( Bureaucrat const &executor ) const;
};

#endif
