#!/usr/bin/env bash
# Entrypoint for the rusefi-build Docker container.
# Mirrors the CI build steps from build-firmware.yaml.
#
# Usage: build.sh <meta-info-path> [make-target]
#   meta-info-path: relative to firmware/, e.g. config/boards/proteus/meta-info-proteus_f4.env
#   make-target:    optional, defaults to 'all' (firmware only). Use 'build_both_bundles' to match CI fully.
#
# Example:
#   docker run --rm -v "$(pwd):/rusefi" rusefi-build config/boards/proteus/meta-info-proteus_f4.env

META="$1"
TARGET="${2:-all}"

if [ -z "$META" ]; then
    echo "Usage: build.sh <meta-info-path> [make-target]"
    echo "Example: build.sh config/boards/proteus/meta-info-proteus_f4.env"
    exit 1
fi

cd /rusefi/firmware

echo "=== Step 1: Config generation ==="
bash bin/compile.sh "$META" config

echo "=== Step 2: Firmware build (target: $TARGET) ==="
bash bin/compile.sh "$META" "$TARGET"
