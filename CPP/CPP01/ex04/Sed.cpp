/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sed.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 06:25:11 by atalaver          #+#    #+#             */
/*   Updated: 2023/07/04 07:09:41 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sed.hpp"

Sed::Sed(std::string file_in)
{
    this->file_in = file_in;
    this->file_out = file_in + ".replace";
}

const void  Sed::replace(std::string find, std::string replace)
{
    if (find == "" || replace == "")
    {
        std::cout << "Empty arguments invalid!" << std::endl;
        return ;
    }
    std::ifstream read(this->file_in);
    if (!read.good())
    {
        std::cout << "Not file exist" << std::endl;
        return ;
    }
    std::string buffer;
    getline(read, buffer, '\0');
    if (buffer.empty())
    {
        std::cout << this->file_in << " is empty" << std::endl;
        read.close();
        return ;
    }
    std::ofstream write(this->file_out);
    if (!write.good())
    {
        read.close();
        std::cout << "Can't create file out" << std::endl;
        return ;
    }
    size_t  pos;
    pos = buffer.find(find);
    while (pos != std::string::npos)
    {
        buffer.erase(pos, find.length());
        buffer.insert(pos, replace);
        pos = buffer.find(find);
    }
    write << buffer;
    read.close();
    write.close();
    std::cout << "SUCCESS!" << std::endl;
}
