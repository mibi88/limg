#!/bin/bash

git submodule update --init;
cd uDraw;                                              
git pull;
cd ..;
git add uDraw;
