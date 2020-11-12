print "============================================================="
print ""
print "                 LATES Motors Inc                            "
print ""
print "        LATES Mortors Entertainment System v6.2              "
print ""
print "             Please enter your credentials                   "
print "============================================================="
username = "dev"
password = "Sup3rStr0ngP4ssw0rd!!"
while 1:    
    user = raw_input("Username: ")    
    passw = raw_input("Password: ")
    if user == username:
        if password == passw:
            print "Welcome dev !"
            exit()
        else:
            print "Wrong password !"
    else:
        print "Wrong username !"
