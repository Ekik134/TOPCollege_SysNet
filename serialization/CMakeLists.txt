# Подпроект, представляющий простое взаимодействие "один клиент - сервер"
project(serialization)

add_executable(server_serialized
    server.cpp
)

add_executable(client_serialized
    client.cpp
)