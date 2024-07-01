# Install 
There are three installation methods:
## Install kaylordut library from source repository
```bash
sudo apt install libspdlog-dev libsystemd-dev -y
git clone https://github.com/kaylorchen/kaylordut.git
mkdir -p kaylordut/build
cd kaylordut/build
cmake ..
make 
sudo make install
```
<!-- DEB_BUILD_OPTIONS=arch=arm64 dpkg-buildpackage -j -aarm64 -us -uc -->

## Create a debian package from source repository
- clone source repository and run docker
```bash
git clone https://github.com/kaylorchen/kaylordut.git
cd kaylordut
docker pull --platform=arm64 kaylor/base-compile:latest # platform: arm64 or amd64
docker run -it -v ${PWD}:/root/kaylordut kaylor/base-compile:latest bash
```
- Compile debian package

```bash
cd /root/kaylordut
git config --global --add safe.directory /root/kaylordut
mk-build-deps --install --remove debian/control
./build.sh
exit
```
- Install kaylordut debian package
```bash
sudo apt install ./kaylordut-dev_*.deb
```
> you can copy the debian package to your target host and installl it

## Install via apt
```shell
cat << 'EOF' | sudo tee /etc/apt/sources.list.d/kaylordut.list 
deb [signed-by=/etc/apt/keyrings/kaylor-keyring.gpg] http://apt.kaylordut.cn/kaylordut/ kaylordut main
EOF
sudo mkdir /etc/apt/keyrings -pv
sudo wget -O /etc/apt/keyrings/kaylor-keyring.gpg http://apt.kaylordut.cn/kaylor-keyring.gpg
sudo apt update
sudo apt install kaylordut-dev
```

# Example
- Edit test.cpp and CMakeLists.txt
```c++
#include "kaylordut/log/logger.h"
int main() {
  KAYLORDUT_LOG_ERROR("this is a test");
  return 0;
}
```
```cmake
cmake_minimum_required(VERSION 3.10)
project(logtest)
find_package(kaylordut REQUIRED)
add_executable(logtest main.cpp)
target_link_libraries(logtest ${kaylordut_LIBS})
```
- Build and run
```bash
mkdir build
cd build
cmake ..
make 
./logtest 
```
