#!/bin/bash

# . ./pre_commit.sh
function generate_docs() {
	cd doxygen
	doxygen Doxyfile
	cd ..
	rm -rf docs
	mv html docs	
}

if [[ $1 = "--doxygen" ]]; then
	generate_docs
fi
