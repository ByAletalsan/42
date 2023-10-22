/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:39:04 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 18:26:48 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character()
{
	this->name = "";
	for (int i = 0; i < 4; i++)
		this->inventory[i] = NULL;
	std::cout << "Created Character default!" << std::endl;
}

Character::Character( const std::string &name )
{
	this->name = name;
	for (int i = 0; i < 4; i++)
		this->inventory[i] = NULL;
	std::cout << "Created Character " << this->name << "!" << std::endl;
}

Character::Character( const Character &c )
{
	this->name = c.name;
	for (int i = 0; i < 4; i++)
		this->inventory[i] = c.inventory[i]->clone();
	std::cout << "Created copy Character " << this->name << "!" << std::endl;
}

Character::~Character()
{
	for (int i = 0; i < 4; i++)
		if (this->inventory[i])
			delete this->inventory[i];
	std::cout << "Destroyed Character " << this->name << "!" << std::endl;
}

Character& Character::operator=( const Character &c )
{
	if (this != &c)
	{
		this->name = c.name;
		for (int i = 0; i < 4; i++)
			this->inventory[i] = c.inventory[i]->clone();
	}
	std::cout << "Created copy Character " << this->name << "!" << std::endl;
	return (*this);
}

std::string const &Character::getName() const
{
	return (this->name);
}

void Character::equip(AMateria* m)
{
	for (int i = 0; i < 4; i++)
	{
		if (!this->inventory[i])
		{
			this->inventory[i] = m;
			std::cout << "Character " << this->name << " equipped with " << m->getType() << std::endl;
			return ;
		}
	}
	std::cout << "Character " << this->name << " can't equip " << m->getType() << std::endl;
}

void Character::unequip(int idx)
{
	if (this->inventory[idx])
	{
		std::cout << "Character " << this->name << " dropped " << this->inventory[idx]->getType() << std::endl;
		delete this->inventory[idx];
		return ;
	}
	std::cout << "Character " << this->name << " can't dropped" << std::endl;
}

void Character::use(int idx, ICharacter& target)
{
	if (this->inventory[idx])
	{
		this->inventory[idx]->use(target);
		std::cout << "Character " << this->name << " use " << this->inventory[idx]->getType() << std::endl;
		return ;
	}
	std::cout << "Character " << this->name << " can't use it" << std::endl;
}
