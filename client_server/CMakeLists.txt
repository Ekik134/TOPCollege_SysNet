# Подпроект, представляющий простое взаимодействие "один клиент - сервер"
project(client_server)

add_executable(server
    server.cpp
)

add_executable(client
    client.cpp
)