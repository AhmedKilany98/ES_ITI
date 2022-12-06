import json

FILE_DATA = dict()
BILL_LIST = list()


def read_file():
    """ read Data in file grocery.json """
    with open("grocery.json", "r", encoding="utf-8") as file:
        return json.load(file)
    


def write_file():
    """ Write Data in file grocery.json """
    # global FILE_DATA
    with open("grocery.json", "w", encoding="utf-8") as file:
        json.dump(FILE_DATA, file, indent=4)


def add_product():
    """ Add New Product To shop """
    print("-"*5, "Welcome To Add New Product Window", "-"*5)
    # global FILE_DATA
    products = FILE_DATA["Products"]
    name = ""
    cost = 0.0
    size = 0

    # Convert Product name to lower case and remove space in right and left
    name = input("Enter Product Name:").lower().lstrip().rstrip()

    # Get Product Cost
    while True:
        cost = input("Enter Product Cost:")
        try:
            cost = float(cost)
        except ValueError:
            print("ERROR: Plz Enter a Valid Value.")
        else:
            break

    # Get Product Size
    while True:
        size = input("Enter Product Size:")
        try:
            size = int(size)
        except ValueError:
            print("Wrong Plz Enter a Positive Number.")
        else:
            break

    if name in list(products.keys()):
        print("i will over wirte on this data in the product")
        print("Product Name:", name)
        print("Product Cost:", cost)
        print("Product Amount:", size)
        overwrite = input("Overwrite (y/n)?").lower().lstrip().rstrip()
        if overwrite == "n":
            return

    products.update({name: [cost, size]})
    FILE_DATA["Products"] = products
    print("----- Your Produt is added -------")


def delete_product():
    """ Delete A Specific Product from shop """
    print("-"*5, "Welcome To Delete Product Window", "-"*5)
    # global FILE_DATA
    products = FILE_DATA["Products"]
    name = input("Enter Product Name:").lower().lstrip().rstrip()
    if name in list(products.keys()):
        print("Product Details")
        print("{", name, ",", end="")
        print(products[name][0], ",", end="")
        print(products[name][1], "}")

        products.pop(name)
        FILE_DATA["Products"] = products
        print("----- Your Produt is Deleted -------")
    else:
        print("ERROR: sorry your Product is not Exist To Delete it")


def show_products():
    """ Show All Products in System """
    print("-"*5, "Welcome To Product Window", "-"*5)
    # global FILE_DATA
    print("Product Name | Product Cost | Product Amount")
    print("--------------------------------------------")
    products = FILE_DATA["Products"]
    for i in list(products.keys()):
        print(i, end="")
        print(" "*(15-len(i)), end="")
        print(products[i][0], end="")
        print(" "*(15-len(str(
            products[i][0]))), end="")
        print(products[i][1])
    print("--------------------------------------------")


def edit_product():
    """ Edit A Specific Product in shop """
    print("-"*5, "Welcome To Edit Product Window", "-"*5)
    # global FILE_DATA
    products = FILE_DATA["Products"]
    # get product name
    name = input("Enter Product Name:").lower().rstrip().lstrip()
    cost = 0.0
    size = 0
    if name in list(products.keys()):
        print("Product Details")
        print("{", name, ",", end="")
        print(products[name][0], ",", end="")
        print(products[name][1], "}")
        # Get Product Cost
        while True:
            cost = input("Enter Product Cost:")
            try:
                cost = float(cost)
            except ValueError:
                print("ERROR: Plz Enter a Valid Value.")
                con = input("continue (y/n)").lower().rstrip().lstrip()
                if con == "n":
                    return
            else:
                break

        # Get Product Size
        while True:
            size = input("Enter Product Size:")
            try:
                size = int(size)
            except ValueError:
                print("Wrong Plz Enter a Positive Number.")
                con = input("continue (y/n)").lower().rstrip().lstrip()
                if con == "n":
                    return
            else:
                break

                # Update specific ID

        products.update({name: [cost, size]})
        FILE_DATA["Products"] = products
        print("----- Your Produt is Edited -------")

    else:
        print("ERROR: sorry your Product is not Exist To Edit it")


