/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:59:56 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/03 13:05:38 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(void)
{
    std::string s = "HI THIS IS BRAIN";
    std::string *stringPTR = &s;
    std::string &stringREF = s;
    
    std::cout << "Direccion memoria S: " << &s << std::endl;
    std::cout << "Direccion memoria stringPTR: " << stringPTR << std::endl;
    std::cout << "Direccion memoria stringREF: " << &stringREF << std::endl;

    std::cout << std::endl;

    std::cout << "Valor de S:" << s << std::endl;
    std::cout << "Valor de stringPRT:" << *stringPTR << std::endl;
    std::cout << "Valor de stringREF:" << stringREF << std::endl;

    return (0);
}
