#include "GameLobby.h"
#include <SDL2pp/SDL2pp.hh>

GameLobby::GameLobby(SDL2pp::Renderer &renderer, std::string user_name)
                     : Screen(renderer), user_name(user_name) {
	std::string room1("Room 1");
    // this->insert_text(room1, 20, 50, 40, A_CENTER);
    std::string room2("Room 2");
    // this->insert_text(room2, 20, 50, 50, A_CENTER);
	Button b1(renderer, room1, 30, 50, 40, A_CENTER);
	Button b2(renderer, room2, 30, 50, 50, A_CENTER);
    //TODO: give roomButtons listener methods onClick(method)
    //TODO: create event handler, needed to launch events
    // so
    // button.onClick ([](){ EventHandler::OnStartGamePressed() });
    // and objects need to listen to that event so like
    // EventHandler::onStartGame += DoSomething;
	buttons.push_back(b1);
	buttons.push_back(b2);
}

int GameLobby::start() {
	SDL_bool done = SDL_FALSE;
	
    while (!done) {
        
        // Event processing:
		// - If window is closed, or Q or Escape roomButtons are pressed,
		//   quit the application
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				return 1;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: case SDLK_q:
					return 1;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				for (auto &b : buttons)
					b.click(event.button);
				break;
			default:
				break;
			}
		}
		
        redraw();

		// Frame limiter: sleep for a little bit to not eat 100% of CPU
		SDL_Delay(1);
    }
    return 0;
}


void GameLobby::redraw() {
	// Clear screen
	renderer.Clear();

	std::string user_info = std::string("User: ") += this->user_name;
	this->insert_text(user_info, 20, 20, 20, A_RIGHT);
	std::string title = "Welcome to Quantum Chess Lobby";
	this->insert_text(title, 30, 50, 20, A_CENTER);
	for (auto &b : buttons)
		b.redraw();
    

	// Show rendered frame
	renderer.Present();
}

