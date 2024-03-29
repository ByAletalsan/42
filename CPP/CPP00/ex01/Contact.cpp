/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 07:52:05 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/11 18:37:53 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact()
{
	this->first_name = "";
	this->last_name = "";
	this->nickname = "";
	this->phone_number = "";
	this->darkest_secret = "";
}

//setters
void	Contact::setFirstName(const std::string &first_name)
{
	this->first_name = first_name;
}

void	Contact::setLastName(const std::string &last_name)
{
	this->last_name = last_name;
}

void	Contact::setNickname(const std::string &nickname)
{
	this->nickname = nickname;
}

void	Contact::setPhoneNumber(const std::string &phone_number)
{
	this->phone_number = phone_number;
}

void	Contact::setDarkestSecret(const std::string &darkest_secret)
{
	this->darkest_secret = darkest_secret;
}

//getter
const std::string	&Contact::getFirstName()
{
	return (this->first_name);
}

const std::string	&Contact::getLastName()
{
	return (this->last_name);
}

const std::string	&Contact::getNickname()
{
	return (this->nickname);
}

const std::string	&Contact::getPhoneNumber()
{
	return (this->phone_number);
}

const std::string	&Contact::getDarkestSecret()
{
	return (this->darkest_secret);
}

//Tools
void	Contact::reset_data()
{
	std::cout << "RESETEAMOS" << std::endl;
	this->first_name = "";
	this->last_name = "";
	this->nickname = "";
	this->phone_number = "";
	this->darkest_secret = "";
}
