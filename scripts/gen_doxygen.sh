#!/bin/bash

function generate_docs() {
	cd doxygen
	doxygen Doxyfile
	cd ..
	rm -rf docs
	mv html docs	
}

generate_docs
