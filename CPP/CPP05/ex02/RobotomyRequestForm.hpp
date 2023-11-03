/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:54:59 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/03 18:16:19 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
	private:
		const std::string	target;
	public:
		RobotomyRequestForm();
		RobotomyRequestForm( const std::string target );
		RobotomyRequestForm( const RobotomyRequestForm &r );
		~RobotomyRequestForm();

		RobotomyRequestForm &operator=( const RobotomyRequestForm &r );

		void	execute( Bureaucrat const &executor ) const;
};

#endif
