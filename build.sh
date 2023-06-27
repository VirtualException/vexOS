./clean.sh

set -e

./build-boot.sh
./build-kernel.sh
./build-img.sh
