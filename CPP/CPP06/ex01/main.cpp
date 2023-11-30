/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:58:00 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/30 18:06:23 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int	main()
{
	Data *data_original = new(Data);
    Data *data_deserialized;
    uintptr_t data_serialized;

    data_original->name = "Dario";
    data_original->age = 50;
    std::cout << "Name: " <<  data_original->name << std::endl;
    std::cout << "Age: " <<  data_original->age << std::endl;

	std::cout << std::endl;

    std::cout << "Original: " << data_original << std::endl;
    data_serialized = Serializer::serialize(data_original);
    std::cout << "Serialized to uint: " << data_serialized << std::endl;
    data_deserialized = Serializer::deserialize(data_serialized);
    std::cout << "Deserialized to data: " << data_deserialized << std::endl;

	std::cout << std::endl;

	std::cout << "Name: " <<  data_deserialized->name << std::endl;
    std::cout << "Age: " <<  data_deserialized->age << std::endl;
	return 0;
}