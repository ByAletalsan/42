/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 05:16:55 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/04 05:21:56 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(const std::string value)
{
    this->type = value;
}

const std::string&  Weapon::getType()
{
    return (this->type);
}

void    Weapon::setType(const std::string value)
{
    this->type = value;
}
