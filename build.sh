set -e

./build-boot.sh
./build-libc.sh
./build-kernel.sh
./build-img.sh