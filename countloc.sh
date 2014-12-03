#!/bin/bash

echo "Source files LoC:"
find -name '*.c' | xargs wc -l
echo 
find -name '*.h' | xargs wc -l
echo 
find -name 'Makefile' | xargs wc -l
echo 
echo "Documentation files LoC:"
find -name '*.md' | xargs wc -l

