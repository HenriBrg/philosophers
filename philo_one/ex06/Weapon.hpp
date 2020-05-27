/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 23:29:04 by henri             #+#    #+#             */
/*   Updated: 2020/04/05 21:54:03 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Créez une classe Weapon comportant une chaîne type et un getType renvoyant une
référence const à cette chaîne.
Ajoutez également un setType.
*/

#ifndef WEAPON_HPP
# define WEAPON_HPP


# include <string>
# include <iostream>

class Weapon {
	public:
		Weapon(std::string const &type);
		const std::string  &getType(void) const;
		void		setType(std::string const &type);
	private:
		std::string type;
};

#endif
