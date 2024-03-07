# Install kaylordut library from source repository
```bash
git clone https://github.com/kaylorchen/kaylordut.git
mkdir -p kaylordut/build
cd kaylordut/build
cmake ..
make 
sudo make install
```
<!-- DEB_BUILD_OPTIONS=arch=arm64 dpkg-buildpackage -j -aarm64 -us -uc -->

# Create a debian package from source repository
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
