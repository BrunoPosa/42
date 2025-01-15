/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:25:22 by bposa             #+#    #+#             */
/*   Updated: 2025/01/15 02:04:48 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.class.hpp"
#include "PhoneBook.class.hpp"
#include <iostream>
#include <csignal>
#include <array>
#include <cstring>
#include <limits>

void sig_exit(int sig)
{
	std::exit(sig);
}

bool	do_cmd(PhoneBook& phonebook, std::array<char, 1024>& input)
{
	if (std::strcmp(input.data(), "ADD") == 0 && phonebook.add_contact() == false)
	{
		std::cout << "Fatal error! Closing.." << std::endl;
		return (false);
	}
	else if (std::strcmp(input.data(), "SEARCH") == 0)
	{
		phonebook.search();
	}
	return (true);
}

int	main (void)
{
	std::array<char, 1024>	input;
	PhoneBook				phonebook;

	input.fill(0);
	std::signal(SIGINT, sig_exit);
	std::signal(SIGQUIT, sig_exit);

	std::cout << "==== Awesome PhoneBook V.1 ====" << std::endl
			<< "Up to " << PHONEBOOK_SIZE << " contacts with "
			<< MAIN_INPUT_BUFFER_SIZE << "-byte fields" << std::endl
			<< "Each contact's fields are:" << std::endl
			<< "first name, last name, nickname, phone number, darkest secret" << std::endl;

	while (std::strcmp(input.data(), "EXIT") != 0)
	{
		input.fill(0);
		std::cout << YELLOW_CLR << "ADD, SEARCH, or EXIT:\n" << RESET_CLR;
		std::cin.getline(input.data(), input.size());
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Input line limit is " << MAIN_INPUT_BUFFER_SIZE << " bytes!\n";
		}
		if (do_cmd(phonebook, input) == false)
			return (1);
	}
	return (0);
}