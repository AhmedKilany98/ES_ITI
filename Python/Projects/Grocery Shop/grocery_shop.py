
# print("-"*10,"Task3 System for grocery shop","-"*10)
print("-"*11,"Wecome To ITI grocery shop","-"*11)

## Product Parameter
pId, pName, pCost, pSize = "", "", 0.0, 0
## Product Dictionary DataBase
Products = {"0":["banana" , 5.3 , 5]}

## Bill Parameter
billList = []

## Owner Parameter
onrSettingFlag=0
onrUserName = ""
onrPassword = ""
## Owner Setting [flagstatus , Owner UserName, Owner Password, Owner Products] 
OwnerSetting = [0,"","",Products]

while True:
    mode  = input("\n1-Owner\n2-User\n3-Exit\n\nSelect Mode:")

    ## Owner Setting
    if mode == '1':
        while True:
            ## Create Username
            if OwnerSetting[0] == 0:
                print("\nMust lenght of UserName and Password not lease than 5 character")
                onrUserName = input("plz Enter UserName:")

                ## Check Username lenght
                if len(onrUserName) < 5:
                    break
                onrPassword = input("plz Enter Password:")

                ## Check Password Lenght
                if len(onrPassword) < 5:
                    break

                OwnerSetting[0] = 1
                OwnerSetting[1] = onrUserName
                OwnerSetting[2] = onrPassword

            ## Access System by Username and password
            else:
                flg = 1
                for i in range(0,3):
                    onrUserName = input("\n\nplz Enter UserName:")
                    if onrUserName == OwnerSetting[1]:
                        for x in range(0,3):
                            onrPassword = input("plz Enter Password:")
                            if onrPassword == OwnerSetting[2]:
                                flg = 0
                                break
                            else:
                                print("password wrong try again.")
                    else:
                        print("UserName wrong try again.")

                    if flg == 0:break

                if flg:break

            ## Owner Operation
            onrSelect  = input("\n\n1-Show Products\n2-Add Product\n3-Edit Product\n4-Delete Product\n5-exit\n\nEnter Selection:")

            ## Show Products To Owner
            if onrSelect == '1':
                print("-"*60)
                print("Product Id | Product Name | Product Cost | Product Size")


                for i in list(Products.keys()):
                    print(i,(" "*(11-len(i))),Products[i][0],(" "*(13-len(str(Products[i][0])))),Products[i][1],(" "*(13-len(str(Products[i][1])))),Products[i][2])
                print("-"*60)

            ## Add Product
            elif onrSelect == '2':
                ## Convert Product name to lower case and remove space in right and left
                pName = input("Enter Product Name:").lower().lstrip().rstrip()

                ## Get Product Cost as floting value 
                fg =0 
                for x in range(0,3):
                    fg=0
                    pCost = input("Enter Product Cost:")
                    for i in pCost:
                        if i.isdigit() != True:
                            if i != '.':
                                fg = 1
                                print("Wrong Plz Enter a Float Positive Number.")
                                break
                    if fg ==0:break

                ## exit if cann't enter a valid value
                if fg == 1:break

                ## Get Product Size 
                for x in range(0,3):
                    fg=0
                    pSize = input("Enter Product Size:")
                    for i in pSize:
                        if i.isdigit() != True:
                            fg = 1
                            print("Wrong Plz Enter a Positive Number.")
                            break
                    if fg ==0:break

                ## exit if cann't enter a valid value
                if fg == 1:break

                ## Compute Product ID by hash Function Algorithm
                p = 31
                m = 1e9+9
                Id = ord(pName[0])
                for i in range(1,len(pName)):
                    Id =  (Id + ord(pName[i]) * pow(p,i)) % m

                pId = str(int(Id))
                
                Products.update({pId:[pName,pCost,pSize]})

                print("----- [Done] Your Produt is added -------")

            ## Edit Product
            elif onrSelect == '3':


                fg = 0
                for x in range(0,3):
                    fg=0
                    pId = input("Enter Product Id:")
                    for i in pId:
                        if i.isdigit() != True:
                            fg = 1
                            print("Wrong Plz Enter a Positive Number.")
                            break
                    if fg ==0:break

                ## exit if cann't enter a valid value
                if fg == 1:break

                ## check if id exist
                # print(list(Products.keys()))
                if list(Products.keys()).count(pId) == 0:
                    print("Id does not exist in product.")
                    # break
                else:
                    pName = Products.get(pId)[0]
                    print("Product Name of ",pId,":",pName)

                    ## Get Product Cost as floting value 
                    fg =0 
                    for x in range(0,3):
                        fg=0
                        pCost = input("Enter Product Cost:")
                        for i in pCost:
                            if i.isdigit() != True:
                                if i != '.':
                                    fg = 1
                                    print("Wrong Plz Enter a Float Positive Number.")
                                    break
                        if fg ==0:break

                    ## exit if cann't enter a valid value
                    if fg == 1:break

                    ## Get Product Size 
                    for x in range(0,3):
                        fg=0
                        pSize = input("Enter Product Size:")
                        for i in pSize:
                            if i.isdigit() != True:
                                fg = 1
                                print("Wrong Plz Enter a Positive Number.")
                                break
                        if fg ==0:break

                    ## exit if cann't enter a valid value
                    if fg == 1:break

                    ## Update specific ID
                    Products.update({pId:[pName,pCost,pSize]})
                    print("----- [Done] Your Produt is Edited -------")

            ## Delete Product
            elif onrSelect == '4':
                fg = 0
                for x in range(0,3):
                    fg=0
                    pId = input("Enter Product Id:")
                    for i in pId:
                        if i.isdigit() != True:
                            fg = 1
                            print("Wrong Plz Enter a Positive Number.")
                            break
                    if fg ==0:break

                ## exit if cann't enter a valid value
                if fg == 1:break
                
                dictmp = Products.pop(pId,"Kilany")
                if dictmp != "Kilany":
                    print(dictmp)
                    print("----- [Done] Your Produt is Deleted -------")

                else:
                    print("----- Id does not exist in product -------")

            ## Exit
            else:
                break

    ## User Setting
    elif mode == '2':
        while True:
            UsrSelect  = input("\n\n1-Show products\n2-Buy product\n3-print bill\n4-exit\n\nEnter Selection:")

            ## Show Products To User
            if UsrSelect == '1':
                print("-"*60)
                print("Product Id | Product Name | Product Cost | Product Size")
                for i in list(Products.keys()):
                    print(i,(" "*(11-len(i))),Products[i][0],(" "*(13-len(str(Products[i][0])))),Products[i][1],(" "*(13-len(str(Products[i][1])))),Products[i][2])
                print("-"*60)

            ## Buy Products    
            elif UsrSelect == '2':
                while True:
                    id = input("Enter Product id:")
                    plst = Products.get(id)
                    if plst != None:
                        mnt = ""
                        while True:
                            mnt = input("Enter Mount:")
                            for i in mnt:
                                if i.isdigit() != True:
                                    print("Plz Enter an integer valid mount:")
                                    mnt = "xx"
                                    break
                            if mnt != "xx":break

                        mnt = int(mnt)
                        if mnt <= plst[2]:
                            plst[2] -= mnt

                            xx = 1
                            ## Duplicate the same product in Bill
                            for l in range(0,len(billList)):
                                if billList[l].count(plst[0]):
                                    billList[l][1] += (plst[1]*mnt)
                                    billList[l][2] += (mnt)
                                    xx = 0 

                            if xx:
                                billList.append([plst[0],plst[1]*mnt,mnt])
                        
                        
                        else:
                            print("it doesn't exist the amount.")

                    else:
                        print("the product does not exist, please Select Another one.")

                    chk = input("continue (y,n)?")
                    if chk != 'y':
                        break
            
            ## Print User Bill 
            elif UsrSelect == '3':
                print("\n\n Your Bill Sir.\n"+"-"*40)
                print("Product Name | Product Cost | Product Size")
                for i in range(0,len(billList)):
                    print(billList[i][0],(" "*(13-len(str(billList[i][0])))),billList[i][1],(" "*(13-len(str(billList[i][1])))),billList[i][2])

                print("Thank You...")
            else:
                break

    ## Anytingh else to exit from App
    else :
        exit(0)

