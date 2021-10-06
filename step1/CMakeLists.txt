cmake_minimum_required(VERSION 3.10)

# set the project name
project(testpro VERSION 1.0)

set(SOURCE 
test2.cxx
test3.cxx
register.cxx
)
# add the executable
add_executable(testproject ${SOURCE})
