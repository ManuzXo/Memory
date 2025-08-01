#!/bin/bash

# Imposta nome progetto e cartelle
PROJECT_NAME="Memory"
BUILD_DIR="build"
SRC_DIR="."
ARCH="x64"
BUILD_TYPE="Debug"

# Pulizia input da eventuali caratteri Windows
cleanup_input() {
    echo "$1" | tr -d '\r'
}

# Parsing argomenti
while [[ $# -gt 0 ]]; do
    case "$1" in
        -a|--arch)
            ARCH=$(cleanup_input "$2")
            shift 2
            ;;
        -t|--type)
            BUILD_TYPE=$(cleanup_input "$2")
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

# Flag architettura
if [[ "$ARCH" == "x86" ]]; then
    C_FLAGS="-m32"
elif [[ "$ARCH" == "x64" ]]; then
    C_FLAGS="-m64"
else
    echo "❌ Architettura non valida: $ARCH"
    exit 1
fi

echo "📦 Configurazione: ARCH=$ARCH | TYPE=$BUILD_TYPE"
echo "🔧 Compilazione con flags: $C_FLAGS"

# Configura con CMake
cmake -S "$SRC_DIR" -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DCMAKE_C_FLAGS="$C_FLAGS" \
    -DCMAKE_EXE_LINKER_FLAGS="$C_FLAGS"

if [[ $? -ne 0 ]]; then
    echo "❌ Errore nella configurazione CMake"
    exit 1
fi

# Costruisci
cmake --build "$BUILD_DIR" --config "$BUILD_TYPE"

if [[ $? -ne 0 ]]; then
    echo "❌ Errore nella compilazione"
    exit 1
fi

echo "✅ Compilazione completata! Eseguibile: bin/$BUILD_TYPE/$PROJECT_NAME"