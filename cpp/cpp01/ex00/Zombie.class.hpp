/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 01:25:30 by bposa             #+#    #+#             */
/*   Updated: 2025/01/18 19:43:49 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_CLASS_HPP
# define ZOMBIE_CLASS_HPP

#include <iostream>

class Zombie
{
	std::string	_name;

public:
	Zombie(std::string name);
	~Zombie();

	void		announce(void);
	Zombie*		newZombie(std::string name);
	void		randomChump(std::string name);
};

#endif
