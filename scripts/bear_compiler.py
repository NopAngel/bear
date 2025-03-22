
# IMPORTANT: This was only created to put a "Launcher" to QEMU and thus run the project faster, but all credits to QEMU.


import tkinter as tk
from tkinter import filedialog, messagebox
import subprocess
import os
import threading
import random

def g_text_console(console):
    characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}|;:',.<>?/~`"
    while True:
        text = "".join(random.choice(characters) for _ in range(random.randint(20, 50)))
        console.insert(tk.END, text + "\n")
        console.see(tk.END)
        console.update()
        root.after(random.randint(50, 150))

def execute_qemu(console):
    file_path = filedialog.askopenfilename(
        title="Select Kernel file",
        filetypes=[("All Files", "*.*")]
    )

    if not file_path:
        messagebox.showwarning("No file selected", "Please select a file.")
        return

    if not os.path.exists(file_path):
        messagebox.showerror("File not found", f"The file '{file_path}' does not exist.")
        return

    file_name = os.path.basename(file_path)

    if file_name != "kernel":
        messagebox.showerror("Invalid file", "The selected file must be named 'kernel' without an extension.")
        return

    try:
        threading.Thread(target=g_text_console, args=(console,), daemon=True).start()
        subprocess.run([
            "qemu-system-x86_64",
            "-kernel", file_path,
        ], check=True)
    except FileNotFoundError:
        messagebox.showerror("QEMU not found", "QEMU executable not found. Please ensure QEMU is installed.")
    except Exception as e:
        messagebox.showerror("Execution error", f"An error occurred while executing QEMU:\n{e}")

root = tk.Tk()
root.title("Bear Launcher")

frame = tk.Frame(root)
frame.pack()

console = tk.Text(frame, height=15, width=50, bg="black", fg="green", font=("Courier", 10))
console.pack(pady=10)

execute_button = tk.Button(root, text="Run BearLauncher", command=lambda: execute_qemu(console))
execute_button.pack(pady=20)

root.geometry("400x400")
root.mainloop()
