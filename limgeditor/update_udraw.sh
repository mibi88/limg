#!/bin/bash

git submodule update --init;
cd uDraw;
git pull --rebase;
cd ..;
git add uDraw;
