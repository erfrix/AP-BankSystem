cmake_minimum_required(VERSION 3.10)

project(BankSystem)

add_executable(app main.cpp account.cpp transaction.cpp)

include_directories(../include)