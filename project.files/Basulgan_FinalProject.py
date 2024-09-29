# Project 

def show_menu():
    print("MENU CHOICES:")
    print("A. Conditional")
    print("B. List")
    print("C. Dictionary")
    print("D. Programmers Profile")

def operate_conditional():
    print("\n-- CONDITIONAL --")
    # Sample input
    try:
        gwa = float(input("Please enter GWA: "))


    # Using conditional statements
        if 1.00 <= gwa <= 3.00:
            print("Passed.")
        elif 3.01 <= gwa <= 5.00:
            print("Failed.")
        else:
            print("Invalid GWA. Enter a GWA between 1.00 and 5.00.")
    except ValueError:
        print("Invalid input. Please enter a valid GPA.")

def operate_list():
    print("\n-- LIST --")
    # Sample input
    bias = ['jennie', 'chen', 'wendy', 'ningning', 'doyoung', 'taeil']

    print("Original List:", bias)

    # Using different list methods
    try:
        new_bias = input("Please enter a new bias to add to the list! ")
        bias.append(new_bias)

        print("Updated List:", bias)
    except Exception as e:
        print(f"Error: {e}")

def operate_dictionary():
    print("\n-- DICTIONARY --")
    # Sample input
    idol = {"Name": "Kween Yasmin", "Age": 24, "Talent": "Singing, Dancing, Acting, Songwriter"}

    print("Original Biography:", idol)

    # Using different dictionary methods
    try:
        key_to_update = input("Please enter a key to update info about kween: ")
        if key_to_update in idol:
            new_value = input(f"Please enter the new value for {key_to_update}: ")
            idol[key_to_update] = new_value
            print("Updated Biography:", idol)
        else:
            print("Not found. Enter a valid key.")
    except Exception as e:
        print(f"Error: {e}")

def programmer_profile():
    print("\n-- Programmer Profile --")
    print("Name: Shaira Nicole J. Basulgan")
    print("Section: BSIS-2B")
    print("Course: Bachelor of Science in Information System")

def clear_screen():
    import os
    os.system('cls' if os.name == 'nt' else 'clear')

def main():
    while True:
        clear_screen()
        show_menu()
        choice = input("Choose a letter from the menu (A-D): ").upper()

        if choice == 'A':
            operate_conditional()
        elif choice == 'B':
            operate_list()
        elif choice == 'C':
            operate_dictionary()
        elif choice == 'D':
            programmer_profile()
        else:
            print("Invalid. Choose A-D only.")

        again = input("Another? (y/n): ").lower()
        if again != 'y':
            print("Bye!")
            break

if __name__ == "__main__":
    main()