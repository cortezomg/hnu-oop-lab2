cmake_minimum_required(VERSION 3.10)
project(oop_project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(oop_project
  main.cpp
  worker.cpp
  project.cpp
  assignment.cpp
  manager.cpp
  contractor.cpp
  intern.cpp
  project_coordinator.cpp
  budget.cpp
  resource_pool.cpp
  team_lead.cpp
  customer.cpp
  block_tracker.cpp
)
