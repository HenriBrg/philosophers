/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sed.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 00:06:22 by henri             #+#    #+#             */
/*   Updated: 2020/04/06 17:18:43 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Sed.hpp"

/*
** Always prefer size_t to iterate
** https://stackoverflow.com/questions/1951519/should-i-use-stdsize-t-or-int-in-my-for-loops
*/

std::string Sed::replace(const std::string &line, const std::string &search, const std::string &replace)
{
	size_t				i;
	size_t				j;
	size_t				lineLength;
	size_t				searchLength;
	std::stringstream	ret;

	lineLength = line.length();
	searchLength = search.length();
	for (i = 0; i < lineLength; i++) {
		j = 0;
		while (line[i + j] == search[j] && j < searchLength)
			j++;
		if (j == searchLength)
		{
			ret << replace;
			i = i + j - 1;
		}
		else
			ret << line[i];
	}
	return (ret.str());
}

/*
** http://www.cplusplus.com/reference/fstream/fstream/open/
*/

void Sed::substitute(const std::string &filename, const std::string &search, const std::string &replace)
{
	std::ifstream	file;
	std::ofstream	output;
	std::string		line;

	if (filename.length() == 0)
		throw "Invalid Filename";
	if (search.length() == 0)
		throw "Invalid Search String";
	if (replace.length() == 0)
		throw "Invalid Replace String";
	file.open(filename);
	if (file.is_open() == 0)
		throw "Couldn't open file";
	output.open(filename + ".replace", std::ios::trunc);
	if (output.is_open() == 0)
		throw "Couldn't open output file";
	while (std::getline(file, line))
	{
		output << Sed::replace(line, search, replace);
		if (file.eof() == 0)
			output << '\n';
	}
	file.close();
	output.close();
}
