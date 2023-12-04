#!/bin/bash
rm -rf raw/
dpkg-deb -R simple-deb*.deb raw
tree raw