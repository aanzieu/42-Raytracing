#!/bin/bash

git clone https://MrPandawan@bitbucket.org/MrPandawan/clang7.3.git clang7
if [ ! -d LibraryTmp ]; then mkdir -p LibraryTmp; fi
if [ ! -d clangtmp ]; then mkdir -p clangtmp; fi
#mkdir clangtmp && mkdir LibraryTmp
pkgutil --expand clang7/Command\ Line\ Tools\ \(OS\ X\ 10.11\).pkg clangtmp
rm -rf clangtmp
pkgutil --expand clang7/Command\ Line\ Tools\ \(OS\ X\ 10.11\).pkg clangtmp
rm -rf clang7
tar -xvf clangtmp/CLTools_Executables.pkg/Payload -C LibraryTmp
rm -rf clangtmp
export PATH=LibraryTmp/Library/Developer/CommandLineTools/usr/bin${PATH:+:${PATH}}
echo $PATH
make -j
#rm -rf LibraryTmp