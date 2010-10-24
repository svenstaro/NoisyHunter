#include <signal.h>

#include "Root.hpp"

#include "MainState.hpp"

void HandleSignal(int sig) {
	auto logmgr =  Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_VERBOSE, Engine::LOGORIGIN_ROOT, "Raised signal: " + boost::lexical_cast<std::string>(sig) + ".");
	exit(1);
}

namespace po = boost::program_options;
po::variables_map usage(int& argc, char* argv[]) {
	po::variables_map vm;

	try {
		// Declare the supported options.
		po::options_description desc("Noisy Hunter - a game in which you are a submarine and use sound to locate your opponents.\
		\n\nAllowed options");
		desc.add_options()
			("help,h", "this message")
			("port,p", po::value<sf::Uint16>()->default_value(12356), "server port")
			("verbose,v", po::value<sf::Uint16>()->implicit_value(1), "be verbose")
		;

		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if(vm.count("help")) {
			std::cout << desc << "\n";
			exit(1);
		}
	} catch(std::exception& e) {
		std::cerr << "ERROR: " << e.what() << "\n";
        exit(1);
    } catch(...) {
		std::cerr << "Exception of unknown type!\n";
    }

	return vm;
}

int main(int argc, char* argv[]) {
	signal(SIGINT, HandleSignal);
	signal(SIGABRT, HandleSignal);
	signal(SIGTERM, HandleSignal);
	// Pass along command line argument to usage() in order to process them.
	po::variables_map opts = usage (argc, argv);

	// Parse commnad line options.
	sf::Uint16 port = opts["port"].as<sf::Uint16>();
	bool verbose = false;
	if(opts.count("verbose"))
		verbose = true;
	// TODO: Implement verbose.

	// Get Root singleton.
    Engine::Root& root = Engine::Root::get_mutable_instance();

	auto idmgr = root.GetIdManagerPtr();
	idmgr->RegisterEntityClass(new Submarine());
	idmgr->RegisterEntityClass(new Torpedo());

	// Initialize Root singleton using parsed values.
    root.InitializeAsServer(port, verbose);
    root.GetStateManagerPtr()->Add(new MainState());
    root.StartMainLoop();
    return 0;
}
