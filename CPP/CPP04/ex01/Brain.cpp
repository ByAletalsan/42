/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 07:02:32 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/09 07:20:59 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
    std::cout << "Brain created!" << std::endl;
}

Brain::Brain( const Brain &b )
{
    for (int i = 0; i < 100; i++)
        this->ideas[i] = b.ideas[i];
    std::cout << "Brain created by copy!" << std::endl;
}

Brain::~Brain()
{
    std::cout << "Brain destroyed!" << std::endl;
}

Brain& Brain::operator=( const Brain &b )
{
    if (this != &b)
    {
        for (int i = 0; i < 100; i++)
            this->ideas[i] = b.ideas[i];
    }
    std::cout << "Brain created (by =) by copy!" << std::endl;
    return (*this);
}
