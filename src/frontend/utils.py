def input_valid(msg, start, end):
    while True:
        inp = input(msg)
        if not inp.isdecimal():
            print("Invalid Input..., Enter a numeric value.")
        elif not start <= int(inp) <= end:
            print("Invalid Range..., Try again!")
        else:
            return int(inp)

def show_menu(menu: list) -> None:
    for index, item in enumerate(menu):
        print(f"{index+1}. {item}")