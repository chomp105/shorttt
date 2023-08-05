import os
shorttt = open(r"shorttt.c","r")
newshorttt = shorttt.readlines()
newshorttt[2] = newshorttt[2].replace(r'\e[1;1H\e[2J",getchar())','",getchar());system(\"cls\")')
shorttt.close()
os.system("del shorttt.c")
shorttt = open("shorttt.c","w")
shorttt.writelines(newshorttt)
shorttt.close()
