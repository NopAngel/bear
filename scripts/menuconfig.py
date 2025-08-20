import os

sections = {
    "General Setup": {
        "CONFIG_DEBUG": "Enable debugging support",
        "CONFIG_RECOVERY": "Include recovery system",
    },
    "Device Drivers": {
        "CONFIG_SOUND_BLASTER": "Sound Blaster driver",
        "CONFIG_MOUSE_PS2": "PS/2 mouse support",
        "CONFIG_ACCELEROMETER": "Accelerometer driver",
        "CONFIG_VESA": "VESA graphics driver"
    }
}

config = {}

def ask_option(key, desc):
    while True:
        choice = input(f"{desc} (y/n): ").strip().lower()
        if choice in ['y', 'n']:
            config[key] = choice
            break

print("🧠 BearOS MenuConfig — Inspired by Linux kernel")
print("==============================================\n")

for section, options in sections.items():
    print(f"\n[{section}]")
    for key, desc in options.items():
        ask_option(key, desc)

with open(".bearconfig", "w") as f:
    for k, v in config.items():
        f.write(f"{k}={v}\n")

print("\nConfiguration saved to .bearconfig")

