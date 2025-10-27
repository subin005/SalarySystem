#include "./function/funclib.hpp"
#include "./menu/menu.hpp"
#include "./memory/file.hpp"
#include <iostream>

// panel p;
std::vector<person*> panel::member_list = {};
int id_base = 0;
int main(){
    std::cout << R"(
        __          __  _                              
        \ \        / / | |                             
         \ \  /\  / /__| | ___ ___  _ __ ___   ___    
          \ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \   
           \  /\  /  __/ | (_| (_) | | | | | |  __/   
            \/  \/ \___|_|\___\___/|_| |_| |_|\___|   
                                                    
            Welcome to use Slary System!
   )"<<std::endl;
    // panel p;
    //menu setup

    Menu* main_menu = new Menu();
    Menu* build_menu = new Menu(main_menu);
    Menu* display_menu = new Menu(main_menu);
    Menu* clear_menu = new Menu(main_menu);
    main_menu->add_submenu("Build",build_menu)
             ->add_submenu("Display",display_menu)
             ->add_submenu("Clear",clear_menu)
             ->add_function("Save",save_mls);
    build_menu->add_function("New",build)
              ->add_function("Change",change);
    display_menu->add_function("Display (forall)",display)
                ->add_function("Display (appointed)",display_index);
    clear_menu->add_function("Clear All",clear)
              ->add_function("Clear by Index",clear_index);
    //load
    load_mls();
    //run
    while(true){
        std::string rest_input;
        std::cout<<std::endl<<"==================================="<<std::endl;
        main_menu->display();
        int choice = 0;
        std::cout<<"Enter your operation: ";
        if(!(std::cin>>choice)){
            std::cin.clear();
            std::getline(std::cin,rest_input);
            std::cout<<"Can't recognize '"<<rest_input<<"'"<<std::endl;
            continue;
        }
        std::getline(std::cin,rest_input);
        // std::cout<<choice<<std::endl;
        main_menu = main_menu->run(choice);
    }
    return 0;
}