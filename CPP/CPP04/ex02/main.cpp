/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 09:39:40 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/22 16:12:16 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"

int main(void)
{    
    const AAnimal* j = new Dog();
    const AAnimal* i = new Cat();
    std::cout << std::endl;
    delete j;//should not create a leak
    delete i;
    //...
	std::cout << std::endl;
	Dog basic;
	{
		Dog tmp = basic;
	}

	//Descomentar para ver que no funciona
	//AAnimal a = AAnimal();
    return (0);
}
