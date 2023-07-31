/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 07:24:01 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/09 07:51:49 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include "Brain.hpp"

class Animal
{
    protected:
        std::string type;

    public:
        Animal();
        Animal( const Animal &a );
        virtual ~Animal();

        virtual Animal& operator=( const Animal &a );

        const std::string &getType() const;
        virtual void makeSound() const;
        virtual Brain* getBrain() const;
};

#endif