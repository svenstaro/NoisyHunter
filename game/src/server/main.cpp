#include <signal.h>

#include "Root.hpp"

#include "MainState.hpp"
#include "PlayWorld.hpp"
// Include entities in the appropriate state

void HandleSignal(int sig) {
    std::cout << "\r";
    Engine::Logger::Critical(Engine::LogOrigin::ROOT, "Raised signal: " + boost::lexical_cast<std::string>(sig) + ".");
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
	idmgr->RegisterEntityClass(new WorldPolygon());
	idmgr->RegisterEntityClass(new SonarPing());

	idmgr->RegisterWorldClass(new PlayWorld());

	// Initialize Root singleton using parsed values.
    root.InitializeAsServer(port, verbose);
	MainState* mainstate = new MainState();
	PlayWorld* playworld = new PlayWorld();
	root.SetWorldPixelsPerFloat(100);
	playworld->GrabWorldUniqueId();
	mainstate->AddWorld(playworld);

	WorldPolygon* pol1 = new WorldPolygon();
	pol1->Initialize();
	pol1->GrabEntityUniqueId();
	//pol1->AddPoint(sf::Vector2f(0.f,	0.f));
	pol1->AddPoint(sf::Vector2f(2.f,	2.f));
	pol1->AddPoint(sf::Vector2f(8.f,	4.f));
	pol1->AddPoint(sf::Vector2f(18.f,	2.f));
	pol1->AddPoint(sf::Vector2f(17.f,	6.f));
	pol1->AddPoint(sf::Vector2f(15.f,	6.4f));
	pol1->AddPoint(sf::Vector2f(18.f,	14.f));
	pol1->AddPoint(sf::Vector2f(12.f,	19.4f));
	pol1->AddPoint(sf::Vector2f(2.4f,	13.4f));
	pol1->AddPoint(sf::Vector2f(0.6f,	4.f));
	/*pol1->AddPoint(sf::Vector2f(20.f,	20.f));
	pol1->AddPoint(sf::Vector2f(0.f,	0.f));
	pol1->AddPoint(sf::Vector2f(20.f,	0.f));
	pol1->AddPoint(sf::Vector2f(20.f,	20.f));
	pol1->AddPoint(sf::Vector2f(0.f,	20.f));*/

	pol1->SetPosition(0.f,0.f);
	playworld->AddEntity(pol1);

	// rock
	WorldPolygon* pol2 = new WorldPolygon();
	pol2->Initialize();
	pol2->GrabEntityUniqueId();
	pol2->AddPoint(sf::Vector2f(12.f,	9.5f));
	pol2->AddPoint(sf::Vector2f(13.f,	11.f));
	pol2->AddPoint(sf::Vector2f(11.f,	10.5f));
	pol2->AddPoint(sf::Vector2f(10.5f,	9.f));
	pol2->AddPoint(sf::Vector2f(11.2f,	8.6f));

	pol2->SetPosition(0.f,0.f);
	playworld->AddEntity(pol2);

    root.GetStateManagerPtr()->Add(mainstate);
    root.StartMainLoop();
    return 0;
}
