/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 07:18:42 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/01 07:30:53 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

static int ft_strlen(char *s)
{
    int i = 0;
    while (s && s[i])
        i++;
    return (i);
}

static char	ft_toupper(char c)
{
	return ((c >= 'a' && c <= 'z') ? c - 32 : c);
}

static void ft_megaphone(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; j < ft_strlen(argv[i]); j++)
            std::cout << ft_toupper(argv[i][j]);
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
    else
        ft_megaphone(argc, argv);
    std::cout << std::endl;
    return (0);
}
