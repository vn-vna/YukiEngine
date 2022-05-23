<div>
    <div align="center">
        <h1>PROJECT YUKI ENGINE</h1>
        <img src="./GHRes/Yuki-W_BB.png" width="300" />
        <br />
        <span align="center">Yuki Engine</span>
        <br />
        <span align="center">~~~ Logo designed by Arisu ~~~</span>
        <br /> <br />
        <img src="https://img.shields.io/github/commit-activity/m/vn-vna/YukiEngine?style=for-the-badge"/>
        <img src="https://img.shields.io/github/last-commit/vn-vna/YukiEngine?color=cyan&style=for-the-badge" />
        <br />
        <img src="https://img.shields.io/github/languages/code-size/vn-vna/YukiEngine?color=purple&style=for-the-badge" />
        <img src="https://img.shields.io/github/issues-pr/vn-vna/YukiEngine?style=for-the-badge" />
        <img src="https://img.shields.io/github/issues-pr-closed/vn-vna/YukiEngine?style=for-the-badge" />
    </div> 
</div>

# About Yuki Engine

# Build Yuki

1. Required tools

- Compiler: `MSVC` (Windows), `clang` (LLVM), `gcc` (Linux)
- Build tool: `CMake` (Version >3.20), [Additional you can use [`Ninja`](https://ninja-build.org/) for better perfomance of `clang` and `gcc`]
- Package manager: `vcpkg`

2. Install tools

- `MSVC`: [Visual Studio Installer](https://visualstudio.microsoft.com/)
- `clang`: [LLVM Home page](https://llvm.org/) or install on linux
    ```bash
    # Arch linux https://archlinux.org/packages/extra/x86_64/llvm/
    $ sudo pacman -Sy llvm
    ```
    ```bash
    # Ubuntu https://apt.llvm.org/
    $ sudo apt-get install llvm
    ```
- `gcc`:
    ```bash
    # Arch linux https://archlinux.org/packages/extra/x86_64/llvm/
    $ sudo pacman -Sy gcc
    ```
    ```bash
    # Ubuntu https://apt.llvm.org/
    $ sudo apt-get install gcc
    ```
- `CMake`: [CMake home page](https://cmake.org/)
    ```bash
    # Arch linux https://archlinux.org/packages/extra/x86_64/llvm/
    $ sudo pacman -Sy cmake
    ```
    ```bash
    # Ubuntu https://apt.llvm.org/
    $ sudo apt-get install cmake
    ```
- `vcpkg`: [Offical tutorial](https://vcpkg.io/en/getting-started.html)
    ```bash
    # Clone vcpkg repository from Microsoft's github
    git clone https://github.com/Microsoft/vcpkg.git
    
    # Run bootstrap script
    # Windows
    .\vcpkg\bootstrap-vcpkg.bat
    # Linux
    ./vcpkg/bootstrap-vcpkg.sh

    # Run this line if you are using windows
    .\vcpkg integrate install
    ```

3. Install dependencies
- Install all required dependencies using vcpkg
    ```bash
    vcpkg install assimp freetype glad glfw3 fmt
    ```

4. Build `Yuki`
- Configure CMake build target
```bash
cd ./YukiEngine
# Replace [...] with the matched value in your computer
cmake -DCMAKE_TOOLCHAIN_FILE=[vcpkg path]/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE:STRING=[build type] -S./ -B./build -G [Your build system]
```
- Build
```bash
cmake --build ./build
```

- Enjoy <3