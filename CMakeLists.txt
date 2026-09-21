cmake_minimum_required(VERSION 3.25)

project(DeepakMart)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Drogon CONFIG REQUIRED)
find_package(unofficial-argon2 CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(deepakmart

    src/main.cpp

    src/controller/HomeController.cpp
    src/controller/UserController.cpp
    src/controller/ProductController.cpp
    src/controller/CartController.cpp
    src/controller/OrderController.cpp
    src/controller/ReviewController.cpp
    src/controller/AdminController.cpp

    src/service/UserService.cpp
    src/service/ProductService.cpp
    src/service/CartService.cpp
    src/service/OrderService.cpp
    src/service/ReviewService.cpp
    src/service/AdminService.cpp

    src/util/PasswordUtil.cpp

    src/repository/UserRepository.cpp
    src/repository/ProductRepository.cpp
    src/repository/CartRepository.cpp
    src/repository/OrderRepository.cpp
    src/repository/ReviewRepository.cpp
    src/repository/AdminRepository.cpp
)

target_link_libraries(deepakmart
    PRIVATE
    Drogon::Drogon
    unofficial::argon2::libargon2
    OpenSSL::Crypto
)