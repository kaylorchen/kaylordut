# Install kaylordut library
```bash
git clone https://github.com/kaylorchen/kaylordut.git
mkdir -p kaylordut/build
cd kaylordut/build
cmake ..
make 
sudo make install
```
DEB_BUILD_OPTIONS=arch=arm64 dpkg-buildpackage -j -aarm64 -us -uc
