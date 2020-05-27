/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sed.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 00:05:56 by henri             #+#    #+#             */
/*   Updated: 2020/04/06 16:20:58 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SED_HPP
# define SED_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>

class Sed {
	public:
		static void substitute(const std::string &file, const std::string &search, const std::string &replace);
	private:
		static std::string replace(const std::string &line, const std::string &search, const std::string &replace);
};

#endif
