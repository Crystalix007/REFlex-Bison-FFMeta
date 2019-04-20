#pragma once

#include <string>
#include <iostream>
#include "lexer.hh"
#include <map>

namespace Grammar {
	class Driver;
}

std::ostream& operator<<(std::ostream& oss, const Grammar::Driver& driver);

namespace Grammar {
	class Driver {
		public:
			Driver() = default;
			virtual ~Driver();

			void parse(const char* const filename);
			void parse(std::istream& iss);

			/*
			 * functions to store data retrieved by grammar / parser
			 */

			void addTag(const std::string& tag, const std::string& value);
			std::string retrieveTag(const std::string& tag, const std::string& defaultValue = {});

			friend std::ostream& ::operator<<(std::ostream& oss, const Driver& driver);

		private:
			void parse_helper(std::istream& iss);

			Grammar::Parser*  parser  = nullptr;
			Grammar::Scanner* scanner = nullptr;
			
			/*
			 * specialised data store
			 */
 
			std::map<std::string, std::string> tags;
	};
}
