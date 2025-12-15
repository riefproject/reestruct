#!/usr/bin/env bash
set -euo pipefail

usage() {
    echo "Usage: $0 [static|shared|release|all|clean|test|docs]"
    echo "Default: release"
}

TARGET=${1:-release}
case "$TARGET" in
    static|shared|release|all|clean|test|docs) ;;
    *) usage; exit 1 ;;
esac

UNAME_OUT=$(uname -s 2>/dev/null || echo "unknown")
case "$UNAME_OUT" in
    Darwin*) OS_NAME="Darwin" ;;
    Linux*) OS_NAME="Linux" ;;
    MINGW*|MSYS*|CYGWIN*) OS_NAME="Windows_NT" ;;
    *) OS_NAME="$UNAME_OUT" ;;
esac
export OS="$OS_NAME"

if ! command -v make >/dev/null 2>&1; then
    echo "Error: make is not available. Please install build tools first."
    exit 1
fi

echo "Building target '$TARGET' for OS=$OS_NAME"
make "$TARGET"
