/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 07:13:22 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/04 07:53:34 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << argv[0] << " ['DEBUG', 'INFO', 'WARNING', 'ERROR']" <<std::endl;
        return (1);
    }
    Harl harl;
    harl.complain(argv[1]);
    return (0);
}
