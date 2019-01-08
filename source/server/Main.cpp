/*
** EPITECH PROJECT, 2018
** Main
** CPP_rtype_2018
** File description:
** Main
*/

#include <boost/asio.hpp>
#include "graphic/Window.hpp"
#include "graphic/RessourceManager.hpp"
#include "graphic/Rectangle.hpp"
#include "net/NetworkService.hpp"
#include "components/TransformComponent.hpp"
#include "components/BoundingBoxComponent.hpp"
#include "systems/SpawnMonsterSystem.hpp"
#include "Server.hpp"

int main()
{
    net::NetworkService netservice;
    boost::asio::io_service::work work(netservice);
    rtype::Server Server(netservice);
    return 0;
}
