function cleaner () {
	for _dir in "$@"
	do
		rm -rf $_dir/CMakeCache.txt
		rm -rf $_dir/CMakeFiles
		rm -rf $_dir/CPackConfig.cmake
		rm -rf $_dir/cmake_install.cmake
		rm -rf $_dir/CPackSourceConfig.cmake
		rm -rf $_dir/Makefile
		rm -rf $_dir/CMakeLists.txt.user
	done
}

cleaner "." "dependencies" "dependencies/simdjson" "lib" "bot" "test"
