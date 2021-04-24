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

function test_cleaner () {
	for _dir in `find test -maxdepth 1 -type d`
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

cleaner "." "lib" "bot" "test"
test_cleaner
