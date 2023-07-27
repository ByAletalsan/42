/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 07:34:53 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/09 08:17:12 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
    private:
        Brain *brain;

    public:
        Dog();
        Dog( const Dog &d );
        ~Dog();

        Dog& operator=( const Dog &d );
        Animal& operator=( Animal const &a );

        void makeSound() const;

        Brain* getBrain() const;
};

#endif
