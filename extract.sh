#!/bin/bash
rm -rf raw/
dpkg-deb -R *.deb raw
tree raw