# 🧠 Memory Game

Gioco di memoria sviluppato utilizzando la libreria [Raylib](https://www.raylib.com/) e l'estensione grafica [Raygui](https://github.com/raysan5/raygui).

---

## ✅ Requisiti

- **CMake** ≥ 3.30  
- **Visual Studio 2022** (versione 17) su **Windows**  
- **GCC** o **Clang** su **Linux**  
- **Raylib** (le librerie sono già incluse nel progetto)

---

## ⚙️ Installazione
Puoi compilare il progetto in due modi:

### 🔧 Metodo 1 — Da terminale con CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```
### 🛠 Metodo 2 — Usando gli script forniti

▶️ Linux
``` bash
chmod +x build.sh
./build.sh
```
▶️ Windows
```bash
build.bat -a x86 -t Release
```
⚠️ Nota: Puoi cambiare -a per l’architettura (x86, x64) e -t per il tipo di build (Debug, Release).
