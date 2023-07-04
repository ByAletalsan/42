/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 07:39:12 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/03 12:44:20 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <iomanip>
#include <limits>

class Contact
{
    private:
        std::string	first_name;
        std::string	last_name;
        std::string	nickname;
        std::string	phone_number;
        std::string	darkest_secret;

    public:
        Contact();

        //setters
        void				setFirstName(const std::string &first_name);
        void				setLastName(const std::string &last_name);
        void				setNickname(const std::string &nickname);
        void				setPhoneNumber(const std::string &phone_number);
        void				setDarkestSecret(const std::string &darkest_secret);

		//getter
		const std::string	&getFirstName();
		const std::string	&getLastName();
		const std::string	&getNickname();

		//Tools
		const void			print_contact();
		void				reset_data();

};

#endif
