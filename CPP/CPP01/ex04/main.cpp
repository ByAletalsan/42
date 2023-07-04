/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 06:23:09 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/04 06:24:43 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sed.hpp"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cout << argv[0] << " <file> <find> <replace>" << std::endl;
        return (1);
    }
    Sed sed(argv[1]);
    sed.replace(argv[2], argv[3]);
    return (0);
}
