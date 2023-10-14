/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 07:34:21 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/11 18:34:23 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
    private:
        Contact             contacts[8];
        int                 size;
		const void          print_list();
        const std::string	print_with_len(const std::string &s);
        void                print_contact(int n);

    public:
        PhoneBook();

        const std::string   ft_getline(const std::string &s);
        void                addContact();
        const void          print_menu();
		const void          search();
        const int		    select_option(const std::string &s);
};

#endif