#!/bin/bash

PROJECT_NAME="Memory"
BUILD_DIR="build"
SRC_DIR="."
ARCH="x64"
BUILD_TYPE="Debug"

# Argument parsing
while [[ $# -gt 0 ]]; do
    case "$1" in
        -a|--arch)
            ARCH="$2"
            shift 2
            ;;
        -t|--type)
            BUILD_TYPE="$2"
            shift 2
            ;;
        -c|--clean)
            echo "🧹 Pulizia..."
            rm -rf "$BUILD_DIR"
            exit 0
            ;;
        -h|--help)
            echo "Uso: ./build.sh [-a x86|x64] [-t Debug|Release] [-c]"
            exit 0
            ;;
        *)
            echo "❌ Argomento sconosciuto: $1"
            exit 1
            ;;
    esac
done

# Flags architettura
if [[ "$ARCH" == "x86" ]]; then
    C_FLAGS="-m32"
elif [[ "$ARCH" == "x64" ]]; then
    C_FLAGS="-m64"
else
    echo "❌ Architettura non valida: $ARCH"
    exit 1
fi

echo "📦 Configurazione: $ARCH / $BUILD_TYPE"

cmake -S "$SRC_DIR" -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DCMAKE_C_FLAGS="$C_FLAGS" \
    -DCMAKE_EXE_LINKER_FLAGS="$C_FLAGS"

if [[ $? -ne 0 ]]; then
    echo "❌ Errore CMake"
    exit 1
fi

cmake --build "$BUILD_DIR" --config "$BUILD_TYPE"

echo "✅ Fatto! Executable: bin/$BUILD_TYPE/$PROJECT_NAME"
