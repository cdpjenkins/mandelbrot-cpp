#include "App.hpp"
#include "Config.hpp"

using namespace std;

int main(int argc, char** argv) {
    Config config = Config::parse(argc, argv);

    App app(config);
    app.main_loop();
}
