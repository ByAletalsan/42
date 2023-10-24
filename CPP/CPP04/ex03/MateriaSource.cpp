/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:06:15 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/24 18:39:00 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; i++)
		this->materias[i] = NULL;
	std::cout << "Created MateriaSource default!" << std::endl;
}

MateriaSource::MateriaSource( const MateriaSource &m )
{
	for (int i = 0; i < 4; i++)
		this->materias[i] = m.materias[i]->clone();
	std::cout << "Created copy MateriaSource!" << std::endl;
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < 4; i++)
		if (this->materias[i])
			delete this->materias[i];
	std::cout << "Destroyed MateriaSource!" << std::endl;
}

MateriaSource &MateriaSource::operator=( const MateriaSource &m )
{
	for (int i = 0; i < 4; i++)
		if (this->materias[i])
			delete this->materias[i];
	for (int i = 0; i < 4; i++)
		this->materias[i] = m.materias[i]->clone();
	std::cout << "Created (by =) MateriaSource!" << std::endl;
	return (*this);
}

void MateriaSource::learnMateria( AMateria* m )
{
	for (int i = 0; i < 4; i++)
	{
		if (!this->materias[i])
		{
			this->materias[i] = m;
			std::cout << "MateriaSource learned " << m->getType() << std::endl;
			return ;
		}
	}
	std::cout << "MateriaSource can't learn " << m->getType() << std::endl;
}

AMateria* MateriaSource::createMateria( std::string const &type )
{
	for (int i = 0; i < 4; i++)
        if (this->materias[i] && this->materias[i]->getType() == type)
            return this->materias[i]->clone();
    return NULL;
}
