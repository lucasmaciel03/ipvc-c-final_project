cmake_minimum_required(VERSION 3.28)
project(ipvc_c_final_project C)

set(CMAKE_C_STANDARD 11)

add_executable(ipvc_c_final_project main.c
        menus/admin_main_menu/admin_main_menu.c
        menus/admin_main_menu/admin_main_menu.h
        menus/agent_main_menu/agent_main_menu.c
        menus/agent_main_menu/agent_main_menu.h
        menus/agent_menu/agent_menu.c
        menus/client_main_menu/client_main_menu.c
        menus/client_main_menu/client_main_menu.h
        menus/main_menu/main_menu.c
        menus/properties_menu/properties_menu.c
        utils/utils.c
        auth/login.c
        auth/register.c
        auth/users/user.c
        agents/agents.c
        properties/properties.c
        properties/properties.h
        menus/database_menu/database_menu.c
        data_base/data_base.h
        data_base/data_base.c
        clients/clients.c
        clients/clients.h
        role_agents/role_agents.c
        role_agents/role_agents.h
)
