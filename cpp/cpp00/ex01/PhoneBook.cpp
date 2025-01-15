/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:00:01 by bposa             #+#    #+#             */
/*   Updated: 2025/01/15 02:30:45 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.class.hpp"
#include <cstring>
#include <iomanip>
#include <limits>

PhoneBook::PhoneBook() : _index(0), _size(0) {};

bool	PhoneBook::add_field(std::string& field, const std::string& label)
{

	while (field.length() > MAIN_INPUT_BUFFER_SIZE || field.length() == 0)
	{
		if (std::cin.fail() == true && (field.length() <= MAIN_INPUT_BUFFER_SIZE && field.length() != 0))
		{
			std::cin.clear();
			return (false);
		}
		std::cin.clear();
		std::cout << "Entry " << 1 + (_index % PHONEBOOK_SIZE)
				<< " - Type " << label << ":" << std::endl;
		std::getline(std::cin, field);
	}
	return (true);
}

bool	PhoneBook::add_contact(void)
{
	std::string	first, last, nick, phone, secret;

	if (!add_field(first, "First Name") || 
		!add_field(last, "Last Name") || 
		!add_field(nick, "Nickname") || 
		!add_field(phone, "Phone Number") || 
		!add_field(secret, "Darkest Secret"))
		return false;

	_contacts[toIndex()] = Contact(first, last, nick, phone, secret);
	if (getSize() != PHONEBOOK_SIZE)
		setSize(getSize() + 1);
	return (true);
}

/*
Todo: check for valid numbers both in index, and in phone number z
*/
bool	PhoneBook::search(void)
{
	std::string		input = "";
	unsigned int	selection = 0;
	unsigned int	inputTryCount = 0;

	//show existing contacts line by line, with their index
	for (unsigned int i = 0; i < getSize(); i++)
	{
		std::cout << std::setw(CONTACT_COLUMN_WIDTH) << i + 1 << "|";
		_contacts[i].showContactRow();
	}
	std::cout << std::endl << "Enter index of contact to display (out of " << _index << "):" << std::endl;
	while (true)
	{
		if (inputTryCount >= MAIN_TRIES_MAX || _inputFromStdin(input) == false)
			return (false);
		if (_isValidNumber(input, selection) == true && selection != 0 && selection <= getSize())
			break ;
		else
		{
			std::cout << "Selection does not exist! " << "(attempt " << inputTryCount + 1
			<< " of " << MAIN_TRIES_MAX << ")" << std::endl;
			inputTryCount++;
		}
	}

	_contacts[selection - 1].showContactPage();

	return (true);
}

bool	PhoneBook::_inputFromStdin(std::string& inputStr)
{
	unsigned int	inputTryCount = 0;

	while (!std::getline(std::cin, inputStr) && inputTryCount < MAIN_TRIES_MAX)
	{
		if (std::cin.eof() == true)
		{
			std::cerr << "EOF detected." << std::endl;
			return (false);
		}
		else
		{
			std::cerr << "Input error." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		inputTryCount++;
	}
	if (inputTryCount >= MAIN_TRIES_MAX)
	{
		std::cout << "Fatal input error! Exiting.." << std::endl;
		return (false);
	}
	return (true);
}

bool	PhoneBook::_isValidNumber(const std::string& inputStr, unsigned int& result)
{
	std::stringstream	ss(inputStr);
	unsigned int		num;

	ss >> num;
	if (ss.fail() || !ss.eof())
		return (false);
	result = num;
	return (true);
}

unsigned int	PhoneBook::toIndex(void)
{
	if (_index == PHONEBOOK_SIZE)
		_index = 0;
	return (_index++);
}

unsigned int	PhoneBook::getSize(void)
{
	return (_size);
}

void	PhoneBook::setSize(unsigned int newSize)
{
	_size = newSize;
}