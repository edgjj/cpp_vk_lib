import os, sys

vcpkg_path = sys.argv[1]
if not os.path.exists(vcpkg_path):
	print("Vcpkg path is invalid")
	exit()
triplet = sys.argv[2]

os.system("mkdir windows_build")
os.chdir("windows_build")
os.system(f'cmake .. -DCMAKE_TOOLCHAIN_FILE="{vcpkg_path}/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="{triplet}"');
