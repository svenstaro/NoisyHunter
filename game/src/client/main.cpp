#include <signal.h>

#include "Root.hpp"

#include "PlayState.hpp"
#include "LoadingState.hpp"

void HandleSignal(int sig) {
	auto logmgr =  Engine::Root::get_mutable_instance().GetLogManagerPtr();
	logmgr->Log(Engine::LOGLEVEL_VERBOSE, Engine::LOGORIGIN_ROOT, "Raised signal: " + boost::lexical_cast<std::string>(sig) + ".");
	Engine::Root::get_mutable_instance().GetStateManagerPtr()->GetCurrentState().OnLeaveGame();
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
			("size,s", po::value<std::string>()->default_value("800x600"), "game resolution")
			("fullscreen,f", po::value<sf::Uint16>()->implicit_value(1), "start in fullscreen")
			("name,n", po::value<std::string>()->default_value("New Player"), "client name")
			("ip,i", po::value<std::string>()->default_value("localhost"), "server ip address")
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

std::vector<sf::Uint16> split(const std::string& size_str) {
	// split "4x4" to int{4,4}
	std::vector<sf::Uint16> size_vec;
	sf::Uint16 sep;
	std::string width;
	std::string height;

	sep = size_str.find("x");

	width = size_str.substr(0, sep);
	height = size_str.substr(sep + 1);

	size_vec.push_back(boost::lexical_cast<sf::Uint16>(width));
	size_vec.push_back(boost::lexical_cast<sf::Uint16>(height));

	return size_vec;
}

int main(int argc, char* argv[]) {

	signal(SIGINT, HandleSignal);
	signal(SIGABRT, HandleSignal);
	signal(SIGTERM, HandleSignal);

	// Pass along command line argument to usage() in order to process them.
	po::variables_map opts = usage (argc, argv);

	// Parse commnad line options.
	sf::Uint16 width = split(opts["size"].as<std::string>())[0];
	sf::Uint16 height = split(opts["size"].as<std::string>())[1];
	bool fullscreen = false;
	if(opts.count("fullscreen"))
		fullscreen = true;
	std::string name = opts["name"].as<std::string>();
	std::string ip = opts["ip"].as<std::string>();
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
    root.InitializeAsClient(sf::VideoMode(width, height), "Noisy Hunter", fullscreen, sf::IpAddress(ip), port, name, verbose);

    //root.GetStateManagerPtr()->Add(new LoadingState());
    root.GetStateManagerPtr()->Add(new PlayState());

    root.StartMainLoop();
    return 0;
}
