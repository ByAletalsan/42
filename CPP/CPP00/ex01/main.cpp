/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 08:24:18 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/11 18:15:09 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int main(void)
{
    PhoneBook   agenda;
    int         option;

    do
    {
        agenda.print_menu();
        option = agenda.select_option(agenda.ft_getline("> "));
        switch (option)
        {
            case 1:
                agenda.addContact();
                break;

            case 2:
                agenda.search();
                break;
        }
    } while (option != 3);
    
}
