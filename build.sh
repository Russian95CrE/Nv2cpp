#!/usr/bin/bash
clear

# try to format the src/ folder
if ! find src/ -name "*.[ch]" -exec clang-format -i {} +; then
    echo -e "\n\e[33mTried to format src/ folder using .clang-format, but failed!\e[0m\n"
fi

# try to compile kernel using all threads
if ! make -j"$(nproc)"; then
    echo -e "\n\e[31mBuild failed!\e[0m\n"
    exit 1
fi

# run
./build/out/nv2cpp
