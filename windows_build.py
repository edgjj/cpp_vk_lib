import os
import sys
import subprocess

vcpkg_path = sys.argv[1]

if not os.path.exists(vcpkg_path):
	print("Vcpkg path is invalid")
	exit()
triplet = sys.argv[2]

absolute_path = os.path.abspath(os.getcwd())

subprocess.call(f"mkdir {absolute_path}/windows_build", shell=True)
os.chdir("windows_build")
subprocess.call(f'cmake .. -DCMAKE_TOOLCHAIN_FILE="{vcpkg_path}/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="{triplet}"', shell=True)
