#include <fstream>
#include <cassert>

#include "driver.hpp"

Grammar::Driver::~Driver()
{
	delete(scanner);
	delete(parser);
}

void Grammar::Driver::parse(const char* const filename)
{
	assert(filename != nullptr);
	std::ifstream iss{ filename };

	if (!iss)
		exit(EXIT_FAILURE);

	parse_helper(iss);
}

void Grammar::Driver::parse(std::istream& iss)
{
	if (!iss.good() && iss.eof())
		return;

	parse_helper(iss);
}

void Grammar::Driver::parse_helper(std::istream& iss)
{
	delete scanner;
	try
	{
		scanner = new Grammar::Scanner(&iss);
	}
	catch (const std::bad_alloc& ba)
	{
		std::cerr << "Failed to allocate scanner: \"" << ba.what() << "\". Exiting!\n";
		exit(EXIT_FAILURE);
	}

	delete parser;
	try
	{
		parser = new Grammar::Parser(*scanner, *this);
	}
	catch (const std::bad_alloc& ba)
	{
		std::cerr << "Failed to allocate parser: \"" << ba.what() << "\". Exiting!\n";
		exit(EXIT_FAILURE);
	}

	if (parser->parse() != 0)
	{
		std::cerr << "Parsing failure!\n";
	}
	return;
}

void Grammar::Driver::addTag(const std::string& tag, const std::string& value)
{
	tags.insert_or_assign(tag, value);
}

std::string Grammar::Driver::retrieveTag(const std::string& tag, const std::string& defaultValue)
{
	const auto iter = tags.find(tag);
	if (iter == tags.end())
		return defaultValue;
	return iter->second;
}

std::ostream& operator<<(std::ostream& oss, const Grammar::Driver& driver)
{
	// print the contents of the grammar
	for (const auto& tagAssignment : driver.tags)
		oss << tagAssignment.first << " = " << tagAssignment.second << '\n';

	return oss;
}
