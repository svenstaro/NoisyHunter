#include "client.hpp"

ClientApp::ClientApp(sf::Uint16 width, sf::Uint16 height, sf::Uint16 port) {
    mWidth = width;
    mHeight = height;
    mPort = port;
}

ClientApp::~ClientApp() {}

bool ClientApp::Init() {
    // init graphics stuff
    std::cout << "STATUS: Initializing client" << std::endl;
    mRenderWin.Create(sf::VideoMode(mWidth, mHeight, 32), "Noisy Hunter");
    std::cout << "STATUS: Render window created with dimensions " << mWidth << "x" << mHeight << std::endl;
    mRenderWin.SetFramerateLimit(60);

    // init network stuff
    std::cout << "STATUS: Binding client port " << mPort << std::endl;
    if(!mSocket.Bind(mPort)) {
        std::cerr << "ERROR: Failed to bind port " << mPort << std::endl;
        return EXIT_FAILURE;
    } 
    else {
        std::cout << "STATUS: Successfully bound port " << mPort << std::endl;
    }
    mSocket.SetBlocking(false);
}

void ClientApp::Run() {
    const sf::Input& Input = mRenderWin.GetInput(); // for game input as opposed to events

    // enter main loop 
    bool running = true;
    while(running) {
        // client events
        sf::Event Event;
        while(mRenderWin.GetEvent(Event)) {
            if(Event.Type == sf::Event::Closed)
                running = false;
            if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
                running = false;
        }

        // client input
        bool a_key_down = Input.IsKeyDown(sf::Key::A); // strafe left
        bool d_key_down = Input.IsKeyDown(sf::Key::D); // strafe right
        bool w_key_down = Input.IsKeyDown(sf::Key::W); // strafe up
        bool s_key_down = Input.IsKeyDown(sf::Key::S); // strage down

        bool q_key_down = Input.IsKeyDown(sf::Key::Q); // rotate sonar turret anti-clockwise
        bool e_key_down = Input.IsKeyDown(sf::Key::E); // rotate sonar turret clockwise

        bool r_key_down = Input.IsKeyDown(sf::Key::R); // sonar pulse
        bool f_key_down = Input.IsKeyDown(sf::Key::F); // sonar beam

        bool space_key_down = Input.IsKeyDown(sf::Key::Space); // fire torpedo

        // draw
        BOOST_FOREACH(IEntity& CurrentEntity, mEntityList) {
            mRenderWin.Draw(CurrentEntity.GetDrawable());
        }
        mRenderWin.Display();
    }
}

void ClientApp::Cleanup() {
    std::cout << "STATUS: Cleaning up client" << std::endl;

    std::cout << "STATUS: Closing render window" << std::endl;
    mRenderWin.Close();

    std::cout << "STATUS: Unbinding client port " << mPort << std::endl;
    mSocket.Unbind();

    std::cout << "STATUS: Client is shut down" << std::endl;
}
