#!/bin/bash
version=$(shell git describe --tags)
commit_msg=$(shell git log -n 1 --pretty=format:'%s')
dch --create --package=ros-noetic-telecontrol -v ${version} ${commit_msg}
rm *.deb
fakeroot debian/rules binary
fakeroot debian/rules clean
mv ../kaylor*.deb ./