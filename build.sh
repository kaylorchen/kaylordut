#!/bin/bash
export EMAIL=kaylor.chen@qq.com
version=$(git describe --tags)
commit_msg=$(git log -n 1 --pretty=format:'%s')
echo version is $version, and commit_msg is $commit_msg
mv debian/changelog debian/changelog.bak
dch --create --package=kaylordut-dev -v ${version} ${commit_msg}
rm *.deb
fakeroot debian/rules binary
mv debian/changelog.bak debian/changelog
fakeroot debian/rules clean
mv ../kaylor*.deb ./