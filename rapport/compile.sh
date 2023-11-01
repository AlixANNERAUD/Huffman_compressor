#!/bin/bash

pdflatex rapport.tex

if [ $? -eq 0 ]; then
    pdflatex rapport.tex;
    echo "Compilation réussie";
else
    echo "Compilation ratée"
fi

find . -name "*.aux" -type f -delete
find . -name "*.toc" -type f -delete
rm *.log