def buy_product():
    """ Buy A Specific Product From shop """
    print("-"*5, "Welcome To Buy Product Window", "-"*5)
    # global FILE_DATA
    # global BILL_LIST
    products = FILE_DATA["Products"]
    # get product name
    name = input("Enter Product Name:").lower().rstrip().lstrip()
    size = 0
    if name in list(products.keys()):
        # Get Product Size
        while True:
            size = input("Enter Product Size:")
            try:
                size = int(size)
            except ValueError:
                print("Wrong Plz Enter a Positive Number.")
                con = input("continue (y/n)").lower().rstrip().lstrip()
                if con == "n":
                    return
            else:
                if products[name][1] < size:
                    print(
                        "ERROR: plz Enter value in range [1-", products[name][1], "]")
                else:
                    break

        flag = 1

        for lst in BILL_LIST:
            if lst[0] == name:
                BILL_LIST[BILL_LIST.index(lst)][1] += products[name][0]*size
                BILL_LIST[BILL_LIST.index(lst)][2] += size
                flag = 0

        if flag == 1:
            BILL_LIST.append([name, products[name][0]*size, size])

        products[name][1] -= size

        if products[name][1] == 0:
            products.pop(name)

        FILE_DATA["Products"] = products
    else:
        print("ERROR: sorry This Product is not Exist")


def print_bill():
    """ Print Bill of Products """
    print("-"*5, "Welcome To Bill Window", "-"*5)
    # global BILL_LIST
    print("-"*45)
    print("\n\n\t\t Your Bill Sir.")
    print("-"*45)
    print("Product Name | Product Cost | Product Amount")
    for lst in BILL_LIST:
        print(lst[0], end="")
        print(" "*(15-len(str(lst[0]))), end="")
        print(round(lst[1], 2), end="")
        print(" "*(15-len(str(round(lst[1], 2)))), end="")
        print(lst[2])
    print("Thank You...")
    BILL_LIST.clear()
    print("-"*45)


def owner_create():
    """ Create new owner Account"""
    print("-"*5, "Welcome To Create New Account Window", "-"*5)
    # global FILE_DATA
    while True:
        print("Must lenght of UserName and Password not lease than 5 character")
        user_name = input("plz Enter UserName:")
        # Check Username lenght
        if len(user_name) < 5:
            print("plz Enter a valid user name")
        else:
            password = input("plz Enter Password:")
            # Check Password Lenght
            if len(password) < 5:
                print("plz Enter a valid password")
            else:
                FILE_DATA["Username"] = user_name
                FILE_DATA["Password"] = password
                break


def owner_login():
    """ Owner Login """
    print("-"*5, "Welcome To Login Window", "-"*5)
    # global FILE_DATA
    for i in range(0, 3):
        user_name = input("plz Enter UserName:")
        if user_name == FILE_DATA["Username"]:
            for x in range(0, 3):
                password = input("plz Enter Password:")
                if password == FILE_DATA["Password"]:
                    return True
                else:
                    print("password wrong try again.")
        else:
            print("UserName wrong try again.")

    return False


def owner():
    """ owner Setting """
    if FILE_DATA["Username"]:
        if not owner_login():
            return

    else:
        owner_create()

    while True:
        print("-"*5, "Welcome To Owner Operation", "-"*5)
        print("1-Show Products")
        print("2-Add Product")
        print("3-Edit Product")
        print("4-Delete Product")
        print("5-Back")
        select = input("\nEnter Your Choice:")

        if select == "1":
            show_products()
        elif select == "2":
            add_product()
        elif select == "3":
            edit_product()
        elif select == "4":
            delete_product()
        else:
            return


def user():
    """ User Setting """
    while True:
        print("-"*5, "Welcome To User Operation", "-"*5)
        print("1-Show Products")
        print("2-Buy Product")
        print("3-Print Bill")
        print("4-Back")
        select = input("\nEnter Your Choice:")
        if select == "1":
            show_products()
        elif select == "2":
            buy_product()
        elif select == "3":
            print_bill()
        else:
            return


def menu():
    """ Menu """
    # Read File grocery shop
    global FILE_DATA
    try:
        FILE_DATA = read_file()
    except:
        FILE_DATA = {"Username": "","Password": "","Products": {}}
        write_file()

    while True:
        mode = input("\n1-Owner\n2-User\n3-Exit\n\nSelect Mode:")
        if mode == "1":
            owner()
        elif mode == "2":
            user()
        else:
            exit(0)

        write_file()


def main():
    """ Main Function """
    print("-"*11, "Wecome To ITI grocery shop", "-"*11)
    menu()


if __name__ == "__main__":
    main()
