/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 08:20:46 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/11 18:37:37 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
    this->size = 0;
}

const std::string   PhoneBook::ft_getline(const std::string &s)
{
    std::string  aux;

    std::cout << s;
    getline(std::cin, aux);
    while (aux.empty())
    {
        std::cout << s;
        getline(std::cin, aux);
    }
    return (aux);
}

void    PhoneBook::addContact()
{
    // if (this->size >= 1)
    //     this->contacts[this->size].reset_data();
	if (size >= 8)
		size--;
    this->contacts[this->size].setFirstName(this->ft_getline("First Name: "));
    this->contacts[this->size].setLastName(this->ft_getline("Last Name: "));
    this->contacts[this->size].setNickname(this->ft_getline("Nickname: "));
    this->contacts[this->size].setPhoneNumber(this->ft_getline("Phone Number: "));
    this->contacts[this->size].setDarkestSecret(this->ft_getline("Darkest Secret: "));
	this->size++;
}

const std::string	PhoneBook::print_with_len(const std::string &s)
{
	if (s.length() > 10)
        return s.substr(0, 9) + ".";
    return (s);
}

const void    PhoneBook::print_list()
{
	std::cout << std::endl;
	std::cout << "|" << std::setw(10) << "ID" << std::flush;
	std::cout << "|" << std::setw(10) << "FIRST NAME" << std::flush;
	std::cout << "|" << std::setw(10) << "LAST NAME" << std::flush;
	std::cout << "|" << std::setw(10) << "NICKNAME" << std::flush;
	std::cout << "|" << std::endl;
    for (int i = 0; i < this->size; i++)
    {
        std::cout << "|" << std::setw(10) << i << std::flush;
        std::cout << "|" << std::setw(10) << this->print_with_len(contacts[i].getFirstName()) << std::flush;
        std::cout << "|" << std::setw(10) << this->print_with_len(contacts[i].getLastName()) << std::flush;
        std::cout << "|" << std::setw(10) << this->print_with_len(contacts[i].getNickname()) << std::flush;
        std::cout << "|" << std::endl;
    }
	std::cout << std::endl;
}

void	PhoneBook::print_contact(int n)
{
	std::cout << "First Name: " << this->contacts[n].getFirstName() << std::endl;
	std::cout << "Last Name: " << this->contacts[n].getLastName() << std::endl;
	std::cout << "Nickname: " << this->contacts[n].getNickname() << std::endl;
	std::cout << "Phone Number: " << this->contacts[n].getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << this->contacts[n].getDarkestSecret() << std::endl;
}

const void	PhoneBook::search()
{
	int	option;

	if (!size)
	{
		std::cout << "Phone Book empty!" << std::endl;
		return ;
	}
	this->print_list();
	std::cout << "ID > " << std::flush;
	std::cin >> option;
	if (!std::cin.good() || ((option < 0 || option >= size)))
	{
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		std::cout << "Invalid option!" << std::endl;
		return ;
	}
	print_contact(option);
	std::cin.ignore();
}
const void    PhoneBook::print_menu()
{
    std::cout << std::endl;
    std::cout << "<----------PHONEBOOK---------->" << std::endl;
    std::cout << "ADD: Add new contact" << std::endl;
    std::cout << "SEARCH: Search contact" << std::endl;
    std::cout << "EXIT: Quit" << std::endl;
    std::cout << std::endl;
}

const int	PhoneBook::select_option(const std::string &s)
{
	if (s == "ADD")
		return (1);
	if (s == "SEARCH")
		return (2);
	if (s == "EXIT")
		return (3);
	std::cout << "Option not valid" << std::endl;
	return (0);
}
