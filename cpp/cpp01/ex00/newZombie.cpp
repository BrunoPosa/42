/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:36:21 by bposa             #+#    #+#             */
/*   Updated: 2025/01/18 19:36:35 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.class.hpp"

Zombie*	Zombie::newZombie(std::string name)
{
	Zombie*	zombie = new (std::nothrow) Zombie(name);
	if (zombie == nullptr)
		std::cout << name << " was not created due to malloc fail!" << std::endl;
	return (zombie);
}