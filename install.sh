#!/bin/bash

# TODO:
# 1. add checks prevent '' from being submitted when reading from stdin
# 2. add colors and emojis to make the installation process more fun
# 3. rm install.sh
# 4. add option to rewrite makefile to compile as a single project binary
# instead of many

printf "what do you want to name your mps430 project?: "

read project_name

git clone https://github.com/breakthatbass/msp430-env.git

mv msp430-env/ $project_name

cd $project_name

printf "do you want to use libraries? (y/n): "
read LIB

rm src/*.c
rm src/*.md
rm -rf .git
rm LICENSE  # add your own if you want

if [[ $LIB == 'n' ]]; then
	rm -rf lib
fi

printf "do you want to init git? (y/n): "
read GIT

if [[ $GIT == 'y' ]]; then
	git init
	echo "# $project_name" > README.md
	git add .
	git commit -m 'initial commit of template'
	git branch -M main

	echo
	echo "git initiated"
	echo "if you would like to add to a GitHub repo, create one and then run:"
	echo
	echo "	git remote add origin https://github.com/USERNAME/$project_name.git"
	echo "	git push -u origin main"
fi
	
echo
echo "Your project template is ready!"
