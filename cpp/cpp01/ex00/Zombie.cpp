/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 01:25:56 by bposa             #+#    #+#             */
/*   Updated: 2025/01/18 01:38:37 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.class.hpp"

void    Zombie::announce(void)
{
    std::cout << _name << ":" << ": BraiiiiiiinnnzzzZ..." << std::endl;
}