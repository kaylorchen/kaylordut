#!/bin/bash
version=$(git describe --tags)
commit_msg=$(git log -n 1 --pretty=format:'%s')
echo version is $version, and commit_msg is $commit_msg
dch --create --package=kaylordut-dev -v ${version} ${commit_msg}
rm *.deb
fakeroot debian/rules binary
fakeroot debian/rules clean
mv ../kaylor*.deb ./