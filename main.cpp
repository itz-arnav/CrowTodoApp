#include <iostream>
#include "include/application.h"

int main() {

    try{
        Application app;
        app.run();
    }catch(std::exception& e){
        std::cerr << e.what();
    }

    return 0;
}
