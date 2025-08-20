import os
import platform

print("🐻 BearOS Installer — Preparing your system")

pkg_managers = {
    "Debian": "apt",
    "Arch": "pacman",
    "Fedora": "dnf"
}

system = platform.system()
distro = platform.linux_distribution()[0] if hasattr(platform, "linux_distribution") else "Unknown"

pkg = pkg_managers.get(distro, "apt")

print(f"Detected distro: {distro}")
print(f"Using package manager: {pkg}")

os.system(f"sudo {pkg} install make gcc g++ nasm python3 -y")
print("✅ Environment ready. You may now run: make menuconfig && make compile")

