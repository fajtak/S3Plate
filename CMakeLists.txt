#
# SCube simulation
# 
# Author(s): Vladimir Fekete, vladko.fekete@gmail.com           
# 
# Copyright GNU General Public License v2.0.
# 
# You should have received a copy of the GNU General Public License
# along with SCube.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(plates)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

find_package(Geant4 REQUIRED)
find_package(ROOT REQUIRED)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${ROOT_INCLUDE_DIRS})

# let's make Geant4 header files visible for KDevelop (there is no other reason for this line)
include_directories(${Geant4_INCLUDE_DIRS})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(plates plates.cc ${sources} ${headers})
target_link_libraries(plates ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

install(TARGETS plates DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${PROJECT_SOURCE_DIR}/input_files DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
