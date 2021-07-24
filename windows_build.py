import os
import sys
import subprocess

vcpkg_path = sys.argv[1]
if not os.path.exists(vcpkg_path):
	print("Vcpkg path is invalid")
	exit()
triplet = sys.argv[2]

subprocess.call("mkdir ./windows_build", shell=False)
os.chdir("windows_build")
subprocess.call(f'cmake .. -DCMAKE_TOOLCHAIN_FILE="{vcpkg_path}/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="{triplet}"', shell=False)
