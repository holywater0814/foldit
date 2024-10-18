#!/bin/bash

# Detect OS
OS=$(uname)

if [[ "$OS" == "Linux" ]]; then
    # Check for Debian/Ubuntu
    if [[ -f /etc/debian_version ]]; then
        echo "Detected Debian/Ubuntu..."

        # Install wget if not installed
        if ! command -v wget &> /dev/null; then
            echo "wget could not be found. Installing..."
            sudo apt update
            sudo apt install -y wget
        fi

        # Download and install the tool
        echo "Downloading the tool..."
        wget https://github.com/your-username/your-repo/releases/download/v1.0/your_tool.deb
        echo "Installing the tool..."
        sudo dpkg -i your_tool.deb
        rm your_tool.deb

    # Check for Arch Linux
    elif [[ -f /etc/arch-release ]]; then
        echo "Detected Arch Linux..."

        # Install wget if not installed
        if ! command -v wget &> /dev/null; then
            echo "wget could not be found. Installing..."
            sudo pacman -Sy wget
        fi

        # Download and install the tool
        echo "Downloading the tool..."
        wget https://github.com/your-username/your-repo/releases/download/v1.0/your_tool.tar.gz
        echo "Extracting the tool..."
        tar -xzf your_tool.tar.gz -C /usr/local/bin
        rm your_tool.tar.gz

    else
        echo "Unsupported Linux distribution."
        exit 1
    fi

elif [[ "$OS" == "Darwin" ]]; then
    # Install on macOS
    echo "Detected macOS..."

    # Install Homebrew if not installed
    if ! command -v brew &> /dev/null; then
        echo "Homebrew is not installed. Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi

    # Install wget if not installed
    if ! command -v wget &> /dev/null; then
        echo "wget could not be found. Installing..."
        brew install wget
    fi

    # Download and install the tool
    echo "Downloading the tool..."
    wget https://github.com/your-username/your-repo/releases/download/v1.0/your_tool.tar.gz
    echo "Extracting the tool..."
    tar -xzf your_tool.tar.gz -C /usr/local/bin
    rm your_tool.tar.gz

else
    echo "Unsupported OS."
    exit 1
fi

echo "Installation complete!"
