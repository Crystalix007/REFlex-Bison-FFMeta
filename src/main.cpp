#include "driver.hpp"
#include <tclap/CmdLine.h>

int main(int argc, char** argv) {
	Grammar::Driver driver{};

	if (argc == 1)
	{
		driver.parse(std::cin);
		std::cout << driver << std::endl;
	}
	else
	{
		try
		{
			TCLAP::CmdLine cmd("Retrieves tags from an FFMetadata file", ' ', "0.1");
			TCLAP::MultiArg<std::string> tags{ "t", "tag", "Tag to retrieve from the FFMetadata (if it exists)", true, "tag name" };
			cmd.add(tags);
			cmd.parse(argc, argv);

			driver.parse(std::cin);

			const auto& requestTags = tags.getValue();

			for (const auto& requestTag : requestTags)
				std::cout << driver.retrieveTag(requestTag) << "\n";
		}
		catch (TCLAP::ArgException& e)
		{
			std::cerr << "Argument parsing error: \'" << e.error() << "\' for argument " << e.argId() << std::endl;
		}
	}

	return 0;
}
