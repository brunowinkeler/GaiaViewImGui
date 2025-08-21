#!/usr/bin/bash

set -e  # para o script se algum comando falhar

echo
echo "Configurando CMake..."
echo

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

echo
echo "Compilando projeto..."
echo

cmake --build build -j

echo
echo "Build completo!"
echo
