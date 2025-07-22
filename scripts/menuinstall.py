import os

BLUE = '\033[44m'
RED = '\033[31m'
RESET = '\033[0m'

def install_select():
    os.system("clear")
    print(f"{BLUE}                   Instalation selector                                 ")
    print(f"{BLUE}                                                                        ")
    print(f"{BLUE}                                                                        ")
    print(f"{BLUE}'qb_x': compile kernel and ruuning with qemu                            ")
    print(f"{BLUE}'qb_p': compile in iso                                                  ")
    print(f"{BLUE}'qb_1s': install programs need                                          ")
    print(f"{BLUE}                                                                        ")
    print(f"{BLUE}                                                                        {RESET}")
    prompt = input(">")
    if prompt == "qb_x":
        os.system("make compile && make run")
    elif prompt == "qb_p":
        os.system("make compile && make iso")
    else:
        os.system("clear")
        print(f"{RED}ERR BearInstall:{RESET}  Command not found!")


    
install_select()

